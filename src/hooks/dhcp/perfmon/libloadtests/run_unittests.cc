// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.

#include <config.h>

#include <log/logger_support.h>

#include <gtest/gtest.h>

int
main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    isc::log::initLogger();

    int result = RUN_ALL_TESTS();

    return (result);
}
