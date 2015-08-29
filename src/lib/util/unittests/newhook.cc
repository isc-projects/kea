// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <stdlib.h>

#include <new>
#include <stdexcept>

#include <util/unittests/newhook.h>

#ifdef ENABLE_CUSTOM_OPERATOR_NEW
void*
operator new(size_t size) throw(std::bad_alloc) {
    if (isc::util::unittests::force_throw_on_new &&
        size == isc::util::unittests::throw_size_on_new) {
        throw std::bad_alloc();
    }
    void* p = malloc(size);
    if (p == NULL) {
        throw std::bad_alloc();
    }
    return (p);
}

void
operator delete(void* p) throw() {
    if (p != NULL) {
        free(p);
    }
}
#endif

namespace isc {
namespace util {
namespace unittests {
bool force_throw_on_new = false;
size_t throw_size_on_new = 0;
}
}
}
