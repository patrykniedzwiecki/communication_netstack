/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef COMMUNICATIONNETSTACK_HTTP_REQUEST_OPTIONS_H
#define COMMUNICATIONNETSTACK_HTTP_REQUEST_OPTIONS_H

#include <map>
#include <string>

namespace OHOS::NetStack {
enum class HttpProtocol {
    HTTP1_1,
    HTTP2,
    HTTP_NONE, // default choose by curl
};

enum class ResponseCode {
    OK = 200,
    CREATED,
    ACCEPTED,
    NOT_AUTHORITATIVE,
    NO_CONTENT,
    RESET,
    PARTIAL,
    MULT_CHOICE = 300,
    MOVED_PERM,
    MOVED_TEMP,
    SEE_OTHER,
    NOT_MODIFIED,
    USE_PROXY,
    BAD_REQUEST = 400,
    UNAUTHORIZED,
    PAYMENT_REQUIRED,
    FORBIDDEN,
    NOT_FOUND,
    BAD_METHOD,
    NOT_ACCEPTABLE,
    PROXY_AUTH,
    CLIENT_TIMEOUT,
    CONFLICT,
    GONE,
    LENGTH_REQUIRED,
    PRECON_FAILED,
    ENTITY_TOO_LARGE,
    REQ_TOO_LONG,
    UNSUPPORTED_TYPE,
    INTERNAL_ERROR = 500,
    NOT_IMPLEMENTED,
    BAD_GATEWAY,
    UNAVAILABLE,
    GATEWAY_TIMEOUT,
    VERSION,
};

class HttpRequestOptions final {
public:
    HttpRequestOptions();

    void SetUrl(const std::string &url);

    void SetMethod(const std::string &method);

    void SetBody(const void *data, size_t length);

    void SetHeader(const std::string &key, const std::string &val);

    void SetReadTimeout(uint32_t readTimeout);

    void SetConnectTimeout(uint32_t connectTimeout);

    void SetUsingProtocol(HttpProtocol httpProtocol);

    [[nodiscard]] const std::string &GetUrl() const;

    [[nodiscard]] const std::string &GetMethod() const;

    [[nodiscard]] const std::string &GetBody() const;

    [[nodiscard]] const std::map<std::string, std::string> &GetHeader() const;

    [[nodiscard]] uint32_t GetReadTimeout() const;

    [[nodiscard]] uint32_t GetConnectTimeout() const;

    [[nodiscard]] uint32_t GetHttpVersion() const;

private:
    std::string url_;

    std::string body_;

    std::string method_;

    std::map<std::string, std::string> header_;

    uint32_t readTimeout_;

    uint32_t connectTimeout_;

    HttpProtocol usingProtocol_;
};
} // namespace OHOS::NetStack

#endif /* COMMUNICATIONNETSTACK_HTTP_REQUEST_OPTIONS_H */
