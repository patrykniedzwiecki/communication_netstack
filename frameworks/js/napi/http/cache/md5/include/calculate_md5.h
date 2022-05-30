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

#ifndef COMMUNICATIONNETSTACK_CALCULATE_MD5_H
#define COMMUNICATIONNETSTACK_CALCULATE_MD5_H

#include <string>

namespace OHOS::NetStack {
std::string CalculateMD5(const std::string &source);
} // namespace OHOS::NetStack
#endif /* COMMUNICATIONNETSTACK_CALCULATE_MD5_H */