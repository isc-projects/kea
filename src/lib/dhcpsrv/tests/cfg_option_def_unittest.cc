// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option_def.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

namespace {

// This test checks that two option definition configurations can be
// compared for equality.
TEST(CfgOptionDefTest, equal) {
    CfgOptionDef cfg1;
    CfgOptionDef cfg2;

    // Default objects must be equal.
    ASSERT_TRUE(cfg1 == cfg2);
    ASSERT_FALSE(cfg1 != cfg2);

    // Let's add the same option but to two different option spaces.
    cfg1.add(OptionDefinitionPtr(new OptionDefinition("option-foo",
                                                      5, "uint16")), "isc");
    cfg2.add(OptionDefinitionPtr(new OptionDefinition("option-foo",
                                                      5, "uint16")), "dns");
    // Configurations must be unequal.
    ASSERT_FALSE(cfg1 == cfg2);
    ASSERT_TRUE(cfg1 != cfg2);

    // Now, let's add them again but to original option spaces. Both objects
    // should now contain the same options under two option spaces. The
    // order should not matter so configurations should be equal.
    cfg1.add(OptionDefinitionPtr(new OptionDefinition("option-foo",
                                                      5, "uint16")), "dns");
    cfg2.add(OptionDefinitionPtr(new OptionDefinition("option-foo",
                                                      5, "uint16")), "isc");

    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);

}

// This test verifies that multiple option definitions can be added
// under different option spaces.
TEST(CfgOptionDefTest, getAll) {
    CfgOptionDef cfg;

    // Create a set of option definitions with codes between 100 and 109.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream option_name;
        // Option name is unique, e.g. option-100, option-101 etc.
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        // Add option definition to "isc" option space.
        // Option codes are not duplicated so expect no error
        // when adding them.
        ASSERT_NO_THROW(cfg.add(def, "isc"));
    }

    // Create a set of option definitions with codes between 105 and 114 and
    // add them to the different option space.
    for (uint16_t code = 105; code < 115; ++code) {
        std::ostringstream option_name;
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        ASSERT_NO_THROW(cfg.add(def, "abcde"));
    }

    // Sanity check that all 10 option definitions are there.
    OptionDefContainerPtr option_defs1 = cfg.getAll("isc");
    ASSERT_TRUE(option_defs1);
    ASSERT_EQ(10, option_defs1->size());

    // Iterate over all option definitions and check that they have
    // valid codes. Also, their order should be the same as they
    // were added (codes 100-109).
    uint16_t code = 100;
    for (OptionDefContainer::const_iterator it = option_defs1->begin();
         it != option_defs1->end(); ++it, ++code) {
        OptionDefinitionPtr def(*it);
        ASSERT_TRUE(def);
        EXPECT_EQ(code, def->getCode());
    }

    // Sanity check that all 10 option definitions are there.
    OptionDefContainerPtr option_defs2 = cfg.getAll("abcde");
    ASSERT_TRUE(option_defs2);
    ASSERT_EQ(10, option_defs2->size());

    // Check that the option codes are valid.
    code = 105;
    for (OptionDefContainer::const_iterator it = option_defs2->begin();
         it != option_defs2->end(); ++it, ++code) {
        OptionDefinitionPtr def(*it);
        ASSERT_TRUE(def);
        EXPECT_EQ(code, def->getCode());
    }

    // Let's make one more check that the empty set is returned when
    // invalid option space is used.
    OptionDefContainerPtr option_defs3 = cfg.getAll("non-existing");
    ASSERT_TRUE(option_defs3);
    EXPECT_TRUE(option_defs3->empty());
}

