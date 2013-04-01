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

#ifndef DATASRC_CACHE_CONFIG_H
#define DATASRC_CACHE_CONFIG_H

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <cc/data.h>
#include <datasrc/memory/load_action.h>

#include <boost/noncopyable.hpp>

#include <map>
#include <string>

namespace isc {
namespace datasrc {
class DataSourceClient;

namespace internal {

/// \brief Exception thrown for configuration error related to in-memory cache.
class CacheConfigError : public Exception {
public:
    CacheConfigError(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

/// This class is intended to be an interface between DataSourceClient and
/// memory ZoneTableSegment implementations.  This class understands the
/// configuration parameters for DataSourceClient related to in-memory cache,
/// and convert it to native, type-safe objects so that it can be used by
/// ZoneTableSegment implementations.  It also provides unified interface
/// for getting a list of zones to be loaded in to memory and
/// and memory::LoadAction object that can be used for the load, regardless
/// of the underlying data source properties, i.e., whether it's special
/// "MasterFiles" type or other generic data sources.
///
/// This class is publicly defined because it has to be referenced by both
/// DataSourceClient and ZoneTableSegment (other than for testing purposes),
/// but it's essentially private to these two classes.  It's therefore
/// defined in an "internal" namespace, and isn't expected to be used by
/// other classes or user applications.  Likewise, this file is not expected
/// to be installed with other publicly usable header files.
class CacheConfig : boost::noncopyable {
public:
    CacheConfig(const std::string& datasrc_type,
                const DataSourceClient* datasrc_client,
                const data::Element& datasrc_conf,
                bool allowed);

    /// \brief Return if the cache is enabled.
    ///
    /// \throw None
    bool isEnabled() const { return (enabled_); }

    /// \brief Return the memory segment type to be used for the zone table.
    ///
    /// \throw None
    const std::string& getSegmentType() const { return (segment_type_); }

    /// This allows ZoneTableSegment to iterate over all zones to be loaded
    /// in to memory.  In this initial implementation we directly give
    /// read-only access to the underlying map to minimize the diff, but
    /// it's not clean in terms of encapsulation and performance (eventually
    /// we may have to look up in the underlying data source to get the list
    /// of zones, in which case constructing a map can be very expensive).
    typedef std::map<dns::Name, std::string>::const_iterator ConstZoneIterator;
    ConstZoneIterator begin() const { return (zone_config_.begin()); }
    ConstZoneIterator end() const { return (zone_config_.end()); }

private:
    const bool enabled_; // if the use of in-memory zone table is enabled
    const std::string segment_type_;
    // client of underlying data source, will be NULL for MasterFile datasrc
    const DataSourceClient* datasrc_client_;

    typedef std::map<dns::Name, std::string> Zones;
    Zones zone_config_;
};
}
}
}

#endif  // DATASRC_CACHE_CONFIG_H

// Local Variables:
// mode: c++
// End:
