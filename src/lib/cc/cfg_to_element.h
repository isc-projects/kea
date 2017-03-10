// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_TO_ELEMENT_H
#define CFG_TO_ELEMENT_H

#include <exceptions/exceptions.h>
#include <cc/data.h>

namespace isc {

/// @brief Cannot unparse error
///
/// This exception is expected to be thrown when toElement fails
/// and to skip flawed elements is not wanted.
class ToElementError : public isc::Exception {
public:
    ToElementError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

namespace data {

/// @brief Abstract class for configuration Cfg_* classes
///
struct CfgToElement {
    /// Destructor
    virtual ~CfgToElement() { }

    /// @brief Unparse a configuration object
    ///
    /// Returns an element which must parse into the same object, i.e.
    /// @code
    /// for all valid config C parse(parse(C)->toElement()) == parse(C)
    /// @endcode
    ///
    /// @return a pointer to a configuration which can be parsed into
    /// the initial configuration object
    virtual isc::data::ElementPtr toElement() const = 0;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // CFG_TO_ELEMENT_H
