// Copyright (C) 2013,2015  Internet Systems Consortium, Inc. ("ISC")
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
      next_step_(NEXT_STEP_CONTINUE) {

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

// Return the library handle allowing the callout to access the CalloutManager
// registration/deregistration functions.

LibraryHandle&
CalloutHandle::getLibraryHandle() const {
    return (manager_->getLibraryHandle());
}

// Return the context for the currently pointed-to library.  This version is
// used by the "setContext()" method and creates a context for the current
// library if it does not exist.

CalloutHandle::ElementCollection&
CalloutHandle::getContextForLibrary() {
    int libindex = manager_->getLibraryIndex();

    // Access a reference to the element collection for the given index,
    // creating a new element collection if necessary, and return it.
    return (context_collection_[libindex]);
}

// The "const" version of the above, used by the "getContext()" method.  If
// the context for the current library doesn't exist, throw an exception.

const CalloutHandle::ElementCollection&
CalloutHandle::getContextForLibrary() const {
    int libindex = manager_->getLibraryIndex();

    ContextCollection::const_iterator libcontext =
        context_collection_.find(libindex);
    if (libcontext == context_collection_.end()) {
        isc_throw(NoSuchCalloutContext, "unable to find callout context "
                  "associated with the current library index (" << libindex <<
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
    // Get the current hook index.
    int index = manager_->getHookIndex();

    // ... and look up the hook.
    string hook = "";
    try {
        hook = server_hooks_.getName(index);
    } catch (const NoSuchHook&) {
        // Hook index is invalid, so this methods probably called from outside
        // a callout being executed via a call to CalloutManager::callCallouts.
        // In this case, the empty string is returned.
    }

    return (hook);
}

} // namespace util
} // namespace isc
