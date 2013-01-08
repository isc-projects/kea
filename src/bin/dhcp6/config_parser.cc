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

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <config/ccsession.h>
#include <dhcp/libdhcp++.h>
#include <dhcp6/config_parser.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/triplet.h>
#include <log/logger_support.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <map>
#include <vector>

#include <stdint.h>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

/// @brief Auxiliary type used for storing an element name and its parser.
typedef pair<string, ConstElementPtr> ConfigPair;

/// @brief Factory method that will create a parser for a given element name
typedef isc::dhcp::DhcpConfigParser* ParserFactory(const std::string& config_id);

/// @brief Collection of factories that create parsers for specified element names
typedef std::map<std::string, ParserFactory*> FactoryMap;

/// @brief Storage for parsed boolean values.
typedef std::map<string, bool> BooleanStorage;

/// @brief Collection of elements that store uint32 values (e.g. renew-timer = 900).
typedef std::map<string, uint32_t> Uint32Storage;

/// @brief Collection of elements that store string values.
typedef std::map<string, string> StringStorage;

/// @brief Collection of address pools.
///
/// This type is used as intermediate storage, when pools are parsed, but there is
/// no subnet object created yet to store them.
typedef std::vector<isc::dhcp::Pool6Ptr> PoolStorage;

/// @brief Collection of option descriptors.
///
/// This container allows to search options using an option code
/// or a persistency flag. This is useful when merging existing
/// options with newly configured options.
typedef isc::dhcp::Subnet::OptionContainer OptionStorage;

/// @brief Global uint32 parameters that will be used as defaults.
Uint32Storage uint32_defaults;

/// @brief global string parameters that will be used as defaults.
StringStorage string_defaults;

/// @brief Global storage for options that will be used as defaults.
OptionStorage option_defaults;

/// @brief a dummy configuration parser
///
/// This is a debugging parser. It does not configure anything,
/// will accept any configuration and will just print it out
/// on commit.  Useful for debugging existing configurations and
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

    /// @brief Pretends to apply the configuration.
    ///
    /// This is a method required by the base class. It pretends to apply the
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
    static DhcpConfigParser* factory(const std::string& param_name) {
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
            isc_throw(isc::dhcp::Dhcp6ConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
    }

    /// @brief Parse a boolean value.
    ///
    /// @param value a value to be parsed.
    ///
    /// @throw isc::InvalidOperation if a storage has not been set
    ///        prior to calling this function
    /// @throw isc::dhcp::Dhcp6ConfigError if a provided parameter's
    ///        name is empty.
    virtual void build(ConstElementPtr value) {
        if (storage_ == NULL) {
            isc_throw(isc::InvalidOperation, "parser logic error:"
                      << " storage for the " << param_name_
                      << " value has not been set");
        } else if (param_name_.empty()) {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "parser logic error:"
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
            (*storage_)[param_name_] = value_;
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
/// @ref dhcpv6ConfigInherit page.
///
/// @todo this class should be turned into the template class which
/// will handle all uintX_types of data (see ticket #2415).
class Uint32Parser : public DhcpConfigParser {
public:

    /// @brief constructor for Uint32Parser
    ///
    /// @param param_name name of the configuration parameter being parsed
    Uint32Parser(const std::string& param_name)
        : storage_(&uint32_defaults),
          param_name_(param_name) {
        // Empty parameter name is invalid.
        if (param_name_.empty()) {
            isc_throw(Dhcp6ConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
    }

    /// @brief Parses configuration configuration parameter as uint32_t.
    ///
    /// @param value pointer to the content of parsed values
    /// @throw isc::dhcp::Dhcp6ConfigError if failed to parse
    ///        the configuration parameter as uint32_t value.
    virtual void build(ConstElementPtr value) {
        if (param_name_.empty()) {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }

        bool parse_error = false;
        // Cast the provided value to int64 value to check.
        int64_t int64value = 0;
        try {
            // Parsing the value as a int64 value allows to
            // check if the provided value is within the range
            // of uint32_t (is not negative or greater than
            // maximal uint32_t value).
            int64value = boost::lexical_cast<int64_t>(value->str());
        } catch (const boost::bad_lexical_cast&) {
            parse_error = true;
        }
        if (!parse_error) {
            // Check that the value is not out of bounds.
            if ((int64value < 0) ||
                (int64value > std::numeric_limits<uint32_t>::max())) {
                parse_error = true;
            } else {
                // A value is not out of bounds so let's cast it to
                // the uint32_t type.
                value_ = static_cast<uint32_t>(int64value);
            }

        }
        // Invalid value provided.
        if (parse_error) {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "Failed to parse value " << value->str()
                      << " as unsigned 32-bit integer.");
        }
    }

    /// @brief Stores the parsed uint32_t value in a storage.
    virtual void commit() {
        if (storage_ != NULL) {
            // If a given parameter already exists in the storage we override
            // its value. If it doesn't we insert a new element.
            (*storage_)[param_name_] = value_;
        }
    }

    /// @brief Factory that constructs Uint32Parser objects.
    ///
    /// @param param_name name of the parameter to be parsed.
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new Uint32Parser(param_name));
    }

    /// @brief Sets storage for value of this parameter.
    ///
    /// See @ref dhcpv6ConfigInherit for details.
    ///
    /// @param storage pointer to the storage container.
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
/// parameter. By default it stores the value in an external global container
/// (string_defaults). If used in smaller scopes (e.g. to parse parameters
/// in subnet config), it can be pointed to a different storage, using the
/// setStorage() method. This class follows the parser interface, laid out
/// in its base class, @ref DhcpConfigParser.
///
/// For overview of usability of this generic purpose parser, see
/// @ref dhcpv6ConfigInherit page.
class StringParser : public DhcpConfigParser {
public:

    /// @brief constructor for StringParser
    ///
    /// @param param_name name of the configuration parameter being parsed
    StringParser(const std::string& param_name)
        : storage_(&string_defaults),
          param_name_(param_name) {
        // Empty parameter name is invalid.
        if (param_name_.empty()) {
            isc_throw(Dhcp6ConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
    }

    /// @brief parses parameter value
    ///
    /// Parses configuration parameter's value as string.
    ///
    /// @param value pointer to the content of parsed values
    /// @throws Dhcp6ConfigError if the parsed parameter's name is empty.
    virtual void build(ConstElementPtr value) {
        if (param_name_.empty()) {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "parser logic error:"
                      << "empty parameter name provided");
        }
        value_ = value->str();
        boost::erase_all(value_, "\"");
    }

    /// @brief Stores the parsed value in a storage.
    virtual void commit() {
        if (storage_ != NULL && !param_name_.empty()) {
            // If a given parameter already exists in the storage we override
            // its value. If it doesn't we insert a new element.
            (*storage_)[param_name_] = value_;
        }
    }

    /// @brief Factory that constructs StringParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new StringParser(param_name));
    }

    /// @brief Sets storage for value of this parameter.
    ///
    /// See @ref dhcpv6ConfigInherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(StringStorage* storage) {
        storage_ = storage;
    }

private:
    /// Pointer to the storage, where parsed value will be stored
    StringStorage* storage_;
    /// Name of the parameter to be parsed
    std::string param_name_;
    /// The actual parsed value
    std::string value_;
};

/// @brief parser for interface list definition
///
/// This parser handles Dhcp6/interface entry.
/// It contains a list of network interfaces that the server listens on.
/// In particular, it can contain an entry called "all" or "any" that
/// designates all interfaces.
///
/// It is useful for parsing Dhcp6/interface parameter.
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
            isc_throw(isc::BadValue, "Internal error. Interface configuration "
                      "parser called for the wrong parameter: " << param_name);
        }
    }

    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of parameters) and stores it in
    /// storage.
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
/// of two syntaxes: min-max and prefix/len. Pool6 objects are created
/// and stored in chosen PoolStorage container.
///
/// As there are no default values for pool, setStorage() must be called
/// before build(). Otherwise an exception will be thrown.
///
/// It is useful for parsing Dhcp6/subnet6[X]/pool parameters.
class PoolParser : public DhcpConfigParser {
public:

    /// @brief constructor.
    PoolParser(const std::string& /*param_name*/)
        : pools_(NULL) {
        // ignore parameter name, it is always Dhcp6/subnet6[X]/pool
    }

    /// @brief parses the actual list
    ///
    /// This method parses the actual list of interfaces.
    /// No validation is done at this stage, everything is interpreted as
    /// interface name.
    /// @param pools_list list of pools defined for a subnet
    /// @throw isc::InvalidOperation if storage was not specified
    ///        (setStorage() not called)
    void build(ConstElementPtr pools_list) {

        // setStorage() should have been called before build
        if (!pools_) {
            isc_throw(isc::InvalidOperation, "parser logic error: no pool storage set,"
                      " but pool parser asked to parse pools");
        }

        BOOST_FOREACH(ConstElementPtr text_pool, pools_list->listValue()) {

            // That should be a single pool representation. It should contain
            // text in the form prefix/len or first - last. Note that spaces
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

                    // It is lexically cast to int and then downcast to uint8_t.
                    // Direct cast to uint8_t (which is really an unsigned char)
                    // will result in interpreting the first digit as output
                    // value and throwing exception if length is written on two
                    // digits (because there are extra characters left over).

                    // No checks for values over 128. Range correctness will
                    // be checked in Pool6 constructor.
                    len = boost::lexical_cast<int>(prefix_len);
                } catch (...)  {
                    isc_throw(Dhcp6ConfigError, "failed to parse pool "
                              "definition: " << text_pool->stringValue());
                }

                Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, addr, len));
                local_pools_.push_back(pool);
                continue;
            }

            // Is this min-max notation?
            pos = txt.find("-");
            if (pos != string::npos) {
                // using min-max notation
                IOAddress min(txt.substr(0, pos));
                IOAddress max(txt.substr(pos + 1));

                Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, min, max));

                local_pools_.push_back(pool);
                continue;
            }

            isc_throw(Dhcp6ConfigError, "failed to parse pool definition:"
                      << text_pool->stringValue() <<
                      ". Does not contain - (for min-max) nor / (prefix/len)");
        }
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See @ref dhcpv6ConfigInherit for details.
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
    /// This is typically a storage somewhere in Subnet parser
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
/// and data carried by the option. If parsing is successful then an
/// instance of an option is created and added to the storage provided
/// by the calling class.
///
/// @todo This class parses and validates the option name. However it is
/// not used anywhere until support for option spaces is implemented
/// (see tickets #2319, #2314). When option spaces are implemented
/// there will be a way to reference the particular option using
/// its type (code) or option name.
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
    /// @throw Dhcp6ConfigError if invalid parameter specified in
    /// the configuration.
    /// @throw isc::InvalidOperation if failed to set storage prior to
    /// calling build.
    /// @throw isc::BadValue if option data storage is invalid.
    virtual void build(ConstElementPtr option_data_entries) {

        if (options_ == NULL) {
            isc_throw(isc::InvalidOperation, "Parser logic error: storage must be set before "
                      "parsing option data.");
        }
        BOOST_FOREACH(ConfigPair param, option_data_entries->mapValue()) {
            ParserPtr parser;
            if (param.first == "name") {
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
            } else if (param.first == "data") {
                boost::shared_ptr<StringParser>
                    value_parser(dynamic_cast<StringParser*>(StringParser::factory(param.first)));
                if (value_parser) {
                    value_parser->setStorage(&string_values_);
                    parser = value_parser;
                }
            } else if (param.first == "csv-format") {
                boost::shared_ptr<BooleanParser>
                    value_parser(dynamic_cast<BooleanParser*>(BooleanParser::factory(param.first)));
                if (value_parser) {
                    value_parser->setStorage(&boolean_values_);
                    parser = value_parser;
                }
            } else {
                isc_throw(Dhcp6ConfigError,
                          "parser error: option-data parameter not supported: "
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
                      "commiting option data.");
        } else  if (!option_descriptor_.option) {
            // Before we can commit the new option should be configured. If it is not
            // than somebody must have called commit() before build().
            isc_throw(isc::InvalidOperation, "parser logic error: no option has been configured and"
                      " thus there is nothing to commit. Has build() been called?");
        }
        uint16_t opt_type = option_descriptor_.option->getType();
        isc::dhcp::Subnet::OptionContainerTypeIndex& idx = options_->get<1>();
        // Try to find options with the particular option code in the main
        // storage. If found, remove these options because they will be
        // replaced with new one.
        isc::dhcp::Subnet::OptionContainerTypeRange range =
            idx.equal_range(opt_type);
        if (std::distance(range.first, range.second) > 0) {
            idx.erase(range.first, range.second);
        }
        // Append new option to the main storage.
        options_->push_back(option_descriptor_);
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
    /// is intitialized but this check is not needed here because it is done
    /// in the \ref build function.
    ///
    /// @throw Dhcp6ConfigError if parameters provided in the configuration
    /// are invalid.
    void createOption() {

        // Option code is held in the uint32_t storage but is supposed to
        // be uint16_t value. We need to check that value in the configuration
        // does not exceed range of uint16_t and is not zero.
        uint32_t option_code = getUint32Param("code");
        if (option_code == 0) {
            isc_throw(Dhcp6ConfigError, "Parser error: value of 'code' must not"
                      << " be equal to zero. Option code '0' is reserved in"
                      << " DHCPv6.");
        } else if (option_code > std::numeric_limits<uint16_t>::max()) {
            isc_throw(Dhcp6ConfigError, "Parser error: value of 'code' must not"
                      << " exceed " << std::numeric_limits<uint16_t>::max());
        }
        // Check that the option name has been specified, is non-empty and does not
        // contain spaces.
        // @todo possibly some more restrictions apply here?
        std::string option_name = getStringParam("name");
        if (option_name.empty()) {
            isc_throw(Dhcp6ConfigError, "Parser error: option name must not be"
                      << " empty");
        } else if (option_name.find(" ") != std::string::npos) {
            isc_throw(Dhcp6ConfigError, "Parser error: option name must not contain"
                      << " spaces");
        }

        // Get option data from the configuration database ('data' field).
        const std::string option_data = getStringParam("data");
        const bool csv_format = getBooleanParam("csv-format");
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
                isc::util::encode::decodeHex(option_data, binary);
            } catch (...) {
                isc_throw(Dhcp6ConfigError, "Parser error: option data is not a valid"
                          << " string of hexadecimal digits: " << option_data);
            }
        }
        // Get all existing DHCPv6 option definitions. The one that matches
        // our option will be picked and used to create it.
        OptionDefContainer option_defs = LibDHCP::getOptionDefs(Option::V6);
        // Get search index #1. It allows searching for options definitions
        // using option type value.
        const OptionDefContainerTypeIndex& idx = option_defs.get<1>();
        // Get all option definitions matching option code we want to create.
        const OptionDefContainerTypeRange& range = idx.equal_range(option_code);
        size_t num_defs = std::distance(range.first, range.second);
        OptionPtr option;
        // Currently we do not allow duplicated definitions and if there are
        // any duplicates we issue internal server error.
        if (num_defs > 1) {
            isc_throw(Dhcp6ConfigError, "Internal error: currently it is not"
                      << " supported to initialize multiple option definitions"
                      << " for the same option code. This will be supported once"
                      << " there option spaces are implemented.");
        } else if (num_defs == 0) {
            if (csv_format) {
                isc_throw(Dhcp6ConfigError, "the CSV option data format can be"
                          " used to specify values for an option that has a"
                          " definition. The option with code " << option_code
                          << " does not have a definition.");
            }
            // @todo We have a limited set of option definitions intiialized at the moment.
            // In the future we want to initialize option definitions for all options.
            // Consequently an error will be issued if an option definition does not exist
            // for a particular option code. For now it is ok to create generic option
            // if definition does not exist.
            OptionPtr option(new Option(Option::V6, static_cast<uint16_t>(option_code),
                                        binary));
            // The created option is stored in option_descriptor_ class member until the
            // commit stage when it is inserted into the main storage. If an option with the
            // same code exists in main storage already the old option is replaced.
            option_descriptor_.option = option;
            option_descriptor_.persistent = false;
        } else {
            // We have exactly one option definition for the particular option code
            // use it to create the option instance.
            const OptionDefinitionPtr& def = *(range.first);
            try {
                OptionPtr option = csv_format ?
                    def->optionFactory(Option::V6, option_code, data_tokens) :
                    def->optionFactory(Option::V6, option_code, binary);
                Subnet::OptionDescriptor desc(option, false);
                option_descriptor_.option = option;
                option_descriptor_.persistent = false;
            } catch (const isc::Exception& ex) {
                isc_throw(Dhcp6ConfigError, "Parser error: option data does not match"
                          << " option definition (code " << option_code << "): "
                          << ex.what());
            }
        }
    }

    /// @brief Get a parameter from the strings storage.
    ///
    /// @param param_id parameter identifier.
    ///
    /// @throw Dhcp6ConfigError if a parameter has not been found.
    /// @return a value of the string parameter.
    std::string getStringParam(const std::string& param_id) const {
        StringStorage::const_iterator param = string_values_.find(param_id);
        if (param == string_values_.end()) {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "parser error: option-data parameter"
                      << " '" << param_id << "' not specified");
        }
        return (param->second);
    }

    /// @brief Get a parameter from the uint32 values storage.
    ///
    /// @param param_id parameter identifier.
    ///
    /// @throw Dhcp6ConfigError if a parameter has not been found.
    /// @return a value of the uint32_t parameter.
    uint32_t getUint32Param(const std::string& param_id) const {
        Uint32Storage::const_iterator param = uint32_values_.find(param_id);
        if (param == uint32_values_.end()) {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "parser error: option-data parameter"
                      << " '" << param_id << "' not specified");
        }
        return (param->second);
    }

    /// @brief Get a parameter from the boolean values storage.
    ///
    /// @param param_id parameter identifier.
    ///
    /// @throw isc::dhcp::Dhcp6ConfigError if a parameter has not been found.
    /// @return a value of the boolean parameter.
    bool getBooleanParam(const std::string& param_id) const {
        BooleanStorage::const_iterator param = boolean_values_.find(param_id);
        if (param == boolean_values_.end()) {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "parser error: option-data parameter"
                      << " '" << param_id << "' not specified");
        }
        return (param->second);
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
    isc::dhcp::Subnet::OptionDescriptor option_descriptor_;
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
    /// @throw Dhcp6ConfigError if option parsing failed.
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

    /// Intermediate option storage. This storage is used by
    /// lower level parsers to add new options.  Values held
    /// in this storage are assigned to main storage (options_)
    /// if overall parsing was successful.
    OptionStorage local_options_;
    /// Pointer to options instances storage.
    OptionStorage* options_;
    /// Collection of parsers;
    ParserCollection parsers_;
};

/// @brief this class parses a single subnet
///
/// This class parses the whole subnet definition. It creates parsers
/// for received configuration parameters as needed.
class Subnet6ConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    Subnet6ConfigParser(const std::string& ) {
        // The parameter should always be "subnet", but we don't check
        // against that here in case some wants to reuse this parser somewhere.
    }

    /// @brief parses parameter value
    ///
    /// @param subnet pointer to the content of subnet definition
    ///
    /// @throw isc::Dhcp6ConfigError if subnet configuration parsing failed.
    void build(ConstElementPtr subnet) {

        BOOST_FOREACH(ConfigPair param, subnet->mapValue()) {
            ParserPtr parser(createSubnet6ConfigParser(param.first));
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
                isc_throw(Dhcp6ConfigError, "failed to find suitable parser");
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

    /// @brief Adds the created subnet to a server's configuration.
    void commit() {
        if (subnet_) {
            isc::dhcp::CfgMgr::instance().addSubnet6(subnet_);
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

    /// @brief Create a new subnet using a data from child parsers.
    ///
    /// @throw isc::dhcp::Dhcp6ConfigError if subnet configuration parsing failed.
    void createSubnet() {
        
        // Find a subnet string.
        StringStorage::const_iterator it = string_values_.find("subnet");
        if (it == string_values_.end()) {
            isc_throw(Dhcp6ConfigError,
                      "Mandatory subnet definition in subnet missing");
        }
        // Remove any spaces or tabs.
        string subnet_txt = it->second;
        boost::erase_all(subnet_txt, " ");
        boost::erase_all(subnet_txt, "\t");
        // The subnet format is prefix/len. We are going to extract
        // the prefix portion of a subnet string to create IOAddress
        // object from it. IOAddress will be passed to the Subnet's
        // constructor later on. In order to extract the prefix we
        // need to get all characters preceding "/".
        size_t pos = subnet_txt.find("/");
        if (pos == string::npos) {
            isc_throw(Dhcp6ConfigError,
                      "Invalid subnet syntax (prefix/len expected):" << it->second);
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
        Triplet<uint32_t> pref = getParam("preferred-lifetime");
        Triplet<uint32_t> valid = getParam("valid-lifetime");

        /// @todo: Convert this to logger once the parser is working reliably
        stringstream tmp;
        tmp << addr.toText() << "/" << (int)len
            << " with params t1=" << t1 << ", t2=" << t2 << ", pref="
            << pref << ", valid=" << valid;

        LOG_INFO(dhcp6_logger, DHCP6_CONFIG_NEW_SUBNET).arg(tmp.str());

        // Create a new subnet.
        subnet_.reset(new Subnet6(addr, len, t1, t2, pref, valid));

        // Add pools to it.
        for (PoolStorage::iterator it = pools_.begin(); it != pools_.end(); ++it) {
            subnet_->addPool6(*it);
        }

        Subnet::OptionContainerPtr options = subnet_->getOptionDescriptors("dhcp6");
        const Subnet::OptionContainerTypeIndex& idx = options->get<1>();

        // Add subnet specific options.
        BOOST_FOREACH(Subnet::OptionDescriptor desc, options_) {
            Subnet::OptionContainerTypeRange range = idx.equal_range(desc.option->getType());
            if (std::distance(range.first, range.second) > 0) {
                LOG_WARN(dhcp6_logger, DHCP6_CONFIG_OPTION_DUPLICATE)
                    .arg(desc.option->getType()).arg(addr.toText());
            }
            subnet_->addOption(desc.option, false, "dhcp6");
        }

        // Check all global options and add them to the subnet object if
        // they have been configured in the global scope. If they have been
        // configured in the subnet scope we don't add global option because
        // the one configured in the subnet scope always takes precedence.
        BOOST_FOREACH(Subnet::OptionDescriptor desc, option_defaults) {
            // Get all options specified locally in the subnet and having
            // code equal to global option's code.
            Subnet::OptionContainerPtr options = subnet_->getOptionDescriptors("dhcp6");
            const Subnet::OptionContainerTypeIndex& idx = options->get<1>();
            Subnet::OptionContainerTypeRange range = idx.equal_range(desc.option->getType());
            // @todo: In the future we will be searching for options using either
            // an option code or namespace. Currently we have only the option
            // code available so if there is at least one option found with the
            // specific code we don't add the globally configured option.
            // @todo with this code the first globally configured option
            // with the given code will be added to a subnet. We may
            // want to issue a warning about dropping the configuration of
            // a global option if one already exsists.
            if (std::distance(range.first, range.second) == 0) {
                subnet_->addOption(desc.option, false, "dhcp6");
            }
        }
    }

    /// @brief creates parsers for entries in subnet definition
    ///
    /// @param config_id name od the entry
    ///
    /// @return parser object for specified entry name
    /// @throw isc::dhcp::Dhcp6ConfigError if trying to create a parser
    ///        for unknown config element
    DhcpConfigParser* createSubnet6ConfigParser(const std::string& config_id) {
        FactoryMap factories;

        factories["preferred-lifetime"] = Uint32Parser::factory;
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

            isc_throw(isc::dhcp::Dhcp6ConfigError,
                      "parser error: subnet6 parameter not supported: "
                      << config_id);
        }
        return (f->second(config_id));
    }

    /// @brief Returns value for a given parameter (after using inheritance)
    ///
    /// This method implements inheritance.  For a given parameter name, it first
    /// checks if there is a global value for it and overwrites it with specific
    /// value if such value was defined in subnet.
    ///
    /// @param name name of the parameter
    /// @return triplet with the parameter name
    /// @throw Dhcp6ConfigError when requested parameter is not present
    isc::dhcp::Triplet<uint32_t> getParam(const std::string& name) {
        uint32_t value = 0;
        bool found = false;
        Uint32Storage::iterator global = uint32_defaults.find(name);
        if (global != uint32_defaults.end()) {
            value = global->second;
            found = true;
        }

        Uint32Storage::iterator local = uint32_values_.find(name);
        if (local != uint32_values_.end()) {
            value = local->second;
            found = true;
        }

        if (found) {
            return (isc::dhcp::Triplet<uint32_t>(value));
        } else {
            isc_throw(isc::dhcp::Dhcp6ConfigError, "Mandatory parameter " << name
                      << " missing (no global default and no subnet-"
                      << "specific value)");
        }
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

    /// Pointer to the created subnet object.
    isc::dhcp::Subnet6Ptr subnet_;
};

/// @brief this class parses a list of subnets
///
/// This is a wrapper parser that handles the whole list of Subnet6
/// definitions. It iterates over all entries and creates Subnet6ConfigParser
/// for each entry.
class Subnets6ListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    Subnets6ListConfigParser(const std::string&) {
        /// parameter name is ignored
    }

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list and creates a Subnet6ConfigParser
    /// for each entry.
    ///
    /// @param subnets_list pointer to a list of IPv6 subnets
    void build(ConstElementPtr subnets_list) {

        // No need to define FactoryMap here. There's only one type
        // used: Subnet6ConfigParser

        BOOST_FOREACH(ConstElementPtr subnet, subnets_list->listValue()) {

            ParserPtr parser(new Subnet6ConfigParser("subnet"));
            parser->build(subnet);
            subnets_.push_back(parser);
        }

    }

    /// @brief commits subnets definitions.
    ///
    /// Iterates over all Subnet6 parsers. Each parser contains definitions
    /// of a single subnet and its parameters and commits each subnet separately.
    void commit() {
        // @todo: Implement more subtle reconfiguration than toss
        // the old one and replace with the new one.

        // remove old subnets
        isc::dhcp::CfgMgr::instance().deleteSubnets6();

        BOOST_FOREACH(ParserPtr subnet, subnets_) {
            subnet->commit();
        }

    }

    /// @brief Returns Subnet6ListConfigParser object
    /// @param param_name name of the parameter
    /// @return Subnets6ListConfigParser object
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new Subnets6ListConfigParser(param_name));
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
/// those that take format of Dhcp6/param1, Dhcp6/param2 and so forth.
///
/// @param config_id pointer to received global configuration entry
/// @return parser for specified global DHCPv6 parameter
/// @throw NotImplemented if trying to create a parser for unknown config element
DhcpConfigParser* createGlobalDhcpConfigParser(const std::string& config_id) {
    FactoryMap factories;

    factories["preferred-lifetime"] = Uint32Parser::factory;
    factories["valid-lifetime"] = Uint32Parser::factory;
    factories["renew-timer"] = Uint32Parser::factory;
    factories["rebind-timer"] = Uint32Parser::factory;
    factories["interface"] = InterfaceListConfigParser::factory;
    factories["subnet6"] = Subnets6ListConfigParser::factory;
    factories["option-data"] = OptionDataListParser::factory;
    factories["version"] = StringParser::factory;

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

ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& , ConstElementPtr config_set) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    /// @todo: append most essential info here (like "2 new subnets configured")
    string config_details;

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_START).arg(config_set->str());

    // Some of the values specified in the configuration depend on
    // other values. Typically, the values in the subnet6 structure
    // depend on the global values. Thus we need to make sure that
    // the global values are processed first and that they can be
    // accessed by the subnet6 parsers. We separate parsers that
    // should process data first (independent_parsers) from those
    // that must process data when the independent data is already
    // processed (dependent_parsers).
    ParserCollection independent_parsers;
    ParserCollection dependent_parsers;

    // The subnet parsers implement data inheritance by directly
    // accessing global storages. For this reason the global data
    // parsers must store the parsed data into global storages
    // immediately. This may cause data inconsistency if the
    // parsing operation fails after the global storage has been
    // modified. We need to preserve the original global data here
    // so as we can rollback changes when an error occurs.
    Uint32Storage uint32_local(uint32_defaults);
    StringStorage string_local(string_defaults);
    OptionStorage option_local(option_defaults);

    // answer will hold the result.
    ConstElementPtr answer;
    // rollback informs whether error occured and original data
    // have to be restored to global storages.
    bool rollback = false;
    try {
        // Iterate over all independent parsers first (all but subnet6)
        // and try to parse the data.
        BOOST_FOREACH(ConfigPair config_pair, config_set->mapValue()) {
            if (config_pair.first != "subnet6") {
                ParserPtr parser(createGlobalDhcpConfigParser(config_pair.first));
                independent_parsers.push_back(parser);
                parser->build(config_pair.second);
                // The commit operation here may modify the global storage
                // but we need it so as the subnet6 parser can access the
                // parsed data.
                parser->commit();
            }
        }

        // Process dependent configuration data.
        BOOST_FOREACH(ConfigPair config_pair, config_set->mapValue()) {
            if (config_pair.first == "subnet6") {
                ParserPtr parser(createGlobalDhcpConfigParser(config_pair.first));
                dependent_parsers.push_back(parser);
                parser->build(config_pair.second);
            }
        }

    } catch (const isc::Exception& ex) {
        answer =
            isc::config::createAnswer(1, string("Configuration parsing failed: ") + ex.what());
        // An error occured, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // for things like bad_cast in boost::lexical_cast
        answer =
            isc::config::createAnswer(1, string("Configuration parsing failed"));
        // An error occured, so make sure that we restore original data.
        rollback = true;
    }

    // So far so good, there was no parsing error so let's commit the
    // configuration. This will add created subnets and option values into
    // the server's configuration.
    // This operation should be exception safe but let's make sure.
    if (!rollback) {
        try {
            BOOST_FOREACH(ParserPtr parser, dependent_parsers) {
                parser->commit();
            }
        }
        catch (const isc::Exception& ex) {
            answer =
                isc::config::createAnswer(2, string("Configuration commit failed:") 
                                          + ex.what());
            // An error occured, so make sure to restore the original data.
            rollback = true;
        } catch (...) {
            // for things like bad_cast in boost::lexical_cast
            answer =
                isc::config::createAnswer(2, string("Configuration commit failed"));
            // An error occured, so make sure to restore the original data.
            rollback = true;
        }
    }

    // Rollback changes as the configuration parsing failed.
    if (rollback) {
        std::swap(uint32_defaults, uint32_local);
        std::swap(string_defaults, string_local);
        std::swap(option_defaults, option_local);
        return (answer);
    }

    LOG_INFO(dhcp6_logger, DHCP6_CONFIG_COMPLETE).arg(config_details);

    // Everything was fine. Configuration is successful.
    answer = isc::config::createAnswer(0, "Configuration commited.");
    return (answer);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
