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
/// tag must not be empty, must not be longer than 256 characters
/// (excluding leading and terminating whitespaces, which are trimmed)
/// and must not be set to "any" which has a special meaning for the
/// server selector.
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
    /// @param tag server tag provided as string. The tag is converted to
    /// lower case.
    explicit ServerTag(const std::string& tag);

    /// @brief Checks if the server tag is set to "all servers".
    ///
    /// @return true if the server tag is set to all servers, false
    /// otherwise.
    bool amAll() const;

    /// @brief Returns server tag as string.
    ///
    /// @return lower case server tag.
    std::string get() const {
        return (tag_);
    }

    /// @brief Overload of the less operator for using @c ServerTag in sets.
    ///
    /// @param other other server tag to compare to.
    /// @return true if this server tag is less than the other server tag.
    bool operator<(const ServerTag& other) const {
        return (tag_ < other.tag_);
    }

private:

    /// @brief Holds server tag as string.
    std::string tag_;
};

/// @brief Insert the @c ServerTag as a string into stream.
///
/// @param os stream to insert server tag into.
/// @param server_tag server tag to be converted to text and
/// inserted into a stream.
/// @return Reference to the stream object with inserted server
/// tag.
std::ostream&
operator<<(std::ostream& os, const ServerTag& server_tag);

} // end of namespace isc::data
} // end of namespace isc

#endif // SERVER_TAG_H
