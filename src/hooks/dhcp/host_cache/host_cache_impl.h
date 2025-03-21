// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_CACHE_IMPL_H
#define HOST_CACHE_IMPL_H

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <container.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace isc {
namespace host_cache {

/// @brief Host Cache hooks library implementation.
class HostCacheImpl {
public:

    /// @brief Constructor.
    /// @throw Unexpected if allocation fails.
    HostCacheImpl();

    /// @brief Destructor.
    virtual ~HostCacheImpl();

    /// @brief Maximum number of elements (0 means unbound).
    size_t maximum_;

    /// @brief Set maximum number of elements.
    void setMaximum(size_t maximum) {
        maximum_ = maximum;
    }

    /// @brief Get maximum number of elements.
    size_t getMaximum() const {
        return (maximum_);
    }

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object using the specified identifier.
    dhcp::ConstHostPtr get4(const dhcp::SubnetID& subnet_id,
                            const dhcp::Host::IdentifierType& identifier_type,
                            const uint8_t* identifier_begin,
                            const size_t identifier_len);

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Const @c Host object using a specified IPv4 address.
    dhcp::ConstHostPtr get4(const dhcp::SubnetID& subnet_id,
                            const asiolink::IOAddress& address);

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object using the specified identifier.
    dhcp::ConstHostPtr get6(const dhcp::SubnetID& subnet_id,
                            const dhcp::Host::IdentifierType& identifier_type,
                            const uint8_t* identifier_begin,
                            const size_t identifier_len);

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @c Host object using a specified prefix.
    dhcp::ConstHostPtr get6(const asiolink::IOAddress& prefix,
                            const uint8_t prefix_len);

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    dhcp::ConstHostPtr get6(const dhcp::SubnetID& subnet_id,
                            const asiolink::IOAddress& address);

    /// @brief Returns @c Host object connected to a subnet.
    ///
    /// @param subnet_id IPv4 or IPv6 subnet identifier.
    /// @param subnet6 A boolean flag which indicates if the subnet identifier
    /// points to a IPv4 (if false) or IPv6 subnet (if true).
    /// @param identifier_type Identifier type.
    /// @param identifier Pointer to a first byte of the buffer holding an
    /// identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Iterator to the found host, or end if no host is found.
    HostContainerSequencedIndex::iterator
    getHostInternal(const dhcp::SubnetID& subnet_id, const bool subnet6,
                    const dhcp::Host::IdentifierType& identifier_type,
                    const uint8_t* identifier,
                    const size_t identifier_len);

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Iterator to the found host, or end if no host is found.
    HostContainerSequencedIndex::iterator
    getHostInternal4(const dhcp::SubnetID& subnet_id,
                     const asiolink::IOAddress& address);

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return @c Host object using a specified prefix, or NULL if no
    // host is found.
    dhcp::HostPtr
    getHostInternal6(const asiolink::IOAddress& prefix,
                     const uint8_t prefix_len);

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Const @c Host object using a specified IPv6 address/prefix,
    /// or NULL if no host is found.
    dhcp::HostPtr
    getHostInternal6(const dhcp::SubnetID& subnet_id,
                     const asiolink::IOAddress& address);

    /// @brief Adds a new host to the collection.
    ///
    /// @param host Pointer to the new @c Host object being added.
    /// @return true if successful, false if there is a conflict
    /// and it fails.
    bool add(const dhcp::HostPtr& host);

    /// @brief Attempts to delete a host by (subnet-id4, address)
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return deleted host information.
    std::string del4(const dhcp::SubnetID& subnet_id,
                     const asiolink::IOAddress& addr);

    /// @brief Attempts to delete a host by (subnet-id4, identifier, identifier-type)
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return deleted host information.
    std::string del4(const dhcp::SubnetID& subnet_id,
                     const dhcp::Host::IdentifierType& identifier_type,
                     const uint8_t* identifier_begin,
                     const size_t identifier_len);

    /// @brief Attempts to delete a host by (subnet-id6, address)
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return deleted host information.
    std::string del6(const dhcp::SubnetID& subnet_id,
                     const asiolink::IOAddress& addr);

    /// @brief Attempts to delete a host by (subnet-id6, identifier, identifier-type)
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return deleted host information.
    std::string del6(const dhcp::SubnetID& subnet_id,
                     const dhcp::Host::IdentifierType& identifier_type,
                     const uint8_t* identifier_begin,
                     const size_t identifier_len);

    /// @brief Relocate an entry to the end of sequenced index.
    ///
    /// Used to implement least-recently-used, called to return
    /// get*() results.
    ///
    /// @param host host to relocate.
    /// @return host itself.
    dhcp::HostPtr relocate(dhcp::HostPtr host);

    /// @brief Unparse cache content.
    ///
    /// @return a pointer to unparsed content
    data::ElementPtr toElement() const;

    /// @brief Insert a host into the cache.
    ///
    /// Does the same than @c add() but with a different purpose.
    ///
    /// @param host Pointer to the new @c Host object being inserted.
    /// @param overwrite false if doing nothing in case of conflicts
    /// (and returning 1), true if removing conflicting entries
    /// (and returning their number).
    /// @return number of conflicts limited to one if overwrite is false.
    size_t insert(const dhcp::ConstHostPtr& host, bool overwrite);

    /// @brief Implements @ref BaseHostDataSource::update() for HostCacheImpl.
    ///
    /// Attempts to update an existing host entry.
    ///
    /// @param host the host up to date with the requested changes
    void update(isc::dhcp::ConstHostPtr const& host);

    /// @brief Insert IPv6 reservations.
    ///
    /// @param host host with the IPv6 reservations to insert.
    /// @return true if succeed.
    bool insertResv6(const dhcp::HostPtr& host);

    /// @brief Remove a host from the cache.
    ///
    /// Does the same than @c del, @c del4 or @c del6 but with
    /// a more uniform interface and a different purpose.
    ///
    /// @note A pointer to a copy does not remove the object.
    ///
    /// @param host Pointer to the existing @c Host object being removed.
    /// @return true when found and removed.
    bool remove(const dhcp::HostPtr& host);

    /// @brief Remove IPv6 reservations.
    ///
    /// @param host host with the IPv6 reservations to remove.
    void removeResv6(const dhcp::HostPtr& host);

    /// @brief Flush all entries.
    void clear() {
        cache_.clear();
        cache6_.clear();
    }

    /// @brief Flush entries.
    ///
    /// @param count number of entries to remove.
    void flush(size_t count);

    /// @brief Return the number of entries.
    ///
    /// @return the current number of active entries in the cache.
    size_t size() const {
        return (cache_.size());
    }

    /// @brief Return the maximum number of entries.
    ///
    /// @return the maximum number of entries, 0 means unbound.
    size_t capacity() const {
        return (maximum_);
    }

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

private:

    /// @brief Multi-index container holding DHCPv4 cache.
    ///
    /// It can be used for finding entries by the following criteria:
    /// - itself
    /// - IPv4 address
    /// - DUID
    /// - HW/MAC address
    HostContainer cache_;

    /// @brief Multi-index container holding DHCPv6 reservation cache.
    ///
    /// It can be used for finding entries by the following criteria:
    /// - IPv6 address
    /// - IPv6 prefix
    Resv6Container cache6_;
};

} // end of namespace isc::host_cache
} // end of namespace isc

#endif
