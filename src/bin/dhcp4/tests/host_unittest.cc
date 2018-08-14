// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/testutils/cql_schema.h>
#include <dhcpsrv/testutils/mysql_schema.h>
#include <dhcpsrv/testutils/pgsql_schema.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <boost/shared_ptr.hpp>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configuration(s) used throughout the Host tests.
///
/// - Configuration 0:
///   - Used for testing global host reservations
///   - 5 global reservations
///   - 1 subnet: 10.0.0.0/24
const char* CONFIGS[] = {
    // Configuration 0
    // 1 subnet, mode HR_GLOBAL,
    // global reservations for different identifier types
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"host-reservation-identifiers\": [ \"circuit-id\", \"hw-address\",\n"
        "                                    \"duid\", \"client-id\" ],\n"
        "\"reservations\": [ \n"
        "{\n"
        "   \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "   \"hostname\": \"hw-host-dynamic\"\n"
        "},\n"
        "{\n"
        "   \"hw-address\": \"01:02:03:04:05:06\",\n"
        "   \"hostname\": \"hw-host-fixed\",\n"
        "   \"ip-address\": \"192.0.1.77\"\n"
        "},\n"
        "{\n"
        "   \"duid\": \"01:02:03:04:05\",\n"
        "   \"hostname\": \"duid-host\"\n"
        "},\n"
        "{\n"
        "   \"circuit-id\": \"'charter950'\",\n"
        "   \"hostname\": \"circuit-id-host\"\n"
        "},\n"
        "{\n"
        "   \"client-id\": \"01:11:22:33:44:55:66\",\n"
        "   \"hostname\": \"client-id-host\"\n"
        "}\n"
        "],\n"
        "\"valid-lifetime\": 600,\n"
        "\"subnet4\": [ { \n"
        "    \"subnet\": \"10.0.0.0/24\", \n"
        "    \"reservation-mode\": \"global\","
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ]\n"
        "} ]\n"
    "}\n"
    ,
    // Configuration 1 global vs in-pool
    // 2 subnets, one mode default (aka HR_ALL), one mode HR_GLOBAL
    // Host reservations for the same client, one global, one in each subnet
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"valid-lifetime\": 600,\n"
        "\"reservations\": [ \n"
        "{\n"
        "   \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "   \"hostname\": \"global-host\"\n"
        "}\n"
        "],\n"
        "\"subnet4\": [\n"
        "    {\n"
        "        \"subnet\": \"10.0.0.0/24\", \n"
        "        \"id\": 10,"
        "        \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],\n"
        "        \"interface\": \"eth0\",\n"
        "        \"reservations\": [ \n"
        "        {\n"
        "           \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "           \"hostname\": \"subnet-10-host\"\n"
        "        }]\n"
        "    },\n"
        "    {\n"
        "        \"subnet\": \"192.0.2.0/26\", \n"
        "        \"id\": 20,"
        "        \"pools\": [ { \"pool\": \"192.0.2.10-192.0.2.63\" } ],\n"
        "        \"interface\": \"eth1\",\n"
        "        \"reservation-mode\": \"global\","
        "        \"reservations\": [ \n"
        "        {\n"
        "           \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "           \"hostname\": \"subnet-20-host\"\n"
        "        }]\n"
        "    }\n"
        "]\n"
    "}\n"
    ,
    // Configuration 2 global and out-of-pool
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"valid-lifetime\": 600,\n"
        "\"reservations\": [ \n"
        "{\n"
        "   \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "   \"hostname\": \"global-host\"\n"
        "}\n"
        "],\n"
        "\"subnet4\": [\n"
        "    {\n"
        "        \"subnet\": \"10.0.0.0/24\", \n"
        "        \"id\": 10,"
        "        \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],\n"
        "        \"interface\": \"eth0\",\n"
        "        \"reservation-mode\": \"out-of-pool\","
        "        \"reservations\": [ \n"
        "        {\n"
        "           \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "           \"hostname\": \"subnet-10-host\",\n"
        "           \"ip-address\": \"192.0.5.10\"\n"
        "        }]\n"
        "    }\n"
        "]\n"
        "}\n"
    ,
    // Configuration 3 global and all
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"valid-lifetime\": 600,\n"
        "\"reservations\": [ \n"
        "{\n"
        "   \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "   \"hostname\": \"global-host\"\n"
        "}\n"
        "],\n"
        "\"subnet4\": [\n"
        "    {\n"
        "        \"subnet\": \"10.0.0.0/24\", \n"
        "        \"id\": 10," "        \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],\n"
        "        \"interface\": \"eth0\",\n"
        "        \"reservation-mode\": \"all\","
        "        \"reservations\": [ \n"
        "        {\n"
        "           \"hw-address\": \"aa:bb:cc:dd:ee:ff\",\n"
        "           \"hostname\": \"subnet-10-host\",\n"
        "           \"ip-address\": \"192.0.5.10\"\n"
        "        }]\n"
        "    }\n"
        "]\n"
        "}\n"
};

/// @brief Test fixture class for testing global v4 reservations.
class HostTest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    HostTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();

        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Destructor.
    ///
    /// Cleans up statistics after the test.
    ~HostTest() {
        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

    /// @brief Conducts DORA exchange and checks assigned address and hostname
    ///
    /// If expected_host is empty, the test expects the hostname option to not
    /// be assigned.
    ///
    /// @param config configuration to be used
    /// @param client reference to a client instance
    /// @param expected_host expected hostname to be assigned (may be empty)
    /// @param expected_addr expected address to be assigned
    void runDoraTest(const std::string& config, Dhcp4Client& client,
                     const std::string& expected_host,
                     const std::string& expected_addr) {

        // Configure DHCP server.
        ASSERT_NO_FATAL_FAILURE(configure(config, *client.getServer()));
        client.requestOptions(DHO_HOST_NAME);

        // Perform 4-way exchange with the server but to not request any
        // specific address in the DHCPDISCOVER message.
        ASSERT_NO_THROW(client.doDORA());

        // Make sure that the server responded.
        ASSERT_TRUE(client.getContext().response_);
        Pkt4Ptr resp = client.getContext().response_;

        // Make sure that the server has responded with DHCPACK.
        ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

        // Fetch the hostname option
        OptionStringPtr hostname = boost::dynamic_pointer_cast<
                                   OptionString>(resp->getOption(DHO_HOST_NAME));

        if (expected_host.empty()) {
            ASSERT_FALSE(hostname);
        } else {
            ASSERT_TRUE(hostname);
            EXPECT_EQ(expected_host, hostname->getValue());
        }

        EXPECT_EQ(client.config_.lease_.addr_.toText(), expected_addr);
    }


};

// Verifies that a client, which fails to match to a global
// reservation, still gets a dynamic address when subnet mode is HR_GLOBAL
TEST_F(HostTest, globalHardwareNoMatch) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    client.setHWAddress("99:99:99:99:99:99");
    runDoraTest(CONFIGS[0], client, "", "10.0.0.10");
}

// Verifies that a client, that matches to a global hostname
// reservation, gets both the hostname and a dynamic address,
// when the subnet mode is HR_GLOBAL
TEST_F(HostTest, globalHardwareDynamicAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    runDoraTest(CONFIGS[0], client, "hw-host-dynamic", "10.0.0.10");
}

// Verifies that a client matched to a global address reservation
// gets both the hostname and the reserved address
// when the subnet mode is HR_GLOBAL
TEST_F(HostTest, globalHardwareFixedAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    //client.includeClientId(clientid_a);
    client.setHWAddress("01:02:03:04:05:06");
    runDoraTest(CONFIGS[0], client, "hw-host-fixed", "192.0.1.77");
}

// Verifies that a client can be matched to a global reservation by DUID
TEST_F(HostTest, globalDuid) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Set hw address to a none-matching value
    client.setHWAddress("99:99:99:99:99:99");

    // - FF is a client identifier type for DUID,
    // - 45454545 - represents 4 bytes for IAID
    // - 01:02:03:04:05 - is an actual DUID for which there is a
    client.includeClientId("FF:45:45:45:45:01:02:03:04:05");

    runDoraTest(CONFIGS[0], client, "duid-host", "10.0.0.10");
}

// Verifies that a client can be matched to a global reservation by circuit-id
TEST_F(HostTest, globalCircuitId) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Set hw address to a none-matching value
    client.setHWAddress("99:99:99:99:99:99");

    // Use relay agent so as the circuit-id can be inserted.
    client.useRelay(true, IOAddress("10.0.0.1"), IOAddress("10.0.0.2"));

    // Set the circuit id
    client.setCircuitId("charter950");

    runDoraTest(CONFIGS[0], client, "circuit-id-host", "10.0.0.10");
}

// Verifies that a client can be matched to a global reservation by client-id
TEST_F(HostTest, globalClientID) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Set hw address to a none-matching value
    client.setHWAddress("99:99:99:99:99:99");

    // - 01 is a client identifier type for CLIENT_ID,
    // - 11:22:33:44:55:66 - is an actual DUID for which there is a
    client.includeClientId("01:11:22:33:44:55:66");

    runDoraTest(CONFIGS[0], client, "client-id-host", "10.0.0.10");
}

// Verifies that even when a matching global reservation exists,
// client will get a subnet scoped reservation, when subnet
// reservation mode is default
TEST_F(HostTest, defaultOverGlobal) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Hardware address matches all reservations
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Subnet 10 usses default HR mode(i.e. "in-pool"), so its
    // reservation should be used, rather than global.
    runDoraTest(CONFIGS[1], client, "subnet-10-host", "10.0.0.10");
}

// Verifies that when there are matching reservations at
// both the global and subnet levels, client will be matched
// to the global reservation, when subnet reservation mode
// is HR_GLOBAL.
TEST_F(HostTest, globalOverSubnet) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Hardware address matches all reservations
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Change to subnet 20
    client.setIfaceName("eth1");

    // Subnet 20 usses global HR mode, so the global
    // reservation should be used, rather than the subnet one.
    runDoraTest(CONFIGS[1], client, "global-host", "192.0.2.10");
}

// Verifies that when there are matching reservations at
// both the global and subnet levels, client will be matched
// to the subnet reservation, when subnet reservation mode
// is HR_OUT_OF_POOL
TEST_F(HostTest, outOfPoolOverGlobal) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Hardware address matches all reservations
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Subnet 10 usses default HR mode(i.e. "in-pool"), so its
    // reservation should be used, rather than global.
    runDoraTest(CONFIGS[2], client, "subnet-10-host", "192.0.5.10");
}

// Verifies that when there are matching reservations at
// both the global and subnet levels, client will be matched
// to the subnet reservation, when subnet reservation mode
// is HR_ALL
TEST_F(HostTest, allOverGlobal) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Hardware address matches all reservations
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Subnet 10 usses default HR mode(i.e. "in-pool"), so its
    // reservation should be used, rather than global.
    runDoraTest(CONFIGS[3], client, "subnet-10-host", "192.0.5.10");
}

} // end of anonymous namespace
