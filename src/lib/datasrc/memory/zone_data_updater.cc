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

#include <exceptions/exceptions.h>

#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/memory/logger.h>
#include <datasrc/memory/util_internal.h>
#include <datasrc/zone.h>

#include <dns/rdataclass.h>

#include <cassert>
#include <string>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

using detail::getCoveredType;

void
ZoneDataUpdater::addWildcards(const Name& name) {
    Name wname(name);
    const unsigned int labels(wname.getLabelCount());
    const unsigned int origin_labels(zone_name_.getLabelCount());
    for (unsigned int l = labels;
         l > origin_labels;
         --l, wname = wname.split(1))
    {
        if (wname.isWildcard()) {
            LOG_DEBUG(logger, DBG_TRACE_DATA,
                      DATASRC_MEMORY_MEM_ADD_WILDCARD).arg(name);

            // Ensure a separate level exists for the "wildcarding"
            // name, and mark the node as "wild".
            ZoneNode* node;
            zone_data_.insertName(mem_sgmt_, wname.split(1), &node);
            node->setFlag(ZoneData::WILDCARD_NODE);

            // Ensure a separate level exists for the wildcard name.
            // Note: for 'name' itself we do this later anyway, but the
            // overhead should be marginal because wildcard names should
            // be rare.
            zone_data_.insertName(mem_sgmt_, wname, &node);
        }
    }
}

void
ZoneDataUpdater::contextCheck(const AbstractRRset& rrset,
                              const RdataSet* rdataset) const
{
    // Ensure CNAME and other type of RR don't coexist for the same
    // owner name except with NSEC, which is the only RR that can
    // coexist with CNAME (and also RRSIG, which is handled separately)
    if (rrset.getType() == RRType::CNAME()) {
        for (const RdataSet* sp = rdataset; sp != NULL; sp = sp->getNext()) {
            if (sp->type != RRType::NSEC()) {
                LOG_ERROR(logger, DATASRC_MEMORY_MEM_CNAME_TO_NONEMPTY).
                    arg(rrset.getName());
                isc_throw(AddError,
                          "CNAME can't be added with " << sp->type
                          << " RRType for " << rrset.getName());
            }
        }
    } else if ((rrset.getType() != RRType::NSEC()) &&
               (RdataSet::find(rdataset, RRType::CNAME()) != NULL))
    {
        LOG_ERROR(logger,
                  DATASRC_MEMORY_MEM_CNAME_COEXIST).arg(rrset.getName());
        isc_throw(AddError,
                  "CNAME and " << rrset.getType() <<
                  " can't coexist for " << rrset.getName());
    }

    // Similar with DNAME, but it must not coexist only with NS and only
    // in non-apex domains.  RFC 2672 section 3 mentions that it is
    // implied from it and RFC 2181.
    if (rrset.getName() != zone_name_ &&
        // Adding DNAME, NS already there
        ((rrset.getType() == RRType::DNAME() &&
          RdataSet::find(rdataset, RRType::NS()) != NULL) ||
         // Adding NS, DNAME already there
         (rrset.getType() == RRType::NS() &&
          RdataSet::find(rdataset, RRType::DNAME()) != NULL)))
    {
        LOG_ERROR(logger, DATASRC_MEMORY_MEM_DNAME_NS).arg(rrset.getName());
        isc_throw(AddError, "DNAME can't coexist with NS in non-apex domain: "
                  << rrset.getName());
    }
}

