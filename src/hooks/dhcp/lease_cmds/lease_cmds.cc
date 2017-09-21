// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <lease_cmds.h>
#include <config/command_mgr.h>
#include <lease_parser.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <asiolink/io_address.h>
#include <lease_cmds_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcp/duid.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <exceptions/exceptions.h>
#include <boost/bind.hpp>
#include <string>

using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;
using namespace isc::asiolink;
using namespace std;

namespace isc {
namespace lease_cmds {

/// @brief Wrapper class around reservation command handlers.
class LeaseCmdsImpl {
public:
    /// @brief Parameters specified for reservation-get and reservation-del
    ///
    /// As both call types (get and delete) need specify which reservation to
    /// act on, they have the same set of parameters. In particular, those
    /// two call types support the following sets of parameters:
    /// - address
    /// - subnet-id, identifier-type, identifier-value (v4)
    /// - subnet-id, lease-type, iaid, identifier-type, identifier-value (v6)
    ///
    /// This class stores those parameters and is used to pass them around.
    class Parameters {
    public:

        /// @brief specifies type of query (by IP addr, by hwaddr, by DUID)
        typedef enum {
            TYPE_ADDR,    ///< query by IP address (either v4 or v6)
            TYPE_HWADDR,  ///< query by hardware address (v4 only)
            TYPE_DUID     ///< query by DUID (v6 only)
        } Type;

        /// @brief Specifies subnet-id (always used)
        SubnetID subnet_id;

        /// @brief Specifies IPv4/v6 address (used when query_type is TYPE_ADDR)
        IOAddress addr;

        /// @brief Specifies hardware address (used when query_type is TYPE_HWADDR)
        HWAddrPtr hwaddr;

        /// @brief Specifies identifier value (used when query_type is TYPE_DUID)
        isc::dhcp::DuidPtr duid;

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
    /// This command attempts to add a lease.
    ///
    /// An example full command looks as follows. Note that the args
    /// parameter is expected to contain the "arguments" portion of it.
    /// This function covers both v4 and v6 leases.
    ///
    /// Example command for v4:
    /// {
    ///     "command": "lease4-add",
    ///     "parameters": {
    ///         "address": "192.0.2.1",
    ///         "hwaddr": "00:01:02:03:04:05",
    ///         "client-id": "this-is-a-client",
    ///         "valid-lft": 3600,
    ///         "expire": 12345678,
    ///         "subnet-id": 1,
    ///         "fqdn-fwd": true,
    ///         "fqdn-rev": true,
    ///         "hostname": "myhost.example.org",
    ///         "state": 0
    ///     }
    /// }
    /// Example command for v6:
    /// {
    ///     "command": "lease6-add",
    ///     "arguments": {
    ///         "subnet-id": 66,
    ///         "ip-address": "2001:db8:abcd::",
    ///         "type": "IA_PD",
    ///         "prefix-len": 48,
    ///         "duid": "01:02:03:04:05:06:07:08",
    ///         "iaid": 1234,
    ///         "preferred-lft": 500,
    ///         "valid-lft": 1000,
    ///         "expire": 12345678,
    ///         "fqdn-fwd": true,
    ///         "fqdn-rev": true,
    ///         "hostname": "urania.example.org""
    ///     }
    /// }

    ///
    /// @param command should be 'lease4-add' or 'lease6-add'
    /// @param args must contain host reservation definition.
    /// @return result of the operation
    ConstElementPtr
    leaseAddHandler(const string& command, ConstElementPtr args);

    /// @brief lease4-get, lease6-get command handler
    ///
    /// This command attempts to retrieve a lease that match selected criteria.
    /// The following types of parameters are supported:
    /// - (subnet-id, address) for both v4 and v6
    /// - (subnet-id, identifier-type, identifier) for v4
    /// - (subnet-id, type, iana, identifier-type, identifier) for v6
    ///
    /// Example command for query by (subnet-id, address):
    /// {
    ///     "command": "lease4-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, identifier-type, identifier)
    /// {
    ///     "command": "lease4-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, type, iana, identifier-type,
    ///                               identifier):
    /// {
    ///     "command": "lease6-get",
    ///     "arguments": {
    ///     "subnet-id": 66,
    ///     "iaid": 42,
    ///     "type": "IA_NA",
    ///     "identifier-type": "duid",
    ///     "identifier": "77:77:77:77:77:77:77:77"
    ///     }
    /// }
    /// @param command "lease4-get" or "lease6-get"
    /// @param args must contain host reservation definition.
    /// @return result of the operation (includes lease details, if found)
    ConstElementPtr
    leaseGetHandler(const string& command, ConstElementPtr args);

    /// @brief lease4-del command handler
    ///
    /// This command attempts to delete an IPv4 lease that match selected
    /// criteria. Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, identifier-type, identifier).
    ///
    /// Example command for deletion by (subnet-id, address):
    /// {
    ///     "command": "lease4-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for deletion by (subnet-id, identifier-type, identifier)
    /// {
    ///     "command": "lease4-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }";
    /// @param command should be 'lease4-del' (but it's ignored)
    /// @param args must contain host reservation definition.
    /// @return result of the operation (host will be included as parameters, if found)
    ConstElementPtr
    lease4DelHandler(const string& command, ConstElementPtr args);

    /// @brief lease6-del command handler
    ///
    /// This command attempts to delete a lease that match selected criteria.
    /// Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, type, iaid, identifier-type, identifier).
    ///
    /// Example command for deletion by (subnet-id, address):
    /// {
    ///     "command": "lease6-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for deletion by (subnet-id, type, iaid, identifier-type,
    /// identifier):
    /// {
    ///     "command": "lease6-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "type": "IA_NA",
    ///         "iaid": 123456,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }";
    /// @param command should be 'lease6-del' (but it's ignored)
    /// @param args must contain host reservation definition.
    /// @return result of the operation (host will be included as parameters, if found)
    ConstElementPtr
    lease6DelHandler(const string& command, ConstElementPtr args);

    /// @brief lease4-update handler
    ///
    /// This command attempts to update existing IPv4 lease. The parameters
    /// specified will replace existing lease. The only condition is that
    /// the IP address must not change. If you want to change the IP address,
    /// please use lease4-del and lease4-add instead.
    ///
    /// Example command:
    /// {
    ///     "command": "lease4-update",
    ///     "arguments": {
    ///         "subnet-id": 44,
    ///         "ip-address": "192.0.2.1",
    ///         "hw-address": "1a:1b:1c:1d:1e:1f",
    ///         "hostname": "newhostname.example.org"
    ///     }
    /// };
    ///
    /// @param command - should be "lease4-update", but it is ignored
    /// @param args arguments that describe the lease being updated.
    ConstElementPtr
    lease4UpdateHandler(const string& command, ConstElementPtr args);

    /// @brief lease6-update handler
    ///
    /// This command attempts to update existing IPv6 lease. The parameters
    /// specified will replace existing lease. The only condition is that
    /// the IP address must not change. If you want to change the IP address,
    /// please use lease6-del and lease6-add instead.
    ///
    /// Example command:
    /// {
    ///     "command": "lease6-update",
    ///     "arguments": {
    ///         "subnet-id": 66,
    ///         "ip-address": "2001:db8::1",
    ///         "iaid": 7654321,
    ///         "duid": "88:88:88:88:88:88:88:88",
    ///         "hostname": "newhostname.example.org"
    ///     }
    /// }";
    ///
    /// @param command - should be "lease6-update" (but it is ignored)
    /// @param args arguments that describe the lease being updated.
    ConstElementPtr
    lease6UpdateHandler(const string& command, ConstElementPtr args);

