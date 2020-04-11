// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef USER_CONTEXT_UTILS_H
#define USER_CONTEXT_UTILS_H

#include <cc/data.h>

namespace isc {
namespace test {

/// @brief Move comment entries to user-context
///
/// Process an element looking for comment entries in maps and
/// moving them to user-context entries. As the common case is
/// no comment and this routine tries to maximize sharing the
/// standard behavior is just to return the argument unchanged.
///
/// @param element
/// @return a processed copy of element or unmodified element
isc::data::ElementPtr moveComments(isc::data::ElementPtr element);

/// @brief Move comment entries to user-context (const variant)
///
/// @param element
/// @return a processed copy of element or unmodified element
isc::data::ConstElementPtr moveComments(isc::data::ConstElementPtr element);

/// extractComments was removed.

}; // end of isc::test namespace
}; // end of isc namespace

#endif // USER_CONTEXT_UTILS_H
