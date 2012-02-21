// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __RBNODE_RRSET_H
#define __RBNODE_RRSET_H

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <util/buffer.h>

#include <string>

namespace isc {
namespace datasrc {

/// \brief Special RRset for optimiing memory datasource requirement
///
/// To speed up the performance of the in-memory data source, at load time
/// associate relevant "additional section" data with each RRset in the
/// data source.
///
/// This class, derived from AbstractRRset, holds a "const" pointer to the
/// underlying RRset object.  All calls to methods on the class are passed to
/// the underlying object.  However, there are some restrictions:
///
/// - Calls to methods that change attributes of the underlying RRset (such as
///   TTL or Name) cause an exception to be thrown.  The in-memory data source
///   does not allow modification of these attributes.
/// - Calls that modify the associated RRSIGs of the RRset are allowed (even
///   though the pointer is to a "const" object).  The reason here is because
///   RRSIGs are added to the in-memory data source after the RBNodeRRset
///   objects have been created.  Thus there has to be the capability of
///   modifying this information.
///
/// The class is not derived from RRset itself to simplify coding: part of the
/// loading of the memory data source is handled in the BIND 10 "libdns++"
/// code, which creates RRsets and passes them to the data source code.  This
/// does not have to be altered if encapsulation, rather than inheritcance, is
/// used.

// Note: non-Doxygen-documented methods are documented in the base class.

class RBNodeRRset : public isc::dns::AbstractRRset {

private:
    // Note: The copy constructor and the assignment operator are intentionally
    // defined as private as we would normally not duplicate a RBNodeRRset.
    RBNodeRRset(const RBNodeRRset& source);
    RBNodeRRset& operator=(const RBNodeRRset& source);

public:
    /// \brief Usual Constructor
    ///
    /// Creates an RBNodeRRset from the pointer to the RRset passed to it.
    RBNodeRRset(const isc::dns::ConstRRsetPtr& rrset) : rrset_(rrset),
        n("a.com"), c("HS"), t("A"), ttl(0) {}

    /// \brief Destructor
    virtual ~RBNodeRRset() {}

    // Getter and Setter Methods
    //
    // The getter methods pass the call through to the underlying RRset.  The
    // setter methods thrown an exception - this specialisation of the RRset
    // object does not expect the underlying RRset to be modified.

    virtual unsigned int getRdataCount() const {
        return (0);
    }

    virtual const isc::dns::Name& getName() const {
        return (n);
    }

    virtual const isc::dns::RRClass& getClass() const {
        return (c);
    }

    virtual const isc::dns::RRType& getType() const {
        return (t);
    }

    virtual const isc::dns::RRTTL& getTTL() const {
        return (ttl);
    }

    virtual void setName(const isc::dns::Name&) {
    }

    virtual void setTTL(const isc::dns::RRTTL&) {
    }

    virtual std::string toText() const {
        return (std::string());
    }

    virtual unsigned int toWire(isc::dns::AbstractMessageRenderer& /*renderer*/) const {
        return (-1);
    }

    virtual unsigned int toWire(isc::util::OutputBuffer& /*buffer*/) const {
        return (-1);
    }

    virtual void addRdata(isc::dns::rdata::ConstRdataPtr) {
    }

    virtual void addRdata(const isc::dns::rdata::Rdata&) {
    }

    virtual isc::dns::RdataIteratorPtr getRdataIterator() const {
        isc::dns::BasicRRset b(isc::dns::Name("example.com"),
                               isc::dns::RRClass("IN"),
                               isc::dns::RRType("A"),
                               isc::dns::RRTTL(1));
        return (b.getRdataIterator());
    }

    virtual isc::dns::RRsetPtr getRRsig() const {
        return (isc::dns::RRsetPtr());
    }

    virtual void addRRsig(const isc::dns::rdata::ConstRdataPtr& /*rdata*/) {
    }

    virtual void addRRsig(const isc::dns::rdata::RdataPtr& /*rdata*/) {
    }

    virtual void addRRsig(const AbstractRRset& /*sigs*/) {
    }

    virtual void addRRsig(const isc::dns::ConstRRsetPtr& /*sigs*/) {
    }

    virtual void addRRsig(const isc::dns::RRsetPtr& /*sigs*/) {
    }

    virtual void removeRRsig() {
    }

    /// \brief Return underlying RRset pointer
    virtual isc::dns::ConstRRsetPtr getUnderlyingRRset() const {
        return rrset_;
    }

private:
    isc::dns::ConstRRsetPtr rrset_;     ///< Underlying RRset

    isc::dns::Name n;
    isc::dns::RRClass c;
    isc::dns::RRType t;
    isc::dns::RRTTL ttl;
};

}   // namespace datasrc
}   // namespace isc

#endif  // __RBNODE_RRSET_H
