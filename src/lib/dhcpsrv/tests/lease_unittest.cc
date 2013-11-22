// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/duid.h>
#include <dhcpsrv/lease.h>
#include <gtest/gtest.h>
#include <vector>

using namespace isc;
using namespace isc::dhcp;

namespace {

// @todo Currently this file contains tests for new functions which return DUID
// or client identifier. Other tests for Lease objects must be implemented.
// See http://bind10.isc.org/ticket/3240.

// Verify that the client id can be returned as a vector object and if client
// id is NULL the empty vector is returned.
TEST(Lease4Test, getClientIdVector) {
    // Create a lease.
    Lease4 lease;
    // By default, the lease should have client id set to NULL. If it doesn't,
    // continuing the test makes no sense.
    ASSERT_FALSE(lease.client_id_);
    // When client id is NULL the vector returned should be empty.
    EXPECT_TRUE(lease.getClientIdVector().empty());
    // Now, let's set the non NULL client id. Fill it with the 8 bytes, each
    // holding a value of 0x42.
    std::vector<uint8_t> client_id_vec(8, 0x42);
    lease.client_id_ = ClientIdPtr(new ClientId(client_id_vec));
    // Check that the returned vector, encapsulating client id is equal to
    // the one that has been used to set the client id for the lease.
    std::vector<uint8_t> returned_vec = lease.getClientIdVector();
    EXPECT_TRUE(returned_vec == client_id_vec);
}

// Verify that the DUID can be returned as a vector object and if DUID is NULL
// the empty vector is returned.
TEST(Lease6Test, getDuidVector) {
    // Create a lease.
    Lease6 lease;
    // By default, the lease should have client id set to NULL. If it doesn't,
    // continuing the test makes no sense.
    ASSERT_FALSE(lease.duid_);
    // When client id is NULL the vector returned should be empty.
    EXPECT_TRUE(lease.getDuidVector().empty());
    // Now, let's set the non NULL DUID. Fill it with the 8 bytes, each
    // holding a value of 0x42.
    std::vector<uint8_t> duid_vec(8, 0x42);
    lease.duid_ = DuidPtr(new DUID(duid_vec));
    // Check that the returned vector, encapsulating DUID is equal to
    // the one that has been used to set the DUID for the lease.
    std::vector<uint8_t> returned_vec = lease.getDuidVector();
    EXPECT_TRUE(returned_vec == duid_vec);
}


}; // end of anonymous namespace
