// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <database/dbaccess_parser.h>
#include <log/logger_support.h>

#include <gtest/gtest.h>

#include <map>
#include <string>

using namespace std;
using namespace isc;
using namespace isc::db;
using namespace isc::data;
using namespace isc::config;

namespace {

/// @brief Database Access Parser test fixture class
class DbAccessParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    DbAccessParserTest() {
    }
    /// @brief Destructor
    ///
    /// As some of the tests have the side-effect of altering the logging
    /// settings (when the parser's "parse" method is called), ensure that
    /// the logging is reset to the default after each test completes.
    ~DbAccessParserTest() {
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
            // The parameters which are not quoted are persist, readonly and
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
    void checkAccessString(const char* trace_string,
                           const DatabaseConnection::ParameterMap& parameters,
                           const char* keyval[]) {
        SCOPED_TRACE(trace_string);

        // Construct a map of keyword value pairs.
        std::map<string, string> expected;
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

        // Check no duplicates in the test set of reference keywords.
        ASSERT_EQ(expected_count, expected.size()) <<
            "Supplied reference keyword/value list contains duplicate keywords";

        // The passed parameter map should have the same number of entries as
        // the reference set of keywords.
        EXPECT_EQ(expected_count, parameters.size());

        // Check that the keywords and keyword values are the same: loop
        // through the keywords in the database access string.
        for (DatabaseConnection::ParameterMap::const_iterator actual = parameters.begin();
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
         return ((parameter != "persist") && (parameter != "lfc-interval") &&
                 (parameter != "connect-timeout") &&
                 (parameter != "read-timeout") &&
                 (parameter != "write-timeout") &&
                 (parameter != "tcp-user-timeout") &&
                 (parameter != "port") &&
                 (parameter != "max-row-errors") &&
                 (parameter != "readonly"));
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
    TestDbAccessParser()
        : DbAccessParser()
    {}

    /// @brief Destructor
    virtual ~TestDbAccessParser()
    {}

    /// @brief Parse configuration value
    ///
    /// @param database_config Configuration to be parsed.
    void parse(ConstElementPtr database_config) {
        std::string db_access_string;
        DbAccessParser::parse(db_access_string, database_config);
    }

    /// @brief Get database access parameters
    ///
    /// Used in testing to check that the configuration information has been
    /// parsed corrected.
    ///
    /// @return Map of keyword/value pairs representing database access
    ///         information.
    const DatabaseConnection::ParameterMap& getDbAccessParameters() const {
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

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid memfile", parser.getDbAccessParameters(), config);
}

// Check that the parser works with a simple configuration for host database.
TEST_F(DbAccessParserTest, hosts) {
    const char* config[] = {"type", "memfile",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
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

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid memfile", parser.getDbAccessParameters(), config);
}

// Check that the parser works with more complex configuration when
// lease file path is specified for DHCPv4.
TEST_F(DbAccessParserTest, persistV4Memfile) {
    const char* config[] = {"type", "memfile",
                            "persist", "true",
                            "name", "/opt/var/lib/kea/kea-leases4.csv",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));

    checkAccessString("Valid memfile", parser.getDbAccessParameters(),
                      config);
}

// Check that the parser works with more complex configuration when
// lease file path is specified for DHCPv6.
TEST_F(DbAccessParserTest, persistV6Memfile) {
    const char* config[] = {"type", "memfile",
                            "persist", "true",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));

    checkAccessString("Valid memfile", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser accepts the valid value of the
// lfc-interval parameter.
TEST_F(DbAccessParserTest, validLFCInterval) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "lfc-interval", "3600",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid LFC Interval", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser rejects the negative value of the
// lfc-interval parameter.
TEST_F(DbAccessParserTest, negativeLFCInterval) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "lfc-interval", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser rejects the too large (greater than
// the max uint32_t) value of the lfc-interval parameter.
TEST_F(DbAccessParserTest, largeLFCInterval) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "lfc-interval", "4294967296",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser accepts the valid value of the
// connect-timeout parameter.
TEST_F(DbAccessParserTest, validConnectTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "connect-timeout", "3600",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid timeout", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser rejects the negative value of the
// connect-timeout parameter.
TEST_F(DbAccessParserTest, negativeConnectTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "connect-timeout", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser rejects a too large (greater than
// the max uint32_t) value of the connecttimeout parameter.
TEST_F(DbAccessParserTest, largeConnectTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "connect-timeout", "4294967296",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser accepts the valid value of the
// read-timeout parameter.
TEST_F(DbAccessParserTest, validReadTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "read-timeout", "3600",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid read timeout", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser rejects the negative value of the
// read-timeout parameter.
TEST_F(DbAccessParserTest, negativeReadTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "read-timeout", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser rejects a too large (greater than
// the max uint32_t) value of the read-timeout parameter.
TEST_F(DbAccessParserTest, largeReadTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "read-timeout", "4294967296",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser accepts the valid value of the
// write-timeout parameter.
TEST_F(DbAccessParserTest, validWriteTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "write-timeout", "3600",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid write timeout", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser rejects the negative value of the
// write-timeout parameter.
TEST_F(DbAccessParserTest, negativeWriteTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "write-timeout", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser rejects a too large (greater than
// the max uint32_t) value of the write-timeout parameter.
TEST_F(DbAccessParserTest, largeWriteTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "write-timeout", "4294967296",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser accepts the valid value of the
// tcp-user-timeout parameter.
TEST_F(DbAccessParserTest, validTcpUserTimeout) {
    const char* config[] = {"type", "postgresql",
                            "name", "keatest",
                            "tcp-user-timeout", "3600",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid write timeout", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser rejects the negative value of the
// tcp-user-timeout parameter.
TEST_F(DbAccessParserTest, negativeTcpUserTimeout) {
    const char* config[] = {"type", "postgresql",
                            "name", "keatest",
                            "tcp-user-timeout", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser rejects a too large (greater than
// the max uint32_t) value of the tcp-user-timeout parameter.
TEST_F(DbAccessParserTest, largeTcpUserTimeout) {
    const char* config[] = {"type", "postgresql",
                            "name", "keatest",
                            "tcp-user-timeout", "4294967296",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test verifies that specifying the tcp-user-timeout for the
// memfile backend is not allowed.
TEST_F(DbAccessParserTest, memfileTcpUserTimeout) {
    const char* config[] = {"type", "memfile",
                            "name", "keatest",
                            "tcp-user-timeout", "10",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test verifies that specifying the tcp-user-timeout for the
// mysql backend is not allowed.
TEST_F(DbAccessParserTest, mysqlTcpUserTimeout) {
    const char* config[] = {"type", "mysql",
                            "name", "keatest",
                            "tcp-user-timeout", "10",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test verifies that specifying the read-timeout for the
// memfile backend is not allowed.
TEST_F(DbAccessParserTest, memfileReadTimeout) {
    const char* config[] = {"type", "memfile",
                            "name", "keatest",
                            "read-timeout", "10",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test verifies that specifying the read-timeout for the
// postgresql backend is not allowed.
TEST_F(DbAccessParserTest, postgresqlReadTimeout) {
    const char* config[] = {"type", "postgresql",
                            "name", "keatest",
                            "read-timeout", "10",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test verifies that specifying the write-timeout for the
// memfile backend is not allowed.
TEST_F(DbAccessParserTest, memfileWriteTimeout) {
    const char* config[] = {"type", "memfile",
                            "name", "keatest",
                            "write-timeout", "10",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test verifies that specifying the write-timeout for the
// postgresql backend is not allowed.
TEST_F(DbAccessParserTest, postgresqlWriteTimeout) {
    const char* config[] = {"type", "postgresql",
                            "name", "keatest",
                            "write-timeout", "10",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser accepts the valid value of the
// port parameter.
TEST_F(DbAccessParserTest, validPort) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "port", "3306",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid port", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser rejects the negative value of the
// port parameter.
TEST_F(DbAccessParserTest, negativePort) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "port", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser rejects a too large (greater than
// the max uint16_t) value of the timeout parameter.
TEST_F(DbAccessParserTest, largePort) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "port", "65536",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser accepts a value of zero for the
// max-row-errors parameter.
TEST_F(DbAccessParserTest, zeroMaxRowErrors) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "max-row-errors", "0",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Zero max-row-errors", parser.getDbAccessParameters(),
                      config);
}

// This test checks that the parser accepts the valid value of the
// max-row-errors parameter.
TEST_F(DbAccessParserTest, validZeroMaxRowErrors) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "max-row-errors", "50",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid max-row-errors", parser.getDbAccessParameters(),
                      config);
}


// This test checks that the parser rejects the negative value of the
// max-row-errors parameter.
TEST_F(DbAccessParserTest, negativeMaxRowErrors) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "max-row-errors", "-1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// This test checks that the parser rejects a too large (greater than
// the max uint32_t) value of the max-row-errors parameter.
TEST_F(DbAccessParserTest, largeMaxRowErrors) {
    const char* config[] = {"type", "memfile",
                            "name", "/opt/var/lib/kea/kea-leases6.csv",
                            "max-row-errors", "4294967296",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// Check that the parser works with a valid MySQL configuration
TEST_F(DbAccessParserTest, validTypeMysql) {
    const char* config[] = {"type",     "mysql",
                            "host",     "erewhon",
                            "port",     "3306",
                            "user",     "kea",
                            "password", "keapassword",
                            "name",     "keatest",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Valid mysql", parser.getDbAccessParameters(), config);
}

// A missing 'type' keyword should cause an exception to be thrown.
TEST_F(DbAccessParserTest, missingTypeKeyword) {
    const char* config[] = {"host",     "erewhon",
                            "port",     "3306",
                            "user",     "kea",
                            "password", "keapassword",
                            "name",     "keatest",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// Check reconfiguration.  Checks that incremental changes applied to the
// database configuration are incremental.
TEST_F(DbAccessParserTest, incrementalChanges) {
    const char* config1[] = {"type", "memfile",
                             NULL};

    // Applying config2 will cause a wholesale change.
    const char* config2[] = {"type",     "mysql",
                             "host",     "erewhon",
                             "port",     "3306",
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
                             "port",     "3306",
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
                             "port",     "3306",
                             "user",     "them",
                             "password", "",
                             "name",     "keatest",
                             NULL};

    TestDbAccessParser parser;

    // First configuration string should cause a representation of that string
    // to be held.
    string json_config = toJson(config1);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Initial configuration", parser.getDbAccessParameters(),
                      config1);

    // Applying a wholesale change will cause the access string to change
    // to a representation of the new configuration.
    json_config = toJson(config2);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Subsequent configuration", parser.getDbAccessParameters(),
                      config2);

    // Applying an incremental change will cause the representation to change
    // incrementally.
    json_config = toJson(incremental2);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Incremental configuration", parser.getDbAccessParameters(),
                      config3);

    // Applying the next incremental change should cause an exception to be
    // thrown and there be no change to the access string.
    json_config = toJson(incremental3);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
    checkAccessString("Incompatible incremental change", parser.getDbAccessParameters(),
                      config3);

    // Applying an incremental change will cause the representation to change
    // incrementally.
    json_config = toJson(incremental4);
    json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    EXPECT_NO_THROW(parser.parse(json_elements));
    checkAccessString("Compatible incremental change", parser.getDbAccessParameters(),
                      config4);
}

// Check that the database access string is constructed correctly.
TEST_F(DbAccessParserTest, getDbAccessString) {
    const char* config[] = {"type",     "mysql",
                            "host",     "",
                            "name",     "keatest",
                            "password", "password with spaces",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));

    // Get the database access string
    std::string dbaccess = parser.getDbAccessString();

    // String should be either "type=mysql name=keatest" or
    // "name=keatest type=mysql". The "host" entry is null, so should not be
    // output.
    EXPECT_EQ(dbaccess, "name=keatest password='password with spaces' type=mysql");
}

// Check that the configuration is accepted for the valid value
// of "readonly".
TEST_F(DbAccessParserTest, validReadOnly) {
    const char* config[] = {"type", "mysql",
                            "user", "keatest",
                            "password", "keatest",
                            "name", "keatest",
                            "readonly", "true",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_NO_THROW(parser.parse(json_elements));

    checkAccessString("Valid readonly parameter",
                      parser.getDbAccessParameters(),
                      config);
}

// Check that for the invalid value of the "readonly" parameter
// an exception is thrown.
TEST_F(DbAccessParserTest, invalidReadOnly) {
    const char* config[] = {"type", "mysql",
                            "user", "keatest",
                            "password", "keatest",
                            "name", "keatest",
                            "readonly", "1",
                            NULL};

    string json_config = toJson(config);
    ConstElementPtr json_elements = Element::fromJSON(json_config);
    EXPECT_TRUE(json_elements);

    TestDbAccessParser parser;
    EXPECT_THROW(parser.parse(json_elements), DbConfigError);
}

// Check that multiple host storages are correctly parsed.
TEST_F(DbAccessParserTest, multipleHost) {
    const char* config1[] = {"type", "mysql",
                             "name", "keatest1",
                             NULL};
    const char* config2[] = {"type", "mysql",
                             "name", "keatest2",
                             NULL};

    string json_config1 = toJson(config1);
    string json_config2 = toJson(config2);
    ConstElementPtr json_elements1 = Element::fromJSON(json_config1);
    ConstElementPtr json_elements2 = Element::fromJSON(json_config2);

    TestDbAccessParser parser1;
    TestDbAccessParser parser2;
    EXPECT_NO_THROW(parser1.parse(json_elements1));
    EXPECT_NO_THROW(parser2.parse(json_elements2));

    checkAccessString("First config",
                      parser1.getDbAccessParameters(),
                      config1);
    checkAccessString("Second config",
                      parser2.getDbAccessParameters(),
                      config2);
}

};  // Anonymous namespace
