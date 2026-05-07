// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <config/cmds_impl.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <asiolink/io_address.h>
#include <asiolink/addr_utilities.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet_id.h>
#include <hooks/hooks.h>
#include <exceptions/exceptions.h>
#include <lease_cmds_log.h>
#include <sflq_cmds.h>
#include <util/multi_threading_mgr.h>

#include <string>
#include <sstream>

using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::util;
using namespace isc::log;
using namespace std;

namespace isc {
namespace lease_cmds {

int
SflqCmdsImpl::sflqPool4CreateHandler(CalloutHandle& handle) {
    static const data::SimpleKeywords keywords =
    {
        { "start-address",  Element::string  },
        { "end-address",    Element::string  },
        { "subnet-id",      Element::integer },
        { "recreate",       Element::boolean }
    };

    static const data::SimpleRequiredKeywords required_keywords =
    {
        "start-address",
        "end-address",
        "subnet-id",
    };

    stringstream resp;
    try {
        extractCommand(handle);
        if (!cmd_args_ || cmd_args_->getType() != Element::map) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        SimpleParser::checkRequired(required_keywords, cmd_args_);
        SimpleParser::checkKeywords(keywords, cmd_args_);

        // Fetch the command parameters.
        IOAddress start_address(IOAddress::IPV4_ZERO_ADDRESS());
        IOAddress end_address(IOAddress::IPV4_ZERO_ADDRESS());
        extractRange(cmd_args_, AF_INET, start_address, end_address);

        /// @todo Should we verify the subnet-id and/or check allocator for subnet?
        SubnetID subnet_id = SimpleParser::getInteger(cmd_args_, "subnet-id");
        if (subnet_id <= 0) {
            isc_throw(isc::BadValue, "'subnet-id' must be greater than zero");
        }

        bool recreate = extractBool(cmd_args_, "recreate", false);

        // Invoke the pool create function inside a CriticalSection.
        MultiThreadingCriticalSection cs;
        bool created = LeaseMgrFactory::instance().
                       sflqCreateFlqPool4(start_address, end_address, subnet_id, recreate);

        resp << (created ? "SFLQ pool created" : "SFLQ pool already exists") << ".";
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, SFLQ_POOL4_CREATE_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA, SFLQ_POOL4_CREATE)
        .arg(cmd_args_->str());

    setSuccessResponse(handle, resp.str());
    return (0);
}

int
SflqCmdsImpl::sflqPool4GetAllHandler(CalloutHandle& handle) {
    return (sflqPoolGetAll(handle, AF_INET));
}

int
SflqCmdsImpl::sflqPool4GetBySubnetHandler(CalloutHandle& handle) {
    return (sflqPoolGetBySubnet(handle, AF_INET));
}

int
SflqCmdsImpl::sflqPool4GetByRangeHandler(CalloutHandle& handle) {
    return (sflqPoolGetByRange(handle, AF_INET));
}

int
SflqCmdsImpl::sflqPool4DelHandler(CalloutHandle& handle) {
    return (sflqPoolDel(handle, AF_INET));
}

int
SflqCmdsImpl::sflqPool6CreateHandler(CalloutHandle& handle) {
    static const data::SimpleKeywords keywords =
    {
        { "start-address",  Element::string  },
        { "end-address",    Element::string  },
        { "subnet-id",      Element::integer },
        { "lease-type",     Element::string  },
        { "delegated-len",  Element::integer },
        { "recreate",       Element::boolean }
    };

    static const data::SimpleRequiredKeywords required_keywords =
    {
        "start-address",
        "end-address",
        "subnet-id",
        "lease-type"
    };

    stringstream resp;
    try {
        extractCommand(handle);
        if (!cmd_args_ || cmd_args_->getType() != Element::map) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        SimpleParser::checkRequired(required_keywords, cmd_args_);
        SimpleParser::checkKeywords(keywords, cmd_args_);

        // Fetch the command parameters.
        IOAddress start_address(IOAddress::IPV6_ZERO_ADDRESS());
        IOAddress end_address(IOAddress::IPV6_ZERO_ADDRESS());
        extractRange(cmd_args_, AF_INET6, start_address, end_address);

        /// @todo Should we verify the subnet-id and/or check allocator for subnet?
        SubnetID subnet_id = SimpleParser::getInteger(cmd_args_, "subnet-id");
        if (subnet_id <= 0) {
            isc_throw(isc::BadValue, "'subnet-id' must be greater than zero");
        }

        auto lease_type = extractLeaseType(cmd_args_, AF_INET6);
        uint8_t delegated_len = extractDelegatedLen(cmd_args_, lease_type);
        bool recreate = extractBool(cmd_args_, "recreate", false);

        // Invoke the pool create function inside a CriticalSection.
        MultiThreadingCriticalSection cs;
        bool created = LeaseMgrFactory::instance().
                       sflqCreateFlqPool6(start_address, end_address, lease_type,
                                          delegated_len, subnet_id, recreate);

        resp << (created ? "SFLQ pool created" : "SFLQ pool already exists") << ".";
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, SFLQ_POOL6_CREATE_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA, SFLQ_POOL6_CREATE)
        .arg(cmd_args_->str());

    setSuccessResponse(handle, resp.str());
    return (0);
}

int
SflqCmdsImpl::sflqPool6GetAllHandler(CalloutHandle& handle) {
    return (sflqPoolGetAll(handle, AF_INET6));
}

int
SflqCmdsImpl::sflqPool6GetBySubnetHandler(CalloutHandle& handle) {
    return (sflqPoolGetBySubnet(handle, AF_INET6));
}

int
SflqCmdsImpl::sflqPool6GetByRangeHandler(CalloutHandle& handle) {
    return (sflqPoolGetByRange(handle, AF_INET6));
}

int
SflqCmdsImpl::sflqPool6DelHandler(CalloutHandle& handle) {
    return (sflqPoolDel(handle, AF_INET6));
}

int
SflqCmdsImpl::sflqPoolGetAll(CalloutHandle& handle, uint16_t family) {
    static const data::SimpleKeywords keywords;
    try {
        extractCommand(handle);
        if (cmd_args_ && ((cmd_args_->getType() != Element::map) ||
            (cmd_args_->mapValue().size()) > 0)) {
            isc_throw(BadValue, "command does not take any arguments");
        }

        // Invoke the pool get function.
        auto pools = (family == AF_INET ? LeaseMgrFactory::instance().sflqPool4GetAll()
                                       : LeaseMgrFactory::instance().sflqPool6GetAll());

        auto resp = buildGetResponse(pools);
        setResponse(handle, resp);
        LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
                  (family == AF_INET ? SFLQ_POOL4_GET_ALL : SFLQ_POOL6_GET_ALL))
                  .arg(pools->size());
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, (family == AF_INET ? SFLQ_POOL4_GET_ALL_FAILED
                                                        : SFLQ_POOL6_GET_ALL_FAILED))
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
SflqCmdsImpl::sflqPoolGetBySubnet(CalloutHandle& handle, uint16_t family) {
    static const data::SimpleKeywords keywords =
    {
        { "subnet-id",      Element::integer },
    };

    static const data::SimpleRequiredKeywords required_keywords =
    {
        "subnet-id",
    };

    try {
        extractCommand(handle);
        if (!cmd_args_ || cmd_args_->getType() != Element::map) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        SimpleParser::checkRequired(required_keywords, cmd_args_);
        SimpleParser::checkKeywords(keywords, cmd_args_);
        SubnetID subnet_id = SimpleParser::getInteger(cmd_args_, "subnet-id");

        // Invoke the pool get by subnet function.
        auto pools = (family == AF_INET ? LeaseMgrFactory::instance().sflqPool4Get(subnet_id)
                      : LeaseMgrFactory::instance().sflqPool6Get(subnet_id));

        auto resp = buildGetResponse(pools);
        setResponse(handle, resp);
        LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
                  (family == AF_INET ? SFLQ_POOL4_GET_BY_SUBNET : SFLQ_POOL6_GET_BY_SUBNET))
                  .arg(cmd_args_->str())
                  .arg(pools->size());
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, (family == AF_INET ? SFLQ_POOL4_GET_BY_SUBNET_FAILED
                                                        : SFLQ_POOL6_GET_BY_SUBNET_FAILED))
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
SflqCmdsImpl::sflqPoolGetByRange(CalloutHandle& handle, uint16_t family) {
    static const data::SimpleKeywords keywords =
    {
        { "start-address",  Element::string  },
        { "end-address",    Element::string  },
    };

    static const data::SimpleRequiredKeywords required_keywords =
    {
        "start-address",
        "end-address",
    };

    try {
        extractCommand(handle);
        if (!cmd_args_ || cmd_args_->getType() != Element::map) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        SimpleParser::checkRequired(required_keywords, cmd_args_);
        SimpleParser::checkKeywords(keywords, cmd_args_);

        // Fetch the command parameters.
        IOAddress start_address(IOAddress::IPV4_ZERO_ADDRESS());
        IOAddress end_address(IOAddress::IPV4_ZERO_ADDRESS());
        extractRange(cmd_args_, family, start_address, end_address);

        // Invoke the pool get by subnet function.
        auto pools = (family == AF_INET
                      ? LeaseMgrFactory::instance().sflqPool4Get(start_address, end_address)
                      : LeaseMgrFactory::instance().sflqPool6Get(start_address, end_address));

        auto resp = buildGetResponse(pools);
        setResponse(handle, resp);
        LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
                  (family == AF_INET ? SFLQ_POOL4_GET_BY_RANGE : SFLQ_POOL6_GET_BY_RANGE))
                  .arg(cmd_args_->str())
                  .arg(pools->size());
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, (family == AF_INET ? SFLQ_POOL4_GET_BY_RANGE_FAILED
                                                        : SFLQ_POOL6_GET_BY_RANGE_FAILED))
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
SflqCmdsImpl::sflqPoolDel(CalloutHandle& handle, uint16_t family) {
    static const data::SimpleKeywords keywords =
    {
        { "start-address",  Element::string  },
        { "end-address",    Element::string  },
        { "force",          Element::boolean },
    };

    static const data::SimpleRequiredKeywords required_keywords =
    {
        "start-address",
        "end-address",
    };

    try {
        extractCommand(handle);
        if (!cmd_args_ || cmd_args_->getType() != Element::map) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        SimpleParser::checkRequired(required_keywords, cmd_args_);
        SimpleParser::checkKeywords(keywords, cmd_args_);

        // Fetch the command parameters.
        IOAddress start_address(IOAddress::IPV4_ZERO_ADDRESS());
        IOAddress end_address(IOAddress::IPV4_ZERO_ADDRESS());
        extractRange(cmd_args_, family, start_address, end_address);
        bool force = extractBool(cmd_args_, "force", false);

        // Invoke the pool get by subnet function.
        bool deleted = (family == AF_INET
                        ? LeaseMgrFactory::instance().sflqPool4Del(start_address,
                                                                   end_address, force)
                        : LeaseMgrFactory::instance().sflqPool6Del(start_address,
                                                                   end_address, force));

        if (deleted) {
            auto response = createAnswer(CONTROL_RESULT_SUCCESS,
                                         "SFLQ pool deleted", cmd_args_);
            setResponse(handle, response);
        } else {
            auto response = createAnswer(CONTROL_RESULT_EMPTY,
                                         "SFLQ pool does not exist", cmd_args_);
            setResponse(handle, response);
        }

        LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
                  (family == AF_INET ? SFLQ_POOL4_DEL : SFLQ_POOL6_DEL))
                  .arg(cmd_args_->str())
                  .arg(deleted ? 1 : 0);
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, (family == AF_INET ? SFLQ_POOL4_DEL_FAILED
                                                        : SFLQ_POOL6_DEL_FAILED))
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

ConstElementPtr
SflqCmdsImpl::buildGetResponse(SflqPoolInfoCollectionPtr pools) {
    ElementPtr pools_json = Element::createList();
    for (auto const& pool : *pools) {
        pools_json->add(pool->toElement());
    }

    auto pool_cnt = pools_json->size();
    stringstream resp_msg;
    resp_msg << pool_cnt << " pool(s) found.";

    ElementPtr args = Element::createMap();
    args->set("pools", pools_json);

    auto response = createAnswer(pool_cnt > 0 ?
                                 CONTROL_RESULT_SUCCESS : CONTROL_RESULT_EMPTY,
                                 resp_msg.str(), args);
    return(response);
}


void
SflqCmdsImpl::extractRange(ConstElementPtr& params, uint8_t family,
                           IOAddress& start_address, IOAddress& end_address) {
    start_address = SimpleParser::getAddress(params, "start-address");
    end_address = SimpleParser::getAddress(params, "end-address");
    if (family == AF_INET) {
        validateV4Range(start_address, end_address);
    } else {
        validateV6Range(start_address, end_address);
    }
}

bool
SflqCmdsImpl::extractBool(ConstElementPtr& params, const std::string& name,
                          bool default_value) {
    auto tmp = params->get(name);
    if (!tmp) {
        return (default_value);
    }

    if (tmp->getType() != Element::boolean) {
        isc_throw(BadValue, "'" << name << "' parameter is not boolean.");
    }

    return (tmp->boolValue());
}

Lease::Type
SflqCmdsImpl::extractLeaseType(ConstElementPtr& params, uint16_t family) {
    auto tmp = SimpleParser::getString(params, "lease-type");
    if (family == AF_INET) {
        if (tmp == "V4" || tmp == "3") {
            return (Lease::TYPE_V4);
        }

        isc_throw(BadValue, "invalid 'lease-type': " << tmp << " must be 'V4'");
    }

    if (tmp == "IA_NA" || tmp == "0") {
        return (Lease::TYPE_NA);
    } else if (tmp == "IA_PD" || tmp == "2") {
        return (Lease::TYPE_PD);
    }

    isc_throw(BadValue, "invalid V6 'lease-type': "
              << tmp << ", valid values are IA_NA and IA_PD");
}

uint8_t
SflqCmdsImpl::extractDelegatedLen(ConstElementPtr& params,
                                  Lease::Type lease_type) {
    auto tmp = params->get("delegated-len");
    if (!tmp) {
        if (lease_type == Lease::TYPE_PD) {
            isc_throw(BadValue, "'delegated-len' is required for IA_PD pools");
        }

        return (128);
    }

    if (tmp->getType() != Element::integer) {
        isc_throw(BadValue, "'delegated-len' parameter is not integer.");
    }

    auto val = tmp->intValue();
    if (val <= 0 || val > 128) {
        isc_throw(BadValue, "'delegated-len' invalid: " << val
                  << ", it must be >= 1 and =< 128");
    }

    if (lease_type == Lease::TYPE_NA && val != 128) {
        isc_throw(BadValue, "'delegated-len' must only be 128 for IA_NA pools");
    }

    return (val);
}

SflqCmds::SflqCmds()
    : sflq_impl_(new SflqCmdsImpl()) {
}

int
SflqCmds::sflqPool4CreateHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool4CreateHandler(handle));
}

int
SflqCmds::sflqPool4GetAllHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool4GetAllHandler(handle));
}

int
SflqCmds::sflqPool4GetBySubnetHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool4GetBySubnetHandler(handle));
}

int
SflqCmds::sflqPool4GetByRangeHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool4GetByRangeHandler(handle));
}

int
SflqCmds::sflqPool4DelHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool4DelHandler(handle));
}

int
SflqCmds::sflqPool6CreateHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool6CreateHandler(handle));
}

int
SflqCmds::sflqPool6GetAllHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool6GetAllHandler(handle));
}

int
SflqCmds::sflqPool6GetBySubnetHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool6GetBySubnetHandler(handle));
}

int
SflqCmds::sflqPool6GetByRangeHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool6GetByRangeHandler(handle));
}

int
SflqCmds::sflqPool6DelHandler(CalloutHandle& handle) {
    return (sflq_impl_->sflqPool6DelHandler(handle));
}

} // end of namespace lease_cmds
} // end of namespace isc
