// Copyright (C) 2014-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option_def.h>
#include <testutils/test_to_element.h>
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
    cfg1.add(OptionDefinitionPtr(new OptionDefinition("option-foo", 5, "isc",
                                                      "uint16")));
    cfg2.add(OptionDefinitionPtr(new OptionDefinition("option-foo", 5, "dns",
                                                      "uint16")));
    // Configurations must be unequal.
    ASSERT_FALSE(cfg1 == cfg2);
    ASSERT_TRUE(cfg1 != cfg2);

    // Now, let's add them again but to original option spaces. Both objects
    // should now contain the same options under two option spaces. The
    // order should not matter so configurations should be equal.
    cfg1.add(OptionDefinitionPtr(new OptionDefinition("option-foo", 5, "dns",
                                                      "uint16")));
    cfg2.add(OptionDefinitionPtr(new OptionDefinition("option-foo", 5, "isc",
                                                      "uint16")));

    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);

}

// This test verifies that multiple option definitions can be added
// under different option spaces and then removed.
TEST(CfgOptionDefTest, getAllThenDelete) {
    CfgOptionDef cfg;

    // Create a set of option definitions with codes between 100 and 109.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream option_name;
        // Option name is unique, e.g. option-100, option-101 etc.
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "isc", "uint16"));
        // We're setting id of 123 for all option definitions in this
        // code range.
        def->setId(123);

        // Add option definition to "isc" option space.
        // Option codes are not duplicated so expect no error
        // when adding them.
        ASSERT_NO_THROW(cfg.add(def));
    }

    // Create a set of option definitions with codes between 105 and 114 and
    // add them to the different option space.
    for (uint16_t code = 105; code < 115; ++code) {
        std::ostringstream option_name;
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "abcde", "uint16"));
        // We're setting id of 234 for all option definitions in this
        // code range.
        def->setId(234);

        ASSERT_NO_THROW(cfg.add(def));
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

    // Check that we can delete option definitions by id.
    uint64_t num_deleted = 0;
    ASSERT_NO_THROW(num_deleted = cfg.del(123));
    EXPECT_EQ(10, num_deleted);

    option_defs1 = cfg.getAll("isc");
    ASSERT_TRUE(option_defs1);
    ASSERT_EQ(0, option_defs1->size());

    option_defs2 = cfg.getAll("abcde");
    ASSERT_TRUE(option_defs2);
    ASSERT_EQ(10, option_defs2->size());

    // Second attempt to delete the same option definitions should
    // result in 0 deletions.
    ASSERT_NO_THROW(num_deleted = cfg.del(123));
    EXPECT_EQ(0, num_deleted);

    // Delete all other option definitions.
    ASSERT_NO_THROW(num_deleted = cfg.del(234));
    EXPECT_EQ(10, num_deleted);

    option_defs2 = cfg.getAll("abcde");
    ASSERT_TRUE(option_defs2);
    ASSERT_EQ(0, option_defs2->size());
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
                                                     "isc", "uint16"));
        // Add option definition to "isc" option space.
        // Option codes are not duplicated so expect no error
        // when adding them.
        ASSERT_NO_THROW(cfg.add(def));
    }

    // Create a set of option definitions with codes between 105 and 114 and
    // add them to the different option space.
    for (uint16_t code = 105; code < 115; ++code) {
        std::ostringstream option_name;
        option_name << "option-other-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "abcde", "uint16"));
        ASSERT_NO_THROW(cfg.add(def));
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
    OptionDefinitionPtr def6(new OptionDefinition("option-foo", 1000,
                                                  DHCP6_OPTION_SPACE,
                                                  "uint16"));
    EXPECT_NO_THROW(cfg.add(def6));

    OptionDefinitionPtr def4(new OptionDefinition("option-foo", 222,
                                                  DHCP4_OPTION_SPACE,
                                                  "uint16"));
    EXPECT_NO_THROW(cfg.add(def4));

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
    def.reset(new OptionDefinition("routers", DHO_ROUTERS,
                                   DHCP4_OPTION_SPACE, "uint32"));
    EXPECT_THROW(cfg.add(def), isc::BadValue);

    // Check code duplicate (same code, different name).
    def.reset(new OptionDefinition("routers-bis", DHO_ROUTERS,
                                   DHCP4_OPTION_SPACE, "uint32"));
    EXPECT_THROW(cfg.add(def), isc::BadValue);

    // Check name duplicate (different code, same name).
    def.reset(new OptionDefinition("routers", 170, DHCP4_OPTION_SPACE,
                                   "uint32"));
    EXPECT_THROW(cfg.add(def), isc::BadValue);

    /// There is no definition for unassigned option 170.
    def.reset(new OptionDefinition("unassigned-option-170", 170,
                                   DHCP4_OPTION_SPACE, "string"));
    EXPECT_NO_THROW(cfg.add(def));

    // It is not allowed to override the definition of the option which
    // has its definition in the libdhcp++.
    def.reset(new OptionDefinition("sntp-servers", D6O_SNTP_SERVERS,
                                   DHCP6_OPTION_SPACE, "ipv4-address"));
    EXPECT_THROW(cfg.add(def), isc::BadValue);
    // There is no definition for option 163 in libdhcp++ yet, so it should
    // be possible provide a custom definition.
    def.reset(new OptionDefinition("geolocation", 163, DHCP6_OPTION_SPACE,
                                   "uint32"));
    EXPECT_NO_THROW(cfg.add(def));
}

// This test verifies that the function that adds new option definition
// throws exceptions when arguments are invalid.
TEST(CfgOptionDefTest, addNegative) {
    CfgOptionDef cfg;

    OptionDefinitionPtr def(new OptionDefinition("option-foo", 1000, "isc",
                                                 "uint16"));

    // Try NULL option definition.
    ASSERT_THROW(cfg.add(OptionDefinitionPtr()),
                 isc::dhcp::MalformedOptionDefinition);
    // Try adding option definition twice and make sure that it
    // fails on the second attempt.
    ASSERT_NO_THROW(cfg.add(def));
    EXPECT_THROW(cfg.add(def), DuplicateOptionDefinition);
}

// This test verifies that the function that unparses configuration
// works as expected.
TEST(CfgOptionDefTest, unparse) {
    CfgOptionDef cfg;

    // Add some options.
    cfg.add(OptionDefinitionPtr(new
        OptionDefinition("option-foo", 5, "isc", "uint16")));
    cfg.add(OptionDefinitionPtr(new
        OptionDefinition("option-bar", 5, "dns", "uint16", true)));
    cfg.add(OptionDefinitionPtr(new
        OptionDefinition("option-baz", 6, "isc", "uint16", "dns")));
    OptionDefinitionPtr rec(new OptionDefinition("option-rec", 6, "dns", "record"));
    std::string json = "{ \"comment\": \"foo\", \"bar\": 1 }";
    rec->setContext(data::Element::fromJSON(json));
    rec->addRecordField("uint16");
    rec->addRecordField("uint16");
    cfg.add(rec);

    // Unparse
    std::string expected = "[\n"
        "{\n"
        "    \"name\": \"option-bar\",\n"
        "    \"code\": 5,\n"
        "    \"type\": \"uint16\",\n"
        "    \"array\": true,\n"
        "    \"record-types\": \"\",\n"
        "    \"encapsulate\": \"\",\n"
        "    \"space\": \"dns\"\n"
        "},{\n"
        "    \"name\": \"option-rec\",\n"
        "    \"code\": 6,\n"
        "    \"type\": \"record\",\n"
        "    \"array\": false,\n"
        "    \"record-types\": \"uint16, uint16\",\n"
        "    \"encapsulate\": \"\",\n"
        "    \"space\": \"dns\",\n"
        "    \"user-context\": { \"comment\": \"foo\", \"bar\": 1 }\n"
        "},{\n"
        "    \"name\": \"option-foo\",\n"
        "    \"code\": 5,\n"
        "    \"type\": \"uint16\",\n"
        "    \"array\": false,\n"
        "    \"record-types\": \"\",\n"
        "    \"encapsulate\": \"\",\n"
        "    \"space\": \"isc\"\n"
        "},{\n"
        "    \"name\": \"option-baz\",\n"
        "    \"code\": 6,\n"
        "    \"type\": \"uint16\",\n"
        "    \"array\": false,\n"
        "    \"record-types\": \"\",\n"
        "    \"encapsulate\": \"dns\",\n"
        "    \"space\": \"isc\"\n"
        "}]\n";
    isc::test::runToElementTest<CfgOptionDef>(expected, cfg);
}

// This test verifies that configured option definitions can be merged
// correctly.
TEST(CfgOptionDefTest, merge) {
    CfgOptionDef to;         // Configuration we are merging to.

    // Add some options to the "to" config.
    to.add((OptionDefinitionPtr(new OptionDefinition("one", 1, "isc", "uint16"))));
    to.add((OptionDefinitionPtr(new OptionDefinition("two", 2, "isc", "uint16"))));
    to.add((OptionDefinitionPtr(new OptionDefinition("three", 3, "fluff", "uint16"))));
    to.add((OptionDefinitionPtr(new OptionDefinition("four", 4, "fluff", "uint16"))));

    // Clone the "to" config and use that for merging.
    CfgOptionDef to_clone;
    to.copyTo(to_clone);

    // Ensure they are equal before we do anything.
    ASSERT_TRUE(to.equals(to_clone));

    // Merge from an empty config.
    CfgOptionDef empty_from;
    ASSERT_NO_THROW(to_clone.merge(empty_from));

    // Should have the same content as before.
    ASSERT_TRUE(to.equals(to_clone));

    // Construct a non-empty "from" config.
    // Options "two" and "three" will be updated definitions and "five" will be new.
    CfgOptionDef from;
    from.add((OptionDefinitionPtr(new OptionDefinition("two", 22, "isc", "uint16"))));
    from.add((OptionDefinitionPtr(new OptionDefinition("three", 3, "fluff", "string"))));
    from.add((OptionDefinitionPtr(new OptionDefinition("five", 5, "fluff", "uint16"))));

    // Now let's clone "from" config and use that manually construct the expected config.
    CfgOptionDef expected;
    from.copyTo(expected);
    expected.add((OptionDefinitionPtr(new OptionDefinition("one", 1, "isc", "uint16"))));
    expected.add((OptionDefinitionPtr(new OptionDefinition("four", 4, "fluff", "uint16"))));

    // Do the merge.
    ASSERT_NO_THROW(to_clone.merge(from));

    // Verify we have the expected content.
    ASSERT_TRUE(expected.equals(to_clone));
}

}
