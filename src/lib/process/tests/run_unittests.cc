// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <log/logger_support.h>
#include <process/d_log.h>
#include <gtest/gtest.h>

int
main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    isc::log::initLogger();

    // Override --localstatedir value for PID files
    setenv("KEA_PIDFILE_DIR", TEST_DATA_BUILDDIR, 1);

    int result = RUN_ALL_TESTS();

    return (result);
}
