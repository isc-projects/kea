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

#include <datasrc/memory/zone_table_segment_mapped.h>

#include <memory>

using namespace isc::data;
using namespace isc::dns;
using namespace isc::util;

namespace isc {
namespace datasrc {
namespace memory {

ZoneTableSegmentMapped::ZoneTableSegmentMapped(const RRClass& rrclass) :
    ZoneTableSegment(rrclass),
    rrclass_(rrclass),
    header_(NULL)
{
}

void
ZoneTableSegmentMapped::reset(MemorySegmentOpenMode mode,
                              isc::data::ConstElementPtr params)
{
    if (mem_sgmt_) {
        if (isWritable()) {
            // If there is a previously opened segment, and it was
            // opened in read-write mode, update its checksum.
            mem_sgmt_->shrinkToFit();
            const MemorySegment::NamedAddressResult result =
                mem_sgmt_->getNamedAddress("zone_table_checksum");
            assert(result.first);
            assert(result.second);
            uint32_t* checksum = static_cast<uint32_t*>(result.second);
            // First, clear the checksum so that getCheckSum() returns
            // a consistent value.
            *checksum = 0;
            const uint32_t new_checksum = mem_sgmt_->getCheckSum();
            // Now, update it into place.
            *checksum = new_checksum;
        }
        // Close the segment here in case the code further below
        // doesn't complete successfully.
        header_ = NULL;
        mem_sgmt_.reset();
    }

    if (!params || params->getType() != Element::map) {
        isc_throw(isc::InvalidParameter,
                  "Configuration does not contain a map");
    }

    if (!params->contains("mapped-file")) {
        isc_throw(isc::InvalidParameter,
                  "Configuration does not contain a \"mapped-file\" key");
    }

    ConstElementPtr mapped_file = params->get("mapped-file");
    if ((!mapped_file) || (mapped_file->getType() != Element::string)) {
        isc_throw(isc::InvalidParameter,
                  "Value of \"mapped-file\" is not a string");
    }

    const std::string filename = mapped_file->stringValue();

    // In case there is a checksum mismatch, we throw. We want the
    // segment to be automatically destroyed then.
    std::auto_ptr<MemorySegmentMapped> segment;

    switch (mode) {
    case CREATE: {
        segment.reset(new MemorySegmentMapped
                      (filename,
                       MemorySegmentMapped::CREATE_ONLY));
        // There must be no previously saved checksum.
        MemorySegment::NamedAddressResult result =
            segment->getNamedAddress("zone_table_checksum");
        if (result.first) {
            isc_throw(isc::Unexpected,
                      "There is already a saved checksum in a mapped segment "
                      "opened in create mode.");
        }
        // Allocate space for a checksum (which is saved during close).
        void* checksum = segment->allocate(sizeof(uint32_t));
        *static_cast<uint32_t*>(checksum) = 0;
        segment->setNamedAddress("zone_table_checksum", checksum);

        // There must be no previously saved ZoneTableHeader.
        result = segment->getNamedAddress("zone_table_header");
        if (result.first) {
            isc_throw(isc::Unexpected,
                      "There is already a saved ZoneTableHeader in a "
                      "mapped segment opened in create mode.");
        }
        void* ptr = segment->allocate(sizeof(ZoneTableHeader));
        ZoneTableHeader* new_header = new(ptr)
             ZoneTableHeader(ZoneTable::create(*segment, rrclass_));
        segment->setNamedAddress("zone_table_header", new_header);
        header_ = new_header;

        break;
    }
    case READ_WRITE: {
        segment.reset(new MemorySegmentMapped
                      (filename, MemorySegmentMapped::OPEN_OR_CREATE));
        // If there is a previously saved checksum, verify that it is
        // consistent. Otherwise, allocate space for a checksum (which
        // is saved during close).
        MemorySegment::NamedAddressResult result =
            segment->getNamedAddress("zone_table_checksum");
        if (result.first) {
            // The segment was already shrunk when it was last
            // closed. Check that its checksum is consistent.
            assert(result.second);
            uint32_t* checksum = static_cast<uint32_t*>(result.second);
            const uint32_t saved_checksum = *checksum;
            // First, clear the checksum so that getCheckSum() returns
            // a consistent value.
            *checksum = 0;
            const uint32_t new_checksum = segment->getCheckSum();
            if (saved_checksum != new_checksum) {
                 isc_throw(isc::Unexpected,
                           "Saved checksum doesn't match mapped segment data");
            }
        } else {
            void* checksum = segment->allocate(sizeof(uint32_t));
            *static_cast<uint32_t*>(checksum) = 0;
            segment->setNamedAddress("zone_table_checksum", checksum);
        }

        // If there is a previously saved ZoneTableHeader, use
        // it. Otherwise, allocate a new header.
        result = segment->getNamedAddress("zone_table_header");
        if (result.first) {
            assert(result.second);
            header_ = static_cast<ZoneTableHeader*>(result.second);
        } else {
            void* ptr = segment->allocate(sizeof(ZoneTableHeader));
            ZoneTableHeader* new_header = new(ptr)
                ZoneTableHeader(ZoneTable::create(*segment, rrclass_));
            segment->setNamedAddress("zone_table_header", new_header);
            header_ = new_header;
        }

        break;
    }
    case READ_ONLY: {
        segment.reset(new MemorySegmentMapped(filename));
        // There must be a previously saved checksum.
        MemorySegment::NamedAddressResult result =
            segment->getNamedAddress("zone_table_checksum");
        if (!result.first) {
            isc_throw(isc::Unexpected,
                      "There is no previously saved checksum in a "
                      "mapped segment opened in read-only mode.");
        }

        // We can't verify the checksum here as we can't set the
        // checksum to 0 for checksum calculation in a read-only
        // segment. So we continue without verifying the checksum.

        // There must be a previously saved ZoneTableHeader.
        result = segment->getNamedAddress("zone_table_header");
        if (result.first) {
            assert(result.second);
            header_ = static_cast<ZoneTableHeader*>(result.second);
        } else {
            isc_throw(isc::Unexpected,
                      "There is no previously saved ZoneTableHeader in a "
                      "mapped segment opened in read-only mode.");
        }
    }
    }

    current_mode_ = mode;
    mem_sgmt_.reset(segment.release());
}

// After more methods' definitions are added here, it would be a good
// idea to move getHeader() and getMemorySegment() definitions to the
// header file.
ZoneTableHeader&
ZoneTableSegmentMapped::getHeader() {
    if (!mem_sgmt_) {
        isc_throw(isc::Unexpected,
                  "getHeader() called without calling reset() first");
    }
    return (*header_);
}

const ZoneTableHeader&
ZoneTableSegmentMapped::getHeader() const {
    if (!mem_sgmt_) {
        isc_throw(isc::Unexpected,
                  "getHeader() called without calling reset() first");
    }
    return (*header_);
}

MemorySegment&
ZoneTableSegmentMapped::getMemorySegment() {
    if (!mem_sgmt_) {
        isc_throw(isc::Unexpected,
                  "getMemorySegment() called without calling reset() first");
    }
    return (*mem_sgmt_);
}

bool
ZoneTableSegmentMapped::isWritable() const {
    if (!mem_sgmt_) {
        // If reset() was never performed for this segment, or if the
        // most recent reset() had failed, then the segment is not
        // writable.
        return (false);
    }

    return ((current_mode_ == CREATE) || (current_mode_ == READ_WRITE));
}

} // namespace memory
} // namespace datasrc
} // namespace isc
