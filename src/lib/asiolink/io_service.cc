// Copyright (C) 2011, 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <unistd.h>             // for some IPC/network system calls
#include <netinet/in.h>
#include <sys/socket.h>

#include <boost/asio.hpp>
#include <asiolink/io_service.h>

namespace isc {
namespace asiolink {

namespace {
// A trivial wrapper for boost::function.  SunStudio doesn't seem to be capable
// of handling a boost::function object if directly passed to
// io_service::post().
class CallbackWrapper {
public:
    CallbackWrapper(const boost::function<void()>& callback) :
        callback_(callback)
    {}
    void operator()() {
        callback_();
    }
private:
    boost::function<void()> callback_;
};
}

class IOServiceImpl {
private:
    IOServiceImpl(const IOService& source);
    IOServiceImpl& operator=(const IOService& source);
public:
    /// \brief The constructor
    IOServiceImpl() :
        io_service_(),
        work_(io_service_)
    {};
    /// \brief The destructor.
    ~IOServiceImpl() {};
    //@}

    /// \brief Start the underlying event loop.
    ///
    /// This method does not return control to the caller until
    /// the \c stop() method is called via some handler.
    void run() {
        io_service_.run();
    };

    /// \brief Run the underlying event loop for a single event.
    ///
    /// This method return control to the caller as soon as the
    /// first handler has completed.  (If no handlers are ready when
    /// it is run, it will block until one is.)
    void run_one() {
        io_service_.run_one();
    };

    /// \brief Run the underlying event loop for a ready events.
    ///
    /// This method executes handlers for all ready events and returns.
    /// It will return immediately if there are no ready events.
    void poll() {
        io_service_.poll();
    };

    /// \brief Stop the underlying event loop.
    ///
    /// This will return the control to the caller of the \c run() method.
    void stop() { io_service_.stop();} ;

    /// \brief Return the native \c io_service object used in this wrapper.
    ///
    /// This is a short term work around to support other Kea modules
    /// that share the same \c io_service with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    boost::asio::io_service& get_io_service() { return io_service_; };
    void post(const boost::function<void ()>& callback) {
        const CallbackWrapper wrapper(callback);
        io_service_.post(wrapper);
    }
private:
    boost::asio::io_service io_service_;
    boost::asio::io_service::work work_;
};

IOService::IOService() {
    io_impl_ = new IOServiceImpl();
}

IOService::~IOService() {
    delete io_impl_;
}

void
IOService::run() {
    io_impl_->run();
}

void
IOService::run_one() {
    io_impl_->run_one();
}

void
IOService::poll() {
    io_impl_->poll();
}

void
IOService::stop() {
    io_impl_->stop();
}

boost::asio::io_service&
IOService::get_io_service() {
    return (io_impl_->get_io_service());
}

void
IOService::post(const boost::function<void ()>& callback) {
    return (io_impl_->post(callback));
}

} // namespace asiolink
} // namespace isc
