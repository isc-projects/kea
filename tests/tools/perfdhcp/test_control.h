// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef __TEST_CONTROL_H
#define __TEST_CONTROL_H

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

namespace isc {
namespace perfdhcp {

/// \brief Test Control class.
///
/// This class is responsible for running whole perfdhcp test.
///
class TestControl : public boost::noncopyable {
public:
    /// TestControl is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// \return the only existing instance of test control
    static TestControl& instance();

    /// Run performance test.
    ///
    /// Method runs whole performance test. Command line options must
    /// be parsed prior to running this function. Othewise function will
    /// throw exception.
    ///
    /// \throw isc::InvalidOperation if command line options are not parsed.
    /// \throw isc::Unexpected if internal Test Controler error occured.
    void run();

private:

    /// \brief Private default constructor.
    ///
    /// Default constructor is private as the object can be created
    /// only via \ref instance method.
    TestControl();

    /// \brief Check if test exit condtitions fulfiled.
    ///
    /// Method checks if test exit conditions are fulfiled.
    /// Exit conditions are checked periodically from the
    /// main loop. Program should break the main loop when
    /// this method returns true. It is calling function
    /// responsibility to break main loop gracefully and
    /// cleanup after test execution.
    ///
    /// \return true if any of the exit conditions is fulfiled.
    bool checkExitConditions() const;

    dhcp::Pkt4* createDiscoverPkt4();

    static dhcp::OptionPtr factoryRequestList4(dhcp::Option::Universe u,
                                               uint16_t type,
                                               const dhcp::OptionBuffer& buf);

    /// \brief Returns number of exchanges to be started.
    ///
    /// Method returns number of new exchanges to be started as soon
    /// as possible to satisfy expected rate. Calculation used here
    /// is based on current time, due time calculated with
    /// \ref updateSendTime function and expected rate.
    ///
    /// \return number of exchanges to be started immediatelly.
    uint64_t getNextExchangesNum() const;

    void registerOptionFactories4() const;

    void registerOptionFactories6() const;

    void registerOptionFactories() const;

    /// \brief Start new exchange of DHCP messages.
    ///
    void startExchange();

    /// \brief Update due time to initiate next chunk of exchanges.
    ///
    /// Method updates due time to initiate next chunk of exchanges.
    /// Function takes current time, last sent packet's time and
    /// expected rate in its calculations.
    void updateSendDue();

    boost::posix_time::ptime send_due_;    ///< Due time to initiate next chunk
                                           ///< of exchanges.
    boost::posix_time::ptime last_sent_;   ///< Indicates when the last exchange
                                           /// was initiated.

    uint64_t sent_packets_0_;
    uint64_t sent_packets_1_;
};

} // namespace perfdhcp
} // namespace isc

#endif // __COMMAND_OPTIONS_H
