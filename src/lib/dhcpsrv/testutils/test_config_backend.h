// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef TEST_CONFIG_BACKEND_H
#define TEST_CONFIG_BACKEND_H

#include <config.h>

#include <database/database_connection.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Base class for implementing fake backends
template<typename ConfigBackendType>
class TestConfigBackend : public ConfigBackendType {
public:
    /// @brief Constructor
    ///
    /// @param params database connection parameters
    /// @throw BadValue if parameters do not include "type"
    TestConfigBackend(const db::DatabaseConnection::ParameterMap& params)
     : connection_(params) {
        try {
            db_type_ = connection_.getParameter("type");
        } catch (...) {
            isc_throw(BadValue, "Backend parameters must include \"type\"");
        }

        try {
            host_ = connection_.getParameter("host");
        } catch (...) {
            host_ = "default_host";
        }

        try {
            port_ = boost::lexical_cast<uint16_t>(connection_.getParameter("host"));
        } catch (...) {
            port_ = 0;
        }
    }

    /// @brief virtual Destructor.
    virtual ~TestConfigBackend(){};

    /// @brief Returns backend type.
    ///
    /// @return string db_type name
    virtual std::string getType() const {
        return (db_type_);
    }

    /// @brief Returns backend host.
    ///
    /// @return string host
    virtual std::string getHost() const {
        return (host_);
    }

    /// @brief Returns backend port.
    ///
    /// @return uint16_t port
    virtual uint16_t getPort() const {
        return (port_);
    }

    /// @brief Fake database connection
    db::DatabaseConnection connection_;

    /// @brief  Back end type
    std::string db_type_;

    /// @brief  Back end host
    std::string host_;

    /// @brief  Back end port
    uint16_t port_;
};

} // namespace test
} // namespace dhcp
} // namespace isc

#endif // TEST_CONFIG_BACKEND_H
