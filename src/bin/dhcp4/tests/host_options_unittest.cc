// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option_int.h>
#include <dhcp/option_vendor.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Boolean value used to signal stateless configuration test.
const bool STATELESS = true;

/// @brief Boolean value used to signal stateful configuration test.
const bool STATEFUL = false;

/// @brief Set of JSON configurations used throughout the tests.
///
/// - Configuration 0:
///   - Used to test that host specific options override subnet specific
///     options when these options are requested with PRL option.
///   - Single subnet 10.0.0.0/24 with a pool of 10.0.0.10-10.0.0.100
///   - 4 options configured within subnet scope
///     - routers: 10.0.0.200,10.0.0.201,
///     - domain-name-servers: 10.0.0.202,10.0.0.203,
///     - log-servers: 10.0.0.200,10.0.0.201,
///     - cookie-servers: 10.0.0.202,10.0.0.203
///   - Single reservation within the subnet:
///     - HW address: aa:bb:cc:dd:ee:ff
///     - ip-address: 10.0.0.7
///     - Two options overriding subnet specific options:
///       - cookie-servers: 10.1.1.202, 10.1.1.203
///       - log-servers: 10.1.1.200, 10.1.1.201
///
/// - Configuration 1:
///   - Used to test that host specific options override subnet specific
///     default options. Default options are those that are sent even when
///     not requested by a client.
///   - Single subnet 10.0.0.0/24 with a pool of 10.0.0.10-10.0.0.100
///   - 4 options configured within subnet scope
///     - routers: 10.0.0.200,10.0.0.201,
///     - domain-name-servers: 10.0.0.202,10.0.0.203,
///     - log-servers: 10.0.0.200,10.0.0.201,
///     - cookie-servers: 10.0.0.202,10.0.0.203
///   - Single reservation within the subnet:
///     - HW address: aa:bb:cc:dd:ee:ff
///     - ip-address: 10.0.0.7
///     - Two options overriding subnet specific default options:
///       - routers: 10.1.1.200, 10.1.1.201
///       - domain-name-servers: 10.1.1.202, 10.1.1.203
///
/// - Configuration 2:
///   - Used to test that client receives options solely specified in a
///     host scope.
///   - Single reservation within the subnet:
///     - HW address: aa:bb:cc:dd:ee:ff
///     - ip-address: 10.0.0.7
///     - Two options:
///       - routers: 10.1.1.200, 10.1.1.201
///       - cookie-servers: 10.1.1.202, 10.1.1.203
///
/// - Configuration 3:
///   - Used to test that host specific vendor options override globally
///     specified vendor options.
///   - Globally specified option 125 with Cable Labs vendor id.
///     - TFTP servers sub option: 10.0.0.202,10.0.0.203
///   - Single subnet 10.0.0.0/24 with a pool of 10.0.0.10-10.0.0.100
///   - Single reservation within the subnet:
///     - HW address: aa:bb:cc:dd:ee:ff
///     - ip-address 10.0.0.7
///     - Vendor option for Cable Labs vendor id specified for the reservation:
///       - TFTP servers suboption overriding globally specified suboption:
///         10.1.1.202,10.1.1.203
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
        "    \"relay\": { \"ip-address\": \"10.0.0.233\" },"
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
        "        \"data\": \"10.0.0.204,10.0.0.205\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"data\": \"10.0.0.206,10.0.0.207\""
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
        "    \"relay\": { \"ip-address\": \"10.0.0.233\" },"
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
        "        \"data\": \"10.0.0.204,10.0.0.205\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"data\": \"10.0.0.206,10.0.0.207\""
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
    "}",

// Configuration 2
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"relay\": { \"ip-address\": \"10.0.0.233\" },"
        "    \"reservations\": [ "
        "    {"
        "        \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "        \"ip-address\": \"10.0.0.7\","
        "        \"option-data\": [ {"
        "            \"name\": \"routers\","
        "            \"data\": \"10.1.1.200,10.1.1.201\""
        "        },"
        "        {"
        "            \"name\": \"cookie-servers\","
        "            \"data\": \"10.1.1.206,10.1.1.207\""
        "        } ]"
        "    } ]"
        " } ]"
    "}",

// Configuration 3
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"option-data\": [ {"
        "    \"name\": \"vivso-suboptions\","
        "    \"data\": \"4491\""
        "},"
        "{"
        "    \"name\": \"tftp-servers\","
        "    \"space\": \"vendor-4491\","
        "    \"data\": \"10.0.0.202,10.0.0.203\""
        "} ],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"relay\": { \"ip-address\": \"10.0.0.233\" },"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"reservations\": [ "
        "    {"
        "        \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "        \"ip-address\": \"10.0.0.7\","
        "        \"option-data\": [ {"
        "            \"name\": \"vivso-suboptions\","
        "            \"data\": \"4491\""
        "        },"
        "        {"
        "            \"name\": \"tftp-servers\","
        "            \"space\": \"vendor-4491\","
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
    }

    /// @brief Verifies that host specific options override subnet specific
    /// options.
    ///
    /// Overridden options are requested with Parameter Request List
    /// option.
    ///
    /// @param stateless Boolean value indicating if stateless or stateful
    /// configuration should be performed.
    void testOverrideRequestedOptions(const bool stateless);

    /// @brief Verifies that host specific options override subnet specific
    /// options.
    ///
    /// Overridden options are the options which server sends regardless
    /// if they are requested with Parameter Request List option or not.
    ///
    /// @param stateless Boolean value indicating if stateless or stateful
    /// configuration should be performed.
    void testOverrideDefaultOptions(const bool stateless);

    /// @brief Verifies that client receives options when they are solely
    /// defined in the host scope (and not in the global or subnet scope).
    ///
    /// @param stateless Boolean value indicating if stateless or stateful
    /// configuration should be performed.
    void testHostOnlyOptions(const bool stateless);

    /// @brief Verifies that host specific vendor options override vendor
    /// options defined in the global scope.
    ///
    /// @param stateless Boolean value indicating if stateless or stateful
    /// configuration should be performed.
    void testOverrideVendorOptions(const bool stateless);

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

void
HostOptionsTest::testOverrideRequestedOptions(const bool stateless) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS, DHO_LOG_SERVERS,
                          DHO_COOKIE_SERVERS);

    // Configure DHCP server.
    configure(HOST_CONFIGS[0], *client.getServer());

    if (stateless) {
        // Need to relay the message from a specific address which can
        // be matched with a configured subnet.
        client.useRelay(true, IOAddress("10.0.0.233"));
        ASSERT_NO_THROW(client.doInform());

    } else {
        // Perform 4-way exchange with the server but to not request any
        // specific address in the DHCPDISCOVER message.
        ASSERT_NO_THROW(client.doDORA());
    }

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    if (!stateless) {
        // Make sure that the client has got the lease for the reserved
        // address.
        ASSERT_EQ("10.0.0.7", client.config_.lease_.addr_.toText());
    }

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

void
HostOptionsTest::testOverrideDefaultOptions(const bool stateless) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    client.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS);

    // Configure DHCP server.
    configure(HOST_CONFIGS[1], *client.getServer());

    if (stateless) {
        // Need to relay the message from a specific address which can
        // be matched with a configured subnet.
        client.useRelay(true, IOAddress("10.0.0.233"));
        ASSERT_NO_THROW(client.doInform());

    } else {
        // Perform 4-way exchange with the server but to not request any
        // specific address in the DHCPDISCOVER message.
        ASSERT_NO_THROW(client.doDORA());
    }

    // Perform 4-way exchange with the server but to not request any
    // specific address in the DHCPDISCOVER message.
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    if (!stateless) {
        // Make sure that the client has got the lease for the reserved
        // address.
        ASSERT_EQ("10.0.0.7", client.config_.lease_.addr_.toText());
    }

    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.1.1.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.1.1.201", client.config_.routers_[1].toText());
    // Make sure that the DNS Servers option has been received.
    ASSERT_EQ(2, client.config_.dns_servers_.size());
    EXPECT_EQ("10.1.1.202", client.config_.dns_servers_[0].toText());
    EXPECT_EQ("10.1.1.203", client.config_.dns_servers_[1].toText());
    // Make sure that the Quotes Servers option has been received.
    ASSERT_EQ(2, client.config_.quotes_servers_.size());
    EXPECT_EQ("10.0.0.206", client.config_.quotes_servers_[0].toText());
    EXPECT_EQ("10.0.0.207", client.config_.quotes_servers_[1].toText());
    // Make sure that the Log Servers option has been received.
    ASSERT_EQ(2, client.config_.log_servers_.size());
    EXPECT_EQ("10.0.0.204", client.config_.log_servers_[0].toText());
    EXPECT_EQ("10.0.0.205", client.config_.log_servers_[1].toText());
}

void
HostOptionsTest::testHostOnlyOptions(const bool stateless) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    client.requestOptions(DHO_COOKIE_SERVERS);

    // Configure DHCP server.
    configure(HOST_CONFIGS[2], *client.getServer());

    if (stateless) {
        // Need to relay the message from a specific address which can
        // be matched with a configured subnet.
        client.useRelay(true, IOAddress("10.0.0.233"));
        ASSERT_NO_THROW(client.doInform());

    } else {
        // Perform 4-way exchange with the server but to not request any
        // specific address in the DHCPDISCOVER message.
        ASSERT_NO_THROW(client.doDORA());
    }

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    if (!stateless) {
        // Make sure that the client has got the lease for the reserved
        // address.
        ASSERT_EQ("10.0.0.7", client.config_.lease_.addr_.toText());
    }

    // Make sure that the Routers options has been received.
    ASSERT_EQ(2, client.config_.routers_.size());
    EXPECT_EQ("10.1.1.200", client.config_.routers_[0].toText());
    EXPECT_EQ("10.1.1.201", client.config_.routers_[1].toText());
    // Make sure that the Quotes Servers option has been received.
    ASSERT_EQ(2, client.config_.quotes_servers_.size());
    EXPECT_EQ("10.1.1.206", client.config_.quotes_servers_[0].toText());
    EXPECT_EQ("10.1.1.207", client.config_.quotes_servers_[1].toText());

    // Other options are not configured and should not be delivered.
    EXPECT_EQ(0, client.config_.dns_servers_.size());
    EXPECT_EQ(0, client.config_.log_servers_.size());
}

void
HostOptionsTest::testOverrideVendorOptions(const bool stateless) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Client needs to include V-I Vendor Specific Information option
    // to include ORO suboption, which the server will use to determine
    // which suboptions should be returned to the client.
    OptionVendorPtr opt_vendor(new OptionVendor(Option::V4,
                                                VENDOR_ID_CABLE_LABS));
    // Include ORO with TFTP servers suboption code being requested.
    opt_vendor->addOption(OptionPtr(new OptionUint8(Option::V4, DOCSIS3_V4_ORO,
                                                    DOCSIS3_V4_TFTP_SERVERS)));
    client.addExtraOption(opt_vendor);

    // Configure DHCP server.
    configure(HOST_CONFIGS[3], *client.getServer());

    if (stateless) {
        // Need to relay the message from a specific address which can
        // be matched with a configured subnet.
        client.useRelay(true, IOAddress("10.0.0.233"));
        ASSERT_NO_THROW(client.doInform());

    } else {
        // Perform 4-way exchange with the server.
        ASSERT_NO_THROW(client.doDORA());
    }

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    if (!stateless) {
        // Make sure that the client has got the lease for the reserved
        // address.
        ASSERT_EQ("10.0.0.7", client.config_.lease_.addr_.toText());
    }

    // Make sure the server has responded with a V-I Vendor Specific
    // Information option with exactly one suboption.
    ASSERT_EQ(1, client.config_.vendor_suboptions_.size());
    // Assume this suboption is a TFTP servers suboption.
    std::multimap<unsigned int, OptionPtr>::const_iterator opt =
        client.config_.vendor_suboptions_.find(DOCSIS3_V4_TFTP_SERVERS);
    ASSERT_TRUE(opt->second);
    Option4AddrLstPtr opt_tftp = boost::dynamic_pointer_cast<
        Option4AddrLst>(opt->second);
    ASSERT_TRUE(opt_tftp);
    // TFTP servers suboption should contain addresses specified on host level.
    const Option4AddrLst::AddressContainer& tftps = opt_tftp->getAddresses();
    ASSERT_EQ(2, tftps.size());
    EXPECT_EQ("10.1.1.202", tftps[0].toText());
    EXPECT_EQ("10.1.1.203", tftps[1].toText());
}

// This test checks that host specific options override subnet specific
// options. Overridden options are requested with Parameter Request List
// option (stateless case).
TEST_F(HostOptionsTest, overrideRequestedOptionsStateless) {
    testOverrideRequestedOptions(STATELESS);
}

// This test checks that host specific options override subnet specific
// options. Overridden options are requested with Parameter Request List
// option (stateful case).
TEST_F(HostOptionsTest, overrideRequestedOptionsStateful) {
    testOverrideRequestedOptions(STATEFUL);
}

// This test checks that host specific options override subnet specific
// options. Overridden options are the options which server sends
// regardless if they are requested with Parameter Request List option
// or not (stateless case).
TEST_F(HostOptionsTest, overrideDefaultOptionsStateless) {
    testOverrideDefaultOptions(STATELESS);
}

// This test checks that host specific options override subnet specific
// options. Overridden options are the options which server sends
// regardless if they are requested with Parameter Request List option
// or not (stateful case).
TEST_F(HostOptionsTest, overrideDefaultOptionsStateful) {
    testOverrideDefaultOptions(STATEFUL);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (stateless case).
TEST_F(HostOptionsTest, hostOnlyOptionsStateless) {
    testHostOnlyOptions(STATELESS);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (stateful case).
TEST_F(HostOptionsTest, hostOnlyOptionsStateful) {
    testHostOnlyOptions(STATEFUL);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (stateless case).
TEST_F(HostOptionsTest, overrideVendorOptionsStateless) {
    testOverrideVendorOptions(STATELESS);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (stateful case).
TEST_F(HostOptionsTest, overrideVendorOptionsStateful) {
    testOverrideVendorOptions(STATEFUL);
}

} // end of anonymous namespace
