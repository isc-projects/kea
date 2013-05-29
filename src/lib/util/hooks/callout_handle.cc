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
#include <util/hooks/library_handle.h>

#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace isc::util;

namespace isc {
namespace util {

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

// Return the "current" library handle.

LibraryHandle&
CalloutHandle::getLibraryHandle() const {
    boost::shared_ptr<LibraryHandle> handle =
        library_collection_->getLibraryHandle();

    // Return refernce to this library handle.  This remains valid even
    // after this method returns, because this object maintains a shared
    // pointer to the LibraryHandleCollection, which in turn maintains
    // a shared pointer to the LibraryHandle in question.

    return (*handle);
}

// Check the current library index.

int
CalloutHandle::getLibraryIndex() const {
    int curidx = library_collection_->getLibraryIndex();
    if (curidx < 0) {
        isc_throw(InvalidIndex, "current library handle index is not valid");
    }

    return (curidx);
}

// Return the context for the currently pointed-to library.  This version is
// used by the "setContext()" method and creates a context for the current
// library if it does not exist.

CalloutHandle::ElementCollection&
CalloutHandle::getContextForLibrary() {

    int libindex = getLibraryIndex();

    // Access a reference to the element collection for the given index,
    // creating a new element collection if necessary, and return it.
    return (context_collection_[libindex]);
}

// The "const" version of the above, used by the "getContext()" method.  If
// the context for the current library doesn't exist, throw a
// "NoSuchCalloutContext" exception.

const CalloutHandle::ElementCollection&
CalloutHandle::getContextForLibrary() const {

    int libindex = getLibraryIndex();
    ContextCollection::const_iterator libcontext =
        context_collection_.find(libindex);
    if (libcontext == context_collection_.end()) {
        isc_throw(NoSuchCalloutContext, "unable to find callout context "
                  "associated with the current library handle");
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
