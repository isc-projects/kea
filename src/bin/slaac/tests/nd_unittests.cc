// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <slaac/nd.h>
#include <slaac/nd_option.h>
#include <slaac/nd_option_lladdr.h>
#include <slaac/nd_option_pref_info.h>
#include <slaac/nd_option_mtu.h>
#include <slaac/nd_pkt.h>
#include <slaac/nd_pkt_rs.h>
#include <slaac/nd_pkt_ra.h>

#include <gtest/gtest.h>

using namespace boost::posix_time;
using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::slaac;
using namespace isc::util;

namespace {

/// @brief SlaacNd test fixture class.
class SlaacNdTest : public ::testing::Test  {
public:
    /// @brief Constructor
    SlaacNdTest() {
    }

    /// @brief Destructor
    virtual ~SlaacNdTest() {
    }
};

// Test valid empty Router Solicitation.
TEST(SlaacNd, emptyRS) {
    // Empty RS content.
    uint8_t data[] = {
        133, // type 133 RS
        0, // code 0
        0, 0, // checksum
        0, 0, 0, 0 // reserved
    };

    const IOAddress& local = IOAddress("2001:db8::1");
    const IOAddress& remote = IOAddress("2001:db8::2");
    RSPktPtr rs;
    EXPECT_NO_THROW(rs.reset(new RSPkt(data, sizeof(data), local, remote)));
    ASSERT_TRUE(rs);

    // Check RS.
    EXPECT_NO_THROW(rs->unpack());
    EXPECT_EQ(ND_RT_SOL, rs->getType());
    EXPECT_EQ(0, rs->getCode());
    EXPECT_EQ(sizeof(data), rs->len());
    EXPECT_EQ("RS", rs->getName());
    EXPECT_EQ("", rs->getIface());
    EXPECT_EQ(-1, rs->getIndex());
    EXPECT_TRUE(rs->getOptions().empty());

    // Check text display.
    rs->setIface("eth");
    rs->setIndex(1);
    string expected = "RS (type=133, code=0)";
    expected += " localAddr=2001:db8::1";
    expected += ", remoteAddr=2001:db8::2";
    expected += " on eth(1)\n";
    EXPECT_EQ(expected, rs->toText());

    // Check packing.
    EXPECT_NO_THROW(rs->pack());
    const OutputBuffer& output = rs->getBuffer();
    ASSERT_EQ(sizeof(data), output.getLength());
    EXPECT_EQ(0, memcmp(data, output.getData(), sizeof(data)));
}

// Test valid common Router Solicitation.
TEST(SlaacNd, commonRS) {
    // Common RS content.
    uint8_t data[] = {
        133, // type 133 ND_RT_SOL
        0, // code 0
        0, 0, // checksum
        0, 0, 0, 0, // reserved

        1, // type 1 ND_SRC_LL_ADD
        1, // length (8 bytes)
        0, 1, 2, 3, 4, 5 // MAC address 00:01:02:03:04:05
    };

    const IOAddress& local = IOAddress("2001:db8::1");
    const IOAddress& remote = IOAddress("2001:db8::2");
    RSPktPtr rs;
    EXPECT_NO_THROW(rs.reset(new RSPkt(data, sizeof(data), local, remote)));
    ASSERT_TRUE(rs);

    // Check RS.
    EXPECT_NO_THROW(rs->unpack());
    EXPECT_EQ(ND_RT_SOL, rs->getType());
    EXPECT_EQ(0, rs->getCode());
    EXPECT_EQ(sizeof(data), rs->len());
    EXPECT_EQ("RS", rs->getName());
    EXPECT_EQ("", rs->getIface());
    EXPECT_EQ(-1, rs->getIndex());
    EXPECT_EQ(1, rs->getOptions().size());

    // Check option.
    OptionPtr opt = rs->getOption(ND_SRC_LL_ADDR);
    ASSERT_TRUE(opt);
    ASSERT_EQ(ND_SRC_LL_ADDR, opt->getType());
    OptionLLAddrPtr lla = boost::dynamic_pointer_cast<OptionLLAddr>(opt);
    ASSERT_TRUE(lla);
    EXPECT_EQ(8, lla->len());

    // Check text display.
    rs->setIface("eth");
    rs->setIndex(1);
    string expected = "RS (type=133, code=0)";
    expected += " localAddr=2001:db8::1";
    expected += ", remoteAddr=2001:db8::2";
    expected += " on eth(1)\n";
    expected += "options:\n";
    expected += " type=1(SrcLLAddr), len=1: 00:01:02:03:04:05\n";
    EXPECT_EQ(expected, rs->toText());

    // Check packing.
    EXPECT_NO_THROW(rs->pack());
    const OutputBuffer& output = rs->getBuffer();
    ASSERT_EQ(sizeof(data), output.getLength());
    EXPECT_EQ(0, memcmp(data, output.getData(), sizeof(data)));
}

// Test empty Router Advertisement.
TEST(SlaacNd, emptyRA) {
    // Get a RA.
    const IOAddress& local = IOAddress("2001:db8::1");
    const IOAddress& remote = IOAddress("2001:db8::2");
    RAPktPtr ra(new RAPkt(local, remote));
    ASSERT_TRUE(ra);

    // Check defaults.
    EXPECT_EQ(0, ra->getHopLimit());
    EXPECT_FALSE(ra->getManagedFlag());
    EXPECT_FALSE(ra->getOtherFlag());
    EXPECT_EQ(0, ra->getRouterLifetime());
    EXPECT_EQ(0, ra->getReachableTime());
    EXPECT_EQ(0, ra->getRetransTimer());

    // Fill the RA.
    ra->setIface("eth");
    ra->setIndex(1);
    ra->setHopLimit(64); // 64 hops
    ra->setManagedFlag(true);
    ra->setOtherFlag(true);
    ra->setRouterLifetime(3600); // one hour
    ra->setReachableTime(300000); // 5 mn
    ra->setRetransTimer(100); // 100 ms

    // Check it (textual).
    string expected_txt = "RA (type=134, code=0)";
    expected_txt += " localAddr=2001:db8::1";
    expected_txt += ", remoteAddr=2001:db8::2";
    expected_txt += " on eth(1)\n";
    expected_txt += "hop_limit=64 flags=MO router_lifetime=3600\n";
    expected_txt += "reachable_time=300000 retrans_timer=100\n";
    EXPECT_EQ(expected_txt, ra->toText());
    
    // Check it (binary).
    uint8_t expected_data[] = {
        134, // type 134 RA
        0, // code 0
        0, 0, // checksum
        64, // hop limit
        0xc0, // flags
        0x0e, 0x10, // router lifetime (3600)
        0x00, 0x04, 0x93, 0xe0, // reachable time (300000)
        0, 0, 0, 100 // retrans timer (100)
    };
    EXPECT_NO_THROW(ra->pack());
    const OutputBuffer& output = ra->getBuffer();
    ASSERT_EQ(sizeof(expected_data), output.getLength());
    EXPECT_EQ(0, memcmp(expected_data, output.getData(), output.getLength()));
    
    // Check unpacking.
    EXPECT_NO_THROW(ra.reset(new RAPkt(expected_data, sizeof(expected_data),
                                       local, remote)));
    ASSERT_TRUE(ra);
    EXPECT_NO_THROW(ra->unpack());
    EXPECT_EQ(64, ra->getHopLimit());
    EXPECT_TRUE(ra->getManagedFlag());
    EXPECT_TRUE(ra->getOtherFlag());
    EXPECT_EQ(3600, ra->getRouterLifetime());
    EXPECT_EQ(300000, ra->getReachableTime());
    EXPECT_EQ(100, ra->getRetransTimer());
}
    
// Test Router Advertisement with a prefix info option.
TEST(SlaacNd, prefInfoRA) {
    // Get a RA.
    const IOAddress& local = IOAddress("2001:db8::1");
    const IOAddress& remote = IOAddress("2001:db8::2");
    RAPktPtr ra(new RAPkt(local, remote));
    ASSERT_TRUE(ra);

    // Check RA defaults.
    EXPECT_EQ(0, ra->getHopLimit());
    EXPECT_FALSE(ra->getManagedFlag());
    EXPECT_FALSE(ra->getOtherFlag());
    EXPECT_EQ(0, ra->getRouterLifetime());
    EXPECT_EQ(0, ra->getReachableTime());
    EXPECT_EQ(0, ra->getRetransTimer());

    // Fill the RA.
    ra->setIface("eth");
    ra->setIndex(1);
    ra->setHopLimit(64); // 64 hops
    ra->setManagedFlag(true);
    ra->setOtherFlag(true);
    ra->setRouterLifetime(3600); // one hour
    ra->setReachableTime(300000); // 5 mn
    ra->setRetransTimer(100); // 100 ms

    // Create a Prefix Info.
    OptionPrefInfoPtr opt(new OptionPrefInfo());
    ASSERT_TRUE(opt);

    // Check Prefix Info Defaults.
    EXPECT_EQ(128, opt->getPrefixLength());
    EXPECT_FALSE(opt->getOnLinkFlag());
    EXPECT_FALSE(opt->getAddrConfigFlag());
    EXPECT_EQ(0, opt->getValidLifetime());
    EXPECT_EQ(0, opt->getPreferredLifetime());
    EXPECT_EQ("::", opt->getPrefix().toText());

    // Fill Prefix Info.
    opt->setPrefixLength(64);
    opt->setOnLinkFlag(true);
    opt->setAddrConfigFlag(true);
    opt->setValidLifetime(86400); // one day
    opt->setPreferredLifetime(21600); // 6 hours
    opt->setPrefix(IOAddress("2001:db8::")); // 2001:db8::/64

    // Check RA (textual).
    string expected_txt = "RA (type=134, code=0)";
    expected_txt += " localAddr=2001:db8::1";
    expected_txt += ", remoteAddr=2001:db8::2";
    expected_txt += " on eth(1)\n";
    expected_txt += "hop_limit=64 flags=MO router_lifetime=3600\n";
    expected_txt += "reachable_time=300000 retrans_timer=100\n";
    expected_txt += "options:";
    expected_txt += "prefix info...";
    EXPECT_EQ(expected_txt, ra->toText());
    
    // Check RA (binary).
    uint8_t expected_data[] = {
        134, // type 134 RA
        0, // code 0
        0, 0, // checksum
        64, // hop limit
        0xc0, // flags
        0x0e, 0x10, // router lifetime (3600)
        0x00, 0x04, 0x93, 0xe0, // reachable time (300000)
        0, 0, 0, 100 // retrans timer (100)
    };
    EXPECT_NO_THROW(ra->pack());
    const OutputBuffer& output = ra->getBuffer();
    ASSERT_EQ(sizeof(expected_data), output.getLength());
    EXPECT_EQ(0, memcmp(expected_data, output.getData(), output.getLength()));
    
    // Check unpacking.
    EXPECT_NO_THROW(ra.reset(new RAPkt(expected_data, sizeof(expected_data),
                                       local, remote)));
    ASSERT_TRUE(ra);
    EXPECT_NO_THROW(ra->unpack());
    EXPECT_EQ(64, ra->getHopLimit());
    EXPECT_TRUE(ra->getManagedFlag());
    EXPECT_TRUE(ra->getOtherFlag());
    EXPECT_EQ(3600, ra->getRouterLifetime());
    EXPECT_EQ(300000, ra->getReachableTime());
    EXPECT_EQ(100, ra->getRetransTimer());
}
    
}
