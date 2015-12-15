// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <set>
#include <string>

/// @file   classify.h
///
/// @brief Defines elements for storing the names of client classes
///
/// This file defines common elements used to track the client classes
/// that may be associated with a given packet.  In order to minimize the
/// exposure of the DHCP library to server side concepts such as client
/// classification the classes herein provide a mechanism to maintain lists
/// of class names, rather than the classes they represent.  It is the
/// upper layers' perogative to use these names as they see fit.
///
/// @todo This file should be moved to dhcpsrv eventually as the classification
/// is server side concept. Client has no notion of classifying incoming server
/// messages as it usually talks to only one server. That move is not possible
/// yet, as the Pkt4 and Pkt6 classes have server-side implementation, even
/// though they reside in the dhcp directory.

namespace isc {

namespace dhcp {

    /// @brief Defines a single class name.
    typedef std::string ClientClass;

    /// @brief Container for storing client class names
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
