// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>
#include <config/command_mgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/resource_handler.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <lease_cmds.h>
#include <lease_cmds_unittest.h>
#include <stats/stats_mgr.h>
#include <util/filesystem.h>
#include <testutils/user_context_utils.h>
#include <testutils/multi_threading_utils.h>
#include <testutils/gtest_utils.h>
#include <dhcpsrv/testutils/sflqtest_lease_mgr.h>
#include <dhcpsrv/sflq_allocator.h>

#include <gtest/gtest.h>

#include <errno.h>
#include <set>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::test;
using namespace isc::lease_cmds;
using namespace isc::dhcp::test;

namespace {

#define SCOPED_LINE(line) \
    std::stringstream ss; \
    ss << "Scenario at line: " << line; \
    SCOPED_TRACE(ss.str());

/// @brief Structure for describing a bad command parameters scenario.
struct BadParamScenario {
    /// @brief Source line number (i.e. __FILE__).
    int line_;

    /// @brief JSON map of arguments.
    std::string args_;

    /// @brief Expected error response text.
    std::string exp_rsp_;
    };


/// @brief Class dedicated to testing SFLQ commands in the lease_cmds library.
///
/// These tests use the dhcp::test::SflqTestLeaseMgr for tests as Memfile
/// does not support SFLQ.
///
/// Provides convenience methods for loading, testing the SLFQ commands.
class SflqCmdsTest : public LibLoadTest {
public:
    /// @brief Pointer to the lease manager
    isc::dhcp::LeaseMgr* lmptr_;

    /// @brief Constructor
    ///
    /// Sets the library filename and clears the lease manager pointer.
    /// Also ensured there is no lease manager leftovers from previous
    /// test.
    SflqCmdsTest(uint16_t family)
        : LibLoadTest(LIBDHCP_LEASE_CMDS_SO) {
        setFamily(family);
        isc::util::file::PathChecker::enableEnforcement(true);
    }

    /// @brief Pre-test setup.
    ///
    /// Installs the lease manager factory, creates a manager instance.
    virtual void SetUp() {
        LeaseMgrFactory::registerFactory("sflqtest", dhcp::test::SflqTestLeaseMgr::factory);
        if (isc::dhcp::CfgMgr::instance().getFamily() == AF_INET) {
            ASSERT_NO_THROW_LOG(LeaseMgrFactory::create("type=sflqtest universe=4"));
        } else {
            ASSERT_NO_THROW_LOG(LeaseMgrFactory::create("type=sflqtest universe=6"));
        }

        ASSERT_TRUE(LeaseMgrFactory::haveInstance());
        ASSERT_EQ(LeaseMgrFactory::instance().getType(), "sflqtest");
        // initSubnet4();
        SharedFlqAllocator::setInUse(false);
    }

    /// @brief Destructor
    ///
    /// Removes library (if any), destroys lease manager (if any).
    virtual ~SflqCmdsTest() {
        // destroys lease manager first because the other order triggers
        // a clang/boost bug
        isc::dhcp::LeaseMgrFactory::destroy();
        unloadLibs();
        lmptr_ = 0;
        isc::util::file::PathChecker::enableEnforcement(true);
    }

    /// @brief Creates JSON text command with arguments
    ///
    /// @param command command name
    /// @param args Element map containing the command arguments. May be empty.
    ///
    /// @return Command with arguments as JSON text.
    std::string buildCommand(const std::string& command,
                             ElementPtr args = Element::createMap()) const {
        std::ostringstream oss;
        oss << "{ \"command\": \"" << command << "\", \"arguments\": " << *args << "}";
        return (oss.str());
    }

    /// Compare two SflqPoolInfo structures for equality.
    ///
    /// All members are compared for equality except the timestamps. Those
    /// are considered correct if the lhs timestamps are greater than or
    /// equal to their rhs counterparts.  Asserts if they are not "equal".
    ///
    /// @param lhs left-side instance to compare
    /// @param rhs left-side instance to compare
    /// @param lineno source line of invocation (pass in __LINE__)
    void checkPoolInfos(const SflqPoolInfo& lhs, const SflqPoolInfo& rhs, int lineno) {
        ASSERT_TRUE(lhs.lease_type_ == rhs.lease_type_ &&
                    lhs.start_address_  == rhs.start_address_ &&
                    lhs.end_address_ == rhs.end_address_ &&
                    lhs.delegated_len_ == rhs.delegated_len_ &&
                    lhs.subnet_id_ == rhs.subnet_id_ &&
                    lhs.free_leases_ == rhs.free_leases_ &&
                    lhs.created_ts_ >= rhs.created_ts_ &&
                    lhs.modified_ts_ >= rhs.modified_ts_
                    )
            << "Pools don't match at line " << lineno << std::endl
            << "lhs: " << *lhs.toElement() << std::endl
            << "rhs: " << *rhs.toElement() << std::endl;
    }

    /// @brief Extracts a list of SflqPoolnfos from a command response.
    ///
    /// @param cmd_rsp command response to extract from
    /// @return list of SflqPoolInfos
    /// @throw BadValue if the response is malformed
    SflqPoolInfoCollectionPtr extractPools(ConstElementPtr cmd_rsp) {
        if (!cmd_rsp) {
            isc_throw(BadValue, "cmd_rsp is empty");
        }

        ConstElementPtr rsp_args = cmd_rsp->get("arguments");
        if (!rsp_args || rsp_args->getType() != Element::map) {
            isc_throw(BadValue, "rsp_args missing or not a map");
        }

        ConstElementPtr pools_elem = rsp_args->get("pools");
        if (!pools_elem || pools_elem->getType() != Element::list) {
            isc_throw(BadValue, "pools missing or not a list");
        }

        auto family = isc::dhcp::CfgMgr::instance().getFamily();
        SflqPoolInfoCollectionPtr pool_infos(new SflqPoolInfoCollection());
        for (size_t i = 0; i < pools_elem->size(); ++i) {
            auto pool_elem = pools_elem->get(i);
            SflqPoolInfoPtr pi(new SflqPoolInfo());
            pi->start_address_ = SimpleParser::getAddress(pool_elem, "start-address");
            pi->end_address_ = SimpleParser::getAddress(pool_elem, "end-address");
            pi->subnet_id_ = SimpleParser::getInteger(pool_elem, "subnet-id");
            pi->lease_type_ = extractLeaseType(pool_elem, family);
            pi->delegated_len_ = SimpleParser::getInteger(pool_elem, "delegated-len");
            pi->free_leases_ = SimpleParser::getInteger(pool_elem, "free-leases");
            pi->created_ts_ = extractTimestamp(pool_elem, "created-ts");
            pi->modified_ts_ = extractTimestamp(pool_elem, "modified-ts");
            pool_infos->push_back(pi);
        }

        return (pool_infos);
    }

    /// @brief Extracts the value of "lease-type" from command parameters
    ///
    /// This function is used both for command parameters and unparsing
    /// JSON pool infos.
    ///
    /// @param params Element map containing the lease-type
    /// @param family protocol family (AF_INET or AF_INET6)
    /// @return Lease::Type found
    /// @throw BadValue if the parameter is missing or invalid
    Lease::Type extractLeaseType(ConstElementPtr& params, uint16_t family) {
        auto tmp = SimpleParser::getString(params, "lease-type");
        if (family == AF_INET) {
            if (tmp == "V4" || tmp == "3") {
                return (Lease::TYPE_V4);
            }

            isc_throw(BadValue, "invalid 'lease-type': " << tmp << " must be 'V4'");
        }

        if (tmp == "IA_NA" || tmp == "0") {
            return (Lease::TYPE_NA);
        } else if (tmp == "IA_PD" || tmp == "2") {
            return (Lease::TYPE_PD);
        }

        isc_throw(BadValue, "invalid V6 'lease-type': "
                  << tmp << ", valid values are IA_NA and IA_PD");
    }

    /// @brief Converts a string into a boost::posix_time::ptime
    ///
    ///  We're doing it this way because boost's function, time_from_string(),
    ///  is part of their date/time library which is not header only.
    ///
    /// @param params Element map containing the timestamp
    /// @param timestamp name of the timestamp element
    ///
    /// @throw BadValue if the timestamp is not found or the string
    /// cannot be converted into a ptime
    boost::posix_time::ptime extractTimestamp(ConstElementPtr& params,
                                              const std::string& name) {
        auto tmp = SimpleParser::getString(params, name);
        struct tm tm_result;
        if (!strptime(tmp.c_str(), "%Y-%m-%d %H:%M:%S", &tm_result)) {
            isc_throw(BadValue, "cannot convert timestamp string: " << tmp);
        }

        return (boost::posix_time::ptime_from_tm(tm_result));
    }
};

/// @brief Class dedicated to testing v4 SFLQ commands in the lease_cmds library.
///
/// These tests use the dhcp::test::SflqTestLeaseMgr for tests as Memfile
/// does not support SFLQ.
///
/// Provides convenience methods for loading, testing the SLFQ commands.
class SflqCmds4Test : public SflqCmdsTest {
public:

    /// @brief Constructor
    SflqCmds4Test()
        : SflqCmdsTest(AF_INET) {}

    /// @brief Destructor
    virtual ~SflqCmds4Test() {}

    /// @brief Exercises invalid parameter checks for sflq-pool4-create.
    void sflqPool4CreateBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool4-get-all.
    void sflqPool4GetAllBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool4-get-by-subnet.
    void sflqPool4GetBySubnetBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool4-get-by-range.
    void sflqPool4GetByRangeBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool4-del.
    void sflqPool4DelBadParams();

    /// @todo invalid arguments for get-by-subnet, get-by-range, and delete

