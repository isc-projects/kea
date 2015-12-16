// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
