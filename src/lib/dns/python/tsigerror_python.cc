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

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

// Import pydoc text
#include "tsigerror_python_inc.cc"

namespace {
// The s_* Class simply covers one instantiation of the object
class s_TSIGError : public PyObject {
public:
    s_TSIGError() : cppobj(NULL) {};
    const TSIGError* cppobj;
};

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
      TSIGError_getCode_doc },
    { "to_text", reinterpret_cast<PyCFunction>(TSIGError_toText), METH_NOARGS,
      TSIGError_toText_doc },
    { "to_rcode", reinterpret_cast<PyCFunction>(TSIGError_toRcode),
      METH_NOARGS,
      TSIGError_toRcode_doc },
    { NULL, NULL, 0, NULL }
};

int
TSIGError_init(s_TSIGError* self, PyObject* args) {
    try {
        // Constructor from the code value
        long code = 0;
        if (PyArg_ParseTuple(args, "l", &code)) {
            if (code < 0 || code > 0xffff) {
                PyErr_SetString(PyExc_ValueError, "TSIG error out of range");
                return (-1);
            }
            self->cppobj = new TSIGError(code);
            return (0);
        }

        // Constructor from Rcode
        PyErr_Clear();
        PyObject* py_rcode;
        if (PyArg_ParseTuple(args, "O!", &rcode_type, &py_rcode)) {
            self->cppobj = new TSIGError(PyRcode_ToRcode(py_rcode));
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
    try {
        return (createRcodeObject(self->cppobj->toRcode()));
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
    "pydnspp.TSIGError",
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
    TSIGError_doc,
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

PyObject*
createTSIGErrorObject(const TSIGError& source) {
    TSIGErrorContainer container(PyObject_New(s_TSIGError, &tsigerror_type));
    container.set(new TSIGError(source));
    return (container.release());
}
} // namespace python
} // namespace dns
} // namespace isc
