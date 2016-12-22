// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_TYPES_H
#define HTTP_TYPES_H

#include <utility>

/// @brief HTTP protocol version.
///
/// First value is a major version, second value is a minor version.
typedef std::pair<unsigned, unsigned> HttpVersion;

#endif
