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
#include <dns/python/name_python.h>

#include <datasrc/client_list.h>

#include "configurableclientlist_python.h"
#include "datasrc.h"
#include "finder_python.h"
#include "client_python.h"

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
ConfigurableClientList_find(PyObject* po_self, PyObject* args) {
    s_ConfigurableClientList* self =
        static_cast<s_ConfigurableClientList*>(po_self);
    try {
        PyObject* name_obj;
        int want_exact_match = 0;
        int want_finder = 1;
        if (PyArg_ParseTuple(args, "O!|ii", &isc::dns::python::name_type,
                             &name_obj, &want_exact_match, &want_finder)) {
            const isc::dns::Name
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

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ConfigurableClientList_methods[] = {
    { "configure", ConfigurableClientList_configure, METH_VARARGS,
        "configure(configuration, allow_cache) -> None\n\
\n\
Wrapper around C++ ConfigurableClientList::configure\n\
\n\
This sets the active configuration. It fills the ConfigurableClientList with\
corresponding data source clients.\n\
\n\
If any error is detected, an exception is raised and the previous\
configuration preserved.\n\
\n\
Parameters:\n\
  configuration     The configuration, as a JSON encoded string.\
  allow_cache       If caching is allowed." },
    { "find", ConfigurableClientList_find, METH_VARARGS,
"find(zone, want_exact_match=False, want_finder=True) -> datasrc_client,\
zone_finder, exact_match\n\
\n\
Look for a data source containing the given zone.\n\
\n\
It searches through the contained data sources and returns a data source\
containing the zone, the zone finder of the zone and a boolean if the answer\
is an exact match.\n\
\n\
The first parameter is isc.dns.Name object of a name in the zone. If the\
want_exact_match is True, only zone with this exact origin is returned.\
If it is False, the best matching zone is returned.\n\
\n\
If the want_finder is False, the returned zone_finder might be None even\
if the data source is identified (in such case, the datasrc_client is not\
None). Setting it to false allows the client list some optimisations, if\
you don't need it, but if you do need it, it is better to set it to True\
instead of getting it from the datasrc_client later.\n\
\n\
If no answer is found, the datasrc_client and zone_finder are None." },
    { NULL, NULL, 0, NULL }
};

const char* const ConfigurableClientList_doc = "\
The list of data source clients\n\
\n\
The purpose is to have several data source clients of the same class\
and then be able to search through them to identify the one containing\
a given zone.\n\
\n\
Unlike the C++ version, we don't have the abstract base class. Abstract\
classes are not needed due to the duck typing nature of python.\
";

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

    return (true);
}

} // namespace python
} // namespace datasrc
} // namespace isc
