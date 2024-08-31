// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKS_CONFIG_H
#define HOOKS_CONFIG_H

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <hooks/libinfo.h>

namespace isc {
namespace hooks {

/// @brief Exception thrown when a library failed to validate
class InvalidHooksLibraries : public Exception {
 public:
    InvalidHooksLibraries(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Wrapper class that holds hooks libraries configuration
///
/// This was moved from HooksLibrariesParser
///
/// However, this class does more than just check the list of library names.
/// It does two other things:
/// # validate libraries
/// # load libraries
/// and it provides a toElement() method to unparse a configuration.
///
/// @todo add toElement() unit tests
class HooksConfig : public isc::data::CfgToElement {
public:
    /// @brief Default constructor.
    ///
    HooksConfig() : libraries_() { }

    /// @brief Adds additional hooks libraries.
    ///
    /// @param libname full filename with path to the library.
    /// @param parameters map of parameters that configure the library.
    void add(std::string libname, isc::data::ConstElementPtr parameters) {
        libraries_.push_back(make_pair(libname, parameters));
    }

    /// @brief Provides access to the configured hooks libraries.
    ///
    /// @note The const reference returned is only valid as long as the
    /// object that returned it.
    const isc::hooks::HookLibsCollection& get() const {
        return libraries_;
    }

    /// @brief Removes all configured hooks libraries.
    void clear() {
        libraries_.clear();
    }

    /// @brief Compares two Hooks Config classes for equality
    ///
    /// @param other other hooksconfig to compare with
    bool equal(const HooksConfig& other) const;

    /// @brief Verifies that libraries stored in libraries_ are valid.
    ///
    /// This method is a smart wrapper around @ref
    /// isc::hooks::HooksManager::validateLibraries().
    /// It tries to validate all the libraries stored in libraries_.
    ///
    /// @param position position of the hooks-library map for error reporting
    /// @param multi_threading_enabled The flag which indicates if MT is enabled
    ///        (used to check hook libraries compatibility with MT).
    ///
    /// @throw InvalidHooksLibraries if any issue is discovered.
    void verifyLibraries(const isc::data::Element::Position& position,
                         bool multi_threading_enabled) const;

    /// @brief Commits hooks libraries configuration.
    ///
    /// This method calls necessary methods in HooksManager that will unload
    /// any libraries that may be currently loaded and will load the actual
    /// libraries. Providing that the specified libraries are valid and are
    /// different to those already loaded, this method loads the new set of
    /// libraries (and unloads the existing set).
    ///
    /// @param multi_threading_enabled The flag which indicates if MT is enabled
    ///        (used to check hook libraries compatibility with MT).
    ///
    /// @throw InvalidHooksLibraries if the call to HooksManager fails.
    void loadLibraries(bool multi_threading_enabled) const;

    /// @brief Unparse a configuration object
    ///
    /// Returns an element which must parse into the same object, i.e.
    /// @code
    /// for all valid config C parse(parse(C)->toElement()) == parse(C)
    /// @endcode
    ///
    /// @return a pointer to a configuration which can be parsed into
    /// the initial configuration object
    isc::data::ElementPtr toElement() const;

private:
    /// @brief List of hooks libraries with their configuration parameters
    isc::hooks::HookLibsCollection libraries_;
};

}  // namespace hooks
}  // namespace isc

#endif // HOOKS_CONFIG_H
