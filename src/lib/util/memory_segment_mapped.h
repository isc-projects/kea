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

#ifndef MEMORY_SEGMENT_MAPPED_H
#define MEMORY_SEGMENT_MAPPED_H

#include <util/memory_segment.h>
#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

#include <string>

namespace isc {
namespace util {

/// \brief Mapped-file based Memory Segment class.
///
/// This implementation of \c MemorySegment uses a concrete file to be mapped
/// into memory.  Multiple processes can share the same mapped memory image.
///
/// This class provides two operation modes: read-only and read-write.
/// A \c MemorySegmentMapped object in the read-only mode cannot modify the
/// mapped memory image or other internal maintenance data of the object;
/// In the read-write mode the object can allocate or deallocate memory
/// from the mapped image, and the owner process can change the content.
///
/// This class does not provide any synchronization mechanism between
/// read-only and read-write objects that share the same mapped image;
/// in fact, the expected usage is the application (or a system of related
/// processes) ensures there's at most one read-write object and if there's
/// such an object no read-only object shares the image.  If an application
/// uses this class beyond that expectation, it's the application's
/// responsibility to provide necessary synchronization between the processes.
class MemorySegmentMapped : boost::noncopyable, public MemorySegment {
public:
    /// \brief The default value of the mapped file size when newly created.
    ///
    /// Its value, 32KB, is an arbitrary choice, but considered to be
    /// sufficiently but not too large.
    static const size_t INITIAL_SIZE = 32768;

    /// \brief Constructor in the read-only mode.
    ///
    /// This constructor will map the content of the given file into memory
    /// in the "read only" mode; the resulting memory segment object cannot
    /// be used with methods that would requite the mapped memory (see method
    /// descriptions).  Also, if the application tries to modify memory in
    /// the segment, it will make the application crash.
    ///
    /// The file must have been created by the other version of the
    /// constructor beforehand and must be readable for the process
    /// constructing this object.  Otherwise \c MemorySegmentOpenError
    /// exception will be thrown.
    ///
    /// \throw MemorySegmentOpenError The given file does not exist, is not
    /// readable, or not valid mappable segment.
    /// \throw std::bad_alloc (rare case) internal resource allocation
    /// failure.
    ///
    /// \param filename The file name to be mapped to memory.
    MemorySegmentMapped(const std::string& filename);

    /// \brief Constructor in the read-write mode.
    ///
    /// This is similar to the read-only version of the constructor, but
    /// does not have the restrictions that the read-only version has.
    /// If \c create is true and the specified file does not exist, it tries
    /// to create a new file of the name and build internal data on it so that
    /// the file will be mappable by this class object.  If \c create is
    /// false, the specified file must exist and be writable, and have been
    /// previously initialized by this version of constructor with \c create
    /// being true.  If any of these conditions is not met,
    /// \c MemorySegmentOpenError exception will be thrown.
    ///
    /// \param filename The file name to be mapped to memory.
    /// \param create If true and the file does not exist a new one is created.
    /// \param initial_size Specifies the size of the newly created file;
    /// ignored if \c create is false.
    MemorySegmentMapped(const std::string& filename, bool create,
                        size_t initial_size = INITIAL_SIZE);

    /// \brief Destructor.
    ///
    /// If the object was constructed in the read-write mode and the underlying
    /// memory segment wasn't broken due to an exceptional event, the
    /// destructor ensures the content of the mapped memory is written back to
    /// the corresponding file.
    virtual ~MemorySegmentMapped();

    /// \brief Allocate/acquire a segment of memory.
    ///
    /// This version can throw \c MemorySegmentGrown.
    ///
    /// This method cannot be called if the segment object is created in the
    /// read-only mode; in that case InvalidOperation will be thrown.
    virtual void* allocate(size_t size);

    /// \brief Deallocate/release a segment of memory.
    ///
    /// This implementation does not check the validity of \c size, because
    /// if this segment object was constructed for an existing file to map,
    /// the underlying segment may already contain allocated regions, so
    /// this object cannot reliably detect whether it's safe to deallocate
    /// the given size of memory from the underlying segment.
    ///
    /// Parameter \c ptr must point to an address that was returned by a
    /// prior call to \c allocate() of this segment object, and there should
    /// not be a \c MemorySegmentGrown exception thrown from \c allocate()
    /// since then; if it was thrown the corresponding address must have been
    /// adjusted some way; e.g., by re-fetching the latest mapped address
    /// via \c getNamedAddress().
    ///
    /// This method cannot be called if the segment object is created in the
    /// read-only mode; in that case InvalidOperation will be thrown.
    virtual void deallocate(void* ptr, size_t size);

    virtual bool allMemoryDeallocated() const;

    /// \brief Mapped segment version of setNamedAddress.
    ///
    /// This implementation detects if \c addr is invalid (see the base class
    /// description) and throws \c MemorySegmentError in that case.
    ///
    /// This version can actually return true.
    ///
    /// This method cannot be called if the segment object is created in the
    /// read-only mode; in that case InvalidOperation will be thrown.
    virtual bool setNamedAddress(const char* name, void* addr);

    /// \brief Mapped segment version of getNamedAddress.
    ///
    /// This version never throws.
    virtual void* getNamedAddress(const char* name);

    /// \brief Mapped segment version of clearNamedAddress.
    ///
    /// This version never throws.
    virtual bool clearNamedAddress(const char* name);

    /// \brief Shrink the underlying mapped segment to actually used size.
    ///
    /// It will be convenient when a large amount of memory is allocated
    /// then deallocated from the segment in order to keep the resulting
    /// segment a reasonable size.
    ///
    /// This method works best effort basis, and does not guarantee any
    /// specific result.
    ///
    /// This method is generally expected to be failure-free, but it's still
    /// possible to fail.  For example, the underlying file may not be writable
    /// at the time of shrink attempt; it also tries to remap the shrunk
    /// segment internally, and there's a small chance it could fail.
    /// In such a case it throws \c MemorySegmentError.  If it's thrown the
    /// segment is not usable any more.
    ///
    /// This method cannot be called if the segment object is created in the
    /// read-only mode; in that case InvalidOperation will be thrown.
    void shrinkToFit();

    /// \brief Return the actual segment size.
    ///
    /// This is generally expected to be the file size to map.  It's
    /// provided mainly for diagnose an testing purposes; the application
    /// shouldn't rely on specific return values of this method.
    ///
    /// \throw None
    size_t getSize() const;

    /// \brief Calculate a checksum over the memory segment.
    ///
    /// This method goes over all pages of the underlying mapped memory
    /// segment, and returns the sum of the value of the first byte of each
    /// page (ignoring any possible overflow).  It only proves weak integrity
    /// of the file contents, but can run fast enough and will ensure all
    /// pages are actually on memory.  The latter property will be useful
    /// if the application cannot allow the initial page fault overhead.
    ///
    /// \throw None
    size_t getCheckSum() const;

private:
    struct Impl;
    Impl* impl_;
};

} // namespace util
} // namespace isc

#endif // MEMORY_SEGMENT_MAPPED_H

// Local Variables:
// mode: c++
// End:
