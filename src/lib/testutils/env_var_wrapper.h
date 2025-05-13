// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ENV_VAR_WRAPPER_H
#define ENV_VAR_WRAPPER_H

#include <string>

namespace isc {
namespace test {

/// @brief Wrapper for environment variable that restores the
/// variable to its original value.
class EnvVarWrapper {
public:
    /// @brief Constructor
    ///
    /// Fetchs and retains the variable's current value as
    /// the "original" value.
    EnvVarWrapper(const std::string& name);

    /// @brief Destructor.
    ///
    /// Restores the original value (if one), otherwise it
    /// unsets it.
    ~EnvVarWrapper();

    /// @brief Fetches the original value of the env variable.
    std::string getOriginalValue() const;

    /// @brief Fetches the current value of the env variable.
    std::string getValue() const;

    /// @brief Sets the current value of the env variable.
    ///
    /// @param value new value of the variable. If empty the
    /// variable is unset.
    void setValue(const std::string value = "");

private:
    /// @brief Name of the variable.
    std::string name_;

    /// @brief Value of the env variable at the time the wrapper
    /// was constructed.
    std::string original_value_;
};

}  // end of isc::test namespace
}  // end of isc namespace

#endif // ENV_VAR_WRAPPER_H
