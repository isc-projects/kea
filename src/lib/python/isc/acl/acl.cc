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

#include <util/python/pycppwrapper_util.h>

#include <acl/acl.h>

using namespace isc::util::python;

#include "acl_inc.cc"

namespace {
// Commonly used Python exception objects.  Right now the acl module consists
// of only one .cc file, so we hide them in an unnamed namespace.  If and when
// we extend this module with multiple .cc files, we should move them to
// a named namespace, say isc::acl::python, and declare them in a separate
// header file.
PyObject* po_ACLError;
PyObject* po_LoaderError;
}

namespace {
PyModuleDef acl = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "isc.acl.acl",
    acl_doc,
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};
} // end of unnamed namespace

PyMODINIT_FUNC
PyInit_acl(void) {
    PyObject* mod = PyModule_Create(&acl);
    if (mod == NULL) {
        return (NULL);
    }

    try {
        po_ACLError = PyErr_NewException("isc.acl.Error", NULL, NULL);
        PyObjectContainer(po_ACLError).installToModule(mod, "Error");

        po_LoaderError = PyErr_NewException("isc.acl.LoaderError", NULL, NULL);
        PyObjectContainer(po_LoaderError).installToModule(mod, "LoaderError");

        // Install module constants.  Note that we can let Py_BuildValue
        // "steal" the references to these object (by specifying false to
        // installToModule), because, unlike the exception cases above,
        // we don't have corresponding C++ variables (see the note in
        // pycppwrapper_util for more details).
        PyObjectContainer(Py_BuildValue("I", isc::acl::ACCEPT)).
            installToModule(mod, "ACCEPT", false);
        PyObjectContainer(Py_BuildValue("I", isc::acl::REJECT)).
            installToModule(mod, "REJECT", false);
        PyObjectContainer(Py_BuildValue("I", isc::acl::DROP)).
            installToModule(mod, "DROP", false);
    } catch (...) {
        Py_DECREF(mod);
        return (NULL);
    }

    return (mod);
}
