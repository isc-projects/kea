// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/memory_segment_local.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace util {

void*
MemorySegmentLocal::allocate(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }

    allocated_size_ += size;
    return (ptr);
}

void
MemorySegmentLocal::deallocate(void* ptr, size_t size) {
    if (ptr == NULL) {
        // Return early if NULL is passed to be deallocated (without
        // modifying allocated_size, or comparing against it).
        return;
    }

    if (size > allocated_size_) {
      isc_throw(OutOfRange, "Invalid size to deallocate: " << size
                << "; currently allocated size: " << allocated_size_);
    }

    allocated_size_ -= size;
    free(ptr);
}

bool
MemorySegmentLocal::allMemoryDeallocated() const {
    return (allocated_size_ == 0 && named_addrs_.empty());
}

MemorySegment::NamedAddressResult
MemorySegmentLocal::getNamedAddressImpl(const char* name) const {
    std::map<std::string, void*>::const_iterator found =
        named_addrs_.find(name);
    if (found != named_addrs_.end()) {
        return (NamedAddressResult(true, found->second));
    }
    return (NamedAddressResult(false, NULL));
}

bool
MemorySegmentLocal::setNamedAddressImpl(const char* name, void* addr) {
    named_addrs_[name] = addr;
    return (false);
}

bool
MemorySegmentLocal::clearNamedAddressImpl(const char* name) {
    const size_t n_erased = named_addrs_.erase(name);
    return (n_erased != 0);
}

} // namespace util
} // namespace isc
