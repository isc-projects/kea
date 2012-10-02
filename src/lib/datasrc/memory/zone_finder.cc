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
#include <datasrc/memory/rdata_serialization.h>

#include <datasrc/zone.h>
#include <datasrc/data_source.h>
#include <dns/labelsequence.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/nsec3hash.h>

#include <datasrc/logger.h>

#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>

#include <algorithm>
#include <vector>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::datasrc;

namespace isc {
namespace datasrc {
namespace memory {

namespace internal {

// Specialized version of ZoneFinder::ResultContext, which  holds objects
// related to find() results using internal representations of the in-memory
// data source implementation.
class ZoneFinderResultContext {
public:
    /// \brief Constructor
    ///
    /// The first three parameters correspond to those of
    /// ZoneFinder::ResultContext.  If node is non NULL, it specifies the
    /// found ZoneNode in the search.
    ZoneFinderResultContext(ZoneFinder::Result code_param,
                            TreeNodeRRsetPtr rrset_param,
                            ZoneFinder::FindResultFlags flags_param,
                            const ZoneData& zone_data_param,
                            const ZoneNode* node, const RdataSet* rdset) :
        code(code_param), rrset(rrset_param), flags(flags_param),
        zone_data(&zone_data_param), found_node(node), found_rdset(rdset)
    {}

    const ZoneFinder::Result code;
    const TreeNodeRRsetPtr rrset;
    const ZoneFinder::FindResultFlags flags;
    const ZoneData* const zone_data;
    const ZoneNode* const found_node;
    const RdataSet* const found_rdset;
};
}
using internal::ZoneFinderResultContext;

namespace {
/// Creates a TreeNodeRRsetPtr for the given RdataSet at the given Node, for
/// the given RRClass
///
/// We should probably have some pool so these  do not need to be allocated
/// dynamically.
///
/// \param node The ZoneNode found by the find() calls
/// \param rdataset The RdataSet to create the RRsetPtr for
/// \param rrclass The RRClass as passed by the client
/// \param realname If given, the TreeNodeRRset is created with this name
///                 (e.g. for wildcard substitution)
///
/// Returns an empty TreeNodeRRsetPtr if node is NULL or if rdataset is NULL.
TreeNodeRRsetPtr
createTreeNodeRRset(const ZoneNode* node,
                    const RdataSet* rdataset,
                    const RRClass& rrclass,
                    ZoneFinder::FindOptions options,
                    const Name* realname = NULL)
{
    const bool dnssec = ((options & ZoneFinder::FIND_DNSSEC) != 0);
    if (node != NULL && rdataset != NULL) {
        if (realname != NULL) {
            return (TreeNodeRRsetPtr(new TreeNodeRRset(*realname, rrclass,
                                                       node, rdataset,
                                                       dnssec)));
        } else {
            return (TreeNodeRRsetPtr(new TreeNodeRRset(rrclass, node, rdataset,
                                                       dnssec)));
        }
    } else {
        return (TreeNodeRRsetPtr());
    }
}

/// Maintain intermediate data specific to the search context used in
/// \c find().
///
/// It will be passed to \c cutCallback() (see below) and record a possible
/// zone cut node and related RRset (normally NS or DNAME).
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
    const RdataSet* rrset_;

