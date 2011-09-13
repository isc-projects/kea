// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __PYTHON_TSIGERROR_H
#define __PYTHON_TSIGERROR_H 1

#include <Python.h>

#include <dns/tsigerror.h>

namespace isc {
namespace dns {
namespace python {

// The s_* Class simply covers one instantiation of the object
class s_TSIGError : public PyObject {
public:
    s_TSIGError();
    const TSIGError* cppobj;
};

extern PyTypeObject tsigerror_type;

bool initModulePart_TSIGError(PyObject* mod);

/// This is A simple shortcut to create a python TSIGError object (in the
/// form of a pointer to PyObject) with minimal exception safety.
/// On success, it returns a valid pointer to PyObject with a reference
/// counter of 1; if something goes wrong it throws an exception (it never
/// returns a NULL pointer).
/// This function is expected to be called with in a try block
/// followed by necessary setup for python exception.
PyObject* createTSIGErrorObject(const TSIGError& source);
} // namespace python
} // namespace dns
} // namespace isc
#endif // __PYTHON_TSIGERROR_H

// Local Variables:
// mode: c++
// End:
