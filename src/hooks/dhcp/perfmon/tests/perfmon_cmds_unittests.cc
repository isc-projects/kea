// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PerfmonMgr class.
#include <config.h>
#include <perfmon_mgr.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/subnet.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <testutils/log_utils.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>
#include <util/boost_time_utils.h>

#include <gtest/gtest.h>
#include <list>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::perfmon;
using namespace isc::stats;
using namespace isc::test;
using namespace isc::util;
using namespace isc::dhcp::test;
using namespace boost::posix_time;

namespace {

/// @brief Test fixture for testing PerfMonMgr
class PerfMonCmdTest : public LogContentTest {
public:
    /// @brief Constructor.
    explicit PerfMonCmdTest(uint16_t family) : family_(family) {
        StatsMgr::instance();
        StatsMgr::instance().removeAll();
        StatsMgr::instance().setMaxSampleCountAll(1);
        if (family_ == AF_INET) {
            subnet22_.reset(new Subnet4(IOAddress("192.0.22.0"), 8, 100, 200, 300, 22));
            subnet33_.reset(new Subnet4(IOAddress("192.0.33.0"), 8, 100, 200, 300, 33));
        } else {
            subnet22_.reset(new Subnet6(IOAddress("3001:22::"), 64, 100, 200, 300, 300, 22));
            subnet33_.reset(new Subnet6(IOAddress("3002:33::"), 64, 100, 200, 300, 300, 33));
        }
    }

    void SetUp() {
        std::string valid_config =
            R"({
                    "enable-monitoring": false,
                    "interval-width-secs": 5000,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 600000,
                    "alarms": [{
                            "duration-key": {
                                "query-type": "",
                                "response-type": "",
                                "start-event": "process-started",
                                "stop-event": "process-completed",
                                "subnet-id": 70
                                },
                            "enable-alarm": true,
                            "high-water-ms": 500,
                            "low-water-ms": 25
                        }]
                })";

