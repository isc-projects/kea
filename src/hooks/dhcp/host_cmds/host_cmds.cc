// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <host_cmds.h>
#include <config/command_mgr.h>
#include <config/cmds_impl.h>
#include <host_data_parser.h>
#include <cc/command_interpreter.h>
#include <cc/simple_parser.h>
#include <cc/data.h>
#include <asiolink/io_address.h>
#include <host_cmds_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/subnet_id.h>
#include <util/encode/encode.h>
#include <util/str.h>
#include <exceptions/exceptions.h>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <sstream>

using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace std;

namespace isc {
namespace host_cmds {

/// @brief Wrapper class around reservation command handlers.
class HostCmdsImpl : private CmdsImpl {
public:

    /// @brief Constructor.
    HostCmdsImpl();

    /// @brief Destructor.
    ~HostCmdsImpl();

    /// @brief Parameters specified for reservation-get and reservation-del
    ///
    /// As both call types (get and delete) need specify which reservation to
    /// act on, they have the same set of parameters. In particular, those
    /// two call types support the following sets of parameters:
    /// - subnet-id, address
    /// - subnet-id, identifier type, identifier value
    ///
    /// This class stores those parameters and is used to pass them around.
    class Parameters {
    public:

        /// @brief Specifies subnet-id
        SubnetID subnet_id;

        /// @brief Specifies if subnet-id is present
        bool has_subnet_id;

        /// @brief Specifies IPv4 or IPv6 address (used when query_by_addr is true)
        IOAddress addr;

        /// @brief Specifies identifier type (usually FLEX_ID, used when
        ///        query_by_addr is false)
        Host::IdentifierType type;

        /// @brief Specifies identifier value (used when query_by_addr is false)
        std::vector<uint8_t> ident;

        /// @brief Specifies parameter types (true = query by address, false =
        ///        query by identifier-type,identifier)
        bool query_by_addr;

        /// @brief Specifies page limit (no default).
        size_t page_limit;

        /// @brief Specifies source index (default 0).
        size_t source_index;

        /// @brief Specifies host identifier (default 0).
        uint64_t host_id;

        /// @brief Specifies host name (default "").
        std::string hostname;

        /// @brief Specifies the target host source (default UNSPECIFIED_SOURCE
        /// which means the default host source is command-related).
        HostMgrOperationTarget operation_target;

        /// @brief Default constructor.
        Parameters()
            : subnet_id(0), has_subnet_id(false), addr("::"),
              type(Host::IdentifierType::IDENT_HWADDR), query_by_addr(true),
              page_limit(0), source_index(0), host_id(0),
              operation_target(HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
        }
    };

public:

    /// @brief reservation-add command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationAddHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    reservationAddHandler(CalloutHandle& handle);

    /// @brief reservation-get command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationGetHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    reservationGetHandler(CalloutHandle& handle);

    /// @brief reservation-get-by-address command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationGetByAddressHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int reservationGetByAddressHandler(CalloutHandle& handle);

    /// @brief reservation-del command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationDelHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// delete command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    reservationDelHandler(CalloutHandle& handle);

    /// @brief reservation-get-all command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationGetAllHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-all command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    reservationGetAllHandler(CalloutHandle& handle);

    /// @brief reservation-get-page command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationGetPageHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-page command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    reservationGetPageHandler(CalloutHandle& handle);

    /// @brief reservation-get-by-hostname command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationGetByHostnameHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-by-hostname command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    reservationGetByHostnameHandler(CalloutHandle& handle);

    /// @brief reservation-get-by-id command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationGetByIdHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-by-id command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    reservationGetByIdHandler(CalloutHandle& handle);

    /// @brief reservation-update command handler
    ///
    /// Provides the implementation for @ref isc::host_cmds::HostCmds::reservationUpdateHandler.
    ///
    /// @param handle callout context
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    reservationUpdateHandler(CalloutHandle& handle);

private:

    /// @brief Extracts parameters required for reservation-get and reservation-del
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param args - arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    Parameters getParameters(const ConstElementPtr& args);

    /// @brief Extracts parameters required for reservation-get-all
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param args - arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    Parameters getAllParameters(const ConstElementPtr& args);

    /// @brief Extracts parameters required for reservation-get-page
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param args - arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    Parameters getPageParameters(const ConstElementPtr& args);

    /// @brief Extracts parameters required for reservation-get-by-hostname
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param args - arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    Parameters getByHostnameParameters(const ConstElementPtr& args);

    /// @brief Extracts parameters required for reservation-get-by-id
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param args - arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    Parameters getByIdParameters(const ConstElementPtr& args);

    /// @brief Extracts parameters required for reservation-get-by-address
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param args - arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    Parameters getByAddressParameters(const ConstElementPtr& params);

    /// @brief Extract the operation target from the parameters.
    /// @param args - arguments passed to command
    /// @return OperationTarget enum value. The target is unspecified if the
    /// related argument doesn't exist.
    HostMgrOperationTarget getOperationTarget(const ConstElementPtr& args);

    /// @brief Checks if the specified IPv4 subnet exists and the reserved address
    /// belongs to this subnet.
    ///
    /// @param subnet_id Subnet identifier. The value of 0 is allowed in which
    /// case no checks are performed and the function simply returns.
    /// @param address Reserved IPv4 address. If this address is 0 it indicates
    /// that no IPv4 address reservation is made and therefore the address is
    /// not checked against the selected subnet.
    ///
    /// @throw isc::BadValue if the subnet id is specified but the subnet does
    /// not exist or if the specified address does not belong to the subnet.
    void validateHostForSubnet4(SubnetID subnet_id, const IOAddress& address);

    /// @brief Checks if the specified IPv6 subnet exists and the reserved
    /// addresses belong to this subnet.
    ///
    /// @param subnet_id Subnet identifier. The value of 0 is allowed in which
    /// case no checks are performed and the function simply returns.
    /// @param addresses Reserved IPv6 addresses. This vector may be empty
    /// indicating that no IPv6 address reservation is made.
    ///
    /// @throw isc::BadValue if the subnet id is specified but the subnet does
    /// not exist or if any of the specified addresses do not belong to the
    /// subnet.
    void validateHostForSubnet6(SubnetID subnet_id,
                                const std::vector<IOAddress>& addresses);

    /// @brief Checks if the subnet is set in the given IPv4 host and
    /// if not add a hint to the error message or return true when empty.
    ///
    /// @param host The host.
    /// @return false if the entry is valid, true if the entry must be
    /// enforced to global (i.e. invalid empty host).
    /// @throw isc::BadValue if the subnet is not set in the host.
    bool checkHost4(const ConstHostPtr& host);

    /// @brief Checks if the subnet is set in the given IPv6 host and
    /// if not add a hint to the error message or return true when empty.
    ///
    /// @param host The host.
    /// @return false if the entry is valid, true if the entry must be
    /// enforced to global (i.e. invalid empty host).
    /// @throw isc::BadValue if the subnet is not set in the host.
    bool checkHost6(const ConstHostPtr& host);

    /// @brief Convenience pointer used to access database storage
    HostDataSourcePtr db_storage_;

    /// @brief Protocol family (IPv4 or IPv6)
    uint16_t family_;
};

HostCmdsImpl::HostCmdsImpl() {
    // There are two ways we can store host reservations: either in configuration
    // or in DB backends. The prime interface we provide - HostMgr class - does
    // not allow storing hosts if alternate data source (DB backend) is not
    // available. Therefore we need to check both. If available, we will store
    // reservations in SQL data source. If not, we will *one day* be able to
    // update the configuration, but it is not possible yet. Current configuration
    // is retrieved as const pointer. We would need a way to clone current
    // configuration to staging, add a host and then commit the change.
    // We need to think this through as we don't want to go through the whole
    // reconfiguration process when a new host is added.

    // Try to get alternate storage.
    db_storage_ = HostMgr::instance().getHostDataSource();

    // Try to get the configuration storage. This will come in handy one day.
    // cfg_storage_ = CfgMgr::instance().getCurrentCfg()->getCfgHosts();

    family_ = CfgMgr::instance().getFamily();
}

HostCmdsImpl::~HostCmdsImpl() {
    db_storage_.reset();
}

int
HostCmdsImpl::reservationAddHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    bool force_global(false);
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_ADD)
            .arg(txt);

        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        HostMgrOperationTarget operation_target = getOperationTarget(cmd_args_);
        if (operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            operation_target = HostMgrOperationTarget::ALTERNATE_SOURCES;
        }

        ConstElementPtr reservation = cmd_args_->get("reservation");
        if (!reservation) {
            isc_throw(isc::BadValue, "reservation must be specified");
        }

        HostPtr host;
        if (family_ == AF_INET) {
            HostDataParser4 parser;
            host = parser.parseWithSubnet(reservation, false);
            force_global = checkHost4(host);
            if (force_global) {
                host->setIPv4SubnetID(SUBNET_ID_GLOBAL);
            }
        } else {
            HostDataParser6 parser;
            host = parser.parseWithSubnet(reservation, false);
            force_global = checkHost6(host);
            if (force_global) {
                host->setIPv6SubnetID(SUBNET_ID_GLOBAL);
            }
        }

        // If we haven't accessed db_storage_ yet, try to retrieve it.
        if (!db_storage_) {
            db_storage_ = HostMgr::instance().getHostDataSource();
        }

        if (!db_storage_ && operation_target == HostMgrOperationTarget::ALTERNATE_SOURCES) {
            // If it's still not available, bail out.
            isc_throw(isc::BadValue, "Host database not available, cannot add host.");
        }

        if (family_ == AF_INET) {
            // Validate the IPv4 subnet id against configured subnet and also verify
            // that the reserved IPv4 address (if non-zero) belongs to this subnet.
            validateHostForSubnet4(host->getIPv4SubnetID(),
                                   host->getIPv4Reservation());

        } else {
            // Retrieve all reserved addresses from the host. We're going to
            // check if these addresses are in range with the specified subnet.
            // If any of them is not in range, we will reject the command.
            // Note that we do not validate delegated prefixes because they don't
            // have to match the subnet prefix.
            auto const& range = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
            std::vector<IOAddress> addresses;
            BOOST_FOREACH(auto const& address, range) {
                addresses.push_back(address.second.getPrefix());
            }
            // Validate the IPv6 subnet id against configured subnet and also
            // verify that the reserved IPv6 addresses (if any) belong to this
            // subnet.
            validateHostForSubnet6(host->getIPv6SubnetID(), addresses);
        }

        HostMgr::instance().add(host, operation_target);
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_ADD_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_ADD_SUCCESS)
        .arg(txt);
    string msg("Host added.");
    if (force_global) {
        msg += " subnet-id not specified, assumed global (subnet-id 0).";
    }
    setSuccessResponse(handle, msg);
    return (0);
}

