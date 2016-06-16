// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <Python.h>

#include <hooks/hooks.h>

#include <hooks/external/python/module.h>
#include <hooks/external/python/ppkt4.h>

#include <iostream>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::python;

namespace {
    // Program name in Unicode
    wchar_t* wprogname;

    // Script module
    PyObject* modscript;

    // Pkt4 receive handler
    PyObject* pkt4_rcv_hndl;
};

extern "C" {

// Framework functions

// version
int version() {
    return (KEA_HOOKS_VERSION);
}

// load
int load(LibraryHandle& handle) {
    // Add kea as a built-in module
    if (PyImport_AppendInittab("kea", PyInit_kea) < 0) {
        cerr << "PyImport_AppendInittab failed\n";
        return (1);
    }

    // Set the program name (default "kea")
    ConstElementPtr program = handle.getParameter("program");
    string progname = "kea";
    if (program && program->getType() == Element::string) {
        progname = program->stringValue();
    } else {
        cout << "no \"program\" parameter: using \"kea\"\n";
    }
    wprogname = Py_DecodeLocale(progname.c_str(), NULL);
    if (!wprogname) {
        cerr << "Py_DecodeLocale failed\n";
        return (2);
    }
    Py_SetProgramName(wprogname);
    
    // Initialize the python interpreter without signal handlers
    Py_InitializeEx(0);

    // Get the script module name (default "hook" for the "hook.py" file)
    ConstElementPtr script = handle.getParameter("script");
    string scptname = "hook";
    if (script && script->getType() == Element::string) {
        scptname = script->stringValue();
    } else {
        cout << "no \"script\" parameter: using \"hook\"\n";
    }
    PyObject* pyscript = PyUnicode_DecodeFSDefault(scptname.c_str());
    if (!pyscript) {
        PyErr_Print();
        cerr << "PyUnicode_DecodeFSDefault failed\n";
        return (3);
    }
    modscript = PyImport_Import(pyscript);
    Py_DECREF(pyscript);
    if (!modscript) {
        PyErr_Print();
        cerr << "PyImport_Import failed\n";
        return (4);
    }

    pkt4_rcv_hndl = PyObject_GetAttrString(modscript, "pkt4_receive");
    if (pkt4_rcv_hndl) {
        if (!PyCallable_Check(pkt4_rcv_hndl)) {
            cerr << "pkt4_receive is not callable\n";
            Py_DECREF(pkt4_rcv_hndl);
            pkt4_rcv_hndl = NULL;
        } else {
            cout << "got pkt4_receive\n";
        }
    }

    return (0);
}

// unload
int unload() {
    // Free script module
    Py_XDECREF(modscript);

    // Shutdown
    Py_Finalize();

    // Free wprogname
    PyMem_RawFree(wprogname);

    return (0);
}

// pkt4_receive hook
int pkt4_receive(CalloutHandle& handle) {
    if (!pkt4_rcv_hndl) {
        return (0);
    }
    cout << "pkt4_receive: enter\n";

    Pkt4Ptr query4;
    handle.getArgument("query4", query4);
    if (!query4) {
        cerr << "pkt4_receive: null query4\n";
        return (0);
    }

    PyObject* query = pkt4_type.tp_alloc(&pkt4_type, 0);
    if (!query) {
        PyErr_Print();
        cerr << "pkt4_alloc failed\n";
        return (0);
    }
    (static_cast<py_pkt4*>(query))->object = query4;

    PyObject* args = Py_BuildValue("(O)", query);
    if (!args) {
        PyErr_Print();
        cerr << "Py_BuildValue failed\n";
        return (0);
    }
    PyObject* ret = PyObject_CallObject(pkt4_rcv_hndl, args);
    Py_DECREF(args);
    if (!ret) {
        PyErr_Print();
        cerr << "pkt4_rcv_hndl failed\n";
        return (0);
    }
    if (!PyLong_Check(ret)) {
        PyErr_Print();
        cerr << "pkt4_rcv_hndl didn't return an int\n";
        Py_DECREF(ret);
        return (0);
    }
    int result = static_cast<int>(PyLong_AsLong(ret));
    Py_DECREF(ret);
    if (PyErr_Occurred()) {
        PyErr_Print();
        cerr << "PyLong_AsLong failed\n";
        return (0);
    }

    cout << "pkt4_receive: return " << result << "\n";
    return (result);
}

}
