// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
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
// vivco (124) - vendor independent vendor class option.
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
public:
    /// @brief Called before each test
    void SetUp() override {
        iface_mgr_test_config_.reset(new IfaceMgrTestConfig(true));
        IfaceMgr::instance().openSockets4();
    }

    /// @brief Called after each test
    void TearDown() override {
        iface_mgr_test_config_.reset();
        IfaceMgr::instance().closeSockets();
    }

    /// @brief Checks if Option Request Option (ORO) in docsis (vendor-id=4491)
    /// vendor options is parsed correctly and the requested options are
    /// actually assigned. Also covers negative tests - that options are not
    /// provided when a different vendor ID is given.
    void testVendorOptionsORO(int vendor_id) {
        // Create a config with a custom option for Cable Labs.
        string config = R"(
            {
                "interfaces-config": {
                    "interfaces": [ "*" ]
                },
                "option-data": [
                    {
                        "code": 2,
                        "csv-format": true,
                        "data": "192.0.2.1, 192.0.2.2",
                        "name": "tftp-servers",
                        "space": "vendor-4491"
                    }
                ],
                "subnet4": [
                    {
                        "interface": "eth0",
                        "pools": [
                            {
                                "pool": "192.0.2.0/25"
                            }
                        ],
                        "subnet": "192.0.2.0/24"
                    }
                ]
            }
        )";

        // Parse the configuration.
        ConstElementPtr json;
        ASSERT_NO_THROW(json = parseDHCP4(config));

        // Configure a mocked server.
        NakedDhcpv4Srv srv(0);
        ConstElementPtr x;
        EXPECT_NO_THROW(x = configureDhcp4Server(srv, json));
        ASSERT_TRUE(x);
        comment_ = parseAnswer(rcode_, x);
        ASSERT_EQ(0, rcode_);
        CfgMgr::instance().commit();

        // Set the giaddr and hops to non-zero address as if it was relayed.
        boost::shared_ptr<Pkt4> dis(new Pkt4(DHCPDISCOVER, 1234));
        dis->setGiaddr(IOAddress("192.0.2.1"));
        dis->setHops(1);

        // Set interface. It is required by the server to generate server id.
        dis->setIface("eth0");
        dis->setIndex(ETH0_INDEX);
        OptionPtr clientid = generateClientId();
        dis->addOption(clientid);

        // Pass it to the server and get an advertise
        Pkt4Ptr offer = srv.processDiscover(dis);

        // Check if we get a response at all.
        ASSERT_TRUE(offer);

        // We did not include any vendor opts in DISCOVER, so there should be none
        // in OFFER.
        ASSERT_FALSE(offer->getOption(DHO_VIVSO_SUBOPTIONS));

        // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
        // That suboption has code 1 and is a docsis ORO option.
        boost::shared_ptr<OptionUint8Array> vendor_oro(new OptionUint8Array(Option::V4,
                                                                            DOCSIS3_V4_ORO));
        vendor_oro->addValue(DOCSIS3_V4_TFTP_SERVERS); // Request option 2.
        OptionPtr vendor(new OptionVendor(Option::V4, vendor_id));
        vendor->addOption(vendor_oro);
        dis->addOption(vendor);

        // Need to process DHCPDISCOVER again after requesting new option.
        offer = srv.processDiscover(dis);
        ASSERT_TRUE(offer);

        // Check if there is a vendor option in the response, if the Cable Labs
        // vendor ID was provided in the request. Otherwise, check that there is
        // no vendor and stop processing since the following checks are built on
        // top of the now-absent options.
        OptionPtr tmp = offer->getOption(DHO_VIVSO_SUBOPTIONS);
        if (vendor_id != VENDOR_ID_CABLE_LABS) {
            EXPECT_FALSE(tmp);
            return;
        }
        ASSERT_TRUE(tmp);

        // The response should be an OptionVendor.
        boost::shared_ptr<OptionVendor> vendor_resp =
            boost::dynamic_pointer_cast<OptionVendor>(tmp);
        ASSERT_TRUE(vendor_resp);

        // Option 2 should be present.
        OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
        ASSERT_TRUE(docsis2);

        // It should be an Option4AddrLst.
        Option4AddrLstPtr tftp_srvs = boost::dynamic_pointer_cast<Option4AddrLst>(docsis2);
        ASSERT_TRUE(tftp_srvs);

        // Check that the provided addresses match the ones in configuration.
        Option4AddrLst::AddressContainer addrs = tftp_srvs->getAddresses();
        ASSERT_EQ(2, addrs.size());
        EXPECT_EQ("192.0.2.1", addrs[0].toText());
        EXPECT_EQ("192.0.2.2", addrs[1].toText());
    }

    std::unique_ptr<IfaceMgrTestConfig> iface_mgr_test_config_;
};

/// @todo Add more extensive vendor options tests, including multiple
///       vendor options

// Checks if vendor options are parsed correctly and requested vendor options
// are echoed back.
TEST_F(VendorOptsTest, vendorOptionsDocsis) {
    NakedDhcpv4Srv srv(0);

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 2,"
        "          \"data\": \"10.253.175.16\","
        "          \"csv-format\": true"
        "        }],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"10.254.226.0/25\" } ],"
        "    \"subnet\": \"10.254.226.0/24\", "
        "    \"interface\": \"eth0\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with 3 suboptions. The server
    // is supposed to echo it back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = PktCaptures::captureRelayedDiscover());

    // Simulate that we have received that traffic
    srv.fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv.run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv.fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv.fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get Relay Agent Info from query...
    OptionPtr vendor_opt_response = offer->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(vendor_opt_response);

    // Check if it's of a correct type
    boost::shared_ptr<OptionVendor> vendor_opt =
        boost::dynamic_pointer_cast<OptionVendor>(vendor_opt_response);
    ASSERT_TRUE(vendor_opt);

    // Get Relay Agent Info from response...
    OptionPtr tftp_servers_generic = vendor_opt->getOption(DOCSIS3_V4_TFTP_SERVERS);
    ASSERT_TRUE(tftp_servers_generic);

    Option4AddrLstPtr tftp_servers =
        boost::dynamic_pointer_cast<Option4AddrLst>(tftp_servers_generic);

    ASSERT_TRUE(tftp_servers);

    Option4AddrLst::AddressContainer addrs = tftp_servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("10.253.175.16", addrs[0].toText());
}

// Checks if server is able to handle a relayed traffic from DOCSIS3.0 modems
TEST_F(VendorOptsTest, docsisVendorOptionsParse) {

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt4Ptr dis = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(dis->unpack());

    // Check if the packet contain
    OptionPtr opt = dis->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    // This particular capture that we have included options 1 and 5
    EXPECT_TRUE(vendor->getOption(1));
    EXPECT_TRUE(vendor->getOption(5));

    // It did not include options any other options
    EXPECT_FALSE(vendor->getOption(2));
    EXPECT_FALSE(vendor->getOption(3));
    EXPECT_FALSE(vendor->getOption(17));
}

// Checks if server is able to parse incoming docsis option and extract suboption 1 (docsis ORO)
TEST_F(VendorOptsTest, docsisVendorORO) {

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt4Ptr dis = PktCaptures::captureRelayedDiscover();
    EXPECT_NO_THROW(dis->unpack());

    // Check if the packet contains vendor specific information option
    OptionPtr opt = dis->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    opt = vendor->getOption(DOCSIS3_V4_ORO);
    ASSERT_TRUE(opt);

    OptionUint8ArrayPtr oro = boost::dynamic_pointer_cast<OptionUint8Array>(opt);
    EXPECT_TRUE(oro);
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsORO) {
    testVendorOptionsORO(VENDOR_ID_CABLE_LABS);
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsORODifferentVendorID) {
    testVendorOptionsORO(32768);
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and persistent options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptions) {
    NakedDhcpv4Srv srv(0);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 2,"
        "          \"data\": \"192.0.2.1, 192.0.2.2\","
        "          \"csv-format\": true,"
        "          \"always-send\": true"
        "        }],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"eth0\" "
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    boost::shared_ptr<Pkt4> dis(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr and hops to non-zero address as if it was relayed.
    dis->setGiaddr(IOAddress("192.0.2.1"));
    dis->setHops(1);

    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    // Set interface. It is required by the server to generate server id.
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);

    // Let's add a vendor-option (vendor-id=4491).
    OptionPtr vendor(new OptionVendor(Option::V4, 4491));
    dis->addOption(vendor);

    // Pass it to the server and get an advertise
    Pkt4Ptr offer = srv.processDiscover(dis);

    // check if we get response at all
    ASSERT_TRUE(offer);

    // Check if there is a vendor option response
    OptionPtr tmp = offer->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(tmp);

    // The response should be OptionVendor object
    boost::shared_ptr<OptionVendor> vendor_resp =
        boost::dynamic_pointer_cast<OptionVendor>(tmp);
    ASSERT_TRUE(vendor_resp);

    OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
    ASSERT_TRUE(docsis2);

    Option4AddrLstPtr tftp_srvs = boost::dynamic_pointer_cast<Option4AddrLst>(docsis2);
    ASSERT_TRUE(tftp_srvs);

    Option4AddrLst::AddressContainer addrs = tftp_srvs->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("192.0.2.1", addrs[0].toText());
    EXPECT_EQ("192.0.2.2", addrs[1].toText());
}

// Test checks whether it is possible to use option definitions defined in
// src/lib/dhcp/docsis3_option_defs.h.
TEST_F(VendorOptsTest, vendorOptionsDocsisDefinitions) {
    ConstElementPtr x;
    string config_prefix = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},"
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": ";
    string config_postfix = ","
        "          \"data\": \"192.0.2.1\","
        "          \"csv-format\": true"
        "        }],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.50\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"\""
        " } ]"
        "}";

    // There is docsis3 (vendor-id=4491) vendor option 2, which is a
    // tftp-server. Its format is list of IPv4 addresses.
    string config_valid = config_prefix + "2" + config_postfix;

    // There is no option 99 defined in vendor-id=4491. As there is no
    // definition, the config should fail.
    string config_bogus = config_prefix + "99" + config_postfix;

    ConstElementPtr json_bogus;
    ASSERT_NO_THROW(json_bogus = parseDHCP4(config_bogus));
    ConstElementPtr json_valid;
    ASSERT_NO_THROW(json_valid = parseDHCP4(config_valid));

    NakedDhcpv4Srv srv(0);

    // This should fail (missing option definition)
    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json_bogus));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(1, rcode_);

    // This should work (option definition present)
    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json_valid));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);
}

/// Checks if DOCSIS client packets are classified properly
///
/// The test has been updated to work with the updated generic
/// vendor options handling code.
TEST_F(VendorOptsTest, docsisClientClassification) {

    NakedDhcpv4Srv srv(0);

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // vendor-class set to docsis3.0
    Pkt4Ptr dis1;
    ASSERT_NO_THROW(dis1 = PktCaptures::captureRelayedDiscover());
    ASSERT_NO_THROW(dis1->unpack());

    srv.classifyPacket(dis1);

    EXPECT_TRUE(dis1->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0:"));
    EXPECT_FALSE(dis1->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // vendor-class set to eRouter1.0
    Pkt4Ptr dis2;
    ASSERT_NO_THROW(dis2 = PktCaptures::captureRelayedDiscover2());
    ASSERT_NO_THROW(dis2->unpack());

    srv.classifyPacket(dis2);

    EXPECT_TRUE(dis2->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));
    EXPECT_FALSE(dis2->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0:"));
}

// Checks that it's possible to have a vivso (125) option in the response
// only. Once specific client (Genexis) sends only vendor-class info and
// expects the server to include vivso in the response.
TEST_F(VendorOptsTest, vivsoInResponseOnly) {
    Dhcp4Client client;

    // The config defines custom vendor 125 suboption 2 that conveys a TFTP URL.
    // The client doesn't send vendor 125 option, so normal vendor option
    // processing is impossible. However, since there's a class defined that
    // matches client's packets and that class inserts vivso in the response,
    // Kea should be able to figure out the vendor-id and then also insert
    // suboption 2 with the TFTP URL.
    string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
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
        "        \"test\": \"substring(option[60].hex,0,7) == 'HMC1000'\","
        "        \"option-data\": ["
        "        {"
        "            \"name\": \"vivso-suboptions\","
        "            \"data\": \"25167\""
        "        },"
        "        {"
        "            \"name\": \"tftp\","
        "            \"space\": \"vendor-25167\","
        "            \"data\": \"tftp://192.0.2.1/genexis/HMC1000.v1.3.0-R.img\","
        "            \"always-send\": true"
        "        } ]"
        "    } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"eth0\" "
        " } ]"
        "}";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Add a vendor-class identifier (this matches what Genexis hardware sends)
    OptionPtr vopt(new OptionString(Option::V4, DHO_VENDOR_CLASS_IDENTIFIER,
                                    "HMC1000.v1.3.0-R,Element-P1090,genexis.eu"));
    client.addExtraOption(vopt);
    client.requestOptions(DHO_VIVSO_SUBOPTIONS);

    // Let's check whether the server is not able to process this packet
    // and include vivso with appropriate sub-options
    EXPECT_NO_THROW(client.doDiscover());
    ASSERT_TRUE(client.getContext().response_);

    // Check there's a response.
    OptionPtr rsp = client.getContext().response_->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(rsp);

    // Check that it includes vivso with vendor-id = 25167
    OptionVendorPtr rsp_vivso = boost::dynamic_pointer_cast<OptionVendor>(rsp);
    ASSERT_TRUE(rsp_vivso);
    EXPECT_EQ(25167, rsp_vivso->getVendorId());

    // Now check that it contains suboption 2 with appropriate content.
    OptionPtr subopt2 = rsp_vivso->getOption(2);
    ASSERT_TRUE(subopt2);
    vector<uint8_t> subopt2bin = subopt2->toBinary(false);
    string txt(subopt2bin.begin(), subopt2bin.end());
    EXPECT_EQ("tftp://192.0.2.1/genexis/HMC1000.v1.3.0-R.img", txt);
}

// Verifies last resort option 43 is backward compatible
TEST_F(VendorOptsTest, option43LastResort) {
    NakedDhcpv4Srv srv(0);

    // If there is no definition for option 43 a last resort
    // one is applied. This definition was used by Kea <= 1.2
    // so should be backward compatible.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"vendor-encapsulated-options-space\", "
        "    \"type\": \"uint32\" } ],"
        "\"option-data\": [ "
        "{   \"name\": \"foo\", "
        "    \"space\": \"vendor-encapsulated-options-space\", "
        "    \"data\": \"12345678\" }, "
        "{   \"name\": \"vendor-class-identifier\", "
        "    \"data\": \"bar\" }, "
        "{   \"name\": \"vendor-encapsulated-options\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Pass it to the server and get a DHCPOFFER.
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-class-identifier (code 60)
    OptionPtr opt = offer->getOption(DHO_VENDOR_CLASS_IDENTIFIER);
    EXPECT_TRUE(opt);

    // And a vendor-encapsulated-options (code 43)
    opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    const OptionCollection& opts = opt->getOptions();
    ASSERT_EQ(1, opts.size());
    OptionPtr sopt = opts.begin()->second;
    ASSERT_TRUE(sopt);
    EXPECT_EQ(1, sopt->getType());
}

// Checks effect of raw not compatible option 43 (no failure)
TEST_F(VendorOptsTest, option43BadRaw) {
    NakedDhcpv4Srv srv(0);

    // The vendor-encapsulated-options has an incompatible data
    // so won't have the expected content but processing of truncated
    // (suboption length > available length) suboptions does not raise
    // an exception.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"option-data\": [ "
        "{   \"name\": \"vendor-class-identifier\", "
        "    \"data\": \"bar\" }, "
        "{   \"name\": \"vendor-encapsulated-options\", "
        "    \"csv-format\": false, "
        "    \"data\": \"0102\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a vendor-encapsulated-options (code 43)
    // with not compatible (not parsable as suboptions) content
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x02);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    query->addOption(vopt);
    query->getDeferredOptions().push_back(DHO_VENDOR_ENCAPSULATED_OPTIONS);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    srv.deferredUnpack(query);

    // Check if the option was (uncorrectly) re-unpacked
    vopt = query->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    OptionCustomPtr custom = boost::dynamic_pointer_cast<OptionCustom>(vopt);
    EXPECT_TRUE(custom);

    // Pass it to the server and get a DHCPOFFER.
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-class-identifier (code 60)
    OptionPtr opt = offer->getOption(DHO_VENDOR_CLASS_IDENTIFIER);
    EXPECT_TRUE(opt);

    // And a vendor-encapsulated-options (code 43)
    opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    // But truncated.
    EXPECT_EQ(0, opt->len() - opt->getHeaderLen());
}

// Checks effect of raw not compatible option 43 (failure)
TEST_F(VendorOptsTest, option43FailRaw) {
    NakedDhcpv4Srv srv(0);

    // The vendor-encapsulated-options has an incompatible data
    // so won't have the expected content. Here the processing
    // of suboptions tries to unpack the uitn32 foo suboption and
    // raises an exception which is caught so the option stays unpacked.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"vendor-encapsulated-options-space\", "
        "    \"type\": \"uint32\" } ],"
        "\"option-data\": [ "
        "{   \"name\": \"vendor-class-identifier\", "
        "    \"data\": \"bar\" }, "
        "{   \"name\": \"vendor-encapsulated-options\", "
        "    \"csv-format\": false, "
        "    \"data\": \"0102\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a vendor-encapsulated-options (code 43)
    // with not compatible (not parsable as suboptions) content
    // which will raise an exception
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x01);
    buf.push_back(0x01);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    query->addOption(vopt);
    query->getDeferredOptions().push_back(DHO_VENDOR_ENCAPSULATED_OPTIONS);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    EXPECT_NO_THROW(srv.deferredUnpack(query));
    ASSERT_TRUE(query->getOption(vopt->getType()));
    EXPECT_EQ(vopt, query->getOption(vopt->getType()));
}

// Verifies raw option 43 can be handled (global)
TEST_F(VendorOptsTest, option43RawGlobal) {
    NakedDhcpv4Srv srv(0);

    // The vendor-encapsulated-options is redefined as raw binary
    // in a global definition.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"option-def\": [ "
        "{   \"code\": 43, "
        "    \"name\": \"vendor-encapsulated-options\", "
        "    \"type\": \"binary\" } ],"
        "\"option-data\": [ "
        "{   \"name\": \"vendor-class-identifier\", "
        "    \"data\": \"bar\" }, "
        "{   \"name\": \"vendor-encapsulated-options\", "
        "    \"csv-format\": false, "
        "    \"data\": \"0102\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a vendor-encapsulated-options (code 43)
    // with not compatible (not parsable as suboptions) content
    OptionBuffer buf;
    buf.push_back(0x02);
    buf.push_back(0x03);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    query->addOption(vopt);
    query->getDeferredOptions().push_back(DHO_VENDOR_ENCAPSULATED_OPTIONS);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Check if the option was (correctly) re-unpacked
    vopt = query->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    OptionCustomPtr custom = boost::dynamic_pointer_cast<OptionCustom>(vopt);
    EXPECT_FALSE(custom);

    // Pass it to the server and get a DHCPOFFER.
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-class-identifier (code 60)
    OptionPtr opt = offer->getOption(DHO_VENDOR_CLASS_IDENTIFIER);
    EXPECT_TRUE(opt);

    // And a vendor-encapsulated-options (code 43)
    opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    // Verifies the content
    ASSERT_EQ(2, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(0x01, opt->getData()[0]);
    EXPECT_EQ(0x02, opt->getData()[1]);
}

// Verifies raw option 43 can be handled (catch-all class)
TEST_F(VendorOptsTest, option43RawClass) {
    NakedDhcpv4Srv srv(0);

    // The vendor-encapsulated-options is redefined as raw binary
    // in a class definition.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"vendor\", "
        "    \"test\": \"option[vendor-encapsulated-options].exists\", "
        "    \"option-def\": [ "
        "    {   \"code\": 43, "
        "        \"name\": \"vendor-encapsulated-options\", "
        "        \"type\": \"binary\" } ],"
        "    \"option-data\": [ "
        "    {   \"name\": \"vendor-class-identifier\", "
        "        \"data\": \"bar\" }, "
        "    {   \"name\": \"vendor-encapsulated-options\", "
        "        \"csv-format\": false, "
        "        \"data\": \"0102\" } ] } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a vendor-encapsulated-options (code 43)
    // with not compatible (not parsable as suboptions) content
    OptionBuffer buf;
    buf.push_back(0x02);
    buf.push_back(0x03);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    query->addOption(vopt);
    query->getDeferredOptions().push_back(DHO_VENDOR_ENCAPSULATED_OPTIONS);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Check if the option was (correctly) re-unpacked
    vopt = query->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    OptionCustomPtr custom = boost::dynamic_pointer_cast<OptionCustom>(vopt);
    EXPECT_FALSE(custom);

    // Pass it to the server and get a DHCPOFFER.
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-class-identifier (code 60)
    OptionPtr opt = offer->getOption(DHO_VENDOR_CLASS_IDENTIFIER);
    EXPECT_TRUE(opt);

    // And a vendor-encapsulated-options (code 43)
    opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    // Verifies the content
    ASSERT_EQ(2, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(0x01, opt->getData()[0]);
    EXPECT_EQ(0x02, opt->getData()[1]);
}

// Verifies option 43 deferred processing (one class)
TEST_F(VendorOptsTest, option43Class) {
    NakedDhcpv4Srv srv(0);

    // A client class defines vendor-encapsulated-options (code 43)
    // and data for it and its sub-option.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"alpha\", "
        "    \"type\": \"uint32\" } ],"
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"alpha\", "
        "    \"test\": \"option[vendor-class-identifier].text == 'alpha'\", "
        "    \"option-def\": [ "
        "    {   \"code\": 43, "
        "        \"name\": \"vendor-encapsulated-options\", "
        "        \"type\": \"empty\", "
        "        \"encapsulate\": \"alpha\" } ],"
        "    \"option-data\": [ "
        "    {   \"name\": \"vendor-class-identifier\", "
        "        \"data\": \"alpha\" }, "
        "    {   \"name\": \"vendor-encapsulated-options\" }, "
        "    {   \"name\": \"foo\", "
        "        \"space\": \"alpha\", "
        "        \"data\": \"12345678\" } ] } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a vendor-encapsulated-options (code 43)
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x04);
    buf.push_back(0x87);
    buf.push_back(0x65);
    buf.push_back(0x43);
    buf.push_back(0x21);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    query->addOption(vopt);
    query->getDeferredOptions().push_back(DHO_VENDOR_ENCAPSULATED_OPTIONS);

    // Create and add a vendor-class-identifier (code 60)
    OptionStringPtr iopt(new OptionString(Option::V4,
                                          DHO_VENDOR_CLASS_IDENTIFIER,
                                          "alpha"));
    query->addOption(iopt);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Check if the option was (correctly) re-unpacked
    vopt = query->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    OptionCustomPtr custom = boost::dynamic_pointer_cast<OptionCustom>(vopt);
    EXPECT_TRUE(custom);
    EXPECT_EQ(1, vopt->getOptions().size());

    // Pass it to the server and get a DHCPOFFER.
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-class-identifier (code 60)
    OptionPtr opt = offer->getOption(DHO_VENDOR_CLASS_IDENTIFIER);
    EXPECT_TRUE(opt);

    // And a vendor-encapsulated-options (code 43)
    opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    // Verifies the content
    const OptionCollection& opts = opt->getOptions();
    ASSERT_EQ(1, opts.size());
    OptionPtr sopt = opts.begin()->second;
    ASSERT_TRUE(sopt);
    EXPECT_EQ(1, sopt->getType());
    OptionUint32Ptr sopt32 = boost::dynamic_pointer_cast<OptionUint32>(sopt);
    ASSERT_TRUE(sopt32);
    EXPECT_EQ(12345678, sopt32->getValue());
}

// Verifies option 43 priority
TEST_F(VendorOptsTest, option43ClassPriority) {
    NakedDhcpv4Srv srv(0);

    // Both global and client-class scopes get vendor-encapsulated-options
    // (code 43) definition and data. The client-class has precedence.
    // Note it does not work without the vendor-encapsulated-options
    // option-data in the client-class.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"alpha\", "
        "    \"type\": \"uint32\" },"
        "{   \"code\": 1, "
        "    \"name\": \"bar\", "
        "    \"space\":  \"beta\", "
        "    \"type\": \"uint8\" }, "
        "{   \"code\": 43, "
        "    \"name\": \"vendor-encapsulated-options\", "
        "    \"type\": \"empty\", "
        "    \"encapsulate\": \"beta\" } ],"
        "\"option-data\": [ "
        "{   \"name\": \"vendor-encapsulated-options\" }, "
        "{   \"name\": \"vendor-class-identifier\", "
        "    \"data\": \"beta\" }, "
        "{   \"name\": \"bar\", "
        "    \"space\": \"beta\", "
        "    \"data\": \"33\" } ],"
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"alpha\", "
        "    \"test\": \"option[vendor-class-identifier].text == 'alpha'\", "
        "    \"option-def\": [ "
        "    {   \"code\": 43, "
        "        \"name\": \"vendor-encapsulated-options\", "
        "        \"type\": \"empty\", "
        "        \"encapsulate\": \"alpha\" } ],"
        "    \"option-data\": [ "
        "{   \"name\": \"vendor-encapsulated-options\" }, "
        "    {   \"name\": \"vendor-class-identifier\", "
        "        \"data\": \"alpha\" }, "
        "    {   \"name\": \"foo\", "
        "        \"space\": \"alpha\", "
        "        \"data\": \"12345678\" } ] } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a vendor-encapsulated-options (code 43)
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x04);
    buf.push_back(0x87);
    buf.push_back(0x65);
    buf.push_back(0x43);
    buf.push_back(0x21);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    query->addOption(vopt);
    query->getDeferredOptions().push_back(DHO_VENDOR_ENCAPSULATED_OPTIONS);

    // Create and add a vendor-class-identifier (code 60)
    OptionStringPtr iopt(new OptionString(Option::V4,
                                          DHO_VENDOR_CLASS_IDENTIFIER,
                                          "alpha"));
    query->addOption(iopt);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Check if the option was (correctly) re-unpacked
    vopt = query->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    OptionCustomPtr custom = boost::dynamic_pointer_cast<OptionCustom>(vopt);
    EXPECT_TRUE(custom);
    EXPECT_EQ(1, vopt->getOptions().size());

    // Pass it to the server and get a DHCPOFFER.
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-class-identifier (code 60)
    OptionPtr opt = offer->getOption(DHO_VENDOR_CLASS_IDENTIFIER);
    EXPECT_TRUE(opt);
    OptionStringPtr id = boost::dynamic_pointer_cast<OptionString>(opt);
    ASSERT_TRUE(id);
    EXPECT_EQ("alpha", id->getValue());

    // And a vendor-encapsulated-options (code 43)
    opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    // Verifies the content
    const OptionCollection& opts = opt->getOptions();
    ASSERT_EQ(1, opts.size());
    OptionPtr sopt = opts.begin()->second;
    ASSERT_TRUE(sopt);
    EXPECT_EQ(1, sopt->getType());
    EXPECT_EQ(2 + 4, sopt->len());
    OptionUint32Ptr sopt32 = boost::dynamic_pointer_cast<OptionUint32>(sopt);
    ASSERT_TRUE(sopt32);
    EXPECT_EQ(12345678, sopt32->getValue());
}

// Verifies option 43 deferred processing (two classes)
TEST_F(VendorOptsTest, option43Classes) {
    NakedDhcpv4Srv srv(0);

    // Two client-class scopes get vendor-encapsulated-options
    // (code 43) definition and data. The first matching client-class
    // (from a set?) applies.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"alpha\", "
        "    \"type\": \"uint32\" },"
        "{   \"code\": 1, "
        "    \"name\": \"bar\", "
        "    \"space\":  \"beta\", "
        "    \"type\": \"uint8\" } ],"
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"alpha\", "
        "    \"test\": \"option[vendor-class-identifier].text == 'alpha'\", "
        "    \"option-def\": [ "
        "    {   \"code\": 43, "
        "        \"name\": \"vendor-encapsulated-options\", "
        "        \"type\": \"empty\", "
        "        \"encapsulate\": \"alpha\" } ],"
        "    \"option-data\": [ "
        "{   \"name\": \"vendor-encapsulated-options\" }, "
        "    {   \"name\": \"vendor-class-identifier\", "
        "        \"data\": \"alpha\" }, "
        "    {   \"name\": \"foo\", "
        "        \"space\": \"alpha\", "
        "        \"data\": \"12345678\" } ] },"
        "{   \"name\": \"beta\", "
        "    \"test\": \"option[vendor-class-identifier].text == 'beta'\", "
        "    \"option-def\": [ "
        "    {   \"code\": 43, "
        "        \"name\": \"vendor-encapsulated-options\", "
        "        \"type\": \"empty\", "
        "        \"encapsulate\": \"beta\" } ],"
        "    \"option-data\": [ "
        "{   \"name\": \"vendor-encapsulated-options\" }, "
        "    {   \"name\": \"vendor-class-identifier\", "
        "        \"data\": \"beta\" }, "
        "    {   \"name\": \"bar\", "
        "        \"space\": \"beta\", "
        "        \"data\": \"33\" } ] } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
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
    query->setIndex(ETH1_INDEX);

    // Create and add a vendor-encapsulated-options (code 43)
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x04);
    buf.push_back(0x87);
    buf.push_back(0x65);
    buf.push_back(0x43);
    buf.push_back(0x21);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    query->addOption(vopt);
    query->getDeferredOptions().push_back(DHO_VENDOR_ENCAPSULATED_OPTIONS);

    // Create and add a vendor-class-identifier (code 60)
    OptionStringPtr iopt(new OptionString(Option::V4,
                                          DHO_VENDOR_CLASS_IDENTIFIER,
                                          "alpha"));
    query->addOption(iopt);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Check if the option was (correctly) re-unpacked
    vopt = query->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    OptionCustomPtr custom = boost::dynamic_pointer_cast<OptionCustom>(vopt);
    EXPECT_TRUE(custom);
    EXPECT_EQ(1, vopt->getOptions().size());

    // Pass it to the server and get a DHCPOFFER.
    Pkt4Ptr offer = srv.processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add a vendor-class-identifier (code 60)
    OptionPtr opt = offer->getOption(DHO_VENDOR_CLASS_IDENTIFIER);
    EXPECT_TRUE(opt);
    OptionStringPtr id = boost::dynamic_pointer_cast<OptionString>(opt);
    ASSERT_TRUE(id);
    EXPECT_EQ("alpha", id->getValue());

    // And a vendor-encapsulated-options (code 43)
    opt = offer->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    // Verifies the content
    const OptionCollection& opts = opt->getOptions();
    ASSERT_EQ(1, opts.size());
    OptionPtr sopt = opts.begin()->second;
    ASSERT_TRUE(sopt);
    EXPECT_EQ(1, sopt->getType());
    EXPECT_EQ(2 + 4, sopt->len());
    OptionUint32Ptr sopt32 = boost::dynamic_pointer_cast<OptionUint32>(sopt);
    ASSERT_TRUE(sopt32);
    EXPECT_EQ(12345678, sopt32->getValue());
}

// Checks effect of raw not compatible option 43 sent by a client (failure)
TEST_F(VendorOptsTest, clientOption43FailRaw) {
    Dhcp4Client client;

    // The vendor-encapsulated-options has an incompatible data
    // so won't have the expected content. Here the processing
    // of suboptions tries to unpack the uint32 foo suboption and
    // raises an exception which is caught.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"10.0.0.10 - 10.0.0.100\" } ], "
        "    \"subnet\": \"10.0.0.0/24\" } ],"
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"vendor-encapsulated-options-space\", "
        "    \"type\": \"uint32\" } ] }";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Create and add a vendor-encapsulated-options (code 43)
    // with not compatible (not parsable as suboptions) content
    // which will raise an exception
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x01);
    buf.push_back(0x01);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    client.addExtraOption(vopt);

    // Let's check whether the server is not able to process this packet
    // and raises an exception which is caught so the response is not empty.
    EXPECT_NO_THROW(client.doDiscover());
    EXPECT_TRUE(client.getContext().response_);
}

// Verifies raw option 43 sent by a client can be handled (global)
TEST_F(VendorOptsTest, clientOption43RawGlobal) {
    Dhcp4Client client;

    // The vendor-encapsulated-options is redefined as raw binary
    // in a global definition.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"10.0.0.10 - 10.0.0.100\" } ], "
        "    \"subnet\": \"10.0.0.0/24\" } ],"
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"vendor-encapsulated-options-space\", "
        "    \"type\": \"uint32\" },"
        "{   \"code\": 43, "
        "    \"name\": \"vendor-encapsulated-options\", "
        "    \"type\": \"binary\" } ],"
        "\"option-data\": [ "
        "{   \"name\": \"vendor-class-identifier\", "
        "    \"data\": \"bar\" }, "
        "{   \"name\": \"vendor-encapsulated-options\", "
        "    \"csv-format\": false, "
        "    \"data\": \"0102\" } ] }";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Create and add a vendor-encapsulated-options (code 43)
    // with not compatible (not parsable as suboptions) content
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x01);
    buf.push_back(0x01);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    client.addExtraOption(vopt);

    // Let's check whether the server is able to process this packet without
    // throwing any exceptions so the response is not empty.
    EXPECT_NO_THROW(client.doDiscover());
    EXPECT_TRUE(client.getContext().response_);
}

// Verifies raw option 43 sent by a client can be handled (catch-all class)
TEST_F(VendorOptsTest, clientOption43RawClass) {
    Dhcp4Client client;

    // The vendor-encapsulated-options is redefined as raw binary
    // in a class definition.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"10.0.0.10 - 10.0.0.100\" } ], "
        "    \"subnet\": \"10.0.0.0/24\" } ],"
        "\"option-def\": [ "
        "{   \"code\": 1, "
        "    \"name\": \"foo\", "
        "    \"space\":  \"vendor-encapsulated-options-space\", "
        "    \"type\": \"uint32\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"vendor\", "
        "    \"test\": \"option[vendor-encapsulated-options].exists\", "
        "    \"option-def\": [ "
        "    {   \"code\": 43, "
        "        \"name\": \"vendor-encapsulated-options\", "
        "        \"type\": \"binary\" } ],"
        "    \"option-data\": [ "
        "    {   \"name\": \"vendor-class-identifier\", "
        "        \"data\": \"bar\" }, "
        "    {   \"name\": \"vendor-encapsulated-options\", "
        "        \"csv-format\": false, "
        "        \"data\": \"0102\" } ] } ] }";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Create and add a vendor-encapsulated-options (code 43)
    // with not compatible (not parsable as suboptions) content
    OptionBuffer buf;
    buf.push_back(0x01);
    buf.push_back(0x01);
    buf.push_back(0x01);
    OptionPtr vopt(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS, buf));
    client.addExtraOption(vopt);

    // Let's check whether the server is able to process this packet without
    // throwing any exceptions so the response is not empty.
    EXPECT_NO_THROW(client.doDiscover());
    EXPECT_TRUE(client.getContext().response_);
}

// Verifies that a client query with a truncated length in
// vendor option (125) will still be processed by the server.
TEST_F(Dhcpv4SrvTest, truncatedVIVSOOption) {
    NakedDhcpv4Srv srv(0);

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"10.206.80.0/25\" } ],"
        "    \"subnet\": \"10.206.80.0/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000"
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_) << isc::data::prettyPrint(status);

    CfgMgr::instance().commit();

    // Create a DISCOVER with a VIVSO option whose length is
    // too short.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = PktCaptures::discoverWithTruncatedVIVSO());

    // Simulate that we have received that traffic
    srv.fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv.run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv.fake_sent_.size());

    // Make sure that we received an response and it was a DHCPOFFER.
    Pkt4Ptr offer = srv.fake_sent_.front();
    ASSERT_TRUE(offer);
}

/// Checks that it's possible to define and use a suboption 0.
TEST_F(VendorOptsTest, vendorOpsSubOption0) {
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
    query->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    prl->addValue(DHO_VENDOR_CLASS_IDENTIFIER);
    query->addOption(prl);

    srv.classifyPacket(query);
    ASSERT_NO_THROW(srv.deferredUnpack(query));

    // Pass it to the server and get a DHCPOFFER.
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
