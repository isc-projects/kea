// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cfgrpt/config_report.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace std;

// This test verifies that the getConfigReport() function
// returns the actual config report.
TEST(ConfigReportTest, getConfigReport) {

    // Fetch the report string
    std::string cfgReport = isc::detail::getConfigReport();

    // Verify that it is not empty and does contain the
    // extended version number
    ASSERT_FALSE(cfgReport.empty());
    EXPECT_NE(std::string::npos, cfgReport.find(EXTENDED_VERSION, 0));
}
