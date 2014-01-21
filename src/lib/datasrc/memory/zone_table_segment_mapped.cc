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
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/segment_object_holder.h>

#include <memory>

using namespace isc::data;
using namespace isc::dns;
using namespace isc::util;
using isc::datasrc::memory::detail::SegmentObjectHolder;

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
    impl_type_("mapped"),
    rrclass_(rrclass)
{
}

ZoneTableSegmentMapped::~ZoneTableSegmentMapped() {
    sync();
}

const std::string&
ZoneTableSegmentMapped::getImplType() const {
    return (impl_type_);
}

bool
ZoneTableSegmentMapped::processChecksum(MemorySegmentMapped& segment,
                                        bool create, bool has_allocations,
                                        std::string& error_msg)
{
    const MemorySegment::NamedAddressResult result =
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
            size_t* checksum = static_cast<size_t*>(result.second);
            const size_t saved_checksum = *checksum;
            // First, clear the checksum so that getCheckSum() returns a
            // consistent value.
            *checksum = 0;
            const size_t new_checksum = segment.getCheckSum();
            if (saved_checksum != new_checksum) {
                error_msg = "Saved checksum doesn't match segment data";
                return (false);
            }
        }
    } else {
        if ((!create) && has_allocations) {
            // If we are resetting in READ_WRITE mode, and some memory
            // was already allocated but there is no checksum name, that
            // indicates that the segment is corrupted.
            error_msg = "Existing segment is missing a checksum name";
            return (false);
        }

        // Allocate space for a checksum (which is saved during close).
        void* checksum = NULL;
        while (!checksum) {
            try {
                checksum = segment.allocate(sizeof(size_t));
            } catch (const MemorySegmentGrown&) {
                // Do nothing and try again.
            }
        }
        *static_cast<size_t*>(checksum) = 0;
        segment.setNamedAddress(ZONE_TABLE_CHECKSUM_NAME, checksum);
    }

    return (true);
}

bool
ZoneTableSegmentMapped::processHeader(MemorySegmentMapped& segment,
                                      bool create, bool has_allocations,
                                      std::string& error_msg)
{
    const MemorySegment::NamedAddressResult result =
        segment.getNamedAddress(ZONE_TABLE_HEADER_NAME);
    if (result.first) {
        if (create) {
            // There must be no previously saved header.
            error_msg = "There is already a saved ZoneTableHeader in the "
                 "segment opened in create mode";
            return (false);
        } else {
            assert(result.second);
        }
    } else {
        if ((!create) && has_allocations) {
            // If we are resetting in READ_WRITE mode, and some memory
            // was already allocated but there is no header name, that
            // indicates that the segment is corrupted.
            error_msg = "Existing segment is missing a ZoneTableHeader name";
            return (false);
        }

        while (true) {
            try {
                SegmentObjectHolder<ZoneTable, int> zt_holder(segment, 0);
                zt_holder.set(ZoneTable::create(segment, rrclass_));
                void* ptr = segment.allocate(sizeof(ZoneTableHeader));
                ZoneTableHeader* new_header = new(ptr)
                    ZoneTableHeader(zt_holder.release());
                segment.setNamedAddress(ZONE_TABLE_HEADER_NAME, new_header);
                break;
            } catch (const MemorySegmentGrown&) {}
        }
    }

    return (true);
}

MemorySegmentMapped*
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

    // This flag is used inside processCheckSum() and processHeader(),
    // and must be initialized before we make any further allocations.
    const bool has_allocations = !segment->allMemoryDeallocated();

    std::string error_msg;
    if ((!processChecksum(*segment, create, has_allocations, error_msg)) ||
        (!processHeader(*segment, create, has_allocations, error_msg))) {
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

    return (segment.release());
}

