// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <config/ccsession.h>
#include <dhcp4/config_parser.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dbaccess_parser.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <dhcpsrv/option_space_container.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <limits>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace {

// Forward declarations of some of the parser classes.
// They are used to define pointer types for these classes.
class BooleanParser;
class StringParser;
class Uint32Parser;

// Pointers to various parser objects.
typedef boost::shared_ptr<BooleanParser> BooleanParserPtr;
typedef boost::shared_ptr<StringParser> StringParserPtr;
typedef boost::shared_ptr<Uint32Parser> Uint32ParserPtr;

/// @brief a factory method that will create a parser for a given element name
typedef isc::dhcp::DhcpConfigParser* ParserFactory(const std::string& config_id);

/// @brief a collection of factories that creates parsers for specified element names
typedef std::map<std::string, ParserFactory*> FactoryMap;

/// @brief Storage for option definitions.
typedef OptionSpaceContainer<OptionDefContainer,
                             OptionDefinitionPtr> OptionDefStorage;

/// @brief a collection of pools
///
/// That type is used as intermediate storage, when pools are parsed, but there is
/// no subnet object created yet to store them.
typedef std::vector<Pool4Ptr> PoolStorage;

/// Collection of containers holding option spaces. Each container within
/// a particular option space holds so-called option descriptors.
typedef OptionSpaceContainer<Subnet::OptionContainer,
                             Subnet::OptionDescriptor> OptionStorage;

/// @brief Global uint32 parameters that will be used as defaults.
Uint32Storage uint32_defaults;

/// @brief global string parameters that will be used as defaults.
StringStorage string_defaults;

/// @brief Global storage for options that will be used as defaults.
OptionStorage option_defaults;

/// @brief Global storage for option definitions.
OptionDefStorage option_def_intermediate;

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
    DebugParser(const std::string& param_name)
        :param_name_(param_name) {
    }

    /// @brief builds parameter value
    ///
    /// See @ref DhcpConfigParser class for details.
    ///
    /// @param new_config pointer to the new configuration
    virtual void build(ConstElementPtr new_config) {
        std::cout << "Build for token: [" << param_name_ << "] = ["
                  << value_->str() << "]" << std::endl;
        value_ = new_config;
    }

    /// @brief pretends to apply the configuration
    ///
    /// This is a method required by base class. It pretends to apply the
    /// configuration, but in fact it only prints the parameter out.
    ///
    /// See @ref DhcpConfigParser class for details.
    virtual void commit() {
        // Debug message. The whole DebugParser class is used only for parser
        // debugging, and is not used in production code. It is very convenient
        // to keep it around. Please do not turn this cout into logger calls.
        std::cout << "Commit for token: [" << param_name_ << "] = ["
                  << value_->str() << "]" << std::endl;
    }

    /// @brief factory that constructs DebugParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* Factory(const std::string& param_name) {
        return (new DebugParser(param_name));
    }

private:
    /// name of the parsed parameter
    std::string param_name_;

    /// pointer to the actual value of the parameter
    ConstElementPtr value_;
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
    BooleanParser(const std::string& param_name)
        : storage_(NULL),
          param_name_(param_name),
          value_(false) {
        // Empty parameter name is invalid.
        if (param_name_.empty()) {
            isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
    }

    /// @brief Parse a boolean value.
    ///
    /// @param value a value to be parsed.
    ///
    /// @throw isc::InvalidOperation if a storage has not been set
    ///        prior to calling this function
    /// @throw isc::dhcp::DhcpConfigError if a provided parameter's
    ///        name is empty.
    virtual void build(ConstElementPtr value) {
        if (storage_ == NULL) {
            isc_throw(isc::InvalidOperation, "parser logic error:"
                      << " storage for the " << param_name_
                      << " value has not been set");
        } else if (param_name_.empty()) {
            isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
        // The Config Manager checks if user specified a
        // valid value for a boolean parameter: True or False.
        // It is then ok to assume that if str() does not return
        // 'true' the value is 'false'.
        value_ = (value->str() == "true") ? true : false;
    }

    /// @brief Put a parsed value to the storage.
    virtual void commit() {
        if (storage_ != NULL && !param_name_.empty()) {
            storage_->setParam(param_name_, value_);
        }
    }

    /// @brief Create an instance of the boolean parser.
    ///
    /// @param param_name name of the parameter for which the
    ///        parser is created.
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new BooleanParser(param_name));
    }

    /// @brief Set the storage for parsed value.
    ///
    /// This function must be called prior to calling build.
    ///
    /// @param storage a pointer to the storage where parsed data
    ///        is to be stored.
    void setStorage(BooleanStorage* storage) {
        storage_ = storage;
    }

