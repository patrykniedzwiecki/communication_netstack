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

#include "socket_fd_context.h"
#include "context_key.h"

namespace OHOS {
namespace NetStack {
SocketFdContext::SocketFdContext(napi_env env, EventManager *manager) : BaseContext(env, manager) {}

void SocketFdContext::ParseParams(napi_value *params, size_t paramsCount)
{
    if (paramsCount == PARAM_JUST_CALLBACK) {
        SetParseOK(SetCallback(params[0]) == napi_ok);
        return;
    }
    SetParseOK(true);
}

uint32_t SocketFdContext::GetSocketFd() const
{
    return reinterpret_cast<uint32_t>(manager_->GetData());
}
} // namespace NetStack
} // namespace OHOS