MemorySegmentMapped*
ZoneTableSegmentMapped::openReadOnly(const std::string& filename) {
    // In case the checksum or table header is missing, we throw. We
    // want the segment to be automatically destroyed then.
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

    return (segment.release());
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
    } else {
        sync();
    }

    // In case current_filename_ below fails, we want the segment to be
    // automatically destroyed.
    std::auto_ptr<MemorySegmentMapped> segment;

    switch (mode) {
    case CREATE:
        segment.reset(openReadWrite(filename, true));
        break;

    case READ_WRITE:
        segment.reset(openReadWrite(filename, false));
        break;

    case READ_ONLY:
        segment.reset(openReadOnly(filename));
        break;

    default:
        isc_throw(isc::InvalidParameter,
                  "Invalid MemorySegmentOpenMode passed to reset()");
    }

    current_filename_ = filename;
    current_mode_ = mode;
    mem_sgmt_.reset(segment.release());

    if (!isWritable()) {
        // Given what we setup above, the following must not throw at
        // this point. If it does, all bets are off.
        cached_ro_header_ = getHeaderHelper<ZoneTableHeader>(true);
    }
}

void
ZoneTableSegmentMapped::sync() {
    // Synchronize checksum, etc.
    if (mem_sgmt_ && isWritable()) {
        // If there is a previously opened segment, and it was opened in
        // read-write mode, update its checksum.
        mem_sgmt_->shrinkToFit();
        const MemorySegment::NamedAddressResult result =
            mem_sgmt_->getNamedAddress(ZONE_TABLE_CHECKSUM_NAME);
        assert(result.first);
        assert(result.second);
        size_t* checksum = static_cast<size_t*>(result.second);
        // First, clear the checksum so that getCheckSum() returns a
        // consistent value.
        *checksum = 0;
        const size_t new_checksum = mem_sgmt_->getCheckSum();
        // Now, update it into place.
        *checksum = new_checksum;
    }
}

void
ZoneTableSegmentMapped::clear() {
    if (mem_sgmt_) {
        sync();
        mem_sgmt_.reset();
    }
}

template<typename T>
T*
ZoneTableSegmentMapped::getHeaderHelper(bool initial) const {
    if (!isUsable()) {
        isc_throw(isc::InvalidOperation,
                  "getHeader() called without calling reset() first");
    }

    if (!isWritable() && !initial) {
        // The header address would not have changed since reset() for
        // READ_ONLY segments.
        return (cached_ro_header_);
    }

    const MemorySegment::NamedAddressResult result =
        mem_sgmt_->getNamedAddress(ZONE_TABLE_HEADER_NAME);
    if (!result.first) {
        isc_throw(isc::Unexpected,
                  "Unable to look up the address of the table header in "
                  "getHeader()");
    }

    T* header = static_cast<ZoneTableHeader*>(result.second);
    assert(header);
    return (header);
}

ZoneTableHeader&
ZoneTableSegmentMapped::getHeader() {
    return (*getHeaderHelper<ZoneTableHeader>(false));
}

const ZoneTableHeader&
ZoneTableSegmentMapped::getHeader() const {
    return (*getHeaderHelper<const ZoneTableHeader>(false));
}

MemorySegment&
ZoneTableSegmentMapped::getMemorySegment() {
    if (!isUsable()) {
        isc_throw(isc::InvalidOperation,
                  "getMemorySegment() called without calling reset() first");
    }
    return (*mem_sgmt_);
}

bool
ZoneTableSegmentMapped::isUsable() const {
    // If mem_sgmt_ is not empty, then it is usable.
    return (mem_sgmt_);
}

bool
ZoneTableSegmentMapped::isWritable() const {
    if (!isUsable()) {
        // If reset() was never performed for this segment, or if the
        // most recent reset() had failed, or if the segment had been
        // cleared, then the segment is not writable.
        return (false);
    }

    return ((current_mode_ == CREATE) || (current_mode_ == READ_WRITE));
}

} // namespace memory
} // namespace datasrc
} // namespace isc
