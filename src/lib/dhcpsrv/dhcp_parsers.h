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

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <dhcpsrv/option_space_container.h>
#include <dhcpsrv/subnet.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Storage for option definitions.
typedef OptionSpaceContainer<OptionDefContainer,
    OptionDefinitionPtr, std::string> OptionDefStorage;
/// @brief Shared pointer to option definitions storage.
typedef boost::shared_ptr<OptionDefStorage> OptionDefStoragePtr;

/// Collection of containers holding option spaces. Each container within
/// a particular option space holds so-called option descriptors.
typedef OptionSpaceContainer<Subnet::OptionContainer,
    Subnet::OptionDescriptor, std::string> OptionStorage;
/// @brief Shared pointer to option storage.
typedef boost::shared_ptr<OptionStorage> OptionStoragePtr;

/// @brief Shared pointer to collection of hooks libraries.
typedef boost::shared_ptr<std::vector<std::string> > HooksLibsStoragePtr;

/// @brief A template class that stores named elements of a given data type.
///
/// This template class is provides data value storage for configuration parameters
/// of a given data type.  The values are stored by parameter name and as instances
/// of type "ValueType".
///
/// @param ValueType is the data type of the elements to store.
template<typename ValueType>
class ValueStorage {
    public:
        /// @brief  Stores the the parameter and its value in the store.
        ///
        /// If the parameter does not exist in the store, then it will be added,
        /// otherwise its data value will be updated with the given value.
        ///
        /// @param name is the name of the paramater to store.
        /// @param value is the data value to store.
        void setParam(const std::string& name, const ValueType& value) {
            values_[name] = value;
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

        /// @brief  Remove the parameter from the store.
        ///
        /// Deletes the entry for the given parameter from the store if it
        /// exists.
        ///
        /// @param name is the name of the paramater to delete.
        void delParam(const std::string& name) {
            values_.erase(name);
        }

        /// @brief Deletes all of the entries from the store.
        ///
        void clear() {
            values_.clear();
        }

    private:
        /// @brief An std::map of the data values, keyed by parameter names.
        std::map<std::string, ValueType> values_;
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

    /// @brief Storage for options.
    OptionStoragePtr options_;

    /// @brief Storage for option definitions.
    OptionDefStoragePtr option_defs_;

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
        : storage_(storage), param_name_(param_name), value_() {
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
        storage_->setParam(param_name_, value_);
    }
 
private:
    /// Pointer to the storage where committed value is stored.
    boost::shared_ptr<ValueStorage<ValueType> > storage_;

    /// Name of the parameter which value is parsed with this parser.
    std::string param_name_;

    /// Parsed value.
    ValueType value_;
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
    /// @brief Check that specified interface exists in
    /// @c InterfaceListConfigParser::interfaces_.
    ///
    /// @param iface A name of the interface.
    ///
    /// @return true if specified interface name was found.
    bool isIfaceAdded(const std::string& iface) const;

    /// contains list of network interfaces
    typedef std::list<std::string> IfaceListStorage;
    IfaceListStorage interfaces_;

    // Should server listen on all interfaces.
    bool activate_all_;

    // Parsed parameter name
    std::string param_name_;
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
    /// @param options is the option storage in which to store the parsed option
    /// upon "commit".
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    /// @throw isc::dhcp::DhcpConfigError if options or global_context are null.
    OptionDataParser(const std::string& dummy, OptionStoragePtr options,
                    ParserContextPtr global_context);

    /// @brief Parses the single option data.
    ///
    /// This method parses the data of a single option from the configuration.
    /// The option data includes option name, option code and data being
    /// carried by this option. Eventually it creates the instance of the
    /// option.
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
    /// This function adds a new option to the storage or replaces an existing
    /// option with the same code.
    ///
    /// @throw isc::InvalidOperation if failed to set pointer to storage or
    /// failed
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

    /// Storage for boolean values.
    BooleanStoragePtr boolean_values_;

    /// Storage for string values (e.g. option name or data).
    StringStoragePtr string_values_;

    /// Storage for uint32 values (e.g. option code).
    Uint32StoragePtr uint32_values_;

    /// Pointer to options storage. This storage is provided by
    /// the calling class and is shared by all OptionDataParser objects.
    OptionStoragePtr options_;

    /// Option descriptor holds newly configured option.
    Subnet::OptionDescriptor option_descriptor_;

    /// Option space name where the option belongs to.
    std::string option_space_;

    /// Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;
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
    /// @param options parsed option storage for options in this list
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    /// @param optionDataParserFactory factory method for creating individual
    /// option parsers
    /// @throw isc::dhcp::DhcpConfigError if options or global_context are null.
    OptionDataListParser(const std::string& dummy, OptionStoragePtr options,
                        ParserContextPtr global_context,
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
    OptionStoragePtr options_;

    /// Intermediate option storage. This storage is used by
    /// lower level parsers to add new options.  Values held
    /// in this storage are assigned to main storage (options_)
    /// if overall parsing was successful.
    OptionStoragePtr local_options_;

    /// Collection of parsers;
    ParserCollection parsers_;

    /// Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;

    /// Factory to create server-specific option data parsers
    OptionDataParserFactory *optionDataParserFactory_;
};


/// @brief Parser for a single option definition.
///
/// This parser creates an instance of a single option definition.
class OptionDefParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param storage is the definition storage in which to store the parsed
    /// definition upon "commit".
    /// @throw isc::dhcp::DhcpConfigError if storage is null.
    OptionDefParser(const std::string& dummy, OptionDefStoragePtr storage);

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
    OptionDefStoragePtr storage_;

    /// Storage for boolean values.
    BooleanStoragePtr boolean_values_;

    /// Storage for string values.
    StringStoragePtr string_values_;

    /// Storage for uint32 values.
    Uint32StoragePtr uint32_values_;
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
    /// @param storage is the definition storage in which to store the parsed
    /// definitions in this list
    /// @throw isc::dhcp::DhcpConfigError if storage is null.
    OptionDefListParser(const std::string& dummy, OptionDefStoragePtr storage);

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
    OptionDefStoragePtr storage_;
};

/// @brief a collection of pools
///
/// That type is used as intermediate storage, when pools are parsed, but there is
/// no subnet object created yet to store them.
typedef std::vector<PoolPtr> PoolStorage;
typedef boost::shared_ptr<PoolStorage> PoolStoragePtr;

/// @brief parser for pool definition
///
/// This abstract parser handles pool definitions, i.e. a list of entries of one
/// of two syntaxes: min-max and prefix/len. Pool objects are created
/// and stored in chosen PoolStorage container.
///
/// It is useful for parsing Dhcp<4/6>/subnet<4/6>[X]/pool parameters.
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

    /// @brief parses the actual list
    ///
    /// This method parses the actual list of interfaces.
    /// No validation is done at this stage, everything is interpreted as
    /// interface name.
    /// @param pools_list list of pools defined for a subnet
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    virtual void build(isc::data::ConstElementPtr pools_list);

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

/// @brief this class parses a single subnet
///
/// This class parses the whole subnet definition. It creates parsers
/// for received configuration parameters as needed.
class SubnetConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    SubnetConfigParser(const std::string&, ParserContextPtr global_context);

    /// @brief parses parameter value
    ///
    /// @param subnet pointer to the content of subnet definition
    ///
    /// @throw isc::DhcpConfigError if subnet configuration parsing failed.
    virtual void build(isc::data::ConstElementPtr subnet);

    /// @brief Adds the created subnet to a server's configuration.
    virtual void commit() = 0;

    /// @brief tries to convert option_space string to numeric vendor_id
    ///
    /// This will work if the option_space has format "vendor-1234".
    /// This is used to detect whether a given option-space is a vendor
    /// space or not. Returns 0 if the format is different.
    /// @return numeric vendor-id (or 0 if the format does not match)
    static uint32_t optionSpaceToVendorId(const std::string& option_space);

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

    /// @brief Determines if the given option space name and code describe
    /// a standard option for the  server.
    ///
    /// @param option_space is the name of the option space to consider
    /// @param code is the numeric option code to consider
    /// @return returns true if the space and code are part of the server's
    /// standard options.
    virtual bool isServerStdOption(std::string option_space, uint32_t code) = 0;

    /// @brief Returns the option definition for a given option code from
    /// the server's standard set of options.
    /// @param code is the numeric option code of the desired option definition.
    /// @return returns a pointer the option definition
    virtual OptionDefinitionPtr getServerStdOptionDefinition (
                                                             uint32_t code) = 0;

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

private:

    /// @brief Append sub-options to an option.
    ///
    /// @param option_space a name of the encapsulated option space.
    /// @param option option instance to append sub-options to.
    void appendSubOptions(const std::string& option_space, OptionPtr& option);

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

    /// Storage for pools belonging to this subnet.
    PoolStoragePtr pools_;

    /// Storage for options belonging to this subnet.
    OptionStoragePtr options_;

    /// Parsers are stored here.
    ParserCollection parsers_;

    /// Pointer to the created subnet object.
    isc::dhcp::SubnetPtr subnet_;

    /// Parsing context which contains global values, options and option
    /// definitions.
    ParserContextPtr global_context_;
};

// Pointers to various parser objects.
typedef boost::shared_ptr<BooleanParser> BooleanParserPtr;
typedef boost::shared_ptr<StringParser> StringParserPtr;
typedef boost::shared_ptr<Uint32Parser> Uint32ParserPtr;

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP_PARSERS_H

