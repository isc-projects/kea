// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet.h>
#include <process/logging_info.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::process;

// Those are the tests for SrvConfig storage. Right now they are minimal,
// but the number is expected to grow significantly once we migrate more
// parameters from CfgMgr storage to SrvConfig storage.

namespace {

/// @brief Derivation of the @c ConfigBase not being @c SrvConfig.
///
/// This is used to verify that the appropriate error is returned
/// when other derivation of the @c ConfigBase than @c SrvConfig
/// is used.
class NonSrvConfig : public ConfigBase { };

/// @brief Number of IPv4 and IPv6 subnets to be created for a test.
const int TEST_SUBNETS_NUM = 3;

/// @brief Test fixture class for testing configuration data storage.
class SrvConfigTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Creates IPv4 and IPv6 subnets for unit test. The number of subnets
    /// is @c TEST_SUBNETS_NUM for IPv4 and IPv6 each.
    SrvConfigTest()
        : iface_mgr_test_config_(true),
          ref_dictionary_(new ClientClassDictionary()) {

        // Disable DDNS.
        enableDDNS(false);

        // Create IPv4 subnets.
        for (int i = 0; i < TEST_SUBNETS_NUM; ++i) {
            // Default triplet carried undefined value.
            Triplet<uint32_t> def_triplet;
            // Create a collection of subnets: 192.0.X.0/24 where X is
            // 0, 1, 2 etc.
            Subnet4Ptr subnet(new Subnet4(IOAddress(0xC0000000 | (i << 2)),
                                          24, def_triplet, def_triplet,
                                          4000));
            test_subnets4_.push_back(subnet);
        }
        // Create IPv6 subnets.
        IOAddress prefix("2001:db8:1::");
        for (int i = 0; i < TEST_SUBNETS_NUM; ++i) {
            // This is a base prefix. All other prefixes will be created by
            // modifying this one.
            std::vector<uint8_t> prefix_bytes = prefix.toBytes();
            // Modify 5th byte of the prefix, so 2001:db8:1::0 becomes
            // 2001:db8:2::0 etc.
            ++prefix_bytes[5];
            prefix = IOAddress::fromBytes(prefix.getFamily(), &prefix_bytes[0]);
            Subnet6Ptr subnet(new Subnet6(prefix, 64, 1000, 2000, 3000, 4000));
            test_subnets6_.push_back(subnet);
        }

        // Build our reference dictionary of client classes
        ref_dictionary_->addClass("cc1", ExpressionPtr(),
                                  "", false, false, CfgOptionPtr());
        ref_dictionary_->addClass("cc2", ExpressionPtr(),
                                  "", false, false, CfgOptionPtr());
        ref_dictionary_->addClass("cc3", ExpressionPtr(),
                                  "", false, false, CfgOptionPtr());
    }


    /// @brief Destructor.
    virtual ~SrvConfigTest() {
    }

    /// @brief Convenience function which adds IPv4 subnet to the configuration.
    ///
    /// @param index Index of the subnet in the @c test_subnets4_ collection
    /// which should be added to the configuration. The configuration is stored
    /// in the @ conf_ member. This value must be lower than
    /// @c TEST_SUBNETS_NUM.
    ///
    /// @todo Until the subnets configuration is migrated from the @c CfgMgr to
    /// the @c SrvConfig object, this function adds the subnet to the
    /// @c CfgMgr. Once, the subnet configuration is held in the
    /// @c SrvConfig this function must be modified to store the subnets in
    /// the @c conf_ object.
    void addSubnet4(const unsigned int index);

    /// @brief Convenience function which adds IPv6 subnet to the configuration.
    ///
    /// @param index Index of the subnet in the @c test_subnets6_ collection
    /// which should be added to the configuration. The configuration is stored
    /// in the @ conf_ member. This value must be lower than
    /// @c TEST_SUBNETS_NUM.
    ///
    /// @todo Until the subnets configuration is migrated from the @c CfgMgr to
    /// the @c SrvConfig object, this function adds the subnet to the
    /// @c CfgMgr. Once, the subnet configuration is held in the
    /// @c SrvConfig this function must be modified to store the subnets in
    /// @c conf_ object.
    void addSubnet6(const unsigned int index);

    /// @brief Enable/disable DDNS.
    ///
    /// @param enable A boolean value indicating if the DDNS should be
    /// enabled (true) or disabled (false).
    void enableDDNS(const bool enable);

