// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <stats/stats_mgr.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::stats;

namespace {

class StatsMgrTest : public ::testing::Test {
public:
    StatsMgrTest() {
    }
};

// Basic tests for V4 functionality
TEST_F(StatsMgrTest, basic) {

    //    EXPECT_NO_THROW(StatsMgr::instance());
}

};
