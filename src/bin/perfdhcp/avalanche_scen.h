// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef AVALANCHE_SCEN_H
#define AVALANCHE_SCEN_H

#include <config.h>

#include <perfdhcp/test_control.h>


namespace isc {
namespace perfdhcp {


class AvalancheScen : public boost::noncopyable {
public:
    AvalancheScen(): total_resent_(0) {};

    /// brief\ Run performance test.
    ///
    /// Method runs whole performance test. Command line options must
    /// be parsed prior to running this function. Otherwise function will
    /// throw exception.
    ///
    /// \throw isc::InvalidOperation if command line options are not parsed.
    /// \throw isc::Unexpected if internal Test Controller error occurred.
    /// \return error_code, 3 if number of received packets is not equal
    /// to number of sent packets, 0 if everything is ok.
    int run();

private:
    TestControl tc_;

    std::unordered_map<ExchangeType, std::unordered_map<uint32_t, int>> retransmissions_;
    std::unordered_map<ExchangeType, std::unordered_map<uint32_t, boost::posix_time::ptime>> start_times_;
    int total_resent_;

    int resendPackets(ExchangeType xchg_type);

};

}
}

#endif // AVALANCHE_SCEN_H
