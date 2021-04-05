// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D_CFG_MGR_H
#define D_CFG_MGR_H

#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <process/config_base.h>
#include <exceptions/exceptions.h>

#include <stdint.h>

#include <functional>
#include <list>
#include <string>

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
    DCfgMgrBase(ConfigPtr context);

    /// @brief Destructor
    virtual ~DCfgMgrBase();

    /// @brief Acts as the receiver of new configurations.
    ///
    /// This method is similar to what parseConfig did, execept it employs
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

    /// @brief Fetches the configuration context.
    ///
    /// @return returns a pointer reference to the configuration context.
    ConfigPtr& getContext() {
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

    /// @brief Redact the configuration.
    ///
    /// This method replaces passwords and secrets by asterisks. By
    /// default it follows all subtrees at the exception of user
    /// contexts. Please derive the method to allow a reasonable
    /// performance by following only subtrees where the syntax allows
    /// the presence of passwords and secrets.
    ///
    /// @param config the Element tree structure that describes the configuration.
    /// @return unmodified config or a copy of the config where passwords were
    /// replaced by asterisks so can be safely logged to an unprivileged place.
    isc::data::ConstElementPtr
    redactConfig(isc::data::ConstElementPtr const& config) const;

protected:
    /// @brief Adds default values to the given config
    ///
    /// Provides derivations a means to add defaults to a configuration
    /// Element map prior to parsing it.
    ///
    /// @param mutable_config - configuration to which defaults should be added
    virtual void setCfgDefaults(isc::data::ElementPtr mutable_config);

    /// @brief Abstract factory which creates a context instance.
    ///
    /// This method is used at the beginning of configuration process to
    /// create a fresh, empty copy of the derivation-specific context. This
    /// new context will be populated during the configuration process
    /// and will replace the existing context provided the configuration
    /// process completes without error.
    ///
    /// @return Returns a ConfigPtr to the new context instance.
    virtual ConfigPtr createNewContext() = 0;

    /// @brief Replaces existing context with a new, empty context.
    void resetContext();

    /// @brief Update the current context.
    ///
    /// Replaces the existing context with the given context.
    /// @param context Pointer to the new context.
    /// @throw DCfgMgrBaseError if context is NULL.
    void setContext(ConfigPtr& context);

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

    /// @brief Return a list of all paths that contain passwords or secrets.
    ///
    /// Used in @ref isc::process::Daemon::redactConfig to only make copies and
    /// only redact configuration subtrees that contain passwords or secrets.
    ///
    /// This method needs to be overridden in each process that has a distinct
    /// configuration structure.
    ///
    /// @return the list of lists of sequential JSON map keys needed to reach
    /// the passwords and secrets.
    virtual std::list<std::list<std::string>> jsonPathsToRedact() const;

private:
    /// @brief Pointer to the configuration context instance.
    ConfigPtr context_;
};

/// @brief Defines a shared pointer to DCfgMgrBase.
typedef boost::shared_ptr<DCfgMgrBase> DCfgMgrBasePtr;

} // end of isc::process namespace
} // end of isc namespace

#endif // D_CFG_MGR_H
