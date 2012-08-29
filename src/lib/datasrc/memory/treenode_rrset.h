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

#include <datasrc/memory/domaintree.h> // CLEAN UP: only for temporary setup
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/rdataset.h>

#include <string>

namespace isc {
namespace datasrc {
namespace memory {

class TreeNodeRRset : public dns::AbstractRRset {
public:
    TreeNodeRRset(const dns::RRClass& rrclass, const ZoneNode* node,
                  const RdataSet* rdataset, bool dnssec_ok) :
        node_(node), rdataset_(rdataset),
        rrsig_count_(rdataset_->getSigRdataCount()), rrclass_(rrclass),
        dnssec_ok_(dnssec_ok), name_(NULL), realname_buf_(NULL)
    {}

    TreeNodeRRset(const dns::Name& realname, const dns::RRClass& rrclass,
                  const ZoneNode* node, const RdataSet* rdataset,
                  bool dnssec_ok);

    virtual ~TreeNodeRRset() {
        delete[] realname_buf_;
        delete name_;
    }

    virtual unsigned int getRdataCount() const {
        return (rdataset_->getRdataCount());
    }

    // needed
    virtual const dns::Name& getName() const;
    virtual const dns::RRClass& getClass() const {
        return (rrclass_);
    }

    virtual const dns::RRType& getType() const {
        return (rdataset_->type);
    }

    virtual const dns::RRTTL& getTTL() const;
    virtual void setName(const dns::Name& name);
    virtual void setTTL(const dns::RRTTL& ttl);
    // needed
    virtual std::string toText() const;

    // needed
    virtual unsigned int toWire(dns::AbstractMessageRenderer& renderer) const;
    virtual unsigned int toWire(util::OutputBuffer& buffer) const;
    virtual void addRdata(dns::rdata::ConstRdataPtr rdata);
    virtual void addRdata(const dns::rdata::Rdata& rdata);

    // needed
    virtual dns::RdataIteratorPtr getRdataIterator() const;
    virtual dns::RRsetPtr getRRsig() const;

    virtual unsigned int getRRsigDataCount() const {
        return (dnssec_ok_ ? rrsig_count_ : 0);
    }

    virtual void addRRsig(const dns::rdata::ConstRdataPtr& rdata);
    virtual void addRRsig(const dns::rdata::RdataPtr& rdata);
    virtual void addRRsig(const dns::AbstractRRset& sigs);
    virtual void addRRsig(const dns::ConstRRsetPtr& sigs);
    virtual void addRRsig(const dns::RRsetPtr& sigs);
    virtual void removeRRsig();

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
    dns::RdataIteratorPtr getRdataIteratorInternal(bool is_rrsig,
                                                   size_t count) const;
    dns::LabelSequence getOwnerLabels(
        uint8_t labels_buf[dns::LabelSequence::MAX_SERIALIZED_LENGTH]) const
    {
        if (realname_buf_ != NULL) {
            return (dns::LabelSequence(realname_buf_));
        }
        return (node_->getAbsoluteLabels(labels_buf));
    }

    // A helper for isSameKind() to check if 'this' and 'other' has
    // the same "real" name in case at least either is constructed with
    // a real name.
    bool hasSameRealName(const TreeNodeRRset& other) const;

    const ZoneNode* node_;
    const RdataSet* rdataset_;
    const size_t rrsig_count_;
    const dns::RRClass rrclass_;
    const bool dnssec_ok_;
    mutable dns::Name* name_;
    uint8_t* realname_buf_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_TREENODE_RRSET_H

// Local Variables:
// mode: c++
// End:
