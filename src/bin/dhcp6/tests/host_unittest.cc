// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <list>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used by the Host reservation unit tests.
///
/// - Configuration 0:
///   Single subnet with two reservations, one with a hostname, one without
/// - Configuration 1:
///   Multiple reservations using different host identifiers.
/// - Configuration 2:
///   Same as configuration 1 but 'host-reservation-identifiers' specified
///   in non-default order.
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
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::10\" } ],"
        "    \"interface\" : \"eth0\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:04\","
        "        \"ip-addresses\": [ \"2001:db8:1:1::1\", \"2001:db8:1:1::2\","
                                    "\"2001:db8:1:1::3\" ],"
        "        \"prefixes\": [  \"3000:1:1::/32\", \"3000:1:2::/32\","
                                 "\"3000:1:3::/32\" ]"
        "    } ]"
        " } ]"
    "}"
};

class Reservation {
public:
    Reservation(const std::string& resource);

    bool isEmpty() const;

    bool isPrefix() const;

    static const Reservation& UNSPEC();

    operator std::string() const;

private:
    IOAddress prefix_;
    uint8_t prefix_len_;
};

Reservation::Reservation(const std::string& resource)
    : prefix_(IOAddress::IPV6_ZERO_ADDRESS()), prefix_len_(0) {
    size_t slash_pos = resource.find("/");
    if ((slash_pos != std::string::npos) && (slash_pos < resource.size() - 1)) {
        prefix_len_ = boost::lexical_cast<unsigned int>(resource.substr(slash_pos + 1));
    }
    prefix_ = IOAddress(resource.substr(0, slash_pos));
}

bool
Reservation::isEmpty() const {
    return (prefix_.isV6Zero());
}

bool
Reservation::isPrefix() const {
    return (!isEmpty() && (prefix_len_ > 0));
}

const Reservation& Reservation::UNSPEC() {
    static Reservation unspec("::/0");
    return (unspec);
}

Reservation::operator std::string() const {
    std::ostringstream s;
    s << "\"" << prefix_;
    if (prefix_len_ > 0) {
        s << "/" << static_cast<int>(prefix_len_);
    }
    s << "\"";
    return (s.str());
}

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
        client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

        // Perform 4-way exchange.
        ASSERT_NO_THROW(client.doSARR());

        // Verify that the client we got the reserved address
        ASSERT_EQ(1, client.getLeaseNum());
        Lease6 lease_client = client.getLease(0);
        EXPECT_EQ(exp_ip_address, lease_client.addr_.toText());
    }

    static void storeReservation(const Reservation& r,
                                 std::list<std::string>& address_list,
                                 std::list<std::string>& prefix_list);

    std::string configString(const DUID& duid,
                             const Reservation& r1 = Reservation::UNSPEC(),
                             const Reservation& r2 = Reservation::UNSPEC(),
                             const Reservation& r3 = Reservation::UNSPEC(),
                             const Reservation& r4 = Reservation::UNSPEC(),
                             const Reservation& r5 = Reservation::UNSPEC(),
                             const Reservation& r6 = Reservation::UNSPEC()) const;

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

void
HostTest::storeReservation(const Reservation& r,
                           std::list<std::string>& address_list,
                           std::list<std::string>& prefix_list) {
    if (!r.isEmpty()) {
        if (r.isPrefix()) {
            prefix_list.push_back(r);
        } else {
            address_list.push_back(r);
        }
    }
}

std::string
HostTest::configString(const DUID& duid,
                       const Reservation& r1, const Reservation& r2,
                       const Reservation& r3, const Reservation& r4,
                       const Reservation& r5, const Reservation& r6) const {
    std::list<std::string> address_list;
    std::list<std::string> prefix_list;
    storeReservation(r1, address_list, prefix_list);
    storeReservation(r2, address_list, prefix_list);
    storeReservation(r3, address_list, prefix_list);
    storeReservation(r4, address_list, prefix_list);
    storeReservation(r5, address_list, prefix_list);
    storeReservation(r6, address_list, prefix_list);

    std::ostringstream s;
    s << "{ "
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
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::10\" } ],"
        "    \"pd-pools\": [ { \"prefix\": \"3001::\", \"prefix-len\": 32,"
        "                      \"delegated-len\": 64 } ],"
        "    \"interface\" : \"eth0\"";

    if (!address_list.empty() || !prefix_list.empty()) {
        s << ","
            "    \"reservations\": ["
            "    {"
            "        \"duid\": ";
        s << "\"" << duid.toText() << "\",";

        if (!address_list.empty()) {
            s << "        \"ip-addresses\": [ "
              << boost::algorithm::join(address_list, ", ")
              << "]";
        }

        if (!prefix_list.empty()) {
            if (!address_list.empty()) {
                s << ", ";
            }
            s << "        \"prefixes\": [ "
              << boost::algorithm::join(prefix_list, ", ")
              << "]";
        }

        s <<  "    } ]";
    }

    s << " } ]"
         "}";

    return (s.str());
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

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

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
    client.clearRequestedIAs();
    client.requestAddress(1234);

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
    client.requestAddress();

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Now play with time
    client.fastFwdTime(1000);

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Do not send the hint while renewing.
    client.clearRequestedIAs();

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
    client.requestAddress();

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Now play with time
    client.fastFwdTime(1000);

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Do not send the hint while renewing.
    client.clearRequestedIAs();

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

TEST_F(HostTest, reservationMultipleIASolicit) {
    Dhcp6Client client;
    client.setDUID("01:02:03:04");

    const std::string c = configString(*client.getDuid(),
                                       Reservation("2001:db8:1:1::1"),
                                       Reservation("2001:db8:1:1::2"),
                                       Reservation("2001:db8:1:1::3"),
                                       Reservation("3000:1:1::/32"),
                                       Reservation("3000:1:2::/32"),
                                       Reservation("3000:1:3::/32"));

    ASSERT_NO_THROW(configure(c, *client.getServer()));

    client.requestAddress(1234);
    client.requestAddress(2345);
    client.requestAddress(3456);
    client.requestPrefix(5678);
    client.requestPrefix(6789);
    client.requestPrefix(7890);

    // Send Solicit and require that the client saves received configuration
    // so as we can test that advertised configuration is correct.
    ASSERT_NO_THROW(client.doSolicit(true));

    ASSERT_EQ(6, client.getLeaseNum());

    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::1")));
    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::2")));
    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::3")));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:1::"), 32));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:2::"), 32));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:3::"), 32));
}

TEST_F(HostTest, reservationMultipleIARequest) {
    Dhcp6Client client;
    client.setDUID("01:02:03:04");

    const std::string c = configString(*client.getDuid(),
                                       Reservation("2001:db8:1:1::1"),
                                       Reservation("2001:db8:1:1::2"),
                                       Reservation("2001:db8:1:1::3"),
                                       Reservation("3000:1:1::/32"),
                                       Reservation("3000:1:2::/32"),
                                       Reservation("3000:1:3::/32"));

    ASSERT_NO_THROW(configure(c, *client.getServer()));

    client.requestAddress(1234);
    client.requestAddress(2345);
    client.requestAddress(3456);
    client.requestPrefix(5678);
    client.requestPrefix(6789);
    client.requestPrefix(7890);

    ASSERT_NO_THROW(client.doSARR());

    ASSERT_EQ(6, client.getLeaseNum());

    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::1")));
    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::2")));
    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::3")));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:1::"), 32));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:2::"), 32));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:3::"), 32));
}

TEST_F(HostTest, reservationAndDynamicIAs) {
    Dhcp6Client client;
    client.setDUID("01:02:03:04");

    const std::string c = configString(*client.getDuid(),
                                       Reservation("2001:db8:1:1::2"),
                                       Reservation("2001:db8:1:1::3"),
                                       Reservation("3000:1:1::/32"),
                                       Reservation("3000:1:3::/32"));

    ASSERT_NO_THROW(configure(c, *client.getServer()));

    client.requestAddress(1234);
    client.requestAddress(2345);
    client.requestAddress(3456);
    client.requestPrefix(5678);
    client.requestPrefix(6789);
    client.requestPrefix(7890);

    // Send Solicit and require that the client saves received configuration
    // so as we can test that advertised configuration is correct.
    ASSERT_NO_THROW(client.doSolicit(true));

    ASSERT_EQ(6, client.getLeaseNum());

    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::2")));
    EXPECT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1:1::3")));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:1::"), 32));
    EXPECT_TRUE(client.hasLeaseForPrefix(IOAddress("3000:1:3::"), 32));

    EXPECT_TRUE(client.hasLeaseForAddressRange(IOAddress("2001:db8:1::1"),
                                               IOAddress("2001:db8:1::10")));
    EXPECT_TRUE(client.hasLeaseForPrefixPool(IOAddress("3001::"), 32, 64));
}

} // end of anonymous namespace
