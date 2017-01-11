// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <http/listener.h>

using namespace isc::asiolink;

namespace isc {
namespace http {

HttpListener::HttpListener(IOService& io_service,
                           const asiolink::IOAddress& server_address,
                           const unsigned short server_port,
                           const HttpResponseCreatorFactoryPtr& creator_factory)
    : io_service_(io_service), acceptor_(io_service),
      endpoint_(server_address, server_port),
      creator_factory_(creator_factory) {
}

HttpListener::~HttpListener() {
    stop();
}

void
HttpListener::start() {
    acceptor_.open(endpoint_);
    acceptor_.setOption(HttpAcceptor::ReuseAddress(true));
    acceptor_.bind(endpoint_);
    acceptor_.listen();

    accept();
}

void
HttpListener::stop() {
    connections_.stopAll();
    acceptor_.close();
}

void
HttpListener::accept() {
    HttpResponseCreatorPtr response_creator = creator_factory_->create();
    HttpAcceptorCallback acceptor_callback =
        boost::bind(&HttpListener::acceptHandler, this, _1);
    HttpConnectionPtr conn(new HttpConnection(io_service_, acceptor_,
                                              connections_,
                                              response_creator,
                                              acceptor_callback));
    connections_.start(conn);
}

void
HttpListener::acceptHandler(const boost::system::error_code& ec) {
    if (!ec) {
        accept();
    }
}


} // end of namespace isc::http
} // end of namespace isc
