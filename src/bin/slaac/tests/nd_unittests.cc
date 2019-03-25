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
#include <slaac/nd_option_univ_ra.h>
#include <slaac/nd_pkt.h>
#include <slaac/nd_pkt_rs.h>
#include <slaac/nd_pkt_ra.h>
#include <slaac/json.hpp>

#include <gtest/gtest.h>

using namespace boost::posix_time;
using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::slaac;
using namespace isc::util;

using json = nlohmann::json;

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
    OptionPrefInfoPtr pi(new OptionPrefInfo());
    ASSERT_TRUE(pi);

    // Check Prefix Info Defaults.
    EXPECT_EQ(128, pi->getPrefixLength());
    EXPECT_FALSE(pi->getOnLinkFlag());
    EXPECT_FALSE(pi->getAddrConfigFlag());
    EXPECT_EQ(0, pi->getValidLifetime());
    EXPECT_EQ(0, pi->getPreferredLifetime());
    EXPECT_EQ("::", pi->getPrefix().toText());

    // Fill Prefix Info.
    pi->setPrefixLength(64);
    pi->setOnLinkFlag(true);
    pi->setAddrConfigFlag(true);
    pi->setValidLifetime(86400); // one day
    pi->setPreferredLifetime(21600); // 6 hours
    pi->setPrefix(IOAddress("2001:db8::")); // 2001:db8::/64

    // Add Prefix Info to RA.
    ra->addOption(pi);
    EXPECT_EQ(1, ra->getOptions().size());
    EXPECT_TRUE(ra->getOption(ND_PREFIX_INFO));

    // Check RA (textual).
    string expected_txt = "RA (type=134, code=0)";
    expected_txt += " localAddr=2001:db8::1";
    expected_txt += ", remoteAddr=2001:db8::2";
    expected_txt += " on eth(1)\n";
    expected_txt += "hop_limit=64 flags=MO router_lifetime=3600\n";
    expected_txt += "reachable_time=300000 retrans_timer=100\n";
    expected_txt += "options:\n";
    expected_txt += " type=3(PrefInfo), len=4:";
    expected_txt += " flags=LA";
    expected_txt += ", prefix-2001:db8::/64\n";
    expected_txt += " valid-lifetime=86400";
    expected_txt += ", preferred-lifetime=21600\n";
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
        0, 0, 0, 100, // retrans timer (100)

        3, // type 3 Prefix Info
        4, // length
        64, // prefix length
        0xc0, // flags
        0x00, 0x01, 0x51, 0x80, // valid lifetime (86400)
        0x00, 0x00, 0x54, 0x60, // preferred lifetime (21600)
        0, 0, 0, 0, // reserved2
        0x20, 0x01, 0x0d, 0xb8, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0 // prefix 2001:db8::
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

    EXPECT_EQ(1, ra->getOptions().size());
    OptionPtr opt = ra->getOption(ND_PREFIX_INFO);
    ASSERT_TRUE(opt);
    string expected_opt = "0x030440C0000151800000546000000000";
    expected_opt += "20010DB8000000000000000000000000";
    EXPECT_EQ(expected_opt, opt->toHexString(true));
    EXPECT_EQ(expected_opt, pi->toHexString(true));
}

// Test Router Advertisement with an universal RA option.
TEST(SlaacNd, universalRA) {
    // Get a RA.
    const IOAddress& local = IOAddress("2001:db8::1");
    const IOAddress& remote = IOAddress("2001:db8::2");
    RAPktPtr ra(new RAPkt(local, remote));

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

    // Create an universal RA option.

    // Get CBOR content.
    string sample = "{\n"
        "    \"ietf\": {\n"
        "        \"dns\": {\n"
        "            \"dnssl\": [\n"
        "                \"example.com\"\n"
        "            ],\n"
        "            \"rdnss\": [\n"
        "                \"2001:db8::1\",\n"
        "                \"2001:db8::2\"\n"
        "            ],\n"
        "            \"nat64\": {\n"
        "                \"prefix\": \"64:ff9b::/96\"\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "}\n";
    json ura_json;
    ASSERT_NO_THROW(ura_json  = json::parse(sample));
    vector<uint8_t> cbor;
    ASSERT_NO_THROW(cbor = json::to_cbor(ura_json));

    // Pad to 6 modulo 8.
    size_t round = ((cbor.size() + 1) | 7) - 1;
    if (round > cbor.size()) {
        cbor.resize(round, 0);
    }
    OptionUnivRaPtr ura(new OptionUnivRa(cbor));
    ASSERT_TRUE(ura);

    // Add universal RA option to RA.
    ra->addOption(ura);
    EXPECT_EQ(1, ra->getOptions().size());
    EXPECT_TRUE(ra->getOption(ND_UNIVERSAL_RA));

    // Check RA (binary).
    uint8_t ra_data[] = {
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
    ASSERT_LT(sizeof(ra_data), output.getLength());
    EXPECT_EQ(0, memcmp(ra_data, output.getData(), sizeof(ra_data)));

    // Check Option.
    uint8_t opt_type = output[RAPkt::RA_MIN_LEN];
    ASSERT_EQ(ND_UNIVERSAL_RA, opt_type);
    size_t opt_len = output[RAPkt::RA_MIN_LEN + 1] << 3;
    ASSERT_EQ(RAPkt::RA_MIN_LEN + opt_len, output.getLength());
    vector<uint8_t> content;
    for (size_t i = RAPkt::RA_MIN_LEN + Option::OPTION_HDR_LEN;
         i < output.getLength(); ++i) {
        content.push_back(output[i]);
    }
    OptionPtr opt;
    EXPECT_NO_THROW(opt.reset(new Option(opt_type, content.begin(), content.end())));
    ASSERT_TRUE(opt);
    // Debug
    // cout << opt->toHexString(true) << endl;
    json opt_json;
    // Disable EOF checking aka strict mode (second argument, default true).
    ASSERT_NO_THROW(opt_json = json::from_cbor(opt->getData(), false));
    EXPECT_EQ(ura_json, opt_json);
}

}
