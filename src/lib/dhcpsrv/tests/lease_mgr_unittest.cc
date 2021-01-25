// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <time.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
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
    ConcreteLeaseMgr(const DatabaseConnection::ParameterMap&)
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
    /// @param client_id A client identifier
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

    /// @brief Returns all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(SubnetID) const {
        return (Lease4Collection());
    }

    /// @brief Returns all IPv4 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(const std::string&) const {
        return (Lease4Collection());
    }

    /// @brief Returns all IPv4 leases.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4() const {
        return (Lease4Collection());
    }

    /// @brief Returns range of IPv4 leases using paging.
    ///
    /// This method implements paged browsing of the lease database. The first
    /// parameter specifies a page size. The second parameter is optional and
    /// specifies the starting address of the range. This address is excluded
    /// from the returned range. The IPv4 zero address (default) denotes that
    /// the first page should be returned. There is no guarantee about the
    /// order of returned leases.
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of leases by specifying IPv4 zero address as the
    ///   beginning of the range.
    /// - Last address of the returned range should be used as a starting
    ///   address for the next page in the subsequent call.
    /// - If the number of leases returned is lower than the page size, it
    ///   indicates that the last page has been retrieved.
    /// - If there are no leases returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection
    getLeases4(const asiolink::IOAddress& /* lower_bound_address */,
               const LeasePageSize& /* page_size */) const {
        return (Lease4Collection());
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

    /// @brief Returns collection of lease for matching DUID
    ///
    /// @param duid ignored
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(const DUID&) const {
        return (leases6_);
    }

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(SubnetID) const {
        return (Lease6Collection());
    }

    /// @brief Returns all IPv6 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(const std::string&) const {
        return (Lease6Collection());
    }

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6() const {
        return (Lease6Collection());
    }

    /// @brief Returns range of IPv6 leases using paging.
    ///
    /// This method implements paged browsing of the lease database. The first
    /// parameter specifies a page size. The second parameter is optional and
    /// specifies the starting address of the range. This address is excluded
    /// from the returned range. The IPv6 zero address (default) denotes that
    /// the first page should be returned. There is no guarantee about the
    /// order of returned leases.
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of leases by specifying IPv6 zero address as the
    ///   beginning of the range.
    /// - Last address of the returned range should be used as a starting
    ///   address for the next page in the subsequent call.
    /// - If the number of leases returned is lower than the page size, it
    ///   indicates that the last page has been retrieved.
    /// - If there are no leases returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection
    getLeases6(const asiolink::IOAddress& /* lower_bound_address */,
               const LeasePageSize& /* page_size */) const {
        return (Lease6Collection());
    };

    /// @brief Returns expired DHCPv6 leases.
    ///
    /// This method is not implemented.
    virtual void getExpiredLeases6(Lease6Collection&, const size_t) const {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getExpiredLeases6 is not"
                  " implemented");
    }

    /// @brief Returns expired DHCPv4 leases.
    ///
    /// This method is not implemented.
    virtual void getExpiredLeases4(Lease4Collection&, const size_t) const {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getExpiredLeases4 is not"
                  " implemented");
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

    /// @brief Deletes an IPv4 lease.
    ///
    /// @param lease IPv4 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    virtual bool deleteLease(const Lease4Ptr&) {
        return (false);
    }

    /// @brief Deletes an IPv6 lease.
    ///
    /// @param lease IPv6 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    virtual bool deleteLease(const Lease6Ptr&) {
        return (false);
    }

    /// @brief Deletes all expired and reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t) {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::deleteExpiredReclaimedLeases4"
                  " is not implemented");
    }

    /// @brief Deletes all expired and reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t) {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::deleteExpiredReclaimedLeases6"
                  " is not implemented");
    }

    /// @brief Pretends to wipe all IPv4 leases from a subnet
    /// @param subnet_id (ignored, but one day may specify the subnet)
    virtual size_t wipeLeases4(const SubnetID&) {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::wipeLeases4 not implemented");
    }

    /// @brief Pretends to wipe all IPv4 leases from a subnet
    /// @param subnet_id (ignored, but one day may specify the subnet)
    virtual size_t wipeLeases6(const SubnetID&) {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::wipeLeases6 not implemented");
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

    DatabaseConnection::ParameterMap pmap;
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
    EXPECT_FALSE(lease);

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

// Verify LeaseStatsQuery default construction
TEST (LeaseStatsQueryTest, defaultCtor) {
    LeaseStatsQueryPtr qry;

    // Valid construction, verifiy member values.
    ASSERT_NO_THROW(qry.reset(new LeaseStatsQuery()));
    ASSERT_EQ(0, qry->getFirstSubnetID());
    ASSERT_EQ(0, qry->getLastSubnetID());
    ASSERT_EQ(LeaseStatsQuery::ALL_SUBNETS, qry->getSelectMode());
}

// Verify LeaseStatsQuery single-subnet construction
TEST (LeaseStatsQueryTest, singleSubnetCtor) {
    LeaseStatsQueryPtr qry;

    // Invalid values for subnet_id
    ASSERT_THROW(qry.reset(new LeaseStatsQuery(0)), BadValue);

    // Valid values should work and set mode accordingly.
    ASSERT_NO_THROW(qry.reset(new LeaseStatsQuery(77)));
    ASSERT_EQ(77, qry->getFirstSubnetID());
    ASSERT_EQ(0, qry->getLastSubnetID());
    ASSERT_EQ(LeaseStatsQuery::SINGLE_SUBNET, qry->getSelectMode());
}

// Verify LeaseStatsQuery subnet-range construction
TEST (LeaseStatsQueryTest, subnetRangeCtor) {
    LeaseStatsQueryPtr qry;

    // Either ID set to 0, or a backward range should throw
    ASSERT_THROW(qry.reset(new LeaseStatsQuery(0,1)), BadValue);
    ASSERT_THROW(qry.reset(new LeaseStatsQuery(1,0)), BadValue);
    ASSERT_THROW(qry.reset(new LeaseStatsQuery(2,1)), BadValue);

    // Valid values should work and set mode accordingly.
    ASSERT_NO_THROW(qry.reset(new LeaseStatsQuery(1,2)));
    ASSERT_EQ(1, qry->getFirstSubnetID());
    ASSERT_EQ(2, qry->getLastSubnetID());
    ASSERT_EQ(LeaseStatsQuery::SUBNET_RANGE, qry->getSelectMode());
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call ConcreteLeaseMgr methods.
// Those methods are just stubs that do not return anything.

}  // namespace
