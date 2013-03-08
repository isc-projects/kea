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

#include <util/memory_segment_mapped.h>

#include <boost/scoped_ptr.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>

#include <cassert>
#include <string>
#include <new>

using boost::interprocess::managed_mapped_file;
using boost::interprocess::open_or_create;
using boost::interprocess::open_only;

namespace isc {
namespace util {

struct MemorySegmentMapped::Impl {
    Impl(const std::string& filename, size_t initial_size) :
        filename_(filename),
        base_sgmt_(new managed_mapped_file(open_or_create, filename.c_str(),
                                           initial_size))
    {}

    Impl(const std::string& filename) :
        filename_(filename),
        base_sgmt_(new managed_mapped_file(open_only, filename.c_str()))
    {}

    // mapped file; remember it in case we need to grow it.
    const std::string filename_;

    // actual Boost implementation of mapped segment.
    boost::scoped_ptr<managed_mapped_file> base_sgmt_;
};

MemorySegmentMapped::MemorySegmentMapped(const std::string& filename) :
    impl_(0)
{
    try {
        impl_ = new Impl(filename);
    } catch (const boost::interprocess::interprocess_exception& ex) {
        isc_throw(MemorySegmentOpenError,
                  "failed to open mapped memory segment for " << filename
                  << ": " << ex.what());
    }
}

MemorySegmentMapped::MemorySegmentMapped(const std::string& filename,
                                         bool create, size_t initial_size) :
    impl_(0)
{
    try {
        if (create) {
            impl_ = new Impl(filename, initial_size);
        } else {
            impl_ = new Impl(filename);
        }
    } catch (const boost::interprocess::interprocess_exception& ex) {
        isc_throw(MemorySegmentOpenError,
                  "failed to open mapped memory segment for " << filename
                  << ": " << ex.what());
    }
}

MemorySegmentMapped::~MemorySegmentMapped() {
    delete impl_;
}

void*
MemorySegmentMapped::allocate(size_t size) {
    void* ptr = impl_->base_sgmt_->allocate(size, std::nothrow);
    if (ptr) {
        return (ptr);
    }

    // Grow the mapped segment doubling the size until we have sufficient
    // free memory in the revised segment for the requested size.
    while (impl_->base_sgmt_->get_free_memory() < size) {
        // We first need to unmap it before calling grow().
        const size_t prev_size = impl_->base_sgmt_->get_size();
        impl_->base_sgmt_.reset();

        const size_t new_size = prev_size * 2;
        assert(new_size != 0); // assume grow fails before size overflow

        // TBD error handling
        managed_mapped_file::grow(impl_->filename_.c_str(),
                                  new_size - prev_size);
        impl_->base_sgmt_.reset(
            new managed_mapped_file(open_only, impl_->filename_.c_str()));
    }
    isc_throw(MemorySegmentGrown, "mapped memory segment grown, size: "
              << impl_->base_sgmt_->get_size() << ", free size: "
              << impl_->base_sgmt_->get_free_memory());
}

void
MemorySegmentMapped::deallocate(void* ptr, size_t /*size*/) {
    impl_->base_sgmt_->deallocate(ptr);
}

bool
MemorySegmentMapped::allMemoryDeallocated() const {
    return (impl_->base_sgmt_->all_memory_deallocated());
}

size_t
MemorySegmentMapped::getSize() const {
    return (impl_->base_sgmt_->get_size());
}

} // namespace util
} // namespace isc
