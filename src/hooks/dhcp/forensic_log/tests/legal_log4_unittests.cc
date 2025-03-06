// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify DHCPv4 legal file entry
/// generation as well as tests which exercise v4 callouts: leases4_committed
/// and pkt4_send.  These tests assume the legal log library
/// is linked in, not loaded.  This allows a great deal more flexibility
/// in testing, such as overriding and accessing the LegalLogMgrFactory::instance().
/// The load and unload callouts are exercised in ../libloadtests, which
/// actually uses the HooksManager to load and unload the library.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_space.h>
#include <test_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace hooks;
using namespace legal_log;

extern std::string genLease4Entry(CalloutHandle& handle,
                                  const Pkt4Ptr& query,
                                  const Pkt4Ptr& response,
                                  const Lease4Ptr& lease,
                                  const Action& action);

extern int legalLog4Handler(CalloutHandle& handle, const Action& action);

extern "C" {
extern int pkt4_receive(CalloutHandle& handle);
extern int leases4_committed(CalloutHandle& handle);
extern int pkt4_send(CalloutHandle& handle);
extern int lease4_release(CalloutHandle& handle);
extern int lease4_decline(CalloutHandle& handle);
}

namespace {

/// @brief Test fixture
struct CalloutTestv4 : CalloutTest {
    /// @brief Constructor. Called at the beginning of the test suite.
    CalloutTestv4() {
        // Get rid of new lines, they are not supported by the expression
        // evaluator.
        boost::replace_all(request_format_, "\n", std::string());
        boost::replace_all(response_format_, "\n", std::string());
        boost::replace_all(request_format_only_, "\n", std::string());
    }

    /// @brief Called before each test.
    virtual void SetUp() override {
        RotatingFileTest::SetUp();
        // Various entities used in tests.
        client_id_ = boost::make_shared<ClientId>(CLIENTID);
        hwaddr_ = boost::make_shared<HWAddr>(HWADDR, HTYPE_ETHER);
        lease_ = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr());
        discover_ = discover();
        request_ = request();
        response_ = response();
        release_ = release();
        decline_ = decline();
    }

    /// @brief Used to construct a DHCPDISCOVER.
    Pkt4Ptr discover() {
        OptionPtr const requested_address(OptionPtr(boost::make_shared<Option>(
            Option::V4, DHO_DHCP_REQUESTED_ADDRESS, OptionBuffer())));
        requested_address->setUint32(lease_->addr_.toUint32());

        OptionPtr lease_time(
            boost::make_shared<OptionUint32>(Option::V4, DHO_DHCP_LEASE_TIME,
                                             lease_->valid_lft_));

        Pkt4Ptr discover(boost::make_shared<Pkt4>(DHCPDISCOVER, 0x77));
        discover->setHWAddr(hwaddr_);
        discover->addOption(requested_address);
        discover->addOption(lease_time);

        return (discover);
    }

    /// @brief Used to construct a DHCPREQUEST.
    Pkt4Ptr request() {
        OptionPtr const requested_address(OptionPtr(boost::make_shared<Option>(
            Option::V4, DHO_DHCP_REQUESTED_ADDRESS, OptionBuffer())));
        requested_address->setUint32(lease_->addr_.toUint32());

        OptionPtr lease_time(
            boost::make_shared<OptionUint32>(Option::V4, DHO_DHCP_LEASE_TIME,
                                             lease_->valid_lft_));

        Pkt4Ptr request(boost::make_shared<Pkt4>(DHCPREQUEST, 0x77));
        request->setHWAddr(hwaddr_);
        request->addOption(requested_address);
        request->addOption(lease_time);

        return (request);
    }

    /// @brief Used to construct a DHCPACK.
    Pkt4Ptr response() {
        OptionPtr lease_time(
            boost::make_shared<OptionUint32>(Option::V4, DHO_DHCP_LEASE_TIME,
                                             lease_->valid_lft_));

        Pkt4Ptr response(boost::make_shared<Pkt4>(DHCPACK, 0x77));
        response->setHWAddr(hwaddr_);
        response->setYiaddr(lease_->addr_);
        response->addOption(lease_time);

        return (response);
    }

    /// @brief Used to construct a DHCPRELEASE.
    Pkt4Ptr release() {
        Pkt4Ptr release(boost::make_shared<Pkt4>(DHCPRELEASE, 0x77));
        release->setHWAddr(hwaddr_);
        release->setCiaddr(lease_->addr_);

        return (release);
    }

    /// @brief Used to construct a DHCPDECLINE.
    Pkt4Ptr decline() {
        OptionPtr const requested_address(OptionPtr(boost::make_shared<Option>(
            Option::V4, DHO_DHCP_REQUESTED_ADDRESS, OptionBuffer())));
        requested_address->setUint32(lease_->addr_.toUint32());

        Pkt4Ptr decline(boost::make_shared<Pkt4>(DHCPDECLINE, 0x77));
        decline->setHWAddr(hwaddr_);
        decline->addOption(requested_address);

        return (decline);
    }

    /// @brief Convenience function which creates a Lease4 instance
    ///
    /// Factory for creating leases which defaults values that are not of
    /// interest during legal entry formation.
    ///
    /// @param addr_str IPv4 lease address as a string
    /// @param valid_lifetime Lifetime of the lease in seconds
    /// @param hwaddr Pointer to the lease hardware address
    /// @param client_id Pointer to the lease client id (may be null)
    /// @param subnet_id subnet identifier.
    ///
    /// @return Pointer to the newly created Lease4 instance
    Lease4Ptr createLease4(const std::string& addr_str,
                           uint32_t valid_lifetime,
                           const HWAddrPtr& hwaddr,
                           const ClientIdPtr& client_id,
                           const uint32_t subnet_id = 0) {
        Lease4Ptr lease(new Lease4(isc::asiolink::IOAddress(addr_str), hwaddr,
                                   client_id, valid_lifetime, 0, subnet_id,
                                   false, false, std::string()));

        return (lease);
    }

    /// @brief Various entities used in tests
    /// @{

    /// @brief The client id used by requests and replies
    ClientIdPtr client_id_;

    /// @brief The client HWAddr used by requests and replies
    HWAddrPtr hwaddr_;

    /// @brief The lease used by requests and replies
    Lease4Ptr lease_;

    /// @brief The discover packet
    Pkt4Ptr discover_;

    /// @brief The request packet
    Pkt4Ptr request_;

    /// @brief The server response packet
    Pkt4Ptr response_;

    /// @brief The release packet
    Pkt4Ptr release_;

    /// @brief The decline packet
    Pkt4Ptr decline_;
    /// @}

    /// @brief the string to be passed in "request-parser-format"
    std::string request_format_ = R"delimiter(
        ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7,
            'Address: ' +
            ifelse(option[50].exists,
                addrtotext(option[50].hex),
                addrtotext(pkt4.ciaddr)) +
            ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
            ifelse(option[61].exists,
                ', client-id: ' + hexstring(option[61].hex, ':'),
                '') +
            ifelse(pkt4.giaddr == 0.0.0.0,
                '',
                ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                ifelse(option[82].option[1].exists,
                    ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                    '') +
                ifelse(option[82].option[2].exists,
                    ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                    '') +
                ifelse(option[82].option[6].exists,
                    ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                    '')),
            '')
        )delimiter";

    /// @brief the string to be passed in "response-parser-format"
    std::string response_format_ = R"delimiter(
        ifelse(pkt4.msgtype == 5,
            'Address: ' + addrtotext(pkt4.yiaddr) + ' has been assigned for ' + uint32totext(option[51].hex) + ' seconds to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
            ifelse(option[61].exists,
                ', client-id: ' + hexstring(option[61].hex, ':'),
                '') +
            ifelse(pkt4.giaddr == 0.0.0.0,
                '',
                ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                ifelse(option[82].option[1].exists,
                    ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                    '') +
                ifelse(option[82].option[2].exists,
                    ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                    '') +
                ifelse(option[82].option[6].exists,
                    ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                    '')),
            '')
        )delimiter";

    /// @brief the string to be passed in "request-parser-format" with the
    /// equivalent effects of a "response-parser-format" 2-in-1.
    std::string request_format_only_ = R"delimiter(
        ifelse(pkt4.msgtype == 3,
            'Address: ' +
            ifelse(option[50].exists,
                addrtotext(option[50].hex),
                addrtotext(pkt4.ciaddr)) +
            ' has been assigned' +
            ifelse(option[51].exists,
                ' for ' + uint32totext(option[51].hex) + ' seconds',
                '') +
            ' to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
            ifelse(option[61].exists,
                ', client-id: ' + hexstring(option[61].hex, ':'),
                '') +
            ifelse(pkt4.giaddr == 0.0.0.0,
                '',
                ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                ifelse(option[82].option[1].exists,
                    ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                    '') +
                ifelse(option[82].option[2].exists,
                    ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                    '') +
                ifelse(option[82].option[6].exists,
                    ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                    '')),
            ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7,
                'Address: ' +
                ifelse(option[50].exists,
                    addrtotext(option[50].hex),
                    addrtotext(pkt4.ciaddr)) +
                ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                ifelse(option[61].exists,
                    ', client-id: ' + hexstring(option[61].hex, ':'),
                    '') +
                ifelse(pkt4.giaddr == 0.0.0.0,
                    '',
                    ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                    ifelse(option[82].option[1].exists,
                        ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                        '') +
                    ifelse(option[82].option[2].exists,
                        ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                        '') +
                    ifelse(option[82].option[6].exists,
                        ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                        '')),
                ''))
        )delimiter";

    /// @brief Client id used by different tests.
    std::vector<uint8_t> const CLIENTID = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};

    /// @brief Hardware address used by different tests.
    std::vector<uint8_t> const HWADDR = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};
};

// Verifies legal entry content for directly connected clients
TEST_F(CalloutTestv4, directClient4) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    std::string entry;

    // Verify address and duration for an assignment (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address and duration for a renewal (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a release (no client id). No server response.
    ASSERT_NO_THROW(entry = genLease4Entry(handle, release_, Pkt4Ptr(), lease_, Action::RELEASE));
    EXPECT_EQ("Address: 192.2.1.100 has been released"
              " from a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a decline (no client id). No server response.
    ASSERT_NO_THROW(entry = genLease4Entry(handle, decline_, Pkt4Ptr(), lease_, Action::RELEASE));
    EXPECT_EQ("Address: 192.2.1.100 has been released"
              " from a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify with a client id
    lease_->client_id_ = client_id_;

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54",
              entry);

    // Verify a relayed request (no RAI)
    request_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option. This option is represented
    // by OptionCustom which requires a definition to be passed to
    // the constructor.
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));

    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));
    rai->addOption(circuit_id_opt);

    request_->addOption(rai);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79 (howdy)",
              entry);

    uint8_t subscriber_id[] = { 0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f };
    OptionPtr subscriber_id_opt(new Option(Option::V4, RAI_OPTION_SUBSCRIBER_ID,
                                           OptionBuffer(subscriber_id,
                                           subscriber_id
                                           + sizeof(subscriber_id))));
    rai->addOption(subscriber_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79 (howdy)"
              " and subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                       remote_id + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79 (howdy)"
              " and remote-id: 87:f6:79:77:ef"
              " and subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    lease_->setContext(Element::fromJSON("{ \"foo\": true }"));

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79 (howdy)"
              " and remote-id: 87:f6:79:77:ef"
              " and subscriber-id: 1a:2b:3c:4d:5e:6f, "
              "context: { \"foo\": true }",
              entry);
}

// Verifies legal entry content for directly connected clients
TEST_F(CalloutTestv4, directClient4CustomLoggingFormatRequestOnly) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    LegalLogMgrFactory::instance()->setRequestFormatExpression(request_format_only_);

    std::string entry;

    // Verify address and duration for an assignment (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address and duration for a renewal (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a release (no client id). No server response.
    ASSERT_NO_THROW(entry = genLease4Entry(handle, release_, Pkt4Ptr(), lease_, Action::RELEASE));
    EXPECT_EQ("Address: 192.2.1.100 has been released"
              " from a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a decline (no client id). No server response.
    ASSERT_NO_THROW(entry = genLease4Entry(handle, decline_, Pkt4Ptr(), lease_, Action::RELEASE));
    EXPECT_EQ("Address: 192.2.1.100 has been released"
              " from a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a discover
    response_->setType(DHCPOFFER);
    ASSERT_NO_THROW(entry = genLease4Entry(handle, discover_, response_, lease_, Action::ASSIGN));
    EXPECT_TRUE(entry.empty());
    response_->setType(DHCPACK);

    // Verify with a client id
    lease_->client_id_ = client_id_;

    OptionPtr client_id_option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                          client_id_->getClientId()));

    request_->addOption(client_id_option);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54",
              entry);

    // Verify a relayed request (no RAI)
    request_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option. This option is represented
    // by OptionCustom which requires a definition to be passed to
    // the constructor.
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));

    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));
    rai->addOption(circuit_id_opt);

    request_->addOption(rai);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79",
              entry);

    uint8_t subscriber_id[] = { 0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f };
    OptionPtr subscriber_id_opt(new Option(Option::V4, RAI_OPTION_SUBSCRIBER_ID,
                                           OptionBuffer(subscriber_id,
                                           subscriber_id
                                           + sizeof(subscriber_id))));
    rai->addOption(subscriber_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                       remote_id + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79"
              ", remote-id: 87:f6:79:77:ef"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);
}

// Verifies legal entry content for directly connected clients
TEST_F(CalloutTestv4, directClient4CustomLoggingFormatRequestAndResponse) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    LegalLogMgrFactory::instance()->setRequestFormatExpression(request_format_);
    LegalLogMgrFactory::instance()->setResponseFormatExpression(response_format_);

    std::string entry;

    // Verify address and duration for an assignment (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address and duration for a renewal (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a release (no client id). No server response.
    ASSERT_NO_THROW(entry = genLease4Entry(handle, release_, Pkt4Ptr(), lease_, Action::RELEASE));
    EXPECT_EQ("Address: 192.2.1.100 has been released"
              " from a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a decline (no client id). No server response.
    ASSERT_NO_THROW(entry = genLease4Entry(handle, decline_, Pkt4Ptr(), lease_, Action::RELEASE));
    EXPECT_EQ("Address: 192.2.1.100 has been released"
              " from a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address for a discover
    response_->setType(DHCPOFFER);
    ASSERT_NO_THROW(entry = genLease4Entry(handle, discover_, response_, lease_, Action::ASSIGN));
    EXPECT_TRUE(entry.empty());
    response_->setType(DHCPACK);

    // Verify with a client id
    lease_->client_id_ = client_id_;

    OptionPtr client_id_option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                          client_id_->getClientId()));

    request_->addOption(client_id_option);
    response_->addOption(client_id_option);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54",
              entry);

    // Verify a relayed request (no RAI)
    request_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    response_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option. This option is represented
    // by OptionCustom which requires a definition to be passed to
    // the constructor.
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));

    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));
    rai->addOption(circuit_id_opt);

    request_->addOption(rai);
    response_->addOption(rai);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79",
              entry);

    uint8_t subscriber_id[] = { 0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f };
    OptionPtr subscriber_id_opt(new Option(Option::V4, RAI_OPTION_SUBSCRIBER_ID,
                                           OptionBuffer(subscriber_id,
                                           subscriber_id
                                           + sizeof(subscriber_id))));
    rai->addOption(subscriber_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                       remote_id + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79"
              ", remote-id: 87:f6:79:77:ef"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);
}

// Verifies legal entry content for relayed clients
// Checks with and without RAI and its suboptions
TEST_F(CalloutTestv4, relayedClient4) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    std::string entry;

    // Verify a relayed request without client id or RAI
    request_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Verify a relayed request with client id, but no RAI
    lease_->client_id_ = client_id_;

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option.
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));

    request_->addOption(rai);

    // Verify a relayed request with RAI but has neither circuit id or remote id
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Create CIRCUIT ID sub-option
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));

    // Verify a relayed request with RAI with only circuit id
    rai->addOption(circuit_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79 (howdy)",
              entry);

    // Verify a relayed request with RAI with both circuit id and remote id
    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                                    remote_id
                                                    + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79 (howdy)"
              " and remote-id: 87:f6:79:77:ef",
              entry);

    // Verify a relayed request with RAI with only remote id
    rai->delOption(RAI_OPTION_AGENT_CIRCUIT_ID);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by remote-id: 87:f6:79:77:ef",
              entry);

    lease_->setContext(Element::fromJSON("{ \"bar\": false }"));
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by remote-id: 87:f6:79:77:ef, "
              "context: { \"bar\": false }",
              entry);
}

// Verifies legal entry content for relayed clients
// Checks with and without RAI and its suboptions
TEST_F(CalloutTestv4, relayedClient4CustomLoggingFormatRequestOnly) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    LegalLogMgrFactory::instance()->setRequestFormatExpression(request_format_only_);

    std::string entry;

    // Verify a relayed request without client id or RAI
    request_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Verify a relayed request with client id, but no RAI
    lease_->client_id_ = client_id_;

    OptionPtr client_id_option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                          client_id_->getClientId()));

    request_->addOption(client_id_option);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option.
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));

    request_->addOption(rai);

    // Verify a relayed request with RAI but has neither circuit id or remote id
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Create CIRCUIT ID sub-option
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));

    // Verify a relayed request with RAI with only circuit id
    rai->addOption(circuit_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79",
              entry);

    // Verify a relayed request with RAI with both circuit id and remote id
    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                                    remote_id
                                                    + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79"
              ", remote-id: 87:f6:79:77:ef",
              entry);

    // Verify a relayed request with RAI with only remote id
    rai->delOption(RAI_OPTION_AGENT_CIRCUIT_ID);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", remote-id: 87:f6:79:77:ef",
              entry);
}

// Verifies legal entry content for relayed clients
// Checks with and without RAI and its suboptions
TEST_F(CalloutTestv4, relayedClient4CustomLoggingFormatRequestAndResponse) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    LegalLogMgrFactory::instance()->setRequestFormatExpression(request_format_);
    LegalLogMgrFactory::instance()->setResponseFormatExpression(response_format_);

    std::string entry;

    // Verify a relayed request without client id or RAI
    request_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    response_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Verify a relayed request with client id, but no RAI
    lease_->client_id_ = client_id_;

    OptionPtr client_id_option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                          client_id_->getClientId()));

    request_->addOption(client_id_option);
    response_->addOption(client_id_option);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option.
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));

    request_->addOption(rai);
    response_->addOption(rai);

    // Verify a relayed request with RAI but has neither circuit id or remote id
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Create CIRCUIT ID sub-option
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));

    // Verify a relayed request with RAI with only circuit id
    rai->addOption(circuit_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79",
              entry);

    // Verify a relayed request with RAI with both circuit id and remote id
    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                                    remote_id
                                                    + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", circuit-id: 68:6f:77:64:79"
              ", remote-id: 87:f6:79:77:ef",
              entry);

    // Verify a relayed request with RAI with only remote id
    rai->delOption(RAI_OPTION_AGENT_CIRCUIT_ID);

    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 6735 seconds"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", remote-id: 87:f6:79:77:ef",
              entry);
}

// Verifies printable items
TEST_F(CalloutTestv4, printable4) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    request_->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    const uint8_t clientid[] = { 0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    lease_->client_id_.reset(new ClientId(clientid, sizeof(clientid)));

    // Add a RAI option.
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));
    request_->addOption(rai);

    // Add a printable CIRCUIT ID sub-option.
    uint8_t circuit_id[] = { 0x46, 0x6f, 0x6f };
    OptionPtr circuit_id_opt(new Option(Option::V4,
                                        RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                                     circuit_id
                                                     + sizeof(circuit_id))));
    rai->addOption(circuit_id_opt);

    // Add a printable REMOTE ID sub-option.
    uint8_t remote_id[] = { 0x42, 0x61, 0x72 };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                                    remote_id
                                                    + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    // Add a printable SUBSCRIBER ID sub-option.
    uint8_t subscriber_id[] = { 0x6f, 0x63, 0x65, 0x61, 0x6e };
    OptionPtr subscriber_id_opt(new Option(Option::V4, RAI_OPTION_SUBSCRIBER_ID,
                                           OptionBuffer(subscriber_id,
                                                        subscriber_id
                                                        + sizeof(subscriber_id))));
    rai->addOption(subscriber_id_opt);

    std::string entry;

    // Verify a relayed request with RAI.
    ASSERT_NO_THROW(entry = genLease4Entry(handle, request_, response_, lease_, Action::ASSIGN));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: "
              "66:6f:6f:62:61:72 (foobar)"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 46:6f:6f (Foo)"
              " and remote-id: 42:61:72 (Bar)"
              " and subscriber-id: 6f:63:65:61:6e (ocean)",
              entry);
}

// Verifies that legalLog4Handler() detects a null LegalLogMgrFactory::instance()
TEST_F(CalloutTestv4, noRotatingFileTest4) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    handle.setArgument("lease4", lease_);
    handle.setArgument("query4", request_);

    // The function should fail when there's no LegalLogMgrFactory::instance().
    int ret;
    ASSERT_NO_THROW(ret = legalLog4Handler(handle, Action::ASSIGN));
    EXPECT_EQ(1, ret);
}

