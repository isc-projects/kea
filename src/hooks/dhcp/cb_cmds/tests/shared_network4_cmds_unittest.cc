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
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcp/option_string.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <set>
#include <string>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::cb;
using namespace isc::cb::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;

namespace {

/// @brief Test fixture class for callouts pertaining to shared networks.
class SharedNetwork4CmdsTest : public ConfigCmdsDhcp4Test {
public:

    /// @brief Adds subnet to the configuration backend.
    ///
    /// @param subnet Pointer to the subnet to be stored.
    void setSubnet(const Subnet4Ptr& subnet) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateSubnet4(BackendSelector(), ServerSelector::ALL(), subnet);
    }

    /// @brief Adds unassigned shared network in the configuration backend.
    ///
    /// @param shared_network Pointer to the shared network to be stored.
    void setSharedNetwork(const SharedNetwork4Ptr& shared_network) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateSharedNetwork4(BackendSelector(),
                                       ServerSelector::UNASSIGNED(),
                                       shared_network);
    }

    /// @brief Returns remote-network4-set command as text.
    ///
    /// @param shared_network Pointer to the shared network to be used in the
    /// command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeSharedNetwork4SetConfig(const SharedNetwork4Ptr& shared_network,
                                            const std::string& remote_map,
                                            const std::set<std::string>& server_tags) {
        ElementPtr sn_element = shared_network->toElement();
        sn_element->remove("subnet4");

        std::string config = "{"
            "\"command\": \"remote-network4-set\","
            "\"arguments\": {"
            "    \"shared-networks\": [";

        config += sn_element->str() + "]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // Only include server tags if specified.
        if (!server_tags.empty()) {
            config += ", \"server-tags\": [";
            for (auto const& tag : server_tags) {
                config += "\"" + tag + "\",";
            }
            // Remove extraneous comma.
            config.pop_back();
            config += "]";
        }

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for setting or updating shared network.
    ///
    /// @param shared_network Pointer to the shared network to be created or
    /// updated.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testSharedNetwork4Set(const SharedNetwork4Ptr& shared_network,
                               const std::string& remote_map = "",
                               const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeSharedNetwork4SetConfig(shared_network,
                                                               remote_map,
                                                               server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setSharedNetwork4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ("IPv4 shared network successfully set.", msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned list of shared networks.
        auto shared_network_list = args->get("shared-networks");
        ASSERT_TRUE(shared_network_list);
        EXPECT_EQ(Element::list, shared_network_list->getType());
        ASSERT_EQ(1U, shared_network_list->size());

        auto shared_network_0 = shared_network_list->get(0);
        ASSERT_TRUE(shared_network_0);
        ASSERT_EQ(Element::map, shared_network_0->getType());
        EXPECT_EQ(1U, shared_network_0->size());

        auto shared_network_0_name = shared_network_0->get("name");
        ASSERT_TRUE(shared_network_0_name);
        EXPECT_EQ(Element::string, shared_network_0_name->getType());
        EXPECT_EQ(shared_network->getName(), shared_network_0_name->stringValue());

        // Make sure that the created/updated shared network is in the database
        // and has correct values and metadata.
        ASSERT_FALSE(server_tags.empty());
        auto fetched_shared_network = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSharedNetwork4(BackendSelector(),
                              ServerSelector::ONE(*server_tags.begin()),
                              shared_network->getName());
        ASSERT_TRUE(fetched_shared_network);

        EXPECT_EQ(shared_network->toElement()->str(),
                  fetched_shared_network->toElement()->str());

        // Make sure that the shared network options are not encapsulated.
        EXPECT_FALSE(fetched_shared_network->getCfgOption()->isEncapsulated());

        auto metadata = fetched_shared_network->getMetadata();
        ASSERT_TRUE(metadata);
        auto expected_metadata = createMetadata(server_tags);
        EXPECT_EQ(expected_metadata->str(), metadata->str());

        // Make sure that the created/updated subnets are in the database.
        auto fetched_subnets = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getAllSubnets4(BackendSelector(),
                           ServerSelector::ONE(*server_tags.begin()));
        auto const& index = fetched_subnets.get<SubnetSubnetIdIndexTag>();
        for (auto const& subnet : *shared_network->getAllSubnets()) {
            EXPECT_EQ(1U, index.count(subnet->getID()));
            // Make sure that the subnet options are not encapsulated.
            EXPECT_FALSE(subnet->getCfgOption()->isEncapsulated());
        }
    }

    /// @brief Negative test scenario for setting or updating a shared network.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected errors message.
    void testSharedNetwork4SetFail(const std::string& args,
                                   const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-network4-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setSharedNetwork4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);

        /// @todo Skipping line number possibly appended to the error message by
        /// the shared network parser. We should modify the parser to not
        /// output the position when used for control commands parsing.
        EXPECT_EQ(0U, msg->stringValue().find(answer_text))
            << "expected: " << answer_text
            << ", found: " << msg->stringValue();
    }

    /// @brief Returns remote-network4-del command as text.
    ///
    /// @param shared_network Pointer to the shared network to be used in the
    /// command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    /// @param action A string to be assigned to the "subnets-action"
    /// argument of the command. If the string is empty the "subnets-action"
    /// argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makeSharedNetwork4DelConfig(const SharedNetwork4Ptr& shared_network,
                                            const std::string& remote_map,
                                            const std::string& action) {
        std::string config = "{"
            "\"command\": \"remote-network4-del\","
            "\"arguments\": {"
            "    \"shared-networks\": [ { ";

        config += "\"name\": \"" + shared_network->getName() + "\" } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        // Only include "subnets-action" parameter if non empty.
        if (!action.empty()) {
            config += ", \"subnets-action\": \"" + action + "\"";
        }
        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for deleting shared network.
    ///
    /// @param shared_network Pointer to the shared network to be deleted.
    /// @param expected_count Expected number of deleted shared networks..
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param action A string to be assigned to the "subnets-action"
    /// argument of the command. If the string is empty the "subnets-action"
    /// argument is not included.
    void testSharedNetwork4Del(const SharedNetwork4Ptr& shared_network,
                               unsigned expected_count,
                               const std::string& remote_map = "",
                               const std::string& action = "") {

        // Generate the command as text.
        std::string command_text = makeSharedNetwork4DelConfig(shared_network,
                                                               remote_map,
                                                               action);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delSharedNetwork4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " IPv4 shared network(s) deleted.";
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

        // Make sure that the deleted shared network is not in the database.
        auto fetched_shared_network = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSharedNetwork4(BackendSelector(),
                              ServerSelector::ANY(),
                              shared_network->getName());
        ASSERT_FALSE(fetched_shared_network);
    }

    /// @brief Negative test scenario for deleting a shared network.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected errors message.
    void testSharedNetwork4DelFail(const std::string& args,
                                   const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-network4-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delSharedNetwork4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-network4-get command as text.
    ///
    /// @param shared_network Pointer to the shared network to be used in the
    /// command.
    /// @param subnets_include Value to be passed to be used for subnets-include.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    ///
    /// @return Command in the textual format.
    std::string makeSharedNetwork4GetConfig(const SharedNetwork4Ptr& shared_network,
                                            const std::string& subnets_include,
                                            const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-network4-get\","
            "\"arguments\": {"
            "    \"shared-networks\": [ { ";

        config += "\"name\": \"" + shared_network->getName() + "\" } ]";

        // Only include "subnets-include" parameter if non empty.
        if (!subnets_include.empty()) {
            config += ", \"subnets-include\": \"" + subnets_include + "\"";
        }

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for getting a shared network.
    ///
    /// @param shared_network Pointer to the shared network to be got.
    /// @param expected Pointer to the expected shared network.
    /// @param subnets_include Value to be passed to be used for subnets-include.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testSharedNetwork4Get(const SharedNetwork4Ptr& shared_network,
                               const SharedNetwork4Ptr& expected,
                               const std::string& subnets_include = "",
                               const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeSharedNetwork4GetConfig(shared_network,
                                                               subnets_include,
                                                               remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getSharedNetwork4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (!expected ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "IPv4 shared network '" << shared_network->getName()
                     << "' " << (!expected ? "not " : "") << "found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned shared network.
        ConstElementPtr networks = args->get("shared-networks");
        ASSERT_TRUE(networks);
        ASSERT_EQ(Element::list, networks->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (!expected) {
            EXPECT_EQ(0U, networks->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(1U, networks->size());
            ConstElementPtr got = networks->get(0);

            // Make sure that expected shared network includes metadata.
            ElementPtr expected_element = expected->toElement();
            auto tags = expected->getServerTags();
            ASSERT_FALSE(tags.empty());
            expected_element->set("metadata",
                                  createMetadata(tags.begin()->get()));

            // There must be no subnet4 parameter if the subnets are not
            // to be included.
            if (subnets_include != "full") {
                expected_element->remove("subnet4");
            }

            EXPECT_TRUE(isEquivalent(got, expected_element))
                << "Actual: " << got->str()
                << ", \nExpected: " << expected_element->str();
            EXPECT_EQ(1, count->intValue());
        }
    }

    /// @brief Negative test scenario for getting a shared network.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected errors message.
    void testSharedNetwork4GetFail(const std::string& args,
                                   const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-network4-get\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getSharedNetwork4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-network4-list command as text.
    ///
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeSharedNetwork4ListConfig(const std::string& remote_map,
                                             const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-network4-list\""
            ", \"arguments\": {";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += "\"remote\": " + remote_map + ",";
        }

        // Always include server tags,
        config += "\"server-tags\": [";
        if (!server_tags.empty()) {
            for (auto const& tag : server_tags) {
                config += "\"" + tag + "\",";
            }
            // Remove extraneous comma.
            config.pop_back();
        } else {
            // Empty means unassigned.
            config += " null ";
        }

        config += "] } }";
        return (config);
    }

    /// @brief Positive test scenario for getting all shared networks.
    ///
    /// @param expected Expected result.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command,
    /// empty means UNASSIGNED.
    void testSharedNetwork4List(ConstElementPtr expected,
                                const std::string& remote_map = "",
                                const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Sanity.
        ASSERT_TRUE(expected) << " bad test";
        ASSERT_EQ(Element::list, expected->getType()) << " bad test";

        // Generate the command as text.
        std::string command_text = makeSharedNetwork4ListConfig(remote_map,
                                                                server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::listSharedNetworks4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected->empty() ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected->size()
                     << " IPv4 shared network(s) found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected->size(), static_cast<size_t>(count->intValue()));

        // Validate returned shared networks.
        // Note this includes the metadata.
        ConstElementPtr networks = args->get("shared-networks");
        ASSERT_TRUE(networks);
        EXPECT_TRUE(isEquivalent(expected, networks))
            << "Actual: " << networks->str()
            << "\nExpected: " << expected->str();
    }

    /// @brief Negative test scenario for getting all shared networks.
    ///
    /// @param args Arguments for the command in the textual format not
    /// including "arguments".
    /// @param answer_text Expected errors message.
    void testSharedNetwork4ListFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-network4-list\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::listSharedNetworks4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update shared network.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4Set) {
    {
        SCOPED_TRACE("add new shared network");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        shared_network->setIface("eth1");
        testSharedNetwork4Set(shared_network, "", { "server1" });
    }

    {
        SCOPED_TRACE("add another shared network");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("bar"));
        shared_network->setIface("eth0");
        testSharedNetwork4Set(shared_network);
    }

    {
        SCOPED_TRACE("update existing shared network");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        shared_network->setIface("eth0");
        testSharedNetwork4Set(shared_network, "", { "server1" });
    }

    {
        SCOPED_TRACE("update another shared network with specifying remote");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("bar"));
        shared_network->setIface("eth1");
        testSharedNetwork4Set(shared_network, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("add a shared network for multiple servers");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("xyz"));
        shared_network->setIface("eth1");
        testSharedNetwork4Set(shared_network, "", { "server1", "server2" });
    }

    {
        SCOPED_TRACE("add a shared network with unknown interface");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("noif"));
        shared_network->setIface("foobar");
        testSharedNetwork4Set(shared_network, "", { "server1" });
    }
}

// This test verifies that it is possible to add a shared network with
// DHCP options.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4SetWithOptions) {
    {
        SCOPED_TRACE("add a shared network with standard option");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptor option_desc(option, false, "my-boot-file");
        option_desc.space_name_ = DHCP4_OPTION_SPACE;
        shared_network->getCfgOption()->add(option_desc, DHCP4_OPTION_SPACE);
        testSharedNetwork4Set(shared_network, "", { "server1" });
    }

    {
        SCOPED_TRACE("add a shared network with a custom option definition");
        OptionDefinitionPtr option_def(new OptionDefinition("foo",
                                                            222,
                                                            DHCP4_OPTION_SPACE,
                                                            "string"));
        ASSERT_NO_THROW(
            ConfigBackendDHCPv4Mgr::instance().getPool()->
                createUpdateOptionDef4(BackendSelector(),
                                       ServerSelector::ALL(),
                                       option_def);
        );

        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        OptionStringPtr option(new OptionString(Option::V4, 222, "xyz"));
        OptionDescriptor option_desc(option, false, "xyz");
        option_desc.space_name_ = DHCP4_OPTION_SPACE;
        shared_network->getCfgOption()->add(option_desc, DHCP4_OPTION_SPACE);
        testSharedNetwork4Set(shared_network, "", { "server1" });
    }
}

// This test verifies that malformed requests to add and update shared networks
// are rejected and proper error messages are returned.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSharedNetwork4SetFail("", "invalid command 'remote-network4-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty shared-networks list");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": [ ]", "'shared-networks' list "
                                  "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty shared network map");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": [ { } ]",
                                  "missing parameter 'name'");
    }

    {
        SCOPED_TRACE("malformed shared network");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": [ { \"interface\": \"eth1\" } ]",
                                  "missing parameter 'name'");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": ["
                                  "{ \"name\": \"foo\", "
                                  "\"subnet6\": [ ] } ]",
                                  "spurious 'subnet6' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": ["
                                  "{ \"name\": \"foo\", "
                                  "\"relay\": 0 } ]",
                                  "'relay' parameter is not a map");
    }

    {
        SCOPED_TRACE("multiple shared networks");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": ["
                                  "{ \"name\": \"foo\" },"
                                  "{ \"name\": \"bar\" }"
                                  "]",
                                  "'shared-networks' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testSharedNetwork4SetFail("\"shared-networks\": [ ]",
                                  "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testSharedNetwork4SetFail("\"server-tags\": [ null ], "
                                  "\"shared-networks\": ["
                                  "    { \"name\": \"bar\" } ]",
                                  "'server-tags' list must contain one or"
                                  " more server tags for the "
                                  "'remote-network4-set' command");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testSharedNetwork4SetFail("\"server-tags\": [ ]",
                                  "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testSharedNetwork4SetFail("\"server-tags\": [ \" \" ]",
                                  "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("subnet specified in shared network");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": ["
                                  "    { \"name\": \"bar\","
                                  "      \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\", \"id\": 1 } ]"
                                  "    }"
                                  "]",
                                  "'subnet4' must not be specified for the shared network. "
                                  "Use 'remote-subnet4-set command to add a subnet to the "
                                  "shared network");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": ["
                                  "    { \"name\": \"foo\" }"
                                  "],"
                                  "\"remote\": {"
                                  "    \"type\": \"postgresql\""
                                  "}",
                                  "no such database found for selector: type=postgresql");
    }

    {
        SCOPED_TRACE("lacking option definition");
        testSharedNetwork4SetFail("\"server-tags\": [ \"all\" ], "
                                  "\"shared-networks\": ["
                                  "    {"
                                  "        \"name\": \"foo\","
                                  "        \"option-data\": ["
                                  "            {"
                                  "                \"name\": \"boot-file-name\","
                                  "                \"data\": \"my-boot-file\","
                                  "                \"space\": \"myspace\""
                                  "            }"
                                  "        ]"
                                  "    }"
                                  "]",
                                  "definition for the option 'myspace.boot-file-name' does not exist");
    }
}

// This test verifies that sanity checks are performed.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4SetCheckFail) {
    {
        SCOPED_TRACE("bad relay");
        std::string config =
            "\"server-tags\": [ \"all\" ], "
            "\"shared-networks\": [ {"
            "    \"name\": \"foo\","
            "    \"relay\": -1"
            "} ]";
        testSharedNetwork4SetFail(config, "'relay' parameter is not a map");
    }

    {
        SCOPED_TRACE("empty name");
        std::string config =
            "\"server-tags\": [ \"all\" ], "
            "\"shared-networks\": [ {"
            "    \"name\": \"\""
            "} ]";
        testSharedNetwork4SetFail(config,
                                  "'name' parameter must not be empty");
    }
}

// This test verifies that it is possible to delete shared network.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4Del) {
    {
        SCOPED_TRACE("add and delete new shared network");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        shared_network->setIface("eth1");
        testSharedNetwork4Set(shared_network);
        testSharedNetwork4Del(shared_network, 1);
    }

    {
        SCOPED_TRACE("add and delete another shared network");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("bar"));
        shared_network->setIface("eth0");
        testSharedNetwork4Set(shared_network);
        testSharedNetwork4Del(shared_network, 1);
    }

    {
        SCOPED_TRACE("delete shared network");
        // Deleting not existing is not an error.
        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        shared_network->setIface("eth1");
        testSharedNetwork4Del(shared_network, 0);
    }

    {
        SCOPED_TRACE("delete another shared network with specifying remote");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        shared_network->setIface("eth0");
        testSharedNetwork4Set(shared_network, "{ \"type\": \"mysql\" }");
        testSharedNetwork4Del(shared_network, 1, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies the different subnets actions.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4DelSubnetsAction) {
    {
        SCOPED_TRACE("default is keep");
        isc::dhcp::test::IfaceMgrTestConfig test_config(true);
        SharedNetwork4Ptr shared_network(new SharedNetwork4("one"));
        shared_network->setIface("eth0");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        subnet->setIface("eth0");
        subnet->setSharedNetworkName("one");
        setSubnet(subnet);

        testSharedNetwork4Set(shared_network);
        testSharedNetwork4Del(shared_network, 1);
        auto fetched_subnets = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getAllSubnets4(BackendSelector(), ServerSelector::ALL());

        auto const& index = fetched_subnets.get<SubnetSubnetIdIndexTag>();
        ASSERT_EQ(1U, index.count(subnet->getID()));
        Subnet4Ptr fetched_subnet = *index.find(subnet->getID());
        SharedNetwork4Ptr network;
        fetched_subnet->getSharedNetwork(network);
        EXPECT_FALSE(network);
        EXPECT_EQ("", fetched_subnet->getSharedNetworkName());
    }

    {
        SCOPED_TRACE("set subnets-action to keep");
        isc::dhcp::test::IfaceMgrTestConfig test_config(true);
        SharedNetwork4Ptr shared_network(new SharedNetwork4("two"));
        shared_network->setIface("eth0");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        subnet->setIface("eth0");
        subnet->setSharedNetworkName("two");
        setSubnet(subnet);
        testSharedNetwork4Set(shared_network);
        testSharedNetwork4Del(shared_network, 1, "", "keep");
        auto fetched_subnets = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getAllSubnets4(BackendSelector(), ServerSelector::ALL());
        auto const& index = fetched_subnets.get<SubnetSubnetIdIndexTag>();
        EXPECT_EQ(1U, index.count(subnet->getID()));
    }

    {
        SCOPED_TRACE("set subnets-action to delete");
        isc::dhcp::test::IfaceMgrTestConfig test_config(true);
        SharedNetwork4Ptr shared_network(new SharedNetwork4("three"));
        shared_network->setIface("eth0");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.4.0"), 24, 30, 40, 60, 3));
        subnet->setIface("eth0");
        subnet->setSharedNetworkName("three");
        setSubnet(subnet);
        testSharedNetwork4Set(shared_network);
        testSharedNetwork4Del(shared_network, 1, "", "delete");
        auto fetched_subnets = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getAllSubnets4(BackendSelector(), ServerSelector::ALL());
        auto const& index = fetched_subnets.get<SubnetSubnetIdIndexTag>();
        EXPECT_EQ(0U, index.count(subnet->getID()));
    }
}

// This test verifies that malformed requests to delete shared networks
// are rejected and proper error messages are returned.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSharedNetwork4DelFail("", "invalid command 'remote-network4-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty shared-networks list");
        testSharedNetwork4DelFail("\"shared-networks\": [ ]",
                                  "'shared-networks' list "
                                  "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty shared network map");
        testSharedNetwork4DelFail("\"shared-networks\": [ { } ]",
                                  "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("malformed shared network");
        testSharedNetwork4DelFail("\"shared-networks\": [ { \"interface\": \"eth1\" } ]",
                                  "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("multiple shared networks");
        testSharedNetwork4DelFail("\"shared-networks\": ["
                                  "{ \"name\": \"foo\" },"
                                  "{ \"name\": \"bar\" }"
                                  "]",
                                  "'shared-networks' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSharedNetwork4DelFail("\"server-tags\": [ ]",
                                  "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSharedNetwork4DelFail("\"shared-networks\": ["
                                  "    { \"name\": \"foo\" }"
                                  "],"
                                  "\"remote\": {"
                                  "    \"type\": \"postgresql\""
                                  "}",
                                  "no such database found for selector: type=postgresql");
    }

    {
        SCOPED_TRACE("unsupported subnets action");
        testSharedNetwork4DelFail("\"shared-networks\": ["
                                  "    { \"name\": \"foo\" }"
                                  "],"
                                  "\"subnets-action\": \"foo\"",
                                  "unknown 'subnets-action' parameter value:"
                                  " 'foo', possible vales are 'keep'"
                                  " (default) and 'delete'");
    }
}

// This test verifies that it is possible to get shared network.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4Get) {
    {
        SCOPED_TRACE("add and get new shared network");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
        shared_network->setIface("eth1");
        shared_network->setServerTag("server1");
        testSharedNetwork4Set(shared_network, "", { "server1" });
        testSharedNetwork4Get(shared_network, shared_network);
    }

    {
        SCOPED_TRACE("add and get another shared network");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("bar"));
        shared_network->setIface("eth0");
        shared_network->setServerTag(ServerTag::ALL);
        testSharedNetwork4Set(shared_network);
        testSharedNetwork4Get(shared_network, shared_network);
    }

    {
        SCOPED_TRACE("get no shared network");
        // Getting not existing is not an error.
        SharedNetwork4Ptr shared_network(new SharedNetwork4("yzt"));
        shared_network->setIface("eth1");
        shared_network->setServerTag(ServerTag::ALL);
        testSharedNetwork4Get(shared_network, SharedNetwork4Ptr());
    }

    {
        SCOPED_TRACE("add and get a shared network with two subnets");
        isc::dhcp::test::IfaceMgrTestConfig test_config(true);
        SharedNetwork4Ptr shared_network(new SharedNetwork4("two"));
        shared_network->setIface("eth0");
        shared_network->setServerTag(ServerTag::ALL);
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        subnet->setIface("eth0");
        subnet->setSharedNetworkName("two");
        setSubnet(subnet);
        subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        subnet->setIface("eth0");
        subnet->setSharedNetworkName("two");
        setSubnet(subnet);
        testSharedNetwork4Set(shared_network);
        testSharedNetwork4Get(shared_network, shared_network);
    }

    {
        SCOPED_TRACE("add and get another shared network with specifying remote");
        SharedNetwork4Ptr shared_network(new SharedNetwork4("abc"));
        shared_network->setIface("eth0");
        shared_network->setServerTag(ServerTag::ALL);
        testSharedNetwork4Set(shared_network, "{ \"type\": \"mysql\" }");
        testSharedNetwork4Get(shared_network, shared_network, "",
                              "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that it is possible to control if the returned
// shared network contains subnets.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4DelSubnetsInclude) {
    isc::dhcp::test::IfaceMgrTestConfig test_config(true);
    SharedNetwork4Ptr shared_network(new SharedNetwork4("two"));
    shared_network->setIface("eth0");
    shared_network->setServerTag(ServerTag::ALL);
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
    subnet1->setIface("eth0");
    subnet1->setSharedNetworkName("two");
    setSubnet(subnet1);
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
    subnet2->setIface("eth0");
    subnet2->setSharedNetworkName("two");
    setSubnet(subnet2);
    testSharedNetwork4Set(shared_network);

    {
        SCOPED_TRACE("default subnets-include");
        testSharedNetwork4Get(shared_network, shared_network, "");
    }

    {
        SCOPED_TRACE("set subnets-include to no");
        testSharedNetwork4Get(shared_network, shared_network, "no");
    }

    {
        SCOPED_TRACE("set subnets-include to full");
        SharedNetwork4Ptr exp_shared_network(new SharedNetwork4("two"));
        exp_shared_network->setIface("eth0");
        exp_shared_network->setServerTag(ServerTag::ALL);
        Subnet4Ptr exp_subnet1(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        exp_subnet1->setIface("eth0");
        exp_shared_network->add(exp_subnet1);
        Subnet4Ptr exp_subnet2(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        exp_subnet2->setIface("eth0");
        exp_shared_network->add(exp_subnet2);
        testSharedNetwork4Get(shared_network, exp_shared_network, "full");
    }
}

// This test verifies that malformed requests to get shared networks
// are rejected and proper error messages are returned.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4GetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSharedNetwork4GetFail("", "invalid command 'remote-network4-get': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty shared-networks list");
        testSharedNetwork4GetFail("\"shared-networks\": [ ]",
                                  "'shared-networks' list "
                                  "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty shared network map");
        testSharedNetwork4GetFail("\"shared-networks\": [ { } ]",
                                  "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("malformed shared network");
        testSharedNetwork4GetFail("\"shared-networks\": [ { \"interface\": \"eth1\" } ]",
                                  "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("multiple shared networks");
        testSharedNetwork4GetFail("\"shared-networks\": ["
                                  "{ \"name\": \"foo\" },"
                                  "{ \"name\": \"bar\" }"
                                  "]",
                                  "'shared-networks' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSharedNetwork4GetFail("\"server-tags\": [ ]",
                                  "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSharedNetwork4GetFail("\"shared-networks\": ["
                                  "    { \"name\": \"foo\" }"
                                  "],"
                                  "\"remote\": {"
                                  "    \"type\": \"postgresql\""
                                  "}",
                                  "no such database found for selector: type=postgresql");
    }

    {
        SCOPED_TRACE("unsupported subnets-include value");
        testSharedNetwork4GetFail("\"shared-networks\": ["
                                  "    { \"name\": \"foo\" }"
                                  "],"
                                  "\"subnets-include\": \"foo\"",
                                  "unknown 'subnets-include' parameter value:"
                                  " 'foo', possible values are 'no' (default)"
                                  " and 'full'");
    }
}

// This test verifies that it is possible to get all shared networks.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4List) {
    // Empty.
    ElementPtr expected = Element::createList();
    ElementPtr expected_all = Element::createList();
    ElementPtr expected_unassigned = Element::createList();
    testSharedNetwork4List(expected);
    testSharedNetwork4List(expected_all);
    testSharedNetwork4List(expected_unassigned);

    // Add a shared network.
    SharedNetwork4Ptr shared_network(new SharedNetwork4("foo"));
    shared_network->setIface("eth1");
    shared_network->setServerTag("server1");
    testSharedNetwork4Set(shared_network, "", { "server1" });
    ElementPtr network_map = Element::createMap();
    network_map->set("name", Element::create("foo"));
    network_map->set("metadata", createMetadata("server1"));
    expected->add(network_map);
    testSharedNetwork4List(expected, "", { "server1" });

    // Add a second shared network.
    shared_network.reset(new SharedNetwork4("bar"));
    shared_network->setIface("eth0");
    shared_network->setServerTag(ServerTag::ALL);
    testSharedNetwork4Set(shared_network);
    network_map = Element::createMap();
    network_map->set("name", Element::create("bar"));
    network_map->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(network_map);
    expected_all->add(network_map);
    testSharedNetwork4List(expected, "", { "server1" });
    testSharedNetwork4List(expected_all);

    // With another server only shared networks belonging to all are returned.
    testSharedNetwork4List(expected_all, "", { "server2" });

    // Try with a remote.
    shared_network.reset(new SharedNetwork4("abc"));
    shared_network->setIface("eth0");
    shared_network->setServerTag(ServerTag::ALL);
    testSharedNetwork4Set(shared_network, "{ \"type\": \"mysql\" }");
    network_map = Element::createMap();
    network_map->set("name", Element::create("abc"));
    network_map->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(network_map);
    expected_all->add(network_map);
    testSharedNetwork4List(expected, "{ \"type\": \"mysql\" }", { "server1" });
    testSharedNetwork4List(expected_all, "{ \"type\": \"mysql\" }");

    // Add a third shared network in another server.
    shared_network.reset(new SharedNetwork4("xyz"));
    shared_network->setIface("eth0");
    shared_network->setServerTag("server2");
    testSharedNetwork4Set(shared_network, "", { "server2" });
    // Not in server1 so not yet expected.
    testSharedNetwork4List(expected, "", { "server1" });
    network_map = Element::createMap();
    network_map->set("name", Element::create("xyz"));
    network_map->set("metadata", createMetadata("server2"));
    expected->add(network_map);
    testSharedNetwork4List(expected, "", { "server1", "server2" });

    // Now try unassigned.
    testSharedNetwork4List(expected_unassigned, "", { });
    shared_network.reset(new SharedNetwork4("uvw"));
    shared_network->setIface("eth0");
    // Adds it directly to the backend (no command yet to do this).
    setSharedNetwork(shared_network);
    // Not visible by a server.
    testSharedNetwork4List(expected, "", { "server1", "server2" });
    network_map = Element::createMap();
    network_map->set("name", Element::create("uvw"));
    expected_unassigned->add(network_map);
    network_map->set("metadata", createMetadata(std::set<std::string>()));
    testSharedNetwork4List(expected_unassigned, "", { });
}

// This test verifies that malformed requests to get all shared networks
// are rejected and proper error messages are returned.
TEST_F(SharedNetwork4CmdsTest, sharedNetwork4ListFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSharedNetwork4ListFail(", \"arguments\": { }",
                                   "invalid command 'remote-network4-list': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("no server tags");
        testSharedNetwork4ListFail(", \"arguments\": { \"remote\": { } }",
                                   "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testSharedNetwork4ListFail(", \"arguments\": { \"server-tags\": [ ] }",
                                   "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("bad formed unassigned");
        testSharedNetwork4ListFail(", \"arguments\": { "
                                   "\"server-tags\": [ null, \"all\" ] }",
                                   "when the 'server-tags' list contains "
                                   "multiple elements all these elements must "
                                   "have the string type");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSharedNetwork4ListFail(", \"arguments\": { "
                                   "\"server-tags\": [ \"all\" ], "
                                   "\"remote\": {"
                                   "    \"type\": \"postgresql\""
                                   "} }",
                                   "no such database found for selector: "
                                   "type=postgresql");
    }
}

}
