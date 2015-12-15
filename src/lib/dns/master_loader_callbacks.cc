// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/master_loader_callbacks.h>

#include <string>

namespace isc {
namespace dns {

namespace {
void
nullCallback(const std::string&, size_t, const std::string&) {
}
}

MasterLoaderCallbacks
MasterLoaderCallbacks::getNullCallbacks() {
    return (MasterLoaderCallbacks(nullCallback, nullCallback));
}

} // end namespace dns
} // end namespace isc
