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

/// \brief Exception thrown when unknown or unsupported type of
/// ZoneTableSegment is asked to be created.
class UnknownSegmentType : public Exception {
public:
    UnknownSegmentType(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

/// \brief Exception thrown when a \c reset() on a \c ZoneTableSegment
/// fails (due to various reasons). When this exception is thrown, a
/// strong exception safety guarantee is provided, and the
/// \c ZoneTableSegment is usable as before.
class ResetFailed : public isc::Exception {
public:
    ResetFailed(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// \brief Exception thrown when a \c reset() on a \c ZoneTableSegment
/// fails (due to various reasons), and it was not able to preserve the
/// state of the \c ZoneTableSegment. When this exception is thrown,
/// only basic exception safety guarantee is provided and the
/// \c ZoneTableSegment must be expected as cleared.
class ResetFailedAndSegmentCleared : public isc::Exception {
public:
    ResetFailedAndSegmentCleared(const char* file, size_t line,
                                 const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// \brief Memory-management independent entry point that contains a
/// pointer to a zone table in memory.
///
/// An instance of this type lives inside a \c ZoneTableSegment
/// implementation. It contains an offset pointer to the \c ZoneTable (a
/// map from domain names to zone locators) in the \c ZoneTableSegment.
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

/// \brief Manages a \c ZoneTableHeader, an entry point into a table of
/// zones
///
/// This class specifies an interface for derived implementations which
/// return a pointer to an object of type \c ZoneTableHeader, an entry
/// point into a table of zones regardless of the underlying memory
/// management implementation. Derived classes implement the interface
/// for the specific memory-implementation behavior.
///
/// Note: At some point in the future, methods such as \c reset(),
/// \c clear(), \c resetHeader(), \c getHeader(), \c isWritable(),
/// \c isUsable() may become non-virtual methods. Such a change should
/// not affect any code that uses this class, but please be aware of
/// such plans.
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

    /// \brief Return a string name for the \c ZoneTableSegment
    /// implementation.
    ///
    /// Implementations of this method should ensure that the returned
    /// string is identical to the corresponding string passed to
    /// \c ZoneTableSegment::create() for that implementation.
    ///
    /// \throw None This method's implementations must be
    /// exception-free.
    virtual const std::string& getImplType() const = 0;

    /// \brief Return the \c ZoneTableHeader for the zone table segment.
    ///
    /// As long as \c isUsable() returns true, this method must always
    /// succeed without throwing an exception.  If \c isUsable() returns
    /// false, a derived class implementation can throw
    /// \c isc::InvalidOperation depending on its implementation
    /// details. Applications are generally expected to call this
    /// method only when \c isUsable() returns true (either by making
    /// sure explicitly or by some other indirect means).
    ///
    /// \throw isc::InvalidOperation may be thrown by some
    /// implementations if this method is called without calling
    /// \c reset() successfully first.
    virtual ZoneTableHeader& getHeader() = 0;

    /// \brief \c const version of \c getHeader().
    ///
    /// See the non- \c const version for documentation.
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

    /// \brief Create an instance depending on the requested memory
    /// segment implementation type.
    ///
    /// This is a factory method to create a derived \c ZoneTableSegment
    /// object based on the \c config passed. The method returns a
    /// dynamically-allocated object. The caller is responsible for
    /// destroying it with \c ZoneTableSegment::destroy().
    ///
    /// \throw UnknownSegmentType The memory segment type specified in
    /// \c config is not known or not supported in this implementation.
    ///
    /// \param rrclass The RR class of the zones to be maintained in the table.
    /// \param type The memory segment type to be used.
    /// \return Returns a \c ZoneTableSegment object of the specified type.
    static ZoneTableSegment* create(const isc::dns::RRClass& rrclass,
                                    const std::string& type);

    /// \brief Destroy a \c ZoneTableSegment
    ///
    /// This method destroys the passed \c ZoneTableSegment. It must be
    /// passed a segment previously created by
    /// \c ZoneTableSegment::create().
    ///
    /// \param segment The segment to destroy.
    static void destroy(ZoneTableSegment* segment);

    /// \brief The mode using which to create a MemorySegment.
    ///
    /// Here, a \c MemorySegment (see its class documentation) is an
    /// interface to a storage area, and provides operations to allocate
    /// and deallocate from that storage area, and also to look up
    /// addresses in that area. The storage area can be a buffer in
    /// memory, a file on disk, or some kind of shared memory depending
    /// on the \c MemorySegment implementation being used.  In every
    /// case in the documentation below, when we mention \c
    /// MemorySegment, we mean both the \c MemorySegment object which
    /// interfaces to the storage area and the contents of the
    /// associated storage area.
    ///
    /// - CREATE: If the \c MemorySegment's storage area doesn't exist,
    ///           create it. If it exists, overwrite it with a new
    ///           storage area (which does not remember old data). In
    ///           both cases, create a \c MemorySegment for it in
    ///           read+write mode.
    ///
    /// - READ_WRITE: If the \c MemorySegment's storage area doesn't
    ///               exist, create it. If it exists, use the existing
    ///               storage area as-is (keeping the existing data
    ///               intact). In both cases, create a \c MemorySegment
    ///               for it in read+write mode.
    ///
    /// - READ_ONLY: If the \c MemorySegment's storage area doesn't
    ///              exist, throw an exception. If it exists, create a
    ///              \c MemorySegment for it in read-only mode.
    enum MemorySegmentOpenMode {
        CREATE,
        READ_WRITE,
        READ_ONLY
    };

    /// \brief Close the current \c MemorySegment (if open) and open the
    /// requested one.
    ///
    /// When we talk about "opening" a \c MemorySegment, it means to
    /// construct a usable \c MemorySegment object that interfaces to
    /// the actual memory storage area. "Closing" is the opposite
    /// operation of opening.
    ///
    /// In case opening the new \c MemorySegment fails for some reason,
    /// one of the following documented (further below) exceptions may
    /// be thrown. In case failures occur, implementations of this
    /// method must strictly provide the associated behavior as follows
    /// and in the exception documentation below.  Code that uses
    /// \c ZoneTableSegment would depend on such assurances.
    ///
    /// First, in case a \c ZoneTableSegment was reset successfully
    /// before and is currently usable (\c isUsable() returns true), and
    /// an invalid configuration is passed in \c params to \c reset(),
    /// the isc::InvalidParameter exception must be thrown. In this
    /// case, a strong exception safety guarantee must be provided, and
    /// the \c ZoneTableSegment must be usable as before.
    ///
    /// In case a \c ZoneTableSegment was reset successfully before and
    /// is currently usable (\c isUsable() returns true), and the attempt
    /// to reset to a different \c MemorySegment storage area fails,
    /// the \c ResetFailed exception must be thrown. In this
    /// case, a strong exception safety guarantee must be provided, and
    /// the \c ZoneTableSegment must be usable as before.
    ///
    /// In case a \c ZoneTableSegment was reset successfully before and
    /// is currently usable (\c isUsable() returns true), and the attempt
    /// to reset to the same \c MemorySegment storage area fails, the
    /// \c ResetFailedAndSegmentCleared exception must be thrown. In
    /// this case, only basic exception safety guarantee is provided and
    /// the \c ZoneTableSegment must be expected as cleared.
    ///
    /// In case a \c ZoneTableSegment was not reset successfully before
    /// and is currently not usable (\c isUsable() returns false), and
    /// the attempt to reset fails, the \c ResetFailed exception must be
    /// thrown. In this unique case, a strong exception safety guarantee
    /// is provided by default, as the \c ZoneTableSegment was clear
    /// previously, and remains cleared.
    ///
    /// In all other cases, \c ZoneTableSegment contents can be expected
    /// as reset.
    ///
    /// See \c MemorySegmentOpenMode for a definition of "storage area"
    /// and the various modes in which a \c MemorySegment can be opened.
    ///
    /// \c params should contain an implementation-defined
    /// configuration. See the specific \c ZoneTableSegment
    /// implementation class for details of what to pass in this
    /// argument.
    ///
    /// \throw isc::InvalidParameter if the configuration in \c params
    /// has incorrect syntax, but there is a strong exception safety
    /// guarantee and the \c ZoneTableSegment is usable or unusable as
    /// before.
    ///
    /// \throw ResetFailed if there was a problem in opening the new
    /// memory store, but there is a strong exception safety guarantee
    /// and the \c ZoneTableSegment is usable or unusable as before.
    ///
    /// \throw ResetFailedAndSegmentCleared if there was a problem in
    /// opening the new memory store, but there is only a basic
    /// exception safety guarantee and the \c ZoneTableSegment is not
    /// usable without a further successful \c reset().
    ///
    /// \throw isc::NotImplemented Some implementations may choose to
    /// not implement this method. In this case, there must be a strong
    /// exception safety guarantee and the \c ZoneTableSegment is usable
    /// or unusable as before.
    ///
    /// \param mode The open mode (see the MemorySegmentOpenMode
    /// documentation).
    /// \param params An element containing implementation-specific
    /// config (see the description).
    virtual void reset(MemorySegmentOpenMode mode,
                       isc::data::ConstElementPtr params) = 0;

    /// \brief Close the currently configured \c MemorySegment (if
    /// open).
    ///
    /// See the \c reset() method's documentation for a definition of
    /// "open" and "close".
    ///
    /// Implementations of this method should close any currently
    /// configured \c MemorySegment and clear the `ZoneTableSegment` to
    /// a freshly constructed state.
    ///
    /// \throw isc::NotImplemented Some implementations may choose to
    /// not implement this method. In this case, there must be a strong
    /// exception safety guarantee and the \c ZoneTableSegment is usable
    /// or unusable as before.
    virtual void clear() = 0;

    /// \brief Return true if the \c ZoneTableSegment has been
    /// successfully \c reset().
    ///
    /// Note that after calling \c clear(), this method will return
    /// false until the segment is reset successfully again.
    virtual bool isUsable() const = 0;

    /// \brief Reset the table header address.
    ///
    /// This method must recalculate the \c ZoneTableHeader address, so
    /// that it is valid when requested using the \c getHeader() method.
    virtual void resetHeader() = 0;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // ZONE_TABLE_SEGMENT_H

// Local Variables:
// mode: c++
// End:
