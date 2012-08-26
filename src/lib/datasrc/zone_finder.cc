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

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {

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
