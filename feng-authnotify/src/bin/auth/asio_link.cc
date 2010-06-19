// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <config.h>

#include <boost/bind.hpp>
#include <boost/utility.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/exceptions.h>
#include <exceptions/exceptions.h>


#if defined(HAVE_BOOST_PYTHON)
#define USE_XFROUT
#include <xfr/xfrout_client.h>
#endif


#include "spec_config.h"        // for XFROUT.  should not be here.
#include "auth_srv.h"
#include "asio_link.h"
#include "auth_util.h"

using namespace asio;
using ip::udp;
using ip::tcp;

using namespace std;
using namespace isc;
using namespace isc::dns;

namespace asio_link {
    
    void UserInfo::setQueryRawData(const char *data, size_t dataLen){
        is_message_valid_ = false;
        needs_reply_ = false;

        message_.clear(Message::PARSE);
        InputBuffer queryData(data, dataLen);
        try{
            message_.parseHeader(queryData);
            if (message_.getHeaderFlag(MessageFlag::QR())){
                return;
            }
        }catch (const Exception& ex) {
            return;
        }

        needs_reply_ = true;
        try{
            message_.fromWire(queryData);
        }catch (const DNSProtocolError& error) {
            auth_util::makeErrorMessage(message_, error.getRcode());
            return ;
        } catch (const Exception& ex) {
            auth_util::makeErrorMessage(message_, Rcode::SERVFAIL());
            return;
        } 

        is_message_valid_ = true;
    }

    class TCPClient {
        public:
            enum {TCP_MESSAGE_LENGTHSIZE = 2, DNS_TCP_MAX_PACKAGE_LENGTH = 0xffff};
            TCPClient(AuthSrv* auth_server, io_service& io_service) :
                auth_server_(auth_server),
                socket_(io_service),
                userInfo_(UserInfo::QueryThroughTCP),
                tcp_package_len_(0),
                response_package_len_(0),
                reply_buffer_(0){
                }

            ~TCPClient(){
                socket_.close();
            }

            void startReceive() {
                // Check for queued configuration commands
                if (auth_server_->configSession()->hasQueuedMsgs()) {
                    auth_server_->configSession()->checkCommand();
                }
                tcp_package_len_ = 0;
                response_package_len_ = 0;
                async_read(socket_, 
                        asio::buffer(data_, TCP_MESSAGE_LENGTHSIZE),
                        boost::bind(&TCPClient::readQuery, this, placeholders::error, placeholders::bytes_transferred));
            }

            tcp::socket& getSocket() { return (socket_); }

            void readQuery(const asio::error_code &error, size_t bytes_transferred)
            {
                if (error){
                    delete this;
                    return;
                }

                if (tcp_package_len_ == 0){
                    if (bytes_transferred != TCP_MESSAGE_LENGTHSIZE){
                        delete this;
                        return;
                    }else{
                        tcp_package_len_ = ntohs(*(uint16_t*)data_);
                        async_read(socket_, 
                                asio::buffer(data_, tcp_package_len_),
                                boost::bind(&TCPClient::readQuery, this, placeholders::error, placeholders::bytes_transferred));
                    }
                }else{
                    assert(bytes_transferred == tcp_package_len_);
                    userInfo_.setQueryRawData(data_, tcp_package_len_);
                    if (userInfo_.isMessageValid()) {
                        tcp::endpoint remote_endpoint = socket_.remote_endpoint();
                        userInfo_.setIOInfo(remote_endpoint.address().to_string(), remote_endpoint.port(), socket_.native());
                        auth_server_->processQuery(userInfo_);
                    }

                    if (!userInfo_.needsReply()){
                        delete this;
                        return;
                    }

                    auth_util::messageToWire(userInfo_.getMessage(), reply_buffer_);
                    //no response needs to send to enduser
                    if (reply_buffer_.getLength() == 0){
                        startReceive();
                    }else{
                        response_package_len_ = htons(reply_buffer_.getLength());
                        async_write(socket_, 
                                asio::buffer(&response_package_len_, TCP_MESSAGE_LENGTHSIZE),
                                boost::bind(&TCPClient::writeComplete, this, placeholders::error));

                    }   
                }
            }

            void writeComplete(const asio::error_code& error) {
                if (error){
                    delete this;
                    return;
                }

                if (response_package_len_ != 0){
                    async_write(socket_, 
                            asio::buffer(reply_buffer_.getData(), reply_buffer_.getLength()),
                            boost::bind(&TCPClient::writeComplete, this, placeholders::error));
                    response_package_len_ = 0;
                }else{
                    startReceive();            // handle next request, if any.
                }
            }


        private:
            AuthSrv* auth_server_;
            tcp::socket socket_;
            UserInfo userInfo_;
            uint16_t tcp_package_len_;
            uint16_t response_package_len_;
            OutputBuffer reply_buffer_;
            char data_[DNS_TCP_MAX_PACKAGE_LENGTH];
    };

    class TCPServer {
        public:
            TCPServer(AuthSrv* auth_server, io_service& io_service, int af, short port) :
                    auth_server_(auth_server), 
                    io_service_(io_service),
                    acceptor_(io_service_), 
                    listening_(new TCPClient(auth_server_, io_service_)){
                    
                tcp::endpoint endpoint(af == AF_INET6 ? tcp::v6() : tcp::v4(), port);
                acceptor_.open(endpoint.protocol());
                // Set v6-only (we use a different instantiation for v4,
                // otherwise asio will bind to both v4 and v6
                if (af == AF_INET6) {
                    acceptor_.set_option(ip::v6_only(true));
                }
                acceptor_.set_option(tcp::acceptor::reuse_address(true));
                acceptor_.bind(endpoint);
                acceptor_.listen();
                acceptor_.async_accept(listening_->getSocket(),
                boost::bind(&TCPServer::handleAccept, 
                            this,
                            listening_, 
                            placeholders::error));
            }

            ~TCPServer() { delete listening_; }

            void handleAccept(TCPClient* new_client,
                    const asio::error_code& error){
                if (error){
                    delete this;
                    return;
                }
                
                assert(new_client == listening_);
                new_client->startReceive();
                listening_ = new TCPClient(auth_server_, io_service_);
                acceptor_.async_accept(listening_->getSocket(),
                        boost::bind(&TCPServer::handleAccept,
                            this, listening_,
                            placeholders::error));
            }

        private:
            AuthSrv* auth_server_;
            io_service& io_service_;
            tcp::acceptor acceptor_;
            TCPClient* listening_;
    };

    class UDPServer {
        public:
            enum {DNS_UDP_MAX_PACKAGE_LENGTH = 4096};
            UDPServer(AuthSrv* auth_server, io_service& io_service,int af, short port) :
                auth_server_(auth_server),
                io_service_(io_service),
                socket_(io_service, af == AF_INET6 ? udp::v6() : udp::v4()),
                userInfo_(UserInfo::QueryThroughUDP),
                reply_buffer_(0)
                {
                    // Set v6-only (we use a different instantiation for v4,
                    // otherwise asio will bind to both v4 and v6
                    if (af == AF_INET6) {
                        socket_.set_option(asio::ip::v6_only(true));
                        socket_.bind(udp::endpoint(udp::v6(), port));
                    } else {
                        socket_.bind(udp::endpoint(udp::v4(), port));
                    }
                    startReceive();
                }

            void handleRequest(const asio::error_code& error,
                    size_t bytes_recvd)
            {
                // Check for queued configuration commands
                if (auth_server_->configSession()->hasQueuedMsgs()) {
                    auth_server_->configSession()->checkCommand();
                }
                if (error || bytes_recvd == 0){
                    startReceive();
                    return;
                }
                userInfo_.setQueryRawData(data_, bytes_recvd);
                if (userInfo_.isMessageValid()){
                    userInfo_.setIOInfo(sender_endpoint_.address().to_string(), sender_endpoint_.port(), socket_.native());
                    auth_server_->processQuery(userInfo_);
                }

                if (userInfo_.needsReply()){
                    auth_util::messageToWire(userInfo_.getMessage(), reply_buffer_);
                    socket_.async_send_to(
                            asio::buffer(reply_buffer_.getData(), reply_buffer_.getLength()),
                            sender_endpoint_,
                            boost::bind(&UDPServer::sendCompleted, this, placeholders::error, placeholders::bytes_transferred));
                }else {
                    startReceive();
                }
            }

            void sendCompleted(const asio::error_code& error UNUSED_PARAM,
                    size_t bytes_sent UNUSED_PARAM)
            {
                // Even if error occurred there's nothing to do.  Simply handle
                // the next request.
                startReceive();
            }
        private:
            void startReceive() {
                socket_.async_receive_from(
                        asio::buffer(data_, DNS_UDP_MAX_PACKAGE_LENGTH), sender_endpoint_,
                        boost::bind(&UDPServer::handleRequest, this, placeholders::error, placeholders::bytes_transferred));
            }

        private:
            AuthSrv* auth_server_;
            io_service& io_service_;
            udp::socket socket_;
            udp::endpoint sender_endpoint_;
            UserInfo userInfo_;
            OutputBuffer reply_buffer_;
            char data_[DNS_UDP_MAX_PACKAGE_LENGTH];
    };

    class IOServiceImpl : private boost::noncopyable {
        public:
            IOServiceImpl(AuthSrv* auth_server, const char* port,
                    const bool use_ipv4, const bool use_ipv6);
            void run()  { io_service_.run();}
            void stop() { io_service_.stop();}
            asio::io_service &get_io_service() { return io_service_;}
        private:
            asio::io_service io_service_;
            AuthSrv* auth_server_;
            std::auto_ptr<UDPServer> udp4_server_; 
            std::auto_ptr<UDPServer> udp6_server_; 
            std::auto_ptr<TCPServer> tcp4_server_; 
            std::auto_ptr<TCPServer> tcp6_server_; 
    };

    IOServiceImpl::IOServiceImpl(AuthSrv* auth_server, const char* const port,const bool use_ipv4, const bool use_ipv6) :
        auth_server_(auth_server), 
        udp4_server_(NULL), 
        udp6_server_(NULL),
        tcp4_server_(NULL), 
        tcp6_server_(NULL){
            short portnum = atoi(port);

            if (use_ipv4) {
                udp4_server_.reset(new UDPServer(auth_server, io_service_,
                            AF_INET, portnum));
                tcp4_server_.reset(new TCPServer(auth_server, io_service_,
                            AF_INET, portnum));
            }
            if (use_ipv6) {
                udp6_server_.reset(new UDPServer(auth_server, io_service_,
                            AF_INET6, portnum));
                tcp6_server_.reset(new TCPServer(auth_server, io_service_,
                            AF_INET6, portnum));
            }

        }


    IOService::IOService(AuthSrv* auth_server, const char* const port,
            const bool use_ipv4, const bool use_ipv6) {
        impl_ = new IOServiceImpl(auth_server, port, use_ipv4, use_ipv6);
    }

    IOService::~IOService() {
        delete impl_;
    }

    void
        IOService::run() {
            impl_->run();
        }

    void
        IOService::stop() {
            impl_->stop();
        }

    asio::io_service&
        IOService::get_io_service() {
            return impl_->get_io_service();
        }
}
