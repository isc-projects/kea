// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include <config.h>

#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>
#include <config/command_mgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/cfgmgr.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <time.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::stats;
using namespace boost::posix_time;

namespace {

/// @brief Test fixture for testing loading and unloading the library
class LibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor
    LibLoadTest(std::string lib_filename)
        : lib_name_(lib_filename), start_time_(second_clock::universal_time()) {
        CommandMgr::instance();
        unloadLibs();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~LibLoadTest() {
        unloadLibs();
    }

    /// @brief Adds library/parameters to list of libraries to be loaded
    void addLib(const std::string& lib, ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    /// @brief Load all specified libraries.
    ///
    /// The libraries are stored in libraries
    void loadLibs() {
        ASSERT_TRUE(HooksManager::loadLibraries(libraries_))
            << "library loading failed";
    }

    /// @brief Unloads all libraries.
    void unloadLibs() {
        ASSERT_NO_THROW(HooksManager::unloadLibraries());
    }

    /// @brief Checks whether specified command is registered
    ///
    /// @param name name of the command to be checked
    /// @param expect_true true - must be registered, false - must not be
    void checkCommandRegistered(const std::string& name, bool expect_true) {

        // First get the list of registered commands
        ConstElementPtr lst = Element::fromJSON("{ \"command\": \"list-commands\" }");
        ConstElementPtr rsp = CommandMgr::instance().processCommand(lst);

        ASSERT_TRUE(rsp);

        ConstElementPtr args = rsp->get("arguments");
        ASSERT_TRUE(args);

        string args_txt = args->str();

        if (expect_true) {
            EXPECT_TRUE(args_txt.find(name) != string::npos);
        } else {
            EXPECT_TRUE(args_txt.find(name) == string::npos);
        } }

    /// @brief tests specified command and verifies response
    ///
    /// This method loads the library, sends specific command,
    /// then checks if the result is as expected, checks if text response
    /// is ok (optional, check skipped if exp_txt is empty) and then returns
    /// the response (for possible additional checks).
    ///
    /// @param cmd JSON command to be sent (must be valid JSON)
    /// @param exp_result 0 - success, 1 - error, 2 - ...
    /// @param exp_txt expected text response (optional)
    void testCommand(string cmd_txt, int exp_result, string exp_txt,
                     string exp_result_json = "") {
        // Let's load the library first.
        loadLib();

        ConstElementPtr cmd;
        ASSERT_NO_THROW(cmd = Element::fromJSON(cmd_txt))
                        << "command JSON invalid, test is broken";

        // Process the command and verify response.
        ConstElementPtr rsp = CommandMgr::instance().processCommand(cmd);
        checkAnswer(rsp, exp_result, exp_txt);

        // Don't care about argument contents, we're done.
        if (exp_result_json.empty()) {
            return;
        }

        // Turn expected result JSON into Element tree
        ConstElementPtr exp_args;
        ASSERT_NO_THROW(exp_args = Element::fromJSON(exp_result_json))
            << "Expected result JSON is invalid, test is broken" << exp_result_json;

        ASSERT_TRUE(exp_args->getType() == Element::map)
            << "Expected args is not a map, test is broken: " << exp_result_json;

        // Fetch "arguments" from the actual response
        ConstElementPtr actual_args = rsp->get("arguments");
        ASSERT_TRUE(actual_args && actual_args->getType() == Element::map)
                << "'arguments' missing or not a map " << toJSON(rsp);

        // If we expect nothing and nothing is what we got, we're done.
        if (exp_args->size() == 0) {
            ASSERT_TRUE(actual_args->size() == 0)
                << "Actual args should be empty:" << toJSON(actual_args);
            return;
        }

        // Fetch "result-set" from the expected arguments
        ConstElementPtr exp_result_set = exp_args->get("result-set");
        ASSERT_TRUE(exp_result_set && (exp_result_set->getType() == Element::map))
            << "Expected 'result-set' missing or not map\n" << toJSON(exp_args);

        // Fetch "result-set" from the actual arguments
        ConstElementPtr actual_result_set = actual_args->get("result-set");
        ASSERT_TRUE(actual_result_set && (actual_result_set->getType() == Element::map))
            << "Actual 'result-set' missing or not map\n" << toJSON(actual_args);

        // Compare the actual and expected "columns"
        ConstElementPtr exp = exp_result_set->get("columns");
        ASSERT_TRUE(exp && exp->getType() == Element::list)
            << "Expected 'columns' is missing or not list, test is broken"
            << toJSON(exp_result_set);

        ConstElementPtr actual = actual_result_set->get("columns");
        ASSERT_TRUE(actual && (actual->getType() == Element::list))
            << "Actual 'columns' is missing or not list"
            << toJSON(actual_result_set);

        ASSERT_TRUE(*exp == *actual) << "Result set columns are wrong\n"
                << "Expected:\n" << toJSON(exp)
                << "\nActual:\n" << toJSON(actual);

        // Compare the actual and expected "rows"
        exp = exp_result_set->get("rows");
        ASSERT_TRUE(exp && (exp->getType() == Element::list))
                << "Expected 'rows' is missing or not a list, test is broken";

        actual = actual_result_set->get("rows");
        ASSERT_TRUE(actual && (actual->getType() == Element::list))
                << "Actual 'rows' is missing or not a list"
                << toJSON(actual_result_set);

        ASSERT_TRUE(*exp == *actual) << "Result set rows are wrong\n"
                << "Expected:\n" << toJSON(exp)
                << "\nActual:\n" << toJSON(actual);

        // Make sure timestamp is present and appears valid
        actual = actual_result_set->get("timestamp");
        ASSERT_TRUE (actual && (actual->getType() == Element::string))
                << "Actual result-set timestamp is missing?"
                << toJSON(rsp);

        // We expect it to be the same or later than the test start time
        ptime timestamp = strToPtime(actual->stringValue());
        EXPECT_TRUE(timestamp >= start_time_)
                    << "Actual timestamp is wrong?" << actual->stringValue();
    }

    /// @brief Compares the status in the given parse result to a given value.
    ///
    /// @param answer Element set containing an integer response and string
    /// comment.
    /// @param exp_status is an integer against which to compare the status.
    /// @param exp_txt is expected text (not checked if "")
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

    /// @brief Loads the library specified by lib_name_
    void loadLib() {
        if (libraries_.empty()) {
            data::ElementPtr params = data::Element::createMap();
            addLib(lib_name_, params);
        }
        EXPECT_NO_THROW(loadLibs());
    }

    /// @brief Test checks if specified commands are provided by the library.
    ///
    /// @param cms a vector of string with command names
    void testCommands(const std::vector<string> cmds) {

        // The commands should not be registered yet.
        for (auto cmd = cmds.begin(); cmd != cmds.end(); ++cmd) {
            checkCommandRegistered(*cmd, false);
        }

        loadLib();

        // The commands should be available after library was loaded.
        for (auto cmd = cmds.begin(); cmd != cmds.end(); ++cmd) {
            checkCommandRegistered(*cmd, true);
        }

        unloadLibs();

        // and the commands should be gone now.
        for (auto cmd = cmds.begin(); cmd != cmds.end(); ++cmd) {
            checkCommandRegistered(*cmd, false);
        }

    }

    // Check that the library can be loaded and unloaded multiple times.
    void testMultipleLoads() {
        EXPECT_NO_THROW(loadLib());
        EXPECT_NO_THROW(unloadLibs());

        EXPECT_NO_THROW(loadLib());
        EXPECT_NO_THROW(unloadLibs());

        EXPECT_NO_THROW(loadLib());
        EXPECT_NO_THROW(unloadLibs());

        EXPECT_NO_THROW(loadLib());
        EXPECT_NO_THROW(unloadLibs());
    }

    std::string toJSON(ConstElementPtr element) {
        std::stringstream os;
        element->toJSON(os);
        return (os.str());
    }

    /// @brief Converts a string into a boost::posix_time::ptime
    ///
    /// The expected format of the input string is:
    ///
    ///    "%Y-%m-%d %H:%M:%S"
    ///
    /// Example: "2018-04-21 15:03:37"
    ///
    /// Any content beyond this length is ignored.
    ///
    ///  We're doing it this way because boost's function, time_from_string(),
    ///  is part of their date/time library which is not header only.
    ///
    /// @param timestamp string to convert into a ptime
    /// @throw BadValue if the string cannot be converted into a ptime
    boost::posix_time::ptime strToPtime(const std::string& timestamp) {
        struct tm tm_result;

        if (!strptime(timestamp.c_str(), "%Y-%m-%d %H:%M:%S", &tm_result)) {
            isc_throw(BadValue, "cannot convert timestamp string: " << timestamp);
        }

        return (ptime_from_tm(tm_result));
    }

    /// List of libraries to be/being loaded (usually just one)
    HookLibsCollection libraries_;

    /// Path to the library filename
    std::string lib_name_;

    /// @brief Holds the time the test started
    boost::posix_time::ptime start_time_;
};

/// @brief Class dedicated to testing lease_cmds library.
///
/// Provides convenience methods for loading, testing all commands and
/// unloading the lease_cmds library.
/// @todo This class should really be separated from loading and unloading
/// the library so implementation classes are tested more directly.
class StatCmdsTest : public LibLoadTest {
public:

    /// @brief Constructor
    ///
    /// Sets the library filename and clears the lease manager pointer.
    /// Also ensured there is no lease manager leftovers from previous
    /// test.
    StatCmdsTest()
        :LibLoadTest(STAT_CMDS_LIB_SO), hwaddr_({10,20,30,40,50,00}),
         duid_({10,20,30,40,50,60,70,00}) {
        LeaseMgrFactory::destroy();
        lmptr_ = 0;
    }

    /// @brief Destructor
    ///
    /// Removes library (if any), destroys lease manager (if any).
    virtual ~StatCmdsTest() {
        // destroys lease manager first because the other order triggers
        // a clang/boost bug
        LeaseMgrFactory::destroy();
        unloadLibs();
        lmptr_ = 0;
    }

    /// @brief Initializes lease manager for v4 operation
    ///
    /// Creates a lease manager (memfile, trimmed down to keep everything in memory
    /// only) and adds five subnets to the configuration.
    void initLeaseMgr4() {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false universe=4");

        lmptr_ = &(LeaseMgrFactory::instance());
        ASSERT_TRUE(lmptr_);

        CfgMgr& cfg_mgr = CfgMgr::instance();
        CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();

        Subnet4Ptr subnet;
        Pool4Ptr pool;

        subnet.reset(new Subnet4(IOAddress("192.0.1.0"), 24, 1, 2, 3, 10));
        pool.reset(new Pool4(IOAddress("192.0.1.0"), 24));
        subnet->addPool(pool);
        subnets->add(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.2.0"), 28, 1, 2, 3, 20));
        pool.reset(new Pool4(IOAddress("192.0.2.0"), 28));
        subnet->addPool(pool);
        subnets->add(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 1, 2, 3, 30));
        pool.reset(new Pool4(IOAddress("192.0.3.0"), 24));
        subnet->addPool(pool);
        subnets->add(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.4.0"), 28, 1, 2, 3, 40));
        pool.reset(new Pool4(IOAddress("192.0.4.0"), 28));
        subnet->addPool(pool);
        subnets->add(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.5.0"), 24, 1, 2, 3, 50));
        pool.reset(new Pool4(IOAddress("192.0.5.0"), 24));
        subnet->addPool(pool);
        subnets->add(subnet);

        cfg_mgr.commit();

        // Subnet 10
        // 300 cumulative, 2 assigned, 3 declined,  1 expired
        setSubnetStat(10, "cumulative-assigned-addresses", 300);
        addLease4("192.0.1.1", 10);
        addLease4("192.0.1.2", 10, Lease::STATE_DECLINED);
        addLease4("192.0.1.3", 10, Lease::STATE_DECLINED);
        addLease4("192.0.1.4", 10, Lease::STATE_DECLINED);
        addLease4("192.0.1.5", 10);
        addLease4("192.0.1.6", 10, Lease::STATE_EXPIRED_RECLAIMED);

        // Subnet 20
        // 10 cumulative, 3 assigned, 0 declined,  2 expired
        setSubnetStat(20, "cumulative-assigned-addresses", 10);
        addLease4("192.0.2.1", 20);
        addLease4("192.0.2.2", 20);
        addLease4("192.0.2.3", 20);
        addLease4("192.0.2.4", 20, Lease::STATE_EXPIRED_RECLAIMED);
        addLease4("192.0.2.5", 20, Lease::STATE_EXPIRED_RECLAIMED);

        // Subnet 30 no leases

        // Subnet 40, 4 cumulative, 4 assigned
        setSubnetStat(40, "cumulative-assigned-addresses", 4);
        addLease4("192.0.4.1", 40);
        addLease4("192.0.4.2", 40);
        addLease4("192.0.4.3", 40);
        addLease4("192.0.4.4", 40);

        // Subnet 50, 2 cumulative, 1 assigned, 1 declined
        setSubnetStat(50, "cumulative-assigned-addresses", 2);
        addLease4("192.0.5.1", 50);
        addLease4("192.0.5.2", 50, Lease::STATE_DECLINED);
    }

    /// @brief Initializes lease manager for v6 operation
    ///
    /// Creates a lease manager (memfile, trimmed down to keep everything in
    /// memory only) and adds five subnets to the configuration.
    void initLeaseMgr6() {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false universe=6");

        lmptr_ = &(LeaseMgrFactory::instance());
        ASSERT_TRUE(lmptr_);

        CfgMgr& cfg_mgr = CfgMgr::instance();
        CfgSubnets6Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();

        Subnet6Ptr subnet;
        Pool6Ptr pool;

        subnet.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4, 10));
        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 112));
        subnet->addPool(pool);
        subnets->add(subnet);

        subnet.reset(new Subnet6(IOAddress("2001:db8:2::"), 64, 1, 2, 3, 4, 20));
        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:2::"), 104));
        subnet->addPool(pool);
        subnets->add(subnet);

        subnet.reset(new Subnet6(IOAddress("2001:db8:3::"), 64, 1, 2, 3, 4, 30));
        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:3::"), 124));
        subnet->addPool(pool);
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("3001::"), 96, 112));
        subnet->addPool(pool);
        subnets->add(subnet);

        subnet.reset(new Subnet6(IOAddress("2001:db8:4::"), 64, 1, 2, 3, 4, 40));
        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:4::"), 104));
        subnet->addPool(pool);
        subnets->add(subnet);

        // Subnet 50 is prefix only
        subnet.reset(new Subnet6(IOAddress("2001:db8:5::"), 64, 1, 2, 3, 4, 50));
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("5001::"), 96, 112));
        subnet->addPool(pool);
        subnets->add(subnet);

        cfg_mgr.commit();

        // Subnet 10: 10000 cumulative NAs, 2 assigned, 3 declined, 1 expired
        setSubnetStat(10, "cumulative-assigned-nas", 10000);
        addLease6("2001:db8:1::1", 10);
        addLease6("2001:db8:1::2", 10);
        addLease6("2001:db8:1::3", 10, Lease::STATE_DECLINED);
        addLease6("2001:db8:1::4", 10, Lease::STATE_DECLINED);
        addLease6("2001:db8:1::5", 10, Lease::STATE_DECLINED);
        addLease6("2001:db8:1::6", 10, Lease::STATE_EXPIRED_RECLAIMED);

        // Subnet 20: 10 cumulative NAs, 3 assigned
        setSubnetStat(20, "cumulative-assigned-nas", 10);
        addLease6("2001:db8:2::1", 20);
        addLease6("2001:db8:2::2", 20);
        addLease6("2001:db8:2::3", 20);

        // Subnet 30: 2 cumulative NAs, 1 assigned, 1 declined,
        // 4 cumulative PDs, 3 assigned
        setSubnetStat(30, "cumulative-assigned-nas", 2);
        addLease6("2001:db8:3::1", 30);
        addLease6("2001:db8:3::2", 30, Lease::STATE_DECLINED);
        setSubnetStat(30, "cumulative-assigned-pds", 4);
        addPrefix("3001::1:0", 112, 30);
        addPrefix("3001::2:0", 112, 30);
        addPrefix("3001::3:0", 112, 30);

        // Subnet 40: no leases

        // Subnet 50: 1000 cumulative PDs, 2 assigned
        setSubnetStat(50, "cumulative-assigned-pds", 1000);
        addPrefix("5001::1:0", 112, 50);
        addPrefix("5001::2:0", 112, 50);
    }

    /// @brief Creates an IPv4 lease
    ///
    /// Lease parameters: valid lifetime = 3600, cltt = 12345678,
    /// fqdn-fwd = false,fqdn-rev = true, hostname = myhost.example.com
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param state lease state
    void addLease4(const std::string& ip_address, const SubnetID& subnet_id,
                   const int state = Lease::STATE_DEFAULT) {
        Lease4Ptr lease(new Lease4());

        lease->addr_ = IOAddress(ip_address);

        ++hwaddr_[5];

        // Set other parameters.  For historical reasons, address 0 is not used.
        lease->hwaddr_.reset(new HWAddr(hwaddr_, HTYPE_ETHER));
        lease->valid_lft_ = 3600;
        lease->cltt_ = 12345678;
        lease->subnet_id_ = subnet_id;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "myhost.example.com.";
        lease->state_ = state;

        ASSERT_NO_THROW(lmptr_->addLease(lease))
                        << "cannot add lease4: " << ip_address
                        << " subnet: " << subnet_id;
    }

    /// @brief Creates an IPv6 lease
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param state lease state of the lease, defaults to STATE_DEFAULT
    /// @param lease_type type of the lease, defaults to TYPE_NA
    /// @param prefix_len prefix length of the lease, defaults to 128
    void addLease6(const std::string& ip_address, const SubnetID& subnet_id,
                   const int state = Lease::STATE_DEFAULT,
                   const Lease::Type& lease_type = Lease::TYPE_NA,
                   const int prefix_len = 128) {
        Lease6Ptr lease(new Lease6());

        ++duid_[7];

        lease->addr_ = IOAddress(ip_address);
        lease->type_ = lease_type;
        lease->prefixlen_ = prefix_len;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(duid_));
        lease->preferred_lft_ = 1800;
        lease->valid_lft_ = 3600;
        lease->cltt_ = 12345678;
        lease->subnet_id_ = subnet_id;
        lease->state_ = state;

        ASSERT_NO_THROW(lmptr_->addLease(lease))
                        << "cannot add lease6: " << lease->toText();
        }

    /// @brief Creates an IPv6 PD lease
    ///
    /// @param prefix IP address prefix for the lease.
    /// @param prefix_len prefix length of the lease
    /// @param subnet_id subnet identifier
    /// @param state lease state of the lease, defaults to STATE_DEFAULT
    void addPrefix(const std::string& prefix, const int prefix_len,
                   const SubnetID& subnet_id,
                   const int state = Lease::STATE_DEFAULT) {
        addLease6(prefix, subnet_id, state, Lease::TYPE_PD, prefix_len);
    }

    /// @brief Creates a statistic
    ///
    /// @param subnet_id subnet identifier
    /// @param name statistic name
    /// @param value statistic value
    void setSubnetStat(const SubnetID& subnet_id, const std::string& name,
                       int64_t value) {
        StatsMgr& stats_mgr = StatsMgr::instance();
        const std::string& stats_name =
            stats_mgr.generateName("subnet", subnet_id, name);
        stats_mgr.setValue(stats_name, value);
    }

    /// @brief Pointer to the lease manager
    LeaseMgr* lmptr_;

    /// @brief Holds the hardware address for creating v4 leases
    vector<uint8_t> hwaddr_;

    /// @brief Holds the DUID for creating v6 leases
    vector<uint8_t> duid_;
};

