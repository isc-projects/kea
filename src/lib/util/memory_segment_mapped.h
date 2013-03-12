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

/// \brief TBD
class MemorySegmentMapped : boost::noncopyable, public MemorySegment {
public:
    /// arbitrary choice.
    static const size_t INITIAL_SIZE = 32768;

    /// \brief Constructor in the read-only mode
    ///
    /// Creates a local memory segment object
    MemorySegmentMapped(const std::string& filename);

    MemorySegmentMapped(const std::string& filename, bool create,
                        size_t initial_size = INITIAL_SIZE);

    /// \brief Destructor
    virtual ~MemorySegmentMapped();

    /// \brief Allocate/acquire a segment of memory.
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
    virtual void deallocate(void* ptr, size_t size);

    virtual bool allMemoryDeallocated() const;

    virtual void* getNamedAddress(const char* name);

    /// \brief TBD
    ///
    /// This implementation detects if \c addr is invalid (see the base class
    /// description) and throws \c MemorySegmentError in that case.
    virtual bool setNamedAddress(const char* name, void* addr);

    virtual bool clearNamedAddress(const char* name);

    virtual void shrinkToFit();

    size_t getSize() const;

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
