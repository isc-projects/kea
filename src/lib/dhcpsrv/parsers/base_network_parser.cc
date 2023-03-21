// Copyright (C) 2019-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/triplet.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/base_network_parser.h>
#include <util/optional.h>
#include <util/strutil.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

void
BaseNetworkParser::moveReservationMode(ElementPtr config) {
    if (!config->contains("reservation-mode")) {
        return;
    }
    if (config->contains("reservations-global") ||
        config->contains("reservations-in-subnet") ||
        config->contains("reservations-out-of-pool")) {
        isc_throw(DhcpConfigError, "invalid use of both 'reservation-mode'"
                  " and one of 'reservations-global', 'reservations-in-subnet'"
                  " or 'reservations-out-of-pool' parameters");
    }
    std::string hr_mode = getString(config, "reservation-mode");
    if ((hr_mode == "disabled") || (hr_mode == "off")) {
        config->set("reservations-global", Element::create(false));
        config->set("reservations-in-subnet", Element::create(false));
    } else if (hr_mode == "out-of-pool") {
        config->set("reservations-global", Element::create(false));
        config->set("reservations-in-subnet", Element::create(true));
        config->set("reservations-out-of-pool", Element::create(true));
    } else if (hr_mode == "global") {
        config->set("reservations-global", Element::create(true));
        config->set("reservations-in-subnet", Element::create(false));
    } else if (hr_mode == "all") {
        config->set("reservations-global", Element::create(false));
        config->set("reservations-in-subnet", Element::create(true));
        config->set("reservations-out-of-pool", Element::create(false));
    } else {
        isc_throw(DhcpConfigError, "invalid reservation-mode parameter: '"
                  << hr_mode << "' ("
                  << getPosition("reservation-mode", config) << ")");
    }
    config->remove("reservation-mode");
}

void
BaseNetworkParser::moveReservationMode(CfgGlobalsPtr config) {
    if (!config->get(CfgGlobals::RESERVATION_MODE)) {
        return;
    }
    if (config->get(CfgGlobals::RESERVATIONS_GLOBAL) ||
        config->get(CfgGlobals::RESERVATIONS_IN_SUBNET) ||
        config->get(CfgGlobals::RESERVATIONS_OUT_OF_POOL)) {
        isc_throw(DhcpConfigError, "invalid use of both 'reservation-mode'"
                  " and one of 'reservations-global', 'reservations-in-subnet'"
                  " or 'reservations-out-of-pool' parameters");
    }
    std::string hr_mode = config->get(CfgGlobals::RESERVATION_MODE)->stringValue();
    if ((hr_mode == "disabled") || (hr_mode == "off")) {
        config->set(CfgGlobals::RESERVATIONS_GLOBAL, Element::create(false));
        config->set(CfgGlobals::RESERVATIONS_IN_SUBNET, Element::create(false));
    } else if (hr_mode == "out-of-pool") {
        config->set(CfgGlobals::RESERVATIONS_GLOBAL, Element::create(false));
        config->set(CfgGlobals::RESERVATIONS_IN_SUBNET, Element::create(true));
        config->set(CfgGlobals::RESERVATIONS_OUT_OF_POOL, Element::create(true));
    } else if (hr_mode == "global") {
        config->set(CfgGlobals::RESERVATIONS_GLOBAL, Element::create(true));
        config->set(CfgGlobals::RESERVATIONS_IN_SUBNET, Element::create(false));
    } else if (hr_mode == "all") {
        config->set(CfgGlobals::RESERVATIONS_GLOBAL, Element::create(false));
        config->set(CfgGlobals::RESERVATIONS_IN_SUBNET, Element::create(true));
        config->set("reservations-out-of-pool", Element::create(false));
    } else {
        isc_throw(DhcpConfigError, "invalid reservation-mode parameter: '"
                  << hr_mode << "' ("
                  << config->get(CfgGlobals::RESERVATION_MODE)->getPosition()
                  << ")");
    }
    config->set(CfgGlobals::RESERVATION_MODE, ConstElementPtr());
}

void
BaseNetworkParser::parseCommon(const ConstElementPtr& network_data,
                               NetworkPtr& network) {
    bool has_renew = network_data->contains("renew-timer");
    bool has_rebind = network_data->contains("rebind-timer");
    int64_t renew = -1;
    int64_t rebind = -1;

    if (has_renew) {
        renew = getInteger(network_data, "renew-timer");
        if (renew < 0) {
            isc_throw(DhcpConfigError, "the value of renew-timer ("
                      << renew << ") must be a positive number");
        }
        network->setT1(renew);
    }

    if (has_rebind) {
        rebind = getInteger(network_data, "rebind-timer");
        if (rebind < 0) {
            isc_throw(DhcpConfigError, "the value of rebind-timer ("
                      << rebind << ") must be a positive number");
        }
        network->setT2(rebind);
    }

    if (has_renew && has_rebind && (renew > rebind)) {
        // The renew-timer value is too large and server logic
        // later on will end up not sending it. Warn the user but
        // allow the configuration to pass.
        LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_RENEW_GTR_REBIND)
                 .arg(network->getLabel())
                 .arg(renew)
                 .arg(rebind);
    }

    network->setValid(parseIntTriplet(network_data, "valid-lifetime"));

    if (network_data->contains("store-extended-info")) {
        network->setStoreExtendedInfo(getBoolean(network_data,
                                                 "store-extended-info"));
    }

    if (network_data->contains("reservations-global")) {
        network->setReservationsGlobal(getBoolean(network_data,
                                                  "reservations-global"));
    }

    if (network_data->contains("reservations-in-subnet")) {
        network->setReservationsInSubnet(getBoolean(network_data,
                                                    "reservations-in-subnet"));
    }

    if (network_data->contains("reservations-out-of-pool")) {
        network->setReservationsOutOfPool(getBoolean(network_data,
                                                     "reservations-out-of-pool"));
    }
}

void
BaseNetworkParser::parseTeePercents(const ConstElementPtr& network_data,
                                    NetworkPtr& network) {
    bool calculate_tee_times = network->getCalculateTeeTimes();
    if (network_data->contains("calculate-tee-times")) {
        calculate_tee_times = getBoolean(network_data, "calculate-tee-times");
        network->setCalculateTeeTimes(calculate_tee_times);
    }

    Optional<double> t2_percent;
    if (network_data->contains("t2-percent")) {
        t2_percent = getDouble(network_data, "t2-percent");
    }

    Optional<double> t1_percent;
    if (network_data->contains("t1-percent")) {
        t1_percent = getDouble(network_data, "t1-percent");
    }
    if (calculate_tee_times) {
        if (!t2_percent.unspecified() && ((t2_percent.get() <= 0.0) ||
                                          (t2_percent.get() >= 1.0))) {
            isc_throw(DhcpConfigError, "t2-percent:  " << t2_percent.get()
                      << " is invalid, it must be greater than 0.0 and less than 1.0");
        }

        if (!t1_percent.unspecified() && ((t1_percent.get() <= 0.0) ||
                                          (t1_percent.get() >= 1.0))) {
            isc_throw(DhcpConfigError, "t1-percent:  " << t1_percent.get()
                      << " is invalid it must be greater than 0.0 and less than 1.0");
        }

        if (!t1_percent.unspecified() && !t2_percent.unspecified() &&
            (t1_percent.get() >= t2_percent.get())) {
            isc_throw(DhcpConfigError, "t1-percent:  " << t1_percent.get()
                      << " is invalid, it must be less than t2-percent: "
                      << t2_percent.get());
        }
    }

    network->setT2Percent(t2_percent);
    network->setT1Percent(t1_percent);
}

void
BaseNetworkParser::parseCacheParams(const ConstElementPtr& network_data,
                                    NetworkPtr& network) {
    if (network_data->contains("cache-threshold")) {
        double cache_threshold = getDouble(network_data, "cache-threshold");
        if ((cache_threshold <= 0.0) || (cache_threshold >= 1.0)) {
            isc_throw(DhcpConfigError, "cache-threshold: " << cache_threshold
                      << " is invalid, it must be greater than 0.0 and less than 1.0");
        }
        network->setCacheThreshold(cache_threshold);
    }

    if (network_data->contains("cache-max-age")) {
        network->setCacheMaxAge(getInteger(network_data, "cache-max-age"));
    }
}

void
BaseNetworkParser::parseDdnsParams(const data::ConstElementPtr& network_data,
                                   NetworkPtr& network) {

    if (network_data->contains("ddns-send-updates")) {
        network->setDdnsSendUpdates(getBoolean(network_data, "ddns-send-updates"));
    }

    if (network_data->contains("ddns-override-no-update")) {
        network->setDdnsOverrideNoUpdate(getBoolean(network_data, "ddns-override-no-update"));
    }

    if (network_data->contains("ddns-override-client-update")) {
        network->setDdnsOverrideClientUpdate(getBoolean(network_data, "ddns-override-client-update"));
    }

    if (network_data->contains("ddns-replace-client-name")) {
        network->setDdnsReplaceClientNameMode(getAndConvert<D2ClientConfig::ReplaceClientNameMode,
                                                            D2ClientConfig::stringToReplaceClientNameMode>
                                                            (network_data, "ddns-replace-client-name",
                                                             "ReplaceClientName mode"));
    }

    if (network_data->contains("ddns-generated-prefix")) {
        network->setDdnsGeneratedPrefix(getString(network_data, "ddns-generated-prefix"));
    }

    if (network_data->contains("ddns-qualifying-suffix")) {
        network->setDdnsQualifyingSuffix(getString(network_data, "ddns-qualifying-suffix"));
    }

    std::string hostname_char_set;
    if (network_data->contains("hostname-char-set")) {
        hostname_char_set = getString(network_data, "hostname-char-set");
        network->setHostnameCharSet(hostname_char_set);
    }

    std::string hostname_char_replacement;
    if (network_data->contains("hostname-char-replacement")) {
        hostname_char_replacement = getString(network_data, "hostname-char-replacement");
        network->setHostnameCharReplacement(hostname_char_replacement);
    }

    // We need to validate sanitizer values here so we can detect problems and
    // cause a configuration.  We don't retain the compilation because it's not
    // something we can inherit.
    if (!hostname_char_set.empty()) {
        try {
            str::StringSanitizerPtr sanitizer(new str::StringSanitizer(hostname_char_set,
                                                                       hostname_char_replacement));
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "hostname-char-set '" << hostname_char_set
                      << "' is not a valid regular expression");
        }
    }

    if (network_data->contains("ddns-update-on-renew")) {
        network->setDdnsUpdateOnRenew(getBoolean(network_data, "ddns-update-on-renew"));
    }

    if (network_data->contains("ddns-use-conflict-resolution")) {
        network->setDdnsUseConflictResolution(getBoolean(network_data, "ddns-use-conflict-resolution"));
    }

    if (network_data->contains("ddns-ttl-percent")) {
        network->setDdnsTtlPercent(getDouble(network_data, "ddns-ttl-percent"));
    }
}

void
BaseNetworkParser::parseAllocatorParams(const data::ConstElementPtr& network_data,
                                        NetworkPtr& network) {
    if (network_data->contains("allocator")) {
        auto allocator_type = getString(network_data, "allocator");
        if ((allocator_type != "iterative") && (allocator_type != "random")) {
            // Unsupported allocator type used.
            isc_throw(DhcpConfigError, "supported allocators are: iterative and random");
        }
        network->setAllocatorType(allocator_type);
    }
}

void
BaseNetworkParser::parsePdAllocatorParams(const data::ConstElementPtr& network_data,
                                          Network6Ptr& network) {
    if (network_data->contains("pd-allocator")) {
        auto allocator_type = getString(network_data, "pd-allocator");
        if ((allocator_type != "iterative") && (allocator_type != "random")) {
            // Unsupported allocator type used.
            isc_throw(DhcpConfigError, "supported allocators are: iterative and random");
        }
        network->setPdAllocatorType(allocator_type);
    }
}

void
BaseNetworkParser::parseOfferLft(const data::ConstElementPtr& network_data,
                                        Network4Ptr& network) {
    if (network_data->contains("offer-lifetime")) {
        auto value = getInteger(network_data, "offer-lifetime");
        if (value < 0) {
            isc_throw(DhcpConfigError, "the value of offer-lifetime '"
                      << value << "' must be a positive number ("
                      << getPosition("offer-lifetime", network_data) << ")");
        }

        network->setOfferLft(value);
    }
}


} // end of namespace isc::dhcp
} // end of namespace isc
