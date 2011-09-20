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
#include <dns/question.h>
#include <dns/messagerenderer.h>
#include <dns/exceptions.h>
#include <util/buffer.h>
#include <util/python/pycppwrapper_util.h>

#include "pydnspp_common.h"
#include "question_python.h"
#include "name_python.h"
#include "rrclass_python.h"
#include "rrtype_python.h"
#include "messagerenderer_python.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::python;
using namespace isc::util;
using namespace isc::util::python;
using namespace isc;

namespace {
class s_Question : public PyObject {
public:
    isc::dns::QuestionPtr cppobj;
};

static int Question_init(s_Question* self, PyObject* args);
static void Question_destroy(s_Question* self);

// These are the functions we export
static PyObject* Question_getName(s_Question* self);
static PyObject* Question_getType(s_Question* self);
static PyObject* Question_getClass(s_Question* self);
static PyObject* Question_toText(s_Question* self);
// This is a second version of toText, we need one where the argument
// is a PyObject*, for the str() function in python.
static PyObject* Question_str(PyObject* self);
static PyObject* Question_toWire(s_Question* self, PyObject* args);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
static PyMethodDef Question_methods[] = {
    { "get_name", reinterpret_cast<PyCFunction>(Question_getName), METH_NOARGS,
      "Returns the Name" },
    { "get_type", reinterpret_cast<PyCFunction>(Question_getType), METH_NOARGS,
      "Returns the RRType" },
    { "get_class", reinterpret_cast<PyCFunction>(Question_getClass), METH_NOARGS,
      "Returns the RRClass" },
    { "to_text", reinterpret_cast<PyCFunction>(Question_toText), METH_NOARGS,
      "Returns the string representation" },
    { "to_wire", reinterpret_cast<PyCFunction>(Question_toWire), METH_VARARGS,
      "Converts the Question object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { NULL, NULL, 0, NULL }
};

static int
Question_init(s_Question* self, PyObject* args) {
    // Try out the various combinations of arguments to call the
    // correct cpp constructor.
    // Note that PyArg_ParseType can set PyError, and we need to clear
    // that if we try several like here. Otherwise the *next* python
    // call will suddenly appear to throw an exception.
    // (the way to do exceptions is to set PyErr and return -1)
    PyObject* name;
    PyObject* rrclass;
    PyObject* rrtype;

    const char* b;
    Py_ssize_t len;
    unsigned int position = 0;

    try {
        if (PyArg_ParseTuple(args, "O!O!O!", &name_type, &name,
                                             &rrclass_type, &rrclass,
                                             &rrtype_type, &rrtype
           )) {
            self->cppobj = QuestionPtr(new Question(PyName_ToName(name),
                                                    PyRRClass_ToRRClass(rrclass),
                                                    PyRRType_ToRRType(rrtype)));
            return (0);
        } else if (PyArg_ParseTuple(args, "y#|I", &b, &len, &position)) {
            PyErr_Clear();
            InputBuffer inbuf(b, len);
            inbuf.setPosition(position);
            self->cppobj = QuestionPtr(new Question(inbuf));
            return (0);
        }
    } catch (const DNSMessageFORMERR& dmfe) {
        PyErr_Clear();
        PyErr_SetString(po_DNSMessageFORMERR, dmfe.what());
        return (-1);
    } catch (const IncompleteRRClass& irc) {
        PyErr_Clear();
        PyErr_SetString(po_IncompleteRRClass, irc.what());
        return (-1);
    } catch (const IncompleteRRType& irt) {
        PyErr_Clear();
        PyErr_SetString(po_IncompleteRRType, irt.what());
        return (-1);
    }

    self->cppobj = QuestionPtr();

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "no valid type in constructor argument");
    return (-1);
}

static void
Question_destroy(s_Question* self) {
    self->cppobj.reset();
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Question_getName(s_Question* self) {
    try {
        return (createNameObject(self->cppobj->getName()));
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure getting question Name: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure getting question Name");
    }
    return (NULL);
}

static PyObject*
Question_getType(s_Question* self) {
    try {
        return (createRRTypeObject(self->cppobj->getType()));
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure getting question RRType: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure getting question RRType");
    }
    return (NULL);
}

static PyObject*
Question_getClass(s_Question* self) {
    try {
        return (createRRClassObject(self->cppobj->getClass()));
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure getting question RRClass: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure getting question RRClass");
    }
    return (NULL);
}

static PyObject*
Question_toText(s_Question* self) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", self->cppobj->toText().c_str()));
}

static PyObject*
Question_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

static PyObject*
Question_toWire(s_Question* self, PyObject* args) {
    PyObject* bytes;
    PyObject* mr;

    if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;

        // Max length is Name::MAX_WIRE + rrclass (2) + rrtype (2)
        OutputBuffer buffer(Name::MAX_WIRE + 4);
        self->cppobj->toWire(buffer);
        PyObject* n = PyBytes_FromStringAndSize(static_cast<const char*>(buffer.getData()),
                                                buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, n);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(n);
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

} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Question
// Most of the functions are not actually implemented and NULL here.
PyTypeObject question_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Question",
    sizeof(s_Question),                 // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Question_destroy,       // tp_dealloc
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
    Question_str,                       // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Question class encapsulates the common search key of DNS"
    "lookup, consisting of owner name, RR type and RR class.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Question_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Question_init,            // tp_init
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
createQuestionObject(const Question& source) {
    s_Question* question =
        static_cast<s_Question*>(question_type.tp_alloc(&question_type, 0));
    question->cppobj = QuestionPtr(new Question(source));
    return (question);
}

bool
PyQuestion_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &question_type));
}

const Question&
PyQuestion_ToQuestion(const PyObject* question_obj) {
    if (question_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in Question PyObject conversion");
    }
    const s_Question* question = static_cast<const s_Question*>(question_obj);
    return (*question->cppobj);
}

} // end python namespace
} // end dns namespace
} // end isc namespace
