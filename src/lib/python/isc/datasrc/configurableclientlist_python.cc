// Copyright (C) 2012-2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <dns/python/name_python.h>
#include <dns/python/pydnspp_common.h>

#include <datasrc/client_list.h>

#include "configurableclientlist_python.h"
#include "datasrc.h"
#include "finder_python.h"
#include "client_python.h"
#include "zonetable_accessor_python.h"
#include "zonewriter_python.h"

#include "configurableclientlist_inc.cc"

using namespace std;
using namespace isc::util::python;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::python;
using namespace isc::datasrc::memory::python;
using namespace isc::dns::python;

//
// ConfigurableClientList
//

// Trivial constructor.
s_ConfigurableClientList::s_ConfigurableClientList() : cppobj(NULL) {
}

namespace {

int
ConfigurableClientList_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        const PyObject* rrclass;
        if (PyArg_ParseTuple(args, "O!", &isc::dns::python::rrclass_type,
                             &rrclass)) {
            self->cppobj =
                new ConfigurableClientList(isc::dns::python::
                                           PyRRClass_ToRRClass(rrclass));
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to construct ConfigurableClientList object: " +
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

PyObject*
ConfigurableClientList_configure(PyObject* po_self, PyObject* args) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        const char* configuration;
        int allow_cache;
        if (PyArg_ParseTuple(args, "si", &configuration, &allow_cache)) {
            const isc::data::ConstElementPtr
                element(isc::data::Element::fromJSON(string(configuration)));
            self->cppobj->configure(element, allow_cache);
            Py_RETURN_NONE;
        } else {
            return (NULL);
        }
    } catch (const isc::data::JSONError& jse) {
        const string ex_what(std::string("JSON parse error in data source"
                               " configuration: ") + jse.what());
        PyErr_SetString(getDataSourceException("Error"), ex_what.c_str());
        return (NULL);
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }
}

PyObject*
ConfigurableClientList_resetMemorySegment(PyObject* po_self, PyObject* args) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        const char* datasrc_name_p;
        int mode_int;
        const char* config_p;
        if (PyArg_ParseTuple(args, "sis", &datasrc_name_p, &mode_int,
                             &config_p)) {
            const std::string datasrc_name(datasrc_name_p);
            const isc::data::ConstElementPtr
                config(isc::data::Element::fromJSON(std::string(config_p)));
            ZoneTableSegment::MemorySegmentOpenMode mode =
                static_cast<ZoneTableSegment::MemorySegmentOpenMode>
                    (mode_int);
            self->cppobj->resetMemorySegment(datasrc_name, mode, config);
            Py_RETURN_NONE;
        }
    } catch (const isc::data::JSONError& jse) {
        const string ex_what(std::string("JSON parse error in memory segment"
                               " configuration: ") + jse.what());
        PyErr_SetString(getDataSourceException("Error"), ex_what.c_str());
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
    }

    return (NULL);
}

PyObject*
ConfigurableClientList_getCachedZoneWriter(PyObject* po_self, PyObject* args) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        PyObject* name_obj;
        int catch_load_error;
        const char* datasrc_name_p = "";
#if (PY_VERSION_HEX >= 0x030300f0)
        // The 'p' specifier for predicate (boolean) is available from
        // Python 3.3 (final) only.
        if (PyArg_ParseTuple(args, "O!p|s", &isc::dns::python::name_type,
                             &name_obj, &catch_load_error, &datasrc_name_p)) {
#else
        if (PyArg_ParseTuple(args, "O!i|s", &isc::dns::python::name_type,
                             &name_obj, &catch_load_error, &datasrc_name_p)) {
#endif
            const isc::dns::Name&
                name(isc::dns::python::PyName_ToName(name_obj));
            const std::string datasrc_name(datasrc_name_p);

            const ConfigurableClientList::ZoneWriterPair result =
                self->cppobj->getCachedZoneWriter(name, catch_load_error,
                                                  datasrc_name);

            PyObjectContainer writer;
            if (!result.second) {
                // Use the Py_BuildValue, as it takes care of the
                // reference counts correctly.
                writer.reset(Py_BuildValue(""));
            } else {
                // Make sure it keeps the writer alive.
                writer.reset(createZoneWriterObject(result.second,
                                                    po_self));
            }

            return (Py_BuildValue("IO", result.first, writer.get()));
        } else {
            return (NULL);
        }
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }
}

PyObject*
ConfigurableClientList_getStatus(PyObject* po_self, PyObject*) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        const std::vector<DataSourceStatus> status = self->cppobj->getStatus();

        PyObjectContainer slist(PyList_New(status.size()));

        for (size_t i = 0; i < status.size(); ++i) {
            PyObjectContainer segment_type;

            if (status[i].getSegmentState() != SEGMENT_UNUSED) {
                segment_type.reset(Py_BuildValue(
                    "s", status[i].getSegmentType().c_str()));
            } else {
                Py_INCREF(Py_None);
                segment_type.reset(Py_None);
            }

            PyObjectContainer tup(Py_BuildValue("(sOI)",
                                                status[i].getName().c_str(),
                                                segment_type.get(),
                                                status[i].getSegmentState()));
            // The following "steals" our reference on tup, so we must
            // not decref.
            PyList_SET_ITEM(slist.get(), i, tup.release());
        }

        return (slist.release());
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }
}

PyObject*
ConfigurableClientList_find(PyObject* po_self, PyObject* args) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        PyObject* name_obj;
        int want_exact_match = 0;
        int want_finder = 1;
        if (PyArg_ParseTuple(args, "O!|ii", &isc::dns::python::name_type,
                             &name_obj, &want_exact_match, &want_finder)) {
            const isc::dns::Name&
                name(isc::dns::python::PyName_ToName(name_obj));
            const ClientList::FindResult
                result(self->cppobj->find(name, want_exact_match,
                                          want_finder));
            PyObjectContainer dsrc;
            if (result.dsrc_client_ == NULL) {
                // Use the Py_BuildValue, as it takes care of the
                // reference counts correctly.
                dsrc.reset(Py_BuildValue(""));
            } else {
                // Make sure we have a keeper there too, so it doesn't
                // die when the underlying client list dies or is
                // reconfigured.
                //
                // However, as it is inside the C++ part, is there a
                // reasonable way to test it?
                dsrc.reset(wrapDataSourceClient(result.dsrc_client_,
                                                result.life_keeper_));
            }
            PyObjectContainer finder;
            if (result.finder_ == NULL) {
                finder.reset(Py_BuildValue(""));
            } else {
                // Make sure it keeps the data source client alive.
                finder.reset(createZoneFinderObject(result.finder_,
                                                    dsrc.get()));
            }
            PyObjectContainer exact(PyBool_FromLong(result.exact_match_));

            return (Py_BuildValue("OOO", dsrc.get(), finder.get(),
                                  exact.get()));
        } else {
            return (NULL);
        }
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }
}

PyObject*
ConfigurableClientList_getZoneTableAccessor(PyObject* po_self, PyObject* args) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        const char* datasrc_name;
        int use_cache;
        if (PyArg_ParseTuple(args, "zi", &datasrc_name, &use_cache)) {
            // python 'None' will be read as NULL, which we convert to an
            // empty string, meaning "any data source"
            const std::string name(datasrc_name ? datasrc_name : "");
            const ConstZoneTableAccessorPtr
                z(self->cppobj->getZoneTableAccessor(name, use_cache));
            if (z == NULL) {
                Py_RETURN_NONE;
            } else {
                return (createZoneTableAccessorObject(z, po_self));
            }
        } else {
            return (NULL);
        }
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ConfigurableClientList_methods[] = {
    { "configure", ConfigurableClientList_configure,
      METH_VARARGS, ConfigurableClientList_configure_doc },
    { "reset_memory_segment", ConfigurableClientList_resetMemorySegment,
      METH_VARARGS, ConfigurableClientList_reset_memory_segment_doc },
    { "get_zone_table_accessor", ConfigurableClientList_getZoneTableAccessor,
      METH_VARARGS, ConfigurableClientList_get_zone_table_accessor_doc },
    { "get_cached_zone_writer", ConfigurableClientList_getCachedZoneWriter,
      METH_VARARGS, ConfigurableClientList_get_cached_zone_writer_doc },
    { "get_status", ConfigurableClientList_getStatus,
      METH_NOARGS, ConfigurableClientList_get_status_doc },
    { "find", ConfigurableClientList_find,
      METH_VARARGS, ConfigurableClientList_find_doc },
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
    sizeof(s_ConfigurableClientList),   // tp_basicsize
    0,                                  // tp_itemsize
    ConfigurableClientList_destroy,     // tp_dealloc
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
    ConfigurableClientList_methods,     // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ConfigurableClientList_init,        // tp_init
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

    try {
        // ConfigurableClientList::CacheStatus enum
        installClassVariable
            (configurableclientlist_type,
             "CACHE_STATUS_CACHE_DISABLED",
             Py_BuildValue("I", ConfigurableClientList::CACHE_DISABLED));
        installClassVariable
            (configurableclientlist_type,
             "CACHE_STATUS_ZONE_NOT_CACHED",
             Py_BuildValue("I", ConfigurableClientList::ZONE_NOT_CACHED));
        installClassVariable
            (configurableclientlist_type,
             "CACHE_STATUS_ZONE_NOT_FOUND",
             Py_BuildValue("I", ConfigurableClientList::ZONE_NOT_FOUND));
        installClassVariable
            (configurableclientlist_type,
             "CACHE_STATUS_CACHE_NOT_WRITABLE",
             Py_BuildValue("I", ConfigurableClientList::CACHE_NOT_WRITABLE));
        installClassVariable
            (configurableclientlist_type,
             "CACHE_STATUS_DATASRC_NOT_FOUND",
             Py_BuildValue("I", ConfigurableClientList::DATASRC_NOT_FOUND));
        installClassVariable
            (configurableclientlist_type,
             "CACHE_STATUS_ZONE_SUCCESS",
             Py_BuildValue("I", ConfigurableClientList::ZONE_SUCCESS));

        // MemorySegmentState enum
        installClassVariable(configurableclientlist_type,
                             "SEGMENT_UNUSED",
                             Py_BuildValue("I", SEGMENT_UNUSED));
        installClassVariable(configurableclientlist_type,
                             "SEGMENT_WAITING",
                             Py_BuildValue("I", SEGMENT_WAITING));
        installClassVariable(configurableclientlist_type,
                             "SEGMENT_INUSE",
                             Py_BuildValue("I", SEGMENT_INUSE));

        // FIXME: These should eventually be moved to the
        // ZoneTableSegment class when we add Python bindings for the
        // memory data source specific bits. But for now, we add these
        // enums here to support reloading a zone table segment.
        installClassVariable(configurableclientlist_type, "CREATE",
                             Py_BuildValue("I", ZoneTableSegment::CREATE));
        installClassVariable(configurableclientlist_type, "READ_WRITE",
                             Py_BuildValue("I", ZoneTableSegment::READ_WRITE));
        installClassVariable(configurableclientlist_type, "READ_ONLY",
                             Py_BuildValue("I", ZoneTableSegment::READ_ONLY));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in ConfigurableClientList initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
            "Unexpected failure in ConfigurableClientList initialization");
        return (false);
    }

    return (true);
}

} // namespace python
} // namespace datasrc
} // namespace isc
