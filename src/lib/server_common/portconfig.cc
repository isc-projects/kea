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

#include <server_common/portconfig.h>
#include <server_common/logger.h>
#include <server_common/socket_request.h>

#include <asiolink/io_address.h>
#include <asiodns/dns_service.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::asiodns;

namespace isc {
namespace server_common {
namespace portconfig {

AddressList
parseAddresses(isc::data::ConstElementPtr addresses,
               const std::string& elemName)
{
    AddressList result;
    if (addresses) {
        if (addresses->getType() == Element::list &&
            !addresses->empty() ) {
            for (size_t i(0); i < addresses->size(); ++ i) {
                ConstElementPtr addrPair(addresses->get(i));
                ConstElementPtr addr(addrPair->get("address"));
                ConstElementPtr port(addrPair->get("port"));
                if (!addr || ! port) {
                    LOG_ERROR(logger, SRVCOMM_ADDRESS_MISSING).
                        arg(addrPair->str());
                    isc_throw(BadValue, "Address must contain both the IP"
                        "address and port");
                }
                try {
                    // We create an IOAddress object to just check that
                    // construction passes. It is immediately destroyed.
                    // cppcheck-suppress unusedScopedObject
                    IOAddress(addr->stringValue());
                    if (port->intValue() < 0 ||
                        port->intValue() > 0xffff) {
                        LOG_ERROR(logger, SRVCOMM_PORT_RANGE).
                            arg(port->intValue()).arg(addrPair->str());
                        isc_throw(BadValue, "Bad port value (" <<
                            port->intValue() << ")");
                    }
                    result.push_back(AddressPair(addr->stringValue(),
                        port->intValue()));
                } catch (const TypeError&) { // Better error message
                    LOG_ERROR(logger, SRVCOMM_ADDRESS_TYPE).
                        arg(addrPair->str());
                    isc_throw(TypeError,
                        "Address must be a string and port an integer");
                }
            }
        } else if (addresses->getType() != Element::null) {
            LOG_ERROR(logger, SRVCOMM_ADDRESSES_NOT_LIST).arg(elemName);
            isc_throw(TypeError, elemName + " config element must be a list");
        }
    }
    return (result);
}

namespace {

vector<string> current_sockets;

void
setAddresses(DNSServiceBase& service, const AddressList& addresses,
             DNSService::ServerFlag server_options)
{
    service.clearServers();
    BOOST_FOREACH(const string& token, current_sockets) {
        socketRequestor().releaseSocket(token);
    }
    current_sockets.clear();
    BOOST_FOREACH(const AddressPair &address, addresses) {
        const int af(IOAddress(address.first).getFamily());
        // We use the application name supplied to the socket requestor on
        // creation. So we can freely use the SHARE_SAME
        const SocketRequestor::SocketID
            tcp(socketRequestor().requestSocket(SocketRequestor::TCP,
                                                address.first, address.second,
                                                SocketRequestor::SHARE_SAME));
        current_sockets.push_back(tcp.second);
        service.addServerTCPFromFD(tcp.first, af);
        const SocketRequestor::SocketID
            udp(socketRequestor().requestSocket(SocketRequestor::UDP,
                                                address.first, address.second,
                                                SocketRequestor::SHARE_SAME));
        current_sockets.push_back(udp.second);
        service.addServerUDPFromFD(udp.first, af, server_options);
    }
}

}

void
installListenAddresses(const AddressList& new_addresses,
                       AddressList& address_store,
                       DNSServiceBase& service,
                       DNSService::ServerFlag server_options)
{
    try {
        LOG_DEBUG(logger, DBG_TRACE_BASIC, SRVCOMM_SET_LISTEN);
        BOOST_FOREACH(const AddressPair& addr, new_addresses) {
            string addr_str;
            if (addr.first.find(':') != string::npos) {
                addr_str = "[" + addr.first + "]";
            } else {
                addr_str = addr.first;
            }
            LOG_DEBUG(logger, DBG_TRACE_VALUES, SRVCOMM_ADDRESS_VALUE).
                arg(addr_str).arg(addr.second);
        }
        setAddresses(service, new_addresses, server_options);
        address_store = new_addresses;
    } catch (const SocketRequestor::NonFatalSocketError& e) {
        /*
         * If one of the addresses isn't set successfully, we will restore
         * the old addresses, the behavior is that either all address are
         * set successuflly or none of them will be used. whether this
         * behavior is user desired, maybe we need revisited it later. And
         * if address setting is more smarter, it should check whether some
         * part of the new address already in used to avoid interrupting the
         * service.
         *
         * If the address setting still failed, we can live with it, since
         * user will get error info, command control can be used to set new
         * address. So we just catch the exception without propagating outside
         */
        LOG_ERROR(logger, SRVCOMM_ADDRESS_FAIL).arg(e.what());
        try {
            setAddresses(service, address_store, server_options);
        } catch (const SocketRequestor::NonFatalSocketError& e2) {
            LOG_FATAL(logger, SRVCOMM_ADDRESS_UNRECOVERABLE).arg(e2.what());
            // If we can't set the new ones, nor the old ones, at least
            // releasing everything should work. If it doesn't, there isn't
            // anything else we could do.
            setAddresses(service, AddressList(), server_options);
            address_store.clear();
        }
        //Anyway the new configure has problem, we need to notify configure
        //manager the new configure doesn't work
        throw;
    } catch (const exception& e) {
        // Any other kind of exception is fatal. It might mean we are in
        // inconsistent state with the b10-init/socket creator, so we abort
        // to make sure it doesn't last.
        LOG_FATAL(logger, SRVCOMM_EXCEPTION_ALLOC).arg(e.what());
        abort();
    } catch (...) {
        // As the previous one, but we know even less info
        LOG_FATAL(logger, SRVCOMM_UNKNOWN_EXCEPTION_ALLOC);
        abort();
    }
}

}
}
}