    // Whether to continue search below a delegation point.
    // Set at construction time.
    const bool glue_ok_;
};

// A callback called from possible zone cut nodes and nodes with DNAME.
// This will be passed from findNode() to \c ZoneTree::find().
bool cutCallback(const ZoneNode& node, FindState* state) {
    // We need to look for DNAME first, there's allowed case where
    // DNAME and NS coexist in the apex. DNAME is the one to notice,
    // the NS is authoritative, not delegation (corner case explicitly
    // allowed by section 3 of 2672)
    const RdataSet* found_dname = RdataSet::find(node.getData(),
                                                 RRType::DNAME());

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

/// Creates a NSEC3 ConstRRsetPtr for the given ZoneNode inside the
/// NSEC3 tree, for the given RRClass.
///
/// It asserts that the node contains data (RdataSet) and is of type
/// NSEC3.
///
/// \param node The ZoneNode inside the NSEC3 tree
/// \param rrclass The RRClass as passed by the client
ConstRRsetPtr
createNSEC3RRset(const ZoneNode* node, const RRClass& rrclass) {
     const RdataSet* rdataset = node->getData();
     // Only NSEC3 ZoneNodes are allowed to be passed to this method. We
     // assert that these have data, and also are of type NSEC3.
     assert(rdataset != NULL);
     assert(rdataset->type == RRType::NSEC3());

    // Create the RRset.  Note the DNSSEC flag: NSEC3 implies DNSSEC.
    return (createTreeNodeRRset(node, rdataset, rrclass,
                                ZoneFinder::FIND_DNSSEC));
}

// convenience function to fill in the final details
//
// Set up ZoneFinderResultContext object as a return value of find(),
// taking into account wildcard matches and DNSSEC information.  We set
// the NSEC/NSEC3 flag when applicable regardless of the find option; the
// caller would simply ignore these when they didn't request DNSSEC
// related results.
//
// Also performs the conversion of node + RdataSet into a TreeNodeRRsetPtr
//
// if wild is true, the RESULT_WILDCARD flag will be set.
// If qname is not NULL, this is the query name, to be used in wildcard
// substitution instead of the Node's name).
ZoneFinderResultContext
createFindResult(const RRClass& rrclass,
                 const ZoneData& zone_data,
                 ZoneFinder::Result code,
                 const RdataSet* rdset,
                 const ZoneNode* node,
                 ZoneFinder::FindOptions options,
                 bool wild = false,
                 const Name* qname = NULL)
{
    ZoneFinder::FindResultFlags flags = ZoneFinder::RESULT_DEFAULT;
    const Name* rename = NULL;

    if (wild) {
        flags = flags | ZoneFinder::RESULT_WILDCARD;
        // only use the rename qname if wild is true
        rename = qname;
    }
    if (code == ZoneFinder::NXRRSET || code == ZoneFinder::NXDOMAIN || wild) {
        if (zone_data.isNSEC3Signed()) {
            flags = flags | ZoneFinder::RESULT_NSEC3_SIGNED;
        } else if (zone_data.isSigned()) {
            flags = flags | ZoneFinder::RESULT_NSEC_SIGNED;
        }
    }

    return (ZoneFinderResultContext(code, createTreeNodeRRset(node, rdset,
                                                              rrclass, options,
                                                              rename),
                                    flags, zone_data, node, rdset));
}

// A helper function for NSEC-signed zones.  It searches the zone for
// the "closest" NSEC corresponding to the search context stored in
// node_path (it should contain sufficient information to identify the
// previous name of the query name in the zone).  In some cases the
// immediate closest name may not have NSEC (when it's under a zone cut
// for glue records, or even when the zone is partly broken), so this
// method continues the search until it finds a name that has NSEC,
// and returns the one found first.  Due to the prerequisite (see below),
// it should always succeed.
//
// node_path must store valid search context (in practice, it's expected
// to be set by findNode()); otherwise the underlying ZoneTree implementation
// throws.
//
// If the zone is not considered NSEC-signed or DNSSEC records were not
// required in the original search context (specified in options), this
// method doesn't bother to find NSEC, and simply returns NULL.  So, by
// definition of "NSEC-signed", when it really tries to find an NSEC it
// should succeed; there should be one at least at the zone origin.
const RdataSet*
getClosestNSEC(const ZoneData& zone_data,
               ZoneChain& node_path,
               const ZoneNode** nsec_node,
               ZoneFinder::FindOptions options)
{
    if (!zone_data.isSigned() ||
        (options & ZoneFinder::FIND_DNSSEC) == 0 ||
        zone_data.isNSEC3Signed()) {
        return (NULL);
    }

    const ZoneNode* prev_node;
    while ((prev_node = zone_data.getZoneTree().previousNode(node_path))
           != NULL) {
        if (!prev_node->isEmpty()) {
            const RdataSet* found =
                RdataSet::find(prev_node->getData(), RRType::NSEC());
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
        const RdataSet* found = RdataSet::find(node->getData(),
                                               RRType::NSEC());
        if (found != NULL) {
            return (found);
        }
    }
    return (NULL);
}

// Structure to hold result data of the findNode() call
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

// Implementation notes: this method identifies an ZoneNode that best matches
// the give name in terms of DNS query handling.  In many cases,
// DomainTree::find() will result in EXACTMATCH or PARTIALMATCH (note that
// the given name is generally expected to be contained in the zone, so
// even if it doesn't exist, it should at least match the zone origin).
// If it finds an exact match, that's obviously the best one.  The partial
// match case is more complicated.
//
// We first need to consider the case where search hits a delegation point,
// either due to NS or DNAME.  They are indicated as either dname_node_ or
// zonecut_node_ being non NULL.  Usually at most one of them will be
// something else than NULL (it might happen both are NULL, in which case we
// consider it NOT FOUND). There's one corner case when both might be
// something else than NULL and it is in case there's a DNAME under a zone
// cut and we search in glue OK mode ‒ in that case we don't stop on the
// domain with NS and ignore it for the answer, but it gets set anyway. Then
// we find the DNAME and we need to act by it, therefore we first check for
// DNAME and then for NS. In all other cases it doesn't matter, as at least
// one of them is NULL.
//
// Next, we need to check if the ZoneTree search stopped at a node for a
// subdomain of the search name (so the comparison result that stopped the
// search is "SUPERDOMAIN"), it means the stopping node is an empty
// non-terminal node.  In this case the search name is considered to exist
// but no data should be found there.
//
// If none of above is the case, we then consider whether there's a matching
// wildcard.  DomainTree::find() records the node if it encounters a
// "wildcarding" node, i.e., the immediate ancestor of a wildcard name
// (e.g., wild.example.com for *.wild.example.com), and returns it if it
// doesn't find any node that better matches the query name.  In this case
// we'll check if there's indeed a wildcard below the wildcarding node.
//
// Note, first, that the wildcard is checked after the empty
// non-terminal domain case above, because if that one triggers, it
// means we should not match according to 4.3.3 of RFC 1034 (the query
// name is known to exist).
//
// Before we try to find a wildcard, we should check whether there's
// an existing node that would cancel the wildcard match.  If
// DomainTree::find() stopped at a node which has a common ancestor
// with the query name, it might mean we are comparing with a
// non-wildcard node. In that case, we check which part is common. If
// we have something in common that lives below the node we got (the
// one above *), then we should cancel the match according to section
// 4.3.3 of RFC 1034 (as the name between the wildcard domain and the
// query name is known to exist).
//
// If there's no node below the wildcarding node that shares a common ancestor
// of the query name, we can conclude the wildcard is the best match.
// We'll then identify the wildcard node via an incremental search.  Note that
// there's no possibility that the query name is at an empty non terminal
// node below the wildcarding node at this stage; that case should have been
// caught above.
//
// If none of the above succeeds, we conclude the name doesn't exist in
// the zone, and throw an OutOfZone exception by default.  If the optional
// out_of_zone_ok is true, it returns an NXDOMAIN result with NULL data so
// the caller can take an action to it (technically it's not "NXDOMAIN",
// but the caller is assumed not to rely on the difference.)
FindNodeResult findNode(const ZoneData& zone_data,
                        const LabelSequence& name_labels,
                        ZoneChain& node_path,
                        ZoneFinder::FindOptions options,
                        bool out_of_zone_ok = false)
{
    ZoneNode* node = NULL;
    FindState state((options & ZoneFinder::FIND_GLUE_OK) != 0);

    const ZoneTree& tree(zone_data.getZoneTree());
    const ZoneTree::Result result = tree.find(name_labels, &node, node_path,
                                              cutCallback, &state);
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
            return (FindNodeResult(ZoneFinder::DNAME, state.dname_node_,
                                   state.rrset_));
        }
        if (state.zonecut_node_ != NULL) { // DELEGATION due to NS
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DELEG_FOUND).
                arg(state.zonecut_node_->getName());
            return (FindNodeResult(ZoneFinder::DELEGATION,
                                   state.zonecut_node_,
                                   state.rrset_));
        }
        if (node_path.getLastComparisonResult().getRelation() ==
            NameComparisonResult::SUPERDOMAIN) { // empty node, so NXRRSET
            LOG_DEBUG(logger, DBG_TRACE_DATA,
                      DATASRC_MEM_SUPER_STOP).arg(name_labels);
            const ZoneNode* nsec_node;
            const RdataSet* nsec_rds = getClosestNSEC(zone_data,
                                                      node_path,
                                                      &nsec_node,
                                                      options);
            return (FindNodeResult(ZoneFinder::NXRRSET, nsec_node,
                                   nsec_rds));
        }
        // Nothing really matched.

        // May be a wildcard, but check only if not disabled
        if (node->getFlag(ZoneData::WILDCARD_NODE) &&
            (options & ZoneFinder::NO_WILDCARD) == 0) {
            if (node_path.getLastComparisonResult().getRelation() ==
                NameComparisonResult::COMMONANCESTOR) {
                // This means, e.g., we have *.wild.example and
                // bar.foo.wild.example and are looking for
                // baz.foo.wild.example. The common ancestor, foo.wild.example,
                // should cancel wildcard.  Treat it as NXDOMAIN.
                LOG_DEBUG(logger, DBG_TRACE_DATA,
                          DATASRC_MEM_WILDCARD_CANCEL).arg(name_labels);
                    const ZoneNode* nsec_node;
                    const RdataSet* nsec_rds = getClosestNSEC(zone_data,
                                                              node_path,
                                                              &nsec_node,
                                                              options);
                    return (FindNodeResult(ZoneFinder::NXDOMAIN, nsec_node,
                                           nsec_rds));
            }
            uint8_t ls_buf[LabelSequence::MAX_SERIALIZED_LENGTH];

            // Create the wildcard name (i.e. take "*" and extend it
            // with all node labels down to the wildcard node
            LabelSequence wildcard_ls(LabelSequence::WILDCARD(), ls_buf);
            const ZoneNode* extend_with = node;
            while (extend_with != NULL) {
                wildcard_ls.extend(extend_with->getLabels(), ls_buf);
                extend_with = extend_with->getUpperNode();
            }

            // Clear the node_path so that we don't keep incorrect (NSEC)
            // context
            node_path.clear();
            ZoneTree::Result result = tree.find(wildcard_ls, &node, node_path,
                                                cutCallback, &state);
            // Otherwise, why would the domain_flag::WILD be there if
            // there was no wildcard under it?
            assert(result == ZoneTree::EXACTMATCH);
            return (FindNodeResult(ZoneFinder::SUCCESS, node, state.rrset_,
                        FindNodeResult::FIND_WILDCARD | zonecut_flag));
        }

        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_NOT_FOUND).
            arg(name_labels);
        const ZoneNode* nsec_node;
        const RdataSet* nsec_rds = getClosestNSEC(zone_data, node_path,
                                                  &nsec_node, options);
        return (FindNodeResult(ZoneFinder::NXDOMAIN, nsec_node, nsec_rds));
    } else {
        // If the name is neither an exact or partial match, it is
        // out of bailiwick, which is considered an error, unless the caller
        // is willing to accept it.
        if (out_of_zone_ok) {
            return (FindNodeResult(ZoneFinder::NXDOMAIN, NULL, NULL));
        }
        isc_throw(OutOfZone, name_labels << " not in " <<
                             zone_data.getOriginNode()->getName());
    }
}

} // end anonymous namespace


/// \brief Specialization of the ZoneFinder::Context for the in-memory finder.
///
/// Note that we don't have a specific constructor for the findAll() case.
/// For (successful) type ANY query, found_node points to the
/// corresponding zone node, which is recorded within this specialized
/// context.
class InMemoryZoneFinder::Context : public ZoneFinder::Context {
public:
    Context(InMemoryZoneFinder& finder, ZoneFinder::FindOptions options,
            const RRClass& rrclass, const ZoneFinderResultContext& result) :
        ZoneFinder::Context(options, ResultContext(result.code, result.rrset,
                                                   result.flags)),
        finder_(finder),        // NOTE: when #2284 is done we won't need this
        rrclass_(rrclass), zone_data_(result.zone_data),
        found_node_(result.found_node),
        found_rdset_(result.found_rdset)
    {}

protected:
    // When #2284 is done this can simply return NULL.
    virtual ZoneFinder* getFinder() { return (&finder_); }

    // We don't use the default protected methods that rely on this method,
    // so we can simply return NULL.
    virtual const std::vector<isc::dns::ConstRRsetPtr>* getAllRRsets() const {
        return (NULL);
    }

    virtual void getAdditionalImpl(const std::vector<RRType>& requested_types,
                                   std::vector<ConstRRsetPtr>& result)
    {
        if (found_rdset_ != NULL) {
            // Normal query with successful result.
            getAdditionalForRdataset(found_rdset_, requested_types, result,
                                     options_);
        } else if (found_node_ != NULL) {
            // Successful type ANY query result.  Call
            // getAdditionalForRdataset for each RdataSet of the node.
            for (const RdataSet* rdset = found_node_->getData();
                 rdset != NULL;
                 rdset = rdset->getNext())
            {
                getAdditionalForRdataset(rdset, requested_types, result,
                                         options_);
            }
        }
    }

private:
    // Main subroutine of getAdditionalImpl, iterate over Rdata fields
    // find, create, and insert necessary additional RRsets.
    void
    getAdditionalForRdataset(const RdataSet* rdset,
                             const std::vector<RRType>& requested_types,
                             std::vector<ConstRRsetPtr>& result,
                             ZoneFinder::FindOptions orig_options) const
    {
        ZoneFinder::FindOptions options = ZoneFinder::FIND_DEFAULT;
        if ((orig_options & ZoneFinder::FIND_DNSSEC) != 0) {
            options = options | ZoneFinder::FIND_DNSSEC;
        }
        if (rdset->type == RRType::NS()) {
            options = options | ZoneFinder::FIND_GLUE_OK;
        }

        RdataReader(rrclass_, rdset->type, rdset->getDataBuf(),
                    rdset->getRdataCount(), rdset->getSigRdataCount(),
                    boost::bind(&Context::findAdditional, this,
                                &requested_types, &result, options, _1, _2),
                    &RdataReader::emptyDataAction).iterate();
    }

