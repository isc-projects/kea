// Copyright (C) 2019-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_NETWORK_PARSER_H
#define BASE_NETWORK_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfg_globals.h>
#include <dhcpsrv/network.h>

namespace isc {
namespace dhcp {

/// @brief Common configuration parser for shared networks
/// and subnets.
class BaseNetworkParser : public data::SimpleParser {
protected:

    /// @brief Parses common parameters
    ///
    /// The parsed parameters are:
    /// - renew-timer,
    /// - rebind-timer,
    /// - valid-lifetime,
    /// - store-extended-info
    /// - reservations-global
    /// - reservations-in-subnet
    /// - reservations-out-of-pool
    ///
    /// @param network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    void parseCommon(const data::ConstElementPtr& network_data,
                     NetworkPtr& network);

    /// @brief Parses parameters related to "percent" timers settings.
    ///
    /// The parsed parameters are:
    /// - calculate-tee-times,
    /// - t1-percent,
    /// - t2-percent.
    ///
    /// @param network_data Data element holding network configuration
    /// to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    ///
    /// @throw DhcpConfigError if configuration of these parameters is
    /// invalid.
    void parseTeePercents(const data::ConstElementPtr& network_data,
                          NetworkPtr& network);

    /// @brief Parses parameters related to lease cache settings.
    ///
    /// The parsed parameters are:
    /// - cache-threshold,
    /// - cache-max-age.
    ///
    /// @param network_data Data element holding network configuration
    /// to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    ///
    /// @throw DhcpConfigError if configuration of these parameters is
    /// invalid.
    void parseCacheParams(const data::ConstElementPtr& network_data,
                          NetworkPtr& network);

    /// @brief Parses parameters pertaining to DDNS behavior.
    ///
    /// The parsed parameters are:
    /// - ddns-send-updates
    /// - ddns-override-no-update
    /// - ddns-override-client-update
    /// - ddns-replace-client-name
    /// - ddns-generated-prefix
    /// - ddns-qualifying-suffix
    /// - ddns-use-conflict-resolution (retained for backward compatibility)
    /// - ddns-update-on-renew
    /// - ddns-ttl-percent
    /// - ddns-conflict-resolution-mode
    ///
    /// @param network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    void parseDdnsParams(const data::ConstElementPtr& network_data,
                         NetworkPtr& network);

    /// @brief Parses parameters pertaining to allocator selection.
    ///
    /// The parsed parameters are:
    /// - allocator
    ///
    /// @param network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    void parseAllocatorParams(const data::ConstElementPtr& network_data,
                              NetworkPtr& network);

    /// @brief Parses parameters pertaining to prefix delegation allocator
    /// selection.
    ///
    /// The parsed parameters are:
    /// - pd-allocator
    ///
    /// @param network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    void parsePdAllocatorParams(const data::ConstElementPtr& network_data,
                                Network6Ptr& network);

    /// @brief Parses offer-lifetime parameter (v4 only)
    ///
    /// @param network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to the v4 network in which parsed data is
    /// to be stored.
    /// @throw DhcpConfigError if the value is less than 0.
    void parseOfferLft(const data::ConstElementPtr& network_data,
                       Network4Ptr& network);
public:
    typedef std::function<void(const isc::dhcp::ClientClass&)> ClassAdderFunc;

    /// @brief Fetches the element for either 'evaluate-additional-classes' or deprecated
    /// 'require-client-classes'
    ///
    /// @param params configuration element tree to search.
    /// @param adder_func function to add class names to an object's additional class list.
    /// @throw DhcpConfigError if both entries are present.
    static void getAdditionalClassesElem(data::ConstElementPtr params,
                                         ClassAdderFunc adder_func);

    /// @brief Fetches the element for either 'client-classes' or deprecated
    /// 'client-class'
    ///
    /// @param params configuration element tree to search.
    /// @param adder_func function to add class names to an object's client class list.
    /// @throw DhcpConfigError if both entries are present.
    static void getClientClassesElem(data::ConstElementPtr params,
                                     ClassAdderFunc adder_func);

    /// @brief Parses parameters pertaining to DDNS behavior.
    ///
    /// The parsed parameters are:
    /// - ddns-send-updates
    /// - ddns-override-no-update
    /// - ddns-override-client-update
    /// - ddns-replace-client-name
    /// - ddns-generated-prefix
    /// - ddns-qualifying-suffix
    /// - ddns-use-conflict-resolution (retained for backward compatibility)
    /// - ddns-update-on-renew
    /// - ddns-ttl-percent
    /// - ddns-conflict-resolution-mode
    /// - ddns-ttl
    /// - ddns-ttl-min
    /// - ddns-ttl-max
    ///
    /// Owner types are expected to have public setters for each of these
    /// parameters.
    ///
    /// @tparam DdnsOwnerPtr pointer to the class type that owns the DDNS parameters.
    /// @param config configuration element holding the DDNS parameters to parse.
    /// @param owner Pointer to the DDNS parameter owner object into which parsed values
    /// should be stored.
    /// @throw BadValue for various invalid values.
    template<typename DdnsOwnerTypePtr>
    void parseDdnsParameters(const data::ConstElementPtr& config,
                             DdnsOwnerTypePtr owner) {

        if (config->contains("ddns-send-updates")) {
            owner->setDdnsSendUpdates(getBoolean(config, "ddns-send-updates"));
        }

        if (config->contains("ddns-override-no-update")) {
            owner->setDdnsOverrideNoUpdate(getBoolean(config, "ddns-override-no-update"));
        }

        if (config->contains("ddns-override-client-update")) {
            owner->setDdnsOverrideClientUpdate(getBoolean(config, "ddns-override-client-update"));
        }

        if (config->contains("ddns-replace-client-name")) {
            owner->setDdnsReplaceClientNameMode(getAndConvert<D2ClientConfig::ReplaceClientNameMode,
                                                              D2ClientConfig::stringToReplaceClientNameMode>
                                                              (config, "ddns-replace-client-name",
                                                              "ReplaceClientName mode"));
        }

        if (config->contains("ddns-generated-prefix")) {
            owner->setDdnsGeneratedPrefix(getString(config, "ddns-generated-prefix"));
        }

        if (config->contains("ddns-qualifying-suffix")) {
            owner->setDdnsQualifyingSuffix(getString(config, "ddns-qualifying-suffix"));
        }

        std::string hostname_char_set;
        if (config->contains("hostname-char-set")) {
            hostname_char_set = getString(config, "hostname-char-set");
            owner->setHostnameCharSet(hostname_char_set);
        }

        std::string hostname_char_replacement;
        if (config->contains("hostname-char-replacement")) {
            hostname_char_replacement = getString(config, "hostname-char-replacement");
            owner->setHostnameCharReplacement(hostname_char_replacement);
        }

        // We need to validate sanitizer values here so we can detect problems and
        // cause a configuration.  We don't retain the compilation because it's not
        // something we can inherit.
        if (!hostname_char_set.empty()) {
            try {
                util::str::StringSanitizerPtr sanitizer(
                    new util::str::StringSanitizer(hostname_char_set,
                                                   hostname_char_replacement));
            } catch (const std::exception& ex) {
                isc_throw(BadValue, "hostname-char-set '" << hostname_char_set
                          << "' is not a valid regular expression");
            }
        }

        if (config->contains("ddns-update-on-renew")) {
            owner->setDdnsUpdateOnRenew(getBoolean(config, "ddns-update-on-renew"));
        }

        bool has_ddns_ttl = false;
        uint32_t ddns_ttl = 0;
        if (config->contains("ddns-ttl")) {
            ddns_ttl = getInteger(config, "ddns-ttl");
            owner->setDdnsTtl(ddns_ttl);
            has_ddns_ttl = true;
        }

        if (config->contains("ddns-ttl-percent")) {
            if (has_ddns_ttl) {
                isc_throw(BadValue, "cannot specify both ddns-ttl-percent and ddns-ttl");
            }

            owner->setDdnsTtlPercent(getDouble(config, "ddns-ttl-percent"));
        }

        uint32_t ddns_ttl_min = 0;
        if (config->contains("ddns-ttl-min")) {
            if (has_ddns_ttl) {
                isc_throw(BadValue, "cannot specify both ddns-ttl-min and ddns-ttl");
            }

            ddns_ttl_min = getInteger(config, "ddns-ttl-min");
            owner->setDdnsTtlMin(ddns_ttl_min);
        }

        if (config->contains("ddns-ttl-max")) {
            if (has_ddns_ttl) {
                isc_throw(BadValue, "cannot specify both ddns-ttl-max and ddns-ttl");
            }

            uint32_t ddns_ttl_max = getInteger(config, "ddns-ttl-max");
            if (ddns_ttl_max < ddns_ttl_min) {
                isc_throw(BadValue, "ddns-ttl-max: " << ddns_ttl_max
                          << " must be greater than ddns-ttl-min: " <<  ddns_ttl_min);
            }

            owner->setDdnsTtlMax(ddns_ttl_max);
        }

        // For backward compatibility, ddns-conflict-resolution-mode is optional.
        if (config->contains("ddns-conflict-resolution-mode")) {
            owner->setDdnsConflictResolutionMode(getString(config,
                                                           "ddns-conflict-resolution-mode"));
        }
    }
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
