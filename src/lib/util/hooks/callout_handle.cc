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

#include <util/hooks/callout_handle.h>
#include <util/hooks/callout_manager.h>
#include <util/hooks/library_handle.h>
#include <util/hooks/server_hooks.h>

#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace isc::util;

namespace isc {
namespace util {

// Constructor.
CalloutHandle::CalloutHandle(const boost::shared_ptr<CalloutManager>& manager)
    : arguments_(), context_collection_(), manager_(manager), skip_(false) {

    // Call the "context_create" hook.  We should be OK doing this - although
    // the constructor has not finished running, all the member variables
    // have been created.
    int status = manager_->callCallouts(ServerHooks::CONTEXT_CREATE, *this);
    if (status > 0) {
        isc_throw(ContextCreateFail, "error code of " << status << " returned "
                  "from context_create callout during the creation of a "
                  "ContextHandle object");
    }
}

// Destructor
CalloutHandle::~CalloutHandle() {

    // Call the "context_destroy" hook.  We should be OK doing this - although
    // the destructor is being called, all the member variables are still in
    // existence.
    int status = manager_->callCallouts(ServerHooks::CONTEXT_DESTROY, *this);
    if (status > 0) {
        // An exception is thrown on failure.  This may be severe, but if
        // none is thrown a resource leak in a library (signalled by the
        // context_destroy callout returning an error) may be difficult to
        // trace.
        isc_throw(ContextDestroyFail, "error code of " << status << " returned "
                  "from context_destroy callout during the destruction of a "
                  "ContextHandle object");
    }
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

} // namespace util
} // namespace isc
