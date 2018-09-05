// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_H
#define BASE_CONFIG_BACKEND_H

#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <string>

namespace isc {
namespace cb {

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
