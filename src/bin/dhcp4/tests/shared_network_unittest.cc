// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;

namespace {

const char* NETWORKS_CONFIG[] = {
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "},"
    "\"valid-lifetime\": 600,"
    "\"shared-networks\": ["
    "    {"
    "        \"name\": \"frog\""
    "        \"subnet4\": ["
    "            {"
    "                \"subnet\": \"192.0.2.0/26\","
    "                \"id\": 10,"
    "                \"pools\": ["
    "                    {"
    "                        \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                    }"
    "                ]"
    "            },"
    "            {"
    "                \"subnet\": \"10.0.0.0/24\","
    "                \"id\": 100,"
    "                \"pools\": ["
    "                    {"
    "                        \"pool\": \10.0.0.1 - 10.0.0.254\""
    "                    }"
    "                ]"
    "            }"
    "        ]"
    "    }"
    "],"
    "\"subnet4\": ["
    "    \"subnet\": \"192.0.2.64/26\","
    "    \"id\": 1000,"
    "    \"pools\": ["
    "        {"
    "            \"pool\": \"192.0.2.65 - 192.0.2.127\""
    "        }"
    "    ]"
    "]"
};

/// @brief Test fixture class for DHCPv4 server using shared networks.
class Dhcpv4SharedNetworkTest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor.
    Dhcpv4SharedNetworkTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();
        StatsMgr::instance().removeAll();
    }

    /// @brief Destructor.
    virtual ~Dhcpv4SharedNetworkTest() {
        StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Selected subnet is out of shared network.
TEST_F(Dhcpv4SharedNetworkTest, outOfSharedNetworkAllocation) {
}

// Shared network is selected based on giaddr value.
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSelectedByRelay) {
}

// Running out of addresses within a subnet in a shared network.
TEST_F(Dhcpv4SharedNetworkTest, poolInSharedNetworkShortage) {
}

// Running out of addresses within entire shared network.
TEST_F(Dhcpv4SharedNetworkTest, addressShortageInNetwork) {
}

// Providing a hint for any address belonging to a shared network.
TEST_F(Dhcpv4SharedNetworkTest, hintWithinSharedNetwork) {
}

// Access to a subnet within shared network is restricted by client
// classification.
TEST_F(Dhcpv4SharedNetworkTest, subnetInSharedNetworkSelectedByClass) {
}

// IPv4 address reservation exists in one of the subnets within
// shared network.
TEST_F(Dhcpv4SharedNetworkTest, reservationInSharedNetwork) {
}

// Reserved address can't be assigned until access to a subnet is
// restricted by classification.
TEST_F(Dhcpv4SharedNetworkTest, reservationAccessRestrictedByClass) {
}

// Multiple subnets within a shared network contain reservations for
// the same client.
TEST_F(Dhcpv4SharedNetworkTest, reservationsInDifferentSubnets) {
}

// Some options are specified on the shared subnet level, some on the
// subnets level.
TEST_F(Dhcpv4SharedNetworkTest, optionsDerivation) {
}

// Host reservations include class specification.
TEST_F(Dhcpv4SharedNetworkTest, classesInReservations) {
}



} // end of anonymous namespace
