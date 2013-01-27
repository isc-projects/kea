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

// Enable this if you use s# variants with PyArg_ParseTuple(), see
// http://docs.python.org/py3k/c-api/arg.html#strings-and-buffers
//#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <util/python/pycppwrapper_util.h>

#include <datasrc/client.h>
#include <datasrc/database.h>
#include <datasrc/data_source.h>
#include <datasrc/sqlite3_accessor.h>
#include <datasrc/zone_iterator.h>
#include <datasrc/zone.h>

#include <dns/python/name_python.h>
#include <dns/python/rrset_python.h>
#include <dns/python/rrclass_python.h>
#include <dns/python/rrtype_python.h>
#include <dns/python/pydnspp_common.h>

#include "datasrc.h"
#include "finder_python.h"
#include "finder_inc.cc"

using namespace std;
using namespace isc::util::python;
using namespace isc::dns::python;
using namespace isc::datasrc;
using namespace isc::datasrc::python;

namespace  {
ZoneFinder::FindResultFlags
getFindResultFlags(const ZoneFinder::Context& context) {
    ZoneFinder::FindResultFlags result_flags = ZoneFinder::RESULT_DEFAULT;
    if (context.isWildcard()) {
        result_flags = result_flags | ZoneFinder::RESULT_WILDCARD;
    }
    if (context.isNSECSigned()) {
        result_flags = result_flags | ZoneFinder::RESULT_NSEC_SIGNED;
    }
    if (context.isNSEC3Signed()) {
        result_flags = result_flags | ZoneFinder::RESULT_NSEC3_SIGNED;
    }
    return (result_flags);
}
}

namespace isc_datasrc_internal {
// This is the shared code for the find() call in the finder and the updater
// Is is intentionally not available through any header, nor at our standard
// namespace, as it is not supposed to be called anywhere but from finder and
// updater
PyObject* ZoneFinder_helper(ZoneFinder* finder, PyObject* args) {
    if (finder == NULL) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Internal error in find() wrapper; "
                        "finder object NULL");
        return (NULL);
    }
    PyObject* name;
    PyObject* rrtype;
    unsigned int options_int = ZoneFinder::FIND_DEFAULT;
    if (PyArg_ParseTuple(args, "O!O!|I", &name_type, &name,
                                         &rrtype_type, &rrtype,
                                         &options_int)) {
        try {
            ZoneFinder::FindOptions options =
                static_cast<ZoneFinder::FindOptions>(options_int);
            ConstZoneFinderContextPtr find_ctx(
                finder->find(PyName_ToName(name), PyRRType_ToRRType(rrtype),
                             options));
            const ZoneFinder::Result r = find_ctx->code;
            isc::dns::ConstRRsetPtr rrsp = find_ctx->rrset;
            ZoneFinder::FindResultFlags result_flags =
                getFindResultFlags(*find_ctx);
            if (rrsp) {
                // Use N instead of O so the refcount isn't increased twice
                return (Py_BuildValue("INI", r, createRRsetObject(*rrsp),
                                      result_flags));
            } else {
                return (Py_BuildValue("IOI", r, Py_None, result_flags));
            }
        } catch (const OutOfZone& ooz) {
            PyErr_SetString(getDataSourceException("OutOfZone"), ooz.what());
            return (NULL);
        } catch (const DataSourceError& dse) {
            PyErr_SetString(getDataSourceException("Error"), dse.what());
            return (NULL);
        } catch (const std::exception& exc) {
            PyErr_SetString(getDataSourceException("Error"), exc.what());
            return (NULL);
        } catch (...) {
            PyErr_SetString(getDataSourceException("Error"),
                            "Unexpected exception");
            return (NULL);
        }
    } else {
        return (NULL);
    }
}

PyObject* ZoneFinder_helper_all(ZoneFinder* finder, PyObject* args) {
    if (finder == NULL) {
        PyErr_SetString(getDataSourceException("Error"),
                        "Internal error in find_all() wrapper; "
                        "finder object NULL");
        return (NULL);
    }
    PyObject* name;
    const unsigned int options_int = ZoneFinder::FIND_DEFAULT;
    if (PyArg_ParseTuple(args, "O!|I", &name_type, &name, &options_int)) {
        try {
            ZoneFinder::FindOptions options =
                static_cast<ZoneFinder::FindOptions>(options_int);
            std::vector<isc::dns::ConstRRsetPtr> target;
            ConstZoneFinderContextPtr find_ctx(
                finder->findAll(PyName_ToName(name), target, options));
            const ZoneFinder::Result r = find_ctx->code;
            isc::dns::ConstRRsetPtr rrsp = find_ctx->rrset;
            ZoneFinder::FindResultFlags result_flags =
                getFindResultFlags(*find_ctx);
            if (r == ZoneFinder::SUCCESS) {
                // Copy all the RRsets to the result list
                PyObjectContainer list_container(PyList_New(target.size()));
                for (size_t i(0); i < target.size(); ++i) {
                    PyList_SET_ITEM(list_container.get(), i,
                                    createRRsetObject(*target[i]));
                }
                // Construct the result with the list. The Py_BuildValue
                // increases the refcount and the container decreases it
                // later. This way, it feels safer in case the build function
                // would fail.
                return (Py_BuildValue("IOI", r, list_container.get(),
                                      result_flags));
            } else {
                if (rrsp) {
                    // Use N instead of O so the refcount isn't increased twice
                    return (Py_BuildValue("INI", r, createRRsetObject(*rrsp),
                                          result_flags));
                } else {
                    return (Py_BuildValue("IOI", r, Py_None, result_flags));
                }
            }
        } catch (const DataSourceError& dse) {
            PyErr_SetString(getDataSourceException("Error"), dse.what());
            return (NULL);
        } catch (const std::exception& exc) {
            PyErr_SetString(getDataSourceException("Error"), exc.what());
            return (NULL);
        } catch (...) {
            PyErr_SetString(getDataSourceException("Error"),
                            "Unexpected exception");
            return (NULL);
        }
    } else {
        return (NULL);
    }
}

} // end namespace internal

namespace {
// The s_* Class simply covers one instantiation of the object
class s_ZoneFinder : public PyObject {
public:
    s_ZoneFinder() : cppobj(ZoneFinderPtr()), base_obj(NULL) {};
    ZoneFinderPtr cppobj;
    // This is a reference to a base object; if the object of this class
    // depends on another object to be in scope during its lifetime,
    // we use INCREF the base object upon creation, and DECREF it at
    // the end of the destructor
    // This is an optional argument to createXXX(). If NULL, it is ignored.
    PyObject* base_obj;
};

// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_ZoneFinder, ZoneFinder> ZoneFinderContainer;

// General creation and destruction
int
ZoneFinder_init(PyObject*, PyObject*, PyObject*) {
    // can't be called directly
    PyErr_SetString(PyExc_TypeError,
                    "ZoneFinder cannot be constructed directly");

    return (-1);
}

void
ZoneFinder_destroy(PyObject* po_self) {
    s_ZoneFinder* self = static_cast<s_ZoneFinder*>(po_self);
    // cppobj is a shared ptr, but to make sure things are not destroyed in
    // the wrong order, we reset it here.
    self->cppobj.reset();
    if (self->base_obj != NULL) {
        Py_DECREF(self->base_obj);
    }
    Py_TYPE(self)->tp_free(self);
}

PyObject*
ZoneFinder_getClass(PyObject* po_self, PyObject*) {
    s_ZoneFinder* self = static_cast<s_ZoneFinder*>(po_self);
    try {
        return (createRRClassObject(self->cppobj->getClass()));
    } catch (const std::exception& exc) {
        PyErr_SetString(getDataSourceException("Error"), exc.what());
        return (NULL);
    }
}

PyObject*
ZoneFinder_getOrigin(PyObject* po_self, PyObject*) {
    s_ZoneFinder* self = static_cast<s_ZoneFinder*>(po_self);
    try {
        return (createNameObject(self->cppobj->getOrigin()));
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
ZoneFinder_find(PyObject* po_self, PyObject* args) {
    s_ZoneFinder* const self = static_cast<s_ZoneFinder*>(po_self);
    return (isc_datasrc_internal::ZoneFinder_helper(self->cppobj.get(), args));
}

PyObject*
ZoneFinder_find_all(PyObject* po_self, PyObject* args) {
    s_ZoneFinder* const self = static_cast<s_ZoneFinder*>(po_self);
    return (isc_datasrc_internal::ZoneFinder_helper_all(self->cppobj.get(),
                                                        args));
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef ZoneFinder_methods[] = {
    { "get_origin", ZoneFinder_getOrigin, METH_NOARGS,
       ZoneFinder_getOrigin_doc },
    { "get_class", ZoneFinder_getClass, METH_NOARGS, ZoneFinder_getClass_doc },
    { "find", ZoneFinder_find, METH_VARARGS, ZoneFinder_find_doc },
    { "find_all", ZoneFinder_find_all, METH_VARARGS, ZoneFinder_findAll_doc },
    { NULL, NULL, 0, NULL }
};

} // end of unnamed namespace

namespace isc {
namespace datasrc {
namespace python {

PyTypeObject zonefinder_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "datasrc.ZoneFinder",
    sizeof(s_ZoneFinder),               // tp_basicsize
    0,                                  // tp_itemsize
    ZoneFinder_destroy,                 // tp_dealloc
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
    ZoneFinder_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    ZoneFinder_methods,                 // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    ZoneFinder_init,                    // tp_init
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
createZoneFinderObject(isc::datasrc::ZoneFinderPtr source, PyObject* base_obj) {
    s_ZoneFinder* py_zf = static_cast<s_ZoneFinder*>(
        zonefinder_type.tp_alloc(&zonefinder_type, 0));
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
} // namespace datasrc
} // namespace isc

