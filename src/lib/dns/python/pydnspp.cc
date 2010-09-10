// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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


// We want a lot of different parts of the DNS API in the python
// module, but not one big 10000-line file.
// So we split it up in several 'mini-modules'
// These would be the same as a single module, except for
// the init function, which has to be modified to a unique
// name initModulePart_<name>, and return true/false instead of
// NULL/*mod
//
// And of course care has to be taken that all identifiers be unique

// $Id$

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <config.h>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>

#include <dns/python/pydnspp_common.h>

// For our 'general' isc::Exception
static PyObject* po_IscException;

// order is important here!
#include <dns/python/messagerenderer_python.cc>
#include <dns/python/name_python.cc>           // needs Messagerenderer
#include <dns/python/rrclass_python.cc>        // needs Messagerenderer
#include <dns/python/rrtype_python.cc>         // needs Messagerenderer
#include <dns/python/rrttl_python.cc>          // needs Messagerenderer
#include <dns/python/rdata_python.cc>          // needs Type, Class
#include <dns/python/rrset_python.cc>          // needs Rdata, RRTTL
#include <dns/python/question_python.cc>       // needs RRClass, RRType, RRTTL,
                                               // Name
#include <dns/python/message_python.cc>        // needs RRset, Question

//
// Definition of the module
//
static PyModuleDef pydnspp = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "pydnspp",
    "Python bindings for the classes in the isc::dns namespace.\n\n"
    "These bindings match the original C++ API as closely as possible, "
    "but are not complete. Some classes are unnecessary (InputBuffer "
    "and OutputBuffer for instance), and others may be necessary, but "
    "were not up to now.",
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC
PyInit_pydnspp(void) {
    PyObject *mod = PyModule_Create(&pydnspp);
    if (mod == NULL) {
        return (NULL);
    }

    po_IscException = PyErr_NewException("pydnspp.IscException", NULL, NULL);
    PyModule_AddObject(mod, "IscException", po_IscException);

    // for each part included above, we call its specific initializer

    if (!initModulePart_Name(mod)) {
        return (NULL);
    }

    if (!initModulePart_MessageRenderer(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRClass(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRType(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRTTL(mod)) {
        return (NULL);
    }

    if (!initModulePart_Rdata(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRset(mod)) {
        return (NULL);
    }

    if (!initModulePart_Question(mod)) {
        return (NULL);
    }

    if (!initModulePart_Message(mod)) {
        return (NULL);
    }

    return (mod);
}

