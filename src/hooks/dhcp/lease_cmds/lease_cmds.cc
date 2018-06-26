// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <config/command_mgr.h>
#include <config/cmds_impl.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcp/duid.h>
#include <hooks/hooks.h>
#include <exceptions/exceptions.h>
#include <lease_cmds.h>
#include <lease_parser.h>
#include <lease_cmds_log.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>
#include <sstream>

using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace std;

namespace isc {
namespace lease_cmds {

/// @brief Wrapper class around reservation command handlers.
class LeaseCmdsImpl : private CmdsImpl {
public:

    /// @brief Parameters specified for lease commands.
    class Parameters {
    public:

        /// @brief specifies type of query (by IP addr, by hwaddr, by DUID)
        typedef enum {
            TYPE_ADDR,      ///< query by IP address (either v4 or v6)
            TYPE_HWADDR,    ///< query by hardware address (v4 only)
            TYPE_DUID,      ///< query by DUID (v6 only)
            TYPE_CLIENT_ID  ///< query by client identifier (v4 only).
        } Type;

        /// @brief Specifies subnet-id (always used)
        SubnetID subnet_id;

        /// @brief Specifies IPv4/v6 address (used when query_type is TYPE_ADDR)
        IOAddress addr;

        /// @brief Specifies hardware address (used when query_type is TYPE_HWADDR)
        HWAddrPtr hwaddr;

        /// @brief Specifies identifier value (used when query_type is TYPE_DUID)
        isc::dhcp::DuidPtr duid;

        /// @brief Specifies identifier value (used when query_type is TYPE_CLIENT_ID)
        isc::dhcp::ClientIdPtr client_id;

        /// @brief Attempts to covert text to one of specified types
        ///
        /// Supported values are: "address", hw-address and duid.
        ///
        /// @param txt text to be converted
        /// @return value converted to Parameters::Type
        /// @throw BadValue if unsupported type is specified
        static Type txtToType(const std::string& txt) {
            if (txt == "address") {
                return (Parameters::TYPE_ADDR);
            } else if (txt == "hw-address") {
                return (Parameters::TYPE_HWADDR);
            } else if (txt == "duid") {
                return (Parameters::TYPE_DUID);
            } else if (txt == "client-id") {
                return (Parameters::TYPE_CLIENT_ID);
            } else {
                isc_throw(BadValue, "Incorrect identifier type: "
                          << txt << ", the only supported values are: "
                          "address, hw-address, duid");
            }
        }

        /// @brief specifies parameter types (true = query by address, false =
        ///         query by identifier-type,identifier)
        Type query_type;

        /// @brief Lease type (NA,TA or PD) used for v6 leases
        Lease::Type lease_type;

        /// @brief IAID identifier used for v6 leases
        uint32_t iaid;

        /// @brief Default constructor.
        Parameters()
            :addr("::"), query_type(TYPE_ADDR), lease_type(Lease::TYPE_NA),
             iaid(0) {
        }
    };

public:

    /// @brief lease4-add, lease6-add command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseAddHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    leaseAddHandler(CalloutHandle& handle);

    /// @brief lease4-get, lease6-get command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseGetHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    leaseGetHandler(CalloutHandle& handle);

    /// @brief lease4-get-all, lease6-get-all commands handler
    ///
    /// These commands attempt to retrieve all IPv4 or IPv6 leases,
    /// or all IPv4 or all IPv6 leases belonging to the particular
    /// subnets. If no subnet identifiers are provided, it returns all
    /// IPv4 or IPv6 leases from the database.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise.
    int
    leaseGetAllHandler(CalloutHandle& handle);

    /// @brief lease4-get-page, lease6-get-page commands handler
    ///
    /// These commands attempt to retrieve 1 page of all IPv4 or IPv6
    /// leases. The size of the page is specified by the caller. The
    /// caller also specifies the last address returned in the previous
    /// page. The new page starts from the first address following the
    /// address specified by the caller. If the first page should be
    /// returned the IPv4 zero address, IPv6 zero address or the keyword
    /// "begin" should be provided instead of the last address.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get commands JSON text in the "command" argument.
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetPageHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-del command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease4DelHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// delete command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    lease4DelHandler(CalloutHandle& handle);

    /// @brief lease6-del command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease6DelHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// delete command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    lease6DelHandler(CalloutHandle& handle);

    /// @brief lease4-update handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease4UpdateHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// update command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    lease4UpdateHandler(CalloutHandle& handle);

    /// @brief lease6-update handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease6UpdateHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// update command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    lease6UpdateHandler(CalloutHandle& handle);

    /// @brief lease4-wipe handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease4WipeHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// wipe command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    lease4WipeHandler(CalloutHandle& handle);

    /// @brief lease6-wipe handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease6WipeHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// wipe command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    lease6WipeHandler(CalloutHandle& handle);

    /// @brief Extracts parameters required for reservation-get and reservation-del
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param v6 whether addresses allowed are v4 (false) or v6 (true)
    /// @param args arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    Parameters getParameters(bool v6, const ConstElementPtr& args);
};

int
LeaseCmdsImpl::leaseAddHandler(CalloutHandle& handle) {
    // Arbitrary defaulting to DHCPv4 or with other words extractCommand
    // below is not expected to throw...
    bool v4 = true;
    string txt = "malformed command";
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-add");

        txt = "(missing parameters)";
        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        txt = cmd_args_->str();

        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();

        Lease4Ptr lease4;
        Lease6Ptr lease6;
        // This parameter is ignored for the commands adding the lease.
        bool force_create = false;
        if (v4) {
            Lease4Parser parser;
            lease4 = parser.parse(config, cmd_args_, force_create);

            // checkLeaseIntegrity(config, lease4);

            if (lease4) {
                LeaseMgrFactory::instance().addLease(lease4);
            }

        } else {
            Lease6Parser parser;
            lease6 = parser.parse(config, cmd_args_, force_create);

            // checkLeaseIntegrity(config, lease6);

            if (lease6) {
                LeaseMgrFactory::instance().addLease(lease6);
            }
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, v4 ? LEASE_CMDS_ADD4_FAILED : LEASE_CMDS_ADD6_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(lease_cmds_logger,
             v4 ? LEASE_CMDS_ADD4 : LEASE_CMDS_ADD6).arg(txt);
    setSuccessResponse(handle, "Lease added.");
    return (0);
}

LeaseCmdsImpl::Parameters
LeaseCmdsImpl::getParameters(bool v6, const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    // We support several sets of parameters for leaseX-get/lease-del:
    // lease-get(type, address)
    // lease-get(type, subnet-id, identifier-type, identifier)

    if (params->contains("type")) {
        string t = params->get("type")->stringValue();
        if (t == "IA_NA" || t == "0") {
            x.lease_type = Lease::TYPE_NA;
        } else if (t == "IA_TA" || t == "1") {
            x.lease_type = Lease::TYPE_TA;
        } else if (t == "IA_PD" || t == "2") {
            x.lease_type = Lease::TYPE_PD;
        } else if (t == "V4" || t == "3") {
            x.lease_type = Lease::TYPE_V4;
        } else {
            isc_throw(BadValue, "Invalid lease type specified: "
                      << t << ", only supported values are: IA_NA, IA_TA,"
                      << " IA_PD and V4");
        }
    }

    ConstElementPtr tmp = params->get("ip-address");
    if (tmp) {
        if (tmp->getType() != Element::string) {
            isc_throw(BadValue, "'ip-address' is not a string.");
        }

        x.addr = IOAddress(tmp->stringValue());

        if ((v6 && !x.addr.isV6()) || (!v6 && !x.addr.isV4())) {
            stringstream txt;
            txt << "Invalid " << (v6 ? "IPv6" : "IPv4")
                << " address specified: " << tmp->stringValue();
            isc_throw(BadValue, txt.str());
        }

        x.query_type = Parameters::TYPE_ADDR;
        return (x);
    }

    tmp = params->get("subnet-id");
    if (!tmp) {
        isc_throw(BadValue, "Mandatory 'subnet-id' parameter missing.");
    }
    if (tmp->getType() != Element::integer) {
        isc_throw(BadValue, "'subnet-id' parameter is not integer.");
    }
    x.subnet_id = tmp->intValue();

    if (params->contains("iaid")) {
        x.iaid = params->get("iaid")->intValue();
    }

    // No address specified. Ok, so it must be identifier based query.
    // "identifier-type": "duid",
    // "identifier": "aa:bb:cc:dd:ee:..."

    ConstElementPtr type = params->get("identifier-type");
    ConstElementPtr ident = params->get("identifier");
    if (!type || type->getType() != Element::string) {
        isc_throw(BadValue, "No 'ip-address' provided"
                  " and 'identifier-type' is either missing or not a string.");
    }
    if (!ident || ident->getType() != Element::string) {
        isc_throw(BadValue, "No 'ip-address' provided"
                  " and 'identifier' is either missing or not a string.");
    }

    // Got the parameters. Let's see if their values make sense.
    // Try to convert identifier-type
    x.query_type = Parameters::txtToType(type->stringValue());

    switch (x.query_type) {
    case Parameters::TYPE_HWADDR: {
        HWAddr hw = HWAddr::fromText(ident->stringValue());
        x.hwaddr = HWAddrPtr(new HWAddr(hw));
        break;
    }
    case Parameters::TYPE_CLIENT_ID: {
        x.client_id = ClientId::fromText(ident->stringValue());
        break;
    }
    case Parameters::TYPE_DUID: {
        DUID duid = DUID::fromText(ident->stringValue());
        x.duid = DuidPtr(new DUID(duid));
        break;
    }
    case Parameters::TYPE_ADDR: {
        // We should never get here. The address clause should have been caught
        // earlier.
        return (x);
    }
    default: {
        isc_throw(BadValue, "Identifier type " << type->stringValue() <<
                  " is not supported.");
    }
    }
    return (x);
}

int
LeaseCmdsImpl::leaseGetHandler(CalloutHandle& handle) {
    Parameters p;
    Lease4Ptr lease4;
    Lease6Ptr lease6;
    bool v4;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-get");

        p = getParameters(!v4, cmd_args_);
        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {
            // Query by address
            if (v4) {
                lease4 = LeaseMgrFactory::instance().getLease4(p.addr);
            } else {
                lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, p.addr);
            }
            break;
        }
        case Parameters::TYPE_HWADDR:
            if (v4) {
                if (!p.hwaddr) {
                    isc_throw(InvalidParameter, "Program error: Query by hw-address "
                                                "requires hwaddr to be specified");
                }

                lease4 = LeaseMgrFactory::instance().getLease4(*p.hwaddr, p.subnet_id);
            } else {
                isc_throw(isc::InvalidParameter, "Query by hw-address is not allowed in v6.");
            }
            break;

        case Parameters::TYPE_DUID:
            if (!v4) {
                if (!p.duid) {
                    isc_throw(InvalidParameter, "Program error: Query by duid "
                                                "requires duid to be specified");
                }

                lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, *p.duid,
                                                               p.iaid, p.subnet_id);
            } else {
                isc_throw(InvalidParameter, "Query by duid is not allowed in v4.");
            }
            break;

        case Parameters::TYPE_CLIENT_ID:
            if (v4) {
                if (!p.client_id) {
                    isc_throw(InvalidParameter, "Program error: Query by client-id "
                                                "requires client-id to be specified");
                }

                lease4 = LeaseMgrFactory::instance().getLease4(*p.client_id, p.subnet_id);
            } else {
                isc_throw(isc::InvalidParameter, "Query by client-id is not allowed in v6.");
            }
            break;

        default: {
            isc_throw(InvalidOperation, "Unknown query type: " << static_cast<int>(p.query_type));
            break;
        }
        }
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (1);
    }

    ElementPtr lease_json;
    if (v4 && lease4) {
        lease_json = lease4->toElement();
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                "IPv4 lease found.", lease_json);
        setResponse(handle, response);
    } else if (!v4 && lease6) {
        lease_json = lease6->toElement();
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                "IPv6 lease found.", lease_json);
        setResponse(handle, response);
    } else {
        // If we got here, the lease has not been found.
        setErrorResponse(handle, "Lease not found.", CONTROL_RESULT_EMPTY);
    }

    return (0);
}

int
LeaseCmdsImpl::leaseGetAllHandler(CalloutHandle& handle) {
    bool v4 = true;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-get-all");

        ElementPtr leases_json = Element::createList();

        // The argument may contain a list of subnets for which leases should
        // be returned.
        if (cmd_args_) {
            ConstElementPtr subnets = cmd_args_->get("subnets");
            if (!subnets) {
                isc_throw(BadValue, "'subnets' parameter not specified");
            }
            if (subnets->getType() != Element::list) {
                isc_throw(BadValue, "'subnets' parameter must be a list");
            }

            const std::vector<ElementPtr>& subnet_ids = subnets->listValue();
            for (auto subnet_id = subnet_ids.begin();
                 subnet_id != subnet_ids.end();
                 ++subnet_id) {
                if ((*subnet_id)->getType() != Element::integer) {
                    isc_throw(BadValue, "listed subnet identifiers must be numbers");
                }

                if (v4) {
                    Lease4Collection leases =
                        LeaseMgrFactory::instance().getLeases4((*subnet_id)->intValue());
                    for (auto lease : leases) {
                        ElementPtr lease_json = lease->toElement();
                        leases_json->add(lease_json);
                    }
                } else {
                    Lease6Collection leases =
                        LeaseMgrFactory::instance().getLeases6((*subnet_id)->intValue());
                    for (auto lease : leases) {
                        ElementPtr lease_json = lease->toElement();
                        leases_json->add(lease_json);
                    }
                }
            }

        } else {
            // There is no 'subnets' argument so let's return all leases.
            if (v4) {
                Lease4Collection leases = LeaseMgrFactory::instance().getLeases4();
                for (auto lease : leases) {
                    ElementPtr lease_json = lease->toElement();
                    leases_json->add(lease_json);
                }
            } else {
                Lease6Collection leases = LeaseMgrFactory::instance().getLeases6();
                for (auto lease : leases) {
                    ElementPtr lease_json = lease->toElement();
                    leases_json->add(lease_json);
                }
            }
        }

        std::ostringstream s;
        s << leases_json->size()
          << " IPv" << (v4 ? "4" : "6")
          << " lease(s) found.";
        ElementPtr args = Element::createMap();
        args->set("leases", leases_json);
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmdsImpl::leaseGetPageHandler(CalloutHandle& handle) {
    bool v4 = true;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-get-page");

        // arguments must always be present
        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the " << cmd_name_
                      << " command");
        }

        // The 'from' argument denotes from which lease we should start the
        // results page. The results page excludes this lease.
        ConstElementPtr from = cmd_args_->get("from");
        if (!from) {
            isc_throw(BadValue, "'from' parameter not specified");
        }

        // The 'from' argument is a string. It may contain a 'start' keyword or
        // an IP address.
        if (from->getType() != Element::string) {
            isc_throw(BadValue, "'from' parameter must be a string");
        }

        boost::scoped_ptr<IOAddress> from_address;
        try {
            if (from->stringValue() == "start") {
                from_address.reset(new IOAddress(v4 ? "0.0.0.0" : "::"));

            } else {
                // Conversion of a string to an IP address may throw.
                from_address.reset(new IOAddress(from->stringValue()));
            }

        } catch (...) {
            isc_throw(BadValue, "'from' parameter value is neither 'start' keyword nor "
                      "a valid IPv" << (v4 ? "4" : "6") << " address");
        }

        // It must be either IPv4 address for lease4-get-page or IPv6 address for
        // lease6-get-page.
        if (v4 && (!from_address->isV4())) {
            isc_throw(BadValue, "'from' parameter value " << from_address->toText()
                      << " is not an IPv4 address");

        } else if (!v4 && from_address->isV4()) {
            isc_throw(BadValue, "'from' parameter value " << from_address->toText()
                      << " is not an IPv6 address");
        }

        // The 'count' is a desired page size. It must always be present.
        ConstElementPtr page_count = cmd_args_->get("count");
        if (!page_count) {
            isc_throw(BadValue, "'count' parameter not specified");
        }

        // The 'count' must be a number.
        if (page_count->getType() != Element::integer) {
            isc_throw(BadValue, "'count' parameter must be a number");
        }

        // Retrieve the desired page size.
        size_t page_count_value = static_cast<size_t>(page_count->intValue());

        ElementPtr leases_json = Element::createList();

        // Use lease stats function to retrieve the total number of leases.
        // Total number of leases is returned apart from the leases list
        // so as the controlling client can track the progress of leases
        // viewed vs all leases count.
        LeaseStatsQueryPtr query;
        if (v4) {
            // Get page of IPv4 leases.
            Lease4Collection leases =
                LeaseMgrFactory::instance().getLeases4(*from_address,
                                                       LeasePageSize(page_count_value));
            // Get the total lease count.
            query = LeaseMgrFactory::instance().startLeaseStatsQuery4();

            // Convert leases into JSON list.
            for (auto lease : leases) {
                ElementPtr lease_json = lease->toElement();
                leases_json->add(lease_json);
            }

        } else {
            // Get page of IPv6 leases.
            Lease6Collection leases =
                LeaseMgrFactory::instance().getLeases6(*from_address,
                                                       LeasePageSize(page_count_value));
            // Get the total lease count.
            query = LeaseMgrFactory::instance().startLeaseStatsQuery6();

            // Convert leases into JSON list.
            for (auto lease : leases) {
                ElementPtr lease_json = lease->toElement();
                leases_json->add(lease_json);
            }
        }

        // Sum up lease counters for various lease states.
        LeaseStatsRow row;
        int64_t total_leases = 0;
        while (query->getNextRow(row)) {
            total_leases += row.state_count_;
        }

        // Prepare textual status.
        std::ostringstream s;
        s << leases_json->size()
          << " IPv" << (v4 ? "4" : "6")
          << " lease(s) found.";
        ElementPtr args = Element::createMap();

        // Put gathered data into arguments map.
        args->set("leases", leases_json);
        args->set("count", Element::create(static_cast<int64_t>(leases_json->size())));
        args->set("total-count", Element::create(total_leases));

        // Create the response.
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

int
LeaseCmdsImpl::lease4DelHandler(CalloutHandle& handle) {
    Parameters p;
    Lease4Ptr lease4;
    IOAddress addr(IOAddress::IPV4_ZERO_ADDRESS());
    try {
        extractCommand(handle);
        p = getParameters(false, cmd_args_);

        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {

            // If address was specified explicitly, let's use it as is.
            addr = p.addr;
            break;
        }
        case Parameters::TYPE_HWADDR:
            if (!p.hwaddr) {
                isc_throw(InvalidParameter, "Program error: Query by hw-address "
                                            "requires hwaddr to be specified");
            }

            // Let's see if there's such a lease at all.
            lease4 = LeaseMgrFactory::instance().getLease4(*p.hwaddr, p.subnet_id);
            if (!lease4) {
                setErrorResponse(handle, "IPv4 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }

            // Found it, can use it as is.
            addr = lease4->addr_;
            break;

        case Parameters::TYPE_CLIENT_ID:
            if (!p.client_id) {
                isc_throw(InvalidParameter, "Program error: Query by client-id "
                                            "requires client-id to be specified");
            }

            // Let's see if there's such a lease at all.
            lease4 = LeaseMgrFactory::instance().getLease4(*p.client_id, p.subnet_id);
            if (!lease4) {
                setErrorResponse(handle, "IPv4 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }

            // Found it, can use it as is.
            addr = lease4->addr_;
            break;

        case Parameters::TYPE_DUID:
            isc_throw(InvalidParameter, "Delete by duid is not allowed in v4.");
            break;

        default: {
            isc_throw(InvalidOperation, "Unknown query type: " << static_cast<int>(p.query_type));
            break;
        }
        }

        if (LeaseMgrFactory::instance().deleteLease(addr)) {
            setSuccessResponse(handle, "IPv4 lease deleted.");
        } else {
            setErrorResponse (handle, "IPv4 lease not found.", CONTROL_RESULT_EMPTY);
        }
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmdsImpl::lease6DelHandler(CalloutHandle& handle) {
    Parameters p;
    Lease6Ptr lease6;
    IOAddress addr(IOAddress::IPV6_ZERO_ADDRESS());
    try {
        extractCommand(handle);
        p = getParameters(true, cmd_args_);

        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {

            // If address was specified explicitly, let's use it as is.
            addr = p.addr;
            break;
        }
        case Parameters::TYPE_HWADDR:
            isc_throw(InvalidParameter, "Delete by hw-address is not allowed in v6.");
            break;

        case Parameters::TYPE_DUID:
            if (!p.duid) {
                isc_throw(InvalidParameter, "Program error: Query by duid "
                                            "requires duid to be specified");
            }

            // Let's see if there's such a lease at all.
            lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, *p.duid,
                                                           p.iaid, p.subnet_id);
            if (!lease6) {
                setErrorResponse(handle, "IPv6 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }

            // Found it, can use it as is.
            addr = lease6->addr_;
            break;

        default: {
            isc_throw(InvalidOperation, "Unknown query type: " << static_cast<int>(p.query_type));
            break;
        }
        }

        if (LeaseMgrFactory::instance().deleteLease(addr)) {
            setSuccessResponse(handle, "IPv6 lease deleted.");
        } else {
            setErrorResponse (handle, "IPv6 lease not found.", CONTROL_RESULT_EMPTY);
        }
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmdsImpl::lease4UpdateHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // We need the lease to be specified.
        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for lease4-update command");
        }

        // Get the parameters specified by the user first.
        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
        Lease4Ptr lease4;
        Lease4Parser parser;
        bool force_create = false;

        // The parser does sanity checks (if the address is in scope, if
        // subnet-id is valid, etc)
        lease4 = parser.parse(config, cmd_args_, force_create);
        if (force_create && !LeaseMgrFactory::instance().getLease4(lease4->addr_)) {
            LeaseMgrFactory::instance().addLease(lease4);
            setSuccessResponse(handle, "IPv4 lease added.");

        } else {
            LeaseMgrFactory::instance().updateLease4(lease4);
            setSuccessResponse(handle, "IPv4 lease updated.");
        }
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmdsImpl::lease6UpdateHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // We need the lease to be specified.
        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for lease6-update command");
        }

        // Get the parameters specified by the user first.
        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
        Lease6Ptr lease6;
        Lease6Parser parser;
        bool force_create = false;

        // The parser does sanity checks (if the address is in scope, if
        // subnet-id is valid, etc)
        lease6 = parser.parse(config, cmd_args_, force_create);
        if (force_create && !LeaseMgrFactory::instance().getLease6(lease6->type_,
                                                                   lease6->addr_)) {
            LeaseMgrFactory::instance().addLease(lease6);
            setSuccessResponse(handle, "IPv6 lease added.");
        } else {
            LeaseMgrFactory::instance().updateLease6(lease6);
            setSuccessResponse(handle, "IPv6 lease updated.");
        }
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmdsImpl::lease4WipeHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        SimpleParser parser;
        SubnetID id = 0;

        size_t num = 0; // number of leases deleted
        stringstream ids; // a text with subnet-ids being wiped

        // The subnet-id parameter is now optional.
        if (cmd_args_ && cmd_args_->contains("subnet-id")) {
            id = parser.getUint32(cmd_args_, "subnet-id");
        }

        if (id) {
            // Wipe a single subnet
            num = LeaseMgrFactory::instance().wipeLeases4(id);
            ids << " " << id;
        } else {
            // Wipe them all!
            ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
            ConstCfgSubnets4Ptr subnets = config->getCfgSubnets4();
            const Subnet4Collection * subs = subnets->getAll();

            // Go over all subnets and wipe leases in each of them.
            for (auto sub : *subs) {
                num += LeaseMgrFactory::instance().wipeLeases4(sub->getID());
                ids << " " << sub->getID();
            }
        }

        stringstream tmp;
        tmp << "Deleted " << num << " IPv4 lease(s) from subnet(s)" << ids.str();
        ConstElementPtr response = createAnswer(num ? CONTROL_RESULT_SUCCESS
                                                    : CONTROL_RESULT_EMPTY, tmp.str());
        setResponse(handle, response);
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmdsImpl::lease6WipeHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        SimpleParser parser;
        SubnetID id = 0;

        size_t num = 0; // number of leases deleted
        stringstream ids; // a text with subnet-ids being wiped

        /// @todo: consider extending the code with wipe-leases:
        /// - of specific type (v6)
        /// - from specific shared network
        /// - from specific pool
        /// see https://kea.isc.org/ticket/5543#comment:6 for background.

        // The subnet-id parameter is now optional.
        if (cmd_args_ && cmd_args_->contains("subnet-id")) {
            id = parser.getUint32(cmd_args_, "subnet-id");
        }

        if (id) {
            // Wipe a single subnet.
            num = LeaseMgrFactory::instance().wipeLeases6(id);
            ids << " " << id;
       } else {
            // Wipe them all!
            ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
            ConstCfgSubnets6Ptr subnets = config->getCfgSubnets6();
            const Subnet6Collection * subs = subnets->getAll();

            // Go over all subnets and wipe leases in each of them.
            for (auto sub : *subs) {
                num += LeaseMgrFactory::instance().wipeLeases6(sub->getID());
                ids << " " << sub->getID();
            }
        }

        stringstream tmp;
        tmp << "Deleted " << num << " IPv6 lease(s) from subnet(s)" << ids.str();
        ConstElementPtr response = createAnswer(num ? CONTROL_RESULT_SUCCESS
                                                    : CONTROL_RESULT_EMPTY, tmp.str());
        setResponse(handle, response);
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmds::leaseAddHandler(CalloutHandle& handle) {
    return(impl_->leaseAddHandler(handle));
}

int
LeaseCmds::leaseGetHandler(CalloutHandle& handle) {
    return(impl_->leaseGetHandler(handle));
}

int
LeaseCmds::leaseGetAllHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetAllHandler(handle));
}

int
LeaseCmds::leaseGetPageHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetPageHandler(handle));
}

int
LeaseCmds::lease4DelHandler(CalloutHandle& handle) {
    return(impl_->lease4DelHandler(handle));
}

int
LeaseCmds::lease6DelHandler(CalloutHandle& handle) {
    return(impl_->lease6DelHandler(handle));
}

int
LeaseCmds::lease4UpdateHandler(CalloutHandle& handle) {
    return(impl_->lease4UpdateHandler(handle));
}

int
LeaseCmds::lease6UpdateHandler(CalloutHandle& handle) {
    return(impl_->lease6UpdateHandler(handle));
}

int
LeaseCmds::lease4WipeHandler(CalloutHandle& handle) {
   return(impl_->lease4WipeHandler(handle));
}

int
LeaseCmds::lease6WipeHandler(CalloutHandle& handle) {
   return(impl_->lease6WipeHandler(handle));
}

LeaseCmds::LeaseCmds()
    :impl_(new LeaseCmdsImpl()) {
}

};
};
