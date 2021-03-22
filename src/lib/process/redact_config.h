// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef REDACT_CONFIG_H
#define REDACT_CONFIG_H

#include <cc/data.h>
#include <set>

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
/// @param config the Element tree structure that describes the configuration.
/// @param redacted The reference to redacted flag: true means the result
/// was redacted so cannot be shared.
/// @param follow The set of keywords of subtrees where a password or a
/// secret can be found.
/// @return unmodified config or a copy of the config where passwords and
/// secrets were replaced by asterisks so can be safely logged to an
/// unprivileged place.
isc::data::ConstElementPtr redactConfig(isc::data::ConstElementPtr elem,
                                        bool& redacted,
                                        const std::set<std::string>& follow);

} // namespace process
} // namespace isc

#endif // REDACT_CONFIG_H
