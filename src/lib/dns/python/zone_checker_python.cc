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
#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <util/python/pycppwrapper_util.h>

#include <dns/python/name_python.h>
#include <dns/python/rrclass_python.h>
#include <dns/python/rrtype_python.h>
#include <dns/python/rrset_python.h>
#include <dns/python/rrset_collection_python.h>
#include <dns/python/zone_checker_python.h>
#include <dns/python/pydnspp_common.h>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrset_collection_base.h>
#include <dns/zone_checker.h>

#include <boost/bind.hpp>

#include <cstring>
#include <string>
#include <stdexcept>

using std::string;
using isc::util::python::PyObjectContainer;
using namespace isc::dns;

namespace {
// This is a template for a common pattern of type mismatch error handling,
// provided to save typing and repeating the mostly identical patterns.
PyObject*
setTypeError(PyObject* pobj, const char* var_name, const char* type_name) {
    PyErr_Format(PyExc_TypeError, "%s must be a %s, not %.200s",
                 var_name, type_name, pobj->ob_type->tp_name);
    return (NULL);
}
}

namespace isc {
namespace dns {
namespace python {
namespace internal {

// Place the exception class in a named namespace to avoid weird run time
// failure with clang++.  See isc.log Python wrapper.
namespace clang_unnamed_namespace_workaround {
// This is used to abort check_zone() and go back to the top level.
// We use a separate exception so it won't be caught in the middle.
class InternalException : public std::exception {
};
}
using namespace clang_unnamed_namespace_workaround;

namespace {
// This is a "wrapper" RRsetCollection subclass.  It's constructed with
// a Python RRsetCollection object, and its find() calls the Python version
// of RRsetCollection.find().  This way, the check_zone() wrapper will work
// for pure-Python RRsetCollection classes, too.
class PyRRsetCollection : public RRsetCollectionBase {
public:
    PyRRsetCollection(PyObject* po_rrsets) : po_rrsets_(po_rrsets) {}

    virtual ConstRRsetPtr find(const Name& name, const RRClass& rrclass,
                               const RRType& rrtype) const {
        try {
            // Convert C++ args to Python objects, and builds argument tuple
            // to the Python method.  This should basically succeed.
            PyObjectContainer poc_name(createNameObject(name));
            PyObjectContainer poc_rrclass(createRRClassObject(rrclass));
            PyObjectContainer poc_rrtype(createRRTypeObject(rrtype));
            PyObjectContainer poc_args(Py_BuildValue("(OOOO)",
                                                     po_rrsets_,
                                                     poc_name.get(),
                                                     poc_rrclass.get(),
                                                     poc_rrtype.get()));

            // Call the Python method.
            // PyObject_CallMethod is dirty and requires mutable C-string for
            // method name and arguments.  While it's unlikely for these to
            // be modified, we err on the side of caution and make copies.
            char method_name[sizeof("find")];
            char method_args[sizeof("(OOO)")];
            std::strcpy(method_name, "find");
            std::strcpy(method_args, "(OOO)");
            PyObjectContainer poc_result(
                PyObject_CallMethod(po_rrsets_, method_name, method_args,
                                    poc_name.get(), poc_rrclass.get(),
                                    poc_rrtype.get()));
            PyObject* const po_result = poc_result.get();
            if (po_result == Py_None) {
                return (ConstRRsetPtr());
            } else if (PyRRset_Check(po_result)) {
                return (PyRRset_ToRRsetPtr(po_result));
            } else {
                PyErr_SetString(PyExc_TypeError, "invalid type for "
                                "RRsetCollection.find(): must be None "
                                "or RRset");
                throw InternalException();
            }
        } catch (const isc::util::python::PyCPPWrapperException& ex) {
            // This normally means the method call fails.  Propagate the
            // already-set Python error to the top level.  Other C++ exceptions
            // are really unexpected, so we also (implicitly) propagate it
            // to the top level and recognize it as "unexpected failure".
            throw InternalException();
        }
    }

    virtual IterPtr getBeginning() {
        isc_throw(NotImplemented, "iterator support is not yet available");
    }
    virtual IterPtr getEnd() {
        isc_throw(NotImplemented, "iterator support is not yet available");
    }

private:
    PyObject* const po_rrsets_;
};

void
callback(const string& reason, PyObject* obj) {
    PyObjectContainer poc_args(Py_BuildValue("(s#)", reason.c_str(),
                                             reason.size()));
    PyObject* po_result = PyObject_CallObject(obj, poc_args.get());
    if (po_result == NULL) {
        throw InternalException();
    }
    Py_DECREF(po_result);
}

ZoneCheckerCallbacks::IssueCallback
PyCallable_ToCallback(PyObject* obj) {
    if (obj == Py_None) {
        return (NULL);
    }
    return (boost::bind(callback, _1, obj));
}

}

PyObject*
pyCheckZone(PyObject*, PyObject* args) {
    try {
        PyObject* po_name;
        PyObject* po_rrclass;
        PyObject* po_rrsets;
        PyObject* po_error;
        PyObject* po_warn;

        if (PyArg_ParseTuple(args, "OOO(OO)", &po_name, &po_rrclass,
                             &po_rrsets, &po_error, &po_warn)) {
            if (!PyName_Check(po_name)) {
                return (setTypeError(po_name, "zone_name", "Name"));
            }
            if (!PyRRClass_Check(po_rrclass)) {
                return (setTypeError(po_rrclass, "zone_rrclass", "RRClass"));
            }
            if (!PyObject_TypeCheck(po_rrsets, &rrset_collection_base_type)) {
                return (setTypeError(po_rrsets, "zone_rrsets",
                                     "RRsetCollectionBase"));
            }
            if (po_error != Py_None && PyCallable_Check(po_error) == 0) {
                return (setTypeError(po_error, "error", "callable or None"));
            }
            if (po_warn != Py_None && PyCallable_Check(po_warn) == 0) {
                return (setTypeError(po_warn, "warn", "callable or None"));
            }

            PyRRsetCollection py_rrsets(po_rrsets);
            if (checkZone(PyName_ToName(po_name),
                          PyRRClass_ToRRClass(po_rrclass), py_rrsets,
                          ZoneCheckerCallbacks(
                              PyCallable_ToCallback(po_error),
                              PyCallable_ToCallback(po_warn)))) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
        }
    } catch (const InternalException& ex) {
        // Normally, error string should have been set already.  For some
        // rare cases such as memory allocation failure, we set the last-resort
        // error string.
        if (PyErr_Occurred() == NULL) {
            PyErr_SetString(PyExc_SystemError,
                            "Unexpected failure in check_zone()");
        }
        return (NULL);
    } catch (const std::exception& ex) {
        const string ex_what = "Unexpected failure in check_zone(): " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    }

    return (NULL);
}

} // namespace internal
} // namespace python
} // namespace dns
} // namespace isc
