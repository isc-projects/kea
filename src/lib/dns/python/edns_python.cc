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

#include <cassert>

#include <dns/edns.h>

using namespace isc::dns;
using namespace isc::dns::rdata;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

namespace {
//
// EDNS
//

// The s_* Class simply covers one instantiation of the object

class s_EDNS : public PyObject {
public:
    EDNS* edns;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int EDNS_init(s_EDNS* self, PyObject* args);
void EDNS_destroy(s_EDNS* self);

// These are the functions we export
PyObject* EDNS_toText(const s_EDNS* self);
// This is a second version of toText, we need one where the argument
// is a PyObject*, for the str() function in python.
PyObject* EDNS_str(PyObject* self);
PyObject* EDNS_toWire(const s_EDNS* self, PyObject* args);
PyObject* EDNS_getVersion(const s_EDNS* self);
PyObject* EDNS_isDNSSECSupported(const s_EDNS* self);
PyObject* EDNS_setDNSSECSupported(s_EDNS* self, PyObject* args);
PyObject* EDNS_getUDPSize(const s_EDNS* self);
PyObject* EDNS_setUDPSize(s_EDNS* self, PyObject* args);
PyObject* EDNS_createFromRR(const s_EDNS* null_self, PyObject* args);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef EDNS_methods[] = {
    { "to_text", reinterpret_cast<PyCFunction>(EDNS_toText), METH_NOARGS,
      "Returns the string representation" },
    { "to_wire", reinterpret_cast<PyCFunction>(EDNS_toWire), METH_VARARGS,
      "Converts the EDNS object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { "get_version",
      reinterpret_cast<PyCFunction>(EDNS_getVersion), METH_NOARGS,
      "Returns the version of EDNS." },
    { "is_dnssec_supported",
      reinterpret_cast<PyCFunction>(EDNS_isDNSSECSupported), METH_NOARGS,
      "Returns True if the message sender indicates DNSSEC is supported. "
      "If EDNS is included, this corresponds to the value of the DO bit. "
      "Otherwise, DNSSEC is considered not supported." },
    { "set_dnssec_supported",
      reinterpret_cast<PyCFunction>(EDNS_setDNSSECSupported), METH_VARARGS,
      "Specify whether DNSSEC is supported in the message." },
    { "get_udp_size",
      reinterpret_cast<PyCFunction>(EDNS_getUDPSize), METH_NOARGS,
      "Return the maximum buffer size of UDP messages for the sender "
      "of the message." },
    { "set_udp_size",
      reinterpret_cast<PyCFunction>(EDNS_setUDPSize), METH_VARARGS,
      "Specify the maximum buffer size of UDP messages that use this EDNS." },
    { "create_from_rr",
      reinterpret_cast<PyCFunction>(EDNS_createFromRR),
      METH_VARARGS | METH_STATIC,
      "Create a new EDNS object from a set of RR parameters, also providing "
      "the extended RCODE value." },
    { NULL, NULL, 0, NULL }
};

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_EDNS
// Most of the functions are not actually implemented and NULL here.
PyTypeObject edns_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.EDNS",
    sizeof(s_EDNS),                     // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)EDNS_destroy,           // tp_dealloc
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
    EDNS_str,                           // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The EDNS class encapsulates DNS extensions "
    "provided by the EDNSx protocol.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    EDNS_methods,                       // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)EDNS_init,                // tp_init
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

EDNS*
createFromRR(const Name& name, const RRClass& rrclass, const RRType& rrtype,
             const RRTTL& rrttl, const Rdata& rdata, uint8_t& extended_rcode)
{
    try {
        return (createEDNSFromRR(name, rrclass, rrtype, rrttl, rdata,
                                 extended_rcode));
    } catch (const isc::InvalidParameter& ex) {
        PyErr_SetString(po_InvalidParameter, ex.what());
    } catch (const DNSMessageFORMERR& ex) {
        PyErr_SetString(po_DNSMessageFORMERR, ex.what());
    } catch (const DNSMessageBADVERS& ex) {
        PyErr_SetString(po_DNSMessageBADVERS, ex.what());
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
    }

    return (NULL);
}
int
EDNS_init(s_EDNS* self, PyObject* args) {
    uint8_t version = EDNS::SUPPORTED_VERSION;
    const s_Name* name;
    const s_RRClass* rrclass;
    const s_RRType* rrtype;
    const s_RRTTL* rrttl;
    const s_Rdata* rdata;

    if (PyArg_ParseTuple(args, "|b", &version)) {
        try {
            self->edns = new EDNS(version);
        } catch (const isc::InvalidParameter& ex) {
            PyErr_SetString(po_InvalidParameter, ex.what());
            return (-1);
        } catch (...) {
            PyErr_SetString(po_IscException, "Unexpected exception");
            return (-1);
        }
        return (0);
    } else if (PyArg_ParseTuple(args, "O!O!O!O!O!", &name_type, &name,
                                &rrclass_type, &rrclass, &rrtype_type, &rrtype,
                                &rrttl_type, &rrttl, &rdata_type, &rdata)) {
        // We use createFromRR() even if we don't need to know extended_rcode
        // in this context so that we can share the try-catch logic with
        // EDNS_createFromRR() (see below).
        uint8_t extended_rcode;
        self->edns = createFromRR(*name->name, *rrclass->rrclass,
                                  *rrtype->rrtype, *rrttl->rrttl,
                                  *rdata->rdata, extended_rcode);
        return (self->edns != NULL ? 0 : -1);
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError, "Invalid arguments to EDNS constructor");

    return (-1);
}

void
EDNS_destroy(s_EDNS* const self) {
    delete self->edns;
    self->edns = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
EDNS_toText(const s_EDNS* const self) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", self->edns->toText().c_str()));
}

PyObject*
EDNS_str(PyObject* const self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                                const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
EDNS_toWire(const s_EDNS* const self, PyObject* args) {
    PyObject* bytes;
    uint8_t extended_rcode;
    s_MessageRenderer* renderer;

    if (PyArg_ParseTuple(args, "Ob", &bytes, &extended_rcode) &&
        PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;
        
        OutputBuffer buffer(0);
        self->edns->toWire(buffer, extended_rcode);
        PyObject* rd_bytes = PyBytes_FromStringAndSize(
            static_cast<const char*>(buffer.getData()), buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, rd_bytes);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(rd_bytes);
        return (result);
    } else if (PyArg_ParseTuple(args, "O!b", &messagerenderer_type,
                                &renderer, &extended_rcode)) {
        const unsigned int n = self->edns->toWire(*renderer->messagerenderer,
                                                  extended_rcode);

        return (Py_BuildValue("I", n));
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError, "Incorrect arguments for EDNS.to_wire()");
    return (NULL);
}

PyObject*
EDNS_getVersion(const s_EDNS* const self) {
    return (Py_BuildValue("B", self->edns->getVersion()));
}

PyObject*
EDNS_isDNSSECSupported(const s_EDNS* const self) {
    if (self->edns->isDNSSECSupported()) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject*
EDNS_setDNSSECSupported(s_EDNS* self, PyObject* args) {
    const PyObject *b;
    if (!PyArg_ParseTuple(args, "O!", &PyBool_Type, &b)) {
        return (NULL);
    }
    self->edns->setDNSSECSupported(b == Py_True);
    Py_RETURN_NONE;
}

PyObject*
EDNS_getUDPSize(const s_EDNS* const self) {
    return (Py_BuildValue("I", self->edns->getUDPSize()));
}

PyObject*
EDNS_setUDPSize(s_EDNS* self, PyObject* args) {
    unsigned int size;
    if (!PyArg_ParseTuple(args, "I", &size)) {
        return (NULL);
    }
    if (size > 65535) {
        PyErr_SetString(PyExc_OverflowError,
                        "UDP size is not an unsigned 16-bit integer");
        return (NULL);
    }
    self->edns->setUDPSize(size);
    Py_RETURN_NONE;
}

PyObject*
EDNS_createFromRR(const s_EDNS* null_self, PyObject* args) {
    const s_Name* name;
    const s_RRClass* rrclass;
    const s_RRType* rrtype;
    const s_RRTTL* rrttl;
    const s_Rdata* rdata;
    s_EDNS* edns_obj = NULL;

    assert(null_self == NULL);

    if (PyArg_ParseTuple(args, "O!O!O!O!O!", &name_type, &name,
                         &rrclass_type, &rrclass, &rrtype_type, &rrtype,
                         &rrttl_type, &rrttl, &rdata_type, &rdata)) {
        uint8_t extended_rcode;
        edns_obj = PyObject_New(s_EDNS, &edns_type);
        if (edns_obj == NULL) {
            return (NULL);
        }

        edns_obj->edns = createFromRR(*name->name, *rrclass->rrclass,
                                      *rrtype->rrtype, *rrttl->rrttl,
                                      *rdata->rdata, extended_rcode);
        if (edns_obj->edns != NULL) {
            PyObject* extrcode_obj = Py_BuildValue("B", extended_rcode);
            return (Py_BuildValue("OO", edns_obj, extrcode_obj));
        }
        
        Py_DECREF(edns_obj);
        return (NULL);
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "Incorrect arguments for EDNS.create_from_rr()");
    return (NULL);
}

} // end of anonymous namespace
// end of EDNS

// Module Initialization, all statics are initialized here
bool
initModulePart_EDNS(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&edns_type) < 0) {
        return (false);
    }
    Py_INCREF(&edns_type);
    void* p = &edns_type;
    PyModule_AddObject(mod, "EDNS", static_cast<PyObject*>(p));

    addClassVariable(edns_type, "SUPPORTED_VERSION",
                     Py_BuildValue("B", EDNS::SUPPORTED_VERSION));

    return (true);
}
