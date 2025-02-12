// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the flexible identifier hook library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <host_cmds.h>
#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/testutils/memory_host_data_source.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::host_cmds;

namespace {

/// @brief Test fixture class for testing host_cmds command handlers.
class HostCmdsTest : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// Clears server configuration before the test.
    HostCmdsTest() {
        CfgMgr::instance().clear();
        CfgMgr::instance().setFamily(AF_INET);
    }

    /// @brief Destructor
    ///
    /// Clears server configuration after the test.
    virtual ~HostCmdsTest() {
        HostMgr::create();
        HostDataSourceFactory::deregisterFactory("mem");
        CfgMgr::instance().clear();
    }

    /// @brief Initializes hosts data source (and inserts v4 or v6 host)
    ///
    /// @param insert_v4 should IPv4 host be inserted into the host source?
    /// @param insert_v6 should IPv6 host be inserted into the host source?
    /// @param operation_target should the host be inserted into the memory
    /// or/and newly created (database) host source?
    /// @param insert_multiple_ips should multiple hosts with the same IP address be inserted?
    MemHostDataSourcePtr setHostsDataSource(
        bool insert_v4,
        bool insert_v6,
        HostMgrOperationTarget operation_target = HostMgrOperationTarget::ALTERNATE_SOURCES,
        bool insert_multiple_ips = false) {
        HostMgr::create();
        HostDataSourceFactory::registerFactory("mem", memFactory);
        HostMgr::addBackend("type=mem");

        if (insert_v4){
            HostMgr::instance().add(createHost4(), operation_target);
            if (insert_multiple_ips) {
                HostMgr::instance().add(createHost4("01:02:03:04:05:07"), operation_target);
                HostMgr::instance().add(createHost4("01:02:03:04:05:08", 5), operation_target);
            }
        }

        if (insert_v6) {
            HostMgr::instance().add(createHost6(), operation_target);
            if (insert_multiple_ips) {
                HostMgr::instance().add(createHost6("01:02:03:04:05:07"), operation_target);
                HostMgr::instance().add(createHost6("01:02:03:04:05:08", 7), operation_target);
            }
        }

        HostDataSourcePtr hds = HostMgr::instance().getHostDataSource();

        return (boost::dynamic_pointer_cast<MemHostDataSource>(hds));
    }

    /// @brief Creates a sample IPv4 host with given HW address and Subnet-id.
    ///
    /// @param hw_addr HW address of created host, "01:02:03:04:05:06" by default
    /// @param subnet_id subnet ID of created host, 4 by default
    /// @return pointer to the created host object
    HostPtr createHost4(const std::string& hw_addr = "01:02:03:04:05:06", int subnet_id = 4) {
        HostPtr h(new Host(hw_addr, "hw-address",
                           SubnetID(subnet_id), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.100"),
                           "somehost.example.org",
                           std::string(), std::string(),
                           IOAddress("192.0.0.2"),
                           "server-hostname.example.org",
                           "bootfile.efi"));
        return (h);
    }

    /// @brief Creates a sample IPv6 host with given HW address and Subnet-id.
    ///
    /// @param hw_addr HW address of created host, "01:02:03:04:05:06" by default
    /// @param subnet_id subnet ID of created host, 6 by default
    /// @return pointer to the created host object
    HostPtr createHost6(const std::string& hw_addr = "01:02:03:04:05:06", int subnet_id = 6) {
        HostPtr host(new Host(hw_addr, "hw-address",
                              SubnetID(SUBNET_ID_UNUSED), SubnetID(subnet_id),
                              IOAddress("0.0.0.0"),
                              "somehost.example.org"));
        // Add 2 reservations: 1 for NA, 1 for PD.
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8::cafe:babe")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                       IOAddress("2001:db8:dead:beef::"), 64));
        return (host);
    };

    /// @brief Checks if specified response contains IPv4 host
    void checkResponseHost4(ConstElementPtr rsp) {
        ASSERT_TRUE(rsp);
        ConstElementPtr host = rsp->get("arguments");
        ASSERT_TRUE(host);
        EXPECT_TRUE(host->get("boot-file-name"));
        EXPECT_TRUE(host->get("ip-address"));
        EXPECT_TRUE(host->get("hw-address"));
        EXPECT_TRUE(host->get("hostname"));
        EXPECT_TRUE(host->get("next-server"));
        EXPECT_TRUE(host->get("option-data"));
        EXPECT_TRUE(host->get("server-hostname"));

        // Check that there are no v6 specific fields
        EXPECT_FALSE(host->get("ip-addresses"));
        EXPECT_FALSE(host->get("prefixes"));

        // Check subnet ID.
        ASSERT_TRUE(host->get("subnet-id"));
        EXPECT_EQ("4", host->get("subnet-id")->str());
    }

    /// @brief Checks if specified response contains IPv6 host
    void checkResponseHost6(ConstElementPtr rsp) {
        ASSERT_TRUE(rsp);
        ConstElementPtr host = rsp->get("arguments");
        ASSERT_TRUE(host);

        // Check that there are expected fields
        EXPECT_TRUE(host->get("ip-addresses"));
        EXPECT_TRUE(host->get("prefixes"));
        EXPECT_TRUE(host->get("hw-address"));
        EXPECT_TRUE(host->get("hostname"));
        EXPECT_TRUE(host->get("option-data"));

        // Check that there are no v4 specific fields.
        EXPECT_FALSE(host->get("boot-file-name"));
        EXPECT_FALSE(host->get("ip-address"));
        EXPECT_FALSE(host->get("server-hostname"));
        EXPECT_FALSE(host->get("next-server"));

        // Check subnet ID.
        ASSERT_TRUE(host->get("subnet-id"));
        EXPECT_EQ("6", host->get("subnet-id")->str());
    }

    /// @brief Compare a specified response with an IPv4 host
    void compResponseHost4(ConstElementPtr rsp, ConstHostPtr host) {
        ASSERT_TRUE(rsp);
        ASSERT_TRUE(host);
        ElementPtr elem = host->toElement4();
        SubnetID subnet_id = host->getIPv4SubnetID();
        elem->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id)));
        EXPECT_TRUE(isEquivalent(rsp, elem));
    }

    /// @brief Compare a specified response with an IPv6 host
    void compResponseHost6(ConstElementPtr rsp, ConstHostPtr host) {
        ASSERT_TRUE(rsp);
        ASSERT_TRUE(host);
        ElementPtr elem = host->toElement6();
        SubnetID subnet_id = host->getIPv6SubnetID();
        elem->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id)));
        EXPECT_TRUE(isEquivalent(rsp, elem));
    }

    /// @brief Tests specified command and verifies response.
    ///
    /// This method processes supplied command via @c HostCmds class. It
    /// then checks if the expected response was returned.
    ///
    /// @param cmd_txt JSON text command to be sent (must be valid JSON)
    /// @param exp_result 0 - success, 1 - error, 2 - ...
    /// @param exp_txt expected text response (optional)
    /// @return full response returned by the command execution.
    ConstElementPtr testCommand(string cmd_txt, int exp_result, string exp_txt) {
        ConstElementPtr cmd;
        EXPECT_NO_THROW(cmd = Element::fromJSON(cmd_txt));
        if (!cmd) {
            ADD_FAILURE() << cmd_txt << " is not a valid JSON, test broken";
            return (ConstElementPtr());
        }
        return (testCommand(cmd, exp_result, exp_txt));
    }

    /// @brief Tests specified command and verifies response.
    ///
    /// This method processes supplied command via @c HostCmds class. It
    /// then checks if the expected response was returned.
    ///
    /// @param cmd JSON command to be sent
    /// @param exp_result 0 - success, 1 - error, 2 - ...
    /// @param exp_txt expected text response (optional)
    /// @return full response returned by the command execution.
    ConstElementPtr testCommand(ConstElementPtr cmd,
                                int exp_result, string exp_txt) {
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

        // Capture hook result.
        HostCmds host_cmds;

        // Run the command handler appropriate for the given command name.
        if (command_name == "reservation-add") {
            static_cast<void>(host_cmds.reservationAddHandler(*callout_handle));

        } else if (command_name == "reservation-get") {
            static_cast<void>(host_cmds.reservationGetHandler(*callout_handle));

        } else if (command_name == "reservation-del") {
            static_cast<void>(host_cmds.reservationDelHandler(*callout_handle));

        } else if (command_name == "reservation-get-all") {
            static_cast<void>(host_cmds.reservationGetAllHandler(*callout_handle));

        } else if (command_name == "reservation-get-page") {
            static_cast<void>(host_cmds.reservationGetPageHandler(*callout_handle));

        } else if (command_name == "reservation-get-by-address") {
            static_cast<void>(host_cmds.reservationGetByAddressHandler(*callout_handle));

        } else if (command_name == "reservation-get-by-hostname") {
            static_cast<void>(host_cmds.reservationGetByHostnameHandler(*callout_handle));

        } else if (command_name == "reservation-get-by-id") {
            static_cast<void>(host_cmds.reservationGetByIdHandler(*callout_handle));

        } else if (command_name == "reservation-update") {
            static_cast<void>(host_cmds.reservationUpdateHandler(*callout_handle));

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
        checkAnswer(rsp, exp_result, exp_txt);

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
                     string exp_txt = "") {
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

protected:
    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp() {
        CfgMgr::instance().clear();
    }

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown() {
        CfgMgr::instance().clear();
    }
};

// Check that a simple, well formed reservation can be added.
TEST_F(HostCmdsTest, ReservationAdd) {
    // Vector of tuples containing the command request, expected number of the
    // host reservations in the memory data source and expected number of the
    // host reservations in the database data source.
    std::vector<boost::tuple<string, size_t, size_t>> test_cases{
        // Default operation target.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-address\": \"192.0.2.202\"\n"
            "        }\n"
            "    }\n"
            "}", 0, 1
        },
        // Unspecified operation target.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-address\": \"192.0.2.202\"\n"
            "        },\n"
            "        \"operation-target\":  \"default\"\n"
            "    }\n"
            "}", 0, 1
        },
        // Operation target is the memory host source.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-address\": \"192.0.2.202\"\n"
            "        },\n"
            "        \"operation-target\":  \"memory\"\n"
            "    }\n"
            "}", 1, 0
        },
        // Operation target is the database host source.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-address\": \"192.0.2.202\"\n"
            "        },\n"
            "        \"operation-target\":  \"database\"\n"
            "    }\n"
            "}", 0, 1
        },
        // Operation target is set to the all host sources.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-address\": \"192.0.2.202\"\n"
            "        },\n"
            "        \"operation-target\":  \"all\"\n"
            "    }\n"
            "}", 1, 1
        }
    };

    for (auto const& test_case : test_cases) {
        // Add a valid subnet with subnet ID of 1.
        CfgMgr::instance().clear();
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
        CfgMgr::instance().commit();

        // First, let's create a dummy host data source (don't insert any hosts)
        MemHostDataSourcePtr hds = setHostsDataSource(false, false);
        ASSERT_TRUE(hds);

        // Check that there are no hosts
        EXPECT_EQ(0, hds->size());
        EXPECT_EQ(0, CfgMgr::instance().getCurrentCfg()->getCfgHosts()->getAll4(SubnetID(1)).size());

        string exp_rsp = "Host added.";
        testCommand(boost::get<0>(test_case), CONTROL_RESULT_SUCCESS, exp_rsp);

        // Now check the memory host source.
        EXPECT_EQ(boost::get<1>(test_case), CfgMgr::instance().getCurrentCfg()->getCfgHosts()->getAll4(SubnetID(1)).size());
        // Now check the database source.
        EXPECT_EQ(boost::get<2>(test_case), hds->size());
    }
}

// Check that reservation without IPv4 address can be added.
TEST_F(HostCmdsTest, reservationAddNoAddress) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // The inserted reservation lacks IPv4 address. It should be added
    // correctly.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Host added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host was really there.
    EXPECT_EQ(1, hds->size());
}

