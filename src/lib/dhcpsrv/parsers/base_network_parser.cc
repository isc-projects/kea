// Copyright (C) 2019-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/triplet.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/base_network_parser.h>
#include <util/optional.h>
#include <util/str.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {


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
    parseDdnsParameters(network_data, network);
}

void
BaseNetworkParser::parseAllocatorParams(const data::ConstElementPtr& network_data,
                                        NetworkPtr& network) {
    if (network_data->contains("allocator")) {
        auto allocator_type = getString(network_data, "allocator");
        if ((allocator_type != "iterative") && (allocator_type != "random") &&
            (allocator_type != "flq")) {
            // Unsupported allocator type used.
            isc_throw(DhcpConfigError, "supported allocators are: iterative, random and flq");
        }
        network->setAllocatorType(allocator_type);
    }
}

void
BaseNetworkParser::parsePdAllocatorParams(const data::ConstElementPtr& network_data,
                                          Network6Ptr& network) {
    if (network_data->contains("pd-allocator")) {
        auto allocator_type = getString(network_data, "pd-allocator");
        if ((allocator_type != "iterative") && (allocator_type != "random") &&
            (allocator_type != "flq")) {
            // Unsupported allocator type used.
            isc_throw(DhcpConfigError, "supported allocators are: iterative, random and flq");
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

void
BaseNetworkParser::getAdditionalClassesElem(ConstElementPtr params,
                                            ClassAdderFunc adder_func) {
    // Try setting up additional client classes.
    ConstElementPtr req_class_list = params->get("require-client-classes");
    ConstElementPtr class_list = params->get("evaluate-additional-classes");
    if (req_class_list) {
        if (!class_list) {
            LOG_WARN(dhcpsrv_logger, DHCPSRV_REQUIRE_CLIENT_CLASSES_DEPRECATED);
            class_list = req_class_list;
        } else {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "cannot specify both 'require-client-classes' and "
                      "'evaluate-additional-classes'. Use only the latter.");
        }
    }

    if (class_list) {
        const std::vector<data::ElementPtr>& classes = class_list->listValue();
        for (auto const& cclass : classes) {
            if ((cclass->getType() != Element::string) ||
                cclass->stringValue().empty()) {
                isc_throw(DhcpConfigError, "invalid class name (" << cclass->getPosition() << ")");
            }

            (adder_func)(cclass->stringValue());
        }
    }
}

void
BaseNetworkParser::getClientClassesElem(ConstElementPtr params,
                                        ClassAdderFunc adder_func) {
    // Try setting up client client classes.
    ConstElementPtr class_elem = params->get("client-class");
    ConstElementPtr class_list = params->get("client-classes");
    if (class_elem) {
        if (!class_list) {
            LOG_WARN(dhcpsrv_logger, DHCPSRV_CLIENT_CLASS_DEPRECATED);
            if (class_elem->getType() != Element::string) {
                isc_throw(DhcpConfigError, "invalid class name (" << class_elem->getPosition() << ")");
            }

            if (!class_elem->stringValue().empty()) {
                (adder_func)(class_elem->stringValue());
            }
        } else {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "cannot specify both 'client-class' and "
                      "'client-classes'. Use only the latter.");
        }
    }

    if (class_list) {
        for (auto const& cclass : class_list->listValue()) {
            if ((cclass->getType() != Element::string) ||
                cclass->stringValue().empty()) {
                isc_throw(DhcpConfigError, "invalid class name (" << cclass->getPosition() << ")");
            }

            (adder_func)(cclass->stringValue());
        }
    }
}


} // end of namespace isc::dhcp
} // end of namespace isc
