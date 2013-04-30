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
#include <util/unittests/check_valgrind.h>

#include <exceptions/exceptions.h>

#include <boost/scoped_ptr.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/file_lock.hpp>

#include <cassert>
#include <string>
#include <new>

// boost::interprocess namespace is big and can cause unexpected import
// (e.g., it has "read_only"), so it's safer to be specific for shortcuts.
using boost::interprocess::basic_managed_mapped_file;
using boost::interprocess::rbtree_best_fit;
using boost::interprocess::null_mutex_family;
using boost::interprocess::iset_index;
using boost::interprocess::create_only_t;
using boost::interprocess::create_only;
using boost::interprocess::open_or_create_t;
using boost::interprocess::open_or_create;
using boost::interprocess::open_read_only;
using boost::interprocess::open_only;
using boost::interprocess::offset_ptr;

namespace isc {
namespace util {
// Definition of class static constant so it can be referenced by address
// or reference.
const size_t MemorySegmentMapped::INITIAL_SIZE;

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
    // Constructor for create-only (and read-write) mode.  this case is
    // tricky because we want to remove any existing file but we also want
    // to detect possible conflict with other readers or writers using
    // file lock.
    Impl(const std::string& filename, create_only_t, size_t initial_size) :
        read_only_(false), filename_(filename)
    {
        try {
            // First, try opening it in boost create_only mode; it fails if
            // the file exists (among other reasons).
            base_sgmt_.reset(new BaseSegment(create_only, filename.c_str(),
                                             initial_size));
        } catch (const boost::interprocess::interprocess_exception& ex) {
            // We assume this is because the file exists; otherwise creating
            // file_lock would fail with interprocess_exception, and that's
            // what we want here (we wouldn't be able to create a segment
            // anyway).
            lock_.reset(new boost::interprocess::file_lock(filename.c_str()));

            // Confirm there's no other reader or writer, and then release
            // the lock before we remove the file; there's a chance of race
            // here, but this check doesn't intend to guarantee 100% safety
            // and so it should be okay.
            checkWriter();
            lock_.reset();

            // now remove the file (if it happens to have been delete, this
            // will be no-op), then re-open it with create_only.  this time
            // it should succeed, and if it fails again, that's fatal for this
            // constructor.
            boost::interprocess::file_mapping::remove(filename.c_str());
            base_sgmt_.reset(new BaseSegment(create_only, filename.c_str(),
                                             initial_size));
        }

        // confirm there's no other user and there won't either.
        lock_.reset(new boost::interprocess::file_lock(filename.c_str()));
        checkWriter();
    }

    // Constructor for open-or-write (and read-write) mode
    Impl(const std::string& filename, open_or_create_t, size_t initial_size) :
        read_only_(false), filename_(filename),
        base_sgmt_(new BaseSegment(open_or_create, filename.c_str(),
                                   initial_size)),
        lock_(new boost::interprocess::file_lock(filename.c_str()))
    {
        checkWriter();
    }

    // Constructor for existing segment, either read-only or read-write
    Impl(const std::string& filename, bool read_only) :
        read_only_(read_only), filename_(filename),
        base_sgmt_(read_only_ ?
                   new BaseSegment(open_read_only, filename.c_str()) :
                   new BaseSegment(open_only, filename.c_str())),
        lock_(new boost::interprocess::file_lock(filename.c_str()))
    {
        if (read_only_) {
            checkReader();
        } else {
            checkWriter();
        }
    }

    // Internal helper to grow the underlying mapped segment.
    void growSegment() {
        // We first need to unmap it before calling grow().
        const size_t prev_size = base_sgmt_->get_size();
        base_sgmt_.reset();

        // Double the segment size.  In theory, this process could repeat
        // so many times, counting to "infinity", and new_size eventually
        // overflows.  That would cause a harsh disruption or unexpected
        // behavior.  But we basically assume grow() would fail before this
        // happens, so we assert it shouldn't happen.
        const size_t new_size = prev_size * 2;
        assert(new_size > prev_size);

        if (!BaseSegment::grow(filename_.c_str(), new_size - prev_size)) {
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

private:
    // helper methods and member to detect any reader-writer conflict at
    // the time of construction using an advisory file lock.  The lock will
    // be held throughout the lifetime of the object and will be released
    // automatically.

    void checkReader() {
        if (!lock_->try_lock_sharable()) {
            isc_throw(MemorySegmentOpenError,
                      "mapped memory segment can't be opened as read-only "
                      "with a writer process");
        }
    }

    void checkWriter() {
        if (!lock_->try_lock()) {
            isc_throw(MemorySegmentOpenError,
                      "mapped memory segment can't be opened as read-write "
                      "with other reader or writer processes");
        }
    }

    boost::scoped_ptr<boost::interprocess::file_lock> lock_;
};

MemorySegmentMapped::MemorySegmentMapped(const std::string& filename) :
    impl_(NULL)
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
                                         OpenMode mode, size_t initial_size) :
    impl_(NULL)
{
    try {
        switch (mode) {
        case OPEN_FOR_WRITE:
            impl_ = new Impl(filename, false);
            break;
        case OPEN_OR_CREATE:
            impl_ = new Impl(filename, open_or_create, initial_size);
            break;
        case CREATE_ONLY:
            impl_ = new Impl(filename, create_only, initial_size);
            break;
        default:
            isc_throw(InvalidParameter,
                      "invalid open mode for MemorySegmentMapped: " << mode);
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
        isc_throw(MemorySegmentError, "allocate attempt on read-only segment");
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
        isc_throw(MemorySegmentError,
                  "deallocate attempt on read-only segment");
    }

    // the underlying deallocate() would deal with the case where ptr == NULL,
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
MemorySegmentMapped::getNamedAddressImpl(const char* name) {
    offset_ptr<void>* storage =
        impl_->base_sgmt_->find<offset_ptr<void> >(name).first;
    if (storage) {
        return (storage->get());
    }
    return (NULL);
}

bool
MemorySegmentMapped::setNamedAddressImpl(const char* name, void* addr) {
    if (impl_->read_only_) {
        isc_throw(MemorySegmentError, "setNamedAddress on read-only segment");
    }

    if (addr && !impl_->base_sgmt_->belongs_to_segment(addr)) {
        isc_throw(MemorySegmentError, "address is out of segment: " << addr);
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
MemorySegmentMapped::clearNamedAddressImpl(const char* name) {
    if (impl_->read_only_) {
        isc_throw(MemorySegmentError,
                  "clearNamedAddress on read-only segment");
    }

    return (impl_->base_sgmt_->destroy<offset_ptr<void> >(name));
}

void
MemorySegmentMapped::shrinkToFit() {
    if (impl_->read_only_) {
        isc_throw(MemorySegmentError, "shrinkToFit on read-only segment");
    }

    // It appears an assertion failure is triggered within Boost if the size
    // is too small (happening if shrink_to_fit() is called twice without
    // allocating any memory from the shrunk segment).  To work this around
    // we'll make it no-op if the size is already reasonably small.
    // Using INITIAL_SIZE is not 100% reliable as it's irrelevant to the
    // internal constraint of the Boost implementation.  But, in practice,
    // it should be sufficiently large and safe.
    if (getSize() < INITIAL_SIZE) {
        return;
    }

    // First, (unmap and) close the underlying file.
    impl_->base_sgmt_.reset();

    BaseSegment::shrink_to_fit(impl_->filename_.c_str());
    try {
        // Remap the shrunk file; this should succeed, but it's not 100%
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
    const size_t pagesize =
        boost::interprocess::mapped_region::get_page_size();
    const uint8_t* const cp_begin = static_cast<const uint8_t*>(
        impl_->base_sgmt_->get_address());
    const uint8_t* const cp_end = cp_begin + impl_->base_sgmt_->get_size();

    size_t sum = 0;
    for (const uint8_t* cp = cp_begin; cp < cp_end; cp += pagesize) {
        sum += *cp;
    }

    return (sum);
}

} // namespace util
} // namespace isc
