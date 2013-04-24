// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_MEMORY_TEST_ZONE_LOADER_UTIL_H
#define DATASRC_MEMORY_TEST_ZONE_LOADER_UTIL_H 1

#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_data_loader.h>

#include <dns/dns_fwd.h>

#include <string>

namespace isc {
namespace datasrc {
namespace memory {
namespace test {

/// \brief A shortcut utility to load a specified zone into ZoneTableSegment
/// from a file.
///
/// This function does nothing special, simply provides a shortcut for commonly
/// used pattern that would be used in tests with a ZoneTableSegment loading
/// a zone from file into it.
void
loadZoneIntoTable(ZoneTableSegment& zt_sgmt, const dns::Name& zname,
                  const dns::RRClass& zclass, const std::string& zone_file);

/// \brief A shortcut utility to load a specified zone into ZoneTableSegment
/// from a zone iterator.
///
/// This is similar to the other version, but use a zone iterator as the
/// source of the zone data.
void
loadZoneIntoTable(ZoneTableSegment& zt_sgmt, const dns::Name& zname,
                  const dns::RRClass& zclass, ZoneIterator& iterator);
} // namespace test
} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_TEST_ZONE_LOADER_UTIL_H

// Local Variables:
// mode: c++
// End:
