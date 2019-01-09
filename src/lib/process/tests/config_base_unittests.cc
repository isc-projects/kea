// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <process/config_base.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::process;

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
