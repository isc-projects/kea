// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/slaac_cfg_mgr.h>
#include <slaac/parser_context.h>
#include <exceptions/exceptions.h>
#include <cc/command_interpreter.h>
#include <process/testutils/d_test_stubs.h>
#include <process/d_cfg_mgr.h>
#include <testutils/test_to_element.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::slaac;
using namespace isc::config;
using namespace isc::data;
using namespace isc::process;

namespace  {

/// @brief Almost regular slaac CfgMgr with internal parse method exposed.
class NakedSlaacCfgMgr : public SlaacCfgMgr {
public:
    using SlaacCfgMgr::parse;
};

// Tests construction of SlaacCfgMgr class.
TEST(SlaacCfgMgr, construction) {
    boost::scoped_ptr<SlaacCfgMgr> cfg_mgr;

    // Verify that configuration manager constructions without error.
    ASSERT_NO_THROW(cfg_mgr.reset(new SlaacCfgMgr()));

    // Verify that the context can be retrieved and is not null.
    SlaacConfigPtr context;
    ASSERT_NO_THROW(context = cfg_mgr->getSlaacConfig());
    EXPECT_TRUE(context);

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(cfg_mgr.reset());
}

// Tests if getContext can be retrieved.
TEST(SlaacCfgMgr, getContext) {
    SlaacCfgMgr cfg_mgr;

    SlaacConfigPtr ctx;
    ASSERT_NO_THROW(ctx = cfg_mgr.getSlaacConfig());
    ASSERT_TRUE(ctx);
}

/// Slaac configurations used in tests.
const char* SLAAC_CONFIGS[] = {

    // configuration 0: empty (nothing specified)
    "{ }",

    // Configuration 1: global parameters only
    "{\n"
    "    \"hop-limit\": 64,\n"
    "    \"managed-flag\": true,\n"
    "    \"router-lifetime\": 1000\n"
    "}"
};

/// @brief Class used for testing CfgMgr
class SlaacParserTest : public isc::process::ConfigParseTest {
public:

    /// @brief Tries to load input text as a configuration
    ///
    /// @param config text containing input configuration
    /// @param expected_answer expected result of configuration (0 = success)
    void configParse(const char* config, int expected_answer) {
        isc::slaac::ParserContext parser;
        ConstElementPtr json = parser.parseString(config, ParserContext::PARSER_SUB_SLAAC);

        EXPECT_NO_THROW(answer_ = cfg_mgr_.parse(json, false));
        EXPECT_TRUE(checkAnswer(expected_answer));
    }

    /// Configuration Manager (used in tests)
    NakedSlaacCfgMgr cfg_mgr_;
};

// This test verifies if an empty config is handled properly. In practice such
// a config makes little sense, but perhaps it's ok for a default deployment.
TEST_F(SlaacParserTest, configParseEmpty) {
    configParse(SLAAC_CONFIGS[0], 0);

    SlaacConfigPtr ctx = cfg_mgr_.getSlaacConfig();
    ASSERT_TRUE(ctx);
}

}; // end of anonymous namespace
