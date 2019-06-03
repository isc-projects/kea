// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SERVER_TAG_H
#define SERVER_TAG_H

#include <string>

namespace isc {
namespace data {

/// @brief Represents a server tag.
///
/// The server tag is a label identifying a server or all servers which
/// configuration is stored in the database. The label "all" is reserved
/// and it means "all servers". A configuration object in the database
/// associated with this server tag belongs to all servers. The server
/// tag must not be empty and must not be longer than 256 characters
/// (excluding leading and terminating whitespaces, which are trimmed).
class ServerTag {
public:

    /// @brief Server tag for all servers as text.
    static std::string ALL;

    /// @brief Default constructor.
    ///
    /// Creates server tag for all servers.
    ServerTag();

    /// @brief Constructor.
    ///
    /// @param tag server tag provided as string.
    explicit ServerTag(const std::string& tag);

    /// @brief Checks if the server tag is set to "all servers".
    ///
    /// @return true if the server tag is set to all servers, false
    /// otherwise.
    bool amAll() const;
    /// @brief Returns server tag as string.
    std::string get() const {
        return (tag_);
    }

private:

    /// @brief Holds server tag as string.
    std::string tag_;
};

} // end of namespace isc::data
} // end of namespace isc

#endif // SERVER_TAG_H
