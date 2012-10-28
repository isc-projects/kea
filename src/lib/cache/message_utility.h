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

// $Id$

#ifndef MESSAGE_UTILITY_H
#define MESSAGE_UTILITY_H

#include <dns/message.h>

namespace isc {
namespace cache {

/// \brief Some utility functions to extract info from message
///
/// We need to check the message before cache it, for example, if no SOA
/// record is found in the Authority section of NXDOMAIN response, the
/// message cannot be cached
namespace MessageUtility{

/// \brief Check whether there is some type of record in
///        Authority section
///
/// \param msg The response message to be checked
/// \param type The RR type that need to check
bool hasTheRecordInAuthoritySection(const isc::dns::Message& msg,
                                    const isc::dns::RRType& type);

/// \brief Check whetehr the message is a negative response
///        (NXDOMAIN or NOERROR_NODATA)
///
/// \param msg The response message
bool isNegativeResponse(const isc::dns::Message& msg);

/// \brief Check whether the message can be cached
///        Negative responses without SOA records SHOULD NOT be cached as there
///        is no way to prevent the negative responses looping forever between a
///        pair of servers even with a short TTL.
///        Despite the DNS forming a tree of servers, with various mis-
///        configurations it is possible to form a loop in the query graph, e.g.
///        two servers listing each other as forwarders, various lame server
///        configurations.  Without a TTL count down a cache negative response
///        when received by the next server would have its TTL reset.  This
///        negative indication could then live forever circulating between the
///        servers involved. (Sec 5, RFC2308)
///
/// \param msg The response message
bool canMessageBeCached(const isc::dns::Message& msg);

} // namespace MessageUtility
} // namespace cache
} // namespace isc


#endif//MESSAGE_UTILITY_H
