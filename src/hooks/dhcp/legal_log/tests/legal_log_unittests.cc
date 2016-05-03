// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>

#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace dhcp;

extern std::string genLease4Entry(Pkt4Ptr query, Lease4Ptr lease, bool renewal);

namespace {


/// Hardware address used by different tests.
const uint8_t HWADDR[] = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};
/// Client id used by different tests.
const uint8_t CLIENTID[] = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};

/// @brief Test fixture for testing DHCPv4 legal entries
class Lease4EntryTest : public ::testing::Test {
public:
    /// @brief Constructor
    /// Fetches the current day and removes files that may be left
    Lease4EntryTest() {
    }

    /// @brief Destructor
    virtual ~Lease4EntryTest() {
    }

    /// @brief Creates an instance of the lease with certain FQDN data.
    ///
    /// @param hostname Hostname.
    /// @param fqdn_fwd Forward FQDN update setting for a created lease.
    /// @param fqdn_rev Reverse FQDN update setting for a created lease.
    ///
    /// @return Instance of the created lease.
    Lease4Ptr createLease4(const std::string& addr_str,
                            uint32_t valid_lifetime,
                            const HWAddrPtr& hwaddr,
                            const ClientIdPtr& client_id) {
            Lease4Ptr lease(new Lease4(isc::asiolink::IOAddress(addr_str),
                                       hwaddr, client_id, valid_lifetime,
                                       0, 0, 0, 0, false, false, ""));

            return(lease);
    }
};

// Verifies DHCPv4 entries for directly connected clients
TEST_F(Lease4EntryTest, directClient) {
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    std::string entry;

    // Verify address and duration for an assignment (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, false));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been assigned for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e");

    // Verify address and duration for a renewal (no client id)
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e");

    // Verify with a client id
    lease4->client_id_.reset(new ClientId(CLIENTID, sizeof(CLIENTID)));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, false));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been assigned for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54");

    // Verify a relayed request (no RAI)
    pkt4->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33");

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
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33"
        ", identified by circuit-id: 68:6f:77:64:79");

    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                    OptionBuffer(remote_id,
                                                 remote_id + sizeof(remote_id))));
    rai->addOption(remote_id_opt);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33"
        ", identified by circuit-id: 68:6f:77:64:79"
        " and remote-id: 87:f6:79:77:ef");
}

// Verifies DHCPv4 entries for directly connected clients
// Checks with and with RAI and its suboptions
TEST_F(Lease4EntryTest, relayedClient) {
    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
    Lease4Ptr lease4 = createLease4("192.2.1.100", 6735, hwaddr, ClientIdPtr());
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, 0x77));
    std::string entry;

    // Verify a relayed request without client id or RAI
    pkt4->setGiaddr(isc::asiolink::IOAddress("192.2.16.33"));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e"
        " connected via relay at address: 192.2.16.33");

    // Verify a relayed request with client id, but no RAI
    lease4->client_id_.reset(new ClientId(CLIENTID, sizeof(CLIENTID)));
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33");

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
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33");

    // Create CIRCUIT ID sub-option
    uint8_t circuit_id[] = { 0x68, 0x6F, 0x77, 0x64, 0x79 };
    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                    OptionBuffer(circuit_id,
                                                 circuit_id + sizeof(circuit_id))));

    // Verify a relayed request with RAI with only circuit id
    rai->addOption(circuit_id_opt);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33"
        ", identified by circuit-id: 68:6f:77:64:79");

    // Verify a relayed request with RAI with both circuit id and remote id
    uint8_t remote_id[] = { 0x87, 0xF6, 0x79, 0x77, 0xEF };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                    OptionBuffer(remote_id,
                                                 remote_id + sizeof(remote_id))));
    rai->addOption(remote_id_opt);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33"
        ", identified by circuit-id: 68:6f:77:64:79"
        " and remote-id: 87:f6:79:77:ef");

    // Verify a relayed request with RAI with only remote id
    rai->delOption(RAI_OPTION_AGENT_CIRCUIT_ID);
    ASSERT_NO_THROW(entry = genLease4Entry(pkt4, lease4, true));
    EXPECT_EQ(entry,
        "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:"
        " hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54"
        " connected via relay at address: 192.2.16.33"
        ", identified by remote-id: 87:f6:79:77:ef");
}

} // end of anonymous namespace
