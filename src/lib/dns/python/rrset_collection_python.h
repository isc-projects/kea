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

#ifndef PYTHON_RRSETCOLLECTION_H
#define PYTHON_RRSETCOLLECTION_H 1

#include <Python.h>

namespace isc {
namespace dns {
class RRsetCollectionBase;

namespace python {

// The s_* Class simply covers one instantiation of the object.
// This structure will be commonly used for all derived classes of
// RRsetCollectionBase.  cppobj will point to an instance of the specific
// derived class of (C++) RRsetCollectionBase.
//
// A C++ wrapper for Python version of RRsetCollection should set this
// variable, and skip the implementation of C++ wrapper of find() method.
class s_RRsetCollection : public PyObject {
public:
    s_RRsetCollection() : cppobj(NULL) {}
    RRsetCollectionBase* cppobj;
};

// Python type information for RRsetCollectionBase
extern PyTypeObject rrset_collection_base_type;

// Python type information for dns.RRsetCollection
extern PyTypeObject rrset_collection_type;

// Class specific exceptions
extern PyObject* po_RRsetCollectionError;

bool initModulePart_RRsetCollectionBase(PyObject* mod);
bool initModulePart_RRsetCollection(PyObject* mod);

} // namespace python
} // namespace dns
} // namespace isc
#endif // PYTHON_RRSETCOLLECTION_H

// Local Variables:
// mode: c++
// End:
