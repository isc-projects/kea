// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

// Enable this if you use s# variants with PyArg_ParseTuple(), see
// http://docs.python.org/py3k/c-api/arg.html#strings-and-buffers
//#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <dns/nsec3hash.h>
#include <dns/rdataclass.h>

#include "pydnspp_common.h"
#include "name_python.h"
#include "nsec3hash_python.h"
#include "rdata_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::python;

// Import pydoc text
#include "nsec3hash_python_inc.cc"

// Trivial constructor.
s_NSEC3Hash::s_NSEC3Hash() : cppobj(NULL) {
}

namespace {
int
NSEC3Hash_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_NSEC3Hash* const self = static_cast<s_NSEC3Hash*>(po_self);
    try {
        PyObject* po_rdata;
        if (PyArg_ParseTuple(args, "O", &po_rdata)) {
            if (!PyRdata_Check(po_rdata)) {
                PyErr_Format(PyExc_TypeError,
                             "param must be an Rdata of type NSEC3/NSEC3PARAM,"
                             " not %.200s", po_rdata->ob_type->tp_name);
                return (-1);
            }
            const Rdata& rdata = PyRdata_ToRdata(po_rdata);
            const generic::NSEC3PARAM* nsec3param =
                dynamic_cast<const generic::NSEC3PARAM*>(&rdata);
            const generic::NSEC3* nsec3 =
                dynamic_cast<const generic::NSEC3*>(&rdata);
            if (nsec3param != NULL) {
                self->cppobj = NSEC3Hash::create(*nsec3param);
            } else if (nsec3 != NULL) {
                self->cppobj = NSEC3Hash::create(*nsec3);
            } else {
                PyErr_Format(PyExc_TypeError,
                             "param must be an Rdata of type NSEC3/NSEC3HASH");
                return (-1);
            }
            return (0);
        }
    } catch (const UnknownNSEC3HashAlgorithm& ex) {
        PyErr_SetString(po_UnknownNSEC3HashAlgorithm, ex.what());
        return (-1);
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct NSEC3Hash object: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (-1);
    }

    return (-1);
}

void
NSEC3Hash_destroy(PyObject* po_self) {
    s_NSEC3Hash* self = static_cast<s_NSEC3Hash*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
NSEC3Hash_calculate(PyObject* po_self, PyObject* args) {
    s_NSEC3Hash* const self = static_cast<s_NSEC3Hash*>(po_self);

    try {
        PyObject* po_name;
        if (PyArg_ParseTuple(args, "O", &po_name)) {
            if (!PyName_Check(po_name)) {
                PyErr_Format(PyExc_TypeError,
                             "name must be a Name, not %.200s",
                             po_name->ob_type->tp_name);
                return (NULL);
            }
            const string hash =
                self->cppobj->calculate(PyName_ToName(po_name));
            return (Py_BuildValue("s", hash.c_str()));
        }
    } catch (const exception& ex) {
        const string ex_what = "Unexpected failure in NSEC3Hash.calculate: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    }

    return (NULL);
}

PyObject*
NSEC3Hash_match(PyObject* po_self, PyObject* args) {
    s_NSEC3Hash* const self = static_cast<s_NSEC3Hash*>(po_self);

    try {
        PyObject* po_rdata;
        if (PyArg_ParseTuple(args, "O", &po_rdata)) {
            if (!PyRdata_Check(po_rdata)) {
                PyErr_Format(PyExc_TypeError,
                             "param must be an Rdata of type NSEC3/NSEC3PARAM,"
                             " not %.200s", po_rdata->ob_type->tp_name);
                return (NULL);
            }
            const Rdata& rdata = PyRdata_ToRdata(po_rdata);
            const generic::NSEC3PARAM* nsec3param =
                dynamic_cast<const generic::NSEC3PARAM*>(&rdata);
            const generic::NSEC3* nsec3 =
                dynamic_cast<const generic::NSEC3*>(&rdata);
            bool matched;
            if (nsec3param != NULL) {
                matched = self->cppobj->match(*nsec3param);
            } else if (nsec3 != NULL) {
                matched = self->cppobj->match(*nsec3);
            } else {
                PyErr_Format(PyExc_TypeError,
                             "param must be an Rdata of type NSEC3/NSEC3HASH");
                return (NULL);
            }
            PyObject* ret = matched ? Py_True : Py_False;
            Py_INCREF(ret);
            return (ret);
        }
    } catch (const exception& ex) {
        const string ex_what = "Unexpected failure in NSEC3Hash.match: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    }

    return (NULL);
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef NSEC3Hash_methods[] = {
    { "calculate", NSEC3Hash_calculate, METH_VARARGS, NSEC3Hash_calculate_doc },
    { "match", NSEC3Hash_match, METH_VARARGS, NSEC3Hash_match_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
//
// Declaration of the custom exceptions
// Initialization and addition of these go in pydnspp.cc
//
PyObject* po_UnknownNSEC3HashAlgorithm;

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_NSEC3Hash
// Most of the functions are not actually implemented and NULL here.
PyTypeObject nsec3hash_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "dns.NSEC3Hash",
    sizeof(s_NSEC3Hash),                 // tp_basicsize
    0,                                  // tp_itemsize
    NSEC3Hash_destroy,                 // tp_dealloc
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
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    NSEC3Hash_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    NSEC3Hash_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    NSEC3Hash_init,                    // tp_init
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

// Module Initialization, all statics (nothing right now) are initialized here
bool
initModulePart_NSEC3Hash(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&nsec3hash_type) < 0) {
        return (false);
    }
    void* p = &nsec3hash_type;
    if (PyModule_AddObject(mod, "NSEC3Hash", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&nsec3hash_type);

    return (true);
}
} // namespace python
} // namespace dns
} // namespace isc
