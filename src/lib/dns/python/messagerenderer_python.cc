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

#include <dns/messagerenderer.h>

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description
using namespace isc::dns;

// MessageRenderer

// since we don't use *Buffer in the python version (but work with
// the already existing bytearray type where we use these custom buffers
// in c++, we need to keep track of one here.
class s_MessageRenderer : public PyObject {
public:
    OutputBuffer* outputbuffer;
    MessageRenderer* messagerenderer;
};

static int MessageRenderer_init(s_MessageRenderer* self);
static void MessageRenderer_destroy(s_MessageRenderer* self);

static PyObject* MessageRenderer_getData(s_MessageRenderer* self);
static PyObject* MessageRenderer_getLength(s_MessageRenderer* self);
static PyObject* MessageRenderer_isTruncated(s_MessageRenderer* self);
static PyObject* MessageRenderer_getLengthLimit(s_MessageRenderer* self);
// TODO: set/get compressmode
static PyObject* MessageRenderer_setTruncated(s_MessageRenderer* self);
static PyObject* MessageRenderer_setLengthLimit(s_MessageRenderer* self, PyObject* args);


static PyMethodDef MessageRenderer_methods[] = {
    { "get_data", reinterpret_cast<PyCFunction>(MessageRenderer_getData), METH_NOARGS,
      "Returns the data as a bytes() object" },
    { "get_length", reinterpret_cast<PyCFunction>(MessageRenderer_getLength), METH_NOARGS,
      "Returns the length of the data" },
    { "is_truncated", reinterpret_cast<PyCFunction>(MessageRenderer_isTruncated), METH_NOARGS,
      "Returns True if the data is truncated" },
    { "get_length_limit", reinterpret_cast<PyCFunction>(MessageRenderer_getLengthLimit), METH_NOARGS,
      "Returns the length limit of the data" },
    { "set_truncated", reinterpret_cast<PyCFunction>(MessageRenderer_setTruncated), METH_NOARGS,
      "Sets truncated to true" },
    { "set_length_limit", reinterpret_cast<PyCFunction>(MessageRenderer_setLengthLimit), METH_VARARGS,
      "Sets the length limit of the data to the given number" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject messagerenderer_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.MessageRenderer",
    sizeof(s_MessageRenderer),          // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)MessageRenderer_destroy,// tp_dealloc
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
    "The MessageRenderer class encapsulates implementation details "
    "of rendering a DNS message into a buffer in wire format. "
    "In effect, it's simply responsible for name compression at least in the "
    "current implementation. A MessageRenderer class object manages the "
    "positions of names rendered in a buffer and uses that information to render "
    "subsequent names with compression.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    MessageRenderer_methods,            // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)MessageRenderer_init,     // tp_init
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
MessageRenderer_init(s_MessageRenderer* self) {
    self->outputbuffer = new OutputBuffer(4096);
    self->messagerenderer = new MessageRenderer(*self->outputbuffer);
    return (0);
}

static void
MessageRenderer_destroy(s_MessageRenderer* self) {
    delete self->messagerenderer;
    delete self->outputbuffer;
    self->messagerenderer = NULL;
    self->outputbuffer = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
MessageRenderer_getData(s_MessageRenderer* self) {
    return (Py_BuildValue("y#",
                         self->messagerenderer->getData(),
                          self->messagerenderer->getLength()));
}

static PyObject*
MessageRenderer_getLength(s_MessageRenderer* self) {
    return (Py_BuildValue("I", self->messagerenderer->getLength()));
}

static PyObject*
MessageRenderer_isTruncated(s_MessageRenderer* self) {
    if (self->messagerenderer->isTruncated()) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject*
MessageRenderer_getLengthLimit(s_MessageRenderer* self) {
    return (Py_BuildValue("I", self->messagerenderer->getLengthLimit()));
}

static PyObject*
MessageRenderer_setTruncated(s_MessageRenderer* self) {
    self->messagerenderer->setTruncated();
    Py_RETURN_NONE;
}

static PyObject*
MessageRenderer_setLengthLimit(s_MessageRenderer* self,
                               PyObject* args)
{
    unsigned int lengthlimit;
    if (!PyArg_ParseTuple(args, "I", &lengthlimit)) {
        return (NULL);
    }
    self->messagerenderer->setLengthLimit(lengthlimit);
    Py_RETURN_NONE;
}

// end of MessageRenderer


// Module Initialization, all statics are initialized here
bool
initModulePart_MessageRenderer(PyObject* mod) {
    // Add the exceptions to the module

    // Add the enums to the module

    // Add the constants to the module

    // Add the classes to the module
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module

    // NameComparisonResult
    if (PyType_Ready(&messagerenderer_type) < 0) {
        return (false);
    }
    Py_INCREF(&messagerenderer_type);
    PyModule_AddObject(mod, "MessageRenderer",
                       reinterpret_cast<PyObject*>(&messagerenderer_type));
    
    return (true);
}


