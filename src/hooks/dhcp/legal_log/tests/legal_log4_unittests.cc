// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify DHCPv4 legal file entry
/// generation as well as tests which exercise the v4 callouts, themselves.
#include <exceptions/exceptions.h>

#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
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

extern LegalFilePtr legal_file;

extern std::string genLease4Entry(Pkt4Ptr query, Lease4Ptr lease, bool renewal);

extern "C" {
extern int load(LibraryHandle& handle);
extern int unload();
extern int pkt4_receive(CalloutHandle& handle);
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
/// @param addr_str - IPv4 lease address as a string
/// @param valid_lifetime - lifetime of the lease in seconds
/// @param hwaddr - pointer to the lease hardware address
/// @param client_id - pointer to the lease client id (may be null)
///
/// @return pointer to the newly created Lease4 instance
Lease4Ptr createLease4(const std::string& addr_str, uint32_t valid_lifetime,
                       const HWAddrPtr& hwaddr, const ClientIdPtr& client_id) {
    Lease4Ptr lease(new Lease4(isc::asiolink::IOAddress(addr_str),
                               hwaddr, client_id, valid_lifetime,
                               0, 0, 0, 0, false, false, ""));

    return(lease);
};

// Verifies legal entry content for directly connected clients
TEST(Lease4EntryTest, directClient) {
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    std::string entry;

    // Verify address and duration for an assignment (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, false));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 min 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify address and duration for a renewal (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e",
              entry);

    // Verify with a client id
    lease4->client_id_.reset(new ClientId(CLIENTID, sizeof(CLIENTID)));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, false));
    EXPECT_EQ("Address: 192.2.1.100 has been assigned for 1 hrs 52 min 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54",
              entry);

    // Verify a relayed request (no RAI)
    pkt4->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
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
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
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
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
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
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e"
              " connected via relay at address: 192.2.16.33",
              entry);

    // Verify a relayed request with client id, but no RAI
    lease4->client_id_.reset(new ClientId(CLIENTID, sizeof(CLIENTID)));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
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
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
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
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
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
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by circuit-id: 68:6f:77:64:79"
              " and remote-id: 87:f6:79:77:ef",
              entry);

    // Verify a relayed request with RAI with only remote id
    rai->delOption(RAI_OPTION_AGENT_CIRCUIT_ID);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
              " to a device with hardware address:"
              " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
              " connected via relay at address: 192.2.16.33"
              ", identified by remote-id: 87:f6:79:77:ef",
              entry);
}

// Verifies that the load callout instantiates and opens the LegalFile and
// that unload() resets it.
// @todo When 4297 is complete, will need to expand this based on
// parameters for path, basename, etc.  NOTE THAT once 4297 is done this
// test must not use the default values (default_legal_path and default_legal_base)
// as we do not want to risk altering a LIVE file.
TEST_F(CalloutTest, loadAndUnload) {
    LibraryHandle library(getCalloutManager().get());

    // Invoke the callout.  It should succeed.
    int ret;
    EXPECT_NO_THROW(ret = load(library));
    EXPECT_EQ(0, ret);

    // Verify the legal_file was created and is open
    ASSERT_TRUE(legal_file);
    EXPECT_TRUE(legal_file->isOpen());

    // Save the filename so we can remove it after unload.
    std::string fname = legal_file->getFileName();

    EXPECT_NO_THROW(ret = unload());
    EXPECT_EQ(0, ret);
    EXPECT_FALSE(legal_file);

    ::remove(fname.c_str());
}

// Verifies that the pkt4_receive callout caches DHCPREQUEST packets
TEST_F(CalloutTest, pkt4_receive) {
    CalloutHandle handle(getCalloutManager());

    // Create a DHCPDISCOVER and use it as the callout query4 argument.
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 0x77));
    handle.setArgument("query4", pkt4);

    // Invoke the callout. It should succeed but not cache the packet.
    int ret;
    ASSERT_NO_THROW(ret = pkt4_receive(handle));
    EXPECT_EQ(0, ret);

    // Verify the context does NOT contain the discover.
    Pkt4Ptr from_context;
    ASSERT_THROW(handle.getContext("query4", from_context), NoSuchCalloutContext);

    // Create a DHCPREQUEST and use it as the callout query4 argument.
    pkt4.reset(new Pkt4(DHCPREQUEST, 0x77));
    handle.setArgument("query4", pkt4);

    // Invoke the callout. It should succeed and cache the packet.
    ASSERT_NO_THROW(ret = pkt4_receive(handle));
    EXPECT_EQ(0, ret);

    // Verify the request was cached.
    ASSERT_NO_THROW(handle.getContext("query4", from_context));
    ASSERT_TRUE(from_context);
    EXPECT_EQ(pkt4, from_context);
}

// Verifies that the lease4_select callout
// -# Detects no LegalFile instance
// -# Detects no Pkt4 in the callout context
// -# Verifies the file content when given a Pkt4 and Lease4
// Note we don't bother testing multple entries or rotation as this is done
// during LegalFile testing.
TEST_F(CalloutTest, lease4_select) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // We should fail if there's no legal_file
    int ret;
    ASSERT_NO_THROW(ret = lease4_select(handle));
    EXPECT_EQ(1, ret);

    // Create the legal file
    TestableLegalFilePtr tfile;
    ASSERT_NO_THROW(tfile.reset(new TestableLegalFile(today_)));
    legal_file = tfile;

    // We should fail if there's a legal file but no context
    // has no packet
    ASSERT_NO_THROW(ret = lease4_select(handle));
    EXPECT_EQ(1, ret);

    // Make a packet and add it to the context
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    handle.setContext("query4", pkt4);

    // Make a lease and add it to the arguments
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    handle.setArgument("lease4", lease4);

    // Call should succeed
    ASSERT_NO_THROW(ret = lease4_select(handle));
    EXPECT_EQ(0, ret);

    // Close it to flush any unwritten data
    tfile->close();

    // Verify that the file content.
    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.100 has been assigned for 1 hrs 52 min 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");
    std::string today_now_string = legal_file->getNowString();
    checkFileLines(genName(today_), today_now_string, lines);
}

// Verifies that the lease4_renew callout
// -# Detects no LegalFile instance
// -# Detects no Pkt4 in the callout context
// -# Verifies the file content when given a Pkt4 and Lease4
// Note we don't bother testing multple entries or rotation as this is done
// during LegalFile testing.
TEST_F(CalloutTest, lease4_renew) {
    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // We should fail if there's no legal_file
    int ret;
    ASSERT_NO_THROW(ret = lease4_renew(handle));
    EXPECT_EQ(1, ret);

    // Create the legal file
    TestableLegalFilePtr tfile;
    ASSERT_NO_THROW(tfile.reset(new TestableLegalFile(today_)));
    legal_file = tfile;

    // We should fail if there's a legal file but no context
    // has no packet
    ASSERT_NO_THROW(ret = lease4_renew(handle));
    EXPECT_EQ(1, ret);

    // Make a packet and add it to the context
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    handle.setContext("query4", pkt4);

    // Make a lease and add it to the arguments
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    handle.setArgument("lease4", lease4);

    // Call should succeed
    ASSERT_NO_THROW(ret = lease4_renew(handle));
    EXPECT_EQ(0, ret);

    // Close it to flush any unwritten data
    tfile->close();

    std::vector<std::string>lines;
    lines.push_back("Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs"
                    " to a device with hardware address:"
                    " hwtype=1 08:00:2b:02:3f:4e");
    std::string today_now_string = legal_file->getNowString();
    checkFileLines(genName(today_), today_now_string, lines);
}

} // end of anonymous namespace
