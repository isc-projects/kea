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

#include <Python.h>

#include <util/buffer.h>

#include <dns/messagerenderer.h>
#include <util/python/pycppwrapper_util.h>

#include "pydnspp_common.h"
#include "messagerenderer_python.h"

using namespace isc::dns;
using namespace isc::dns::python;
using namespace isc::util;
using namespace isc::util::python;

namespace {
// The s_* Class simply covers one instantiation of the object.
//
// since we don't use *Buffer in the python version (but work with
// the already existing bytearray type where we use these custom buffers
// in C++, we need to keep track of one here.
class s_MessageRenderer : public PyObject {
public:
    s_MessageRenderer();
    isc::util::OutputBuffer* outputbuffer;
    MessageRenderer* cppobj;
};

int MessageRenderer_init(s_MessageRenderer* self);
void MessageRenderer_destroy(s_MessageRenderer* self);

PyObject* MessageRenderer_getData(s_MessageRenderer* self);
PyObject* MessageRenderer_getLength(s_MessageRenderer* self);
PyObject* MessageRenderer_isTruncated(s_MessageRenderer* self);
PyObject* MessageRenderer_getLengthLimit(s_MessageRenderer* self);
PyObject* MessageRenderer_getCompressMode(s_MessageRenderer* self);
PyObject* MessageRenderer_setTruncated(s_MessageRenderer* self);
PyObject* MessageRenderer_setLengthLimit(s_MessageRenderer* self, PyObject* args);
PyObject* MessageRenderer_setCompressMode(s_MessageRenderer* self, PyObject* args);
PyObject* MessageRenderer_clear(s_MessageRenderer* self);

PyMethodDef MessageRenderer_methods[] = {
    { "get_data", reinterpret_cast<PyCFunction>(MessageRenderer_getData), METH_NOARGS,
      "Returns the data as a bytes() object" },
    { "get_length", reinterpret_cast<PyCFunction>(MessageRenderer_getLength), METH_NOARGS,
      "Returns the length of the data" },
    { "is_truncated", reinterpret_cast<PyCFunction>(MessageRenderer_isTruncated), METH_NOARGS,
      "Returns True if the data is truncated" },
    { "get_length_limit", reinterpret_cast<PyCFunction>(MessageRenderer_getLengthLimit), METH_NOARGS,
      "Returns the length limit of the data" },
    { "get_compress_mode", reinterpret_cast<PyCFunction>(MessageRenderer_getCompressMode), METH_NOARGS,
      "Returns the current compression mode" },
    { "set_truncated", reinterpret_cast<PyCFunction>(MessageRenderer_setTruncated), METH_NOARGS,
      "Sets truncated to true" },
    { "set_length_limit", reinterpret_cast<PyCFunction>(MessageRenderer_setLengthLimit), METH_VARARGS,
      "Sets the length limit of the data to the given number" },
    { "set_compress_mode", reinterpret_cast<PyCFunction>(MessageRenderer_setCompressMode), METH_VARARGS,
      "Sets the compression mode of the MessageRenderer" },
    { "clear", reinterpret_cast<PyCFunction>(MessageRenderer_clear),
      METH_NOARGS,
      "Clear the internal buffer and other internal resources." },
    { NULL, NULL, 0, NULL }
};

int
MessageRenderer_init(s_MessageRenderer* self) {
    self->outputbuffer = new OutputBuffer(4096);
    self->cppobj = new MessageRenderer(*self->outputbuffer);
    return (0);
}

void
MessageRenderer_destroy(s_MessageRenderer* self) {
    delete self->cppobj;
    delete self->outputbuffer;
    self->cppobj = NULL;
    self->outputbuffer = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
MessageRenderer_getData(s_MessageRenderer* self) {
    return (Py_BuildValue("y#",
                          self->cppobj->getData(),
                          self->cppobj->getLength()));
}

PyObject*
MessageRenderer_getLength(s_MessageRenderer* self) {
    return (Py_BuildValue("I", self->cppobj->getLength()));
}

PyObject*
MessageRenderer_isTruncated(s_MessageRenderer* self) {
    if (self->cppobj->isTruncated()) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject*
MessageRenderer_getLengthLimit(s_MessageRenderer* self) {
    return (Py_BuildValue("I", self->cppobj->getLengthLimit()));
}

PyObject*
MessageRenderer_getCompressMode(s_MessageRenderer* self) {
    return (Py_BuildValue("I", self->cppobj->getCompressMode()));
}

PyObject*
MessageRenderer_setTruncated(s_MessageRenderer* self) {
    self->cppobj->setTruncated();
    Py_RETURN_NONE;
}

PyObject*
MessageRenderer_setLengthLimit(s_MessageRenderer* self,
                               PyObject* args)
{
    long lengthlimit;
    if (!PyArg_ParseTuple(args, "l", &lengthlimit)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "No valid type in set_length_limit argument");
        return (NULL);
    }
    if (lengthlimit < 0) {
        PyErr_SetString(PyExc_ValueError,
                        "MessageRenderer length limit out of range");
        return (NULL);
    }
    self->cppobj->setLengthLimit(lengthlimit);
    Py_RETURN_NONE;
}

PyObject*
MessageRenderer_setCompressMode(s_MessageRenderer* self,
                               PyObject* args)
{
    int mode;
    if (!PyArg_ParseTuple(args, "i", &mode)) {
        return (NULL);
    }

    if (mode == MessageRenderer::CASE_INSENSITIVE) {
        self->cppobj->setCompressMode(MessageRenderer::CASE_INSENSITIVE);
        // If we return NULL it is seen as an error, so use this for
        // None returns, it also applies to CASE_SENSITIVE.
        Py_RETURN_NONE;
    } else if (mode == MessageRenderer::CASE_SENSITIVE) {
        self->cppobj->setCompressMode(MessageRenderer::CASE_SENSITIVE);
        Py_RETURN_NONE;
    } else {
        PyErr_SetString(PyExc_TypeError,
                        "MessageRenderer compress mode must be MessageRenderer.CASE_INSENSITIVE"
                        "or MessageRenderer.CASE_SENSITIVE");
        return (NULL);
    }
}

PyObject*
MessageRenderer_clear(s_MessageRenderer* self) {
    self->cppobj->clear();
    Py_RETURN_NONE;
}
} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
PyTypeObject messagerenderer_type = {
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

// If we need a createMessageRendererObject(), should we copy? can we?
// copy the existing buffer into a new one, then create a new renderer with
// that buffer?

bool
PyMessageRenderer_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &messagerenderer_type));
}

MessageRenderer&
PyMessageRenderer_ToMessageRenderer(PyObject* messagerenderer_obj) {
    if (messagerenderer_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in MessageRenderer PyObject conversion");
    }
    s_MessageRenderer* messagerenderer = static_cast<s_MessageRenderer*>(messagerenderer_obj);
    return (*messagerenderer->cppobj);
}


} // namespace python
} // namespace dns
} // namespace isc
