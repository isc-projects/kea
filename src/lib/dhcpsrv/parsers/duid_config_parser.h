// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DUID_CONFIG_PARSER_H
#define DUID_CONFIG_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <stdint.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Parser for server DUID configuration.
///
/// This parser currently supports the following DUID types:
/// - DUID-LLT,
/// - DUID-EN
/// - DUID-LL
///
/// @todo Add support for DUID-UUID in the parser.
class DUIDConfigParser : public DhcpConfigParser {
public:

    /// @brief Constructor.
    DUIDConfigParser();

    /// @brief Parses DUID configuration.
    ///
    /// @param duid_configuration Data element holding a map representing
    /// DUID configuration.
    ///
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual void build(isc::data::ConstElementPtr duid_configuration);

    /// @brief Commit, unused.
    virtual void commit() { }

private:

    /// @brief Validate and set DUID type.
    ///
    /// @param duid_type DUID type in textfual format.
    void setType(const std::string& duid_type) const;

    /// @brief Validate and set identifier.
    ///
    /// @param identifier Identifier.
    void setIdentifier(const std::string& identifier) const;

    /// @brief Validate and set hardware type.
    ///
    /// @param htype Hardware type.
    void setHType(const int64_t htype) const;

    /// @brief Validate and set time value.
    ///
    /// @param new_time Time value to be used for DUID.
    void setTime(const int64_t new_time) const;

    /// @brief Validate and set enterprise id.
    ///
    /// @param enterprise_id Enterprise id.
    void setEnterpriseId(const int64_t enterprise_id) const;

    /// @brief Set persistence flag.
    ///
    /// @param persist A boolean value indicating if the server
    /// identifier should be stored on the disk (if true) or
    /// not (if false).
    void setPersist(const bool persist);

    /// @brief Verifies if the specified parameter is in range.
    ///
    /// Each numeric value must be in range of [0 .. max_value], where
    /// max_value is a maximum value for the numeric type used for this
    /// parameter.
    ///
    /// @param parameter_name Parameter name.
    /// @tparam Numeric type of the specified parameter.
    template<typename NumericType>
    void checkRange(const std::string& parameter_name,
                    const int64_t parameter_value) const;
};

}
} // end of namespace isc

#endif // DUID_CONFIG_PARSER_H
