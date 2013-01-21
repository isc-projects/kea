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

#include <exceptions/exceptions.h>

#include <dns/python/rrset_collection_python.h>
#include <dns/python/name_python.h>
#include <dns/python/rrtype_python.h>
#include <dns/python/rrclass_python.h>
#include <dns/python/rrset_python.h>
#include <dns/python/pydnspp_common.h>

#include <dns/rrset_collection_base.h>
#include <dns/rrset_collection.h>

#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace isc::util::python;
using namespace isc::dns;
using namespace isc::dns::python;

// Import pydoc text
#include "rrset_collection_python_inc.cc"

namespace {
// This is a template for a common pattern of type mismatch error handling,
// provided to save typing and repeating the mostly identical patterns.
PyObject*
setTypeError(PyObject* pobj, const char* var_name, const char* type_name) {
    PyErr_Format(PyExc_TypeError, "%s must be a %s, not %.200s",
                 var_name, type_name, pobj->ob_type->tp_name);
    return (NULL);
}
}

// RRsetCollectionBase: the base RRsetCollection class in Python.
//
// Any derived RRsetCollection class is supposed to be inherited from this
// class:
// - If the derived class is implemented via a C++ wrapper (associated with
//   a C++ implementation of RRsetCollection), its PyTypeObject should
//   specify rrset_collection_base_type for tp_base.  Its C/C++-representation
//   of objects should be compatible with s_RRsetCollection, and the wrapper
//   should set its cppobj member to point to the corresponding C++
//   RRsetCollection object.  Normally it doesn't have to provide Python
//   wrapper of find(); the Python interpreter will then call find() on
//   the base class, which ensures that the corresponding C++ version of
//   find() will be used.
// - If the derived class is implemented purely in Python, it must implement
//   find() in Python within the class.  As explained in the first bullet,
//   the base class method is generally expected to be used only for C++
//   wrapper of RRsetCollection derived class.
namespace {
int
RRsetCollectionBase_init(PyObject*, PyObject*, PyObject*) {
    PyErr_SetString(PyExc_TypeError,
                    "RRsetCollectionBase cannot be instantiated directly");
    return (-1);
}

void
RRsetCollectionBase_destroy(PyObject* po_self) {
    s_RRsetCollection* self = static_cast<s_RRsetCollection*>(po_self);

    // Any C++-wrapper of derived RRsetCollection class should have its own
    // destroy function (as it may manage cppobj in its own way);
    // Python-only derived classes shouldn't set cppobj (which is
    // 0-initialized).  So this assertion must hold.
    assert(self->cppobj == NULL);

    Py_TYPE(self)->tp_free(self);
}

PyObject*
RRsetCollectionBase_find(PyObject* po_self, PyObject* args) {
    s_RRsetCollection* self = static_cast<s_RRsetCollection*>(po_self);

    // If this function is called with cppobj being NULL, this means
    // a pure-Python derived class skips implementing its own find().
    // This is an error (see general description above).
    if (self->cppobj == NULL) {
        PyErr_Format(PyExc_TypeError, "find() is not implemented in the "
                     "derived RRsetCollection class");
        return (NULL);
    }

    try {
        PyObject* po_name;
        PyObject* po_rrclass;
        PyObject* po_rrtype;

        if (PyArg_ParseTuple(args, "OOO", &po_name, &po_rrclass, &po_rrtype)) {
            if (!PyName_Check(po_name)) {
                return (setTypeError(po_name, "name", "Name"));
            }
            if (!PyRRClass_Check(po_rrclass)) {
                return (setTypeError(po_rrclass, "rrclass", "RRClass"));
            }
            if (!PyRRType_Check(po_rrtype)) {
                return (setTypeError(po_rrtype, "rrtype", "RRType"));
            }
            ConstRRsetPtr found_rrset = self->cppobj->find(
                PyName_ToName(po_name), PyRRClass_ToRRClass(po_rrclass),
                PyRRType_ToRRType(po_rrtype));
            if (found_rrset) {
                return (createRRsetObject(*found_rrset));
            }
            Py_RETURN_NONE;
        }
    } catch (const RRsetCollectionError& ex) {
        PyErr_SetString(po_RRsetCollectionError, ex.what());
        return (NULL);
    } catch (const std::exception& ex) {
        const string ex_what = "Unexpected failure in "
            "RRsetCollectionBase.find: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    }

    return (NULL);
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef RRsetCollectionBase_methods[] = {
    { "find", RRsetCollectionBase_find, METH_VARARGS,
      RRsetCollectionBase_find_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
// Definition of class specific exception(s)
PyObject* po_RRsetCollectionError;

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_RRsetCollection
// Most of the functions are not actually implemented and NULL here.
PyTypeObject rrset_collection_base_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "dns.RRsetCollectionBase",
    sizeof(s_RRsetCollection),                 // tp_basicsize
    0,                                  // tp_itemsize
    RRsetCollectionBase_destroy,                 // tp_dealloc
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
    NULL,                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE, // tp_flags (it's inheritable)
    RRsetCollectionBase_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                 // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    RRsetCollectionBase_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    RRsetCollectionBase_init,           // tp_init
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
initModulePart_RRsetCollectionBase(PyObject* mod) {
    if (!initClass(rrset_collection_base_type, "RRsetCollectionBase", mod)) {
        return (false);
    }

    try {
        po_RRsetCollectionError =
            PyErr_NewException("dns.RRsetCollectionError",
                               po_IscException, NULL);
        PyObjectContainer(po_RRsetCollectionError).installToModule(
            mod, "RRsetCollectionError");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in RRsetCollectionBase initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "RRsetCollectionBase initialization");
        return (false);
    }

    return (true);
}

//
// RRsetCollection
//

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_RRsetCollection, RRsetCollection> RRsetCollectionContainer;

int
RRsetCollection_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_RRsetCollection* self = static_cast<s_RRsetCollection*>(po_self);
    try {
        const char* filename;
        PyObject* po_name;
        PyObject* po_rrclass;
        Py_buffer py_buf;

        if (PyArg_ParseTuple(args, "sO!O!", &filename, &name_type, &po_name,
                             &rrclass_type, &po_rrclass)) {
            self->cppobj =
                new RRsetCollection(filename, PyName_ToName(po_name),
                                    PyRRClass_ToRRClass(po_rrclass));
            return (0);
        } else if (PyArg_ParseTuple(args, "y*O!O!", &py_buf, &name_type,
                                    &po_name,&rrclass_type, &po_rrclass)) {
            PyErr_Clear();      // clear the error for the first ParseTuple
            const char* const cp = static_cast<const char*>(py_buf.buf);
            std::istringstream iss(string(cp, cp + py_buf.len));
            self->cppobj =
                new RRsetCollection(iss, PyName_ToName(po_name),
                                    PyRRClass_ToRRClass(po_rrclass));
            return (0);
        } else if (PyArg_ParseTuple(args, "")) {
            PyErr_Clear();      // clear the error for the second ParseTuple
            self->cppobj = new RRsetCollection;
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct RRsetCollection object: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (-1);
    }

    // Default error string isn't helpful when it takes multiple combinations
    // of args.  We provide our own.
    PyErr_SetString(PyExc_TypeError, "Invalid argument(s) to RRsetCollection "
                    "constructor; see pydoc");

    return (-1);
}

void
RRsetCollection_destroy(PyObject* po_self) {
    s_RRsetCollection* self = static_cast<s_RRsetCollection*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
RRsetCollection_addRRset(PyObject* po_self, PyObject* args) {
    s_RRsetCollection* self = static_cast<s_RRsetCollection*>(po_self);
    try {
        PyObject* po_rrset;
        if (PyArg_ParseTuple(args, "O", &po_rrset)) {
            if (!PyRRset_Check(po_rrset)) {
                return (setTypeError(po_rrset, "rrset", "RRset"));
            }
            static_cast<RRsetCollection*>(self->cppobj)->addRRset(
                PyRRset_ToRRsetPtr(po_rrset));
            Py_RETURN_NONE;
        }
    } catch (const InvalidParameter& ex) { // duplicate add
        PyErr_SetString(PyExc_ValueError, ex.what());
        return (NULL);
    } catch (const std::exception& ex) {
        const string ex_what = "Unexpected failure in "
            "RRsetCollection.add_rrset: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    }

    return (NULL);
}

PyObject*
RRsetCollection_removeRRset(PyObject* po_self, PyObject* args) {
    s_RRsetCollection* self = static_cast<s_RRsetCollection*>(po_self);
    try {
        PyObject* po_name;
        PyObject* po_rrclass;
        PyObject* po_rrtype;

        if (PyArg_ParseTuple(args, "OOO", &po_name, &po_rrclass, &po_rrtype)) {
            if (!PyName_Check(po_name)) {
                return (setTypeError(po_name, "name", "Name"));
            }
            if (!PyRRClass_Check(po_rrclass)) {
                return (setTypeError(po_rrclass, "rrclass", "RRClass"));
            }
            if (!PyRRType_Check(po_rrtype)) {
                return (setTypeError(po_rrtype, "rrtype", "RRType"));
            }
            const bool result =
                static_cast<RRsetCollection*>(self->cppobj)->removeRRset(
                    PyName_ToName(po_name), PyRRClass_ToRRClass(po_rrclass),
                    PyRRType_ToRRType(po_rrtype));
            if (result) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
        }
    } catch (...) {}

    return (NULL);
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef RRsetCollection_methods[] = {
    { "add_rrset", RRsetCollection_addRRset, METH_VARARGS,
      RRsetCollection_addRRset_doc },
    { "remove_rrset", RRsetCollection_removeRRset, METH_VARARGS,
      RRsetCollection_removeRRset_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_RRsetCollection
// Most of the functions are not actually implemented and NULL here.
PyTypeObject rrset_collection_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "dns.RRsetCollection",
    sizeof(s_RRsetCollection),                 // tp_basicsize
    0,                                  // tp_itemsize
    RRsetCollection_destroy,                 // tp_dealloc
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
    RRsetCollection_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    RRsetCollection_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    &rrset_collection_base_type,        // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    RRsetCollection_init,                    // tp_init
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
initModulePart_RRsetCollection(PyObject* mod) {
    if (!initClass(rrset_collection_type, "RRsetCollection", mod)) {
        return (false);
    }

    return (true);
}

} // namespace python
} // namespace dns
} // namespace isc
