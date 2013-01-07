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

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <config.h>

#include <datasrc/client.h>
#include <datasrc/database.h>
#include <datasrc/sqlite3_accessor.h>

#include "datasrc.h"
#include "client_python.h"
#include "finder_python.h"
#include "iterator_python.h"
#include "updater_python.h"
#include "journal_reader_python.h"
#include "configurableclientlist_python.h"
#include "zone_loader_python.h"

#include <util/python/pycppwrapper_util.h>
#include <dns/python/pydnspp_common.h>

using namespace isc::datasrc;
using namespace isc::datasrc::python;
using namespace isc::util::python;
using namespace isc::dns::python;

namespace isc {
namespace datasrc {
namespace python {
PyObject*
getDataSourceException(const char* ex_name) {
    PyObject* ex_obj = NULL;

    PyObject* datasrc_module = PyImport_AddModule("isc.datasrc");
    if (datasrc_module != NULL) {
        PyObject* datasrc_dict = PyModule_GetDict(datasrc_module);
        if (datasrc_dict != NULL) {
            ex_obj = PyDict_GetItemString(datasrc_dict, ex_name);
        }
    }

    if (ex_obj == NULL) {
        ex_obj = PyExc_RuntimeError;
    }
    return (ex_obj);
}

} // end namespace python
} // end namespace datasrc
} // end namespace isc

namespace {

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

    try {
        installClassVariable(datasourceclient_type, "SUCCESS",
                             Py_BuildValue("I", result::SUCCESS));
        installClassVariable(datasourceclient_type, "EXIST",
                             Py_BuildValue("I", result::EXIST));
        installClassVariable(datasourceclient_type, "NOTFOUND",
                             Py_BuildValue("I", result::NOTFOUND));
        installClassVariable(datasourceclient_type, "PARTIALMATCH",
                             Py_BuildValue("I", result::PARTIALMATCH));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in DataSourceClient initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
            "Unexpected failure in DataSourceClient initialization");
        return (false);
    }

    return (true);
}

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

    try {
        installClassVariable(zonefinder_type, "SUCCESS",
                             Py_BuildValue("I", ZoneFinder::SUCCESS));
        installClassVariable(zonefinder_type, "DELEGATION",
                             Py_BuildValue("I", ZoneFinder::DELEGATION));
        installClassVariable(zonefinder_type, "NXDOMAIN",
                             Py_BuildValue("I", ZoneFinder::NXDOMAIN));
        installClassVariable(zonefinder_type, "NXRRSET",
                             Py_BuildValue("I", ZoneFinder::NXRRSET));
        installClassVariable(zonefinder_type, "CNAME",
                             Py_BuildValue("I", ZoneFinder::CNAME));
        installClassVariable(zonefinder_type, "DNAME",
                             Py_BuildValue("I", ZoneFinder::DNAME));

        installClassVariable(zonefinder_type, "FIND_DEFAULT",
                             Py_BuildValue("I", ZoneFinder::FIND_DEFAULT));
        installClassVariable(zonefinder_type, "FIND_GLUE_OK",
                             Py_BuildValue("I", ZoneFinder::FIND_GLUE_OK));
        installClassVariable(zonefinder_type, "FIND_DNSSEC",
                             Py_BuildValue("I", ZoneFinder::FIND_DNSSEC));
        installClassVariable(zonefinder_type, "NO_WILDCARD",
                             Py_BuildValue("I", ZoneFinder::NO_WILDCARD));

        installClassVariable(zonefinder_type, "RESULT_WILDCARD",
                             Py_BuildValue("I", ZoneFinder::RESULT_WILDCARD));
        installClassVariable(zonefinder_type, "RESULT_NSEC_SIGNED",
                             Py_BuildValue("I",
                                           ZoneFinder::RESULT_NSEC_SIGNED));
        installClassVariable(zonefinder_type, "RESULT_NSEC3_SIGNED",
                             Py_BuildValue("I",
                                           ZoneFinder::RESULT_NSEC3_SIGNED));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in ZoneFinder initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in ZoneFinder initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_ZoneIterator(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&zoneiterator_type) < 0) {
        return (false);
    }
    void* zip = &zoneiterator_type;
    if (PyModule_AddObject(mod, "ZoneIterator", static_cast<PyObject*>(zip)) < 0) {
        return (false);
    }
    Py_INCREF(&zoneiterator_type);

    return (true);
}

bool
initModulePart_ZoneLoader(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&zone_loader_type) < 0) {
        return (false);
    }
    void* p = &zone_loader_type;
    if (PyModule_AddObject(mod, "ZoneLoader", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&zone_loader_type);

    return (true);
}

bool
initModulePart_ZoneUpdater(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&zoneupdater_type) < 0) {
        return (false);
    }
    void* zip = &zoneupdater_type;
    if (PyModule_AddObject(mod, "ZoneUpdater", static_cast<PyObject*>(zip)) < 0) {
        return (false);
    }
    Py_INCREF(&zoneupdater_type);

    return (true);
}

bool
initModulePart_ZoneJournalReader(PyObject* mod) {
    if (PyType_Ready(&journal_reader_type) < 0) {
        return (false);
    }
    void* p = &journal_reader_type;
    if (PyModule_AddObject(mod, "ZoneJournalReader",
                           static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&journal_reader_type);

    try {
        installClassVariable(journal_reader_type, "SUCCESS",
                             Py_BuildValue("I", ZoneJournalReader::SUCCESS));
        installClassVariable(journal_reader_type, "NO_SUCH_ZONE",
                             Py_BuildValue("I",
                                           ZoneJournalReader::NO_SUCH_ZONE));
        installClassVariable(journal_reader_type, "NO_SUCH_VERSION",
                             Py_BuildValue("I",
                                           ZoneJournalReader::NO_SUCH_VERSION));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in ZoneJournalReader initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
            "Unexpected failure in ZoneJournalReader initialization");
        return (false);
    }

    return (true);
}

PyObject* po_DataSourceError;
PyObject* po_MasterFileError;
PyObject* po_NotImplemented;
PyObject* po_OutOfZone;

PyModuleDef iscDataSrc = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "datasrc",
    "Python bindings for the classes in the isc::datasrc namespace.\n\n"
    "These bindings are close match to the C++ API, but they are not complete "
    "(some parts are not needed) and some are done in more python-like ways.",
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

} // end anonymous namespace

PyMODINIT_FUNC
PyInit_datasrc(void) {
    PyObject* mod = PyModule_Create(&iscDataSrc);
    if (mod == NULL) {
        return (NULL);
    }

    try {
        po_DataSourceError = PyErr_NewException("isc.datasrc.Error", NULL,
                                                NULL);
        PyObjectContainer(po_DataSourceError).installToModule(mod, "Error");
        po_MasterFileError = PyErr_NewException("isc.datasrc.MasterFileError",
                                                po_DataSourceError, NULL);
        PyObjectContainer(po_MasterFileError).
            installToModule(mod, "MasterFileError");
        po_OutOfZone = PyErr_NewException("isc.datasrc.OutOfZone", NULL, NULL);
        PyObjectContainer(po_OutOfZone).installToModule(mod, "OutOfZone");
        po_NotImplemented = PyErr_NewException("isc.datasrc.NotImplemented",
                                               NULL, NULL);
        PyObjectContainer(po_NotImplemented).installToModule(mod,
                                                             "NotImplemented");

    } catch (...) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_DataSourceClient(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneFinder(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneIterator(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneUpdater(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneJournalReader(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ConfigurableClientList(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    if (!initModulePart_ZoneLoader(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    return (mod);
}
