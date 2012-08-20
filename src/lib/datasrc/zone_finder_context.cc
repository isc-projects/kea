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

#include <dns/rdata.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>

#include <datasrc/zone.h>

#include <boost/foreach.hpp>

#include <vector>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {

namespace {
void
getAdditionalAddrs(ZoneFinder& finder, const Name& name,
                   const vector<RRType>& requested_types,
                   vector<ConstRRsetPtr>& result_rrsets,
                   ZoneFinder::FindOptions options)
{
    // Ignore out-of-zone names
    const NameComparisonResult cmp = finder.getOrigin().compare(name);
    if ((cmp.getRelation() != NameComparisonResult::SUPERDOMAIN) &&
        (cmp.getRelation() != NameComparisonResult::EQUAL)) {
        return;
    }

    BOOST_FOREACH(RRType rrtype, requested_types) {
        ConstZoneFinderContextPtr ctx = finder.find(name, rrtype, options);
        if (ctx->code == ZoneFinder::SUCCESS) {
            ConstRRsetPtr rr = ctx->rrset;
            ConstRRsetPtr sig_rrset = rr->getRRsig();
            if (sig_rrset &&
                ((options & ZoneFinder::FIND_DNSSEC) == 0)) {
                RRsetPtr result_base(new RRset(rr->getName(),
                                               rr->getClass(),
                                               rr->getType(),
                                               rr->getTTL()));
                for (RdataIteratorPtr i(rr->getRdataIterator());
                     !i->isLast();
                     i->next()) {
                    result_base->addRdata(i->getCurrent());
                }

                result_rrsets.push_back(result_base);
            } else {
                result_rrsets.push_back(rr);
            }
        }
    }
}

void
getAdditionalForRRset(ZoneFinder& finder, const AbstractRRset& rrset,
                      const vector<RRType>& requested_types,
                      vector<ConstRRsetPtr>& result,
                      ZoneFinder::FindOptions orig_options)
{
    RdataIteratorPtr rdata_iterator(rrset.getRdataIterator());
    ZoneFinder::FindOptions options = ZoneFinder::FIND_DEFAULT;
    if ((orig_options & ZoneFinder::FIND_DNSSEC) != 0) {
        options = options | ZoneFinder::FIND_DNSSEC;
    }

    for (; !rdata_iterator->isLast(); rdata_iterator->next()) {
        const Rdata& rdata(rdata_iterator->getCurrent());

        if (rrset.getType() == RRType::NS()) {
            // Need to perform the search in the "GLUE OK" mode.
            const generic::NS& ns = dynamic_cast<const generic::NS&>(rdata);
            getAdditionalAddrs(finder, ns.getNSName(), requested_types,
                               result, options | ZoneFinder::FIND_GLUE_OK);
        } else if (rrset.getType() == RRType::MX()) {
            const generic::MX& mx = dynamic_cast<const generic::MX&>(rdata);
            getAdditionalAddrs(finder, mx.getMXName(), requested_types,
                               result, options);
        }
    }
}
}

void
ZoneFinder::Context::getAdditionalImpl(const vector<RRType>& requested_types,
                                       vector<ConstRRsetPtr>& result)
{
    // If rrset is non NULL, it should have been SUCCESS/DELEGATION; otherwise
    // we should have responded to type ANY query.
    if (rrset) {
        getAdditionalForRRset(finder_, *rrset, requested_types, result,
                              options_);
        return;
    }
    BOOST_FOREACH(ConstRRsetPtr rrset_in_set, all_set_) {
        getAdditionalForRRset(finder_, *rrset_in_set, requested_types, result,
                              options_);
    }
}

} // namespace datasrc
} // datasrc isc
