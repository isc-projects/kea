
// Ok we want a lot of different parts of the DNS API in the python
// module, but not one big 10000-line file.
// So we split it up in several 'mini-modules'
// These would be the same as a single module, except for
// the init function, which has to be modified to a unique
// name initModulePart_<name>, and return true/false instead of
// NULL/*mod
//
// And of course care has to be taken that all identifiers be unique

// 
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "config.h"

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>

#include "libdns_python_common.h"

//#include "buffer_python.cc"
// order is important here! (TODO: document dependencies)
#include "name_python.cc"
#include "messagerenderer_python.cc"
#include "rrclass_python.cc"
#include "rrtype_python.cc"
#include "rrttl_python.cc"
#include "rdata_python.cc"
#include "rrset_python.cc"

//
// Definition of the module
//
static PyModuleDef libdns_python = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "libdns_python",
    "Python bindings for isc.dns",
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC
PyInit_libdns_python(void)
{
    PyObject *mod = PyModule_Create(&libdns_python);
    if (mod == NULL) {
        return NULL;
    }

    // for each part included above, we call its specific initializer

    if (!initModulePart_Name(mod)) {
        return NULL;
    }

    if (!initModulePart_MessageRenderer(mod)) {
        return NULL;
    }

    if (!initModulePart_RRClass(mod)) {
        return NULL;
    }

    if (!initModulePart_RRType(mod)) {
        return NULL;
    }

    if (!initModulePart_RRTTL(mod)) {
        return NULL;
    }

    if (!initModulePart_Rdata(mod)) {
        return NULL;
    }

    if (!initModulePart_RRset(mod)) {
        return NULL;
    }

    return mod;
}

