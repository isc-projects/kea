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

#ifndef __PYTHON_MESSAGERENDERER_H
#define __PYTHON_MESSAGERENDERER_H 1

#include <Python.h>

#include <dns/messagerenderer.h>
#include <util/buffer.h>

namespace isc {
namespace dns {
namespace python {

// The s_* Class simply covers one instantiation of the object.
//
// since we don't use *Buffer in the python version (but work with
// the already existing bytearray type where we use these custom buffers
// in C++, we need to keep track of one here.
class s_MessageRenderer : public PyObject {
public:
    s_MessageRenderer();
    isc::util::OutputBuffer* outputbuffer;
    MessageRenderer* messagerenderer;
};

extern PyTypeObject messagerenderer_type;

bool initModulePart_MessageRenderer(PyObject* mod);

} // namespace python
} // namespace dns
} // namespace isc
#endif // __PYTHON_MESSAGERENDERER_H

// Local Variables:
// mode: c++
// End:
