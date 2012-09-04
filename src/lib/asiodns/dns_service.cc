// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <dns_service.h>

#include <asiolink/io_service.h>

#include <asio.hpp> // xxx_server.h requires this to be included first
#include <tcp_server.h>
#include <udp_server.h>
#include <sync_udp_server.h>

#include <boost/foreach.hpp>

using namespace isc::asiolink;

namespace isc {
namespace asiodns {

class DNSLookup;
class DNSAnswer;

class DNSServiceImpl {
public:
    DNSServiceImpl(IOService& io_service, SimpleCallback* checkin,
                   DNSLookup* lookup, DNSAnswer* answer) :
            io_service_(io_service), checkin_(checkin), lookup_(lookup),
            answer_(answer), tcp_recv_timeout_(5000)
    {}

    IOService& io_service_;

    typedef boost::shared_ptr<UDPServer> UDPServerPtr;
    typedef boost::shared_ptr<SyncUDPServer> SyncUDPServerPtr;
    typedef boost::shared_ptr<TCPServer> TCPServerPtr;
    typedef boost::shared_ptr<DNSServer> DNSServerPtr;
    std::vector<DNSServerPtr> servers_;
    SimpleCallback* checkin_;
    DNSLookup* lookup_;
    DNSAnswer* answer_;
    size_t tcp_recv_timeout_;

    template<class Ptr, class Server> void addServerFromFD(int fd, int af) {
        Ptr server(new Server(io_service_.get_io_service(), fd, af, checkin_,
                              lookup_, answer_));
        server->setTCPRecvTimeout(tcp_recv_timeout_);
        (*server)();
        servers_.push_back(server);
    }

    void setTCPRecvTimeout(size_t timeout) {
        // Store it for future tcp connections
        tcp_recv_timeout_ = timeout;
        // Update existing (TCP) Servers
        std::vector<DNSServerPtr>::iterator it = servers_.begin();
        for (; it != servers_.end(); ++it) {
            (*it)->setTCPRecvTimeout(timeout);
        }
    }
};

DNSService::DNSService(IOService& io_service, SimpleCallback* checkin,
                       DNSLookup* lookup, DNSAnswer *answer) :
    impl_(new DNSServiceImpl(io_service, checkin, lookup, answer)),
    io_service_(io_service)
{
}

DNSService::~DNSService() {
    delete impl_;
}

void DNSService::addServerTCPFromFD(int fd, int af) {
    impl_->addServerFromFD<DNSServiceImpl::TCPServerPtr, TCPServer>(fd, af);
}

void DNSService::addServerUDPFromFD(int fd, int af, ServerFlag options) {
    if ((~SERVER_DEFINED_FLAGS & static_cast<unsigned int>(options)) != 0) {
        isc_throw(isc::InvalidParameter, "Invalid DNS/UDP server option: "
                  << options);
    }
    if ((options & SERVER_SYNC_OK) != 0) {
        impl_->addServerFromFD<DNSServiceImpl::SyncUDPServerPtr,
            SyncUDPServer>(fd, af);
    } else {
        impl_->addServerFromFD<DNSServiceImpl::UDPServerPtr, UDPServer>(
            fd, af);
    }
}

void
DNSService::clearServers() {
    BOOST_FOREACH(const DNSServiceImpl::DNSServerPtr& s, impl_->servers_) {
        s->stop();
    }
    impl_->servers_.clear();
}

void
DNSService::setTCPRecvTimeout(size_t timeout) {
    impl_->setTCPRecvTimeout(timeout);
}

} // namespace asiodns
} // namespace isc
