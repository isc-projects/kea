// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DNS_FWD_H
#define DNS_FWD_H 1

#include <dns/api.h>

/// \file dns_fwd.h
/// \brief Forward declarations for definitions of libdns++
///
/// This file provides a set of forward declarations for definitions commonly
/// used in libdns++ to help minimize dependency when actual the definition
/// is not necessary.

namespace isc {
namespace dns {

class EDNS;
class Name;
class MasterLoader;
class MasterLoaderCallbacks;
class Message;
class AbstractMessageRenderer;
class MessageRenderer;
class NSEC3Hash;
class NSEC3HashCreator;
class Opcode;
class Question;
class Rcode;
namespace rdata {
class Rdata;
}
class RRCollator;
class RRClass;
class RRType;
class RRTTL;
class AbstractRRset;
class RdataIterator;
class RRsetCollectionBase;
class RRsetCollection;
class Serial;
class TSIGContext;
class TSIGError;
class TSIGKey;
class TSIGKeyRing;
class TSIGRecord;

} // namespace dns
} // namespace isc
#endif  // DNS_FWD_H

// Local Variables:
// mode: c++
// End:
