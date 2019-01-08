// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <testutils/user_context_utils.h>
#include <process/testutils/d_test_stubs.h>
#include <d2/d2_config.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/parser_context.h>
#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "test_data_files_config.h"

using namespace isc::config;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::process;
using namespace isc::test;

namespace {

/// @name How to generate the testdata/get_config.json file
///
/// Define GENERATE_ACTION and recompile. Run d2_unittests on
/// D2GetConfigTest redirecting the standard error to a temporary
/// file, e.g. by
/// @code
///    ./d2_unittests --gtest_filter="D2GetConfig*" > /dev/null 2> u
/// @endcode
///
/// Update testdata/get_config.json using the temporary file content,
/// recompile without GENERATE_ACTION.

/// @brief the generate action
/// false means do nothing, true means unparse extracted configurations
#ifdef GENERATE_ACTION
const bool generate_action = true;
#else
const bool generate_action = false;
#endif

/// @brief Read a file into a string
std::string
readFile(const std::string& file_path) {
    std::ifstream ifs(file_path);
    if (!ifs.is_open()) {
        ADD_FAILURE() << "readFile cannot open " << file_path;
        isc_throw(isc::Unexpected, "readFile cannot open " << file_path);
    }
    std::string lines;
    std::string line;
    while (std::getline(ifs, line)) {
        lines += line + "\n";
    }
    ifs.close();
    return (lines);
}

/// @brief Runs parser in JSON mode
ElementPtr
parseJSON(const std::string& in,  bool verbose = false) {
    try {
        D2ParserContext ctx;
        return (ctx.parseString(in, D2ParserContext::PARSER_JSON));
    } catch (const std::exception& ex) {
        if (verbose) {
            std::cout << "EXCEPTION: " << ex.what() << std::endl;
        }
        throw;
    }
}

/// @brief Runs parser in DHCPDDNS mode
ElementPtr
parseDHCPDDNS(const std::string& in,  bool verbose = false) {
    try {
        D2ParserContext ctx;
        return (ctx.parseString(in, D2ParserContext::PARSER_DHCPDDNS));
    } catch (const std::exception& ex) {
        if (verbose) {
            std::cout << "EXCEPTION: " << ex.what() << std::endl;
        }
        throw;
    }
}

}

/// Test fixture class
class D2GetConfigTest : public ConfigParseTest {
public:
    D2GetConfigTest()
    : rcode_(-1) {
        srv_.reset(new D2CfgMgr());
        // Enforce not verbose mode.
        Daemon::setVerbose(false);
        // Create fresh context.
        resetConfiguration();
    }

    ~D2GetConfigTest() {
        resetConfiguration();
    }

    /// @brief Parse and Execute configuration
    ///
    /// Parses a configuration and executes a configuration of the server.
    /// If the operation fails, the current test will register a failure.
    ///
    /// @param config Configuration to parse
    /// @param operation Operation being performed.  In the case of an error,
    ///        the error text will include the string "unable to <operation>.".
    ///
    /// @return true if the configuration succeeded, false if not.
    bool
    executeConfiguration(const std::string& config, const char* operation) {
        // try JSON parser
        ConstElementPtr json;
        try {
            json = parseJSON(config, true);
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "invalid JSON for " << operation
                          << " failed with " << ex.what()
                          << " on\n" << config << "\n";
            return (false);
        }

        // try DHCPDDNS parser
        try {
            json = parseDHCPDDNS(config, true);
        } catch (...) {
            ADD_FAILURE() << "parsing failed for " << operation
                          << " on\n" << prettyPrint(json) << "\n";
            return (false);
        }

        // get DhcpDdns element
        ConstElementPtr d2 = json->get("DhcpDdns");
        if (!d2) {
            ADD_FAILURE() << "cannot get DhcpDdns for " << operation
                          << " on\n" << prettyPrint(json) << "\n";
            return (false);
        }

        // try DHCPDDNS configure
        ConstElementPtr status;
        try {
            status = srv_->simpleParseConfig(d2, false);
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "configure for " << operation
                          << " failed with " << ex.what()
                          << " on\n" << prettyPrint(json) << "\n";
            return (false);
        }

        // The status object must not be NULL
        if (!status) {
            ADD_FAILURE() << "configure for " << operation
                          << " returned null on\n"
                          << prettyPrint(json) << "\n";
            return (false);
        }

        // Returned value should be 0 (configuration success)
        comment_ = parseAnswer(rcode_, status);
        if (rcode_ != 0) {
            string reason = "";
            if (comment_) {
                reason = string(" (") + comment_->stringValue() + string(")");
            }
            ADD_FAILURE() << "configure for " << operation
                          << " returned error code "
                          << rcode_ << reason << " on\n"
                          << prettyPrint(json) << "\n";
            return (false);
        }
        return (true);
    }

