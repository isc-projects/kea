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

#ifndef __MEMORY_SEGMENT_LOCAL_H__
#define __MEMORY_SEGMENT_LOCAL_H__

#include <util/memory_segment.h>

namespace isc {
namespace util {

class MemorySegmentLocal : public MemorySegment {
public:
    MemorySegmentLocal() : allocated_size_(0) {
    }

    void* allocate(size_t size);
    void deallocate(void* ptr, size_t size);
    bool allMemoryDeallocated() const;

private:
    size_t allocated_size_;
};

} // namespace util
} // namespace isc

#endif // __MEMORY_SEGMENT_LOCAL_H__
