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

// $Id$

#include <Python.h>
#include <pydnspp_common.h>

int
readDataFromSequence(uint8_t *data, size_t len, PyObject* sequence) {
    PyObject* el = NULL;
    for (size_t i = 0; i < len; i++) {
        el = PySequence_GetItem(sequence, i);
        if (!el) {
            PyErr_SetString(PyExc_TypeError,
                "sequence too short");
            return (-1);
        }
        if (PyLong_Check(el)) {
            long l = PyLong_AsLong(el);
            if (l < 0 || l > 255) {
                PyErr_SetString(PyExc_TypeError,
                    "number in fromWire sequence not between 0 and 255");
                return (-1);
            }
            data[i] = static_cast<uint8_t>(PyLong_AsLong(el));
        } else {
            PyErr_SetString(PyExc_TypeError,
                "not a number in fromWire sequence");
            return (-1);
        }
    }
    PySequence_DelSlice(sequence, 0, len);
    return (0);
}


void addClassVariable(PyTypeObject& c, const char* name,
                      PyObject* obj)
{
    PyDict_SetItemString(c.tp_dict, name, obj);
}
