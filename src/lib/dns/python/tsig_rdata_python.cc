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

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <dns/rdataclass.h>

#include "pydnspp_common.h"
#include "pydnspp_towire.h"
#include "name_python.h"
#include "tsig_rdata_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::python;

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

namespace {
// The s_* Class simply covers one instantiation of the object
class s_TSIG : public PyObject {
public:
    s_TSIG() : cppobj(NULL) {};
    const rdata::any::TSIG* cppobj;
};


// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_TSIG, any::TSIG> TSIGContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int TSIG_init(s_TSIG* self, PyObject* args);
void TSIG_destroy(s_TSIG* self);

// These are the functions we export
// ADD/REMOVE/MODIFY THE FOLLOWING AS APPROPRIATE FOR THE ACTUAL CLASS.
//
PyObject* TSIG_toText(const s_TSIG* const self);
PyObject* TSIG_getAlgorithm(const s_TSIG* const self);
PyObject* TSIG_getTimeSigned(const s_TSIG* const self);
PyObject* TSIG_getFudge(const s_TSIG* const self);
PyObject* TSIG_getOriginalID(const s_TSIG* const self);
PyObject* TSIG_getError(const s_TSIG* const self);
PyObject* TSIG_getMAC(const s_TSIG* const self);
PyObject* TSIG_getOtherData(const s_TSIG* const self);
PyObject* TSIG_str(PyObject* self);
PyObject* TSIG_richcmp(const s_TSIG* const self,
                       const s_TSIG* const other, int op);
PyObject* TSIG_toWire(const s_TSIG* self, PyObject* args);

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef TSIG_methods[] = {
    { "get_algorithm", reinterpret_cast<PyCFunction>(TSIG_getAlgorithm),
      METH_NOARGS,
      "Return the algorithm name." },
    { "get_timesigned", reinterpret_cast<PyCFunction>(TSIG_getTimeSigned),
      METH_NOARGS,
      "Return the value of the Time Signed field. "
      "The returned value does not exceed 2^48-1."
    },
    { "get_fudge", reinterpret_cast<PyCFunction>(TSIG_getFudge),
      METH_NOARGS,
      "Return the value of the Fudge field." },
    { "get_original_id", reinterpret_cast<PyCFunction>(TSIG_getOriginalID),
      METH_NOARGS,
      "Return the value of the Original ID field." },
    { "get_error", reinterpret_cast<PyCFunction>(TSIG_getError),
      METH_NOARGS,
      "Return the value of the Error field." },
    { "get_mac", reinterpret_cast<PyCFunction>(TSIG_getMAC),
      METH_NOARGS,
      "Return the value of the MAC field."
      "If it's empty, return None." },
    { "get_other_data", reinterpret_cast<PyCFunction>(TSIG_getOtherData),
      METH_NOARGS,
      "Return the value of the Other Data field."
      "If it's empty, return None." },
    { "to_text", reinterpret_cast<PyCFunction>(TSIG_toText), METH_NOARGS,
      "Returns the text representation" },
    { "to_wire", reinterpret_cast<PyCFunction>(TSIG_toWire), METH_VARARGS,
      "Converts the TSIG object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { NULL, NULL, 0, NULL }
};

int
TSIG_init(s_TSIG* self, PyObject* args) {
    try {
        // constructor from string
        const char* rdata_str;
        if (PyArg_ParseTuple(args, "s", &rdata_str)) {
            self->cppobj = new any::TSIG(string(rdata_str));
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct TSIG object: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in constructing TSIG");
        return (-1);
    }

    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to TSIG constructor");

    return (-1);
}

void
TSIG_destroy(s_TSIG* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
TSIG_getAlgorithm(const s_TSIG* const self) {
    try {
        return (createNameObject(self->cppobj->getAlgorithm()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to get TSIG algorithm: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "getting TSIG algorithm");
    }
    return (NULL);
}

PyObject*
TSIG_getTimeSigned(const s_TSIG* const self) {
    return (Py_BuildValue("K", self->cppobj->getTimeSigned()));
}

PyObject*
TSIG_getFudge(const s_TSIG* const self) {
    return (Py_BuildValue("H", self->cppobj->getFudge()));
}

PyObject*
TSIG_getOriginalID(const s_TSIG* const self) {
    return (Py_BuildValue("H", self->cppobj->getOriginalID()));
}

PyObject*
TSIG_getError(const s_TSIG* const self) {
    return (Py_BuildValue("H", self->cppobj->getError()));
}

PyObject*
TSIG_getMAC(const s_TSIG* const self) {
    return (Py_BuildValue("y#", self->cppobj->getMAC(),
                          self->cppobj->getMACSize()));
}

PyObject*
TSIG_getOtherData(const s_TSIG* const self) {
    return (Py_BuildValue("y#", self->cppobj->getOtherData(),
                          self->cppobj->getOtherLen()));
}

PyObject*
TSIG_toText(const s_TSIG* const self) {
    try {
        // toText() could throw, so we need to catch any exceptions below.
        return (Py_BuildValue("s", self->cppobj->toText().c_str()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to convert TSIG object to text: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "converting TSIG object to text");
    }
    return (NULL);
}

PyObject*
TSIG_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self, const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
TSIG_toWire(const s_TSIG* const self, PyObject* args) {
    typedef any::TSIG TSIGRdata;
    return (toWireWrapper<s_TSIG, TSIGRdata, ToWireCallVoid<const TSIGRdata> >(
                self, args));
}

PyObject*
TSIG_richcmp(const s_TSIG* const self,
                   const s_TSIG* const other,
                   const int op)
{
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (other == NULL || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    // Only equals and not equals here, unorderable type
    const int cmp = self->cppobj->compare(*other->cppobj);
    switch (op) {
    case Py_EQ:
        c = (cmp == 0);
        break;
    case Py_NE:
        c = (cmp != 0);
        break;
    case Py_GT:
        c = (cmp > 0);
        break;
    case Py_GE:
        c = (cmp >= 0);
        break;
    case Py_LT:
        c = (cmp < 0);
        break;
    case Py_LE:
        c = (cmp <= 0);
        break;
    default:
        PyErr_SetString(PyExc_IndexError,
                        "Unhandled rich comparison operator for TSIG");
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
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_TSIG
// Most of the functions are not actually implemented and NULL here.
PyTypeObject tsig_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.TSIG",
    sizeof(s_TSIG),                 // tp_basicsize
    0,                                  // tp_itemsize
    reinterpret_cast<destructor>(TSIG_destroy),       // tp_dealloc
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
    TSIG_str,                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The TSIG class objects represents the TSIG RDATA as defined in RFC2845.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    reinterpret_cast<richcmpfunc>(TSIG_richcmp), // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    TSIG_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    // At the moment, we leave tp_base NULL as we won't use this class
    // in a polymorphic way for our immediate need.
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    reinterpret_cast<initproc>(TSIG_init),            // tp_init
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
createTSIGObject(const any::TSIG& source) {
    TSIGContainer container(PyObject_New(s_TSIG, &tsig_type));
    container.set(new any::TSIG(source));
    return (container.release());
}

bool
PyTSIG_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &tsig_type));
}

const any::TSIG&
PyTSIG_ToTSIG(const PyObject* tsig_obj) {
    if (tsig_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in TSIG PyObject conversion");
    }
    const s_TSIG* tsig = static_cast<const s_TSIG*>(tsig_obj);
    return (*tsig->cppobj);
}

} // namespace python
} // namespace dns
} // namespace isc
