// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/triplet.h>
#include <dhcpsrv/parsers/base_network_parser.h>
#include <util/optional.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

void
BaseNetworkParser::parseCommonTimers(const ConstElementPtr& network_data,
                                     NetworkPtr& network) {
    Triplet<uint32_t> t1;
    if (network_data->contains("renew-timer")) {
        network->setT1(getInteger(network_data, "renew-timer"));
    }

    Triplet<uint32_t> t2;
    if (network_data->contains("rebind-timer")) {
        network->setT2(getInteger(network_data, "rebind-timer"));
    }

    Triplet<uint32_t> valid;
    if (network_data->contains("valid-lifetime")) {
        network->setValid(getInteger(network_data, "valid-lifetime"));
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
BaseNetworkParser::parseHostReservationMode(const data::ConstElementPtr& network_data,
                                            NetworkPtr& network) {
    if (network_data->contains("reservation-mode")) {
        try {
            std::string hr_mode = getString(network_data, "reservation-mode");
            network->setHostReservationMode(Network::hrModeFromString(hr_mode));
        } catch (const BadValue& ex) {
            isc_throw(DhcpConfigError, "invalid reservation-mode parameter: "
                      << ex.what() << " (" << getPosition("reservation-mode",
                                                          network_data) << ")");
        }
    }
}



} // end of namespace isc::dhcp
} // end of namespace isc
