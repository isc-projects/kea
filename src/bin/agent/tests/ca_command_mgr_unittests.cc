// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_command_mgr.h>
#include <cc/command_interpreter.h>
#include <gtest/gtest.h>

using namespace isc::agent;
using namespace isc::data;

namespace {

/// @brief Test fixture class for @ref CtrlAgentCommandMgr.
///
/// @todo Add tests for various commands, including the cases when the
/// commands are forwarded to other servers via unix sockets.
/// Meanwhile, this is just a placeholder for the tests.
class CtrlAgentCommandMgrTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Deregisters all commands except 'list-commands'.
    CtrlAgentCommandMgrTest()
        : mgr_(CtrlAgentCommandMgr::instance()) {
        mgr_.deregisterAll();
    }

    /// @brief Destructor.
    ///
    /// Deregisters all commands except 'list-commands'.
    virtual ~CtrlAgentCommandMgrTest() {
        mgr_.deregisterAll();
    }

    /// @brief Verifies received answer
    ///
    /// @todo Add better checks for failure cases and for
    /// verification of the response parameters.
    ///
    /// @param answer answer to be verified
    /// @param expected_code code expected to be returned in the answer
    void checkAnswer(ConstElementPtr answer, int expected_code) {
        int status_code;
        // There may be multiple answers returned within a list.
        std::vector<ElementPtr> answer_list = answer->listValue();
        // There must be at least one answer.
        ASSERT_GE(answer_list.size(), 1);
        // Check that all answers indicate success.
        for (auto ans = answer_list.cbegin(); ans != answer_list.cend();
             ++ans) {
            ASSERT_NO_THROW(isc::config::parseAnswer(status_code, *ans));
            EXPECT_EQ(expected_code, status_code);
        }
    }

    /// @brief a convenience reference to control agent command manager
    CtrlAgentCommandMgr& mgr_;
};

/// Just a basic test checking that non-existent command is handled
/// properly.
TEST_F(CtrlAgentCommandMgrTest, bogus) {
    ConstElementPtr answer;
    EXPECT_NO_THROW(answer = mgr_.handleCommand("fish-and-chips-please",
                                                ConstElementPtr()));
    checkAnswer(answer, isc::config::CONTROL_RESULT_ERROR);
};

/// Just a basic test checking that 'list-commands' is supported.
TEST_F(CtrlAgentCommandMgrTest, listCommands) {
    ConstElementPtr answer;
    EXPECT_NO_THROW(answer = mgr_.handleCommand("list-commands",
                                                ConstElementPtr()));
    checkAnswer(answer, isc::config::CONTROL_RESULT_SUCCESS);
};


}
