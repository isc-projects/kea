// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_space.h>
#include <dhcp/option_string.h>
#include <dhcp/option4_addrlst.h>
#include <dhcpsrv/cfg_option.h>
#include <testutils/test_to_element.h>
#include <boost/foreach.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include <limits>
#include <list>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// This class fixture for testing @c CfgOption class, holding option
/// configuration.
class CfgOptionTest : public ::testing::Test {
public:

    /// @brief Generates encapsulated options and adds them to CfgOption
    ///
    /// This method generates the following options:
    /// - 1000-1019 options: uint16 with value 1234, encapsulate "foo"
    ///   - 1-19 options: uint8 with value 1, encapsulate "foo-subs"
    ///     - 1-9 options: uint8 with value 3
    /// - 1020-1039 options: uint16 with value 2345, encapsulate "bar"
    ///   - 100-119 options: uint8 with value 2, encapsulate "bar-subs"
    ///     - 501-509 options: uint8 with value 4
    void generateEncapsulatedOptions(CfgOption& cfg) {
        // Create top-level options encapsulating "foo" option space.
        for (uint16_t code = 1000; code < 1020; ++code) {
            OptionUint16Ptr option = OptionUint16Ptr(new OptionUint16(Option::V6,
                                                                      code, 1234));
            option->setEncapsulatedSpace("foo");
            ASSERT_NO_THROW(cfg.add(option, false, DHCP6_OPTION_SPACE));
        }

        // Create top level options encapsulating "bar" option space.
        for (uint16_t code = 1020; code < 1040; ++code) {
            OptionUint16Ptr option = OptionUint16Ptr(new OptionUint16(Option::V6,
                                                                      code, 2345));
            option->setEncapsulatedSpace("bar");
            ASSERT_NO_THROW(cfg.add(option, false, DHCP6_OPTION_SPACE));
        }

        // Create sub-options belonging to "foo" option space and encapsulating
        // foo-subs option space.
        for (uint16_t code = 1; code < 20; ++code) {
            OptionUint8Ptr option = OptionUint8Ptr(new OptionUint8(Option::V6, code,
                                                                   0x01));
            option->setEncapsulatedSpace("foo-subs");
            ASSERT_NO_THROW(cfg.add(option, false, "foo"));
        }

        // Create sub-options belonging to "bar" option space and encapsulating
        // bar-subs option space.
        for (uint16_t code = 100;  code < 119; ++code) {
            OptionUint8Ptr option = OptionUint8Ptr(new OptionUint8(Option::V6,
                                                                   code, 0x02));
            option->setEncapsulatedSpace("bar-subs");
            ASSERT_NO_THROW(cfg.add(option, false, "bar"));
        }

        // Create sub-options belonging to "foo-subs" option space.
        for (uint16_t code = 1; code < 10; ++code) {
            OptionUint8Ptr option = OptionUint8Ptr(new OptionUint8(Option::V6, code,
                                                                   0x03));
            ASSERT_NO_THROW(cfg.add(option, false, "foo-subs"));
        }

        // Create sub-options belonging to "bar-subs" option space.
        for (uint16_t code = 501;  code < 510; ++code) {
            OptionUint8Ptr option = OptionUint8Ptr(new OptionUint8(Option::V6,
                                                                   code, 0x04));
            ASSERT_NO_THROW(cfg.add(option, false, "bar-subs"));
        }
    }
};

// This test verifies the empty predicate.
TEST_F(CfgOptionTest, empty) {
    CfgOption cfg1;
    CfgOption cfg2;

    // Initially the option configurations should be empty.
    ASSERT_TRUE(cfg1.empty());
    ASSERT_TRUE(cfg2.empty());

    // Add an option to each configuration
    OptionPtr option(new Option(Option::V6, 1));
    ASSERT_NO_THROW(cfg1.add(option, false, DHCP6_OPTION_SPACE));
    ASSERT_NO_THROW(cfg2.add(option, true, "isc"));

    // The first option configuration has an option
    ASSERT_FALSE(cfg1.empty());

    // The second option configuration has a vendor option
    ASSERT_FALSE(cfg2.empty());
}

// This test verifies that the option configurations can be compared.
TEST_F(CfgOptionTest, equals) {
    CfgOption cfg1;
    CfgOption cfg2;

    // Initially the configurations should be equal.
    ASSERT_TRUE(cfg1 == cfg2);
    ASSERT_FALSE(cfg1 != cfg2);

    // Add 9 options to two different option spaces. Each option have different
    // option code and content.
    for (uint16_t code = 1; code < 10; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, code)));
        ASSERT_NO_THROW(cfg1.add(option, false, "isc"));
        ASSERT_NO_THROW(cfg1.add(option, true, "vendor-123"));
    }

    // Configurations should now be different.
    ASSERT_FALSE(cfg1 == cfg2);
    ASSERT_TRUE(cfg1 != cfg2);

    // Add 8 options (excluding the option with code 1) to the same option
    // spaces.
    for (uint16_t code = 2; code < 10; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, code)));
        ASSERT_NO_THROW(cfg2.add(option, false, "isc"));
        ASSERT_NO_THROW(cfg2.add(option, true, "vendor-123"));
    }

    // Configurations should still be unequal.
    ASSERT_FALSE(cfg1 == cfg2);
    ASSERT_TRUE(cfg1 != cfg2);

    // Add missing option to the option space isc.
    ASSERT_NO_THROW(cfg2.add(OptionPtr(new Option(Option::V6, 1,
                                                  OptionBuffer(10, 0x01))),
                             false, "isc"));
    // Configurations should still be unequal because option with code 1
    // is missing in the option space vendor-123.
    ASSERT_FALSE(cfg1 == cfg2);
    ASSERT_TRUE(cfg1 != cfg2);

    // Add missing option.
    ASSERT_NO_THROW(cfg2.add(OptionPtr(new Option(Option::V6, 1,
                                                  OptionBuffer(10, 0x01))),
                             true, "vendor-123"));
    // Configurations should now be equal.
    ASSERT_TRUE(cfg1 == cfg2);
    ASSERT_FALSE(cfg1 != cfg2);

}

// This test verifies that multiple options can be added to the configuration
// and that they can be retrieved using the option space name.
TEST_F(CfgOptionTest, add) {
    CfgOption cfg;

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, DHCP6_OPTION_SPACE));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "isc"));
    }

    // Get options from the Subnet and check if all 10 are there.
    OptionContainerPtr options = cfg.getAll(DHCP6_OPTION_SPACE);
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    options = cfg.getAll("isc");
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = cfg.getAll("abcd");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

// This test verifies that options can be replaced with udpated content.
TEST_F(CfgOptionTest, replace) {
    CfgOption cfg;

    // Let's add some options to the config to the config.
    OptionStringPtr option(new OptionString(Option::V6, 1, "one"));
    ASSERT_NO_THROW(cfg.add(option, false, "isc"));

    option.reset(new OptionString(Option::V6, 2, "two"));
    ASSERT_NO_THROW(cfg.add(option, false, "isc"));

    option.reset(new OptionString(Option::V6, 3, "three"));
    ASSERT_NO_THROW(cfg.add(option, false, "isc"));

    // Now let's make sure we can find them and they are as expected.
    OptionDescriptor desc = cfg.get("isc", 1);
    ASSERT_TRUE(desc.option_);
    OptionStringPtr opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("one", opstr->getValue());

    desc = cfg.get("isc", 2);
    ASSERT_TRUE(desc.option_);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("two", opstr->getValue());

    desc = cfg.get("isc", 3);
    ASSERT_TRUE(desc.option_);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("three", opstr->getValue());

    // Now let's replace one and three.
    desc.option_.reset(new OptionString(Option::V6, 1, "new one"));
    ASSERT_NO_THROW(cfg.replace(desc, "isc"));

    desc.option_.reset(new OptionString(Option::V6, 3, "new three"));
    ASSERT_NO_THROW(cfg.replace(desc, "isc"));

    // Now let's make sure we can find them again and they are as expected.
    desc = cfg.get("isc", 1);
    ASSERT_TRUE(desc.option_);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("new one", opstr->getValue());

    desc = cfg.get("isc", 2);
    ASSERT_TRUE(desc.option_);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("two", opstr->getValue());

    desc = cfg.get("isc", 3);
    ASSERT_TRUE(desc.option_);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("new three", opstr->getValue());
}

// This test verifies that one configuration can be merged into another.
TEST_F(CfgOptionTest, mergeTo) {
    CfgOption cfg_src;
    CfgOption cfg_dst;

    // Create collection of options in option space dhcp6, with option codes
    // from the range of 100 to 109 and holding one byte of data equal to 0xFF.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0xFF)));
        ASSERT_NO_THROW(cfg_src.add(option, false, DHCP6_OPTION_SPACE));
    }

    // Create collection of options in vendor space 123, with option codes
    // from the range of 100 to 109 and holding one byte of data equal to 0xFF.
    for (uint16_t code = 100; code < 110; code += 2) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0xFF)));
        ASSERT_NO_THROW(cfg_src.add(option, false, "vendor-123"));
    }

    // Create destination configuration (configuration that we merge the
    // other configuration to).

    // Create collection of options having even option codes in the range of
    // 100 to 108.
    for (uint16_t code = 100; code < 110; code += 2) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0x01)));
        ASSERT_NO_THROW(cfg_dst.add(option, false, DHCP6_OPTION_SPACE));
    }

    // Create collection of options having odd option codes in the range of
    // 101 to 109.
    for (uint16_t code = 101; code < 110; code += 2) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0x01)));
        ASSERT_NO_THROW(cfg_dst.add(option, false, "vendor-123"));
    }

    // Merge source configuration to the destination configuration. The options
    // in the destination should be preserved. The options from the source
    // configuration should be added.
    ASSERT_NO_THROW(cfg_src.mergeTo(cfg_dst));

    // Validate the options in the dhcp6 option space in the destination.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionDescriptor desc = cfg_dst.get(DHCP6_OPTION_SPACE, code);
        ASSERT_TRUE(desc.option_);
        ASSERT_EQ(1, desc.option_->getData().size());
        // The options with even option codes should hold one byte of data
        // equal to 0x1. These are the ones that we have initially added to
        // the destination configuration. The other options should hold the
        // values of 0xFF which indicates that they have been merged from the
        // source configuration.
        if ((code % 2) == 0) {
            EXPECT_EQ(0x01, desc.option_->getData()[0]);
        } else {
            EXPECT_EQ(0xFF, desc.option_->getData()[0]);
        }
    }

    // Validate the options in the vendor space.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionDescriptor desc = cfg_dst.get(123, code);
        ASSERT_TRUE(desc.option_);
        ASSERT_EQ(1, desc.option_->getData().size());
        // This time, the options with even option codes should hold a byte
        // of data equal to 0xFF. The other options should hold the byte of
        // data equal to 0x01.
        if ((code % 2) == 0) {
            EXPECT_EQ(0xFF, desc.option_->getData()[0]);
        } else {
            EXPECT_EQ(0x01, desc.option_->getData()[0]);
        }
    }
}

// This test verifies that the options configuration can be copied between
// objects.
TEST_F(CfgOptionTest, copy) {
    CfgOption cfg_src;
    // Add 10 options to the custom option space in the source configuration.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0x01)));
        ASSERT_NO_THROW(cfg_src.add(option, false, "foo"));
    }

    CfgOption cfg_dst;
    // Add 20 options to the custom option space in destination configuration.
    for (uint16_t code = 100; code < 120; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0xFF)));
        ASSERT_NO_THROW(cfg_dst.add(option, false, "isc"));
    }

    // Copy entire configuration to the destination. This should override any
    // existing data.
    ASSERT_NO_THROW(cfg_src.copyTo(cfg_dst));

    // Validate options in the destination configuration.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionDescriptor desc = cfg_dst.get("foo", code);
        ASSERT_TRUE(desc.option_);
        ASSERT_EQ(1, desc.option_->getData().size());
        EXPECT_EQ(0x01, desc.option_->getData()[0]);
    }

    // Any existing options should be removed.
    OptionContainerPtr container = cfg_dst.getAll("isc");
    ASSERT_TRUE(container);
    EXPECT_TRUE(container->empty());

    // The option space "foo" should contain exactly 10 options.
    container = cfg_dst.getAll("foo");
    ASSERT_TRUE(container);
    EXPECT_EQ(10, container->size());
}

// This test verifies that DHCP options from one configuration
// can be used to update options in another configuration.
// In other words, options from an "other" configuration
// can be merged into an existing configuration, with any
// duplicates in other overwriting those in the existing
// configuration.
TEST_F(CfgOptionTest, validMerge) {
    CfgOption this_cfg;
    CfgOption other_cfg;

    // We need to create a dictionary of defintions pass into option merge.
    CfgOptionDefPtr defs(new CfgOptionDef());
    defs->add((OptionDefinitionPtr(new OptionDefinition("one", 1, "uint8"))), "isc");
    defs->add((OptionDefinitionPtr(new OptionDefinition("two", 2, "uint8"))), "isc");
    defs->add((OptionDefinitionPtr(new OptionDefinition("four", 4, "uint8"))), "isc");
    defs->add((OptionDefinitionPtr(new OptionDefinition("three", 3, "uint8"))), "fluff");
    defs->add((OptionDefinitionPtr(new OptionDefinition("four", 4, "uint8"))), "fluff");

    // Create our existing config, that gets merged into.
    OptionPtr option(new Option(Option::V4, 1, OptionBuffer(1, 0x01)));
    ASSERT_NO_THROW(this_cfg.add(option, false, "isc"));

    // Add option 3 to "fluff"
    option.reset(new Option(Option::V4, 3, OptionBuffer(1, 0x03)));
    ASSERT_NO_THROW(this_cfg.add(option, false, "fluff"));

    // Add option 4 to "fluff".
    option.reset(new Option(Option::V4, 4, OptionBuffer(1, 0x04)));
    ASSERT_NO_THROW(this_cfg.add(option, false, "fluff"));

    // Create our other config that will be merged from.
    // Add Option 1 to "isc",  this should "overwrite" the original.
    option.reset(new Option(Option::V4, 1, OptionBuffer(1, 0x10)));
    ASSERT_NO_THROW(other_cfg.add(option, false, "isc"));

    // Add option 2  to "isc".
    option.reset(new Option(Option::V4, 2, OptionBuffer(1, 0x20)));
    ASSERT_NO_THROW(other_cfg.add(option, false, "isc"));

    // Add option 4 to "isc".
    option.reset(new Option(Option::V4, 4, OptionBuffer(1, 0x40)));
    ASSERT_NO_THROW(other_cfg.add(option, false, "isc"));

    // Merge source configuration to the destination configuration. The options
    // in the destination should be preserved. The options from the source
    // configuration should be added.
    ASSERT_NO_THROW(this_cfg.merge(defs, other_cfg));

    // isc:1 should come from "other" config.
    OptionDescriptor desc = this_cfg.get("isc", 1);
    ASSERT_TRUE(desc.option_);
    OptionUint8Ptr opint = boost::dynamic_pointer_cast<OptionUint8>(desc.option_);
    ASSERT_TRUE(opint);
    EXPECT_EQ(16, opint->getValue());

    // isc:2 should come from "other" config.
    desc = this_cfg.get("isc", 2);
    ASSERT_TRUE(desc.option_);
    opint = boost::dynamic_pointer_cast<OptionUint8>(desc.option_);
    ASSERT_TRUE(opint);
    EXPECT_EQ(32, opint->getValue());

    // isc:4 should come from "other" config.
    desc = this_cfg.get("isc", 4);
    ASSERT_TRUE(desc.option_);
    opint = boost::dynamic_pointer_cast<OptionUint8>(desc.option_);
    ASSERT_TRUE(opint);
    EXPECT_EQ(64, opint->getValue());

    // fluff:3 should come from "this" config.
    desc = this_cfg.get("fluff", 3);
    ASSERT_TRUE(desc.option_);
    opint = boost::dynamic_pointer_cast<OptionUint8>(desc.option_);
    ASSERT_TRUE(opint);
    EXPECT_EQ(3, opint->getValue());

    // fluff:4 should come from "this" config.
    desc = this_cfg.get("fluff", 4);
    ASSERT_TRUE(desc.option_);
    opint = boost::dynamic_pointer_cast<OptionUint8>(desc.option_);
    ASSERT_TRUE(opint);
    EXPECT_EQ(4, opint->getValue());
}

// This test verifies that attempting to merge options
// which are by incompatible with "known" option definitions
// are detected.
TEST_F(CfgOptionTest, mergeInvalid) {
    CfgOption this_cfg;
    CfgOption other_cfg;

    // Create an empty dictionary of defintions pass into option merge.
    CfgOptionDefPtr defs(new CfgOptionDef());

    // Create our other config that will be merged from.
    // Add an option without a formatted value.
    OptionPtr option(new Option(Option::V4, 1, OptionBuffer(1, 0x01)));
    ASSERT_NO_THROW(other_cfg.add(option, false, "isc"));

    // Add an option with a formatted value.
    option.reset(new Option(Option::V4, 2));
    OptionDescriptor desc(option, false, "one,two,three");
    ASSERT_NO_THROW(other_cfg.add(desc, "isc"));

    // When we attempt to merge, it should fail, recognizing that
    // option 2, which has a formatted value,  has no definition.
    try {
        this_cfg.merge(defs, other_cfg);
        GTEST_FAIL() << "merge should have thrown";
    } catch (const InvalidOperation& ex) {
        std::string exp_msg = "option: isc.2 has a formatted value: "
                              "'one,two,three' but no option definition";
        EXPECT_EQ(std::string(exp_msg), std::string(ex.what()));
    } catch (const std::exception& ex) {
        GTEST_FAIL() << "wrong exception thrown:" << ex.what();
    }

    // Now let's add an option definition that will force data truncated
    // error for option 1.
    defs->add((OptionDefinitionPtr(new OptionDefinition("one", 1, "uint16"))), "isc");

    // When we attempt to merge, it should fail because option 1's data
    // is not valid per its definition.
    try {
        this_cfg.merge(defs, other_cfg);
        GTEST_FAIL() << "merge should have thrown";
    } catch (const InvalidOperation& ex) {
        std::string exp_msg = "could not create option: isc.1"
                              " from data specified, reason:"
                              " Option 1 truncated";
        EXPECT_EQ(std::string(exp_msg), std::string(ex.what()));
    } catch (const std::exception& ex) {
        GTEST_FAIL() << "wrong exception thrown:" << ex.what();
    }
}

