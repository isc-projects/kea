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

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <config.h>

#include <datasrc/client.h>
#include <datasrc/database.h>
#include <datasrc/sqlite3_accessor.h>

#include "datasrc.h"
#include "client_python.h"
#include "finder_python.h"
#include "iterator_python.h"
#include "updater_python.h"

#include <util/python/pycppwrapper_util.h>

using namespace isc::datasrc::python;
using namespace isc::util::python;

namespace isc {
namespace datasrc {
namespace python {
PyObject*
getDataSourceException(const char* ex_name) {
    PyObject* ex_obj = NULL;

    PyObject* acl_module = PyImport_AddModule("isc.datasrc");
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

namespace internal {
bool initModulePart_DataSourceClient(PyObject* mod);
bool initModulePart_ZoneFinder(PyObject* mod);
bool initModulePart_ZoneIterator(PyObject* mod);
bool initModulePart_ZoneUpdater(PyObject* mod);
} // end namespace internal

} // end namespace python
} // end namespace datasrc
} // end namespace isc

namespace {

PyObject* po_DataSourceError;
PyObject* po_NotImplemented;

PyModuleDef iscDataSrc = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "datasrc",
    "Python bindings for the classes in the isc::datasrc namespace.\n\n"
    "These bindings are close match to the C++ API, but they are not complete "
    "(some parts are not needed) and some are done in more python-like ways.",
    -1,
    NULL,// TODO do we need module-level functions?
    NULL,
    NULL,
    NULL,
    NULL
};

} // end anonymous namespace

using namespace isc::datasrc::python::internal;

PyMODINIT_FUNC
PyInit_datasrc(void) {
    PyObject* mod = PyModule_Create(&iscDataSrc);
    if (mod == NULL) {
        return (NULL);
    }

    if (!initModulePart_DataSourceClient(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneFinder(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneIterator(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneUpdater(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    try {
        po_DataSourceError = PyErr_NewException("isc.datasrc.Error", NULL,
                                                NULL);
        PyObjectContainer(po_DataSourceError).installToModule(mod, "Error");
        po_NotImplemented = PyErr_NewException("isc.datasrc.NotImplemented",
                                               NULL, NULL);
        PyObjectContainer(po_NotImplemented).installToModule(mod,
                                                             "NotImplemented");
    } catch (...) {
        Py_DECREF(mod);
        return (NULL);
    }

    return (mod);
}
