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

#ifndef __PYTHON_DATASRC_ITERATOR_H
#define __PYTHON_DATASRC_ITERATOR_H 1

#include <Python.h>

namespace isc {
namespace datasrc {
class DataSourceClient;

namespace python {

// The s_* Class simply covers one instantiation of the object
class s_ZoneIterator : public PyObject {
public:
    s_ZoneIterator();
    ZoneIteratorPtr cppobj;
};

extern PyTypeObject zoneiterator_type;

bool initModulePart_ZoneIterator(PyObject* mod);

PyObject* createZoneIteratorObject(isc::datasrc::ZoneIteratorPtr source);


} // namespace python
} // namespace datasrc
} // namespace isc
#endif // __PYTHON_DATASRC_ITERATOR_H

// Local Variables:
// mode: c++
// End:
