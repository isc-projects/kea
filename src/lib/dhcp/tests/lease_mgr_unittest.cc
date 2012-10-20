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

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

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
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    Memfile_LeaseMgr(const LeaseMgr::ParameterMap& parameters);

    /// @brief Destructor (closes file)
    virtual ~Memfile_LeaseMgr();

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease4Ptr& lease);

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease6Ptr& lease);

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return a collection of leases
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv4 lease for specific address and subnet
    /// @param addr address of the searched lease
    /// @param subnet_id ID of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr,
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
    Lease6Ptr getLease6(const isc::asiolink::IOAddress& addr) const;

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
    void updateLease4(const Lease4Ptr& lease4);

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    void updateLease6(const Lease6Ptr& lease6);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease4(const isc::asiolink::IOAddress& addr);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease6(const isc::asiolink::IOAddress& addr);

    /// @brief Returns backend name.
    ///
    /// Each backend have specific name, e.g. "mysql" or "sqlite".
    std::string getName() const { return "memfile"; }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    std::string getDescription() const;

    /// @brief Returns backend version.
    std::pair<uint32_t, uint32_t> getVersion() const {
        return (make_pair(uint32_t(0), uint32_t(0)));
    }

    /// @brief Commit transactions
    void commit() {
    }

    /// @brief Rollback transactions
    void rollback() {
    }

    using LeaseMgr::getParameter;

protected:


};

Memfile_LeaseMgr::Memfile_LeaseMgr(const LeaseMgr::ParameterMap& parameters)
    : LeaseMgr(parameters) {
}

Memfile_LeaseMgr::~Memfile_LeaseMgr() {
}

bool Memfile_LeaseMgr::addLease(const boost::shared_ptr<isc::dhcp::Lease4>&) {
    return (false);
}

bool Memfile_LeaseMgr::addLease(const boost::shared_ptr<isc::dhcp::Lease6>&) {
    return (false);
}

Lease4Ptr Memfile_LeaseMgr::getLease4(const isc::asiolink::IOAddress&) const {
    return (Lease4Ptr());
}

Lease4Collection Memfile_LeaseMgr::getLease4(const HWAddr& ) const {
    return (Lease4Collection());
}

Lease4Ptr Memfile_LeaseMgr::getLease4(const isc::asiolink::IOAddress & ,
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

Lease6Ptr Memfile_LeaseMgr::getLease6(const isc::asiolink::IOAddress&) const {
    return (Lease6Ptr());
}

Lease6Collection Memfile_LeaseMgr::getLease6(const DUID& , uint32_t ) const {
    return (Lease6Collection());
}

Lease6Ptr Memfile_LeaseMgr::getLease6(const DUID&, uint32_t,
                                      SubnetID) const {
    return (Lease6Ptr());
}

void Memfile_LeaseMgr::updateLease4(const Lease4Ptr&) {
}

void Memfile_LeaseMgr::updateLease6(const Lease6Ptr&) {

}

bool Memfile_LeaseMgr::deleteLease4(const isc::asiolink::IOAddress&) {
    return (false);
}

bool Memfile_LeaseMgr::deleteLease6(const isc::asiolink::IOAddress&) {
    return (false);
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
TEST_F(LeaseMgrTest, getParameter) {

    LeaseMgr::ParameterMap pmap;
    pmap[std::string("param1")] = std::string("value1");
    pmap[std::string("param2")] = std::string("value2");
    Memfile_LeaseMgr leasemgr(pmap);

    EXPECT_EQ("value1", leasemgr.getParameter("param1"));
    EXPECT_EQ("value2", leasemgr.getParameter("param2"));
    EXPECT_THROW(leasemgr.getParameter("param3"), BadValue);
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call Memfile_LeaseMgr methods.
// Those methods are just stubs that does not return anything.
// It seems likely that we will need to extend the memfile code for
// allocation engine tests, so we may implement tests that call
// Memfile_LeaseMgr methods then.

}; // end of anonymous namespace
