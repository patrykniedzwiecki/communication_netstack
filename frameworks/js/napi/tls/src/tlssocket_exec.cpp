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

#include "tlssocket_exec.h"

#include <string>
#include <vector>

#include <napi/native_api.h>

#include "context_key.h"
#include "event_list.h"
#include "napi_utils.h"
#include "netstack_log.h"
#include "socket_error.h"
#include "tls_socket.h"

namespace OHOS {
namespace NetStack {
bool TLSSocketExec::ExecGetCertificate(GetCertificateContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecGetCertificate tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->GetCertificate([&context](int32_t errorNumber, const std::string &cert) {
        context->cert_ = cert;
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecConnect(TLSConnectContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecConnect tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->Connect(context->connectOptions_, [&context](int32_t errorNumber) {
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecGetCipherSuites(GetCipherSuitesContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecGetCipherSuites tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->GetCipherSuite([&context](int32_t errorNumber, const std::vector<std::string> &suite) {
        context->cipherSuites_ = suite;
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecGetRemoteCertificate(GetRemoteCertificateContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecGetRemoteCertificate tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->GetRemoteCertificate([&context](int32_t errorNumber, const std::string &cert) {
        context->remoteCert_ = cert;
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecGetProtocol(GetProtocolContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecGetProtocol tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->GetProtocol([&context](int32_t errorNumber, const std::string &protocol) {
        context->protocol_ = protocol;
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecGetSignatureAlgorithms(GetSignatureAlgorithmsContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecGetSignatureAlgorithms tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->GetSignatureAlgorithms([&context](int32_t errorNumber, const std::vector<std::string> &algorithms) {
        context->signatureAlgorithms_ = algorithms;
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecSend(TLSSendContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecSend tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    TCPSendOptions tcpSendOptions;
    tcpSendOptions.SetData(context->data_);
    tlsSocket->Send(tcpSendOptions, [&context](int32_t errorNumber) {
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecClose(TLSNapiContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecClose tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->Close([&context](int32_t errorNumber) {
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    delete tlsSocket;
    manager->SetData(nullptr);
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecBind(TLSBindContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = new TLSSocket();
    tlsSocket->Bind(context->address_, [&context](int32_t errorNumber) {
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            std::string errorString = MakeErrorMessage(errorNumber);
            context->SetError(errorNumber, errorString);
        }
    });
    manager->SetData(tlsSocket);
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecGetRemoteAddress(TLSGetRemoteAddressContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecGetRemoteAddress tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->GetRemoteAddress([&context](int32_t errorNumber, const NetAddress address) {
        context->address_ = address;
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecGetState(TLSGetStateContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecGetState tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->GetState([&context](int32_t errorNumber, const SocketStateBase state) {
        context->state_ = state;
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

bool TLSSocketExec::ExecSetExtraOptions(TLSSetExtraOptionsContext *context)
{
    auto manager = context->GetManager();
    if (manager == nullptr) {
        NETSTACK_LOGE("manager is nullptr");
        return false;
    }
    auto tlsSocket = reinterpret_cast<TLSSocket *>(manager->GetData());
    if (tlsSocket == nullptr) {
        NETSTACK_LOGE("ExecSetExtraOptions tlsSocket is null");
        context->SetError(TLS_ERR_NO_BIND, MakeErrorMessage(TLS_ERR_NO_BIND));
        return false;
    }
    tlsSocket->SetExtraOptions(context->options_, [&context](int32_t errorNumber) {
        context->errorNumber_ = errorNumber;
        if (errorNumber != TLSSOCKET_SUCCESS) {
            context->SetError(errorNumber, MakeErrorMessage(errorNumber));
        }
    });
    return context->errorNumber_ == TLSSOCKET_SUCCESS;
}

napi_value TLSSocketExec::GetCertificateCallback(GetCertificateContext *context)
{
    napi_value obj = NapiUtils::CreateObject(context->GetEnv());
    if (NapiUtils::GetValueType(context->GetEnv(), obj) != napi_object) {
        return NapiUtils::GetUndefined(context->GetEnv());
    }
    napi_value x509CertRawData = NapiUtils::CreateArray(context->GetEnv(), context->cert_.size());
    NapiUtils::SetNamedProperty(context->GetEnv(), obj, "data", x509CertRawData);
    NapiUtils::SetInt32Property(context->GetEnv(), obj, "encodingFormat", 1);
    return obj;
}

napi_value TLSSocketExec::ConnectCallback(TLSConnectContext *context)
{
    return NapiUtils::GetUndefined(context->GetEnv());
}

napi_value TLSSocketExec::GetCipherSuitesCallback(GetCipherSuitesContext *context)
{
    napi_value cipherSuites = NapiUtils::CreateArray(context->GetEnv(), 0);
    int index = 0;
    for (const auto &cipher : context->cipherSuites_) {
        napi_value cipherSuite = NapiUtils::CreateStringUtf8(context->GetEnv(), cipher);
        NapiUtils::SetArrayElement(context->GetEnv(), cipherSuites, index++, cipherSuite);
    }
    return cipherSuites;
}

napi_value TLSSocketExec::GetRemoteCertificateCallback(GetRemoteCertificateContext *context)
{
    napi_value obj = NapiUtils::CreateObject(context->GetEnv());
    if (NapiUtils::GetValueType(context->GetEnv(), obj) != napi_object) {
        return NapiUtils::GetUndefined(context->GetEnv());
    }
    napi_value x509CertRawData = NapiUtils::CreateArray(context->GetEnv(), context->remoteCert_.size());
    NapiUtils::SetNamedProperty(context->GetEnv(), obj, "data", x509CertRawData);
    NapiUtils::SetInt32Property(context->GetEnv(), obj, "encodingFormat", 1);
    return obj;
}

napi_value TLSSocketExec::GetProtocolCallback(GetProtocolContext *context)
{
    return NapiUtils::CreateStringUtf8(context->GetEnv(), context->protocol_);
}

napi_value TLSSocketExec::GetSignatureAlgorithmsCallback(GetSignatureAlgorithmsContext *context)
{
    napi_value signatureAlgorithms = NapiUtils::CreateArray(context->GetEnv(), 0);
    int index = 0;
    for (const auto &algorithm : context->signatureAlgorithms_) {
        napi_value signatureAlgorithm = NapiUtils::CreateStringUtf8(context->GetEnv(), algorithm);
        NapiUtils::SetArrayElement(context->GetEnv(), signatureAlgorithms, index++, signatureAlgorithm);
    }
    return signatureAlgorithms;
}

napi_value TLSSocketExec::SendCallback(TLSSendContext *context)
{
    return NapiUtils::GetUndefined(context->GetEnv());
}

napi_value TLSSocketExec::CloseCallback(TLSNapiContext *context)
{
    return NapiUtils::GetUndefined(context->GetEnv());
}

napi_value TLSSocketExec::BindCallback(TLSBindContext *context)
{
    context->Emit(EVENT_LISTENING, std::make_pair(NapiUtils::GetUndefined(context->GetEnv()),
                                                  NapiUtils::GetUndefined(context->GetEnv())));
    return NapiUtils::GetUndefined(context->GetEnv());
}

napi_value TLSSocketExec::GetStateCallback(TLSGetStateContext *context)
{
    napi_value obj = NapiUtils::CreateObject(context->GetEnv());
    if (NapiUtils::GetValueType(context->GetEnv(), obj) != napi_object) {
        return NapiUtils::GetUndefined(context->GetEnv());
    }
    NapiUtils::SetBooleanProperty(context->GetEnv(), obj, KEY_IS_BOUND, context->state_.IsBound());
    NapiUtils::SetBooleanProperty(context->GetEnv(), obj, KEY_IS_CLOSE, context->state_.IsClose());
    NapiUtils::SetBooleanProperty(context->GetEnv(), obj, KEY_IS_CONNECTED, context->state_.IsConnected());
    return obj;
}

napi_value TLSSocketExec::GetRemoteAddressCallback(TLSGetRemoteAddressContext *context)
{
    napi_value obj = NapiUtils::CreateObject(context->GetEnv());
    if (NapiUtils::GetValueType(context->GetEnv(), obj) != napi_object) {
        return NapiUtils::GetUndefined(context->GetEnv());
    }
    NapiUtils::SetStringPropertyUtf8(context->GetEnv(), obj, KEY_ADDRESS, context->address_.GetAddress());
    NapiUtils::SetUint32Property(context->GetEnv(), obj, KEY_FAMILY, context->address_.GetJsValueFamily());
    NapiUtils::SetUint32Property(context->GetEnv(), obj, KEY_PORT, context->address_.GetPort());
    return obj;
}

napi_value TLSSocketExec::SetExtraOptionsCallback(TLSSetExtraOptionsContext *context)
{
    return NapiUtils::GetUndefined(context->GetEnv());
}

} // namespace NetStack
} // namespace OHOS
