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

// $Id$

#include <vector>

#include <dns/rrttl.h>

using namespace std;
using namespace isc::dns;

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the initModulePart
// function at the end of this file
//
static PyObject* po_InvalidRRTTL;
static PyObject* po_IncompleteRRTTL;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// RRTTL
//

// The s_* Class simply covers one instantiation of the object
class s_RRTTL : public PyObject {
public:
    RRTTL* rrttl;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
static int RRTTL_init(s_RRTTL* self, PyObject* args);
static void RRTTL_destroy(s_RRTTL* self);

// These are the functions we export
static PyObject* RRTTL_toText(s_RRTTL* self);
// This is a second version of toText, we need one where the argument
// is a PyObject*, for the str() function in python.
static PyObject* RRTTL_str(PyObject* self);
static PyObject* RRTTL_toWire(s_RRTTL* self, PyObject* args);
static PyObject* RRTTL_getValue(s_RRTTL* self);
static PyObject* RRTTL_richcmp(s_RRTTL* self, s_RRTTL* other, int op);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
static PyMethodDef RRTTL_methods[] = {
    { "to_text", reinterpret_cast<PyCFunction>(RRTTL_toText), METH_NOARGS,
      "Returns the string representation" },
    { "to_wire", reinterpret_cast<PyCFunction>(RRTTL_toWire), METH_VARARGS,
      "Converts the RRTTL object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { "get_value", reinterpret_cast<PyCFunction>(RRTTL_getValue), METH_NOARGS,
      "Returns the TTL as an integer" },
    { NULL, NULL, 0, NULL }
};

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_RRTTL
// Most of the functions are not actually implemented and NULL here.
static PyTypeObject rrttl_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.RRTTL",
    sizeof(s_RRTTL),                    // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)RRTTL_destroy,          // tp_dealloc
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
    RRTTL_str,                          // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The RRTTL class encapsulates TTLs used in DNS resource records.\n\n"
    "This is a straightforward class; an RRTTL object simply maintains a "
    "32-bit unsigned integer corresponding to the TTL value.  The main purpose "
    "of this class is to provide convenient interfaces to convert a textual "
    "representation into the integer TTL value and vice versa, and to handle "
    "wire-format representations.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)RRTTL_richcmp,         // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    RRTTL_methods,                      // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)RRTTL_init,               // tp_init
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

static int
RRTTL_init(s_RRTTL* self, PyObject* args) {
    const char* s;
    unsigned long i;
    PyObject* bytes = NULL;
    // The constructor argument can be a string ("1234"), an integer (1),
    // or a sequence of numbers between 0 and 255 (wire code)

    // Note that PyArg_ParseType can set PyError, and we need to clear
    // that if we try several like here. Otherwise the *next* python
    // call will suddenly appear to throw an exception.
    // (the way to do exceptions is to set PyErr and return -1)
    try {
        if (PyArg_ParseTuple(args, "s", &s)) {
            self->rrttl = new RRTTL(s);
            return (0);
        } else if (PyArg_ParseTuple(args, "I", &i)) {
            PyErr_Clear();
            self->rrttl = new RRTTL(i);
            return (0);
        } else if (PyArg_ParseTuple(args, "O", &bytes) &&
                   PySequence_Check(bytes)) {
            Py_ssize_t size = PySequence_Size(bytes);
            vector<uint8_t> data(size);
            int result = readDataFromSequence(&data[0], size, bytes);
            if (result != 0) {
                return (result);
            }
            InputBuffer ib(&data[0], size);
            self->rrttl = new RRTTL(ib);
            PyErr_Clear();
            return (0);
        }
    } catch (const IncompleteRRTTL& icc) {
        // Ok so one of our functions has thrown a C++ exception.
        // We need to translate that to a Python Exception
        // First clear any existing error that was set
        PyErr_Clear();
        // Now set our own exception
        PyErr_SetString(po_IncompleteRRTTL, icc.what());
        // And return negative
        return (-1);
    } catch (const InvalidRRTTL& ic) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidRRTTL, ic.what());
        return (-1);
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "no valid type in constructor argument");
    return (-1);
}

static void
RRTTL_destroy(s_RRTTL* self) {
    delete self->rrttl;
    self->rrttl = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
RRTTL_toText(s_RRTTL* self) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", self->rrttl->toText().c_str()));
}

static PyObject*
RRTTL_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

static PyObject*
RRTTL_toWire(s_RRTTL* self, PyObject* args) {
    PyObject* bytes;
    s_MessageRenderer* mr;
    
    if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;
        
        OutputBuffer buffer(4);
        self->rrttl->toWire(buffer);
        PyObject* n = PyBytes_FromStringAndSize(static_cast<const char*>(buffer.getData()),
                                                buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, n);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(n);
        return (result);
    } else if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, (PyObject**) &mr)) {
        self->rrttl->toWire(*mr->messagerenderer);
        // If we return NULL it is seen as an error, so use this for
        // None returns
        Py_RETURN_NONE;
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a sequence object or a MessageRenderer");
    return (NULL);
}

static PyObject*
RRTTL_getValue(s_RRTTL* self) {
    return (Py_BuildValue("I", self->rrttl->getValue()));
}

static PyObject* 
RRTTL_richcmp(s_RRTTL* self, s_RRTTL* other, int op) {
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    switch (op) {
    case Py_LT:
        c = *self->rrttl < *other->rrttl;
        break;
    case Py_LE:
        c = *self->rrttl < *other->rrttl ||
            *self->rrttl == *other->rrttl;
        break;
    case Py_EQ:
        c = *self->rrttl == *other->rrttl;
        break;
    case Py_NE:
        c = *self->rrttl != *other->rrttl;
        break;
    case Py_GT:
        c = *other->rrttl < *self->rrttl;
        break;
    case Py_GE:
        c = *other->rrttl < *self->rrttl ||
            *self->rrttl == *other->rrttl;
        break;
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}
// end of RRTTL


// Module Initialization, all statics are initialized here
bool
initModulePart_RRTTL(PyObject* mod) {
    // Add the exceptions to the module
    po_InvalidRRTTL = PyErr_NewException("pydnspp.InvalidRRTTL", NULL, NULL);
    PyModule_AddObject(mod, "InvalidRRTTL", po_InvalidRRTTL);
    po_IncompleteRRTTL = PyErr_NewException("pydnspp.IncompleteRRTTL", NULL, NULL);
    PyModule_AddObject(mod, "IncompleteRRTTL", po_IncompleteRRTTL);

    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&rrttl_type) < 0) {
        return (false);
    }
    Py_INCREF(&rrttl_type);
    PyModule_AddObject(mod, "RRTTL",
                       reinterpret_cast<PyObject*>(&rrttl_type));
    
    return (true);
}