    /// @brief Stores configuration.
    SrvConfig conf_;
    /// @brief A collection of IPv4 subnets used by unit tests.
    Subnet4Collection test_subnets4_;
    /// @brief A collection of IPv6 subnets used by unit tests.
    Subnet6Collection test_subnets6_;
    /// @brief Fakes interface configuration.
    isc::dhcp::test::IfaceMgrTestConfig iface_mgr_test_config_;

    /// @brief Client class dictionary with fixed content
    ClientClassDictionaryPtr ref_dictionary_;
};

void
SrvConfigTest::addSubnet4(const unsigned int index) {
    if (index >= TEST_SUBNETS_NUM) {
        FAIL() << "Subnet index " << index << "out of range (0.."
               << TEST_SUBNETS_NUM << "): " << "unable to add IPv4 subnet";
    }
    conf_.getCfgSubnets4()->add(test_subnets4_[index]);
}

void
SrvConfigTest::addSubnet6(const unsigned int index) {
    if (index >= TEST_SUBNETS_NUM) {
        FAIL() << "Subnet index " << index << "out of range (0.."
               << TEST_SUBNETS_NUM << "): " << "unable to add IPv6 subnet";
    }
    conf_.getCfgSubnets6()->add(test_subnets6_[index]);
}

void
SrvConfigTest::enableDDNS(const bool enable) {
    const D2ClientConfigPtr& d2_config = conf_.getD2ClientConfig();
    ASSERT_TRUE(d2_config);
    d2_config->enableUpdates(enable);
}

// Check that by default there are no logging entries
TEST_F(SrvConfigTest, basic) {
    EXPECT_TRUE(conf_.getLoggingInfo().empty());
}

// Check that SrvConfig can store logging information.
TEST_F(SrvConfigTest, loggingInfo) {
    LoggingInfo log1;
    log1.clearDestinations();
    log1.name_ = "foo";
    log1.severity_ = isc::log::WARN;
    log1.debuglevel_ = 77;

    LoggingDestination dest;
    dest.output_ = "some-logfile.txt";
    dest.maxver_ = 5;
    dest.maxsize_ = 2097152;

    log1.destinations_.push_back(dest);

    conf_.addLoggingInfo(log1);

    EXPECT_EQ("foo", conf_.getLoggingInfo()[0].name_);
    EXPECT_EQ(isc::log::WARN, conf_.getLoggingInfo()[0].severity_);
    EXPECT_EQ(77, conf_.getLoggingInfo()[0].debuglevel_);

    EXPECT_EQ("some-logfile.txt", conf_.getLoggingInfo()[0].destinations_[0].output_);
    EXPECT_EQ(5, conf_.getLoggingInfo()[0].destinations_[0].maxver_);
    EXPECT_EQ(2097152, conf_.getLoggingInfo()[0].destinations_[0].maxsize_);
}

// Check that the configuration summary including information about the status
// of DDNS is returned.
TEST_F(SrvConfigTest, summaryDDNS) {
    EXPECT_EQ("DDNS: disabled",
              conf_.getConfigSummary(SrvConfig::CFGSEL_DDNS));

    enableDDNS(true);
    EXPECT_EQ("DDNS: enabled",
              conf_.getConfigSummary(SrvConfig::CFGSEL_DDNS));

    enableDDNS(false);
    EXPECT_EQ("no IPv4 subnets!; no IPv6 subnets!; DDNS: disabled",
              conf_.getConfigSummary(SrvConfig::CFGSEL_ALL));
}

