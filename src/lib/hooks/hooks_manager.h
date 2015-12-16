// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKS_MANAGER_H
#define HOOKS_MANAGER_H

#include <hooks/server_hooks.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

namespace isc {
namespace hooks {

// Forward declarations
class CalloutHandle;
class CalloutManager;
class LibraryHandle;
class LibraryManagerCollection;

/// @brief Hooks Manager
///
/// This is the overall manager of the hooks framework and is the main class
/// used by a Kea module when handling hooks.  It is responsible for the
/// loading and unloading of user libraries, and for calling the callouts on
/// each hook point.
///
/// The class is a singleton, the single instance of the object being accessed
/// through the static getHooksManager() method.

class HooksManager : boost::noncopyable {
public:
    /// @brief Get singleton hooks manager
    ///
    /// @return Reference to the singleton hooks manager.
    static HooksManager& getHooksManager();

    /// @brief Load and reload libraries
    ///
    /// Loads the list of libraries into the server address space.  For each
    /// library, the "standard" functions (ones with the same names as the
    /// hook points) are configured and the libraries' "load" function
    /// called.
    ///
    /// If libraries are already loaded, they are unloaded and the new
    /// libraries loaded.
    ///
    /// If any library fails to load, an error message will be logged.  The
    /// remaining libraries will be loaded if possible.
    ///
    /// @param libraries List of libraries to be loaded.  The order is
    ///        important, as it determines the order that callouts on the same
    ///        hook will be called.
    ///
    /// @return true if all libraries loaded without a problem, false if one or
    ///        more libraries failed to load.  In the latter case, message will
    ///        be logged that give the reason.
    static bool loadLibraries(const std::vector<std::string>& libraries);

    /// @brief Unload libraries
    ///
    /// Unloads the loaded libraries and leaves the hooks subsystem in the
    /// state it was after construction but before loadLibraries() is called.
    ///
    /// @note: This method should be used with caution - see the notes for
    ///        the class LibraryManager for pitfalls.  In general, a server
    ///        should not call this method: library unloading will automatically
    ///        take place when new libraries are loaded, and when appropriate
    ///        objects are destroyed.
    ///
    /// @return true if all libraries unloaded successfully, false on an error.
    ///         In the latter case, an error message will have been output.
    static void unloadLibraries();

    /// @brief Are callouts present?
    ///
    /// Checks loaded libraries and returns true if at lease one callout
    /// has been registered by them for the given hook.
    ///
    /// @param index Hooks index for which callouts are checked.
    ///
    /// @return true if callouts are present, false if not.
    /// @throw NoSuchHook Given index does not correspond to a valid hook.
    static bool calloutsPresent(int index);

    /// @brief Calls the callouts for a given hook
    ///
    /// Iterates through the library handles and calls the callouts associated
    /// with the given hook index.
    ///
    /// @note This method invalidates the current library index set with
    ///       setLibraryIndex().
    ///
    /// @param index Index of the hook to call.
    /// @param handle Reference to the CalloutHandle object for the current
    ///        object being processed.
    static void callCallouts(int index, CalloutHandle& handle);

    /// @brief Return pre-callouts library handle
    ///
    /// Returns a library handle that can be used by the server to register
    /// callouts on a hook that are called _before_ any callouts belonging
    /// to a library.
    ///
    /// @note Both the reference returned and the callouts registered with
    ///       this handle only remain valid until the next loadLibraries() or
    ///       unloadLibraries() call.  If the callouts are to remain registered
    ///       after this time, a new handle will need to be obtained and the
    ///       callouts re-registered.
    ///
    /// @return Reference to library handle associated with pre-library callout
    ///         registration.
    static LibraryHandle& preCalloutsLibraryHandle();

    /// @brief Return post-callouts library handle
    ///
    /// Returns a library handle that can be used by the server to register
    /// callouts on a hook that are called _after any callouts belonging
    /// to a library.
    ///
    /// @note Both the reference returned and the callouts registered with
    ///       this handle only remain valid until the next loadLibraries() or
    ///       unloadLibraries() call.  If the callouts are to remain registered
    ///       after this time, a new handle will need to be obtained and the
    ///       callouts re-registered.
    ///
    /// @return Reference to library handle associated with post-library callout
    ///         registration.
    static LibraryHandle& postCalloutsLibraryHandle();

    /// @brief Return callout handle
    ///
    /// Returns a callout handle to be associated with a request passed round
    /// the system.
    ///
    /// @note This handle is valid only after a loadLibraries() call and then
    ///       only up to the next loadLibraries() call.
    ///
    /// @return Shared pointer to a CalloutHandle object.
    static boost::shared_ptr<CalloutHandle> createCalloutHandle();

    /// @brief Register Hook
    ///
    /// This is just a convenience shell around the ServerHooks::registerHook()
    /// method.  It - along with the definitions of the two hook indexes for
    /// the context_create and context_destroy methods - means that server
    /// authors only need to deal with HooksManager and CalloutHandle, and not
    /// include any other hooks framework classes.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook, to be used in subsequent hook-related calls.
    ///         This will be greater than or equal to zero (so allowing a
    ///         negative value to indicate an invalid index).
    ///
    /// @throws DuplicateHook A hook with the same name has already been
    ///         registered.
    static int registerHook(const std::string& name);

    /// @brief Return list of loaded libraries
    ///
    /// Returns the names of the loaded libraries.
    ///
    /// @return List of loaded library names.
    static std::vector<std::string> getLibraryNames();

    /// @brief Validate library list
    ///
    /// For each library passed to it, checks that the library can be opened
    /// and that the "version" function is present and gives the right answer.
    /// Each library is closed afterwards.
    ///
    /// This is used during the configuration parsing - when the list of hooks
    /// libraries is changed, each of the new libraries is checked before the
    /// change is committed.
    ///
    /// @param libraries List of libraries to be validated.
    ///
    /// @return An empty vector if all libraries validated.  Otherwise it
    ///         holds the names of the libraries that failed validation.
    static std::vector<std::string> validateLibraries(
                       const std::vector<std::string>& libraries);

    /// Index numbers for pre-defined hooks.
    static const int CONTEXT_CREATE = ServerHooks::CONTEXT_CREATE;
    static const int CONTEXT_DESTROY = ServerHooks::CONTEXT_DESTROY;

private:

    /// @brief Constructor
    ///
    /// This is private as the object is a singleton and can only be addressed
    /// through the getHooksManager() static method.
    HooksManager();

    //@{
    /// The following methods correspond to similarly-named static methods,
    /// but actually do the work on the singleton instance of the HooksManager.
    /// See the descriptions of the static methods for more details.

    /// @brief Validate library list
    ///
    /// @param List of libraries to be validated.
    ///
    /// @return An empty string if all libraries validated.  Otherwise it is
    ///         the name of the first library that failed validation.  The
    ///         configuration code can return this to bindctl as an indication
    ///         of the problem.
    std::string validateLibrariesInternal(
                       const std::vector<std::string>& libraries) const;

    /// @brief Load and reload libraries
    ///
    /// @param libraries List of libraries to be loaded.  The order is
    ///        important, as it determines the order that callouts on the same
    ///        hook will be called.
    ///
    /// @return true if all libraries loaded without a problem, false if one or
    ///        more libraries failed to load.  In the latter case, message will
    ///        be logged that give the reason.
    bool loadLibrariesInternal(const std::vector<std::string>& libraries);

    /// @brief Unload libraries
    void unloadLibrariesInternal();

    /// @brief Are callouts present?
    ///
    /// @param index Hooks index for which callouts are checked.
    ///
    /// @return true if callouts are present, false if not.
    /// @throw NoSuchHook Given index does not correspond to a valid hook.
    bool calloutsPresentInternal(int index);

    /// @brief Calls the callouts for a given hook
    ///
    /// @param index Index of the hook to call.
    /// @param handle Reference to the CalloutHandle object for the current
    ///        object being processed.
    void callCalloutsInternal(int index, CalloutHandle& handle);

    /// @brief Return callout handle
    ///
    /// @return Shared pointer to a CalloutHandle object.
    boost::shared_ptr<CalloutHandle> createCalloutHandleInternal();

    /// @brief Return pre-callouts library handle
    ///
    /// @return Reference to library handle associated with pre-library callout
    ///         registration.
    LibraryHandle& preCalloutsLibraryHandleInternal();

    /// @brief Return post-callouts library handle
    ///
    /// @return Reference to library handle associated with post-library callout
    ///         registration.
    LibraryHandle& postCalloutsLibraryHandleInternal();

    /// @brief Return list of loaded libraries
    ///
    /// @return List of loaded library names.
    std::vector<std::string> getLibraryNamesInternal() const;

    //@}

    /// @brief Initialization to No Libraries
    ///
    /// Initializes the hooks manager with an "empty set" of libraries.  This
    /// method is called if conditionallyInitialize() determines that such
    /// initialization is needed.
    void performConditionalInitialization();

    /// @brief Conditional initialization of the  hooks manager
    ///
    /// loadLibraries() performs the initialization of the HooksManager,
    /// setting up the internal structures and loading libraries.  However,
    /// in some cases, server authors may not do that.  This method is called
    /// whenever any hooks execution function is invoked (checking callouts,
    /// calling callouts or returning a callout handle).  If the HooksManager
    /// is uninitialized, it will initialize it with an "empty set"
    /// of libraries.
    ///
    /// For speed, the test of whether initialization is required is done
    /// in-line here.  The actual initialization is performed in
    /// performConditionalInitialization().
    void conditionallyInitialize() {
        if (!lm_collection_) {
            performConditionalInitialization();
        }
    }

    // Members

    /// Set of library managers.
    boost::shared_ptr<LibraryManagerCollection> lm_collection_;

    /// Callout manager for the set of library managers.
    boost::shared_ptr<CalloutManager> callout_manager_;
};

} // namespace util
} // namespace hooks

#endif // HOOKS_MANAGER_H
