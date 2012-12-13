// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfgmgr.h>
#include <dhcp4/config_parser.h>
#include <dhcp4/dhcp4_log.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <limits>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

/// @brief auxiliary type used for storing element name and its parser
typedef pair<string, ConstElementPtr> ConfigPair;

/// @brief a factory method that will create a parser for a given element name
typedef Dhcp4ConfigParser* ParserFactory(const std::string& config_id);

/// @brief a collection of factories that creates parsers for specified element names
typedef std::map<std::string, ParserFactory*> FactoryMap;

/// @brief a collection of pools
///
/// That type is used as intermediate storage, when pools are parsed, but there is
/// no subnet object created yet to store them.
typedef std::vector<Pool4Ptr> PoolStorage;

/// @brief Global uint32 parameters that will be used as defaults.
Uint32Storage uint32_defaults;

/// @brief global string parameters that will be used as defaults.
StringStorage string_defaults;

/// @brief a dummy configuration parser
///
/// It is a debugging parser. It does not configure anything,
/// will accept any configuration and will just print it out
/// on commit. Useful for debugging existing configurations and
/// adding new ones.
class DebugParser : public Dhcp4ConfigParser {
public:

    /// @brief Constructor
    ///
    /// See \ref Dhcp4ConfigParser class for details.
    ///
    /// @param param_name name of the parsed parameter
    DebugParser(const std::string& param_name)
        :param_name_(param_name) {
    }

    /// @brief builds parameter value
    ///
    /// See \ref Dhcp4ConfigParser class for details.
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
    /// See \ref Dhcp4ConfigParser class for details.
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
    static Dhcp4ConfigParser* Factory(const std::string& param_name) {
        return (new DebugParser(param_name));
    }

private:
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
/// in its base class, \ref Dhcp4ConfigParser.
///
/// For overview of usability of this generic purpose parser, see
/// \ref dhcpv4ConfigInherit page.
class Uint32Parser : public Dhcp4ConfigParser {
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
    /// @throw BadValue if supplied value could not be base to uint32_t
    virtual void build(ConstElementPtr value) {
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

        (*storage_)[param_name_] = value_;
    }

    /// @brief does nothing
    ///
    /// This method is required for all parsers. The value itself
    /// is not commited anywhere. Higher level parsers are expected to
    /// use values stored in the storage, e.g. renew-timer for a given
    /// subnet is stored in subnet-specific storage. It is not commited
    /// here, but is rather used by \ref Subnet4ConfigParser when constructing
    /// the subnet.
    virtual void commit() {
    }

    /// @brief factory that constructs Uint32Parser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static Dhcp4ConfigParser* Factory(const std::string& param_name) {
        return (new Uint32Parser(param_name));
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See \ref dhcpv4ConfigInherit for details.
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
/// in its base class, \ref Dhcp4ConfigParser.
///
/// For overview of usability of this generic purpose parser, see
/// \ref dhcpv4ConfigInherit page.
class StringParser : public Dhcp4ConfigParser {
public:

    /// @brief constructor for StringParser
    /// @param param_name name of the configuration parameter being parsed
    StringParser(const std::string& param_name)
        :storage_(&string_defaults), param_name_(param_name) {
    }

    /// @brief parses parameter value
    ///
    /// Parses configuration entry and stores it in storage. See
    /// \ref setStorage() for details.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(ConstElementPtr value) {
        value_ = value->str();
        boost::erase_all(value_, "\"");

        (*storage_)[param_name_] = value_;
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
    static Dhcp4ConfigParser* Factory(const std::string& param_name) {
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
class InterfaceListConfigParser : public Dhcp4ConfigParser {
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
    static Dhcp4ConfigParser* Factory(const std::string& param_name) {
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
class PoolParser : public Dhcp4ConfigParser {
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
    /// @throw Dhcp4ConfigError when pool parsing fails
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
                    isc_throw(Dhcp4ConfigError, "Failed to parse pool "
                              "definition: " << text_pool->stringValue());
                }

                Pool4Ptr pool(new Pool4(addr, len));
                pools_->push_back(pool);
                continue;
            }

            // Is this min-max notation?
            pos = txt.find("-");
            if (pos != string::npos) {
                // using min-max notation
                IOAddress min(txt.substr(0,pos));
                IOAddress max(txt.substr(pos + 1));

                Pool4Ptr pool(new Pool4(min, max));

                pools_->push_back(pool);
                continue;
            }

            isc_throw(Dhcp4ConfigError, "Failed to parse pool definition:"
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

    /// @brief does nothing.
    ///
    /// This method is required for all parsers. The value itself
    /// is not commited anywhere. Higher level parsers (for subnet) are expected
    /// to use values stored in the storage.
    virtual void commit() {}

    /// @brief factory that constructs PoolParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static Dhcp4ConfigParser* Factory(const std::string& param_name) {
        return (new PoolParser(param_name));
    }

private:
    /// @brief pointer to the actual Pools storage
    ///
    /// That is typically a storage somewhere in Subnet parser
    /// (an upper level parser).
    PoolStorage* pools_;
};

/// @brief this class parses a single subnet
///
/// This class parses the whole subnet definition. It creates parsers
/// for received configuration parameters as needed.
class Subnet4ConfigParser : public Dhcp4ConfigParser {
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

            // if this is an Uint32 parser, tell it to store the values
            // in values_, rather than in global storage
            boost::shared_ptr<Uint32Parser> uint_parser =
                boost::dynamic_pointer_cast<Uint32Parser>(parser);
            if (uint_parser) {
                uint_parser->setStorage(&uint32_values_);
            } else {

                boost::shared_ptr<StringParser> string_parser =
                    boost::dynamic_pointer_cast<StringParser>(parser);
                if (string_parser) {
                    string_parser->setStorage(&string_values_);
                } else {

                    boost::shared_ptr<PoolParser> pool_parser =
                        boost::dynamic_pointer_cast<PoolParser>(parser);
                    if (pool_parser) {
                        pool_parser->setStorage(&pools_);
                    }
                }
            }

            parser->build(param.second);
            parsers_.push_back(parser);
        }

        // Ok, we now have subnet parsed
    }

    /// @brief commits received configuration.
    ///
    /// This method does most of the configuration. Many other parsers are just
    /// storing the values that are actually consumed here. Pool definitions
    /// created in other parsers are used here and added to newly created Subnet4
    /// objects. Subnet4 are then added to DHCP CfgMgr.
    /// @throw Dhcp4ConfigError if there are any issues encountered during commit
    void commit() {

        StringStorage::const_iterator it = string_values_.find("subnet");
        if (it == string_values_.end()) {
            isc_throw(Dhcp4ConfigError,
                      "Mandatory subnet definition in subnet missing");
        }
        string subnet_txt = it->second;
        boost::erase_all(subnet_txt, " ");
        boost::erase_all(subnet_txt, "\t");

        size_t pos = subnet_txt.find("/");
        if (pos == string::npos) {
            isc_throw(Dhcp4ConfigError,
                      "Invalid subnet syntax (prefix/len expected):" << it->second);
        }
        IOAddress addr(subnet_txt.substr(0, pos));
        uint8_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

        Triplet<uint32_t> t1 = getParam("renew-timer");
        Triplet<uint32_t> t2 = getParam("rebind-timer");
        Triplet<uint32_t> valid = getParam("valid-lifetime");

        /// @todo: Convert this to logger once the parser is working reliably
        stringstream tmp;
        tmp << addr.toText() << "/" << (int)len
            << " with params t1=" << t1 << ", t2=" << t2 << ", valid=" << valid;

        LOG_INFO(dhcp4_logger, DHCP4_CONFIG_NEW_SUBNET).arg(tmp.str());

        Subnet4Ptr subnet(new Subnet4(addr, len, t1, t2, valid));

        for (PoolStorage::iterator it = pools_.begin(); it != pools_.end(); ++it) {
            subnet->addPool4(*it);
        }

        CfgMgr::instance().addSubnet4(subnet);
    }

private:

    /// @brief creates parsers for entries in subnet definition
    ///
    /// @todo Add subnet-specific things here (e.g. subnet-specific options)
    ///
    /// @param config_id name od the entry
    /// @return parser object for specified entry name
    /// @throw NotImplemented if trying to create a parser for unknown config element
    Dhcp4ConfigParser* createSubnet4ConfigParser(const std::string& config_id) {
        FactoryMap factories;

        factories["valid-lifetime"] = Uint32Parser::Factory;
        factories["renew-timer"] = Uint32Parser::Factory;
        factories["rebind-timer"] = Uint32Parser::Factory;
        factories["subnet"] = StringParser::Factory;
        factories["pool"] = PoolParser::Factory;

        FactoryMap::iterator f = factories.find(config_id);
        if (f == factories.end()) {
            // Used for debugging only.
            // return new DebugParser(config_id);

            isc_throw(NotImplemented,
                      "Parser error: Subnet4 parameter not supported: "
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
    /// @throw Dhcp4ConfigError when requested parameter is not present
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
            isc_throw(Dhcp4ConfigError, "Mandatory parameter " << name
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

    /// parsers are stored here
    ParserCollection parsers_;
};

/// @brief this class parses list of subnets
///
/// This is a wrapper parser that handles the whole list of Subnet4
/// definitions. It iterates over all entries and creates Subnet4ConfigParser
/// for each entry.
class Subnets4ListConfigParser : public Dhcp4ConfigParser {
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
    static Dhcp4ConfigParser* Factory(const std::string& param_name) {
        return (new Subnets4ListConfigParser(param_name));
    }

    /// @brief collection of subnet parsers.
    ParserCollection subnets_;
};

/// @brief creates global parsers
///
/// This method creates global parsers that parse global parameters, i.e.
/// those that take format of Dhcp4/param1, Dhcp4/param2 and so forth.
///
/// @param config_id pointer to received global configuration entry
/// @return parser for specified global DHCPv4 parameter
/// @throw NotImplemented if trying to create a parser for unknown config element
Dhcp4ConfigParser* createGlobalDhcp4ConfigParser(const std::string& config_id) {
    FactoryMap factories;

    factories["valid-lifetime"] = Uint32Parser::Factory;
    factories["renew-timer"] = Uint32Parser::Factory;
    factories["rebind-timer"] = Uint32Parser::Factory;
    factories["interface"] = InterfaceListConfigParser::Factory;
    factories["subnet4"] = Subnets4ListConfigParser::Factory;
    factories["version"] = StringParser::Factory;

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
configureDhcp4Server(Dhcpv4Srv& , ConstElementPtr config_set) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    /// @todo: append most essential info here (like "2 new subnets configured")
    string config_details;

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_START).arg(config_set->str());

    ParserCollection parsers;
    try {
        BOOST_FOREACH(ConfigPair config_pair, config_set->mapValue()) {

            ParserPtr parser(createGlobalDhcp4ConfigParser(config_pair.first));
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

    LOG_INFO(dhcp4_logger, DHCP4_CONFIG_COMPLETE).arg(config_details);

    ConstElementPtr answer = isc::config::createAnswer(0, "Configuration commited.");
    return (answer);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
