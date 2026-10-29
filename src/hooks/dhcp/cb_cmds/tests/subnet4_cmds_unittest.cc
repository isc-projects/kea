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
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
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

/// @brief Test fixture class for callouts pertaining to subnets.
class Subnet4CmdsTest : public ConfigCmdsDhcp4Test {
public:

    /// @brief Constructor.
    Subnet4CmdsTest() {
        initTestSharedNetwork4();
    }

    /// @brief Inserts shared network used in tests into the database.
    void initTestSharedNetwork4() {
        SharedNetwork4Ptr shared_network = SharedNetwork4::create("test4");
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateSharedNetwork4(BackendSelector(), ServerSelector::ALL(),
                                       shared_network);
    }

    /// @brief Adds unassigned subnet to the configuration backend.
    ///
    /// @param subnet Pointer to the subnet to be stored.
    void setSubnet(const Subnet4Ptr& subnet) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateSubnet4(BackendSelector(), ServerSelector::UNASSIGNED(),
                                subnet);
    }

    /// @brief Returns remote-subnet4-set command as text.
    ///
    /// @param shared_network_name Name to be associated with the subnet.
    /// @param subnet Pointer to the subnet to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeSubnet4SetConfig(const std::string& shared_network_name,
                                     const Subnet4Ptr& subnet,
                                     const std::string& remote_map,
                                     const std::set<std::string>& server_tags) {
        auto subnet_element = subnet->toElement();

        // Always include shared-network-name.
        if (shared_network_name == "null") {
            subnet_element->set("shared-network-name", Element::create());

        } else {
            subnet_element->set("shared-network-name",
                                Element::create(shared_network_name));
        }

        std::string config = "{"
            "\"command\": \"remote-subnet4-set\","
            "\"arguments\": {"
            "    \"subnets\": [";

        config += subnet_element->str() + "]";

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

    /// @brief Positive test scenario for setting or updating a subnet
    /// belonging to a shared network.
    ///
    /// @param shared_network_name Name to be associated with the subnet.
    /// @param subnet Pointer to the subnet to be created or updated.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testSubnet4Set(const std::string& shared_network_name,
                        const Subnet4Ptr& subnet,
                        const std::string& remote_map = "",
                        const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeSubnet4SetConfig(shared_network_name,
                                                        subnet, remote_map,
                                                        server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setSubnet4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ("IPv4 subnet successfully set.", msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned list of subnets.
        auto subnet_list = args->get("subnets");
        ASSERT_TRUE(subnet_list);
        EXPECT_EQ(Element::list, subnet_list->getType());
        ASSERT_EQ(1U, subnet_list->size());

        auto subnet_0 = subnet_list->get(0);
        ASSERT_TRUE(subnet_0);
        ASSERT_EQ(Element::map, subnet_0->getType());
        EXPECT_EQ(2U, subnet_0->size());

        auto subnet_0_id = subnet_0->get("id");
        ASSERT_TRUE(subnet_0_id);
        ASSERT_EQ(Element::integer, subnet_0_id->getType());
        EXPECT_EQ(subnet->getID(), static_cast<uint32_t>(subnet_0_id->intValue()));

        auto subnet_0_subnet = subnet_0->get("subnet");
        ASSERT_TRUE(subnet_0_subnet);
        ASSERT_EQ(Element::string, subnet_0_subnet->getType());
        EXPECT_EQ(subnet->toText(), subnet_0_subnet->stringValue());

        // Make sure that the created/updated subnet is in the database
        // and has correct values and metadata.
        auto fetched_subnet = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSubnet4(BackendSelector(),
                       ServerSelector::ONE(*server_tags.begin()),
                       subnet->getID());
        ASSERT_TRUE(fetched_subnet);
        EXPECT_EQ(subnet->toElement()->str(), fetched_subnet->toElement()->str());

        // Make sure that the subnet options are not encapsulated.
        EXPECT_FALSE(fetched_subnet->getCfgOption()->isEncapsulated());

        if (shared_network_name != "null") {
            EXPECT_EQ(shared_network_name, fetched_subnet->getSharedNetworkName());

        } else {
            EXPECT_TRUE(fetched_subnet->getSharedNetworkName().empty());
        }

        auto metadata = fetched_subnet->getMetadata();
        ASSERT_TRUE(metadata);
        auto expected_metadata = createMetadata(server_tags);
        EXPECT_EQ(expected_metadata->str(), metadata->str());
    }

    /// @brief Positive test scenario for setting or updating a subnet.
    ///
    /// @param subnet Pointer to the subnet to be created or updated.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    ///
    /// @param server_tags Server tags to be included in the command.
    void testSubnet4Set(const Subnet4Ptr& subnet,
                        const std::string& remote_map = "",
                        const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        testSubnet4Set("", subnet, remote_map, server_tags);
    }

    /// @brief Negative test scenario for setting or updating a subnet.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testSubnet4SetFail(const std::string& args,
                            const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-subnet4-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setSubnet4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        ASSERT_EQ(CONTROL_RESULT_ERROR, rcode);

        /// @todo Skipping line number possibly appended to the error message by
        /// the subnet parser. We should modify the parser to not output the
        /// position when used for control commands parsing.
        EXPECT_EQ(0U, answer->stringValue().find(answer_text))
            << "expected: " << answer_text
            << ", found: " << answer->stringValue();
    }

    /// @brief Returns remote-subnet4-del-by-id command as text.
    ///
    /// @param subnet Pointer to the subnet to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    ///
    /// @return Command in the textual format.
    std::string makeSubnet4DelIdConfig(const Subnet4Ptr& subnet,
                                       const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-subnet4-del-by-id\","
            "\"arguments\": {"
            "    \"subnets\": [ { ";

        std::ostringstream id;
        id << subnet->getID();
        config += "\"id\": " + id.str() + " } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for deleting a subnet by id.
    ///
    /// @param subnet Pointer to the subnet to be deleted.
    /// @param expected_count Expected number of deleted subnets.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testSubnet4DelId(const Subnet4Ptr& subnet,
                          unsigned expected_count,
                          const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeSubnet4DelIdConfig(subnet, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delSubnet4Id,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " IPv4 subnet(s) deleted.";
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

        // Make sure that the deleted subnet is not in the database.
        auto fetched_subnet = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSubnet4(BackendSelector(),
                       ServerSelector::ANY(),
                       subnet->getID());
        ASSERT_FALSE(fetched_subnet);
    }

    /// @brief Negative test scenario for deleting a subnet by id.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testSubnet4DelIdFail(const std::string& args,
                              const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-subnet4-del-by-id\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delSubnet4Id,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-subnet4-del-by-prefix command as text.
    ///
    /// @param subnet Pointer to the subnet to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    ///
    /// @return Command in the textual format.
    std::string makeSubnet4DelPrefixConfig(const Subnet4Ptr& subnet,
                                           const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-subnet4-del-by-prefix\","
            "\"arguments\": {"
            "    \"subnets\": [ { ";

        config += "\"subnet\": \"" + subnet->toText() + "\" } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for deleting a subnet by prefix.
    ///
    /// @param subnet Pointer to the subnet to be deleted.
    /// @param expected_count Expected number of deleted subnets.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testSubnet4DelPrefix(const Subnet4Ptr& subnet,
                              unsigned expected_count,
                              const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text =
            makeSubnet4DelPrefixConfig(subnet, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
            impl_.run(&TestConfigCmdsDhcp4Impl::delSubnet4Prefix, command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " IPv4 subnet(s) deleted.";
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

        // Make sure that the deleted subnet is not in the database.
        auto fetched_subnet = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSubnet4(BackendSelector(),
                       ServerSelector::ANY(),
                       subnet->getID());
        ASSERT_FALSE(fetched_subnet);
    }

    /// @brief Negative test scenario for deleting a subnet by prefix.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testSubnet4DelPrefixFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-subnet4-del-by-prefix\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
            impl_.run(&TestConfigCmdsDhcp4Impl::delSubnet4Prefix, command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-subnet4-get-by-id command as text.
    ///
    /// @param subnet Pointer to the subnet to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    ///
    /// @return Command in the textual format.
    std::string makeSubnet4GetIdConfig(const Subnet4Ptr& subnet,
                                       const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-subnet4-get-by-id\","
            "\"arguments\": {"
            "    \"subnets\": [ { ";

        std::ostringstream id;
        id << subnet->getID();
        config += "\"id\": " + id.str() + " } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for getting a subnet by id.
    ///
    /// @param subnet Pointer to the subnet to be got.
    /// @param expected Pointer to the expected subnet.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testSubnet4GetId(const Subnet4Ptr& subnet,
                          const Subnet4Ptr& expected,
                          const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeSubnet4GetIdConfig(subnet, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::getSubnet4Id,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (!expected ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "IPv4 subnet " << subnet->getID() << " "
                     << (!expected ? "not " : "") << "found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned subnet.
        ConstElementPtr subnets = args->get("subnets");
        ASSERT_TRUE(subnets);
        ASSERT_EQ(Element::list, subnets->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (!expected) {
            EXPECT_EQ(0U, subnets->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(1U, subnets->size());
            ConstElementPtr got = subnets->get(0);
            ElementPtr expected_element = expected->toElement();

            // Shared network name must always be returned.
            std::string sn_name = subnet->getSharedNetworkName();
            if (!sn_name.empty()) {
                expected_element->set("shared-network-name",
                                      Element::create(sn_name));
            } else {
                // Shared network name is not specified. Output null value.
                expected_element->set("shared-network-name",
                                      Element::create());
            }

            // Make sure that expected element includes metadata.
            auto tags = expected->getServerTags();
            ASSERT_FALSE(tags.empty());
            expected_element->set("metadata",
                                  createMetadata(tags.begin()->get()));

            EXPECT_TRUE(isEquivalent(got, expected_element))
                << "Actual: " << got->str()
                << "\nExpected: " << expected_element->str();
            EXPECT_EQ(1, count->intValue());
        }
    }

    /// @brief Negative test scenario for getting a subnet by id.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testSubnet4GetIdFail(const std::string& args,
                              const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-subnet4-get-by-id\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::getSubnet4Id,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-subnet4-get-by-prefix command as text.
    ///
    /// @param subnet Pointer to the subnet to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    ///
    /// @return Command in the textual format.
    std::string makeSubnet4GetPrefixConfig(const Subnet4Ptr& subnet,
                                           const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-subnet4-get-by-prefix\","
            "\"arguments\": {"
            "    \"subnets\": [ { ";

        config += "\"subnet\": \"" + subnet->toText() + "\" } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for getting a subnet by prefix.
    ///
    /// @param subnet Pointer to the subnet to be got.
    /// @param expected Pointer to the expected subnet.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testSubnet4GetPrefix(const Subnet4Ptr& subnet,
                              const Subnet4Ptr& expected,
                              const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text =
            makeSubnet4GetPrefixConfig(subnet, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
            impl_.run(&TestConfigCmdsDhcp4Impl::getSubnet4Prefix, command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (!expected ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "IPv4 subnet " << subnet->toText()
                     << (!expected ? " not " : " ") << "found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned subnet.
        ConstElementPtr subnets = args->get("subnets");
        ASSERT_TRUE(subnets);
        ASSERT_EQ(Element::list, subnets->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (!expected) {
            EXPECT_EQ(0U, subnets->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(1U, subnets->size());
            ConstElementPtr got = subnets->get(0);
            ElementPtr expected_element = expected->toElement();

            // Shared network name must always be returned.
            std::string sn_name = subnet->getSharedNetworkName();
            if (!sn_name.empty()) {
                expected_element->set("shared-network-name",
                                      Element::create(sn_name));
            } else {
                // Shared network name is not specified. Output null value.
                expected_element->set("shared-network-name",
                                      Element::create());
            }

            // Make sure that expected element includes metadata.
            auto tags = expected->getServerTags();
            ASSERT_FALSE(tags.empty());
            expected_element->set("metadata",
                                  createMetadata(tags.begin()->get()));

            EXPECT_TRUE(isEquivalent(got, expected_element))
                << "Actual: " << got->str()
                << "\nExpected: " << expected_element->str();
            EXPECT_EQ(1, count->intValue());
        }
    }

    /// @brief Negative test scenario for getting a subnet by prefix.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testSubnet4GetPrefixFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-subnet4-get-by-prefix\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
            impl_.run(&TestConfigCmdsDhcp4Impl::getSubnet4Prefix, command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-subnet4-list command as text.
    ///
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeSubnet4ListConfig(const std::string& remote_map,
                                      const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-subnet4-list\""
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

    /// @brief Positive test scenario for getting all subnets.
    ///
    /// @param expected Expected result.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command,
    /// empty means UNASSIGNED.
    void testSubnet4List(ConstElementPtr expected,
                         const std::string& remote_map = "",
                         const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Sanity.
        ASSERT_TRUE(expected) << " bad test";
        ASSERT_EQ(Element::list, expected->getType()) << " bad test";

        // Generate the command as text.
        std::string command_text = makeSubnet4ListConfig(remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::listSubnets4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected->empty() ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected->size() << " IPv4 subnet(s) found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected->size(), static_cast<size_t>(count->intValue()));

        // Validate returned subnets.
        // Note this includes the metadata.
        ConstElementPtr subnets = args->get("subnets");
        ASSERT_TRUE(subnets);
        EXPECT_TRUE(isEquivalent(expected, subnets))
            << "Actual: " << subnets->str()
            << "\nExpected: " << expected->str();
    }

    /// @brief Negative test scenario for getting all subnets.
    ///
    /// @param args Arguments for the command in the textual format not
    /// including "arguments".
    /// @param answer_text Expected error message.
    void testSubnet4ListFail(const std::string& args,
                             const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-subnet4-list\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::listSubnets4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update subnet.
TEST_F(Subnet4CmdsTest, subnet4Set) {
    {
        SCOPED_TRACE("add new subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        testSubnet4Set(subnet, "", { "server1" });
    }

    {
        SCOPED_TRACE("add another subnet within shared network");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        testSubnet4Set("test4", subnet);
    }

    {
        SCOPED_TRACE("update existing subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 40, 50, 60, 1));
        testSubnet4Set(subnet, "", { "server1" });
    }

    {
        SCOPED_TRACE("update another subnet with specifying remote");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 40, 50, 60, 2));
        testSubnet4Set("test4", subnet, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("nullify subnet's shared network");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 40, 50, 60, 2));
        testSubnet4Set("null", subnet);
    }

    {
        SCOPED_TRACE("add a subnet for multiple servers");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.4.0"), 24, 30, 40, 60, 3));
        testSubnet4Set(subnet, "", { "server1", "server2" });
    }

    {
        SCOPED_TRACE("add a subnet with unknown interface");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.5.0"), 24, 30, 40, 60, 4));
        subnet->setIface("foobar");
        testSubnet4Set(subnet, "", { "server1" });
    }
}

// This test verifies that it is possible to add a subnet with
// DHCP options at the subnet and pool levels.
TEST_F(Subnet4CmdsTest, subnet4SetWithOptions) {
    {
        SCOPED_TRACE("add a subnet with standard option");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.5.0"), 24, 30, 40, 60, 4));

        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptor option_desc(option, false, "my-boot-file");
        option_desc.space_name_ = DHCP4_OPTION_SPACE;
        subnet->getCfgOption()->add(option_desc, DHCP4_OPTION_SPACE);

        Option4AddrLstPtr option2(new Option4AddrLst(DHO_ROUTERS, IOAddress("192.0.2.1")));
        OptionDescriptor option_desc2(option2, false, false);
        option_desc2.space_name_ = DHCP4_OPTION_SPACE;
        Pool4Ptr pool(new Pool4(IOAddress("192.0.5.5"), IOAddress("192.0.5.100")));
        pool->getCfgOption()->add(option_desc2, DHCP4_OPTION_SPACE);
        subnet->addPool(pool);

        testSubnet4Set(subnet, "", { "server1" });
    }

    {
        SCOPED_TRACE("add a subnet with a custom option definition");
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

        OptionDefinitionPtr option_def2(new OptionDefinition("baz", 1, "myspace",
                                                             "ipv4-address", true));
        ASSERT_NO_THROW(
            ConfigBackendDHCPv4Mgr::instance().getPool()->
                createUpdateOptionDef4(BackendSelector(),
                                       ServerSelector::ALL(),
                                       option_def2);
        );


        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.5.0"), 24, 30, 40, 60, 4));
        OptionStringPtr option(new OptionString(Option::V4, 222, "xyz"));
        OptionDescriptor option_desc(option, false, "xyz");
        option_desc.space_name_ = DHCP4_OPTION_SPACE;
        subnet->getCfgOption()->add(option_desc, DHCP4_OPTION_SPACE);

        Option4AddrLstPtr option2(new Option4AddrLst(1, IOAddress("192.0.2.1")));
        OptionDescriptor option_desc2(option2, false, "192.0.2.1");
        option_desc2.space_name_ = "myspace";
        Pool4Ptr pool(new Pool4(IOAddress("192.0.5.5"), IOAddress("192.0.5.100")));
        pool->getCfgOption()->add(option_desc2, "myspace");
        subnet->addPool(pool);

        testSubnet4Set(subnet, "", { "server1" });
    }
}

// This test verifies that malformed requests to add and update subnets are
// rejected and proper error messages are returned.
TEST_F(Subnet4CmdsTest, subnet4SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnet4SetFail("", "invalid command 'remote-subnet4-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty subnet4 list");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": [ ]", "'subnets' list "
                           "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty subnet map");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": [ { } ]",
                           "subnet 'id' is mandatory for the remote-subnet4-set command");
    }

    {
        SCOPED_TRACE("malformed subnet");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": [ { \"interface\": \"eth1\" } ]",
                           "subnet 'id' is mandatory for the remote-subnet4-set command");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\", \"id\": 1,"
                           "\"shared-network-name\": null, "
                           "\"pd-pools\": [ ] } ]",
                           "spurious 'pd-pools' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\", \"id\": 1,"
                           "\"shared-network-name\": null, "
                           "\"next-server\": 0 } ]",
                           "'next-server' parameter is not a string");
    }

    {
        SCOPED_TRACE("multiple subnets");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.2.0/24\", \"shared-network-name\": null },"
                           "{ \"subnet\": \"192.0.3.0/24\", \"shared-network-name\": null }"
                           "]",
                           "'subnets' list must include exactly one element");
    }

    {
        SCOPED_TRACE("invalid shared network name type");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\", \"id\": 1,"
                           "  \"shared-network-name\": 1 }"
                           "]",
                           "'shared-network-name' must be a string or null");
    }

    {
        SCOPED_TRACE("no subnet id");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\" }"
                           "]",
                           "subnet 'id' is mandatory for the remote-subnet4-set command");
    }

    {
        SCOPED_TRACE("subnet id not int");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\","
                           " \"id\": \"foo\" }"
                           "]",
                           "'id' is not an integer");
    }

    {
        SCOPED_TRACE("zero subnet id");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\","
                           " \"id\": 0 }"
                           "]",
                           "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("too large subnet id");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\","
                           " \"id\": 4294967295 }"
                           "]",
                           "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("no shared network name");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "{ \"subnet\": \"192.0.3.0/24\", \"id\": 1 }"
                           "]",
                           "'shared-network-name' is mandatory (but can be null or empty)");
    }

    {
        SCOPED_TRACE("no server tags");
        testSubnet4SetFail("\"subnets\": [ ]",
                           "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testSubnet4SetFail("\"server-tags\": [ null ], "
                           "\"subnets\": ["
                           "    { \"subnet\": \"192.0.2.0/24\", \"id\": 1,"
                           "      \"shared-network-name\": null }"
                           "]",
                           "'server-tags' list must contain one or"
                           " more server tags for the "
                           "'remote-subnet4-set' command");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testSubnet4SetFail("\"server-tags\": [ ]",
                           "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testSubnet4SetFail("\"server-tags\": [ \" \" ]",
                           "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnet4SetFail("\"server-tags\": [ \"all\"], "
                           "\"subnets\": ["
                           "    { \"subnet\": \"192.0.2.0/24\", \"id\": 1,"
                           "      \"shared-network-name\": null }"
                           "],"
                           "\"remote\": {"
                           "    \"type\": \"postgresql\""
                           "}",
                           "no such database found for selector: type=postgresql");
    }

    {
        SCOPED_TRACE("lacking option definition");
        testSubnet4SetFail("\"server-tags\": [ \"all\" ], "
                           "\"subnets\": ["
                           "    {"
                           "        \"subnet\": \"192.0.2.0/24\","
                           "        \"id\": 1,"
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

// This test verifies that requests with reservations are refused.
TEST_F(Subnet4CmdsTest, subnet4SetHostsFail) {
    {
        SCOPED_TRACE("not list hosts");
        std::string config =
            "\"server-tags\": [ \"all\"], "
            "\"subnets\": [ {"
            "    \"id\": 1,"
            "    \"subnet\": \"192.0.2.0/24\","
            "    \"reservations\": 0"
            "} ]";
        testSubnet4SetFail(config, "'reservations' entry is not a list");
    }

    {
        SCOPED_TRACE("not empty hosts");
        std::string config =
            "\"server-tags\": [ \"all\"], "
            "\"subnets\": [ {"
            "    \"id\": 1,"
            "    \"subnet\": \"192.0.2.0/24\","
            "    \"reservations\": [ { } ]"
            "} ]";
        testSubnet4SetFail(config, "'reservations' entry is not empty. "
                           "This is not supported by the "
                           "remote-subnet4-set command");
    }
}

// This test verifies that it is possible to delete subnet by id.
TEST_F(Subnet4CmdsTest, subnet4DelById) {
    {
        SCOPED_TRACE("add and delete subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        testSubnet4Set(subnet);
        testSubnet4DelId(subnet, 1);
    }

    {
        SCOPED_TRACE("add and delete another subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        testSubnet4Set(subnet);
        testSubnet4DelId(subnet, 1);
    }

    {
        SCOPED_TRACE("delete subnet");
        // Deleting not existing is not an error.
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        testSubnet4DelId(subnet, 0);
    }

    {
        SCOPED_TRACE("delete another subnet with specifying remote");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 40, 50, 60, 2));
        testSubnet4Set(subnet, "{ \"type\": \"mysql\" }");
        testSubnet4DelId(subnet, 1, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to delete subnets by id are
// rejected and proper error messages are returned.
TEST_F(Subnet4CmdsTest, subnet4DelByIdFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnet4DelIdFail("", "invalid command 'remote-subnet4-del-by-id': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty subnet4 list");
        testSubnet4DelIdFail("\"subnets\": [ ]", "'subnets' list "
                             "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty subnet map");
        testSubnet4DelIdFail("\"subnets\": [ { } ]", "missing 'id' parameter");
    }

    {

        SCOPED_TRACE("malformed id");
        testSubnet4DelIdFail("\"subnets\": [ { \"id\": true } ]",
                             "'id' parameter is not an integer");
    }

    {
        SCOPED_TRACE("zero subnet id");
        testSubnet4DelIdFail("\"subnets\": [ { \"id\": 0 } ]",
                             "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("invalid subnet id");
        testSubnet4DelIdFail("\"subnets\": [ { \"id\": 4294967295 } ]",
                             "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("malformed subnet");
        testSubnet4DelIdFail("\"subnets\": [ { \"interface\": \"eth1\" } ]",
                             "missing 'id' parameter");
    }

    {
        SCOPED_TRACE("spurious prefix");
        testSubnet4DelIdFail("\"subnets\": [ { "
                             "\"id\": 1, \"subnet\": \"192.0.2.0/24\" } ]",
                             "spurious 'subnet' parameter");
    }

    {
        SCOPED_TRACE("multiple subnets");
        testSubnet4DelIdFail("\"subnets\": ["
                             "{ \"id\": 1 },"
                             "{ \"id\": 2 }"
                           "]",
                           "'subnets' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSubnet4DelIdFail("\"server-tags\": [ ]",
                             "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnet4DelIdFail("\"subnets\": ["
                           "    { \"id\": 1 }"
                           "],"
                           "\"remote\": {"
                           "    \"type\": \"postgresql\""
                           "}",
                           "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to delete subnet by prefix.
TEST_F(Subnet4CmdsTest, subnet4DelByPrefix) {
    {
        SCOPED_TRACE("add and delete subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        testSubnet4Set(subnet);
        testSubnet4DelPrefix(subnet, 1);
    }

    {
        SCOPED_TRACE("add and delete another subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        testSubnet4Set(subnet);
        testSubnet4DelPrefix(subnet, 1);
    }

    {
        SCOPED_TRACE("delete subnet");
        // Deleting not existing is not an error.
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        testSubnet4DelPrefix(subnet, 0);
    }

    {
        SCOPED_TRACE("delete another subnet with specifying remote");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 40, 50, 60, 2));
        testSubnet4Set(subnet, "{ \"type\": \"mysql\" }");
        testSubnet4DelPrefix(subnet, 1, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to delete subnets by prefix
//  are rejected and proper error messages are returned.
TEST_F(Subnet4CmdsTest, subnet4DelByPrefixFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnet4DelPrefixFail("", "invalid command 'remote-subnet4-del-by-prefix': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty subnets list");
        testSubnet4DelPrefixFail("\"subnets\": [ ]", "'subnets' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty subnet map");
        testSubnet4DelPrefixFail("\"subnets\": [ { } ]",
                                 "missing 'subnet' parameter");
    }

    {
        SCOPED_TRACE("malformed subnet");
        testSubnet4DelPrefixFail("\"subnets\": [ { \"interface\": \"eth1\" } ]",
                                 "missing 'subnet' parameter");
    }

    {
        SCOPED_TRACE("empty subnet");
        testSubnet4DelPrefixFail("\"subnets\": [ { \"subnet\": \"\" } ]",
                                 "'subnet' parameter must not be empty");

    }

    {
        SCOPED_TRACE("invalid subnet");
        testSubnet4DelPrefixFail("\"subnets\": [ { \"subnet\": \"foo\" } ]",
                                 "unable to parse invalid prefix foo");
    }

    {
        SCOPED_TRACE("spurious id");
        testSubnet4DelPrefixFail("\"subnets\": [ { "
                                 "\"subnet\": \"192.0.2.0/24\", \"id\": 1 } ]",
                                 "spurious 'id' parameter");
    }

    {
        SCOPED_TRACE("multiple subnets");
        testSubnet4DelPrefixFail("\"subnets\": ["
                                 "{ \"subnet\": \"192.0.2.0/24\" },"
                                 "{ \"subnet\": \"192.0.3.0/24\" }"
                                 "]",
                                 "'subnets' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSubnet4DelPrefixFail("\"server-tags\": [ ]",
                                 "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnet4DelPrefixFail("\"subnets\": ["
                                 "    { \"subnet\": \"192.0.2.0/24\" }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get subnet by id.
TEST_F(Subnet4CmdsTest, subnet4GetById) {
    {
        SCOPED_TRACE("add and get subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        subnet->setServerTag("server1");
        testSubnet4Set(subnet, "", { "server1" });
        testSubnet4GetId(subnet, subnet);
    }

    {
        SCOPED_TRACE("add and get another subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        subnet->setServerTag(ServerTag::ALL);
        testSubnet4Set(subnet);
        testSubnet4GetId(subnet, subnet);
    }

    {
        SCOPED_TRACE("get no subnet");
        // Getting not existing is not an error.
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.4.0"), 24, 30, 40, 60, 3));
        testSubnet4GetId(subnet, Subnet4Ptr());
    }

    {
        SCOPED_TRACE("get another subnet with specifying remote");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.5.0"), 24, 40, 50, 60, 4));
        subnet->setServerTag(ServerTag::ALL);
        testSubnet4Set(subnet, "{ \"type\": \"mysql\" }");
        testSubnet4GetId(subnet, subnet, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to get subnets by id are
// rejected and proper error messages are returned.
TEST_F(Subnet4CmdsTest, subnet4GetByIdFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnet4GetIdFail("", "invalid command 'remote-subnet4-get-by-id': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty subnets list");
        testSubnet4GetIdFail("\"subnets\": [ ]", "'subnets' list "
                             "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty subnet map");
        testSubnet4GetIdFail("\"subnets\": [ { } ]", "missing 'id' parameter");
    }

    {

        SCOPED_TRACE("malformed id");
        testSubnet4GetIdFail("\"subnets\": [ { \"id\": true } ]",
                             "'id' parameter is not an integer");
    }

    {
        SCOPED_TRACE("zero subnet id");
        testSubnet4GetIdFail("\"subnets\": [ { \"id\": 0 } ]",
                             "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("invalid subnet id");
        testSubnet4GetIdFail("\"subnets\": [ { \"id\": 4294967295 } ]",
                             "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("malformed subnet");
        testSubnet4GetIdFail("\"subnets\": [ { \"interface\": \"eth1\" } ]",
                             "missing 'id' parameter");
    }

    {
        SCOPED_TRACE("spurious prefix");
        testSubnet4GetIdFail("\"subnets\": [ { "
                             "\"id\": 1, \"subnet\": \"192.0.2.0/24\" } ]",
                             "spurious 'subnet' parameter");
    }

    {
        SCOPED_TRACE("multiple subnets");
        testSubnet4GetIdFail("\"subnets\": ["
                             "{ \"id\": 1 },"
                             "{ \"id\": 2 }"
                           "]",
                           "'subnets' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSubnet4GetIdFail("\"server-tags\": [ ]",
                             "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnet4GetIdFail("\"subnets\": ["
                           "    { \"id\": 1 }"
                           "],"
                           "\"remote\": {"
                           "    \"type\": \"postgresql\""
                           "}",
                           "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get subnet by prefix.
TEST_F(Subnet4CmdsTest, subnet4GetByPrefix) {
    {
        SCOPED_TRACE("add and get subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
        subnet->setServerTag("server1");
        testSubnet4Set(subnet, "", { "server1" });
        testSubnet4GetPrefix(subnet, subnet);
    }

    {
        SCOPED_TRACE("add and get another subnet");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
        subnet->setServerTag(ServerTag::ALL);
        testSubnet4Set(subnet);
        testSubnet4GetPrefix(subnet, subnet);
    }

    {
        SCOPED_TRACE("get no subnet");
        // Getting not existing is not an error.
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.4.0"), 24, 30, 40, 60, 3));
        testSubnet4GetPrefix(subnet, Subnet4Ptr());
    }

    {
        SCOPED_TRACE("get another subnet with specifying remote");
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.5.0"), 24, 40, 50, 60, 4));
        subnet->setServerTag(ServerTag::ALL);
        testSubnet4Set(subnet, "{ \"type\": \"mysql\" }");
        testSubnet4GetPrefix(subnet, subnet, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to get subnets by prefix
//  are rejected and proper error messages are returned.
TEST_F(Subnet4CmdsTest, subnet4GetByPrefixFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnet4GetPrefixFail("", "invalid command 'remote-subnet4-get-by-prefix': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty subnets list");
        testSubnet4GetPrefixFail("\"subnets\": [ ]", "'subnets' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty subnet map");
        testSubnet4GetPrefixFail("\"subnets\": [ { } ]",
                                 "missing 'subnet' parameter");
    }

    {
        SCOPED_TRACE("malformed subnet");
        testSubnet4GetPrefixFail("\"subnets\": [ { \"interface\": \"eth1\" } ]",
                                 "missing 'subnet' parameter");
    }

    {
        SCOPED_TRACE("empty subnet");
        testSubnet4GetPrefixFail("\"subnets\": [ { \"subnet\": \"\" } ]",
                                 "'subnet' parameter must not be empty");

    }

    {
        SCOPED_TRACE("invalid subnet");
        testSubnet4GetPrefixFail("\"subnets\": [ { \"subnet\": \"foo\" } ]",
                                 "unable to parse invalid prefix foo");
    }

    {
        SCOPED_TRACE("spurious id");
        testSubnet4GetPrefixFail("\"subnets\": [ { "
                                 "\"subnet\": \"192.0.2.0/24\", \"id\": 1 } ]",
                                 "spurious 'id' parameter");
    }

    {
        SCOPED_TRACE("multiple subnets");
        testSubnet4GetPrefixFail("\"subnets\": ["
                                 "{ \"subnet\": \"192.0.2.0/24\" },"
                                 "{ \"subnet\": \"192.0.3.0/24\" }"
                                 "]",
                                 "'subnets' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSubnet4GetPrefixFail("\"server-tags\": [ ]",
                                 "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnet4GetPrefixFail("\"subnets\": ["
                                 "    { \"subnet\": \"192.0.2.0/24\" }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get all subnets.
TEST_F(Subnet4CmdsTest, subnet4List) {
    // Empty.
    ElementPtr expected = Element::createList();
    ElementPtr expected_all = Element::createList();
    ElementPtr expected_unassigned = Element::createList();
    testSubnet4List(expected);
    testSubnet4List(expected_all);
    testSubnet4List(expected_unassigned);

    // Add a subnet.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
    subnet->setServerTag("server1");
    testSubnet4Set("test4", subnet, "", { "server1" });
    ElementPtr sub = Element::createMap();
    sub->set("id", Element::create(1));
    sub->set("subnet", Element::create("192.0.2.0/24"));
    sub->set("shared-network-name", Element::create("test4"));
    sub->set("metadata", createMetadata("server1"));
    expected->add(sub);
    testSubnet4List(expected, "", { "server1" });

    // Add a second subnet.
    subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 2));
    subnet->setServerTag(ServerTag::ALL);
    testSubnet4Set(subnet);
    sub = Element::createMap();
    sub->set("id", Element::create(2));
    sub->set("subnet", Element::create("192.0.3.0/24"));
    sub->set("shared-network-name", Element::create());
    sub->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(sub);
    expected_all->add(sub);
    testSubnet4List(expected, "", { "server1" });
    testSubnet4List(expected_all);

    // With another server only subnets belonging to all are returned.
    testSubnet4List(expected_all, "", { "server2" });

    // Try with a remote.
    subnet.reset(new Subnet4(IOAddress("192.0.5.0"), 24, 40, 50, 60, 4));
    subnet->setServerTag(ServerTag::ALL);
    testSubnet4Set(subnet, "{ \"type\": \"mysql\" }");
    sub = Element::createMap();
    sub->set("id", Element::create(4));
    sub->set("subnet", Element::create("192.0.5.0/24"));
    sub->set("shared-network-name", Element::create());
    sub->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(sub);
    expected_all->add(sub);
    testSubnet4List(expected, "{ \"type\": \"mysql\" }", { "server1" });
    testSubnet4List(expected_all, "{ \"type\": \"mysql\" }");

    // Add a third subnet in another server.
    subnet.reset(new Subnet4(IOAddress("192.0.6.0"), 24, 40, 50, 60, 5));
    subnet->setServerTag("server2");
    testSubnet4Set(subnet, "", { "server2" });
    // Not in server1 so not yet expected.
    testSubnet4List(expected, "", { "server1" });
    sub = Element::createMap();
    sub->set("id", Element::create(5));
    sub->set("subnet", Element::create("192.0.6.0/24"));
    sub->set("shared-network-name", Element::create());
    sub->set("metadata", createMetadata("server2"));
    expected->add(sub);
    testSubnet4List(expected, "", { "server1", "server2" });

    // Now try unassigned.
    testSubnet4List(expected_unassigned, "", { });
    subnet.reset(new Subnet4(IOAddress("192.0.7.0"), 24, 40, 50, 60, 6));
    // Adds it directly to the backend (no command yet to do this).
    setSubnet(subnet);
    // Not visible by a server.
    testSubnet4List(expected, "", { "server1", "server2" });
    sub = Element::createMap();
    sub->set("id", Element::create(6));
    sub->set("subnet", Element::create("192.0.7.0/24"));
    sub->set("shared-network-name", Element::create());
    sub->set("metadata", createMetadata(std::set<std::string>()));
    expected_unassigned->add(sub);
    testSubnet4List(expected_unassigned, "", { });
}

// This test verifies that malformed requests to get subnets by id are
// rejected and proper error messages are returned.
TEST_F(Subnet4CmdsTest, subnet4ListFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnet4ListFail(", \"arguments\": { }",
                            "invalid command 'remote-subnet4-list': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("no server tags");
        testSubnet4ListFail(", \"arguments\": { \"remote\": { } }",
                            "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testSubnet4ListFail(", \"arguments\": { \"server-tags\": [ ] }",
                            "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("bad formed unassigned");
        testSubnet4ListFail(", \"arguments\": { "
                            "\"server-tags\": [ null, \"all\" ] }",
                            "when the 'server-tags' list contains "
                            "multiple elements all these elements must "
                            "have the string type");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnet4ListFail(", \"arguments\": { "
                            "\"server-tags\": [ \"all\"], "
                            "\"remote\": {"
                            "    \"type\": \"postgresql\""
                            "} }",
                            "no such database found for selector: type=postgresql");
    }
}

}
