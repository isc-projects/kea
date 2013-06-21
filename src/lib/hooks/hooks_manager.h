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

#ifndef HOOKS_MANAGER_H
#define HOOKS_MANAGER_H

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
/// used by a BIND 10 module when handling hooks.  It is responsible for the
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

    /// @brief Reset hooks manager
    ///
    /// Resets the hooks manager to the initial state.  This should only be
    /// called by test functions, so causes a warning message to be output.
    void reset() {}

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
    bool loadLibraries(const std::vector<std::string>& /* libraries */) {return false;}

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
    bool unloadLibraries() {return false;}

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
    /// Iterates through the libray handles and calls the callouts associated
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
    /// @note This library handle is valid only after loadLibraries() is
    ///       called and before another call to loadLibraries().  Its use
    ///       at any other time may cause severe problems.
    ///
    /// TODO: This is also invalidated by a call to obtaining the
    ///       post-callout function.
    ///
    /// @return Shared pointer to library handle associated with pre-library
    ///       callout registration.
    boost::shared_ptr<LibraryHandle> preCalloutLibraryHandle() const;

    /// @brief Return post-callouts library handle
    ///
    /// Returns a library handle that can be used by the server to register
    /// callouts on a hook that are called _after any callouts belonging
    /// to a library.
    ///
    /// @note This library handle is valid only after loadLibraries() is
    ///       called and before another call to loadLibraries().  Its use
    ///       at any other time may cause severe problems.
    ///
    /// TODO: This is also invalidated by a call to obtaining the
    ///       pret-callout function.
    ///
    /// @return Shared pointer to library handle associated with post-library
    ///       callout registration.
    boost::shared_ptr<LibraryHandle> postCalloutLibraryHandle() const;

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

private:

    /// @brief Constructor
    ///
    /// This is private as the object is a singleton and can only be addessed
    /// through the getHooksManager() static method.
    HooksManager();

    //@{
    /// The following correspond to the each of the static methods above
    /// but operate on the current instance.

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
    /// @note This handle is valid only after a loadLibraries() call and then
    ///       only up to the next loadLibraries() call.
    ///
    /// @return Shared pointer to a CalloutHandle object.
    boost::shared_ptr<CalloutHandle> createCalloutHandleInternal();

    //@}

    /// @brief Conditional initialization of the  hooks manager
    ///
    /// loadLibraries() performs the initialization of the HooksManager,
    /// setting up the internal structures and loading libraries.  However,
    /// in some cases, server authors may not do that.  This method is called
    /// whenever any hooks execution function is invoked (checking callouts,
    /// calling callouts or returning a callout handle).  If the HooksManager
    /// is unitialised, it will initialize it with an "empty set" of libraries.
    void conditionallyInitialize();

    // Members

    /// Set of library managers.
    boost::shared_ptr<LibraryManagerCollection> lm_collection_;

    /// Callout manager for the set of library managers.
    boost::shared_ptr<CalloutManager> callout_manager_;
};

} // namespace util
} // namespace hooks

#endif // HOOKS_MANAGER_H
