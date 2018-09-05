// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_H
#define BASE_CONFIG_BACKEND_H

#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <set>
#include <string>

namespace isc {
namespace cb {

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
/// with any patrticular server.
///
/// When fetching the configuration data from a databse or when storing
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
class ServerSelector {
public:

    /// @brief Type of the server selection.
    enum class Type {
        UNASSIGNED,
        ALL,
        SUBSET
    };

    /// @brief Factory returning "unassigned" server selector.
    static ServerSelector& UNASSIGNED() {
        static ServerSelector selector(Type::UNASSIGNED);
        return (selector);
    }

    /// @brief Factory returning "all servers" selector.
    static ServerSelector& ALL() {
        static ServerSelector selector(Type::ALL);
        return (selector);
    }

    /// @brief Factory returning selector of one server.
    ///
    /// @param server_tag tag of the single server to be selected.
    static ServerSelector& ONE(const std::string& server_tag) {
        static ServerSelector selector(server_tag);
        return (selector);
    }

    /// @brief Factory returning "multiple servers" selector.
    ///
    /// @param server_tags set of server tags to be selected.
    static ServerSelector& MULTIPLE(const std::set<std::string>& server_tags) {
        static ServerSelector selector(server_tags);
        return (selector);
    }

    /// @brief Returns type of the selector.
    Type getType() const {
        return (type_);
    }

    /// @brief Returns tags associated with the selector.
    ///
    /// @return server tags for mutliple selections and for one server,
    /// empty set for all servers and and unassigned.
    std::set<std::string> getTags() const {
        return (tags_);
    }

private:

    /// @brief Constructor used for "unassigned" and "all" slection types.
    ///
    /// @param type selector type.
    explicit ServerSelector(const Type& type)
        : type_(type), tags_() {
    }

    /// @brief Constructor used for selecting a single server.
    ///
    /// @param server_tag tag of the server to be selected.
    explicit ServerSelector(const std::string& server_tag)
        : type_(Type::SUBSET), tags_() {
        tags_.insert(server_tag);
    }

    /// @brief Constructor used for selecting multiple servers.
    ///
    /// @param server_tags set of server tags.
    explicit ServerSelector(const std::set<std::string>& server_tags)
        : type_(Type::SUBSET), tags_(server_tags) {
    }

    /// @brief Selection type used.
    Type type_;

    /// @brief Holds tags of explicitly selected servers.
    std::set<std::string> tags_;
};

/// @brief Base class for server specific configuration backends.
class BaseConfigBackend {
public:

    /// @brief Virtual destructor.
    virtual ~BaseConfigBackend() { }

    /// @brief Returns backend type in the textual format.
    virtual std::string getType() const = 0;

    /// @brief Returns backend host.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return host on which the database is located.
    virtual std::string getHost() const = 0;

    /// @brief Returns backend port number.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return Port number on which database service is available.
    virtual uint16_t getPort() const = 0;
};

/// @brief Shared pointer to the @c BaseConfigBackend.
typedef boost::shared_ptr<BaseConfigBackend> BaseConfigBackendPtr;

} // end of namespace isc::cb
} // end of namespace isc

#endif // BASE_CONFIG_BACKEND_H
