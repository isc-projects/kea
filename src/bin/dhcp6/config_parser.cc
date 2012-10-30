// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <stdint.h>
#include <iostream>
#include <vector>
#include <map>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <util/encode/hex.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <config/ccsession.h>
#include <log/logger_support.h>
#include <dhcp/triplet.h>
#include <dhcp/pool.h>
#include <dhcp/subnet.h>
#include <dhcp/cfgmgr.h>
#include <dhcp6/config_parser.h>
#include <dhcp6/dhcp6_log.h>

using namespace std;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

/// @brief auxiliary type used for storing element name and its parser
typedef pair<string, ConstElementPtr> ConfigPair;

/// @brief a factory method that will create a parser for a given element name
typedef DhcpConfigParser* ParserFactory(const std::string& config_id);

/// @brief a collection of factories that creates parsers for specified element names
typedef std::map<std::string, ParserFactory*> FactoryMap;

/// @brief a collection of elements that store uint32 values (e.g. renew-timer = 900)
typedef std::map<string, uint32_t> Uint32Storage;

/// @brief a collection of elements that store string values
typedef std::map<string, string> StringStorage;

/// @brief a collection of pools
///
/// That type is used as intermediate storage, when pools are parsed, but there is
/// no subnet object created yet to store them.
typedef std::vector<Pool6Ptr> PoolStorage;

/// @brief Collection of options.
typedef std::vector<OptionPtr> OptionStorage;

/// @brief Global uint32 parameters that will be used as defaults.
Uint32Storage uint32_defaults;

/// @brief global string parameters that will be used as defaults.
StringStorage string_defaults;

/// @brief Global storage for options that will be used as defaults.
OptionStorage option_defaults;

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
    /// See \ref DhcpConfigParser class for details.
    ///
    /// @param param_name name of the parsed parameter
    DebugParser(const std::string& param_name)
        :param_name_(param_name) {
    }

    /// @brief builds parameter value
    ///
    /// See \ref DhcpConfigParser class for details.
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
    /// See \ref DhcpConfigParser class for details.
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

protected:
    /// name of the parsed parameter
    std::string param_name_;

    /// pointer to the actual value of the parameter
    ConstElementPtr value_;
};

/// @brief Configuration parser for uint32 parameters
///
/// This class is a generic parser that is able to handle any uint32 integer
/// type. By default it stores the value in external global container
/// (uint32_defaults). If used in smaller scopes (e.g. to parse parameters
/// in subnet config), it can be pointed to a different storage, using
/// setStorage() method. This class follows the parser interface, laid out
/// in its base class, \ref DhcpConfigParser.
///
/// For overview of usability of this generic purpose parser, see
/// \ref dhcpv6-config-inherit page.
class Uint32Parser : public DhcpConfigParser {
public:

    /// @brief constructor for Uint32Parser
    /// @param param_name name of the configuration parameter being parsed
    Uint32Parser(const std::string& param_name)
        :storage_(&uint32_defaults), param_name_(param_name) {
    }

    /// @brief builds parameter value
    ///
    /// Parses configuration entry and stores it in a storage. See
    /// \ref setStorage() for details.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(ConstElementPtr value) {
        bool parse_error = false;
        // Cast the provided value to int64 value to check.
        int64_t int64value = 0;
        try {
            // Parsing the value as a int64 value allows to
            // check if the provided value is within the range
            // of uint32_t (is not negative or greater than
            // maximal uint32_t value.
            int64value = boost::lexical_cast<int64_t>(value->str());
        } catch (const boost::bad_lexical_cast&) {
            parse_error = true;
        }
        if (!parse_error) {
            if ((int64value < 0) ||
                (int64value > std::numeric_limits<uint32_t>::max())) {
                parse_error = true;
            } else {
                try {
                    value_ = boost::lexical_cast<uint32_t>(value->str());
                } catch (const boost::bad_lexical_cast &) {
                    parse_error = true;
                }
            }

        }

        if (parse_error) {
            isc_throw(BadValue, "Failed to parse value " << value->str()
                      << " as unsigned 32-bit integer.");
        }

        storage_->insert(pair<string, uint32_t>(param_name_, value_));
    }

    /// @brief does nothing
    ///
    /// This method is required for all parser. The value itself
    /// is not commited anywhere. Higher level parsers are expected to
    /// use values stored in the storage, e.g. renew-timer for a given
    /// subnet is stored in subnet-specific storage. It is not commited
    /// here, but is rather used by \ref Subnet6Parser when constructing
    /// the subnet.
    virtual void commit() {
    }

    /// @brief factory that constructs Uint32Parser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* Factory(const std::string& param_name) {
        return (new Uint32Parser(param_name));
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See \ref dhcpv6-config-inherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(Uint32Storage* storage) {
        storage_ = storage;
    }

protected:
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
/// in its base class, \ref DhcpConfigParser.
///
/// For overview of usability of this generic purpose parser, see
/// \ref dhcpv6-config-inherit page.
class StringParser : public DhcpConfigParser {
public:

    /// @brief constructor for StringParser
    /// @param param_name name of the configuration parameter being parsed
    StringParser(const std::string& param_name)
        :storage_(&string_defaults), param_name_(param_name) {
    }

    /// @brief parses parameter value
    ///
    /// Parses configuration entry and stored it in storage. See
    /// \ref setStorage() for details.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(ConstElementPtr value) {
        value_ = value->str();
        boost::erase_all(value_, "\"");
        storage_->insert(pair<string, string>(param_name_, value_));
    }

    /// @brief does nothing
    ///
    /// This method is required for all parser. The value itself
    /// is not commited anywhere. Higher level parsers are expected to
    /// use values stored in the storage, e.g. renew-timer for a given
    /// subnet is stored in subnet-specific storage. It is not commited
    /// here, but is rather used by its parent parser when constructing
    /// an object, e.g. the subnet.
    virtual void commit() {
    }

    /// @brief factory that constructs StringParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* Factory(const std::string& param_name) {
        return (new StringParser(param_name));
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See \ref dhcpv6-config-inherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(StringStorage* storage) {
        storage_ = storage;
    }

protected:
    /// pointer to the storage, where parsed value will be stored
    StringStorage* storage_;

    /// name of the parameter to be parsed
    std::string param_name_;

    /// the actual parsed value
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
    InterfaceListConfigParser(const std::string& param_name) {
        if (param_name != "interface") {
            isc_throw(NotImplemented, "Internal error. Interface configuration "
                      "parser called for the wrong parameter: " << param_name);
        }
    }

    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of parameters) and stores it in
    /// storage. See \ref setStorage() for details.
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
    static DhcpConfigParser* Factory(const std::string& param_name) {
        return (new InterfaceListConfigParser(param_name));
    }

protected:
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
/// before build(). Otherwise exception will be thrown.
///
/// It is useful for parsing Dhcp6/subnet6[X]/pool parameters.
class PoolParser : public DhcpConfigParser {
public:

    /// @brief constructor.
    PoolParser(const std::string& /*param_name*/)
        :pools_(NULL) {
        // ignore parameter name, it is always Dhcp6/subnet6[X]/pool
    }

    /// @brief parses the actual list
    ///
    /// This method parses the actual list of interfaces.
    /// No validation is done at this stage, everything is interpreted as
    /// interface name.
    void build(ConstElementPtr pools_list) {
        // setStorage() should have been called before build
        if (!pools_) {
            isc_throw(NotImplemented, "Parser logic error. No pool storage set,"
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
                    // be checked in Pool6 constructor.
                    len = boost::lexical_cast<int>(prefix_len);
                } catch (...)  {
                    isc_throw(Dhcp6ConfigError, "Failed to parse pool "
                              "definition: " << text_pool->stringValue());
                }

                Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, addr, len));
                pools_->push_back(pool);
                continue;
            }

            // Is this min-max notation?
            pos = txt.find("-");
            if (pos != string::npos) {
                // using min-max notation
                IOAddress min(txt.substr(0,pos - 1));
                IOAddress max(txt.substr(pos + 1));

                Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, min, max));

                pools_->push_back(pool);
                continue;
            }

            isc_throw(Dhcp6ConfigError, "Failed to parse pool definition:"
                      << text_pool->stringValue() <<
                      ". Does not contain - (for min-max) nor / (prefix/len)");
        }
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See \ref dhcpv6-config-inherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(PoolStorage* storage) {
        pools_ = storage;
    }

    /// @brief does nothing.
    ///
    /// This method is required for all parser. The value itself
    /// is not commited anywhere. Higher level parsers (for subnet) are expected
    /// to use values stored in the storage.
    virtual void commit() {}

    /// @brief factory that constructs PoolParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* Factory(const std::string& param_name) {
        return (new PoolParser(param_name));
    }

