// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef POPTION_H
#define POPTION_H 1

#include <Python.h>

#include <dhcp/option.h>

namespace isc {
namespace python {

// Python option class
class py_option : public PyObject  {
    py_option();

public:
    isc::dhcp::OptionPtr object;
};

extern PyTypeObject option_type;

bool initmod_option(PyObject* mod);

} // namespace python
} // namespace isc

#endif // POPTION_H
