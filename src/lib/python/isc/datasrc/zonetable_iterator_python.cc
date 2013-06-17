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
#include <dns/python/name_python.h>

#include "datasrc.h"
#include "zonetable_iterator_python.h"

using namespace std;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_ZoneTableIterator : public PyObject {
public:
    s_ZoneTableIterator() :
        cppobj(ZoneTableAccessor::IteratorPtr()), base_obj(NULL)
    {};

    ZoneTableAccessor::IteratorPtr cppobj;
    // This is a reference to a base object; if the object of this class
    // depends on another object to be in scope during its lifetime,
    // we use INCREF the base object upon creation, and DECREF it at
    // the end of the destructor
    // This is an optional argument to createXXX(). If NULL, it is ignored.
    PyObject* base_obj;
};

// General creation and destruction
int
ZoneTableIterator_init(s_ZoneTableIterator*, PyObject*) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneTableIterator cannot be constructed directly");

    return (-1);
}

void
ZoneTableIterator_destroy(s_ZoneTableIterator* const self) {
    // cppobj is a shared ptr, but to make sure things are not destroyed in
    // the wrong order, we reset it here.
    self->cppobj.reset();
    if (self->base_obj != NULL) {
        Py_DECREF(self->base_obj);
    }
    Py_TYPE(self)->tp_free(self);
}

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//
PyObject*
ZoneTableIterator_iter(PyObject *self) {
    Py_INCREF(self);
    return (self);
}

PyObject*
ZoneTableIterator_next(PyObject* po_self) {
    s_ZoneTableIterator* self = static_cast<s_ZoneTableIterator*>(po_self);
    if (!self->cppobj || self->cppobj->isLast()) {
        return (NULL);
    }
    try {
        const isc::datasrc::ZoneSpec& zs = self->cppobj->getCurrent();
        PyObject* result =
            Py_BuildValue("iO", zs.index,
                          isc::dns::python::createNameObject(zs.origin));
        self->cppobj->next();
        return (result);
    } catch (const std::exception& exc) {
        // isc::InvalidOperation is thrown when we call getCurrent()
        // when we are already done iterating ('iterating past end')
        // We could also simply return None again
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unexpected exception");
        return (NULL);
    }
}

PyMethodDef ZoneTableIterator_methods[] = {
    { NULL, NULL, 0, NULL }
};

const char* const ZoneTableIterator_doc = "\
Read-only iterator to a zone table.\n\
\n\
You can get an instance of the ZoneTableIterator from the\
ZoneTableAccessor.get_iterator() method.\n\
\n\
There's no way to start iterating from the beginning again or return.\n\
\n\
The ZoneTableIterator is a Python iterator, and can be iterated over\
directly.\n\
";

} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace python {
PyTypeObject zonetableiterator_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneTableIterator",
    sizeof(s_ZoneTableIterator),        // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(ZoneTableIterator_destroy),// tp_dealloc
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
    ZoneTableIterator_doc,              // tp_doc
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    ZoneTableIterator_iter,             // tp_iter
    ZoneTableIterator_next,             // tp_iternext
    ZoneTableIterator_methods,          // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(ZoneTableIterator_init),// tp_init
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
createZoneTableIteratorObject(ZoneTableAccessor::IteratorPtr source,
                              PyObject* base_obj)
{
    s_ZoneTableIterator* py_zi = static_cast<s_ZoneTableIterator*>(
        zonetableiterator_type.tp_alloc(&zonetableiterator_type, 0));
    if (py_zi != NULL) {
        py_zi->cppobj = source;
        py_zi->base_obj = base_obj;
        if (base_obj != NULL) {
            Py_INCREF(base_obj);
        }
    }
    return (py_zi);
}

} // namespace python
} // namespace datasrc
} // namespace isc