private:
    /// Pointer to the storage where parsed value is stored.
    BooleanStorage* storage_;
    /// Name of the parameter which value is parsed with this parser.
    std::string param_name_;
    /// Parsed value.
    bool value_;
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
    Uint32Parser(const std::string& param_name)
        : storage_(&uint32_defaults),
          param_name_(param_name) {
        // Empty parameter name is invalid.
        if (param_name_.empty()) {
            isc_throw(DhcpConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
    }

    /// @brief Parses configuration configuration parameter as uint32_t.
    ///
    /// @param value pointer to the content of parsed values
    /// @throw BadValue if supplied value could not be base to uint32_t
    ///        or the parameter name is empty.
    virtual void build(ConstElementPtr value) {
        if (param_name_.empty()) {
            isc_throw(DhcpConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }

        int64_t check;
        string x = value->str();
        try {
            check = boost::lexical_cast<int64_t>(x);
        } catch (const boost::bad_lexical_cast &) {
            isc_throw(BadValue, "Failed to parse value " << value->str()
                      << " as unsigned 32-bit integer.");
        }
        if (check > std::numeric_limits<uint32_t>::max()) {
            isc_throw(BadValue, "Value " << value->str() << "is too large"
                      << " for unsigned 32-bit integer.");
        }
        if (check < 0) {
            isc_throw(BadValue, "Value " << value->str() << "is negative."
                      << " Only 0 or larger are allowed for unsigned 32-bit integer.");
        }

        // value is small enough to fit
        value_ = static_cast<uint32_t>(check);
    }

    /// @brief Stores the parsed uint32_t value in a storage.
    virtual void commit() {
        if (storage_ != NULL && !param_name_.empty()) {
            // If a given parameter already exists in the storage we override
            // its value. If it doesn't we insert a new element.
            storage_->setParam(param_name_, value_);
        }
    }

    /// @brief factory that constructs Uint32Parser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new Uint32Parser(param_name));
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See @ref dhcpv4ConfigInherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(Uint32Storage* storage) {
        storage_ = storage;
    }

private:
    /// pointer to the storage, where parsed value will be stored
    Uint32Storage* storage_;

    /// name of the parameter to be parsed
    std::string param_name_;

    /// the actual parsed value
    uint32_t value_;
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
    StringParser(const std::string& param_name)
        :storage_(&string_defaults), param_name_(param_name) {
        // Empty parameter name is invalid.
        if (param_name_.empty()) {
            isc_throw(DhcpConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
    }

    /// @brief parses parameter value
    ///
    /// Parses configuration entry and stores it in storage. See
    /// @ref setStorage() for details.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(ConstElementPtr value) {
        value_ = value->str();
        boost::erase_all(value_, "\"");
    }

    /// @brief Stores the parsed value in a storage.
    virtual void commit() {
        if (storage_ != NULL && !param_name_.empty()) {
            // If a given parameter already exists in the storage we override
            // its value. If it doesn't we insert a new element.
            storage_->setParam(param_name_, value_);
        }
    }

    /// @brief factory that constructs StringParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new StringParser(param_name));
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See \ref dhcpv4ConfigInherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(StringStorage* storage) {
        storage_ = storage;
    }

private:
    /// pointer to the storage, where parsed value will be stored
    StringStorage* storage_;

    /// name of the parameter to be parsed
    std::string param_name_;

    /// the actual parsed value
    std::string value_;
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
    InterfaceListConfigParser(const std::string& param_name) {
        if (param_name != "interface") {
            isc_throw(BadValue, "Internal error. Interface configuration "
                      "parser called for the wrong parameter: " << param_name);
        }
    }

    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of parameters) and adds each element
    /// to the interfaces list.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(ConstElementPtr value) {
        BOOST_FOREACH(ConstElementPtr iface, value->listValue()) {
            interfaces_.push_back(iface->str());
        }
    }

    /// @brief commits interfaces list configuration
    virtual void commit() {
        /// @todo: Implement per interface listening. Currently always listening
        /// on all interfaces.
    }

    /// @brief factory that constructs InterfaceListConfigParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new InterfaceListConfigParser(param_name));
    }

private:
    /// contains list of network interfaces
    vector<string> interfaces_;
};

/// @brief parser for pool definition
///
/// This parser handles pool definitions, i.e. a list of entries of one
/// of two syntaxes: min-max and prefix/len. Pool4 objects are created
/// and stored in chosen PoolStorage container.
///
/// As there are no default values for pool, setStorage() must be called
/// before build(). Otherwise exception will be thrown.
///
/// It is useful for parsing Dhcp4/subnet4[X]/pool parameters.
class PoolParser : public DhcpConfigParser {
public:

    /// @brief constructor.
    PoolParser(const std::string& /*param_name*/)
        :pools_(NULL) {
        // ignore parameter name, it is always Dhcp4/subnet4[X]/pool
    }

    /// @brief parses the actual list
    ///
    /// This method parses the actual list of interfaces.
    /// No validation is done at this stage, everything is interpreted as
    /// interface name.
    /// @param pools_list list of pools defined for a subnet
    /// @throw InvalidOperation if storage was not specified (setStorage() not called)
    /// @throw DhcpConfigError when pool parsing fails
    void build(ConstElementPtr pools_list) {
        // setStorage() should have been called before build
        if (!pools_) {
            isc_throw(InvalidOperation, "Parser logic error. No pool storage set,"
                      " but pool parser asked to parse pools");
        }

        BOOST_FOREACH(ConstElementPtr text_pool, pools_list->listValue()) {

            // That should be a single pool representation. It should contain
            // text is form prefix/len or first - last. Note that spaces
            // are allowed
            string txt = text_pool->stringValue();

            // first let's remove any whitespaces
            boost::erase_all(txt, " "); // space
            boost::erase_all(txt, "\t"); // tabulation

            // Is this prefix/len notation?
            size_t pos = txt.find("/");
            if (pos != string::npos) {
                IOAddress addr("::");
                uint8_t len = 0;
                try {
                    addr = IOAddress(txt.substr(0, pos));

                    // start with the first character after /
                    string prefix_len = txt.substr(pos + 1);

                    // It is lexical cast to int and then downcast to uint8_t.
                    // Direct cast to uint8_t (which is really an unsigned char)
                    // will result in interpreting the first digit as output
                    // value and throwing exception if length is written on two
                    // digits (because there are extra characters left over).

                    // No checks for values over 128. Range correctness will
                    // be checked in Pool4 constructor.
                    len = boost::lexical_cast<int>(prefix_len);
                } catch (...)  {
                    isc_throw(DhcpConfigError, "Failed to parse pool "
                              "definition: " << text_pool->stringValue());
                }

                Pool4Ptr pool(new Pool4(addr, len));
                local_pools_.push_back(pool);
                continue;
            }

            // Is this min-max notation?
            pos = txt.find("-");
            if (pos != string::npos) {
                // using min-max notation
                IOAddress min(txt.substr(0,pos));
                IOAddress max(txt.substr(pos + 1));

                Pool4Ptr pool(new Pool4(min, max));

                local_pools_.push_back(pool);
                continue;
            }

            isc_throw(DhcpConfigError, "Failed to parse pool definition:"
                      << text_pool->stringValue() <<
                      ". Does not contain - (for min-max) nor / (prefix/len)");
        }
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See \ref dhcpv4ConfigInherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(PoolStorage* storage) {
        pools_ = storage;
    }

    /// @brief Stores the parsed values in a storage provided
    ///        by an upper level parser.
    virtual void commit() {
        if (pools_) {
            // local_pools_ holds the values produced by the build function.
            // At this point parsing should have completed successfuly so
            // we can append new data to the supplied storage.
            pools_->insert(pools_->end(), local_pools_.begin(),
                           local_pools_.end());
        }
    }

    /// @brief factory that constructs PoolParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new PoolParser(param_name));
    }

private:
    /// @brief pointer to the actual Pools storage
    ///
    /// That is typically a storage somewhere in Subnet parser
    /// (an upper level parser).
    PoolStorage* pools_;
    /// A temporary storage for pools configuration. It is a
    /// storage where pools are stored by build function.
    PoolStorage local_pools_;
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
    OptionDataParser(const std::string&)
        : options_(NULL),
          // initialize option to NULL ptr
          option_descriptor_(false) { }

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
    virtual void build(ConstElementPtr option_data_entries) {
        if (options_ == NULL) {
            isc_throw(isc::InvalidOperation, "Parser logic error: storage must be set before "
                      "parsing option data.");
        }
        BOOST_FOREACH(ConfigPair param, option_data_entries->mapValue()) {
            ParserPtr parser;
            if (param.first == "name" || param.first == "data" ||
                param.first == "space") {
                boost::shared_ptr<StringParser>
                    name_parser(dynamic_cast<StringParser*>(StringParser::factory(param.first)));
                if (name_parser) {
                    name_parser->setStorage(&string_values_);
                    parser = name_parser;
                }
            } else if (param.first == "code") {
                boost::shared_ptr<Uint32Parser>
                    code_parser(dynamic_cast<Uint32Parser*>(Uint32Parser::factory(param.first)));
                if (code_parser) {
                    code_parser->setStorage(&uint32_values_);
                    parser = code_parser;
                }
            } else if (param.first == "csv-format") {
                boost::shared_ptr<BooleanParser>
                    value_parser(dynamic_cast<BooleanParser*>(BooleanParser::factory(param.first)));
                if (value_parser) {
                    value_parser->setStorage(&boolean_values_);
                    parser = value_parser;
                }
            } else {
                isc_throw(DhcpConfigError,
                          "Parser error: option-data parameter not supported: "
                          << param.first);
            }
            parser->build(param.second);
            // Before we can create an option we need to get the data from
            // the child parsers. The only way to do it is to invoke commit
            // on them so as they store the values in appropriate storages
            // that this class provided to them. Note that this will not
            // modify values stored in the global storages so the configuration
            // will remain consistent even parsing fails somewhere further on.
            parser->commit();
        }
        // Try to create the option instance.
        createOption();
    }

    /// @brief Commits option value.
    ///
    /// This function adds a new option to the storage or replaces an existing option
    /// with the same code.
    ///
    /// @throw isc::InvalidOperation if failed to set pointer to storage or failed
    /// to call build() prior to commit. If that happens data in the storage
    /// remain un-modified.
    virtual void commit() {
        if (options_ == NULL) {
            isc_throw(isc::InvalidOperation, "parser logic error: storage must be set before "
                      "committing option data.");
        } else  if (!option_descriptor_.option) {
            // Before we can commit the new option should be configured. If it is not
            // than somebody must have called commit() before build().
            isc_throw(isc::InvalidOperation, "parser logic error: no option has been configured and"
                      " thus there is nothing to commit. Has build() been called?");
        }
        uint16_t opt_type = option_descriptor_.option->getType();
        Subnet::OptionContainerPtr options = options_->getItems(option_space_);
        // The getItems() should never return NULL pointer. If there are no
        // options configured for the particular option space a pointer
        // to an empty container should be returned.
        assert(options);
        Subnet::OptionContainerTypeIndex& idx = options->get<1>();
        // Try to find options with the particular option code in the main
        // storage. If found, remove these options because they will be
        // replaced with new one.
        Subnet::OptionContainerTypeRange range =
            idx.equal_range(opt_type);
        if (std::distance(range.first, range.second) > 0) {
            idx.erase(range.first, range.second);
        }
        // Append new option to the main storage.
        options_->addItem(option_descriptor_, option_space_);
    }

    /// @brief Set storage for the parser.
    ///
    /// Sets storage for the parser. This storage points to the
    /// vector of options and is used by multiple instances of
    /// OptionDataParser. Each instance creates exactly one object
    /// of dhcp::Option or derived type and appends it to this
    /// storage.
    ///
    /// @param storage pointer to the options storage
    void setStorage(OptionStorage* storage) {
        options_ = storage;
    }

private:

    /// @brief Create option instance.
    ///
    /// Creates an instance of an option and adds it to the provided
    /// options storage. If the option data parsed by \ref build function
    /// are invalid or insufficient this function emits an exception.
    ///
    /// @warning this function does not check if options_ storage pointer
    /// is initialized but this check is not needed here because it is done
    /// in the \ref build function.
    ///
    /// @throw DhcpConfigError if parameters provided in the configuration
    /// are invalid.
    void createOption() {
        // Option code is held in the uint32_t storage but is supposed to
        // be uint16_t value. We need to check that value in the configuration
        // does not exceed range of uint8_t and is not zero.
        uint32_t option_code = uint32_values_.getParam("code");
        if (option_code == 0) {
            isc_throw(DhcpConfigError, "option code must not be zero."
                      << " Option code '0' is reserved in DHCPv4.");
        } else if (option_code > std::numeric_limits<uint8_t>::max()) {
            isc_throw(DhcpConfigError, "invalid option code '" << option_code
                      << "', it must not exceed '"
                      << std::numeric_limits<uint8_t>::max() << "'");
        }

        // Check that the option name has been specified, is non-empty and does not
        // contain spaces
        std::string option_name = string_values_.getParam("name"); 
        if (option_name.empty()) {
            isc_throw(DhcpConfigError, "name of the option with code '"
                      << option_code << "' is empty");
        } else if (option_name.find(" ") != std::string::npos) {
            isc_throw(DhcpConfigError, "invalid option name '" << option_name
                      << "', space character is not allowed");
        }

        std::string option_space = string_values_.getParam("space"); 
        if (!OptionSpace::validateName(option_space)) {
            isc_throw(DhcpConfigError, "invalid option space name '"
                      << option_space << "' specified for option '"
                      << option_name << "' (code '" << option_code
                      << "')");
        }

        OptionDefinitionPtr def;
        if (option_space == "dhcp4" &&
            LibDHCP::isStandardOption(Option::V4, option_code)) {
            def = LibDHCP::getOptionDef(Option::V4, option_code);

        } else if (option_space == "dhcp6") {
            isc_throw(DhcpConfigError, "'dhcp6' option space name is reserved"
                      << " for DHCPv6 server");
        } else {
            // If we are not dealing with a standard option then we
            // need to search for its definition among user-configured
            // options. They are expected to be in the global storage
            // already.
            OptionDefContainerPtr defs = option_def_intermediate.getItems(option_space);
            // The getItems() should never return the NULL pointer. If there are
            // no option definitions for the particular option space a pointer
            // to an empty container should be returned.
            assert(defs);
            const OptionDefContainerTypeIndex& idx = defs->get<1>();
            OptionDefContainerTypeRange range = idx.equal_range(option_code);
            if (std::distance(range.first, range.second) > 0) {
                def = *range.first;
            }
            if (!def) {
                isc_throw(DhcpConfigError, "definition for the option '"
                          << option_space << "." << option_name
                          << "' having code '" <<  option_code
                          << "' does not exist");
            }

        }

        // Get option data from the configuration database ('data' field).
        const std::string option_data = string_values_.getParam("data");
        const bool csv_format = boolean_values_.getParam("csv-format");

        // Transform string of hexadecimal digits into binary format.
        std::vector<uint8_t> binary;
        std::vector<std::string> data_tokens;

        if (csv_format) {
            // If the option data is specified as a string of comma
            // separated values then we need to split this string into
            // individual values - each value will be used to initialize
            // one data field of an option.
            data_tokens = isc::util::str::tokens(option_data, ",");
        } else {
            // Otherwise, the option data is specified as a string of
            // hexadecimal digits that we have to turn into binary format.
            try {
                util::encode::decodeHex(option_data, binary);
            } catch (...) {
                isc_throw(DhcpConfigError, "option data is not a valid"
                          << " string of hexadecimal digits: " << option_data);
            }
        }

        OptionPtr option;
        if (!def) {
            if (csv_format) {
                isc_throw(DhcpConfigError, "the CSV option data format can be"
                          " used to specify values for an option that has a"
                          " definition. The option with code " << option_code
                          << " does not have a definition.");
            }

            // @todo We have a limited set of option definitions initialized at the moment.
            // In the future we want to initialize option definitions for all options.
            // Consequently an error will be issued if an option definition does not exist
            // for a particular option code. For now it is ok to create generic option
            // if definition does not exist.
            OptionPtr option(new Option(Option::V4, static_cast<uint16_t>(option_code),
                                        binary));
            // The created option is stored in option_descriptor_ class member until the
            // commit stage when it is inserted into the main storage. If an option with the
            // same code exists in main storage already the old option is replaced.
            option_descriptor_.option = option;
            option_descriptor_.persistent = false;
        } else {

            // Option name should match the definition. The option name
            // may seem to be redundant but in the future we may want
            // to reference options and definitions using their names
            // and/or option codes so keeping the option name in the
            // definition of option value makes sense.
            if (def->getName() != option_name) {
                isc_throw(DhcpConfigError, "specified option name '"
                          << option_name << "' does not match the "
                          << "option definition: '" << option_space
                          << "." << def->getName() << "'");
            }

            // Option definition has been found so let's use it to create
            // an instance of our option.
            try {
                OptionPtr option = csv_format ?
                    def->optionFactory(Option::V4, option_code, data_tokens) :
                    def->optionFactory(Option::V4, option_code, binary);
                Subnet::OptionDescriptor desc(option, false);
                option_descriptor_.option = option;
                option_descriptor_.persistent = false;
            } catch (const isc::Exception& ex) {
                isc_throw(DhcpConfigError, "option data does not match"
                          << " option definition (space: " << option_space
                          << ", code: " << option_code << "): "
                          << ex.what());
            }

        }
        // All went good, so we can set the option space name.
        option_space_ = option_space;
    }

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
};

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
    /// Unless otherwise specified, parsed options will be stored in
    /// a global option container (option_default). That storage location
    /// is overriden on a subnet basis.
    OptionDataListParser(const std::string&)
        : options_(&option_defaults), local_options_() { }

    /// @brief Parses entries that define options' data for a subnet.
    ///
    /// This method iterates over all entries that define option data
    /// for options within a single subnet and creates options' instances.
    ///
    /// @param option_data_list pointer to a list of options' data sets.
    /// @throw DhcpConfigError if option parsing failed.
    void build(ConstElementPtr option_data_list) {
        BOOST_FOREACH(ConstElementPtr option_value, option_data_list->listValue()) {
            boost::shared_ptr<OptionDataParser> parser(new OptionDataParser("option-data"));
            // options_ member will hold instances of all options thus
            // each OptionDataParser takes it as a storage.
            parser->setStorage(&local_options_);
            // Build the instance of a single option.
            parser->build(option_value);
            // Store a parser as it will be used to commit.
            parsers_.push_back(parser);
        }
    }

    /// @brief Set storage for option instances.
    ///
    /// @param storage pointer to options storage.
    void setStorage(OptionStorage* storage) {
        options_ = storage;
    }


    /// @brief Commit all option values.
    ///
    /// This function invokes commit for all option values.
    void commit() {
        BOOST_FOREACH(ParserPtr parser, parsers_) {
            parser->commit();
        }
        // Parsing was successful and we have all configured
        // options in local storage. We can now replace old values
        // with new values.
        std::swap(local_options_, *options_);
    }

    /// @brief Create DhcpDataListParser object
    ///
    /// @param param_name param name.
    ///
    /// @return DhcpConfigParser object.
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new OptionDataListParser(param_name));
    }

    /// Pointer to options instances storage.
    OptionStorage* options_;
    /// Intermediate option storage. This storage is used by
    /// lower level parsers to add new options.  Values held
    /// in this storage are assigned to main storage (options_)
    /// if overall parsing was successful.
    OptionStorage local_options_;
    /// Collection of parsers;
    ParserCollection parsers_;
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
    OptionDefParser(const std::string&)
        : storage_(NULL) {
    }

    /// @brief Parses an entry that describes single option definition.
    ///
    /// @param option_def a configuration entry to be parsed.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    void build(ConstElementPtr option_def) {
        if (storage_ == NULL) {
            isc_throw(DhcpConfigError, "parser logic error: storage must be set"
                      " before parsing option definition data");
        }
        // Parse the elements that make up the option definition.
        BOOST_FOREACH(ConfigPair param, option_def->mapValue()) {
            std::string entry(param.first);
            ParserPtr parser;
            if (entry == "name" || entry == "type" ||
                entry == "record-types" || entry == "space" ||
                entry == "encapsulate") {
                StringParserPtr
                    str_parser(dynamic_cast<StringParser*>(StringParser::factory(entry)));
                if (str_parser) {
                    str_parser->setStorage(&string_values_);
                    parser = str_parser;
                }
            } else if (entry == "code") {
                Uint32ParserPtr
                    code_parser(dynamic_cast<Uint32Parser*>(Uint32Parser::factory(entry)));
                if (code_parser) {
                    code_parser->setStorage(&uint32_values_);
                    parser = code_parser;
                }
            } else if (entry == "array") {
                BooleanParserPtr
                    array_parser(dynamic_cast<BooleanParser*>(BooleanParser::factory(entry)));
                if (array_parser) {
                    array_parser->setStorage(&boolean_values_);
                    parser = array_parser;
                }
            } else {
                isc_throw(DhcpConfigError, "invalid parameter: " << entry);
            }

            parser->build(param.second);
            parser->commit();
        }

        // Create an instance of option definition.
        createOptionDef();

        // Get all items we collected so far for the particular option space.
        OptionDefContainerPtr defs = storage_->getItems(option_space_name_);
        // Check if there are any items with option code the same as the
        // one specified for the definition we are now creating.
        const OptionDefContainerTypeIndex& idx = defs->get<1>();
        const OptionDefContainerTypeRange& range =
            idx.equal_range(option_definition_->getCode());
        // If there are any items with this option code already we need
        // to issue an error because we don't allow duplicates for
        // option definitions within an option space.
        if (std::distance(range.first, range.second) > 0) {
            isc_throw(DhcpConfigError, "duplicated option definition for"
                      << " code '" << option_definition_->getCode() << "'");
        }
    }

    /// @brief Stores the parsed option definition in a storage.
    void commit() {
        if (storage_ && option_definition_ &&
            OptionSpace::validateName(option_space_name_)) {
            storage_->addItem(option_definition_, option_space_name_);
        }
    }

    /// @brief Sets a pointer to the data store.
    ///
    /// The newly created instance of an option definition will be
    /// added to the data store given by the argument.
    ///
    /// @param storage pointer to the data store where the option definition
    /// will be added to.
    void setStorage(OptionDefStorage* storage) {
        storage_ = storage;
    }

private:

    /// @brief Create option definition from the parsed parameters.
    void createOptionDef() {

        // Get the option space name and validate it.
        std::string space = string_values_.getParam("space");
        if (!OptionSpace::validateName(space)) {
            isc_throw(DhcpConfigError, "invalid option space name '"
                      << space << "'");
        }

        // Get other parameters that are needed to create the
        // option definition.
        std::string name = string_values_.getParam("name");
        uint32_t code = uint32_values_.getParam("code");
        std::string type = string_values_.getParam("type");
        bool array_type = boolean_values_.getParam("array");
        std::string encapsulates = string_values_.getParam("encapsulate");

        // Create option definition.
        OptionDefinitionPtr def;
        // We need to check if user has set encapsulated option space
        // name. If so, different constructor will be used.
        if (!encapsulates.empty()) {
            // Arrays can't be used together with sub-options.
            if (array_type) {
                isc_throw(DhcpConfigError, "option '" << space << "."
                          << "name" << "', comprising an array of data"
                          << " fields may not encapsulate any option space");

            } else if (encapsulates == space) {
                isc_throw(DhcpConfigError, "option must not encapsulate"
                          << " an option space it belongs to: '"
                          << space << "." << name << "' is set to"
                          << " encapsulate '" << space << "'");

            } else {
                def.reset(new OptionDefinition(name, code, type,
                                               encapsulates.c_str()));
            }

        } else {
            def.reset(new OptionDefinition(name, code, type, array_type));

        }
        // The record-types field may carry a list of comma separated names
        // of data types that form a record.
        std::string record_types = string_values_.getParam("record-types");

        // Split the list of record types into tokens.
        std::vector<std::string> record_tokens =
            isc::util::str::tokens(record_types, ",");
        // Iterate over each token and add a record type into
        // option definition.
        BOOST_FOREACH(std::string record_type, record_tokens) {
            try {
                boost::trim(record_type);
                if (!record_type.empty()) {
                    def->addRecordField(record_type);
                }
            } catch (const Exception& ex) {
                isc_throw(DhcpConfigError, "invalid record type values"
                          << " specified for the option definition: "
                          << ex.what());
            }
        }

        // Check the option definition parameters are valid.
        try {
            def->validate();
        } catch (const isc::Exception& ex) {
            isc_throw(DhcpConfigError, "invalid option definition"
                      << " parameters: " << ex.what());
        }
        // Option definition has been created successfully.
        option_space_name_ = space;
        option_definition_ = def;
    }

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
};

/// @brief Parser for a list of option definitions.
///
/// This parser iterates over all configuration entries that define
/// option definitions and creates instances of these definitions.
/// If the parsing is successful, the collection of created definitions
/// is put into the provided storage.
class OptionDefListParser : DhcpConfigParser {
public:

    /// @brief Constructor.
    ///
    /// This constructor initializes the pointer to option definitions
    /// storage to NULL value. This pointer has to be set to point to
    /// the actual storage before the \ref build function is called.
    OptionDefListParser(const std::string&) {
    }

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries and creates instances
    /// of option definitions.
    ///
    /// @param option_def_list pointer to an element that holds entries
    /// that define option definitions.
    /// @throw DhcpConfigError if configuration parsing fails.
    void build(ConstElementPtr option_def_list) {
        // Clear existing items in the global storage.
        // We are going to replace all of them.
        option_def_intermediate.clearItems();

        if (!option_def_list) {
            isc_throw(DhcpConfigError, "parser error: a pointer to a list of"
                      << " option definitions is NULL");
        }

        BOOST_FOREACH(ConstElementPtr option_def, option_def_list->listValue()) {
            boost::shared_ptr<OptionDefParser>
                parser(new OptionDefParser("single-option-def"));
            parser->setStorage(&option_def_intermediate);
            parser->build(option_def);
            parser->commit();
        }
    }

    /// @brief Stores option definitions in the CfgMgr.
    void commit() {

        CfgMgr& cfg_mgr = CfgMgr::instance();

        cfg_mgr.deleteOptionDefs();

        // We need to move option definitions from the temporary
        // storage to the global storage.
        std::list<std::string> space_names =
            option_def_intermediate.getOptionSpaceNames();
        BOOST_FOREACH(std::string space_name, space_names) {

            BOOST_FOREACH(OptionDefinitionPtr def,
                          *option_def_intermediate.getItems(space_name)) {
                // All option definitions should be initialized to non-NULL
                // values. The validation is expected to be made by the
                // OptionDefParser when creating an option definition.
                assert(def);
                cfg_mgr.addOptionDef(def, space_name);
            }
        }
    }

    /// @brief Create an OptionDefListParser object.
    ///
    /// @param param_name configuration entry holding option definitions.
    ///
    /// @return OptionDefListParser object.
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new OptionDefListParser(param_name));
    }

};

/// @brief this class parses a single subnet
///
/// This class parses the whole subnet definition. It creates parsers
/// for received configuration parameters as needed.
class Subnet4ConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    Subnet4ConfigParser(const std::string& ) {
        // The parameter should always be "subnet", but we don't check here
        // against it in case someone wants to reuse this parser somewhere.
    }

    /// @brief parses parameter value
    ///
    /// @param subnet pointer to the content of subnet definition
    void build(ConstElementPtr subnet) {

        BOOST_FOREACH(ConfigPair param, subnet->mapValue()) {
            ParserPtr parser(createSubnet4ConfigParser(param.first));
            // The actual type of the parser is unknown here. We have to discover
            // the parser type here to invoke the corresponding setStorage function
            // on it.  We discover parser type by trying to cast the parser to various
            // parser types and checking which one was successful. For this one
            // a setStorage and build methods are invoked.

            // Try uint32 type parser.
            if (!buildParser<Uint32Parser, Uint32Storage >(parser, uint32_values_,
                                                          param.second) &&
                // Try string type parser.
                !buildParser<StringParser, StringStorage >(parser, string_values_,
                                                           param.second) &&
                // Try pool parser.
                !buildParser<PoolParser, PoolStorage >(parser, pools_,
                                                       param.second) &&
                // Try option data parser.
                !buildParser<OptionDataListParser, OptionStorage >(parser, options_,
                                                                   param.second)) {
                // Appropriate parsers are created in the createSubnet6ConfigParser
                // and they should be limited to those that we check here for. Thus,
                // if we fail to find a matching parser here it is a programming error.
                isc_throw(DhcpConfigError, "failed to find suitable parser");
            }
        }
        // In order to create new subnet we need to get the data out
        // of the child parsers first. The only way to do it is to
        // invoke commit on them because it will make them write
        // parsed data into storages we have supplied.
        // Note that triggering commits on child parsers does not
        // affect global data because we supplied pointers to storages
        // local to this object. Thus, even if this method fails
        // later on, the configuration remains consistent.
        BOOST_FOREACH(ParserPtr parser, parsers_) {
            parser->commit();
        }

        // Create a subnet.
        createSubnet();
    }

    /// @brief commits received configuration.
    ///
    /// This method does most of the configuration. Many other parsers are just
    /// storing the values that are actually consumed here. Pool definitions
    /// created in other parsers are used here and added to newly created Subnet4
    /// objects. Subnet4 are then added to DHCP CfgMgr.
    /// @throw DhcpConfigError if there are any issues encountered during commit
    void commit() {
        if (subnet_) {
            CfgMgr::instance().addSubnet4(subnet_);
        }
    }

private:

    /// @brief Set storage for a parser and invoke build.
    ///
    /// This helper method casts the provided parser pointer to the specified
    /// type. If the cast is successful it sets the corresponding storage for
    /// this parser, invokes build on it and saves the parser.
    ///
    /// @tparam T parser type to which parser argument should be cast.
    /// @tparam Y storage type for the specified parser type.
    /// @param parser parser on which build must be invoked.
    /// @param storage reference to a storage that will be set for a parser.
    /// @param subnet subnet element read from the configuration and being parsed.
    /// @return true if parser pointer was successfully cast to specialized
    /// parser type provided as Y.
    template<typename T, typename Y>
    bool buildParser(const ParserPtr& parser, Y& storage, const ConstElementPtr& subnet) {
        // We need to cast to T in order to set storage for the parser.
        boost::shared_ptr<T> cast_parser = boost::dynamic_pointer_cast<T>(parser);
        // It is common that this cast is not successful because we try to cast to all
        // supported parser types as we don't know the type of a parser in advance.
        if (cast_parser) {
            // Cast, successful so we go ahead with setting storage and actual parse.
            cast_parser->setStorage(&storage);
            parser->build(subnet);
            parsers_.push_back(parser);
            // We indicate that cast was successful so as the calling function
            // may skip attempts to cast to other parser types and proceed to
            // next element.
            return (true);
        }
        // It was not successful. Indicate that another parser type
        // should be tried.
        return (false);
    }

    /// @brief Append sub-options to an option.
    ///
    /// @param option_space a name of the encapsulated option space.
    /// @param option option instance to append sub-options to.
    void appendSubOptions(const std::string& option_space, OptionPtr& option) {
        // Only non-NULL options are stored in option container.
        // If this option pointer is NULL this is a serious error.
        assert(option);

        OptionDefinitionPtr def;
        if (option_space == "dhcp4" &&
            LibDHCP::isStandardOption(Option::V4, option->getType())) {
            def = LibDHCP::getOptionDef(Option::V4, option->getType());
            // Definitions for some of the standard options hasn't been
            // implemented so it is ok to leave here.
            if (!def) {
                return;
            }
        } else {
            const OptionDefContainerPtr defs =
                option_def_intermediate.getItems(option_space);
            const OptionDefContainerTypeIndex& idx = defs->get<1>();
            const OptionDefContainerTypeRange& range =
                idx.equal_range(option->getType());
            // There is no definition so we have to leave.
            if (std::distance(range.first, range.second) == 0) {
                return;
            }

            def = *range.first;

            // If the definition exists, it must be non-NULL.
            // Otherwise it is a programming error.
            assert(def);
        }

        // We need to get option definition for the particular option space
        // and code. This definition holds the information whether our
        // option encapsulates any option space.
        // Get the encapsulated option space name.
        std::string encapsulated_space = def->getEncapsulatedSpace();
        // If option space name is empty it means that our option does not
        // encapsulate any option space (does not include sub-options).
        if (!encapsulated_space.empty()) {
            // Get the sub-options that belong to the encapsulated
            // option space.
            const Subnet::OptionContainerPtr sub_opts =
                option_defaults.getItems(encapsulated_space);
            // Append sub-options to the option.
            BOOST_FOREACH(Subnet::OptionDescriptor desc, *sub_opts) {
                if (desc.option) {
                    option->addOption(desc.option);
                }
            }
        }
    }

    /// @brief Create a new subnet using a data from child parsers.
    ///
    /// @throw isc::dhcp::DhcpConfigError if subnet configuration parsing failed.
    void createSubnet() {
        std::string subnet_txt;
        try {
            subnet_txt = string_values_.getParam("subnet"); 
        } catch (DhcpConfigError) {
            // Rethrow with precise error.
            isc_throw(DhcpConfigError,
                      "Mandatory subnet definition in subnet missing");
        }

        // Remove any spaces or tabs.
        boost::erase_all(subnet_txt, " ");
        boost::erase_all(subnet_txt, "\t");

        // The subnet format is prefix/len. We are going to extract
        // the prefix portion of a subnet string to create IOAddress
        // object from it. IOAddress will be passed to the Subnet's
        // constructor later on. In order to extract the prefix we
        // need to get all characters preceding "/".
        size_t pos = subnet_txt.find("/");
        if (pos == string::npos) {
            isc_throw(DhcpConfigError,
                      "Invalid subnet syntax (prefix/len expected):" << subnet_txt);
        }

        // Try to create the address object. It also validates that
        // the address syntax is ok.
        IOAddress addr(subnet_txt.substr(0, pos));
        uint8_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

        // Get all 'time' parameters using inheritance.
        // If the subnet-specific value is defined then use it, else
        // use the global value. The global value must always be
        // present. If it is not, it is an internal error and exception
        // is thrown.
        Triplet<uint32_t> t1 = getParam("renew-timer");
        Triplet<uint32_t> t2 = getParam("rebind-timer");
        Triplet<uint32_t> valid = getParam("valid-lifetime");

        /// @todo: Convert this to logger once the parser is working reliably
        stringstream tmp;
        tmp << addr.toText() << "/" << (int)len
            << " with params t1=" << t1 << ", t2=" << t2 << ", valid=" << valid;

        LOG_INFO(dhcp4_logger, DHCP4_CONFIG_NEW_SUBNET).arg(tmp.str());

        subnet_.reset(new Subnet4(addr, len, t1, t2, valid));

        for (PoolStorage::iterator it = pools_.begin(); it != pools_.end(); ++it) {
            subnet_->addPool(*it);
        }

        // We are going to move configured options to the Subnet object.
        // Configured options reside in the container where options
        // are grouped by space names. Thus we need to get all space names
        // and iterate over all options that belong to them.
        std::list<std::string> space_names = options_.getOptionSpaceNames();
        BOOST_FOREACH(std::string option_space, space_names) {
            // Get all options within a particular option space.
            BOOST_FOREACH(Subnet::OptionDescriptor desc,
                          *options_.getItems(option_space)) {
                // The pointer should be non-NULL. The validation is expected
                // to be performed by the OptionDataParser before adding an
                // option descriptor to the container.
                assert(desc.option);
                // We want to check whether an option with the particular
                // option code has been already added. If so, we want
                // to issue a warning.
                Subnet::OptionDescriptor existing_desc =
                    subnet_->getOptionDescriptor("option_space",
                                                 desc.option->getType());
                if (existing_desc.option) {
                    LOG_WARN(dhcp4_logger, DHCP4_CONFIG_OPTION_DUPLICATE)
                        .arg(desc.option->getType()).arg(addr.toText());
                }
                // Add sub-options (if any).
                appendSubOptions(option_space, desc.option);
                // In any case, we add the option to the subnet.
                subnet_->addOption(desc.option, false, option_space);
            }
        }

        // Check all global options and add them to the subnet object if
        // they have been configured in the global scope. If they have been
        // configured in the subnet scope we don't add global option because
        // the one configured in the subnet scope always takes precedence.
        space_names = option_defaults.getOptionSpaceNames();
        BOOST_FOREACH(std::string option_space, space_names) {
            // Get all global options for the particular option space.
            BOOST_FOREACH(Subnet::OptionDescriptor desc,
                          *option_defaults.getItems(option_space)) {
                // The pointer should be non-NULL. The validation is expected
                // to be performed by the OptionDataParser before adding an
                // option descriptor to the container.
                assert(desc.option);
                // Check if the particular option has been already added.
                // This would mean that it has been configured in the
                // subnet scope. Since option values configured in the
                // subnet scope take precedence over globally configured
                // values we don't add option from the global storage
                // if there is one already.
                Subnet::OptionDescriptor existing_desc =
                    subnet_->getOptionDescriptor(option_space, desc.option->getType());
                if (!existing_desc.option) {
                    // Add sub-options (if any).
                    appendSubOptions(option_space, desc.option);

                    subnet_->addOption(desc.option, false, option_space);
                }
            }
        }
    }

    /// @brief creates parsers for entries in subnet definition
    ///
    /// @todo Add subnet-specific things here (e.g. subnet-specific options)
    ///
    /// @param config_id name od the entry
    /// @return parser object for specified entry name
    /// @throw NotImplemented if trying to create a parser for unknown config element
    DhcpConfigParser* createSubnet4ConfigParser(const std::string& config_id) {
        FactoryMap factories;
        factories["valid-lifetime"] = Uint32Parser::factory;
        factories["renew-timer"] = Uint32Parser::factory;
        factories["rebind-timer"] = Uint32Parser::factory;
        factories["subnet"] = StringParser::factory;
        factories["pool"] = PoolParser::factory;
        factories["option-data"] = OptionDataListParser::factory;

        FactoryMap::iterator f = factories.find(config_id);
        if (f == factories.end()) {
            // Used for debugging only.
            // return new DebugParser(config_id);

            isc_throw(NotImplemented,
                      "parser error: Subnet4 parameter not supported: "
                      << config_id);
        }
        return (f->second(config_id));
    }

    /// @brief Returns value for a given parameter (after using inheritance)
    ///
    /// This method implements inheritance. For a given parameter name, it first
    /// checks if there is a global value for it and overwrites it with specific
    /// value if such value was defined in subnet.
    ///
    /// @param name name of the parameter
    /// @return triplet with the parameter name
    /// @throw DhcpConfigError when requested parameter is not present
    Triplet<uint32_t> getParam(const std::string& name) {
        uint32_t value = 0;
        try {
            // look for local value 
            value = uint32_values_.getParam(name);
        } catch (DhcpConfigError) {
            try {
                // no local, use global value 
                value = uint32_defaults.getParam(name);
            } catch (DhcpConfigError) {
                isc_throw(DhcpConfigError, "Mandatory parameter " << name
                      << " missing (no global default and no subnet-"
                      << "specific value)");
            }
        }

        return (Triplet<uint32_t>(value));
    }

    /// storage for subnet-specific uint32 values
    Uint32Storage uint32_values_;

    /// storage for subnet-specific integer values
    StringStorage string_values_;

    /// storage for pools belonging to this subnet
    PoolStorage pools_;

    /// storage for options belonging to this subnet
    OptionStorage options_;

    /// parsers are stored here
    ParserCollection parsers_;

    /// @brief Pointer to the created subnet object.
    isc::dhcp::Subnet4Ptr subnet_;
};

/// @brief this class parses list of subnets
///
/// This is a wrapper parser that handles the whole list of Subnet4
/// definitions. It iterates over all entries and creates Subnet4ConfigParser
/// for each entry.
class Subnets4ListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    Subnets4ListConfigParser(const std::string&) {
        /// parameter name is ignored
    }

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list and creates Subnet4ConfigParser
    /// for each entry.
    ///
    /// @param subnets_list pointer to a list of IPv4 subnets
    void build(ConstElementPtr subnets_list) {

        // No need to define FactoryMap here. There's only one type
        // used: Subnet4ConfigParser

        BOOST_FOREACH(ConstElementPtr subnet, subnets_list->listValue()) {
            ParserPtr parser(new Subnet4ConfigParser("subnet"));
            parser->build(subnet);
            subnets_.push_back(parser);
        }

    }

    /// @brief commits subnets definitions.
    ///
    /// Iterates over all Subnet4 parsers. Each parser contains definitions
    /// of a single subnet and its parameters and commits each subnet separately.
    void commit() {
        // @todo: Implement more subtle reconfiguration than toss
        // the old one and replace with the new one.

        // remove old subnets
        CfgMgr::instance().deleteSubnets4();

        BOOST_FOREACH(ParserPtr subnet, subnets_) {
            subnet->commit();
        }

    }

    /// @brief Returns Subnet4ListConfigParser object
    /// @param param_name name of the parameter
    /// @return Subnets4ListConfigParser object
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new Subnets4ListConfigParser(param_name));
    }

    /// @brief collection of subnet parsers.
    ParserCollection subnets_;

};

} // anonymous namespace

namespace isc {
namespace dhcp {

/// @brief creates global parsers
///
/// This method creates global parsers that parse global parameters, i.e.
/// those that take format of Dhcp4/param1, Dhcp4/param2 and so forth.
///
/// @param config_id pointer to received global configuration entry
/// @return parser for specified global DHCPv4 parameter
/// @throw NotImplemented if trying to create a parser for unknown config element
DhcpConfigParser* createGlobalDhcp4ConfigParser(const std::string& config_id) {
    FactoryMap factories;

    factories["valid-lifetime"] = Uint32Parser::factory;
    factories["renew-timer"] = Uint32Parser::factory;
    factories["rebind-timer"] = Uint32Parser::factory;
    factories["interface"] = InterfaceListConfigParser::factory;
    factories["subnet4"] = Subnets4ListConfigParser::factory;
    factories["option-data"] = OptionDataListParser::factory;
    factories["option-def"] = OptionDefListParser::factory;
    factories["version"] = StringParser::factory;
    factories["lease-database"] = DbAccessParser::factory;

    FactoryMap::iterator f = factories.find(config_id);
    if (f == factories.end()) {
        // Used for debugging only.
        // return new DebugParser(config_id);

        isc_throw(NotImplemented,
                  "Parser error: Global configuration parameter not supported: "
                  << config_id);
    }
    return (f->second(config_id));
}

isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv&, ConstElementPtr config_set) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    /// @todo: append most essential info here (like "2 new subnets configured")
    string config_details;

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_START).arg(config_set->str());

    // Some of the values specified in the configuration depend on
    // other values. Typically, the values in the subnet4 structure
    // depend on the global values. Also, option values configuration
    // must be performed after the option definitions configurations.
    // Thus we group parsers and will fire them in the right order:
    // all parsers other than subnet4 and option-data parser,
    // option-data parser, subnet4 parser.
    ParserCollection independent_parsers;
    ParserPtr subnet_parser;
    ParserPtr option_parser;

    // The subnet parsers implement data inheritance by directly
    // accessing global storage. For this reason the global data
    // parsers must store the parsed data into global storages
    // immediately. This may cause data inconsistency if the
    // parsing operation fails after the global storage has been
    // modified. We need to preserve the original global data here
    // so as we can rollback changes when an error occurs.
    Uint32Storage uint32_local(uint32_defaults);
    StringStorage string_local(string_defaults);
    OptionStorage option_local(option_defaults);
    OptionDefStorage option_def_local(option_def_intermediate);

    // answer will hold the result.
    ConstElementPtr answer;
    // rollback informs whether error occured and original data
    // have to be restored to global storages.
    bool rollback = false;
    // config_pair holds the details of the current parser when iterating over
    // the parsers.  It is declared outside the loops so in case of an error,
    // the name of the failing parser can be retrieved in the "catch" clause.
    ConfigPair config_pair;
    try {
        // Make parsers grouping.
        const std::map<std::string, ConstElementPtr>& values_map =
            config_set->mapValue();
        BOOST_FOREACH(config_pair, values_map) {
            ParserPtr parser(createGlobalDhcp4ConfigParser(config_pair.first));
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_PARSER_CREATED)
                      .arg(config_pair.first);
            if (config_pair.first == "subnet4") {
                subnet_parser = parser;

            } else if (config_pair.first == "option-data") {
                option_parser = parser;

            } else {
                // Those parsers should be started before other
                // parsers so we can call build straight away.
                independent_parsers.push_back(parser);
                parser->build(config_pair.second);
                // The commit operation here may modify the global storage
                // but we need it so as the subnet6 parser can access the
                // parsed data.
                parser->commit();
            }
        }

        // The option values parser is the next one to be run.
        std::map<std::string, ConstElementPtr>::const_iterator option_config =
            values_map.find("option-data");
        if (option_config != values_map.end()) {
            option_parser->build(option_config->second);
            option_parser->commit();
        }

        // The subnet parser is the last one to be run.
        std::map<std::string, ConstElementPtr>::const_iterator subnet_config =
            values_map.find("subnet4");
        if (subnet_config != values_map.end()) {
            subnet_parser->build(subnet_config->second);
        }

    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_FAIL)
                  .arg(config_pair.first).arg(ex.what());
        answer = isc::config::createAnswer(1,
                     string("Configuration parsing failed: ") + ex.what());

        // An error occured, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // for things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_EXCEPTION).arg(config_pair.first);
        answer = isc::config::createAnswer(1,
                     string("Configuration parsing failed"));

        // An error occured, so make sure that we restore original data.
        rollback = true;
    }

    // So far so good, there was no parsing error so let's commit the
    // configuration. This will add created subnets and option values into
    // the server's configuration.
    // This operation should be exception safe but let's make sure.
    if (!rollback) {
        try {
            if (subnet_parser) {
                subnet_parser->commit();
            }
        }
        catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(2,
                         string("Configuration commit failed: ") + ex.what());
            rollback = true;

        } catch (...) {
            // for things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(2,
                         string("Configuration commit failed"));
            rollback = true;

        }
    }

    // Rollback changes as the configuration parsing failed.
    if (rollback) {
        std::swap(uint32_defaults, uint32_local);
        std::swap(string_defaults, string_local);
        std::swap(option_defaults, option_local);
        std::swap(option_def_intermediate, option_def_local);
        return (answer);
    }

    LOG_INFO(dhcp4_logger, DHCP4_CONFIG_COMPLETE).arg(config_details);

    // Everything was fine. Configuration is successful.
    answer = isc::config::createAnswer(0, "Configuration committed.");
    return (answer);
}

const Uint32Storage& getUint32Defaults() {
    return (uint32_defaults);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
