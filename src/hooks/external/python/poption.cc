// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <hooks/external/python/poption.h>

#include <iostream>

using namespace std;
using namespace isc::dhcp;
using namespace isc::python;

// Constructor
py_option::py_option() {}

namespace { // anonymous namespace

// tp_init
int
option_init(PyObject* obj, PyObject* args, PyObject*) {
    unsigned char u;
    unsigned short int t;
    PyBytesObject* d = NULL;

    if (!PyArg_ParseTuple(args, "bHS", &u, &t, &d)) {
        return (-1);
    }
    Option::Universe universe;
    switch (u) {
    case 4:
        universe = Option::V4;
        if (t > 255) {
            PyErr_Format(PyExc_ValueError,
                         "out of range type for DHCPv4: %u",
                         static_cast<unsigned>(t));
            return (-1);
        }
        break;
    case 6:
        universe = Option::V6;
        break;
    default:
        PyErr_Format(PyExc_ValueError,
                     "universe must be 4 or 6 (not %u)",
                     static_cast<unsigned>(u));
        return (-1);
    }

    OptionBuffer data;
    data.resize(PyBytes_GET_SIZE(d));
    memmove(&data[0], PyBytes_AS_STRING(d), data.size());

    py_option* const self = static_cast<py_option*>(obj);
    self->object.reset(new Option(universe, t, data));

    return (0);
}

// tp_dealloc
void
option_dealloc(PyObject* obj) {
    // This is a critical code to avoid memory leaks
    cout << "option_dealloc called\n";
    py_option* const self = static_cast<py_option*>(obj);
    self->object.reset();
    Py_TYPE(self)->tp_free(self);
}

// tp_str
PyObject*
option_str(PyObject* obj) {
    py_option* const self = static_cast<py_option*>(obj);
    return (PyUnicode_FromString(self->object->toText(0).c_str()));
}

// getUniverse() method
PyObject*
getUniverse(PyObject* obj) {
    py_option* const self = static_cast<py_option*>(obj);
    switch (self->object->getUniverse()) {
    case Option::V4:
        return (PyLong_FromLong(4l));
    case Option::V6:
        return (PyLong_FromLong(6l));
    default:
        PyErr_SetString(PyExc_SystemError, "getUniverse");
        return (NULL);
    }
}

// toBinary(bool include_header = false) method
PyObject*
toBinary(PyObject* obj, PyObject* args) {
    int ih = 0;

    if (!PyArg_ParseTuple(args, "|p", &ih)) {
        return (NULL);
    }

    py_option* const self = static_cast<py_option*>(obj);
    vector<uint8_t> bin = self->object->toBinary(ih != 0);
    return (PyBytes_FromStringAndSize(reinterpret_cast<char*>(&bin[0]),
                                      static_cast<Py_ssize_t>(bin.size())));
}

// getType() method
PyObject*
getType(PyObject* obj) {
    py_option* const self = static_cast<py_option*>(obj);
    return (PyLong_FromLong(static_cast<long>(self->object->getType())));
}

// len() method
PyObject*
len(PyObject* obj) {
    py_option* const self = static_cast<py_option*>(obj);
    return (PyLong_FromLong(static_cast<long>(self->object->len())));
}

// getHeaderLen() method
PyObject*
getHeaderLen(PyObject* obj) {
    py_option* const self = static_cast<py_option*>(obj);
    return (PyLong_FromLong(static_cast<long>(self->object->getHeaderLen())));
}

// getData() method
PyObject*
getData(PyObject* obj) {
    py_option* const self = static_cast<py_option*>(obj);
    const OptionBuffer& data = self->object->getData();
    return (PyBytes_FromStringAndSize(reinterpret_cast<const char*>(&data[0]),
                                      static_cast<Py_ssize_t>(data.size())));
}

// addOption(OptionPtr opt) method
PyObject*
addOption(PyObject* obj, PyObject* args) {
    PyObject* s = NULL;

    if (!PyArg_ParseTuple(args, "O!", &option_type, &s)) {
        return (NULL);
    }
    py_option* const sub = static_cast<py_option*>(s);
    py_option* const self = static_cast<py_option*>(obj);
    self->object->addOption(sub->object);
    Py_RETURN_NONE;
}

// getOption(uint16_t type) method
PyObject*
getOption(PyObject* obj, PyObject* args) {
    unsigned short t;

    if (!PyArg_ParseTuple(args, "H", &t)) {
        return (NULL);
    }
    py_option* const self = static_cast<py_option*>(obj);
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

// TODO: getOptions() method

// delOption(uint16_t type) method
PyObject*
delOption(PyObject* obj, PyObject* args) {
    unsigned short t;

    if (!PyArg_ParseTuple(args, "H", &t)) {
        return (NULL);
    }
    py_option* const self = static_cast<py_option*>(obj);
    bool ret = self->object->delOption(t);
    return (PyBool_FromLong(ret ? 1l : 0l));
}

// setData(<byte>) method
PyObject*
setData(PyObject* obj, PyObject* args) {
    PyBytesObject* d = NULL;

    if (!PyArg_ParseTuple(args, "S", &d)) {
        return (NULL);
    }
    vector<uint8_t> data;
    data.resize(PyBytes_GET_SIZE(d));
    memmove(&data[0], PyBytes_AS_STRING(d), data.size());

    py_option* const self = static_cast<py_option*>(obj);
    self->object->setData(data.begin(), data.end());
    Py_RETURN_NONE;
}

// setEncapsulatedSpace(const string& encapsulated_space) method
PyObject*
setEncapsulatedSpace(PyObject* obj, PyObject* args) {
    const char* es = NULL;

    if (!PyArg_ParseTuple(args, "s", &es)) {
        return (NULL);
    }
    const string& encapsulated_space(es);

    py_option* const self = static_cast<py_option*>(obj);
    self->object->setEncapsulatedSpace(encapsulated_space);
    Py_RETURN_NONE;
}

// getEncapsulatedSpace() method
PyObject*
getEncapsulatedSpace(PyObject* obj) {
    py_option* const self = static_cast<py_option*>(obj);
    return (Py_BuildValue("s", self->object->getEncapsulatedSpace().c_str()));
}

// Method table
PyMethodDef option_method[] = {
    { "getUniverse", (PyCFunction)getUniverse, METH_NOARGS,
      "returns option universe (4 or 6" },
    { "toBinary", toBinary, METH_VARARGS,
      "returns binary representation of the option" },
    { "getType", (PyCFunction)getType, METH_NOARGS,
      "returns option type" },
    { "len", (PyCFunction)len, METH_NOARGS,
      "returns length of the complete option" },
    { "getHeaderLen", (PyCFunction)getHeaderLen, METH_NOARGS,
      "returns length of option header" },
    { "getData", (PyCFunction)getData, METH_NOARGS,
      "returns actual data" },
    { "addOption", addOption, METH_VARARGS,
      "adds a sub-option" },
    { "getOption", getOption, METH_VARARGS,
      "return suboption of specific type" },
    { "delOption", delOption, METH_VARARGS,
      "attempts to delete first suboption of requested type" },
    { "setData", setData, METH_VARARGS,
      "sets content of this option" },
    { "setEncapsulatedSpace", setEncapsulatedSpace, METH_VARARGS,
      "sets the name of the option space encapsulated by this option" },
    { "getEncapsulatedSpace", (PyCFunction)getEncapsulatedSpace, METH_NOARGS,
      "returns the name of the option space encapsulated by this option" },
    { NULL, NULL, 0, NULL }
};

} // end of anonymous namespace

namespace isc {
namespace python {

// Python option type definition
PyTypeObject option_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "kea-option",                       // tp_name
    sizeof(py_option),                  // tp_basicsize
    0,                                  // tp_itemsize
    option_dealloc,                     // tp_dealloc
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
    option_str,                         // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "kea option",                       // tp_doc
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    option_method,                      // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    option_init,                        // tp_init
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
initmod_option(PyObject* mod) {
    // Initialize the description object
    if (PyType_Ready(&option_type) < 0) {
        return (false);
    }
    // Add it to the module
    void* p = &option_type;
    if (PyModule_AddObject(mod, "Option", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&option_type);

    return (true);
}

} // namespace python
} // namespace isc
