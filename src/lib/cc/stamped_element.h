// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STAMPED_ELEMENT_H
#define STAMPED_ELEMENT_H

#include <cc/base_stamped_element.h>
#include <cc/server_tag.h>
#include <set>

namespace isc {
namespace data {

/// @brief This class represents configuration element which is
/// associated with database identifier, modification timestamp
/// and servers.
///
/// Classes storing Kea configuration should derive from this object
/// to track ids and modification times of the configuration objects.
/// This is specifically required by the Kea Configuration Backend
/// feature which stores and fetches configuration from the database.
/// The configuration elements must be accessible by their database
/// identifiers and modification times.
///
/// @note This class is not derived from @c Element and should not
/// be confused with the classes being derived from @c Element class.
/// Those classes are used to represent JSON structures, whereas this
/// class represents data fetched from the database.
///
/// @todo Find a better name for @c StampedElement.
class StampedElement : public BaseStampedElement {
public:

    /// @brief Constructor.
    ///
    /// Sets timestamp to the current time.
    StampedElement();

    /// @brief Adds new server tag.
    ///
    /// @param server_tag new server tag.
    /// @throw BadValue if the server tag length exceeds 256 characters.
    void setServerTag(const std::string& server_tag) {
        server_tags_.insert(ServerTag(server_tag));
    }

    /// @brief Deletes server tag.
    ///
    /// Remove the first occurrence of the given server tag.
    ///
    /// @param server_tag server tag to delete.
    /// @throw NotFound if the server tag cannot be found.
    void delServerTag(const std::string& server_tag);

    /// @brief Returns server tags.
    ///
    /// @return Server tags.
    std::set<ServerTag> getServerTags() const {
        return (server_tags_);
    }

    /// @brief Checks if the element has the given server tag.
    ///
    /// @param server_tag Server tag to be found.
    /// @return true if the server tag was found, false otherwise.
    bool hasServerTag(const ServerTag& server_tag) const;

    /// @brief Checks if the element has 'all' server tag.
    ///
    /// @return true if the server tag was found, false otherwise.
    bool hasAllServerTag() const;

    /// @brief Returns an object representing metadata to be returned
    /// with objects from the configuration backend.
    ///
    /// @return Pointer to the metadata element.
    isc::data::ElementPtr getMetadata() const;

private:

    /// @brief Holds server tags.
    std::set<ServerTag> server_tags_;
};

} // end of namespace isc::data
} // end of namespace isc

#endif
