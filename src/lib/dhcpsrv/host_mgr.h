// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_MGR_H
#define HOST_MGR_H

#include <database/database_connection.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

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
    ///
    /// @return Collection of const @c Host objects.
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
    ///
    /// @return Collection of const @c Host objects.
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
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id) const;

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
    ///
    /// @return Collection of const @c Host objects.
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
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
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
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
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
    ///
    /// @return Const @c Host object using a specified IPv4 address.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

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
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
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
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
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
    ///
    /// @return Const @c Host object using a specified IPv6 prefix.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Returns a host from specific subnet and reserved address.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    ///
    /// @return Const @c host object that has a reservation for specified address.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& addr) const;

    /// @brief Adds a new host to the alternate data source.
    ///
    /// This method will throw an exception if no alternate data source is
    /// in use.
    ///
    /// @param host Pointer to the new @c Host object being added.
    virtual void add(const HostPtr& host);

    /// @brief Attempts to delete a host by address.
    ///
    /// This method supports both v4 and v6.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return true if deletion was successful, false otherwise.
    virtual bool del(const SubnetID& subnet_id, const asiolink::IOAddress& addr);

    /// @brief Attempts to delete a host by (subnet4-id, identifier, identifier-type)
    ///
    /// This method supports v4 only.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false otherwise.
    virtual bool
    del4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Attempts to delete a host by (subnet6-id, identifier, identifier-type)
    ///
    /// This method supports v6 only.
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false otherwise.
    virtual bool
    del6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len);

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
    /// @param host Pointer to the missied host.
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

    /// @brief Private default constructor.
    HostMgr() : negative_caching_(false), disable_single_query_(false) { }

    /// @brief List of alternate host data sources.
    HostDataSourceList alternate_sources_;

    /// @brief Pointer to the cache.
    CacheHostDataSourcePtr cache_ptr_;

    /// @brief Returns a pointer to the currently used instance of the
    /// @c HostMgr.
    static boost::scoped_ptr<HostMgr>& getHostMgrPtr();

};
}
}

#endif // HOST_MGR_H
