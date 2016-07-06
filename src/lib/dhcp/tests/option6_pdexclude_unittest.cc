// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Author: Andrei Pavel <andrei.pavel@qualitance.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option6_pdexclude.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/pool.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace asiolink;

namespace {

const IOAddress empty("::");
const IOAddress beef("2001:db8:dead:beef::"); // /48 prefix length
const IOAddress cafe("2001:db8:dead:cafe::"); // /48 prefix length
const IOAddress beef01("2001:db8:dead:beef::01"); // /56 prefix length

// Description
TEST(Option6PDExcludeTest, testName) {
    Option6PDExclude option = Option6PDExclude(beef, 56, beef01, 60);

    OptionBuffer data(option.getData());

    util::OutputBuffer buf(128);
    option.pack(buf);

    Option6PDExclude unpackedOption(empty, 0, empty, 0);

    unpackedOption.unpack(data.begin(), data.end());

    EXPECT_EQ(option.getDelegatedAddress(),
            unpackedOption.getDelegatedAddress());
    EXPECT_EQ(option.getDelegatedPrefixLength(),
            unpackedOption.getDelegatedPrefixLength());
    EXPECT_EQ(option.getExcludedAddress(), unpackedOption.getExcludedAddress());
    EXPECT_EQ(option.getExcludedPrefixLength(),
            unpackedOption.getExcludedPrefixLength());
}

TEST(Option6PDExcludeTest, pool) {
    //Pool6Ptr pool6Ptr = Pool6Ptr(new Pool6(Lease::TYPE_PD, beef, cafe));
    //ASSERT_TRUE(pool6Ptr);
    //ASSERT_GT(pool6Ptr->getPrefixExcludedLength(), 0);
    /*
     OptionPtr opt(
     new Option6PDExclude((*l)->addr_, (*l)->prefixlen_,
     pool->getPrefixExcluded(),
     pool->getPrefixExcludedLength()));
     */
}

} // anonymous namespace
