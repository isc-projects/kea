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

#include <dns/rcode.h>

using namespace isc::dns;

//
// Declaration of the custom exceptions (None for this class)

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

namespace {
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
    s_Rcode() : rcode(NULL), static_code(false) {}
    const Rcode* rcode;
    bool static_code;
};

int Rcode_init(s_Rcode* const self, PyObject* args);
void Rcode_destroy(s_Rcode* const self);

PyObject* Rcode_getCode(const s_Rcode* const self);
PyObject* Rcode_getExtendedCode(const s_Rcode* const self);
PyObject* Rcode_toText(const s_Rcode* const self);
PyObject* Rcode_str(PyObject* self);
PyObject* Rcode_NOERROR(const s_Rcode* self);
PyObject* Rcode_FORMERR(const s_Rcode* self);
PyObject* Rcode_SERVFAIL(const s_Rcode* self);
PyObject* Rcode_NXDOMAIN(const s_Rcode* self);
PyObject* Rcode_NOTIMP(const s_Rcode* self);
PyObject* Rcode_REFUSED(const s_Rcode* self);
PyObject* Rcode_YXDOMAIN(const s_Rcode* self);
PyObject* Rcode_YXRRSET(const s_Rcode* self);
PyObject* Rcode_NXRRSET(const s_Rcode* self);
PyObject* Rcode_NOTAUTH(const s_Rcode* self);
PyObject* Rcode_NOTZONE(const s_Rcode* self);
PyObject* Rcode_RESERVED11(const s_Rcode* self);
PyObject* Rcode_RESERVED12(const s_Rcode* self);
PyObject* Rcode_RESERVED13(const s_Rcode* self);
PyObject* Rcode_RESERVED14(const s_Rcode* self);
PyObject* Rcode_RESERVED15(const s_Rcode* self);
PyObject* Rcode_BADVERS(const s_Rcode* self);
PyObject* Rcode_richcmp(const s_Rcode* const self,
                         const s_Rcode* const other, int op);

PyMethodDef Rcode_methods[] = {
    { "get_code", reinterpret_cast<PyCFunction>(Rcode_getCode), METH_NOARGS,
      "Returns the code value" },
    { "get_extended_code",
      reinterpret_cast<PyCFunction>(Rcode_getExtendedCode), METH_NOARGS,
      "Returns the upper 8-bit part of the extended code value" },
    { "to_text", reinterpret_cast<PyCFunction>(Rcode_toText), METH_NOARGS,
      "Returns the text representation" },
    { "NOERROR", reinterpret_cast<PyCFunction>(Rcode_NOERROR),
      METH_NOARGS | METH_STATIC, "Creates a NOERROR Rcode" },
    { "FORMERR", reinterpret_cast<PyCFunction>(Rcode_FORMERR),
      METH_NOARGS | METH_STATIC, "Creates a FORMERR Rcode" },
    { "SERVFAIL", reinterpret_cast<PyCFunction>(Rcode_SERVFAIL),
      METH_NOARGS | METH_STATIC, "Creates a SERVFAIL Rcode" },
    { "NXDOMAIN", reinterpret_cast<PyCFunction>(Rcode_NXDOMAIN),
      METH_NOARGS | METH_STATIC, "Creates a NXDOMAIN Rcode" },
    { "NOTIMP", reinterpret_cast<PyCFunction>(Rcode_NOTIMP),
      METH_NOARGS | METH_STATIC, "Creates a NOTIMP Rcode" },
    { "REFUSED", reinterpret_cast<PyCFunction>(Rcode_REFUSED),
      METH_NOARGS | METH_STATIC, "Creates a REFUSED Rcode" },
    { "YXDOMAIN", reinterpret_cast<PyCFunction>(Rcode_YXDOMAIN),
      METH_NOARGS | METH_STATIC, "Creates a YXDOMAIN Rcode" },
    { "YXRRSET", reinterpret_cast<PyCFunction>(Rcode_YXRRSET),
      METH_NOARGS | METH_STATIC, "Creates a YYRRSET Rcode" },
    { "NXRRSET", reinterpret_cast<PyCFunction>(Rcode_NXRRSET),
      METH_NOARGS | METH_STATIC, "Creates a NXRRSET Rcode" },
    { "NOTAUTH", reinterpret_cast<PyCFunction>(Rcode_NOTAUTH),
      METH_NOARGS | METH_STATIC, "Creates a NOTAUTH Rcode" },
    { "NOTZONE", reinterpret_cast<PyCFunction>(Rcode_NOTZONE),
      METH_NOARGS | METH_STATIC, "Creates a NOTZONE Rcode" },
    { "RESERVED11", reinterpret_cast<PyCFunction>(Rcode_RESERVED11),
      METH_NOARGS | METH_STATIC, "Creates a RESERVED11 Rcode" },
    { "RESERVED12", reinterpret_cast<PyCFunction>(Rcode_RESERVED12),
      METH_NOARGS | METH_STATIC, "Creates a RESERVED12 Rcode" },
    { "RESERVED13", reinterpret_cast<PyCFunction>(Rcode_RESERVED13),
      METH_NOARGS | METH_STATIC, "Creates a RESERVED13 Rcode" },
    { "RESERVED14", reinterpret_cast<PyCFunction>(Rcode_RESERVED14),
      METH_NOARGS | METH_STATIC, "Creates a RESERVED14 Rcode" },
    { "RESERVED15", reinterpret_cast<PyCFunction>(Rcode_RESERVED15),
      METH_NOARGS | METH_STATIC, "Creates a RESERVED15 Rcode" },
    { "BADVERS", reinterpret_cast<PyCFunction>(Rcode_BADVERS),
      METH_NOARGS | METH_STATIC, "Creates a BADVERS Rcode" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject rcode_type = {
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

int
Rcode_init(s_Rcode* const self, PyObject* args) {
    int code = 0;
    int ext_code = 0;

    if (PyArg_ParseTuple(args, "i", &code)) {
        if (code < 0 || code > 0xffff) {
            PyErr_SetString(PyExc_OverflowError, "Rcode out of range");
            return (-1);
        }
        ext_code = -1;
    } else if (PyArg_ParseTuple(args, "ii", &code, &ext_code)) {
        if (code < 0 || code > 0xff || ext_code < 0 || ext_code > 0xff) {
            PyErr_SetString(PyExc_OverflowError, "Rcode out of range");
            return (-1);
        }
    } else {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "Invalid arguments to Rcode constructor");
        return (-1);
    }
    try {
        if (ext_code == -1) {
            self->rcode = new Rcode(code);
        } else {
            self->rcode = new Rcode(code, ext_code);
        }
        self->static_code = false;
    } catch (const isc::OutOfRange& ex) {
            PyErr_SetString(PyExc_OverflowError, ex.what());
            return (-1);
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
        return (-1);
    }
    return (0);
}

void
Rcode_destroy(s_Rcode* const self) {
    // Depending on whether we created the rcode or are referring
    // to a global one, we do or do not delete self->rcode here
    if (!self->static_code) {
        delete self->rcode;
    }
    self->rcode = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
Rcode_getCode(const s_Rcode* const self) {
    return (Py_BuildValue("I", self->rcode->getCode()));
}

PyObject*
Rcode_getExtendedCode(const s_Rcode* const self) {
    return (Py_BuildValue("I", self->rcode->getExtendedCode()));
}

PyObject*
Rcode_toText(const s_Rcode* const self) {
    return (Py_BuildValue("s", self->rcode->toText().c_str()));
}

PyObject*
Rcode_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self, const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
Rcode_createStatic(const Rcode& rcode) {
    s_Rcode* ret = PyObject_New(s_Rcode, &rcode_type);
    if (ret != NULL) {
        ret->rcode = &rcode;
        ret->static_code = true;
    }
    return (ret);
}

PyObject*
Rcode_NOERROR(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::NOERROR()));
}

PyObject*
Rcode_FORMERR(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::FORMERR()));
}

PyObject*
Rcode_SERVFAIL(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::SERVFAIL()));
}

PyObject*
Rcode_NXDOMAIN(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::NXDOMAIN()));
}

PyObject*
Rcode_NOTIMP(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::NOTIMP()));
}

PyObject*
Rcode_REFUSED(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::REFUSED()));
}

PyObject*
Rcode_YXDOMAIN(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::YXDOMAIN()));
}

PyObject*
Rcode_YXRRSET(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::YXRRSET()));
}

PyObject*
Rcode_NXRRSET(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::NXRRSET()));
}

PyObject*
Rcode_NOTAUTH(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::NOTAUTH()));
}

PyObject*
Rcode_NOTZONE(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::NOTZONE()));
}

PyObject*
Rcode_RESERVED11(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::RESERVED11()));
}

PyObject*
Rcode_RESERVED12(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::RESERVED12()));
}

PyObject*
Rcode_RESERVED13(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::RESERVED13()));
}

PyObject*
Rcode_RESERVED14(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::RESERVED14()));
}

PyObject*
Rcode_RESERVED15(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::RESERVED15()));
}

PyObject*
Rcode_BADVERS(const s_Rcode*) {
    return (Rcode_createStatic(Rcode::BADVERS()));
}

PyObject* 
Rcode_richcmp(const s_Rcode* const self, const s_Rcode* const other,
              const int op)
{
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
    case Py_LE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return (NULL);
    case Py_EQ:
        c = (*self->rcode == *other->rcode);
        break;
    case Py_NE:
        c = (*self->rcode != *other->rcode);
        break;
    case Py_GT:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return (NULL);
    case Py_GE:
        PyErr_SetString(PyExc_TypeError, "Unorderable type; Rcode");
        return (NULL);
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

// Module Initialization, all statics are initialized here
bool
initModulePart_Rcode(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&rcode_type) < 0) {
        return (false);
    }
    Py_INCREF(&rcode_type);
    void* p = &rcode_type;
    if (PyModule_AddObject(mod, "Rcode", static_cast<PyObject*>(p)) != 0) {
        Py_DECREF(&rcode_type);
        return (false);
    }

    addClassVariable(rcode_type, "NOERROR_CODE",
                     Py_BuildValue("h", Rcode::NOERROR_CODE));
    addClassVariable(rcode_type, "FORMERR_CODE",
                     Py_BuildValue("h", Rcode::FORMERR_CODE));
    addClassVariable(rcode_type, "SERVFAIL_CODE",
                     Py_BuildValue("h", Rcode::SERVFAIL_CODE));
    addClassVariable(rcode_type, "NXDOMAIN_CODE",
                     Py_BuildValue("h", Rcode::NXDOMAIN_CODE));
    addClassVariable(rcode_type, "NOTIMP_CODE",
                     Py_BuildValue("h", Rcode::NOTIMP_CODE));
    addClassVariable(rcode_type, "REFUSED_CODE",
                     Py_BuildValue("h", Rcode::REFUSED_CODE));
    addClassVariable(rcode_type, "YXDOMAIN_CODE",
                     Py_BuildValue("h", Rcode::YXDOMAIN_CODE));
    addClassVariable(rcode_type, "YXRRSET_CODE",
                     Py_BuildValue("h", Rcode::YXRRSET_CODE));
    addClassVariable(rcode_type, "NXRRSET_CODE",
                     Py_BuildValue("h", Rcode::NXRRSET_CODE));
    addClassVariable(rcode_type, "NOTAUTH_CODE",
                     Py_BuildValue("h", Rcode::NOTAUTH_CODE));
    addClassVariable(rcode_type, "NOTZONE_CODE",
                     Py_BuildValue("h", Rcode::NOTZONE_CODE));
    addClassVariable(rcode_type, "RESERVED11_CODE",
                     Py_BuildValue("h", Rcode::RESERVED11_CODE));
    addClassVariable(rcode_type, "RESERVED12_CODE",
                     Py_BuildValue("h", Rcode::RESERVED12_CODE));
    addClassVariable(rcode_type, "RESERVED13_CODE",
                     Py_BuildValue("h", Rcode::RESERVED13_CODE));
    addClassVariable(rcode_type, "RESERVED14_CODE",
                     Py_BuildValue("h", Rcode::RESERVED14_CODE));
    addClassVariable(rcode_type, "RESERVED15_CODE",
                     Py_BuildValue("h", Rcode::RESERVED15_CODE));
    addClassVariable(rcode_type, "BADVERS_CODE",
                     Py_BuildValue("h", Rcode::BADVERS_CODE));

    return (true);
}
} // end of unnamed namespace
