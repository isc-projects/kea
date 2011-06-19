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

#ifndef ACL_DNS_H
#define ACL_DNS_H

#include "loader.h"

#include <asiolink/io_address.h>
#include <dns/message.h>

namespace isc {
namespace acl {
namespace dns {

/**
 * \brief DNS Packet to be checked.
 *
 * This plays the role of Context of the generic template ACLs (in namespace
 * isc::acl).
 *
 * It is simple structure holding just the bunch of information. Therefore
 * the names don't end up with a slash, there are no methods so they can't be
 * confused with local variables.
 *
 * \todo Do we want a constructor to set this in a shorter manner? So we can
 *     call the ACLs directly?
 */
struct Packet {
    /// \brief The DNS message (payload).
    isc::dns::ConstMessagePtr message;
    /// \brief The remote IP address (eg. the client).
    asiolink::IOAddress remote_address;
    /// \brief The local IP address (ours, of the interface where we received).
    asiolink::IOAddress local_address;
    /// \brief The remote port.
    uint16_t remote_port;
    /// \brief The local port.
    uint16_t local_port;
    /**
     * \brief Name of the TSIG key the message is signed with.
     *
     * This will be either the name of the TSIG key the message is signed with,
     * or empty string, if the message is not signed. It is true we could get
     * the information from the message itself, but because at the time when
     * the ACL is checked, the signature has been verified already, so passing
     * it around is probably cheaper.
     *
     * It is expected that messages with invalid signatures are handled before
     * ACL.
     */
    std::string tisg_key;
};

/// \brief DNS based check.
typedef acl::Check<Packet> Check;
/// \brief DNS based compound check.
typedef acl::CompoundCheck<Packet> CompoundCheck;
/// \brief DNS based ACL.
typedef acl::ACL<Packet> ACL;
/// \brief DNS based ACL loader.
typedef acl::Loader<Packet> Loader;

/**
 * \brief Loader singleton access function.
 *
 * This function returns a loader of ACLs. It is expected applications
 * will use this function instead of creating their own loaders, because
 * one is enough, this one will have registered default checks and it
 * is known one, so any plugins can registrer additional checks as well.
 */
Loader& getLoader();

}
}
}

#endif
