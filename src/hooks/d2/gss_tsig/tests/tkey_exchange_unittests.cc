// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <d2srv/testutils/stats_test_utils.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rdataclass.h>
#include <gss_tsig_api_utils.h>
#include <testutils/gss_tsig_dns_server.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::d2::test;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;
using namespace isc::stats;
using namespace isc::stats::test;
using namespace isc::util;

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
namespace ph = std::placeholders;

namespace {

const char* TEST_ADDRESS = "127.0.0.1";
const uint16_t TEST_PORT = 5376;
const long TEST_TIMEOUT = 5 * 1000; // expressed in milliseconds.

/// @brief Callback class used to handle the TKEY exchange status.
class TKeyExchangeTestCallback : public TKeyExchange::Callback {
public:
    /// @brief Constructor
    ///
    /// @param io_service The IOService which handles IO operations.
    /// @param status The expected status.
    TKeyExchangeTestCallback(IOServicePtr io_service,
                             TKeyExchange::Status status, bool go_on = false) :
        io_service_(io_service), status_(status), go_on_(go_on) {
    }

    /// @brief Destructor.
    ~TKeyExchangeTestCallback() = default;

    /// @brief The callback function which retrieves the TKEY exchange status.
    void operator()(TKeyExchange::Status status) {
        if (status != status_) {
            ADD_FAILURE() << "key exchange returned " << status
                          << ", expected: " << status_;
        }
        if (!go_on_) {
            io_service_->stop();
        }
    }

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;

    /// @brief The expected TKEY exchange status.
    TKeyExchange::Status status_;

    /// @brief The flag which specifies if the callback should leave the
    /// IOService handle more events.
    bool go_on_;
};

/// @brief Test fixture for testing the GSS-API GSS-TSIG TKEY exchange with
/// Kerberos 5.
class TKeyExchangeTest : public GssApiBaseTest, public D2StatTest {
public:
    /// @brief Constructor.
    TKeyExchangeTest() : io_service_(new IOService()), test_timer_(io_service_) {
        // Set the test timeout to break any running tasks if they hang.
        test_timer_.setup(std::bind(&TKeyExchangeTest::testTimeoutHandler, this),
                          TEST_TIMEOUT);
    }

    /// @brief Destructor.
    ~TKeyExchangeTest() {
        test_timer_.cancel();
        io_service_->stopAndPoll();
    }

    /// @brief Handler invoked when test timeout is hit
    ///
    /// This callback stops all running (hanging) tasks on IO service.
    void testTimeoutHandler() {
        io_service_->stop();
        FAIL() << "Test timeout hit.";
    }

    /// @brief Compares StatsMgr server statistics against expected values.
    ///
    /// Prepend server part of names before calling checkStats simpler variant.
    ///
    /// @param serve The server.
    /// @param expected_stats Map of expected static names and values.
    void checkStats(const DnsServerPtr& server, const StatMap& expected_stats) {
        StatMap key_stats;
        for (auto const& it : expected_stats) {
            const string& stat_name =
                StatsMgr::generateName("server", server->getID(), it.first);
            key_stats[stat_name] = it.second;
        }
        isc::stats::test::checkStats(key_stats);
    }

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;

    /// @brief The timeout timer.
    asiolink::IntervalTimer test_timer_;

    /// @brief Dummy DNS server.
    boost::shared_ptr<DummyDNSServer> dns_server_;
};

/// @brief Check TKEY exchange fails for different reasons.
TEST_F(TKeyExchangeTest, exchangeFailure) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();

    {
        SCOPED_TRACE("timeout when TKEY server is missing");
        TKeyExchangeTestCallback callback(io_service_, TKeyExchange::TIMEOUT);
        GssTsigKeyPtr key(new GssTsigKey(key_name));

        ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

        TKeyExchangePtr ex;

        ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                                  &callback, 100)));

        ASSERT_NO_THROW(ex->doExchange());
        io_service_->run();
        io_service_->stopAndPoll();

        StatMap stats = {
            { "tkey-sent", 1 },
            { "tkey-success", 0 },
            { "tkey-timeout", 1 },
            { "tkey-error", 0 }
        };
        checkStats(server, stats);

        ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
    }

    {
        SCOPED_TRACE("stop when exchange is canceled");
        TKeyExchangeTestCallback callback(io_service_, TKeyExchange::IO_STOPPED);
        GssTsigKeyPtr key(new GssTsigKey(key_name));

        ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

        TKeyExchangePtr ex;

        ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                                  &callback, 100)));

        ASSERT_NO_THROW(ex->doExchange());
        ASSERT_NO_THROW(ex->cancel());
        io_service_->run();
        io_service_->stopAndPoll();

        StatMap stats = {
            { "tkey-sent", 2 },
            { "tkey-success", 0 },
            { "tkey-timeout", 1 },
            { "tkey-error", 1 }
        };
        checkStats(server, stats);

        ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
    }

    {
        SCOPED_TRACE("validation failure when TKEY response is not signed");
        TKeyExchangeTestCallback callback(io_service_, TKeyExchange::UNSIGNED_RESPONSE);
        GssTsigKeyPtr key(new GssTsigKey(key_name));

        ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

        TKeyExchangePtr ex;

        ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                                  &callback, 100)));

        dns_server_.reset(new DummyDNSServer(io_service_, false, false, true));
        dns_server_->start();

        // The socket is now ready to receive the data. Let's post some request
        // message then. Set timeout to some reasonable value to make sure that
        // there is sufficient amount of time for the test to generate a
        // response.

        ASSERT_NO_THROW(ex->doExchange());
        io_service_->run();
        io_service_->stopAndPoll();

        StatMap stats = {
            { "tkey-sent", 3 },
            { "tkey-success", 0 },
            { "tkey-timeout", 1 },
            { "tkey-error", 2 }
        };
        checkStats(server, stats);

        ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
    }
}

