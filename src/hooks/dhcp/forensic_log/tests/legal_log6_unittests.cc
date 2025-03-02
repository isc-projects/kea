// Copyright (C) 2016-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify DHCPv6 legal file entry
/// generation as well as tests which exercise v6 callouts: leases6_committed
/// and pkt6_send.  These tests assume the legal log library
/// is linked in, not loaded.  This allows a great deal more flexibility
/// in testing, such as overriding and accessing the BackendStoreFactory::instance().
/// The load and unload callouts are exercised in ../libloadtests, which
/// actually uses the HooksManager to load and unload the library.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/lease.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <test_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace dhcp;

extern std::string hwaddrSourceToString(uint32_t source);

extern std::string genLease6Entry(CalloutHandle& handle,
                                  const Pkt6Ptr& query,
                                  const Pkt6Ptr& response,
                                  const Lease6Ptr& lease,
                                  const Action& action);

extern int legalLog6Handler(CalloutHandle& handle, const Action& action);

extern "C" {
extern int pkt6_receive(CalloutHandle& handle);
extern int leases6_committed(CalloutHandle& handle);
extern int pkt6_send(CalloutHandle& handle);
extern int lease6_release(CalloutHandle& handle);
extern int lease6_decline(CalloutHandle& handle);
}

namespace {

struct CalloutTestv6 : CalloutTest {
    /// @brief Constructor. Called at the beginning of the test suite.
    CalloutTestv6() {
        // Get rid of new lines, they are not supported by the expression
        // evaluator.
        boost::replace_all(request_format_, "\n", std::string());
        boost::replace_all(response_format_, "\n", std::string());
        boost::replace_all(request_format_only_, "\n", std::string());
    }

    /// @brief Called before each test.
    virtual void SetUp() final override {
        RotatingFileTest::SetUp();
        // Various entities used in tests.
        duid_ = boost::make_shared<DUID>(DUID_DATA);
        hwaddr_ = boost::make_shared<HWAddr>(HWADDR, HTYPE_ETHER);
        hwaddr_->source_ = HWAddr::HWADDR_SOURCE_RAW;
        lease_na_ = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128, 713, HWAddrPtr());
        lease_pd_ = createLease6(duid_, Lease::TYPE_PD, "2001:db8:1::", 64, 713, HWAddrPtr());
        solicit_na_ = createNAMsg(DHCPV6_SOLICIT);
        solicit_pd_ = createPDMsg(DHCPV6_SOLICIT);
        request_na_ = createNAMsg(DHCPV6_REQUEST);
        request_pd_ = createPDMsg(DHCPV6_REQUEST);
        renew_na_ = createNAMsg(DHCPV6_RENEW);
        renew_pd_ = createPDMsg(DHCPV6_RENEW);
        rebind_na_ = createNAMsg(DHCPV6_REBIND);
        rebind_pd_ = createPDMsg(DHCPV6_REBIND);
        response_na_ = createNAMsg(DHCPV6_REPLY);
        response_pd_ = createPDMsg(DHCPV6_REPLY);
        release_na_ = createNAMsg(DHCPV6_RELEASE);
        release_pd_ = createPDMsg(DHCPV6_RELEASE);
        decline_ = decline();
        response_ = response();
    }

    /// @brief Used to construct a NA request/response.
    ///
    /// @brief msg_type The message type to create.
    Pkt6Ptr createNAMsg(uint8_t msg_type) {
        OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, duid_->getDuid()));
        boost::shared_ptr<Option6IA> ia(new Option6IA(D6O_IA_NA, 1234));
        Option6IAAddrPtr addr(new Option6IAAddr(D6O_IAADDR, lease_na_->addr_,
                                                lease_na_->preferred_lft_,
                                                lease_na_->valid_lft_));
        ia->addOption(addr);

        Pkt6Ptr pkt(boost::make_shared<Pkt6>(msg_type, 0x77));
        pkt->addOption(ia);
        pkt->addOption(client_id);

        return (pkt);
    }

    /// @brief Used to construct a PD request/response.
    ///
    /// @brief msg_type The message type to create.
    Pkt6Ptr createPDMsg(uint8_t msg_type) {
        OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, duid_->getDuid()));
        boost::shared_ptr<Option6IA> ia(new Option6IA(D6O_IA_PD, 1234));
        Option6IAPrefixPtr addr(new Option6IAPrefix(D6O_IAPREFIX, lease_pd_->addr_,
                                                    lease_pd_->prefixlen_,
                                                    lease_pd_->preferred_lft_,
                                                    lease_pd_->valid_lft_));
        ia->addOption(addr);

        Pkt6Ptr pkt(boost::make_shared<Pkt6>(msg_type, 0x77));
        pkt->addOption(ia);
        pkt->addOption(client_id);

        return (pkt);
    }

    /// @brief Used to construct a decline.
    Pkt6Ptr decline() {
        OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, duid_->getDuid()));
        boost::shared_ptr<Option6IA> ia(new Option6IA(D6O_IA_NA, 1234));
        Option6IAAddrPtr addr(new Option6IAAddr(D6O_IAADDR, lease_na_->addr_,
                                                lease_na_->preferred_lft_,
                                                lease_na_->valid_lft_));
        ia->addOption(addr);

        Pkt6Ptr decline(boost::make_shared<Pkt6>(DHCPV6_DECLINE, 0x77));
        decline->addOption(ia);
        decline->addOption(client_id);

        return (decline);
    }

    /// @brief Used to construct an empty response.
    Pkt6Ptr response() {
        OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, duid_->getDuid()));

        Pkt6Ptr response(boost::make_shared<Pkt6>(DHCPV6_REPLY, 0x77));

        return (response);
    }

    /// @brief Convenience function which creates a Lease6 instance
    ///
    /// Factory for creating leases which defaults values that are not of
    /// interest during legal entry formation.
    ///
    /// @param duid Pointer to the lease DUID
    /// @param type Type of the lease (TYPE_IA, TYPE_NA, TYPE_PD)
    /// @param addr_str IPv6 lease address/ prefix as a string
    /// @param prefix_len Prefix length
    /// @param valid_lifetime Lifetime of the lease in seconds
    /// @param hwaddr Pointer to the lease hardware address (may be null)
    /// @param subnet_id subnet identifier.
    /// @param iaid The lease IAID
    ///
    /// @return Pointer to the newly created Lease6 instance
    Lease6Ptr createLease6(const DuidPtr& duid, const Lease::Type& type,
                           const std::string& addr_str, uint8_t prefix_len,
                           uint32_t valid_lifetime, const HWAddrPtr& hwaddr,
                           const uint32_t subnet_id = 0, uint32_t iaid = 1234) {
        Lease6Ptr lease(new Lease6(type, isc::asiolink::IOAddress(addr_str),
                                   duid, iaid, 0, valid_lifetime, subnet_id,
                                   hwaddr, prefix_len));
        return (lease);
    }

    /// @brief Various entities used in tests
    /// @{

    /// @brief The DUID used by requests and replies
    DuidPtr duid_;

    /// @brief The client HWAddr used by requests and replies
    HWAddrPtr hwaddr_;

    /// @brief The lease NA used by requests and replies
    Lease6Ptr lease_na_;

    /// @brief The lease PD used by requests and replies
    Lease6Ptr lease_pd_;

    /// @brief The solicit NA packet
    Pkt6Ptr solicit_na_;

    /// @brief The solicit PD packet
    Pkt6Ptr solicit_pd_;

    /// @brief The request NA packet
    Pkt6Ptr request_na_;

    /// @brief The request PD packet
    Pkt6Ptr request_pd_;

    /// @brief The renew NA packet
    Pkt6Ptr renew_na_;

    /// @brief The renew PD packet
    Pkt6Ptr renew_pd_;

    /// @brief The rebind NA packet
    Pkt6Ptr rebind_na_;

    /// @brief The rebind PD packet
    Pkt6Ptr rebind_pd_;

    /// @brief The server NA response packet
    Pkt6Ptr response_na_;

    /// @brief The server PD response packet
    Pkt6Ptr response_pd_;

    /// @brief The release NA packet
    Pkt6Ptr release_na_;

    /// @brief The release PD packet
    Pkt6Ptr release_pd_;

    /// @brief The decline packet
    Pkt6Ptr decline_;

    /// @brief The response packet
    Pkt6Ptr response_;
    /// @}

    /// @brief the string to be passed in "request-parser-format"
    std::string request_format_ = R"delimiter(
        ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9,
            ifelse(option[3].option[5].exists,
                'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                ifelse(relay6[0].peeraddr == '',
                    '',
                    ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                    ifelse(relay6[0].option[37].exists,
                        ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[38].exists,
                        ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[18].exists,
                        ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                        '')),
                '') +
            ifelse(option[25].option[26].exists,
                'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                ifelse(relay6[0].peeraddr == '',
                    '',
                    ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                    ifelse(relay6[0].option[37].exists,
                        ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[38].exists,
                        ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[18].exists,
                        ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                        '')),
                ''),
            '')
        )delimiter";

    /// @brief the string to be passed in "response-parser-format"
    std::string response_format_ = R"delimiter(
        ifelse(pkt6.msgtype == 7,
            ifelse(option[3].option[5].exists and not (substring(option[3].option[5].hex, 20, 4) == 0),
                'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                ifelse(relay6[0].peeraddr == '',
                    '',
                    ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                    ifelse(relay6[0].option[37].exists,
                        ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[38].exists,
                        ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[18].exists,
                        ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                        '')),
                '') +
            ifelse(option[25].option[26].exists and not (substring(option[25].option[26].hex, 4, 4) == 0),
                'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                ifelse(relay6[0].peeraddr == '',
                    '',
                    ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                    ifelse(relay6[0].option[37].exists,
                        ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[38].exists,
                        ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[18].exists,
                        ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                        '')),
                ''),
            '')
        )delimiter";

    /// @brief the string to be passed in "request-parser-format" with the
    /// equivalent effects of a "response-parser-format" 2-in-1.
    std::string request_format_only_ = R"delimiter(
        ifelse(pkt6.msgtype == 3 or pkt6.msgtype == 5 or pkt6.msgtype == 6,
            ifelse(option[3].option[5].exists,
                'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                ifelse(relay6[0].peeraddr == '',
                    '',
                    ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                    ifelse(relay6[0].option[37].exists,
                        ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[38].exists,
                        ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[18].exists,
                        ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                        '')),
                '') +
            ifelse(option[25].option[26].exists,
                'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                ifelse(relay6[0].peeraddr == '',
                    '',
                    ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                    ifelse(relay6[0].option[37].exists,
                        ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[38].exists,
                        ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                        '') +
                    ifelse(relay6[0].option[18].exists,
                        ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                        '')),
                ''),
            ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9,
                ifelse(option[3].option[5].exists,
                    'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    '') +
                ifelse(option[25].option[26].exists,
                    'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    ''),
                ''))
        )delimiter";

    /// @brief DUID used by different tests.
    std::vector<uint8_t> const DUID_DATA = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};

    /// @brief Hardware address used by different tests.
    std::vector<uint8_t> const HWADDR = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};
};

// Verifies that the function hwaddrSourceToString() properly converts
// hardware address sources to strings.
TEST(Lease6FuncTest, hwaddrSourceToString ) {
    EXPECT_EQ("Raw Socket", hwaddrSourceToString(HWAddr::HWADDR_SOURCE_RAW));
    EXPECT_EQ("DUID", hwaddrSourceToString(HWAddr::HWADDR_SOURCE_DUID));
    EXPECT_EQ("IPv6 Link Local",
              hwaddrSourceToString(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL));
    EXPECT_EQ("Client Address Relay Option",
              hwaddrSourceToString(HWAddr
                                   ::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION));
    EXPECT_EQ("Remote ID",
              hwaddrSourceToString(HWAddr::HWADDR_SOURCE_REMOTE_ID));
    EXPECT_EQ("Subscriber ID",
              hwaddrSourceToString(HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID));
    EXPECT_EQ("DOCSIS CMTS",
              hwaddrSourceToString(HWAddr::HWADDR_SOURCE_DOCSIS_CMTS));
    EXPECT_EQ("DOCSIS MODEM",
              hwaddrSourceToString(HWAddr::HWADDR_SOURCE_DOCSIS_MODEM));
    EXPECT_EQ("UNKNOWN", hwaddrSourceToString(0));
    EXPECT_EQ("UNKNOWN",
              hwaddrSourceToString(HWAddr::HWADDR_SOURCE_DOCSIS_MODEM + 1));
}

// Verifies DHCPv6 entries for directly connected clients
TEST_F(CalloutTestv6, directClient6NA) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a renewal
    ASSERT_NO_THROW(entry = genLease6Entry(handle, renew_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a rebind
    ASSERT_NO_THROW(entry = genLease6Entry(handle, rebind_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a release
    ASSERT_NO_THROW(entry = genLease6Entry(handle, release_na_, response_, lease_na_, Action::RELEASE));
    EXPECT_EQ("Address: 2001:db8:1:: has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a decline
    ASSERT_NO_THROW(entry = genLease6Entry(handle, decline_, response_, lease_na_, Action::RELEASE));
    EXPECT_EQ("Address: 2001:db8:1:: has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Add in hardware address and verify.  We do need to explicitly test each
    // possible value for hardware source as the function which converts it
    // is tested explicitly.
    lease_na_->hwaddr_ = hwaddr_;
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54 and hardware"
              " address: hwtype=1 08:00:2b:02:3f:4e (from Raw Socket)",
              entry);

    // Add user context.
    lease_na_->setContext(Element::fromJSON("{ \"foo\": true }"));
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54 and hardware"
              " address: hwtype=1 08:00:2b:02:3f:4e (from Raw Socket),"
              " context: { \"foo\": true }",
              entry);
}

// Verifies DHCPv6 entries for directly connected clients
TEST_F(CalloutTestv6, directClient6NACustomLoggingFormatRequestOnly) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_only_);

    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a renewal
    ASSERT_NO_THROW(entry = genLease6Entry(handle, renew_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a rebind
    ASSERT_NO_THROW(entry = genLease6Entry(handle, rebind_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a release
    ASSERT_NO_THROW(entry = genLease6Entry(handle, release_na_, response_, lease_na_, Action::RELEASE));
    EXPECT_EQ("Address: 2001:db8:1:: has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a decline
    ASSERT_NO_THROW(entry = genLease6Entry(handle, decline_, response_, lease_na_, Action::RELEASE));
    EXPECT_EQ("Address: 2001:db8:1:: has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a solicit
    ASSERT_NO_THROW(entry = genLease6Entry(handle, solicit_na_, response_na_, lease_na_, Action::RELEASE));
    EXPECT_TRUE(entry.empty());
}

// Verifies DHCPv6 entries for directly connected clients
TEST_F(CalloutTestv6, directClient6NACustomLoggingFormatRequestAndResponse) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_);
    BackendStoreFactory::instance()->setResponseFormatExpression(response_format_);

    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a renewal
    ASSERT_NO_THROW(entry = genLease6Entry(handle, renew_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a rebind
    ASSERT_NO_THROW(entry = genLease6Entry(handle, rebind_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a release
    ASSERT_NO_THROW(entry = genLease6Entry(handle, release_na_, response_, lease_na_, Action::RELEASE));
    EXPECT_EQ("Address: 2001:db8:1:: has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a decline
    ASSERT_NO_THROW(entry = genLease6Entry(handle, decline_, response_, lease_na_, Action::RELEASE));
    EXPECT_EQ("Address: 2001:db8:1:: has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a solicit
    response_na_->setType(DHCPV6_ADVERTISE);
    ASSERT_NO_THROW(entry = genLease6Entry(handle, solicit_na_, response_na_, lease_na_, Action::RELEASE));
    EXPECT_TRUE(entry.empty());
}

// Verifies DHCPv6 entries for relayed clients
TEST_F(CalloutTestv6, relayedClient6NA) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    std::string entry;

    // Verify server level relay basic info, no options
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");

    request_na_->addRelayInfo(relay1);

    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1",
              entry);

    // Next we'll add REMOTE_ID option to the relay info
    const uint8_t rem_data[] = {
        1, 2, 3, 4,  // enterprise-number
        0xa, 0xb, 0xc, 0xd, 0xe, 0xf // MAC
    };

    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(rem_data, rem_data + sizeof(rem_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f",
              entry);

    // Next we'll add SUBSCRIBER_ID option to the relay info
    const uint8_t sub_data[] = {
        0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f
    };

    relay_opt.reset(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                        OptionBuffer(sub_data, sub_data + sizeof(sub_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID and SUBSCRIBER_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f"
              " and subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only SUBSCRIBER_ID
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only INTERFACE_ID
    const string iface_id("relay1:eth0");
    relay_opt.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                               OptionBuffer(iface_id.begin(), iface_id.end())));
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30 (relay1:eth0)",
              entry);

    // Verify user context
    lease_na_->setContext(Element::fromJSON("{ \"bar\": false }"));
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30 (relay1:eth0)"
              ", context: { \"bar\": false }",
              entry);
}

// Verifies DHCPv6 entries for relayed clients
TEST_F(CalloutTestv6, relayedClient6NACustomLoggingFormatRequestOnly) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_only_);

    std::string entry;

    // Verify server level relay basic info, no options
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");

    request_na_->addRelayInfo(relay1);

    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1",
              entry);

    // Next we'll add REMOTE_ID option to the relay info
    const uint8_t rem_data[] = {
        1, 2, 3, 4,  // enterprise-number
        0xa, 0xb, 0xc, 0xd, 0xe, 0xf // MAC
    };

    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(rem_data, rem_data + sizeof(rem_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f",
              entry);

    // Next we'll add SUBSCRIBER_ID option to the relay info
    const uint8_t sub_data[] = {
        0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f
    };

    relay_opt.reset(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                        OptionBuffer(sub_data, sub_data + sizeof(sub_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID and SUBSCRIBER_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only SUBSCRIBER_ID
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only INTERFACE_ID
    const string iface_id("relay1:eth0");
    relay_opt.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                               OptionBuffer(iface_id.begin(), iface_id.end())));
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30",
              entry);
}

// Verifies DHCPv6 entries for relayed clients
TEST_F(CalloutTestv6, relayedClient6NACustomLoggingFormatRequestAndResponse) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_);
    BackendStoreFactory::instance()->setResponseFormatExpression(response_format_);

    std::string entry;

    // Verify server level relay basic info, no options
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");

    request_na_->addRelayInfo(relay1);
    response_na_->addRelayInfo(relay1);

    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1",
              entry);

    // Next we'll add REMOTE_ID option to the relay info
    const uint8_t rem_data[] = {
        1, 2, 3, 4,  // enterprise-number
        0xa, 0xb, 0xc, 0xd, 0xe, 0xf // MAC
    };

    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(rem_data, rem_data + sizeof(rem_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    response_na_->relay_info_.clear();
    response_na_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f",
              entry);

    // Next we'll add SUBSCRIBER_ID option to the relay info
    const uint8_t sub_data[] = {
        0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f
    };

    relay_opt.reset(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                        OptionBuffer(sub_data, sub_data + sizeof(sub_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    response_na_->relay_info_.clear();
    response_na_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID and SUBSCRIBER_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only SUBSCRIBER_ID
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    response_na_->relay_info_.clear();
    response_na_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only INTERFACE_ID
    const string iface_id("relay1:eth0");
    relay_opt.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                               OptionBuffer(iface_id.begin(), iface_id.end())));
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_na_->relay_info_.clear();
    request_na_->addRelayInfo(relay1);

    response_na_->relay_info_.clear();
    response_na_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30",
              entry);
}

// Verifies DHCPv6 entries for directly connected clients
TEST_F(CalloutTestv6, directClient6PD) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a renewal
    ASSERT_NO_THROW(entry = genLease6Entry(handle, renew_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a rebind
    ASSERT_NO_THROW(entry = genLease6Entry(handle, rebind_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a release
    ASSERT_NO_THROW(entry = genLease6Entry(handle, release_pd_, response_, lease_pd_, Action::RELEASE));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Add in hardware address and verify.  We do need to explicitly test each
    // possible value for hardware source as the function which converts it
    // is tested explicitly.
    lease_pd_->hwaddr_ = hwaddr_;
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54 and hardware"
              " address: hwtype=1 08:00:2b:02:3f:4e (from Raw Socket)",
              entry);

    // Add user context.
    lease_pd_->setContext(Element::fromJSON("{ \"foo\": true }"));
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54 and hardware"
              " address: hwtype=1 08:00:2b:02:3f:4e (from Raw Socket),"
              " context: { \"foo\": true }",
              entry);
}

// Verifies DHCPv6 entries for directly connected clients
TEST_F(CalloutTestv6, directClient6PDCustomLoggingFormatRequestOnly) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_only_);

    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a renewal
    ASSERT_NO_THROW(entry = genLease6Entry(handle, renew_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a rebind
    ASSERT_NO_THROW(entry = genLease6Entry(handle, rebind_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a release
    ASSERT_NO_THROW(entry = genLease6Entry(handle, release_pd_, response_, lease_pd_, Action::RELEASE));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a solicit
    ASSERT_NO_THROW(entry = genLease6Entry(handle, solicit_pd_, response_pd_, lease_pd_, Action::RELEASE));
    EXPECT_TRUE(entry.empty());
}

// Verifies DHCPv6 entries for directly connected clients
TEST_F(CalloutTestv6, directClient6PDCustomLoggingFormatRequestAndResponse) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_);
    BackendStoreFactory::instance()->setResponseFormatExpression(response_format_);

    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a renewal
    ASSERT_NO_THROW(entry = genLease6Entry(handle, renew_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a rebind
    ASSERT_NO_THROW(entry = genLease6Entry(handle, rebind_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a release
    ASSERT_NO_THROW(entry = genLease6Entry(handle, release_pd_, response_, lease_pd_, Action::RELEASE));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been released"
              " from a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address for a solicit
    response_pd_->setType(DHCPV6_ADVERTISE);
    ASSERT_NO_THROW(entry = genLease6Entry(handle, solicit_pd_, response_pd_, lease_pd_, Action::RELEASE));
    EXPECT_TRUE(entry.empty());
}

// Verifies DHCPv6 entries for relayed clients
TEST_F(CalloutTestv6, relayedClient6PD) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    std::string entry;

    // Verify server level relay basic info, no options
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");

    request_pd_->addRelayInfo(relay1);

    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1",
              entry);

    // Next we'll add REMOTE_ID option to the relay info
    const uint8_t rem_data[] = {
        1, 2, 3, 4,  // enterprise-number
        0xa, 0xb, 0xc, 0xd, 0xe, 0xf // MAC
    };

    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(rem_data, rem_data + sizeof(rem_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f",
              entry);

    // Next we'll add SUBSCRIBER_ID option to the relay info
    const uint8_t sub_data[] = {
        0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f
    };

    relay_opt.reset(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                        OptionBuffer(sub_data, sub_data + sizeof(sub_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID and SUBSCRIBER_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f"
              " and subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only SUBSCRIBER_ID
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only INTERFACE_ID
    const string iface_id("relay1:eth0");
    relay_opt.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                               OptionBuffer(iface_id.begin(), iface_id.end())));
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30 (relay1:eth0)",
              entry);

    // Verify user context
    lease_pd_->setContext(Element::fromJSON("{ \"bar\": false }"));
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30 (relay1:eth0)"
              ", context: { \"bar\": false }",
              entry);
}

// Verifies DHCPv6 entries for relayed clients
TEST_F(CalloutTestv6, relayedClient6PDCustomLoggingFormatRequestOnly) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_only_);

    std::string entry;

    // Verify server level relay basic info, no options
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");

    request_pd_->addRelayInfo(relay1);

    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1",
              entry);

    // Next we'll add REMOTE_ID option to the relay info
    const uint8_t rem_data[] = {
        1, 2, 3, 4,  // enterprise-number
        0xa, 0xb, 0xc, 0xd, 0xe, 0xf // MAC
    };

    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(rem_data, rem_data + sizeof(rem_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f",
              entry);

    // Next we'll add SUBSCRIBER_ID option to the relay info
    const uint8_t sub_data[] = {
        0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f
    };

    relay_opt.reset(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                        OptionBuffer(sub_data, sub_data + sizeof(sub_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID and SUBSCRIBER_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only SUBSCRIBER_ID
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only INTERFACE_ID
    const string iface_id("relay1:eth0");
    relay_opt.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                               OptionBuffer(iface_id.begin(), iface_id.end())));
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30",
              entry);
}

// Verifies DHCPv6 entries for relayed clients
TEST_F(CalloutTestv6, relayedClient6PDCustomLoggingFormatRequestAndResponse) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_);
    BackendStoreFactory::instance()->setResponseFormatExpression(response_format_);

    std::string entry;

    // Verify server level relay basic info, no options
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");

    request_pd_->addRelayInfo(relay1);
    response_pd_->addRelayInfo(relay1);

    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1",
              entry);

    // Next we'll add REMOTE_ID option to the relay info
    const uint8_t rem_data[] = {
        1, 2, 3, 4,  // enterprise-number
        0xa, 0xb, 0xc, 0xd, 0xe, 0xf // MAC
    };

    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(rem_data, rem_data + sizeof(rem_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    response_pd_->relay_info_.clear();
    response_pd_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f",
              entry);

    // Next we'll add SUBSCRIBER_ID option to the relay info
    const uint8_t sub_data[] = {
        0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f
    };

    relay_opt.reset(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                        OptionBuffer(sub_data, sub_data + sizeof(sub_data))));

    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    response_pd_->relay_info_.clear();
    response_pd_->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID and SUBSCRIBER_ID
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only SUBSCRIBER_ID
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    response_pd_->relay_info_.clear();
    response_pd_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only INTERFACE_ID
    const string iface_id("relay1:eth0");
    relay_opt.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                               OptionBuffer(iface_id.begin(), iface_id.end())));
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    request_pd_->relay_info_.clear();
    request_pd_->addRelayInfo(relay1);

    response_pd_->relay_info_.clear();
    response_pd_->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_pd_, response_pd_, lease_pd_, Action::ASSIGN));
    EXPECT_EQ("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30",
              entry);
}

// Verifies printable id handling
TEST_F(CalloutTestv6, printable6) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");

    // We'll add printable REMOTE_ID option to the relay info
    const uint8_t rem_data[] = { 0x66, 0x6f, 0x6f };
    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(rem_data, rem_data + sizeof(rem_data))));
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    // We'll add printable SUBSCRIBER_ID option to the relay info
    const uint8_t sub_data[] = { 0x62, 0x61, 0x72 };
    relay_opt.reset(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                        OptionBuffer(sub_data, sub_data + sizeof(sub_data))));
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    // We'll add printable INTERFACE_ID option to the relay info
    const string iface_id("relay1:eth0");
    relay_opt.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                        OptionBuffer(iface_id.begin(), iface_id.end())));
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));
    request_na_->addRelayInfo(relay1);

    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(handle, request_na_, response_na_, lease_na_, Action::ASSIGN));
    EXPECT_EQ("Address: 2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by remote-id: 66:6f:6f (foo)"
              " and subscriber-id: 62:61:72 (bar)"
              ", connected at location interface-id: "
              "72:65:6c:61:79:31:3a:65:74:68:30 (relay1:eth0)",
              entry);
}

// Verifies that legalLog6Handler() detects a null BackendStoreFactory::instance()
TEST_F(CalloutTestv6, noRotatingFileTest6) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());
    handle.setCurrentLibrary(0);
    handle.setArgument("lease6", lease_na_);
    handle.setArgument("query6", request_na_);

    // The function should fail when there's no BackendStoreFactory::instance().
    int ret;
    ASSERT_NO_THROW(ret = legalLog6Handler(handle, Action::ASSIGN));
    EXPECT_EQ(1, ret);
}

// Verifies that the pkt6_receive callout creates an empty context which can be
// used in all other hook points.
TEST_F(CalloutTestv6, pkt6_receive) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(solicit_na_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet6Ptr subnet2345(new Subnet6(IOAddress("2001:db8:2::"), 64, 30, 40, 50, 60,
                                      SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet6Ptr subnet3456(new Subnet6(IOAddress("2001:db8:3::"), 64, 30, 40, 50, 60,
                                      SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    new_leases->push_back(lease6);

    // The callout should succeed and generate no entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        ASSERT_NO_THROW(ret = pkt6_receive(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", solicit_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 2001:db8:2::1 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::1", 128, 713, HWAddrPtr(),
                          2345);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        ASSERT_NO_THROW(ret = pkt6_receive(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", solicit_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Do not log the lease for address 2001:db8:3::1 and subnet identifier 3456.
    // This should not be logged even though legal logging is explicitly enabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::1", 128, 713, HWAddrPtr(),
                          3456);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        ASSERT_NO_THROW(ret = pkt6_receive(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", solicit_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileNotCreated(genName(today()));
}

// Verifies that the leases6_committed callout
// -# Does not generate an entry when fake_allocation is true
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// -# Generates an entry when legal logging is explicitly enabled for a subnet
// -# Does not generate an entry when legal logging is explicitly disabled for
//    a subnet.
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, leases6_committed) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(request_na_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet6Ptr subnet2345(new Subnet6(IOAddress("2001:db8:2::"), 64, 30, 40, 50, 60,
                                      SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet6Ptr subnet3456(new Subnet6(IOAddress("2001:db8:3::"), 64, 30, 40, 50, 60,
                                      SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    new_leases->push_back(lease6);

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", request_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 2001:db8:2::1 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::1", 128, 713, HWAddrPtr(),
                          2345);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", request_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 2001:db8:3::1 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::1", 128, 713, HWAddrPtr(),
                          3456);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", request_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 2001:db8:1:: has been assigned"
                    " for 0 hrs 11 mins 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    lines.push_back("Address: 2001:db8:3::1 has been assigned"
                    " for 0 hrs 11 mins 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_renew callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, lease6_renew) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(renew_na_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet6Ptr subnet2345(new Subnet6(IOAddress("2001:db8:2::"), 64, 30, 40, 50, 60,
                                      SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet6Ptr subnet3456(new Subnet6(IOAddress("2001:db8:3::"), 64, 30, 40, 50, 60,
                                      SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    new_leases->push_back(lease6);

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", renew_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 2001:db8:2::1 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::1", 128, 713, HWAddrPtr(),
                          2345);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", renew_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 2001:db8:3::1 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::1", 128, 713, HWAddrPtr(),
                          3456);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", renew_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 2001:db8:1:: has been assigned"
                    " for 0 hrs 11 mins 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    lines.push_back("Address: 2001:db8:3::1 has been assigned"
                    " for 0 hrs 11 mins 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_renew callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, customRequestLoggingFormat_lease6_renew) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(renew_na_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt6.msgtype == 5, concat('Assigned address: ', addrtotext(substring(option[3].option[5].hex, 0, 16))), '')";

    BackendStoreFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    new_leases->push_back(lease6);

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", renew_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Assigned address: 2001:db8:1::");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_rebind callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, lease6_rebind) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(rebind_na_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet6Ptr subnet2345(new Subnet6(IOAddress("2001:db8:2::"), 64, 30, 40, 50, 60,
                                      SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet6Ptr subnet3456(new Subnet6(IOAddress("2001:db8:3::"), 64, 30, 40, 50, 60,
                                      SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    new_leases->push_back(lease6);

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", rebind_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 2001:db8:2::1 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::1", 128, 713, HWAddrPtr(),
                          2345);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", rebind_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 2001:db8:3::1 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::1", 128, 713, HWAddrPtr(),
                          3456);

    new_leases->clear();
    new_leases->push_back(lease6);
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", rebind_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 2001:db8:1:: has been assigned"
                    " for 0 hrs 11 mins 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    lines.push_back("Address: 2001:db8:3::1 has been assigned"
                    " for 0 hrs 11 mins 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_rebind callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, customRequestLoggingFormat_lease6_rebind) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(rebind_na_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt6.msgtype == 6, concat('Assigned address: ', addrtotext(substring(option[3].option[5].hex, 0, 16))), '')";

    BackendStoreFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    new_leases->push_back(lease6);

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", rebind_na_);
        handle->setArgument("response6", response_na_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Assigned address: 2001:db8:1::");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_release callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, lease6_release) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(release_na_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet6Ptr subnet2345(new Subnet6(IOAddress("2001:db8:2::"), 64, 30, 40, 50, 60,
                                      SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet6Ptr subnet3456(new Subnet6(IOAddress("2001:db8:3::"), 64, 30, 40, 50, 60,
                                      SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_release(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", release_na_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 2001:db8:2::1 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::1", 128, 713, HWAddrPtr(),
                          2345);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_release(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", release_na_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 2001:db8:3::1 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::1", 128, 713, HWAddrPtr(),
                          3456);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_release(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", release_na_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 2001:db8:1:: has been released"
                    " from a device with DUID: 17:34:e2:ff:09:92:54");

    lines.push_back("Address: 2001:db8:3::1 has been released"
                    " from a device with DUID: 17:34:e2:ff:09:92:54");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_release callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, customRequestLoggingFormat_lease6_release) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(release_na_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt6.msgtype == 8, concat('Released address: ', addrtotext(substring(option[3].option[5].hex, 0, 16))), '')";

    BackendStoreFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_release(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", release_na_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Released address: 2001:db8:1::");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_decline callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, lease6_decline) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(decline_);
    handle->setCurrentLibrary(0);

    // Create a subnet with user context disabling legal logging.
    Subnet6Ptr subnet2345(new Subnet6(IOAddress("2001:db8:2::"), 64, 30, 40, 50, 60,
                                      SubnetID(2345)));
    ElementPtr ctx2345 = Element::createMap();
    ctx2345->set("legal-logging", Element::create(false));
    subnet2345->setContext(ctx2345);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2345);

    // Create a subnet with user context explicitly enabling legal logging.
    Subnet6Ptr subnet3456(new Subnet6(IOAddress("2001:db8:3::"), 64, 30, 40, 50, 60,
                                      SubnetID(3456)));
    ElementPtr ctx3456 = Element::createMap();
    ctx3456->set("legal-logging", Element::create(true));
    subnet3456->setContext(ctx3456);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3456);
    CfgMgr::instance().commit();

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", decline_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Try to log the lease for address 2001:db8:2::1 and subnet identifier 2345. The log
    // entry should not be generated because legal-logging is disabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::1", 128, 713, HWAddrPtr(),
                          2345);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", decline_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Log the lease for address 2001:db8:3::1 and subnet identifier 3456. This should be
    // logged because legal logging is explicitly enabled for this subnet.
    lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::1", 128, 713, HWAddrPtr(),
                          3456);

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", decline_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 2001:db8:1:: has been released"
                    " from a device with DUID: 17:34:e2:ff:09:92:54");

    lines.push_back("Address: 2001:db8:3::1 has been released"
                    " from a device with DUID: 17:34:e2:ff:09:92:54");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the lease6_decline callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multiple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTestv6, customRequestLoggingFormat_lease6_decline) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(decline_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt6.msgtype == 9, concat('Declined address: ', addrtotext(substring(option[3].option[5].hex, 0, 16))), '')";

    BackendStoreFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", decline_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Declined address: 2001:db8:1::");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Verifies that the custom format logs on multiple lines.
TEST_F(CalloutTestv6, customRequestLoggingFormatMultipleLines) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    CfgMgr::instance().setFamily(AF_INET6);

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(decline_);
    handle->setCurrentLibrary(0);

    std::string format = "ifelse(pkt6.msgtype == 9, 'first line' + 0x0a + 'second line', '')";

    BackendStoreFactory::instance()->setRequestFormatExpression(format);

    int ret;

    // Make a lease and add it to the callout arguments.
    Lease6Ptr lease6 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:1::", 128,
                                    713, HWAddrPtr());

    // The callout should succeed and generate an entry for 2001:db8:1::
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("lease6", lease6);
        ASSERT_NO_THROW(ret = lease6_decline(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", decline_);
        handle->setArgument("response6", response_);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("first line");
    lines.push_back("second line");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

TEST_F(CalloutTestv6, multipleAddressesAndPrefixesCustomLoggingFormatRequestOnly) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(request_na_);
    handle->setCurrentLibrary(0);

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_only_);

    int ret;

    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, duid_->getDuid()));

    Pkt6Ptr request(boost::make_shared<Pkt6>(DHCPV6_REQUEST, 0x77));
    request->addOption(client_id);

    Pkt6Ptr response(boost::make_shared<Pkt6>(DHCPV6_REPLY, 0x77));
    response->addOption(client_id);

    Lease6Ptr lease_na2 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::", 128, 256, HWAddrPtr(), 0, 1024);
    Lease6Ptr lease_pd2 = createLease6(duid_, Lease::TYPE_PD, "2001:db8:2::", 64, 256, HWAddrPtr(), 0, 1024);

    Lease6Ptr lease_na3 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::", 128, 512, HWAddrPtr(), 0, 1024);
    Lease6Ptr lease_pd3 = createLease6(duid_, Lease::TYPE_PD, "2001:db8:3::", 64, 512, HWAddrPtr(), 0, 1024);

    Lease6Ptr lease_na4 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:4::", 128, 512, HWAddrPtr(), 0, 1024);
    Lease6Ptr lease_pd4 = createLease6(duid_, Lease::TYPE_PD, "2001:db8:4::", 64, 512, HWAddrPtr(), 0, 1024);

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    // The requests are for 2001:db8:1:: 2001:db8:2:: and 2001:db8:4:: address and prefix
    // but the response has 2001:db8:1:: 2001:db8:3:: and 2001:db8:4:: address and prefix
    new_leases->push_back(lease_na_);
    new_leases->push_back(lease_pd_);
    new_leases->push_back(lease_na3);
    new_leases->push_back(lease_pd3);
    new_leases->push_back(lease_na4);
    new_leases->push_back(lease_pd4);
    deleted_leases->push_back(lease_na2);
    deleted_leases->push_back(lease_pd2);

    // Address that is requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_na(new Option6IA(D6O_IA_NA, 1234));
    Option6IAAddrPtr addr(new Option6IAAddr(D6O_IAADDR, lease_na_->addr_,
                                            lease_na_->preferred_lft_,
                                            lease_na_->valid_lft_));
    ia_na->addOption(addr);

    // Address that is requested and is not assigned by the server
    boost::shared_ptr<Option6IA> ia_na2(new Option6IA(D6O_IA_NA, 1024));
    Option6IAAddrPtr addr2(new Option6IAAddr(D6O_IAADDR, lease_na2->addr_,
                                             lease_na2->preferred_lft_,
                                             lease_na2->valid_lft_));
    ia_na2->addOption(addr2);

    // Address that is not requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_na3(new Option6IA(D6O_IA_NA, 1024));
    Option6IAAddrPtr addr3(new Option6IAAddr(D6O_IAADDR, lease_na3->addr_,
                                             lease_na3->preferred_lft_,
                                             lease_na3->valid_lft_));
    ia_na3->addOption(addr3);

    // Address that is requested and is assigned by the server with 0 valid lifetime
    Option6IAAddrPtr addr4(new Option6IAAddr(D6O_IAADDR, lease_na2->addr_, 0, 0));
    ia_na3->addOption(addr4);

    // Address that is requested and is assigned by the server
    Option6IAAddrPtr addr5(new Option6IAAddr(D6O_IAADDR, lease_na4->addr_,
                                             lease_na4->preferred_lft_,
                                             lease_na4->valid_lft_));
    ia_na2->addOption(addr5);
    ia_na3->addOption(addr5);

    // Prefix that is requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_pd(new Option6IA(D6O_IA_PD, 1234));
    Option6IAPrefixPtr prefix(new Option6IAPrefix(D6O_IAPREFIX, lease_pd_->addr_,
                                                  lease_pd_->prefixlen_,
                                                  lease_pd_->preferred_lft_,
                                                  lease_pd_->valid_lft_));
    ia_pd->addOption(prefix);

    // Prefix that is requested and is not assigned by the server
    boost::shared_ptr<Option6IA> ia_pd2(new Option6IA(D6O_IA_PD, 1024));
    Option6IAPrefixPtr prefix2(new Option6IAPrefix(D6O_IAPREFIX, lease_pd2->addr_,
                                                   lease_pd2->prefixlen_,
                                                   lease_pd2->preferred_lft_,
                                                   lease_pd2->valid_lft_));
    ia_pd2->addOption(prefix2);

    // Prefix that is not requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_pd3(new Option6IA(D6O_IA_PD, 1024));
    Option6IAPrefixPtr prefix3(new Option6IAPrefix(D6O_IAPREFIX, lease_pd3->addr_,
                                                   lease_pd3->prefixlen_,
                                                   lease_pd3->preferred_lft_,
                                                   lease_pd3->valid_lft_));
    ia_pd3->addOption(prefix3);

    // Prefix that is requested and is assigned by the server with 0 valid lifetime
    Option6IAPrefixPtr prefix4(new Option6IAPrefix(D6O_IAPREFIX, lease_pd2->addr_,
                                                   lease_pd2->prefixlen_, 0, 0));
    ia_pd3->addOption(prefix4);

    // Prefix that is requested and is assigned by the server
    Option6IAPrefixPtr prefix5(new Option6IAPrefix(D6O_IAPREFIX, lease_pd4->addr_,
                                                   lease_pd4->prefixlen_,
                                                   lease_pd4->preferred_lft_,
                                                   lease_pd4->valid_lft_));
    ia_pd2->addOption(prefix5);
    ia_pd3->addOption(prefix5);

    // The request contains IA_NA and IA_PD (IAID 1234) with address and prefix
    // 2001:db8:1:: and IA_NA and IA_PD (IAID 1024) with address and prefix
    // 2001:db8:2:: and 2001:db8:4::
    request->addOption(ia_na);
    request->addOption(ia_na2);
    request->addOption(ia_pd);
    request->addOption(ia_pd2);

    // The response contains IA_NA and IA_PD (IAID 1234) with address and prefix
    // 2001:db8:1:: and IA_NA and IA_PD (IAID 1024) with address and prefix
    // 2001:db8:3:: and 2001:db8:4:: and address and prefix 2001:db8:2:: which
    // have valid lifetime set to 0 because they are no longer available
    response->addOption(ia_na);
    response->addOption(ia_na3);
    response->addOption(ia_pd);
    response->addOption(ia_pd3);

    // The callout should succeed and generate an entry for 2001:db8:1::
    // 2001:db8:2:: 2001:db8:4:: because that is what we have in request
    // The 2001:db8:3:: is present in the response, but the parser is run
    // against the request only
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", request);
        handle->setArgument("response6", response);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 2001:db8:1:: has been assigned for 713 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Address: 2001:db8:4:: has been assigned for 512 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Prefix: 2001:db8:4::/64 has been assigned for 512 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Address: 2001:db8:2:: has been assigned for 256 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Prefix: 2001:db8:2::/64 has been assigned for 256 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

TEST_F(CalloutTestv6, multipleAddressesAndPrefixesCustomLoggingFormatRequestAndResponse) {
    ASSERT_NO_THROW(BackendStoreFactory::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandlePtr handle = getCalloutHandle(request_na_);
    handle->setCurrentLibrary(0);

    CfgMgr::instance().setFamily(AF_INET6);

    BackendStoreFactory::instance()->setRequestFormatExpression(request_format_);
    BackendStoreFactory::instance()->setResponseFormatExpression(response_format_);

    int ret;

    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, duid_->getDuid()));

    Pkt6Ptr request(boost::make_shared<Pkt6>(DHCPV6_REQUEST, 0x77));
    request->addOption(client_id);

    Pkt6Ptr response(boost::make_shared<Pkt6>(DHCPV6_REPLY, 0x77));
    response->addOption(client_id);

    Lease6Ptr lease_na2 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:2::", 128, 256, HWAddrPtr(), 0, 1024);
    Lease6Ptr lease_pd2 = createLease6(duid_, Lease::TYPE_PD, "2001:db8:2::", 64, 256, HWAddrPtr(), 0, 1024);

    Lease6Ptr lease_na3 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:3::", 128, 512, HWAddrPtr(), 0, 1024);
    Lease6Ptr lease_pd3 = createLease6(duid_, Lease::TYPE_PD, "2001:db8:3::", 64, 512, HWAddrPtr(), 0, 1024);

    Lease6Ptr lease_na4 = createLease6(duid_, Lease::TYPE_NA, "2001:db8:4::", 128, 512, HWAddrPtr(), 0, 1024);
    Lease6Ptr lease_pd4 = createLease6(duid_, Lease::TYPE_PD, "2001:db8:4::", 64, 512, HWAddrPtr(), 0, 1024);

    Lease6CollectionPtr new_leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    // The requests are for 2001:db8:1:: 2001:db8:2:: and 2001:db8:4:: address and prefix
    // but the response has 2001:db8:1:: 2001:db8:3:: and 2001:db8:4:: address and prefix
    new_leases->push_back(lease_na_);
    new_leases->push_back(lease_pd_);
    new_leases->push_back(lease_na3);
    new_leases->push_back(lease_pd3);
    new_leases->push_back(lease_na4);
    new_leases->push_back(lease_pd4);
    deleted_leases->push_back(lease_na2);
    deleted_leases->push_back(lease_pd2);

    // Address that is requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_na(new Option6IA(D6O_IA_NA, 1234));
    Option6IAAddrPtr addr(new Option6IAAddr(D6O_IAADDR, lease_na_->addr_,
                                            lease_na_->preferred_lft_,
                                            lease_na_->valid_lft_));
    ia_na->addOption(addr);

    // Address that is requested and is not assigned by the server
    boost::shared_ptr<Option6IA> ia_na2(new Option6IA(D6O_IA_NA, 1024));
    Option6IAAddrPtr addr2(new Option6IAAddr(D6O_IAADDR, lease_na2->addr_,
                                             lease_na2->preferred_lft_,
                                             lease_na2->valid_lft_));
    ia_na2->addOption(addr2);

    // Address that is not requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_na3(new Option6IA(D6O_IA_NA, 1024));
    Option6IAAddrPtr addr3(new Option6IAAddr(D6O_IAADDR, lease_na3->addr_,
                                             lease_na3->preferred_lft_,
                                             lease_na3->valid_lft_));
    ia_na3->addOption(addr3);

    // Address that is requested and is assigned by the server with 0 valid lifetime
    Option6IAAddrPtr addr4(new Option6IAAddr(D6O_IAADDR, lease_na2->addr_, 0, 0));
    ia_na3->addOption(addr4);

    // Address that is requested and is assigned by the server
    Option6IAAddrPtr addr5(new Option6IAAddr(D6O_IAADDR, lease_na4->addr_,
                                             lease_na4->preferred_lft_,
                                             lease_na4->valid_lft_));
    ia_na2->addOption(addr5);
    ia_na3->addOption(addr5);

    // Prefix that is requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_pd(new Option6IA(D6O_IA_PD, 1234));
    Option6IAPrefixPtr prefix(new Option6IAPrefix(D6O_IAPREFIX, lease_pd_->addr_,
                                                  lease_pd_->prefixlen_,
                                                  lease_pd_->preferred_lft_,
                                                  lease_pd_->valid_lft_));
    ia_pd->addOption(prefix);

    // Prefix that is requested and is not assigned by the server
    boost::shared_ptr<Option6IA> ia_pd2(new Option6IA(D6O_IA_PD, 1024));
    Option6IAPrefixPtr prefix2(new Option6IAPrefix(D6O_IAPREFIX, lease_pd2->addr_,
                                                   lease_pd2->prefixlen_,
                                                   lease_pd2->preferred_lft_,
                                                   lease_pd2->valid_lft_));
    ia_pd2->addOption(prefix2);

    // Prefix that is not requested and is assigned by the server
    boost::shared_ptr<Option6IA> ia_pd3(new Option6IA(D6O_IA_PD, 1024));
    Option6IAPrefixPtr prefix3(new Option6IAPrefix(D6O_IAPREFIX, lease_pd3->addr_,
                                                   lease_pd3->prefixlen_,
                                                   lease_pd3->preferred_lft_,
                                                   lease_pd3->valid_lft_));
    ia_pd3->addOption(prefix3);

    // Prefix that is requested and is assigned by the server with 0 valid lifetime
    Option6IAPrefixPtr prefix4(new Option6IAPrefix(D6O_IAPREFIX, lease_pd2->addr_,
                                                   lease_pd2->prefixlen_, 0, 0));
    ia_pd3->addOption(prefix4);

    // Prefix that is requested and is assigned by the server
    Option6IAPrefixPtr prefix5(new Option6IAPrefix(D6O_IAPREFIX, lease_pd4->addr_,
                                                   lease_pd4->prefixlen_,
                                                   lease_pd4->preferred_lft_,
                                                   lease_pd4->valid_lft_));
    ia_pd2->addOption(prefix5);
    ia_pd3->addOption(prefix5);

    // The request contains IA_NA and IA_PD (IAID 1234) with address and prefix
    // 2001:db8:1:: and IA_NA and IA_PD (IAID 1024) with address and prefix
    // 2001:db8:2:: and 2001:db8:4::
    request->addOption(ia_na);
    request->addOption(ia_na2);
    request->addOption(ia_pd);
    request->addOption(ia_pd2);

    // The response contains IA_NA and IA_PD (IAID 1234) with address and prefix
    // 2001:db8:1:: and IA_NA and IA_PD (IAID 1024) with address and prefix
    // 2001:db8:3:: and 2001:db8:4:: and address and prefix 2001:db8:2:: which
    // have valid lifetime set to 0 because they are no longer available
    response->addOption(ia_na);
    response->addOption(ia_na3);
    response->addOption(ia_pd);
    response->addOption(ia_pd3);

    // The callout should succeed and generate an entry for 2001:db8:1::
    // 2001:db8:3:: and 2001:db8:4:: because that is what we have in response
    // The 2001:db8:2:: is present, but with valid lifetime of 0, so it is
    // excluded by the parser expression
    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("leases6", new_leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        ASSERT_NO_THROW(ret = leases6_committed(*handle));
        EXPECT_EQ(0, ret);
    }

    {
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", request);
        handle->setArgument("response6", response);
        ASSERT_NO_THROW(ret = pkt6_send(*handle));
        EXPECT_EQ(0, ret);
    }

    // Close it to flush any unwritten data
    BackendStoreFactory::instance()->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 2001:db8:1:: has been assigned for 713 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Prefix: 2001:db8:1::/64 has been assigned for 713 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Address: 2001:db8:3:: has been assigned for 512 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Prefix: 2001:db8:3::/64 has been assigned for 512 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Address: 2001:db8:4:: has been assigned for 512 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    lines.push_back("Prefix: 2001:db8:4::/64 has been assigned for 512 seconds"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");

    std::string today_now_string = BackendStoreFactory::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

} // end of anonymous namespace
