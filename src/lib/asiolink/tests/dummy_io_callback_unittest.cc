// Copyright (C) 2014-2015  Internet Systems Consortium, Inc. ("ISC")
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
