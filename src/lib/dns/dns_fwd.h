// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DNS_FWD_H
#define DNS_FWD_H 1

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
