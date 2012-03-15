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

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/nsec3hash.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrsetlist.h>
#include <dns/masterload.h>

#include <datasrc/memory_datasrc.h>
#include <datasrc/rbtree.h>
#include <datasrc/rbnode_rrset.h>
#include <datasrc/logger.h>
#include <datasrc/iterator.h>
#include <datasrc/data_source.h>
#include <datasrc/factory.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <map>
#include <utility>
#include <cctype>
#include <cassert>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using boost::scoped_ptr;

namespace isc {
namespace datasrc {

using namespace internal;

namespace {
// Some type aliases

// RRset specified for this implementation
typedef boost::shared_ptr<internal::RBNodeRRset> RBNodeRRsetPtr;
typedef boost::shared_ptr<const internal::RBNodeRRset> ConstRBNodeRRsetPtr;

/*
 * Each domain consists of some RRsets. They will be looked up by the
 * RRType.
 *
 * The use of map is questionable with regard to performance - there'll
 * be usually only few RRsets in the domain, so the log n benefit isn't
 * much and a vector/array might be faster due to its simplicity and
 * continuous memory location. But this is unlikely to be a performance
 * critical place and map has better interface for the lookups, so we use
 * that.
 */
typedef map<RRType, ConstRBNodeRRsetPtr> Domain;
typedef Domain::value_type DomainPair;
typedef boost::shared_ptr<Domain> DomainPtr;
// The tree stores domains
typedef RBTree<Domain> DomainTree;
typedef RBNode<Domain> DomainNode;

// In the following dedicated namespace we define a few application-specific
// RBNode flags.  We use a separate namespace so we can consolidate the
// definition in a single place, which would hopefully reduce the risk of
// collisions.
// (Note: it's within an unnamed namespace, so effectively private.)
namespace domain_flag {
// This flag indicates the node is at a "wildcard level" (in short, it means
// one of the node's immediate child is a wildcard).  See addWildcards()
// for more details.
const DomainNode::Flags WILD = DomainNode::FLAG_USER1;

// This flag is used for additional record shortcut.  If a node has this
// flag, it's under a zone cut for a delegation to a child zone.
// Note: for a statically built zone this information is stable, but if we
// change the implementation to be dynamically modifiable, it may not be
// realistic to keep this flag update for all affected nodes, and we may
// have to reconsider the mechanism.
const DomainNode::Flags GLUE = DomainNode::FLAG_USER2;
};

// Separate storage for NSEC3 RRs (and their RRSIGs).  It's an STL map
// from string to the NSEC3 RRset.  The map key is the first label
// (upper cased) of the owner name of the corresponding NSEC3 (i.e., map
// value).  We can use  the standard string comparison (if the comparison
// target is also upper cased) due to the nature of NSEC3 owner names.
//
// Note: We maintain the RRsets in the form of RBNodeRRset even if they are
// not stored in the RB tree.  The reason is because comparison can be
// more efficient if we make sure all RRsets returned from this module are
// of the same type.
typedef map<string, ConstRBNodeRRsetPtr> NSEC3Map;
typedef NSEC3Map::value_type NSEC3Pair;

// Actual zone data: Essentially a set of zone's RRs.  This is defined as
// a separate structure so that it'll be replaceable on reload.
struct ZoneData {
    ZoneData(const Name& origin) : domains_(true), origin_data_(NULL) {
        // We create the node for origin (it needs to exist anyway in future)
        domains_.insert(origin, &origin_data_);
        DomainPtr origin_domain(new Domain);
        origin_data_->setData(origin_domain);
    }

    // The main data (name + RRsets)
    DomainTree domains_;

    // Shortcut to the origin node, which should always exist
    DomainNode* origin_data_;

    // The optional NSEC3 related data
    struct NSEC3Data {
        NSEC3Data(const generic::NSEC3PARAM& nsec3param) :
            hash_(NSEC3Hash::create(nsec3param))
        {}
        NSEC3Data(const generic::NSEC3& nsec3) :
            hash_(NSEC3Hash::create(nsec3))
        {}
        NSEC3Map map_;    // Actual NSEC3 RRs
        const scoped_ptr<NSEC3Hash> hash_; // hash parameter/calculator
    };
    scoped_ptr<NSEC3Data> nsec3_data_; // non NULL only when it's NSEC3 signed
};
}

namespace internal {

/// \brief An encapsulation type for a pointer of an additional node
/// associated with an \c RBNodeRRset object.
///
/// Currently this is defined as a structure only so that it can declared
/// in rbnode_rrset.h; this is essentially a pointer to \c DomainNode.
/// In future, however, this structure may have other attributes.
struct AdditionalNodeInfo {
    AdditionalNodeInfo(DomainNode* node) : node_(node) {}
    DomainNode* node_;
};

//
// RBNodeRRset details
//
struct RBNodeRRsetImpl {
public:
    RBNodeRRsetImpl(const ConstRRsetPtr& rrset) : rrset_(rrset)
    {}

    ConstRRsetPtr rrset_;     ///< Underlying RRset
    scoped_ptr<vector<AdditionalNodeInfo> > additionals_;
};

RBNodeRRset::RBNodeRRset(const ConstRRsetPtr& rrset) :
    impl_(new RBNodeRRsetImpl(rrset))
{
}

RBNodeRRset::~RBNodeRRset() {
    delete impl_;
}

unsigned int
RBNodeRRset::getRdataCount() const {
    return (impl_->rrset_->getRdataCount());
}

const Name&
RBNodeRRset::getName() const {
    return (impl_->rrset_->getName());
}

const RRClass&
RBNodeRRset::getClass() const {
    return (impl_->rrset_->getClass());
}

const RRType&
RBNodeRRset::getType() const {
    return (impl_->rrset_->getType());
}

const RRTTL&
RBNodeRRset::getTTL() const {
    return (impl_->rrset_->getTTL());
}

void
RBNodeRRset::setName(const Name&) {
    isc_throw(isc::NotImplemented, "RBNodeRRset::setName() not supported");
}

void
RBNodeRRset::setTTL(const RRTTL&) {
    isc_throw(isc::NotImplemented, "RBNodeRRset::setTTL() not supported");
}

string
RBNodeRRset::toText() const {
    return (impl_->rrset_->toText());
}

unsigned int
RBNodeRRset::toWire(AbstractMessageRenderer& renderer) const {
    return (impl_->rrset_->toWire(renderer));
}

unsigned int
RBNodeRRset::toWire(isc::util::OutputBuffer& buffer) const {
    return (impl_->rrset_->toWire(buffer));
}

void
RBNodeRRset::addRdata(ConstRdataPtr) {
    isc_throw(isc::NotImplemented, "RBNodeRRset::addRdata() not supported");
}

void
RBNodeRRset::addRdata(const Rdata&) {
    isc_throw(isc::NotImplemented, "RBNodeRRset::addRdata() not supported");
}

RdataIteratorPtr
RBNodeRRset::getRdataIterator() const {
    return (impl_->rrset_->getRdataIterator());
}

RRsetPtr
RBNodeRRset::getRRsig() const {
    return (impl_->rrset_->getRRsig());
}

void
RBNodeRRset::addRRsig(const ConstRdataPtr& rdata) {
    AbstractRRset* p = const_cast<AbstractRRset*>(impl_->rrset_.get());
    p->addRRsig(rdata);
}

void
RBNodeRRset::addRRsig(const RdataPtr& rdata) {
    AbstractRRset* p = const_cast<AbstractRRset*>(impl_->rrset_.get());
    p->addRRsig(rdata);
}

void
RBNodeRRset::addRRsig(const AbstractRRset& sigs) {
    AbstractRRset* p = const_cast<AbstractRRset*>(impl_->rrset_.get());
    p->addRRsig(sigs);
}

void
RBNodeRRset::addRRsig(const ConstRRsetPtr& sigs) {
    AbstractRRset* p = const_cast<AbstractRRset*>(impl_->rrset_.get());
    p->addRRsig(sigs);
}

void
RBNodeRRset::addRRsig(const RRsetPtr& sigs) {
    AbstractRRset* p = const_cast<AbstractRRset*>(impl_->rrset_.get());
    p->addRRsig(sigs);
}

void
RBNodeRRset::removeRRsig() {
    AbstractRRset* p = const_cast<AbstractRRset*>(impl_->rrset_.get());
    p->removeRRsig();
}

ConstRRsetPtr
RBNodeRRset::getUnderlyingRRset() const {
    return (impl_->rrset_);
}

void
RBNodeRRset::addAdditionalNode(const AdditionalNodeInfo& additional) {
    // Lazy initialization
    if (!impl_->additionals_) {
        impl_->additionals_.reset(new vector<AdditionalNodeInfo>);
    }
    impl_->additionals_->push_back(additional);
}

const vector<AdditionalNodeInfo>*
RBNodeRRset::getAdditionalNodes() const {
    return (impl_->additionals_.get());
}

void
RBNodeRRset::copyAdditionalNodes(RBNodeRRset& dst) const {
    if (impl_->additionals_) {
        dst.impl_->additionals_.reset(
            new vector<AdditionalNodeInfo>(impl_->additionals_->begin(),
                                           impl_->additionals_->end()));
    }
}

} // end of internal

namespace {
// Specialized version of ZoneFinder::ResultContext, which specifically
// holds rrset in the form of RBNodeRRset.
struct RBNodeResultContext {
    /// \brief Constructor
    ///
    /// The first three parameters correspond to those of
    /// ZoneFinder::ResultContext.  If node is non NULL, it specifies the
    /// found RBNode in the search.
    RBNodeResultContext(ZoneFinder::Result code_param,
                        ConstRBNodeRRsetPtr rrset_param,
                        ZoneFinder::FindResultFlags flags_param,
                        const DomainNode* node) :
        code(code_param), rrset(rrset_param), flags(flags_param),
        found_node(node)
    {}

    const ZoneFinder::Result code;
    const ConstRBNodeRRsetPtr rrset;
    const ZoneFinder::FindResultFlags flags;
    const DomainNode* const found_node;
};
}

class InMemoryZoneFinder::Context : public ZoneFinder::Context {
public:
    /// \brief Constructor.
    ///
    /// Note that we don't have a specific constructor for the findAll() case.
    /// For (successful) type ANY query, found_node points to the
    /// corresponding RB node, which is recorded within this specialized
    /// context.
    Context(ZoneFinder& finder, ZoneFinder::FindOptions options,
            const RBNodeResultContext& result) :
        ZoneFinder::Context(finder, options,
                            ResultContext(result.code, result.rrset,
                                          result.flags)),
        rrset_(result.rrset), found_node_(result.found_node)
    {}

protected:
    virtual void getAdditionalImpl(const vector<RRType>& requested_types,
                                   vector<ConstRRsetPtr>& result)
    {
        if (!rrset_) {
            // In this case this context should encapsulate the result of
            // findAll() and found_node_ should point to a valid answer node.
            if (found_node_ == NULL || found_node_->isEmpty()) {
                isc_throw(isc::Unexpected,
                          "Invalid call to in-memory getAdditional: caller's "
                          "bug or broken zone");
            }
            BOOST_FOREACH(const DomainPair& dom_it, *found_node_->getData()) {
                getAdditionalForRRset(*dom_it.second, requested_types,
                                      result);
            }
        } else {
            getAdditionalForRRset(*rrset_, requested_types, result);
        }
    }

private:
    // Retrieve additional RRsets for a given RRset associated in the context.
    // The process is straightforward: it examines the link to
    // AdditionalNodeInfo vector (if set), and find RRsets of the requested
    // type for each node.
    static void getAdditionalForRRset(const RBNodeRRset& rrset,
                                      const vector<RRType>& requested_types,
                                      vector<ConstRRsetPtr>& result)
    {
        const vector<AdditionalNodeInfo>* additionals_ =
            rrset.getAdditionalNodes();
        if (additionals_ == NULL) {
            return;
        }
        const bool glue_ok = (rrset.getType() == RRType::NS());
        BOOST_FOREACH(const AdditionalNodeInfo& additional, *additionals_) {
            assert(additional.node_ != NULL);
            if (additional.node_->isEmpty()) {
                continue;
            }
            if (!glue_ok && additional.node_->getFlag(domain_flag::GLUE)) {
                continue;
            }
            BOOST_FOREACH(const RRType& rrtype, requested_types) {
                Domain::const_iterator found =
                    additional.node_->getData()->find(rrtype);
                if (found != additional.node_->getData()->end()) {
                    // TODO: wildcard consideration
                    result.push_back(found->second);
                }
            }
        }
    }

    const ConstRBNodeRRsetPtr rrset_;
    const DomainNode* const found_node_;
};

// Private data and hidden methods of InMemoryZoneFinder
struct InMemoryZoneFinder::InMemoryZoneFinderImpl {
    // Constructor
    InMemoryZoneFinderImpl(const RRClass& zone_class, const Name& origin) :
        zone_class_(zone_class), origin_(origin),
        zone_data_(new ZoneData(origin_))
    {}

    // Information about the zone
    RRClass zone_class_;
    Name origin_;
    string file_name_;

    // The actual zone data
    scoped_ptr<ZoneData> zone_data_;

    // Add the necessary magic for any wildcard contained in 'name'
    // (including itself) to be found in the zone.
    //
    // In order for wildcard matching to work correctly in find(),
    // we must ensure that a node for the wildcarding level exists in the
    // backend RBTree.
    // E.g. if the wildcard name is "*.sub.example." then we must ensure
    // that "sub.example." exists and is marked as a wildcard level.
    // Note: the "wildcarding level" is for the parent name of the wildcard
    // name (such as "sub.example.").
    //
    // We also perform the same trick for empty wild card names possibly
    // contained in 'name' (e.g., '*.foo.example' in 'bar.*.foo.example').
    void addWildcards(DomainTree& domains, const Name& name) {
        Name wname(name);
        const unsigned int labels(wname.getLabelCount());
        const unsigned int origin_labels(origin_.getLabelCount());
        for (unsigned int l = labels;
             l > origin_labels;
             --l, wname = wname.split(1)) {
            if (wname.isWildcard()) {
                LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ADD_WILDCARD).
                    arg(name);
                // Ensure a separate level exists for the "wildcarding" name,
                // and mark the node as "wild".
                DomainNode* node;
                DomainTree::Result result(domains.insert(wname.split(1),
                                                         &node));
                assert(result == DomainTree::SUCCESS ||
                       result == DomainTree::ALREADYEXISTS);
                node->setFlag(domain_flag::WILD);

                // Ensure a separate level exists for the wildcard name.
                // Note: for 'name' itself we do this later anyway, but the
                // overhead should be marginal because wildcard names should
                // be rare.
                result = domains.insert(wname, &node);
                assert(result == DomainTree::SUCCESS ||
                       result == DomainTree::ALREADYEXISTS);
            }
        }
    }

    // A helper predicate used in contextCheck() to check if a given domain
    // name has a RRset of type different than NSEC.
    static bool isNotNSEC(const DomainPair& element) {
        return (element.second->getType() != RRType::NSEC());
    }

    /*
     * Does some checks in context of the data that are already in the zone.
     * Currently checks for forbidden combinations of RRsets in the same
     * domain (CNAME+anything, DNAME+NS).
     *
     * If such condition is found, it throws AddError.
     */
    void contextCheck(const AbstractRRset& rrset, const Domain& domain) const {
        // Ensure CNAME and other type of RR don't coexist for the same
        // owner name except with NSEC, which is the only RR that can coexist
        // with CNAME (and also RRSIG, which is handled separately)
        if (rrset.getType() == RRType::CNAME()) {
            if (find_if(domain.begin(), domain.end(), isNotNSEC)
                != domain.end()) {
                LOG_ERROR(logger, DATASRC_MEM_CNAME_TO_NONEMPTY).
                    arg(rrset.getName());
                isc_throw(AddError, "CNAME can't be added with other data for "
                          << rrset.getName());
            }
        } else if (rrset.getType() != RRType::NSEC() &&
                   domain.find(RRType::CNAME()) != domain.end()) {
            LOG_ERROR(logger, DATASRC_MEM_CNAME_COEXIST).arg(rrset.getName());
            isc_throw(AddError, "CNAME and " << rrset.getType() <<
                      " can't coexist for " << rrset.getName());
        }

        /*
         * Similar with DNAME, but it must not coexist only with NS and only in
         * non-apex domains.
         * RFC 2672 section 3 mentions that it is implied from it and RFC 2181
         */
        if (rrset.getName() != origin_ &&
            // Adding DNAME, NS already there
            ((rrset.getType() == RRType::DNAME() &&
            domain.find(RRType::NS()) != domain.end()) ||
            // Adding NS, DNAME already there
            (rrset.getType() == RRType::NS() &&
            domain.find(RRType::DNAME()) != domain.end())))
        {
            LOG_ERROR(logger, DATASRC_MEM_DNAME_NS).arg(rrset.getName());
            isc_throw(AddError, "DNAME can't coexist with NS in non-apex "
                "domain " << rrset.getName());
        }
    }

    // Validate rrset before adding it to the zone.  If something is wrong
    // it throws an exception.  It doesn't modify the zone, and provides
    // the strong exception guarantee.
    void addValidation(const ConstRRsetPtr rrset) {
        if (!rrset) {
            isc_throw(NullRRset, "The rrset provided is NULL");
        }
        if (rrset->getRdataCount() == 0) {
            isc_throw(AddError, "The rrset provided is empty: " <<
                      rrset->getName() << "/" << rrset->getType());
        }
        // Check for singleton RRs. It should probably handled at a different
        // layer in future.
        if ((rrset->getType() == RRType::CNAME() ||
            rrset->getType() == RRType::DNAME()) &&
            rrset->getRdataCount() > 1)
        {
            // XXX: this is not only for CNAME or DNAME. We should generalize
            // this code for all other "singleton RR types" (such as SOA) in a
            // separate task.
            LOG_ERROR(logger, DATASRC_MEM_SINGLETON).arg(rrset->getName()).
                arg(rrset->getType());
            isc_throw(AddError, "multiple RRs of singleton type for "
                      << rrset->getName());
        }
        // NSEC3/NSEC3PARAM is not a "singleton" per protocol, but this
        // implementation requests it be so at the moment.
        if ((rrset->getType() == RRType::NSEC3() ||
             rrset->getType() == RRType::NSEC3PARAM()) &&
            rrset->getRdataCount() > 1) {
            isc_throw(AddError, "Multiple NSEC3/NSEC3PARAM RDATA is given for "
                      << rrset->getName() << " which isn't supported");
        }

        NameComparisonResult compare(origin_.compare(rrset->getName()));
        if (compare.getRelation() != NameComparisonResult::SUPERDOMAIN &&
            compare.getRelation() != NameComparisonResult::EQUAL)
        {
            LOG_ERROR(logger, DATASRC_MEM_OUT_OF_ZONE).arg(rrset->getName()).
                arg(origin_);
            isc_throw(OutOfZone, "The name " << rrset->getName() <<
                " is not contained in zone " << origin_);
        }

        // Some RR types do not really work well with a wildcard.
        // Even though the protocol specifically doesn't completely ban such
        // usage, we refuse to load a zone containing such RR in order to
        // keep the lookup logic simpler and more predictable.
        // See RFC4592 and (for DNAME) draft-ietf-dnsext-rfc2672bis-dname
        // for more technical background.  Note also that BIND 9 refuses
        // NS at a wildcard, so in that sense we simply provide compatible
        // behavior.
        if (rrset->getName().isWildcard()) {
            if (rrset->getType() == RRType::NS()) {
                LOG_ERROR(logger, DATASRC_MEM_WILDCARD_NS).
                    arg(rrset->getName());
                isc_throw(AddError, "Invalid NS owner name (wildcard): " <<
                          rrset->getName());
            }
            if (rrset->getType() == RRType::DNAME()) {
                LOG_ERROR(logger, DATASRC_MEM_WILDCARD_DNAME).
                    arg(rrset->getName());
                isc_throw(AddError, "Invalid DNAME owner name (wildcard): " <<
                          rrset->getName());
            }
        }

        // Owner names of NSEC3 have special format as defined in RFC5155,
        // and cannot be a wildcard name or must be one label longer than
        // the zone origin.  While the RFC doesn't prohibit other forms of
        // names, no sane zone would have such names for NSEC3.
        // BIND 9 also refuses NSEC3 at wildcard.
        if (rrset->getType() == RRType::NSEC3() &&
            (rrset->getName().isWildcard() ||
             rrset->getName().getLabelCount() !=
             origin_.getLabelCount() + 1)) {
            LOG_ERROR(logger, DATASRC_BAD_NSEC3_NAME).
                arg(rrset->getName());
            isc_throw(AddError, "Invalid NSEC3 owner name: " <<
                      rrset->getName());
        }
    }

    result::Result addRRsig(const ConstRRsetPtr sig_rrset, ZoneData& zone_data)
    {
        // Check consistency of the type covered.
        // We know the RRset isn't empty, so the following check is safe.
        RdataIteratorPtr rit = sig_rrset->getRdataIterator();
        const RRType covered = dynamic_cast<const generic::RRSIG&>(
            rit->getCurrent()).typeCovered();
        for (rit->next(); !rit->isLast(); rit->next()) {
            if (dynamic_cast<const generic::RRSIG&>(
                    rit->getCurrent()).typeCovered() != covered) {
                isc_throw(AddError, "RRSIG contains mixed covered types: "
                          << sig_rrset->toText());
            }
        }

        // Find the RRset to be covered; if not found, treat it as an error
        // for now.
        ConstRRsetPtr covered_rrset;
        if (covered != RRType::NSEC3()) {
            DomainNode* node = NULL;
            if (zone_data.domains_.find(sig_rrset->getName(), &node) !=
                DomainTree::EXACTMATCH || node == NULL || !node->getData()) {
                isc_throw(AddError,
                          "RRSIG is being added, but no RR to be covered: "
                          << sig_rrset->getName());
            }
            const Domain::const_iterator it = node->getData()->find(covered);
            if (it != node->getData()->end()) {
                covered_rrset = it->second;
            }
        } else {
            // In case of NSEC3 if something is found it must be NSEC3 RRset
            // under the assumption of our current implementation.
            if (zone_data.nsec3_data_) {
                // Convert the first label to upper-cased text.  Note that
                // for a valid NSEC3 RR the label should only consist of
                // positive 8-bit char values, so using toupper(int) should be
                // safe (if it's a bogus label for NSEC3 the zone won't work
                // anyway).  Also note the '::' below: g++'s STL implementation
                // seems to require it to toupper to make this compile.
                string fst_label =
                    sig_rrset->getName().split(0, 1).toText(true);
                transform(fst_label.begin(), fst_label.end(),
                          fst_label.begin(), ::toupper);

                NSEC3Map::const_iterator found =
                    zone_data.nsec3_data_->map_.find(fst_label);
                if (found != zone_data.nsec3_data_->map_.end()) {
                    covered_rrset = found->second;
                    assert(covered_rrset->getType() == covered);
                }
            }
        }
        if (!covered_rrset) {
            isc_throw(AddError, "RRSIG is being added, but no RR of "
                      "covered type found: " << sig_rrset->toText());
        }

        // The current implementation doesn't allow an existing RRSIG to be
        // overridden (or updated with additional ones).
        if (covered_rrset->getRRsig()) {
            isc_throw(AddError,
                      "RRSIG is being added to override an existing one: "
                      << sig_rrset->toText());
        }

        // All okay, setting the RRSIG.
        // XXX: we break const-ness of the covered RRsets.  In practice the
        // ownership of these RRsets would have been given to us so it should
        // be safe, but it's still a very bad practice.
        // We'll fix this problem anyway when we update the underlying
        // representation so that it's more space efficient.
        // Note: there's a slight chance of getting an exception.
        // As noted in add(), we give up strong exception guarantee in such
        // cases.
        boost::const_pointer_cast<AbstractRRset>(covered_rrset)->addRRsig(sig_rrset);

        return (result::SUCCESS);
    }

    result::Result addNSEC3(const ConstRRsetPtr rrset, ZoneData& zone_data) {
        // We know rrset has exactly one RDATA
        const generic::NSEC3& nsec3_rdata =
            dynamic_cast<const generic::NSEC3&>(
                rrset->getRdataIterator()->getCurrent());

        // If we've not done any NSEC3 setup for the zone, do it now;
        // otherwise check parameter consistency.
        if (!zone_data.nsec3_data_) {
            zone_data.nsec3_data_.reset(new ZoneData::NSEC3Data(nsec3_rdata));
        } else if (!zone_data.nsec3_data_->hash_->match(nsec3_rdata)) {
            isc_throw(AddError, "NSEC3 with inconsistent parameters: " <<
                      rrset->toText());
        }

        string fst_label = rrset->getName().split(0, 1).toText(true);
        transform(fst_label.begin(), fst_label.end(), fst_label.begin(),
                  ::toupper);

        // Our current implementation doesn't allow an existing NSEC3 to be
        // updated/overridden.
        if (zone_data.nsec3_data_->map_.find(fst_label) !=
            zone_data.nsec3_data_->map_.end()) {
            return (result::EXIST);
        }

        zone_data.nsec3_data_->map_.insert(
            NSEC3Pair(fst_label, ConstRBNodeRRsetPtr(new RBNodeRRset(rrset))));
        return (result::SUCCESS);
    }

    /*
     * Implementation of longer methods. We put them here, because the
     * access is without the impl_-> and it will get inlined anyway.
     */
    // Implementation of InMemoryZoneFinder::add
    result::Result add(const ConstRRsetPtr& rawrrset, ZoneData& zone_data,
                       vector<RBNodeRRset*>* need_additionals)
    {
        // Sanitize input.  This will cause an exception to be thrown
        // if the input RRset is empty.
        addValidation(rawrrset);

        // OK, can add the RRset.
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ADD_RRSET).
            arg(rawrrset->getName()).arg(rawrrset->getType()).arg(origin_);

        // ... although instead of loading the RRset directly, we encapsulate
        // it within an RBNodeRRset.  This contains additional information that
        // speeds up queries.
        RBNodeRRsetPtr rrset(new RBNodeRRset(rawrrset));

        if (rrset->getType() == RRType::NSEC3()) {
            return (addNSEC3(rrset, zone_data));
        }

        // RRSIGs are special in various points, so we handle it in a
        // separate dedicated method.
        if (rrset->getType() == RRType::RRSIG()) {
            return (addRRsig(rrset, zone_data));
        }

        // Add wildcards possibly contained in the owner name to the domain
        // tree.
        // Note: this can throw an exception, breaking strong exception
        // guarantee.  (see also the note for contextCheck() below).
        addWildcards(zone_data.domains_, rrset->getName());

        // Get the node
        DomainNode* node;
        DomainTree::Result result = zone_data.domains_.insert(rrset->getName(),
                                                              &node);
        // Just check it returns reasonable results
        assert((result == DomainTree::SUCCESS ||
                result == DomainTree::ALREADYEXISTS) && node!= NULL);

        // Now get the domain
        DomainPtr domain;
        // It didn't exist yet, create it
        if (node->isEmpty()) {
            domain.reset(new Domain);
            node->setData(domain);
        } else { // Get existing one
            domain = node->getData();
        }

        // Checks related to the surrounding data.
        // Note: when the check fails and the exception is thrown, it may
        // break strong exception guarantee.  At the moment we prefer
        // code simplicity and don't bother to introduce complicated
        // recovery code.
        contextCheck(*rrset, *domain);

        // Try inserting the rrset there
        if (domain->insert(DomainPair(rrset->getType(), rrset)).second) {
            // Ok, we just put it in

            // If this RRset creates a zone cut at this node, mark the node
            // indicating the need for callback in find().
            if (rrset->getType() == RRType::NS() &&
                rrset->getName() != origin_) {
                node->setFlag(DomainNode::FLAG_CALLBACK);
                // If it is DNAME, we have a callback as well here
            } else if (rrset->getType() == RRType::DNAME()) {
                node->setFlag(DomainNode::FLAG_CALLBACK);
            }

            if (need_additionals != NULL &&
                (rrset->getType() == RRType::NS() ||
                 rrset->getType() == RRType::MX())) {
                need_additionals->push_back(rrset.get());
            }

            // If we've added NSEC3PARAM at zone origin, set up NSEC3 specific
            // data or check consistency with already set up parameters.
            if (rrset->getType() == RRType::NSEC3PARAM() &&
                rrset->getName() == origin_) {
                // We know rrset has exactly one RDATA
                const generic::NSEC3PARAM& param =
                    dynamic_cast<const generic::NSEC3PARAM&>(
                        rrset->getRdataIterator()->getCurrent());

                if (!zone_data.nsec3_data_) {
                    zone_data.nsec3_data_.reset(
                        new ZoneData::NSEC3Data(param));
                } else if (!zone_data.nsec3_data_->hash_->match(param)) {
                    isc_throw(AddError, "NSEC3PARAM with inconsistent "
                              "parameters: " << rrset->toText());
                }
            }
            return (result::SUCCESS);
        } else {
            // The RRSet of given type was already there
            return (result::EXIST);
        }
    }

    /*
     * Same as above, but it checks the return value and if it already exists,
     * it throws.
     */
    void addFromLoad(const ConstRRsetPtr& set, ZoneData* zone_data,
                     vector<RBNodeRRset*>* need_additionals)
    {
        switch (add(set, *zone_data, need_additionals)) {
        case result::EXIST:
            LOG_ERROR(logger, DATASRC_MEM_DUP_RRSET).
                arg(set->getName()).arg(set->getType());
            isc_throw(dns::MasterLoadError, "Duplicate rrset: " <<
                      set->toText());
        case result::SUCCESS:
            return;
        default:
            assert(0);
        }
    }

    // Maintain intermediate data specific to the search context used in
    /// \c find().
    ///
    /// It will be passed to \c zonecutCallback() and record a possible
    /// zone cut node and related RRset (normally NS or DNAME).
    struct FindState {
        FindState(FindOptions options) :
            zonecut_node_(NULL),
            dname_node_(NULL),
            options_(options)
        {}
        const DomainNode* zonecut_node_;
        const DomainNode* dname_node_;
        ConstRBNodeRRsetPtr rrset_;
        const FindOptions options_;
    };

    // A callback called from possible zone cut nodes and nodes with DNAME.
    // This will be passed from the \c find() method to \c RBTree::find().
    static bool cutCallback(const DomainNode& node, FindState* state) {
        // We need to look for DNAME first, there's allowed case where
        // DNAME and NS coexist in the apex. DNAME is the one to notice,
        // the NS is authoritative, not delegation (corner case explicitly
        // allowed by section 3 of 2672)
        const Domain::const_iterator foundDNAME(node.getData()->find(
            RRType::DNAME()));
        if (foundDNAME != node.getData()->end()) {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                      DATASRC_MEM_DNAME_ENCOUNTERED);
            state->dname_node_ = &node;
            state->rrset_ = foundDNAME->second;
            // No more processing below the DNAME (RFC 2672, section 3
            // forbids anything to exist below it, so there's no need
            // to actually search for it). This is strictly speaking
            // a different way than described in 4.1 of that RFC,
            // but because of the assumption in section 3, it has the
            // same behaviour.
            return (true);
        }

        // Look for NS
        const Domain::const_iterator foundNS(node.getData()->find(
            RRType::NS()));
        if (foundNS != node.getData()->end()) {
            // We perform callback check only for the highest zone cut in the
            // rare case of nested zone cuts.
            if (state->zonecut_node_ != NULL) {
                return (false);
            }

            LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_MEM_NS_ENCOUNTERED);

            // BIND 9 checks if this node is not the origin.  That's probably
            // because it can support multiple versions for dynamic updates
            // and IXFR, and it's possible that the callback is called at
            // the apex and the DNAME doesn't exist for a particular version.
            // It cannot happen for us (at least for now), so we don't do
            // that check.
            state->zonecut_node_ = &node;
            state->rrset_ = foundNS->second;

            // Unless glue is allowed the search stops here, so we return
            // false; otherwise return true to continue the search.
            return ((state->options_ & FIND_GLUE_OK) == 0);
        }

        // This case should not happen because we enable callback only
        // when we add an RR searched for above.
        assert(0);
        // This is here to avoid warning (therefore compilation error)
        // in case assert is turned off. Otherwise we could get "Control
        // reached end of non-void function".
        return (false);
    }

    /*
     * Prepares a rrset to be return as a result.
     *
     * If rename is false, it returns the one provided. If it is true, it
     * creates a new rrset with the same data but with provided name.
     * In addition, if DNSSEC records are required by the original caller of
     * find(), it also creates expanded RRSIG based on the RRSIG of the
     * wildcard RRset.
     * It is designed for wildcard case, where we create the rrsets
     * dynamically.
     */
    static ConstRBNodeRRsetPtr prepareRRset(const Name& name,
                                            const ConstRBNodeRRsetPtr& rrset,
                                            bool rename, FindOptions options)
    {
        if (rename) {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_MEM_RENAME).
                arg(rrset->getName()).arg(name);
            RRsetPtr result_base(new RRset(name, rrset->getClass(),
                                           rrset->getType(),
                                           rrset->getTTL()));
            for (RdataIteratorPtr i(rrset->getRdataIterator()); !i->isLast();
                 i->next()) {
                result_base->addRdata(i->getCurrent());
            }
            if ((options & FIND_DNSSEC) != 0) {
                ConstRRsetPtr sig_rrset = rrset->getRRsig();
                if (sig_rrset) {
                    RRsetPtr result_sig(new RRset(name, sig_rrset->getClass(),
                                                  RRType::RRSIG(),
                                                  sig_rrset->getTTL()));
                    for (RdataIteratorPtr i(sig_rrset->getRdataIterator());
                         !i->isLast();
                         i->next())
                    {
                        result_sig->addRdata(i->getCurrent());
                    }
                    result_base->addRRsig(result_sig);
                }
            }
            RBNodeRRsetPtr result(new RBNodeRRset(result_base));
            rrset->copyAdditionalNodes(*result);
            return (result);
        } else {
            return (rrset);
        }
    }

    // Set up FindContext object as a return value of find(), taking into
    // account wildcard matches and DNSSEC information.  We set the NSEC/NSEC3
    // flag when applicable regardless of the find option; the caller would
    // simply ignore these when they didn't request DNSSEC related results.
    // When the optional parameter 'node' is given (in which case it should be
    // non NULL), it means it's a result of ANY query and the context should
    // remember the matched node.
    RBNodeResultContext createFindResult(Result code,
                                         ConstRBNodeRRsetPtr rrset,
                                         bool wild = false,
                                         const DomainNode* node = NULL) const
    {
        FindResultFlags flags = RESULT_DEFAULT;
        if (wild) {
            flags = flags | RESULT_WILDCARD;
        }
        if ((code == NXRRSET || code == NXDOMAIN || wild) &&
            zone_data_->nsec3_data_) {
            flags = flags | RESULT_NSEC3_SIGNED;
        }
        return (RBNodeResultContext(code, rrset, flags, node));
    }

    // Implementation of InMemoryZoneFinder::find
    RBNodeResultContext find(const Name& name, RRType type,
                             std::vector<ConstRRsetPtr>* target,
                             const FindOptions options) const
    {
        LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FIND).arg(name).
            arg(type);
        // Get the node
        DomainNode* node(NULL);
        FindState state(options);
        RBTreeNodeChain<Domain> node_path;
        bool rename(false);
        switch (zone_data_->domains_.find(name, &node, node_path, cutCallback,
                                          &state)) {
            case DomainTree::PARTIALMATCH:
                /*
                 * In fact, we could use a single variable instead of
                 * dname_node_ and zonecut_node_. But then we would need
                 * to distinquish these two cases by something else and
                 * it seemed little more confusing to me when I wrote it.
                 *
                 * Usually at most one of them will be something else than
                 * NULL (it might happen both are NULL, in which case we
                 * consider it NOT FOUND). There's one corner case when
                 * both might be something else than NULL and it is in case
                 * there's a DNAME under a zone cut and we search in
                 * glue OK mode ‒ in that case we don't stop on the domain
                 * with NS and ignore it for the answer, but it gets set
                 * anyway. Then we find the DNAME and we need to act by it,
                 * therefore we first check for DNAME and then for NS. In
                 * all other cases it doesn't matter, as at least one of them
                 * is NULL.
                 */
                if (state.dname_node_ != NULL) {
                    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DNAME_FOUND).
                        arg(state.rrset_->getName());
                    // We were traversing a DNAME node (and wanted to go
                    // lower below it), so return the DNAME
                    return (createFindResult(DNAME,
                                             prepareRRset(name, state.rrset_,
                                                          false, options)));
                }
                if (state.zonecut_node_ != NULL) {
                    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DELEG_FOUND).
                        arg(state.rrset_->getName());
                    return (createFindResult(DELEGATION,
                                             prepareRRset(name, state.rrset_,
                                                          false, options)));
                }

                // If the RBTree search stopped at a node for a super domain
                // of the search name, it means the search name exists in
                // the zone but is empty.  Treat it as NXRRSET.
                if (node_path.getLastComparisonResult().getRelation() ==
                    NameComparisonResult::SUPERDOMAIN) {
                    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_SUPER_STOP).
                        arg(name);
                    return (createFindResult(NXRRSET, ConstRBNodeRRsetPtr()));
                }

                /*
                 * No redirection anywhere. Let's try if it is a wildcard.
                 *
                 * The wildcard is checked after the empty non-terminal domain
                 * case above, because if that one triggers, it means we should
                 * not match according to 4.3.3 of RFC 1034 (the query name
                 * is known to exist).
                 */
                if (node->getFlag(domain_flag::WILD)) {
                    /* Should we cancel this match?
                     *
                     * If we compare with some node and get a common ancestor,
                     * it might mean we are comparing with a non-wildcard node.
                     * In that case, we check which part is common. If we have
                     * something in common that lives below the node we got
                     * (the one above *), then we should cancel the match
                     * according to section 4.3.3 of RFC 1034 (as the name
                     * between the wildcard domain and the query name is known
                     * to exist).
                     *
                     * Because the way the tree stores relative names, we will
                     * have exactly one common label (the ".") in case we have
                     * nothing common under the node we got and we will get
                     * more common labels otherwise (yes, this relies on the
                     * internal RBTree structure, which leaks out through this
                     * little bit).
                     *
                     * If the empty non-terminal node actually exists in the
                     * tree, then this cancellation is not needed, because we
                     * will not get here at all.
                     */
                    if (node_path.getLastComparisonResult().getRelation() ==
                        NameComparisonResult::COMMONANCESTOR && node_path.
                        getLastComparisonResult().getCommonLabels() > 1) {
                        LOG_DEBUG(logger, DBG_TRACE_DATA,
                                     DATASRC_MEM_WILDCARD_CANCEL).arg(name);
                        return (createFindResult(NXDOMAIN,
                                                 ConstRBNodeRRsetPtr(),
                                                 false));
                    }
                    const Name wildcard(Name("*").concatenate(
                        node_path.getAbsoluteName()));
                    DomainTree::Result result =
                        zone_data_->domains_.find(wildcard, &node);
                    /*
                     * Otherwise, why would the domain_flag::WILD be there if
                     * there was no wildcard under it?
                     */
                    assert(result == DomainTree::EXACTMATCH);
                    /*
                     * We have the wildcard node now. Jump below the switch,
                     * where handling of the common (exact-match) case is.
                     *
                     * However, rename it to the searched name.
                     */
                    rename = true;
                    break;
                }

                // fall through
            case DomainTree::NOTFOUND:
                LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_NOT_FOUND).
                    arg(name);
                return (createFindResult(NXDOMAIN, ConstRBNodeRRsetPtr(),
                                         false));
            case DomainTree::EXACTMATCH: // This one is OK, handle it
                break;
            default:
                assert(0);
        }
        assert(node != NULL);

        // If there is an exact match but the node is empty, it's equivalent
        // to NXRRSET.
        if (node->isEmpty()) {
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DOMAIN_EMPTY).
                arg(name);
            return (createFindResult(NXRRSET, ConstRBNodeRRsetPtr(), rename));
        }

        Domain::const_iterator found;

        // If the node callback is enabled, this may be a zone cut.  If it
        // has a NS RR, we should return a delegation, but not in the apex.
        // There is one exception: the case for DS query, which should always
        // be considered in-zone lookup.
        if (node->getFlag(DomainNode::FLAG_CALLBACK) &&
            node != zone_data_->origin_data_ && type != RRType::DS()) {
            found = node->getData()->find(RRType::NS());
            if (found != node->getData()->end()) {
                LOG_DEBUG(logger, DBG_TRACE_DATA,
                          DATASRC_MEM_EXACT_DELEGATION).arg(name);
                return (createFindResult(DELEGATION,
                                         prepareRRset(name, found->second,
                                                      rename, options)));
            }
        }

        // handle type any query
        if (target != NULL && !node->getData()->empty()) {
            // Empty domain will be handled as NXRRSET by normal processing
            for (found = node->getData()->begin();
                 found != node->getData()->end(); ++found)
            {
                target->push_back(prepareRRset(name, found->second, rename,
                                               options));
            }
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ANY_SUCCESS).
                arg(name);
            return (createFindResult(SUCCESS, ConstRBNodeRRsetPtr(), rename,
                                     node));
        }

        found = node->getData()->find(type);
        if (found != node->getData()->end()) {
            // Good, it is here
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_SUCCESS).arg(name).
                arg(type);
            return (createFindResult(SUCCESS, prepareRRset(name,
                                                           found->second,
                                                           rename, options),
                                     rename));
        } else {
            // Next, try CNAME.
            found = node->getData()->find(RRType::CNAME());
            if (found != node->getData()->end()) {
                LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_CNAME).arg(name);
                return (createFindResult(CNAME,
                                          prepareRRset(name, found->second,
                                                       rename, options),
                                          rename));
            }
        }
        // No exact match or CNAME.  Return NXRRSET.
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_NXRRSET).arg(type).
            arg(name);
        return (createFindResult(NXRRSET, ConstRBNodeRRsetPtr(), rename));
    }
};

InMemoryZoneFinder::InMemoryZoneFinder(const RRClass& zone_class, const Name& origin) :
    impl_(new InMemoryZoneFinderImpl(zone_class, origin))
{
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_CREATE).arg(origin).
        arg(zone_class);
}

InMemoryZoneFinder::~InMemoryZoneFinder() {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_DESTROY).arg(getOrigin()).
        arg(getClass());
    delete impl_;
}

Name
InMemoryZoneFinder::getOrigin() const {
    return (impl_->origin_);
}

RRClass
InMemoryZoneFinder::getClass() const {
    return (impl_->zone_class_);
}

ZoneFinderContextPtr
InMemoryZoneFinder::find(const Name& name, const RRType& type,
                         const FindOptions options)
{
    return (ZoneFinderContextPtr(
                new Context(*this, options, impl_->find(name, type, NULL,
                                                        options))));
}

ZoneFinderContextPtr
InMemoryZoneFinder::findAll(const Name& name,
                            std::vector<ConstRRsetPtr>& target,
                            const FindOptions options)
{
    return (ZoneFinderContextPtr(
                new Context(*this, options, impl_->find(name, RRType::ANY(),
                                                        &target, options))));
}

