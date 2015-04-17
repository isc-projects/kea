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
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/tests/test_utils.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <time.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

// This is a concrete implementation of a Lease database.  It does not do
// anything useful and is used for abstract LeaseMgr class testing.
class ConcreteLeaseMgr : public LeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ConcreteLeaseMgr(const DataSource::ParameterMap&)
        : LeaseMgr()
    {}

    /// @brief Destructor
    virtual ~ConcreteLeaseMgr()
    {}

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease4Ptr&) {
        return (false);
    }

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease6Ptr&) {
        return (false);
    }

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress&) const {
        return (Lease4Ptr());
    }

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
    virtual Lease4Collection getLease4(const HWAddr&) const {
        return (Lease4Collection());
    }

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
    virtual Lease4Ptr getLease4(const HWAddr&, SubnetID) const {
        return (Lease4Ptr());
    }

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const ClientId&) const {
        return (Lease4Collection());
    }

    /// @brief Returns existing IPv4 lease for specified client identifier,
    /// HW address and subnet identifier.
    ///
    /// @param client_id Aclient identifier
    /// @param hwaddr A HW address.
    /// @param subnet_id A subnet identifier.
    ///
    /// @return A pointer to an existing lease or NULL if lease not found.
    virtual Lease4Ptr
    getLease4(const ClientId&, const HWAddr&, SubnetID) const {
        return (Lease4Ptr());
    }

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId&, SubnetID) const {
        return (Lease4Ptr());
    }

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(Lease::Type /* not used yet */,
                                const isc::asiolink::IOAddress&) const {
        return (Lease6Ptr());
    }

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid ignored
    /// @param iaid ignored
    ///
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(Lease::Type /* not used yet */,
                                        const DUID&, uint32_t) const {
        return (leases6_);
    }

    /// @brief Returns existing IPv6 lease for a given DUID+IA+subnet-id combination
    ///
    /// @param duid ignored
    /// @param iaid ignored
    /// @param subnet_id ignored
    ///
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(Lease::Type /* not used yet */,
                                        const DUID&, uint32_t, SubnetID) const {
        return (leases6_);
    }

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr&) {}

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease6(const Lease6Ptr&) {}

    /// @brief Deletes a lease.
    ///
    /// @param addr Address of the lease to be deleted. (This can be either
    ///        a V4 address or a V6 address.)
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease(const isc::asiolink::IOAddress&) {
        return (false);
    }

    /// @brief Returns backend type.
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("concrete"));
    }

    /// @brief Returns backend name.
    ///
    /// If the backend is a database, this is the name of the database or the
    /// file.  Otherwise it is just the same as the type.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const {
        return (std::string("concrete"));
    }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const {
        return (std::string("This is a dummy concrete backend implementation."));
    }

    /// @brief Returns backend version.
    virtual std::pair<uint32_t, uint32_t> getVersion() const {
        return (make_pair(uint32_t(0), uint32_t(0)));
    }

    /// @brief Commit transactions
    virtual void commit() {
    }

    /// @brief Rollback transactions
    virtual void rollback() {
    }

    // We need to use it in ConcreteLeaseMgr
    using LeaseMgr::getLease6;

    Lease6Collection leases6_; ///< getLease6 methods return this as is
};

class LeaseMgrTest : public GenericLeaseMgrTest {
public:
    LeaseMgrTest() {
    }

    /// @brief Reopen the database
    ///
    /// No-op implementation. We need to provide concrete implementation,
    /// as this is a pure virtual method in GenericLeaseMgrTest.
    virtual void reopen(Universe) {
    }

};

namespace {

// This test checks if getLease6() method is working properly for 0 (NULL),
// 1 (return the lease) and more than 1 leases (throw).
TEST_F(LeaseMgrTest, getLease6) {

    DataSource::ParameterMap pmap;
    boost::scoped_ptr<ConcreteLeaseMgr> mgr(new ConcreteLeaseMgr(pmap));

    vector<Lease6Ptr> leases = createLeases6();

    mgr->leases6_.clear();
    // For no leases, the function should return NULL pointer
    Lease6Ptr lease;

    // the getLease6() is calling getLeases6(), which is a dummy. It returns
    // whatever is there in leases6_ field.
    EXPECT_NO_THROW(lease = mgr->getLease6(leasetype6_[1], *leases[1]->duid_,
                                           leases[1]->iaid_,
                                           leases[1]->subnet_id_));
    EXPECT_TRUE(Lease6Ptr() == lease);

    // For a single lease, the function should return that lease
    mgr->leases6_.push_back(leases[1]);
    EXPECT_NO_THROW(lease = mgr->getLease6(leasetype6_[1], *leases[1]->duid_,
                                           leases[1]->iaid_,
                                           leases[1]->subnet_id_));
    EXPECT_TRUE(lease);

    EXPECT_NO_THROW(detailCompareLease(lease, leases[1]));

    // Add one more lease. There are 2 now. It should throw
    mgr->leases6_.push_back(leases[2]);

    EXPECT_THROW(lease = mgr->getLease6(leasetype6_[1], *leases[1]->duid_,
                                        leases[1]->iaid_,
                                        leases[1]->subnet_id_),
                 MultipleRecords);
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call ConcreteLeaseMgr methods.
// Those methods are just stubs that do not return anything.



}; // end of anonymous namespace
