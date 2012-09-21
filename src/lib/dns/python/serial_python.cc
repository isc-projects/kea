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

#include <dns/serial.h>
#include <util/python/pycppwrapper_util.h>

#include "serial_python.h"
#include "pydnspp_common.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::python;
using namespace isc::util;
using namespace isc::util::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_Serial : public PyObject {
public:
    s_Serial() : cppobj(NULL) {};
    isc::dns::Serial* cppobj;
};

typedef CPPPyObjectContainer<s_Serial, Serial> SerialContainer;

PyObject* Serial_str(PyObject* self);
PyObject* Serial_getValue(s_Serial* self);
PyObject* Serial_richcmp(s_Serial* self, s_Serial* other, int op);
PyObject* Serial_add(PyObject *right, PyObject *left);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef Serial_methods[] = {
    { "get_value", reinterpret_cast<PyCFunction>(Serial_getValue), METH_NOARGS,
      "Returns the Serial value as an integer" },
    { NULL, NULL, 0, NULL }
};

// For overriding the + operator. We do not define any other operators for
// this type.
PyNumberMethods Serial_NumberMethods = {
    Serial_add, //nb_add;
    NULL, //nb_subtract;
    NULL, //nb_multiply;
    NULL, //nb_remainder;
    NULL, //nb_divmod;
    NULL, //nb_power;
    NULL, //nb_negative;
    NULL, //nb_positive;
    NULL, //nb_absolute;
    NULL, //nb_bool;
    NULL, //nb_invert;
    NULL, //nb_lshift;
    NULL, //nb_rshift;
    NULL, //nb_and;
    NULL, //nb_xor;
    NULL, //nb_or;
    NULL, //nb_int;
    NULL, //nb_reserved;
    NULL, //nb_float;

    NULL, //nb_inplace_add;
    NULL, //nb_inplace_subtract;
    NULL, //nb_inplace_multiply;
    NULL, //nb_inplace_remainder;
    NULL, //nb_inplace_power;
    NULL, //nb_inplace_lshift;
    NULL, //nb_inplace_rshift;
    NULL, //nb_inplace_and;
    NULL, //nb_inplace_xor;
    NULL, //nb_inplace_or;

    NULL, //nb_floor_divide;
    NULL, //nb_true_divide;
    NULL, //nb_inplace_floor_divide;
    NULL, //nb_inplace_true_divide;

    NULL, //nb_index;
};

int
Serial_init(s_Serial* self, PyObject* args) {
    long long i;
    if (PyArg_ParseTuple(args, "L", &i)) {
        PyErr_Clear();
        if (i < 0 || i > 0xffffffff) {
            PyErr_SetString(PyExc_ValueError, "Serial number out of range");
            return (-1);
        }
        self->cppobj = new Serial(i);
        return (0);
    } else {
        return (-1);
    }
}

void
Serial_destroy(s_Serial* self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
Serial_getValue(s_Serial* self) {
    return (Py_BuildValue("I", self->cppobj->getValue()));
}

PyObject*
Serial_str(PyObject* po_self) {
    const s_Serial* const self = static_cast<s_Serial*>(po_self);
    return (PyUnicode_FromFormat("%u", self->cppobj->getValue()));
}

PyObject*
Serial_richcmp(s_Serial* self, s_Serial* other, int op) {
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    switch (op) {
    case Py_LT:
        c = *self->cppobj < *other->cppobj;
        break;
    case Py_LE:
        c = *self->cppobj <= *other->cppobj;
        break;
    case Py_EQ:
        c = *self->cppobj == *other->cppobj;
        break;
    case Py_NE:
        c = *self->cppobj != *other->cppobj;
        break;
    case Py_GT:
        c = *self->cppobj > *other->cppobj;
        break;
    case Py_GE:
        c = *self->cppobj >= *other->cppobj;
        break;
    }
    if (c) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject *
Serial_add(PyObject *left, PyObject *right) {
    // Either can be either a serial or a long, as long as one of them is a
    // serial
    if (PySerial_Check(left) && PySerial_Check(right)) {
        return (createSerialObject(PySerial_ToSerial(left) +
                                   PySerial_ToSerial(right)));
    } else if (PySerial_Check(left) && PyLong_Check(right)) {
        return (createSerialObject(PySerial_ToSerial(left) +
                                   PyLong_AsLong(right)));
    } else if (PyLong_Check(left) && PySerial_Check(right)) {
        return (createSerialObject(PySerial_ToSerial(right) +
                                   PyLong_AsLong(left)));
    } else {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
}

} // end anonymous namespace

namespace isc {
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Serial
// Most of the functions are not actually implemented and NULL here.
PyTypeObject serial_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Serial",
    sizeof(s_Serial),                   // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Serial_destroy,         // tp_dealloc
    NULL,                               // tp_print
    NULL,                               // tp_getattr
    NULL,                               // tp_setattr
    NULL,                               // tp_reserved
    NULL,                               // tp_repr
    &Serial_NumberMethods,              // tp_as_number
    NULL,                               // tp_as_sequence
    NULL,                               // tp_as_mapping
    NULL,                               // tp_hash
    NULL,                               // tp_call
    Serial_str,                         // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Serial class encapsulates Serials used in DNS SOA records.\n\n"
    "This is a straightforward class; an Serial object simply maintains a "
    "32-bit unsigned integer corresponding to the SOA SERIAL value.  The "
    "main purpose of this class is to provide serial number arithmetic, as "
    "described in RFC 1892. Objects of this type can be compared and added "
    "to each other, as described in RFC 1892. Apart from str(), get_value(), "
    "comparison operators, and the + operator, no other operations are "
    "defined for this type.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)Serial_richcmp,        // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Serial_methods,                     // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Serial_init,              // tp_init
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
createSerialObject(const Serial& source) {
    SerialContainer container(PyObject_New(s_Serial, &serial_type));
    container.set(new Serial(source));
    return (container.release());
}

bool
PySerial_Check(PyObject* obj) {
    return (PyObject_TypeCheck(obj, &serial_type));
}

const Serial&
PySerial_ToSerial(const PyObject* serial_obj) {
    const s_Serial* serial = static_cast<const s_Serial*>(serial_obj);
    return (*serial->cppobj);
}

} // namespace python
} // namespace dns
} // namespace isc
