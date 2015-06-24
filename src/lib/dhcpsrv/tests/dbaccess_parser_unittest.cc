// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/command_interpreter.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/parsers/dbaccess_parser.h>
#include <log/logger_support.h>

#include <gtest/gtest.h>

#include <map>
#include <string>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;

namespace {

/// @brief Database Access Parser test fixture class
class DbAccessParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Just make sure that the lease database is closed before every test
    /// (the first in particular).
    DbAccessParserTest() {
        LeaseMgrFactory::destroy();
    }
    /// @brief Destructor
    ///
    /// Just make sure that the lease database is closed after every test
    /// (the last in particular).
    ///
    /// As some of the tests have the side-effect of altering the logging
    /// settings (when the parser's "build" method is called), ensure that
    /// the logging is reset to the default after each test completes.
    ~DbAccessParserTest() {
        LeaseMgrFactory::destroy();
        isc::log::setDefaultLoggingOutput();
    }

    /// @brief Build JSON String
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
            // The parameters which are not quoted are persist and
            // lfc-interval as they are boolean and integer respectively.
            result += quote + keyval[i] + quote + colon + space;
            if (!quoteValue(std::string(keyval[i]))) {
                result += keyval[i + 1];

            } else {
                result += quote + keyval[i + 1] + quote;
            }
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
    /// @param dbaccess set of database access parameters to check
    /// @param keyval Array of "const char*" strings in the order keyword,
    ///        value, keyword, value ...  A NULL entry terminates the list.
    /// @param u Universe (V4 or V6).
    void checkAccessString(const char* trace_string,
                           const DbAccessParser::StringPairMap& parameters,
                           const char* keyval[],
                           Option::Universe u = Option::V4) {
        SCOPED_TRACE(trace_string);

        // Construct a map of keyword value pairs.
        std::map<string, string> expected;
        expected["universe"] = (u == Option::V4 ? "4" : "6");
        // The universe is always injected by the parser itself.
        size_t expected_count = 1;
        for (size_t i = 0; keyval[i] != NULL; i += 2) {
            // Get the value.  This should not be NULL
            ASSERT_NE(static_cast<const char*>(NULL), keyval[i + 1]) <<
                "Supplied reference keyword/value list does not contain values "
                "for all keywords";
            expected[keyval[i]] = keyval[i + 1];

            // One more keyword processed
            ++expected_count;
        }

        // Check no duplicates in the test set of reference keywords.
        ASSERT_EQ(expected_count, expected.size()) <<
            "Supplied reference keyword/value list contains duplicate keywords";

        // The passed parameter map should have the same number of entries as
        // the reference set of keywords.
        EXPECT_EQ(expected_count, parameters.size());

        // Check that the keywords and keyword values are the same: loop
        // through the keywords in the database access string.
        for (LeaseMgr::ParameterMap::const_iterator actual = parameters.begin();
             actual != parameters.end(); ++actual) {

            // Does the keyword exist in the set of expected keywords?
            std::map<string, string>::iterator corresponding =
                expected.find(actual->first);
            ASSERT_TRUE(corresponding != expected.end());

            // Keyword exists, is the value the same?
            EXPECT_EQ(corresponding->second, actual->second);
        }
    }

private:

    /// @brief Checks if the value of the specified parameter should be
    /// quoted in the configuration.
    ///
    /// @param parameter A parameter for which it should be checked whether
    /// the value should be quoted or not.
    ///
    /// @return true if the value of the parameter should be quoted.
     bool quoteValue(const std::string& parameter) const {
         return ((parameter != "persist") && (parameter != "lfc-interval"));
    }

};


/// @brief Version of parser with protected methods public
///
/// Some of the methods in DbAccessParser are not required to be public in Kea.
/// Instead of being declared "private", they are declared "protected" so that
/// they can be accessed through a derived class in the unit tests.
class TestDbAccessParser : public DbAccessParser {
public:

    /// @brief Constructor
    ///
    /// @brief Keyword/value collection of ddatabase access parameters
    TestDbAccessParser(const std::string& param_name, const ParserContext& ctx)
        : DbAccessParser(param_name, ctx)
    {}

    /// @brief Destructor
    virtual ~TestDbAccessParser()
    {}

    /// Allow use of superclass's protected functions.
    using DbAccessParser::getDbAccessParameters;
    using DbAccessParser::getDbAccessString;

    /// @brief Get database access parameters
    ///
    /// Used in testing to check that the configuration information has been
    /// parsed corrected.
    ///
    /// @return Map of keyword/value pairs representing database access
    ///         information.
    const StringPairMap& getDbAccessParameters() const {
        return (DbAccessParser::getDbAccessParameters());
    }

    /// @brief Construct database access string
    ///
    /// Constructs the database access string from the stored parameters.
    ///
    /// @return Database access string
    std::string getDbAccessString() const {
        return (DbAccessParser::getDbAccessString());
    }
};

// Check that the parser works with a simple configuration.
TEST_F(DbAccessParserTest, validTypeMemfile) {
    const char* config[] = {"type", "memfile",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));
    EXPECT_NO_THROW(parser.build(json_elements));
    checkAccessString("Valid memfile", parser.getDbAccessParameters(), config);
}

// Check that the parser works with a simple configuration that
// includes empty elements.
TEST_F(DbAccessParserTest, emptyKeyword) {
    const char* config[] = {"type", "memfile",
                            "name", "",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));
    EXPECT_NO_THROW(parser.build(json_elements));
    checkAccessString("Valid memfile", parser.getDbAccessParameters(), config);
}

