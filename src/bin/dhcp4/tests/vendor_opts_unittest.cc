// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file is dedicated to testing vendor options. There are several
// vendor options in DHCPv4:
//
// vivso (125) - vendor independent vendor specific option. This is by far the
//               most popular
// vendor specific (43) - this is probably the second most popular.
//               Unfortunately, its definition is blurry, so there are many
//               similar, but not exact implementations that do things in
//               different ways.
// vivco (124) - vendor indepdent vendor class option.
// class identifier (60) - not exactly vendor specific. It's a string, but the
//               content of that string identifies what kind of vendor device
//               this is.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/tests/pkt_captures.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/dhcp4.h>
#include <dhcpsrv/cfgmgr.h>

#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::config;
using namespace isc::dhcp::test;

/// @brief Class dedicated to testing vendor options in DHCPv4
///
/// For the time being it does not provide any additional functionality, but it
/// groups all vendor related tests under a single name. There were too many
/// tests in Dhcpv4SrvTest class anyway.
class VendorOptsTest : public Dhcpv4SrvTest {

};

/// Checks that it's possible to define and use a suboption 0.
TEST_F(VendorOptsTest, vendorOpsSubOption0) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    // Zero Touch provisioning
    string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"option-def\": ["
        "        {"
        "            \"name\": \"vendor-encapsulated-options\","
        "            \"code\": 43,"
        "            \"type\": \"empty\","
        "            \"encapsulate\": \"ZTP\""
        "        },"
        "        {"
        "            \"name\": \"config-file-name\","
        "            \"code\": 1,"
        "            \"space\": \"ZTP\","
        "            \"type\": \"string\""
        "        },"
        "        {"
        "            \"name\": \"image-file-name\","
        "            \"code\": 0,"
        "            \"space\": \"ZTP\","
        "            \"type\": \"string\""
        "        },"
        "        {"
        "            \"name\": \"image-file-type\","
        "            \"code\": 2,"
        "            \"space\": \"ZTP\","
        "            \"type\": \"string\""
        "        },"
        "        {"
        "            \"name\": \"transfer-mode\","
        "            \"code\": 3,"
        "            \"space\": \"ZTP\","
        "            \"type\": \"string\""
        "        },"
        "        {"
        "            \"name\": \"all-image-file-name\","
        "            \"code\": 4,"
        "            \"space\": \"ZTP\","
        "            \"type\": \"string\""
        "        },"
        "        {"
        "            \"name\": \"http-port\","
        "            \"code\": 5,"
        "            \"space\": \"ZTP\","
        "            \"type\": \"string\""
        "        }"
        "    ],"
        "    \"option-data\": ["
        "        {"
        "            \"name\": \"vendor-encapsulated-options\""
        "        },"
        "        {"
        "            \"name\": \"image-file-name\","
        "            \"data\": \"/dist/images/jinstall-ex.tgz\","
        "            \"space\": \"ZTP\""
        "        }"
        "    ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

        // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-encapsulated-options (code 43)
    OptionPtr opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    const OptionCollection& opts = opt->getOptions();
    ASSERT_EQ(1, opts.size());
    OptionPtr sopt = opts.begin()->second;
    ASSERT_TRUE(sopt);
    EXPECT_EQ(0, sopt->getType());

    // Check suboption 0 content.
    OptionStringPtr sopt0 =
        boost::dynamic_pointer_cast<OptionString>(sopt);
    ASSERT_TRUE(sopt0);
    EXPECT_EQ("/dist/images/jinstall-ex.tgz", sopt0->getValue());
}
