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

#include <util/python/pycppwrapper_util.h>

#include <datasrc/client.h>
#include <datasrc/database.h>
#include <datasrc/data_source.h>
#include <datasrc/sqlite3_accessor.h>
#include <datasrc/iterator.h>
#include <datasrc/zone.h>
#include <datasrc/zone_loader.h>

#include <dns/python/name_python.h>
//#include <dns/python/rrset_python.h>
//#include <dns/python/rrclass_python.h>
//#include <dns/python/rrtype_python.h>
#include <dns/python/pydnspp_common.h>

#include "client_python.h"
#include "datasrc.h"
#include "zone_loader_inc.cc"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_ZoneLoader : public PyObject {
public:
    s_ZoneLoader() : cppobj(NULL), client(NULL) {};
    ZoneLoader* cppobj;
    // a zoneloader should not survive its associated client,
    // so add a ref to it at init
    PyObject* client;
};

// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_ZoneLoader, ZoneLoader> ZoneLoaderContainer;

// General creation and destruction
int
ZoneLoader_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    PyObject *po_ds_client;
    PyObject *po_name;
    char* master_file;
    if (PyArg_ParseTuple(args, "O!O!s", &datasourceclient_type, &po_ds_client, &name_type, &po_name, &master_file)) {
        try {
            Py_INCREF(po_ds_client);
            self->client = po_ds_client;
            self->cppobj = new ZoneLoader(PyDataSourceClient_ToDataSourceClient(po_ds_client), PyName_ToName(po_name), master_file);
            return (0);
        } catch (const isc::datasrc::MasterFileError& mfe) {
            PyErr_SetString(getDataSourceException("MasterFileError"), mfe.what());
        } catch (const isc::datasrc::DataSourceError& dse) {
            PyErr_SetString(getDataSourceException("Error"), dse.what());
        } catch (const isc::NotImplemented& ni) {
            PyErr_SetString(getDataSourceException("NotImplemented"), ni.what());
        } catch (const std::exception& stde) {
            PyErr_SetString(getDataSourceException("Error"), stde.what());
        } catch (...) {
            PyErr_SetString(getDataSourceException("Error"),
                            "Unexpected exception");
        }
    }
    return (-1);
}

void
ZoneLoader_destroy(PyObject* po_self) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    if (self->client != NULL) {
        Py_DECREF(self->client);
    }
    Py_TYPE(self)->tp_free(self);
}

PyObject* ZoneLoader_load(PyObject* po_self, PyObject*) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    try {
        self->cppobj->load();
        Py_RETURN_NONE;
    } catch (const isc::datasrc::MasterFileError& mfe) {
        PyErr_SetString(getDataSourceException("MasterFileError"), mfe.what());
        return (NULL);
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unexpected exception");
        return (NULL);
    }
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneLoader_methods[] = {
/*
    { "get_origin", ZoneLoader_getOrigin, METH_NOARGS,
       ZoneLoader_getOrigin_doc },
    { "get_class", ZoneLoader_getClass, METH_NOARGS, ZoneLoader_getClass_doc },
    { "find", ZoneLoader_find, METH_VARARGS, ZoneLoader_find_doc },
    { "find_all", ZoneLoader_find_all, METH_VARARGS, ZoneLoader_findAll_doc },
*/
    { "load", ZoneLoader_load, METH_NOARGS, ZoneLoader_load_doc },
    { NULL, NULL, 0, NULL }
};

} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace python {

PyTypeObject zone_loader_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneLoader",
    sizeof(s_ZoneLoader),               // tp_basicsize
    0,                                  // tp_itemsize
    ZoneLoader_destroy,                 // tp_dealloc
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
    ZoneLoader_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    ZoneLoader_methods,                 // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ZoneLoader_init,                    // tp_init
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

PyObject* po_MasterFileError;

} // namespace python
} // namespace datasrc
} // namespace isc

