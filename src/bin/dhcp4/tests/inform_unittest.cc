// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used throughout the Inform tests.
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
/// - Configuration 1:
///   - Use for testing relayed messages
///   - 1 subnet: 192.0.2.0/24
///   - Router option present: 192.0.2.200 and 192.0.2.201
///   - Domain Name Server option present: 192.0.2.202, 192.0.2.203.
///   - Log Servers option present: 192.0.2.200 and 192.0.2.201
///   - Quotes Servers option present: 192.0.2.202, 192.0.2.203.
///
/// - Configuration 2:
///   - This configuration provides reservations for next-server,
///     server-hostname and boot-file-name value.
///   - 1 subnet: 192.0.2.0/24
///   - 1 reservation for this subnet:
///     - Client's HW address: aa:bb:cc:dd:ee:ff
///     - next-server = 10.0.0.7
///     - server name = "some-name.example.org"
///     - boot-file-name = "bootfile.efi"
///
/// - Configuration 3:
///   - This configuration provides reservations for big options
///     server-hostname and boot-file-name value.
///   - 1 subnet: 192.0.2.0/24
///   - 1 reservation for this subnet:
///     - Client's HW address: aa:bb:cc:dd:ee:ff
///     - option 240 = data
///            -00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809
///            -00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809
///            -00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809
///            -data
const char* INFORM_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
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
        "        \"data\": \"10.0.0.202,10.0.0.203\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"data\": \"10.0.0.200,10.0.0.201\""
        "    } ]"
        " } ]"
    "}",

// Configuration 1
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": [ {"
        "        \"name\": \"routers\","
        "        \"data\": \"192.0.2.200,192.0.2.201\""
        "    },"
        "    {"
        "        \"name\": \"domain-name-servers\","
        "        \"data\": \"192.0.2.202,192.0.2.203\""
        "    },"
        "    {"
        "        \"name\": \"log-servers\","
        "        \"data\": \"10.0.0.200,10.0.0.201\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"data\": \"10.0.0.202,10.0.0.203\""
        "    } ]"
        " } ]"
    "}",

// Configuration 2
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"next-server\": \"10.0.0.1\","
        "\"server-hostname\": \"nohost\","
        "\"boot-file-name\": \"nofile\","
        "\"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"reservations\": [ "
        "       {"
        "         \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "         \"next-server\": \"10.0.0.7\","
        "         \"server-hostname\": \"some-name.example.org\","
        "         \"boot-file-name\": \"bootfile.efi\""
        "       }"
        "    ]"
        "} ]"
    "}",

// Configuration 3
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"next-server\": \"10.0.0.1\","
        "\"server-hostname\": \"nohost\","
        "\"boot-file-name\": \"nofile\","
        "\"option-def\": ["
        "    {"
        "        \"array\": false,"
        "        \"code\": 240,"
        "        \"encapsulate\": \"\","
        "        \"name\": \"my-option\","
        "        \"space\": \"dhcp4\","
        "        \"type\": \"string\""
        "    }"
        "],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"reservations\": [ "
        "       {"
        "         \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "         \"option-data\": ["
        "            {"
        "              \"always-send\": false,"
        "              \"code\": 240,"
        "              \"name\": \"my-option\","
        "              \"csv-format\": true,"
        "              \"data\": \"data"
        "-00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809"
        "-00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809"
        "-00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809"
        "-data\","
        "              \"space\": \"dhcp4\""
        "    }"
        "],"
        "       }"
        "    ]"
        "} ]"
    "}",
};

/// @brief Test fixture class for testing DHCPINFORM.
class InformTest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    InformTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Destructor.
    ///
    /// Cleans up statistics after the test.
    ~InformTest() {
        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

// Test that directly connected client's DHCPINFORM message is processed and
// DHCPACK message is sent back.
TEST_F(InformTest, directClientBroadcast) {
    Dhcp4Client client;
    // Configure DHCP server.
    configure(INFORM_CONFIGS[0], *client.getServer());
    // Request some configuration when DHCPINFORM is sent.
    client.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS);
    // Preconfigure the client with the IP address.
    client.createLease(IOAddress("10.0.0.56"), 600);

    // Send DHCPINFORM message to the server.
    ASSERT_NO_THROW(client.doInform());

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response should have been unicast to the ciaddr.
    EXPECT_EQ(IOAddress("10.0.0.56"), resp->getLocalAddr());
    // The ciaddr should have been copied.
    EXPECT_EQ(IOAddress("10.0.0.56"), resp->getCiaddr());
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());

    // Make sure that the Routers option has been received.
    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.dns_servers_[1].toText());
    // Make sure that the Log Servers option has been received.
    ASSERT_EQ(2, client.config_.quotes_servers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.quotes_servers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.quotes_servers_[1].toText());
    // Make sure that the Quotes Servers option has been received.
    ASSERT_EQ(2, client.config_.log_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.log_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.log_servers_[1].toText());

    // Check that we can send another DHCPINFORM message using
    // different ciaddr and we will get the configuration.
    client.createLease(IOAddress("10.0.0.12"), 600);
    // This time do not request Quotes Servers option and it should not
    // be returned.
    client.requestOptions(DHO_LOG_SERVERS);

    // Send DHCPINFORM.
    ASSERT_NO_THROW(client.doInform());

    // Make sure that the server responded.
    resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response should have been unicast to the ciaddr.
    EXPECT_EQ(IOAddress("10.0.0.12"), resp->getLocalAddr());
    // The ciaddr should have been copied.
    EXPECT_EQ(IOAddress("10.0.0.12"), resp->getCiaddr());
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());

    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the Routers option has been received.
    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.dns_servers_[1].toText());
    // Make sure that the Quotes Servers option hasn't been received.
    ASSERT_TRUE(client.config_.quotes_servers_.empty());
}

// This test checks that the server drops DHCPINFORM message when the
// source address and ciaddr is 0.
TEST_F(InformTest, directClientBroadcastNoAddress) {
    Dhcp4Client client;
    // Configure DHCP server.
    configure(INFORM_CONFIGS[0], *client.getServer());
    // Request some configuration when DHCPINFORM is sent.
    client.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS);
    // Send DHCPINFORM message to the server.
    ASSERT_NO_THROW(client.doInform());
    // Make sure that the server dropped the message.
    ASSERT_FALSE(client.getContext().response_);
}

// Test that client's DHCPINFORM message sent to a unicast address
// is received and processed by the server and that the DHCPACK is
// is sent.
TEST_F(InformTest, directClientUnicast) {
    Dhcp4Client client;
    // Configure DHCP server.
    configure(INFORM_CONFIGS[0], *client.getServer());
    // Preconfigure the client with the IP address.
    client.createLease(IOAddress("10.0.0.56"), 600);
    // Set remote address to unicast.
    client.setDestAddress(IOAddress("10.0.0.1"));
    // Send DHCPINFORM message to the server.
    ASSERT_NO_THROW(client.doInform());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response should have been unicast to the ciaddr.
    EXPECT_EQ(IOAddress("10.0.0.56"), resp->getLocalAddr());
    // The ciaddr should have been copied.
    EXPECT_EQ(IOAddress("10.0.0.56"), resp->getCiaddr());
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the Routers option has been received.
    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.dns_servers_[1].toText());
}

// This test checks that the server responds to the source address of the
// packet received from the directly connected client if the client didn't
// set the ciaddr.
TEST_F(InformTest, directClientNoCiaddr) {
    Dhcp4Client client;
    // Configure DHCP server.
    configure(INFORM_CONFIGS[0], *client.getServer());
    // Preconfigure the client with the IP address.
    client.createLease(IOAddress("10.0.0.56"), 600);
    // Send DHCPINFORM message (with ciaddr not set) to the server.
    ASSERT_NO_THROW(client.doInform(false));
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response should have been unicast to the client address.
    EXPECT_EQ(IOAddress("10.0.0.56"), resp->getLocalAddr());
    // The ciaddr should be 0.
    EXPECT_EQ(IOAddress("0.0.0.0"), resp->getCiaddr());
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    EXPECT_EQ(DHCP4_CLIENT_PORT, resp->getLocalPort());
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getRemotePort());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the Routers option has been received.
    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.dns_servers_[1].toText());
}

// This test checks that the server receiving DHCPINFORM via relay, unicasts the
// DHCPACK to the client (ciaddr).
TEST_F(InformTest, relayedClient) {
    Dhcp4Client client;
    // Configure DHCP server.
    configure(INFORM_CONFIGS[1], *client.getServer());
    // Message is relayed.
    client.useRelay();
    // Request some configuration when DHCPINFORM is sent.
    client.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS);
    // Preconfigure the client with the IP address.
    client.createLease(IOAddress("192.0.2.56"), 600);
    // Send DHCPINFORM message to the server.
    ASSERT_NO_THROW(client.doInform());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response should have been unicast to the ciaddr.
    EXPECT_EQ(IOAddress("192.0.2.56"), resp->getLocalAddr());
    // The ciaddr should have been copied.
    EXPECT_EQ(IOAddress("192.0.2.56"), resp->getCiaddr());
    // Response is unicast to the client, so it must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    EXPECT_EQ(DHCP4_CLIENT_PORT, resp->getLocalPort());
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getRemotePort());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the Routers option has been received.
    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("192.0.2.200", client.config_.routers_[0].toText());
    EXPECT_EQ("192.0.2.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("192.0.2.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("192.0.2.203", client.config_.dns_servers_[1].toText());
    // Make sure that the Quotes Servers option has been received.
    ASSERT_EQ(2, client.config_.quotes_servers_.size());
    EXPECT_EQ("10.0.0.202", client.config_.quotes_servers_[0].toText());
    EXPECT_EQ("10.0.0.203", client.config_.quotes_servers_[1].toText());
    // Make sure that the Log Servers option has been received.
    ASSERT_EQ(2, client.config_.log_servers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.log_servers_[0].toText());
    EXPECT_EQ("10.0.0.201", client.config_.log_servers_[1].toText());
}

// This test checks that the server can respond to the DHCPINFORM message
// received via relay when the ciaddr is not set.
TEST_F(InformTest, relayedClientNoCiaddr) {
    Dhcp4Client client;
    // Configure DHCP server.
    configure(INFORM_CONFIGS[1], *client.getServer());
    // Message is relayed.
    client.useRelay();
    // Send DHCPINFORM message to the server.
    ASSERT_NO_THROW(client.doInform());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response should go through a relay as there is no ciaddr.
    EXPECT_EQ(IOAddress("192.0.2.2"), resp->getLocalAddr());
    EXPECT_EQ(IOAddress("192.0.2.2"), resp->getGiaddr());
    EXPECT_EQ(1, resp->getHops());
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getLocalPort());
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getRemotePort());
    // In the case when the client didn't set the ciaddr and the message
    // was received via relay the server sets the Broadcast flag to help
    // the relay forwarding the message (without yiaddr) to the client.
    EXPECT_EQ(BOOTP_BROADCAST, resp->getFlags() & BOOTP_BROADCAST);
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the Routers option has been received.
    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("192.0.2.200", client.config_.routers_[0].toText());
    EXPECT_EQ("192.0.2.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("192.0.2.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("192.0.2.203", client.config_.dns_servers_[1].toText());
}

// This test verifies that the server assigns reserved values for the
// siaddr, sname and file fields carried within DHCPv4 message.
TEST_F(InformTest, messageFieldsReservations) {
    // Client has a reservation.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Message is relayed.
    client.useRelay();
    // Set explicit HW address so as it matches the reservation in the
    // configuration used below.
    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    // Configure DHCP server.
    configure(INFORM_CONFIGS[2], *client.getServer());
    // Client sends DHCPINFORM and should receive reserved fields.
    ASSERT_NO_THROW(client.doInform());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Check that the reserved values have been assigned.
    EXPECT_EQ("10.0.0.7", client.config_.siaddr_.toText());
    EXPECT_EQ("some-name.example.org", client.config_.sname_);
    EXPECT_EQ("bootfile.efi", client.config_.boot_file_name_);
}

