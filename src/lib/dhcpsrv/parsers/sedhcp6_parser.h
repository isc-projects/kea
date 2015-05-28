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

#ifndef SEDHCP6_PARSER_H
#define SEDHCP6_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <exceptions/exceptions.h>

#include <string>

namespace isc {
namespace dhcp {

/// @brief Secure DHCPv6 Parameters
///
/// This class is the parser for the secure DHCPv6 configuration.  This is a
/// map under the top-level "secure" element, and comprises a map of
/// strings.
class SeDhcp6Parser: public DhcpConfigParser {
public:
    /// @brief Keyword and associated value
    typedef std::pair<std::string, std::string> StringPair;

    /// @brief Keyword/value collection of secure DHCPv6 parameters
    typedef std::map<std::string, std::string> StringPairMap;

    /// @brief Constructor
    ///
    /// @param param_name Name of the parameter under which the secure
    ///        DHCPv6 details are held.
    /// @param ctx Parser context.
    SeDhcp6Parser(const std::string& param_name, const ParserContext& ctx);

    /// The destructor.
    virtual ~SeDhcp6Parser()
    {}

    /// @brief Prepare configuration value.
    ///
    /// Parses the set of strings forming the secure DHCPv6 specification and
    /// checks that all are OK.  In particular it checks:
    ///
    /// TODO
    ///
    /// Once all has been validated, TODO
    ///
    /// @param config_value The configuration value for the "secure""
    ///        identifier.
    ///
    /// @throw TODO
    virtual void build(isc::data::ConstElementPtr config_value);

    /// @brief Apply the prepared configuration value to the server.
    ///
    /// With the string validated, TODO
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
    /// @return Pointer to a SeDhcp6Parser.  The caller is responsible for
    ///         destroying the parser after use.
    static DhcpConfigParser* factory(const std::string& param_name,
                                     const ParserContext& ctx) {
        return (new SeDhcp6Parser(param_name, ctx));
    }

protected:
    /// @brief Get secure DHCPv6 parameters
    ///
    /// Used in testing to check that the configuration information has been
    /// parsed correctly.
    ///
    /// @return Reference to the internal map of keyword/value pairs
    ///         representing secure DHCPv6 information.  This is valid only
    ///         for so long as the the parser remains in existence.
    const StringPairMap& getSeDhcp6Parameters() const {
        return (values_);
    }

    /// TODO

private:

    std::map<std::string, std::string> values_; ///< Stored parameter values

    ParserContext ctx_; ///< Parser context
};

};  // namespace dhcp
};  // namespace isc


#endif // SEDHCP6_PARSER_H
