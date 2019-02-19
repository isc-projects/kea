// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ABSTRACT_SCEN_H
#define ABSTRACT_SCEN_H


#include <perfdhcp/test_control.h>


namespace isc {
namespace perfdhcp {


/// \brief Abstract Scenario class.
///
/// This class must be inherited by scenario classes.
class AbstractScen : public boost::noncopyable {
public:
    /// \brief Default and the only constructor of AbstractScen.
    ///
    /// \param options reference to command options,
    /// \param socket reference to a socket.
    AbstractScen(CommandOptions& options, BasePerfSocket &socket) :
        options_(options),
        tc_(options, socket)
    {
        if (options_.getIpVersion() == 4) {
            stage1_xchg_ = ExchangeType::DO;
            stage2_xchg_ = ExchangeType::RA;
        } else {
            stage1_xchg_ = ExchangeType::SA;
            stage2_xchg_ = ExchangeType::RR;
        }
    };

    /// \brief Run performance test.
    ///
    /// Method runs whole performance test.
    ///
    /// \return execution status.
    virtual int run() = 0;

    /// \brief Trivial virtual destructor.
    virtual ~AbstractScen() {};

protected:
    CommandOptions& options_; ///< Reference to commandline options.
    TestControl tc_;  ///< Object for controling sending and receiving packets.

    // Helper fields to avoid checking IP version each time an exchange type
    // is needed.
    ExchangeType stage1_xchg_;
    ExchangeType stage2_xchg_;
};


}
}

#endif // ABSTRACT_SCEN_H
