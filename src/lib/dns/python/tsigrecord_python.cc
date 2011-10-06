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

#include <Python.h>

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <dns/tsigrecord.h>

#include "pydnspp_common.h"
#include "pydnspp_towire.h"
#include "name_python.h"
#include "tsig_rdata_python.h"
#include "tsigrecord_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns;
using namespace isc::dns::python;

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// TSIGRecord
//

namespace {
// The s_* Class simply covers one instantiation of the object
class s_TSIGRecord : public PyObject {
public:
    s_TSIGRecord() : cppobj(NULL) {};
    TSIGRecord* cppobj;
};

// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_TSIGRecord, TSIGRecord> TSIGRecordContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int TSIGRecord_init(s_TSIGRecord* self, PyObject* args);
void TSIGRecord_destroy(s_TSIGRecord* self);
PyObject* TSIGRecord_toText(const s_TSIGRecord* const self);
PyObject* TSIGRecord_str(PyObject* self);
PyObject* TSIGRecord_toWire(const s_TSIGRecord* self, PyObject* args);
PyObject* TSIGRecord_getName(const s_TSIGRecord* self);
PyObject* TSIGRecord_getLength(const s_TSIGRecord* self);
PyObject* TSIGRecord_getRdata(const s_TSIGRecord* self);

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef TSIGRecord_methods[] = {
    { "get_name", reinterpret_cast<PyCFunction>(TSIGRecord_getName),
      METH_NOARGS,
      "Return the owner name of the TSIG RR, which is the TSIG key name" },
    { "get_length", reinterpret_cast<PyCFunction>(TSIGRecord_getLength),
      METH_NOARGS,
      "Return the length of the TSIG record" },
    { "get_rdata", reinterpret_cast<PyCFunction>(TSIGRecord_getRdata),
      METH_NOARGS,
      "Return the RDATA of the TSIG RR" },
    { "to_text", reinterpret_cast<PyCFunction>(TSIGRecord_toText), METH_NOARGS,
      "Returns the text representation" },
    { "to_wire", reinterpret_cast<PyCFunction>(TSIGRecord_toWire),
      METH_VARARGS,
      "Converts the TSIGRecord object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { NULL, NULL, 0, NULL }
};

int
TSIGRecord_init(s_TSIGRecord* self, PyObject* args) {
    try {
        const PyObject* py_name;
        const PyObject* py_tsig;
        if (PyArg_ParseTuple(args, "O!O!", &name_type, &py_name,
                             &tsig_type, &py_tsig)) {
            self->cppobj = new TSIGRecord(PyName_ToName(py_name),
                                          PyTSIG_ToTSIG(py_tsig));
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct TSIGRecord object: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in constructing TSIGRecord");
        return (-1);
    }

    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to TSIGRecord constructor");

    return (-1);
}

// This is a template of typical code logic of python object destructor.
// In many cases you can use it without modification, but check that carefully.
void
TSIGRecord_destroy(s_TSIGRecord* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

// This should be able to be used without modification as long as the
// underlying C++ class has toText().
PyObject*
TSIGRecord_toText(const s_TSIGRecord* const self) {
    try {
        // toText() could throw, so we need to catch any exceptions below.
        return (Py_BuildValue("s", self->cppobj->toText().c_str()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to convert TSIGRecord object to text: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "converting TSIGRecord object to text");
    }
    return (NULL);
}

PyObject*
TSIGRecord_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self, const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
TSIGRecord_toWire(const s_TSIGRecord* const self, PyObject* args) {
    typedef ToWireCallInt<const TSIGRecord> ToWireCall;
    PyObject* (*towire_fn)(const s_TSIGRecord* const, PyObject*) =
        toWireWrapper<s_TSIGRecord, TSIGRecord, ToWireCall>;
    return (towire_fn(self, args));
}

PyObject*
TSIGRecord_getName(const s_TSIGRecord* const self) {
    try {
        return (createNameObject(self->cppobj->getName()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to get TSIGRecord name: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "getting TSIGRecord name");
    }
    return (NULL);
}

PyObject*
TSIGRecord_getLength(const s_TSIGRecord* const self) {
    return (Py_BuildValue("H", self->cppobj->getLength()));
}

PyObject*
TSIGRecord_getRdata(const s_TSIGRecord* const self) {
    try {
        return (createTSIGObject(self->cppobj->getRdata()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to get TSIGRecord RDATA: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "getting TSIGRecord RDATA");
    }
    return (NULL);
}

} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_TSIGRecord
// Most of the functions are not actually implemented and NULL here.
PyTypeObject tsigrecord_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.TSIGRecord",
    sizeof(s_TSIGRecord),                 // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(TSIGRecord_destroy),       // tp_dealloc
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
    TSIGRecord_str,                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The TSIGRecord class objects is...(COMPLETE THIS)",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    TSIGRecord_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(TSIGRecord_init),            // tp_init
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
createTSIGRecordObject(const TSIGRecord& source) {
    TSIGRecordContainer container(PyObject_New(s_TSIGRecord, &tsigrecord_type));
    container.set(new TSIGRecord(source));
    return (container.release());
}

bool
PyTSIGRecord_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &tsigrecord_type));
}

const TSIGRecord&
PyTSIGRecord_ToTSIGRecord(PyObject* tsigrecord_obj) {
    if (tsigrecord_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in TSIGRecord PyObject conversion");
    }
    s_TSIGRecord* tsigrecord = static_cast<s_TSIGRecord*>(tsigrecord_obj);
    return (*tsigrecord->cppobj);
}


} // namespace python
} // namespace dns
} // namespace isc
