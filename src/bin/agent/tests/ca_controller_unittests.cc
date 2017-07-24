// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_controller.h>
#include <agent/ca_process.h>
#include <agent/ca_command_mgr.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <process/testutils/d_test_stubs.h>
#include <boost/pointer_cast.hpp>
#include <sstream>

using namespace std;
using namespace isc::agent;
using namespace isc::data;
using namespace isc::http;
using namespace isc::process;
using namespace boost::posix_time;

namespace {

/// @brief Valid Control Agent Config used in tests.
const char* valid_agent_config =
    "{"
    "  \"http-host\": \"127.0.0.1\","
    "  \"http-port\": 8081,"
    "  \"control-sockets\": {"
    "    \"dhcp4\": {"
    "      \"socket-type\": \"unix\","
    "      \"socket-name\": \"/first/dhcp4/socket\""
    "    },"
    "    \"dhcp6\": {"
    "      \"socket-type\": \"unix\","
    "      \"socket-name\": \"/first/dhcp6/socket\""
    "    }"
    "  }"
    "}";

/// @brief test fixture class for testing CtrlAgentController class. This
/// class derives from DControllerTest and wraps CtrlAgentController. Much
/// of the underlying functionality is in the DControllerBase class which
/// has extensive set of unit tests that are independent from the Control
/// Agent.
class CtrlAgentControllerTest : public DControllerTest {
public:

    /// @brief Constructor.
    CtrlAgentControllerTest()
        : DControllerTest(CtrlAgentController::instance) {
    }

    /// @brief Returns pointer to CtrlAgentProcess instance.
    CtrlAgentProcessPtr getCtrlAgentProcess() {
        return (boost::dynamic_pointer_cast<CtrlAgentProcess>(getProcess()));
    }

    /// @brief Returns pointer to CtrlAgentCfgMgr instance for a process.
    CtrlAgentCfgMgrPtr getCtrlAgentCfgMgr() {
        CtrlAgentCfgMgrPtr p;
        if (getCtrlAgentProcess()) {
            p = getCtrlAgentProcess()->getCtrlAgentCfgMgr();
        }
        return (p);
    }

    /// @brief Returns a pointer to the configuration context.
    CtrlAgentCfgContextPtr getCtrlAgentCfgContext() {
        CtrlAgentCfgContextPtr p;
        if (getCtrlAgentCfgMgr()) {
            p = getCtrlAgentCfgMgr()->getCtrlAgentCfgContext();
        }
        return (p);
    }

    /// @brief Tests that socket info structure contains 'unix' socket-type
    /// value and the expected socket-name.
    ///
    /// @param service Service type.
    /// @param exp_socket_name Expected socket name.
    void testUnixSocketInfo(const std::string& service,
                            const std::string& exp_socket_name) {
        CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
        ASSERT_TRUE(ctx);

        ConstElementPtr sock_info = ctx->getControlSocketInfo(service);
        ASSERT_TRUE(sock_info);
        ASSERT_TRUE(sock_info->contains("socket-type"));
        EXPECT_EQ("unix", sock_info->get("socket-type")->stringValue());
        ASSERT_TRUE(sock_info->contains("socket-name"));
        EXPECT_EQ(exp_socket_name,
                  sock_info->get("socket-name")->stringValue());
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
                     string exp_txt = "") {

        // Get rid of the outer list.
        ASSERT_TRUE(answer);
        ASSERT_EQ(Element::list, answer->getType());
        ASSERT_LE(1, answer->size());
        answer = answer->get(0);

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
    }

    /// @brief Checks whether specified command is registered
    ///
    /// @param name name of the command to be checked
    /// @param expect_true true - must be registered, false - must not be
    void checkCommandRegistered(const std::string& name, bool expect_true = true) {

        // First get the list of registered commands
        ConstElementPtr lst = Element::fromJSON("{ \"command\": \"list-commands\" }");
        ConstElementPtr rsp = CtrlAgentCommandMgr::instance().processCommand(lst);

        // The response must be an array with at least one element
        ASSERT_TRUE(rsp);
        ASSERT_EQ(Element::list, rsp->getType());
        ASSERT_LE(1, rsp->size());
        ConstElementPtr args = rsp->get(0)->get("arguments");
        ASSERT_TRUE(args);

        string args_txt = args->str();

        if (expect_true) {
            EXPECT_TRUE(args_txt.find(name) != string::npos);
        } else {
            EXPECT_TRUE(args_txt.find(name) == string::npos);
        }
    }

};

// Basic Controller instantiation testing.
// Verifies that the controller singleton gets created and that the
// basic derivation from the base class is intact.
TEST_F(CtrlAgentControllerTest, basicInstanceTesting) {
    // Verify the we can the singleton instance can be fetched and that
    // it is the correct type.
    DControllerBasePtr& controller = DControllerTest::getController();
    ASSERT_TRUE(controller);
    ASSERT_NO_THROW(boost::dynamic_pointer_cast<CtrlAgentController>(controller));

    // Verify that controller's app name is correct.
    EXPECT_TRUE(checkAppName(CtrlAgentController::agent_app_name_));

    // Verify that controller's bin name is correct.
    EXPECT_TRUE(checkBinName(CtrlAgentController::agent_bin_name_));

    // Verify that controller's IOService exists.
    EXPECT_TRUE(checkIOService());

    // Verify that the Process does NOT exist.
    EXPECT_FALSE(checkProcess());
}


// Tests basic command line processing.
// Verifies that:
// 1. Standard command line options are supported.
// 2. Invalid options are detected.
TEST_F(CtrlAgentControllerTest, commandLineArgs) {
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-c"),
                     const_cast<char*>(DControllerTest::CFG_TEST_FILE),
                     const_cast<char*>("-d") };
    int argc = 4;

    // Verify that verbose flag is false initially.
    EXPECT_TRUE(checkVerbose(false));

    // Verify that standard options can be parsed without error.
    EXPECT_NO_THROW(parseArgs(argc, argv));

    // Verify that verbose flag is true.
    EXPECT_TRUE(checkVerbose(true));

    // Verify configuration file name is correct.
    EXPECT_TRUE(checkConfigFileName(DControllerTest::CFG_TEST_FILE));

    // Verify that an unknown option is detected.
    char* argv2[] = { const_cast<char*>("progName"),
                      const_cast<char*>("-x") };
    argc = 2;
    EXPECT_THROW(parseArgs(argc, argv2), InvalidUsage);
}

// Tests application process creation and initialization.
// Verifies that the process can be successfully created and initialized.
TEST_F(CtrlAgentControllerTest, initProcessTesting) {
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());
}

// Tests launch and normal shutdown (stand alone mode).
// This creates an interval timer to generate a normal shutdown and then
// launches with a valid, stand-alone command line and no simulated errors.
TEST_F(CtrlAgentControllerTest, launchNormalShutdown) {
    // Write valid_agent_config and then run launch() for 1000 ms.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 1000, elapsed_time);

    // Give a generous margin to accommodate slower test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() >= 800 &&
                elapsed_time.total_milliseconds() <= 1300);
}

// Tests that the SIGINT triggers a normal shutdown.
TEST_F(CtrlAgentControllerTest, sigintShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGINT, 1);

    // Write valid_agent_config and then run launch() for a maximum
    // of 1000 ms.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 1000, elapsed_time);

    // Signaled shutdown should make our elapsed time much smaller than
    // the maximum run time.  Give generous margin to accommodate slow
    // test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);
}

// Tests that the SIGTERM triggers a normal shutdown.
TEST_F(CtrlAgentControllerTest, sigtermShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGTERM, 1);

    // Write valid_agent_config and then run launch() for a maximum of 1 s.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 1000, elapsed_time);

    // Signaled shutdown should make our elapsed time much smaller than
    // the maximum run time.  Give generous margin to accommodate slow
    // test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);
}

// Tests that the sockets settings are updated upon successful reconfiguration.
TEST_F(CtrlAgentControllerTest, successfulConfigUpdate) {
    // This configuration should be used to override the initial configuration.
    const char* second_config =
        "{"
        "  \"http-host\": \"127.0.0.1\","
        "  \"http-port\": 8080,"
        "  \"control-sockets\": {"
        "    \"dhcp4\": {"
        "      \"socket-type\": \"unix\","
        "      \"socket-name\": \"/second/dhcp4/socket\""
        "    },"
        "    \"dhcp6\": {"
        "      \"socket-type\": \"unix\","
        "      \"socket-name\": \"/second/dhcp6/socket\""
        "    }"
        "  }"
        "}";

    // Schedule reconfiguration.
    scheduleTimedWrite(second_config, 100);
    // Schedule SIGHUP signal to trigger reconfiguration.
    TimedSignal sighup(*getIOService(), SIGHUP, 200);

    // Start the server.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 500, elapsed_time);

    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
    ASSERT_TRUE(ctx);

    // The server should now hold the new listener configuration.
    EXPECT_EQ("127.0.0.1", ctx->getHttpHost());
    EXPECT_EQ(8080, ctx->getHttpPort());

    // The forwarding configuration should have been updated too.
    testUnixSocketInfo("dhcp4", "/second/dhcp4/socket");
    testUnixSocketInfo("dhcp6", "/second/dhcp6/socket");

    CtrlAgentProcessPtr process = getCtrlAgentProcess();
    ASSERT_TRUE(process);

    // Check that the HTTP listener still exists after reconfiguration.
    ConstHttpListenerPtr listener = process->getHttpListener();
    ASSERT_TRUE(listener);
    EXPECT_TRUE(process->isListening());

    // The listener should have been reconfigured to use new address and port.
    EXPECT_EQ("127.0.0.1", listener->getLocalAddress().toText());
    EXPECT_EQ(8080, listener->getLocalPort());
}

// Tests that the server continues to use an old configuration when the listener
// reconfiguration is unsuccessful.
TEST_F(CtrlAgentControllerTest, unsuccessfulConfigUpdate) {
    // This is invalid configuration. We're using restricted port number and
    // IP address of 1.1.1.1.
    const char* second_config =
        "{"
        "  \"http-host\": \"1.1.1.1\","
        "  \"http-port\": 1,"
        "  \"control-sockets\": {"
        "    \"dhcp4\": {"
        "      \"socket-type\": \"unix\","
        "      \"socket-name\": \"/second/dhcp4/socket\""
        "    },"
        "    \"dhcp6\": {"
        "      \"socket-type\": \"unix\","
        "      \"socket-name\": \"/second/dhcp6/socket\""
        "    }"
        "  }"
        "}";

    // Schedule reconfiguration.
    scheduleTimedWrite(second_config, 100);
    // Schedule SIGHUP signal to trigger reconfiguration.
    TimedSignal sighup(*getIOService(), SIGHUP, 200);

    // Start the server.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 500, elapsed_time);

    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
    ASSERT_TRUE(ctx);

    // The reconfiguration should have been unsuccessful, and the server should
    // still use the original configuration.
    EXPECT_EQ("127.0.0.1", ctx->getHttpHost());
    EXPECT_EQ(8081, ctx->getHttpPort());

    // Same for forwarding.
    testUnixSocketInfo("dhcp4", "/first/dhcp4/socket");
    testUnixSocketInfo("dhcp6", "/first/dhcp6/socket");

    CtrlAgentProcessPtr process = getCtrlAgentProcess();
    ASSERT_TRUE(process);

    // We should still be using an original listener.
    ConstHttpListenerPtr listener = process->getHttpListener();
    ASSERT_TRUE(listener);
    EXPECT_TRUE(process->isListening());

    EXPECT_EQ("127.0.0.1", listener->getLocalAddress().toText());
    EXPECT_EQ(8081, listener->getLocalPort());
}

// Tests that it is possible to update the configuration in such a way that the
// listener configuration remains the same. The server should continue using the
// listener instance it has been using prior to the reconfiguration.
TEST_F(CtrlAgentControllerTest, noListenerChange) {
    // This configuration should be used to override the initial configuration.
    const char* second_config =
        "{"
        "  \"http-host\": \"127.0.0.1\","
        "  \"http-port\": 8081,"
        "  \"control-sockets\": {"
        "    \"dhcp4\": {"
        "      \"socket-type\": \"unix\","
        "      \"socket-name\": \"/second/dhcp4/socket\""
        "    },"
        "    \"dhcp6\": {"
        "      \"socket-type\": \"unix\","
        "      \"socket-name\": \"/second/dhcp6/socket\""
        "    }"
        "  }"
        "}";

    // Schedule reconfiguration.
    scheduleTimedWrite(second_config, 100);
    // Schedule SIGHUP signal to trigger reconfiguration.
    TimedSignal sighup(*getIOService(), SIGHUP, 200);

    // Start the server.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 500, elapsed_time);

    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
    ASSERT_TRUE(ctx);

    // The server should use a correct listener configuration.
    EXPECT_EQ("127.0.0.1", ctx->getHttpHost());
    EXPECT_EQ(8081, ctx->getHttpPort());

    // The forwarding configuration should have been updated.
    testUnixSocketInfo("dhcp4", "/second/dhcp4/socket");
    testUnixSocketInfo("dhcp6", "/second/dhcp6/socket");

    CtrlAgentProcessPtr process = getCtrlAgentProcess();
    ASSERT_TRUE(process);

    // The listener should keep listening.
    ConstHttpListenerPtr listener = process->getHttpListener();
    ASSERT_TRUE(listener);
    EXPECT_TRUE(process->isListening());

    EXPECT_EQ("127.0.0.1", listener->getLocalAddress().toText());
    EXPECT_EQ(8081, listener->getLocalPort());
}

// Tests that registerCommands actually registers anything.
TEST_F(CtrlAgentControllerTest, registeredCommands) {
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // The framework available makes it very difficult to test the actual
    // code as CtrlAgentController is not initialized the same way it is
    // in production code. In particular, the way CtrlAgentController
    // is initialized in tests does not call registerCommands().
    // This is a crude workaround for this problem. Proper solution should
    // be developed sooner rather than later.
    const DControllerBasePtr& base = getController();
    const CtrlAgentControllerPtr& ctrl =
        boost::dynamic_pointer_cast<CtrlAgentController>(base);
    ASSERT_TRUE(ctrl);
    ctrl->registerCommands();

    // Check that the following command are really available.
    checkCommandRegistered("build-report");
    checkCommandRegistered("config-get");
    checkCommandRegistered("config-test");
    checkCommandRegistered("config-write");
    checkCommandRegistered("list-commands");
    checkCommandRegistered("shutdown");
    checkCommandRegistered("version-get");

    ctrl->deregisterCommands();
}

// Tests that config-write really writes a config file that contains
// Control-agent configuration and not some other random nonsense.
TEST_F(CtrlAgentControllerTest, configWrite) {
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // The framework available makes it very difficult to test the actual
    // code as CtrlAgentController is not initialized the same way it is
    // in production code. In particular, the way CtrlAgentController
    // is initialized in tests does not call registerCommands().
    // This is a crude workaround for this problem. Proper solution should
    // be developed sooner rather than later.
    const DControllerBasePtr& base = getController();
    const CtrlAgentControllerPtr& ctrl
        = boost::dynamic_pointer_cast<CtrlAgentController>(base);
    ASSERT_TRUE(ctrl);
    // Now clean up after ourselves.
    ctrl->registerCommands();

    // First, build the command:
    string file = string(TEST_DATA_BUILDDIR) + string("/config-write.json");
    string cmd_txt = "{ \"command\": \"config-write\" }";
    ConstElementPtr cmd = Element::fromJSON(cmd_txt);
    ConstElementPtr params = Element::fromJSON("{\"filename\": \"" + file + "\" }");
    CtrlAgentCommandMgr& mgr_ =  CtrlAgentCommandMgr::instance();

    // Send the command
    ConstElementPtr answer = mgr_.handleCommand("config-write", params, cmd);

    // Check that the command was successful
    checkAnswer(answer, isc::config::CONTROL_RESULT_SUCCESS);

    // Now check that the file is there.
    ifstream f(file.c_str());
    ASSERT_TRUE(f.good());

    // Now that's some rough check that the the config written really contains
    // something that looks like Control-agent configuration.
    ConstElementPtr from_file = Element::fromJSONFile(file, true);
    ASSERT_TRUE(from_file);
    ConstElementPtr ca = from_file->get("Control-agent");
    ASSERT_TRUE(ca);
    EXPECT_TRUE(ca->get("control-sockets"));
    EXPECT_TRUE(ca->get("hooks-libraries"));
    EXPECT_TRUE(ca->get("http-host"));
    EXPECT_TRUE(ca->get("http-port"));

    // Remove the file.
    ::remove(file.c_str());

    // Now clean up after ourselves.
    ctrl->deregisterCommands();
}

}
