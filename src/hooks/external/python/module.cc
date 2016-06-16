// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <Python.h>

#include <hooks/external/python/poption.h>
#include <hooks/external/python/ppkt4.h>

using namespace std;
using namespace isc::python;

namespace { // anonymous namespace

// Module definition
PyModuleDef kea = {
    PyModuleDef_HEAD_INIT,
    "kea",                      // m_name
    "kea hook support",         // m_doc
    -1,                         // m_size
    NULL,                       // m_methods
    NULL,                       // m_slots
    NULL,                       // m_traverse
    NULL,                       // m_clear
    NULL                        // m_free
};

} // end of anonymous namespace

// Module initialization
PyMODINIT_FUNC
PyInit_kea(void) {
    // Create module
    PyObject* mod = PyModule_Create(&kea);
    if (!mod) {
        return (NULL);
    }

    // Initialize option
    if (!initmod_option(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    // Initialize pkt4
    if (!initmod_pkt4(mod)) {
        Py_DECREF(mod);
        return (NULL);
    }

    // Constants

    return (mod);
}
