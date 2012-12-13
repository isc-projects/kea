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

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>

#include "pydnspp_common.h"
#include "messagerenderer_python.h"
#include "name_python.h"
#include "rdata_python.h"
#include "rrclass_python.h"
#include "rrtype_python.h"
#include "rrttl_python.h"
#include "rrset_python.h"
#include "rcode_python.h"
#include "opcode_python.h"
#include "tsigkey_python.h"
#include "tsig_rdata_python.h"
#include "tsigerror_python.h"
#include "tsigrecord_python.h"
#include "tsig_python.h"
#include "question_python.h"
#include "message_python.h"

using namespace isc::dns::python;

namespace isc {
namespace dns {
namespace python {
// For our 'general' isc::Exceptions
PyObject* po_IscException;
PyObject* po_InvalidOperation;
PyObject* po_InvalidParameter;

// For our own isc::dns::Exception
PyObject* po_DNSMessageBADVERS;


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


int
addClassVariable(PyTypeObject& c, const char* name, PyObject* obj) {
    if (obj == NULL) {
        PyErr_SetString(PyExc_ValueError,
                        "NULL object is specified for a class variable");
        return (-1);
    }
    return (PyDict_SetItemString(c.tp_dict, name, obj));
}
}
}
}
