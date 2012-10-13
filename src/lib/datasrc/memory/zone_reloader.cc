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

#include "zone_reloader.h"
#include "zone_data.h"
#include "zone_table_segment.h"

#include <memory>

using std::auto_ptr;

namespace isc {
namespace datasrc {
namespace memory {

ZoneReloaderLocal::ZoneReloaderLocal(ZoneTableSegment* segment,
                                     const LoadAction& load_action,
                                     const InstallAction& install_action,
                                     const dns::Name& origin,
                                     const dns::RRClass& rrclass) :
    segment_(segment),
    load_action_(load_action),
    install_action_(install_action),
    origin_(origin),
    rrclass_(rrclass),
    zone_data_(NULL),
    loaded_(false),
    data_ready_(false)
{}

ZoneReloaderLocal::~ZoneReloaderLocal() {
    // Clean up everything there might be left if someone forgot, just
    // in case. Or should we assert instead?
    cleanup();
}

void
ZoneReloaderLocal::load() {
    if (loaded_) {
        isc_throw(isc::Unexpected, "Trying to load twice");
    }
    loaded_ = true;

    zone_data_ = ZoneData::create(segment_->getMemorySegment(), origin_);

    load_action_(zone_data_);

    data_ready_ = true;
}

void
ZoneReloaderLocal::install() {
    if (!data_ready_) {
        isc_throw(isc::Unexpected, "No data to install");
    }

    data_ready_ = false;
    auto_ptr<ZoneSegment> zone_segment(new ZoneSegment(zone_data_));

    zone_data_ = install_action_(ZoneSegmentID(), zone_segment.get());

    // The ownership was passed to the callback, no need to clear it now.
    zone_segment.release();
}

void
ZoneReloaderLocal::cleanup() {
    // We eat the data (if any) now.
    data_ready_ = false;

    if (zone_data_ != NULL) {
        ZoneData::destroy(segment_->getMemorySegment(), zone_data_, rrclass_);
        zone_data_ = NULL;
    }
}

}
}
}
