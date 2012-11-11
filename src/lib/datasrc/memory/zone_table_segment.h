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

#ifndef ZONE_TABLE_SEGMENT_H
#define ZONE_TABLE_SEGMENT_H

#include <dns/rrclass.h>
#include <datasrc/memory/zone_table.h>
#include "load_action.h"
#include <cc/data.h>
#include <util/memory_segment.h>

#include <boost/interprocess/offset_ptr.hpp>

#include <stdlib.h>

namespace isc {
// Some forward declarations
namespace dns {
class Name;
class RRClass;
}
namespace datasrc {
namespace memory {
class ZoneWriter;

/// \brief Memory-management independent entry point that contains a
/// pointer to a zone table in memory.
///
/// An instance of this type lives inside a ZoneTableSegment
/// implementation. It contains an offset pointer to the zone table (a
/// map from domain names to zone locators) in memory.
struct ZoneTableHeader {
public:
    ZoneTableHeader(ZoneTable* zone_table) :
        table_(zone_table)
    {}

    /// \brief Returns a pointer to the underlying zone table.
    ZoneTable* getTable() {
        return (table_.get());
    }

    /// \brief const version of \c getTable().
    const ZoneTable* getTable() const {
        return (table_.get());
    }
private:
    boost::interprocess::offset_ptr<ZoneTable> table_;
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
    ZoneTableSegment(isc::dns::RRClass)
    {}
public:
    /// \brief Destructor
    virtual ~ZoneTableSegment() {}

    /// \brief Return the ZoneTableHeader for the zone table segment.
    virtual ZoneTableHeader& getHeader() = 0;

    /// \brief const version of \c getHeader().
    virtual const ZoneTableHeader& getHeader() const = 0;

    /// \brief Return the MemorySegment for the zone table segment.
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
    static ZoneTableSegment* create(const isc::data::Element& config,
                                    const isc::dns::RRClass& rrclass);

    /// \brief Temporary/Testing version of create.
    ///
    /// This exists as a temporary solution during the migration phase
    /// towards using the ZoneTableSegment. It doesn't take a config,
    /// but a memory segment instead. If you can, you should use the
    /// other version, this one will be gone soon.
    ///
    /// \param segment The memory segment to use.
    /// \return Returns a new ZoneTableSegment object.
    /// \todo Remove this method.
    static ZoneTableSegment* create(isc::util::MemorySegment& segment);

    /// \brief Destroy a ZoneTableSegment
    ///
    /// This method destroys the passed ZoneTableSegment. It must be
    /// passed a segment previously created by \c ZoneTableSegment::create().
    ///
    /// \param segment The segment to destroy.
    static void destroy(ZoneTableSegment* segment);

    /// \brief Create a zone write corresponding to this segment
    ///
    /// This creates a new write that can be used to update zones
    /// inside this zone table segment.
    ///
    /// \param loadAction Callback to provide the actual data.
    /// \param origin The origin of the zone to reload.
    /// \param rrclass The class of the zone to reload.
    /// \return New instance of a zone writer. The ownership is passed
    ///     onto the caller and the caller needs to \c delete it when
    ///     it's done with the writer.
    virtual ZoneWriter* getZoneWriter(const LoadAction& load_action,
                                      const dns::Name& origin,
                                      const dns::RRClass& rrclass) = 0;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // ZONE_TABLE_SEGMENT_H
