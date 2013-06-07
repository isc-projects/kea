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

#ifndef CALLOUT_MANAGER_H
#define CALLOUT_MANAGER_H

#include <exceptions/exceptions.h>
#include <util/hooks/library_handle.h>
#include <util/hooks/server_hooks.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <string>

namespace isc {
namespace util {


/// @brief Callout Manager
///
/// This class manages the registration, deregistration and execution of the
/// library callouts.
///
/// It is constructed using a @ref isc::util::ServerHooks object that holds the
/// list of hooks registered for the server, which it uses to create the
/// hook vector.  This is a vector represting the callouts for each hook. Each
/// element is itself a vector of callouts registered by the loaded libraries.
///
/// The class also holds the collection of library handles, used to allow the
/// libraries to manipulate their callout list.

class CalloutManager {
private:

    // Private typedefs

    /// Vector of library handles.
    typedef std::vector<boost::shared_ptr<LibraryHandle> > HandleVector;

    /// Element in the vector of callouts.  The elements in the pair are the
    /// library index and the pointer to the callout.
    typedef std::pair<int, CalloutPtr> CalloutEntry;

    /// Entry in the list of callouts for an individual hook.
    typedef std::vector<CalloutEntry> CalloutVector;

public:

    /// @brief Constructor
    ///
    /// Initializes member variables, in particular sizing the hook vector
    /// (the vector of callouts) to the appropriate size.
    ///
    /// @param hook Collection of known hook names.
    CalloutManager(const boost::shared_ptr<ServerHooks>& hooks) :
        hooks_(hooks), handles_(), hook_vector_(hooks->getCount())
    {}

    /// @brief Register a callout on a hook
    ///
    /// Registers a callout function for a particular library with a given hook.
    /// The callout is added to the end of the callouts for this library that
    /// are associated with that hook.
    ///
    /// @param libindex Index of the library registering the callout
    /// @param name Name of the hook to which the callout is added.
    /// @param callout Pointer to the callout function to be registered.
    ///
    /// @throw NoSuchHook The hook name is unrecognised.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    void registerCallout(int libindex, const std::string& name,
                         CalloutPtr callout);

    /// @brief De-Register a callout on a hook
    ///
    /// Searches through the functions registered by the specified library with
    /// the named hook and removes all entries matching the callout.
    ///
    /// @param libindex Index of the library deregistering the callout
    /// @param name Name of the hook from which the callout is removed.
    /// @param callout Pointer to the callout function to be removed.
    ///
    /// @return true if a one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook The hook name is unrecognised.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    bool deregisterCallout(int libindex, const std::string& name,
                           CalloutPtr callout);

    /// @brief Removes all callouts on a hook
    ///
    /// Removes all callouts associated with a given hook that were registered
    /// by the specified library.
    ///
    /// @param libindex Index of the library deregistering the callouts
    /// @param name Name of the hook from which the callouts are removed.
    ///
    /// @return true if one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognised.
    bool deregisterAllCallouts(int libindex, const std::string& name);

    /// @brief Checks if callouts are present on a hook
    ///
    /// Checks all loaded libraries and returns true if at least one callout
    /// has been registered by any of them for the given hook.
    ///
    /// @param index Hook index for which callouts are checked.
    ///
    /// @return true if callouts are present, false if not.
    ///
    /// @throw NoSuchHook Given index does not correspond to a valid hook.
    bool calloutsPresent(int index) const;

    /// @brief Calls the callouts for a given hook
    ///
    /// Iterates through the libray handles and calls the callouts associated
    /// with the given hook index.
    ///
    /// @param index Index of the hook to call.
    /// @param callout_handle Reference to the CalloutHandle object for the
    ///        current object being processed.
    ///
    /// @return Status return.
    int callCallouts(int index, CalloutHandle& callout_handle);


    /// @brief Create library handle
    ///
    /// Creates a library handle.  The handle is used when loading a library in
    /// that the callouts are associated with the given library and when calling
    /// a callout: the handle for the library can be obtained to allow dynamic
    /// registration and de-registration.
    boost::shared_ptr<LibraryHandle> createHandle();

private:
    /// @brief Check hook index
    ///
    /// Ensures that the passed hook index is valid.
    ///
    /// @param index Hook index to test
    ///
    /// @throw NoSuchHook
    void checkHookIndex(int hook_index) const {
        if ((hook_index < 0) || (hook_index >= hook_vector_.size())) {
            isc_throw(NoSuchHook, "hook index " << hook_index <<
                      " is not valid for the list of registered hooks");
        }
    }

    /// @brief Compare two callout entries for library equality
    ///
    /// This is used in callout removal code.  It just checks whether two
    /// entries have the same library element.
    ///
    /// @param ent1 First callout entry to check
    /// @param ent2 Second callout entry to check
    ///
    /// @return bool true if the library entries are the same
    class CalloutLibraryEqual {
    public:
        bool operator()(const CalloutEntry& ent1, const CalloutEntry& ent2) {
            return (ent1.first == ent2.first);
        }
    };

    /// List of server hooks.  This is used 
    boost::shared_ptr<ServerHooks>  hooks_;

    /// Vector of pointers to library handles.
    HandleVector handles_;

    /// Vector of callout vectors.  There is one entry in this outer vector for
    /// each hook.
    std::vector<CalloutVector>  hook_vector_;

};

} // namespace util
} // namespace isc

#endif // CALLOUT_MANAGER_H
