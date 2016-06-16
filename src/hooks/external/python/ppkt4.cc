// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <hooks/external/python/poption.h>
#include <hooks/external/python/ppkt4.h>

#include <iostream>

using namespace std;
using namespace isc::dhcp;
using namespace isc::python;

// Constructor
py_pkt4::py_pkt4() {}

namespace { // anonymous namespace

// tp_init
int
pkt4_init(PyObject*, PyObject*, PyObject*) {
    PyErr_SetString(PyExc_SystemError,
                    "pkt4 cannot be directly constructed");
    return (-1);
}

// tp_dealloc
void
pkt4_dealloc(PyObject* obj) {
    // This is a critical code to avoid memory leaks
    cout << "pkt4_dealloc called\n";
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    self->object.reset();
    Py_TYPE(self)->tp_free(self);
}

// tp_str
PyObject*
pkt4_str(PyObject* obj) {
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    return (PyUnicode_FromString(self->object->toText().c_str()));
}

// addOption(const OptionPtr opt) method
PyObject*
addOption(PyObject* obj, PyObject* args) {
    PyObject* s = NULL;

    if (!PyArg_ParseTuple(args, "O!", &option_type, &s)) {
        return (NULL);
    }
    py_option* const sub = static_cast<py_option*>(s);
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    self->object->addOption(sub->object);
    Py_RETURN_NONE;
}

// delOption(uint16_t type) method
PyObject*
delOption(PyObject* obj, PyObject* args) {
    unsigned short t;

    if (!PyArg_ParseTuple(args, "H", &t)) {
        return (NULL);
    }
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    bool ret = self->object->delOption(t);
    return (PyBool_FromLong(ret ? 1l : 0l));
}

// len() method
PyObject*
len(PyObject* obj) {
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    return (PyLong_FromLong(static_cast<long>(self->object->len())));
}

// getType() method
PyObject*
getType(PyObject* obj) {
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    return (PyLong_FromLong(static_cast<long>(self->object->getType())));
}

// setType(uint8_t type) method
PyObject*
setType(PyObject* obj, PyObject* args) {
    unsigned char t;

    if (!PyArg_ParseTuple(args, "b", &t)) {
        return (NULL);
    }
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    self->object->setType(t);
    Py_RETURN_NONE;
}

// setTransid(uint32_t transid) method
PyObject*
setTransid(PyObject* obj, PyObject* args) {
    unsigned int t;

    if (!PyArg_ParseTuple(args, "I", &t)) {
        return (NULL);
    }
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    self->object->setTransid(static_cast<uint32_t>(t));
    Py_RETURN_NONE;
}

// getTransid() method
PyObject*
getTransid(PyObject* obj) {
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    uint32_t transid = self->object->getTransid();
    return (PyLong_FromUnsignedLong(static_cast<unsigned long>(transid)));
}

// inClass(const isc::dhcp::ClientClass& client_class) method
PyObject*
inClass(PyObject* obj, PyObject* args) {
    const char* cc = NULL;

    if (!PyArg_ParseTuple(args, "s", &cc)) {
        return (NULL);
    }
    const ClientClass& client_class(cc);

    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    bool ret = self->object->inClass(client_class);
    return (PyBool_FromLong(ret ? 1l : 0l));
}

// addClass(const isc::dhcp::ClientClass& client_class) method
PyObject*
addClass(PyObject* obj, PyObject* args) {
    const char* cc = NULL;

    if (!PyArg_ParseTuple(args, "s", &cc)) {
        return (NULL);
    }
    const ClientClass& client_class(cc);

    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    self->object->addClass(client_class);
    Py_RETURN_NONE;
}

// TODO: getClasses() method

// getOption(uint16_t type) method
PyObject*
getOption(PyObject* obj, PyObject* args) {
    unsigned short t;

    if (!PyArg_ParseTuple(args, "H", &t)) {
        return (NULL);
    }
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    OptionPtr sub = self->object->getOption(t);
    if (sub) {
        PyObject* ret = option_type.tp_alloc(&option_type, 0);
        if (ret) {
            (static_cast<py_option*>(ret))->object = sub;
        }
        return (ret);
    }
    Py_RETURN_NONE;
}

// TODO: getTimestamp() method

// TODO: set/getLocal/RemoteAddr/Port methods

// setIndex(uint32_t ifindex) method
PyObject*
setIndex(PyObject* obj, PyObject* args) {
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i)) {
        return (NULL);
    }
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    self->object->setIndex(static_cast<uint32_t>(i));
    Py_RETURN_NONE;
}

// getIndex() method
PyObject*
getIndex(PyObject* obj) {
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    uint32_t ifindex = self->object->getIndex();
    return (PyLong_FromUnsignedLong(static_cast<unsigned long>(ifindex)));
}

// getIface() method
PyObject*
getIface(PyObject* obj) {
    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    return (Py_BuildValue("s", self->object->getIface().c_str()));
}

// setIface(const std::string& iface) method
PyObject*
setIface(PyObject* obj, PyObject* args) {
    const char* ifn = NULL;

    if (!PyArg_ParseTuple(args, "s", &ifn)) {
        return (NULL);
    }
    const string iface(ifn);

    py_pkt4* const self = static_cast<py_pkt4*>(obj);
    self->object->setIface(iface);
    Py_RETURN_NONE;
}

// Method table
PyMethodDef pkt4_method[] = {
    { "addOption", addOption, METH_VARARGS,
      "adds an option to this packet" },
    { "delOption", delOption, METH_VARARGS,
      "attempts to delete first suboption of requested type" },
    { "len", (PyCFunction)len, METH_NOARGS,
      "returns packet size in binary format" },
    { "getType", (PyCFunction)getType, METH_NOARGS,
      "returns message type" },
    { "setType", setType, METH_VARARGS,
      "sets message type" },
    { "setTransid", setTransid, METH_VARARGS,
      "sets transaction-id value" },
    { "getTransid", (PyCFunction)getTransid, METH_NOARGS,
      "returns value of transaction-id field" },
    { "inClass", inClass, METH_VARARGS,
      "checks whether a packet belongs to a given class" },
    { "addClass", addClass, METH_VARARGS,
      "adds packet to a specified class" },
    { "getOption", getOption, METH_VARARGS,
      "returns the first option of specified type" },
    { "setIndex", setIndex, METH_VARARGS,
      "sets interface index" },
    { "getIndex", (PyCFunction)getIndex, METH_NOARGS,
      "returns interface index" },
    { "getIface", (PyCFunction)getIface, METH_NOARGS,
      "return interface name" },
    { "setIface", setIface, METH_VARARGS,
      "sets interface name" },
    { NULL, NULL, 0, NULL }
};

} // end of anonymous namespace

namespace isc {
namespace python {

// Python pkt4 type definition
PyTypeObject pkt4_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "kea-pkt4",                         // tp_name
    sizeof(py_pkt4),                    // tp_basicsize
    0,                                  // tp_itemsize
    pkt4_dealloc,                       // tp_dealloc
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
    pkt4_str,                           // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "kea pkt4",                         // tp_doc
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    pkt4_method,                        // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    pkt4_init,                          // tp_init
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
    0,                                  // tp_version_tag
    NULL                                // tp_finalize
};

bool
initmod_pkt4(PyObject* mod) {
    // Initialize the description object
    if (PyType_Ready(&pkt4_type) < 0) {
        return (false);
    }
    // Add it to the module
    void* p = &pkt4_type;
    if (PyModule_AddObject(mod, "Pkt4", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&pkt4_type);

    return (true);
}

} // namespace python
} // namespace isc
