// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_SERVER_COLLECTION_H
#define DB_SERVER_COLLECTION_H

#include <database/server.h>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>

namespace isc {
namespace db {

/// @brief Tag identifying an index by server tag.
struct ServerTagIndexTag { };

/// @brief Multi index container for @c Server.
///
/// It merely contains one index at the moment, but the number of
/// indexes is likely to grow.
typedef boost::multi_index_container<
    ServerPtr,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<ServerTagIndexTag>,
            boost::multi_index::const_mem_fun<Server, std::string,
                                              &Server::getServerTagAsText>
        >
    >
> ServerCollection;

/// @brief Utility class used to fetch @c Server objects from the
/// @c ServerCollection.
class ServerFetcher {
public:

    /// @brief Fetches server from the collection by tag.
    ///
    /// @return Pointer to the @c Server object or null if no such object
    /// was found.
    static ServerPtr get(const ServerCollection& collection,
                         const data::ServerTag& server_tag);
};

} // end of namespace isc::db
} // end of namespace isc

#endif
