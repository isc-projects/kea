// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
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
#include <testutils/gtest_utils.h>

#include <iostream>
#include <list>
#include <sstream>

#include <time.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
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
    virtual bool addLease(const Lease4Ptr&) override {
        return (false);
    }

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease6Ptr&) override {
        return (false);
    }

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress&) const override {
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
    virtual Lease4Collection getLease4(const HWAddr&) const override {
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
    virtual Lease4Ptr getLease4(const HWAddr&, SubnetID) const override {
        return (Lease4Ptr());
    }

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const ClientId&) const override {
        return (Lease4Collection());
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
    virtual Lease4Ptr getLease4(const ClientId&, SubnetID) const override {
        return (Lease4Ptr());
    }

    /// @brief Returns all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(SubnetID) const override {
        return (Lease4Collection());
    }

    /// @brief Returns all IPv4 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(const std::string&) const override {
        return (Lease4Collection());
    }

    /// @brief Returns all IPv4 leases.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4() const override {
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
               const LeasePageSize& /* page_size */) const override {
        return (Lease4Collection());
    }

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(Lease::Type /* not used yet */,
                                const isc::asiolink::IOAddress&) const override {
        return (Lease6Ptr());
    }

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid ignored
    /// @param iaid ignored
    ///
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(Lease::Type /* not used yet */,
                                        const DUID&, uint32_t) const override {
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
                                        const DUID&, uint32_t, SubnetID) const override {
        return (leases6_);
    }

    /// @brief Returns collection of lease for matching DUID
    ///
    /// @param duid ignored
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(const DUID&) const override {
        return (leases6_);
    }

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(SubnetID) const override {
        return (Lease6Collection());
    }

    /// @brief Returns all IPv6 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(const std::string&) const override {
        return (Lease6Collection());
    }

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6() const override {
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
               const LeasePageSize& /* page_size */) const override {
        return (Lease6Collection());
    };

    /// @brief Returns expired DHCPv6 leases.
    ///
    /// This method is not implemented.
    virtual void getExpiredLeases6(Lease6Collection&, const size_t) const override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getExpiredLeases6 is not"
                  " implemented");
    }

    /// @brief Returns expired DHCPv4 leases.
    ///
    /// This method is not implemented.
    virtual void getExpiredLeases4(Lease4Collection&, const size_t) const override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getExpiredLeases4 is not"
                  " implemented");
    }

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr&) override {}

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease6(const Lease6Ptr&) override {}

    /// @brief Deletes an IPv4 lease.
    ///
    /// @param lease IPv4 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    virtual bool deleteLease(const Lease4Ptr&) override {
        return (false);
    }

    /// @brief Deletes an IPv6 lease.
    ///
    /// @param lease IPv6 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    virtual bool deleteLease(const Lease6Ptr&) override {
        return (false);
    }

    /// @brief Deletes all expired and reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::deleteExpiredReclaimedLeases4"
                  " is not implemented");
    }

    /// @brief Deletes all expired and reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::deleteExpiredReclaimedLeases6"
                  " is not implemented");
    }

    /// @brief Pretends to wipe all IPv4 leases from a subnet
    /// @param subnet_id (ignored, but one day may specify the subnet)
    virtual size_t wipeLeases4(const SubnetID&) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::wipeLeases4 not implemented");
    }

    /// @brief Pretends to wipe all IPv4 leases from a subnet
    /// @param subnet_id (ignored, but one day may specify the subnet)
    virtual size_t wipeLeases6(const SubnetID&) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::wipeLeases6 not implemented");
    }

    /// @brief Pretends to check if the IPv4 lease limits set in the given user
    /// context are exceeded.
    virtual std::string
    checkLimits4(isc::data::ConstElementPtr const& /* user_context */) const override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::checkLimits4() not implemented");
    }

    /// @brief Pretends to check if the IPv6 lease limits set in the given user
    /// context are exceeded.
    virtual std::string
    checkLimits6(isc::data::ConstElementPtr const& /* user_context */) const override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::checkLimits6() not implemented");
    }

    /// @brief Pretends to check if JSON support is enabled in the database.
    ///
    /// @return true if there is JSON support, false otherwise
    virtual bool isJsonSupported() const override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::isJsonSupported() not implemented");
    }

    /// @brief Pretends to return the class lease count for a given class and lease type.
    ///
    /// @param client_class client class for which the count is desired
    /// @param ltype type of lease for which the count is desired. Defaults to
    /// Lease::TYPE_V4.
    ///
    /// @return number of leases
    virtual size_t getClassLeaseCount(const ClientClass& /* client_class */,
                              const Lease::Type& /* ltype = Lease::TYPE_V4 */) const override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getClassLeaseCount() not implemented");
    }

    /// @brief Pretends to recount the leases per class for V4 leases.
    virtual void recountClassLeases4() override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::recountClassLeases4() not implemented");
    }

    /// @brief Pretends to recount the leases per class for V6 leases.
    virtual void recountClassLeases6() override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::recountClassLeases6() not implemented");
    }

    /// @brief Pretends to clear the class-lease count map.
    virtual void clearClassLeaseCounts() override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::clearClassLeaseCounts() not implemented");
    }

    /// @brief Import addExtendedInfo6.
    using LeaseMgr::addExtendedInfo6;

    /// @brief Delete lease6 extended info from tables.
    ///
    /// @param addr The address of the lease.
    void
    deleteExtendedInfo6(const IOAddress& addr) override {
        auto relay_id_it = relay_id6_.begin();
        while (relay_id_it != relay_id6_.end()) {
            if ((*relay_id_it)->lease_addr_ == addr) {
                relay_id_it = relay_id6_.erase(relay_id_it);
            } else {
                ++relay_id_it;
            }
        }
        auto remote_id_it = remote_id6_.begin();
        while (remote_id_it != remote_id6_.end()) {
            if ((*remote_id_it)->lease_addr_ == addr) {
                remote_id_it = remote_id6_.erase(remote_id_it);
            } else {
                ++remote_id_it;
            }
        }
    }

    /// @brief Add lease6 extended info into by-relay-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param relay_id The relay id from the relay header options.
    void
    addRelayId6(const IOAddress& lease_addr,
                const vector<uint8_t>& relay_id) override {
        Lease6ExtendedInfoPtr ex_info;
        ex_info.reset(new Lease6ExtendedInfo(lease_addr, relay_id));
        relay_id6_.push_back(ex_info);
    }

    /// @brief Add lease6 extended info into by-remote-id table.
    ///
    /// @param lease_addr The address of the lease.
    void
    addRemoteId6(const IOAddress& lease_addr,
                 const vector<uint8_t>& remote_id) override {
        Lease6ExtendedInfoPtr ex_info;
        ex_info.reset(new Lease6ExtendedInfo(lease_addr, remote_id));
        remote_id6_.push_back(ex_info);
    }

    /// @brief Stub implementation.
    Lease4Collection
    getLeases4ByRelayId(const OptionBuffer& /* relay_id */,
                        const IOAddress& /* lower_bound_address */,
                        const LeasePageSize& /* page_size */,
                        const time_t& /* qry_start_time = 0 */,
                        const time_t& /* qry_end_time = 0 */) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases4ByRelayId not implemented");
    }

    /// @brief Stub implementation.
    Lease4Collection
    getLeases4ByRemoteId(const OptionBuffer& /* remote_id */,
                         const IOAddress& /* lower_bound_address */,
                         const LeasePageSize& /* page_size */,
                         const time_t& /* qry_start_time = 0 */,
                         const time_t& /* qry_end_time = 0 */) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases4ByRemoteId not implemented");
    }

    /// @brief Stub implementation.
    Lease6Collection
    getLeases6ByRelayId(const DUID& /* relay_id */,
                        const IOAddress& /* link_addr */,
                        uint8_t /* link_len */,
                        const IOAddress& /* lower_bound_address */,
                        const LeasePageSize& /* page_size */) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases6ByRelayId not implemented");
    }

    /// @brief Stub implementation.
    Lease6Collection
    getLeases6ByRemoteId(const OptionBuffer& /* remote_id */,
                         const IOAddress& /* link_addr */,
                         uint8_t /* link_len */,
                         const IOAddress& /* lower_bound_address */,
                         const LeasePageSize& /* page_size*/) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases6ByRemoteId not implemented");
    }

    /// @brief Stub implementation.
    Lease6Collection
    getLeases6ByLink(const IOAddress& /* link_addr */,
                     uint8_t /* link_len */,
                     const IOAddress& /* lower_bound_address */,
                     const LeasePageSize& /* page_size */) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases6ByLink not implemented");
    }

    /// @brief Stub implementation.
    virtual size_t buildExtendedInfoTables6(bool /* update */,
                                            bool /* current */) override {
        isc_throw(isc::NotImplemented, "ConcreteLeaseMgr:buildExtendedInfoTables6 not implemented");
    }

    ///  @brief Pretends to write V4 leases to a file.
    virtual void writeLeases4(const std::string&) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::writeLeases4() not implemented");
    }

    ///  @brief Pretends to write V6 leases to a file.
    virtual void writeLeases6(const std::string&) override {
        isc_throw(NotImplemented, "ConcreteLeaseMgr::writeLeases6() not implemented");
    }

    /// @brief Returns backend type.
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const override {
        return (std::string("concrete"));
    }

    /// @brief Returns backend name.
    ///
    /// If the backend is a database, this is the name of the database or the
    /// file.  Otherwise it is just the same as the type.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const override {
        return (std::string("concrete"));
    }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const override {
        return (std::string("This is a dummy concrete backend implementation."));
    }

    /// @brief Returns backend version.
    virtual std::pair<uint32_t, uint32_t> getVersion() const override {
        return (make_pair(uint32_t(0), uint32_t(0)));
    }

    /// @brief Commit transactions
    virtual void commit() override {
    }

    /// @brief Rollback transactions
    virtual void rollback() override {
    }

    // We need to use it in ConcreteLeaseMgr
    using LeaseMgr::getLease6;

    Lease6Collection leases6_; ///< getLease6 methods return this as is

    // List supports easier erase.
    list<Lease6ExtendedInfoPtr> relay_id6_;
    list<Lease6ExtendedInfoPtr> remote_id6_;
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

