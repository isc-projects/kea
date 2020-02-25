// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/server_hooks.h>

#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace isc {
namespace hooks {

// Constructor.
CalloutHandle::CalloutHandle(const boost::shared_ptr<CalloutManager>& manager,
                    const boost::shared_ptr<LibraryManagerCollection>& lmcoll)
    : lm_collection_(lmcoll), arguments_(), context_collection_(),
      manager_(manager), server_hooks_(ServerHooks::getServerHooks()),
      current_library_(-1), current_hook_(-1), next_step_(NEXT_STEP_CONTINUE) {

    // Call the "context_create" hook.  We should be OK doing this - although
    // the constructor has not finished running, all the member variables
    // have been created.
    manager_->callCallouts(ServerHooks::CONTEXT_CREATE, *this);
}

// Destructor
CalloutHandle::~CalloutHandle() {
    // Call the "context_destroy" hook.  We should be OK doing this - although
    // the destructor is being called, all the member variables are still in
    // existence.
    manager_->callCallouts(ServerHooks::CONTEXT_DESTROY, *this);

    // Explicitly clear the argument and context objects.  This should free up
    // all memory that could have been allocated by libraries that were loaded.
    arguments_.clear();
    context_collection_.clear();

    // Normal destruction of the remaining variables will include the
    // destruction of lm_collection_, an action that decrements the reference
    // count on the library manager collection (which holds the libraries that
    // could have allocated memory in the argument and context members.)  When
    // that goes to zero, the libraries will be unloaded: at that point nothing
    // in the hooks framework will be pointing to memory in the libraries'
    // address space.
    //
    // It is possible that some other data structure in the server (the program
    // using the hooks library) still references the address space and attempts
    // to access it causing a segmentation fault. That issue is outside the
    // scope of this framework and is not addressed by it.
}

// Return the name of all argument items.

vector<string>
CalloutHandle::getArgumentNames() const {
    vector<string> names;
    for (ElementCollection::const_iterator i = arguments_.begin();
         i != arguments_.end(); ++i) {
        names.push_back(i->first);
    }

    return (names);
}

ParkingLotHandlePtr
CalloutHandle::getParkingLotHandlePtr() const {
    return (boost::make_shared<ParkingLotHandle>(server_hooks_.getParkingLotPtr(current_hook_)));
}

// Return the context for the currently pointed-to library.  This version is
// used by the "setContext()" method and creates a context for the current
// library if it does not exist.

CalloutHandle::ElementCollection&
CalloutHandle::getContextForLibrary() {
    // Access a reference to the element collection for the given index,
    // creating a new element collection if necessary, and return it.
    return (context_collection_[current_library_]);
}

// The "const" version of the above, used by the "getContext()" method.  If
// the context for the current library doesn't exist, throw an exception.

const CalloutHandle::ElementCollection&
CalloutHandle::getContextForLibrary() const {
    auto libcontext = context_collection_.find(current_library_);
    if (libcontext == context_collection_.end()) {
        isc_throw(NoSuchCalloutContext, "unable to find callout context "
                  "associated with the current library index (" << current_library_ <<
                  ")");
    }

    // Return a reference to the context's element collection.
    return (libcontext->second);
}

// Return the name of all items in the context associated with the current]
// library.

vector<string>
CalloutHandle::getContextNames() const {
    vector<string> names;
    const ElementCollection& elements = getContextForLibrary();
    for (ElementCollection::const_iterator i = elements.begin();
         i != elements.end(); ++i) {
        names.push_back(i->first);
    }

    return (names);
}

// Return name of current hook (the hook to which the current callout is
// attached) or the empty string if not called within the context of a
// callout.

string
CalloutHandle::getHookName() const {
    string hook = "";
    try {
        hook = server_hooks_.getName(current_hook_);
    } catch (const NoSuchHook&) {
        // Hook index is invalid, so this methods probably called from outside
        // a callout being executed via a call to CalloutManager::callCallouts.
        // In this case, the empty string is returned.
    }

    return (hook);
}

ScopedCalloutHandleState::
ScopedCalloutHandleState(const CalloutHandlePtr& callout_handle)
    : callout_handle_(callout_handle) {
    if (!callout_handle_) {
        isc_throw(BadValue, "callout_handle argument must not be null");
    }

    resetState();
}

ScopedCalloutHandleState::~ScopedCalloutHandleState() {
    resetState();
}

void
ScopedCalloutHandleState::resetState() {
    // No need to check if the handle is null because the constructor
    // already checked that.
    callout_handle_->deleteAllArguments();
    callout_handle_->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
}

} // namespace hooks
} // namespace isc
