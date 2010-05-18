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

// $Id$

#include <dns/rrset.h>

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the module init at the
// end
//
static PyObject* po_EmptyRRset;

// This one's for our 'general' exception
// TODO: does this need an according general class?
// should we replace it with some more direct base exception?

//
// Declaration of enums
// Initialization and addition of these go in the module init at the
// end
//

//
// Declaration of class constants
// Initialization and addition of these go in the module init at the
// end
//

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description
using namespace isc::dns;

// RRset
typedef struct {
    PyObject_HEAD
    RRsetPtr rrset;
} s_RRset;

static int RRset_init(s_RRset* self, PyObject* args);
static void RRset_destroy(s_RRset* self);

static PyObject* RRset_getRdataCount(s_RRset* self);
static PyObject* RRset_getName(s_RRset* self);
static PyObject* RRset_getClass(s_RRset* self);
static PyObject* RRset_getType(s_RRset* self);
static PyObject* RRset_getTTL(s_RRset* self);
static PyObject* RRset_setName(s_RRset* self, PyObject* args);
static PyObject* RRset_setTTL(s_RRset* self, PyObject* args);
static PyObject* RRset_toText(s_RRset* self);
static PyObject* RRset_toWire(s_RRset* self, PyObject* args);
static PyObject* RRset_addRdata(s_RRset* self, PyObject* args);
static PyObject* RRset_getRdata(s_RRset* self);
// TODO: iterator?

static PyMethodDef RRset_methods[] = {
    { "get_rdata_count", (PyCFunction)RRset_getRdataCount, METH_NOARGS, "Return the number of rdata fields" },
    { "get_name", (PyCFunction)RRset_getName, METH_NOARGS, "Return" },
    { "get_class", (PyCFunction)RRset_getClass, METH_NOARGS, "Return" },
    { "get_type", (PyCFunction)RRset_getType, METH_NOARGS, "Return" },
    { "get_ttl", (PyCFunction)RRset_getTTL, METH_NOARGS, "Return" },
    { "set_name", (PyCFunction)RRset_setName, METH_VARARGS, "Return" },
    { "set_ttl", (PyCFunction)RRset_setTTL, METH_VARARGS, "Return" },
    { "to_text", (PyCFunction)RRset_toText, METH_NOARGS, "Return" },
    { "to_wire", (PyCFunction)RRset_toWire, METH_VARARGS, "Return" },
    { "add_rdata", (PyCFunction)RRset_addRdata, METH_VARARGS, "Return" },
    { "get_rdata", (PyCFunction)RRset_getRdata, METH_NOARGS, "Returns a List containing all Rdata elements" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject rrset_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "libdns_python.RRset",
    sizeof(s_RRset),                       /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)RRset_destroy,   /* tp_dealloc */
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
    "C++ Name Object",  /* tp_doc */
    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */
    RRset_methods,                       /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc)RRset_init,                /* tp_init */
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
RRset_init(s_RRset* self, PyObject* args UNUSED_PARAM)
{
    s_Name* name;
    s_RRClass* rrclass;
    s_RRType* rrtype;
    s_RRTTL* rrttl;

    if (PyArg_ParseTuple(args, "O!O!O!O!", &name_type, &name,
                                           &rrclass_type, &rrclass,
                                           &rrtype_type, &rrtype,
                                           &rrttl_type, &rrttl
       )) {
        Py_INCREF(self);
        self->rrset = RRsetPtr(new RRset(*name->name, *rrclass->rrclass,
                                *rrtype->rrtype, *rrttl->rrttl));
        return 0;
    }

    self->rrset = RRsetPtr();
    return -1;
}

static void
RRset_destroy(s_RRset* self)
{
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
RRset_getRdataCount(s_RRset* self)
{
    return Py_BuildValue("I", self->rrset->getRdataCount());
}

static PyObject*
RRset_getName(s_RRset* self)
{
    s_Name* name;

    // is this the best way to do this?
    name = (s_Name*)name_type.tp_alloc(&name_type, 0);
    if (name != NULL) {
        name->name = new Name(self->rrset->getName());
        if (name->name == NULL)
          {
            Py_DECREF(name);
            return NULL;
          }
    }

    return (PyObject*)name;
}

static PyObject*
RRset_getClass(s_RRset* self)
{
    s_RRClass* rrclass;

    rrclass = (s_RRClass*)rrclass_type.tp_alloc(&rrclass_type, 0);
    if (rrclass != NULL) {
        rrclass->rrclass = new RRClass(self->rrset->getClass());
        if (rrclass->rrclass == NULL)
          {
            Py_DECREF(rrclass);
            return NULL;
          }
    }

    return (PyObject*)rrclass;
}

static PyObject*
RRset_getType(s_RRset* self)
{
    s_RRType* rrtype;

    rrtype = (s_RRType*)rrtype_type.tp_alloc(&rrtype_type, 0);
    if (rrtype != NULL) {
        rrtype->rrtype = new RRType(self->rrset->getType());
        if (rrtype->rrtype == NULL)
          {
            Py_DECREF(rrtype);
            return NULL;
          }
    }

    return (PyObject*)rrtype;
}

static PyObject*
RRset_getTTL(s_RRset* self)
{
    s_RRTTL* rrttl;

    rrttl = (s_RRTTL*)rrttl_type.tp_alloc(&rrttl_type, 0);
    if (rrttl != NULL) {
        rrttl->rrttl = new RRTTL(self->rrset->getTTL());
        if (rrttl->rrttl == NULL)
          {
            Py_DECREF(rrttl);
            return NULL;
          }
    }

    return (PyObject*)rrttl;
}

static PyObject*
RRset_setName(s_RRset* self, PyObject* args)
{
    s_Name* name;
    if (!PyArg_ParseTuple(args, "O!", &name_type, &name)) {
        return NULL;
    }
    self->rrset->setName(*name->name);
    Py_RETURN_NONE;
}

static PyObject*
RRset_setTTL(s_RRset* self, PyObject* args)
{
    s_RRTTL* rrttl;
    if (!PyArg_ParseTuple(args, "O!", &rrttl_type, &rrttl)) {
        return NULL;
    }
    self->rrset->setTTL(*rrttl->rrttl);
    Py_RETURN_NONE;
}

static PyObject*
RRset_toText(s_RRset* self)
{
    try {
        return Py_BuildValue("s", self->rrset->toText().c_str());
    } catch (EmptyRRset ers) {
        PyErr_SetString(po_EmptyRRset, ers.what());
        return NULL;
    }
}

static PyObject*
RRset_toWire(s_RRset* self, PyObject* args)
{
    PyObject* bytes;
    s_MessageRenderer* mr;

    try {
        if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
            PyObject* bytes_o = bytes;
            
            OutputBuffer buffer(4096);
            self->rrset->toWire(buffer);
            PyObject* n = PyBytes_FromStringAndSize((const char*) buffer.getData(), buffer.getLength());
            PyObject* result = PySequence_InPlaceConcat(bytes_o, n);
            // We need to release the object we temporarily created here
            // to prevent memory leak
            Py_DECREF(n);
            return result;
        } else if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, (PyObject**) &mr)) {
            self->rrset->toWire(*mr->messagerenderer);
            // If we return NULL it is seen as an error, so use this for
            // None returns
            Py_RETURN_NONE;
        }
    } catch (EmptyRRset ers) {
        PyErr_Clear();
        PyErr_SetString(po_EmptyRRset, ers.what());
        return NULL;
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a sequence object or a MessageRenderer");
    return NULL;
}

static PyObject*
RRset_addRdata(s_RRset* self, PyObject* args)
{
    s_Rdata* rdata;
    if (!PyArg_ParseTuple(args, "O!", &rdata_type, &rdata)) {
        return NULL;
    }
    try {
        self->rrset->addRdata(*rdata->rdata);
        Py_RETURN_NONE;
    } catch (std::bad_cast) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "Rdata type to add must match type of RRset");
        return NULL;
    }
}

static PyObject*
RRset_getRdata(s_RRset* self)
{
    PyObject* list = PyList_New(0);

    RdataIteratorPtr it = self->rrset->getRdataIterator();

    for (it->first(); !it->isLast(); it->next()) {
        s_Rdata *rds = (s_Rdata*)rdata_type.tp_alloc(&rdata_type, 0);
        if (rds != NULL) {
            // hmz them iterators/shared_ptrs and private constructors
            // make this a bit weird, so we create a new one with
            // the data available
            const Rdata *rd = &it->getCurrent();
            rds->rdata = createRdata(self->rrset->getType(), self->rrset->getClass(), *rd);
            PyList_Append(list, (PyObject*) rds);
        } else {
            return NULL;
        }
    }
    
    return list;
}

// end of RRset


// Module Initialization, all statics are initialized here
bool
initModulePart_RRset(PyObject* mod)
{
    // Add the exceptions to the module
    po_EmptyRRset = PyErr_NewException("libdns_python.EmptyRRset", NULL, NULL);
    Py_INCREF(po_EmptyRRset);
    PyModule_AddObject(mod, "EmptyRRset", po_EmptyRRset);

    // Add the enums to the module

    // Add the constants to the module

    // Add the classes to the module
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module

    // NameComparisonResult
    if (PyType_Ready(&rrset_type) < 0) {
        return false;
    }
    Py_INCREF(&rrset_type);
    PyModule_AddObject(mod, "RRset",
                       (PyObject*) &rrset_type);
    
    return true;
}

