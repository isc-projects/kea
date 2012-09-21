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

#include <util/buffer.h>
#include <util/encode/base32hex.h>
#include <util/hash/sha1.h>

#include <datasrc/logger.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::datasrc;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::util::hash;

namespace isc {
namespace datasrc {
namespace memory {

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
                    const Name* realname = NULL)
{
    if (node != NULL && rdataset != NULL) {
        if (realname != NULL) {
            return TreeNodeRRsetPtr(new TreeNodeRRset(*realname, rrclass, node,
                                                      rdataset, true));
        } else {
            return TreeNodeRRsetPtr(new TreeNodeRRset(rrclass, node,
                                                      rdataset, true));
        }
    } else {
        return TreeNodeRRsetPtr();
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
// This will be passed from findNode() to \c RBTree::find().
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
isc::datasrc::memory::ZoneFinderResultContext
createFindResult(const RRClass& rrclass,
                 const ZoneData& zone_data,
                 ZoneFinder::Result code,
                 const RdataSet* rrset,
                 const ZoneNode* node,
                 bool wild = false,
                 const Name* qname = NULL) {
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

    return (ZoneFinderResultContext(code, createTreeNodeRRset(node, rrset,
                                                              rrclass, rename),
                                    flags, node));
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
// to be set by findNode()); otherwise the underlying RBTree implementation
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
// the zone, and throw an OutOfZone exception.
FindNodeResult findNode(const ZoneData& zone_data,
                        const Name& name,
                        ZoneChain& node_path,
                        ZoneFinder::FindOptions options)
{
    ZoneNode* node = NULL;
    FindState state((options & ZoneFinder::FIND_GLUE_OK) != 0);

    const ZoneTree& tree(zone_data.getZoneTree());
    ZoneTree::Result result = tree.find(isc::dns::LabelSequence(name),
                                        &node, node_path, cutCallback,
                                        &state);
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
                      DATASRC_MEM_SUPER_STOP).arg(name);
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
                          DATASRC_MEM_WILDCARD_CANCEL).arg(name);
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
            ZoneTree::Result result = tree.find(LabelSequence(wildcard_ls),
                                                &node, node_path, cutCallback,
                                                &state);
            // Otherwise, why would the domain_flag::WILD be there if
            // there was no wildcard under it?
            assert(result == ZoneTree::EXACTMATCH);
            return (FindNodeResult(ZoneFinder::SUCCESS, node, state.rrset_,
                        FindNodeResult::FIND_WILDCARD | zonecut_flag));
        }

        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_NOT_FOUND).arg(name);
        const ZoneNode* nsec_node;
        const RdataSet* nsec_rds = getClosestNSEC(zone_data, node_path,
                                                  &nsec_node, options);
        return (FindNodeResult(ZoneFinder::NXDOMAIN, nsec_node, nsec_rds));
    } else {
        // If the name is neither an exact or partial match, it is
        // out of bailiwick, which is considered an error.
        isc_throw(OutOfZone, name.toText() << " not in " <<
                             zone_data.getOriginNode()->getName());
    }
}

} // end anonymous namespace

inline void
iterateSHA1(SHA1Context* ctx, const uint8_t* input, size_t inlength,
            const uint8_t* salt, size_t saltlen,
            uint8_t output[SHA1_HASHSIZE])
{
    SHA1Reset(ctx);
    SHA1Input(ctx, input, inlength);
    SHA1Input(ctx, salt, saltlen); // this works whether saltlen == or > 0
    SHA1Result(ctx, output);
}

std::string
InMemoryZoneFinderNSEC3Calculate(const Name& name,
                                 const uint16_t iterations,
                                 const uint8_t* salt,
                                 size_t salt_len) {
    // We first need to normalize the name by converting all upper case
    // characters in the labels to lower ones.
    OutputBuffer obuf(Name::MAX_WIRE);
    Name name_copy(name);
    name_copy.downcase();
    name_copy.toWire(obuf);

    const uint8_t* const salt_buf = (salt_len > 0) ? salt : NULL;
    std::vector<uint8_t> digest(SHA1_HASHSIZE);
    uint8_t* const digest_buf = &digest[0];

    SHA1Context sha1_ctx;
    iterateSHA1(&sha1_ctx, static_cast<const uint8_t*>(obuf.getData()),
                obuf.getLength(), salt_buf, salt_len, digest_buf);
    for (unsigned int n = 0; n < iterations; ++n) {
        iterateSHA1(&sha1_ctx, digest_buf, SHA1_HASHSIZE,
                    salt_buf, salt_len,
                    digest_buf);
    }

    return (encodeBase32Hex(digest));
}

// Specialization of the ZoneFinder::Context for the in-memory finder.
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
    ZoneChain node_path;
    const FindNodeResult node_result =
        findNode(zone_data_, name, node_path, options);
    if (node_result.code != SUCCESS) {
        return (createFindResult(rrclass_, zone_data_, node_result.code,
                                 node_result.rrset, node_result.node));
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
                                 nsec_rds,
                                 nsec_node,
                                 wild));
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
            return (createFindResult(rrclass_, zone_data_, DELEGATION,
                                     found, node, wild, &name));
        }
    }

    // Handle type any query
    if (target != NULL && node->getData() != NULL) {
        // Empty domain will be handled as NXRRSET by normal processing
        const RdataSet* cur_rds = node->getData();
        while (cur_rds != NULL) {
            target->push_back(createTreeNodeRRset(node, cur_rds, rrclass_,
                                                  &name));
            cur_rds = cur_rds->getNext();
        }
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ANY_SUCCESS).
            arg(name);
        return (createFindResult(rrclass_, zone_data_, SUCCESS, NULL, node,
                                 wild, &name));
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
        return (createFindResult(rrclass_, zone_data_, SUCCESS, found, node,
                                 wild, &name));
    } else {
        // Next, try CNAME.
        found = RdataSet::find(node->getData(), RRType::CNAME());
        if (found != NULL) {

            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_CNAME).arg(name);
            return (createFindResult(rrclass_, zone_data_, CNAME, found, node,
                                     wild, &name));
        }
    }
    // No exact match or CNAME.  Get NSEC if necessary and return NXRRSET.
    return (createFindResult(rrclass_, zone_data_, NXRRSET,
                             getNSECForNXRRSET(zone_data_, options, node),
                             node, wild, &name));
}

isc::datasrc::ZoneFinder::FindNSEC3Result
InMemoryZoneFinder::findNSEC3(const isc::dns::Name& name, bool recursive) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FINDNSEC3).arg(name).
        arg(recursive ? "recursive" : "non-recursive");

    if (!zone_data_.isNSEC3Signed()) {
        isc_throw(DataSourceError,
                  "findNSEC3 attempt for non NSEC3 signed zone: " <<
                  getOrigin() << "/" << getClass());
    }

    const NSEC3Data* nsec3_data = zone_data_.getNSEC3Data();
    const ZoneTree& tree = nsec3_data->getNSEC3Tree();
    if (tree.getNodeCount() == 0) {
        isc_throw(DataSourceError,
                  "findNSEC3 attempt but zone has no NSEC3 RR: " <<
                  getOrigin() << "/" << getClass());
    }

    const NameComparisonResult cmp_result = name.compare(getOrigin());
    if (cmp_result.getRelation() != NameComparisonResult::EQUAL &&
        cmp_result.getRelation() != NameComparisonResult::SUBDOMAIN) {
        isc_throw(OutOfZone, "findNSEC3 attempt for out-of-zone name: "
                  << name << ", zone: " << getOrigin() << "/"
                  << getClass());
    }

    // Convenient shortcuts
    const unsigned int olabels = getOrigin().getLabelCount();
    const unsigned int qlabels = name.getLabelCount();

    // placeholder of the next closer proof
    const ZoneNode* covering_node(NULL);

    ZoneChain chain;

    // Examine all names from the query name to the origin name, stripping
    // the deepest label one by one, until we find a name that has a matching
    // NSEC3 hash.
    for (unsigned int labels = qlabels; labels >= olabels; --labels) {
        const Name& hname = (labels == qlabels ?
                             name : name.split(qlabels - labels, labels));
        const std::string hlabel =
            (nsec3_calculate_) (hname,
                                nsec3_data->iterations,
                                nsec3_data->getSaltData(),
                                nsec3_data->getSaltLen());

        LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FINDNSEC3_TRYHASH).
            arg(name).arg(labels).arg(hlabel);

        ZoneNode* node(NULL);
        chain.clear();
        const ZoneTree::Result result =
            tree.find(Name(hlabel).concatenate(getOrigin()), &node, chain);

        if (result == ZoneTree::EXACTMATCH) {
            // We found an exact match.
            const RdataSet* rdataset = node->getData();
            assert(rdataset != NULL);
            assert(rdataset->type == RRType::NSEC3());

            ConstRRsetPtr closest = createTreeNodeRRset(node, rdataset,
                                                        getClass());
            ConstRRsetPtr next;
            if (covering_node != NULL) {
                rdataset = covering_node->getData();
                assert(rdataset != NULL);
                assert(rdataset->type == RRType::NSEC3());

                next = createTreeNodeRRset(covering_node, rdataset,
                                           getClass());
            }

            LOG_DEBUG(logger, DBG_TRACE_BASIC,
                      DATASRC_MEM_FINDNSEC3_MATCH).arg(name).arg(labels).
                arg(*closest);

            return (FindNSEC3Result(true, labels, closest, next));
        } else {
            const NameComparisonResult& last_cmp =
                chain.getLastComparisonResult();
            const ZoneNode* last_node = chain.getLastComparedNode();
            assert(last_cmp.getOrder() != 0);

            // find() finished in between one of these and last_node:
            const ZoneNode* previous_node = last_node->predecessor();
            const ZoneNode* next_node = last_node->successor();

            // If the given hash is larger than the largest stored hash or
            // the first label doesn't match the target, identify the
            // "previous" hash value and remember it as the candidate next
            // closer proof.
            if (((last_cmp.getOrder() < 0) && (previous_node == NULL)) ||
                ((last_cmp.getOrder() > 0) && (next_node == NULL))) {
                covering_node = last_node->getLargestInSubTree();
            } else {
                // Otherwise, H(found_entry-1) < given_hash < H(found_entry).
                // The covering proof is the first one (and it's valid
                // because found is neither begin nor end)
                covering_node = previous_node;
            }

            if (!recursive) {   // in non recursive mode, we are done.
                ConstRRsetPtr closest;
                if (covering_node != NULL) {
                    const RdataSet* rdataset = covering_node->getData();
                    assert(rdataset != NULL);
                    assert(rdataset->type == RRType::NSEC3());

                    closest = createTreeNodeRRset(covering_node, rdataset,
                                                  getClass());
                }

                if (closest) {
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

} // namespace memory
} // namespace datasrc
} // namespace isc
