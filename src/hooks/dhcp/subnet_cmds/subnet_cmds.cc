// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <subnet_cmds.h>
#include <subnet_cmds_log.h>
#include <cc/command_interpreter.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <util/multi_threading_mgr.h>
#include <sstream>
#include <cstdint>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace isc {
namespace subnet_cmds {

/// @brief Type of subnet update.
enum UpdateType {
    /// @brief completely replace old subnet with the new entry.
    UPDATE_REPLACE,
    /// @brief update the old subnet by adding the parameters form the new
    /// entry.
    UPDATE_DELTA_ADD,
    /// @brief update the old subnet by removing the parameters from the new
    /// entry.
    UPDATE_DELTA_DEL
};

/// @brief Manager which handles the delta (differences) between two subnets
/// serialized as a JSON tree (usually a user provided subnet configuration and
/// an already existing subnet configuration).
/// It uses an internal representation of the subnet parameters hierarchy to
/// traverse the JSON tree, and functions to detect elements that match the same
/// configuration element or to detect if the element itself is a key identifier
/// of another configuration element. For more details, see
/// @ref isc::data::mergeDiffAdd @ref isc::data::mergeDiffDel and
/// @ref isc::data::extend.
///
/// @tparam SubnetConfigParserType One of the @c Subnet4ConfigParser or
/// @c Subnet6ConfigParser.
template <typename SubnetConfigParserType>
class ConfigDiffManager {
public:

    /// @brief Constructor.
    ///
    /// @param space The type of configuration to handle (dhcp4 or dhcp6).
    ConfigDiffManager(std::string space) : space_(space) {
        if (space != DHCP4_OPTION_SPACE && space != DHCP6_OPTION_SPACE) {
            isc_throw(BadValue, "wrong dhcp type " << space
                      << ", supported " << DHCP4_OPTION_SPACE  << " or "
                      << DHCP6_OPTION_SPACE);
        }

        // Define the hierarchy and keys matching functions.

        /// @brief function which returns true if there are no other parameters
        /// in the subnet beside the identification keys: 'id' and 'subnet'.
        auto const& subnet_empty = [](ElementPtr& element) {
            for (auto const& kv : element->mapValue()) {
                auto const& key = kv.first;
                if (key != "id" && key != "subnet") {
                    return (false);
                }
            }
            return (true);
        };

        /// @brief function which returns true if there are no other parameters
        /// in the pool beside the identification keys: 'pool' and an empty
        /// 'option-data'.
        auto const& pool_empty = [](ElementPtr& element) {
            for (auto const& kv : element->mapValue()) {
                auto const& key = kv.first;
                if (key != "pool") {
                    if (key == "option-data") {
                        if (kv.second->size()) {
                            return (false);
                        }
                    } else {
                        return (false);
                    }
                }
            }
            return (true);
        };

        /// @brief function which returns true if there are no other parameters
        /// in the pd-pool beside the identification keys: 'prefix',
        /// 'prefix-len', 'delegated-len' and an empty 'option-data'.
        auto const& pd_pool_empty = [](ElementPtr& element) {
            for (auto const& kv : element->mapValue()) {
                auto const& key = kv.first;
                if (key != "prefix" && key != "prefix-len" && key != "delegated-len") {
                    if (key == "option-data") {
                        if (kv.second->size()) {
                            return (false);
                        }
                    } else {
                        return (false);
                    }
                }
            }
            return (true);
        };

        /// @brief function which returns true if there are no other parameters
        /// in the option beside the identification keys: 'code' and 'name' and
        /// 'space'.
        auto const& option_empty = [](ElementPtr& element) {
            for (auto const& kv : element->mapValue()) {
                auto const& key = kv.first;
                if (key != "code" && key != "name" && key != "space") {
                    return (false);
                }
            }
            return (true);
        };

        /// @brief function which returns true for any pair of configuration
        /// elements.
        auto const& match_any = [](ElementPtr&, ElementPtr&) -> bool { return (true); };

        /// @brief function which returns true if the pair of subnet elements
        /// refer to the same subnet in the configuration.
        auto const& subnet_match = [](ElementPtr& left, ElementPtr& right) -> bool {
            return (left->get("id")->intValue() == right->get("id")->intValue());
        };

        /// @brief function which returns true if the pair of pool elements
        /// refer to the same pool in the configuration.
        auto const& pool_match = [](ElementPtr& left, ElementPtr& right) -> bool {
            return (left->get("pool")->stringValue() == right->get("pool")->stringValue());
        };

        /// @brief function which returns true if the pair of pd-pool elements
        /// refer to the same pd-pool in the configuration.
        auto const& pd_pool_match = [](ElementPtr& left, ElementPtr& right) -> bool {
            return (left->get("prefix")->stringValue() == right->get("prefix")->stringValue() &&
                    left->get("prefix-len")->intValue() == right->get("prefix-len")->intValue() &&
                    left->get("delegated-len")->intValue() == right->get("delegated-len")->intValue());
        };

        /// @brief function which returns true if the pair of option elements
        /// refer to the same option in the configuration.
        auto const& option_match = [&](ElementPtr& left, ElementPtr& right) -> bool {
            std::string left_space = space;
            std::string right_space = space;
            if (left->get("space")) {
                left_space = left->get("space")->stringValue();
            }
            if (right->get("space")) {
                right_space = right->get("space")->stringValue();
            }
            if (left_space == right_space) {
                if (left->find("code") && right->find("code")) {
                    return (left->get("code")->intValue() == right->get("code")->intValue());
                } else if (left->find("name") && right->find("name")) {
                    return (left->get("name")->stringValue() == right->get("name")->stringValue());
                }
            }
            return (false);
        };

        /// @brief function which returns true if the parameter name is an
        /// identification key for the subnet.
        auto const& subnet_is_key = [](const std::string& key) -> bool {
            return (key == "id" || key == "subnet");
        };

        /// @brief function which returns true if the parameter name is an
        /// identification key for the pool.
        auto const& pool_is_key = [](const std::string& key) -> bool {
            return (key == "pool");
        };

        /// @brief function which returns true if the parameter name is an
        /// identification key for the pd-pool.
        auto const& pd_pool_is_key = [](const std::string& key) -> bool {
            return (key == "prefix" || key == "prefix-len" || key == "delegated-len");
        };

        /// @brief function which returns true if the parameter name is an
        /// identification key for the option.
        auto const& option_is_key = [](const std::string& key) -> bool {
            return (key == "space" || key == "code" || key == "name");
        };

        subnet_hierarchy_any_match_ = {
            { { "subnet", { subnet_match, subnet_empty, subnet_is_key } } },
            { { "pools", { match_any, pool_empty, pool_is_key } },
              { "pd-pools", { match_any, pd_pool_empty, pd_pool_is_key } },
              { "option-data", { option_match, option_empty, option_is_key } } },
            { { "option-data", { option_match, option_empty, option_is_key } } }
        };

        subnet_hierarchy_ = {
            { { "subnet", { subnet_match, subnet_empty, subnet_is_key } } },
            { { "pools", { pool_match, pool_empty, pool_is_key } },
              { "pd-pools", { pd_pool_match, pd_pool_empty, pd_pool_is_key } },
              { "option-data", { option_match, option_empty, option_is_key } } },
            { { "option-data", { option_match, option_empty, option_is_key } } }
        };
    }

    /// @brief Destructor.
    ~ConfigDiffManager() = default;

