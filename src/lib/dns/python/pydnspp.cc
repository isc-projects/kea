// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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


// We want a lot of different parts of the DNS API in the python
// module, but not one big 10000-line file.
// So we split it up in several 'mini-modules'
// These would be the same as a single module, except for
// the init function, which has to be modified to a unique
// name initModulePart_<name>, and return true/false instead of
// NULL/*mod
//
// And of course care has to be taken that all identifiers be unique

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include "pydnspp_common.h"
/* Note that we do forward declarations of the initialization functions here,
 * and these are not defined in headers (since they are not to be used in any
 * other place */
namespace isc {
namespace dns {
namespace python {
namespace internal {

bool initModulePart_EDNS(PyObject* mod);
bool initModulePart_Message(PyObject* mod);
bool initModulePart_MessageRenderer(PyObject* mod);
bool initModulePart_Name(PyObject* mod);
bool initModulePart_Opcode(PyObject* mod);
bool initModulePart_Question(PyObject* mod);
bool initModulePart_Rcode(PyObject* mod);
bool initModulePart_Rdata(PyObject* mod);
bool initModulePart_RRClass(PyObject* mod);
bool initModulePart_RRset(PyObject* mod);
bool initModulePart_RRTTL(PyObject* mod);
bool initModulePart_RRType(PyObject* mod);
bool initModulePart_TSIGError(PyObject* mod);
bool initModulePart_TSIGKey(PyObject* mod);
bool initModulePart_TSIGKeyRing(PyObject* mod);
bool initModulePart_TSIGContext(PyObject* mod);
bool initModulePart_TSIG(PyObject* mod);
bool initModulePart_TSIGRecord(PyObject* mod);

}
} // namespace python
} // namespace dns
} // namespace isc


using namespace isc::dns::python;
using namespace isc::dns::python::internal;

//
// Definition of the module
//
namespace {
PyModuleDef pydnspp = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "pydnspp",
    "Python bindings for the classes in the isc::dns namespace.\n\n"
    "These bindings match the original C++ API as closely as possible, "
    "but are not complete. Some classes are unnecessary (InputBuffer "
    "and OutputBuffer for instance), and others may be necessary, but "
    "were not up to now.",
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};
}

PyMODINIT_FUNC
PyInit_pydnspp(void) {
    PyObject* mod = PyModule_Create(&pydnspp);
    if (mod == NULL) {
        return (NULL);
    }

    // Add the exceptions to the class
    po_IscException = PyErr_NewException("pydnspp.IscException", NULL, NULL);
    PyModule_AddObject(mod, "IscException", po_IscException);

    po_InvalidParameter = PyErr_NewException("pydnspp.InvalidParameter",
                                             NULL, NULL);
    PyModule_AddObject(mod, "InvalidParameter", po_InvalidParameter);

    // for each part included above, we call its specific initializer

    if (!initModulePart_Name(mod)) {
        return (NULL);
    }

    if (!initModulePart_MessageRenderer(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRClass(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRType(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRTTL(mod)) {
        return (NULL);
    }

    if (!initModulePart_Rdata(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRset(mod)) {
        return (NULL);
    }

    if (!initModulePart_Question(mod)) {
        return (NULL);
    }

    if (!initModulePart_Opcode(mod)) {
        return (NULL);
    }

    if (!initModulePart_Rcode(mod)) {
        return (NULL);
    }

    if (!initModulePart_Message(mod)) {
        return (NULL);
    }

    if (!initModulePart_EDNS(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGKey(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGKeyRing(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIG(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGError(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGRecord(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGContext(mod)) {
        return (NULL);
    }

    return (mod);
}
