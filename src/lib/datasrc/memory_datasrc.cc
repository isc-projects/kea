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

#include <dns/name.h>
#include <datasrc/memory_datasrc.h>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {

/// Implementation details for \c MemoryDataSrc hidden from the public
/// interface.
///
/// For now, \c MemoryDataSrc only contains a \c ZoneTable object, which
/// consists of (pointers to) \c MemoryZone objects, we may add more
/// member variables later for new features.
class MemoryDataSrc::MemoryDataSrcImpl {
public:
    MemoryDataSrcImpl() : zone_count(0) {}
    unsigned int zone_count;
    ZoneTable zone_table;
};

MemoryDataSrc::MemoryDataSrc() : impl_(new MemoryDataSrcImpl)
{}

MemoryDataSrc::~MemoryDataSrc() {
    delete impl_;
}

unsigned int
MemoryDataSrc::getZoneCount() const {
    return (impl_->zone_count);
}

result::Result
MemoryDataSrc::addZone(ZonePtr zone) {
    if (!zone) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to MemoryDataSrc::addZone()");
    }

    const result::Result result = impl_->zone_table.addZone(zone);
    if (result == result::SUCCESS) {
        ++impl_->zone_count;
    }
    return (result);
}

MemoryDataSrc::FindResult
MemoryDataSrc::findZone(const isc::dns::Name& name) const {
    return (FindResult(impl_->zone_table.findZone(name).code,
                       impl_->zone_table.findZone(name).zone));
}
} // end of namespace datasrc
} // end of namespace dns
