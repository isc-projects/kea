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
// Configuration 4
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
        "   \"ip-address\": \"10.0.0.7\"\n"
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
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ]\n"
        "} ]\n"
    "}\n"
};

/// @brief Test fixture class for testing v4 exchanges.
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

    void runDoraTest(const std::string& config, Dhcp4Client& client, 
                     const std::string& expected_host, 
                     const std::string& expected_addr) {

        // Configure DHCP server.
        configure(config, *client.getServer());
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

TEST_F(HostTest, globalHardwareDynamicAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    runDoraTest(CONFIGS[0], client, "hw-host-dynamic", "10.0.0.10");
}


TEST_F(HostTest, globalHardwareFixedAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    //client.includeClientId(clientid_a);
    client.setHWAddress("01:02:03:04:05:06");
    runDoraTest(CONFIGS[0], client, "hw-host-fixed", "10.0.0.7");
}

} // end of anonymous namespace
