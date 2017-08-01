// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>
#include <config/command_mgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/cfgmgr.h>
#include <cc/command_interpreter.h>
#include <gtest/gtest.h>
#include <cc/data.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

/// @brief Test fixture for testing loading and unloading the flex-id library
class LibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor
    LibLoadTest(std::string lib_filename)
        : lib_name_(lib_filename) {
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

    /// @brief Load all specified libriaries.
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
        }
    }

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
    /// @return full response returned by the command execution.
    ConstElementPtr testCommand(string cmd_txt, int exp_result, string exp_txt) {
        // Let's load the library first.
        loadLib();

        ConstElementPtr cmd;
        EXPECT_NO_THROW(cmd = Element::fromJSON(cmd_txt));
        if (!cmd) {
            ADD_FAILURE() << cmd_txt << " is not a valid JSON, test broken";
            return (ConstElementPtr());
        }

        cout << "#### processing command " << cmd->str() << endl;

        ConstElementPtr rsp = CommandMgr::instance().processCommand(cmd);

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

    /// @brief Loads the library specified by lib_name_
    void loadLib() {
        if (libraries_.empty()) {
            data::ElementPtr params = data::Element::createMap();
            std::cout << "Trying to load " << lib_name_ << "..." << std::endl;
            addLib(lib_name_, params);
        }
        EXPECT_NO_THROW(loadLibs());
    }

    /// List of libraries to be/being loaded (usually just one)
    HookLibsCollection libraries_;

    /// Path to the library filename
    std::string lib_name_;
};

class LeaseCmdsTest : public LibLoadTest {
public:

    /// @brief Pointer to the lease manager
    LeaseMgr* lmptr_;

    LeaseCmdsTest()
        :LibLoadTest(LIB_SO) {
        lmptr_ = 0;
    }

    virtual ~LeaseCmdsTest() {
        LeaseMgrFactory::destroy();
        lmptr_ = 0;
    }

    void initLeaseMgr(bool v6, bool insert_lease) {

        LeaseMgrFactory::destroy();
        std::ostringstream s;
        s << "type=memfile persist=false " << (v6 ? "universe=6" : "universe=4");
        LeaseMgrFactory::create(s.str());

        lmptr_ = &(LeaseMgrFactory::instance());
        ASSERT_TRUE(lmptr_);

        CfgMgr& cfg_mgr = CfgMgr::instance();
        if (v6) {
            Subnet6Ptr subnet6(new Subnet6(IOAddress("2001:db8::"), 48, 1, 2, 3, 4, 66));
            CfgSubnets6Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();
            subnets->add(subnet6);
            cfg_mgr.commit();
        } else {
            Subnet4Ptr subnet4(new Subnet4(IOAddress("192.1.2.0"), 24, 1, 2, 3, 44));
            CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();
            subnets->add(subnet4);
            cfg_mgr.commit();
        }

        if (insert_lease) {
            if (v6) {
                lmptr_->addLease(createLease6());
            } else {
                lmptr_->addLease(createLease6());
            }
        }
    }

    Lease4Ptr createLease4() {
        Lease4Ptr lease(new Lease4());

        lease->addr_ = IOAddress("192.0.2.123");

        // Initialize unused fields.
        lease->t1_ = 0;                             // Not saved
        lease->t2_ = 0;                             // Not saved

        // Set other parameters.  For historical reasons, address 0 is not used.
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x08), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x42)));
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->subnet_id_ = 23;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = false;
        lease->hostname_ = "myhost.example.com.";

        return (lease);
    }

    Lease6Ptr createLease6() {
        Lease6Ptr lease(new Lease6());

        lease->type_ = Lease::TYPE_NA;
        lease->prefixlen_ = 4;
        lease->iaid_ = 142;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x77)));
        lease->preferred_lft_ = 900;
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->subnet_id_ = 23;
        lease->fqdn_fwd_ = true;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "myhost.example.com.";

        return (lease);
    }


    // @brief Checks if specified response contains IPv4 lease
    void checkResponseLease4(ConstElementPtr rsp, bool client_id_required) {
        ASSERT_TRUE(rsp);
        ConstElementPtr l = rsp->get("arguments"); // Lease
        ASSERT_TRUE(l);
        EXPECT_TRUE(l->get("ip-address"));
        // client-id may or may not appear
        if (client_id_required) {
            EXPECT_TRUE(l->get("client-id"));
        }
        EXPECT_TRUE(l->get("hw-address"));
        EXPECT_TRUE(l->get("valid-lft"));
        EXPECT_TRUE(l->get("expire"));
        EXPECT_TRUE(l->get("subnet-id"));
        EXPECT_TRUE(l->get("state"));
        EXPECT_TRUE(l->get("fqdn-fwd"));
        EXPECT_TRUE(l->get("fqdn-rev"));
        EXPECT_TRUE(l->get("hostname"));
        EXPECT_TRUE(l->get("state"));


        // Check that there are no v6 specific fields
        EXPECT_FALSE(l->get("prefix"));
        EXPECT_FALSE(l->get("duid"));
    }

    // @brief Checks if specified response contains IPv6 lease
    void checkResponseHost6(ConstElementPtr rsp) {
        ASSERT_TRUE(rsp);
        ConstElementPtr l = rsp->get("arguments"); // lease
        ASSERT_TRUE(l);

        // Check that there are expected fields
        ASSERT_TRUE(l->contains("ip-address") || l->contains("prefix"))
            << " either ip-address or prefix must be present for IPv6 lease";
        EXPECT_TRUE(l->get("duid"));
        EXPECT_TRUE(l->get("valid-lft"));
        EXPECT_TRUE(l->get("expire"));
        EXPECT_TRUE(l->get("subnet-id"));
        EXPECT_TRUE(l->get("fqdn-fwd"));
        EXPECT_TRUE(l->get("fqdn-rev"));
        EXPECT_TRUE(l->get("hostname"));
        EXPECT_TRUE(l->get("state"));

        // Check that there are no v4 specific fields.
        EXPECT_FALSE(l->get("hw-address"));
        EXPECT_FALSE(l->get("client-id"));
    }

};

// Simple test that checks the library really registers the commands.
TEST_F(LeaseCmdsTest, commands) {

    vector<string> cmds = { "lease4-add", "lease6-add",
                            "lease4-get", "lease6-get",
                            "lease4-del", "lease6-del",
                            "lease4-update", "lease6-update",
                            "lease4-del-all", "lease6-del-all" };

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
TEST_F(LeaseCmdsTest, multipleLoads) {

    EXPECT_NO_THROW(loadLib());
    EXPECT_NO_THROW(unloadLibs());

    EXPECT_NO_THROW(loadLib());
    EXPECT_NO_THROW(unloadLibs());

    EXPECT_NO_THROW(loadLib());
    EXPECT_NO_THROW(unloadLibs());

    EXPECT_NO_THROW(loadLib());
    EXPECT_NO_THROW(unloadLibs());
}

using namespace isc::dhcp;

// Check that a simple, well formed lease4 can be added.
TEST_F(LeaseCmdsTest, Lease4Add) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"lease\": {"
        "            \"subnet-id\": 44,\n"
        "            \"ip-address\": \"192.0.2.202\",\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ(3, l->valid_lft_); // taken from subnet configuration
    EXPECT_EQ(false, l->fqdn_fwd_);
    EXPECT_EQ(false, l->fqdn_rev_);
    EXPECT_EQ("", l->hostname_);

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could hit the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(0, l->state_);

}

// Check that a well formed lease4 with tons of parameters can be added.
TEST_F(LeaseCmdsTest, Lease4AddFull) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"lease\": {"
        "            \"subnet-id\": 44,\n"
        "            \"ip-address\": \"192.0.2.202\",\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"client-id\": \"01:02:03:04:05:06:07:08\",\n"
        "            \"valid-lft\": 1000,\n"
        "            \"expire\": 12345678,\n"
        "            \"fqdn-fwd\": true,\n"
        "            \"fqdn-rev\": true,\n"
        "            \"hostname\": \"urania.example.org\""
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ("192.0.2.202", l->addr_.toText());
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->client_id_);
    EXPECT_EQ("01:02:03:04:05:06:07:08", l->client_id_->toText());
    EXPECT_EQ(l->cltt_, 12344678); // expire (12345678) - valid_lft(1000)
    EXPECT_EQ(true, l->fqdn_fwd_);
    EXPECT_EQ(true, l->fqdn_rev_);
    EXPECT_EQ("urania.example.org", l->hostname_);
}

// Check that a simple, well formed lease6 can be added.
TEST_F(LeaseCmdsTest, Lease6Add) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"lease\": {"
        "            \"subnet-id\": 66,\n"
        "            \"ip-address\": \"2001:db8::3\",\n"
        "            \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"iaid\": 1234\n"
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8::3")));
}

// Check that a well formed lease4 with tons of parameters can be added.
TEST_F(LeaseCmdsTest, Lease6AddFullAddr) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"lease\": {"
        "            \"subnet-id\": 66,\n"
        "            \"ip-address\": \"2001:db8::3\",\n"
        "            \"duid\": \"01:02:03:04:05:06:07:08\",\n"
        "            \"iaid\": 1234,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "            \"preferred-lft\": 500,\n"
        "            \"valid-lft\": 1000,\n"
        "            \"expire\": 12345678,\n"
        "            \"fqdn-fwd\": true,\n"
        "            \"fqdn-rev\": true,\n"
        "            \"hostname\": \"urania.example.org\""
        "        }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::TYPE_NA, l->type_);
    EXPECT_EQ("2001:db8::3", l->addr_.toText());
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("01:02:03:04:05:06:07:08", l->duid_->toText());
    EXPECT_EQ(l->cltt_, 12344678); // expire (12345678) - valid_lft(1000)
    EXPECT_EQ(true, l->fqdn_fwd_);
    EXPECT_EQ(true, l->fqdn_rev_);
    EXPECT_EQ("urania.example.org", l->hostname_);
}

// Checks that reservation-get can handle a situation when the query is
// broken (no parameters at all).
TEST_F(LeaseCmdsTest, ReservationGetNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-get can handle a situation when the query is
// broken (just subnet-id).
TEST_F(LeaseCmdsTest, ReservationGetNoAddress) {
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
TEST_F(LeaseCmdsTest, ReservationGetNoIdentifier) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
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
TEST_F(LeaseCmdsTest, ReservationGetNoIdentifierType) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier\": \"00:11:22:33:44:55\""
        "    }\n"
        "}";
    string rsp = "No 'ip-address' provided and 'identifier-type' is either missing "
                 "or not a string.";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that reservation-get(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(LeaseCmdsTest, ReservationGetByAddr4NotFound) {
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

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-get(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is returned.
TEST_F(LeaseCmdsTest, ReservationGetByAddr4) {

    // First, let's create a dummy host data source.
    initLeaseMgr(true, false); // insert v4 host

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

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
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
}

// Checks that reservation-get(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(LeaseCmdsTest, ReservationGetByAddr6NotFound) {
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

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-get(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(LeaseCmdsTest, ReservationGetByIdentifierNotFound) {
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

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-get(subnet-id, identifier-type, identifier) can handle
// a situation when the query returns a host.
TEST_F(LeaseCmdsTest, ReservationGetByIdentifier4) {
    CfgMgr::instance().setFamily(AF_INET);

    // First, let's create a dummy host data source.
    initLeaseMgr(true, false); // insert v4 host

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
}

// Checks that reservation-get(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is returned.
TEST_F(LeaseCmdsTest, ReservationGetByAddr6) {

    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    initLeaseMgr(false, true); // insert v6 host

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
TEST_F(LeaseCmdsTest, ReservationGetByIdentifier6) {
    CfgMgr::instance().setFamily(AF_INET6);

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
TEST_F(LeaseCmdsTest, ReservationDelNoParams) {
    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";

    // This should be rejected, because subnet-id parameter is mandatory.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-del can handle a situation when the query is
// broken (just subnet-id).
TEST_F(LeaseCmdsTest, ReservationDelNoAddress) {
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
TEST_F(LeaseCmdsTest, ReservationDelIdentifier) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
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
TEST_F(LeaseCmdsTest, ReservationDelNoIdentifierType) {
    string cmd =
        "{\n"
        "    \"command\": \"reservation-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier\": \"00:11:22:33:44:55\""
        "    }\n"
        "}";
    string rsp = "No 'ip-address' provided and 'identifier-type' is either missing "
                 "or not a string.";

    testCommand(cmd, CONTROL_RESULT_ERROR, rsp);
}

// Checks that properly formed reservation-del(subnet-id, addr) will not work if
// there is no hosts-database configured.
TEST_F(LeaseCmdsTest, ReservationDelNoHostsDatabase) {
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

// Checks that reservation-del(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(LeaseCmdsTest, ReservationDelByAddr4NotFound) {

    initLeaseMgr(false, false);

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

    // Note the status expected is failure, because the host was not found.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is deleted.
TEST_F(LeaseCmdsTest, ReservationDelByAddr4) {

    // First, let's create a dummy host data source.
    initLeaseMgr(true, false); // insert v4 host

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

    // Note the status expected is success, because the query was well formed
    // and the DB search actually completed. It just didn't found the host.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(LeaseCmdsTest, ReservationDelByAddr6NotFound) {

    // First, let's create a dummy host data source.
    initLeaseMgr(false, false); // Don't insert any hosts.

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

    // Note the status expected is failure, because the host was not found.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-del(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the host is not there.
TEST_F(LeaseCmdsTest, ReservationDelByIdentifierNotFound) {

    // First, let's create a dummy host data source.
    initLeaseMgr(false, false); // Don't insert any hosts.

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

    // Note the status expected is failure, because the host was not found.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that reservation-del(subnet-id, identifier-type, identifier) can handle
// a situation when the v4 host is deleted.
TEST_F(LeaseCmdsTest, ReservationDelByIdentifier4) {
    CfgMgr::instance().setFamily(AF_INET);

    // First, let's create a dummy host data source.
    initLeaseMgr(true, false); // insert v4 host

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

// Checks that reservation-del(subnet-id, addr4) can handle a situation when
// the query is correctly formed and the host is deleted.
TEST_F(LeaseCmdsTest, ReservationDelByAddr6) {

    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    initLeaseMgr(false, true); // insert v6 host

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

// Checks that reservation-del(subnet-id, identifier-type, identifier) can handle
// a situation when the v6 host is actually deleted.
TEST_F(LeaseCmdsTest, ReservationDelByIdentifier6) {
    CfgMgr::instance().setFamily(AF_INET6);

    // First, let's create a dummy host data source.
    initLeaseMgr(false, true); // insert v6 host

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

} // end of anonymous namespace
