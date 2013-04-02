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

#include <dns/dns_fwd.h>
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

/// \brief Configuration for in-memory cache of a data source.
///
/// This class understands and validates the configuration parameters for
/// \c DataSourceClient related to in-memory cache, and converts it to native,
/// type-safe objects for the convenience of the user of this class.
/// Specifically, it allows the user to get the underlying memory segment
/// type for the cache as a string and to iterate over zone names to be
/// cached in memory.
///
/// It also provides unified interface for getting \c memory::LoadAction
/// object that can be used for loading zones, regardless of the underlying
/// data source properties, i.e., whether it's special "MasterFiles" type
/// or other generic data sources.
/// NOTE: this part will be done in #2834.
///
/// This class is publicly defined so it can be tested directly, but
/// it's essentially private to the \c ConfigurableClientList class.
/// It's therefore defined in an "internal" namespace, and isn't expected
/// to be used by other classes or user applications.  Likewise, this file
/// is not expected to be installed with other publicly usable header files.
///
/// It's defined as noncopyable, simply because it's not expected to be
/// copied in the intended usage for \c ConfigurableClientList.  Prohibiting
/// copies will help avoid unexpected disruption due to accidental copy and
/// sharing internal resources as a result of that.
class CacheConfig : boost::noncopyable {
public:
    /// \brief Constructor.
    ///
    /// It performs the following validation on the given configuration:
    /// - For the "MasterFiles" type
    ///   - datasrc_client_ must not be provided (must be null); throws
    ///     InvalidParameter otherwise.
    ///   - cache must be enabled: "cache-enable" configuration item exists
    ///     and is true, and allowed parameter is true, too; throws
    ///     CacheConfigError otherwise.
    ///   - "params" configuration item must be provided and of a map type,
    ///     and each map entry maps a string to another string; throws
    ///     data::TypeError otherwise.
    ///   - the key string of each map entry must be a valid textual
    ///     representation of a domain name.  Otherwise corresponding
    ///     exception from the dns::Name class will be thrown.
    /// - For other types
    ///   - datasrc_client_ must be provided (must not be null); throws
    ///     InvalidParameter otherwise.
    ///   - (Unless cache is disabled) "cache-zones" configuration item must
    ///     exist and must be a list of strings; throws data::TypeError
    ///     otherwise.
    ///   - Each string value of cache-zones entries must be a valid textual
    ///     representation of a domain name.  Otherwise corresponding
    ///     exception from the dns::Name class will be thrown.
    ///   - Names in the list must not have duplicates;
    ///     throws CacheConfigError otherwise.
    ///
    /// For other data source types than "MasterFiles", cache can be disabled.
    /// In this case cache-zones configuration item is simply ignored, even
    /// it contains an error that would otherwise trigger an exception.
    ///
    /// The specified set of zones (directly in "params" in case of
    /// "MasterFile", and specified in "cache-zones" for others) can be
    /// empty.
    ///
    /// This constructor also identifies the underlying memory segment type
    /// used for the cache.  It's given via the "cache-type" configuration
    /// item if defined; otherwise it defaults to "local".
    ///
    /// \throw InvalidParameter Program error at the caller side rather than
    /// in the configuration (see above)
    /// \throw CacheConfigError There is a semantics error in the given
    /// configuration (see above)
    /// \throw data::TypeError Invalid type of data is found in the
    /// configuration (see above)
    /// \throw Other Exceptions from the dns::Name class when conversion from
    /// text fails (see above)
    ///
    /// \param datasrc_type Type of data source. This must be the "type"
    /// value of the data source configuration.
    /// \param datasrc_client Client of the underlying data source for the
    /// cache, if it's used; for MasterFiles types it's null.
    /// \param datasrc_conf Configuration element for the data source.
    /// This must be the value of, e.g., data_sources/classes/IN[0] of
    /// BIND 10 configuration.
    /// \param allowed Whether in-memory cache is allowed by the process.
    /// This must be derived from the allow_cache parameter of
    /// \c ConfigurableClientList::configure().
    CacheConfig(const std::string& datasrc_type,
                const DataSourceClient* datasrc_client,
                const data::Element& datasrc_conf,
                bool allowed);

    /// \brief Return if the cache is enabled.
    ///
    /// The cache is considered enabled iff the "cache-enable" configuration
    /// item (given on construction) existed and was set to true, and
    /// the \c allowed parameter to the constructor was true.
    ///
    /// \throw None
    bool isEnabled() const { return (enabled_); }

    /// \brief Return the memory segment type to be used for the zone table.
    ///
    /// \throw None
    const std::string& getSegmentType() const { return (segment_type_); }

    memory::LoadAction getLoadAction(const dns::RRClass& rrlcass,
                                     const dns::Name& zone_name) const;

    /// \todo the following definition is tentative, mainly for tests.
    /// In #2834 we'll (probably) extend it to be a custom iterator so
    /// the caller can iterate over the whole set of zones, loading the
    /// content in memory.
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
