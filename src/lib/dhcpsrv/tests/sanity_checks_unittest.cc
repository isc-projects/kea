// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_consistency.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/sanity_checks_parser.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/sanity_checker.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <testutils/log_utils.h>
#include <util/range_utilities.h>
#include <cc/data.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

class SanityChecksTest : public ::testing::Test {
public:

    SanityChecksTest() {
        LeaseMgrFactory::destroy();
    }

    void startLeaseBackend(bool v6) {
        std::ostringstream s;
        s << "type=memfile " << (v6 ? "universe=6 " : "universe=4 ")
          << "persist=false lfc-interval=0";
        LeaseMgrFactory::create(s.str());
    }

    void setLeaseCheck(CfgConsistency::LeaseSanity sanity) {
        CfgMgr::instance().getCurrentCfg()->getConsistency()->setLeaseSanityCheck(sanity);
    }

    ~SanityChecksTest() {
        CfgMgr::instance().clear();
        LeaseMgrFactory::destroy();
    }

    /// @brief Generates a simple IPv4 lease.
    ///
    /// The HW address is randomly generated, subnet_id is specified.
    ///
    /// @param address Lease address.
    /// @param subnet_id ID of the subnet to use.
    ///
    /// @return new lease with random content
    Lease4Ptr newLease4(const IOAddress& address, SubnetID subnet_id) {

        // Randomize HW address.
        vector<uint8_t> mac(6);
        isc::util::fillRandom(mac.begin(), mac.end());
        HWAddrPtr hwaddr(new HWAddr(mac, HTYPE_ETHER));

        vector<uint8_t> clientid(1);

        time_t timestamp = time(0) - 86400 + random() % 86400;

        // Return created lease.
        return (Lease4Ptr(new Lease4(address, hwaddr,
                                     &clientid[0], 0, // no client-id
                                     1200, // valid
                                     timestamp, subnet_id, false, false, "")));
    }

    /// @brief Generates a simple IPv6 lease.
    ///
    /// The DUID and IAID are randomly generated, subnet_id is specified.
    ///
    /// @param address Lease address.
    /// @param subnet_id ID of the subnet to use.
    ///
    /// @return new lease with random content
    Lease6Ptr newLease6(const IOAddress& address, SubnetID subnet_id) {
        // Let's generate DUID of random length.
        std::vector<uint8_t> duid_vec(8 + random()%20);
        // And then fill it with random value.
        isc::util::fillRandom(duid_vec.begin(), duid_vec.end());
        DuidPtr duid(new DUID(duid_vec));

        Lease::Type lease_type = Lease::TYPE_NA;
        uint32_t iaid = 1 + random()%100;

        std::ostringstream hostname;
        hostname << "hostname" << (random() % 2048);

        // Return created lease.
        Lease6Ptr lease(new Lease6(lease_type, address, duid, iaid,
                                   1000, 1200, // pref, valid
                                   subnet_id,
                                   false, false, "")); // fqdn fwd, rev, hostname
        return (lease);
    }

    Subnet4Ptr createSubnet4(string subnet_txt, SubnetID id) {
        size_t pos = subnet_txt.find("/");
        isc::asiolink::IOAddress addr(subnet_txt.substr(0, pos));
        size_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

        return (Subnet4Ptr(new Subnet4(addr, len, 1000, 2000, 3000, id)));
    }

    Subnet6Ptr createSubnet6(string subnet_txt, SubnetID id) {
        size_t pos = subnet_txt.find("/");
        isc::asiolink::IOAddress addr(subnet_txt.substr(0, pos));
        size_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

        return (Subnet6Ptr(new Subnet6(addr, len, 1000, 2000, 3000, 4000, id)));
    }

    void
    parserCheck(SrvConfig& cfg, const string& txt, bool exp_throw,
                CfgConsistency::LeaseSanity exp_sanity,
                CfgConsistency::ExtendedInfoSanity exp_sanity2) {

        // Reset to defaults.
        cfg.getConsistency()->setLeaseSanityCheck(CfgConsistency::LEASE_CHECK_NONE);
        cfg.getConsistency()->setExtendedInfoSanityCheck(CfgConsistency::EXTENDED_INFO_CHECK_FIX);

        SanityChecksParser parser;

        ElementPtr json;
        EXPECT_NO_THROW(json = Element::fromJSON(txt));

        if (exp_throw) {
            // Should throw DhcpConfigError.
            try {
                parser.parse(cfg, json);
                ADD_FAILURE() << "should throw not did not throw";
                return;
            } catch (const DhcpConfigError&) {
                return;
            } catch (const exception& ex) {
                ADD_FAILURE() << "throw another exception with " << ex.what();
            }
        } else {
            // Should not throw.
            try {
                parser.parse(cfg, json);
            } catch (const exception& ex) {
                ADD_FAILURE() << "throw an exception with " << ex.what();
            }
        }

        EXPECT_EQ(cfg.getConsistency()->getLeaseSanityCheck(), exp_sanity);
        EXPECT_EQ(cfg.getConsistency()->getExtendedInfoSanityCheck(), exp_sanity2);
    }

};

