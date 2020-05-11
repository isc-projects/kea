// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/resource_handler.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

namespace {

// Verifies behavior with empty block.
TEST(ResourceHandleTest, empty) {
    try {
        // Get a resource handler.
        ResourceHandler resource_handler;
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with empty block (v4).
TEST(ResourceHandleTest, empty4) {
    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

} // end of anonymous namespace
