// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcp/dhcp6.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <stats/stats_mgr.h>

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;
using namespace isc::stats;
using namespace isc;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

template <typename Storage>
bool isZeroPosition(const Storage& storage, const std::string& param_name) {
    Element::Position position = storage.getPosition(param_name);
    return ((position.line_ == 0) && (position.pos_ == 0) &&
            (position.file_.empty()));
}

// This test verifies that BooleanStorage functions properly.
TEST(ValueStorageTest, BooleanTesting) {
    BooleanStorage testStore;

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstBool", false, Element::Position("kea.conf", 123, 234));
    testStore.setParam("secondBool", true, Element::Position("keax.conf", 10, 20));

    EXPECT_FALSE(testStore.getParam("firstBool"));
    EXPECT_TRUE(testStore.getParam("secondBool"));

    EXPECT_EQ(123, testStore.getPosition("firstBool").line_);
    EXPECT_EQ(234, testStore.getPosition("firstBool").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstBool").file_);

    EXPECT_EQ(10, testStore.getPosition("secondBool").line_);
    EXPECT_EQ(20, testStore.getPosition("secondBool").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondBool").file_);

    // Verify that we can update parameters.
    testStore.setParam("firstBool", true, Element::Position("keax.conf", 555, 111));
    testStore.setParam("secondBool", false, Element::Position("kea.conf", 1, 3));

    EXPECT_TRUE(testStore.getParam("firstBool"));
    EXPECT_FALSE(testStore.getParam("secondBool"));

    EXPECT_EQ(555, testStore.getPosition("firstBool").line_);
    EXPECT_EQ(111, testStore.getPosition("firstBool").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("firstBool").file_);

    EXPECT_EQ(1, testStore.getPosition("secondBool").line_);
    EXPECT_EQ(3, testStore.getPosition("secondBool").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondBool").file_);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstBool");
    EXPECT_THROW(testStore.getParam("firstBool"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "firstBool"));

    // Verify that the delete was safe and the store still operates.
    EXPECT_FALSE(testStore.getParam("secondBool"));

    EXPECT_EQ(1, testStore.getPosition("secondBool").line_);
    EXPECT_EQ(3, testStore.getPosition("secondBool").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondBool").file_);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusBool"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "bogusBool"));

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusBool"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondBool"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "secondBool"));
}

// This test verifies that Uint32Storage functions properly.
TEST(ValueStorageTest, Uint32Testing) {
    Uint32Storage testStore;

    uint32_t int_one = 77;
    uint32_t int_two = 33;

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstInt", int_one, Element::Position("kea.conf", 123, 234));
    testStore.setParam("secondInt", int_two, Element::Position("keax.conf", 10, 20));

    EXPECT_EQ(testStore.getParam("firstInt"), int_one);
    EXPECT_EQ(testStore.getParam("secondInt"), int_two);

    EXPECT_EQ(123, testStore.getPosition("firstInt").line_);
    EXPECT_EQ(234, testStore.getPosition("firstInt").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstInt").file_);

    EXPECT_EQ(10, testStore.getPosition("secondInt").line_);
    EXPECT_EQ(20, testStore.getPosition("secondInt").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondInt").file_);

    // Verify that we can update parameters.
    testStore.setParam("firstInt", --int_one, Element::Position("keax.conf", 555, 111));
    testStore.setParam("secondInt", ++int_two, Element::Position("kea.conf", 1, 3));

    EXPECT_EQ(testStore.getParam("firstInt"), int_one);
    EXPECT_EQ(testStore.getParam("secondInt"), int_two);

    EXPECT_EQ(555, testStore.getPosition("firstInt").line_);
    EXPECT_EQ(111, testStore.getPosition("firstInt").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("firstInt").file_);

    EXPECT_EQ(1, testStore.getPosition("secondInt").line_);
    EXPECT_EQ(3, testStore.getPosition("secondInt").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondInt").file_);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstInt");
    EXPECT_THROW(testStore.getParam("firstInt"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "firstInt"));

    // Verify that the delete was safe and the store still operates.
    EXPECT_EQ(testStore.getParam("secondInt"), int_two);

    EXPECT_EQ(1, testStore.getPosition("secondInt").line_);
    EXPECT_EQ(3, testStore.getPosition("secondInt").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondInt").file_);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusInt"), isc::dhcp::DhcpConfigError);

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusInt"));

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "bogusInt"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondInt"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "secondInt"));
}

// This test verifies that StringStorage functions properly.
TEST(ValueStorageTest, StringTesting) {
    StringStorage testStore;

    std::string string_one = "seventy-seven";
    std::string string_two = "thirty-three";

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstString", string_one,
                       Element::Position("kea.conf", 123, 234));
    testStore.setParam("secondString", string_two,
                       Element::Position("keax.conf", 10, 20));

    EXPECT_EQ(testStore.getParam("firstString"), string_one);
    EXPECT_EQ(testStore.getParam("secondString"), string_two);

    EXPECT_EQ(123, testStore.getPosition("firstString").line_);
    EXPECT_EQ(234, testStore.getPosition("firstString").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstString").file_);

    EXPECT_EQ(10, testStore.getPosition("secondString").line_);
    EXPECT_EQ(20, testStore.getPosition("secondString").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondString").file_);

    // Verify that we can update parameters.
    string_one.append("-boo");
    string_two.append("-boo");

    testStore.setParam("firstString", string_one,
                       Element::Position("kea.conf", 555, 111));
    testStore.setParam("secondString", string_two,
                       Element::Position("keax.conf", 1, 3));

    EXPECT_EQ(testStore.getParam("firstString"), string_one);
    EXPECT_EQ(testStore.getParam("secondString"), string_two);

    EXPECT_EQ(555, testStore.getPosition("firstString").line_);
    EXPECT_EQ(111, testStore.getPosition("firstString").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstString").file_);

    EXPECT_EQ(1, testStore.getPosition("secondString").line_);
    EXPECT_EQ(3, testStore.getPosition("secondString").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondString").file_);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstString");
    EXPECT_THROW(testStore.getParam("firstString"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "firstString"));

    // Verify that the delete was safe and the store still operates.
    EXPECT_EQ(testStore.getParam("secondString"), string_two);

    EXPECT_EQ(1, testStore.getPosition("secondString").line_);
    EXPECT_EQ(3, testStore.getPosition("secondString").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondString").file_);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusString"), isc::dhcp::DhcpConfigError);

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusString"));

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "bogusString"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondString"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "secondString"));
}



class CfgMgrTest : public ::testing::Test {
public:
    CfgMgrTest() {
        // make sure we start with a clean configuration
        clear();
    }

    /// @brief generates interface-id option based on provided text
    ///
    /// @param text content of the option to be created
    ///
    /// @return pointer to the option object created
    OptionPtr generateInterfaceId(const string& text) {
        OptionBuffer buffer(text.begin(), text.end());
        return OptionPtr(new Option(Option::V6, D6O_INTERFACE_ID, buffer));
    }

    ~CfgMgrTest() {
        // clean up after the test
        clear();
    }

    void clear() {
        CfgMgr::instance().setVerbose(false);
        CfgMgr::instance().clear();
    }

    /// used in client classification (or just empty container for other tests)
    isc::dhcp::ClientClasses classify_;
};

// Checks that there is a configuration structure available and that
// it is empty by default.
TEST_F(CfgMgrTest, configuration) {

    ConstSrvConfigPtr configuration = CfgMgr::instance().getCurrentCfg();
    ASSERT_TRUE(configuration);
    EXPECT_TRUE(configuration->getLoggingInfo().empty());

    configuration = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(configuration);
    EXPECT_TRUE(configuration->getLoggingInfo().empty());
}

// This test verifies that new DHCPv4 option spaces can be added to
// the configuration manager and that duplicated option space is
// rejected.
TEST_F(CfgMgrTest, optionSpace4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Create some option spaces.
    OptionSpacePtr space1(new OptionSpace("isc", false));
    OptionSpacePtr space2(new OptionSpace("xyz", true));

    // Add option spaces with different names and expect they
    // are accepted.
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace4(space1));
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace4(space2));

    // Validate that the option spaces have been added correctly.
    const OptionSpaceCollection& spaces = cfg_mgr.getOptionSpaces4();

    ASSERT_EQ(2, spaces.size());
    EXPECT_FALSE(spaces.find("isc") == spaces.end());
    EXPECT_FALSE(spaces.find("xyz") == spaces.end());

    // Create another option space with the name that duplicates
    // the existing option space.
    OptionSpacePtr space3(new OptionSpace("isc", true));
    // Expect that the duplicate option space is rejected.
    ASSERT_THROW(
        cfg_mgr.addOptionSpace4(space3), isc::dhcp::InvalidOptionSpace
    );

    /// @todo decode if a duplicate vendor space is allowed.
}

