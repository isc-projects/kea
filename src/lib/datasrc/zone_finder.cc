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

#include <datasrc/zone_finder.h>
#include <datasrc/exceptions.h>

#include <dns/rrclass.h>
#include <dns/rdata.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {

namespace {
// Identify zone's SOA and return its MINTTL in the form of RRTTL.
RRTTL
getMinTTL(ZoneFinder& finder, ConstRRsetPtr rrset) {
    ConstRRsetPtr soa_rrset;
    if (rrset->getType() == RRType::SOA()) {
        // Shortcut: if we are looking at SOA itself (which should be the
        // case in the expected scenario), we can simply use its RDATA.
        soa_rrset = rrset;
    } else {
        soa_rrset =
            finder.findAtOrigin(RRType::SOA(), false,
                                ZoneFinder::FIND_DEFAULT)->rrset;
    }

    // In a valid zone there is one and only one SOA RR at the origin.
    // Otherwise either zone data or the data source implementation is broken.
    if (!soa_rrset || soa_rrset->getRdataCount() != 1) {
        isc_throw(DataSourceError, "Zone " << rrset->getName().toText(true)
                  << "/" << rrset->getClass().toText() << " is broken: "
                  << (!soa_rrset ? "no SOA" : "empty SOA"));
    }

    return (RRTTL(dynamic_cast<const generic::SOA&>(
                      soa_rrset->getRdataIterator()->getCurrent()).
                  getMinimum()));
}

// Make a fresh copy of given RRset, just replacing RRTTL with the given one.
RRsetPtr
copyRRset(const AbstractRRset& rrset, const RRTTL& ttl) {
    RRsetPtr rrset_copy(new RRset(rrset.getName(), rrset.getClass(),
                                  rrset.getType(), ttl));
    for (RdataIteratorPtr rit = rrset.getRdataIterator();
         !rit->isLast();
         rit->next()) {
        rrset_copy->addRdata(rit->getCurrent());
    }

    ConstRRsetPtr rrsig = rrset.getRRsig();
    if (rrsig) {
        RRsetPtr rrsig_copy(new RRset(rrset.getName(), rrset.getClass(),
                                      RRType::RRSIG(), ttl));
        for (RdataIteratorPtr rit = rrsig->getRdataIterator();
             !rit->isLast();
             rit->next()) {
            rrsig_copy->addRdata(rit->getCurrent());
        }
        rrset_copy->addRRsig(rrsig_copy);
    }

    return (rrset_copy);
}
}

ZoneFinderContextPtr
ZoneFinder::findAtOrigin(const dns::RRType& type, bool use_minttl,
                         FindOptions options)
{
    ZoneFinderContextPtr context = find(getOrigin(), type, options);

    // If we are requested to use the min TTL and the RRset's RR TTL is larger
    // than that, we need to make a copy of the RRset, replacing the TTL,
    // and return a newly created context copying other parameters.
    if (use_minttl && context->rrset) {
        const AbstractRRset& rrset = *context->rrset;
        const RRTTL min_ttl = getMinTTL(*this, context->rrset);
        if (min_ttl < rrset.getTTL()) {
            FindResultFlags flags_copy = RESULT_DEFAULT;
            if (context->isWildcard()) {
                flags_copy = flags_copy | RESULT_WILDCARD;
            }
            if (context->isNSECSigned()) {
                flags_copy = flags_copy | RESULT_NSEC_SIGNED;
            } else if (context->isNSEC3Signed()) {
                flags_copy = flags_copy | RESULT_NSEC3_SIGNED;
            }

            return (ZoneFinderContextPtr(
                        new GenericContext(*this, options,
                                           ResultContext(context->code,
                                                         copyRRset(rrset,
                                                                   min_ttl),
                                                         flags_copy))));
        }
    }

    return (context);
}

isc::dns::ConstRRsetPtr
ZoneFinder::stripRRsigs(isc::dns::ConstRRsetPtr rp,
                        const FindOptions options) {
    if (rp) {
        isc::dns::ConstRRsetPtr sig_rrset = rp->getRRsig();
        if (sig_rrset &&
            ((options & ZoneFinder::FIND_DNSSEC) == 0)) {
            isc::dns::RRsetPtr result_base
                (new isc::dns::RRset(rp->getName(),
                                     rp->getClass(),
                                     rp->getType(),
                                     rp->getTTL()));
            for (isc::dns::RdataIteratorPtr i(rp->getRdataIterator());
                 !i->isLast();
                 i->next()) {
                result_base->addRdata(i->getCurrent());
            }

            return (result_base);
        }
    }

    return (rp);
}

} // namespace datasrc
} // datasrc isc
