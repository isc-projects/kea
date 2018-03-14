// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.

#ifndef CACHE_HOST_DATA_SOURCE_H
#define CACHE_HOST_DATA_SOURCE_H

#include <dhcpsrv/base_host_data_source.h>

namespace isc {
namespace dhcp {

/// @brief Abstract interface extending base simple data source for host
/// reservations to host cache.
/// Only the insert() method is required to use the cache.
class CacheHostDataSource : public virtual BaseHostDataSource {
public:

    /// @brief Default destructor implementation.
    virtual ~CacheHostDataSource() { }

    /// @brief Insert a host into the cache.
    ///
    /// Similar to @c add() but with a different purpose.
    ///
    /// @param host Pointer to the new @c Host object being inserted.
    /// @param[in,out] overwrite -1 if accepting conflicts, 0 if removing
    /// conflicting entries, set to the number of removed entries.
    /// @return true when succeeded.
    virtual bool insert(const ConstHostPtr& host, int& overwrite) = 0;

    /// @brief Remove a host from the cache.
    ///
    /// Does the same than @c del, @c del4 or @c del6 but with
    /// a more uniform interface and a different purpose.
    ///
    /// @param host Pointer to the existing @c Host object being removed.
    /// @return true when found and removed.
    virtual bool remove(const HostPtr& host) = 0;

    /// @brief Flush entries.
    ///
    /// @param count number of entries to remove, 0 means all.
    virtual void flush(size_t count) = 0;

    /// @brief Return the number of entries.
    ///
    /// @return the current number of active entries in the cache.
    virtual size_t size() const = 0;

    /// @brief Return the maximum number of entries.
    ///
    /// @return the maximum number of entries, 0 means unbound.
    virtual size_t capacity() const = 0;
};

/// @brief CacheHostDataSource pointer.
typedef boost::shared_ptr<CacheHostDataSource> CacheHostDataSourcePtr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CACHE_HOST_DATA_SOURCE_H
