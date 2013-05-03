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

#include <datasrc/memory/zone_table_segment_local.h>

using namespace isc::dns;
using namespace isc::util;

namespace isc {
namespace datasrc {
namespace memory {

ZoneTableSegmentLocal::ZoneTableSegmentLocal(const RRClass& rrclass) :
    ZoneTableSegment(rrclass),
    header_(ZoneTable::create(mem_sgmt_, rrclass))
{
}

ZoneTableSegmentLocal::~ZoneTableSegmentLocal() {
    // Explicitly clear the contained data, and check memory
    // leak.  assert() (with abort on failure) may be too harsh, but
    // it's probably better to find more leaks initially.  Once it's stabilized
    // we should probably revisit it.

    ZoneTable::destroy(mem_sgmt_, header_.getTable());
    assert(mem_sgmt_.allMemoryDeallocated());
}

void
ZoneTableSegmentLocal::reset(MemorySegmentOpenMode,
                             isc::data::ConstElementPtr)
{
    isc_throw(isc::NotImplemented,
              "ZoneTableSegmentLocal::reset() is not implemented and "
              "should not be used.");
}

// After more methods' definitions are added here, it would be a good
// idea to move getHeader() and getMemorySegment() definitions to the
// header file.
ZoneTableHeader&
ZoneTableSegmentLocal::getHeader() {
     return (header_);
}

const ZoneTableHeader&
ZoneTableSegmentLocal::getHeader() const {
     return (header_);
}

MemorySegment&
ZoneTableSegmentLocal::getMemorySegment() {
     return (mem_sgmt_);
}

} // namespace memory
} // namespace datasrc
} // namespace isc
