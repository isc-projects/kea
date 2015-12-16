// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>

#include <boost/asio.hpp>

#include <asiolink/dummy_io_cb.h>

using namespace isc::asiolink;
using namespace boost::asio;

namespace { // begin unnamed namespace

TEST(DummyIOCallbackTest, throws) {
    DummyIOCallback cb;
    boost::system::error_code error_code;

    // All methods should throw isc::Unexpected.
    EXPECT_THROW(cb(error_code), isc::Unexpected);
    EXPECT_THROW(cb(error_code, 42), isc::Unexpected);
}

} // end of unnamed namespace