protected:
    /// @brief pointer to the actual Pools storage
    ///
    /// That is typically a storage somewhere in Subnet parser
    /// (an upper level parser).
    PoolStorage* pools_;
};

/// @brief Parser for option data value.
///
/// This parser parses configuration entries that specify value of
/// a single option. These entries include option name, option code
/// and data carried by the option. If parsing is successful than
/// instance of an option is created and added to the storage provided
/// by the calling class.
class OptionDataParser : public DhcpConfigParser {
public:

    /// @brief Constructor.
    ///
    /// Class constructor.
    OptionDataParser(const std::string&)
        : options_(NULL) { }

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
                    name_parser(dynamic_cast<StringParser*>(StringParser::Factory(param.first)));
                if (name_parser) {
                    name_parser->setStorage(&string_values_);
                    parser = name_parser;
                }
            } else if (param.first == "code") {
                boost::shared_ptr<Uint32Parser>
                    code_parser(dynamic_cast<Uint32Parser*>(Uint32Parser::Factory(param.first)));
                if (code_parser) {
                    code_parser->setStorage(&uint32_values_);
                    parser = code_parser;
                }
            } else if (param.first == "data") {
                boost::shared_ptr<StringParser>
                    value_parser(dynamic_cast<StringParser*>(StringParser::Factory(param.first)));
                if (value_parser) {
                    value_parser->setStorage(&string_values_);
                    parser = value_parser;
                }
            } else {
                isc_throw(Dhcp6ConfigError,
                          "Parser error: option-data parameter not supported: "
                          << param.first);
            }
            parser->build(param.second);
        }
        // Try to create the option instance.
        createOption();
    }

    /// @brief Does nothing.
    ///
    /// This function does noting because option data is committed
    /// by a higher level parser.
    virtual void commit() { }

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
    /// are invalid or insufficient it emits exception.
    ///
    /// @warning this function does not check if options_ storage pointer
    /// is intitialized but this is not needed here because it is checked in
    /// \ref build function.
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
        // Check the option name has been specified, is non-empty and does not
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

        std::string option_data = getStringParam("data");
        std::vector<uint8_t> binary;
        try {
            util::encode::decodeHex(option_data, binary);
        } catch (...) {
            isc_throw(Dhcp6ConfigError, "Parser error: option data is not a valid"
                      << " string of hexadecimal digits: " << option_data);
        }

        // Create the actual option.
        // @todo Currently we simply create dhcp::Option instance here but we will
        // need to use dedicated factory functions once the option definitions are
        // created for all options.
        OptionPtr option(new Option(Option::V6, static_cast<uint16_t>(option_code),
                                    binary));

        // If option is created succesfully, add it to the storage.
        options_->push_back(option);
    }

    /// @brief Get a parameter from the strings storage.
    ///
    /// @param param_id parameter identifier.
    /// @throw Dhcp6ConfigError if parameter has not been found.
    std::string getStringParam(const std::string& param_id) const {
        StringStorage::const_iterator param = string_values_.find(param_id);
        if (param == string_values_.end()) {
            isc_throw(Dhcp6ConfigError, "Parser error: option-data parameter"
                      << " '" << param_id << "' not specified");
        }
        return (param->second);
    }

    /// @brief Get a parameter from the uint32 values storage.
    ///
    /// @param param_id parameter identifier.
    /// @throw Dhcp6ConfigError if parameter has not been found.
    uint32_t getUint32Param(const std::string& param_id) const {
        Uint32Storage::const_iterator param = uint32_values_.find(param_id);
        if (param == uint32_values_.end()) {
            isc_throw(Dhcp6ConfigError, "Parser error: option-data parameter"
                      << " '" << param_id << "' not specified");
        }
        return (param->second);
    }

    /// Storage for uint32 values (e.g. option code).
    Uint32Storage uint32_values_;
    /// Storage for string values (e.g. option name or data).
    StringStorage string_values_;
    /// Pointer to options storage. This storage is provided by
    /// the calling class and is shared by all OptionDataParser objects.
    OptionStorage* options_;
};

/// @brief Parser for option data values with ina subnet.
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
    /// a global option containers (option_default). That storage location
    /// is overriden on a subnet basis.
    OptionDataListParser(const std::string&)
        : options_(&option_defaults) { }

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
            parser->setStorage(options_);
            // Build the instance of a singkle option.
            parser->build(option_value);
        }
    }

    /// @brief Set storage for option instances.
    ///
    /// @param storage pointer to options storage.
    void setStorage(OptionStorage* storage) {
        options_ = storage;
    }


    /// @brief Does nothing.
    ///
    /// @todo Currently this function does nothing but in the future
    /// we may need to extend it to commit at this level.
    void commit() { }

    /// @brief Create DhcpDataListParser object
    ///
    /// @param param_name param name.
    ///
    /// @return DhcpConfigParser object.
    static DhcpConfigParser* Factory(const std::string& param_name) {
        return (new OptionDataListParser(param_name));
    }

    /// Pointer to options instances storage.
    OptionStorage* options_;
};

/// @brief this class parses a single subnet
///
/// This class parses the whole subnet definition. It creates parsers
/// for received configuration parameters as needed.
class Subnet6ConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    Subnet6ConfigParser(const std::string& ) {
        // The parameter should always be "subnet", but we don't check here
        // against it in case some wants to reuse this parser somewhere.
    }

    /// @brief parses parameter value
    ///
    /// @param subnet pointer to the content of subnet definition
    void build(ConstElementPtr subnet) {

        BOOST_FOREACH(ConfigPair param, subnet->mapValue()) {
            ParserPtr parser(createSubnet6ConfigParser(param.first));
            // The actual type of the parser is unknown here. We have to discover
            // parser type here to invoke corresponding setStorage function on it.
            // We discover parser type by trying to cast the parser to various
            // parser types and checking which one was successful. For this one
            // a setStorage and build methods are invoked.

            // Try uint32 type parser.
            if (buildParser<Uint32Parser, Uint32Storage >(parser, uint32_values_,
                                                          param.second)) {
                // Storage set, build invoked on the parser, proceed with
                // next configuration element.
                continue;
            }
            // Try string type parser.
            if (buildParser<StringParser, StringStorage >(parser, string_values_,
                                                          param.second)) {
                continue;
            }
            // Try pools parser.
            if (buildParser<PoolParser, PoolStorage >(parser, pools_,
                                                      param.second)) {
                continue;
            }
            // Try option data parser.
            if (buildParser<OptionDataListParser, OptionStorage >(parser, options_,
                                                                  param.second)) {
                continue;
            }
        }
        // Ok, we now have subnet parsed
    }

    /// @brief commits received configuration.
    ///
    /// This method does most of the configuration. Many other parsers are just
    /// storing the values that are actually consumed here. Pool definitions
    /// created in other parsers are used here and added to newly created Subnet6
    /// objects. Subnet6 are then added to DHCP CfgMgr.
    void commit() {

        StringStorage::const_iterator it = string_values_.find("subnet");
        if (it == string_values_.end()) {
            isc_throw(Dhcp6ConfigError,
                      "Mandatory subnet definition in subnet missing");
        }
        string subnet_txt = it->second;
        boost::erase_all(subnet_txt, " ");
        boost::erase_all(subnet_txt, "\t");

        size_t pos = subnet_txt.find("/");
        if (pos == string::npos) {
            isc_throw(Dhcp6ConfigError,
                      "Invalid subnet syntax (prefix/len expected):" << it->second);
        }
        IOAddress addr(subnet_txt.substr(0, pos));
        uint8_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

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

        Subnet6Ptr subnet(new Subnet6(addr, len, t1, t2, pref, valid));

        for (PoolStorage::iterator it = pools_.begin(); it != pools_.end(); ++it) {
            subnet->addPool6(*it);
        }

        // Add subnet specific options.
        BOOST_FOREACH(OptionPtr option, options_) {
            Subnet::OptionContainerTypeRange range =
                subnet->getOptions(option->getType());
            if (std::distance(range.first, range.second) > 0) {
                LOG_WARN(dhcp6_logger, DHCP6_CONFIG_OPTION_DUPLICATE)
                    .arg(option->getType()).arg(addr.toText());
            }
            subnet->addOption(option);
        }

        // Check all global options and add them to the subnet object if
        // they have been configured in the global scope. If they have been
        // configured in the subnet scope we don't add global option because
        // the one configured in the subnet scope always takes precedense.
        BOOST_FOREACH(OptionPtr option, option_defaults) {
            // Get all options specified locally in the subnet and having
            // code equal to global option's code.
            Subnet::OptionContainerTypeRange range =
                subnet->getOptions(option->getType());
            // @todo: In the future we will be searching for options using either
            // option code or namespace. Currently we have only the option
            // code available so if there is at least one option found with the
            // specific code we don't add globally configured option.
            // @todo with this code the first globally configured option
            // with the given code will be added to a subnet. We may
            // want to issue warning about dropping configuration of
            // global option if one already exsist.
            if (std::distance(range.first, range.second) == 0) {
                subnet->addOption(option);
            }
        }

        CfgMgr::instance().addSubnet6(subnet);
    }

private:

    /// @brief Set storage for a parser and invoke build.
    ///
    /// This helper method casts the provided parser pointer to specified
    /// type. If cast is successful it sets the corresponding storage for
    /// this parser, invokes build on it and save the parser.
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

    /// @brief creates parsers for entries in subnet definition
    ///
    /// @todo Add subnet-specific things here (e.g. subnet-specific options)
    ///
    /// @param config_id name od the entry
    /// @return parser object for specified entry name
    DhcpConfigParser* createSubnet6ConfigParser(const std::string& config_id) {
        FactoryMap factories;

        factories.insert(pair<string, ParserFactory*>(
                             "preferred-lifetime", Uint32Parser::Factory));
        factories.insert(pair<string, ParserFactory*>(
                             "valid-lifetime", Uint32Parser::Factory));
        factories.insert(pair<string, ParserFactory*>(
                             "renew-timer", Uint32Parser::Factory));
        factories.insert(pair<string, ParserFactory*>(
                             "rebind-timer", Uint32Parser::Factory));

        factories.insert(pair<string, ParserFactory*>(
                             "subnet", StringParser::Factory));

        factories.insert(pair<string, ParserFactory*>(
                             "pool", PoolParser::Factory));

        factories.insert(pair<string, ParserFactory*>(
                             "option-data", OptionDataListParser::Factory));


        FactoryMap::iterator f = factories.find(config_id);
        if (f == factories.end()) {
            // Used for debugging only.
            // return new DebugParser(config_id);

            isc_throw(NotImplemented,
                      "Parser error: Subnet6 parameter not supported: "
                      << config_id);
        }
        return (f->second(config_id));
    }

    /// @brief returns value for a given parameter (after using inheritance)
    ///
    /// This method implements inheritance. For a given parameter name, it first
    /// checks if there is a global value for it and overwrites it with specific
    /// value if such value was defined in subnet.
    ///
    /// @param name name of the parameter
    /// @return triplet with the parameter name
    Triplet<uint32_t> getParam(const std::string& name) {
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
            return (Triplet<uint32_t>(value));
        } else {
            isc_throw(Dhcp6ConfigError, "Mandatory parameter " << name
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
};

/// @brief this class parses list of subnets
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
    /// Iterates over all entries on the list and creates Subnet6ConfigParser
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
        CfgMgr::instance().deleteSubnets6();

        BOOST_FOREACH(ParserPtr subnet, subnets_) {
            subnet->commit();
        }

    }

    /// @brief Returns Subnet6ListConfigParser object
    /// @param param_name name of the parameter
    /// @return Subnets6ListConfigParser object
    static DhcpConfigParser* Factory(const std::string& param_name) {
        return (new Subnets6ListConfigParser(param_name));
    }

    /// @brief collection of subnet parsers.
    ParserCollection subnets_;
};

/// @brief creates global parsers
///
/// This method creates global parsers that parse global parameters, i.e.
/// those that take format of Dhcp6/param1, Dhcp6/param2 and so forth.
///
/// @param config_id pointer to received global configuration entry
/// @return parser for specified global DHCPv6 parameter
DhcpConfigParser* createGlobalDhcpConfigParser(const std::string& config_id) {
    FactoryMap factories;

    factories.insert(pair<string, ParserFactory*>(
                         "preferred-lifetime", Uint32Parser::Factory));
    factories.insert(pair<string, ParserFactory*>(
                         "valid-lifetime", Uint32Parser::Factory));
    factories.insert(pair<string, ParserFactory*>(
                         "renew-timer", Uint32Parser::Factory));
    factories.insert(pair<string, ParserFactory*>(
                         "rebind-timer", Uint32Parser::Factory));

    factories.insert(pair<string, ParserFactory*>(
                         "interface", InterfaceListConfigParser::Factory));
    factories.insert(pair<string, ParserFactory*>(
                         "subnet6", Subnets6ListConfigParser::Factory));

    factories.insert(pair<string, ParserFactory*>(
                         "option-data", OptionDataListParser::Factory));

    factories.insert(pair<string, ParserFactory*>(
                         "version", StringParser::Factory));

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

/// @brief configures DHCPv6 server
///
/// This function is called every time a new configuration is received. The extra
/// parameter is a reference to DHCPv6 server component. It is currently not used
/// and CfgMgr::instance() is accessed instead.
///
/// This method does not throw. It catches all exceptions and returns them as
/// reconfiguration statuses. It may return the following response codes:
/// 0 - configuration successful
/// 1 - malformed configuration (parsing failed)
/// 2 - logical error (parsing was successful, but the values are invalid)
///
/// @param config_set a new configuration for DHCPv6 server
/// @return answer that contains result of reconfiguration
ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& , ConstElementPtr config_set) {
    if (!config_set) {
        isc_throw(Dhcp6ConfigError,
                  "Null pointer is passed to configuration parser");
    }

    /// Reset global storage. Containers being reset below may contain
    /// data from the previous configuration attempts.
    option_defaults.clear();
    uint32_defaults.clear();
    string_defaults.clear();

    /// @todo: append most essential info here (like "2 new subnets configured")
    string config_details;

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_START).arg(config_set->str());

    ParserCollection parsers;
    try {
        BOOST_FOREACH(ConfigPair config_pair, config_set->mapValue()) {

            ParserPtr parser(createGlobalDhcpConfigParser(config_pair.first));
            parser->build(config_pair.second);
            parsers.push_back(parser);
        }
    } catch (const isc::Exception& ex) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Configuration parsing failed:") + ex.what());
        return (answer);
    } catch (...) {
        // for things like bad_cast in boost::lexical_cast
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Configuration parsing failed"));
    }

    try {
        BOOST_FOREACH(ParserPtr parser, parsers) {
            parser->commit();
        }
    }
    catch (const isc::Exception& ex) {
        ConstElementPtr answer = isc::config::createAnswer(2,
                                 string("Configuration commit failed:") + ex.what());
        return (answer);
    } catch (...) {
        // for things like bad_cast in boost::lexical_cast
        ConstElementPtr answer = isc::config::createAnswer(2,
                                 string("Configuration commit failed"));
    }

    LOG_INFO(dhcp6_logger, DHCP6_CONFIG_COMPLETE).arg(config_details);

    ConstElementPtr answer = isc::config::createAnswer(0, "Configuration commited.");
    return (answer);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
