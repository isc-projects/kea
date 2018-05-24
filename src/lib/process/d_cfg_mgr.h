// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D_CFG_MGR_H
#define D_CFG_MGR_H

#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <functional>

#include <stdint.h>
#include <string>

// Undefine the macro OPTIONAL which is defined in some operating
// systems but conflicts with class constant is the context base class.

#ifdef OPTIONAL
#undef OPTIONAL
#endif

namespace isc {
namespace process {

/// @brief Defines a map of ConstElementPtrs keyed by name
typedef std::map<std::string, isc::data::ConstElementPtr> ElementMap;

/// @brief Exception thrown if the configuration manager encounters an error.
class DCfgMgrBaseError : public isc::Exception {
public:
    DCfgMgrBaseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class DCfgContextBase;
/// @brief Pointer to a configuration context.
typedef boost::shared_ptr<DCfgContextBase> DCfgContextBasePtr;

/// @brief Abstract class that implements a container for configuration context.
/// It provides a single enclosure for the storage of configuration parameters
/// and any other context specific information that needs to be accessible
/// during configuration parsing as well as to the application as a whole.
/// The base class supports storage for a small set of simple data types.
/// Derivations simply add additional storage as needed.  Note that this class
/// declares the pure virtual clone() method, its copy constructor is protected,
/// and its copy operator is inaccessible.  Derivations must supply an
/// implementation of clone that calls the base class copy constructor.
/// This allows the management class to perform context backup and restoration
/// without derivation specific knowledge using logic like
/// the following:
///
///    // Make a backup copy
///    DCfgContextBasePtr backup_copy(context_->clone());
///    :
///    // Restore from backup
///    context_ = backup_copy;
///
class DCfgContextBase : public isc::dhcp::UserContext, public isc::data::CfgToElement {
public:
    /// @brief Indicator that a configuration parameter is optional.
    static const bool OPTIONAL = true;
    static const bool REQUIRED = false;

    /// @brief Constructor
    DCfgContextBase();

    /// @brief Destructor
    virtual ~DCfgContextBase();

    /// @brief Fetches the value for a given boolean configuration parameter
    /// from the context.
    ///
    /// @param name is the name of the parameter to retrieve.
    /// @param value is an output parameter in which to return the retrieved
    /// value.
    /// @param optional if true, the parameter is optional and the method
    /// will not throw if the parameter is not found in the context. The
    /// contents of the output parameter, value, will not be altered.
    /// It defaults to false if not specified.
    ///
    /// @return The parameter's element's position information if found,
    /// otherwise it returns isc::data::Element::ZERO_POSITION().
    ///
    /// @throw throws DhcpConfigError if the context does not contain the
    /// parameter and optional is false.
    const data::Element::Position&
    getParam(const std::string& name, bool& value, bool optional=false);

    /// @brief Fetches the value for a given uint32_t configuration parameter
    /// from the context.
    ///
    /// @param name is the name of the parameter to retrieve.
    /// @param value is an output parameter in which to return the retrieved
    /// value.
    /// @param optional if true, the parameter is optional and the method
    /// will not throw if the parameter is not found in the context. The
    /// contents of the output parameter, value, will not be altered.
    ///
    /// @return The parameter's element's position information if found,
    /// otherwise it returns isc::data::Element::ZERO_POSITION().
    ///
    /// @throw throws DhcpConfigError if the context does not contain the
    /// parameter and optional is false.
    const data::Element::Position&
    getParam(const std::string& name, uint32_t& value,
                 bool optional=false);

    /// @brief Fetches the value for a given string configuration parameter
    /// from the context.
    ///
    /// @param name is the name of the parameter to retrieve.
    /// @param value is an output parameter in which to return the retrieved
    /// value.
    /// @param optional if true, the parameter is optional and the method
    /// will not throw if the parameter is not found in the context. The
    /// contents of the output parameter, value, will not be altered.
    ///
    /// @return The parameter's element's position information if found,
    /// otherwise it returns isc::data::Element::ZERO_POSITION().
    ///
    /// @throw throws DhcpConfigError if the context does not contain the
    /// parameter and optional is false.
    const data::Element::Position&
    getParam(const std::string& name, std::string& value,
                  bool optional=false);

    /// @brief Fetches the Boolean Storage. Typically used for passing
    /// into parsers.
    ///
    /// @return returns a pointer to the Boolean Storage.
    isc::dhcp::BooleanStoragePtr getBooleanStorage() {
        return (boolean_values_);
    }

    /// @brief Fetches the uint32 Storage. Typically used for passing
    /// into parsers.
    ///
    /// @return returns a pointer to the uint32 Storage.
    isc::dhcp::Uint32StoragePtr getUint32Storage() {
        return (uint32_values_);
    }

    /// @brief Fetches the string Storage. Typically used for passing
    /// into parsers.
    ///
    /// @return returns a pointer to the string Storage.
    isc::dhcp::StringStoragePtr getStringStorage() {
        return (string_values_);
    }

    /// @brief Creates a clone of this context object.
    ///
    /// As mentioned in the the class brief, derivation must supply an
    /// implementation that initializes the base class storage as well as its
    /// own.  Typically the derivation's clone method would return the result
    /// of passing  "*this" into its own copy constructor:
    ///
    /// @code
    /// class DStubContext : public DCfgContextBase {
    /// public:
    ///  :
    ///     // Clone calls its own copy constructor
    ///     virtual DCfgContextBasePtr clone() {
    ///         return (DCfgContextBasePtr(new DStubContext(*this)));
    ///     }
    ///
    ///     // Note that the copy constructor calls the base class copy ctor
    ///     // then initializes its additional storage.
    ///     DStubContext(const DStubContext& rhs) : DCfgContextBase(rhs),
    ///         extra_values_(new Uint32Storage(*(rhs.extra_values_))) {
    ///     }
    ///  :
    ///    // Here's the derivation's additional storage.
    ///    isc::dhcp::Uint32StoragePtr extra_values_;
    ///  :
    /// @endcode
    ///
    /// @return returns a pointer to the new clone.
    virtual DCfgContextBasePtr clone() = 0;

    /// @brief Unparse a configuration object
    ///
    /// Returns an element which must parse into the same object, i.e.
    /// @code
    /// for all valid config C parse(parse(C)->toElement()) == parse(C)
    /// @endcode
    ///
    /// @return a pointer to a configuration which can be parsed into
    /// the initial configuration object
    virtual isc::data::ElementPtr toElement() const = 0;

protected:
    /// @brief Copy constructor for use by derivations in clone().
    DCfgContextBase(const DCfgContextBase& rhs);

private:
    /// @brief Private assignment operator to avoid potential for slicing.
    DCfgContextBase& operator=(const DCfgContextBase& rhs);

    /// @brief Storage for boolean parameters.
    isc::dhcp::BooleanStoragePtr boolean_values_;

    /// @brief Storage for uint32 parameters.
    isc::dhcp::Uint32StoragePtr uint32_values_;

    /// @brief Storage for string parameters.
    isc::dhcp::StringStoragePtr string_values_;
};

/// @brief Defines a sequence of Element IDs used to specify a parsing order.
typedef std::vector<std::string> ElementIdList;

/// @brief Configuration Manager
///
/// DCfgMgrBase is an abstract class that provides the mechanisms for managing
/// an application's configuration.  This includes services for parsing sets of
/// configuration values, storing the parsed information in its converted form,
/// and retrieving the information on demand.  It is intended to be the worker
/// class which is handed a set of configuration values to process by upper
/// application management layers.
///
/// This class allows two configuration methods:
///
/// 1. classic method
///
/// The class presents a public method for receiving new configurations,
/// parseConfig.  This method coordinates the parsing effort as follows:
///
/// @code
///    make backup copy of configuration context
///    Split top-level configuration elements into to sets:
///      1. Set of scalar elements (strings, booleans, ints, etc..)
///      2. Set of object elements (maps, lists, etc...)
///    For each entry in the scalar set:
///        get derivation-specific parser for element
///        run parser
///        update context with parsed results
///        break on error
///
///    For each entry in the object set;
///        get derivation-specific parser for element
///        run parser
///        update context with parsed results
///        break on error
///
///    if an error occurred or this is only a check
///        restore configuration context from backup
/// @endcode
///
/// The above structuring ensures that global parameters are parsed first
/// making them available during subsequent object element parsing. The order
/// in which the object elements are processed is either:
///
///    1. Natural order presented by the configuration set
///    2. Specific order determined by a list of element ids
///
/// This allows a derivation to specify the order in which its elements are
/// parsed if there are dependencies between elements.
///
/// To parse a given element, its id along with the element itself, 
/// is passed into the virtual method, @c parseElement. Derivations are 
/// expected to converts the element into application specific object(s),
/// thereby isolating the CPL from application details.
///
/// In the event that an error occurs, parsing is halted and the
/// configuration context is restored from backup.
///
/// See @ref isc::d2::D2CfgMgr and @ref isc::d2::D2Process for example use of
/// this approach.
///
/// 2. simple configuration method
///
/// This approach assumes usage of @ref isc::data::SimpleParser paradigm. It
/// does not use any intermediate storage, does not use parser pointers, does
/// not enforce parsing order.
///
/// Here's the expected control flow order:
/// 1. implementation calls simpleParseConfig from its configure method.
/// 2. simpleParseConfig makes a configuration context
/// 3. parse method from the derived class is called
/// 4. if the configuration was unsuccessful or this is only a check, the
///    old context is reinstantiated. If not, the configuration is kept.
///
/// See @ref isc::agent::CtrlAgentCfgMgr and @ref isc::agent::CtrlAgentProcess
/// for example use of this approach.
class DCfgMgrBase {
public:
    /// @brief Constructor
    ///
    /// @param context is a pointer to the configuration context the manager
    /// will use for storing parsed results.
    ///
    /// @throw throws DCfgMgrBaseError if context is null
    DCfgMgrBase(DCfgContextBasePtr context);

    /// @brief Destructor
    virtual ~DCfgMgrBase();

    /// @brief Acts as the receiver of new configurations and coordinates
    /// the parsing as described in the class brief.
    ///
    /// @param config_set is a set of configuration elements to be parsed.
    /// @param check_only true if the config is to be checked only, but not applied
    ///
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    isc::data::ConstElementPtr
    parseConfig(isc::data::ConstElementPtr config_set,
                bool check_only = false);


    /// @brief Acts as the receiver of new configurations.
    ///
    /// This method is similar to what @ref parseConfig does, execept it employs
    /// the simple parser paradigm: no intermediate storage, no parser pointers
    /// no distinction between params_map and objects_map, parse order (if needed)
    /// can be enforced in the actual implementation by calling specific
    /// parsers first. See @ref isc::agent::CtrlAgentCfgMgr::parse for example.
    ///
    /// If check_only is true, the actual parsing is done to check if the configuration
    /// is sane, but is then reverted.
    ///
    /// @param config set of configuration elements to be parsed
    /// @param check_only true if the config is to be checked only, but not applied
    /// @param post_config_cb Callback to be executed after the usual parsing stage.
    /// This can be specified as a C++ lambda which configures other parts of the
    /// system based on the parsed configuration information. The callback should
    /// throw an exception to signal an error. This method will catch this
    /// exception and place an exception string within the result returned.
    ///
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    isc::data::ConstElementPtr
    simpleParseConfig(isc::data::ConstElementPtr config,
                      bool check_only = false,
                      const std::function<void()>& post_config_cb = nullptr);

    /// @brief Adds a given element id to the end of the parse order list.
    ///
    /// The order in which object elements are retrieved from this is the
    /// order in which they are added to the list. Derivations should use this
    /// method to populate the parse order as part of their constructor.
    /// Scalar parameters should NOT be included in this list.
    ///
    /// @param element_id is the string name of the element as it will appear
    /// in the configuration set.
    void addToParseOrder(const std::string& element_id){
        parse_order_.push_back(element_id);
    }

    /// @brief Fetches the parse order list.
    ///
    /// @return returns a const reference to the list.
    const ElementIdList& getParseOrder() const {
        return (parse_order_);
    }

    /// @brief Fetches the configuration context.
    ///
    /// @return returns a pointer reference to the configuration context.
    DCfgContextBasePtr& getContext() {
        return (context_);
    }

    /// @brief Returns configuration summary in the textual format.
    ///
    /// This method returns the brief text describing the current configuration.
    /// It may be used for logging purposes, e.g. whn the new configuration is
    /// committed to notify a user about the changes in configuration.
    ///
    /// @param selection Bitfield which describes the parts of the configuration
    /// to be returned.
    ///
    /// @return Summary of the configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t selection) = 0;

protected:
    /// @brief Adds default values to the given config
    ///
    /// Provides derivations a means to add defaults to a configuration
    /// Element map prior to parsing it.
    ///
    /// @param mutable_config - configuration to which defaults should be added
    virtual void setCfgDefaults(isc::data::ElementPtr mutable_config);

    /// @brief Parses an individual element
    ///
    /// Each element to be parsed is passed into this method to be converted
    /// into the requisite application object(s).
    ///
    /// @param element_id name of the element as it is expected in the cfg
    /// @param element value of the element as ElementPtr
    ///
    virtual void parseElement(const std::string& element_id,
                              isc::data::ConstElementPtr element);

    /// @brief Parses a set of scalar configuration elements into global
    /// parameters
    ///
    /// For each scalar element in the set:
    /// - Invoke parseElement
    /// - If it returns true go to the next element otherwise:
    ///     - create a parser for the element
    ///     - invoke the parser's build method
    ///     - invoke the parser's commit method
    ///
    /// This will commit the values to context storage making them accessible
    /// during object parsing.
    ///
    /// @param params_config set of scalar configuration elements to parse
    virtual void buildParams(isc::data::ConstElementPtr params_config);

    /// @brief Abstract factory which creates a context instance.
    ///
    /// This method is used at the beginning of configuration process to
    /// create a fresh, empty copy of the derivation-specific context. This
    /// new context will be populated during the configuration process
    /// and will replace the existing context provided the configuration
    /// process completes without error.
    ///
    /// @return Returns a DCfgContextBasePtr to the new context instance.
    virtual DCfgContextBasePtr createNewContext() = 0;

    /// @brief Replaces existing context with a new, empty context.
    void resetContext();

    /// @brief Update the current context.
    ///
    /// Replaces the existing context with the given context.
    /// @param context Pointer to the new context.
    /// @throw DCfgMgrBaseError if context is NULL.
    void setContext(DCfgContextBasePtr& context);

    /// @brief Parses actual configuration.
    ///
    /// This method is expected to be implemented in derived classes that employ
    /// SimpleParser paradigm (i.e. they call simpleParseConfig rather than
    /// parseConfig from their configure method).
    ///
    /// Implementations that do not employ this method may provide dummy
    /// implementation.
    ///
    /// @param config the Element tree structure that describes the configuration.
    /// @param check_only false for normal configuration, true when verifying only
    ///
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr parse(isc::data::ConstElementPtr config,
                                             bool check_only);

private:

    /// @brief Parse a configuration element.
    ///
    /// Given an element_id and data value, invoke parseElement. If
    /// it returns true the return, otherwise created the appropriate
    /// parser, parse the data value, and commit the results.
    ///
    ///
    /// @param element_id is the string name of the element as it will appear
    /// in the configuration set.
    /// @param value is the data value to be parsed and associated with
    /// element_id.
    ///
    /// @throw throws DCfgMgrBaseError if an error occurs.
    void buildAndCommit(std::string& element_id,
                        isc::data::ConstElementPtr value);

    /// @brief A list of element ids which specifies the element parsing order.
    ///
    /// If the list is empty, the natural order in the configuration set
    /// it used.
    ElementIdList parse_order_;

    /// @brief Pointer to the configuration context instance.
    DCfgContextBasePtr context_;
};

/// @brief Defines a shared pointer to DCfgMgrBase.
typedef boost::shared_ptr<DCfgMgrBase> DCfgMgrBasePtr;


}; // end of isc::process namespace
}; // end of isc namespace

#endif // D_CFG_MGR_H
