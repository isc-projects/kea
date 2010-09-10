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
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description


//
// MessageFlag
//
class s_MessageFlag : public PyObject {
public:
    const MessageFlag* messageflag;
};

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
    { "get_bit", reinterpret_cast<PyCFunction>(MessageFlag_getBit), METH_NOARGS, "Returns the flag bit" },
    { "QR", reinterpret_cast<PyCFunction>(MessageFlag_QR), METH_NOARGS | METH_STATIC, "Creates a QR MessageFlag" },
    { "AA", reinterpret_cast<PyCFunction>(MessageFlag_AA), METH_NOARGS | METH_STATIC, "Creates a AA MessageFlag" },
    { "TC", reinterpret_cast<PyCFunction>(MessageFlag_TC), METH_NOARGS | METH_STATIC, "Creates a TC MessageFlag" },
    { "RD", reinterpret_cast<PyCFunction>(MessageFlag_RD), METH_NOARGS | METH_STATIC, "Creates a RD MessageFlag" },
    { "RA", reinterpret_cast<PyCFunction>(MessageFlag_RA), METH_NOARGS | METH_STATIC, "Creates a RA MessageFlag" },
    { "AD", reinterpret_cast<PyCFunction>(MessageFlag_AD), METH_NOARGS | METH_STATIC, "Creates a AD MessageFlag" },
    { "CD", reinterpret_cast<PyCFunction>(MessageFlag_CD), METH_NOARGS | METH_STATIC, "Creates a CD MessageFlag" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject messageflag_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.MessageFlag",
    sizeof(s_MessageFlag),              // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)MessageFlag_destroy,    // tp_dealloc
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
    "The MessageFlag class objects represent standard "
    "flag bits of the header section of DNS messages.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    MessageFlag_methods,                // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)MessageFlag_init,         // tp_init
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
MessageFlag_init(s_MessageFlag* self UNUSED_PARAM,
                 PyObject* args UNUSED_PARAM)
{
    PyErr_SetString(PyExc_NotImplementedError,
                    "MessageFlag can't be built directly");
    return (-1);
}

static void
MessageFlag_destroy(s_MessageFlag* self) {
    // We only use the consts from MessageFlag, so don't
    // delete self->messageflag here
    self->messageflag = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
MessageFlag_getBit(s_MessageFlag* self) {
    return (Py_BuildValue("I", self->messageflag->getBit()));
}

static PyObject*
MessageFlag_createStatic(const MessageFlag& flag) {
    s_MessageFlag* ret = PyObject_New(s_MessageFlag, &messageflag_type);
    if (ret != NULL) {
        ret->messageflag = &flag;
    }
    return (ret);
}

static PyObject*
MessageFlag_QR(s_MessageFlag* self UNUSED_PARAM) {
    return (MessageFlag_createStatic(MessageFlag::QR()));
}

static PyObject*
MessageFlag_AA(s_MessageFlag* self UNUSED_PARAM) {
    return (MessageFlag_createStatic(MessageFlag::AA()));
}

static PyObject*
MessageFlag_TC(s_MessageFlag* self UNUSED_PARAM) {
    return (MessageFlag_createStatic(MessageFlag::TC()));
}

static PyObject*
MessageFlag_RD(s_MessageFlag* self UNUSED_PARAM) {
    return (MessageFlag_createStatic(MessageFlag::RD()));
}

static PyObject*
MessageFlag_RA(s_MessageFlag* self UNUSED_PARAM) {
    return (MessageFlag_createStatic(MessageFlag::RA()));
}

static PyObject*
MessageFlag_AD(s_MessageFlag* self UNUSED_PARAM) {
    return (MessageFlag_createStatic(MessageFlag::AD()));
}

static PyObject*
MessageFlag_CD(s_MessageFlag* self UNUSED_PARAM) {
    return (MessageFlag_createStatic(MessageFlag::CD()));
}

//
// End of MessageFlag wrapper
//


//
// Opcode
//
class s_Opcode : public PyObject {
public:
    const Opcode* opcode;
};

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
    { "get_code", reinterpret_cast<PyCFunction>(Opcode_getCode), METH_NOARGS, "Returns the code value" },
    { "to_text", reinterpret_cast<PyCFunction>(Opcode_toText), METH_NOARGS, "Returns the text representation" },
    { "QUERY", reinterpret_cast<PyCFunction>(Opcode_QUERY), METH_NOARGS | METH_STATIC, "Creates a QUERY Opcode" },
    { "IQUERY", reinterpret_cast<PyCFunction>(Opcode_IQUERY), METH_NOARGS | METH_STATIC, "Creates a IQUERY Opcode" },
    { "STATUS", reinterpret_cast<PyCFunction>(Opcode_STATUS), METH_NOARGS | METH_STATIC, "Creates a STATUS Opcode" },
    { "RESERVED3", reinterpret_cast<PyCFunction>(Opcode_RESERVED3), METH_NOARGS | METH_STATIC, "Creates a RESERVED3 Opcode" },
    { "NOTIFY", reinterpret_cast<PyCFunction>(Opcode_NOTIFY), METH_NOARGS | METH_STATIC, "Creates a NOTIFY Opcode" },
    { "UPDATE", reinterpret_cast<PyCFunction>(Opcode_UPDATE), METH_NOARGS | METH_STATIC, "Creates a UPDATE Opcode" },
    { "RESERVED6", reinterpret_cast<PyCFunction>(Opcode_RESERVED6), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED7", reinterpret_cast<PyCFunction>(Opcode_RESERVED7), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED8", reinterpret_cast<PyCFunction>(Opcode_RESERVED8), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED9", reinterpret_cast<PyCFunction>(Opcode_RESERVED9), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED10", reinterpret_cast<PyCFunction>(Opcode_RESERVED10), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED11", reinterpret_cast<PyCFunction>(Opcode_RESERVED11), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED12", reinterpret_cast<PyCFunction>(Opcode_RESERVED12), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED13", reinterpret_cast<PyCFunction>(Opcode_RESERVED13), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED14", reinterpret_cast<PyCFunction>(Opcode_RESERVED14), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { "RESERVED15", reinterpret_cast<PyCFunction>(Opcode_RESERVED15), METH_NOARGS | METH_STATIC, "Creates a RESERVED Opcode" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject opcode_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Opcode",
    sizeof(s_Opcode),                   // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Opcode_destroy,         // tp_dealloc
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
    Opcode_str,                         // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Opcode class objects represent standard OPCODEs "
    "of the header section of DNS messages.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)Opcode_richcmp,        // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Opcode_methods,                     // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Opcode_init,              // tp_init
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
Opcode_init(s_Opcode* self UNUSED_PARAM, PyObject* args UNUSED_PARAM) {
    PyErr_SetString(PyExc_NotImplementedError,
                    "Opcode can't be built directly");
    return (-1);
}

static void
Opcode_destroy(s_Opcode* self) {
    // We only use the consts from Opcode, so don't
    // delete self->opcode here
    self->opcode = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Opcode_getCode(s_Opcode* self) {
    return (Py_BuildValue("I", self->opcode->getCode()));
}

static PyObject*
Opcode_toText(s_Opcode* self) {
    return (Py_BuildValue("s", self->opcode->toText().c_str()));
}

static PyObject*
Opcode_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

static PyObject*
Opcode_createStatic(const Opcode& opcode) {
    s_Opcode* ret = PyObject_New(s_Opcode, &opcode_type);
    if (ret != NULL) {
        ret->opcode = &opcode;
    }
    return (ret);
}

static PyObject*
Opcode_QUERY(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::QUERY()));
}

static PyObject*
Opcode_IQUERY(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::IQUERY()));
}

static PyObject*
Opcode_STATUS(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::STATUS()));
}

static PyObject*
Opcode_RESERVED3(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED3()));
}

static PyObject*
Opcode_NOTIFY(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::NOTIFY()));
}

static PyObject*
Opcode_UPDATE(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::UPDATE()));
}

static PyObject*
Opcode_RESERVED6(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED6()));
}

static PyObject*
Opcode_RESERVED7(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED7()));
}

static PyObject*
Opcode_RESERVED8(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED8()));
}

static PyObject*
Opcode_RESERVED9(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED9()));
}

static PyObject*
Opcode_RESERVED10(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED10()));
}

static PyObject*
Opcode_RESERVED11(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED11()));
}

static PyObject*
Opcode_RESERVED12(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED12()));
}

static PyObject*
Opcode_RESERVED13(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED13()));
}

static PyObject*
Opcode_RESERVED14(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED14()));
}

static PyObject*
Opcode_RESERVED15(s_Opcode* self UNUSED_PARAM) {
    return (Opcode_createStatic(Opcode::RESERVED15()));
}

static PyObject* 
Opcode_richcmp(s_Opcode* self, s_Opcode* other, int op) {
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return (NULL);
        break;
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return (NULL);
        break;
    case Py_EQ:
        c = (*self->opcode == *other->opcode);
        break;
    case Py_NE:
        c = (*self->opcode != *other->opcode);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return (NULL);
        break;
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Opcode");
        return (NULL);
        break;
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

// We added a helper variable static_code here
// Since we can create Rcodes dynamically with Rcode(int), but also
// use the static globals (Rcode::NOERROR() etc), we use this
// variable to see if the code came from one of the latter, in which
// case Rcode_destroy should not free it (the other option is to
// allocate new Rcodes for every use of the static ones, but this
// seems more efficient).
class s_Rcode : public PyObject {
public:
    const Rcode* rcode;
    bool static_code;
};

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
    { "get_code", reinterpret_cast<PyCFunction>(Rcode_getCode), METH_NOARGS, "Returns the code value" },
    { "to_text", reinterpret_cast<PyCFunction>(Rcode_toText), METH_NOARGS, "Returns the text representation" },
    { "NOERROR", reinterpret_cast<PyCFunction>(Rcode_NOERROR), METH_NOARGS | METH_STATIC, "Creates a NOERROR Rcode" },
    { "FORMERR", reinterpret_cast<PyCFunction>(Rcode_FORMERR), METH_NOARGS | METH_STATIC, "Creates a FORMERR Rcode" },
    { "SERVFAIL", reinterpret_cast<PyCFunction>(Rcode_SERVFAIL), METH_NOARGS | METH_STATIC, "Creates a SERVFAIL Rcode" },
    { "NXDOMAIN", reinterpret_cast<PyCFunction>(Rcode_NXDOMAIN), METH_NOARGS | METH_STATIC, "Creates a NXDOMAIN Rcode" },
    { "NOTIMP", reinterpret_cast<PyCFunction>(Rcode_NOTIMP), METH_NOARGS | METH_STATIC, "Creates a NOTIMP Rcode" },
    { "REFUSED", reinterpret_cast<PyCFunction>(Rcode_REFUSED), METH_NOARGS | METH_STATIC, "Creates a REFUSED Rcode" },
    { "YXDOMAIN", reinterpret_cast<PyCFunction>(Rcode_YXDOMAIN), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "YXRRSET", reinterpret_cast<PyCFunction>(Rcode_YXRRSET), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "NXRRSET", reinterpret_cast<PyCFunction>(Rcode_NXRRSET), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "NOTAUTH", reinterpret_cast<PyCFunction>(Rcode_NOTAUTH), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "NOTZONE", reinterpret_cast<PyCFunction>(Rcode_NOTZONE), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "RESERVED11", reinterpret_cast<PyCFunction>(Rcode_RESERVED11), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "RESERVED12", reinterpret_cast<PyCFunction>(Rcode_RESERVED12), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "RESERVED13", reinterpret_cast<PyCFunction>(Rcode_RESERVED13), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "RESERVED14", reinterpret_cast<PyCFunction>(Rcode_RESERVED14), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "RESERVED15", reinterpret_cast<PyCFunction>(Rcode_RESERVED15), METH_NOARGS | METH_STATIC, "Creates a RESERVED Rcode" },
    { "BADVERS", reinterpret_cast<PyCFunction>(Rcode_BADVERS), METH_NOARGS | METH_STATIC, "Creates a BADVERS Rcode" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject rcode_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Rcode",
    sizeof(s_Rcode),                    // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Rcode_destroy,          // tp_dealloc
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
    Rcode_str,                          // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Rcode class objects represent standard RCODEs"
    "of the header section of DNS messages.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)Rcode_richcmp,         // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Rcode_methods,                      // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Rcode_init,               // tp_init
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
Rcode_init(s_Rcode* self UNUSED_PARAM, PyObject* args UNUSED_PARAM) {
    uint16_t code = 0;
    if (PyArg_ParseTuple(args, "h", &code)) {
        try {
            self->rcode = new Rcode(code);
            self->static_code = false;
        } catch (const isc::OutOfRange&) {
            PyErr_SetString(PyExc_OverflowError,
                            "rcode out of range");
            return (-1);
        }
        return (0);
    } else {
        return (-1);
    }
}

static void
Rcode_destroy(s_Rcode* self) {
    // Depending on whether we created the rcode or are referring
    // to a global static one, we do or do not delete self->rcode here
    if (!self->static_code) {
        delete self->rcode;
    }
    self->rcode = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Rcode_getCode(s_Rcode* self) {
    return (Py_BuildValue("I", self->rcode->getCode()));
}

static PyObject*
Rcode_toText(s_Rcode* self) {
    return (Py_BuildValue("s", self->rcode->toText().c_str()));
}

static PyObject*
Rcode_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

static PyObject*
Rcode_createStatic(const Rcode& rcode) {
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &rcode;
        ret->static_code = true;
    }
    return (ret);
}

static PyObject*
Rcode_NOERROR(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::NOERROR()));
}

static PyObject*
Rcode_FORMERR(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::FORMERR()));
}

static PyObject*
Rcode_SERVFAIL(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::SERVFAIL()));
}

static PyObject*
Rcode_NXDOMAIN(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::NXDOMAIN()));
}

static PyObject*
Rcode_NOTIMP(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::NOTIMP()));
}

static PyObject*
Rcode_REFUSED(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::REFUSED()));
}

static PyObject*
Rcode_YXDOMAIN(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::YXDOMAIN()));
}

static PyObject*
Rcode_YXRRSET(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::YXRRSET()));
}

static PyObject*
Rcode_NXRRSET(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::NXRRSET()));
}

static PyObject*
Rcode_NOTAUTH(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::NOTAUTH()));
}

static PyObject*
Rcode_NOTZONE(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::NOTZONE()));
}

static PyObject*
Rcode_RESERVED11(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::RESERVED11()));
}

static PyObject*
Rcode_RESERVED12(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::RESERVED12()));
}

static PyObject*
Rcode_RESERVED13(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::RESERVED13()));
}

static PyObject*
Rcode_RESERVED14(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::RESERVED14()));
}

static PyObject*
Rcode_RESERVED15(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::RESERVED15()));
}

static PyObject*
Rcode_BADVERS(s_Rcode* self UNUSED_PARAM) {
    return (Rcode_createStatic(Rcode::BADVERS()));
}

static PyObject* 
Rcode_richcmp(s_Rcode* self, s_Rcode* other, int op) {
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return (NULL);
        break;
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return (NULL);
        break;
    case Py_EQ:
        c = (*self->rcode == *other->rcode);
        break;
    case Py_NE:
        c = (*self->rcode != *other->rcode);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return (NULL);
        break;
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return (NULL);
        break;
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

class s_Section : public PyObject {
public:
    const Section* section;
};

static int Section_init(s_Section* self, PyObject* args);
static void Section_destroy(s_Section* self);

static PyObject* Section_getCode(s_Section* self);
static PyObject* Section_QUESTION(s_Section* self);
static PyObject* Section_ANSWER(s_Section* self);
static PyObject* Section_AUTHORITY(s_Section* self);
static PyObject* Section_ADDITIONAL(s_Section* self);
static PyObject* Section_richcmp(s_Section* self, s_Section* other, int op);

static PyMethodDef Section_methods[] = {
    { "get_code", reinterpret_cast<PyCFunction>(Section_getCode), METH_NOARGS, "Returns the code value" },
    { "QUESTION", reinterpret_cast<PyCFunction>(Section_QUESTION), METH_NOARGS | METH_STATIC, "Creates a QUESTION Section" },
    { "ANSWER", reinterpret_cast<PyCFunction>(Section_ANSWER), METH_NOARGS | METH_STATIC, "Creates an ANSWER Section" },
    { "AUTHORITY", reinterpret_cast<PyCFunction>(Section_AUTHORITY), METH_NOARGS | METH_STATIC, "Creates an AUTHORITY Section" },
    { "ADDITIONAL", reinterpret_cast<PyCFunction>(Section_ADDITIONAL), METH_NOARGS | METH_STATIC, "Creates an ADDITIONAL Section" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject section_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Section",
    sizeof(s_Section),                  // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Section_destroy,        // tp_dealloc
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
    "The Section class objects represent DNS message sections such "
    "as the header, question, or answer.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)Section_richcmp,       // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Section_methods,                    // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Section_init,             // tp_init
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
Section_init(s_Section* self UNUSED_PARAM,
             PyObject* args UNUSED_PARAM)
{
    PyErr_SetString(PyExc_NotImplementedError,
                    "Section can't be built directly");
    return (-1);
}

static void
Section_destroy(s_Section* self) {
    // We only use the consts from Section, so don't
    // delete self->section here
    self->section = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Section_getCode(s_Section* self) {
    return (Py_BuildValue("I", self->section->getCode()));
}

static PyObject*
Section_createStatic(const Section& section) {
    s_Section* ret = PyObject_New(s_Section, &section_type);
    if (ret != NULL) {
        ret->section = &section;
    }
    return (ret);
}


static PyObject*
Section_QUESTION(s_Section* self UNUSED_PARAM) {
    return (Section_createStatic(Section::QUESTION()));
}

static PyObject*
Section_ANSWER(s_Section* self UNUSED_PARAM) {
    return (Section_createStatic(Section::ANSWER()));
}

static PyObject*
Section_AUTHORITY(s_Section* self UNUSED_PARAM) {
    return (Section_createStatic(Section::AUTHORITY()));
}

static PyObject*
Section_ADDITIONAL(s_Section* self UNUSED_PARAM) {
    return (Section_createStatic(Section::ADDITIONAL()));
}

static PyObject* 
Section_richcmp(s_Section* self, s_Section* other, int op) {
    bool c = false;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    // Only equals and not equals here, unorderable type
    switch (op) {
    case Py_LT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return (NULL);
        break;
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return (NULL);
        break;
    case Py_EQ:
        c = (*self->section == *other->section);
        break;
    case Py_NE:
        c = (*self->section != *other->section);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return (NULL);
        break;
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Section");
        return (NULL);
        break;
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
class s_Message : public PyObject {
public:
    Message* message;
};

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

static PyObject* Message_addQuestion(s_Message* self, PyObject* args);
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
    { "get_header_flag", reinterpret_cast<PyCFunction>(Message_getHeaderFlag), METH_VARARGS,
      "Return whether the specified header flag bit is set in the "
      "header section. Takes a MessageFlag object as the only argument." },
    { "set_header_flag", reinterpret_cast<PyCFunction>(Message_setHeaderFlag), METH_VARARGS,
      "Sets the specified header flag bit to 1. The message must be in "
      "RENDER mode. If not, an InvalidMessageOperation is raised. "
      "Takes a MessageFlag object as the only argument." },
    { "clear_header_flag", reinterpret_cast<PyCFunction>(Message_clearHeaderFlag), METH_VARARGS, 
      "Sets the specified header flag bit to 0. The message must be in "
      "RENDER mode. If not, an InvalidMessageOperation is raised. "
      "Takes a MessageFlag object as the only argument." },
    { "is_dnssec_supported", reinterpret_cast<PyCFunction>(Message_isDNSSECSupported), METH_NOARGS,
      "Returns True if the message sender indicates DNSSEC is supported. "
      "If EDNS is included, this corresponds to the value of the DO bit. "
      "Otherwise, DNSSEC is considered not supported." },
    { "set_dnssec_supported", reinterpret_cast<PyCFunction>(Message_setDNSSECSupported), METH_VARARGS,
      "Specify whether DNSSEC is supported in the message. "
      "The message must be in RENDER mode. If not, an "
      "InvalidMessageOperation is raised."
      "If EDNS is included in the message, the DO bit is set or cleared "
      "according to given argument (True or False) of this method."},
    { "get_udp_size", reinterpret_cast<PyCFunction>(Message_getUDPSize), METH_NOARGS,
      "Return the maximum buffer size of UDP messages for the sender "
      "of the message.\n\n"
      "The semantics of this value is different based on the mode:\n"
      "In the PARSE mode, it means the buffer size of the remote node;\n"
      "in the RENDER mode, it means the buffer size of the local node.\n\n"
      "In either case, its value is the value of the UDP payload size field "
      "of EDNS (when it's included) or DEFAULT_MAX_UDPSIZE." },
    { "set_udp_size", reinterpret_cast<PyCFunction>(Message_setUDPSize), METH_VARARGS,
      "Specify the maximum buffer size of UDP messages of the local "
      "node. If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised.\n\n"
      "If EDNS OPT RR is included in the message, its UDP payload size field "
      "will be set to the specified value.\n"
      "Unless explicitly specified, DEFAULT_MAX_UDPSIZE will be assumed "
      "for the maximum buffer size, regardless of whether EDNS OPT RR is "
      "included or not.  This means if an application wants to send a message "
      "with an EDNS OPT RR for specifying a larger UDP size, it must explicitly "
      "specify the value using this method. "},
    { "get_qid", reinterpret_cast<PyCFunction>(Message_getQid), METH_NOARGS,
      "Returns the query id" },
    { "set_qid", reinterpret_cast<PyCFunction>(Message_setQid), METH_VARARGS,
      "Sets the query id. If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised.\n"
      "The argument must be an integer" },
    { "get_rcode", reinterpret_cast<PyCFunction>(Message_getRcode), METH_NOARGS,
      "Returns the message Response code (an Rcode object)" },
    { "set_rcode", reinterpret_cast<PyCFunction>(Message_setRcode), METH_VARARGS,
      "Sets the message Response code (an Rcode object).\n"
      "If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised."},
    { "get_opcode", reinterpret_cast<PyCFunction>(Message_getOpcode), METH_NOARGS,
      "Returns the message opcode (an Opcode object)" },
    { "set_opcode", reinterpret_cast<PyCFunction>(Message_setOpcode), METH_VARARGS,
      "Sets the message opcode (an Opcode object).\n"
      "If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised."},
    { "get_rr_count", reinterpret_cast<PyCFunction>(Message_getRRCount), METH_VARARGS,
      "Returns the number of RRs contained in the given section." },
    { "get_question", reinterpret_cast<PyCFunction>(Message_getQuestion), METH_NOARGS,
      "Returns a list of all Question objects in the message "
      "(should be either 0 or 1)" },
    { "get_section", reinterpret_cast<PyCFunction>(Message_getSection), METH_VARARGS,
      "Returns a list of all RRset objects in the given section of the message\n"
      "The argument must be of type Section" },
    { "add_question", reinterpret_cast<PyCFunction>(Message_addQuestion), METH_VARARGS,
      "Add a Question to the message."
      "If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised."},
    { "add_rrset", reinterpret_cast<PyCFunction>(Message_addRRset), METH_VARARGS,
      "Add an RRset to the given section of the message.\n"
      "The first argument is of type Section\n"
      "The second is of type RRset\n"
      "The third argument is an optional Boolean specifying whether "
      "the RRset is signed"},
    { "clear", reinterpret_cast<PyCFunction>(Message_clear), METH_VARARGS,
      "Clears the message content (if any) and reinitialize the "
      "message in the given mode\n"
      "The argument must be either Message.PARSE or Message.RENDER"},
    { "make_response", reinterpret_cast<PyCFunction>(Message_makeResponse), METH_NOARGS,
      "Prepare for making a response from a request.\n"
      "This will clear the DNS header except those fields that should be kept "
      "for the response, and clear answer and the following sections. "
      "See also dns_message_reply() of BIND9."},
    { "to_text", reinterpret_cast<PyCFunction>(Message_toText), METH_NOARGS,
      "Returns the string representation of the message" },
    { "to_wire", reinterpret_cast<PyCFunction>(Message_toWire), METH_VARARGS,
      "Render the message in wire format.\n"
      "The argument must be a MessageRenderer.\n"
      "If the given message is not in RENDER mode, an "
      "InvalidMessageOperation is raised.\n"
       },
    { "from_wire", reinterpret_cast<PyCFunction>(Message_fromWire), METH_VARARGS,
      "Parses the given wire format to a Message object.\n"
      "The first argument is a Message to parse the data into.\n"
      "The second argument must implement the buffer interface.\n"
      "If the given message is not in PARSE mode, an "
      "InvalidMessageOperation is raised.\n"
      "Raises MessageTooShort, DNSMessageFORMERR or DNSMessageBADVERS "
      " if there is a problem parsing the message." },
    { NULL, NULL, 0, NULL }
};

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Message
// Most of the functions are not actually implemented and NULL here.
static PyTypeObject message_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Message",
    sizeof(s_Message),                  // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Message_destroy,        // tp_dealloc
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
    Message_str,                        // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Message class encapsulates a standard DNS message.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Message_methods,                    // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Message_init,             // tp_init
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
Message_init(s_Message* self, PyObject* args) {
    unsigned int i;
    // The constructor argument can be a string ("IN"), an integer (1),
    // or a sequence of numbers between 0 and 255 (wire code)
    
    if (PyArg_ParseTuple(args, "I", &i)) {
        PyErr_Clear();
        if (i == Message::PARSE) {
            self->message = new Message(Message::PARSE);
            return (0);
        } else if (i == Message::RENDER) {
            self->message = new Message(Message::RENDER);
            return (0);
        } else {
            PyErr_SetString(PyExc_TypeError, "Message mode must be Message.PARSE or Message.RENDER");
            return (-1);
        }
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "no valid type in constructor argument");
    return (-1);
}

static void
Message_destroy(s_Message* self) {
    delete self->message;
    self->message = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Message_getHeaderFlag(s_Message* self, PyObject* args) {
    s_MessageFlag* messageflag;
    if (!PyArg_ParseTuple(args, "O!", &messageflag_type, &messageflag)) {
        return (NULL);
    }
    
    if (self->message->getHeaderFlag(*messageflag->messageflag)) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject*
Message_setHeaderFlag(s_Message* self, PyObject* args) {
    s_MessageFlag* messageflag;
    if (!PyArg_ParseTuple(args, "O!", &messageflag_type, &messageflag)) {
        return (NULL);
    }

    try {
        self->message->setHeaderFlag(*messageflag->messageflag);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_clearHeaderFlag(s_Message* self, PyObject* args) {
    s_MessageFlag* messageflag;
    if (!PyArg_ParseTuple(args, "O!", &messageflag_type, &messageflag)) {
        return (NULL);
    }

    try {
        self->message->clearHeaderFlag(*messageflag->messageflag);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }

    Py_RETURN_NONE;
}

static PyObject*
Message_isDNSSECSupported(s_Message* self) {
    if (self->message->isDNSSECSupported()) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject*
Message_setDNSSECSupported(s_Message* self, PyObject* args) {
    PyObject *b;
    if (!PyArg_ParseTuple(args, "O!", &PyBool_Type, &b)) {
        return (NULL);
    }
    try {
        if (b == Py_True) {
            self->message->setDNSSECSupported(true);
        } else {
            self->message->setDNSSECSupported(false);
        }
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getUDPSize(s_Message* self) {
    return (Py_BuildValue("I", self->message->getUDPSize()));
}

static PyObject*
Message_setUDPSize(s_Message* self, PyObject* args) {
    uint16_t size;
    if (!PyArg_ParseTuple(args, "H", &size)) {
        return (NULL);
    }
    try {
        self->message->setUDPSize(size);
        Py_RETURN_NONE;
    } catch (const InvalidMessageUDPSize& imus) {
        PyErr_SetString(po_InvalidMessageUDPSize, imus.what());
        return (NULL);
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getQid(s_Message* self) {
    return (Py_BuildValue("I", self->message->getQid()));
}

static PyObject*
Message_setQid(s_Message* self, PyObject* args) {
    uint16_t id;
    if (!PyArg_ParseTuple(args, "H", &id)) {
        return (NULL);
    }
    try {
        self->message->setQid(id);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getRcode(s_Message* self) {
    s_Rcode* rcode;

    rcode = static_cast<s_Rcode*>(rcode_type.tp_alloc(&rcode_type, 0));
    if (rcode != NULL) {
        rcode->rcode = new Rcode(self->message->getRcode());
        if (rcode->rcode == NULL)
          {
            Py_DECREF(rcode);
            return (NULL);
          }
    }

    return (rcode);
}

static PyObject*
Message_setRcode(s_Message* self, PyObject* args) {
    s_Rcode* rcode;
    if (!PyArg_ParseTuple(args, "O!", &rcode_type, &rcode)) {
        return (NULL);
    }
    try {
        self->message->setRcode(*rcode->rcode);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getOpcode(s_Message* self) {
    s_Opcode* opcode;

    opcode = static_cast<s_Opcode*>(opcode_type.tp_alloc(&opcode_type, 0));
    if (opcode != NULL) {
        // Note that we do not new and delete for opcodes.
        // all rcodes point to the statics defined in
        // message.cc
        opcode->opcode = &self->message->getOpcode();
        if (opcode->opcode == NULL)
          {
            Py_DECREF(opcode);
            return (NULL);
          }
    }

    return (opcode);
}

static PyObject*
Message_setOpcode(s_Message* self, PyObject* args) {
    s_Opcode* opcode;
    if (!PyArg_ParseTuple(args, "O!", &opcode_type, &opcode)) {
        return (NULL);
    }
    try {
        self->message->setOpcode(*opcode->opcode);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getRRCount(s_Message* self, PyObject* args) {
    s_Section *section;
    if (!PyArg_ParseTuple(args, "O!", &section_type, &section)) {
        return (NULL);
    }
    return (Py_BuildValue("I", self->message->getRRCount(*section->section)));
}

// TODO use direct iterators for these? (or simply lists for now?)
static PyObject*
Message_getQuestion(s_Message* self) {
    PyObject* list = PyList_New(0);
    
    for (QuestionIterator qi = self->message->beginQuestion();
         qi != self->message->endQuestion();
         ++qi) {
        s_Question *question = static_cast<s_Question*>(question_type.tp_alloc(&question_type, 0));
        if (question != NULL) {
            question->question = *qi;
            if (question->question == NULL)
              {
                Py_DECREF(question);
                return (NULL);
              }
        }
        PyList_Append(list, question);
    }
    return (list);
}

static PyObject*
Message_getSection(s_Message* self, PyObject* args) {
    s_Section *section;
    if (!PyArg_ParseTuple(args, "O!", &section_type, &section)) {
        return (NULL);
    }
    PyObject* list = PyList_New(0);
    
    for (RRsetIterator rrsi = self->message->beginSection(*section->section);
         rrsi != self->message->endSection(*section->section);
         ++rrsi) {

        s_RRset *rrset = static_cast<s_RRset*>(rrset_type.tp_alloc(&rrset_type, 0));
        if (rrset != NULL) {
            rrset->rrset = *rrsi;
            if (rrset->rrset == NULL)
              {
                Py_DECREF(rrset);
                Py_DECREF(list);
                return (NULL);
              }
        }
        PyList_Append(list, rrset);
        // PyList_Append increases refcount, so we remove ours since
        // we don't need it anymore
        Py_DECREF(rrset);
    }
    return (list);
}

//static PyObject* Message_beginQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_endQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_beginSection(s_Message* self, PyObject* args);
//static PyObject* Message_endSection(s_Message* self, PyObject* args);
//static PyObject* Message_addQuestion(s_Message* self, PyObject* args);
static PyObject*
Message_addQuestion(s_Message* self, PyObject* args) {
    s_Question *question;

    if (!PyArg_ParseTuple(args, "O!", &question_type, &question)) {
        return (NULL);
    }

    self->message->addQuestion(question->question);
    
    Py_RETURN_NONE;
}

static PyObject*
Message_addRRset(s_Message* self, PyObject* args) {
    PyObject *sign = Py_False;
    s_Section* section;
    s_RRset* rrset;
    if (!PyArg_ParseTuple(args, "O!O!|O!", &section_type, &section,
                                           &rrset_type, &rrset,
                                           &PyBool_Type, &sign)) {
        return (NULL);
    }

    try {
        if (sign == Py_True) {
            self->message->addRRset(*section->section, rrset->rrset, true);
        } else {
            self->message->addRRset(*section->section, rrset->rrset, false);
        }
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_clear(s_Message* self, PyObject* args) {
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
            return (NULL);
        }
    } else {
        return (NULL);
    }
}

static PyObject*
Message_makeResponse(s_Message* self) {
    self->message->makeResponse();
    Py_RETURN_NONE;
}

static PyObject*
Message_toText(s_Message* self) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", self->message->toText().c_str()));
}

static PyObject*
Message_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

static PyObject*
Message_toWire(s_Message* self, PyObject* args) {
    s_MessageRenderer* mr;
    
    if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, (PyObject**) &mr)) {
        try {
            self->message->toWire(*mr->messagerenderer);
            // If we return NULL it is seen as an error, so use this for
            // None returns
            Py_RETURN_NONE;
        } catch (const InvalidMessageOperation& imo) {
            PyErr_Clear();
            PyErr_SetString(po_InvalidMessageOperation, imo.what());
            return (NULL);
        }
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a MessageRenderer");
    return (NULL);
}

static PyObject*
Message_fromWire(s_Message* self, PyObject* args) {
    const char* b;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "y#", &b, &len)) {
        return (NULL);
    }
    
    InputBuffer inbuf(b, len);
    try {
        self->message->fromWire(inbuf);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (const DNSMessageFORMERR& dmfe) {
        PyErr_SetString(po_DNSMessageFORMERR, dmfe.what());
        return (NULL);
    } catch (const DNSMessageBADVERS& dmfe) {
        PyErr_SetString(po_DNSMessageBADVERS, dmfe.what());
        return (NULL);
    } catch (const MessageTooShort& mts) {
        PyErr_SetString(po_MessageTooShort, mts.what());
        return (NULL);
    }
}

// Module Initialization, all statics are initialized here
bool
initModulePart_Message(PyObject* mod) {
    
    // add methods to class
    if (PyType_Ready(&messageflag_type) < 0) {
        return (false);
    }
    Py_INCREF(&messageflag_type);
    PyModule_AddObject(mod, "MessageFlag",
                       reinterpret_cast<PyObject*>(&messageflag_type));

    
    if (PyType_Ready(&opcode_type) < 0) {
        return (false);
    }
    Py_INCREF(&opcode_type);
    PyModule_AddObject(mod, "Opcode",
                       reinterpret_cast<PyObject*>(&opcode_type));

    if (PyType_Ready(&rcode_type) < 0) {
        return (false);
    }
    Py_INCREF(&rcode_type);
    PyModule_AddObject(mod, "Rcode",
                       reinterpret_cast<PyObject*>(&rcode_type));

    if (PyType_Ready(&section_type) < 0) {
        return (false);
    }
    Py_INCREF(&section_type);
    PyModule_AddObject(mod, "Section",
                       reinterpret_cast<PyObject*>(&section_type));

    
    if (PyType_Ready(&message_type) < 0) {
        return (false);
    }
    
    // Class variables
    // These are added to the tp_dict of the type object
    //
    addClassVariable(message_type, "PARSE", Py_BuildValue("I", Message::PARSE));
    addClassVariable(message_type, "RENDER", Py_BuildValue("I", Message::RENDER));
    addClassVariable(message_type, "DEFAULT_MAX_UDPSIZE", Py_BuildValue("I", Message::DEFAULT_MAX_UDPSIZE));

    /* Class-specific exceptions */
    po_MessageTooShort = PyErr_NewException("pydnspp.MessageTooShort", NULL, NULL);
    PyModule_AddObject(mod, "MessageTooShort", po_MessageTooShort);
    po_InvalidMessageSection = PyErr_NewException("pydnspp.InvalidMessageSection", NULL, NULL);
    PyModule_AddObject(mod, "InvalidMessageSection", po_InvalidMessageSection);
    po_InvalidMessageOperation = PyErr_NewException("pydnspp.InvalidMessageOperation", NULL, NULL);
    PyModule_AddObject(mod, "InvalidMessageOperation", po_InvalidMessageOperation);
    po_InvalidMessageUDPSize = PyErr_NewException("pydnspp.InvalidMessageUDPSize", NULL, NULL);
    PyModule_AddObject(mod, "InvalidMessageUDPSize", po_InvalidMessageUDPSize);
    po_DNSMessageBADVERS = PyErr_NewException("pydnspp.DNSMessageBADVERS", NULL, NULL);
    PyModule_AddObject(mod, "DNSMessageBADVERS", po_DNSMessageBADVERS);

    Py_INCREF(&message_type);
    PyModule_AddObject(mod, "Message",
                       reinterpret_cast<PyObject*>(&message_type));


    return (true);
}
