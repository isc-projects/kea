// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PPKT4_H
#define PPKT4_H 1

#include <Python.h>

#include <dhcp/pkt4.h>

namespace isc {
namespace python {

// Python pkt4 class
class py_pkt4 : public PyObject  {
    py_pkt4();

public:
    isc::dhcp::Pkt4Ptr object;
};

extern PyTypeObject pkt4_type;

bool initmod_pkt4(PyObject* mod);

} // namespace python
} // namespace isc

#endif // PPKT4_H
