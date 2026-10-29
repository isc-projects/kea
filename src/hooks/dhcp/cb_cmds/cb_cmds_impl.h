// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CMDS_IMPL_H
#define CB_CMDS_IMPL_H

#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <cc/stamped_value.h>
#include <database/backend_selector.h>
#include <database/server.h>
#include <database/server_collection.h>
#include <database/server_selector.h>
#include <dhcpsrv/cb_ctl_dhcp.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <hooks/hooks.h>

#include <cstdint>
#include <sstream>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <cb_cmds/cb_parsers.h>
#include <sys/socket.h>

namespace isc {
namespace cb {

/// @brief This parser class contains the common logic for various callouts
/// to parse and validate the contents of the received command.
class ConfigCmdsParser {
public:

    /// @brief Server selector parsing.
    ///
    /// It determines the expected server tags specified for the command
    /// parsed by the @c parseInputListElement and @c parseInputMapElement.
    ///
    /// @note We currently don't support the case of the optional server-tags
    /// list, but it may be useful in the future and makes the progressive
    /// implementation of the server tags easier.
    enum ServerTagsParse : uint16_t {
        TAGS_OPTIONAL,  ///< server-tags entry is optional
        TAGS_REQUIRED,  ///< server-tags is required
        TAGS_FORBIDDEN  ///< server-tags is not allowed
    };

    /// @brief Subnets actions for shared network delete.
    enum SubnetsAction : uint16_t {
        ACTION_KEEP,   ///< keep subnets (default)
        ACTION_DELETE  ///< delete subnets
    };

    /// @brief Subnets actions for shared network get command.
    enum SubnetsInclude : uint16_t {
        INCLUDE_NO,
        INCLUDE_FULL
    };

    /// @brief Parses a command containing a list of elements.
    ///
    /// This method is used for processing control commands which contain a
    /// list of maps. The map contains a configuration data structure such as
    /// subnet, shared network, global parameter, option etc. The parser to be
    /// used to parse the command arguments into the respective C++ objects is
    /// provided via the template parameters.
    ///
    /// The second template argument, i.e. @c ParserArgs, is a variadic template
    /// parameter pack which can contain no parameters, one parameter or multiple
    /// parameters. This parameter pack is passed to the configuration parser's
    /// (@c ParserType) constructor. For example:
    ///
    /// @code
    /// auto option_pair = std::make_pair(OptionDescriptor(false, false), "");
    /// BackendSelector backend_selector;
    ///
    /// parseInputListElement<OptionDataParser, uint16_t, CfgOptionDefPtr>
    ///     (callout_handle, "options", AF_INET,
    ///      CfgMgr::instance().getCurrentCfg()->getCfgOptionDef(),
    ///      option_pair, backend_selector, server_selector,
    ///      ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);
    /// @endcode
    ///
    /// The first template argument specifies that @c OptionDataParser must
    /// be used to parse the data. Its constructor takes two parameters:
    /// - const uint16_t address_family
    /// - CfgOptionDefPtr cfg_option_def
    ///
    /// The second and third template parameter belong to the aforementioned
    /// parameter pack and they indicate that the @c uint16_t and the
    /// @c CfgOptionDefPtr parameters must be passed to the parser's constructor.
    /// These parameters are provided as the second and third parameter in
    /// the invocation. The last template parameter @c ElementType is not
    /// specified in the example above, because it is inferred by the compiler
    /// from the function arguments.
    ///
    /// Another example demonstrates how to call this method when the parser's
    /// constructor takes no arguments:
    ///
    /// @code
    /// Subnet4Ptr subnet;
    /// BackendSelector backend_selector;
    /// ServerSelector server_selector = ServerSelector::UNASSIGNED();
    /// parseInputListElement<Subnet4ConfigParser>(callout_handle,
    ///                                            "subnets",
    ///                                            subnet,
    ///                                            backend_selector,
    ///                                            server_selector,
    ///                                            ServerTagsParse::TAGS_REQUIRED);
    /// @endcode
    ///
    /// In this case, the sole template parameter is the one that specifies
    /// the parser type. Neither the parameter pack is provided nor parser
    /// specific arguments.
    ///
    /// Currently, the number of maps allowed in the list is restricted to 1.
    /// That means that only one subnet, shared network, global parameter etc.
    /// can be sent in a single command.
    ///
    /// @tparam ParserType Type of the parser to be used for parsing the data.
    /// @tparam ParserArgs Arguments to be passed to the parser specified via
    /// @c ParserType.
    /// @tparam ElementType Type of the object which holds parsed data.
    ///
    /// @param callout_handle Reference to the callout handle holding the
    /// command to be parsed.
    /// @param list_name Name of the list within command's arguments that
    /// holds the data, e.g. "subnets", "shared-networks" etc.
    /// @param parser_args Arguments to be passed to the parser.
    /// @param [out] parsed_element Reference to the object where the parsed data
    /// should be stored.
    /// @param [out] backend_selector Reference to the backend selector retrieved
    /// from the command.
    /// @param [out] server_selector Reference to the server selector retrieved
    /// from the command.
    /// @param tags_parse Parsing choice for server-tags entry.
    /// @param sub_type type of the element of the list.
    ///
    /// @return Pointer to the command arguments.
    /// @throw BadValue if the command is malformed.
    template<typename ParserType, typename... ParserArgs, typename ElementType>
    data::ConstElementPtr
    parseInputListElement(hooks::CalloutHandle& callout_handle,
                          const std::string& list_name,
                          ParserArgs... parser_args,
                          ElementType& parsed_element,
                          db::BackendSelector& backend_selector,
                          db::ServerSelector& server_selector,
                          ServerTagsParse tags_parse,
                          data::Element::types sub_type = data::Element::map) const {
        // Retrieve the command from the callout handle.
        data::ConstElementPtr command;
        callout_handle.getArgument("command", command);

        // Expect that the command include arguments.
        data::ConstElementPtr args;
        static_cast<void>(config::parseCommandWithArgs(args, command));

        // Create backend selector from the received arguments. If the arguments
        // do not include "remote" parameter, the default (unspecified) backend
        // selector is created.
        backend_selector = getBackendSelector(args);

        // Create server selector from the received arguments.
        server_selector = getServerSelector(args, tags_parse);

        // Get the named list from the arguments.
        data::ConstElementPtr element_list = args->get(list_name);
        if (!element_list ||
            (element_list->getType() != data::Element::list)) {
            isc_throw(BadValue, "'" << list_name << "' parameter must be specified"
                      " and must be a list");

        // We currently require exactly one argument in the list. In the future
        // we may allow multiple elements.
        } else if (element_list->size() != 1) {
            isc_throw(BadValue, "'" << list_name << "' list must include exactly one element");
        }

        // Since we have already checked that there is one element in the list
        // we can get it directly via index of 0.
        data::ConstElementPtr element = element_list->get(0);

        // It must be of the given type (default a map).
        if (element->getType() != sub_type) {
            isc_throw(BadValue, "'" << list_name << "' sub-element must be a "
                      << data::Element::typeToName(sub_type));
        }

        // Run the parser for this element and return it via the method's argument.
        ParserType parser(parser_args...);
        parsed_element = parser.parse(element);
        return (args);
    }

    /// @brief Parses a command containing a list of elements (second call).
    ///
    /// This method is used for processing control commands which contain a
    /// list of maps. The map contains a configuration data structure such as
    /// subnet, shared network, global parameter, option etc. The parser to be
    /// used to parse the command arguments into the respective C++ objects is
    /// provided via the template parameters.
    ///
    /// This is a stripped down version which is intended to be called a
    /// second time after "full" parseInputListElement.
    ///
    /// @tparam ParserType Type of the parser to be used for parsing the data.
    /// @tparam ParserArgs Arguments to be passed to the parser specified via
    /// @c ParserType.
    /// @tparam ElementType Type of the object which holds parsed data.
    ///
    /// @param callout_handle Reference to the callout handle holding the
    /// command to be parsed.
    /// @param list_name Name of the list within command's arguments that
    /// holds the data, e.g. "subnets", "shared-networks" etc.
    /// @param parser_args Arguments to be passed to the parser.
    /// @param [out] parsed_element Reference to the object where the parsed data
    /// should be stored.
    /// @param sub_type type of the element of the list.
    ///
    /// @return Pointer to the command arguments.
    /// @throw BadValue if the command is malformed.
    template<typename ParserType, typename... ParserArgs, typename ElementType>
    data::ConstElementPtr
    parseInputListElement(hooks::CalloutHandle& callout_handle,
                          const std::string& list_name,
                          ParserArgs... parser_args,
                          ElementType& parsed_element,
                          data::Element::types sub_type = data::Element::map) const {
        // Retrieve the command from the callout handle.
        data::ConstElementPtr command;
        callout_handle.getArgument("command", command);

        // Expect that the command include arguments.
        data::ConstElementPtr args;
        static_cast<void>(config::parseCommandWithArgs(args, command));

        // Skipped backend and server selectors.

        // Get the named list from the arguments.
        data::ConstElementPtr element_list = args->get(list_name);
        if (!element_list ||
            (element_list->getType() != data::Element::list)) {
            isc_throw(BadValue, "'" << list_name << "' parameter must be specified"
                      " and must be a list");

        // We currently require exactly one argument in the list. In the future
        // we may allow multiple elements.
        } else if (element_list->size() != 1) {
            isc_throw(BadValue, "'" << list_name << "' list must include exactly one element");
        }

        // Since we have already checked that there is one element in the list
        // we can get it directly via index of 0.
        data::ConstElementPtr element = element_list->get(0);

        // It must be of the given type (default a map).
        if (element->getType() != sub_type) {
            isc_throw(BadValue, "'" << list_name << "' sub-element must be a "
                      << data::Element::typeToName(sub_type));
        }

        // Run the parser for this element and return it via the method's argument.
        ParserType parser(parser_args...);
        parsed_element = parser.parse(element);
        return (args);
    }

    /// @brief Parses a command containing a map of elements.
    ///
    /// This method is used for processing control commands which contain a
    /// non-empty map. For example, it is used to parse a map of global
    /// configuration parameters for the DHCP servers. The parser to be
    /// used to parse the command arguments into the respective C++ objects is
    /// provided via the template parameters.
    ///
    /// The second template argument, i.e. @c ParserArgs, is a variadic template
    /// parameter pack which can contain no parameters, one parameter or multiple
    /// parameters. This parameter pack is passed to the configuration parser's
    /// (@c ParserType) constructor. For example:
    ///
    /// @code
    /// StampedValueCollection stamped_values;
    /// BackendSelector backend_selector;
    /// ServerSelector server_selector = ServerSelector::UNASSIGNED();
    /// const SimpleKeywords& keywords = SimpleParser4::GLOBAL4_PARAMETERS;
    /// parser_->parseInputMapElement<GlobalParameterParser, const SimpleKeywords&>
    ///     (callout_handle, "parameters", keywords,
    ///      stamped_values, backend_selector, server_selector,
    ///      ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);
    /// @endcode
    ///
    /// The first template argument specifies that @c GlobalParameterParser must
    /// be used to parse the map. Its constructor takes one argument, i.e.
    /// const SimpleKeywords&.
    ///
    /// The second template parameter belongs to the aforementioned parameter pack
    /// and it indicates that const SimpleKeywords& parameters must be passed to the
    /// parser's constructor.
    ///
    /// The last template parameter @c ElementType is not specified in the example
    /// above, because it is inferred by the compiler from the function arguments.
    ///
    /// @tparam ParserType Type of the parser to be used for parsing the data.
    /// @tparam ParserArgs Arguments to be passed to the parser specified via
    /// @c ParserType.
    /// @tparam ElementType Type of the object which holds parsed data.
    ///
    /// @param callout_handle Reference to the callout handle holding the
    /// command to be parsed.
    /// @param map_name Name of the map within command's arguments that holds
    /// the data.
    /// @param parser_args Arguments to be passed to the parser.
    /// @param [out] parsed_element Reference to the object where the parsed data
    /// should be stored.
    /// @param [out] backend_selector Reference to the backend selector retrieved
    /// from the command.
    /// @param [out] server_selector Reference to the server selector retrieved
    /// from the command.
    /// @param tags_parse Parsing choice for server-tags entry.
    template<typename ParserType, typename... ParserArgs, typename ElementType>
    void parseInputMapElement(hooks::CalloutHandle& callout_handle,
                              const std::string& map_name,
                              ParserArgs... parser_args,
                              ElementType& parsed_element,
                              db::BackendSelector& backend_selector,
                              db::ServerSelector& server_selector,
                              ServerTagsParse tags_parse) const {
        // Retrieve the command from the callout handle.
        data::ConstElementPtr command;
        callout_handle.getArgument("command", command);

        // Expect that the command include arguments.
        data::ConstElementPtr args;
        static_cast<void>(config::parseCommandWithArgs(args, command));

        // Create backend selector from the received arguments. If the arguments
        // do not include "remote" parameter, the default (unspecified) backend
        // selector is created.
        backend_selector = getBackendSelector(args);

        // Create server selector from the received arguments.
        server_selector = getServerSelector(args, tags_parse);

        // Get the named map from the arguments.
        data::ConstElementPtr element_map = args->get(map_name);
        if (!element_map || (element_map->getType() != data::Element::map)) {
            isc_throw(BadValue, "'" << map_name << "' parameter must be specified"
                      " and must be a map");
        }

        // There must be at least one parameter in the map.
        if (element_map->size() == 0) {
            isc_throw(BadValue, "'" << map_name << "' map must not be empty");
        }

        // Run the parser for this element and return it via the method's argument.
        ParserType parser(parser_args...);
        parsed_element = parser.parse(element_map);
    }

    /// @brief Creates backend selector from the command's arguments.
    ///
    /// If the command arguments include "remote" parameter we will use the
    /// contents of this parameter to create backend selector. Otherwise, we
    /// will return the default selector (unspecified).
    ///
    /// @param args Pointer to the command arguments.
    db::BackendSelector
    getBackendSelector(const data::ConstElementPtr& args) const;

    /// @brief Creates server selector from the command's arguments.
    ///
    /// If the parsing choice is TAGS_REQUIRED:
    ///   - no "server-tags" or empty parameter give an error.
    ///   - "server-tags" parameter contents is used to create server selector.
    ///
    /// If the parsing choice is TAGS_FORBIDDEN:
    ///   - a "server-tags" parameter gives an error.
    ///   - no "server-tags" gives the ANY server selector.
    ///
    /// If the parsing choice is TAGS_OPTIONAL:
    ///   - no "server-tags" parameter gives the ANY server selector.
    ///   - empty "server-tags" parameter gives an error.
    ///   - "server-tags" parameter contents is used to create server selector.
    ///
    /// @param args Pointer to the command arguments.
    /// @param tags_parse Parsing choice for server-tags entry.
    /// @throw BadValue if server selector cannot be parsed following tags_parse.
    db::ServerSelector
    getServerSelector(const data::ConstElementPtr& args,
                      ServerTagsParse tags_parse) const;

    /// @brief Creates subnets action from the command's arguments.
    ///
    /// If the command arguments include "subnets-action" parameter we will
    /// use the contents of this parameter to create subnets action.
    /// Otherwise, we will return the default action (keep).
    ///
    /// @param args Pointer to the command arguments.
    SubnetsAction getSubnetsAction(const data::ConstElementPtr& args) const;

    //// @brief Common routine invoked when getting a subnet.
    ///
    /// Creates a response to the caller which includes the fetched subnet
    /// and appropriate control result.
    ///
    /// @tparam SubnetPtrType Type of the pointer to the retrieved subnet.
    /// @tparam KeyType Type of the key used to fetch the subnet.
    ///
    /// @param callout_handle Callout handle where response will be stored.
    /// @param subnet Instance of the fetched subnet or null if no subnet
    /// was found.
    /// @param address_family Address family.
    /// @param key Subnet property used for locating the subnet, e.g.
    /// subnet identifier or prefix.
    template<typename SubnetPtrType, typename KeyType>
    void getSubnetCommon(hooks::CalloutHandle& callout_handle,
                         const SubnetPtrType& subnet,
                         const uint16_t address_family,
                         const KeyType& key) {
        int rcode;
        std::ostringstream msg;
        msg << (address_family == AF_INET ? "IPv4" : "IPv6")
            << " subnet " << key << " ";
        data::ElementPtr info = data::Element::createMap();
        data::ElementPtr info_list = data::Element::createList();
        info->set("subnets", info_list);
        if (subnet) {
            rcode = config::CONTROL_RESULT_SUCCESS;
            data::ElementPtr subnet_element = subnet->toElement();

            // Always include shared network name.
            std::string sn_name = subnet->getSharedNetworkName();
            if (!sn_name.empty()) {
                subnet_element->set("shared-network-name",
                                    data::Element::create(sn_name));

            } else {
                // Shared network name is null.
                subnet_element->set("shared-network-name",
                                    data::Element::create());
            }

            // Include metadata with the subnet.
            subnet_element->set("metadata", subnet->getMetadata());

            info_list->add(subnet_element);
            msg << "found.";
        } else {
            rcode = config::CONTROL_RESULT_EMPTY;
            msg << "not found.";
        }
        info->set("count", data::Element::create(subnet ? 1 : 0));

        // Configuration backend didn't complain so let's return the success status.
        data::ConstElementPtr response =
            config::createAnswer(rcode, msg.str(), info);
        callout_handle.setArgument("response", response);
    }

    /// @brief Creates @c SubnetsInclude from the command's arguments.
    ///
    /// If teh command arguments include "subnets-include" parameter we will
    /// use the contents of this parameter we will use it to determine whether
    /// the subnets should be included in the response to the
    /// remote-network[46]-get command.
    ///
    /// @param args Pointer to the command arguments.
    SubnetsInclude getSubnetsInclude(const data::ConstElementPtr& args) const;
};

/// @brief Base class for the implementations of the callouts for
/// cb_cmds library for DHCPv4 and DHCPv6.
///
/// This class implements common code for callouts supported by
/// the cb_cmds hooks library.
class ConfigCmdsImpl {
public:

    /// @brief Constructor.
    ConfigCmdsImpl();

    /// @brief Implements handler for remote-global-parameter[46]-set
    /// command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param keywords Keywords of global parameters.
    /// @param list_keywords Keywords of global list parameters.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setGlobalParameter(hooks::CalloutHandle& callout_handle,
                            const data::SimpleKeywords& keywords,
                            const data::SimpleKeywords& list_keywords,
                            const uint16_t address_family,
                            FunType create_update_fun) {
        try {
            // Parse the command and store the data in the stamped_values object.
            data::StampedValueCollection stamped_values;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputMapElement
                <GlobalParameterParser, const data::SimpleKeywords&, const data::SimpleKeywords&>
                (callout_handle, "parameters", keywords, list_keywords,
                 stamped_values, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the global parameter setting.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-global-parameter"
                          << (address_family == AF_INET ? "4" : "6") << "-set'"
                          " command");
            }

            uint64_t count = 0;
            for (auto const& stamped_value : stamped_values) {
                // Pass the received global parameter into the configuration backend.
                create_update_fun(backend_selector, server_selector, stamped_value);
                ++count;
            }

            // Build response.
            data::ElementPtr parameters = data::Element::createMap();
            for (auto const& stamped_value : stamped_values) {
                std::string param_name;
                std::string sub_param_name;
                if (isc::dhcp::CBControlDHCP<bool>::translateName(stamped_value->getName(),
                                                                  param_name, sub_param_name)) {
                    data::ElementPtr sub_param = boost::const_pointer_cast<data::Element>(parameters->get(param_name));
                    if (!sub_param) {
                        sub_param = data::Element::createMap();
                        parameters->set(param_name, sub_param);
                    }
                    sub_param->set(sub_param_name, stamped_value->getElementValue());
                } else {
                    // Reuse name and value.
                    parameters->set(param_name, stamped_value->getElementValue());
                }
            }
            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("parameters", parameters);
            response_arguments->set("count",
                data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " global parameter(s) successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-global-parameter[46]-del
    /// command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param keywords Keywords of global parameters.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delGlobalParameter(hooks::CalloutHandle& callout_handle,
                            const data::SimpleKeywords& keywords,
                            const uint16_t address_family,
                            FunType delete_fun) {
        try {
            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement
                <GlobalParameterNameParser, const data::SimpleKeywords&>
                (callout_handle, "parameters", keywords, name,
                 backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED,
                 data::Element::string);

            // We allow exactly one server tag for the global parameter deleting..
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-global-parameter"
                          << (address_family == AF_INET ? "4" : "6") << "-del'"
                          " command");
            }

            // Pass the received global parameter into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_selector, name);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " global parameter(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-global-parameter[46]-get
    /// command.
    ///
    /// @tparam FunType Type of get method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param keywords Keywords of global parameters.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    template <typename FunType>
    void getGlobalParameter(hooks::CalloutHandle& callout_handle,
                            const data::SimpleKeywords& keywords,
                            const uint16_t address_family,
                            FunType get_fun) {
        try {
            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement
                <GlobalParameterNameParser, const data::SimpleKeywords&>
                (callout_handle, "parameters", keywords, name,
                 backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED,
                 data::Element::string);

            // We allow exactly one server tag for the global parameter getting.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-global-parameter"
                          << (address_family == AF_INET ? "4" : "6") << "-get'"
                          " command");
            }

            // Get the global parameter from the configuration backend.
            data::StampedValuePtr value =
                get_fun(backend_selector, server_selector, name);

            int rcode;
            std::ostringstream msg;
            msg << "'" << name;
            if (address_family == AF_INET) {
                msg << "' DHCPv4";
            } else {
                msg << "' DHCPv6";
            }
            msg << " global parameter ";
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_map = data::Element::createMap();
            info->set("parameters", info_map);
            if (value) {
                rcode = config::CONTROL_RESULT_SUCCESS;
                data::ConstElementPtr info_value = value->getElementValue();
                if (!info_value) {
                    isc_throw(InvalidOperation,
                              "StampedValue: attempt to get null value of the '"
                              << value->getName() << "' parameter");
                }
                auto const it = keywords.find(value->getName());
                if (it == keywords.end()) {
                    isc_throw(BadValue, "unknown parameter '" << value->getName() << "'");
                }
                if (it->second == data::Element::list) {
                    info_value = data::Element::fromJSON(info_value->stringValue());
                }
                std::string param_name;
                std::string sub_param_name;
                if (isc::dhcp::CBControlDHCP<bool>::translateName(value->getName(),
                                                                  param_name, sub_param_name)) {
                    data::ElementPtr sub_param = data::Element::createMap();
                    sub_param->set(sub_param_name, info_value);
                    info_map->set(param_name, sub_param);
                } else {
                    info_map->set(param_name, info_value);
                }
                info_map->set("metadata", value->getMetadata());
                msg << "found.";
            } else {
                rcode = config::CONTROL_RESULT_EMPTY;
                msg << "not found.";
            }
            info->set("count", data::Element::create(value ? 1 : 0));

            // Configuration backend didn't complain so let's return the success status.

            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-global-parameter[46]-get-all
    /// command.
    ///
    /// @tparam FunType Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param keywords List of keywords to accept.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_all_fun getAll method.
    template <typename FunType>
    void getAllGlobalParameters(hooks::CalloutHandle& callout_handle,
                                const data::SimpleKeywords& keywords,
                                const uint16_t address_family,
                                FunType get_all_fun) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Get arguments.
            data::ConstElementPtr args;
            static_cast<void>(config::parseCommandWithArgs(args, command));

            // Create backend and server selectors from the received arguments.
            // If the arguments do not include "remote" parameter, the default
            // (unspecified) backend selector is created.
            db::BackendSelector backend_selector;
            backend_selector = parser_->getBackendSelector(args);

            // The arguments must include "server-tags" parameter.
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            server_selector = parser_->getServerSelector(args,
                        ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the global parameter listing.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-global-parameter"
                          << (address_family == AF_INET ? "4" : "6") << "-get-all'"
                          " command");
            }

            // Get global parameters from the configuration backend.
            data::StampedValueCollection values =
                get_all_fun(backend_selector, server_selector);

            // Build response.
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("parameters", info_list);
            for (auto const& value : values) {
                data::ConstElementPtr info_value = value->getElementValue();
                if (!info_value) {
                    isc_throw(InvalidOperation,
                              "StampedValue: attempt to get null value of the '"
                              << value->getName() << "' parameter");
                }
                auto const it = keywords.find(value->getName());
                if (it == keywords.end()) {
                    isc_throw(BadValue, "unknown parameter '" << value->getName() << "'");
                }
                if (it->second == data::Element::list) {
                    info_value = data::Element::fromJSON(info_value->stringValue());
                }
                data::ElementPtr param = data::Element::createMap();
                std::string param_name;
                std::string sub_param_name;
                if (isc::dhcp::CBControlDHCP<bool>::translateName(value->getName(),
                                                                  param_name, sub_param_name)) {
                    data::ElementPtr sub_param = data::Element::createMap();
                    sub_param->set(sub_param_name, info_value);
                    param->set(param_name, sub_param);
                } else {
                    param->set(param_name, info_value);
                }
                param->set("metadata", value->getMetadata());
                info_list->add(param);
            }
            info->set("count",
                      data::Element::create(static_cast<long int>(values.size())));

            // Configuration backend didn't complain so let's return the success status.

            std::ostringstream msg;
            msg << values.size()
                << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " global parameter(s) found.";
            int rcode =
                (values.empty() ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-subnet[46]-set command.
    ///
    /// @tparam SubnetPtrType Type of shared pointers to subnets
    /// (@c dhcp::Subnet4Ptr or @c dhcp::Subnet6Ptr).
    /// @tparam SubnetConfigParser Subnet configuration parser
    /// (@c CBSubnet4ConfigParser or @c CBSubnet6ConfigParser).
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename SubnetPtrType, typename SubnetConfigParser, typename FunType>
    void setSubnet(hooks::CalloutHandle& callout_handle,
                   const uint16_t address_family,
                   FunType create_update_fun) {
        try {
            // Parse the command and store the subnet data in the subnet object.
            SubnetPtrType subnet;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<SubnetConfigParser, db::BackendSelector&,
                                           db::ServerSelector&>
                (callout_handle, "subnets", backend_selector, server_selector,
                 subnet, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow one or more server tags for the subnet setting.
            if (server_selector.hasNoTags()) {
                isc_throw(BadValue,
                          "'server-tags' list must contain one or more"
                          " server tags for the 'remote-subnet"
                          << (address_family == AF_INET ? "4" : "6") << "-set'"
                          " command");
            }

            // Pass the received subnet into the configuration backend.
            create_update_fun(backend_selector, server_selector, subnet);

            // The response contains subnet prefix and subnet id.
            data::ElementPtr subnet_info = data::Element::createMap();
            subnet_info->set("id",
                             data::Element::create(static_cast<long int>(subnet->getID())));
            subnet_info->set("subnet",
                             data::Element::create(subnet->toText()));

            // The subnet information is encapsulated in a single element list.
            data::ElementPtr subnets_list = data::Element::createList();
            subnets_list->add(subnet_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("subnets", subnets_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "IPv4" : "IPv6")
                << " subnet successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-subnet[46]-del-by-id
    /// command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delSubnetId(hooks::CalloutHandle& callout_handle,
                     const uint16_t address_family,
                     FunType delete_fun) {
        try {
            dhcp::SubnetID subnet_id;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBSubnetIdParser>
              (callout_handle, "subnets", subnet_id, backend_selector,
               server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Pass the received subnet into the configuration backend.
            uint64_t count =
                delete_fun(backend_selector, server_selector, subnet_id);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " IPv4" : " IPv6")
                << " subnet(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-subnet[46]-del-by-prefix
    /// command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delSubnetPrefix(hooks::CalloutHandle& callout_handle,
                         const uint16_t address_family,
                         FunType delete_fun) {
        try {
            std::string prefix;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement
                <CBSubnetPrefixParser, uint16_t>
                (callout_handle, "subnets", address_family,
                 prefix, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Pass the received subnet into the configuration backend.
            uint64_t count =
                delete_fun(backend_selector, server_selector, prefix);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " IPv4" : " IPv6")
                << " subnet(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-subnet[46]-get-by-id
    /// command.
    ///
    /// @tparam SubnetPtrType Type of shared pointers to subnets
    /// (@c dhcp::Subnet4Ptr or @c dhcp::Subnet6Ptr).
    /// @tparam FunType Type of get method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    template <typename SubnetPtrType, typename FunType>
    void getSubnetId(hooks::CalloutHandle& callout_handle,
                     const uint16_t address_family,
                     FunType get_fun) {
        try {
            dhcp::SubnetID subnet_id;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBSubnetIdParser>
              (callout_handle, "subnets", subnet_id, backend_selector,
               server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Get the subnet from the configuration backend.
            SubnetPtrType subnet =
                get_fun(backend_selector, server_selector, subnet_id);

            // Invoke common routine to prepare the appropriate response.
            parser_->getSubnetCommon(callout_handle, subnet, address_family, subnet_id);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-subnet[46]-get-by-prefix
    /// command.
    ///
    /// @tparam SubnetPtrType Type of shared pointers to subnets
    /// (@c dhcp::Subnet4Ptr or @c dhcp::Subnet6Ptr).
    /// @tparam FunType Type of get method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    template <typename SubnetPtrType, typename FunType>
    void getSubnetPrefix(hooks::CalloutHandle& callout_handle,
                         const uint16_t address_family,
                         FunType get_fun) {
        try {
            std::string prefix;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement
                <CBSubnetPrefixParser, uint16_t>
                (callout_handle, "subnets", address_family,
                 prefix, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Get the subnet from the configuration backend.
            SubnetPtrType subnet =
                get_fun(backend_selector, server_selector, prefix);

            // Invoke common routine to prepare the appropriate response.
            parser_->getSubnetCommon(callout_handle, subnet,
                                     address_family, prefix);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-subnet[46]-list command.
    ///
    /// @tparam SubnetCollection Type of collection of subnet pointers
    /// (@c dhcp::Subnet4Collection or @c dhcp::Subnet6Collection).
    /// @tparam FunType Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_all_fun getAll method.
    template <typename SubnetCollection, typename FunType>
    void listSubnets(hooks::CalloutHandle& callout_handle,
                     const uint16_t address_family,
                     FunType get_all_fun) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Get arguments.
            data::ConstElementPtr args;
            static_cast<void>(config::parseCommandWithArgs(args, command));

            // Create backend selector from the received arguments.
            // If the arguments do not include "remote" parameter,
            // the default (unspecified) backend selector is created.
            db::BackendSelector backend_selector;
            backend_selector = parser_->getBackendSelector(args);

            // The arguments must include "server-tags" parameter.
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            server_selector = parser_->getServerSelector(args,
                        ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // Get the subnet list from the configuration backend.
            SubnetCollection subnets =
                get_all_fun(backend_selector, server_selector);

            // Build response.
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("subnets", info_list);
            for (auto const& subnet : subnets) {
                data::ElementPtr subnet_info = data::Element::createMap();
                subnet_info->set("id",
                                 data::Element::create(static_cast<long int>(subnet->getID())));
                subnet_info->set("subnet",
                                 data::Element::create(subnet->toText()));

                // Shared network name.
                std::string sn_name = subnet->getSharedNetworkName();
                if (!sn_name.empty()) {
                    subnet_info->set("shared-network-name",
                                     data::Element::create(sn_name));
                } else {
                    // Shared network name is null.
                    subnet_info->set("shared-network-name",
                                     data::Element::create());
                }

                // Include metadata.
                subnet_info->set("metadata", subnet->getMetadata());

                info_list->add(subnet_info);
            }
            info->set("count",
                      data::Element::create(static_cast<long int>(subnets.size())));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << subnets.size()
                << (address_family == AF_INET ? " IPv4" : " IPv6")
                << " subnet(s) found.";
            int rcode =
                (subnets.empty() ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-shared-network[46]-set command.
    ///
    /// @tparam SharedNetworkPtrType Type of shared pointers to shared networks
    /// (@c dhcp::SharedNetwork4Ptr or @c dhcp::SharedNetwork6Ptr).
    /// @tparam SharedNetworkParser Subnet configuration parser
    /// (@c CBSharedNetwork4Parser or @c CBSharedNetwork6Parser).
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename SharedNetworkPtrType, typename SharedNetworkParser, typename FunType>
    void setSharedNetwork(hooks::CalloutHandle& callout_handle,
                          const uint16_t address_family,
                          FunType create_update_fun) {
        try {
            // Parse the command and store the shared network data in
            // the shared_network object.
            SharedNetworkPtrType shared_network;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<SharedNetworkParser, db::BackendSelector&,
                                           db::ServerSelector&>
                (callout_handle, "shared-networks", backend_selector, server_selector,
                 shared_network, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow one or more server tags for the shared network setting.
            if (server_selector.hasNoTags()) {
                isc_throw(BadValue,
                          "'server-tags' list must contain one or more"
                          " server tags for the 'remote-network"
                          << (address_family == AF_INET ? "4" : "6") << "-set'"
                          " command");
            }

            // Pass the received shared network into the configuration backend.
            create_update_fun(backend_selector, server_selector, shared_network);

            // The response contains a network name.
            data::ElementPtr network_info = data::Element::createMap();
            network_info->set("name",
                              data::Element::create(shared_network->getName()));

            // The network information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(network_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("shared-networks", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "IPv4" : "IPv6");
            msg << " shared network successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-shared-network[46]-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @tparam FunType2 Type of deleteAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    /// @param delete_all_fun deleteAll method.
    template <typename FunType, typename FunType2>
    void delSharedNetwork(hooks::CalloutHandle& callout_handle,
                          const uint16_t address_family,
                          FunType delete_fun, FunType2 delete_all_fun) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Get optional arguments.
            data::ConstElementPtr args;

            // Create subnets action from the received arguments.
            // If the arguments do not include "subnets-action" parameter,
            // the default (keep) action is created.
            static_cast<void>(config::parseCommandWithArgs(args, command));
            auto subnets_action = parser_->getSubnetsAction(args);

            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBSharedNetworkNameParser>
                (callout_handle, "shared-networks", name, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Delete subnets when wanted.
            if (subnets_action == ConfigCmdsParser::SubnetsAction::ACTION_DELETE) {
                delete_all_fun(backend_selector, server_selector, name);
            }

            // Pass the received shared network into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_selector, name);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " IPv4" : " IPv6");
            msg << " shared network(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-shared-network[46]-get command.
    ///
    /// @tparam SharedNetworkPtrType Type of shared pointers to shared networks
    /// (@c dhcp::SharedNetwork4Ptr or @c dhcp::SharedNetwork6Ptr).
    /// @tparam SubnetCollection Type of collection of subnet pointers
    /// (@c dhcp::Subnet4Collection or @c dhcp::Subnet6Collection).
    /// @tparam FunType Type of get method.
    /// @tparam FunType2 Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    /// @param get_all getAll method.
    template <typename SharedNetworkPtrType, typename SubnetCollection,
        typename FunType, typename FunType2>
    void getSharedNetwork(hooks::CalloutHandle& callout_handle,
                          const uint16_t address_family,
                          FunType get_fun, FunType2 get_all) {
        try {
            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            auto args =
                parser_->parseInputListElement<CBSharedNetworkNameParser>
                (callout_handle, "shared-networks", name, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Get the flag which denotes whether we should include subnets
            // in the response or not.
            auto subnets_include = parser_->getSubnetsInclude(args);

            // Get the shared network from the configuration backend.
            SharedNetworkPtrType network =
                get_fun(backend_selector, server_selector, name);

            // Get all subnets belonging to the shared network
            // when none was returned from the database.
            if ((subnets_include == ConfigCmdsParser::SubnetsInclude::INCLUDE_FULL) &&
                network && network->getAllSubnets()->empty()) {
                SubnetCollection subnets =
                    get_all(backend_selector, server_selector, name);
                for (auto const& subnet : subnets) {
                    network->add(subnet);
                }
            }

            int rcode;
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("shared-networks", info_list);;
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "IPv4" : "IPv6");
            msg << " shared network '" << name << "' ";
            if (network) {
                rcode = config::CONTROL_RESULT_SUCCESS;

                // If we're not supposed to include subnets in the response,
                // remove them. In case the backend returned them.
                data::ElementPtr network_element = network->toElement();
                if (subnets_include == ConfigCmdsParser::SubnetsInclude::INCLUDE_NO) {
                    if (address_family == AF_INET) {
                        network_element->remove("subnet4");
                    } else {
                        network_element->remove("subnet6");
                    }
                }

                // Include metadata.
                network_element->set("metadata", network->getMetadata());

                info_list->add(network_element);
                msg << "found.";
            } else {
                rcode = config::CONTROL_RESULT_EMPTY;
                msg << "not found.";
            }
            info->set("count", data::Element::create(network ? 1 : 0));

            // Configuration backend didn't complain so let's return the success status.
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-shared-network[46]-list command.
    ///
    /// @tparam SharedNetworkCollection Type of collection of shared
    /// network pointers (@c dhcp::SharedNetwork4Collection or
    /// @c dhcp::SharedNetwork6Collection).
    /// @tparam FunType Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_all getAll method.
    template <typename SharedNetworkCollection, typename FunType>
    void listSharedNetworks(hooks::CalloutHandle& callout_handle,
                            const uint16_t address_family,
                            FunType get_all) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Expect that the command include arguments.
            data::ConstElementPtr args;
            static_cast<void>(config::parseCommandWithArgs(args, command));

            // Create backend selector from the received arguments.
            // If the arguments do not include "remote" parameter,
            // the default (unspecified) backend selector is created.
            db::BackendSelector backend_selector;
            backend_selector = parser_->getBackendSelector(args);

            // The arguments must include "server-tags" parameter.
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            server_selector = parser_->getServerSelector(args,
                        ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // Get shared networks from the configuration backend.
            SharedNetworkCollection networks =
                get_all(backend_selector, server_selector);

            // Build response.
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("shared-networks", info_list);
            for (auto const& network : networks) {
                data::ElementPtr network_map = data::Element::createMap();
                network_map->set("name",
                                 data::Element::create(network->getName()));
                network_map->set("metadata", network->getMetadata());
                info_list->add(network_map);
            }
            info->set("count",
                      data::Element::create(static_cast<long int>(networks.size())));

            // Configuration backend didn't complain so let's return the success status.

            std::ostringstream msg;
            msg << networks.size();
            msg << (address_family == AF_INET ? " IPv4" : " IPv6");
            msg << " shared network(s) found.";
            int rcode =
                (networks.empty() ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-class[46]-set command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setClientClass(hooks::CalloutHandle& callout_handle,
                        const uint16_t address_family,
                        FunType create_update_fun) {
        try {
            std::pair<dhcp::ClientClassDefPtr, std::string> class_pair;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBClientClassParser, uint16_t, dhcp::CfgOptionDefPtr,
                                           db::BackendSelector&, db::ServerSelector&>
                (callout_handle, "client-classes", address_family, CfgOptionDefPtr(),
                 backend_selector, server_selector,
                 class_pair, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow one or more server tags for the client class setting.
            if (server_selector.hasNoTags()) {
                isc_throw(BadValue,
                          "'server-tags' list must contain one or more"
                          " server tags for the 'remote-class"
                          << (address_family == AF_INET ? "4" : "6") << "-set'"
                          " command");
            }

            // Pass the received shared network into the configuration backend.
            create_update_fun(backend_selector, server_selector, class_pair.first,
                              class_pair.second);

            // The response contains a network name.
            data::ElementPtr client_class_info = data::Element::createMap();
            client_class_info->set("name",
                                   data::Element::create(class_pair.first->getName()));

            // The client class information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(client_class_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("client-classes", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6");
            msg << " client class successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-class[46]-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delClientClass(hooks::CalloutHandle& callout_handle,
                        const uint16_t address_family,
                        FunType delete_fun) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBClientClassNameParser>
                (callout_handle, "client-classes", name, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Pass the received client class into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_selector, name);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6");
            msg << " client class(es) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-class[46]-get command.
    ///
    /// @tparam FunType Type of get method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    template <typename FunType>
    void getClientClass(hooks::CalloutHandle& callout_handle,
                        const uint16_t address_family,
                        FunType get_fun) {
        try {
            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            auto args =
                parser_->parseInputListElement<CBClientClassNameParser>
                (callout_handle, "client-classes", name, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Get the client class from the configuration backend.
            ClientClassDefPtr client_class = get_fun(backend_selector, server_selector, name);

            int rcode;
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("client-classes", info_list);;
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6");
            msg << " client class '" << name << "' ";
            if (client_class) {
                rcode = config::CONTROL_RESULT_SUCCESS;

                data::ElementPtr client_class_element = client_class->toElement();

                // Include metadata.
                client_class_element->set("metadata", client_class->getMetadata());

                info_list->add(client_class_element);
                msg << "found.";
            } else {
                rcode = config::CONTROL_RESULT_EMPTY;
                msg << "not found.";
            }
            info->set("count", data::Element::create(client_class ? 1 : 0));

            // Configuration backend didn't complain so let's return the success status.
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-class[46]-get-all command.
    ///
    /// @tparam FunType Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_all getAll method.
    template <typename FunType>
    void getAllClientClasses(hooks::CalloutHandle& callout_handle,
                             const uint16_t address_family,
                             FunType get_all) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Expect that the command includes arguments.
            data::ConstElementPtr args;
            static_cast<void>(config::parseCommandWithArgs(args, command));

            // Create backend selector from the received arguments.
            // If the arguments do not include "remote" parameter,
            // the default (unspecified) backend selector is created.
            db::BackendSelector backend_selector;
            backend_selector = parser_->getBackendSelector(args);

            // The arguments must include "server-tags" parameter.
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            server_selector = parser_->getServerSelector(args,
                        ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // Get client classes from the configuration backend.
            ClientClassDictionary client_classes = get_all(backend_selector, server_selector);

            // Build response.
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("client-classes", info_list);
            for (auto const& client_class : *client_classes.getClasses()) {
                data::ElementPtr client_class_map = client_class->toElement();
                client_class_map->set("metadata", client_class->getMetadata());
                info_list->add(client_class_map);
            }
            info->set("count",
                      data::Element::create(static_cast<long int>(client_classes.getClasses()->size())));

            // Configuration backend didn't complain so let's return the success status.

            std::ostringstream msg;
            msg << client_classes.getClasses()->size();
            msg << (address_family == AF_INET ? " DHCPv4" : " DHCPv6");
            msg << " client class(es) found.";
            int rcode =
                (client_classes.empty() ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option-def[46]-set command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setOptionDef(hooks::CalloutHandle& callout_handle,
                      const uint16_t address_family,
                      FunType create_update_fun) {
        try {
            // Parse the command and store the option definition data
            // in the option_def object.
            dhcp::OptionDefinitionPtr option_def;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBOptionDefParser, uint16_t>
                (callout_handle, "option-defs", address_family,
                 option_def, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option definition setting.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option-def"
                          << (address_family == AF_INET ? "4" : "6") << "-set'"
                          " command");
            }

            // Pass the received option definition into the configuration backend.
            create_update_fun(backend_selector, server_selector, option_def);

            // The response contains option code, space, and client classes.
            auto option_def_info = makeOptionInfoElement(*option_def);

            // The option definition information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(option_def_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("option-defs", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " option definition successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option-def[46]-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delOptionDef(hooks::CalloutHandle& callout_handle,
                      const uint16_t address_family,
                      FunType delete_fun) {
        try {
            CBOptionDefDelete option_def_delete;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBOptionDefDeleteParser, uint16_t>
                (callout_handle, "option-defs", address_family,
                 option_def_delete, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option definition deleting.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option-def"
                          << (address_family == AF_INET ? "4" : "6") << "-del'"
                          " command");
            }

            // Pass the received option definition into the configuration backend.
            uint64_t count =
                delete_fun(backend_selector, server_selector,
                           std::get<0>(option_def_delete),
                           std::get<1>(option_def_delete),
                           std::get<2>(option_def_delete));

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                 << " option definition(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option-def[46]-get command.
    ///
    /// @tparam FunType Type of get method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    template <typename FunType>
    void getOptionDef(hooks::CalloutHandle& callout_handle,
                      const uint16_t address_family,
                      FunType get_fun) {
        try {
            std::pair<uint16_t, std::string> option_def_pair;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBOptionPairParser, uint16_t>
                (callout_handle, "option-defs", address_family,
                 option_def_pair, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option definition getting.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option-def"
                          << (address_family == AF_INET ? "4" : "6") << "-get'"
                          " command");
            }

            // Get the option definition from the configuration backend.
            dhcp::OptionDefinitionPtr def =
                get_fun(backend_selector, server_selector,
                        option_def_pair.first, option_def_pair.second);

            int rcode;
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " option definition " << option_def_pair.first
                << " in '" << option_def_pair.second << "' ";
            data::ElementPtr info = data::Element::createMap();
            if (def) {
                rcode = config::CONTROL_RESULT_SUCCESS;
                dhcp::CfgOptionDefPtr defs(new dhcp::CfgOptionDef());
                defs->add(def);
                info->set("option-defs", defs->toElementWithMetadata(true));
                msg << "found.";
            } else {
                rcode = config::CONTROL_RESULT_EMPTY;
                data::ElementPtr info_list = data::Element::createList();
                info->set("option-defs", info_list);
                msg << "not found.";
            }
            info->set("count", data::Element::create(def ? 1 : 0));

            // Configuration backend didn't complain so let's return the success status.
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option-def[46]-get-all command.
    ///
    /// @tparam FunType Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_all_fun getAll method.
    template <typename FunType>
    void getAllOptionDefs(hooks::CalloutHandle& callout_handle,
                          const uint16_t address_family,
                          FunType get_all_fun) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Get arguments.
            data::ConstElementPtr args;
            static_cast<void>(config::parseCommandWithArgs(args, command));

            // Create backend selector from the received arguments.
            // If the arguments do not include "remote" parameter,
            // the default (unspecified) backend selector is created.
            db::BackendSelector backend_selector;
            backend_selector = parser_->getBackendSelector(args);

            // The arguments must include "server-tags" parameter.
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            server_selector = parser_->getServerSelector(args,
                        ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option definition listing.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option-def"
                          << (address_family == AF_INET ? "4" : "6") << "-get-all'"
                          " command");
            }

            // Get option definitions from the configuration backend.
            dhcp::OptionDefContainer defs =
                get_all_fun(backend_selector, server_selector);

            // Build response.
            data::ElementPtr info = data::Element::createMap();
            dhcp::CfgOptionDefPtr cfg_defs(new dhcp::CfgOptionDef());
            for (auto const& def : defs) {
                cfg_defs->add(def);
            }
            info->set("option-defs", cfg_defs->toElementWithMetadata(true));
            info->set("count",
                      data::Element::create(static_cast<long int>(defs.size())));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << defs.size()
                << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " option definition(s) found.";
            int rcode =
                (defs.empty() ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-global-set command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setGlobalOption(hooks::CalloutHandle& callout_handle,
                         const uint16_t address_family,
                         FunType create_update_fun) {
        try {
            // Parse the command and store the option data in
            // the option_pair object.
            std::pair<dhcp::OptionDescriptor, std::string> option_pair =
                std::make_pair(dhcp::OptionDescriptor(false, false), "");
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement
                <CBOptionDataParser, uint16_t, CfgOptionDefPtr, db::BackendSelector&,
                 db::ServerSelector&>
                (callout_handle, "options", address_family, CfgOptionDefPtr(),
                 backend_selector, server_selector,
                 option_pair, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option setting.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option"
                          << (address_family == AF_INET ? "4" : "6")
                          << "-global-set' command");
            }

            auto option_descriptor = option_pair.first;
            option_descriptor.space_name_ = option_pair.second;

            // Pass the received option into the configuration backend.
            create_update_fun(backend_selector, server_selector, option_descriptor);

            // The response contains option code, space, and client classes.
            auto option_info = makeOptionInfoElement(option_descriptor);

            // The option information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(option_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("options", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " option successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-global-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delGlobalOption(hooks::CalloutHandle& callout_handle,
                         const uint16_t address_family,
                         FunType delete_fun) {
        try {
            CBOptionTuple option_tuple;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBOptionTupleParser, uint16_t>
                (callout_handle, "options", address_family,
                 option_tuple, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option deleting..
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option"
                          << (address_family == AF_INET ? "4" : "6")
                          << "-global-del' command");
            }

            // Pass the received option into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_selector,
                                        std::get<0>(option_tuple),
                                        std::get<1>(option_tuple),
                                        std::get<2>(option_tuple));

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " option(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-global-get command.
    ///
    /// @tparam FunType Type of get method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    template <typename FunType>
    void getGlobalOption(hooks::CalloutHandle& callout_handle,
                         const uint16_t address_family,
                         FunType get_fun) {
        try {
            CBOptionTuple option_tuple;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBOptionTupleParser, uint16_t>
                (callout_handle, "options", address_family,
                 option_tuple, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option getting.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option"
                          << (address_family == AF_INET ? "4" : "6")
                          << "-global-get' command");
            }

            // Get the option from the configuration backend.
            dhcp::OptionDescriptorPtr option =
                get_fun(backend_selector, server_selector,
                        std::get<0>(option_tuple),
                        std::get<1>(option_tuple),
                        std::get<2>(option_tuple));

            int rcode;
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " option " << std::get<0>(option_tuple);

            auto cclasses = std::get<2>(option_tuple);
            if (cclasses) {
                msg << " with client-classes = " << cclasses->toElement()->str();
            }

            msg << " in '" << std::get<1>(option_tuple) << "' ";

            data::ElementPtr info = data::Element::createMap();
            if (option) {
                rcode = config::CONTROL_RESULT_SUCCESS;
                dhcp::CfgOptionPtr options(new dhcp::CfgOption());
                options->add(*option, std::get<1>(option_tuple));
                info->set("options", options->toElementWithMetadata(true));
                msg << "found.";
            } else {
                rcode = config::CONTROL_RESULT_EMPTY;
                data::ElementPtr info_list = data::Element::createList();
                info->set("options", info_list);
                msg << "not found.";
            }
            info->set("count", data::Element::create(option ? 1 : 0));

            // Configuration backend didn't complain so let's return the success status.
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

    } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-global-get-all
    /// command.
    ///
    /// @tparam FunType Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_all_fun getAll method.
    template <typename FunType>
    void getAllGlobalOptions(hooks::CalloutHandle& callout_handle,
                             const uint16_t address_family,
                             FunType get_all_fun) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Get arguments.
            data::ConstElementPtr args;
            static_cast<void>(config::parseCommandWithArgs(args, command));

            // Create backend selector from the received arguments.
            // If the arguments do not include "remote" parameter,
            // the default (unspecified) backend selector is created.
            db::BackendSelector backend_selector;
            backend_selector = parser_->getBackendSelector(args);

            // The arguments must include "server-tags" parameter.
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            server_selector = parser_->getServerSelector(args,
                        ConfigCmdsParser::ServerTagsParse::TAGS_REQUIRED);

            // We allow exactly one server tag for the option listing.
            if (server_selector.getTags().size() != 1) {
                isc_throw(BadValue,
                          "'server-tags' list must contain exactly one"
                          " server tag for the 'remote-option"
                          << (address_family == AF_INET ? "4" : "6")
                          << "-global-get-all' command");
            }

            // Get options from the configuration backend.
            const dhcp::OptionContainer& options =
                get_all_fun(backend_selector, server_selector);

            // Build response.
            data::ElementPtr info = data::Element::createMap();
            dhcp::CfgOptionPtr cfg_options(new dhcp::CfgOption());
            for (auto const& option : options) {
                cfg_options->add(option, option.space_name_);
            }
            info->set("options", cfg_options->toElementWithMetadata(true));
            info->set("count",
                      data::Element::create(static_cast<long int>(options.size())));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << options.size()
                << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " option(s) found.";
            int rcode =
                (options.empty() ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-server[46]-set command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setServer(hooks::CalloutHandle& callout_handle,
                   const uint16_t address_family,
                   FunType create_update_fun) {
        try {
            // Parse the command and store the server data in the server object.
            db::ServerPtr server;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<ServerConfigParser>
                (callout_handle, "servers", server,
                 backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Pass the received server into the configuration backend.
            create_update_fun(backend_selector, server);

            // The server information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(server->toElement());

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("servers", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " server successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-server[46]-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delServer(hooks::CalloutHandle& callout_handle,
                   const uint16_t address_family,
                   FunType delete_fun) {
        try {
            data::ServerTag server_tag;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<ServerTagParser>
                (callout_handle, "servers", server_tag,
                 backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Pass the received server tag into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_tag);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " server(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-server[46]-get command.
    ///
    /// @tparam FunType Type of get method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_fun get method.
    template <typename FunType>
    void getServer(hooks::CalloutHandle& callout_handle,
                   const uint16_t address_family,
                   FunType get_fun) {
        try {
            data::ServerTag server_tag;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<ServerTagParser>
                (callout_handle, "servers", server_tag,
                 backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Get the server from the configuration backend.
            db::ServerPtr server = get_fun(backend_selector, server_tag);

            int rcode;
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " server '" << server_tag.get() << "' ";
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("servers", info_list);
            if (server) {
                rcode = config::CONTROL_RESULT_SUCCESS;
                msg << "found.";

                info_list->add(server->toElement());
            } else {
                rcode = config::CONTROL_RESULT_EMPTY;
                msg << "not found.";
            }
            info->set("count", data::Element::create(server ? 1 : 0));

            // Configuration backend didn't complain so let's return the success status.
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

    } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-server[46]-get-all
    /// command.
    ///
    /// @tparam FunType Type of getAll method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param get_all_fun getAll method.
    template <typename FunType>
    void getAllServers(hooks::CalloutHandle& callout_handle,
                       const uint16_t address_family,
                       FunType get_all_fun) {
        try {
            // Retrieve the command from the callout handle.
            data::ConstElementPtr command;
            callout_handle.getArgument("command", command);

            // Get arguments.
            data::ConstElementPtr args;
            static_cast<void>(config::parseCommand(args, command));

            // Create backend selector from the received arguments.
            // If the arguments do not include "remote" parameter,
            // the default (unspecified) backend selector is created.
            db::BackendSelector backend_selector;
            if (args) {
                static_cast<void>(config::parseCommandWithArgs(args, command));
                backend_selector = parser_->getBackendSelector(args);
            }

            // The arguments must not include "server-tags" parameter.
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            if (args && args->contains("server-tags")) {
                isc_throw(BadValue, "'server-tags' is forbidden in this command");
            }

            // Get servers from the configuration backend.
            db::ServerCollection servers = get_all_fun(backend_selector);

            // Build response.
            data::ElementPtr info = data::Element::createMap();
            data::ElementPtr info_list = data::Element::createList();
            info->set("servers", info_list);
            for (auto const& server : servers) {
                info_list->add(server->toElement());
            }
            info->set("count",
                      data::Element::create(static_cast<long int>(servers.size())));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << servers.size()
                << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " server(s) found.";
            int rcode =
                (servers.empty() ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), info);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-network-set command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setSharedNetworkOption(hooks::CalloutHandle& callout_handle,
                                const uint16_t address_family,
                                FunType create_update_fun) {
        try {
            // Parse the command and store the shared network name.
            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBSharedNetworkNameParser>
                (callout_handle, "shared-networks", name, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Parse again the command and store the option data in
            // the option_pair object.
            std::pair<dhcp::OptionDescriptor, std::string> option_pair =
                std::make_pair(dhcp::OptionDescriptor(false, false), "");
            parser_->parseInputListElement
                <CBOptionDataParser, uint16_t, dhcp::CfgOptionDefPtr, db::BackendSelector&,
                 db::ServerSelector&>
                (callout_handle, "options", address_family, CfgOptionDefPtr(),
                 backend_selector, server_selector, option_pair);

            auto option_descriptor = option_pair.first;
            option_descriptor.space_name_ = option_pair.second;

            // Pass the received arguments into the configuration backend.
            create_update_fun(backend_selector, server_selector,
                              name, option_descriptor);

            auto option_info = makeOptionInfoElement(option_descriptor);

            // The option information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(option_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("options", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " option successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-network-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delSharedNetworkOption(hooks::CalloutHandle& callout_handle,
                                const uint16_t address_family,
                                FunType delete_fun) {
        try {
            // Parse the command and store the shared network name.
            std::string name;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBSharedNetworkNameParser>
                (callout_handle, "shared-networks", name, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Parse again the command and store the option code/space/client classes tuple.
            CBOptionTuple option_tuple;
            parser_->parseInputListElement<CBOptionTupleParser, uint16_t>
                (callout_handle, "options", address_family, option_tuple);

            // Pass the received arguments into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_selector,
                                        name,
                                        std::get<0>(option_tuple),
                                        std::get<1>(option_tuple),
                                        std::get<2>(option_tuple));

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " option(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-subnet-set command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setSubnetOption(hooks::CalloutHandle& callout_handle,
                         const uint16_t address_family,
                         FunType create_update_fun) {
        try {
            // Parse the command and store the subnet id.
            dhcp::SubnetID subnet_id;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBSubnetIdParser>
                (callout_handle, "subnets", subnet_id, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Parse again the command and store the option data in
            // the option_pair object.
            std::pair<dhcp::OptionDescriptor, std::string> option_pair =
                std::make_pair(dhcp::OptionDescriptor(false, false), "");
            parser_->parseInputListElement
                <CBOptionDataParser, uint16_t, dhcp::CfgOptionDefPtr, db::BackendSelector&,
                 db::ServerSelector&>
                (callout_handle, "options", address_family, CfgOptionDefPtr(),
                 backend_selector, server_selector, option_pair);

            auto option_descriptor = option_pair.first;
            option_descriptor.space_name_ = option_pair.second;

            // Pass the received arguments into the configuration backend.
            create_update_fun(backend_selector, server_selector,
                              subnet_id, option_descriptor);

            // The response contains option code, space, and client classes.
            auto option_info = makeOptionInfoElement(option_descriptor);

            // The option information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(option_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("options", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " option successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-subnet-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delSubnetOption(hooks::CalloutHandle& callout_handle,
                         const uint16_t address_family,
                         FunType delete_fun) {
        try {
            // Parse the command and store the subnet id.
            dhcp::SubnetID subnet_id;
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBSubnetIdParser>
                (callout_handle, "subnets", subnet_id, backend_selector,
                 server_selector, ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Parse again the command and store the option code/space/client classes tuple.
            CBOptionTuple option_tuple;
            parser_->parseInputListElement<CBOptionTupleParser, uint16_t>
                (callout_handle, "options", address_family, option_tuple);

            // Pass the received arguments into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_selector,
                                        subnet_id,
                                        std::get<0>(option_tuple),
                                        std::get<1>(option_tuple),
                                        std::get<2>(option_tuple));

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " option(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-pool-set command.
    ///
    /// @tparam FunType Type of createUpdate method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param create_update_fun createUpdate method.
    template <typename FunType>
    void setPoolOption(hooks::CalloutHandle& callout_handle,
                       const uint16_t address_family,
                       FunType create_update_fun) {
        try {
            // Parse the command and store the pool range.
            std::pair<asiolink::IOAddress, asiolink::IOAddress> pool_range =
                (address_family == AF_INET ?
                 std::make_pair(asiolink::IOAddress::IPV4_ZERO_ADDRESS(),
                                asiolink::IOAddress::IPV4_ZERO_ADDRESS()) :
                 std::make_pair(asiolink::IOAddress::IPV6_ZERO_ADDRESS(),
                                asiolink::IOAddress::IPV6_ZERO_ADDRESS()));
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBPoolRangeParser, uint16_t>
                (callout_handle, "pools", address_family,
                 pool_range, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Parse again the command and store the option data in
            // the option_pair object.
            std::pair<dhcp::OptionDescriptor, std::string> option_pair =
                std::make_pair(dhcp::OptionDescriptor(false, false), "");
            parser_->parseInputListElement<
                CBOptionDataParser, uint16_t, dhcp::CfgOptionDefPtr, db::BackendSelector&,
                db::ServerSelector&>
                (callout_handle, "options", address_family, CfgOptionDefPtr(),
                 backend_selector, server_selector, option_pair);

            auto option_descriptor = option_pair.first;
            option_descriptor.space_name_ = option_pair.second;

            // Pass the received arguments into the configuration backend.
            create_update_fun(backend_selector, server_selector,
                              pool_range.first, pool_range.second,
                              option_descriptor);

            // The response contains option code, space, and client classes.
            auto option_info = makeOptionInfoElement(option_descriptor);

            // The option information is encapsulated in a single element list.
            data::ElementPtr response_list = data::Element::createList();
            response_list->add(option_info);

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("options", response_list);

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << (address_family == AF_INET ? "DHCPv4" : "DHCPv6")
                << " option successfully set.";
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                     msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Implements handler for remote-option[46]-pool-del command.
    ///
    /// @tparam FunType Type of delete method.
    /// @param callout_handle Callout handle provided to the callout.
    /// @param address_family Address family (AF_INET or AF_INET6).
    /// @param delete_fun delete method.
    template <typename FunType>
    void delPoolOption(hooks::CalloutHandle& callout_handle,
                       const uint16_t address_family,
                       FunType delete_fun) {
        try {
            // Parse the command and store the pool range.
            std::pair<asiolink::IOAddress, asiolink::IOAddress> pool_range =
                (address_family == AF_INET ?
                 std::make_pair(asiolink::IOAddress::IPV4_ZERO_ADDRESS(),
                                asiolink::IOAddress::IPV4_ZERO_ADDRESS()) :
                 std::make_pair(asiolink::IOAddress::IPV6_ZERO_ADDRESS(),
                                asiolink::IOAddress::IPV6_ZERO_ADDRESS()));
            db::BackendSelector backend_selector;
            db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
            parser_->parseInputListElement<CBPoolRangeParser, uint16_t>
                (callout_handle, "pools", address_family,
                 pool_range, backend_selector, server_selector,
                 ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

            // Parse again the command and store the option code/space/client classes tuple.
            CBOptionTuple option_tuple;
            parser_->parseInputListElement<CBOptionTupleParser, uint16_t>
                (callout_handle, "options", address_family, option_tuple);

            // Pass the received arguments into the configuration backend.
            uint64_t count = delete_fun(backend_selector, server_selector,
                                        pool_range.first, pool_range.second,
                                        std::get<0>(option_tuple),
                                        std::get<1>(option_tuple),
                                        std::get<2>(option_tuple));

            data::ElementPtr response_arguments = data::Element::createMap();
            response_arguments->set("count",
                                    data::Element::create(static_cast<long int>(count)));

            // Configuration backend didn't complain so let's return the success status.
            std::ostringstream msg;
            msg << count << (address_family == AF_INET ? " DHCPv4" : " DHCPv6")
                << " option(s) deleted.";
            int rcode =
                (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
            data::ConstElementPtr response =
                config::createAnswer(rcode, msg.str(), response_arguments);
            callout_handle.setArgument("response", response);

        } catch (const std::exception& ex) {
            // Something went wrong. Return an error response to the client.
            data::ConstElementPtr response =
                config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
            callout_handle.setArgument("response", response);
        }
    }

    /// @brief Create an element map containing an OptionDef's code and space
    ///
    /// @param def option definition who's information is desired.
    /// @return Map element containing the options' code and space.
    data::ElementPtr
    makeOptionInfoElement(const OptionDefinition& def) const {
        data::ElementPtr option_info = data::Element::createMap();
        option_info->set("code",
                          data::Element::create(static_cast<int64_t>
                                                (def.getCode())));

        option_info->set("space", data::Element::create(def.getOptionSpaceName()));
        return (option_info);
    }


    /// @brief Create an element map containing an OptionDescriptor's code, space,
    /// and client classes.
    ///
    /// @param desc option descriptor who's information is desired.
    /// @return Map element containing the options' code, space, and client classes.
    data::ElementPtr
    makeOptionInfoElement(const OptionDescriptor& desc) const {
        data::ElementPtr option_info = data::Element::createMap();
        option_info->set("code",
                          data::Element::create(static_cast<int64_t>
                                                (desc.option_->getType())));

        option_info->set("space", data::Element::create(desc.space_name_));
        if (!desc.client_classes_.empty()) {
            option_info->set("client-classes", desc.client_classes_.toElement());
        }
        return (option_info);
    }

protected:
    /// @brief Shared pointer to the commands parser.
    boost::shared_ptr<ConfigCmdsParser> parser_;
};

} // end of namespace isc::cb
} // end of namespace isc

#endif // CB_CMDS_IMPL_H