// This test verifies that the server assigns and splits long options within
// DHCPv4 message.
TEST_F(InformTest, messageFieldsLongOptions) {
    // Client has a reservation.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Message is relayed.
    client.useRelay();
    // Set explicit HW address so as it matches the reservation in the
    // configuration used below.
    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    // Configure DHCP server.
    configure(INFORM_CONFIGS[3], *client.getServer());
    // Client requests big option.
    client.requestOption(240);
    // Client also sends multiple options with the same code.
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    // Create RAI options which should be fused by the server.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));
    for (uint8_t i = 0; i < 4; ++i) {
        // Create a buffer holding some binary data. This data will be
        // used as reference when we read back the data from a created
        // option.
        OptionBuffer buf_in(16);
        for (uint8_t j = 0; j < 16; ++j) {
            buf_in[j] = i * 16 + j;
        }

        OptionPtr circuit_id_opt(new Option(Option::V4,
                                            RAI_OPTION_AGENT_CIRCUIT_ID, buf_in));
        ASSERT_TRUE(circuit_id_opt);
        rai->addOption(circuit_id_opt);
    }
    client.addExtraOption(rai);

    // Client sends large options which should be split by the client.
    OptionDefinition opt_def_bar("option-foo", 231, "my-space", "binary",
                                 "option-foo-space");
    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(2560);
    for (uint32_t i = 0; i < 2560; ++i) {
        buf_in[i] = i;
    }

    boost::shared_ptr<OptionCustom> option;
    ASSERT_NO_THROW(option.reset(new OptionCustom(opt_def_bar, Option::V4, buf_in)));
    ASSERT_TRUE(option);
    client.addExtraOption(option);
    // Client sends DHCPINFORM and should receive reserved fields.
    ASSERT_NO_THROW(client.doInform());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Long option should have been split by the client on pack, serialized and
    // then restored.
    uint32_t count = 0;
    uint8_t index = 0;
    for (auto const& option : client.getContext().query_->options_) {
        if (option.first == 231) {
            for (auto const& value : option.second->getData()) {
                ASSERT_EQ(value, index);
                index++;
            }
            count++;
        }
    }
    ASSERT_EQ(1, count);

    count = 0;
    for (auto const& option : resp->options_) {
        if (option.first == DHO_DHCP_AGENT_OPTIONS) {
            for (auto const& suboption: option.second->getOptions()) {
                if (suboption.first == RAI_OPTION_AGENT_CIRCUIT_ID) {
                    uint8_t index = 0;
                    for (auto const& value : suboption.second->getData()) {
                        ASSERT_EQ(value, index);
                        index++;
                    }
                    count++;
                }
            }
        }
    }
    // Multiple options should have been fused by the server on unpack.
    ASSERT_EQ(count, 1);

    // Check that the reserved and requested values have been assigned.
    string expected =
        "-00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809"
        "-00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809"
        "-00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809";

    count = 0;
    string value = "";
    for (auto const& option : resp->options_) {
        if (option.second->getType() == 240) {
            value += string(reinterpret_cast<const char*>(&option.second->getData()[0]),
                            option.second->getData().size());
            count++;
        }
    }
    // Multiple options should have been fused by the server on unpack.
    ASSERT_EQ(count, 1);
    ASSERT_EQ(value, string("data") + expected + string("-data"));
}

/// This test verifies that after a client completes its INFORM exchange,
/// appropriate statistics are updated.
TEST_F(InformTest, statisticsInform) {
    Dhcp4Client client;
    // Configure DHCP server.
    configure(INFORM_CONFIGS[0], *client.getServer());
    // Request some configuration when DHCPINFORM is sent.
    client.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS);
    // Preconfigure the client with the IP address.
    client.createLease(IOAddress("10.0.0.56"), 600);

    // Send DHCPINFORM message to the server.
    ASSERT_NO_THROW(client.doInform());

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Ok, let's check the statistics.
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr pkt4_received = mgr.getObservation("pkt4-received");
    ObservationPtr pkt4_inform_received = mgr.getObservation("pkt4-inform-received");
    ObservationPtr pkt4_ack_sent = mgr.getObservation("pkt4-ack-sent");
    ObservationPtr pkt4_sent = mgr.getObservation("pkt4-sent");

    // All expected statistics must be present.
    ASSERT_TRUE(pkt4_received);
    ASSERT_TRUE(pkt4_inform_received);
    ASSERT_TRUE(pkt4_ack_sent);
    ASSERT_TRUE(pkt4_sent);

    // And they must have expected values.
    EXPECT_EQ(1, pkt4_received->getInteger().first);
    EXPECT_EQ(1, pkt4_inform_received->getInteger().first);
    EXPECT_EQ(1, pkt4_ack_sent->getInteger().first);
    EXPECT_EQ(1, pkt4_sent->getInteger().first);

    // Let the client send iform 4 times, which should make the server
    // to send 4 acks.
    ASSERT_NO_THROW(client.doInform());
    ASSERT_NO_THROW(client.doInform());
    ASSERT_NO_THROW(client.doInform());
    ASSERT_NO_THROW(client.doInform());

    // Let's see if the stats are properly updated.
    EXPECT_EQ(5, pkt4_received->getInteger().first);
    EXPECT_EQ(5, pkt4_inform_received->getInteger().first);
    EXPECT_EQ(5, pkt4_ack_sent->getInteger().first);
    EXPECT_EQ(5, pkt4_sent->getInteger().first);
}

} // end of anonymous namespace
