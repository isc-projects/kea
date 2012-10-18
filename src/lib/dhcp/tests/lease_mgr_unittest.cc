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

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/mem_fun.hpp>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

using namespace boost;
using namespace boost::multi_index;

// This is a concrete implementation of a Lease database.
// It does not do anything useful now, and is used for abstract LeaseMgr
// class testing. It may later evolve into more useful backend if the
// need arises. We can reuse code from memfile benchmark. See code in
// tests/tools/dhcp-ubench/memfile_bench.{cc|h}
class Memfile_LeaseMgr : public LeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ///
    /// @param dbconfig database configuration
    Memfile_LeaseMgr(const std::string& dbconfig);

    /// @brief Destructor (closes file)
    virtual ~Memfile_LeaseMgr();

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(Lease4Ptr lease);

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(Lease6Ptr lease);

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return a collection of leases
    virtual Lease4Ptr getLease4(isc::asiolink::IOAddress addr) const;

    /// @brief Returns existing IPv4 lease for specific address and subnet
    /// @param addr address of the searched lease
    /// @param subnet_id ID of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(isc::asiolink::IOAddress addr,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv4 leases for specified hardware address.
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param hwaddr hardware address of the client
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const HWAddr& hwaddr) const;

    /// @brief Returns existing IPv4 leases for specified hardware address
    ///        and a subnet
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const HWAddr& hwaddr,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    virtual Lease4Collection getLease4(const ClientId& clientid) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    Lease6Ptr getLease6(isc::asiolink::IOAddress addr) const;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return collection of IPv6 leases
    Lease6Collection getLease6(const DUID& duid, uint32_t iaid) const;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id identifier of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    Lease6Ptr getLease6(const DUID& duid, uint32_t iaid, SubnetID subnet_id) const;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    void updateLease4(Lease4Ptr lease4);

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    void updateLease6(Lease6Ptr lease6);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease4(uint32_t addr);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease6(isc::asiolink::IOAddress addr);

    /// @brief Returns backend name.
    ///
    /// Each backend have specific name, e.g. "mysql" or "sqlite".
    std::string getName() const { return "memfile"; }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    std::string getDescription() const;

    /// @brief Returns backend version.
    std::string getVersion() const { return "test-version"; }

    using LeaseMgr::getParameter;

protected:

    typedef multi_index_container< // this is a multi-index container...
    Lease6Ptr, // it will hold shared_ptr to leases6
    indexed_by< // and will be sorted by

        // IPv6 address that are unique. That particular key is a member
        // of the Lease6 structure, is of type IOAddress and can be accessed
        // by doing &Lease6::addr_
        ordered_unique< member<Lease6, IOAddress, &Lease6::addr_> >
        >
    > Lease6Storage; // Let the whole contraption be called Lease6Storage.

    Lease6Storage storage6_;
};

Memfile_LeaseMgr::Memfile_LeaseMgr(const std::string& dbconfig)
    : LeaseMgr(dbconfig) {
}

Memfile_LeaseMgr::~Memfile_LeaseMgr() {
}

bool Memfile_LeaseMgr::addLease(Lease4Ptr) {
    return (false);
}

bool Memfile_LeaseMgr::addLease(Lease6Ptr lease) {
    if (getLease6(lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }
    storage6_.insert(lease);
    return (true);
}

Lease4Ptr Memfile_LeaseMgr::getLease4(isc::asiolink::IOAddress) const {
    return (Lease4Ptr());
}

Lease4Collection Memfile_LeaseMgr::getLease4(const HWAddr& ) const {
    return (Lease4Collection());
}

Lease4Ptr Memfile_LeaseMgr::getLease4(isc::asiolink::IOAddress ,
                                      SubnetID) const {
    return (Lease4Ptr());
}

Lease4Ptr Memfile_LeaseMgr::getLease4(const HWAddr&,
                                      SubnetID) const {
    return (Lease4Ptr());
}


Lease4Ptr Memfile_LeaseMgr::getLease4(const ClientId&,
                                      SubnetID) const {
    return (Lease4Ptr());
}

Lease4Collection Memfile_LeaseMgr::getLease4(const ClientId& ) const {
    return (Lease4Collection());
}

Lease6Ptr Memfile_LeaseMgr::getLease6(isc::asiolink::IOAddress addr) const {
    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end()) {
        return (Lease6Ptr());
    } else {
        return (*l);
    }
}

Lease6Collection Memfile_LeaseMgr::getLease6(const DUID& , uint32_t ) const {
    return (Lease6Collection());
}

Lease6Ptr Memfile_LeaseMgr::getLease6(const DUID&, uint32_t,
                                      SubnetID) const {

    return (Lease6Ptr());
}

void Memfile_LeaseMgr::updateLease4(Lease4Ptr ) {
}

void Memfile_LeaseMgr::updateLease6(Lease6Ptr ) {

}

bool Memfile_LeaseMgr::deleteLease4(uint32_t ) {
    return (false);
}

bool Memfile_LeaseMgr::deleteLease6(isc::asiolink::IOAddress addr) {
    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end()) {
        // no such lease
        return (false);
    } else {
        storage6_.erase(l);
        return (true);
    }
}

std::string Memfile_LeaseMgr::getDescription() const {
    return (string("This is a dummy memfile backend implementation.\n"
                   "It does not offer any useful lease management and its only\n"
                   "purpose is to test abstract lease manager API."));
}

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class LeaseMgrTest : public ::testing::Test {
public:
    LeaseMgrTest() {
    }
};

// This test checks if the LeaseMgr can be instantiated and that it
// parses parameters string properly.
TEST_F(LeaseMgrTest, constructor) {

    // should not throw any exceptions here
    Memfile_LeaseMgr * leaseMgr = new Memfile_LeaseMgr("");
    delete leaseMgr;

    leaseMgr = new Memfile_LeaseMgr("param1=value1 param2=value2");

    EXPECT_EQ("value1", leaseMgr->getParameter("param1"));
    EXPECT_EQ("value2", leaseMgr->getParameter("param2"));
    EXPECT_THROW(leaseMgr->getParameter("param3"), BadValue);

    delete leaseMgr;
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call Memfile_LeaseMgr methods.
// Those methods are just stubs that does not return anything.
// It seems likely that we will need to extend the memfile code for
// allocation engine tests, so we may implement tests that call
// Memfile_LeaseMgr methods then.

TEST_F(LeaseMgrTest, addGetDelete) {
    Memfile_LeaseMgr * leaseMgr = new Memfile_LeaseMgr("");

    IOAddress addr("2001:db8:1::456");

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    uint32_t iaid = 7; // just a number

    SubnetID subnet_id = 8; // just another number

    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr,
                               duid, iaid, 100, 200, 50, 80,
                               subnet_id));

    EXPECT_TRUE(leaseMgr->addLease(lease));

    // should not be allowed to add a second lease with the same address
    EXPECT_FALSE(leaseMgr->addLease(lease));

    Lease6Ptr x = leaseMgr->getLease6(IOAddress("2001:db8:1::234"));
    EXPECT_EQ(Lease6Ptr(), x);

    x = leaseMgr->getLease6(IOAddress("2001:db8:1::456"));
    ASSERT_TRUE(x);

    EXPECT_TRUE(x->addr_ == addr);
    EXPECT_TRUE(*x->duid_ == *duid);
    EXPECT_TRUE(x->iaid_ == iaid);
    EXPECT_TRUE(x->subnet_id_ == subnet_id);

    // These are not important from lease management perspective, but
    // let's check them anyway.
    EXPECT_TRUE(x->type_ == Lease6::LEASE_IA_NA);
    EXPECT_TRUE(x->preferred_lft_ == 100);
    EXPECT_TRUE(x->valid_lft_ == 200);
    EXPECT_TRUE(x->t1_ == 50);
    EXPECT_TRUE(x->t2_ == 80);

    // should return false - there's no such address
    EXPECT_FALSE(leaseMgr->deleteLease6(IOAddress("2001:db8:1::789")));

    // this one should succeed
    EXPECT_TRUE(leaseMgr->deleteLease6(IOAddress("2001:db8:1::456")));

    // after the lease is deleted, it should really be gone
    x = leaseMgr->getLease6(IOAddress("2001:db8:1::456"));
    EXPECT_EQ(Lease6Ptr(), x);

    delete leaseMgr;
}

}; // end of anonymous namespace