    /// @brief Exercises all the V4 SFLQ commands.
    /// The intent is to verify that each command gets the arguments
    /// it expects, carries out the appropriate action, and returns
    /// the correct responses.
    void testSflqCommands();
};

void SflqCmds4Test::sflqPool4CreateBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'start-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10"
        )",
        "missing 'end-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20"
        )",
        "missing 'subnet-id' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::",
            "end-address" : "178.0.0.20",
            "subnet-id" : 1
        )",
        "invalid V4 range - start_address 3001::, end_address 178.0.0.20,"
        " must be V4 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.20",
            "end-address" : "178.0.0.10",
            "subnet-id" : 1
        )",
        "invalid V4 range - start_address 178.0.0.20, end_address 178.0.0.10,"
        " must be V4 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20",
            "subnet-id" : "bogus"
        )",
        "'subnet-id' parameter is not an integer"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20",
            "subnet-id" : 0
        )",
        "'subnet-id' must be greater than zero"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20",
            "subnet-id" : 0,
            "recreate" : 1
        )",
        "'recreate' parameter is not a boolean"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20",
            "subnet-id" : 0,
            "recreate" : true,
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    }};

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool4-create", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds4Test::sflqPool4GetAllBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"(
            "bogus" : "fluff"
        )",
        "command does not take any arguments"
    }};

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool4-get-all", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds4Test::sflqPool4GetBySubnetBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'subnet-id' parameter"
    },
    {
        __LINE__,
        R"(
            "subnet-id": "silly"
        )",
        "'subnet-id' parameter is not an integer"
    },
    {
        __LINE__,
        R"(
            "subnet-id": 1,
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    },
    {
        __LINE__,
        R"(
            "subnet-id": -1
        )",
        "'subnet-id' -1 is invalid, must be greater than zero"
        " and less than 4294967295"
    }
    };

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool4-get-by-subnet", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds4Test::sflqPool4GetByRangeBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'start-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10"
        )",
        "missing 'end-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::",
            "end-address" : "178.0.0.20"
        )",
        "invalid V4 range - start_address 3001::, end_address 178.0.0.20,"
        " must be V4 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.20",
            "end-address" : "178.0.0.10"
        )",
        "invalid V4 range - start_address 178.0.0.20, end_address 178.0.0.10,"
        " must be V4 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20",
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    }
    };

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool4-get-by-range", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds4Test::sflqPool4DelBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'start-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10"
        )",
        "missing 'end-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::",
            "end-address" : "178.0.0.20"
        )",
        "invalid V4 range - start_address 3001::, end_address 178.0.0.20,"
        " must be V4 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.20",
            "end-address" : "178.0.0.10"
        )",
        "invalid V4 range - start_address 178.0.0.20, end_address 178.0.0.10,"
        " must be V4 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20",
            "force" : "oops"
        )",
        "'force' parameter is not a boolean"
    },
    {
        __LINE__,
        R"(
            "start-address" : "178.0.0.10",
            "end-address" : "178.0.0.20",
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    }
    };

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool4-del", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void
SflqCmds4Test::testSflqCommands() {
    auto test_start = boost::posix_time::second_clock::local_time();

    // Fetching all pools should find none.
    auto command = buildCommand("sflq-pool4-get-all");
    testCommand(command, CONTROL_RESULT_EMPTY, "0 pool(s) found.");

    // Create three test pool infos.
    SflqPoolInfoCollection test_pools;
    SflqPoolInfoPtr pi;

    pi.reset(new SflqPoolInfo());
    pi->start_address_ = IOAddress("192.0.1.0");
    pi->end_address_ = IOAddress("192.0.1.2");
    pi->subnet_id_ = 1;
    pi->created_ts_ = test_start;
    pi->modified_ts_ = test_start;
    pi->free_leases_ = 3;
    test_pools.push_back(pi);

    pi.reset(new SflqPoolInfo());
    pi->start_address_ = IOAddress("192.0.2.0");
    pi->end_address_ = IOAddress("192.0.2.2");
    pi->subnet_id_ = 2;
    pi->created_ts_ = test_start;
    pi->modified_ts_ = test_start;
    pi->free_leases_ = 3;
    test_pools.push_back(pi);

    pi.reset(new SflqPoolInfo());
    pi->start_address_ = IOAddress("192.0.3.0");
    pi->end_address_ = IOAddress("192.0.3.2");
    pi->subnet_id_ = 1;
    pi->created_ts_ = test_start;
    pi->modified_ts_ = test_start;
    pi->free_leases_ = 3;
    test_pools.push_back(pi);

    // Now create the pools.
    for ( auto const& test_pool : test_pools) {
        auto args = test_pool->toElement();
        // Take out what we don't need.
        args->remove("lease-type");
        args->remove("delegated-len");
        args->remove("created-ts");
        args->remove("modified-ts");
        args->remove("free-leases");
        // Add recreate flag.
        args->set("recreate", Element::create(false));

        // Initial create should work.
        command = buildCommand("sflq-pool4-create", args);
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool created.");

        // Trying again without recreate should say it already exists.
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool already exists.");

        // Recreating it should work.
        args->set("recreate", Element::create(true));
        command = buildCommand("sflq-pool4-create", args);
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool created.");
    }

    // Fetching all pools should find all three.
    command = buildCommand("sflq-pool4-get-all");
    auto cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "3 pool(s) found.");
    auto pool_infos = extractPools(cmd_rsp);

    // Should get them back in order they were created. Dummy back end doesn't sort.
    for (size_t i = 0; i < test_pools.size(); ++i) {
        checkPoolInfos(*(*pool_infos)[i], *test_pools[i], __LINE__);
    }

    // Fetch by subnet id for subnet_id = 1.
    pool_infos.reset();
    auto args = Element::fromJSON("{\"subnet-id\": 1}");
    command = buildCommand("sflq-pool4-get-by-subnet", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "2 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(2, pool_infos->size());
    checkPoolInfos(*(*pool_infos)[0], *test_pools[0], __LINE__);
    checkPoolInfos(*(*pool_infos)[1], *test_pools[2], __LINE__);

    // Fetch by subnet id for subnet_id = 2.
    pool_infos.reset();
    args = Element::fromJSON("{\"subnet-id\": 2}");
    command = buildCommand("sflq-pool4-get-by-subnet", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "1 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(1, pool_infos->size());
    checkPoolInfos(*(*pool_infos)[0], *test_pools[1], __LINE__);

    // Fetch by subnet id for subnet_id = 99
    pool_infos.reset();
    pool_infos.reset();
    args = Element::fromJSON("{\"subnet-id\": 99}");
    command = buildCommand("sflq-pool4-get-by-subnet", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_EMPTY, "0 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(0, pool_infos->size());

    // Fetch by a range that excludes them all.
    pool_infos.reset();
    args = Element::fromJSON("{\"start-address\": \"1.2.3.4\","
                             " \"end-address\": \"1.2.3.4\"}");
    command = buildCommand("sflq-pool4-get-by-range", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_EMPTY, "0 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(0, pool_infos->size());

    // Fetch by a range that includes them all.
    pool_infos.reset();
    args = Element::fromJSON("{\"start-address\": \"192.0.0.0\","
                             " \"end-address\": \"192.0.4.0\"}");
    command = buildCommand("sflq-pool4-get-by-range", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "3 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);

    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(3, pool_infos->size());
    checkPoolInfos(*(*pool_infos)[0], *test_pools[0], __LINE__);
    checkPoolInfos(*(*pool_infos)[1], *test_pools[1], __LINE__);
    checkPoolInfos(*(*pool_infos)[2], *test_pools[2], __LINE__);

    // Fetch each by exact range match.
    for ( auto const& test_pool : test_pools) {
        pool_infos.reset();
        args = Element::createMap();
        args->set("start-address", Element::create(test_pool->start_address_.toText()));
        args->set("end-address", Element::create(test_pool->end_address_.toText()));
        command = buildCommand("sflq-pool4-get-by-range", args);
        cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "1 pool(s) found.");
        pool_infos = extractPools(cmd_rsp);
        ASSERT_TRUE(pool_infos);
        ASSERT_EQ(1, pool_infos->size());
        checkPoolInfos(*(*pool_infos)[0], *test_pool, __LINE__);
    }

    // Delete each pool.
    for ( auto const& test_pool : test_pools) {
        // Delete the pool.
        args = Element::createMap();
        args->set("start-address", Element::create(test_pool->start_address_.toText()));
        args->set("end-address", Element::create(test_pool->end_address_.toText()));
        command = buildCommand("sflq-pool4-del", args);
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool deleted");

        // Try again, no such lease.
        testCommand(command, CONTROL_RESULT_EMPTY, "SFLQ pool does not exist");
    }
}

TEST_F(SflqCmds4Test, sflqPool4CreateBadParams) {
    sflqPool4CreateBadParams();
}

TEST_F(SflqCmds4Test, sflqPool4GetAllBadParams) {
    sflqPool4GetAllBadParams();
}

TEST_F(SflqCmds4Test, sflqPool4GetBySubnetBadParams) {
    sflqPool4GetBySubnetBadParams();
}

TEST_F(SflqCmds4Test, sflqPool4GetByRangeBadParams) {
    sflqPool4GetByRangeBadParams();
}

TEST_F(SflqCmds4Test, sflqPool4DelBadParams) {
    sflqPool4DelBadParams();
}

TEST_F(SflqCmds4Test, testSflqCommands) {
    testSflqCommands();
}

TEST_F(SflqCmds4Test, testSflqCommandsMt) {
    MultiThreadingTest mt(true);
    testSflqCommands();
}

/// @brief Class dedicated to testing v6 SFLQ commands in the lease_cmds library.
///
/// These tests use the dhcp::test::SflqTestLeaseMgr for tests as Memfile
/// does not support SFLQ.
///
/// Provides convenience methods for loading, testing the SLFQ commands.
class SflqCmds6Test : public SflqCmdsTest {
public:

    /// @brief Constructor
    SflqCmds6Test()
        : SflqCmdsTest(AF_INET6) {}

    /// @brief Destructor
    virtual ~SflqCmds6Test() {}

    /// @brief Exercises invalid parameter checks for sflq-pool6-create.
    void sflqPool6CreateBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool6-get-all.
    void sflqPool6GetAllBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool6-get-by-subnet.
    void sflqPool6GetBySubnetBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool6-get-by-range.
    void sflqPool6GetByRangeBadParams();

    /// @brief Exercises invalid parameter checks for sflq-pool6-del.
    void sflqPool6DelBadParams();

    /// @todo invalid arguments for get-by-subnet, get-by-range, and delete

    /// @brief Exercises all the V4 SFLQ commands.
    ///
    /// The intent is to verify that each command gets the arguments
    /// it expects, carries out the appropriate action, and returns
    /// the correct responses.
    ///
    /// @param lease_type lease type to test IA_NA or IA_PD
    void testSflqCommands(Lease::Type lease_type);
};

void SflqCmds6Test::sflqPool6CreateBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'start-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10"
        )",
        "missing 'end-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20"
        )",
        "missing 'subnet-id' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 1
        )",
        "missing 'lease-type' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "178.0.0.20",
            "subnet-id" : 1,
            "lease-type": "IA_NA"
        )",
        "invalid V6 range - start_address 3001::10, end_address 178.0.0.20,"
        " must be V6 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::20",
            "end-address" : "3001::10",
            "subnet-id" : 1,
            "lease-type": "IA_NA"
        )",
        "invalid V6 range - start_address 3001::20, end_address 3001::10,"
        " must be V6 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : "bogus",
            "lease-type": "IA_NA"
        )",
        "'subnet-id' parameter is not an integer"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 0,
            "lease-type": "IA_NA"
        )",
        "'subnet-id' must be greater than zero"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 1,
            "lease-type": "bogus"
        )",
        "invalid V6 'lease-type': bogus, valid values are IA_NA and IA_PD"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 1,
            "lease-type": "IA_PD",
            "delegated-len": "bogus"
        )",
        "'delegated-len' parameter is not an integer"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 1,
            "lease-type": "IA_PD",
            "delegated-len": 0
        )",
        "'delegated-len' invalid: 0, it must be >= 1 and =< 128"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 1,
            "lease-type": "IA_PD",
            "delegated-len": 129
        )",
        "'delegated-len' invalid: 129, it must be >= 1 and =< 128"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 0,
            "lease-type": "IA_NA",
            "recreate" : 1
        )",
        "'recreate' parameter is not a boolean"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 0,
            "lease-type": "IA_NA",
            "recreate" : true,
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 100,
            "lease-type": "IA_NA",
            "delegated-len": 56
        )",
        "'delegated-len' must only be 128 for IA_NA pools"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "subnet-id" : 100,
            "lease-type": "IA_PD"
        )",
        "'delegated-len' is required for IA_PD pools"
    }
    };

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool6-create", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds6Test::sflqPool6GetAllBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"(
            "bogus" : "fluff"
        )",
        "command does not take any arguments"
    }};

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool6-get-all", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds6Test::sflqPool6GetBySubnetBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'subnet-id' parameter"
    },
    {
        __LINE__,
        R"(
            "subnet-id": "silly"
        )",
        "'subnet-id' parameter is not an integer"
    },
    {
        __LINE__,
        R"(
            "subnet-id": 1,
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    },
    {
        __LINE__,
        R"(
            "subnet-id": -1
        )",
        "'subnet-id' -1 is invalid, must be greater than zero"
        " and less than 4294967295"
    }
    };

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool6-get-by-subnet", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds6Test::sflqPool6GetByRangeBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'start-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10"
        )",
        "missing 'end-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "178.0.0.20"
        )",
        "invalid V6 range - start_address 3001::10, end_address 178.0.0.20,"
        " must be V6 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::20",
            "end-address" : "3001::10"
        )",
        "invalid V6 range - start_address 3001::20, end_address 3001::10,"
        " must be V6 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    }
    };

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool6-get-by-range", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}

