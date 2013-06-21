// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

// TODO - This is a temporary implementation of the hooks manager - it is
//        likely to be completely rewritte

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/library_manager_collection.h>
#include <hooks/hooks_manager.h>
#include <hooks/server_hooks.h>

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

using namespace std;

namespace isc {
namespace hooks {

// Constructor

HooksManager::HooksManager() {
}

// Return reference to singleton hooks manager.

HooksManager&
HooksManager::getHooksManager() {
    static HooksManager manager;
    return (manager);
}

// Perform conditional initialization if nothing is loaded.

void
HooksManager::conditionallyInitialize() {
    if (!lm_collection_) {

        // Nothing present, so create the collection with any empty set of
        // libraries, and get the CalloutManager.
        vector<string> libraries;
        lm_collection_.reset(new LibraryManagerCollection(libraries));
        lm_collection_->loadLibraries();

        callout_manager_ = lm_collection_->getCalloutManager();
    }
}

// Create a callout handle

boost::shared_ptr<CalloutHandle>
HooksManager::createCalloutHandleInternal() {
    conditionallyInitialize();
    return (boost::shared_ptr<CalloutHandle>(
                             new CalloutHandle(callout_manager_)));
}

boost::shared_ptr<CalloutHandle>
HooksManager::createCalloutHandle() {
    return (getHooksManager().createCalloutHandleInternal());
}

// Are callouts present?

bool
HooksManager::calloutsPresentInternal(int index) {
    conditionallyInitialize();
    return (callout_manager_->calloutsPresent(index));
}

bool
HooksManager::calloutsPresent(int index) {
    return (getHooksManager().calloutsPresentInternal(index));
}

// Call the callouts

void
HooksManager::callCalloutsInternal(int index, CalloutHandle& handle) {
    conditionallyInitialize();
    return (callout_manager_->callCallouts(index, handle));
}

void
HooksManager::callCallouts(int index, CalloutHandle& handle) {
    return (getHooksManager().callCalloutsInternal(index, handle));
}




} // namespace util
} // namespace isc
