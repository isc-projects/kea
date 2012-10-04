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

#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/zone.h>

#include <dns/rdataclass.h>
#include <dns/nsec3hash.h>

#include <boost/scoped_ptr.hpp>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

namespace { // anonymous namespace

// Returns a value-less than, or greater-than zero if 'a' is less-than
// or greater-than 'b'. If they are equal, it returns 0. The comparison
// function is such that often-used types such as A, AAAA, NS, SOA, MX,
// etc.  are less than other types. See the code for the ordering.
int
compareTypes(const RdataSet* a, const RdataSet* b) {
    // First RRType::A()
    if (a->type == RRType::A()) {
        return (-1);
    } else if (b->type == RRType::A()) {
        return (1);
    }

    // Then, RRType::AAAA(), etc.
    if (a->type == RRType::AAAA()) {
        return (-1);
    } else if (b->type == RRType::AAAA()) {
        return (1);
    }

    if (a->type == RRType::NS()) {
        return (-1);
    } else if (b->type == RRType::NS()) {
        return (1);
    }

    if (a->type == RRType::SOA()) {
        return (-1);
    } else if (b->type == RRType::SOA()) {
        return (1);
    }

    if (a->type == RRType::MX()) {
        return (-1);
    } else if (b->type == RRType::MX()) {
        return (1);
    }

    // Everything else comes in front of the rest of the list, so that
    // we can insert quickly.
    return (-1);
}

} // end of anonymous namespace

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
                              const RdataSet* set) const
{
    // Ensure CNAME and other type of RR don't coexist for the same
    // owner name except with NSEC, which is the only RR that can
    // coexist with CNAME (and also RRSIG, which is handled separately)
    if (rrset.getType() == RRType::CNAME()) {
        for (const RdataSet* sp = set; sp != NULL; sp = sp->getNext()) {
            if (sp->type != RRType::NSEC()) {
                isc_throw(AddError,
                          "CNAME can't be added with " << sp->type
                          << " RRType for " << rrset.getName());
            }
        }
    } else if ((rrset.getType() != RRType::NSEC()) &&
               (RdataSet::find(set, RRType::CNAME()) != NULL))
    {
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
          RdataSet::find(set, RRType::NS()) != NULL) ||
         // Adding NS, DNAME already there
         (rrset.getType() == RRType::NS() &&
          RdataSet::find(set, RRType::DNAME()) != NULL)))
    {
        isc_throw(AddError, "DNAME can't coexist with NS in non-apex domain: "
                  << rrset.getName());
    }
}

void
ZoneDataUpdater::validate(const isc::dns::ConstRRsetPtr rrset) const {
    if (!rrset) {
        isc_throw(NullRRset, "The rrset provided is NULL");
    }

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
        isc_throw(OutOfZone,
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
            isc_throw(AddError, "Invalid NS owner name (wildcard): "
                      << rrset->getName());
        }

        if (rrset->getType() == RRType::DNAME()) {
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
         rrset->getName().getLabelCount() !=
         zone_name_.getLabelCount() + 1))
    {
        isc_throw(AddError, "Invalid NSEC3 owner name: " <<
                  rrset->getName() << "; zone: " << zone_name_);
    }
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
        const boost::scoped_ptr<NSEC3Hash> hash
            (NSEC3Hash::create(nsec3_data->hashalg,
                               nsec3_data->iterations,
                               nsec3_data->getSaltData(),
                               nsec3_data->getSaltLen()));

        if (!hash->match(nsec3_rdata)) {
            isc_throw(AddError,
                      rrset->getType() << " with inconsistent parameters: "
                      << rrset->toText());
        }
    }
}

void
ZoneDataUpdater::addNSEC3(const ConstRRsetPtr rrset, const ConstRRsetPtr rrsig)
{
    setupNSEC3<generic::NSEC3>(rrset);

    NSEC3Data* nsec3_data = zone_data_.getNSEC3Data();

    ZoneNode* node;
    nsec3_data->insertName(mem_sgmt_, rrset->getName(), &node);

    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, rrset, rrsig);
    RdataSet* old_rdataset = node->setData(rdataset);
    if (old_rdataset != NULL) {
        RdataSet::destroy(mem_sgmt_, rrclass_, old_rdataset);
    }
}

void
ZoneDataUpdater::addRdataSet(const ConstRRsetPtr rrset,
                             const ConstRRsetPtr rrsig)
{
    if (rrset->getType() == RRType::NSEC3()) {
        addNSEC3(rrset, rrsig);
    } else {
        ZoneNode* node;
        zone_data_.insertName(mem_sgmt_, rrset->getName(), &node);

        RdataSet* rdataset_head = node->getData();

        // Checks related to the surrounding data.  Note: when the check
        // fails and the exception is thrown, it may break strong
        // exception guarantee.  At the moment we prefer code simplicity
        // and don't bother to introduce complicated recovery code.
        contextCheck(*rrset, rdataset_head);

        if (RdataSet::find(rdataset_head, rrset->getType()) != NULL) {
            isc_throw(AddError,
                      "RRset of the type already exists: "
                      << rrset->getName() << " (type: "
                      << rrset->getType() << ")");
        }

        RdataSet* rdataset_new = RdataSet::create(mem_sgmt_, encoder_,
                                                  rrset, rrsig);

        // Insertion sort the new RdataSet into place in the list.
        RdataSet* prev = NULL;
        RdataSet* current = rdataset_head;
        for (; current != NULL; current = current->getNext())
        {
            if (compareTypes(rdataset_new, current) < 0) {
                break;
            }

            prev = current;
        }

        rdataset_new->next = current;
        if (prev != NULL) {
             prev->next = rdataset_new;
        } else {
             node->setData(rdataset_new);
        }

        // Ok, we just put it in.

        // If this RRset creates a zone cut at this node, mark the node
        // indicating the need for callback in find().
        if (rrset->getType() == RRType::NS() &&
            rrset->getName() != zone_name_) {
            node->setFlag(ZoneNode::FLAG_CALLBACK);
            // If it is DNAME, we have a callback as well here
        } else if (rrset->getType() == RRType::DNAME()) {
            node->setFlag(ZoneNode::FLAG_CALLBACK);
        }

        // If we've added NSEC3PARAM at zone origin, set up NSEC3
        // specific data or check consistency with already set up
        // parameters.
        if (rrset->getType() == RRType::NSEC3PARAM() &&
            rrset->getName() == zone_name_) {
            setupNSEC3<generic::NSEC3PARAM>(rrset);
        } else if (rrset->getType() == RRType::NSEC()) {
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
    // Validate input.  This will cause an exception to be thrown if the
    // input RRset is empty.
    validate(rrset);
    if (sig_rrset) {
        validate(sig_rrset);
    }

    // OK, can add the RRset.

    // Add wildcards possibly contained in the owner name to the domain
    // tree.  This can only happen for the normal (non-NSEC3) tree.
    // Note: this can throw an exception, breaking strong exception
    // guarantee.  (see also the note for the call to contextCheck()
    // above).
    if (rrset->getType() != RRType::NSEC3()) {
        addWildcards(rrset->getName());
    }

    addRdataSet(rrset, sig_rrset);
}

} // namespace memory
} // namespace datasrc
} // namespace isc
