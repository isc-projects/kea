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

#ifndef DATASRC_MEMORY_UTIL_INTERNAL_H
#define DATASRC_MEMORY_UTIL_INTERNAL_H 1

#include <dns/rdataclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

namespace isc {
namespace datasrc {
namespace memory {
namespace detail {

/// \brief Return the covered RR type of an RRSIG RRset.
///
/// This is a commonly used helper to extract the type covered field of an
/// RRSIG RRset and return it in the form of an RRType object.
///
/// Normally, an empty RRSIG shouldn't be passed to this function, whether
/// it comes from a master file or another data source iterator, but it could
/// still happen in some buggy situations.  This function catches and rejects
/// such cases.
inline dns::RRType
getCoveredType(const dns::ConstRRsetPtr& sig_rrset) {
    dns::RdataIteratorPtr it = sig_rrset->getRdataIterator();
    if (it->isLast()) {
        isc_throw(isc::Unexpected,
                  "Empty RRset is passed in-memory loader, name: "
                  << sig_rrset->getName());
    }
    return (dynamic_cast<const dns::rdata::generic::RRSIG&>(it->getCurrent()).
            typeCovered());
}

} // namespace detail
} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_UTIL_INTERNAL_H

// Local Variables:
// mode: c++
// End:
