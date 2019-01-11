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
