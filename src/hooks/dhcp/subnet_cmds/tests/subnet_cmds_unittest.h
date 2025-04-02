// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <hooks/hooks_manager.h>
#include <config/command_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <process/daemon.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace {

struct Scenario {
    std::string desc_;                          // scenario description
    std::string command_;                       // command to run
    std::string exp_response_;                  // expected response
    uint8_t exp_code_;                          // expected return code
    bool check_has_subnet_;                     // check that the response contains subnet
    std::string exp_text_;                      // expected text
    std::vector<uint8_t> rerun_scenario_;       // list of scenarios to run again
};

/// @brief Handler type
typedef std::function<void (const Scenario& test)> HandlerType;

/// @brief Test fixture class for Subnet Commands hook library.
class SubnetCmdsTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Clears the configuration and unloads hook libraries.
    SubnetCmdsTest() {
        isc::dhcp::CfgMgr::instance().clear();
        unloadLibs();
        isc::dhcp::LeaseMgrFactory::create("type=memfile universe=4 persist=false");
    }

    /// @brief Destructor
    ///
    /// Clears the configuration and unloads hook libraries.
    virtual ~SubnetCmdsTest() {
        isc::dhcp::LeaseMgrFactory::destroy();
        isc::dhcp::CfgMgr::instance().clear();
        isc::dhcp::LibDHCP::clearRuntimeOptionDefs();
        unloadLibs();
    }

    /// @brief Set family.
    ///
    /// @param family Address family: either AF_INET or AF_INET6.
    void setFamily(uint16_t family) {
        isc::dhcp::CfgMgr::instance().setFamily(family);
        isc::process::Daemon::setProcName(family == AF_INET ?
                                          "kea-dhcp4" : "kea-dhcp6");
    }

    /// @brief Adds library/parameters to list of libraries to be loaded.
    ///
    /// @param lib Path to the library.
    /// @param params Pointer to the parameters with which library should
    /// be configured.
    void addLib(const std::string& lib, const isc::data::ConstElementPtr& params) {
        libraries_.push_back(make_pair(lib, params));
    }

    /// @brief Load all specified libraries.
    ///
    /// The libraries are stored in @c libraries_ member.
    void loadLibs() {
        ASSERT_TRUE(isc::hooks::HooksManager::loadLibraries(libraries_))
            << "library loading failed";
    }

    /// @brief Loads subnet commands library
    void loadSubnetCmds() {
        if (libraries_.empty()) {
            isc::data::ElementPtr params = isc::data::Element::createMap();
            addLib(LIB_SO, params);
        }
        ASSERT_NO_FATAL_FAILURE(loadLibs());
    }

    /// @brief Unloads all libraries.
    void unloadLibs() {
        ASSERT_NO_THROW(isc::hooks::HooksManager::unloadLibraries());
    }

    /// @brief Generates and adds 5 IPv4 reservations to a subnet.
    ///
    /// @param subnet Pointer to the subnet for which reservations should
    /// be added.
    /// @param cfg_hosts Pointer to the hosts configuration where the
    /// reservations should be stored.
    void addReservations(const isc::dhcp::Subnet4Ptr& subnet,
                         const isc::dhcp::CfgHostsPtr& cfg_hosts) {
        // We're going to add several host reservations to the subnet.
        // The reservations must match the subnet prefix. The easiest
        // way is to create the pool with the capacity of the entire
        // subnet prefix and then pick several addresses to be reserved.
        isc::dhcp::Pool4 pool(subnet->get().first, subnet->get().second);
        isc::asiolink::IOAddress reservation = pool.getFirstAddress();
        // Add 5 host reservations.
        for (auto i = 0; i < 5; ++i) {
            // Generate unique HW address.
            std::vector<uint8_t> identifier(6, i);

            // Create the host and the IPv4 reservation.
           isc::dhcp::HostPtr host(new isc::dhcp::Host(&identifier[0], identifier.size(),
                                                       isc::dhcp::Host::IDENT_HWADDR,
                                                       subnet->getID(), 0,
                                                       reservation));

            // Add the host.
            cfg_hosts->add(host);
            // Use next reservation.
            reservation = isc::asiolink::IOAddress::increase(reservation);
        }
    }

    /// @brief Generates and adds 5 IPv6 reservations to a subnet.
    ///
    /// @param subnet Pointer to the subnet for which reservations should
    /// be added.
    /// @param cfg_hosts Pointer to the hosts configuration where the
    /// reservations should be stored.
    void addReservations(const isc::dhcp::Subnet6Ptr& subnet,
                         const isc::dhcp::CfgHostsPtr& cfg_hosts) {
        // We're going to add several host reservations to the subnet.
        // The reservations must match the subnet prefix. The easiest
        // way is to create the pool with the capacity of the entire
        // subnet prefix and then pick several addresses to be reserved.
        isc::dhcp::Pool6 pool(isc::dhcp::Lease::TYPE_NA, subnet->get().first, subnet->get().second);
        isc::asiolink::IOAddress reservation = pool.getFirstAddress();
        // Add 5 host reservations.
        for (auto i = 0; i < 5; ++i) {
            // Generate unique HW address.
            std::vector<uint8_t> identifier(6, i);

            // Create the host and the IPv6 reservation.
           isc::dhcp::HostPtr host(new isc::dhcp::Host(&identifier[0], identifier.size(),
                                                       isc::dhcp::Host::IDENT_HWADDR,
                                                       isc::dhcp::SUBNET_ID_UNUSED,
                                                       subnet->getID(),
                                                       isc::asiolink::IOAddress::IPV4_ZERO_ADDRESS()));
            isc::dhcp::IPv6Resrv resrv(isc::dhcp::IPv6Resrv::TYPE_NA, reservation, 128);
            host->addReservation(resrv);

            // Add the host.
            cfg_hosts->add(host);
            // Use next reservation.
            reservation = isc::asiolink::IOAddress::increase(reservation);
        }
    }

    /// @brief Adds IPv4 or IPv6 subnet to the server's configuration.
    ///
    /// The only values explicitly set for the created subnets are: prefix,
    /// prefix length and subnet identifier. Other parameters are auto generated.
    ///
    /// @param subnet_str Subnet in a textual form, e.g. 10.0.0.0/8 or
    /// 2001:db8::/64.
    /// @param subnet_id Subnet id.
    /// @param shared_network_name name of shared-network, defaults to empty string.
    void addSubnet(const std::string& subnet_str, const isc::dhcp::SubnetID& subnet_id,
                   const std::string& shared_network_name = "") {
        try {
            // Split prefix and prefix length.
            auto split_pos = subnet_str.find('/');
            if ((split_pos == std::string::npos) ||
                (split_pos == subnet_str.size() - 1)) {
                ADD_FAILURE() << "invalid subnet " << subnet_str;
                return;
            }

            isc::asiolink::IOAddress prefix(subnet_str.substr(0, split_pos));

            // Convert prefix length to a number.
            unsigned prefix_length = boost::lexical_cast<unsigned>
                (subnet_str.substr(split_pos + 1));

            // Create Subnet4 or Subnet6 object, depending on the detected prefix
            // type.
            if (prefix.isV4()) {
                isc::dhcp::CfgSubnets4Ptr cfg = isc::dhcp::CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
                isc::dhcp::Subnet4Ptr subnet(new isc::dhcp::Subnet4(prefix, prefix_length, 30, 40, 60, subnet_id));
                if (!shared_network_name.empty()) {
                    subnet->setSharedNetworkName(shared_network_name);
                }

                cfg->add(subnet);
                addReservations(subnet, isc::dhcp::CfgMgr::instance().getStagingCfg()->getCfgHosts());

            } else {
                isc::dhcp::CfgSubnets6Ptr cfg = isc::dhcp::CfgMgr::instance().getStagingCfg()->getCfgSubnets6();
                isc::dhcp::Subnet6Ptr subnet(new isc::dhcp::Subnet6(prefix, prefix_length, 30, 40, 50, 60, subnet_id));
                if (!shared_network_name.empty()) {
                    subnet->setSharedNetworkName(shared_network_name);
                }

                cfg->add(subnet);
                addReservations(subnet, isc::dhcp::CfgMgr::instance().getStagingCfg()->getCfgHosts());
            }

        } catch (const std::exception& ex) {
            ADD_FAILURE() << "failed to add new subnet " << subnet_str
                   << ", reason: " << ex.what();
        }
    }

    /// @brief Adds an empty (without subnets) shared network
    ///
    /// @param name name of the network to be added
    /// @param v6 should this network be v4 (false) or v6 (true)
    void addEmptyNetwork(const std::string& name, bool v6) {
        if (!v6) {
            isc::dhcp::SharedNetwork4Ptr network(new isc::dhcp::SharedNetwork4(name));
            isc::dhcp::CfgSharedNetworks4Ptr cfg = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
            EXPECT_NO_THROW(cfg->add(network));
        } else {
            isc::dhcp::SharedNetwork6Ptr network(new isc::dhcp::SharedNetwork6(name));
            isc::dhcp::CfgSharedNetworks6Ptr cfg = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
            EXPECT_NO_THROW(cfg->add(network));
        }
    }

    /// @brief Checks whether specified command is registered
    ///
    /// @param name name of the command to be checked
    /// @return true if the command handler has been registered, false otherwise.
    bool checkCommandRegistered(const std::string& name) {
        // First get the list of registered commands
        isc::data::ConstElementPtr lst = isc::data::Element::fromJSON("{ \"command\": \"list-commands\" }");
        isc::data::ConstElementPtr rsp = isc::config::CommandMgr::instance().processCommand(lst);
        if (!rsp) {
            ADD_FAILURE() << "failed to process 'list-commands'";
            return (false);
        }

        isc::data::ConstElementPtr args = rsp->get("arguments");
        if (!args) {
            ADD_FAILURE() << "response to list-commands does not contain any"
                " arguments";
        }

        std::string args_txt = args->str();

        return (args_txt.find(name) != std::string::npos);
    }

    /// @brief Tests specified command and verifies response
    ///
    /// This method loads the subnet cmds library, sends specific command,
    /// then checks if the result is as expected, checks if text response
    /// is ok (optional, check skipped if exp_txt is empty) and then returns
    /// the response (for possible additional checks).
    ///
    /// @param cmd JSON command to be sent (must be valid JSON)
    /// @param exp_result 0 for success, non-zero otherwise.
    /// @param exp_txt expected text response (optional)
    /// @return full response returned by the command execution.
    isc::data::ConstElementPtr testCommand(const std::string& cmd_txt,  const int exp_result,
                                           const std::string& exp_txt = "") {
        // Let's load the library first.
        loadSubnetCmds();

        isc::data::ConstElementPtr cmd;
        EXPECT_NO_THROW(cmd = isc::data::Element::fromJSON(cmd_txt));
        if (!cmd) {
            ADD_FAILURE() << cmd_txt << " is not a valid JSON, test broken";
            return (isc::data::ConstElementPtr());
        }

        // Send the command and receive response.
        isc::data::ConstElementPtr rsp = isc::config::CommandMgr::instance().processCommand(cmd);

        // Check that the expected parameters are correct.
        checkAnswer(rsp, exp_result, exp_txt);

        // Return response for additional checks.
        return (rsp);
    }

    /// @brief Generic method for testing 'subnet4-get' and 'subnet6-get'
    /// commands.
    ///
    /// This test invokes @c testCommand for a command specified as a parameter.
    /// The expected commands are 'subnet4-get' and 'subnet6-get'. It expects
    /// that the result contains a single subnet and the text information
    /// informing that the subnet has been returned.
    ///
    /// It also verifies that the returned arguments have appropriate structure
    /// and tests selected values of the subnet returned.
    ///
    /// @param command 'subnet4-get' or 'subnet6-get' command including one of
    /// the supported parameters by which the subnet should be found.
    /// @param subnet_prefix Subnet prefix, e.g. 10.1.2.0/24.
    /// @param subnet_id Subnet identifier.
    void testSubnetGet(const std::string& command, const std::string& subnet_prefix,
                       const isc::dhcp::SubnetID& subnet_id) {
        // Determine the subnet type: "4" or "6" for IPv4 and IPv6 subnet
        // respectively.
        const std::string subnet_type =
            (command.find("subnet4-get") != std::string::npos) ? "4" : "6";

        // Construct the expected text message to be returned within the response.
        std::ostringstream text;
        text << "Info about IPv" << subnet_type << " subnet " << subnet_prefix
             << " (id " << subnet_id << ") returned";
        isc::data::ConstElementPtr response = testCommand(command, isc::config::CONTROL_RESULT_SUCCESS,
                                                          text.str());

        // Get arguments which must be a map.
        int rcode = 0;
        isc::data::ConstElementPtr args;
        ASSERT_NO_THROW(args = isc::config::parseAnswer(rcode, response));
        ASSERT_TRUE(args);
        ASSERT_EQ(isc::data::Element::map, args->getType());

        // Retrieve 'subnet4' or 'subnet6 (depending on the subnet_type).
        std::string subnet_parameter = "subnet" + subnet_type;
        isc::data::ConstElementPtr subnet_list = args->get(subnet_parameter);
        ASSERT_TRUE(subnet_list);
        ASSERT_EQ(isc::data::Element::list, subnet_list->getType());
        ASSERT_EQ(1, subnet_list->size());

        // Subnet is stored within a list, even though this is a single element.
        // In the future we may want to query for a collection of subnets.
        isc::data::ConstElementPtr subnet = subnet_list->get(0);
        ASSERT_TRUE(subnet);
        ASSERT_EQ(isc::data::Element::map, subnet->getType());

        // The subnet prefix is stored in 'subnet' parameter.
        isc::data::ConstElementPtr subnet_prefix_found = subnet->get("subnet");
        ASSERT_TRUE(subnet_prefix_found);
        ASSERT_EQ(isc::data::Element::string, subnet_prefix_found->getType());
        EXPECT_EQ(subnet_prefix, subnet_prefix_found->stringValue());

        // It should also contain subnet id.
        isc::data::ConstElementPtr subnet_id_found = subnet->get("id");
        ASSERT_TRUE(subnet_id_found);
        ASSERT_EQ(isc::data::Element::integer, subnet_id_found->getType());
        EXPECT_EQ(subnet_id, subnet_id_found->intValue());

        // There are tons of other parameters stored within this structure
        // but we don't want to test all of them. The subnet information
        // should be produced using Subnet::toElement function which should
        // be tested elsewhere.
    }

    /// @brief Test retrieving subnet by subnet id.
    ///
    /// @param command_name Command name, i.e. 'subnet4-get' or 'subnet6-get'.
    /// @param subnet_prefix Subnet prefix, e.g. 10.2.3.0/24
    /// @param subnet_id Subnet identifier.
    void testSubnetGetById(const std::string& command_name,
                           const std::string& subnet_prefix,
                           const isc::dhcp::SubnetID& subnet_id) {
        std::ostringstream command;
        command << "{\n"
            "    \"command\": \"" << command_name <<"\",\n"
            "    \"arguments\": {\n"
            "        \"id\": " << subnet_id << "\n"
            "    }\n"
            "}\n";

        testSubnetGet(command.str(), subnet_prefix, subnet_id);
    }

    /// @brief Test retrieving subnet by subnet prefix.
    ///
    /// @param command_name Command name, i.e. 'subnet4-get' or 'subnet6-get'.
    /// @param subnet_prefix Subnet prefix, e.g. 10.2.3.0/24
    /// @param subnet_id Subnet identifier.
    void testSubnetGetByPrefix(const std::string& command_name,
                               const std::string& subnet_prefix,
                               const isc::dhcp::SubnetID& subnet_id) {
        std::ostringstream command;
        command << "{\n"
            "    \"command\": \"" << command_name <<"\",\n"
            "    \"arguments\": {\n"
            "        \"subnet\": \"" << subnet_prefix << "\"\n"
            "    }\n"
            "}\n";

        testSubnetGet(command.str(), subnet_prefix, subnet_id);
    }

    /// @brief Tests negative scenarios for various commands.
    ///
    /// @param command_name Command name.
    /// @param arguments A string containing arguments but without the word
    /// \"arguments\": which opens the map. If the string is empty, the
    /// \"arguments\": is not included in the command name. This is useful to
    /// test commands that lack arguments map.
    /// @param expected_text Test expected to be returned in the response.
    /// @param exp_result Expected result (CONTROL_RESULT_ERROR if not specified)
    void testCommandNegative(const std::string& command_name,
                             const std::string& arguments,
                             const std::string& expected_text,
                             int exp_result = isc::config::CONTROL_RESULT_ERROR) {
        std::ostringstream command;
        command << "{ \"command\": \"" << command_name << "\"";
        // Only add arguments parameter if arguments are not empty.
        if (!arguments.empty()) {
            command << ", \"arguments\": " << arguments;
        }
        command << "}";

        // Before we run the command let's check if the statistics cotains any
        // subnet-level statistics. It will be needed to verify that the failing
        // command did not remove the subnet-level statistics.
        auto stats = isc::stats::StatsMgr::instance().getAll();
        ASSERT_TRUE(stats);
        ASSERT_EQ(isc::data::Element::map, stats->getType());
        auto map_value = stats->mapValue();
        auto has_subnet_stats = false;
        for (auto pair : map_value) {
            if (pair.first.find("].total-addresses") != std::string::npos ||
                (pair.first.find("].total-nas")) != std::string::npos) {
                has_subnet_stats = true;
                break;
            }
        }

        // Test the command. Expect error status and the status text provided
        // by the caller.
        testCommand(command.str(), exp_result, expected_text);

        // If there had been no subnet-level stats there is nothing more to test.
        if (!has_subnet_stats) {
            return;
        }

        // Make sure that the subnet statistics exists.
        stats = isc::stats::StatsMgr::instance().getAll();
        ASSERT_TRUE(stats);
        ASSERT_EQ(isc::data::Element::map, stats->getType());
        map_value = stats->mapValue();
        has_subnet_stats = false;
        for (auto pair : map_value) {
            if (pair.first.find("].total-addresses") != std::string::npos ||
                (pair.first.find("].total-nas")) != std::string::npos) {
                has_subnet_stats = true;
                break;
            }
        }
        EXPECT_TRUE(has_subnet_stats);
    }

    /// @brief Checks the status code and message against expected values.
    ///
    /// @param answer Element set containing an integer response and string
    /// comment.
    /// @param exp_status Status code against which to compare the status.
    /// @param exp_txt Expected text (not checked if empty)
    void checkAnswer(const isc::data::ConstElementPtr& answer,
                     const int exp_status, const std::string& exp_txt = "") {
        int rcode = 0;
        isc::data::ConstElementPtr comment;
        comment = isc::config::parseAnswer(rcode, answer);

        EXPECT_EQ(exp_status, rcode)
            << "Expected status code " << exp_status
            << " but received " << rcode << ", comment: "
            << (comment ? comment->str() : "(none)");

        // Ok, parseAnswer interface is weird. If there are no arguments,
        // it returns content of text. But if there is an argument,
        // it returns the argument and it's not possible to retrieve
        // "text" (i.e. comment).
        if (comment->getType() != isc::data::Element::string) {
            comment = answer->get("text");
        }

        if (!exp_txt.empty()) {
            EXPECT_EQ(exp_txt, comment->stringValue());
        }
    }

    /// @brief Verifies the content of the "args" element in the response.
    ///
    /// @param answer Server's response to a command.
    /// @param exp_args JSON map of the expected arguments contents.
    void checkResponseArgs(const isc::data::ConstElementPtr& answer,
                           const std::string exp_args) {
        // Retrieve "arguments" and make sure it is a map.
        int rcode = 0;
        isc::data::ConstElementPtr args = isc::config::parseAnswer(rcode, answer);
        ASSERT_TRUE(args);
        ASSERT_EQ(isc::data::Element::map, args->getType());

        isc::data::ConstElementPtr exp_args_map;
        ASSERT_NO_THROW_LOG(exp_args_map = isc::data::Element::fromJSON(exp_args));

        isc::test::expectEqWithDiff(args, exp_args_map);
    }

    /// @brief Checks that the response includes a given subnet.
    ///
    /// @param answer Server's response.
    /// @param subnet Expected subnet prefix.
    /// @param subnet_id Expected subnet identifier.
    ///
    /// @return true if the given subnet is included in the response.
    bool hasSubnet(const isc::data::ConstElementPtr& answer,
                   const std::string& subnet,
                   const isc::dhcp::SubnetID& subnet_id) const {
        if (!answer) {
            ADD_FAILURE() << "Answer not specified";
            return (false);
        }
        int rcode = 0;
        isc::data::ConstElementPtr args = isc::config::parseAnswer(rcode, answer);
        if (!args) {
            ADD_FAILURE() << "Unable to parse answer: " << answer->str();
            return (false);
        }
        if (args->getType() != isc::data::Element::map) {
            ADD_FAILURE() << "The answer doesn't have any parameters";
            return (false);
        }

        isc::data::ConstElementPtr subnet_ids = args->get("subnets");
        if (!subnet_ids) {
            ADD_FAILURE() << "Expected 'subnets' missing.";
            return (false);
        }

        // Iterate over all returned subnet and try to find a match.
        for (unsigned index = 0; index != subnet_ids->size(); ++index) {
            isc::data::ConstElementPtr subnet_element = subnet_ids->get(index);
            if (!subnet_element) {
                ADD_FAILURE() << "Malformed subnets list";
                return (false);
            }
            if (!subnet_element->get("id")) {
                ADD_FAILURE() << "Mandatory 'id' parameter missing";
                return (false);
            }
            if (!subnet_element->get("subnet")) {
                ADD_FAILURE() << "Mandatory 'subnet' parameter missing";
                return (false);
            }
            // Both subnet prefix and subnet identifier should match.
            if ((subnet_element->get("id")->intValue() == subnet_id) &&
                (subnet_element->get("subnet")->stringValue() == subnet)) {
                return (true);
            }
        }

        // Subnet not found.
        return (false);
    }

    /// @brief Checks that the response includes a given shared network.
    ///
    /// For networkX-get, the detailed parameters as well as subnets will be returned.
    /// Those can be checked if expect_params is true and subnet is non-empty.
    ///
    /// @param answer Server's response.
    /// @param name name of the network to be checked
    /// @param check_params whether network parameters should be checked
    /// @param subnet Expected subnet prefix (if empty, subnet check is omitted)
    /// @param v6 is this v4 (false) or v6 (true) subnet?
    ///
    /// @return true if the validation was successful (network is included, has expected
    ///         parameters and expected subnet was found)
    bool hasNetwork(const isc::data::ConstElementPtr& answer,
                    const std::string& name, bool expect_params,
                    const std::string& subnet, bool v6) {
        if (!answer) {
            ADD_FAILURE() << "Answer not specified";
            return (false);
        }
        int rcode = 0;
        isc::data::ConstElementPtr args = isc::config::parseAnswer(rcode, answer);
        if (!args) {
            ADD_FAILURE() << "Unable to parse answer: " << answer->str();
            return (false);
        }
        if (args->getType() != isc::data::Element::map) {
            ADD_FAILURE() << "The answer doesn't have any parameters";
            return (false);
        }

        isc::data::ConstElementPtr networks = args->get("shared-networks");
        if (!networks) {
            ADD_FAILURE() << "Expected 'shared-networks' missing.";
            return (false);
        }

        bool found = false;

        // Iterate over all returned subnet and try to find a match.
        for (unsigned index = 0; index != networks->size(); ++index) {
            isc::data::ConstElementPtr net = networks->get(index);
            if (!net) {
                ADD_FAILURE() << "Malformed shared networks list";
                return (false);
            }
            if (!net->get("name")) {
                ADD_FAILURE() << "Mandatory 'name' parameter missing";
                return (false);
            }

            // Do we expect all network parameters?
            if (expect_params) {
                EXPECT_FALSE(net->get("match-client-id"));
                EXPECT_TRUE(net->get("option-data"));
                EXPECT_FALSE(net->get("rebind-timer"));
                EXPECT_TRUE(net->get("relay"));
                EXPECT_FALSE(net->get("renew-timer"));
                EXPECT_FALSE(net->get("reservations-in-subnet"));
                EXPECT_FALSE(net->get("valid-lifetime"));

                if (v6) {
                    EXPECT_TRUE(net->get("subnet6"));
                    EXPECT_FALSE(net->get("subnet4"));
                } else {
                    EXPECT_TRUE(net->get("subnet4"));
                    EXPECT_FALSE(net->get("subnet6"));
                }
            }

            if (net->get("name")->stringValue() != name) {
                // this is not our network, keep looking
                continue;
            }
            found = true; // ok, this *is* our network

            // If subnet has been specified, check it!
            if (!subnet.empty()) {

                // Ok, network was found, but we still need to find a subnet.
                found = false;
                std::string param = (v6 ? "subnet6" : "subnet4");
                isc::data::ConstElementPtr subnets = net->get(param);
                if (!subnets) {
                    // Something is wrong. There's no subnet element.
                    ADD_FAILURE() << "Unable to find " << param << ", can't find " << subnet;
                    return (false);
                }

                // Iterate over all returned subnet and try to find a match.
                for (unsigned idx = 0; idx != subnets->size(); ++idx) {
                    isc::data::ConstElementPtr subnet_element = subnets->get(idx);
                    if (!subnet_element) {
                        ADD_FAILURE() << "Malformed subnets list";
                        return (false);
                    }
                    if (!subnet_element->get("id")) {
                        ADD_FAILURE() << "Mandatory 'id' parameter missing";
                        return (false);
                    }
                    if (!subnet_element->get("subnet")) {
                        ADD_FAILURE() << "Mandatory 'subnet' parameter missing";
                        return (false);
                    }
                    // Both subnet prefix and subnet identifier should match.
                    if ((subnet_element->get("subnet")->stringValue() == subnet)) {
                        found = true;
                        break;
                    }
                }
            }
        }

        return (found);
    }

    /// @brief Checks returned arguments in a response.
    ///
    /// This is a very generic method that checks if the response has exactly the specified
    /// arguments. This can be used to verify any responses as long as we know the exact
    /// expected arguments.
    /// @param response server's response to be checked.
    /// @param expected string version of expected response
    void checkArguments(const isc::data::ConstElementPtr& response, const std::string& expected) {
        ASSERT_TRUE(response);
        isc::data::ConstElementPtr args = response->get("arguments");
        ASSERT_TRUE(args);

        EXPECT_EQ(expected, args->str());
    }

    /// List of libraries to be/being loaded (usually just one)
    isc::hooks::HookLibsCollection libraries_;
};

} // end of anonymous namespace
