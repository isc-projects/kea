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

#include <datasrc/memory/zone_finder.h>
#include <datasrc/memory/domaintree.h>
#include <datasrc/memory/treenode_rrset.h>

#include <datasrc/zone.h>
#include <datasrc/data_source.h>
#include <dns/labelsequence.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

#include <datasrc/logger.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::datasrc;

namespace isc {
namespace datasrc {
namespace memory {

namespace {
// (temporary?) convenience function to create a treenoderrset
// given an rdataset; we should probably have some pool so these
// do not need to be allocated dynamically
// For now they are still dynamically allocated, and have a fixed rrclass (...)
TreeNodeRRsetPtr
createTreeNodeRRset(const ZoneNode* node,
                    const RdataSet* rdataset,
                    const RRClass& rrclass)
{
    if (rdataset != NULL) {
        return TreeNodeRRsetPtr(new TreeNodeRRset(rrclass, node,
                                                  rdataset, true));
    } else {
        return TreeNodeRRsetPtr();
    }
}

struct FindState {
    FindState(bool glue_ok) :
        zonecut_node_(NULL),
        dname_node_(NULL),
        rrset_(NULL),
        glue_ok_(glue_ok)
    {}

    // These will be set to a domain node of the highest delegation point,
    // if any.  In fact, we could use a single variable instead of both.
    // But then we would need to distinquish these two cases by something
    // else and it seemed little more confusing when this was written.
    const ZoneNode* zonecut_node_;
    const ZoneNode* dname_node_;

    // Delegation RRset (NS or DNAME), if found.
    //TreeNodeRRsetPtr rrset_;
    const RdataSet* rrset_;

    // Whether to continue search below a delegation point.
    // Set at construction time.
    const bool glue_ok_;
};

// A callback called from possible zone cut nodes and nodes with DNAME.
// This will be passed from findNode() to \c RBTree::find().
bool cutCallback(const ZoneNode& node, FindState* state) {
    // We need to look for DNAME first, there's allowed case where
    // DNAME and NS coexist in the apex. DNAME is the one to notice,
    // the NS is authoritative, not delegation (corner case explicitly
    // allowed by section 3 of 2672)
    const RdataSet* found_dname = RdataSet::find(node.getData(), RRType::DNAME());

    if (found_dname != NULL) {
        LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_MEM_DNAME_ENCOUNTERED);
        state->dname_node_ = &node;
        state->rrset_ = found_dname;
        return (true);
    }

    // Look for NS
    const RdataSet* found_ns = RdataSet::find(node.getData(), RRType::NS());
    if (found_ns != NULL) {
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
        state->rrset_ = found_ns;

        // Unless glue is allowed the search stops here, so we return
        // false; otherwise return true to continue the search.
        return (!state->glue_ok_);
    }

    // This case should not happen because we enable callback only
    // when we add an RR searched for above.
    assert(0);
    // This is here to avoid warning (therefore compilation error)
    // in case assert is turned off. Otherwise we could get "Control
    // reached end of non-void function".
    return (false);
}

// convenience function to fill in the final details
isc::datasrc::memory::ZoneFinderResultContext
createFindResult(const RRClass& rrclass,
                 const ZoneData& zone_data,
                 ZoneFinder::Result code,
                 const RdataSet* rrset,
                 const ZoneNode* node,
                 bool wild = false) {
    ZoneFinder::FindResultFlags flags = ZoneFinder::RESULT_DEFAULT;

    if (wild) {
        flags = flags | ZoneFinder::RESULT_WILDCARD;
    }
    if (code == ZoneFinder::NXRRSET || code == ZoneFinder::NXDOMAIN || wild) {
        if (zone_data.isNSEC3Signed()) {
            flags = flags | ZoneFinder::RESULT_NSEC3_SIGNED;
        } else if (zone_data.isSigned()) {
            flags = flags | ZoneFinder::RESULT_NSEC_SIGNED;
        }
    }

    return (ZoneFinderResultContext(code, createTreeNodeRRset(node, rrset, rrclass), flags, node));
}

const RdataSet*
getClosestNSEC(const ZoneData& zone_data,
               ZoneNodeChain& chain,
               const ZoneNode** nsec_node,
               ZoneFinder::FindOptions options)
{
    if (!zone_data.isSigned() || (options & ZoneFinder::FIND_DNSSEC) == 0 || zone_data.isNSEC3Signed()) {
        return (NULL);
    }

    const ZoneNode* prev_node;
    while ((prev_node = zone_data.getZoneTree().previousNode(chain)) != NULL) {
        if (!prev_node->isEmpty()) {
            const RdataSet* found = RdataSet::find(prev_node->getData(), RRType::NSEC());
            if (found != NULL) {
                *nsec_node = prev_node;
                return (found);
            }
        }
    }
    // This must be impossible and should be an internal bug.
    // See the description at the method declaration.
    assert(false);
    // Even though there is an assert here, strict compilers
    // will still need some return value.
    return (NULL);
}

// A helper function for the NXRRSET case in find().  If the zone is
// NSEC-signed and DNSSEC records are requested, try to find NSEC
// on the given node, and return it if found; return NULL for all other
// cases.
const RdataSet*
getNSECForNXRRSET(const ZoneData& zone_data,
                  ZoneFinder::FindOptions options,
                  const ZoneNode* node)
{
    if (zone_data.isSigned() &&
        !zone_data.isNSEC3Signed() &&
        (options & ZoneFinder::FIND_DNSSEC) != 0) {
        const RdataSet* found = RdataSet::find(node->getData(), RRType::NSEC());
        if (found != NULL) {
            return (found);
        }
    }
    return (NULL);
}


class FindNodeResult {
public:
    // Bitwise flags to represent supplemental information of the
    // search result:
    // Search resulted in a wildcard match.
    static const unsigned int FIND_WILDCARD = 1;
    // Search encountered a zone cut due to NS but continued to look for
    // a glue.
    static const unsigned int FIND_ZONECUT = 2;

    FindNodeResult(ZoneFinder::Result code_param,
                   const ZoneNode* node_param,
                   const RdataSet* rrset_param,
                   unsigned int flags_param = 0) :
        code(code_param),
        node(node_param),
        rrset(rrset_param),
        flags(flags_param)
    {}
    const ZoneFinder::Result code;
    const ZoneNode* node;
    const RdataSet* rrset;
    const unsigned int flags;
};

FindNodeResult findNode(const ZoneData& zone_data,
                        const Name& name,
                        ZoneNodeChain& chain,
                        ZoneFinder::FindOptions options)
{
    ZoneNode* node = NULL;
    FindState state((options & ZoneFinder::FIND_GLUE_OK) != 0);

    const ZoneTree& tree(zone_data.getZoneTree());
    ZoneTree::Result result = tree.find(isc::dns::LabelSequence(name),
                                        &node, chain, cutCallback, &state);
    const unsigned int zonecut_flag =
        (state.zonecut_node_ != NULL) ? FindNodeResult::FIND_ZONECUT : 0;
    if (result == ZoneTree::EXACTMATCH) {
        return (FindNodeResult(ZoneFinder::SUCCESS, node, state.rrset_,
                               zonecut_flag));
    } else if (result == ZoneTree::PARTIALMATCH) {
        assert(node != NULL);
        if (state.dname_node_ != NULL) { // DNAME
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DNAME_FOUND).
                arg(state.dname_node_->getName());
            return (FindNodeResult(ZoneFinder::DNAME, state.dname_node_, state.rrset_));
        }
        if (state.zonecut_node_ != NULL) { // DELEGATION due to NS
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DELEG_FOUND).
                arg(state.zonecut_node_->getName());
            return (FindNodeResult(ZoneFinder::DELEGATION, state.zonecut_node_, state.rrset_));
        }
        if (chain.getLastComparisonResult().getRelation() ==
            NameComparisonResult::SUPERDOMAIN) { // empty node, so NXRRSET
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_SUPER_STOP).arg(name);
            const ZoneNode* nsec_node;
            const RdataSet* nsec_rds = getClosestNSEC(zone_data, chain, &nsec_node, options);
            return (FindNodeResult(ZoneFinder::NXRRSET, nsec_node, nsec_rds));
        }
        // TODO: wildcard (see memory_datasrc.cc:480)
        // Nothing really matched.
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_NOT_FOUND).arg(name);
        const ZoneNode* nsec_node;
        const RdataSet* nsec_rds = getClosestNSEC(zone_data, chain, &nsec_node, options);
        return (FindNodeResult(ZoneFinder::NXDOMAIN, nsec_node, nsec_rds));
    } else {
        // If the name is neither an exact or partial match, it is
        // out of bailiwick, which is considered an error.
        isc_throw(OutOfZone, name.toText() << " not in " <<
                             zone_data.getOriginNode()->getName());
    }
}

} // end anonymous namespace

class InMemoryZoneFinder::Context : public ZoneFinder::Context {
public:
    /// \brief Constructor.
    ///
    /// Note that we don't have a specific constructor for the findAll() case.
    /// For (successful) type ANY query, found_node points to the
    /// corresponding RB node, which is recorded within this specialized
    /// context.
    Context(ZoneFinder& finder, ZoneFinder::FindOptions options,
            ZoneFinderResultContext result) :
        ZoneFinder::Context(finder, options,
                            ResultContext(result.code, result.rrset,
                                          result.flags)),
        rrset_(result.rrset), found_node_(result.found_node)
    {}

private:
    const TreeNodeRRsetPtr rrset_;
    const ZoneNode* const found_node_;
};

boost::shared_ptr<ZoneFinder::Context>
InMemoryZoneFinder::find(const isc::dns::Name& name,
                const isc::dns::RRType& type,
                const FindOptions options)
{
    // call find_internal, and wrap the result in a ContextPtr
    return ZoneFinderContextPtr(new Context(*this, options,
                                            find_internal(name,
                                                          type,
                                                          NULL,
                                                          options)));
}

boost::shared_ptr<ZoneFinder::Context>
InMemoryZoneFinder::findAll(const isc::dns::Name& name,
        std::vector<isc::dns::ConstRRsetPtr>& target,
        const FindOptions options)
{
    // call find_internal, and wrap the result in a ContextPtr
    return ZoneFinderContextPtr(new Context(*this, options,
                                            find_internal(name,
                                                          RRType::ANY(),
                                                          &target,
                                                          options)));
}

ZoneFinderResultContext
InMemoryZoneFinder::find_internal(const isc::dns::Name& name,
                                  const isc::dns::RRType& type,
                                  std::vector<ConstRRsetPtr>* target,
                                  const FindOptions options)
{
    // Get the node.  All other cases than an exact match are handled
    // in findNode().  We simply construct a result structure and return.
    ZoneNodeChain chain;
    const FindNodeResult node_result =
        findNode(zone_data_, name, chain, options);
    if (node_result.code != SUCCESS) {
        return (createFindResult(rrclass_, zone_data_, node_result.code, node_result.rrset, node_result.node));
    }

    const ZoneNode* node = node_result.node;
    assert(node != NULL);

    // We've found an exact match, may or may not be a result of wildcard.
    // TODO, ticket #2110
    // If there is an exact match but the node is empty, it's equivalent
    // to NXRRSET.
    if (node->isEmpty()) {
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DOMAIN_EMPTY).
            arg(name);
        const ZoneNode* nsec_node;
        const RdataSet* nsec_rds = getClosestNSEC(zone_data_, chain, &nsec_node, options);
        return (createFindResult(rrclass_, zone_data_, NXRRSET,
                                 nsec_rds,
                                 nsec_node));
    }

    const RdataSet* found;

    // If the node callback is enabled, this may be a zone cut.  If it
    // has a NS RR, we should return a delegation, but not in the apex.
    // There is one exception: the case for DS query, which should always
    // be considered in-zone lookup.
    if (node->getFlag(ZoneNode::FLAG_CALLBACK) &&
            node != zone_data_.getOriginNode() && type != RRType::DS()) {
        found = RdataSet::find(node->getData(), RRType::NS());
        if (found != NULL) {
            LOG_DEBUG(logger, DBG_TRACE_DATA,
                      DATASRC_MEM_EXACT_DELEGATION).arg(name);
            // TODO: rename argument (wildcards, see #2110)
            return (createFindResult(rrclass_, zone_data_, DELEGATION, found, node));
        }
    }

    // Handle type any query
    if (target != NULL && node->getData() != NULL) {
        // Empty domain will be handled as NXRRSET by normal processing
        const RdataSet* cur_rds = node->getData();
        while (cur_rds != NULL) {
            target->push_back(createTreeNodeRRset(node, cur_rds, rrclass_));
            cur_rds = cur_rds->getNext();
        }
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ANY_SUCCESS).
            arg(name);
        return (createFindResult(rrclass_, zone_data_, SUCCESS, NULL, node));
    }

    const RdataSet* currds = node->getData();
    while (currds != NULL) {
        currds = currds->getNext();
    }
    found = RdataSet::find(node->getData(), type);
    if (found != NULL) {
        // Good, it is here
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_SUCCESS).arg(name).
            arg(type);
        return (createFindResult(rrclass_, zone_data_, SUCCESS, found, node));
    } else {
        // Next, try CNAME.
        found = RdataSet::find(node->getData(), RRType::CNAME());
        if (found != NULL) {
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_CNAME).arg(name);
            return (createFindResult(rrclass_, zone_data_, CNAME, found, node));
        }
    }
    // No exact match or CNAME.  Get NSEC if necessary and return NXRRSET.
    return (createFindResult(rrclass_, zone_data_, NXRRSET, getNSECForNXRRSET(zone_data_, options, node), node));
}

isc::datasrc::ZoneFinder::FindNSEC3Result
InMemoryZoneFinder::findNSEC3(const isc::dns::Name& name, bool recursive) {
    (void)name;
    (void)recursive;
    isc_throw(isc::NotImplemented, "not completed yet! please implement me");
}

} // namespace memory
} // namespace datasrc
} // namespace isc
