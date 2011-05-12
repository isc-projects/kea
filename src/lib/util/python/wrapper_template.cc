// Copyright (C) @YEAR@  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include "@cppclass@_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::@MODULE@;
using namespace isc::@MODULE@::python;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// @CPPCLASS@
//

// Trivial constructor.
s_@CPPCLASS@::s_@CPPCLASS@() : cppobj(NULL) {
}

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_@CPPCLASS@, @CPPCLASS@> @CPPCLASS@Container;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int @CPPCLASS@_init(s_@CPPCLASS@* self, PyObject* args);
void @CPPCLASS@_destroy(s_@CPPCLASS@* self);

// These are the functions we export
// ADD/REMOVE/MODIFY THE FOLLOWING AS APPROPRIATE FOR THE ACTUAL CLASS.
//
PyObject* @CPPCLASS@_toText(const s_@CPPCLASS@* const self);
PyObject* @CPPCLASS@_str(PyObject* self);
PyObject* @CPPCLASS@_richcmp(const s_@CPPCLASS@* const self,
                            const s_@CPPCLASS@* const other, int op);

// This is quite specific pydnspp.  For other wrappers this should probably
// be removed.
PyObject* @CPPCLASS@_toWire(const s_@CPPCLASS@* self, PyObject* args);

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef @CPPCLASS@_methods[] = {
    { "to_text", reinterpret_cast<PyCFunction>(@CPPCLASS@_toText), METH_NOARGS,
      "Returns the text representation" },
    // This is quite specific pydnspp.  For other wrappers this should probably
    // be removed:
    { "to_wire", reinterpret_cast<PyCFunction>(@CPPCLASS@_toWire), METH_VARARGS,
      "Converts the @CPPCLASS@ object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { NULL, NULL, 0, NULL }
};

// This is a template of typical code logic of python class initialization
// with C++ backend.  You'll need to adjust it according to details of the
// actual C++ class.
int
@CPPCLASS@_init(s_@CPPCLASS@* self, PyObject* args) {
    try {
        if (PyArg_ParseTuple(args, "REPLACE ME")) {
            // YOU'LL NEED SOME VALIDATION, PREPARATION, ETC, HERE.
            self->cppobj = new @CPPCLASS@(/*NECESSARY PARAMS*/);
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct @CPPCLASS@ object: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in constructing @CPPCLASS@");
        return (-1);
    }

    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to @CPPCLASS@ constructor");

    return (-1);
}

// This is a template of typical code logic of python object destructor.
// In many cases you can use it without modification, but check that carefully.
void
@CPPCLASS@_destroy(s_@CPPCLASS@* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

// This should be able to be used without modification as long as the
// underlying C++ class has toText().
PyObject*
@CPPCLASS@_toText(const s_@CPPCLASS@* const self) {
    try {
        // toText() could throw, so we need to catch any exceptions below.
        return (Py_BuildValue("s", self->cppobj->toText().c_str()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to convert @CPPCLASS@ object to text: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "converting @CPPCLASS@ object to text");
    }
    return (NULL);
}

PyObject*
@CPPCLASS@_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self, const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject* 
@CPPCLASS@_richcmp(const s_@CPPCLASS@* const self,
                   const s_@CPPCLASS@* const other,
                   const int op)
{
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (other == NULL || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; @CPPCLASS@");
        return (NULL);
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; @CPPCLASS@");
        return (NULL);
    case Py_EQ:
        c = (*self->cppobj == *other->cppobj);
        break;
    case Py_NE:
        c = (*self->cppobj != *other->cppobj);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; @CPPCLASS@");
        return (NULL);
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; @CPPCLASS@");
        return (NULL);
    }
    if (c) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}
} // end of unnamed namespace

namespace isc {
namespace @MODULE@ {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_@CPPCLASS@
// Most of the functions are not actually implemented and NULL here.
PyTypeObject @cppclass@_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.@CPPCLASS@",
    sizeof(s_@CPPCLASS@),                 // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(@CPPCLASS@_destroy),       // tp_dealloc
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
    // THIS MAY HAVE TO BE CHANGED TO NULL:
    @CPPCLASS@_str,                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The @CPPCLASS@ class objects is...(COMPLETE THIS)",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    // THIS MAY HAVE TO BE CHANGED TO NULL:
    reinterpret_cast<richcmpfunc>(@CPPCLASS@_richcmp), // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    @CPPCLASS@_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(@CPPCLASS@_init),            // tp_init
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
initModulePart_@CPPCLASS@(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&@cppclass@_type) < 0) {
        return (false);
    }
    void* p = &@cppclass@_type;
    if (PyModule_AddObject(mod, "@CPPCLASS@", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&@cppclass@_type);

    // The following template is the typical procedure for installing class
    // variables.  If the class doesn't have a class variable, remove the
    // entire try-catch clauses.
    try {
        // Constant class variables
        installClassVariable(@cppclass@_type, "REPLACE_ME",
                             Py_BuildValue("REPLACE ME"));
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure in @CPPCLASS@ initialization: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in @CPPCLASS@ initialization");
        return (false);
    }

    return (true);
}

PyObject*
create@CPPCLASS@Object(const @CPPCLASS@& source) {
    @CPPCLASS@Container container =
        PyObject_New(s_@CPPCLASS@, &@cppclass@_type);
    container.set(new @CPPCLASS@(source));
    return (container.release());
}
} // namespace python
} // namespace @MODULE@
} // namespace isc
