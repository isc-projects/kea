// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify DHCPv6 legal file entry
/// generation as well as tests which exercise v6 callouts: pkt6_receive
/// lease6_select, lease6_renew.  These tests assume the legal log library
/// is linked in, not loaded.  This allows a great deal more flexiblity
/// in testing, such as overriding and accessing the legal_file instance.
/// The load and unload callouts are excercised in ../libloadtests, which
/// actually uses the HooksManager to load and unload the library.
#include <exceptions/exceptions.h>

#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <test_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace dhcp;

extern std::string genLease6Entry(Pkt6Ptr query, Lease6Ptr lease, bool renewal);
extern std::string hwaddrSourceToString(uint32_t source);
extern int legallog6_handler(CalloutHandle& handle, bool renewal);

extern LegalFilePtr legal_file;

extern "C" {
extern int pkt6_receive(CalloutHandle& handle);
extern int lease6_select(CalloutHandle& handle);
extern int lease6_renew(CalloutHandle& handle);
extern int lease6_rebind(CalloutHandle& handle);
}

namespace {

/// @brief Hardware address used by different tests.
const uint8_t HWADDR[] = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};

/// @brief DUID id used by different tests.
const uint8_t DUID1[] = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};

/// @brief Convenience function which creates a Lease6 instanceo
///
/// Factory for creating leases which defaults values that are not of
/// interest during legal entry formation.
///
/// @param duid - pointer to the lease DUID
/// @param type - type of the lease (TYPE_IA, TYPE_NA, TYPE_PD)
/// @param addr_str - IPv6 lease address/ prefix as a string
/// @param prefix_len - prefix length
/// @param valid_lifetime - lifetime of the lease in seconds
/// @param hwaddr - pointer to the lease hardware address (may be null)
///
/// @return pointer to the newly created Lease6 instance
Lease6Ptr createLease6(const DuidPtr& duid, const Lease::Type& type,
                       const std::string& addr_str, uint8_t prefix_len,
                       uint32_t valid_lifetime, const HWAddrPtr& hwaddr) {
    Lease6Ptr lease(new Lease6(type, isc::asiolink::IOAddress(addr_str),
                               duid, 0, 0, valid_lifetime, 0, 0, 0,
                               hwaddr, prefix_len));
    return(lease);
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
    EXPECT_EQ("UKNOWN", hwaddrSourceToString(0));
    EXPECT_EQ("UKNOWN",
              hwaddrSourceToString(HWAddr::HWADDR_SOURCE_DOCSIS_MODEM + 1));
}

// Verifies DHCPv6 entries for directly connected clients
TEST(Lease6EntryTest, directClient) {
    DuidPtr duid1(new DUID(DUID1, sizeof(DUID1)));
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    hwaddr->source_ = HWAddr::HWADDR_SOURCE_RAW;

    Lease6Ptr lease6 = createLease6(duid1, Lease::TYPE_NA, "2001:db8:1::", 0,
                                   713, HWAddrPtr());

    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REQUEST, 0x77));
    std::string entry;

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(pkt6, lease6, false));
    EXPECT_EQ("Address:2001:db8:1:: has been assigned for 0 hrs 11 min 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Verify address and duration for a renewal
    ASSERT_NO_THROW(entry = genLease6Entry(pkt6, lease6, true));
    EXPECT_EQ("Address:2001:db8:1:: has been renewed for 0 hrs 11 min 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54",
              entry);

    // Add in hardware address and verify.  We do need to explicitly test each
    // possible value for hardware source as the function which converts it
    // is tested explicitly.
    lease6->hwaddr_ = hwaddr;
    ASSERT_NO_THROW(entry = genLease6Entry(pkt6, lease6, false));
    EXPECT_EQ("Address:2001:db8:1:: has been assigned for 0 hrs 11 min 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54 and hardware"
              " address: hwtype=1 08:00:2b:02:3f:4e (from Raw Socket)",
              entry);
}

// Verifies DHCPv6 entries for relayed clients
TEST(Lease6EntryTest, relayedClient) {
    DuidPtr duid1(new DUID(DUID1, sizeof(DUID1)));
    Lease6Ptr lease6 = createLease6(duid1, Lease::TYPE_NA, "2001:db8:1::", 0,
                                   713, HWAddrPtr());
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REQUEST, 0x77));
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = isc::asiolink::IOAddress("3001::1");
    relay1.peeraddr_ = isc::asiolink::IOAddress("fe80::abcd");
    pkt6->addRelayInfo(relay1);

    // Verify server level relay basic info, no options
    std::string entry;
    ASSERT_NO_THROW(entry = genLease6Entry(pkt6, lease6, false));
    EXPECT_EQ("Address:2001:db8:1:: has been assigned for 0 hrs 11 min 53 secs"
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
    pkt6->relay_info_.clear();
    pkt6->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID
    ASSERT_NO_THROW(entry = genLease6Entry(pkt6, lease6, false));
    EXPECT_EQ("Address:2001:db8:1:: has been assigned for 0 hrs 11 min 53 secs"
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
    pkt6->relay_info_.clear();
    pkt6->addRelayInfo(relay1);

    // Verify relay info with REMOTE_ID and SUBSCRIBER_ID
    ASSERT_NO_THROW(entry = genLease6Entry(pkt6, lease6, false));
    EXPECT_EQ("Address:2001:db8:1:: has been assigned for 0 hrs 11 min 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f"
              " and subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);

    // Verify relay info with only SUBSCRIBER_ID
    relay1.options_.clear();
    relay1.options_.insert(make_pair(relay_opt->getType(), relay_opt));
    pkt6->relay_info_.clear();
    pkt6->addRelayInfo(relay1);

    // Verify address and duration for an assignment
    ASSERT_NO_THROW(entry = genLease6Entry(pkt6, lease6, false));
    EXPECT_EQ("Address:2001:db8:1:: has been assigned for 0 hrs 11 min 53 secs"
              " to a device with DUID: 17:34:e2:ff:09:92:54"
              " connected via relay at address: fe80::abcd"
              " for client on link address: 3001::1, hop count: 1"
              ", identified by subscriber-id: 1a:2b:3c:4d:5e:6f",
              entry);
}

// Verifies that legallog6_handler() detects a null legal_file
TEST_F(CalloutTest, noLegalFileTest) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // Make a lease and add it to the callout arguments
    DuidPtr duid1(new DUID(DUID1, sizeof(DUID1)));
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    hwaddr->source_ = HWAddr::HWADDR_SOURCE_RAW;
    Lease6Ptr lease6 = createLease6(duid1, Lease::TYPE_NA, "2001:db8:1::", 0,
                                    713, HWAddrPtr());
    handle.setArgument("lease6", lease6);

    // Make a packet and add it to the callout arugments
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REQUEST, 0x77));
    handle.setArgument("query6", pkt6);

    // The function should fail when there's no legal_file.
    int ret;
    ASSERT_NO_THROW(ret = legallog6_handler(handle, false));
    EXPECT_EQ(1, ret);
}

// Verifies that the lease6_select callout
// -# Does not generate an entry when fake_allocation is true
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multple entries or rotation as this is done
// during LegalFile testing.
TEST_F(CalloutTest, lease6_select) {
    // Create the legal file
    TestableLegalFilePtr tfile;
    ASSERT_NO_THROW(tfile.reset(new TestableLegalFile(today_)));
    legal_file = tfile;

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // Make a lease and add it to the arguments
    DuidPtr duid1(new DUID(DUID1, sizeof(DUID1)));
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    hwaddr->source_ = HWAddr::HWADDR_SOURCE_RAW;
    Lease6Ptr lease6 = createLease6(duid1, Lease::TYPE_NA, "2001:db8:1::", 0,
                                    713, HWAddrPtr());
    handle.setArgument("lease6", lease6);

    // Make a packet and add it to the context for now.  We need a non-null
    // packet to verify the legal file check.
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REQUEST, 0x77));
    handle.setArgument("query6", pkt6);

    // Set fake allocation arugment to true.
    bool fake_allocation = true;
    handle.setArgument("fake_allocation", fake_allocation);

    // The callout should succeed but with fake allocation set
    // to true, no entry should be generated. We'll check file
    //  content later.
    int ret;
    ASSERT_NO_THROW(ret = lease6_select(handle));
    EXPECT_EQ(0, ret);

    // Set fake allocation arugment to false and change the
    // lease address so we'll know that the next invocation is
    // the one which generated the entry.
    fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    lease6->addr_ = isc::asiolink::IOAddress("2001:db8:1::111");

    // The callout should succeed and generate an entry for 2001:db8:1::111
    ASSERT_NO_THROW(ret = lease6_select(handle));
    EXPECT_EQ(0, ret);

    // Close it to flush any unwritten data
    tfile->close();

    // Verify that the file content.
    std::vector<std::string>lines;
    lines.push_back("Address:2001:db8:1::111 has been assigned"
                    " for 0 hrs 11 min 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    std::string today_now_string = legal_file->getNowString();
    checkFileLines(genName(today_), today_now_string, lines);
}

// Verifies that the lease6_renew callout
// -# Detects no LegalFile instance
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multple entries or rotation as this is done
// during LegalFile testing.
TEST_F(CalloutTest, lease6_renew) {
    // Create the legal file
    TestableLegalFilePtr tfile;
    ASSERT_NO_THROW(tfile.reset(new TestableLegalFile(today_)));
    legal_file = tfile;

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // Make a lease and add it to the arguments
    DuidPtr duid1(new DUID(DUID1, sizeof(DUID1)));
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    hwaddr->source_ = HWAddr::HWADDR_SOURCE_RAW;
    Lease6Ptr lease6 = createLease6(duid1, Lease::TYPE_NA, "2001:db8:1::", 0,
                                    713, HWAddrPtr());
    handle.setArgument("lease6", lease6);

    // Make a packet and add it to the arugments.
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_RENEW, 0x77));
    handle.setArgument("query6", pkt6);

    // The callout should succeed and generate an entry for 2001:db8:1::111
    int ret;
    ASSERT_NO_THROW(ret = lease6_renew(handle));
    EXPECT_EQ(0, ret);

    // Close it to flush any unwritten data
    tfile->close();

    // Verify that the file content.
    std::vector<std::string>lines;
    lines.push_back("Address:2001:db8:1:: has been renewed"
                    " for 0 hrs 11 min 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    std::string today_now_string = legal_file->getNowString();
    checkFileLines(genName(today_), today_now_string, lines);
}

// Verifies that the lease6_rebind callout
// -# Generates the correct entry in the legal file given a Pkt6 and Lease6
// Note we don't bother testing multple entries or rotation as this is done
// during LegalFile testing.
TEST_F(CalloutTest, lease6_rebind) {
    // Create the legal file
    TestableLegalFilePtr tfile;
    ASSERT_NO_THROW(tfile.reset(new TestableLegalFile(today_)));
    legal_file = tfile;

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // Make a lease and add it to the arguments
    DuidPtr duid1(new DUID(DUID1, sizeof(DUID1)));
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    hwaddr->source_ = HWAddr::HWADDR_SOURCE_RAW;
    Lease6Ptr lease6 = createLease6(duid1, Lease::TYPE_NA, "2001:db8:1::", 0,
                                    713, HWAddrPtr());
    handle.setArgument("lease6", lease6);

    // Make a packet and add it to the arugments.
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REBIND, 0x77));
    handle.setArgument("query6", pkt6);

    // The callout should succeed and generate an entry for 2001:db8:1::111
    int ret;
    ASSERT_NO_THROW(ret = lease6_rebind(handle));
    EXPECT_EQ(0, ret);

    // Close it to flush any unwritten data
    tfile->close();

    // Verify that the file content.
    std::vector<std::string>lines;
    lines.push_back("Address:2001:db8:1:: has been renewed"
                    " for 0 hrs 11 min 53 secs"
                    " to a device with DUID: 17:34:e2:ff:09:92:54");
    std::string today_now_string = legal_file->getNowString();
    checkFileLines(genName(today_), today_now_string, lines);
}

} // end of anonymous namespace