// This test verifies that new DHCPv6 option spaces can be added to
// the configuration manager and that duplicated option space is
// rejected.
TEST_F(CfgMgrTest, optionSpace6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Create some option spaces.
    OptionSpacePtr space1(new OptionSpace("isc", false));
    OptionSpacePtr space2(new OptionSpace("xyz", true));

    // Add option spaces with different names and expect they
    // are accepted.
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace6(space1));
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace6(space2));

    // Validate that the option spaces have been added correctly.
    const OptionSpaceCollection& spaces = cfg_mgr.getOptionSpaces6();

    ASSERT_EQ(2, spaces.size());
    EXPECT_FALSE(spaces.find("isc") == spaces.end());
    EXPECT_FALSE(spaces.find("xyz") == spaces.end());

    // Create another option space with the name that duplicates
    // the existing option space.
    OptionSpacePtr space3(new OptionSpace("isc", true));
    // Expect that the duplicate option space is rejected.
    ASSERT_THROW(
        cfg_mgr.addOptionSpace6(space3), isc::dhcp::InvalidOptionSpace
    );

    /// @todo decide if a duplicate vendor space is allowed.
}

// This test verifies that RFC6842 (echo client-id) compatibility may be
// configured.
TEST_F(CfgMgrTest, echoClientId) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Check that the default is true
    EXPECT_TRUE(cfg_mgr.echoClientId());

    // Check that it can be modified to false
    cfg_mgr.echoClientId(false);
    EXPECT_FALSE(cfg_mgr.echoClientId());

    // Check that the default value can be restored
    cfg_mgr.echoClientId(true);
    EXPECT_TRUE(cfg_mgr.echoClientId());
}

// This test checks the D2ClientMgr wrapper methods.
TEST_F(CfgMgrTest, d2ClientConfig) {
    // After CfgMgr construction, D2ClientMgr member should be initialized
    // with a D2 configuration that is disabled.
    // Verify we can Fetch the mgr.
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    EXPECT_FALSE(d2_mgr.ddnsEnabled());

    // Make sure the convenience method fetches the config correctly.
    D2ClientConfigPtr original_config = CfgMgr::instance().getD2ClientConfig();
    ASSERT_TRUE(original_config);
    EXPECT_FALSE(original_config->getEnableUpdates());

    // Verify that we cannot set the configuration to an empty pointer.
    D2ClientConfigPtr new_cfg;
    ASSERT_THROW(CfgMgr::instance().setD2ClientConfig(new_cfg), D2ClientError);

    // Create a new, enabled configuration.
    ASSERT_NO_THROW(new_cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  true, true, true, true,
                                  "pre-fix", "suf-fix")));

    // Verify that we can assign a new, non-empty configuration.
    ASSERT_NO_THROW(CfgMgr::instance().setD2ClientConfig(new_cfg));

    // Verify that we can fetch the newly assigned configuration.
    D2ClientConfigPtr updated_config = CfgMgr::instance().getD2ClientConfig();
    ASSERT_TRUE(updated_config);
    EXPECT_TRUE(updated_config->getEnableUpdates());

    // Make sure convenience method agrees with updated configuration.
    EXPECT_TRUE(CfgMgr::instance().ddnsEnabled());

    // Make sure the configuration we fetched is the one we assigned,
    // and not the original configuration.
    EXPECT_EQ(*new_cfg, *updated_config);
    EXPECT_NE(*original_config, *updated_config);
}

// This test verifies that the configuration staging, commit and rollback works
// as expected.
TEST_F(CfgMgrTest, staging) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Initially, the current configuration is a default one. We are going
    // to get the current configuration a couple of times and make sure
    // that always the same instance is returned.
    ConstSrvConfigPtr const_config;
    for (int i = 0; i < 5; ++i) {
        const_config = cfg_mgr.getCurrentCfg();
        ASSERT_TRUE(const_config) << "Returned NULL current configuration"
            " for iteration " << i;
        EXPECT_EQ(0, const_config->getSequence())
            << "Returned invalid sequence number "
            << const_config->getSequence() << " for iteration " << i;
    }

    // Try to get the new staging configuration. When getStagingCfg() is called
    // for the first time the new instance of the staging configuration is
    // returned. This instance is returned for every call to getStagingCfg()
    // until commit is called.
    SrvConfigPtr config;
    for (int i = 0; i < 5; ++i) {
        config = cfg_mgr.getStagingCfg();
        ASSERT_TRUE(config) << "Returned NULL staging configuration for"
            " iteration " << i;
        // The sequence id is 1 for staging because it is ahead of current
        // configuration having sequence number 0.
        EXPECT_EQ(1, config->getSequence()) << "Returned invalid sequence"
            " number " << config->getSequence() << " for iteration " << i;
    }

    // This should change the staging configuration so as it becomes a current
    // one.
    cfg_mgr.commit();
    const_config = cfg_mgr.getCurrentCfg();
    ASSERT_TRUE(const_config);
    // Sequence id equal to 1 indicates that the current configuration points
    // to the configuration that used to be a staging configuration previously.
    EXPECT_EQ(1, const_config->getSequence());

    // Create a new staging configuration. It should be assigned a new
    // sequence id.
    config = cfg_mgr.getStagingCfg();
    ASSERT_TRUE(config);
    EXPECT_EQ(2, config->getSequence());

    // Let's execute commit a couple of times. The first invocation to commit
    // changes the configuration having sequence 2 to current configuration.
    // Other commits are no-op.
    for (int i = 0; i < 5; ++i) {
        cfg_mgr.commit();
    }

    // The current configuration now have sequence number 2.
    const_config = cfg_mgr.getCurrentCfg();
    ASSERT_TRUE(const_config);
    EXPECT_EQ(2, const_config->getSequence());

    // Clear configuration along with a history.
    cfg_mgr.clear();

    // After clearing configuration we should successfully get the
    // new staging configuration.
    config = cfg_mgr.getStagingCfg();
    ASSERT_TRUE(config);
    EXPECT_EQ(1, config->getSequence());

    // Modify the staging configuration.
    config->addLoggingInfo(LoggingInfo());
    ASSERT_TRUE(config);
    // The modified staging configuration should have one logger configured.
    ASSERT_EQ(1, config->getLoggingInfo().size());

    // Rollback should remove a staging configuration, including the logger.
    ASSERT_NO_THROW(cfg_mgr.rollback());

    // Make sure that the logger is not set. This is an indication that the
    // rollback worked.
    config = cfg_mgr.getStagingCfg();
    ASSERT_TRUE(config);
    EXPECT_EQ(0, config->getLoggingInfo().size());
}

// This test verifies that it is possible to revert to an old configuration.
TEST_F(CfgMgrTest, revert) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Let's create 5 unique configurations: differing by a debug level in the
    // range of 10 to 14.
    for (int i = 0; i < 5; ++i) {
        SrvConfigPtr config = cfg_mgr.getStagingCfg();
        LoggingInfo logging_info;
        logging_info.debuglevel_ = i + 10;
        config->addLoggingInfo(logging_info);
        cfg_mgr.commit();
    }

    // Now we have 6 configurations with:
    // - debuglevel = 99 (a default one)
    // - debuglevel = 10
    // - debuglevel = 11
    // - debuglevel = 12
    // - debuglevel = 13
    // - debuglevel = 14 (current)

    // Hence, the maximum index of the configuration to revert is 5 (which
    // points to the configuration with debuglevel = 99). For the index greater
    // than 5 we should get an exception.
    ASSERT_THROW(cfg_mgr.revert(6), isc::OutOfRange);
    // Value of 0 also doesn't make sense.
    ASSERT_THROW(cfg_mgr.revert(0), isc::OutOfRange);

    // We should be able to revert to configuration with debuglevel = 10.
    ASSERT_NO_THROW(cfg_mgr.revert(4));
    // And this configuration should be now the current one and the debuglevel
    // of this configuration is 10.
    EXPECT_EQ(10, cfg_mgr.getCurrentCfg()->getLoggingInfo()[0].debuglevel_);
    EXPECT_NE(cfg_mgr.getCurrentCfg()->getSequence(), 1);

    // The new set of configuration is now as follows:
    // - debuglevel = 99
    // - debuglevel = 10
    // - debuglevel = 11
    // - debuglevel = 12
    // - debuglevel = 13
    // - debuglevel = 14
    // - debuglevel = 10 (current)
    // So, reverting to configuration having index 3 means that the debug level
    // of the current configuration will become 12.
    ASSERT_NO_THROW(cfg_mgr.revert(3));
    EXPECT_EQ(12, cfg_mgr.getCurrentCfg()->getLoggingInfo()[0].debuglevel_);
}

// This test verifies that the verbosity can be set and obtained from the
// configuration manager.
TEST_F(CfgMgrTest, verbosity) {
    ASSERT_FALSE(CfgMgr::instance().isVerbose());

    CfgMgr::instance().setVerbose(true);
    ASSERT_TRUE(CfgMgr::instance().isVerbose());

    CfgMgr::instance().setVerbose(false);
    EXPECT_FALSE(CfgMgr::instance().isVerbose());
}

// This test verifies that once the configuration is committed, statistics
// are updated appropriately.
TEST_F(CfgMgrTest, commitStats4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    StatsMgr& stats_mgr = StatsMgr::instance();

    // Let's prepare the "old" configuration: a subnet with id 123
    // and pretend there were addresses assigned, so statistics are non-zero.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.1.2.0"), 24, 1, 2, 3, 123));
    CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();
    subnets->add(subnet1);
    cfg_mgr.commit();
    stats_mgr.addValue("subnet[123].total-addresses", static_cast<int64_t>(256));
    stats_mgr.setValue("subnet[123].assigned-addresses", static_cast<int64_t>(150));

    // Now, let's change the configuration to something new.

    // There's a subnet 192.1.2.0/24 with ID=42
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.1.2.0"), 24, 1, 2, 3, 42));

    // Let's make a pool with 128 addresses available.
    PoolPtr pool(new Pool4(IOAddress("192.1.2.0"), 25)); // 128 addrs
    subnet2->addPool(pool);

    subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();
    subnets->add(subnet2);

    // Let's commit it
    cfg_mgr.commit();

    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].total-addresses"));
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].assigned-addresses"));

    ObservationPtr total_addrs;
    EXPECT_NO_THROW(total_addrs = stats_mgr.getObservation("subnet[42].total-addresses"));
    ASSERT_TRUE(total_addrs);
    EXPECT_EQ(128, total_addrs->getInteger().first);
}

// This test verifies that once the configuration is cleared, the statistics
// are removed.
TEST_F(CfgMgrTest, clearStats4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    StatsMgr& stats_mgr = StatsMgr::instance();

    // Let's prepare the "old" configuration: a subnet with id 123
    // and pretend there were addresses assigned, so statistics are non-zero.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.1.2.0"), 24, 1, 2, 3, 123));
    CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();
    subnets->add(subnet1);
    cfg_mgr.commit();
    stats_mgr.addValue("subnet[123].total-addresses", static_cast<int64_t>(256));
    stats_mgr.setValue("subnet[123].assigned-addresses", static_cast<int64_t>(150));

    // The stats should be there.
    EXPECT_TRUE(stats_mgr.getObservation("subnet[123].total-addresses"));
    EXPECT_TRUE(stats_mgr.getObservation("subnet[123].assigned-addresses"));

    // Let's remove all configurations
    cfg_mgr.clear();

    // The stats should not be there anymore.
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].total-addresses"));
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].assigned-addresses"));
}

// This test verifies that once the configuration is committed, statistics
// are updated appropriately.
TEST_F(CfgMgrTest, commitStats6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    StatsMgr& stats_mgr = StatsMgr::instance();

    // Let's prepare the "old" configuration: a subnet with id 123
    // and pretend there were addresses assigned, so statistics are non-zero.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4, 123));
    CfgSubnets6Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();
    subnets->add(subnet1);
    cfg_mgr.commit();
    stats_mgr.addValue("subnet[123].total-nas", static_cast<int64_t>(256));
    stats_mgr.setValue("subnet[123].assigned-nas", static_cast<int64_t>(150));

    stats_mgr.addValue("subnet[123].total-pds", static_cast<int64_t>(256));
    stats_mgr.setValue("subnet[123].assigned-pds", static_cast<int64_t>(150));

    // Now, let's change the configuration to something new.

    // There's a subnet 2001:db8:2::/48 with ID=42
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4, 42));

    // Let's make pools with 128 addresses and 65536 prefixes available.
    PoolPtr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:2::"), 121)); // 128 addrs
    PoolPtr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:3::"), 96, 112)); // 65536 prefixes
    subnet2->addPool(pool1);
    subnet2->addPool(pool2);

    subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();
    subnets->add(subnet2);

    // Let's commit it
    cfg_mgr.commit();

    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].total-nas"));
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].assigned-nas"));

    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].total-pds"));
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].assigned-pds"));

    ObservationPtr total_addrs;
    EXPECT_NO_THROW(total_addrs = stats_mgr.getObservation("subnet[42].total-nas"));
    ASSERT_TRUE(total_addrs);
    EXPECT_EQ(128, total_addrs->getInteger().first);

    EXPECT_NO_THROW(total_addrs = stats_mgr.getObservation("subnet[42].total-pds"));
    ASSERT_TRUE(total_addrs);
    EXPECT_EQ(65536, total_addrs->getInteger().first);
}

// This test verifies that once the configuration is cleared, the v6 statistics
// are removed.
TEST_F(CfgMgrTest, clearStats6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    StatsMgr& stats_mgr = StatsMgr::instance();

    // Let's prepare the "old" configuration: a subnet with id 123
    // and pretend there were addresses assigned, so statistics are non-zero.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4, 123));
    CfgSubnets6Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();
    subnets->add(subnet1);
    cfg_mgr.commit();
    stats_mgr.addValue("subnet[123].total-nas", static_cast<int64_t>(256));
    stats_mgr.setValue("subnet[123].assigned-nas", static_cast<int64_t>(150));

    stats_mgr.addValue("subnet[123].total-pds", static_cast<int64_t>(256));
    stats_mgr.setValue("subnet[123].assigned-pds", static_cast<int64_t>(150));

    // The stats should be there.
    EXPECT_TRUE(stats_mgr.getObservation("subnet[123].total-nas"));
    EXPECT_TRUE(stats_mgr.getObservation("subnet[123].assigned-nas"));

    EXPECT_TRUE(stats_mgr.getObservation("subnet[123].total-pds"));
    EXPECT_TRUE(stats_mgr.getObservation("subnet[123].assigned-pds"));

    // Let's remove all configurations
    cfg_mgr.clear();

    // The stats should not be there anymore.
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].total-nas"));
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].assigned-nas"));

    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].total-pds"));
    EXPECT_FALSE(stats_mgr.getObservation("subnet[123].assigned-pds"));
}

/// @todo Add unit-tests for testing:
/// - addActiveIface() with invalid interface name
/// - addActiveIface() with the same interface twice
/// - addActiveIface() with a bogus address
///
/// This is somewhat tricky. Care should be taken here, because it is rather
/// difficult to decide if interface name is valid or not. Some servers, e.g.
/// dibbler, allow to specify interface names that are not currently present in
/// the system. The server accepts them, but upon discovering that they are
/// yet available (for different definitions of not being available), adds
/// the to to-be-activated list.
///
/// Cases covered by dibbler are:
/// - missing interface (e.g. PPP connection that is not established yet)
/// - downed interface (no link local address, no way to open sockets)
/// - up, but not running interface (wifi up, but not associated)
/// - tentative addresses (interface up and running, but DAD procedure is
///   still in progress)
/// - weird interfaces without link-local addresses (don't ask, 6rd tunnels
///   look weird to me as well)

// No specific tests for getSubnet6. That method (2 overloaded versions) is tested
// in Dhcpv6SrvTest.selectSubnetAddr and Dhcpv6SrvTest.selectSubnetIface
// (see src/bin/dhcp6/tests/dhcp6_srv_unittest.cc)

} // end of anonymous namespace
