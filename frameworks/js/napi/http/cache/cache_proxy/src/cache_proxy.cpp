/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base64_utils.h"
#include "calculate_md5.h"
#include "constant.h"
#if USE_CACHE
#include "http_exec.h"
#endif
#include "lru_cache_disk_handler.h"
#include "netstack_common_utils.h"
#if USE_CACHE
#include "netstack_log.h"
#include "request_context.h"
#endif

#include "cache_proxy.h"

static constexpr const char *CACHE_FILE = "/data/storage/el2/base/cache.json";

namespace OHOS::NetStack {
static LRUCacheDiskHandler DISK_LRU_CACHE(CACHE_FILE, MAX_DISK_CACHE_SIZE); // NOLINT(cert-err58-cpp)

CacheProxy::CacheProxy(HttpRequestOptions &requestOptions) : requestOptions_(requestOptions), strategy_(requestOptions)
{
}

std::string CacheProxy::MakeKey()
{
    std::string str = requestOptions_.GetUrl() + HttpConstant::HTTP_LINE_SEPARATOR +
                      CommonUtils::ToLower(requestOptions_.GetMethod()) + HttpConstant::HTTP_LINE_SEPARATOR;
    for (const auto &p : requestOptions_.GetHeader()) {
        str += p.first + HttpConstant::HTTP_HEADER_SEPARATOR + p.second + HttpConstant::HTTP_LINE_SEPARATOR;
    }
    str += std::to_string(requestOptions_.GetHttpVersion());
    return CalculateMD5(str);
}

bool CacheProxy::ReadResponseFromCache(HttpResponse &response)
{
#if USE_CACHE
    if (!strategy_.CouldUseCache()) {
        NETSTACK_LOGI("only GET/HEAD method or header has [Range] can use cache");
        return false;
    }

    auto responseFromCache = DISK_LRU_CACHE.Get(MakeKey());
    if (responseFromCache.empty()) {
        NETSTACK_LOGI("no cache with this request");
        return false;
    }
    HttpResponse cachedResponse;
    cachedResponse.SetRawHeader(Base64::Decode(responseFromCache[HttpConstant::RESPONSE_KEY_HEADER]));
    cachedResponse.SetResult(Base64::Decode(responseFromCache[HttpConstant::RESPONSE_KEY_RESULT]));
    cachedResponse.SetCookies(Base64::Decode(responseFromCache[HttpConstant::RESPONSE_KEY_COOKIES]));
    cachedResponse.SetResponseTime(Base64::Decode(responseFromCache[HttpConstant::RESPONSE_TIME]));
    cachedResponse.SetResponseCode(static_cast<uint32_t>(ResponseCode::OK));
    cachedResponse.ParseHeaders();

    CacheStatus status = strategy_.RunStrategy(cachedResponse);
    if (status == CacheStatus::FRESH) {
        response = cachedResponse;
        NETSTACK_LOGI("cache is FRESH");
        return true;
    }
    if (status == CacheStatus::STALE) {
        NETSTACK_LOGI("cache is STATE, we try to talk to the server");
        RequestContext context(nullptr, nullptr);
        context.options = requestOptions_;
        HttpExec::ExecRequest(&context);
        if (context.response.GetResponseCode() == static_cast<uint32_t>(ResponseCode::NOT_MODIFIED)) {
            NETSTACK_LOGI("cache is NOT_MODIFIED, we use the cache");
            response = cachedResponse;
        } else {
            NETSTACK_LOGI("cache is MODIFIED, server return the newer one");
            response = context.response;
        }
        WriteResponseToCache(response);
        return true;
    }
    NETSTACK_LOGI("cache should not be used");
    return false;
#else
    return false;
#endif
}

void CacheProxy::WriteResponseToCache(const HttpResponse &response)
{
#if USE_CACHE
    if (!strategy_.IsCacheable(response)) {
        NETSTACK_LOGI("do not cache this response");
        return;
    }
    std::unordered_map<std::string, std::string> cacheResponse;
    cacheResponse[HttpConstant::RESPONSE_KEY_HEADER] = Base64::Encode(response.GetRawHeader());
    cacheResponse[HttpConstant::RESPONSE_KEY_RESULT] = Base64::Encode(response.GetResult());
    cacheResponse[HttpConstant::RESPONSE_KEY_COOKIES] = Base64::Encode(response.GetCookies());
    cacheResponse[HttpConstant::RESPONSE_TIME] = Base64::Encode(response.GetResponseTime());

    DISK_LRU_CACHE.Put(MakeKey(), cacheResponse);
#endif
}
} // namespace OHOS::NetStack