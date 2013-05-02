// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef DATASRC_ZONE_TABLE_ACCESSOR_CACHE_H
#define DATASRC_ZONE_TABLE_ACCESSOR_CACHE_H

#include <datasrc/zone_table_accessor.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace datasrc {
namespace internal {
class CacheConfig;

/// \brief A \c ZoneTableAccessor implementation for in-memory cache.
///
/// This class implements the \c ZoneTableAccessor interface for in-memory
/// cache.  Its conceptual table consists of the zones that are specified
/// to be loaded into memory in configuration.  Note that these zones
/// may or may not actually be loaded in memory.  In fact, this class object
/// is intended to be used by applications that load these zones into memory,
/// so that the application can get a list of zones to be loaded.  Also, even
/// after loading, some zone may still not be loaded, e.g., due to an error
/// in the corresponding zone file.
///
/// An object of this class is expected to be returned by
/// \c ConfigurableClientList.  Normal applications shouldn't instantiate
/// this class directly.  It's still defined to be publicly visible for
/// testing purposes but, to clarify the intent, it's hidden in the
/// "internal" namespace.
class ZoneTableAccessorCache : public ZoneTableAccessor {
public:
    /// \brief Constructor.
    ///
    /// This class takes a \c CacheConfig object and holds it throughout
    /// its lifetime.  The caller must ensure that the configuration is
    /// valid throughout the lifetime of this accessor object.
    ///
    /// \throw None
    ///
    /// \param config The cache configuration that the accessor refers to.
    ZoneTableAccessorCache(const CacheConfig& config) : config_(config) {}

    /// \brief In-memory cache version of \c getIterator().
    ///
    /// As returned from this version of iterator, \c ZoneSpec::index
    /// will always be set to 0 at the moment.
    ///
    /// \throw None except std::bad_alloc in case of memory allocation failure
    virtual IteratorPtr getIterator() const;

private:
    const CacheConfig& config_;
};

}
}
}

#endif  // DATASRC_ZONE_TABLE_ACCESSOR_CACHE_H

// Local Variables:
// mode: c++
// End:
