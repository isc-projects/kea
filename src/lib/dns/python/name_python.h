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

#ifndef __PYTHON_NAME_H
#define __PYTHON_NAME_H 1

#include <Python.h>

#include <util/python/pycppwrapper_util.h>

namespace isc {
namespace dns {
class NameComparisonResult;
class Name;

namespace python {

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the module init at the
// end
//
extern PyObject* po_EmptyLabel;
extern PyObject* po_TooLongName;
extern PyObject* po_TooLongLabel;
extern PyObject* po_BadLabelType;
extern PyObject* po_BadEscape;
extern PyObject* po_IncompleteName;
extern PyObject* po_InvalidBufferPosition;
extern PyObject* po_DNSMessageFORMERR;

//
// Declaration of enums
// Initialization and addition of these go in the module init at the
// end
//
extern PyObject* po_NameRelation;

// The s_* Class simply covers one instantiation of the object.
class s_NameComparisonResult : public PyObject {
public:
    s_NameComparisonResult() : cppobj(NULL) {}
    NameComparisonResult* cppobj;
};

class s_Name : public PyObject {
public:
    s_Name() : cppobj(NULL), position(0) {}
    Name* cppobj;
    size_t position;
};

extern PyTypeObject name_comparison_result_type;
extern PyTypeObject name_type;

bool initModulePart_Name(PyObject* mod);

/// This is A simple shortcut to create a python Name object (in the
/// form of a pointer to PyObject) with minimal exception safety.
/// On success, it returns a valid pointer to PyObject with a reference
/// counter of 1; if something goes wrong it throws an exception (it never
/// returns a NULL pointer).
/// This function is expected to be called with in a try block
/// followed by necessary setup for python exception.
PyObject* createNameObject(const Name& source);
} // namespace python
} // namespace dns
} // namespace isc
#endif // __PYTHON_NAME_H

// Local Variables:
// mode: c++
// End:
