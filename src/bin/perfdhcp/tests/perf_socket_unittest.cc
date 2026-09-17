// Copyright (C) 2019-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <exceptions/exceptions.h>
#include <perfdhcp/perf_socket.h>
#include <perfdhcp/tests/command_options_helper.h>

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <stdint.h>

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;


/// \brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on perfdhcp PerfSocketTest class.
class PerfSocketTest : public virtual ::testing::Test
{
public:
    PerfSocketTest() { }
};


TEST_F(PerfSocketTest, WrongCommandOptions) {
    // Check if incorrect command options are casing failure during
    // socket setup.
    CommandOptions opt;

    // make sure we catch -6 paired with v4 address
    CommandOptionsHelper::process(opt, "perfdhcp -l 127.0.0.1 -6 192.168.1.1");
    EXPECT_THROW(PerfSocket sock(opt), isc::InvalidParameter);

    // make sure we catch -4 paired with v6 address
    CommandOptionsHelper::process(opt, "perfdhcp -l 127.0.0.1 -4 ff02::1:2");
    EXPECT_THROW(PerfSocket sock(opt), isc::InvalidParameter);
}
