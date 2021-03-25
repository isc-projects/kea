// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_TLS_H
#define TEST_TLS_H

#ifndef CONFIG_H_WAS_INCLUDED
#error config.h must be included before test_tls.h
#endif

#include <asiolink/crypto_tls.h>

#include <string>

namespace isc {
namespace asiolink {
namespace test {

/// @brief Configure the TLS server.
void configServer(TlsContextPtr& ctx);

/// @brief Configure trusted self-signed TLS server.
void configTrustedSelf(TlsContextPtr& ctx);

/// @brief Configure the TLS server with no client certificate request.
void configServerNoReq(TlsContextPtr& ctx);

/// @brief Configure the TLS server with no subject alternative name.
void configServerRaw(TlsContextPtr& ctx);

/// @brief Configure the TLS client.
void configClient(TlsContextPtr& ctx);

/// @brief Configure another TLS client.
void configOther(TlsContextPtr& ctx);

/// @brief Configure self-signed TLS client.
void configSelf(TlsContextPtr& ctx);

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc

#endif // TEST_TLS_H
