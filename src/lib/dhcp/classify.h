// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <set>
#include <string>

/// @file   classify.h
///
/// @brief Defines basic elements of client classification.
///
/// This file defines common elements used for client classification.
/// It is simple for now, but the complexity involved in client
/// classification is expected to grow significantly.
///
/// @todo This file should be moved to dhcpsrv eventually as the classification
/// is server side concept. Client has no notion of classifying incoming server
/// messages as it usually talks to only one server. That move is not possible
/// yet, as the Pkt4 and Pkt6 classes have server-side implementation, even
/// though they reside in the dhcp directory.

namespace isc {

namespace dhcp {

    /// Definition of a single class.
    typedef std::string ClientClass;

    /// @brief Container for storing client classes
    ///
    /// Depending on how you look at it, this is either a little more than just
    /// a set of strings or a client classifier that performs access control.
    /// For now, it is a simple access list that may contain zero or more
    /// class names. It is expected to grow in complexity once support for
    /// client classes becomes more feature rich.
    ///
    /// Note: This class is derived from std::set which may not have Doxygen
    /// documentation. See  http://www.cplusplus.com/reference/set/set/.
    class ClientClasses : public std::set<ClientClass> {
    public:

        /// @brief Default constructor.
        ClientClasses() : std::set<ClientClass>() {
        }

        /// @brief Constructor from comma separated values.
        ///
        /// @param class_names A string containing a client classes separated
        /// with commas. The class names are trimmed before insertion to the set.
        ClientClasses(const std::string& class_names);

        /// @brief returns if class x belongs to the defined classes
        ///
        /// @param x client class to be checked
        /// @return true if x belongs to the classes
        bool
        contains(const ClientClass& x) const {
            return (find(x) != end());
        }
    };

};

};

#endif /* CLASSIFY_H */
