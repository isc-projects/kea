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

// $Id$

#include <vector>

#include <boost/foreach.hpp>

#include <exceptions/exceptions.h>

#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrsetlist.h>

namespace isc {
namespace dns {

void
RRsetList::addRRset(RRsetPtr rrsetptr) {
    ConstRRsetPtr rrset_found = findRRset(rrsetptr->getType(),
                                          rrsetptr->getClass());
    if (rrset_found != NULL) {
        isc_throw(DuplicateRRset, "RRset is being doubly added to RRsetList: "
                  "type=" << rrsetptr->getType() << ", class=" <<
                  rrsetptr->getClass());
    }
    rrsets_.push_back(rrsetptr);
}

void
RRsetList::append(RRsetList& source)
{
    BOOST_FOREACH(RRsetPtr rrset, source) {
        addRRset(rrset);
    }
}

RRsetPtr
RRsetList::findRRset(const RRType& rrtype, const RRClass& rrclass) {
    BOOST_FOREACH(RRsetPtr rrsetptr, rrsets_) {
        if ((rrsetptr->getClass() == rrclass) &&
            (rrsetptr->getType() == rrtype)) {
            return (rrsetptr);
        }
    }
    return (RRsetPtr());
}

}
}
