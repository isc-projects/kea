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
        if (addresses->getType() == Element::list) {
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
                }
                catch (const TypeError &e) { // Better error message
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

void
setAddresses(DNSService& service, const AddressList& addresses) {
    service.clearServers();
    BOOST_FOREACH(const AddressPair &address, addresses) {
        service.addServer(address.second, address.first);
    }
}

}

void
installListenAddresses(const AddressList& newAddresses,
                       AddressList& addressStore,
                       isc::asiodns::DNSService& service)
{
    try {
        LOG_DEBUG(logger, DBG_TRACE_BASIC, SRVCOMM_SET_LISTEN);
        BOOST_FOREACH(const AddressPair& addr, newAddresses) {
            LOG_DEBUG(logger, DBG_TRACE_VALUES, SRVCOMM_ADDRESS_VALUE).
                arg(addr.first).arg(addr.second);
        }
        setAddresses(service, newAddresses);
        addressStore = newAddresses;
    }
    catch (const exception& e) {
        /*
         * If one of the addresses isn't set successfully, we will restore
         * the old addresses, the behavior is that either all address are
         * set successuflly or none of them will be used. whether this
         * behavior is user desired, maybe we need revisited it later. And
         * if address setting is more smarter, it should check whether some
         * part of the new address already in used to avoid interuption the
         * service.
         *
         * If the address setting still failed, we can live with it, since
         * user will get error info, command control can be used to set new
         * address. So we just catch the exception without propagating outside
         */
        LOG_ERROR(logger, SRVCOMM_ADDRESS_FAIL).arg(e.what());
        try {
            setAddresses(service, addressStore);
        }
        catch (const exception& e2) {
            LOG_FATAL(logger, SRVCOMM_ADDRESS_UNRECOVERABLE).arg(e2.what());
        }
        //Anyway the new configure has problem, we need to notify configure
        //manager the new configure doesn't work
        throw;
    }
}

}
}
}
