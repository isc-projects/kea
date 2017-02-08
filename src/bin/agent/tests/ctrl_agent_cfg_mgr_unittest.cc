// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ctrl_agent_cfg_mgr.h>
#include <process/testutils/d_test_stubs.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc::agent;

namespace  {

// Tests construction of CtrlAgentCfgMgr class.
TEST(CtrlAgentCfgMgr, construction) {
    boost::scoped_ptr<CtrlAgentCfgMgr> cfg_mgr;

    // Verify that configuration manager constructions without error.
    ASSERT_NO_THROW(cfg_mgr.reset(new CtrlAgentCfgMgr()));

    // Verify that the context can be retrieved and is not null.
    CtrlAgentCfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr->getCtrlAgentCfgContext());
    EXPECT_TRUE(context);

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(cfg_mgr.reset());
}

}
