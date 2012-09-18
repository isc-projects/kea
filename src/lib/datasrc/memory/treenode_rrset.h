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

#ifndef DATASRC_MEMORY_TREENODE_RRSET_H
#define DATASRC_MEMORY_TREENODE_RRSET_H 1

#include <util/buffer.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rrset.h>

#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/rdataset.h>

#include <boost/noncopyable.hpp>

#include <string>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Special RRset for optimizing memory datasource requirement
///
/// This is a derived class of \c dns::AbstractRRset intended to be used
/// by the in-memory data source finder implementation.  It is designed
/// so performance sensitive operations will be lightweight; for example,
/// (in the general case) the construction is just set up references to
/// pre-loaded in-memory objects, not involving any dynamic memory allocation.
/// Its \c toWire() method is also customized so it won't have to use
/// the generic but expensive \c dns::RdataIterator.
///
/// On the other hand, some other performance-insensitive methods could be
/// even less efficient than the generic version.  Those include \c getName(),
/// \c toText(), and \c getRdataIterator() methods.
///
/// \note Right now, the authoritative server's query processing still needs
/// to use \c getRdataIterator() and \c getName() for relatively rare case
/// operations.  We should revise that part of the authoritative server
/// implementation in the next phase in order to eliminate the bottleneck.
///
/// Since this class is assumed to be instantiated only from the in-memory
/// zone finder, which only returns immutable (const) \c RRset objects,
/// we skip implementing non const virtual methods of this class.
/// Unless the application intentionally breaks the constness or the class
/// is abused outside of the in-memory data source implementation, this
/// should be safe because such methods should never be called.
///
/// Some other const member methods are still incomplete; if they are called
/// it will result in an exception.  In the expected usage of this class
/// it should be safe, but we should eventually provide complete
/// implementations of these methods.
///
/// This class can internally maintain dynamically allocated resource.
/// It would cause copying a class object complicated while objects of
/// this class are not expected to be copyable in the usage, so it's
/// explicitly defined non copyable.
///
/// \note This class is exposed in this separate header file so that other
/// part of the in-memory data source implementation and test code
/// can refer to its definition, and only for that purpose.  Otherwise this is
/// essentially a private class of the in-memory data source implementation,
/// and an application shouldn't directly refer to this class.
class TreeNodeRRset : boost::noncopyable, public dns::AbstractRRset {
public:
    /// \brief Normal case constructor.
    ///
    /// This class object is basically defined with a \c ZoneNode and
    /// \c RdataSet.  The former determines the owner name of the RRset,
    /// and the latter provides the rest of the RRset parameters.
    /// Since the RR class is maintained outside of the \c ZoneData,
    /// it must be explicitly given as a constructor parameter.
    ///
    /// The \c RdataSet may or may not be associated with RRSIGs.  It's
    /// fixed at the load time, but depending on the query context they
    /// may or may not be requested (and supposed to be visible to the
    /// caller).  Since \c rdataset cannot be modified at the time of
    /// construction, a separate parameter (\c dnssec_ok) controls this
    /// policy.  Any associated RRSIGs are visible if and only if \c dnssec_ok
    /// is true.  If the RRset is not associated with RRSIGs, the value
    /// does not have any effect.
    ///
    /// In some rare cases \c rdataset may only consist of RRSIGs (when
    /// the zone contains an RRSIG that doesn't have covered RRsets).
    /// This class works for such cases, too.
    ///
    /// \throw none
    ///
    /// \param rrclass The RR class of the RRset.  This must be consistent
    /// with the corresponding zone class.
    /// \param node The \c ZoneNode for the \c RRset.  Must not be NULL.
    /// \param rdataset The \c RdataSet for the \c RRset.  Must not be NULL.
    /// \param dnssec_ok Whether the RRSIGs for the RRset (if associated)
    /// should be visible to the caller.
    TreeNodeRRset(const dns::RRClass& rrclass, const ZoneNode* node,
                  const RdataSet* rdataset, bool dnssec_ok) :
        node_(node), rdataset_(rdataset),
        rrsig_count_(rdataset_->getSigRdataCount()), rrclass_(rrclass),
        dnssec_ok_(dnssec_ok), name_(NULL), realname_(NULL), ttl_(NULL)
    {}

    /// \brief Constructor for wildcard-expanded owner name.
    ///
    /// This constructor is mostly the same as the other version, but takes
    /// an extra parameter, \c realname.  It effectively overrides the owner
    /// name of the RRset; wherever the owner name is used (e.g., in the
    /// \c toWire() method), the specified name will be used instead of
    /// the name associated with \c node.
    ///
    /// The expected usage is \c node has a wildcard name (such as
    /// *.example.com), but this constructor does not enforce the assumption.
    ///
    /// \throw std::bad_alloc Memory allocation fails
    TreeNodeRRset(const dns::Name& realname, const dns::RRClass& rrclass,
                  const ZoneNode* node, const RdataSet* rdataset,
                  bool dnssec_ok) :
        node_(node), rdataset_(rdataset),
        rrsig_count_(rdataset_->getSigRdataCount()), rrclass_(rrclass),
        dnssec_ok_(dnssec_ok), name_(NULL), realname_(new dns::Name(realname)),
	ttl_(NULL)
    {}

    virtual ~TreeNodeRRset() {
        delete realname_;
        delete ttl_;
        delete name_;
    }

    virtual unsigned int getRdataCount() const {
        return (rdataset_->getRdataCount());
    }

    virtual const dns::Name& getName() const;
    virtual const dns::RRClass& getClass() const {
        return (rrclass_);
    }

    virtual const dns::RRType& getType() const {
        return (rdataset_->type);
    }

    /// \brief Specialized version of \c getTTL() for \c TreeNodeRRset.
    virtual const dns::RRTTL& getTTL() const;

    /// \brief Specialized version of \c setName() for \c TreeNodeRRset.
    ///
    /// It throws \c isc::Unexpected unconditionally.
    virtual void setName(const dns::Name& name);

    /// \brief Specialized version of \c setName() for \c TreeNodeRRset.
    ///
    /// It throws \c isc::Unexpected unconditionally.
    virtual void setTTL(const dns::RRTTL& ttl);

    virtual std::string toText() const;

    virtual unsigned int toWire(dns::AbstractMessageRenderer& renderer) const;

    /// \brief Specialized version of \c toWire(buffer) for \c TreeNodeRRset.
    ///
    /// It throws \c isc::Unexpected unconditionally.
    virtual unsigned int toWire(util::OutputBuffer& buffer) const;

    /// \brief Specialized version of \c addRdata() for \c TreeNodeRRset.
    ///
    /// It throws \c isc::Unexpected unconditionally.
    virtual void addRdata(dns::rdata::ConstRdataPtr rdata);

    /// \brief Specialized version of \c addRdata() for \c TreeNodeRRset.
    ///
    /// It throws \c isc::Unexpected unconditionally.
    virtual void addRdata(const dns::rdata::Rdata& rdata);

    virtual dns::RdataIteratorPtr getRdataIterator() const;

    /// \brief Specialized version of \c getRRsig() for \c TreeNodeRRset.
    ///
    /// It throws \c isc::Unexpected unconditionally.
    virtual dns::RRsetPtr getRRsig() const;

    virtual unsigned int getRRsigDataCount() const {
        return (dnssec_ok_ ? rrsig_count_ : 0);
    }

    ///
    /// \name Specialized version of RRsig related methods for
    /// \c TreeNodeRRset.
    ///
    /// These throw \c isc::Unexpected unconditionally.
    ////
    //@{
    virtual void addRRsig(const dns::rdata::ConstRdataPtr& rdata);
    virtual void addRRsig(const dns::rdata::RdataPtr& rdata);
    virtual void addRRsig(const dns::AbstractRRset& sigs);
    virtual void addRRsig(const dns::ConstRRsetPtr& sigs);
    virtual void addRRsig(const dns::RRsetPtr& sigs);
    virtual void removeRRsig();
    //@}

    /// \brief Specialized version of \c isSameKind() for \c TreeNodeRRset.
    ///
    /// As a kind of optimization, this implementation exploits the assumption
    /// of how \c TreeNodeRRset objects are created: They must be always
    /// created inside the in-memory data source finder implementation,
    /// and they are constructed with the \c realname parameter if and only
    /// if the corresponding query name is subject to wildcard substitution.
    ///
    /// So, if the given RRset is of \c TreeNodeRRset, and one and only one of
    /// of them has \c realname, they are considered to have different names.
    ///
    /// Also, this implementation does not compare RR classes explicitly;
    /// if two \c TreeNodeRRset objects belong to different RR classes,
    /// they should belong to different zone trees (according to the assumption
    /// of how the zone data are built), and therefore they cannot be at
    /// same zone node.  So it's sufficient to compare the (address of the)
    /// node; if they are different they cannot be of the same kind.
    virtual bool isSameKind(const dns::AbstractRRset& abs_other) const;

private:
    dns::RdataIteratorPtr getSigRdataIterator() const;

    // Common backend for getRdataIterator() and getSigRdataIterator()
    dns::RdataIteratorPtr getRdataIteratorInternal(bool is_rrsig,
                                                   size_t count) const;

    // Return \c LabelSequence for the owner name regardless of how this
    /// class is constructed (with or without 'realname')
    dns::LabelSequence getOwnerLabels(
        uint8_t labels_buf[dns::LabelSequence::MAX_SERIALIZED_LENGTH]) const
    {
        if (realname_ != NULL) {
            return (dns::LabelSequence(*realname_));
        }
        return (node_->getAbsoluteLabels(labels_buf));
    }

    const ZoneNode* node_;
    const RdataSet* rdataset_;
    const size_t rrsig_count_;
    const dns::RRClass rrclass_;
    const bool dnssec_ok_;
    mutable dns::Name* name_;
    const dns::Name* const realname_;
    mutable dns::RRTTL* ttl_;
};

typedef boost::shared_ptr<TreeNodeRRset> TreeNodeRRsetPtr;

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_TREENODE_RRSET_H

// Local Variables:
// mode: c++
// End:
