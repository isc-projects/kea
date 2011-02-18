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

#include "portconfig.h"

#include <asiolink/io_address.h>
#include <asiolink/dns_service.h>
#include <log/dummylog.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace isc::data;
using namespace asiolink;
using isc::log::dlog;

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
                    isc_throw(BadValue, "Address must contain both the IP"
                        "address and port");
                }
                try {
                    IOAddress(addr->stringValue());
                    if (port->intValue() < 0 ||
                        port->intValue() > 0xffff) {
                        isc_throw(BadValue, "Bad port value (" <<
                            port->intValue() << ")");
                    }
                    result.push_back(AddressPair(addr->stringValue(),
                        port->intValue()));
                }
                catch (const TypeError &e) { // Better error message
                    isc_throw(TypeError,
                        "Address must be a string and port an integer");
                }
            }
        } else if (addresses->getType() != Element::null) {
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
                       asiolink::DNSService& service)
{
    try {
        dlog("Setting listen addresses:");
        BOOST_FOREACH(const AddressPair& addr, newAddresses) {
            dlog(" " + addr.first + ":" +
                        boost::lexical_cast<string>(addr.second));
        }
        setAddresses(service, newAddresses);
        addressStore = newAddresses;
    }
    catch (const exception& e) {
        /*
         * We couldn't set it. So return it back. If that fails as well,
         * we have a problem.
         *
         * If that fails, bad luck, but we are useless anyway, so just die
         * and let boss start us again.
         */
        dlog(string("Unable to set new address: ") + e.what(), true);
        try {
            setAddresses(service, addressStore);
        }
        catch (const exception& e2) {
            dlog("Unable to recover from error;", true);
            dlog(string("Rollback failed with: ") + e2.what(), true);
            abort();
        }
        throw e; // Let it fly a little bit further
    }
}

}
}
}
