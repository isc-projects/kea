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

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls

#include <boost/lexical_cast.hpp>

#include <log/dummylog.h>

#include <asio.hpp>
#include <dns_service.h>
#include <asiolink/io_service.h>
#include <tcp_server.h>
#include <udp_server.h>
#include <sync_udp_server.h>

#include <log/dummylog.h>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

using isc::log::dlog;

using namespace isc::asiolink;

namespace isc {
namespace asiodns {

class DNSLookup;
class DNSAnswer;

namespace {

asio::ip::address
convertAddr(const std::string& address) {
    asio::error_code err;
    asio::ip::address addr = asio::ip::address::from_string(address, err);
    if (err) {
        isc_throw(IOError, "Invalid IP address '" << &address << "': "
            << err.message());
    }
    return (addr);
}

}


class DNSServiceImpl {
public:
    DNSServiceImpl(IOService& io_service, const char& port,
                  const asio::ip::address* v4addr,
                  const asio::ip::address* v6addr,
                  SimpleCallback* checkin, DNSLookup* lookup,
                  DNSAnswer* answer,
                  const UDPVersion param_flags);

    IOService& io_service_;

    typedef boost::shared_ptr<UDPServer> UDPServerPtr;
    typedef boost::shared_ptr<SyncUDPServer> SyncUDPServerPtr;
    typedef boost::shared_ptr<TCPServer> TCPServerPtr;
    typedef boost::shared_ptr<DNSServer> DNSServerPtr;
    std::vector<DNSServerPtr> servers_;
    SimpleCallback *checkin_;
    DNSLookup *lookup_;
    DNSAnswer *answer_;

    template<class Ptr, class Server> void addServerFromFD(int fd, int af) {
        Ptr server(new Server(io_service_.get_io_service(), fd, af, checkin_,
                              lookup_, answer_));
        (*server)();
        servers_.push_back(server);
    }

    void addServer(uint16_t port, const asio::ip::address& address,
                   const UDPVersion param_flags) {
        try {
            dlog(std::string("Initialize TCP server at ") + address.to_string() + ":" + boost::lexical_cast<std::string>(port));
            TCPServerPtr tcpServer(new TCPServer(io_service_.get_io_service(),
                address, port, checkin_, lookup_, answer_));
            (*tcpServer)();
            servers_.push_back(tcpServer);
            dlog(std::string("Initialize UDP server at ") + address.to_string() + ":" + boost::lexical_cast<std::string>(port));
            // Use param_flags to generate diff UDPServers.    
            switch(param_flags) {
                case SYNC_: {
                    SyncUDPServerPtr syncUdpServer(new SyncUDPServer(io_service_.get_io_service(),
                                                   address, port, checkin_, lookup_, answer_));
                    (*syncUdpServer)();
                    servers_.push_back(syncUdpServer);
                    break;
                }
                case ASYNC_: {
                    UDPServerPtr udpServer(new UDPServer(io_service_.get_io_service(),
                                           address, port, checkin_, lookup_, answer_));
                    (*udpServer)();
                    servers_.push_back(udpServer);
                    break;
                }
                default:
                    // If nerther asyn UDPServer nor sync UDNServer, it throws.
                    isc_throw(IOError, "Bad UDPServer Version!");
                    break;
            }
        }
        catch (const asio::system_error& err) {
            // We need to catch and convert any ASIO level exceptions.
            // This can happen for unavailable address, binding a privilege port
            // without the privilege, etc.
            isc_throw(IOError, "Failed to initialize network servers: " <<
                      err.what());
        }
    }
    void addServer(const char& port, const asio::ip::address& address,
                   const UDPVersion param_flags) {
        uint16_t portnum;
        try {
            // XXX: SunStudio with stlport4 doesn't reject some invalid
            // representation such as "-1" by lexical_cast<uint16_t>, so
            // we convert it into a signed integer of a larger size and perform
            // range check ourselves.
            const int32_t portnum32 = boost::lexical_cast<int32_t>(&port);
            if (portnum32 < 0 || portnum32 > 65535) {
                isc_throw(IOError, "Invalid port number '" << &port);
            }
            portnum = portnum32;
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(IOError, "Invalid port number '" << &port << "': " <<
                      ex.what());
        }
        addServer(portnum, address,param_flags);
    }
};

DNSServiceImpl::DNSServiceImpl(IOService& io_service,
                               const char& port,
                               const asio::ip::address* const v4addr,
                               const asio::ip::address* const v6addr,
                               SimpleCallback* checkin,
                               DNSLookup* lookup,
                               DNSAnswer* answer,
                               const UDPVersion param_flags):
    io_service_(io_service),
    checkin_(checkin),
    lookup_(lookup),
    answer_(answer)
{

    if (v4addr) {
        addServer(port, *v4addr,param_flags);
    }
    if (v6addr) {
        addServer(port, *v6addr,param_flags);
    }
}

DNSService::DNSService(IOService& io_service,
                       const char& port, const char& address,
                       SimpleCallback* checkin,
                       DNSLookup* lookup,
                       DNSAnswer* answer,
                       const UDPVersion param_flags) :
    impl_(new DNSServiceImpl(io_service, port, NULL, NULL, checkin, lookup,
        answer,param_flags)), io_service_(io_service)
{
    addServer(port, &address,param_flags);
}

DNSService::DNSService(IOService& io_service,
                       const char& port,
                       const bool use_ipv4, const bool use_ipv6,
                       SimpleCallback* checkin,
                       DNSLookup* lookup,
                       DNSAnswer* answer,
                       const UDPVersion param_flags) :
    impl_(NULL), io_service_(io_service)
{
    const asio::ip::address v4addr_any =
        asio::ip::address(asio::ip::address_v4::any());
    const asio::ip::address* const v4addrp = use_ipv4 ? &v4addr_any : NULL; 
    const asio::ip::address v6addr_any =
        asio::ip::address(asio::ip::address_v6::any());
    const asio::ip::address* const v6addrp = use_ipv6 ? &v6addr_any : NULL;
    impl_ = new DNSServiceImpl(io_service, port, v4addrp, v6addrp, checkin, lookup, answer,param_flags);
}

DNSService::DNSService(IOService& io_service, SimpleCallback* checkin,
    DNSLookup* lookup, DNSAnswer *answer,const UDPVersion param_flags) :
    impl_(new DNSServiceImpl(io_service, *"0", NULL, NULL, checkin, lookup,
        answer,param_flags)), io_service_(io_service)
{
}

DNSService::~DNSService() {
    delete impl_;
}

void
DNSService::addServer(const char& port, const std::string& address,UDPVersion param_flags) {
    impl_->addServer(port, convertAddr(address),param_flags);
}

void
DNSService::addServer(uint16_t port, const std::string& address,UDPVersion param_flags) {
    impl_->addServer(port, convertAddr(address),param_flags);
}

void DNSService::addServerTCPFromFD(int fd, int af) {
    impl_->addServerFromFD<DNSServiceImpl::TCPServerPtr, TCPServer>(fd, af);
}

void DNSService::addServerUDPFromFD(int fd, int af,const UDPVersion param_flags) {
    if(SYNC_ == param_flags) { 
        impl_->addServerFromFD<DNSServiceImpl::SyncUDPServerPtr, SyncUDPServer>(fd, af);
    } else if(ASYNC_ == param_flags) {
        impl_->addServerFromFD<DNSServiceImpl::UDPServerPtr, UDPServer>(fd, af);
    }
}

void
DNSService::clearServers() {
    BOOST_FOREACH(const DNSServiceImpl::DNSServerPtr& s, impl_->servers_) {
        s->stop();
    }
    impl_->servers_.clear();
}

} // namespace asiodns
} // namespace isc