    /// @brief Process the delta between existing configuration and user
    /// provided data.
    ///
    /// @param type The type of merge performed.
    /// @param old_element The configuration element which needs update.
    /// @param subnet_element The user provided data containing only the desired
    /// configuration changes.
    void processDelta(UpdateType type, ElementPtr& old_element,
                      ConstElementPtr& subnet_element) {
        // To be able to have unified format of the key values of pools and
        // pd-pools, we need to parse the user provided data using one of
        // the @c Subnet4ConfigParser or @c Subnet6ConfigParser.
        // This will make keys match when traversing the configuration tree
        // hierarchy.

        // Save the initial list of keys provided by user.
        std::set<std::string> initial_keys;
        for (auto const& key : subnet_element->mapValue()) {
            initial_keys.insert(key.first);
        }

        // The merge delete functionality is flexible and permits deleting
        // entire elements by providing only the keys identifying the
        // respective element. In the case of options, the space can be a
        // determined automatically for options inside the default spaces.
        // The @c Subnet4ConfigParser and @c Subnet6ConfigParser will throw
        // if the "data" is not provided for specified options, so we must
        // extend the user input with valid data from the existing
        // configuration. We don't care about exact pool or pd-pool match as
        // the data will be removed anyway. A relaxed search for the "data"
        // value for the specific option space, code and name is done
        // storing only the valid data so that the parser will not complain.
        if (type == UPDATE_DELTA_DEL) {
            ElementPtr extended = boost::const_pointer_cast<Element>(subnet_element);
            extend("option-data", "data", extended, old_element, subnet_hierarchy_any_match_, "subnet");
        }

        // The parser is applied on user provided data and then is translated
        // back to an JSON tree to be able to convert the data to an uniform
        // internal format: same number of spaces, using prefix or interval
        // format:
        //   "192.0.2.1-192.0.2.100" and "192.0.2.1 - 192.0.2.100" refer to the
        //   same thing, so does "192.0.2.0/24" and "192.0.2.0 - 192.0.2.255"
        //   "2003:db8::1-2003:db8::10" and "2003:db8::1 - 2003:db8::10" refer
        //   to the same thing, so does "2003:db8::/120" and
        //   "2003:db8:: - 2003:db8::ff"
        // The Subnet::toElement function adds extra parameters
        // (e.g. option-data) even if they are empty. This is used for better
        // matching parameters.
        SubnetConfigParserType parser;
        auto new_element = parser.parse(subnet_element)->toElement();

        // The Subnet::toElement function formats the data, but it adds some
        // undesired elements which will be interpreted as being added by
        // user, so they must be removed.
        std::set<std::string> final_keys;
        for (auto const& key : new_element->mapValue()) {
            if (initial_keys.find(key.first) == initial_keys.end()) {
                final_keys.insert(key.first);
            }
        }
        for (auto const& value : final_keys) {
            new_element->remove(value);
        }

        if (type == UPDATE_DELTA_ADD) {
            // Do the merge add.
            mergeDiffAdd(old_element, new_element, subnet_hierarchy_, "subnet");
        } else if (type == UPDATE_DELTA_DEL) {
            // Do the merge del.
            mergeDiffDel(old_element, new_element, subnet_hierarchy_, "subnet");
        }
    };

private:

    /// @brief The dhcp space (either dhcp4 or dhcp6).
    std::string space_;

    /// @brief Subnet configuration hierarchy using non restrictive option data
    /// search (match any option with the same space, code and name).
    HierarchyDescriptor subnet_hierarchy_any_match_;

    /// @breif Subnet configuration hierarchy using restrictive search for all
    /// elements.
    HierarchyDescriptor subnet_hierarchy_;
};

/// @brief Implementation of the @c SubnetCmds class.
///
/// It provides generic functions for subnet manipulations.
class SubnetCmdsImpl {
public:

    /// @brief Returns a response to a 'subnet4-list' and 'subnet6-list'
    /// command.
    ///
    /// Whether this function returns a list of IPv4 or IPv6 subnets depends
    /// on the type of the @c cfg object provided by the caller.
    ///
    /// @param cfg Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr object.
    /// @param protocol_type 'IPv4' or 'IPv6', depending on the subnet types
    /// being retrieved.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    ///
    /// @tparam CfgType One of the following types: @c CfgSubnets4Ptr or
    /// @c CfgSubnets6Ptr holding subnets configuration.
    template<typename CfgType>
    ConstElementPtr getSubnetList(const CfgType& cfg,
                                  const std::string& protocol_type) const {
        // Create a list where we're going to store subnets' information.
        ElementPtr subnet_list = Element::createList();
        // Create arguments map and add subnet map.
        ElementPtr args = Element::createMap();
        args->set("subnets", subnet_list);

        // Retrieve all subnets from the configuration structure.
        auto subnets = cfg->getAll();

        // Iterate over all subnets and retrieve the information we're interested in.
        for (auto const& s : *subnets) {
            // Information for the individual subnets is held in the map.
            subnet_list->add(subnetToElement(*s, true));
        }

        // Generate the status message including the number of subnets found.
        std::ostringstream s;
        s << subnets->size() << " " << protocol_type << " subnet";

        // For 0 subnets or more than 1 subnets returned, we use plural form 'subnets'.
        if (subnets->size() != 1) {
            s << "s";
        }
        s << " found";

        // Log the number of subnets found.
        if (subnets->size() > 0) {
            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_SUBNET_LIST)
                .arg(subnets->size())
                .arg(protocol_type);
            return (createAnswer(CONTROL_RESULT_SUCCESS, s.str(), args));

        } else {
            // No subnets found.
            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_SUBNET_LIST_EMPTY)
                .arg(protocol_type);
            return (createAnswer(CONTROL_RESULT_EMPTY, s.str(), args));
        }
    }

    /// @brief Provides a response to a 'subnet4-get' or 'subnet6-get' command.
    ///
    /// @param cfg Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr object.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'subnet4-get' or 'subnet6-get'.
    /// @param subnet_parameter One of the following: 'subnet4' or 'subnet6'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam SubnetTypePtr One of the following types: @c ConstSubnet4Ptr
    /// or @c ConstSubnet6Ptr.
    /// @tparam CfgType One of the following types: @c CfgSubnets4Ptr or
    /// @c CfgSubnets6Ptr holding subnets configuration.
    template<typename SubnetTypePtr, typename CfgType>
    ConstElementPtr getSubnet(const CfgType& cfg,
                              const data::ConstElementPtr& arguments,
                              const std::string& command_name,
                              const std::string& subnet_parameter,
                              const std::string& protocol_version) const {
        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        // Currently we allow only one parameter in this command: id or
        // subnet and they are mutually exclusive.
        } else if (arguments->size() != 1) {
            isc_throw(BadValue, "invalid number of arguments " << arguments->size()
                      << " for the '" << command_name << "' command. Expecting"
                      " 'id' or 'subnet'");
        }

        SubnetTypePtr subnet;

        ConstElementPtr subnet_id_param;
        ConstElementPtr subnet_param = arguments->get("subnet");

        // Check if the 'subnet' parameter has been specified in the command.
        if (subnet_param) {
            // This parameter must be a string.
            if (subnet_param->getType() != Element::string) {
                isc_throw(BadValue, "'subnet' parameter must be a string");
            }
            // Try to find a subnet by prefix.
            subnet = cfg->getByPrefix(subnet_param->stringValue());

        } else {
            // Check if the 'id' parameter has been specified in the command.
            subnet_id_param = arguments->get("id");
            if (subnet_id_param) {
                // Subnet identifier must be an integer.
                if (subnet_id_param->getType() != Element::integer) {
                    isc_throw(BadValue, "'id' parameter must be an integer");
                }
                // Try to find a subnet by subnet identifier.
                subnet = cfg->getBySubnetId(SubnetID(subnet_id_param->intValue()));

            } else {
                // If neither of these parameters has been specified, signal an error.
                isc_throw(BadValue, "'id' or 'subnet' parameter required");
            }
        }

        ConstElementPtr response;

        // If subnet found, wrap this response in the successful response.
        if (subnet) {
            ElementPtr subnets_list = Element::createList();
            subnets_list->add(subnet->toElement());
            ElementPtr response_arguments  = Element::createMap();
            response_arguments->set(subnet_parameter, subnets_list);

            std::ostringstream s;
            s << "Info about " << protocol_version << " subnet " << subnet->toText()
              << " (id " << subnet->getID() << ") returned";
            response = createAnswer(CONTROL_RESULT_SUCCESS, s.str(),
                                    response_arguments);

            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_SUBNET_GET)
                .arg(subnet->toText())
                .arg(subnet->getID());

        // No subnet found.
        } else {
            std::stringstream s;
            if (subnet_param) {
                s << "No " << subnet_param->stringValue() << " subnet found";
            } else {
                s << "No subnet with id " << subnet_id_param->intValue() << " found";
            }

            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_SUBNET_GET_EMPTY).arg(s.str());
            response = createAnswer(CONTROL_RESULT_EMPTY, s.str());
        }

        return (response);
    }

    /// @brief Provides a response to a 'subnet4-add' and 'subnet6-add'
    /// command.
    ///
    /// This method is used for processing 'subnet4-add' and 'subnet6-add'
    /// commands. It parses received command, adds the subnet to the current
    /// server configuration and provides a response to the controlling client.
    ///
    /// @param cfg Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr object.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'subnet4-add' or 'subnet6-add'.
    /// @param subnet_parameter One of the following: 'subnet4' or 'subnet6'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam SimpleParserType One of the @c SimpleParser4 or @c SimpleParser6
    /// @tparam SubnetConfigParserType One of the @c Subnet4ConfigParser or
    /// @c Subnet6ConfigParser.
    /// @tparam CfgType One of the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr.
    ///
    /// @return Pointer to the object representing a response. This pointer is
    /// only returned to indicate successful processing of the command.
    /// Errors are signaled to a caller by exceptions.
    template<typename SimpleParserType, typename SubnetConfigParserType,
             typename CfgType>
    ConstElementPtr addSubnet(CfgType& cfg, const ConstElementPtr& arguments,
                              const std::string& command_name,
                              const std::string& subnet_parameter,
                              const std::string& protocol_version) {

        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        } else if (arguments->size() != 1) {
            isc_throw(BadValue, "invalid number of arguments "
                      << arguments->size() << " for the '"
                      << command_name << "' command. Expecting "
                      "'" << subnet_parameter << "' list");
        }

        // The map should contain a 'subnet4' or 'subnet6' list.
        ConstElementPtr subnet_list = arguments->get(subnet_parameter);
        if (!subnet_list) {
            isc_throw(BadValue, "missing '" << subnet_parameter << "'"
                      " argument for the '" << command_name << "' command");

        // Make sure it is a list.
        } else if (subnet_list->getType() != Element::list) {
            isc_throw(BadValue, "'" << subnet_parameter << "'"
                      " argument specified for the '"
                      << command_name << "' command is not a list");

        // Currently we allow only one subnet in the list.
        } else if (subnet_list->size() != 1) {
            isc_throw(BadValue, "invalid number of subnets specified for the"
                      " '" << command_name << "' command. Expected one subnet");
        }

        // Make sure that the subnet information is a map.
        ConstElementPtr subnet_element = subnet_list->get(0);
        if (subnet_element->getType() != Element::map) {
            isc_throw(BadValue, "invalid subnet information specified for the"
                      "'" << command_name << "' command. Expected a map");

        // Make sure that the subnet doesn't specify any host reservations.
        // This is only allowed when setting the full server configuration.
        // In order to add reservations for a subnet a different set of
        // commands is used.
        } else if (subnet_element->get("reservations")) {
            isc_throw(BadValue, "must not specify host reservations with '"
                      << command_name << "'. Use 'reservation-add' to add"
                      " a reservation to a subnet");
        }

        // The tricky part is that some of the subnet parameters may be
        // inherited from the global scope. The command itself has no
        // information about the global parameters' values, so we will
        // construct a "global" map populated with the server's globals
        // and add the subnet(s) from the command to that.
        ElementPtr global_scope;

        // Add in any configured, global parameters from the server
        global_scope = CfgMgr::instance().getCurrentCfg()->
            getConfiguredGlobals()->toElement();

        global_scope->set(subnet_parameter, subnet_list);

        // Now, let's specify the default values using SimpleParser4
        // or SimpleParser6 and derive to the subnet we're adding.
        SimpleParserType::setAllDefaults(global_scope);
        SimpleParserType::deriveParameters(global_scope);

        // Finally, let's parse the subnet information extended with the
        // default values.
        SubnetConfigParserType parser;
        auto subnet = parser.parse(subnet_list->get(0));

        // Add this subnet to the current configuration.
        cfg->add(subnet);

        // Update the statistics. There is no need to remove any existing statistics
        // because we are not removing any pools, just adding new ones.
        cfg->updateStatistics();

        // Some allocators require initialization of their state. In particular,
        // the FLQ allocator needs to populate free leases.
        subnet->initAllocatorsAfterConfigure();

        // The response contains a subnet prefix and subnet id.
        ElementPtr subnet_info = Element::createMap();
        subnet_info->set("id",
                         Element::create(static_cast<long int>(subnet->getID())));
        subnet_info->set("subnet", Element::create(subnet->toText()));

        // The subnet information is encapsulated in a single element list.
        ElementPtr subnets_list = Element::createList();
        subnets_list->add(subnet_info);

        // The list is called subnets just like with 'subnet4-get' and
        // 'subnet6-get'.
        ElementPtr response_arguments  = Element::createMap();
        response_arguments->set("subnets", subnets_list);

        // Add text stating that IPv4 or IPv6 subnet has been added.
        std::ostringstream response_text;
        response_text << protocol_version << " subnet added";

        // Create the response.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                response_text.str(),
                                                response_arguments);

        LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_SUBNET_ADD)
            .arg(subnet->toText())
            .arg(subnet->getID());

        return (response);
    }

    /// @brief Provides a response to a 'subnet4-update' and 'subnet6-update'
    /// command.
    ///
    /// This method is used for processing 'subnet4-update' and
    /// 'subnet6-update' commands. It parses received command, updates
    /// the subnet with the given ID in the current server configuration
    /// and provides a response to the controlling client.
    ///
    /// @param cfg Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr object.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'subnet4-update' or 'subnet6-update'.
    /// @param subnet_parameter One of the following: 'subnet4' or 'subnet6'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    /// @param type The update type (replace, delta add, delta del).
    ///
    /// @tparam SimpleParserType One of the @c SimpleParser4 or @c SimpleParser6
    /// @tparam SubnetConfigParserType One of the @c Subnet4ConfigParser or
    /// @c Subnet6ConfigParser.
    /// @tparam SharedNetworkPtrType One of the @c SharedNetwork4 or @c SharedNetwork6.
    /// @tparam SubnetTypePtr One of the following types: @c Subnet4Ptr
    /// or @c Subnet6Ptr.
    /// @tparam CfgType One of the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr.
    ///
    /// @return Pointer to the object representing a response. This pointer is
    /// only returned to indicate successful processing of the command.
    /// Errors are signaled to a caller by exceptions.
    template<typename SimpleParserType, typename SubnetConfigParserType,
             typename SharedNetworkPtrType, typename SubnetTypePtr,
             typename CfgType>
    ConstElementPtr updateSubnet(CfgType& cfg,
                                 const ConstElementPtr& arguments,
                                 const std::string& command_name,
                                 const std::string& subnet_parameter,
                                 const std::string& protocol_version,
                                 UpdateType type = UPDATE_REPLACE) {

        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        } else if (arguments->size() != 1) {
            isc_throw(BadValue, "invalid number of arguments "
                      << arguments->size() << " for the '"
                      << command_name << "' command. Expecting "
                      "'" << subnet_parameter << "' list");
        }

        // The map should contain a 'subnet4' or 'subnet6' list.
        ConstElementPtr subnet_list = arguments->get(subnet_parameter);
        if (!subnet_list) {
            isc_throw(BadValue, "missing '" << subnet_parameter << "'"
                      " argument for the '" << command_name << "' command");

        // Make sure it is a list.
        } else if (subnet_list->getType() != Element::list) {
            isc_throw(BadValue, "'" << subnet_parameter << "'"
                      " argument specified for the '"
                      << command_name << "' command is not a list");

        // Currently we allow only one subnet in the list.
        } else if (subnet_list->size() != 1) {
            isc_throw(BadValue, "invalid number of subnets specified for the"
                      " '" << command_name << "' command. Expected one subnet");
        }

        // Make sure that the subnet information is a map.
        ConstElementPtr subnet_element = subnet_list->get(0);
        if (subnet_element->getType() != Element::map) {
            isc_throw(BadValue, "invalid subnet information specified for the"
                      "'" << command_name << "' command. Expected a map");

        // Make sure that the subnet doesn't specify any host reservations.
        // This is only allowed when setting the full server configuration.
        } else if (subnet_element->get("reservations")) {
            isc_throw(BadValue, "must not specify host reservations with '"
                      << command_name << "'.");
        }

        // Verify that the subnet ID is specified and in 1..max
        ConstElementPtr id_element = subnet_element->get("id");
        if (!id_element) {
            isc_throw(BadValue, "must specify subnet id with '"
                      << command_name << "' command.");
        }
        const SubnetID& subnet_id =
            SimpleParser::getInteger(subnet_element, "id", 1, SUBNET_ID_MAX);

        // Check the subnet with the same ID.
        auto old_subnet = cfg->getBySubnetId(subnet_id);
        if (!old_subnet) {
            isc_throw(NotFound,
                      "Can't find subnet '" << subnet_id << "' to update");
        }

        if (type != UPDATE_REPLACE) {
            auto old_element = old_subnet->toElement();

            std::string space = DHCP4_OPTION_SPACE;
            if (subnet_parameter == "subnet6") {
                space = DHCP6_OPTION_SPACE;
            }

            ConfigDiffManager<SubnetConfigParserType> mgr(space);

            mgr.processDelta(type, old_element, subnet_element);

            // Update the list element with the data after merge add/del.
            boost::const_pointer_cast<Element>(subnet_list)->set(0, old_element);
        }

        // The tricky part is that some of the subnet parameters may be
        // inherited from the global scope. The command itself has no
        // information about the global parameters' values, so we will
        // construct a "global" map populated with the server's globals
        // and replace the subnet(s) from the command to that.
        ElementPtr global_scope;

        // Add in any configured, global parameters from the server
        global_scope = CfgMgr::instance().getCurrentCfg()->
            getConfiguredGlobals()->toElement();

        global_scope->set(subnet_parameter, subnet_list);

        // Now, let's specify the default values using SimpleParser4
        // or SimpleParser6 and derive to the subnet we're updating.
        SimpleParserType::setAllDefaults(global_scope);
        SimpleParserType::deriveParameters(global_scope);

        // Finally, let's parse the subnet information extended with the
        // default values.
        SubnetConfigParserType parser;
        auto subnet = parser.parse(subnet_list->get(0));

        // Subnet update may result in removing some of the pools. Any possibly existing
        // per-pool statistics should be removed.
        cfg->removeStatistics();

        try {
            // Update this subnet to the current configuration.
            auto old = cfg->replace(subnet);
            if (!old) {
                isc_throw(Unexpected, "Unable to update subnet '" << subnet_id
                          << "' in the configuration");
            }

            // Deal with shared network.
            SharedNetworkPtrType network;
            old->getSharedNetwork(network);
            if (network) {
                if (!network->replace(subnet)) {
                    // Try to rollback.
                    if (!cfg->replace(old)) {
                        isc_throw(Unexpected, "Unable to rollback subnet '"
                                  << subnet_id << "' update. Configuration is "
                                  "broken beyond repair.");
                    }
                    isc_throw(Unexpected, "Cancelled subnet '" << subnet_id
                              << "' update: update in shared network '"
                              << network->getName() << "' failed.");
                }
            }
        } catch (...) {
            // We removed the statistics but we failed to process the command.
            // We have to add it back before leaving.
            cfg->updateStatistics();
            throw;
        }

        // Update the statistics for all subnets and the pools that left in the
        // updated subnet.
        cfg->updateStatistics();

        // Some allocators require initialization of their state. In particular,
        // the FLQ allocator needs to populate free leases.
        subnet->initAllocatorsAfterConfigure();

        // The response contains a subnet prefix and subnet id.
        ElementPtr subnet_info = Element::createMap();
        subnet_info->set("id",
                         Element::create(static_cast<long int>(subnet->getID())));
        subnet_info->set("subnet", Element::create(subnet->toText()));

        // The subnet information is encapsulated in a single element list.
        ElementPtr subnets_list = Element::createList();
        subnets_list->add(subnet_info);

        // The list is called subnets just like with 'subnet4-get' and
        // 'subnet6-get'.
        ElementPtr response_arguments  = Element::createMap();
        response_arguments->set("subnets", subnets_list);

        // Add text stating that IPv4 or IPv6 subnet has been updated.
        std::ostringstream response_text;
        response_text << protocol_version << " subnet updated";

        // Create the response.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                response_text.str(),
                                                response_arguments);

        LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_SUBNET_UPDATE)
            .arg(subnet->toText())
            .arg(subnet->getID());

        return (response);
    }

    /// @brief Provides a response to a 'subnet4-del' and 'subnet6-del'
    /// command.
    ///
    /// @param cfg Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr object.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'subnet4-del' or 'subnet6-del'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam CfgType One of the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr.
    /// @tparam SharedNetworkPtrType One of the @c SharedNetwork4Ptr or @c SharedNetwork6Ptr.
    ///
    /// @return Pointer to the object representing a response. This pointer is
    /// only returned to indicate successful processing of the command.
    /// Errors are signaled to a caller by exceptions.
    template<typename CfgType,
             typename SharedNetworkPtrType>
    ConstElementPtr delSubnet(CfgType& cfg, const ConstElementPtr& arguments,
                              const std::string& command_name,
                              const std::string& protocol_version) {
        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        // Currently we only accept one argument, i.e. subnet identifier.
        } else if (arguments->size() != 1) {
            isc_throw(BadValue, "invalid number of arguments specified for the '"
                      << command_name << " command. Expected subnet identifier");
        }

        ConstElementPtr subnet_id_element = arguments->get("id");
        if (!subnet_id_element) {
            isc_throw(BadValue, "subnet identifier is required for the '"
                      << command_name << "' command");

        // Subnet identifier must be an integer.
        } else if (subnet_id_element->getType() != Element::integer) {
            isc_throw(BadValue, "subnet identifier specified for the '"
                      << command_name << "' is not a number");
        }

        uint32_t subnet_id = static_cast<uint32_t>(subnet_id_element->intValue());
        auto subnet = cfg->getBySubnetId(SubnetID(subnet_id));

        // If subnet found, remove it from the configuration.
        if (!subnet) {
            // Subnet not found.
            std::stringstream tmp;
            tmp << "no subnet with id " << subnet_id << " found";
            return (createAnswer(CONTROL_RESULT_EMPTY, tmp.str()));
        }

        // Remove existing statistics because we're removing some pools.
        cfg->removeStatistics();

        try {
            cfg->del(subnet);

            // Remove subnet from its shared-network (if one).
            SharedNetworkPtrType network;
            subnet->getSharedNetwork(network);
            if (network) {
                network->del(subnet->getID());
            }

            // Delete associated host reservations.
            CfgHostsPtr cfg_hosts = CfgMgr::instance().getCurrentCfg()->getCfgHosts();
            if (command_name == "subnet4-del") {
                cfg_hosts->delAll4(subnet_id);
            } else {
                cfg_hosts->delAll6(subnet_id);
            }
        } catch (...) {
            // We removed the statistics but we failed to process the command.
            // We have to add it back before leaving.
            cfg->updateStatistics();
            throw;
        }

        // Update the statistics for the remaning subnets and pools.
        cfg->updateStatistics();

        std::ostringstream response_text;
        response_text << protocol_version << " subnet " << subnet->toText()
            << " (id " << subnet->getID() << ") deleted";

        ElementPtr details = Element::createMap();
        ElementPtr lst = Element::createList();
        lst->add(subnetToElement(*subnet, false));
        details->set("subnets", lst);

        // Create the response.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                response_text.str(), details);

        LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_SUBNET_DEL)
            .arg(subnet->toText())
            .arg(subnet->getID());

        return (response);
    }

    /// @brief Returns essential subnet parameters in Element format
    ///
    /// @brief subnet details of that subnet will be returned
    /// @return id and subnet in Element format
    ElementPtr subnetToElement(const Subnet& subnet, bool include_shared_network) const {
        ElementPtr subnet_element = Element::createMap();
        subnet_element->set("id",
                            Element::create(static_cast<long int>(subnet.getID())));
        subnet_element->set("subnet", Element::create(subnet.toText()));

        if (include_shared_network) {
            std::string sn_name = subnet.getSharedNetworkName();
            if (!sn_name.empty()) {
                subnet_element->set("shared-network-name", data::Element::create(sn_name));
            } else {
                // Shared network name is null.
                subnet_element->set("shared-network-name", data::Element::create());
            }
        }

        return (subnet_element);
    }

    /// @brief Returns a response to a 'network4-list' and 'network6-list'
    /// command.
    ///
    /// Whether this function returns a list of IPv4 or IPv6 networks depends
    /// on the type of the @c cfg object provided by the caller.
    ///
    /// @param networks_cfg Reference to the @c CfgSharedNetworks4Ptr
    ///        or @c CfgSharedNetworks6Ptr object.
    /// @param protocol_type 'IPv4' or 'IPv6', depending on the network types
    /// being retrieved.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    ///
    /// @tparam CfgType One of the following types: @c CfgSharedNetworks4Ptr or
    /// @c CfgSharedNetworks6Ptr holding shared networks configuration.
    template<typename CfgType>
    ConstElementPtr getNetworkList(const CfgType& networks_cfg,
                                   const std::string& protocol_type) const {
        // Create a list where we're going to store networks' information.
        ElementPtr network_list = Element::createList();
        // Create arguments map and add network map.
        ElementPtr args = Element::createMap();
        args->set("shared-networks", network_list);

        // Retrieve all networks from the configuration structure.
        auto networks = networks_cfg->getAll();

        // Iterate over all networks and retrieve the information we're interested in.
        for (auto const& n : *networks) {
            ElementPtr json = Element::createMap();
            json->set("name", Element::create(n->getName()));
            // Information for the individual networks is held in the map.
            network_list->add(json);
        }

        // Generate the status message including the number of networks found.
        std::ostringstream s;
        s << networks->size() << " " << protocol_type << " network";
        // For 0 networks or more than 1 networks returned, we use plural form 'networks'.
        if (networks->size() != 1) {
            s << "s";
        }
        s << " found";

        // Log the number of networks found.
        if (networks->size() > 0) {
            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_LIST)
                .arg(networks->size())
                .arg(protocol_type);
            return (createAnswer(CONTROL_RESULT_SUCCESS, s.str(), args));

        } else {
            // No networks found.
            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_LIST_EMPTY)
                .arg(protocol_type);
            return (createAnswer(CONTROL_RESULT_EMPTY, s.str(), args));
        }
    }

    /// @brief Provides a response to a 'network4-get' or 'network6-get' command.
    ///
    /// @param cfg Reference to the @c CfgSharedNetworks4Ptr or @c CfgSharedNetworks6Ptr object.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'network4-get' or 'network6-get'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam NetworkTypePtr One of the following types: @c SharedNetwork4Ptr
    /// or @c SharedNetwork4Ptr.
    /// @tparam CfgType One of the following types: @c CfgSharedNetworks4Ptr or
    /// @c CfgSharedNetworks6Ptr holding shared networks configuration.
    template<typename NetworkTypePtr, typename CfgType>
    ConstElementPtr getNetwork(const CfgType& cfg,
                               const data::ConstElementPtr& arguments,
                               const std::string& command_name,
                               const std::string& protocol_version) const {
        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");
        }

        // Make sure there's name parameter and that it's a string.
        ConstElementPtr name = arguments->get("name");
        if (!name) {
            isc_throw(BadValue, "invalid '" << command_name
                      << "': missing mandatory 'name' parameter");
        }
        if (name->getType() != Element::string) {
            isc_throw(BadValue, "'name' parameter must be a string");
        }

        // Try to find the network.
        NetworkTypePtr network = cfg->getByName(name->stringValue());

        ConstElementPtr response;

        // If network found, wrap this response in the successful response.
        if (network) {
            ElementPtr networks_list = Element::createList();
            networks_list->add(network->toElement());
            ElementPtr response_arguments  = Element::createMap();
            response_arguments->set("shared-networks", networks_list);

            std::ostringstream s;
            s << "Info about " << protocol_version << " shared network '" << network->getName()
              << "' returned";
            response = createAnswer(CONTROL_RESULT_SUCCESS, s.str(), response_arguments);

            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_GET)
                .arg(network->getName());

        // No network found.
        } else {
            std::stringstream s;
            s << "No '" << name->stringValue() << "' shared network found";

            LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_GET_EMPTY).arg(s.str());
            response = createAnswer(CONTROL_RESULT_EMPTY, s.str());
        }

        return (response);
    }

    /// @brief Provides a response to a 'network4-add' and 'network6-add'
    /// command.
    ///
    /// This method is used for processing 'network4-add' and 'network6-add'
    /// commands. It parses received command, adds the network to the current
    /// server configuration and provides a response to the controlling client.
    ///
    /// @param networks_cfg Reference to the @c CfgSharedNetworks4Ptr
    ///        or @c CfgSharedNetworks6Ptr object.
    /// @param subnets_cfg Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'network4-add' or 'network6-add'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam SimpleParserType One of the @c SimpleParser4 or @c SimpleParser6
    /// @tparam SharedNetworkParserType One of the @c SharedNetwork4Parser or
    /// @c SharedNetwork6Parser.
    /// @tparam CfgNetworksType One of the @c CfgSharedNetworks4Ptr or
    /// @c CfgSharedNetworks6Ptr.
    /// @tparam CfgSubnetsType One of the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr.
    ///
    /// @return Pointer to the object representing a response. This pointer is
    /// only returned to indicate successful processing of the command.
    /// Errors are signaled to a caller by exceptions.
    template<typename SimpleParserType, typename SharedNetworkParserType,
             typename CfgNetworksType, typename CfgSubnetsType>
    ConstElementPtr addNetwork(CfgNetworksType& networks_cfg, CfgSubnetsType& subnets_cfg,
                               const ConstElementPtr& arguments,
                               const std::string& command_name,
                               const std::string& protocol_version) {

        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        }

        // The map should contain a 'shared-networks' list.
        ConstElementPtr network_list = arguments->get("shared-networks");
        if (!network_list) {
            isc_throw(BadValue, "missing 'shared-networks'"
                      " argument for the '" << command_name << "' command");

        // Make sure it is a list.
        } else if (network_list->getType() != Element::list) {
            isc_throw(BadValue, "'shared-networks' argument specified for the '"
                      << command_name << "' command is not a list");

        // Currently we allow only one network in the list.
        } else if (network_list->size() != 1) {
            isc_throw(BadValue, "invalid number of networks specified for the"
                      " '" << command_name << "' command. Expected one network");
        }

        // Make sure that the network information is a map.
        ConstElementPtr network_element = network_list->get(0);
        if (network_element->getType() != Element::map) {
            isc_throw(BadValue, "invalid network information specified for the"
                      "'" << command_name << "' command. Expected a map");
        }

        // The tricky part is that some of the network parameters may be
        // inherited from the global scope. The command itself has no
        // information about the global parameters' values, so we will
        // construct a "global" map populated with the server's globals
        // and add the network(s) from the command to that.
        ElementPtr global_scope;

        // Add in any configured, global parameters from the server
        global_scope = CfgMgr::instance().getCurrentCfg()->
            getConfiguredGlobals()->toElement();

        global_scope->set("shared-networks", network_list);

        // Now, let's specify the default values using SimpleParser4
        // or SimpleParser6 and derive to the network we're adding.
        SimpleParserType::setAllDefaults(global_scope);
        SimpleParserType::deriveParameters(global_scope);

        // Finally, let's parse the network information extended with the
        // default values.
        SharedNetworkParserType parser;
        auto network = parser.parse(network_list->get(0));

        // Add this network to the current configuration.
        networks_cfg->add(network);

        // Also add all subnets to the subnets list.
        auto subnets_list = network->getAllSubnets();
        if (subnets_list) {
            // For each subnet, add it to a list of regular subnets.
            for (auto const& subnet : *subnets_list) {
                subnets_cfg->add(subnet);
            }
        }

        // Update the statistics for the subnets and pools. There is no need to remove
        // any statistics because we're adding new subnets and pools. We remove none.
        subnets_cfg->updateStatistics();

        // Now that we have successfully added the subnets, let's initialize the
        // allocation states for all newly added subnets.
        for (auto const& subnet : *subnets_list) {
            subnet->initAllocatorsAfterConfigure();
        }

        // The response contains a network name.
        ElementPtr network_info = Element::createMap();
        network_info->set("name", Element::create(network->getName()));

        // The network information is encapsulated in a single element list.
        ElementPtr response_list = Element::createList();
        response_list->add(network_info);

        ElementPtr response_arguments  = Element::createMap();
        response_arguments->set("shared-networks", response_list);

        // Add text stating that IPv4 or IPv6 network has been added.
        std::ostringstream response_text;
        response_text << "A new " << protocol_version << " shared network '" << network->getName()
                      << "' added";

        // Create the response.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                response_text.str(),
                                                response_arguments);

        LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_ADD)
            .arg(network->getName());

        return (response);
    }

   /// @brief Provides a response to a 'network4-del' and 'network6-del'
    /// command.
    ///
    /// @param networks_cfg Reference to the @c CfgSharedNetworks4Ptr
    ///        or @c CfgSharedNetworks6Ptr object.
    /// @param subnets_cfg Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'network4-del' or 'network6-del'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam CfgNetworksType One of the @c CfgSharedNetworks4Ptr or @c CfgSharedNetworks6Ptr.
    /// @tparam CfgSubnetsType One of the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr.
    ///
    /// @return Pointer to the object representing a response. This pointer is
    /// only returned to indicate successful processing of the command.
    /// Errors are signaled to a caller by exceptions.
    template<typename CfgNetworksType, typename CfgSubnetsType>
    ConstElementPtr delNetwork(CfgNetworksType& networks_cfg, CfgSubnetsType& subnets_cfg,
                               const ConstElementPtr& arguments,
                               const std::string& command_name,
                               const std::string& protocol_version) {
        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        // Currently we only accept one argument, i.e. shared network name.
        }

        // Make sure there's name parameter and that it's a string.
        ConstElementPtr name_element = arguments->get("name");
        if (!name_element) {
            isc_throw(BadValue, "network name ('name') is required for the '"
                      << command_name << "' command");
        } else if (name_element->getType() != Element::string) {
            isc_throw(BadValue, "network name ('name') specified for the '"
                      << command_name << "' is not a string");
        }

        bool del = false;
        ConstElementPtr subnet_action = arguments->get("subnets-action");
        if (subnet_action) {
            if (subnet_action->getType() != Element::string) {
                isc_throw(BadValue, "subnets-action parameter for " << command_name
                          << " command must be a string. Supported values are: "
                          << "'keep' and 'delete'.");
            }
            string tmp = subnet_action->stringValue();
            if ( (tmp != "keep") && (tmp != "delete") ) {
                isc_throw(BadValue, "Invalid value for subnets-action parameter: "
                          << tmp << ", Supported values: 'keep' and 'delete'.");
            }
            if (tmp == "delete") {
                del = true;
            }
        }

        std::string name = name_element->stringValue();

        auto network = networks_cfg->getByName(name);
        if (!network) {
            std::stringstream tmp;
            tmp << "no shared network with name '" << name << "' found";
            return (createAnswer(CONTROL_RESULT_EMPTY, tmp.str()));
        }

        // Remove the statistics because some of the subnets will be removed.
        // The statistics will be later updated for the remaining subnets.
        subnets_cfg->removeStatistics();

        try {
            // Should we delete all the subnets?
            if (del) {

                // Get the list of all subnets in this shared network.
                auto network_subs = network->getAllSubnets();

                // Delete them one by one.
                for (auto const& sub : *network_subs) {
                    subnets_cfg->del(sub);

                    // Delete associated host reservations.
                    CfgHostsPtr cfg_hosts = CfgMgr::instance().getCurrentCfg()->getCfgHosts();
                    if (command_name == "network4-del") {
                        cfg_hosts->delAll4(sub->getID());

                    } else if (command_name == "network6-del") {
                        cfg_hosts->delAll6(sub->getID());
                    }
                }
            }
            networks_cfg->del(name);

        } catch (...) {
            // We removed the statistics but we failed to process the command.
            // We have to add it back before leaving.
            subnets_cfg->updateStatistics();
        }

        // Recreate the statistics for the remaining subnets.
        subnets_cfg->updateStatistics();

        std::ostringstream response_text;
        response_text << protocol_version << " shared network '"
                      << name << "' deleted";

        ElementPtr details = Element::createMap();
        ElementPtr lst = Element::createList();
        ElementPtr m = Element::createMap();
        m->set("name", Element::create(name));
        lst->add(m);
        details->set("shared-networks", lst);

        // Create the response.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                response_text.str(), details);

        LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_DEL)
            .arg(name);

        return (response);
    }

    /// @brief Provides a response to a 'network4-subnet-add' and 'network6-subnet-add'
    /// command.
    ///
    /// This method is used for processing 'network4-subnet-add' and 'network6-subnet-add'
    /// commands. It parses received command, adds existing subnet to existing shared network
    /// to the current server configuration and provides a response to the controlling client.
    ///
    /// @param networks Reference to the @c CfgSharedNetworks4Ptr or @c CfgSharedNetworks6Ptr object.
    /// @param subnets Reference to the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr object.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'network4-subnet-add' or 'network6-subnet-add'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam CfgNetworksType One of the @c CfgSharedNetworks4Ptr or @c CfgSharedNetworks6Ptr
    /// @tparam CfgSubnetsType One of the @c CfgSubnets4Ptr or @c CfgSubnets6Ptr
    ///
    /// @return Pointer to the object representing a response. This pointer is
    /// only returned to indicate successful processing of the command.
    /// Errors are signaled to a caller by exceptions.
    template<typename CfgNetworksType, typename CfgSubnetsType>
    ConstElementPtr addNetworkSubnet(CfgNetworksType& networks, CfgSubnetsType& subnets,
                                     const ConstElementPtr& arguments,
                                     const std::string& command_name,
                                     const std::string& protocol_version) {

        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        }

        // The map should contain two parameters: name (string) that identifies a shared network
        // and id (int) which identifies a subnet.
        ConstElementPtr name_elem = arguments->get("name");
        if (!name_elem) {
            isc_throw(BadValue, "missing 'name'"
                      " argument for the '" << command_name << "' command");

        // Make sure it is a string.
        } else if (name_elem->getType() != Element::string) {
            isc_throw(BadValue, "'name' argument specified for the '"
                      << command_name << "' command is not a string");
        }
        string name = name_elem->stringValue();

        ConstElementPtr id_elem = arguments->get("id");
        if (!id_elem) {
            isc_throw(BadValue, "missing 'id'"
                      " argument for the '" << command_name << "' command");

        // Make sure it is an integer.
        } else if (id_elem->getType() != Element::integer) {
            isc_throw(BadValue, "'name' argument specified for the '"
                      << command_name << "' command is not an integer");
        }
        SubnetID id(id_elem->intValue());

        // Let's check if we have such a shared network
        auto network = networks->getByName(name);

        if (!network) {
            std::stringstream tmp;
            tmp << "no " << protocol_version << " shared network with name '" << name << "' found";
            return (createAnswer(CONTROL_RESULT_EMPTY, tmp.str()));
        }

        auto subnet = subnets->getSubnet(id);
        if (!subnet) {
            std::stringstream tmp;
            tmp << "no " << protocol_version << " subnet with id '" << id << "' found";
            return (createAnswer(CONTROL_RESULT_EMPTY, tmp.str()));
        }

        // Ok, let's add it. It may throw if the subnet is already part of another network.
        // That's ok. The exception will be returned as error code.
        network->add(subnet);

        // Add text stating that IPv4 or IPv6 subnet has been added.
        std::ostringstream response_text;
        response_text << protocol_version << " subnet " << subnet->toText() << " (id " <<
            id << ") is now part of shared network '" << network->getName()
                      << "'";

        LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_SUBNET_ADD)
            .arg(protocol_version).arg(subnet->toText()).arg(id).arg(network->getName());

        // Create the response.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                response_text.str());
        return (response);
    }

    /// @brief Provides a response to a 'network4-subnet-del' and 'network6-subnet-del'
    /// command.
    ///
    /// This method is used for processing 'network4-subnet-del' and 'network6-subnet-del'
    /// commands. It parses received command, removes existing subnet from existing shared network
    /// in the current server configuration and provides a response to the controlling client.
    ///
    /// @param networks Reference to the @c CfgSharedNetworks4Ptr or @c CfgSharedNetworks6Ptr object.
    /// @param arguments Pointer to the arguments specified in the command.
    /// @param command_name One of the following: 'network4-subnet-add' or 'network6-subnet-add'.
    /// @param protocol_version One of the following: 'IPv4' or 'IPv6'.
    ///
    /// @tparam CfgNetworksType One of the @c CfgSharedNetworks4Ptr or @c CfgSharedNetworks6Ptr
    ///
    /// @return Pointer to the object representing a response. This pointer is
    /// only returned to indicate successful processing of the command.
    /// Errors are signaled to a caller by exceptions.
    template<typename CfgNetworksType>
    ConstElementPtr delNetworkSubnet(CfgNetworksType& networks,
                                     const ConstElementPtr& arguments,
                                     const std::string& command_name,
                                     const std::string& protocol_version) {

        // Arguments are required.
        if (!arguments) {
            isc_throw(BadValue, "no arguments specified for the '"
                      << command_name << "' command");

        // Arguments must be a map.
        } else if (arguments->getType() != Element::map) {
            isc_throw(BadValue, "arguments specified for the '"
                      << command_name << "' command are not a map");

        }

        // The map should contain two parameters: name (string) that identifies a shared network
        // and id (int) which identifies a subnet.
        ConstElementPtr name_elem = arguments->get("name");
        if (!name_elem) {
            isc_throw(BadValue, "missing 'name'"
                      " argument for the '" << command_name << "' command");

        // Make sure it is a string.
        } else if (name_elem->getType() != Element::string) {
            isc_throw(BadValue, "'name' argument specified for the '"
                      << command_name << "' command is not a string");
        }
        string name = name_elem->stringValue();

        ConstElementPtr id_elem = arguments->get("id");
        if (!id_elem) {
            isc_throw(BadValue, "missing 'id'"
                      " argument for the '" << command_name << "' command");

        // Make sure it is an integer.
        } else if (id_elem->getType() != Element::integer) {
            isc_throw(BadValue, "'name' argument specified for the '"
                      << command_name << "' command is not an integer");
        }
        SubnetID id(id_elem->intValue());

        // Let's check if we have such a shared network
        auto network = networks->getByName(name);

        if (!network) {
            std::stringstream tmp;
            tmp << "no " << protocol_version << " shared network with name '" << name << "' found";
            return (createAnswer(CONTROL_RESULT_EMPTY, tmp.str()));
        }

        // Now check if there is such a subnet.
        auto subnet = network->getSubnet(id);
        if (!subnet) {
            std::stringstream tmp;
            tmp << "The " << protocol_version << " subnet with id " << id
                << " is not part of the shared network with name '" << name << "' found";
            return (createAnswer(CONTROL_RESULT_EMPTY, tmp.str()));
        }

        // Ok, let's delete it.
        network->del(id);

        // Add text stating that IPv4 or IPv6 subnet has been added.
        std::ostringstream response_text;
        response_text << protocol_version << " subnet " << subnet->toText() << " (id " <<
            id << ") is now removed from shared network '" << network->getName()
                      << "'";

        LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_NETWORK_SUBNET_DEL)
            .arg(protocol_version).arg(subnet->toText()).arg(id).arg(network->getName());

        // Create the response.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                response_text.str());
        return (response);
    }

};

