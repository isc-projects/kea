// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfg_rsoo.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

namespace {

// This test verifies that the RSOO configuration holds the default
// RSOO-enabled options.
TEST(CfgRSOOTest, defaults) {
    CfgRSOO rsoo;
    EXPECT_TRUE(rsoo.enabled(D6O_ERP_LOCAL_DOMAIN_NAME));
    for (uint16_t code = 0; code < 200; ++code) {
        if (code != D6O_ERP_LOCAL_DOMAIN_NAME) {
            EXPECT_FALSE(rsoo.enabled(code))
                << "expected that the option with code "
                << code << " is by default RSOO-disabled, but"
                " it is enabled";
        }
    }

    // Now, let's see if we can remove the default options.
    ASSERT_NO_THROW(rsoo.clear());
    EXPECT_FALSE(rsoo.enabled(D6O_ERP_LOCAL_DOMAIN_NAME));

    // Make sure it can be added again.
    ASSERT_NO_THROW(rsoo.enable(D6O_ERP_LOCAL_DOMAIN_NAME));
    EXPECT_TRUE(rsoo.enabled(D6O_ERP_LOCAL_DOMAIN_NAME));
}

// This test verifies that it is possible to enable more RSOO options
// and later remove all of them.
TEST(CfgRSOOTest, enableAndClear) {
    CfgRSOO rsoo;
    EXPECT_TRUE(rsoo.enabled(D6O_ERP_LOCAL_DOMAIN_NAME));

    // Enable option 88.
    ASSERT_FALSE(rsoo.enabled(88));
    ASSERT_NO_THROW(rsoo.enable(88));
    EXPECT_TRUE(rsoo.enabled(88));

    // Enable option 89.
    ASSERT_FALSE(rsoo.enabled(89));
    ASSERT_NO_THROW(rsoo.enable(89));
    EXPECT_TRUE(rsoo.enabled(89));

    // Remove them and make sure they have been removed.
    ASSERT_NO_THROW(rsoo.clear());
    for (uint16_t code = 0; code < 200; ++code) {
        EXPECT_FALSE(rsoo.enabled(code))
            << "expected that the option with code "
            << code << " is RSOO-disabled after clearing"
            " the RSOO configuration, but it is not";
    }
}

// This test verfies that the same option may be specified
// multiple times and that the code doesn't fail.
TEST(CfgRSOOTest, enableTwice) {
    CfgRSOO rsoo;
    // By default there should be the default option enabled.
    // Let's try to enable it again. It should pass.
    ASSERT_NO_THROW(rsoo.enable(D6O_ERP_LOCAL_DOMAIN_NAME));
    EXPECT_TRUE(rsoo.enabled(D6O_ERP_LOCAL_DOMAIN_NAME));

    // Enable option 88.
    ASSERT_FALSE(rsoo.enabled(88));
    ASSERT_NO_THROW(rsoo.enable(88));
    EXPECT_TRUE(rsoo.enabled(88));

    // And enable it again.
    ASSERT_NO_THROW(rsoo.enabled(88));
    EXPECT_TRUE(rsoo.enabled(88));

    // Remove all.
    ASSERT_NO_THROW(rsoo.clear());
    ASSERT_FALSE(rsoo.enabled(D6O_ERP_LOCAL_DOMAIN_NAME));
    ASSERT_FALSE(rsoo.enabled(88));
}

} // end of anonymous namespace
