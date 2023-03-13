// Copyright (C) 2019-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file is dedicated to testing vendor options. There are several
// vendor options in DHCPv4:
//
// vivso (125) - vendor independent vendor specific option. This is by far the
//               most popular.
// vendor specific (43) - this is probably the second most popular.
//                        Unfortunately, its definition is blurry, so there are
//                        many similar, but not exact implementations that do
//                        things in different ways.
// vivco (124) - vendor independent vendor class option.
// class identifier (60) - not exactly vendor specific. It's a string, but the
//                         content of that string identifies what kind of vendor
//                         device this is.
// client-class (77) - this specifies (as a plain string) what kind of device
//                     this is.

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
#include <dhcp/option_vendor_class.h>
#include <dhcp/tests/pkt_captures.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/dhcp4.h>
#include <dhcpsrv/cfg_multi_threading.h>
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
    /// actually assigned. Also covers negative tests that options are not
    /// provided when a different vendor ID is given.
    ///
    /// @note  Kea only knows how to process VENDOR_ID_CABLE_LABS DOCSIS3_V4_ORO
    /// (suboption 1).
    ///
    /// @param configured_vendor_ids The vendor IDs that are configured in the
    /// server: 4491 or both 4491 and 3561.
    /// @param requested_vendor_ids Then vendor IDs that are present in ORO.
    /// @param requested_options The requested options in ORO.
    void testVendorOptionsORO(std::set<uint32_t> configured_vendor_ids,
                              std::set<uint32_t> requested_vendor_ids,
                              std::set<uint16_t> requested_options) {
        std::set<uint32_t> result_vendor_ids;
        ASSERT_FALSE(configured_vendor_ids.empty());
        ASSERT_TRUE(configured_vendor_ids.find(VENDOR_ID_CABLE_LABS) != configured_vendor_ids.end());
        for (uint32_t req : requested_vendor_ids) {
            if (req == VENDOR_ID_CABLE_LABS) {
                result_vendor_ids.insert(req);
            }
        }
        // Create a config with custom options.
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
                    },
                    {
                        "code": 22,
                        "csv-format": true,
                        "data": "first",
                        "name": "tag",
                        "space": "vendor-4491"
        )";
        if (configured_vendor_ids.size() > 1) {
            config += R"(
                    },
                    {
                        "code": 2,
                        "csv-format": true,
                        "data": "10.0.2.1, 10.0.2.2",
                        "name": "custom",
                        "space": "vendor-3561",
                    },
                    {
                        "code": 22,
                        "csv-format": true,
                        "data": "last",
                        "name": "special",
                        "space": "vendor-3561"
            )";
        }
        config += R"(
                    }
                ],
                "option-def": [
                    {
                        "code": 22,
                        "name": "tag",
                        "space": "vendor-4491",
                        "type": "string"
        )";
        if (configured_vendor_ids.size() > 1) {
            config += R"(
                    },
                    {
                        "code": 2,
                        "name": "custom",
                        "space": "vendor-3561",
                        "type": "ipv4-address",
                        "array": true
                    },
                    {
                        "code": 22,
                        "name": "special",
                        "space": "vendor-3561",
                        "type": "string"
            )";
        }
        config += R"(
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
        EXPECT_NO_THROW(x = Dhcpv4SrvTest::configure(srv, json));
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

        // Pass it to the server and get an offer
        Pkt4Ptr offer = srv.processDiscover(dis);

        // Check if we get a response at all.
        ASSERT_TRUE(offer);

        // We did not include any vendor opts in DISCOVER, so there should be none
        // in OFFER.
        ASSERT_FALSE(offer->getOption(DHO_VIVSO_SUBOPTIONS));

        // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
        // That suboption has code 1 and is a docsis ORO option.
        OptionUint8ArrayPtr vendor_oro(new OptionUint8Array(Option::V4, DOCSIS3_V4_ORO));
        for (uint16_t option : requested_options) {
            vendor_oro->addValue(option);
        }

        for (uint32_t vendor_id : requested_vendor_ids) {
            OptionVendorPtr vendor(new OptionVendor(Option::V4, vendor_id));
            vendor->addOption(vendor_oro);
            dis->Pkt::addOption(vendor);
        }

        // Need to process DHCPDISCOVER again after requesting new option.
        offer = srv.processDiscover(dis);
        ASSERT_TRUE(offer);

        // Check if there is a vendor option in the response, if the Cable Labs
        // vendor ID was provided in the request. Otherwise, check that there is
        // no vendor and stop processing since the following checks are built on
        // top of the now-absent options.
        OptionCollection tmp = offer->getOptions(DHO_VIVSO_SUBOPTIONS);
        ASSERT_EQ(tmp.size(), result_vendor_ids.size());
        if (result_vendor_ids.empty()) {
            return;
        }

        for (auto const& opt : tmp) {
            // The response should be an OptionVendor.
            OptionVendorPtr vendor_resp;

            for (uint32_t vendor_id : result_vendor_ids) {
                vendor_resp = boost::dynamic_pointer_cast<OptionVendor>(opt.second);
                ASSERT_TRUE(vendor_resp);
                if (vendor_resp->getVendorId() == vendor_id) {
                    break;
                }
                vendor_resp.reset();
            }
            ASSERT_TRUE(vendor_resp);
            if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS) {
                for (uint16_t option : requested_options) {
                    if (option == DOCSIS3_V4_TFTP_SERVERS) {
                        // Option 2 should be present.
                        OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
                        ASSERT_TRUE(docsis2);

                        // It should be an Option4AddrLst.
                        Option4AddrLstPtr tftp_srvs =
                                boost::dynamic_pointer_cast<Option4AddrLst>(docsis2);
                        ASSERT_TRUE(tftp_srvs);

                        // Check that the provided addresses match the ones in configuration.
                        Option4AddrLst::AddressContainer addrs = tftp_srvs->getAddresses();
                        ASSERT_EQ(2, addrs.size());
                        EXPECT_EQ("192.0.2.1", addrs[0].toText());
                        EXPECT_EQ("192.0.2.2", addrs[1].toText());
                    }

                    if (option == 22) {
                        // Option 22 should be present.
                        OptionPtr custom = vendor_resp->getOption(22);
                        ASSERT_TRUE(custom);

                        // It should be an OptionString.
                        OptionStringPtr tag = boost::dynamic_pointer_cast<OptionString>(custom);
                        ASSERT_TRUE(tag);

                        // Check that the provided value match the ones in configuration.
                        EXPECT_EQ(tag->getValue(), "first");
                    }
                }
            } else {
                // If explicitly sending OptionVendor and the vendor is not
                // VENDOR_ID_CABLE_LABS, options should not be present. Kea only
                // knows how to process VENDOR_ID_CABLE_LABS DOCSIS3_V4_ORO
                // (suboption 1).
                // Option 2 should not be present.
                OptionPtr docsis2 = vendor_resp->getOption(2);
                ASSERT_FALSE(docsis2);

                // Option 22 should not be present.
                OptionPtr custom = vendor_resp->getOption(22);
                ASSERT_FALSE(custom);
            }
        }
    }

    /// @brief Checks if vendor options are parsed correctly and the persistent
    /// options are actually assigned. Also covers negative tests that options
    /// are not provided when a different vendor ID is given.
    ///
    /// @param configured_vendor_ids The vendor IDs that are configured in the
    /// server: 4491 or both 4491 and 3561.
    /// @param requested_vendor_ids Then vendor IDs that are present in ORO.
    /// @param configured_options The configured options.
    /// @param add_vendor_option The flag which indicates if the request should
    /// contain a OptionVendor option or should the server always send all the
    /// OptionVendor options and suboptions.
    void testVendorOptionsPersistent(std::set<uint32_t> configured_vendor_ids,
                                     std::set<uint32_t> requested_vendor_ids,
                                     std::set<uint16_t> configured_options,
                                     bool add_vendor_option) {
        std::set<uint32_t> result_vendor_ids;
        ASSERT_FALSE(configured_vendor_ids.empty());
        ASSERT_TRUE(configured_vendor_ids.find(VENDOR_ID_CABLE_LABS) != configured_vendor_ids.end());
        if (add_vendor_option) {
            for (uint32_t req : requested_vendor_ids) {
                if (configured_vendor_ids.find(req) != configured_vendor_ids.end()) {
                    result_vendor_ids.insert(req);
                }
            }
        } else {
            result_vendor_ids = configured_vendor_ids;
        }
        ASSERT_FALSE(configured_options.empty());
        ASSERT_TRUE(configured_options.find(DOCSIS3_V4_TFTP_SERVERS) != configured_options.end());
        // Create a config with custom options.
        string config = R"(
            {
                "interfaces-config": {
                    "interfaces": [ "*" ]
                },
                "option-data": [
                    {
                        "always-send": true,
                        "code": 2,
                        "csv-format": true,
                        "data": "192.0.2.1, 192.0.2.2",
                        "name": "tftp-servers",
                        "space": "vendor-4491"
            )";
        if (configured_options.size() > 1) {
            config += R"(
                    },
                    {
                        "always-send": true,
                        "code": 22,
                        "csv-format": true,
                        "data": "first",
                        "name": "tag",
                        "space": "vendor-4491"
            )";
        }
        if (!add_vendor_option) {
            config += R"(
                    },
                    {
                        "always-send": true,
                        "name": "vivso-suboptions",
                        "data": "4491",
                        "space": "dhcp4"
            )";
        }
        if (configured_vendor_ids.size() > 1) {
            config += R"(
                    },
                    {
                        "always-send": true,
                        "code": 2,
                        "csv-format": true,
                        "data": "10.0.2.1, 10.0.2.2",
                        "name": "custom",
                        "space": "vendor-3561"
            )";
            if (configured_options.size() > 1) {
                config += R"(
                    },
                    {
                        "always-send": true,
                        "code": 22,
                        "csv-format": true,
                        "data": "last",
                        "name": "special",
                        "space": "vendor-3561"
                )";
            }
            if (!add_vendor_option) {
                config += R"(
                    },
                    {
                        "always-send": true,
                        "name": "vivso-suboptions",
                        "data": "3561",
                        "space": "dhcp4"
                )";
            }
        }
        config += R"(
                    }
                ],
                "option-def": [
                    {
                        "code": 22,
                        "name": "tag",
                        "space": "vendor-4491",
                        "type": "string"
        )";
        if (configured_vendor_ids.size() > 1) {
            config += R"(
                    },
                    {
                        "code": 2,
                        "name": "custom",
                        "space": "vendor-3561",
                        "type": "ipv4-address",
                        "array": true
                    },
                    {
                        "code": 22,
                        "name": "special",
                        "space": "vendor-3561",
                        "type": "string"
            )";
        }
        config += R"(
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
        EXPECT_NO_THROW(x = Dhcpv4SrvTest::configure(srv, json));
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

        if (add_vendor_option) {
            for (uint32_t vendor_id : requested_vendor_ids) {
                // Let's add a vendor-option (vendor-id=4491).
                OptionVendorPtr vendor(new OptionVendor(Option::V4, vendor_id));

                dis->Pkt::addOption(vendor);
            }
        }

        // Pass it to the server and get an offer
        Pkt4Ptr offer = srv.processDiscover(dis);

        // check if we get response at all
        ASSERT_TRUE(offer);

        // Check if there is a vendor option response
        OptionCollection tmp = offer->getOptions(DHO_VIVSO_SUBOPTIONS);
        ASSERT_EQ(tmp.size(), result_vendor_ids.size());

        for (auto const& opt : tmp) {
            // The response should be an OptionVendor.
            OptionVendorPtr vendor_resp;

            for (uint32_t vendor_id : result_vendor_ids) {
                vendor_resp = boost::dynamic_pointer_cast<OptionVendor>(opt.second);
                ASSERT_TRUE(vendor_resp);
                if (vendor_resp->getVendorId() == vendor_id) {
                    break;
                }
            }
            ASSERT_TRUE(vendor_resp);

            for (uint16_t option : configured_options) {
                if (add_vendor_option &&
                    requested_vendor_ids.find(vendor_resp->getVendorId()) == requested_vendor_ids.end()) {
                    // If explicitly sending OptionVendor and the vendor is not
                    // configured, options should not be present.
                    if (option == DOCSIS3_V4_TFTP_SERVERS) {
                        // Option 2 should not be present.
                        OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
                        ASSERT_FALSE(docsis2);
                    }
                    if (option == 22) {
                        // Option 22 should not be present.
                        OptionPtr custom = vendor_resp->getOption(22);
                        ASSERT_FALSE(custom);
                    }
                } else {
                    if (option == DOCSIS3_V4_TFTP_SERVERS) {
                        // Option 2 should be present.
                        OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
                        ASSERT_TRUE(docsis2);

                        // It should be an Option4AddrLst.
                        Option4AddrLstPtr tftp_srvs;
                        if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS) {
                            tftp_srvs = boost::dynamic_pointer_cast<Option4AddrLst>(docsis2);
                        } else {
                            // The option is serialized as Option so it needs to be converted to
                            // Option4AddrLst.
                            auto const& buffer = docsis2->toBinary();
                            tftp_srvs.reset(new Option4AddrLst(DOCSIS3_V4_TFTP_SERVERS,
                                                               buffer.begin(), buffer.end()));
                        }
                        ASSERT_TRUE(tftp_srvs);

                        // Check that the provided addresses match the ones in configuration.
                        Option4AddrLst::AddressContainer addrs = tftp_srvs->getAddresses();
                        ASSERT_EQ(2, addrs.size());
                        if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS) {
                            EXPECT_EQ("192.0.2.1", addrs[0].toText());
                            EXPECT_EQ("192.0.2.2", addrs[1].toText());
                        } else {
                            EXPECT_EQ("10.0.2.1", addrs[0].toText());
                            EXPECT_EQ("10.0.2.2", addrs[1].toText());
                        }
                    }

                    if (option == 22) {
                        // Option 22 should be present.
                        OptionPtr custom = vendor_resp->getOption(22);
                        ASSERT_TRUE(custom);

                        // It should be an OptionString.
                        // The option is serialized as Option so it needs to be converted to
                        // OptionString.
                        auto const& buffer = custom->toBinary();
                        OptionStringPtr tag(new OptionString(Option::V4, 22,
                                                             buffer.begin(), buffer.end()));
                        ASSERT_TRUE(tag);

                        // Check that the provided value match the ones in configuration.
                        if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS) {
                            EXPECT_EQ(tag->getValue(), "first");
                        } else {
                            EXPECT_EQ(tag->getValue(), "last");
                        }
                    }
                }
            }
        }
    }

    /// @brief Checks if vendor options are parsed correctly and the persistent
    /// options are actually assigned. Also covers negative tests that options
    /// are not provided when a different vendor ID is given.
    ///
    /// @param configured_vendor_ids The vendor IDs that are configured in the
    /// server: 4491 or both 4491 and 3561.
    /// @param requested_vendor_ids Then vendor IDs that are present in ORO.
    /// @param requested_options The requested options in ORO.
    /// @param configured_options The configured options. The suboption 22 has
    /// always send flag set to true so it will always be sent.
    void testVendorOptionsOROAndPersistent(std::set<uint32_t> configured_vendor_ids,
                                           std::set<uint32_t> requested_vendor_ids,
                                           std::set<uint16_t> requested_options,
                                           std::set<uint16_t> configured_options) {
        std::set<uint32_t> result_vendor_ids;
        ASSERT_FALSE(configured_vendor_ids.empty());
        ASSERT_TRUE(configured_vendor_ids.find(VENDOR_ID_CABLE_LABS) != configured_vendor_ids.end());
        result_vendor_ids = configured_vendor_ids;
        ASSERT_FALSE(configured_options.empty());
        ASSERT_TRUE(configured_options.find(DOCSIS3_V4_TFTP_SERVERS) != configured_options.end());
        // Create a config with custom options.
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
            )";
        if (configured_options.size() > 1) {
            config += R"(
                    },
                    {
                        "always-send": true,
                        "code": 22,
                        "csv-format": true,
                        "data": "first",
                        "name": "tag",
                        "space": "vendor-4491"
            )";
        }
        config += R"(
                },
                {
                    "always-send": true,
                    "name": "vivso-suboptions",
                    "data": "4491",
                    "space": "dhcp4"
        )";
        if (configured_vendor_ids.size() > 1) {
            config += R"(
                    },
                    {
                        "code": 2,
                        "csv-format": true,
                        "data": "10.0.2.1, 10.0.2.2",
                        "name": "custom",
                        "space": "vendor-3561"
            )";
            if (configured_options.size() > 1) {
                config += R"(
                    },
                    {
                        "always-send": true,
                        "code": 22,
                        "csv-format": true,
                        "data": "last",
                        "name": "special",
                        "space": "vendor-3561"
                )";
            }
            config += R"(
                },
                {
                    "always-send": true,
                    "name": "vivso-suboptions",
                    "data": "3561",
                    "space": "dhcp4"
            )";
        }
        config += R"(
                    }
                ],
                "option-def": [
                    {
                        "code": 22,
                        "name": "tag",
                        "space": "vendor-4491",
                        "type": "string"
        )";
        if (configured_vendor_ids.size() > 1) {
            config += R"(
                    },
                    {
                        "code": 2,
                        "name": "custom",
                        "space": "vendor-3561",
                        "type": "ipv4-address",
                        "array": true
                    },
                    {
                        "code": 22,
                        "name": "special",
                        "space": "vendor-3561",
                        "type": "string"
            )";
        }
        config += R"(
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
        EXPECT_NO_THROW(x = Dhcpv4SrvTest::configure(srv, json));
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

        // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
        // That suboption has code 1 and is a docsis ORO option.
        OptionUint8ArrayPtr vendor_oro(new OptionUint8Array(Option::V4, DOCSIS3_V4_ORO));
        for (uint16_t option : requested_options) {
            vendor_oro->addValue(option);
        }

        for (uint32_t vendor_id : requested_vendor_ids) {
            OptionVendorPtr vendor(new OptionVendor(Option::V4, vendor_id));
            vendor->addOption(vendor_oro);
            dis->Pkt::addOption(vendor);
        }

        // Pass it to the server and get an offer
        Pkt4Ptr offer = srv.processDiscover(dis);

        // check if we get response at all
        ASSERT_TRUE(offer);

        // Check if there is a vendor option response
        OptionCollection tmp = offer->getOptions(DHO_VIVSO_SUBOPTIONS);
        ASSERT_EQ(tmp.size(), result_vendor_ids.size());

        for (auto const& opt : tmp) {
            // The response should be an OptionVendor.
            OptionVendorPtr vendor_resp;

            for (uint32_t vendor_id : result_vendor_ids) {
                vendor_resp = boost::dynamic_pointer_cast<OptionVendor>(opt.second);
                ASSERT_TRUE(vendor_resp);
                if (vendor_resp->getVendorId() == vendor_id) {
                    break;
                }
            }
            ASSERT_TRUE(vendor_resp);

            for (uint16_t option : configured_options) {
                if (option == DOCSIS3_V4_TFTP_SERVERS) {
                    if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS &&
                        requested_options.find(option) != requested_options.end() &&
                        requested_vendor_ids.find(vendor_resp->getVendorId()) != requested_vendor_ids.end()) {
                        // Option 2 should be present.
                        OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
                        ASSERT_TRUE(docsis2);

                        // It should be an Option4AddrLst.
                        Option4AddrLstPtr tftp_srvs;
                        if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS) {
                            tftp_srvs = boost::dynamic_pointer_cast<Option4AddrLst>(docsis2);
                        } else {
                            // The option is serialized as Option so it needs to be converted to
                            // Option4AddrLst.
                            auto const& buffer = docsis2->toBinary();
                            tftp_srvs.reset(new Option4AddrLst(DOCSIS3_V4_TFTP_SERVERS,
                                                               buffer.begin(), buffer.end()));
                        }
                        ASSERT_TRUE(tftp_srvs);

                        // Check that the provided addresses match the ones in configuration.
                        Option4AddrLst::AddressContainer addrs = tftp_srvs->getAddresses();
                        ASSERT_EQ(2, addrs.size());
                        if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS) {
                            EXPECT_EQ("192.0.2.1", addrs[0].toText());
                            EXPECT_EQ("192.0.2.2", addrs[1].toText());
                        } else {
                            EXPECT_EQ("10.0.2.1", addrs[0].toText());
                            EXPECT_EQ("10.0.2.2", addrs[1].toText());
                        }
                    } else {
                        // If explicitly sending OptionVendor and the vendor is not
                        // VENDOR_ID_CABLE_LABS, or the option is not explicitly
                        // requested, options should not be present. Kea only knows
                        // how to process VENDOR_ID_CABLE_LABS DOCSIS3_V4_ORO
                        // (suboption 1).
                        // Option 2 should not be present.
                        OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
                        ASSERT_FALSE(docsis2);
                    }
                }

                if (option == 22) {
                    // Option 22 should be present.
                    OptionPtr custom = vendor_resp->getOption(22);
                    ASSERT_TRUE(custom);

                    // It should be an OptionString.
                    // The option is serialized as Option so it needs to be converted to
                    // OptionString.
                    auto const& buffer = custom->toBinary();
                    OptionStringPtr tag(new OptionString(Option::V4, 22,
                                                         buffer.begin(), buffer.end()));
                    ASSERT_TRUE(tag);

                    // Check that the provided value match the ones in configuration.
                    if (vendor_resp->getVendorId() == VENDOR_ID_CABLE_LABS) {
                        EXPECT_EQ(tag->getValue(), "first");
                    } else {
                        EXPECT_EQ(tag->getValue(), "last");
                    }
                }
            }
        }
    }

    // @brief Test configuration for IfaceMgr.
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    OptionVendorPtr vendor_opt =
            boost::dynamic_pointer_cast<OptionVendor>(vendor_opt_response);
    ASSERT_TRUE(vendor_opt);
    ASSERT_EQ(vendor_opt->getVendorId(), VENDOR_ID_CABLE_LABS);

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

    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    ASSERT_EQ(vendor->getVendorId(), VENDOR_ID_CABLE_LABS);

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
    ASSERT_NO_THROW(dis->unpack());

    // Check if the packet contains vendor specific information option
    OptionPtr opt = dis->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);

    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    ASSERT_EQ(vendor->getVendorId(), VENDOR_ID_CABLE_LABS);

    opt = vendor->getOption(DOCSIS3_V4_ORO);
    ASSERT_TRUE(opt);

    OptionUint8ArrayPtr oro = boost::dynamic_pointer_cast<OptionUint8Array>(opt);
    EXPECT_TRUE(oro);
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROOneOption) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS },
                         { VENDOR_ID_CABLE_LABS },
                         { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROMultipleOptions) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS },
                         { VENDOR_ID_CABLE_LABS },
                         { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROOneOptionMultipleVendorsMatchOne) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS, 3561 },
                         { VENDOR_ID_CABLE_LABS },
                         { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROMultipleOptionsMultipleVendorsMatchOne) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS, 3561 },
                         { VENDOR_ID_CABLE_LABS },
                         { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROOneOptionMultipleVendorsMatchAll) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS, 3561 },
                         { VENDOR_ID_CABLE_LABS, 3561 },
                         { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROMultipleOptionsMultipleVendorsMatchAll) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS, 3561 },
                         { VENDOR_ID_CABLE_LABS, 3561 },
                         { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROOneOptionDifferentVendorID) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS },
                         { 32768 },
                         { DOCSIS3_V4_TFTP_SERVERS });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROMultipleOptionsDifferentVendorID) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS },
                         { 32768 },
                         { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROOneOptionDifferentVendorIDMultipleVendorsMatchNone) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS, 3561 },
                         { 32768, 16384 },
                         { DOCSIS3_V4_TFTP_SERVERS });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROMultipleOptionDifferentVendorIDMultipleVendorsMatchNone) {
    testVendorOptionsORO({ VENDOR_ID_CABLE_LABS, 3561 },
                         { 32768, 16384 },
                         { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsOneOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS },
                                false);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsMultipleOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS, 22 },
                                false);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsOneOptionMultipleVendorsMatchOne) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS },
                                false);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsMultipleOptionMultipleVendorsMatchOne) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS, 22 },
                                false);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsOneOptionMultipleVendorsMatchAll) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS, 3561 },
                                { DOCSIS3_V4_TFTP_SERVERS },
                                false);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsMultipleOptionMultipleVendorsMatchAll) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS, 3561 },
                                { DOCSIS3_V4_TFTP_SERVERS, 22 },
                                false);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsOneOptionAddVendorOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS },
                                true);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsMultipleOptionAddVendorOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS, 22 },
                                true);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsOneOptionMultipleVendorsMatchOneAddVendorOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS },
                                true);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsMultipleOptionMultipleVendorsMatchOneAddVendorOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS },
                                { DOCSIS3_V4_TFTP_SERVERS, 22 },
                                true);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsOneOptionMultipleVendorsMatchAllAddVendorOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS, 3561 },
                                { DOCSIS3_V4_TFTP_SERVERS },
                                true);
}

