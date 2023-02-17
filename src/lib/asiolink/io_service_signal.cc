// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_signal.h>
#include <exceptions/exceptions.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio/signal_set.hpp>
#include <functional>

namespace ph = std::placeholders;

namespace isc {
namespace asiolink {

/// @brief Implementation class of IOSignalSet.
class IOSignalSetImpl : public boost::enable_shared_from_this<IOSignalSetImpl>,
                        public boost::noncopyable {
public:
    /// @brief Constructor.
    ///
    /// @param io_service the process IO service.
    /// @param handler the signal handler.
    IOSignalSetImpl(IOServicePtr io_service, IOSignalHandler handler);

    /// @brief Destructor.
    ~IOSignalSetImpl();

    /// @brief Install the callback on the IO service queue.
    void install();

    /// @brief Add a signal to the ASIO signal set.
    ///
    /// @param signum the signal number.
    void add(int signum);

    /// @brief Remove a signal from the ASIO signal set.
    ///
    /// @param signum the signal number.
    void remove(int signum);

    /// @brief Cancel the remaining installed signal handler callbacks.
    void cancel();

private:
    /// @brief Extends the lifetime of IOService to avoid heap-use-after-free.
    IOServicePtr io_service_;

    /// @brief the ASIO signal set.
    boost::asio::signal_set signal_set_;

    /// @brief the signal handler.
    IOSignalHandler handler_;

    /// @brief the callback (called on cancel or received signal).
    ///
    /// The callback is installed on the IO service queue and calls
    /// the handler if the operation was not aborted.
    void callback(const boost::system::error_code& ec, int signum);
};

IOSignalSetImpl::IOSignalSetImpl(IOServicePtr io_service,
                                 IOSignalHandler handler)
    : io_service_(io_service),
      signal_set_(io_service_->get_io_service()),
      handler_(handler) {
}

IOSignalSetImpl::~IOSignalSetImpl() {
    handler_ = IOSignalHandler();
}

void
IOSignalSetImpl::cancel() {
    signal_set_.cancel();
}

void
IOSignalSetImpl::callback(const boost::system::error_code& ec, int signum) {
    if (ec && ec.value() == boost::asio::error::operation_aborted) {
        return;
    }
    install();
    if (!ec && (signum > 0)) {
        try {
            handler_(signum);
        } catch (const std::exception& ex) {
        }
    }
}

void
IOSignalSetImpl::install() {
    signal_set_.async_wait(std::bind(&IOSignalSetImpl::callback,
                                     shared_from_this(),
                                     ph::_1, ph::_2));
}

void
IOSignalSetImpl::add(int signum) {
    try {
        signal_set_.add(signum);
    } catch (const boost::system::system_error& ex) {
        isc_throw(isc::Unexpected,
                  "Failed to add signal " << signum << ": " << ex.what());
    }
}

void
IOSignalSetImpl::remove(int signum) {
    try {
        signal_set_.remove(signum);
    } catch (const boost::system::system_error& ex) {
        isc_throw(isc::Unexpected,
                  "Failed to remove signal " << signum << ": " << ex.what());
    }
}

IOSignalSet::IOSignalSet(IOServicePtr io_service, IOSignalHandler handler) :
    impl_(new IOSignalSetImpl(io_service, handler)) {
    // It can throw but the error is fatal...
    impl_->install();
}

IOSignalSet::~IOSignalSet() {
    impl_->cancel();
}

void
IOSignalSet::add(int signum) {
    impl_->add(signum);
}

void
IOSignalSet::remove(int signum) {
    impl_->remove(signum);
}

} // namespace asiolink
} // namespace isc
