// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
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
    virtual ~TestCallback() = default;

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

/// @brief Test fixture class for TlsContext.
class TLSTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Besides initializing class members it also sets the test timer to guard
    /// against endlessly running IO service when TCP connections are
    /// unsuccessful.
    TLSTest() : io_service_(new IOService()) {
    }

    /// @brief Destructor.
    virtual ~TLSTest() {
        io_service_->stopAndPoll();
    }

    /// @brief IO service.
    IOServicePtr io_service_;

    /// @brief The shutdown callback.
    TestCallback shutdown_cb_;

    /// @brief The TLS server.
    boost::shared_ptr<TlsStream<TestCallback>> server_;

    /// @brief The TLS client.
    boost::shared_ptr<TlsStream<TestCallback>> client_;
};

////////////////////////////////////////////////////////////////////////
//                              TlsContext tests                      //
////////////////////////////////////////////////////////////////////////

// Test if we can get a client context.
TEST_F(TLSTest, clientContext) {
    TlsContextPtr ctx;
    EXPECT_NO_THROW(ctx.reset(new TlsContext(TlsRole::CLIENT)));
}

// Test if we can get a server context.
TEST_F(TLSTest, serverContext) {
    TlsContextPtr ctx;
    EXPECT_NO_THROW(ctx.reset(new TlsContext(TlsRole::SERVER)));
}

// Test if the cert required flag is handled as expected.
TEST_F(TLSTest, certRequired) {
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
TEST_F(TLSTest, loadCAFile) {
    string ca(string(TEST_CA_DIR) + "/kea-ca.crt");
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadCaFile(ca));
}

// Test that no certificate authority gives an error.
TEST_F(TLSTest, loadNoCAFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("I/O error: DataSource: Failure opening file /no-such-file");
    // OpenSSL errors.
    exps.addThrow("No such file or directory");
    exps.addThrow("No such file or directory (system library)");
    exps.addThrow("No such file or directory (system library, fopen)");
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
TEST_F(TLSTest, loadTrustedSelfCAFile) {
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
TEST_F(TLSTest, loadCAPath) {
    string ca(TEST_CA_DIR);
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadCaPath(ca));
}

// Test that a certificate is wanted.
TEST_F(TLSTest, loadKeyCA) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("Flatfile_Certificate_Store::Flatfile_Certificate_Store cert file is empty");
    // LibreSSL or old OpenSSL does not check.
    exps.addNoError();
    // Recent OpenSSL errors.
    exps.addThrow("no certificate or crl found");
    exps.addThrow("no certificate or crl found (x509 certificate routines)");
    exps.addThrow("no certificate or crl found (x509 certificate routines, CRYPTO_internal)");
    exps.addThrow("no certificate or crl found (x509 certificate routines, X509_load_cert_crl_file)");
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
TEST_F(TLSTest, loadCertFile) {
    string cert(string(TEST_CA_DIR) + "/kea-client.crt");
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadCertFile(cert));
}