// Verify whether configuration parser is able to understand the values
// that are valid and reject those that are not.
TEST_F(SanityChecksTest, leaseCheck) {

    // These are valid and should be accepted.
    string valid1 = "{ \"lease-checks\": \"none\" }";
    string valid2 = "{ \"lease-checks\": \"warn\" }";
    string valid3 = "{ \"lease-checks\": \"fix\" }";
    string valid4 = "{ \"lease-checks\": \"fix-del\" }";
    string valid5 = "{ \"lease-checks\": \"del\" }";

    // These are not valid values or types.
    string bogus1 = "{ \"lease-checks\": \"sanitize\" }";
    string bogus2 = "{ \"lease-checks\": \"ignore\" }";
    string bogus3 = "{ \"lease-checks\": true }";
    string bogus4 = "{ \"lease-checks\": 42 }";

    // These are valid and should be accepted.
    string valid6 = "{ \"extended-info-checks\": \"none\" }";
    string valid7 = "{ \"extended-info-checks\": \"fix\" }";
    string valid8 = "{ \"extended-info-checks\": \"strict\" }";
    string valid9 = "{ \"extended-info-checks\": \"pedantic\" }";
    string valid10 = "{ \"lease-checks\": \"fix\",\n"
        " \"extended-info-checks\": \"fix\" }";

    string bogus5 = "{ \"extended-info-checks\": \"sanitize\" }";
    string bogus6 = "{ \"extended-info-checks\": \"ignore\" }";
    string bogus7 = "{ \"extended-info-checks\": true }";
    string bogus8 = "{ \"extended-info-checks\": 42 }";

    SrvConfig cfg;

    // The lease default should be to none.
    EXPECT_EQ(cfg.getConsistency()->getLeaseSanityCheck(),
              CfgConsistency::LEASE_CHECK_NONE);

    // The extended info default should be to fix.
    EXPECT_EQ(cfg.getConsistency()->getExtendedInfoSanityCheck(),
              CfgConsistency::EXTENDED_INFO_CHECK_FIX);

    parserCheck(cfg, valid1, false, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, valid2, false, CfgConsistency::LEASE_CHECK_WARN,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, valid3, false, CfgConsistency::LEASE_CHECK_FIX,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, valid4, false, CfgConsistency::LEASE_CHECK_FIX_DEL,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, valid5, false, CfgConsistency::LEASE_CHECK_DEL,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);

    parserCheck(cfg, bogus1, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, bogus2, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, bogus3, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, bogus4, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);

    parserCheck(cfg, valid6, false, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_NONE);
    parserCheck(cfg, valid7, false, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, valid8, false, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_STRICT);
    parserCheck(cfg, valid9, false, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
    parserCheck(cfg, valid10, false, CfgConsistency::LEASE_CHECK_FIX,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);

    parserCheck(cfg, bogus5, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, bogus6, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, bogus7, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
    parserCheck(cfg, bogus8, true, CfgConsistency::LEASE_CHECK_NONE,
                CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// Verify whether sanity checker works as expected (valid v4).
TEST_F(SanityChecksTest,  valid4) {
    // Create network and lease.
    CfgMgr::instance().setFamily(AF_INET);
    Subnet4Ptr subnet = createSubnet4("192.168.1.0/24", 1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    IOAddress addr("192.168.1.1");
    Lease4Ptr lease = newLease4(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here in the same subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet->getID(), lease->subnet_id_);
}

// Verify whether sanity checker works as expected (valid v6).
TEST_F(SanityChecksTest,  valid6) {
    // Create network and lease.
    CfgMgr::instance().setFamily(AF_INET6);
    Subnet6Ptr subnet = createSubnet6("2001:db8:1::/64", 1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = newLease6(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here in the same subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet->getID(), lease->subnet_id_);
}

// Verify whether sanity checker works as expected (wrong subnet v4).
TEST_F(SanityChecksTest,  wrongSubnet4) {
    // Create networks and lease in the second and wrong subnet.
    CfgMgr::instance().setFamily(AF_INET);
    Subnet4Ptr subnet1 = createSubnet4("192.168.1.0/24", 1);
    Subnet4Ptr subnet2 = createSubnet4("192.168.2.0/24", 2);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);
    IOAddress addr("192.168.1.1");
    Lease4Ptr lease = newLease4(addr, 2);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here but was moved to the first and right subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet1->getID(), lease->subnet_id_);
}

// Verify whether sanity checker works as expected (wrong subnet v6).
TEST_F(SanityChecksTest,  wrongSubnet6) {
    // Create networks and lease in the second and wrong subnet.
    CfgMgr::instance().setFamily(AF_INET6);
    Subnet6Ptr subnet1 = createSubnet6("2001:db8:1::/64", 1);
    Subnet6Ptr subnet2 = createSubnet6("2001:db8:2::/64", 2);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = newLease6(addr, 2);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here but was moved to the first and right subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet1->getID(), lease->subnet_id_);
}

// Verify whether sanity checker works as expected (no subnet v4).
TEST_F(SanityChecksTest,  noSubnet4) {
    // Create network and lease in a wrong subnet.
    CfgMgr::instance().setFamily(AF_INET);
    Subnet4Ptr subnet = createSubnet4("192.168.2.0/24", 1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    IOAddress addr("192.168.1.1");
    Lease4Ptr lease = newLease4(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease was removed because its subnet does not exist,
    EXPECT_FALSE(lease);
}

// Verify whether sanity checker works as expected (no subnet v6).
TEST_F(SanityChecksTest,  noSubnet6) {
    // Create network and lease in a wrong subnet.
    CfgMgr::instance().setFamily(AF_INET6);
    Subnet6Ptr subnet = createSubnet6("2001:db8:2::/64", 1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = newLease6(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease was removed because its subnet does not exist,
    EXPECT_FALSE(lease);
}

// Verify whether sanity checker works as expected (guard v4).
TEST_F(SanityChecksTest, guard4) {
    // Create networks and lease in the first and guarded subnet.
    CfgMgr::instance().setFamily(AF_INET);
    Subnet4Ptr subnet1 = createSubnet4("192.168.1.0/24", 1);
    subnet1->allowClientClass("foo");
    Subnet4Ptr subnet2 = createSubnet4("192.168.1.100/24", 2);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);
    IOAddress addr("192.168.1.1");
    Lease4Ptr lease = newLease4(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here and in the guarded subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet1->getID(), lease->subnet_id_);
}

// Verify whether sanity checker works as expected (guard v6).
TEST_F(SanityChecksTest, guard6) {
    // Create networks and lease in the first and guarded subnet.
    CfgMgr::instance().setFamily(AF_INET6);
    Subnet6Ptr subnet1 = createSubnet6("2001:db8:1::/64", 1);
    subnet1->allowClientClass("foo");
    Subnet6Ptr subnet2 = createSubnet6("2001:db8:2::100/64", 2);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = newLease6(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here and in the guarded subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet1->getID(), lease->subnet_id_);
}

// Verify whether sanity checker works as expected (guard only v4).
TEST_F(SanityChecksTest, guardOnly4) {
    // Create guarded network and lease.
    CfgMgr::instance().setFamily(AF_INET);
    Subnet4Ptr subnet = createSubnet4("192.168.1.0/24", 1);
    subnet->allowClientClass("foo");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    IOAddress addr("192.168.1.1");
    Lease4Ptr lease = newLease4(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here in the same subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet->getID(), lease->subnet_id_);
}

// Verify whether sanity checker works as expected (valid v6).
TEST_F(SanityChecksTest, guardOnly6) {
    // Create guarded network and lease.
    CfgMgr::instance().setFamily(AF_INET6);
    Subnet6Ptr subnet = createSubnet6("2001:db8:1::/64", 1);
    subnet->allowClientClass("foo");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = newLease6(addr, 1);

    // Check the lease.
    setLeaseCheck(CfgConsistency::LEASE_CHECK_FIX_DEL);
    SanityChecker checker;
    checker.checkLease(lease);

    // Verify the lease is still here in the same subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ(subnet->getID(), lease->subnet_id_);
}

class ExtendedInfoChecksTest : public LogContentTest {
public:

    /// @brief Generates a simple IPv4 lease.
    ///
    /// The HW address is randomly generated, user context is specified.
    ///
    /// @param address Lease address.
    /// @param user_context User context to use.
    ///
    /// @return new lease with random content.
    Lease4Ptr newLease4(const IOAddress& address,
                        ConstElementPtr user_context) {

        // Randomize HW address.
        vector<uint8_t> mac(6);
        isc::util::fillRandom(mac.begin(), mac.end());
        HWAddrPtr hwaddr(new HWAddr(mac, HTYPE_ETHER));

        vector<uint8_t> clientid(1);

        time_t timestamp = time(0) - 86400 + random() % 86400;

        // Return created lease.
        Lease4Ptr lease(new Lease4(address, hwaddr,
                                   &clientid[0], 0, // no client-id
                                   1200, // valid
                                   timestamp, 1, false, false, ""));
        lease->setContext(user_context);
        return(lease);
    }

    /// @brief Generates a simple IPv6 lease.
    ///
    /// The DUID and IAID are randomly generated, user context is specified.
    ///
    /// @param address Lease address.
    /// @param user_context User context to use.
    ///
    /// @return new lease with random content.
    Lease6Ptr newLease6(const IOAddress& address,
                        ConstElementPtr user_context) {
        // Let's generate DUID of random length.
        std::vector<uint8_t> duid_vec(8 + random()%20);
        // And then fill it with random value.
        isc::util::fillRandom(duid_vec.begin(), duid_vec.end());
        DuidPtr duid(new DUID(duid_vec));

        Lease::Type lease_type = Lease::TYPE_NA;
        uint32_t iaid = 1 + random()%100;

        std::ostringstream hostname;
        hostname << "hostname" << (random() % 2048);

        // Return created lease.
        Lease6Ptr lease(new Lease6(lease_type, address, duid, iaid,
                                   1000, 1200, // pref, valid
                                   1, false, false, ""));
        lease->setContext(user_context);
        return(lease);
    }

    /// @brief Check IPv4 scenario.
    ///
    /// @brief original Original user context.
    /// @brief expected Expected user context.
    /// @brief sanity Extended info sanity level.
    /// @break logs Expected log messages.
    void check4(string description, string original, string expected,
                CfgConsistency::ExtendedInfoSanity sanity,
                vector<string> logs = {}) {
        ElementPtr orig_context;
        if (!original.empty()) {
            ASSERT_NO_THROW(orig_context = Element::fromJSON(original))
                << "invalid original user context, test " << description
                << " is broken";
        }
        ElementPtr exp_context;
        if (!expected.empty()) {
            ASSERT_NO_THROW(exp_context = Element::fromJSON(expected))
                << "invalid expected user context, test " << description
                << " is broken";
        }

        Lease4Ptr lease = newLease4(IOAddress("192.168.1.1"), orig_context);
        ConstElementPtr before;
        if (orig_context) {
            before = isc::data::copy(orig_context);
        }
        for (const string& log : logs) {
            addString(log);
        }

        bool ret = LeaseMgr::upgradeLease4ExtendedInfo(lease, sanity);
        ConstElementPtr after = lease->getContext();
        if (!before && !after) {
            EXPECT_FALSE(ret) << "null before and null after";
        } else if ((before && !after) || (!before && after)) {
            EXPECT_TRUE(ret) << "only one of before and after is null";
        } else if (before->equals(*after)) {
            EXPECT_FALSE(ret) << "before == after";
        } else {
            EXPECT_TRUE(ret) << "before != after";
        }
        if (!exp_context) {
            EXPECT_FALSE(after) << "expected null, got " << *after;
        } else {
            ASSERT_TRUE(after) << "expected not null, got null";
            EXPECT_TRUE(exp_context->equals(*after))
                << "expected: " << *exp_context << std::endl
                << "actual: " << *after << std::endl;
        }
        EXPECT_TRUE(checkFile());
    }

    /// @brief Check IPv6 scenario.
    ///
    /// @brief original Original user context.
    /// @brief expected Expected user context.
    /// @brief sanity Extended info sanity level.
    /// @break logs Expected log messages.
    void check6(string description, string original, string expected,
                CfgConsistency::ExtendedInfoSanity sanity,
                vector<string> logs = {}) {
        ElementPtr orig_context;
        if (!original.empty()) {
            ASSERT_NO_THROW(orig_context = Element::fromJSON(original))
                << "invalid original user context, test " << description
                << " is broken";
        }
        ElementPtr exp_context;
        if (!expected.empty()) {
            ASSERT_NO_THROW(exp_context = Element::fromJSON(expected))
                << "invalid expected user context, test " << description
                << " is broken";
        }

        Lease6Ptr lease = newLease6(IOAddress("2001::1"), orig_context);
        ConstElementPtr before;
        if (orig_context) {
            before = isc::data::copy(orig_context);
        }
        for (const string& log : logs) {
            addString(log);
        }

        bool ret = LeaseMgr::upgradeLease6ExtendedInfo(lease, sanity);
        ConstElementPtr after = lease->getContext();
        if (!before && !after) {
            EXPECT_FALSE(ret) << "null before and null after";
        } else if ((before && !after) || (!before && after)) {
            EXPECT_TRUE(ret) << "only one of before and after is null";
        } else if (before->equals(*after)) {
            EXPECT_FALSE(ret) << "before == after";
        } else {
            EXPECT_TRUE(ret) << "before != after";
        }
        if (!exp_context) {
            EXPECT_FALSE(after) << "expected null, got " << *after;
        } else {
            ASSERT_TRUE(after) << "expected not null, got null";
            EXPECT_TRUE(exp_context->equals(*after))
                << "expected: " << *exp_context << std::endl
                << "actual: " << *after << std::endl;
        }
        EXPECT_TRUE(checkFile());
    }
};

// No user context is right for any sanity check level including the highest.
TEST_F(ExtendedInfoChecksTest, noUserContext4) {
    string description = "no user context, pedantic";
    check4(description, "", "", CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
}

// User context with a bad type is right only when no check is done.
TEST_F(ExtendedInfoChecksTest, badTypeUserContext4none) {
    string description = "user context not a map, none";
    check4(description, "1", "1", CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// User context with a bad type is refused by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeUserContext4) {
    string description = "user context not a map, fix";
    check4(description, "1", "", CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in user context a problem was found:"
             " user context is not a map)" });
}

// Empty user context is right only when no check is done.
TEST_F(ExtendedInfoChecksTest, emptyTypeUserContext4none) {
    string description = "empty user context, none";
    check4(description, "{ }", "{ }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// Empty user context is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, emptyTypeUserContext4) {
    string description = "empty user context, fix";
    check4(description, "{ }", "", CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// No ISC entry is right in all cases.
TEST_F(ExtendedInfoChecksTest, noISC4) {
    string description = "no ISC entry, pedantic";
    check4(description, "{ \"foo\": 1 }", "{ \"foo\": 1 }",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
}

// ISC entry with a bad type is right only when no check is done.
TEST_F(ExtendedInfoChecksTest, badTypeISC4none) {
    string description = "ISC entry no a map, none";
    check4(description, "{ \"ISC\": 1 }", "{ \"ISC\": 1 }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// ISC entry with a bad type is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeISC4) {
    string description = "ISC entry no a map, fix";
    check4(description, "{ \"ISC\": 1 }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in isc a problem was found:"
             " ISC entry is not a map)" });
}

// When the ISC entry is dropped other entries are kept.
TEST_F(ExtendedInfoChecksTest, badTypeISC4other) {
    string description = "ISC entry no a map with others, fix";
    check4(description, "{ \"ISC\": 1, \"foo\": 2 }", "{ \"foo\": 2 }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in isc a problem was found:"
             " ISC entry is not a map)" });
}

// Empty ISC entry is kept only when no check is done.
TEST_F(ExtendedInfoChecksTest, emptyISC4none) {
    string description = "empty ISC entry, none";
    check4(description, "{ \"ISC\": { } }", "{ \"ISC\": { } }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// Empty ISC entry is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, emptyISC4) {
    string description = "empty ISC entry, fix";
    check4(description, "{ \"ISC\": { } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// No relay-agent-info entry is right at all sanity levels.
TEST_F(ExtendedInfoChecksTest, noRAI) {
    string description = "no RAI, pedantic";
    check4(description, "{ \"ISC\": { \"foo\": 1 } }",
           "{ \"ISC\": { \"foo\": 1 } }",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
}

// relay-agent-info entry with a bad type is right only when no check is done.
TEST_F(ExtendedInfoChecksTest, badTypeRAInone) {
    string description = "RAI is not a string or a map, none";
    check4(description, "{ \"ISC\": { \"relay-agent-info\": true } }",
           "{ \"ISC\": { \"relay-agent-info\": true } }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// relay-agent-info entry with a bad type is dropped by all not none sanity
// check levels.
TEST_F(ExtendedInfoChecksTest, badTypeRAI) {
    string description = "RAI is not a string or a map, fix";
    check4(description, "{ \"ISC\": { \"relay-agent-info\": true } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in relay-agent-info a problem was found:"
             " relay-agent-info is not a map or a string)" });
}

// When relay-agent-info entry is dropped other entries are kept.
TEST_F(ExtendedInfoChecksTest, badTypeRAIother) {
    string description = "RAI is not a string or a map with others, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": true, \"foo\": 1 } }",
           "{ \"ISC\": { \"foo\": 1 } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in relay-agent-info a problem was found:"
             " relay-agent-info is not a map or a string)" });
}

// String relay-agent-info entry which can't be decoded is right
// only when no check is done.
TEST_F(ExtendedInfoChecksTest, badEncodingStringRAInone) {
    string description = "string RAI with a junk value, none";
    check4(description, "{ \"ISC\": { \"relay-agent-info\": \"foo\" } }",
           "{ \"ISC\": { \"relay-agent-info\": \"foo\" } }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// String relay-agent-info entry which can't be decoded is dropped
// by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badEncodingStringRAI) {
    string description = "string RAI with a junk value, fix";
    check4(description, "{ \"ISC\": { \"relay-agent-info\": \"foo\" } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in rai a problem was found:"
             " 'foo' is not a valid string of hexadecimal digits)" });
}

// String relay-agent-info entry for an empty option is dropped
// by all not none sanity check levels (this should not happen).
TEST_F(ExtendedInfoChecksTest, emptyStringRAI) {
    string description = "string RAI with empty content, fix";
    check4(description, "{ \"ISC\": { \"relay-agent-info\": \"0x\" } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in rai a problem was found:"
             " '0x' is not a valid string of hexadecimal digits)" });
}

// Valid string relay-agent-info entry is upgraded by all not none
// sanity check levels.
TEST_F(ExtendedInfoChecksTest, upgradedRAI) {
    string description = "valid string RAI, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": \"0x0104AABBCCDD\" } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
           " \"0x0104AABBCCDD\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_UPGRADED"
             " extended info for lease 192.168.1.1 was upgraded" });
}

// Upgraded string relay-agent-info entry with ids.
TEST_F(ExtendedInfoChecksTest, upgradedRAIwithIds) {
    string description = "valid string RAI with ids, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": \"0x02030102030C03AABBCC\" } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
           " \"0x02030102030C03AABBCC\", \"remote-id\": \"010203\","
           " \"relay-id\": \"AABBCC\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_UPGRADED"
             " extended info for lease 192.168.1.1 was upgraded" });
}

// sub-options entry with a bad type is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, badTypeSubOptionsfix) {
    string description = "sub-options not a string, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\": 1 } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\": 1 } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// sub-options entry with a bad type is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badTypeSubOptionsstrict) {
    string description = "sub-options not a string, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\": 1 } } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in sub-options a problem was found:"
             " sub-options is not a string)" });
}

// sub-options entry which can't be decoded is right up to the fix
// sanity level.
TEST_F(ExtendedInfoChecksTest, badEncodingSubOptionsfix) {
    string description = "sub-options with a junk value, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
           " \"foo\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
           " \"foo\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// sub-options entry which can't be decoded is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badEncodingSubOptionsstrict) {
    string description = "sub-options with a junk value, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
           " \"foo\" } } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in sub-options a problem was found:"
             " 'foo' is not a valid string of hexadecimal digits)" });
}

// remote-id entry with a bad type is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, badTypeRemoteId4fix) {
    string description = "remote-id not a string, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\": 1 } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\": 1 } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// remote-id entry with a bad type is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badTypeRemoteId4strict) {
    string description = "remote-id not a string, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\": 1 } } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in remote-id a problem was found:"
             " remote-id is not a string)" });
}

