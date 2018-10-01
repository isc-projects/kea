// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <netconf/netconf_cfg_mgr.h>
#include <exceptions/exceptions.h>
#include <process/testutils/d_test_stubs.h>
#include <process/d_cfg_mgr.h>
#include <netconf/tests/test_libraries.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::netconf;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::process;

namespace  {

/// @brief Almost regular netconf CfgMgr with internal parse method exposed.
class NakedNetconfCfgMgr : public NetconfCfgMgr {
public:
    using NetconfCfgMgr::parse;
};

// Tests construction of NetconfCfgMgr class.
TEST(NetconfCfgMgr, construction) {
    boost::scoped_ptr<NetconfCfgMgr> cfg_mgr;

    // Verify that configuration manager constructions without error.
    ASSERT_NO_THROW(cfg_mgr.reset(new NetconfCfgMgr()));

    // Verify that the context can be retrieved and is not null.
    NetconfCfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr->getNetconfCfgContext());
    EXPECT_TRUE(context);

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(cfg_mgr.reset());
}

// Tests if getContext can be retrieved.
TEST(NetconfCfgMgr, getContext) {
    NetconfCfgMgr cfg_mgr;

    NetconfCfgContextPtr ctx;
    ASSERT_NO_THROW(ctx = cfg_mgr.getNetconfCfgContext());
    ASSERT_TRUE(ctx);
}

// Tests if the context can store and retrieve hook libs information.
TEST(NetconfCfgMgr, contextHookParams) {
    NetconfCfgContext ctx;

    // By default there should be no hooks.
    HooksConfig& libs = ctx.getHooksConfig();
    EXPECT_TRUE(libs.get().empty());

    libs.add("libone.so", ConstElementPtr());
    libs.add("libtwo.so", Element::fromJSON("{\"foo\": true}"));
    libs.add("libthree.so", Element::fromJSON("{\"bar\": 42}"));

    const HooksConfig& stored_libs = ctx.getHooksConfig();
    EXPECT_EQ(3, stored_libs.get().size());

    EXPECT_EQ(libs.get(), stored_libs.get());
}

}; // end of anonymous namespace
