// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_HOOKS_LIBRARIES_H
#define CFG_HOOKS_LIBRARIES_H

#include <exceptions/exceptions.h>
#include <hooks/libinfo.h>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when a library failed to validate
class InvalidHooksLibraries : public Exception {
 public:
    InvalidHooksLibraries(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Wrapper class that holds hooks libraries
///
/// This was moved from HooksLibrariesParser
///
/// However, this class does more than just check the list of library names.
/// It does two other things:
/// # validate libraries
/// # load libraries
class CfgHooksLibraries {

 public:
    /// @brief Default constructor.
    ///
    CfgHooksLibraries() : libraries_() { }

    /// @brief Adds additional hooks libraries.
    ///
    /// @param libname full filename with path to the library.
    /// @param parameters map of parameters that configure the library.
    ///
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

    /// @brief Verifies that libraries stored in libraries_ are valid.
    ///
    /// This method is a smart wrapper around @ref
    /// isc::hooks::HooksManager::validateLibraries().
    /// It tries to validate all the libraries stored in libraries_.
    ///
    /// @param position position of the hooks-library map for error reporting
    /// @throw InvalidHooksLibraries if any issue is discovered.
    void verifyLibraries(const isc::data::Element::Position& position) const;

    /// @brief Commits hooks libraries configuration.
    ///
    /// This method calls necessary methods in HooksManager that will unload
    /// any libraries that may be currently loaded and will load the actual
    /// libraries. Providing that the specified libraries are valid and are
    /// different to those already loaded, this method loads the new set of
    /// libraries (and unloads the existing set).
    ///
    /// @throw InvalidHooksLibraries if the call to HooksManager fails.
    void loadLibraries() const;

 protected:
    /// @brief List of hooks libraries with their configuration parameters
    isc::hooks::HookLibsCollection libraries_;
};

};
};

#endif
