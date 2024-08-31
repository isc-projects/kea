// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT_CLASS_DEF_PARSER_H
#define CLIENT_CLASS_DEF_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <eval/eval_context.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <functional>
#include <list>

/// @file client_class_def_parser.h
///
/// @brief Parsers for client class definitions
///
/// These parsers are used to parse lists of client class definitions
/// into a ClientClassDictionary of ClientClassDef instances.  Each
/// ClientClassDef consists of (at least) a name, an expression, option-def
/// and option-data.  Currently only a not empty name is required.
///
/// There parsers defined are:
///
/// ClientClassDefListParser  - creates a ClientClassDictionary from a list
/// of element maps, where each map contains the entries that specify a
/// single class.  The names of the classes in the are expected to be
/// unique.  Attempting to define a duplicate class will result in an
/// DhcpConfigError throw.  At the end the dictionary is stored by the CfgMgr.
///
/// ClientClassDefParser - creates a ClientClassDefinition from an element
/// map. The elements are as follows:
///
/// -# "name" - a string containing the name of the class
///
/// -# "test" - a string containing the logical expression used to determine
/// membership in the class. This is passed into the eval parser.
///
/// -# "option-def" - a list which defines the options which processing
/// is deferred. This element is optional and parsed using the @ref
/// isc::dhcp::OptionDefParser. A check is done to verify definitions
/// are only for deferred processing option (DHCPv4 43 and 224-254).
///
/// -# "option-data" - a list which defines the options that should be
/// assigned to remembers of the class.  This element is optional and parsed
/// using the @ref isc::dhcp::OptionDataListParser.
///
/// ExpressionParser  - creates an eval::Expression from a string element,
/// using the Eval Parser.
///
namespace isc {
namespace dhcp {

/// @brief Parser for a logical expression
///
/// This parser creates an instance of an Expression from a string.  The
/// string is passed to the Eval Parser and the resultant Expression is
/// stored into the ExpressionPtr reference passed into the constructor.
class ExpressionParser : public isc::data::SimpleParser {
public:

    /// @brief Parses an expression configuration element into an Expression
    ///
    /// @param expression variable in which to store the new expression
    /// @param expression_cfg the configuration entry to be parsed.
    /// @param family the address family of the expression.
    /// @param check_defined a closure to check if a client class is defined.
    /// @param parser_type the expected type of the evaluated expression.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void parse(ExpressionPtr& expression,
               isc::data::ConstElementPtr expression_cfg,
               uint16_t family,
               isc::eval::EvalContext::CheckDefined check_defined = isc::eval::EvalContext::acceptAll,
               isc::eval::EvalContext::ParserType parser_type = isc::eval::EvalContext::PARSER_BOOL);
};

/// @brief Parser for a single client class definition.
///
/// This parser creates an instance of a client class definition.
class ClientClassDefParser : public isc::data::SimpleParser {
public:

    /// @brief Virtual destructor.
    virtual ~ClientClassDefParser() {
    }

    /// @brief Parses an entry that describes single client class definition.
    ///
    /// Attempts to add the new class directly into the given dictionary.
    /// This done here to detect duplicate classes prior to commit().
    /// @param class_dictionary dictionary into which the class should be added
    /// @param client_class_def a configuration entry to be parsed.
    /// @param family the address family of the client class.
    /// @param append_error_position Boolean flag indicating if position
    /// of the parsed string within parsed JSON should be appended. The
    /// default setting is to append it, but it is typically set to false
    /// when this parser is used by hooks libraries.
    /// @param check_dependencies indicates if the parser should evaluate an
    /// expression to see if the referenced client classes exist.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void parse(ClientClassDictionaryPtr& class_dictionary,
               isc::data::ConstElementPtr client_class_def,
               uint16_t family,
               bool append_error_position = true,
               bool check_dependencies = true);

    /// @brief Iterates over class parameters and checks if they are supported.
    ///
    /// This method should be called by hooks libraries which do not use Bison
    /// to validate class syntax prior to parsing the client class information.
    ///
    /// @param class_def_cfg class configuration entry.
    /// @param family the address family of the client class.
    ///
    /// @throw DhcpConfigError if any of the parameters is not supported.
    void checkParametersSupported(const isc::data::ConstElementPtr& class_def_cfg,
                                  const uint16_t family);

protected:

    /// @brief Returns an instance of the @c OptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for option data.
    ///
    /// @param address_family @c AF_INET (for DHCPv4) or @c AF_INET6 (for DHCPv6).
    /// @param cfg_option_def structure holding option definitions.
    ///
    /// @return an instance of the @c OptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser(const uint16_t address_family,
                               CfgOptionDefPtr cfg_option_def) const;
};

/// @brief Defines a pointer to a ClientClassDefParser
typedef boost::shared_ptr<ClientClassDefParser> ClientClassDefParserPtr;

/// @brief Parser for a list of client class definitions.
///
/// This parser iterates over all configuration entries that define
/// client classes and creates ClientClassDef instances for each.
/// When the parsing successfully completes, the collection of
/// created definitions is given to the CfgMgr.
class ClientClassDefListParser : public isc::data::SimpleParser {
public:

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries, creates instances
    /// of client class definitions and tries to adds them to the
    /// local dictionary. At the end the dictionary is returned.
    ///
    /// @param class_def_list pointer to an element that holds entries
    /// for client class definitions.
    /// @param family the address family of the client class definitions.
    /// @param check_dependencies indicates if the parser should evaluate an
    /// expression to see if the referenced client classes exist.
    /// @return a pointer to the filled dictionary
    /// @throw DhcpConfigError if configuration parsing fails.
    ClientClassDictionaryPtr
    parse(isc::data::ConstElementPtr class_def_list, uint16_t family,
          bool check_dependencies = true);
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CLIENT_CLASS_DEF_PARSER_H
