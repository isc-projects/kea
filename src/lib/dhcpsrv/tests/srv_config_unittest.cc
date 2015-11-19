// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet.h>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;

// Those are the tests for SrvConfig storage. Right now they are minimal,
// but the number is expected to grow significantly once we migrate more
// parameters from CfgMgr storage to SrvConfig storage.

namespace {

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
        for (int i = 0; i < TEST_SUBNETS_NUM; ++i) {
            // This is a base prefix. All other prefixes will be created by
            // modifying this one.
            IOAddress prefix("2001:db8:1::0");
            std::vector<uint8_t> prefix_bytes = prefix.toBytes();
            // Modify 5th byte of the prefix, so 2001:db8:1::0 becomes
            // 2001:db8:2::0 etc.
            ++prefix_bytes[5];
            prefix = IOAddress::fromBytes(prefix.getFamily(), &prefix_bytes[0]);
            Subnet6Ptr subnet(new Subnet6(prefix, 64, 1000, 2000, 3000, 4000));
            test_subnets6_.push_back(subnet);
        }

        // Build our reference dictionary of client classes
        ref_dictionary_->addClass("cc1", ExpressionPtr(), CfgOptionPtr());
        ref_dictionary_->addClass("cc2", ExpressionPtr(), CfgOptionPtr());
        ref_dictionary_->addClass("cc3", ExpressionPtr(), CfgOptionPtr());
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
    // D2 configuration should always be non-NULL.
    CfgMgr::instance().getD2ClientConfig()->enableUpdates(enable);
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
    conf1.getCfgOption()->add(option, true, "dhcp6");

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

} // end of anonymous namespace
