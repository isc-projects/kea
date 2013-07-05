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

#include <hooks/callout_manager.h>
#include <hooks/library_manager.h>
#include <hooks/library_manager_collection.h>

namespace isc {
namespace hooks {

// Return callout manager for the loaded libraries.  This call is only valid
// after one has been created for the loaded libraries (which includes the
// case of no loaded libraries).
//
// Note that there is no real connection between the callout manager and the
// libraries, other than it knows the number of libraries so can do sanity
// checks on values passed to it.  However, this may change in the future,
// so the hooks framework is written such that a callout manager is used only
// with the LibraryManagerCollection that created it.  It is also the reason
// why each LibraryManager contains a pointer to this CalloutManager.

boost::shared_ptr<CalloutManager>
LibraryManagerCollection::getCalloutManager() const {

    // Only return a pointer if we have a CalloutManager created.
    if (! callout_manager_) {
        isc_throw(LoadLibrariesNotCalled, "must load hooks libraries before "
                  "attempting to retrieve a CalloutManager for them");
    }

    return (callout_manager_);
}

// Load a set of libraries

bool
LibraryManagerCollection::loadLibraries() {

    // Unload libraries if any are loaded.
    static_cast<void>(unloadLibraries());

    // Create the callout manager.  A pointer to this is maintained by
    // each library.  Note that the callout manager does not hold any memory
    // allocated by a library: although a library registers a callout (and so
    // causes the creation of an entry in the CalloutManager's callout list),
    // that creation is done by the CalloutManager itself.  The CalloutManager
    // is created within the server.
    //
    // The upshot of this is that it is therefore safe for the CalloutManager
    // to be deleted after all associated libraries are deleted, hence this
    // link (LibraryManager -> CalloutManager) is safe.
    callout_manager_.reset(new CalloutManager(library_names_.size()));

    // Now iterate through the libraries are load them one by one.  We'll
    for (int i = 0; i < library_names_.size(); ++i) {
        // Create a pointer to the new library manager.  The index of this
        // library is determined by the number of library managers currently
        // loaded: note that the library indexes run from 1 to (number of loaded
        // libraries).
        boost::shared_ptr<LibraryManager> manager(
                new LibraryManager(library_names_[i], lib_managers_.size() + 1,
                                   callout_manager_));

        // Load the library.  On success, add it to the list of loaded
        // libraries.  On failure, an error will have been logged and the
        // library closed.
        if (manager->loadLibrary()) {
            lib_managers_.push_back(manager);
        }
    }

    // Update the CalloutManager's idea of the number of libraries it is
    // handling.
    callout_manager_->setNumLibraries(lib_managers_.size());

    // Get an indication of whether all libraries loaded successfully.
    bool status = (library_names_.size() == lib_managers_.size());

    // Don't need the library names any more, so free up the space.
    library_names_.clear();

    return (status);
}

// Unload the libraries.

void
LibraryManagerCollection::unloadLibraries() {

    // Delete the library managers in the reverse order to which they were
    // created, then clear the library manager vector.
    for (int i = lib_managers_.size() - 1; i >= 0; --i) {
        lib_managers_[i].reset();
    }
    lib_managers_.clear();

    // Get rid of the callout manager. (The other member, the list of library
    // names, was cleared when the libraries were loaded.)
    callout_manager_.reset();
}

} // namespace hooks
} // namespace isc
