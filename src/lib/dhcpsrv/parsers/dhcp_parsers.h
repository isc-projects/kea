// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space_container.h>
#include <dhcpsrv/d2_client_cfg.h>
#include <dhcpsrv/cfg_iface.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
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

/// @brief Shared pointer to collection of hooks libraries.
typedef boost::shared_ptr<std::vector<std::string> > HooksLibsStoragePtr;

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
    /// @param name is the name of the paramater to store.
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
    /// @return The paramater's data value of type @c ValueType.
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
    /// @return The paramater's data value of type @c ValueType.
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
    /// @param name is the name of the paramater to delete.
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

/// @brief Container for the current parsing context. It provides a
/// single enclosure for the storage of configuration parameters,
/// options, option definitions, and other context specific information
/// that needs to be accessible throughout the parsing and parsing
/// constructs.
class ParserContext {
public:
    /// @brief Constructor
    ///
    /// @param universe is the Option::Universe value of this
    /// context.
    ParserContext(Option::Universe universe);

    /// @brief Copy constructor
    ParserContext(const ParserContext& rhs);

    /// @brief Storage for boolean parameters.
    BooleanStoragePtr boolean_values_;

    /// @brief Storage for uint32 parameters.
    Uint32StoragePtr uint32_values_;

    /// @brief Storage for string parameters.
    StringStoragePtr string_values_;

    /// @brief Hooks libraries pointer.
    ///
    /// The hooks libraries information is a vector of strings, each containing
    /// the name of a library.  Hooks libraries should only be reloaded if the
    /// list of names has changed, so the list of current DHCP parameters
    /// (in isc::dhcp::CfgMgr) contains an indication as to whether the list has
    /// altered.  This indication is implemented by storing a pointer to the
    /// list of library names which is cleared when the libraries are loaded.
    /// So either the pointer is null (meaning don't reload the libraries and
    /// the list of current names can be obtained from the HooksManager) or it
    /// is non-null (this is the new list of names, reload the libraries when
    /// possible).
    HooksLibsStoragePtr hooks_libraries_;

    /// @brief The parsing universe of this context.
    Option::Universe universe_;

    /// @brief Assignment operator
    ParserContext& operator=(const ParserContext& rhs);

    /// @brief Copy the context fields.
    ///
    /// This class method initializes the context data by copying the data
    /// stored in the context instance provided as an argument. Note that
    /// this function will also handle copying the NULL pointers.
    ///
    /// @param ctx context to be copied.
    void copyContext(const ParserContext& ctx);

    template<typename T>
    void copyContextPointer(const boost::shared_ptr<T>& source_ptr,
                            boost::shared_ptr<T>& dest_ptr);
};

/// @brief Pointer to various parser context.
typedef boost::shared_ptr<ParserContext> ParserContextPtr;

/// @brief Simple data-type parser template class
///
/// This is the template class for simple data-type parsers. It supports
/// parsing a configuration parameter with specific data-type for its
/// possible values. It provides a common constructor, commit, and templated
/// data storage.  The "build" method implementation must be provided by a
/// declaring type.
/// @param ValueType is the data type of the configuration paramater value
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

        // NUll storage is invalid.
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

/// @brief parser for MAC/hardware aquisition sources
///
/// This parser handles Dhcp6/mac-sources entry.
/// It contains a list of MAC/hardware aquisition source, i.e. methods how
/// MAC address can possibly by obtained in DHCPv6. For a currently supported
/// methods, see @ref isc::dhcp::Pkt::getMAC.
class MACSourcesListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    /// As this is a dedicated parser, it must be used to parse
    /// "mac-sources" parameter only. All other types will throw exception.
    ///
    /// @param param_name name of the configuration parameter being parsed
    /// @param global_context Global parser context.
    /// @throw BadValue if supplied parameter name is not "mac-sources"
    MACSourcesListConfigParser(const std::string& param_name,
                               ParserContextPtr global_context);

    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of sources) and adds each element
    /// to the sources list.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Does nothing.
    virtual void commit();

private:

    // Parsed parameter name
    std::string param_name_;

    /// Global parser context.
    ParserContextPtr global_context_;
};

/// @brief Parser for the control-socket structure
///
/// It does not parse anything, simply stores the element in
/// the staging config.
class ControlSocketParser : public DhcpConfigParser {
public:

    ControlSocketParser(const std::string& param_name);

    /// @brief Stores contents of the control-socket map in the staging config.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Does nothing.
    virtual void commit();
};

/// @brief Parser for hooks library list
///
/// This parser handles the list of hooks libraries.  This is an optional list,
/// which may be empty.
///
/// However, the parser does more than just check the list of library names.
/// It does two other things:
///
/// -# The problem faced with the hooks libraries is that we wish to avoid
/// reloading the libraries if they have not changed.  (This would cause the
/// "unload" and "load" methods to run.  Although libraries should be written
/// to cope with this, it is feasible that such an action may be constly in
/// terms of time and resources, or may cause side effects such as clearning
/// an internal cache.)  To this end, the parser also checks the list against
/// the list of libraries current loaded and notes if there are changes.
/// -# If there are, the parser validates the libraries; it opens them and
/// checks that the "version" function exists and returns the correct value.
///
/// Only if the library list has changed and the libraries are valid will the
/// change be applied.
class HooksLibrariesParser : public DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// As this is a dedicated parser, it must be used to parse
    /// "hooks-libraries" parameter only. All other types will throw exception.
    ///
    /// @param param_name name of the configuration parameter being parsed.
    ///
    /// @throw BadValue if supplied parameter name is not "hooks-libraries"
    HooksLibrariesParser(const std::string& param_name);

    /// @brief Parses parameters value
    ///
    /// Parses configuration entry (list of parameters) and adds each element
    /// to the hooks libraries list.  The  method also checks whether the
    /// list of libraries is the same as that already loaded.  If not, it
    /// checks each of the libraries in the list for validity (they exist and
    /// have a "version" function that returns the correct value).
    ///
    /// The syntax for specifying hooks libraries allow for library-specific
    /// parameters to be specified along with the library, e.g.
    ///
    /// @code
    ///      "hooks-libraries": [
    ///          {
    ///              "library": "hook-lib-1.so",
    ///              "parameters": {
    ///                  "alpha": "a string",
    ///                  "beta": 42
    ///              }
    ///          },
    ///          :
    ///      ]
    /// @endcode
    ///
    /// As Kea has not yet implemented parameters, the parsing code only checks
    /// that:
    ///
    /// -# Each element in the hooks-libraries list is a map
    /// -# The map contains an element "library" whose value is a string: all
    ///    other elements in the map are ignored.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Commits hooks libraries data
    ///
    /// Providing that the specified libraries are valid and are different
    /// to those already loaded, this method loads the new set of libraries
    /// (and unloads the existing set).
    virtual void commit();

    /// @brief Returns list of parsed libraries
    ///
    /// Principally for testing, this returns the list of libraries as well as
    /// an indication as to whether the list is different from the list of
    /// libraries already loaded.
    ///
    /// @param [out] libraries List of libraries that were specified in the
    ///        new configuration.
    /// @param [out] changed true if the list is different from that currently
    ///        loaded.
    void getLibraries(std::vector<std::string>& libraries, bool& changed);

private:
    /// List of hooks libraries.
    std::vector<std::string> libraries_;

    /// Indicator flagging that the list of libraries has changed.
    bool changed_;
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
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param [out] cfg Pointer to the configuration object where parsed option
    /// should be stored or NULL if this is a global option.
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    /// @throw isc::dhcp::DhcpConfigError if options or global_context are null.
    OptionDataParser(const std::string& dummy, const CfgOptionPtr& cfg,
                     const uint16_t address_family);

    /// @brief Parses the single option data.
    ///
    /// This method parses the data of a single option from the configuration.
    /// The option data includes option name, option code and data being
    /// carried by this option. Eventually it creates the instance of the
    /// option and adds it to the Configuration Manager.
    ///
    /// @param option_data_entries collection of entries that define value
    /// for a particular option.
    /// @throw DhcpConfigError if invalid parameter specified in
    /// the configuration.
    /// @throw isc::InvalidOperation if failed to set storage prior to
    /// calling build.
    virtual void build(isc::data::ConstElementPtr option_data_entries);

    /// @brief Does nothing.
    virtual void commit();

    /// @brief virtual destructor to ensure orderly destruction of derivations.
    virtual ~OptionDataParser(){};
private:

    /// @brief Finds an option definition within an option space
    ///
    /// Given an option space and an option code, find the correpsonding
    /// option defintion within the option defintion storage.
    ///
    /// @param option_space name of the parameter option space
    /// @param search_key an option code or name to be used to lookup the
    /// option definition.
    /// @tparam A numeric type for searching using an option code or the
    /// string for searching using the option name.
    ///
    /// @return OptionDefintionPtr of the option defintion or an
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
    /// @warning this function does not check if options_ storage pointer
    /// is intitialized but this check is not needed here because it is done
    /// in the \ref build function.
    ///
    /// @param option_data An element holding data for a single option being
    /// created.
    ///
    /// @throw DhcpConfigError if parameters provided in the configuration
    /// are invalid.
    void createOption(isc::data::ConstElementPtr option_data);

    /// @brief Retrieves parsed option code as an optional value.
    ///
    /// @param parent A data element holding full option data configuration.
    /// It is used here to log a position if the element holding a code
    /// is not specified and its position is therefore unavailable.
    ///
    /// @return Option code, possibly unspecified.
    /// @throw DhcpConfigError if option code is invalid.
    util::OptionalValue<uint32_t>
    extractCode(data::ConstElementPtr parent) const;

    /// @brief Retrieves parsed option name as an optional value.
    ///
    /// @param parent A data element holding full option data configuration.
    /// It is used here to log a position if the element holding a name
    /// is not specified and its position is therefore unavailable.
    ///
    /// @return Option name, possibly unspecified.
    /// @throw DhcpConfigError if option name is invalid.
    util::OptionalValue<std::string>
    extractName(data::ConstElementPtr parent) const;

    /// @brief Retrieves csv-format parameter as an optional value.
    ///
    /// @return Value of the csv-format parameter, possibly unspecified.
    util::OptionalValue<bool> extractCSVFormat() const;

    /// @brief Retrieves option data as a string.
    ///
    /// @return Option data as a string. It will return empty string if
    /// option data is unspecified.
    std::string extractData() const;

    /// @brief Retrieves option space name.
    ///
    /// If option space name is not specified in the configuration the
    /// 'dhcp4' or 'dhcp6' option space name is returned, depending on
    /// the universe specified in the parser context.
    ///
    /// @return Option space name.
    std::string extractSpace() const;

    /// Storage for boolean values.
    BooleanStoragePtr boolean_values_;

    /// Storage for string values (e.g. option name or data).
    StringStoragePtr string_values_;

    /// Storage for uint32 values (e.g. option code).
    Uint32StoragePtr uint32_values_;

    /// Option descriptor holds newly configured option.
    OptionDescriptor option_descriptor_;

    /// Option space name where the option belongs to.
    std::string option_space_;

    /// @brief Configuration holding option being parsed or NULL if the option
    /// is global.
    CfgOptionPtr cfg_;

    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
};

///@brief Function pointer for OptionDataParser factory methods
typedef OptionDataParser *OptionDataParserFactory(const std::string&,
                     OptionStoragePtr options, ParserContextPtr global_context);

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
    /// @param dummy nominally would be param name, this is always ignored.
    /// @param [out] cfg Pointer to the configuration object where options
    /// should be stored or NULL if this is global option scope.
    /// @param address_family Address family: @c AF_INET or AF_INET6
    OptionDataListParser(const std::string& dummy, const CfgOptionPtr& cfg,
                         const uint16_t address_family);

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
    /// This function invokes commit for all option values
    /// and append suboptions to the top-level options.
    void commit();

private:

    /// Collection of parsers;
    ParserCollection parsers_;

    /// @brief Pointer to a configuration where options are stored.
    CfgOptionPtr cfg_;

    /// @brief Address family: @c AF_INET or @c AF_INET6
    uint16_t address_family_;

};

typedef boost::shared_ptr<OptionDataListParser> OptionDataListParserPtr;


/// @brief Parser for a single option definition.
///
/// This parser creates an instance of a single option definition.
class OptionDefParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    OptionDefParser(const std::string& dummy, ParserContextPtr global_context);

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
    ///
    /// @param option_def_element A data element holding the configuration
    /// for an option definition.
    void createOptionDef(isc::data::ConstElementPtr option_def_element);

    /// Instance of option definition being created by this parser.
    OptionDefinitionPtr option_definition_;

    /// Name of the space the option definition belongs to.
    std::string option_space_name_;

    /// Storage for boolean values.
    BooleanStoragePtr boolean_values_;

    /// Storage for string values.
    StringStoragePtr string_values_;

    /// Storage for uint32 values.
    Uint32StoragePtr uint32_values_;

    /// Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;
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
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    OptionDefListParser(const std::string& dummy,
                        ParserContextPtr global_context);

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries, creates instances
    /// of option definitions and tries to add them to the Configuration
    /// Manager.
    ///
    /// @param option_def_list pointer to an element that holds entries
    /// that define option definitions.
    /// @throw DhcpConfigError if configuration parsing fails.
    void build(isc::data::ConstElementPtr option_def_list);

    /// @brief Commits option definitions.
    ///
    /// Currently this function is no-op, because option definitions are
    /// added to the Configuration Manager in the @c build method.
    void commit();

    /// Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;
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
class PoolParser : public DhcpConfigParser {
public:

    /// @brief constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param pools is the storage in which to store the parsed pool
    /// upon "commit".
    /// @throw isc::dhcp::DhcpConfigError if storage is null.
    PoolParser(const std::string& dummy, PoolStoragePtr pools);

    /// @brief parses the actual structure
    ///
    /// This method parses the actual list of interfaces.
    /// No validation is done at this stage, everything is interpreted as
    /// interface name.
    /// @param pool_structure a single entry on a list of pools
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    virtual void build(isc::data::ConstElementPtr pool_structure);

    /// @brief Stores the parsed values in a storage provided
    ///        by an upper level parser.
    virtual void commit();

protected:
    /// @brief Creates a Pool object given a IPv4 prefix and the prefix length.
    ///
    /// @param addr is the IP  prefix of the pool.
    /// @param len is the prefix length.
    /// @param ptype is the type of pool to create.
    /// @return returns a PoolPtr to the new Pool object.
    virtual PoolPtr poolMaker(isc::asiolink::IOAddress &addr, uint32_t len,
                           int32_t ptype=0) = 0;

    /// @brief Creates a Pool object given starting and ending IP addresses.
    ///
    /// @param min is the first IP address in the pool.
    /// @param max is the last IP address in the pool.
    /// @param ptype is the type of pool to create (not used by all derivations)
    /// @return returns a PoolPtr to the new Pool object.
    virtual PoolPtr poolMaker(isc::asiolink::IOAddress &min,
                           isc::asiolink::IOAddress &max, int32_t ptype=0) = 0;

    /// @brief pointer to the actual Pools storage
    ///
    /// That is typically a storage somewhere in Subnet parser
    /// (an upper level parser).
    PoolStoragePtr pools_;

    /// A temporary storage for pools configuration. It is a
    /// storage where pools are stored by build function.
    PoolStorage local_pools_;
};

/// @brief Parser for a list of pools
///
/// This parser parses a list pools. Each element on that list gets its own
/// parser, created with poolParserMaker() method. That method must be specified
/// for each protocol family (v4 or v6) separately.
///
/// This class is not intended to be used directly. Instead, derived classes
/// should implement poolParserMaker() method.
class PoolsListParser :  public DhcpConfigParser {
public:

    /// @brief constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept a string as the first argument.
    /// @param pools is the storage in which to store the parsed pool
    /// upon "commit".
    /// @throw isc::dhcp::DhcpConfigError if storage is null.
    PoolsListParser(const std::string& dummy, PoolStoragePtr pools);

    /// @brief parses the actual structure
    ///
    /// This method parses the actual list of pools. It creates a parser
    /// for each structure using poolParserMaker().
    ///
    /// @param pools_list a list of pool structures
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    virtual void build(isc::data::ConstElementPtr pools_list);

    /// @brief Stores the parsed values in storage provided
    ///        by an upper level parser.
    virtual void commit();

protected:

    /// @brief Creates a PoolParser object
    ///
    /// Instantiates appropriate (v4 or v6) PoolParser object.
    /// @param storage parameter that is passed to ParserMaker() constructor.
    virtual ParserPtr poolParserMaker(PoolStoragePtr storage) = 0;

    /// @brief pointer to the actual Pools storage
    ///
    /// That is typically a storage somewhere in Subnet parser
    /// (an upper level parser).
    PoolStoragePtr pools_;

    /// A temporary storage for pools configuration. It is the
    /// storage where pools are stored by the build function.
    PoolStoragePtr local_pools_;

    /// Collection of parsers;
    ParserCollection parsers_;
};

/// @brief parser for additional relay information
///
/// This concrete parser handles RelayInfo structure defintions.
/// So far that structure holds only relay IP (v4 or v6) address, but it
/// is expected that the number of parameters will increase over time.
///
/// It is useful for parsing Dhcp<4/6>/subnet<4/6>[x]/relay parameters.
class RelayInfoParser : public DhcpConfigParser {
public:

    /// @brief constructor
    /// @param unused first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param relay_info is the storage in which to store the parsed
    /// @param family specifies protocol family (IPv4 or IPv6)
    RelayInfoParser(const std::string& unused,
                    const isc::dhcp::Subnet::RelayInfoPtr& relay_info,
                    const isc::dhcp::Option::Universe& family);

    /// @brief parses the actual relay parameters
    /// @param relay_info JSON structure holding relay parameters to parse
    virtual void build(isc::data::ConstElementPtr relay_info);

    /// @brief stores parsed info in relay_info
    virtual void commit();

protected:

    /// @brief Creates a parser for the given "relay" member element id.
    ///
    /// The elements currently supported are:
    /// -# ip-address
    ///
    /// @param parser is the "item_name" for a specific member element of
    /// the "relay" specification.
    ///
    /// @return returns a pointer to newly created parser.
    isc::dhcp::ParserPtr
    createConfigParser(const std::string& parser);

    /// Parsed data will be stored there on commit()
    isc::dhcp::Subnet::RelayInfoPtr storage_;

    /// Local storage information (for temporary values)
    isc::dhcp::Subnet::RelayInfo local_;

    /// Storage for subnet-specific string values.
    StringStoragePtr string_values_;

    /// Protocol family (IPv4 or IPv6)
    Option::Universe family_;
};

/// @brief this class parses a single subnet
///
/// This class parses the whole subnet definition. It creates parsers
/// for received configuration parameters as needed.
class SubnetConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    /// @param global_context
    /// @param default_addr default IP address (0.0.0.0 for IPv4, :: for IPv6)
    SubnetConfigParser(const std::string&, ParserContextPtr global_context,
                       const isc::asiolink::IOAddress& default_addr);

    /// @brief parses parameter value
    ///
    /// @param subnet pointer to the content of subnet definition
    ///
    /// @throw isc::DhcpConfigError if subnet configuration parsing failed.
    virtual void build(isc::data::ConstElementPtr subnet);

    /// @brief Adds the created subnet to a server's configuration.
    virtual void commit() = 0;

protected:
    /// @brief creates parsers for entries in subnet definition
    ///
    /// @param config_id name od the entry
    ///
    /// @return parser object for specified entry name
    /// @throw isc::dhcp::DhcpConfigError if trying to create a parser
    ///        for unknown config element
    virtual DhcpConfigParser* createSubnetConfigParser(
                                            const std::string& config_id) = 0;

    /// @brief Issues a server specific warning regarding duplicate subnet
    /// options.
    ///
    /// @param code is the numeric option code of the duplicate option
    /// @param addr is the subnet address
    /// @todo a means to know the correct logger and perhaps a common
    /// message would allow this method to be emitted by the base class.
    virtual void duplicate_option_warning(uint32_t code,
        isc::asiolink::IOAddress& addr) = 0;

    /// @brief Instantiates the subnet based on a given IP prefix and prefix
    /// length.
    ///
    /// @param addr is the IP prefix of the subnet.
    /// @param len is the prefix length
    virtual void initSubnet(isc::asiolink::IOAddress addr, uint8_t len) = 0;

    /// @brief Returns value for a given parameter (after using inheritance)
    ///
    /// This method implements inheritance. For a given parameter name, it first
    /// checks if there is a global value for it and overwrites it with specific
    /// value if such value was defined in subnet.
    ///
    /// @param name name of the parameter
    /// @return triplet with the parameter name
    /// @throw DhcpConfigError when requested parameter is not present
    isc::dhcp::Triplet<uint32_t> getParam(const std::string& name);

    /// @brief Returns optional value for a given parameter.
    ///
    /// This method checks if an optional parameter has been specified for
    /// a subnet. If not, it will try to use a global value. If the global
    /// value is not specified it will return an object representing an
    /// unspecified value.
    ///
    /// @param name name of the configuration parameter.
    /// @return An optional value or a @c Triplet object representing
    /// unspecified value.
    isc::dhcp::Triplet<uint32_t> getOptionalParam(const std::string& name);

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
    /// @throw isc::dhcp::DhcpConfigError if subnet configuration parsing
    /// failed.
    void createSubnet();

protected:

    /// Storage for subnet-specific integer values.
    Uint32StoragePtr uint32_values_;

    /// Storage for subnet-specific string values.
    StringStoragePtr string_values_;

    /// Storage for subnet-specific boolean values.
    BooleanStoragePtr boolean_values_;

    /// Storage for pools belonging to this subnet.
    PoolStoragePtr pools_;

    /// Parsers are stored here.
    ParserCollection parsers_;

    /// Pointer to the created subnet object.
    isc::dhcp::SubnetPtr subnet_;

    /// Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;

    /// Pointer to relay information
    isc::dhcp::Subnet::RelayInfoPtr relay_info_;

    /// Pointer to the options configuration.
    CfgOptionPtr options_;
};

/// @brief Parser for  D2ClientConfig
///
/// This class parses the configuration element "dhcp-ddns" common to the
/// spec files for both dhcp4 and dhcp6. It creates an instance of a
/// D2ClientConfig.
class D2ClientConfigParser : public  isc::dhcp::DhcpConfigParser {
public:
    /// @brief Constructor
    ///
    /// @param entry_name is an arbitrary label assigned to this configuration
    /// definition.
    D2ClientConfigParser(const std::string& entry_name);

    /// @brief Destructor
    virtual ~D2ClientConfigParser();

    /// @brief Performs the parsing of the given dhcp-ddns element.
    ///
    /// The results of the parsing are retained internally for use during
    /// commit.
    /// @todo This parser supplies hard-coded default values for all
    /// optional parameters.  This should be changed once a new plan
    /// for configuration is determined.
    ///
    /// @param client_config is the "dhcp-ddns" configuration to parse
    virtual void build(isc::data::ConstElementPtr client_config);

    /// @brief Creates a parser for the given "dhcp-ddns" member element id.
    ///
    /// The elements currently supported are (see isc::dhcp::D2ClientConfig
    /// for details on each):
    /// -# enable-updates
    /// -# qualifying-suffix
    /// -# server-ip
    /// -# server-port
    /// -# ncr-protocol
    /// -# ncr-format
    /// -# remove-on-renew
    /// -# always-include-fqdn
    /// -# allow-client-update
    /// -# override-no-update
    /// -# override-client-update
    /// -# replace-client-name
    /// -# generated-prefix
    ///
    /// @param config_id is the "item_name" for a specific member element of
    /// the "dns_server" specification.
    ///
    /// @return returns a pointer to newly created parser.
    virtual isc::dhcp::ParserPtr createConfigParser(const std::string&
                                                    config_id);

    /// @brief Instantiates a D2ClientConfig from internal data values
    /// passes to CfgMgr singleton.
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    /// Primarily used for diagnostics.
    std::string entry_name_;

    /// Storage for subnet-specific boolean values.
    BooleanStoragePtr boolean_values_;

    /// Storage for subnet-specific integer values.
    Uint32StoragePtr uint32_values_;

    /// Storage for subnet-specific string values.
    StringStoragePtr string_values_;

    /// @brief Pointer to temporary local instance created during build.
    D2ClientConfigPtr local_client_config_ ;
};

// Pointers to various parser objects.
typedef boost::shared_ptr<BooleanParser> BooleanParserPtr;
typedef boost::shared_ptr<StringParser> StringParserPtr;
typedef boost::shared_ptr<Uint32Parser> Uint32ParserPtr;

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP_PARSERS_H
