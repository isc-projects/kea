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
#include <string>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Mapped-file based implementation of \c ZoneTableSegment class
///
/// This class specifies a concrete implementation for a memory-mapped
/// \c ZoneTableSegment. Please see the \c ZoneTableSegment class
/// documentation for usage.
class ZoneTableSegmentMapped : public ZoneTableSegment {
    // This is so that \c ZoneTableSegmentMapped can be instantiated
    // from \c ZoneTableSegment::create().
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

    /// \brief Returns "mapped" as the implementation type.
    virtual const std::string& getImplType() const;

    /// \brief Resets the \c ZoneTableHeader address from the named
    /// address in the mapped file. This method should be called once
    /// before calls to \c getHeader() if the mapped \c MemorySegment
    /// has grown.
    virtual void resetHeader();

    /// \brief Return the \c ZoneTableHeader for this mapped zone table
    /// segment.
    ///
    /// \throws isc::InvalidOperation if this method is called without a
    /// successful \c reset() call first.
    virtual ZoneTableHeader& getHeader();

    /// \brief const version of \c getHeader().
    virtual const ZoneTableHeader& getHeader() const;

    /// \brief Return the \c MemorySegment for the memory-mapped zone
    /// table segment implementation (a \c MemorySegmentMapped
    /// instance).
    ///
    /// \throws isc::InvalidOperation if this method is called without a
    /// successful \c reset() call first.
    virtual isc::util::MemorySegment& getMemorySegment();

    /// \brief Returns if the segment is writable.
    ///
    /// Segments successfully opened in CREATE or READ_WRITE modes are
    /// writable. Segments opened in READ_ONLY mode are not writable.
    /// If the \c ZoneTableSegment was cleared for some reason, it is
    /// not writable until it is reset successfully.
    virtual bool isWritable() const;

    /// \brief Close the current \c MemorySegment (if open) and open the
    /// requested one.
    ///
    /// See \c MemorySegmentOpenMode for a definition of "storage area"
    /// and the various modes in which a \c MemorySegment can be opened.
    ///
    /// \c params should be a map containing a "mapped-file" key that
    /// points to a string value containing the filename of a mapped
    /// file. E.g.,
    ///
    ///  {"mapped-file": "/var/bind10/mapped-files/zone-sqlite3.mapped.0"}
    ///
    /// Please see the \c ZoneTableSegment API documentation for the
    /// behavior in case of exceptions.
    ///
    /// \throws isc::Unexpected when it's unable to lookup a named
    /// address that it expected to be present. This is extremely
    /// unlikely, and it points to corruption.
    ///
    /// \param mode The open mode (see the \c MemorySegmentOpenMode
    /// documentation in \c ZoneTableSegment class).
    /// \param params An element containing config for the mapped file
    /// (see the description).
    virtual void reset(MemorySegmentOpenMode mode,
                       isc::data::ConstElementPtr params);

    /// \brief Close the currently configured \c MemorySegment (if
    /// open). See the base class for a definition of "open" and
    /// "close".
    virtual void clear();

    /// \brief Return true if the segment is usable.
    ///
    /// See the base class for the description.
    virtual bool isUsable() const;

private:
    void sync();

    bool processChecksum(isc::util::MemorySegmentMapped& segment, bool create,
                         bool has_allocations, std::string& error_msg);
    bool processHeader(isc::util::MemorySegmentMapped& segment, bool create,
                       bool has_allocations, std::string& error_msg);

    isc::util::MemorySegmentMapped* openReadWrite(const std::string& filename,
                                                  bool create);
    isc::util::MemorySegmentMapped* openReadOnly(const std::string& filename);

    template<typename T> T* getHeaderHelper() const;

private:
    std::string impl_type_;
    isc::dns::RRClass rrclass_;
    MemorySegmentOpenMode current_mode_;
    std::string current_filename_;
    // Internally holds a MemorySegmentMapped. This is NULL on
    // construction, and is set by the \c reset() method.
    boost::scoped_ptr<isc::util::MemorySegmentMapped> mem_sgmt_;
    ZoneTableHeader* cached_header_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // ZONE_TABLE_SEGMENT_MAPPED_H
