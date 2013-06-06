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

#include <exceptions/exceptions.h>
#include <util/hooks/server_hooks.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <string>

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

class NoSuchLibraryContext : public Exception {
public:
    NoSuchLibraryContext(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Invalid index
///
/// Thrown if an attempt is made to obtain a library handle but the current
/// library handle index is invalid.  This will occur if the method
/// LibraryHandleCollection::getLibraryHandle() is called outside of a callout.

class InvalidIndex : public Exception {
public:
    InvalidIndex(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

// Forward declaration for CalloutHandle
class CalloutHandle;

/// Typedef for a callout pointer.  (Callouts must have "C" linkage.)
extern "C" {
    typedef int (*CalloutPtr)(CalloutHandle&);
};


/// @brief Library handle
///
/// This class is used to manage a loaded library.  It is used by the user
/// library to register callouts and by the HookManager to call them.
///
/// The functions related to loading and unloading the asssociated library are
/// handled in the related LibraryManager class - there is a 1:1 correspondence
/// between LibraryManager and LibraryHandle objects.  The separation prevents
/// the user library callouts from tinkering around with the loading and
/// unloading of libraries.

class LibraryHandle {
public:

    /// @brief Constructor
    ///
    /// This is passed the ServerHooks object, which is used both to size the
    /// internal hook vector and in the registration of callouts.
    ///
    /// @param hooks Pointer to the hooks registered by the server.
    LibraryHandle(boost::shared_ptr<ServerHooks>& hooks)
        : hooks_(hooks), hook_vector_(hooks->getCount())
    {}

    /// @brief Register a callout on a hook
    ///
    /// Registers a callout function with a given hook.  The callout is added
    /// to the end of the callouts associated with the hook.
    ///
    /// @param name Name of the hook to which the callout is added.
    /// @param callout Pointer to the callout function to be registered.
    ///
    /// @throw NoSuchHook The hook name is unrecognised.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    void registerCallout(const std::string& name, CalloutPtr callout);

    /// @brief De-Register a callout on a hook
    ///
    /// Searches through the functions associated with the named hook and
    /// removes all entries matching the callout.  If there are no matching
    /// callouts, the result is a no-op.
    ///
    /// @param name Name of the hook from which the callout is removed.
    /// @param callout Pointer to the callout function to be removed.
    ///
    /// @throw NoSuchHook The hook name is unrecognised.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    void deregisterCallout(const std::string& name, CalloutPtr callout);

    /// @brief Removes all callouts on a hook
    ///
    /// Removes all callouts associated with a given hook.  This is a no-op
    /// if there are no callouts associated with the hook.
    ///
    /// @param name Name of the hook from which the callouts are removed.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognised.
    void deregisterAll(const std::string& name);

    /// @brief Checks if callouts are present on a hook
    ///
    /// @param index Hook index for which callouts are checked.
    ///
    /// @return true if callouts are present, false if not.
    ///
    /// @throw NoSuchHook Thrown if the index is not valid.
    bool calloutsPresent(int index) const;

    /// @brief Calls the callouts for a given hook
    ///
    /// Calls the callouts associated with the given hook index.
    ///
    /// @param index Index of the hook to call.
    /// @param callout_handle Reference to the CalloutHandle object for the
    ///        current object being processed.
    ///
    /// @return Status return.
    int callCallouts(int index, CalloutHandle& callout_handle);

private:

    /// @brief Check hook index
    ///
    /// Checks that the hook index is valid for the hook vector.  If not,
    /// an exception is thrown.
    ///
    /// @param index Hooks index to check.
    ///
    /// @throw NoSuchHook The index is not valid for the hook vector (i.e.
    ///        less than zero or equal to or greater than the size of the
    ///        vector).
    void checkHookIndex(int index) const;

    /// @brief Get hook index
    ///
    /// Utility function to return the index associated with a hook name. It
    /// also checks for validity of the index: if the name is valid, the
    /// index should be valid.  However, as the class only keeps a pointer to
    /// a shared ServerHooks object, it is possible that the object was modified
    /// after the hook_vector_ was sized: in this case the name could be valid
    /// but the index is invalid.
    ///
    /// @param name Name of the hook to check
    ///
    /// @return Index of the hook in the hook_vector_
    ///
    /// @throw NoSuchHook The hook name is unrecognised.
    /// @throw Unexpected Index of the hook name is not valid for the hook
    ///        vector.
    int getHookIndex(const std::string& name) const;

    // Member variables

    /// Pointer to the list of hooks registered by the server
    boost::shared_ptr<ServerHooks> hooks_;

    /// Each element in the following vector corresponds to a single hook and
    /// is an ordered list of callouts for that hook.
    std::vector<std::vector<CalloutPtr> > hook_vector_;
};


/// @brief Collection of Library Handles
///
/// This simple class is a collection of handles for all libraries loaded.
/// It is pointed to by the CalloutHandle object and is used by that object
/// to locate the correct LibraryHandle should one be requested by a callout
/// function.
///
/// To do this, the class contains an index indicating the "current" handle.
/// This is updated during the calling of callouts: prior to calling a callout
/// associated with a particular LibraryHandle, the index is updated to point to
/// that handle.  If the callout requests access to the LibraryHandle, it is
/// passed a reference to the correct one.

class LibraryHandleCollection {
private:

    /// Private typedef to abbreviate statements in class methods.
    typedef std::vector<boost::shared_ptr<LibraryHandle> > HandleVector;

public:

    /// @brief Constructor
    ///
    /// Initializes member variables, in particular setting the "current library
    /// handle index" to an invalid value.
    LibraryHandleCollection() : curidx_(-1), handles_()
    {}

    /// @brief Add library handle
    ///
    /// Adds a library handle to the collection.  The collection is ordered,
    /// and this adds a library handle to the end of it.
    ///
    /// @param library_handle Pointer to the a library handle to be added.
    void addLibraryHandle(const boost::shared_ptr<LibraryHandle>& handle) {
        handles_.push_back(handle);
    }

    /// @brief Return current library index
    ///
    /// Returns the value of the "current library index".  Although a callout
    /// callout can retrieve this information, it is of limited use: the
    /// value is intended for use by the CalloutHandle object to access the
    /// per-library context.
    ///
    /// @return Current library index value
    int getLibraryIndex() const {
        return (curidx_);
    }

    /// @brief Get current library handle
    ///
    /// Returns a pointer to the current library handle.  This method can
    /// only be called while the code is iterating through the list of
    /// library handles: calling it at any other time is meaningless and will
    /// cause an exception to be thrown.
    ///
    /// @return Pointer to current library handle. This is the handle for the
    ///         library on which the callout currently running is associated.
    boost::shared_ptr<LibraryHandle> getLibraryHandle() const;

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

private:
    /// Index of the library handle on which the currently called callout is
    /// registered.
    int curidx_;

    /// Vector of pointers to library handles.
    HandleVector handles_;
};

} // namespace util
} // namespace isc

#endif // LIBRARY_HANDLE_H
