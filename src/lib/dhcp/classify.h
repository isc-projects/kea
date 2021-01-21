// Copyright (C) 2014-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <string>
#include <iterator>
#include <list>
#include <unordered_set>

/// @file   classify.h
///
/// @brief Defines elements for storing the names of client classes
///
/// This file defines common elements used to track the client classes
/// that may be associated with a given packet.  In order to minimize the
/// exposure of the DHCP library to server side concepts such as client
/// classification the classes herein provide a mechanism to maintain lists
/// of class names, rather than the classes they represent.  It is the
/// upper layers' prerogative to use these names as they see fit.
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
    /// Both a list to iterate on it in insert order and unordered
    /// set of names for existence.
    class ClientClasses {
    public:

        /// @brief Type of iterators
        typedef std::list<ClientClass>::const_iterator const_iterator;

        /// @brief Default constructor.
        ClientClasses() : list_(), set_() {
        }

        /// @brief Constructor from comma separated values.
        ///
        /// @param class_names A string containing a client classes separated
        /// with commas. The class names are trimmed before insertion to the set.
        ClientClasses(const ClientClass& class_names);

        /// @brief Insert an element.
        ///
        /// @param class_name The name of the class to insert
        void insert(const ClientClass& class_name) {
            list_.push_back(class_name);
            set_.insert(class_name);
        }

        /// @brief Erase element by name.
        ///
        /// @param class_name The name of the class to erase.
        void erase(const ClientClass& class_name);

        /// @brief Check if classes is empty.
        bool empty() const {
            return (list_.empty());
        }

        /// @brief Returns the number of classes.
        ///
        /// @note; in C++ 11 list size complexity is constant so
        /// there is no advantage to use the set part.
        size_t size() const {
            return (list_.size());
        }

        /// @brief Iterator to the first element.
        const_iterator cbegin() const {
            return (list_.cbegin());
        }

        /// @brief Iterator to the past the end element.
        const_iterator cend() const {
            return (list_.cend());
        }

        /// @brief returns if class x belongs to the defined classes
        ///
        /// @param x client class to be checked
        /// @return true if x belongs to the classes
        bool contains(const ClientClass& x) const {
            return (set_.count(x) != 0);
        }

        /// @brief Clears containers.
        void clear() {
            list_.clear();
            set_.clear();
        }

        /// @brief Returns all class names as text
        ///
        /// @param separator Separator to be used between class names. The
        /// default separator comprises comma sign followed by space
        /// character.
        std::string toText(const std::string& separator = ", ") const;

    private:
        /// @brief List/ordered part
        std::list<ClientClass> list_;

        /// @brief Set/unordered part
        std::unordered_set<ClientClass> set_;
    };

};

};

#endif /* CLASSIFY_H */
