// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cb_cmds_test.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <database/backend_selector.h>
#include <database/server_collection.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <set>
#include <string>
#include <sstream>

using namespace isc::cb;
using namespace isc::cb::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for callouts pertaining to DHCP server definitions.
class Server4CmdsTest : public ConfigCmdsDhcp4Test {
public:

    /// @brief Returns remote-server4-set command as text.
    ///
    /// @param server Pointer to the server to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makeServer4SetConfig(const ServerPtr& server,
                                     const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-server4-set\","
            "\"arguments\": {"
            "    \"servers\": [ { ";

        config += "\"server-tag\": \"" + server->getServerTagAsText() + "\"";
        if (!server->getDescription().empty()) {
            config += ", \"description\": \"" + server->getDescription() + "\"";
        }
        config += "} ] ";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for setting or updating a server.
    ///
    /// @param server Pointer to the server to be created or updated.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testServer4Set(const ServerPtr& server,
                        const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeServer4SetConfig(server, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setServer4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ("DHCPv4 server successfully set.", msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned list of servers.
        auto servers = args->get("servers");
        ASSERT_TRUE(servers);
        ASSERT_EQ(Element::list, servers->getType());
        ASSERT_EQ(1U, servers->size());

        auto server_0 = servers->get(0);
        ASSERT_TRUE(server_0);
        ASSERT_EQ(Element::map, server_0->getType());

        EXPECT_EQ(server->toElement()->str(), server_0->str());

        // Make sure that the created/updated server is in the database
        // and has correct values.
        auto fetched_server = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getServer4(BackendSelector(), server->getServerTag());
        ASSERT_TRUE(fetched_server);
        EXPECT_EQ(fetched_server->getServerTagAsText(),
                  server->getServerTagAsText());
        EXPECT_EQ(fetched_server->getDescription(), server->getDescription());
    }

    /// @brief Negative test scenario for setting or updating an option
    /// definition.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testServer4SetFail(const std::string& args,
                            const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-server4-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setServer4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        /// @todo Skipping line number possibly appended to the error message by
        /// the server parser. We should modify the parser to not
        /// output the position when used for control commands parsing.
        EXPECT_EQ(0U, answer->stringValue().find(answer_text))
            << "expected: " << answer_text
            << ", found: " << answer->stringValue();
    }

    /// @brief Returns remote-server4-del command as text.
    ///
    /// @param server Pointer to the server to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makeServer4DelConfig(const ServerPtr& server,
                                     const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-server4-del\","
            "\"arguments\": {"
            "    \"servers\": [ { ";

        config += "\"server-tag\": \"" + server->getServerTagAsText() + "\"";
        config += "} ] ";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for deleting a server.
    ///
    /// @param server Pointer to the server to be deleted.
    /// @param expected_count Expected number of deleted servers.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testServer4Del(const ServerPtr& server,
                        unsigned expected_count,
                        const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeServer4DelConfig(server, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delServer4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count
                     << " DHCPv4 server(s) deleted.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate count.
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected_count, static_cast<unsigned>(count->intValue()));

        // Make sure that the deleted server is not in the database.
        auto fetched_server = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getServer4(BackendSelector(), server->getServerTag());
        ASSERT_FALSE(fetched_server);
    }

    /// @brief Negative test scenario for deleting a server.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testServer4DelFail(const std::string& args,
                               const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-server4-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delServer4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-server4-get command as text.
    ///
    /// @param server Pointer to the server to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makeServer4GetConfig(const ServerPtr& server,
                                     const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-server4-get\","
            "\"arguments\": {"
            "    \"servers\": [ { ";

        config += "\"server-tag\": \"" + server->getServerTagAsText() + "\"";
        config += "} ] ";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for getting a server.
    ///
    /// @param server Pointer to the server to be got.
    /// @param expected Pointer to the expected server.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testServer4Get(const ServerPtr& server,
                        const ServerPtr& expected,
                        const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeServer4GetConfig(server, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::getServer4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (!expected ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "DHCPv4 server '"
                     << server->getServerTagAsText() << "' "
                     << (!expected ? "not " : "") << "found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned server.
        ConstElementPtr servers = args->get("servers");
        ASSERT_TRUE(servers);
        ASSERT_EQ(Element::list, servers->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (!expected) {
            EXPECT_EQ(0U, servers->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(1U, servers->size());
            EXPECT_EQ(1, count->intValue());

            ConstElementPtr got = servers->get(0);
            ASSERT_TRUE(got);
            ASSERT_EQ(Element::map, got->getType());
            EXPECT_EQ(expected->toElement()->str(), got->str());
        }
    }

    /// @brief Negative test scenario for getting a server.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testServer4GetFail(const std::string& args,
                               const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-server4-get\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::getServer4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-server4-get-all command as text.
    ///
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makeServer4GetAllConfig(const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-server4-get-all\"";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"arguments\": { ";

            // Only include remote if specified.
            if (!remote_map.empty()) {
                config += "\"remote\": " + remote_map;
            }
            config += " }";
        }
        config += "}";
        return (config);
    }

    /// @brief Positive test scenario for getting all servers.
    ///
    /// @param expected Expected result.
    /// @param expected_count Expected number of got servers.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testServer4GetAll(const ServerCollection& expected,
                           unsigned expected_count,
                           const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeServer4GetAllConfig(remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getAllServers4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count
                     << " DHCPv4 server(s) found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected_count, static_cast<unsigned>(count->intValue()));

        // Validate returned servers.
        ConstElementPtr servers = args->get("servers");
        ASSERT_TRUE(servers);
        ASSERT_EQ(Element::list, servers->getType());

        // Build the set of received servers
        std::set<std::string> got;
        for (auto const& server : servers->listValue()) {
            ASSERT_TRUE(server);
            got.insert(server->str());
        }
        EXPECT_EQ(expected_count, got.size());
        std::set<std::string> exp;
        for (auto const& server : expected) {
            ASSERT_TRUE(server);
            exp.insert(server->toElement()->str());
        }
        EXPECT_EQ(exp, got);
    }

    /// @brief Negative test scenario for getting all servers.
    ///
    /// @param args Arguments for the command in the textual format not
    /// including "arguments".
    /// @param answer_text Expected error message.
    void testServer4GetAllFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-server4-get-all\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getAllServers4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};


// This test verifies that it is possible to add and update server.
TEST_F(Server4CmdsTest, server4Set) {
    {
        SCOPED_TRACE("add new server");
        ServerPtr server = Server::create(ServerTag("foo"), "a server");
        testServer4Set(server);
    }

    {
        SCOPED_TRACE("add another server");
        ServerPtr server = Server::create(ServerTag("bar"));
        testServer4Set(server);
    }

    {
        SCOPED_TRACE("update existing server");
        ServerPtr server = Server::create(ServerTag("foo"), "changed server");
        testServer4Set(server);
    }

    {
        SCOPED_TRACE("update another server with specifying remote");
        ServerPtr server = Server::create(ServerTag("xyz"), "remote server");
        testServer4Set(server, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to add and update option
// definition are rejected and proper error messages are returned.
TEST_F(Server4CmdsTest, server4SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testServer4SetFail("", "invalid command 'remote-server4-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty server list");
        testServer4SetFail("\"servers\": [ ]", "'servers' list "
                           "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty server map");
        testServer4SetFail("\"servers\": [ { } ]",
                           "missing 'server-tag' parameter");
    }

    {
        SCOPED_TRACE("malformed server");
        testServer4SetFail("\"servers\": [ { \"name\": \"foo\" } ]",
                           "missing 'server-tag' parameter");
    }

    {
        SCOPED_TRACE("empty server tag");
        testServer4SetFail("\"servers\": ["
                           "{ \"server-tag\": \"\" } ]",
                           "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag");
        testServer4SetFail("\"servers\": ["
                           "{ \"server-tag\": \" \" } ]",
                           "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("too long server tag");
        std::ostringstream args;
        args << "\"servers\": ["
             << "{ \"server-tag\": \""
             << std::string(257, 'a')
             << "\" } ]";
        testServer4SetFail(args.str(),
                           "server-tag must not be longer than 256 characters");
    }

    {
        SCOPED_TRACE("multiple servers");
        testServer4SetFail("\"servers\": ["
                           "{ \"server-tag\": \"foo\" },"
                           "{ \"server-tag\": \"bar\" } ]",
                           "'servers' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testServer4SetFail("\"servers\": [ { \"server-tag\": \"foo\" } ],"
                           "\"remote\": {"
                           "    \"type\": \"postgresql\""
                           "}",
                           "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to delete server.
TEST_F(Server4CmdsTest, server4Del) {
    {
        SCOPED_TRACE("add and delete new server");
        ServerPtr server = Server::create(ServerTag("foo"), "a server");
        testServer4Set(server);
        testServer4Del(server, 1);
    }

    {
        SCOPED_TRACE("add and delete another server");
        ServerPtr server = Server::create(ServerTag("bar"));
        testServer4Set(server);
        testServer4Del(server, 1);
    }

    {
        SCOPED_TRACE("delete server");
        // Deleting not existing is not an error.
        ServerPtr server = Server::create(ServerTag("foo"), "does not exist");
        testServer4Del(server, 0);
    }

    {
        SCOPED_TRACE("delete another server with specifying remote");
        ServerPtr server = Server::create(ServerTag("foo"), "remote server");
        testServer4Set(server, "{ \"type\": \"mysql\" }");
        testServer4Del(server, 1, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to delete server
// are rejected and proper error messages are returned.
TEST_F(Server4CmdsTest, server4DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testServer4DelFail("", "invalid command 'remote-server4-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty server list");
        testServer4DelFail("\"servers\": [ ]", "'servers' list "
                           "must include exactly one element");
    }

    {
        SCOPED_TRACE("malformed server");
        testServer4DelFail("\"servers\": [ { \"name\": \"foo\" } ]",
                           "missing 'server-tag' parameter");
    }

    {
        SCOPED_TRACE("spurious parameter");
        testServer4DelFail("\"servers\": [ { \"server-tag\": \"foo\", "
                           "\"name\": \"foo\" } ]",
                           "spurious 'name' parameter");
    }

    {
        SCOPED_TRACE("empty server tag");
        testServer4DelFail("\"servers\": ["
                           "{ \"server-tag\": \"\" } ]",
                           "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag");
        testServer4DelFail("\"servers\": ["
                           "{ \"server-tag\": \" \" } ]",
                           "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("too long server tag");
        std::ostringstream args;
        args << "\"servers\": ["
             << "{ \"server-tag\": \""
             << std::string(257, 'a')
             << "\" } ]";
        testServer4DelFail(args.str(),
                           "server-tag must not be longer than 256 characters");
    }

    {
        SCOPED_TRACE("multiple servers");
        testServer4DelFail("\"servers\": ["
                           "{ \"server-tag\": \"foo\" },"
                           "{ \"server-tag\": \"bar\" } ]",
                           "'servers' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testServer4DelFail("\"servers\": [ { \"server-tag\": \"foo\" } ],"
                           "\"remote\": {"
                           "    \"type\": \"postgresql\""
                           "}",
                           "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get server.
TEST_F(Server4CmdsTest, server4Get) {
    {
        SCOPED_TRACE("add and get new server");
        ServerPtr server = Server::create(ServerTag("foo"), "a server");
        testServer4Set(server);
        testServer4Get(server, server);
    }

    {
        SCOPED_TRACE("add and get another server");
        ServerPtr server = Server::create(ServerTag("bar"));
        testServer4Set(server);
        testServer4Get(server, server);
    }

    {
        SCOPED_TRACE("get no server");
        // Getting not existing is not an error.
        ServerPtr server = Server::create(ServerTag("abc"), "does not exist");
        testServer4Get(server, ServerPtr());
    }

    {
        SCOPED_TRACE("delete another server with specifying remote");
        ServerPtr server = Server::create(ServerTag("xyz"), "remote server");
        testServer4Set(server, "{ \"type\": \"mysql\" }");
        testServer4Get(server, server, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to get server
// are rejected and proper error messages are returned.
TEST_F(Server4CmdsTest, server4GetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testServer4GetFail("", "invalid command 'remote-server4-get': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty server list");
        testServer4GetFail("\"servers\": [ ]", "'servers' list "
                           "must include exactly one element");
    }

    {
        SCOPED_TRACE("malformed server");
        testServer4GetFail("\"servers\": [ { \"name\": \"foo\" } ]",
                           "missing 'server-tag' parameter");
    }

    {
        SCOPED_TRACE("spurious parameter");
        testServer4GetFail("\"servers\": [ { \"server-tag\": \"foo\", "
                           "\"name\": \"foo\" } ]",
                           "spurious 'name' parameter");
    }

    {
        SCOPED_TRACE("empty server tag");
        testServer4GetFail("\"servers\": ["
                           "{ \"server-tag\": \"\" } ]",
                           "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag");
        testServer4GetFail("\"servers\": ["
                           "{ \"server-tag\": \" \" } ]",
                           "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("too long server tag");
        std::ostringstream args;
        args << "\"servers\": ["
             << "{ \"server-tag\": \""
             << std::string(257, 'a')
             << "\" } ]";
        testServer4GetFail(args.str(),
                           "server-tag must not be longer than 256 characters");
    }

    {
        SCOPED_TRACE("multiple servers");
        testServer4GetFail("\"servers\": ["
                           "{ \"server-tag\": \"foo\" },"
                           "{ \"server-tag\": \"bar\" } ]",
                           "'servers' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testServer4DelFail("\"servers\": [ { \"server-tag\": \"foo\" } ],"
                           "\"remote\": {"
                           "    \"type\": \"postgresql\""
                           "}",
                           "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get all servers.
TEST_F(Server4CmdsTest, server4GetAll) {
    // Empty.
    ServerCollection expected;
    testServer4GetAll(expected, 0);

    // Add a server.
    ServerPtr server = Server::create(ServerTag("foo"), "a server");
    testServer4Set(server);
    expected.insert(server);
    testServer4GetAll(expected, 1);

    // Add a second server.
    server = Server::create(ServerTag("bar"));
    testServer4Set(server);
    expected.insert(server);
    testServer4GetAll(expected, 2);

    // Try with a remote.
    server = Server::create(ServerTag("abc"), "remote server");
    testServer4Set(server, "{ \"type\": \"mysql\" }");
    expected.insert(server);
    testServer4GetAll(expected, 3, "{ \"type\": \"mysql\" }");
}

// This test verifies that malformed requests to get all servers
// are rejected and proper error messages are returned.
TEST_F(Server4CmdsTest, server4GetAllFail) {
    {
        SCOPED_TRACE("empty arguments");
        testServer4GetAllFail(", \"arguments\": { }",
                              "invalid command 'remote-server4-get-all': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testServer4GetAllFail(", \"arguments\": { "
                              "\"remote\": {"
                              "    \"type\": \"postgresql\""
                              "} }",
                              "no such database found for selector: "
                              "type=postgresql");
    }
}

}
