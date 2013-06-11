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

#include <datasrc/zone_table_accessor.h>

#include "datasrc.h"
#include "zonetable_accessor_python.h"
#include "zonetable_iterator_python.h"

using namespace std;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_ZoneTableAccessor : public PyObject {
public:
    s_ZoneTableAccessor() : cppobj(ConstZoneTableAccessorPtr()) {};
    ConstZoneTableAccessorPtr cppobj;
    // This is a reference to a base object; if the object of this class
    // depends on another object to be in scope during its lifetime,
    // we use INCREF the base object upon creation, and DECREF it at
    // the end of the destructor
    // This is an optional argument to createXXX(). If NULL, it is ignored.
    PyObject* base_obj;
};

int
ZoneTableAccessor_init(PyObject*, PyObject*, PyObject*) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneTableAccessor cannot be constructed directly");

    return (-1);
}

void
ZoneTableAccessor_destroy(PyObject* po_self) {
    s_ZoneTableAccessor* const self =
        static_cast<s_ZoneTableAccessor*>(po_self);
    // cppobj is a shared ptr, but to make sure things are not destroyed in
    // the wrong order, we reset it here.
    self->cppobj.reset();
    if (self->base_obj != NULL) {
        Py_DECREF(self->base_obj);
    }
    Py_TYPE(self)->tp_free(self);
}

PyObject*
ZoneTableAccessor_iter(PyObject* po_self) {
    s_ZoneTableAccessor* const self =
        static_cast<s_ZoneTableAccessor*>(po_self);
    try {
        return (createZoneTableIteratorObject(self->cppobj->getIterator(),
                                              po_self));
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unexpected exception");
        return (NULL);
    }
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneTableAccessor_methods[] = {
    { NULL, NULL, 0, NULL }
};

const char* const ZoneTableAccessor_doc = "\
An accessor to a zone table for a data source.\n\
\n\
This class object is intended to be used by applications that load zones\
into memory, so that the application can get a list of zones to be loaded.";

} // end anonymous namespace

namespace isc {
namespace datasrc {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_ZoneTableAccessor
// Most of the functions are not actually implemented and NULL here.
PyTypeObject zonetableaccessor_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneTableAccessor",
    sizeof(s_ZoneTableAccessor),         // tp_basicsize
    0,                                  // tp_itemsize
    ZoneTableAccessor_destroy,           // tp_dealloc
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
    ZoneTableAccessor_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    ZoneTableAccessor_iter,             // tp_iter
    NULL,                               // tp_iternext
    ZoneTableAccessor_methods,          // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ZoneTableAccessor_init,             // tp_init
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
createZoneTableAccessorObject(isc::datasrc::ConstZoneTableAccessorPtr source,
                              PyObject* base_obj)
{
    s_ZoneTableAccessor* py_zt = static_cast<s_ZoneTableAccessor*>(
        zonetableaccessor_type.tp_alloc(&zonetableaccessor_type, 0));
    if (py_zt != NULL) {
        py_zt->cppobj = source;
        py_zt->base_obj = base_obj;
        if (base_obj != NULL) {
            Py_INCREF(base_obj);
        }
    }
    return (py_zt);
}

} // namespace python
} // namespace datasrc
} // namespace isc