// remote-id entry which can't be decoded is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, badEncodingRemoteId4fix) {
    string description = "remote-id with a junk value, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\":"
           " \"foo\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\":"
           " \"foo\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// remote-id entry which can't be decoded is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badEncodingRemoteId4strict) {
    string description = "remote-id with a junk value, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\":"
           " \"foo\" } } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in remote-id a problem was found:"
             " attempt to decode a value not in base16 char set)" });
}

// Empty remote-id entry is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, emptyRemoteId4fix) {
    string description = "empty remote-id, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\": \"\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\": \"\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// Empty remote-id entry is dropped at strict or higher sanity levels.
TEST_F(ExtendedInfoChecksTest, emptyRemoteId4strict) {
    string description = "empty remote-id, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\": \"\" } } }",
           "", CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in remote-id a problem was found:"
             " remote-id is empty)" });
}

// Valid remote-id entry is right for all sanity levels.
TEST_F(ExtendedInfoChecksTest, validRemoteId4strict) {
    string description = "valid remote-id, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\":"
           " \"AABB\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"remote-id\":"
           " \"AABB\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT);
}

// relay-id entry with a bad type is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, badTypeRelayId4fix) {
    string description = "relay-id not a string, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\": 1 } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\": 1 } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// relay-id entry with a bad type is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badTypeRelayId4strict) {
    string description = "relay-id not a string, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\": 1 } } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in relay-id a problem was found:"
             " relay-id is not a string)" });
}

// relay-id entry which can't be decoded is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, badEncodingRelayId4fix) {
    string description = "relay-id with a junk value, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\":"
           " \"foo\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\":"
           " \"foo\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// relay-id entry which can't be decoded is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badEncodingRelayId4strict) {
    string description = "relay-id with a junk value, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\":"
           " \"foo\" } } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in relay-id a problem was found:"
             " attempt to decode a value not in base16 char set)" });
}

// Empty relay-id entry is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, emptyRelayId4fix) {
    string description = "empty relay-id, fix";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\": \"\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\": \"\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// Empty relay-id entry is dropped at strict or higher sanity levels.
TEST_F(ExtendedInfoChecksTest, emptyRelayId4strict) {
    string description = "empty relay-id, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\": \"\" } } }",
           "", CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in relay-id a problem was found:"
             " relay-id is empty)" });
}

// Valid relay-id entry is right for all sanity levels.
TEST_F(ExtendedInfoChecksTest, validRelayId4strict) {
    string description = "valid relay-id, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\":"
           " \"AABB\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"relay-id\":"
           " \"AABB\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT);
}

// Junk entries are right up to the strict sanity level.
TEST_F(ExtendedInfoChecksTest, junk4strict) {
    string description = "junk entry, strict";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"foo\": 1 } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"foo\": 1 } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT);
}

// Junk entries are dropped at the pedantic level.
TEST_F(ExtendedInfoChecksTest, junk4pedantic) {
    string description = "junk entry, pedantic";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"foo\": 1 } } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 192.168.1.1 failed checks"
             " (in relay-agent-info a problem was found:"
             " spurious 'foo' entry in relay-agent-info)" });
}

// comment is not considered as a junk entry.
TEST_F(ExtendedInfoChecksTest, comment4) {
    string description = "comment entry, pedantic";
    check4(description,
           "{ \"ISC\": { \"relay-agent-info\": { \"comment\": \"good\" } } }",
           "{ \"ISC\": { \"relay-agent-info\": { \"comment\": \"good\" } } }",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
}

// No user context is right for any sanity check level including the highest.
TEST_F(ExtendedInfoChecksTest, noUserContext6) {
    string description = "no user context, pedantic";
    check6(description, "", "", CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
}

// User context with a bad type is right only when no check is done.
TEST_F(ExtendedInfoChecksTest, badTypeUserContext6none) {
    string description = "user context not a map, none";
    check6(description, "1", "1", CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// User context with a bad type is refused by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeUserContext6) {
    string description = "user context not a map, fix";
    check6(description, "1", "", CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in user context a problem was found:"
             " user context is not a map)" });
}

// Empty user context is right only when no check is done.
TEST_F(ExtendedInfoChecksTest, emptyTypeUserContext6none) {
    string description = "empty user context, none";
    check6(description, "{ }", "{ }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// Empty user context is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, emptyTypeUserContext6) {
    string description = "empty user context, fix";
    check6(description, "{ }", "", CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// No ISC entry is right in all cases.
TEST_F(ExtendedInfoChecksTest, noISC6) {
    string description = "no ISC entry, pedantic";
    check6(description, "{ \"foo\": 1 }", "{ \"foo\": 1 }",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
}

// ISC entry with a bad type is right only when no check is done.
TEST_F(ExtendedInfoChecksTest, badTypeISC6none) {
    string description = "ISC entry no a map, none";
    check6(description, "{ \"ISC\": 1 }", "{ \"ISC\": 1 }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// ISC entry with a bad type is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeISC6) {
    string description = "ISC entry no a map, fix";
    check6(description, "{ \"ISC\": 1 }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in isc a problem was found:"
             " ISC entry is not a map)" });
}

// When the ISC entry is dropped other entries are kept.
TEST_F(ExtendedInfoChecksTest, badTypeISC6other) {
    string description = "ISC entry no a map with others, fix";
    check6(description, "{ \"ISC\": 1, \"foo\": 2 }", "{ \"foo\": 2 }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in isc a problem was found:"
             " ISC entry is not a map)" });
}

// Empty ISC entry is kept only when no check is done.
TEST_F(ExtendedInfoChecksTest, emptyISC6none) {
    string description = "empty ISC entry, none";
    check6(description, "{ \"ISC\": { } }", "{ \"ISC\": { } }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// Empty ISC entry is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, emptyISC6) {
    string description = "empty ISC entry, fix";
    check6(description, "{ \"ISC\": { } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// relays is not upgraded when no check is done.
TEST_F(ExtendedInfoChecksTest, relaysnone) {
    string description = "relays, none";
    check6(description, "{ \"ISC\": { \"relays\": true } }",
           "{ \"ISC\": { \"relays\": true } }",
           CfgConsistency::EXTENDED_INFO_CHECK_NONE);
}

// relays is dropped when relay-info is present by all not none sanity
// check levels.
TEST_F(ExtendedInfoChecksTest, relaysAndRelayInfo) {
    string description = "relays and relay-info, fix";
    check6(description,
           "{ \"ISC\": { \"relays\": true, \"relay-info\":"
           " [ { \"foo\": 1 } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"foo\": 1 } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// relays with bad type is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeRelays) {
    string description = "relays is not a list, fix";
    check6(description, "{ \"ISC\": { \"relays\": true } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relays a problem was found:"
             " relays is not a list)" });
}

// Empty relays is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, emptyRelays) {
    string description = "empty relays, fix";
    check6(description, "{ \"ISC\": { \"relays\": [ ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relays a problem was found:"
             " relays is empty)" });
}

// Relay (element of relays) with bad type is dropped by all not none
// sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeRelay) {
    string description = "relay is not a map, fix";
    check6(description, "{ \"ISC\": { \"relays\": [ 1 ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay [relay#0] a problem was found:"
             " relay#0 is not a map)" });
}

// options with bad type is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeOptions) {
    string description = "options is not a string, fix";
    check6(description, "{ \"ISC\": { \"relays\": [ { \"options\": 1 } ] } }",
           "", CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in options [relay#0] a problem was found:"
             " options is not a string)" });
}

// options which can't be decoded is dropped by all not none sanity
// check levels.
TEST_F(ExtendedInfoChecksTest, badEncodingOptions) {
    string description = "options with junk value, fix";
    check6(description,
           "{ \"ISC\": { \"relays\": [ { \"options\": \"foo\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in options [relay#0] a problem was found:"
             " 'foo' is not a valid string of hexadecimal digits)" });
}

// Valid relays is upgraded by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, upgradedRelays) {
    string description = "upgraded relays, fix";
    check6(description,
           "{ \"ISC\": { \"relays\": [ { \"hop\": 33,"
           " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
           " \"options\": \"0x00C800080102030405060708\" } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
           " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
           " \"options\": \"0x00C800080102030405060708\" } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_UPGRADED"
             " extended info for lease 2001::1 was upgraded" });
}

// Valid relays with ids is upgraded by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, upgradedRelaysWithIds) {
    string description = "upgraded relays with ids, fix";
    check6(description,
           "{ \"ISC\": { \"relays\": [ { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\" } ] } }",
            "{ \"ISC\": { \"relay-info\": [ { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\","
            " \"remote-id\": \"010203040506\","
           " \"relay-id\": \"6464646464646464\" } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_UPGRADED"
             " extended info for lease 2001::1 was upgraded" });
}

// Valid relays with 2 relays is upgraded by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, upgradedRelays2) {
    string description = "upgraded relays with 2 relays, fix";
    check6(description,
           "{ \"ISC\": { \"relays\": [ { \"hop\": 33,"
            " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
            " \"options\": \"0x00C800080102030405060708\" }, { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\" } ] } }",
            "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
            " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
            " \"options\": \"0x00C800080102030405060708\" }, { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\","
            " \"remote-id\": \"010203040506\","
           " \"relay-id\": \"6464646464646464\" } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_UPGRADED"
             " extended info for lease 2001::1 was upgraded" });
}

// relayinfo with bad type is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeRelayInfo) {
    string description = "relayinfo is not a list, fix";
    check6(description, "{ \"ISC\": { \"relay-info\": true } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay-info a problem was found:"
             " relay-info is not a list)" });
}

// Empty relay-info is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, emptyRelayInfo) {
    string description = "empty relay-info, fix";
    check6(description, "{ \"ISC\": { \"relay-info\": [ ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay-info a problem was found:"
             " relay-info is empty)" });
}

// Relay (element of relay-info) with bad type is dropped by all not none
// sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeRelay2) {
    string description = "relay is not a map, fix";
    check6(description, "{ \"ISC\": { \"relay-info\": [ 1 ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay [relay#0] a problem was found:"
             " relay#0 is not a map)" });
}

// options with bad type is dropped by all not none sanity check levels.
TEST_F(ExtendedInfoChecksTest, badTypeOptions2) {
    string description = "options is not a string, fix";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"options\": 1 } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in options [relay#0] a problem was found:"
             " options is not a string)" });
}

// options which can't be decoded is dropped by all not none sanity
// check levels.
TEST_F(ExtendedInfoChecksTest, badEncodingOptions2) {
    string description = "options with junk value, fix";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"options\": \"foo\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in options [relay#0] a problem was found:"
             " 'foo' is not a valid string of hexadecimal digits)" });
}

// Relay without a link entry is right up to fix sanity check level.
TEST_F(ExtendedInfoChecksTest, noLinkfix) {
    string description = "no link, fix";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"foo\": 1  } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"foo\": 1  } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// Relay without a link entry is dropped by strict sanity check level and
// higher.
TEST_F(ExtendedInfoChecksTest, noLinkstrict) {
    string description = "no link, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"foo\": 1  } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in link [relay#0] a problem was found:"
             " no link)" });
}

// link entry with bad type is dropped by strict sanity check level and higher.
TEST_F(ExtendedInfoChecksTest, badTypeLink) {
    string description = "link is not a string, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": 1 } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in link [relay#0] a problem was found:"
             " link is not a string)" });
}

// link entry which is not an address is dropped by strict sanity check level
// and higher.
TEST_F(ExtendedInfoChecksTest, notAddressLink) {
    string description = "link is not an address, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"foo\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in link [relay#0] a problem was found:"
             " Failed to convert string to address 'foo':"
             " Invalid argument)" });
}

// link entry which is an IPv4 (vs IPv6) address is dropped by strict sanity
// check level and higher.
TEST_F(ExtendedInfoChecksTest, notV6Link) {
    string description = "link is v4, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\":"
           " \"192.128.1.1\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in link [relay#0] a problem was found:"
             " link is not an IPv6 address)" });
}

// Valid link entry is right for all sanity levels.
TEST_F(ExtendedInfoChecksTest, validLink) {
    string description = "valid link, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\" } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\" } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT);
}

// remote-id entry with a bad type is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, badTypeRemoteId6fix) {
    string description = "remote-id not a string, fix";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"remote-id\": 1 } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"remote-id\": 1 } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// remote-id entry with a bad type is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badTypeRemoteId6strict) {
    string description = "remote-id not a string, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"remote-id\": 1,"
           " \"link\": \"2001::2\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in remote-id [relay#0] a problem was found:"
             " remote-id is not a string)" });
}

// remote-id entry which can't be decoded is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badEncodingRemoteId6strict) {
    string description = "remote-id with a junk value, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"remote-id\": \"foo\","
           " \"link\": \"2001::2\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in remote-id [relay#0] a problem was found:"
             " attempt to decode a value not in base16 char set)" });
}

// Empty remote-id entry is dropped at strict or higher sanity levels.
TEST_F(ExtendedInfoChecksTest, emptyRemoteId6strict) {
    string description = "empty remote-id, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"remote-id\": \"\","
           " \"link\": \"2001::2\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in remote-id [relay#0] a problem was found:"
             " remote-id is empty)" });
}

// Valid remote-id entry is right at all sanity levels.
TEST_F(ExtendedInfoChecksTest, validRemoteId6strict) {
    string description = "valid remote-id, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"remote-id\": \"AABB\","
           " \"link\": \"2001::2\" } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"remote-id\": \"AABB\","
           " \"link\": \"2001::2\" } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT);
}

// relay-id entry with a bad type is right up to the fix sanity level.
TEST_F(ExtendedInfoChecksTest, badTypeRelayId6fix) {
    string description = "relay-id not a string, fix";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"relay-id\": 1 } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"relay-id\": 1 } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_FIX);
}

// relay-id entry with a bad type is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badTypeRelayId6strict) {
    string description = "relay-id not a string, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"relay-id\": 1,"
           " \"link\": \"2001::2\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay-id [relay#0] a problem was found:"
             " relay-id is not a string)" });
}

// relay-id entry which can't be decoded is dropped at strict or higher
// sanity levels.
TEST_F(ExtendedInfoChecksTest, badEncodingRelayId6strict) {
    string description = "relay-id with a junk value, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"relay-id\": \"foo\","
           " \"link\": \"2001::2\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay-id [relay#0] a problem was found:"
             " attempt to decode a value not in base16 char set)" });
}

// Empty relay-id entry is dropped at strict or higher sanity levels.
TEST_F(ExtendedInfoChecksTest, emptyRelayId6strict) {
    string description = "empty relay-id, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"relay-id\": \"\","
           " \"link\": \"2001::2\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay-id [relay#0] a problem was found:"
             " relay-id is empty)" });
}

// Valid relay-id entry is right at all sanity levels.
TEST_F(ExtendedInfoChecksTest, validRelayId6strict) {
    string description = "valid relay-id, strict";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"relay-id\": \"AABB\","
           " \"link\": \"2001::2\" } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"relay-id\": \"AABB\","
           " \"link\": \"2001::2\" } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_STRICT);
}

// Pedantic requires a peer entry.
TEST_F(ExtendedInfoChecksTest, noPeerpedantic) {
    string description = "no peer, pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\" } ] } }",
           "", CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in peer [relay#0] a problem was found:"
             " no peer)" });
}

// peer entry with bad type is dropped by pedantic sanity check level.
TEST_F(ExtendedInfoChecksTest, badTypePeer) {
    string description = "peer is not a string, pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": 1 } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in peer [relay#0] a problem was found:"
             " peer is not a string)" });
}

// peer entry which is not an address is dropped by pedantic sanity check level.
TEST_F(ExtendedInfoChecksTest, notAddressPeer) {
    string description = "peer is not an address, pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": \"foo\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in peer [relay#0] a problem was found:"
             " Failed to convert string to address 'foo':"
             " Invalid argument)" });
}

// peer entry which is an IPv4 (vs IPv6) address is dropped by pedantic sanity
// check level.
TEST_F(ExtendedInfoChecksTest, notV6Peer) {
    string description = "peer is v4, pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": \"192.128.1.1\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in peer [relay#0] a problem was found:"
             " peer is not an IPv6 address)" });
}

// Pedantic requires a hop entry.
TEST_F(ExtendedInfoChecksTest, noHop) {
    string description = "no hop, pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": \"2001::3\" } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in hop [relay#0] a problem was found:"
             " no hop)" });
}

// hop entry with bad type is dropped by pedantic sanity check level.
TEST_F(ExtendedInfoChecksTest, badTypeHop) {
    string description = "hop is not an integer pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": \"2001::3\", \"hop\": false } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in hop [relay#0] a problem was found:"
             " hop is not an integer)" });
}

// Valid relay.
TEST_F(ExtendedInfoChecksTest, valid6Pedantic) {
    string description = "valid, pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": \"2001::3\", \"hop\": 10 } ] } }",
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": \"2001::3\", \"hop\": 10 } ] } }",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC);
}

// Junk entries are dropped at the pedantic level.
TEST_F(ExtendedInfoChecksTest, junk6pedantic) {
    string description = "junk entry, pedantic";
    check6(description,
           "{ \"ISC\": { \"relay-info\": [ { \"link\": \"2001::2\","
           " \"peer\": \"2001::3\", \"hop\": 10, \"foo\": 1 } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relay-info [relay#0] a problem was found:"
             " spurious 'foo' entry)" });
}

// Same with relays post upgrade checks.
TEST_F(ExtendedInfoChecksTest, junkRelayspedantic) {
    string description = "junk entry, pedantic";
    check6(description,
           "{ \"ISC\": { \"relays\": [ { \"link\": \"2001::2\","
           " \"peer\": \"2001::3\", \"hop\": 10, \"foo\": 1 } ] } }", "",
           CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
           { "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL"
             " extended info for lease 2001::1 failed checks"
             " (in relays [relay#0] a problem was found:"
             " spurious 'foo' entry)" });
}
