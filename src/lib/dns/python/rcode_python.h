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

#ifndef __PYTHON_RCODE_H
#define __PYTHON_RCODE_H 1

#include <Python.h>

#include <dns/rcode.h>

namespace isc {
namespace dns {
namespace python {

// The s_* Class simply covers one instantiation of the object.
//
// We added a helper variable static_code here
// Since we can create Rcodes dynamically with Rcode(int), but also
// use the static globals (Rcode::NOERROR() etc), we use this
// variable to see if the code came from one of the latter, in which
// case Rcode_destroy should not free it (the other option is to
// allocate new Rcodes for every use of the static ones, but this
// seems more efficient).
//
// Follow-up note: we don't have to use the proxy function in the python lib;
// we can just define class specific constants directly (see TSIGError).
// We should make this cleanup later.
class s_Rcode : public PyObject {
public:
    s_Rcode();
    const Rcode* cppobj;
    bool static_code;
};

extern PyTypeObject rcode_type;

} // namespace python
} // namespace dns
} // namespace isc
#endif // __PYTHON_RCODE_H

// Local Variables:
// mode: c++
// End:
