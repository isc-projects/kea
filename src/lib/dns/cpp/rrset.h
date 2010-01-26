// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __RRSET_H
#define __RRSET_H 1

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

#include "rdata.h"

namespace isc {
namespace dns {

class Name;
class RRType;
class RRClass;
class RRTTL;
class OututBuffer;
class MessageRenderer;

class AbstractRRset;
typedef boost::shared_ptr<AbstractRRset> RRsetPtr;
class BasicRRset;
typedef BasicRRset RRset;
class BasicRRsetImpl;

class RdataIterator;
typedef boost::shared_ptr<RdataIterator> RdataIteratorPtr;

/// \brief TBD
///
/// An \c RRset object models an RRset as described in the DNS standard:
/// a set of DNS resource records (RRs) of the same type and class.
/// The standard requires the TTL of all RRs in an RRset be the same;
/// this class follows that requirement.
/// Note about duplication: we probably don't enforce the RDATA is unique
/// as a class responsibility - but may revisit the decision.
///
// This is a primary class internally used in our major software such as name
// servers.
//
// Note about terminology: there has been a discussion at the IETF namedroppers
// ML about RRset vs RRSet (case of "s").  While RFC2181 uses the latter,
// many other RFCs use the former, and most of the list members who showed
// their opinion seem to prefer RRset.  We follow that preference in this
// implementation.
//
// Open Issues:
//   - add more set-like operations, e.g, merge?
//   - add a "sort" method?  "search(find)" method?
//   - BIND9 libdns has some special DNSSEC-related methods
//     such as addnoqname(), addclosest().  do we need these?
//   - need to check duplicate rdata in addrdata()?
//   - need a comparison method?  if so, should it compare
//     rdata's as a set or as a list (compare each rdata one
//     by one)?  ldns has ldns_rr_list_compare(), which takes
//     the latter approach (assuming the caller sorts the lists
//     beforehand?).
class AbstractRRset {
public:
    virtual ~AbstractRRset() {}
    virtual std::string toText() const;
    /// Note: perhaps we may want to add more arguments to convey optional
    /// information such as an "rrset-order" policy.
    /// no name compression, no truncation
    virtual unsigned int toWire(OutputBuffer& buffer) const;
    /// name compression when necessary, taking into account truncation
    virtual unsigned int toWire(MessageRenderer& renderer) const;
    virtual unsigned int getRdataCount() const = 0;
    virtual const Name& getName() const = 0;
    virtual const RRClass& getClass() const = 0;
    virtual const RRType& getType() const = 0;
    virtual const RRTTL& getTTL() const = 0;
    ///
    /// once constructed, only TTL and the set of Rdata can be modified,
    /// so \c setTTL() is the only explicit setter method.
    ///
    /// Do we need to allow the user to remove specific Rdata?
    /// Looking at the BIND9 code, don't see the strong need for this at the
    /// moment.
    ///
    virtual void setTTL(const RRTTL& ttl) = 0;

    ///
    /// \name RDATA manipulation methods
    ///
    //@{
    virtual void addRdata(const rdata::RdataPtr rdata) = 0;
    /// This method has the default implementation.
    /// Note: since concrete classes would define the pure virtual version
    /// of \c addRdata(), they'll need to declare the use of this method
    /// to avoid name hiding (unless they redefine this method):
    /// \code class CustomizedRRset : public AbstractRRset {
    /// public:
    ///     using AbstractRRset::addRdata;
    ///     ...
    /// }; \endcode
    virtual void addRdata(const rdata::Rdata& rdata);
    virtual RdataIteratorPtr getRdataIterator() const = 0;
    //@}
};

class RdataIterator {
public:
    virtual ~RdataIterator() {}
    virtual void first() = 0;
    virtual void next() = 0;
    virtual const rdata::Rdata& getCurrent() const = 0;
    virtual bool isLast() const = 0;
};

/// Straightforward RRset implementation.
/// designed to be as portable as possible.  performance is a secondary
/// concern for this class.
class BasicRRset : public AbstractRRset {
private:
    BasicRRset(const BasicRRset& source);
    void operator=(const BasicRRset& source);
public:
    explicit BasicRRset(const Name& name, const RRClass& rrclass,
                        const RRType& rrtype, const RRTTL& ttl);
    virtual ~BasicRRset();
    ///
    /// See the note for the base class version.
    ///
    using AbstractRRset::addRdata;
    virtual void addRdata(const rdata::RdataPtr rdata);
    ///
    /// We'd use the default implementations for toText() and toWire()
    /// variants as defined in the base class.  These are not fully optimized
    /// for performance, but, again, it's a secondary goal for this generic
    /// class.

    ///
    /// \name Getter and setter methods
    ///
    //@{
    virtual unsigned int getRdataCount() const;
    virtual const Name& getName() const;
    virtual const RRClass& getClass() const;
    virtual const RRType& getType() const;
    virtual const RRTTL& getTTL() const;
    virtual void setTTL(const RRTTL& ttl);
    //@}
    ///
    virtual RdataIteratorPtr getRdataIterator() const;
private:
    BasicRRsetImpl* impl_;
};

std::ostream& operator<<(std::ostream& os, const AbstractRRset& rrset);
} // end of namespace dns
} // end of namespace isc
#endif  // __RRSET_H

// Local Variables: 
// mode: c++
// End: 
