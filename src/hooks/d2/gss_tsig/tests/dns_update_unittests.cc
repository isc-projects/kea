// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/interval_timer.h>
#include <asiodns/io_fetch.h>
#include <d2srv/dns_client.h>
#include <d2srv/testutils/stats_test_utils.h>
#include <dns/rcode.h>
#include <gss_tsig_api_utils.h>
#include <managed_key.h>
#include <testutils/gss_tsig_dns_server.h>
#include <util/chrono_time_utils.h>

#include <chrono>

#include <gtest/gtest.h>

namespace {

const char* TEST_ADDRESS = "127.0.0.1";
const uint16_t TEST_PORT = 5376;
const long TEST_TIMEOUT = 5 * 1000; // expressed in milliseconds.

using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::d2;
using namespace isc::d2::test;
using namespace isc::dns;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;
using namespace isc::util;

using namespace std;
using namespace std::chrono;

typedef std::function<void()> DNSCallback;

/// @brief Callback class used to handle the TKEY exchange status.
class NSUpdateTestCallback : public TKeyExchange::Callback {
public:
    /// @brief Constructor
    ///
    /// @param io_service The IOService which handles IO operations.
    /// @param callback The callback used as a continuation after the TKEY
    /// exchange is completed.
    /// @param status The expected status.
    NSUpdateTestCallback(IOServicePtr io_service, DNSCallback& callback,
                         TKeyExchange::Status status = TKeyExchange::SUCCESS) :
        io_service_(io_service), callback_(callback), status_(status) {
    }

    /// @brief Destructor.
    ~NSUpdateTestCallback() = default;

    /// @brief The callback function which retrieves the TKEY exchange status.
    void operator()(TKeyExchange::Status status) override {
        if (status != status_) {
            ADD_FAILURE() << "key exchange returned " << status
                          << ", expected: " << status_;
            io_service_->stop();
            return;
        }

        if (status != TKeyExchange::SUCCESS) {
            io_service_->stop();
            return;
        }

        if (callback_) {
            callback_();
        } else {
            io_service_->stop();
        }
    }

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;

    /// @brief The callback called after the GSS-TSIG TKEY exchange has
    /// succeeded so that the GSS-TSIG DNS update is performed.
    DNSCallback& callback_;

    /// @brief The expected TKEY exchange status.
    TKeyExchange::Status status_;
};

/// @brief Test fixture for testing the GSS-API GSS-TSIG DNS update with
/// Kerberos 5.
class GssTsigDNSUpdateTest : public GssApiBaseTest, public DNSClient::Callback,
                             public D2StatTest {
public:
    /// @brief Constructor.
    GssTsigDNSUpdateTest() : io_service_(new IOService()),
                             test_timer_(io_service_), response_(),
                             dns_client_(new DNSClient(response_, this)),
                             expected_status_(DNSClient::SUCCESS),
                             success_(false), use_fallback_(false) {

        // Set the test timeout to break any running tasks if they hang.
        test_timer_.setup(std::bind(&GssTsigDNSUpdateTest::testTimeoutHandler, this),
                          TEST_TIMEOUT);
    }

    /// @brief Destructor.
    virtual ~GssTsigDNSUpdateTest() {
        key_->getTKeyExchange().reset();
        test_timer_.cancel();
        io_service_->stopAndPoll();
    }

    /// @brief Perform the DNS update.
    void doGssTsigDNSUpdate() {
        auto key = key_;
        if (use_fallback_) {
            key.reset();
        }
        // Create a request DNS Update message.
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        ASSERT_NO_THROW(message.setRcode(Rcode(Rcode::NOERROR_CODE)));
        ASSERT_NO_THROW(message.setZone(Name("example.com"), RRClass::IN()));

        // The socket is now ready to receive the data. Let's post some request
        // message then. Set timeout to some reasonable value to make sure that
        // there is sufficient amount of time for the test to generate a
        // response.
        const int timeout = 500;
        dns_client_->doUpdate(io_service_, IOAddress(TEST_ADDRESS), TEST_PORT,
                              message, timeout, key);
    }

    /// @brief Exchange completion callback
    ///
    /// This callback is called when the exchange with the DNS server is
    /// complete or an error occurred. This includes the occurrence of a timeout.
    ///
    /// @param status A status code returned by DNSClient.
    virtual void operator()(DNSClient::Status status) override {
        io_service_->stop();
        EXPECT_EQ(expected_status_, status);
        if (expected_status_ == DNSClient::SUCCESS) {
            // We should have received a signed response.
            ASSERT_TRUE(response_);
            EXPECT_EQ(D2UpdateMessage::RESPONSE, response_->getQRFlag());
            ASSERT_EQ(1, response_->getRRCount(D2UpdateMessage::SECTION_ZONE));
            D2ZonePtr zone = response_->getZone();
            ASSERT_TRUE(zone);
            EXPECT_EQ("example.com.", zone->getName().toText());
            EXPECT_EQ(RRClass::IN().getCode(), zone->getClass().getCode());
            // DNS update has been signed on the server side and verified on the
            // client side.
            success_ = true;
        } else if (expected_status_ == DNSClient::INVALID_RESPONSE) {
            // We should have received an unsigned response.
            ASSERT_TRUE(response_);
            EXPECT_EQ(D2UpdateMessage::RESPONSE, response_->getQRFlag());
            ASSERT_EQ(1, response_->getRRCount(D2UpdateMessage::SECTION_ZONE));
            D2ZonePtr zone = response_->getZone();
            ASSERT_FALSE(zone);
        }
    }

    /// @brief Handler invoked when test timeout is hit.
    ///
    /// This callback stops all running (hanging) tasks on IO service.
    void testTimeoutHandler() {
        io_service_->stop();
        FAIL() << "Test timeout hit.";
    }

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;

    /// @brief The timeout timer.
    asiolink::IntervalTimer test_timer_;

    /// @brief DNS client response.
    D2UpdateMessagePtr response_;

    /// @brief The DNS client performing GSS-TSIG DNS update.
    DNSClientPtr dns_client_;

    /// @brief The DNS client key.
    ManagedKeyPtr key_;

    /// @brief The expected status of the DNS client update callback.
    DNSClient::Status expected_status_;

    /// @brief The flag which indicates that the DNS update has been
    /// successfully verified.
    bool success_;

    /// @brief The flag which indicates if the DNS update should fallback to non
    /// GSS-TSIG if the key is removed.
    bool use_fallback_;
};

/// @brief Check GSS-TSIG DNS update fails because the DNS server is not
/// responding to DNS updates.
TEST_F(GssTsigDNSUpdateTest, runGssTsigDNSUpdateTimeout) {
    expected_status_ = DNSClient::TIMEOUT;
    string key_name("1234.sig-blu.example.nil.");
    key_.reset(new ManagedKey(key_name));
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);
    setKeytab();
    setAdministratorCCache();

    DNSCallback dns_callback = std::bind(&GssTsigDNSUpdateTest::doGssTsigDNSUpdate, this);
    NSUpdateTestCallback callback(io_service_, dns_callback);

    system_clock::time_point now = system_clock::now();
    key_->setInception(now);
    key_->setExpire(now + seconds(server->getKeyLifetime()));
    key_->getTKeyExchange().reset(new TKeyExchange(io_service_, server, key_,
                                                   &callback));
    key_->getTKeyExchange()->doExchange();

    // The server will sign the TKEY and stop responding to DNS updates.
    DummyDNSServer dns_server(io_service_, true, true, false, false);
    dns_server.start();
    io_service_->run();
    ASSERT_FALSE(success_);
    // Check statistics.
    StatMap stats_key = {
        { "update-sent", 1},
        { "update-success", 0},
        { "update-timeout", 1},
        { "update-error", 0}
    };
    checkStats(key_name, stats_key);
    StatMap stats_upd = {
        { "update-sent", 1},
        { "update-signed", 1},
        { "update-unsigned", 0},
        { "update-success", 0},
        { "update-timeout", 1},
        { "update-error", 0}
    };
    checkStats(stats_upd);
}

