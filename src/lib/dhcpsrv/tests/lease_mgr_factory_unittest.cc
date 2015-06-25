// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

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

// This test checks that a database access string can be parsed correctly.
TEST_F(LeaseMgrFactoryTest, parse) {

    DataSource::ParameterMap parameters = DataSource::parse(
        "user=me password=forbidden name=kea somethingelse= type=mysql");

    EXPECT_EQ(5, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
    EXPECT_EQ("", parameters["somethingelse"]);
}

// This test checks that an invalid database access string behaves as expected.
TEST_F(LeaseMgrFactoryTest, parseInvalid) {

    // No tokens in the string, so we expect no parameters
    std::string invalid = "";
    DataSource::ParameterMap parameters = DataSource::parse(invalid);
    EXPECT_EQ(0, parameters.size());

    // With spaces, there are some tokens so we expect invalid parameter
    // as there are no equals signs.
    invalid = "   \t  ";
    EXPECT_THROW(DataSource::parse(invalid), isc::InvalidParameter);

    invalid = "   noequalshere  ";
    EXPECT_THROW(DataSource::parse(invalid), isc::InvalidParameter);

    // A single "=" is valid string, but is placed here as the result is
    // expected to be nothing.
    invalid = "=";
    parameters = DataSource::parse(invalid);
    EXPECT_EQ(1, parameters.size());
    EXPECT_EQ("", parameters[""]);
}

/// @brief redactConfigString test
///
/// Checks that the redacted configuration string includes the password only
/// as a set of asterisks.
TEST_F(LeaseMgrFactoryTest, redactAccessString) {

    DataSource::ParameterMap parameters =
    		DataSource::parse("user=me password=forbidden name=kea type=mysql");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DataSource::redactedAccessString(parameters);
    parameters = DataSource::parse(redacted);

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("*****", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
}

/// @brief redactConfigString test - empty password
///
/// Checks that the redacted configuration string includes the password only
/// as a set of asterisks, even if the password is null.
TEST_F(LeaseMgrFactoryTest, redactAccessStringEmptyPassword) {

    DataSource::ParameterMap parameters =
    		DataSource::parse("user=me name=kea type=mysql password=");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DataSource::redactedAccessString(parameters);
    parameters = DataSource::parse(redacted);

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("*****", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // ... and again to check that the position of the empty password in the
    // string does not matter.
    parameters = DataSource::parse("user=me password= name=kea type=mysql");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    redacted = DataSource::redactedAccessString(parameters);
    parameters = DataSource::parse(redacted);

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("*****", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
}

/// @brief redactConfigString test - no password
///
/// Checks that the redacted configuration string excludes the password if there
/// was no password to begin with.
TEST_F(LeaseMgrFactoryTest, redactAccessStringNoPassword) {

    DataSource::ParameterMap parameters =
    		DataSource::parse("user=me name=kea type=mysql");
    EXPECT_EQ(3, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DataSource::redactedAccessString(parameters);
    parameters = DataSource::parse(redacted);

    EXPECT_EQ(3, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
}

}; // end of anonymous namespace
