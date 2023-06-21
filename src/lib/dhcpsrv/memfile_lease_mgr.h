// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MEMFILE_LEASE_MGR_H
#define MEMFILE_LEASE_MGR_H

#include <asiolink/interval_timer.h>
#include <asiolink/process_spawn.h>
#include <database/database_connection.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/memfile_lease_limits.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <dhcpsrv/tracking_lease_mgr.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <mutex>

namespace isc {
namespace dhcp {

class LFCSetup;

/// @brief Concrete implementation of a lease database backend using flat file.
///
/// This class implements a lease database backend using CSV files to store
/// DHCPv4 and DHCPv6 leases on disk. The format of the files is determined
/// by the @c CSVLeaseFile4 and @c CSVLeaseFile6 classes.
///
/// In order to obtain good performance, the backend stores leases
/// incrementally, i.e. updates to leases are appended at the end of the lease
/// file. To record the deletion of a lease, the lease record is appended to
/// the lease file with the valid lifetime set to 0. However, this may result
/// in a significant growth of the lease file size over time, because the lease
/// file will contain many entries for each lease. In order to mitigate this
/// problem, the backend implements the Lease File Cleanup mechanism which is
/// described on the Kea wiki:
/// https://gitlab.isc.org/isc-projects/kea/wikis/designs/Lease-File-Cleanup-design.
///
/// The backend installs an @c asiolink::IntervalTimer to periodically execute
/// the @c Memfile_LeaseMgr::lfcCallback. This callback function controls
/// the startup of the background process which removes redundant information
/// from the lease file(s).
///
/// When the backend is starting up, it reads leases from the lease file (one
/// by one) and adds them to the in-memory container as follows:
/// - if the lease record being parsed identifies a lease which is not present
/// in the container, and the lease has valid lifetime greater than 0,
/// the lease is added to the container,
/// - if the lease record being parsed identifies a lease which is present in
/// the container, and the valid lifetime of the lease record being parsed is
/// greater than 0, the lease in the container is updated
/// - if the lease record being parsed has valid lifetime equal to 0, and the
/// corresponding lease exists in the container, the lease is removed from
/// the container.
///
/// After the container holding leases is initialized, each subsequent update,
/// removal or addition of the lease is appended to the lease file
/// synchronously.
///
/// Originally, the Memfile backend didn't write leases to disk. This was
/// particularly useful for testing server performance in non-disk bound
/// conditions. In order to preserve this capability, the new parameter
/// "persist=true|false" has been introduced in the database access string.
/// For example, database access string: "type=memfile persist=true"
/// enables writes of leases to a disk.
///
/// The lease file locations can be specified with the "name=[path]"
/// parameter in the database access string. The [path] is the
/// absolute path to the file (including file name). If this parameter
/// is not specified, the default location in the installation
/// directory is used: <install-dir>/var/lib/kea/kea-leases4.csv and
/// <install-dir>/var/lib/kea/kea-leases6.csv.
class Memfile_LeaseMgr : public TrackingLeaseMgr {
public:

    /// @defgroup v4 memfile backend versions
    ///
    /// Version history:
    /// 1.0 - initial version (released in Kea 0.9)
    /// 2.0 - hwaddr column added (released in Kea 0.9.1)
    /// 2.1 - user context column added (released in Kea 1.4.0)
    /// 3.0 - pool_id column added (released in Kea 2.3.8)
    ///
    /// @{
    /// @brief the major version of the v4 memfile backend
    static const int MAJOR_VERSION_V4 = 3;

    /// @brief the minor version of the v4 memfile backend
    static const int MINOR_VERSION_V4 = 0;
    /// @}

    /// @defgroup v6 memfile backend versions
    ///
    /// Version history:
    /// 1.0 - initial version (released in Kea 0.9)
    /// 2.0 - hwaddr column added (released in Kea 0.9.1)
    /// 3.0 - state column added (released in Kea 0.9.2)
    /// 3.1 - user context column added (released in Kea 1.4.0)
    /// 4.0 - hwtype,hwaddr_source columns added (released in Kea 2.1.2)
    /// 5.0 - pool_id column added (released in Kea 2.3.8)
    ///
    /// @{
    /// @brief the major version of the v6 memfile backend
    static const int MAJOR_VERSION_V6 = 5;

    /// @brief the minor version of the v6 memfile backend
    static const int MINOR_VERSION_V6 = 0;
    /// @}


    /// @brief Specifies universe (V4, V6)
    ///
    /// This enumeration is used by various functions in Memfile %Lease Manager,
    /// to identify the lease type referred to. In particular, it is used by
    /// functions operating on the lease files to distinguish between lease
    /// files for DHCPv4 and DHCPv6.
    enum Universe {
        V4,
        V6
    };

    /// @name Methods implementing the API of the lease database backend.
    ///       The following methods are implementing the API of the
    ///       @c LeaseMgr to manage leases.
    //@{

    /// @brief The sole lease manager constructor
    ///
    /// This method:
    /// - Initializes the new instance based on the parameters given
    /// - Loads (or creates) the appropriate lease file(s)
    /// - Initiates the periodic scheduling of the LFC (if enabled)
    ///
    /// If any of the files loaded require conversion to the current schema
    /// (upgrade or downgrade), @c lfcSetup() will be invoked with its
    /// @c run_once_now parameter set to true.  This causes lfcSetup() to
    /// invoke the LFC process immediately regardless of whether LFC is
    /// enabled. This ensures that any files which need conversion are
    /// converted automatically.
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    Memfile_LeaseMgr(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor (closes file)
    virtual ~Memfile_LeaseMgr();

    /// @brief Local version of getDBVersion() class method
    static std::string getDBVersion(Universe const& u);

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not
    virtual bool addLease(const Lease4Ptr& lease) override;

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not
    virtual bool addLease(const Lease6Ptr& lease) override;

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// @param addr An address of the searched lease.
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const override;

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
    virtual Lease4Collection getLease4(const isc::dhcp::HWAddr& hwaddr) const override;

    /// @brief Returns existing IPv4 lease for specified hardware address
    ///        and a subnet
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const HWAddr& hwaddr,
                                SubnetID subnet_id) const override;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param client_id client identifier
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const ClientId& client_id) const override;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const override;

    /// @brief Returns all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(SubnetID subnet_id) const override;

    /// @brief Returns all IPv4 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(const std::string& hostname) const override;

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
    getLeases4(const asiolink::IOAddress& lower_bound_address,
               const LeasePageSize& page_size) const override;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param addr An address of the searched lease.
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(Lease::Type type,
                                const isc::asiolink::IOAddress& addr) const override;

    /// @brief Returns existing IPv6 lease for a given DUID + IA + lease type
    /// combination
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection getLeases6(Lease::Type type,
                                        const DUID& duid,
                                        uint32_t iaid) const override;

    /// @brief Returns existing IPv6 lease for a given DUID + IA + subnet-id +
    /// lease type combination.
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id identifier of the subnet the lease must belong to
    ///
    /// @return lease collection (may be empty if no lease is found)
    virtual Lease6Collection getLeases6(Lease::Type type,
                                        const DUID& duid,
                                        uint32_t iaid,
                                        SubnetID subnet_id) const override;

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(SubnetID subnet_id) const override;

    /// @brief Returns all IPv6 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(const std::string& hostname) const override;

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6() const override;

    /// @brief Returns IPv6 leases for the DUID.
    ///
    /// @param duid client DUID
    virtual Lease6Collection getLeases6(const DUID& duid) const override;

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
    /// @param lower_bound_address IPv6 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection
    getLeases6(const asiolink::IOAddress& lower_bound_address,
               const LeasePageSize& page_size) const override;

    /// @brief Returns a collection of expired DHCPv4 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases4(Lease4Collection& expired_leases,
                                   const size_t max_leases) const override;

    /// @brief Returns a collection of expired DHCPv6 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases6(Lease6Collection& expired_leases,
                                   const size_t max_leases) const override;

    /// @brief Updates IPv4 lease.
    ///
    /// @warning This function does not validate the pointer to the lease.
    /// It is caller's responsibility to pass the valid pointer.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// @throw NoSuchLease if there is no such lease to be updated.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the update
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and UPDATE with different expiration time.
    virtual void updateLease4(const Lease4Ptr& lease4) override;

    /// @brief Updates IPv6 lease.
    ///
    /// @warning This function does not validate the pointer to the lease.
    /// It is caller's responsibility to pass the valid pointer.
    ///
    /// @param lease6 The lease to be updated.
    ///
    /// @throw NoSuchLease if there is no such lease to be updated.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the update
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and UPDATE with different expiration time.
    virtual void updateLease6(const Lease6Ptr& lease6) override;

    /// @brief Deletes an IPv4 lease.
    ///
    /// @param lease IPv4 lease being deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the deletion
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and DELETE with different expiration time.
    virtual bool deleteLease(const Lease4Ptr& lease) override;

    /// @brief Deletes an IPv6 lease.
    ///
    /// @param lease IPv6 lease being deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the deletion
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and DELETE with different expiration time.
    virtual bool deleteLease(const Lease6Ptr& lease) override;

    /// @brief Deletes all expired-reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t secs) override;

    /// @brief Deletes all expired-reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t secs) override;

    /// @brief Removes specified IPv4 leases.
    ///
    /// This rather dangerous method is able to remove all leases from specified
    /// subnet.
    ///
    /// @param subnet_id identifier of the subnet
    ///
    /// @return number of leases removed.
    virtual size_t wipeLeases4(const SubnetID& subnet_id) override;

    /// @brief Removed specified IPv6 leases.
    ///
    /// This rather dangerous method is able to remove all leases from specified
    /// subnet.
    ///
    /// @param subnet_id identifier of the subnet
    ///
    /// @return number of leases removed.
    virtual size_t wipeLeases6(const SubnetID& subnet_id) override;

    /// @brief Checks if the IPv4 lease limits set in the given user context are exceeded.
    /// Memfile implementation.
    ///
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    virtual std::string
    checkLimits4(isc::data::ConstElementPtr const& user_context) const override;

    /// @brief Checks if the IPv6 lease limits set in the given user context are exceeded.
    /// Memfile implementation.
    ///
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2, "prefix-limit": 1 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2, "prefix-limit": 1 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    virtual std::string
    checkLimits6(isc::data::ConstElementPtr const& user_context) const override;

    /// @brief Checks if JSON support is enabled in the database.
    /// Memfile implementation assumes JSON support is always enabled.
    ///
    /// @return true if there is JSON support, false otherwise
    virtual bool isJsonSupported() const override;

private:

    /// @name Internal methods called while holding the mutex in multi threading
    /// mode.
    ///@{

    /// @brief Adds an IPv4 lease,
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not
    bool addLeaseInternal(const Lease4Ptr& lease);

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not
    bool addLeaseInternal(const Lease6Ptr& lease);

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr An address of the searched lease.
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    Lease4Ptr getLease4Internal(const isc::asiolink::IOAddress& addr) const;

    /// @brief Gets existing IPv4 leases for specified hardware address.
    ///
    /// @param hwaddr hardware address of the client
    /// @param collection lease collection
    void getLease4Internal(const isc::dhcp::HWAddr& hwaddr,
                           Lease4Collection& collection) const;

    /// @brief Returns existing IPv4 lease for specified hardware address
    ///        and a subnet
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    Lease4Ptr getLease4Internal(const HWAddr& hwaddr,
                                SubnetID subnet_id) const;

    /// @brief Gets existing IPv4 lease for specified client-id
    ///
    /// @param client_id client identifier
    /// @param collection lease collection
    void getLease4Internal(const ClientId& client_id,
                           Lease4Collection& collection) const;

    /// @brief Returns IPv4 lease for specified client-id/hwaddr/subnet-id tuple
    ///
    /// @param clientid client identifier
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    Lease4Ptr getLease4Internal(const ClientId& clientid,
                                const HWAddr& hwaddr,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    Lease4Ptr getLease4Internal(const ClientId& clientid,
                                SubnetID subnet_id) const;

    /// @brief Gets all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    /// @param collection lease collection
    void getLeases4Internal(SubnetID subnet_id,
                            Lease4Collection& collection) const;

    /// @brief Returns all IPv4 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    /// @param collection lease collection
    void getLeases4Internal(const std::string& hostname,
                            Lease4Collection& collection) const;

    /// @brief Gets all IPv4 leases.
    ///
    /// @param collection lease collection
    void getLeases4Internal(Lease4Collection& collection) const;

    /// @brief Returns range of IPv4 leases using paging.
    ///
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param collection lease collection
    void getLeases4Internal(const asiolink::IOAddress& lower_bound_address,
                            const LeasePageSize& page_size,
                            Lease4Collection& collection) const;

    /// @brief Returns existing IPv6 lease for a given IPv6 address and type.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param addr An address of the searched lease.
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    Lease6Ptr getLease6Internal(Lease::Type type,
                                const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv6 lease of any type for a given IPv6 address.
    ///
    /// @param addr An address of the searched lease.
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    Lease6Ptr getAnyLease6Internal(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv6 lease for a given DUID + IA + lease type
    /// combination
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param collection lease collection
    void getLeases6Internal(Lease::Type type,
                            const DUID& duid,
                            uint32_t iaid,
                            Lease6Collection& collection) const;

    /// @brief Returns existing IPv6 lease for a given DUID + IA + subnet-id +
    /// lease type combination.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id identifier of the subnet the lease must belong to
    /// @param collection lease collection
    void getLeases6Internal(Lease::Type type,
                            const DUID& duid,
                            uint32_t iaid,
                            SubnetID subnet_id,
                            Lease6Collection& collection) const;

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    /// @param collection lease collection
    void getLeases6Internal(SubnetID subnet_id,
                            Lease6Collection& collection) const;

    /// @brief Returns all IPv6 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    /// @param collection lease collection
    void getLeases6Internal(const std::string& hostname,
                            Lease6Collection& collection) const;

    /// @brief Returns all IPv6 leases.
    ///
    /// @param collection lease collection
    void getLeases6Internal(Lease6Collection& collection) const;

    /// @brief Returns IPv6 leases for the DUID.
    ///
    /// @param duid client DUID
    /// @param collection lease collection
    void getLeases6Internal(const DUID& duid,
                            Lease6Collection& collection) const;

    /// @brief Returns range of IPv6 leases using paging.
    ///
    /// @param lower_bound_address IPv6 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param collection lease collection
    void getLeases6Internal(const asiolink::IOAddress& lower_bound_address,
                            const LeasePageSize& page_size,
                            Lease6Collection& collection) const;

    /// @brief Returns a collection of expired DHCPv4 leases.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    void getExpiredLeases4Internal(Lease4Collection& expired_leases,
                                   const size_t max_leases) const;

    /// @brief Returns a collection of expired DHCPv6 leases.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    void getExpiredLeases6Internal(Lease6Collection& expired_leases,
                                   const size_t max_leases) const;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// @throw NoSuchLease if there is no such lease to be updated.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the update
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and UPDATE with different expiration time.
    void updateLease4Internal(const Lease4Ptr& lease4);

    /// @brief Updates IPv6 lease.
    ///
    /// @param lease6 The lease to be updated.
    ///
    /// @throw NoSuchLease if there is no such lease to be updated.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the update
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and UPDATE with different expiration time.
    void updateLease6Internal(const Lease6Ptr& lease6);

    /// @brief Deletes an IPv4 lease.
    ///
    /// @param lease IPv4 lease being deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the deletion
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and DELETE with different expiration time.
    bool deleteLeaseInternal(const Lease4Ptr& addr);

    /// @brief Deletes an IPv6 lease.
    ///
    /// @param lease IPv6 lease being deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note For test purposes only, when persistence is disabled, the deletion
    /// of the lease is performed only if the value matches the one received on
    /// the SELECT query, effectively enforcing no update on the lease between
    /// SELECT and DELETE with different expiration time.
    bool deleteLeaseInternal(const Lease6Ptr& addr);

    /// @brief Removes specified IPv4 leases.
    ///
    /// @param subnet_id identifier of the subnet
    ///
    /// @return The number of deleted leases
    size_t wipeLeases4Internal(const SubnetID& subnet_id);

    /// @brief Removed specified IPv6 leases.
    ///
    /// @param subnet_id identifier of the subnet
    ///
    /// @return The number of deleted leases
    size_t wipeLeases6Internal(const SubnetID& subnet_id);
    ///@}

    /// @brief Deletes all expired-reclaimed leases.
    ///
    /// This private method is called by both of the public methods:
    /// @c deleteExpiredReclaimedLeases4 and
    /// @c deleteExpiredReclaimedLeases6 to remove all expired
    /// reclaimed DHCPv4 or DHCPv6 leases respectively.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    /// @param universe V4 or V6.
    /// @param storage Reference to the container where leases are held.
    /// Some expired-reclaimed leases will be removed from this container.
    /// @param lease_file Reference to a DHCPv4 or DHCPv6 lease file
    /// instance where leases should be marked as deleted.
    ///
    /// @return Number of leases deleted.
    ///
    /// @tparam IndexType Index type to be used to search for the
    /// expired-reclaimed leases, i.e.
    /// @c Lease4StorageExpirationIndex or @c Lease6StorageExpirationIndex.
    /// @tparam LeaseType Lease type, i.e. @c Lease4 or @c Lease6.
    /// @tparam StorageType Type of storage where leases are held, i.e.
    /// @c Lease4Storage or @c Lease6Storage.
    /// @tparam LeaseFileType Type of the lease file, i.e. DHCPv4 or
    /// DHCPv6 lease file type.
    template<typename IndexType, typename LeaseType, typename StorageType,
             typename LeaseFileType>
    uint64_t deleteExpiredReclaimedLeases(const uint32_t secs,
                                          const Universe& universe,
                                          StorageType& storage,
                                          LeaseFileType& lease_file);

    /// @brief Fetches the most recent value for a subnet statistic
    ///
    /// @param subnet_id subnet id of the subnet for which the stat is desired
    /// @param stat_label name of the statistic desired (e.g. "assigned-addresses")
    ///
    /// @return Value of the statistic or zero if there are no entries found.
    int64_t getSubnetStat(const SubnetID& subnet_id, const std::string& stat_label) const;

    /// @brief Fetches the integer value of lease limit element from a parent element based
    /// on Lease::Type.
    ///
    /// @param parent parent element (e.g. "client-class" or "subnet") in which to look for
    /// the limit
    /// @param ltype Lease::Type of the limit for which to look (one of Lease::TYPE_V4,
    /// Lease::TYPE_NA, or Lease::TYPE_PD)
    /// @param[out] limit contains the value of the limit if found
    ///
    /// @return bool true if a limit for the lease type was found, false otherwise.
    bool getLeaseLimit(data::ConstElementPtr parent, Lease::Type ltype, size_t& limit) const;

public:

    /// @brief Return backend type
    ///
    /// Returns the type of the backend.
    ///
    /// @return Type of the backend.
    virtual std::string getType() const override {
        return (std::string("memfile"));
    }

    /// @brief Returns backend name.
    ///
    /// For now, memfile can only store data in memory.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const override {
        return ("memory");
    }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const override;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    virtual std::pair<uint32_t, uint32_t> getVersion() const override;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void commit() override;

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void rollback() override;

    //@}

    /// @name Public type and method used to determine file names for LFC.
    //@{

    /// @brief Types of the lease files used by the %Lease File Cleanup.
    ///
    /// This enumeration is used by a method which appends the appropriate
    /// suffix to the lease file name.
    enum LFCFileType {
        FILE_CURRENT,  ///< %Lease File
        FILE_INPUT,    ///< %Lease File Copy
        FILE_PREVIOUS, ///< Previous %Lease File
        FILE_OUTPUT,   ///< LFC Output File
        FILE_FINISH,   ///< LFC Finish File
        FILE_PID       ///< PID File
    };

    /// @brief Appends appropriate suffix to the file name.
    ///
    /// The suffix is selected using the LFC file type specified as a
    /// parameter. Each file type uses a unique suffix or no suffix:
    /// - Current File: no suffix
    /// - %Lease File Copy or Input File: ".1"
    /// - Previous File: ".2"
    /// - LFC Output File: ".output"
    /// - LFC Finish File: ".completed"
    /// - LFC PID File: ".pid"
    ///
    /// See
    /// https://gitlab.isc.org/isc-projects/kea/wikis/designs/Lease-File-Cleanup-design
    /// for details.
    ///
    /// @param file_name A base file name to which suffix is appended.
    /// @param file_type An LFC file type.
    /// @return A lease file name with a suffix appended.
    static std::string appendSuffix(const std::string& file_name,
                                    const LFCFileType& file_type);
    //@}


    /// @name Miscellaneous public convenience methods.
    ///       The following methods allow for retrieving useful information
    ///       about the state of the backend.
    //@{

    /// @brief Returns default path to the lease file.
    ///
    /// @param u Universe (V4 or V6).
    std::string getDefaultLeaseFilePath(Universe u) const;

    /// @brief Returns an absolute path to the lease file.
    ///
    /// @param u Universe (V4 or V6).
    ///
    /// @return Absolute path to the lease file or empty string if no lease
    /// file is used.
    std::string getLeaseFilePath(Universe u) const;

    /// @brief Specifies whether or not leases are written to disk.
    ///
    /// It is possible that leases for DHCPv4 are written to disk whereas leases
    /// for DHCPv6 are not; or vice versa. The argument of the method specifies
    /// the type of lease in that respect.
    ///
    /// @param u Universe (V4 or V6).
    ///
    /// @return true if leases are written to lease file; if false is
    /// returned, leases will be held in memory and will be lost upon
    /// server shut down.
    bool persistLeases(Universe u) const;

    //@}

private:

    /// @brief Initialize the location of the lease file.
    ///
    /// This method uses the parameters passed as a map to the constructor to
    /// initialize the location of the lease file. If the lease file is not
    /// specified, the method will use the default location for the universe
    /// (v4 or v6) selected. If the location is specified in the map as empty
    /// or the "persist" parameter is set to "no" it will set the empty
    /// location, which implies that leases belonging to the specified universe
    /// will not be written to disk.
    ///
    /// @param u Universe (v4 or v6)
    ///
    /// @return The location of the lease file that should be assigned to the
    /// lease_file4_ or lease_file6_, depending on the universe specified as an
    /// argument to this function.
    std::string initLeaseFilePath(Universe u);

    /// @brief Load leases from the persistent storage.
    ///
    /// This method loads DHCPv4 or DHCPv6 leases from lease files in the
    /// following order:
    /// - If the <filename>.completed doesn't exist:
    ///   - leases from the <filename>.2
    ///   - leases from the <filename>.1
    ///   - leases from the <filename>
    /// - else
    ///   - leases from the <filename>.completed
    ///   - leases from the <filename>
    ///
    /// If any of the files doesn't exist the method proceeds to reading
    /// leases from the subsequent file. If the <filename> doesn't exist
    /// it is created.
    ///
    /// When the method successfully reads leases from the files, it leaves
    /// the file <filename> open and its internal pointer is set to the
    /// end of file. The server will append lease entries to this file as
    /// a result of processing new messages from the clients.
    ///
    /// The <filename>.2, <filename>.1 and <filename>.completed are the
    /// products of the lease file cleanups (LFC).
    /// See:
    /// https://gitlab.isc.org/isc-projects/kea/wikis/designs/Lease-File-Cleanup-design
    /// for details.
    ///
    /// @note: When the server starts up or is reconfigured it will try to
    /// read leases from the lease files using this method. It is possible
    /// that the %Lease File Cleanup is performed upon the lease files to
    /// be read by this method. This may result in conflicts between the
    /// server process and the LFC. To prevent it, the method checks if the
    /// instance of the @c kea-lfc is running (using the PID file) before it
    /// tries to load leases from the lease files. If it finds that there
    /// is an LFC in progress, it throws an exception which will result
    /// in the server refuse to start or reconfigure. When the administrator
    /// retries starting up or reconfiguring the server it will most likely
    /// be successful as the LFC should be complete by that time.
    ///
    /// @todo Consider implementing delaying the lease files loading when
    /// the LFC is in progress by the specified amount of time.
    ///
    /// @param filename Name of the lease file.
    /// @param lease_file An object representing a lease file to which
    /// the server will store lease updates.
    /// @param storage A storage for leases read from the lease file.
    /// @tparam LeaseObjectType @c Lease4 or @c Lease6.
    /// @tparam LeaseFileType @c CSVLeaseFile4 or @c CSVLeaseFile6.
    /// @tparam StorageType @c Lease4Storage or @c Lease6Storage.
    ///
    /// @return Returns true if any of the files loaded need conversion from
    /// an older or newer schema.
    ///
    /// @throw CSVFileError when parsing any of the lease files fails.
    /// @throw DbOpenError when it is found that the LFC is in progress.
    template<typename LeaseObjectType, typename LeaseFileType,
             typename StorageType>
    bool loadLeasesFromFiles(const std::string& filename,
                             boost::shared_ptr<LeaseFileType>& lease_file,
                             StorageType& storage);

    /// @brief stores IPv4 leases
    Lease4Storage storage4_;

    /// @brief stores IPv6 leases
    Lease6Storage storage6_;

protected:

    /// @brief stores IPv6 by-relay-id cross-reference table
    Lease6ExtendedInfoRelayIdTable relay_id6_;

    /// @brief stores IPv6 by-remote-id cross-reference table
    Lease6ExtendedInfoRemoteIdTable remote_id6_;

    /// @brief Holds the pointer to the DHCPv4 lease file IO.
    boost::shared_ptr<CSVLeaseFile4> lease_file4_;

    /// @brief Holds the pointer to the DHCPv6 lease file IO.
    boost::shared_ptr<CSVLeaseFile6> lease_file6_;

public:

    /// @name Public methods to retrieve information about the LFC process state.
    ///       These methods are meant to be used by unit tests to retrieve the
    ///       state of the spawned LFC process before validating the result of
    ///       the lease file cleanup.
    //@{

    /// @brief Checks if the process performing lease file cleanup is running.
    ///
    /// @return true if the process performing lease file cleanup is running.
    bool isLFCRunning() const;

    /// @brief Returns the status code returned by the last executed
    /// LFC process.
    int getLFCExitStatus() const;
    //@}

    /// @brief Creates and runs the IPv4 lease stats query
    ///
    /// It creates an instance of a MemfileLeaseStatsQuery4 for an all subnets
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @return The populated query as a pointer to an LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery4() override;

    /// @brief Creates and runs the IPv4 lease stats query for all subnets and
    /// pools
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv4 lease statistical data for all subnets
    /// and pools.
    /// Each row of the result set is an LeaseStatRow which ordered ascending
    /// by subnet ID and pool ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startPoolLeaseStatsQuery4() override;

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// It creates an instance of a MemfileLeaseStatsQuery4 for a single subnet
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery4(const SubnetID& subnet_id) override;

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// It creates an instance of a MemfileLeaseStatsQuery4 for a subnet range
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetRangeLeaseStatsQuery4(const SubnetID& first_subnet_id,
                                                                const SubnetID& last_subnet_id) override;

    /// @brief Creates and runs the IPv6 lease stats query
    ///
    /// It creates an instance of a MemfileLeaseStatsQuery6 and then
    /// invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @return The populated query as a pointer to an LeaseStatsQuery.
    virtual LeaseStatsQueryPtr startLeaseStatsQuery6() override;

    /// @brief Creates and runs the IPv6 lease stats query for all subnets and
    /// pools
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv6 lease statistical data for all subnets
    /// and pools.
    /// Each row of the result set is an LeaseStatRow which ordered ascending
    /// by subnet ID and pool ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startPoolLeaseStatsQuery6() override;

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// It creates an instance of a MemfileLeaseStatsQuery6 for a single subnet
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery6(const SubnetID& subnet_id) override;

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// It creates an instance of a MemfileLeaseStatsQuery6 for a subnet range
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetRangeLeaseStatsQuery6(const SubnetID& first_subnet_id,
                                                                const SubnetID& last_subnet_id) override;

    /// @name Protected methods used for %Lease File Cleanup.
    /// The following methods are protected so as they can be accessed and
    /// tested by unit tests.
    //@{

protected:

    /// @brief A callback function triggering %Lease File Cleanup (LFC).
    ///
    /// This method is executed periodically to start the lease file cleanup.
    /// It checks whether the file is a DHCPv4 lease file or DHCPv6 lease file
    /// and executes the @c Memfile_LeaseMgr::lfcExecute private method
    /// with the appropriate parameters.
    ///
    /// This method is virtual so as it can be overridden and customized in
    /// the unit tests. In particular, the unit test which checks that the
    /// callback function has been executed would override this function
    /// to increase the execution counter each time it is executed.
    virtual void lfcCallback();
    //@}

    /// @name Private methods and members used for %Lease File Cleanup.
    //@{

private:

    /// @brief Setup the periodic %Lease File Cleanup.
    ///
    /// This method checks if the @c lfc-interval configuration parameter
    /// is set to a non-zero value and sets up the interval timer to
    /// perform the %Lease File Cleanup periodically. It also prepares the
    /// path and arguments for the @c kea-lfc application which will be
    /// executed to perform the cleanup. By default the backend will use
    /// the path to the kea-lfc in the Kea installation directory. If
    /// the unit tests need to override this path (with the path in the
    /// Kea build directory, the @c KEA_LFC_EXECUTABLE environmental
    /// variable should be set to hold an absolute path to the kea-lfc
    /// executable.
    /// @param conversion_needed flag that indicates input lease file(s) are
    /// schema do not match the current schema (older or newer), and need
    /// conversion. This value is passed through to LFCSetup::setup() via its
    /// run_once_now parameter.
    void lfcSetup(bool conversion_needed = false);

    /// @brief Performs a lease file cleanup for DHCPv4 or DHCPv6.
    ///
    /// This method performs all the actions necessary to prepare for the
    /// execution of the LFC and if these actions are successful, it executes
    /// the @c kea-lfc application as a background process to process (cleanup)
    /// the lease files.
    ///
    /// For the design and the terminology used in this description refer to
    /// the https://gitlab.isc.org/isc-projects/kea/wikis/designs/Lease-File-Cleanup-design.
    ///
    /// If the method finds that the %Lease File Copy exists it simply runs
    /// the @c kea-lfc application.
    ///
    /// If the %Lease File Copy doesn't exist it moves the Current %Lease File
    /// to Lease File Copy, and then recreates the Current Lease File without
    /// any lease entries. If the file has been successfully moved, it runs
    /// the @c kea-lfc application.
    ///
    /// @param lease_file A pointer to the object representing the Current
    /// %Lease File (DHCPv4 or DHCPv6 lease file).
    ///
    /// @tparam LeaseFileType One of @c CSVLeaseFile4 or @c CSVLeaseFile6.
    template<typename LeaseFileType>
    void lfcExecute(boost::shared_ptr<LeaseFileType>& lease_file);

    /// @brief A pointer to the Lease File Cleanup configuration.
    boost::scoped_ptr<LFCSetup> lfc_setup_;

    /// @brief Parameters storage
    ///
    /// DatabaseConnection object is used only for storing, accessing and
    /// printing parameter map.
    db::DatabaseConnection conn_;

    //@}

    /// @brief Manager mutex
    boost::scoped_ptr<std::mutex> mutex_;

    /// @brief Class lease counts container
    ClassLeaseCounter class_lease_counter_;

