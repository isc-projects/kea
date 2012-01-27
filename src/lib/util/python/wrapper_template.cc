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

// Enable this if you use s# variants with PyArg_ParseTuple(), see
// http://docs.python.org/py3k/c-api/arg.html#strings-and-buffers
//#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include "@cppclass@_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::@MODULE@;
using namespace isc::@MODULE@::python;

//
// @CPPCLASS@
//

// Trivial constructor.
s_@CPPCLASS@::s_@CPPCLASS@() : cppobj(NULL) {
}

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_@CPPCLASS@, @CPPCLASS@> @CPPCLASS@Container;

@REMOVE_THIS_ON_RELEASE@
// This is a template of typical code logic of python class initialization
// with C++ backend.  You'll need to adjust it according to details of the
// actual C++ class.
int
@CPPCLASS@_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_@CPPCLASS@* self = static_cast<s_@CPPCLASS@*>(po_self);
    try {
        if (PyArg_ParseTuple(args, "REPLACE ME")) {
            @REMOVE_THIS_ON_RELEASE@
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
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (-1);
    }

    @REMOVE_THIS_ON_RELEASE@
    // If we are here PyArg_ParseTuple() failed and TypeError should have
    // been set.  If the constructor is more complicated and the control
    // could reach this point for other reasons, an appropriate Python
    // exception should be set by PyErr_SetString.

    return (-1);
}

@REMOVE_THIS_ON_RELEASE@
// This is a template of typical code logic of python object destructor.
// In many cases you can use it without modification, but check that carefully.
void
@CPPCLASS@_destroy(PyObject* po_self) {
    s_@CPPCLASS@* self = static_cast<s_@CPPCLASS@*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

@REMOVE_THIS_ON_RELEASE@
// This should be able to be used without modification as long as the
// underlying C++ class has toText().
PyObject*
@CPPCLASS@_toText(PyObject* po_self) {
    const s_@CPPCLASS@* self = static_cast<const s_@CPPCLASS@*>(po_self);
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

@REMOVE_THIS_ON_RELEASE@
// This is quite specific isc.dns.  For other wrappers this should probably
// be removed.
PyObject* @CPPCLASS@_toWire(PyObject* self, PyObject* args) {
}

PyObject* 
@CPPCLASS@_richcmp(PyObject* po_self, PyObject* po_other, const int op) {
    const s_@CPPCLASS@* const self = static_cast<const s_@CPPCLASS@*>(po_self);
    const s_@CPPCLASS@* const other =
        static_cast<const s_@CPPCLASS@*>(po_other);

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

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef @CPPCLASS@_methods[] = {
    { "to_text", @CPPCLASS@_toText, METH_NOARGS,
      @CPPCLASS@_toText_doc },

    @REMOVE_THIS_ON_RELEASE@
    // This is quite specific isc.dns.  For other wrappers this should probably
    // be removed:
    { "to_wire", @CPPCLASS@_toWire, METH_VARARGS,
      @CPPCLASS@_toWire_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace @MODULE@ {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_@CPPCLASS@
// Most of the functions are not actually implemented and NULL here.
PyTypeObject @cppclass@_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "@MODULE@.@CPPCLASS@",
    sizeof(s_@CPPCLASS@),                 // tp_basicsize
    0,                                  // tp_itemsize
    @CPPCLASS@_destroy,                 // tp_dealloc
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
    @CPPCLASS@_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    // THIS MAY HAVE TO BE CHANGED TO NULL:
    @CPPCLASS@_richcmp,                 // tp_richcompare
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
    @CPPCLASS@_init,                    // tp_init
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

    @REMOVE_THIS_ON_RELEASE@
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
    @CPPCLASS@Container container(PyObject_New(s_@CPPCLASS@,
                                               &@cppclass@_type));
    container.set(new @CPPCLASS@(source));
    return (container.release());
}
} // namespace python
} // namespace @MODULE@
} // namespace isc
