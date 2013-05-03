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

#include <exceptions/exceptions.h>

#include <dns/rrclass.h>

#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/load_action.h>

#include <cc/data.h>
#include <util/memory_segment.h>

#include <boost/interprocess/offset_ptr.hpp>

#include <cstdlib>
#include <string>

namespace isc {
// Some forward declarations
namespace dns {
class Name;
class RRClass;
}
namespace datasrc {
namespace memory {
class ZoneWriter;

/// \brief Exception thrown when unknown or unsupported type of zone table
/// segment is specified.
class UnknownSegmentType : public Exception {
public:
    UnknownSegmentType(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

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
    ZoneTableSegment(const isc::dns::RRClass&)
    {}
public:
    /// \brief Destructor
    virtual ~ZoneTableSegment() {}

    /// \brief Return the ZoneTableHeader for the zone table segment.
    ///
    /// \throw isc::InvalidOperation may be thrown by some
    /// implementations if this method is called without calling
    /// \c reset() successfully first.
    virtual ZoneTableHeader& getHeader() = 0;

    /// \brief const version of \c getHeader().
    ///
    /// \throw isc::InvalidOperation may be thrown by some
    /// implementations if this method is called without calling
    /// \c reset() successfully first.
    virtual const ZoneTableHeader& getHeader() const = 0;

    /// \brief Return the MemorySegment for the zone table segment.
    ///
    /// \throw isc::InvalidOperation may be thrown by some
    /// implementations if this method is called without calling
    /// \c reset() successfully first.
    virtual isc::util::MemorySegment& getMemorySegment() = 0;

    /// \brief Return true if the segment is writable.
    ///
    /// The user of the zone table segment will load or update zones
    /// into the segment only for writable ones.  The precise definition
    /// of "writability" differs in different derived classes (see
    /// derived class documentation).  In general, however, the user
    /// should only rely on this interface rather than assume a specific
    /// definition for a specific type of segment.
    ///
    /// \throw None This method's implementations must be
    /// exception-free.
    virtual bool isWritable() const = 0;

    /// \brief Create an instance depending on the memory segment model
    ///
    /// This is a factory method to create a derived ZoneTableSegment
    /// object based on the \c config passed. The method returns a
    /// dynamically-allocated object. The caller is responsible for
    /// destroying it with \c ZoneTableSegment::destroy().
    ///
    /// \throw UnknownSegmentType The memory segment type specified in
    /// \c config is not known or not supported in this implementation.
    ///
    /// \param rrclass The RR class of the zones to be maintained in the table.
    /// \param type The memory segment type used for the zone table segment.
    /// \return Returns a ZoneTableSegment object of the specified type.
    static ZoneTableSegment* create(const isc::dns::RRClass& rrclass,
                                    const std::string& type);

    /// \brief Destroy a ZoneTableSegment
    ///
    /// This method destroys the passed ZoneTableSegment. It must be
    /// passed a segment previously created by \c ZoneTableSegment::create().
    ///
    /// \param segment The segment to destroy.
    static void destroy(ZoneTableSegment* segment);

    /// \brief The mode using which to open a ZoneTableSegment.
    ///
    /// - CREATE: If the backing memory store doesn't exist, create
    ///           it. If it exists, overwrite it with a newly created
    ///           memory store. In both cases, open the newly created
    ///           memory store in read+write mode.
    ///
    /// - READ_WRITE: If the backing memory store doesn't exist, create
    ///               it. If it exists, use the existing memory store
    ///               as-is. In both cases, open the memory store in
    ///               read+write mode.
    ///
    /// - READ_ONLY: If the backing memory store doesn't exist, throw an
    ///              exception. If it exists, open the existing memory
    ///              store in read-only mode.
    enum MemorySegmentOpenMode {
        CREATE,
        READ_WRITE,
        READ_ONLY
    };

    /// \brief Unload the current memory store (if loaded) and load the
    /// specified one.
    ///
    /// See the \c MemorySegmentOpenMode documentation above for the
    /// various modes in which a ZoneTableSegment can be created.
    ///
    /// \c params should contain an implementation-defined
    /// configuration. See the specific \c ZoneTableSegment
    /// implementation class for details of what to pass in this
    /// argument.
    ///
    /// \throws isc::InvalidParameter if the configuration in \c params
    /// has incorrect syntax.
    /// \throws isc::Unexpected for a variety of cases where an
    /// unexpected condition occurs. These should not occur normally in
    /// correctly written code.
    ///
    /// \param mode The open mode (see the MemorySegmentOpenMode
    /// documentation).
    /// \param params An element containing implementation-specific
    /// config (see the description).
    virtual void reset(MemorySegmentOpenMode mode,
                       isc::data::ConstElementPtr params) = 0;

    /// \brief Unload the current memory store (if loaded).
    ///
    /// Implementations of this method should unload any current memory
    /// store and reset the `ZoneTableSegment` to a freshly constructed
    /// state.
    ///
    /// \throw none
    virtual void clear() = 0;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // ZONE_TABLE_SEGMENT_H

// Local Variables:
// mode: c++
// End:
