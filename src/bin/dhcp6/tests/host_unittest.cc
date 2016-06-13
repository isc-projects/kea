// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_vendor.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used by the Host reservation unit tests.
///
/// - Configuration 0:
///   Single subnet with two reservations, one with a hostname, one without
///
/// - Configuration 1:
///   Multiple reservations using different host identifiers.
///
/// - Configuration 2:
///   Same as configuration 1 but 'host-reservation-identifiers' specified
///   in non-default order.
///
/// - Configuration 3:
///   - Used to test that host specific options override subnet specific
///     options and global options.
///
/// - Configuration 4:
///   - Used to test that client receives options solely specified in a
///     host scope.
///
/// - Configuration 5:
///   - Used to test that host specific vendor options override globally
///     specified vendor options.
const char* CONFIGS[] = {
    // Configuration 0:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1:1::/64\" } ],"
        "    \"interface\" : \"eth0\" , "
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:04\","
        "        \"ip-addresses\": [ \"2001:db8:1:1::babe\" ],"
        "        \"hostname\": \"alice\""
        "    },"
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1:1::babf\" ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 1:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"mac-sources\": [ \"ipv6-link-local\" ], "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\" , "
        "    \"reservations\": ["
        "    {"
        "        \"hw-address\": \"38:60:77:d5:ff:ee\","
        "        \"ip-addresses\": [ \"2001:db8:1::1\" ]"
        "    },"
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 2:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\", \"hw-address\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"mac-sources\": [ \"ipv6-link-local\" ], "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\" , "
        "    \"reservations\": ["
        "    {"
        "        \"hw-address\": \"38:60:77:d5:ff:ee\","
        "        \"ip-addresses\": [ \"2001:db8:1::1\" ]"
        "    },"
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 3:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"nisp-servers\","
        "    \"data\": \"3000:3::123\""
        "} ],"
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\","
        "    \"option-data\": [ {"
        "        \"name\": \"dns-servers\","
        "        \"data\": \"3000:2::123\""
        "    },"
        "    {"
        "        \"name\": \"nis-servers\","
        "        \"data\": \"3000:2::123\""
        "    },"
        "    {"
        "        \"name\": \"sntp-servers\","
        "        \"data\": \"3000:2::123\""
        "    } ],"
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ],"
        "        \"option-data\": [ {"
        "            \"name\": \"dns-servers\","
        "            \"data\": \"3000:1::234\""
        "        },"
        "        {"
        "            \"name\": \"nis-servers\","
        "            \"data\": \"3000:1::234\""
        "        } ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 4:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ],"
        "        \"option-data\": [ {"
        "            \"name\": \"dns-servers\","
        "            \"data\": \"3000:1::234\""
        "        },"
        "        {"
        "            \"name\": \"nis-servers\","
        "            \"data\": \"3000:1::234\""
        "        } ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 5:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"vendor-opts\","
        "    \"data\": 4491"
        "},"
        "{"
        "    \"name\": \"tftp-servers\","
        "    \"space\": \"vendor-4491\","
        "    \"data\": \"3000:3::123\""
        "} ],"
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ],"
        "        \"option-data\": [ {"
        "            \"name\": \"vendor-opts\","
        "            \"data\": 4491"
        "        },"
        "        {"
        "            \"name\": \"tftp-servers\","
        "            \"space\": \"vendor-4491\","
        "            \"data\": \"3000:1::234\""
        "        } ]"
        "    } ]"
        " } ]"
    "}"

};

/// @brief Test fixture class for testing host reservations
class HostTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    HostTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
    }

    /// @brief Checks that specified option contains a desired address.
    ///
    /// The option must cast to the @ref Option6AddrLst type. The function
    /// expects that this option contains at least one address and checks
    /// first address for equality with @ref expected_addr.
    ///
    /// @param option_type Option type.
    /// @param expected_addr Desired address.
    /// @param config Configuration obtained from the server.
    void verifyAddressOption(const uint16_t option_type,
                             const std::string& expected_addr,
                             const Dhcp6Client::Configuration& config) const {
        Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
            Option6AddrLst>(config.findOption(option_type));
        ASSERT_TRUE(opt) << "option " << option_type << " not found or it "
            "is of incorrect type";
        Option6AddrLst::AddressContainer addrs = opt->getAddresses();
        ASSERT_GE(addrs.size(), 1) << "test failed for option type " << option_type;
        EXPECT_EQ(expected_addr, addrs[0].toText())
            << "test failed for option type " << option_type;
    }

    /// @brief Verifies that the reservation is retrieved by the server
    /// using one of the host identifiers.
    ///
    /// @param client Reference to a client to be used in the test.
    /// The client should be preconfigured to insert a specific identifier
    /// into the message, e.g. DUID, HW address etc.
    /// @param config_index Index of the configuration to use in the CONFIGS
    /// table.
    /// @param exp_ip_address Expected IPv6 address in the returned
    /// reservation.
    void testReservationByIdentifier(Dhcp6Client& client,
                                     const unsigned int config_index,
                                     const std::string exp_ip_address) {
        configure(CONFIGS[config_index], *client.getServer());

        const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets6()->getAll();
        ASSERT_EQ(1, subnets->size());

        // Configure client to request IA_NA and append IA_NA option
        //  to the client's message.
        client.useNA();
        ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

        // Perform 4-way exchange.
        ASSERT_NO_THROW(client.doSARR());

        // Verify that the client we got the reserved address
        ASSERT_EQ(1, client.getLeaseNum());
        Lease6 lease_client = client.getLease(0);
        EXPECT_EQ(exp_ip_address, lease_client.addr_.toText());
    }

    /// @brief Initiate exchange with DHCPv6 server.
    ///
    /// This method initiates DHCPv6 message exchange between a specified
    /// client a the server. The msg_type is used to indicate what kind
    /// of exchange should be initiated. If the message type is a Renew
    /// or Rebind, the 4-way handshake is made first. If the message type
    /// is a Request, the Solicit-Advertise is done prior to this.
    ///
    /// @param msg_type Message type to be sent to the server.
    /// @param client Reference to a client to be used to initiate the
    /// exchange with the server.
    void doExchange(const uint16_t msg_type, Dhcp6Client& client);

    /// @brief Verifies that host specific options override subnet specific
    /// options.
    ///
    /// Overriden options are requested with Option Request option.
    ///
    /// @param msg_type DHCPv6 message type to be sent to the server. If the
    /// message type is Renew or Rebind, the 4-way exchange is made prior to
    /// sending a Renew or Rebind. For a Request case, the Solicit-Advertise
    /// is also performed.
    void testOverrideRequestedOptions(const uint16_t msg_type);

    /// @brief Verifies that client receives options when they are solely
    /// defined in the host scope (and not in the global or subnet scope).
    ///
    /// @param msg_type DHCPv6 message type to be sent to the server. If the
    /// message type is Renew or Rebind, the 4-way exchange is made prior to
    /// sending a Renew or Rebind. For a Request case, the Solicit-Advertise
    /// is also performed.
    void testHostOnlyOptions(const uint16_t msg_type);

    /// @brief Verifies that host specific vendor options override vendor
    /// options defined in the global scope.
    ///
    /// @param msg_type DHCPv6 message type to be sent to the server. If the
    /// message type is Renew or Rebind, the 4-way exchange is made prior to
    /// sending a Renew or Rebind. For a Request case, the Solicit-Advertise
    /// is also performed.
    void testOverrideVendorOptions(const uint16_t msg_type);

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

void
HostTest::doExchange(const uint16_t msg_type, Dhcp6Client& client) {
    switch (msg_type) {
    case DHCPV6_INFORMATION_REQUEST:
        ASSERT_NO_THROW(client.doInfRequest());
        break;
    case DHCPV6_REQUEST:
        ASSERT_NO_THROW(client.doSARR());
        break;
    case DHCPV6_SOLICIT:
        ASSERT_NO_THROW(client.doSolicit());
        break;
    case DHCPV6_RENEW:
        ASSERT_NO_THROW(client.doSARR());
        ASSERT_NO_THROW(client.doRenew());
        break;
    case DHCPV6_REBIND:
        ASSERT_NO_THROW(client.doSARR());
        ASSERT_NO_THROW(client.doRebind());
        break;
    default:
        ;
    }

    // Make sure that the server has responded with a Reply.
    ASSERT_TRUE(client.getContext().response_);
    ASSERT_EQ(DHCPV6_REPLY, client.getContext().response_->getType());

}


void
HostTest::testOverrideRequestedOptions(const uint16_t msg_type) {
    Dhcp6Client client;
    // Reservation has been made for a client with this DUID.
    client.setDUID("01:02:03:05");

    // Request all options specified in the configuration.
    client.requestOption(D6O_NAME_SERVERS);
    client.requestOption(D6O_NIS_SERVERS);
    client.requestOption(D6O_NISP_SERVERS);
    client.requestOption(D6O_SNTP_SERVERS);

    configure(CONFIGS[3], *client.getServer());

    ASSERT_NO_FATAL_FAILURE(doExchange(msg_type, client));

    {
        SCOPED_TRACE("host specific dns-servers");
        // Host specific DNS server should be used.
        verifyAddressOption(D6O_NAME_SERVERS, "3000:1::234", client.config_);
    }

    {
        SCOPED_TRACE("host specific nis-servers");
        // Host specific NIS server should be used.
        verifyAddressOption(D6O_NIS_SERVERS, "3000:1::234", client.config_);
    }

    {
        SCOPED_TRACE("subnet specific sntp-servers");
        // Subnet specific SNTP server should be used as it is not specified
        // in a host scope.
        verifyAddressOption(D6O_SNTP_SERVERS, "3000:2::123", client.config_);
    }

    {
        SCOPED_TRACE("global nisp-servers");
        // Globally specified NISP server should be used as it is not
        // specified in a host scope.
        verifyAddressOption(D6O_NISP_SERVERS, "3000:3::123", client.config_);
    }
}

void
HostTest::testHostOnlyOptions(const uint16_t msg_type) {
    Dhcp6Client client;
    client.setDUID("01:02:03:05");
    client.requestOption(D6O_NAME_SERVERS);
    client.requestOption(D6O_NIS_SERVERS);

    configure(CONFIGS[3], *client.getServer());

    ASSERT_NO_FATAL_FAILURE(doExchange(msg_type, client));

    {
        SCOPED_TRACE("host specific dns-servers");
        // DNS servers are specified only in a host scope.
        verifyAddressOption(D6O_NAME_SERVERS, "3000:1::234", client.config_);
    }

    {
        SCOPED_TRACE("host specific nis-servers");
        // NIS servers are specified only in a host scope.
        verifyAddressOption(D6O_NIS_SERVERS, "3000:1::234", client.config_);
    }
}

void
HostTest::testOverrideVendorOptions(const uint16_t msg_type) {
    Dhcp6Client client;
    client.setDUID("01:02:03:05");

    // Client needs to include Vendor Specific Information option
    // with ORO suboption, which the server will use to determine
    // which suboptions should be returned to the client.
    OptionVendorPtr opt_vendor(new OptionVendor(Option::V6,
                                                VENDOR_ID_CABLE_LABS));
    // Include ORO with TFTP servers suboption code being requested.
    opt_vendor->addOption(OptionPtr(new OptionUint16(Option::V6, DOCSIS3_V6_ORO,
                                                     DOCSIS3_V6_TFTP_SERVERS)));
    client.addExtraOption(opt_vendor);

    configure(CONFIGS[5], *client.getServer());

    ASSERT_NO_FATAL_FAILURE(doExchange(msg_type, client));

    // Vendor Specific Information option should be returned by the server.
    OptionVendorPtr vendor_opt = boost::dynamic_pointer_cast<
        OptionVendor>(client.config_.findOption(D6O_VENDOR_OPTS));
    ASSERT_TRUE(vendor_opt);

    // TFTP server suboption should be returned because it was requested
    // with Option Request suboption.
    Option6AddrLstPtr tftp = boost::dynamic_pointer_cast<
        Option6AddrLst>(vendor_opt->getOption(DOCSIS3_V6_TFTP_SERVERS));
    ASSERT_TRUE(tftp);

    // Address specified in the host scope should be used.
    Option6AddrLst::AddressContainer addrs = tftp->getAddresses();
    ASSERT_EQ(addrs.size(), 1);
    EXPECT_EQ("3000:1::234", addrs[0].toText());
}

// Test basic SARR scenarios against a server configured with one subnet
// containing two reservations.  One reservation with a hostname, one
// without a hostname. Scenarios:
//
// - Verify that a client when matched to a host reservation with a hostname
// gets that reservation and the lease hostname matches the reserved hostname
//
// - Verify that a client when matched to a host reservation without a hostname
// gets that reservation and the lease hostname is blank
//
// - Verify that a client that does not match a host reservation gets a dynamic
// lease and the hostname for the lease is blank.
//
TEST_F(HostTest, basicSarrs) {
    Dhcp6Client client;
    configure(CONFIGS[0], *client.getServer());

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and append IA_NA option
    // to the client's message.
    client.setDUID("01:02:03:04");
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and lease has reserved hostname
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("alice", lease_server->hostname_);

    // Now redo the client, adding one to the DUID
    client.clearConfig();
    client.modifyDUID();
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babf", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and that the server lease has NO hostname
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("", lease_server->hostname_);

    // Now redo the client with yet another DUID and verify that
    // we get a dynamic address.
    client.clearConfig();
    client.modifyDUID();
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client got a dynamic address
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and that the server lease has NO hostname
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("", lease_server->hostname_);
}

// Test basic SARR and renew situation with a client that matches a host
// reservation
TEST_F(HostTest, sarrAndRenew) {
    Dhcp6Client client;

    configure(CONFIGS[0], *client.getServer());

    // Configure client to request IA_NA.
    client.useNA();

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Now play with time
    client.fastFwdTime(1000);

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Send Renew message to the server.
    ASSERT_NO_THROW(client.doRenew());

    // Verify that we got an extended lease back
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client2.addr_.toText());

    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);

    // Make sure, that the client's lease matches the lease held by the
    // server and that we have the reserved host name.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    EXPECT_EQ("alice", lease_server2->hostname_);
}

// Test basic SARR and rebind situation with a client that matches a host
// reservation.
TEST_F(HostTest, sarrAndRebind) {
    Dhcp6Client client;

    configure(CONFIGS[0], *client.getServer());

    // Configure client to request IA_NA.
    client.useNA();

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Now play with time
    client.fastFwdTime(1000);

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());

    // Verify that we got an extended lease back
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client2.addr_.toText());

    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);

    // Make sure, that the client's lease matches the lease held by the
    // server and that we have the reserved host name.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    EXPECT_EQ("alice", lease_server2->hostname_);
}

// This test verfies that the host reservation by DUID is found by the
// server.
TEST_F(HostTest, reservationByDUID) {
    Dhcp6Client client;
    // Set DUID matching the one used to create host reservations.
    client.setDUID("01:02:03:05");
    // Run the actual test.
    testReservationByIdentifier(client, 1, "2001:db8:1::2");
}

// This test verfies that the host reservation by HW address is found
// by the server.
TEST_F(HostTest, reservationByHWAddress) {
    Dhcp6Client client;
    // Set link local address for the client which the server will
    // use to decode the HW address as 38:60:77:d5:ff:ee. This
    // decoded address will be used to search for host reservations.
    client.setLinkLocal(IOAddress("fe80::3a60:77ff:fed5:ffee"));
    // Run the actual test.
    testReservationByIdentifier(client, 1, "2001:db8:1::1");
}

// This test verifies that order in which host identifiers are used to
// retrieve host reservations can be controlled.
TEST_F(HostTest, hostIdentifiersOrder) {
    Dhcp6Client client;
    // Set DUID matching the one used to create host reservations.
    client.setDUID("01:02:03:05");
    // Set link local address for the client which the server will
    // use to decode the HW address as 38:60:77:d5:ff:ee. This
    // decoded address will be used to search for host reservations.
    client.setLinkLocal(IOAddress("fe80::3a60:77ff:fed5:ffee"));
    testReservationByIdentifier(client, 2, "2001:db8:1::2");
}

// This test checks that host specific options override subnet specific
// options. Overridden options are requested with Option Request
// option (Information-request case).
TEST_F(HostTest, overrideRequestedOptionsInformationRequest) {
    testOverrideRequestedOptions(DHCPV6_INFORMATION_REQUEST);
}

// This test checks that host specific options override subnet specific
// options. Overridden options are requested with Option Request
// option (Request case).
TEST_F(HostTest, overrideRequestedOptionsRequest) {
    testOverrideRequestedOptions(DHCPV6_REQUEST);
}

// This test checks that host specific options override subnet specific
// options. Overridden options are requested with Option Request
// option (Renew case).
TEST_F(HostTest, overrideRequestedOptionsRenew) {
    testOverrideRequestedOptions(DHCPV6_RENEW);
}

// This test checks that host specific options override subnet specific
// options. Overridden options are requested with Option Request
// option (Rebind case).
TEST_F(HostTest, overrideRequestedOptionsRebind) {
    testOverrideRequestedOptions(DHCPV6_REBIND);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Information-request case).
TEST_F(HostTest, testHostOnlyOptionsInformationRequest) {
    testHostOnlyOptions(DHCPV6_INFORMATION_REQUEST);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Request case).
TEST_F(HostTest, testHostOnlyOptionsRequest) {
    testHostOnlyOptions(DHCPV6_REQUEST);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Renew case).
TEST_F(HostTest, testHostOnlyOptionsRenew) {
    testHostOnlyOptions(DHCPV6_RENEW);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Rebind case).
TEST_F(HostTest, testHostOnlyOptionsRebind) {
    testHostOnlyOptions(DHCPV6_REBIND);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (Request case).
TEST_F(HostTest, overrideVendorOptionsRequest) {
    testOverrideVendorOptions(DHCPV6_REQUEST);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (Renew case).
TEST_F(HostTest, overrideVendorOptionsRenew) {
    testOverrideVendorOptions(DHCPV6_RENEW);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (Rebind case).
TEST_F(HostTest, overrideVendorOptionsRebind) {
    testOverrideVendorOptions(DHCPV6_REBIND);
}


} // end of anonymous namespace
