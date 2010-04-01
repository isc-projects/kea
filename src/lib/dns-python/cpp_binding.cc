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

/* isc::dns::Name Python bindings */

#define PY_SSIZE_T_CLEAN

#include "config.h"

#include <Python.h>
#include <structmember.h>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>

#include <cassert>

using isc::OutOfRange;
using isc::dns::DNSMessageFORMERR;
using isc::dns::InvalidBufferPosition;
using isc::dns::InputBuffer;
using isc::dns::OutputBuffer;
using isc::dns::EmptyLabel;
using isc::dns::TooLongName;
using isc::dns::TooLongLabel;
using isc::dns::BadLabelType;
using isc::dns::BadEscape;
using isc::dns::IncompleteName;
using isc::dns::NameComparisonResult;
using isc::dns::Name;
using isc::dns::MessageRenderer;

static PyObject *cName_Exception;
static PyObject *cName_Relation;
static PyObject *cName_MAX_WIRE;
static PyObject *cName_MAX_LABELS;
static PyObject *cName_MAX_LABELLEN;
static PyObject *cName_MAX_COMPRESS_POINTER;
static PyObject *cName_COMPRESS_POINTER_MARK8;
static PyObject *cName_COMPRESS_POINTER_MARK16;

typedef struct {
    PyObject_HEAD
    NameComparisonResult *ncr;
} cNCR;

static void cNCR_dealloc(cNCR *self);
static int cNCR_init(cNCR *self, PyObject *args);
static PyObject *cNCR_getOrder(cNCR *self);
static PyObject *cNCR_getCommonLabels(cNCR *self);
static PyObject *cNCR_getRelation(cNCR *self);

static PyMethodDef cNCR_Methods[] = {
    { "getOrder", (PyCFunction)cNCR_getOrder, METH_NOARGS,
      "Return the ordering of the comparison result" },
    { "getCommonLabels", (PyCFunction)cNCR_getCommonLabels, METH_NOARGS,
      "Return the number of common labels of the comparison result" },
    { "getRelation", (PyCFunction)cNCR_getRelation, METH_NOARGS,
      "Return the NameRelation of the comparison result" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject cNCR_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "bind10_dns_noboost.cNameComparisonResult", /* tp_name */
    sizeof(cNCR),                       /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)cNCR_dealloc,           /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_reserved */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash  */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "C++ NameComparisonResult Object",  /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    cNCR_Methods,                       /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc)cNCR_init,                /* tp_init */
    NULL,                               /* tp_alloc */
    PyType_GenericNew,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */
    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
    // Note: not sure if the following are correct.  Added them just to
    // make the compiler happy.
    NULL,                               /* tp_del */
    0                                   /* tp_version_tag */
};

static void
cNCR_dealloc(cNCR *self) {
    if (self->ncr != NULL)
        delete self->ncr;
    self->ncr = NULL;
    Py_TYPE(self)->tp_free(self);
}

static int
cNCR_init(cNCR *self UNUSED_PARAM, PyObject *args UNUSED_PARAM) {
    PyErr_SetString(PyExc_NotImplementedError,
                    "cNameComparisonResult can't be built");
    return -1;
}

static PyObject *
cNCR_getOrder(cNCR *self) {
    return Py_BuildValue("i", self->ncr->getOrder());
}

static PyObject *
cNCR_getCommonLabels(cNCR *self) {
    return Py_BuildValue("I", self->ncr->getCommonLabels());
}

static PyObject *
cNCR_getRelation(cNCR *self) {
    return Py_BuildValue("i", (int) self->ncr->getRelation());
}

typedef struct {
    PyObject_HEAD
    Name *name;
    size_t position;
} cName;

static void cName_dealloc(cName *self);
static int cName_init(cName *self, PyObject *args);
static PyObject *cName_getLength(cName *self);
static PyObject *cName_getLabelCount(cName *self);
static PyObject *cName_toText(cName *self, PyObject *args);
static PyObject *cName_toWire(cName *self, PyObject *args);
static PyObject *cName_compare(cName *self, PyObject *args);
static PyObject *cName_equals(cName *self, PyObject *args);
static PyObject *cName_nequals(cName *self, PyObject *args);
static PyObject *cName_richcmp(cName *n1, cName *n2, int op);
static PyObject *cName_split(cName *self, PyObject *args);
static PyObject *cName_concatenate(cName *self, PyObject *args);
static PyObject *cName_downcase(cName *self);
static PyObject *cName_isWildcard(cName *self);
static PyObject *cName_getPosition(cName *self);
static PyObject *cName_clone(cName *self, PyObject *args);

static PyMethodDef cName_Methods[] = {
    { "getLength", (PyCFunction)cName_getLength, METH_NOARGS,
      "Return the length of the Name" },
    { "getLabelCount", (PyCFunction)cName_getLabelCount, METH_NOARGS,
      "Return the number of labels" },
    { "toText", (PyCFunction)cName_toText, METH_VARARGS,
      "Convert the Name to a string" },
    { "toWire", (PyCFunction)cName_toWire, METH_VARARGS,
      "Render the Name in the wire format" },
    { "compare", (PyCFunction)cName_compare, METH_VARARGS,
      "Compare two Names" },
    { "equals", (PyCFunction)cName_equals, METH_VARARGS,
      "Return true iff two Names are equal" },
    { "nequals", (PyCFunction)cName_nequals, METH_VARARGS,
      "Return true iff two Names are not equal" },
    { "split", (PyCFunction)cName_split, METH_VARARGS,
      "Extract a specified subpart of Name" },
    { "concatenate", (PyCFunction)cName_concatenate, METH_VARARGS,
      "Concatenate two Names" },
    { "downcase", (PyCFunction)cName_downcase, METH_NOARGS,
      "Downcase the calling object" },
    { "isWildcard", (PyCFunction)cName_isWildcard, METH_NOARGS,
      "Test if this is a wildcard Name" },
    { "getPosition", (PyCFunction)cName_getPosition, METH_NOARGS,
      "Return the end position in the wire buffer" },
    { "clone", (PyCFunction)cName_clone, METH_NOARGS,
      "Clone a Name" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject cName_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "bind10_dns_noboost.cName",         /* tp_name */
    sizeof(cName),                      /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)cName_dealloc,          /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_reserved */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash  */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,     /* tp_flags */
    "C++ Name Object",                  /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    (richcmpfunc)cName_richcmp,         /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    cName_Methods,                      /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc)cName_init,               /* tp_init */
    NULL,                               /* tp_alloc */
    PyType_GenericNew,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */
    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
    // Note: not sure if the following are correct.  Added them just to
    // make the compiler happy.
    NULL,                               /* tp_del */
    0                                   /* tp_version_tag */
};

static void
cName_dealloc(cName *self) {
    if (self->name != NULL)
        delete self->name;
    self->name = NULL;
    Py_TYPE(self)->tp_free(self);
}

static int
cName_init(cName *self, PyObject *args) {
    const char *s;
    PyObject *downcase = Py_False;

    /* fromText */
    if (PyArg_ParseTuple(args, "s|O!", &s, &PyBool_Type, &downcase)) {
        try {
            const std::string n(s);

            self->name = new Name(n, downcase == Py_True);
            self->position = 0;
        } catch (EmptyLabel) {
            PyErr_SetString(cName_Exception, "EmptyLabel");
            return -1;
        } catch (TooLongLabel) {
            PyErr_SetString(cName_Exception, "TooLongLabel");
            return -1;
        } catch (BadLabelType) {
            PyErr_SetString(cName_Exception, "BadLabelType");
            return -1;
        } catch (BadEscape) {
            PyErr_SetString(cName_Exception, "BadEscape");
            return -1;
        } catch (TooLongName) {
            PyErr_SetString(cName_Exception, "TooLongName");
            return -1;
        } catch (IncompleteName) {
            PyErr_SetString(cName_Exception, "IncompleteName");
            return -1;
#ifdef CATCHMEMERR
        } catch (std::bad_alloc) {
            PyErr_NoMemory();
            return -1;
#endif
        } catch (...) {
            PyErr_SetString(cName_Exception, "Unexpected?!");
            return -1;
        }
        return 0;
    }
    PyErr_Clear();

    const char *b;
    Py_ssize_t len;
    unsigned int position;

    /* fromWire */
    if (PyArg_ParseTuple(args, "y#I|O!", &b, &len, &position,
                         &PyBool_Type, &downcase)) {
        try {
            InputBuffer buffer(b, len);

            buffer.setPosition(position);
            self->name = new Name(buffer, downcase == Py_True);
            self->position = buffer.getPosition();
        } catch (InvalidBufferPosition) {
            PyErr_SetString(cName_Exception,
                            "InvalidBufferPosition");
            return -1;
        } catch (TooLongName) {
            PyErr_SetString(cName_Exception, "TooLongName");
            return -1;
        } catch (BadLabelType) {
            PyErr_SetString(cName_Exception, "BadLabelType");
            return -1;
        } catch (DNSMessageFORMERR) {
            PyErr_SetString(cName_Exception, "DNSMessageFORMERR");
            return -1;
        } catch (IncompleteName) {
            PyErr_SetString(cName_Exception, "IncompleteName");
            return -1;
#ifdef CATCHMEMERR
        } catch (std::bad_alloc) {
            PyErr_NoMemory();
            return -1;
#endif
        } catch (...) {
            PyErr_SetString(cName_Exception, "Unexpected?!");
            return -1;
        }
        return 0;
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "fromText and fromWire Name constructors don't match");
    return -1;
}

static PyObject *
cName_getLength(cName *self) {
    return Py_BuildValue("I", (unsigned int) self->name->getLength());
}

static PyObject *
cName_getLabelCount(cName *self) {
    return Py_BuildValue("I", self->name->getLabelCount());
}

static PyObject *
cName_toText(cName *self, PyObject *args) {
    PyObject *omit = Py_False;

    if (!PyArg_ParseTuple(args, "|O!", &PyBool_Type, &omit))
        return NULL;

    try {
        std::string s = self->name->toText(omit == Py_True);

        return Py_BuildValue("s", s.c_str());
    } catch (BadLabelType) {
        PyErr_SetString(cName_Exception, "BadLabelType");
        return NULL;
    }
}

static PyObject *
cName_toWire(cName *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    OutputBuffer buffer(255);

    self->name->toWire(buffer);
    return Py_BuildValue("y#", buffer.getData(),
                         (Py_ssize_t) buffer.getLength());
}