// Check that adding new host works only when actual data source is
// specified.
TEST_F(HostCmdsTest, reservationAddNoHostDataSource) {
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Host database not available, cannot add host.";

    // Check that the command was rejected. The reason for rejecting is that
    // there is host data source, so there's no way to store the host.
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that a reservation with an illegal host address cannot be added.
TEST_F(HostCmdsTest, reservationAddBadHwAddr) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \n"
        "\"00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14\",\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "too long client identifier type hw-address ";
    exp_rsp += "length 21 (:0:0)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that a simple, well formed IPv6 reservation can be added.
TEST_F(HostCmdsTest, reservationAdd6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Vector of tuples containing the command request, expected number of the
    // host reservations in the memory data source and expected number of the
    // host reservations in the database source.
    // The command adds reservations for two IPv6 addresses and one delegated prefix.
    // The delegated prefix does not have to match the subnet prefix.
    std::vector<boost::tuple<string, size_t, size_t>> test_cases{
        // Default operation target.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ],\n"
            "            \"prefixes\": [ \"3001:1::/64\" ]\n"
            "        }\n"
            "    }\n"
            "}", 0, 1
        },
        // Unspecified operation target.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ],\n"
            "            \"prefixes\": [ \"3001:1::/64\" ]"
            "        },\n"
            "        \"operation-target\":  \"default\"\n"
            "    }\n"
            "}", 0, 1
        },
        // Operation target is the memory host source.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ],\n"
            "            \"prefixes\": [ \"3001:1::/64\" ]"
            "        },\n"
            "        \"operation-target\":  \"memory\"\n"
            "    }\n"
            "}", 1, 0
        },
        // Operation target is the database host source.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ],\n"
            "            \"prefixes\": [ \"3001:1::/64\" ]"
            "        },\n"
            "        \"operation-target\":  \"database\"\n"
            "    }\n"
            "}", 0, 1
        },
        // Operation target is set to the all host sources.
        {
            "{\n"
            "    \"command\": \"reservation-add\",\n"
            "    \"arguments\": {"
            "        \"reservation\": {"
            "            \"subnet-id\": 1,\n"
            "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
            "            \"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ],\n"
            "            \"prefixes\": [ \"3001:1::/64\" ]"
            "        },\n"
            "        \"operation-target\":  \"all\"\n"
            "    }\n"
            "}", 1, 1
        }
    };

    for (auto const& test_case : test_cases) {
        // Add a valid subnet with subnet ID of 1.
        CfgMgr::instance().clear();
        Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
        CfgMgr::instance().commit();

        // First, let's create a dummy host data source (don't insert any hosts)
        MemHostDataSourcePtr hds = setHostsDataSource(false, false);
        ASSERT_TRUE(hds);

        // Check that there are no hosts
        EXPECT_EQ(0, hds->size());

        string exp_rsp = "Host added.";
        testCommand(boost::get<0>(test_case), CONTROL_RESULT_SUCCESS, exp_rsp);

        // Now check the memory host source.
        EXPECT_EQ(boost::get<1>(test_case), CfgMgr::instance().getCurrentCfg()->getCfgHosts()->getAll6(SubnetID(1)).size());
        // Now check the database source.
        EXPECT_EQ(boost::get<2>(test_case), hds->size());
    }
}

// Check that the reservation without any IPv6 address and prefix can be added.
TEST_F(HostCmdsTest, reservationAdd6NoAddresses) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // The inserted reservation lacks IPv6 addresses and prefixes. It
    // should be added correctly.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Host added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host was really there.
    EXPECT_EQ(1, hds->size());
}

// Checks that the reservation without any subnet and IPv4 address is added
// as a global (subnet-id 0) one.
TEST_F(HostCmdsTest, reservationAddNoSubnetNoAddress4) {
    CfgMgr::instance().setFamily(AF_INET);

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // The inserted reservation lacks subnet id and IPv4 address.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Host added.";
    exp_rsp += " subnet-id not specified, assumed global (subnet-id 0).";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host was really there.
    EXPECT_EQ(1, hds->size());

    // Verify the host is global.
    uint8_t hw_addr[] = { 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
    ConstHostPtr host = hds->get4(0, Host::IdentifierType::IDENT_HWADDR,
                                  &hw_addr[0], sizeof(hw_addr));
    ASSERT_TRUE(host);
}

// Checks that the reservation without any subnet and with a not
// localized address can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetBadAddress4) {
    CfgMgr::instance().setFamily(AF_INET);

    // The inserted reservation lacks subnet id, the IPv4 address belongs
    // to no subnet.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-address\": \"192.0.2.202\",\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " The address '192.0.2.202' belongs to no configured subnet.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress4) {
    CfgMgr::instance().setFamily(AF_INET);

    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv4 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-address\": \"192.0.2.202\",\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " The address '192.0.2.202' belongs to subnet";
    exp_rsp += " '192.0.2.0/24' id 1.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address in two subnets can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress4Others) {
    CfgMgr::instance().setFamily(AF_INET);

    // Add a guarded subnet with subnet ID of 1 and a second not guarded one.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.1"), 24, 30, 40, 50, 1));
    subnet->allowClientClass("foobar");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv4 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-address\": \"192.0.2.202\",\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " The address '192.0.2.202' belongs to subnet";
    exp_rsp += " '192.0.2.0/24' id 2 and others.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address in a guarded subnet can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress4Guarded) {
    CfgMgr::instance().setFamily(AF_INET);

    // Add a guarded subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    subnet->allowClientClass("foobar");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv4 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-address\": \"192.0.2.202\",\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " The address '192.0.2.202' belongs to guarded subnet";
    exp_rsp += " '192.0.2.0/24' id 1.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address in two guarded subnets can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress4GuardedOthers) {
    CfgMgr::instance().setFamily(AF_INET);

    // Add a guarded subnet with subnet ID of 1 and a second not guarded one.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    subnet->allowClientClass("foo");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.1"), 24, 30, 40, 50, 2));
    subnet2->allowClientClass("bar");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv4 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-address\": \"192.0.2.202\",\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " The address '192.0.2.202' belongs to guarded subnet";
    exp_rsp += " '192.0.2.0/24' id 1 and others.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and IPv6 address/prefixes
// is added as a global (subnet-id 0) one.
TEST_F(HostCmdsTest, reservationAddNoSubnetNoAddress6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // The inserted reservation lacks subnet id and IPv6 address/prefixes.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Host added.";
    exp_rsp += " subnet-id not specified, assumed global (subnet-id 0).";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host was really there.
    EXPECT_EQ(1, hds->size());

    // Verify the host is global.
    uint8_t hw_addr[] = { 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
    ConstHostPtr host = hds->get6(0, Host::IdentifierType::IDENT_HWADDR,
                                  &hw_addr[0], sizeof(hw_addr));
    ASSERT_TRUE(host);
}

// Checks that the reservation without any subnet and address can't be added,
// and prefixes (which are not localized) can't help.
TEST_F(HostCmdsTest, reservationAddNoSubnetPrefix6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // The inserted reservation lacks subnet id and IPv6 address/prefixes.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\",\n"
        "            \"prefixes\": [ \"3001:1::/64\" ]"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Prefixes are not attached to subnets so no hint is available.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a not
// localized address can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetBadAddress6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // The inserted reservation lacks subnet id, the IPv6 address belongs
    // to no subnet.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-addresses\": [ \"2001:db8:1::1\" ],\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Reserved IPv6 addresses do not belong to a common";
    exp_rsp += " configured subnet.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv6 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-addresses\": [ \"2001:db8:1::1\" ],\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Reserved IPv6 addresses belong to subnet";
    exp_rsp += " '2001:db8:1::/64' id 1.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with two
// localized addresses in different subnets can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetBadAddress6NoCommon) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add valid subnet with subnet ID of 1 and 2.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"),
                                   64, 30, 40, 50, 60, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, IPv6 addresses belong
    // to different subnets.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-addresses\": [ \"2001:db8:1::1\",\n"
        "                                \"2001:db8:2::2\" ],\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Reserved IPv6 addresses do not belong to a common";
    exp_rsp += " configured subnet.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with two
// localized addresses in the same subnet can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress6Common) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv6 addresses belong to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-addresses\": [ \"2001:db8:1::1\",\n"
        "                                \"2001:db8:1::2\" ],\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Reserved IPv6 addresses belong to subnet";
    exp_rsp += " '2001:db8:1::/64' id 1.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address in two subnets can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress6Others) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a guarded subnet with subnet ID of 1 and a second not guarded one.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::1"),
                                  64, 30, 40, 50, 60, 1));
    subnet->allowClientClass("foobar");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:1::"),
                                   64, 30, 40, 50, 60, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv6 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-addresses\": [ \"2001:db8:1::1\" ],\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Reserved IPv6 addresses belong to subnet";
    exp_rsp += " '2001:db8:1::/64' id 2 and others.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address in a guarded subnet can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress6Guarded) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a guarded subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    subnet->allowClientClass("foobar");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv6 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-addresses\": [ \"2001:db8:1::1\" ],\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Reserved IPv6 addresses belong to guarded subnet";
    exp_rsp += " '2001:db8:1::/64' id 1.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that the reservation without any subnet and with a
// localized address in two guarded subnets can't be added.
TEST_F(HostCmdsTest, reservationAddNoSubnetAddress6GuardedOthers) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a guarded subnet with subnet ID of 1 and a second not guarded one.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    subnet->allowClientClass("foo");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:1::1"),
                                   64, 30, 40, 50, 60, 2));
    subnet2->allowClientClass("bar");
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().commit();

    // The inserted reservation lacks subnet id, the IPv6 address belongs to
    // subnet 1.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"ip-addresses\": [ \"2001:db8:1::1\" ],\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"hostname\": \"myhost\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    exp_rsp += " Reserved IPv6 addresses belong to guarded subnet";
    exp_rsp += " '2001:db8:1::/64' id 1 and others.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that a prefix exclude IPv6 reservation can be added.
TEST_F(HostCmdsTest, reservationAdd6PrefixExclude) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Add a reservation with a Prefix Exclude option.
    string txt =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"prefixes\": [ \"3000::/32\", \"2001:db8::/48\" ],\n"
        "            \"excluded-prefixes\": [ \"\", \"2001:db8:0:1::/64\" ]\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Host added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host was really there.
    EXPECT_EQ(1, hds->size());

    // Verify there is a host with the Prefix Exclude option.
    uint8_t hw_addr[] = { 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
    ConstHostPtr host = hds->get6(1, Host::IdentifierType::IDENT_HWADDR,
                                  &hw_addr[0], sizeof(hw_addr));
    ASSERT_TRUE(host);
    auto const& resvs = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    Option6PDExcludePtr opt;
    for (auto resv = resvs.first; resv != resvs.second; ++resv) {
        if (resv->second.getPDExclude()) {
            ASSERT_FALSE(opt) << "got twice the option";
            opt = resv->second.getPDExclude();
        }
    }
    EXPECT_TRUE(opt) << "got no option";
}

