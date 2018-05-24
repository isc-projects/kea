// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Extract comment entries from user-context
///
/// Process an element looking for user-context entries carrying
/// comments and moving these comments at the same level than
/// user-contexts. As the common case is no comment and this routine
/// tries to maximize sharing the standard behavior is just to return
/// the argument unchanged.
///
/// @param element
/// @return a processed copy of element or unmodified element
isc::data::ElementPtr extractComments(isc::data::ElementPtr element);

}; // end of isc::test namespace
}; // end of isc namespace

#endif // USER_CONTEXT_UTILS_H
