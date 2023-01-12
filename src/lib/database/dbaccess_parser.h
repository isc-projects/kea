// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DBACCESS_PARSER_H
#define DBACCESS_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <database/database_connection.h>
#include <exceptions/exceptions.h>

#include <string>

namespace isc {
namespace db {

/// @brief Parse Database Parameters
///
/// This class is the parser for the database configuration.  This is a
/// map under the top-level "lease-database", "hosts-database" and
/// "config-database" elements, and comprises a map of strings.
class DbAccessParser: public isc::data::SimpleParser {
public:
    /// @brief Constructor
    DbAccessParser();

    /// The destructor.
    virtual ~DbAccessParser()
    {}

    /// @brief Parse configuration value.
    ///
    /// Parses the set of strings forming the database access specification and
    /// checks that all are OK.  In particular it checks:
    ///
    /// - "type" is "memfile", "mysql" or "postgresql"
    /// - "lfc-interval" is a number from the range of 0 to 4294967295.
    /// - "connect-timeout" is a number from the range of 0 to 4294967295.
    /// - "port" is a number from the range of 0 to 65535.
    ///
    /// Once all has been validated, constructs the database access string.
    ///
    /// @param [out] access_string Generated database access string.
    /// @param database_config The configuration value for the "*-database"
    ///        identifier.
    ///
    /// @throw isc::dhcp::DbConfigError The connection parameters or their
    /// combination is invalid.
    void parse(std::string& access_string,
               isc::data::ConstElementPtr database_config);

    /// @brief Get database access parameters
    ///
    /// Used in testing to check that the configuration information has been
    /// parsed correctly.
    ///
    /// @return Reference to the internal map of keyword/value pairs
    ///         representing database access information.  This is valid only
    ///         for so long as the parser remains in existence.
    const DatabaseConnection::ParameterMap& getDbAccessParameters() const {
        return (values_);
    }
protected:

    /// @brief Construct database access string
    ///
    /// Constructs the database access string from the stored parameters.
    ///
    /// @return Database access string
    std::string getDbAccessString() const;

private:

    DatabaseConnection::ParameterMap values_; ///< Stored parameter values
};

}  // namespace db
}  // namespace isc

#endif // DBACCESS_PARSER_H
