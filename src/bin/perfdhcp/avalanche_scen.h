// Copyright (C) 2012-2019,2021 Internet Systems Consortium, Inc. ("ISC")
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

// This class fixes an issue in older compilers
// that cannot handle enum class as key in std::unordered_map.
// See: https://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

/// \brief Avalanche Scenario class.
///
/// This class is used to run the performance test where DHCP server
/// is first loaded with indicated buffer of Discover or Solicit messages
/// and then the class is waiting till receiving all required responses.
/// Full DORA and SARR message sequences are expected.
class AvalancheScen : public AbstractScen {
public:
    /// \brief Default and the only constructor of AvalancheScen.
    ///
    /// \param options reference to command options,
    /// \param socket reference to a socket.
    AvalancheScen(CommandOptions& options, BasePerfSocket &socket):
        AbstractScen(options, socket),
        socket_(socket),
        total_resent_(0) {};

    /// brief\ Run performance test.
    ///
    /// Method runs whole performance test.
    ///
    /// \return execution status.
    int run() override;

protected:

    // A reference to socket;
    BasePerfSocket &socket_;

    /// A map xchg type -> (a map of trans id -> retransmissions count.
    std::unordered_map<ExchangeType, std::unordered_map<uint32_t, int>, EnumClassHash> retransmissions_;
    /// A map xchg type -> (a map of trans id -> time of sending first packet.
    std::unordered_map<ExchangeType, std::unordered_map<uint32_t, boost::posix_time::ptime>, EnumClassHash> start_times_;

    /// Total number of resent packets.
    int total_resent_;

    /// \\brief Resend packets.
    ///
    /// It resends packets for given exchange type that did not receive
    /// a response yet.
    ///
    /// \param xchg_type exchange type that should be looked for.
    /// \return number of packets still waiting for resending.
    int resendPackets(ExchangeType xchg_type);

};

}
}

#endif // AVALANCHE_SCEN_H
