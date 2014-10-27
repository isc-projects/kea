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

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_reservation_parser.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c HostReservationParser.
class HostReservationParserTest : public ::testing::Test {
protected:

    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();

};

void
HostReservationParserTest::SetUp() {
    CfgMgr::instance().clear();
}

void
HostReservationParserTest::TearDown() {
    CfgMgr::instance().clear();
}

// This test verfies that the parser can parse the reservation entry for
// which hw-address is a host identifier.
TEST_F(HostReservationParserTest, hwaddr) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"hostname\": \"\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser parser;
    ASSERT_NO_THROW(parser.build(config_element));
}

} // end of anonymous namespace
