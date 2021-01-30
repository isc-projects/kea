// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <run_script.h>

using namespace isc::data;
using namespace isc::hooks;
using namespace isc::util;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace run_script {

RunScriptImpl::RunScriptImpl() : name_(), sync_(false) {
}

RunScriptImpl::~RunScriptImpl() {
}

void
RunScriptImpl::configure(LibraryHandle& handle) {
    ConstElementPtr name = handle.getParameter("name");
    if (!name) {
        isc_throw(NotFound, "The 'name' parameter is mandatory");
    }
    if (name->getType() != Element::string) {
        isc_throw(InvalidParameter, "The 'name' parameter must be a string");
    }
    setName(name->stringValue());
    ConstElementPtr sync = handle.getParameter("sync");
    if (sync) {
        if (sync->getType() != Element::boolean) {
            isc_throw(InvalidParameter, "The 'sync' parameter must be a boolean");
        }
        setSync(sync->boolValue());
    }
}

void
RunScriptImpl::runScript(const ProcessArgs& args, const ProcessEnvVars& vars) {
    ProcessSpawn process(name_, args, vars);
    process.spawn();
}

void
RunScriptImpl::extractBoolean(isc::util::ProcessEnvVars& vars,
                              const bool value,
                              const std::string& prefix,
                              const std::string& sufix) {
    std::string data = "0";
    if (value) {
        data = "1";
    }
    std::string exported_data = prefix + sufix + "=" + data;
    vars.push_back(exported_data);
}

void
RunScriptImpl::extractInteger(isc::util::ProcessEnvVars& vars,
                              const uint64_t value,
                              const std::string& prefix,
                              const std::string& sufix) {
    std::string data = "";
    try {
        data = boost::lexical_cast<std::string>(value);
    } catch (...) {
    }
    std::string exported_data = prefix + sufix + "=" + data;
    vars.push_back(exported_data);
}

void
RunScriptImpl::extractString(isc::util::ProcessEnvVars& vars,
                             const std::string& value,
                             const std::string& prefix,
                             const std::string& sufix) {
    std::string exported_data = prefix + sufix + "=" + value;
    vars.push_back(exported_data);
}

void
RunScriptImpl::extractHWAddr(isc::util::ProcessEnvVars& vars,
                             const isc::dhcp::HWAddrPtr& hwaddr,
                             const std::string& prefix,
                             const std::string& sufix) {
    if (hwaddr) {
        RunScriptImpl::extractString(vars, hwaddr->toText(false), prefix, sufix);
        RunScriptImpl::extractInteger(vars, hwaddr->htype_, prefix + "_TYPE", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix, sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", sufix);
    }
}

void
RunScriptImpl::extractDUID(isc::util::ProcessEnvVars& vars,
                           const isc::dhcp::DuidPtr duid,
                           const std::string& prefix,
                           const std::string& sufix) {
    std::string data = "";
    if (duid) {
        RunScriptImpl::extractString(vars, duid->toText(),
                                     prefix + "_ID", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ID", sufix);
    }
}

void
RunScriptImpl::extractOptionIA(isc::util::ProcessEnvVars& vars,
                               const isc::dhcp::Option6IAPtr option6IA,
                               const std::string& prefix,
                               const std::string& sufix) {
    if (option6IA) {
        RunScriptImpl::extractInteger(vars, option6IA->getIAID(),
                                      prefix + "_IAID", sufix);
        RunScriptImpl::extractInteger(vars, option6IA->getType(),
                                      prefix + "_IA_TYPE", sufix);
        RunScriptImpl::extractInteger(vars, option6IA->getT1(),
                                      prefix + "_IA_T1", sufix);
        RunScriptImpl::extractInteger(vars, option6IA->getT2(),
                                      prefix + "_IA_T2", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_IAID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IA_TYPE", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IA_T1", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IA_T2", sufix);
    }
}

void
RunScriptImpl::extractSubnet4(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Subnet4Ptr subnet4,
                              const std::string& prefix,
                              const std::string& sufix) {
    if (subnet4) {
        RunScriptImpl::extractInteger(vars, subnet4->getID(),
                                      prefix + "_ID", sufix);
        RunScriptImpl::extractString(vars, subnet4->toText(),
                                     prefix + "_NAME", sufix);
        auto prefix_data = subnet4->get();
        RunScriptImpl::extractString(vars, prefix_data.first.toText(),
                                     prefix + "_PREFIX", sufix);
        RunScriptImpl::extractInteger(vars, prefix_data.second,
                                      prefix + "_PREFIX_LEN", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_NAME", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX_LEN", sufix);
    }
}

void
RunScriptImpl::extractSubnet6(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Subnet6Ptr subnet6,
                              const std::string& prefix,
                              const std::string& sufix) {
    if (subnet6) {
        RunScriptImpl::extractInteger(vars, subnet6->getID(),
                                      prefix + "_ID", sufix);
        RunScriptImpl::extractString(vars, subnet6->toText(),
                                     prefix + "_NAME", sufix);
        auto prefix_data = subnet6->get();
        RunScriptImpl::extractString(vars, prefix_data.first.toText(),
                                     prefix + "_PREFIX", sufix);
        RunScriptImpl::extractInteger(vars, prefix_data.second,
                                      prefix + "_PREFIX_LEN", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_NAME", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX_LEN", sufix);
    }
}

void
RunScriptImpl::extractLease4(isc::util::ProcessEnvVars& vars,
                             const isc::dhcp::Lease4Ptr& lease4,
                             const std::string& prefix,
                             const std::string& sufix) {
    if (lease4) {
        RunScriptImpl::extractString(vars, lease4->addr_.toText(),
                                     prefix + "_ADDRESS", sufix);
        RunScriptImpl::extractInteger(vars, static_cast<uint64_t>(lease4->cltt_),
                                      prefix + "_CLTT", sufix);
        RunScriptImpl::extractString(vars, lease4->hostname_,
                                     prefix + "_HOSTNAME", sufix);
        RunScriptImpl::extractHWAddr(vars, lease4->hwaddr_,
                                     prefix + "_HWADDR", sufix);
        RunScriptImpl::extractString(vars, Lease4::statesToText(lease4->state_),
                                     prefix + "_STATE", sufix);
        RunScriptImpl::extractInteger(vars, lease4->subnet_id_,
                                      prefix + "_SUBNET_ID", sufix);
        RunScriptImpl::extractInteger(vars, lease4->valid_lft_,
                                      prefix + "_VALID_LIFETIME", sufix);
        RunScriptImpl::extractDUID(vars, lease4->client_id_,
                                   prefix + "_CLIENT_ID", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ADDRESS", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_CLTT", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_HOSTNAME", sufix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(), prefix + "_HWADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_STATE", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_SUBNET_ID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_VALID_LIFETIME", sufix);
        RunScriptImpl::extractDUID(vars, DuidPtr(), prefix + "_CLIENT_ID", sufix);
    }
}

void
RunScriptImpl::extractLease6(isc::util::ProcessEnvVars& vars,
                             const isc::dhcp::Lease6Ptr& lease6,
                             const std::string& prefix,
                             const std::string& sufix) {
    if (lease6) {
        RunScriptImpl::extractString(vars, lease6->addr_.toText(),
                                     prefix + "_ADDRESS", sufix);
        RunScriptImpl::extractInteger(vars, static_cast<uint64_t>(lease6->cltt_),
                                      prefix + "_CLTT", sufix);
        RunScriptImpl::extractString(vars, lease6->hostname_,
                                     prefix + "_HOSTNAME", sufix);
        RunScriptImpl::extractHWAddr(vars, lease6->hwaddr_,
                                     prefix + "_HWADDR", sufix);
        RunScriptImpl::extractString(vars, Lease6::statesToText(lease6->state_),
                                     prefix + "_STATE", sufix);
        RunScriptImpl::extractInteger(vars, lease6->subnet_id_,
                                      prefix + "_SUBNET_ID", sufix);
        RunScriptImpl::extractInteger(vars, lease6->valid_lft_,
                                      prefix + "_VALID_LIFETIME", sufix);
        RunScriptImpl::extractDUID(vars, lease6->duid_,
                                   prefix + "_DUID", sufix);
        RunScriptImpl::extractInteger(vars, lease6->iaid_,
                                      prefix + "_IAID", sufix);
        RunScriptImpl::extractInteger(vars, lease6->preferred_lft_,
                                      prefix + "_PREFERRED_LIFETIME", sufix);
        RunScriptImpl::extractInteger(vars, lease6->prefixlen_,
                                      prefix + "_PREFIX_LEN", sufix);
        RunScriptImpl::extractString(vars, Lease::typeToText(lease6->type_),
                                     prefix + "_TYPE", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ADDRESS", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_CLTT", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_HOSTNAME", sufix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(), prefix + "_HWADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_STATE", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_SUBNET_ID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_VALID_LIFETIME", sufix);
        RunScriptImpl::extractDUID(vars, DuidPtr(), prefix + "_DUID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IAID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFERRED_LIFETIME", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX_LEN", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", sufix);
    }
}

void
RunScriptImpl::extractLeases4(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Lease4CollectionPtr& leases4,
                              const std::string& prefix,
                              const std::string& sufix) {
    if (leases4) {
        RunScriptImpl::extractInteger(vars, leases4->size(),
                                      prefix + "_SIZE", sufix);
        for (int i = 0; i < leases4->size(); ++i) {
            RunScriptImpl::extractLease4(vars, leases4->at(i),
                                         prefix + "_AT" +
                                         boost::lexical_cast<std::string>(i),
                                         sufix);
        }
    } else {
        RunScriptImpl::extractString(vars, "0", prefix + "_SIZE", sufix);
    }
}

void
RunScriptImpl::extractLeases6(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Lease6CollectionPtr& leases6,
                              const std::string& prefix,
                              const std::string& sufix) {
    if (leases6) {
        RunScriptImpl::extractInteger(vars, leases6->size(),
                                      prefix + "_SIZE", sufix);
        for (int i = 0; i < leases6->size(); ++i) {
            RunScriptImpl::extractLease6(vars, leases6->at(i),
                                         prefix + "_AT" +
                                         boost::lexical_cast<std::string>(i),
                                         sufix);
        }
    } else {
        RunScriptImpl::extractString(vars, "0", prefix + "_SIZE", sufix);
    }
}

void
RunScriptImpl::extractPkt4(isc::util::ProcessEnvVars& vars,
                           const isc::dhcp::Pkt4Ptr& pkt4,
                           const std::string& prefix,
                           const std::string& sufix) {
    if (pkt4) {
        RunScriptImpl::extractString(vars, pkt4->getName(pkt4->getType()),
                                     prefix + "_TYPE", sufix);
        RunScriptImpl::extractInteger(vars, pkt4->getTransid(),
                                      prefix + "_TXID", sufix);
        RunScriptImpl::extractString(vars, pkt4->getLocalAddr().toText(),
                                     prefix + "_LOCAL_ADDR", sufix);
        RunScriptImpl::extractInteger(vars, pkt4->getLocalPort(),
                                      prefix + "_LOCAL_PORT", sufix);
        RunScriptImpl::extractString(vars, pkt4->getRemoteAddr().toText(),
                                     prefix + "_REMOTE_ADDR", sufix);
        RunScriptImpl::extractInteger(vars, pkt4->getRemotePort(),
                                      prefix + "_REMOTE_PORT", sufix);
        RunScriptImpl::extractInteger(vars, pkt4->getIndex(),
                                      prefix + "_IFACE_INDEX", sufix);
        RunScriptImpl::extractString(vars, pkt4->getIface(),
                                     prefix + "_IFACE_NAME", sufix);
        RunScriptImpl::extractInteger(vars, pkt4->getHops(),
                                      prefix + "_HOPS", sufix);
        RunScriptImpl::extractInteger(vars, pkt4->getSecs(),
                                      prefix + "_SECS", sufix);
        RunScriptImpl::extractInteger(vars, pkt4->getFlags(),
                                      prefix + "_FLAGS", sufix);
        RunScriptImpl::extractString(vars, pkt4->getCiaddr().toText(),
                                     prefix + "_CIADDR", sufix);
        RunScriptImpl::extractString(vars, pkt4->getSiaddr().toText(),
                                     prefix + "_SIADDR", sufix);
        RunScriptImpl::extractString(vars, pkt4->getYiaddr().toText(),
                                     prefix + "_YIADDR", sufix);
        RunScriptImpl::extractString(vars, pkt4->getGiaddr().toText(),
                                     prefix + "_GIADDR", sufix);
        RunScriptImpl::extractBoolean(vars, pkt4->isRelayed(),
                                      prefix + "_RELAYED", sufix);
        RunScriptImpl::extractHWAddr(vars, pkt4->getHWAddr(),
                                     prefix + "_HWADDR", sufix);
        RunScriptImpl::extractHWAddr(vars, pkt4->getLocalHWAddr(),
                                     prefix + "_LOCAL_HWADDR", sufix);
        RunScriptImpl::extractHWAddr(vars, pkt4->getRemoteHWAddr(),
                                     prefix + "_REMOTE_HWADDR", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_TXID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_ADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_PORT", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_ADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_PORT", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_INDEX", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_NAME", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_HOPS", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_SECS", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_FLAGS", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_CIADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_SIADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_YIADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_GIADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_RELAYED", sufix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_HWADDR", sufix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_LOCAL_HWADDR", sufix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_REMOTE_HWADDR", sufix);
    }
}

void
RunScriptImpl::extractPkt6(isc::util::ProcessEnvVars& vars,
                           const isc::dhcp::Pkt6Ptr& pkt6,
                           const std::string& prefix,
                           const std::string& sufix) {
    if (pkt6) {
        RunScriptImpl::extractString(vars, pkt6->getName(pkt6->getType()),
                                     prefix + "_TYPE", sufix);
        RunScriptImpl::extractInteger(vars, pkt6->getTransid(),
                                      prefix + "_TXID", sufix);
        RunScriptImpl::extractString(vars, pkt6->getLocalAddr().toText(),
                                     prefix + "_LOCAL_ADDR", sufix);
        RunScriptImpl::extractInteger(vars, pkt6->getLocalPort(),
                                      prefix + "_LOCAL_PORT", sufix);
        RunScriptImpl::extractString(vars, pkt6->getRemoteAddr().toText(),
                                     prefix + "_REMOTE_ADDR", sufix);
        RunScriptImpl::extractInteger(vars, pkt6->getRemotePort(),
                                      prefix + "_REMOTE_PORT", sufix);
        RunScriptImpl::extractInteger(vars, pkt6->getIndex(),
                                      prefix + "_IFACE_INDEX", sufix);
        RunScriptImpl::extractString(vars, pkt6->getIface(),
                                     prefix + "_IFACE_NAME", sufix);
        RunScriptImpl::extractHWAddr(vars, pkt6->getRemoteHWAddr(),
                                     prefix + "_REMOTE_HWADDR", sufix);
        std::string proto_data = (pkt6->getProto() == Pkt6::UDP ? "UDP" : "TCP");
        RunScriptImpl::extractString(vars, proto_data,
                                     prefix + "_PROTO", sufix);
        RunScriptImpl::extractDUID(vars, pkt6->getClientId(),
                                   prefix + "_CLIENT_ID", sufix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_TXID", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_ADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_PORT", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_ADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_PORT", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_INDEX", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_NAME", sufix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_REMOTE_HWADDR", sufix);
        RunScriptImpl::extractString(vars, "", prefix + "_PROTO", sufix);
        RunScriptImpl::extractDUID(vars, DuidPtr(),
                                   prefix + "_CLIENT_ID", sufix);
    }
}

} // end of namespace run_script
} // end of namespace isc
