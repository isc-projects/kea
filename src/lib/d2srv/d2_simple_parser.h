// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_SIMPLE_PARSER_H
#define D2_SIMPLE_PARSER_H

#include <cc/simple_parser.h>
#include <d2srv/d2_cfg_mgr.h>

namespace isc {
namespace d2 {

/// @brief SimpleParser specialized for D2
///
/// This class is a @ref isc::data::SimpleParser dedicated to D2.
/// In particular, it contains all the default values and names of the
/// parameters that are to be derived (inherited) between scopes.
/// For the actual values, see @file d2_simple_parser.cc
class D2SimpleParser : public data::SimpleParser {
public:

    /// @brief Sets all defaults for D2 configuration
    ///
    /// This method sets global and element defaults.
    ///
    /// @param global scope to be filled in with defaults.
    /// @return number of default values added
    static size_t setAllDefaults(data::ElementPtr global);

    // see d2_simple_parser.cc for comments for those parameters
    static const data::SimpleDefaults D2_GLOBAL_DEFAULTS;

    // Defaults for tsig-keys list elements, TSIGKeyInfos
    static const data::SimpleDefaults TSIG_KEY_DEFAULTS;

    // Defaults for <forward|reverse>-ddns elements, DdnsDomainListMgrs
    static const data::SimpleDefaults DDNS_DOMAIN_MGR_DEFAULTS;

    // Defaults for ddns-domains list elements, DdnsDomains
    static const data::SimpleDefaults DDNS_DOMAIN_DEFAULTS;

    // Defaults for dns-servers list elements, DnsServerInfos
    static const data::SimpleDefaults DNS_SERVER_DEFAULTS;

    /// @brief Adds default values to a DDNS Domain element
    ///
    /// Adds the scalar default values to the given DDNS domain
    /// element, and then adds the DNS Server defaults to the domain's
    /// server list, "dns-servers".
    ///
    /// @param domain DDNS domain element to which defaults should be added
    /// @param domain_defaults list of default values from which to add
    /// @return returns the number of default values added
    static size_t setDdnsDomainDefaults(data::ElementPtr domain,
                                        const data::SimpleDefaults&
                                        domain_defaults);

    /// @brief Adds default values to a DDNS Domain List Manager
    ///
    /// This function looks for the named DDNS domain manager element within
    /// the given element tree.  If it is found, it adds the scalar default
    /// values to the manager element and then adds the DDNS Domain defaults
    /// to its domain list, "ddns-domains".  If the manager element is not
    /// found, then an empty map entry is added for it, thus defaulting the
    /// manager to "disabled".
    ///
    /// @param global element tree containing the DDNS domain manager element
    /// to which defaults should be
    /// added
    /// @param mgr_name name of the manager element within the element tree
    /// (e.g. "forward-ddns", "reverse-ddns")
    /// @param mgr_defaults list of default values from which to add
    /// @return returns the number of default values added
    static size_t setManagerDefaults(data::ElementPtr global,
                                     const std::string& mgr_name,
                                     const data::SimpleDefaults& mgr_defaults);

    /// @brief Parses the whole D2 configuration
    ///
    /// @param ctx - parsed information will be stored here
    /// @param config - Element tree structure that holds configuration
    /// @param check_only - if true the configuration is verified only, not applied
    ///
    /// @throw ConfigError if any issues are encountered.
    void parse(const D2CfgContextPtr& ctx,
               const isc::data::ConstElementPtr& config,
               bool check_only);
};

};
};

#endif
