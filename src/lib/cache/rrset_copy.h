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

#ifndef RRSET_COPY
#define RRSET_COPY

#include <dns/rrset.h>

namespace isc {
namespace cache {

/// \brief RRset Copy Function
///
/// Adds all Rdatas and the RRsig in the source RRset to the target
/// RRset
///
/// \param src RRset to copy from
/// \param dst RRset to copy to
///
/// \note RRset class doesn't provide the interface for
///       doing RRset copy. But in cache's code, sometime
///       we have to do the copy.

void
rrsetCopy(const isc::dns::AbstractRRset& src, isc::dns::AbstractRRset& dst);

} // namespace cache
} // namespace isc

#endif // RRSET_COPY

