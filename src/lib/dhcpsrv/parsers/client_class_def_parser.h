// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
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
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void parse(ExpressionPtr& expression,
               isc::data::ConstElementPtr expression_cfg,
               uint16_t family,
               isc::eval::EvalContext::CheckDefined check_defined =
                   isc::eval::EvalContext::acceptAll);
};

/// @brief Parser for a single client class definition.
///
/// This parser creates an instance of a client class definition.
class ClientClassDefParser : public isc::data::SimpleParser {
public:

    /// @brief Parses an entry that describes single client class definition.
    ///
    /// Attempts to add the new class directly into the given dictionary.
    /// This done here to detect duplicate classes prior to commit().
    /// @param class_dictionary dictionary into which the class should be added
    /// @param client_class_def a configuration entry to be parsed.
    /// @param family the address family of the client class.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void parse(ClientClassDictionaryPtr& class_dictionary,
               isc::data::ConstElementPtr client_class_def, uint16_t family);
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
    /// @return a pointer to the filled dictionary
    /// @throw DhcpConfigError if configuration parsing fails.
    ClientClassDictionaryPtr
    parse(isc::data::ConstElementPtr class_def_list, uint16_t family);
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CLIENT_CLASS_DEF_PARSER_H
