// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <process/d_log.h>
#include <process/io_service_signal.h>
#include <exceptions/exceptions.h>

#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/signal_set.hpp>

using namespace isc::asiolink;

namespace isc {
namespace process {

/// Implementation class of IOSignalSet.
class IOSignalSetImpl :
        public boost::enable_shared_from_this<IOSignalSetImpl>
{
private:
    // Prohibit copy.
    IOSignalSetImpl(const IOSignalSetImpl& source);
    IOSignalSetImpl& operator=(const IOSignalSetImpl& source);
public:
    IOSignalSetImpl(IOServicePtr io_service, IOSignalHandler handler);
    ~IOSignalSetImpl(){}
    void install();
    void add(int signum);
 private:
    boost::asio::signal_set signal_set_;
    IOSignalHandler handler_;
    void callback(const boost::system::error_code& ec, int signum);
};

IOSignalSetImpl::IOSignalSetImpl(IOServicePtr io_service,
                                 IOSignalHandler handler)
    : signal_set_(io_service->get_io_service()), handler_(handler) {
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
            // We log it and swallow it so we don't undermine IOService::run.
            LOG_ERROR(dctl_logger, DCTL_SIGNAL_ERROR)
                .arg(signum)
                .arg(ex.what());
        }
    }
}

void
IOSignalSetImpl::install() {
    signal_set_.async_wait(boost::bind(&IOSignalSetImpl::callback,
                                       shared_from_this(), _1, _2));
}

void
IOSignalSetImpl::add(int signum) {
    try {
        signal_set_.add(signum);
    } catch (const boost::system::system_error& ex) {
        isc_throw(isc::Unexpected, "Failed to add signal " << signum
                  << ": " << ex.what());
    }
}

IOSignalSet::IOSignalSet(IOServicePtr io_service, IOSignalHandler handler) :
    impl_(new IOSignalSetImpl(io_service, handler))
{
    // It can throw but the error is fatal...
    impl_->install();
}

IOSignalSet::~IOSignalSet() {
    impl_.reset();
}

void
IOSignalSet::add(int signum) {
    impl_->add(signum);
}

}; // end of isc::process namespace
}; // end of isc namespace
