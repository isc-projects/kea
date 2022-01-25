// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <testutils/user_context_utils.h>
#include <process/testutils/d_test_stubs.h>
#include <agent/ca_cfg_mgr.h>
#include <agent/parser_context.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "test_data_files_config.h"
#include "test_callout_libraries.h"

using namespace isc::agent;
using namespace isc::config;
using namespace isc::data;
using namespace isc::process;
using namespace isc::test;

namespace {

/// @name How to generate the testdata/get_config.json file
///
/// Define GENERATE_ACTION and recompile. Run ca_unittests on
/// CtrlAgentGetCfgTest redirecting the standard error to a temporary
/// file, e.g. by
/// @code
///    ./ca_unittests --gtest_filter="CtrlAgentGetCfg*" > /dev/null 2> u
/// @endcode
///
/// Update testdata/get_config.json using the temporary file content,
/// (removing head comment and restoring hook library path),
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
        ParserContext ctx;
        return (ctx.parseString(in, ParserContext::PARSER_JSON));
    } catch (const std::exception& ex) {
        if (verbose) {
            std::cout << "EXCEPTION: " << ex.what() << std::endl;
        }
        throw;
    }
}

/// @brief Runs parser in AGENT mode
ElementPtr
parseAGENT(const std::string& in,  bool verbose = false) {
    try {
        ParserContext ctx;
        return (ctx.parseString(in, ParserContext::PARSER_AGENT));
    } catch (const std::exception& ex) {
        if (verbose) {
            std::cout << "EXCEPTION: " << ex.what() << std::endl;
        }
        throw;
    }
}

/// @brief Replace the library path
void
pathReplacer(ConstElementPtr ca_cfg) {
    ConstElementPtr hooks_libs = ca_cfg->get("hooks-libraries");
    if (!hooks_libs || hooks_libs->empty()) {
        return;
    }
    ElementPtr first_lib = hooks_libs->getNonConst(0);
    std::string lib_path(CALLOUT_LIBRARY);
    first_lib->set("library", Element::create(lib_path));
}

/// @brief Replace the credential directory
void
dirReplacer(ConstElementPtr ca_cfg) {
    ConstElementPtr auth = ca_cfg->get("authentication");
    if (!auth || auth->empty()) {
        return;
    }
    ElementPtr mutable_auth = boost::const_pointer_cast<Element>(auth);
    std::string dir_path(CA_TEST_DATA_DIR);
    mutable_auth->set("directory", Element::create(dir_path));
}

/// @brief Almost regular agent CfgMgr with internal parse method exposed.
class NakedAgentCfgMgr : public CtrlAgentCfgMgr {
public:
    using CtrlAgentCfgMgr::parse;
};

}

/// Test fixture class
class CtrlAgentGetCfgTest : public ConfigParseTest {
public:
    CtrlAgentGetCfgTest()
    : rcode_(-1) {
        srv_.reset(new NakedAgentCfgMgr());
        // Create fresh context.
        resetConfiguration();
    }

    ~CtrlAgentGetCfgTest() {
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

        // try AGENT parser
        try {
            json = parseAGENT(config, true);
        } catch (...) {
            ADD_FAILURE() << "parsing failed for " << operation
                          << " on\n" << prettyPrint(json) << "\n";
            return (false);
        }

        // get Control-agent element
        ConstElementPtr ca = json->get("Control-agent");
        if (!ca) {
            ADD_FAILURE() << "cannot get Control-agent for " << operation
                          << " on\n" << prettyPrint(json) << "\n";
            return (false);
        }

        // update hooks-libraries
        pathReplacer(ca);

        // update authentication directory
        dirReplacer(ca);

        // try AGENT configure
        ConstElementPtr status;
        try {
            status = srv_->parse(ca, true);
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
    /// removing control sockets and hooks. Reset must
    /// be performed after each test to make sure that
    /// contents of the database do not affect result of
    /// subsequent tests.
    void resetConfiguration() {
        string config = "{ \"Control-agent\": {"
            " \"http-host\": \"\","
            " \"http-port\": 0 } }";
        EXPECT_TRUE(executeConfiguration(config, "reset config"));
    }

    boost::scoped_ptr<NakedAgentCfgMgr> srv_; ///< CA server under test
    int rcode_;                       ///< Return code from element parsing
    ConstElementPtr comment_;         ///< Reason for parse fail
};

/// Test a configuration
TEST_F(CtrlAgentGetCfgTest, simple) {

    // get the simple configuration
    std::string simple_file = string(CFG_EXAMPLES) + "/" + "simple.json";
    std::string config;
    ASSERT_NO_THROW(config = readFile(simple_file));

    // get the expected configuration
    std::string expected_file =
        std::string(CA_TEST_DATA_DIR) + "/" + "get_config.json";
    std::string expected;
    ASSERT_NO_THROW(expected = readFile(expected_file));

    // execute the sample configuration
    ASSERT_TRUE(executeConfiguration(config, "simple config"));

    // unparse it
    CtrlAgentCfgContextPtr context = srv_->getCtrlAgentCfgContext();
    ConstElementPtr unparsed;
    ASSERT_NO_THROW(unparsed = context->toElement());

    // dump if wanted else check
    if (generate_action) {
        std::cerr << "// Generated Configuration (remove this line)\n";
        ASSERT_NO_THROW(expected = prettyPrint(unparsed));
        prettyPrint(unparsed, std::cerr, 0, 4);
        std::cerr << "\n";
    } else {
        // get the expected config using the agent syntax parser
        ElementPtr jsond;
        ASSERT_NO_THROW(jsond = parseAGENT(expected, true));
        // get the expected config using the generic JSON syntax parser
        ElementPtr jsonj;
        ASSERT_NO_THROW(jsonj = parseJSON(expected));
        // the generic JSON parser does not handle comments
        EXPECT_TRUE(isEquivalent(jsond, moveComments(jsonj)));
        // replace the paths by their actual values
        ConstElementPtr ca;
        ASSERT_NO_THROW(ca = jsonj->get("Control-agent"));
        ASSERT_TRUE(ca);
        pathReplacer(ca);
        dirReplacer(ca);
        // check that unparsed and updated expected values match
        EXPECT_TRUE(isEquivalent(unparsed, jsonj));
        // check on pretty prints too
        std::string current = prettyPrint(unparsed, 0, 4);
        std::string expected2 = prettyPrint(jsonj, 0, 4);
        EXPECT_EQ(expected2, current);
        if (expected2 != current) {
            expected = current + "\n";
        }
    }

    // execute the control agent configuration
    EXPECT_TRUE(executeConfiguration(expected, "unparsed config"));

    // is it a fixed point?
    CtrlAgentCfgContextPtr context2 = srv_->getCtrlAgentCfgContext();
    ConstElementPtr unparsed2;
    ASSERT_NO_THROW(unparsed2 = context2->toElement());
    ASSERT_TRUE(unparsed2);
    EXPECT_TRUE(isEquivalent(unparsed, unparsed2));
}
