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

// $Id: question_python.cc 1711 2010-04-14 15:14:53Z jelte $

#include <dns/question.h>
using namespace isc::dns;

//
// Question
//

// The s_* Class simply coverst one instantiation of the object
class s_Question : public PyObject {
public:
    QuestionPtr question;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
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

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Question
// Most of the functions are not actually implemented and NULL here.
static PyTypeObject question_type = {
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

static int
Question_init(s_Question* self, PyObject* args) {
    // Try out the various combinations of arguments to call the
    // correct cpp constructor.
    // Note that PyArg_ParseType can set PyError, and we need to clear
    // that if we try several like here. Otherwise the *next* python
    // call will suddenly appear to throw an exception.
    // (the way to do exceptions is to set PyErr and return -1)
    s_Name* name;
    s_RRClass* rrclass;
    s_RRType* rrtype;

    const char* b;
    Py_ssize_t len;
    unsigned int position = 0;

    try {
        if (PyArg_ParseTuple(args, "O!O!O!", &name_type, &name,
                                               &rrclass_type, &rrclass,
                                               &rrtype_type, &rrtype
           )) {
            self->question = QuestionPtr(new Question(*name->name, *rrclass->rrclass,
                                          *rrtype->rrtype));
            return (0);
        } else if (PyArg_ParseTuple(args, "y#|I", &b, &len, &position)) {
            PyErr_Clear();
            InputBuffer inbuf(b, len);
            inbuf.setPosition(position);
            self->question = QuestionPtr(new Question(inbuf));
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

    self->question = QuestionPtr();
    
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "no valid type in constructor argument");
    return (-1);
}

static void
Question_destroy(s_Question* self) {
    self->question.reset();
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Question_getName(s_Question* self) {
    s_Name* name;

    // is this the best way to do this?
    name = static_cast<s_Name*>(name_type.tp_alloc(&name_type, 0));
    if (name != NULL) {
        name->name = new Name(self->question->getName());
    }

    return (name);
}

static PyObject*
Question_getType(s_Question* self) {
    s_RRType* rrtype;

    rrtype = static_cast<s_RRType*>(rrtype_type.tp_alloc(&rrtype_type, 0));
    if (rrtype != NULL) {
        rrtype->rrtype = new RRType(self->question->getType());
    }

    return (rrtype);
}

static PyObject*
Question_getClass(s_Question* self) {
    s_RRClass* rrclass;

    rrclass = static_cast<s_RRClass*>(rrclass_type.tp_alloc(&rrclass_type, 0));
    if (rrclass != NULL) {
        rrclass->rrclass = new RRClass(self->question->getClass());
    }

    return (rrclass);
}


static PyObject*
Question_toText(s_Question* self) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", self->question->toText().c_str()));
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
    s_MessageRenderer* mr;
    
    if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;

        // Max length is Name::MAX_WIRE + rrclass (2) + rrtype (2)
        OutputBuffer buffer(Name::MAX_WIRE + 4);
        self->question->toWire(buffer);
        PyObject* n = PyBytes_FromStringAndSize(static_cast<const char*>(buffer.getData()),
                                                buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, n);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(n);
        return (result);
    } else if (PyArg_ParseTuple(args, "O!", &messagerenderer_type,
                                reinterpret_cast<PyObject**>(&mr))) {
        self->question->toWire(*mr->messagerenderer);
        // If we return NULL it is seen as an error, so use this for
        // None returns
        Py_RETURN_NONE;
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a sequence object or a MessageRenderer");
    return (NULL);
}

// end of Question


// Module Initialization, all statics are initialized here
bool
initModulePart_Question(PyObject* mod) {
    // Add the exceptions to the module

    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&question_type) < 0) {
        return (false);
    }
    Py_INCREF(&question_type);
    PyModule_AddObject(mod, "Question",
                       reinterpret_cast<PyObject*>(&question_type));
    
    return (true);
}
