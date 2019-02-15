// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/option_int_array.h>
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

/// @todo move vendor options tests to a separate file.
/// @todo Add more extensive vendor options tests, including multiple
///       vendor options

// Checks if vendor options are parsed correctly and requested vendor options
// are echoed back.
TEST_F(Dhcpv4SrvTest, vendorOptionsDocsis) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
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
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
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
TEST_F(Dhcpv4SrvTest, docsisVendorOptionsParse) {

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
TEST_F(Dhcpv4SrvTest, docsisVendorORO) {

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
TEST_F(Dhcpv4SrvTest, vendorOptionsORO) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 2,"
        "          \"data\": \"192.0.2.1, 192.0.2.2\","
        "          \"csv-format\": true"
        "        }],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"eth0\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
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

    // Pass it to the server and get an advertise
    Pkt4Ptr offer = srv.processDiscover(dis);

    // check if we get response at all
    ASSERT_TRUE(offer);

    // We did not include any vendor opts in DISCOVER, so there should be none
    // in OFFER.
    ASSERT_FALSE(offer->getOption(DHO_VIVSO_SUBOPTIONS));

    // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
    // That suboption has code 1 and is a docsis ORO option.
    boost::shared_ptr<OptionUint8Array> vendor_oro(new OptionUint8Array(Option::V4,
                                                                        DOCSIS3_V4_ORO));
    vendor_oro->addValue(DOCSIS3_V4_TFTP_SERVERS); // Request option 33
    OptionPtr vendor(new OptionVendor(Option::V4, 4491));
    vendor->addOption(vendor_oro);
    dis->addOption(vendor);

    // Need to process SOLICIT again after requesting new option.
    offer = srv.processDiscover(dis);
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

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and persistent options are actually assigned.
TEST_F(Dhcpv4SrvTest, vendorPersistentOptions) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
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
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"eth0\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
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
TEST_F(Dhcpv4SrvTest, vendorOptionsDocsisDefinitions) {
    ConstElementPtr x;
    string config_prefix = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
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
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

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
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(1, rcode_);

    // This should work (option definition present)
    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json_valid));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);
}

/// Checks if DOCSIS client packets are classified properly
///
/// @todo: With the change in #4626 the vendorClassSpecificProcessing
/// code was removed and replaced with generic classification. One day
/// we should rewrite this test to use classes. It would check that the
/// classification system can be used for docsis packets.
TEST_F(Dhcpv4SrvTest, DISABLED_docsisClientClassification) {

    NakedDhcpv4Srv srv(0);

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // vendor-class set to docsis3.0
    Pkt4Ptr dis1;
    ASSERT_NO_THROW(dis1 = PktCaptures::captureRelayedDiscover());
    ASSERT_NO_THROW(dis1->unpack());

    srv.classifyPacket(dis1);

    EXPECT_TRUE(dis1->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0"));
    EXPECT_FALSE(dis1->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // vendor-class set to eRouter1.0
    Pkt4Ptr dis2;
    ASSERT_NO_THROW(dis2 = PktCaptures::captureRelayedDiscover2());
    ASSERT_NO_THROW(dis2->unpack());

    srv.classifyPacket(dis2);

    EXPECT_TRUE(dis2->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));
    EXPECT_FALSE(dis2->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0"));
}
