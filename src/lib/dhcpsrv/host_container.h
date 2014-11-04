// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef HOST_CONTAINER_H
#define HOST_CONTAINER_H

#include <dhcpsrv/host.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>

namespace isc {
namespace dhcp {

/// @brief Multi-index container holding host reservations.
///
/// This container holds a collection of @c Host objects which can be retrieved
/// using various parameters. The typical use of this container is to search for
/// all @c Host objects which are identified by a specified identifier, i.e.
/// HW address or DUID.
///
/// @todo This container will be extended to search for @c Host objects
/// associated with a specific IPv4 address or IPv6 prefix/length.
///
/// @see http://www.boost.org/doc/libs/1_56_0/libs/multi_index/doc/index.html
typedef boost::multi_index_container<
    // This container stores pointers to Host objects.
    HostPtr,
    // Start specification of indexes here.
    boost::multi_index::indexed_by<
        // First index is used to search for the host using one of the
        // identifiers, i.e. HW address or DUID. The elements of this
        // index are non-unique because there may be multiple reservations
        // for the same host belonging to a different subnets.
        boost::multi_index::ordered_non_unique<
            // The index comprises actual identifier (HW address or DUID) in
            // a binary form and a type of the identifier which indicates
            // that it is HW address or DUID.
            boost::multi_index::composite_key<
                // Composite key uses members of the Host class.
                Host,
                // Binary identifier is retrieved from the Host class using
                // a getIdentifier method.
                boost::multi_index::const_mem_fun<
                    Host, const std::vector<uint8_t>&,
                    &Host::getIdentifier
                >,
                // Identifier type is retrieved from the Host class using
                // a getIdentifierType method.
                boost::multi_index::const_mem_fun<
                    Host, Host::IdentifierType,
                    &Host::getIdentifierType
                >
            >
        >
    >
> HostContainer;

/// @brief First index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using an
/// identifier + identifier type tuple.
typedef HostContainer::nth_index<0>::type HostContainerIndex0;

/// @brief Results range returned using the @c HostContainerIndex0.
typedef std::pair<HostContainerIndex0::iterator,
                  HostContainerIndex0::iterator> HostContainerIndex0Range;

}
}

#endif // HOST_CONTAINER_H
