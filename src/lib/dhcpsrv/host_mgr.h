// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_MGR_H
#define HOST_MGR_H

#include <asiolink/io_service.h>
#include <database/database_connection.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>
#include <cstdint>

namespace isc {
namespace dhcp {

// Enum flags to define a target of the host manager functions.
enum HostMgrOperationTarget {
    // The operation target not specified. Consider nothing.
    UNSPECIFIED_SOURCE = 0,
    // Consider only the CfgHosts instance.
    PRIMARY_SOURCE = 1, // 1 << 1
    // Consider only the alternate sources.
    ALTERNATE_SOURCES = 2, // 1 << 2
    // Consider both CfgInstance and alternate sources.
    ALL_SOURCES = 3  // PRIMARY_SOURCE | ALTERNATE_SOURCES
};

/// @brief Host Manager.
///
/// This is a singleton class which provides access to multiple sources of
/// information about static host reservations. These sources are also referred
/// to as host data sources. Each source derives (directly or indirectly) from
/// the @c BaseHostDataSource.
///
/// The @c HostMgr is a central point for providing information about the host
/// reservations. Internally, it relays the queries (calls to the appropriate
/// methods declared in the @c BaseHostDataSource) to the data sources it is
/// connected to. The @c HostMgr is always connected to the server's
/// configuration, accessible through the @c CfgHosts object in the @c CfgMgr.
/// The @c CfgHosts object holds all reservations specified in the DHCP server
/// configuration file. If a particular reservation is not found in the
/// @c CfgHosts object, the @c HostMgr will try to find it using alternate
/// host data storages. An alternate host data storage is usually a database
/// (e.g. SQL database), accessible through a dedicated host data source
/// object (a.k.a. database backend). This datasource is responsible for
/// managing the connection with the database and forming appropriate queries
/// to retrieve (or update) the information about the reservations.
///
/// The use of alternate host data sources is optional and usually requires
/// additional configuration to be specified by the server administrator.
/// For example, for the SQL database the user's credentials, database address,
/// and database name are required. The @c HostMgr passes these parameters
/// to an appropriate datasource which is responsible for opening a connection
/// and maintaining it.
///
/// It is possible to switch to different alternate data sources or disable
/// the use of alternate datasources, e.g. as a result of server's
/// reconfiguration. However, the use of the primary host data source (i.e.
/// reservations specified in the configuration file) can't be disabled.
class HostMgr : public boost::noncopyable, public BaseHostDataSource {
public:

    /// @brief Creates new instance of the @c HostMgr.
    ///
    /// If an instance of the @c HostMgr already exists, it will be replaced
    /// by the new instance. Thus, any instances of alternate host data
    /// sources will be dropped.
    ///
    static void create();

    /// @brief Add an alternate host backend (aka host data source).
    ///
    /// @param access Host backend access parameters for the alternate
    /// host backend. It holds "keyword=value" pairs, separated by spaces.
    ///
    /// The supported values are specific to the alternate backend in use.
    /// However, the "type" parameter will be common and it will specify which
    /// backend is to be used. Currently, no parameters are supported
    /// and the parameter is ignored.
    static void addBackend(const std::string& access);

    /// @brief Delete an alternate host backend (aka host data source).
    ///
    /// @param db_type database backend type.
    /// @return true when found and removed, false when not found.
    static bool delBackend(const std::string& db_type);

    /// @brief Delete an alternate host backend (aka host data source).
    ///
    /// @param db_type database backend type.
    /// @param access Host backend access parameters for the alternate
    /// host backend. It holds "keyword=value" pairs, separated by spaces.
    /// @param if_unusable flag which indicates if the host data source should
    /// be deleted only if it is unusable.
    /// @return false when not removed because it is not found or because it is
    /// still usable (if_unusable is true), true otherwise.
    static bool delBackend(const std::string& db_type,
                           const std::string& access,
                           bool if_unusable = false);

    /// @brief Delete all alternate backends.
    static void delAllBackends();

    /// @brief Check for the cache host backend.
    ///
    /// Checks if the first host backend implements
    /// the cache abstract class and sets cache_ptr_.
    ///
    /// @param logging When true (not the default) emit an informational log.
    /// @return true if the first host backend is a cache.
    static bool checkCacheBackend(bool logging = false);

    /// @brief Returns a sole instance of the @c HostMgr.
    ///
    /// This method should be used to retrieve an instance of the @c HostMgr
    /// to be used to gather/manage host reservations. It returns an instance
    /// of the @c HostMgr created by the @c create method. If such instance
    /// doesn't exist yet, it is created using the @c create method with the
    /// default value of the data access string, which configures the host
    /// manager to not use the alternate host data source.
    static HostMgr& instance();

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This method returns all @c Host objects representing reservations for
    /// a specified identifier as documented in the
    /// @c BaseHostDataSource::getAll.
    ///
    /// It retrieves reservations from both primary and alternate host data
    /// source as a single collection of @c Host objects, i.e. if matching
    /// reservations are in both sources, all of them are returned. The
    /// reservations from the primary data source are placed before the
    /// reservations from the alternate source.
    ///
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len,
           const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAll compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const;

    /// @brief Return all hosts in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects representing reservations
    /// in a specified subnet as documented in the
    /// @c BaseHostDataSource::getAll4
    ///
    /// It retrieves reservations from both primary and alternate host data
    /// source as a single collection of @c Host objects, i.e. if matching
    /// reservations are in both sources, all of them are returned. The
    /// reservations from the primary data source are placed before the
    /// reservations from the alternate source.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAll4(const SubnetID& subnet_id, const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAll4 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id) const;

    /// @brief Return all hosts in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects representing reservations
    /// in a specified subnet as documented in the
    /// @c BaseHostDataSource::getAll6
    ///
    /// It retrieves reservations from both primary and alternate host data
    /// source as a single collection of @c Host objects, i.e. if matching
    /// reservations are in both sources, all of them are returned. The
    /// reservations from the primary data source are placed before the
    /// reservations from the alternate source.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAll6(const SubnetID& subnet_id,
            const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAll6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname.
    ///
    /// @param hostname The lower case hostname.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAllbyHostname(const std::string& hostname,
                     const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAllbyHostname compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAllbyHostname(const std::string& hostname) const;

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAllbyHostname4(const std::string& hostname, const SubnetID& subnet_id,
                      const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAllbyHostname4 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAllbyHostname4(const std::string& hostname, const SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAllbyHostname6(const std::string& hostname, const SubnetID& subnet_id,
                      const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAllbyHostname6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAllbyHostname6(const std::string& hostname, const SubnetID& subnet_id) const;

    /// @brief Returns range of hosts in a DHCPv4 subnet.
    ///
    /// This method returns a page of @c Host objects representing
    /// reservations in a specified subnet as documented in the
    /// @c BaseHostDataSource::getPage4
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of hosts by specifying zero index and id
    ///   as the beginning of the range.
    /// - Index and last id of the returned range should be used as
    ///   starting index and id for the next page in the subsequent call.
    /// - All returned hosts are from the same source so if the number of
    ///   hosts returned is lower than the page size, it does not indicate
    ///   that the last page has been retrieved.
    /// - If there are no hosts returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage4(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Returns range of hosts in a DHCPv6 subnet.
    ///
    /// This method returns a page of @c Host objects representing
    /// reservations in a specified subnet as documented in the
    /// @c BaseHostDataSource::getPage6
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of hosts by specifying zero index and id
    ///   as the beginning of the range.
    /// - Index and last id of the returned range should be used as
    ///   starting index and id for the next page in the subsequent call.
    /// - All returned hosts are from the same source so if the number of
    ///   hosts returned is lower than the page size, it does not indicate
    ///   that the last page has been retrieved.
    /// - If there are no hosts returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage6(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Returns range of hosts.
    ///
    /// This method returns a page of @c Host objects representing
    /// reservations as documented in the @c BaseHostDataSource::getPage4
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of hosts by specifying zero index and id
    ///   as the beginning of the range.
    /// - Index and last id of the returned range should be used as
    ///   starting index and id for the next page in the subsequent call.
    /// - All returned hosts are from the same source so if the number of
    ///   hosts returned is lower than the page size, it does not indicate
    ///   that the last page has been retrieved.
    /// - If there are no hosts returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage4(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Returns range of hosts.
    ///
    /// This method returns a page of @c Host objects representing
    /// reservations as documented in the @c BaseHostDataSource::getPage6
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of hosts by specifying zero index and id
    ///   as the beginning of the range.
    /// - Index and last id of the returned range should be used as
    ///   starting index and id for the next page in the subsequent call.
    /// - All returned hosts are from the same source so if the number of
    ///   hosts returned is lower than the page size, it does not indicate
    ///   that the last page has been retrieved.
    /// - If there are no hosts returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage6(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected to
    /// different subnets.
    ///
    /// If matching reservations are both in the primary and the alternate
    /// data source, all of them are returned. The reservations from the
    /// primary data source are placed before the reservations from the
    /// alternate source.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAll4(const asiolink::IOAddress& address,
            const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAll4 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const;

    /// @brief Returns any host connected to the IPv4 subnet.
    ///
    /// This method returns a single reservation for a particular host as
    /// documented in the @c BaseHostDataSource::get4 even when the
    /// reservation is marked as from negative caching. This allows to
    /// monitor negative caching.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    ConstHostPtr
    get4Any(const SubnetID& subnet_id,
            const Host::IdentifierType& identifier_type,
            const uint8_t* identifier_begin,
            const size_t identifier_len,
            const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::get4Any compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostPtr
    get4Any(const SubnetID& subnet_id,
            const Host::IdentifierType& identifier_type,
            const uint8_t* identifier_begin,
            const size_t identifier_len) const;

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// This method returns a single reservation for a particular host as
    /// documented in the @c BaseHostDataSource::get4.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    ConstHostPtr
    get4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len,
         const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::get4 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) const;

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// This method returns a single reservation for the particular host
    /// (identified by the HW address or DUID) as documented in the
    /// @c BaseHostDataSource::get4.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Const @c Host object using a specified IPv4 address.
    ConstHostPtr
    get4(const SubnetID& subnet_id, const asiolink::IOAddress& address,
         const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::get4 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

    /// @brief Returns all hosts connected to the IPv4 subnet and having
    /// a reservation for a specified address.
    ///
    /// In most cases it is desired that there is at most one reservation
    /// for a given IPv4 address within a subnet. In a default configuration,
    /// the backend does not allow for inserting more than one host with
    /// the same IPv4 reservation. In that case, the number of hosts returned
    /// by this function is 0 or 1.
    ///
    /// If the backend is configured to allow multiple hosts with reservations
    /// for the same IPv4 address in the given subnet, this method can return
    /// more than one host.
    ///
    /// The typical use case when a single IPv4 address is reserved for multiple
    /// hosts is when these hosts represent different interfaces of the same
    /// machine and each interface comes with a different MAC address. In that
    /// case, the same IPv4 address is assigned regardless of which interface is
    /// used by the DHCP client to communicate with the server.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAll4(const SubnetID& subnet_id,
            const asiolink::IOAddress& address,
            const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAll4 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const;

    /// @brief Returns any host connected to the IPv6 subnet.
    ///
    /// This method returns a host connected to the IPv6 subnet as described
    /// in the @c BaseHostDataSource::get6 even when the
    /// reservation is marked as from negative caching. This allows to
    /// monitor negative caching.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    ConstHostPtr
    get6Any(const SubnetID& subnet_id,
            const Host::IdentifierType& identifier_type,
            const uint8_t* identifier_begin,
            const size_t identifier_len,
            const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::get6Any compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostPtr
    get6Any(const SubnetID& subnet_id,
            const Host::IdentifierType& identifier_type,
            const uint8_t* identifier_begin,
            const size_t identifier_len) const;

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// This method returns a host connected to the IPv6 subnet as described
    /// in the @c BaseHostDataSource::get6.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    ConstHostPtr
    get6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len,
         const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::get6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// This method returns a host using specified IPv6 prefix, as described
    /// in the @c BaseHostDataSource::get6.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Const @c Host object using a specified IPv6 prefix.
    ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len,
         const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::get6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Returns a host from specific subnet and reserved address.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Const @c host object that has a reservation for specified address.
    ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& addr,
         const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::get6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& addr) const;

    /// @brief Returns all hosts connected to the IPv6 subnet and having
    /// a reservation for a specified address or delegated prefix (lease).
    ///
    /// In most cases it is desired that there is at most one reservation
    /// for a given IPv6 lease within a subnet. In a default configuration,
    /// the backend does not allow for inserting more than one host with
    /// the same IPv6 address or prefix. In that case, the number of hosts
    /// returned by this function is 0 or 1.
    ///
    /// If the backend is configured to allow multiple hosts with reservations
    /// for the same IPv6 lease in the given subnet, this method can return
    /// more than one host.
    ///
    /// The typical use case when a single IPv6 lease is reserved for multiple
    /// hosts is when these hosts represent different interfaces of the same
    /// machine and each interface comes with a different MAC address. In that
    /// case, the same IPv6 lease is assigned regardless of which interface is
    /// used by the DHCP client to communicate with the server.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAll6(const SubnetID& subnet_id,
            const asiolink::IOAddress& address,
            const HostMgrOperationTarget target) const;

    /// @brief The @c HostMgr::getAll6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const;

    /// @brief The @c HostMgr::getAll6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on all host sources.
    virtual ConstHostCollection
    getAll6(const asiolink::IOAddress& address) const;

    /// @brief Returns a collection of hosts using the specified IPv6 address/prefix.
    ///
    /// This method may return multiple @c Host objects if they are connected to
    /// different subnets or if there are multiple hosts with the same IPv6 address/prefix.
    ///
    /// If matching reservations are both in the primary and the alternate
    /// data source, all of them are returned. The reservations from the
    /// primary data source are placed before the reservations from the
    /// alternate source.
    ///
    /// @param address IPv6 address for which the @c Host object is searched.
    /// @param target The host data source being a target of the operation.
    ///
    /// @return Collection of const @c Host objects.
    ConstHostCollection
    getAll6(const asiolink::IOAddress& address,
            const HostMgrOperationTarget target) const;

    /// @brief Adds a new host to the alternate data source.
    ///
    /// This method will throw an exception if no alternate data source is
    /// in use.
    ///
    /// @param host Pointer to the new @c Host object being added.
    /// @param target The host data source being a target of the operation.
    void add(const HostPtr& host, const HostMgrOperationTarget target);

    /// @brief The @c HostMgr::add compatible with @c BaseHostDataSource
    /// interfaces. Operates on alternate host sources only.
    virtual void add(const HostPtr& host);

    /// @brief Attempts to delete hosts by address.
    ///
    /// It deletes hosts from the first alternate source in which at least
    /// one matching host is found. In unlikely case that the hosts having
    /// the same IP address exist in other alternate sources, the hosts
    /// from these other sources are not deleted.
    ///
    /// This method supports both v4 and v6.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @param target The host data source being a target of the operation.
    /// @return true if deletion was successful, false otherwise.
    bool del(const SubnetID& subnet_id, const asiolink::IOAddress& addr,
             const HostMgrOperationTarget target);

    /// @brief The @c HostMgr::del compatible with @c BaseHostDataSource
    /// interfaces. Operates on alternate host sources only.
    virtual bool del(const SubnetID& subnet_id, const asiolink::IOAddress& addr);

    /// @brief Attempts to delete a host by (subnet4-id, identifier,
    /// identifier-type, operation-target)
    ///
    /// This method supports v4 only.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param target The host data source being a target of the operation.
    /// @return true if deletion was successful, false otherwise.
    bool
    del4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len,
         const HostMgrOperationTarget target);

    /// @brief The @c HostMgr::del4 compatible with @c BaseHostDataSource
    /// interfaces. Operates on alternate host sources only.
    virtual bool
    del4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Attempts to delete a host by (subnet6-id, identifier,
    /// identifier-type, operation-target)
    ///
    /// This method supports v6 only.
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param target The host data source being a target of the operation.
    /// @return true if deletion was successful, false otherwise.
    bool
    del6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len,
         const HostMgrOperationTarget target);

    /// @brief The @c HostMgr::del6 compatible with @c BaseHostDataSource
    /// interfaces. Operates on alternate host sources only.
    virtual bool
    del6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Implements @ref BaseHostDataSource::update() for alternate sources.
    ///
    /// Attempts to update an existing host entry.
    ///
    /// @param host the host up to date with the requested changes
    /// @param target The host data source being a target of the operation.
    void update(HostPtr const& host, const HostMgrOperationTarget target);

    /// @brief The @c HostMgr::update with default operation target. Operates
    /// on alternate host sources only.
    void update(HostPtr const& host);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("host_mgr"));
    }

    /// @brief Returns the host data source list.
    ///
    /// @return reference to the host data source list.
    HostDataSourceList& getHostDataSourceList() {
        return (alternate_sources_);
    }

    /// @brief Returns the first host data source.
    ///
    /// May return NULL if the host data source list is empty.
    /// @return pointer to the first host data source (or NULL).
    HostDataSourcePtr getHostDataSource() const;

    /// @brief Returns the negative caching flag.
    ///
    /// @return the negative caching flag.
    bool getNegativeCaching() const {
        return (negative_caching_);
    }

    /// @brief Sets the negative caching flag.
    ///
    void setNegativeCaching(bool negative_caching) {
        negative_caching_ = negative_caching;
    }

    /// @brief Returns the disable single query flag.
    ///
    /// @return the disable single query flag.
    bool getDisableSingleQuery() const {
        return (disable_single_query_);
    }

    /// @brief Sets the disable single query flag.
    ///
    void setDisableSingleQuery(bool disable_single_query) {
        disable_single_query_ = disable_single_query;
    }

    /// @brief Controls whether IP reservations are unique or non-unique.
    ///
    /// In a typical case, the IP reservations are unique and backends verify
    /// prior to adding a host reservation to the database that the reservation
    /// for a given IP address/subnet does not exist. In some cases it may be
    /// required to allow non-unique IP reservations, e.g. in the case when a
    /// host has several interfaces and independently of which interface is used
    /// by this host to communicate with the DHCP server the same IP address
    /// should be assigned. In this case the @c unique value should be set to
    /// false to disable the checks for uniqueness on the backend side.
    ///
    /// Calling this function on @c HostMgr causes the manager to attempt to
    /// set this flag on all backends in use.
    ///
    /// @param unique boolean flag indicating if the IP reservations must be
    /// unique or can be non-unique.
    /// @return true if the new setting was accepted by the backend or false
    /// otherwise.
    virtual bool setIPReservationsUnique(const bool unique);

    /// @brief Returns the boolean flag indicating if the IP reservations
    /// must be unique or can be non-unique.
    ///
    /// @return true if IP reservations must be unique or false if IP
    /// reservations can be non-unique.
    bool getIPReservationsUnique() const {
        return (ip_reservations_unique_);
    }

    /// @brief Sets IO service to be used by the Host Manager.
    ///
    /// @param io_service IOService object, used for all ASIO operations.
    static void setIOService(const isc::asiolink::IOServicePtr& io_service) {
        io_service_ = io_service;
    }

    /// @brief Returns pointer to the IO service.
    static isc::asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

protected:

    /// @brief The negative caching flag.
    ///
    /// When true and the first backend is a cache
    /// negative answers are inserted in the cache.
    /// This works for get[46] for a subnet and an identifier.
    bool negative_caching_;

    /// @brief The disable single query flag.
    ///
    /// When true prevent the use of lookup methods returning a collection
    /// aka single queries when methods returning a host object are usable
    /// instead.
    bool disable_single_query_;

    /// @brief Cache an answer.
    ///
    /// @param host Pointer to the missed host.
    virtual void cache(ConstHostPtr host) const;

    /// @brief Cache a negative answer.
    ///
    /// @param ipv4_subnet_id Identifier of the IPv4 subnet.
    /// @param ipv6_subnet_id Identifier of the IPv6 subnet.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of the Identifier.
    /// @param identifier_len Identifier length.
    virtual void cacheNegative(const SubnetID& ipv4_subnet_id,
                               const SubnetID& ipv6_subnet_id,
                               const Host::IdentifierType& identifier_type,
                               const uint8_t* identifier_begin,
                               const size_t identifier_len) const;

private:

    /// @brief Indicates if backends are running in the mode in which IP
    /// reservations must be unique (true) or non-unique (false).
    ///
    /// This flag is set to false only after calling @c setIPReservationsUnique
    /// with the @c unique value set to false and after this setting was
    /// successfully applied to all backends.
    bool ip_reservations_unique_;

    /// @brief Private default constructor.
    HostMgr() : negative_caching_(false), disable_single_query_(false),
                ip_reservations_unique_(true) { }

    /// @brief List of alternate host data sources.
    HostDataSourceList alternate_sources_;

    /// @brief Pointer to the cache.
    CacheHostDataSourcePtr cache_ptr_;

    /// @brief Returns a pointer to the currently used instance of the
    /// @c HostMgr.
    static boost::scoped_ptr<HostMgr>& getHostMgrPtr();

    /// The IOService object, used for all ASIO operations.
    static isc::asiolink::IOServicePtr io_service_;
};

}  // namespace dhcp
}  // namespace isc

#endif // HOST_MGR_H
