// Copyright (C) 2011-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>

#include <unistd.h>             // for some IPC/network system calls
#include <netinet/in.h>
#include <boost/shared_ptr.hpp>
#include <sys/socket.h>

namespace isc {
namespace asiolink {

class IOServiceImpl {
    /// @brief Constructors and Destructor.
    ///
    /// @note The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOServiceImpl(const IOService& source);
    IOServiceImpl& operator=(const IOService& source);
public:
    /// @brief The constructor.
    IOServiceImpl() :
        io_service_(),
        work_(boost::asio::make_work_guard(io_service_)) {
    };

    /// @brief The destructor.
    ~IOServiceImpl() = default;
    //@}

    /// @brief Start the underlying event loop.
    ///
    /// This method does not return control to the caller until
    /// the @ref stop() or @ref stopWork() method is called via some handler.
    void run() {
        io_service_.run();
    };

    /// @brief Run the underlying event loop for a single event.
    ///
    /// This method return control to the caller as soon as the
    /// first handler has completed.  (If no handlers are ready when
    /// it is run, it will block until one is.)
    ///
    /// @return The number of handlers that were executed.
    size_t runOne() {
        return (static_cast<size_t>(io_service_.run_one()));
    };

    /// @brief Run the underlying event loop for a ready events.
    ///
    /// This method executes handlers for all ready events and returns.
    /// It will return immediately if there are no ready events.
    ///
    /// @return The number of handlers that were executed.
    size_t poll() {
        return (static_cast<size_t>(io_service_.poll()));
    };

    /// @brief Run the underlying event loop for a ready events.
    ///
    /// This method executes handlers for all ready events and returns.
    /// It will return immediately if there are no ready events.
    ///
    /// @return The number of handlers that were executed.
    size_t pollOne() {
        return (static_cast<size_t>(io_service_.poll_one()));
    };

    /// @brief Stop the underlying event loop.
    ///
    /// This will return the control to the caller of the @ref run() method.
    void stop() {
        io_service_.stop();
    }

    /// @brief Indicates if the IOService has been stopped.
    ///
    /// @return true if the IOService has been stopped, false otherwise.
    bool stopped() const {
        return (io_service_.stopped());
    }

    /// @brief Restarts the IOService in preparation for a subsequent @ref run() invocation.
    void restart() {
        io_service_.restart();
    }

    /// @brief Removes IO service work object to let it finish running
    /// when all handlers have been invoked.
    void stopWork() {
        work_.reset();
    }

    /// @brief Return the native @c io_context object used in this wrapper.
    ///
    /// This is a short term work around to support other Kea modules
    /// that share the same @c io_context with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    boost::asio::io_context& getInternalIOService() {
        return (io_service_);
    }

    /// @brief Post a callback on the IO service.
    ///
    /// @param callback The callback to be run on the IO service.
    void post(const std::function<void ()>& callback) {
        boost::asio::post(io_service_, callback);
    }

private:
    boost::asio::io_context io_service_;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_;
};

IOService::IOService() : io_impl_(new IOServiceImpl()) {
}

IOService::~IOService() {
}

void
IOService::run() {
    io_impl_->run();
}

size_t
IOService::runOne() {
    return (io_impl_->runOne());
}

size_t
IOService::poll() {
    return (io_impl_->poll());
}

size_t
IOService::pollOne() {
    return (io_impl_->pollOne());
}

void
IOService::stop() {
    io_impl_->stop();
}

bool
IOService::stopped() const {
    return (io_impl_->stopped());
}

void
IOService::restart() {
    io_impl_->restart();
}

void
IOService::stopWork() {
    io_impl_->stopWork();
}

boost::asio::io_context&
IOService::getInternalIOService() {
    return (io_impl_->getInternalIOService());
}

void
IOService::post(const std::function<void ()>& callback) {
    return (io_impl_->post(callback));
}

void
IOService::stopAndPoll(bool ignore_errors) {
    stop();
    restart();
    if (ignore_errors) {
        try {
            poll();
        } catch (...) {
            // Ignore all exceptions.
        }
    } else {
        poll();
    }
}

}  // namespace asiolink
}  // namespace isc
