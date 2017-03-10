// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP_PARSERS_H
#define DHCP_PARSERS_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space_container.h>
#include <dhcpsrv/d2_client_cfg.h>
#include <dhcpsrv/cfg_iface.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <cc/simple_parser.h>
#include <exceptions/exceptions.h>
#include <util/optional_value.h>

#include <boost/shared_ptr.hpp>

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// Collection of containers holding option spaces. Each container within
/// a particular option space holds so-called option descriptors.
typedef OptionSpaceContainer<OptionContainer, OptionDescriptor,
                             std::string> OptionStorage;
/// @brief Shared pointer to option storage.
typedef boost::shared_ptr<OptionStorage> OptionStoragePtr;

/// @brief A template class that stores named elements of a given data type.
///
/// This template class is provides data value storage for configuration
/// parameters of a given data type.  The values are stored by parameter name
/// and as instances of type "ValueType". Each value held in the storage has
/// a corresponding position within a configuration string (file) specified
/// as a: file name, line number and position within the line. The position
/// information is used for logging when the particular configuration value
/// causes a configuration error.
///
/// @tparam ValueType is the data type of the elements to store.
template<typename ValueType>
class ValueStorage {
public:
    /// @brief  Stores the the parameter, its value and the position in the
    /// store.
    ///
    /// If the parameter does not exist in the store, then it will be added,
    /// otherwise its data value and the position will be updated with the
    /// given values.
    ///
    /// @param name is the name of the parameter to store.
    /// @param value is the data value to store.
    /// @param position is the position of the data element within a
    /// configuration string (file).
    void setParam(const std::string& name, const ValueType& value,
                  const data::Element::Position& position) {
        values_[name] = value;
        positions_[name] = position;
    }

    /// @brief Returns the data value for the given parameter.
    ///
    /// Finds and returns the data value for the given parameter.
    /// @param name is the name of the parameter for which the data
    /// value is desired.
    ///
    /// @return The parameter's data value of type @c ValueType.
    /// @throw DhcpConfigError if the parameter is not found.
    ValueType getParam(const std::string& name) const {
        typename std::map<std::string, ValueType>::const_iterator param
            = values_.find(name);

        if (param == values_.end()) {
            isc_throw(DhcpConfigError, "Missing parameter '"
                      << name << "'");
        }

        return (param->second);
    }

    /// @brief Returns position of the data element in the configuration string.
    ///
    /// The returned object comprises file name, line number and the position
    /// within the particular line of the configuration string where the data
    /// element holding a particular value is located.
    ///
    /// @param name is the name of the parameter which position is desired.
    /// @param parent Pointer to a data element which position should be
    /// returned when position of the specified parameter is not found.
    ///
    /// @return Position of the data element or the position holding empty
    /// file name and two zeros if the position hasn't been specified for the
    /// particular value.
    const data::Element::Position&
    getPosition(const std::string& name, const data::ConstElementPtr parent =
                data::ConstElementPtr()) const {
        typename std::map<std::string, data::Element::Position>::const_iterator
            pos = positions_.find(name);
        if (pos == positions_.end()) {
            return (parent ? parent->getPosition() :
                    data::Element::ZERO_POSITION());
        }

        return (pos->second);
    }

    /// @brief Returns the data value for an optional parameter.
    ///
    /// Finds and returns the data value for the given parameter or
    /// a supplied default value if it is not found.
    ///
    /// @param name is the name of the parameter for which the data
    /// value is desired.
    /// @param default_value value to use the default
    ///
    /// @return The parameter's data value of type @c ValueType.
    ValueType getOptionalParam(const std::string& name,
                               const ValueType& default_value) const {
        typename std::map<std::string, ValueType>::const_iterator param
            = values_.find(name);

        if (param == values_.end()) {
            return (default_value);
        }

        return (param->second);
    }

    /// @brief  Remove the parameter from the store.
    ///
    /// Deletes the entry for the given parameter from the store if it
    /// exists.
    ///
    /// @param name is the name of the parameter to delete.
    void delParam(const std::string& name) {
        values_.erase(name);
        positions_.erase(name);
    }

    /// @brief Deletes all of the entries from the store.
    ///
    void clear() {
        values_.clear();
        positions_.clear();
    }

private:
    /// @brief An std::map of the data values, keyed by parameter names.
    std::map<std::string, ValueType> values_;

    /// @brief An std::map holding positions of the data elements in the
    /// configuration, which values are held in @c values_.
    ///
    /// The position is used for logging, when the particular value
    /// causes a configuration error.
    std::map<std::string, data::Element::Position> positions_;

};


/// @brief a collection of elements that store uint32 values
typedef ValueStorage<uint32_t> Uint32Storage;
typedef boost::shared_ptr<Uint32Storage> Uint32StoragePtr;

/// @brief a collection of elements that store string values
typedef ValueStorage<std::string> StringStorage;
typedef boost::shared_ptr<StringStorage> StringStoragePtr;

/// @brief Storage for parsed boolean values.
typedef ValueStorage<bool> BooleanStorage;
typedef boost::shared_ptr<BooleanStorage> BooleanStoragePtr;

/// @brief Simple data-type parser template class
///
/// This is the template class for simple data-type parsers. It supports
/// parsing a configuration parameter with specific data-type for its
/// possible values. It provides a common constructor, commit, and templated
/// data storage.  The "build" method implementation must be provided by a
/// declaring type.
/// @param ValueType is the data type of the configuration parameter value
/// the parser should handle.
template<typename ValueType>
class ValueParser : public DhcpConfigParser {
public:

    /// @brief Constructor.
    ///
    /// @param param_name name of the parameter.
    /// @param storage is a pointer to the storage container where the parsed
    /// value be stored upon commit.
    /// @throw isc::dhcp::DhcpConfigError if a provided parameter's
    /// name is empty.
    /// @throw isc::dhcp::DhcpConfigError if storage is null.
    ValueParser(const std::string& param_name,
        boost::shared_ptr<ValueStorage<ValueType> > storage)
        : storage_(storage), param_name_(param_name), value_(), pos_() {
        // Empty parameter name is invalid.
        if (param_name_.empty()) {
            isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
                << "empty parameter name provided");
        }

        // Null storage is invalid.
        if (!storage_) {
            isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
                << "storage may not be NULL");
        }
    }

    /// @brief Parse a given element into a value of type @c ValueType
    ///
    /// @param value a value to be parsed.
    ///
    /// @throw isc::BadValue Typically the implementing type will throw
    /// a BadValue exception when given an invalid Element to parse.
    void build(isc::data::ConstElementPtr value);

    /// @brief Put a parsed value to the storage.
    void commit() {
        // If a given parameter already exists in the storage we override
        // its value. If it doesn't we insert a new element.
        storage_->setParam(param_name_, value_, pos_);
    }

private:

    /// @brief Performs operations common for all specializations of the
    /// @c build function.
    ///
    /// This method should be called by all specializations of the @c build
    /// method.
    ///
    /// @param value a value being parsed.
    void buildCommon(isc::data::ConstElementPtr value) {
        // Remember position of the data element.
        pos_ = value->getPosition();
    }

    /// Pointer to the storage where committed value is stored.
    boost::shared_ptr<ValueStorage<ValueType> > storage_;

    /// Name of the parameter which value is parsed with this parser.
    std::string param_name_;

    /// Parsed value.
    ValueType value_;

    data::Element::Position pos_;
};

/// @brief typedefs for simple data type parsers
typedef ValueParser<bool> BooleanParser;
typedef ValueParser<uint32_t> Uint32Parser;
typedef ValueParser<std::string> StringParser;

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

/// @brief parser for MAC/hardware acquisition sources
///
/// This parser handles Dhcp6/mac-sources entry.
/// It contains a list of MAC/hardware acquisition source, i.e. methods how
/// MAC address can possibly by obtained in DHCPv6. For a currently supported
/// methods, see @ref isc::dhcp::Pkt::getMAC.
class MACSourcesListConfigParser : public isc::data::SimpleParser {
public:
    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of sources) and adds each element
    /// to the sources list.
    ///
    /// @param value pointer to the content of parsed values
    /// @param mac_sources parsed sources will be stored here
    void parse(CfgMACSource& mac_sources, isc::data::ConstElementPtr value);
};

/// @brief Parser for the control-socket structure
///
/// It does not parse anything, simply stores the element in
/// the staging config.
class ControlSocketParser : public isc::data::SimpleParser {
public:
    /// @brief "Parses" control-socket structure
    ///
    /// Since the SrvConfig structure takes the socket definition
    /// as ConstElementPtr, there's really nothing to parse here.
    /// It only does basic sanity checks and throws DhcpConfigError
    /// if the value is null or is not a map.
    ///
    /// @param srv_cfg parsed values will be stored here
    /// @param value pointer to the content of parsed values
    void parse(SrvConfig& srv_cfg, isc::data::ConstElementPtr value);
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
class OptionDataParser : public isc::data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    explicit OptionDataParser(const uint16_t address_family);

    /// @brief Parses ElementPtr containing option definition
    ///
    /// This method parses ElementPtr containing the option definition,
    /// instantiates the option for it and then returns a pair
    /// of option descriptor (that holds that new option) and
    /// a string that specifies the option space.
    ///
    /// Note: ElementPtr is expected to contain all fields. If your
    /// ElementPtr does not have them, please use
    /// @ref isc::data::SimpleParser::setDefaults to fill the missing fields
    /// with default values.
    ///
    /// @param single_option ElementPtr containing option definition
    /// @return Option object wrapped in option description and an option
    ///         space
    std::pair<OptionDescriptor, std::string>
    parse(isc::data::ConstElementPtr single_option);
private:

    /// @brief Finds an option definition within an option space
    ///
    /// Given an option space and an option code, find the corresponding
    /// option definition within the option definition storage.
    ///
    /// @param option_space name of the parameter option space
    /// @param search_key an option code or name to be used to lookup the
    /// option definition.
    /// @tparam A numeric type for searching using an option code or the
    /// string for searching using the option name.
    ///
    /// @return OptionDefinitionPtr of the option definition or an
    /// empty OptionDefinitionPtr if not found.
    /// @throw DhcpConfigError if the option space requested is not valid
    /// for this server.
    template<typename SearchKey>
    OptionDefinitionPtr findOptionDefinition(const std::string& option_space,
                                             const SearchKey& search_key) const;

    /// @brief Create option instance.
    ///
    /// Creates an instance of an option and adds it to the provided
    /// options storage. If the option data parsed by \ref build function
    /// are invalid or insufficient this function emits an exception.
    ///
    /// @param option_data An element holding data for a single option being
    /// created.
    ///
    /// @return created option descriptor
    ///
    /// @throw DhcpConfigError if parameters provided in the configuration
    /// are invalid.
    std::pair<OptionDescriptor, std::string>
    createOption(isc::data::ConstElementPtr option_data);

    /// @brief Retrieves parsed option code as an optional value.
    ///
    /// @param parent A data element holding full option data configuration.
    ///
    /// @return Option code, possibly unspecified.
    /// @throw DhcpConfigError if option code is invalid.
    util::OptionalValue<uint32_t>
    extractCode(data::ConstElementPtr parent) const;

    /// @brief Retrieves parsed option name as an optional value.
    ///
    /// @param parent A data element holding full option data configuration.
    ///
    /// @return Option name, possibly unspecified.
    /// @throw DhcpConfigError if option name is invalid.
    util::OptionalValue<std::string>
    extractName(data::ConstElementPtr parent) const;

    /// @brief Retrieves csv-format parameter as an optional value.
    ///
    /// @return Value of the csv-format parameter, possibly unspecified.
    util::OptionalValue<bool> extractCSVFormat(data::ConstElementPtr parent) const;

    /// @brief Retrieves option data as a string.
    ///
    /// @param parent A data element holding full option data configuration.
    /// @return Option data as a string. It will return empty string if
    /// option data is unspecified.
    std::string extractData(data::ConstElementPtr parent) const;

    /// @brief Retrieves option space name.
    ///
    /// If option space name is not specified in the configuration the
    /// 'dhcp4' or 'dhcp6' option space name is returned, depending on
    /// the universe specified in the parser context.
    ///
    /// @param parent A data element holding full option data configuration.
    ///
    /// @return Option space name.
    std::string extractSpace(data::ConstElementPtr parent) const;

    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
};

/// @brief Parser for option data values within a subnet.
///
/// This parser iterates over all entries that define options
/// data for a particular subnet and creates a collection of options.
/// If parsing is successful, all these options are added to the Subnet
/// object.
class OptionDataListParser : public isc::data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or AF_INET6
    explicit OptionDataListParser(const uint16_t address_family);

    /// @brief Parses a list of options, instantiates them and stores in cfg
    ///
    /// This method expects to get a list of options in option_data_list,
    /// iterates over them, creates option objects, wraps them with
    /// option descriptor and stores in specified cfg.
    ///
    /// @param cfg created options will be stored here
    /// @param option_data_list configuration that describes the options
    void parse(const CfgOptionPtr& cfg,
               isc::data::ConstElementPtr option_data_list);
private:
    /// @brief Address family: @c AF_INET or @c AF_INET6
    uint16_t address_family_;
};

typedef std::pair<isc::dhcp::OptionDefinitionPtr, std::string> OptionDefinitionTuple;

/// @brief Parser for a single option definition.
///
/// This parser creates an instance of a single option definition.
class OptionDefParser : public isc::data::SimpleParser {
public:
    /// @brief Parses an entry that describes single option definition.
    ///
    /// @param option_def a configuration entry to be parsed.
    /// @return tuple (option definition, option space) of the parsed structure
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    OptionDefinitionTuple
    parse(isc::data::ConstElementPtr option_def);
};

/// @brief Parser for a list of option definitions.
///
/// This parser iterates over all configuration entries that define
/// option definitions and creates instances of these definitions.
/// If the parsing is successful, the collection of created definitions
/// is put into the provided storage.
class OptionDefListParser : public isc::data::SimpleParser {
public:
    /// @brief Parses a list of option definitions, create them and store in cfg
    ///
    /// This method iterates over def_list, which is a JSON list of option definitions,
    /// then creates corresponding option definitions and store them in the
    /// configuration structure.
    ///
    /// @param def_list JSON list describing option definitions
    /// @param cfg parsed option definitions will be stored here
    void parse(CfgOptionDefPtr cfg, isc::data::ConstElementPtr def_list);
};

/// @brief a collection of pools
///
/// That type is used as intermediate storage, when pools are parsed, but there is
/// no subnet object created yet to store them.
typedef std::vector<PoolPtr> PoolStorage;
typedef boost::shared_ptr<PoolStorage> PoolStoragePtr;

/// @brief parser for a single pool definition
///
/// This abstract parser handles pool definitions, i.e. a list of entries of one
/// of two syntaxes: min-max and prefix/len. Pool objects are created
/// and stored in chosen PoolStorage container.
///
/// It is useful for parsing Dhcp<4/6>/subnet<4/6>[X]/pools[X] structure.
class PoolParser : public isc::data::SimpleParser {
public:

    /// @brief destructor.
    virtual ~PoolParser() {
    }

    /// @brief parses the actual structure
    ///
    /// This method parses the actual list of interfaces.
    /// No validation is done at this stage, everything is interpreted as
    /// interface name.
    /// @param pools is the storage in which to store the parsed pool
    /// @param pool_structure a single entry on a list of pools
    /// @param address_family AF_INET (for DHCPv4) or AF_INET6 (for DHCPv6).
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    virtual void parse(PoolStoragePtr pools,
                       isc::data::ConstElementPtr pool_structure,
                       const uint16_t address_family);

protected:
    /// @brief Creates a Pool object given a IPv4 prefix and the prefix length.
    ///
    /// @param addr is the IP  prefix of the pool.
    /// @param len is the prefix length.
    /// @param ptype is the type of pool to create.
    /// @return returns a PoolPtr to the new Pool object.
    virtual PoolPtr poolMaker(isc::asiolink::IOAddress &addr, uint32_t len,
                              int32_t ptype = 0) = 0;

    /// @brief Creates a Pool object given starting and ending IP addresses.
    ///
    /// @param min is the first IP address in the pool.
    /// @param max is the last IP address in the pool.
    /// @param ptype is the type of pool to create (not used by all derivations)
    /// @return returns a PoolPtr to the new Pool object.
    virtual PoolPtr poolMaker(isc::asiolink::IOAddress &min,
                              isc::asiolink::IOAddress &max,
                              int32_t ptype = 0) = 0;
};

/// @brief Parser for a list of pools
///
/// This parser parses a list pools. Each element on that list gets its own
/// parser, created with poolParserMaker() method. That method must be specified
/// for each protocol family (v4 or v6) separately.
class PoolsListParser : public isc::data::SimpleParser {
public:

    /// @brief destructor.
    virtual ~PoolsListParser() {
    }

    /// @brief parses the actual structure
    ///
    /// This method parses the actual list of pools.
    ///
    /// @param pools is the storage in which to store the parsed pools.
    /// @param pools_list a list of pool structures
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    virtual void parse(PoolStoragePtr pools,
                       isc::data::ConstElementPtr pools_list) = 0;
};

/// @brief parser for additional relay information
///
/// This concrete parser handles RelayInfo structure definitions.
/// So far that structure holds only relay IP (v4 or v6) address, but it
/// is expected that the number of parameters will increase over time.
///
/// It is useful for parsing Dhcp<4/6>/subnet<4/6>[x]/relay parameters.
class RelayInfoParser : public isc::data::SimpleParser {
public:

    /// @brief constructor
    /// @param family specifies protocol family (IPv4 or IPv6)
    explicit RelayInfoParser(const isc::dhcp::Option::Universe& family);

    /// @brief parses the actual relay parameters
    ///
    /// The elements currently supported are:
    /// -# ip-address
    ///
    /// @param cfg configuration will be stored here
    /// @param relay_info JSON structure holding relay parameters to parse
    void parse(const isc::dhcp::Subnet::RelayInfoPtr& cfg,
               isc::data::ConstElementPtr relay_info);

private:

    /// @brief Returns a value converted to IOAddress
    ///
    /// Instantiation of getAndConvert() to IOAddress
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an IOAddress value
    isc::asiolink::IOAddress
    getIOAddress(isc::data::ConstElementPtr scope, const std::string& name);

    /// Protocol family (IPv4 or IPv6)
    Option::Universe family_;
};

/// @brief this class parses a single subnet
///
/// There are dedicated @ref Subnet4ConfigParser and @ref Subnet6ConfigParser
/// classes. They provide specialized parse() methods that return Subnet4Ptr
/// or Subnet6Ptr.
///
/// This class parses the whole subnet definition. This class attempts to
/// unify the code between v4 and v6 as much as possible. As a result, the flow
/// is somewhat complex and it looks as follows:
///
///     ------- Base class
///    /
///    | /----- Derived class
/// 1.   * SubnetXConfigParser::parse() is called.
/// 2. *   SubnetConfigParser::parse() is called.
/// 3. *   SubnetConfigParser::createSubnet() is called.
/// 4.   * SubnetXConfigParser::initSubnet() is called (Subnet4 or Subnet6 is
///        instantiated here and family specific parameters are set)
/// 5.     Control returns to createSubnet() (step 3) and common parameters
///        are set.

class SubnetConfigParser : public isc::data::SimpleParser {
public:

    /// @brief constructor
    ///
    /// @param family address family: @c AF_INET or @c AF_INET6
    explicit SubnetConfigParser(uint16_t family);

    /// @brief virtual destructor (does nothing)
    virtual ~SubnetConfigParser() { }

protected:
    /// @brief parses a subnet description and returns Subnet{4,6} structure
    ///
    /// This method is called from specialized (Subnet4ConfigParser or
    /// Subnet6ConfigParser) classes.
    ///
    /// @param subnet pointer to the content of subnet definition
    /// @return a pointer to newly created subnet
    ///
    /// @throw isc::DhcpConfigError if subnet configuration parsing failed.
    SubnetPtr parse(isc::data::ConstElementPtr subnet);

    /// @brief Instantiates the subnet based on a given IP prefix and prefix
    /// length.
    ///
    /// @param params configuration parameters for that subnet
    /// @param addr is the IP prefix of the subnet.
    /// @param len is the prefix length
    virtual void initSubnet(isc::data::ConstElementPtr params,
                            isc::asiolink::IOAddress addr, uint8_t len) = 0;

    /// @brief Attempts to convert text representation to HRMode enum.
    ///
    /// Allowed values are "disabled", "off" (alias for disabled),
    /// "out-of-pool" and "all". See Subnet::HRMode for their exact meaning.
    ///
    /// @param txt Host Reservation mode in the textual form.
    ///
    /// @throw BadValue if the text cannot be converted.
    ///
    /// @return one of allowed HRMode values
    static Subnet::HRMode hrModeFromText(const std::string& txt);

private:

    /// @brief Create a new subnet using a data from child parsers.
    ///
    /// @param data Element map that describes the subnet
    /// @throw isc::dhcp::DhcpConfigError if subnet configuration parsing
    /// failed.
    void createSubnet(isc::data::ConstElementPtr data);

protected:

    /// Storage for pools belonging to this subnet.
    PoolStoragePtr pools_;

    /// Pointer to the created subnet object.
    isc::dhcp::SubnetPtr subnet_;

    /// @brief Address family: @c AF_INET or @c AF_INET6
    uint16_t address_family_;

    /// Pointer to relay information
    isc::dhcp::Subnet::RelayInfoPtr relay_info_;

    /// Pointer to the options configuration.
    CfgOptionPtr options_;
};

/// @brief Parser for  D2ClientConfig
///
/// This class parses the configuration element "dhcp-ddns" common to the
/// config files for both dhcp4 and dhcp6. It creates an instance of a
/// D2ClientConfig.
class D2ClientConfigParser : public  isc::data::SimpleParser {
public:

    /// @brief Parses a given dhcp-ddns element into D2ClientConfig.
    ///
    /// @param d2_client_cfg is the "dhcp-ddns" configuration to parse
    ///
    /// The elements currently supported are (see isc::dhcp::D2ClientConfig
    /// for details on each):
    /// -# enable-updates
    /// -# qualifying-suffix
    /// -# server-ip
    /// -# server-port
    /// -# sender-ip
    /// -# sender-port
    /// -# max-queue-size
    /// -# ncr-protocol
    /// -# ncr-format
    /// -# always-include-fqdn
    /// -# override-no-update
    /// -# override-client-update
    /// -# replace-client-name
    /// -# generated-prefix
    ///
    /// @return returns a pointer to newly created D2ClientConfig.
    D2ClientConfigPtr parse(isc::data::ConstElementPtr d2_client_cfg);

    /// @brief Defaults for the D2 client configuration.
    static const isc::data::SimpleDefaults D2_CLIENT_CONFIG_DEFAULTS;

    /// @brief Sets all defaults for D2 client configuration.
    ///
    /// This method sets defaults value. It must not be called
    /// before the short cut disabled updates condition was checked.
    ///
    /// @param d2_config d2 client configuration (will be const cast
    //  to ElementPtr)
    /// @return number of parameters inserted
    static size_t setAllDefaults(isc::data::ConstElementPtr d2_config);

private:

    /// @brief Returns a value converted to IOAddress
    ///
    /// Instantiation of getAndConvert() to IOAddress
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an IOAddress value
    isc::asiolink::IOAddress
    getIOAddress(isc::data::ConstElementPtr scope, const std::string& name);

    /// @brief Returns a value converted to NameChangeProtocol
    ///
    /// Instantiation of getAndConvert() to NameChangeProtocol
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a NameChangeProtocol value
    dhcp_ddns::NameChangeProtocol
    getProtocol(isc::data::ConstElementPtr scope, const std::string& name);

    /// @brief Returns a value converted to NameChangeFormat
    ///
    /// Instantiation of getAndConvert() to NameChangeFormat
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a NameChangeFormat value
    dhcp_ddns::NameChangeFormat
    getFormat(isc::data::ConstElementPtr scope, const std::string& name);

    /// @brief Returns a value converted to ReplaceClientNameMode
    ///
    /// Instantiation of getAndConvert() to ReplaceClientNameMode
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a NameChangeFormat value
    D2ClientConfig::ReplaceClientNameMode
    getMode(isc::data::ConstElementPtr scope, const std::string& name);
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP_PARSERS_H
