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

#ifndef CALLOUT_HANDLE_H
#define CALLOUT_HANDLE_H

#include <exceptions/exceptions.h>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace util {

/// @brief No such argument
///
/// Thrown if an attempt is made to use an invalid argument name.
class NoSuchArgument : public Exception {
public:
    NoSuchArgument(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

// Forward declaration of the hook manager class
class HookManager;

/// @brief Per-Packet callout handle
///
/// An object of this class is associated with every packet (or request)
/// processed by the server.  It forms the principle means of passing 
/// data between the server and the user-library callouts.

class CalloutHandle {
private:
    /// Typedef to allow abbreviation of iterator specification in methods
    typedef std::map<std::string, boost::any> ArgumentCollection;

public:

    /// @brief Constructor
    ///
    /// @param manager Pointer to the HookManager object controlling the
    ///        the operations of the hooks.
    CalloutHandle(boost::shared_ptr<HookManager>& manager)
        : arguments_(), manager_(manager), skip_(false)
    {}

    /// @brief Set argument
    ///
    /// Sets an argument.  If the argument is already present, it is replaced.
    ///
    /// @param name Name of the element in the context to set
    /// @param value Value to set
    template <typename T>
    void setArgument(const std::string& name, T value) {
        arguments_[name] = value;
    }

    /// @brief Get argument
    ///
    /// Gets an argument.  If an argument of the given name does not exist,
    /// a "NoSuchArgument" exception is thrown.
    ///
    /// @param name Name of the element in the argument list to set.
    /// @param value [out] Value to set.  The type of "value" is important:
    ///        it must match the type of the value set.
    ///
    /// @throw NoSuchArgument Thrown if no argument with the name "name" is
    ///        present.
    /// @throw boost::bad_any_cast Thrown if the context element is present,
    ///        but the type of the element is not that expected
    template <typename T>
    void getArgument(const std::string& name, T& value) const {
        ArgumentCollection::const_iterator element_ptr = arguments_.find(name);
        if (element_ptr == arguments_.end()) {
            isc_throw(NoSuchArgument, "unable to find argument with name " <<
                      name);
        }

        value = boost::any_cast<T>(element_ptr->second);
    }
    
    /// @brief Get argument names
    ///
    /// Returns a vector holding the names of arguments in the argument
    /// vector.
    ///
    /// @return Vector of strings reflecting argument names
    std::vector<std::string> getArgumentNames() const {
        std::vector<std::string> a;
        return (a);
    }

    /// @brief Delete argument
    ///
    /// Deletes an argument of the given name.  If an argument of that name
    /// does not exist, the method is a no-op.
    ///
    /// @param name Name of the element in the argument list to set.
    void deleteArgument(const std::string& name) {
        static_cast<void>(arguments_.erase(name));
    }

    /// @brief Delete all arguments
    ///
    /// Deletes all arguments associated with this context.
    void deleteAllArguments() {
        arguments_.clear();
    }

    /// @brief Set skip flag
    ///
    /// Sets the "skip" variable in the callout handle.  This variable is
    /// interrogated by the server to see if the remaining callouts should be
    /// bypassed.
    ///
    /// @param skip New value of the "skip" flag.
    void setSkip(bool skip) {
        skip_ = skip;
    }

    /// @brief Get skip flag
    ///
    /// Gets the current value of the "skip" flag.
    ///
    /// @return Current value of the skip flag.
    bool getSkip() const {
        return (skip_);
    }


private:
    /// Collection of arguments passed to the callouts
    ArgumentCollection arguments_;

    /// Controlling hook manager
    boost::shared_ptr<HookManager> manager_;   ///< Controlling hook manager

    /// "Skip" flag, indicating if the caller should bypass remaining callouts.
    bool skip_;
};

} // namespace util
} // namespace isc


#endif // CALLOUT_HANDLE_H