void SflqCmds6Test::sflqPool6DelBadParams() {
    std::list<BadParamScenario> scenarios = {
    {
        __LINE__,
        R"( )",
        "missing 'start-address' parameter"
    },

    {
        __LINE__,
        R"(
            "start-address" : "3001::10"
        )",
        "missing 'end-address' parameter"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "178.0.0.20"
        )",
        "invalid V6 range - start_address 3001::10, end_address 178.0.0.20,"
        " must be V6 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::20",
            "end-address" : "3001::10"
        )",
        "invalid V6 range - start_address 3001::20, end_address 3001::10,"
        " must be V6 addresses where start_address <= end_address"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "force" : "oops"
        )",
        "'force' parameter is not a boolean"
    },
    {
        __LINE__,
        R"(
            "start-address" : "3001::10",
            "end-address" : "3001::20",
            "bogus" : "fluff"
        )",
        "spurious 'bogus' parameter"
    }
    };

    for ( auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::ostringstream command;
        command << R"({ "command": "sflq-pool6-del", "arguments": {)"
                << scenario.args_ << "}}";

        testCommand(command.str(), CONTROL_RESULT_ERROR, scenario.exp_rsp_);
    }
}


void
SflqCmds6Test::testSflqCommands(Lease::Type lease_type) {
    auto test_start = boost::posix_time::second_clock::local_time();

    // Fetching all pools should find none.
    auto command = buildCommand("sflq-pool6-get-all");
    auto cmd_rsp = testCommand(command, CONTROL_RESULT_EMPTY, "0 pool(s) found.");
    auto pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(0, pool_infos->size());

    // Create three test pool infos.
    SflqPoolInfoCollection test_pools;
    SflqPoolInfoPtr pi;
    pi.reset(new SflqPoolInfo());
    pi->start_address_ = IOAddress("3001::10");
    pi->end_address_ = IOAddress("3001::12");
    pi->subnet_id_ = 1;
    pi->lease_type_ = lease_type;
    pi->created_ts_ = test_start;
    pi->modified_ts_ = test_start;
    pi->free_leases_ = 3;
    test_pools.push_back(pi);

    pi.reset(new SflqPoolInfo());
    pi->start_address_ = IOAddress("3001::20");
    pi->end_address_ = IOAddress("3001::22");
    pi->subnet_id_ = 2;
    pi->lease_type_ = lease_type;
    pi->created_ts_ = test_start;
    pi->modified_ts_ = test_start;
    pi->free_leases_ = 3;
    test_pools.push_back(pi);


    pi.reset(new SflqPoolInfo());
    pi->start_address_ = IOAddress("3001::30");
    pi->end_address_ = IOAddress("3001::32");
    pi->subnet_id_ = 1;
    pi->lease_type_ = lease_type;
    pi->created_ts_ = test_start;
    pi->modified_ts_ = test_start;
    pi->free_leases_ = 3;
    test_pools.push_back(pi);

    // Now create the pools.
    for ( auto const& test_pool : test_pools) {
        auto args = test_pool->toElement();
        // Take out what we don't need.
        args->remove("created-ts");
        args->remove("modified-ts");
        args->remove("free-leases");
        // Add recreate flag.
        args->set("recreate", Element::create(false));

        // Initial create should work.
        command = buildCommand("sflq-pool6-create", args);
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool created.");

        // Trying again without recreate should say it already exists.
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool already exists.");

        // Recreating it should work.
        args->set("recreate", Element::create(true));
        command = buildCommand("sflq-pool6-create", args);
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool created.");

    }

    // Fetching all pools should find all three.
    command = buildCommand("sflq-pool6-get-all");
    cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "3 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);

    // Should get them back in order they were created. Dummy back end doesn't sort.
    for (size_t i = 0; i < test_pools.size(); ++i) {
        checkPoolInfos(*(*pool_infos)[i], *test_pools[i], __LINE__);
    }

   // Fetch by subnet id for subnet_id = 1.
    pool_infos.reset();
    auto args = Element::fromJSON("{\"subnet-id\": 1}");
    command = buildCommand("sflq-pool6-get-by-subnet", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "2 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(2, pool_infos->size());
    checkPoolInfos(*(*pool_infos)[0], *test_pools[0], __LINE__);
    checkPoolInfos(*(*pool_infos)[1], *test_pools[2], __LINE__);

    // Fetch by subnet id for subnet_id = 2.
    pool_infos.reset();
    args = Element::fromJSON("{\"subnet-id\": 2}");
    command = buildCommand("sflq-pool6-get-by-subnet", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "1 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(1, pool_infos->size());
    checkPoolInfos(*(*pool_infos)[0], *test_pools[1], __LINE__);

    // Fetch by subnet id for subnet_id = 99
    pool_infos.reset();
    args = Element::fromJSON("{\"subnet-id\": 99}");
    command = buildCommand("sflq-pool6-get-by-subnet", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_EMPTY, "0 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(0, pool_infos->size());

    // Fetch by a range that excludes them all.
    pool_infos.reset();
    args = Element::fromJSON("{\"start-address\": \"2001::1\","
                             " \"end-address\": \"2001::2\"}");
    command = buildCommand("sflq-pool6-get-by-range", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_EMPTY, "0 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(0, pool_infos->size());

    // Fetch by a range that includes them all.
    pool_infos.reset();
    args = Element::fromJSON("{\"start-address\": \"3001::\","
                             " \"end-address\": \"3001::FF\"}");
    command = buildCommand("sflq-pool6-get-by-range", args);
    cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "3 pool(s) found.");
    pool_infos = extractPools(cmd_rsp);
    ASSERT_TRUE(pool_infos);
    ASSERT_EQ(3, pool_infos->size());
    checkPoolInfos(*(*pool_infos)[0], *test_pools[0], __LINE__);
    checkPoolInfos(*(*pool_infos)[1], *test_pools[1], __LINE__);
    checkPoolInfos(*(*pool_infos)[2], *test_pools[2], __LINE__);

    // Fetch each by exact range match.
    for ( auto const& test_pool : test_pools) {
        pool_infos.reset();
        args = Element::createMap();
        args->set("start-address", Element::create(test_pool->start_address_.toText()));
        args->set("end-address", Element::create(test_pool->end_address_.toText()));
        command = buildCommand("sflq-pool6-get-by-range", args);
        cmd_rsp = testCommand(command, CONTROL_RESULT_SUCCESS, "1 pool(s) found.");
        pool_infos = extractPools(cmd_rsp);
        ASSERT_TRUE(pool_infos);
        ASSERT_EQ(1, pool_infos->size());
        checkPoolInfos(*(*pool_infos)[0], *test_pool, __LINE__);
    }

    // Delete each pool.
    for ( auto const& test_pool : test_pools) {
        // Delete the pool.
        args = Element::createMap();
        args->set("start-address", Element::create(test_pool->start_address_.toText()));
        args->set("end-address", Element::create(test_pool->end_address_.toText()));
        command = buildCommand("sflq-pool6-del", args);
        testCommand(command, CONTROL_RESULT_SUCCESS, "SFLQ pool deleted");

        // Try again, no such lease.
        testCommand(command, CONTROL_RESULT_EMPTY, "SFLQ pool does not exist");
    }
}

TEST_F(SflqCmds6Test, sflqPool6CreateBadParams) {
    sflqPool6CreateBadParams();
}

TEST_F(SflqCmds6Test, sflqPool6GetAllBadParams) {
    sflqPool6GetAllBadParams();
}

TEST_F(SflqCmds6Test, sflqPool6GetBySubnetBadParams) {
    sflqPool6GetBySubnetBadParams();
}

TEST_F(SflqCmds6Test, sflqPool6GetByRangeBadParams) {
    sflqPool6GetByRangeBadParams();
}

TEST_F(SflqCmds6Test, sflqPool6DelBadParams) {
    sflqPool6DelBadParams();
}

TEST_F(SflqCmds6Test, testSflqCommandsNA) {
    testSflqCommands(Lease::TYPE_NA);
}

TEST_F(SflqCmds6Test, testSflqCommandsNAMt) {
    MultiThreadingTest mt(true);
    testSflqCommands(Lease::TYPE_NA);
}

TEST_F(SflqCmds6Test, testSflqCommandsPD) {
    testSflqCommands(Lease::TYPE_PD);
}

TEST_F(SflqCmds6Test, testSflqCommandsPDMt) {
    MultiThreadingTest mt(true);
    testSflqCommands(Lease::TYPE_PD);
}


} // end of anonymous namespace
