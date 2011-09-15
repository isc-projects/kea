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

#ifndef __PYTHON_EDNS_H
#define __PYTHON_EDNS_H 1

#include <Python.h>

#include <dns/edns.h>

namespace isc {
namespace dns {
namespace python {

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the module init at the
// end
//
class s_EDNS : public PyObject {
public:
    EDNS* cppobj;
};

extern PyTypeObject edns_type;

} // namespace python
} // namespace dns
} // namespace isc
#endif // __PYTHON_EDNS_H

// Local Variables:
// mode: c++
// End:
