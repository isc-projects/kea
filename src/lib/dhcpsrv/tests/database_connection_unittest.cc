// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/database_connection.h>
#include <gtest/gtest.h>

using namespace isc::dhcp;


/// @brief getParameter test
///
/// This test checks if the LeaseMgr can be instantiated and that it
/// parses parameters string properly.
TEST(DatabaseConnectionTest, getParameter) {

    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("param1")] = std::string("value1");
    pmap[std::string("param2")] = std::string("value2");
    DatabaseConnection datasrc(pmap);

    EXPECT_EQ("value1", datasrc.getParameter("param1"));
    EXPECT_EQ("value2", datasrc.getParameter("param2"));
    EXPECT_THROW(datasrc.getParameter("param3"), isc::BadValue);
}

// This test checks that a database access string can be parsed correctly.
TEST(DatabaseConnectionTest, parse) {

    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(
        "user=me password=forbidden name=kea somethingelse= type=mysql");

    EXPECT_EQ(5, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
    EXPECT_EQ("", parameters["somethingelse"]);
}

// This test checks that an invalid database access string behaves as expected.
TEST(DatabaseConnectionTest, parseInvalid) {

    // No tokens in the string, so we expect no parameters
    std::string invalid = "";
    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(invalid);
    EXPECT_EQ(0, parameters.size());

    // With spaces, there are some tokens so we expect invalid parameter
    // as there are no equals signs.
    invalid = "   \t  ";
    EXPECT_THROW(DatabaseConnection::parse(invalid), isc::InvalidParameter);

    invalid = "   noequalshere  ";
    EXPECT_THROW(DatabaseConnection::parse(invalid), isc::InvalidParameter);

    // A single "=" is valid string, but is placed here as the result is
    // expected to be nothing.
    invalid = "=";
    parameters = DatabaseConnection::parse(invalid);
    EXPECT_EQ(1, parameters.size());
    EXPECT_EQ("", parameters[""]);
}

/// @brief redactConfigString test
///
/// Checks that the redacted configuration string includes the password only
/// as a set of asterisks.
TEST(DatabaseConnectionTest, redactAccessString) {

    DatabaseConnection::ParameterMap parameters =
        DatabaseConnection::parse("user=me password=forbidden name=kea type=mysql");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

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
TEST(DatabaseConnectionTest, redactAccessStringEmptyPassword) {

    DatabaseConnection::ParameterMap parameters =
        DatabaseConnection::parse("user=me name=kea type=mysql password=");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("*****", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // ... and again to check that the position of the empty password in the
    // string does not matter.
    parameters = DatabaseConnection::parse("user=me password= name=kea type=mysql");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

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
TEST(DatabaseConnectionTest, redactAccessStringNoPassword) {

    DatabaseConnection::ParameterMap parameters =
        DatabaseConnection::parse("user=me name=kea type=mysql");
    EXPECT_EQ(3, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

    EXPECT_EQ(3, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
}
