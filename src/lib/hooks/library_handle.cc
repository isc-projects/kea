// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>

namespace isc {
namespace hooks {

// Callout manipulation - all deferred to the CalloutManager.

void
LibraryHandle::registerCallout(const std::string& name, CalloutPtr callout) {
    // Reset library index if required, saving the current value.
    int saved_index = callout_manager_->getLibraryIndex();
    if (index_ >= 0) {
        callout_manager_->setLibraryIndex(index_);
    }

    // Register the callout.
    callout_manager_->registerCallout(name, callout);

    // Restore the library index if required.  We know that the saved index
    // is valid for the number of libraries (or is -1, which is an internal
    // state indicating there is no current library index) as we obtained it
    // from the callout manager.
    if (index_ >= 0) {
        callout_manager_->setLibraryIndex(saved_index);
    }
}

bool
LibraryHandle::deregisterCallout(const std::string& name, CalloutPtr callout) {
    int saved_index = callout_manager_->getLibraryIndex();
    if (index_ >= 0) {
        callout_manager_->setLibraryIndex(index_);
    }

    bool status = callout_manager_->deregisterCallout(name, callout);

    if (index_ >= 0) {
        callout_manager_->setLibraryIndex(saved_index);
    }

    return (status);
}

bool
LibraryHandle::deregisterAllCallouts(const std::string& name) {
    int saved_index = callout_manager_->getLibraryIndex();
    if (index_ >= 0) {
        callout_manager_->setLibraryIndex(index_);
    }

    bool status = callout_manager_->deregisterAllCallouts(name);

    if (index_ >= 0) {
        callout_manager_->setLibraryIndex(saved_index);
    }

    return (status);
}

} // namespace util
} // namespace isc
