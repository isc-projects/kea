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

#include <datasrc/client.h>
#include <datasrc/database.h>
#include <datasrc/data_source.h>
#include <datasrc/sqlite3_accessor.h>
#include <datasrc/iterator.h>
#include <datasrc/zone.h>

#include <dns/python/name_python.h>
#include <dns/python/rrset_python.h>
#include <dns/python/rrclass_python.h>
#include <dns/python/rrtype_python.h>
#include <dns/python/pydnspp_common.h>

#include "datasrc.h"
#include "finder_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// Zone Finder
//

// Trivial constructor.
s_ZoneFinder::s_ZoneFinder() : cppobj(ZoneFinderPtr()) {
}

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_ZoneFinder, ZoneFinder> ZoneFinderContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int
ZoneFinder_init(s_ZoneFinder* self, PyObject* args) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneFinder cannot be constructed directly");

    return (-1);
}

void
ZoneFinder_destroy(s_ZoneFinder* const self) {
    // cppobj is shared ptr, so no need for explicit delete
    Py_TYPE(self)->tp_free(self);
}

// These are the functions we export
//
PyObject* ZoneFinder_GetClass(PyObject* po_self, PyObject*) {
    s_ZoneFinder* self = static_cast<s_ZoneFinder*>(po_self);
    try {
        return (isc::dns::python::createRRClassObject(self->cppobj->getClass()));
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    }
}

PyObject* ZoneFinder_GetOrigin(PyObject* po_self, PyObject*) {
    s_ZoneFinder* self = static_cast<s_ZoneFinder*>(po_self);
    try {
        return (isc::dns::python::createNameObject(self->cppobj->getOrigin()));
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    }
}

PyObject* ZoneFinder_Find(PyObject* po_self, PyObject* args) {
    s_ZoneFinder* const self = static_cast<s_ZoneFinder*>(po_self);
    PyObject *name;
    PyObject *rrtype;
    PyObject *target;
    int options_int;
    if (PyArg_ParseTuple(args, "O!O!OI", &isc::dns::python::name_type, &name,
                                         &isc::dns::python::rrtype_type, &rrtype,
                                         &target, &options_int)) {
        try {
            ZoneFinder::FindOptions options = static_cast<ZoneFinder::FindOptions>(options_int);
            ZoneFinder::FindResult find_result(
                self->cppobj->find(isc::dns::python::PyName_ToName(name),
                                   isc::dns::python::PyRRType_ToRRType(rrtype),
                                   NULL,
                                   options
                                   ));
            ZoneFinder::Result r = find_result.code;
            isc::dns::ConstRRsetPtr rrsp = find_result.rrset;
            if (rrsp) {
                return Py_BuildValue("IO", r, isc::dns::python::createRRsetObject(*rrsp));
            } else {
                Py_INCREF(Py_None);
                return Py_BuildValue("IO", r, Py_None);
            }
        } catch (const DataSourceError& dse) {
            PyErr_SetString(getDataSourceException("Error"), dse.what());
            return (NULL);
        } catch (const std::exception& exc) {
            PyErr_SetString(getDataSourceException("Error"), exc.what());
            return (NULL);
        }
    } else {
        return (NULL);
    }
    return Py_BuildValue("I", 1);
}

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneFinder_methods[] = {
    { "get_class", ZoneFinder_GetClass, METH_NOARGS, "TODO" },
    { "get_origin", ZoneFinder_GetOrigin, METH_NOARGS, "TODO" },
    { "find", ZoneFinder_Find, METH_VARARGS, "TODO" },
    { NULL, NULL, 0, NULL }
};

} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace python {
PyTypeObject zonefinder_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneFinder",
    sizeof(s_ZoneFinder),             // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(ZoneFinder_destroy),       // tp_dealloc
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
    "The ZoneFinder class objects is...(TODO COMPLETE THIS)",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    ZoneFinder_methods,               // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(ZoneFinder_init),// tp_init
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
initModulePart_ZoneFinder(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&zonefinder_type) < 0) {
        return (false);
    }
    void* zip = &zonefinder_type;
    if (PyModule_AddObject(mod, "ZoneFinder", static_cast<PyObject*>(zip)) < 0) {
        return (false);
    }
    Py_INCREF(&zonefinder_type);

    isc::dns::python::addClassVariable(zonefinder_type, "SUCCESS",
                                       Py_BuildValue("I", ZoneFinder::SUCCESS));
    isc::dns::python::addClassVariable(zonefinder_type, "DELEGATION",
                                       Py_BuildValue("I", ZoneFinder::DELEGATION));
    isc::dns::python::addClassVariable(zonefinder_type, "NXDOMAIN",
                                       Py_BuildValue("I", ZoneFinder::NXDOMAIN));
    isc::dns::python::addClassVariable(zonefinder_type, "NXRRSET",
                                       Py_BuildValue("I", ZoneFinder::NXRRSET));
    isc::dns::python::addClassVariable(zonefinder_type, "CNAME",
                                       Py_BuildValue("I", ZoneFinder::CNAME));
    isc::dns::python::addClassVariable(zonefinder_type, "DNAME",
                                       Py_BuildValue("I", ZoneFinder::DNAME));

    isc::dns::python::addClassVariable(zonefinder_type, "FIND_DEFAULT",
                                       Py_BuildValue("I", ZoneFinder::FIND_DEFAULT));
    isc::dns::python::addClassVariable(zonefinder_type, "FIND_GLUE_OK",
                                       Py_BuildValue("I", ZoneFinder::FIND_GLUE_OK));
    isc::dns::python::addClassVariable(zonefinder_type, "FIND_DNSSEC",
                                       Py_BuildValue("I", ZoneFinder::FIND_DNSSEC));


    return (true);
}

PyObject*
createZoneFinderObject(isc::datasrc::ZoneFinderPtr source) {
    s_ZoneFinder* py_zi = static_cast<s_ZoneFinder*>(
        zonefinder_type.tp_alloc(&zonefinder_type, 0));
    if (py_zi != NULL) {
        py_zi->cppobj = source;
    }
    return (py_zi);
}

} // namespace python
} // namespace datasrc
} // namespace isc

