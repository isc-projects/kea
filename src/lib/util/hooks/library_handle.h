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

#ifndef LIBRARY_HANDLE_H
#define LIBRARY_HANDLE_H

#include <map>
#include <string>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>
#include <util/hooks/server_hooks.h>

namespace isc {
namespace util {

/// @brief No such hook
///
/// Thrown if an attempt is made to use an invalid hook name or hook index.
class NoSuchHook : public Exception {
public:
    NoSuchHook(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief No Such Context
///
/// Thrown if an attempt is made to obtain context that has not been previously
/// set.

class NoSuchContext : public Exception {
public:
    NoSuchContext(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

// Forward declaration for CalloutHandle
class CalloutHandle;

/// Typedef for a callout pointer
extern "C" {
    typedef int (*CalloutPtr)(CalloutHandle&);
};


/// @brief Global Callout Handle
/// @todo Change name to Library Handle?
///
/// This class is used to manage a loaded library.  It is used by the user
/// library to register callouts and by the HookManager to call them.  The
/// class also contains storage for library-specific context.
///
/// Although there is an argument for the class to load unload the user
/// library, that is handled by the HookManager to prevent the user library
/// from accessing those functions.

class LibraryHandle {
private:
    /// Typedef to allow abbreviation of iterator specification in methods
    typedef std::map<std::string, boost::any> ContextCollection;

public:

    /// @brief Constructor
    ///
    /// This is passed the ServerHooks object and an index number: the former
    /// allows for the sizing of the internal hook vector, and the latter
    /// is used by the CalloutHandle object to access appropriate context
    ///
    /// @param hooks Pointer to the hooks registered by the server.
    /// @param index Index of this library in the list of loaded libraries.
    LibraryHandle(boost::shared_ptr<ServerHooks> hooks, int index)
        : context_(), hooks_(hooks), hook_vector_(hooks->getCount()),
          index_(index)
    {}

    /// @brief Set context
    ///
    /// Sets an element in the library context.  If an element of the name
    /// is already present, it is replaced.
    ///
    /// @param name Name of the element in the context to set
    /// @param value Value to set
    template <typename T>
    void setContext(const std::string& name, T value) {
        context_[name] = value;
    }

    /// @brief Get context
    ///
    /// Sets an element in the library context.  If the name does not exist,
    /// a "NoSuchContext" exception is thrown.
    ///
    /// @param name Name of the element in the context to set.
    /// @param value [out] Value to set.  The type of "value" is important:
    ///        it must match the type of the value set.
    ///
    /// @throw NoSuchContext Thrown if no context element with the name
    ///        "name" is present.
    /// @throw boost::bad_any_cast Thrown if the context element is present,
    ///        but the type of the element is not that expected
    template <typename T>
    void getContext(const std::string& name, T& value) const {
        ContextCollection::const_iterator element_ptr = context_.find(name);
        if (element_ptr == context_.end()) {
            isc_throw(NoSuchContext, "unable to find library context datum " <<
                      name << " in library at index " << index_);
        }

        value = boost::any_cast<T>(element_ptr->second);
    }

    /// @brief Register a callout
    ///
    /// Registers a callout function with a given hook.  The callout is added
    /// to the end of the callouts associated with the hook.
    ///
    /// @param name Name of the hook to which the callout is added.
    /// @param callout Pointer to the callout function to be registered.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognised.
    /// @throw Unexpected Hooks name is valid but internal data structure is
    ///        of the wrong size.
    void registerCallout(const std::string& name, CalloutPtr callout);

    /// @brief De-Register a callout
    ///
    /// Searches through the functions associated with the named hook and
    /// removes all entries matching the callout.  If there are no matching
    /// callouts, the result is a no-op.
    ///
    /// @param name Name of the hook from which the callout is removed.
    /// @param callout Pointer to the callout function to be removed.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognised.
    /// @throw Unexpected Hooks name is valid but internal data structure is
    ///        of the wrong size.
    void deregisterCallout(const std::string& name, CalloutPtr callout);

    /// @brief Removes all callouts
    ///
    /// Removes all callouts associated with a given hook.  This is a no-op
    /// if there are no callouts associated with the hook.
    ///
    /// @param name Name of the hook from which the callouts are removed.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognised.
    void deregisterAll(const std::string& name);


    /// @brief Checks if callouts are present
    ///
    /// @param index Hook index for which callouts are checked.
    ///
    /// @return true if callouts are present, false if not.
    ///
    /// @throw NoSuchHook Thrown if the indesx is not valid.
    bool calloutsPresent(int index) const;

    /// @brief Calls the callouts for a given hook
    ///
    /// Calls the callouts associated with the given hook index.
    ///
    /// @param index Index of the hook to call.
    /// @param handle Reference to the CalloutHandle object for the current
    ///        object being processed.
    ///
    /// @return Status return.
    ///
    int callCallouts(int index, CalloutHandle& handle);

private:
    /// @brief Check hook index
    ///
    /// Checks that the hook index is valid for the hook vector.  If not,
    /// an exception is thrown.
    ///
    /// @param index Hooks index to check.
    ///
    /// @throw NoSuchHook Thrown if the index is not valid for the hook vector.
    void checkHookIndex(int index) const;

    /// @brief Get hook index
    ///
    /// Utility function to return the index associated with a hook name. It
    /// also checks for validity of the index: if the name is valid, the
    /// index should be valid.  However, as the class only keeps a pointer to
    /// a shared ServerHooks object, it is possible that the object was modified
    /// after the hook_vector_ was sized.  This function performs some checks
    /// on the name and throws an exception if the checks fail.
    ///
    /// @param name Name of the hook to check
    ///
    /// @return Index of the hook in the hook_vector_
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognised.
    /// @throw Unexpected Index not valid for the hook vector.
    int getHookIndex(const std::string& name) const;

    /// @brief Callout pointers equal
    ///
    /// Unary predicate to 

    // Member variables

    /// Context - mapping of names variables that can be of different types.
    ContextCollection context_;

    /// Pointer to the list of hooks registered by the server
    boost::shared_ptr<ServerHooks>      hooks_;     ///< Pointer to hooks

    /// Each element in the following vector corresponds to a single hook and
    /// is an ordered list of callouts for that hook.
    std::vector<std::vector<CalloutPtr> >  hook_vector_;

    /// Index of this library in the list of libraries
    int index_;
};

} // namespace util
} // namespace isc

#endif // LIBRARY_HANDLE_H
