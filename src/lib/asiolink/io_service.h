// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ASIOLINK_IO_SERVICE_H
#define ASIOLINK_IO_SERVICE_H

#include <boost/version.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>

namespace boost {
namespace asio {
#if BOOST_VERSION < 106600
    class io_service;
#else
    class io_context;
    typedef io_context io_service;
#endif
}
}

namespace isc {
namespace asiolink {

class IOServiceImpl;

/// \brief The \c IOService class is a wrapper for the ASIO \c io_service
/// class.
///
class IOService {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOService(const IOService& source);
    IOService& operator=(const IOService& source);
public:
    /// \brief The constructor
    IOService();
    /// \brief The destructor.
    ~IOService();
    //@}

    /// \brief Start the underlying event loop.
    ///
    /// This method does not return control to the caller until
    /// the \c stop() method is called via some handler.
    void run();

    /// \brief Run the underlying event loop for a single event.
    ///
    /// This method return control to the caller as soon as the
    /// first handler has completed.  (If no handlers are ready when
    /// it is run, it will block until one is.)
    void run_one();

    /// \brief Run the underlying event loop for a ready events.
    ///
    /// This method executes handlers for all ready events and returns.
    /// It will return immediately if there are no ready events.
    void poll();

    /// \brief Stop the underlying event loop.
    ///
    /// This will return the control to the caller of the \c run() method.
    void stop();

    /// \brief Indicates if the IOService has been stopped.
    ///
    /// \return true if the IOService has been stopped, false otherwise.
    bool stopped() const;

    /// \brief Restarts the IOService in preparation for a subsequent \c run() invocation.
    void restart();

    /// \brief Removes IO service work object to let it finish running
    /// when all handlers have been invoked.
    void stopWork();

    /// \brief Return the native \c io_service object used in this wrapper.
    ///
    /// This is a short term work around to support other Kea modules
    /// that share the same \c io_service with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    boost::asio::io_service& get_io_service();

    /// \brief Post a callback to the end of the queue.
    ///
    /// Requests the callback be called sometime later. It is not guaranteed
    /// by the underlying asio, but it can reasonably be expected the callback
    /// is put to the end of the callback queue. It is not called from within
    /// this function.
    ///
    /// It may be used to implement "background" work, for example (doing stuff
    /// by small bits that are called from time to time).
    void post(const std::function<void ()>& callback);

private:
    boost::shared_ptr<IOServiceImpl> io_impl_;
};

/// @brief Defines a smart pointer to an IOService instance.
typedef boost::shared_ptr<IOService> IOServicePtr;

} // namespace asiolink
} // namespace isc
#endif // ASIOLINK_IO_SERVICE_H
