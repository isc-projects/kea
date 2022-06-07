// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/dhcp_space.h>

#include <cstring>

#include <gtest/gtest.h>

namespace {

using namespace isc::util;

TEST(DhcpSpace, cString) {
    EXPECT_EQ(std::strcmp(cStringDhcpSpace<DHCPv4>(), "4"), 0);
    EXPECT_EQ(std::strcmp(cStringDhcpSpace<DHCPv6>(), "6"), 0);
}

TEST(DhcpSpace, format) {
    EXPECT_EQ(formatDhcpSpace<DHCPv4>("dhcp{}"), "dhcp4");
    EXPECT_EQ(formatDhcpSpace<DHCPv6>("dhcp{}"), "dhcp6");

    EXPECT_EQ(formatDhcpSpace<DHCPv4>("Dhcp{}.subnet{}"), "Dhcp4.subnet4");
    EXPECT_EQ(formatDhcpSpace<DHCPv6>("Dhcp{}.subnet{}"), "Dhcp6.subnet6");
}

}  // namespace
