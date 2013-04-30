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
/// Multiple processes can open multiple segments for the same file in
/// read-only mode at the same time.  But there shouldn't be more than
/// one process that opens segments for the same file in read-write mode
/// at the same time.  Likewise, if one process opens a segment for a
/// file in read-write mode, there shouldn't be any other process that
/// opens a segment for the file in read-only mode. If one or more
/// processes open segments for a file in read-only mode, there
/// shouldn't be any other process that opens a segment for the file in
/// read-write mode. This class tries to detect any violation of this
/// restriction, but this does not intend to provide 100% safety.  It's
/// generally the user's responsibility to ensure this condition.
///
/// The same restriction applies within the single process, whether
/// multi-threaded or not: a process shouldn't open read-only and read-write
/// (or multiple read-write) segments for the same file.  The violation
/// detection mentioned above may or may not work in such cases due to
/// limitation of the underlying API.  It's completely user's responsibility
/// to prevent this from happening.  A single process may open multiple
/// segments in read-only mode for the same file, but that shouldn't be
/// necessary in practice; since it's read-only there wouldn't be a reason
/// to have a redundant copy.
class MemorySegmentMapped : boost::noncopyable, public MemorySegment {
public:
    /// \brief The default value of the mapped file size when newly created.
    ///
    /// Its value, 32KB, is an arbitrary choice, but considered to be
    /// sufficiently but not too large.
    static const size_t INITIAL_SIZE = 32768;

    /// \brief Open modes of \c MemorySegmentMapped.
    ///
    /// These modes matter only for \c MemorySegmentMapped to be opened
    /// in read-write mode, and specify further details of open operation.
    enum OpenMode {
        OPEN_FOR_WRITE = 0,     ///< Open only.  File must exist.
        OPEN_OR_CREATE,         ///< If file doesn't exist it's created.
        CREATE_ONLY ///< New file is created; existing one will be removed.
    };

    /// \brief Constructor in the read-only mode.
    ///
    /// This constructor will map the content of the given file into memory
    /// in read-only mode; the resulting memory segment object cannot
    /// be used with methods that would require the mapped memory (see method
    /// descriptions).  Also, if the application tries to modify memory in
    /// the segment, it will make the application crash.
    ///
    /// The file must have been created by the other version of the
    /// constructor beforehand and must be readable for the process
    /// constructing this object.  Otherwise \c MemorySegmentOpenError
    /// exception will be thrown.
    ///
    /// \throw MemorySegmentOpenError The given file does not exist, is not
    /// readable, or not valid mappable segment.  Or there is another process
    /// that has already opened a segment for the file.
    /// \throw std::bad_alloc (rare case) internal resource allocation
    /// failure.
    ///
    /// \param filename The file name to be mapped to memory.
    MemorySegmentMapped(const std::string& filename);

    /// \brief Constructor in the read-write mode.
    ///
    /// This is similar to the read-only version of the constructor, but
    /// does not have the restrictions that the read-only version has.
    ///
    /// The \c mode parameter specifies further details of how the segment
    /// should be opened.
    /// - OPEN_FOR_WRITE: this is open-only mode.  The file must exist,
    ///   and it will be opened without any initial modification.
    /// - OPEN_OR_CREATE: similar to OPEN_FOR_WRITE, but if the file does not
    ///   exist, a new one will be created.  An existing file will be used
    ///   any initial modification.
    /// - CREATE_ONLY: a new file (of the given file name) will be created;
    ///   any existing file of the same name will be removed.
    ///
    /// If OPEN_FOR_WRITE is specified, the specified file must exist
    /// and be writable, and have been previously initialized by this
    /// version of constructor either with OPEN_OR_CREATE or CREATE_ONLY.
    /// If the mode is OPEN_OR_CREATE or CREATE_ONLY, and the file needs
    /// to be created, then this method tries to create a new file of the
    /// name and build internal data on it so that the file will be mappable
    /// by this class object.  If any of these conditions is not met, or
    /// create or initialization fails, \c MemorySegmentOpenError exception
    /// will be thrown.
    ///
    /// This constructor also throws \c MemorySegmentOpenError when it
    /// detects violation of the restriction on the mixed open of read-only
    /// and read-write mode (see the class description).
    ///
    /// When initial_size is specified but is too small (including a value of
    /// 0), the underlying Boost library will reject it, and this constructor
    /// throws \c MemorySegmentOpenError exception.  The Boost documentation
    /// does not specify how large it should be, but the default
    /// \c INITIAL_SIZE should be sufficiently large in practice.
    ///
    /// \throw MemorySegmentOpenError see the description.
    ///
    /// \param filename The file name to be mapped to memory.
    /// \param mode Open mode (see the description).
    /// \param initial_size Specifies the size of the newly created file;
    /// ignored if \c mode is OPEN_FOR_WRITE.
    MemorySegmentMapped(const std::string& filename, OpenMode mode,
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
    /// read-only mode; in that case MemorySegmentError will be thrown.
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
    /// read-only mode; in that case MemorySegmentError will be thrown.
    virtual void deallocate(void* ptr, size_t size);

    virtual bool allMemoryDeallocated() const;

    /// \brief Mapped segment version of setNamedAddress.
    ///
    /// This implementation detects if \c addr is invalid (see the base class
    /// description) and throws \c MemorySegmentError in that case.
    ///
    /// This version of method should normally return false.  However,
    /// it internally allocates memory in the segment for the name and
    /// address to be stored, which can require segment extension, just like
    /// allocate().  So it's possible to return true unlike
    /// \c MemorySegmentLocal version of the method.
    ///
    /// This method cannot be called if the segment object is created in the
    /// read-only mode; in that case MemorySegmentError will be thrown.
    virtual bool setNamedAddressImpl(const char* name, void* addr);

    /// \brief Mapped segment version of getNamedAddress.
    ///
    /// This version never throws.
    virtual void* getNamedAddressImpl(const char* name);

    /// \brief Mapped segment version of clearNamedAddress.
    ///
    /// This method cannot be called if the segment object is created in the
    /// read-only mode; in that case MemorySegmentError will be thrown.
    virtual bool clearNamedAddressImpl(const char* name);

    /// \brief Shrink the underlying mapped segment to actually used size.
    ///
    /// When a large amount of memory is allocated and then deallocated
    /// from the segment, this method can be used to keep the resulting
    /// segment at a reasonable size.
    ///
    /// This method works by a best-effort basis, and does not guarantee
    /// any specific result.
    ///
    /// This method is generally expected to be failure-free, but it's still
    /// possible to fail.  For example, the underlying file may not be writable
    /// at the time of shrink attempt; it also tries to remap the shrunk
    /// segment internally, and there's a small chance it could fail.
    /// In such a case it throws \c MemorySegmentError.  If it's thrown the
    /// segment is not usable anymore.
    ///
    /// This method cannot be called if the segment object is created in the
    /// read-only mode; in that case MemorySegmentError will be thrown.
    ///
    /// \throw MemorySegmentError see the description.
    void shrinkToFit();

    /// \brief Return the actual segment size.
    ///
    /// This is generally expected to be the file size to map.  It's
    /// provided mainly for diagnosis and testing purposes; the application
    /// shouldn't rely on specific return values of this method.
    ///
    /// \throw None
    size_t getSize() const;

    /// \brief Calculate a checksum over the memory segment.
    ///
    /// This method goes over all pages of the underlying mapped memory
    /// segment, and returns the sum of the value of the first byte of each
    /// page (wrapping around upon overflow).  It only proves weak integrity
    /// of the file contents, but can run fast enough and will ensure all
    /// pages are actually in memory.  The latter property will be useful
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
