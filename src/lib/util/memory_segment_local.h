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

#ifndef MEMORY_SEGMENT_LOCAL_H
#define MEMORY_SEGMENT_LOCAL_H

#include <util/memory_segment.h>

#include <string>
#include <map>

namespace isc {
namespace util {

/// \brief malloc/free based Memory Segment class
///
/// This class specifies a concrete implementation for a malloc/free
/// based MemorySegment. Please see the MemorySegment class
/// documentation for usage.
class MemorySegmentLocal : public MemorySegment {
public:
    /// \brief Constructor
    ///
    /// Creates a local memory segment object
    MemorySegmentLocal() : allocated_size_(0) {
    }

    /// \brief Destructor
    virtual ~MemorySegmentLocal() {}

    /// \brief Allocate/acquire a segment of memory. The source of the
    /// memory is libc's malloc().
    ///
    /// Throws <code>std::bad_alloc</code> if the implementation cannot
    /// allocate the requested storage.
    ///
    /// \param size The size of the memory requested in bytes.
    /// \return Returns pointer to the memory allocated.
    virtual void* allocate(size_t size);

    /// \brief Free/release a segment of memory.
    ///
    /// This method may throw <code>isc::OutOfRange</code> if \c size is
    /// not equal to the originally allocated size.
    ///
    /// \param ptr Pointer to the block of memory to free/release. This
    /// should be equal to a value returned by <code>allocate()</code>.
    /// \param size The size of the memory to be freed in bytes. This
    /// should be equal to the number of bytes originally allocated.
    virtual void deallocate(void* ptr, size_t size);

    /// \brief Check if all allocated memory was deallocated.
    ///
    /// \return Returns <code>true</code> if all allocated memory was
    /// deallocated, <code>false</code> otherwise.
    virtual bool allMemoryDeallocated() const;

    /// \brief Local segment version of getNamedAddress.
    ///
    /// There's a small chance this method could throw std::bad_alloc.
    /// It should be considered a fatal error.
    virtual void* getNamedAddress(const char* name);

    /// \brief Local segment version of setNamedAddress.
    ///
    /// This version does not validate the given address to see whether it
    /// belongs to this segment.
    virtual bool setNamedAddress(const char* name, void* addr);

    /// \brief Local segment version of clearNamedAddress.
    ///
    /// There's a small chance this method could throw std::bad_alloc.
    /// It should be considered a fatal error.
    virtual bool clearNamedAddress(const char* name);

private:
    // allocated_size_ can underflow, wrap around to max size_t (which
    // is unsigned). But because we only do a check against 0 and not a
    // relation comparison, this is okay.
    size_t allocated_size_;

    std::map<std::string, void*> named_addrs_;
};

} // namespace util
} // namespace isc

#endif // MEMORY_SEGMENT_LOCAL_H

// Local Variables:
// mode: c++
// End:
