// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used throughout the tests.
///
/// - Configuration 0:
///   - Used for testing direct traffic
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - Router option present: 10.0.0.200 and 10.0.0.201
///   - Domain Name Server option present: 10.0.0.202, 10.0.0.203.
///   - Log Servers option present: 192.0.2.200 and 192.0.2.201
///   - Quotes Servers option present: 192.0.2.202, 192.0.2.203.
///
const char* HOST_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"option-data\": [ {"
        "        \"name\": \"routers\","
        "        \"data\": \"10.0.0.200,10.0.0.201\""
        "    },"
        "    {"
        "        \"name\": \"domain-name-servers\","
        "        \"data\": \"10.0.0.202,10.0.0.203\""
        "    },"
        "    {"
        "        \"name\": \"log-servers\","
        "        \"data\": \"10.0.0.200,10.0.0.201\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"data\": \"10.0.0.202,10.0.0.203\""
        "    } ],"
        "    \"reservations\": [ "
        "    {"
        "        \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "        \"ip-address\": \"10.0.0.7\","
        "        \"option-data\": [ {"
        "            \"name\": \"cookie-servers\","
        "            \"data\": \"10.1.1.202,10.1.1.203\""
        "        },"
        "        {"
        "            \"name\": \"log-servers\","
        "            \"data\": \"10.1.1.200,10.1.1.201\""
        "        } ]"
        "    } ]"
        " } ]"
    "}",

// Configuration 1
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"option-data\": [ {"
        "        \"name\": \"routers\","
        "        \"data\": \"10.0.0.200,10.0.0.201\""
        "    },"
        "    {"
        "        \"name\": \"domain-name-servers\","
        "        \"data\": \"10.0.0.202,10.0.0.203\""
        "    },"
        "    {"
        "        \"name\": \"log-servers\","
        "        \"data\": \"10.0.0.200,10.0.0.201\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"data\": \"10.0.0.202,10.0.0.203\""
        "    } ],"
        "    \"reservations\": [ "
        "    {"
        "        \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "        \"ip-address\": \"10.0.0.7\","
        "        \"option-data\": [ {"
        "            \"name\": \"routers\","
        "            \"data\": \"10.1.1.200,10.1.1.201\""
        "        },"
        "        {"
        "            \"name\": \"domain-name-servers\","
        "            \"data\": \"10.1.1.202,10.1.1.203\""
        "        } ]"
        "    } ]"
        " } ]"
    "}"
};

/// @brief Test fixture class for testing static reservations of options.
class HostOptionsTest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    HostOptionsTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();

        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Destructor.
    ///
    /// Cleans up statistics after the test.
    virtual ~HostOptionsTest() {
        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

TEST_F(HostOptionsTest, overrideRequestedOptions) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS, DHO_LOG_SERVERS,
                          DHO_COOKIE_SERVERS);

    // Configure DHCP server.
    configure(HOST_CONFIGS[0], *client.getServer());

    // Perform 4-way exchange with the server but to not request any
    // specific address in the DHCPDISCOVER message.
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease for the reserved
    // address.
    ASSERT_EQ("10.0.0.7", client.config_.lease_.addr_.toText());

    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.dns_servers_[1].toText());
    // Make sure that the Quotes Servers option has been received.
    ASSERT_EQ(2, client.config_.quotes_servers_.size());
    EXPECT_EQ("10.1.1.202", client.config_.quotes_servers_[0].toText());
    EXPECT_EQ("10.1.1.203", client.config_.quotes_servers_[1].toText());
    // Make sure that the Log Servers option has been received.
    ASSERT_EQ(2, client.config_.log_servers_.size());
    EXPECT_EQ("10.1.1.200", client.config_.log_servers_[0].toText());
    EXPECT_EQ("10.1.1.201", client.config_.log_servers_[1].toText());
}

TEST_F(HostOptionsTest, overrideDefaultOptions) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    client.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS);

    // Configure DHCP server.
    configure(HOST_CONFIGS[1], *client.getServer());

    // Perform 4-way exchange with the server but to not request any
    // specific address in the DHCPDISCOVER message.
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease for the reserved
    // address.
    ASSERT_EQ("10.0.0.7", client.config_.lease_.addr_.toText());

    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.1.1.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.1.1.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("10.1.1.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("10.1.1.203", client.config_.dns_servers_[1].toText());
    // Make sure that the Quotes Servers option has been received.
    ASSERT_EQ(2, client.config_.quotes_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.quotes_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.quotes_servers_[1].toText());
    // Make sure that the Log Servers option has been received.
    ASSERT_EQ(2, client.config_.log_servers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.log_servers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.log_servers_[1].toText());
}


} // end of anonymous namespace
