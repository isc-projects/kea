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
        tc_(options, socket) {};

    /// \brief Run performance test.
    ///
    /// Method runs whole performance test.
    ///
    /// \return execution status.
    virtual int run() = 0;

    /// \brief Trivial virtual destructor.
    virtual ~AbstractScen() {};

protected:
    CommandOptions& options_;
    TestControl tc_;  ///< Object for controling sending and receiving packets.
};


}
}

#endif // ABSTRACT_SCEN_H