SubnetCmds::SubnetCmds()
    : impl_(new SubnetCmdsImpl()) {
}

ConstElementPtr
SubnetCmds::getSubnet4List() const {
    ConstCfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    return (impl_->getSubnetList(cfg, "IPv4"));
}

ConstElementPtr
SubnetCmds::getSubnet6List() const {
    ConstCfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    return (impl_->getSubnetList(cfg, "IPv6"));
}

ConstElementPtr
SubnetCmds::getSubnet4(const data::ConstElementPtr& arguments) const {
    ConstCfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    return (impl_->getSubnet<ConstSubnet4Ptr>(cfg, arguments, "subnet4-get",
                                              "subnet4", "IPv4"));
}

ConstElementPtr
SubnetCmds::getSubnet6(const data::ConstElementPtr& arguments) const {
    ConstCfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    return (impl_->getSubnet<ConstSubnet6Ptr>(cfg, arguments, "subnet6-get",
                                              "subnet6", "IPv6"));
}

/// Modifying subnet configuration requires a critical section.

ConstElementPtr
SubnetCmds::addSubnet4(const data::ConstElementPtr& arguments) {
    CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    MultiThreadingCriticalSection sc;
    return (impl_->addSubnet<SimpleParser4, Subnet4ConfigParser>(cfg, arguments,
                                                                 "subnet4-add",
                                                                 "subnet4", "IPv4"));
}

