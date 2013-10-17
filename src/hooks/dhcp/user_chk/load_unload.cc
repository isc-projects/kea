// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
// load_unload.cc

#include <hooks/hooks.h>
#include <user_registry.h>
#include <user_file.h>

#include <iostream>
#include <fstream>
#include <errno.h>

using namespace isc::hooks;

UserRegistryPtr user_registry;
std::fstream user_chk_output;
const char* registry_fname = "/tmp/user_registry.txt";
const char* user_chk_output_fname = "/tmp/user_check_output.txt";

extern "C" {

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
        int sav_errno = errno;
        if (!user_chk_output) {
            isc_throw(isc::Unexpected, "Cannot open output file: "
                                       << user_chk_output_fname
                                       << " reason: " << strerror(sav_errno));
        }
    }
    catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook could not be loaded: "
                  << ex.what() << std::endl;
        ret_val = 1;
    }

    return (ret_val);
}

int unload() {
    try {
        user_registry.reset();
        if (user_chk_output.is_open()) {
            user_chk_output.close();
        }
    } catch (const std::exception& ex) {
        // On the off chance something goes awry, catch it and log it.
        // @todo Not sure if we should return a non-zero result or not.
        std::cout << "DHCP UserCheckHook could not be unloaded: "
                  << ex.what() << std::endl;
    }

    return (0);
}

}