HostCmdsImpl::Parameters
HostCmdsImpl::getParameters(const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    // We support 2 types of reservation-get:
    // reservation-get(subnet-id, address, operation-target)
    // reservation-get(subnet-id, identifier-type, identifier, operation-target)
    ConstElementPtr addr = params->get("ip-address");
    ConstElementPtr type = params->get("identifier-type");
    ConstElementPtr ident = params->get("identifier");
    if (params->contains("subnet-id") || (!addr && !type && !ident)) {
        int64_t value = data::SimpleParser::getInteger(params, "subnet-id",
                                                       0, dhcp::SUBNET_ID_MAX);
        x.subnet_id = static_cast<SubnetID>(value);
        x.has_subnet_id = true;
    } else {
        x.has_subnet_id = false;
    }

    x.operation_target = getOperationTarget(params);

    if (addr) {
        if (addr->getType() != Element::string) {
            isc_throw(BadValue, "'ip-address' is not a string.");
        }

        x.addr = IOAddress(addr->stringValue());
        x.query_by_addr = true;
        if (!x.has_subnet_id) {
            isc_throw(BadValue, "missing parameter 'subnet-id', use "
                      "'reservation-get-by-address' with 'ip-address' set to \""
                      << addr->stringValue() << "\" to get the list of "
                      << "reservations with this address");
        }
        return (x);
    }

    // No address specified. Ok, so it must be identifier based query.
    // "identifier-type": "duid",
    // "identifier": "aa:bb:cc:dd:ee:..."

    if (!type || type->getType() != Element::string) {
        isc_throw(BadValue, "No 'ip-address' provided"
                  " and 'identifier-type' is either missing or not a string.");
    }
    if (!ident || ident->getType() != Element::string) {
        isc_throw(BadValue, "No 'ip-address' provided"
                  " and 'identifier' is either missing or not a string.");
    }

    // Got the parameters. Let's see if their values make sense.

    // Try to parse the identifier value first.
    try {
        x.ident = util::str::quotedStringToBinary(ident->stringValue());
        if (x.ident.empty()) {
            util::str::decodeFormattedHexString(ident->stringValue(),
                                                x.ident);
        }
    } catch (...) {
        // The string doesn't match any known pattern, so we have to
        // report an error at this point.
        isc_throw(BadValue, "Unable to parse 'identifier' value.");
    }

    if (x.ident.empty()) {
        isc_throw(BadValue, "Unable to query for empty 'identifier'.");
    }

    // Next, try to convert identifier-type
    try {
        x.type = Host::getIdentifierType(type->stringValue());
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "Value of 'identifier-type' was not recognized.");
    }

    x.query_by_addr = false;
    if (!x.has_subnet_id) {
        isc_throw(BadValue, "missing parameter 'subnet-id', use "
                  "'reservation-get-by-id' with 'identifier-type' set to \""
                  << type->stringValue() << "\" and 'identifier' to \""
                  << ident->stringValue() << "\" to get the list of "
                  << "reservations with this identifier");
    }
    return (x);
}

void
HostCmdsImpl::validateHostForSubnet4(SubnetID subnet_id, const IOAddress& address) {
    if (subnet_id != 0) {
        auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        auto subnet = cfg->getBySubnetId(subnet_id);
        if (!subnet) {
            isc_throw(isc::BadValue,
                      "IPv4 subnet with ID of '" << subnet_id
                      << "' is not configured");
        }

        if (!address.isV4Zero() && !address.isV6Zero()
            && !subnet->inRange(address)) {
            isc_throw(isc::BadValue,
                      "specified reservation '" << address
                      << "' is not matching the IPv4 subnet prefix '"
                      << subnet->toText() << "'");
        }
    }
}

void
HostCmdsImpl::validateHostForSubnet6(SubnetID subnet_id,
                                     const std::vector<IOAddress>& addresses) {
    if (subnet_id != 0) {
        auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        auto subnet = cfg->getBySubnetId(subnet_id);
        if (!subnet) {
            isc_throw(isc::BadValue,
                      "IPv6 subnet with ID of '" << subnet_id
                      << "' is not configured");
        }

        for (auto const& address : addresses) {
            if (!subnet->inRange(address)) {
                isc_throw(isc::BadValue,
                          "specified reservation '" << address
                          << "' is not matching the IPv6 subnet prefix '"
                          << subnet->toText() << "'");
            }
        }
    }
}

bool
HostCmdsImpl::checkHost4(const ConstHostPtr& host) {
    if (host->getIPv4SubnetID() != SUBNET_ID_UNUSED) {
        return (false);
    }
    const IOAddress& addr = host->getIPv4Reservation();
    if (!addr.isV4Zero()) {
        // Try to find a subnet hint.
        auto subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        ConstSubnet4Ptr guarded;
        ConstSubnet4Ptr candidate;
        bool others = false;
        for (auto const& subnet : *subnets->getAll()) {
            if (!subnet->inRange(addr)) {
                continue;
            }
            if (subnet->clientSupported(ClientClasses())) {
                if (!candidate) {
                    candidate = subnet;
                } else {
                    others = true;
                }
            } else if (!guarded) {
                guarded = subnet;
            } else {
                others = true;
            }
        }
        if (guarded && candidate) {
            others = true;
        }
        if (!guarded && !candidate) {
            isc_throw(isc::BadValue, "Mandatory 'subnet-id' parameter missing."
                      << " The address '" << addr.toText()
                      << "' belongs to no configured subnet.");
        }
        if (candidate) {
            isc_throw(isc::BadValue, "Mandatory 'subnet-id' parameter missing."
                      << " The address '" << addr.toText()
                      << "' belongs to subnet '" << candidate->toText()
                      << "' id " << candidate->getID()
                      << (others ? " and others." : "."));
        } else {
            isc_throw(isc::BadValue, "Mandatory 'subnet-id' parameter missing."
                      << " The address '" << addr.toText()
                      << "' belongs to guarded subnet '" << guarded->toText()
                      << "' id " << guarded->getID()
                      << (others ? " and others." : "."));
        }
    } else {
        return (true);
    }
}

bool
HostCmdsImpl::checkHost6(const ConstHostPtr& host) {
    if (host->getIPv6SubnetID() != SUBNET_ID_UNUSED) {
        return (false);
    }
    auto const& range = host->getIPv6Reservations();
    std::vector<IOAddress> addresses;
    bool has_prefixes = false;
    BOOST_FOREACH(auto const& address, range) {
        if (address.first == IPv6Resrv::TYPE_NA) {
            addresses.push_back(address.second.getPrefix());
        } else {
            has_prefixes = true;
        }
    }
    if (!addresses.empty()) {
        // Try to find a subnet hint.
        auto subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        ConstSubnet6Ptr guarded;
        ConstSubnet6Ptr candidate;
        bool others = false;
        for (auto const& subnet : *subnets->getAll()) {
            bool in_range = true;
            for (auto const& address : addresses) {
                if (!subnet->inRange(address)) {
                    in_range = false;
                    break;
                }
            }
            if (!in_range) {
                continue;
            }
            if (subnet->clientSupported(ClientClasses())) {
                if (!candidate) {
                    candidate = subnet;
                } else {
                    others = true;
                }
            } else if (!guarded) {
                guarded = subnet;
            } else {
                others = true;
            }
        }
        if (guarded && candidate) {
            others = true;
        }
        if (!guarded && !candidate) {
            isc_throw(isc::BadValue, "Mandatory 'subnet-id' parameter missing."
                      << " Reserved IPv6 addresses do not belong to a"
                      << " common configured subnet.");
        }
        if (candidate) {
            isc_throw(isc::BadValue, "Mandatory 'subnet-id' parameter missing."
                      << " Reserved IPv6 addresses belong to subnet '"
                      << candidate->toText() << "' id " << candidate->getID()
                      << (others ? " and others." : "."));
        } else {
            isc_throw(isc::BadValue, "Mandatory 'subnet-id' parameter missing."
                      << " Reserved IPv6 addresses belong to guarded subnet '"
                      << guarded->toText() << "' id " << guarded->getID()
                      << (others ? " and others." : "."));
        }
    } else if (has_prefixes) {
        isc_throw(isc::BadValue, "Mandatory 'subnet-id' parameter missing."
                  << " Prefixes are not attached to subnets so no hint is"
                  << " available.");
    } else {
        return (true);
    }
}

int
HostCmdsImpl::reservationGetHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    Parameters p;
    ElementPtr host_json;
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET)
            .arg(txt);

        p = getParameters(cmd_args_);

        if (p.operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            p.operation_target = HostMgrOperationTarget::ALL_SOURCES;
        }

        ConstHostPtr host;
        if (p.query_by_addr) {
            // Query by address
            if (p.addr.isV4()) {
                host = HostMgr::instance().get4(p.subnet_id, p.addr, p.operation_target);
            } else {
                host = HostMgr::instance().get6(p.subnet_id, p.addr, p.operation_target);
            }
        } else {
            // Query by identifier
            if (family_ == AF_INET) {
                host = HostMgr::instance().get4(p.subnet_id, p.type, &p.ident[0],
                                                p.ident.size(), p.operation_target);
            } else {
                host = HostMgr::instance().get6(p.subnet_id, p.type, &p.ident[0],
                                                p.ident.size(), p.operation_target);
            }
        }
        if (host) {
            SubnetID subnet_id;
            if (family_ == AF_INET) {
                host_json = host->toElement4();
                subnet_id = host->getIPv4SubnetID();
            } else {
                host_json = host->toElement6();
                subnet_id = host->getIPv6SubnetID();
            }
            host_json->set("subnet-id", Element::create(subnet_id));
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_GET_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_SUCCESS)
        .arg(txt);

    if (host_json) {
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                "Host found.", host_json);
        setResponse(handle, response);
    } else {
        setErrorResponse(handle, "Host not found.", CONTROL_RESULT_EMPTY);
    }

    return (0);
}

