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

// Enable this if you use s# variants with PyArg_ParseTuple(), see
// http://docs.python.org/py3k/c-api/arg.html#strings-and-buffers
//#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <datasrc/client.h>
#include <datasrc/database.h>
#include <datasrc/sqlite3_accessor.h>
#include <datasrc/iterator.h>

#include <dns/python/name_python.h>
#include <dns/python/rrset_python.h>

#include "datasrc.h"
#include "iterator_python.h"

#include "iterator_inc.cc"

using namespace std;
using namespace isc::util::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_ZoneIterator : public PyObject {
public:
    s_ZoneIterator() : cppobj(ZoneIteratorPtr()) {};
    ZoneIteratorPtr cppobj;
};

// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_ZoneIterator, ZoneIterator> ZoneIteratorContainer;


// General creation and destruction
int
ZoneIterator_init(s_ZoneIterator* self, PyObject* args) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneIterator cannot be constructed directly");

    return (-1);
}

// This is a template of typical code logic of python object destructor.
// In many cases you can use it without modification, but check that carefully.
void
ZoneIterator_destroy(s_ZoneIterator* const self) {
    // cppobj is a shared ptr, but to make sure things are not destroyed in
    // the wrong order, we reset it here.
    self->cppobj.reset();
    Py_TYPE(self)->tp_free(self);
}

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//
PyObject* ZoneIterator_getNextRRset(PyObject* po_self, PyObject*) {
    s_ZoneIterator* self = static_cast<s_ZoneIterator*>(po_self);
    try {
        isc::dns::ConstRRsetPtr rrset = self->cppobj->getNextRRset();
        if (!rrset) {
            Py_RETURN_NONE;
        }
        return (isc::dns::python::createRRsetObject(*rrset));
    } catch (const isc::Exception& isce) {
        // isc::Unexpected is thrown when we call getNextRRset() when we are
        // already done iterating ('iterating past end')
        // We could also simply return None again
        PyErr_SetString(getDataSourceException("Error"), isce.what());
        return (NULL);
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"), "Unexpected exception");
        return (NULL);
    }
}

// These are the functions we export
//

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneIterator_methods[] = {
    { "get_next_rrset", reinterpret_cast<PyCFunction>(ZoneIterator_getNextRRset),
      METH_NOARGS, ZoneIterator_getNextRRset_doc },
    { NULL, NULL, 0, NULL }
};


} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace python {
PyTypeObject zoneiterator_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneIterator",
    sizeof(s_ZoneIterator),             // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(ZoneIterator_destroy),       // tp_dealloc
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
    ZoneIterator_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    ZoneIterator_methods,               // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(ZoneIterator_init),// tp_init
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
createZoneIteratorObject(isc::datasrc::ZoneIteratorPtr source) {
    s_ZoneIterator* py_zi = static_cast<s_ZoneIterator*>(
        zoneiterator_type.tp_alloc(&zoneiterator_type, 0));
    if (py_zi != NULL) {
        py_zi->cppobj = source;
    }
    return (py_zi);
}

} // namespace python
} // namespace datasrc
} // namespace isc