// This test checks vendor options are parsed correctly and the persistent
// options are actually assigned.
TEST_F(VendorOptsTest, vendorPersistentOptionsMultipleOptionMultipleVendorsMatchAllAddVendorOption) {
    testVendorOptionsPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                { VENDOR_ID_CABLE_LABS, 3561 },
                                { DOCSIS3_V4_TFTP_SERVERS, 22 },
                                true);
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOption) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { VENDOR_ID_CABLE_LABS },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptions) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { VENDOR_ID_CABLE_LABS },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionMultipleVendorsMatchOne) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionsMultipleVendorsMatchOne) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionMultipleVendorsMatchAll) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS, 3561 },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionsMultipleVendorsMatchAll) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS, 3561 },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionDifferentVendorID) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { 32768 },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionsDifferentVendorID) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { 32768 },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionDifferentVendorIDMultipleVendorsMatchNone) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { 32768, 16384 },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionDifferentVendorIDMultipleVendorsMatchNone) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { 32768, 16384 },
                                      { DOCSIS3_V4_TFTP_SERVERS },
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { VENDOR_ID_CABLE_LABS },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionsNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { VENDOR_ID_CABLE_LABS },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionMultipleVendorsMatchOneNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionsMultipleVendorsMatchOneNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionMultipleVendorsMatchAllNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS, 3561 },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionsMultipleVendorsMatchAllNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { VENDOR_ID_CABLE_LABS, 3561 },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionDifferentVendorIDNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { 32768 },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionsDifferentVendorIDNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS },
                                      { 32768 },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentOneOptionDifferentVendorIDMultipleVendorsMatchNoneNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { 32768, 16384 },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS });
}

