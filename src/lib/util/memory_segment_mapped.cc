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
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <cassert>
#include <string>
#include <new>

using namespace boost::interprocess;

namespace isc {
namespace util {

// We customize managed_mapped_file to make it completely lock free.  In our
// usage the application (or the system of applications) is expected to ensure
// there's at most one writer process or concurrent writing the shared memory
// segment is protected at a higher level.  Using the null mutex is mainly for
// eliminating unnecessary dependency; the default version would require
// (probably depending on the system) Pthread library that is actually not
// needed and could cause various build time troubles.
typedef basic_managed_mapped_file<char,
                                  rbtree_best_fit<null_mutex_family>,
                                  iset_index> BaseSegment;

struct MemorySegmentMapped::Impl {
    Impl(const std::string& filename, size_t initial_size) :
        read_only_(false), filename_(filename),
        base_sgmt_(new BaseSegment(open_or_create, filename.c_str(),
                                   initial_size))
    {}

    Impl(const std::string& filename, bool read_only) :
        read_only_(read_only), filename_(filename),
        base_sgmt_(read_only ?
                   new BaseSegment(open_read_only, filename.c_str()) :
                   new BaseSegment(open_only, filename.c_str()))
    {}

    // Internal helper to grow the underlying mapped segment.
    void growSegment() {
        // We first need to unmap it before calling grow().
        const size_t prev_size = base_sgmt_->get_size();
        base_sgmt_->flush();
        base_sgmt_.reset();

        const size_t new_size = prev_size * 2;
        assert(new_size != 0); // assume grow fails before size overflow

        if (!BaseSegment::grow(filename_.c_str(), new_size - prev_size))
        {
            throw std::bad_alloc();
        }

        try {
            // Remap the grown file; this should succeed, but it's not 100%
            // guaranteed.  If it fails we treat it as if we fail to create
            // the new segment.
            base_sgmt_.reset(new BaseSegment(open_only, filename_.c_str()));
        } catch (const boost::interprocess::interprocess_exception& ex) {
            throw std::bad_alloc();
        }
    }

    // remember if the segment is opened read-only or not
    const bool read_only_;

    // mapped file; remember it in case we need to grow it.
    const std::string filename_;

    // actual Boost implementation of mapped segment.
    boost::scoped_ptr<BaseSegment> base_sgmt_;
};

MemorySegmentMapped::MemorySegmentMapped(const std::string& filename) :
    impl_(0)
{
    try {
        impl_ = new Impl(filename, true);
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
            impl_ = new Impl(filename, false);
        }
    } catch (const boost::interprocess::interprocess_exception& ex) {
        isc_throw(MemorySegmentOpenError,
                  "failed to open mapped memory segment for " << filename
                  << ": " << ex.what());
    }
}

MemorySegmentMapped::~MemorySegmentMapped() {
    if (impl_->base_sgmt_ && !impl_->read_only_) {
        impl_->base_sgmt_->flush(); // note: this is exception free
    }
    delete impl_;
}

void*
MemorySegmentMapped::allocate(size_t size) {
    if (impl_->read_only_) {
        isc_throw(InvalidOperation, "allocate attempt on read-only segment");
    }

    // We explicitly check the free memory size; it appears
    // managed_mapped_file::allocate() could incorrectly return a seemingly
    // valid pointer for some very large requested size.
    if (impl_->base_sgmt_->get_free_memory() >= size) {
        void* ptr = impl_->base_sgmt_->allocate(size, std::nothrow);
        if (ptr) {
            return (ptr);
        }
    }

    // Grow the mapped segment doubling the size until we have sufficient
    // free memory in the revised segment for the requested size.
    do {
        impl_->growSegment();
    } while (impl_->base_sgmt_->get_free_memory() < size);
    isc_throw(MemorySegmentGrown, "mapped memory segment grown, size: "
              << impl_->base_sgmt_->get_size() << ", free size: "
              << impl_->base_sgmt_->get_free_memory());
}

void
MemorySegmentMapped::deallocate(void* ptr, size_t) {
    if (impl_->read_only_) {
        isc_throw(InvalidOperation, "allocate attempt on read-only segment");
    }

    // the underlying deallocate() would deal with the case where ptr == 0,
    // but it's an undocumented behavior, so we handle it ourselves for safety.
    if (!ptr) {
        return;
    }

    impl_->base_sgmt_->deallocate(ptr);
}

bool
MemorySegmentMapped::allMemoryDeallocated() const {
    return (impl_->base_sgmt_->all_memory_deallocated());
}

void*
MemorySegmentMapped::getNamedAddress(const char* name) {
    offset_ptr<void>* storage =
        impl_->base_sgmt_->find<offset_ptr<void> >(name).first;
    if (storage) {
        return (storage->get());
    }
    return (0);
}

bool
MemorySegmentMapped::setNamedAddress(const char* name, void* addr) {
    if (impl_->read_only_) {
        isc_throw(InvalidOperation, "setNamedAddress on read-only segment");
    }

    if (addr && !impl_->base_sgmt_->belongs_to_segment(addr)) {
        isc_throw(MemorySegmentError, "out of segment address: " << addr);
    }

    bool grown = false;
    while (true) {
        offset_ptr<void>* storage =
            impl_->base_sgmt_->find_or_construct<offset_ptr<void> >(
                name, std::nothrow)();
        if (storage) {
            *storage = addr;
            return (grown);
        }

        impl_->growSegment();
        grown = true;
    }
}

bool
MemorySegmentMapped::clearNamedAddress(const char* name) {
    if (impl_->read_only_) {
        isc_throw(InvalidOperation, "clearNamedAddress on read-only segment");
    }

    return (impl_->base_sgmt_->destroy<offset_ptr<void> >(name));
}

void
MemorySegmentMapped::shrinkToFit() {
    if (impl_->read_only_) {
        isc_throw(InvalidOperation, "shrinkToFit on read-only segment");
    }

    // It appears an assertion failure is triggered within Boost if the size
    // is too small.  To work this around we'll make it no-op if the size is
    // already reasonably small.
    if (getSize() < INITIAL_SIZE) {
        return;
    }

    impl_->base_sgmt_.reset();
    BaseSegment::shrink_to_fit(impl_->filename_.c_str());
    try {
        // Remap the grown file; this should succeed, but it's not 100%
        // guaranteed.  If it fails we treat it as if we fail to create
        // the new segment.
        impl_->base_sgmt_.reset(
            new BaseSegment(open_only, impl_->filename_.c_str()));
    } catch (const boost::interprocess::interprocess_exception& ex) {
        isc_throw(MemorySegmentError,
                  "remap after shrink failed; segment is now unusable");
    }
}

size_t
MemorySegmentMapped::getSize() const {
    return (impl_->base_sgmt_->get_size());
}

size_t
MemorySegmentMapped::getCheckSum() const {
    const size_t page_sz = boost::interprocess::mapped_region::get_page_size();
    const uint8_t* const cp_beg = static_cast<const uint8_t*>(
        impl_->base_sgmt_->get_address());
    const uint8_t* const cp_end = cp_beg + impl_->base_sgmt_->get_size();

    size_t sum = 0;
    for (const uint8_t* cp = cp_beg; cp < cp_end; cp += page_sz) {
        sum += *cp;
    }

    return (sum);
}

} // namespace util
} // namespace isc
