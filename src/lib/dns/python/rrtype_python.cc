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

#include <dns/rrtype.h>
using namespace isc::dns;

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the initModulePart
// function at the end of this file
//
static PyObject* po_InvalidRRType;
static PyObject* po_IncompleteRRType;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// RRType
//

// The s_* Class simply covers one instantiation of the object
class s_RRType : public PyObject {
public:
    const RRType* rrtype;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
static int RRType_init(s_RRType* self, PyObject* args);
static void RRType_destroy(s_RRType* self);

// These are the functions we export
static PyObject*
RRType_toText(s_RRType* self);
// This is a second version of toText, we need one where the argument
// is a PyObject*, for the str() function in python.
static PyObject*
RRType_str(PyObject* self);
static PyObject*
RRType_toWire(s_RRType* self, PyObject* args);
static PyObject*
RRType_getCode(s_RRType* self);
static PyObject*
RRType_richcmp(s_RRType* self, s_RRType* other, int op);
static PyObject*
RRType_NSEC3PARAM(s_RRType *self);
static PyObject*
RRType_DNAME(s_RRType *self);
static PyObject*
RRType_PTR(s_RRType *self);
static PyObject*
RRType_MX(s_RRType *self);
static PyObject*
RRType_DNSKEY(s_RRType *self);
static PyObject*
RRType_TXT(s_RRType *self);
static PyObject*
RRType_RRSIG(s_RRType *self);
static PyObject*
RRType_NSEC(s_RRType *self);
static PyObject*
RRType_AAAA(s_RRType *self);
static PyObject*
RRType_DS(s_RRType *self);
static PyObject*
RRType_OPT(s_RRType *self);
static PyObject*
RRType_A(s_RRType *self);
static PyObject*
RRType_NS(s_RRType *self);
static PyObject*
RRType_CNAME(s_RRType *self);
static PyObject*
RRType_SOA(s_RRType *self);
static PyObject*
RRType_NSEC3(s_RRType *self);
static PyObject*
RRType_IXFR(s_RRType *self);
static PyObject*
RRType_AXFR(s_RRType *self);
static PyObject*
RRType_ANY(s_RRType *self);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
static PyMethodDef RRType_methods[] = {
    { "to_text", reinterpret_cast<PyCFunction>(RRType_toText), METH_NOARGS,
      "Returns the string representation" },
    { "to_wire", reinterpret_cast<PyCFunction>(RRType_toWire), METH_VARARGS,
      "Converts the RRType object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { "get_code", reinterpret_cast<PyCFunction>(RRType_getCode), METH_NOARGS,
      "Returns the type code as an integer" },
    { "NSEC3PARAM", reinterpret_cast<PyCFunction>(RRType_NSEC3PARAM), METH_NOARGS | METH_STATIC, "Creates an NSEC3PARAM RRType" },
    { "DNAME", reinterpret_cast<PyCFunction>(RRType_DNAME), METH_NOARGS | METH_STATIC, "Creates a DNAME RRType" },
    { "PTR", reinterpret_cast<PyCFunction>(RRType_PTR), METH_NOARGS | METH_STATIC, "Creates a PTR RRType" },
    { "MX", reinterpret_cast<PyCFunction>(RRType_MX), METH_NOARGS | METH_STATIC, "Creates an MX RRType" },
    { "DNSKEY", reinterpret_cast<PyCFunction>(RRType_DNSKEY), METH_NOARGS | METH_STATIC, "Creates a DNSKEY RRType" },
    { "TXT", reinterpret_cast<PyCFunction>(RRType_TXT), METH_NOARGS | METH_STATIC, "Creates a TXT RRType" },
    { "RRSIG", reinterpret_cast<PyCFunction>(RRType_RRSIG), METH_NOARGS | METH_STATIC, "Creates a RRSIG RRType" },
    { "NSEC", reinterpret_cast<PyCFunction>(RRType_NSEC), METH_NOARGS | METH_STATIC, "Creates a NSEC RRType" },
    { "AAAA", reinterpret_cast<PyCFunction>(RRType_AAAA), METH_NOARGS | METH_STATIC, "Creates an AAAA RRType" },
    { "DS", reinterpret_cast<PyCFunction>(RRType_DS), METH_NOARGS | METH_STATIC, "Creates a DS RRType" },
    { "OPT", reinterpret_cast<PyCFunction>(RRType_OPT), METH_NOARGS | METH_STATIC, "Creates an OPT RRType" },
    { "A", reinterpret_cast<PyCFunction>(RRType_A), METH_NOARGS | METH_STATIC, "Creates an A RRType" },
    { "NS", reinterpret_cast<PyCFunction>(RRType_NS), METH_NOARGS | METH_STATIC, "Creates an NS RRType" },
    { "CNAME", reinterpret_cast<PyCFunction>(RRType_CNAME), METH_NOARGS | METH_STATIC, "Creates a CNAME RRType" },
    { "SOA", reinterpret_cast<PyCFunction>(RRType_SOA), METH_NOARGS | METH_STATIC, "Creates a SOA RRType" },
    { "NSEC3", reinterpret_cast<PyCFunction>(RRType_NSEC3), METH_NOARGS | METH_STATIC, "Creates an NSEC3 RRType" },
    { "IXFR", reinterpret_cast<PyCFunction>(RRType_IXFR), METH_NOARGS | METH_STATIC, "Creates an IXFR RRType" },
    { "AXFR", reinterpret_cast<PyCFunction>(RRType_AXFR), METH_NOARGS | METH_STATIC, "Creates an AXFR RRType" },
    { "ANY", reinterpret_cast<PyCFunction>(RRType_ANY), METH_NOARGS | METH_STATIC, "Creates an ANY RRType" },
    { NULL, NULL, 0, NULL }
};

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_RRType
// Most of the functions are not actually implemented and NULL here.
static PyTypeObject rrtype_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.RRType",
    sizeof(s_RRType),                   // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)RRType_destroy,         // tp_dealloc
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
    RRType_str,                         // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The RRType class encapsulates DNS resource record types.\n\n"
    "This class manages the 16-bit integer type codes in quite a straightforward "
    "way. The only non trivial task is to handle textual representations of "
    "RR types, such as \"A\", \"AAAA\", or \"TYPE65534\".",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)RRType_richcmp,        // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    RRType_methods,                     // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)RRType_init,              // tp_init
    NULL,                               // tp_alloc
    PyType_GenericNew,                  // tp_new
    NULL,                               // tp_free
    NULL,                               // tp_is_gc
    NULL,                               // tp_bases
    NULL,                               // tp_mro
    NULL,                               // tp_cache
    NULL,                               // tp_subclasses
    NULL,                               // tp_weaklist
    // Note: not sure if the following are correct.  Added them just to
    // make the compiler happy.
    NULL,                               // tp_del
    0                                   // tp_version_tag
};

static int
RRType_init(s_RRType* self, PyObject* args) {
    const char* s;
    unsigned int i;
    PyObject* bytes = NULL;
    // The constructor argument can be a string ("IN"), an integer (1),
    // or a sequence of numbers between 0 and 255 (wire code)

    // Note that PyArg_ParseType can set PyError, and we need to clear
    // that if we try several like here. Otherwise the *next* python
    // call will suddenly appear to throw an exception.
    // (the way to do exceptions is to set PyErr and return -1)
    try {
        if (PyArg_ParseTuple(args, "s", &s)) {
            self->rrtype = new RRType(s);
            return 0;
        } else if (PyArg_ParseTuple(args, "I", &i)) {
            PyErr_Clear();
            if (i > 65535) {
                PyErr_SetString(po_InvalidRRType, "Class number too high");
                return -1;
            }
            self->rrtype = new RRType(i);
            return 0;
        } else if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
            Py_ssize_t size = PySequence_Size(bytes);
            uint8_t data[size];
            int result = readDataFromSequence(data, size, bytes);
            if (result != 0) {
                return result;
            }
            InputBuffer ib(data, size);
            self->rrtype = new RRType(ib);
            PyErr_Clear();
            return 0;
        }
    } catch (IncompleteRRType icc) {
        // Ok so one of our functions has thrown a C++ exception.
        // We need to translate that to a Python Exception
        // First clear any existing error that was set
        PyErr_Clear();
        // Now set our own exception
        PyErr_SetString(po_IncompleteRRType, icc.what());
        // And return negative
        return -1;
    } catch (InvalidRRType ic) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidRRType, ic.what());
        return -1;
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "no valid type in constructor argument");
    return -1;
}

