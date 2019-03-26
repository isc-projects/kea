// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <slaac/simple_parser.h>
#include <slaac/slaac_cfg_mgr.h>
#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace isc::data;

namespace isc {
namespace slaac {
/// @brief This sets of arrays define the default values in various scopes
///        of the Slaac Configuration.
///
/// Each of those is documented in @file slaac/simple_parser.cc. This
/// is different than most other comments in Kea code. The reason
/// for placing those in .cc rather than .h file is that it
/// is expected to be one centralized place to look at for
/// the default values. This is expected to be looked at also by
/// people who are not skilled in C or C++, so they may be
/// confused with the differences between declaration and definition.
/// As such, there's one file to look at that hopefully is readable
/// without any C or C++ skills.
///
/// @{

/// @brief This table defines all global parameters in Slaac.
///
/// Boolean, integer, real and string types are for scalar parameters,
/// list and map types for entries, any matches all types.
/// Order follows global_param rule in bison grammar.
const SimpleKeywords SlaacSimpleParser::SLAAC_PARAMETERS = {
    { "interfaces-config", Element::map },
    { "loggers",           Element::list },
    { "hop-limit",         Element::integer },
    { "managed-flag",      Element::boolean },
    { "other-flag",        Element::boolean },
    { "router-lifetime",   Element::integer },
    { "reachable-time",    Element::integer },
    { "retrans-timer",     Element::integer },
    { "source-ll-address", Element::boolean },
    { "mtu",               Element::integer },
    { "universal-ra",      Element::any },
    { "prefix-infos",      Element::list },
    { "user-context",      Element::map },
    { "comment",           Element::string }
};

/// @brief This table defines default values for global options.
///
/// These are global Slaac parameters.
const SimpleDefaults SlaacSimpleParser::SLAAC_DEFAULTS = {
    { "hop-limit",         Element::integer, "0" },
    { "managed-flag",      Element::boolean, "true" },
    { "other-flag",        Element::boolean, "false" },
    { "router-lifetime",   Element::integer, "0" },
    { "reachable-time",    Element::integer, "0" },
    { "retrans-timer",     Element::integer, "0" },
    { "source-ll-address", Element::boolean, "false" },
    { "mtu",               Element::integer, "0" }
};

/// @brief This table defines all required prefix info parameters.
const SimpleRequiredKeywords SlaacSimpleParser::PREFIX_INFO_REQUIRED = {
    "prefix"
};

/// @brief This table defines all prefix info parameters in Slaac.
///
/// Boolean, integer, real and string types are for scalar parameters,
/// list and map types for entries, any matches all types.
/// Order follows global_param rule in bison grammar.
const SimpleKeywords SlaacSimpleParser::PREFIX_INFO_PARAMETERS = {
    { "prefix",              Element::string },
    { "on-link-flag",        Element::boolean },
    { "address-config-flag", Element::boolean },
    { "valid-lifetime",      Element::integer },
    { "preferred-lifetime",  Element::integer },
    { "user-context",        Element::map },
    { "comment",             Element::string }
};

/// @brief This table defines default values for prefix info  options.
///
/// These are Prefix Info parameters.
const SimpleDefaults SlaacSimpleParser::PREFIX_INFO_DEFAULTS = {
    { "on-link-flag",        Element::boolean, "false" },
    { "address-config-flag", Element::boolean, "false" },
    { "valid-lifetime",      Element::integer, "0" },
    { "preferred-lifetime",  Element::integer, "0" }
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t SlaacSimpleParser::setAllDefaults(const ElementPtr& global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, SLAAC_DEFAULTS);

    return (cnt);
}

size_t SlaacSimpleParser::deriveParameters(ConstElementPtr /*global*/) {
    size_t cnt = 0;

    return (cnt);
}

void
SlaacSimpleParser::parseExperimental(const SlaacConfigPtr& config,
                                     const ConstElementPtr& json) {
    if (!json) {
        return;
    }
    /// @todo: parse experimental structure
}

SlaacSimpleParser::parsePrefixInfos(PrefixInfosConfig& config,
                                    const ConstElementPtr& json) {
    // Reset first the config.
    config.clear();

    // Skip no or empty config.
    if (!json || json->empty()) {
        return;
    }

    // Iterate on the list.
    for (ElementPtr prefix_info_cfg : json->listValue()) {
        config.push_back(parsePrefixInfo(prefix_info_cfg));
    }
}

PrefixInfoConfigPtr
SlaacSimpleParser::parsePrefixInfo(ElementPtr json) {
    checkRequired(PREFIX_INFO_REQUIRED, json);

    setDefaults(json, PREFIX_INFO_DEFAULTS);

    checkKeywords(PREFIX_INFO_PARAMETERS, json);

    // Decode the prefix.
    std::string txt = json->get("prefix")->stringValue();

    // first let's remove any whitespaces.
    boost::erase_all(txt, " "); // space
    boost::erase_all(txt, "\t"); // tabulation

    isc::asiolink::IOAddress addr("::");
    uint8_t len = 0;

    try {
        // Is this prefix/len notation?
        size_t pos = txt.find("/");
        if (pos == std::string::npos) {
            isc_throw(ConfigError, "no / in prefix");
        }

        // Get address part.
        addr = isc::asiolink::IOAddress(txt.substr(0, pos));

        // Get length: start with the first character after /.
        std::string prefix_len = txt.substr(pos + 1);

        // It is lexical cast to int and then downcast to uint8_t.
        // Direct cast to uint8_t (which is really an unsigned char)
        // will result in interpreting the first digit as output
        // value and throwing exception if length is written on two
        // digits (because there are extra characters left over).
        int val_len = boost::lexical_cast<int>(prefix_len);
        if ((val_len < 0) || (val_len > 128)) {
            isc_throw(OutOfRange, "prefix length not in allowed 0..128 range");
        }
        len = static_cast<uint8_t>(val_len);
    } catch(const std::exception& ex) {
        isc_throw(ConfigError, "Failed to parse prefix: " << txt
                  << " (" << ex.what() << ")");
    } catch (...) {
        isc_throw(ConfigError, "Failed to parse prefix: " << txt);
    }

    PrefixInfoConfigPtr cfg(new PrefixInfoConfig(addr, len));

    cfg->setOnLinkFlag(getBoolean(json, "on-link-flag"));
    cfg->setAddrConfigFlag(getBoolean(json, "address-config-flag"));
    cfg->setValidLifetime(getUint32(json, "valid-lifetime"));
    cfg->setPreferredLifetime(getUint32(json, "preferred-lifetime"));

    return (cfg);
}

void
SlaacSimpleParser::parseInterfaces(const SlaacConfigPtr& config,
                                   const ConstElementPtr& json) {
    if (!json) {
        return;
    }

    /// @todo: parse interfaces
}

void
SlaacSimpleParser::parse(const SlaacConfigPtr& config,
                         const ConstElementPtr& json,
                         bool /*check_only*/) {

    checkKeywords(SlaacSimpleParser::SLAAC_PARAMETERS, json);

    config->setHopLimit(getUint8(json, "hop-limit"));
    config->setManagedFlag(getBoolean(json, "managed-flag"));
    config->setOtherFlag(getBoolean(json, "other-flag"));
    config->setRouterLifetime(getUint16(json, "router-lifetime"));
    config->setReachableTime(getUint32(json, "reachable-time"));
    config->setRetransTimer(getUint32(json, "retrans-timer"));

    config->setSrcLlAddr(getBoolean(json, "source-ll-address"));
    config->setMtu(getUint32(json, "mtu"));
    config->setUnivRa(json->get("universal-ra"));

    parseExperimental(config, json->get("experimental"));

    parsePrefixInfos(config->getPrefixInfosConfig(),
                     json->get("prefix-infos"));

    parseInterfaces(config, json->get("interfaces-list"));

    // User context can be done at anytime.
    ConstElementPtr user_context = json->get("user-context");
    if (user_context) {
        config->setContext(user_context);
    }
}

};
};
