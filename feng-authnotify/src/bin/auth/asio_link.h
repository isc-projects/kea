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

#ifndef __ASIO_LINK_H
#define __ASIO_LINK_H 1


#include <string.h>
#include <asio.hpp>
#include <dns/message.h>

class AuthSrv;
namespace asio_link {
struct IOServiceImpl;
using namespace asio::ip;

///\brief stands for one query client including its network information and query message
class UserInfo
{
    public:
        enum {QUERY_PACKAGE_MAX_LEN = 0xffff};
        enum QueryProtocol{ QueryThroughTCP , QueryThroughUDP};

        UserInfo(QueryProtocol protocol):queryProtocol_(protocol), message_(isc::dns::Message::PARSE), needs_reply_(false), is_message_valid_(false)  {}

        void setIOInfo(const std::string &ipaddr, unsigned short port, int socketfd){
            ipaddr_ = ipaddr;
            port_ = port;
            socket_ = socketfd;
        } 

        const std::string &     getIPAddress()const    { return ipaddr_;}
        UserInfo::QueryProtocol getProtocolType()const   {    return queryProtocol_;}
        unsigned short          getPort()const {   return port_;}
        int                     getSocket()const  {   return socket_; }


        void                        setQueryRawData(const char *data, size_t dataLen);
        bool                        needsReply() const { return needs_reply_;} //if even head part isn't complete then no need send reply back
        bool                        isMessageValid() const { return is_message_valid_;}
        isc::dns::Message &         getMessage() { return message_;}
        const isc::dns::Message &   getMessage() const{ return message_;}

    private:
        std::string ipaddr_;
        unsigned short port_;
        int socket_;

        QueryProtocol queryProtocol_;
        isc::dns::Message message_;
        bool needs_reply_;
        bool is_message_valid_;
};

class IOService {
public:
    IOService(AuthSrv* auth_server, const char* port,
              const bool use_ipv4, const bool use_ipv6);
    ~IOService();
    void run();
    void stop();
    asio::io_service& get_io_service();
private:
    IOServiceImpl* impl_;
};
}      // asio_link
#endif // __ASIO_LINK_H

// Local Variables: 
// mode: c++
// End: 