    /// @brief Reset configuration database.
    ///
    /// This function resets configuration data base by
    /// removing control sockets and domain lists. Reset must
    /// be performed after each test to make sure that
    /// contents of the database do not affect result of
    /// subsequent tests.
    void resetConfiguration() {
        string config = "{ \"DhcpDdns\": {"
            " \"ip-address\": \"127.0.0.1\","
            " \"port\": 53001,"
            " \"dns-server-timeout\": 100,"
            " \"ncr-protocol\": \"UDP\","
            " \"ncr-format\": \"JSON\","
            " \"tsig-keys\": [ ],"
            " \"forward-ddns\": { },"
            " \"reverse-ddns\": { } } }";
        EXPECT_TRUE(executeConfiguration(config, "reset config"));
    }

    boost::scoped_ptr<D2CfgMgr> srv_;  ///< D2 server under test
    int rcode_;                        ///< Return code from element parsing
    ConstElementPtr comment_;          ///< Reason for parse fail
};

/// Test a configuration
TEST_F(D2GetConfigTest, sample1) {

    // get the sample1 configuration
    std::string sample1_file = string(CFG_EXAMPLES) + "/" + "sample1.json";
    std::string config;
    ASSERT_NO_THROW(config = readFile(sample1_file));

    // get the expected configuration
    std::string expected_file =
        std::string(D2_TEST_DATA_DIR) + "/" + "get_config.json";
    std::string expected;
    ASSERT_NO_THROW(expected = readFile(expected_file));

    // execute the sample configuration
    ASSERT_TRUE(executeConfiguration(config, "sample1 config"));

    // unparse it
    D2CfgContextPtr context = srv_->getD2CfgContext();
    ConstElementPtr unparsed;
    ASSERT_NO_THROW(unparsed = context->toElement());

    // dump if wanted else check
    if (generate_action) {
        std::cerr << "/ Generated Configuration (remove this line)\n";
        ASSERT_NO_THROW(expected = prettyPrint(unparsed));
        prettyPrint(unparsed, std::cerr, 0, 4);
        std::cerr << "\n";
    } else {
        // get the expected config using the d2 syntax parser
        ElementPtr jsond;
        ASSERT_NO_THROW(jsond = parseDHCPDDNS(expected, true));
        // get the expected config using the generic JSON syntax parser
        ElementPtr jsonj;
        ASSERT_NO_THROW(jsonj = parseJSON(expected));
        // the generic JSON parser does not handle comments
        EXPECT_TRUE(isEquivalent(jsond, moveComments(jsonj)));
        // check that unparsed and expected values match
        EXPECT_TRUE(isEquivalent(unparsed, jsonj));
        // check on pretty prints too
        std::string current = prettyPrint(unparsed, 0, 4) + "\n";
        EXPECT_EQ(expected, current);
        if (expected != current) {
            expected = current;
        }
    }

    // execute the d2 configuration
    EXPECT_TRUE(executeConfiguration(expected, "unparsed config"));

    // is it a fixed point?
    D2CfgContextPtr context2 = srv_->getD2CfgContext();
    ConstElementPtr unparsed2;
    ASSERT_NO_THROW(unparsed2 = context2->toElement());
    ASSERT_TRUE(unparsed2);
    EXPECT_TRUE(isEquivalent(unparsed, unparsed2));
}
