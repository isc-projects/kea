// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
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
        isc::config::CommandMgr::instance();
        unloadLibs();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~LibLoadTest() {
        unloadLibs();
    }

    /// @brief Adds library/parameters to list of libraries to be loaded
    void addLib(const std::string& lib, isc::data::ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    /// @brief Load all specified libraries.
    ///
    /// The libraries are stored in libraries
    void loadLibs() {
        ASSERT_TRUE(isc::hooks::HooksManager::loadLibraries(libraries_))
            << "library loading failed";
    }

    /// @brief Unloads all libraries.
    void unloadLibs() {
        ASSERT_NO_THROW(isc::hooks::HooksManager::unloadLibraries());
    }

    /// @brief Checks whether specified command is registered
    ///
    /// @param name name of the command to be checked
    /// @param expect_true true - must be registered, false - must not be
    void checkCommandRegistered(const std::string& name, bool expect_true) {
        // First get the list of registered commands
        isc::data::ConstElementPtr lst = isc::data::Element::fromJSON("{ \"command\": \"list-commands\" }");
        isc::data::ConstElementPtr rsp = isc::config::CommandMgr::instance().processCommand(lst);

        ASSERT_TRUE(rsp);

        isc::data::ConstElementPtr args = rsp->get("arguments");
        ASSERT_TRUE(args);

        std::string args_txt = args->str();

        if (expect_true) {
            EXPECT_TRUE(args_txt.find(name) != std::string::npos);
        } else {
            EXPECT_TRUE(args_txt.find(name) == std::string::npos);
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
    isc::data::ConstElementPtr testCommand(std::string cmd_txt, int exp_result,
                                           std::string exp_txt) {
        // Let's load the library first.
        loadLib();

        isc::data::ConstElementPtr cmd;
        EXPECT_NO_THROW(cmd = isc::data::Element::fromJSON(cmd_txt));
        if (!cmd) {
            ADD_FAILURE() << cmd_txt << " is not a valid JSON, test broken";
            return (isc::data::ConstElementPtr());
        }

        // Process the command and verify response.
        isc::data::ConstElementPtr rsp = isc::config::CommandMgr::instance().processCommand(cmd);
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
                     std::string exp_txt = "") {
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
        if (comment->getType() != isc::data::Element::string) {
            comment = answer->get("text");
        }

        if (!exp_txt.empty()) {
            EXPECT_EQ(exp_txt, comment->stringValue());
        }
    }

    /// @brief Loads the library specified by lib_name_
    void loadLib() {
        if (libraries_.empty()) {
            isc::data::ElementPtr params = isc::data::Element::createMap();
            addLib(lib_name_, params);
        }
        EXPECT_NO_THROW(loadLibs());
    }

    /// @brief Test checks if specified commands are provided by the library.
    ///
    /// @param cms a vector of string with command names
    void testCommands(const std::vector<std::string> cmds) {
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
        isc::dhcp_ddns::NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = isc::dhcp::CfgMgr::instance().getD2ClientMgr().peekAt(0));
        ASSERT_TRUE(ncr);

        EXPECT_EQ(type, ncr->getChangeType());
        EXPECT_EQ(forward, ncr->isForwardChange());
        EXPECT_EQ(reverse, ncr->isReverseChange());
        EXPECT_EQ(addr, ncr->getIpAddress());

        if (!fqdn.empty()) {
           EXPECT_EQ(fqdn, ncr->getFqdn());
        }

        // Process the message off the queue
        ASSERT_NO_THROW(isc::dhcp::CfgMgr::instance().getD2ClientMgr().runReadyIO());
    }

    /// List of libraries to be/being loaded (usually just one)
    isc::hooks::HookLibsCollection libraries_;

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
    isc::dhcp::LeaseMgr* lmptr_;

    /// @brief Reference to the D2 client manager.
    isc::dhcp::D2ClientMgr& d2_mgr_;

    /// @brief Constructor
    ///
    /// Sets the library filename and clears the lease manager pointer.
    /// Also ensured there is no lease manager leftovers from previous
    /// test.
    LeaseCmdsTest()
        : LibLoadTest(LEASE_CMDS_LIB_SO),
        d2_mgr_(isc::dhcp::CfgMgr::instance().getD2ClientMgr()) {
        isc::dhcp::LeaseMgrFactory::destroy();
        enableD2();
        lmptr_ = 0;
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Destructor
    ///
    /// Removes library (if any), destroys lease manager (if any).
    virtual ~LeaseCmdsTest() {
        // destroys lease manager first because the other order triggers
        // a clang/boost bug
        isc::dhcp::LeaseMgrFactory::destroy();
        disableD2();
        unloadLibs();
        lmptr_ = 0;
        isc::stats::StatsMgr::instance().removeAll();
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
    isc::dhcp::Lease4Ptr createLease4(const std::string& ip_address,
                                      const isc::dhcp::SubnetID& subnet_id,
                                      const uint8_t hw_address_pattern,
                                      const uint8_t client_id_pattern,
                                      bool declined = false) {
        isc::dhcp::Lease4Ptr lease(new isc::dhcp::Lease4());

        lease->addr_ = isc::asiolink::IOAddress(ip_address);

        // Set other parameters.  For historical reasons, address 0 is not used.
        lease->hwaddr_.reset(new isc::dhcp::HWAddr(std::vector<uint8_t>(6, hw_address_pattern), isc::dhcp::HTYPE_ETHER));
        lease->client_id_ = isc::dhcp::ClientIdPtr(new isc::dhcp::ClientId(std::vector<uint8_t>(8, client_id_pattern)));
        // Purposely using high cltt and valid lifetime to test that
        // expiration time is cast properly.
        lease->valid_lft_ = HIGH_VALID_LIFETIME; // Very high valid lifetime
        lease->cltt_ = DEC_2030_TIME; // December 11th 2030
        lease->updateCurrentExpirationTime();
        if (declined) {
            lease->state_ = isc::dhcp::Lease::STATE_DECLINED;
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
    isc::dhcp::Lease6Ptr createLease6(const std::string& ip_address,
                                      const isc::dhcp::SubnetID& subnet_id,
                                      const uint8_t duid_pattern,
                                      bool declined = false) {
        isc::dhcp::Lease6Ptr lease(new isc::dhcp::Lease6());

        lease->addr_ = isc::asiolink::IOAddress(ip_address);
        lease->type_ = isc::dhcp::Lease::TYPE_NA;
        lease->prefixlen_ = 128;
        lease->iaid_ = 42;
        lease->duid_ = isc::dhcp::DuidPtr(new isc::dhcp::DUID(std::vector<uint8_t>(8, duid_pattern)));
        lease->preferred_lft_ = 1800;
        // Purposely using high cltt and valid lifetime to test that
        // expiration time is cast properly.
        lease->valid_lft_ = HIGH_VALID_LIFETIME; // Very high valid lifetime
        lease->cltt_ = DEC_2030_TIME; // December 11th 2030
        lease->updateCurrentExpirationTime();
        if (declined) {
            lease->state_ = isc::dhcp::Lease::STATE_DECLINED;
        }
        lease->subnet_id_ = subnet_id;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "myhost.example.com.";

        return (lease);
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
        isc::dhcp::LeaseMgrFactory::destroy();
        std::ostringstream s;
        s << "type=memfile persist=false " << (v6 ? "universe=6" : "universe=4");
        isc::dhcp::LeaseMgrFactory::create(s.str());

        lmptr_ = &(isc::dhcp::LeaseMgrFactory::instance());
        ASSERT_TRUE(lmptr_);

        isc::dhcp::CfgMgr& cfg_mgr = isc::dhcp::CfgMgr::instance();
        if (v6) {
            isc::dhcp::Subnet6Ptr subnet66(new isc::dhcp::Subnet6(isc::asiolink::IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4, 66));
            isc::dhcp::Subnet6Ptr subnet99(new isc::dhcp::Subnet6(isc::asiolink::IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4, 99));
            isc::dhcp::CfgSubnets6Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();
            subnets->add(subnet66);
            subnets->add(subnet99);
            cfg_mgr.commit();
        } else {
            isc::dhcp::Subnet4Ptr subnet44(new isc::dhcp::Subnet4(isc::asiolink::IOAddress("192.0.2.0"), 24, 1, 2, 3, 44));
            isc::dhcp::Subnet4Ptr subnet88(new isc::dhcp::Subnet4(isc::asiolink::IOAddress("192.0.3.0"), 24, 1, 2, 3, 88));
            isc::dhcp::CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();
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
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 66, "declined-addresses"),
                        int64_t(2));
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 99, "declined-addresses"),
                        int64_t(2));
                } else {
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 66, "declined-addresses"),
                        int64_t(0));
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 99, "declined-addresses"),
                        int64_t(0));
                }
                isc::stats::StatsMgr::instance().setValue(
                        isc::stats::StatsMgr::generateName("subnet", 66, "assigned-nas" ),
                    int64_t(2));
                isc::stats::StatsMgr::instance().setValue(
                        isc::stats::StatsMgr::generateName("subnet", 99, "assigned-nas" ),
                    int64_t(2));
            } else {
                lmptr_->addLease(createLease4("192.0.2.1", 44, 0x08, 0x42, declined));
                lmptr_->addLease(createLease4("192.0.2.2", 44, 0x09, 0x56, declined));
                lmptr_->addLease(createLease4("192.0.3.1", 88, 0x08, 0x42, declined));
                lmptr_->addLease(createLease4("192.0.3.2", 88, 0x09, 0x56, declined));
                if (declined) {
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 44, "declined-addresses"),
                        int64_t(2));
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 88, "declined-addresses"),
                        int64_t(2));
                } else {
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 44, "declined-addresses"),
                        int64_t(0));
                    isc::stats::StatsMgr::instance().setValue(
                            isc::stats::StatsMgr::generateName("subnet", 88, "declined-addresses"),
                        int64_t(0));
                }
                isc::stats::StatsMgr::instance().setValue(
                        isc::stats::StatsMgr::generateName("subnet", 44, "assigned-addresses"),
                    int64_t(2));
                isc::stats::StatsMgr::instance().setValue(
                        isc::stats::StatsMgr::generateName("subnet", 88, "assigned-addresses"),
                    int64_t(2));
            }
        }
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
    void checkFailedLease(const isc::data::ConstElementPtr& failed_leases_list,
                          const std::string& expected_type,
                          const std::string& expected_ip_address,
                          const int expected_control_result,
                          const std::string& expected_error_msg = "") {
        ASSERT_TRUE(failed_leases_list);

        for (auto i = 0; i < failed_leases_list->size(); ++i) {
            auto failed_lease = failed_leases_list->get(i);
            ASSERT_TRUE(failed_lease);
            ASSERT_EQ(isc::data::Element::map, failed_lease->getType());

            auto ip_address = failed_lease->get("ip-address");
            ASSERT_TRUE(ip_address);
            ASSERT_EQ(isc::data::Element::string, ip_address->getType());

            if (ip_address->stringValue() == expected_ip_address) {
                auto lease_type = failed_lease->get("type");
                ASSERT_TRUE(lease_type);
                ASSERT_EQ(isc::data::Element::string, lease_type->getType());
                EXPECT_EQ(expected_type, lease_type->stringValue());

                auto control_result = failed_lease->get("result");
                ASSERT_TRUE(control_result);
                ASSERT_EQ(isc::data::Element::integer, control_result->getType());
                EXPECT_EQ(expected_control_result, control_result->intValue());

                if (!expected_error_msg.empty()) {
                    auto error_msg = failed_lease->get("error-message");
                    ASSERT_TRUE(error_msg);
                    ASSERT_EQ(isc::data::Element::string, error_msg->getType());
                    EXPECT_EQ(expected_error_msg, error_msg->stringValue());
                }

                return;
            }
        }

        ADD_FAILURE() << "expected lease not found";
    }

    /// @brief Enables DHCP-DDNS updates.
    void enableD2() {
        isc::dhcp::D2ClientConfigPtr cfg(new isc::dhcp::D2ClientConfig());
        ASSERT_NO_THROW(cfg->enableUpdates(true));
        ASSERT_NO_THROW(isc::dhcp::CfgMgr::instance().setD2ClientConfig(cfg));
        d2_mgr_.startSender(std::bind(&LeaseCmdsTest::d2ErrorHandler, this,
                                      std::placeholders::_1, std::placeholders::_2));
    }

    /// @brief Disables DHCP-DDNS updates.
    void disableD2() {
        d2_mgr_.stopSender();
        // Default constructor creates a config with DHCP-DDNS updates
        // disabled.
        isc::dhcp::D2ClientConfigPtr cfg(new isc::dhcp::D2ClientConfig());
        isc::dhcp::CfgMgr::instance().setD2ClientConfig(cfg);
    }

    /// @brief No-op error handler for D2.
    void d2ErrorHandler(const isc::dhcp_ddns::NameChangeSender::Result,
                        isc::dhcp_ddns::NameChangeRequestPtr&) {
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

    /// @brief Check that leaseX-del checks update-ddns input.
    void testLeaseXDelBadUpdateDdnsParam();
};

} // end of anonymous namespace
