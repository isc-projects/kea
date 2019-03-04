// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>
#include <hooks/hooks.h>
#include <mysql_cb_dhcp4.h>

using namespace isc::hooks;

extern "C" {

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise

int load(LibraryHandle& /* handle */) {

    // Register MySQL CB factory with CB Manager
    isc::dhcp::MySqlConfigBackendDHCPv4::registerBackendType();

    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {

    // Unregister the factory and remove MySQL backends
    isc::dhcp::MySqlConfigBackendDHCPv4::unregisterBackendType();
    return (0);
}


} // end extern "C"