// Check that the configuration summary including information about added
// subnets is returned.
TEST_F(SrvConfigTest, summarySubnets) {
    EXPECT_EQ("no config details available",
              conf_.getConfigSummary(SrvConfig::CFGSEL_NONE));

    // Initially, there are no subnets added but it should be explicitly
    // reported when we query for information about the subnets.
    EXPECT_EQ("no IPv4 subnets!; no IPv6 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));

    // If we just want information about IPv4 subnets, there should be no
    // mention of IPv6 subnets, even though there are none added.
    EXPECT_EQ("no IPv4 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET4));

    // If we just want information about IPv6 subnets, there should be no
    // mention of IPv4 subnets, even though there are none added.
    EXPECT_EQ("no IPv6 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET6));

    // Add IPv4 subnet and make sure it is reported.
    addSubnet4(0);
    EXPECT_EQ("added IPv4 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET4));
    EXPECT_EQ("added IPv4 subnets: 1; no IPv6 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));

    // Add IPv6 subnet and make sure it is reported.
    addSubnet6(0);
    EXPECT_EQ("added IPv6 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET6));
    EXPECT_EQ("added IPv4 subnets: 1; added IPv6 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));

    // Add one more subnet and make sure the bumped value is only
    // for IPv4, but not for IPv6.
    addSubnet4(1);
    EXPECT_EQ("added IPv4 subnets: 2; added IPv6 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));
    EXPECT_EQ("added IPv4 subnets: 2",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET4));

    addSubnet6(1);
    EXPECT_EQ("added IPv4 subnets: 2; added IPv6 subnets: 2",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));
}

// Verifies that we can get and set the client class dictionary
TEST_F(SrvConfigTest, classDictionaryBasics) {
    ClientClassDictionaryPtr d1;
    SrvConfig conf(32);

    // Upon construction the dictionary should be empty.
    ASSERT_TRUE(d1 = conf.getClientClassDictionary());
    EXPECT_EQ(0, d1->getClasses()->size());

    // Verify we can replace it with a new dictionary.
    ASSERT_NO_THROW(conf.setClientClassDictionary(ref_dictionary_));
    ASSERT_TRUE(d1 = conf.getClientClassDictionary());
    EXPECT_EQ(ref_dictionary_->getClasses()->size(), d1->getClasses()->size());

    // Verify const fetcher works too.
    const ClientClassDictionaryPtr cd = conf.getClientClassDictionary();
    ASSERT_TRUE(cd);
    EXPECT_EQ(ref_dictionary_->getClasses()->size(), cd->getClasses()->size());
}

// This test verifies that RFC6842 (echo client-id) compatibility may be
// configured.
TEST_F(SrvConfigTest, echoClientId) {
    SrvConfig conf;

    // Check that the default is true
    EXPECT_TRUE(conf.getEchoClientId());

    // Check that it can be modified to false
    conf.setEchoClientId(false);
    EXPECT_FALSE(conf.getEchoClientId());

    // Check that the default value can be restored
    conf.setEchoClientId(true);
    EXPECT_TRUE(conf.getEchoClientId());

    // Check the other constructor has the same default
    SrvConfig conf1(1);
    EXPECT_TRUE(conf1.getEchoClientId());
}

// This test checks if entire configuration can be copied and that the sequence
// number is not affected.
TEST_F(SrvConfigTest, copy) {
    // Create two configurations with different sequence numbers.
    SrvConfig conf1(32);
    SrvConfig conf2(64);

    // Set logging information for conf1.
    LoggingInfo info;
    info.name_ = "foo";
    info.severity_ = isc::log::DEBUG;
    info.debuglevel_ = 64;
    info.destinations_.push_back(LoggingDestination());

    // Set interface configuration for conf1.
    conf1.getCfgIface()->use(AF_INET, "eth0");
    conf1.addLoggingInfo(info);

    // Add option definition.
    OptionDefinitionPtr def(new OptionDefinition("option-foo", 5, "string"));
    conf1.getCfgOptionDef()->add(def, "isc");

    // Add an option.
    OptionPtr option(new Option(Option::V6, 1000, OptionBuffer(10, 0xFF)));
    conf1.getCfgOption()->add(option, true, DHCP6_OPTION_SPACE);

    // Add a class dictionary
    conf1.setClientClassDictionary(ref_dictionary_);

    // Make sure both configurations are different.
    ASSERT_TRUE(conf1 != conf2);

    // Copy conf1 to conf2.
    ASSERT_NO_THROW(conf1.copy(conf2));

    // Now they should be equal.
    EXPECT_TRUE(conf1 == conf2);

    // But, their sequence numbers should be unequal.
    EXPECT_FALSE(conf1.sequenceEquals(conf2));
}

// This test checks that two configurations can be compared for (in)equality.
TEST_F(SrvConfigTest, equality) {
    SrvConfig conf1(32);
    SrvConfig conf2(64);

    // Initially, both objects should be equal, even though the configuration
    // sequences are not matching.
    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by logging information.
    LoggingInfo info1;
    LoggingInfo info2;
    info1.name_ = "foo";
    info2.name_ = "bar";

    conf1.addLoggingInfo(info1);
    conf2.addLoggingInfo(info2);

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf1.addLoggingInfo(info2);
    conf2.addLoggingInfo(info1);

    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by interface configuration.
    conf1.getCfgIface()->use(AF_INET, "eth0");

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf2.getCfgIface()->use(AF_INET, "eth0");

    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by option definitions.
    conf1.getCfgOptionDef()->
        add(OptionDefinitionPtr(new OptionDefinition("option-foo", 123,
                                                     "uint16_t")), "isc");

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf2.getCfgOptionDef()->
        add(OptionDefinitionPtr(new OptionDefinition("option-foo", 123,
                                                     "uint16_t")), "isc");
    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by option data.
    OptionPtr option(new Option(Option::V6, 1000, OptionBuffer(1, 0xFF)));
    conf1.getCfgOption()->add(option, false, "isc");

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf2.getCfgOption()->add(option, false, "isc");

    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Add a class dictionary to conf1
    conf1.setClientClassDictionary(ref_dictionary_);
    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    // Add same class dictionary to conf2
    conf2.setClientClassDictionary(ref_dictionary_);
    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);
}

// Verifies that we can get and set configured hooks libraries
TEST_F(SrvConfigTest, hooksLibraries) {
    SrvConfig conf(32);
    isc::hooks::HooksConfig& libraries = conf.getHooksConfig();

    // Upon construction configured hooks libraries should be empty.
    EXPECT_EQ(0, libraries.get().size());

    // Verify we can update it.
    ConstElementPtr elem0;
    libraries.add("foo", elem0);
    std::string config = "{ \"library\": \"bar\" }";
    ConstElementPtr elem1 = Element::fromJSON(config);
    libraries.add("bar", elem1);
    EXPECT_EQ(2, libraries.get().size());
    EXPECT_EQ(2, conf.getHooksConfig().get().size());

    // Try to copy
    SrvConfig copied(64);
    ASSERT_TRUE(conf != copied);
    ASSERT_NO_THROW(conf.copy(copied));
    ASSERT_TRUE(conf == copied);
    EXPECT_EQ(2, copied.getHooksConfig().get().size());

    EXPECT_TRUE(copied.getHooksConfig().equal(conf.getHooksConfig()));
}

// Verifies basic functions of configured global handling.
TEST_F(SrvConfigTest, configuredGlobals) {
    // Create an instance.
    SrvConfig conf(32);

    // The map of configured globals should be empty.
    ConstElementPtr srv_globals = conf.getConfiguredGlobals();
    ASSERT_TRUE(srv_globals);
    ASSERT_EQ(Element::map, srv_globals->getType());
    ASSERT_TRUE(srv_globals->mapValue().empty());

    // Attempting to extract globals from a non-map should throw.
    ASSERT_THROW(conf.extractConfiguredGlobals(Element::create(777)), isc::BadValue);

    // Now let's create a configuration from which to extract global scalars.
    // Extraction (currently) has no business logic, so the elements we use
    // can be arbitrary.
    ConstElementPtr global_cfg;
    std::string global_cfg_str =
    "{\n"
    " \"astring\": \"okay\",\n"
    " \"amap\": { \"not-this\":777, \"not-that\": \"poo\" },\n"
    " \"anint\": 444,\n"
    " \"alist\": [ 1, 2, 3 ],\n"
    " \"abool\": true\n"
    "}\n";
    ASSERT_NO_THROW(global_cfg = Element::fromJSON(global_cfg_str));

    // Extract globals from the config.
    ASSERT_NO_THROW(conf.extractConfiguredGlobals(global_cfg));

    // Now see if the extract was correct.
    srv_globals = conf.getConfiguredGlobals();
    ASSERT_TRUE(srv_globals);
    ASSERT_EQ(Element::map, srv_globals->getType());
    ASSERT_FALSE(srv_globals->mapValue().empty());

    // Maps and lists should be excluded.
    auto globals = srv_globals->mapValue();
    for (auto global = globals.begin(); global != globals.end(); ++global) {
        if (global->first == "astring") {
            ASSERT_EQ(Element::string, global->second->getType());
            EXPECT_EQ("okay", global->second->stringValue());
        } else if (global->first == "anint") {
            ASSERT_EQ(Element::integer, global->second->getType());
            EXPECT_EQ(444, global->second->intValue());
        } else if (global->first == "abool") {
            ASSERT_EQ(Element::boolean, global->second->getType());
            EXPECT_TRUE(global->second->boolValue());
        } else {
            ADD_FAILURE() << "unexpected element found:" << global->first;
        }
    }
}

// Verifies that the toElement method works well (tests limited to
// direct parameters)
TEST_F(SrvConfigTest, unparse) {
    SrvConfig conf(32);
    std::string header4 = "{\n\"Dhcp4\": {\n";
    std::string header6 = "{\n\"Dhcp6\": {\n";

    std::string defaults = "\"decline-probation-period\": 0,\n";
    defaults += "\"dhcp4o6-port\": 0,\n";
    defaults += "\"interfaces-config\": { \"interfaces\": [ ],\n";
    defaults += " \"re-detect\": false },\n";
    defaults += "\"option-def\": [ ],\n";
    defaults += "\"option-data\": [ ],\n";
    defaults += "\"expired-leases-processing\": ";
    defaults += conf.getCfgExpiration()->toElement()->str() + ",\n";
    defaults += "\"lease-database\": { \"type\": \"memfile\" },\n";
    defaults += "\"hooks-libraries\": [ ],\n";
    defaults += "\"sanity-checks\": {\n";
    defaults += "    \"lease-checks\": \"warn\"\n";
    defaults += "    },\n";
    defaults += "\"dhcp-ddns\": \n";

    defaults += conf.getD2ClientConfig()->toElement()->str() + ",\n";

    std::string defaults4 = "\"echo-client-id\": true,\n";
    defaults4 += "\"shared-networks\": [ ],\n";
    defaults4 += "\"subnet4\": [ ],\n";
    defaults4 += "\"host-reservation-identifiers\": ";
    defaults4 += "[ \"hw-address\", \"duid\", \"circuit-id\", \"client-id\" ],\n";

    std::string defaults6 = "\"relay-supplied-options\": [ \"65\" ],\n";
    defaults6 += "\"shared-networks\": [ ],\n";
    defaults6 += "\"subnet6\": [ ],\n";
    defaults6 += "\"server-id\": ";
    defaults6 += conf.getCfgDUID()->toElement()->str() + ",\n";
    defaults6 += "\"host-reservation-identifiers\": ";
    defaults6 += "[ \"hw-address\", \"duid\" ],\n";
    defaults6 += "\"dhcp4o6-port\": 0,\n";
    defaults6 += "\"mac-sources\": [ \"any\" ]\n";

    std::string params = "\"echo-client-id\": true,\n";
    params += "\"dhcp4o6-port\": 0\n";
    std::string trailer = "}\n}\n";

    // Verify DHCPv4
    CfgMgr::instance().setFamily(AF_INET);
    isc::test::runToElementTest<SrvConfig>
        (header4 + defaults + defaults4 + params + trailer, conf);

    // Verify DHCPv6
    CfgMgr::instance().setFamily(AF_INET6);
    isc::test::runToElementTest<SrvConfig>
        (header6 + defaults + defaults6 + trailer, conf);

    // Verify direct non-default parameters and configured globals
    CfgMgr::instance().setFamily(AF_INET);
    conf.setEchoClientId(false);
    conf.setDhcp4o6Port(6767);
    // Add "configured globals"
    conf.addConfiguredGlobal("renew-timer", Element::create(777));
    conf.addConfiguredGlobal("foo", Element::create("bar"));
    params = "\"echo-client-id\": false,\n";
    params += "\"dhcp4o6-port\": 6767,\n";
    params += "\"renew-timer\": 777,\n";
    params += "\"foo\": \"bar\"\n";
    isc::test::runToElementTest<SrvConfig>
        (header4 + defaults + defaults4 + params + trailer, conf);

    // Verify direct non-default parameters and configured globals
    CfgMgr::instance().setFamily(AF_INET6);
    params = ",\"dhcp4o6-port\": 6767,\n";
    params += "\"renew-timer\": 777,\n";
    params += "\"foo\": \"bar\"\n";
    isc::test::runToElementTest<SrvConfig>
        (header6 + defaults + defaults6 + params + trailer, conf);
}

// Verifies that the toElement method does not miss host reservations
TEST_F(SrvConfigTest, unparseHR) {
    // DHCPv4 version
    CfgMgr::instance().setFamily(AF_INET);
    SrvConfig conf4(32);

    // Add a plain subnet
    Triplet<uint32_t> def_triplet;
    SubnetID p_id(1);
    Subnet4Ptr psubnet4(new Subnet4(IOAddress("192.0.1.0"), 24,
                                    def_triplet, def_triplet, 4000, p_id));
    conf4.getCfgSubnets4()->add(psubnet4);

    // Add a shared network
    SharedNetwork4Ptr network4(new SharedNetwork4("frog"));
    conf4.getCfgSharedNetworks4()->add(network4);

    // Add a shared subnet
    SubnetID s_id(100);
    Subnet4Ptr ssubnet4(new Subnet4(IOAddress("192.0.2.0"), 24,
                                    def_triplet, def_triplet, 4000, s_id));
    network4->add(ssubnet4);

    // Add a v4 global host reservation to the plain subnet
    HostPtr ghost4(new Host("AA:01:02:03:04:05", "hw-address",
                            SUBNET_ID_GLOBAL, SUBNET_ID_UNUSED,
                            IOAddress("192.0.3.1")));
    conf4.getCfgHosts()->add(ghost4);

    // Add a host reservation to the plain subnet
    HostPtr phost4(new Host("00:01:02:03:04:05", "hw-address",
                            p_id, SUBNET_ID_UNUSED, IOAddress("192.0.1.1")));
    conf4.getCfgHosts()->add(phost4);

    // Add a host reservation to the shared subnet
    HostPtr shost4(new Host("00:05:04:03:02:01", "hw-address",
                            s_id, SUBNET_ID_UNUSED, IOAddress("192.0.2.1")));
    conf4.getCfgHosts()->add(shost4);

    // Unparse the config
    ConstElementPtr unparsed4 = conf4.toElement();
    ASSERT_TRUE(unparsed4);
    ASSERT_EQ(Element::map, unparsed4->getType());

    // Get Dhcp4 entry
    ConstElementPtr dhcp4;
    ASSERT_NO_THROW(dhcp4 = unparsed4->get("Dhcp4"));
    ASSERT_TRUE(dhcp4);
    ASSERT_EQ(Element::map, dhcp4->getType());

    // Get global host reservations
    ConstElementPtr check;
    ASSERT_NO_THROW(check = dhcp4->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the global host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the reserved address
    ASSERT_NO_THROW(check = check->get("ip-address"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("192.0.3.1", check->stringValue());

    // Get plain subnets
    ASSERT_NO_THROW(check = dhcp4->get("subnet4"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 1
    ConstElementPtr sub;
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(p_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the reserved address
    ASSERT_NO_THROW(check = check->get("ip-address"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("192.0.1.1", check->stringValue());

    // Get shared networks
    ASSERT_NO_THROW(check = dhcp4->get("shared-networks"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared network
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its name is "frog"
    ASSERT_NO_THROW(sub = check->get("name"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::string, sub->getType());
    EXPECT_EQ("frog", sub->stringValue());

    // Get shared subnets
    ASSERT_NO_THROW(check = check->get("subnet4"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 100
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(s_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the reserved address
    ASSERT_NO_THROW(check = check->get("ip-address"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("192.0.2.1", check->stringValue());

    // DHCPv6 version
    CfgMgr::instance().setFamily(AF_INET6);
    SrvConfig conf6(32);

    // Add a plain subnet
    Subnet6Ptr psubnet6(new Subnet6(IOAddress("2001:db8:1::"), 64,
                                    1000, 2000, 3000, 4000, p_id));
    conf6.getCfgSubnets6()->add(psubnet6);

    // Add a shared network
    SharedNetwork6Ptr network6(new SharedNetwork6("frog"));
    conf6.getCfgSharedNetworks6()->add(network6);

    // Add a shared subnet
    Subnet6Ptr ssubnet6(new Subnet6(IOAddress("2001:db8:2::"), 64,
                                    1000, 2000, 3000, 4000, s_id));
    network6->add(ssubnet6);

    // Add a v6 global host reservation
    HostPtr ghost6(new Host("ff:b2:c3:d4:e5:f6", "duid", SUBNET_ID_UNUSED,
                            SUBNET_ID_GLOBAL, IOAddress::IPV4_ZERO_ADDRESS(),
                            "global.example.org"));
    conf6.getCfgHosts()->add(ghost6);

    // Add a host reservation to the plain subnet
    HostPtr phost6(new Host("a1:b2:c3:d4:e5:f6", "duid", SUBNET_ID_UNUSED,
                            p_id, IOAddress::IPV4_ZERO_ADDRESS(),
                            "foo.example.org"));

    conf6.getCfgHosts()->add(phost6);

    // Add a host reservation to the shared subnet
    HostPtr shost6(new Host("f6:e5:d4:c3:b2:a1", "duid", SUBNET_ID_UNUSED,
                            s_id, IOAddress::IPV4_ZERO_ADDRESS(),
                            "bar.example.org"));
    conf6.getCfgHosts()->add(shost6);

    // Unparse the config
    ConstElementPtr unparsed6 = conf6.toElement();
    ASSERT_TRUE(unparsed6);
    ASSERT_EQ(Element::map, unparsed6->getType());

    // Get Dhcp6 entry
    ConstElementPtr dhcp6;
    ASSERT_NO_THROW(dhcp6 = unparsed6->get("Dhcp6"));
    ASSERT_TRUE(dhcp6);
    ASSERT_EQ(Element::map, dhcp6->getType());

    // Get global host reservations
    ASSERT_NO_THROW(check = dhcp6->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the global host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the host name
    ASSERT_NO_THROW(check = check->get("hostname"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("global.example.org", check->stringValue());

    // Get plain subnets
    ASSERT_NO_THROW(check = dhcp6->get("subnet6"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 1
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(p_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the host name
    ASSERT_NO_THROW(check = check->get("hostname"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("foo.example.org", check->stringValue());

    // Get shared networks
    ASSERT_NO_THROW(check = dhcp6->get("shared-networks"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared network
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its name is "frog"
    ASSERT_NO_THROW(sub = check->get("name"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::string, sub->getType());
    EXPECT_EQ("frog", sub->stringValue());

    // Get shared subnets
    ASSERT_NO_THROW(check = check->get("subnet6"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 100
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(s_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the host name
    ASSERT_NO_THROW(check = check->get("hostname"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("bar.example.org", check->stringValue());
}

// Verifies that the toElement method does not miss config control info
TEST_F(SrvConfigTest, unparseConfigControlInfo4) {
    // DHCPv4 version
    CfgMgr::instance().setFamily(AF_INET);
    SrvConfig conf4(32);

    // Unparse the config
    ConstElementPtr unparsed4 = conf4.toElement();
    ASSERT_TRUE(unparsed4);
    ASSERT_EQ(Element::map, unparsed4->getType());

    // Get Dhcp4 entry
    ConstElementPtr dhcp4;
    ASSERT_NO_THROW(dhcp4 = unparsed4->get("Dhcp4"));
    ASSERT_TRUE(dhcp4);
    ASSERT_EQ(Element::map, dhcp4->getType());

    // Config control should not be present.
    ConstElementPtr check;
    ASSERT_NO_THROW(check = dhcp4->get("config-control"));
    EXPECT_FALSE(check);

    // Now let's create the info and add it to the configuration
    ConfigControlInfoPtr info(new ConfigControlInfo());
    ASSERT_NO_THROW(info->addConfigDatabase("type=mysql"));
    ASSERT_NO_THROW(conf4.setConfigControlInfo(info));

    // Unparse the config again
    unparsed4 = conf4.toElement();
    ASSERT_NO_THROW(dhcp4 = unparsed4->get("Dhcp4"));
    ASSERT_TRUE(dhcp4);
    ASSERT_EQ(Element::map, dhcp4->getType());

    // Config control should be present.
    ASSERT_NO_THROW(check = dhcp4->get("config-control"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Unparse the info object and compare its elements to
    // that in unparsed config.  They should be equal.
    ElementPtr info_elem = info->toElement();
    EXPECT_TRUE(info_elem->equals(*check));
}

// Verifies that the toElement method does not miss config control info
TEST_F(SrvConfigTest, unparseConfigControlInfo6) {
    // DHCPv6 version
    CfgMgr::instance().setFamily(AF_INET6);
    SrvConfig conf6(32);

    // Unparse the config
    ConstElementPtr unparsed6 = conf6.toElement();
    ASSERT_TRUE(unparsed6);
    ASSERT_EQ(Element::map, unparsed6->getType());

    // Get Dhcp4 entry
    ConstElementPtr dhcp6;
    ASSERT_NO_THROW(dhcp6 = unparsed6->get("Dhcp6"));
    ASSERT_TRUE(dhcp6);
    ASSERT_EQ(Element::map, dhcp6->getType());

    // Config control should not be present.
    ConstElementPtr check;
    ASSERT_NO_THROW(check = dhcp6->get("config-control"));
    EXPECT_FALSE(check);

    // Now let's create the info and add it to the configuration
    ConfigControlInfoPtr info(new ConfigControlInfo());
    ASSERT_NO_THROW(info->addConfigDatabase("type=mysql"));
    ASSERT_NO_THROW(conf6.setConfigControlInfo(info));

    // Unparse the config again
    unparsed6 = conf6.toElement();
    ASSERT_NO_THROW(dhcp6 = unparsed6->get("Dhcp6"));
    ASSERT_TRUE(dhcp6);
    ASSERT_EQ(Element::map, dhcp6->getType());

    // Config control should be present.
    ASSERT_NO_THROW(check = dhcp6->get("config-control"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Unparse the info object and compare its elements to
    // that in unparsed config.  They should be equal.
    ElementPtr info_elem = info->toElement();
    EXPECT_TRUE(info_elem->equals(*check));
}

// Verifies that exception is thrown when instead of SrvConfig
// another derivation of ConfigBase is used in the call to
// merge.
TEST_F(SrvConfigTest, mergeBadCast) {
    SrvConfig srv_config;
    NonSrvConfig non_srv_config;
    ASSERT_THROW(srv_config.merge(non_srv_config), isc::InvalidOperation);
}

// This test verifies that globals from one SrvConfig
// can be merged into another. It verifies that values
// in the from-config override those in to-config which
// override those in GLOBAL4_DEFAULTS.
TEST_F(SrvConfigTest, mergeGlobals4) {
    // Set the family we're working with.
    CfgMgr::instance().setFamily(AF_INET);

    // Let's create the "existing" config we will merge into.
    SrvConfig cfg_to;

    // Set some explicit values. 
    cfg_to.setDeclinePeriod(100);
    cfg_to.setEchoClientId(false);
    cfg_to.setDhcp4o6Port(777);
    cfg_to.setServerTag("not_this_server");

    // Add some configured globals
    cfg_to.addConfiguredGlobal("decline-probation-period", Element::create(300));
    cfg_to.addConfiguredGlobal("dhcp4o6port", Element::create(888));

    // Now we'll create the config we'll merge from.
    SrvConfig cfg_from;

    // Set some explicit values. None of these should be preserved.
    cfg_from.setDeclinePeriod(200);
    cfg_from.setEchoClientId(true);
    cfg_from.setDhcp4o6Port(888);
    cfg_from.setServerTag("nor_this_server");

    // Add some configured globals:
    cfg_to.addConfiguredGlobal("dhcp4o6port", Element::create(999));
    cfg_to.addConfiguredGlobal("server-tag", Element::create("use_this_server"));

    // Now let's merge.
    ASSERT_NO_THROW(cfg_to.merge(cfg_from));

    // Make sure the explicit values are set correctly.

    // decline-probation-period should be the "to" configured value.
    EXPECT_EQ(300, cfg_to.getDeclinePeriod());

    // echo-client-id should be the preserved "to" member value.
    EXPECT_EQ(false, cfg_to.getEchoClientId());

    //  dhcp4o6port should be the "from" configured value.
    EXPECT_EQ(999, cfg_to.getDhcp4o6Port());

    //  server-tag port should be the "from" configured value.
    EXPECT_EQ("use_this_server", cfg_to.getServerTag().get());

    // Next we check the explicitly "configured" globals. 
    // The list should be all of the "to" + "from", with the
    // latter overwriting the former.
    std::string exp_globals =
        "{ \n"
        "   \"decline-probation-period\": 300,  \n"
        "   \"dhcp4o6port\": 999,  \n"
        "   \"server-tag\": \"use_this_server\"  \n"
        "} \n";

    ConstElementPtr expected_globals;
    ASSERT_NO_THROW(expected_globals = Element::fromJSON(exp_globals))
                    << "exp_globals didn't parse, test is broken";

    EXPECT_TRUE(isEquivalent(expected_globals, cfg_to.getConfiguredGlobals()));

}

} // end of anonymous namespace
