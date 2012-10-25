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

#ifndef PYTHON_RRSET_H
#define PYTHON_RRSET_H 1

#include <Python.h>

#include <dns/rrset.h>

#include <util/python/pycppwrapper_util.h>

namespace isc {
namespace dns {
namespace python {

extern PyObject* po_EmptyRRset;

extern PyTypeObject rrset_type;

/// This is a simple shortcut to create a python RRset object (in the
/// form of a pointer to PyObject) with minimal exception safety.
/// On success, it returns a valid pointer to PyObject with a reference
/// counter of 1; if something goes wrong it throws an exception (it never
/// returns a NULL pointer).
/// This function is expected to be called within a try block
/// followed by necessary setup for python exception.
PyObject* createRRsetObject(const AbstractRRset& source);

/// \brief Checks if the given python object is a RRset object
///
/// \exception PyCPPWrapperException if obj is NULL
///
/// \param obj The object to check the type of
/// \return true if the object is of type RRset, false otherwise
bool PyRRset_Check(PyObject* obj);

/// \brief Returns a reference to the RRset object contained within the given
///        Python object.
///
/// \note The given object MUST be of type RRset; this can be checked with
///       either the right call to ParseTuple("O!"), or with PyRRset_Check()
///
/// \note This is not a copy; if the RRset is needed when the PyObject
/// may be destroyed, the caller must copy it itself.
///
/// \param rrset_obj The rrset object to convert
AbstractRRset& PyRRset_ToRRset(PyObject* rrset_obj);

/// \brief Returns the shared_ptr of the RRset object contained within the
///        given Python object.
///
/// \note The given object MUST be of type RRset; this can be checked with
///       either the right call to ParseTuple("O!"), or with PyRRset_Check()
///
/// \param rrset_obj The rrset object to convert
RRsetPtr PyRRset_ToRRsetPtr(PyObject* rrset_obj);


} // namespace python
} // namespace dns
} // namespace isc
#endif // PYTHON_RRSET_H

// Local Variables:
// mode: c++
// End:
