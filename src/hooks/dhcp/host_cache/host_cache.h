// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_CACHE_H
#define HOST_CACHE_H

#include <config.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <config/cmds_impl.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <mutex>
#include <vector>

namespace isc {
namespace host_cache {

class HostCacheImpl;

/// @brief Host Cache implementation.
///
/// This Host cache provides Host backend that is able to cache hosts.
/// Support for both positive (there is an entry for given host) and
/// negative (there is no such entry) can be cached. Host collections
/// (returned by getAll*() methods) are not handled.
class HostCache : public isc::dhcp::CacheHostDataSource,
    private isc::config::CmdsImpl  {
public:

    /// @brief Constructor.
    /// @throw Unexpected if allocation fails.
    HostCache();

    /// @brief Destructor.
    virtual ~HostCache();

    /// @brief Parses configuration.
    ///
    /// @param config Configuration specified for the hooks library.
    /// @throw ConfigError when configuration fails.
    virtual void configure(const data::ConstElementPtr& config);

    /// @brief Set maximum number of cached hosts (0 means unbound).
    virtual void setMaximum(size_t maximum);

    /// @brief Get maximum number of cached hosts.
    virtual size_t getMaximum() const;

    ///
    /// BaseHostDataSource methods
    ///

    /// @note Methods returning collections must return empty collections
    /// and not throw because the host cache is an individual object cache
    /// so is transparent for these methods. Beware that these methods
    /// simply merge results without checking if an entry is already
    /// present too.

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// for a specified identifier. This method may return multiple hosts
    /// because a particular client may have reservations in multiple subnets.
    ///
    /// @param identifier_type Identifier type (ignored).
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier (ignored).
    /// @param identifier_len Identifier length.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll(const dhcp::Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const;

    /// @brief Return all hosts in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll4(const dhcp::SubnetID& subnet_id) const;

    /// @brief Return all hosts in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll6(const dhcp::SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname.
    ///
    /// @param hostname The lower case hostname.
    ///
    /// @return Collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAllbyHostname(const std::string& hostname) const;

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAllbyHostname4(const std::string& hostname,
                      const dhcp::SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAllbyHostname6(const std::string& hostname,
                      const dhcp::SubnetID& subnet_id) const;

    /// @brief Return range of hosts in a DHCPv4 subnet.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getPage4(const dhcp::SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const;

    /// @brief Return range of hosts in a DHCPv6 subnet.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getPage6(const dhcp::SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const;

    /// @brief Return range of hosts.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getPage4(size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const;

    /// @brief Return range of hosts.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getPage6(size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched
    ///        (ignored).
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const;

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual dhcp::ConstHostPtr
    get4(const dhcp::SubnetID& subnet_id,
         const dhcp::Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const;

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// One of the use cases for this method is to detect collisions between
    /// dynamically allocated addresses and reserved addresses. When the new
    /// address is assigned to a client, the allocation mechanism should check
    /// if this address is not reserved for some other host and do not allocate
    /// this address if reservation is present.
    ///
    /// Implementations of this method should guard against invalid addresses,
    /// such as IPv6 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Const @c Host object using a specified IPv4 address.
    virtual dhcp::ConstHostPtr
    get4(const dhcp::SubnetID& subnet_id,
         const asiolink::IOAddress& address) const;

    /// @brief Returns all hosts connected to the IPv4 subnet and having
    /// a reservation for a specified address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll4(const dhcp::SubnetID& subnet_id,
            const asiolink::IOAddress& address) const;

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual dhcp::ConstHostPtr
    get6(const dhcp::SubnetID& subnet_id,
         const dhcp::Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @c Host object using a specified IPv6 prefix.
    virtual dhcp::ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    virtual dhcp::ConstHostPtr
    get6(const dhcp::SubnetID& subnet_id,
         const asiolink::IOAddress& address) const;

    /// @brief Returns all hosts connected to the IPv6 subnet and having
    /// a reservation for a specified address or delegated prefix (lease).
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll6(const dhcp::SubnetID& subnet_id,
            const asiolink::IOAddress& address) const;

    /// @brief Returns a collection of hosts using the specified IPv6 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv6 address for which the @c Host object is searched.
    ///
    /// @return Empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll6(const asiolink::IOAddress& address) const;

    /// @brief Adds a new host to the collection.
    ///
    /// The implementations of this method should guard against duplicate
    /// reservations for the same host, where possible. For example, when the
    /// reservation for the same HW address and subnet id is added twice, the
    /// implementation should throw an exception. Note, that usually it is
    /// impossible to guard against adding duplicated host, where one instance
    /// is identified by HW address, another one by DUID.
    ///
    /// @param host Pointer to the new @c Host object being added.
    virtual void add(const dhcp::HostPtr& host);

    /// @brief Attempts to delete a host by (subnet-id, address)
    ///
    /// This method supports both v4 and v6.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return always false.
    virtual bool del(const dhcp::SubnetID& subnet_id,
                     const asiolink::IOAddress& addr);

    /// @brief Attempts to delete a host by (subnet-id4, identifier, identifier-type)
    ///
    /// This method supports v4 hosts only.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return always false.
    virtual bool del4(const dhcp::SubnetID& subnet_id,
                      const dhcp::Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len);

    /// @brief Attempts to delete a host by (subnet-id6, identifier, identifier-type)
    ///
    /// This method supports v6 hosts only.
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return always false.
    virtual bool del6(const dhcp::SubnetID& subnet_id,
                      const dhcp::Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len);

    /// @brief Implements @ref isc::dhcp::BaseHostDataSource::update() for
    /// HostCache.
    ///
    /// Attempts to update an existing host entry.
    ///
    /// @param host the host up to date with the requested changes
    void update(isc::dhcp::HostPtr const& host);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return "cache" string.
    virtual std::string getType() const {
        return ("cache");
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
    /// @param unique boolean flag indicating if the IP reservations must be
    /// unique within the subnet or can be non-unique.
    /// @return true when addresses must be unique, false otherwise because
    /// this backend does not support specifying the same IP address in multiple
    /// host reservations.
    virtual bool setIPReservationsUnique(const bool unique);

    /// @brief Returns the whole content of the cache as Element tree.
    ///
    /// @return a pointer to unparsed content
    virtual data::ElementPtr toElement() const;

    /// @brief Insert a host into the cache.
    ///
    /// Similar to @c add() but with a different purpose.
    ///
    /// @param host Pointer to the new @c Host object being inserted.
    /// @param overwrite false if doing nothing in case of conflicts
    /// (and returning 1), true if removing conflicting entries
    /// (and returning their number).
    /// @return number of conflicts limited to one if overwrite is false.
    virtual size_t insert(const dhcp::ConstHostPtr& host, bool overwrite);

    /// @brief Remove a host from the cache.
    ///
    /// Does the same than @c del, @c del4 or @c del6 but with
    /// a more uniform interface and a different purpose.
    ///
    /// @note A pointer to a copy does not remove the object.
    ///
    /// @param host Pointer to the existing @c Host object being removed.
    /// @return true when found and removed.
    virtual bool remove(const dhcp::HostPtr& host);

    /// @brief Flush entries.
    ///
    /// @param count number of entries to remove, 0 means all.
    virtual void flush(size_t count);

    /// @brief Return the number of entries.
    ///
    /// @return the current number of active entries in the cache.
    virtual size_t size() const;

    /// @brief Return the maximum number of entries.
    ///
    /// @return the maximum number of entries, 0 means unbound.
    virtual size_t capacity() const;

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// for a specified identifier. This method may return multiple hosts
    /// because a particular client may have reservations in multiple subnets.
    ///
    /// @param identifier_type Identifier type (ignored).
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier (ignored).
    /// @param identifier_len Identifier length.
    ///
    /// @return Collection of const @c Host objects.
    /// @todo Add to the cache_host_data_source.h file.
    virtual dhcp::ConstHostCollection
    get(const dhcp::Host::IdentifierType& identifier_type,
        const uint8_t* identifier_begin,
        const size_t identifier_len) const;

    ///
    /// Command handlers
    ///

    /// @brief cache-size command handler.
    ///
    /// This command returns the size of the host cache.
    ///
    /// No parameter taken.
    ///
    /// Example command returning the cache size.
    ///{
    ///    "command": "cache-size"
    ///}
    ///
    /// The result is the size of the cache.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// size command JSON text in the "command" argument
    /// @return result of the operation
    int cacheSizeHandler(hooks::CalloutHandle& handle);

    /// @brief cache-clear command handler.
    ///
    /// This command cleares the host cache.
    ///
    /// No parameter taken.
    ///
    /// Example command clearing the whole cache.
    ///{
    ///    "command": "cache-clear"
    ///}
    ///
    /// @param handle Callout context - which is expected to contain the
    /// clear command JSON text in the "command" argument
    /// @return result of the operation
    int cacheClearHandler(hooks::CalloutHandle& handle);

    /// @brief cache-flush command handler.
    ///
    /// This command flushes the host cache.
    ///
    /// Parameter is the number of entries to flush (must be > 0)
    /// or the string 'all'.
    ///
    /// Example command flushing at most 5 entries
    ///{
    ///    "command": "cache-flush",
    ///    "arguments": 5
    ///}
    ///
    /// Example command flush the whole cache
    ///{
    ///    "command": "cache-flush",
    ///    "arguments": "all"
    ///}
    ///
    /// @param handle Callout context - which is expected to contain the
    /// flush command JSON text in the "command" argument
    /// @return result of the operation
    int cacheFlushHandler(hooks::CalloutHandle& handle);

    /// @brief cache-get command handler.
    ///
    /// This command retrieves the host cache content.
    ///
    /// No parameter taken.
    ///
    /// Example command dumping the whole cache
    ///{
    ///    "command": "cache-get",
    ///}
    ///
    /// The result is a list of modified host reservations:
    ///  - client-classes for DHCPv4 and DHCPv6 are returned in
    ///    client-classes4 and client-classes6 entries
    ///  - option-data for DHCPv4 and DHCPv6 are returned in
    ///    option-data4 and option-data6 entries
    ///  - IPv4 subnet-id is added in the subnet-id4 entry
    ///  - IPv6 subnet-id is added in the subnet-id6 entry
    ///  - internal host-id is added in the host-id entry
    /// The list is ordered is decreasing last used time, i.e.
    /// the first host is the oldest and the last the newest.
    /// This operation is the main debug tool.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return result of the operation
    int cacheGetHandler(hooks::CalloutHandle& handle);

    /// @brief cache-get-by-id command handler.
    ///
    /// This command retrieves the host cache entries matching the
    /// given identifier.
    ///
    /// Parameters are an identifier-type and an identifier.
    ///
    /// Example command getting the specified entries.
    ///{
    ///    "command": "cache-get-by-id",
    ///    "arguments": { "hw-address": "01:02:03:04:05:06" }
    ///}
    ///
    /// The result is a list of modified host reservations:
    ///  - client-classes for DHCPv4 and DHCPv6 are returned in
    ///    client-classes4 and client-classes6 entries
    ///  - option-data for DHCPv4 and DHCPv6 are returned in
    ///    option-data4 and option-data6 entries
    ///  - IPv4 subnet-id is added in the subnet-id4 entry
    ///  - IPv6 subnet-id is added in the subnet-id6 entry
    ///  - internal host-id is added in the host-id entry
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return result of the operation
    int cacheGetByIdHandler(hooks::CalloutHandle& handle);

    /// @brief cache-insert command handler.
    ///
    /// This command inserts entries into the host cache.
    ///
    /// Parameter is either one entry, or a list of entries in
    /// the format described for cache-get.
    ///
    /// Example command
    ///{
    ///    "command": "cache-insert",
    ///    "arguments": { host1, host2 }
    ///}
    ///
    /// @param handle Callout context - which is expected to contain the
    /// insert command JSON text in the "command" argument and entry/entries
    /// in the "arguments" one.
    /// @return result of the operation
    int cacheInsertHandler(hooks::CalloutHandle& handle);

    /// @brief cache-write command handler.
    ///
    /// This command writes the host cache content to disk.
    ///
    /// Parameter is the path of the file where to write the host cache
    /// content as a JSON list of entries in the format described
    /// for cache-get.
    ///
    /// Example command
    ///{
    ///    "command": "cache-write",
    ///    "arguments": "cache.dump"
    ///}
    ///
    /// @param handle Callout context - which is expected to contain the
    /// write command JSON text in the "command" argument
    /// @return result of the operation
    int cacheWriteHandler(hooks::CalloutHandle& handle);

    /// @brief cache-load command handler.
    ///
    /// This command loads the cache content from disk.
    ///
    /// Parameter is the path of the file where to read the host cache
    /// content, i.e. the cache-write opposite operation.
    /// When two entries conflict the most recent one is kept and the
    /// previous/older one is removed.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// flush command JSON text in the "command" argument
    /// @return result of the operation
    int cacheLoadHandler(hooks::CalloutHandle& handle);

    /// @brief cache-remove command handler.
    ///
    /// This command removes entries into the host cache.
    ///
    /// Parameters are either a subnet-id and an ip-address, or
    /// an identifier-type, an identifier and subnet-id4 or subnet-id6.
    ///
    /// Example command with an address
    ///{
    ///    "command": "cache-remove",
    ///    "arguments": { "subnet-id": 123, "ip-address": "192.0.0.2" }
    ///}
    ///
    /// Example command with an identifier
    ///{
    ///    "command": "cache-remove",
    ///    "arguments": { "subnet-id6": 10, "hw-address": "01:02:03:04:05:06" }
    ///}
    ///
    /// @param handle Callout context - which is expected to contain the
    /// remove command JSON text in the "command" argument and entry/entries
    /// in the "arguments" one.
    /// @return result of the operation
    int cacheRemoveHandler(hooks::CalloutHandle& handle);

protected:

    /// @brief Implementation
    boost::shared_ptr<HostCacheImpl> impl_;

    /// @brief mutex
    boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Pointer to the Host Cache hooks library implementation.
typedef boost::shared_ptr<HostCache> HostCachePtr;

/// @brief Unparse a host cache entry.
///
/// Extension of host toElement method.
///
/// @param host host cache entry
/// @return Element representation of the host cache entry.
data::ElementPtr toElement(const dhcp::ConstHostPtr& host);

} // end of namespace isc::host_cache
} // end of namespace isc

#endif
