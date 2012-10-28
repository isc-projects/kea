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

#ifndef RBNODE_RRSET_H
#define RBNODE_RRSET_H

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

// Forward declaration of an opaque data type defined and used within the
// implementation.  This is public only because it needs to be used within
// the in-memory data source implementation, but conceptually this is a
// private type for the in-memory data source implementation.
// Note that the definition of the structure is still hidden within the
// implementation, so, basically, a normal application should never be able
// to use it directly even if it peeks into the "internal" namespace.
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

    virtual bool isSameKind(const AbstractRRset& other) const {
        // This code is an optimisation for comparing
        // RBNodeRRsets. However, in doing this optimisation,
        // semantically the code is not "is same kind" but is instead
        // "is identical object" in the case where RBNodeRRsets are compared.

        const RBNodeRRset* rb = dynamic_cast<const RBNodeRRset*>(&other);
        if (rb != NULL) {
            return (this == rb);
        } else {
            return (AbstractRRset::isSameKind(other));
        }
    }

    virtual unsigned int toWire(
        isc::dns::AbstractMessageRenderer& renderer) const;

    virtual unsigned int toWire(isc::util::OutputBuffer& buffer) const;

    virtual void addRdata(isc::dns::rdata::ConstRdataPtr);

    virtual void addRdata(const isc::dns::rdata::Rdata&);

    virtual isc::dns::RdataIteratorPtr getRdataIterator() const;

    virtual isc::dns::RRsetPtr getRRsig() const;

    virtual unsigned int getRRsigDataCount() const;

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

    /// \brief Associate a link to an RB node of the additional record.
    ///
    /// This method adds a given opaque object that holds a link to an RB node
    /// of the underlying in-memory data source that is corresponding to an
    /// RDATA of this RRset.
    ///
    /// This method is exposed as public so it can be used within the in-memory
    /// data source implementation, and only for that purpose.
    ///
    /// \param additional An opaque \c AdditionalNodeInfo object to be
    /// associated with this RRset.
    void addAdditionalNode(const AdditionalNodeInfo& additional);

    /// \brief Return a pointer to the list (vector) of additional RB nodes.
    ///
    /// This method returns a pointer to a vector storing the opaque
    /// \c AdditionalNodeInfo object that may be possibly set in this RRset.
    /// Not all RRsets are associated with additional nodes; if no
    /// such node is stored, this method returns NULL.
    ///
    /// Like \c addAdditionalNode(), this method is exposed as public only for
    /// the in-memory data source implementation.
    ///
    /// \return A pointer to the associated vector of \c AdditionalNodeInfo;
    /// NULL if no additional nodes are associated to this RRset.
    const std::vector<AdditionalNodeInfo>* getAdditionalNodes() const;

    /// \brief Copy the list of additional RB nodes to another RRset.
    ///
    /// This method copies the internal list (an STL vector in the actual
    /// implementation) of additional RB nodes for this RRset to another
    /// \c RBNodeRRset object.  The copy destination is generally expected to
    /// be newly created and have an empty list, but this method does not
    /// check the condition.  If the destination already has a non empty list,
    /// the existing entries will be lost.
    ///
    /// \param dst The \c RBNodeRRset object to which the additional
    /// RB node list is to be copied.
    void copyAdditionalNodes(RBNodeRRset& dst) const;

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

#endif  // RBNODE_RRSET_H