// Same as vendorOptionsORO except a different vendor ID than Cable Labs is
// provided and vendor options are expected to not be present in the response.
TEST_F(VendorOptsTest, vendorOptionsOROAndPersistentMultipleOptionDifferentVendorIDMultipleVendorsMatchNoneNoneRequested) {
    testVendorOptionsOROAndPersistent({ VENDOR_ID_CABLE_LABS, 3561 },
                                      { 32768, 16384 },
                                      {},
                                      { DOCSIS3_V4_TFTP_SERVERS, 22 });
}

// This test checks if cancelled options are actually never assigned.
TEST_F(VendorOptsTest, vendorCancelledOptions) {
    NakedDhcpv4Srv srv(0);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "    \"option-def\": [ {"
        "          \"space\": \"vendor-4491\","
        "          \"name\": \"foo\","
        "          \"code\": 100,"
        "          \"type\": \"string\""
        "        } ],"
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 2,"
        "          \"data\": \"192.0.2.1, 192.0.2.2\","
        "          \"csv-format\": true,"
        "          \"always-send\": true"
        "        },{"
        "          \"space\": \"vendor-4491\","
        "          \"code\": 100,"
        "          \"csv-format\": true,"
        "          \"data\": \"bar\""
        "        } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"eth0\", "
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 2,"
        "          \"never-send\": true"
        "        } ]"
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_) << comment_->str();

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

    // There should be no vendor option response.
    EXPECT_FALSE(offer->getOption(DHO_VIVSO_SUBOPTIONS));

    // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
    // That suboption has code 1 and is a docsis ORO option.
    boost::shared_ptr<OptionUint8Array> vendor_oro(new OptionUint8Array(Option::V4,
                                                                        DOCSIS3_V4_ORO));
    vendor_oro->addValue(DOCSIS3_V4_TFTP_SERVERS); // Request option 2.
    vendor->addOption(vendor_oro);

    // Need to process DHCPDISCOVER again after requesting new option.
    offer = srv.processDiscover(dis);
    ASSERT_TRUE(offer);

    // Again there should be no vendor option response.
    EXPECT_FALSE(offer->getOption(DHO_VIVSO_SUBOPTIONS));

    // Request option 100.
    vendor_oro->addValue(100);

    // Try again.
    offer = srv.processDiscover(dis);
    ASSERT_TRUE(offer);

    // Check if there is a vendor option response
    OptionPtr tmp = offer->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(tmp);

    // The response should be OptionVendor object
    boost::shared_ptr<OptionVendor> vendor_resp =
        boost::dynamic_pointer_cast<OptionVendor>(tmp);
    ASSERT_TRUE(vendor_resp);

    // No tftp-servers.
    EXPECT_FALSE(vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS));

    // But an option 100.
    EXPECT_EQ(1, vendor_resp->getOptions().size());
    EXPECT_TRUE(vendor_resp->getOption(100));
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
    EXPECT_NO_THROW(x = Dhcpv4SrvTest::configure(srv, json_bogus));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(1, rcode_);

    // This should work (option definition present)
    EXPECT_NO_THROW(x = Dhcpv4SrvTest::configure(srv, json_valid));
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
    EXPECT_EQ(rsp_vivso->getVendorId(), 25167);

    // Now check that it contains suboption 2 with appropriate content.
    OptionPtr subopt2 = rsp_vivso->getOption(2);
    ASSERT_TRUE(subopt2);
    vector<uint8_t> subopt2bin = subopt2->toBinary(false);
    string txt(subopt2bin.begin(), subopt2bin.end());
    EXPECT_EQ("tftp://192.0.2.1/genexis/HMC1000.v1.3.0-R.img", txt);

    // Check the config was not altered by unwanted side effect
    // on the vendor option.

    // Get class config:
    ClientClassDefPtr cdef = CfgMgr::instance().getCurrentCfg()->
        getClientClassDictionary()->findClass("cpe_genexis");
    ASSERT_TRUE(cdef);
    OptionDescriptor cdesc = cdef->getCfgOption()->
        get(DHCP4_OPTION_SPACE, DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(cdesc.option_);
    // If the config was altered these two EXPECT will fail.
    EXPECT_TRUE(cdesc.option_->getOptions().empty());
    EXPECT_FALSE(cdesc.option_->getOption(2));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(srv, json));
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

