// Copyright (C) 2018-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SERVER_SELECTOR_H
#define SERVER_SELECTOR_H

#include <cc/server_tag.h>
#include <set>
#include <string>

namespace isc {
namespace db {

/// @brief Server selector for associating objects in a database with
/// specific servers.
///
/// Configuration information stored in the configuration backends can be
/// associated with selected servers, all servers or no particular server.
/// For example: a particular subnet definition in the database may be
/// associated with one server or can be shared by multiple servers.
/// In the latter case, a subnet may be associated with a subset of
/// servers or all servers. An administrator may also add the
/// configuration data into the database and do not associate this data
/// with any particular server.
///
/// When fetching the configuration data from a database or when storing
/// data in the database there is a need to specify which servers this
/// data is associated with. The @c ServerSelector class represents
/// such associations.
///
/// It includes three modes of selection: UNASSIGNED, ALL and SUBSET and
/// several factory functions making associations described above.
///
/// The @c ServerSelector class should be used in objects derived from
/// @c BaseConfigBackendPool and in objects derived from
/// @c BaseConfigBackend to indicate which servers the specific calls
/// exposed by these objects refer to.
///
/// @todo Add server selector for selecting only those configuration
/// elements that are associated with all servers (and not with any
/// particular server tags). Translating this to SQL queries it would
/// probably be an empty or non-existing server tag.
class ServerSelector {
public:

    /// @brief Type of the server selection.
    enum class Type {
        UNASSIGNED,
        ALL,
        SUBSET,
        ANY
    };

    /// @brief Factory returning "unassigned" server selector.
    static ServerSelector UNASSIGNED() {
        ServerSelector selector(Type::UNASSIGNED);
        return (selector);
    }

    /// @brief Factory returning "all servers" selector.
    static ServerSelector ALL() {
        ServerSelector selector(Type::ALL);
        return (selector);
    }

    /// @brief Factory returning selector of one server.
    ///
    /// @param server_tag tag of the single server to be selected.
    static ServerSelector ONE(const std::string& server_tag) {
        ServerSelector selector((data::ServerTag(server_tag)));
        return (selector);
    }

    /// @brief Factory returning "multiple servers" selector.
    ///
    /// @param server_tags set of server tags to be selected.
    /// @throw InvalidOperation if no server tags provided.
    static ServerSelector MULTIPLE(const std::set<std::string>& server_tags);

    /// @brief Factory returning "any server" selector.
    static ServerSelector ANY() {
        ServerSelector selector(Type::ANY);
        return (selector);
    }

    /// @brief Returns type of the selector.
    Type getType() const {
        return (type_);
    }

    /// @brief Returns tags associated with the selector.
    ///
    /// @return server tags for multiple selections and for one server,
    /// empty set for all servers and and unassigned.
    std::set<data::ServerTag> getTags() const {
        return (tags_);
    }

    /// @brief Convenience method checking if the server selector has no tags.
    ///
    /// @return true when the server selector has no tags, false otherwise.
    bool hasNoTags() const {
        return (tags_.empty());
    }

    /// @brief Convenience method checking if the server selector is "unassigned".
    ///
    /// @return true if the selector is "unassigned", false otherwise.
    bool amUnassigned() const {
        return (getType() == Type::UNASSIGNED);
    }

    /// @brief Convenience method checking if the server selector is "all".
    ///
    /// @return true if the selector is "all", false otherwise.
    bool amAll() const {
        return (getType() == Type::ALL);
    }

    /// @brief Convenience method checking if the server selector is "any".
    ///
    /// @return true if the selector is "any", false otherwise.
    bool amAny() const {
        return (getType() == Type::ANY);
    }

    /// @brief Convenience method checking if the server selector has multiple tags.
    ///
    /// @return true if it has multiple tags, false otherwise.
    bool hasMultipleTags() const {
        return (tags_.size() > 1);
    }

private:

    /// @brief Constructor used for "unassigned" and "all" selection types.
    ///
    /// @param type selector type.
    explicit ServerSelector(const Type& type);

    /// @brief Constructor used for selecting a single server.
    ///
    /// @param server_tag tag of the server to be selected.
    explicit ServerSelector(const data::ServerTag& server_tag);

    /// @brief Constructor used for selecting multiple servers.
    ///
    /// @param server_tags set of server tags.
    explicit ServerSelector(const std::set<data::ServerTag>& server_tags);

    /// @brief Selection type used.
    Type type_;

    /// @brief Holds tags of explicitly selected servers.
    std::set<data::ServerTag> tags_;
};


} // end of namespace isc::db
} // end of namespace isc

#endif
