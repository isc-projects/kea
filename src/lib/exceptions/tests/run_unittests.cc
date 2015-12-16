// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

int
main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    // Unlike other tests we cannot use our wrapper for RUN_ALL_TESTS()
    // due to dependency.
    return (RUN_ALL_TESTS());
}
