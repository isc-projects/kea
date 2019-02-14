// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef AVALANCHE_SCEN_H
#define AVALANCHE_SCEN_H

#include <config.h>

#include <perfdhcp/abstract_scen.h>


namespace isc {
namespace perfdhcp {


/// \brief Avalanche Scenario class.
///
/// This class is used to run the performance test where DHCP server
/// is first loaded with indicated bumer of Discover or Solicit messages
/// and then the class is waiting till receiving all required responses.
/// Full DORA and SARR message sequences are expected.
class AvalancheScen : public AbstractScen {
public:
    /// Default and the only constructor of AvalancheScen.
    AvalancheScen(): total_resent_(0) {};

    /// brief\ Run performance test.
    ///
    /// Method runs whole performance test.
    int run();

private:

    /// A map xchg type -> (a map of trans id -> retransmissions count.
    std::unordered_map<ExchangeType, std::unordered_map<uint32_t, int>> retransmissions_;
    /// A map xchg type -> (a map of trans id -> time of sending first packet.
    std::unordered_map<ExchangeType, std::unordered_map<uint32_t, boost::posix_time::ptime>> start_times_;

    /// Total number of resent packets.
    int total_resent_;

    /// Resend packets for given exchange type that did not receive
    /// a response yet.
    int resendPackets(ExchangeType xchg_type);

};

}
}

#endif // AVALANCHE_SCEN_H