// Check that an invalid prefix exclude IPv6 reservation is rejected.
TEST_F(HostCmdsTest, reservationAdd6PrefixExcludeInvalid) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a reservation with a bad (not matching) Prefix Exclude option
    string bad1 =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"prefixes\": [ \"3000::/32\", \"2001:db8::/48\" ],\n"
        "            \"excluded-prefixes\": [ \"\", \"2001:db9:0:1::/64\" ]\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "excluded prefix 2001:db9:0:1::/64 must have ";
    exp_rsp += "the same common prefix part of 48 as the delegated prefix ";
    exp_rsp += "2001:db8::/48 (<string>:6:40)";

    // This should be rejected as prefixes do not match.
    testCommand(bad1, CONTROL_RESULT_ERROR, exp_rsp);

    string bad2 =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"prefixes\": [ \"3000::/32\", \"2001:db8::/48\" ],\n"
        "            \"excluded-prefixes\": [ \"\", \"2001:db8::/48\" ]\n"
        "        }\n"
        "    }\n"
        "}";
    exp_rsp = "length of the excluded prefix 2001:db8::/48 must be ";
    exp_rsp += "greater than the length of the delegated prefix ";
    exp_rsp += "2001:db8::/48 (<string>:6:40)";

    // This should be rejected as excluded prefix is too short.
    testCommand(bad2, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get can handle a situation when the query is
// broken (no parameters at all).
TEST_F(HostCmdsTest, reservationGetNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'subnet-id' (<string>:3:19)";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get can handle a situation when the query is
// broken (just subnet-id).
TEST_F(HostCmdsTest, reservationGetNoAddress) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";

    string rsp = "No 'ip-address' provided and 'identifier-type' is either "
                 "missing or not a string.";

    // Providing just subnet-id is not enough, the code needs either
    // (subnet-id, addr) or (subnet-id, identifier-type, identifier)
    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get can handle a situation when the query is
// broken (subnet-id, identifier-type) and identifier itself missing.
TEST_F(HostCmdsTest, reservationGetNoIdentifier) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\""
        "    }\n"
        "}";
    string rsp = "No 'ip-address' provided and 'identifier' is either missing "
                 "or not a string.";

    // It's better (one parameter missing), but we still not there yet.
    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get can handle a situation when the query is
// broken (subnet-id, identifier) and identifier-type is missing.
TEST_F(HostCmdsTest, reservationGetNoIdentifierType) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"identifier\": \"00:11:22:33:44:55\""
        "    }\n"
        "}";
    string rsp = "No 'ip-address' provided and 'identifier-type' is either missing "
                 "or not a string.";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get can handle a situation when the query is
// broken (operation-target is invalid).
TEST_F(HostCmdsTest, reservationGetInvalidOperationTarget) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"operation-target\":  \"invalid\"\n"
        "    }\n"
        "}";
    string rsp = "The 'operation-target' value (invalid) is not within "
                 "expected set: (memory, database, all, default)";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetOutOfRangeSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get can handle a situation when the query is
// brokern (address but no subnet-id).
TEST_F(HostCmdsTest, reservationGetAddrNotSubnet) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    string rsp = "missing parameter 'subnet-id', use ";
    rsp += "'reservation-get-by-address' with 'ip-address' set to ";
    rsp += "\"192.0.2.202\" to get the list of reservations with this address";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get can handle a situation when the query is
// brokern (identifier but no subnet-id).
TEST_F(HostCmdsTest, reservationGetIdNotSubnet) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"00:01:02:03:04:05\"\n"
        "    }\n"
        "}";
    string rsp = "missing parameter 'subnet-id', use ";
    rsp += "'reservation-get-by-id' with 'identifier-type' set to ";
    rsp += "\"hw-address\" and 'identifier' to \"00:01:02:03:04:05\" ";
    rsp += "to get the list of reservations with this identifier";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationGetAddr4NotFound) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not found.";

    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-get(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is returned.
TEST_F(HostCmdsTest, reservationGetAddr4) {

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(true, false)); // insert v4 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4,\n"
        "        \"ip-address\": \"192.0.2.100\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host found.";

    // Should have found it.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr host = rsp->get("arguments");
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->get("boot-file-name"));
    EXPECT_TRUE(host->get("ip-address"));
    EXPECT_TRUE(host->get("hw-address"));
    EXPECT_TRUE(host->get("hostname"));
    EXPECT_TRUE(host->get("next-server"));
    EXPECT_TRUE(host->get("option-data"));
    EXPECT_TRUE(host->get("server-hostname"));

    // Check that there are no v6 specific fields
    EXPECT_FALSE(host->get("ip-addresses"));
    EXPECT_FALSE(host->get("prefixes"));

    // Check subnet ID.
    ASSERT_TRUE(host->get("subnet-id"));
    EXPECT_EQ("4", host->get("subnet-id")->str());
}

// Host derived class with setIdentifierType visible.
class TestHost : public Host {
public:
    TestHost(const uint8_t* identifier, const size_t identifier_len,
             const IdentifierType& identifier_type,
             const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
             const asiolink::IOAddress& ipv4_reservation) :
        Host(identifier, identifier_len, identifier_type,
             ipv4_subnet_id, ipv6_subnet_id, ipv4_reservation) {
    }
    virtual ~TestHost() {
    }
    using Host::setIdentifierType;
};

// Checks that reservation-get handles illegal hardware address (#2557).
TEST_F(HostCmdsTest, reservationGetBadHwAddr) {

    // First, let's create a dummy host data source (don't insert any hosts).
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts.
    EXPECT_EQ(0, hds->size());

    uint8_t duid[21];
    for (uint8_t i = 0; i < 21; ++i) {
        duid[i] = i;
    }

    boost::shared_ptr<TestHost> host;
    EXPECT_NO_THROW(host.reset(new TestHost(duid, sizeof(duid),
                                            Host::IDENT_DUID,
                                            SubnetID(4),
                                            SubnetID(SUBNET_ID_UNUSED),
                                            IOAddress("192.0.2.100"))));
    ASSERT_TRUE(host);
    EXPECT_NO_THROW(host->setIdentifierType(Host::IDENT_HWADDR));
    ASSERT_THROW(host->getHWAddress(), BadValue);
    HostMgr::instance().add(host);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4,\n"
        "        \"ip-address\": \"192.0.2.100\"\n"
        "    }\n"
        "}";
    string exp_rsp = "address vector size exceeds MAX_HWADDR_LEN";

    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationGetAddr6NotFound) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"2001:db8::1\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not found.";

    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-get(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationGetHostNotFound) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"00:01:02:03:04:05\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not found.";

    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-get(subnet-id, identifier-type, identifier,
// operation-target) can handle a situation when the query returns a host.
TEST_F(HostCmdsTest, reservationGetHwAddr4) {
    CfgMgr::instance().setFamily(AF_INET);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(true, false)); // insert v4 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4,\n"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host found.";

    // Note the status expected is success. The host should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr host = rsp->get("arguments");
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->get("boot-file-name"));
    EXPECT_TRUE(host->get("ip-address"));
    EXPECT_TRUE(host->get("hw-address"));
    EXPECT_TRUE(host->get("hostname"));
    EXPECT_TRUE(host->get("next-server"));
    EXPECT_TRUE(host->get("option-data"));
    EXPECT_TRUE(host->get("server-hostname"));

    // Check that there are no v6 specific fields
    EXPECT_FALSE(host->get("ip-addresses"));
    EXPECT_FALSE(host->get("prefixes"));

    // Check subnet ID.
    ASSERT_TRUE(host->get("subnet-id"));
    EXPECT_EQ("4", host->get("subnet-id")->str());
}

// Checks that reservation-get(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is returned.
TEST_F(HostCmdsTest, reservationGetAddr6) {

    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(false, true)); // insert v6 host
    HostMgr::instance().add(createHost6());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"ip-address\": \"2001:db8::cafe:babe\""
        "    }\n"
        "}";
    string exp_rsp = "Host found.";

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    checkResponseHost6(rsp);
}

// Checks that reservation-get(subnet-id, identifier-type, identifier) can handle
// a situation when the query returns a host.
TEST_F(HostCmdsTest, reservationGetHwAddr6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(false, false));
    HostMgr::instance().add(createHost6());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host found.";

    // Note the status expected is success. The host should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host parameters were indeed returned.
    checkResponseHost6(rsp);
}

// reservation-del

// Checks that reservation-del can handle a situation when the query is
// broken (no parameters at all).
TEST_F(HostCmdsTest, reservationDelNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'subnet-id' (<string>:3:19)";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-del can handle a situation when the query is
// broken (just subnet-id).
TEST_F(HostCmdsTest, reservationDelNoAddress) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";

    string rsp = "No 'ip-address' provided and 'identifier-type' is either "
                 "missing or not a string.";

    // Providing just subnet-id is not enough, the code needs either
    // (subnet-id, addr) or (subnet-id, identifier-type, identifier)
    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-del can handle a situation when the query is
// broken (subnet-id, identifier-type specified, identifier missing).
TEST_F(HostCmdsTest, reservationDelNoIdentifier) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\""
        "    }\n"
        "}";
    string rsp = "No 'ip-address' provided and 'identifier' is either missing "
                 "or not a string.";

    // It's better (one parameter missing), but we still not there yet.
    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-del can handle a situation when the query is
// broken (subnet-id, identifier specified, identifier-type missing).
TEST_F(HostCmdsTest, reservationDelNoIdentifierType) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"identifier\": \"00:11:22:33:44:55\""
        "    }\n"
        "}";
    string rsp = "No 'ip-address' provided and 'identifier-type' is either missing "
                 "or not a string.";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-del can handle a situation when the query is
// broken (operation-target is invalid).
TEST_F(HostCmdsTest, reservationDelInvalidOperationTarget) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"operation-target\":  \"invalid\"\n"
        "    }\n"
        "}";
    string rsp = "The 'operation-target' value (invalid) is not within "
                 "expected set: (memory, database, all, default)";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-del detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationDelOutOfRangeSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range: "
                "(0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-del can handle a situation when the query is
// brokern (address but no subnet-id).
TEST_F(HostCmdsTest, reservationDelAddrNotSubnet) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    string rsp = "missing parameter 'subnet-id', use ";
    rsp += "'reservation-get-by-address' with 'ip-address' set to ";
    rsp += "\"192.0.2.202\" to get the list of reservations with this address";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-del can handle a situation when the query is
// brokern (identifier but no subnet-id).
TEST_F(HostCmdsTest, reservationDelIdNotSubnet) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"00:01:02:03:04:05\"\n"
        "    }\n"
        "}";
    string rsp = "missing parameter 'subnet-id', use ";
    rsp += "'reservation-get-by-id' with 'identifier-type' set to ";
    rsp += "\"hw-address\" and 'identifier' to \"00:01:02:03:04:05\" ";
    rsp += "to get the list of reservations with this identifier";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that properly formed reservation-del(subnet-id, addr) will not work if
// there is no hosts-database configured and the operation target is default.
TEST_F(HostCmdsTest, reservationDelNoHostsDatabaseDefaultSource) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Unable to delete a host because there is no "
                     "hosts-database configured.";

    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that properly formed reservation-del(subnet-id, addr) will work if
// there is no hosts-database configured but the operation target is memory
// source.
TEST_F(HostCmdsTest, reservationDelNoHostsDatabaseMemorySource) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"operation-target\":  \"memory\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not deleted (not found).";

    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-del will work with an illegal hardware address.
// No host object is created vs reservation-add so it simply always fails
// to find something...
TEST_F(HostCmdsTest, reservationDelBadHwAddr) {

    ASSERT_TRUE(setHostsDataSource(true, false)); // insert v4 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \n"
        "\"00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not deleted (not found).";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationDelByAddr4NotFound) {

    ASSERT_TRUE(setHostsDataSource(false, false));

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not deleted (not found).";

    // Delete that doesn't find should return a status of empty
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is deleted.
TEST_F(HostCmdsTest, reservationDelByAddr4) {

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(true, false)); // insert v4 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4,\n"
        "        \"ip-address\": \"192.0.2.100\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Should succeed, host should get deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr4, operation-target) can handle
// a situation when the query is correctly formed and the host from CfgHosts
// is deleted.
TEST_F(HostCmdsTest, reservationDelByAddr4MemorySource) {
    // First, let's create a host reservation in the memory source.
    const uint8_t hwaddr_data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    HWAddrPtr hwaddr_ = HWAddrPtr(new HWAddr(hwaddr_data, sizeof(hwaddr_data), HTYPE_ETHER));
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, SubnetID(4), SUBNET_ID_UNUSED,
                          asiolink::IOAddress("10.1.2.105")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgHosts()->get4(
        SubnetID(4), asiolink::IOAddress("10.1.2.105")));

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4,\n"
        "        \"ip-address\": \"10.1.2.105\",\n"
        "        \"operation-target\":  \"memory\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Should succeed, host should get deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationDelByAddr6NotFound) {

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(false, false)); // Don't insert any hosts.

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"2001:db8::1\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not deleted (not found).";

    // Delete that doesn't find should return a status of empty
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationDelByIdentifierNotFound) {

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(false, false)); // Don't insert any hosts.

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"00:01:02:03:04:05\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host not deleted (not found).";

    // Delete that doesn't find, should return a result of empty.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-del(subnet-id, identifier-type, identifier) can handle
// a situation when the v4 host is deleted from the default data source.
TEST_F(HostCmdsTest, reservationDelByIdentifier4) {
    CfgMgr::instance().setFamily(AF_INET);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(true, false)); // insert v4 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4,\n"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Note the status expected is success. The host should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, identifier-type, identifier) can handle
