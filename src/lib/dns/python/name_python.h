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

#ifndef PYTHON_NAME_H
#define PYTHON_NAME_H 1

#include <Python.h>

namespace isc {
namespace dns {
class Name;

namespace python {

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

extern PyTypeObject name_comparison_result_type;
extern PyTypeObject name_type;

/// This is A simple shortcut to create a python Name object (in the
/// form of a pointer to PyObject) with minimal exception safety.
/// On success, it returns a valid pointer to PyObject with a reference
/// counter of 1; if something goes wrong it throws an exception (it never
/// returns a NULL pointer).
/// This function is expected to be called with in a try block
/// followed by necessary setup for python exception.
PyObject* createNameObject(const Name& source);

/// \brief Checks if the given python object is a Name object
///
/// \exception PyCPPWrapperException if obj is NULL
///
/// \param obj The object to check the type of
/// \return true if the object is of type Name, false otherwise
bool PyName_Check(PyObject* obj);

/// \brief Returns a reference to the Name object contained within the given
///        Python object.
///
/// \note The given object MUST be of type Name; this can be checked with
///       either the right call to ParseTuple("O!"), or with PyName_Check()
///
/// \note This is not a copy; if the Name is needed when the PyObject
/// may be destroyed, the caller must copy it itself.
///
/// \param name_obj The name object to convert
const Name& PyName_ToName(const PyObject* name_obj);

} // namespace python
} // namespace dns
} // namespace isc
#endif // PYTHON_NAME_H

// Local Variables:
// mode: c++
// End:
