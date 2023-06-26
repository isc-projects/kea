// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/network.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/parsers/base_network_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <cc/simple_parser.h>
#include <exceptions/exceptions.h>
#include <util/optional.h>

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
    /// @brief  Stores the parameter, its value and the position in the
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

/// @brief Combination of parameter name and configuration contents
typedef std::pair<std::string, isc::data::ConstElementPtr> ConfigPair;

/// @brief a collection of elements that store uint32 values
typedef ValueStorage<uint32_t> Uint32Storage;
typedef boost::shared_ptr<Uint32Storage> Uint32StoragePtr;

/// @brief a collection of elements that store string values
typedef ValueStorage<std::string> StringStorage;
typedef boost::shared_ptr<StringStorage> StringStoragePtr;

/// @brief Storage for parsed boolean values.
typedef ValueStorage<bool> BooleanStorage;
typedef boost::shared_ptr<BooleanStorage> BooleanStoragePtr;

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

/// @brief Parser for a single option definition.
///
/// This parser creates an instance of a single option definition.
class OptionDefParser : public isc::data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    OptionDefParser(const uint16_t address_family);

    /// @brief Parses an entry that describes single option definition.
    ///
    /// @param option_def a configuration entry to be parsed.
    /// @return option definition of the parsed structure.
    ///
    /// @throw DhcpConfigError if parsing was unsuccessful.
    OptionDefinitionPtr parse(isc::data::ConstElementPtr option_def);

private:
    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
};

/// @brief Parser for a list of option definitions.
///
/// This parser iterates over all configuration entries that define
/// option definitions and creates instances of these definitions.
/// If the parsing is successful, the collection of created definitions
/// is put into the provided storage.
class OptionDefListParser : public isc::data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    OptionDefListParser(const uint16_t address_family);

    /// @brief Parses a list of option definitions, create them and store in cfg
    ///
    /// This method iterates over def_list, which is a JSON list of option definitions,
    /// then creates corresponding option definitions and store them in the
    /// configuration structure.
    ///
    /// @param def_list JSON list describing option definitions
    /// @param cfg parsed option definitions will be stored here
    void parse(CfgOptionDefPtr cfg, isc::data::ConstElementPtr def_list);

private:
    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
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
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    virtual void parse(PoolStoragePtr pools,
                       isc::data::ConstElementPtr pool_structure,
                       const uint16_t address_family,
                       bool encapsulate_options = true);

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

    /// @brief Returns an instance of the @c OptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for option data.
    ///
    /// @param address_family AF_INET (for DHCPv4) or AF_INET6 (for DHCPv6).
    ///
    /// @return an instance of the @c OptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser(const uint16_t address_family) const;
};

/// @brief Parser for IPv4 pool definitions.
///
/// This is the IPv4 derivation of the PoolParser class and handles pool
/// definitions, i.e. a list of entries of one of two syntaxes: min-max and
/// prefix/len for IPv4 pools. Pool4 objects are created and stored in chosen
/// PoolStorage container.
///
/// It is useful for parsing Dhcp4/subnet4[X]/pool parameters.
class Pool4Parser : public PoolParser {
protected:
    /// @brief Creates a Pool4 object given a IPv4 prefix and the prefix length.
    ///
    /// @param addr is the IPv4 prefix of the pool.
    /// @param len is the prefix length.
    /// @param ignored dummy parameter to provide symmetry between the
    /// PoolParser derivations. The V6 derivation requires a third value.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (asiolink::IOAddress &addr, uint32_t len,
                       int32_t ignored);

    /// @brief Creates a Pool4 object given starting and ending IPv4 addresses.
    ///
    /// @param min is the first IPv4 address in the pool.
    /// @param max is the last IPv4 address in the pool.
    /// @param ignored dummy parameter to provide symmetry between the
    /// PoolParser derivations. The V6 derivation requires a third value.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (asiolink::IOAddress &min, asiolink::IOAddress &max,
                       int32_t ignored);
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
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    virtual void parse(PoolStoragePtr pools,
                       isc::data::ConstElementPtr pools_list,
                       bool encapsulate_options) = 0;

protected:

    /// @brief Returns an instance of the @c PoolParser to be used in
    /// parsing the address pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c PoolParser.
    virtual boost::shared_ptr<PoolParser> createPoolConfigParser() const = 0;
};

/// @brief Specialization of the pool list parser for DHCPv4
class Pools4ListParser : public PoolsListParser {
public:

    /// @brief parses the actual structure
    ///
    /// This method parses the actual list of pools.
    ///
    /// @param pools storage container in which to store the parsed pool.
    /// @param pools_list a list of pool structures
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    void parse(PoolStoragePtr pools, data::ConstElementPtr pools_list,
               bool encapsulate_options = true);

protected:

    /// @brief Returns an instance of the @c Pool4Parser to be used in
    /// parsing the address pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c Pool4Parser.
    virtual boost::shared_ptr<PoolParser> createPoolConfigParser() const;
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
    /// -# ip-addresses
    ///
    /// Note that ip-address and ip-addresses are mutually exclusive, with
    /// former being deprecated.  The use of ip-address will cause an debug
    /// log to be emitted, reminded users to switch.
    ///
    /// @param relay_info configuration will be stored here
    /// @param relay_elem Element tree containing the relay and its members
    /// @throw isc::dhcp::DhcpConfigError if both or neither of ip-address
    /// and ip-addresses are specified.
    void parse(const isc::dhcp::Network::RelayInfoPtr& relay_info,
               isc::data::ConstElementPtr relay_elem);

    /// @brief Attempts to add an IP address to list of relay addresses
    ///
    /// @param name name of the element supplying the address string, (either
    /// "ip-address" or "ip-addresses")
    /// @param address_str string form of the IP address to add
    /// @param relay_elem parent relay element (needed for position info)
    /// @param relay_info RelayInfo to which the address should be added
    /// @throw isc::dhcp::DhcpConfigError if the address string is not a valid
    /// IP address, is an address of the wrong family, or is already in the
    /// relay address list
    void addAddress(const std::string& name, const std::string& address_str,
                    isc::data::ConstElementPtr relay_elem,
                    const isc::dhcp::Network::RelayInfoPtr& relay_info);
private:

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
class SubnetConfigParser : public BaseNetworkParser {
public:

    /// @brief constructor
    ///
    /// @param family address family: @c AF_INET or @c AF_INET6
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    explicit SubnetConfigParser(uint16_t family, bool check_iface = true);

    /// @brief virtual destructor (does nothing)
    virtual ~SubnetConfigParser() { }

protected:
    /// @brief parses a subnet description and returns Subnet{4,6} structure
    ///
    /// This method is called from specialized (Subnet4ConfigParser or
    /// Subnet6ConfigParser) classes.
    ///
    /// @param subnet pointer to the content of subnet definition
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @return a pointer to newly created subnet
    ///
    /// @throw isc::DhcpConfigError if subnet configuration parsing failed.
    SubnetPtr parse(isc::data::ConstElementPtr subnet,
                    bool encapsulate_options);

    /// @brief Instantiates the subnet based on a given IP prefix and prefix
    /// length.
    ///
    /// @param params configuration parameters for that subnet
    /// @param addr is the IP prefix of the subnet.
    /// @param len is the prefix length
    virtual void initSubnet(isc::data::ConstElementPtr params,
                            isc::asiolink::IOAddress addr, uint8_t len) = 0;

protected:

    /// @brief Create a new subnet using a data from child parsers.
    ///
    /// @param data Element map that describes the subnet
    /// @throw isc::dhcp::DhcpConfigError if subnet configuration parsing
    /// failed.
    void createSubnet(isc::data::ConstElementPtr data);

    /// @brief Returns an instance of the @c OptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for option data.
    ///
    /// @return an instance of the @c OptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser> createOptionDataListParser() const;

    /// @brief Returns an instance of the @c PoolsListParser to be used
    /// in parsing the address pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c PoolsListParser.
    virtual boost::shared_ptr<PoolsListParser>
    createPoolsListParser() const = 0;

    /// Storage for pools belonging to this subnet.
    PoolStoragePtr pools_;

    /// Pointer to the created subnet object.
    isc::dhcp::SubnetPtr subnet_;

    /// @brief Address family: @c AF_INET or @c AF_INET6
    uint16_t address_family_;

    /// Pointer to relay information
    isc::dhcp::Network::RelayInfoPtr relay_info_;

    /// Check if the specified interface exists in the system.
    bool check_iface_;
};

/// @anchor Subnet4ConfigParser
/// @brief This class parses a single IPv4 subnet.
///
/// This is the IPv4 derivation of the SubnetConfigParser class and it parses
/// the whole subnet definition. It creates parsersfor received configuration
/// parameters as needed.
class Subnet4ConfigParser : public SubnetConfigParser {
public:
    /// @brief Constructor
    ///
    /// stores global scope parameters, options, option definitions.
    ///
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    Subnet4ConfigParser(bool check_iface = true);

    /// @brief Parses a single IPv4 subnet configuration and adds to the
    /// Configuration Manager.
    ///
    /// @param subnet A new subnet being configured.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @return a pointer to created Subnet4 object
    Subnet4Ptr parse(data::ConstElementPtr subnet,
                     bool encapsulate_options = true);

protected:

    /// @brief Instantiates the IPv4 Subnet based on a given IPv4 address
    /// and prefix length.
    ///
    /// @param params Data structure describing a subnet.
    /// @param addr is IPv4 address of the subnet.
    /// @param len is the prefix length
    void initSubnet(data::ConstElementPtr params,
                    asiolink::IOAddress addr, uint8_t len);

    /// @brief Verifies the host reservation address is in the subnet range
    ///
    /// @param subnet pointer to the subnet
    /// @param host pointer to the host reservation
    /// @throw DhcpConfigError when the address is not in the subnet range.
    void validateResv(const Subnet4Ptr& subnet, ConstHostPtr host);

    /// @brief Returns an instance of the @c Pools4ListParser to be used
    /// in parsing the address pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c Pools4ListParser.
    virtual boost::shared_ptr<PoolsListParser>
    createPoolsListParser() const;
};

/// @brief this class parses list of DHCP4 subnets
///
/// This is a wrapper parser that handles the whole list of Subnet4
/// definitions. It iterates over all entries and creates Subnet4ConfigParser
/// for each entry.
class Subnets4ListConfigParser : public isc::data::SimpleParser {
public:

    /// @brief constructor
    ///
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    Subnets4ListConfigParser(bool check_iface = true);

    /// @brief Virtual destructor.
    virtual ~Subnets4ListConfigParser() {
    }

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list, parses its content
    /// (by instantiating Subnet6ConfigParser) and adds to specified
    /// configuration.
    ///
    /// @param cfg Pointer to server configuration.
    /// @param subnets_list pointer to a list of IPv4 subnets
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @return number of subnets created
    size_t parse(SrvConfigPtr cfg, data::ConstElementPtr subnets_list,
                 bool encapsulate_options = true);

    /// @brief Parses contents of the subnet4 list.
    ///
    /// @param [out] subnets Container where parsed subnets will be stored.
    /// @param subnets_list pointer to a list of IPv4 subnets
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @return Number of subnets created.
    size_t parse(Subnet4Collection& subnets,
                 data::ConstElementPtr subnets_list,
                 bool encapsulate_options = true);

protected:

    /// @brief Returns an instance of the @c Subnet4ConfigParser to be
    /// used in parsing the subnets.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the subnets.
    ///
    /// @return an instance of the @c Subnet4ConfigParser.
    virtual boost::shared_ptr<Subnet4ConfigParser> createSubnetConfigParser() const;

    /// Check if the specified interface exists in the system.
    bool check_iface_;
};

/// @brief Parser for IPv6 pool definitions.
///
/// This is the IPv6 derivation of the PoolParser class and handles pool
/// definitions, i.e. a list of entries of one of two syntaxes: min-max and
/// prefix/len for IPv6 pools. Pool6 objects are created and stored in chosen
/// PoolStorage container.
///
/// It is useful for parsing Dhcp6/subnet6[X]/pool parameters.
class Pool6Parser : public PoolParser {
protected:
    /// @brief Creates a Pool6 object given a IPv6 prefix and the prefix length.
    ///
    /// @param addr is the IPv6 prefix of the pool.
    /// @param len is the prefix length.
    /// @param ptype is the type of IPv6 pool (Pool::PoolType). Note this is
    /// passed in as an int32_t and cast to PoolType to accommodate a
    /// polymorphic interface.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (asiolink::IOAddress &addr, uint32_t len, int32_t ptype);

    /// @brief Creates a Pool6 object given starting and ending IPv6 addresses.
    ///
    /// @param min is the first IPv6 address in the pool.
    /// @param max is the last IPv6 address in the pool.
    /// @param ptype is the type of IPv6 pool (Pool::PoolType). Note this is
    /// passed in as an int32_t and cast to PoolType to accommodate a
    /// polymorphic interface.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (asiolink::IOAddress &min, asiolink::IOAddress &max,
                       int32_t ptype);
};

/// @brief Specialization of the pool list parser for DHCPv6
class Pools6ListParser : public PoolsListParser {
public:

    /// @brief parses the actual structure
    ///
    /// This method parses the actual list of pools.
    ///
    /// @param pools storage container in which to store the parsed pool.
    /// @param pools_list a list of pool structures
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    void parse(PoolStoragePtr pools, data::ConstElementPtr pools_list,
               bool encapsulate_options = true);

protected:

    /// @brief Returns an instance of the @c Pool6Parser to be used in
    /// parsing the address pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c Pool6Parser.
    virtual boost::shared_ptr<PoolParser> createPoolConfigParser() const;
};

/// @brief Parser for IPv6 prefix delegation definitions.
///
/// This class handles prefix delegation pool definitions for IPv6 subnets
/// Pool6 objects are created and stored in the given PoolStorage container.
///
/// PdPool definitions currently support three elements: prefix, prefix-len,
/// and delegated-len, as shown in the example JSON text below:
///
/// @code
///
/// {
///     "prefix": "2001:db8:1::",
///     "prefix-len": 64,
///     "delegated-len": 128
/// }
/// @endcode
///
class PdPoolParser : public isc::data::SimpleParser {
public:

    /// @brief Constructor.
    ///
    PdPoolParser();

    /// @brief Virtual destructor.
    virtual ~PdPoolParser() {
    }

    /// @brief Builds a prefix delegation pool from the given configuration
    ///
    /// This function parses configuration entries and creates an instance
    /// of a dhcp::Pool6 configured for prefix delegation.
    ///
    /// @param pools storage container in which to store the parsed pool.
    /// @param pd_pool_ pointer to an element that holds configuration entries
    /// that define a prefix delegation pool.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    ///
    /// @throw DhcpConfigError if configuration parsing fails.
    void parse(PoolStoragePtr pools, data::ConstElementPtr pd_pool_,
               bool encapsulate_options = true);

protected:

    /// @brief Returns an instance of the @c OptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for option data.
    ///
    /// @return an instance of the @c OptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser() const;

    /// Pointer to the created pool object.
    isc::dhcp::Pool6Ptr pool_;

    /// @brief User context (optional, may be null)
    ///
    /// User context is arbitrary user data, to be used by hooks.
    isc::data::ConstElementPtr user_context_;

    /// @brief Client class (a client has to belong to to use this pd-pool)
    ///
    /// If null, everyone is allowed.
    isc::data::ConstElementPtr client_class_;
};

/// @brief Parser for a list of prefix delegation pools.
///
/// This parser iterates over a list of prefix delegation pool entries and
/// creates pool instances for each one. If the parsing is successful, the
/// collection of pools is committed to the provided storage.
class PdPoolsListParser : public isc::data::SimpleParser {
public:

    /// @brief Virtual destructor.
    virtual ~PdPoolsListParser() {
    }

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries and creates instances
    /// of prefix delegation pools .
    ///
    /// @param pools is the pool storage in which to store the parsed
    /// @param pd_pool_list pointer to an element that holds entries
    /// that define a prefix delegation pool.
    ///
    /// @throw DhcpConfigError if configuration parsing fails.
    void parse(PoolStoragePtr pools, data::ConstElementPtr pd_pool_list);

protected:

    /// @brief Returns an instance of the @c PdPoolParser to be used in
    /// parsing the prefix delegation pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c PdPool6Parser.
    virtual boost::shared_ptr<PdPoolParser>
    createPdPoolConfigParser() const;
};

/// @anchor Subnet6ConfigParser
/// @brief This class parses a single IPv6 subnet.
///
/// This is the IPv6 derivation of the SubnetConfigParser class and it parses
/// the whole subnet definition. It creates parsersfor received configuration
/// parameters as needed.
class Subnet6ConfigParser : public SubnetConfigParser {
public:

    /// @brief Constructor
    ///
    /// stores global scope parameters, options, option definitions.
    ///
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    Subnet6ConfigParser(bool check_iface = true);

