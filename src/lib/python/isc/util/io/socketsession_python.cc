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

#include "socketsessionreceiver_python.h"
#include "socketsessionforwarder_python.h"

using namespace isc::util::io::python;
using namespace isc::util::python;

#include "socketsession_inc.cc"

namespace isc {
namespace util {
namespace io {
namespace python {
PyObject* po_SocketSessionError;
}
}
}
}

namespace {

PyModuleDef socketsession = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "isc.util.io.socketsession",
    socketsession_doc,
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};
} // end of unnamed namespace

PyMODINIT_FUNC
PyInit_socketsession(void) {
    PyObject* mod = PyModule_Create(&socketsession);
    if (mod == NULL) {
        return (NULL);
    }

    try {
        po_SocketSessionError =
            PyErr_NewException("isc.util.io.SocketSessionError", NULL, NULL);
        PyObjectContainer(po_SocketSessionError).
            installToModule(mod, "SocketSessionError");
    } catch (...) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_SocketSessionForwarder(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }
    if (!initModulePart_SocketSessionReceiver(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    return (mod);
}
