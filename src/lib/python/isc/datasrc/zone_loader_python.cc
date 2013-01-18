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

#include <datasrc/zone_loader.h>
#include <dns/python/name_python.h>
#include <dns/python/pydnspp_common.h>
#include <exceptions/exceptions.h>

#include "client_python.h"
#include "datasrc.h"
#include "zone_loader_inc.cc"

using namespace std;
using namespace isc::dns::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;
using namespace isc::util::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_ZoneLoader : public PyObject {
public:
    s_ZoneLoader() : cppobj(NULL), target_client(NULL), source_client(NULL)
        {};
    ZoneLoader* cppobj;
    // a zoneloader should not survive its associated client(s),
    // so add a ref to it at init
    PyObject* target_client;
    PyObject* source_client;
};

// General creation and destruction
int
ZoneLoader_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    PyObject *po_target_client = NULL;
    PyObject *po_source_client = NULL;
    PyObject *po_name = NULL;
    char* master_file;
    if (!PyArg_ParseTuple(args, "O!O!s", &datasourceclient_type,
                          &po_target_client, &name_type, &po_name,
                          &master_file) &&
        !PyArg_ParseTuple(args, "O!O!O!", &datasourceclient_type,
                          &po_target_client, &name_type, &po_name,
                          &datasourceclient_type, &po_source_client)
       ) {
        PyErr_SetString(PyExc_TypeError,
                        "Invalid arguments to ZoneLoader constructor, "
                        "expects isc.datasrc.DataSourceClient, isc.dns.Name, "
                        "and either a string or another DataSourceClient");
        return (-1);
    }
    PyErr_Clear();
    try {
        // The associated objects must be alive during the lifetime
        // of this instance, so incref them (through a container in case
        // of exceptions in this method)
        Py_INCREF(po_target_client);
        PyObjectContainer target_client(po_target_client);
        if (po_source_client != NULL) {
            // See above
            Py_INCREF(po_source_client);
            PyObjectContainer source_client(po_source_client);
            self->cppobj = new ZoneLoader(
                PyDataSourceClient_ToDataSourceClient(po_target_client),
                PyName_ToName(po_name),
                PyDataSourceClient_ToDataSourceClient(po_source_client));
            self->source_client = source_client.release();
        } else {
            self->cppobj = new ZoneLoader(
                PyDataSourceClient_ToDataSourceClient(po_target_client),
                PyName_ToName(po_name),
                master_file);
        }
        self->target_client = target_client.release();
        return (0);
    } catch (const isc::InvalidParameter& ivp) {
        PyErr_SetString(po_InvalidParameter, ivp.what());
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
    return (-1);
}

void
ZoneLoader_destroy(PyObject* po_self) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    if (self->target_client != NULL) {
        Py_DECREF(self->target_client);
    }
    if (self->source_client != NULL) {
        Py_DECREF(self->source_client);
    }
    Py_TYPE(self)->tp_free(self);
}

PyObject*
ZoneLoader_load(PyObject* po_self, PyObject*) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    try {
        self->cppobj->load();
        Py_RETURN_NONE;
    } catch (const isc::InvalidOperation& ivo) {
        PyErr_SetString(po_InvalidOperation, ivo.what());
        return (NULL);
    } catch (const isc::datasrc::MasterFileError& mfe) {
        PyErr_SetString(getDataSourceException("MasterFileError"), mfe.what());
        return (NULL);
    } catch (const isc::datasrc::DataSourceError& dse) {
        PyErr_SetString(getDataSourceException("Error"), dse.what());
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

PyObject*
ZoneLoader_loadIncremental(PyObject* po_self, PyObject* args) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);

    int limit;
    if (!PyArg_ParseTuple(args, "i", &limit)) {
        return (NULL);
    }
    if (limit < 0) {
        PyErr_SetString(PyExc_ValueError,
                        "load_incremental argument must be positive");
        return (NULL);
    }
    try {
        if (self->cppobj->loadIncremental(limit)) {
            Py_RETURN_TRUE;
        } else {
            Py_RETURN_FALSE;
        }
    } catch (const isc::InvalidOperation& ivo) {
        PyErr_SetString(po_InvalidOperation, ivo.what());
        return (NULL);
    } catch (const isc::datasrc::MasterFileError& mfe) {
        PyErr_SetString(getDataSourceException("MasterFileError"), mfe.what());
        return (NULL);
    } catch (const isc::datasrc::DataSourceError& dse) {
        PyErr_SetString(getDataSourceException("Error"), dse.what());
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

PyObject*
ZoneLoader_getRRCount(PyObject* po_self, PyObject*) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    return (Py_BuildValue("I", self->cppobj->getRRCount()));
}

PyObject*
ZoneLoader_getProgress(PyObject* po_self, PyObject*) {
    s_ZoneLoader* self = static_cast<s_ZoneLoader*>(po_self);
    return (Py_BuildValue("d", self->cppobj->getProgress()));
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneLoader_methods[] = {
    { "load", ZoneLoader_load, METH_NOARGS, ZoneLoader_load_doc },
    { "load_incremental", ZoneLoader_loadIncremental, METH_VARARGS,
      ZoneLoader_loadIncremental_doc },
    { "get_rr_count", ZoneLoader_getRRCount, METH_NOARGS,
      ZoneLoader_getRRCount_doc },
    { "get_progress", ZoneLoader_getProgress, METH_NOARGS,
      ZoneLoader_getProgress_doc },
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

} // namespace python
} // namespace datasrc
} // namespace isc