    /// @brief Parses a single IPv6 subnet configuration and adds to the
    /// Configuration Manager.
    ///
    /// @param subnet A new subnet being configured.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @return a pointer to created Subnet6 object
    Subnet6Ptr parse(data::ConstElementPtr subnet,
                     bool encapsulate_options = true);

protected:
    /// @brief Issues a DHCP6 server specific warning regarding duplicate subnet
    /// options.
    ///
    /// @param code is the numeric option code of the duplicate option
    /// @param addr is the subnet address
    /// @todo A means to know the correct logger and perhaps a common
    /// message would allow this message to be emitted by the base class.
    virtual void duplicateOptionWarning(uint32_t code,
                                        asiolink::IOAddress& addr);

    /// @brief Instantiates the IPv6 Subnet based on a given IPv6 address
    /// and prefix length.
    ///
    /// @param params Data structure describing a subnet.
    /// @param addr is IPv6 prefix of the subnet.
    /// @param len is the prefix length
    void initSubnet(isc::data::ConstElementPtr params,
                    isc::asiolink::IOAddress addr, uint8_t len);

    /// @brief Verifies host reservation addresses are in the subnet range
    ///
    /// @param subnet pointer to the subnet
    /// @param host pointer to the host reservation
    /// @throw DhcpConfigError when an address is not in the subnet range.
    void validateResvs(const Subnet6Ptr& subnet, ConstHostPtr host);

    /// @brief Returns an instance of the @c Pools6ListParser to be used
    /// in parsing the address pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c Pools6ListParser.
    virtual boost::shared_ptr<PoolsListParser>
    createPoolsListParser() const;

    /// @brief Returns an instance of the @c PdPools6ListParser to be used
    /// in parsing the prefix delegation pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c PdPools6ListParser.
    virtual boost::shared_ptr<PdPoolsListParser>
    createPdPoolsListParser() const;
};


/// @brief this class parses a list of DHCP6 subnets
///
/// This is a wrapper parser that handles the whole list of Subnet6
/// definitions. It iterates over all entries and creates Subnet6ConfigParser
/// for each entry.
class Subnets6ListConfigParser : public isc::data::SimpleParser {
public:

    /// @brief constructor
    ///
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    Subnets6ListConfigParser(bool check_iface = true);

    /// @brief Virtual destructor.
    virtual ~Subnets6ListConfigParser() {
    }

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list, parses its content
    /// (by instantiating Subnet6ConfigParser) and adds to specified
    /// configuration.
    ///
    /// @param cfg configuration (parsed subnets will be stored here)
    /// @param subnets_list pointer to a list of IPv6 subnets
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    /// @throw DhcpConfigError if CfgMgr rejects the subnet (e.g. subnet-id is a duplicate)
    size_t parse(SrvConfigPtr cfg, data::ConstElementPtr subnets_list,
                 bool encapsulate_options = true);

    /// @brief Parses contents of the subnet6 list.
    ///
    /// @param [out] subnets Container where parsed subnets will be stored.
    /// @param subnets_list pointer to a list of IPv6 subnets
    /// @return Number of subnets created.
    size_t parse(Subnet6Collection& subnets,
                 data::ConstElementPtr subnets_list,
                 bool encapsulate_options = true);

protected:

    /// @brief Returns an instance of the @c Subnet6ConfigParser to be
    /// used in parsing the subnets.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the subnets.
    ///
    /// @return an instance of the @c Subnet6ConfigParser.
    virtual boost::shared_ptr<Subnet6ConfigParser> createSubnetConfigParser() const;

    /// Check if the specified interface exists in the system.
    bool check_iface_;
};

/// @brief Parser for D2ClientConfig
///
/// This class parses the configuration element "dhcp-ddns" common to the
/// config files for both dhcp4 and dhcp6. It creates an instance of a
/// D2ClientConfig.
class D2ClientConfigParser : public isc::data::SimpleParser {
public:

    /// @brief Parses a given dhcp-ddns element into D2ClientConfig.
    ///
    /// @param d2_client_cfg is the "dhcp-ddns" configuration to parse
    ///
    /// The elements currently supported are (see isc::dhcp::D2ClientConfig
    /// for details on each):
    /// -# enable-updates
    /// -# server-ip
    /// -# server-port
    /// -# sender-ip
    /// -# sender-port
    /// -# max-queue-size
    /// -# ncr-protocol
    /// -# ncr-format
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

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // DHCP_PARSERS_H
