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

#include <datasrc/exceptions.h>
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
/// This is thrown if an empty zone would be created during
/// \c loadZoneData().
struct EmptyZone : public ZoneLoaderException {
    EmptyZone(const char* file, size_t line, const char* what) :
        ZoneLoaderException(file, line, what)
    {}
};

/// \brief Create and return a ZoneData instance populated from the
/// \c zone_file.
///
/// Throws \c ZoneDataUpdater::AddError if invalid or inconsistent data
/// is present in the \c zone_file. Throws \c isc::Unexpected if empty
/// RRsets are passed by the master loader. Throws \c EmptyZone if an
/// empty zone would be created due to the \c loadZoneData().
///
/// \param mem_sgmt The memory segment.
/// \param rrclass The RRClass.
/// \param zone_name The name of the zone that is being loaded.
/// \param zone_file Filename which contains the zone data for \c zone_name.
ZoneData* loadZoneData(util::MemorySegment& mem_sgmt,
                       const isc::dns::RRClass& rrclass,
                       const isc::dns::Name& zone_name,
                       const std::string& zone_file);

/// \brief Create and return a ZoneData instance populated from the
/// \c iterator.
///
/// Throws \c ZoneDataUpdater::AddError if invalid or inconsistent data
/// is present in the \c zone_file. Throws \c isc::Unexpected if empty
/// RRsets are passed by the zone iterator. Throws \c EmptyZone if an
/// empty zone would be created due to the \c loadZoneData().
///
/// \param mem_sgmt The memory segment.
/// \param rrclass The RRClass.
/// \param zone_name The name of the zone that is being loaded.
/// \param iterator Iterator that returns RRsets to load into the zone.
ZoneData* loadZoneData(util::MemorySegment& mem_sgmt,
                       const isc::dns::RRClass& rrclass,
                       const isc::dns::Name& zone_name,
                       ZoneIterator& iterator);

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_ZONE_DATA_LOADER_H

// Local Variables:
// mode: c++
// End:
