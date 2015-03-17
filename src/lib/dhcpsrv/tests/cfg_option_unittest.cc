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
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option.h>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <sstream>

using namespace isc;
using namespace isc::dhcp;

namespace {

// This test verifies that the option configurations can be compared.
TEST(CfgOptionTest, equals) {
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

// This test verifies that two option configurations can be merged.
TEST(CfgOption, merge) {
    CfgOption cfg_src;
    CfgOption cfg_dst;

    // Create collection of options in option space dhcp6, with option codes
    // from the range of 100 to 109 and holding one byte of data equal to 0xFF.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(1, 0xFF)));
        ASSERT_NO_THROW(cfg_src.add(option, false, "dhcp6"));
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
        ASSERT_NO_THROW(cfg_dst.add(option, false, "dhcp6"));
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
        OptionDescriptor desc = cfg_dst.get("dhcp6", code);
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
TEST(CfgOptionTest, copy) {
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

// This test verifies that encapsulated options are added as sub-options
// to the top level options on request.
TEST(CfgOptionTest, encapsulate) {
    CfgOption cfg;
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

    // Create sub-options belonging to "foo" option space.
    for (uint16_t code = 1; code < 20; ++code) {
        OptionUint8Ptr option = OptionUint8Ptr(new OptionUint8(Option::V6, code,
                                                               0x01));
        ASSERT_NO_THROW(cfg.add(option, false, "foo"));
    }

    // Create sub-options belonging to "bar" option space.
    for (uint16_t code = 100;  code < 130; ++code) {
        OptionUint8Ptr option = OptionUint8Ptr(new OptionUint8(Option::V6,
                                                               code, 0x02));
        ASSERT_NO_THROW(cfg.add(option, false, "bar"));
    }

    // Append options from "foo" and "bar" space as sub-options.
    ASSERT_NO_THROW(cfg.encapsulate());

    // Verify that we have 40 top-level options.
    OptionContainerPtr options = cfg.getAll(DHCP6_OPTION_SPACE);
    ASSERT_EQ(40, options->size());

    for (uint16_t code = 1000; code < 1040; ++code) {
        OptionUint16Ptr option = boost::dynamic_pointer_cast<
            OptionUint16>(cfg.get(DHCP6_OPTION_SPACE, code).option_);
        ASSERT_TRUE(option) << "option with code " << code << " not found";
        const OptionCollection& suboptions = option->getOptions();
        for (OptionCollection::const_iterator suboption =
                 suboptions.begin(); suboption != suboptions.end();
             ++suboption) {
            OptionUint8Ptr opt = boost::dynamic_pointer_cast<
                OptionUint8>(suboption->second);
            ASSERT_TRUE(opt);
            if (code < 1020) {
                EXPECT_EQ(0x01, opt->getValue());
            } else {
                EXPECT_EQ(0x02, opt->getValue());
            }
        }
    }
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
        EXPECT_FALSE(desc.option_);
        // Now, try the valid option space.
        desc = cfg.get("dhcp6", code);
        // Test that the option code matches the expected code.
        ASSERT_TRUE(desc.option_);
        EXPECT_EQ(code, desc.option_->getType());
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
            ASSERT_TRUE(option_desc->option_);
            EXPECT_EQ(code, option_desc->option_->getType());
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


} // end of anonymous namespace