// Verifies that the pkt4_receive callout creates an empty context which can be
// used in all other hook points.
TEST_F(CalloutTestv4, pkt4_receive) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(discover_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet4Ptr subnet2345(new Subnet4(IOAddress("192.2.2.0"), 24, 30, 40, 50, SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet4Ptr subnet3456(new Subnet4(IOAddress("192.2.3.0"), 24, 30, 40, 50, SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr(), 1234);

    Lease4CollectionPtr new_leases(new Lease4Collection());
    Lease4CollectionPtr deleted_leases(new Lease4Collection());

    new_leases->push_back(lease4);

    // The callout should succeed and generate no entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        ASSERT_NO_THROW(ret = pkt4_receive(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", discover_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 192.2.2.123 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease4 = createLease4("192.2.2.123", 6735, hwaddr_, ClientIdPtr(), 2345);

    new_leases->clear();
    new_leases->push_back(lease4);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        ASSERT_NO_THROW(ret = pkt4_receive(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", discover_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Do not log the lease for address 192.2.3.122 and subnet identifier 3456.
    // This should not be logged even though legal logging is explicitly enabled for this subnet.
    lease4 = createLease4("192.2.3.122", 6735, hwaddr_, ClientIdPtr(), 3456);

    new_leases->clear();
    new_leases->push_back(lease4);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        ASSERT_NO_THROW(ret = pkt4_receive(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", discover_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct. We should have no entry.
    std::vector<std::string>lines;

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileNotCreated(genName(today()));
}

// Verifies that the leases4_committed callout
// -# Generates the correct entry in the legal file given a Pkt4 and Lease4
// -# Generates an entry when legal logging is explicitly enabled for a subnet
// -# Does not generate an entry when legal logging is explicitly disabled for
//    a subnet.
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv4, leases4_committed) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(request_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet4Ptr subnet2345(new Subnet4(IOAddress("192.2.2.0"), 24, 30, 40, 50, SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet4Ptr subnet3456(new Subnet4(IOAddress("192.2.3.0"), 24, 30, 40, 50, SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr(), 1234);

    Lease4CollectionPtr new_leases(new Lease4Collection());
    Lease4CollectionPtr deleted_leases(new Lease4Collection());

    new_leases->push_back(lease4);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases4", new_leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        ASSERT_NO_THROW(ret = leases4_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", request_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 192.2.2.123 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease4 = createLease4("192.2.2.123", 6735, hwaddr_, ClientIdPtr(), 2345);

    new_leases->clear();
    new_leases->push_back(lease4);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases4", new_leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        ASSERT_NO_THROW(ret = leases4_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", request_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 192.2.3.122 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease4 = createLease4("192.2.3.122", 6735, hwaddr_, ClientIdPtr(), 3456);

    new_leases->clear();
    new_leases->push_back(lease4);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases4", new_leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        ASSERT_NO_THROW(ret = leases4_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", request_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct. We should have two entries:
    // 192.2.1.111 and 192.2.3.122.
    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.100 has been assigned"
                    " for 1 hrs 52 mins 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    lines.push_back("Address: 192.2.3.122 has been assigned"
                    " for 1 hrs 52 mins 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease4_renew callout generates the correct entry
// in the legal file given a Pkt4 and Lease4
TEST_F(CalloutTestv4, lease4_renew) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(request_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet4Ptr subnet2345(new Subnet4(IOAddress("192.2.2.0"), 24, 30, 40, 50, SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet4Ptr subnet3456(new Subnet4(IOAddress("192.2.3.0"), 24, 30, 40, 50, SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr());

    Lease4CollectionPtr new_leases(new Lease4Collection());
    Lease4CollectionPtr deleted_leases(new Lease4Collection());

    new_leases->push_back(lease4);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases4", new_leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        ASSERT_NO_THROW(ret = leases4_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", request_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 192.2.2.123 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease4 = createLease4("192.2.2.123", 6735, hwaddr_, ClientIdPtr(), 2345);

    new_leases->clear();
    new_leases->push_back(lease4);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases4", new_leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        ASSERT_NO_THROW(ret = leases4_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", request_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 192.2.3.122 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease4 = createLease4("192.2.3.122", 6735, hwaddr_, ClientIdPtr(), 3456);

    new_leases->clear();
    new_leases->push_back(lease4);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases4", new_leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        ASSERT_NO_THROW(ret = leases4_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", request_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.100 has been assigned"
                    " for 1 hrs 52 mins 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    lines.push_back("Address: 192.2.3.122 has been assigned"
                    " for 1 hrs 52 mins 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease4_renew callout generates the correct entry
// in the legal file given a Pkt4 and Lease4
TEST_F(CalloutTestv4, customRequestLoggingFormat_lease4_renew) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(request_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt4.msgtype == 5, concat('Assigned address: ', addrtotext(pkt4.yiaddr)), '')";

    LegalLogMgrFactory::instance()->setResponseFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.101", 6735, hwaddr_, ClientIdPtr());

    Lease4CollectionPtr new_leases(new Lease4Collection());
    Lease4CollectionPtr deleted_leases(new Lease4Collection());

    new_leases->push_back(lease4);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases4", new_leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        ASSERT_NO_THROW(ret = leases4_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", request_);
        handle->setArgument("response4", response_);
        ASSERT_NO_THROW(ret = pkt4_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Assigned address: 192.2.1.100");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease4_release callout generates the correct entry
// in the legal file given a Pkt4 and Lease4
TEST_F(CalloutTestv4, lease4_release) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(release_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet4Ptr subnet2345(new Subnet4(IOAddress("192.2.2.0"), 24, 30, 40, 50, SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet4Ptr subnet3456(new Subnet4(IOAddress("192.2.3.0"), 24, 30, 40, 50, SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr(), 1234);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", release_);
        ASSERT_NO_THROW(ret = lease4_release(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 192.2.2.123 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease4 = createLease4("192.2.2.123", 6735, hwaddr_, ClientIdPtr(), 2345);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", release_);
        ASSERT_NO_THROW(ret = lease4_release(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 192.2.3.122 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease4 = createLease4("192.2.3.122", 6735, hwaddr_, ClientIdPtr(), 3456);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", release_);
        ASSERT_NO_THROW(ret = lease4_release(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.100 has been released"
                    " from a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    lines.push_back("Address: 192.2.3.122 has been released"
                    " from a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease4_release callout generates the correct entry
// in the legal file given a Pkt4 and Lease4
TEST_F(CalloutTestv4, customRequestLoggingFormat_lease4_release) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(release_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt4.msgtype == 7, concat('Released address: ', addrtotext(pkt4.ciaddr)), '')";

    LegalLogMgrFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr(), 1234);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease_);
        handle->setArgument("query4", release_);
        ASSERT_NO_THROW(ret = lease4_release(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Released address: 192.2.1.100");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease4_decline callout generates the correct entry
// in the legal file given a Pkt4 and Lease4
TEST_F(CalloutTestv4, lease4_decline) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(decline_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet4Ptr subnet2345(new Subnet4(IOAddress("192.2.2.0"), 24, 30, 40, 50, SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet4Ptr subnet3456(new Subnet4(IOAddress("192.2.3.0"), 24, 30, 40, 50, SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr(), 1234);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", decline_);
        ASSERT_NO_THROW(ret = lease4_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 192.2.2.123 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease4 = createLease4("192.2.2.123", 6735, hwaddr_, ClientIdPtr(), 2345);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", decline_);
        ASSERT_NO_THROW(ret = lease4_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 192.2.3.122 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease4 = createLease4("192.2.3.122", 6735, hwaddr_, ClientIdPtr(), 3456);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", decline_);
        ASSERT_NO_THROW(ret = lease4_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.100 has been released"
                    " from a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    lines.push_back("Address: 192.2.3.122 has been released"
                    " from a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease4_decline callout generates the correct entry
// in the legal file given a Pkt4 and Lease4
TEST_F(CalloutTestv4, customRequestLoggingFormat_lease4_decline) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(decline_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt4.msgtype == 4, concat('Declined address: ', addrtotext(option[50].hex)), '')";

    LegalLogMgrFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr(), 1234);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", decline_);
        ASSERT_NO_THROW(ret = lease4_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Declined address: 192.2.1.100");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the custom format logs on multiple lines.
TEST_F(CalloutTestv4, customRequestLoggingFormatMultipleLines) {
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(decline_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt4.msgtype == 4, 'first line' + 0x0a + 'second line', '')";

    LegalLogMgrFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr_, ClientIdPtr(), 1234);

    // The callout should succeed and generate an entry for 192.2.1.100.
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease4", lease4);
        handle->setArgument("query4", decline_);
        ASSERT_NO_THROW(ret = lease4_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    LegalLogMgrFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("first line");
    lines.push_back("second line");

    std::string today_now_string = LegalLogMgrFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

} // end of anonymous namespace
