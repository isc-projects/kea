// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEGAL_SYSLOG_H
#define LEGAL_SYSLOG_H

#include <dhcpsrv/legal_log_mgr_factory.h>

namespace isc {
namespace legal_log {

class LegalSyslog : public isc::dhcp::LegalLogMgr {
public:
    /// @brief Constructor.
    ///
    /// @note The supported parameters are:
    /// - syslog parameters:
    ///       - pattern
    ///       - facility
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the manager configuration.
    LegalSyslog(const isc::db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ///
    /// The destructor does call the close method.
    virtual ~LegalSyslog() = default;

    /// @brief Opens the store.
    virtual void open();

    /// @brief Closes the store.
    virtual void close();

    /// @brief Appends a string to the store with a timestamp and address.
    ///
    /// @param text String to append
    /// @param addr Address or prefix
    /// @throw LegalLogMgrError if the write fails
    virtual void writeln(const std::string& text, const std::string& addr);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "logfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const;

private:
    /// @brief Logger used to write to syslog.
    std::shared_ptr<isc::log::Logger> logger_;

public:
    /// @brief Factory class method.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @return The Syslog File Store Backend.
    static isc::dhcp::LegalLogMgrPtr
    factory(const isc::db::DatabaseConnection::ParameterMap& parameters);
};

} // namespace legal_log
} // namespace isc

#endif
