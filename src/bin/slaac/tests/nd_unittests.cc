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
}

}