int
HostCmdsImpl::reservationGetByAddressHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    Parameters p;
    ElementPtr hosts_json = Element::createList();
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_ADDRESS)
            .arg(txt);

        p = getByAddressParameters(cmd_args_);

        if (p.operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            p.operation_target = HostMgrOperationTarget::ALL_SOURCES;
        }

        ConstHostCollection hosts;
        if (p.has_subnet_id) {
            if (family_ == AF_INET) {
                validateHostForSubnet4(p.subnet_id,
                                       IOAddress::IPV4_ZERO_ADDRESS());
                hosts = HostMgr::instance().getAll4(p.subnet_id, p.addr, p.operation_target);
            } else {
                validateHostForSubnet6(p.subnet_id, std::vector<IOAddress>());
                hosts = HostMgr::instance().getAll6(p.subnet_id, p.addr, p.operation_target);
            }
        } else {
            if (family_ == AF_INET) {
                hosts = HostMgr::instance().getAll4(p.addr, p.operation_target);
            } else {
                hosts = HostMgr::instance().getAll6(p.addr, p.operation_target);
            }
        }

        // Add the subnet-id when it was not specified by the command
        // parameters and filter out wrong universe entries.
        SubnetID subnet_id = p.subnet_id;
        ElementPtr host_json;
        for (auto const& host : hosts) {
            if (!p.has_subnet_id) {
                if (family_ == AF_INET) {
                    subnet_id = host->getIPv4SubnetID();
                } else {
                    subnet_id = host->getIPv6SubnetID();
                }

                if (subnet_id == SUBNET_ID_UNUSED) {
                    continue;
                }
            }

            if (family_ == AF_INET) {
                host_json = host->toElement4();
            } else {
                host_json = host->toElement6();
            }

            host_json->set("subnet-id", Element::create(subnet_id));
            hosts_json->add(host_json);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_ADDRESS_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_ADDRESS_SUCCESS)
        .arg(txt);

    ostringstream msg;
    msg << hosts_json->size()
        << " IPv" << (family_ == AF_INET ? "4" : "6")
        << " host(s) found.";
    ElementPtr result = Element::createMap();
    result->set("hosts", hosts_json);

    ConstElementPtr response = createAnswer(hosts_json->size() > 0 ?
                                                CONTROL_RESULT_SUCCESS :
                                                CONTROL_RESULT_EMPTY,
                                            msg.str(), result);
    setResponse(handle, response);

    return (0);
}

int
HostCmdsImpl::reservationDelHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    Parameters p;
    bool deleted;
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_DEL)
            .arg(txt);

        p = getParameters(cmd_args_);
        if (p.operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            p.operation_target = HostMgrOperationTarget::ALTERNATE_SOURCES;
        }

        if (p.query_by_addr) {
            // try to delete by address
            deleted = HostMgr::instance().del(p.subnet_id, p.addr, p.operation_target);
        } else {
            // try to delete by identifier
            if (family_ == AF_INET) {
                deleted = HostMgr::instance().del4(p.subnet_id, p.type,
                                                   &p.ident[0], p.ident.size(),
                                                   p.operation_target);
            } else {
                deleted = HostMgr::instance().del6(p.subnet_id, p.type,
                                                   &p.ident[0], p.ident.size(),
                                                   p.operation_target);
            }
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_DEL_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_DEL_SUCCESS)
        .arg(txt);

    if (deleted) {
        setSuccessResponse(handle, "Host deleted.");
    } else {
        setErrorResponse(handle, "Host not deleted (not found).",
                         CONTROL_RESULT_EMPTY);
    }

    return (0);
}

HostCmdsImpl::Parameters
HostCmdsImpl::getAllParameters(const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    // We support one type of reservation-get-all(subnet-id)
    int64_t tmp = data::SimpleParser::getInteger(params, "subnet-id",
                                                 0, dhcp::SUBNET_ID_MAX);
    x.subnet_id = static_cast<SubnetID>(tmp);
    x.has_subnet_id = true;

    x.operation_target = getOperationTarget(params);

    return (x);
}

HostCmdsImpl::Parameters
HostCmdsImpl::getPageParameters(const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    int64_t tmp = data::SimpleParser::getInteger(params, "limit", 0,
                                                 numeric_limits<uint32_t>::max());
    x.page_limit = static_cast<size_t>(tmp);

    // subnet-id, source-index and from host-id are optional.
    if (params->contains("subnet-id")) {
        tmp = data::SimpleParser::getInteger(params, "subnet-id",
                                             0, dhcp::SUBNET_ID_MAX);
        x.subnet_id = static_cast<SubnetID>(tmp);
        x.has_subnet_id = true;
    }

    x.source_index = 0;
    if (params->get("source-index")) {
        tmp = data::SimpleParser::getInteger(params, "source-index", 0, 10);
        x.source_index = static_cast<size_t>(tmp);
    }

    x.host_id = 0;
    if (params->get("from")) {
        tmp = data::SimpleParser::getInteger(params, "from");
        x.host_id = static_cast<uint64_t>(tmp);
    }

    return (x);
}

HostCmdsImpl::Parameters
HostCmdsImpl::getByHostnameParameters(const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    string hostname =  data::SimpleParser::getString(params, "hostname");
    x.hostname = hostname;

    // subnet-id is optional.
    if (params->contains("subnet-id")) {
        int64_t tmp = data::SimpleParser::getInteger(params, "subnet-id",
                                                     0, dhcp::SUBNET_ID_MAX);
        x.subnet_id = static_cast<SubnetID>(tmp);
        x.has_subnet_id = true;
    }

    x.operation_target = getOperationTarget(params);

    return (x);
}

HostCmdsImpl::Parameters
HostCmdsImpl::getByIdParameters(const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    ConstElementPtr type = params->get("identifier-type");
    ConstElementPtr ident = params->get("identifier");
    if (!type || type->getType() != Element::string) {
        isc_throw(BadValue, "'identifier-type' is either missing"
                  " or not a string.");
    }
    if (!ident || ident->getType() != Element::string) {
        isc_throw(BadValue, "'identifier' is either missing or not a string.");
    }

    // subnet-id is forbidden.
    if (params->contains("subnet-id")) {
        isc_throw(BadValue, "'subnet-id' is forbidden in reservation-get-by-id");
    }

    // Got the parameters. Let's see if their values make sense.

    // Try to parse the identifier value first.
    try {
        x.ident = util::str::quotedStringToBinary(ident->stringValue());
        if (x.ident.empty()) {
            util::str::decodeFormattedHexString(ident->stringValue(),
                                                x.ident);
        }
    } catch (...) {
        // The string doesn't match any known pattern, so we have to
        // report an error at this point.
        isc_throw(BadValue, "Unable to parse 'identifier' value.");
    }

    if (x.ident.empty()) {
        isc_throw(BadValue, "Unable to query for empty 'identifier'.");
    }

    // Next, try to convert identifier-type
    try {
        x.type = Host::getIdentifierType(type->stringValue());
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "Value of 'identifier-type' was not recognized.");
    }

    x.operation_target = getOperationTarget(params);

    return (x);
}

HostCmdsImpl::Parameters
HostCmdsImpl::getByAddressParameters(const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    // We support 1 type of reservation-get-by-address:
    // reservation-get-by-address(subnet-id, address, operation-target)
    // where subnet-id and operation-target are optional
    IOAddress addr = data::SimpleParser::getAddress(params, "ip-address");
    if (!addr.isV4() && !addr.isV6()) {
        isc_throw(BadValue, "Failed to parse IP address " << addr);
    }

    x.addr = addr;
    x.query_by_addr = true;

    if (params->contains("subnet-id")) {
        int64_t tmp = data::SimpleParser::getInteger(params, "subnet-id",
                                                     0, dhcp::SUBNET_ID_MAX);
        x.subnet_id = static_cast<SubnetID>(tmp);
        x.has_subnet_id = true;
    }

    x.operation_target = getOperationTarget(params);

    return (x);
}

HostMgrOperationTarget
HostCmdsImpl::getOperationTarget(const ConstElementPtr& args) {
    // Operation target is optional.
    if (!args->get("operation-target")) {
        return HostMgrOperationTarget::UNSPECIFIED_SOURCE;
    }

    std::string raw = data::SimpleParser::getString(args, "operation-target");

    if (raw == "memory") {
        return HostMgrOperationTarget::PRIMARY_SOURCE;
    } else if (raw == "database") {
        return HostMgrOperationTarget::ALTERNATE_SOURCES;
    } else if (raw == "all") {
        return HostMgrOperationTarget::ALL_SOURCES;
    } else if (raw == "default") {
        return HostMgrOperationTarget::UNSPECIFIED_SOURCE;
    } else {
        isc_throw(BadValue,
                  "The 'operation-target' value (" << raw
                  << ") is not within expected set: (memory, database, all, "
                  << "default)");
    }
}

int
HostCmdsImpl::reservationGetAllHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    Parameters p;
    ElementPtr hosts_json = Element::createList();
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_ALL)
            .arg(txt);

        p = getAllParameters(cmd_args_);
        if (p.operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            p.operation_target = HostMgrOperationTarget::ALL_SOURCES;
        }

        ConstHostCollection hosts;
        if (family_ == AF_INET) {
            validateHostForSubnet4(p.subnet_id,
                                   IOAddress::IPV4_ZERO_ADDRESS());
            hosts = HostMgr::instance().getAll4(p.subnet_id, p.operation_target);
        } else {
            validateHostForSubnet6(p.subnet_id, std::vector<IOAddress>());
            hosts = HostMgr::instance().getAll6(p.subnet_id, p.operation_target);
        }
        for (auto const& host : hosts) {
            ElementPtr host_json;
            if (family_ == AF_INET) {
                host_json = host->toElement4();
                SubnetID subnet_id = host->getIPv4SubnetID();
                host_json->set("subnet-id", Element::create(subnet_id));
            } else {
                host_json = host->toElement6();
                SubnetID subnet_id = host->getIPv6SubnetID();
                host_json->set("subnet-id", Element::create(subnet_id));
            }
            hosts_json->add(host_json);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_GET_ALL_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_ALL_SUCCESS)
        .arg(txt);

    ostringstream msg;
    msg << hosts_json->size()
        << " IPv" << (family_ == AF_INET ? "4" : "6")
        << " host(s) found.";
    ElementPtr result = Element::createMap();
    result->set("hosts", hosts_json);

    ConstElementPtr response = createAnswer(hosts_json->size() > 0 ?
                                            CONTROL_RESULT_SUCCESS :
                                            CONTROL_RESULT_EMPTY,
                                            msg.str(), result);
    setResponse(handle, response);

    return (0);
}

int
HostCmdsImpl::reservationGetPageHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    Parameters p;
    size_t idx;
    ElementPtr hosts_json = Element::createList();
    uint64_t last_id(0);
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_PAGE)
            .arg(txt);

        p = getPageParameters(cmd_args_);
        idx = p.source_index;
        HostPageSize page_size(p.page_limit);
        ConstHostCollection hosts;
        if (p.has_subnet_id) {
            if (family_ == AF_INET) {
                validateHostForSubnet4(p.subnet_id,
                                       IOAddress::IPV4_ZERO_ADDRESS());
                hosts = HostMgr::instance().getPage4(p.subnet_id, idx,
                                                     p.host_id, page_size);
            } else {
                validateHostForSubnet6(p.subnet_id, std::vector<IOAddress>());
                hosts = HostMgr::instance().getPage6(p.subnet_id, idx,
                                                     p.host_id, page_size);
            }
        } else {
            if (family_ == AF_INET) {
                hosts = HostMgr::instance().getPage4(idx, p.host_id, page_size);
            } else {
                hosts = HostMgr::instance().getPage6(idx, p.host_id, page_size);
            }
        }
        SubnetID subnet_id = p.subnet_id;
        ElementPtr host_json;
        for (auto const& host : hosts) {
            if (!p.has_subnet_id) {
                if (family_ == AF_INET) {
                    subnet_id = host->getIPv4SubnetID();
                } else {
                    subnet_id = host->getIPv6SubnetID();
                }
                if (subnet_id == SUBNET_ID_UNUSED) {
                    continue;
                }
            }
            if (family_ == AF_INET) {
                host_json = host->toElement4();
            } else {
                host_json = host->toElement6();
            }
            host_json->set("subnet-id", Element::create(subnet_id));
            hosts_json->add(host_json);
            last_id = host->getHostId();
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_GET_PAGE_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_PAGE_SUCCESS)
        .arg(txt);

    ostringstream msg;
    msg << hosts_json->size()
        << " IPv" << (family_ == AF_INET ? "4" : "6")
        << " host(s) found.";
    ElementPtr result = Element::createMap();
    result->set("hosts", hosts_json);
    result->set("count",
                Element::create(static_cast<int64_t>(hosts_json->size())));
    if (hosts_json->size() > 0) {
        ElementPtr next = Element::createMap();
        next->set("source-index",
                  Element::create(static_cast<int64_t>(idx)));
        next->set("from", Element::create(static_cast<int64_t>(last_id)));
        result->set("next", next);
    }

    ConstElementPtr response = createAnswer(hosts_json->size() > 0 ?
                                            CONTROL_RESULT_SUCCESS :
                                            CONTROL_RESULT_EMPTY,
                                            msg.str(), result);
    setResponse(handle, response);

    return (0);
}

int
HostCmdsImpl::reservationGetByHostnameHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    Parameters p;
    ElementPtr hosts_json = Element::createList();
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_HOSTNAME)
            .arg(txt);

        p = getByHostnameParameters(cmd_args_);
        if (p.operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            p.operation_target = HostMgrOperationTarget::ALL_SOURCES;
        }

        string hostname = p.hostname;
        if (hostname.empty()) {
            isc_throw(isc::BadValue, "Empty hostname");
        }
        boost::algorithm::to_lower(hostname);
        ConstHostCollection hosts;
        if (p.has_subnet_id) {
            if (family_ == AF_INET) {
                validateHostForSubnet4(p.subnet_id,
                                       IOAddress::IPV4_ZERO_ADDRESS());
                hosts = HostMgr::instance().getAllbyHostname4(hostname,
                                                              p.subnet_id,
                                                              p.operation_target);
            } else {
                validateHostForSubnet6(p.subnet_id, std::vector<IOAddress>());
                hosts = HostMgr::instance().getAllbyHostname6(hostname,
                                                              p.subnet_id,
                                                              p.operation_target);
            }
        } else {
            hosts = HostMgr::instance().getAllbyHostname(hostname, p.operation_target);
        }

        // Add the subnet-id when it was not specified by the command
        // parameters and filter out wrong universe entries.
        SubnetID subnet_id = p.subnet_id;
        ElementPtr host_json;
        for (auto const& host : hosts) {
            if (!p.has_subnet_id) {
                if (family_ == AF_INET) {
                    subnet_id = host->getIPv4SubnetID();
                } else {
                    subnet_id = host->getIPv6SubnetID();
                }
                if (subnet_id == SUBNET_ID_UNUSED) {
                    continue;
                }
            }
            if (family_ == AF_INET) {
                host_json = host->toElement4();
            } else {
                host_json = host->toElement6();
            }
            host_json->set("subnet-id", Element::create(subnet_id));
            hosts_json->add(host_json);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_HOSTNAME_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_HOSTNAME_SUCCESS)
        .arg(txt);

    ostringstream msg;
    msg << hosts_json->size()
        << " IPv" << (family_ == AF_INET ? "4" : "6")
        << " host(s) found.";
    ElementPtr result = Element::createMap();
    result->set("hosts", hosts_json);

    ConstElementPtr response = createAnswer(hosts_json->size() > 0 ?
                                            CONTROL_RESULT_SUCCESS :
                                            CONTROL_RESULT_EMPTY,
                                            msg.str(), result);
    setResponse(handle, response);

    return (0);
}

int
HostCmdsImpl::reservationGetByIdHandler(CalloutHandle& handle) {
    string txt = "(missing parameters)";
    Parameters p;
    ElementPtr hosts_json = Element::createList();
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_ID)
            .arg(txt);

        p = getByIdParameters(cmd_args_);
        if (p.operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            p.operation_target = HostMgrOperationTarget::ALL_SOURCES;
        }

        ConstHostCollection hosts;
        hosts = HostMgr::instance().getAll(p.type, &p.ident[0], p.ident.size(),
                                           p.operation_target);
        SubnetID subnet_id;
        ElementPtr host_json;
        for (auto const& host : hosts) {
            if (family_ == AF_INET) {
                subnet_id = host->getIPv4SubnetID();
            } else {
                subnet_id = host->getIPv6SubnetID();
            }
            if (subnet_id == SUBNET_ID_UNUSED) {
                continue;
            }
            if (family_ == AF_INET) {
                host_json = host->toElement4();
            } else {
                host_json = host->toElement6();
            }
            host_json->set("subnet-id", Element::create(subnet_id));
            hosts_json->add(host_json);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_ID_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_GET_BY_ID_SUCCESS)
        .arg(txt);

    ostringstream msg;
    msg << hosts_json->size()
        << " IPv" << (family_ == AF_INET ? "4" : "6")
        << " host(s) found.";
    ElementPtr result = Element::createMap();
    result->set("hosts", hosts_json);

    ConstElementPtr response = createAnswer(hosts_json->size() > 0 ?
                                            CONTROL_RESULT_SUCCESS :
                                            CONTROL_RESULT_EMPTY,
                                            msg.str(), result);
    setResponse(handle, response);

    return (0);
}

int
HostCmdsImpl::reservationUpdateHandler(CalloutHandle& handle) {
    string parameters("(missing parameters)");
    try {
        // Basic command extraction
        extractCommand(handle);
        if (cmd_args_) {
            parameters = cmd_args_->str();
        }

        LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_UPDATE)
            .arg(parameters);

        // Sanity checks
        if (!cmd_args_) {
            isc_throw(BadValue,
                      "invalid command: does not contain mandatory '" << CONTROL_ARGUMENTS << "'");
        }
        if (cmd_args_->getType() != Element::map) {
            isc_throw(BadValue, "invalid command: expected '"
                      << CONTROL_ARGUMENTS << "' to be a map, got "
                      << Element::typeToName(cmd_args_->getType()) << " instead");
        }
        ConstElementPtr const reservation(cmd_args_->get("reservation"));
        if (!reservation) {
            isc_throw(BadValue, "invalid command: expected 'reservation' as the sole parameter "
                      "inside the 'arguments' map, didn't get it instead");
        }
        if (reservation->getType() != Element::map) {
            isc_throw(BadValue, "invalid command: expected 'reservation' to be a map, got "
                      << Element::typeToName(reservation->getType()) << " instead");
        }

        HostMgrOperationTarget operation_target = getOperationTarget(cmd_args_);
        if (operation_target == HostMgrOperationTarget::UNSPECIFIED_SOURCE) {
            operation_target = HostMgrOperationTarget::ALTERNATE_SOURCES;
        }

        // Parse host-specific parameters.
        HostPtr host;
        if (family_ == AF_INET) {
            HostDataParser4 parser;
            host = parser.parseWithSubnet(reservation);
        } else {
            HostDataParser6 parser;
            host = parser.parseWithSubnet(reservation);
        }

        // If db_storage_ was not accessed yet, try to retrieve it.
        if (!db_storage_) {
            db_storage_ = HostMgr::instance().getHostDataSource();
        }

        if (!db_storage_ && operation_target == HostMgrOperationTarget::ALTERNATE_SOURCES) {
            // If it's still not available, bail out.
            isc_throw(BadValue, "host database not available, cannot update host");
        }

        if (family_ == AF_INET) {
            // Validate the IPv4 subnet id against configured subnet and also verify
            // that the reserved IPv4 address (if non-zero) belongs to this subnet.
            validateHostForSubnet4(host->getIPv4SubnetID(),
                                   host->getIPv4Reservation());

        } else {
            // Retrieve all reserved addresses from the host. We're going to
            // check if these addresses are in range with the specified subnet.
            // If any of them is not in range, we will reject the command.
            // Note that we do not validate delegated prefixes because they don't
            // have to match the subnet prefix.
            auto const& range = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
            std::vector<IOAddress> addresses;
            BOOST_FOREACH(auto const& address, range) {
                addresses.push_back(address.second.getPrefix());
            }
            // Validate the IPv6 subnet id against configured subnet and also
            // verify that the reserved IPv6 addresses (if any) belong to this
            // subnet.
            validateHostForSubnet6(host->getIPv6SubnetID(), addresses);
        }

        // Do the update.
        HostMgr::instance().update(host, operation_target);
    } catch (exception const& exception) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_RESERV_UPDATE_FAILED)
            .arg(parameters)
            .arg(exception.what());
        setErrorResponse(handle, exception.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_RESERV_UPDATE_SUCCESS).arg(parameters);
    setSuccessResponse(handle, "Host updated.");

    return (0);
}

HostCmds::HostCmds()
    :impl_(new HostCmdsImpl()) {
}

int
HostCmds::reservationAddHandler(CalloutHandle& handle) {
    return (impl_->reservationAddHandler(handle));
}

int
HostCmds::reservationGetHandler(CalloutHandle& handle) {
    return (impl_->reservationGetHandler(handle));
}

int
HostCmds::reservationDelHandler(CalloutHandle& handle) {
    return (impl_->reservationDelHandler(handle));
}

int
HostCmds::reservationGetAllHandler(CalloutHandle& handle) {
    return (impl_->reservationGetAllHandler(handle));
}

int
HostCmds::reservationGetPageHandler(CalloutHandle& handle) {
    return (impl_->reservationGetPageHandler(handle));
}

int
HostCmds::reservationGetByHostnameHandler(CalloutHandle& handle) {
    return (impl_->reservationGetByHostnameHandler(handle));
}

int
HostCmds::reservationGetByIdHandler(CalloutHandle& handle) {
    return (impl_->reservationGetByIdHandler(handle));
}

int
HostCmds::reservationUpdateHandler(CalloutHandle& handle) {
    return (impl_->reservationUpdateHandler(handle));
}

int
HostCmds::reservationGetByAddressHandler(CalloutHandle& handle) {
    return (impl_->reservationGetByAddressHandler(handle));
}

}  // namespace host_cmds
}  // namespace isc
