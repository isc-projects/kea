// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify DHCPv4 legal file entry
/// generation as well as tests which exercise v4 callouts: lease4_select
/// and lease4_renew.  These tests assume the legal log library
/// is linked in, not loaded.  This allows a great deal more flexiblity
/// in testing, such as overriding and accessing the legal_file instance.
/// The load and unload callouts are excercised in ../libloadtests, which
/// actually uses the HooksManager to load and unload the library.

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <test_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace dhcp;
using namespace hooks;
using namespace legal_log;

extern RotatingFilePtr legal_file;

extern std::string genLease4Entry(const Pkt4Ptr& query, const Lease4Ptr& lease, const bool renewal);
extern int legalLog4Handler(CalloutHandle& handle, bool renewal);

extern "C" {
extern int lease4_select(CalloutHandle& handle);
extern int lease4_renew(CalloutHandle& handle);
}

namespace {

/// @brief Hardware address used by different tests.
const uint8_t HWADDR[] = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};
/// @brief Client id used by different tests.
const uint8_t CLIENTID[] = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};

/// @brief Convenience function which creates a Lease4 instanceo
///
/// Factory for creating leases which defaults values that are not of
/// interest during legal entry formation.
///
/// @param addr_str IPv4 lease address as a string
/// @param valid_lifetime Lifetime of the lease in seconds
/// @param hwaddr Pointer to the lease hardware address
/// @param client_id Pointer to the lease client id (may be null)
///
/// @return Pointer to the newly created Lease4 instance
Lease4Ptr createLease4(const std::string& addr_str, uint32_t valid_lifetime,
                       const HWAddrPtr& hwaddr, const ClientIdPtr& client_id) {
    Lease4Ptr lease(new Lease4(isc::asiolink::IOAddress(addr_str),
                               hwaddr, client_id, valid_lifetime,
                               0, 0, 0, 0, false, false, ""));

    return (lease);
};

// Verifies legal entry content for directly connected clients
TEST(Lease4EntryTest, directClient) {
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    std::string entry;

    // Verify address and duration for an assignment (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, false));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address and duration for a renewal (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify with a client id
    lease4->client_id_.reset(new ClientId(CLIENTID, sizeof(CLIENTID)));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, false));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54",
              entry);

    // Verify a relayed request (no RAI)
    pkt4->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option. This option is represented
    // by OptionCustom which requires a definition to be passed to
    // the constructor.
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(Option::V4,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));

    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));
    rai->addOption(circuit_id_opt);

    pkt4->addOption(rai);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79",
              entry);

    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                       remote_id + sizeof(remote_id))));
    rai->addOption(remote_id_opt);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79"
              " and remote-id: 87:f6:79:77:ef",
              entry);
}

// Verifies legal entry content for relayed clients
// Checks with and without RAI and its suboptions
TEST(Lease4EntryTest, relayedClient) {
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    std::string entry;

    // Verify a relayed request without client id or RAI
    pkt4->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Verify a relayed request with client id, but no RAI
    lease4->client_id_.reset(new ClientId(CLIENTID, sizeof(CLIENTID)));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Get the option definition for RAI option.
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(Option::V4,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));
    pkt4->addOption(rai);

    // Verify a relayed request with RAI but has neither circuit id or remote id
    pkt4->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
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
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79",
              entry);

    // Verify a relayed request with RAI with both circuit id and remote id
    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                                    remote_id
                                                    + sizeof(remote_id))));
    rai->addOption(remote_id_opt);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79"
              " and remote-id: 87:f6:79:77:ef",
              entry);

    // Verify a relayed request with RAI with only remote id
    rai->delOption(RAI_OPTION_AGENT_CIRCUIT_ID);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 mins 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by remote-id: 87:f6:79:77:ef",
              entry);
}

// Verifies that legalLog4Handler() detects a null legal_file
TEST_F(CalloutTest, noRotatingFileTest) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // Make a lease and add it to the callout arguments
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    handle.setArgument("lease4", lease4);

    // Make a packet and add it to the cllout arguments
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    handle.setArgument("query4", pkt4);

    // The function should fail when there's no legal_file.
    int ret;
    ASSERT_NO_THROW(ret = legalLog4Handler(handle, false));
    EXPECT_EQ(1, ret);
}

// Verifies that the lease4_select callout
// -# Does not generate an entry when fake_allocation arugment is true
// -# Generates the correct entry in the legal file given a Pkt4 and Lease4
// Note we don't bother testing multple entries or rotation as this is done
// during RotatingFile testing.
TEST_F(CalloutTest, lease4_select) {
    // Create the legal file
    TestableRotatingFilePtr tfile;
    ASSERT_NO_THROW(tfile.reset(new TestableRotatingFile(today_)));
    legal_file = tfile;

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // Make a lease and add it to the callout arguments.
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    handle.setArgument("lease4", lease4);

    // Make a packet and add it to the callout arugments.
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    handle.setArgument("query4", pkt4);

    // Set fake allocation arugment to true.
    bool fake_allocation = true;
    handle.setArgument("fake_allocation", fake_allocation);

    // The callout should succeed but with fake allocation set
    // to true, no entry should be generated. We'll check file
    //  content later.
    int ret;
    ASSERT_NO_THROW(ret = lease4_select(handle));
    EXPECT_EQ(0, ret);

    // Set fake allocation arugment to false and change the
    // lease address so we'll know that the next invocation is
    // the one which generated the entry.
    fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    lease4->addr_ = isc::asiolink::IOAddress("192.2.1.111");

    // Callout should succeed and generate an entry for 192.2.1.111.
    ASSERT_NO_THROW(ret = lease4_select(handle));
    EXPECT_EQ(0, ret);

    // Close it to flush any unwritten data
    tfile->close();

    // Verify that the file content is correct. We should have only
    // the one entry for address 192.2.1.111.
    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.111 has been assigned"
                    " for 1 hrs 52 mins 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    std::string today_now_string = legal_file->getNowString();
    checkFileLines(genName(today_), today_now_string, lines);
}

// Verifies that the lease4_renew callout generates the correct entry
// in the legal file given a Pkt4 and Lease4
TEST_F(CalloutTest, lease4_renew) {
    // Create the legal file
    TestableRotatingFilePtr tfile;
    ASSERT_NO_THROW(tfile.reset(new TestableRotatingFile(today_)));
    legal_file = tfile;

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // Make a lease and add it to the call argument
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    handle.setArgument("lease4", lease4);

    // Make a packet and add it to the callout arugments.
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    handle.setArgument("query4", pkt4);

    // Callout should succeed and generate an entry for 192.2.1.100.
    int ret;
    ASSERT_NO_THROW(ret = lease4_renew(handle));
    EXPECT_EQ(0, ret);

    // Close it to flush any unwritten data
    tfile->close();

    // Verify that the file content is correct.
    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.100 has been renewed"
                    " for 1 hrs 52 mins 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");

    std::string today_now_string = legal_file->getNowString();
    checkFileLines(genName(today_), today_now_string, lines);
}

} // end of anonymous namespace
