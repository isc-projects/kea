// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_BASE_H
#define CFG_BASE_H

#include <cc/data.h>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief Abstract class for configuration Cfg_* classes
///
class CfgBase {
public:
    /// @brief Unparse a configuration objet
    ///
    /// Returns an element which must parse into the same objet, i.e.
    /// @code
    /// for all valid config C parse(unparse(parse(C)) == parse(C)
    /// @endcode
    ///
    /// @param flags a bitfield which can be used to modify the result
    /// @return a pointer to a configuration which can be parsed into
    /// the initial configuration object
    virtual ConstElementPtr unparse(const uint32_t flags) = 0;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // CFG_BASE_H
