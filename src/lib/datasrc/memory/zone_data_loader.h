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

#ifndef DATASRC_ZONE_DATA_LOADER_H
#define DATASRC_ZONE_DATA_LOADER_H 1

#include <datasrc/memory/zone_data.h>
#include <datasrc/iterator.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <util/memory_segment.h>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Zone is empty exception.
///
/// This is thrown if we have an empty zone created during
/// \c loadZoneData().
struct EmptyZone : public InvalidParameter {
    EmptyZone(const char* file, size_t line, const char* what) :
        InvalidParameter(file, line, what)
    {}
};

ZoneData* loadZoneData(util::MemorySegment& mem_sgmt,
		       const isc::dns::RRClass rrclass,
		       const isc::dns::Name& zone_name,
		       const std::string& zone_file);

ZoneData* loadZoneData(util::MemorySegment& mem_sgmt,
		       const isc::dns::RRClass rrclass,
		       const isc::dns::Name& zone_name,
		       ZoneIterator& iterator);

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_ZONE_DATA_LOADER_H

// Local Variables:
// mode: c++
// End:
