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

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <dns/rdata.h>
#include <dns/messagerenderer.h>
#include <dns/exceptions.h>
#include <util/buffer.h>
#include <util/python/pycppwrapper_util.h>

#include "rdata_python.h"
#include "rrtype_python.h"
#include "rrclass_python.h"
#include "messagerenderer_python.h"
#include "name_python.h"

using namespace isc::dns;
using namespace isc::dns::python;
using namespace isc::util;
using namespace isc::util::python;
using namespace isc::dns::rdata;

namespace {

typedef PyObject* method(PyObject* self, PyObject* args);

// Wrap a method into an exception handling, converting C++ exceptions
// to python ones. The params and return value is just passed through.
PyObject*
exception_wrap(method* method, PyObject* self, PyObject* args) {
    try {
        return (method(self, args));
    } catch (const std::exception& ex) {
        // FIXME: These exceptions are not tested, I don't know how or if
        // at all they can be triggered. But they are caught just in the case.
        PyErr_SetString(PyExc_Exception, (std::string("Unknown exception: ") +
                        ex.what()).c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_Exception, "Unknown exception");
        return (NULL);
    }
}

class s_Rdata : public PyObject {
public:
    isc::dns::rdata::ConstRdataPtr cppobj;
};

typedef CPPPyObjectContainer<s_Rdata, Rdata> RdataContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int Rdata_init(PyObject* self, PyObject* args, PyObject*);
void Rdata_destroy(PyObject* self);

// These are the functions we export
PyObject* Rdata_toText(PyObject* self, PyObject*);
// This is a second version of toText, we need one where the argument
// is a PyObject*, for the str() function in python.
PyObject* Rdata_str(PyObject* self);
PyObject* Rdata_toWire(PyObject* self, PyObject* args);
PyObject* RData_richcmp(PyObject* self, PyObject* other, int op);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef Rdata_methods[] = {
    { "to_text", Rdata_toText, METH_NOARGS,
      "Returns the string representation" },
    { "to_wire", Rdata_toWire, METH_VARARGS,
      "Converts the Rdata object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { NULL, NULL, 0, NULL }
};

int
Rdata_init(PyObject* self_p, PyObject* args, PyObject*) {
    PyObject* rrtype;
    PyObject* rrclass;
    const char* s;
    const char* data;
    Py_ssize_t len;
    s_Rdata* self(static_cast<s_Rdata*>(self_p));

    try {
        // Create from string
        if (PyArg_ParseTuple(args, "O!O!s", &rrtype_type, &rrtype,
                             &rrclass_type, &rrclass,
                             &s)) {
            self->cppobj = createRdata(PyRRType_ToRRType(rrtype),
                                       PyRRClass_ToRRClass(rrclass), s);
            return (0);
        } else if (PyArg_ParseTuple(args, "O!O!y#", &rrtype_type, &rrtype,
                                    &rrclass_type, &rrclass, &data, &len)) {
            InputBuffer input_buffer(data, len);
            self->cppobj = createRdata(PyRRType_ToRRType(rrtype),
                                       PyRRClass_ToRRClass(rrclass),
                                       input_buffer, len);
            return (0);
        }
    } catch (const isc::dns::rdata::InvalidRdataText& irdt) {
        PyErr_SetString(po_InvalidRdataText, irdt.what());
        return (-1);
    } catch (const isc::dns::rdata::InvalidRdataLength& irdl) {
        PyErr_SetString(po_InvalidRdataLength, irdl.what());
        return (-1);
    } catch (const isc::dns::rdata::CharStringTooLong& cstl) {
        PyErr_SetString(po_CharStringTooLong, cstl.what());
        return (-1);
    } catch (const isc::dns::DNSMessageFORMERR& dmfe) {
        PyErr_SetString(po_DNSMessageFORMERR, dmfe.what());
        return (-1);
    } catch (const std::exception& ex) {
        // FIXME: These exceptions are not tested, I don't know how or if
        // at all they can be triggered. But they are caught just in the case.
        PyErr_SetString(PyExc_Exception, (std::string("Unknown exception: ") +
                        ex.what()).c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(PyExc_Exception, "Unknown exception");
        return (-1);
    }

    return (-1);
}

void
Rdata_destroy(PyObject* self) {
    // Clear the shared_ptr so that its reference count is zero
    // before we call tp_free() (there is no direct release())
    static_cast<s_Rdata*>(self)->cppobj.reset();
    Py_TYPE(self)->tp_free(self);
}

PyObject*
Rdata_toText_internal(PyObject* self, PyObject*) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", static_cast<const s_Rdata*>(self)->cppobj->
                          toText().c_str()));
}