void
ZoneDataUpdater::validate(const isc::dns::ConstRRsetPtr rrset) const {
    assert(rrset);

    if (rrset->getRdataCount() == 0) {
        isc_throw(AddError,
                  "The rrset provided is empty: "
                  << rrset->getName() << "/" << rrset->getType());
    }

    // Check for singleton RRs. It should probably handled at a different
    // layer in future.
    if ((rrset->getType() == RRType::CNAME() ||
         rrset->getType() == RRType::DNAME()) &&
        rrset->getRdataCount() > 1)
    {
        // XXX: this is not only for CNAME or DNAME. We should
        // generalize this code for all other "singleton RR types" (such
        // as SOA) in a separate task.
        LOG_ERROR(logger,
                  DATASRC_MEMORY_MEM_SINGLETON).arg(rrset->getName()).
            arg(rrset->getType());
        isc_throw(AddError, "multiple RRs of singleton type for "
                  << rrset->getName());
    }

    // NSEC3/NSEC3PARAM is not a "singleton" per protocol, but this
    // implementation requests it be so at the moment.
    if ((rrset->getType() == RRType::NSEC3() ||
         rrset->getType() == RRType::NSEC3PARAM()) &&
        (rrset->getRdataCount() > 1))
    {
        isc_throw(AddError, "Multiple NSEC3/NSEC3PARAM RDATA is given for "
                  << rrset->getName() << " which isn't supported");
    }

    // For RRSIGs, check consistency of the type covered.  We know the
    // RRset isn't empty, so the following check is safe.
    if (rrset->getType() == RRType::RRSIG()) {
        RdataIteratorPtr rit = rrset->getRdataIterator();
        const RRType covered = dynamic_cast<const generic::RRSIG&>(
            rit->getCurrent()).typeCovered();
        for (rit->next(); !rit->isLast(); rit->next()) {
            if (dynamic_cast<const generic::RRSIG&>(
                     rit->getCurrent()).typeCovered() != covered)
            {
                isc_throw(AddError, "RRSIG contains mixed covered types: "
                          << rrset->toText());
            }
        }
    }

    const NameComparisonResult compare = zone_name_.compare(rrset->getName());
    if (compare.getRelation() != NameComparisonResult::SUPERDOMAIN &&
        compare.getRelation() != NameComparisonResult::EQUAL)
    {
        LOG_ERROR(logger,
                  DATASRC_MEMORY_MEM_OUT_OF_ZONE).arg(rrset->getName()).
            arg(zone_name_);
        isc_throw(AddError,
                  "The name " << rrset->getName() <<
                  " is not contained in zone " << zone_name_);
    }

    // Some RR types do not really work well with a wildcard.  Even
    // though the protocol specifically doesn't completely ban such
    // usage, we refuse to load a zone containing such RR in order to
    // keep the lookup logic simpler and more predictable.  See RFC4592
    // and (for DNAME) RFC6672 for more technical background.  Note also
    // that BIND 9 refuses NS at a wildcard, so in that sense we simply
    // provide compatible behavior.
    if (rrset->getName().isWildcard()) {
        if (rrset->getType() == RRType::NS()) {
            LOG_ERROR(logger, DATASRC_MEMORY_MEM_WILDCARD_NS).
                arg(rrset->getName());
            isc_throw(AddError, "Invalid NS owner name (wildcard): "
                      << rrset->getName());
        }

        if (rrset->getType() == RRType::DNAME()) {
            LOG_ERROR(logger, DATASRC_MEMORY_MEM_WILDCARD_DNAME).
                arg(rrset->getName());
            isc_throw(AddError, "Invalid DNAME owner name (wildcard): "
                      << rrset->getName());
        }
    }

    // Owner names of NSEC3 have special format as defined in RFC5155,
    // and cannot be a wildcard name or must be one label longer than
    // the zone origin.  While the RFC doesn't prohibit other forms of
    // names, no sane zone would have such names for NSEC3.  BIND 9 also
    // refuses NSEC3 at wildcard.
    if (rrset->getType() == RRType::NSEC3() &&
        (rrset->getName().isWildcard() ||
         rrset->getName().getLabelCount() != zone_name_.getLabelCount() + 1))
    {
        LOG_ERROR(logger, DATASRC_MEMORY_BAD_NSEC3_NAME).arg(rrset->getName());
        isc_throw(AddError, "Invalid NSEC3 owner name: " <<
                  rrset->getName() << "; zone: " << zone_name_);
    }
}

const NSEC3Hash*
ZoneDataUpdater::getNSEC3Hash() {
    if (hash_ == NULL) {
        NSEC3Data* nsec3_data = zone_data_.getNSEC3Data();
        // This should never be NULL in this codepath.
        assert(nsec3_data != NULL);

        hash_ = NSEC3Hash::create(nsec3_data->hashalg,
                                  nsec3_data->iterations,
                                  nsec3_data->getSaltData(),
                                  nsec3_data->getSaltLen());
    }

    return (hash_);
}

template <typename T>
void
ZoneDataUpdater::setupNSEC3(const ConstRRsetPtr rrset) {
    // We know rrset has exactly one RDATA
    const T& nsec3_rdata =
        dynamic_cast<const T&>(
            rrset->getRdataIterator()->getCurrent());

    NSEC3Data* nsec3_data = zone_data_.getNSEC3Data();
    if (nsec3_data == NULL) {
        nsec3_data = NSEC3Data::create(mem_sgmt_, nsec3_rdata);
        zone_data_.setNSEC3Data(nsec3_data);
        zone_data_.setSigned(true);
    } else {
        const NSEC3Hash* hash = getNSEC3Hash();
        if (!hash->match(nsec3_rdata)) {
            isc_throw(AddError,
                      rrset->getType() << " with inconsistent parameters: "
                      << rrset->toText());
        }
    }
}

void
ZoneDataUpdater::addNSEC3(const Name& name, const ConstRRsetPtr rrset,
                          const ConstRRsetPtr rrsig)
{
    if (rrset) {
        setupNSEC3<generic::NSEC3>(rrset);
    }

    NSEC3Data* nsec3_data = zone_data_.getNSEC3Data();
    if (nsec3_data == NULL) {
        // This is some tricky case: an RRSIG for NSEC3 is given without the
        // covered NSEC3, and we don't even know any NSEC3 related data.
        // This situation is not necessarily broken, but in our current
        // implementation it's very difficult to deal with.  So we reject it;
        // hopefully this case shouldn't happen in practice, at least unless
        // zone is really broken.
        assert(!rrset);
        isc_throw(NotImplemented,
                  "RRSIG for NSEC3 cannot be added - no known NSEC3 data");
    }

    ZoneNode* node;
    nsec3_data->insertName(mem_sgmt_, name, &node);

    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, rrset, rrsig);
    RdataSet* old_rdataset = node->setData(rdataset);
    if (old_rdataset != NULL) {
        RdataSet::destroy(mem_sgmt_, old_rdataset, rrclass_);
    }
}

void
ZoneDataUpdater::addRdataSet(const Name& name, const RRType& rrtype,
                             const ConstRRsetPtr rrset,
                             const ConstRRsetPtr rrsig)
{
    if (rrtype == RRType::NSEC3()) {
        addNSEC3(name, rrset, rrsig);
    } else {
        ZoneNode* node;
        zone_data_.insertName(mem_sgmt_, name, &node);

        RdataSet* rdataset_head = node->getData();

        // Checks related to the surrounding data.  Note: when the check
        // fails and the exception is thrown, it may break strong
        // exception guarantee.  At the moment we prefer code simplicity
        // and don't bother to introduce complicated recovery code.
        if (rrset) { // this check is only for covered RRset, not RRSIG
            contextCheck(*rrset, rdataset_head);
        }

        if (RdataSet::find(rdataset_head, rrtype, true) != NULL) {
            isc_throw(AddError,
                      "RRset of the type already exists: "
                      << name << " (type: " << rrtype << ")");
        }

        RdataSet* rdataset_new = RdataSet::create(mem_sgmt_, encoder_,
                                                  rrset, rrsig);
        rdataset_new->next = rdataset_head;
        node->setData(rdataset_new);

        // Ok, we just put it in.

        // Convenient (and more efficient) shortcut to check RRsets at origin
        const bool is_origin = (node == zone_data_.getOriginNode());

        // If this RRset creates a zone cut at this node, mark the node
        // indicating the need for callback in find().  Note that we do this
        // only when non RRSIG RRset of that type is added.
        if (rrset && rrtype == RRType::NS() && !is_origin) {
            node->setFlag(ZoneNode::FLAG_CALLBACK);
            // If it is DNAME, we have a callback as well here
        } else if (rrset && rrtype == RRType::DNAME()) {
            node->setFlag(ZoneNode::FLAG_CALLBACK);
        }

        // If we've added NSEC3PARAM at zone origin, set up NSEC3
        // specific data or check consistency with already set up
        // parameters.
        if (rrset && rrtype == RRType::NSEC3PARAM() && is_origin) {
            setupNSEC3<generic::NSEC3PARAM>(rrset);
        } else if (rrset && rrtype == RRType::NSEC() && is_origin) {
            // If it is NSEC signed zone, we mark the zone as signed
            // (conceptually "signed" is a broader notion but our
            // current zone finder implementation regards "signed" as
            // "NSEC signed")
            zone_data_.setSigned(true);
        }
    }
}

void
ZoneDataUpdater::add(const ConstRRsetPtr& rrset,
                     const ConstRRsetPtr& sig_rrset)
{
    // Validate input.
    if (!rrset && !sig_rrset) {
        isc_throw(NullRRset,
                  "ZoneDataUpdater::add is given 2 NULL pointers");
    }
    if (rrset) {
        validate(rrset);
    }
    if (sig_rrset) {
        validate(sig_rrset);
    }

    const Name& name = rrset ? rrset->getName() : sig_rrset->getName();
    const RRType& rrtype = rrset ? rrset->getType() :
        getCoveredType(sig_rrset);

    // OK, can add the RRset.
    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEMORY_MEM_ADD_RRSET).arg(name).
        arg(rrset ? rrtype.toText() : "RRSIG(" + rrtype.toText() + ")").
        arg(zone_name_);

    // Add wildcards possibly contained in the owner name to the domain
    // tree.  This can only happen for the normal (non-NSEC3) tree.
    // Note: this can throw an exception, breaking strong exception
    // guarantee.  (see also the note for the call to contextCheck()
    // above).
    if (rrtype != RRType::NSEC3()) {
        addWildcards(name);
    }

    addRdataSet(name, rrtype, rrset, sig_rrset);
}

} // namespace memory
} // namespace datasrc
} // namespace isc
