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
#include <vector>

namespace isc {
namespace datasrc {
namespace internal {

/// \brief The actual content of \c RBNodeRRset
///
///  This is defined in the namespace-scope (not hidden in the main class)
/// so that the In-memory data source implementation can refer to it.
struct RBNodeRRsetImpl;

struct AdditionalNodeInfo;

/// \brief Special RRset for optimizing memory datasource requirement
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
///   does not allow modification of these attributes.  In theory, it is a bad
///   practice in that it doesn't preserve the assumed behavior of the base
///   class.  In practice, however, it should be acceptable because this
///   class is effectively hidden from applications and will only be given
///   to them as a const pointer to the base class via find() variants.
///   So the application cannot call non const methods anyway unless it
///   intentionally breaks the constness.
///
/// - Calls that add the pointer to the associated RRSIG to the RRset are
///   allowed (even though the pointer is to a "const" RRset).  The reason here
///   is that RRSIGs are added to the in-memory data source after the
///   RBNodeRRset objects have been created.  Thus there has to be the
///   capability of modifying this information.
///
/// The class is not derived from RRset itself to simplify coding: part of the
/// loading of the memory data source is handled in the BIND 10 "libdns++"
/// code, which creates RRsets and passes them to the data source code.  This
/// does not have to be altered if encapsulation, rather than inheritance, is
/// used.
///
/// \note This class is exposed in this separate header file so that test code
/// can refer to its definition, and only for that purpose.  Otherwise this is
/// essentially a private class of the in-memory data source implementation,
/// and an application shouldn't directly refer to this class.
/// 
// Note: non-Doxygen-documented methods are documented in the base class.

class RBNodeRRset : public isc::dns::AbstractRRset {

private:
    // Note: The copy constructor and the assignment operator are intentionally
    // defined as private as we would normally not duplicate a RBNodeRRset.
    // (We use the "private" method instead of inheriting from
    // boost::noncopyable so as to avoid multiple inheritance.)
    RBNodeRRset(const RBNodeRRset& source);
    RBNodeRRset& operator=(const RBNodeRRset& source);

public:
    /// \brief Usual Constructor
    ///
    /// Creates an RBNodeRRset from the pointer to the RRset passed to it.
    ///
    /// \param rrset Pointer to underlying RRset encapsulated by this object.
    explicit RBNodeRRset(const isc::dns::ConstRRsetPtr& rrset);

    /// \brief Destructor
    virtual ~RBNodeRRset();

    // Getter and Setter Methods
    //
    // The getter methods pass the call through to the underlying RRset.  The
    // setter methods thrown an exception - this specialisation of the RRset
    // object does not expect the underlying RRset to be modified.

    virtual unsigned int getRdataCount() const;

    virtual const isc::dns::Name& getName() const;

    virtual const isc::dns::RRClass& getClass() const;

    virtual const isc::dns::RRType& getType() const;

    virtual const isc::dns::RRTTL& getTTL() const;

    virtual void setName(const isc::dns::Name&);

    virtual void setTTL(const isc::dns::RRTTL&);

    virtual std::string toText() const;

    virtual unsigned int toWire(
        isc::dns::AbstractMessageRenderer& renderer) const;

    virtual unsigned int toWire(isc::util::OutputBuffer& buffer) const;

    virtual void addRdata(isc::dns::rdata::ConstRdataPtr);

    virtual void addRdata(const isc::dns::rdata::Rdata&);

    virtual isc::dns::RdataIteratorPtr getRdataIterator() const;

    virtual isc::dns::RRsetPtr getRRsig() const;

    // With all the RRsig methods, we have the problem that we store the
    // underlying RRset using a ConstRRsetPtr - a pointer to a "const" RRset -
    // but we need to modify it by adding or removing an RRSIG.  We overcome
    // this by temporarily violating the "const" nature of the RRset to add the
    // data.

    virtual void addRRsig(const isc::dns::rdata::ConstRdataPtr& rdata);

    virtual void addRRsig(const isc::dns::rdata::RdataPtr& rdata);

    virtual void addRRsig(const AbstractRRset& sigs);

    virtual void addRRsig(const isc::dns::ConstRRsetPtr& sigs);

    virtual void addRRsig(const isc::dns::RRsetPtr& sigs);

    virtual void removeRRsig();

    /// \brief TBD
    /// Note: this method is mostly private to the in-memory implementation.
    void addAdditionalNode(const AdditionalNodeInfo& additional);

    /// \brief TBD
    const std::vector<AdditionalNodeInfo>* getAdditionalNodes() const;

    /// \brief Return underlying RRset pointer
    ///
    /// ... mainly for testing.
    isc::dns::ConstRRsetPtr getUnderlyingRRset() const;

private:
    RBNodeRRsetImpl* impl_;
};

}   // namespace internal
}   // namespace datasrc
}   // namespace isc

#endif  // __RBNODE_RRSET_H
