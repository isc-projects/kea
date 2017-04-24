// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_cfg_mgr.h>
#include <agent/ca_command_mgr.h>
#include <agent/ca_controller.h>
#include <agent/ca_process.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <process/testutils/d_test_stubs.h>
#include <util/threads/thread.h>
#include <boost/bind.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>
#include <cstdlib>
#include <vector>

using namespace isc::agent;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::process;

namespace {

/// @brief Test unix socket file name.
const std::string TEST_SOCKET = "test-socket";

/// @brief Test timeout in ms.
const long TEST_TIMEOUT = 10000;

/// @brief Test fixture class for @ref CtrlAgentCommandMgr.
///
/// @todo Add tests for various commands, including the cases when the
/// commands are forwarded to other servers via unix sockets.
/// Meanwhile, this is just a placeholder for the tests.
class CtrlAgentCommandMgrTest : public DControllerTest {
public:

    /// @brief Constructor.
    ///
    /// Deregisters all commands except 'list-commands'.
    CtrlAgentCommandMgrTest()
        : DControllerTest(CtrlAgentController::instance),
          mgr_(CtrlAgentCommandMgr::instance()) {
        mgr_.deregisterAll();
        removeUnixSocketFile();
        initProcess();
    }

    /// @brief Destructor.
    ///
    /// Deregisters all commands except 'list-commands'.
    virtual ~CtrlAgentCommandMgrTest() {
        mgr_.deregisterAll();
        removeUnixSocketFile();
    }

    /// @brief Verifies received answer
    ///
    /// @todo Add better checks for failure cases and for
    /// verification of the response parameters.
    ///
    /// @param answer answer to be verified
    /// @param expected_code0 code expected to be returned in first result within
    /// the answer.
    /// @param expected_code1 code expected to be returned in second result within
    /// the answer.
    /// @param expected_code2 code expected to be returned in third result within
    /// the answer.
    void checkAnswer(const ConstElementPtr& answer, const int expected_code0 = 0,
                     const int expected_code1 = -1, const int expected_code2 = -1) {
        std::vector<int> expected_codes;
        if (expected_code0 >= 0) {
            expected_codes.push_back(expected_code0);
        }

        if (expected_code1 >= 0) {
            expected_codes.push_back(expected_code1);
        }

        if (expected_code2 >= 0) {
            expected_codes.push_back(expected_code2);
        }

        int status_code;
        // There may be multiple answers returned within a list.
        std::vector<ElementPtr> answer_list = answer->listValue();

        ASSERT_EQ(expected_codes.size(), answer_list.size());
        // Check all answers.
        for (auto ans = answer_list.cbegin(); ans != answer_list.cend();
             ++ans) {
            ConstElementPtr text;
            ASSERT_NO_THROW(text = isc::config::parseAnswer(status_code, *ans));
            EXPECT_EQ(expected_codes[std::distance(answer_list.cbegin(), ans)],
                      status_code)
                << "answer contains text: " << text->stringValue();
        }
    }

    /// @brief Returns socket file path.
    ///
    /// If the KEA_SOCKET_TEST_DIR environment variable is specified, the
    /// socket file is created in the location pointed to by this variable.
    /// Otherwise, it is created in the build directory.
    static std::string unixSocketFilePath() {
        std::ostringstream s;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            s << std::string(env);
        } else {
            s << TEST_DATA_BUILDDIR;
        }

        s << "/" << TEST_SOCKET;
        return (s.str());
    }

    /// @brief Removes unix socket descriptor.
    void removeUnixSocketFile() {
        static_cast<void>(remove(unixSocketFilePath().c_str()));
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

    /// @brief Adds configuration of the control socket.
    ///
    /// @param server_type Server type for which socket configuration is to
    /// be added.
    void
    configureControlSocket(const CtrlAgentCfgContext::ServerType& server_type) {
        CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
        ASSERT_TRUE(ctx);

        ElementPtr control_socket = Element::createMap();
        control_socket->set("socket-name",
                            Element::create(unixSocketFilePath()));
        ctx->setControlSocketInfo(control_socket, server_type);
    }

    /// @brief Create and bind server side socket.
    ///
    /// @param response Stub response to be sent from the server socket to the
    /// client.
    void bindServerSocket(const std::string& response) {
        server_socket_.reset(new test::TestServerUnixSocket(*getIOService(),
                                                            unixSocketFilePath(),
                                                            TEST_TIMEOUT,
                                                            response));
        server_socket_->bindServerSocket();
    }

    /// @brief Creates command with no arguments.
    ///
    /// @param command_name Command name.
    /// @param service Service value to be added to the command. This value is
    /// specified as a list of comma separated values, e.g. "dhcp4, dhcp6".
    ///
    /// @return Pointer to the instance of the created command.
    ConstElementPtr createCommand(const std::string& command_name,
                                  const std::string& service) {
        ElementPtr command = Element::createMap();
        command->set("command", Element::create(command_name));

        // Only add the 'service' parameter if non-empty.
        if (!service.empty()) {
            std::string s = boost::replace_all_copy(service, ",", "\",\"");
            s = std::string("[ \"") + s + std::string("\" ]");
            command->set("service", Element::fromJSON(s));
        }

        command->set("arguments", Element::createMap());

        return (command);
    }

    /// @brief Test forwarding the command.
    ///
    /// @param server_type Server for which the client socket should be
    /// configured.
    /// @param service Service to be included in the command.
    /// @param expected_result0 Expected first result in response from the server.
    /// @param expected_result1 Expected second result in response from the server.
    /// @param expected_result2 Expected third result in response from the server.
    /// server socket after which the IO service should be stopped.
    /// @param expected_responses Number of responses after which the test finishes.
    /// @param server_response Stub response to be sent by the server.
    void testForward(const CtrlAgentCfgContext::ServerType& server_type,
                     const std::string& service,
                     const int expected_result0,
                     const int expected_result1 = -1,
                     const int expected_result2 = -1,
                     const size_t expected_responses = 1,
                     const std::string& server_response = "{ \"result\": 0 }") {
        // Configure client side socket.
        configureControlSocket(server_type);
        // Create server side socket.
        bindServerSocket(server_response);

        // The client side communication is synchronous. To be able to respond
        // to this we need to run the server side socket at the same time.
        // Running IO service in a thread guarantees that the server responds
        // as soon as it receives the control command.
        isc::util::thread::Thread th(boost::bind(&CtrlAgentCommandMgrTest::runIO,
                                                 getIOService(), server_socket_,
                                                 expected_responses));

        ConstElementPtr command = createCommand("foo", service);
        ConstElementPtr answer = mgr_.handleCommand("foo", ConstElementPtr(),
                                                    command);

        th.wait();

        checkAnswer(answer, expected_result0, expected_result1, expected_result2);
    }

    /// @brief Runs IO service until number of sent responses is lower than
    /// expected.
    ///
    /// @param server_socket Pointer to the server socket.
    /// @param expected_responses Number of expected responses.
    static void runIO(IOServicePtr& io_service,
                      const test::TestServerUnixSocketPtr& server_socket,
                      const size_t expected_responses) {
        while (server_socket->getResponseNum() < expected_responses) {
            io_service->run_one();
        }
    }


    CtrlAgentCommandMgrTest* getTestSelf() {
        return (this);
    }

    /// @brief a convenience reference to control agent command manager
    CtrlAgentCommandMgr& mgr_;

    /// @brief Pointer to the test server unix socket.
    test::TestServerUnixSocketPtr server_socket_;
};

/// Just a basic test checking that non-existent command is handled
/// properly.
TEST_F(CtrlAgentCommandMgrTest, bogus) {
    ConstElementPtr answer;
    EXPECT_NO_THROW(answer = mgr_.handleCommand("fish-and-chips-please",
                                                ConstElementPtr(),
                                                ConstElementPtr()));
    checkAnswer(answer, isc::config::CONTROL_RESULT_COMMAND_UNSUPPORTED);
};

/// Just a basic test checking that 'list-commands' is supported.
TEST_F(CtrlAgentCommandMgrTest, listCommands) {
    ConstElementPtr answer;
    EXPECT_NO_THROW(answer = mgr_.handleCommand("list-commands",
                                                ConstElementPtr(),
                                                ConstElementPtr()));
    checkAnswer(answer, isc::config::CONTROL_RESULT_SUCCESS);
};

/// Check that control command is successfully forwarded to the DHCPv4 server.
TEST_F(CtrlAgentCommandMgrTest, forwardToDHCPv4Server) {
    testForward(CtrlAgentCfgContext::TYPE_DHCP4, "dhcp4",
                isc::config::CONTROL_RESULT_SUCCESS);
}

/// Check that control command is successfully forwarded to the DHCPv6 server.
TEST_F(CtrlAgentCommandMgrTest, forwardToDHCPv6Server) {
    testForward(CtrlAgentCfgContext::TYPE_DHCP6, "dhcp6",
                isc::config::CONTROL_RESULT_SUCCESS);
}

/// Check that the same command is forwarded to multiple servers.
TEST_F(CtrlAgentCommandMgrTest, forwardToBothDHCPServers) {
    configureControlSocket(CtrlAgentCfgContext::TYPE_DHCP6);

    testForward(CtrlAgentCfgContext::TYPE_DHCP4, "dhcp4,dhcp6",
                isc::config::CONTROL_RESULT_SUCCESS,
                isc::config::CONTROL_RESULT_SUCCESS,
                -1, 2);
}

/// Check that the command may forwarded to the second server even if
/// forwarding to a first server fails.
TEST_F(CtrlAgentCommandMgrTest, failForwardToServer) {
    testForward(CtrlAgentCfgContext::TYPE_DHCP6, "dhcp4,dhcp6",
                isc::config::CONTROL_RESULT_ERROR,
                isc::config::CONTROL_RESULT_SUCCESS);
}

/// Check that control command is not forwarded if the service is not specified.
TEST_F(CtrlAgentCommandMgrTest, noService) {
    testForward(CtrlAgentCfgContext::TYPE_DHCP6, "",
                isc::config::CONTROL_RESULT_COMMAND_UNSUPPORTED,
                -1, -1, 0);
}

/// Check that error is returned to the client when the server to which the
/// command was forwarded sent an invalid message.
TEST_F(CtrlAgentCommandMgrTest, invalidAnswer) {
    testForward(CtrlAgentCfgContext::TYPE_DHCP6, "dhcp6",
                isc::config::CONTROL_RESULT_ERROR, -1, -1, 1,
                "{ \"result\": 0");
}

/// Check that error is returned to the client if the forwarding socket is
/// not configured for the given service.
TEST_F(CtrlAgentCommandMgrTest, noClientSocket) {
    ConstElementPtr command = createCommand("foo", "dhcp4");
    ConstElementPtr answer = mgr_.handleCommand("foo", ConstElementPtr(),
                                                command);

    checkAnswer(answer, isc::config::CONTROL_RESULT_ERROR);
}

/// Check that error is returned to the client if the remote server to
/// which the control command is to be forwarded is not available.
TEST_F(CtrlAgentCommandMgrTest, noServerSocket) {
    configureControlSocket(CtrlAgentCfgContext::TYPE_DHCP6);

    ConstElementPtr command = createCommand("foo", "dhcp6");
    ConstElementPtr answer = mgr_.handleCommand("foo", ConstElementPtr(),
                                                command);

    checkAnswer(answer, isc::config::CONTROL_RESULT_ERROR);
}

// Check that list-commands command is forwarded when the service
// value is specified.
TEST_F(CtrlAgentCommandMgrTest, forwardListCommands) {
    // Configure client side socket.
    configureControlSocket(CtrlAgentCfgContext::TYPE_DHCP4);
    // Create server side socket.
    bindServerSocket("{ \"result\" : 3 }");

    // The client side communication is synchronous. To be able to respond
    // to this we need to run the server side socket at the same time.
    // Running IO service in a thread guarantees that the server responds
    // as soon as it receives the control command.
    isc::util::thread::Thread th(boost::bind(&CtrlAgentCommandMgrTest::runIO,
                                             getIOService(), server_socket_, 1));

    ConstElementPtr command = createCommand("list-commands", "dhcp4");
    ConstElementPtr answer = mgr_.handleCommand("list-commands", ConstElementPtr(),
                                                command);

    th.wait();

    // Answer of 3 is specific to the stub response we send when the
    // command is forwarded. So having this value returned means that
    // the command was forwarded as expected.
    checkAnswer(answer, 3);
}

}
