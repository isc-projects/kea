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
    /// @param service Service value to be added to the command. If this value
    /// holds an empty string, the service parameter is not added.
    ///
    /// @return Pointer to the instance of the created command.
    ConstElementPtr createCommand(const std::string& command_name,
                                  const std::string& service) {
        ElementPtr command = Element::createMap();

        command->set("command", Element::create(command_name));

        // Only add the 'service' parameter if non-empty.
        if (!service.empty()) {
            ElementPtr services = Element::createList();
            services->add(Element::create(service));
            command->set("service", services);
        }

        command->set("arguments", Element::createMap());

        return (command);
    }

    /// @brief Test forwarding the command.
    ///
    /// @param server_type Server for which the client socket should be
    /// configured.
    /// @param service Service to be included in the command.
    /// @param expected_result Expected result in response from the server.
    /// @param server_response Stub response to be sent by the server.
    void testForward(const CtrlAgentCfgContext::ServerType& server_type,
                     const std::string& service,
                     const int expected_result,
                     const std::string& server_response = "{ \"result\": 0 }") {
        // Configure client side socket.
        configureControlSocket(server_type);
        // Create server side socket.
        bindServerSocket(server_response);

        // The client side communication is synchronous. To be able to respond
        // to this we need to run the server side socket at the same time.
        // Running IO service in a thread guarantees that the server responds
        // as soon as it receives the control command.
        isc::util::thread::Thread(boost::bind(&IOService::run,
                                              getIOService().get()));

        ConstElementPtr command = createCommand("foo", service);
        ConstElementPtr answer = mgr_.handleCommand("foo", ConstElementPtr(),
                                                    command);

        checkAnswer(answer, expected_result);
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

/// Check that control command is not forwarded if the service is not specified.
TEST_F(CtrlAgentCommandMgrTest, noService) {
    testForward(CtrlAgentCfgContext::TYPE_DHCP6, "",
                isc::config::CONTROL_RESULT_COMMAND_UNSUPPORTED);
}

/// Check that error is returned to the client when the server to which the
/// command was forwarded sent an invalid message.
TEST_F(CtrlAgentCommandMgrTest, invalidAnswer) {
    testForward(CtrlAgentCfgContext::TYPE_DHCP6, "dhcp6",
                isc::config::CONTROL_RESULT_ERROR,
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
    isc::util::thread::Thread(boost::bind(&IOService::run,
                                          getIOService().get()));

    ConstElementPtr command = createCommand("list-commands", "dhcp4");
    ConstElementPtr answer = mgr_.handleCommand("list-commands", ConstElementPtr(),
                                                command);

    // Answer of 3 is specific to the stub response we send when the
    // command is forwarded. So having this value returned means that
    // the command was forwarded as expected.
    checkAnswer(answer, 3);
}

}
