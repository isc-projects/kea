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

#include <cassert>

#include <dns/edns.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <util/python/pycppwrapper_util.h>

#include "edns_python.h"
#include "name_python.h"
#include "rrclass_python.h"
#include "rrtype_python.h"
#include "rrttl_python.h"
#include "rdata_python.h"
#include "messagerenderer_python.h"
#include "pydnspp_common.h"

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::python;
using namespace isc::util;
using namespace isc::util::python;

namespace {

class s_EDNS : public PyObject {
public:
    EDNS* cppobj;
};

typedef CPPPyObjectContainer<s_EDNS, EDNS> EDNSContainer;

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
PyObject* EDNS_getDNSSECAwareness(const s_EDNS* self);
PyObject* EDNS_setDNSSECAwareness(s_EDNS* self, PyObject* args);
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
    { "get_dnssec_awareness",
      reinterpret_cast<PyCFunction>(EDNS_getDNSSECAwareness), METH_NOARGS,
      "Returns whether the message sender is DNSSEC aware." },
    { "set_dnssec_awareness",
      reinterpret_cast<PyCFunction>(EDNS_setDNSSECAwareness), METH_VARARGS,
      "Specifies whether the sender of the message containing this "
      "EDNS is DNSSEC aware." },
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
    const PyObject* name;
    const PyObject* rrclass;
    const PyObject* rrtype;
    const PyObject* rrttl;
    const PyObject* rdata;

    if (PyArg_ParseTuple(args, "|b", &version)) {
        try {
            self->cppobj = new EDNS(version);
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
        self->cppobj = createFromRR(PyName_ToName(name),
                                    PyRRClass_ToRRClass(rrclass),
                                    PyRRType_ToRRType(rrtype),
                                    PyRRTTL_ToRRTTL(rrttl),
                                    PyRdata_ToRdata(rdata), extended_rcode);
        return (self->cppobj != NULL ? 0 : -1);
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError, "Invalid arguments to EDNS constructor");

    return (-1);
}

void
EDNS_destroy(s_EDNS* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
EDNS_toText(const s_EDNS* const self) {
    // Py_BuildValue makes python objects from native data
    return (Py_BuildValue("s", self->cppobj->toText().c_str()));
}

PyObject*
EDNS_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                                const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
EDNS_toWire(const s_EDNS* const self, PyObject* args) {
    PyObject* bytes;
    uint8_t extended_rcode;
    PyObject* renderer;

    if (PyArg_ParseTuple(args, "Ob", &bytes, &extended_rcode) &&
        PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;

        OutputBuffer buffer(0);
        self->cppobj->toWire(buffer, extended_rcode);
        PyObject* rd_bytes = PyBytes_FromStringAndSize(
            static_cast<const char*>(buffer.getData()), buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, rd_bytes);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(rd_bytes);
        return (result);
    } else if (PyArg_ParseTuple(args, "O!b", &messagerenderer_type,
                                &renderer, &extended_rcode)) {
        const unsigned int n = self->cppobj->toWire(
            PyMessageRenderer_ToMessageRenderer(renderer), extended_rcode);

        return (Py_BuildValue("I", n));
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError, "Incorrect arguments for EDNS.to_wire()");
    return (NULL);
}

PyObject*
EDNS_getVersion(const s_EDNS* const self) {
    return (Py_BuildValue("B", self->cppobj->getVersion()));
}

PyObject*
EDNS_getDNSSECAwareness(const s_EDNS* const self) {
    if (self->cppobj->getDNSSECAwareness()) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject*
EDNS_setDNSSECAwareness(s_EDNS* self, PyObject* args) {
    const PyObject *b;
    if (!PyArg_ParseTuple(args, "O!", &PyBool_Type, &b)) {
        return (NULL);
    }
    self->cppobj->setDNSSECAwareness(b == Py_True);
    Py_RETURN_NONE;
}

PyObject*
EDNS_getUDPSize(const s_EDNS* const self) {
    return (Py_BuildValue("I", self->cppobj->getUDPSize()));
}

PyObject*
EDNS_setUDPSize(s_EDNS* self, PyObject* args) {
    long size;
    if (!PyArg_ParseTuple(args, "l", &size)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "No valid type in set_udp_size argument");
        return (NULL);
    }
    if (size < 0 || size > 0xffff) {
        PyErr_SetString(PyExc_ValueError,
                        "UDP size is not an unsigned 16-bit integer");
        return (NULL);
    }
    self->cppobj->setUDPSize(size);
    Py_RETURN_NONE;
}

PyObject*
EDNS_createFromRR(const s_EDNS* null_self, PyObject* args) {
    const PyObject* name;
    const PyObject* rrclass;
    const PyObject* rrtype;
    const PyObject* rrttl;
    const PyObject* rdata;

    assert(null_self == NULL);

    if (PyArg_ParseTuple(args, "O!O!O!O!O!", &name_type, &name,
                         &rrclass_type, &rrclass, &rrtype_type, &rrtype,
                         &rrttl_type, &rrttl, &rdata_type, &rdata)) {
        uint8_t extended_rcode;
        s_EDNS* edns_obj = PyObject_New(s_EDNS, &edns_type);
        if (edns_obj == NULL) {
            return (NULL);
        }

        edns_obj->cppobj = createFromRR(PyName_ToName(name),
                                        PyRRClass_ToRRClass(rrclass),
                                        PyRRType_ToRRType(rrtype),
                                        PyRRTTL_ToRRTTL(rrttl),
                                        PyRdata_ToRdata(rdata),
                                        extended_rcode);
        if (edns_obj->cppobj != NULL) {
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

namespace isc {
namespace dns {
namespace python {

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_EDNS
// Most of the functions are not actually implemented and NULL here.
PyTypeObject edns_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.EDNS",
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

PyObject*
createEDNSObject(const EDNS& source) {
    EDNSContainer container(PyObject_New(s_EDNS, &edns_type));
    container.set(new EDNS(source));
    return (container.release());
}

bool
PyEDNS_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &edns_type));
}

const EDNS&
PyEDNS_ToEDNS(const PyObject* edns_obj) {
    if (edns_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in EDNS PyObject conversion");
    }
    const s_EDNS* edns = static_cast<const s_EDNS*>(edns_obj);
    return (*edns->cppobj);
}

} // end namespace python
} // end namespace dns
} // end namespace isc
