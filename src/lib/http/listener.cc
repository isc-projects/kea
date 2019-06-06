// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <http/listener.h>
#include <http/listener_impl.h>

using namespace isc::asiolink;

namespace isc {
namespace http {

HttpListener::HttpListener(IOService& io_service,
                           const asiolink::IOAddress& server_address,
                           const unsigned short server_port,
                           const HttpResponseCreatorFactoryPtr& creator_factory,
                           const HttpListener::RequestTimeout& request_timeout,
                           const HttpListener::IdleTimeout& idle_timeout)
    : impl_(new HttpListenerImpl(io_service, server_address, server_port,
                                 creator_factory, request_timeout.value_,
                                 idle_timeout.value_)) {
}

HttpListener::~HttpListener() {
    stop();
}

IOAddress
HttpListener::getLocalAddress() const {
    return (impl_->getEndpoint().getAddress());
}

uint16_t
HttpListener::getLocalPort() const {
    return (impl_->getEndpoint().getPort());
}

void
HttpListener::start() {
    impl_->start();
}

void
HttpListener::stop() {
    impl_->stop();
}

} // end of namespace isc::http
} // end of namespace isc