// Check that the parser works with more complex configuration when
// lease file path is specified for DHCPv4.
TEST_F(DbAccessParserTest, persistV4Memfile) {
    const char* config[] = {"type", "memfile",
                            "persist", "true",
                            "name", "/opt/kea/var/kea-leases4.csv",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));
    EXPECT_NO_THROW(parser.build(json_elements));

    checkAccessString("Valid memfile", parser.getDbAccessParameters(),
                      config);
}

// Check that the parser works with more complex configuration when
// lease file path is specified for DHCPv6.
TEST_F(DbAccessParserTest, persistV6Memfile) {
    const char* config[] = {"type", "memfile",
                            "persist", "true",
                            "name", "/opt/kea/var/kea-leases6.csv",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V6));
    EXPECT_NO_THROW(parser.build(json_elements));

    checkAccessString("Valid memfile", parser.getDbAccessParameters(),
                      config, Option::V6);
}

// This test checks that the parser accepts the valid value of the
// lfc-interval parameter.
TEST_F(DbAccessParserTest, validLFCInterval) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/kea/var/kea-leases6.csv",
                            "lfc-interval", "3600",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V6));
    ASSERT_NO_THROW(parser.build(json_elements));
    checkAccessString("Valid LFC Interval", parser.getDbAccessParameters(),
                      config, Option::V6);
}

// This test checks that the parser rejects the negative value of the
// lfc-interval parameter.
TEST_F(DbAccessParserTest, negativeLFCInterval) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/kea/var/kea-leases6.csv",
                            "lfc-interval", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V6));
    EXPECT_THROW(parser.build(json_elements), BadValue);
}

// This test checks that the parser rejects the too large (greater than
// the max uint32_t) value of the lfc-interval parameter.
TEST_F(DbAccessParserTest, largeLFCInterval) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/kea/var/kea-leases6.csv",
                            "lfc-interval", "4294967296",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V6));
    EXPECT_THROW(parser.build(json_elements), BadValue);
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

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));
    EXPECT_NO_THROW(parser.build(json_elements));
    checkAccessString("Valid mysql", parser.getDbAccessParameters(), config);
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

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));
    EXPECT_THROW(parser.build(json_elements), TypeKeywordMissing);
}

// Check that the factory function works.
TEST_F(DbAccessParserTest, factory) {

    // Check that the parser is built through the factory.
    boost::scoped_ptr<DhcpConfigParser> parser(
        DbAccessParser::factory("lease-database", ParserContext(Option::V4))
    );
    EXPECT_TRUE(parser);
    DbAccessParser* dbap = dynamic_cast<DbAccessParser*>(parser.get());
    EXPECT_NE(static_cast<DbAccessParser*>(NULL), dbap);
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
                                  "password", "",
                                  NULL};
    const char* config4[] = {"type",     "mysql",
                             "host",     "erewhon",
                             "user",     "them",
                             "password", "",
                             "name",     "keatest",
                             NULL};

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));

    // First configuration string should cause a representation of that string
    // to be held.
    string json_config = toJson(config1);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    checkAccessString("Initial configuration", parser.getDbAccessParameters(),
                      config1);

    // Applying a wholesale change will cause the access string to change
    // to a representation of the new configuration.
    json_config = toJson(config2);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    checkAccessString("Subsequent configuration", parser.getDbAccessParameters(),
                      config2);

    // Applying an incremental change will cause the representation to change
    // incrementally.
    json_config = toJson(incremental2);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    checkAccessString("Incremental configuration", parser.getDbAccessParameters(),
                      config3);

    // Applying the next incremental change should cause an exception to be
    // thrown and there be no change to the access string.
    json_config = toJson(incremental3);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_THROW(parser.build(json_elements), BadValue);
    checkAccessString("Incompatible incremental change", parser.getDbAccessParameters(),
                      config3);

    // Applying an incremental change will cause the representation to change
    // incrementally.
    json_config = toJson(incremental4);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.build(json_elements));
    checkAccessString("Compatible incremental change", parser.getDbAccessParameters(),
                      config4);
}

// Check that the database access string is constructed correctly.
TEST_F(DbAccessParserTest, getDbAccessString) {
    const char* config[] = {"type",     "mysql",
                            "host",     "" ,
                            "name",     "keatest",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));
    EXPECT_NO_THROW(parser.build(json_elements));

    // Get the database access string
    std::string dbaccess = parser.getDbAccessString();

    // String should be either "type=mysql name=keatest" or
    // "name=keatest type=mysql". The "host" entry is null, so should not be
    // output.
    EXPECT_EQ(dbaccess, "name=keatest type=mysql universe=4");
}

// Check that the "commit" function actually opens the database.  We will
// only do this for the "memfile" database, as that does not assume that the
// test has been built with MySQL support.
TEST_F(DbAccessParserTest, commit) {

    // Verify that no lease database is open
    EXPECT_THROW({
            LeaseMgr& manager = LeaseMgrFactory::instance();
            manager.getType();  // Never executed but satisfies compiler
            }, isc::dhcp::NoLeaseManager);

    // Set up the parser to open the memfile database.
    const char* config[] = {"type", "memfile", "persist", "false", NULL};
    string json_config = toJson(config);

    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser("lease-database", ParserContext(Option::V4));
    EXPECT_NO_THROW(parser.build(json_elements));

    // Ensure that the access string is as expected.
    EXPECT_EQ("persist=false type=memfile universe=4",
              parser.getDbAccessString());

    // Committal of the parser changes should open the database.
    EXPECT_NO_THROW(parser.commit());

    // Verify by checking the type of database open.
    std::string dbtype;
    EXPECT_NO_THROW(dbtype = LeaseMgrFactory::instance().getType());
    EXPECT_EQ(std::string("memfile"), dbtype);
}

};  // Anonymous namespace
