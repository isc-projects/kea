// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/crypto_tls.h>
#include <asiolink/botan_tls.h>
#include <asiolink/openssl_tls.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/testutils/test_tls.h>
#include <testutils/gtest_utils.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#ifdef WITH_OPENSSL
#include <openssl/opensslv.h>
#endif

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::cryptolink;
using namespace std;

// Test if we can get a client context.
TEST(TLSTest, clientContext) {
    TlsContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new TlsContext(TlsRole::CLIENT)));
}

// Test if we can get a server context.
TEST(TLSTest, serverContext) {
    TlsContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new TlsContext(TlsRole::SERVER)));
}

// Test if the cert required flag is handled as expected.
TEST(TLSTest, certRequired) {
    auto check = [] (TlsContext& ctx) -> bool {
#ifdef WITH_BOTAN
        // Implement it.
        return (ctx.getCertRequired());
#else // WITH_OPENSSL
        ::SSL_CTX* ssl_ctx = ctx.getNativeContext();
        if (!ssl_ctx) {
            ADD_FAILURE() << "null SSL_CTX";
            return (false);
        }
        int mode = SSL_CTX_get_verify_mode(ssl_ctx);
        switch (mode) {
        case SSL_VERIFY_NONE:
            return (false);
        case (SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT):
            return (true);
        default:
            ADD_FAILURE() << "unknown ssl_verify_mode: " << mode;
            return (false);
        }
#endif
    };

    TlsContext ctx(TlsRole::CLIENT);
    EXPECT_TRUE(ctx.getCertRequired());
    EXPECT_TRUE(check(ctx));
    ASSERT_NO_THROW(ctx.setCertRequired(false));
    EXPECT_FALSE(ctx.getCertRequired());
    EXPECT_FALSE(check(ctx));
    ASSERT_NO_THROW(ctx.setCertRequired(true));
    EXPECT_TRUE(ctx.getCertRequired());
    EXPECT_TRUE(check(ctx));
}

// Test if the certificate authority can be loaded.
TEST(TLSTest, loadCAFile) {
    string ca(string(TEST_CA_DIR) + "/kea-ca.crt");
    TlsContext ctx(TlsRole::CLIENT);
    ASSERT_NO_THROW(ctx.loadCaFile(ca));
}

// Test that no certificate authority gives an error.
TEST(TLSTest, loadNoCAFile) {
    string ca("/no-such-file");
    TlsContext ctx(TlsRole::CLIENT);
    EXPECT_THROW_MSG(ctx.loadCaFile(ca), LibraryError,
                     "No such file or directory");
}

#ifdef WITH_BOTAH
// Test that a directory can't be loaded with Botan.
TEST(TLSTest, loadCAPath) {
    string ca(TEST_CA_DIR);
    TlsContext ctx(TlsRole::CLIENT);
    EXPECT_THROW(ctx.loadCaPath(ca), NotImplemented);
}
#else // WITH_OPENSSL
// Test that a directory can be loaded.
TEST(TLSTest, loadCAPath) {
    string ca(TEST_CA_DIR);
    TlsContext ctx(TlsRole::CLIENT);
    ASSERT_NO_THROW(ctx.loadCaPath(ca));
}
#endif

// Test that a certificate is wanted.
TEST(TLSTest, loadKeyCA) {
    string ca(string(TEST_CA_DIR) + "/kea-ca.key");
    TlsContext ctx(TlsRole::CLIENT);
#ifdef WITH_OPENSSL
#if defined(LIBRESSL_VERSION_NUMBER) || (OPENSSL_VERSION_NUMBER >= 0x10100000L)
    EXPECT_THROW_MSG(ctx.loadCaFile(ca), LibraryError,
                     "no certificate or crl found");
#endif
#endif
}

// Test if the end entity certificate can be loaded.
TEST(TLSTest, loadCertFile) {
    string cert(string(TEST_CA_DIR) + "/kea-client.crt");
    TlsContext ctx(TlsRole::CLIENT);
    ASSERT_NO_THROW(ctx.loadCertFile(cert));
}

// Test that no end entity certificate gives an error.
TEST(TLSTest, loadNoCertFile) {
    string cert("/no-such-file");
    TlsContext ctx(TlsRole::CLIENT);
    EXPECT_THROW_MSG(ctx.loadCertFile(cert), LibraryError,
                     "No such file or directory");
}

// Test that a certificate is wanted.
TEST(TLSTest, loadCsrCertFile) {
    string cert(string(TEST_CA_DIR) + "/kea-client.csr");
    TlsContext ctx(TlsRole::CLIENT);
    EXPECT_THROW_MSG(ctx.loadCertFile(cert), LibraryError,
                     "no start line");
}

// Test if the private key can be loaded.
TEST(TLSTest, loadKeyFile) {
    string key(string(TEST_CA_DIR) + "/kea-client.key");
    TlsContext ctx(TlsRole::CLIENT);
    ASSERT_NO_THROW(ctx.loadKeyFile(key));
}

// Test that no private key gives an error.
TEST(TLSTest, loadNoKeyFile) {
    string key("/no-such-file");
    TlsContext ctx(TlsRole::CLIENT);
    EXPECT_THROW_MSG(ctx.loadKeyFile(key), LibraryError,
                     "No such file or directory");
}

// Test that a private key is wanted.
TEST(TLSTest, loadCertKeyFile) {
    string key(string(TEST_CA_DIR) + "/kea-client.crt");
    TlsContext ctx(TlsRole::CLIENT);
    EXPECT_THROW_MSG(ctx.loadKeyFile(key), LibraryError,
                     "no start line");
}

// Test that the certificate and private key must match.
TEST(TLSTest, loadMismatch) {
    string cert(string(TEST_CA_DIR) + "/kea-server.crt");
    TlsContext ctx(TlsRole::SERVER);
    EXPECT_NO_THROW(ctx.loadCertFile(cert));
    string key(string(TEST_CA_DIR) + "/kea-client.key");
    // In fact OpenSSL checks only RSA key values...
    // The explicit check function is SSL_CTX_check_private_key.
    EXPECT_THROW_MSG(ctx.loadKeyFile(key), LibraryError,
                     "key values mismatch");
}

// Test the configure class method.
TEST(TLSTest, configure) {
    TlsContextPtr ctx;
    string ca(string(TEST_CA_DIR) + "/kea-ca.crt");
    string cert(string(TEST_CA_DIR) + "/kea-client.crt");
    string key(string(TEST_CA_DIR) + "/kea-client.key");
    EXPECT_NO_THROW(TlsContext::configure(ctx, TlsRole::CLIENT,
                                          ca, cert, key, true));
    ASSERT_TRUE(ctx);
    EXPECT_EQ(TlsRole::CLIENT, ctx->getRole());
    EXPECT_TRUE(ctx->getCertRequired());

#ifdef WITH_OPENSSL
    // Retry using the directory and the server.
    ca = TEST_CA_DIR;
    cert = string(TEST_CA_DIR) + "/kea-server.crt";
    key = string(TEST_CA_DIR) + "/kea-server.key";
    EXPECT_NO_THROW(TlsContext::configure(ctx, TlsRole::SERVER,
                                          ca, cert, key, false));
    ASSERT_TRUE(ctx);
    EXPECT_EQ(TlsRole::SERVER, ctx->getRole());
    EXPECT_FALSE(ctx->getCertRequired());

#endif

    // The error case.
    cert = "/no-such-file";
    key = string(TEST_CA_DIR) + "/kea-client.key";
    EXPECT_THROW_MSG(TlsContext::configure(ctx, TlsRole::CLIENT,
                                           ca, cert, key, true),
                     LibraryError,
                     "No such file or directory");
    // The context is reseted on errors.
    EXPECT_FALSE(ctx);
}

// Define a callback class.
namespace { // anonymous namespace.

/// @brief Local server address used for testing.
const char SERVER_ADDRESS[] = "127.0.0.1";

/// @brief Local server port used for testing.
const unsigned short SERVER_PORT = 18123;

/// @brief Class of test callbacks.
class Callback {
public:
    /// @brief State part.
    class State {
    public:
        /// @brief Constructor.
        State() : called_(false), error_code_() {
        }

        /// @brief Destructor.
        virtual ~State() {
        }

        /// @brief Called flag.
        ///
        /// Initialized to false, set to true when the callback is called.
        bool called_;

        /// @brief Last error code.
        boost::system::error_code error_code_;
    };

    /// @brief Constructor.
    ///
    /// Used to shared pointer to state to allow the callback object to
    /// be copied keeping the state member values.
    Callback() : state_(new State()) {
    }

    /// @brief Destructor.
    virtual ~Callback() {
    }

    /// @brief Callback function (one argument).
    ///
    /// @parame ec Boost completion code.
    void operator()(const boost::system::error_code& ec) {
        state_->called_ = true;
        state_->error_code_ = ec;
    }

    /// @brief Callback function (two arguments).
    ///
    /// @parame ec Boost completion code.
    void operator()(const boost::system::error_code& ec, size_t) {
        state_->called_ = true;
        state_->error_code_ = ec;
    }

    /// @brief Get called value.
    inline bool getCalled() const {
        return (state_->called_);
    }

    /// @brief Get error code.
    inline const boost::system::error_code& getCode() const {
        return (state_->error_code_);
    }

protected:
    /// @brief Pointer to state.
    boost::shared_ptr<State> state_;
};

} // end of anonymous namespace.

// Test if we can get a stream.
TEST(TLSTest, stream) {
    IOService service;
    TlsContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new TlsContext(TlsRole::CLIENT)));
    boost::scoped_ptr<TlsStream<Callback> > st;
    ASSERT_NO_THROW(st.reset(new TlsStream<Callback>(service, ctx)));
}

namespace { // anonymous namespace.
} // end of anonymous namespace.

// Test what happens when handshake is forgotten.
TEST(TLSTest, noHandshake) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<Callback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    Callback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<Callback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    Callback connect_cb;
    client.lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        service.run_one();
    }

    // Verify the error codes.
    if (accept_cb.getCode()) {
        FAIL() << "accept error " << accept_cb.getCode().value()
               << " '" << accept_cb.getCode().message() << "'";
    }
    // Possible EINPROGRESS for the client.
    if (connect_cb.getCode() &&
        (connect_cb.getCode().value() != EINPROGRESS)) {
        FAIL() << "connect error " << connect_cb.getCode().value()
               << " '" << connect_cb.getCode().message() << "'";
    }

    // Send on the client.
    char send_buf[] = "some text...";
    Callback send_cb;
    async_write(client, boost::asio::buffer(send_buf), send_cb);
    while (!send_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(send_cb.getCode());
    EXPECT_EQ("uninitialized", send_cb.getCode().message());

    // Receive on the server.
    vector<char> receive_buf(64);
    Callback receive_cb;
    server.async_read_some(boost::asio::buffer(receive_buf), receive_cb);
    while (!receive_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(receive_cb.getCode());
    EXPECT_EQ("uninitialized", receive_cb.getCode().message());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the server was not configured.
TEST(TLSTest, serverNotConfigured) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    // Skip config.
    TlsStream<Callback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    Callback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<Callback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    Callback connect_cb;
    client.lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        service.run_one();
    }

    // Verify the error codes.
    if (accept_cb.getCode()) {
        FAIL() << "accept error " << accept_cb.getCode().value()
               << " '" << accept_cb.getCode().message() << "'";
    }
    // Possible EINPROGRESS for the client.
    if (connect_cb.getCode() &&
        (connect_cb.getCode().value() != EINPROGRESS)) {
        FAIL() << "connect error " << connect_cb.getCode().value()
               << " '" << connect_cb.getCode().message() << "'";
    }

    // Perform TLS handshakes.
    Callback server_cb;
    server.handshake(server_cb);
    Callback client_cb;
    client.handshake(client_cb);
    while (!server_cb.getCalled() || !client_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(server_cb.getCode());
#ifndef LIBRESSL_VERSION_NUMBER
    string server_expected("no shared cipher");
#else
    string server_expected("sslv3 alert handshake failure");
#endif
    EXPECT_EQ(server_expected, server_cb.getCode().message());
    EXPECT_TRUE(client_cb.getCode());
    EXPECT_EQ("sslv3 alert handshake failure", client_cb.getCode().message());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client was not configured.
TEST(TLSTest, clientNotConfigured) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<Callback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    Callback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx(new TlsContext(TlsRole::CLIENT));
    // Skip config.
    TlsStream<Callback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    Callback connect_cb;
    client.lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        service.run_one();
    }

    // Verify the error codes.
    if (accept_cb.getCode()) {
        FAIL() << "accept error " << accept_cb.getCode().value()
               << " '" << accept_cb.getCode().message() << "'";
    }
    // Possible EINPROGRESS for the client.
    if (connect_cb.getCode() &&
        (connect_cb.getCode().value() != EINPROGRESS)) {
        FAIL() << "connect error " << connect_cb.getCode().value()
               << " '" << connect_cb.getCode().message() << "'";
    }

    // Perform TLS handshakes.
    Callback server_cb;
    server.async_handshake(ssl::stream_base::server, server_cb);
    Callback client_cb;
    client.async_handshake(ssl::stream_base::client, client_cb);
    while (!server_cb.getCalled() || !client_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(server_cb.getCode());
    EXPECT_EQ("tlsv1 alert unknown ca", server_cb.getCode().message());
    EXPECT_TRUE(client_cb.getCode());
#ifndef LIBRESSL_VERSION_NUMBER
    string client_expected("certificate verify failed");
#else
    string client_expected("tlsv1 alert unknown ca");
#endif
    EXPECT_EQ(client_expected, client_cb.getCode().message());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client is HTTP (vs HTTPS).
TEST(TLSTest, clientHTTPnoS) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<Callback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    Callback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(service.get_io_service());

    // Connect to.
    client.open(tcp::v4());
    Callback connect_cb;
    client.async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        service.run_one();
    }

    // Verify the error codes.
    if (accept_cb.getCode()) {
        FAIL() << "accept error " << accept_cb.getCode().value()
               << " '" << accept_cb.getCode().message() << "'";
    }
    // Possible EINPROGRESS for the client.
    if (connect_cb.getCode() &&
        (connect_cb.getCode().value() != EINPROGRESS)) {
        FAIL() << "connect error " << connect_cb.getCode().value()
               << " '" << connect_cb.getCode().message() << "'";
    }

    // Perform server TLS handshake.
    Callback server_cb;
    server.async_handshake(ssl::stream_base::server, server_cb);

    // Client sending a HTTP GET.
    char send_buf[] = "GET / HTTP/1.1\r\n";
    Callback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!server_cb.getCalled() || !client_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(server_cb.getCode());
#ifndef LIBRESSL_VERSION_NUMBER
    string server_expected("http request");
#else
    string server_expected("tlsv1 alert protocol version");
#endif
    EXPECT_EQ(server_expected, server_cb.getCode().message());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client does not use HTTP nor HTTP.
TEST(TLSTest, unknownClient) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<Callback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    Callback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(service.get_io_service());

    // Connect to.
    client.open(tcp::v4());
    Callback connect_cb;
    client.async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        service.run_one();
    }

    // Verify the error codes.
    if (accept_cb.getCode()) {
        FAIL() << "accept error " << accept_cb.getCode().value()
               << " '" << accept_cb.getCode().message() << "'";
    }
    // Possible EINPROGRESS for the client.
    if (connect_cb.getCode() &&
        (connect_cb.getCode().value() != EINPROGRESS)) {
        FAIL() << "connect error " << connect_cb.getCode().value()
               << " '" << connect_cb.getCode().message() << "'";
    }

    // Perform server TLS handshake.
    Callback server_cb;
    server.async_handshake(ssl::stream_base::server, server_cb);

    // Client sending something which is not a TLS ClientHello.
    char send_buf[] = "hello my server...";
    Callback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!server_cb.getCalled() || !client_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(server_cb.getCode());
#ifdef WITH_OPENSSL
#ifndef LIBRESSL_VERSION_NUMBER
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L)
    string server_expected("wrong version number");
#else
    string server_expected("unknown protocol");
#endif
#else
    string server_expected("tlsv1 alert protocol version");
#endif
#endif
    EXPECT_EQ(server_expected, server_cb.getCode().message());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client uses a certificate from another CA.
TEST(TLSTest, anotherClient) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<Callback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    Callback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a certificate signed by another CA.
    TlsContextPtr client_ctx;
    test::configOther(client_ctx);
    TlsStream<Callback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    Callback connect_cb;
    client.lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        service.run_one();
    }

    // Verify the error codes.
    if (accept_cb.getCode()) {
        FAIL() << "accept error " << accept_cb.getCode().value()
               << " '" << accept_cb.getCode().message() << "'";
    }
    // Possible EINPROGRESS for the client.
    if (connect_cb.getCode() &&
        (connect_cb.getCode().value() != EINPROGRESS)) {
        FAIL() << "connect error " << connect_cb.getCode().value()
               << " '" << connect_cb.getCode().message() << "'";
    }

    // Perform TLS handshakes.
    Callback server_cb;
    server.async_handshake(ssl::stream_base::server, server_cb);
    Callback client_cb;
    client.async_handshake(ssl::stream_base::client, client_cb);
    while (!server_cb.getCalled() || !client_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(server_cb.getCode());
    // Full error is:
    // error 20 at 0 depth lookup:unable to get local issuer certificate
#ifdef WITH_OPENSSL
#ifndef LIBRESSL_VERSION_NUMBER
    string server_expected("certificate verify failed");
#else
    string server_expected("tlsv1 alert unknown ca");
#endif
    EXPECT_EQ(server_expected, server_cb.getCode().message());
#if defined(LIBRESSL_VERSION_NUMBER) || (OPENSSL_VERSION_NUMBER >= 0x10100000L)
    EXPECT_FALSE(client_cb.getCode());
#endif
#endif

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client uses a self-signed certificate.
TEST(TLSTest, selfSigned) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<Callback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    Callback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a self-signed certificate.
    TlsContextPtr client_ctx;
    test::configSelf(client_ctx);
    TlsStream<Callback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    Callback connect_cb;
    client.lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        service.run_one();
    }

    // Verify the error codes.
    if (accept_cb.getCode()) {
        FAIL() << "accept error " << accept_cb.getCode().value()
               << " '" << accept_cb.getCode().message() << "'";
    }
    // Possible EINPROGRESS for the client.
    if (connect_cb.getCode() &&
        (connect_cb.getCode().value() != EINPROGRESS)) {
        FAIL() << "connect error " << connect_cb.getCode().value()
               << " '" << connect_cb.getCode().message() << "'";
    }

    // Perform TLS handshakes.
    Callback server_cb;
    server.async_handshake(ssl::stream_base::server, server_cb);
    Callback client_cb;
    client.async_handshake(ssl::stream_base::client, client_cb);
    while (!server_cb.getCalled() || !client_cb.getCalled()) {
        service.run_one();
    }
    EXPECT_TRUE(server_cb.getCode());
    // Full error is:
    // error 18 at 0 depth lookup:self signed certificate
#ifdef WITH_OPENSSL
#ifndef LIBRESSL_VERSION_NUMBER
    string server_expected("certificate verify failed");
#else
    string server_expected("tlsv1 alert unknown ca");
#endif
    EXPECT_EQ(server_expected, server_cb.getCode().message());
#if defined(LIBRESSL_VERSION_NUMBER) || (OPENSSL_VERSION_NUMBER >= 0x10100000L)
    EXPECT_FALSE(client_cb.getCode());
#endif
#endif

    // Used when adding other error cases.
#if 0
    cerr << "server: '" << server_cb.getCode().message() << "'\n";
    cerr << "client: '" << client_cb.getCode().message() << "'\n";
#endif

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}









