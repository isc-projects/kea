// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

#include <string.h>

namespace isc {
namespace log {

typedef const char* MessageID;

/// \brief Compare MessageID for Equality
///
/// \param m1 First message ID
/// \param m2 Second message ID
/// \return true if they are equal, false if not
bool equalMessageID(const MessageID& m1, const MessageID& m2);

} // namespace log
} // namespace isc



#endif // MESSAGE_TYPES_H
