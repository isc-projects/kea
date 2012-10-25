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

#ifndef PYTHON_MESSAGE_H
#define PYTHON_MESSAGE_H 1

#include <Python.h>

namespace isc {
namespace dns {
class Message;

namespace python {

extern PyObject* po_MessageTooShort;
extern PyObject* po_InvalidMessageSection;
extern PyObject* po_InvalidMessageOperation;
extern PyObject* po_InvalidMessageUDPSize;

extern PyTypeObject message_type;

} // namespace python
} // namespace dns
} // namespace isc
#endif // PYTHON_MESSAGE_H

// Local Variables:
// mode: c++
// End:
