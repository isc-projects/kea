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

/// \brief Memory-management independent entry point that contains a
/// pointer to a zone table in memory.
///
/// An instance of this type lives inside a ZoneTableSegment
/// implementation. It contains an offset pointer to the zone table (a
/// map from domain names to zone locators) in memory.
struct ZoneTableHeader {
public:
    /// \brief Returns a pointer to the underlying zone table.
    ZoneTable* getTable() {
        return (table.get());
    }

    /// \brief const version of \c getTable().
    const ZoneTable* getTable() const {
        return (table.get());
    }

private:
    boost::interprocess::offset_ptr<ZoneTable> table;
};

/// \brief Manages a ZoneTableHeader, an entry point into a table of
/// zones
///
/// This class specifies an interface for derived implementations which
/// return a pointer to an object of type ZoneTableHeader, an entry
/// point into a table of zones regardless of the underlying memory
/// management implementation. Derived classes would implement the
/// interface for specific memory-implementation behavior.
class ZoneTableSegment {
protected:
    /// \brief Protected constructor
    ///
    /// An instance implementing this interface is expected to be
    /// created by the factory method (\c create()), so this constructor
    /// is protected.
    ZoneTableSegment()
    {}
public:
    /// \brief Destructor
    virtual ~ZoneTableSegment() {}

    /// \brief Return the ZoneTableHeader for the zone table segment.
    ///
    /// NOTE: This method should never return \c NULL.
    ///
    /// \return Returns the ZoneTableHeader for this zone table segment.
    virtual ZoneTableHeader* getHeader() = 0;

    /// \brief const version of \c getHeader().
    ///
    /// NOTE: This method should never return \c NULL.
    ///
    /// \return Returns the ZoneTableHeader for this zone table segment.
    virtual const ZoneTableHeader* getHeader() const = 0;

    /// \brief Return the MemorySegment for the zone table segment.
    ///
    /// \return Returns the ZoneTableHeader for this zone table segment.
    virtual isc::util::MemorySegment& getMemorySegment() = 0;

    /// \brief Create an instance depending on the memory segment model
    ///
    /// This is a factory method to create a derived ZoneTableSegment
    /// object based on the \c config passed. The method returns a
    /// dynamically-allocated object. The caller is responsible for
    /// destroying it with \c ZoneTableSegment::destroy().
    ///
    /// FIXME: For now, we always return ZoneTableSegmentLocal
    /// regardless of the passed \c config.
    ///
    /// \param config The configuration based on which a derived object
    ///               is returned.
    /// \return Returns a ZoneTableSegment object
    static ZoneTableSegment* create(const isc::data::Element& config);

    /// \brief Destroy a ZoneTableSegment
    ///
    /// This method destroys the passed ZoneTableSegment. It must be
    /// passed a segment previously created by \c
    /// ZoneTableSegment::create().
    ///
    /// \param segment The segment to destroy.
    static void destroy(ZoneTableSegment* segment);
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // __ZONE_TABLE_SEGMENT_H__
