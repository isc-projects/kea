// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

#include <asiolink/io_address.h>
#include <dhcp/lease_mgr_factory.h>

using namespace std;
using namespace isc::dhcp;

// This set of tests only check the parsing functions of LeaseMgrFactory.
// Tests of the LeaseMgr create/instance/destroy are implicitly carried out
// in the tests for the different concrete lease managers (e.g. MySqlLeaseMgr).

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class LeaseMgrFactoryTest : public ::testing::Test {
public:
    LeaseMgrFactoryTest() {
    }
};

// This test checks if the LeaseMgr can be instantiated and that it
// parses parameters string properly.
TEST_F(LeaseMgrFactoryTest, parse) {

    std::map<std::string, std::string> parameters = LeaseMgrFactory::parse(
        "param1=value1 param2=value2 param3=value3");

    EXPECT_EQ("value1", parameters["param1"]);
    EXPECT_EQ("value2", parameters["param2"]);
    EXPECT_TRUE(parameters.find("type") == parameters.end());
}

}; // end of anonymous namespace
