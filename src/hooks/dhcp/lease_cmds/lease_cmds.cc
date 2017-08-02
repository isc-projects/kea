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
    LeaseCmdsImpl();

    ~LeaseCmdsImpl();

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

    /// @brief specifies type of query (by IP addr, by hwaddr, by DUID)
    typedef enum {
        TYPE_ADDR,    ///< query by IP address (either v4 or v6)
        TYPE_HWADDR,  ///< query by hardware address (v4 only)
        TYPE_DUID     ///< query by DUID (v6 only)
    } Type;

    /// @brief Specifies subnet-id (always used)
    SubnetID subnet_id;

    /// @brief Specifies IPv4 or IPv6 address (used when query_by_addr is true)
    IOAddress addr;

    /// @brief Specifies identifier type (usually FLEX_ID, used when
    ///        query_by_addr is false)
    HWAddrPtr hwaddr;

    /// @brief Specifies identifier value (used when query_by_addr is false)
    isc::dhcp::DuidPtr duid;

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
    ///         query by indetifier-type,identifier)
    Type query_type;

    Lease::Type lease_type;

    uint32_t iaid;

    /// @brief Default contstructor.
    Parameters()
        :addr("::"), query_type(TYPE_ADDR), lease_type(Lease::TYPE_NA), iaid(0) {
    }
};

private:

    /// @brief Registers commands:
    ///
    /// Registers:
    /// - lease4-add
    /// - lease6-add
    /// - lease4-get
    /// - lease6-get
    /// - lease4-del
    /// - lease6-del
    /// - lease4-update
    /// - lease6-update
    /// - lease4-del-all
    /// - lease6-del-all
    
    /// @throw Unexpected if CommandMgr is not available (should not happen)
    void registerCommands();

    /// @brief Dergisters commands:
    ///
    /// Deregisters:
    /// - lease4-add
    /// - lease6-add
    /// - lease4-get
    /// - lease6-get
    /// - lease4-del
    /// - lease6-del
    /// - lease4-update
    /// - lease6-update
    /// - lease4-del-all
    /// - lease6-del-all
    ///
    /// @throw Unexpected if CommandMgr is not available (should not happen)
    void deregisterCommands();

    /// @brief reservation-add command handler
    ///
    /// This command attempts to add a lease.
    ///
    /// An example full command looks as follows. Note that the args
    /// parameter is expected to contain the "arguments" portion of it.
    /// This function covers v4 lease only.
    ///
    /// Example command
    /// {
    ///     "command": "lease4-add",
    ///     "parameters": {
    ///         "address": "192.0.2.1",
    ///         "hwaddr": "00:01:02:03:04:05",
    ///         "client-id": "this-is-a-client",
    ///         "valid-lft": 3600,
    ///         "expire": 1499282530,
    ///         "subnet-id": 1,
    ///         "fdqn-fwd": true,
    ///         "fqdn-rev": true,
    ///         "hostname": "myhost.example.org",
    ///         "state": 0
    ///     }
    /// }
    ///
    /// @param command should be 'reservation-add' (but it's ignored)
    /// @param args must contain host reservation definition.
    /// @return result of the operation
    static ConstElementPtr
    leaseAddHandler(const string& command, ConstElementPtr args);

    /// @brief reservation-get command handler
    ///
    /// This command attempts to retrieve a host that match selected criteria.
    /// Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, identifier-type, identifier).
    ///
    /// Example command for query by (subnet-id, address):
    /// {
    ///     "command": "reservation-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, identifier-type, identifier)
    /// {
    ///     "command": "reservation-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }";
    /// @param command should be 'reservation-get' (but it's ignored)
    /// @param args must contain host reservation definition.
    /// @return result of the operation (host will be included as parameters, if found)
    static ConstElementPtr
    leaseGetHandler(const string& command, ConstElementPtr args);

    /// @brief reservation-del command handler
    ///
    /// This command attempts to delete a host that match selected criteria.
    /// Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, identifier-type, identifier).
    ///
    /// Note: for this operation to work, hosts-database must be specified
    /// in your configuration file (or from code point of view, alternate_source_
    /// must be set in HostMgr).
    ///
    /// Example command for query by (subnet-id, address):
    /// {
    ///     "command": "reservation-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, identifier-type, identifier)
    /// {
    ///     "command": "reservation-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }";
    /// @param command should be 'reservation-add' (but it's ignored)
    /// @param args must contain host reservation definition.
    /// @return result of the operation (host will be included as parameters, if found)
    static ConstElementPtr
    leaseDelHandler(const string& command, ConstElementPtr args);

    static ConstElementPtr
    leaseUpdateHandler(const string& command, ConstElementPtr args);

    static ConstElementPtr
    leaseWipeHandler(const string& command, ConstElementPtr args);
    
    /// @brief Extracts parameters required for reservation-get and reservation-del
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param args - arguments passed to command
    /// @return parsed parameters
    /// @throw BadValue if input arguments don't make sense.
    static Parameters getParameters(const ConstElementPtr& args);

    /// @brief Covenience pointer used to access database storage
    static HostDataSourcePtr db_storage_;

    /// @brief Protocol family (IPv4 or IPv6)
    static uint16_t family_;
};

LeaseCmdsImpl::LeaseCmdsImpl() {
    /// @todo: Remove family_
    family_ = CfgMgr::instance().getFamily();

    registerCommands();
}

LeaseCmdsImpl::~LeaseCmdsImpl() {
    deregisterCommands();
}

void LeaseCmdsImpl::registerCommands() {
    /// @todo: Use registration mechanism once #5321 discussion is done
    CommandMgr::instance().registerCommand("lease4-add",
        boost::bind(&LeaseCmdsImpl::leaseAddHandler, _1, _2));
    CommandMgr::instance().registerCommand("lease6-add",
        boost::bind(&LeaseCmdsImpl::leaseAddHandler, _1, _2));

    CommandMgr::instance().registerCommand("lease4-get",
        boost::bind(&LeaseCmdsImpl::leaseGetHandler, _1, _2));
    CommandMgr::instance().registerCommand("lease6-get",
        boost::bind(&LeaseCmdsImpl::leaseGetHandler, _1, _2));

    CommandMgr::instance().registerCommand("lease4-del",
    boost::bind(&LeaseCmdsImpl::leaseDelHandler, _1, _2));
    CommandMgr::instance().registerCommand("lease6-del",
    boost::bind(&LeaseCmdsImpl::leaseDelHandler, _1, _2));

    CommandMgr::instance().registerCommand("lease4-update",
    boost::bind(&LeaseCmdsImpl::leaseUpdateHandler, _1, _2));
    CommandMgr::instance().registerCommand("lease6-update",
    boost::bind(&LeaseCmdsImpl::leaseUpdateHandler, _1, _2));

    CommandMgr::instance().registerCommand("lease4-del-all",
    boost::bind(&LeaseCmdsImpl::leaseWipeHandler, _1, _2));
    CommandMgr::instance().registerCommand("lease6-del-all",
    boost::bind(&LeaseCmdsImpl::leaseWipeHandler, _1, _2));
}

void LeaseCmdsImpl::deregisterCommands() {
    /// @todo: Use deregistration mechanism once #5321 discussion is done
    CommandMgr::instance().deregisterCommand("lease4-add");
    CommandMgr::instance().deregisterCommand("lease6-add");

    CommandMgr::instance().deregisterCommand("lease4-get");
    CommandMgr::instance().deregisterCommand("lease6-get");

    CommandMgr::instance().deregisterCommand("lease4-del");
    CommandMgr::instance().deregisterCommand("lease6-del");

    CommandMgr::instance().deregisterCommand("lease4-update");
    CommandMgr::instance().deregisterCommand("lease6-update");

    CommandMgr::instance().deregisterCommand("lease4-del-all");
    CommandMgr::instance().deregisterCommand("lease6-del-all");
}

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
    LOG_INFO(lease_cmds_logger, v4?LEASE_CMDS_ADD4 : LEASE_CMDS_ADD6).arg(txt);
    return (createAnswer(CONTROL_RESULT_SUCCESS, "Lease added."));
}

LeaseCmdsImpl::Parameters
LeaseCmdsImpl::getParameters(const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    // We support 2 sets of parameters for lease-get/lease-del:
    // lease-get(subnet-id, address)
    // lease-get(subnet-id, interifier-type, identifier)

    ConstElementPtr tmp = params->get("subnet-id");
    if (!tmp) {
        isc_throw(BadValue, "Mandatory 'subnet-id' parameter missing.");
    }
    if (tmp->getType() != Element::integer) {
        isc_throw(BadValue, "'subnet-id' parameter is not integer.");
    }
    x.subnet_id = tmp->intValue();

    tmp = params->get("address");
    if (tmp) {
        if (tmp->getType() != Element::string) {
            isc_throw(BadValue, "'address' is not a string.");
        }

        x.addr = IOAddress(tmp->stringValue());
        x.query_type = Parameters::TYPE_ADDR;
        return (x);
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
        p = getParameters(params);

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
        default: {
            stringstream tmp;
            tmp << "Unknown query type: " << static_cast<int>(p.query_type);
            return (createAnswer(CONTROL_RESULT_ERROR, tmp.str()));
        }
        }
    } catch (const std::exception& ex) {
        stringstream tmp;
        tmp << "Failure during leaseX-get: " << ex.what();
        return (createAnswer(CONTROL_RESULT_ERROR, tmp.str()));
    }

    ElementPtr lease_json;
    if (v4 && lease4) {
        lease_json = lease4->toElement();
        return (createAnswer(CONTROL_RESULT_SUCCESS, "DHCPv4 lease found.", lease_json));
    }
    if (!v4 && lease6) {
        lease_json = lease6->toElement();
        return (createAnswer(CONTROL_RESULT_SUCCESS, "DHCPv6 lease found.", lease_json));
        
    }

    // If we got here, the lease has not been found.
    return (createAnswer(CONTROL_RESULT_EMPTY, "Lease not found."));
}

ConstElementPtr
LeaseCmdsImpl::leaseDelHandler(const std::string& name,
                               ConstElementPtr params) {
    Parameters p;
    bool deleted = false;
#if 0    
    try {
        p = getParameters(params);

        if (p.query_by_addr) {
            // try to delete by address
            deleted = LeaseMgrFactory::instance().del(p.subnet_id, p.addr);
        } else {
            // try to delete by identifier
            if (family_ == AF_INET) {
                deleted = LeaseMgrFactory::instance().del4(p.subnet_id, p.type,
                                                           &p.ident[0], p.ident.size());
            } else {
                deleted = LeaseMgrFactory::instance().del6(p.subnet_id, p.type,
                                                           &p.ident[0], p.ident.size());
            }
        }
    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }
#endif

    if (deleted) {
        return (createAnswer(CONTROL_RESULT_SUCCESS, "Lease deleted."));
    } else {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Lease not deleted (not found)."));
    }
}

ConstElementPtr
LeaseCmdsImpl::leaseUpdateHandler(const string& command, ConstElementPtr args) {
    return (createAnswer(CONTROL_RESULT_ERROR, "not implemented yet."));
}

ConstElementPtr
LeaseCmdsImpl::leaseWipeHandler(const string& command, ConstElementPtr args) {
    return (createAnswer(CONTROL_RESULT_ERROR, "not implemented yet."));
}


uint16_t LeaseCmdsImpl::family_ = AF_INET;

LeaseCmds::LeaseCmds()
    :impl_(new LeaseCmdsImpl()) {
}

LeaseCmds::~LeaseCmds() {
    impl_.reset();
}

};
};
