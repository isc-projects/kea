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
    virtual void deallocate(void* ptr, size_t size);

    virtual bool allMemoryDeallocated() const;

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
