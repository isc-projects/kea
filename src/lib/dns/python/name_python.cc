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

#include <util/buffer.h>
#include <util/python/pycppwrapper_util.h>

#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/labelsequence.h>

#include "pydnspp_common.h"
#include "messagerenderer_python.h"
#include "name_python.h"

#include <iostream>

using namespace isc::dns;
using namespace isc::dns::python;
using namespace isc::util;
using namespace isc::util::python;

namespace {
// The s_* Class simply covers one instantiation of the object.
class s_NameComparisonResult : public PyObject {
public:
    s_NameComparisonResult() : cppobj(NULL) {}
    NameComparisonResult* cppobj;
};

class s_Name : public PyObject {
public:
    s_Name() : cppobj(NULL), position(0) {}
    Name* cppobj;
    size_t position;
};

int NameComparisonResult_init(s_NameComparisonResult*, PyObject*);
void NameComparisonResult_destroy(s_NameComparisonResult* self);
PyObject* NameComparisonResult_getOrder(s_NameComparisonResult* self);
PyObject* NameComparisonResult_getCommonLabels(s_NameComparisonResult* self);
PyObject* NameComparisonResult_getRelation(s_NameComparisonResult* self);

PyMethodDef NameComparisonResult_methods[] = {
    { "get_order", reinterpret_cast<PyCFunction>(NameComparisonResult_getOrder), METH_NOARGS,
      "Returns the order" },
    { "get_common_labels", reinterpret_cast<PyCFunction>(NameComparisonResult_getCommonLabels), METH_NOARGS,
      "Returns the number of common labels" },
    { "get_relation", reinterpret_cast<PyCFunction>(NameComparisonResult_getRelation), METH_NOARGS,
      "Returns the relation" },
    { NULL, NULL, 0, NULL }
};

int
NameComparisonResult_init(s_NameComparisonResult*, PyObject*) {
    PyErr_SetString(PyExc_NotImplementedError,
                    "NameComparisonResult can't be built directly");
    return (-1);
}

void
NameComparisonResult_destroy(s_NameComparisonResult* self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
NameComparisonResult_getOrder(s_NameComparisonResult* self) {
    return (Py_BuildValue("i", self->cppobj->getOrder()));
}

PyObject*
NameComparisonResult_getCommonLabels(s_NameComparisonResult* self) {
    return (Py_BuildValue("I", self->cppobj->getCommonLabels()));
}

PyObject*
NameComparisonResult_getRelation(s_NameComparisonResult* self) {
    return (Py_BuildValue("I", self->cppobj->getRelation()));
}

// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_Name, Name> NameContainer;

int Name_init(s_Name* self, PyObject* args);
void Name_destroy(s_Name* self);

PyObject* Name_toWire(s_Name* self, PyObject* args);
PyObject* Name_toText(s_Name* self, PyObject* args);
PyObject* Name_str(PyObject* self);
PyObject* Name_getLabelCount(s_Name* self);
PyObject* Name_at(s_Name* self, PyObject* args);
PyObject* Name_getLength(s_Name* self);

PyObject* Name_compare(s_Name* self, PyObject* args);
PyObject* Name_equals(s_Name* self, PyObject* args);

PyObject* Name_richcmp(s_Name* self, s_Name* other, int op);
PyObject* Name_split(s_Name* self, PyObject* args);
PyObject* Name_reverse(s_Name* self);
PyObject* Name_concatenate(s_Name* self, PyObject* args);
PyObject* Name_downcase(s_Name* self);
PyObject* Name_isWildCard(s_Name* self);
Py_hash_t Name_hash(PyObject* py_self);

PyMethodDef Name_methods[] = {
    { "at", reinterpret_cast<PyCFunction>(Name_at), METH_VARARGS,
      "Returns the integer value of the name data at the specified position" },
    { "get_length", reinterpret_cast<PyCFunction>(Name_getLength), METH_NOARGS,
      "Returns the length" },
    { "get_labelcount", reinterpret_cast<PyCFunction>(Name_getLabelCount), METH_NOARGS,
      "Returns the number of labels" },
    { "to_text", reinterpret_cast<PyCFunction>(Name_toText), METH_VARARGS,
      "Returns the string representation. The optional argument must be either"
      "True of False. If True, the final dot will be omitted." },
    { "to_wire", reinterpret_cast<PyCFunction>(Name_toWire), METH_VARARGS,
      "Converts the Name object to wire format.\n"
      "The argument can be either a MessageRenderer or an object that "
      "implements the sequence interface. If the object is mutable "
      "(for instance a bytearray()), the wire data is added in-place.\n"
      "If it is not (for instance a bytes() object), a new object is "
      "returned" },
    { "compare", reinterpret_cast<PyCFunction>(Name_compare), METH_VARARGS,
      "Returns a NameComparisonResult object. The argument must be another Name object" },
    { "equals", reinterpret_cast<PyCFunction>(Name_equals), METH_VARARGS,
      "Returns true if the given Name object is equal to this one" },
    { "split", reinterpret_cast<PyCFunction>(Name_split), METH_VARARGS,
      "Splits the name, takes two arguments, the first is an integer "
      "specifying the first label to place in the result. The second "
      "is an integer specifying the number of labels to put in the "
      "result. Returns a new Name object" },
    { "reverse", reinterpret_cast<PyCFunction>(Name_reverse), METH_NOARGS,
      "Returns a new Name object that is the reverse of this one" },
    { "concatenate", reinterpret_cast<PyCFunction>(Name_concatenate), METH_VARARGS,
      "Concatenates the given Name object to this one and returns the "
      "result as a new Name object" },
    { "downcase", reinterpret_cast<PyCFunction>(Name_downcase), METH_NOARGS,
      "Downcases this name object (in-place). Returns a new reference to the Name." },
    { "is_wildcard", reinterpret_cast<PyCFunction>(Name_isWildCard), METH_NOARGS,
      "Returns True if the Name object represents a wildcard name." },
    { NULL, NULL, 0, NULL }
};

int
Name_init(s_Name* self, PyObject* args) {
    const char* s;
    PyObject* downcase = Py_False;

    // Depending on the arguments in *args, we decide which of the
    // constructors is meant. If the first argument is of type string,
    // we use the string-based constructor. If it is a bytes object,
    // we use the wire-based one.
    if (PyArg_ParseTuple(args, "s|O!", &s, &PyBool_Type, &downcase)) {
        try {
            const std::string n(s);

            self->cppobj = new Name(n, downcase == Py_True);
            self->position = 0;
        } catch (const EmptyLabel&) {
            PyErr_SetString(po_EmptyLabel, "EmptyLabel");
            return (-1);
        } catch (const TooLongLabel&) {
            PyErr_SetString(po_TooLongLabel, "TooLongLabel");
            return (-1);
        } catch (const BadLabelType&) {
            PyErr_SetString(po_BadLabelType, "BadLabelType");
            return (-1);
        } catch (const BadEscape&) {
            PyErr_SetString(po_BadEscape, "BadEscape");
            return (-1);
        } catch (const TooLongName&) {
            PyErr_SetString(po_TooLongName, "TooLongName");
            return (-1);
        } catch (const IncompleteName&) {
            PyErr_SetString(po_IncompleteName, "IncompleteName");
            return (-1);
#ifdef CATCHMEMERR
        } catch (const std::bad_alloc&) {
            PyErr_NoMemory();
            return (-1);
#endif
        } catch (...) {
            PyErr_SetString(po_IscException, "Unexpected?!");
            return (-1);
        }
        return (0);
    }
    PyErr_Clear();

    PyObject* bytes_obj;
    const char* bytes;
    Py_ssize_t len;
    long position = 0;

    // It was not a string (see comment above), so try bytes, and
    // create with buffer object
    if (PyArg_ParseTuple(args, "O|lO!", &bytes_obj, &position,
                         &PyBool_Type, &downcase) &&
                         PyObject_AsCharBuffer(bytes_obj, &bytes, &len) != -1) {
        try {
            if (position < 0) {
                // Throw IndexError here since name index should be unsigned
                PyErr_SetString(PyExc_IndexError,
                                "Name index shouldn't be negative");
                return (-1);
            }
            InputBuffer buffer(bytes, len);

            buffer.setPosition(position);
            self->cppobj = new Name(buffer, downcase == Py_True);
            self->position = buffer.getPosition();
        } catch (const InvalidBufferPosition&) {
            PyErr_SetString(po_InvalidBufferPosition,
                            "InvalidBufferPosition");
            return (-1);
        } catch (const DNSMessageFORMERR&) {
            PyErr_SetString(po_DNSMessageFORMERR, "DNSMessageFORMERR");
            return (-1);
        } catch (...) {
            PyErr_SetString(po_IscException, "Unexpected?!");
            return (-1);
        }
        return (0);
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "No valid types in Name constructor (should be string or sequence and offset");
    return (-1);
}

void
Name_destroy(s_Name* self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
Name_at(s_Name* self, PyObject* args) {
    int pos;
    if (!PyArg_ParseTuple(args, "i", &pos)) {
        return (NULL);
    }
    if (pos < 0) {
        // Throw IndexError here since name index should be unsigned
        PyErr_SetString(PyExc_IndexError,
                        "name index shouldn't be negative");
        return (NULL);
    }

    try {
        return (Py_BuildValue("I", self->cppobj->at(pos)));
    } catch (const isc::OutOfRange&) {
        PyErr_SetString(PyExc_IndexError,
                        "name index out of range");
        return (NULL);
    }
}

PyObject*
Name_getLength(s_Name* self) {
    return (Py_BuildValue("i", self->cppobj->getLength()));
}

PyObject*
Name_getLabelCount(s_Name* self) {
    return (Py_BuildValue("i", self->cppobj->getLabelCount()));
}

PyObject*
Name_toText(s_Name* self, PyObject* args) {
    PyObject* omit_final_dot_obj = NULL;
    if (PyArg_ParseTuple(args, "|O", &omit_final_dot_obj)) {
        bool omit_final_dot = false;
        if (omit_final_dot_obj != NULL) {
            if (PyBool_Check(omit_final_dot_obj) != 0) {
                omit_final_dot = (omit_final_dot_obj == Py_True);
            } else {
                PyErr_SetString(PyExc_TypeError,
                    "Optional argument 1 of to_text() should be True of False");
                return (NULL);
            }
        }
        return (Py_BuildValue("s",
                              self->cppobj->toText(omit_final_dot).c_str()));
    } else {
        return (NULL);
    }
}

PyObject*
Name_str(PyObject* self) {
    // Simply call the to_text method we already defined
    // str() is not defined in the c++ version, only to_text
    // and we already have a wrapper for that one.
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
Name_toWire(s_Name* self, PyObject* args) {
    PyObject* bytes;
    PyObject* mr;

    if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
        PyObject* bytes_o = bytes;

        OutputBuffer buffer(Name::MAX_WIRE);
        self->cppobj->toWire(buffer);
        PyObject* name_bytes = PyBytes_FromStringAndSize(static_cast<const char*>(buffer.getData()), buffer.getLength());
        PyObject* result = PySequence_InPlaceConcat(bytes_o, name_bytes);
        // We need to release the object we temporarily created here
        // to prevent memory leak
        Py_DECREF(name_bytes);
        return (result);
    } else if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, &mr)) {
        self->cppobj->toWire(PyMessageRenderer_ToMessageRenderer(mr));
        // If we return NULL it is seen as an error, so use this for
        // None returns
        Py_RETURN_NONE;
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a sequence object or a MessageRenderer");
    return (NULL);
}

PyObject*
Name_compare(s_Name* self, PyObject* args) {
    s_Name* other;

    if (!PyArg_ParseTuple(args, "O!", &name_type, &other))
        return (NULL);

    s_NameComparisonResult* ret = PyObject_New(s_NameComparisonResult, &name_comparison_result_type);
    if (ret != NULL) {
        ret->cppobj = new NameComparisonResult(
            self->cppobj->compare(*other->cppobj));
    }
    return (ret);
}

PyObject*
Name_equals(s_Name* self, PyObject* args) {
    s_Name* other;

    if (!PyArg_ParseTuple(args, "O!", &name_type, &other))
        return (NULL);

    if (self->cppobj->equals(*other->cppobj))
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

PyObject*
Name_split(s_Name* self, PyObject* args) {
    int first, n;
    s_Name* ret = NULL;

    if (PyArg_ParseTuple(args, "ii", &first, &n)) {
        if (first < 0 || n < 0) {
            // Throw IndexError here since name index should be unsigned
            PyErr_SetString(PyExc_IndexError,
                            "name index shouldn't be negative");
            return (NULL);
        }
        ret = PyObject_New(s_Name, &name_type);
        if (ret != NULL) {
            ret->cppobj = NULL;
            try {
                ret->cppobj = new Name(self->cppobj->split(first, n));
            } catch (const isc::OutOfRange& oor) {
                PyErr_SetString(PyExc_IndexError, oor.what());
                ret->cppobj = NULL;
            }
            if (ret->cppobj == NULL) {
                Py_DECREF(ret);
                return (NULL);
            }
        }
    } else if (PyArg_ParseTuple(args, "i", &n)) {
        PyErr_Clear();
        if (n < 0) {
            // Throw IndexError here since name index should be unsigned
            PyErr_SetString(PyExc_IndexError,
                            "name index shouldn't be negative");
            return (NULL);
        }
        ret = PyObject_New(s_Name, &name_type);
        if (ret != NULL) {
            ret->cppobj = NULL;
            try {
                ret->cppobj = new Name(self->cppobj->split(n));
            } catch (const isc::OutOfRange& oor) {
                PyErr_SetString(PyExc_IndexError, oor.what());
                ret->cppobj = NULL;
            }
            if (ret->cppobj == NULL) {
                Py_DECREF(ret);
                return (NULL);
            }
        }
    } else {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError, "No valid type in split argument");
    }
    return (ret);
}

//
// richcmp defines the ==, !=, >, <, >= and <= operators in python
// It is translated to a function that gets 3 arguments, an object,
// an object to compare to, and an operator.
//
PyObject*
Name_richcmp(s_Name* self, s_Name* other, int op) {
    bool c;

    // Check for null and if the types match. If different type,
    // simply return False
    if (!other || (self->ob_type != other->ob_type)) {
        Py_RETURN_FALSE;
    }

    switch (op) {
    case Py_LT:
        c = *self->cppobj < *other->cppobj;
        break;
    case Py_LE:
        c = *self->cppobj <= *other->cppobj;
        break;
    case Py_EQ:
        c = *self->cppobj == *other->cppobj;
        break;
    case Py_NE:
        c = *self->cppobj != *other->cppobj;
        break;
    case Py_GT:
        c = *self->cppobj > *other->cppobj;
        break;
    case Py_GE:
        c = *self->cppobj >= *other->cppobj;
        break;
    default:
        PyErr_SetString(PyExc_IndexError,
                        "Unhandled rich comparison operator");
        return (NULL);
    }
    if (c) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject*
Name_reverse(s_Name* self) {
    s_Name* ret = PyObject_New(s_Name, &name_type);

    if (ret != NULL) {
        ret->cppobj = new Name(self->cppobj->reverse());
        if (ret->cppobj == NULL) {
            Py_DECREF(ret);
            return (NULL);
        }
    }
    return (ret);
}

PyObject*
Name_concatenate(s_Name* self, PyObject* args) {
    s_Name* other;

    if (!PyArg_ParseTuple(args, "O!", &name_type, &other))
        return (NULL);

    s_Name* ret = PyObject_New(s_Name, &name_type);
    if (ret != NULL) {
        try {
            ret->cppobj = new Name(self->cppobj->concatenate(*other->cppobj));
        } catch (const TooLongName& tln) {
            PyErr_SetString(po_TooLongName, tln.what());
            return (NULL);
        }
    }
    return (ret);
}

PyObject*
Name_downcase(s_Name* self) {
    self->cppobj->downcase();
    Py_INCREF(self);
    return (self);
}

PyObject*
Name_isWildCard(s_Name* self) {
    if (self->cppobj->isWildcard()) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

Py_hash_t
Name_hash(PyObject* pyself) {
    const s_Name* const self = static_cast<s_Name*>(pyself);
    return (convertToPyHash<size_t>(
                LabelSequence(*self->cppobj).getHash(false)));
}

} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {

//
// Definition of the custom exceptions
// Initialization and addition of these go in the module init at the
// end
//
PyObject* po_EmptyLabel;
PyObject* po_TooLongName;
PyObject* po_TooLongLabel;
PyObject* po_BadLabelType;
PyObject* po_BadEscape;
PyObject* po_IncompleteName;
PyObject* po_InvalidBufferPosition;
PyObject* po_DNSMessageFORMERR;

//
// Definition of enums
// Initialization and addition of these go in the module init at the
// end
//
PyObject* po_NameRelation;

PyTypeObject name_comparison_result_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.NameComparisonResult",
    sizeof(s_NameComparisonResult),           // tp_basicsize
    0,                                        // tp_itemsize
    (destructor)NameComparisonResult_destroy, // tp_dealloc
    NULL,                                     // tp_print
    NULL,                                     // tp_getattr
    NULL,                                     // tp_setattr
    NULL,                                     // tp_reserved
    NULL,                                     // tp_repr
    NULL,                                     // tp_as_number
    NULL,                                     // tp_as_sequence
    NULL,                                     // tp_as_mapping
    NULL,                                     // tp_hash
    NULL,                                     // tp_call
    NULL,                                     // tp_str
    NULL,                                     // tp_getattro
    NULL,                                     // tp_setattro
    NULL,                                     // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                       // tp_flags
    "This is a supplemental class used only as a return value of Name.compare(). "
    "It encapsulate a tuple of the comparison: ordering, number of common labels, "
    "and relationship as follows:\n"
    "- ordering: relative ordering under the DNSSEC order relation\n"
    "- labels: the number of common significant labels of the two names being"
    "  compared\n"
    "- relationship: see NameComparisonResult.NameRelation\n",
    NULL,                                     // tp_traverse
    NULL,                                     // tp_clear
    NULL,                                     // tp_richcompare
    0,                                        // tp_weaklistoffset
    NULL,                                     // tp_iter
    NULL,                                     // tp_iternext
    NameComparisonResult_methods,             // tp_methods
    NULL,                                     // tp_members
    NULL,                                     // tp_getset
    NULL,                                     // tp_base
    NULL,                                     // tp_dict
    NULL,                                     // tp_descr_get
    NULL,                                     // tp_descr_set
    0,                                        // tp_dictoffset
    (initproc)NameComparisonResult_init,      // tp_init
    NULL,                                     // tp_alloc
    PyType_GenericNew,                        // tp_new
    NULL,                                     // tp_free
    NULL,                                     // tp_is_gc
    NULL,                                     // tp_bases
    NULL,                                     // tp_mro
    NULL,                                     // tp_cache
    NULL,                                     // tp_subclasses
    NULL,                                     // tp_weaklist
    NULL,                                     // tp_del
    0                                         // tp_version_tag
};

PyTypeObject name_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Name",
    sizeof(s_Name),                     // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Name_destroy,           // tp_dealloc
    NULL,                               // tp_print
    NULL,                               // tp_getattr
    NULL,                               // tp_setattr
    NULL,                               // tp_reserved
    NULL,                               // tp_repr
    NULL,                               // tp_as_number
    NULL,                               // tp_as_sequence
    NULL,                               // tp_as_mapping
    Name_hash,                          // tp_hash
    NULL,                               // tp_call
    Name_str,                           // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Name class encapsulates DNS names.\n"
    "It provides interfaces to construct a name from string or wire-format data, "
    "transform a name into a string or wire-format data, compare two names, get "
    "access to various properties of a name, etc.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    (richcmpfunc)Name_richcmp,          // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Name_methods,                       // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Name_init,                // tp_init
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

PyObject*
createNameObject(const Name& source) {
    NameContainer container(PyObject_New(s_Name, &name_type));
    container.set(new Name(source));
    return (container.release());
}

bool
PyName_Check(PyObject* obj) {
    if (obj == NULL) {
        isc_throw(PyCPPWrapperException, "obj argument NULL in typecheck");
    }
    return (PyObject_TypeCheck(obj, &name_type));
}

const Name&
PyName_ToName(const PyObject* name_obj) {
    if (name_obj == NULL) {
        isc_throw(PyCPPWrapperException,
                  "obj argument NULL in Name PyObject conversion");
    }
    const s_Name* name = static_cast<const s_Name*>(name_obj);
    return (*name->cppobj);
}


} // namespace python
} // namespace dns
} // namespace isc
