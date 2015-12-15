// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
