// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <process/config_base.h>
#include <util/optional.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::process;
using namespace isc::util;

/// @brief Derived ConfigBase class
/// We use this derivation to test the
/// copy and equality functions.
class ConfigBaseImpl : public ConfigBase {
public:
    void
    copy(ConfigBaseImpl& other) const {
        ConfigBase::copy(other);
    }
};

// Verifies construction, copy, and equality of
// ConfigBase with respect to ConfigControInfo.
TEST(ConfigBase, configControlInfoTests) {

    // Create a control info instance
    ConfigControlInfoPtr ctl_info1(new ConfigControlInfo());
    ctl_info1->addConfigDatabase("type=mysql host=example.com");
    ctl_info1->addConfigDatabase("type=mysql host=example2.com");

    // Create a ConfigBase
    ConfigBaseImpl base1;
    base1.setConfigControlInfo(ctl_info1);

    // Clone the ConfigBase
    ConfigBaseImpl base2;
    base1.copy(base2);

    // They should be equal.
    EXPECT_TRUE(base1.equals(base2));

    // Reset control info for one of them.
    base1.setConfigControlInfo(ConfigControlInfoPtr());

    // They should not be equal.
    EXPECT_FALSE(base1.equals(base2));

    // Reset control info for the other one.
    base2.setConfigControlInfo(ConfigControlInfoPtr());

    // They should be equal again.
    EXPECT_TRUE(base1.equals(base2));
}

// Verifies that logging information can be merged to another.
TEST(ConfigBase, mergeLoggingInfo) {
    // Create first logging info.
    LoggingInfo log_info1;
    log_info1.name_ = "foo";

    // Create second logging info.
    LoggingInfo log_info2;
    log_info2.name_ = "bar";

    // Create first config base instance.
    ConfigBaseImpl base1;
    base1.addLoggingInfo(log_info1);

    // Copy the first instance to keep it as reference.
    ConfigBaseImpl base1_copy;
    base1_copy.copy(base1);

    // Create second config base instance.
    ConfigBaseImpl base2;
    ASSERT_NO_THROW(base1.merge(base2));
    EXPECT_TRUE(base1.equals(base1_copy));

    // Set some data for the second config.
    base2.addLoggingInfo(log_info2);

    // This time the merge should replace the original config.
    ASSERT_NO_THROW(base1.merge(base2));
    EXPECT_TRUE(base1.equals(base2));
}

// Verifies that config control can be merged to another.
TEST(ConfigBase, mergeConfigControl) {
    // Create first config control info.
    ConfigControlInfoPtr ctl_info1(new ConfigControlInfo());
    ctl_info1->addConfigDatabase("type=mysql host=example.com");
    ctl_info1->addConfigDatabase("type=mysql host=example2.com");

    // Create second config control info.
    ConfigControlInfoPtr ctl_info2(new ConfigControlInfo());
    ctl_info2->addConfigDatabase("type=pgsql host=example.com");
    ctl_info2->addConfigDatabase("type=pgsql host=example2.com");

    // Create first config base instance.
    ConfigBaseImpl base1;
    base1.setConfigControlInfo(ctl_info1);

    // Copy the first instance to keep it as reference.
    ConfigBaseImpl base1_copy;
    base1_copy.copy(base1);

    // Create second config base instance.
    ConfigBaseImpl base2;

    // Merged base is empty, so the original should be preserved.
    ASSERT_NO_THROW(base1.merge(base2));
    EXPECT_TRUE(base1.equals(base1_copy));

    // Set some data for the second config.
    base2.setConfigControlInfo(ctl_info2);

    // This time the merge should replace the original config.
    ASSERT_NO_THROW(base1.merge(base2));
    EXPECT_TRUE(base1.equals(base2));
}

// Verifies that server-tag may be configured.
TEST(ConfigBase, serverTag) {
    ConfigBaseImpl conf;

    // Check that the default is an unspecified and empty string.
    EXPECT_TRUE(conf.getServerTag().unspecified());
    EXPECT_TRUE(conf.getServerTag().empty());

    // Check that it can be modified.
    conf.setServerTag("boo");
    EXPECT_FALSE(conf.getServerTag().unspecified());
    EXPECT_EQ("boo", conf.getServerTag().get());
}

// Verifies that server tag can be merged to another config.
TEST(ConfigBase, mergeServerTag) {
    ConfigBaseImpl base1;
    ConfigBaseImpl base2;

    // Initially the server tags in both config should be
    // unspecified.
    EXPECT_TRUE(base1.getServerTag().unspecified());
    EXPECT_TRUE(base2.getServerTag().unspecified());

    // Merging the config with unspecified server tag should
    // not modify the target config.
    ASSERT_NO_THROW(base1.merge(base2));
    EXPECT_TRUE(base1.getServerTag().unspecified());
    EXPECT_TRUE(base2.getServerTag().unspecified());

    // Set server tag for base2 and merge it.
    base2.setServerTag(std::string("base2"));
    ASSERT_NO_THROW(base1.merge(base2));

    // The server tag should be copied into the base1. Both
    // should now be unspecified.
    EXPECT_FALSE(base1.getServerTag().unspecified());
    EXPECT_FALSE(base2.getServerTag().unspecified());

    // They should also hold the same value.
    EXPECT_EQ("base2", base1.getServerTag().get());
    EXPECT_EQ("base2", base2.getServerTag().get());

    // Reset the server tag to unspecified.
    base2.setServerTag(Optional<std::string>());
    EXPECT_FALSE(base1.getServerTag().unspecified());
    EXPECT_TRUE(base2.getServerTag().unspecified());

    // Merging the config with unspecified server tag should
    // result in no change in the target config.
    ASSERT_NO_THROW(base1.merge(base2));
    EXPECT_FALSE(base1.getServerTag().unspecified());
    EXPECT_TRUE(base2.getServerTag().unspecified());

    // The server tag should remain the same.
    EXPECT_EQ("base2", base1.getServerTag().get());

    // Set the explicit server tag in the source config.
    base2.setServerTag("new-base2");

    // Merge again.
    ASSERT_NO_THROW(base1.merge(base2));

    // The new value should be stored in the target config, so
    // both should be specified and have the same value.
    EXPECT_FALSE(base1.getServerTag().unspecified());
    EXPECT_FALSE(base2.getServerTag().unspecified());
    EXPECT_EQ("new-base2", base1.getServerTag().get());
    EXPECT_EQ("new-base2", base2.getServerTag().get());
}

// Verifies that server tag can be copied to another config.
TEST(ConfigBase, copyServerTag) {
    ConfigBaseImpl base1;
    ConfigBaseImpl base2;

    // Set server tag for the base2.
    base2.setServerTag(std::string("base2"));

    // The base1 has server tag unspecified. Copying it to the
    // base2 should result in unspecified server tag in base2.
    ASSERT_NO_THROW(base1.copy(base2));
    EXPECT_TRUE(base2.getServerTag().unspecified());

    // Set server tag for base1 and copy it to base2.
    base1.setServerTag(std::string("base1"));
    ASSERT_NO_THROW(base1.copy(base2));

    // The base2 should now hold the value from base1.
    EXPECT_FALSE(base2.getServerTag().unspecified());
    EXPECT_EQ("base1", base2.getServerTag().get());

    // Set base1 value to a different value.
    base1.setServerTag(std::string("new-base1"));

    // Copy again.
    ASSERT_NO_THROW(base1.copy(base2));

    // It should override the value in the base2.
    EXPECT_FALSE(base2.getServerTag().unspecified());
    EXPECT_EQ("new-base1", base2.getServerTag().get());
}
