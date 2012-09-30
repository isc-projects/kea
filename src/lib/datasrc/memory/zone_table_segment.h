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

#ifndef __ZONE_TABLE_SEGMENT_H__
#define __ZONE_TABLE_SEGMENT_H__

#include <datasrc/memory/zone_table.h>
#include <cc/data.h>
#include <util/memory_segment.h>

#include <boost/interprocess/offset_ptr.hpp>

#include <stdlib.h>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Zone Table Header Class
struct ZoneTableHeader {
    boost::interprocess::offset_ptr<ZoneTable> table;
};

/// \brief Zone Table Segment Class
///
/// This class specifies an interface for derived implementations which
/// return a pointer to an object of type ZoneTableHeader, an entry
/// point of some memory image regardless of the underlying memory
/// management implementation.
class ZoneTableSegment {
public:
    /// \brief Destructor
    virtual ~ZoneTableSegment() {}

    /// \brief Return a ZoneTableHeader for the zone table segment.
    ///
    /// Returns a ZoneTableHeader that contains a pointer to the zone
    /// table data in memory.
    ///
    /// \return Returns a ZoneTableHeader for this zone table segment.
    virtual ZoneTableHeader* getHeader() = 0;

    /// \brief Return the MemorySegment for the zone table segment.
    ///
    /// Returns the MemorySegment used in this zone table segment.
    ///
    /// \return Returns a ZoneTableHeader for this zone table segment.
    virtual isc::util::MemorySegment& getMemorySegment() = 0;

    /// \brief Create a subclass depending on the memory segment model
    ///
    /// This is a factory method to create a derived ZoneTableSegment
    /// object based on the \c config passed.
    ///
    /// FIXME: For now, we always return ZoneTableSegmentLocal.
    ///
    /// \param config The configuration based on which a derived object
    ///               is returned.
    /// \return Returns a ZoneTableSegment object
    static ZoneTableSegment* create(const isc::data::Element& config);
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // __ZONE_TABLE_SEGMENT_H__
