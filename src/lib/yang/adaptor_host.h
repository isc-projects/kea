// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_HOST_H
#define ISC_ADAPTOR_HOST_H 1

#include <yang/adaptor.h>

namespace isc {
namespace yang {

/// @brief JSON adaptor for host reservations quoting identifiers.
///
/// The identifier type and identifier value are used as keys in YANG
/// host reservation lists so some constraints were put on their contents.
/// For instance a quoted flex-id identifier raises an error (keys
/// are between quotes in setItem commands).
class AdaptorHost {
public:

    /// @brief The string of standard (vs special or not printable)
    /// characters (digit, letters, -, ., @, _).
    static const std::string STD_CHARACTERS;

    /// @brief Constructor.
    AdaptorHost();

    /// @brief Destructor.
    virtual ~AdaptorHost();

    /// @brief Quote when needed a host identifier.
    ///
    /// Check if the flex-id identifier includes a special (including quote)
    /// or not printable character. When it is the case produce and replace
    /// by a hexadecimal identifier trying first for a quoted identifier.
    ///
    /// @param host The host.
    static void quoteIdentifier(isc::data::ElementPtr host);
};

}  // end of namespace isc::yang
}  // end of namespace isc

#endif // ISC_ADAPTOR_HOST_H