/// @brief Check TKEY exchange fails when using Null IOService.
TEST_F(TKeyExchangeTest, exchangeBadUseNullIOService) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();
    TKeyExchangeTestCallback callback(IOServicePtr(), TKeyExchange::OTHER);
    GssTsigKeyPtr key(new GssTsigKey(key_name));

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    TKeyExchangePtr ex;

    ASSERT_THROW(ex.reset(new TKeyExchange(IOServicePtr(), server, key,
                                           &callback, 100)), BadValue);

    StatMap stats = {
        { "tkey-sent", 0 },
        { "tkey-success", 0 },
        { "tkey-timeout", 0 },
        { "tkey-error", 0 }
    };
    checkStats(server, stats);

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
}

/// @brief Check TKEY exchange fails when using same key name.
TEST_F(TKeyExchangeTest, exchangeBadUseSameKeyName) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();
    TKeyExchangeTestCallback callback(io_service_, TKeyExchange::SUCCESS, true);
    TKeyExchangeTestCallback callback_bad(io_service_, TKeyExchange::INVALID_RESPONSE);
    GssTsigKeyPtr key(new GssTsigKey(key_name));
    GssTsigKeyPtr key_bad(new GssTsigKey(key_name));

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
    ASSERT_EQ(key_bad->getSecCtx().get(), GSS_C_NO_CONTEXT);

    TKeyExchangePtr ex;

    ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                              &callback, 100)));

    TKeyExchangePtr ex_bad;

    ASSERT_NO_THROW(ex_bad.reset(new TKeyExchange(io_service_, server, key_bad,
                                                  &callback_bad, 100)));

    dns_server_.reset(new DummyDNSServer(io_service_, true, true, true));
    dns_server_->start();

    // The socket is now ready to receive the data. Let's post some request
    // message then. Set timeout to some reasonable value to make sure that
    // there is sufficient amount of time for the test to generate a
    // response.

    ASSERT_NO_THROW(ex->doExchange());
    ASSERT_NO_THROW(ex_bad->doExchange());
    io_service_->run();

    StatMap stats = {
        { "tkey-sent", 2 },
        { "tkey-success", 1 },
        { "tkey-timeout", 0 },
        { "tkey-error", 1 }
    };
    checkStats(server, stats);

    ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
    ASSERT_NE(key_bad->getSecCtx().get(), GSS_C_NO_CONTEXT);
    ASSERT_NE(key->getSecCtx().get(), key_bad->getSecCtx().get());
}

/// @brief Check TKEY exchange fails when using same key.
TEST_F(TKeyExchangeTest, exchangeBadUseSameKey) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();
    TKeyExchangeTestCallback callback(io_service_, TKeyExchange::SUCCESS);
    GssTsigKeyPtr key(new GssTsigKey(key_name));

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    TKeyExchangePtr ex;

    ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                              &callback, 100)));

    dns_server_.reset(new DummyDNSServer(io_service_));
    dns_server_->start();

    // The socket is now ready to receive the data. Let's post some request
    // message then. Set timeout to some reasonable value to make sure that
    // there is sufficient amount of time for the test to generate a
    // response.

    ASSERT_NO_THROW(ex->doExchange());
    io_service_->run();

    ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    auto old_ctx = key->getSecCtx().get();

    TKeyExchangePtr ex_bad;

    ASSERT_THROW(ex_bad.reset(new TKeyExchange(io_service_, server, key,
                                               &callback, 100)), BadValue);

    StatMap stats = {
        { "tkey-sent", 1 },
        { "tkey-success", 1 },
        { "tkey-timeout", 0 },
        { "tkey-error", 0 }
    };
    checkStats(server, stats);

    ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
    ASSERT_EQ(key->getSecCtx().get(), old_ctx);
}

/// @brief Check TKEY exchange fails when doing second exchange on same key.
TEST_F(TKeyExchangeTest, exchangeBadUseSecondExchange) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();
    TKeyExchangeTestCallback callback(io_service_, TKeyExchange::SUCCESS);
    GssTsigKeyPtr key(new GssTsigKey(key_name));

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    TKeyExchangePtr ex;

    ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                              &callback, 100)));

    dns_server_.reset(new DummyDNSServer(io_service_));
    dns_server_->start();

    // The socket is now ready to receive the data. Let's post some request
    // message then. Set timeout to some reasonable value to make sure that
    // there is sufficient amount of time for the test to generate a
    // response.

    ASSERT_NO_THROW(ex->doExchange());
    io_service_->run();

    ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    auto old_ctx = key->getSecCtx().get();

    ASSERT_THROW(ex->doExchange(), InvalidOperation);

    StatMap stats = {
        { "tkey-sent", 1 },
        { "tkey-success", 1 },
        { "tkey-timeout", 0 },
        { "tkey-error", 0 }
    };
    checkStats(server, stats);

    ASSERT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
    ASSERT_EQ(key->getSecCtx().get(), old_ctx);
}

/// @brief Check TKEY exchange does not start with bad client credentials.
TEST_F(TKeyExchangeTest, badCredentials) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setClientPrincipal("DHCP/foo.bar@FOO.BAR");
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();
    TKeyExchangeTestCallback callback(io_service_, TKeyExchange::BAD_CREDENTIALS);
    GssTsigKeyPtr key(new GssTsigKey(key_name));

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    TKeyExchangePtr ex;

    ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                              &callback, 100)));
    ASSERT_NO_THROW(ex->doExchange());

    StatMap stats = {
        { "tkey-sent", 0 },
        { "tkey-success", 0 },
        { "tkey-timeout", 0 },
        { "tkey-error", 1 }
    };
    checkStats(server, stats);

    EXPECT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
}

/// @brief Check TKEY exchange does not start with no server principal.
TEST_F(TKeyExchangeTest, noServerPrincipal) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    // This could give a different error but in all cases an error.
    server->setServerPrincipal("DNS/bad.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();
    TKeyExchangeTestCallback callback(io_service_, TKeyExchange::OTHER);
    GssTsigKeyPtr key(new GssTsigKey(key_name));

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    TKeyExchangePtr ex;

    ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                              &callback, 100)));
    ASSERT_NO_THROW(ex->doExchange());

    StatMap stats = {
        { "tkey-sent", 0 },
        { "tkey-success", 0 },
        { "tkey-timeout", 0 },
        { "tkey-error", 1 }
    };
    checkStats(server, stats);

    EXPECT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
}

/// @brief Check TKEY exchange fails with too short client credential lifetime.
TEST_F(TKeyExchangeTest, tooShortLifetime) {
    string key_name("1234.sig-blu.example.nil.");
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setKeyLifetime(0x7fff0000);
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);

    setKeytab();
    setAdministratorCCache();
    TKeyExchangeTestCallback callback(io_service_, TKeyExchange::BAD_CREDENTIALS);
    GssTsigKeyPtr key(new GssTsigKey(key_name));

    ASSERT_EQ(key->getSecCtx().get(), GSS_C_NO_CONTEXT);

    TKeyExchangePtr ex;

    ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                              &callback, 100)));

    dns_server_.reset(new DummyDNSServer(io_service_));
    dns_server_->start();

    // The socket is now ready to receive the data. Let's post some request
    // message then. Set timeout to some reasonable value to make sure that
    // there is sufficient amount of time for the test to generate a
    // response.

    ASSERT_NO_THROW(ex->doExchange());
    io_service_->run();

    StatMap stats = {
        { "tkey-sent", 1 },
        { "tkey-success", 0 },
        { "tkey-timeout", 0 },
        { "tkey-error", 1 }
    };
    checkStats(server, stats);

    EXPECT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
}

/// @brief Check TKEY exchange succeeds.
TEST_F(TKeyExchangeTest, exchangeSuccess) {
    string key_name("1234.sig-blu.example.nil.");
    GssTsigKeyPtr key(new GssTsigKey(key_name));
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);
    setKeytab();
    setAdministratorCCache();

    TKeyExchangeTestCallback callback(io_service_, TKeyExchange::SUCCESS);
    TKeyExchangePtr ex;

    ASSERT_NO_THROW(ex.reset(new TKeyExchange(io_service_, server, key,
                                              &callback, 100)));

    dns_server_.reset(new DummyDNSServer(io_service_));
    dns_server_->start();

    // The socket is now ready to receive the data. Let's post some request
    // message then. Set timeout to some reasonable value to make sure that
    // there is sufficient amount of time for the test to generate a
    // response.
    // This exchange should succeed.
    ASSERT_NO_THROW(ex->doExchange());
    io_service_->run();

    StatMap stats = {
        { "tkey-sent", 1 },
        { "tkey-success", 1 },
        { "tkey-timeout", 0 },
        { "tkey-error", 0 }
    };
    checkStats(server, stats);

    EXPECT_NE(key->getSecCtx().get(), GSS_C_NO_CONTEXT);
}

}