// Verify Lease4 user context upgrade basic operations.
TEST(Lease4ExtendedInfoTest, basic) {
    Lease4Ptr lease;

    // No Lease.
    ASSERT_FALSE(lease);
    EXPECT_FALSE(LeaseMgr::upgradeLease4ExtendedInfo(lease));

    // No user context.
    lease.reset(new Lease4());
    ASSERT_TRUE(lease);
    ASSERT_FALSE(lease->getContext());
    EXPECT_FALSE(LeaseMgr::upgradeLease4ExtendedInfo(lease));

    // Not map user context.
    ElementPtr user_context = Element::createList();
    lease->setContext(user_context);
    EXPECT_TRUE(LeaseMgr::upgradeLease4ExtendedInfo(lease));
    EXPECT_FALSE(lease->getContext());

    // No ISC.
    user_context = Element::createMap();
    user_context->set("foo", Element::create(string("bar")));
    lease->setContext(user_context);
    EXPECT_FALSE(LeaseMgr::upgradeLease4ExtendedInfo(lease));

    // Not a map ISC.
    user_context = Element::createMap();
    lease->setContext(user_context);
    ElementPtr isc = Element::create(string("..."));
    user_context->set("ISC", isc);
    EXPECT_TRUE(LeaseMgr::upgradeLease4ExtendedInfo(lease));
    EXPECT_FALSE(lease->getContext());

    // No relay agent info.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    isc->set("foo", Element::create(string("bar")));
    EXPECT_FALSE(LeaseMgr::upgradeLease4ExtendedInfo(lease));

    // Not string or map relay agent info.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    ElementPtr rai = Element::createMap();
    rai->set("foo", Element::create(string("bar")));
    isc->set("relay-agent-info", rai);
    EXPECT_FALSE(LeaseMgr::upgradeLease4ExtendedInfo(lease));

    // Positive case.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    rai = Element::create(string("0xAA01BB"));
    isc->set("relay-agent-info", rai);
    EXPECT_TRUE(LeaseMgr::upgradeLease4ExtendedInfo(lease));

    ConstElementPtr new_user_context = lease->getContext();
    ASSERT_TRUE(new_user_context);
    ConstElementPtr new_isc = new_user_context->get("ISC");
    ASSERT_TRUE(new_isc);
    ConstElementPtr new_rai = new_isc->get("relay-agent-info");
    ASSERT_TRUE(new_rai);
    ASSERT_EQ(Element::map, new_rai->getType());
    ASSERT_EQ("{ \"sub-options\": \"0xAA01BB\" }", new_rai->str());
}

// Verify Lease4 user context upgrade complex operations.
TEST(Lease4ExtendedInfoTest, upgradeLease4ExtendedInfo) {
    // Structure that defines a test scenario.
    struct Scenario {
        string description_;  // test description.
        string orig_;         // original user context.
        string expected_;     // expected user context.
    };

    // Test scenarios.
    vector<Scenario> scenarios {
        {
            "no user context",
            "",
            ""
        },
        {
            "user context is not a map",
            "[ ]",
            ""
        },
        {
            "no ISC entry",
            "{ }",
            ""
        },
        {
            "no ISC entry but not empty",
            "{ \"foo\": true }",
            "{ \"foo\": true }"
        },
        {
            "ISC entry is not a map",
            "{ \"ISC\": true }",
            ""
        },
        {
            "ISC entry is not a map, user context not empty",
            "{ \"foo\": true, \"ISC\": true }",
            "{ \"foo\": true }"
        },
        {
            "no relay agent info",
            "{ \"ISC\": { } }",
            ""
        },
        {
            "no relay agent info, ISC not empty",
            "{ \"ISC\": { \"foo\": true } }",
            "{ \"ISC\": { \"foo\": true } }"
        },
        {
            "relay agent info is not a string or a map",
            "{ \"ISC\": { \"relay-agent-info\": false } }",
            ""
        },
        {
            "relay agent info is not a string or a map, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relay-agent-info\": false } }",
            "{ \"ISC\": { \"foo\": true } }"
        },
        {
            "relay agent info has a junk value",
            "{ \"ISC\": { \"relay-agent-info\": \"foobar\" } }",
            ""
        },
        {
            "relay agent info has a junk value, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relay-agent-info\": \"foobar\" } }",
            "{ \"ISC\": { \"foo\": true } }"
        },
        {
            "relay agent info has a rai without ids",
            "{ \"ISC\": { \"relay-agent-info\": \"0x0104AABBCCDD\" } }",
            "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
            " \"0x0104AABBCCDD\" } } }"
        },
        {
            "relay agent info with other entries",
            "{ \"foo\": 123, \"ISC\": { \"bar\": 456,"
            " \"relay-agent-info\": \"0x0104AABBCCDD\" } }",
            "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
            " \"0x0104AABBCCDD\" }, \"bar\": 456 }, \"foo\": 123 }"
        },
        {
            "relay agent info has a rai with ids",
            "{ \"ISC\": { \"relay-agent-info\": \"0x02030102030C03AABBCC\" } }",
            "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
            " \"0x02030102030C03AABBCC\", \"remote-id\": \"010203\","
            " \"relay-id\": \"AABBCC\" } } }"
        }
    };

    Lease4Ptr lease(new Lease4());
    ElementPtr orig_context;
    ElementPtr exp_context;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Create the original user context from JSON.
        if (scenario.orig_.empty()) {
            orig_context.reset();
        } else {
            ASSERT_NO_THROW(orig_context = Element::fromJSON(scenario.orig_))
                << "invalid original context, test " << scenario.description_
                << " is broken";
        }

        // Create the expected user context from JSON.
        if (scenario.expected_.empty()) {
            exp_context.reset();
        } else {
            ASSERT_NO_THROW(exp_context = Element::fromJSON(scenario.expected_))
                << "invalid expected context, test is broken";
        }

        // Perform the test.
        lease->setContext(orig_context);
        ConstElementPtr before;
        if (orig_context) {
            before = isc::data::copy(orig_context);
        }
        bool ret = LeaseMgr::upgradeLease4ExtendedInfo(lease);
        ConstElementPtr after = lease->getContext();
        if (!before && !after) {
            EXPECT_FALSE(ret) << "null before and null after";
        } else if ((before && !after) || (!before && after)) {
            EXPECT_TRUE(ret) << "only one of before and after is null";
        } else if (before->equals(*after)) {
            EXPECT_FALSE(ret) << "before == after";
        } else {
            EXPECT_TRUE(ret) << "before != after";
        }
        if (!exp_context) {
            EXPECT_FALSE(after) << "expected null, got " << *after;
        } else {
            ASSERT_TRUE(after) << "expected not null, got null";
            EXPECT_TRUE(exp_context->equals(*after))
                << "expected: " << *exp_context << std::endl
                << "actual: " << *after << std::endl;
        }
    }
}

// Verify Lease4 user context extract basic operations.
TEST(Lease4ExtendedInfoTest, extract) {
    Lease4Ptr lease;

    // No Lease.
    ASSERT_FALSE(lease);
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease, false));

    // No user context.
    lease.reset(new Lease4());
    ASSERT_TRUE(lease);
    ASSERT_FALSE(lease->getContext());
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease, false));

    // Not map user context.
    ElementPtr user_context = Element::createList();
    lease->setContext(user_context);
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));

    // No ISC.
    user_context = Element::createMap();
    user_context->set("foo", Element::create(string("bar")));
    lease->setContext(user_context);
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease, false));

    // Not a map ISC.
    user_context = Element::createMap();
    lease->setContext(user_context);
    ElementPtr isc = Element::create(string("..."));
    user_context->set("ISC", isc);
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));

    // No relay agent info.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    isc->set("foo", Element::create(string("bar")));
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease, false));

    // Not a map relay agent info.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    ElementPtr rai = Element::createMap();
    rai->set("foo", Element::create(string("bar")));
    isc->set("relay-agent-info", rai);
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));

    // No upgraded.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    rai = Element::create(string("0x02030102030C03AABBCC"));
    isc->set("relay-agent-info", rai);
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));
    EXPECT_TRUE(lease->relay_id_.empty());
    EXPECT_TRUE(lease->remote_id_.empty());

    // Upgraded.
    EXPECT_TRUE(LeaseMgr::upgradeLease4ExtendedInfo(lease));
    EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease, false));
    const vector<uint8_t> relay_id = { 0xaa, 0xbb, 0xcc };
    EXPECT_EQ(relay_id, lease->relay_id_);
    const vector<uint8_t> remote_id = { 1, 2, 3 };
    EXPECT_EQ(remote_id, lease->remote_id_);
}

