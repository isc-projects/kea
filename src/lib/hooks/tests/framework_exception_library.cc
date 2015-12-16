// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Framework exception library
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// - All three framework functions are supplied (version(), load() and
///   unload()) and all generate an exception.

#include <config.h>

#include <hooks/hooks.h>

#include <exception>

extern "C" {

int
version() {
    throw std::exception();
}

int
load(isc::hooks::LibraryHandle& /*handle*/) {
    throw std::exception();
}

int
unload() {
    throw std::exception();
}

};

