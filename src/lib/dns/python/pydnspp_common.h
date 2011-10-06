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

#ifndef __LIBDNS_PYTHON_COMMON_H
#define __LIBDNS_PYTHON_COMMON_H 1

#include <Python.h>

#include <stdexcept>
#include <string>

namespace isc {
namespace dns {
namespace python {
// For our 'general' isc::Exceptions
extern PyObject* po_IscException;
extern PyObject* po_InvalidParameter;

// For our own isc::dns::Exception
extern PyObject* po_DNSMessageBADVERS;

// This function reads 'bytes' from a sequence
// This sequence can be anything that implements the Sequence interface,
// but must consist of Numbers between 0 and 255 for every value.
//
// The data is stored in *data.
// Data must be allocated and have at least len bytes available.
//
// The current implementation removes read items from the
// head of the sequence, unless it fails (and returns -1), in which
// case nothing is removed
int readDataFromSequence(uint8_t *data, size_t len, PyObject* sequence);

int addClassVariable(PyTypeObject& c, const char* name, PyObject* obj);
} // namespace python
} // namespace dns
} // namespace isc
#endif // __LIBDNS_PYTHON_COMMON_H

// Local Variables:
// mode: c++
// End:
