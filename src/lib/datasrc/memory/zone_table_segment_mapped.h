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

#ifndef ZONE_TABLE_SEGMENT_MAPPED_H
#define ZONE_TABLE_SEGMENT_MAPPED_H

#include <datasrc/memory/zone_table_segment.h>
#include <util/memory_segment_mapped.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Mapped-file based implementation of ZoneTableSegment class
///
/// This class specifies a concrete implementation for a memory-mapped
/// ZoneTableSegment. Please see the ZoneTableSegment class
/// documentation for usage.
class ZoneTableSegmentMapped : public ZoneTableSegment {
    // This is so that ZoneTableSegmentMapped can be instantiated from
    // ZoneTableSegment::create().
    friend class ZoneTableSegment;
protected:
    /// \brief Protected constructor
    ///
    /// Instances are expected to be created by the factory method
    /// (\c ZoneTableSegment::create()), so this constructor is
    /// protected.
    ZoneTableSegmentMapped(const isc::dns::RRClass& rrclass);
public:
    /// \brief Destructor
    virtual ~ZoneTableSegmentMapped();

    /// \brief Return the ZoneTableHeader for the mapped zone table
    /// segment implementation.
    ///
    /// \throws isc::Unexpected if this method is called without a
    /// successful \c reset() call first.
    virtual ZoneTableHeader& getHeader();

    /// \brief const version of \c getHeader().
    ///
    /// \throws isc::Unexpected if this method is called without a
    /// successful \c reset() call first.
    virtual const ZoneTableHeader& getHeader() const;

    /// \brief Return the MemorySegment for the memory-mapped zone table
    /// segment implementation (a MemorySegmentMapped instance).
    ///
    /// \throws isc::Unexpected if this method is called without a
    /// successful \c reset() call first.
    virtual isc::util::MemorySegment& getMemorySegment();

    /// \brief Return true if the segment is writable. For read-only
    /// segments, false is returned.
    ///
    /// \throws isc::Unexpected if this method is called without a
    /// successful \c reset() call first.
    virtual bool isWritable() const;

    /// \brief The mode using which to open a ZoneTableSegment around a
    /// mapped file.
    ///
    /// - CREATE: If the mapped file doesn't exist, create it. If it
    ///           exists, overwrite it with a newly created mapped
    ///           file. In both cases, open the newly created mapped
    ///           file in read+write mode.
    ///
    /// - READ_WRITE: If the mapped file doesn't exist, create it. If it
    ///               exists, use the existing mapped file. In both
    ///               cases, open the mapped file in read+write mode.
    ///
    /// - READ_ONLY: If the mapped file doesn't exist, throw an
    ///              exception. If it exists, open the existing mapped
    ///              file in read-only mode.
    enum MemorySegmentOpenMode {
        CREATE,
        READ_WRITE,
        READ_ONLY
    };

    /// \brief Unmap the current file (if mapped) and map the specified
    /// one.
    ///
    /// See the \c MemorySegmentOpenMode documentation above for the
    /// various modes in which a ZoneTableSegment can be created.
    ///
    /// \c params should be a map containing a "mapped-file" key that
    /// points to a string value containing the filename of a mapped
    /// file. E.g.,
    ///
    ///  {"mapped-file": "/var/bind10/mapped-files/zone-sqlite3.mapped.0"}
    ///
    /// \throws isc::InvalidParameter if the configuration in \c params
    /// has incorrect syntax.
    /// \throws isc::Unexpected for a variety of cases where an
    /// unexpected condition occurs. These should not occur normally in
    /// correctly written code.
    ///
    /// \param mode The open mode (see the MemorySegmentOpenMode
    /// documentation).
    /// \param params An element containing config for the mapped file
    /// (see the description).
    virtual void reset(MemorySegmentOpenMode mode,
                       isc::data::ConstElementPtr params);

private:
    // Internally holds a MemorySegmentMapped. This is NULL on
    // construction, and is set by the \c reset() method.
    isc::dns::RRClass rrclass_;
    MemorySegmentOpenMode current_mode_;
    boost::scoped_ptr<isc::util::MemorySegmentMapped> mem_sgmt_;
    ZoneTableHeader* header_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // ZONE_TABLE_SEGMENT_MAPPED_H
