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
#include <dhcp/option.h>
#include <dhcpsrv/cfg_option.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

namespace {

// This test verifies that multiple options can be added to the configuration
// and that they can be retrieved using the option space name.
TEST(CfgOptionTest, add) {
    CfgOption cfg;

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "dhcp6"));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "isc"));
    }

    // Get options from the Subnet and check if all 10 are there.
    OptionContainerPtr options = cfg.getAll("dhcp6");
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    options = cfg.getAll("isc");
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = cfg.getAll("abcd");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

// This test verifies that single option can be retrieved from the configuration
// using option code and option space.
TEST(CfgOption, get) {
    CfgOption cfg;

    // Add 10 options to a "dhcp6" option space in the subnet.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "dhcp6"));
    }

    // Check that we can get each added option descriptor using
    // individually.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream stream;
        // First, try the invalid option space name.
        OptionDescriptor desc = cfg.get("isc", code);
        // Returned descriptor should contain NULL option ptr.
        EXPECT_FALSE(desc.option);
        // Now, try the valid option space.
        desc = cfg.get("dhcp6", code);
        // Test that the option code matches the expected code.
        ASSERT_TRUE(desc.option);
        EXPECT_EQ(code, desc.option->getType());
    }
}

// This test verifies that the same options can be added to the configuration
// under different option space.
TEST(CfgOptionTest, addNonUniqueOptions) {
    CfgOption cfg;

    // Create a set of options with non-unique codes.
    for (int i = 0;  i < 2; ++i) {
        // In the inner loop we create options with unique codes (100-109).
        for (uint16_t code = 100; code < 110; ++code) {
            OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
            ASSERT_NO_THROW(cfg.add(option, false, "dhcp6"));
        }
    }

    // Sanity check that all options are there.
    OptionContainerPtr options = cfg.getAll("dhcp6");
    ASSERT_EQ(20, options->size());

    // Use container index #1 to get the options by their codes.
    OptionContainerTypeIndex& idx = options->get<1>();
    // Look for the codes 100-109.
    for (uint16_t code = 100; code < 110; ++ code) {
        // For each code we should get two instances of options->
        std::pair<OptionContainerTypeIndex::const_iterator,
                  OptionContainerTypeIndex::const_iterator> range =
            idx.equal_range(code);
        // Distance between iterators indicates how many options
        // have been retured for the particular code.
        ASSERT_EQ(2, distance(range.first, range.second));
        // Check that returned options actually have the expected option code.
        for (OptionContainerTypeIndex::const_iterator option_desc = range.first;
             option_desc != range.second; ++option_desc) {
            ASSERT_TRUE(option_desc->option);
            EXPECT_EQ(code, option_desc->option->getType());
        }
    }

    // Let's try to find some non-exiting option.
    const uint16_t non_existing_code = 150;
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(non_existing_code);
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
        ASSERT_NO_THROW(cfg.add(option, persistent, "dhcp6"));
    }

    // Get added options from the subnet.
    OptionContainerPtr options = cfg.getAll("dhcp6");

    // options->get<2> returns reference to container index #2. This
    // index is used to access options by the 'persistent' flag.
    OptionContainerPersistIndex& idx = options->get<2>();

    // Get all persistent options->
    std::pair<OptionContainerPersistIndex::const_iterator,
              OptionContainerPersistIndex::const_iterator> range_persistent =
        idx.equal_range(true);
    // 3 out of 10 options have been flagged persistent.
    ASSERT_EQ(7, distance(range_persistent.first, range_persistent.second));

    // Get all non-persistent options->
    std::pair<OptionContainerPersistIndex::const_iterator,
              OptionContainerPersistIndex::const_iterator> range_non_persistent =
        idx.equal_range(false);
    // 7 out of 10 options have been flagged persistent.
    ASSERT_EQ(3, distance(range_non_persistent.first, range_non_persistent.second));
}

// This test verifies that the vendor option can be added to the configuration.
TEST(CfgOptionTest, addVendorOptions) {
    CfgOption cfg;

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "vendor-12345678"));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(cfg.add(option, false, "vendor-87654321"));
    }

    // Get options from the Subnet and check if all 10 are there.
    OptionContainerPtr options = cfg.getAll(12345678);
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    options = cfg.getAll(87654321);
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = cfg.getAll(1111111);
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}


} // end of anonymous namespace
