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

#ifndef PYTHON_REQUESTACL_H
#define PYTHON_REQUESTACL_H 1

#include <Python.h>

#include <boost/shared_ptr.hpp>

#include <acl/dns.h>

namespace isc {
namespace acl {
namespace dns {
namespace python {

// The s_* Class simply covers one instantiation of the object
class s_RequestACL : public PyObject {
public:
    s_RequestACL();

    // We don't have to use a shared pointer for its original purposes as
    // the python object maintains reference counters itself.  But the
    // underlying C++ API only exposes a shared pointer for the ACL objects,
    // so we store it in that form.
    boost::shared_ptr<RequestACL> cppobj;
};

extern PyTypeObject requestacl_type;

bool initModulePart_RequestACL(PyObject* mod);

} // namespace python
} // namespace dns
} // namespace acl
} // namespace isc
#endif // PYTHON_REQUESTACL_H

// Local Variables:
// mode: c++
// End:
