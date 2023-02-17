// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_SERVICE_SIGNAL_H
#define IO_SERVICE_SIGNAL_H

#include <asiolink/io_service.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace asiolink {

/// @brief Defines a handler function for an IOSignal.
typedef std::function<void(int signum)> IOSignalHandler;

class IOSignalSetImpl;

/// @brief Implements an asynchronous "signal" for IOService driven processing
///
/// This class allows a OS signal such as SIGHUP to propagated to an IOService
/// as a ready event with a callback using boost ASIO.
class IOSignalSet {
public:
    /// @brief Constructor.
    ///
    /// @param io_service IOService to which to send the signal.
    /// @param handler Handler to call when a signal is received.
    IOSignalSet(asiolink::IOServicePtr io_service, IOSignalHandler handler);

    /// @brief Destructor.
    ~IOSignalSet();

    /// @brief Add a signal to the list of signals to handle.
    ///
    /// @param signum Signal number.
    /// @throw Unexpected on error.
    void add(int signum);

    /// @brief Remove a signal from the list of signals to handle.
    ///
    /// @param signum Signal number.
    /// @throw Unexpected on error.
    void remove(int signum);

private:
    /// @brief Pointer to the implementation.
    boost::shared_ptr<IOSignalSetImpl> impl_;
};

/// @brief Defines a pointer to an IOSignalSet.
typedef boost::shared_ptr<IOSignalSet> IOSignalSetPtr;

} // namespace asiolink
} // namespace isc

#endif // IO_SERVICE_SIGNAL_H
