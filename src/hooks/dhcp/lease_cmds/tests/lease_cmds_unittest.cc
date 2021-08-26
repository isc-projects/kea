// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
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
#include <stats/stats_mgr.h>
#include <testutils/user_context_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

#include <errno.h>
#include <set>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::asiolink;
using namespace isc::stats;
using namespace isc::test;
namespace ph = std::placeholders;

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

    /// @brief Verify that NameChangeRequest holds valid values.
    ///
    /// This function picks first NameChangeRequest from the internal server's
    /// queue and checks that it holds valid parameters. The NameChangeRequest
    /// is removed from the queue.
    ///
    /// @param type An expected type of the NameChangeRequest (Add or Remove).
    /// @param reverse An expected setting of the reverse update flag.
    /// @param forward An expected setting of the forward update flag.
    /// @param addr A string representation of the IPv6 address held in the
    /// NameChangeRequest.
    /// @param fqdn The expected string value of the FQDN, if blank the
    /// check is skipped
    void verifyNameChangeRequest(const isc::dhcp_ddns::NameChangeType type,
                                 const bool reverse, const bool forward,
                                 const std::string& addr,
                                 const std::string& fqdn = "") {
        NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = CfgMgr::instance().getD2ClientMgr().peekAt(0));
        ASSERT_TRUE(ncr);

        EXPECT_EQ(type, ncr->getChangeType());
        EXPECT_EQ(forward, ncr->isForwardChange());
        EXPECT_EQ(reverse, ncr->isReverseChange());
        EXPECT_EQ(addr, ncr->getIpAddress());

        if (!fqdn.empty()) {
           EXPECT_EQ(fqdn, ncr->getFqdn());
        }

        // Process the message off the queue
        ASSERT_NO_THROW(CfgMgr::instance().getD2ClientMgr().runReadyIO());
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

    /// @brief Reference to the D2 client manager.
    D2ClientMgr& d2_mgr_;

    /// @brief Constructor
    ///
    /// Sets the library filename and clears the lease manager pointer.
    /// Also ensured there is no lease manager leftovers from previous
    /// test.
    LeaseCmdsTest()
        :LibLoadTest(LEASE_CMDS_LIB_SO),
        d2_mgr_(CfgMgr::instance().getD2ClientMgr()) {
        LeaseMgrFactory::destroy();
        enableD2();
        lmptr_ = 0;
        StatsMgr::instance().removeAll();
    }

    /// @brief Destructor
    ///
    /// Removes library (if any), destroys lease manager (if any).
    virtual ~LeaseCmdsTest() {
        // destroys lease manager first because the other order triggers
        // a clang/boost bug
        LeaseMgrFactory::destroy();
        disableD2();
        unloadLibs();
        lmptr_ = 0;
        StatsMgr::instance().removeAll();
    }

    /// @brief Initializes lease manager (and optionally populates it with a lease)
    ///
    /// Creates a lease manager (memfile, trimmed down to keep everything in memory
    /// only) and optionally can create a lease, which is useful for leaseX-get and
    /// leaseX-del type of tests. For lease details, see @ref createLease4 and
    /// @ref createLease6.
    ///
    /// @param v6 true = v6, false = v4
    /// @param insert_lease governs whether a lease should be pre-inserted
    /// @param declined governs whether a lease should be in declined state
    void initLeaseMgr(bool v6, bool insert_lease, bool declined = false) {

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
                lmptr_->addLease(createLease6("2001:db8:1::1", 66, 0x42, declined));
                lmptr_->addLease(createLease6("2001:db8:1::2", 66, 0x56, declined));
                lmptr_->addLease(createLease6("2001:db8:2::1", 99, 0x42, declined));
                lmptr_->addLease(createLease6("2001:db8:2::2", 99, 0x56, declined));
                if (declined) {
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 66, "declined-addresses"),
                        int64_t(2));
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 99, "declined-addresses"),
                        int64_t(2));
                } else {
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 66, "declined-addresses"),
                        int64_t(0));
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 99, "declined-addresses"),
                        int64_t(0));
                }
                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", 66, "assigned-nas" ),
                    int64_t(2));
                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", 99, "assigned-nas" ),
                    int64_t(2));
            } else {
                lmptr_->addLease(createLease4("192.0.2.1", 44, 0x08, 0x42, declined));
                lmptr_->addLease(createLease4("192.0.2.2", 44, 0x09, 0x56, declined));
                lmptr_->addLease(createLease4("192.0.3.1", 88, 0x08, 0x42, declined));
                lmptr_->addLease(createLease4("192.0.3.2", 88, 0x09, 0x56, declined));
                if (declined) {
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 44, "declined-addresses"),
                        int64_t(2));
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 88, "declined-addresses"),
                        int64_t(2));
                } else {
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 44, "declined-addresses"),
                        int64_t(0));
                    StatsMgr::instance().setValue(
                        StatsMgr::generateName("subnet", 88, "declined-addresses"),
                        int64_t(0));
                }
                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", 44, "assigned-addresses"),
                    int64_t(2));
                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", 88, "assigned-addresses"),
                    int64_t(2));
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
    /// @param declined controls whether the lease should be in declined state.
    ///
    /// @return Returns the lease created
    Lease4Ptr createLease4(const std::string& ip_address,
                           const SubnetID& subnet_id,
                           const uint8_t hw_address_pattern,
                           const uint8_t client_id_pattern,
                           bool declined = false) {
        Lease4Ptr lease(new Lease4());

        lease->addr_ = IOAddress(ip_address);

        // Set other parameters.  For historical reasons, address 0 is not used.
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, hw_address_pattern), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, client_id_pattern)));
        // Purposely using high cltt and valid lifetime to test that
        // expiration time is cast properly.
        lease->valid_lft_ = HIGH_VALID_LIFETIME; // Very high valid lifetime
        lease->cltt_ = DEC_2030_TIME; // December 11th 2030
        lease->updateCurrentExpirationTime();
        if (declined) {
            lease->state_ = Lease::STATE_DECLINED;
        }
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
    /// @param declined controls whether the lease should be in declined state.
    ///
    /// @return Returns the lease created
    Lease6Ptr createLease6(const std::string& ip_address,
                           const SubnetID& subnet_id,
                           const uint8_t duid_pattern,
                           bool declined = false) {
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
        lease->updateCurrentExpirationTime();
        if (declined) {
            lease->state_ = Lease::STATE_DECLINED;
        }
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

    /// @brief Enables DHCP-DDNS updates.
    void enableD2() {
        D2ClientConfigPtr cfg(new D2ClientConfig());
        ASSERT_NO_THROW(cfg->enableUpdates(true));
        ASSERT_NO_THROW(CfgMgr::instance().setD2ClientConfig(cfg));
        d2_mgr_.startSender(std::bind(&LeaseCmdsTest::d2ErrorHandler, this,
                                      ph::_1, ph::_2));
    }

    /// @brief Disables DHCP-DDNS updates.
    void disableD2() {
        d2_mgr_.stopSender();
        // Default constructor creates a config with DHCP-DDNS updates
        // disabled.
        D2ClientConfigPtr cfg(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(cfg);
    }

    /// @brief No-op error handler for D2.
    void d2ErrorHandler(const NameChangeSender::Result, NameChangeRequestPtr&) {
        // no-op
    }

    /// @brief Fetches the number of entries in the NCR sender queue.
    ///
    /// @return The NCR queue size.
    int ncrQueueSize() {
        int size = -1;
        try {
            size = d2_mgr_.getQueueSize();
        } catch (...) {
            // If d2_mgr_ isn't in sending, it will throw.
            // Swallow the exception and return -1.
        }

        return (size);
    }

    /// @brief Check lease4 statistics.
    ///
    /// @param id Subnet id of the stats to check.
    /// @assigned The expected value of assigned addresses in subnet.
    /// @declined The expected value of declined addresses in subnet.
    void checkLease4Stats(SubnetID id, int32_t assigned, int32_t declined) {
        ASSERT_EQ(StatsMgr::instance().getObservation(
                      StatsMgr::generateName("subnet", id,
                          "assigned-addresses"))->getInteger().first, assigned);

        ASSERT_EQ(StatsMgr::instance().getObservation(
                      StatsMgr::generateName("subnet", id,
                          "declined-addresses"))->getInteger().first, declined);
    }

    /// @brief Check lease4 statistics.
    ///
    /// @param id Subnet id of the stats to check.
    /// @assigned_nas The expected value of assigned nas addresses in subnet.
    /// @declined The expected value of declined addresses in subnet.
    /// @assigned_pds The expected value of assigned pds addresses in subnet.
    void checkLease6Stats(SubnetID id, int32_t assigned_nas, int32_t declined,
                          int32_t assigned_pds) {
        ASSERT_EQ(StatsMgr::instance().getObservation(
                      StatsMgr::generateName("subnet", id,
                          "assigned-nas"))->getInteger().first, assigned_nas);

        ASSERT_EQ(StatsMgr::instance().getObservation(
                      StatsMgr::generateName("subnet", id,
                          "declined-addresses"))->getInteger().first, declined);

        ASSERT_EQ(StatsMgr::instance().getObservation(
                      StatsMgr::generateName("subnet", id,
                          "assigned-pds"))->getInteger().first, assigned_pds);
    }

    /// @brief Check that lease4-add with missing parameters will fail.
    void testLease4AddMissingParams();

    /// @brief Verify that lease4-add can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease4AddBadParams();

    /// @brief Check that a simple, well formed lease4 can be added.
    void testLease4Add();

    /// @brief Check that a simple, well formed lease4 can be added.
    void testLease4AddDeclinedLeases();

    /// @brief Check that a lease4 is not added when it already exists.
    void testLease4AddExisting();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease4AddSubnetIdMissing();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease4AddSubnetIdMissingDeclinedLeases();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own, but if there's no subnet for address being added,
    /// it should fail.
    void testLease4AddSubnetIdMissingBadAddr();

    /// @brief Check that the lease with negative expiration time is rejected.
    void testLease4AddNegativeExpireTime();

    /// @brief Check that the lease with negative cltt is rejected.
    void testLease4AddNegativeCltt();

    /// @brief Check that a well formed lease4 with tons of parameters can be
    /// added.
    void testLease4AddFullAddr();

    /// @brief Check that a well formed lease4 with a comment can be added.
    void testLease4AddComment();

    /// @brief Check that lease6-add with missing parameters will fail.
    void testLease6AddMissingParams();

    /// @brief Verify that lease6-add can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease6AddBadParams();

    /// @brief Check that a simple, well formed lease6 can be added.
    void testLease6Add();

    /// @brief Check that a simple, well formed lease6 can be added.
    void testLease6AddDeclinedLeases();

    /// @brief Check that a lease6 is not added when it already exists.
    void testLease6AddExisting();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease6AddSubnetIdMissing();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease6AddSubnetIdMissingDeclinedLeases();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own, but if there's no subnet for address being added,
    /// it should fail.
    void testLease6AddSubnetIdMissingBadAddr();

    /// @brief Check that the lease with negative expiration time is rejected.
    void testLease6AddNegativeExpireTime();

    /// @brief Check that the lease with negative cltt is rejected.
    void testLease6AddNegativeCltt();

    /// @brief Check that a simple, well formed prefix lease can be added.
    void testLease6AddPrefix();

    /// @brief Check that a well formed lease6 with tons of parameters can be
    /// added.
    void testLease6AddFullAddr();

    /// @brief Check that a well formed lease6 with a comment can be added.
    void testLease6AddComment();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease4GetMissingParams();

    /// @brief Check that lease4-get sanitizes its input.
    void testLease4GetByAddrBadParam();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4GetByAddrNotFound();

    /// @brief Check that lease4-get can return a lease by address.
    void testLease4GetByAddr();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4GetByHWAddrNotFound();

    /// @brief Check that lease4-get can find a lease by hardware address.
    void testLease4GetByHWAddr();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4GetByClientIdNotFound();

    /// @brief Check that lease4-get can find a lease by client identifier.
    void testLease4GetByClientId();

    /// @brief Check that lease6-get can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease6GetMissingParams();

    /// @brief Check that lease6-get sanitizes its input.
    void testLease6GetByAddrBadParam();

    /// @brief Check that lease6-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease6GetByAddrNotFound();

    /// @brief Check that lease6-get can return a lease by address.
    void testLease6GetByAddr();

    /// @brief Check that lease6-get can return a lease by prefix.
    void testLease6GetByAddrPrefix();

    /// @bfief Check that lease6-get rejects queries by client-id.
    void testLease6GetByClientIdInvalidType();

    /// @brief Check that lease6-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease6GetByDuidNotFound();

    /// @bfief Check that lease6-get can find a lease by duid.
    void testLease6GetByDuid();

    /// @brief Check that lease4-get-all returns all leases.
    void testLease4GetAll();

    /// @brief Check that lease4-get-all returns empty set if no leases are
    /// found.
    void testLease4GetAllNoLeases();

    /// @brief Check that lease4-get-all returns all leases for a subnet.
    void testLease4GetAllBySubnetId();

    /// @brief Check that lease4-get-all returns empty set when no leases are
    /// found.
    void testLease4GetAllBySubnetIdNoLeases();

    /// @brief Check that lease4-get-all returns leases from multiple subnets.
    void testLease4GetAllByMultipleSubnetIds();

    /// @brief Check that lease4-get-all checks its input arguments.
    void testLease4GetBySubnetIdInvalidArguments();

    /// @brief Check that multiple calls to lease4-get-page return all leases.
    void testLease4GetPaged();

    /// @brief Verifies that first page of IPv4 leases can be retrieved by
    /// specifying zero IPv4 address.
    void testLease4GetPagedZeroAddress();

    /// @brief Verifies that IPv6 address as a start address is rejected.
    void testLease4GetPagedIPv6Address();

    /// @brief Verifies that value of 'from' parameter other than 'start' or an
    /// IPv4 address is rejected.
    void testLease4GetPagedInvalidFrom();

    /// @brief Verifies that limit is mandatory.
    void testLease4GetPagedNoLimit();

    /// @brief Verifies that the limit must be a number.
    void testLease4GetPagedLimitNotNumber();

    /// @brief Verifies that the limit of 0 is rejected.
    void testLease4GetPagedLimitIsZero();

    /// @brief Check that lease6-get-all returns all leases.
    void testLease6GetAll();

    /// @brief Check that lease6-get-all returns empty set if no leases are
    /// found.
    void testLease6GetAllNoLeases();

    /// @brief Check that lease6-get-all returns all leases for a subnet.
    void testLease6GetAllBySubnetId();

    /// @brief Check that lease6-get-all returns empty set when no leases are
    /// found.
    void testLease6GetAllBySubnetIdNoLeases();

    /// @brief Check that lease6-get-all returns leases from multiple subnets.
    void testLease6GetAllByMultipleSubnetIds();

    /// @brief Check that lease6-get-all checks its input arguments.
    void testLease6GetBySubnetIdInvalidArguments();

    /// @brief Check that multiple calls to lease6-get-page return all leases.
    void testLease6GetPaged();

    /// @brief Verifies that first page of IPv6 leases can be retrieved by
    /// specifying zero IPv6 address.
    void testLease6GetPagedZeroAddress();

    /// @brief Verifies that IPv4 address as a start address is rejected.
    void testLease6GetPagedIPv4Address();

    /// @brief Verifies that value of 'from' parameter other than 'start' or an
    /// IPv6 address is rejected.
    void testLease6GetPagedInvalidFrom();

    /// @brief Verifies that limit is mandatory.
    void testLease6GetPagedNoLimit();

    /// @brief Verifies that the limit must be a number.
    void testLease6GetPagedLimitNotNumber();

    /// @brief Verifies that the limit of 0 is rejected.
    void testLease6GetPagedLimitIsZero();

    /// @brief Check that lease4-get-by-hw-address can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLeaseGetByHwAddressParams();

    /// @brief Check that lease4-get-by-hw-address works as expected (find no
    /// lease).
    void testLeaseGetByHwAddressFind0();

    /// @brief Check that lease4-get-by-hw-address works as expected (find two
    /// leases).
    void testLeaseGetByHwAddressFind2();

    /// @brief Check that lease4-get-by-client-id can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLeaseGetByClientIdParams();

    /// @brief Check that lease4-get-by-client-id works as expected (find no
    /// lease).
    void testLeaseGetByClientIdFind0();

    /// @brief Check that lease4-get-by-client-id works as expected (find two
    /// leases).
    void testLeaseGetByClientIdFind2();

    /// @brief Check that lease6-get-by-duid can handle a situation when the
    /// query is broken (required parameter is missing).
    void testLeaseGetByDuidParams();

    /// @brief Check that lease6-get-by-duid works as expected (find no lease).
    void testLeaseGetByDuidFind0();

    /// @brief Check that lease6-get-by-duid works as expected (find two
    /// leases).
    void testLeaseGetByDuidFind2();

    /// @brief Check that lease4-get-by-hostname can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLease4GetByHostnameParams();

    /// @brief Check that lease4-get-by-hostname works as expected (find no
    /// lease).
    void testLease4GetByHostnameFind0();

    /// @brief Check that lease4-get-by-hostname works as expected (find two
    /// leases).
    void testLease4GetByHostnameFind2();

    /// @brief Check that lease6-get-by-hostname can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLease6GetByHostnameParams();

    /// @brief Check that lease6-get-by-hostname works as expected (find no
    /// lease).
    void testLease6GetByHostnameFind0();

    /// @brief Check that lease6-get-by-hostname works as expected (find two
    /// leases).
    void testLease6GetByHostnameFind2();

    /// @brief Test checks if lease4-update handler refuses calls with missing
    /// parameters.
    void testLease4UpdateMissingParams();

    /// @brief Verify that lease4-update can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease4UpdateBadParams();

    /// @brief Check that lease4-update correctly handles case when there is no
    /// lease to be updated.
    void testLease4UpdateNoLease();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease4Update();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease4UpdateDeclinedLeases();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease4UpdateNoSubnetId();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease4UpdateNoSubnetIdDeclinedLeases();

    /// @brief Check that a lease4 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command.
    void testLease4UpdateForceCreate();

    /// @brief Check that a lease4 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command. The subnet-id is not specified, Kea will
    /// figure it out.
    void testLease4UpdateForceCreateNoSubnetId();

    /// @brief Check that lease4-update correctly handles case when the
    /// 'force-create' parameter is explicitly set to false.
    void testLease4UpdateDoNotForceCreate();

    /// @brief Check that a lease4 can be updated. We're adding a comment and an
    /// user context.
    void testLease4UpdateComment();

    /// @brief Test checks if lease6-update handler refuses calls with missing
    /// parameters.
    void testLease6UpdateMissingParams();

    /// @brief Verify that lease6-update can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease6UpdateBadParams();

    /// @brief Check that lease6-update correctly handles case when there is no
    /// lease to be updated.
    void testLease6UpdateNoLease();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease6Update();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease6UpdateDeclinedLeases();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease6UpdateNoSubnetId();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease6UpdateNoSubnetIdDeclinedLeases();

    /// @brief Check that a lease6 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command.
    void testLease6UpdateForceCreate();

    /// @brief Check that a lease6 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command. The subnet-id is not specified, Kea will
    /// figure it out.
    void testLease6UpdateForceCreateNoSubnetId();

    /// @brief Check that lease6-update correctly handles case when the
    /// 'force-create' parameter is explicitly set to false.
    void testLease6UpdateDoNotForceCreate();

    /// @brief Check that a lease6 can be updated. We're adding a comment and an
    /// user context.
    void testLease6UpdateComment();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease4DelMissingParams();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// valid, but the lease is not there.
    void testLease4DelByAddrNotFound();

    /// @brief Check that lease4-del sanitizes its input.
    void testLease4DelByAddrBadParam();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed and the lease is deleted.
    void testLease4DelByAddr();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed and the lease is deleted.
    void testLease4DelByAddrDeclinedLeases();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4DelByHWAddrNotFound();

    /// @brief Check that lease4-del can find and delete a lease by hardware
    /// address.
    void testLease4DelByHWAddr();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4DelByClientIdNotFound();

    /// @brief Check that lease4-del can find and delete a lease by client
    /// identifier.
    void testLease4DelByClientId();

    /// @brief Check that lease6-del can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease6DelMissingParams();

    /// @brief Check that lease6-del(subnet-id, addr6) can handle a situation
    /// when the query is correctly formed, but the lease is not there.
    void testLease6DelByAddrNotFound();

    /// @brief Check that lease6-del sanitizes its input.
    void testLease6DelByAddrBadParam();

    /// @brief Check that lease6-del(subnet-id, addr6) can handle a situation
    /// when the query is correctly formed and the lease is deleted.
    void testLease6DelByAddr();

    /// @brief Check that lease6-del(subnet-id, addr6) can handle a situation
    /// when the query is correctly formed and the lease is deleted.
    void testLease6DelByAddrDeclinedLeases();

    /// @brief Check that lease6-del(type, addr6) can handle a
    /// situation when the query is correctly formed and the lease is deleted.
    void testLease6DelByAddrPrefix();

    /// @brief Check that lease6-del(subnet-id, addr) can handle a situation
    /// when the query is correctly formed, but the lease is not there.
    void testLease6DelByDuidNotFound();

    /// @brief Check that lease6-del(subnet-id, iaid, identifier-type,
    /// identifier) can find and delete a lease by duid.
    void testLease6DelByDuid();

    /// @brief Check that leaseX-del checks update-ddns input.
    void testLeaseXDelBadUpdateDdnsParam();

    /// @brief Check that lease4-wipe can remove leases.
    void testLease4Wipe();

    /// @brief Check that lease4-wipe can remove leases from all subnets at
    /// once.
    void testLease4WipeAll();

    /// @brief Check that lease4-wipe can remove leases from all subnets at
    /// once (when no parameters are specified).
    void testLease4WipeAllNoArgs();

    /// @brief Check that lease4-wipe properly reports when no leases were
    /// deleted.
    void testLease4WipeNoLeases();

    /// @brief Check that lease4-wipe properly reports when no leases were
    /// deleted.
    void testLease4WipeNoLeasesAll();

    /// @brief Check that lease6-wipe can remove leases.
    void testLease6Wipe();

    /// @brief Check that lease6-wipe can remove leases from all subnets at
    /// once.
    void testLease6WipeAll();

    /// @brief Check that lease6-wipe can remove leases from all subnets at
    /// once (when no parameters are specified).
    void testLease6WipeAllNoArgs();

    /// @brief Check that lease6-wipe properly reports when no leases were
    /// deleted.
    void testLease6WipeNoLeases();

    /// @brief Check that lease6-wipe properly reports when no leases were
    /// deleted.
    void testLease6WipeNoLeasesAll();

    /// @brief Check that an attempt to update a lease (set incorrect
    /// subnet-id) will fail.
    void testLease4BrokenUpdate();

    /// @brief Check that an attempt to update a lease (set incorrect
    /// subnet-id) will fail.
    void testLease6BrokenUpdate();

    /// @brief This test verifies that it is possible to add two leases and
    /// delete two leases as a result of the single lease6-bulk-apply command.
    void testLease6BulkApply();

    /// @brief This test verifies that the lease parameters are checked when
    /// adding new leases only with the lease6-bulk-apply.
    void testLease6BulkApplyAddsOnlyBadParam();

    /// @brief This test verifies that it is possible to send new leases only
    /// with the lease6-bulk-apply.
    void testLease6BulkApplyAddsOnly();

    /// @brief This test verifies that the lease parameters are checked when
    /// updating leases only with the lease6-bulk-apply.
    void testLease6BulkApplyUpdatesOnlyBadParam();

    /// @brief This test verifies that it is possible to update leases with the
    /// lease6-bulk-apply.
    void testLease6BulkApplyUpdatesOnly();

    /// @brief This test verifies that it is possible to only delete leases with
    /// the lease6-bulk-apply.
    void testLease6BulkApplyDeletesOnly();

    /// @brief This test verifies that deleting non existing leases returns an
    /// 'empty' result.
    void testLease6BulkApplyDeleteNonExiting();

    /// @brief Check that changes for other leases are not applied if one of the
    /// leases is malformed.
    void testLease6BulkApplyRollback();

    /// @brief Check that lease4-resend-ddns sanitizes its input.
    void testLease4ResendDdnsBadParam();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for given
    /// lease when DDNS updating is disabled.
    void testLease4ResendDdnsDisabled();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for when
    /// there is no matching lease.
    void testLease4ResendDdnsNoLease();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled but Lease::hostname_ is blank.
    void testLease4ResendNoHostname();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, but both
    /// Lease::fqdn_fwd_ and fdqn_rev_ are false.
    void testLease4ResendNoDirectionsEnabled();

    /// @brief Check that lease4-resend-ddns can generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, and at
    /// least one of Lease::fqdn_fwd_ or fdqn_rev_ are true.
    void testLease4ResendDdnsEnabled();

    /// @brief Check that lease6-resend-ddns sanitizes its input.
    void testLease6ResendDdnsBadParam();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for given
    /// lease when DDNS updating is disabled.
    void testLease6ResendDdnsDisabled();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for when
    /// there is no matching lease.
    void testLease6ResendDdnsNoLease();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled but Lease::hostname_ is blank.
    void testLease6ResendNoHostname();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, but both
    /// Lease::fqdn_fwd_ and fdqn_rev_ are false.
    void testLease6ResendNoDirectionsEnabled();

    /// @brief Check that lease6-resend-ddns can generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, and at
    /// least one of Lease::fqdn_fwd_ or fdqn_rev_ are true.
    void testLease6ResendDdnsEnabled();

    /// @brief Check that lease4-del does (or does not) generate an NCR to
    /// remove DNS for a given lease based on lease content when DDNS updates
    /// are enabled.
    void testLease4DnsRemoveD2Enabled();

    /// @brief Check that lease4-del does not generate an NCR to remove DNS for
    /// a given lease based on lease content when DDNS updates are disabled.
    void testLease4DnsRemoveD2Disabled();

    /// @brief Check that lease6-del does (or does not) generate an NCR to
    /// remove DNS for a given lease based on lease content when DDNS updates
    /// are enabled.
    void testLease6DnsRemoveD2Enabled();

    /// @brief Check that lease6-del does not generate an NCR to remove DNS for
    /// a given lease based on lease content when DDNS updates are disabled.
    void testLease6DnsRemoveD2Disabled();
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
        "lease4-wipe",              "lease6-wipe",
        "lease4-resend-ddns",       "lease6-resend-ddns"
    };
    testCommands(cmds);
}

// Check that the library can be loaded and unloaded multiple times.
TEST_F(LeaseCmdsTest, multipleLoads) {
    testMultipleLoads();
}

using namespace isc::dhcp;

void LeaseCmdsTest::testLease4AddMissingParams() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

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

TEST_F(LeaseCmdsTest, lease4AddMissingParams) {
    testLease4AddMissingParams();
}

TEST_F(LeaseCmdsTest, lease4AddMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddMissingParams();
}

void LeaseCmdsTest::testLease4AddBadParams() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

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

TEST_F(LeaseCmdsTest, lease4AddBadParams) {
    testLease4AddBadParams();
}

TEST_F(LeaseCmdsTest, lease4AddBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddBadParams();
}

void LeaseCmdsTest::testLease4Add() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease has proper value set.
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

TEST_F(LeaseCmdsTest, lease4Add) {
    testLease4Add();
}

TEST_F(LeaseCmdsTest, lease4AddMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4Add();
}

void LeaseCmdsTest::testLease4AddDeclinedLeases() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"state\": 1,\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 1);

    checkLease4Stats(88, 0, 0);

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
    EXPECT_EQ(1, l->state_);
}

TEST_F(LeaseCmdsTest, lease4AddDeclinedLeases) {
    testLease4AddDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease4AddDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddDeclinedLeases();
}

void LeaseCmdsTest::testLease4AddExisting() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease already exists.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);
}

TEST_F(LeaseCmdsTest, lease4AddExisting) {
    testLease4AddExisting();
}

TEST_F(LeaseCmdsTest, lease4AddExistingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddExisting();
}

void LeaseCmdsTest::testLease4AddSubnetIdMissing() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ(44, l->subnet_id_);
}

TEST_F(LeaseCmdsTest, lease4AddSubnetIdMissing) {
    testLease4AddSubnetIdMissing();
}

TEST_F(LeaseCmdsTest, lease4AddSubnetIdMissingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddSubnetIdMissing();
}

void LeaseCmdsTest::testLease4AddSubnetIdMissingDeclinedLeases() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command without subnet-id. Kea should select
    // the subnet id on its own.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"state\": 1,\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 1);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ(44, l->subnet_id_);
}

TEST_F(LeaseCmdsTest, lease4AddSubnetIdMissingDeclinedLeases) {
    testLease4AddSubnetIdMissingDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease4AddSubnetIdMissingDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddSubnetIdMissingDeclinedLeases();
}

void LeaseCmdsTest::testLease4AddSubnetIdMissingBadAddr() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.55.1"));
    ASSERT_FALSE(l);
}

TEST_F(LeaseCmdsTest, lease4AddSubnetIdMissingBadAddr) {
    testLease4AddSubnetIdMissingBadAddr();
}

TEST_F(LeaseCmdsTest, lease4AddSubnetIdMissingBadAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddSubnetIdMissingBadAddr();
}

void LeaseCmdsTest::testLease4AddNegativeExpireTime() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_FALSE(l);
}

TEST_F(LeaseCmdsTest, lease4AddNegativeExpireTime) {
    testLease4AddNegativeExpireTime();
}

TEST_F(LeaseCmdsTest, lease4AddNegativeExpireTimeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddNegativeExpireTime();
}

void LeaseCmdsTest::testLease4AddNegativeCltt() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_FALSE(l);
}

TEST_F(LeaseCmdsTest, lease4AddNegativeCltt) {
    testLease4AddNegativeCltt();
}

TEST_F(LeaseCmdsTest, lease4AddNegativeClttMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddNegativeCltt();
}

void LeaseCmdsTest::testLease4AddFullAddr() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

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

TEST_F(LeaseCmdsTest, lease4AddFullAddr) {
    testLease4AddFullAddr();
}

TEST_F(LeaseCmdsTest, lease4AddFullAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddFullAddr();
}

void LeaseCmdsTest::testLease4AddComment() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"comment\": \"a comment\" }", l->getContext()->str());
}

TEST_F(LeaseCmdsTest, lease4AddComment) {
    testLease4AddComment();
}

TEST_F(LeaseCmdsTest, lease4AddCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddComment();
}

void LeaseCmdsTest::testLease6AddMissingParams() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

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

TEST_F(LeaseCmdsTest, lease6AddMissingParams) {
    testLease6AddMissingParams();
}

TEST_F(LeaseCmdsTest, lease6AddMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddMissingParams();
}

void LeaseCmdsTest::testLease6AddBadParams() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
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

    // Invalid declined state (1) for PD prefix.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"prefix-len\": 48,\n"
        "        \"type\": \"IA_PD\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"state\": 1"
        "    }\n"
        "}";
    exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6AddBadParams) {
    testLease6AddBadParams();
}

TEST_F(LeaseCmdsTest, lease6AddBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddBadParams();
}

void LeaseCmdsTest::testLease6Add() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could have the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(0, l->state_);
}

TEST_F(LeaseCmdsTest, lease6Add) {
    testLease6Add();
}

TEST_F(LeaseCmdsTest, lease6AddMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6Add();
}

void LeaseCmdsTest::testLease6AddDeclinedLeases() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"state\": 1,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 1, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could have the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(1, l->state_);
}

TEST_F(LeaseCmdsTest, lease6AddDeclinedLeases) {
    testLease6AddDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease6AddDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddDeclinedLeases();
}

void LeaseCmdsTest::testLease6AddExisting() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease already exists.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);
}

TEST_F(LeaseCmdsTest, lease6AddExisting) {
    testLease6AddExisting();
}

TEST_F(LeaseCmdsTest, lease6AddExistingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddExisting();
}

void LeaseCmdsTest::testLease6AddSubnetIdMissing() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there and has correct subnet-id.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(66, l->subnet_id_);
}

TEST_F(LeaseCmdsTest, lease6AddSubnetIdMissing) {
    testLease6AddSubnetIdMissing();
}

TEST_F(LeaseCmdsTest, lease6AddSubnetIdMissingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddSubnetIdMissing();
}

void LeaseCmdsTest::testLease6AddSubnetIdMissingDeclinedLeases() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command (without subnet-id)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"state\": 1,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 1, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there and has correct subnet-id.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(66, l->subnet_id_);
}

TEST_F(LeaseCmdsTest, lease6AddSubnetIdMissingDeclinedLeases) {
    testLease6AddSubnetIdMissingDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease6AddSubnetIdMissingDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddSubnetIdMissingDeclinedLeases();
}

void LeaseCmdsTest::testLease6AddSubnetIdMissingBadAddr() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease was not added.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:ffff::1"));
    ASSERT_FALSE(l);
}

TEST_F(LeaseCmdsTest, lease6AddSubnetIdMissingBadAddr) {
    testLease6AddSubnetIdMissingBadAddr();
}

TEST_F(LeaseCmdsTest, lease6AddSubnetIdMissingBadAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddSubnetIdMissingBadAddr();
}

void LeaseCmdsTest::testLease6AddNegativeExpireTime() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Add a lease with negative expiration time.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"expire\": -6218189367\n"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be positive for address 2001:db8:1::3";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease was not added.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_FALSE(l);
}

TEST_F(LeaseCmdsTest, lease6AddNegativeExpireTime) {
    testLease6AddNegativeExpireTime();
}

TEST_F(LeaseCmdsTest, lease6AddNegativeExpireTimeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddNegativeExpireTime();
}

void LeaseCmdsTest::testLease6AddNegativeCltt() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Add a lease with negative cltt (expiration time - valid lifetime)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"expire\": 123456,\n"
        "        \"iaid\": 1234,\n"
        "        \"valid-lft\": 123457"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be greater than valid lifetime for "
        "address 2001:db8:1::3";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease was not added.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_FALSE(l);
}

TEST_F(LeaseCmdsTest, lease6AddNegativeCltt) {
    testLease6AddNegativeCltt();
}

TEST_F(LeaseCmdsTest, lease6AddNegativeClttMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddNegativeCltt();
}

void LeaseCmdsTest::testLease6AddPrefix() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 0, 0, 1);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:abcd::"));
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::TYPE_PD, l->type_);
    EXPECT_EQ(48, l->prefixlen_);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

TEST_F(LeaseCmdsTest, lease6AddPrefix) {
    testLease6AddPrefix();
}

TEST_F(LeaseCmdsTest, lease6AddPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddPrefix();
}

void LeaseCmdsTest::testLease6AddFullAddr() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

TEST_F(LeaseCmdsTest, lease6AddFullAddr) {
    testLease6AddFullAddr();
}

TEST_F(LeaseCmdsTest, lease6AddFullAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddFullAddr();
}

void LeaseCmdsTest::testLease6AddComment() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"comment\": \"a comment\" }", l->getContext()->str());
}

TEST_F(LeaseCmdsTest, lease6AddComment) {
    testLease6AddComment();
}

TEST_F(LeaseCmdsTest, lease6AddCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddComment();
}

void LeaseCmdsTest::testLease4GetMissingParams() {

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

TEST_F(LeaseCmdsTest, lease4GetMissingParams) {
    testLease4GetMissingParams();
}

TEST_F(LeaseCmdsTest, lease4GetMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetMissingParams();
}

void LeaseCmdsTest::testLease4GetByAddrBadParam() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetByAddrBadParam) {
    testLease4GetByAddrBadParam();
}

TEST_F(LeaseCmdsTest, lease4GetByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByAddrBadParam();
}

void LeaseCmdsTest::testLease4GetByAddrNotFound() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetByAddrNotFound) {
    testLease4GetByAddrNotFound();
}

TEST_F(LeaseCmdsTest, lease4GetByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByAddrNotFound();
}

void LeaseCmdsTest::testLease4GetByAddr() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetByAddr) {
    testLease4GetByAddr();
}

TEST_F(LeaseCmdsTest, lease4GetByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByAddr();
}

void LeaseCmdsTest::testLease4GetByHWAddrNotFound() {

    // Initialize lease manager (false = v4, false = don't add leases)
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

TEST_F(LeaseCmdsTest, lease4GetByHWAddrNotFound) {
    testLease4GetByHWAddrNotFound();
}

TEST_F(LeaseCmdsTest, lease4GetByHWAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHWAddrNotFound();
}

void LeaseCmdsTest::testLease4GetByHWAddr() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetByHWAddr) {
    testLease4GetByHWAddr();
}

TEST_F(LeaseCmdsTest, lease4GetByHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHWAddr();
}

void LeaseCmdsTest::testLease6GetByAddrNotFound() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetByAddrNotFound) {
    testLease6GetByAddrNotFound();
}

TEST_F(LeaseCmdsTest, lease6GetByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddrNotFound();
}

void LeaseCmdsTest::testLease4GetByClientIdNotFound() {

    // Initialize lease manager (false = v4, false = don't add leases)
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

TEST_F(LeaseCmdsTest, lease4GetByClientIdNotFound) {
    testLease4GetByClientIdNotFound();
}

TEST_F(LeaseCmdsTest, lease4GetByClientIdNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByClientIdNotFound();
}

void LeaseCmdsTest::testLease4GetByClientId() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetByClientId) {
    testLease4GetByClientId();
}

TEST_F(LeaseCmdsTest, lease4GetByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByClientId();
}

void LeaseCmdsTest::testLease6GetByClientIdInvalidType() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetByClientIdInvalidType) {
    testLease6GetByClientIdInvalidType();
}

TEST_F(LeaseCmdsTest, lease6GetByClientIdInvalidTypeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByClientIdInvalidType();
}

void LeaseCmdsTest::testLease6GetByDuidNotFound() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetByDuidNotFound) {
    testLease6GetByDuidNotFound();
}

TEST_F(LeaseCmdsTest, lease6GetByDuidNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByDuidNotFound();
}

void LeaseCmdsTest::testLease6GetByAddr() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

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

TEST_F(LeaseCmdsTest, lease6GetByAddr) {
    testLease6GetByAddr();
}

TEST_F(LeaseCmdsTest, lease6GetByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddr();
}

void LeaseCmdsTest::testLease6GetMissingParams() {

    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by hw-address is not supported in v6. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Query by hw-address is not allowed in v6.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"duid\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier-type is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6GetMissingParams) {
    testLease6GetMissingParams();
}

TEST_F(LeaseCmdsTest, lease6GetMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetMissingParams();
}

void LeaseCmdsTest::testLease6GetByAddrBadParam() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetByAddrBadParam) {
    testLease6GetByAddrBadParam();
}

TEST_F(LeaseCmdsTest, lease6GetByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddrBadParam();
}

void LeaseCmdsTest::testLease6GetByAddrPrefix() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // We need to get a prefix lease. We need to create it by hand.
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

TEST_F(LeaseCmdsTest, lease6GetByAddrPrefix) {
    testLease6GetByAddrPrefix();
}

TEST_F(LeaseCmdsTest, lease6GetByAddrPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddrPrefix();
}

void LeaseCmdsTest::testLease6GetByDuid() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

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

TEST_F(LeaseCmdsTest, lease6GetByDuid) {
    testLease6GetByDuid();
}

TEST_F(LeaseCmdsTest, lease6GetByDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByDuid();
}

void LeaseCmdsTest::testLease4GetAll() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetAll) {
    testLease4GetAll();
}

TEST_F(LeaseCmdsTest, lease4GetAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAll();
}

void LeaseCmdsTest::testLease4GetAllNoLeases() {

    // Initialize lease manager (false = v4, false = don't add leases)
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

TEST_F(LeaseCmdsTest, lease4GetAllNoLeases) {
    testLease4GetAllNoLeases();
}

TEST_F(LeaseCmdsTest, lease4GetAllNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllNoLeases();
}

void LeaseCmdsTest::testLease4GetAllBySubnetId() {

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

TEST_F(LeaseCmdsTest, lease4GetAllBySubnetId) {
    testLease4GetAllBySubnetId();
}

TEST_F(LeaseCmdsTest, lease4GetAllBySubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllBySubnetId();
}

void LeaseCmdsTest::testLease4GetAllBySubnetIdNoLeases() {

    // Initialize lease manager (false = v4, false = don't add leases)
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

TEST_F(LeaseCmdsTest, lease4GetAllBySubnetIdNoLeases) {
    testLease4GetAllBySubnetIdNoLeases();
}

TEST_F(LeaseCmdsTest, lease4GetAllBySubnetIdNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllBySubnetIdNoLeases();
}

void LeaseCmdsTest::testLease4GetAllByMultipleSubnetIds() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetAllByMultipleSubnetIds) {
    testLease4GetAllByMultipleSubnetIds();
}

TEST_F(LeaseCmdsTest, lease4GetAllByMultipleSubnetIdsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllByMultipleSubnetIds();
}

void LeaseCmdsTest::testLease4GetBySubnetIdInvalidArguments() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetBySubnetIdInvalidArguments) {
    testLease4GetBySubnetIdInvalidArguments();
}

TEST_F(LeaseCmdsTest, lease4GetBySubnetIdInvalidArgumentsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetBySubnetIdInvalidArguments();
}

void LeaseCmdsTest::testLease4GetPaged() {

    // Initialize lease manager (false = v4, true = add leases)
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

        // For the first two pages we should get success. For the last
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

TEST_F(LeaseCmdsTest, lease4GetPaged) {
    testLease4GetPaged();
}

TEST_F(LeaseCmdsTest, lease4GetPagedMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPaged();
}

void LeaseCmdsTest::testLease4GetPagedZeroAddress() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetPagedZeroAddress) {
    testLease4GetPagedZeroAddress();
}

TEST_F(LeaseCmdsTest, lease4GetPagedZeroAddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedZeroAddress();
}

void LeaseCmdsTest::testLease4GetPagedIPv6Address() {

    // Initialize lease manager (false = v4, true = add leases)
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

TEST_F(LeaseCmdsTest, lease4GetPagedIPv6Address) {
    testLease4GetPagedIPv6Address();
}

TEST_F(LeaseCmdsTest, lease4GetPagedIPv6AddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedIPv6Address();
}

void LeaseCmdsTest::testLease4GetPagedInvalidFrom() {

    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"foo\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value is neither 'start' keyword "
        "nor a valid IPv4 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4GetPagedInvalidFrom) {
    testLease4GetPagedInvalidFrom();
}

TEST_F(LeaseCmdsTest, lease4GetPagedInvalidFromMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedInvalidFrom();
}

void LeaseCmdsTest::testLease4GetPagedNoLimit() {

    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\""
        "    }"
        "}";

    string exp_rsp = "'limit' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4GetPagedNoLimit) {
    testLease4GetPagedNoLimit();
}

TEST_F(LeaseCmdsTest, lease4GetPagedNoLimitMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedNoLimit();
}

void LeaseCmdsTest::testLease4GetPagedLimitNotNumber() {

    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": false"
        "    }"
        "}";

    string exp_rsp = "'limit' parameter must be a number";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4GetPagedLimitNotNumber) {
    testLease4GetPagedLimitNotNumber();
}

TEST_F(LeaseCmdsTest, lease4GetPagedLimitNotNumberMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedLimitNotNumber();
}

void LeaseCmdsTest::testLease4GetPagedLimitIsZero() {

    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": 0"
        "    }"
        "}";

    string exp_rsp = "page size of retrieved leases must not be 0";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4GetPagedLimitIsZero) {
    testLease4GetPagedLimitIsZero();
}

TEST_F(LeaseCmdsTest, lease4GetPagedLimitIsZeroMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedLimitIsZero();
}

void LeaseCmdsTest::testLease6GetAll() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetAll) {
    testLease6GetAll();
}

TEST_F(LeaseCmdsTest, lease6GetAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAll();
}

void LeaseCmdsTest::testLease6GetAllNoLeases() {

    // Initialize lease manager (true = v6, false = don't add leases)
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

TEST_F(LeaseCmdsTest, lease6GetAllNoLeases) {
    testLease6GetAllNoLeases();
}

TEST_F(LeaseCmdsTest, lease6GetAllNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllNoLeases();
}

void LeaseCmdsTest::testLease6GetAllBySubnetId() {

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

TEST_F(LeaseCmdsTest, lease6GetAllBySubnetId) {
    testLease6GetAllBySubnetId();
}

TEST_F(LeaseCmdsTest, lease6GetAllBySubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllBySubnetId();
}

void LeaseCmdsTest::testLease6GetAllBySubnetIdNoLeases() {

    // Initialize lease manager (true = v6, false = don't add leases)
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

TEST_F(LeaseCmdsTest, lease6GetAllBySubnetIdNoLeases) {
    testLease6GetAllBySubnetIdNoLeases();
}

TEST_F(LeaseCmdsTest, lease6GetAllBySubnetIdNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllBySubnetIdNoLeases();
}

void LeaseCmdsTest::testLease6GetAllByMultipleSubnetIds() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetAllByMultipleSubnetIds) {
    testLease6GetAllByMultipleSubnetIds();
}

TEST_F(LeaseCmdsTest, lease6GetAllByMultipleSubnetIdsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllByMultipleSubnetIds();
}

void LeaseCmdsTest::testLease6GetBySubnetIdInvalidArguments() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetBySubnetIdInvalidArguments) {
    testLease6GetBySubnetIdInvalidArguments();
}

TEST_F(LeaseCmdsTest, lease6GetBySubnetIdInvalidArgumentsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetBySubnetIdInvalidArguments();
}

void LeaseCmdsTest::testLease6GetPaged() {

    // Initialize lease manager (true = v6, true = add leases)
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

        // For the first two pages we should get success. For the last
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

TEST_F(LeaseCmdsTest, lease6GetPaged) {
    testLease6GetPaged();
}

TEST_F(LeaseCmdsTest, lease6GetPagedMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPaged();
}

void LeaseCmdsTest::testLease6GetPagedZeroAddress() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetPagedZeroAddress) {
    testLease6GetPagedZeroAddress();
}

TEST_F(LeaseCmdsTest, lease6GetPagedZeroAddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedZeroAddress();
}

void LeaseCmdsTest::testLease6GetPagedIPv4Address() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetPagedIPv4Address) {
    testLease6GetPagedIPv4Address();
}

TEST_F(LeaseCmdsTest, lease6GetPagedIPv4AddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedIPv4Address();
}

void LeaseCmdsTest::testLease6GetPagedInvalidFrom() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetPagedInvalidFrom) {
    testLease6GetPagedInvalidFrom();
}

TEST_F(LeaseCmdsTest, lease6GetPagedInvalidFromMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedInvalidFrom();
}

void LeaseCmdsTest::testLease6GetPagedNoLimit() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetPagedNoLimit) {
    testLease6GetPagedNoLimit();
}

TEST_F(LeaseCmdsTest, lease6GetPagedNoLimitMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedNoLimit();
}

void LeaseCmdsTest::testLease6GetPagedLimitNotNumber() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetPagedLimitNotNumber) {
    testLease6GetPagedLimitNotNumber();
}

TEST_F(LeaseCmdsTest, lease6GetPagedLimitNotNumberMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedLimitNotNumber();
}

void LeaseCmdsTest::testLease6GetPagedLimitIsZero() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6GetPagedLimitIsZero) {
    testLease6GetPagedLimitIsZero();
}

TEST_F(LeaseCmdsTest, lease6GetPagedLimitIsZeroMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedLimitIsZero();
}

void LeaseCmdsTest::testLeaseGetByHwAddressParams() {

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
    exp_rsp = "'hw-address' parameter must be a string";
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

TEST_F(LeaseCmdsTest, leaseGetByHwAddressParams) {
    testLeaseGetByHwAddressParams();
}

TEST_F(LeaseCmdsTest, leaseGetByHwAddressParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByHwAddressParams();
}

void LeaseCmdsTest::testLeaseGetByHwAddressFind0() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
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

TEST_F(LeaseCmdsTest, leaseGetByHwAddressFind0) {
    testLeaseGetByHwAddressFind0();
}

TEST_F(LeaseCmdsTest, leaseGetByHwAddressFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByHwAddressFind0();
}

void LeaseCmdsTest::testLeaseGetByHwAddressFind2() {

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

TEST_F(LeaseCmdsTest, leaseGetByHwAddressFind2) {
    testLeaseGetByHwAddressFind2();
}

TEST_F(LeaseCmdsTest, leaseGetByHwAddressFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByHwAddressFind2();
}

void LeaseCmdsTest::testLeaseGetByClientIdParams() {

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
    exp_rsp = "'client-id' parameter must be a string";
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

TEST_F(LeaseCmdsTest, leaseGetByClientIdParams) {
    testLeaseGetByClientIdParams();
}

TEST_F(LeaseCmdsTest, leaseGetByClientIdParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByClientIdParams();
}

void LeaseCmdsTest::testLeaseGetByClientIdFind0() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
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

TEST_F(LeaseCmdsTest, leaseGetByClientIdFind0) {
    testLeaseGetByClientIdFind0();
}

TEST_F(LeaseCmdsTest, leaseGetByClientIdFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByClientIdFind0();
}

void LeaseCmdsTest::testLeaseGetByClientIdFind2() {

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

TEST_F(LeaseCmdsTest, leaseGetByClientIdFind2) {
    testLeaseGetByClientIdFind2();
}

TEST_F(LeaseCmdsTest, leaseGetByClientIdFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByClientIdFind2();
}

void LeaseCmdsTest::testLeaseGetByDuidParams() {

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
    exp_rsp = "'duid' parameter must be a string";
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

TEST_F(LeaseCmdsTest, leaseGetByDuidParams) {
    testLeaseGetByDuidParams();
}

TEST_F(LeaseCmdsTest, leaseGetByDuidParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByDuidParams();
}

void LeaseCmdsTest::testLeaseGetByDuidFind0() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // No such lease.
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

TEST_F(LeaseCmdsTest, leaseGetByDuidFind0) {
    testLeaseGetByDuidFind0();
}

TEST_F(LeaseCmdsTest, leaseGetByDuidFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByDuidFind0();
}

void LeaseCmdsTest::testLeaseGetByDuidFind2() {

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

TEST_F(LeaseCmdsTest, leaseGetByDuidFind2) {
    testLeaseGetByDuidFind2();
}

TEST_F(LeaseCmdsTest, leaseGetByDuidFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseGetByDuidFind2();
}

void LeaseCmdsTest::testLease4GetByHostnameParams() {

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
    exp_rsp = "'hostname' parameter must be a string";
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

TEST_F(LeaseCmdsTest, lease4GetByHostnameParams) {
    testLease4GetByHostnameParams();
}

TEST_F(LeaseCmdsTest, lease4GetByHostnameParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHostnameParams();
}

void LeaseCmdsTest::testLease4GetByHostnameFind0() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
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

TEST_F(LeaseCmdsTest, lease4GetByHostnameFind0) {
    testLease4GetByHostnameFind0();
}

TEST_F(LeaseCmdsTest, lease4GetByHostnameFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHostnameFind0();
}

void LeaseCmdsTest::testLease4GetByHostnameFind2() {

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

TEST_F(LeaseCmdsTest, lease4GetByHostnameFind2) {
    testLease4GetByHostnameFind2();
}

TEST_F(LeaseCmdsTest, lease4GetByHostnameFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHostnameFind2();
}

void LeaseCmdsTest::testLease6GetByHostnameParams() {

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
    exp_rsp = "'hostname' parameter must be a string";
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

TEST_F(LeaseCmdsTest, lease6GetByHostnameParams) {
    testLease6GetByHostnameParams();
}

TEST_F(LeaseCmdsTest, lease6GetByHostnameParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByHostnameParams();
}

void LeaseCmdsTest::testLease6GetByHostnameFind0() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // No such lease.
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

TEST_F(LeaseCmdsTest, lease6GetByHostnameFind0) {
    testLease6GetByHostnameFind0();
}

TEST_F(LeaseCmdsTest, lease6GetByHostnameFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByHostnameFind0();
}

void LeaseCmdsTest::testLease6GetByHostnameFind2() {

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

TEST_F(LeaseCmdsTest, lease6GetByHostnameFind2) {
    testLease6GetByHostnameFind2();
}

TEST_F(LeaseCmdsTest, lease6GetByHostnameFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByHostnameFind2();
}

void LeaseCmdsTest::testLease4UpdateMissingParams() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

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

TEST_F(LeaseCmdsTest, lease4UpdateMissingParams) {
    testLease4UpdateMissingParams();
}

TEST_F(LeaseCmdsTest, lease4UpdateMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateMissingParams();
}

void LeaseCmdsTest::testLease4UpdateBadParams() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

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

TEST_F(LeaseCmdsTest, lease4UpdateBadParams) {
    testLease4UpdateBadParams();
}

TEST_F(LeaseCmdsTest, lease4UpdateBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateBadParams();
}

void LeaseCmdsTest::testLease4UpdateNoLease() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

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
    string exp_rsp = "failed to update the lease with address 192.0.2.1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4UpdateNoLease) {
    testLease4UpdateNoLease();
}

TEST_F(LeaseCmdsTest, lease4UpdateNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateNoLease();
}

void LeaseCmdsTest::testLease4Update() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

TEST_F(LeaseCmdsTest, lease4Update) {
    testLease4Update();
}

TEST_F(LeaseCmdsTest, lease4UpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4Update();
}

void LeaseCmdsTest::testLease4UpdateDeclinedLeases() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true, true);

    checkLease4Stats(44, 2, 2);

    checkLease4Stats(88, 2, 2);

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

    checkLease4Stats(44, 2, 1);

    checkLease4Stats(88, 2, 2);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

TEST_F(LeaseCmdsTest, lease4UpdateDeclinedLeases) {
    testLease4UpdateDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease4UpdateDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateDeclinedLeases();
}

void LeaseCmdsTest::testLease4UpdateNoSubnetId() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

TEST_F(LeaseCmdsTest, lease4UpdateNoSubnetId) {
    testLease4UpdateNoSubnetId();
}

TEST_F(LeaseCmdsTest, lease4UpdateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateNoSubnetId();
}

void LeaseCmdsTest::testLease4UpdateNoSubnetIdDeclinedLeases() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true, true);

    checkLease4Stats(44, 2, 2);

    checkLease4Stats(88, 2, 2);

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

    checkLease4Stats(44, 2, 1);

    checkLease4Stats(88, 2, 2);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

TEST_F(LeaseCmdsTest, lease4UpdateNoSubnetIdDeclinedLeases) {
    testLease4UpdateNoSubnetIdDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease4UpdateNoSubnetIdDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateNoSubnetIdDeclinedLeases();
}

void LeaseCmdsTest::testLease4UpdateForceCreate() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it contains expected values..
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

TEST_F(LeaseCmdsTest, lease4UpdateForceCreate) {
    testLease4UpdateForceCreate();
}

TEST_F(LeaseCmdsTest, lease4UpdateForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateForceCreate();
}

void LeaseCmdsTest::testLease4UpdateForceCreateNoSubnetId() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

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

TEST_F(LeaseCmdsTest, lease4UpdateForceCreateNoSubnetId) {
    testLease4UpdateForceCreateNoSubnetId();
}

TEST_F(LeaseCmdsTest, lease4UpdateForceCreateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateForceCreateNoSubnetId();
}

void LeaseCmdsTest::testLease4UpdateDoNotForceCreate() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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
    string exp_rsp = "failed to update the lease with address 192.0.2.1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);
}

TEST_F(LeaseCmdsTest, lease4UpdateDoNotForceCreate) {
    testLease4UpdateDoNotForceCreate();
}

TEST_F(LeaseCmdsTest, lease4UpdateDoNotForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateDoNotForceCreate();
}

void LeaseCmdsTest::testLease4UpdateComment() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

TEST_F(LeaseCmdsTest, lease4UpdateComment) {
    testLease4UpdateComment();
}

TEST_F(LeaseCmdsTest, lease4UpdateCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateComment();
}

void LeaseCmdsTest::testLease6UpdateMissingParams() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

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
        "            \"subnet-id\": 66,\n"
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
        "            \"subnet-id\": 66,\n"
        "            \"duid\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id, duid and iaid is not enough (ip missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
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
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'iaid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6UpdateMissingParams) {
    testLease6UpdateMissingParams();
}

TEST_F(LeaseCmdsTest, lease6UpdateMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateMissingParams();
}

void LeaseCmdsTest::testLease6UpdateBadParams() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

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

    // Invalid declined state (1) for PD prefix.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"prefix-len\": 48,\n"
        "        \"type\": \"IA_PD\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"state\": 1"
        "    }\n"
        "}";
    exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6UpdateBadParams) {
    testLease6UpdateBadParams();
}

TEST_F(LeaseCmdsTest, lease6UpdateBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateBadParams();
}

void LeaseCmdsTest::testLease6Update() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

TEST_F(LeaseCmdsTest, lease6Update) {
    testLease6Update();
}

TEST_F(LeaseCmdsTest, lease6UpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6Update();
}

void LeaseCmdsTest::testLease6UpdateDeclinedLeases() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true, true);

    checkLease6Stats(66, 2, 2, 0);

    checkLease6Stats(99, 2, 2, 0);

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

    checkLease6Stats(66, 2, 1, 0);

    checkLease6Stats(99, 2, 2, 0);

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

TEST_F(LeaseCmdsTest, lease6UpdateDeclinedLeases) {
    testLease6UpdateDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease6UpdateDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateDeclinedLeases();
}

void LeaseCmdsTest::testLease6UpdateNoSubnetId() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

TEST_F(LeaseCmdsTest, lease6UpdateNoSubnetId) {
    testLease6UpdateNoSubnetId();
}

TEST_F(LeaseCmdsTest, lease6UpdateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateNoSubnetId();
}

void LeaseCmdsTest::testLease6UpdateNoSubnetIdDeclinedLeases() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true, true);

    checkLease6Stats(66, 2, 2, 0);

    checkLease6Stats(99, 2, 2, 0);

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

    checkLease6Stats(66, 2, 1, 0);

    checkLease6Stats(99, 2, 2, 0);

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

TEST_F(LeaseCmdsTest, lease6UpdateNoSubnetIdDeclinedLeases) {
    testLease6UpdateNoSubnetIdDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease6UpdateNoSubnetIdDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateNoSubnetIdDeclinedLeases();
}

void LeaseCmdsTest::testLease6UpdateComment() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

TEST_F(LeaseCmdsTest, lease6UpdateComment) {
    testLease6UpdateComment();
}

TEST_F(LeaseCmdsTest, lease6UpdateCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateComment();
}

void LeaseCmdsTest::testLease6UpdateNoLease() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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
    string exp_rsp = "failed to update the lease with address 2001:db8:1::1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

TEST_F(LeaseCmdsTest, lease6UpdateNoLease) {
    testLease6UpdateNoLease();
}

TEST_F(LeaseCmdsTest, lease6UpdateNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateNoLease();
}

void LeaseCmdsTest::testLease6UpdateForceCreate() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

TEST_F(LeaseCmdsTest, lease6UpdateForceCreate) {
    testLease6UpdateForceCreate();
}

TEST_F(LeaseCmdsTest, lease6UpdateForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateForceCreate();
}

void LeaseCmdsTest::testLease6UpdateForceCreateNoSubnetId() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

TEST_F(LeaseCmdsTest, lease6UpdateForceCreateNoSubnetId) {
    testLease6UpdateForceCreateNoSubnetId();
}

TEST_F(LeaseCmdsTest, lease6UpdateForceCreateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateForceCreateNoSubnetId();
}

void LeaseCmdsTest::testLease6UpdateDoNotForceCreate() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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
    string exp_rsp = "failed to update the lease with address 2001:db8:1::1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

TEST_F(LeaseCmdsTest, lease6UpdateDoNotForceCreate) {
    testLease6UpdateDoNotForceCreate();
}

TEST_F(LeaseCmdsTest, lease6UpdateDoNotForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateDoNotForceCreate();
}

void LeaseCmdsTest::testLease4DelMissingParams() {

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

TEST_F(LeaseCmdsTest, lease4DelMissingParams) {
    testLease4DelMissingParams();
}

TEST_F(LeaseCmdsTest, lease4DelMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelMissingParams();
}

void LeaseCmdsTest::testLease4DelByAddrNotFound() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);
}

TEST_F(LeaseCmdsTest, lease4DelByAddrNotFound) {
    testLease4DelByAddrNotFound();
}

TEST_F(LeaseCmdsTest, lease4DelByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddrNotFound();
}

void LeaseCmdsTest::testLease4DelByAddr() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

TEST_F(LeaseCmdsTest, lease4DelByAddr) {
    testLease4DelByAddr();
}

TEST_F(LeaseCmdsTest, lease4DelByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddr();
}

void LeaseCmdsTest::testLease4DelByAddrDeclinedLeases() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true, true);

    checkLease4Stats(44, 2, 2);

    checkLease4Stats(88, 2, 2);

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

    checkLease4Stats(44, 1, 1);

    checkLease4Stats(88, 2, 2);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

TEST_F(LeaseCmdsTest, lease4DelByAddrDeclinedLeases) {
    testLease4DelByAddrDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease4DelByAddrDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddrDeclinedLeases();
}

void LeaseCmdsTest::testLeaseXDelBadUpdateDdnsParam() {

    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.1.0\","
        "        \"update-ddns\": 77"
        "    }\n"
        "}";

    string exp_rsp = "'update-ddns' is not a boolean";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\","
        "        \"update-ddns\": \"bogus\""
        "    }\n"
        "}";

    exp_rsp = "'update-ddns' is not a boolean";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, leaseXDelBadUpdateDdnsParam) {
    testLeaseXDelBadUpdateDdnsParam();
}

TEST_F(LeaseCmdsTest, leaseXDelBadUpdateDdnsParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseXDelBadUpdateDdnsParam();
}

void LeaseCmdsTest::testLease4DelByAddrBadParam() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

TEST_F(LeaseCmdsTest, lease4DelByAddrBadParam) {
    testLease4DelByAddrBadParam();
}

TEST_F(LeaseCmdsTest, lease4DelByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddrBadParam();
}

void LeaseCmdsTest::testLease4DelByHWAddrNotFound() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

TEST_F(LeaseCmdsTest, lease4DelByHWAddrNotFound) {
    testLease4DelByHWAddrNotFound();
}

TEST_F(LeaseCmdsTest, lease4DelByHWAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByHWAddrNotFound();
}

void LeaseCmdsTest::testLease4DelByHWAddr() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

TEST_F(LeaseCmdsTest, lease4DelByHWAddr) {
    testLease4DelByHWAddr();
}

TEST_F(LeaseCmdsTest, lease4DelByHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByHWAddr();
}

void LeaseCmdsTest::testLease4DelByClientIdNotFound() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

TEST_F(LeaseCmdsTest, lease4DelByClientIdNotFound) {
    testLease4DelByClientIdNotFound();
}

TEST_F(LeaseCmdsTest, lease4DelByClientIdNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByClientIdNotFound();
}

void LeaseCmdsTest::testLease4DelByClientId() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

TEST_F(LeaseCmdsTest, lease4DelByClientId) {
    testLease4DelByClientId();
}

TEST_F(LeaseCmdsTest, lease4DelByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByClientId();
}

void LeaseCmdsTest::testLease6DelMissingParams() {

    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by hw-address is not supported in v6. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Delete by hw-address is not allowed in v6.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
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
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6DelMissingParams) {
    testLease6DelMissingParams();
}

TEST_F(LeaseCmdsTest, lease6DelMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelMissingParams();
}

void LeaseCmdsTest::testLease6DelByAddrNotFound() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);
}

TEST_F(LeaseCmdsTest, lease6DelByAddrNotFound) {
    testLease6DelByAddrNotFound();
}

TEST_F(LeaseCmdsTest, lease6DelByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrNotFound();
}

void LeaseCmdsTest::testLease6DelByDuidNotFound() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

TEST_F(LeaseCmdsTest, lease6DelByDuidNotFound) {
    testLease6DelByDuidNotFound();
}

TEST_F(LeaseCmdsTest, lease6DelByDuidNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByDuidNotFound();
}

void LeaseCmdsTest::testLease6DelByAddr() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

TEST_F(LeaseCmdsTest, lease6DelByAddr) {
    testLease6DelByAddr();
}

TEST_F(LeaseCmdsTest, lease6DelByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddr();
}

void LeaseCmdsTest::testLease6DelByAddrDeclinedLeases() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true, true);

    checkLease6Stats(66, 2, 2, 0);

    checkLease6Stats(99, 2, 2, 0);

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

    checkLease6Stats(66, 1, 1, 0);

    checkLease6Stats(99, 2, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

TEST_F(LeaseCmdsTest, lease6DelByAddrDeclinedLeases) {
    testLease6DelByAddrDeclinedLeases();
}

TEST_F(LeaseCmdsTest, lease6DelByAddrDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrDeclinedLeases();
}

void LeaseCmdsTest::testLease6DelByAddrBadParam() {

    // Initialize lease manager (true = v6, true = add leases)
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

TEST_F(LeaseCmdsTest, lease6DelByAddrBadParam) {
    testLease6DelByAddrBadParam();
}

TEST_F(LeaseCmdsTest, lease6DelByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrBadParam();
}

void LeaseCmdsTest::testLease6DelByAddrPrefix() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Let's start with regular address lease and make it a prefix lease.
    Lease6Ptr l = createLease6("2001:db8:1::1", 66, 0x77);
    l->addr_ = IOAddress("2001:db8:1234:ab::");
    l->type_ = Lease::TYPE_PD;
    l->prefixlen_ = 56;
    lmptr_->addLease(l);

    StatsMgr::instance().setValue(StatsMgr::generateName("subnet", 66,
                                                         "assigned-pds" ),
                                  int64_t(1));

    checkLease6Stats(66, 0, 0, 1);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:1234:ab::")));
}

TEST_F(LeaseCmdsTest, lease6DelByAddrPrefix) {
    testLease6DelByAddrPrefix();
}

TEST_F(LeaseCmdsTest, lease6DelByAddrPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrPrefix();
}

void LeaseCmdsTest::testLease6DelByDuid() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

TEST_F(LeaseCmdsTest, lease6DelByDuid) {
    testLease6DelByDuid();
}

TEST_F(LeaseCmdsTest, lease6DelByDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByDuid();
}

void LeaseCmdsTest::testLease4Wipe() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

TEST_F(LeaseCmdsTest, lease4Wipe) {
    testLease4Wipe();
}

TEST_F(LeaseCmdsTest, lease4WipeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4Wipe();
}

void LeaseCmdsTest::testLease4WipeAll() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are gone, too.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

TEST_F(LeaseCmdsTest, lease4WipeAll) {
    testLease4WipeAll();
}

TEST_F(LeaseCmdsTest, lease4WipeAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeAll();
}

void LeaseCmdsTest::testLease4WipeAllNoArgs() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\"\n"
        "}";
    string exp_rsp = "Deleted 4 IPv4 lease(s) from subnet(s) 44 88";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are gone, too.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

TEST_F(LeaseCmdsTest, lease4WipeAllNoArgs) {
    testLease4WipeAllNoArgs();
}

TEST_F(LeaseCmdsTest, lease4WipeAllNoArgsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeAllNoArgs();
}

void LeaseCmdsTest::testLease4WipeNoLeases() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);
}

TEST_F(LeaseCmdsTest, lease4WipeNoLeases) {
    testLease4WipeNoLeases();
}

TEST_F(LeaseCmdsTest, lease4WipeNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeNoLeases();
}

void LeaseCmdsTest::testLease4WipeNoLeasesAll() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

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

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);
}

TEST_F(LeaseCmdsTest, lease4WipeNoLeasesAll) {
    testLease4WipeNoLeasesAll();
}

TEST_F(LeaseCmdsTest, lease4WipeNoLeasesAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeNoLeasesAll();
}

void LeaseCmdsTest::testLease6Wipe() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the leases in subnet 66 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // Make sure the leases from subnet 99 are still there.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

TEST_F(LeaseCmdsTest, lease6Wipe) {
    testLease6Wipe();
}

TEST_F(LeaseCmdsTest, lease6WipeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6Wipe();
}

void LeaseCmdsTest::testLease6WipeAll() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Make sure the leases in subnet 66 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // Make sure the leases from subnet 99 are gone, too.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

TEST_F(LeaseCmdsTest, lease6WipeAll) {
    testLease6WipeAll();
}

TEST_F(LeaseCmdsTest, lease6WipeAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeAll();
}

void LeaseCmdsTest::testLease6WipeAllNoArgs() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\"\n"
        "}";
    string exp_rsp = "Deleted 4 IPv6 lease(s) from subnet(s) 66 99";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Make sure the leases in subnet 66 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // Make sure the leases from subnet 99 are gone, too.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

TEST_F(LeaseCmdsTest, lease6WipeAllNoArgs) {
    testLease6WipeAllNoArgs();
}

TEST_F(LeaseCmdsTest, lease6WipeAllNoArgsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeAllNoArgs();
}

void LeaseCmdsTest::testLease6WipeNoLeases() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

TEST_F(LeaseCmdsTest, lease6WipeNoLeases) {
    testLease6WipeNoLeases();
}

TEST_F(LeaseCmdsTest, lease6WipeNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeNoLeases();
}

void LeaseCmdsTest::testLease6WipeNoLeasesAll() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

TEST_F(LeaseCmdsTest, lease6WipeNoLeasesAll) {
    testLease6WipeNoLeasesAll();
}

TEST_F(LeaseCmdsTest, lease6WipeNoLeasesAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeNoLeasesAll();
}

void LeaseCmdsTest::testLease4BrokenUpdate() {

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Set the sanity checks level.
    CfgMgr::instance().getCurrentCfg()->getConsistency()
        ->setLeaseSanityCheck(CfgConsistency::LEASE_CHECK_FIX);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 444,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"force-create\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv4 subnet with "
                     "subnet-id=444 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4BrokenUpdate) {
    testLease4BrokenUpdate();
}

TEST_F(LeaseCmdsTest, lease4BrokenUpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4BrokenUpdate();
}

void LeaseCmdsTest::testLease6BrokenUpdate() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Set the sanity checks level.
    CfgMgr::instance().getCurrentCfg()->getConsistency()
        ->setLeaseSanityCheck(CfgConsistency::LEASE_CHECK_FIX);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 444,\n"
        "        \"ip-address\": \"2001:db8:1::23\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"force-create\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv6 subnet with "
                     "subnet-id=444 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6BrokenUpdate) {
    testLease6BrokenUpdate();
}

TEST_F(LeaseCmdsTest, lease6BrokenUpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BrokenUpdate();
}

void LeaseCmdsTest::testLease6BulkApply() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 3, 0, 0);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));

    // Check that the leases we deleted are gone,
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

TEST_F(LeaseCmdsTest, lease6BulkApply) {
    testLease6BulkApply();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApply();
}

void LeaseCmdsTest::testLease6BulkApplyAddsOnlyBadParam() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Now send the command. The command uses an invalid state declined (1) for
    // PD prefix.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\",\n"
        "                \"prefix-len\": 48,\n"
        "                \"type\": \"IA_PD\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234,\n"
        "                \"state\": 1"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Check that the lease was not inserted.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
}

TEST_F(LeaseCmdsTest, lease6BulkApplyAddsOnlyBadParam) {
    testLease6BulkApplyAddsOnlyBadParam();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyAddsOnlyBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyAddsOnlyBadParam();
}

void LeaseCmdsTest::testLease6BulkApplyAddsOnly() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

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

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 1, 0, 0);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));
}

TEST_F(LeaseCmdsTest, lease6BulkApplyAddsOnly) {
    testLease6BulkApplyAddsOnly();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyAddsOnlyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyAddsOnly();
}

void LeaseCmdsTest::testLease6BulkApplyUpdatesOnlyBadParam() {

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Let's start with regular address lease and make it a prefix lease.
    Lease6Ptr l = createLease6("2001:db8:1::1", 66, 0x77);
    l->addr_ = IOAddress("2001:db8:1234:ab::");
    l->type_ = Lease::TYPE_PD;
    l->prefixlen_ = 56;
    lmptr_->addLease(l);

    // Now send the command. The command uses an invalid state declined (1) for
    // PD prefix.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1234:ab::\",\n"
        "                \"prefix-len\": 56,\n"
        "                \"type\": \"IA_PD\",\n"
        "                \"duid\": \"77:77:77:77:77:77\",\n"
        "                \"iaid\": 1234,\n"
        "                \"state\": 1"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Check that the lease we inserted is stored.
    Lease6Ptr lease1 = lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:1234:ab::"));
    ASSERT_TRUE(lease1);

    // The IAID should have not been updated for the existing lease.
    EXPECT_EQ(42, lease1->iaid_);
}

TEST_F(LeaseCmdsTest, lease6BulkApplyUpdatesOnlyBadParam) {
    testLease6BulkApplyUpdatesOnlyBadParam();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyUpdatesOnlyBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyUpdatesOnlyBadParam();
}

void LeaseCmdsTest::testLease6BulkApplyUpdatesOnly() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    //  Check that the leases we inserted are stored.
    Lease6Ptr lease1 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    Lease6Ptr lease2 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"));
    ASSERT_TRUE(lease1);
    ASSERT_TRUE(lease2);

    // The IAIDs should have been updated for the existing leases.
    EXPECT_EQ(1234, lease1->iaid_);
    EXPECT_EQ(1234, lease2->iaid_);
}

TEST_F(LeaseCmdsTest, lease6BulkApplyUpdatesOnly) {
    testLease6BulkApplyUpdatesOnly();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyUpdatesOnlyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyUpdatesOnly();
}

void LeaseCmdsTest::testLease6BulkApplyDeletesOnly() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Check that the leases we deleted are gone,
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

TEST_F(LeaseCmdsTest, lease6BulkApplyDeletesOnly) {
    testLease6BulkApplyDeletesOnly();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyDeletesOnlyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyDeletesOnly();
}

void LeaseCmdsTest::testLease6BulkApplyDeleteNonExiting() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

TEST_F(LeaseCmdsTest, lease6BulkApplyDeleteNonExiting) {
    testLease6BulkApplyDeleteNonExiting();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyDeleteNonExitingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyDeleteNonExiting();
}

void LeaseCmdsTest::testLease6BulkApplyRollback() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

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

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));

    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

TEST_F(LeaseCmdsTest, lease6BulkApplyRollback) {
    testLease6BulkApplyRollback();
}

TEST_F(LeaseCmdsTest, lease6BulkApplyRollbackMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyRollback();
}

void LeaseCmdsTest::testLease4ResendDdnsBadParam() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Missing address parameter.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "    }\n"
        "}\n";

    string exp_rsp = "'ip-address' parameter is missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid address family.
    cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "Invalid IPv4 address specified: 2001:db8:1::1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // ip-address is not an address at all.
    cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"221B Baker St.\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "'221B Baker St.' is not a valid IP address.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsBadParam) {
    testLease4ResendDdnsBadParam();
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsBadParam();
}

void LeaseCmdsTest::testLease4ResendDdnsDisabled() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    disableD2();

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.5\""
        "    }\n"
        "}";

    string exp_rsp = "DDNS updating is not enabled";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
    // With D2 disabled there is no queue, size should come back as -1.
    EXPECT_EQ(ncrQueueSize(), -1);
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsDisabled) {
    testLease4ResendDdnsDisabled();
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsDisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsDisabled();
}

void LeaseCmdsTest::testLease4ResendDdnsNoLease() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"192.0.2.5\"\n"
        "    }\n"
        "}\n";
    string exp_rsp = "No lease found for: 192.0.2.5";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsNoLease) {
    testLease4ResendDdnsNoLease();
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsNoLease();
}

void LeaseCmdsTest::testLease4ResendNoHostname() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(lease);
    lease->hostname_ = "";
    lmptr_->updateLease4(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";

    string exp_rsp = "Lease for: 192.0.2.1, has no hostname, nothing to update";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

TEST_F(LeaseCmdsTest, lease4ResendNoHostname) {
    testLease4ResendNoHostname();
}

TEST_F(LeaseCmdsTest, lease4ResendNoHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendNoHostname();
}

void LeaseCmdsTest::testLease4ResendNoDirectionsEnabled() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(lease);
    lease->fqdn_fwd_ = false;
    lease->fqdn_rev_ = false;
    lmptr_->updateLease4(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";

    string exp_rsp = "Neither forward nor reverse updates enabled for lease for: 192.0.2.1";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

TEST_F(LeaseCmdsTest, lease4ResendNoDirectionsEnabled) {
    testLease4ResendNoDirectionsEnabled();
}

TEST_F(LeaseCmdsTest, lease4ResendNoDirectionsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendNoDirectionsEnabled();
}

void LeaseCmdsTest::testLease4ResendDdnsEnabled() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Structure detailing a test scenario.
    struct Scenario {
        std::string description_;
        bool fqdn_fwd_;
        bool fqdn_rev_;
    };

    // Three test scenarios to verify each combination of true flags.
    std::vector<Scenario> scenarios = {
       { "fwd_only", true,  false },
       { "rev_only", false, true},
       { "both",     true,  true},
    };

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";

    // Expected response string.
    string exp_rsp = "NCR generated for: 192.0.2.1, hostname: myhost.example.com.";

    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Fetch the lease so we can update the DDNS direction flags.
        Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.1"));
        ASSERT_TRUE(lease);
        lease->fqdn_rev_ = scenario.fqdn_rev_;
        lease->fqdn_fwd_ = scenario.fqdn_fwd_;
        lmptr_->updateLease4(lease);

        // Queue should be empty.
        ASSERT_EQ(ncrQueueSize(), 0);
        ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        // We should have one entry in the queue.
        ASSERT_EQ(ncrQueueSize(), 1);
        verifyNameChangeRequest(CHG_ADD, scenario.fqdn_rev_, scenario.fqdn_fwd_,
                                "192.0.2.1", "myhost.example.com.");
    }
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsEnabled) {
    testLease4ResendDdnsEnabled();
}

TEST_F(LeaseCmdsTest, lease4ResendDdnsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsEnabled();
}

void LeaseCmdsTest::testLease6ResendDdnsBadParam() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Missing address parameter.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "    }\n"
        "}\n";

    string exp_rsp = "'ip-address' parameter is missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid address family.
    cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"192.0.2.1\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "Invalid IPv6 address specified: 192.0.2.1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // ip-address is not an address at all.
    cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"221B Baker St.\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "'221B Baker St.' is not a valid IP address.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsBadParam) {
    testLease6ResendDdnsBadParam();
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsBadParam();
}

void LeaseCmdsTest::testLease6ResendDdnsDisabled() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Disable DDNS updating.
    disableD2();

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001::dead:beef\"\n"
        "    }\n"
        "}";

    string exp_rsp = "DDNS updating is not enabled";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
    // With D2 disabled there is no queue, size should come back as -1.
    EXPECT_EQ(ncrQueueSize(), -1);
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsDisabled) {
    testLease6ResendDdnsDisabled();
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsDisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsDisabled();
}

void LeaseCmdsTest::testLease6ResendDdnsNoLease() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001::dead:beef\"\n"
        "    }\n"
        "}\n";
    string exp_rsp = "No lease found for: 2001::dead:beef";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsNoLease) {
    testLease6ResendDdnsNoLease();
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsNoLease();
}

void LeaseCmdsTest::testLease6ResendNoHostname() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(lease);
    lease->hostname_ = "";
    lmptr_->updateLease6(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";

    string exp_rsp = "Lease for: 2001:db8:1::1, has no hostname, nothing to update";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

TEST_F(LeaseCmdsTest, lease6ResendNoHostname) {
    testLease6ResendNoHostname();
}

TEST_F(LeaseCmdsTest, lease6ResendNoHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendNoHostname();
}

void LeaseCmdsTest::testLease6ResendNoDirectionsEnabled() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(lease);
    lease->fqdn_fwd_ = false;
    lease->fqdn_rev_ = false;
    lmptr_->updateLease6(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";

    string exp_rsp = "Neither forward nor reverse updates enabled for lease for: 2001:db8:1::1";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

TEST_F(LeaseCmdsTest, lease6ResendNoDirectionsEnabled) {
    testLease6ResendNoDirectionsEnabled();
}

TEST_F(LeaseCmdsTest, lease6ResendNoDirectionsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendNoDirectionsEnabled();
}

void LeaseCmdsTest::testLease6ResendDdnsEnabled() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Structure detailing a test scenario.
    struct Scenario {
        std::string description_;
        bool fqdn_fwd_;
        bool fqdn_rev_;
    };

    // Three test scenarios to verify each combination of true flags.
    std::vector<Scenario> scenarios = {
       { "fwd_only", true,  false },
       { "rev_only", false, true},
       { "both",     true,  true},
    };

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";

    // Expected response string.
    string exp_rsp = "NCR generated for: 2001:db8:1::1, hostname: myhost.example.com.";

    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Fetch the lease so we can update the DDNS direction flags.
        Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
        ASSERT_TRUE(lease);
        lease->fqdn_rev_ = scenario.fqdn_rev_;
        lease->fqdn_fwd_ = scenario.fqdn_fwd_;
        lmptr_->updateLease6(lease);

        // Queue should be empty.
        ASSERT_EQ(ncrQueueSize(), 0);
        ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        // We should have one entry in the queue.
        ASSERT_EQ(ncrQueueSize(), 1);
        verifyNameChangeRequest(CHG_ADD, scenario.fqdn_rev_, scenario.fqdn_fwd_,
                                "2001:db8:1::1", "myhost.example.com.");
    }
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsEnabled) {
    testLease6ResendDdnsEnabled();
}

TEST_F(LeaseCmdsTest, lease6ResendDdnsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsEnabled();
}

void LeaseCmdsTest::testLease4DnsRemoveD2Enabled() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Structure detailing a test scenario.
    struct Scenario {
        std::string description_;
        std::string hostname_;
        bool fqdn_fwd_;
        bool fqdn_rev_;
        std::string update_ddns_;
        bool exp_ncr_;
    };

    bool fwd = true;
    bool rev = true;
    bool ncr = true;

    // Three test scenarios to verify each combination of true flags.
    std::vector<Scenario> scenarios = {
        {
            "no_host",
            "",
            fwd, rev,
            "\"update-ddns\": true",
            !ncr
        },
        {
            "no directions",
            "myhost.example.com.",
            !fwd, !rev,
            "\"update-ddns\": true",
            !ncr
        },
        {
            "fwd_only",
            "myhost.example.com.",
            fwd, !rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "rev_only",
            "myhost.example.com.",
            !fwd, rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "both directions",
            "myhost.example.com.",
            fwd, rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "default update-ddns",
            "myhost.example.com.",
            fwd, rev,
            "",
            !ncr
        },
        {
            "update-ddns = false",
            "myhost.example.com.",
            fwd, rev,
            "\"update-ddns\": false",
            !ncr
        },
    };

    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Let's create a lease with scenario attributes.
        Lease4Ptr lease = createLease4("192.0.2.8", 44, 0x08, 0x42);
        lease->hostname_ = scenario.hostname_;
        lease->fqdn_rev_ = scenario.fqdn_rev_;
        lease->fqdn_fwd_ = scenario.fqdn_fwd_;
        ASSERT_TRUE(lmptr_->addLease(lease));

        // NCR Queue should be empty.
        ASSERT_EQ(ncrQueueSize(), 0);

        // Build the command
        std::stringstream cmd;
        cmd <<
            "{"
            "    \"command\": \"lease4-del\","
            "    \"arguments\": {"
            "        \"ip-address\": \"192.0.2.8\"";

        if (!scenario.update_ddns_.empty()) {
            cmd << "," << scenario.update_ddns_;
        }

        cmd << "}}";

        // Execute the delete command.
        static_cast<void>(testCommand(cmd.str(), CONTROL_RESULT_SUCCESS, "IPv4 lease deleted."));

        if (!scenario.exp_ncr_) {
            // Should not have an ncr.
            ASSERT_EQ(ncrQueueSize(), 0);
        } else {
            // We should have an ncr, verify it.
            ASSERT_EQ(ncrQueueSize(), 1);
            verifyNameChangeRequest(CHG_REMOVE, scenario.fqdn_rev_, scenario.fqdn_fwd_,
                                    lease->addr_.toText(), lease->hostname_);
        }

        // Lease should have been deleted.
        lease = lmptr_->getLease4(lease->addr_);
        ASSERT_FALSE(lease);
    }
}

TEST_F(LeaseCmdsTest, lease4DnsRemoveD2Enabled) {
    testLease4DnsRemoveD2Enabled();
}

TEST_F(LeaseCmdsTest, lease4DnsRemoveD2EnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DnsRemoveD2Enabled();
}

void LeaseCmdsTest::testLease4DnsRemoveD2Disabled() {

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    disableD2();

    // Delete for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"192.0.2.8\",\n"
        "        \"update-ddns\": true\n"
        "    }\n"
        "}";

    // Let's create a lease with scenario attributes.
    Lease4Ptr lease = createLease4("192.0.2.8", 44, 0x08, 0x42);
    lease->hostname_ = "myhost.example.com.";
    lease->fqdn_rev_ = true;
    lease->fqdn_fwd_ = true;
    ASSERT_TRUE(lmptr_->addLease(lease));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Execute the delete command.
    static_cast<void>(testCommand(cmd, CONTROL_RESULT_SUCCESS, "IPv4 lease deleted."));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Lease should have been deleted.
    lease = lmptr_->getLease4(lease->addr_);
    ASSERT_FALSE(lease);
}

TEST_F(LeaseCmdsTest, lease4DnsRemoveD2Disabled) {
    testLease4DnsRemoveD2Disabled();
}

TEST_F(LeaseCmdsTest, lease4DnsRemoveD2DisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DnsRemoveD2Disabled();
}

void LeaseCmdsTest::testLease6DnsRemoveD2Enabled() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Structure detailing a test scenario.
    struct Scenario {
        std::string description_;
        std::string hostname_;
        bool fqdn_fwd_;
        bool fqdn_rev_;
        std::string update_ddns_;
        bool exp_ncr_;
    };

    bool fwd = true;
    bool rev = true;
    bool ncr = true;

    // Three test scenarios to verify each combination of true flags.
    std::vector<Scenario> scenarios = {
        {
            "no_host",
            "",
            fwd, rev,
            "\"update-ddns\": true",
            !ncr
        },
        {
            "no directions",
            "myhost.example.com.",
            !fwd, !rev,
            "\"update-ddns\": true",
            !ncr
        },
        {
            "fwd_only",
            "myhost.example.com.",
            fwd, !rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "rev_only",
            "myhost.example.com.",
            !fwd, rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "both directions",
            "myhost.example.com.",
            fwd, rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "default update-ddns",
            "myhost.example.com.",
            fwd, rev,
            "",
            !ncr
        },
        {
            "update-ddns = false",
            "myhost.example.com.",
            fwd, rev,
            "\"update-ddns\": false",
            !ncr
        },
    };

    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Let's create a lease with scenario attributes.
        Lease6Ptr lease = createLease6("2001:db8:1::8", 66, 0x77);
        lease->hostname_ = scenario.hostname_;
        lease->fqdn_rev_ = scenario.fqdn_rev_;
        lease->fqdn_fwd_ = scenario.fqdn_fwd_;
        ASSERT_TRUE(lmptr_->addLease(lease));

        // NCR Queue should be empty.
        ASSERT_EQ(ncrQueueSize(), 0);

        // Build the command
        std::stringstream cmd;
        cmd <<
            "{"
            "    \"command\": \"lease6-del\","
            "    \"arguments\": {"
            "        \"ip-address\": \"2001:db8:1::8\"\n";

        if (!scenario.update_ddns_.empty()) {
            cmd << "," << scenario.update_ddns_;
        }

        cmd << "}}";

        // Execute the delete command.
        static_cast<void>(testCommand(cmd.str(), CONTROL_RESULT_SUCCESS, "IPv6 lease deleted."));

        if (!scenario.exp_ncr_) {
            // Should not have an ncr.
            ASSERT_EQ(ncrQueueSize(), 0);
        } else {
            // We should have an ncr, verify it.
            ASSERT_EQ(ncrQueueSize(), 1);
            verifyNameChangeRequest(CHG_REMOVE, scenario.fqdn_rev_, scenario.fqdn_fwd_,
                                    lease->addr_.toText(), lease->hostname_);
        }

        // Lease should have been deleted.
        lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
        ASSERT_FALSE(lease);
    }
}

TEST_F(LeaseCmdsTest, lease6DnsRemoveD2Enabled) {
    testLease6DnsRemoveD2Enabled();
}

TEST_F(LeaseCmdsTest, lease6DnsRemoveD2EnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DnsRemoveD2Enabled();
}

void LeaseCmdsTest::testLease6DnsRemoveD2Disabled() {

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    disableD2();

    // Delete for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001:db8:1::8\",\n"
        "        \"update-ddns\": true\n"
        "    }\n"
        "}";

    // Let's create a lease with scenario attributes.
    Lease6Ptr lease = createLease6("2001:db8:1::8", 66, 0x77);
    lease->hostname_ = "myhost.example.com.";
    lease->fqdn_rev_ = true;
    lease->fqdn_fwd_ = true;
    ASSERT_TRUE(lmptr_->addLease(lease));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Execute the delete command.
    static_cast<void>(testCommand(cmd, CONTROL_RESULT_SUCCESS, "IPv6 lease deleted."));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Lease should have been deleted.
    lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
    ASSERT_FALSE(lease);
}

TEST_F(LeaseCmdsTest, lease6DnsRemoveD2Disabled) {
    testLease6DnsRemoveD2Disabled();
}

TEST_F(LeaseCmdsTest, lease6DnsRemoveD2DisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DnsRemoveD2Disabled();
}

// Verify that v4 lease add handles conflict as expected.
TEST_F(LeaseCmdsTest, lease4ConflictingAdd) {
    MultiThreadingTest mt(true);

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Make sure the lease doesn't exist.
    IOAddress addr("192.0.2.1");
    Lease4Ptr lease = lmptr_->getLease4(addr);
    ASSERT_FALSE(lease);

    // Verify stats show no leases.
    checkLease4Stats(44, 0, 0);

    // Lock the address.
    ResourceHandler4 resource_handler;
    ASSERT_TRUE(resource_handler.tryLock4(addr));

    // Now let's try to add the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:192.0.2.1 could not be added.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Lease should not have been added.
    lease = lmptr_->getLease4(addr);
    ASSERT_FALSE(lease);

    // Stats should not have changed.
    checkLease4Stats(44, 0, 0);
}

// Verify that v4 lease update handles conflict as expected.
TEST_F(LeaseCmdsTest, lease4ConflictingUpdate) {
    MultiThreadingTest mt(true);

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Verify stats show no leases.
    checkLease4Stats(44, 2, 0);

    // Make sure the lease exists.
    IOAddress addr("192.0.2.1");
    Lease4Ptr lease = lmptr_->getLease4(addr);
    ASSERT_TRUE(lease);
    // Save a copy of the original lease.
    Lease4 original_lease = *lease;

    // Lock the address.
    ResourceHandler4 resource_handler;
    ASSERT_TRUE(resource_handler.tryLock4(addr));

    // Now let's try to update the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"2a:2b:2c:2d:2e:2f\",\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:192.0.2.1 could not be updated.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Fetch the lease again.
    lease = lmptr_->getLease4(addr);
    ASSERT_TRUE(lease);

    // Lease should not have been changed.
    EXPECT_EQ(original_lease, *lease);
}

// Verify that v6 lease add handles conflict as expected.
TEST_F(LeaseCmdsTest, lease6ConflictingAdd) {
    MultiThreadingTest mt(true);

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Make sure the lease doesn't exist.
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_FALSE(lease);

    // Verify stats show no leases.
    checkLease6Stats(66, 0, 0, 0);

    // Lock the address.
    ResourceHandler resource_handler;
    ASSERT_TRUE(resource_handler.tryLock(Lease::TYPE_NA, addr));

    // Now let's try to add the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:2001:db8:1::1 could not be added.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Lease should not have been added.
    lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_FALSE(lease);

    // Stats should not have changed.
    checkLease6Stats(66, 0, 0, 0);
}

// Verify that v6 lease update handles conflict as expected.
TEST_F(LeaseCmdsTest, lease6ConflictingUpdate) {
    MultiThreadingTest mt(true);

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Verify lease stats show leases.
    checkLease6Stats(66, 2, 0, 0);

    // Make sure the lease exists.
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(lease);
    // Save a copy of the original lease.
    Lease6 original_lease = *lease;

    // Lock the address.
    ResourceHandler resource_handler;
    ASSERT_TRUE(resource_handler.tryLock(Lease::TYPE_NA, addr));

    // Now let's try to update the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"2a:2b:2c:2d:2e:2f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:2001:db8:1::1 could not be updated.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Fetch the lease again.
    lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(lease);

    // Lease should not have been changed.
    EXPECT_EQ(original_lease, *lease);
}

// Verify that v6 lease bulk update handles conflict as expected.
TEST_F(LeaseCmdsTest, testLease6BulkApplyAddConflict) {
    MultiThreadingTest mt(true);

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);
    checkLease6Stats(99, 0, 0, 0);

    // Lock the address.
    IOAddress locked_addr("2001:db8:2::77");
    ResourceHandler resource_handler;
    ASSERT_TRUE(resource_handler.tryLock(Lease::TYPE_NA, locked_addr));

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
        "                \"ip-address\": \"2001:db8:2::77\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::124\",\n"
        "                \"duid\": \"33:33:33:33:33:33\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    auto rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);
    checkLease6Stats(99, 0, 0, 0);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::124")));

    // Check that the lease for locked address was not added.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, locked_addr));

    auto args = rsp->get("arguments");
    auto failed_leases = args->get("failed-leases");
    ASSERT_TRUE(failed_leases);
    ASSERT_EQ(Element::list, failed_leases->getType());
    ASSERT_EQ(1, failed_leases->size());
    checkFailedLease(failed_leases, "IA_NA", locked_addr.toText(),
                     CONTROL_RESULT_ERROR,
                     "ResourceBusy: IP address:2001:db8:2::77 could not be updated.");
}

} // end of anonymous namespace
