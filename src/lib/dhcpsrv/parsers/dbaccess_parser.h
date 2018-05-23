// Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DBACCESS_PARSER_H
#define DBACCESS_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfg_db_access.h>
#include <exceptions/exceptions.h>

#include <string>

namespace isc {
namespace dhcp {

/// @brief Parse Lease Database Parameters
///
/// This class is the parser for the lease database configuration.  This is a
/// map under the top-level "lease-database" element, and comprises a map of
/// strings.
///
/// Only the "type" sub-element is mandatory: the remaining sub-elements 
/// depend on the database chosen.
class DbAccessParser: public isc::data::SimpleParser {
public:

    /// @brief Keyword and associated value
    typedef std::pair<std::string, std::string> StringPair;

    /// @brief Keyword/value collection of database access parameters
    typedef std::map<std::string, std::string> StringPairMap;

    /// @brief Constructor
    ///
    /// @param db_type Specifies database type (lease or hosts)
    explicit DbAccessParser(DBType db_type);

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
    /// Once all has been validated, constructs the database access string
    /// expected by the lease manager.
    ///
    /// @param cfg_db The configuration where the access string will be set
    /// @param database_config The configuration value for the "*-database"
    ///        identifier.
    ///
    /// @throw isc::dhcp::DhcpConfigError The 'type' keyword contains an
    ///        unknown database type or is missing from the list of
    ///        database access keywords.
    void parse(isc::dhcp::CfgDbAccessPtr& cfg_db,
               isc::data::ConstElementPtr database_config);


protected:
    /// @brief Get database access parameters
    ///
    /// Used in testing to check that the configuration information has been
    /// parsed correctly.
    ///
    /// @return Reference to the internal map of keyword/value pairs
    ///         representing database access information.  This is valid only
    ///         for so long as the the parser remains in existence.
    const StringPairMap& getDbAccessParameters() const {
        return (values_);
    }


    /// @brief Construct database access string
    ///
    /// Constructs the database access string from the stored parameters.
    ///
    /// @return Database access string
    std::string getDbAccessString() const;

private:

    std::map<std::string, std::string> values_; ///< Stored parameter values

    DBType type_; ///< Database type (leases or hosts)
};

};  // namespace dhcp
};  // namespace isc


#endif // DBACCESS_PARSER_H