    // RdataReader callback for additional section processing.
    void
    findAdditional(const std::vector<RRType>* requested_types,
                   std::vector<ConstRRsetPtr>* result,
                   ZoneFinder::FindOptions options,
                   const LabelSequence& name_labels,
                   RdataNameAttributes attr) const;

    // Subroutine for findAdditional() to unify the normal and wildcard match
    // cases.
    void
    findAdditionalHelper(const std::vector<RRType>* requested_types,
                         std::vector<ConstRRsetPtr>* result,
                         const ZoneNode* node,
                         ZoneFinder::FindOptions options,
                         const Name* real_name) const
    {
        const std::vector<RRType>::const_iterator type_beg =
            requested_types->begin();
        const std::vector<RRType>::const_iterator type_end =
            requested_types->end();
        for (const RdataSet* rdset = node->getData();
             rdset != NULL;
             rdset = rdset->getNext())
        {
            // Checking all types for all RdataSets could be suboptimal.
            // This can be a bit more optimized, but unless we have many
            // requested types the effect is probably marginal.  For now we
            // keep it simple.
            if (std::find(type_beg, type_end, rdset->type) != type_end) {
                result->push_back(createTreeNodeRRset(node, rdset, rrclass_,
                                                      options, real_name));
            }
        }
    }

private:
    InMemoryZoneFinder& finder_;
    const RRClass rrclass_;
    const ZoneData* const zone_data_;
    const ZoneNode* const found_node_;
    const RdataSet* const found_rdset_;
};

void
InMemoryZoneFinder::Context::findAdditional(
    const std::vector<RRType>* requested_types,
    std::vector<ConstRRsetPtr>* result,
    ZoneFinder::FindOptions options,
    const LabelSequence& name_labels,
    RdataNameAttributes attr) const
{
    // Ignore name data that don't need additional processing.
    if ((attr & NAMEATTR_ADDITIONAL) == 0) {
        return;
    }

    // Find the zone node for the additional name.  By passing true as the
    // last parameter of findNode() we ignore out-of-zone names.
    ZoneChain node_path;
    const FindNodeResult node_result =
        findNode(*zone_data_, name_labels, node_path, options, true);
    // we only need non-empty exact match
    if (node_result.code != SUCCESS) {
        return;
    }

    // Ignore data at a zone cut (due to subdomain delegation) unless glue is
    // allowed.  Checking the node callback flag is a cheap way to detect
    // zone cuts, but it includes DNAME delegation, in which case we should
    // keep finding the additional records regardless of the 'GLUE_OK' flag.
    // The last two conditions limit the case to delegation NS, i.e, the node
    // has an NS and it's not the zone origin.
    const ZoneNode* node = node_result.node;
    if ((options & ZoneFinder::FIND_GLUE_OK) == 0 &&
        node->getFlag(ZoneNode::FLAG_CALLBACK) &&
        node != zone_data_->getOriginNode() &&
        RdataSet::find(node->getData(), RRType::NS()) != NULL) {
        return;
    }

    // Examine RdataSets of the node, and create and insert requested types
    // of RRsets as we find them.
    if ((node_result.flags & FindNodeResult::FIND_WILDCARD) == 0) {
        // normal case
        findAdditionalHelper(requested_types, result, node, options, NULL);
    } else {
        // if the additional name is subject to wildcard substitution, we need
        // to create a name object for the "real" (after substitution) name.
        // This is expensive, but in the additional processing this should be
        // very rare cases and acceptable.
        size_t data_len;
        const uint8_t* data;
        data = name_labels.getData(&data_len);
        util::InputBuffer buffer(data, data_len);
        const Name real_name(buffer);
        findAdditionalHelper(requested_types, result, node, options,
                             &real_name);
    }
}

boost::shared_ptr<ZoneFinder::Context>
InMemoryZoneFinder::find(const isc::dns::Name& name,
                const isc::dns::RRType& type,
                const FindOptions options)
{
    return (ZoneFinderContextPtr(new Context(*this, options, rrclass_,
                                             find_internal(name, type,
                                                           NULL, options))));
}

boost::shared_ptr<ZoneFinder::Context>
InMemoryZoneFinder::findAll(const isc::dns::Name& name,
        std::vector<isc::dns::ConstRRsetPtr>& target,
        const FindOptions options)
{
    return (ZoneFinderContextPtr(new Context(*this, options, rrclass_,
                                             find_internal(name,
                                                           RRType::ANY(),
                                                           &target,
                                                           options))));
}

ZoneFinderResultContext
InMemoryZoneFinder::find_internal(const isc::dns::Name& name,
                                  const isc::dns::RRType& type,
                                  std::vector<ConstRRsetPtr>* target,
                                  const FindOptions options)
{
    // Get the node.  All other cases than an exact match are handled
    // in findNode().  We simply construct a result structure and return.
    ZoneChain node_path;
    const FindNodeResult node_result =
        findNode(zone_data_, LabelSequence(name), node_path, options);
    if (node_result.code != SUCCESS) {
        return (createFindResult(rrclass_, zone_data_, node_result.code,
                                 node_result.rrset, node_result.node,
                                 options));
    }

    const ZoneNode* node = node_result.node;
    assert(node != NULL);

    // We've found an exact match, may or may not be a result of wildcard.
    const bool wild = ((node_result.flags &
                        FindNodeResult::FIND_WILDCARD) != 0);

    // If there is an exact match but the node is empty, it's equivalent
    // to NXRRSET.
    if (node->isEmpty()) {
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DOMAIN_EMPTY).
            arg(name);
        const ZoneNode* nsec_node;
        const RdataSet* nsec_rds = getClosestNSEC(zone_data_, node_path,
                                                  &nsec_node, options);
        return (createFindResult(rrclass_, zone_data_, NXRRSET,
                                 nsec_rds, nsec_node, options, wild));
    }

    const RdataSet* found;

    // If the node callback is enabled, this may be a zone cut.  If it
    // has a NS RR, we should return a delegation, but not in the apex.
    // There are two exceptions:
    // - the case for DS query, which should always be considered in-zone
    //   lookup.
    // - when we are looking for glue records (FIND_GLUE_OK)
    if (node->getFlag(ZoneNode::FLAG_CALLBACK) &&
        (options & FIND_GLUE_OK) == 0 &&
        node != zone_data_.getOriginNode() && type != RRType::DS()) {
        found = RdataSet::find(node->getData(), RRType::NS());
        if (found != NULL) {
            LOG_DEBUG(logger, DBG_TRACE_DATA,
                      DATASRC_MEM_EXACT_DELEGATION).arg(name);
            return (createFindResult(rrclass_, zone_data_, DELEGATION,
                                     found, node, options, wild, &name));
        }
    }

    // Handle type any query
    if (target != NULL && node->getData() != NULL) {
        // Empty domain will be handled as NXRRSET by normal processing
        const RdataSet* cur_rds = node->getData();
        while (cur_rds != NULL) {
            target->push_back(createTreeNodeRRset(node, cur_rds, rrclass_,
                                                  options, &name));
            cur_rds = cur_rds->getNext();
        }
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ANY_SUCCESS).
            arg(name);
        return (createFindResult(rrclass_, zone_data_, SUCCESS, NULL, node,
                                 options, wild, &name));
    }

    found = RdataSet::find(node->getData(), type);
    if (found != NULL) {
        // Good, it is here
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_SUCCESS).arg(name).
            arg(type);
        return (createFindResult(rrclass_, zone_data_, SUCCESS, found, node,
                                 options, wild, &name));
    } else {
        // Next, try CNAME.
        found = RdataSet::find(node->getData(), RRType::CNAME());
        if (found != NULL) {

            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_CNAME).arg(name);
            return (createFindResult(rrclass_, zone_data_, CNAME, found, node,
                                     options, wild, &name));
        }
    }
    // No exact match or CNAME.  Get NSEC if necessary and return NXRRSET.
    return (createFindResult(rrclass_, zone_data_, NXRRSET,
                             getNSECForNXRRSET(zone_data_, options, node),
                             node, options, wild, &name));
}

isc::datasrc::ZoneFinder::FindNSEC3Result
InMemoryZoneFinder::findNSEC3(const isc::dns::Name& name, bool recursive) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FINDNSEC3).arg(name).
        arg(recursive ? "recursive" : "non-recursive");

    uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];
    const LabelSequence origin_ls(zone_data_.getOriginNode()->
                                  getAbsoluteLabels(labels_buf));
    const LabelSequence name_ls(name);

    if (!zone_data_.isNSEC3Signed()) {
        isc_throw(DataSourceError,
                  "findNSEC3 attempt for non NSEC3 signed zone: " <<
                  origin_ls << "/" << getClass());
    }

    const NSEC3Data* nsec3_data = zone_data_.getNSEC3Data();
    // This would be a programming mistake, as ZoneData::isNSEC3Signed()
    // should check this.
    assert(nsec3_data != NULL);

    const ZoneTree& tree = nsec3_data->getNSEC3Tree();
    if (tree.getNodeCount() == 0) {
        isc_throw(DataSourceError,
                  "findNSEC3 attempt but zone has no NSEC3 RRs: " <<
                  origin_ls << "/" << getClass());
    }

    const NameComparisonResult cmp_result = name_ls.compare(origin_ls);
    if (cmp_result.getRelation() != NameComparisonResult::EQUAL &&
        cmp_result.getRelation() != NameComparisonResult::SUBDOMAIN) {
        isc_throw(OutOfZone, "findNSEC3 attempt for out-of-zone name: "
                  << name_ls << ", zone: " << origin_ls << "/"
                  << getClass());
    }

    // Convenient shortcuts
    const unsigned int olabels = origin_ls.getLabelCount();
    const unsigned int qlabels = name.getLabelCount();
    // placeholder of the next closer proof
    const ZoneNode* covering_node(NULL);

    // Now we'll first look up the origin node and initialize orig_chain
    // with it.
    ZoneChain orig_chain;
    const ZoneNode* node(NULL);
    ZoneTree::Result result =
         tree.find<void*>(origin_ls, &node, orig_chain, NULL, NULL);
    if (result != ZoneTree::EXACTMATCH) {
        // If the origin node doesn't exist, simply fail.
        isc_throw(DataSourceError,
                  "findNSEC3 attempt but zone has no NSEC3 RRs: " <<
                  origin_ls << "/" << getClass());
    }

    const boost::scoped_ptr<NSEC3Hash> hash
        (NSEC3Hash::create(nsec3_data->hashalg,
                           nsec3_data->iterations,
                           nsec3_data->getSaltData(),
                           nsec3_data->getSaltLen()));

    // Examine all names from the query name to the origin name, stripping
    // the deepest label one by one, until we find a name that has a matching
    // NSEC3 hash.
    for (unsigned int labels = qlabels; labels >= olabels; --labels) {
        const Name& hname = (labels == qlabels ?
                             name : name.split(qlabels - labels, labels));
        const std::string hlabel = hash->calculate(hname);

        LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FINDNSEC3_TRYHASH).
            arg(name).arg(labels).arg(hlabel);

        node = NULL;
        ZoneChain chain(orig_chain);

        // Now, make a label sequence relative to the origin.
        const Name hlabel_name(hlabel);
        LabelSequence hlabel_ls(hlabel_name);
        // Remove trailing '.' making it relative
        hlabel_ls.stripRight(1);

        // Find hlabel relative to the orig_chain.
        result = tree.find<void*>(hlabel_ls, &node, chain, NULL, NULL);
        if (result == ZoneTree::EXACTMATCH) {
            // We found an exact match.
            ConstRRsetPtr closest = createNSEC3RRset(node, getClass());
            ConstRRsetPtr next;
            if (covering_node != NULL) {
                next = createNSEC3RRset(covering_node, getClass());
            }

            LOG_DEBUG(logger, DBG_TRACE_BASIC,
                      DATASRC_MEM_FINDNSEC3_MATCH).arg(name).arg(labels).
                arg(*closest);

            return (FindNSEC3Result(true, labels, closest, next));
        } else {
            while ((covering_node = tree.previousNode(chain)) != NULL &&
                   covering_node->isEmpty()) {
                ;
            }
            if (covering_node == NULL) {
                covering_node = tree.largestNode();
            }

            if (!recursive) {   // in non recursive mode, we are done.
                ConstRRsetPtr closest;
                if (covering_node != NULL) {
                    closest = createNSEC3RRset(covering_node, getClass());

                    LOG_DEBUG(logger, DBG_TRACE_BASIC,
                              DATASRC_MEM_FINDNSEC3_COVER).
                        arg(name).arg(*closest);
                }

                return (FindNSEC3Result(false, labels,
                                        closest, ConstRRsetPtr()));
            }
        }
    }

    isc_throw(DataSourceError, "recursive findNSEC3 mode didn't stop, likely "
              "a broken NSEC3 zone: " << getOrigin() << "/"
              << getClass());
}

Name
InMemoryZoneFinder::getOrigin() const {
    // In future we may allow adding out-of-zone names in the zone tree.
    // For example, to hold out-of-zone NS names so we can establish a
    // shortcut link to them as an optimization.  If and when that happens
    // the origin node may not have an absolute label (consider the zone
    // is example.org and we add ns.noexample.org).  Even in such cases,
    // DomainTreeNode::getAbsoluteLabels() returns the correct absolute
    // label sequence.
    uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];
    const LabelSequence name_labels =
         zone_data_.getOriginNode()->getAbsoluteLabels(labels_buf);
    size_t data_len;
    const uint8_t* data = name_labels.getData(&data_len);

    util::InputBuffer buffer(data, data_len);
    return (Name(buffer));
}

} // namespace memory
} // namespace datasrc
} // namespace isc
