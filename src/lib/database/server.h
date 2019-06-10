// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_SERVER_H
#define DB_SERVER_H

#include <cc/stamped_element.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace db {

class Server;

/// @brief Shared pointer to the @c Server class.
typedef boost::shared_ptr<Server> ServerPtr;

/// @brief Represents information about a Kea server in the database.
///
/// The configuration backend holds the information about the servers
/// for which the backend holds the configuration information. The
/// information includes the server tag (unique name), server description
/// provided by the administrator and the metadata.
///
/// This class extends the base class with the server description field.
class Server : public data::StampedElement {
public:

    /// @brief Constructor.
    ///
    /// @param tag server tag.
    /// @param description server description.
    Server(const data::ServerTag& tag, const std::string& description);

    /// @brief Factory function to be used to create an instance of the
    /// @c Server object.
    ///
    /// @param tag server tag.
    /// @param description server description.
    ///
    /// @return Pointer to the server instance.
    /// @throw BadValue if the server tag exceeds 256 characters or the
    /// description exceeds 65536 characters.
    static ServerPtr create(const data::ServerTag& tag,
                            const std::string& description = "");

    /// @brief Returns the description of the server.
    ///
    /// @return Description of the server or an empty string if no
    /// description was specified.
    std::string getDescription() const {
        return (description_);
    }

private:

    /// @brief Description of the server.
    std::string description_;
};

} // end of namespace isc::db
} // end of namespace isc

#endif // DB_SERVER_H
