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

#define PY_SSIZE_T_CLEAN        // need for "y#" below
#include <Python.h>

#include <string>
#include <stdexcept>

#include <exceptions/exceptions.h>

#include <util/python/pycppwrapper_util.h>

#include <dns/tsig.h>

#include "pydnspp_common.h"
#include "name_python.h"
#include "tsigkey_python.h"
#include "tsigerror_python.h"
#include "tsigrecord_python.h"
#include "tsig_python.h"

using namespace std;
using namespace isc;
using namespace isc::util::python;
using namespace isc::dns;
using namespace isc::dns::python;

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

namespace {
// The s_* Class simply covers one instantiation of the object
class s_TSIGContext : public PyObject {
public:
    s_TSIGContext() : cppobj(NULL) {};
    TSIGContext* cppobj;
};

// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_TSIGContext, TSIGContext> TSIGContextContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int TSIGContext_init(s_TSIGContext* self, PyObject* args);
void TSIGContext_destroy(s_TSIGContext* self);

// Class specific methods
PyObject* TSIGContext_getState(s_TSIGContext* self);
PyObject* TSIGContext_getError(s_TSIGContext* self);
PyObject* TSIGContext_sign(s_TSIGContext* self, PyObject* args);
PyObject* TSIGContext_verify(s_TSIGContext* self, PyObject* args);
PyObject* TSIGContext_lastHadSignature(s_TSIGContext* self);

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef TSIGContext_methods[] = {
    { "get_state", reinterpret_cast<PyCFunction>(TSIGContext_getState),
      METH_NOARGS,
      "Return the current state of the context (mainly for tests)" },
    { "get_error", reinterpret_cast<PyCFunction>(TSIGContext_getError),
      METH_NOARGS,
      "Return the TSIG error as a result of the latest verification" },
    { "sign",
      reinterpret_cast<PyCFunction>(TSIGContext_sign), METH_VARARGS,
      "Sign a DNS message." },
    { "verify",
      reinterpret_cast<PyCFunction>(TSIGContext_verify), METH_VARARGS,
      "Verify a DNS message." },
    { "last_had_signature",
      reinterpret_cast<PyCFunction>(TSIGContext_lastHadSignature), METH_NOARGS,
      "Return if the last verified message contained a signature" },
    { NULL, NULL, 0, NULL }
};

int
TSIGContext_init(s_TSIGContext* self, PyObject* args) {
    try {
        // "From key" constructor
        const PyObject* tsigkey_obj;
        if (PyArg_ParseTuple(args, "O!", &tsigkey_type, &tsigkey_obj)) {
            self->cppobj = new TSIGContext(PyTSIGKey_ToTSIGKey(tsigkey_obj));
            return (0);
        }

        // "From key param + keyring" constructor
        PyErr_Clear();
        const PyObject* keyname_obj;
        const PyObject* algname_obj;
        const PyObject* keyring_obj;
        if (PyArg_ParseTuple(args, "O!O!O!", &name_type, &keyname_obj,
                             &name_type, &algname_obj, &tsigkeyring_type,
                             &keyring_obj)) {
            self->cppobj = new TSIGContext(PyName_ToName(keyname_obj),
                                           PyName_ToName(algname_obj),
                                           PyTSIGKeyRing_ToTSIGKeyRing(keyring_obj));
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct TSIGContext object: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in constructing TSIGContext");
        return (-1);
    }

    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to TSIGContext constructor");

    return (-1);
}

void
TSIGContext_destroy(s_TSIGContext* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
TSIGContext_getState(s_TSIGContext* self) {
    return (Py_BuildValue("I", self->cppobj->getState()));
}

PyObject*
TSIGContext_getError(s_TSIGContext* self) {
    try {
        PyObjectContainer container(createTSIGErrorObject(
                                    self->cppobj->getError()));
        return (Py_BuildValue("O", container.get()));
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpectedly failed to get TSIGContext error: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in TSIGContext.get_error");
    }
    return (NULL);
}

PyObject*
TSIGContext_sign(s_TSIGContext* self, PyObject* args) {
    long qid = 0;
    const char* mac;
    Py_ssize_t mac_size;

    if (PyArg_ParseTuple(args, "ly#", &qid, &mac, &mac_size)) {
        if (qid < 0 || qid > 0xffff) {
            PyErr_SetString(PyExc_ValueError,
                            "TSIGContext.sign: QID out of range");
            return (NULL);
        }

        try {
            ConstTSIGRecordPtr record = self->cppobj->sign(qid, mac, mac_size);
            return (createTSIGRecordObject(*record));
        } catch (const TSIGContextError& ex) {
            PyErr_SetString(po_TSIGContextError, ex.what());
        } catch (const exception& ex) {
            const string ex_what = "Unexpected failure in TSIG sign: " +
                string(ex.what());
            PyErr_SetString(po_IscException, ex_what.c_str());
        } catch (...) {
            PyErr_SetString(PyExc_SystemError,
                            "Unexpected failure in TSIG sign");
        }
    } else {
        PyErr_SetString(PyExc_TypeError,
                        "Invalid arguments to TSIGContext.sign");
    }

    return (NULL);
}

PyObject*
TSIGContext_verify(s_TSIGContext* self, PyObject* args) {
    const char* data;
    Py_ssize_t data_len;
    PyObject* py_record;
    PyObject* py_maybe_none;
    const TSIGRecord* record;

    if (PyArg_ParseTuple(args, "O!y#", &tsigrecord_type, &py_record,
                         &data, &data_len)) {
        record = &PyTSIGRecord_ToTSIGRecord(py_record);
    } else if (PyArg_ParseTuple(args, "Oy#", &py_maybe_none, &data,
                                &data_len)) {
        record = NULL;
    } else {
        PyErr_SetString(PyExc_TypeError,
                        "Invalid arguments to TSIGContext.verify");
        return (NULL);
    }
    PyErr_Clear();

    try {
        const TSIGError error = self->cppobj->verify(record, data, data_len);
        return (createTSIGErrorObject(error));
    } catch (const TSIGContextError& ex) {
        PyErr_SetString(po_TSIGContextError, ex.what());
    } catch (const InvalidParameter& ex) {
        PyErr_SetString(po_InvalidParameter, ex.what());
    } catch (const exception& ex) {
        const string ex_what = "Unexpected failure in TSIG verify: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in TSIG verify");
    }

    return (NULL);
}

PyObject*
TSIGContext_lastHadSignature(s_TSIGContext* self) {
    try {
        long result = self->cppobj->lastHadSignature();
        return (PyBool_FromLong(result));
    } catch (const TSIGContextError& ex) {
        PyErr_SetString(po_TSIGContextError, ex.what());
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure in TSIG lastHadSignature: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in TSIG lastHadSignature");
    }

    return (NULL);
}
} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
// Definition of class specific exception(s)
PyObject* po_TSIGContextError;

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_TSIGContext
// Most of the functions are not actually implemented and NULL here.
PyTypeObject tsigcontext_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.TSIGContext",
    sizeof(s_TSIGContext),                 // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(TSIGContext_destroy),       // tp_dealloc
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
    NULL,                               // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer

    // We allow the python version of TSIGContext to act as a base class.
    // From pure design point of view, this is wrong because it's not intended
    // to be inherited.  However, cryptographic operations are generally
    // difficult to test, so it would be very advantageous if we can define
    // a mock context class.
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE, // tp_flags

    "The TSIGContext class objects is...(COMPLETE THIS)",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL, // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    TSIGContext_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(TSIGContext_init),            // tp_init
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

bool
PyTSIGContext_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &tsigcontext_type));
}

TSIGContext&
PyTSIGContext_ToTSIGContext(PyObject* tsigcontext_obj) {
    if (tsigcontext_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in TSIGContext PyObject conversion");
    }
    s_TSIGContext* tsigcontext = static_cast<s_TSIGContext*>(tsigcontext_obj);
    return (*tsigcontext->cppobj);
}

} // namespace python
} // namespace dns
} // namespace isc
