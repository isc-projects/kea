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

#ifndef __ZONE_TABLE_SEGMENT_LOCAL_H__
#define __ZONE_TABLE_SEGMENT_LOCAL_H__

#include <datasrc/memory/zone_table_segment.h>
#include <util/memory_segment_local.h>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Local implementation of ZoneTableSegment class
///
/// This class specifies a concrete implementation for a
/// MemorySegmentLocal based ZoneTableSegment. Please see the
/// ZoneTableSegment class documentation for usage.
class ZoneTableSegmentLocal : public ZoneTableSegment {
    // This is so that ZoneTableSegmentLocal can be instantiated from
    // ZoneTableSegment::create().
    friend class ZoneTableSegment;
protected:
    /// \brief Protected constructor
    ///
    /// Instances are expected to be created by the factory method
    /// (\c ZoneTableSegment::create()), so this constructor is
    /// protected.
    ZoneTableSegmentLocal()
    {}
public:
    /// \brief Destructor
    virtual ~ZoneTableSegmentLocal() {}

    /// \brief Return the ZoneTableHeader for the local zone table
    /// segment implementation.
    ///
    /// NOTE: This method will never return \c NULL.
    ///
    /// \return Returns the ZoneTableHeader for this zone table segment.
    virtual ZoneTableHeader* getHeader();

    /// \brief Return the MemorySegment for the local zone table segment
    /// implementation.
    ///
    /// \return Returns the MemorySegment for this zone table segment (a
    /// MemorySegmentLocal instance).
    virtual isc::util::MemorySegment& getMemorySegment();

private:
    ZoneTableHeader header_;
    isc::util::MemorySegmentLocal mem_sgmt_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // __ZONE_TABLE_SEGMENT_LOCAL_H__
