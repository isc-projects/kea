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

#ifndef TEST_LIBRARIES_H
#define TEST_LIBRARIES_H

#include <config.h>

namespace {


// Take care of differences in DLL naming between operating systems.

#ifdef OS_OSX
#define DLL_SUFFIX ".dylib"

#else
#define DLL_SUFFIX ".so"

#endif


// Names of the libraries used in these tests.  These libraries are built using
// libtool, so we need to look in the hidden ".libs" directory to locate the
// shared library.

// Library with load/unload functions creating marker files to check their
// operation.
static const char* CALLOUT_LIBRARY_1 = "/home/thomson/devel/bind10/src/lib/dhcpsrv/tests/.libs/libco1"
                                           DLL_SUFFIX;
static const char* CALLOUT_LIBRARY_2 = "/home/thomson/devel/bind10/src/lib/dhcpsrv/tests/.libs/libco2"
                                           DLL_SUFFIX;

// Name of a library which is not present.
static const char* NOT_PRESENT_LIBRARY = "/home/thomson/devel/bind10/src/lib/dhcpsrv/tests/.libs/libnothere"
                                         DLL_SUFFIX;
} // anonymous namespace


#endif // TEST_LIBRARIES_H
