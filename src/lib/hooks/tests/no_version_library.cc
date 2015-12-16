// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief No version function library
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// - No version() function is present.

extern "C" {

int no_version() {
    return (0);
}

};