// a situation when the v4 host is deleted from the memory data source.
TEST_F(HostCmdsTest, reservationDelByIdentifier4MemorySource) {
    CfgMgr::instance().setFamily(AF_INET);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(true, false, HostMgrOperationTarget::PRIMARY_SOURCE)); // insert v4 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:02:03:04:05:06\",\n"
        "        \"operation-target\":  \"memory\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Note the status expected is success. The host should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is deleted.
TEST_F(HostCmdsTest, reservationDelByAddr6) {

    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(false, true)); // insert v6 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"ip-address\": \"2001:db8::cafe:babe\""
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr4, operation-target) can handle a
// situation when the query is correctly formed and the host from CfgHosts
// is deleted.
TEST_F(HostCmdsTest, reservationDelByAddr6MemorySource) {
    // First, let's create a host reservation in the memory source.
    const uint8_t hwaddr_data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    HWAddrPtr hwaddr_ = HWAddrPtr(new HWAddr(hwaddr_data, sizeof(hwaddr_data), HTYPE_ETHER));
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, SUBNET_ID_UNUSED, SubnetID(6),
                          IOAddress::IPV4_ZERO_ADDRESS()));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, asiolink::IOAddress("2001:db8::cafe:babe"), 128));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgHosts()->get6(
        SubnetID(6), asiolink::IOAddress("2001:db8::cafe:babe")));

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"ip-address\": \"2001:db8::cafe:babe\",\n"
        "        \"operation-target\":  \"memory\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, identifier-type, identifier) can handle
// a situation when the v6 host is actually deleted.
TEST_F(HostCmdsTest, reservationDelByIdentifier6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(false, true)); // insert v6 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Note the status expected is success. The host should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, identifier-type, identifier) can handle
// a situation when the v6 host is actually deleted from the memory source.
TEST_F(HostCmdsTest, reservationDelByIdentifier6MemorySource) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    ASSERT_TRUE(setHostsDataSource(false, true, HostMgrOperationTarget::PRIMARY_SOURCE)); // insert v6 host

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:02:03:04:05:06\",\n"
        "        \"operation-target\":  \"memory\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host deleted.";

    // Note the status expected is success. The host should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-add detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationAddOutOfRangeSubnetID) {
    // Command to send.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": -1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR,
                "subnet-id: -1 is invalid, must be between"
                " 0 and 4294967294 (inclusive).");

    // Command to send.
    cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 4294967295,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR,
                "subnet-id: 4294967295 is invalid, must be between"
                " 0 and 4294967294 (inclusive).");
}

// Checks that the reservation is not added if the specified subnet identifier
// doesn't exist in the server's configuration.
TEST_F(HostCmdsTest, reservationAddNonMatchingSubnetID) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.64"), 26, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // Create in-memory hosts database to be used for the test.
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);
    ASSERT_EQ(0, hds->size());

    // Address for which the reservation is added is valid for the prefix
    // of the configured subnet, but the subnet id is not matching.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 100,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-address\": \"192.0.2.70\"\n"
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected because subnet id is not matching.
    testCommand(cmd, CONTROL_RESULT_ERROR, "IPv4 subnet with ID of '100' is not configured");

    // Make sure the host wasn't added.
    ASSERT_EQ(0, hds->size());
}

// Checks that the reservation is not added if the specified subnet identifier
// doesn't exist in the server's configuration.
TEST_F(HostCmdsTest, reservationAddNonMatchingSubnetID6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Create in-memory hosts database to be used for the test.
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);
    ASSERT_EQ(0, hds->size());

    // Address for which the reservation is added is valid for the prefix
    // of the configured subnet, but the subnet id is not matching.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 100,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-addresses\": [ \"2001:db8:1::1\" ]\n"
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected because subnet id is not matching.
    testCommand(cmd, CONTROL_RESULT_ERROR, "IPv6 subnet with ID of '100' is not configured");

    // Make sure the host wasn't added.
    ASSERT_EQ(0, hds->size());
}

// Checks that the reservation is not added if the specified IP address
// is not in range of the configured subnet prefix.
TEST_F(HostCmdsTest, reservationAddNonMatchingSubnetPrefix) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.64"), 26, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // Create in-memory hosts database to be used for the test.
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);
    ASSERT_EQ(0, hds->size());

    // Subnet id matches the configured subnet, but the reserved IP
    // address should be in range of the subnet prefix, so between
    // 192.0.2.65 and 192.0.2.126.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-address\": \"192.0.2.63\"\n"
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected, because reserved IP address is not
    // matching the subnet prefix.
    testCommand(cmd, CONTROL_RESULT_ERROR,
                "specified reservation '192.0.2.63' is not matching the "
                "IPv4 subnet prefix '192.0.2.64/26'");

    // Make sure the host wasn't added.
    ASSERT_EQ(0, hds->size());
}

// Checks that the reservation is not added if any of the specified IPv6
// addresses is not in range of the configured subnet prefix.
TEST_F(HostCmdsTest, reservationAddNonMatchingSubnetPrefix6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Create in-memory hosts database to be used for the test.
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);
    ASSERT_EQ(0, hds->size());

    // Subnet id matches the configured subnet, but all reserved IP
    // addresses should be in range of the subnet prefix.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 1,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:2::2\" ]\n"
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected, because reserved IP address is not
    // matching the subnet prefix.
    testCommand(cmd, CONTROL_RESULT_ERROR,
                "specified reservation '2001:db8:2::2' is not matching the "
                "IPv6 subnet prefix '2001:db8:1::/64'");

    // Make sure the host wasn't added.
    ASSERT_EQ(0, hds->size());
}

// Checks that reservation-get-all can handle a situation when the query is
// broken (no parameters at all).
TEST_F(HostCmdsTest, reservationGetAllNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'subnet-id' (<string>:3:19)";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Now try without arguments at all
    cmd = "{\n"
        "    \"command\": \"reservation-get-all\"\n"
        "}";
    exp_rsp = "Parameters missing or are not a map.";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get-all detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetAll4OutOfRangeSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-all detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetAll6OutOfRangeSubnetID) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-all detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetAll4NotConfiguredSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv4 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-all detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetAll6NotConfiguredSubnetID) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv6 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-all with some IPv4 hosts.
TEST_F(HostCmdsTest, getAll4) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    // Add another subnet.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 50, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv4 host(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    // Add host to the configuration.
    HostPtr host0(new Host("01:02:03:04:05:00", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.10"),
                           "host0.example.org"));
    CfgMgr::instance().getCurrentCfg()->getCfgHosts()->add(host0);

    HostPtr host1(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.1"),
                           "host1.example.org"));
    hds->add(host1);
    HostPtr host2(new Host("01:02:03:04:05:07", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.2"),
                           "host2.example.org"));
    hds->add(host2);
    HostPtr host3(new Host("01:02:03:04:05:08", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.3"),
                           "host3.example.org"));
    hds->add(host3);
    HostPtr host4(new Host("01:02:03:04:05:09", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.4"),
                           "host4.example.org"));
    hds->add(host4);

    // Add another host in another subnet.
    HostPtr host5(new Host("01:02:03:04:05:0a", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.3.5"),
                           "host5.example.org"));
    hds->add(host5);
    EXPECT_EQ(5, hds->size());

    // Retry command.
    exp_rsp = "5 IPv4 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(5, hosts->size());

    // Assume the order is kept.
    ElementPtr rsp0 = host0->toElement4();
    SubnetID subnet_id0 = host0->getIPv4SubnetID();
    rsp0->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id0)));
    EXPECT_TRUE(isEquivalent(hosts->get(0), rsp0));

    ElementPtr rsp1 = host1->toElement4();
    SubnetID subnet_id1 = host1->getIPv4SubnetID();
    rsp1->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id1)));
    EXPECT_TRUE(isEquivalent(hosts->get(1), rsp1));

    ElementPtr rsp2 = host2->toElement4();
    SubnetID subnet_id2 = host2->getIPv4SubnetID();
    rsp2->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id2)));
    EXPECT_TRUE(isEquivalent(hosts->get(2), rsp2));

    ElementPtr rsp3 = host3->toElement4();
    SubnetID subnet_id3 = host3->getIPv4SubnetID();
    rsp3->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id3)));
    EXPECT_TRUE(isEquivalent(hosts->get(3), rsp3));

    ElementPtr rsp4 = host4->toElement4();
    SubnetID subnet_id4 = host4->getIPv4SubnetID();
    rsp4->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id4)));
    EXPECT_TRUE(isEquivalent(hosts->get(4), rsp4));
}

// Checks that reservation-get-all handles illegal hardware address (#2557).
TEST_F(HostCmdsTest, getAll4BadHwAddr) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    // Add another subnet.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 50, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Add some hosts.
    HostPtr host1(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.1"),
                           "host1.example.org"));
    hds->add(host1);
    HostPtr host2(new Host("01:02:03:04:05:07", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.2"),
                           "host2.example.org"));
    hds->add(host2);
    HostPtr host3(new Host("01:02:03:04:05:08", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.3"),
                           "host3.example.org"));
    hds->add(host3);
    HostPtr host4(new Host("01:02:03:04:05:09", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.4"),
                           "host4.example.org"));
    hds->add(host4);

    // Add another host in another subnet.
    HostPtr host5(new Host("01:02:03:04:05:0a", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.3.5"),
                           "host5.example.org"));
    hds->add(host5);
    EXPECT_EQ(5, hds->size());

    // Add a host with illegal hardware address.
    uint8_t duid[21];
    for (uint8_t i = 0; i < 21; ++i) {
        duid[i] = i;
    }
    boost::shared_ptr<TestHost> bad;
    EXPECT_NO_THROW(bad.reset(new TestHost(duid, sizeof(duid),
                                           Host::IDENT_DUID,
                                           SubnetID(1),
                                           SubnetID(SUBNET_ID_UNUSED),
                                           IOAddress("192.0.2.66"))));
    ASSERT_TRUE(bad);
    EXPECT_NO_THROW(bad->setIdentifierType(Host::IDENT_HWADDR));
    ASSERT_THROW(bad->getHWAddress(), BadValue);
    hds->add(bad);
    EXPECT_EQ(6, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";

    string exp_rsp = "address vector size exceeds MAX_HWADDR_LEN";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get-all with some IPv6 hosts.
TEST_F(HostCmdsTest, getAll6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    // Add another subnet.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"),
                                   64, 30, 40, 50, 60, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv6 host(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    HostPtr host0(new Host("01:02:03:04:05:00", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "host0.example.org"));
    host0->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::")));
    CfgMgr::instance().getCurrentCfg()->getCfgHosts()->add(host0);

    HostPtr host1(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "host1.example.org"));
    host1->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::1")));
    hds->add(host1);
    HostPtr host2(new Host("01:02:03:04:05:07", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "host2.example.org"));
    host2->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::2")));
    hds->add(host2);
    HostPtr host3(new Host("01:02:03:04:05:08", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "host3.example.org"));
    host3->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::3")));
    hds->add(host3);
    HostPtr host4(new Host("01:02:03:04:05:09", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "host4.example.org"));
    host4->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::4")));
    hds->add(host4);

    // Add another host in another subnet.
    HostPtr host5(new Host("01:02:03:04:05:0a", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(2),
                           IOAddress("0.0.0.0"),
                           "host5.example.org"));
    host5->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:2::5")));
    hds->add(host5);
    EXPECT_EQ(5, hds->size());

    // Retry command.
    exp_rsp = "5 IPv6 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(5, hosts->size());

    // Assume the order is kept.
    ElementPtr rsp0 = host0->toElement6();
    SubnetID subnet_id0 = host0->getIPv6SubnetID();
    rsp0->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id0)));
    EXPECT_TRUE(isEquivalent(hosts->get(0), rsp0));

    ElementPtr rsp1 = host1->toElement6();
    SubnetID subnet_id1 = host1->getIPv6SubnetID();
    rsp1->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id1)));
    EXPECT_TRUE(isEquivalent(hosts->get(1), rsp1));

    ElementPtr rsp2 = host2->toElement6();
    SubnetID subnet_id2 = host2->getIPv6SubnetID();
    rsp2->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id2)));
    EXPECT_TRUE(isEquivalent(hosts->get(2), rsp2));

    ElementPtr rsp3 = host3->toElement6();
    SubnetID subnet_id3 = host3->getIPv6SubnetID();
    rsp3->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id3)));
    EXPECT_TRUE(isEquivalent(hosts->get(3), rsp3));

    ElementPtr rsp4 = host4->toElement6();
    SubnetID subnet_id4 = host4->getIPv6SubnetID();
    rsp4->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id4)));
    EXPECT_TRUE(isEquivalent(hosts->get(4), rsp4));
}

// Checks that reservation-get-page can handle a situation when the query is
// broken (no parameters at all).
TEST_F(HostCmdsTest, reservationGetPageNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'limit' (<string>:3:19)";

    // This should be rejected, because limit parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get-page detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetPage4OutOfRangeSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range: "
                "(0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-page detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetPage6OutOfRangeSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-page detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetPage4NotConfiguredSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv4 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-all detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetPage6NotConfiguredSubnetID) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv6 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-page with some IPv4 hosts in a subnet.
TEST_F(HostCmdsTest, getPage4Subnet) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd_txt =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv4 host(s) found.";
    testCommand(cmd_txt, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    static uint8_t hwaddr[] = {65, 66, 67, 68, 69, 69};
    IOAddress addr("192.0.2.0");
    for (unsigned i = 0; i < 25; ++i) {
        hwaddr[sizeof(hwaddr) - 1]++;
        vector<uint8_t> ident(hwaddr, hwaddr + sizeof(hwaddr));
        addr = IOAddress::increase(addr);
        HostPtr host(new Host(&ident[0], ident.size(),
                              Host::IDENT_HWADDR,
                              SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                              addr));
        hds->add(host);
    }
    EXPECT_EQ(25, hds->size());

    // Get all.
    cmd_txt =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";
    exp_rsp = "25 IPv4 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd_txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    ConstElementPtr hosts_all = rsp_args->get("hosts");
    ASSERT_TRUE(hosts_all);
    ASSERT_EQ(Element::list, hosts_all->getType());
    ASSERT_EQ(25, hosts_all->size());

    // Get first page.
    ElementPtr cmd = Element::createMap();
    cmd->set("command", Element::create(string("reservation-get-page")));
    ElementPtr cmd_args = Element::createMap();
    cmd_args->set("subnet-id", Element::create(1));
    cmd_args->set("limit", Element::create(10));
    cmd->set("arguments", cmd_args);

    exp_rsp = "10 IPv4 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    ConstElementPtr page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    ASSERT_EQ(10, page->size());
    ElementPtr hosts = data::copy(page);
    ConstElementPtr count = rsp_args->get("count");
    ASSERT_TRUE(count);
    ASSERT_EQ(Element::integer, count->getType());
    EXPECT_EQ(10, count->intValue());
    ConstElementPtr next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    ConstElementPtr idx = next->get("source-index");
    ASSERT_TRUE(idx);
    ASSERT_EQ(Element::integer, idx->getType());
    EXPECT_EQ(1, idx->intValue());
    ConstElementPtr next_id = next->get("from");
    ASSERT_TRUE(next_id);
    ASSERT_EQ(Element::integer, next_id->getType());
    EXPECT_LT(0, next_id->intValue());

    // Get second page.
    cmd_args->set("source-index", idx);
    cmd_args->set("from", next_id);
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(10, page->size());
    for (size_t i = 0; i < page->size(); ++i) {
        hosts->add(data::copy(page->get(i)));
    }
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Get last page.
    cmd_args->set("from", next_id);
    exp_rsp = "5 IPv4 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(5, page->size());
    for (size_t i = 0; i < page->size(); ++i) {
        hosts->add(data::copy(page->get(i)));
    }
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Check that we are at the end.
    cmd_args->set("from", next_id);
    exp_rsp = "0 IPv4 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(0, page->size());
    next = rsp_args->get("next");
    EXPECT_FALSE(next);

    // Get page and all should retrieve the same thing modulo the subnet-id.
    ElementPtr expected = data::copy(hosts_all);
    ASSERT_TRUE(expected);
    ASSERT_EQ(expected->getType(), Element::list);
    for (auto const& host : expected->listValue()) {
        host->set("subnet-id", Element::create(1));
    }
    EXPECT_TRUE(hosts->equals(*expected));
}

// Checks that reservation-get-page with some IPv6 hosts in a subnet.
TEST_F(HostCmdsTest, getPage6Subnet) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd_txt =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv6 host(s) found.";
    testCommand(cmd_txt, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    static uint8_t duid[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 73};
    IOAddress addr("2001:db8:1::");
    for (unsigned i = 0; i < 25; ++i) {
        duid[sizeof(duid) - 1]++;
        vector<uint8_t> ident(duid, duid + sizeof(duid));
        addr = IOAddress::increase(addr);
        HostPtr host(new Host(&ident[0], ident.size(),
                              Host::IDENT_DUID,
                              SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                              IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, addr));
        hds->add(host);
    }
    EXPECT_EQ(25, hds->size());

    // Get all.
    cmd_txt =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";
    exp_rsp = "25 IPv6 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd_txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    ConstElementPtr hosts_all = rsp_args->get("hosts");
    ASSERT_TRUE(hosts_all);
    ASSERT_EQ(Element::list, hosts_all->getType());
    ASSERT_EQ(25, hosts_all->size());

    // Get first page.
    ElementPtr cmd = Element::createMap();
    cmd->set("command", Element::create(string("reservation-get-page")));
    ElementPtr cmd_args = Element::createMap();
    cmd_args->set("subnet-id", Element::create(1));
    cmd_args->set("limit", Element::create(10));
    cmd->set("arguments", cmd_args);

    exp_rsp = "10 IPv6 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    ConstElementPtr page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    ASSERT_EQ(10, page->size());
    ElementPtr hosts = data::copy(page);
    ConstElementPtr count = rsp_args->get("count");
    ASSERT_TRUE(count);
    ASSERT_EQ(Element::integer, count->getType());
    EXPECT_EQ(10, count->intValue());
    ConstElementPtr next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    ConstElementPtr idx = next->get("source-index");
    ASSERT_TRUE(idx);
    ASSERT_EQ(Element::integer, idx->getType());
    EXPECT_EQ(1, idx->intValue());
    ConstElementPtr next_id = next->get("from");
    ASSERT_TRUE(next_id);
    ASSERT_EQ(Element::integer, next_id->getType());
    EXPECT_LT(0, next_id->intValue());

    // Get second page.
    cmd_args->set("source-index", idx);
    cmd_args->set("from", next_id);
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(10, page->size());
    for (size_t i = 0; i < page->size(); ++i) {
        hosts->add(data::copy(page->get(i)));
    }
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Get last page.
    cmd_args->set("from", next_id);
    exp_rsp = "5 IPv6 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(5, page->size());
    for (size_t i = 0; i < page->size(); ++i) {
        hosts->add(data::copy(page->get(i)));
    }
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Check that we are at the end.
    cmd_args->set("from", next_id);
    exp_rsp = "0 IPv6 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(0, page->size());
    next = rsp_args->get("next");
    EXPECT_FALSE(next);

    // Get page and all should retrieve the same thing modulo the subnet-id.
    ElementPtr expected = data::copy(hosts_all);
    ASSERT_TRUE(expected);
    ASSERT_EQ(expected->getType(), Element::list);
    for (auto const& host : expected->listValue()) {
        host->set("subnet-id", Element::create(1));
    }
    EXPECT_TRUE(hosts->equals(*expected));
}

// Checks that reservation-get-page with some IPv4 hosts.
TEST_F(HostCmdsTest, getPage4) {
    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd_txt =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv4 host(s) found.";
    testCommand(cmd_txt, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    ConstHostPtr host0;
    static uint8_t hwaddr[] = {65, 66, 67, 68, 69, 69};
    IOAddress addr("192.0.2.0");
    for (unsigned i = 0; i < 25; ++i) {
        hwaddr[sizeof(hwaddr) - 1]++;
        vector<uint8_t> ident(hwaddr, hwaddr + sizeof(hwaddr));
        addr = IOAddress::increase(addr);
        HostPtr host(new Host(&ident[0], ident.size(),
                              Host::IDENT_HWADDR,
                              SubnetID(i), SubnetID(SUBNET_ID_UNUSED),
                              addr));
        if (i == 0) {
            host0 = host;
        }
        hds->add(host);
    }

    // Add an IPv6 host (it will be ignored from its subnet id).
    HostPtr hostu(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(2),
                           IOAddress("0.0.0.0")));
    hostu->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:2::6")));
    hds->add(hostu);
    EXPECT_EQ(26, hds->size());

    // Get first page.
    ElementPtr cmd = Element::createMap();
    cmd->set("command", Element::create(string("reservation-get-page")));
    ElementPtr cmd_args = Element::createMap();
    cmd_args->set("limit", Element::create(10));
    cmd->set("arguments", cmd_args);

    exp_rsp = "10 IPv4 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    ConstElementPtr rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    ConstElementPtr page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    ASSERT_EQ(10, page->size());
    ConstElementPtr count = rsp_args->get("count");
    ASSERT_TRUE(count);
    ASSERT_EQ(Element::integer, count->getType());
    EXPECT_EQ(10, count->intValue());
    ConstElementPtr next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    ConstElementPtr idx = next->get("source-index");
    ASSERT_TRUE(idx);
    ASSERT_EQ(Element::integer, idx->getType());
    EXPECT_EQ(1, idx->intValue());
    ConstElementPtr next_id = next->get("from");
    ASSERT_TRUE(next_id);
    ASSERT_EQ(Element::integer, next_id->getType());
    EXPECT_LT(0, next_id->intValue());
    // Expect the first host is host0.
    compResponseHost4(page->get(0), host0);

    // Get second page.
    cmd_args->set("source-index", idx);
    cmd_args->set("from", next_id);
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(10, page->size());
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Get last page.
    cmd_args->set("from", next_id);
    exp_rsp = "5 IPv4 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(5, page->size());
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Check that we are at the end.
    cmd_args->set("from", next_id);
    exp_rsp = "0 IPv4 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(0, page->size());
    next = rsp_args->get("next");
    EXPECT_FALSE(next);
}

// Checks that reservation-get-page with some IPv6 hosts.
TEST_F(HostCmdsTest, getPage6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd_txt =
        "{\n"
        "    \"command\": \"reservation-get-page\",\n"
        "    \"arguments\": {"
        "        \"limit\": 100\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv6 host(s) found.";
    testCommand(cmd_txt, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    ConstHostPtr host0;
    static uint8_t duid[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 73};
    IOAddress addr("2001:db8:1::");
    for (unsigned i = 0; i < 25; ++i) {
        duid[sizeof(duid) - 1]++;
        vector<uint8_t> ident(duid, duid + sizeof(duid));
        addr = IOAddress::increase(addr);
        HostPtr host(new Host(&ident[0], ident.size(),
                              Host::IDENT_DUID,
                              SubnetID(SUBNET_ID_UNUSED), SubnetID(i),
                              IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, addr));
        if (i == 0) {
            host0 = host;
        }
        hds->add(host);
    }

    // Add an IPv4 host (it will be ignored from its subnet id).
    HostPtr hostu(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.3.6")));
    hds->add(hostu);
    EXPECT_EQ(26, hds->size());

    // Get first page.
    ElementPtr cmd = Element::createMap();
    cmd->set("command", Element::create(string("reservation-get-page")));
    ElementPtr cmd_args = Element::createMap();
    cmd_args->set("limit", Element::create(10));
    cmd->set("arguments", cmd_args);

    exp_rsp = "10 IPv6 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    ConstElementPtr rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    ConstElementPtr page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    ASSERT_EQ(10, page->size());
    ConstElementPtr count = rsp_args->get("count");
    ASSERT_TRUE(count);
    ASSERT_EQ(Element::integer, count->getType());
    EXPECT_EQ(10, count->intValue());
    ConstElementPtr next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    ConstElementPtr idx = next->get("source-index");
    ASSERT_TRUE(idx);
    ASSERT_EQ(Element::integer, idx->getType());
    EXPECT_EQ(1, idx->intValue());
    ConstElementPtr next_id = next->get("from");
    ASSERT_TRUE(next_id);
    ASSERT_EQ(Element::integer, next_id->getType());
    EXPECT_LT(0, next_id->intValue());
    // Expect the first host is host0.
    compResponseHost6(page->get(0), host0);

    // Get second page.
    cmd_args->set("source-index", idx);
    cmd_args->set("from", next_id);
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(10, page->size());
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Get last page.
    cmd_args->set("from", next_id);
    exp_rsp = "5 IPv6 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(5, page->size());
    next = rsp_args->get("next");
    ASSERT_TRUE(next);
    ASSERT_EQ(Element::map, next->getType());
    next_id = next->get("from");
    ASSERT_TRUE(next_id);

    // Check that we are at the end.
    cmd_args->set("from", next_id);
    exp_rsp = "0 IPv6 host(s) found.";
    rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
    ASSERT_TRUE(rsp);
    rsp_args = rsp->get("arguments");
    ASSERT_TRUE(rsp_args);
    page = rsp_args->get("hosts");
    ASSERT_TRUE(page);
    ASSERT_EQ(Element::list, page->getType());
    EXPECT_EQ(0, page->size());
    next = rsp_args->get("next");
    EXPECT_FALSE(next);
}

// Checks that subnetID = SUBNET_ID_GLOBAL is ok for IPv4 host reservations
TEST_F(HostCmdsTest, subnetIdGlobal4) {
    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);
    ASSERT_EQ(0, hds->size());

    // Command to add global host.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 0,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "Host added.");

    // Make sure we now have at least one host.
    ASSERT_EQ(1, hds->size());

    // Verify that we can fetch the host using global subnet id.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";

    // Note the status expected is success. The host should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "Host found.");

    // Verify that we can fetch hosts using global subnet id.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0\n"
        "    }\n"
        "}";

    // Note the status expected is success. Hosts should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "1 IPv4 host(s) found.");

    // Make sure that trying to fetch the global HR with subnet other
    // than global subnet id, does NOT find it.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";

    // Verify we did NOT find it.
    testCommand(cmd, CONTROL_RESULT_EMPTY, "Host not found.");

    // Add the 7777 subnet.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.7.0"),
                                  24, 30, 40, 50, 7777));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // Make sure that trying to fetch global HRs with subnet other
    // than global subnet id, does NOT find them.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777\n"
        "    }\n"
        "}";

    // Verify we did NOT find them.
    testCommand(cmd, CONTROL_RESULT_EMPTY, "0 IPv4 host(s) found.");

    // Verify we can delete the global host.
    cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";

    // Note the status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "Host deleted.");

    // Make sure we now have at least one host.
    EXPECT_EQ(0, hds->size());
}

// Checks that subnetID = SUBNET_ID_GLOBAL is ok for IPv6 host reservations
TEST_F(HostCmdsTest, subnetIdGlobal6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);
    ASSERT_EQ(0, hds->size());

    // Command to add global host.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-add\",\n"
        "    \"arguments\": {"
        "        \"reservation\": {"
        "            \"subnet-id\": 0,\n"
        "            \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"ip-addresses\": [ \"3001::1\"] "
        "        }\n"
        "    }\n"
        "}";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "Host added.");

    // Make sure we now have at least one host.
    ASSERT_EQ(1, hds->size());

    // Verify that we can fetch the host using global subnet id.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0,\n"
        "        \"ip-address\": \"3001::1\"\n"
        "    }\n"
        "}";

    // Note the status expected is success. The host should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "Host found.");

    // Verify that we can fetch hosts using global subnet id.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0\n"
        "    }\n"
        "}";

    // Note the status expected is success. Hosts should be returned.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "1 IPv6 host(s) found.");

    // Make sure that trying to fetch the global HR with subnet other
    // than global subnet id, does NOT find it.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 777,\n"
        "        \"ip-address\": \"3001::1\"\n"
        "    }\n"
        "}";

    // Verify we did NOT find it.
    testCommand(cmd, CONTROL_RESULT_EMPTY, "Host not found.");

    // Add the 7777 subnet.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:100::"),
                                  64, 30, 40, 50, 60, 7777));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Make sure that trying to fetch global HRs with subnet other
    // than global subnet id, does NOT find them.
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777\n"
        "    }\n"
        "}";

    // Verify we did NOT find them.
    testCommand(cmd, CONTROL_RESULT_EMPTY, "0 IPv6 host(s) found.");


    // Command to fetch del the host.
    cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0,\n"
        "        \"ip-address\": \"3001::1\"\n"
        "    }\n"
        "}";

    // Note the status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, "Host deleted.");

    // Make sure we now have at least one host.
    EXPECT_EQ(0, hds->size());
}

// Checks that reservation-get-by-hostname with some IPv4 hosts.
TEST_F(HostCmdsTest, getByHostname4) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    // Add another subnet.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 50, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    \"hostname\": \"host.Example.org\"\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv4 host(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Retry with the subnet.
    string cmd4 =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    \"hostname\": \"host.example.Org\",\n"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";

    exp_rsp = "0 IPv4 host(s) found.";
    testCommand(cmd4, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    HostPtr host1(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.1"),
                           "host.example.org"));
    hds->add(host1);
    HostPtr host2(new Host("01:02:03:04:05:07", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.2"),
                           "HOST.EXAMPLE.ORG"));
    hds->add(host2);
    HostPtr host3(new Host("01:02:03:04:05:08", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.3"),
                           "Host.Example.Org"));
    hds->add(host3);
    HostPtr host4(new Host("01:02:03:04:05:09", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.4"),
                           "host.example.com"));
    hds->add(host4);

    // Add another host in another subnet.
    HostPtr host5(new Host("01:02:03:04:05:0a", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.3.5"),
                           "host.example.org"));
    hds->add(host5);

    // Add an IPv6 host (it will be ignored from its subnet id).
    HostPtr hostu(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(2),
                           IOAddress("0.0.0.0")));
    hostu->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:2::6")));
    hds->add(hostu);
    EXPECT_EQ(6, hds->size());

    // Retry command.
    exp_rsp = "4 IPv4 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(4, hosts->size());

    // Assume the order is kept.
    compResponseHost4(hosts->get(0), host1);
    compResponseHost4(hosts->get(1), host2);
    compResponseHost4(hosts->get(2), host3);
    compResponseHost4(hosts->get(3), host5);

    // Retry command with subnet.
    exp_rsp = "3 IPv4 host(s) found.";
    rsp = testCommand(cmd4, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    args = rsp->get("arguments");
    ASSERT_TRUE(args);
    hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(3, hosts->size());

    // Assume the order is kept.
    ElementPtr expected = host1->toElement4();
    expected->set("subnet-id", Element::create(1));
    EXPECT_TRUE(isEquivalent(hosts->get(0), expected));
    expected = host2->toElement4();
    expected->set("subnet-id", Element::create(1));
    EXPECT_TRUE(isEquivalent(hosts->get(1), expected));
    expected = host3->toElement4();
    expected->set("subnet-id", Element::create(1));
    EXPECT_TRUE(isEquivalent(hosts->get(2), expected));
}

// Checks that reservation-get-by-hostname with some IPv6 hosts.
TEST_F(HostCmdsTest, getByHostname6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    // Add another subnet.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"),
                                   64, 30, 40, 50, 60, 2));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    \"hostname\": \"host.examplE.org\"\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv6 host(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Retry with the subnet.
    string cmd6 =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    \"hostname\": \"host.example.orG\",\n"
        "        \"subnet-id\": 1\n"
        "    }\n"
        "}";

    exp_rsp = "0 IPv6 host(s) found.";
    testCommand(cmd6, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    HostPtr host1(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "host.example.org"));
    host1->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::1")));
    hds->add(host1);
    HostPtr host2(new Host("01:02:03:04:05:07", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "HOST.EXAMPLE.ORG"));
    host2->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::2")));
    hds->add(host2);
    HostPtr host3(new Host("01:02:03:04:05:08", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "Host.Example.Org"));
    host3->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::3")));
    hds->add(host3);
    HostPtr host4(new Host("01:02:03:04:05:09", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0"),
                           "host.example.com"));
    host4->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::4")));
    hds->add(host4);

    // Add another host in another subnet.
    HostPtr host5(new Host("01:02:03:04:05:0a", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(2),
                           IOAddress("0.0.0.0"),
                           "host.example.org"));
    host5->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:2::5")));
    hds->add(host5);

    // Add an IPv4 host (it will be ignored from its subnet id).
    HostPtr hostu(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.3.6")));
    hds->add(hostu);
    EXPECT_EQ(6, hds->size());

    // Retry command.
    exp_rsp = "4 IPv6 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(4, hosts->size());

    // Assume the order is kept.
    compResponseHost6(hosts->get(0), host1);
    compResponseHost6(hosts->get(1), host2);
    compResponseHost6(hosts->get(2), host3);
    compResponseHost6(hosts->get(3), host5);

    // Retry command with subnet.
    exp_rsp = "3 IPv6 host(s) found.";
    rsp = testCommand(cmd6, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    args = rsp->get("arguments");
    ASSERT_TRUE(args);
    hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(3, hosts->size());

    // Assume the order is kept.
    ElementPtr expected = host1->toElement6();
    expected->set("subnet-id", Element::create(1));
    EXPECT_TRUE(isEquivalent(hosts->get(0), expected));
    expected = host2->toElement6();
    expected->set("subnet-id", Element::create(1));
    EXPECT_TRUE(isEquivalent(hosts->get(1), expected));
    expected = host3->toElement6();
    expected->set("subnet-id", Element::create(1));
    EXPECT_TRUE(isEquivalent(hosts->get(2), expected));
}

// Checks that reservation-get-by-hostname can handle a situation when
// the query is broken (no parameters at all).
TEST_F(HostCmdsTest, reservationGetByHostnameNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'hostname' (<string>:3:19)";

    // This should be rejected, because hostname parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Now try without arguments at all
    cmd = "{\n"
        "    \"command\": \"reservation-get-by-hostname\"\n"
        "}";
    exp_rsp = "Parameters missing or are not a map.";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get-by-hostname detects empty hostname.
TEST_F(HostCmdsTest, reservationGetByHostnameEmpty) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Empty hostname";

    // This should be rejected, because hostname parameter must not be empty.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get-by-hostname detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetByHostname4OutOfRangeSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo\",\n"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo\",\n"
        "        \"subnet-id\": 4294967295\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-by-hostname detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetByHostname6OutOfRangeSubnetID) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo\",\n"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo\",\n"
        "        \"subnet-id\": 4294967295\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-by-hostname detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetByHostname4NotConfiguredSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo\",\n"
        "        \"subnet-id\": 7777\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv4 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-by-hostname detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetByHostname6NotConfiguredSubnetID) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo\",\n"
        "        \"subnet-id\": 7777\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv6 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-by-id with some IPv4 hosts.
TEST_F(HostCmdsTest, getById4) {
    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-id\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv4 host(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    HostPtr host1(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.1")));
    hds->add(host1);
    HostPtr host2(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.2")));
    hds->add(host2);
    HostPtr host3(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(3), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.3")));
    hds->add(host3);
    HostPtr host4(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(4), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.4")));
    hds->add(host4);

    // Add another host with another identifier.
    HostPtr host5(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.3.5")));
    hds->add(host5);

    // Add an IPv6 host (it will be ignored from its subnet id).
    HostPtr hostu(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(2),
                           IOAddress("0.0.0.0")));
    hostu->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:2::6")));
    hds->add(hostu);
    EXPECT_EQ(6, hds->size());

    // Retry command.
    exp_rsp = "4 IPv4 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(4, hosts->size());

    // Assume the order is kept.
    compResponseHost4(hosts->get(0), host1);
    compResponseHost4(hosts->get(1), host2);
    compResponseHost4(hosts->get(2), host3);
    compResponseHost4(hosts->get(3), host4);
}

// Checks that reservation-get-by-id with some IPv6 hosts.
TEST_F(HostCmdsTest, getById6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-id\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";

    string exp_rsp = "0 IPv6 host(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Add some hosts.
    HostPtr host1(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                           IOAddress("0.0.0.0")));
    host1->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::1")));
    hds->add(host1);
    HostPtr host2(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(2),
                           IOAddress("0.0.0.0")));
    host2->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::2")));
    hds->add(host2);
    HostPtr host3(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(3),
                           IOAddress("0.0.0.0")));
    host3->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::3")));
    hds->add(host3);
    HostPtr host4(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(4),
                           IOAddress("0.0.0.0")));
    host4->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::4")));
    hds->add(host4);

    // Add another host with another identifier.
    HostPtr host5(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(SUBNET_ID_UNUSED), SubnetID(2),
                           IOAddress("0.0.0.0")));
    host5->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:2::5")));
    hds->add(host5);

    // Add an IPv4 host (it will be ignored from its subnet id).
    HostPtr hostu(new Host("01:02:03:04:05:05", "hw-address",
                           SubnetID(2), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.3.6")));
    hds->add(hostu);
    EXPECT_EQ(6, hds->size());

    // Retry command.
    exp_rsp = "4 IPv6 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(4, hosts->size());

    // Assume the order is kept.
    compResponseHost6(hosts->get(0), host1);
    compResponseHost6(hosts->get(1), host2);
    compResponseHost6(hosts->get(2), host3);
    compResponseHost6(hosts->get(3), host4);
}

// Checks that reservation-get-by-id can handle a situation when
// the query is broken (no parameters at all).
TEST_F(HostCmdsTest, reservationGetByIdNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-id\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'identifier-type' is either missing or not a string.";

    // This should be rejected, because identifier parameters are mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Now try without arguments at all
    cmd = "{\n"
        "    \"command\": \"reservation-get-by-id\"\n"
        "}";
    exp_rsp = "Parameters missing or are not a map.";

    // This should be rejected, because identifier parameters are mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get-by-id can handle a situation when
// the query is broken (identifier-type) and identifier itself missing.
TEST_F(HostCmdsTest, reservationGetByIdNoIdentifier) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-id\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\"\n"
        "    }\n"
        "}";
    string rsp = "'identifier' is either missing or not a string.";

    // It's better (one parameter missing), but not yet correct.
    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get-by-id can handle a situation when
// the query is broken (identifier) and identifier-type itself missing.
TEST_F(HostCmdsTest, reservationGetByIdNoIdentifierType) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-id\",\n"
        "    \"arguments\": {"
        "        \"identifier\": \"00:11:22:33:44:55\"\n"
        "    }\n"
        "}";
    string rsp = "'identifier-type' is either missing or not a string.";

    // It's better (one parameter missing), but not yet correct.
    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get-by-id can handle a situation when
// the query is broken (forbidden subnet-id).
TEST_F(HostCmdsTest, reservationGetByIdForbiddenSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-id\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"00:11:22:33:44:55\"\n"
        "    }\n"
        "}";

    string rsp = "'subnet-id' is forbidden in reservation-get-by-id";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that missing arguments are properly reported as an error
// in the response to the reservation-update command.
TEST_F(HostCmdsTest, reservationUpdateNegativeTestMissingArguments) {
    testCommand(R"(
        {
            "command": "reservation-update"
        }
    )",
                CONTROL_RESULT_ERROR,
                "invalid command: does not contain mandatory 'arguments'");
}

// Checks that wrong type for arguments is properly reported as an
// error in the response to the reservation-update command.
TEST_F(HostCmdsTest, reservationUpdateNegativeTestListArguments) {
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": []
        }
    )",
                CONTROL_RESULT_ERROR,
                "invalid command: expected 'arguments' to be a map, got list instead");
}

// Checks that empty arguments are properly reported as an
// error in the response to the reservation-update command.
TEST_F(HostCmdsTest, reservationUpdateNegativeTestMissingReservation) {
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {}
        }
    )",
                CONTROL_RESULT_ERROR,
                "invalid command: expected 'reservation' as the sole parameter inside the "
                "'arguments' map, didn't get it instead");
}

