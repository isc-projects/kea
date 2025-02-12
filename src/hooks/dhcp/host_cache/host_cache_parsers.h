// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_CACHE_PARSER_H
#define HOST_CACHE_PARSER_H

#include <host_cache.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/host.h>
#include <container.h>

namespace isc {
namespace host_cache {

/// @brief Configuration parser for Host Cache.
class HCConfigParser : public data::SimpleParser {
public:

    /// @brief Parses Host Cache configuration.
    ///
    /// @param hcref Reference to the Host Cache instance.
    /// @param config Specified configuration.
    /// @throw ConfigError when parsing fails or configuration is invalid.
    void parse(HostCache& hcref, const data::ConstElementPtr& config);

    /// @brief Defaults for Host Cache configuration.
    static const data::SimpleDefaults HOST_CACHE_DEFAULTS;

    /// @brief Absolute maximum number of elements.
    static const int64_t MAXIMUM = 1000000000ULL;
};

/// @brief Host cache entry parser.
class HCEntryParser : public data::SimpleParser {
public:

    /// @brief Parses Host Cache entry.
    ///
    /// The entry is inserted into the host cache.
    ///
    /// @param entry Data element holding map with a host cache entry.
    /// @return @c isc::dhcp::Host pointer
    dhcp::HostPtr parse(const data::ConstElementPtr& entry);
};

/// @brief Host cache content parser.
class HCEntryListParser : public data::SimpleParser {
public:

    /// @brief Parses Host Cache entries.
    ///
    /// Entries are inserted into the host cache.
    ///
    /// @param entry_list Data element holding list of host cache entries.
    /// @return @c isc::dhcp::Host collection.
    dhcp::HostCollection parse(const data::ConstElementPtr& entry_list) {
        auto& entries = entry_list->listValue();
        dhcp::HostCollection hosts;
        for (auto const& entry : entries) {
            HCEntryParser parser;
            hosts.push_back(parser.parse(entry));
        }
        return (hosts);
    }
};

} // end of namespace isc::host_cache
} // end of namespace isc

#endif
