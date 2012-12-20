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

#include <dhcp6/dbaccess_parser.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <config/ccsession.h>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;

namespace {

/// @brief Database Access Parser test fixture class
class DbAccessParserTest : public ::testing::Test {
public:
    /// @ Build JSON String
    ///
    /// Given a array of "const char*" strings representing in order, keyword,
    /// value, keyword, value, ... and terminated by a NULL, return a string
    /// that represents the JSON map for the keywords and values.
    ///
    /// @param keyval Array of "const char*" strings in the order keyword,
    ///        value, keyword, value ...  A NULL entry terminates the list.
    ///
    /// @return JSON map for the keyword value array.
    std::string toJson(const char* keyval[]) {
        const std::string quote = "\"";
        const std::string colon = ":";
        const std::string space = " ";

        string result = "{ ";

        for (size_t i = 0; keyval[i] != NULL; i+= 2) {
            // Get the value.  This should not be NULL.  As ASSERT_NE will
            // cause a return - which gives compilation problems as a return
            // statement is expected to return a string - use EXPECT_NE and
            // explicitly return if the expected array is incorrect.
            EXPECT_NE(static_cast<const char*>(NULL), keyval[i + 1]) <<
                "Supplied reference keyword/value list does not contain values "
                "for all keywords";
            if (keyval[i + 1] == NULL) {
                return (std::string(""));
            }

            // Add the separating comma if not the first.
            if (i != 0) {
                result += ", ";
            }

            // Add the keyword and value - make sure that they are quoted.
            result += quote + keyval[i] + quote + colon + space +
                      quote + keyval[i + 1] + quote;
        }

        // Add the terminating brace
        result += " }";

        return (result);
    }

    /// @brief Check for Keywords
    ///
    /// Takes a database access string and checks it against a list of keywords
    /// and values.  It checks that:
    ///
    /// a. Every keyword in the string appears once and only once in the
    ///    list.
    /// b. Every keyword in the list appears in the string.
    /// c. Every keyword's value is the same as that in the string.
    ///
    /// To parse the access string, we use the parsing function in the
    /// DHCP lease manager.
    ///
    /// @param trace_string String that will be used to set the value of a
    ///        SCOPED_TRACE for this call.
    /// @param dbaccess Database access string to check
    /// @param keyval Array of "const char*" strings in the order keyword,
    ///        value, keyword, value ...  A NULL entry terminates the list.
    void checkAccessString(const char* trace_string, std::string& dbaccess,
                           const char* keyval[]) {
        SCOPED_TRACE(trace_string);

        // Construct a map of keyword value pairs.  Check that no keyword
        // is repeated.
        map<string, string> expected;
        size_t expected_count = 0;
        for (size_t i = 0; keyval[i] != NULL; i += 2) {
            // Get the value.  This should not be NULL
            ASSERT_NE(static_cast<const char*>(NULL), keyval[i + 1]) <<
                "Supplied reference keyword/value list does not contain values "
                "for all keywords";
            expected[keyval[i]] = keyval[i + 1];

            // One more keyword processed
            ++expected_count;
        }

        // Check no duplicates in the supplied keywords
        ASSERT_EQ(expected_count, expected.size()) << 
            "Supplied reference keyword/value list contains duplicate keywords";

        // Split the database access string.
        const LeaseMgr::ParameterMap dbamap = LeaseMgrFactory::parse(dbaccess);

        // It should have the same number keyword value pairs as the
        EXPECT_EQ(expected_count, dbamap.size());

        // Check that the keywords and keyword values are the same: loop
        // through the keywords in the database access string.
        for (LeaseMgr::ParameterMap::const_iterator actual = dbamap.begin();
             actual != dbamap.end(); ++actual) {

            // Does the keyword exist in the set of expected keywords?
            map<string, string>::iterator corresponding =
                expected.find(actual->first);
            ASSERT_TRUE(corresponding != expected.end());

            // Keyword exists, is the value the same?
            EXPECT_EQ(corresponding->second, actual->second);
        }
    }
};

// Check that the parser works with a simple configuration.
TEST_F(DbAccessParserTest, validMemfile) {
    const char* config[] = {"type", "memfile",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    DbAccessParser parser;
    EXPECT_NO_THROW(parser.build(json_elements));
    string dbaccess = parser.getDbAccessString();

    checkAccessString("Valid memfile", dbaccess, config);
}

// Check that it works with a valid MySQL configuration
TEST_F(DbAccessParserTest, validMySql) {
    const char* config[] = {"type",     "mysql",
                            "host",     "erewhon",
                            "user",     "kea",
                            "password", "keapassword",
                            "name",     "keatest",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    DbAccessParser parser;
    EXPECT_NO_THROW(parser.build(json_elements));
    string dbaccess = parser.getDbAccessString();

    checkAccessString("Valid mysql", dbaccess, config);
}

};  // Anonymous namespace
