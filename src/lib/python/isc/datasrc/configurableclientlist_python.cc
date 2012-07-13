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

#include <dns/python/rrclass_python.h>

#include <datasrc/client_list.h>

#include "configurableclientlist_python.h"
#include "datasrc.h"
#include "configurableclientlist_inc.cc"

using namespace std;
using namespace isc::util::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

//
// ConfigurableClientList
//

// Trivial constructor.
s_ConfigurableClientList::s_ConfigurableClientList() : cppobj(NULL) {
}

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_ConfigurableClientList, ConfigurableClientList>
    ConfigurableClientListContainer;

int
ConfigurableClientList_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        isc::dns::RRClass rrclass(isc::dns::RRClass::IN());
        if (PyArg_ParseTuple(args, "O!", &isc::dns::python::rrclass_type,
                             &rrclass)) {
            self->cppobj = new ConfigurableClientList(rrclass);
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct ConfigurableClientList object: " +
            string(ex.what());
        PyErr_SetString(getDataSourceException("Error"), ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (-1);
    }

    return (-1);
}

void
ConfigurableClientList_destroy(PyObject* po_self) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ConfigurableClientList_methods[] = {
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_ConfigurableClientList
// Most of the functions are not actually implemented and NULL here.
PyTypeObject configurableclientlist_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ConfigurableClientList",
    sizeof(s_ConfigurableClientList),                 // tp_basicsize
    0,                                  // tp_itemsize
    ConfigurableClientList_destroy,                 // tp_dealloc
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
    ConfigurableClientList_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    ConfigurableClientList_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ConfigurableClientList_init,                    // tp_init
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

// Module Initialization, all statics are initialized here
bool
initModulePart_ConfigurableClientList(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&configurableclientlist_type) < 0) {
        return (false);
    }
    void* p = &configurableclientlist_type;
    if (PyModule_AddObject(mod, "ConfigurableClientList",
                           static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&configurableclientlist_type);

#if 0
    TODO: The return states, etc.
    try {
        // Constant class variables
        installClassVariable(configurableclientlist_type, "REPLACE_ME",
                             Py_BuildValue("REPLACE ME"));
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure in ConfigurableClientList initialization: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in ConfigurableClientList initialization");
        return (false);
    }
#endif

    return (true);
}

} // namespace python
} // namespace datasrc
} // namespace isc
