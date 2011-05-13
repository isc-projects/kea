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

#include <Python.h>

#include <stdint.h>

// see util/time_utilities.h
namespace isc {
namespace util {
namespace detail {
extern int64_t (*gettimeFunction)();
}
}
}

namespace {
int64_t fake_current_time;

int64_t
getFakeTime() {
    return (fake_current_time);
}

PyObject*
fixCurrentTime(PyObject*, PyObject* args) {
    PyObject* maybe_none;
    if (PyArg_ParseTuple(args, "L", &fake_current_time)) {
        isc::util::detail::gettimeFunction = getFakeTime;
    } else if (PyArg_ParseTuple(args, "O", &maybe_none) &&
               maybe_none == Py_None) {
        isc::util::detail::gettimeFunction = NULL;
    } else {
         PyErr_SetString(PyExc_TypeError, "Invalid arguments to "
                         "pyunittests_util.fix_current_time");
         return (NULL);
    }

    PyErr_Clear();
    Py_RETURN_NONE;
}

PyMethodDef PyUnittestsUtilMethods[] = {
    { "fix_current_time", fixCurrentTime, METH_VARARGS,
      "Fix the current system time at the specified (fake) value.\n\n"
      "This is useful for testing modules that depend on the current time.\n"
      "Note that it only affects C++ modules that use gettimeWrapper() "
      "defined in libutil, which allows a hook for testing.\n"
      "If an integer (signed 64bit) is given, the current time will be fixed "
      "to that value; if None is specified (which is the default) the use of "
      "faked time will be canceled."
    },
    { NULL, NULL, 0, NULL}
};

PyModuleDef pyunittests_util = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "pyunittests_util",
    "This module is a collection of utilities useful for testing "
    "the BIND 10 C++ binding modules.",
    -1,
    PyUnittestsUtilMethods,
    NULL,
    NULL,
    NULL,
    NULL
};
} // end of unnamed namespace

PyMODINIT_FUNC
PyInit_pyunittests_util(void) {
    return (PyModule_Create(&pyunittests_util));
}
