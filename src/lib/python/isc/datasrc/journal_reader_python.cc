// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <util/python/pycppwrapper_util.h>

#include <datasrc/client.h>
#include <datasrc/database.h>

#include <dns/python/rrset_python.h>

#include "datasrc.h"
#include "journal_reader_python.h"

#include "journal_reader_inc.cc"

using namespace isc::util::python;
using namespace isc::dns::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

namespace {
// The s_* Class simply covers one instantiation of the object
class s_ZoneJournalReader : public PyObject {
public:
    s_ZoneJournalReader() : cppobj(ZoneJournalReaderPtr()), base_obj(NULL) {};
    ZoneJournalReaderPtr cppobj;
    // This is a reference to a base object; if the object of this class
    // depends on another object to be in scope during its lifetime,
    // we use INCREF the base object upon creation, and DECREF it at
    // the end of the destructor
    // This is an optional argument to createXXX(). If NULL, it is ignored.
    PyObject* base_obj;
};

// General creation and destruction
int
ZoneJournalReader_init(PyObject*, PyObject*, PyObject*) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneJournalReader cannot be constructed directly");

    return (-1);
}

void
ZoneJournalReader_destroy(PyObject* po_self) {
    s_ZoneJournalReader* const self =
        static_cast<s_ZoneJournalReader*>(po_self) ;
    // cppobj is a shared ptr, but to make sure things are not destroyed in
    // the wrong order, we reset it here.
    self->cppobj.reset();
    if (self->base_obj != NULL) {
        Py_DECREF(self->base_obj);
    }
    Py_TYPE(self)->tp_free(self);
}

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//
PyObject*
ZoneJournalReader_getNextDiff(PyObject* po_self, PyObject*) {
    s_ZoneJournalReader* self = static_cast<s_ZoneJournalReader*>(po_self);
    try {
        isc::dns::ConstRRsetPtr rrset = self->cppobj->getNextDiff();
        if (!rrset) {
            Py_RETURN_NONE;
        }
        return (createRRsetObject(*rrset));
    } catch (const isc::InvalidOperation& ex) {
        PyErr_SetString(PyExc_ValueError, ex.what());
        return (NULL);
    } catch (const isc::Exception& isce) {
        PyErr_SetString(getDataSourceException("Error"), isce.what());
        return (NULL);
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unexpected exception");
        return (NULL);
    }
}

PyObject*
ZoneJournalReader_iter(PyObject *self) {
    Py_INCREF(self);
    return (self);
}

PyObject*
ZoneJournalReader_next(PyObject* self) {
    PyObject* result = ZoneJournalReader_getNextDiff(self, NULL);
    // iter_next must return NULL without error instead of Py_None
    if (result == Py_None) {
        Py_DECREF(result);
        return (NULL);
    } else {
        return (result);
    }
}

PyMethodDef ZoneJournalReader_methods[] = {
    { "get_next_diff", ZoneJournalReader_getNextDiff, METH_NOARGS,
      ZoneJournalReader_getNextDiff_doc },
    { NULL, NULL, 0, NULL }
};


} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace python {
PyTypeObject journal_reader_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneJournalReader",
    sizeof(s_ZoneJournalReader),             // tp_basicsize
    0,                                  // tp_itemsize
    ZoneJournalReader_destroy,          // tp_dealloc
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
    ZoneJournalReader_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    ZoneJournalReader_iter,                  // tp_iter
    ZoneJournalReader_next,                  // tp_iternext
    ZoneJournalReader_methods,               // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ZoneJournalReader_init,             // tp_init
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
createZoneJournalReaderObject(ZoneJournalReaderPtr source,
                              PyObject* base_obj)
{
    s_ZoneJournalReader* po = static_cast<s_ZoneJournalReader*>(
        journal_reader_type.tp_alloc(&journal_reader_type, 0));
    if (po != NULL) {
        po->cppobj = source;
        po->base_obj = base_obj;
        if (base_obj != NULL) {
            Py_INCREF(base_obj);
        }
    }
    return (po);
}

} // namespace python
} // namespace datasrc
} // namespace isc
