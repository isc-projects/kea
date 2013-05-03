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

namespace { // unnamed namespace

// The name with which the zone table checksum is associated in the segment.
const char* const ZONE_TABLE_CHECKSUM_NAME = "zone_table_checksum";

// The name with which the zone table header is associated in the segment.
const char* const ZONE_TABLE_HEADER_NAME = "zone_table_header";

} // end of unnamed namespace

ZoneTableSegmentMapped::ZoneTableSegmentMapped(const RRClass& rrclass) :
    ZoneTableSegment(rrclass),
    rrclass_(rrclass),
    header_(NULL)
{
}

bool
ZoneTableSegmentMapped::processChecksum(MemorySegmentMapped& segment,
                                        bool create,
                                        std::string& error_msg)
{
    MemorySegment::NamedAddressResult result =
        segment.getNamedAddress(ZONE_TABLE_CHECKSUM_NAME);
    if (result.first) {
        if (create) {
            // There must be no previously saved checksum.
            error_msg = "There is already a saved checksum in the segment "
                 "opened in create mode";
            return (false);
        } else {
            // The segment was already shrunk when it was last
            // closed. Check that its checksum is consistent.
            assert(result.second);
            uint32_t* checksum = static_cast<uint32_t*>(result.second);
            const uint32_t saved_checksum = *checksum;
            // First, clear the checksum so that getCheckSum() returns a
            // consistent value.
            *checksum = 0;
            const uint32_t new_checksum = segment.getCheckSum();
            if (saved_checksum != new_checksum) {
                error_msg = "Saved checksum doesn't match segment data";
                return (false);
            }
        }
    } else {
        // Allocate space for a checksum (which is saved during close).

        // First allocate a ZONE_TABLE_CHECKSUM_NAME, so that we can set
        // it without growing the segment (and changing the checksum's
        // address).
        segment.setNamedAddress(ZONE_TABLE_CHECKSUM_NAME, NULL);
        void* checksum = NULL;
        while (!checksum) {
            try {
                checksum = segment.allocate(sizeof(uint32_t));
            } catch (const MemorySegmentGrown&) {
                // Do nothing and try again.
            }
        }
        *static_cast<uint32_t*>(checksum) = 0;
        const bool grew = segment.setNamedAddress(ZONE_TABLE_CHECKSUM_NAME,
                                                  checksum);
        if (grew) {
            // If the segment grew here, we have a problem as the
            // checksum address may no longer be valid. In this case, we
            // cannot recover. This case is extremely unlikely as we
            // reserved memory for the ZONE_TABLE_CHECKSUM_NAME
            // above. It indicates a very restrictive MemorySegment
            // which we should not use.
            error_msg = "Segment grew unexpectedly in setNamedAddress()";
            return (false);
        }
    }

    return (true);
}

bool
ZoneTableSegmentMapped::processHeader(MemorySegmentMapped& segment,
                                      bool create,
                                      std::string& error_msg)
{
    MemorySegment::NamedAddressResult result =
        segment.getNamedAddress(ZONE_TABLE_HEADER_NAME);
    if (result.first) {
        if (create) {
            // There must be no previously saved checksum.
            error_msg = "There is already a saved ZoneTableHeader in the "
                 "segment opened in create mode";
            return (false);
        } else {
            assert(result.second);
            header_ = static_cast<ZoneTableHeader*>(result.second);
        }
    } else {
        segment.setNamedAddress(ZONE_TABLE_HEADER_NAME, NULL);
        void* ptr = NULL;
        while (!ptr) {
            try {
                ptr = segment.allocate(sizeof(ZoneTableHeader));
            } catch (const MemorySegmentGrown&) {
                // Do nothing and try again.
            }
        }
        ZoneTableHeader* new_header = new(ptr)
            ZoneTableHeader(ZoneTable::create(segment, rrclass_));
        const bool grew = segment.setNamedAddress(ZONE_TABLE_HEADER_NAME,
                                                  new_header);
        if (grew) {
            // If the segment grew here, we have a problem as the table
            // header address may no longer be valid. In this case, we
            // cannot recover. This case is extremely unlikely as we
            // reserved memory for the ZONE_TABLE_HEADER_NAME above. It
            // indicates a very restrictive MemorySegment which we
            // should not use.
            error_msg = "Segment grew unexpectedly in setNamedAddress()";
            return (false);
        }
        header_ = new_header;
    }

    return (true);
}

void
ZoneTableSegmentMapped::openReadWrite(const std::string& filename,
                                      bool create)
{
    const MemorySegmentMapped::OpenMode mode = create ?
         MemorySegmentMapped::CREATE_ONLY :
         MemorySegmentMapped::OPEN_OR_CREATE;
    // In case there is a problem, we throw. We want the segment to be
    // automatically destroyed then.
    std::auto_ptr<MemorySegmentMapped> segment
        (new MemorySegmentMapped(filename, mode));

    std::string error_msg;
    if (!processChecksum(*segment, create, error_msg)) {
         if (mem_sgmt_) {
              isc_throw(ResetFailed,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         } else {
              isc_throw(ResetFailedAndSegmentCleared,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         }
    }

    if (!processHeader(*segment, create, error_msg)) {
         if (mem_sgmt_) {
              isc_throw(ResetFailed,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         } else {
              isc_throw(ResetFailedAndSegmentCleared,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         }
    }

    mem_sgmt_.reset(segment.release());
}

void
ZoneTableSegmentMapped::openReadOnly(const std::string& filename) {
    // In case there is a checksum mismatch, we throw. We want the
    // segment to be automatically destroyed then.
    std::auto_ptr<MemorySegmentMapped> segment
        (new MemorySegmentMapped(filename));
    // There must be a previously saved checksum.
    MemorySegment::NamedAddressResult result =
        segment->getNamedAddress(ZONE_TABLE_CHECKSUM_NAME);
    if (!result.first) {
         const std::string error_msg =
             "There is no previously saved checksum in a "
             "mapped segment opened in read-only mode";
         if (mem_sgmt_) {
              isc_throw(ResetFailed,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         } else {
              isc_throw(ResetFailedAndSegmentCleared,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         }
    }

    // We can't verify the checksum here as we can't set the checksum to
    // 0 for checksum calculation in a read-only segment. So we continue
    // without verifying the checksum.

    // There must be a previously saved ZoneTableHeader.
    result = segment->getNamedAddress(ZONE_TABLE_HEADER_NAME);
    if (result.first) {
        assert(result.second);
        header_ = static_cast<ZoneTableHeader*>(result.second);
    } else {
         const std::string error_msg =
             "There is no previously saved ZoneTableHeader in a "
             "mapped segment opened in read-only mode.";
         if (mem_sgmt_) {
              isc_throw(ResetFailed,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         } else {
              isc_throw(ResetFailedAndSegmentCleared,
                        "Error in resetting zone table segment to use "
                        << filename << ": " << error_msg);
         }
    }

    mem_sgmt_.reset(segment.release());
}

void
ZoneTableSegmentMapped::reset(MemorySegmentOpenMode mode,
                              isc::data::ConstElementPtr params)
{
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

    if (mem_sgmt_ && (filename == current_filename_)) {
        // This reset() is an attempt to re-open the currently open
        // mapped file. We cannot do this in many mode combinations
        // unless we close the existing mapped file. So just close it.
        clear();
    }

    switch (mode) {
    case CREATE:
        openReadWrite(filename, true);
        break;

    case READ_WRITE:
        openReadWrite(filename, false);
        break;

    case READ_ONLY:
        openReadOnly(filename);
    }

    current_mode_ = mode;
    current_filename_ = filename;
}

void
ZoneTableSegmentMapped::clear()
{
    if (mem_sgmt_) {
        if (isWritable()) {
            // If there is a previously opened segment, and it was
            // opened in read-write mode, update its checksum.
            mem_sgmt_->shrinkToFit();
            const MemorySegment::NamedAddressResult result =
                mem_sgmt_->getNamedAddress(ZONE_TABLE_CHECKSUM_NAME);
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
}

// After more methods' definitions are added here, it would be a good
// idea to move getHeader() and getMemorySegment() definitions to the
// header file.
ZoneTableHeader&
ZoneTableSegmentMapped::getHeader() {
    if (!mem_sgmt_) {
        isc_throw(isc::InvalidOperation,
                  "getHeader() called without calling reset() first");
    }
    return (*header_);
}

const ZoneTableHeader&
ZoneTableSegmentMapped::getHeader() const {
    if (!mem_sgmt_) {
        isc_throw(isc::InvalidOperation,
                  "getHeader() called without calling reset() first");
    }
    return (*header_);
}

MemorySegment&
ZoneTableSegmentMapped::getMemorySegment() {
    if (!mem_sgmt_) {
        isc_throw(isc::InvalidOperation,
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