PyObject*
Rdata_toText(PyObject* self, PyObject* args) {
    return (exception_wrap(&Rdata_toText_internal, self, args));
}

PyObject*
Rdata_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                                const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
Rdata_toWire_internal(PyObject* self_p, PyObject* args) {
    PyObject* bytes;
    PyObject* mr;
    const s_Rdata* self(static_cast<const s_Rdata*>(self_p));

    if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;

        OutputBuffer buffer(4);
        self->cppobj->toWire(buffer);
        PyObject* rd_bytes = PyBytes_FromStringAndSize(static_cast<const char*>(buffer.getData()), buffer.getLength());
        // Make sure exceptions from here are propagated.
        // The exception is already set, so we just return NULL
        if (rd_bytes == NULL) {
            return (NULL);
        }
        PyObject* result = PySequence_InPlaceConcat(bytes_o, rd_bytes);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(rd_bytes);
        return (result);
    } else if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, &mr)) {
        self->cppobj->toWire(PyMessageRenderer_ToMessageRenderer(mr));
        // If we return NULL it is seen as an error, so use this for
        // None returns
        Py_RETURN_NONE;
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a sequence object or a MessageRenderer");
    return (NULL);
}

PyObject*
Rdata_toWire(PyObject* self, PyObject* args) {
    return (exception_wrap(&Rdata_toWire_internal, self, args));
}

PyObject*
RData_richcmp(PyObject* self_p, PyObject* other_p, int op) {
    try {
        bool c;
        const s_Rdata* self(static_cast<const s_Rdata*>(self_p)),
              * other(static_cast<const s_Rdata*>(other_p));

        // Check for null and if the types match. If different type,
        // simply return False
        if (!other || (self->ob_type != other->ob_type)) {
            Py_RETURN_FALSE;
        }

        switch (op) {
            case Py_LT:
                c = self->cppobj->compare(*other->cppobj) < 0;
                break;
            case Py_LE:
                c = self->cppobj->compare(*other->cppobj) < 0 ||
                    self->cppobj->compare(*other->cppobj) == 0;
                break;
            case Py_EQ:
                c = self->cppobj->compare(*other->cppobj) == 0;
                break;
            case Py_NE:
                c = self->cppobj->compare(*other->cppobj) != 0;
                break;
            case Py_GT:
                c = self->cppobj->compare(*other->cppobj) > 0;
                break;
            case Py_GE:
                c = self->cppobj->compare(*other->cppobj) > 0 ||
                    self->cppobj->compare(*other->cppobj) == 0;
                break;
            default:
                PyErr_SetString(PyExc_IndexError,
                                "Unhandled rich comparison operator");
                return (NULL);
        }
        if (c) {
            Py_RETURN_TRUE;
        } else {
            Py_RETURN_FALSE;
        }
    } catch (const std::exception& ex) {
        // FIXME: These exceptions are not tested, I don't know how or if
        // at all they can be triggered. But they are caught just in the case.
        PyErr_SetString(PyExc_Exception, (std::string("Unknown exception: ") +
                        ex.what()).c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_Exception, "Unknown exception");
        return (NULL);
    }
}

} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {


//
// Declaration of the custom exceptions
// Initialization and addition of these go in the initModulePart
// function in pydnspp
//
PyObject* po_InvalidRdataLength;
PyObject* po_InvalidRdataText;
PyObject* po_CharStringTooLong;

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Rdata
// Most of the functions are not actually implemented and NULL here.
PyTypeObject rdata_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Rdata",
    sizeof(s_Rdata),                    // tp_basicsize
    0,                                  // tp_itemsize
    Rdata_destroy,                      // tp_dealloc
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
    RData_richcmp,                      // tp_richcompare
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
    Rdata_init,                         // tp_init
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
createRdataObject(ConstRdataPtr source) {
    s_Rdata* py_rdata =
        static_cast<s_Rdata*>(rdata_type.tp_alloc(&rdata_type, 0));
    if (py_rdata == NULL) {
        isc_throw(PyCPPWrapperException, "Unexpected NULL C++ object, "
                  "probably due to short memory");
    }
    py_rdata->cppobj = source;
    return (py_rdata);
}

bool
PyRdata_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &rdata_type));
}

const Rdata&
PyRdata_ToRdata(const PyObject* rdata_obj) {
    if (rdata_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in Rdata PyObject conversion");
    }
    const s_Rdata* rdata = static_cast<const s_Rdata*>(rdata_obj);
    return (*rdata->cppobj);
}

} // end python namespace
} // end dns namespace
} // end isc namespace