    /// @brief lease4-wipe handler
    ///
    /// This commands attempts to remove all IPv4 leases from a specific
    /// subnet. Currently the leases are removed from the database,
    /// without any processing (like calling hooks or doing DDNS
    /// cleanups).
    ///
    /// Example command:
    /// {\n"
    ///     "command": "lease4-wipe",\n"
    ///     "arguments": {"
    ///         "subnet-id": 44
    ///     }\n"
    /// }";
    /// @param command - should be "lease4-wipe" (but is ignored)
    /// @param args arguments that describe the lease being updated.
    ConstElementPtr
    lease4WipeHandler(const string& command, ConstElementPtr args);

    /// @brief lease6-wipe handler
    ///
    /// This commands attempts to remove all IPv4 leases from a specific
    /// subnet. Currently the leases are removed from the database,
    /// without any processing (like calling hooks or doing DDNS
    /// cleanups).
    ///
    /// Example command:
    /// {\n"
    ///     "command": "lease4-wipe",\n"
    ///     "arguments": {"
    ///         "subnet-id": 44
    ///     }\n"
    /// }";
    /// @param command - should be "lease4-wipe" (but is ignored)
    /// @param args arguments that describe the lease being updated.
    ConstElementPtr
    lease6WipeHandler(const string& command, ConstElementPtr args);

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

ConstElementPtr
LeaseCmdsImpl::leaseAddHandler(const std::string& name,
                               ConstElementPtr params) {
    bool v4 = (name == "lease4-add");

    string txt = "(missing parameters)";
    if (params) {
        txt = params->str();
    }

    try {
        if (!params) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();

        Lease4Ptr lease4;
        Lease6Ptr lease6;
        if (v4) {
            Lease4Parser parser;
            lease4 = parser.parse(config, params);

            // checkLeaseIntegrity(config, lease4);

            if (lease4) {
                LeaseMgrFactory::instance().addLease(lease4);
            }

        } else {
            Lease6Parser parser;
            lease6 = parser.parse(config, params);

            // checkLeaseIntegrity(config, lease6);

            if (lease6) {
                LeaseMgrFactory::instance().addLease(lease6);
            }
        }


    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, v4 ? LEASE_CMDS_ADD4_FAILED : LEASE_CMDS_ADD6_FAILED)
            .arg(txt)
            .arg(ex.what());
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
    LOG_INFO(lease_cmds_logger,
             v4 ? LEASE_CMDS_ADD4 : LEASE_CMDS_ADD6).arg(txt);
    return (createAnswer(CONTROL_RESULT_SUCCESS, "Lease added."));
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

ConstElementPtr
LeaseCmdsImpl::leaseGetHandler(const std::string& name, ConstElementPtr params) {
    Parameters p;
    Lease4Ptr lease4;
    Lease6Ptr lease6;
    bool v4 = (name == "lease4-get");
    try {
        p = getParameters(!v4, params);

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
                    return (createAnswer(CONTROL_RESULT_ERROR,
                                         "Program error: Query by hw-address "
                                         "requires hwaddr to be specified"));
                }
                lease4 = LeaseMgrFactory::instance().getLease4(*p.hwaddr, p.subnet_id);
            } else {
                return (createAnswer(CONTROL_RESULT_ERROR,
                                     "Query by hw-address is not allowed in v6."));
            }
            break;
        case Parameters::TYPE_DUID:
            if (!v4) {
                if (!p.duid) {
                    return (createAnswer(CONTROL_RESULT_ERROR,
                                         "Program error: Query by duid "
                                         "requires duid to be specified"));
                }
                lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, *p.duid,
                                                               p.iaid, p.subnet_id);
            } else {
                return (createAnswer(CONTROL_RESULT_ERROR,
                                     "Query by duid is not allowed in v4."));
            }
            break;
        default: {
            stringstream tmp;
            tmp << "Unknown query type: " << static_cast<int>(p.query_type);
            return (createAnswer(CONTROL_RESULT_ERROR, tmp.str()));
        }
        }
    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }

    ElementPtr lease_json;
    if (v4 && lease4) {
        lease_json = lease4->toElement();
        return (createAnswer(CONTROL_RESULT_SUCCESS, "IPv4 lease found.", lease_json));
    }
    if (!v4 && lease6) {
        lease_json = lease6->toElement();
        return (createAnswer(CONTROL_RESULT_SUCCESS, "IPv6 lease found.", lease_json));

    }

    // If we got here, the lease has not been found.
    return (createAnswer(CONTROL_RESULT_EMPTY, "Lease not found."));
}

ConstElementPtr
LeaseCmdsImpl::lease4DelHandler(const std::string& , ConstElementPtr params) {
    Parameters p;
    Lease4Ptr lease4;
    IOAddress addr(IOAddress::IPV4_ZERO_ADDRESS());
    try {
        p = getParameters(false, params);

        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {

            // If address was specified explicitly, let's use it as is.
            addr = p.addr;
            break;
        }
        case Parameters::TYPE_HWADDR:
            if (!p.hwaddr) {
                return (createAnswer(CONTROL_RESULT_ERROR,
                                     "Program error: Query by hw-address "
                                     "requires hwaddr to be specified"));
            }

            // Let's see if there's such a lease at all.
            lease4 = LeaseMgrFactory::instance().getLease4(*p.hwaddr, p.subnet_id);
            if (!lease4) {
                return (createAnswer(CONTROL_RESULT_EMPTY, "IPv4 lease not found."));
            }

            // Found it, can use it as is.
            addr = lease4->addr_;
            break;

        case Parameters::TYPE_DUID:
            return (createAnswer(CONTROL_RESULT_ERROR,
                                     "Delete by duid is not allowed in v4."));
            break;

        default: {
            stringstream tmp;
            tmp << "Unknown query type: " << static_cast<int>(p.query_type);
            return (createAnswer(CONTROL_RESULT_ERROR, tmp.str()));
        }
        }

        if (LeaseMgrFactory::instance().deleteLease(addr)) {
            return (createAnswer(CONTROL_RESULT_SUCCESS, "IPv4 lease deleted."));
        } else {
            return (createAnswer(CONTROL_RESULT_EMPTY, "IPv4 lease not found."));
        }
    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
}

ConstElementPtr
LeaseCmdsImpl::lease6DelHandler(const std::string& , ConstElementPtr params) {
    Parameters p;
    Lease6Ptr lease6;
    IOAddress addr(IOAddress::IPV6_ZERO_ADDRESS());
    try {
        p = getParameters(true, params);

        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {

            // If address was specified explicitly, let's use it as is.
            addr = p.addr;
            break;
        }
        case Parameters::TYPE_HWADDR:
            return (createAnswer(CONTROL_RESULT_ERROR,
                                 "Delete by hw-address is not allowed in v6."));

        case Parameters::TYPE_DUID:
            if (!p.duid) {
                return (createAnswer(CONTROL_RESULT_ERROR,
                                     "Program error: Query by duid "
                                     "requires duid to be specified"));
            }

            // Let's see if there's such a lease at all.
            lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, *p.duid,
                                                           p.iaid, p.subnet_id);
            if (!lease6) {
                return (createAnswer(CONTROL_RESULT_EMPTY, "IPv6 lease not found."));
            }

            // Found it, can use it as is.
            addr = lease6->addr_;
            break;

        default: {
            stringstream tmp;
            tmp << "Unknown query type: " << static_cast<int>(p.query_type);
            return (createAnswer(CONTROL_RESULT_ERROR, tmp.str()));
        }
        }

        if (LeaseMgrFactory::instance().deleteLease(addr)) {
            return (createAnswer(CONTROL_RESULT_SUCCESS, "IPv6 lease deleted."));
        } else {
            return (createAnswer(CONTROL_RESULT_EMPTY, "IPv6 lease not found."));
        }
    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
}

ConstElementPtr
LeaseCmdsImpl::lease4UpdateHandler(const string& , ConstElementPtr params) {
    try {

        // We need the lease to be specified.
        if (!params) {
            isc_throw(isc::BadValue, "no parameters specified for lease4-update command");
        }

        // Get the parameters specified by the user first.
        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
        Lease4Ptr lease4;
        Lease4Parser parser;
        // The parser does sanity checks (if the address is in scope, if
        // subnet-id is valid, etc)
        lease4 = parser.parse(config, params);

        LeaseMgrFactory::instance().updateLease4(lease4);
        return (createAnswer(CONTROL_RESULT_SUCCESS, "IPv4 lease updated."));

    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
}

ConstElementPtr
LeaseCmdsImpl::lease6UpdateHandler(const string& , ConstElementPtr params) {
    try {
        // We need the lease to be specified.
        if (!params) {
            isc_throw(isc::BadValue, "no parameters specified for lease6-update command");
        }

        // Get the parameters specified by the user first.
        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
        Lease6Ptr lease6;
        Lease6Parser parser;
        // The parser does sanity checks (if the address is in scope, if
        // subnet-id is valid, etc)
        lease6 = parser.parse(config, params);

        LeaseMgrFactory::instance().updateLease6(lease6);
        return (createAnswer(CONTROL_RESULT_SUCCESS, "IPv6 lease updated."));

    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
}

ConstElementPtr
LeaseCmdsImpl::lease4WipeHandler(const string& /*cmd*/, ConstElementPtr params) {
    try {

        // The subnet-id is a mandatory parameter.
        if (!params) {
            isc_throw(isc::BadValue, "no parameters specified for lease4-wipe command");
        }
        SimpleParser parser;
        SubnetID id = parser.getUint32(params, "subnet-id");

        size_t num = LeaseMgrFactory::instance().wipeLeases4(id);

        stringstream tmp;
        tmp << "Deleted " << num << " IPv4 lease(s).";
        return (createAnswer(num ? CONTROL_RESULT_SUCCESS : CONTROL_RESULT_EMPTY,
                             tmp.str()));
    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
}

ConstElementPtr
LeaseCmdsImpl::lease6WipeHandler(const string& /*cmd*/, ConstElementPtr params) {
    try {

        // The subnet-id is a mandatory parameter.
        if (!params) {
            isc_throw(isc::BadValue, "no parameters specified for lease6-wipe command");
        }
        SimpleParser parser;
        SubnetID id = parser.getUint32(params, "subnet-id");

        size_t num = LeaseMgrFactory::instance().wipeLeases6(id);

        stringstream tmp;
        tmp << "Deleted " << num << " IPv6 lease(s).";
        return (createAnswer(num ? CONTROL_RESULT_SUCCESS : CONTROL_RESULT_EMPTY,
                             tmp.str()));
    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
}

ConstElementPtr
LeaseCmds::leaseAddHandler(const string& command, ConstElementPtr args) {
    return(impl_->leaseAddHandler(command, args));
}

ConstElementPtr
LeaseCmds::leaseGetHandler(const string& command, ConstElementPtr args) {
    return(impl_->leaseGetHandler(command, args));
}

ConstElementPtr
LeaseCmds::lease4DelHandler(const string& command, ConstElementPtr args) {
    return(impl_->lease4DelHandler(command, args));
}

ConstElementPtr
LeaseCmds::lease6DelHandler(const string& command, ConstElementPtr args) {
    return(impl_->lease6DelHandler(command, args));
}

ConstElementPtr
LeaseCmds::lease4UpdateHandler(const string& command, ConstElementPtr args) {
    return(impl_->lease4UpdateHandler(command, args));
}

ConstElementPtr
LeaseCmds::lease6UpdateHandler(const string& command, ConstElementPtr args) {
    return(impl_->lease6UpdateHandler(command, args));
}

ConstElementPtr
LeaseCmds::lease4WipeHandler(const string& command, ConstElementPtr args) {
    return(impl_->lease4WipeHandler(command, args));
}

ConstElementPtr
LeaseCmds::lease6WipeHandler(const string& command, ConstElementPtr args) {
    return(impl_->lease6WipeHandler(command, args));
}

LeaseCmds::LeaseCmds()
    :impl_(new LeaseCmdsImpl()) {
}

};
};
