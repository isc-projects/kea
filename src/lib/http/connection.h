// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include <asiolink/io_service.h>
#include <http/http_acceptor.h>
#include <http/request_parser.h>
#include <http/response_creator_factory.h>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>
#include <array>

namespace isc {
namespace http {

class HttpConnectionPool;

class HttpConnection;
typedef boost::shared_ptr<HttpConnection> HttpConnectionPtr;

class HttpConnection : public boost::enable_shared_from_this<HttpConnection> {
private:

    typedef boost::function<void(boost::system::error_code ec, size_t length)>
    SocketCallbackFunction;

    class SocketCallback {
    public:

        SocketCallback(SocketCallbackFunction socket_callback)
            : callback_(socket_callback) {
        }

        void operator()(boost::system::error_code ec, size_t length = 0);

    private:
        SocketCallbackFunction callback_;
    };


public:

    HttpConnection(asiolink::IOService& io_service,
                   HttpAcceptor& acceptor,
                   HttpConnectionPool& connection_pool,
                   const HttpResponseCreatorPtr& response_creator,
                   const HttpAcceptorCallback& callback);

    ~HttpConnection();

    void asyncAccept();

    void close();

    void doRead();

    void doWrite();

    void acceptorCallback(const boost::system::error_code& ec);

    void socketReadCallback(boost::system::error_code ec,
                            size_t length);

    void socketWriteCallback(boost::system::error_code ec,
                             size_t length);

private:

    asiolink::TCPSocket<SocketCallback> socket_;

    SocketCallback socket_callback_;

    SocketCallback socket_write_callback_;

    HttpAcceptor& acceptor_;

    HttpConnectionPool& connection_pool_;

    HttpResponseCreatorPtr response_creator_;

    HttpRequestPtr request_;

    HttpRequestParserPtr parser_;

    HttpAcceptorCallback acceptor_callback_;

    std::array<char, 4096> buf_;

    std::string output_buf_;
};

}
}

#endif