// Checks that wrong type for reservation is properly reported as an
// error in the response to the reservation-update command.
TEST_F(HostCmdsTest, reservationUpdateNegativeTestListReservation) {
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": []
            }
        }
    )",
                CONTROL_RESULT_ERROR,
                "invalid command: expected 'reservation' to be a map, got list instead");
}

// Checks that an empty reservation is properly reported as an
// error in the response to the reservation-update command.
TEST_F(HostCmdsTest, reservationUpdateNegativeTestMissingSubnetId) {
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {}
            }
        }
    )",
                CONTROL_RESULT_ERROR,
                "Mandatory 'subnet-id' parameter missing."
                " Use `reservation-get-by-id' or"
                " 'reservation-get-by-address' to get the list of"
                " reservations with given identifier or address.");
}

// Checks that a missing host identifier is properly reported as an
// error in the response to the reservation-update command.
TEST_F(HostCmdsTest, reservationUpdateNegativeTestWrongTypeForSubnetId) {
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "subnet-id": "1"
                }
            }
        }
    )",
                CONTROL_RESULT_ERROR,
                "'subnet-id' parameter is not integer.");
}

// Checks that a missing host identifier is properly reported as an
// error in the response to the reservation-update command.
TEST_F(HostCmdsTest, reservationUpdateNegativeTestMissingIdentifier) {
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "subnet-id": 1
                }
            }
        }
    )",
                CONTROL_RESULT_ERROR,
                "one of the supported identifiers must be specified for host reservation: "
                "circuit-id, client-id, duid, flex-id, hw-address (:0:0)");
}

// Checks that an update on a host that has not been inserted yet
// results in an error.
TEST_F(HostCmdsTest, reservationUpdateNoHost) {
    // Assume v6.
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Create a dummy memory-based host data source.
    MemHostDataSourcePtr const hds(setHostsDataSource(/* insert_v4 = */ false,
                                                      /* insert_v6 = */ false));
    ASSERT_TRUE(hds);

    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "duid": "1234",
                    "subnet-id": 1
                }
            }
        }
    )",
                CONTROL_RESULT_ERROR,
                "Host not updated (not found).");
}

// Checks that an update with no reserved resources on an existing host works.
TEST_F(HostCmdsTest, reservationUpdateSimpleHost) {
    // Assume v6.
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Create a dummy memory-based host data source.
    MemHostDataSourcePtr const hds(setHostsDataSource(/* insert_v4 = */ false,
                                                      /* insert_v6 = */ false));
    ASSERT_TRUE(hds);

    HostPtr host;
    EXPECT_NO_THROW(host = boost::make_shared<Host>("1234", "duid", SubnetID(SUBNET_ID_UNUSED),
                                                    SubnetID(1), IOAddress("0.0.0.0")));
    HostMgr::instance().add(host);

    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "duid": "1234",
                    "subnet-id": 1,
                    "hostname": "domain.example.com"
                }
            }
        }
    )",
                CONTROL_RESULT_SUCCESS,
                "Host updated.");

    ConstHostCollection hosts = HostMgr::instance().getAll6(SubnetID(1));
    EXPECT_EQ(1, hosts.size());
    EXPECT_EQ("domain.example.com", hosts[0]->getHostname());
}

// Checks that an update in all data sources with no reserved resources on an
// existing host works.
TEST_F(HostCmdsTest, reservationUpdateSimpleHostAllDataSources) {
    // Assume v6.
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Create a dummy memory-based host data source.
    MemHostDataSourcePtr const hds(setHostsDataSource(/* insert_v4 = */ false,
                                                      /* insert_v6 = */ false));
    ASSERT_TRUE(hds);

    HostPtr host;
    EXPECT_NO_THROW(host = boost::make_shared<Host>("123456", "duid", SubnetID(SUBNET_ID_UNUSED),
                                                    SubnetID(1), IOAddress("0.0.0.0")));
    HostMgr::instance().add(host, HostMgrOperationTarget::ALL_SOURCES);

    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "duid": "123456",
                    "subnet-id": 1,
                    "hostname": "domain.example.com"
                },
                "operation-target": "all"
            }
        }
    )",
                CONTROL_RESULT_SUCCESS,
                "Host updated.");

    ConstHostCollection hosts = HostMgr::instance().getAll6(SubnetID(1));
    EXPECT_EQ(2, hosts.size());
    for (auto const& h : hosts) {
        EXPECT_EQ("domain.example.com", h->getHostname());
    }
}

// Checks that an update with some reserved resources on an existing host works.
TEST_F(HostCmdsTest, reservationUpdateHostWithResources) {
    // Assume v6.
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Create a dummy memory-based host data source.
    MemHostDataSourcePtr const hds(setHostsDataSource(/* insert_v4 = */ false,
                                                      /* insert_v6 = */ false));
    ASSERT_TRUE(hds);

    HostPtr host;
    EXPECT_NO_THROW(host = boost::make_shared<Host>("1234", "duid", SubnetID(SUBNET_ID_UNUSED),
                                                    SubnetID(1), IOAddress("0.0.0.0")));
    HostMgr::instance().add(host);

    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "duid": "1234",
                    "subnet-id": 1,
                    "ip-addresses": ["2001:db8:1::1"],
                    "hostname": "domain.example.com",
                    "prefixes": ["::/32", "2001:db8::/64"],
                    "client-classes": ["foo", "bar"],
                    "user-context": "my user context"
                }
            }
        }
    )",
                CONTROL_RESULT_SUCCESS,
                "Host updated.");

    std::vector<uint8_t> const& identifier(host->getIdentifier());

    ConstHostPtr const retrieved(HostMgr::instance().get6(SubnetID(1), Host::IDENT_DUID,
                                                          identifier.data(), identifier.size()));
    ASSERT_TRUE(retrieved);
    EXPECT_EQ(retrieved->toText(),
              "duid=1234 ipv6_subnet_id=1 hostname=domain.example.com "
              "ipv4_reservation=(no) siaddr=(no) sname=(empty) file=(empty) "
              "key=(empty) ipv6_reservation0=2001:db8:1::1 ipv6_reservation1=::/32 "
              "ipv6_reservation2=2001:db8::/64 dhcp6_class0=foo dhcp6_class1=bar");
    ASSERT_TRUE(retrieved->getContext());
    EXPECT_EQ(retrieved->getContext()->stringValue(), "my user context");
}

// Checks that the reservation is not updated if the specified IP address
// is not in range of the configured subnet prefix.
TEST_F(HostCmdsTest, reservationUpdateNonMatchingSubnetPrefix) {
    CfgMgr::instance().setFamily(AF_INET);

    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.64"), 26, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // Create in-memory hosts database to be used for the test.
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    HostPtr host;
    EXPECT_NO_THROW(host = boost::make_shared<Host>("1a:1b:1c:1d:1e:1f",
                                                    "hw-address",
                                                    SubnetID(1),
                                                    SubnetID(SUBNET_ID_UNUSED),
                                                    IOAddress("0.0.0.0")));
    HostMgr::instance().add(host);

    // Subnet id matches the configured subnet, but all reserved IP
    // addresses should be in range of the subnet prefix.
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "hw-address": "1a:1b:1c:1d:1e:1f",
                    "subnet-id": 1,
                    "ip-address": "192.0.2.63",
                    "hostname": "domain.example.com"
                }
            }
        }
    )",
                CONTROL_RESULT_ERROR,
                "specified reservation '192.0.2.63' is not matching the "
                "IPv4 subnet prefix '192.0.2.64/26'");

    std::vector<uint8_t> const& identifier(host->getIdentifier());

    ConstHostPtr const retrieved(HostMgr::instance().get4(SubnetID(1),
                                                          Host::IDENT_HWADDR,
                                                          identifier.data(),
                                                          identifier.size()));
    ASSERT_TRUE(retrieved);
    EXPECT_EQ(retrieved->toText(),
              "hwaddr=1A1B1C1D1E1F ipv4_subnet_id=1 hostname=(empty) "
              "ipv4_reservation=(no) siaddr=(no) sname=(empty) file=(empty) "
              "key=(empty) ipv6_reservations=(none)");
    EXPECT_FALSE(retrieved->getContext());
}

// Checks that the reservation is not updated if any of the specified IPv6
// addresses is not in range of the configured subnet prefix.
TEST_F(HostCmdsTest, reservationUpdateNonMatchingSubnetPrefix6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // Create in-memory hosts database to be used for the test.
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    HostPtr host;
    EXPECT_NO_THROW(host = boost::make_shared<Host>("1234", "duid",
                                                    SubnetID(SUBNET_ID_UNUSED),
                                                    SubnetID(1),
                                                    IOAddress("0.0.0.0")));
    HostMgr::instance().add(host);

    // Subnet id matches the configured subnet, but all reserved IP
    // addresses should be in range of the subnet prefix.
    testCommand(R"(
        {
            "command": "reservation-update",
            "arguments": {
                "reservation": {
                    "duid": "1234",
                    "subnet-id": 1,
                    "ip-addresses": ["2001:db8:1::1", "2001:db8:2::2"],
                    "hostname": "domain.example.com"
                }
            }
        }
    )",
                CONTROL_RESULT_ERROR,
                "specified reservation '2001:db8:2::2' is not matching the "
                "IPv6 subnet prefix '2001:db8:1::/64'");

    std::vector<uint8_t> const& identifier(host->getIdentifier());

    ConstHostPtr const retrieved(HostMgr::instance().get6(SubnetID(1),
                                                          Host::IDENT_DUID,
                                                          identifier.data(),
                                                          identifier.size()));
    ASSERT_TRUE(retrieved);
    EXPECT_EQ(retrieved->toText(),
              "duid=1234 ipv6_subnet_id=1 hostname=(empty) ipv4_reservation=(no) "
              "siaddr=(no) sname=(empty) file=(empty) key=(empty) "
              "ipv6_reservations=(none)");
    EXPECT_FALSE(retrieved->getContext());
}

// Checks that reservation-get-by-address can handle a situation when the query is
// broken (no parameters at all).
TEST_F(HostCmdsTest, reservationGetByAddressNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get-by-address detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetByAddress4OutOfRangeSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295,\n"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-by-address(addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationGetByAddress4HostNotFound) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 host(s) found.";

    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-get-by-address(subnet-id, addr4) can handle a situation when
// the query is correctly formed and one host is returned.
TEST_F(HostCmdsTest, reservationGetByAddress4HostFound) {
    // Add a valid subnet with subnet ID of 1.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Check that there are no hosts
    EXPECT_EQ(0, hds->size());

    // Add host to the configuration.
    HostPtr host0(new Host("01:02:03:04:05:00", "hw-address",
                           SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.10"),
                           "host0.example.org"));
    hds->add(host0);
    EXPECT_EQ(1, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"192.0.2.10\"\n"
        "    }\n"
        "}";

    string exp_rsp = "1 IPv4 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(1, hosts->size());

    ElementPtr rsp0 = host0->toElement4();
    SubnetID subnet_id0 = host0->getIPv4SubnetID();
    rsp0->set("subnet-id", Element::create(static_cast<int64_t>(subnet_id0)));
    EXPECT_TRUE(isEquivalent(hosts->get(0), rsp0));
}

// Checks that reservation-get-by-address detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetByAddress4NotConfiguredSubnetID) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777,\n"
        "        \"ip-address\": \"192.168.0.100\"\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv4 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-by-address works with some IPv4 hosts.
TEST_F(HostCmdsTest, reservationGetByAddress4) {
    // Let's configure subnets 4 and 5
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50, 4));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet4);
    Subnet4Ptr subnet5(new Subnet4(IOAddress("192.0.0.0"), 16, 30, 40, 50, 5));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet5);
    CfgMgr::instance().commit();

    // Let's create a dummy host data source.
    // 2 host reservations are added to subnet-id 4 with the same IP address 192.0.2.100
    // and 1 host reservation is added to subnet-id 5 with the same IP address 192.0.2.100
    MemHostDataSourcePtr hds = setHostsDataSource(true, false, HostMgrOperationTarget::ALTERNATE_SOURCES, true);
    ASSERT_TRUE(hds);

    // Let's extract Hosts from created host data source.
    uint8_t hw_addr_1[] = {1, 2, 3, 4, 5, 6};
    uint8_t hw_addr_2[] = {1, 2, 3, 4, 5, 7};
    uint8_t hw_addr_3[] = {1, 2, 3, 4, 5, 8};
    ConstHostPtr host1 = hds->get4(4, Host::IdentifierType::IDENT_HWADDR, &hw_addr_1[0], 6);
    ConstHostPtr host2 = hds->get4(4, Host::IdentifierType::IDENT_HWADDR, &hw_addr_2[0], 6);
    ConstHostPtr host3 = hds->get4(5, Host::IdentifierType::IDENT_HWADDR, &hw_addr_3[0], 6);
    ASSERT_TRUE(host1);
    ASSERT_TRUE(host2);
    ASSERT_TRUE(host3);

    // Now send the command with the subnet-id 4.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "    \"ip-address\": \"192.0.2.100\",\n"
        "    \"subnet-id\": 4\n"
        "    }\n"
        "}";

    string exp_rsp = "2 IPv4 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(2, hosts->size());

    // Let's verify if hosts received in a response are as expected.
    compResponseHost4(hosts->get(0), host1);
    compResponseHost4(hosts->get(1), host2);

    // Retry without the subnet. All 3 host reservations are expected.
    string cmd_no_subnet =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "    \"ip-address\": \"192.0.2.100\"\n"
        "    }\n"
        "}";

    exp_rsp = "3 IPv4 host(s) found.";
    rsp = testCommand(cmd_no_subnet, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    args = rsp->get("arguments");
    ASSERT_TRUE(args);
    hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(3, hosts->size());

    // Let's verify if hosts received in a response are as expected.
    compResponseHost4(hosts->get(0), host1);
    compResponseHost4(hosts->get(1), host2);
    compResponseHost4(hosts->get(2), host3);
}

// Checks that reservation-get-by-address detects out-of-range subnet IDs
TEST_F(HostCmdsTest, reservationGetByAddress6OutOfRangeSubnetID) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1,\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (-1) is not within expected range:"
                " (0 - 4294967294)");
    cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 4294967295,\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "The 'subnet-id' value (4294967295) is not within expected "
                "range: (0 - 4294967294)");
}

// Checks that reservation-get-by-address(addr6) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(HostCmdsTest, reservationGetByAddress6HostNotFound) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv6 host(s) found.";

    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that reservation-get-by-address(subnet-id, addr6) can handle a situation when
// the query is correctly formed and one host is returned.
TEST_F(HostCmdsTest, reservationGetByAddress6HostFound) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 6));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source with v6 host
    MemHostDataSourcePtr hds = setHostsDataSource(false, true);
    ASSERT_TRUE(hds);

    EXPECT_EQ(1, hds->size());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"ip-address\": \"2001:db8::cafe:babe\"\n"
        "    }\n"
        "}";

    string exp_rsp = "1 IPv6 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(1, hosts->size());
}

// Checks that reservation-get-by-address detects not configured subnet IDs
TEST_F(HostCmdsTest, reservationGetByAddress6NotConfiguredSubnetID) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 7777,\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";

    testCommand(cmd, CONTROL_RESULT_ERROR,
                "IPv6 subnet with ID of '7777' is not configured");
}

// Checks that reservation-get-by-address works with some IPv6 hosts.
TEST_F(HostCmdsTest, reservationGetByAddress6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Let's configure subnets 6 and 7
    Subnet6Ptr subnet6(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 6));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet6);
    Subnet6Ptr subnet7(new Subnet6(IOAddress("2001:db8:1::"), 63, 30, 40, 50, 60, 7));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet7);
    CfgMgr::instance().commit();

    // Let's create a dummy host data source.
    // 2 host reservations are added to subnet-id 6 with the same IPv6 NA "2001:db8::cafe:babe"
    // and 1 host reservation is added to subnet-id 7 with the same IPv6 NA "2001:db8::cafe:babe"
    MemHostDataSourcePtr hds = setHostsDataSource(false, true, HostMgrOperationTarget::ALTERNATE_SOURCES, true);
    ASSERT_TRUE(hds);

    // Let's extract Hosts from created host data source.
    uint8_t hw_addr_1[] = {1, 2, 3, 4, 5, 6};
    uint8_t hw_addr_2[] = {1, 2, 3, 4, 5, 7};
    uint8_t hw_addr_3[] = {1, 2, 3, 4, 5, 8};
    ConstHostPtr host1 = hds->get6(6, Host::IdentifierType::IDENT_HWADDR, &hw_addr_1[0], 6);
    ConstHostPtr host2 = hds->get6(6, Host::IdentifierType::IDENT_HWADDR, &hw_addr_2[0], 6);
    ConstHostPtr host3 = hds->get6(7, Host::IdentifierType::IDENT_HWADDR, &hw_addr_3[0], 6);
    ASSERT_TRUE(host1);
    ASSERT_TRUE(host2);
    ASSERT_TRUE(host3);

    // Now send the command with the subnet-id 6.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 6,\n"
        "        \"ip-address\": \"2001:db8::cafe:babe\"\n"
        "    }\n"
        "}";

    string exp_rsp = "2 IPv6 host(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(2, hosts->size());

    // Let's verify if hosts received in a response are as expected.
    compResponseHost6(hosts->get(0), host1);
    compResponseHost6(hosts->get(1), host2);

    // Retry without the subnet. All 3 host reservations are expected.
    string cmd_no_subnet =
        "{\n"
        "    \"command\": \"reservation-get-by-address\",\n"
        "    \"arguments\": {"
        "    \"ip-address\": \"2001:db8::cafe:babe\"\n"
        "    }\n"
        "}";

    exp_rsp = "3 IPv6 host(s) found.";
    rsp = testCommand(cmd_no_subnet, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check response.
    ASSERT_TRUE(rsp);
    args = rsp->get("arguments");
    ASSERT_TRUE(args);
    hosts = args->get("hosts");
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(3, hosts->size());

    // Let's verify if hosts received in a response are as expected.
    compResponseHost6(hosts->get(0), host1);
    compResponseHost6(hosts->get(1), host2);
    compResponseHost6(hosts->get(2), host3);
}

// Check that a prefix exclude IPv6 reservation can be fetched
TEST_F(HostCmdsTest, reservationGet6PrefixExclude) {
    CfgMgr::instance().setFamily(AF_INET6);

    // Add a valid subnet with subnet ID of 1.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    CfgMgr::instance().commit();

    // First, let's create a dummy host data source (don't insert any hosts)
    MemHostDataSourcePtr hds = setHostsDataSource(false, false);
    ASSERT_TRUE(hds);

    // Add a host reservation with a Prefix Exclude option.
    HostPtr host(new Host("1a:1b:1c:1d:1e:1f", "hw-address",
                          SubnetID(SUBNET_ID_UNUSED), SubnetID(1),
                          IOAddress("0.0.0.0")));
    // Add two PD reservations.
    IPv6Resrv resv1(IPv6Resrv::TYPE_PD, IOAddress("3000::"), 32);
    host->addReservation(resv1);
    IPv6Resrv resv2(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 48);
    resv2.setPDExclude(IOAddress("2001:db8:0:1::"), 64);
    host->addReservation(resv2);
    ASSERT_NO_THROW(hds->add(host));

    // Get the host reservation.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Host found.";

    // Should have found it.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the host prefixes were indeed returned.
    ASSERT_TRUE(rsp);
    ASSERT_TRUE(rsp->get("arguments"));
    ConstElementPtr prefixes = rsp->get("arguments")->get("prefixes");
    ASSERT_TRUE(prefixes);
    ASSERT_EQ(Element::list, prefixes->getType());
    ConstElementPtr excluded_prefixes = rsp->get("arguments")->get("excluded-prefixes");
    ASSERT_TRUE(excluded_prefixes);
    ASSERT_EQ(Element::list, excluded_prefixes->getType());
    ASSERT_EQ(prefixes->size(), excluded_prefixes->size());
    bool got_3000(false);
    bool got_2001(false);
    for (size_t i = 0; i < prefixes->size(); ++i) {
        ConstElementPtr prefix = prefixes->get(i);
        ASSERT_TRUE(prefix);
        ASSERT_EQ(Element::string, prefix->getType());
        string pref = prefix->stringValue();

        ConstElementPtr excluded_prefix = excluded_prefixes->get(i);
        ASSERT_TRUE(excluded_prefix);
        string excluded_pref = excluded_prefix->stringValue();
        if (pref == "3000::/32") {
            EXPECT_FALSE(got_3000);
            got_3000 = true;
            EXPECT_EQ("", excluded_pref);
        } else if (pref == "2001:db8::/48") {
            EXPECT_FALSE(got_2001);
            got_2001 = true;
            EXPECT_EQ("2001:db8:0:1::/64", excluded_pref);
        } else {
            ADD_FAILURE() << "unexpected prefix " << pref;
        }
    }
    EXPECT_TRUE(got_3000);
    EXPECT_TRUE(got_2001);
}

}  // namespace