ConstElementPtr
SubnetCmds::addSubnet6(const data::ConstElementPtr& arguments) {
    CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    MultiThreadingCriticalSection sc;
    return (impl_->addSubnet<SimpleParser6, Subnet6ConfigParser>(cfg, arguments,
                                                                 "subnet6-add",
                                                                 "subnet6", "IPv6"));
}

ConstElementPtr
SubnetCmds::updateSubnet4(const data::ConstElementPtr& arguments) {
    CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    MultiThreadingCriticalSection sc;
    return (impl_->updateSubnet<SimpleParser4, Subnet4ConfigParser,
                                SharedNetwork4Ptr, Subnet4>(cfg, arguments,
                                                            "subnet4-update",
                                                            "subnet4", "IPv4"));
}

ConstElementPtr
SubnetCmds::updateSubnet6(const data::ConstElementPtr& arguments) {
    CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    MultiThreadingCriticalSection sc;
    return (impl_->updateSubnet<SimpleParser6, Subnet6ConfigParser,
                                SharedNetwork6Ptr, Subnet6>(cfg, arguments,
                                                            "subnet6-update",
                                                            "subnet6", "IPv6"));
}

ConstElementPtr
SubnetCmds::delSubnet4(const data::ConstElementPtr& arguments) {
    CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    MultiThreadingCriticalSection sc;
    return (impl_->delSubnet<CfgSubnets4Ptr, SharedNetwork4Ptr>(cfg, arguments, "subnet4-del", "IPv4"));
}

ConstElementPtr
SubnetCmds::delSubnet6(const data::ConstElementPtr& arguments) {
    CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    MultiThreadingCriticalSection sc;
    return (impl_->delSubnet<CfgSubnets6Ptr, SharedNetwork6Ptr>(cfg, arguments, "subnet6-del", "IPv6"));
}

ConstElementPtr
SubnetCmds::addSubnet4Delta(const data::ConstElementPtr& arguments) {
    CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    MultiThreadingCriticalSection sc;
    return (impl_->updateSubnet<SimpleParser4, Subnet4ConfigParser,
                                SharedNetwork4Ptr, Subnet4>(cfg, arguments,
                                                            "subnet4-delta-add",
                                                            "subnet4", "IPv4",
                                                            UPDATE_DELTA_ADD));
}

ConstElementPtr
SubnetCmds::addSubnet6Delta(const data::ConstElementPtr& arguments) {
    CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    MultiThreadingCriticalSection sc;
    return (impl_->updateSubnet<SimpleParser6, Subnet6ConfigParser,
                                SharedNetwork6Ptr, Subnet6>(cfg, arguments,
                                                            "subnet6-delta-add",
                                                            "subnet6", "IPv6",
                                                            UPDATE_DELTA_ADD));
}

ConstElementPtr
SubnetCmds::delSubnet4Delta(const data::ConstElementPtr& arguments) {
    CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    MultiThreadingCriticalSection sc;
    return (impl_->updateSubnet<SimpleParser4, Subnet4ConfigParser,
                                SharedNetwork4Ptr, Subnet4>(cfg, arguments,
                                                            "subnet4-delta-del",
                                                            "subnet4", "IPv4",
                                                            UPDATE_DELTA_DEL));
}

ConstElementPtr
SubnetCmds::delSubnet6Delta(const data::ConstElementPtr& arguments) {
    CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    MultiThreadingCriticalSection sc;
    return (impl_->updateSubnet<SimpleParser6, Subnet6ConfigParser,
                                SharedNetwork6Ptr, Subnet6>(cfg, arguments,
                                                            "subnet6-delta-del",
                                                            "subnet6", "IPv6",
                                                            UPDATE_DELTA_DEL));
}

// =============================================================================
// === SHARED NETWORKS =========================================================
// =============================================================================

ConstElementPtr
SubnetCmds::getNetwork4List() const {
    CfgSharedNetworks4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    return (impl_->getNetworkList(cfg, "IPv4"));
}

ConstElementPtr
SubnetCmds::getNetwork6List() const {
    CfgSharedNetworks6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
    return (impl_->getNetworkList(cfg, "IPv6"));
}

ConstElementPtr
SubnetCmds::getNetwork4(const data::ConstElementPtr& arguments) const {
    CfgSharedNetworks4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    return (impl_->getNetwork<SharedNetwork4Ptr>(cfg, arguments, "network4-get", "IPv4"));
}

ConstElementPtr
SubnetCmds::getNetwork6(const data::ConstElementPtr& arguments) const {
    CfgSharedNetworks6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
    return (impl_->getNetwork<SharedNetwork6Ptr>(cfg, arguments, "network6-get", "IPv6"));
}

/// Modifying shared network configuration requires a critical section.

ConstElementPtr
SubnetCmds::addNetwork4(const data::ConstElementPtr& arguments) {
    CfgSubnets4Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    CfgSharedNetworks4Ptr networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    MultiThreadingCriticalSection sc;
    return (impl_->addNetwork<SimpleParser4, SharedNetwork4Parser>(networks, subnets, arguments,
                                                                 "network4-add", "IPv4"));
}

ConstElementPtr
SubnetCmds::addNetwork6(const data::ConstElementPtr& arguments) {
    CfgSubnets6Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    CfgSharedNetworks6Ptr networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
    MultiThreadingCriticalSection sc;
    return (impl_->addNetwork<SimpleParser6, SharedNetwork6Parser>(networks, subnets, arguments,
                                                                 "network6-add", "IPv6"));
}

ConstElementPtr
SubnetCmds::delNetwork4(const data::ConstElementPtr& arguments) {
    CfgSubnets4Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    CfgSharedNetworks4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    MultiThreadingCriticalSection sc;
    return (impl_->delNetwork(cfg, subnets, arguments, "network4-del", "IPv4"));
}

ConstElementPtr
SubnetCmds::delNetwork6(const data::ConstElementPtr& arguments) {
    CfgSubnets6Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    CfgSharedNetworks6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
    MultiThreadingCriticalSection sc;
    return (impl_->delNetwork(cfg, subnets, arguments, "network6-del", "IPv6"));
}

ConstElementPtr
SubnetCmds::addNetwork4Subnet(const data::ConstElementPtr& arguments) {
    CfgSharedNetworks4Ptr networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    CfgSubnets4Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    MultiThreadingCriticalSection sc;
    return (impl_->addNetworkSubnet(networks, subnets, arguments, "network4-subnet-add",
                                    "IPv4"));
}

ConstElementPtr
SubnetCmds::addNetwork6Subnet(const data::ConstElementPtr& arguments) {
    CfgSharedNetworks6Ptr networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
    CfgSubnets6Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    MultiThreadingCriticalSection sc;
    return (impl_->addNetworkSubnet(networks, subnets, arguments, "network6-subnet-add",
                                    "IPv6"));
}

ConstElementPtr
SubnetCmds::delNetwork4Subnet(const data::ConstElementPtr& arguments) {
    CfgSharedNetworks4Ptr networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    MultiThreadingCriticalSection sc;
    return (impl_->delNetworkSubnet(networks, arguments, "network4-subnet-del", "IPv4"));
}

ConstElementPtr
SubnetCmds::delNetwork6Subnet(const data::ConstElementPtr& arguments) {
    CfgSharedNetworks6Ptr networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
    MultiThreadingCriticalSection sc;
    return (impl_->delNetworkSubnet(networks, arguments, "network6-subnet-del", "IPv6"));
}

} // end of namespace isc::subnet_cmds
} // end of namespace isc
