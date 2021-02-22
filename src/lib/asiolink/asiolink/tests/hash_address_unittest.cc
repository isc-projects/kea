// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <gtest/gtest.h>
#include <boost/functional/hash.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>

// In fact the goal i.e. is to check if the file compiles.

using namespace isc::asiolink;

typedef boost::hash<IOAddress> hash_address;

TEST(HashAddressTest, unorderedSet) {
    std::unordered_set<IOAddress, hash_address> set;
    EXPECT_TRUE(set.empty());
    EXPECT_EQ(0, set.size());

    IOAddress addr("192.168.2.1");
    EXPECT_EQ(set.end(), set.find(addr));
    EXPECT_EQ(0, set.count(addr));

    EXPECT_NO_THROW(set.insert(addr));
    EXPECT_FALSE(set.empty());
    EXPECT_EQ(1, set.size());
    EXPECT_NE(set.end(), set.find(addr));
    EXPECT_EQ(1, set.count(addr));

    EXPECT_NO_THROW(set.clear());
    EXPECT_TRUE(set.empty());
}

TEST(HashAddressTest, unorderedMap) {
    std::unordered_map<IOAddress, std::string, hash_address> map;
    EXPECT_TRUE(map.empty());
    EXPECT_EQ(0, map.size());

    IOAddress addr("192.168.2.1");
    EXPECT_EQ(map.end(), map.find(addr));
    EXPECT_EQ(0, map.count(addr));

    std::string str("my-address");
    EXPECT_NO_THROW(map[addr] = str);
    EXPECT_FALSE(map.empty());
    EXPECT_EQ(1, map.size());
    EXPECT_NE(map.end(), map.find(addr));
    EXPECT_EQ(1, map.count(addr));

    EXPECT_NO_THROW(map.clear());
    EXPECT_TRUE(map.empty());
}
