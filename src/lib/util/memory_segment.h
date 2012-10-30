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

#include <stdlib.h>

namespace isc {
namespace util {

/// \brief Memory Segment Class
///
/// This class specifies an interface for allocating memory
/// segments. This is an abstract class and a real
/// implementation such as MemorySegmentLocal should be used
/// in code.
class MemorySegment {
public:
    /// \brief Destructor
    virtual ~MemorySegment() {}

    /// \brief Allocate/acquire a segment of memory. The source of the
    /// memory is dependent on the implementation used.
    ///
    /// Throws <code>std::bad_alloc</code> if the implementation cannot
    /// allocate the requested storage.
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
    /// \return Returns <code>true</code> if all allocated memory was
    /// deallocated, <code>false</code> otherwise.
    virtual bool allMemoryDeallocated() const = 0;
};

} // namespace util
} // namespace isc

#endif // MEMORY_SEGMENT_H
