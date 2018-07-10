// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <eval/token.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Checks dependency on a token.
///
/// It checks if the token is a TokenMember for the given class.
///
/// @param token A pointer to the token.
/// @param name The client class name.
/// @return true if token points to a TokenMember of name, false if not.
bool dependOnClass(const TokenPtr& token, const std::string& name);

/// @brief Checks dependency on an expression.
///
/// It checks if a member of the expression depends on the given class.
///
/// @param expr An expression.
/// @param name The client class name.
/// @return true if a member of expr depends on name, false if not.
bool dependOnClass(const ExpressionPtr& expr, const std::string& name);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
