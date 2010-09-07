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

#include <dns/rdata.h>
using namespace isc::dns;
using namespace isc::dns::rdata;

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the initModulePart
// function at the end of this file
//
static PyObject* po_InvalidRdataLength;
static PyObject* po_InvalidRdataText;
static PyObject* po_CharStringTooLong;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// Rdata
//

// The s_* Class simply coverst one instantiation of the object

// Using a shared_ptr here should not really be necessary (PyObject
// is already reference-counted), however internally on the cpp side,
// not doing so might result in problems, since we can't copy construct
// rdata field, adding them to rrsets results in a problem when the
// rrset is destroyed later
class s_Rdata : public PyObject {
public:
    RdataPtr rdata;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
static int Rdata_init(s_Rdata* self, PyObject* args);
static void Rdata_destroy(s_Rdata* self);

// These are the functions we export
static PyObject* Rdata_toText(s_Rdata* self);
// This is a second version of toText, we need one where the argument
// is a PyObject*, for the str() function in python.
static PyObject* Rdata_str(PyObject* self);
static PyObject* Rdata_toWire(s_Rdata* self, PyObject* args);
static PyObject* RData_richcmp(s_Rdata* self, s_Rdata* other, int op);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
static PyMethodDef Rdata_methods[] = {
    { "to_text", reinterpret_cast<PyCFunction>(Rdata_toText), METH_NOARGS,
      "Returns the string representation" },
    { "to_wire", reinterpret_cast<PyCFunction>(Rdata_toWire), METH_VARARGS,
      "Converts the Rdata object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { NULL, NULL, 0, NULL }
};

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Rdata
// Most of the functions are not actually implemented and NULL here.
static PyTypeObject rdata_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Rdata",
    sizeof(s_Rdata),                    // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Rdata_destroy,          // tp_dealloc
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
    Rdata_str,                          // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Rdata class is an abstract base class that provides "
    "a set of common interfaces to manipulate concrete RDATA objects.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)RData_richcmp,         // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Rdata_methods,                      // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Rdata_init,               // tp_init
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
Rdata_init(s_Rdata* self, PyObject* args) {
    s_RRType* rrtype;
    s_RRClass* rrclass;
    const char* s;
    
    if (PyArg_ParseTuple(args, "O!O!s", &rrtype_type, &rrtype,
                                        &rrclass_type, &rrclass,
                                        &s)) {
        self->rdata = createRdata(*rrtype->rrtype, *rrclass->rrclass, s);
        return (0);
    }

    return (-1);
}

static void
Rdata_destroy(s_Rdata* self) {
    // Clear the shared_ptr so that its reference count is zero
    // before we call tp_free() (there is no direct release())
    self->rdata.reset();
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Rdata_toText(s_Rdata* self) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", self->rdata->toText().c_str()));
}

static PyObject*
Rdata_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

static PyObject*
Rdata_toWire(s_Rdata* self, PyObject* args) {
    PyObject* bytes;
    s_MessageRenderer* mr;
    
    if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;
        
        OutputBuffer buffer(4);
        self->rdata->toWire(buffer);
        PyObject* rd_bytes = PyBytes_FromStringAndSize(static_cast<const char*>(buffer.getData()), buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, rd_bytes);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(rd_bytes);
        return (result);
    } else if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, (PyObject**) &mr)) {
        self->rdata->toWire(*mr->messagerenderer);
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
RData_richcmp(s_Rdata* self, s_Rdata* other, int op) {
    bool c;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    switch (op) {
    case Py_LT:
        c = self->rdata->compare(*other->rdata) < 0;
        break;
    case Py_LE:
        c = self->rdata->compare(*other->rdata) < 0 ||
            self->rdata->compare(*other->rdata) == 0;
        break;
    case Py_EQ:
        c = self->rdata->compare(*other->rdata) == 0;
        break;
    case Py_NE:
        c = self->rdata->compare(*other->rdata) != 0;
        break;
    case Py_GT:
        c = self->rdata->compare(*other->rdata) > 0;
        break;
    case Py_GE:
        c = self->rdata->compare(*other->rdata) > 0 ||
            self->rdata->compare(*other->rdata) == 0;
        break;
    default:
        PyErr_SetString(PyExc_IndexError,
                        "Unhandled rich comparison operator");
        return (NULL);
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}
// end of Rdata


// Module Initialization, all statics are initialized here
bool
initModulePart_Rdata(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&rdata_type) < 0) {
        return (false);
    }
    Py_INCREF(&rdata_type);
    PyModule_AddObject(mod, "Rdata",
                       reinterpret_cast<PyObject*>(&rdata_type));

    // Add the exceptions to the class
    po_InvalidRdataLength = PyErr_NewException("pydnspp.InvalidRdataLength", NULL, NULL);
    PyModule_AddObject(mod, "InvalidRdataLength", po_InvalidRdataLength);

    po_InvalidRdataText = PyErr_NewException("pydnspp.InvalidRdataText", NULL, NULL);
    PyModule_AddObject(mod, "InvalidRdataText", po_InvalidRdataText);

    po_CharStringTooLong = PyErr_NewException("pydnspp.CharStringTooLong", NULL, NULL);
    PyModule_AddObject(mod, "CharStringTooLong", po_CharStringTooLong);

    
    return (true);
}
