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

#include <dns/tsig.h>

using namespace isc::dns;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

namespace {
// The s_* Class simply covers one instantiation of the object
class s_TSIGContext : public PyObject {
public:
    TSIGContext* tsig_ctx;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int TSIGContext_init(s_TSIGContext* self, PyObject* args);
void TSIGContext_destroy(s_TSIGContext* self);

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef TSIGContext_methods[] = {
    { NULL, NULL, 0, NULL }
};

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_EDNS
// Most of the functions are not actually implemented and NULL here.
PyTypeObject tsig_context_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.TSIGContext",
    sizeof(s_TSIGContext),              // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)TSIGContext_destroy,    // tp_dealloc
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
    "The TSIGContext class maintains a context of a signed session of "
    "DNS transactions by TSIG.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    TSIGContext_methods,                // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)TSIGContext_init,         // tp_init
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

int
TSIGContext_init(s_TSIGContext* self, PyObject* args) {
    const s_TSIGKey* tsigkey_obj;

    try {
        if (PyArg_ParseTuple(args, "O!", &tsigkey_type, &tsigkey_obj)) {
            self->tsig_ctx = new TSIGContext(*tsigkey_obj->tsigkey);
            return (0);
        }
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
        return (-1);
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to TSIGContext constructor");

    return (-1);
}

void
TSIGContext_destroy(s_TSIGContext* const self) {
    delete self->tsig_ctx;
    self->tsig_ctx = NULL;
    Py_TYPE(self)->tp_free(self);
}

// Module Initialization, all statics are initialized here
bool
initModulePart_TSIGContext(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&tsig_context_type) < 0) {
        return (false);
    }
    Py_INCREF(&tsig_context_type);
    void* p = &tsig_context_type;
    PyModule_AddObject(mod, "TSIGContext", static_cast<PyObject*>(p));

    addClassVariable(tsig_context_type, "DEFAULT_FUDGE",
                     Py_BuildValue("H", TSIGContext::DEFAULT_FUDGE));

    return (true);
}
} // end of anonymous namespace