// Simple test that checks the library really registers the commands.
TEST_F(StatCmdsTest, commands) {

    vector<string> cmds = { "stat-lease4-get",
                            "stat-lease6-get" };
    testCommands(cmds);
}

// Check that the library can be loaded and unloaded multiple times.
TEST_F(StatCmdsTest, multipleLoads) {
    testMultipleLoads();
}

struct TestScenario {
    std::string description_;
    std::string command_txt_;
    std::string exp_response_;
    std::string exp_result_json;
};

// Verifies detection of invalid v4 input parameters.
TEST_F(StatCmdsTest, StatLease4GetBadParams) {
    // Initialize lease manager
    initLeaseMgr4();

    std::vector<TestScenario> tests = {
        {
        "arguments is not a map",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": \"not a map\"\n"
        "}",
        "'arguments' parameter is not a map"
        },
        {
        "subnet-id 0",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0\n"
        "    }\n"
        "}",
        "'subnet-id' parameter must be > 0"
        },

        {
        "subnet-id -1",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}",
        "'subnet-id' parameter must be > 0"
        },
        {
        "subnet-id string",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": \"boo\"\n"
        "    }\n"
        "}",
        "'subnet-id' parameter is not integer"
        },
        {
        "subnet-range not a map",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": -1\n"
        "    }\n"
        "}",
        "subnet-range parameter is not a map"
        },
        {
        "subnet-range empty",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "       }\n"
        "    }\n"
        "}",
        "'first-subnet-id' parameter missing or not an integer"
        },
        {
        "first-subnet-id string",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": \"boo\"\n"
        "       }\n"
        "    }\n"
        "}",
        "'first-subnet-id' parameter missing or not an integer"
        },
        {
        "first-subnet-id < 0",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": -77\n"
        "       }\n"
        "    }\n"
        "}",
        "'first-subnet-id' parameter must be > 0"
        },
        {
        "last-subnet-id missing",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' parameter missing or not an integer"
        },
        {
        "last-subnet-id string",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10,\n"
        "           \"last-subnet-id\": \"boo\"\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' parameter missing or not an integer"
        },
        {
        "last-subnet-id < 0",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10,\n"
        "           \"last-subnet-id\": -1\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' parameter must be > 0"
        },
        {
        "invalid range",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 50,\n"
        "           \"last-subnet-id\": 2\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' must be greater than 'first-subnet-id'"
        },
        {
        "Subnet-Range: all in the middle",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-id\": 10,\n"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 20,"
        "           \"last-subnet-id\": 40"
        "       }\n"
        "    }\n"
        "}",
        "cannot specify both subnet-id and subnet-range"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_ERROR,(*test).exp_response_);
        }
    }
}

