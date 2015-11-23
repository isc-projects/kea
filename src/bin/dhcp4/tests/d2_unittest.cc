// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <dhcp/iface_mgr.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/tests/d2_unittest.h>
#include <dhcpsrv/cfgmgr.h>

#include <gtest/gtest.h>

#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;

namespace isc {
namespace dhcp {
namespace test {

void
D2Dhcpv4Srv::d2ClientErrorHandler(const
                                dhcp_ddns::NameChangeSender::Result result,
                                dhcp_ddns::NameChangeRequestPtr& ncr) {
    ++error_count_;
    // call base class error handler
    Dhcpv4Srv::d2ClientErrorHandler(result, ncr);
}

const bool Dhcp4SrvD2Test::SHOULD_PASS;
const bool Dhcp4SrvD2Test::SHOULD_FAIL;

Dhcp4SrvD2Test::Dhcp4SrvD2Test() : rcode_(-1) {
}

Dhcp4SrvD2Test::~Dhcp4SrvD2Test() {
    reset();
}

dhcp_ddns::NameChangeRequestPtr
Dhcp4SrvD2Test::buildTestNcr(uint32_t dhcid_id_num) {
    // Build an NCR from json string.
    std::ostringstream stream;

    stream <<
        "{"
        " \"change-type\" : 0 , "
        " \"forward-change\" : true , "
        " \"reverse-change\" : false , "
        " \"fqdn\" : \"myhost.example.com.\" , "
        " \"ip-address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \""

        << std::hex << std::setfill('0') << std::setw(16)
        << dhcid_id_num << "\" , "

        " \"lease-expires-on\" : \"20140121132405\" , "
        " \"lease-length\" : 1300 "
        "}";

    return (dhcp_ddns::NameChangeRequest::fromJSON(stream.str()));
}

void
Dhcp4SrvD2Test::reset() {
    std::string config = "{ \"interfaces-config\": {"
            "    \"interfaces\": [ \"*\" ]"
            "},"
            "\"hooks-libraries\": [ ], "
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"valid-lifetime\": 4000, "
            "\"subnet4\": [ ], "
            "\"dhcp-ddns\": { \"enable-updates\" : false }, "
            "\"option-def\": [ ], "
            "\"option-data\": [ ] }";
    configure(config, SHOULD_PASS);
}

void
Dhcp4SrvD2Test::configureD2(bool enable_d2, const bool exp_result,
                            const std::string& server_ip,
                            const size_t port,
                            const std::string& sender_ip,
                            const size_t sender_port,
                            const size_t max_queue_size) {
    std::ostringstream config;
    config <<
        "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : " << (enable_d2 ? "true" : "false") <<  ", "
        "     \"server-ip\" : \"" << server_ip << "\", "
        "     \"server-port\" : " << port << ", "
        "     \"sender-ip\" : \"" << sender_ip << "\", "
        "     \"sender-port\" : " << sender_port << ", "
        "     \"max-queue-size\" : " << max_queue_size << ", "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"always-include-fqdn\" : true, "
        "     \"allow-client-update\" : true, "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" },"
        "\"valid-lifetime\": 4000 }";

    configure(config.str(), exp_result);
}

void
Dhcp4SrvD2Test::configure(const std::string& config, bool exp_result) {
    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    CfgMgr::instance().clear();

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv_, json));
    ASSERT_TRUE(status);

    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    if (exp_result == SHOULD_PASS) {
        ASSERT_EQ(0, rcode);
    } else {
        ASSERT_EQ(1, rcode);
    }
}

// Tests ability to turn on and off ddns updates by submitting
// by submitting the appropriate configuration to Dhcp4 server
// and then invoking its startD2() method.
TEST_F(Dhcp4SrvD2Test, enableDisable) {
    // Grab the manager and verify that be default ddns is off
    // and a sender was not started.
    dhcp::D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    ASSERT_FALSE(mgr.ddnsEnabled());
    ASSERT_FALSE(mgr.amSending());

    // Verify a valid config with ddns enabled configures ddns properly,
    // but does not start the sender.
    ASSERT_NO_FATAL_FAILURE(configureD2(true));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_FALSE(mgr.amSending());

    // Verify that calling start does not throw and starts the sender.
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Verify a valid config with ddns disabled configures ddns properly.
    // Sender should not have been started.
    ASSERT_NO_FATAL_FAILURE(configureD2(false));
    ASSERT_FALSE(mgr.ddnsEnabled());
    ASSERT_FALSE(mgr.amSending());

    // Verify that the sender does NOT get started when ddns is disabled.
    srv_.startD2();
    ASSERT_FALSE(mgr.amSending());
}

// Tests Dhcp4 server's ability to correctly handle a flawed dhcp-ddns
// configuration.  It does so by first enabling updates by submitting a valid
// configuration and then ensuring they remain on after submitting a flawed
// configuration and then invoking its startD2() method.
TEST_F(Dhcp4SrvD2Test, badConfig) {
    // Grab the manager and verify that be default ddns is off
    // and a sender was not started.
    dhcp::D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    ASSERT_FALSE(mgr.ddnsEnabled());

    // Configure it enabled and start it.
    ASSERT_NO_FATAL_FAILURE(configureD2(true));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Now attempt to give it an invalid configuration.
    // Result should indicate failure.
    ASSERT_NO_FATAL_FAILURE(configureD2(false, SHOULD_FAIL, "bogus_ip"));

    // Configure was not altered, so ddns should be enabled and still sending.
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_TRUE(mgr.amSending());

    // Verify that calling start does not throw or stop the sender.
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

}

// Checks that submitting an identical dhcp-ddns configuration
// is handled properly.  Not effect should be no change in
// status for ddns updating.  Updates should still enabled and
// in send mode.  This indicates that the sender was not stopped.
TEST_F(Dhcp4SrvD2Test, sameConfig) {
    // Grab the manager and verify that be default ddns is off
    // and a sender was not started.
    dhcp::D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    ASSERT_FALSE(mgr.ddnsEnabled());

    // Configure it enabled and start it.
    ASSERT_NO_FATAL_FAILURE(configureD2(true));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Now submit an identical configuration.
    ASSERT_NO_FATAL_FAILURE(configureD2(true));

    // Configuration was not altered, so ddns should still enabled and sending.
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_TRUE(mgr.amSending());

    // Verify that calling start does not throw or stop the sender.
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());
}

// Checks that submitting an different, but valid dhcp-ddns configuration
// is handled properly.  Updates should be enabled, however they should
// not yet be running.  This indicates that the sender was stopped and
// replaced, but not yet started.
TEST_F(Dhcp4SrvD2Test, differentConfig) {
    // Grab the manager and verify that be default ddns is off
    // and a sender was not started.
    dhcp::D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    ASSERT_FALSE(mgr.ddnsEnabled());

    // Configure it enabled and start it.
    ASSERT_NO_FATAL_FAILURE(configureD2(true));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Now enable it on a different port.
    ASSERT_NO_FATAL_FAILURE(configureD2(true, SHOULD_PASS, "127.0.0.1", 54001));

    // Configuration was altered, so ddns should still enabled but not sending.
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_FALSE(mgr.amSending());

    // Verify that calling start starts the sender.
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());
}

// Checks that given a valid, enabled configuration and placing
// sender in send mode, permits NCR requests to be sent via UPD
// socket.  Note this test does not employ any sort of receiving
// client to verify actual transmission.  These types of tests
// are including under dhcp_ddns and d2 unit testing.
TEST_F(Dhcp4SrvD2Test, simpleUDPSend) {
    // Grab the manager and verify that be default ddns is off
    // and a sender was not started.
    dhcp::D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    ASSERT_FALSE(mgr.ddnsEnabled());

    // Configure it enabled and start it.
    ASSERT_NO_FATAL_FAILURE(configureD2(true));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Verify that we can queue up a message.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(mgr.sendRequest(ncr));
    EXPECT_EQ(1, mgr.getQueueSize());

    // Calling receive should detect the ready IO on the sender's select-fd,
    // and invoke callback, which should complete the send.
    ASSERT_NO_THROW(IfaceMgr::instance().receive4(0,0));

    // Verify the queue is now empty.
    EXPECT_EQ(0, mgr.getQueueSize());
}

// Checks that an IO error in sending a request to D2, results in ddns updates
// being suspended.  This indicates that Dhcp4Srv's error handler has been
// invoked as expected.  Note that this unit test relies on an attempt to send
// to a server address of 0.0.0.0 port 0 fails, which it does  under all OSes
// except Solaris 11.
/// @todo Eventually we should find a way to test this under Solaris.
#ifndef OS_SOLARIS
TEST_F(Dhcp4SrvD2Test, forceUDPSendFailure) {
#else
TEST_F(Dhcp4SrvD2Test, DISABLED_forceUDPSendFailure) {
#endif
    // Grab the manager and verify that be default ddns is off
    // and a sender was not started.
    dhcp::D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    ASSERT_FALSE(mgr.ddnsEnabled());

    // Configure it enabled and start it.
    // Using server address of 0.0.0.0/0 should induce failure on send.
    // Pass in a non-zero sender port to avoid validation error when
    // server-ip/port are same as sender-ip/port
    ASSERT_NO_FATAL_FAILURE(configureD2(true, SHOULD_PASS, "0.0.0.0", 0,
                                        "0.0.0.0", 53001));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Queue up 3 messages.
    for (int i = 0; i < 3; i++) {
        dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr(i + 1);
        ASSERT_NO_THROW(mgr.sendRequest(ncr));
    }
    EXPECT_EQ(3, mgr.getQueueSize());

    // Calling receive should detect the ready IO on the sender's select-fd,
    // and invoke callback, which should complete the send, which should
    // fail.
    ASSERT_NO_THROW(IfaceMgr::instance().receive4(0,0));

    // Verify the error handler was invoked.
    EXPECT_EQ(1, srv_.error_count_);

    // Verify that updates are disabled and we are no longer sending.
    ASSERT_FALSE(mgr.ddnsEnabled());
    ASSERT_FALSE(mgr.amSending());

    // Verify message is still in the queue.
    EXPECT_EQ(3, mgr.getQueueSize());

    // Verify that we can't just restart it.
    /// @todo This may change if we add ability to resume.
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_FALSE(mgr.amSending());

    // Configure it enabled and start it.
    ASSERT_NO_FATAL_FAILURE(configureD2(true));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Verify message is still in the queue.
    EXPECT_EQ(3, mgr.getQueueSize());

    // This will finish sending the 1st message in queue
    // and initiate send of 2nd message.
    ASSERT_NO_THROW(IfaceMgr::instance().receive4(0,0));
    EXPECT_EQ(1, srv_.error_count_);

    // First message is off the queue.
    EXPECT_EQ(2, mgr.getQueueSize());
}

// Tests error handling of D2ClientMgr::sendRequest() failure
// by attempting to queue maximum number of messages.
TEST_F(Dhcp4SrvD2Test, queueMaxError) {
    // Configure it enabled and start it.
    dhcp::D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    ASSERT_NO_FATAL_FAILURE(configureD2(true));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_NO_THROW(srv_.startD2());
    ASSERT_TRUE(mgr.amSending());

    // Attempt to queue more then the maximum allowed.
    int max_msgs = mgr.getQueueMaxSize();
    for (int i = 0; i < max_msgs + 1; i++) {
        dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr(i + 1);
        ASSERT_NO_THROW(mgr.sendRequest(ncr));
    }

    // Stopping sender will complete the first message so there
    // should be max less one.
    EXPECT_EQ(max_msgs - 1, mgr.getQueueSize());

    // Verify the error handler was invoked.
    EXPECT_EQ(1, srv_.error_count_);

    // Verify that updates are disabled and we are no longer sending.
    ASSERT_FALSE(mgr.ddnsEnabled());
    ASSERT_FALSE(mgr.amSending());
}


} // namespace test
} // namespace dhcp
} // namespace isc

