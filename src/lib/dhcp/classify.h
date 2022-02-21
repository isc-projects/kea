// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
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

    /// @brief Tag for the sequence index.
    struct ClassSequenceTag { };

    /// @brief Tag for the name index.
    struct ClassNameTag { };

    /// @brief the client class multi-index.
    typedef boost::multi_index_container<
        ClientClass,
        boost::multi_index::indexed_by<
            // First index is the sequence one.
            boost::multi_index::sequenced<
                boost::multi_index::tag<ClassSequenceTag>
            >,
            // Second index is the name hash one.
            boost::multi_index::hashed_unique<
                boost::multi_index::tag<ClassNameTag>,
                boost::multi_index::identity<ClientClass>
            >
        >
    > ClientClassContainer;

    /// @brief Container for storing client class names
    ///
    /// Both a list to iterate on it in insert order and unordered
    /// set of names for existence.
    class ClientClasses {
    public:

        /// @brief Type of iterators
        typedef ClientClassContainer::const_iterator const_iterator;

        /// @brief Default constructor.
        ClientClasses() : container_() {
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
            static_cast<void>(container_.push_back(class_name));
        }

        /// @brief Erase element by name.
        ///
        /// @param class_name The name of the class to erase.
        void erase(const ClientClass& class_name);

        /// @brief Check if classes is empty.
        bool empty() const {
            return (container_.empty());
        }

        /// @brief Returns the number of classes.
        ///
        /// @note; in C++ 11 list size complexity is constant so
        /// there is no advantage to use the set part.
        size_t size() const {
            return (container_.size());
        }

        /// @brief Iterator to the first element.
        const_iterator cbegin() const {
            return (container_.cbegin());
        }

        /// @brief Iterator to the past the end element.
        const_iterator cend() const {
            return (container_.cend());
        }

        /// @brief returns if class x belongs to the defined classes
        ///
        /// @param x client class to be checked
        /// @return true if x belongs to the classes
        bool contains(const ClientClass& x) const;

        /// @brief Clears containers.
        void clear() {
            container_.clear();
        }

        /// @brief Returns all class names as text
        ///
        /// @param separator Separator to be used between class names. The
        /// default separator comprises comma sign followed by space
        /// character.
        std::string toText(const std::string& separator = ", ") const;

    private:
        /// @brief container part
        ClientClassContainer container_;
    };
}

}

#endif /* CLASSIFY_H */
