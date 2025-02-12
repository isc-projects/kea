// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <tests/subnet_cmds_unittest.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

// Tests that command handlers are registered when the library is loaded,
// and that handlers are deregistered when the library is unloaded.
TEST_F(SubnetCmdsTest, commands) {

    ASSERT_FALSE(checkCommandRegistered("subnet4-list"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-list"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-get"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-get"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-add"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-add"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-update"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-update"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-del"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-del"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-delta-add"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-delta-add"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-delta-del"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-delta-del"));
    ASSERT_FALSE(checkCommandRegistered("network4-list"));
    ASSERT_FALSE(checkCommandRegistered("network6-list"));
    ASSERT_FALSE(checkCommandRegistered("network4-get"));
    ASSERT_FALSE(checkCommandRegistered("network6-get"));
    ASSERT_FALSE(checkCommandRegistered("network4-add"));
    ASSERT_FALSE(checkCommandRegistered("network6-add"));
    ASSERT_FALSE(checkCommandRegistered("network4-del"));
    ASSERT_FALSE(checkCommandRegistered("network6-del"));
    ASSERT_FALSE(checkCommandRegistered("network4-subnet-add"));
    ASSERT_FALSE(checkCommandRegistered("network6-subnet-add"));
    ASSERT_FALSE(checkCommandRegistered("network4-subnet-del"));
    ASSERT_FALSE(checkCommandRegistered("network6-subnet-del"));

    setFamily(AF_INET);
    loadSubnetCmds();

    ASSERT_TRUE(checkCommandRegistered("subnet4-list"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-list"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-get"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-get"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-update"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-update"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-del"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-del"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-delta-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-delta-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-delta-del"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-delta-del"));
    ASSERT_TRUE(checkCommandRegistered("network4-list"));
    ASSERT_TRUE(checkCommandRegistered("network6-list"));
    ASSERT_TRUE(checkCommandRegistered("network4-get"));
    ASSERT_TRUE(checkCommandRegistered("network6-get"));
    ASSERT_TRUE(checkCommandRegistered("network4-add"));
    ASSERT_TRUE(checkCommandRegistered("network6-add"));
    ASSERT_TRUE(checkCommandRegistered("network4-del"));
    ASSERT_TRUE(checkCommandRegistered("network6-del"));
    ASSERT_TRUE(checkCommandRegistered("network4-subnet-add"));
    ASSERT_TRUE(checkCommandRegistered("network6-subnet-add"));
    ASSERT_TRUE(checkCommandRegistered("network4-subnet-del"));
    ASSERT_TRUE(checkCommandRegistered("network6-subnet-del"));

    unloadLibs();

    EXPECT_FALSE(checkCommandRegistered("subnet4-list"));
    EXPECT_FALSE(checkCommandRegistered("subnet6-list"));
    EXPECT_FALSE(checkCommandRegistered("subnet4-get"));
    EXPECT_FALSE(checkCommandRegistered("subnet6-get"));
    EXPECT_FALSE(checkCommandRegistered("subnet4-add"));
    EXPECT_FALSE(checkCommandRegistered("subnet6-add"));
    EXPECT_FALSE(checkCommandRegistered("subnet4-update"));
    EXPECT_FALSE(checkCommandRegistered("subnet6-update"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-del"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-del"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-delta-add"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-delta-add"));
    ASSERT_FALSE(checkCommandRegistered("subnet4-delta-del"));
    ASSERT_FALSE(checkCommandRegistered("subnet6-delta-del"));
    EXPECT_FALSE(checkCommandRegistered("network4-list"));
    EXPECT_FALSE(checkCommandRegistered("network6-list"));
    EXPECT_FALSE(checkCommandRegistered("network4-get"));
    EXPECT_FALSE(checkCommandRegistered("network6-get"));
    EXPECT_FALSE(checkCommandRegistered("network4-add"));
    EXPECT_FALSE(checkCommandRegistered("network6-add"));
    EXPECT_FALSE(checkCommandRegistered("network4-del"));
    EXPECT_FALSE(checkCommandRegistered("network6-del"));
    EXPECT_FALSE(checkCommandRegistered("network4-subnet-add"));
    EXPECT_FALSE(checkCommandRegistered("network6-subnet-add"));
    EXPECT_FALSE(checkCommandRegistered("network4-subnet-del"));
    EXPECT_FALSE(checkCommandRegistered("network6-subnet-del"));

    setFamily(AF_INET6);
    loadSubnetCmds();

    ASSERT_TRUE(checkCommandRegistered("subnet4-list"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-list"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-get"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-get"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-update"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-update"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-del"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-del"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-delta-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-delta-add"));
    ASSERT_TRUE(checkCommandRegistered("subnet4-delta-del"));
    ASSERT_TRUE(checkCommandRegistered("subnet6-delta-del"));
    ASSERT_TRUE(checkCommandRegistered("network4-list"));
    ASSERT_TRUE(checkCommandRegistered("network6-list"));
    ASSERT_TRUE(checkCommandRegistered("network4-get"));
    ASSERT_TRUE(checkCommandRegistered("network6-get"));
    ASSERT_TRUE(checkCommandRegistered("network4-add"));
    ASSERT_TRUE(checkCommandRegistered("network6-add"));
    ASSERT_TRUE(checkCommandRegistered("network4-del"));
    ASSERT_TRUE(checkCommandRegistered("network6-del"));
    ASSERT_TRUE(checkCommandRegistered("network4-subnet-add"));
    ASSERT_TRUE(checkCommandRegistered("network6-subnet-add"));
    ASSERT_TRUE(checkCommandRegistered("network4-subnet-del"));
    ASSERT_TRUE(checkCommandRegistered("network6-subnet-del"));
}

// Check that the library can be loaded and unloaded multiple times.
TEST_F(SubnetCmdsTest, multipleLoads) {

    setFamily(AF_INET);
    EXPECT_NO_THROW(loadSubnetCmds());
    EXPECT_NO_THROW(unloadLibs());

    EXPECT_NO_THROW(loadSubnetCmds());
    EXPECT_NO_THROW(unloadLibs());

    EXPECT_NO_THROW(loadSubnetCmds());
    EXPECT_NO_THROW(unloadLibs());

    setFamily(AF_INET6);
    EXPECT_NO_THROW(loadSubnetCmds());
    EXPECT_NO_THROW(unloadLibs());

    EXPECT_NO_THROW(loadSubnetCmds());
    EXPECT_NO_THROW(unloadLibs());
}

} // end of anonymous namespace
