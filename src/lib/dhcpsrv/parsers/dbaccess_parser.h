// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef DBACCESS_PARSER_H
#define DBACCESS_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <exceptions/exceptions.h>

#include <string>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when 'type' keyword is missing from string
///
/// This condition is checked, but should never occur because 'type' is marked
/// as mandatory in the .spec file for the server.
class TypeKeywordMissing : public isc::Exception {
public:
    TypeKeywordMissing(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Parse Lease Database Parameters
///
/// This class is the parser for the lease database configuration.  This is a
/// map under the top-level "lease-database" element, and comprises a map of
/// strings.
///
/// Only the "type" sub-element is mandatory: the remaining sub-elements 
/// depend on the database chosen.
class DbAccessParser: public DhcpConfigParser {
public:

    /// @brief Specifies the database type
    typedef enum {
        LEASE_DB = 1,
        HOSTS_DB = 2
    } DBType;

    /// @brief Keyword and associated value
    typedef std::pair<std::string, std::string> StringPair;

    /// @brief Keyword/value collection of database access parameters
    typedef std::map<std::string, std::string> StringPairMap;

    /// @brief Constructor
    ///
    /// @param param_name Name of the parameter under which the database
    ///        access details are held.
    /// @param db_type Specifies database type (lease or hosts)
    /// @param ctx Parser context.
    DbAccessParser(const std::string& param_name, DBType db_type,
                   const ParserContext& ctx);

    /// The destructor.
    virtual ~DbAccessParser()
    {}

    /// @brief Prepare configuration value.
    ///
    /// Parses the set of strings forming the database access specification and
    /// checks that all are OK.  In particular it checks:
    ///
    /// - "type" is "memfile", "mysql" or "postgresql"
    /// - "lfc-interval" is a number from the range of 0 to 4294967295.
    ///
    /// Once all has been validated, constructs the database access string
    /// expected by the lease manager.
    ///
    /// @param config_value The configuration value for the "lease-database"
    ///        identifier.
    ///
    /// @throw isc::BadValue The 'type' keyword contains an unknown database
    ///        type.
    /// @throw isc::dhcp::MissingTypeKeyword The 'type' keyword is missing from
    ///        the list of database access keywords.
    virtual void build(isc::data::ConstElementPtr config_value);

    /// @brief Apply the prepared configuration value to the server.
    ///
    /// With the string validated, this closes the currently open database (if
    /// any), then opens a database corresponding to the stored string.
    ///
    /// This method is expected to be called after \c build(), and only once.
    /// The result is undefined otherwise.
    virtual void commit();

    /// @brief Factory method to create parser
    ///
    /// Creates an instance of this parser.
    ///
    /// @param param_name Name of the parameter used to access the
    ///         configuration.
    /// @param ctx Parser context.
    ///
    /// @return Pointer to a DbAccessParser.  The caller is responsible for
    ///         destroying the parser after use.
    static DhcpConfigParser* factory(const std::string& param_name,
                                     const ParserContext& ctx) {
        if (param_name == "lease-database") {
            return (new DbAccessParser(param_name, DbAccessParser::LEASE_DB, ctx));
        } else if (param_name == "hosts-database") {
            return (new DbAccessParser(param_name, DbAccessParser::HOSTS_DB, ctx));
        } else {
            isc_throw(BadValue, "Unexpected parameter name (" << param_name
                      << ") passed to DbAccessParser::factory");
        }
    }

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

    ParserContext ctx_; ///< Parser context
};

};  // namespace dhcp
};  // namespace isc


#endif // DBACCESS_PARSER_H
