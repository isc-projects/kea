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

#ifndef CLIENT_CLASS_DEF_PARSER_H
#define CLIENT_CLASS_DEF_PARSER_H

#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>

/// @file client_class_def.h
///
/// @brief Parsers for client class definitions
///
/// These parsers are used to parse lists of client class definitions
/// into a ClientClassDictionary of ClientClassDef instances.  Each
/// ClientClassDef consists of (at least) a name, an expression, and
/// option-data.  The latter two are currently optional.
///
/// There parsers defined are:
///
/// ClientClassDefListParser  - creates a ClientClassDictionary from a list
/// of element maps, where each map contains the entries that specifiy a
/// single class.  The names of the classes in the are expected to be
/// unique.  Attempting to define a duplicate class will result in an
/// DhcpConfigError throw.  Invoking @c commit() method causes the dictionary
/// to be stored by the CfgMgr.
///
/// ClientClassDefParser - creates a ClientClassDefinition from an element
/// map. The elements are as follows:
///
/// -# "name" - a string containing the name of the class
///
/// -# "test" - a string containing the logical expression used to determine
/// membership in the class.  @todo This is passed into the Bison parser.
///
/// -# "option-data" - a list which defines the options that should be
/// assigned to memebers of the class.  This element is optional and parsed
/// using the @ref dhcp::OptionDataListParser.
///
/// ExpressionParser  - creates an eval::Expression from a string element,
/// using the Bison Parser @todo.
///
namespace isc {
namespace dhcp {

/// @brief Parser for a logical expression
///
/// This parser creates an instance of an Expression from a string.  The
/// string is passed to the Bison Parser and the resultant Expression is
/// stored into the ExpressionPtr reference passed into the constructor.
class ExpressionParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param expression variable in which to store the new expression
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    ExpressionParser(const std::string& dummy, ExpressionPtr& expression,
                     ParserContextPtr global_context);

    /// @brief Parses an expression configuration element into an Expression
    ///
    /// @param expression_cfg the configuration entry to be parsed.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void build(isc::data::ConstElementPtr expression_cfg);

    /// @brief Stores the parsed expression to the supplied storage.
    void commit();

private:
    /// @brief Local storage for the parsed expression
    ExpressionPtr local_expression_;

    /// @brief Storage into which the parsed expression should be committed
    ExpressionPtr& expression_;

    /// @brief Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;
};

typedef boost::shared_ptr<ExpressionParser> ExpressionParserPtr;

/// @brief Parser for a single client class definition.
///
/// This parser creates an instance of a client class definition.
class ClientClassDefParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param class_dictionary dictionary into which the class should be added
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    ClientClassDefParser(const std::string& dummy,
                         ClientClassDictionaryPtr& class_dictionary,
                         ParserContextPtr global_context);

    /// @brief Parses an entry that describes single client class definition.
    ///
    /// Attempts to add the new class direclty into the given dictionary.
    /// This done here to detect duplicate classes prior to commit().
    /// @param client_class_def a configuration entry to be parsed.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void build(isc::data::ConstElementPtr client_class_def);

    /// @brief Does nothing.
    void commit() {};

private:

    /// @brief Storage for class string values.
    StringStoragePtr string_values_;

    /// @brief Storage for the class match expression
    ExpressionPtr match_expr_;

    /// @brief Storage for the class options
    CfgOptionPtr options_;

    /// @brief Dictionary to which the new class should be added
    ClientClassDictionaryPtr class_dictionary_;

    /// @brief Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;
};

/// @brief Defines a pointer to a ClientClassDefParser
typedef boost::shared_ptr<ClientClassDefParser> ClientClassDefParserPtr;

/// @brief Parser for a list of client class definitions.
///
/// This parser iterates over all configuration entries that define
/// client classes and creates ClientClassDef instances for each.
/// If the parsing done in build() is successful, the collection of
/// created definitions is given to the @todo CfgMgr.
class ClientClassDefListParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    ClientClassDefListParser(const std::string& dummy,
                        ParserContextPtr global_context);

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries, creates instances
    /// of client class definitions and tries to adds them to the a
    /// local dictionary.
    ///
    /// @param class_def_list pointer to an element that holds entries
    /// for client class definitions.
    /// @throw DhcpConfigError if configuration parsing fails.
    void build(isc::data::ConstElementPtr option_def_list);

    /// @brief Commits class definitions to CfgMgr's global storage.
    void commit();

    /// @brief Local class dictionary to store classes as they are being parsed
    ClientClassDictionaryPtr local_dictionary_;

    /// Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;
};

/// @brief Defines a pointer to a ClientClassDefListParser
typedef boost::shared_ptr<ClientClassDefListParser> ClientClassDefListParserPtr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CLIENT_CLASS_DEF_PARSER_H
