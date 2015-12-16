// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MEMORY_SEGMENT_H
#define MEMORY_SEGMENT_H

#include <exceptions/exceptions.h>

#include <utility>

#include <stdlib.h>

namespace isc {
namespace util {

/// \brief Exception that can be thrown when constructing a MemorySegment
/// object.
class MemorySegmentOpenError : public Exception {
public:
    MemorySegmentOpenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief Exception that is thrown, when allocating space in a MemorySegment
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
/// This class specifies an interface for allocating memory segments.
/// It's intended to provide a unified interface, whether the underlying
/// memory is local to a specific process or is sharable by multiple
/// processes.
///
/// This is an abstract class and a real implementation such as
/// MemorySegmentLocal should be used in code.
class MemorySegment {
public:
    /// \brief Destructor
    virtual ~MemorySegment() {}

    /// \brief Allocate/acquire a fragment of memory.
    ///
    /// The source of the memory is dependent on the implementation used.
    ///
    /// Depending on the implementation details, it may have to grow the
    /// internal memory segment (again, in an implementation dependent way)
    /// to allocate the required size of memory.  In that case the
    /// implementation must grow the internal segment sufficiently so the
    /// next call to allocate() for the same size will succeed, and throw
    /// a \c MemorySegmentGrown exception (not really allocating the memory
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
    /// The intended use case of \c allocate() with the \c MemorySegmentGrown
    /// exception is to build a complex object that would internally require
    /// multiple calls to \c allocate():
    ///
    /// \code
    /// ComplicatedStuff* stuff = NULL;
    /// while (!stuff) { // this must eventually succeed or result in bad_alloc
    ///     try {
    ///         // create() is a factory method that takes a memory segment
    ///         // and calls allocate() on it multiple times.  create()
    ///         // provides an exception guarantee that any intermediately
    ///         // allocated memory will be properly deallocate()-ed on
    ///         // exception.
    ///         stuff = ComplicatedStuff::create(mem_segment);
    ///     } catch (const MemorySegmentGrown&) { /* just try again */ }
    /// }
    /// \endcode
    ///
    /// This way, \c create() can be written as if each call to \c allocate()
    /// always succeeds.
    ///
    /// Alternatively, or in addition to this, we could introduce a "no throw"
    /// version of this method with a way to tell the caller the reason of
    /// any failure (whether it's really out of memory or just due to growing
    /// the segment).  That would be more convenient if the caller wants to
    /// deal with the failures on a per-call basis rather than as a set
    /// of calls like in the above example.  At the moment, we don't expect
    /// to have such use-cases, so we only provide the exception
    /// version.
    ///
    /// \throw std::bad_alloc The implementation cannot allocate the
    /// requested storage.
    /// \throw MemorySegmentGrown The memory segment doesn't have sufficient
    /// space for the requested size and has grown internally.
    /// \throw MemorySegmentError An attempt was made to allocate
    /// storage on a read-only memory segment.
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
    /// Specific implementation may also throw \c MemorySegmentError if it
    /// encounters violation of implementation specific restrictions.
    ///
    /// In general, however, this method must succeed and exception free
    /// as long as the caller passes valid parameters (\c ptr specifies
    /// memory previously allocated and \c size is correct).
    ///
    /// \throw OutOfRange The passed size doesn't match the allocated memory
    /// size (when identifiable for the implementation).
    /// \throw MemorySegmentError Failure of implementation specific
    /// validation.
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
    /// Some names are reserved for internal use by this class. If such
    /// a name is passed to this method, an \c isc::InvalidParameter
    /// exception will be thrown. See \c validateName() method for details.
    ///
    /// \c addr must be 0 (NULL) or an address that belongs to this segment.
    /// The latter case means it must be the return value of a previous call
    /// to \c allocate().  The actual implementation is encouraged to detect
    /// violation of this restriction and signal it with an exception, but
    /// it's not an API requirement.  It's generally the caller's
    /// responsibility to meet the restriction.  Note that NULL is allowed
    /// as \c addr even if it wouldn't be considered to "belong to" the
    /// segment in its normal sense; it can be used to indicate that memory
    /// has not been allocated for the specified name.  A subsequent call
    /// to \c getNamedAddress() will return NamedAddressResult(true, NULL)
    /// for that name.
    ///
    /// \note Naming an address is intentionally separated from allocation
    /// so that, for example, one module of a program can name a memory
    /// region allocated by another module of the program.
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
    /// \note The behavior in case the internal segment grows is different
    /// from that of \c allocate().  This is intentional.  In intended use
    /// cases (for the moment) this method will be called independently,
    /// rather than as part of a set of allocations.  It's also expected
    /// that other raw memory addresses (which would have been invalidated
    /// due to the change to the segment) won't be referenced directly
    /// immediately after this call.  So, the caller should normally be able
    /// to call this method as mostly never-fail one (except in case of real
    /// memory exhaustion) and ignore the return value.
    ///
    /// \throw std::bad_alloc Allocation of a segment space for the given name
    /// failed.
    /// \throw InvalidParameter name is NULL, empty ("") or begins with
    /// an underscore ('_').
    /// \throw MemorySegmentError Failure of implementation specific
    /// validation.
    ///
    /// \param name A C string to be associated with \c addr. Must not be NULL.
    /// \param addr A memory address returned by a prior call to \c allocate.
    /// \return true if the internal segment has grown to allocate space for
    /// the name; false otherwise (see above).
    bool setNamedAddress(const char* name, void* addr) {
        // This public method implements common validation.  The actual
        // work specific to the derived segment is delegated to the
        // corresponding protected method.
        validateName(name);
        return (setNamedAddressImpl(name, addr));
    }

    /// \brief Type definition for result returned by getNamedAddress()
    typedef std::pair<bool, void*> NamedAddressResult;

    /// \brief Return the address in the segment that has the given name.
    ///
    /// This method returns the memory address in the segment corresponding
    /// to the specified \c name.  The name and address must have been
    /// associated by a prior call to \c setNameAddress().  If no address
    /// associated with the given name is found, it returns NULL.
    ///
    /// Some names are reserved for internal use by this class. If such
    /// a name is passed to this method, an \c isc::InvalidParameter
    /// exception will be thrown. See \c validateName() method for details.
    ///
    /// This method should generally be considered exception free, but there
    /// can be a small chance it throws, depending on the internal
    /// implementation (e.g., if it converts the name to std::string), so the
    /// API doesn't guarantee that property.  In general, if this method
    /// throws it should be considered a fatal condition.
    ///
    /// \throw InvalidParameter name is NULL, empty ("") or begins with
    /// an underscore ('_').
    ///
    /// \param name A C string of which the segment memory address is to be
    /// returned.  Must not be NULL.
    /// \return An std::pair containing a bool (set to true if the name
    /// was found, or false otherwise) and the address associated with
    /// the name (which is undefined if the name was not found).
    NamedAddressResult getNamedAddress(const char* name) const {
        // This public method implements common validation.  The actual
        // work specific to the derived segment is delegated to the
        // corresponding protected method.
        validateName(name);
        return (getNamedAddressImpl(name));
    }

    /// \brief Delete a name previously associated with a segment address.
    ///
    /// This method deletes the association of the given \c name to
    /// a corresponding segment address previously established by
    /// \c setNamedAddress().  If there is no association for the given name
    /// this method returns false; otherwise it returns true.
    ///
    /// Some names are reserved for internal use by this class. If such
    /// a name is passed to this method, an \c isc::InvalidParameter
    /// exception will be thrown. See \c validateName() method for details.
    ///
    /// See \c getNamedAddress() about exception consideration.
    ///
    /// \throw InvalidParameter name is NULL, empty ("") or begins with
    /// an underscore ('_').
    /// \throw MemorySegmentError Failure of implementation specific
    /// validation.
    ///
    /// \param name A C string of which the segment memory address is to be
    /// deleted. Must not be NULL.
    bool clearNamedAddress(const char* name) {
        // This public method implements common validation.  The actual
        // work specific to the derived segment is delegated to the
        // corresponding protected method.
        validateName(name);
        return (clearNamedAddressImpl(name));
    }

private:
    /// \brief Validate the passed name.
    ///
    /// This method validates the passed name (for name/address pairs)
    /// and throws \c InvalidParameter if the name fails
    /// validation. Otherwise, it does nothing.
    ///
    /// \throw InvalidParameter name is NULL, empty ("") or begins with
    /// an underscore ('_').
    static void validateName(const char* name) {
        if (!name) {
            isc_throw(InvalidParameter, "NULL is invalid for a name.");
        } else if (*name == '\0') {
            isc_throw(InvalidParameter, "Empty names are invalid.");
        } else if (*name == '_') {
            isc_throw(InvalidParameter,
                      "Names beginning with '_' are reserved for "
                      "internal use only.");
        }
    }

protected:
    /// \brief Implementation of setNamedAddress beyond common validation.
    virtual bool setNamedAddressImpl(const char* name, void* addr) = 0;

    /// \brief Implementation of getNamedAddress beyond common validation.
    virtual NamedAddressResult getNamedAddressImpl(const char* name) const = 0;

    /// \brief Implementation of clearNamedAddress beyond common validation.
    virtual bool clearNamedAddressImpl(const char* name) = 0;
};

} // namespace util
} // namespace isc

#endif // MEMORY_SEGMENT_H

// Local Variables:
// mode: c++
// End:
