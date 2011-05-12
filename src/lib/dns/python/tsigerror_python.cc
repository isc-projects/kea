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

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <dns/tsigerror.h>

#include "pydnspp_common.h"
#include "rcode_python.h"
#include "tsigerror_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns;
using namespace isc::dns::python;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// TSIGError
//

// Trivial constructor.
s_TSIGError::s_TSIGError() : cppobj(NULL) {
}

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_TSIGError, TSIGError> TSIGErrorContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int TSIGError_init(s_TSIGError* self, PyObject* args);
void TSIGError_destroy(s_TSIGError* self);

// These are the functions we export
PyObject* TSIGError_getCode(const s_TSIGError* const self);
PyObject* TSIGError_toText(const s_TSIGError* const self);
PyObject* TSIGError_toRcode(const s_TSIGError* const self);
PyObject* TSIGError_str(PyObject* self);
PyObject* TSIGError_richcmp(const s_TSIGError* const self,
                            const s_TSIGError* const other, int op);

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef TSIGError_methods[] = {
    { "get_code", reinterpret_cast<PyCFunction>(TSIGError_getCode),
      METH_NOARGS,
      "Returns the code value" },
    { "to_text", reinterpret_cast<PyCFunction>(TSIGError_toText), METH_NOARGS,
      "Returns the text representation" },
    { "to_rcode", reinterpret_cast<PyCFunction>(TSIGError_toRcode),
      METH_NOARGS,
      "Convert the TSIGError to a Rcode" },
    { NULL, NULL, 0, NULL }
};

int
TSIGError_init(s_TSIGError* self, PyObject* args) {
    try {
        long code = 0;
        if (PyArg_ParseTuple(args, "l", &code)) {
            if (code < 0 || code > 0xffff) {
                PyErr_SetString(PyExc_ValueError, "TSIG error out of range");
                return (-1);
            }
            self->cppobj = new TSIGError(code);
            return (0);
        }

        PyErr_Clear();
        s_Rcode* py_rcode;
        if (PyArg_ParseTuple(args, "O!", &rcode_type, &py_rcode)) {
            self->cppobj = new TSIGError(*py_rcode->cppobj);
            return (0);
        }
    } catch (const isc::OutOfRange& ex) {
        const string ex_what = "Failed to construct TSIGError object: " +
            string(ex.what());
        PyErr_SetString(PyExc_ValueError, ex_what.c_str());
        return (-1);
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct TSIGError object: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in constructing TSIGError");
        return (-1);
    }

    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to TSIGError constructor");

    return (-1);
}

void
TSIGError_destroy(s_TSIGError* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
TSIGError_getCode(const s_TSIGError* const self) {
    return (Py_BuildValue("I", self->cppobj->getCode()));
}

PyObject*
TSIGError_toText(const s_TSIGError* const self) {
    try {
        // toText() could throw, so we need to catch any exceptions below.
        return (Py_BuildValue("s", self->cppobj->toText().c_str()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to convert TSIGError object to text: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "converting TSIGError object to text");
    }
    return (NULL);
}

PyObject*
TSIGError_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self, const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
TSIGError_toRcode(const s_TSIGError* const self) {
    typedef CPPPyObjectContainer<s_Rcode, Rcode> RcodePyObjectContainer;

    try {
        RcodePyObjectContainer rcode_container(PyObject_New(s_Rcode,
                                                            &rcode_type));
        rcode_container.set(new Rcode(self->cppobj->toRcode()));
        return (rcode_container.release());
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to convert TSIGError to Rcode: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "converting TSIGError to Rcode");
    }
    return (NULL);
}

PyObject* 
TSIGError_richcmp(const s_TSIGError* const self,
                   const s_TSIGError* const other,
                   const int op)
{
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (other == NULL || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; TSIGError");
        return (NULL);
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; TSIGError");
        return (NULL);
    case Py_EQ:
        c = (*self->cppobj == *other->cppobj);
        break;
    case Py_NE:
        c = (*self->cppobj != *other->cppobj);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; TSIGError");
        return (NULL);
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; TSIGError");
        return (NULL);
    }
    if (c) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}
} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_TSIGError
// Most of the functions are not actually implemented and NULL here.
PyTypeObject tsigerror_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.TSIGError",
    sizeof(s_TSIGError),                 // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(TSIGError_destroy),       // tp_dealloc
    NULL,                               // tp_print
    NULL,                               // tp_getattr
    NULL,                               // tp_setattr
    NULL,                               // tp_reserved
    NULL,                               // tp_repr
    NULL,                               // tp_as_number
    NULL,                               // tp_as_sequence
    NULL,                               // tp_as_mapping
    NULL,                               // tp_hash 
    NULL,                               // tp_call
    // THIS MAY HAVE TO BE CHANGED TO NULL:
    TSIGError_str,                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The TSIGError class objects represent standard errors related to "
    "TSIG protocol operations as defined in related specifications, mainly "
    "in RFC2845.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    // THIS MAY HAVE TO BE CHANGED TO NULL:
    reinterpret_cast<richcmpfunc>(TSIGError_richcmp), // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    TSIGError_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(TSIGError_init),            // tp_init
    NULL,                               // tp_alloc
    PyType_GenericNew,                  // tp_new
    NULL,                               // tp_free
    NULL,                               // tp_is_gc
    NULL,                               // tp_bases
    NULL,                               // tp_mro
    NULL,                               // tp_cache
    NULL,                               // tp_subclasses
    NULL,                               // tp_weaklist
    NULL,                               // tp_del
    0                                   // tp_version_tag
};

namespace {
// Trivial shortcut to create and install TSIGError constants.
inline void
installTSIGErrorConstant(const char* name, const TSIGError& val) {
    TSIGErrorContainer container(PyObject_New(s_TSIGError, &tsigerror_type));
    container.installAsClassVariable(tsigerror_type, name, new TSIGError(val));
}
}

// Module Initialization, all statics are initialized here
bool
initModulePart_TSIGError(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&tsigerror_type) < 0) {
        return (false);
    }
    void* p = &tsigerror_type;
    if (PyModule_AddObject(mod, "TSIGError", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&tsigerror_type);

    try {
        // Constant class variables
        // Error codes (bare values)
        installClassVariable(tsigerror_type, "BAD_SIG_CODE",
                             Py_BuildValue("H", TSIGError::BAD_SIG_CODE));
        installClassVariable(tsigerror_type, "BAD_KEY_CODE",
                             Py_BuildValue("H", TSIGError::BAD_KEY_CODE));
        installClassVariable(tsigerror_type, "BAD_TIME_CODE",
                             Py_BuildValue("H", TSIGError::BAD_TIME_CODE));

        // Error codes (constant objects)
        installTSIGErrorConstant("NOERROR", TSIGError::NOERROR());
        installTSIGErrorConstant("FORMERR", TSIGError::FORMERR());
        installTSIGErrorConstant("SERVFAIL", TSIGError::SERVFAIL());
        installTSIGErrorConstant("NXDOMAIN", TSIGError::NXDOMAIN());
        installTSIGErrorConstant("NOTIMP", TSIGError::NOTIMP());
        installTSIGErrorConstant("REFUSED", TSIGError::REFUSED());
        installTSIGErrorConstant("YXDOMAIN", TSIGError::YXDOMAIN());
        installTSIGErrorConstant("YXRRSET", TSIGError::YXRRSET());
        installTSIGErrorConstant("NXRRSET", TSIGError::NXRRSET());
        installTSIGErrorConstant("NOTAUTH", TSIGError::NOTAUTH());
        installTSIGErrorConstant("NOTZONE", TSIGError::NOTZONE());
        installTSIGErrorConstant("RESERVED11", TSIGError::RESERVED11());
        installTSIGErrorConstant("RESERVED12", TSIGError::RESERVED12());
        installTSIGErrorConstant("RESERVED13", TSIGError::RESERVED13());
        installTSIGErrorConstant("RESERVED14", TSIGError::RESERVED14());
        installTSIGErrorConstant("RESERVED15", TSIGError::RESERVED15());
        installTSIGErrorConstant("BAD_SIG", TSIGError::BAD_SIG());
        installTSIGErrorConstant("BAD_KEY", TSIGError::BAD_KEY());
        installTSIGErrorConstant("BAD_TIME", TSIGError::BAD_TIME());
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure in TSIGError initialization: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in TSIGError initialization");
        return (false);
    }

    return (true);
}

PyObject*
createTSIGErrorObject(const TSIGError& source) {
    TSIGErrorContainer container = PyObject_New(s_TSIGError, &tsigerror_type);
    container.set(new TSIGError(source));
    return (container.release());
}
} // namespace python
} // namespace dns
} // namespace isc
