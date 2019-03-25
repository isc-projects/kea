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

}