static void
RRType_destroy(s_RRType* self) {
    if (self->rrtype != NULL)
        delete self->rrtype;
    self->rrtype = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
RRType_toText(s_RRType* self) {
    // Py_BuildValue makes python objects from native data
    return Py_BuildValue("s", self->rrtype->toText().c_str());
}

static PyObject*
RRType_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return PyObject_CallMethod(self, const_cast<char*>("to_text"),
                                     const_cast<char*>(""));
}

static PyObject*
RRType_toWire(s_RRType* self, PyObject* args) {
    PyObject* bytes;
    s_MessageRenderer* mr;
    
    if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;
        
        OutputBuffer buffer(2);
        self->rrtype->toWire(buffer);
        PyObject* n = PyBytes_FromStringAndSize((const char*) buffer.getData(), buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, n);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(n);
        return result;
    } else if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, (PyObject**) &mr)) {
        self->rrtype->toWire(*mr->messagerenderer);
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
RRType_getCode(s_RRType* self) {
    return Py_BuildValue("I", self->rrtype->getCode());
}

static PyObject* 
RRType_richcmp(s_RRType* self, s_RRType* other, int op) {
    bool c;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    switch (op) {
    case Py_LT:
        c = *self->rrtype < *other->rrtype;
        break;
    case Py_LE:
        c = *self->rrtype < *other->rrtype ||
            *self->rrtype == *other->rrtype;
        break;
    case Py_EQ:
        c = *self->rrtype == *other->rrtype;
        break;
    case Py_NE:
        c = *self->rrtype != *other->rrtype;
        break;
    case Py_GT:
        c = *other->rrtype < *self->rrtype;
        break;
    case Py_GE:
        c = *other->rrtype < *self->rrtype ||
            *self->rrtype == *other->rrtype;
        break;
    default:
        assert(0);              // XXX: should trigger an exception
    }
    if (c)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static PyObject*
RRType_NSEC3PARAM(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::NSEC3PARAM());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_DNAME(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::DNAME());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_PTR(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::PTR());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_MX(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::MX());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_DNSKEY(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::DNSKEY());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_TXT(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::TXT());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_RRSIG(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::RRSIG());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_NSEC(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::NSEC());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_AAAA(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::AAAA());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_DS(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::DS());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_OPT(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::OPT());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_A(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::A());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_NS(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::NS());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_CNAME(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::CNAME());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_SOA(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::SOA());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_NSEC3(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::NSEC3());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_IXFR(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::IXFR());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_AXFR(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::AXFR());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}

static PyObject*
RRType_ANY(s_RRType *self UNUSED_PARAM) {
    s_RRType* ret = PyObject_New(s_RRType, &rrtype_type);
    if (ret != NULL) {
        ret->rrtype = new RRType(RRType::ANY());
        if (ret->rrtype == NULL) {
            Py_DECREF(ret);
            return NULL;
        }
    }
    return static_cast<PyObject*>(ret);
}


// end of RRType


// Module Initialization, all statics are initialized here
bool
initModulePart_RRType(PyObject* mod) {
    // Add the exceptions to the module
    po_InvalidRRType = PyErr_NewException("libdns_python.InvalidRRType", NULL, NULL);
    PyModule_AddObject(mod, "InvalidRRType", po_InvalidRRType);
    po_IncompleteRRType = PyErr_NewException("libdns_python.IncompleteRRType", NULL, NULL);
    PyModule_AddObject(mod, "IncompleteRRType", po_IncompleteRRType);

    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&rrtype_type) < 0) {
        return false;
    }
    Py_INCREF(&rrtype_type);
    PyModule_AddObject(mod, "RRType",
                       reinterpret_cast<PyObject*>(&rrtype_type));
    
    return true;
}