// Verifies result content for valid v4 statistic commands.
// These test scenarios are all valid, and not expected to throw.
TEST_F(StatCmdsTest, statLease4GetValid) {

    // Initialize lease manager.
    initLeaseMgr4();

    // Note timestamp actual values are not important but are included
    // for clarity.
    std::vector<TestScenario> tests = {
        {
        "ALL-Subnets",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}",
        "stat-lease4-get[all subnets]: 5 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 10, 256, 300, 2, 3 ],\n"
        "       [ 20, 16, 10, 3, 0 ],\n"
        "       [ 30, 256, 0, 0, 0 ],\n"
        "       [ 40, 16, 4, 4, 0 ],\n"
        "       [ 50, 256, 2, 1, 1 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "ALL-Subnets - arguments omitted",
        "{\n"
        "    \"command\": \"stat-lease4-get\"\n"
        "}",
        "stat-lease4-get[all subnets]: 5 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 10, 256, 300, 2, 3 ],\n"
        "       [ 20, 16, 10, 3, 0 ],\n"
        "       [ 30, 256, 0, 0, 0 ],\n"
        "       [ 40, 16, 4, 4, 0 ],\n"
        "       [ 50, 256, 2, 1, 1 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Single-Subnet",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-id\": 20"
        "    }\n"
        "}",
        "stat-lease4-get[subnet-id=20]: 1 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 20, 16, 10, 3, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range: beginning to middle",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10,"
        "           \"last-subnet-id\": 30"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease4-get[subnets 10 through 30]: 3 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 10, 256, 300, 2, 3 ],\n"
        "       [ 20, 16, 10, 3, 0 ],\n"
        "       [ 30, 256, 0, 0, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range: all in the middle",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 20,"
        "           \"last-subnet-id\": 40"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease4-get[subnets 20 through 40]: 3 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 20, 16, 10, 3, 0 ],\n"
        "       [ 30, 256, 0, 0, 0 ],\n"
        "       [ 40, 16, 4, 4, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range: middle to end",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 30,"
        "           \"last-subnet-id\": 50"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease4-get[subnets 30 through 50]: 3 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 30, 256, 0, 0, 0 ],\n"
        "       [ 40, 16, 4, 4, 0 ],\n"
        "       [ 50, 256, 2, 1, 1 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range: fuzzy range",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 25,"
        "           \"last-subnet-id\": 45"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease4-get[subnets 25 through 45]: 2 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 30, 256, 0, 0, 0 ],\n"
        "       [ 40, 16, 4, 4, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_SUCCESS,
                    (*test).exp_response_, (*test).exp_result_json);
        }
    }

}

// Verifies result content for valid v4 statistic commands that
// result in no matching subnets.
TEST_F(StatCmdsTest, statLease4GetSubnetsNotFound) {

    // Initialize lease manager.
    initLeaseMgr4();

    // Note timestamp actual values are not important but are included
    // for clarity.
    std::vector<TestScenario> tests = {
        {
        "Single-Subnet, undefined subnet",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-id\": 88"
        "    }\n"
        "}",
        "stat-lease4-get[subnet-id=88]: no matching data, subnet-id: 88 does not exist",
        "{}"
        },
        {
        "Subnet-Range: empty range below",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 2,"
        "           \"last-subnet-id\": 6"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease4-get[subnets 2 through 6]: no matching data, selected ID range: 2 through 6 includes no known subnets",
        "{}"
        },
        {
        "Subnet-Range: empty range above",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 200,"
        "           \"last-subnet-id\": 600"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease4-get[subnets 200 through 600]: no matching data, selected ID range: 200 through 600 includes no known subnets",
        "{}"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_EMPTY,
                    (*test).exp_response_, (*test).exp_result_json);
        }
    }

}

// Verifies detection of invalid v6 input parameters.
TEST_F(StatCmdsTest, StatLease6GetBadParams) {
    // Initialize lease manager
    initLeaseMgr6();

    std::vector<TestScenario> tests = {
        {
        "arguments not a map",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": \"not a map\"\n"
        "}",
        "'arguments' parameter is not a map"
        },
        {
        "subnet-id 0",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0\n"
        "    }\n"
        "}",
        "'subnet-id' parameter must be > 0"
        },

        {
        "subnet-id -1",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": -1\n"
        "    }\n"
        "}",
        "'subnet-id' parameter must be > 0"
        },
        {
        "subnet-id string",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": \"boo\"\n"
        "    }\n"
        "}",
        "'subnet-id' parameter is not integer"
        },
        {
        "subnet-range not a map",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": -1\n"
        "    }\n"
        "}",
        "subnet-range parameter is not a map"
        },
        {
        "subnet-range empty",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "       }\n"
        "    }\n"
        "}",
        "'first-subnet-id' parameter missing or not an integer"
        },
        {
        "first-subnet-id string",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": \"boo\"\n"
        "       }\n"
        "    }\n"
        "}",
        "'first-subnet-id' parameter missing or not an integer"
        },
        {
        "first-subnet-id < 0",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": -77\n"
        "       }\n"
        "    }\n"
        "}",
        "'first-subnet-id' parameter must be > 0"
        },
        {
        "last-subnet-id missing",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' parameter missing or not an integer"
        },
        {
        "last-subnet-id string",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10,\n"
        "           \"last-subnet-id\": \"boo\"\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' parameter missing or not an integer"
        },
        {
        "last-subnet-id < 0",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10,\n"
        "           \"last-subnet-id\": -1\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' parameter must be > 0"
        },
        {
        "invalid range",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-range\": {\n"
        "           \"first-subnet-id\": 50,\n"
        "           \"last-subnet-id\": 2\n"
        "       }\n"
        "    }\n"
        "}",
        "'last-subnet-id' must be greater than 'first-subnet-id'"
        },
        {
        "both subnet and range",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-id\": 10,\n"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 20,"
        "           \"last-subnet-id\": 40"
        "       }\n"
        "    }\n"
        "}",
        "cannot specify both subnet-id and subnet-range"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_ERROR,(*test).exp_response_);
        }
    }
}

// Verifies result content for valid v6 statistic commands.
// These test scenarios are all valid, and not expected to throw.
TEST_F(StatCmdsTest, statLease6GetValid) {

    // Initialize lease manager
    initLeaseMgr6();

    // Note timestamp actual values are not important but are included
    // for clarity.
    std::vector<TestScenario> tests = {
        {
        "ALL-Subnets6",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}",
        "stat-lease6-get[all subnets]: 5 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 10, 65536, 10000, 2, 3, 0, 0, 0 ],\n"
        "       [ 20, 16777216, 10, 3, 0, 0, 0, 0 ],\n"
        "       [ 30, 16, 2, 1, 1, 65536, 4, 3 ],\n"
        "       [ 40, 16777216, 0, 0, 0, 0, 0, 0 ],\n"
        "       [ 50, 0, 0, 0, 0, 65536, 1000, 2 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "ALL-Subnets6 arguments omitted",
        "{\n"
        "    \"command\": \"stat-lease6-get\"\n"
        "}",
        "stat-lease6-get[all subnets]: 5 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 10, 65536, 10000, 2, 3, 0, 0, 0 ],\n"
        "       [ 20, 16777216, 10, 3, 0, 0, 0, 0 ],\n"
        "       [ 30, 16, 2, 1, 1, 65536, 4, 3 ],\n"
        "       [ 40, 16777216, 0, 0, 0, 0, 0, 0 ],\n"
        "       [ 50, 0, 0, 0, 0, 65536, 1000, 2 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Single-Subnet6",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-id\": 20"
        "    }\n"
        "}",
        "stat-lease6-get[subnet-id=20]: 1 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 20, 16777216, 10, 3, 0, 0, 0, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range6: beginning to middle",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 10,"
        "           \"last-subnet-id\": 30"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease6-get[subnets 10 through 30]: 3 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 10, 65536, 10000, 2, 3, 0, 0, 0 ],\n"
        "       [ 20, 16777216, 10, 3, 0, 0, 0, 0 ],\n"
        "       [ 30, 16, 2, 1, 1, 65536, 4, 3 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range6: all in the middle",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 20,"
        "           \"last-subnet-id\": 40"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease6-get[subnets 20 through 40]: 3 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 20, 16777216, 10, 3, 0, 0, 0, 0 ],\n"
        "       [ 30, 16, 2, 1, 1, 65536, 4, 3 ],\n"
        "       [ 40, 16777216, 0, 0, 0, 0, 0, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range6: middle to end",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 30,"
        "           \"last-subnet-id\": 50"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease6-get[subnets 30 through 50]: 3 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 30, 16, 2, 1, 1, 65536, 4, 3 ],\n"
        "       [ 40, 16777216, 0, 0, 0, 0, 0, 0 ],\n"
        "       [ 50, 0, 0, 0, 0, 65536, 1000, 2 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        },
        {
        "Subnet-Range6: fuzzy range",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 25,"
        "           \"last-subnet-id\": 45"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease6-get[subnets 25 through 45]: 2 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 30, 16, 2, 1, 1, 65536, 4, 3 ],\n"
        "       [ 40, 16777216, 0, 0, 0, 0, 0, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_SUCCESS,
                    (*test).exp_response_, (*test).exp_result_json);
        }
    }

}

// Verifies result content for valid v6 statistic commands that
// result in no matching subnets.
TEST_F(StatCmdsTest, statLease6GetSubnetsNotFound) {

    // Initialize lease manager
    initLeaseMgr6();

    // Note timestamp actual values are not important but are included
    // for clarity.
    std::vector<TestScenario> tests = {
        {
        "Single-Subnet6, undefined subnet",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-id\": 88"
        "    }\n"
        "}",
        "stat-lease6-get[subnet-id=88]: no matching data, subnet-id: 88 does not exist",
        "{}"
        },
        {
        "Subnet-Range6: empty range below",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 2,"
        "           \"last-subnet-id\": 6"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease6-get[subnets 2 through 6]: no matching data, selected ID range: 2 through 6 includes no known subnets",
        "{}"
        },
        {
        "Subnet-Range6: empty range above",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "       \"subnet-range\": {\n"
        "           \"first-subnet-id\": 200,"
        "           \"last-subnet-id\": 600"
        "       }\n"
        "    }\n"
        "}",
        "stat-lease6-get[subnets 200 through 600]: no matching data, selected ID range: 200 through 600 includes no known subnets",
        "{}"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_EMPTY,
                    (*test).exp_response_, (*test).exp_result_json);
        }
    }
}

// Verifies that statistics for v4 subnets which no longer
// exist are dropped from the result sets.
TEST_F(StatCmdsTest, statLease4OrphanedStats) {

    // Initialize lease manager.
    initLeaseMgr4();

    // Now remove subnets 10, 30, and 50 thereby orphaning their leases.
    CfgMgr& cfg_mgr = CfgMgr::instance();
    CfgSubnets4Ptr subnets = cfg_mgr.getCurrentCfg()->getCfgSubnets4();
    ASSERT_NO_THROW_LOG(subnets->del(10));
    ASSERT_NO_THROW_LOG(subnets->del(30));
    ASSERT_NO_THROW_LOG(subnets->del(50));
    cfg_mgr.commit();

    // Note timestamp actual values are not important but are included
    // for clarity.
    std::vector<TestScenario> tests = {
        {
        "ALL-Subnets",
        "{\n"
        "    \"command\": \"stat-lease4-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}",
        "stat-lease4-get[all subnets]: 2 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-addresses\",\n"
        "        \"cumulative-assigned-addresses\",\n"
        "        \"assigned-addresses\", \"declined-addresses\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 20, 16, 0, 3, 0 ],\n"
        "       [ 40, 16, 0, 4, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_SUCCESS,
                    (*test).exp_response_, (*test).exp_result_json);
        }
    }
}

