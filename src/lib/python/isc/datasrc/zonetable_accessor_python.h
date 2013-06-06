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

#ifndef PYTHON_ZONETABLE_ACCESSOR_H
#define PYTHON_ZONETABLE_ACCESSOR_H 1

#include <Python.h>

namespace isc {
namespace datasrc {
namespace python {

extern PyTypeObject zonetableaccessor_type;

/// \brief Create a ZoneTableAccessor python object
///
/// \param source The zone iterator pointer to wrap
/// \param base_obj An optional PyObject that this ZoneFinder depends on
///                 Its refcount is increased, and will be decreased when
///                 this zone iterator is destroyed, making sure that the
///                 base object is never destroyed before this zonefinder.
PyObject* createZoneTableAccessorObject(
    isc::datasrc::ConstZoneTableAccessorPtr source, PyObject* base_obj);

} // namespace python
} // namespace datasrc
} // namespace isc
#endif // PYTHON_ZONETABLE_ACCESSOR_H

// Local Variables:
// mode: c++
// End:
