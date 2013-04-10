// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCP_PARSERS_H
#define DHCP_PARSERS_H

#include <cc/data.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <dhcpsrv/option_space_container.h>
#include <dhcpsrv/subnet.h>
#include <exceptions/exceptions.h>

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Storage for option definitions.
typedef OptionSpaceContainer<OptionDefContainer,
                             OptionDefinitionPtr> OptionDefStorage;

/// Collection of containers holding option spaces. Each container within
/// a particular option space holds so-called option descriptors.
typedef OptionSpaceContainer<Subnet::OptionContainer,
                             Subnet::OptionDescriptor> OptionStorage;

/// @brief a dummy configuration parser
///
/// It is a debugging parser. It does not configure anything,
/// will accept any configuration and will just print it out
/// on commit. Useful for debugging existing configurations and
/// adding new ones.
class DebugParser : public DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// See @ref DhcpConfigParser class for details.
    ///
    /// @param param_name name of the parsed parameter
    DebugParser(const std::string& param_name);

    /// @brief builds parameter value
    ///
    /// See @ref DhcpConfigParser class for details.
    ///
    /// @param new_config pointer to the new configuration
    virtual void build(isc::data::ConstElementPtr new_config);

    /// @brief pretends to apply the configuration
    ///
    /// This is a method required by base class. It pretends to apply the
    /// configuration, but in fact it only prints the parameter out.
    ///
    /// See @ref DhcpConfigParser class for details.
    virtual void commit();

private:
    /// name of the parsed parameter
    std::string param_name_;

    /// pointer to the actual value of the parameter
    isc::data::ConstElementPtr value_;

};

/// @brief A boolean value parser.
///
/// This parser handles configuration values of the boolean type.
/// Parsed values are stored in a provided storage. If no storage
/// is provided then the build function throws an exception.
class BooleanParser : public DhcpConfigParser {
public:

    /// @brief Constructor.
    ///
    /// @param param_name name of the parameter.
    BooleanParser(const std::string& param_name, BooleanStorage *storage);

    /// @brief Parse a boolean value.
    ///
    /// @param value a value to be parsed.
    ///
    /// @throw isc::InvalidOperation if a storage has not been set
    ///        prior to calling this function
    /// @throw isc::dhcp::DhcpConfigError if a provided parameter's
    ///        name is empty.
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Put a parsed value to the storage.
    virtual void commit();

private:
    /// Pointer to the storage where parsed value is stored.
    BooleanStorage* storage_;
    /// Name of the parameter which value is parsed with this parser.
    std::string param_name_;
    /// Parsed value.
    bool value_;

    /// Default constructor is private for safety.
    BooleanParser(){};
};

/// @brief Configuration parser for uint32 parameters
///
/// This class is a generic parser that is able to handle any uint32 integer
/// type. By default it stores the value in external global container
/// (uint32_defaults). If used in smaller scopes (e.g. to parse parameters
/// in subnet config), it can be pointed to a different storage, using
/// setStorage() method. This class follows the parser interface, laid out
/// in its base class, @ref DhcpConfigParser.
///
/// For overview of usability of this generic purpose parser, see
/// @ref dhcpv4ConfigInherit page.
class Uint32Parser : public DhcpConfigParser {
public:

    /// @brief constructor for Uint32Parser
    /// @param param_name name of the configuration parameter being parsed
    Uint32Parser(const std::string& param_name, Uint32Storage *storage);

    /// @brief Parses configuration configuration parameter as uint32_t.
    ///
    /// @param value pointer to the content of parsed values
    /// @throw BadValue if supplied value could not be base to uint32_t
    ///        or the parameter name is empty.
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Stores the parsed uint32_t value in a storage.
    virtual void commit();

private:
    /// pointer to the storage, where parsed value will be stored
    Uint32Storage* storage_;

    /// name of the parameter to be parsed
    std::string param_name_;

    /// the actual parsed value
    uint32_t value_;

    /// Default constructor is private for safety.
    Uint32Parser(){};
};

/// @brief Configuration parser for string parameters
///
/// This class is a generic parser that is able to handle any string
/// parameter. By default it stores the value in external global container
/// (string_defaults). If used in smaller scopes (e.g. to parse parameters
/// in subnet config), it can be pointed to a different storage, using
/// setStorage() method. This class follows the parser interface, laid out
/// in its base class, @ref DhcpConfigParser.
///
/// For overview of usability of this generic purpose parser, see
/// @ref dhcpv4ConfigInherit page.
class StringParser : public DhcpConfigParser {
public:
    /// @brief constructor for StringParser
    /// @param param_name name of the configuration parameter being parsed
    StringParser(const std::string& param_name, StringStorage *storage);

    /// @brief parses parameter value
    ///
    /// Parses configuration entry and stores it in storage. See
    /// @ref setStorage() for details.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Stores the parsed value in a storage.
    virtual void commit();

private:
    /// pointer to the storage, where parsed value will be stored
    StringStorage* storage_;

    /// name of the parameter to be parsed
    std::string param_name_;

    /// the actual parsed value
    std::string value_;

    /// Default constructor is private for safety.
    StringParser(){};
};

/// @brief parser for interface list definition
///
/// This parser handles Dhcp4/interface entry.
/// It contains a list of network interfaces that the server listens on.
/// In particular, it can contain an entry called "all" or "any" that
/// designates all interfaces.
///
/// It is useful for parsing Dhcp4/interface parameter.
class InterfaceListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    /// As this is a dedicated parser, it must be used to parse
    /// "interface" parameter only. All other types will throw exception.
    ///
    /// @param param_name name of the configuration parameter being parsed
    /// @throw BadValue if supplied parameter name is not "interface"
    InterfaceListConfigParser(const std::string& param_name);

    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of parameters) and adds each element
    /// to the interfaces list.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief commits interfaces list configuration
    virtual void commit();

private:
    /// contains list of network interfaces
    std::vector<std::string> interfaces_;

    /// Default constructor is private for safety.
    InterfaceListConfigParser(){};
};


/// @brief Parser for option data value.
///
/// This parser parses configuration entries that specify value of
/// a single option. These entries include option name, option code
/// and data carried by the option. The option data can be specified
/// in one of the two available formats: binary value represented as
/// a string of hexadecimal digits or a list of comma separated values.
/// The format being used is controlled by csv-format configuration
/// parameter. When setting this value to True, the latter format is
/// used. The subsequent values in the CSV format apply to relevant
/// option data fields in the configured option. For example the
/// configuration: "data" : "192.168.2.0, 56, hello world" can be
/// used to set values for the option comprising IPv4 address,
/// integer and string data field. Note that order matters. If the
/// order of values does not match the order of data fields within
/// an option the configuration will not be accepted. If parsing
/// is successful then an instance of an option is created and
/// added to the storage provided by the calling class.
class OptionDataParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// Class constructor.
    OptionDataParser(const std::string&, OptionStorage *options, 
        OptionDefStorage *option_defs, Option::Universe universe);

    /// @brief Parses the single option data.
    ///
    /// This method parses the data of a single option from the configuration.
    /// The option data includes option name, option code and data being
    /// carried by this option. Eventually it creates the instance of the
    /// option.
    ///
    /// @warning setStorage must be called with valid storage pointer prior
    /// to calling this method.
    ///
    /// @param option_data_entries collection of entries that define value
    /// for a particular option.
    /// @throw DhcpConfigError if invalid parameter specified in
    /// the configuration.
    /// @throw isc::InvalidOperation if failed to set storage prior to
    /// calling build.
    virtual void build(isc::data::ConstElementPtr option_data_entries);

    /// @brief Commits option value.
    ///
    /// This function adds a new option to the storage or replaces an existing option
    /// with the same code.
    ///
    /// @throw isc::InvalidOperation if failed to set pointer to storage or failed
    /// to call build() prior to commit. If that happens data in the storage
    /// remain un-modified.
    virtual void commit();

    /// @brief virtual destructor to ensure orderly destruction of derivations. 
    virtual ~OptionDataParser(){};

protected:
    /// @brief Finds an option definition within the server's option space
    /// 
    /// Given an option space and an option code, find the correpsonding 
    /// option defintion within the server's option defintion storage. This
    /// method is pure virtual requiring derivations to manage which option
    /// space(s) is valid for search.
    ///
    /// @param option_space name of the parameter option space 
    /// @param option_code numeric value of the parameter to find 
    /// @return OptionDefintionPtr of the option defintion or an 
    /// empty OptionDefinitionPtr if not found.
    /// @throw DhcpConfigError if the option space requested is not valid 
    /// for this server.
    virtual OptionDefinitionPtr findServerSpaceOptionDefinition (
            std::string& option_space, uint32_t option_code) = 0;

private:

    /// @brief Create option instance.
    ///
    /// Creates an instance of an option and adds it to the provided
    /// options storage. If the option data parsed by \ref build function
    /// are invalid or insufficient this function emits an exception.
    ///
    /// @warning this function does not check if options_ storage pointer
    /// is intitialized but this check is not needed here because it is done
    /// in the \ref build function.
    ///
    /// @throw DhcpConfigError if parameters provided in the configuration
    /// are invalid.
    void createOption();

    /// Storage for uint32 values (e.g. option code).
    Uint32Storage uint32_values_;
    /// Storage for string values (e.g. option name or data).
    StringStorage string_values_;
    /// Storage for boolean values.
    BooleanStorage boolean_values_;
    /// Pointer to options storage. This storage is provided by
    /// the calling class and is shared by all OptionDataParser objects.
    OptionStorage* options_;
    /// Option descriptor holds newly configured option.
    Subnet::OptionDescriptor option_descriptor_;
    /// Option space name where the option belongs to.
    std::string option_space_;

    /// Option definition storage
    OptionDefStorage *global_option_defs_;

    /// Option::Universe for this parser's option
    Option::Universe universe_;

    /// Default constructor is private for safety.
    OptionDataParser():option_descriptor_(false){};
};

///@brief Function pointer for OptionDataParser factory methods
typedef OptionDataParser *OptionDataParserFactory(const std::string&, OptionStorage *options, 
        OptionDefStorage *option_defs);

/// @brief Parser for option data values within a subnet.
///
/// This parser iterates over all entries that define options
/// data for a particular subnet and creates a collection of options.
/// If parsing is successful, all these options are added to the Subnet
/// object.
class OptionDataListParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// @param string& nominally would be param name, this is always ignored.
    /// @param storage parsed option storage for options in this list
    /// @param global_option_defs global set of option definitions to reference
    /// @param optionDataParserFactory factory method for creating individual option
    /// parsers 
    OptionDataListParser(const std::string&, OptionStorage *storage, 
        OptionDefStorage *global_option_defs,
        OptionDataParserFactory *optionDataParserFactory);

    /// @brief Parses entries that define options' data for a subnet.
    ///
    /// This method iterates over all entries that define option data
    /// for options within a single subnet and creates options' instances.
    ///
    /// @param option_data_list pointer to a list of options' data sets.
    /// @throw DhcpConfigError if option parsing failed.
    void build(isc::data::ConstElementPtr option_data_list);

    /// @brief Commit all option values.
    ///
    /// This function invokes commit for all option values.
    void commit();

private:
    /// Pointer to options instances storage.
    OptionStorage* options_;
    /// Intermediate option storage. This storage is used by
    /// lower level parsers to add new options.  Values held
    /// in this storage are assigned to main storage (options_)
    /// if overall parsing was successful.
    OptionStorage local_options_;
    /// Collection of parsers;
    ParserCollection parsers_;

    /// Global option definitions
    OptionDefStorage *global_option_defs_;

    /// Factory to create server-specific option data parsers
    OptionDataParserFactory *optionDataParserFactory_;

    /// Default constructor is private for safety.
    OptionDataListParser(){};
};


/// @brief Parser for a single option definition.
///
/// This parser creates an instance of a single option definition.
class OptionDefParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// This constructor sets the pointer to the option definitions
    /// storage to NULL. It must be set to point to the actual storage
    /// before \ref build is called.
    OptionDefParser(const std::string&, OptionDefStorage *storage);

    /// @brief Parses an entry that describes single option definition.
    ///
    /// @param option_def a configuration entry to be parsed.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void build(isc::data::ConstElementPtr option_def);

    /// @brief Stores the parsed option definition in a storage.
    void commit();

private:

    /// @brief Create option definition from the parsed parameters.
    void createOptionDef();

    /// Instance of option definition being created by this parser.
    OptionDefinitionPtr option_definition_;
    /// Name of the space the option definition belongs to.
    std::string option_space_name_;

    /// Pointer to a storage where the option definition will be
    /// added when \ref commit is called.
    OptionDefStorage* storage_;

    /// Storage for boolean values.
    BooleanStorage boolean_values_;
    /// Storage for string values.
    StringStorage string_values_;
    /// Storage for uint32 values.
    Uint32Storage uint32_values_;

    // Default constructor is private for safety.
    OptionDefParser(){};
};

/// @brief Parser for a list of option definitions.
///
/// This parser iterates over all configuration entries that define
/// option definitions and creates instances of these definitions.
/// If the parsing is successful, the collection of created definitions
/// is put into the provided storage.
class OptionDefListParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// This constructor initializes the pointer to option definitions
    /// storage to NULL value. This pointer has to be set to point to
    /// the actual storage before the \ref build function is called.
    OptionDefListParser(const std::string&, OptionDefStorage *storage);

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries and creates instances
    /// of option definitions.
    ///
    /// @param option_def_list pointer to an element that holds entries
    /// that define option definitions.
    /// @throw DhcpConfigError if configuration parsing fails.
    void build(isc::data::ConstElementPtr option_def_list);

    /// @brief Stores option definitions in the CfgMgr.
    void commit();

private:
    /// @brief storage for option definitions.
    OptionDefStorage *storage_; 

    // Default constructor is private for safety.
    OptionDefListParser(){};

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP_PARSERS_H

