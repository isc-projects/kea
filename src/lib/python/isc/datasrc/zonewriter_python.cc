// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/memory/zone_writer.h>

#include "zonewriter_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::python;

//
// ZoneWriter
//

// Trivial constructor.
s_ZoneWriter::s_ZoneWriter() : cppobj(NULL) {
}

namespace {

int
ZoneWriter_init(PyObject*, PyObject*, PyObject*) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneWriter cannot be constructed directly");

    return (-1);
}

void
ZoneWriter_destroy(PyObject* po_self) {
    s_ZoneWriter* self = static_cast<s_ZoneWriter*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneWriter_methods[] = {
    { NULL, NULL, 0, NULL }
};

const char* const ZoneWriter_doc = "\
Does an update to a zone\n\
\n\
This represents the work of a (re)load of a zone.  The work is divided\n\
into three stages -- load(), install() and cleanup().  They should\n\
be called in this order for the effect to take place.\n\
";

} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace memory {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_ZoneWriter
// Most of the functions are not actually implemented and NULL here.
PyTypeObject zonewriter_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneWriter",
    sizeof(s_ZoneWriter),               // tp_basicsize
    0,                                  // tp_itemsize
    ZoneWriter_destroy,                 // tp_dealloc
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
    ZoneWriter_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    ZoneWriter_methods,                 // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ZoneWriter_init,                    // tp_init
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
initModulePart_ZoneWriter(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&zonewriter_type) < 0) {
        return (false);
    }
    void* p = &zonewriter_type;
    if (PyModule_AddObject(mod, "ZoneWriter", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&zonewriter_type);

    return (true);
}

} // namespace python
} // namespace memory
} // namespace datasrc
} // namespace isc
