// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id: message_python.cc 1711 2010-04-14 15:14:53Z jelte $

#include <dns/message.h>
using namespace isc::dns;

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the initModulePart
// function at the end of this file
//
static PyObject* po_MessageTooShort;
static PyObject* po_InvalidMessageSection;
static PyObject* po_InvalidMessageOperation;
static PyObject* po_InvalidMessageUDPSize;
static PyObject* po_DNSMessageBADVERS;

//
// Constants
//
static PyObject* po_MessagePARSE;
static PyObject* po_MessageRENDER;
static PyObject* po_MessageDefaultMaxUDPSize;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description


//
// MessageFlag
//
typedef struct {
    PyObject_HEAD
    const MessageFlag* messageflag;
} s_MessageFlag;

static int MessageFlag_init(s_MessageFlag* self, PyObject* args);
static void MessageFlag_destroy(s_MessageFlag* self);

static PyObject* MessageFlag_getBit(s_MessageFlag* self);
static PyObject* MessageFlag_QR(s_MessageFlag* self);
static PyObject* MessageFlag_AA(s_MessageFlag* self);
static PyObject* MessageFlag_TC(s_MessageFlag* self);
static PyObject* MessageFlag_RD(s_MessageFlag* self);
static PyObject* MessageFlag_RA(s_MessageFlag* self);
static PyObject* MessageFlag_AD(s_MessageFlag* self);
static PyObject* MessageFlag_CD(s_MessageFlag* self);

static PyMethodDef MessageFlag_methods[] = {
    { "get_bit", (PyCFunction)MessageFlag_getBit, METH_NOARGS, "Return the flag bit" },
    { "QR", (PyCFunction)MessageFlag_QR, METH_NOARGS | METH_STATIC, "Create a QR MessageFlag" },
    { "AA", (PyCFunction)MessageFlag_AA, METH_NOARGS | METH_STATIC, "Create a AA MessageFlag" },
    { "TC", (PyCFunction)MessageFlag_TC, METH_NOARGS | METH_STATIC, "Create a TC MessageFlag" },
    { "RD", (PyCFunction)MessageFlag_RD, METH_NOARGS | METH_STATIC, "Create a RD MessageFlag" },
    { "RA", (PyCFunction)MessageFlag_RA, METH_NOARGS | METH_STATIC, "Create a RA MessageFlag" },
    { "AD", (PyCFunction)MessageFlag_AD, METH_NOARGS | METH_STATIC, "Create a AD MessageFlag" },
    { "CD", (PyCFunction)MessageFlag_CD, METH_NOARGS | METH_STATIC, "Create a CD MessageFlag" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject messageflag_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.MessageFlag",
    sizeof(s_MessageFlag),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)MessageFlag_destroy,        /* tp_dealloc */
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
    "C++ MessageFlag Object",               /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,       /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    MessageFlag_methods,                    /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    // TODO: Can we make this NULL? (no direct constructor)
    (initproc)MessageFlag_init,                /* tp_init */
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


static int
MessageFlag_init(s_MessageFlag* self UNUSED_PARAM, PyObject* args UNUSED_PARAM)
{
    PyErr_SetString(PyExc_NotImplementedError,
                    "MessageFlag can't be built directly");
    return -1;
}

static void
MessageFlag_destroy(s_MessageFlag* self)
{
    // We only use the consts from MessageFlag, so don't
    // delete self->messageflag here
    self->messageflag = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
MessageFlag_getBit(s_MessageFlag* self)
{
    return Py_BuildValue("I", self->messageflag->getBit());
}

static PyObject*
MessageFlag_QR(s_MessageFlag* self UNUSED_PARAM)
{
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &MessageFlag::QR();
        if (ret->messageflag == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
MessageFlag_AA(s_MessageFlag* self UNUSED_PARAM)
{
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &MessageFlag::AA();
        if (ret->messageflag == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
MessageFlag_TC(s_MessageFlag* self UNUSED_PARAM)
{
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &MessageFlag::TC();
        if (ret->messageflag == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
MessageFlag_RD(s_MessageFlag* self UNUSED_PARAM)
{
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &MessageFlag::RD();
        if (ret->messageflag == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
MessageFlag_RA(s_MessageFlag* self UNUSED_PARAM)
{
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &MessageFlag::RA();
        if (ret->messageflag == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
MessageFlag_AD(s_MessageFlag* self UNUSED_PARAM)
{
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &MessageFlag::AD();
        if (ret->messageflag == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
MessageFlag_CD(s_MessageFlag* self UNUSED_PARAM)
{
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &MessageFlag::CD();
        if (ret->messageflag == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

//
// End of MessageFlag wrapper
//


//
// Opcode
//
typedef struct {
    PyObject_HEAD
    const Opcode* opcode;
} s_Opcode;

static int Opcode_init(s_Opcode* self, PyObject* args);
static void Opcode_destroy(s_Opcode* self);

static PyObject* Opcode_getCode(s_Opcode* self);
static PyObject* Opcode_toText(s_Opcode* self);
static PyObject* Opcode_str(PyObject* self);
static PyObject* Opcode_QUERY(s_Opcode* self);
static PyObject* Opcode_IQUERY(s_Opcode* self);
static PyObject* Opcode_STATUS(s_Opcode* self);
static PyObject* Opcode_RESERVED3(s_Opcode* self);
static PyObject* Opcode_NOTIFY(s_Opcode* self);
static PyObject* Opcode_UPDATE(s_Opcode* self);
static PyObject* Opcode_RESERVED6(s_Opcode* self);
static PyObject* Opcode_RESERVED7(s_Opcode* self);
static PyObject* Opcode_RESERVED8(s_Opcode* self);
static PyObject* Opcode_RESERVED9(s_Opcode* self);
static PyObject* Opcode_RESERVED10(s_Opcode* self);
static PyObject* Opcode_RESERVED11(s_Opcode* self);
static PyObject* Opcode_RESERVED12(s_Opcode* self);
static PyObject* Opcode_RESERVED13(s_Opcode* self);
static PyObject* Opcode_RESERVED14(s_Opcode* self);
static PyObject* Opcode_RESERVED15(s_Opcode* self);
static PyObject* Opcode_richcmp(s_Opcode* self, s_Opcode* other, int op);

static PyMethodDef Opcode_methods[] = {
    { "get_code", (PyCFunction)Opcode_getCode, METH_NOARGS, "Return the code value" },
    { "to_text", (PyCFunction)Opcode_toText, METH_NOARGS, "Return the text representation" },
    { "QUERY", (PyCFunction)Opcode_QUERY, METH_NOARGS | METH_STATIC, "Create a QUERY Opcode" },
    { "IQUERY", (PyCFunction)Opcode_IQUERY, METH_NOARGS | METH_STATIC, "Create a IQUERY Opcode" },
    { "STATUS", (PyCFunction)Opcode_STATUS, METH_NOARGS | METH_STATIC, "Create a STATUS Opcode" },
    { "RESERVED3", (PyCFunction)Opcode_RESERVED3, METH_NOARGS | METH_STATIC, "Create a RESERVED3 Opcode" },
    { "NOTIFY", (PyCFunction)Opcode_NOTIFY, METH_NOARGS | METH_STATIC, "Create a NOTIFY Opcode" },
    { "UPDATE", (PyCFunction)Opcode_UPDATE, METH_NOARGS | METH_STATIC, "Create a UPDATE Opcode" },
    { "RESERVED6", (PyCFunction)Opcode_RESERVED6, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED7", (PyCFunction)Opcode_RESERVED7, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED8", (PyCFunction)Opcode_RESERVED8, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED9", (PyCFunction)Opcode_RESERVED9, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED10", (PyCFunction)Opcode_RESERVED10, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED11", (PyCFunction)Opcode_RESERVED11, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED12", (PyCFunction)Opcode_RESERVED12, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED13", (PyCFunction)Opcode_RESERVED13, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED14", (PyCFunction)Opcode_RESERVED14, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { "RESERVED15", (PyCFunction)Opcode_RESERVED15, METH_NOARGS | METH_STATIC, "Create a RESERVED Opcode" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject opcode_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.Opcode",
    sizeof(s_Opcode),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)Opcode_destroy,        /* tp_dealloc */
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
    Opcode_str,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "C++ Opcode Object",               /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    (richcmpfunc)Opcode_richcmp,       /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    Opcode_methods,                    /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    // TODO: Can we make this NULL? (no direct constructor)
    (initproc)Opcode_init,                /* tp_init */
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


static int
Opcode_init(s_Opcode* self UNUSED_PARAM, PyObject* args UNUSED_PARAM)
{
    PyErr_SetString(PyExc_NotImplementedError,
                    "Opcode can't be built directly");
    return -1;
}

static void
Opcode_destroy(s_Opcode* self)
{
    // We only use the consts from Opcode, so don't
    // delete self->opcode here
    self->opcode = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Opcode_getCode(s_Opcode* self)
{
    return Py_BuildValue("I", self->opcode->getCode());
}

static PyObject*
Opcode_toText(s_Opcode* self)
{
    return Py_BuildValue("s", self->opcode->toText().c_str());
}

static PyObject*
Opcode_str(PyObject* self)
{
    // Simply call the to_text method we already defined
    return PyObject_CallMethod(self, (char*)"to_text", (char*)"");
}

static PyObject*
Opcode_QUERY(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::QUERY();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_IQUERY(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::IQUERY();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_STATUS(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::STATUS();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED3(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED3();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_NOTIFY(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::NOTIFY();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_UPDATE(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::UPDATE();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED6(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED6();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED7(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED7();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED8(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED8();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED9(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED9();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED10(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED10();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED11(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED11();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED12(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED12();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED13(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED13();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED14(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED14();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Opcode_RESERVED15(s_Opcode* self UNUSED_PARAM)
{
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &Opcode::RESERVED15();
        if (ret->opcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject* 
Opcode_richcmp(s_Opcode* self, s_Opcode* other, int op)
{
    bool c;

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return NULL;
        break;
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return NULL;
        break;
    case Py_EQ:
        c = (*self->opcode == *other->opcode);
        break;
    case Py_NE:
        c = (*self->opcode != *other->opcode);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return NULL;
        break;
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return NULL;
        break;
    default:
        assert(0);              // XXX: should trigger an exception
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

//
// End of Opcode wrapper
//

//
// Rcode
//
typedef struct {
    PyObject_HEAD
    const Rcode* rcode;
} s_Rcode;

static int Rcode_init(s_Rcode* self, PyObject* args);
static void Rcode_destroy(s_Rcode* self);

static PyObject* Rcode_getCode(s_Rcode* self);
static PyObject* Rcode_toText(s_Rcode* self);
static PyObject* Rcode_str(PyObject* self);
static PyObject* Rcode_NOERROR(s_Rcode* self);
static PyObject* Rcode_FORMERR(s_Rcode* self);
static PyObject* Rcode_SERVFAIL(s_Rcode* self);
static PyObject* Rcode_NXDOMAIN(s_Rcode* self);
static PyObject* Rcode_NOTIMP(s_Rcode* self);
static PyObject* Rcode_REFUSED(s_Rcode* self);
static PyObject* Rcode_YXDOMAIN(s_Rcode* self);
static PyObject* Rcode_YXRRSET(s_Rcode* self);
static PyObject* Rcode_NXRRSET(s_Rcode* self);
static PyObject* Rcode_NOTAUTH(s_Rcode* self);
static PyObject* Rcode_NOTZONE(s_Rcode* self);
static PyObject* Rcode_RESERVED11(s_Rcode* self);
static PyObject* Rcode_RESERVED12(s_Rcode* self);
static PyObject* Rcode_RESERVED13(s_Rcode* self);
static PyObject* Rcode_RESERVED14(s_Rcode* self);
static PyObject* Rcode_RESERVED15(s_Rcode* self);
static PyObject* Rcode_BADVERS(s_Rcode* self);
static PyObject* Rcode_richcmp(s_Rcode* self, s_Rcode* other, int op);

static PyMethodDef Rcode_methods[] = {
    { "get_code", (PyCFunction)Rcode_getCode, METH_NOARGS, "Return the code value" },
    { "to_text", (PyCFunction)Rcode_toText, METH_NOARGS, "Return the text representation" },
    { "NOERROR", (PyCFunction)Rcode_NOERROR, METH_NOARGS | METH_STATIC, "Create a NOERROR Rcode" },
    { "FORMERR", (PyCFunction)Rcode_FORMERR, METH_NOARGS | METH_STATIC, "Create a FORMERR Rcode" },
    { "SERVFAIL", (PyCFunction)Rcode_SERVFAIL, METH_NOARGS | METH_STATIC, "Create a SERVFAIL Rcode" },
    { "NXDOMAIN", (PyCFunction)Rcode_NXDOMAIN, METH_NOARGS | METH_STATIC, "Create a NXDOMAIN Rcode" },
    { "NOTIMP", (PyCFunction)Rcode_NOTIMP, METH_NOARGS | METH_STATIC, "Create a NOTIMP Rcode" },
    { "REFUSED", (PyCFunction)Rcode_REFUSED, METH_NOARGS | METH_STATIC, "Create a REFUSED Rcode" },
    { "YXDOMAIN", (PyCFunction)Rcode_YXDOMAIN, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "YXRRSET", (PyCFunction)Rcode_YXRRSET, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "NXRRSET", (PyCFunction)Rcode_NXRRSET, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "NOTAUTH", (PyCFunction)Rcode_NOTAUTH, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "NOTZONE", (PyCFunction)Rcode_NOTZONE, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "RESERVED11", (PyCFunction)Rcode_RESERVED11, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "RESERVED12", (PyCFunction)Rcode_RESERVED12, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "RESERVED13", (PyCFunction)Rcode_RESERVED13, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "RESERVED14", (PyCFunction)Rcode_RESERVED14, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "RESERVED15", (PyCFunction)Rcode_RESERVED15, METH_NOARGS | METH_STATIC, "Create a RESERVED Rcode" },
    { "BADVERS", (PyCFunction)Rcode_BADVERS, METH_NOARGS | METH_STATIC, "Create a BADVERS Rcode" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject rcode_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.Rcode",
    sizeof(s_Rcode),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)Rcode_destroy,        /* tp_dealloc */
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
    Rcode_str,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "C++ Rcode Object",               /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    (richcmpfunc)Rcode_richcmp,       /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    Rcode_methods,                    /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    // TODO: Can we make this NULL? (no direct constructor)
    (initproc)Rcode_init,                /* tp_init */
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


static int
Rcode_init(s_Rcode* self UNUSED_PARAM, PyObject* args UNUSED_PARAM)
{
    uint16_t code = 0;
    if (PyArg_ParseTuple(args, "h", &code)) {
        try {
            self->rcode = new Rcode(code);
        } catch (isc::OutOfRange) {
            PyErr_SetString(PyExc_OverflowError,
                            "rcode out of range");
            return -1;
        }
        return 0;
    } else {
        return -1;
    }
}

static void
Rcode_destroy(s_Rcode* self)
{
    // We only use the consts from Rcode, so don't
    // delete self->rcode here
    delete self->rcode;
    self->rcode = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Rcode_getCode(s_Rcode* self)
{
    return Py_BuildValue("I", self->rcode->getCode());
}

static PyObject*
Rcode_toText(s_Rcode* self)
{
    return Py_BuildValue("s", self->rcode->toText().c_str());
}

static PyObject*
Rcode_str(PyObject* self)
{
    // Simply call the to_text method we already defined
    return PyObject_CallMethod(self, (char*)"to_text", (char*)"");
}

static PyObject*
Rcode_NOERROR(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::NOERROR();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_FORMERR(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::FORMERR();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_SERVFAIL(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::SERVFAIL();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_NXDOMAIN(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::NXDOMAIN();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_NOTIMP(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::NOTIMP();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_REFUSED(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::REFUSED();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_YXDOMAIN(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::YXDOMAIN();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_YXRRSET(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::YXRRSET();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_NXRRSET(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::NXRRSET();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_NOTAUTH(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::NOTAUTH();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_NOTZONE(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::NOTZONE();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_RESERVED11(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::RESERVED11();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_RESERVED12(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::RESERVED12();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_RESERVED13(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::RESERVED13();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_RESERVED14(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::RESERVED14();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_RESERVED15(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::RESERVED15();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject*
Rcode_BADVERS(s_Rcode* self UNUSED_PARAM)
{
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &Rcode::BADVERS();
        if (ret->rcode == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    Py_INCREF(ret);
    return (PyObject*) ret;
}

static PyObject* 
Rcode_richcmp(s_Rcode* self, s_Rcode* other, int op)
{
    bool c;

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return NULL;
        break;
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return NULL;
        break;
    case Py_EQ:
        c = (*self->rcode == *other->rcode);
        break;
    case Py_NE:
        c = (*self->rcode != *other->rcode);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return NULL;
        break;
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return NULL;
        break;
    default:
        assert(0);              // XXX: should trigger an exception
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

//
// End of Rcode wrapper
//


//
// Section
//

// TODO: iterator?

typedef struct {
    PyObject_HEAD
    const Section* section;
} s_Section;

static int Section_init(s_Section* self, PyObject* args);
static void Section_destroy(s_Section* self);

static PyObject* Section_getCode(s_Section* self);
static PyObject* Section_QUESTION(s_Section* self);
static PyObject* Section_ANSWER(s_Section* self);
static PyObject* Section_AUTHORITY(s_Section* self);
static PyObject* Section_ADDITIONAL(s_Section* self);
static PyObject* Section_richcmp(s_Section* self, s_Section* other, int op);

static PyMethodDef Section_methods[] = {
    { "get_code", (PyCFunction)Section_getCode, METH_NOARGS, "Return the code value" },
    { "QUESTION", (PyCFunction)Section_QUESTION, METH_NOARGS | METH_STATIC, "Create a QUESTION Section" },
    { "ANSWER", (PyCFunction)Section_ANSWER, METH_NOARGS | METH_STATIC, "Create a ANSWER Section" },
    { "AUTHORITY", (PyCFunction)Section_AUTHORITY, METH_NOARGS | METH_STATIC, "Create a AUTHORITY Section" },
    { "ADDITIONAL", (PyCFunction)Section_ADDITIONAL, METH_NOARGS | METH_STATIC, "Create a ADDITIONAL Section" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject section_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.Section",
    sizeof(s_Section),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)Section_destroy,        /* tp_dealloc */
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
    "C++ Section Object",               /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    (richcmpfunc)Section_richcmp,       /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    Section_methods,                    /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    // TODO: Can we make this NULL? (no direct constructor)
    (initproc)Section_init,                /* tp_init */
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


static int
Section_init(s_Section* self UNUSED_PARAM, PyObject* args UNUSED_PARAM)
{
    PyErr_SetString(PyExc_NotImplementedError,
                    "Section can't be built directly");
    return -1;
}

static void
Section_destroy(s_Section* self)
{
    // We only use the consts from Section, so don't
    // delete self->section here
    self->section = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Section_getCode(s_Section* self)
{
    return Py_BuildValue("I", self->section->getCode());
}

static PyObject*
Section_QUESTION(s_Section* self UNUSED_PARAM)
{
    s_Section* ret = PyObject_New(s_Section, &section_type);
    if (ret != NULL) {
        ret->section = &Section::QUESTION();
        if (ret->section == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Section_ANSWER(s_Section* self UNUSED_PARAM)
{
    s_Section* ret = PyObject_New(s_Section, &section_type);
    if (ret != NULL) {
        ret->section = &Section::ANSWER();
        if (ret->section == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Section_AUTHORITY(s_Section* self UNUSED_PARAM)
{
    s_Section* ret = PyObject_New(s_Section, &section_type);
    if (ret != NULL) {
        ret->section = &Section::AUTHORITY();
        if (ret->section == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject*
Section_ADDITIONAL(s_Section* self UNUSED_PARAM)
{
    s_Section* ret = PyObject_New(s_Section, &section_type);
    if (ret != NULL) {
        ret->section = &Section::ADDITIONAL();
        if (ret->section == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return (PyObject*) ret;
}

static PyObject* 
Section_richcmp(s_Section* self, s_Section* other, int op)
{
    bool c;

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return NULL;
        break;
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return NULL;
        break;
    case Py_EQ:
        c = (*self->section == *other->section);
        break;
    case Py_NE:
        c = (*self->section != *other->section);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return NULL;
        break;
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return NULL;
        break;
    default:
        assert(0);              // XXX: should trigger an exception
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

//
// End of Section wrapper
//



//
// Message
//

// The s_* Class simply coverst one instantiation of the object
typedef struct {
    PyObject_HEAD
    Message* message;
} s_Message;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
static int Message_init(s_Message* self, PyObject* args);
static void Message_destroy(s_Message* self);

static PyObject* Message_getHeaderFlag(s_Message* self, PyObject* args);
static PyObject* Message_setHeaderFlag(s_Message* self, PyObject* args);
static PyObject* Message_clearHeaderFlag(s_Message* self, PyObject* args);
static PyObject* Message_isDNSSECSupported(s_Message* self);
static PyObject* Message_setDNSSECSupported(s_Message* self, PyObject* args);
static PyObject* Message_getUDPSize(s_Message* self);
static PyObject* Message_setUDPSize(s_Message* self, PyObject* args);
static PyObject* Message_getQid(s_Message* self);
static PyObject* Message_setQid(s_Message* self, PyObject* args);
static PyObject* Message_getRcode(s_Message* self);
static PyObject* Message_setRcode(s_Message* self, PyObject* args);
static PyObject* Message_getOpcode(s_Message* self);
static PyObject* Message_setOpcode(s_Message* self, PyObject* args);
static PyObject* Message_getRRCount(s_Message* self, PyObject* args);
// use direct iterators for these? (or simply lists for now?)
static PyObject* Message_getQuestion(s_Message* self);
static PyObject* Message_getSection(s_Message* self, PyObject* args);
//static PyObject* Message_beginQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_endQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_beginSection(s_Message* self, PyObject* args);
//static PyObject* Message_endSection(s_Message* self, PyObject* args);

// TODO: Question not wrapped yet
//static PyObject* Message_addQuestion(s_Message* self, PyObject* args);
static PyObject* Message_addRRset(s_Message* self, PyObject* args);
static PyObject* Message_clear(s_Message* self, PyObject* args);
static PyObject* Message_makeResponse(s_Message* self);
static PyObject* Message_toText(s_Message* self);
static PyObject* Message_str(PyObject* self);
static PyObject* Message_toWire(s_Message* self, PyObject* args);
static PyObject* Message_fromWire(s_Message* self, PyObject* args);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
static PyMethodDef Message_methods[] = {
    { "get_header_flag", (PyCFunction)Message_getHeaderFlag, METH_VARARGS, "" },
    { "set_header_flag", (PyCFunction)Message_setHeaderFlag, METH_VARARGS, "" },
    { "clear_header_flag", (PyCFunction)Message_clearHeaderFlag, METH_VARARGS, "" },
    { "is_dnssec_supported", (PyCFunction)Message_isDNSSECSupported, METH_NOARGS, "" },
    { "set_dnssec_supported", (PyCFunction)Message_setDNSSECSupported, METH_VARARGS, "" },
    { "get_udp_size", (PyCFunction)Message_getUDPSize, METH_NOARGS, "" },
    { "set_udp_size", (PyCFunction)Message_setUDPSize, METH_VARARGS, "" },
    { "get_qid", (PyCFunction)Message_getQid, METH_NOARGS, "" },
    { "set_qid", (PyCFunction)Message_setQid, METH_VARARGS, "" },
    { "get_rcode", (PyCFunction)Message_getRcode, METH_NOARGS, "" },
    { "set_rcode", (PyCFunction)Message_setRcode, METH_VARARGS, "" },
    { "get_opcode", (PyCFunction)Message_getOpcode, METH_NOARGS, "" },
    { "set_opcode", (PyCFunction)Message_setOpcode, METH_VARARGS, "" },
    { "get_rr_count", (PyCFunction)Message_getRRCount, METH_VARARGS, "" },
    { "get_question", (PyCFunction)Message_getQuestion, METH_NOARGS, "Returns a list of all Question object in the message (should be 0 or 1)" },
    { "get_section", (PyCFunction)Message_getSection, METH_VARARGS, "Returns a list of all RRset objects in the given section of the message" },
//    { "add_question", (PyCFunction)Message_addQuestion, METH_VARARGS, "" },
    { "add_rrset", (PyCFunction)Message_addRRset, METH_VARARGS, "" },
    { "clear", (PyCFunction)Message_clear, METH_VARARGS, "" },
    { "make_response", (PyCFunction)Message_makeResponse, METH_NOARGS, "" },
    { "to_text", (PyCFunction)Message_toText, METH_NOARGS, "Return the string representation" },
    { "to_wire", (PyCFunction)Message_toWire, METH_VARARGS, "to wire format" },
    { "from_wire", (PyCFunction)Message_fromWire, METH_VARARGS, "to wire format" },
    { NULL, NULL, 0, NULL }
};

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Message
// Most of the functions are not actually implemented and NULL here.
static PyTypeObject message_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.Message",
    sizeof(s_Message),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)Message_destroy,        /* tp_dealloc */
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
    Message_str,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "C++ Message Object",               /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,       /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    Message_methods,                    /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc)Message_init,                /* tp_init */
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

static int
Message_init(s_Message* self, PyObject* args)
{
    unsigned int i;
    // The constructor argument can be a string ("IN"), an integer (1),
    // or a sequence of numbers between 0 and 255 (wire code)
    
    if (PyArg_ParseTuple(args, "I", &i)) {
        PyErr_Clear();
        if (i == Message::PARSE) {
            self->message = new Message(Message::PARSE);
            Py_INCREF(self);
            return 0;
        } else if (i == Message::RENDER) {
            Py_INCREF(self);
            self->message = new Message(Message::RENDER);
            return 0;
        } else {
            PyErr_SetString(PyExc_TypeError, "Message mode must be Message.PARSE or Message.RENDER");
            return -1;
        }
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "no valid type in constructor argument");
    return -1;
}

static void
Message_destroy(s_Message* self)
{
    if (self->message != NULL)
        delete self->message;
    self->message = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Message_getHeaderFlag(s_Message* self, PyObject* args)
{
    s_MessageFlag* messageflag;
    if (!PyArg_ParseTuple(args, "O!", &messageflag_type, &messageflag)) {
        return NULL;
    }
    
    if (self->message->getHeaderFlag(*messageflag->messageflag)) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject*
Message_setHeaderFlag(s_Message* self, PyObject* args)
{
    s_MessageFlag* messageflag;
    if (!PyArg_ParseTuple(args, "O!", &messageflag_type, &messageflag)) {
        return NULL;
    }

    self->message->setHeaderFlag(*messageflag->messageflag);

    Py_RETURN_NONE;
}

static PyObject*
Message_clearHeaderFlag(s_Message* self, PyObject* args)
{
    s_MessageFlag* messageflag;
    if (!PyArg_ParseTuple(args, "O!", &messageflag_type, &messageflag)) {
        return NULL;
    }

    self->message->clearHeaderFlag(*messageflag->messageflag);

    Py_RETURN_NONE;
}

static PyObject*
Message_isDNSSECSupported(s_Message* self)
{
    if (self->message->isDNSSECSupported()) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject*
Message_setDNSSECSupported(s_Message* self, PyObject* args)
{
    PyObject *b;
    if (!PyArg_ParseTuple(args, "O!", &PyBool_Type, &b)) {
        return NULL;
    }
    try {
        if (b == Py_True) {
            self->message->setDNSSECSupported(true);
        } else {
            self->message->setDNSSECSupported(false);
        }
        Py_RETURN_NONE;
    } catch (isc::dns::InvalidMessageOperation imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return NULL;
    }
}

static PyObject*
Message_getUDPSize(s_Message* self)
{
    return Py_BuildValue("I", self->message->getUDPSize());
}

static PyObject*
Message_setUDPSize(s_Message* self, PyObject* args)
{
    uint16_t size;
    if (!PyArg_ParseTuple(args, "I", &size)) {
        return NULL;
    }
    try {
        self->message->setUDPSize(size);
        Py_RETURN_NONE;
    } catch (isc::dns::InvalidMessageUDPSize imus) {
        PyErr_SetString(po_InvalidMessageUDPSize, imus.what());
        return NULL;
    } catch (isc::dns::InvalidMessageOperation imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return NULL;
    }
}

static PyObject*
Message_getQid(s_Message* self)
{
    return Py_BuildValue("I", self->message->getQid());
}

static PyObject*
Message_setQid(s_Message* self, PyObject* args)
{
    uint16_t id;
    if (!PyArg_ParseTuple(args, "I", &id)) {
        return NULL;
    }
    self->message->setQid(id);
    Py_RETURN_NONE;
}

static PyObject*
Message_getRcode(s_Message* self)
{
    s_Rcode* rcode;

    rcode = (s_Rcode*)rcode_type.tp_alloc(&rcode_type, 0);
    if (rcode != NULL) {
        rcode->rcode = new Rcode(self->message->getRcode());
        if (rcode->rcode == NULL)
          {
            Py_DECREF(rcode);
            return NULL;
          }
    }

    return (PyObject*)rcode;
}

static PyObject*
Message_setRcode(s_Message* self, PyObject* args)
{
    s_Rcode* rcode;
    if (!PyArg_ParseTuple(args, "O!", &rcode_type, &rcode)) {
        return NULL;
    }
    self->message->setRcode(*rcode->rcode);
    Py_RETURN_NONE;
}

static PyObject*
Message_getOpcode(s_Message* self)
{
    s_Opcode* opcode;

    opcode = (s_Opcode*)opcode_type.tp_alloc(&opcode_type, 0);
    if (opcode != NULL) {
        // Note that we do not new and delete for opcodes.
        // all rcodes point to the statics defined in
        // message.cc
        opcode->opcode = &self->message->getOpcode();
        if (opcode->opcode == NULL)
          {
            Py_DECREF(opcode);
            return NULL;
          }
    }

    return (PyObject*)opcode;
}

static PyObject*
Message_setOpcode(s_Message* self, PyObject* args)
{
    s_Opcode* opcode;
    if (!PyArg_ParseTuple(args, "O!", &opcode_type, &opcode)) {
        return NULL;
    }
    self->message->setOpcode(*opcode->opcode);
    Py_RETURN_NONE;
}

static PyObject*
Message_getRRCount(s_Message* self, PyObject* args)
{
    s_Section *section;
    if (!PyArg_ParseTuple(args, "O!", &section_type, &section)) {
        return NULL;
    }
    return Py_BuildValue("I", self->message->getRRCount(*section->section));
}

// TODO use direct iterators for these? (or simply lists for now?)
static PyObject*
Message_getQuestion(s_Message* self)
{
    PyObject* list = PyList_New(0);
    
    for (QuestionIterator qi = self->message->beginQuestion();
         qi != self->message->endQuestion();
         ++qi) {
        s_Question *question = (s_Question*)question_type.tp_alloc(&question_type, 0);
        if (question != NULL) {
            question->question = new Question(*qi->get());
            if (question->question == NULL)
              {
                Py_DECREF(question);
                return NULL;
              }
        }
        PyList_Append(list, (PyObject*) question);
    }
    return list;
}

static PyObject*
Message_getSection(s_Message* self, PyObject* args)
{
    s_Section *section;
    if (!PyArg_ParseTuple(args, "O!", &section_type, &section)) {
        return NULL;
    }
    PyObject* list = PyList_New(0);
    
    for (RRsetIterator rrsi = self->message->beginSection(*section->section);
         rrsi != self->message->endSection(*section->section);
         ++rrsi) {
        s_RRset *rrset = (s_RRset*)rrset_type.tp_alloc(&rrset_type, 0);
        if (rrset != NULL) {
            rrset->rrset = rrsi->get();
            if (rrset->rrset == NULL)
              {
                Py_DECREF(rrset);
                return NULL;
              }
        }
        PyList_Append(list, (PyObject*) rrset);
    }
    return list;
}

//static PyObject* Message_beginQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_endQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_beginSection(s_Message* self, PyObject* args);
//static PyObject* Message_endSection(s_Message* self, PyObject* args);
//static PyObject* Message_addQuestion(s_Message* self, PyObject* args);

static PyObject*
Message_addRRset(s_Message* self, PyObject* args)
{
    PyObject *sign;
    s_Section* section;
    s_RRset* rrset;
    if (!PyArg_ParseTuple(args, "O!O!|O!", &section_type, &section,
                                           &rrset_type, &rrset,
                                           &PyBool_Type, &sign)) {
        return NULL;
    }
    Py_INCREF(rrset);
    RRsetPtr rrset_ptr = RRsetPtr(rrset->rrset);

    if (sign == Py_True) {
        self->message->addRRset(*section->section, rrset_ptr, true);
    } else {
        self->message->addRRset(*section->section, rrset_ptr, false);
    }
    
    Py_RETURN_NONE;
}

static PyObject*
Message_clear(s_Message* self, PyObject* args)
{
    unsigned int i;
    // The constructor argument can be a string ("IN"), an integer (1),
    // or a sequence of numbers between 0 and 255 (wire code)

    if (PyArg_ParseTuple(args, "I", &i)) {
        PyErr_Clear();
        if (i == Message::PARSE) {
            self->message->clear(Message::PARSE);
            Py_RETURN_NONE;
        } else if (i == Message::RENDER) {
            self->message->clear(Message::RENDER);
            Py_RETURN_NONE;
        } else {
            PyErr_SetString(PyExc_TypeError, "Message mode must be Message.PARSE or Message.RENDER");
            return NULL;
        }
    } else {
        return NULL;
    }
}

static PyObject*
Message_makeResponse(s_Message* self)
{
    self->message->makeResponse();
    Py_RETURN_NONE;
}

static PyObject*
Message_toText(s_Message* self)
{
    // Py_BuildValue makes python objects from native data
    return Py_BuildValue("s", self->message->toText().c_str());
}

static PyObject*
Message_str(PyObject* self)
{
    // Simply call the to_text method we already defined
    return PyObject_CallMethod(self, (char*)"to_text", (char*)"");
}

static PyObject*
Message_toWire(s_Message* self, PyObject* args)
{
    s_MessageRenderer* mr;
    
    if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, (PyObject**) &mr)) {
        self->message->toWire(*mr->messagerenderer);
        // If we return NULL it is seen as an error, so use this for
        // None returns
        Py_RETURN_NONE;
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a sequence object or a MessageRenderer");
    return NULL;
}

static PyObject*
Message_fromWire(s_Message* self, PyObject* args)
{
    const char* b;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "y#", &b, &len)) {
        return NULL;
    }
    
    InputBuffer inbuf(b, len);
    try {
        self->message->fromWire(inbuf);
        Py_RETURN_NONE;
    } catch (isc::dns::DNSMessageFORMERR dmfe) {
        PyErr_SetString(po_DNSMessageFORMERR, dmfe.what());
        return NULL;
    } catch (isc::dns::DNSMessageBADVERS dmfe) {
        PyErr_SetString(po_DNSMessageBADVERS, dmfe.what());
        return NULL;
    }
}

// end of Message


// Module Initialization, all statics are initialized here
bool
initModulePart_Message(PyObject* mod)
{
    // Add the exceptions to the module
    po_MessageTooShort = PyErr_NewException("libdns_python.MessageTooShort", NULL, NULL);
    Py_INCREF(po_MessageTooShort);
    PyModule_AddObject(mod, "MessageTooShort", po_MessageTooShort);
    po_InvalidMessageSection = PyErr_NewException("libdns_python.InvalidMessageSection", NULL, NULL);
    Py_INCREF(po_InvalidMessageSection);
    PyModule_AddObject(mod, "InvalidMessageSection", po_InvalidMessageSection);
    po_InvalidMessageOperation = PyErr_NewException("libdns_python.InvalidMessageOperation", NULL, NULL);
    Py_INCREF(po_InvalidMessageOperation);
    PyModule_AddObject(mod, "InvalidMessageOperation", po_InvalidMessageOperation);
    po_InvalidMessageUDPSize = PyErr_NewException("libdns_python.InvalidMessageUDPSize", NULL, NULL);
    Py_INCREF(po_InvalidMessageUDPSize);
    PyModule_AddObject(mod, "InvalidMessageUDPSize", po_InvalidMessageUDPSize);
    po_DNSMessageBADVERS = PyErr_NewException("libdns_python.DNSMessageBADVERS", NULL, NULL);
    Py_INCREF(po_DNSMessageBADVERS);
    PyModule_AddObject(mod, "DNSMessageBADVERS", po_DNSMessageBADVERS);

    // Constants. These should probably go into the Message class, but need to find out how first
    po_MessagePARSE = Py_BuildValue("I", Message::PARSE);
    Py_INCREF(po_MessagePARSE);
    PyModule_AddObject(mod, "PARSE", po_MessagePARSE);
    po_MessageRENDER = Py_BuildValue("I", Message::RENDER);
    Py_INCREF(po_MessageRENDER);
    PyModule_AddObject(mod, "RENDER", po_MessageRENDER);
    po_MessageDefaultMaxUDPSize = Py_BuildValue("I", Message::DEFAULT_MAX_UDPSIZE);
    Py_INCREF(po_MessageDefaultMaxUDPSize);
    PyModule_AddObject(mod, "DEFAULT_MAX_UDPSIZE", po_MessageDefaultMaxUDPSize);

    /* add methods to class */
    if (PyType_Ready(&messageflag_type) < 0) {
        return false;
    }
    Py_INCREF(&messageflag_type);
    PyModule_AddObject(mod, "MessageFlag",
                       (PyObject*) &messageflag_type);

    
    if (PyType_Ready(&opcode_type) < 0) {
        return false;
    }
    Py_INCREF(&opcode_type);
    PyModule_AddObject(mod, "Opcode",
                       (PyObject*) &opcode_type);

    if (PyType_Ready(&rcode_type) < 0) {
        return false;
    }
    Py_INCREF(&rcode_type);
    PyModule_AddObject(mod, "Rcode",
                       (PyObject*) &rcode_type);

    if (PyType_Ready(&section_type) < 0) {
        return false;
    }
    Py_INCREF(&section_type);
    PyModule_AddObject(mod, "Section",
                       (PyObject*) &section_type);

    
    if (PyType_Ready(&message_type) < 0) {
        return false;
    }
    Py_INCREF(&message_type);
    PyModule_AddObject(mod, "Message",
                       (PyObject*) &message_type);
    

    return true;
}
