// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include <asiolink/io_address.h>
#include <dhcp/lease_mgr.h>
#include <dhcp/duid.h>
#include <dhcp/alloc_engine.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;


namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class AllocEngineTest : public ::testing::Test {
public:
    AllocEngineTest() {
    }
};

// This test checks if the Allocation Engine can be instantiated and that it
// parses parameters string properly.
TEST_F(AllocEngineTest, constructor) {

    AllocEngine* x = NULL;

    // Hashed and random allocators are not supported yet
    ASSERT_THROW(x = new AllocEngine(AllocEngine::ALLOC_HASHED, 5), BadValue);
    ASSERT_THROW(x = new AllocEngine(AllocEngine::ALLOC_RANDOM, 5), BadValue);

    ASSERT_NO_THROW(x = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));

    delete x;
}

}; // end of anonymous namespace
