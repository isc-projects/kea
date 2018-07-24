// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/tests/test_utils.h>
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

        time_t timestamp = time(NULL) - 86400 + random()%86400;

        // Return created lease.
        return (Lease4Ptr(new Lease4(address, hwaddr,
                                     &clientid[0], 0, // no client-id
                                     1200, 600, 900, // valid, t1, t2
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
        uint32_t valid_lft = 1200;
        uint32_t preferred_lft = 1000;
        uint32_t t1 = 600;
        uint32_t t2 = 900;

        std::ostringstream hostname;
        hostname << "hostname" << (random() % 2048);

        // Return created lease.
        Lease6Ptr lease(new Lease6(lease_type, address, duid, iaid,
                                   1000, 1200, 600, 900, // pref, valid, t1, t2
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

    void
    parserCheck(SrvConfig& cfg, const string& txt, bool exp_throw,
                CfgConsistency::LeaseSanity exp_sanity) {

        SanityChecksParser parser;

        ElementPtr json;
        EXPECT_NO_THROW(json = Element::fromJSON(txt));

        if (exp_throw) {
            EXPECT_THROW(parser.parse(cfg, json), DhcpConfigError);

            return;
        }

        // Should not throw.
        EXPECT_NO_THROW(parser.parse(cfg, json));

        EXPECT_EQ(cfg.getConsistency()->getLeaseSanityCheck(), exp_sanity);
    }

    /// @brief Creates subnet configuration, inserts a lease and checks the result.
    ///
    /// This is a bit complicated test. It creates a Subnet configuration first
    /// (defined by subnet/subnet_id), adds it to the current configuration,
    /// then sets the lease checks to specified value, then creates a lease
    /// (addr/lease_id) and tries to add it to the lease backend (memfile is used).
    /// Afterwards it checks whether the lease is added or not (exp_lease_present)
    /// and if it is present, whether it has expected subnet-id (expected_id).
    ///
    /// @param addr Address of the lease to be created
    /// @param lease_id Subnet-id of the lease to be created
    /// @param subnet_txt Text representation of the subnet, e.g. 192.0.2.0/24
    /// @param subnet_id Subnet-id of the subnet to be created
    /// @param sanity Sanity checks set in the configuration
    /// @param exp_lease_present whether the lease is expected to be inserted
    /// @param expected_id if exp_lease_present is true, lease's subnet id should
    ///                    match this value.
    /// @return lease from the backend (may return null)
    void
    leaseAddCheck4(string addr, SubnetID lease_id, string subnet_txt, SubnetID subnet_id,
                  CfgConsistency::LeaseSanity sanity, bool exp_lease_present,
                  SubnetID expected_id) {

        // Let's start a backend in proper universe.
        IOAddress a(addr);
        startLeaseBackend(a.isV6());

        // Now set the sanity checks to a proper value.
        ASSERT_NO_THROW(CfgMgr::instance().getCurrentCfg()->getConsistency()
                        ->setLeaseSanityCheck(sanity));

        // Create the subnet and add it to configuration.
        Subnet4Ptr subnet = createSubnet4(subnet_txt, subnet_id);
        ASSERT_NO_THROW(CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet));

        // Now try to insert the lease.
        Lease4Ptr l = newLease4(addr, lease_id);
        bool result = false;
        EXPECT_NO_THROW(result = LeaseMgrFactory::instance().addLease(l));
        EXPECT_EQ(result, exp_lease_present);

        Lease4Ptr from_backend;
        if (result && exp_lease_present) {

            ASSERT_TRUE(from_backend = LeaseMgrFactory::instance().getLease4(IOAddress(addr)));

            EXPECT_EQ(l->addr_, from_backend->addr_);
            EXPECT_EQ(from_backend->subnet_id_, expected_id);
        }
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

    SrvConfig cfg;

    // The default should be to warn about inconsistency.
    EXPECT_EQ(cfg.getConsistency()->getLeaseSanityCheck(),
              CfgConsistency::LEASE_CHECK_WARN);

    parserCheck(cfg, valid1, false, CfgConsistency::LEASE_CHECK_NONE);
    parserCheck(cfg, valid2, false, CfgConsistency::LEASE_CHECK_WARN);
    parserCheck(cfg, valid3, false, CfgConsistency::LEASE_CHECK_FIX);
    parserCheck(cfg, valid4, false, CfgConsistency::LEASE_CHECK_FIX_DEL);
    parserCheck(cfg, valid5, false, CfgConsistency::LEASE_CHECK_DEL);

    parserCheck(cfg, bogus1, true, CfgConsistency::LEASE_CHECK_NONE);
    parserCheck(cfg, bogus2, true, CfgConsistency::LEASE_CHECK_NONE);
    parserCheck(cfg, bogus3, true, CfgConsistency::LEASE_CHECK_NONE);
    parserCheck(cfg, bogus4, true, CfgConsistency::LEASE_CHECK_NONE);
}

// This test checks how the code behaves when there is no subnet matching
// the lease added.
TEST_F(SanityChecksTest, memfileAdd4NoSubnet) {

    startLeaseBackend(false); // false = V4

    string addr("192.0.2.1");
    SubnetID lease_id = 1;
    SubnetID subnet_id = 1;

    Lease4Ptr l = newLease4(addr, lease_id);

    EXPECT_TRUE(LeaseMgrFactory::instance().addLease(l));

    Lease4Ptr from_backend;
    ASSERT_TRUE(from_backend = LeaseMgrFactory::instance().getLease4(IOAddress(addr)));

    // The lease should be returned exactly as is.
    detailCompareLease(l, from_backend);

    LeaseMgrFactory::instance().deleteLease(IOAddress(addr));
}

TEST_F(SanityChecksTest, memfileAdd4_checksNone) {
    leaseAddCheck4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_NONE, true, 1);
}

TEST_F(SanityChecksTest, memfileAdd4_checksWarn) {
    leaseAddCheck4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_WARN, true, 1);
}

TEST_F(SanityChecksTest, memfileAdd4_checksFix) {
    leaseAddCheck4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_FIX, true, 2);
}

TEST_F(SanityChecksTest, memfileAdd4_checksFixdel1) {
    leaseAddCheck4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_FIX_DEL, true, 1);
}

TEST_F(SanityChecksTest, memfileAdd4_checksFixdel2) {
    leaseAddCheck4("192.0.2.1", 1, "192.0.3.0/24", 2, CfgConsistency::LEASE_CHECK_FIX_DEL, false, 0);
}

TEST_F(SanityChecksTest, memfileAdd4_checksDel) {
    leaseAddCheck4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_DEL, false, 0);
}
