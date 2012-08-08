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

#ifndef DATASRC_MEMORY_ZONE_DATA_H
#define DATASRC_MEMORY_ZONE_DATA_H 1

#include <dns/name.h>
#include <dns/rrclass.h>

namespace isc {
namespace datasrc {
namespace memory {
class ZoneData {
private:
    ZoneData(const dns::Name& zone_name) :
        zone_name_(zone_name)
    {}
public:
    static ZoneData* create(util::MemorySegment& mem_sgmt,
                            const dns::Name& zone_name)
    {
        void* p = mem_sgmt.allocate(sizeof(ZoneData));
        ZoneData* zone_data = new(p) ZoneData(zone_name);
        return (zone_data);
    }
    static void destroy(util::MemorySegment& mem_sgmt, ZoneData* zone_data) {
        zone_data->~ZoneData();
        mem_sgmt.deallocate(zone_data, sizeof(ZoneData));
    }

private:
    const dns::Name zone_name_;
};
} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_ZONE_DATA_H

// Local Variables:
// mode: c++
// End:
