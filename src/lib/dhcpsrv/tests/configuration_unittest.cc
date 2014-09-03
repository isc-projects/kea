// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/configuration.h>
#include <dhcpsrv/subnet.h>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;

// Those are the tests for Configuration storage. Right now they are minimal,
// but the number is expected to grow significantly once we migrate more
// parameters from CfgMgr storage to Configuration storage.

namespace {

/// @brief Number of IPv4 and IPv6 subnets to be created for a test.
const int TEST_SUBNETS_NUM = 3;

/// @brief Test fixture class for testing configuration data storage.
class ConfigurationTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Creates IPv4 and IPv6 subnets for unit test. The number of subnets
    /// is @c TEST_SUBNETS_NUM for IPv4 and IPv6 each.
    ConfigurationTest()
        : iface_mgr_test_config_(true) {
        // Remove any subnets dangling from previous unit tests.
        clearSubnets();

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
    }

    /// @brief Destructor.
    ///
    /// Removes any dangling configuration.
    virtual ~ConfigurationTest() {
        clearSubnets();
    }

    /// @brief Convenience function which adds IPv4 subnet to the configuration.
    ///
    /// @param index Index of the subnet in the @c test_subnets4_ collection
    /// which should be added to the configuration. The configuration is stored
    /// in the @ conf_ member. This value must be lower than
    /// @c TEST_SUBNETS_NUM.
    ///
    /// @todo Until the subnets configuration is migrated from the @c CfgMgr to
    /// the @c Configuration object, this function adds the subnet to the
    /// @c CfgMgr. Once, the subnet configuration is held in the
    /// @c Configuration this function must be modified to store the subnets in
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
    /// the @c Configuration object, this function adds the subnet to the
    /// @c CfgMgr. Once, the subnet configuration is held in the
    /// @c Configuration this function must be modified to store the subnets in
    /// @c conf_ object.
    void addSubnet6(const unsigned int index);

    /// @brief Removes all subnets from the configuration.
    ///
    /// @todo Modify this function once the subnet configuration is migrated
    /// from @c CfgMgr to @c Configuration.
    void clearSubnets();

    /// @brief Enable/disable DDNS.
    ///
    /// @param enable A boolean value indicating if the DDNS should be
    /// enabled (true) or disabled (false).
    void enableDDNS(const bool enable);

    /// @brief Stores configuration.
    Configuration conf_;
    /// @brief A collection of IPv4 subnets used by unit tests.
    Subnet4Collection test_subnets4_;
    /// @brief A collection of IPv6 subnets used by unit tests.
    Subnet6Collection test_subnets6_;
    /// @brief Fakes interface configuration.
    isc::dhcp::test::IfaceMgrTestConfig iface_mgr_test_config_;

};

void
ConfigurationTest::addSubnet4(const unsigned int index) {
    if (index >= TEST_SUBNETS_NUM) {
        FAIL() << "Subnet index " << index << "out of range (0.."
               << TEST_SUBNETS_NUM << "): " << "unable to add IPv4 subnet";
    }
    CfgMgr::instance().addSubnet4(test_subnets4_[index]);
}

void
ConfigurationTest::addSubnet6(const unsigned int index) {
    if (index >= TEST_SUBNETS_NUM) {
        FAIL() << "Subnet index " << index << "out of range (0.."
               << TEST_SUBNETS_NUM << "): " << "unable to add IPv6 subnet";
    }
    CfgMgr::instance().addSubnet6(test_subnets6_[index]);
}

void
ConfigurationTest::clearSubnets() {
    CfgMgr::instance().deleteSubnets4();
    CfgMgr::instance().deleteSubnets6();
}

void
ConfigurationTest::enableDDNS(const bool enable) {
    // D2 configuration should always be non-NULL.
    CfgMgr::instance().getD2ClientConfig()->enableUpdates(enable);
}

// Check that by default there are no logging entries
TEST_F(ConfigurationTest, basic) {
    EXPECT_TRUE(conf_.getLoggingInfo().empty());
}

// Check that Configuration can store logging information.
TEST_F(ConfigurationTest, loggingInfo) {
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
TEST_F(ConfigurationTest, summaryDDNS) {
    EXPECT_EQ("DDNS: disabled",
              conf_.getConfigSummary(Configuration::CFGSEL_DDNS));

    enableDDNS(true);
    EXPECT_EQ("DDNS: enabled",
              conf_.getConfigSummary(Configuration::CFGSEL_DDNS));

    enableDDNS(false);
    EXPECT_EQ("no IPv4 subnets!; no IPv6 subnets!; DDNS: disabled",
              conf_.getConfigSummary(Configuration::CFGSEL_ALL));
}

// Check that the configuration summary including information about added
// subnets is returned.
TEST_F(ConfigurationTest, summarySubnets) {
    EXPECT_EQ("no config details available",
              conf_.getConfigSummary(Configuration::CFGSEL_NONE));

    // Initially, there are no subnets added but it should be explicitly
    // reported when we query for information about the subnets.
    EXPECT_EQ("no IPv4 subnets!; no IPv6 subnets!",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET));

    // If we just want information about IPv4 subnets, there should be no
    // mention of IPv6 subnets, even though there are none added.
    EXPECT_EQ("no IPv4 subnets!",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET4));

    // If we just want information about IPv6 subnets, there should be no
    // mention of IPv4 subnets, even though there are none added.
    EXPECT_EQ("no IPv6 subnets!",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET6));

    // Add IPv4 subnet and make sure it is reported.
    addSubnet4(0);
    EXPECT_EQ("added IPv4 subnets: 1",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET4));
    EXPECT_EQ("added IPv4 subnets: 1; no IPv6 subnets!",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET));

    // Add IPv6 subnet and make sure it is reported.
    addSubnet6(0);
    EXPECT_EQ("added IPv6 subnets: 1",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET6));
    EXPECT_EQ("added IPv4 subnets: 1; added IPv6 subnets: 1",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET));

    // Add one more subnet and make sure the bumped value is only
    // for IPv4, but not for IPv6.
    addSubnet4(1);
    EXPECT_EQ("added IPv4 subnets: 2; added IPv6 subnets: 1",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET));
    EXPECT_EQ("added IPv4 subnets: 2",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET4));

    addSubnet6(1);
    EXPECT_EQ("added IPv4 subnets: 2; added IPv6 subnets: 2",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET));

    // Remove all subnets and make sure that there are no reported subnets
    // back again.
    clearSubnets();
    EXPECT_EQ("no IPv4 subnets!; no IPv6 subnets!",
              conf_.getConfigSummary(Configuration::CFGSEL_SUBNET));
}

// This test checks if entire configuration can be copied and that the sequence
// number is not affected.
TEST_F(ConfigurationTest, copy) {
    // Create two configurations with different sequence numbers.
    Configuration conf1(32);
    Configuration conf2(64);

    // Set logging information for conf1.
    LoggingInfo info;
    info.name_ = "foo";
    info.severity_ = isc::log::DEBUG;
    info.debuglevel_ = 64;
    info.destinations_.push_back(LoggingDestination());

    // Set interface configuration for conf1.
    CfgIface cfg_iface;
    cfg_iface.use(CfgIface::V4, "eth0");

    conf1.addLoggingInfo(info);
    conf1.setCfgIface(cfg_iface);

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
TEST_F(ConfigurationTest, equality) {
    Configuration conf1(32);
    Configuration conf2(64);

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
    CfgIface cfg_iface1;
    CfgIface cfg_iface2;

    cfg_iface1.use(CfgIface::V4, "eth0");
    conf1.setCfgIface(cfg_iface1);

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    cfg_iface2.use(CfgIface::V4, "eth0");
    conf2.setCfgIface(cfg_iface2);

    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);
}

} // end of anonymous namespace
