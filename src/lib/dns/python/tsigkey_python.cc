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

#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <dns/name.h>
#include <dns/tsigkey.h>
#include <dns/rdata.h>

#include "pydnspp_common.h"
#include "name_python.h"
#include "tsigkey_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns;
using namespace isc::dns::python;

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// TSIGKey
//

namespace {
// The s_* Class simply covers one instantiation of the object
class s_TSIGKey : public PyObject {
public:
    s_TSIGKey() : cppobj(NULL) {};
    TSIGKey* cppobj;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
int TSIGKey_init(s_TSIGKey* self, PyObject* args);
void TSIGKey_destroy(s_TSIGKey* self);

// These are the functions we export
// This is a second version of toText, we need one where the argument
// is a PyObject*, for the str() function in python.
PyObject* TSIGKey_getKeyName(const s_TSIGKey* self);
PyObject* TSIGKey_getAlgorithmName(const s_TSIGKey* self);
PyObject* TSIGKey_getSecret(const s_TSIGKey* self);
PyObject* TSIGKey_toText(const s_TSIGKey* self);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef TSIGKey_methods[] = {
    { "get_key_name",
      reinterpret_cast<PyCFunction>(TSIGKey_getKeyName), METH_NOARGS,
      "Return the key name." },
    { "get_algorithm_name",
      reinterpret_cast<PyCFunction>(TSIGKey_getAlgorithmName), METH_NOARGS,
      "Return the algorithm name." },
    { "get_secret",
      reinterpret_cast<PyCFunction>(TSIGKey_getSecret), METH_NOARGS,
      "Return the value of the TSIG secret." },
    { "to_text", reinterpret_cast<PyCFunction>(TSIGKey_toText), METH_NOARGS,
      "Returns the string representation (name:secret:algorithm)" },
    { NULL, NULL, 0, NULL }
};

int
TSIGKey_init(s_TSIGKey* self, PyObject* args) {
    try {
        const char* str;
        if (PyArg_ParseTuple(args, "s", &str)) {
            self->cppobj = new TSIGKey(str);
            return (0);
        }

        PyErr_Clear();
        const PyObject* key_name;
        const PyObject* algorithm_name;
        PyObject* bytes_obj;
        const char* secret;
        Py_ssize_t secret_len;
        if (PyArg_ParseTuple(args, "O!O!O", &name_type, &key_name,
                             &name_type, &algorithm_name, &bytes_obj) &&
            PyObject_AsCharBuffer(bytes_obj, &secret, &secret_len) == 0) {
            if (secret_len == 0) {
                secret = NULL;
            }
            self->cppobj = new TSIGKey(PyName_ToName(key_name),
                                       PyName_ToName(algorithm_name),
                                       secret, secret_len);
            return (0);
        }
    } catch (const isc::InvalidParameter& ex) {
        PyErr_SetString(po_InvalidParameter, ex.what());
        return (-1);
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
        return (-1);
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to TSIGKey constructor");

    return (-1);
}

void
TSIGKey_destroy(s_TSIGKey* const self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
TSIGKey_getKeyName(const s_TSIGKey* const self) {
    try {
        return (createNameObject(self->cppobj->getKeyName()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to get key name of TSIGKey: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "getting key name of TSIGKey");
    }
    return (NULL);
}

PyObject*
TSIGKey_getAlgorithmName(const s_TSIGKey* const self) {
    try {
        return (createNameObject(self->cppobj->getAlgorithmName()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to get algorithm name of TSIGKey: " + string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "getting algorithm name of TSIGKey");
    }
    return (NULL);
}

PyObject*
TSIGKey_getSecret(const s_TSIGKey* const self) {
    return (Py_BuildValue("y#", self->cppobj->getSecret(),
                          self->cppobj->getSecretLength()));
}

PyObject*
TSIGKey_toText(const s_TSIGKey* self) {
    return (Py_BuildValue("s", self->cppobj->toText().c_str()));
}
} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_EDNS
// Most of the functions are not actually implemented and NULL here.
PyTypeObject tsigkey_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.TSIGKey",
    sizeof(s_TSIGKey),                  // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)TSIGKey_destroy,        // tp_dealloc
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
    "The TSIGKey class holds a TSIG key along with some related attributes as "
    "defined in RFC2845.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    TSIGKey_methods,                    // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)TSIGKey_init,             // tp_init
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

bool
PyTSIGKey_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &tsigkey_type));
}

const TSIGKey&
PyTSIGKey_ToTSIGKey(const PyObject* tsigkey_obj) {
    const s_TSIGKey* tsigkey = static_cast<const s_TSIGKey*>(tsigkey_obj);
    return (*tsigkey->cppobj);
}

} // namespace python
} // namespace dns
} // namespace isc
//
// End of TSIGKey
//

//
// TSIGKeyRing
//

namespace {
// The s_* Class simply covers one instantiation of the object
class s_TSIGKeyRing : public PyObject {
public:
    s_TSIGKeyRing() : cppobj(NULL) {};
    TSIGKeyRing* cppobj;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

int TSIGKeyRing_init(s_TSIGKeyRing* self, PyObject* args);
void TSIGKeyRing_destroy(s_TSIGKeyRing* self);

PyObject* TSIGKeyRing_size(const s_TSIGKeyRing* self);
PyObject* TSIGKeyRing_add(const s_TSIGKeyRing* self, PyObject* args);
PyObject* TSIGKeyRing_remove(const s_TSIGKeyRing* self, PyObject* args);
PyObject* TSIGKeyRing_find(const s_TSIGKeyRing* self, PyObject* args);

PyMethodDef TSIGKeyRing_methods[] = {
    { "size", reinterpret_cast<PyCFunction>(TSIGKeyRing_size), METH_NOARGS,
      "Return the number of keys stored in the TSIGKeyRing." },
    { "add", reinterpret_cast<PyCFunction>(TSIGKeyRing_add), METH_VARARGS,
      "Add a TSIGKey to the TSIGKeyRing." },
    { "remove", reinterpret_cast<PyCFunction>(TSIGKeyRing_remove),
      METH_VARARGS,
      "Remove a TSIGKey for the given name from the TSIGKeyRing." },
    { "find", reinterpret_cast<PyCFunction>(TSIGKeyRing_find), METH_VARARGS,
      "Find a TSIGKey for the given name in the TSIGKeyRing. Optional "
      "second argument is an algorithm, in which case it only returns "
      "a key if both match.\n"
      "It returns a tuple of (result_code, key)." },
    { NULL, NULL, 0, NULL }
};

int
TSIGKeyRing_init(s_TSIGKeyRing* self, PyObject* args) {
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "Invalid arguments to TSIGKeyRing constructor");
        return (-1);
    }

    self->cppobj = new(nothrow) TSIGKeyRing();
    if (self->cppobj == NULL) {
        PyErr_SetString(po_IscException, "Allocating TSIGKeyRing failed");
        return (-1);
    }

    return (0);
}

void
TSIGKeyRing_destroy(s_TSIGKeyRing* self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
TSIGKeyRing_size(const s_TSIGKeyRing* const self) {
    return (Py_BuildValue("I", self->cppobj->size()));
}

PyObject*
TSIGKeyRing_add(const s_TSIGKeyRing* const self, PyObject* args) {
    s_TSIGKey* tsigkey;

    if (PyArg_ParseTuple(args, "O!", &tsigkey_type, &tsigkey)) {
        try {
            const TSIGKeyRing::Result result =
                self->cppobj->add(*tsigkey->cppobj);
            return (Py_BuildValue("I", result));
        } catch (...) {
            PyErr_SetString(po_IscException, "Unexpected exception");
            return (NULL);
        }
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError, "Invalid arguments to TSIGKeyRing.add");

    return (NULL);
}

PyObject*
TSIGKeyRing_remove(const s_TSIGKeyRing* self, PyObject* args) {
    PyObject* key_name;

    if (PyArg_ParseTuple(args, "O!", &name_type, &key_name)) {
        const TSIGKeyRing::Result result =
            self->cppobj->remove(PyName_ToName(key_name));
        return (Py_BuildValue("I", result));
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError, "Invalid arguments to TSIGKeyRing.add");

    return (NULL);
}

PyObject*
TSIGKeyRing_find(const s_TSIGKeyRing* self, PyObject* args) {
    PyObject* key_name;
    PyObject* algorithm_name = NULL;

    if (PyArg_ParseTuple(args, "O!|O!", &name_type, &key_name,
                         &name_type, &algorithm_name)) {
        // Can't init TSIGKeyRing::FindResult without actual result,
        // so use ternary operator
        TSIGKeyRing::FindResult result = (algorithm_name == NULL) ?
                    self->cppobj->find(PyName_ToName(key_name)) :
                    self->cppobj->find(PyName_ToName(key_name),
                                       PyName_ToName(algorithm_name));
        if (result.key != NULL) {
            s_TSIGKey* key = PyObject_New(s_TSIGKey, &tsigkey_type);
            if (key == NULL) {
                return (NULL);
            }
            key->cppobj = new(nothrow) TSIGKey(*result.key);
            if (key->cppobj == NULL) {
                Py_DECREF(key);
                PyErr_SetString(po_IscException,
                                "Allocating TSIGKey object failed");
                return (NULL);
            }
            return (Py_BuildValue("IN", result.code, key));
        } else {
            return (Py_BuildValue("Is", result.code, NULL));
        }
    }

    return (NULL);
}
} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {
PyTypeObject tsigkeyring_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.TSIGKeyRing",
    sizeof(s_TSIGKeyRing),              // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)TSIGKeyRing_destroy,    // tp_dealloc
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
    "A simple repository of a set of TSIGKey objects.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    TSIGKeyRing_methods,                // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)TSIGKeyRing_init,         // tp_init
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

bool
PyTSIGKeyRing_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &tsigkeyring_type));
}

const TSIGKeyRing&
PyTSIGKeyRing_ToTSIGKeyRing(const PyObject* tsigkeyring_obj) {
    if (tsigkeyring_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in TSIGKeyRing PyObject conversion");
    }
    const s_TSIGKeyRing* tsigkeyring =
        static_cast<const s_TSIGKeyRing*>(tsigkeyring_obj);
    return (*tsigkeyring->cppobj);
}

} // namespace python
} // namespace dns
} // namespace isc