        ASSERT_NO_THROW_LOG(createMgr(valid_config));
    }

    /// @brief Destructor.
    virtual ~PerfMonCmdTest() = default;

    /// @brief Re-creates and then configures the PerfMonMgr instance with a
    /// given configuration.
    ///
    /// @param config JSON configuration text
    void createMgr(const std::string& config) {
        mgr_.reset(new PerfMonMgr(family_));
        ConstElementPtr json_elements;
        json_elements = Element::fromJSON(config);
        mgr_->configure(json_elements);
    }

    /// @brief Adds durations to the store.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6.
    void addDurations(uint16_t family) {
        // Create two keys where the stop event for the first key is the start
        // event for the second key.
        DurationKeyPtr key1(new DurationKey(family, 0, 0, "socket_received", "buffer_read", 1));
        DurationKeyPtr key2(new DurationKey(family, 0, 0, "buffer_read", "process_started", 1));

        // Make multiple calls to addDurationSample() for each key, starting with key1.
        auto store = mgr_->getDurationStore();
        ASSERT_TRUE(store);
        for (int i = 0; i < 4; ++i) {
            ASSERT_NO_THROW_LOG(store->addDurationSample(key1, milliseconds(1)));
            ASSERT_NO_THROW_LOG(store->addDurationSample(key2, milliseconds(2)));
        }
    }

    /// @brief Tests specified command and verifies response.
    ///
    /// This method processes supplied command by invoking the
    /// corresponding PerfMonMgr command handler and checks
    /// if the expected response was returned.
    ///
    /// @param cmd_txt JSON text command to be sent (must be valid JSON)
    /// @param exp_result 0 - success, 1 - error, 2 - ...
    /// @param exp_txt expected text response (optional)
    /// @return full response returned by the command execution.
    ConstElementPtr testCommand(string cmd_txt, int exp_result, string exp_txt,
                                ConstElementPtr exp_args = ConstElementPtr()) {
        ConstElementPtr cmd;
        EXPECT_NO_THROW(cmd = Element::fromJSON(cmd_txt));
        if (!cmd) {
            ADD_FAILURE() << cmd_txt << " is not a valid JSON, test broken";
            return (ConstElementPtr());
        }
        return (testCommand(cmd, exp_result, exp_txt, exp_args));
    }

    /// @brief Tests specified command and verifies response.
    ///
    /// This method processes supplied command by invoking the
    /// corresponding PerfMonMgr command handler.
    ///
    /// @param cmd JSON command to be sent
    /// @param exp_result 0 - success, 1 - error, 2 - ...
    /// @param exp_txt expected text response (optional)
    /// @return full response returned by the command execution.
    ConstElementPtr testCommand(ConstElementPtr cmd,
                                int exp_result,
                                string exp_txt,
                                ConstElementPtr exp_args = ConstElementPtr()) {
        string cmd_txt("...");
        if (cmd) {
            cmd_txt = prettyPrint(cmd);
        }
        SCOPED_TRACE(cmd_txt);

        // Command must be a map.
        if (!cmd || (cmd->getType() != Element::map)) {
            ADD_FAILURE() << cmd_txt << " is not a map, test broken";
            return (ConstElementPtr());
        }

        // We need to extract command name to select appropriate handler.
        ConstElementPtr command_element = cmd->get("command");
        if (!command_element || (command_element->getType() != Element::string)) {
            ADD_FAILURE() << cmd_txt << " does not contain command parameter";
            return (ConstElementPtr());
        }

        // Command name found.
        std::string command_name = command_element->stringValue();

        // Need to encapsulate the command in CalloutHandle.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("command", cmd);

        // Run the command handler appropriate for the given command name.
        if (command_name == "perfmon-control") {
            static_cast<void>(mgr_->perfmonControlHandler(*callout_handle));
        } else if (command_name == "perfmon-get-all-durations") {
            static_cast<void>(mgr_->perfmonGetAllDurationsHandler(*callout_handle));
        } else {
            ADD_FAILURE() << "unrecognized command '" << command_name << "'";
        }

        // Get the response.
        ConstElementPtr rsp;
        callout_handle->getArgument("response", rsp);

        // Response must be present.
        if (!rsp) {
            ADD_FAILURE() << "no response returned for command '"
                          << command_name << "'";
            return (ConstElementPtr());
        }

        // Verify the response against expected values.
        checkAnswer(rsp, exp_result, exp_txt, exp_args);

        return (rsp);
    }

    /// @brief Compares the status in the given parse result to a given value.
    ///
    /// @param answer Element set containing an integer response and string
    /// comment.
    /// @param exp_status is an integer against which to compare the status.
    /// @param exp_txt is expected text (not checked if "")
    ///
    void checkAnswer(isc::data::ConstElementPtr answer,
                     int exp_status,
                     string exp_txt = "",
                     ConstElementPtr exp_args = ConstElementPtr()) {
        int rcode = 0;
        isc::data::ConstElementPtr comment;
        comment = isc::config::parseAnswer(rcode, answer);

        if (rcode != exp_status) {
            ADD_FAILURE() << "Expected status code " << exp_status
                          << " but received " << rcode << ", comment: "
                          << (comment ? comment->str() : "(none)");
        }

        // Ok, parseAnswer interface is weird. If there are no arguments,
        // it returns content of text. But if there is an argument,
        // it returns the argument and it's not possible to retrieve
        // "text" (i.e. comment).
        if (comment->getType() != Element::string) {
            comment = answer->get("text");
        }

        if (!exp_txt.empty()) {
            EXPECT_EQ(exp_txt, comment->stringValue());
        }

        if (exp_args) {
            ConstElementPtr args = answer->get("arguments");
            ASSERT_TRUE(args);
            EXPECT_EQ(*exp_args, *args);
        }
    }

    /// @brief Verify that invalid perfmon-control commands are caught.
    void testInvalidPerfMonControl() {
        struct Scenario {
            int line_;              // Scenario line number
            std::string cmd_;       // JSON command text
            int exp_result_;        // Expected result code
            std::string exp_text_;  // Expected result text
        };

        std::list<Scenario> scenarios = {
            {
                __LINE__,
                R"({
                    "command": "perfmon-control",
                    "arguments": {
                        "enable-monitoring": "bogus"
                    }
                })",
                CONTROL_RESULT_ERROR,
                "'enable-monitoring' parameter is not a boolean"
            },
            {
                __LINE__,
                R"({
                    "command": "perfmon-control",
                    "arguments": {
                        "bogus": 23
                    }
                })",
                CONTROL_RESULT_ERROR,
                "spurious 'bogus' parameter"
            }
        };

        for (const auto& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());
            ConstElementPtr answer = testCommand(scenario.cmd_,
                                                 scenario.exp_result_,
                                                 scenario.exp_text_);
        }
    }

    /// @brief Verify that valid perfmon-control are processed correctly.
    void testValidPerfMonControl() {
        struct Scenario {
            int line_;                      // Scenario line number
            std::string cmd_;               // JSON command text
            int exp_result_;                // Expected result code
            std::string exp_text_;          // Expected result text
            bool exp_monitor_enabled_;      // Expected state of monitoring
            bool exp_stats_mgr_reporting_;  // Expected state of monitoring
        };

        // Verify that monitoring is enabled.
        ASSERT_EQ(mgr_->getEnableMonitoring(), false);

        // Define valid scenarios.
        std::list<Scenario> scenarios = {
            {
                // No arguments element should be ok.
                __LINE__,
                R"({
                    "command": "perfmon-control"
                })",
                CONTROL_RESULT_SUCCESS,
                "perfmon-control success",
                false,
                false
            },
            {
                // Empty arguments element should be ok.
                __LINE__,
                R"({
                    "command": "perfmon-control",
                    "arguments": {
                    }
                })",
                CONTROL_RESULT_SUCCESS,
                "perfmon-control success",
                false,
                false
            },
            {
                // Only enable-monitoring should be ok.
                __LINE__,
                R"({
                    "command": "perfmon-control",
                    "arguments": {
                        "enable-monitoring": true
                    }
                })",
                CONTROL_RESULT_SUCCESS,
                "perfmon-control success",
                true,
                false
            },
            {
                // Only stats-mgr-reporting should be ok.
                __LINE__,
                R"({
                    "command": "perfmon-control",
                    "arguments": {
                        "stats-mgr-reporting": true
                    }
                })",
                CONTROL_RESULT_SUCCESS,
                "perfmon-control success",
                true,
                true
            },
            {
                // Both enable-monitoring and stats-mgr-reporting should be ok.
                __LINE__,
                R"({
                    "command": "perfmon-control",
                    "arguments": {
                        "enable-monitoring": false,
                        "stats-mgr-reporting": false
                    }
                })",
                CONTROL_RESULT_SUCCESS,
                "perfmon-control success",
                false,
                false
            }
        };

        for (const auto& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());
            ElementPtr exp_args(Element::createMap());
            exp_args->set("enable-monitoring",
                          Element::create(scenario.exp_monitor_enabled_));
            exp_args->set("stats-mgr-reporting",
                          Element::create(scenario.exp_stats_mgr_reporting_));
            ConstElementPtr answer = testCommand(scenario.cmd_,
                                                 scenario.exp_result_,
                                                 scenario.exp_text_,
                                                 exp_args);

            EXPECT_EQ(mgr_->getEnableMonitoring(), scenario.exp_monitor_enabled_);
            EXPECT_EQ(mgr_->getStatsMgrReporting(), scenario.exp_stats_mgr_reporting_);
        }
    }

    /// @brief Verify that invalid perfmon-get-all-durations commands are caught.
    void testInvalidPerfMonGetAllDurations() {
        struct Scenario {
            int line_;              // Scenario line number
            std::string cmd_;       // JSON command text
            int exp_result_;        // Expected result code
            std::string exp_text_;  // Expected result text
        };

        std::list<Scenario> scenarios = {
            {
                __LINE__,
                R"({
                    "command": "perfmon-get-all-durations",
                    "arguments": {
                        "result-set-format": "bogus"
                    }
                })",
                CONTROL_RESULT_ERROR,
                "'result-set-format' parameter is not a boolean"
            },
            {
                __LINE__,
                R"({
                    "command": "perfmon-get-all-durations",
                    "arguments": {
                        "bogus": 23
                    }
                })",
                CONTROL_RESULT_ERROR,
                "spurious 'bogus' parameter"
            }
        };

        for (const auto& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());
            ConstElementPtr answer = testCommand(scenario.cmd_,
                                                 scenario.exp_result_,
                                                 scenario.exp_text_);
        }
    }

    /// @brief Veriies that a valid perfmon-get-all-durations command with
    /// result-set-format set false, returns all durations correctly.
    void testPerfMonGetAllDurationsResultSetFalse() {
        std::string now_str = ptimeToText(PktEvent::now());
        std::string cmd =
                R"({
                    "command": "perfmon-get-all-durations",
                    "arguments": {
                        "result-set-format": false
                    }
                })";

        addDurations(family_);

        auto ref_durations = mgr_->getDurationStore()->getAll();
        auto ref_time = PktEvent::now();
        std::ostringstream oss;
        oss << "perfmon-get-all-durations: " << ref_durations->size() << " found";
        ConstElementPtr answer = testCommand(cmd, CONTROL_RESULT_SUCCESS, oss.str());

        checkAnswerAgainstDurations(ref_durations, answer, ref_time, false);
    }

    /// @brief Veriies that a valid perfmon-get-all-durations with result-set-format
    /// set true, returns all durations correctly.
    void testPerfMonGetAllDurationsResultSetTrue() {
        std::string now_str = ptimeToText(PktEvent::now());
        std::string cmd =
                R"({
                    "command": "perfmon-get-all-durations",
                    "arguments": {
                        "result-set-format": true
                    }
                })";

        addDurations(family_);
        auto ref_durations = mgr_->getDurationStore()->getAll();
        ASSERT_TRUE(ref_durations);

        auto ref_time = PktEvent::now();
        std::ostringstream oss;
        oss << "perfmon-get-all-durations: " << ref_durations->size() << " found";
        ConstElementPtr answer = testCommand(cmd, CONTROL_RESULT_SUCCESS, oss.str());

        checkAnswerAgainstDurations(ref_durations, answer, ref_time, true);
    }

    /// @brief Verifies that the command response content against a list of
    /// MonitoredDurations and the expected format.
    ///
    /// @param ref_durations list of expected MonitoredDurations in the order they
    /// should appear in the results.
    /// @param anwswer complete command answer to check
    /// @param ref_time timestamp used to compare againt the "timestamp" in the answer.
    /// @param result_set_format expected format style of the answer
    void checkAnswerAgainstDurations(const MonitoredDurationCollectionPtr ref_durations,
                                    ConstElementPtr answer,
                                    const Timestamp& ref_time,
                                    bool result_set_format) {
        // Sanity check.
        ASSERT_TRUE(ref_durations);
        auto ref_count = ref_durations->size();
        ASSERT_TRUE(answer);

        // Verify content as either list elements or result-set.
        if (!result_set_format) {
            auto durations_list = answer->find("arguments/durations");
            ASSERT_TRUE(durations_list);
            EXPECT_EQ(ref_count, durations_list->size());

            int i = 0;
            for (const auto& ref_duration : *ref_durations) {
                auto duration_elem = durations_list->get(i);
                ASSERT_TRUE(duration_elem);
                EXPECT_EQ(*(duration_elem), *(ref_duration->toElement()));
                ++i;
            }
        } else {
            auto elem = answer->find("arguments/result-set-format");
            ASSERT_TRUE(elem);
            ASSERT_TRUE(elem->boolValue());

            auto result_set = answer->find("arguments/durations-result-set");
            ASSERT_TRUE(result_set);
            auto columns = result_set->find("columns");
            ASSERT_TRUE(columns);
            EXPECT_EQ(*columns, *MonitoredDuration::valueRowColumns());

            auto rows = result_set->find("rows");
            ASSERT_TRUE(rows);

            int i = 0;
            for (const auto& ref_duration : *ref_durations) {
                auto row  = rows->get(i);
                ASSERT_TRUE(row);
                EXPECT_EQ(*row, *(ref_duration->toValueRow()));
                ++i;
            }
        }

        auto elem = answer->find("arguments/interval-width-secs");
        ASSERT_TRUE(elem);
        EXPECT_EQ(mgr_->getIntervalWidthSecs(), elem->intValue());

        elem = answer->find("arguments/timestamp");
        ASSERT_TRUE(elem);
        EXPECT_GE(elem->stringValue(), ptimeToText(ref_time));
    }

    /// @brief Protocol family AF_INET or AF_INET6
    uint16_t family_;

    /// @brief PerfMonMgr instance used in test functions.
    PerfMonMgrPtr mgr_;

    /// @brief Family specific subnets.
    SubnetPtr subnet22_;
    SubnetPtr subnet33_;
};

/// @brief Test fixture for testing PerfMonConfig for DHCPV4.
class PerfMonCmdTest4: public PerfMonCmdTest {
public:
    /// @brief Constructor.
    explicit PerfMonCmdTest4() : PerfMonCmdTest(AF_INET) {
    }

    /// @brief Destructor.
    virtual ~PerfMonCmdTest4() = default;
};

/// @brief Test fixture for testing PerfMonConfig for DHCPV6.
class PerfMonCmdTest6: public PerfMonCmdTest {
public:
    /// @brief Constructor.
    explicit PerfMonCmdTest6() : PerfMonCmdTest(AF_INET6) {
    }

    /// @brief Destructor.
    virtual ~PerfMonCmdTest6() = default;
};

TEST_F(PerfMonCmdTest4, invalidPerfMonControl) {
    testInvalidPerfMonControl();
}

TEST_F(PerfMonCmdTest6, invalidPerfMonControl) {
    testInvalidPerfMonControl();
}

TEST_F(PerfMonCmdTest4, validPerfMonControl) {
    testValidPerfMonControl();
}

TEST_F(PerfMonCmdTest6, validPerfMonControl) {
    testValidPerfMonControl();
}

TEST_F(PerfMonCmdTest4, invalidPerfMonGetAllDurations) {
    testInvalidPerfMonGetAllDurations();
}

TEST_F(PerfMonCmdTest6, invalidPerfMonGetAllDurations) {
    testInvalidPerfMonGetAllDurations();
}

TEST_F(PerfMonCmdTest4, perfMonGetAllDurationsResultSetFalse) {
    testPerfMonGetAllDurationsResultSetFalse();
}

TEST_F(PerfMonCmdTest4, perfMonGetAllDurationsResultSetTrue) {
    testPerfMonGetAllDurationsResultSetTrue();
}

TEST_F(PerfMonCmdTest6, perfMonGetAllDurationsResultSetFalse) {
    testPerfMonGetAllDurationsResultSetFalse();
}

TEST_F(PerfMonCmdTest6, perfMonGetAllDurationsResultSetTrue) {
    testPerfMonGetAllDurationsResultSetTrue();
}

} // end of anonymous namespace
