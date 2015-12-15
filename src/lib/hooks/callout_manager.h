// Copyright (C) 2013,2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CALLOUT_MANAGER_H
#define CALLOUT_MANAGER_H

#include <exceptions/exceptions.h>
#include <hooks/library_handle.h>
#include <hooks/server_hooks.h>

#include <boost/shared_ptr.hpp>

#include <climits>
#include <map>
#include <string>

namespace isc {
namespace hooks {

/// @brief No such library
///
/// Thrown if an attempt is made to set the current library index to a value
/// that is invalid for the number of loaded libraries.
class NoSuchLibrary : public Exception {
public:
    NoSuchLibrary(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Callout Manager
///
/// This class manages the registration, deregistration and execution of the
/// library callouts.  It is part of the hooks framework used by the Kea
/// server, and is not for use by user-written code in a hooks library.
///
/// In operation, the class needs to know two items of data:
///
/// - The list of server hooks, which is used in two ways.  Firstly, when a
///   callout registers or deregisters a hook, it does so by name: the
///   @ref isc::hooks::ServerHooks object supplies the names of registered
///   hooks.  Secondly, when the callouts associated with a hook are called by
///   the server, the server supplies the index of the relevant hook: this is
///   validated by reference to the list of hook.
///
/// - The number of loaded libraries.  Each callout registered by a user
///   library is associated with that library, the callout manager storing both
///   a pointer to the callout and the index of the library in the list of
///   loaded libraries.  Callouts are allowed to dynamically register and
///   deregister callouts in the same library (including themselves): they
///   cannot affect callouts registered by another library.  When calling a
///   callout, the callout manager maintains the idea of a "current library
///   index": if the callout calls one of the callout registration functions
///   (indirectly via the @ref LibraryHandle object), the registration
///   functions use the "current library index" in their processing.
///
/// These two items of data are supplied when an object of this class is
/// constructed.  The latter (number of libraries) can be updated after the
/// class is constructed.  (Such an update is used during library loading where
/// the CalloutManager has to be constructed before the libraries are loaded,
/// but one of the libraries subsequently fails to load.)
///
/// The library index is important because it determines in what order callouts
/// on a particular hook are called.  For each hook, the CalloutManager
/// maintains a vector of callouts ordered by library index.  When a callout
/// is added to the list, it is added at the end of the callouts associated
/// with the current library.  To clarify this further, suppose that three
/// libraries are loaded, A (assigned an index 1), B (assigned an index 2) and
/// C (assigned an index 3).  Suppose A registers two callouts on a given hook,
/// A1 and A2 (in that order) B registers B1 and B2 (in that order) and C
/// registers C1 and C2 (in that order).  Internally, the callouts are stored
/// in the order A1, A2, B1, B2, C1, and C2: this is also the order in which
/// the are called.  If B now registers another callout (B3), it is added to
/// the vector after the list of callouts associated with B: the new order is
/// therefore A1, A2, B1, B2, B3, C1 and C2.
///
/// Indexes range between 1 and n (where n is the number of the libraries
/// loaded) and are assigned to libraries based on the order the libraries
/// presented to the hooks framework for loading (something that occurs in the
/// isc::hooks::HooksManager) class.  However, two other indexes are recognized,
/// 0 and INT_MAX.  These are used when the server itself registers callouts -
/// the server is able to register callouts that get called before any
/// user-library callouts, and ones that get called after user-library callouts.
/// In other words, assuming the callouts on a hook are A1, A2, B1, B2, B3, C2,
/// C2 as before, and that the server registers S1 (to run before the
/// user-registered callouts) and S2 (to run after them), the callouts are
/// stored (and executed) in the order S1, A1, A2, B1, B2, B3, C2, C2, S2.  In
/// summary, the recognized index values are:
///
/// - < 0: invalid.
/// - 0: used for server-registered callouts that are called before
///   user-registered callouts.
/// - 1 - n: callouts from user libraries.
/// - INT_MAX: used for server-registered callouts called after
///   user-registered callouts.
///
/// Note that the callout functions do not access the CalloutManager: instead,
/// they use a LibraryHandle object.  This contains an internal pointer to
/// the CalloutManager, but provides a restricted interface.  In that way,
/// callouts are unable to affect callouts supplied by other libraries.

class CalloutManager {
private:

    // Private typedefs

    /// Element in the vector of callouts.  The elements in the pair are the
    /// index of the library from which this callout was registered, and a#
    /// pointer to the callout itself.
    typedef std::pair<int, CalloutPtr> CalloutEntry;

    /// An element in the hook vector. Each element is a vector of callouts
    /// associated with a given hook.
    typedef std::vector<CalloutEntry> CalloutVector;

public:

    /// @brief Constructor
    ///
    /// Initializes member variables, in particular sizing the hook vector
    /// (the vector of callout vectors) to the appropriate size.
    ///
    /// @param num_libraries Number of loaded libraries.
    ///
    /// @throw isc::BadValue if the number of libraries is less than 0,
    CalloutManager(int num_libraries = 0);

    /// @brief Register a callout on a hook for the current library
    ///
    /// Registers a callout function for the current library with a given hook
    /// (the index of the "current library" being given by the current_library_
    /// member).  The callout is added to the end of the callouts for this
    /// library that are associated with that hook.
    ///
    /// @param name Name of the hook to which the callout is added.
    /// @param callout Pointer to the callout function to be registered.
    ///
    /// @throw NoSuchHook The hook name is unrecognized.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    void registerCallout(const std::string& name, CalloutPtr callout);

    /// @brief De-Register a callout on a hook for the current library
    ///
    /// Searches through the functions registered by the the current library
    /// (the index of the "current library" being given by the current_library_
    /// member) with the named hook and removes all entries matching the
    /// callout.
    ///
    /// @param name Name of the hook from which the callout is removed.
    /// @param callout Pointer to the callout function to be removed.
    ///
    /// @return true if a one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook The hook name is unrecognized.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    bool deregisterCallout(const std::string& name, CalloutPtr callout);

    /// @brief Removes all callouts on a hook for the current library
    ///
    /// Removes all callouts associated with a given hook that were registered
    /// by the current library (the index of the "current library" being given
    /// by the current_library_ member).
    ///
    /// @param name Name of the hook from which the callouts are removed.
    ///
    /// @return true if one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognized.
    bool deregisterAllCallouts(const std::string& name);

    /// @brief Checks if callouts are present on a hook
    ///
    /// Checks all loaded libraries and returns true if at least one callout
    /// has been registered by any of them for the given hook.
    ///
    /// @param hook_index Hook index for which callouts are checked.
    ///
    /// @return true if callouts are present, false if not.
    ///
    /// @throw NoSuchHook Given index does not correspond to a valid hook.
    bool calloutsPresent(int hook_index) const;

    /// @brief Calls the callouts for a given hook
    ///
    /// Iterates through the libray handles and calls the callouts associated
    /// with the given hook index.
    ///
    /// @note This method invalidates the current library index set with
    ///       setLibraryIndex().
    ///
    /// @param hook_index Index of the hook to call.
    /// @param callout_handle Reference to the CalloutHandle object for the
    ///        current object being processed.
    void callCallouts(int hook_index, CalloutHandle& callout_handle);

    /// @brief Get current hook index
    ///
    /// Made available during callCallouts, this is the index of the hook
    /// on which callouts are being called.
    int getHookIndex() const {
        return (current_hook_);
    }

    /// @brief Get number of libraries
    ///
    /// Returns the number of libraries that this CalloutManager is expected
    /// to serve.  This is the number passed to its constructor.
    ///
    /// @return Number of libraries served by this CalloutManager.
    int getNumLibraries() const {
        return (num_libraries_);
    }

    /// @brief Get current library index
    ///
    /// Returns the index of the "current" library.  This the index associated
    /// with the currently executing callout when callCallouts is executing.
    /// When callCallouts() is not executing (as is the case when the load()
    /// function in a user-library is called during the library load process),
    /// the index can be set by setLibraryIndex().
    ///
    /// @note The value set by this method is lost after a call to
    ///       callCallouts.
    ///
    /// @return Current library index.
    int getLibraryIndex() const {
        return (current_library_);
    }

    /// @brief Set current library index
    ///
    /// Sets the current library index.  This has the following valid values:
    ///
    /// - -1: invalidate current index.
    /// - 0: pre-user library callout.
    /// - 1 - numlib: user-library callout (where "numlib" is the number of
    ///   libraries loaded in the system, this figure being passed to this
    ///   object at construction time).
    /// - INT_MAX: post-user library callout.
    ///
    /// @param library_index New library index.
    ///
    /// @throw NoSuchLibrary if the index is not valid.
    void setLibraryIndex(int library_index) {
        checkLibraryIndex(library_index);
        current_library_ = library_index;
    }

    /// @defgroup calloutManagerLibraryHandles Callout manager library handles
    ///
    /// The CalloutManager offers three library handles:
    ///
    /// - a "standard" one, used to register and deregister callouts for
    ///   the library index that is marked as current in the CalloutManager.
    ///   When a callout is called, it is passed this one.
    /// - a pre-library callout handle, used by the server to register
    //    callouts to run prior to user-library callouts.
    /// - a post-library callout handle, used by the server to register
    ///   callouts to run after the user-library callouts.
    //@{

    /// @brief Return library handle
    ///
    /// The library handle is available to the user callout via the callout
    /// handle object.  It provides a cut-down view of the CalloutManager,
    /// allowing the callout to register and deregister callouts in the
    /// library of which it is part, whilst denying access to anything that
    /// may affect other libraries.
    ///
    /// @return Reference to library handle for this manager
    LibraryHandle& getLibraryHandle() {
        return (library_handle_);
    }

    /// @brief Return pre-user callouts library handle
    ///
    /// The LibraryHandle to affect callouts that will run before the
    /// user-library callouts.
    ///
    /// @return Reference to pre-user library handle for this manager
    LibraryHandle& getPreLibraryHandle() {
        return (pre_library_handle_);
    }

    /// @brief Return post-user callouts library handle
    ///
    /// The LibraryHandle to affect callouts that will run before the
    /// user-library callouts.
    ///
    /// @return Reference to post-user library handle for this manager
    LibraryHandle& getPostLibraryHandle() {
        return (post_library_handle_);
    }

    //@}

private:
    /// @brief Check library index
    ///
    /// Ensures that the current library index is valid.  This is called by
    /// the hook registration functions.
    ///
    /// @param library_index Value to check for validity as a library index.
    ///        Valid values are 0 - numlib+1 and -1: see @ref setLibraryIndex
    ///        for the meaning of the various values.
    ///
    /// @throw NoSuchLibrary Library index is not valid.
    void checkLibraryIndex(int library_index) const;

    /// @brief Compare two callout entries for library equality
    ///
    /// This is used in callout removal code when all callouts on a hook for a
    /// given library are being removed.  It checks whether two callout entries
    /// have the same library index.
    ///
    /// @param ent1 First callout entry to check
    /// @param ent2 Second callout entry to check
    ///
    /// @return bool true if the library entries are the same
    class CalloutLibraryEqual :
        public std::binary_function<CalloutEntry, CalloutEntry, bool> {
    public:
        bool operator()(const CalloutEntry& ent1,
                        const CalloutEntry& ent2) const {
            return (ent1.first == ent2.first);
        }
    };

    // Member variables

    /// Reference to the singleton ServerHooks object.  See the
    /// @ref hooksmgMaintenanceGuide for information as to why the class holds
    /// a reference instead of accessing the singleton within the code.
    ServerHooks& server_hooks_;

    /// Current hook.  When a call is made to callCallouts, this holds the
    /// index of the current hook.  It is set to an invalid value (-1)
    /// otherwise.
    int current_hook_;

    /// Current library index.  When a call is made to any of the callout
    /// registration methods, this variable indicates the index of the user
    /// library that should be associated with the call.
    int current_library_;

    /// Vector of callout vectors.  There is one entry in this outer vector for
    /// each hook. Each element is itself a vector, with one entry for each
    /// callout registered for that hook.
    std::vector<CalloutVector> hook_vector_;

    /// LibraryHandle object user by the callout to access the callout
    /// registration methods on this CalloutManager object.  The object is set
    /// such that the index of the library associated with any operation is
    /// whatever is currently set in the CalloutManager.
    LibraryHandle library_handle_;

    /// LibraryHandle for callouts to be registered as being called before
    /// the user-registered callouts.
    LibraryHandle pre_library_handle_;

    /// LibraryHandle for callouts to be registered as being called after
    /// the user-registered callouts.
    LibraryHandle post_library_handle_;

    /// Number of libraries.
    int num_libraries_;
};

} // namespace util
} // namespace isc

#endif // CALLOUT_MANAGER_H
