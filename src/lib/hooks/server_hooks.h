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

#ifndef SERVER_HOOKS_H
#define SERVER_HOOKS_H

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace util {

/// @brief Duplicate hook
///
/// Thrown if an attempt is made to register a hook with the same name as a
/// previously-registered hook.
class DuplicateHook : public Exception {
public:
    DuplicateHook(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Invalid hook
///
/// Thrown if an attempt is made to get the index for an invalid hook.
class NoSuchHook : public Exception {
public:
    NoSuchHook(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


/// @brief Server hook collection
///
/// This class is used by the server-side code to register hooks - points in the
/// server processing at which libraries can register functions (callouts) that
/// the server will call.  These functions can modify data and so affect the
/// processing of the server.
///
/// The ServerHooks class is little more than a wrapper around the std::map
/// class.  It stores a hook, assigning to it a unique index number.  This
/// number is then used by the server code to identify the hook being called.
/// (Although it would be feasible to use a name as an index, using an integer
/// will speed up the time taken to locate the callouts, which may make a
/// difference in a frequently-executed piece of code.)
///
/// ServerHooks is a singleton object and is only accessible by the static
/// method getserverHooks().

class ServerHooks : public boost::noncopyable {
public:

    /// Index numbers for pre-defined hooks.
    static const int CONTEXT_CREATE = 0;
    static const int CONTEXT_DESTROY = 1;

    /// @brief Reset to Initial State
    ///
    /// Resets the collection of hooks to the initial state, with just the
    /// context_create and context_destroy hooks set.  This used during
    /// construction. It is also used during testing to reset the global
    /// ServerHooks object.
    ///
    /// @throws isc::Unexpected if the registration of the pre-defined hooks
    ///         fails in some way.
    void reset();

    /// @brief Register a hook
    ///
    /// Registers a hook and returns the hook index.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook, to be used in subsequent hook-related calls.
    ///         This will be greater than or equal to zero (so allowing a
    ///         negative value to indicate an invalid index).
    ///
    /// @throws DuplicateHook A hook with the same name has already been
    ///         registered.
    int registerHook(const std::string& name);

    /// @brief Get hook name
    ///
    /// Returns the name of a hook given the index.  This is most likely to be
    /// used in log messages.
    ///
    /// @param index Index of the hoold
    ///
    /// @return Name of the hook.
    ///
    /// @throw NoSuchHook if the hook index is invalid.
    std::string getName(int index) const;

    /// @brief Get hook index
    ///
    /// Returns the index of a hook.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook, to be used in subsequent calls.
    ///
    /// @throw NoSuchHook if the hook name is unknown to the caller.
    int getIndex(const std::string& name) const;

    /// @brief Return number of hooks
    ///
    /// Returns the total number of hooks registered.
    ///
    /// @return Number of hooks registered.
    int getCount() const {
        return (hooks_.size());
    }

    /// @brief Get hook names
    ///
    /// Return list of hooks registered in the object.
    ///
    /// @return Vector of strings holding hook names.
    std::vector<std::string> getHookNames() const;

    /// @brief Return ServerHookms object
    ///
    /// Returns the global ServerHooks object.
    ///
    /// @return Reference to the global ServerHooks object.
    static ServerHooks& getServerHooks();

private:
    /// @brief Constructor
    ///
    /// This pre-registers two hooks, context_create and context_destroy, which
    /// are called by the server before processing a packet and after processing
    /// for the packet has completed.  They allow the server code to allocate
    /// and destroy per-packet context.
    ///
    /// Constructor is declared private to enforce the singleton nature of
    /// the object.  A reference to the singleton is obtainable through the
    /// ggetServerHooks() static method.
    ///
    /// @throws isc::Unexpected if the registration of the pre-defined hooks
    ///         fails in some way.
    ServerHooks();

    /// Useful typedefs.
    typedef std::map<std::string, int> HookCollection;
    typedef std::map<int, std::string> InverseHookCollection;

    /// Two maps, one for name->index, the other for index->name.  (This is
    /// simpler than using a multi-indexed container.)
    HookCollection  hooks_;                 ///< Hook name/index collection
    InverseHookCollection inverse_hooks_;   ///< Hook index/name collection
};


/// @brief Hooks Registration
///
/// All hooks must be registered before libraries are loaded and callouts
/// assigned to them.  One way of doing this is to have a global list of hooks:
/// the addition of any hook anywhere would require updating the list. This
/// is possible and, if desired, the author of a server can do it.
///
/// An alternative is the option provided here, where each component of BIND 10
/// registers the hooks they are using.  To do this, the component should
/// create a hook registration function of the form:
///
/// @code
/// static int hook1_num = -1;  // Initialize number for hook 1
/// static int hook2_num = -1;  // Initialize number for hook 2
///
/// void myModuleRegisterHooks(ServerHooks& hooks) {
///     hook1_num = hooks.registerHook("hook1");
///     hook2_num = hooks.registerHook("hook2");
/// }
/// @endcode
///
/// ... which registers the hooks and stores the associated hook index. To
/// avoid the need to add an explicit call to each of the hook registration
/// functions to the server initialization code, the component should declare
/// an object of this class in the same file as the registration function,
/// but outside of any function.  The declaration should include the name
/// of the registration function, i.e.
///
/// @code
/// HookRegistrationFunction f(myModuleRegisterHooks);
/// @code
///
/// The constructor of this object will run prior to main() getting called and
/// will add the registration function to a list of such functions.  The server
/// then calls the static class method "execute()" to run all the declared
/// registration functions.

class HookRegistrationFunction {
public:
    /// @brief Pointer to a hook registration function
    typedef void (*RegistrationFunctionPtr)(ServerHooks&);

    /// @brief Constructor
    ///
    /// For variables declared outside functions or methods, the constructors
    /// are run after the program is loaded and before main() is called. This
    /// constructor adds the passed pointer to a vector of such pointers.
    HookRegistrationFunction(RegistrationFunctionPtr reg_func);

    /// @brief Access registration function vector
    ///
    /// One of the problems with functions run prior to starting main() is the
    /// "static initialization fiasco".  This occurs because the order in which
    /// objects outside functions are constructed is not defined.  So if this
    /// constructor were to depend on a vector declared externally, we would
    /// not be able to guarantee that the vector had been initialised properly
    /// before we used it.
    ///
    /// To get round this situation, the vector is declared statically within
    /// a static function.  The first time the function is called, the vector
    /// is initialized before it is used.
    ///
    /// This function returns a reference to the vector used to hold the
    /// pointers.
    ///
    /// @return Reference to the (static) list of registration functions
    static std::vector<RegistrationFunctionPtr>& getFunctionVector();

    /// @brief Execute registration functions
    ///
    /// Called by the server initialization code, this function executes all
    /// registered hook registration functions.
    ///
    /// @param hooks ServerHooks object to which hook information will be added.
    static void execute(ServerHooks& hooks);
};

} // namespace util
} // namespace isc

#endif  // SERVER_HOOKS_H
