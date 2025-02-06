// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/lease_mgr_factory.h>

#include <gtest/gtest.h>

namespace {

#define SCOPED_LINE(line) \
    std::stringstream ss; \
    ss << "Scenario at line: " << line; \
    SCOPED_TRACE(ss.str());

class LeaseCmdsFuncTest :  public ::testing::Test { 
public:
    /// @brief Constructor
    LeaseCmdsFuncTest() {
        isc::dhcp::LeaseMgrFactory::destroy();
        lmptr_ = 0;
    }

    virtual void SetUp() {
        initLeaseMgr();
    }

    /// @brief Destructor
    ///
    virtual ~LeaseCmdsFuncTest() {
        isc::dhcp::LeaseMgrFactory::destroy();
        lmptr_ = 0;
    }

    /// @brief Initializes lease manager creates the lease manager
    /// and initial leases.
    virtual void initLeaseMgr() = 0;

    /// @brief Pointer to the lease manager
    isc::dhcp::LeaseMgr* lmptr_;
};

} // end of anonymous namespace
