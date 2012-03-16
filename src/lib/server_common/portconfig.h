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

#ifndef ISC_SERVER_COMMON_PORTCONFIG_H
#define ISC_SERVER_COMMON_PORTCONFIG_H

#include <cc/data.h>

#include <asiodns/dns_service.h>

#include <utility>
#include <string>
#include <stdint.h>
#include <vector>

namespace isc {
namespace server_common {
/**
 * \brief Utilities to configure ports and addresses.
 *
 * Here are some utilities to help a server to parse configuration of addresses
 * and ports and install the configuration.
 */
namespace portconfig {

/**
 * \brief An address-port pair.
 *
 * It is just a pair of string for an address and unsigned integer for port
 * number. Anything more fancy would be an overkill, it is used only to pass
 * the addresses and ports around as intermediate results.
 */
typedef std::pair<std::string, uint16_t> AddressPair;

/// \brief Bunch of address pairs
typedef std::vector<AddressPair> AddressList;

/**
 * \brief
 *
 * This parses a list of address-port configurations and returns them. The
 * configuration looks like this:
 *
 * \verbatim
[
  {
    "address": "192.0.2.1",
    "port": 13
  },
  {
    "address": "::",
    "port": 80
  }
]
 * \endverbatim
 * \param addresses The configuration element to parse (the list). Empty list,
 *     null element and null pointer all mean empty list of addresses.
 * \param elemName The name of the element, used to create descriptions for
 *     exceptions.
 * \return Vector of parsed address-port pairs found in the configuration.
 * \throw isc::data::TypeError if something in the configuration is of a wrong
 *     type (string passed to a port, element in the list that isn't hash,
 *     etc).
 * \throw asiolink::IOError if the provided address string can't be parsed.
 * \throw BadValue for other invalid configurations (missing port or address
 *     element in the hash, port number out of range).
 * \throw std::bad_alloc when allocation fails.
 */
AddressList
parseAddresses(isc::data::ConstElementPtr addresses,
               const std::string& elemName);

/// \brief Changes current listening addresses and ports.
///
/// Removes all sockets we currently listen on and starts listening on the
/// addresses and ports requested in new_addresses.
///
/// If it fails to set up the new addresses, it attempts to roll back to the
/// previous addresses (but it still propagates the exception). If the rollback
/// fails as well, it doesn't abort the application (to allow reconfiguration),
/// but removes all the sockets it listened on. One of the exceptions is
/// propagated.
///
/// The ports are requested from the socket creator through boss. Therefore
/// you need to initialize the SocketRequestor before using this function.
///
/// \param new_addresses are the addresses you want to listen on.
/// \param address_store is the place you store your current addresses. It is
///     used when there's a need for rollback. The new_addresses are copied
///     here when the change is successful.
/// \param dns_service is the DNSService object we use now. The requests from
///     the new sockets are handled using this dns_service (and all current
///     sockets on the service are closed first).
/// \param server_options specifies optional properties for the servers
///        created via \c dns_service.
///
/// \throw asiolink::IOError when initialization or closing of socket fails.
/// \throw isc::server_common::SocketRequestor::Socket error when the
///     boss/socket creator doesn't want to give us the socket.
/// \throw std::bad_alloc when allocation fails.
/// \throw isc::InvalidOperation when the function is called and the
///     SocketRequestor isn't initialized yet.
void
installListenAddresses(const AddressList& new_addresses,
                       AddressList& address_store,
                       asiodns::DNSServiceBase& dns_service,
                       asiodns::DNSService::ServerFlag server_options =
                       asiodns::DNSService::SERVER_DEFAULT);

}
}
}

#endif

// Local Variables:
// mode: c++
// End:
