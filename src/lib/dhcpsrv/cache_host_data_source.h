// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    /// @param overwrite false if doing nothing in case of conflicts
    /// (and returning 1), true if removing conflicting entries
    /// (and returning their number).
    /// @return number of conflicts limited to one if overwrite is false.
    virtual size_t insert(const ConstHostPtr& host, bool overwrite) = 0;

    /// @brief Remove a host from the cache.
    ///
    /// Does the same as @c del, @c del4 or @c del6 but with
    /// a more uniform interface and a different purpose.
    ///
    /// @note A pointer to a copy does not remove the object.
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