// Test that no end entity certificate gives an error.
TEST_F(TLSTest, loadNoCertFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("I/O error: DataSource: Failure opening file /no-such-file");
    // OpenSSL errors.
    exps.addThrow("No such file or directory");
    exps.addThrow("No such file or directory (system library)");
    exps.addThrow("No such file or directory (system library, fopen)");
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
TEST_F(TLSTest, loadCsrCertFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("Expected a certificate, got 'CERTIFICATE REQUEST'");
    // OpenSSL errors.
    exps.addThrow("no start line");
    exps.addThrow("no start line (PEM routines)");
    exps.addThrow("no start line (PEM routines, get_name)");
    exps.addThrow("no start line (PEM routines, CRYPTO_internal)");
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
TEST_F(TLSTest, loadKeyFile) {
    string key(string(TEST_CA_DIR) + "/kea-client.key");
    TestTlsContext ctx(TlsRole::CLIENT);
    EXPECT_NO_THROW(ctx.loadKeyFile(key));
}

// Test that no private key gives an error.
TEST_F(TLSTest, loadNoKeyFile) {
    Expecteds exps;
    // Botan error.
    exps.addThrow("I/O error: DataSource: Failure opening file /no-such-file");
    // OpenSSL errors.
    exps.addThrow("No such file or directory");
    exps.addThrow("No such file or directory (system library)");
    exps.addThrow("No such file or directory (system library, fopen)");
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
TEST_F(TLSTest, loadCertKeyFile) {
    Expecteds exps;
    // Botan error.
    string botan_error = "PKCS #8 private key decoding failed with PKCS #8: ";
    botan_error += "Unknown PEM label CERTIFICATE";
    exps.addThrow(botan_error);
    // OpenSSL errors.
    exps.addThrow("no start line");
    exps.addThrow("no start line (PEM routines)");
    exps.addThrow("no start line (PEM routines, get_name)");
    exps.addThrow("no start line (PEM routines, CRYPTO_internal)");
    exps.addThrow("PEM lib");
    exps.addThrow("PEM lib (SSL routines)");
    exps.addThrow("unsupported (DECODER routines)");
    exps.addThrow("unsupported");
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
TEST_F(TLSTest, loadMismatch) {
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
TEST_F(TLSTest, configure) {
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
TEST_F(TLSTest, configureError) {
    // The error case.
    Expecteds exps;
    // Common part of the error message.
    string common_error = "load of cert file '/no-such-file' failed: ";
    // Botan error.
    string botan_error = "I/O error: DataSource: Failure opening file /no-such-file";
    exps.addThrow(common_error + botan_error);
    // OpenSSL errors.
    string openssl_error = "No such file or directory";
    exps.addThrow(common_error + openssl_error);
    exps.addThrow(common_error + "No such file or directory (system library)");
    exps.addThrow(common_error + "No such file or directory (system library, fopen)");
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
TEST_F(TLSTest, stream) {
    TlsContextPtr ctx(new TlsContext(TlsRole::CLIENT));
    boost::scoped_ptr<TlsStream<TestCallback> > st;
    EXPECT_NO_THROW(server_.reset(new TlsStream<TestCallback>(io_service_, ctx)));
}

// Test what happens when handshake is forgotten.
TEST_F(TLSTest, noHandshake) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer1(io_service_);
    bool timeout = false;
    timer1.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Send on the client.
    char send_buf[] = "some text...";
    TestCallback send_cb;
    async_write(*client_, boost::asio::buffer(send_buf), send_cb);
    while (!timeout && !send_cb.getCalled()) {
        io_service_->runOne();
    }
    timer1.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("InvalidObjectState");
    // OpenSSL errors.
    exps.addError("uninitialized");
    exps.addError("uninitialized (SSL routines)");
    exps.addError("uninitialized (SSL routines, ST_BEFORE_ACCEPT)");
    exps.addError("uninitialized (SSL routines, ssl_write_internal)");
    exps.checkAsync("send", send_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "send: " << exps.getErrMsg() << "\n";
    }

    // Setup a second timeout.
    IntervalTimer timer2(io_service_);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server_->async_read_some(boost::asio::buffer(receive_buf), receive_cb);
    while (!timeout && !receive_cb.getCalled()) {
        io_service_->runOne();
    }
    timer2.cancel();

    exps.clear();
    // On Botan and some OpenSSL the receive party hangs.
    exps.addTimeout();
    // OpenSSL errors.
    exps.addError("uninitialized");
    exps.addError("uninitialized (SSL routines)");
    exps.addError("uninitialized (SSL routines, ST_BEFORE_ACCEPT)");
    exps.addError("uninitialized (SSL routines, ssl_read_internal)");
    exps.checkAsync("receive", receive_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "receive timeout\n";
        } else {
            std::cout << "receive: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the server was not configured.
TEST_F(TLSTest, serverNotConfigured) {
    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    // Skip config.
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->handshake(server_cb);
    TestCallback client_cb;
    client_->handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("handshake_failure");
    // Old LibreSSL error.
    exps.addError("no shared cipher");
    // OpenSSL errors.
    exps.addError("sslv3 alert handshake failure");
    exps.addError("no shared cipher (SSL routines)");
    exps.addError("no shared cipher (SSL routines, ACCEPT_SR_CLNT_HELLO_C)");
    exps.addError("no shared cipher (SSL routines, tls_post_process_client_hello)");
    // Recent LibreSSL error.
    exps.addError("missing rsa certificate (SSL routines, (UNKNOWN)SSL_internal)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // On Botan and some OpenSSL the client hangs.
    exps.addTimeout();
    // OpenSSL errors.
    exps.addError("sslv3 alert handshake failure");
    exps.addError("sslv3 alert handshake failure (SSL routines)");
    exps.addError("sslv3 alert handshake failure (SSL routines, CONNECT_CR_SRVR_HELLO)");
    exps.addError("sslv3 alert handshake failure (SSL routines, CONNECT_CR_CERT)");
    exps.addError("sslv3 alert handshake failure (SSL routines, ssl3_read_bytes)");
    exps.addError("ssl/tls alert handshake failure (SSL routines)");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "client timeout\n";
        } else {
            std::cout << "client: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client was not configured.
TEST_F(TLSTest, clientNotConfigured) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx(new TlsContext(TlsRole::CLIENT));
    // Skip config.
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // On Botan and some OpenSSL the server hangs.
    exps.addTimeout();
    // OpenSSL errors.
    exps.addError("tlsv1 alert unknown ca");
    exps.addError("tlsv1 alert unknown ca (SSL routines)");
    exps.addError("tlsv1 alert unknown ca (SSL routines, ACCEPT_SR_CERT)");
    exps.addError("tlsv1 alert unknown ca (SSL routines, ACCEPT_SR_CERT_VRFY)");
    exps.addError("tlsv1 alert unknown ca (SSL routines, ssl3_read_bytes)");
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
    // Old LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL errors.
    exps.addError("certificate verify failed");
    exps.addError("certificate verify failed (SSL routines)");
    exps.addError("certificate verify failed (SSL routines, CONNECT_CR_CERT)");
    exps.addError("certificate verify failed (SSL routines, (UNKNOWN)SSL_internal)");
    exps.addError("certificate verify failed (SSL routines, tls_process_server_certificate)");
    // The client should not hang.
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client is HTTP (vs HTTPS).
TEST_F(TLSTest, clientHTTPnoS) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(io_service_->getInternalIOService());

    // Connect to.
    client.open(tcp::v4());
    TestCallback connect_cb;
    client.async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform server TLS handshake.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);

    // Client sending a HTTP GET.
    char send_buf[] = "GET / HTTP/1.1\r\n";
    TestCallback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan server hangs before 2.18.
    exps.addTimeout();
    // Botan error.
    exps.addError("protocol_version");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert protocol version");
    // OpenSSL errors (OpenSSL recognizes HTTP).
    exps.addError("http request");
    exps.addError("http request (SSL routines)");
    exps.addError("http request (SSL routines, ACCEPT_SR_CLNT_HELLO)");
    exps.addError("http request (SSL routines, ssl3_get_record)");
    // Another OpenSSL error (not all OpenSSL recognizes HTTP).
    exps.addError("wrong version number");
    // Recent LibreSSL error.
    exps.addError("tlsv1 alert protocol version (SSL routines, ACCEPT_SR_CLNT_HELLO)");
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
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client does not use HTTP nor HTTP.
TEST_F(TLSTest, unknownClient) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(io_service_->getInternalIOService());

    // Connect to.
    client.open(tcp::v4());
    TestCallback connect_cb;
    client.async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform server TLS handshake.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);

    // Client sending something which is not a TLS ClientHello.
    char send_buf[] = "hello my server...";
    TestCallback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan errors.
    exps.addError("record_overflow");
    exps.addError("protocol_version");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert protocol version");
    // Old OpenSSL error.
    exps.addError("unknown protocol");
    // Recent OpenSSL errors.
    exps.addError("wrong version number");
    exps.addError("wrong version number (SSL routines)");
    exps.addError("wrong version number (SSL routines, ssl3_get_record)");
    exps.addError("packet length too long (SSL routines)");
    // Recent LibreSSL error.
    exps.addError("unknown protocol (SSL routines, ACCEPT_SR_CLNT_HELLO)");
    exps.addError("tlsv1 alert protocol version (SSL routines, ACCEPT_SR_CLNT_HELLO)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    // No error on the client side.
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client.lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client uses a certificate from another CA.
TEST_F(TLSTest, anotherClient) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part using a certificate signed by another CA.
    TlsContextPtr client_ctx;
    test::configOther(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL errors.
    // Full error is:
    // error 20 at 0 depth lookup:unable to get local issuer certificate
    exps.addError("certificate verify failed");
    exps.addError("certificate verify failed (SSL routines)");
    exps.addError("certificate verify failed (SSL routines, tls_process_client_certificate)");
    // Recent LibreSSL errors.
    exps.addError("no certificate returned (SSL routines, ACCEPT_SR_CERT)");
    exps.addError("certificate verify failed (SSL routines, (UNKNOWN)SSL_internal)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan client hangs.
    exps.addTimeout();
    // Old LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // Recent LibreSSL error.
    exps.addError("tlsv1 alert unknown ca (SSL routines, CONNECT_CR_SESSION_TICKET)");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "client timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "client: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client uses a self-signed certificate.
TEST_F(TLSTest, selfSigned) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part using a self-signed certificate.
    TlsContextPtr client_ctx;
    test::configSelf(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL errors.
    // Full error is:
    // error 18 at 0 depth lookup:self signed certificate
    exps.addError("certificate verify failed");
    exps.addError("certificate verify failed (SSL routines)");
    exps.addError("certificate verify failed (SSL routines, tls_process_client_certificate)");
    // Recent LibreSSL errors.
    exps.addError("no certificate returned (SSL routines, ACCEPT_SR_CERT)");
    exps.addError("certificate verify failed (SSL routines, (UNKNOWN)SSL_internal)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan client hangs.
    exps.addTimeout();
    // Old LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // Recent LibreSSL error.
    exps.addError("tlsv1 alert unknown ca (SSL routines, CONNECT_CR_SESSION_TICKET)");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "client timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "client: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

////////////////////////////////////////////////////////////////////////
//                  Close on error handshake failures                 //
////////////////////////////////////////////////////////////////////////

// Investigate what happens when a peer closes its streams when the
// handshake callback returns an error. In particular does still
// the other peer timeout?

// Test what happens when handshake is forgotten.
TEST_F(TLSTest, noHandshakeCloseonError) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer1(io_service_);
    bool timeout = false;
    timer1.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Send on the client.
    char send_buf[] = "some text...";
    TestCallback send_cb(&client_->lowest_layer());
    async_write(*client_, boost::asio::buffer(send_buf), send_cb);
    while (!timeout && !send_cb.getCalled()) {
        io_service_->runOne();
    }
    timer1.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("InvalidObjectState");
    // OpenSSL errors.
    exps.addError("uninitialized");
    exps.addError("uninitialized (SSL routines)");
    exps.addError("uninitialized (SSL routines, ST_BEFORE_ACCEPT)");
    exps.addError("uninitialized (SSL routines, ssl_write_internal)");
    exps.checkAsync("send", send_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "send: " << exps.getErrMsg() << "\n";
    }

    // Setup a second timeout.
    IntervalTimer timer2(io_service_);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server_->async_read_some(boost::asio::buffer(receive_buf), receive_cb);
    while (!timeout && !receive_cb.getCalled()) {
        io_service_->runOne();
    }
    timer2.cancel();

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // OpenSSL errors.
    exps.addError("uninitialized");
    exps.addError("uninitialized (SSL routines)");
    exps.addError("uninitialized (SSL routines, ST_BEFORE_ACCEPT)");
    exps.addError("uninitialized (SSL routines, ssl_read_internal)");
    exps.checkAsync("receive", receive_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "receive: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the server was not configured.
TEST_F(TLSTest, serverNotConfiguredCloseonError) {
    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    // Skip config.
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server_->lowest_layer());
    server_->handshake(server_cb);
    TestCallback client_cb;
    client_->handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("handshake_failure");
    // Old LibreSSL error.
    exps.addError("no shared cipher");
    // OpenSSL errors.
    exps.addError("sslv3 alert handshake failure");
    exps.addError("no shared cipher (SSL routines)");
    exps.addError("no shared cipher (SSL routines, ACCEPT_SR_CLNT_HELLO_C)");
    exps.addError("no shared cipher (SSL routines, tls_post_process_client_hello)");
    // Recent LibreSSL error.
    exps.addError("missing rsa certificate (SSL routines, (UNKNOWN)SSL_internal)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // OpenSSL errors.
    exps.addError("sslv3 alert handshake failure");
    exps.addError("sslv3 alert handshake failure (SSL routines)");
    exps.addError("sslv3 alert handshake failure (SSL routines, CONNECT_CR_SRVR_HELLO)");
    exps.addError("sslv3 alert handshake failure (SSL routines, ssl3_read_bytes)");
    exps.addError("ssl/tls alert handshake failure (SSL routines)");
    // Recent LibreSSL error.
    exps.addError("sslv3 alert handshake failure (SSL routines, CONNECT_CR_CERT)");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client was not configured.
TEST_F(TLSTest, clientNotConfiguredCloseonError) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx(new TlsContext(TlsRole::CLIENT));
    // Skip config.
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb(&client_->lowest_layer());
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // OpenSSL errors.
    exps.addError("tlsv1 alert unknown ca");
    exps.addError("tlsv1 alert unknown ca (SSL routines)");
    exps.addError("tlsv1 alert unknown ca (SSL routines, ACCEPT_SR_CERT)");
    exps.addError("tlsv1 alert unknown ca (SSL routines, ACCEPT_SR_CERT_VRFY)");
    exps.addError("tlsv1 alert unknown ca (SSL routines, ssl3_read_bytes)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan error (unfortunately a bit generic).
    exps.addError("bad_certificate");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL errors.
    exps.addError("certificate verify failed");
    exps.addError("certificate verify failed (SSL routines)");
    exps.addError("certificate verify failed (SSL routines, CONNECT_CR_CERT)");
    exps.addError("certificate verify failed (SSL routines, tls_process_server_certificate)");
    // Recent LibreSSL error.
    exps.addError("certificate verify failed (SSL routines, (UNKNOWN)SSL_internal)");
    // The client should not hang.
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client is HTTP (vs HTTPS).
TEST_F(TLSTest, clientHTTPnoSCloseonError) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    tcp::socket client(io_service_->getInternalIOService());

    // Connect to.
    client.open(tcp::v4());
    TestCallback connect_cb;
    client.async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform server TLS handshake.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);

    // Client sending a HTTP GET.
    char send_buf[] = "GET / HTTP/1.1\r\n";
    TestCallback client_cb;
    client.async_send(boost::asio::buffer(send_buf), client_cb);

    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan server hangs before 2.18.
    exps.addTimeout();
    // Botan behavior was reported and fixed.
    exps.addError("protocol_version");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert protocol version");
    // OpenSSL errors when OpenSSL recognizes HTTP.
    exps.addError("http request");
    exps.addError("http request (SSL routines)");
    exps.addError("http request (SSL routines, ACCEPT_SR_CLNT_HELLO)");
    exps.addError("http request (SSL routines, ssl3_get_record)");
    // Another OpenSSL error (not all OpenSSL recognizes HTTP).
    exps.addError("wrong version number");
    // Recent LibreSSL error.
    exps.addError("tlsv1 alert protocol version (SSL routines, ACCEPT_SR_CLNT_HELLO)");
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
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client uses a certificate from another CA.
TEST_F(TLSTest, anotherClientCloseonError) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part using a certificate signed by another CA.
    TlsContextPtr client_ctx;
    test::configOther(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server_->lowest_layer());
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL errors.
    // Full error is:
    // error 20 at 0 depth lookup:unable to get local issuer certificate
    exps.addError("certificate verify failed");
    exps.addError("certificate verify failed (SSL routines)");
    exps.addError("certificate verify failed (SSL routines, tls_process_client_certificate)");
    // Recent LibreSSL errors.
    exps.addError("no certificate returned (SSL routines, ACCEPT_SR_CERT)");
    exps.addError("certificate verify failed (SSL routines, (UNKNOWN)SSL_internal)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // Old LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // Recent LibreSSL error.
    exps.addError("tlsv1 alert unknown ca (SSL routines, CONNECT_CR_SESSION_TICKET)");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg() && exps.hasErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the client uses a self-signed certificate.
TEST_F(TLSTest, selfSignedCloseonError) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part using a self-signed certificate.
    TlsContextPtr client_ctx;
    test::configSelf(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server_->lowest_layer());
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    Expecteds exps;
    // Botan error.
    exps.addError("bad_certificate");
    // Old LibreSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // OpenSSL errors.
    // Full error is:
    // error 18 at 0 depth lookup:self signed certificate
    exps.addError("certificate verify failed");
    exps.addError("certificate verify failed (SSL routines)");
    exps.addError("certificate verify failed (SSL routines, tls_process_client_certificate)");
    // Recent LibreSSL errors.
    exps.addError("no certificate returned (SSL routines, ACCEPT_SR_CERT)");
    exps.addError("certificate verify failed (SSL routines, (UNKNOWN)SSL_internal)");
    exps.checkAsync("server", server_cb);
    if (Expecteds::displayErrMsg()) {
        std::cout << "server: " << exps.getErrMsg() << "\n";
    }

    exps.clear();
    // Botan and some OpenSSL.
    exps.addError("stream truncated");
    // Alias on old OpenSSL.
    exps.addError("short read");
    // Old LibreSSL and recent OpenSSL do not fail.
    exps.addNoError();
    // Old OpenSSL error.
    exps.addError("tlsv1 alert unknown ca");
    // Recent LibreSSL error.
    exps.addError("tlsv1 alert unknown ca (SSL routines, CONNECT_CR_SESSION_TICKET)");
    exps.checkAsync("client", client_cb);
    if (Expecteds::displayErrMsg() && exps.hasErrMsg()) {
        std::cout << "client: " << exps.getErrMsg() << "\n";
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

////////////////////////////////////////////////////////////////////////
//                      TLS handshake corner case                     //
////////////////////////////////////////////////////////////////////////

// Some special cases.

// Test what happens when the client uses a certificate from another CA
// but the client certificate request and validation are disabled.
TEST_F(TLSTest, anotherClientNoReq) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServerNoReq(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part using a certificate signed by another CA.
    TlsContextPtr client_ctx;
    test::configOther(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    // Should not fail.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the server uses a certificate without subject
// alternative name (but still a version 3 certificate).
TEST_F(TLSTest, serverRaw) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configServerRaw(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    // Should not fail.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

#ifdef WITH_OPENSSL
// Test what happens when the client uses a trusted self-signed certificate.
// Not really a failure case as it works...
TEST_F(TLSTest, trustedSelfSigned) {
    // Server part.
    TlsContextPtr server_ctx;
    test::configTrustedSelf(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part using a self-signed certificate.
    TlsContextPtr client_ctx;
    test::configSelf(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb;
    server_->async_handshake(roleToImpl(TlsRole::SERVER), server_cb);
    TestCallback client_cb;
    client_->async_handshake(roleToImpl(TlsRole::CLIENT), client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    // It should work for all OpenSSL.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}
#endif // WITH_OPENSSL

////////////////////////////////////////////////////////////////////////
//                              TLS shutdown                          //
////////////////////////////////////////////////////////////////////////

// Investigate the TLS shutdown processing.

// Test what happens when the shutdown receiver is inactive.
TEST_F(TLSTest, shutdownInactive) {
    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server_->lowest_layer());
    server_->handshake(server_cb);
    TestCallback client_cb;
    client_->handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown.
    IntervalTimer timer2(io_service_);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Shutdown on the client leaving the server inactive.
    client_->shutdown(shutdown_cb_);
    while (!timeout && !shutdown_cb_.getCalled()) {
        io_service_->runOne();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // OpenSSL hangs.
    exps.addTimeout();
    exps.checkAsync("shutdown", shutdown_cb_);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "shutdown timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "shutdown: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the shutdown receiver is active.
TEST_F(TLSTest, shutdownActive) {
    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server_->lowest_layer());
    server_->handshake(server_cb);
    TestCallback client_cb;
    client_->handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown and receive.
    IntervalTimer timer2(io_service_);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server_->async_read_some(boost::asio::buffer(receive_buf), receive_cb);

    // Shutdown on the client.
    client_->shutdown(shutdown_cb_);
    while (!timeout && (!shutdown_cb_.getCalled() || !receive_cb.getCalled())) {
        io_service_->runOne();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // OpenSSL hangs.
    exps.addTimeout();
    exps.checkAsync("shutdown", shutdown_cb_);
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
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the shutdown receiver is inactive on shutdown
// and immediate close.
TEST_F(TLSTest, shutdownCloseInactive) {
    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server_->lowest_layer());
    server_->handshake(server_cb);
    TestCallback client_cb;
    client_->handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown.
    IntervalTimer timer2(io_service_);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Shutdown on the client leaving the server inactive.
    client_->shutdown(shutdown_cb_);

    // Post a close which should be called after the shutdown.
    io_service_->post([&] { client_->lowest_layer().close(); });
    while (!timeout && !shutdown_cb_.getCalled()) {
        io_service_->runOne();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // LibreSSL and some old OpenSSL gets Operation canceled.
    exps.addError("Operation canceled");
    // OpenSSL gets Bad file descriptor.
    exps.addError("Bad file descriptor");
    exps.checkAsync("shutdown", shutdown_cb_);
    if (Expecteds::displayErrMsg()) {
        if (timeout) {
            std::cout << "shutdown timeout\n";
        } else if (exps.hasErrMsg()) {
            std::cout << "shutdown: " << exps.getErrMsg() << "\n";
        }
    }

    // Close client and server.
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Test what happens when the shutdown receiver is active with an
// immediate close.
TEST_F(TLSTest, shutdownCloseActive) {
    // Server part.
    TlsContextPtr server_ctx(new TlsContext(TlsRole::SERVER));
    test::configServer(server_ctx);
    server_.reset(new TlsStream<TestCallback>(io_service_, server_ctx));

    // Accept a client.
    tcp::endpoint server_ep(tcp::endpoint(make_address(SERVER_ADDRESS),
                                          SERVER_PORT));
    tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    TestCallback accept_cb;
    acceptor.async_accept(server_->lowest_layer(), accept_cb);

    // Client part.
    TlsContextPtr client_ctx;
    test::configClient(client_ctx);
    client_.reset(new TlsStream<TestCallback>(io_service_, client_ctx));

    // Connect to.
    client_->lowest_layer().open(tcp::v4());
    TestCallback connect_cb;
    client_->lowest_layer().async_connect(server_ep, connect_cb);

    // Run accept and connect.
    while (!accept_cb.getCalled() || !connect_cb.getCalled()) {
        io_service_->runOne();
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
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Perform TLS handshakes.
    TestCallback server_cb(&server_->lowest_layer());
    server_->handshake(server_cb);
    TestCallback client_cb;
    client_->handshake(client_cb);
    while (!timeout && (!server_cb.getCalled() || !client_cb.getCalled())) {
        io_service_->runOne();
    }
    timer.cancel();

    // No problem is expected.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_FALSE(server_cb.getCode());
    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_FALSE(client_cb.getCode());

    // Setup a timeout for the shutdown and receive.
    IntervalTimer timer2(io_service_);
    timeout = false;
    timer2.setup([&timeout] { timeout = true; }, 100, IntervalTimer::ONE_SHOT);

    // Receive on the server.
    vector<char> receive_buf(64);
    TestCallback receive_cb;
    server_->async_read_some(boost::asio::buffer(receive_buf), receive_cb);

    // Shutdown on the client.
    client_->shutdown(shutdown_cb_);

    // Post a close which should be called after the shutdown.
    io_service_->post([&] { client_->lowest_layer().close(); });
    while (!timeout && (!shutdown_cb_.getCalled() || !receive_cb.getCalled())) {
        io_service_->runOne();
    }
    timer2.cancel();

    Expecteds exps;
    // Botan gets no error.
    exps.addNoError();
    // LibreSSL and some old OpenSSL gets Operation canceled.
    exps.addError("Operation canceled");
    // OpenSSL gets Bad file descriptor.
    exps.addError("Bad file descriptor");
    exps.checkAsync("shutdown", shutdown_cb_);
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
    EXPECT_NO_THROW(client_->lowest_layer().close());
    EXPECT_NO_THROW(server_->lowest_layer().close());
}

// Conclusion about the shutdown: do the close on completion (e.g. in the
// handler) or on timeout (i.e. simulate an asynchronous shutdown with
// timeout).

} // end of anonymous namespace.
