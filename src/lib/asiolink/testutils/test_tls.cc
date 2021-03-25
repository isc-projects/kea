// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/testutils/test_tls.h>

namespace isc {
namespace asiolink {
namespace test {

/// @brief Configure the TLS server.
void configServer(TlsContextPtr& ctx) {
    std::string ca(std::string(TEST_CA_DIR) + "/kea-ca.crt");
    std::string cert(std::string(TEST_CA_DIR) + "/kea-server.crt");
    std::string key(std::string(TEST_CA_DIR) + "/kea-server.key");
    TlsContext::configure(ctx, TlsRole::SERVER, ca, cert, key, true);
}

/// @brief Configure the TLS server trusting the self-signed client.
void configTrustedSelf(TlsContextPtr& ctx) {
    std::string ca(std::string(TEST_CA_DIR) + "/kea-self.crt");
    std::string cert(std::string(TEST_CA_DIR) + "/kea-server.crt");
    std::string key(std::string(TEST_CA_DIR) + "/kea-server.key");
    TlsContext::configure(ctx, TlsRole::SERVER, ca, cert, key, true);
}

/// @brief Configure the TLS server with no client certificate request.
void configServerNoReq(TlsContextPtr& ctx) {
    std::string ca(std::string(TEST_CA_DIR) + "/kea-ca.crt");
    std::string cert(std::string(TEST_CA_DIR) + "/kea-server.crt");
    std::string key(std::string(TEST_CA_DIR) + "/kea-server.key");
    TlsContext::configure(ctx, TlsRole::SERVER, ca, cert, key, false);
}

/// @brief Configure the TLS server with no subject alternative name.
void configServerRaw(TlsContextPtr& ctx) {
    std::string ca(std::string(TEST_CA_DIR) + "/kea-ca.crt");
    std::string cert(std::string(TEST_CA_DIR) + "/kea-server-raw.crt");
    std::string key(std::string(TEST_CA_DIR) + "/kea-server.key");
    TlsContext::configure(ctx, TlsRole::SERVER, ca, cert, key, true);
}

/// @brief Configure the TLS client.
void configClient(TlsContextPtr& ctx) {
    std::string ca(std::string(TEST_CA_DIR) + "/kea-ca.crt");
    std::string cert(std::string(TEST_CA_DIR) + "/kea-client.crt");
    std::string key(std::string(TEST_CA_DIR) + "/kea-client.key");
    TlsContext::configure(ctx, TlsRole::CLIENT, ca, cert, key, true);
}

/// @brief Configure another TLS client.
void configOther(TlsContextPtr& ctx) {
    std::string ca(std::string(TEST_CA_DIR) + "/kea-ca.crt");
    std::string cert(std::string(TEST_CA_DIR) + "/kea-other.crt");
    std::string key(std::string(TEST_CA_DIR) + "/kea-other.key");
    TlsContext::configure(ctx, TlsRole::CLIENT, ca, cert, key, true);
}

/// @brief Configure self-signed TLS client.
void configSelf(TlsContextPtr& ctx) {
    std::string ca(std::string(TEST_CA_DIR) + "/kea-ca.crt");
    std::string cert(std::string(TEST_CA_DIR) + "/kea-self.crt");
    std::string key(std::string(TEST_CA_DIR) + "/kea-self.key");
    TlsContext::configure(ctx, TlsRole::CLIENT, ca, cert, key, true);
}

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc
