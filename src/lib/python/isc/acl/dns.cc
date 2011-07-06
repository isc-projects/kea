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

#include "dns_requestacl_python.h"

using namespace std;
using boost::shared_ptr;
using namespace isc::util::python;
using namespace isc::data;
using namespace isc::acl::dns;
using namespace isc::acl::dns::python;

namespace {
PyObject* po_dns_LoaderError;

PyObject*
loadRequestACL(PyObject*, PyObject* args) {
    const char* acl_config;

    if (PyArg_ParseTuple(args, "s", &acl_config)) {
        try {
            shared_ptr<RequestACL> acl(
                getRequestLoader().load(Element::fromJSON(acl_config)));
            s_RequestACL* py_acl = static_cast<s_RequestACL*>(
                requestacl_type.tp_alloc(&requestacl_type, 0));
            if (py_acl != NULL) {
                py_acl->cppobj = acl;
            }
            return (py_acl);
        } catch (const exception& ex) {
            PyErr_SetString(po_dns_LoaderError, ex.what());
            return (NULL);
        } catch (...) {
            PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
            return (NULL);
        }
    }

    return (NULL);
}

PyMethodDef methods[] = {
    { "load_request_acl", loadRequestACL, METH_VARARGS, "TBD" },
    { NULL, NULL, 0, NULL }
};

PyModuleDef dnsacl = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "isc.acl.dns",
    "This module provides Python bindings for the C++ classes in the "
    "isc::acl::dns namespace.  Specifically, it defines Python interfaces of "
    "handling access control lists (ACLs) with DNS related contexts.\n\n"
    "These bindings are close match to the C++ API, but they are not complete "
    "(some parts are not needed) and some are done in more python-like ways.",
    -1,
    methods,
    NULL,
    NULL,
    NULL,
    NULL
};
} // end of unnamed namespace

PyMODINIT_FUNC
PyInit_dns(void) {
    PyObject* mod = PyModule_Create(&dnsacl);
    if (mod == NULL) {
        return (NULL);
    }

    try {
        po_dns_LoaderError = PyErr_NewException("isc.acl.dns.LoaderError",
                                                NULL, NULL);
        PyObjectContainer(po_dns_LoaderError).installToModule(mod,
                                                              "LoaderError");
    } catch (...) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_RequestACL(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    return (mod);
}