ZoneFinder::FindNSEC3Result
InMemoryZoneFinder::findNSEC3(const Name& name, bool recursive) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FINDNSEC3).arg(name).
        arg(recursive ? "recursive" : "non-recursive");

    if (!impl_->zone_data_->nsec3_data_) {
        isc_throw(DataSourceError,
                  "findNSEC3 attempt for non NSEC3 signed zone: " <<
                  impl_->origin_ << "/" << impl_->zone_class_);
    }
    const NSEC3Map& map = impl_->zone_data_->nsec3_data_->map_;
    if (map.empty()) {
        isc_throw(DataSourceError,
                  "findNSEC3 attempt but zone has no NSEC3 RR: " <<
                  impl_->origin_ << "/" << impl_->zone_class_);
    }
    const NameComparisonResult cmp_result = name.compare(impl_->origin_);
    if (cmp_result.getRelation() != NameComparisonResult::EQUAL &&
        cmp_result.getRelation() != NameComparisonResult::SUBDOMAIN) {
        isc_throw(InvalidParameter, "findNSEC3 attempt for out-of-zone name: "
                  << name << ", zone: " << impl_->origin_ << "/"
                  << impl_->zone_class_);
    }

    // Convenient shortcuts
    const NSEC3Hash& nsec3hash = *impl_->zone_data_->nsec3_data_->hash_;
    const unsigned int olabels = impl_->origin_.getLabelCount();
    const unsigned int qlabels = name.getLabelCount();

    ConstRBNodeRRsetPtr covering_proof; // placeholder of the next closer proof
    // Examine all names from the query name to the origin name, stripping
    // the deepest label one by one, until we find a name that has a matching
    // NSEC3 hash.
    for (unsigned int labels = qlabels; labels >= olabels; --labels) {
        const string hlabel = nsec3hash.calculate(
            labels == qlabels ? name : name.split(qlabels - labels, labels));
        NSEC3Map::const_iterator found = map.lower_bound(hlabel);
        LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FINDNSEC3_TRYHASH).
            arg(name).arg(labels).arg(hlabel);

        // If the given hash is larger than the largest stored hash or
        // the first label doesn't match the target, identify the "previous"
        // hash value and remember it as the candidate next closer proof.
        if (found == map.end() || found->first != hlabel) {
            // If the given hash is larger or smaller than everything,
            // the covering proof is the NSEC3 that has the largest hash.
            // Note that we know the map isn't empty, so rbegin() is
            // safe.
            if (found == map.end() || found == map.begin()) {
                covering_proof = map.rbegin()->second;
            } else {
                // Otherwise, H(found_entry-1) < given_hash < H(found_entry).
                // The covering proof is the first one (and it's valid
                // because found is neither begin nor end)
                covering_proof = (--found)->second;
            }
            if (!recursive) {   // in non recursive mode, we are done.
                LOG_DEBUG(logger, DBG_TRACE_BASIC,
                          DATASRC_MEM_FINDNSEC3_COVER).
                    arg(name).arg(*covering_proof);
                return (FindNSEC3Result(false, labels, covering_proof,
                                        ConstRRsetPtr()));
            }
        } else {                // found an exact match.
                LOG_DEBUG(logger, DBG_TRACE_BASIC,
                          DATASRC_MEM_FINDNSEC3_MATCH).arg(name).arg(labels).
                    arg(*found->second);
            return (FindNSEC3Result(true, labels, found->second,
                                    covering_proof));
        }
    }

    isc_throw(DataSourceError, "recursive findNSEC3 mode didn't stop, likely "
              "a broken NSEC3 zone: " << impl_->origin_ << "/"
              << impl_->zone_class_);
}

result::Result
InMemoryZoneFinder::add(const ConstRRsetPtr& rrset) {
    return (impl_->add(rrset, *impl_->zone_data_, NULL));
}

namespace {
// This should eventually be more generalized.
const Name
getAdditionalName(RRType rrtype, const rdata::Rdata& rdata) {
    if (rrtype == RRType::NS()) {
        const generic::NS& ns = dynamic_cast<const generic::NS&>(rdata);
        return (ns.getNSName());
    } else {
        // In our usage the only other possible case is MX.
        assert(rrtype == RRType::MX());
        const generic::MX& mx = dynamic_cast<const generic::MX&>(rdata);
        return (mx.getMXName());
    }
}

bool
checkZoneCut(const DomainNode& node, pair<bool, bool>* arg) {
    // We are only interested in the highest zone cut information.
    // Ignore others and continue the search.
    if (arg->first) {
        return (false);
    }
    // Once we encounter a delegation point due to a DNAME, anything under it
    // should be hidden.
    if (node.getData()->find(RRType::DNAME()) != node.getData()->end()) {
        return (true);
    } else if (node.getData()->find(RRType::NS()) != node.getData()->end()) {
        arg->first = true;
        arg->second = true;
        return (false);
    }
    return (false);
}

void
addAdditional(RBNodeRRset* rrset, ZoneData* zone_data) {
    RdataIteratorPtr rdata_iterator = rrset->getRdataIterator();
    for (; !rdata_iterator->isLast(); rdata_iterator->next()) {
        // For each domain name that requires additional section processing
        // in each RDATA, search the tree for the name and remember it if
        // found.  If the name is under a zone cut (for a delegation to a
        // child zone), mark the node as "GLUE", so we can selectively
        // include/exclude them when we use it.

        // TODO: wildcard
        RBTreeNodeChain<Domain> node_path;
        DomainNode* node = NULL;
        // The callback argument is a pair of bools: the first is a flag to
        // only check the highest cut; the second one records whether the
        // search goes under a zone cut.
        pair<bool, bool> callback_arg(false, false);
        const DomainTree::Result result =
            zone_data->domains_.find(
                getAdditionalName(rrset->getType(),
                                  rdata_iterator->getCurrent()),
                &node, node_path, checkZoneCut, &callback_arg);
        if (result == DomainTree::EXACTMATCH) {
            assert(node != NULL);
            if (callback_arg.second ||
                (node->getFlag(DomainNode::FLAG_CALLBACK) &&
                 node->getData()->find(RRType::NS()) !=
                 node->getData()->end())) {
                // The node is under or at a zone cut; mark it as a glue.
                node->setFlag(domain_flag::GLUE);
            }
            // Note that node may be empty.  We should keep it in the list
            // in case we dynamically update the tree and it becomes non empty
            // (which is not supported yet)
            rrset->addAdditionalNode(node);
        }
    }
}
}

void
InMemoryZoneFinder::load(const string& filename) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_LOAD).arg(getOrigin()).
        arg(filename);
    // Load it into temporary zone data.  As we build the zone, we record
    // the (RBNode)RRsets that needs to be associated with additional
    // information in 'need_additionals'.
    vector<RBNodeRRset*> need_additionals;
    scoped_ptr<ZoneData> tmp(new ZoneData(getOrigin()));

    masterLoad(filename.c_str(), getOrigin(), getClass(),
               boost::bind(&InMemoryZoneFinderImpl::addFromLoad, impl_,
                           _1, tmp.get(), &need_additionals));

    // For each RRset in need_additionals, identify the corresponding
    // RBnode for additional processing and associate it in the RRset.
    for_each(need_additionals.begin(), need_additionals.end(),
             boost::bind(addAdditional, _1, tmp.get()));

    // If the zone is NSEC3-signed, check if it has NSEC3PARAM
    if (tmp->nsec3_data_) {
        // Note: origin_data_ is set on creation of ZoneData, and the load
        // process only adds new nodes (and their data), so this assertion
        // should hold.
        assert(tmp->origin_data_ != NULL && !tmp->origin_data_->isEmpty());
        if (tmp->origin_data_->getData()->find(RRType::NSEC3PARAM()) ==
            tmp->origin_data_->getData()->end()) {
            LOG_WARN(logger, DATASRC_MEM_NO_NSEC3PARAM).
                arg(getOrigin()).arg(getClass());
        }
    }

    // If it went well, put it inside
    impl_->file_name_ = filename;
    tmp.swap(impl_->zone_data_);
    // And let the old data die with tmp
}

void
InMemoryZoneFinder::swap(InMemoryZoneFinder& zone_finder) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_SWAP).arg(getOrigin()).
        arg(zone_finder.getOrigin());
    std::swap(impl_, zone_finder.impl_);
}

const string
InMemoryZoneFinder::getFileName() const {
    return (impl_->file_name_);
}

isc::dns::Name
InMemoryZoneFinder::findPreviousName(const isc::dns::Name&) const {
    isc_throw(NotImplemented, "InMemory data source doesn't support DNSSEC "
              "yet, can't find previous name");
}

/// Implementation details for \c InMemoryClient hidden from the public
/// interface.
///
/// For now, \c InMemoryClient only contains a \c ZoneTable object, which
/// consists of (pointers to) \c InMemoryZoneFinder objects, we may add more
/// member variables later for new features.
class InMemoryClient::InMemoryClientImpl {
public:
    InMemoryClientImpl() : zone_count(0) {}
    unsigned int zone_count;
    ZoneTable zone_table;
};

InMemoryClient::InMemoryClient() : impl_(new InMemoryClientImpl)
{}

InMemoryClient::~InMemoryClient() {
    delete impl_;
}

unsigned int
InMemoryClient::getZoneCount() const {
    return (impl_->zone_count);
}

result::Result
InMemoryClient::addZone(ZoneFinderPtr zone_finder) {
    if (!zone_finder) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to InMemoryClient::addZone()");
    }

    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_ADD_ZONE).
        arg(zone_finder->getOrigin()).arg(zone_finder->getClass().toText());

    const result::Result result = impl_->zone_table.addZone(zone_finder);
    if (result == result::SUCCESS) {
        ++impl_->zone_count;
    }
    return (result);
}

InMemoryClient::FindResult
InMemoryClient::findZone(const isc::dns::Name& name) const {
    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_FIND_ZONE).arg(name);
    ZoneTable::FindResult result(impl_->zone_table.findZone(name));
    return (FindResult(result.code, result.zone));
}

namespace {

class MemoryIterator : public ZoneIterator {
private:
    RBTreeNodeChain<Domain> chain_;
    Domain::const_iterator dom_iterator_;
    const DomainTree& tree_;
    const DomainNode* node_;
    // Only used when separate_rrs_ is true
    RdataIteratorPtr rdata_iterator_;
    bool separate_rrs_;
    bool ready_;
public:
    MemoryIterator(const DomainTree& tree, const Name& origin, bool separate_rrs) :
        tree_(tree),
        separate_rrs_(separate_rrs),
        ready_(true)
    {
        // Find the first node (origin) and preserve the node chain for future
        // searches
        DomainTree::Result result(tree_.find<void*>(origin, &node_, chain_,
                                                    NULL, NULL));
        // It can't happen that the origin is not in there
        if (result != DomainTree::EXACTMATCH) {
            isc_throw(Unexpected,
                      "In-memory zone corrupted, missing origin node");
        }
        // Initialize the iterator if there's somewhere to point to
        if (node_ != NULL && node_->getData() != DomainPtr()) {
            dom_iterator_ = node_->getData()->begin();
            if (separate_rrs_ && dom_iterator_ != node_->getData()->end()) {
                rdata_iterator_ = dom_iterator_->second->getRdataIterator();
            }
        }
    }

    virtual ConstRRsetPtr getNextRRset() {
        if (!ready_) {
            isc_throw(Unexpected, "Iterating past the zone end");
        }
        /*
         * This cycle finds the first nonempty node with yet unused RRset.
         * If it is NULL, we run out of nodes. If it is empty, it doesn't
         * contain any RRsets. If we are at the end, just get to next one.
         */
        while (node_ != NULL && (node_->getData() == DomainPtr() ||
                                 dom_iterator_ == node_->getData()->end())) {
            node_ = tree_.nextNode(chain_);
            // If there's a node, initialize the iterator and check next time
            // if the map is empty or not
            if (node_ != NULL && node_->getData() != NULL) {
                dom_iterator_ = node_->getData()->begin();
                // New RRset, so get a new rdata iterator
                if (separate_rrs_) {
                    rdata_iterator_ = dom_iterator_->second->getRdataIterator();
                }
            }
        }
        if (node_ == NULL) {
            // That's all, folks
            ready_ = false;
            return (ConstRRsetPtr());
        }

        if (separate_rrs_) {
            // For separate rrs, reconstruct a new RRset with just the
            // 'current' rdata
            RRsetPtr result(new RRset(dom_iterator_->second->getName(),
                                      dom_iterator_->second->getClass(),
                                      dom_iterator_->second->getType(),
                                      dom_iterator_->second->getTTL()));
            result->addRdata(rdata_iterator_->getCurrent());
            rdata_iterator_->next();
            if (rdata_iterator_->isLast()) {
                // all used up, next.
                ++dom_iterator_;
                // New RRset, so get a new rdata iterator, but only if this
                // was not the final RRset in the chain
                if (dom_iterator_ != node_->getData()->end()) {
                    rdata_iterator_ = dom_iterator_->second->getRdataIterator();
                }
            }
            return (result);
        } else {
            // The iterator points to the next yet unused RRset now
            ConstRRsetPtr result(dom_iterator_->second);

            // This one is used, move it to the next time for next call
            ++dom_iterator_;

            return (result);
        }
    }

    virtual ConstRRsetPtr getSOA() const {
        isc_throw(NotImplemented, "Not imelemented");
    }
};

} // End of anonymous namespace

ZoneIteratorPtr
InMemoryClient::getIterator(const Name& name, bool separate_rrs) const {
    ZoneTable::FindResult result(impl_->zone_table.findZone(name));
    if (result.code != result::SUCCESS) {
        isc_throw(DataSourceError, "No such zone: " + name.toText());
    }

    const InMemoryZoneFinder*
        zone(dynamic_cast<const InMemoryZoneFinder*>(result.zone.get()));
    if (zone == NULL) {
        /*
         * TODO: This can happen only during some of the tests and only as
         * a temporary solution. This should be fixed by #1159 and then
         * this cast and check shouldn't be necessary. We don't have
         * test for handling a "can not happen" condition.
         */
        isc_throw(Unexpected, "The zone at " + name.toText() +
                  " is not InMemoryZoneFinder");
    }
    return (ZoneIteratorPtr(new MemoryIterator(
                                zone->impl_->zone_data_->domains_, name,
                                separate_rrs)));
}

ZoneUpdaterPtr
InMemoryClient::getUpdater(const isc::dns::Name&, bool, bool) const {
    isc_throw(isc::NotImplemented, "Update attempt on in memory data source");
}

pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
InMemoryClient::getJournalReader(const isc::dns::Name&, uint32_t,
                                 uint32_t) const
{
    isc_throw(isc::NotImplemented, "Journaling isn't supported for "
              "in memory data source");
}

} // end of namespace datasrc
} // end of namespace isc
