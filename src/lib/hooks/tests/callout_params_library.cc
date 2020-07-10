// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Callout Library
///
/// This is the source of a test library for the DHCP parser tests that
/// specify parameters. It will attempt to obtain its own parameters.

#include <config.h>
#include <hooks/hooks.h>
#include <iostream>

using namespace std;
using namespace isc::hooks;
using namespace isc::data;

extern "C" {

// Framework functions
int
version() {
    return (KEA_HOOKS_VERSION);
}

/// @brief This method will be called when the hook library is loaded
///
/// While its primary usage is for unit-testing, it also doubles as an
/// illustration referred to from Hooks Developer's Guide. As such, please
/// keep it simple, tidy and try to avoid referencing unnecessary code.
/// Parts of it can be used as copy-paste examples.
///
/// @param handle passed by the hooks framework
/// @return 0 if load was successful, non-zero for errors
int load(LibraryHandle& handle) {
    ConstElementPtr elems        = handle.getParameters();
    ConstElementPtr string_elem  = handle.getParameter("svalue");
    ConstElementPtr int_elem     = handle.getParameter("ivalue");
    ConstElementPtr bool_elem    = handle.getParameter("bvalue");
    ConstElementPtr nonexistent  = handle.getParameter("nonexistent");
    vector<string>  names        = handle.getParameterNames();

    // String handling example.
    if (!string_elem) {
        // Parameter was not specified at all.
        return (1);
    }

    if (string_elem->getType() != Element::string) {
        // Parameter is specified, but it's not a string.
        return (2);
    }

    string str = string_elem->stringValue();
    if (str != "string value") {
        // Parameter is specified, is a string, but has unexpected value.
        //
        // This library is used for testing, so it expects exact value of the
        // parameter. Normal library would likely use whatever value user
        // specified.
        return (3);
    }

    // Integer handling example
    if (!int_elem) {
        // Parameter was not specified at all.
        return (4);
    }

    if (int_elem->getType() != Element::integer) {
        // Parameter is specified, but it's not an integer.
        return (5);
    }

    int int_value = int_elem->intValue();
    if (int_value != 42) {
        // Parameter specified, is an integer, but has a value different than
        // expected.
        return (6);
    }

    // Boolean handling example
    if (!bool_elem) {
        // Parameter was not specified at all.
        return (7);
    }

    if (bool_elem->getType() != Element::boolean) {
        // Parameter is specified, but it's not a boolean.
        return (8);
    }

    bool flag = bool_elem->boolValue();
    if (flag != true) {
        // Parameter specified, is a boolean, but has a value different than
        // expected.
        return (9);
    }

    // Check names. As a side effect of what maps using strings are
    // implemented names are sorted in alphabetical order.
    if ((names.size() != 3) || (names[0] != "bvalue") ||
        (names[1] != "ivalue") || (names[2] != "svalue")) {
        // Expect 3 names: bvalue, ivalue, svalue.
        return (10);
    }

    // Check elems map.
    if (!elems) {
        return (11);
    }
    string expected_str = "{ "
        "\"bvalue\": true, "
        "\"ivalue\": 42, "
        "\"svalue\": \"string value\""
        " }";
    if (expected_str != elems->str()) {
        return (12);
    }

    // All validation steps were successful. The library has all the parameters
    // it needs, so we should report a success.
    return (0);
}

}
