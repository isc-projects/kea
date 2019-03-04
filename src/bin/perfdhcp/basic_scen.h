// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASIC_SCEN_H
#define BASIC_SCEN_H

#include <config.h>

#include <perfdhcp/abstract_scen.h>


namespace isc {
namespace perfdhcp {


/// \brief Basic Scenario class.
///
/// This class is used to run the performance test where DHCP server
/// is continuously loaded with DHCP messages according to given rate.
class BasicScen : public AbstractScen {
public:
    /// \brief Default and the only constructor of BasicScen.
    ///
    /// \param options reference to command options,
    /// \param socket reference to a socket.
    BasicScen(CommandOptions& options, BasePerfSocket &socket):
        AbstractScen(options, socket)
    {
        basic_rate_control_.setRate(options_.getRate());
        renew_rate_control_.setRate(options_.getRenewRate());
        release_rate_control_.setRate(options_.getReleaseRate());
    };

    /// brief\ Run performance test.
    ///
    /// Method runs whole performance test. Command line options must
    /// be parsed prior to running this function. Otherwise function will
    /// throw exception.
    ///
    /// \throw isc::InvalidOperation if command line options are not parsed.
    /// \throw isc::Unexpected if internal Test Controller error occurred.
    /// \return execution status.
    int run() override;

protected:
    /// \brief A rate control class for Discover and Solicit messages.
    RateControl basic_rate_control_;
    /// \brief A rate control class for Renew messages.
    RateControl renew_rate_control_;
    /// \brief A rate control class for Release messages.
    RateControl release_rate_control_;

    /// \brief Check if test exit conditions fulfilled.
    ///
    /// Method checks if the test exit conditions are fulfilled.
    /// Exit conditions are checked periodically from the
    /// main loop. Program should break the main loop when
    /// this method returns true. It is calling function
    /// responsibility to break main loop gracefully and
    /// cleanup after test execution.
    ///
    /// \return true if any of the exit conditions is fulfilled.
    bool checkExitConditions();
};

}
}

#endif // BASIC_SCEN_H
