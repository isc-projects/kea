// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_TO_ELEMENT_H
#define CFG_TO_ELEMENT_H

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <stdint.h>

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

namespace dhcp {

/// @name Constants for unparsing styles
///
//@{
/// Default
static const uint32_t TO_ELEMENT_DEFAULT        = 0x00000000;
/// Add default values
static const uint32_t TO_ELEMENT_ADD_DEFAULTS   = 0x00000001;
/// Ignore disables
static const uint32_t TO_ELEMENT_IGNORE_DISABLE = 0x00000002;
/// Don't copy
static const uint32_t TO_ELEMENT_DO_NOT_COPY    = 0x00000004;

/// Get option names
static const uint32_t TO_ELEMENT_OPTION_NAMES   = 0x00000100;
/// Get ranges as prefixs
static const uint32_t TO_ELEMENT_TRY_PREFIXES   = 0x00000200;

/// Skip (vs throw) on errors
static const uint32_t TO_ELEMENT_SKIP_ERRORS    = 0x80000000;
//@}


/// @brief Abstract class for configuration Cfg_* classes
///
template<typename ... Args>
struct CfgToElement {
    /// Destructor
    virtual ~CfgToElement() { }

    /// @brief Unparse a configuration objet
    ///
    /// Returns an element which must parse into the same objet, i.e.
    /// @code
    /// for all valid config C parse(toElement(parse(C)) == parse(C)
    /// @endcode
    ///
    /// @param extras extra arguments
    /// @param flags a bitfield which can be used to modify the result
    /// @return a pointer to a configuration which can be parsed into
    /// the initial configuration object
    virtual isc::data::ElementPtr toElement(Args... extras,
                                            const uint32_t flags) const = 0;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // CFG_TO_ELEMENT_H
