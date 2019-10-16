// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfgmgr.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <testutils/user_context_utils.h>
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

namespace {

/// @brief High valid lifetime used for leases in the tests below.
constexpr uint32_t HIGH_VALID_LIFETIME = 0xFFFFFFFE;

/// @brief December 11th 2030 date used in the unit tests for cltt.
constexpr time_t DEC_2030_TIME = 1923222072;

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

        // Process the command and verify response.
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

    /// List of libraries to be/being loaded (usually just one)
    HookLibsCollection libraries_;

    /// Path to the library filename
    std::string lib_name_;
};

/// @brief Class dedicated to testing lease_cmds library.
///
/// Provides convenience methods for loading, testing all commands and
/// unloading the lease_cmds library.
class LeaseCmdsTest : public LibLoadTest {
public:

    /// @brief Pointer to the lease manager
    LeaseMgr* lmptr_;

    /// @brief Constructor
    ///
    /// Sets the library filename and clears the lease manager pointer.
    /// Also ensured there is no lease manager leftovers from previous
    /// test.
    LeaseCmdsTest()
        :LibLoadTest(LEASE_CMDS_LIB_SO) {
        LeaseMgrFactory::destroy();
        lmptr_ = 0;
    }

    /// @brief Destructor
    ///
    /// Removes library (if any), destroys lease manager (if any).
    virtual ~LeaseCmdsTest() {
        // destroys lease manager first because the other order triggers
        // a clang/boost bug
        LeaseMgrFactory::destroy();
        unloadLibs();
        lmptr_ = 0;
    }

    /// @brief Initializes lease manager (and optionally populates it with a lease)
    ///
    /// Creates a lease manager (memfile, trimmed down to keep everything in memory
    /// only) and optionally can create a lease, which is useful for leaseX-get and
    /// leasex-del type of tests. For lease details, see @ref createLease4 and
    /// @ref createLease6.
    ///
    /// @param v6 true = v6, false = v4
    /// @param insert_lease governs whether a lease should be pre-inserted
    void initLeaseMgr(bool v6, bool insert_lease) {

        LeaseMgrFactory::destroy();
        std::ostringstream s;
        s << "type=memfile persist=false " << (v6 ? "universe=6" : "universe=4");
        LeaseMgrFactory::create(s.str());

        lmptr_ = &(LeaseMgrFactory::instance());
        ASSERT_TRUE(lmptr_);

        CfgMgr& cfg_mgr = CfgMgr::instance();
        if (v6) {
            Subnet6Ptr subnet66(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4, 66));
            Subnet6Ptr subnet99(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4, 99));
            CfgSubnets6Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();
            subnets->add(subnet66);
            subnets->add(subnet99);
            cfg_mgr.commit();
        } else {
            Subnet4Ptr subnet44(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 44));
            Subnet4Ptr subnet88(new Subnet4(IOAddress("192.0.3.0"), 24, 1, 2, 3, 88));
            CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();
            subnets->add(subnet44);
            subnets->add(subnet88);
            cfg_mgr.commit();
        }

        if (insert_lease) {
            if (v6) {
                lmptr_->addLease(createLease6("2001:db8:1::1", 66, 0x42));
                lmptr_->addLease(createLease6("2001:db8:1::2", 66, 0x56));
                lmptr_->addLease(createLease6("2001:db8:2::1", 99, 0x42));
                lmptr_->addLease(createLease6("2001:db8:2::2", 99, 0x56));
            } else {
                lmptr_->addLease(createLease4("192.0.2.1", 44, 0x08, 0x42));
                lmptr_->addLease(createLease4("192.0.2.2", 44, 0x09, 0x56));
                lmptr_->addLease(createLease4("192.0.3.1", 88, 0x08, 0x42));
                lmptr_->addLease(createLease4("192.0.3.2", 88, 0x09, 0x56));
            }
        }
    }

    /// @brief Creates an IPv4 lease
    ///
    /// Lease parameters: valid lifetime = 0xFFFFFFFE, cltt = 1923222072, fqdn-fwd = false,
    /// fqdn-rev = true, hostname = myhost.example.com
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param hw_address_pattern value to be used for generating HW address by repeating
    /// it 6 times.
    /// @param client_id_pattern value to be used for generating client identifier by
    /// repeating it 8 times.
    /// @return Returns the lease created
    Lease4Ptr createLease4(const std::string& ip_address, const SubnetID& subnet_id,
                           const uint8_t hw_address_pattern,
                           const uint8_t client_id_pattern) {
        Lease4Ptr lease(new Lease4());

        lease->addr_ = IOAddress(ip_address);

        // Set other parameters.  For historical reasons, address 0 is not used.
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, hw_address_pattern), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, client_id_pattern)));
        // Purposely using high cltt and valid lifetime to test that
        // expiration time is cast properly.
        lease->valid_lft_ = HIGH_VALID_LIFETIME; // Very high valid lifetime
        lease->cltt_ = DEC_2030_TIME; // December 11th 2030
        lease->subnet_id_ = subnet_id;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "myhost.example.com.";

        return (lease);
    }

    /// @brief Creates an IPv6 lease
    ///
    /// Lease parameters: cltt = 1923222072, fqdn-fwd = false, fqdn-rev = true,
    /// hostname = myhost.example.com, preferred lifetime = 1800,
    /// valid lifetime = 0xFFFFFFFE
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param duid_address_pattern value to be used for generating DUID by
    /// repeating it 8 times
    /// @return Returns the lease created
    Lease6Ptr createLease6(const std::string& ip_address, const SubnetID& subnet_id,
                           const uint8_t duid_pattern) {
        Lease6Ptr lease(new Lease6());

        lease->addr_ = IOAddress(ip_address);
        lease->type_ = Lease::TYPE_NA;
        lease->prefixlen_ = 128;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, duid_pattern)));
        lease->preferred_lft_ = 1800;
        // Purposely using high cltt and valid lifetime to test that
        // expiration time is cast properly.
        lease->valid_lft_ = HIGH_VALID_LIFETIME; // Very high valid lifetime
        lease->cltt_ = DEC_2030_TIME; // December 11th 2030
        lease->subnet_id_ = subnet_id;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "myhost.example.com.";

        return (lease);
    }

    /// @brief Checks if specified response contains IPv4 lease
    ///
    /// @param lease Element tree that represents a lease
    /// @param ip expected IP address
    /// @param subnet_id expected subnet-id
    /// @param hwaddr expected value of hardware address
    /// @param client_id_required true if client-id is expected
    void checkLease4(ConstElementPtr l, std::string ip,
                     uint32_t subnet_id, std::string hwaddr,
                     bool client_id_required) {
        ASSERT_TRUE(l);

        // If the element is a list we need to retrieve the lease that
        // we're interested in.
        if (l->getType() == Element::list) {
            std::vector<ElementPtr> e = l->listValue();
            for (auto it = e.begin(); it != e.end(); ++it) {
                ConstElementPtr ip_address = (*it)->get("ip-address");
                if (ip_address && ip_address->stringValue() == ip) {
                    l = (*it);
                    break;
                }
            }

            ASSERT_TRUE(l);
        }

        ASSERT_TRUE(l->get("ip-address"));
        EXPECT_EQ(ip, l->get("ip-address")->stringValue());

        ASSERT_TRUE(l->get("subnet-id"));
        EXPECT_EQ(subnet_id, l->get("subnet-id")->intValue());

        ASSERT_TRUE(l->get("hw-address"));
        EXPECT_EQ(hwaddr, l->get("hw-address")->stringValue());

        // client-id may or may not appear
        if (client_id_required) {
            EXPECT_TRUE(l->get("client-id"));
        }

        // Check that other parameters are there.
        ASSERT_TRUE(l->contains("valid-lft"));
        ASSERT_TRUE(l->contains("cltt"));
        ASSERT_TRUE(l->contains("subnet-id"));
        ASSERT_TRUE(l->contains("state"));
        ASSERT_TRUE(l->contains("fqdn-fwd"));
        ASSERT_TRUE(l->contains("fqdn-rev"));
        ASSERT_TRUE(l->contains("hostname"));
        ASSERT_TRUE(l->contains("state"));

        // Check that there are no v6 specific fields
        ASSERT_FALSE(l->contains("prefix"));
        ASSERT_FALSE(l->contains("duid"));
        ASSERT_FALSE(l->contains("preferred-lft"));

        // Assuming that these values were used to create the lease.
        // If we ever want to test different values they will need to
        // be added as parameters to this function.
        EXPECT_EQ(HIGH_VALID_LIFETIME,
                  static_cast<uint32_t>(l->get("valid-lft")->intValue()));
        EXPECT_EQ(DEC_2030_TIME, l->get("cltt")->intValue());
    }

    /// @brief Checks if specified response contains IPv6 lease
    ///
    /// @param lease Element tree that represents a lease
    /// @param ip expected IP address (or prefix)
    /// @param prefixlen prefix length (0 = expect address)
    /// @param subnet_id expected subnet-id
    /// @param duid expected value of DUID
    /// @param hwaddr_required true if hwaddr is expected
    void checkLease6(ConstElementPtr l, std::string ip,
                     uint8_t prefixlen,
                     uint32_t subnet_id, std::string duid,
                     bool hwaddr_required) {

        ASSERT_TRUE(l);

        // If the element is a list we need to retrieve the lease that
        // we're interested in.
        if (l->getType() == Element::list) {
            std::vector<ElementPtr> e = l->listValue();
            for (auto it = e.begin(); it != e.end(); ++it) {
                ConstElementPtr ip_address = (*it)->get("ip-address");
                if (ip_address && ip_address->stringValue() == ip) {
                    l = (*it);
                    break;
                }
            }

            ASSERT_TRUE(l);
        }

        ASSERT_TRUE(l->contains("ip-address"));
        EXPECT_EQ(ip, l->get("ip-address")->stringValue());
        if (prefixlen != 0) {
            ASSERT_TRUE(l->get("prefix-len"));
            EXPECT_EQ(prefixlen, l->get("prefix-len")->intValue());
        }

        ASSERT_TRUE(l->contains("subnet-id"));
        EXPECT_EQ(subnet_id, l->get("subnet-id")->intValue());

        ASSERT_TRUE(l->contains("duid"));
        EXPECT_EQ(duid, l->get("duid")->stringValue());

        // hwaddr may or may not appear
        if (hwaddr_required) {
            EXPECT_TRUE(l->get("hwaddr"));
        }

        // Check that there are expected fields
        ASSERT_TRUE(l->contains("preferred-lft"));
        ASSERT_TRUE(l->contains("valid-lft"));
        ASSERT_TRUE(l->contains("cltt"));
        ASSERT_TRUE(l->contains("subnet-id"));
        ASSERT_TRUE(l->contains("fqdn-fwd"));
        ASSERT_TRUE(l->contains("fqdn-rev"));
        ASSERT_TRUE(l->contains("hostname"));
        ASSERT_TRUE(l->contains("state"));

        // Check that there are no v4 specific fields.
        ASSERT_FALSE(l->contains("client-id"));

        // Assuming that these values were used to create the lease.
        // If we ever want to test different values they will need to
        // be added as parameters to this function.
        EXPECT_EQ(HIGH_VALID_LIFETIME,
                  static_cast<uint32_t>(l->get("valid-lft")->intValue()));
        EXPECT_EQ(DEC_2030_TIME, l->get("cltt")->intValue());
    }

    /// @brief This function checks that the JSON list contains an entry
    /// indicating lease deletion, creation or update failure.
    ///
    /// @param failed_leases_list JSON list containing list of leases.
    /// @param expected_type Expected lease type as text.
    /// @param expected_ip_address Expected IP address.
    /// @oaram expected_control_result Expected control result for the lease.
    /// @param expected_error_msg Expected error message. Default is an empty
    /// string which indicates that the error message should not be checked.
    void checkFailedLease(const ConstElementPtr& failed_leases_list,
                          const std::string& expected_type,
                          const std::string& expected_ip_address,
                          const int expected_control_result,
                          const std::string& expected_error_msg = "") {
        ASSERT_TRUE(failed_leases_list);

        for (auto i = 0; i < failed_leases_list->size(); ++i) {

            auto failed_lease = failed_leases_list->get(i);
            ASSERT_TRUE(failed_lease);
            ASSERT_EQ(Element::map, failed_lease->getType());

            auto ip_address = failed_lease->get("ip-address");
            ASSERT_TRUE(ip_address);
            ASSERT_EQ(Element::string, ip_address->getType());

            if (ip_address->stringValue() == expected_ip_address) {

                auto lease_type = failed_lease->get("type");
                ASSERT_TRUE(lease_type);
                ASSERT_EQ(Element::string, lease_type->getType());
                EXPECT_EQ(expected_type, lease_type->stringValue());

                auto control_result = failed_lease->get("result");
                ASSERT_TRUE(control_result);
                ASSERT_EQ(Element::integer, control_result->getType());
                EXPECT_EQ(expected_control_result, control_result->intValue());

                if (!expected_error_msg.empty()) {
                    auto error_msg = failed_lease->get("error-message");
                    ASSERT_TRUE(error_msg);
                    ASSERT_EQ(Element::string, error_msg->getType());
                    EXPECT_EQ(expected_error_msg, error_msg->stringValue());
                }

                return;
            }
        }

        ADD_FAILURE() << "expected lease not found";
    }
};

// Simple test that checks the library really registers the commands.
TEST_F(LeaseCmdsTest, commands) {

    vector<string> cmds = {
        "lease4-add",               "lease6-add",
        "lease4-get",               "lease6-get",
        "lease4-get-all",           "lease6-get-all",
        "lease4-get-page",          "lease6-get-page",
        "lease4-get-by-hw-address",
        "lease4-get-by-client-id",  "lease6-get-by-duid",
        "lease4-get-by-hostname",   "lease6-get-by-hostname",
        "lease4-del",               "lease6-del",
        "lease4-update",            "lease6-update",
        "lease4-wipe",              "lease6-wipe"
    };
    testCommands(cmds);
}

// Check that the library can be loaded and unloaded multiple times.
TEST_F(LeaseCmdsTest, multipleLoads) {
    testMultipleLoads();
}

using namespace isc::dhcp;

// Check that lease4-add with missing parameters will fail.
TEST_F(LeaseCmdsTest, Lease4AddMissingParams) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Everything missing. What sort of crap is that?
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and hwaddr missing, although
    // subnet-id can now be figured out by Kea code)
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "            \"ip-address\": \"192.0.2.123\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Better, but still no luck. (hwaddr missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Close, but no cigars. (ip-address missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verify that lease4-add can be rejected if parameters are specified, but
// have incorrect values.
TEST_F(LeaseCmdsTest, Lease4AddBadParams) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv4 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // This time the IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"10.0.0.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "The address 10.0.0.1 does not belong to subnet 192.0.2.0/24, subnet-id=44";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // We don't use any of that bleeding edge nonsense in this museum. v4 only.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv4 address specified: 2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // currently defined states are 0,1 and 2. 123 is junk.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"state\": 123\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid state value: 123, supported values are: 0 (default), 1 "
        "(declined) and 2 (expired-reclaimed)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

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
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ(3, l->valid_lft_); // taken from subnet configuration
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could have the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(0, l->state_);

}

// Check that subnet-id is optional. If not specified, Kea should select
// it on its own.
TEST_F(LeaseCmdsTest, Lease4AddSubnetIdMissing) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command without subnet-id. Kea should select
    // the subnet id on its own.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ(44, l->subnet_id_);

}

// Check that subnet-id is optional. If not specified, Kea should select
// it on its own, but if there's no subnet for address being added, it
// should fail.
TEST_F(LeaseCmdsTest, Lease4AddSubnetIdMissingBadAddr) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command without subnet-id. Kea should select
    // the subnet id on its own.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.55.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "subnet-id not specified and failed to find a subnet for "
                     "address 192.0.55.1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.55.1"));
    ASSERT_FALSE(l);
}

// Check that the lease with negative expiration time is rejected.
TEST_F(LeaseCmdsTest, Lease4AddNegativeExpireTime) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Add a lease with negative expiration time.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"expire\": -6218189367\n"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be positive for address 192.0.2.202";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_FALSE(l);
}

// Check that the lease with negative cltt is rejected.
TEST_F(LeaseCmdsTest, Lease4AddNegativeCltt) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Add a lease with negative cltt (expiration time - valid lifetime)
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"expire\": 123456,\n"
        "        \"valid-lft\": 123457"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be greater than valid lifetime for "
        "address 192.0.2.202";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_FALSE(l);
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
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"client-id\": \"01:02:03:04:05:06:07:08\",\n"
        "        \"valid-lft\": 1000,\n"
        "        \"expire\": 6218189367,\n"
        "        \"fqdn-fwd\": true,\n"
        "        \"fqdn-rev\": true,\n"
        "        \"hostname\": \"urania.example.org\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ("192.0.2.202", l->addr_.toText());
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->client_id_);
    EXPECT_EQ("01:02:03:04:05:06:07:08", l->client_id_->toText());
    // expire (6218189367) - valid_lft(1000)
    EXPECT_EQ(static_cast<time_t>(6218189367 - 1000), l->cltt_);
    EXPECT_EQ(true, l->fqdn_fwd_);
    EXPECT_EQ(true, l->fqdn_rev_);
    EXPECT_EQ("urania.example.org", l->hostname_);
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"foobar\": true }", l->getContext()->str());
}

// Check that a well formed lease4 with a comment can be added.
TEST_F(LeaseCmdsTest, Lease4AddComment) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
            "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"comment\": \"a comment\" }", l->getContext()->str());
}

// Check that lease6-add with missing parameters will fail.
TEST_F(LeaseCmdsTest, Lease6AddMissingParams) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Everything missing. What sort of nonsense is that?
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and duid missing, but subnet-id
    // can now be figured out by kea)
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::3\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id and ip is not enough (duid missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id and duid is not enough (ip, iaid missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id, duid and iaid is not enough (ip missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Close, but no cigars. Still missing iaid.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"ip-address\": \"2001:db8:1::3\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'iaid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verify that lease6-add can be rejected if parameters specified, but
// have incorrect values.
TEST_F(LeaseCmdsTest, Lease6AddBadParams) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Invalid subnet-id. Only 66 is configured.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv6 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // This time the IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"3000::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "The address 3000::3 does not belong to subnet 2001:db8:1::/48, subnet-id=66";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // v4? You're a time traveler from early 80s or what?
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv6 address specified: 192.0.2.1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid state: the only supported values are 0,1,2.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"state\": 123\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid state value: 123, supported values are: 0 (default), 1 "
        "(declined) and 2 (expired-reclaimed)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Negative expiration time.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"expire\": -6218189367\n"
        "    }\n"
        "}";
    exp_rsp = "expiration time must be positive for address 2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Negative cltt
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"expire\": 123456,\n"
        "        \"valid-lft\": 123457"
        "    }\n"
        "}";
    exp_rsp = "expiration time must be greater than valid lifetime for address "
        "2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

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
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

// Check that subnet-id is optional. If not specified, Kea should select
// it on its own.
TEST_F(LeaseCmdsTest, Lease6AddSubnetIdMissing) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command (without subnet-id)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there and has correct subnet-id.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(66, l->subnet_id_);
}

// Check that subnet-id is optional. If not specified, Kea should select
// it on its own, but if there's no subnet for address being added, it
// should fail.
TEST_F(LeaseCmdsTest, Lease6AddSubnetIdMissingBadAddr) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command (without subnet-id)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:ffff::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "subnet-id not specified and failed to find a subnet for "
                     "address 2001:ffff::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Now check that the lease is really there and has correct subnet-id.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:ffff::1"));
    ASSERT_FALSE(l);
}

// Check that a simple, well formed prefix lease can be added.
TEST_F(LeaseCmdsTest, Lease6AddPrefix) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:abcd::\",\n"
        "        \"prefix-len\": 48,\n"
        "        \"type\": \"IA_PD\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for prefix 2001:db8:abcd::/48, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:abcd::"));
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::TYPE_PD, l->type_);
    EXPECT_EQ(48, l->prefixlen_);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

// Check that a well formed lease6 with tons of parameters can be added.
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
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"01:02:03:04:05:06:07:08\",\n"
        "        \"iaid\": 1234,\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"preferred-lft\": 500,\n"
        "        \"valid-lft\": 1000,\n"
        "        \"expire\": 6218189367,\n"
        "        \"fqdn-fwd\": true,\n"
        "        \"fqdn-rev\": true,\n"
        "        \"hostname\": \"urania.example.org\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::TYPE_NA, l->type_);
    EXPECT_EQ("2001:db8:1::3", l->addr_.toText());
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("01:02:03:04:05:06:07:08", l->duid_->toText());
    // expire (6218189367) - valid_lft(1000)
    EXPECT_EQ(static_cast<time_t>(6218189367 - 1000), l->cltt_);
    EXPECT_EQ(true, l->fqdn_fwd_);
    EXPECT_EQ(true, l->fqdn_rev_);
    EXPECT_EQ("urania.example.org", l->hostname_);
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"foobar\": true }", l->getContext()->str());
}

// Check that a well formed lease6 with a comment can be added.
TEST_F(LeaseCmdsTest, Lease6AddComment) {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"comment\": \"a comment\" }", l->getContext()->str());
}

// Checks that lease6-get can handle a situation when the query is
// broken (some required parameters are missing).
TEST_F(LeaseCmdsTest, Lease4GetMissingParams) {

    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by DUID is not supported in v4. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"duid\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Query by duid is not allowed in v4.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"hw-address\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier-type is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-get sanitizes its input.
TEST_F(LeaseCmdsTest, Lease4GetByAddrBadParam) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv4 address specified: 2001:db8:1::1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // This is way off
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"221B Baker St.\""
        "    }\n"
        "}";
    exp_rsp = "Failed to convert string to address '221B Baker St.': Invalid argument";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-get can handle a situation when the query is
// valid, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease4GetByAddrNotFound) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.5\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-get can return a lease by address.
TEST_F(LeaseCmdsTest, Lease4GetByAddr) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Let's check if the response makes any sense.
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", true);
}

// Checks that lease4-get can handle a situation when the query is
// well formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease4GetByHWAddrNotFound) {

    // Initialize lease manager (false = v4, false = don't add a lease)
    initLeaseMgr(false, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-get can find a lease by hardware address.
TEST_F(LeaseCmdsTest, Lease4GetByHWAddr) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"08:08:08:08:08:08\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Let's check if the response makes any sense.
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
}

// Checks that lease6-get(addr) can handle a situation when
// the query is correctly formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease6GetByAddr6NotFound) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"2001:db8:1::10\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-get can handle a situation when the query is
// well formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease4GetByClientIdNotFound) {

    // Initialize lease manager (false = v4, false = don't add a lease)
    initLeaseMgr(false, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"01:02:03:04\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Check that lease4-get can find a lease by client identifier.
TEST_F(LeaseCmdsTest, Lease4GetByClientId) {
    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Let's check if the response makes any sense.
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
}

// Checks that lease6-get rejects queries by client-id.
TEST_F(LeaseCmdsTest, Lease6GetByClientIdInvalidType) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // client-id query is allowed in v4 only.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"01:02:03:04\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Query by client-id is not allowed in v6.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease6-get(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease6GetByDuidNotFound) {
    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"00:01:02:03:04:05:06:07\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease6-get(subnet-id, addr6) can handle a situation when
// the query is correctly formed and the lease is returned.
TEST_F(LeaseCmdsTest, Lease6GetByAddr) {

    initLeaseMgr(true, true); // (true = v6, true = create a lease)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease found.";

    // The status expected is success. The lease should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);

    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Now check that the lease was indeed returned.
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
}

// Checks that lease6-get sanitizes its input.
TEST_F(LeaseCmdsTest, Lease6GetByAddrBadParam) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv6 address specified: 192.0.2.1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // This is way off
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"221B Baker St.\""
        "    }\n"
        "}";
    exp_rsp = "Failed to convert string to address '221B Baker St.': Invalid argument";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease6-get(subnet-id, type, addr6) can handle a situation when
// the query is correctly formed and the lease is returned.
TEST_F(LeaseCmdsTest, Lease6GetByAddrPrefix) {

    // We need to get a prefix lease. We need to create it by hand.
    initLeaseMgr(true, false); // (true = v6, true = create a lease)

    // Let's start with regular address lease and make it a prefix lease.
    Lease6Ptr l = createLease6("2001:db8:1::1", 66, 0x77);
    l->addr_ = IOAddress("2001:db8:1234:ab::");
    l->type_ = Lease::TYPE_PD;
    l->prefixlen_ = 56;
    lmptr_->addLease(l);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"type\": \"IA_PD\","
        "        \"ip-address\": \"2001:db8:1234:ab::\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease found.";

    // The status expected is success. The lease should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);

    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Now check that the lease was indeed returned.
    checkLease6(lease, "2001:db8:1234:ab::", 56, 66, "77:77:77:77:77:77:77:77", false);
}

// Checks that lease6-get(subnet-id, iaid, identifier-type, identifier) can handle
// a situation when the query returns a lease.
TEST_F(LeaseCmdsTest, Lease6GetByDUID) {

    initLeaseMgr(true, true); // (true = v6, true = create a lease)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"iaid\": 42,"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease found.";

    // The status expected is success. The lease should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);

    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Now check that the lease was indeed returned.
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
}

// Checks that lease4-get-all returns all leases.
TEST_F(LeaseCmdsTest, Lease4GetAll) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\"\n"
        "}";
    string exp_rsp = "4 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease4(leases, "192.0.2.1", 44, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.2.2", 44, "09:09:09:09:09:09", true);
    checkLease4(leases, "192.0.3.1", 88, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.3.2", 88, "09:09:09:09:09:09", true);
}

// Checks that lease4-get-all returns empty set if no leases are found.
TEST_F(LeaseCmdsTest, Lease4GetAllNoLeases) {

    // Initialize lease manager (false = v4, false = do not add leasesxs)
    initLeaseMgr(false, false);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\"\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    EXPECT_EQ(0, leases->size());
}


// Checks that lease4-get-all returns all leases for a subnet.
TEST_F(LeaseCmdsTest, Lease4GetAllBySubnetId) {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Query for leases from subnet 44. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 44, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease4(leases, "192.0.2.1", 44, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.2.2", 44, "09:09:09:09:09:09", true);
}

// Checks that lease4-get-all returns empty set when no leases are found.
TEST_F(LeaseCmdsTest, Lease4GetAllBySubnetIdNoLeases) {

    // Initialize lease manager (false = v4, true = do not add leases)
    initLeaseMgr(false, false);

    // Query for leases from subnet 44. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 44, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    EXPECT_EQ(0, leases->size());
}

// Checks that lease4-get-all returns leases from multiple subnets.
TEST_F(LeaseCmdsTest, Lease4GetAllByMultipleSubnetIds) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for leases from subnet 44 and 88.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 44, 88 ]"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease4(leases, "192.0.2.1", 44, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.2.2", 44, "09:09:09:09:09:09", true);
    checkLease4(leases, "192.0.3.1", 88, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.3.2", 88, "09:09:09:09:09:09", true);
}

// Checks that lease4-get-all checks its input arguments.
TEST_F(LeaseCmdsTest, Lease4GetBySubnetIdInvalidArguments) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Subnets not specified in arguments.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {"
        "        \"foo\": 1\n"
        "    }\n"
        "}";
    string exp_rsp = "'subnets' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets are not a list.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": 1\n"
        "    }\n"
        "}";
    exp_rsp = "'subnets' parameter must be a list";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets list must contain numbers.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": [ \"x\", \"y\" ]\n"
        "    }\n"
        "}";
    exp_rsp = "listed subnet identifiers must be numbers";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that multiple calls to lease4-get-pages return all leases.
TEST_F(LeaseCmdsTest, Lease4GetPaged) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Gather all returned addresses to verify that all were returned.
    std::set<std::string> lease_addresses;

    // Keyword start indicates that we want to retrieve the first page.
    std::string last_address = "start";

    // There are 4 leases in the database, so the first two pages should
    // include leases and the 3 page should be empty.
    for (auto i = 0; i < 3; ++i) {
        // Query for a page of leases.
        string cmd =
            "{\n"
            "    \"command\": \"lease4-get-page\",\n"
            "    \"arguments\": {"
            "        \"from\": \"" + last_address + "\","
            "        \"limit\": 2"
            "    }"
            "}";

        // For the first two pages we shuould get success. For the last
        // one an empty status code.
        ConstElementPtr rsp;
        if (i < 2) {
            string exp_rsp = "2 IPv4 lease(s) found.";
            rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        } else {
            string exp_rsp = "0 IPv4 lease(s) found.";
            rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

        }

        // Now check that the lease parameters were indeed returned.
        ASSERT_TRUE(rsp);

        // Arguments must exist.
        ConstElementPtr args = rsp->get("arguments");
        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // For convenience, we return the number of returned leases,
        // so as the client can check whether there was anything returned
        // before parsing the leases structure.
        ConstElementPtr page_count = args->get("count");
        ASSERT_TRUE(page_count);
        ASSERT_EQ(Element::integer, page_count->getType());

        // leases must exist, but may be empty.
        ConstElementPtr leases = args->get("leases");
        ASSERT_TRUE(leases);
        ASSERT_EQ(Element::list, leases->getType());

        if (!leases->empty()) {
            EXPECT_EQ(2, page_count->intValue());

            // Go over each lease and verify its correctness.
            for (ConstElementPtr lease : leases->listValue()) {
                ASSERT_EQ(Element::map, lease->getType());
                ASSERT_TRUE(lease->contains("ip-address"));
                ConstElementPtr ip_address = lease->get("ip-address");
                ASSERT_EQ(Element::string, ip_address->getType());
                last_address = ip_address->stringValue();

                lease_addresses.insert(last_address);

                // The easiest way to retrieve the subnet id and HW address is to
                // ask the Lease Manager.
                Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(IOAddress(last_address));
                ASSERT_TRUE(from_mgr);
                checkLease4(leases, last_address, from_mgr->subnet_id_,
                            from_mgr->hwaddr_->toText(false), true);
            }

        } else {
            // In the third iteration the page should be empty.
            EXPECT_EQ(0, page_count->intValue());
        }
    }

    // Check if all addresses were returned.
    EXPECT_EQ(1, lease_addresses.count("192.0.2.1"));
    EXPECT_EQ(1, lease_addresses.count("192.0.2.2"));
    EXPECT_EQ(1, lease_addresses.count("192.0.3.1"));
    EXPECT_EQ(1, lease_addresses.count("192.0.3.2"));
}

// Verifies that first page of IPv4 leases can be retrieved by specifying
// zero IPv4 address.
TEST_F(LeaseCmdsTest, Lease4GetPagedZeroAddress) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"0.0.0.0\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "2 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Verifies that IPv6 address as a start address is rejected.
TEST_F(LeaseCmdsTest, Lease4GetPagedIPv4Address) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"2001:db8::1\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value 2001:db8::1 is not an IPv4 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease6-get-all returns all leases.
TEST_F(LeaseCmdsTest, Lease6GetAll) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\"\n"
        "}";
    string exp_rsp = "4 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease6(leases, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:1::2", 0, 66, "56:56:56:56:56:56:56:56", false);
    checkLease6(leases, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:2::2", 0, 99, "56:56:56:56:56:56:56:56", false);
}

// Checks that lease6-get-all returns empty set if no leases are found.
TEST_F(LeaseCmdsTest, Lease6GetAllNoLeases) {

    // Initialize lease manager (true = v6, false = do not add leasesxs)
    initLeaseMgr(true, false);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\"\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    EXPECT_EQ(0, leases->size());
}


// Checks that lease6-get-all returns all leases for a subnet.
TEST_F(LeaseCmdsTest, Lease6GetAllBySubnetId) {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for leases from subnet 66. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 66, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease6(leases, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:1::2", 0, 66, "56:56:56:56:56:56:56:56", false);
}

// Checks that lease6-get-all returns empty set when no leases are found.
TEST_F(LeaseCmdsTest, Lease6GetAllBySubnetIdNoLeases) {

    // Initialize lease manager (true = v6, true = do not add leases)
    initLeaseMgr(true, false);

    // Query for leases from subnet 66. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 66, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    EXPECT_EQ(0, leases->size());
}

// Checks that lease6-get-all returns leases from multiple subnets.
TEST_F(LeaseCmdsTest, Lease6GetAllByMultipleSubnetIds) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for leases from subnet 66 and 99.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 66, 99 ]"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease6(leases, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:1::2", 0, 66, "56:56:56:56:56:56:56:56", false);
    checkLease6(leases, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:2::2", 0, 99, "56:56:56:56:56:56:56:56", false);
}

// Checks that lease6-get-all checks its input arguments.
TEST_F(LeaseCmdsTest, Lease6GetBySubnetIdInvalidArguments) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Subnets not specified in arguments.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {"
        "        \"foo\": 1\n"
        "    }\n"
        "}";
    string exp_rsp = "'subnets' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets are not a list.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": 1\n"
        "    }\n"
        "}";
    exp_rsp = "'subnets' parameter must be a list";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets list must contain numbers.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": [ \"x\", \"y\" ]\n"
        "    }\n"
        "}";
    exp_rsp = "listed subnet identifiers must be numbers";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that multiple calls to lease6-get-page return all leases.
TEST_F(LeaseCmdsTest, Lease6GetPaged) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Gather all returned addresses to verify that all were returned.
    std::set<std::string> lease_addresses;

    // Keyword start indicates that we want to retrieve the first page.
    std::string last_address = "start";

    // There are 4 leases in the database, so the first two pages should
    // include leases and the 3 page should be empty.
    for (auto i = 0; i < 3; ++i) {
        // Query for a page of leases.
        string cmd =
            "{\n"
            "    \"command\": \"lease6-get-page\",\n"
            "    \"arguments\": {"
            "        \"from\": \"" + last_address + "\","
            "        \"limit\": 2"
            "    }"
            "}";

        // For the first two pages we shuould get success. For the last
        // one an empty status code.
        ConstElementPtr rsp;
        if (i < 2) {
            string exp_rsp = "2 IPv6 lease(s) found.";
            rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        } else {
            string exp_rsp = "0 IPv6 lease(s) found.";
            rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

        }

        // Now check that the lease parameters were indeed returned.
        ASSERT_TRUE(rsp);

        // Arguments must exist.
        ConstElementPtr args = rsp->get("arguments");
        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // For convenience, we return the number of returned leases,
        // so as the client can check whether there was anything returned
        // before parsing the leases structure.
        ConstElementPtr page_count = args->get("count");
        ASSERT_TRUE(page_count);
        ASSERT_EQ(Element::integer, page_count->getType());

        // leases must exist, but may be empty.
        ConstElementPtr leases = args->get("leases");
        ASSERT_TRUE(leases);
        ASSERT_EQ(Element::list, leases->getType());

        if (!leases->empty()) {
            EXPECT_EQ(2, page_count->intValue());

            // Go over each lease and verify its correctness.
            for (ConstElementPtr lease : leases->listValue()) {
                ASSERT_EQ(Element::map, lease->getType());
                ASSERT_TRUE(lease->contains("ip-address"));
                ConstElementPtr ip_address = lease->get("ip-address");
                ASSERT_EQ(Element::string, ip_address->getType());
                last_address = ip_address->stringValue();

                lease_addresses.insert(last_address);

                // The easiest way to retrieve the subnet id and HW address is to
                // ask the Lease Manager.
                Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                                           IOAddress(last_address));
                ASSERT_TRUE(from_mgr);
                checkLease6(leases, last_address, 0, from_mgr->subnet_id_,
                            from_mgr->duid_->toText(), false);
            }

        } else {
            // In the third iteration the page should be empty.
            EXPECT_EQ(0, page_count->intValue());
        }
    }

    // Check if all addresses were returned.
    EXPECT_EQ(1, lease_addresses.count("2001:db8:1::1"));
    EXPECT_EQ(1, lease_addresses.count("2001:db8:1::2"));
    EXPECT_EQ(1, lease_addresses.count("2001:db8:2::1"));
    EXPECT_EQ(1, lease_addresses.count("2001:db8:2::2"));
}

// Verifies that first page of IPv6 leases can be retrieved by specifying
// zero IPv6 address.
TEST_F(LeaseCmdsTest, Lease6GetPagedZeroAddress) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"::\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "2 IPv6 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

// Verifies that IPv4 address as a start address is rejected.
TEST_F(LeaseCmdsTest, Lease6GetPagedIPv4Address) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"192.0.2.3\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value 192.0.2.3 is not an IPv6 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verifies that value of 'from' parameter other than 'start' or an IPv6
// address is rejected.
TEST_F(LeaseCmdsTest, Lease6GetPagedInvalidFrom) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"foo\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value is neither 'start' keyword "
        "nor a valid IPv6 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verifies that limit is mandatory.
TEST_F(LeaseCmdsTest, Lease6GetPagedNoLimit) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\""
        "    }"
        "}";

    string exp_rsp = "'limit' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verifies that the limit must be a number.
TEST_F(LeaseCmdsTest, Lease6GetPagedLimitNotNumber) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": false"
        "    }"
        "}";

    string exp_rsp = "'limit' parameter must be a number";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verifies that the limit of 0 is rejected.
TEST_F(LeaseCmdsTest, Lease6GetPagedLimitIsZero) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": 0"
        "    }"
        "}";

    string exp_rsp = "page size of retrieved leases must not be 0";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-get-by-hw-address can handle a situation when
// the query is broken (required parameter is missing).
TEST_F(LeaseCmdsTest, LeaseGetByHwAddressParams) {

    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'hw-address' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hw-address must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'hw-address'parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Simply bad value.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": \"00::01:00:bc:0d:67\"\n"
        "    }\n"
        "}";
    exp_rsp = "two consecutive separators (':') specified in a decoded string";
    exp_rsp += " '00::01:00:bc:0d:67'";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-get-by-hw-address works as expected (find no lease).
TEST_F(LeaseCmdsTest, LeaseGetByHwAddressFind0) {
    // Initialize lease manager (false = v4, false = don't add a lease)
    initLeaseMgr(false, false);

    // No such leasea.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-get-by-hw-address works as expected (find two leases).
TEST_F(LeaseCmdsTest, LeaseGetByHwAddressFind2) {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": \"08:08:08:08:08:08\"\n"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr map = rsp->get("arguments");
    ASSERT_TRUE(map);
    ASSERT_EQ(Element::map, map->getType());
    ConstElementPtr leases = map->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());
    ASSERT_EQ(2, leases->size());

    // Let's check if the response makes any sense.
    ConstElementPtr lease = leases->get(0);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
    lease = leases->get(1);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.3.1", 88, "08:08:08:08:08:08", false);
}

// Checks that lease4-get-by-client-id can handle a situation when
// the query is broken (required parameter is missing).
TEST_F(LeaseCmdsTest, LeaseGetByClientIdParams) {

    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'client-id' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // client-id must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'client-id'parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Simply bad value.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": \"00::01:00:bc:0d:67\"\n"
        "    }\n"
        "}";
    exp_rsp = "two consecutive separators (':') specified in a decoded string";
    exp_rsp += " '00::01:00:bc:0d:67'";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-get-by-client-id works as expected (find no lease).
TEST_F(LeaseCmdsTest, LeaseGetByClientIdFind0) {
    // Initialize lease manager (false = v4, false = don't add a lease)
    initLeaseMgr(false, false);

    // No such leasea.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": \"01:02:03:04\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-get-by-client-id works as expected (find two leases).
TEST_F(LeaseCmdsTest, LeaseGetByClientIdFind2) {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr map = rsp->get("arguments");
    ASSERT_TRUE(map);
    ASSERT_EQ(Element::map, map->getType());
    ConstElementPtr leases = map->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());
    ASSERT_EQ(2, leases->size());

    // Let's check if the response makes any sense.
    ConstElementPtr lease = leases->get(0);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
    lease = leases->get(1);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.3.1", 88, "08:08:08:08:08:08", false);
}

// Checks that lease6-get-by-duid can handle a situation when
// the query is broken (required parameter is missing).
TEST_F(LeaseCmdsTest, LeaseGetByDuidParams) {

    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'duid' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // duid must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'duid'parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Simply bad value.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": \"00::01:00:bc:0d:67\"\n"
        "    }\n"
        "}";
    exp_rsp = "two consecutive separators (':') specified in a decoded string";
    exp_rsp += " '00::01:00:bc:0d:67'";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease6-get-by-duid works as expected (find no lease).
TEST_F(LeaseCmdsTest, LeaseGetByDuidFind0) {
    // Initialize lease manager (true = v6, false = don't add a lease)
    initLeaseMgr(true, false);

    // No such leasea.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": \"00:01:02:03:04:05:06:07\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease6-get-by-duid works as expected (find two leases).
TEST_F(LeaseCmdsTest, LeaseGetByDuidFind2) {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr map = rsp->get("arguments");
    ASSERT_TRUE(map);
    ASSERT_EQ(Element::map, map->getType());
    ConstElementPtr leases = map->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());
    ASSERT_EQ(2, leases->size());

    // Let's check if the response makes any sense.
    ConstElementPtr lease = leases->get(0);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    lease = leases->get(1);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
}

// Checks that lease4-get-by-hostname can handle a situation when
// the query is broken (required parameter is missing).
TEST_F(LeaseCmdsTest, Lease4GetByHostnameParams) {

    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'hostname' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname'parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be not empty.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"\"\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname' parameter is empty";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-get-by-hostname works as expected (find no lease).
TEST_F(LeaseCmdsTest, Lease4GetByHostnameFind0) {
    // Initialize lease manager (false = v4, false = don't add a lease)
    initLeaseMgr(false, false);

    // No such leasea.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo.bar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-get-by-hostname works as expected (find two leases).
TEST_F(LeaseCmdsTest, Lease4GetByHostnameFind2) {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"Myhost.Example.Com.\"\n"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv4 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr map = rsp->get("arguments");
    ASSERT_TRUE(map);
    ASSERT_EQ(Element::map, map->getType());
    ConstElementPtr leases = map->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());
    ASSERT_EQ(4, leases->size());

    // Let's check if the response makes any sense.
    ConstElementPtr lease = leases->get(0);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
    lease = leases->get(2);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.3.1", 88, "08:08:08:08:08:08", false);
}

// Checks that lease6-get-by-hostname can handle a situation when
// the query is broken (required parameter is missing).
TEST_F(LeaseCmdsTest, Lease6GetByHostnameParams) {

    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'hostname' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname'parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be not empty.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"\"\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname' parameter is empty";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease6-get-by-hostname works as expected (find no lease).
TEST_F(LeaseCmdsTest, Lease6GetByHostnameFind0) {
    // Initialize lease manager (true = v6, false = don't add a lease)
    initLeaseMgr(true, false);

    // No such leasea.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo.bar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease6-get-by-hostname works as expected (find two leases).
TEST_F(LeaseCmdsTest, Lease6GetByHostnameFind2) {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"Myhost.Example.Com.\"\n"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr map = rsp->get("arguments");
    ASSERT_TRUE(map);
    ASSERT_EQ(Element::map, map->getType());
    ConstElementPtr leases = map->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());
    ASSERT_EQ(4, leases->size());

    // Let's check if the response makes any sense.
    ConstElementPtr lease = leases->get(0);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    lease = leases->get(2);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
}

// Test checks if lease4-update handler refuses calls with missing parameters.
TEST_F(LeaseCmdsTest, Lease4UpdateMissingParams) {
    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Everything missing. What sort of crap is that?
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and hwaddr missing, although
    // Kea can now figure out subnet-id on its own).
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "            \"ip-address\": \"192.0.2.123\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Better, but still no luck. (hwaddr missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Close, but no cigars. (ip-address missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verify that lease4-update can be rejected if parameters are specified, but
// have incorrect values.
TEST_F(LeaseCmdsTest, Lease4UpdateBadParams) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv4 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // This time the new IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"10.0.0.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "The address 10.0.0.1 does not belong to subnet 192.0.2.0/24, subnet-id=44";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // We don't use any of that bleeding edge nonsense in this museum. v4 only.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv4 address specified: 2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that lease4-update correctly handles case when there is
// no lease to be updated.
TEST_F(LeaseCmdsTest, Lease4UpdateNoLease) {

    // Initialize lease manager (false = v4, false = don't add any lease)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 192.0.2.1 - no such lease";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that a lease4 can be updated. We're changing hw-address
// and a hostname.
TEST_F(LeaseCmdsTest, Lease4Update) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

// Check that a lease4 can be updated. We're changing hw-address
// and a hostname. The subnet-id is not specified.
TEST_F(LeaseCmdsTest, Lease4UpdateNoSubnetId) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

// Check that a lease4 is created if it doesn't exist during the update.
// To trigger this behavior 'force-create' boolean parameter must be
// included in the command.
TEST_F(LeaseCmdsTest, Lease4UpdateForceCreate) {
    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it contains expected values..
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

// Check that a lease4 is created if it doesn't exist during the update.
// To trigger this behavior 'force-create' boolean parameter must be
// included in the command. The subnet-id is not specified, Kea will
// figure it out.
TEST_F(LeaseCmdsTest, Lease4UpdateForceCreateNoSubnetId) {
    // Initialize lease manager (false = v4, false = don't add any lease)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure the subnet-id is figured out correctly.
    EXPECT_EQ(44, l->subnet_id_);

    // Make sure it contains expected values..
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

// Check that lease4-update correctly handles case when the 'force-create'
// parameter is explicitly set to false.
TEST_F(LeaseCmdsTest, Lease4UpdateDoNotForceCreate) {

    // Initialize lease manager (false = v4, false = don't add any lease)
    initLeaseMgr(false, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": false"
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 192.0.2.1 - no such lease";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that a lease4 can be updated. We're adding a comment and an user
// context.
TEST_F(LeaseCmdsTest, Lease4UpdateComment) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"42:42:42:42:42:42:42:42\",\n"
        "        \"comment\": \"a comment\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("42:42:42:42:42:42:42:42", l->hwaddr_->toText(false));

    // Check user context.
    ConstElementPtr ctx = l->getContext();
    ASSERT_TRUE(ctx);
    EXPECT_EQ(2, ctx->size());
    ASSERT_TRUE(ctx->contains("comment"));
    EXPECT_EQ("\"a comment\"", ctx->get("comment")->str());
    ASSERT_TRUE(ctx->contains("foobar"));
    EXPECT_EQ("true", ctx->get("foobar")->str());
}

// Test checks if lease6-update handler refuses calls with missing parameters.
TEST_F(LeaseCmdsTest, Lease6UpdateMissingParams) {
    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Everything missing. What sort of crap is that?
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and duid missing, although
    // kea should be able to figure out the subnet-id on its own.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "            \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Better, but still no luck. (duid missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // ip-address and identifier-type missing.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"duid\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Verify that lease6-update can be rejected if parameters are specified, but
// have incorrect values.
TEST_F(LeaseCmdsTest, Lease6UpdateBadParams) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv6 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // This time the new IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"3000::1\",\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\"\n"
        "    }\n"
        "}";
    exp_rsp = "The address 3000::1 does not belong to subnet 2001:db8:1::/48, subnet-id=66";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Nope, can't do v4 address in v6 lease.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\"\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv6 address specified: 192.0.2.1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that a lease6 can be updated. We're changing hw-address
// and a hostname.
TEST_F(LeaseCmdsTest, Lease6Update) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

// Check that a lease6 can be updated. We're changing hw-address
// and a hostname. The subnet-id is not specified.
TEST_F(LeaseCmdsTest, Lease6UpdateNoSubnetId) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the subnet-id is correct.
    EXPECT_EQ(66, l->subnet_id_);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}


// Check that a lease6 can be updated. We're adding a comment and an user
// context.
TEST_F(LeaseCmdsTest, Lease6UpdateComment) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 42,\n"
        "        \"duid\": \"42:42:42:42:42:42:42:42\",\n"
        "        \"comment\": \"a comment\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);

    // Check user context.
    ConstElementPtr ctx = l->getContext();
    ASSERT_TRUE(ctx);
    EXPECT_EQ(2, ctx->size());
    ASSERT_TRUE(ctx->contains("comment"));
    EXPECT_EQ("\"a comment\"", ctx->get("comment")->str());
    ASSERT_TRUE(ctx->contains("foobar"));
    EXPECT_EQ("true", ctx->get("foobar")->str());
}


// Check that lease6-update correctly handles case when there is
// no lease to be updated.
TEST_F(LeaseCmdsTest, Lease6UpdateNoLease) {

    // Initialize lease manager (true = v6, false = don't add any lease)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 2001:db8:1::1 - no such lease";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Check that a lease6 is created if it doesn't exist during the update.
// To trigger this behavior 'force-create' boolean parameter must be
// included in the command.
TEST_F(LeaseCmdsTest, Lease6UpdateForceCreate) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease is correct.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

// Check that a lease6 is created if it doesn't exist during the update.
// To trigger this behavior 'force-create' boolean parameter must be
// included in the command. The subnet-id is not specified, Kea will
// figure it out.
TEST_F(LeaseCmdsTest, Lease6UpdateForceCreateNoSubnetId) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the subnet-id is figured out correctly.
    EXPECT_EQ(66, l->subnet_id_);

    // Make sure the lease is correct.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

// Check that lease6-update correctly handles case when the 'force-create'
// parameter is explicitly set to false.
TEST_F(LeaseCmdsTest, Lease6UpdateDoNotForceCreate) {

    // Initialize lease manager (true = v6, false = don't add any lease)
    initLeaseMgr(true, false);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": false"
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 2001:db8:1::1 - no such lease";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease6-del can handle a situation when the query is
// broken (some required parameters are missing).
TEST_F(LeaseCmdsTest, Lease4DelMissingParams) {

    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by DUID is not supported in v4. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"duid\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Delete by duid is not allowed in v4.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"hw-address\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier-type is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-del can handle a situation when the query is
// valid, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease4DelByAddrNotFound) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.5\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-del can return a lease by address.
TEST_F(LeaseCmdsTest, Lease4DelByAddr) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease deleted.";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}


// Checks that lease4-del sanitizes its input.
TEST_F(LeaseCmdsTest, Lease4DelByAddrBadParam) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv4 address specified: 2001:db8:1::1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // This is way off
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"221B Baker St.\""
        "    }\n"
        "}";
    exp_rsp = "Failed to convert string to address '221B Baker St.': Invalid argument";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease4-del can handle a situation when the query is
// well formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease4DelByHWAddrNotFound) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

// Checks that lease4-del can find a lease by hardware address.
TEST_F(LeaseCmdsTest, Lease4DelByHWAddr) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"08:08:08:08:08:08\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease deleted.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

// Checks that lease4-del can handle a situation when the query is
// well formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease4DelByClientIdNotFound) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"01:02:03:04\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

// Checks that lease4-del can find and delete a lease by client identifier.
TEST_F(LeaseCmdsTest, Lease4DelByClientId) {
    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease deleted.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

// Checks that lease6-del(addr) can handle a situation when
// the query is correctly formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease6DelByAddr6NotFound) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"2001:db8:1::10\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease6-del(subnet-id, addr) can handle a situation when
// the query is correctly formed, but the lease is not there.
TEST_F(LeaseCmdsTest, Lease6DelByDuidNotFound) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"00:01:02:03:04:05:06:07\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

// Checks that lease6-del(subnet-id, addr6) can handle a situation when
// the query is correctly formed and the lease is returned.
TEST_F(LeaseCmdsTest, Lease6DelByAddr) {

    initLeaseMgr(true, true); // (true = v6, true = create a lease)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease deleted.";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

// Checks that lease6-del sanitizes its input.
TEST_F(LeaseCmdsTest, Lease6DelByAddrBadParam) {

    // Initialize lease manager (true = v6, true = add a lease)
    initLeaseMgr(true, true);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv6 address specified: 192.0.2.1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // This is way off
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"221B Baker St.\""
        "    }\n"
        "}";
    exp_rsp = "Failed to convert string to address '221B Baker St.': Invalid argument";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

// Checks that lease6-del(subnet-id, type, addr6) can handle a situation when
// the query is correctly formed and the lease is deleted.
TEST_F(LeaseCmdsTest, Lease6DelByAddrPrefix) {

    initLeaseMgr(true, false); // (true = v6, false = don't add any leases)

    // Let's start with regular address lease and make it a prefix lease.
    Lease6Ptr l = createLease6("2001:db8:1::1", 66, 0x77);
    l->addr_ = IOAddress("2001:db8:1234:ab::");
    l->type_ = Lease::TYPE_PD;
    l->prefixlen_ = 56;
    lmptr_->addLease(l);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"type\": \"IA_PD\","
        "        \"ip-address\": \"2001:db8:1234:ab::\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease deleted.";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:1234:ab::")));
}

// Checks that lease6-del(subnet-id, iaid, identifier-type, identifier) can handle
// a situation when the query finds a lease.
TEST_F(LeaseCmdsTest, Lease6DelByDUID) {

    initLeaseMgr(true, true); // (true = v6, true = create a lease)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"iaid\": 42,"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease deleted.";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

// Checks that lease4-wipe can remove leases.
TEST_F(LeaseCmdsTest, Lease4Wipe) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 2 IPv4 lease(s) from subnet(s) 44";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

// Checks that lease4-wipe can remove leases from all subnets
// at once.
TEST_F(LeaseCmdsTest, Lease4WipeAll) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 4 IPv4 lease(s) from subnet(s) 44 88";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are gone, too.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

// Checks that lease4-wipe can remove leases from all subnets
// at once (when no parameters are specifed).
TEST_F(LeaseCmdsTest, Lease4WipeAllNoArgs) {

    // Initialize lease manager (false = v4, true = add a lease)
    initLeaseMgr(false, true);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\"\n"
        "}";
    string exp_rsp = "Deleted 4 IPv4 lease(s) from subnet(s) 44 88";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are gone, too.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

// Checks that lease4-wipe properly reports when no leases were deleted.
TEST_F(LeaseCmdsTest, Lease4WipeNoLeases) {

    // Initialize lease manager (false = v4, false = no leases)
    initLeaseMgr(false, false);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv4 lease(s) from subnet(s) 44";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-wipe properly reports when no leases were deleted.
TEST_F(LeaseCmdsTest, Lease4WipeNoLeasesAll) {

    // Initialize lease manager (false = v4, false = no leases)
    initLeaseMgr(false, false);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv4 lease(s) from subnet(s) 44 88";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-wipe can remove leases.
TEST_F(LeaseCmdsTest, Lease6Wipe) {

    initLeaseMgr(true, true); // (true = v6, true = create a lease)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66\n"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 2 IPv6 lease(s) from subnet(s) 66";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // The leases in subnet 88 are supposed to be still there.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

// Checks that lease4-wipe can remove leases from all subnets
TEST_F(LeaseCmdsTest, Lease6WipeAll) {

    initLeaseMgr(true, true); // (true = v6, true = create a lease)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0\n"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 4 IPv6 lease(s) from subnet(s) 66 99";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // The leases in subnet 88 are supposed to be still there.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

// Checks that lease4-wipe can remove leases from all subnets
// (no arguments)
TEST_F(LeaseCmdsTest, Lease6WipeAllNoArgs) {

    initLeaseMgr(true, true); // (true = v6, true = create a lease)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\"\n"
        "}";
    string exp_rsp = "Deleted 4 IPv6 lease(s) from subnet(s) 66 99";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // The leases in subnet 88 are supposed to be still there.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

// Checks that lease4-wipe properly reports when no leases were deleted.
TEST_F(LeaseCmdsTest, Lease6WipeNoLeases) {

    // Initialize lease manager (false = v4, false = no leases)
    initLeaseMgr(true, false);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv6 lease(s) from subnet(s) 66";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that lease4-wipe properly reports when no leases were deleted.
TEST_F(LeaseCmdsTest, Lease6WipeNoLeasesAll) {

    // Initialize lease manager (false = v4, false = no leases)
    initLeaseMgr(true, false);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv6 lease(s) from subnet(s) 66 99";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

// Checks that an attempt to update a lease (set incorrect subnet-id)
// will fail.
TEST_F(LeaseCmdsTest, brokenUpdate) {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Set the sanity checks level.
    CfgMgr::instance().getCurrentCfg()->getConsistency()
        ->setLeaseSanityCheck(CfgConsistency::LEASE_CHECK_FIX);

    // Check that the lease manager pointer is there.
    ASSERT_TRUE(lmptr_);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 444,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "        ,\"force-create\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv4 subnet with "
                     "subnet-id=444 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

// This test verifies that it is possible to add two leases and delete
// two leases as a result of the single lease6-bulk-apply command.
TEST_F(LeaseCmdsTest, Lease6BulkApply) {

    initLeaseMgr(true, true); // (true = v6, true = create leases)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::1\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::2\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ],"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 99,\n"
        "                \"ip-address\": \"2001:db8:2::123\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 4 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));

    // Check that the leases we deleted are gone,
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

// This test verifies that it is possible to send new leases only
// with the lease6-bulk-apply.
TEST_F(LeaseCmdsTest, Lease6BulkApplyAddsOnly) {

    initLeaseMgr(true, false); // (true = v6, true = create leases)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 99,\n"
        "                \"ip-address\": \"2001:db8:2::123\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));
}

// This test verifies that it is possible to update leases with
// the lease6-bulk-apply.
TEST_F(LeaseCmdsTest, Lease6BulkApplyUpdatesOnly) {

    initLeaseMgr(true, true); // (true = v6, true = create leases)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::1\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::2\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    //  Check that the leases we inserted are stored.
    Lease6Ptr lease1 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    Lease6Ptr lease2 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"));
    ASSERT_TRUE(lease1);
    ASSERT_TRUE(lease2);

    // The IAIDs should have been updated for the existing leases.
    EXPECT_EQ(1234, lease1->iaid_);
    EXPECT_EQ(1234, lease2->iaid_);
}

// This test verifies that it is possible to only delete leases
// with the lease6-bulk-apply.
TEST_F(LeaseCmdsTest, Lease6BulkApplyDeletesOnly) {

    initLeaseMgr(true, true); // (true = v6, true = create leases)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::1\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::2\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Check that the leases we deleted are gone,
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

// This test verifies that deleting non existing leases returns an
// 'empty' result.
TEST_F(LeaseCmdsTest, Lease6BulkApplyDeleteNonExiting) {

    initLeaseMgr(true, true); // (true = v6, true = create leases)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::123\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::234\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 0 IPv6 leases completed.";

    // The status expected is success.
    auto resp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
    ASSERT_TRUE(resp);
    ASSERT_EQ(Element::map, resp->getType());

    auto args = resp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    auto failed_deleted_leases = args->get("failed-deleted-leases");
    ASSERT_TRUE(failed_deleted_leases);
    ASSERT_EQ(Element::list, failed_deleted_leases->getType());
    ASSERT_EQ(2, failed_deleted_leases->size());

    {
        SCOPED_TRACE("lease address 2001:db8:1::123");
        checkFailedLease(failed_deleted_leases, "IA_NA", "2001:db8:1::123",
                         CONTROL_RESULT_EMPTY, "lease not found");
    }

    {
        SCOPED_TRACE("lease address 2001:db8:1::234");
        checkFailedLease(failed_deleted_leases, "IA_NA", "2001:db8:1::234",
                         CONTROL_RESULT_EMPTY, "lease not found");
    }
}

// Check that changes for other leases are not applied if one of
// the leases is malformed.
TEST_F(LeaseCmdsTest, Lease6BulkApplyRollback) {

    initLeaseMgr(true, true); // (true = v6, true = create leases)

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::1\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::2\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ],"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\","
        "                \"duid\": \"11:11:11:11:11:11\","
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": -1,"
        "                \"ip-address\": \"2001:db8:2::123\","
        "                \"duid\": \"22:22:22:22:22:22\","
        "                \"iaid\": 1234"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "out of range value (-1) specified for parameter 'subnet-id' (<string>:5:57)";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));

    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}


} // end of anonymous namespace
