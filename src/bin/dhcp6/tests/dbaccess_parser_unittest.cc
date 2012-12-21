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
    /// E.g. given the array of strings: alpha, one, beta, two, NULL, it would
    /// return the string '{ "alpha": "one", "beta": "two" }'
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
TEST_F(DbAccessParserTest, validTypeMemfile) {
    const char* config[] = {"type", "memfile",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    DbAccessParser parser("lease-database");
    EXPECT_NO_THROW(parser.build(json_elements));
    string dbaccess = parser.getDbAccessString();
    checkAccessString("Valid memfile", dbaccess, config);
}

// Check that the parser works with a valid MySQL configuration
TEST_F(DbAccessParserTest, validTypeMysql) {
    const char* config[] = {"type",     "mysql",
                            "host",     "erewhon",
                            "user",     "kea",
                            "password", "keapassword",
                            "name",     "keatest",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    DbAccessParser parser("lease-database");
    EXPECT_NO_THROW(parser.build(json_elements));
    string dbaccess = parser.getDbAccessString();
    checkAccessString("Valid mysql", dbaccess, config);
}

// A missing 'type' keyword should cause an exception to be thrown.
TEST_F(DbAccessParserTest, missingTypeKeyword) {
    const char* config[] = {"host",     "erewhon",
                            "user",     "kea",
                            "password", "keapassword",
                            "name",     "keatest",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    DbAccessParser parser("lease-database");
    EXPECT_THROW(parser.build(json_elements), TypeKeywordMissing);
}

// If the value of the "type" keyword is unknown, a BadValue exception should
// be thrown.
TEST_F(DbAccessParserTest, badTypeKeyword) {
    const char* config[] = {"type",     "invalid",
                            "host",     "erewhon",
                            "user",     "kea",
                            "password", "keapassword",
                            "name",     "keatest",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    DbAccessParser parser("lease-database");
    EXPECT_THROW(parser.build(json_elements), BadValue);
}

// Check that the factory function works.
TEST_F(DbAccessParserTest, factory) {
    const char* config[] = {"type", "memfile",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    // Check that the parser is built through the factory.
    boost::scoped_ptr<DhcpConfigParser> parser(
        DbAccessParser::factory("lease-database"));
    EXPECT_NO_THROW(parser->build(json_elements));

    // Access the "raw" parser.
    DbAccessParser* dbap = dynamic_cast<DbAccessParser*>(parser.get());
    EXPECT_NE(static_cast<DbAccessParser*>(NULL), dbap);
    string dbaccess = dbap->getDbAccessString();
    checkAccessString("Valid mysql", dbaccess, config);
}

// Check reconfiguration.  Checks that incremental changes applied to the
// database configuration are incremental.
TEST_F(DbAccessParserTest, incrementalChanges) {
    const char* config1[] = {"type", "memfile",
                             NULL};

    // Applying config2 will cause a wholesale change.
    const char* config2[] = {"type",     "mysql",
                             "host",     "erewhon",
                             "user",     "kea",
                             "password", "keapassword",
                             "name",     "keatest",
                             NULL};

    // Applying incremental2 should cause a change to config3.
    const char* incremental2[] = {"user",     "me",
                                  "password", "meagain",
                                  NULL};
    const char* config3[] = {"type",     "mysql",
                             "host",     "erewhon",
                             "user",     "me",
                             "password", "meagain",
                             "name",     "keatest",
                             NULL};

    // incremental3 will cause an exception.  There should be no change
    // to the returned value.
    const char* incremental3[] = {"type",     "invalid",
                                  "user",     "you",
                                  "password", "youagain",
                                  NULL};

    // incremental4 is a compatible change and should cause a transition
    // to config4.
    const char* incremental4[] = {"user",     "them",
                                  "password", "themagain",
                                  NULL};
    const char* config4[] = {"type",     "mysql",
                             "host",     "erewhon",
                             "user",     "them",
                             "password", "themagain",
                             "name",     "keatest",
                             NULL};

    DbAccessParser parser("lease-database");

    // First configuration string should cause a representation of that string
    // to be held.
    string json_config = toJson(config1);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    string dbaccess = parser.getDbAccessString();
    checkAccessString("Initial configuration", dbaccess, config1);

    // Applying a wholesale change will cause the access string to change
    // to a representation of the new configuration.
    json_config = toJson(config2);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    dbaccess = parser.getDbAccessString();
    checkAccessString("Subsequent configuration", dbaccess, config2);

    // Applying an incremental change will cause the representation to change
    // incrementally.
    json_config = toJson(incremental2);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    dbaccess = parser.getDbAccessString();
    checkAccessString("Incremental configuration", dbaccess, config3);

    // Applying the next incremental change should cause an exception to be
    // thrown and there be no change to the access string.
    json_config = toJson(incremental3);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_THROW(parser.build(json_elements), BadValue);
    dbaccess = parser.getDbAccessString();
    checkAccessString("Incompatible incremental change", dbaccess, config3);

    // Applying an incremental change will cause the representation to change
    // incrementally.
    json_config = toJson(incremental4);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    dbaccess = parser.getDbAccessString();
    checkAccessString("Compatible incremental change", dbaccess, config4);
}

};  // Anonymous namespace