static PyObject *
cName_compare(cName *self, PyObject *args) {
    cName *other;

    if (!PyArg_ParseTuple(args, "O!", &cName_Type, (PyObject **) &other))
        return NULL;

    cNCR *ret = PyObject_New(cNCR, &cNCR_Type);
    if (ret != NULL) {
        ret->ncr = new NameComparisonResult(
            self->name->compare(*other->name));
        if (ret->ncr == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject *) ret;
}

static PyObject *
cName_equals(cName *self, PyObject *args) {
    cName *other;

    if (!PyArg_ParseTuple(args, "O!", &cName_Type, (PyObject **) &other))
        return NULL;

    if (self->name->equals(*other->name))
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static PyObject *
cName_nequals(cName *self, PyObject *args) {
    cName *other;

    if (!PyArg_ParseTuple(args, "O!", &cName_Type, (PyObject **) &other))
        return NULL;

    if (self->name->nequals(*other->name))
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static PyObject *
cName_richcmp(cName *n1, cName *n2, int op) {
    bool c;

    switch (op) {
    case Py_LT:
        c = n1->name->lthan(*n2->name);
        break;
    case Py_LE:
        c = n1->name->leq(*n2->name);
        break;
    case Py_EQ:
        c = n1->name->equals(*n2->name);
        break;
    case Py_NE:
        c = n1->name->nequals(*n2->name);
        break;
    case Py_GT:
        c = n1->name->gthan(*n2->name);
        break;
    case Py_GE:
        c = n1->name->geq(*n2->name);
        break;
    default:
        assert(0);              // XXX: should trigger an exception
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static PyObject *
cName_split(cName *self, PyObject *args) {
    unsigned int first, n;

    if (!PyArg_ParseTuple(args, "II", &first, &n))
        return NULL;

    cName *ret = PyObject_New(cName, &cName_Type);
    if (ret != NULL) {
        ret->name = NULL;
        try {
            ret->name = new Name(self->name->split(first, n));
        } catch(OutOfRange) {
            PyErr_SetString(cName_Exception, "OutOfRange");
        }
        if (ret->name == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject *) ret;
}

static PyObject *
cName_concatenate(cName *self, PyObject *args) {
    cName *suffix;

    if (!PyArg_ParseTuple(args, "O!", &cName_Type, (PyObject **) &suffix))
        return NULL;

    cName *ret = PyObject_New(cName, &cName_Type);
    if (ret != NULL) {
        ret->name = NULL;
        try {
            ret->name = new Name(
                self->name->concatenate(*suffix->name));
        } catch(TooLongName) {
            PyErr_SetString(cName_Exception, "TooLongName");
        }
        if (ret->name == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject *) ret;
}

static PyObject *
cName_downcase(cName *self) {
    self->name->downcase();
    Py_RETURN_NONE;
}

static PyObject *
cName_isWildcard(cName *self) {
    if (self->name->isWildcard())
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static PyObject *
cName_getPosition(cName *self) {
    return Py_BuildValue("I", (unsigned int) self->position);
}

static PyObject *
cName_clone(cName *self, PyObject *args UNUSED_PARAM) {
    cName *copy = PyObject_New(cName, &cName_Type);

    if (copy != NULL) {
        copy->name = new Name(*self->name);
        if (copy->name == NULL) {
            Py_DECREF(copy);
            return NULL;
        }
    }
    return (PyObject *) copy;
}

typedef struct {
    PyObject_HEAD
    MessageRenderer *mr;
    OutputBuffer *buffer;
} cMR;

static void cMR_dealloc(cMR *self);
static int cMR_init(cMR *self, PyObject *args);
static PyObject *cMR_dump(cMR *self);
static PyObject *cMR_writeData(cMR *self, PyObject *args);
static PyObject *cMR_writeName(cMR *self, PyObject *args);

static PyMethodDef cMR_Methods[] = {
    { "dump", (PyCFunction)cMR_dump, METH_NOARGS,
      "Return content of the MessageRenderer" },
    { "writeData", (PyCFunction)cMR_writeData, METH_VARARGS,
      "Write data into the MessageRenderer" },
    { "writeName", (PyCFunction)cMR_writeName, METH_VARARGS,
      "Write a Name into the MessageRenderer" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject cMR_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "bind10_dns_noboost.cMessageRenderer", /* tp_name */
    sizeof(cMR),                        /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)cMR_dealloc,            /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_reserved */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash  */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,     /* tp_flags */
    "C++ MessageRenderer Object",       /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    cMR_Methods,                        /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc)cMR_init,                 /* tp_init */
    NULL,                               /* tp_alloc */
    PyType_GenericNew,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */
    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
    // Note: not sure if the following are correct.  Added them just to
    // make the compiler happy.
    NULL,                               /* tp_del */
    0                                   /* tp_version_tag */
};

static void
cMR_dealloc(cMR *self) {
    if (self->mr != NULL)
        delete self->mr;
    self->mr = NULL;
    if (self->buffer != NULL)
        delete self->buffer;
    self->buffer = NULL;
    Py_TYPE(self)->tp_free(self);
}

static int
cMR_init(cMR *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;

    self->buffer = new OutputBuffer(1024);
    if (self->buffer == NULL) {
        (void) PyErr_NoMemory();
        return -1;
    }
    self->mr = new MessageRenderer(*self->buffer);
    if (self->mr == NULL) {
        delete self->buffer;
        self->buffer = NULL;
        return -1;
    }
    return 0;
}

static PyObject *
cMR_dump(cMR *self) {
    return Py_BuildValue("y#", self->buffer->getData(),
                         (Py_ssize_t) self->buffer->getLength());
}

static PyObject *
cMR_writeData(cMR *self, PyObject *args) {
    const char *b;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "y#", &b, &len))
        return NULL;

    self->buffer->writeData(b, len);
    Py_RETURN_NONE;
}

static PyObject *
cMR_writeName(cMR *self, PyObject *args) {
    cName *name;
    PyObject *compress = Py_True;

    if (!PyArg_ParseTuple(args, "O!|O!",
                          &cName_Type, (PyObject **) &name,
                          &PyBool_Type, &compress))
        return NULL;

    self->mr->writeName(*name->name, compress == Py_True);
    Py_RETURN_NONE;
}

static PyModuleDef cName_Module = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL}, // XXX: ad hoc init values
    "bind10_dns_noboost",                       /* m_name */
    "Python bindings for C++ Name Module",      /* m_doc */
    -1,                                 /* m_size */
    NULL,                               /* m_methods */
    NULL,                               /* m_reload */
    NULL,                               /* m_traverse */
    NULL,                               /* m_clear */
    NULL,                               /* m_free */
};

PyMODINIT_FUNC
PyInit_bind10_dns_noboost(void) {
    if (PyType_Ready(&cName_Type) < 0)
        return NULL;
    if (PyType_Ready(&cNCR_Type) < 0)
        return NULL;
    if (PyType_Ready(&cMR_Type) < 0)
        return NULL;

    PyObject *mod;

    mod = PyModule_Create(&cName_Module);
    if (mod == NULL)
        return NULL;

    Py_INCREF(&cName_Type);
    PyModule_AddObject(mod, "cName", (PyObject *) &cName_Type);
    Py_INCREF(&cNCR_Type);
    PyModule_AddObject(mod, "cNameComparisonResult",
                       (PyObject *) &cNCR_Type);
    Py_INCREF(&cMR_Type);
    PyModule_AddObject(mod, "cMessageRenderer", (PyObject *) &cMR_Type);
        
    cName_Exception = PyErr_NewException("bind10_dns_noboost.DNSException", NULL,
                                         NULL);
    Py_INCREF(cName_Exception);
    PyModule_AddObject(mod, "DNSException", cName_Exception);

    cName_Relation = Py_BuildValue("{i:s,i:s,i:s,i:s}",
                                   0, "SUPERDOMAIN",
                                   1, "SUBDOMAIN",
                                   2, "EQUAL",
                                   3, "COMMONANCESTOR");
    Py_INCREF(cName_Relation);
    PyModule_AddObject(mod, "NameRelation", cName_Relation);

    cName_MAX_WIRE = Py_BuildValue("I", 255U);
    Py_INCREF(cName_MAX_WIRE);
    PyModule_AddObject(mod, "MAX_WIRE", cName_MAX_WIRE);
    cName_MAX_LABELS = Py_BuildValue("I", 128U);
    Py_INCREF(cName_MAX_LABELS);
    PyModule_AddObject(mod, "MAX_LABELS", cName_MAX_LABELS);
    cName_MAX_LABELLEN = Py_BuildValue("I", 63U);
    Py_INCREF(cName_MAX_LABELLEN);
    PyModule_AddObject(mod, "MAX_LABELLEN", cName_MAX_LABELLEN);
    cName_MAX_COMPRESS_POINTER = Py_BuildValue("I", 0x3fffU);
    Py_INCREF(cName_MAX_COMPRESS_POINTER);
    PyModule_AddObject(mod, "MAX_COMPRESS_POINTER",
                       cName_MAX_COMPRESS_POINTER);
    cName_COMPRESS_POINTER_MARK8 = Py_BuildValue("I", 0xc0U);
    Py_INCREF(cName_COMPRESS_POINTER_MARK8);
    PyModule_AddObject(mod, "COMPRESS_POINTER_MARK8",
                       cName_COMPRESS_POINTER_MARK8);
    cName_COMPRESS_POINTER_MARK16 = Py_BuildValue("I", 0xc000U);
    Py_INCREF(cName_COMPRESS_POINTER_MARK16);
    PyModule_AddObject(mod, "COMPRESS_POINTER_MARK16",
                       cName_COMPRESS_POINTER_MARK16);

    return mod;
}
