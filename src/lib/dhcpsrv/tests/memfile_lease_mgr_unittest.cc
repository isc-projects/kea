// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/tests/test_utils.h>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class MemfileLeaseMgrTest : public GenericLeaseMgrTest {
public:

    /// @brief memfile lease mgr test constructor
    ///
    /// Creates memfile and stores it in lmptr_ pointer
    MemfileLeaseMgrTest() {
        const LeaseMgr::ParameterMap pmap;
        lmptr_ = new Memfile_LeaseMgr(pmap);
    }

    virtual void reopen() {
        /// @todo: write lease to disk, flush, read file from disk
    }

    /// @brief destructor
    ///
    /// destroys lease manager backend.
    virtual ~MemfileLeaseMgrTest() {
        delete lmptr_;
        lmptr_ = 0;
    }

};

// This test checks if the LeaseMgr can be instantiated and that it
// parses parameters string properly.
TEST_F(MemfileLeaseMgrTest, constructor) {

    const LeaseMgr::ParameterMap pmap;  // Empty parameter map
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr;

    ASSERT_NO_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)));
}

// Checks if the getType() and getName() methods both return "memfile".
TEST_F(MemfileLeaseMgrTest, getTypeAndName) {
    EXPECT_EQ(std::string("memfile"), lmptr_->getType());
    EXPECT_EQ(std::string("memory"),  lmptr_->getName());
}

// Checks that adding/getting/deleting a Lease6 object works.
TEST_F(MemfileLeaseMgrTest, addGetDelete6) {
    testAddGetDelete6(true);
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4 (by address) and deleteLease (with an
/// IPv4 address) works.
TEST_F(MemfileLeaseMgrTest, basicLease4) {
    testBasicLease4();
}

/// @todo Write more memfile tests

// Simple test about lease4 retrieval through client id method
TEST_F(MemfileLeaseMgrTest, getLease4ClientId) {
    testGetLease4ClientId();
}

// Checks that lease4 retrieval client id is null is working
TEST_F(MemfileLeaseMgrTest, getLease4NullClientId) {
    testGetLease4NullClientId();
}

// Checks lease4 retrieval through HWAddr
TEST_F(MemfileLeaseMgrTest, getLease4HWAddr) {
    testGetLease4HWAddr();
}

// Checks lease4 retrieval with clientId, HWAddr and subnet_id
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdHWAddrSubnetId) {
    testGetLease4ClientIdHWAddrSubnetId();
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease (IPv4 address) can handle NULL client-id.
/// (client-id is optional and may not be present)
TEST_F(MemfileLeaseMgrTest, DISABLED_lease4NullClientId) {

    /// @todo Test is disabled, because memfile does not support disk storage, so
    /// all leases are lost after reopen()
    testLease4NullClientId();
}


}; // end of anonymous namespace
