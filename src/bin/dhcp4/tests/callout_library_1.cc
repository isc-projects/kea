// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Marker file callout library
///
/// This is the source of a test library for the DHCP parser and configuration
/// tests.  See callout_common.cc for details.

static const int LIBRARY_NUMBER = 1;
#include <config.h>

#include <dhcp4/tests/callout_library_common.h>

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

int (*do_load)(isc::hooks::LibraryHandle& handle);

int (*do_unload)(isc::hooks::LibraryHandle& handle);

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
