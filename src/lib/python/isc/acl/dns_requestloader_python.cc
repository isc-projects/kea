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

#include <boost/shared_ptr.hpp>

#include <util/python/pycppwrapper_util.h>

#include <cc/data.h>

#include <acl/dns.h>

#include "dns.h"
#include "dns_requestacl_python.h"
#include "dns_requestloader_python.h"

using namespace std;
using boost::shared_ptr;
using namespace isc::util::python;
using namespace isc::data;
using namespace isc::acl::dns;
using namespace isc::acl::dns::python;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// RequestLoader
//

// Trivial constructor.
s_RequestLoader::s_RequestLoader() : cppobj(NULL) {
}

// Import pydoc text
#include "dns_requestloader_inc.cc"

namespace {
//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

int
RequestLoader_init(PyObject*, PyObject*, PyObject*) {
    PyErr_SetString(getACLException("Error"),
                    "RequestLoader cannot be directly constructed");
    return (-1);
}

void
RequestLoader_destroy(PyObject* po_self) {
    s_RequestLoader* const self = static_cast<s_RequestLoader*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
RequestLoader_load(PyObject* po_self, PyObject* args) {
    s_RequestLoader* const self = static_cast<s_RequestLoader*>(po_self);
    const char* acl_config;

    if (PyArg_ParseTuple(args, "s", &acl_config)) {
        try {
            shared_ptr<RequestACL> acl(
                self->cppobj->load(Element::fromJSON(acl_config)));
            s_RequestACL* py_acl = static_cast<s_RequestACL*>(
                requestacl_type.tp_alloc(&requestacl_type, 0));
            if (py_acl != NULL) {
                py_acl->cppobj = acl;
            }
            return (py_acl);
        } catch (const exception& ex) {
            PyErr_SetString(getACLException("LoaderError"), ex.what());
            return (NULL);
        } catch (...) {
            PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
            return (NULL);
        }
    }

    return (NULL);
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef RequestLoader_methods[] = {
    { "load", RequestLoader_load, METH_VARARGS, RequestLoader_load_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace acl {
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_RequestLoader
// Most of the functions are not actually implemented and NULL here.
PyTypeObject requestloader_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "isc.acl.dns.RequestLoader",
    sizeof(s_RequestLoader),                 // tp_basicsize
    0,                                  // tp_itemsize
    RequestLoader_destroy,       // tp_dealloc
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
    NULL,                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    RequestLoader_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL, // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    RequestLoader_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    RequestLoader_init,            // tp_init
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
initModulePart_RequestLoader(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&requestloader_type) < 0) {
        return (false);
    }
    void* p = &requestloader_type;
    if (PyModule_AddObject(mod, "RequestLoader",
                           static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&requestloader_type);

    return (true);
}
} // namespace python
} // namespace dns
} // namespace acl
} // namespace isc