// This test verifies that single option definition is correctly
// returned with get function.
TEST(CfgOptionDefTest, get) {
    CfgOptionDef cfg;
    // Create a set of option definitions with codes between 100 and 109.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream option_name;
        // Option name is unique, e.g. option-100, option-101 etc.
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        // Add option definition to "isc" option space.
        // Option codes are not duplicated so expect no error
        // when adding them.
        ASSERT_NO_THROW(cfg.add(def, "isc"));
    }

    // Create a set of option definitions with codes between 105 and 114 and
    // add them to the different option space.
    for (uint16_t code = 105; code < 115; ++code) {
        std::ostringstream option_name;
        option_name << "option-other-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        ASSERT_NO_THROW(cfg.add(def, "abcde"));
    }

    // Try to get option definitions one by one using all codes
    // that we expect to be there.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionDefinitionPtr def = cfg.get("isc", code);
        ASSERT_TRUE(def);
        // Check that the option name is in the format of 'option-[code]'.
        // That way we make sure that the options that have the same codes
        // within different option spaces are different.
        std::ostringstream option_name;
        option_name << "option-" << code;
        EXPECT_EQ(option_name.str(), def->getName());
        EXPECT_EQ(code, def->getCode());

        // Try to get the same option definition using an option name as
        // a key.
        def = cfg.get("isc", option_name.str());
        ASSERT_TRUE(def);
        EXPECT_EQ(code, def->getCode());
    }

    // Check that the option codes are valid.
    for (uint16_t code = 105; code < 115; ++code) {
        OptionDefinitionPtr def = cfg.get("abcde", code);
        ASSERT_TRUE(def);
        // Check that the option name is in the format of 'option-other-[code]'.
        // That way we make sure that the options that have the same codes
        // within different option spaces are different.
        std::ostringstream option_name;
        option_name << "option-other-" << code;
        EXPECT_EQ(option_name.str(), def->getName());
        EXPECT_EQ(code, def->getCode());

        // Try to get the same option definition using an option name as
        // a key.
        def = cfg.get("abcde", option_name.str());
        ASSERT_TRUE(def);
        EXPECT_EQ(code, def->getCode());
    }

    // Check that an option definition can be added to the standard
    // (dhcp4 and dhcp6) option spaces when the option code is not
    // reserved by the standard option.
    OptionDefinitionPtr def6(new OptionDefinition("option-foo", 79, "uint16"));
    EXPECT_NO_THROW(cfg.add(def6, DHCP6_OPTION_SPACE));

    OptionDefinitionPtr def4(new OptionDefinition("option-foo", 222, "uint16"));
    EXPECT_NO_THROW(cfg.add(def4, DHCP4_OPTION_SPACE));

    // Try to query the option definition from an non-existing
    // option space and expect NULL pointer.
    OptionDefinitionPtr def = cfg.get("non-existing", 56);
    EXPECT_FALSE(def);

    // Try to get the non-existing option definition from an
    // existing option space.
    EXPECT_FALSE(cfg.get("isc", 56));
}

// This test verifies that it is not allowed to override a definition of the
// standard option which has its definition defined in libdhcp++, but it is
// allowed to create a definition for the standard option which doesn't have
// its definition in libdhcp++.
TEST(CfgOptionDefTest, overrideStdOptionDef) {
    CfgOptionDef cfg;
    OptionDefinitionPtr def;
    // There is a definition for routers option in libdhcp++, so an attempt
    // to add (override) another definition for this option should fail.
    def.reset(new OptionDefinition("routers", DHO_ROUTERS, "uint32"));
    EXPECT_THROW(cfg.add(def, DHCP4_OPTION_SPACE), isc::BadValue);

    /// @todo There is no definition for the NIS Server Addr option in
    /// libdhcp++. Once it is implemented it should be not allowed to
    /// add a custom definition for it. At the moment, it should be ok
    /// to add a definition for this option (using configuration mechanism)
    /// because we haven't implemented the one in libdhcp++.
    def.reset(new OptionDefinition("nis-server-addr", 65, "uint16"));
    EXPECT_NO_THROW(cfg.add(def, DHCP4_OPTION_SPACE));

    // It is not allowed to override the definition of the option which
    // has its definition in the libdhcp++.
    def.reset(new OptionDefinition("sntp-servers", D6O_SNTP_SERVERS,
                                   "ipv4-address"));
    EXPECT_THROW(cfg.add(def, DHCP6_OPTION_SPACE), isc::BadValue);
    // There is no definition for option 63 in libdhcp++ yet, so it should
    // be possible provide a custom definition.
    def.reset(new OptionDefinition("geolocation", 63, "uint32"));
    EXPECT_NO_THROW(cfg.add(def, DHCP6_OPTION_SPACE));
}

// This test verifies that the function that adds new option definition
// throws exceptions when arguments are invalid.
TEST(CfgOptionDefTest, addNegative) {
    CfgOptionDef cfg;

    OptionDefinitionPtr def(new OptionDefinition("option-foo", 1000, "uint16"));

    // Try empty option space name.
    ASSERT_THROW(cfg.add(def, ""), isc::BadValue);
    // Try NULL option definition.
    ASSERT_THROW(cfg.add(OptionDefinitionPtr(), "isc"),
                 isc::dhcp::MalformedOptionDefinition);
    // Try adding option definition twice and make sure that it
    // fails on the second attempt.
    ASSERT_NO_THROW(cfg.add(def, "isc"));
    EXPECT_THROW(cfg.add(def, "isc"), DuplicateOptionDefinition);
}

}
