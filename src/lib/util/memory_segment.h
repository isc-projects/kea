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

#ifndef MEMORY_SEGMENT_H
#define MEMORY_SEGMENT_H

#include <exceptions/exceptions.h>

#include <stdlib.h>

namespace isc {
namespace util {

/// \brief Exception that can be thrown on constructing a MemorySegment
/// object.
class MemorySegmentOpenError : public Exception {
public:
    MemorySegmentOpenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief Exception that is thrown when allocating a space in a MemorySegment
/// results in growing the underlying segment.
///
/// See MemorySegment::allocate() for details.
class MemorySegmentGrown : public Exception {
public:
    MemorySegmentGrown(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief General error that can be thrown by a MemorySegment
/// implementation.
class MemorySegmentError : public Exception {
public:
    MemorySegmentError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief Memory Segment Class
///
/// This class specifies an interface for allocating memory
/// segments. This is an abstract class and a real
/// implementation such as MemorySegmentLocal should be used
/// in code.
///
/// It's intended to provide a unified interface whether the underlying
/// memory is local to a specific process or is sharable by multiple
/// processes.
class MemorySegment {
public:
    /// \brief Destructor
    virtual ~MemorySegment() {}

    /// \brief Allocate/acquire a segment of memory.
    ///
    /// The source of the memory is dependent on the implementation used.
    ///
    /// Depending on the implementation details, it may have to grow the
    /// internal memory segment (again, in an implementation dependent way)
    /// to allocate the required size of memory.  In that case the
    /// implementation must grow the internal segment sufficiently so the
    /// next call to allocate() for the same size will succeed and throw
    /// an \c MemorySegmentGrown exception (not really allocating the memory
    /// yet).
    ///
    /// An application that uses this memory segment abstraction to allocate
    /// memory should expect this exception, and should normally catch it
    /// at an appropriate layer (which may be immediately after a call to
    /// \c allocate() or a bit higher layer).  It should interpret the
    /// exception as any raw address that belongs to the segment may have
    /// been remapped and must be re-fetched via an already established
    /// named address using the \c getNamedAddress() method.
    ///
    /// \throw std::bad_alloc The implementation cannot allocate the
    /// requested storage.
    /// \throw MemorySegmentGrown The memory segment doesn't have sufficient
    /// space for the requested size and has grown internally.
    ///
    /// \param size The size of the memory requested in bytes.
    /// \return Returns pointer to the memory allocated.
    virtual void* allocate(size_t size) = 0;

    /// \brief Free/release a segment of memory.
    ///
    /// This method may throw <code>isc::OutOfRange</code> if \c size is
    /// not equal to the originally allocated size. \c size could be
    /// used by some implementations such as a slice allocator, where
    /// freeing memory also requires the size to be specified. We also
    /// use this argument in some implementations to test if all allocated
    /// memory was deallocated properly.
    ///
    /// \param ptr Pointer to the block of memory to free/release. This
    /// should be equal to a value returned by <code>allocate()</code>.
    /// \param size The size of the memory to be freed in bytes. This
    /// should be equal to the number of bytes originally allocated.
    virtual void deallocate(void* ptr, size_t size) = 0;

    /// \brief Check if all allocated memory was deallocated.
    ///
    /// \return Returns <code>true</code> if all allocated memory (including
    /// names associated by memory addresses by \c setNamedAddress()) was
    /// deallocated, <code>false</code> otherwise.
    virtual bool allMemoryDeallocated() const = 0;

    /// \brief Associate specified address in the segment with a given name.
    ///
    /// This method establishes an association between the given name and
    /// the address in an implementation specific way.  The stored address
    /// is retrieved by the name later by calling \c getNamedAddress().
    /// If the underlying memory segment is sharable by multiple processes,
    /// the implementation must ensure the portability of the association;
    /// if a process gives an address in the shared segment a name, another
    /// process that shares the same segment should be able to retrieve the
    /// corresponding address by that name (in such cases the real address
    /// may be different between these two processes).
    ///
    /// \c addr must be 0 (NULL) or an address that belongs to this segment.
    /// The latter case means it must be the return value of a previous call
    /// to \c allocate().  The actual implementation is encouraged to detect
    /// violation of this restriction and signal it with an exception, but
    /// it's not an API requirement.  It's generally the caller's
    /// responsibility to meet the restriction.
    ///
    /// There can be an existing association for the name; in that case the
    /// association will be overridden with the newly given address.
    ///
    /// While normally unexpected, it's possible that available space in the
    /// segment is not sufficient to allocate a space (if not already exist)
    /// for the specified name in the segment.  In that case, if possible, the
    /// implementation should try to grow the internal segment and retry
    /// establishing the association.  The implementation should throw
    /// std::bad_alloc if even reasonable attempts of retry still fail.
    ///
    /// This method should normally return false, but if the internal segment
    /// had to grow to store the given name, it must return true.  The
    /// application should interpret it just like the case of
    /// \c MemorySegmentGrown exception thrown from the \c allocate() method.
    ///
    /// \throw std::bad_alloc Allocation of a segment space for the given name
    /// failed.
    ///
    /// \param name A C string to be associated with \c addr.
    /// \param addr A memory address returned by a prior call to \c allocate.
    /// \return true if the internal segment has grown to allocate space for
    /// the name; false otherwise (see above).
    virtual bool setNamedAddress(const char* name, void* addr) = 0;

    /// \brief Return the address in the segment that has the given name.
    ///
    /// This method returns the memory address in the segment corresponding
    /// to the specified \c name.  The name and address must have been
    /// associated by a prior call to \c setNameAddress().  If no address
    /// associated with the given name is found, it returns NULL.
    ///
    /// This method should generally be considered exception free, but there
    /// can be a small chance it throws, depending on the internal
    /// implementation (e.g., if it converts the name to std::string), so the
    /// API doesn't guarantee that property.  In general, if this method
    /// throws it should be considered a fatal condition.
    ///
    /// \param name A C string of which the segment memory address is to be
    /// returned.
    /// \return The address associated with the name, or NULL if not found.
    virtual void* getNamedAddress(const char* name) = 0;

    /// \brief Delete a name previously associated with a segment address.
    ///
    /// This method deletes the association of the given \c name to
    /// a corresponding segment address previously established by
    /// \c setNamedAddress().  If there is no association for the given name
    /// this method returns false; otherwise it returns true.
    ///
    /// See \c getNamedAddress() about exception consideration.
    ///
    /// \param name A C string of which the segment memory address is to be
    /// deleted.
    virtual bool clearNamedAddress(const char* name) = 0;
};

} // namespace util
} // namespace isc

#endif // MEMORY_SEGMENT_H

// Local Variables:
// mode: c++
// End:
