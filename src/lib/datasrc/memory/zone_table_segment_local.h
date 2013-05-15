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

#ifndef ZONE_TABLE_SEGMENT_LOCAL_H
#define ZONE_TABLE_SEGMENT_LOCAL_H

#include <datasrc/memory/zone_table_segment.h>
#include <util/memory_segment_local.h>

#include <string>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Local implementation of \c ZoneTableSegment class
///
/// This class specifies a concrete implementation for a
/// \c MemorySegmentLocal -based \c ZoneTableSegment. Please see the
/// \c ZoneTableSegment class documentation for usage.
class ZoneTableSegmentLocal : public ZoneTableSegment {
    // This is so that \c ZoneTableSegmentLocal can be instantiated from
    // \c ZoneTableSegment::create().
    friend class ZoneTableSegment;

protected:
    /// \brief Protected constructor
    ///
    /// Instances are expected to be created by the factory method
    /// (\c ZoneTableSegment::create()), so this constructor is
    /// protected.
    ZoneTableSegmentLocal(const isc::dns::RRClass& rrclass);

public:
    /// \brief Destructor
    virtual ~ZoneTableSegmentLocal();

    /// \brief Returns "local" as the implementation type.
    virtual const std::string& getImplType() const;

    /// \brief This method does not have to do anything in this
    /// implementation. It has an empty definition.
    virtual void resetHeader();

    /// \brief Return the \c ZoneTableHeader for this local zone table
    /// segment.
    virtual ZoneTableHeader& getHeader();

    /// \brief \c const version of \c getHeader().
    virtual const ZoneTableHeader& getHeader() const;

    /// \brief Return the \c MemorySegment for the local zone table
    /// segment implementation (a \c MemorySegmentLocal instance).
    virtual isc::util::MemorySegment& getMemorySegment();

    /// \brief Return true if the segment is writable.
    ///
    /// Local segments are always writable. This implementation always
    /// returns true.
    virtual bool isWritable() const {
        return (true);
    }

    /// \brief This method is not implemented.
    ///
    /// Resetting a local \c ZoneTableSegment is not supported at this
    /// time.
    ///
    /// \throw isc::NotImplemented
    virtual void reset(MemorySegmentOpenMode mode,
                       isc::data::ConstElementPtr params);

    /// \brief This method is not implemented.
    ///
    /// Clearing a local \c ZoneTableSegment is not supported at this
    /// time.
    ///
    /// \throw isc::NotImplemented
    virtual void clear();

    /// \brief Return true if the segment is usable.
    ///
    /// Local segments are always usable. This implementation always
    /// returns true.
    virtual bool isUsable() const {
        return (true);
    }

private:
    std::string impl_type_;
    isc::util::MemorySegmentLocal mem_sgmt_;
    ZoneTableHeader header_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // ZONE_TABLE_SEGMENT_LOCAL_H
