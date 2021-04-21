// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef REDACT_CONFIG_H
#define REDACT_CONFIG_H

#include <cc/data.h>
#include <list>

namespace isc {
namespace process {

/// @brief Redact a configuration.
///
/// This method walks on the configuration tree:
///  - it copies only subtrees where a change was done.
///  - it replaces passwords and secrets by asterisks.
///  - it skips user context.
///  - if a not empty list of keywords is given it follows only them.
///
/// @param element initially the Element tree structure that describe the
/// configuration and smaller subtrees in recursive calls.
/// @param json_path JSON path to redact
///
/// @return a copy of the config where passwords and secrets were replaced by
/// asterisks so it can be safely logged to an unprivileged place.
isc::data::ConstElementPtr
redactConfig(isc::data::ConstElementPtr const& element,
             std::list<std::string> const& json_path = {"*"});

} // namespace process
} // namespace isc

#endif // REDACT_CONFIG_H