// Verify Lease4 user context extract complex operations.
TEST(Lease4ExtendedInfoTest, extractLease4ExtendedInfo) {
    struct Scenario {
        string description_;  // test description.
        string context_;      // user context.
        string msg_;          // error message.
    };

    // Test scenarios.
    vector<Scenario> scenarios {
        {
            "no user context",
            "",
            ""
        },
        {
            "user context is not a map",
            "[ ]",
            "user context is not a map"
        },
        {
            "no ISC entry",
            "{ }",
            ""
        },
        {
            "no ISC entry but not empty",
            "{ \"foo\": true }",
            ""
        },
        {
            "ISC entry is not a map",
            "{ \"ISC\": true }",
            "ISC entry is not a map"
        },
        {
            "ISC entry is not a map, user context not empty",
            "{ \"foo\": true, \"ISC\": true }",
            "ISC entry is not a map"
        },
        {
            "no relay agent info",
            "{ \"ISC\": { } }",
            ""
        },
        {
            "no relay agent info, ISC not empty",
            "{ \"ISC\": { \"foo\": true } }",
            ""
        },
        {
            "relay agent info is not a string or a map",
            "{ \"ISC\": { \"relay-agent-info\": false } }",
            "relay-agent-info is not a map"
        },
        {
            "relay agent info is not a string or a map, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relay-agent-info\": false } }",
            "relay-agent-info is not a map"
        },
        {
            "relay agent info has a junk value",
            "{ \"ISC\": { \"relay-agent-info\": \"foobar\" } }",
            "relay-agent-info is not a map"
        },
        {
            "relay agent info has a junk value, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relay-agent-info\": \"foobar\" } }",
            "relay-agent-info is not a map"
        },
        {
            "relay agent info has a rai without ids",
            "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
            " \"0x0104AABBCCDD\" } } }",
            ""
        },
        {
            "relay agent info with other entries",
            "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
            " \"0x0104AABBCCDD\" }, \"bar\": 456 }, \"foo\": 123 }",
            ""
        },
        {
            "relay agent info has a rai with ids",
            "{ \"ISC\": { \"relay-agent-info\": { \"sub-options\":"
            " \"0x02030102030C03AABBCC\", \"remote-id\": \"010203\","
            " \"relay-id\": \"AABBCC\" } } }",
            ""
        }
    };

    Lease4Ptr lease(new Lease4());
    ElementPtr user_context;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Create the original user context from JSON.
        if (scenario.context_.empty()) {
            user_context.reset();
        } else {
            ASSERT_NO_THROW(user_context = Element::fromJSON(scenario.context_))
                << "invalid user context, test " << scenario.description_
                << " is broken";
        }

        // Perform the test.
        lease->setContext(user_context);
        if (scenario.msg_.empty()) {
            EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease, false));
        } else {
            EXPECT_NO_THROW(LeaseMgr::extractLease4ExtendedInfo(lease));
            EXPECT_THROW_MSG(LeaseMgr::extractLease4ExtendedInfo(lease, false),
                             BadValue, scenario.msg_);
        }
    }
    // Last scenario sets relay and remote ids.
    const vector<uint8_t> relay_id = { 0xaa, 0xbb, 0xcc };
    EXPECT_EQ(relay_id, lease->relay_id_);
    const vector<uint8_t> remote_id = { 1, 2, 3 };
    EXPECT_EQ(remote_id, lease->remote_id_);
}

// Verify Lease6 user context upgrade basic operations.
TEST(Lease6ExtendedInfoTest, basic) {
    Lease6Ptr lease;

    // No Lease.
    ASSERT_FALSE(lease);
    EXPECT_FALSE(LeaseMgr::upgradeLease6ExtendedInfo(lease));

    // No user context.
    lease.reset(new Lease6());
    ASSERT_TRUE(lease);
    ASSERT_FALSE(lease->getContext());
    EXPECT_FALSE(LeaseMgr::upgradeLease6ExtendedInfo(lease));

    // Not map user context.
    ElementPtr user_context = Element::createList();
    lease->setContext(user_context);
    EXPECT_TRUE(LeaseMgr::upgradeLease6ExtendedInfo(lease));
    EXPECT_FALSE(lease->getContext());

    // No ISC.
    user_context = Element::createMap();
    user_context->set("foo", Element::create(string("bar")));
    lease->setContext(user_context);
    EXPECT_FALSE(LeaseMgr::upgradeLease6ExtendedInfo(lease));

    // Not map ISC.
    user_context = Element::createMap();
    lease->setContext(user_context);
    ElementPtr isc = Element::create(string("..."));
    user_context->set("ISC", isc);
    EXPECT_TRUE(LeaseMgr::upgradeLease6ExtendedInfo(lease));
    EXPECT_FALSE(lease->getContext());

    // No relays.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    isc->set("foo", Element::create(string("bar")));
    EXPECT_FALSE(LeaseMgr::upgradeLease6ExtendedInfo(lease));

    // Not list relays.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    ElementPtr relays = Element::create(string("foo"));
    isc->set("relays", relays);
    EXPECT_TRUE(LeaseMgr::upgradeLease6ExtendedInfo(lease));
    EXPECT_FALSE(lease->getContext());

    // Empty relays.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    relays = Element::createList();
    isc->set("relays", relays);
    EXPECT_TRUE(LeaseMgr::upgradeLease6ExtendedInfo(lease));
    EXPECT_FALSE(lease->getContext());

    // Not map relay.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    relays = Element::createList();
    isc->set("relays", relays);
    relays->add(Element::create(string("foo")));
    EXPECT_TRUE(LeaseMgr::upgradeLease6ExtendedInfo(lease));
    EXPECT_FALSE(lease->getContext());

    // Positive case.
    user_context = Element::createMap();
    lease->setContext(user_context);
    isc = Element::createMap();
    user_context->set("ISC", isc);
    relays = Element::createList();
    isc->set("relays", relays);
    ElementPtr relay = Element::createMap();
    relays->add(relay);
    relay->set("foo", Element::create(string("bar")));
    EXPECT_TRUE(LeaseMgr::upgradeLease6ExtendedInfo(lease));

    ConstElementPtr new_user_context = lease->getContext();
    ASSERT_TRUE(new_user_context);
    ASSERT_EQ(Element::map, new_user_context->getType());
    ConstElementPtr new_isc = new_user_context->get("ISC");
    ASSERT_TRUE(new_isc);
    ASSERT_EQ(Element::map, new_isc->getType());
    ConstElementPtr relay_info = new_isc->get("relay-info");
    ASSERT_TRUE(relay_info);
    ASSERT_EQ(Element::list, relay_info->getType());
    ASSERT_EQ("[ { \"foo\": \"bar\" } ]", relay_info->str());
}

// Verify Lease6 user context upgrade complex operations.
TEST(Lease6ExtendedInfoTest, upgradeLease6ExtendedInfo) {
    // Structure that defines a test scenario.
    struct Scenario {
        string description_;  // test description.
        string orig_;         // original user context.
        string expected_;     // expected user context.
    };

    // Test scenarios.
    vector<Scenario> scenarios {
        {
            "no user context",
            "",
            ""
        },
        {
            "user context is not a map",
            "[ ]",
            ""
        },
        {
            "no ISC entry",
            "{ }",
            ""
        },
        {
            "no ISC entry but not empty",
            "{ \"foo\": true }",
            "{ \"foo\": true }"
        },
        {
            "ISC entry is not a map",
            "{ \"ISC\": true }",
            ""
        },
        {
            "ISC entry is not a map, user context not empty",
            "{ \"foo\": true, \"ISC\": true }",
            "{ \"foo\": true }"
        },
        {
            "no relays",
            "{ \"ISC\": { } }",
            ""
        },
        {
            "no relays, ISC not empty",
            "{ \"ISC\": { \"foo\": true } }",
            "{ \"ISC\": { \"foo\": true } }"
        },
        {
            "relays is not a list",
            "{ \"ISC\": { \"relays\": { } } }",
            ""
        },
        {
            "relays is not a list, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relays\": { } } }",
            "{ \"ISC\": { \"foo\": true } }"
        },
        {
            "relays is empty",
            "{ \"ISC\": { \"relays\": [ ] } }",
            ""
        },
        {
            "relays is empty, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relays\": [ ] } }",
            "{ \"ISC\": { \"foo\": true } }"
        },
        {
            "relay is not a map",
            "{ \"ISC\": { \"relays\": [ \"foobar\" ] } }",
            ""
        },
        {
            "relay has other values",
            "{ \"ISC\": { \"relays\": [ { \"foo\": \"bar\" } ] } }",
            "{ \"ISC\": { \"relay-info\": [ { \"foo\": \"bar\" } ] } }"
        },
        {
            "one relay with no ids",
            "{ \"ISC\": { \"relays\": [ { \"hop\": 33,"
            " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
            " \"options\": \"0x00C800080102030405060708\" } ] } }",
            "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
            " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
            " \"options\": \"0x00C800080102030405060708\" } ] } }"
        },
        {
            "one relay with remote and relay ids",
            "{ \"ISC\": { \"relays\": [ { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\" } ] } }",
            "{ \"ISC\": { \"relay-info\": [ { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\","
            " \"remote-id\": \"010203040506\","
            " \"relay-id\": \"6464646464646464\" } ] } }"
        },
        {
            "two relays",
            "{ \"ISC\": { \"relays\": [ { \"hop\": 33,"
            " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
            " \"options\": \"0x00C800080102030405060708\" }, { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\" } ] } }",
            "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
            " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
            " \"options\": \"0x00C800080102030405060708\" }, { \"hop\": 100,"
            " \"options\": \"0x00250006010203040506003500086464646464646464\","
            " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\","
            " \"remote-id\": \"010203040506\","
            " \"relay-id\": \"6464646464646464\" } ] } }"
        }
    };

    Lease6Ptr lease(new Lease6());
    ElementPtr orig_context;
    ElementPtr exp_context;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Create the original user context from JSON.
        if (scenario.orig_.empty()) {
            orig_context.reset();
        } else {
            ASSERT_NO_THROW(orig_context = Element::fromJSON(scenario.orig_))
                << "invalid original context, test " << scenario.description_
                << " is broken";
        }

        // Create the expected user context from JSON.
        if (scenario.expected_.empty()) {
            exp_context.reset();
        } else {
            ASSERT_NO_THROW(exp_context = Element::fromJSON(scenario.expected_))
                << "invalid expected context, test is broken";
        }

        // Perform the test.
        lease->setContext(orig_context);
        ConstElementPtr before;
        if (orig_context) {
            before = isc::data::copy(orig_context);
        }
        bool ret = LeaseMgr::upgradeLease6ExtendedInfo(lease);
        ConstElementPtr after = lease->getContext();
        if (!before && !after) {
            EXPECT_FALSE(ret) << "null before and null after";
        } else if ((before && !after) || (!before && after)) {
            EXPECT_TRUE(ret) << "only one of before and after is null";
        } else if (before->equals(*after)) {
            EXPECT_FALSE(ret) << "before == after";
        } else {
            EXPECT_TRUE(ret) << "before != after";
        }
        if (!exp_context) {
            EXPECT_FALSE(after) << "expected null, got " << *after;
        } else {
            ASSERT_TRUE(after) << "expected not null, got null";
            EXPECT_TRUE(exp_context->equals(*after))
                << "expected: " << *exp_context << std::endl
                << "actual: " << *after << std::endl;
        }
    }
}

/// Verify setExtendedInfoTablesEnabled without valid extended info.
TEST(Lease6ExtendedInfoTest, invalidSetExtendedInfoTablesEnabled) {

    DatabaseConnection::ParameterMap pmap;
    boost::scoped_ptr<ConcreteLeaseMgr> mgr(new ConcreteLeaseMgr(pmap));

    // Structure that defines a test scenario.
    struct Scenario {
        string description_;       // test description.
        string user_context_txt_;  // user context.
    };

    // Test scenarios.
    vector<Scenario> scenarios {
        {
            "no user context",
            ""
        },
        {
            "user context is not a map",
            "[ ]"
        },
        {
            "no ISC entry",
            "{ }"
        },
        {
            "no ISC entry but not empty",
            "{ \"foo\": true }"
        },
        {
            "ISC entry is not a map",
            "{ \"ISC\": true }"
        },
        {
            "ISC entry is not a map, user context not empty",
            "{ \"foo\": true, \"ISC\": true }"
        },
        {
            "no relay-info",
            "{ \"ISC\": { } }"
        },
        {
            "no relay-info, ISC not empty",
            "{ \"ISC\": { \"foo\": true } }"
        },
        {
            "relay-info is not a list",
            "{ \"ISC\": { \"relay-info\": { } } }"
        },
        {
            "relay-info is not a list, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relay-info\": { } } }"
        },
        {
            "relay-info is empty",
            "{ \"ISC\": { \"relay-info\": [ ] } }"
        },
        {
            "relay-info is empty, ISC not empty",
            "{ \"ISC\": { \"foo\": true, \"relay-info\": [ ] } }"
        },
        {
            "relay is not a map",
            "{ \"ISC\": { \"relay-info\": [ \"foobar\" ] } }"
        },
        {
            "relay has other values",
            "{ \"ISC\": { \"relay-info\": [ { \"foo\": \"bar\" } ] } }"
        }
    };

    Lease6Ptr lease(new Lease6());
    ElementPtr user_context;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Create the user context from JSON.
        if (scenario.user_context_txt_.empty()) {
            user_context.reset();
        } else {
            ASSERT_NO_THROW(user_context = Element::fromJSON(scenario.user_context_txt_))
                << "invalid user context, test " << scenario.description_
                << " is broken";
        }

        // Perform the test.
        lease->setContext(user_context);
        mgr->relay_id6_.clear();
        mgr->remote_id6_.clear();
        EXPECT_NO_THROW(mgr->addExtendedInfo6(lease));
        EXPECT_TRUE(mgr->relay_id6_.empty());
        EXPECT_TRUE(mgr->remote_id6_.empty());
    }
}

/// Verify setExtendedInfoTablesEnabled with one relay without ids.
TEST(Lease6ExtendedInfoTest, noIdSetExtendedInfoTablesEnabled) {

    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
        " \"options\": \"0x00C800080102030405060708\" } ] } }";

    DatabaseConnection::ParameterMap pmap;
    boost::scoped_ptr<ConcreteLeaseMgr> mgr(new ConcreteLeaseMgr(pmap));

    Lease6Ptr lease(new Lease6());
    lease->addr_ = IOAddress("2001:db8::100");
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);
    EXPECT_NO_THROW(mgr->addExtendedInfo6(lease));
    EXPECT_TRUE(mgr->relay_id6_.empty());
    EXPECT_TRUE(mgr->remote_id6_.empty());
}

/// Verify setExtendedInfoTablesEnabled with one relay with ids.
TEST(Lease6ExtendedInfoTest, idsSetExtendedInfoTablesEnabled) {

    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 100,"
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";

    DatabaseConnection::ParameterMap pmap;
    boost::scoped_ptr<ConcreteLeaseMgr> mgr(new ConcreteLeaseMgr(pmap));

    Lease6Ptr lease(new Lease6());
    lease->addr_ = IOAddress("2001:db8::100");
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);
    EXPECT_NO_THROW(mgr->addExtendedInfo6(lease));

    EXPECT_EQ(1, mgr->relay_id6_.size());
    Lease6ExtendedInfoPtr ex_info = mgr->relay_id6_.front();
    ASSERT_TRUE(ex_info);
    EXPECT_EQ("2001:db8::100", ex_info->lease_addr_.toText());
    const vector<uint8_t>& relay_id = ex_info->id_;
    const vector<uint8_t>& exp_relay_id = vector<uint8_t>(8, 0x64);
    EXPECT_EQ(exp_relay_id, relay_id);

    EXPECT_EQ(1, mgr->remote_id6_.size());
    ex_info = mgr->remote_id6_.front();
    ASSERT_TRUE(ex_info);
    EXPECT_EQ("2001:db8::100", ex_info->lease_addr_.toText());
    const vector<uint8_t>& remote_id = ex_info->id_;
    const vector<uint8_t>& exp_remote_id = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(exp_remote_id, remote_id);
}

/// Verify setExtendedInfoTablesEnabled with one relay with ids but
/// :: link address.
TEST(Lease6ExtendedInfoTest, linkZeroSetExtendedInfoTablesEnabled) {

    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 100,"
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"link\": \"::\", \"peer\": \"2001:db8::6\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";

    DatabaseConnection::ParameterMap pmap;
    boost::scoped_ptr<ConcreteLeaseMgr> mgr(new ConcreteLeaseMgr(pmap));

    Lease6Ptr lease(new Lease6());
    lease->addr_ = IOAddress("2001:db8::100");
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);
    EXPECT_NO_THROW(mgr->addExtendedInfo6(lease));

    EXPECT_EQ(1, mgr->relay_id6_.size());
    Lease6ExtendedInfoPtr ex_info = mgr->relay_id6_.front();
    ASSERT_TRUE(ex_info);
    EXPECT_EQ("2001:db8::100", ex_info->lease_addr_.toText());
    const vector<uint8_t>& relay_id = ex_info->id_;
    const vector<uint8_t>& exp_relay_id = vector<uint8_t>(8, 0x64);
    EXPECT_EQ(exp_relay_id, relay_id);

    EXPECT_EQ(1, mgr->remote_id6_.size());
    ex_info = mgr->remote_id6_.front();
    ASSERT_TRUE(ex_info);
    EXPECT_EQ("2001:db8::100", ex_info->lease_addr_.toText());
    const vector<uint8_t>& remote_id = ex_info->id_;
    const vector<uint8_t>& exp_remote_id = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(exp_remote_id, remote_id);
}

/// Verify setExtendedInfoTablesEnabled with two relays.
TEST(Lease6ExtendedInfoTest, twoSetExtendedInfoTablesEnabled) {

    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\","
        " \"options\": \"0x00C800080102030405060708\" }, { \"hop\": 100,"
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";

    DatabaseConnection::ParameterMap pmap;
    boost::scoped_ptr<ConcreteLeaseMgr> mgr(new ConcreteLeaseMgr(pmap));

    Lease6Ptr lease(new Lease6());
    lease->addr_ = IOAddress("2001:db8::100");
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);
    EXPECT_NO_THROW(mgr->addExtendedInfo6(lease));

    EXPECT_EQ(1, mgr->relay_id6_.size());
    Lease6ExtendedInfoPtr ex_info = mgr->relay_id6_.front();
    ASSERT_TRUE(ex_info);
    EXPECT_EQ("2001:db8::100", ex_info->lease_addr_.toText());
    const vector<uint8_t>& relay_id = ex_info->id_;
    const vector<uint8_t>& exp_relay_id = vector<uint8_t>(8, 0x64);
    EXPECT_EQ(exp_relay_id, relay_id);

    EXPECT_EQ(1, mgr->remote_id6_.size());
    ex_info = mgr->remote_id6_.front();
    ASSERT_TRUE(ex_info);
    EXPECT_EQ("2001:db8::100", ex_info->lease_addr_.toText());
    const vector<uint8_t>& remote_id = ex_info->id_;
    const vector<uint8_t>& exp_remote_id = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(exp_remote_id, remote_id);
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call ConcreteLeaseMgr methods.
// Those methods are just stubs that do not return anything.

}  // namespace
