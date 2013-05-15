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

#ifndef DATASRC_MEMORY_SEGMENT_OBJECT_HOLDER_H
#define DATASRC_MEMORY_SEGMENT_OBJECT_HOLDER_H 1

#include <util/memory_segment.h>
#include <string>
#include <cassert>

namespace isc {
namespace datasrc {
namespace memory {
namespace detail {

// Internal function to get next yet unused name of segment holder.
// We need the names of holders to be unique per segment at any given
// momemnt. This just keeps incrementing number after a prefix with
// each call, it should be enough (the holder should no longer be
// alive when the counter wraps around, if that ever happens with
// presumably 64bit counters).
std::string
getNextHolderName();

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
        mem_sgmt_(mem_sgmt), arg_(arg),
        holder_name_(getNextHolderName()), holding_(true)
    {
        mem_sgmt_.setNamedAddress(holder_name_.c_str(), obj);
    }
    ~SegmentObjectHolder() {
        if (holding_) {
            // Use release, as it removes the stored address from segment
            T* obj = release();
            T::destroy(mem_sgmt_, obj, arg_);
        }
    }
    T* get() {
        if (holding_) {
            const util::MemorySegment::NamedAddressResult result =
                mem_sgmt_.getNamedAddress(holder_name_.c_str());
            assert(result.first);
            return (static_cast<T*>(result.second));
        } else {
            return (NULL);
        }
    }
    T* release() {
        if (holding_) {
            T* obj = get();
            mem_sgmt_.clearNamedAddress(holder_name_.c_str());
            holding_ = false;
            return (obj);
        } else {
            return (NULL);
        }
    }
private:
    util::MemorySegment& mem_sgmt_;
    ARG_T arg_;
    const std::string holder_name_;
    bool holding_;
};

} // detail
} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_SEGMENT_OBJECT_HOLDER_H

// Local Variables:
// mode: c++
// End:
