// Copyright (C) @YEAR@  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PYTHON_@CPPCLASS@_H
#define PYTHON_@CPPCLASS@_H 1

#include <Python.h>

namespace isc {
namespace @MODULE@ {
class @CPPCLASS@;

namespace python {

// The s_* Class simply covers one instantiation of the object
class s_@CPPCLASS@ : public PyObject {
public:
    s_@CPPCLASS@();
    @CPPCLASS@* cppobj;
};

extern PyTypeObject @cppclass@_type;

bool initModulePart_@CPPCLASS@(PyObject* mod);

// Note: this utility function works only when @CPPCLASS@ is a copy
// constructable.
// And, it would only be useful when python binding needs to create this
// object frequently.  Otherwise, it would (or should) probably be better to
// remove the declaration and definition of this function.
//
/// This is a simple shortcut to create a python @CPPCLASS@ object (in the
/// form of a pointer to PyObject) with minimal exception safety.
/// On success, it returns a valid pointer to PyObject with a reference
/// counter of 1; if something goes wrong it throws an exception (it never
/// returns a NULL pointer).
/// This function is expected to be called within a try block
/// followed by necessary setup for python exception.
PyObject* create@CPPCLASS@Object(const @CPPCLASS@& source);

} // namespace python
} // namespace @MODULE@
} // namespace isc
#endif // PYTHON_@CPPCLASS@_H

// Local Variables:
// mode: c++
// End:
