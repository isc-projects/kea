// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
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
///   library registers or deregisters a hook, it does so by name: the
///   @ref isc::hooks::ServerHooks object supplies the names of registered
///   hooks.  Secondly, when the callouts associated with a hook are called by
///   the server, the server supplies the index of the relevant hook: this is
///   validated by reference to the list of hooks.
///
/// - The number of loaded libraries.  Each callout registered by a user
///   library is associated with that library, the callout manager storing both
///   a pointer to the callout and the index of the library in the list of
///   loaded libraries.  When calling a callout, the callout manager maintains
///   the idea of a "current library index": this is used to access the context
///   associated with the library.
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
/// they are called.
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
/// Since Kea 1.3.0 release hook libraries can register callouts as control
/// command handlers. Such handlers are associated with dynamically created
/// hook points which names are created after command names. For example,
/// if a command name is 'foo-bar', the name of the hook point to which
/// callouts/command handlers are registered is '$foo_bar'. Prefixing the
/// hook point name with the dollar sign eliminates potential conflicts
/// between hook points dedicated to commands handling and other (fixed)
/// hook points.
///
/// Prefixing hook names for command handlers with a dollar sign precludes
/// auto registration of command handlers, i.e. hooks framework is unable
/// to match hook points with names of functions implementing command
/// handlers, because the dollar sign is not legal in C++ function names.
/// This is intended because we want hook libraries to explicitly register
/// commands handlers for supported commands and not rely on Kea to register
/// hook points for them. Should we find use cases for auto registration of
/// command handlers, we may modify the
/// @ref ServerHooks::commandToHookName to use an encoding of hook
/// point names for command handlers that would only contain characters
/// allowed in function names.
///
/// The @ref CalloutManager::registerCommandHook has been added to allow for
/// dynamically creating hook points for which command handlers are registered.
/// This method is called from the @ref LibraryHandle::registerCommandCallout
/// as a result of registering the command handlers by the hook library in
/// its @c load() function. If the hook point for the given command already
/// exists, this function doesn't do anything. The
/// @ref LibraryHandle::registerCommandCallout can install callouts on this
/// hook point.
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
    /// Registers a callout function for the current library with a given hook.
    /// The callout is added to the end of the callouts for this library that
    /// are associated with that hook.
    ///
    /// @param name Name of the hook to which the callout is added.
    /// @param callout Pointer to the callout function to be registered.
    /// @param library_index Library index used for registering the callout.
    ///
    /// @throw NoSuchHook The hook name is unrecognized.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    void registerCallout(const std::string& name,
                         CalloutPtr callout,
                         int library_index);

    /// @brief De-Register a callout on a hook for the current library
    ///
    /// Searches through the functions registered by the current library
    /// with the named hook and removes all entries matching the
    /// callout.
    ///
    /// @param name Name of the hook from which the callout is removed.
    /// @param callout Pointer to the callout function to be removed.
    /// @param library_index Library index used for deregistering the callout.
    ///
    /// @return true if a one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook The hook name is unrecognized.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    bool deregisterCallout(const std::string& name,
                           CalloutPtr callout,
                           int library_index);

    /// @brief Removes all callouts on a hook for the current library
    ///
    /// Removes all callouts associated with a given hook that were registered
    /// by the current library.
    ///
    /// @param name Name of the hook from which the callouts are removed.
    /// @param library_index Library index used for deregistering all callouts.
    ///
    /// @return true if one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognized.
    bool deregisterAllCallouts(const std::string& name, int library_index);

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

    /// @brief Checks if control command handlers are present for the
    /// specified command.
    ///
    /// @param command_name Command name for which handlers' presence should
    ///        be checked.
    ///
    /// @return true if there is a hook point associated with the specified
    /// command and callouts/command handlers are installed for this hook
    /// point, false otherwise.
    bool commandHandlersPresent(const std::string& command_name) const;

    /// @brief Calls the callouts for a given hook
    ///
    /// Iterates through the library handles and calls the callouts associated
    /// with the given hook index.
    ///
    /// @note This method invalidates the current library index set with
    ///       setLibraryIndex().
    ///
    /// @param hook_index Index of the hook to call.
    /// @param callout_handle Reference to the CalloutHandle object for the
    ///        current object being processed.
    void callCallouts(int hook_index, CalloutHandle& callout_handle);

    /// @brief Calls the callouts/command handlers for a given command name.
    ///
    /// Iterates through the library handles and calls the command handlers
    /// associated with the given command. It expects that the hook point
    /// for this command exists (with a name being a command_name prefixed
    /// with a dollar sign and with hyphens replaced with underscores).
    ///
    /// @param command_name Command name for which handlers should be called.
    /// @param callout_handle Reference to the CalloutHandle object for the
    ///        current object being processed.
    ///
    /// @throw NoSuchHook if the hook point for the specified command does
    ///        not exist.
    void callCommandHandlers(const std::string& command_name,
                             CalloutHandle& callout_handle);

    /// @brief Registers a hook point for the specified command name.
    ///
    /// If the hook point for such command already exists, this function
    /// doesn't do anything. The registered hook point name is created
    /// after command_name by prefixing it with a dollar sign and replacing
    /// all hyphens with underscores, e.g. for the 'foo-bar' command the
    /// following hook point name will be generated: '$foo_bar'.
    ///
    /// @param command_name Command name for which the hook point should be
    ///        registered.
    void registerCommandHook(const std::string& command_name);

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

    /// @brief Return number of currently available hooks
    size_t getHookLibsVectorSize() const {
        return (hook_vector_.size());
    }

private:

    /// @brief This method checks whether the hook_vector_ size is sufficient
    ///        and extends it if necessary.
    ///
    /// The problem is as follows: some hooks are initialized statically
    /// from global static objects. ServerHooks object creates hooks_ collection
    /// and CalloutManager creates its own hook_vector_ and both are initialized
    /// to the same size. All works well so far. However, if some code at a
    /// later time (e.g. a hook library) registers new hook point, then
    /// ServerHooks::registerHook() will extend its hooks_ collection, but
    /// the CalloutManager will keep the old hook_vector_ that is too small by
    /// one. Now when the library is unloaded, deregisterAllCallouts will
    /// go through all hook points and will eventually hit the one that
    /// will return index greater than the hook_vector_ size.
    ///
    /// To solve this problem, ensureVectorSize was implemented. It should
    /// be called (presumably from ServerHooks) every time a new hook point
    /// is registered. It checks whether the vector size is sufficient and
    /// extends it if necessary. It is safe to call it multiple times. It
    /// may grow the vector size, but will never shrink it.
    void ensureHookLibsVectorSize();

    /// @brief Check library index
    ///
    /// Ensures that the current library index is valid.  This is called by
    /// the hook registration functions.
    ///
    /// @param library_index Value to check for validity as a library index.
    ///        Valid values are 0 -> numlib + 1 and -1: see @ref setLibraryIndex
    ///        for the meaning of the various values.
    ///
    /// @throw NoSuchLibrary Library index is not valid.
    void checkLibraryIndex(int library_index) const;

    // Member variables

    /// Reference to the singleton ServerHooks object.  See the
    /// @ref hooksmgMaintenanceGuide for information as to why the class holds
    /// a reference instead of accessing the singleton within the code.
    ServerHooks& server_hooks_;

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

}  // namespace util
}  // namespace isc

#endif // CALLOUT_MANAGER_H
