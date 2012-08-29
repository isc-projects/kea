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

#ifndef DATASRC_MEMORY_SEGMENT_OBJECT_HOLDER_H
#define DATASRC_MEMORY_SEGMENT_OBJECT_HOLDER_H 1

#include <util/memory_segment.h>

namespace isc {
namespace datasrc {
namespace memory {
namespace detail {

// A simple holder to create and use some objects in this implementation
// in an exception safe manner.   It works like std::auto_ptr but much
// more simplified.
// template parameter T is the type of object allocated by mem_sgmt.
// template parameter ARG_T is the type that will be passed to destroy()
// (deleter functor, etc).  It must be copyable.
template <typename T, typename ARG_T>
class SegmentObjectHolder {
public:
    SegmentObjectHolder(util::MemorySegment& mem_sgmt, T* obj, ARG_T arg) :
        mem_sgmt_(mem_sgmt), obj_(obj), arg_(arg)
    {}
    ~SegmentObjectHolder() {
        if (obj_ != NULL) {
            T::destroy(mem_sgmt_, obj_, arg_);
        }
    }
    T* get() { return (obj_); }
    T* release() {
        T* ret = obj_;
        obj_ = NULL;
        return (ret);
    }
private:
    util::MemorySegment& mem_sgmt_;
    T* obj_;
    ARG_T arg_;
};

} // detail
} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_SEGMENT_OBJECT_HOLDER_H

// Local Variables:
// mode: c++
// End:
