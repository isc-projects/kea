// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

typedef boost::shared_ptr<Dhcp6ConfigParser> ParserPtr;
typedef pair<string, ConstElementPtr> ConfigPair;
typedef std::vector<ParserPtr> ParserCollection;
typedef Dhcp6ConfigParser* ParserFactory(const std::string& config_id);
typedef std::map<std::string, ParserFactory*> FactoryMap;
typedef std::map<string, uint32_t> Uint32Storage;
/// @brief That is a map with global parameters that will be used as defaults
Uint32Storage uint32_defaults;

typedef std::map<string, string> StringStorage;
StringStorage string_defaults;

typedef std::vector<Pool6Ptr> PoolStorage;

/// @brief a dummy configuration parser
///
/// It is a debugging parser. It does not configure anything,
/// will accept any configuration and will just print it out
/// on commit. Useful for debugging existing configurations and
/// adding new ones.
class DummyParser : public Dhcp6ConfigParser {
public:

    /// @brief Constructor
    ///
    /// See \ref Dhcp6ConfigParser class for details.
    ///
    /// @param param_name name of the parsed parameter
    DummyParser(const std::string& param_name)
        :param_name_(param_name) {
    }

    /// @brief builds parameter value
    ///
    /// See \ref Dhcp6ConfigParser class for details.
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
    /// See \ref Dhcp6ConfigParser class for details.
    virtual void commit() {
        // Debug message. The whole DummyParser class is used only for parser
        // debugging, and is not used in production code. It is very convenient
        // to keep it around. Please do not turn this cout into logger calls.
        std::cout << "Commit for token: [" << param_name_ << "] = ["
                  << value_->str() << "]" << std::endl;
    }

    /// @brief factory that constructs DummyParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static Dhcp6ConfigParser* Factory(const std::string& param_name) {
        return (new DummyParser(param_name));
    }

protected:
    /// name of the parsed parameter
    std::string param_name_;

    /// pointer to the actual value of the parameter
    ConstElementPtr value_;
};

/// @brief Configuration parser for uint32 types
///
/// This class is a generic parser that is able to handle any uint32 integer
/// type. By default it stores the value in external global container
/// (uint32_defaults). If used in smaller scopes (e.g. to parse parameters
/// in subnet config), it can be pointed to a different storage, using
/// setStorage() method. This class follows the parser interface, laid out
/// in its base class, \ref Dhcp6ConfigParser.

class Uint32Parser : public Dhcp6ConfigParser {
public:

    /// @brief constructor for Uint32Parser
    /// @param param_name name of the parameter that is going to be parsed
    Uint32Parser(const std::string& param_name)
        :storage_(&uint32_defaults), param_name_(param_name) {
    }

    /// @brief builds parameter value
    ///
    /// Parses configuration entry and stored it in storage. See
    /// \ref setStorage() for details.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(ConstElementPtr value) {
        try {
            value_ = boost::lexical_cast<uint32_t>(value->str());
        } catch (const boost::bad_lexical_cast &) {
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

    /// @brief factory that constructs DummyParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static Dhcp6ConfigParser* Factory(const std::string& param_name) {
        return (new Uint32Parser(param_name));
    }

    void setStorage(Uint32Storage* storage) {
        storage_ = storage;
    }

protected:
    Uint32Storage * storage_;
    std::string param_name_;
    uint32_t value_;
};

class StringParser : public Dhcp6ConfigParser {
public:
    StringParser(const std::string& param_name)
        :storage_(&string_defaults), param_name_(param_name) {
    }

    virtual void build(ConstElementPtr value) {
        value_ = value->str();
        boost::erase_all(value_, "\"");
        storage_->insert(pair<string, string>(param_name_, value_));
    }

    virtual void commit() {
    }

    static Dhcp6ConfigParser* Factory(const std::string& param_name) {
        return (new StringParser(param_name));
    }

    void setStorage(StringStorage * storage) {
        storage_ = storage;
    }

protected:
    StringStorage * storage_;
    std::string param_name_;
    std::string value_;
};

class InterfaceListConfigParser : public Dhcp6ConfigParser {
public:
    InterfaceListConfigParser(const std::string& param_name) {
        if (param_name != "interface") {
            isc_throw(NotImplemented, "Internal error. Interface configuration "
                      "parser called for the wrong parameter: " << param_name);
        }
    }
    virtual void build(ConstElementPtr value) {
        BOOST_FOREACH(ConstElementPtr iface, value->listValue()) {
            interfaces_.push_back(iface->str());
        }
    }

    virtual void commit() {
        /// @todo: Implement per interface listening. Currently always listening on all
        /// interfaces.
    }

    static Dhcp6ConfigParser* Factory(const std::string& param_name) {
        return (new InterfaceListConfigParser(param_name));
    }

protected:
    vector<string> interfaces_;
};

class PoolParser : public Dhcp6ConfigParser {
public:
    PoolParser(const std::string& /*param_name*/)
        :pools_(NULL) {
        // ignore parameter name, it is always Dhcp6/subnet6[X]/pool
    }
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

            // first let's remove any spaces or tabs
            boost::erase_all(txt, " ");
            boost::erase_all(txt, "\t");

            // Is this prefix/len notation?
            size_t pos = txt.find("/");
            if (pos != string::npos) {
                IOAddress addr("::");
                uint8_t len = 0;
                try {
                    addr = IOAddress(txt.substr(0, pos));
                    string num = txt.substr(pos+1);

                    // it is lexical cast to int and then downcast to uint8_t
                    // direct cast to uint8_t (which is really an unsigned char)
                    // will result in interpreting the first digit as output
                    // value and throwing exception if length written on two
                    // digits (because there are extra characters left over)
                    len = boost::lexical_cast<int>(num);
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
                IOAddress min(txt.substr(0,pos-1));
                IOAddress max(txt.substr(pos+1));

                Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, min, max));

                pools_->push_back(pool);
                continue;
            }

            isc_throw(Dhcp6ConfigError, "Failed to parse pool definition:"
                      << text_pool->stringValue() <<
                      ". Does not contain - (for min-max) nor / (prefix/len)");
        }
    }
    void setStorage(PoolStorage* storage) {
        pools_ = storage;
    }

    void commit() {}

    static Dhcp6ConfigParser* Factory(const std::string& param_name) {
        return (new PoolParser(param_name));
    }

protected:
    PoolStorage * pools_;

};

/// @brief this class parses a single subnet
class Subnet6ConfigParser : public Dhcp6ConfigParser {
public:
    Subnet6ConfigParser(const std::string& param_name) {
    }

    void build(ConstElementPtr subnet) {

        BOOST_FOREACH(ConfigPair param, subnet->mapValue()) {

            ParserPtr parser(createSubnet6ConfigParser(param.first));

            // if this is an Uint32 parser, tell it to store the values
            // in values_, rather than in global storage
            boost::shared_ptr<Uint32Parser> uintParser =
                boost::dynamic_pointer_cast<Uint32Parser>(parser);
            if (uintParser) {
                uintParser->setStorage(&uint32_values_);
            }

            boost::shared_ptr<StringParser> stringParser =
                boost::dynamic_pointer_cast<StringParser>(parser);
            if (stringParser) {
                stringParser->setStorage(&string_values_);
            }

            boost::shared_ptr<PoolParser> poolParser =
                boost::dynamic_pointer_cast<PoolParser>(parser);
            if (poolParser) {
                poolParser->setStorage(&pools_);
            }

            parser->build(param.second);
            parsers_.push_back(parser);
        }

        // Ok, we now have subnet parsed
    }

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

        CfgMgr::instance().addSubnet6(subnet);
    }

protected:
    Dhcp6ConfigParser* createSubnet6ConfigParser(const std::string& config_id) {
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

        FactoryMap::iterator f = factories.find(config_id);
        if (f == factories.end()) {
            // Used for debugging only.
            // return new DummyParser(config_id);

            isc_throw(NotImplemented,
                      "Parser error: Subnet6 parameter not supported: "
                      << config_id);
        }
        return (f->second(config_id));
    }

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

    Uint32Storage uint32_values_;
    StringStorage string_values_;
    PoolStorage pools_;
    ParserCollection parsers_;
};

/// @brief this class parses list of subnets
class Subnets6ListConfigParser : public Dhcp6ConfigParser {
public:
    Subnets6ListConfigParser(const std::string& param_name) {
    }

    void build(ConstElementPtr subnets_list) {

        // No need to define FactoryMap here. There's only one type
        // used: Subnet6ConfigParser

        BOOST_FOREACH(ConstElementPtr subnet, subnets_list->listValue()) {

            ParserPtr parser(new Subnet6ConfigParser("subnet"));
            parser->build(subnet);
            subnets_.push_back(parser);
        }

    }

    void commit() {
        // @todo: Implement more subtle reconfiguration than toss
        // the old one and replace with the new one.

        // remove old subnets
        CfgMgr::instance().deleteSubnets6();

        BOOST_FOREACH(ParserPtr subnet, subnets_) {
            subnet->commit();
        }

    }

    static Dhcp6ConfigParser* Factory(const std::string& param_name) {
        return (new Subnets6ListConfigParser(param_name));
    }

    ParserCollection subnets_;
};

/// @brief creates global parsers
///
/// This method creates global parsers that parse global parameters, i.e.
/// those that take format of Dhcp6/param1, Dhcp6/param2 and so forth.
Dhcp6ConfigParser* createGlobalDhcp6ConfigParser(const std::string& config_id) {
    FactoryMap factories;

    //
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
                         "version", StringParser::Factory));

    FactoryMap::iterator f = factories.find(config_id);
    if (f == factories.end()) {
        // Used for debugging only.
        // return new DummyParser(config_id);

        isc_throw(NotImplemented,
                  "Parser error: Global configuration parameter not supported: "
                  << config_id);
    }
    return (f->second(config_id));
}

ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& , ConstElementPtr config_set) {
    if (!config_set) {
        isc_throw(Dhcp6ConfigError,
                  "Null pointer is passed to configuration parser");
    }

    /// @todo: append most essential info here (like "2 new subnets configured")
    string config_details;

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_START).arg(config_set->str());

    ParserCollection parsers;
    try {
        BOOST_FOREACH(ConfigPair config_pair, config_set->mapValue()) {

            ParserPtr parser(createGlobalDhcp6ConfigParser(config_pair.first));
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
