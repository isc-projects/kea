// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_CONCRETE_LEASE_MGR_H
#define TEST_CONCRETE_LEASE_MGR_H

#include <config.h>

#include <database/database_connection.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <dhcpsrv/tracking_lease_mgr.h>
#include <list>
#include <utility>

namespace isc {
namespace dhcp {
namespace test {

// This is a concrete implementation of a Lease database.  It does not do
// anything useful and is used for abstract LeaseMgr class testing.
class ConcreteLeaseMgr : public TrackingLeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ConcreteLeaseMgr(const db::DatabaseConnection::ParameterMap&);

    /// @brief Destructor
    virtual ~ConcreteLeaseMgr();

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease4Ptr&) override;

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease6Ptr&) override;

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress&) const override;

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
    virtual Lease4Collection getLease4(const HWAddr&) const override;

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
    virtual Lease4Ptr getLease4(const HWAddr&, SubnetID) const override;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const ClientId&) const override;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId&, SubnetID) const override;

    /// @brief Returns all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(SubnetID) const override;

    /// @brief Returns all IPv4 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(const std::string&) const override;

    /// @brief Returns all IPv4 leases.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4() const override;

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
               const LeasePageSize& /* page_size */) const override;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(Lease::Type /* not used yet */,
                                const isc::asiolink::IOAddress&) const override;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid ignored
    /// @param iaid ignored
    ///
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(Lease::Type /* not used yet */,
                                        const DUID&, uint32_t) const override;

    /// @brief Returns existing IPv6 lease for a given DUID+IA+subnet-id combination
    ///
    /// @param duid ignored
    /// @param iaid ignored
    /// @param subnet_id ignored
    ///
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(Lease::Type /* not used yet */,
                                        const DUID&, uint32_t, SubnetID) const override;

    /// @brief Returns collection of lease for matching DUID
    ///
    /// @param duid ignored
    /// @return whatever is set in leases6_ field
    virtual Lease6Collection getLeases6(const DUID&) const override;

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(SubnetID) const override;

    /// @brief Returns all IPv6 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(const std::string&) const override;

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6() const override;

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
               const LeasePageSize& /* page_size */) const override;

    /// @brief Returns expired DHCPv6 leases.
    ///
    /// This method is not implemented.
    virtual void getExpiredLeases6(Lease6Collection&, const size_t) const override;

    /// @brief Returns expired DHCPv4 leases.
    ///
    /// This method is not implemented.
    virtual void getExpiredLeases4(Lease4Collection&, const size_t) const override;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr&) override;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease6(const Lease6Ptr&) override;

    /// @brief Deletes an IPv4 lease.
    ///
    /// @param lease IPv4 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    virtual bool deleteLease(const Lease4Ptr&) override;

    /// @brief Deletes an IPv6 lease.
    ///
    /// @param lease IPv6 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    virtual bool deleteLease(const Lease6Ptr&) override;

    /// @brief Deletes all expired and reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t) override;

    /// @brief Deletes all expired and reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t) override;

    /// @brief Pretends to wipe all IPv4 leases from a subnet
    /// @param subnet_id (ignored, but one day may specify the subnet)
    virtual size_t wipeLeases4(const SubnetID&) override;

    /// @brief Pretends to wipe all IPv4 leases from a subnet
    /// @param subnet_id (ignored, but one day may specify the subnet)
    virtual size_t wipeLeases6(const SubnetID&) override;

    /// @brief Pretends to check if the IPv4 lease limits set in the given user
    /// context are exceeded.
    virtual std::string
    checkLimits4(isc::data::ConstElementPtr const& /* user_context */) const override;

    /// @brief Pretends to check if the IPv6 lease limits set in the given user
    /// context are exceeded.
    virtual std::string
    checkLimits6(isc::data::ConstElementPtr const& /* user_context */) const override;

    /// @brief Pretends to check if JSON support is enabled in the database.
    ///
    /// @return true if there is JSON support, false otherwise
    virtual bool isJsonSupported() const override;

    /// @brief Pretends to return the class lease count for a given class and lease type.
    ///
    /// @param client_class client class for which the count is desired
    /// @param ltype type of lease for which the count is desired. Defaults to
    /// Lease::TYPE_V4.
    ///
    /// @return number of leases
    virtual size_t getClassLeaseCount(const ClientClass& /* client_class */,
                              const Lease::Type& /* ltype = Lease::TYPE_V4 */) const override;

    /// @brief Pretends to recount the leases per class for V4 leases.
    virtual void recountClassLeases4() override;

    /// @brief Pretends to recount the leases per class for V6 leases.
    virtual void recountClassLeases6() override;

    /// @brief Pretends to clear the class-lease count map.
    virtual void clearClassLeaseCounts() override;

    /// @brief Import addExtendedInfo6.
    using LeaseMgr::addExtendedInfo6;

    /// @brief Delete lease6 extended info from tables.
    ///
    /// @param addr The address of the lease.
    void
    deleteExtendedInfo6(const asiolink::IOAddress& addr) override;

    /// @brief Add lease6 extended info into by-relay-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param relay_id The relay id from the relay header options.
    void
    addRelayId6(const asiolink::IOAddress& lease_addr,
                const std::vector<uint8_t>& relay_id) override;

    /// @brief Add lease6 extended info into by-remote-id table.
    ///
    /// @param lease_addr The address of the lease.
    void
    addRemoteId6(const asiolink::IOAddress& lease_addr,
                 const std::vector<uint8_t>& remote_id) override;

    /// @brief Stub implementation.
    Lease4Collection
    getLeases4ByRelayId(const OptionBuffer& /* relay_id */,
                        const asiolink::IOAddress& /* lower_bound_address */,
                        const LeasePageSize& /* page_size */,
                        const time_t& /* qry_start_time = 0 */,
                        const time_t& /* qry_end_time = 0 */) override;

    /// @brief Stub implementation.
    Lease4Collection
    getLeases4ByRemoteId(const OptionBuffer& /* remote_id */,
                         const asiolink::IOAddress& /* lower_bound_address */,
                         const LeasePageSize& /* page_size */,
                         const time_t& /* qry_start_time = 0 */,
                         const time_t& /* qry_end_time = 0 */) override;

    /// @brief Stub implementation.
    Lease6Collection
    getLeases6ByRelayId(const DUID& /* relay_id */,
                        const asiolink::IOAddress& /* link_addr */,
                        uint8_t /* link_len */,
                        const asiolink::IOAddress& /* lower_bound_address */,
                        const LeasePageSize& /* page_size */) override;

    /// @brief Stub implementation.
    Lease6Collection
    getLeases6ByRemoteId(const OptionBuffer& /* remote_id */,
                         const asiolink::IOAddress& /* link_addr */,
                         uint8_t /* link_len */,
                         const asiolink::IOAddress& /* lower_bound_address */,
                         const LeasePageSize& /* page_size*/) override;

    /// @brief Stub implementation.
    Lease6Collection
    getLeases6ByLink(const asiolink::IOAddress& /* link_addr */,
                     uint8_t /* link_len */,
                     const asiolink::IOAddress& /* lower_bound_address */,
                     const LeasePageSize& /* page_size */) override;

    /// @brief Stub implementation.
    virtual size_t buildExtendedInfoTables6(bool /* update */,
                                            bool /* current */) override;

    ///  @brief Pretends to write V4 leases to a file.
    virtual void writeLeases4(const std::string&) override;

    ///  @brief Pretends to write V6 leases to a file.
    virtual void writeLeases6(const std::string&) override;

    /// @brief Returns backend type.
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const override;

    /// @brief Returns backend name.
    ///
    /// If the backend is a database, this is the name of the database or the
    /// file.  Otherwise it is just the same as the type.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const override;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const override;

    /// @brief Returns backend version.
    virtual std::pair<uint32_t, uint32_t> getVersion() const override;

    /// @brief Commit transactions
    virtual void commit() override;

    /// @brief Rollback transactions
    virtual void rollback() override;

    // We need to use them in ConcreteLeaseMgr
    using LeaseMgr::getLease6;
    using TrackingLeaseMgr::tryLock;
    using TrackingLeaseMgr::unlock;
    using TrackingLeaseMgr::trackAddLease;
    using TrackingLeaseMgr::trackUpdateLease;
    using TrackingLeaseMgr::trackDeleteLease;
    using TrackingLeaseMgr::hasCallbacks;
    using TrackingLeaseMgr::callbackTypeToString;

    Lease6Collection leases6_; ///< getLease6 methods return this as is

    // List supports easier erase.
    std::list<Lease6ExtendedInfoPtr> relay_id6_;
    std::list<Lease6ExtendedInfoPtr> remote_id6_;
};


} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif // TEST_CONCRETE_LEASE_MGR_H
