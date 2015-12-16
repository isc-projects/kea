// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <util/unittests/run_all.h>
#include <stdlib.h>

// This file uses TEST_DATA_TOPBUILDDIR macro, which must point to a writeable
// directory. It will be used for creating a logger lockfile.

int
main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    setenv("KEA_LOCKFILE_DIR", TEST_DATA_TOPBUILDDIR, 1);
    return (isc::util::unittests::run_all());
}
