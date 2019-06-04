// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
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

