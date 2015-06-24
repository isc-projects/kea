// Copyright (C) 2013,2015 Internet Systems Consortium, Inc. ("ISC")
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

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>

#include <hooks/hooks.h>
#include <user_chk_log.h>
#include <user_registry.h>
#include <user_file.h>

#include <iostream>
#include <fstream>
#include <errno.h>

using namespace isc::hooks;
using namespace user_chk;

/// @brief Pointer to the registry instance.
UserRegistryPtr user_registry;

/// @brief Output filestream for recording user check outcomes.
std::fstream user_chk_output;

/// @brief User registry input file name.
/// @todo Hard-coded for now, this should be configurable.
const char* registry_fname = "/tmp/user_chk_registry.txt";

/// @brief User check outcome file name.
/// @todo Hard-coded for now, this should be configurable.
const char* user_chk_output_fname = "/tmp/user_chk_outcome.txt";

/// @brief Text label of user id in the inbound query in callout context
const char* query_user_id_label = "query_user_id";

/// @brief Text label of registered user pointer in callout context
const char* registered_user_label = "registered_user";

/// @brief Text id used to identify the default IPv4 user in the registry
/// The format is a string containing an even number of hex digits.  This
/// value is to look up the default IPv4 user in the user registry for the
/// the purpose of retrieving default values for user options.
const char* default_user4_id_str = "00000000";

/// @brief Text id used to identify the default IPv6 user in the registry
/// The format is a string containing an even number of hex digits.  This
/// value is to look up the default IPv6 user in the user registry for the
/// the purpose of retrieving default values for user options.
const char *default_user6_id_str = "00000000";

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Called by the Hooks library manager when the library is loaded.
///
/// Instantiates the UserRegistry and opens the outcome file. Failure in
/// either results in a failed return code.
///
/// @return Returns 0 upon success, non-zero upon failure.
int load(LibraryHandle&) {
    // non-zero indicates an error.
    int ret_val = 0;
    try {
        // Instantiate the registry.
        user_registry.reset(new UserRegistry());

        // Create the data source.
        UserDataSourcePtr user_file(new UserFile(registry_fname));

        // Set the registry's data source
        user_registry->setSource(user_file);

        // Do an initial load of the registry.
        user_registry->refresh();

        // Open up the output file for user_chk results.
        user_chk_output.open(user_chk_output_fname,
                     std::fstream::out | std::fstream::app);

        if (!user_chk_output) {
            // Grab the system error message.
            const char* errmsg = strerror(errno);
            isc_throw(isc::Unexpected, "Cannot open output file: "
                                       << user_chk_output_fname
                                       << " reason: " << errmsg);
        }
    }
    catch (const std::exception& ex) {
        // Log the error and return failure.
        LOG_ERROR(user_chk_logger, USER_CHK_HOOK_LOAD_ERROR)
            .arg(ex.what());
        ret_val = 1;
    }

    return (ret_val);
}

/// @brief Called by the Hooks library manager when the library is unloaded.
///
/// Destroys the UserRegistry and closes the outcome file.
///
/// @return Always returns 0.
int unload() {
    try {
        user_registry.reset();
        if (user_chk_output.is_open()) {
            user_chk_output.close();
        }
    } catch (const std::exception& ex) {
        // On the off chance something goes awry, catch it and log it.
        // @todo Not sure if we should return a non-zero result or not.
        LOG_ERROR(user_chk_logger, USER_CHK_HOOK_UNLOAD_ERROR)
            .arg(ex.what());
    }

    return (0);
}

}
