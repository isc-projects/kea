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

#include <Python.h>

#include <stdexcept>
#include <boost/shared_ptr.hpp>

#include <util/python/pycppwrapper_util.h>

#include <cc/data.h>

#include <acl/acl.h>
#include <acl/dns.h>

#include "dns.h"
#include "dns_requestcontext_python.h"
#include "dns_requestacl_python.h"
#include "dns_requestloader_python.h"

using namespace std;
using boost::shared_ptr;
using namespace isc::util::python;
using namespace isc::data;
using namespace isc::acl::dns;
using namespace isc::acl::dns::python;

#include "dnsacl_inc.cc"

namespace {
// This is a Python binding object corresponding to the singleton loader used
// in the C++ version of the library.
// We can define it as a pure object rather than through an accessor function,
// because in Python we can ensure it has been created and initialized
// in the module initializer by the time it's actually used.
s_RequestLoader* po_REQUEST_LOADER;

PyMethodDef methods[] = {
    { NULL, NULL, 0, NULL }
};

PyModuleDef dnsacl = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "isc.acl._dns",
    dnsacl_doc,
    -1,
    methods,
    NULL,
    NULL,
    NULL,
    NULL
};
} // end of unnamed namespace

namespace isc {
namespace acl {
namespace dns {
namespace python {
PyObject*
getACLException(const char* ex_name) {
    PyObject* ex_obj = NULL;

    PyObject* acl_module = PyImport_AddModule("isc.acl.acl");
    if (acl_module != NULL) {
        PyObject* acl_dict = PyModule_GetDict(acl_module);
        if (acl_dict != NULL) {
            ex_obj = PyDict_GetItemString(acl_dict, ex_name);
        }
    }

    if (ex_obj == NULL) {
        ex_obj = PyExc_RuntimeError;
    }
    return (ex_obj);
}
}
}
}
}

PyMODINIT_FUNC
PyInit__dns(void) {
    PyObject* mod = PyModule_Create(&dnsacl);
    if (mod == NULL) {
        return (NULL);
    }

    if (!initModulePart_RequestContext(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }
    if (!initModulePart_RequestACL(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }
    if (!initModulePart_RequestLoader(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    // Module constants
    try {
        if (po_REQUEST_LOADER == NULL) {
            po_REQUEST_LOADER = static_cast<s_RequestLoader*>(
                requestloader_type.tp_alloc(&requestloader_type, 0));
        }
        if (po_REQUEST_LOADER != NULL) {
            // We gain and keep our own reference to the singleton object
            // for the same reason as that for exception objects (see comments
            // in pycppwrapper_util for more details).  Note also that we don't
            // bother to release the reference even if exception is thrown
            // below (in fact, we cannot delete the singleton loader).
            po_REQUEST_LOADER->cppobj = &getRequestLoader();
            Py_INCREF(po_REQUEST_LOADER);
        }
        PyObjectContainer(po_REQUEST_LOADER).installToModule(mod,
                                                             "REQUEST_LOADER");
    } catch (...) {
        Py_DECREF(mod);
        return (NULL);
    }

    return (mod);
}
