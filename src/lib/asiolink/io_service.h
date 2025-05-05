// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ASIOLINK_IO_SERVICE_H
#define ASIOLINK_IO_SERVICE_H

#include <boost/version.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <list>

#if BOOST_VERSION < 106600
#error "Boost ASIO older than 1.66 are not supported"
#endif

#include <boost/asio/io_context.hpp>

namespace isc {
namespace asiolink {

class IOServiceImpl;
class IOService;

/// @brief Defines a smart pointer to an IOService instance.
typedef boost::shared_ptr<IOService> IOServicePtr;

/// @brief The @ref IOService class is a wrapper for the ASIO @c io_context
/// class.
class IOService {
    /// @brief Constructors and Destructor.
    ///
    /// @note The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOService(const IOService& source);
    IOService& operator=(const IOService& source);
public:
    /// @brief The constructor.
    IOService();

    /// @brief The destructor.
    ~IOService();
    //@}

    /// @brief Start the underlying event loop.
    ///
    /// This method does not return control to the caller until
    /// the @ref stop() or @ref stopWork() method is called via some handler.
    void run();

    /// @brief Run the underlying event loop for a single event.
    ///
    /// This method return control to the caller as soon as the
    /// first handler has completed.  (If no handlers are ready when
    /// it is run, it will block until one is.)
    ///
    /// @return The number of handlers that were executed.
    size_t runOne();

    /// @brief Run the underlying event loop for a ready events.
    ///
    /// This method executes handlers for all ready events and returns.
    /// It will return immediately if there are no ready events.
    ///
    /// @return The number of handlers that were executed.
    size_t poll();

    /// @brief Run the underlying event loop for a ready events.
    ///
    /// This method executes handlers for all ready events and returns.
    /// It will return immediately if there are no ready events.
    ///
    /// @return The number of handlers that were executed.
    size_t pollOne();

    /// @brief Stop the underlying event loop.
    ///
    /// This will return the control to the caller of the @ref run() method.
    void stop();

    /// @brief Indicates if the IOService has been stopped.
    ///
    /// @return true if the IOService has been stopped, false otherwise.
    bool stopped() const;

    /// @brief Restarts the IOService in preparation for a subsequent @ref run() invocation.
    void restart();

    /// @brief Removes IO service work object to let it finish running
    /// when all handlers have been invoked.
    void stopWork();

    /// @brief Return the native @c io_context object used in this wrapper.
    ///
    /// This is a short term work around to support other Kea modules
    /// that share the same @c io_context with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    ///
    /// @return The internal io_context object.
    boost::asio::io_context& getInternalIOService();

    /// @brief Post a callback to the end of the queue.
    ///
    /// Requests the callback be called sometime later. It is not guaranteed
    /// by the underlying asio, but it can reasonably be expected the callback
    /// is put to the end of the callback queue. It is not called from within
    /// this function.
    ///
    /// It may be used to implement "background" work, for example (doing stuff
    /// by small bits that are called from time to time).
    void post(const std::function<void ()>& callback);

    /// @brief Stop and poll to handle all registered events.
    ///
    /// @param ignore_errors Flag which indicates if errors should be ignored.
    void stopAndPoll(bool ignore_errors = true);

private:

    /// @brief The implementation.
    boost::shared_ptr<IOServiceImpl> io_impl_;
};

}  // namespace asiolink
}  // namespace isc

#endif // ASIOLINK_IO_SERVICE_H
