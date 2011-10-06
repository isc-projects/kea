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

// Enable this if you use s# variants with PyArg_ParseTuple(), see
// http://docs.python.org/py3k/c-api/arg.html#strings-and-buffers
//#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <acl/acl.h>
#include <acl/dns.h>

#include "dns.h"
#include "dns_requestacl_python.h"
#include "dns_requestcontext_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::acl;
using namespace isc::acl::dns;
using namespace isc::acl::dns::python;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// RequestACL
//

// Trivial constructor.
s_RequestACL::s_RequestACL() {}

// Import pydoc text
#include "dns_requestacl_inc.cc"

namespace {
int
RequestACL_init(PyObject*, PyObject*, PyObject*) {
    PyErr_SetString(getACLException("Error"),
                    "RequestACL cannot be directly constructed");
    return (-1);
}

void
RequestACL_destroy(PyObject* po_self) {
    s_RequestACL* const self = static_cast<s_RequestACL*>(po_self);
    self->cppobj.reset();
    Py_TYPE(self)->tp_free(self);
}

PyObject*
RequestACL_execute(PyObject* po_self, PyObject* args) {
    s_RequestACL* const self = static_cast<s_RequestACL*>(po_self);

    try {
        const s_RequestContext* po_context;
        if (PyArg_ParseTuple(args, "O!", &requestcontext_type, &po_context)) {
            const BasicAction action =
                self->cppobj->execute(*po_context->cppobj);
            return (Py_BuildValue("I", action));
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to execute ACL: " + string(ex.what());
        PyErr_SetString(getACLException("Error"), ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError,
                        "Unexpected exception in executing ACL");
    }

    return (NULL);
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef RequestACL_methods[] = {
    { "execute", RequestACL_execute, METH_VARARGS, RequestACL_execute_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace acl {
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_RequestACL
// Most of the functions are not actually implemented and NULL here.
PyTypeObject requestacl_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "isc.acl._dns.RequestACL",
    sizeof(s_RequestACL),                 // tp_basicsize
    0,                                  // tp_itemsize
    RequestACL_destroy,                // tp_dealloc
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
    NULL,	                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE, // tp_flags
    RequestACL_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,				 // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    RequestACL_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    RequestACL_init,                    // tp_init
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
initModulePart_RequestACL(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&requestacl_type) < 0) {
        return (false);
    }
    void* p = &requestacl_type;
    if (PyModule_AddObject(mod, "RequestACL", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&requestacl_type);

    return (true);
}
} // namespace python
} // namespace dns
} // namespace acl
} // namespace isc
