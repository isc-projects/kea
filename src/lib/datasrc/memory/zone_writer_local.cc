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

#include "zone_writer_local.h"
#include "zone_data.h"
#include "zone_table_segment.h"

#include <memory>

using std::auto_ptr;

namespace isc {
namespace datasrc {
namespace memory {

ZoneWriterLocal::ZoneWriterLocal(ZoneTableSegment* segment,
                                 const LoadAction& load_action,
                                 const dns::Name& origin,
                                 const dns::RRClass& rrclass) :
    segment_(segment),
    load_action_(load_action),
    origin_(origin),
    rrclass_(rrclass),
    zone_data_(NULL),
    loaded_(false),
    data_ready_(false)
{}

ZoneWriterLocal::~ZoneWriterLocal() {
    // Clean up everything there might be left if someone forgot, just
    // in case. Or should we assert instead?
    cleanup();
}

void
ZoneWriterLocal::load() {
    if (loaded_) {
        isc_throw(isc::Unexpected, "Trying to load twice");
    }

    zone_data_ = load_action_(segment_->getMemorySegment());

    if (zone_data_ == NULL) {
        // Bug inside load_action_.
        isc_throw(isc::Unexpected, "No data returned from load action");
    }

    loaded_ = true;
    data_ready_ = true;
}

void
ZoneWriterLocal::install() {
    if (!data_ready_) {
        isc_throw(isc::Unexpected, "No data to install");
    }


    ZoneTable* table(segment_->getHeader().getTable());
    if (table == NULL) {
        isc_throw(isc::Unexpected, "No zone table present");
    }
    ZoneTable::AddResult result(table->addZone(segment_->getMemorySegment(),
                                               rrclass_, origin_, zone_data_));

    data_ready_ = false;
    zone_data_ = result.zone_data;
}

void
ZoneWriterLocal::cleanup() {
    // We eat the data (if any) now.

    if (zone_data_ != NULL) {
        ZoneData::destroy(segment_->getMemorySegment(), zone_data_, rrclass_);
        zone_data_ = NULL;
        data_ready_ = false;
    }
}

}
}
}