public:
    /// @brief Returns the class lease count for a given class and lease type.
    ///
    /// @param client_class client class for which the count is desired
    /// @param ltype type of lease for which the count is desired. Defaults to
    /// Lease::TYPE_V4.
    ///
    /// @return number of leases
    virtual size_t getClassLeaseCount(const ClientClass& client_class,
                                      const Lease::Type& ltype = Lease::TYPE_V4) const override;

    /// @brief Recount the leases per class for V4 leases.
    ///
    /// Clears the current class-lease count map and then iterates
    /// over all, retabulating counts based on class lists in each lease
    /// user-context.
    ///
    /// Must be called from a thread-safe context.
    virtual void recountClassLeases4() override;

    /// @brief Recount the leases per class for V6 leases.
    ///
    /// Clears the current class-lease count map and then iterates
    /// over all, retabulating counts based on class lists in each lease
    /// user-context.
    ///
    /// Must be called from a thread-safe context.
    virtual void recountClassLeases6() override;

    /// @brief Clears the class-lease count map.
    ///
    /// Must be called from a thread-safe context.
    virtual void clearClassLeaseCounts() override;

    /// The following queries are used to fulfill Bulk Lease Query
    /// queries. They rely on relay data contained in lease's
    /// user-context when the extended-store-info flag is enabled.

    /// @brief Returns existing IPv4 leases with a given relay-id.
    ///
    /// @param relay_id RAI Relay-ID sub-option value for relay_id of interest
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param qry_start_time when not zero, only leases whose CLTT is greater than
    /// or equal to this value will be included
    /// @param qry_end_time when not zero, only leases whose CLTT is less than
    /// or equal to this value will be included
    ///
    /// @return collection of IPv4 leases
    virtual Lease4Collection
    getLeases4ByRelayId(const OptionBuffer& relay_id,
                        const asiolink::IOAddress& lower_bound_address,
                        const LeasePageSize& page_size,
                        const time_t& qry_start_time = 0,
                        const time_t& qry_end_time = 0) override;

    /// @brief Returns existing IPv4 leases with a given remote-id.
    ///
    /// @param remote_id RAI Remote-ID sub-option value for remote-id of interest
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param qry_start_time when not zero, only leases whose CLTT is greater than
    /// or equal to this value will be included. Defaults to zero.
    /// @param qry_end_time when not zero, only leases whose CLTT is less than
    /// or equal to this value will be included. Defaults to zero.
    ///
    /// @return collection of IPv4 leases
    virtual Lease4Collection
    getLeases4ByRemoteId(const OptionBuffer& remote_id,
                         const asiolink::IOAddress& lower_bound_address,
                         const LeasePageSize& page_size,
                         const time_t& qry_start_time = 0,
                         const time_t& qry_end_time = 0) override;

    /// @brief Returns existing IPv6 leases with a given relay-id.
    ///
    /// @param relay_id DUID for relay_id of interest.
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByRelayId(const DUID& relay_id,
                        const asiolink::IOAddress& link_addr,
                        uint8_t link_len,
                        const asiolink::IOAddress& lower_bound_address,
                        const LeasePageSize& page_size) override;

    /// @brief Returns existing IPv6 leases with a given remote-id.
    ///
    /// @param remote_id remote-id option data of interest
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByRemoteId(const OptionBuffer& remote_id,
                         const asiolink::IOAddress& link_addr,
                         uint8_t link_len,
                         const asiolink::IOAddress& lower_bound_address,
                         const LeasePageSize& page_size) override;

    /// @brief Returns existing IPv6 leases with on a given link.
    ///
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByLink(const asiolink::IOAddress& link_addr,
                     uint8_t link_len,
                     const asiolink::IOAddress& lower_bound_address,
                     const LeasePageSize& page_size) override;

    /// @brief Extract extended info for v4 leases.
    ///
    /// For v4 relay and remote identifiers are stored inside leases vs.
    /// tables for v6.
    ///
    /// @param update Update extended info in database.
    /// @param current specify whether to use current (true) or staging
    /// (false) config.
    /// @return The number of updates in the database or 0.
    size_t extractExtendedInfo4(bool update, bool current);

    /// @brief Build extended info v6 tables.
    ///
    /// @param update Update extended info in database.
    /// @param current specify whether to use current (true) or staging
    /// (false) config.
    /// @return The number of updates in the database or 0.
    virtual size_t buildExtendedInfoTables6(bool update, bool current) override;

private:

    /// @brief Returns existing IPv4 leases with a given relay-id.
    ///
    /// @param relay_id RAI Relay-ID sub-option value for relay_id of interest
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param qry_start_time when not zero, only leases whose CLTT is greater than
    /// or equal to this value will be included
    /// @param qry_end_time when not zero, only leases whose CLTT is less than
    /// or equal to this value will be included
    ///
    /// @return collection of IPv4 leases
    Lease4Collection
    getLeases4ByRelayIdInternal(const OptionBuffer& relay_id,
                                const asiolink::IOAddress& lower_bound_address,
                                const LeasePageSize& page_size,
                                const time_t& qry_start_time,
                                const time_t& qry_end_time);

    /// @brief Returns existing IPv4 leases with a given remote-id.
    ///
    /// @param remote_id RAI Remote-ID sub-option value for remote-id of interest
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param qry_start_time when not zero, only leases whose CLTT is greater than
    /// or equal to this value will be included. Defaults to zero.
    /// @param qry_end_time when not zero, only leases whose CLTT is less than
    /// or equal to this value will be included. Defaults to zero.
    ///
    /// @return collection of IPv4 leases
    Lease4Collection
    getLeases4ByRemoteIdInternal(const OptionBuffer& remote_id,
                                 const asiolink::IOAddress& lower_bound_address,
                                 const LeasePageSize& page_size,
                                 const time_t& qry_start_time,
                                 const time_t& qry_end_time);

    /// @brief Returns existing IPv6 leases with a given relay-id.
    ///
    /// @param relay_id DUID for relay_id of interest.
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    Lease6Collection
    getLeases6ByRelayIdInternal(const DUID& relay_id,
                                const asiolink::IOAddress& link_addr,
                                uint8_t link_len,
                                const asiolink::IOAddress& lower_bound_address,
                                const LeasePageSize& page_size);

    /// @brief Returns existing IPv6 leases with a given remote-id.
    ///
    /// @param remote_id remote-id option data of interest.
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    Lease6Collection
    getLeases6ByRemoteIdInternal(const OptionBuffer& remote_id,
                                 const asiolink::IOAddress& link_addr,
                                 uint8_t link_len,
                                 const asiolink::IOAddress& lower_bound_address,
                                 const LeasePageSize& page_size);

    /// @brief Returns existing IPv6 leases with on a given link.
    ///
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    Lease6Collection
    getLeases6ByLinkInternal(const asiolink::IOAddress& link_addr,
                             uint8_t link_len,
                             const asiolink::IOAddress& lower_bound_address,
                             const LeasePageSize& page_size);

    /// @brief Build extended info v6 tables.
    ///
    /// @param update Update extended info in database.
    /// @param current specify whether to use current (true) or staging
    /// (false) config.
    /// @return The number of updates in the database or 0.
    size_t buildExtendedInfoTables6Internal(bool update, bool current);

public:

    /// @brief Write V4 leases to a file.
    ///
    /// @param filename File name to write leases.
    virtual void writeLeases4(const std::string& filename) override;

    /// @brief Write V6 leases to a file.
    ///
    /// @param filename File name to write leases.
    virtual void writeLeases6(const std::string& filename) override;

    /// @brief Upgrade extended info (v4).
    ///
    /// @param page_size The page size used for retrieval.
    /// @return Always return 0 as this function is a noop for not SQL backends.
    virtual size_t upgradeExtendedInfo4(const LeasePageSize& page_size) override;

protected:

    /// Extended information / Bulk Lease Query shared interface.

    /// @brief Delete lease6 extended info from tables.
    ///
    /// @param addr The address of the lease.
    virtual void deleteExtendedInfo6(const isc::asiolink::IOAddress& addr) override;

    /// @brief Add lease6 extended info into by-relay-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param relay_id The relay id from the relay header options.
    virtual void addRelayId6(const isc::asiolink::IOAddress& lease_addr,
                             const std::vector<uint8_t>& relay_id) override;

    /// @brief Add lease6 extended info into by-remote-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param remote_id The remote id from the relay header options.
    virtual void addRemoteId6(const isc::asiolink::IOAddress& lease_addr,
                              const std::vector<uint8_t>& remote_id) override;

private:
    /// @brief Write V4 leases to a file.
    ///
    /// @param filename File name to write leases.
    /// Must be called from a thread-safe context.
    virtual void writeLeases4Internal(const std::string& filename);

    /// @brief Write V6 leases to a file.
    ///
    /// @param filename File name to write leases.
    /// Must be called from a thread-safe context.
    virtual void writeLeases6Internal(const std::string& filename);
};

}  // namespace dhcp
}  // namespace isc

#endif // MEMFILE_LEASE_MGR_H
