// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_HOOKS_EXPORT

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
