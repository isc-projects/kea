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

#ifndef LIBDNS_PYTHON_TOWIRE_H
#define LIBDNS_PYTHON_TOWIRE_H 1

#include <Python.h>

#include <stdexcept>
#include <string>

#include <dns/messagerenderer.h>

#include <util/buffer.h>
#include <util/python/pycppwrapper_util.h>

#include "messagerenderer_python.h"

namespace isc {
namespace dns {
namespace python {

// The following two templated structures are a helper to use the same
// toWire() template implementation for two types of toWire() methods:
// return an integer or have no return value.
template <typename CPPCLASS>
struct ToWireCallVoid {
    ToWireCallVoid(CPPCLASS& cppobj) : cppobj_(cppobj) {}
    int operator()(AbstractMessageRenderer& renderer) const {
        cppobj_.toWire(renderer);
        return (0);
    }
    const CPPCLASS& cppobj_;
};

template <typename CPPCLASS>
struct ToWireCallInt {
    ToWireCallInt(CPPCLASS& cppobj) : cppobj_(cppobj) {}
    int operator()(AbstractMessageRenderer& renderer) const {
        return (cppobj_.toWire(renderer));
    }
    const CPPCLASS& cppobj_;
};

// This templated function gives a common implementation of the toWire()
// wrapper for various libdns++ classes.  PYSTRUCT and CPPCLASS are
// (C++ binding of) python and (pure) C++ classes (e.g., s_Name and Name),
// and TOWIRECALLER is either ToWireCallVoid<CPPCLASS> or
// ToWireCallInt<CPPCLASS>, depending on the toWire() method of the class
// returns a value or not.
//
// See, e.g., tsigrecord_python.cc for how to use it.
//
// This should be able to be used without modification for most classes that
// have toWire().  But if the underlying toWire() has an extra argument, the
// definition will need to be adjusted accordingly.
template <typename PYSTRUCT, typename CPPCLASS, typename TOWIRECALLER>
PyObject*
toWireWrapper(const PYSTRUCT* const self, PyObject* args) {
    try {
        // To OutputBuffer version
        PyObject* bytes; // this won't have own reference, no risk of leak.
        if (PyArg_ParseTuple(args, "O", &bytes) && PySequence_Check(bytes)) {
            // render the object into a buffer (this can throw)
            isc::util::OutputBuffer buffer(0);
            self->cppobj->toWire(buffer);

            // convert the rendered data into PyObject.  This could leak later,
            // so we need to store it in a container.
            PyObject* rd_bytes = PyBytes_FromStringAndSize(
                static_cast<const char*>(buffer.getData()),
                buffer.getLength());
            isc::util::python::PyObjectContainer rd_bytes_container(rd_bytes);

            // concat the latest data to the given existing sequence.  concat
            // operation could fail, so we use a container to clean it up
            // safely should that happen.
            PyObject* result = PySequence_InPlaceConcat(bytes, rd_bytes);
            isc::util::python::PyObjectContainer result_container(result);

            return (result_container.release());
        }

        // To MessageRenderer version
        PyObject* renderer;
        if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, &renderer)) {
            const unsigned int n = TOWIRECALLER(*self->cppobj)(
                PyMessageRenderer_ToMessageRenderer(renderer));

            return (Py_BuildValue("I", n));
        }
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Failed to render an libdns++ object wire-format: "
            + std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpectedly failed to render an "
                        "libdns++ object wire-format.");
        return (NULL);
    }

    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "Incorrect arguments for a to_wire() method");
    return (NULL);
}
} // namespace python
} // namespace dns
} // namespace isc
#endif // LIBDNS_PYTHON_TOWIRE_H

// Local Variables:
// mode: c++
// End:
