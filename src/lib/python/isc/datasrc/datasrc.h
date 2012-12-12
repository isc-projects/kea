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

#ifndef PYTHON_DATASRC_H
#define PYTHON_DATASRC_H 1

#include <Python.h>

namespace isc {
namespace datasrc {
namespace python {

// Return a Python exception object of the given name (ex_name) defined in
// the isc.datasrc.datasrc loadable module.
//
// Since the datasrc module is a different binary image and is loaded separately
// from the dns module, it would be very tricky to directly access to
// C/C++ symbols defined in that module.  So we get access to these object
// using the Python interpretor through this wrapper function.
//
// The __init__.py file should ensure isc.datasrc has been loaded by the time
// whenever this function is called, and there shouldn't be any operation
// within this function that can fail (such as dynamic memory allocation),
// so this function should always succeed.  Yet there may be an overlooked
// failure mode, perhaps due to a bug in the binding implementation, or
// due to invalid usage.  As a last resort for such cases, this function
// returns PyExc_RuntimeError (a C binding of Python's RuntimeError) should
// it encounters an unexpected failure.
extern PyObject* getDataSourceException(const char* ex_name);

} // namespace python
} // namespace datasrc
} // namespace isc

#endif // PYTHON_DATASRC_H

// Local Variables:
// mode: c++
// End:
