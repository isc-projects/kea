// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASIC_SCEN_H
#define BASIC_SCEN_H

#include <config.h>

#include <perfdhcp/test_control.h>


namespace isc {
namespace perfdhcp {


class BasicScen : public boost::noncopyable {
public:
    BasicScen() : tc_(false) {};

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

    /// \brief A rate control class for Discover and Solicit messages.
    RateControl basic_rate_control_;
    /// \brief A rate control class for Renew messages.
    RateControl renew_rate_control_;
    /// \brief A rate control class for Release messages.
    RateControl release_rate_control_;

    int resendPackets(ExchangeType xchg_type);

};

}
}

#endif // BASIC_SCEN_H
