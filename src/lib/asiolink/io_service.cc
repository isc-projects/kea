// Copyright (C) 2011, 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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
    explicit CallbackWrapper(const boost::function<void()>& callback) :
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
    explicit IOServiceImpl(const IOService& source);
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