// Verifies that statistics for v6 subnets which no longer
// exist are dropped from the result sets.
TEST_F(StatCmdsTest, statLease6OrphanedStats) {

    // Initialize lease manager.
    initLeaseMgr6();

    // Now remove subnets 10, 30, and 50 thereby orphaning their leases.
    CfgMgr& cfg_mgr = CfgMgr::instance();
    CfgSubnets6Ptr subnets = cfg_mgr.getCurrentCfg()->getCfgSubnets6();
    ASSERT_NO_THROW_LOG(subnets->del(10));
    ASSERT_NO_THROW_LOG(subnets->del(30));
    ASSERT_NO_THROW_LOG(subnets->del(50));
    cfg_mgr.commit();

    // Note timestamp actual values are not important but are included
    // for clarity.
    std::vector<TestScenario> tests = {
        {
        "ALL-Subnets",
        "{\n"
        "    \"command\": \"stat-lease6-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}",
        "stat-lease6-get[all subnets]: 2 rows found",
        "{\n"
        "\"result-set\": {\n"
        "   \"columns\": [\n"
        "        \"subnet-id\", \"total-nas\",\n"
        "        \"cumulative-assigned-nas\", \"assigned-nas\",\n"
        "        \"declined-nas\", \"total-pds\",\n"
        "        \"cumulative-assigned-pds\", \"assigned-pds\"\n"
        "   ],\n"
        "   \"rows\": [\n"
        "       [ 20, 16777216, 0, 3, 0, 0, 0, 0 ],\n"
        "       [ 40, 16777216, 0, 0, 0, 0, 0, 0 ]\n"
        "   ],\n"
        "   \"timestamp\": \"2018-05-04 15:03:37.000000\" }\n"
        "}\n"
        }
    };

    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
        SCOPED_TRACE((*test).description_);
        testCommand((*test).command_txt_, CONTROL_RESULT_SUCCESS,
                    (*test).exp_response_, (*test).exp_result_json);
        }
    }
}

} // end of anonymous namespace

