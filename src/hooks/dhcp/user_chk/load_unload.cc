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

using namespace isc::hooks;

UserRegistryPtr user_registry;

extern "C" {

int load(LibraryHandle&) {
    // @todo what about exception handling

    // Instantiate the registry.
    user_registry.reset(new UserRegistry());

    // Create the data source.
    UserDataSourcePtr user_file(new UserFile("/tmp/user_registry.txt"));

    // Set the registry's data source
    user_registry->setSource(user_file);

    // Do an initial load of the registry.
    user_registry->refresh();
    return (0);
}

int unload() {
    user_registry.reset();
    return (0);
}

}
