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

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace util {

/// @brief Duplicate Hook
///
/// Thrown if an attempt is made to register a hook with the same name as a
/// previously-registered hook.

class DuplicateHook : public Exception {
public:
    DuplicateHook(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


/// @brief Server Hook List
///
/// This class is used by the server-side code to register hooks - points at
/// in the server processing at which libraries can register functions
/// (callouts) that the server will call.  These functions can modify data and
/// so affect the processing of the server.
///
/// The ServerHooks class is little more than a wrapper around the std::map
/// class.  It stores a hook, assigning to it a unique index number.  This
/// number is then used by the server code to identify the hook being called.

class ServerHooks {
public:

    /// Pre-Defined Hooks
    static const int CONTEXT_CREATE = 0;
    static const int CONTEXT_DESTROY = 1;

    /// @brief Constructor
    ///
    /// This pre-registers two hooks, context_create and context_destroy.  These
    /// are called by the server before processing a packet and after processing
    /// for the packet has completed.  They allow the server code to allocate
    /// and destroy per-packet context.
    ///
    /// @throws isc::Unexpected if the registration of the pre-defined hooks
    ///         fails in some way.
    ServerHooks();

    /// @brief Register a hook
    ///
    /// Registers a hook and returns the hook index.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook, to be used in subsequent calls.  This will
    ///         be greater than or equal to zero.
    ///
    /// @throws DuplicateHook A hook with the same name has already been
    ///         registered.
    int registerHook(const std::string& name);

    /// @brief Get hook index
    ///
    /// Returns the index of a hook.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook, to be used in subsequent calls. A value of
    ///         -1 is returned if no hook of the given name is found.
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

private:
    typedef std::map<std::string, int> HookCollection;

    HookCollection  hooks_;     ///< Hook name/index collection
};

} // namespace util
} // namespace isc

#endif  // SERVER_HOOKS_H
