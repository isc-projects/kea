// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

// Enable this if you use s# variants with PyArg_ParseTuple(), see
// http://docs.python.org/py3k/c-api/arg.html#strings-and-buffers
//#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <string>
#include <stdexcept>

#include <util/python/pycppwrapper_util.h>

#include <datasrc/memory/zone_writer.h>

#include "zonewriter_python.h"
#include "datasrc.h"

#include "zonewriter_inc.cc"

using namespace std;
using namespace isc::util::python;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::python;
using namespace isc::datasrc::memory::python;

//
// ZoneWriter
//

namespace {

// The s_* Class simply covers one instantiation of the object
class s_ZoneWriter : public PyObject {
public:
    s_ZoneWriter() :
        cppobj(ConfigurableClientList::ZoneWriterPtr()),
        base_obj(NULL)
    {}

    ConfigurableClientList::ZoneWriterPtr cppobj;
    // This is a reference to a base object; if the object of this class
    // depends on another object to be in scope during its lifetime,
    // we use INCREF the base object upon creation, and DECREF it at
    // the end of the destructor
    // This is an optional argument to createXXX(). If NULL, it is ignored.
    PyObject* base_obj;
};

int
ZoneWriter_init(PyObject*, PyObject*, PyObject*) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneWriter cannot be constructed directly");

    return (-1);
}

void
ZoneWriter_destroy(PyObject* po_self) {
    s_ZoneWriter* self = static_cast<s_ZoneWriter*>(po_self);
    // cppobj is a shared ptr, but to make sure things are not destroyed in
    // the wrong order, we reset it here.
    self->cppobj.reset();
    if (self->base_obj != NULL) {
        Py_DECREF(self->base_obj);
    }
    Py_TYPE(self)->tp_free(self);
}

PyObject*
ZoneWriter_load(PyObject* po_self, PyObject*) {
    s_ZoneWriter* self = static_cast<s_ZoneWriter*>(po_self);
    try {
        std::string error_msg;
        self->cppobj->load(&error_msg);
        if (!error_msg.empty()) {
            return (Py_BuildValue("s", error_msg.c_str()));
        }
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }

    Py_RETURN_NONE;
}

PyObject*
ZoneWriter_install(PyObject* po_self, PyObject*) {
    s_ZoneWriter* self = static_cast<s_ZoneWriter*>(po_self);
    try {
        self->cppobj->install();
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }

    Py_RETURN_NONE;
}

PyObject*
ZoneWriter_cleanup(PyObject* po_self, PyObject*) {
    s_ZoneWriter* self = static_cast<s_ZoneWriter*>(po_self);
    try {
        self->cppobj->cleanup();
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Unknown C++ exception");
        return (NULL);
    }

    Py_RETURN_NONE;
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneWriter_methods[] = {
    { "load", ZoneWriter_load, METH_NOARGS,
      ZoneWriter_load_doc },
    { "install", ZoneWriter_install, METH_NOARGS,
      ZoneWriter_install_doc },
    { "cleanup", ZoneWriter_cleanup, METH_NOARGS,
      ZoneWriter_cleanup_doc },
    { NULL, NULL, 0, NULL }
};

} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace memory {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_ZoneWriter
// Most of the functions are not actually implemented and NULL here.
PyTypeObject zonewriter_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneWriter",
    sizeof(s_ZoneWriter),               // tp_basicsize
    0,                                  // tp_itemsize
    ZoneWriter_destroy,                 // tp_dealloc
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
    ZoneWriter_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    ZoneWriter_methods,                 // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ZoneWriter_init,                    // tp_init
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

// Module Initialization, all statics are initialized here
bool
initModulePart_ZoneWriter(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&zonewriter_type) < 0) {
        return (false);
    }
    void* p = &zonewriter_type;
    if (PyModule_AddObject(mod, "ZoneWriter", static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&zonewriter_type);

    return (true);
}

PyObject*
createZoneWriterObject(ConfigurableClientList::ZoneWriterPtr source,
                       PyObject* base_obj)
{
    s_ZoneWriter* py_zf = static_cast<s_ZoneWriter*>(
        zonewriter_type.tp_alloc(&zonewriter_type, 0));
    if (py_zf != NULL) {
        py_zf->cppobj = source;
        py_zf->base_obj = base_obj;
        if (base_obj != NULL) {
            Py_INCREF(base_obj);
        }
    }
    return (py_zf);
}

} // namespace python
} // namespace memory
} // namespace datasrc
} // namespace isc