/// @brief Check GSS-TSIG DNS update fails because the DNS update is not signed.
TEST_F(GssTsigDNSUpdateTest, runGssTsigDNSUpdateFailure) {
    expected_status_ = DNSClient::INVALID_RESPONSE;
    string key_name("1234.sig-blu.example.nil.");
    key_.reset(new ManagedKey(key_name));
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);
    setKeytab();
    setAdministratorCCache();

    DNSCallback dns_callback = std::bind(&GssTsigDNSUpdateTest::doGssTsigDNSUpdate, this);
    NSUpdateTestCallback callback(io_service_, dns_callback);

    system_clock::time_point now = system_clock::now();
    key_->setInception(now);
    key_->setExpire(now + seconds(server->getKeyLifetime()));
    key_->getTKeyExchange().reset(new TKeyExchange(io_service_, server, key_,
                                                   &callback));
    key_->getTKeyExchange()->doExchange();

    // The server will sign the TKEY, but not sign the DNS update.
    DummyDNSServer dns_server(io_service_, true, false);
    dns_server.start();
    io_service_->run();
    ASSERT_FALSE(success_);
    // Check statistics.
    StatMap stats_key = {
        { "update-sent", 1},
        { "update-success", 0},
        { "update-timeout", 0},
        { "update-error", 1}
    };
    checkStats(key_name, stats_key);
    StatMap stats_upd = {
        { "update-sent", 1},
        { "update-signed", 1},
        { "update-unsigned", 0},
        { "update-success", 0},
        { "update-timeout", 0},
        { "update-error", 1}
    };
    checkStats(stats_upd);
}

/// @brief Check GSS-TSIG DNS update succeeds.
TEST_F(GssTsigDNSUpdateTest, runGssTsigDNSUpdateSuccess) {
    string key_name("1234.sig-blu.example.nil.");
    key_.reset(new ManagedKey(key_name));
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);
    setKeytab();
    setAdministratorCCache();

    DNSCallback dns_callback = std::bind(&GssTsigDNSUpdateTest::doGssTsigDNSUpdate, this);
    NSUpdateTestCallback callback(io_service_, dns_callback);

    system_clock::time_point now = system_clock::now();
    key_->setInception(now);
    key_->setExpire(now + seconds(server->getKeyLifetime()));
    key_->getTKeyExchange().reset(new TKeyExchange(io_service_, server, key_,
                                                   &callback));
    key_->getTKeyExchange()->doExchange();

    // The server will sign both the TKEY and the DNS update.
    DummyDNSServer dns_server(io_service_);
    dns_server.start();
    io_service_->run();
    ASSERT_TRUE(success_);
    // Check statistics.
    StatMap stats_key = {
        { "update-sent", 1},
        { "update-success", 1},
        { "update-timeout", 0},
        { "update-error", 0}
    };
    checkStats(key_name, stats_key);
    StatMap stats_upd = {
        { "update-sent", 1},
        { "update-signed", 1},
        { "update-unsigned", 0},
        { "update-success", 1},
        { "update-timeout", 0},
        { "update-error", 0}
    };
    checkStats(stats_upd);
}

/// @brief Check GSS-TSIG DNS update succeeds.
TEST_F(GssTsigDNSUpdateTest, runGssTsigDNSUpdateSuccessWithFallback) {
    string key_name("1234.sig-blu.example.nil.");
    key_.reset(new ManagedKey(key_name));
    DnsServerPtr server(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                      TEST_PORT));
    server->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    server->setKeyProto(IOFetch::Protocol::UDP);
    use_fallback_ = true;
    setKeytab();
    setAdministratorCCache();

    DNSCallback dns_callback = std::bind(&GssTsigDNSUpdateTest::doGssTsigDNSUpdate, this);
    NSUpdateTestCallback callback(io_service_, dns_callback);

    system_clock::time_point now = system_clock::now();
    key_->setInception(now);
    key_->setExpire(now + seconds(server->getKeyLifetime()));
    key_->getTKeyExchange().reset(new TKeyExchange(io_service_, server, key_,
                                                   &callback));
    key_->getTKeyExchange()->doExchange();

    // The server will sign the TKEY, but not sign the DNS update.
    DummyDNSServer dns_server(io_service_, true, false);
    dns_server.start();
    io_service_->run();
    ASSERT_TRUE(success_);
    // Check statistics.
    StatMap stats_key = {
        { "update-sent", 0},
        { "update-success", 0},
        { "update-timeout", 0},
        { "update-error", 0}
    };
    checkStats(key_name, stats_key);
    StatMap stats_upd = {
        { "update-sent", 1},
        { "update-signed", 0},
        { "update-unsigned", 1},
        { "update-success", 1},
        { "update-timeout", 0},
        { "update-error", 0}
    };
    checkStats(stats_upd);
}

}