// This test verifies the all of the valid option cases
// in createDescriptorOption():
// 1. standard option
// 2. vendor option
// 3. user-defined, unformatted option
// 4. user-defined, formatted option
// 5. undefined, unformatted option
TEST_F(CfgOptionTest, createDescriptorOptionValid) {
    // First we'll create our "known" user definitions
    CfgOptionDefPtr defs(new CfgOptionDef());
    defs->add((OptionDefinitionPtr(new OptionDefinition("one", 1, "uint8"))), "isc");
    defs->add((OptionDefinitionPtr(new OptionDefinition("two", 2, "uint8", true))), "isc");

    // We'll try a standard option first.
    std::string space = "dhcp4";
    std::string value("example.org");
    OptionPtr option(new Option(Option::V4, DHO_HOST_NAME));
    option->setData(value.begin(), value.end());
    OptionDescriptorPtr desc(new OptionDescriptor(option, false));

    bool updated = false;
    ASSERT_NO_THROW(updated = CfgOption::createDescriptorOption(defs, space, *desc));
    ASSERT_TRUE(updated);
    OptionStringPtr opstr = boost::dynamic_pointer_cast<OptionString>(desc->option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("example.org", opstr->getValue());

    // Next we'll try a vendor option with a formatted value
    space = "vendor-4491";
    value = "192.0.2.1, 192.0.2.2";
    option.reset(new Option(Option::V4, 2));
    desc.reset(new OptionDescriptor(option, false, value));

    ASSERT_NO_THROW(updated = CfgOption::createDescriptorOption(defs, space, *desc));
    ASSERT_TRUE(updated);
    Option4AddrLstPtr opaddrs = boost::dynamic_pointer_cast<Option4AddrLst>(desc->option_);
    ASSERT_TRUE(opaddrs);
    Option4AddrLst::AddressContainer exp_addresses = { IOAddress("192.0.2.1"), IOAddress("192.0.2.2") };
    EXPECT_EQ(exp_addresses, opaddrs->getAddresses());

    // Now, a user defined uint8 option
    space = "isc";
    option.reset(new Option(Option::V4, 1, OptionBuffer(1, 0x77)));
    desc.reset(new OptionDescriptor(option, false));

    ASSERT_NO_THROW(updated = CfgOption::createDescriptorOption(defs, space, *desc));
    ASSERT_TRUE(updated);
    OptionUint8Ptr opint = boost::dynamic_pointer_cast<OptionUint8>(desc->option_);
    ASSERT_TRUE(opint);
    EXPECT_EQ(119, opint->getValue());

    // Now, a user defined array of ints from a formatted value
    option.reset(new Option(Option::V4, 2));
    desc.reset(new OptionDescriptor(option, false, "1,2,3"));

    ASSERT_NO_THROW(updated = CfgOption::createDescriptorOption(defs, space, *desc));
    ASSERT_TRUE(updated);
    OptionUint8ArrayPtr oparray = boost::dynamic_pointer_cast<OptionUint8Array>(desc->option_);
    ASSERT_TRUE(oparray);
    std::vector<uint8_t> exp_ints = { 1, 2, 3 };
    EXPECT_EQ(exp_ints, oparray->getValues());

    // Finally, a generic, undefined option
    option.reset(new Option(Option::V4, 199, OptionBuffer(1, 0x77)));
    desc.reset(new OptionDescriptor(option, false));

    ASSERT_NO_THROW(updated = CfgOption::createDescriptorOption(defs, space, *desc));
    ASSERT_FALSE(updated);
    ASSERT_EQ(1, desc->option_->getData().size());
    EXPECT_EQ(0x77, desc->option_->getData()[0]);
}

// This test verifies that encapsulated options are added as sub-options
// to the top level options on request.
TEST_F(CfgOptionTest, encapsulate) {
    CfgOption cfg;

    generateEncapsulatedOptions(cfg);

    // Append options from "foo" and "bar" space as sub-options and options
    // from "foo-subs" and "bar-subs" as sub-options of "foo" and "bar"
    // options.
    ASSERT_NO_THROW(cfg.encapsulate());

    // Verify that we have 40 top-level options.
    OptionContainerPtr options = cfg.getAll(DHCP6_OPTION_SPACE);
    ASSERT_EQ(40, options->size());

    // Iterate over top level options.
    for (uint16_t code = 1000; code < 1040; ++code) {

        OptionUint16Ptr option = boost::dynamic_pointer_cast<
            OptionUint16>(cfg.get(DHCP6_OPTION_SPACE, code).option_);
        ASSERT_TRUE(option) << "option with code " << code << " not found";

        // First level sub options. There are 19 sub-options for each top
        // level option.
        const OptionCollection& first_level = option->getOptions();
        ASSERT_EQ(19, first_level.size());

        // Iterate over all first level sub-options.
        std::pair<unsigned int, OptionPtr> first_level_opt;
        BOOST_FOREACH(first_level_opt, first_level) {
            // Each option in this test comprises a single one byte field and
            // should cast to OptionUint8 type.
            OptionUint8Ptr first_level_uint8 = boost::dynamic_pointer_cast<
                OptionUint8>(first_level_opt.second);
            ASSERT_TRUE(first_level_uint8);

            const unsigned int value = static_cast<unsigned int>(first_level_uint8->getValue());
            // There are two sets of first level sub-options. Those that include
            // a value of 1 and those that include a value of 2.
            if (first_level_uint8->getType() < 20) {
                EXPECT_EQ(1, value);
            } else {
                EXPECT_EQ(2, value);
            }

            // Each first level sub-option should include 9 second level
            // sub options.
            const OptionCollection& second_level = first_level_uint8->getOptions();
            ASSERT_EQ(9, second_level.size());

            // Iterate over sub-options and make sure they include the expected
            // values.
            std::pair<unsigned int, OptionPtr> second_level_opt;
            BOOST_FOREACH(second_level_opt, second_level) {
                OptionUint8Ptr second_level_uint8 = boost::dynamic_pointer_cast<
                    OptionUint8>(second_level_opt.second);
                ASSERT_TRUE(second_level_uint8);
                const unsigned value = static_cast<
                    unsigned>(second_level_uint8->getValue());
                // Certain sub-options should have a value of 3, other the values
                // of 4.
                if (second_level_uint8->getType() < 20) {
                    EXPECT_EQ(3, value);
                } else {
                    EXPECT_EQ(4, value);
                }
            }
        }
    }
}

// This test verifies that an option can be deleted from the configuration.
TEST_F(CfgOptionTest, delFromOptionSpace) {
    CfgOption cfg;

    generateEncapsulatedOptions(cfg);

    // Append options from "foo" and "bar" space as sub-options and options
    // from "foo-subs" and "bar-subs" as sub-options of "foo" and "bar"
    // options.
    ASSERT_NO_THROW(cfg.encapsulate());

    // The option with the code 5 should exist in the option space "foo".
    ASSERT_TRUE(cfg.get("foo", 5).option_);

    // Because we called "encapsulate", this option should have been
    // propagated to the options encapsulating option space "foo".
    for (uint16_t code = 1000; code < 1020; ++code) {
        OptionDescriptor top_level_option(false);
        ASSERT_NO_THROW(top_level_option = cfg.get(DHCP6_OPTION_SPACE, code));
        // Make sure that the option with code 5 is there.
        ASSERT_TRUE(top_level_option.option_);
        ASSERT_TRUE(top_level_option.option_->getOption(5));

        // Make sure that options belonging to space "foo-subs" should contain
        // options with the code of 5.
        for (uint16_t code_subs = 1; code_subs != 19; ++code_subs) {
            OptionPtr sub_option;
            ASSERT_NO_THROW(sub_option = top_level_option.option_->getOption(code_subs));
            ASSERT_TRUE(sub_option);
            ASSERT_TRUE(sub_option->getOption(5));
        }
    }

    // Delete option with the code 5 and belonging to option space "foo".
    uint64_t deleted_num;
    ASSERT_NO_THROW(deleted_num = cfg.del("foo", 5));
    EXPECT_EQ(1, deleted_num);

    // The option should now be gone from options config.
    EXPECT_FALSE(cfg.get("foo", 5).option_);
    // Option with the code of 5 in other option spaces should remain.
    EXPECT_TRUE(cfg.get("foo-subs", 5).option_);

    // Iterate over the options encapsulating "foo" option space. Make sure
    // that the option with code 5 is no longer encapsulated by these options.
    for (uint16_t code = 1000; code < 1020; ++code) {
        OptionDescriptor top_level_option(false);
        ASSERT_NO_THROW(top_level_option = cfg.get(DHCP6_OPTION_SPACE, code));
        ASSERT_TRUE(top_level_option.option_);
        EXPECT_FALSE(top_level_option.option_->getOption(5));
        // Other options should remain.
        EXPECT_TRUE(top_level_option.option_->getOption(1));

        // Iterate over options within foo-subs option space and make sure
        // that they still contain options with the code of 5.
        for (uint16_t code_subs = 1; code_subs != 19; ++code_subs) {
            // There shouldn't be option with the code of 5 in the "foo" space.
            if (code_subs == 5) {
                continue;
            }

            OptionPtr sub_option;
            ASSERT_NO_THROW(sub_option = top_level_option.option_->getOption(code_subs));
            // Options belonging to option space "foo-subs" should include option
            // with the code of 5.
            ASSERT_TRUE(sub_option);
            ASSERT_TRUE(sub_option->getOption(5));
        }
    }
}

// This test verifies that a vendor option can be deleted from the configuration.
TEST_F(CfgOptionTest, delVendorOption) {
    CfgOption cfg;

    // Create multiple vendor options for vendor id 123.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "vendor-123"));
    }

    // Create multiple vendor options for vendor id 234.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "vendor-234"));
    }

    // Make sure that the option we're trying to delete is there.
    ASSERT_TRUE(cfg.get(123, 105).option_);
    // There should also be an option 105 for vendor id 234.
    ASSERT_TRUE(cfg.get(234, 105).option_);

    // Delete the option for vendor id 123.
    uint64_t deleted_num;
    ASSERT_NO_THROW(deleted_num = cfg.del(123, 105));
    EXPECT_EQ(1, deleted_num);

    // Make sure the option is gone.
    EXPECT_FALSE(cfg.get(123, 105).option_);
    // Make sure that the option with code 105 is not affected for vendor id 234.
    EXPECT_TRUE(cfg.get(234, 105).option_);

    // Other options, like 107, shouldn't be gone.
    EXPECT_TRUE(cfg.get(123, 107).option_);
}

// This test verifies that single option can be retrieved from the configuration
// using option code and option space.
TEST_F(CfgOptionTest, get) {
    CfgOption cfg;

    // Add 10 options to a "dhcp6" option space in the subnet.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, DHCP6_OPTION_SPACE));
    }

    // Check that we can get each added option descriptor using
    // individually.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream stream;
        // First, try the invalid option space name.
        OptionDescriptor desc = cfg.get("isc", code);
        // Returned descriptor should contain NULL option ptr.
        EXPECT_FALSE(desc.option_);
        // Now, try the valid option space.
        desc = cfg.get(DHCP6_OPTION_SPACE, code);
        // Test that the option code matches the expected code.
        ASSERT_TRUE(desc.option_);
        EXPECT_EQ(code, desc.option_->getType());
    }
}

// This test verifies that the same options can be added to the configuration
// under different option space.
TEST_F(CfgOptionTest, addNonUniqueOptions) {
    CfgOption cfg;

    // Create a set of options with non-unique codes.
    for (int i = 0;  i < 2; ++i) {
        // In the inner loop we create options with unique codes (100-109).
        for (uint16_t code = 100; code < 110; ++code) {
            OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
            ASSERT_NO_THROW(cfg.add(option, false, DHCP6_OPTION_SPACE));
        }
    }

    // Sanity check that all options are there.
    OptionContainerPtr options = cfg.getAll(DHCP6_OPTION_SPACE);
    ASSERT_EQ(20, options->size());

    // Use container index #1 to get the options by their codes.
    OptionContainerTypeIndex& idx = options->get<1>();
    // Look for the codes 100-109.
    for (uint16_t code = 100; code < 110; ++ code) {
        // For each code we should get two instances of options->
        OptionContainerTypeRange range = idx.equal_range(code);
        // Distance between iterators indicates how many options
        // have been returned for the particular code.
        ASSERT_EQ(2, distance(range.first, range.second));
        // Check that returned options actually have the expected option code.
        for (OptionContainerTypeIndex::const_iterator option_desc = range.first;
             option_desc != range.second; ++option_desc) {
            ASSERT_TRUE(option_desc->option_);
            EXPECT_EQ(code, option_desc->option_->getType());
        }
    }

    // Let's try to find some non-exiting option.
    const uint16_t non_existing_code = 150;
    OptionContainerTypeRange range = idx.equal_range(non_existing_code);
    // Empty set is expected.
    EXPECT_EQ(0, distance(range.first, range.second));
}

// This test verifies that the option with the persistency flag can be
// added to the configuration and that options with the persistency flags
// can be retrieved.
TEST(Subnet6Test, addPersistentOption) {
    CfgOption cfg;

    // Add 10 options to the subnet with option codes 100 - 109.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        // We create 10 options and want some of them to be flagged
        // persistent and some non-persistent. Persistent options are
        // those that server sends to clients regardless if they ask
        // for them or not. We pick 3 out of 10 options and mark them
        // non-persistent and 7 other options persistent.
        // Code values: 102, 105 and 108 are divisible by 3
        // and options with these codes will be flagged non-persistent.
        // Options with other codes will be flagged persistent.
        bool persistent = (code % 3) ? true : false;
        ASSERT_NO_THROW(cfg.add(option, persistent, DHCP6_OPTION_SPACE));
    }

    // Get added options from the subnet.
    OptionContainerPtr options = cfg.getAll(DHCP6_OPTION_SPACE);

    // options->get<2> returns reference to container index #2. This
    // index is used to access options by the 'persistent' flag.
    OptionContainerPersistIndex& idx = options->get<2>();

    // Get all persistent options->
    OptionContainerPersistRange range_persistent = idx.equal_range(true);
    // 7 out of 10 options have been flagged persistent.
    ASSERT_EQ(7, distance(range_persistent.first, range_persistent.second));

    // Get all non-persistent options->
    OptionContainerPersistRange range_non_persistent = idx.equal_range(false);
    // 3 out of 10 options have been flagged not persistent.
    ASSERT_EQ(3, distance(range_non_persistent.first, range_non_persistent.second));
}

// This test verifies that the vendor option can be added to the configuration.
TEST_F(CfgOptionTest, addVendorOptions) {
    CfgOption cfg;

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "vendor-12345678"));
    }

    // Second option space uses corner case value for vendor id = max uint8.
    uint32_t vendor_id = std::numeric_limits<uint32_t>::max();
    std::ostringstream option_space;
    option_space << "vendor-" << vendor_id;

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, option_space.str()));
    }

    // Get options from the Subnet and check if all 10 are there.
    OptionContainerPtr options = cfg.getAll(12345678);
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    options = cfg.getAll(vendor_id);
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = cfg.getAll(1111111);
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

// This test verifies that option space names for the vendor options are
// correct.
TEST_F(CfgOptionTest, getVendorIdsSpaceNames) {
    CfgOption cfg;

    // Create 10 options, each goes under a different vendor id.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        // Generate space name for a unique vendor id.
        std::ostringstream s;
        s << "vendor-" << code;
        ASSERT_NO_THROW(cfg.add(option, false, s.str()));
    }

    // We should now have 10 different vendor ids.
    std::list<std::string> space_names = cfg.getVendorIdsSpaceNames();
    ASSERT_EQ(10, space_names.size());

    // Check that the option space names for those vendor ids are correct.
    for (std::list<std::string>::iterator name = space_names.begin();
         name != space_names.end(); ++name) {
        uint16_t id = static_cast<uint16_t>(std::distance(space_names.begin(),
                                                          name));
        std::ostringstream s;
        s << "vendor-" << (100 + id);
        EXPECT_EQ(s.str(), *name);
    }
}

// This test verifies that the unparse function returns what is expected.
TEST_F(CfgOptionTest, unparse) {
    CfgOption cfg;

    // Add some options.
    OptionPtr opt1(new Option(Option::V6, 100, OptionBuffer(4, 0x12)));
    cfg.add(opt1, false, "dns");
    OptionPtr opt2(new Option(Option::V6, 101, OptionBuffer(4, 12)));
    OptionDescriptor desc2(opt2, false, "12, 12, 12, 12");
    std::string ctx = "{ \"comment\": \"foo\", \"bar\": 1 }";
    desc2.setContext(data::Element::fromJSON(ctx));
    cfg.add(desc2, "dns");
    OptionPtr opt3(new Option(Option::V6, D6O_STATUS_CODE, OptionBuffer(2, 0)));
    cfg.add(opt3, false, DHCP6_OPTION_SPACE);
    OptionPtr opt4(new Option(Option::V6, 100, OptionBuffer(4, 0x21)));
    cfg.add(opt4, true, "vendor-1234");

    // Unparse
    std::string expected = "[\n"
        "{\n"
        "    \"code\": 100,\n"
        "    \"space\": \"dns\",\n"
        "    \"csv-format\": false,\n"
        "    \"data\": \"12121212\",\n"
        "    \"always-send\": false\n"
        "},{\n"
        "    \"comment\": \"foo\",\n"
        "    \"code\": 101,\n"
        "    \"space\": \"dns\",\n"
        "    \"csv-format\": true,\n"
        "    \"data\": \"12, 12, 12, 12\",\n"
        "    \"always-send\": false,\n"
        "    \"user-context\": { \"bar\": 1 }\n"
        "},{\n"
        "    \"code\": 13,\n"
        "    \"name\": \"status-code\",\n"
        "    \"space\": \"dhcp6\",\n"
        "    \"csv-format\": false,\n"
        "    \"data\": \"0000\",\n"
        "    \"always-send\": false\n"
        "},{\n"
        "    \"code\": 100,\n"
        "    \"space\": \"vendor-1234\",\n"
        "    \"csv-format\": false,\n"
        "    \"data\": \"21212121\",\n"
        "    \"always-send\": true\n"
        "}]\n";
    isc::test::runToElementTest<CfgOption>(expected, cfg);
}

} // end of anonymous namespace
