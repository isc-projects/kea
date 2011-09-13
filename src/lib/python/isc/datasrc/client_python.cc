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
#include <datasrc/sqlite3_accessor.h>
#include <datasrc/iterator.h>

#include <dns/python/name_python.h>
#include <dns/python/rrset_python.h>
#include <dns/python/pydnspp_common.h>

#include "datasrc.h"
#include "client_python.h"
#include "finder_python.h"
#include "iterator_python.h"
#include "updater_python.h"

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
// DataSourceClient
//

// Trivial constructor.
s_DataSourceClient::s_DataSourceClient() : cppobj(NULL) {
}

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_DataSourceClient, DataSourceClient>
    DataSourceClientContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int DataSourceClient_init(s_DataSourceClient* self, PyObject* args);
void DataSourceClient_destroy(s_DataSourceClient* self);

// These are the functions we export
//
PyObject*
DataSourceClient_FindZone(PyObject* po_self, PyObject* args) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    PyObject *name;
    if (PyArg_ParseTuple(args, "O!", &isc::dns::python::name_type, &name)) {
        DataSourceClient::FindResult find_result(
            self->cppobj->findZone(isc::dns::python::PyName_ToName(name)));

        result::Result r = find_result.code;
        ZoneFinderPtr zfp = find_result.zone_finder;
        return Py_BuildValue("IO", r, createZoneFinderObject(zfp));
    } else {
        return (NULL);
    }
}

PyObject*
DataSourceClient_GetIterator(PyObject* po_self, PyObject* args) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    PyObject *name_obj;
    if (PyArg_ParseTuple(args, "O!", &isc::dns::python::name_type, &name_obj)) {
        return (createZoneIteratorObject(self->cppobj->getIterator(isc::dns::python::PyName_ToName(name_obj))));
    } else {
        return (NULL);
    }
}

PyObject*
DataSourceClient_GetUpdater(PyObject* po_self, PyObject* args) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    PyObject *name_obj;
    PyObject *replace_obj;
    if (PyArg_ParseTuple(args, "O!O", &isc::dns::python::name_type, &name_obj, &replace_obj) && PyBool_Check(replace_obj)) {
        bool replace = (replace_obj != Py_False);
        return (createZoneUpdaterObject(self->cppobj->getUpdater(isc::dns::python::PyName_ToName(name_obj), replace)));
    } else {
        return (NULL);
    }
}

// These are the functions we export

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef DataSourceClient_methods[] = {
    { "find_zone", DataSourceClient_FindZone, METH_VARARGS, "TODO" },
    { "get_iterator", DataSourceClient_GetIterator, METH_VARARGS, "TODO" },
    { "get_updater", DataSourceClient_GetUpdater, METH_VARARGS, "TODO" },
    { NULL, NULL, 0, NULL }
};

// This is a template of typical code logic of python class initialization
// with C++ backend.  You'll need to adjust it according to details of the
// actual C++ class.
int
DataSourceClient_init(s_DataSourceClient* self, PyObject* args) {
    // TODO: we should use the factory function which hasn't been written
    // yet. For now we hardcode the sqlite3 initialization, and pass it one
    // string for the database file. (similar to how the 'old direct'
    // sqlite3_ds code works)
    try {
        char* db_file_name;
        if (PyArg_ParseTuple(args, "s", &db_file_name)) {
            boost::shared_ptr<DatabaseAccessor> sqlite3_accessor(
                new SQLite3Accessor(db_file_name, isc::dns::RRClass::IN()));
            self->cppobj = new DatabaseClient(isc::dns::RRClass::IN(),
                                              sqlite3_accessor);
            return (0);
        } else {
            return (-1);
        }

    } catch (const exception& ex) {
        const string ex_what = "Failed to construct DataSourceClient object: " +
            string(ex.what());
        PyErr_SetString(getDataSourceException("Error"), ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError,
            "Unexpected exception in constructing DataSourceClient");
        return (-1);
    }
    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to DataSourceClient constructor");

    return (-1);
}

// This is a template of typical code logic of python object destructor.
// In many cases you can use it without modification, but check that carefully.
void
DataSourceClient_destroy(s_DataSourceClient* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

} // end anonymous namespace

namespace isc {
namespace datasrc {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_DataSourceClient
// Most of the functions are not actually implemented and NULL here.
PyTypeObject datasourceclient_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.DataSourceClient",
    sizeof(s_DataSourceClient),                 // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(DataSourceClient_destroy),       // tp_dealloc
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
    "The DataSourceClient class objects is...(COMPLETE THIS)",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    DataSourceClient_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(DataSourceClient_init),            // tp_init
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
initModulePart_DataSourceClient(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&datasourceclient_type) < 0) {
        return (false);
    }
    void* dscp = &datasourceclient_type;
    if (PyModule_AddObject(mod, "DataSourceClient", static_cast<PyObject*>(dscp)) < 0) {
        return (false);
    }
    Py_INCREF(&datasourceclient_type);

    isc::dns::python::addClassVariable(datasourceclient_type, "SUCCESS",
                                       Py_BuildValue("I", result::SUCCESS));
    isc::dns::python::addClassVariable(datasourceclient_type, "EXIST",
                                       Py_BuildValue("I", result::EXIST));
    isc::dns::python::addClassVariable(datasourceclient_type, "NOTFOUND",
                                       Py_BuildValue("I", result::NOTFOUND));
    isc::dns::python::addClassVariable(datasourceclient_type, "PARTIALMATCH",
                                       Py_BuildValue("I", result::PARTIALMATCH));

    return (true);
}

} // namespace python
} // namespace datasrc
} // namespace isc
