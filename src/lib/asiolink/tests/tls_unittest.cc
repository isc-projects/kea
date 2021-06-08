// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>
#include <asiolink/crypto_tls.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/testutils/test_tls.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <cstdlib>
#include <list>
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

namespace { // anonymous namespace.

/// @brief Local server address used for testing.
const char SERVER_ADDRESS[] = "127.0.0.1";

/// @brief Local server port used for testing.
const unsigned short SERVER_PORT = 18123;

/// @brief Name of the environment variable controlling the display
/// (default off) of TLS error messages.
const char KEA_TLS_CHECK_VERBOSE[] = "KEA_TLS_CHECK_VERBOSE";

/// @brief Test TLS context class exposing protected methods.
class TestTlsContext : public TlsContext {
public:
    /// @brief Constructor.
    ///
    /// @param role The TLS role client or server.
    explicit TestTlsContext(TlsRole role) : TlsContext(role) { }

    /// @brief Destructor.
    virtual ~TestTlsContext() { }

    /// @brief Make protected methods visible in tests.
    using TlsContext::setCertRequired;
    using TlsContext::loadCaFile;
    using TlsContext::loadCaPath;
    using TlsContext::loadCertFile;
    using TlsContext::loadKeyFile;
};

/// @brief Class of test callbacks.
class TestCallback {
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
    TestCallback()
        : state_(new State()), tcpp_(0) {
    }

    /// @brief Close on error constructor.
    ///
    /// An overload which takes the stream to close on error.
    ///
    /// @param tcpp Pointer to the stream to close on error.
    TestCallback(TlsStream<TestCallback>::lowest_layer_type* tcpp)
        : state_(new State()), tcpp_(tcpp) {
    }

    /// @brief Destructor.
    virtual ~TestCallback() {
    }

    /// @brief Callback function (one argument).
    ///
    /// @parame ec Boost completion code.
    void operator()(const boost::system::error_code& ec) {
        state_->called_ = true;
        state_->error_code_ = ec;
        if (ec && tcpp_) {
            tcpp_->close();
        }
    }

    /// @brief Callback function (two arguments).
    ///
    /// @parame ec Boost completion code.
    void operator()(const boost::system::error_code& ec, size_t) {
        state_->called_ = true;
        state_->error_code_ = ec;
        if (ec && tcpp_) {
            tcpp_->close();
        }
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

    /// @brief Pointer to the stream to close on error.
    TlsStream<TestCallback>::lowest_layer_type* tcpp_;
};

/// @brief The type of a test to be run.
typedef function<void()> Test;

/// @brief Class of an expected behavior.
///
/// Some TLS tests can not use the standard GTEST macros because they
/// show different behaviors depending on the crypto backend and the
/// boost library versions. Worse in some cases the behavior can not
/// be deduced from them so #ifdef's do not work...
///
/// Until this is adopted / widespread the policy is to use these flexible
/// expected behavior tests ONLY when needed.
class Expected {
private:
    /// Constructor.
    ///
    /// @param throwing True when an exception should be thrown.
    /// @param timeout True when a timeout should occur.
    /// @param no_error True when no error should be returned.
    /// @param message Expected message.
    Expected(bool throwing, bool timeout, bool no_error,
             const string& message)
        : throwing_(throwing), timeout_(timeout), no_error_(no_error),
          message_(message) {
    }

    /// @brief The throwing flag.
    bool throwing_;

    /// @brief The timeout flag.
    bool timeout_;

    /// @brief The no error flag.
    bool no_error_;

    /// @brief The expected error message.
    string message_;

public:
    /// @brief Create an expected throwing exception behavior.
    ///
    /// @param message Expected message.
    static Expected createThrow(const string& message) {
        return (Expected(true, false, false, message));
    }

    /// @brief Create an expected timeout behavior.
    static Expected createTimeout() {
        return (Expected(false, true, false, ""));
    }

    /// @brief Create an expected no error behavior.
    static Expected createNoError() {
        return (Expected(false, false, true, ""));
    }

    /// @brief Create an expected error message behavior.
    ///
    /// @param message Expected message.
    static Expected createError(const string& message) {
        return (Expected(false, false, false, message));
    }

    /// @brief Get the throwing flag.
    ///
    /// @return The throwing flag.
    bool getThrow() const {
        return (throwing_);
    }

    /// @brief Get the timeout flag.
    ///
    /// @return The timeout flag.
    bool getTimeout() const {
        return (timeout_);
    }

    /// @brief Get the no error flag.
    ///
    /// @return The no error flag.
    bool getNoError() const {
        return (no_error_);
    }

    /// @brief Get the expected error message.
    ///
    /// @return The expected error message.
    const string& getMessage() const {
        return (message_);
    }
};

/// @brief Class of expected behaviors.
class Expecteds {
private:
    /// @brief List of expected behaviors.
    list<Expected> list_;

    /// @brief The error message for the verbose mode.
    string errmsg_;

public:
    /// Constructor.
    ///
    /// @return An empty expected behavior list.
    Expecteds() : list_(), errmsg_("") {
    }

    /// @brief Clear the list.
    void clear() {
        list_.clear();
        errmsg_.clear();
    }

    /// @brief Add an expected throwing exception behavior.
    ///
    /// @param message Expected message.
    void addThrow(const string& message) {
        list_.push_back(Expected::createThrow(message));
    }

    /// @brief Add an expected timeout behavior.
    void addTimeout() {
        list_.push_back(Expected::createTimeout());
    }

    /// @brief Add an expected no error behavior.
    void addNoError() {
        list_.push_back(Expected::createNoError());
    }

    /// @brief Add an expected error message behavior.
    ///
    /// @param message Expected message.
    void addError(const string& message) {
        list_.push_back(Expected::createError(message));
    }

    /// @brief Display error messages.
    ///
    /// @return True if error messages are displayed.
    static bool displayErrMsg() {
        return (getenv(KEA_TLS_CHECK_VERBOSE));
    }

    /// @brief Has an error message.
    ///
    /// @return True when there is a cached error message.
    bool hasErrMsg() const {
        return (!errmsg_.empty());
    }

    /// @brief Get error message.
    ///
    /// @return The cached error message.
    const string& getErrMsg() const {
        return (errmsg_);
    }

    /// @brief Run a test which can throw.
    ///
    /// @param test The test to run.
    void runCanThrow(const Test& test) {
        // Check consistency.
        for (auto const& exp : list_) {
            if (!exp.getThrow() && !exp.getNoError()) {
                ADD_FAILURE() << "inconsistent runCanThrow settings";
            }
        }

        // Collect the test behavior.
        bool thrown = false;
        try {
            test();
        } catch (const LibraryError& ex) {
            thrown = true;
            errmsg_ = ex.what();
        } catch (const isc::BadValue& ex) {
            thrown = true;
            errmsg_ = ex.what();
        } catch (const exception& ex) {
            thrown = true;
            errmsg_ = ex.what();
            ADD_FAILURE() << "expect only LibraryError or BadValue exception";
        }

        // Check the no error case.
        if (!thrown) {
            for (auto const& exp : list_) {
                if (exp.getNoError()) {
                    // No error was expected: good.
                    return;
                }
            }
            // No error was not expected: bad.
            ADD_FAILURE() << "no exception?";
            return;
        }

        // Check the thrown message.
        for (auto const& exp : list_) {
            if (!exp.getThrow()) {
                continue;
            }
            if (errmsg_ == exp.getMessage()) {
                // Got an expected message: good.
                return;
            }
        }
        // The message was not expected: bad.
        ADD_FAILURE() << "exception with unknown '" << errmsg_ << "'";
    }

    /// @brief Check the result of an asynchronous operation.
    ///
    /// @param party The name of the party.
    /// @param callback The test callback of the an asynchronous.
    void checkAsync(const string& party, const TestCallback& callback) {
        // Check timeout i.e. the callback was not called.
        if (!callback.getCalled()) {
            bool expected = false;
            for (auto const& exp : list_) {
                if (exp.getTimeout()) {
                    expected = true;
                    break;
                }
            }
            if (!expected) {
                ADD_FAILURE() << "unexpected timeout";
            }
        }

        // Check the no error case.
        const boost::system::error_code& ec = callback.getCode();
        if (!ec) {
            for (auto const& exp : list_) {
                if (exp.getTimeout() || exp.getNoError()) {
                    // Expected timeout or no error: good.
                    return;
                }
            }
            // Should have failed but did not: bad.
            ADD_FAILURE() << party << " did not failed as expected";
            return;
        }

        // Got an error but was this one expected?
        errmsg_ = ec.message();
        for (auto const& exp : list_) {
            if (exp.getTimeout() || exp.getNoError()) {
                continue;
            }
            if (errmsg_ == exp.getMessage()) {
                // This error message was expected: good.
                return;
            }
        }
        ADD_FAILURE() << party << " got unexpected error '" << errmsg_ << "'";
    }

};

////////////////////////////////////////////////////////////////////////
//                              TlsContext tests                      //
////////////////////////////////////////////////////////////////////////

// Test if we can get a client context.
TEST(TLSTest, clientContext) {
    TlsContextPtr ctx;
    EXPECT_NO_THROW(ctx.reset(new TlsContext(TlsRole::CLIENT)));
}

// Test if we can get a server context.
TEST(TLSTest, serverContext) {
    TlsContextPtr ctx;
    EXPECT_NO_THROW(ctx.reset(new TlsContext(TlsRole::SERVER)));
}

// Test if the cert required flag is handled as expected.
TEST(TLSTest, certRequired) {
    auto check = [] (TlsContext& ctx) -> bool {
#ifdef WITH_BOTAN
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

    TestTlsContext ctx(TlsRole::SERVER);
    EXPECT_TRUE(ctx.getCertRequired());
    EXPECT_TRUE(check(ctx));
    ASSERT_NO_THROW(ctx.setCertRequired(false));
    EXPECT_FALSE(ctx.getCertRequired());
    EXPECT_FALSE(check(ctx));
    ASSERT_NO_THROW(ctx.setCertRequired(true));
    EXPECT_TRUE(ctx.getCertRequired());
    EXPECT_TRUE(check(ctx));

    // Client role is different so test it too.
    TestTlsContext cctx(TlsRole::CLIENT);
    EXPECT_TRUE(cctx.getCertRequired());
    EXPECT_TRUE(check(cctx));
    ASSERT_NO_THROW(cctx.setCertRequired(true));
    EXPECT_TRUE(cctx.getCertRequired());
    EXPECT_TRUE(check(cctx));
    EXPECT_THROW(cctx.setCertRequired(false), isc::BadValue);
}

// Test if the certificate authority can be loaded.
TEST(TLSTest, loadCAFile) {
    string ca(string(TEST_CA_DIR) + "/kea-ca.crt");
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadCaFile(ca));
}

// Test that no certificate authority gives an error.
TEST(TLSTest, loadNoCAFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("I/O error: DataSource: Failure opening file /no-such-file");
    // OpenSSL error.
    exps.addThrow("No such file or directory");
    exps.runCanThrow([] {
        string ca("/no-such-file");
        TestTlsContext ctx(TlsRole::CLIENT);
        ctx.loadCaFile(ca);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}

#ifdef WITH_BOTAN
// Test that Botan requires a real CA certificate so fails with
// trusted self-signed client.
/// @note: convert to GTEST when gtest_utils.h will be moved.
TEST(TLSTest, loadTrustedSelfCAFile) {
    Expecteds exps;
    // Botan error.
    string botan_error = "Flatfile_Certificate_Store received non CA cert ";
    botan_error += "C=\"US\",X520.State=\"Some-State\",O=\"ISC Inc.\",";
    botan_error += "CN=\"kea-self\"";
    exps.addThrow(botan_error);
    exps.runCanThrow([] {
        string ca(string(TEST_CA_DIR) + "/kea-self.crt");
        TestTlsContext ctx(TlsRole::CLIENT);
        ctx.loadCaFile(ca);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}
#endif // WITH_BOTAN

// Test that a directory can be loaded.
TEST(TLSTest, loadCAPath) {
    string ca(TEST_CA_DIR);
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadCaPath(ca));
}

// Test that a certificate is wanted.
TEST(TLSTest, loadKeyCA) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("Flatfile_Certificate_Store::Flatfile_Certificate_Store cert file is empty");
    // LibreSSL or old OpenSSL does not check.
    exps.addNoError();
    // Recent OpenSSL error.
    exps.addThrow("no certificate or crl found");
    exps.runCanThrow([] {
        string ca(string(TEST_CA_DIR) + "/kea-ca.key");
        TestTlsContext ctx(TlsRole::CLIENT);
        ctx.loadCaFile(ca);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}

// Test if the end entity certificate can be loaded.
TEST(TLSTest, loadCertFile) {
    string cert(string(TEST_CA_DIR) + "/kea-client.crt");
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadCertFile(cert));
}

// Test that no end entity certificate gives an error.
TEST(TLSTest, loadNoCertFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("I/O error: DataSource: Failure opening file /no-such-file");
    // OpenSSL error.
    exps.addThrow("No such file or directory");
    exps.runCanThrow([] {
        string cert("/no-such-file");
        TestTlsContext ctx(TlsRole::CLIENT);
        ctx.loadCertFile(cert);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}

// Test that a certificate is wanted.
TEST(TLSTest, loadCsrCertFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("Expected a certificate, got 'CERTIFICATE REQUEST'");
    // OpenSSL error.
    exps.addThrow("no start line");
    exps.runCanThrow([] {
        string cert(string(TEST_CA_DIR) + "/kea-client.csr");
        TestTlsContext ctx(TlsRole::CLIENT);
        ctx.loadCertFile(cert);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}

// Test if the private key can be loaded.
TEST(TLSTest, loadKeyFile) {
    string key(string(TEST_CA_DIR) + "/kea-client.key");
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadKeyFile(key));
}

// Test that no private key gives an error.
TEST(TLSTest, loadNoKeyFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("I/O error: DataSource: Failure opening file /no-such-file");
    // OpenSSL error.
    exps.addThrow("No such file or directory");
    // Another possible error.
    exps.addThrow("PEM lib");
    exps.runCanThrow([] {
        string key("/no-such-file");
        TestTlsContext ctx(TlsRole::CLIENT);
        ctx.loadKeyFile(key);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}

// Test that a private key is wanted.
TEST(TLSTest, loadCertKeyFile) {
    Expecteds exps;
    // Botan error.
    string botan_error = "PKCS #8 private key decoding failed with PKCS #8: ";
    botan_error += "Unknown PEM label CERTIFICATE";
    exps.addThrow(botan_error);
    // OpenSSL error.
    exps.addThrow("no start line");
    // Another possible error.
    exps.addThrow("No such file or directory");
    exps.runCanThrow([] {
        string key(string(TEST_CA_DIR) + "/kea-client.crt");
        TestTlsContext ctx(TlsRole::CLIENT);
        ctx.loadKeyFile(key);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}

// Test that the certificate and private key must match.
TEST(TLSTest, loadMismatch) {
    Expecteds exps;
    exps.addNoError();
    exps.runCanThrow([] {
        string cert(string(TEST_CA_DIR) + "/kea-server.crt");
        TestTlsContext ctx(TlsRole::SERVER);
        ctx.loadCertFile(cert);
    });
    // Keep no error for at least Botan.
    // OpenSSL error.
    exps.addThrow("key values mismatch");
    exps.runCanThrow([] {
        string key(string(TEST_CA_DIR) + "/kea-client.key");
        TestTlsContext ctx(TlsRole::SERVER);
        // In fact OpenSSL checks only RSA key values...
        // The explicit check function is SSL_CTX_check_private_key.
        ctx.loadKeyFile(key);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
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

    // Retry using the directory and the server.
    ctx.reset();
    ca = TEST_CA_DIR;
    cert = string(TEST_CA_DIR) + "/kea-server.crt";
    key = string(TEST_CA_DIR) + "/kea-server.key";
    EXPECT_NO_THROW(TlsContext::configure(ctx, TlsRole::SERVER,
                                          ca, cert, key, false));
    ASSERT_TRUE(ctx);
    EXPECT_EQ(TlsRole::SERVER, ctx->getRole());
    EXPECT_FALSE(ctx->getCertRequired());
}

// Test the configure class method error case.
TEST(TLSTest, configureError) {
    // The error case.
    Expecteds exps;
    // Common part of the error message.
    string common_error = "load of cert file '/no-such-file' failed: ";
    // Botan error.
    string botan_error = "I/O error: DataSource: Failure opening file /no-such-file";
    exps.addThrow(common_error + botan_error);
    // OpenSSL error.
    string openssl_error = "No such file or directory";
    exps.addThrow(common_error + openssl_error);
    exps.runCanThrow([] {
        TlsContextPtr ctx1;
        string ca(string(TEST_CA_DIR) + "/kea-ca.crt");
        string cert = "/no-such-file";
        string key = string(TEST_CA_DIR) + "/kea-client.key";
        TlsContext::configure(ctx1, TlsRole::CLIENT,
                              ca, cert, key, true);
        // The context is reset on errors.
        EXPECT_FALSE(ctx1);
    });
    if (Expecteds::displayErrMsg()) {
        std::cout << exps.getErrMsg() << "\n";
    }
}

////////////////////////////////////////////////////////////////////////
//                      Basic handshake failures                      //
////////////////////////////////////////////////////////////////////////

// Test if we can get a stream.
TEST(TLSTest, stream) {
    IOService service;
    TlsContextPtr ctx(new TlsContext(TlsRole::CLIENT));
    boost::scoped_ptr<TlsStream<TestCallback> > st;
    EXPECT_NO_THROW(st.reset(new TlsStream<TestCallback>(service, ctx)));
}

// Test what happens when handshake is forgotten.
TEST(TLSTest, noHandshake) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer1(service);
    bool timeout = false;
    timer1.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Send on the client.
    char send_buf[] = "some text...";
    TestCallback send_cb;
    async_write(client, boost::asio::buffer(send_buf), send_cb);
    while (!timeout && !send_cb.getCalled()) {
        service.run_one();
    }
    timer1.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("InvalidObjectState");
    // OpenSSL error.
    exps.addError("uninitialized");
    exps.checkAsync("send", send_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "send: " << exps.getErrMsg() << "\n";
    }

    // Setup a second timeout.
    IntervalTimer timer2(service);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server.async_read_some(boost::asio::buffer(receive_buf), receive_cb);
    while (!timeout && !receive_cb.getCalled()) {
        service.run_one();
    }
    timer2.cancel();

    exps.clear();
    // On Botan and some OpenSSL the receive party hangs.
    exps.addTimeout();
    // OpenSSL error,
    exps.addError("uninitialized");
    exps.checkAsync("receive", receive_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "receive timeout\n";
        } else {
            std::cout << "receive: " << exps.getErrMsg() << "\n";
        }
    }

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
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.handshake(server_cb);
    TestCallback client_cb;
    client.handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("handshake_failure");
    // LibreSSL error.
    exps.addError("no shared cipher");
    // OpenSSL error.
    exps.addError("sslv3 alert handshake failure");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // On Botan and some OpenSSL the client hangs.
    exps.addTimeout();
    // OpenSSL error.
    exps.addError("sslv3 alert handshake failure");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "client timeout\n";
        } else {
            std::cout << "client: " << exps.getErrMsg() << "\n";
        }
    }

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
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx(new TlsContext(TlsRole::CLIENT));
    // Skip config.
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // On Botan and some OpenSSL the server hangs.
    exps.addTimeout();
    // OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "server timeout\n";
        } else {
            std::cout << "server: " << exps.getErrMsg() << "\n";
        }
    }

    exps.clear();
    // Botan error (unfortunately a bit generic).
    exps.addError("bad_certificate");
    // LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL error.
    exps.addError("certificate verify failed");
    // The client should not hang.
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

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
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(service.get_io_service());

    // Connect to.
    client.open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform server TLS handshake.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);

    // Client sending a HTTP GET.
    char send_buf[] = "GET / HTTP/1.1\r\n";
    TestCallback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan server hangs before 2.18.
    exps.addTimeout();
    // Botan error.
    exps.addError("protocol_version");
    // LibreSSL error.
    exps.addError("tlsv1 alert protocol version");
    // OpenSSL error (OpenSSL recognizes HTTP).
    exps.addError("http request");
    // Another OpenSSL error (not all OpenSSL recognizes HTTP).
    exps.addError("wrong version number");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "server timeout\n";
        } else {
            std::cout << "server: " << exps.getErrMsg() << "\n";
        }
    }

    // No error at the client.
    EXPECT_TRUE(client_cb.getCalled());
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
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(service.get_io_service());

    // Connect to.
    client.open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform server TLS handshake.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);

    // Client sending something which is not a TLS ClientHello.
    char send_buf[] = "hello my server...";
    TestCallback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan errors.
    exps.addError("record_overflow");
    exps.addError("protocol_version");
    // LibreSSL error.
    exps.addError("tlsv1 alert protocol version");
    // Old OpenSSL error.
    exps.addError("unknown protocol");
    // Recent OpenSSL error.
    exps.addError("wrong version number");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    // No error on the client side.
    EXPECT_TRUE(client_cb.getCalled());
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
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a certificate signed by another CA.
    TlsContextPtr client_ctx;
    test::configOther(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL error.
    // Full error is:
    // error 20 at 0 depth lookup:unable to get local issuer certificate
    exps.addError("certificate verify failed");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan client hangs.
    exps.addTimeout();
    // LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "client timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "client: " << exps.getErrMsg() << "\n";
        }
    }

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
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a self-signed certificate.
    TlsContextPtr client_ctx;
    test::configSelf(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL error.
    // Full error is:
    // error 18 at 0 depth lookup:self signed certificate
    exps.addError("certificate verify failed");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan client hangs.
    exps.addTimeout();
    // LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "client timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "client: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

////////////////////////////////////////////////////////////////////////
//                  Close on error handshake failures                 //
////////////////////////////////////////////////////////////////////////

// Investigate what happens when a peer closes its streams when the
// handshake callback returns an error. In particular does still
// the other peer timeout?

// Test what happens when handshake is forgotten.
TEST(TLSTest, noHandshakeCloseOnError) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer1(service);
    bool timeout = false;
    timer1.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Send on the client.
    char send_buf[] = "some text...";
    TestCallback send_cb(&client.lowest_layer());
    async_write(client, boost::asio::buffer(send_buf), send_cb);
    while (!timeout && !send_cb.getCalled()) {
        service.run_one();
    }
    timer1.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("InvalidObjectState");
    // OpenSSL error.
    exps.addError("uninitialized");
    exps.checkAsync("send", send_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "send: " << exps.getErrMsg() << "\n";
    }

    // Setup a second timeout.
    IntervalTimer timer2(service);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server.async_read_some(boost::asio::buffer(receive_buf), receive_cb);
    while (!timeout && !receive_cb.getCalled()) {
        service.run_one();
    }
    timer2.cancel();

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // OpenSSL error,
    exps.addError("uninitialized");
    exps.checkAsync("receive", receive_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "receive: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the server was not configured.
TEST(TLSTest, serverNotConfiguredCloseonError) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    // Skip config.
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server.lowest_layer());
    server.handshake(server_cb);
    TestCallback client_cb;
    client.handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("handshake_failure");
    // LibreSSL error.
    exps.addError("no shared cipher");
    // OpenSSL error.
    exps.addError("sslv3 alert handshake failure");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // OpenSSL error.
    exps.addError("sslv3 alert handshake failure");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client was not configured.
TEST(TLSTest, clientNotConfiguredCloseonError) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx(new TlsContext(TlsRole::CLIENT));
    // Skip config.
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb(&client.lowest_layer());
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan error (unfortunately a bit generic).
    exps.addError("bad_certificate");
    // LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL error.
    exps.addError("certificate verify failed");
    // The client should not hang.
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client is HTTP (vs HTTPS).
TEST(TLSTest, clientHTTPnoSCloseonError) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(service.get_io_service());

    // Connect to.
    client.open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform server TLS handshake.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);

    // Client sending a HTTP GET.
    char send_buf[] = "GET / HTTP/1.1\r\n";
    TestCallback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan server hangs before 2.18.
    exps.addTimeout();
    // Botan behavior was reported and fixed.
    exps.addError("protocol_version");
    // LibreSSL error.
    exps.addError("tlsv1 alert protocol version");
    // OpenSSL error (OpenSSL recognizes HTTP).
    exps.addError("http request");
    // Another OpenSSL error (not all OpenSSL recognizes HTTP).
    exps.addError("wrong version number");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "server timeout\n";
        } else {
            std::cout << "server: " << exps.getErrMsg() << "\n";
        }
    }

    // No error at the client.
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client uses a certificate from another CA.
TEST(TLSTest, anotherClientCloseonError) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a certificate signed by another CA.
    TlsContextPtr client_ctx;
    test::configOther(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server.lowest_layer());
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL error.
    // Full error is:
    // error 20 at 0 depth lookup:unable to get local issuer certificate
    exps.addError("certificate verify failed");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg() && exps.hasErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the client uses a self-signed certificate.
TEST(TLSTest, selfSignedCloseonError) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a self-signed certificate.
    TlsContextPtr client_ctx;
    test::configSelf(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server.lowest_layer());
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL error.
    // Full error is:
    // error 18 at 0 depth lookup:self signed certificate
    exps.addError("certificate verify failed");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg() && exps.hasErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

////////////////////////////////////////////////////////////////////////
//                      TLS handshake corner case                     //
////////////////////////////////////////////////////////////////////////

// Some special cases.

// Test what happens when the client uses a certificate from another CA
// but the client certificate request and validation are disabled.
TEST(TLSTest, anotherClientNoReq) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServerNoReq(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a certificate signed by another CA.
    TlsContextPtr client_ctx;
    test::configOther(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    // Should not fail.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the server uses a certificate without subject
// alternative name (but still a version 3 certificate).
TEST(TLSTest, serverRaw) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configServerRaw(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    // Should not fail.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

#ifdef WITH_OPENSSL
// Test what happens when the client uses a trusted self-signed certificate.
// Not really a failure case as it works...
TEST(TLSTest, trustedSelfSigned) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx;
    test::configTrustedSelf(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part using a self-signed certificate.
    TlsContextPtr client_ctx;
    test::configSelf(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server.async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client.async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    // It should work for all OpenSSL.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}
#endif // WITH_OPENSSL

////////////////////////////////////////////////////////////////////////
//                              TLS shutdown                          //
////////////////////////////////////////////////////////////////////////

// Investigate the TLS shutdown processing.

// Test what happens when the shutdown receiver is inactive.
TEST(TLSTest, shutdownInactive) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server.lowest_layer());
    server.handshake(server_cb);
    TestCallback client_cb;
    client.handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown.
    IntervalTimer timer2(service);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Shutdown on the client leaving the server inactive.
    TestCallback shutdown_cb;
    client.shutdown(shutdown_cb);
    while (!timeout && !shutdown_cb.getCalled()) {
        service.run_one();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // OpenSSL hangs.
    exps.addTimeout();
    exps.checkAsync("shutdown", shutdown_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "shutdown timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "shutdown: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the shutdown receiver is active.
TEST(TLSTest, shutdownActive) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server.lowest_layer());
    server.handshake(server_cb);
    TestCallback client_cb;
    client.handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown and receive.
    IntervalTimer timer2(service);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server.async_read_some(boost::asio::buffer(receive_buf), receive_cb);

    // Shutdown on the client.
    TestCallback shutdown_cb;
    client.shutdown(shutdown_cb);
    while (!timeout && (!shutdown_cb.getCalled() || !receive_cb.getCalled())) {
        service.run_one();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // OpenSSL hangs.
    exps.addTimeout();
    exps.checkAsync("shutdown", shutdown_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "shutdown timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "shutdown: " << exps.getErrMsg() << "\n";
        }
    }

    exps.clear();
    // End of file on the receive side.
    exps.addError("End of file");
    exps.checkAsync("receive", receive_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "receive: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the shutdown receiver is inactive on shutdown
// and immediate close.
TEST(TLSTest, shutdownCloseInactive) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server.lowest_layer());
    server.handshake(server_cb);
    TestCallback client_cb;
    client.handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown.
    IntervalTimer timer2(service);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Shutdown on the client leaving the server inactive.
    TestCallback shutdown_cb;
    client.shutdown(shutdown_cb);

    // Post a close which should be called after the shutdown.
    service.post([&client] { client.lowest_layer().close(); });
    while (!timeout && !shutdown_cb.getCalled()) {
        service.run_one();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // LibreSSL and some old OpenSSL gets Operation canceled.
    exps.addError("Operation canceled");
    // OpenSSL gets Bad file descriptor.
    exps.addError("Bad file descriptor");
    exps.checkAsync("shutdown", shutdown_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "shutdown timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "shutdown: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Test what happens when the shutdown receiver is active with an
// immediate close.
TEST(TLSTest, shutdownCloseActive) {
    IOService service;

    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    TlsStream<TestCallback> server(service, server_ctx);

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(address::from_string(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(service.get_io_service(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server.lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    TlsStream<TestCallback> client(service, client_ctx);

    // Connect to.
    client.lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
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

    // Setup a timeout.
    IntervalTimer timer(service);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server.lowest_layer());
    server.handshake(server_cb);
    TestCallback client_cb;
    client.handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        service.run_one();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown and receive.
    IntervalTimer timer2(service);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server.async_read_some(boost::asio::buffer(receive_buf), receive_cb);

    // Shutdown on the client.
    TestCallback shutdown_cb;
    client.shutdown(shutdown_cb);

    // Post a close which should be called after the shutdown.
    service.post([&client] { client.lowest_layer().close(); });
    while (!timeout && (!shutdown_cb.getCalled() || !receive_cb.getCalled())) {
        service.run_one();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // LibreSSL and some old OpenSSL gets Operation canceled.
    exps.addError("Operation canceled");
    // OpenSSL gets Bad file descriptor.
    exps.addError("Bad file descriptor");
    exps.checkAsync("shutdown", shutdown_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "shutdown timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "shutdown: " << exps.getErrMsg() << "\n";
        }
    }

    // End of file on the receive side.
    EXPECT_TRUE(receive_cb.getCalled());
    EXPECT_TRUE(receive_cb.getCode());
    EXPECT_EQ("End of file", receive_cb.getCode().message());
    if (Expecteds::displayErrMsg()) {
        std::cout << "receive: " << receive_cb.getCode().message() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server.lowest_layer().close());
}

// Conclusion about the shutdown: do the close on completion (e.g. in the
// handler) or on timeout (i.e. simulate an asynchronous shutdown with
// timeout).

} // end of anonymous namespace.
