// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file is dedicated to testing vendor options in DHCPv6. There
// are several related options:
//
// client-class (15) - this specifies (as a plain string) what kind of
//                     device this is
// vendor-class (16) - contains an enterprise-id followed by zero or
//                     more of vendor-class data.
// vendor-option (17) - contains an enterprise-id followed by zero or
//                     more vendor suboptions

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp/tests/pkt_captures.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/option_string.h>
#include <cc/command_interpreter.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::asiolink;

/// @brief Class dedicated to testing vendor options in DHCPv6
///
/// For the time being it does not provide any additional functionality, but it
/// groups all vendor related tests under a single name. There were too many
/// tests in Dhcpv4SrvTest class anyway.
class VendorOptsTest : public Dhcpv6SrvTest {

};

// Checks if server is able to handle a relayed traffic from DOCSIS3.0 modems
TEST_F(VendorOptsTest, docsisVendorOptionsParse) {

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt6Ptr sol = PktCaptures::captureDocsisRelayedSolicit();
    EXPECT_NO_THROW(sol->unpack());

    // Check if the packet contain
    OptionPtr opt = sol->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    EXPECT_TRUE(vendor->getOption(DOCSIS3_V6_ORO));
    EXPECT_TRUE(vendor->getOption(36));
    EXPECT_TRUE(vendor->getOption(35));
    EXPECT_TRUE(vendor->getOption(DOCSIS3_V6_DEVICE_TYPE));
    EXPECT_TRUE(vendor->getOption(3));
    EXPECT_TRUE(vendor->getOption(4));
    EXPECT_TRUE(vendor->getOption(5));
    EXPECT_TRUE(vendor->getOption(6));
    EXPECT_TRUE(vendor->getOption(7));
    EXPECT_TRUE(vendor->getOption(8));
    EXPECT_TRUE(vendor->getOption(9));
    EXPECT_TRUE(vendor->getOption(DOCSIS3_V6_VENDOR_NAME));
    EXPECT_TRUE(vendor->getOption(15));

    EXPECT_FALSE(vendor->getOption(20));
    EXPECT_FALSE(vendor->getOption(11));
    EXPECT_FALSE(vendor->getOption(17));
}

// Checks if server is able to parse incoming docsis option and extract suboption 1 (docsis ORO)
TEST_F(VendorOptsTest, docsisVendorORO) {

    NakedDhcpv6Srv srv(0);

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt6Ptr sol = PktCaptures::captureDocsisRelayedSolicit();
    ASSERT_NO_THROW(sol->unpack());

    // Check if the packet contains vendor options option
    OptionPtr opt = sol->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    opt = vendor->getOption(DOCSIS3_V6_ORO);
    ASSERT_TRUE(opt);

    OptionUint16ArrayPtr oro = boost::dynamic_pointer_cast<OptionUint16Array>(opt);
    EXPECT_TRUE(oro);
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsORO) {

    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-def\": [ {"
        "        \"name\": \"config-file\","
        "        \"code\": 33,"
        "        \"type\": \"string\","
        "        \"space\": \"vendor-4491\""
        "     } ],"
        "    \"option-data\": [ {"
        "          \"name\": \"config-file\","
        "          \"space\": \"vendor-4491\","
        "          \"data\": \"normal_erouter_v6.cm\""
        "        }],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"preferred-lifetime\": 3000,"
        "    \"valid-lifetime\": 4000,"
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    AllocEngine::ClientContext6 ctx;
    bool drop = false;
    srv_.initContext(sol, ctx, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr adv = srv_.processSolicit(ctx);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // We did not include any vendor opts in SOLICIT, so there should be none
    // in ADVERTISE.
    ASSERT_FALSE(adv->getOption(D6O_VENDOR_OPTS));

    // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
    // That suboption has code 1 and is a docsis ORO option.
    boost::shared_ptr<OptionUint16Array> vendor_oro(new OptionUint16Array(Option::V6,
                                                                          DOCSIS3_V6_ORO));
    vendor_oro->addValue(DOCSIS3_V6_CONFIG_FILE); // Request option 33
    OptionPtr vendor(new OptionVendor(Option::V6, 4491));
    vendor->addOption(vendor_oro);
    sol->addOption(vendor);

    // Need to process SOLICIT again after requesting new option.
    AllocEngine::ClientContext6 ctx2;
    srv_.initContext(sol, ctx2, drop);
    ASSERT_FALSE(drop);
    adv = srv_.processSolicit(ctx2);
    ASSERT_TRUE(adv);

    // Check if there is vendor option response
    OptionPtr tmp = adv->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(tmp);

    // The response should be OptionVendor object
    boost::shared_ptr<OptionVendor> vendor_resp =
        boost::dynamic_pointer_cast<OptionVendor>(tmp);
    ASSERT_TRUE(vendor_resp);

    OptionPtr docsis33 = vendor_resp->getOption(33);
    ASSERT_TRUE(docsis33);

    OptionStringPtr config_file = boost::dynamic_pointer_cast<OptionString>(docsis33);
    ASSERT_TRUE(config_file);
    EXPECT_EQ("normal_erouter_v6.cm", config_file->getValue());
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the persistent options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptions) {

    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-def\": [ {"
        "        \"name\": \"config-file\","
        "        \"code\": 33,"
        "        \"type\": \"string\","
        "        \"space\": \"vendor-4491\""
        "     } ],"
        "    \"option-data\": [ {"
        "          \"name\": \"config-file\","
        "          \"space\": \"vendor-4491\","
        "          \"data\": \"normal_erouter_v6.cm\","
        "          \"always-send\": true"
        "        }],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"preferred-lifetime\": 3000,"
        "    \"valid-lifetime\": 4000,"
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Let's add a vendor-option (vendor-id=4491).
    OptionPtr vendor(new OptionVendor(Option::V6, 4491));
    sol->addOption(vendor);

    // Pass it to the server and get an advertise
    AllocEngine::ClientContext6 ctx;
    bool drop = false;
    srv_.initContext(sol, ctx, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr adv = srv_.processSolicit(ctx);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // Check if there is vendor option response
    OptionPtr tmp = adv->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(tmp);

    // The response should be OptionVendor object
    boost::shared_ptr<OptionVendor> vendor_resp =
        boost::dynamic_pointer_cast<OptionVendor>(tmp);
    ASSERT_TRUE(vendor_resp);

    OptionPtr docsis33 = vendor_resp->getOption(33);
    ASSERT_TRUE(docsis33);

    OptionStringPtr config_file = boost::dynamic_pointer_cast<OptionString>(docsis33);
    ASSERT_TRUE(config_file);
    EXPECT_EQ("normal_erouter_v6.cm", config_file->getValue());
}

// Test checks whether it is possible to use option definitions defined in
// src/lib/dhcp/docsis3_option_defs.h.
TEST_F(VendorOptsTest, vendorOptionsDocsisDefinitions) {
    ConstElementPtr x;
    string config_prefix = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-data\": [ {"
        "          \"name\": \"config-file\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": ";
    string config_postfix = ","
        "          \"data\": \"normal_erouter_v6.cm\","
        "          \"csv-format\": true"
        "        }],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"preferred-lifetime\": 3000,"
        "    \"valid-lifetime\": 4000,"
        "    \"interface-id\": \"\","
        "    \"interface\": \"\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // There is docsis3 (vendor-id=4491) vendor option 33, which is a
    // config-file. Its format is a single string.
    string config_valid = config_prefix + "33" + config_postfix;

    // There is no option 99 defined in vendor-id=4491. As there is no
    // definition, the config should fail.
    string config_bogus = config_prefix + "99" + config_postfix;

    ConstElementPtr json_bogus;
    ASSERT_NO_THROW(json_bogus = parseDHCP6(config_bogus));
    ConstElementPtr json_valid;
    ASSERT_NO_THROW(json_valid = parseDHCP6(config_valid));

    NakedDhcpv6Srv srv(0);

    // This should fail (missing option definition)
    EXPECT_NO_THROW(x = configureDhcp6Server(srv, json_bogus));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(1, rcode_);

    // This should work (option definition present)
    EXPECT_NO_THROW(x = configureDhcp6Server(srv, json_valid));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);
}

// This test checks that the server will handle a Solicit with the Vendor Class
// having a length of 4 (enterprise-id only).
TEST_F(VendorOptsTest, cableLabsShortVendorClass) {
    NakedDhcpv6Srv srv(0);

    // Create a simple Solicit with the 4-byte long vendor class option.
    Pkt6Ptr sol = PktCaptures::captureCableLabsShortVendorClass();

    // Simulate that we have received that traffic
    srv.fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    srv.run();

    // Get Advertise...
    ASSERT_FALSE(srv.fake_sent_.empty());
    Pkt6Ptr adv = srv.fake_sent_.front();
    ASSERT_TRUE(adv);

    // This is sent back to client, so port is 546
    EXPECT_EQ(DHCP6_CLIENT_PORT, adv->getRemotePort());
}

// Checks that it's possible to have a vendor opts (17) option in the response
// only. Once specific client (Genexis) sends only vendor-class info and
// expects the server to include vendor opts in the response.
TEST_F(VendorOptsTest, vendorOpsInResponseOnly) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets6();
    Dhcp6Client client;

    // The config defines custom vendor (17) suboption 2 that conveys
    // a TFTP URL.  The client doesn't send vendor class (16) or
    // vendor opts (17) option, so normal vendor option processing is
    // impossible. However, since there's a class defined that matches
    // client's packets and that class inserts a vendor opts in the
    // response, Kea should be able to figure out the vendor-id and
    // then also insert the suboption 2 with the TFTP URL.
    string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ ]"
        "    },"
        "    \"option-def\": ["
        "        {"
        "            \"name\": \"tftp\","
        "            \"code\": 2,"
        "            \"space\": \"vendor-25167\","
        "            \"type\": \"string\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "    {"
        "        \"name\": \"cpe_genexis\","
        "        \"test\": \"substring(option[15].hex,0,7) == 'HMC1000'\","
        "        \"option-data\": ["
        "        {"
        "            \"name\": \"vendor-opts\","
        "            \"data\": \"25167\""
        "        },"
        "        {"
        "            \"name\": \"tftp\","
        "            \"space\": \"vendor-25167\","
        "            \"data\": \"tftp://192.0.2.1/genexis/HMC1000.v1.3.0-R.img\","
        "            \"always-send\": true"
        "        } ]"
        "    } ],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8::/64\" } ],"
        "    \"subnet\": \"2001:db8::/64\", "
        "    \"interface\": \"eth0\" "
        " } ]"
        "}";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // A a vendor-class identifier (this matches what Genexis hardware sends)
    OptionPtr vopt(new OptionString(Option::V6, D6O_USER_CLASS,
                                    "HMC1000.v1.3.0-R,Element-P1090,genexis.eu"));
    client.addExtraOption(vopt);
    client.requestOption(D6O_VENDOR_OPTS);

    // Let's check whether the server is not able to process this packet
    // and include vivso with appropriate sub-options
    EXPECT_NO_THROW(client.doSolicit());
    ASSERT_TRUE(client.getContext().response_);

    // Check there's a response.
    OptionPtr rsp = client.getContext().response_->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(rsp);

    // Check that it includes vendor opts with vendor-id = 25167
    OptionVendorPtr rsp_vopts = boost::dynamic_pointer_cast<OptionVendor>(rsp);
    ASSERT_TRUE(rsp_vopts);
    EXPECT_EQ(25167, rsp_vopts->getVendorId());

    // Now check that it contains suboption 2 with appropriate content.
    OptionPtr subopt2 = rsp_vopts->getOption(2);
    ASSERT_TRUE(subopt2);
    vector<uint8_t> subopt2bin = subopt2->toBinary(false);
    string txt(subopt2bin.begin(), subopt2bin.end());
    EXPECT_EQ("tftp://192.0.2.1/genexis/HMC1000.v1.3.0-R.img", txt);
}