// Checks if it's possible to have 2 vivco options  with different vendor IDs.
TEST_F(VendorOptsTest, twoVivcos) {
    Dhcp4Client client;

    // The config defines 2 vendors with for each a vivco option,
    // having the always send flag set to true.
    // The encoding for the option-class option is a bit hairy: first is
    // the vendor id (uint32) and the remaining is a binary which stands
    // for a tuple so length (uint8) x value.
    string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ ]"
        "    },"
        "    \"option-data\": ["
        "        {"
        "            \"name\": \"vivco-suboptions\","
        "            \"always-send\": true,"
        "            \"data\": \"1234, 03666f6f\""
        "        },"
        "        {"
        "            \"name\": \"vivco-suboptions\","
        "            \"always-send\": true,"
        "            \"data\": \"5678, 03626172\""
        "        }"
        "    ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"10.0.0.10 - 10.0.0.100\" } ],"
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"interface\": \"eth0\" "
        " } ]"
        "}";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Let's check whether the server is able to process this packet.
    EXPECT_NO_THROW(client.doDiscover());
    ASSERT_TRUE(client.getContext().response_);

    // Check whether there are vivco options.
    const OptionCollection& classes =
        client.getContext().response_->getOptions(DHO_VIVCO_SUBOPTIONS);
    ASSERT_EQ(2, classes.size());
    OptionVendorClassPtr opt_class1234;
    OptionVendorClassPtr opt_class5678;
    for (auto opt : classes) {
        ASSERT_EQ(DHO_VIVCO_SUBOPTIONS, opt.first);
        OptionVendorClassPtr opt_class =
            boost::dynamic_pointer_cast<OptionVendorClass>(opt.second);
        ASSERT_TRUE(opt_class);
        uint32_t vendor_id = opt_class->getVendorId();
        if (vendor_id == 1234) {
            ASSERT_FALSE(opt_class1234);
            opt_class1234 = opt_class;
            continue;
        }
        ASSERT_EQ(5678, vendor_id);
        ASSERT_FALSE(opt_class5678);
        opt_class5678 = opt_class;
    }

    // Verify first vivco option.
    ASSERT_TRUE(opt_class1234);
    ASSERT_EQ(1, opt_class1234->getTuplesNum());
    EXPECT_EQ("foo", opt_class1234->getTuple(0).getText());

    // Verify second vivco option.
    ASSERT_TRUE(opt_class5678);
    ASSERT_EQ(1, opt_class5678->getTuplesNum());
    EXPECT_EQ("bar", opt_class5678->getTuple(0).getText());
}
