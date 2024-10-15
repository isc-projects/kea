// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_error.h>
#include <dhcpsrv/packet_fuzzer.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

namespace isc {
namespace dhcp {
namespace test {

TEST(PacketFuzzerTest, constructor) {
    PacketFuzzer(67, "testeth", "127.0.0.1");
    // v6 requires valid interface. Skip positive test case.

    // Negative test cases
    EXPECT_THROW_MSG(PacketFuzzer(547, "invalid_eth%", "fe80::1"), FuzzInitFail,
                     "error retrieving interface ID for invalid_eth%: No such device");
    EXPECT_THROW_MSG(PacketFuzzer(1234, "testeth", "abcd"), isc::asiolink::IOError,
                     "Failed to convert string to address 'abcd': Invalid argument");
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
