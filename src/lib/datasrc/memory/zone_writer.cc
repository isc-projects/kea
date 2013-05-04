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

#include <datasrc/memory/zone_writer.h>
#include <datasrc/memory/zone_data.h>

#include <memory>

using std::auto_ptr;

namespace isc {
namespace datasrc {
namespace memory {

ZoneWriter::ZoneWriter(ZoneTableSegment& segment,
                       const LoadAction& load_action,
                       const dns::Name& origin,
                       const dns::RRClass& rrclass) :
    segment_(segment),
    load_action_(load_action),
    origin_(origin),
    rrclass_(rrclass),
    zone_data_(NULL),
    state_(ZW_UNUSED)
{
    if (!segment.isWritable()) {
        isc_throw(isc::InvalidOperation,
                  "Attempt to construct ZoneWriter for a read-only segment");
    }
}

ZoneWriter::~ZoneWriter() {
    // Clean up everything there might be left if someone forgot, just
    // in case.
    cleanup();
}

void
ZoneWriter::load() {
    if (state_ != ZW_UNUSED) {
        isc_throw(isc::InvalidOperation, "Trying to load twice");
    }

    zone_data_ = load_action_(segment_.getMemorySegment());

    if (!zone_data_) {
        // Bug inside load_action_.
        isc_throw(isc::InvalidOperation, "No data returned from load action");
    }

    state_ = ZW_LOADED;
}

void
ZoneWriter::install() {
    if (state_ != ZW_LOADED) {
        isc_throw(isc::InvalidOperation, "No data to install");
    }

    ZoneTable* table(segment_.getHeader().getTable());
    if (!table) {
        isc_throw(isc::Unexpected, "No zone table present");
    }
    const ZoneTable::AddResult result(table->addZone(
                                          segment_.getMemorySegment(),
                                          rrclass_, origin_, zone_data_));

    state_ = ZW_INSTALLED;
    zone_data_ = result.zone_data;
}

void
ZoneWriter::cleanup() {
    // We eat the data (if any) now.

    if (zone_data_ != NULL) {
        ZoneData::destroy(segment_.getMemorySegment(), zone_data_, rrclass_);
        zone_data_ = NULL;
        state_ = ZW_CLEANED;
    }
}

}
}
}
