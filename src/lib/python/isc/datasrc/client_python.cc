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

#include <util/python/pycppwrapper_util.h>

#include <datasrc/client.h>
#include <datasrc/factory.h>
#include <datasrc/database.h>
#include <datasrc/data_source.h>
#include <datasrc/sqlite3_accessor.h>
#include <datasrc/iterator.h>
#include <datasrc/client_list.h>

#include <dns/python/name_python.h>
#include <dns/python/rrset_python.h>
#include <dns/python/pydnspp_common.h>

#include "datasrc.h"
#include "client_python.h"
#include "finder_python.h"
#include "iterator_python.h"
#include "updater_python.h"
#include "journal_reader_python.h"
#include "client_inc.cc"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_DataSourceClient : public PyObject {
public:
    s_DataSourceClient() :
        cppobj(NULL),
        client(NULL),
        keeper(NULL)
    {};
    DataSourceClientContainer* cppobj;
    DataSourceClient* client;
    // We can't rely on the constructor or destructor being
    // called, so this is a pointer to shared pointer, so we
    // can call the new and delete explicitly.
    boost::shared_ptr<ClientList::FindResult::LifeKeeper>* keeper;
};

PyObject*
DataSourceClient_findZone(PyObject* po_self, PyObject* args) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    PyObject *name;
    if (PyArg_ParseTuple(args, "O!", &name_type, &name)) {
        try {
            DataSourceClient::FindResult find_result(
                self->client->findZone(PyName_ToName(name)));

            result::Result r = find_result.code;
            ZoneFinderPtr zfp = find_result.zone_finder;
            // Use N instead of O so refcount isn't increased twice
            return (Py_BuildValue("IN", r, createZoneFinderObject(zfp, po_self)));
        } catch (const std::exception& exc) {
            PyErr_SetString(getDataSourceException("Error"), exc.what());
            return (NULL);
        } catch (...) {
            PyErr_SetString(getDataSourceException("Error"),
                            "Unexpected exception");
            return (NULL);
        }
    } else {
        return (NULL);
    }
}

PyObject*
DataSourceClient_getIterator(PyObject* po_self, PyObject* args) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    PyObject* name_obj;
    PyObject* separate_rrs_obj = NULL;
    if (PyArg_ParseTuple(args, "O!|O", &name_type, &name_obj,
                         &separate_rrs_obj)) {
        try {
            bool separate_rrs = false;
            if (separate_rrs_obj != NULL) {
                // store result in local var so we can explicitely check for
                // -1 error return value
                int separate_rrs_true = PyObject_IsTrue(separate_rrs_obj);
                if (separate_rrs_true == 1) {
                    separate_rrs = true;
                } else if (separate_rrs_true == -1) {
                    PyErr_SetString(getDataSourceException("Error"),
                                    "Error getting value of separate_rrs");
                    return (NULL);
                }
            }
            return (createZoneIteratorObject(
                self->client->getIterator(PyName_ToName(name_obj),
                                                        separate_rrs),
                po_self));
        } catch (const isc::NotImplemented& ne) {
            PyErr_SetString(getDataSourceException("NotImplemented"),
                            ne.what());
            return (NULL);
        } catch (const DataSourceError& dse) {
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
    } else {
        return (NULL);
    }
}

PyObject*
DataSourceClient_getUpdater(PyObject* po_self, PyObject* args) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    PyObject *name_obj;
    PyObject *replace_obj = NULL;
    PyObject *journaling_obj = Py_False;
    if (PyArg_ParseTuple(args, "O!O|O", &name_type, &name_obj,
                         &replace_obj, &journaling_obj) &&
        PyBool_Check(replace_obj) && PyBool_Check(journaling_obj)) {
        const bool replace = (replace_obj != Py_False);
        const bool journaling = (journaling_obj == Py_True);
        try {
            ZoneUpdaterPtr updater =
                self->client->getUpdater(PyName_ToName(name_obj),
                                                       replace, journaling);
            if (!updater) {
                return (Py_None);
            }
            return (createZoneUpdaterObject(updater, po_self));
        } catch (const isc::NotImplemented& ne) {
            PyErr_SetString(getDataSourceException("NotImplemented"),
                            ne.what());
            return (NULL);
        } catch (const DataSourceError& dse) {
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
    } else {
        // PyBool_Check doesn't set the error, so we have to set it ourselves.
        if (replace_obj != NULL && !PyBool_Check(replace_obj)) {
            PyErr_SetString(PyExc_TypeError, "'replace' for "
                            "DataSourceClient.get_updater must be boolean");
        }
        if (!PyBool_Check(journaling_obj)) {
            PyErr_SetString(PyExc_TypeError, "'journaling' for "
                            "DataSourceClient.get_updater must be boolean");
        }
        return (NULL);
    }
}

PyObject*
DataSourceClient_getJournalReader(PyObject* po_self, PyObject* args) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    PyObject *name_obj;
    unsigned long begin_obj, end_obj;

    if (PyArg_ParseTuple(args, "O!kk", &name_type, &name_obj,
                         &begin_obj, &end_obj)) {
        try {
            pair<ZoneJournalReader::Result, ZoneJournalReaderPtr> result =
                self->client->getJournalReader(
                    PyName_ToName(name_obj), static_cast<uint32_t>(begin_obj),
                    static_cast<uint32_t>(end_obj));
            PyObject* po_reader;
            if (result.first == ZoneJournalReader::SUCCESS) {
                po_reader = createZoneJournalReaderObject(result.second,
                                                          po_self);
            } else {
                po_reader = Py_None;
                Py_INCREF(po_reader); // this will soon be released
            }
            PyObjectContainer container(po_reader);
            return (Py_BuildValue("(iO)", result.first, container.get()));
        } catch (const isc::NotImplemented& ex) {
            PyErr_SetString(getDataSourceException("NotImplemented"),
                            ex.what());
        } catch (const DataSourceError& ex) {
            PyErr_SetString(getDataSourceException("Error"), ex.what());
        } catch (const std::exception& ex) {
            PyErr_SetString(PyExc_SystemError, ex.what());
        } catch (...) {
            PyErr_SetString(PyExc_SystemError, "Unexpected exception");
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
PyMethodDef DataSourceClient_methods[] = {
    { "find_zone", DataSourceClient_findZone, METH_VARARGS,
      DataSourceClient_findZone_doc },
    { "get_iterator",
      DataSourceClient_getIterator, METH_VARARGS,
      DataSourceClient_getIterator_doc },
    { "get_updater", DataSourceClient_getUpdater,
      METH_VARARGS, DataSourceClient_getUpdater_doc },
    { "get_journal_reader", DataSourceClient_getJournalReader,
      METH_VARARGS, DataSourceClient_getJournalReader_doc },
    { NULL, NULL, 0, NULL }
};

int
DataSourceClient_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_DataSourceClient* self = static_cast<s_DataSourceClient*>(po_self);
    char* ds_type_str;
    char* ds_config_str;
    try {
        // Turn the given argument into config Element; then simply call
        // factory class to do its magic

        // for now, ds_config must be JSON string
        if (PyArg_ParseTuple(args, "ss", &ds_type_str, &ds_config_str)) {
            isc::data::ConstElementPtr ds_config =
                isc::data::Element::fromJSON(ds_config_str);
            self->cppobj = new DataSourceClientContainer(ds_type_str,
                                                         ds_config);
            self->client = &self->cppobj->getInstance();
            self->keeper = NULL;
            return (0);
        } else {
            return (-1);
        }
    } catch (const isc::data::JSONError& je) {
        const string ex_what = "JSON parse error in data source configuration "
                               "data for type " +
                               string(ds_type_str) + ":" + je.what();
        PyErr_SetString(getDataSourceException("Error"), ex_what.c_str());
        return (-1);
    } catch (const DataSourceError& dse) {
        const string ex_what = "Failed to create DataSourceClient of type " +
                               string(ds_type_str) + ":" + dse.what();
        PyErr_SetString(getDataSourceException("Error"), ex_what.c_str());
        return (-1);
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

void
DataSourceClient_destroy(PyObject* po_self) {
    s_DataSourceClient* const self = static_cast<s_DataSourceClient*>(po_self);
    delete self->cppobj;
    delete self->keeper;
    self->cppobj = NULL;
    self->client = NULL;
    self->keeper = NULL;
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
    sizeof(s_DataSourceClient),         // tp_basicsize
    0,                                  // tp_itemsize
    DataSourceClient_destroy,           // tp_dealloc
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
    DataSourceClient_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    DataSourceClient_methods,           // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    DataSourceClient_init,              // tp_init
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
wrapDataSourceClient(DataSourceClient* client,
                     const boost::shared_ptr<ClientList::FindResult::
                     LifeKeeper>& life_keeper)
{
    s_DataSourceClient *result =
        static_cast<s_DataSourceClient*>(PyObject_New(s_DataSourceClient,
                                                      &datasourceclient_type));
    CPPPyObjectContainer<s_DataSourceClient, DataSourceClientContainer>
        container(result);
    result->cppobj = NULL;
    result->keeper =
        new boost::shared_ptr<ClientList::FindResult::LifeKeeper>(life_keeper);
    result->client = client;
    return (container.release());
}

DataSourceClient&
PyDataSourceClient_ToDataSourceClient(PyObject* client_obj) {
    if (client_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in Name PyObject conversion");
    }
    const s_DataSourceClient* client =
        static_cast<const s_DataSourceClient*>(client_obj);
    return (*client->client);
}

} // namespace python
} // namespace datasrc
} // namespace isc
