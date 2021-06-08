// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <run_script.h>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::util;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace run_script {

IOServicePtr RunScriptImpl::io_service_;

RunScriptImpl::RunScriptImpl() : name_(), sync_(false) {
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
    try {
        ProcessSpawn process(IOServicePtr(), name->stringValue());
    } catch (const isc::Exception& ex) {
        isc_throw(InvalidParameter, "Invalid 'name' parameter: " << ex.what());
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
    ProcessSpawn process(getIOService(), name_, args, vars);
    process.spawn(true);
}

void
RunScriptImpl::extractBoolean(ProcessEnvVars& vars,
                              const bool value,
                              const string& prefix,
                              const string& suffix) {
    string data;
    if (value) {
        data = "true";
    } else {
        data = "false";
    }
    string exported_data = prefix + suffix + "=" + data;
    vars.push_back(exported_data);
}

void
RunScriptImpl::extractInteger(ProcessEnvVars& vars,
                              const uint64_t value,
                              const string& prefix,
                              const string& suffix) {
    string exported_data = prefix + suffix + "=" + boost::lexical_cast<string>(value);
    vars.push_back(exported_data);
}

void
RunScriptImpl::extractString(ProcessEnvVars& vars,
                             const string& value,
                             const string& prefix,
                             const string& suffix) {
    string exported_data = prefix + suffix + "=" + value;
    vars.push_back(exported_data);
}

void
RunScriptImpl::extractHWAddr(ProcessEnvVars& vars,
                             const HWAddrPtr& hwaddr,
                             const string& prefix,
                             const string& suffix) {
    if (hwaddr) {
        RunScriptImpl::extractString(vars, hwaddr->toText(false), prefix, suffix);
        RunScriptImpl::extractInteger(vars, hwaddr->htype_, prefix + "_TYPE", suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix, suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", suffix);
    }
}

void
RunScriptImpl::extractDUID(ProcessEnvVars& vars,
                           const DuidPtr duid,
                           const string& prefix,
                           const string& suffix) {
    if (duid) {
        RunScriptImpl::extractString(vars, duid->toText(),
                                     prefix, suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix, suffix);
    }
}

void
RunScriptImpl::extractOption(ProcessEnvVars& vars,
                             const OptionPtr option,
                             const string& prefix,
                             const string& suffix) {
    if (option) {
        RunScriptImpl::extractString(vars, option->toHexString(),
                                     prefix + "_OPTION_" +
                                     boost::lexical_cast<string>(option->getType()),
                                     suffix);
    }
}

void
RunScriptImpl::extractSubOption(ProcessEnvVars& vars,
                                const OptionPtr option,
                                uint16_t code,
                                const string& prefix,
                                const string& suffix) {
    if (option) {
        RunScriptImpl::extractOption(vars, option->getOption(code),
                                     prefix + "_OPTION_" +
                                     boost::lexical_cast<string>(option->getType()) +
                                     "_SUB", suffix);
    }
}

void
RunScriptImpl::extractOptionIA(ProcessEnvVars& vars,
                               const Option6IAPtr option6IA,
                               const string& prefix,
                               const string& suffix) {
    if (option6IA) {
        RunScriptImpl::extractInteger(vars, option6IA->getIAID(),
                                      prefix + "_IAID", suffix);
        RunScriptImpl::extractInteger(vars, option6IA->getType(),
                                      prefix + "_IA_TYPE", suffix);
        RunScriptImpl::extractInteger(vars, option6IA->getT1(),
                                      prefix + "_IA_T1", suffix);
        RunScriptImpl::extractInteger(vars, option6IA->getT2(),
                                      prefix + "_IA_T2", suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_IAID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IA_TYPE", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IA_T1", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IA_T2", suffix);
    }
}

void
RunScriptImpl::extractSubnet4(ProcessEnvVars& vars,
                              const Subnet4Ptr subnet4,
                              const string& prefix,
                              const string& suffix) {
    if (subnet4) {
        RunScriptImpl::extractInteger(vars, subnet4->getID(),
                                      prefix + "_ID", suffix);
        RunScriptImpl::extractString(vars, subnet4->toText(),
                                     prefix + "_NAME", suffix);
        auto prefix_data = subnet4->get();
        RunScriptImpl::extractString(vars, prefix_data.first.toText(),
                                     prefix + "_PREFIX", suffix);
        RunScriptImpl::extractInteger(vars, prefix_data.second,
                                      prefix + "_PREFIX_LEN", suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_NAME", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX_LEN", suffix);
    }
}

void
RunScriptImpl::extractSubnet6(ProcessEnvVars& vars,
                              const Subnet6Ptr subnet6,
                              const string& prefix,
                              const string& suffix) {
    if (subnet6) {
        RunScriptImpl::extractInteger(vars, subnet6->getID(),
                                      prefix + "_ID", suffix);
        RunScriptImpl::extractString(vars, subnet6->toText(),
                                     prefix + "_NAME", suffix);
        auto prefix_data = subnet6->get();
        RunScriptImpl::extractString(vars, prefix_data.first.toText(),
                                     prefix + "_PREFIX", suffix);
        RunScriptImpl::extractInteger(vars, prefix_data.second,
                                      prefix + "_PREFIX_LEN", suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_NAME", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX_LEN", suffix);
    }
}

void
RunScriptImpl::extractLease4(ProcessEnvVars& vars,
                             const Lease4Ptr& lease4,
                             const string& prefix,
                             const string& suffix) {
    if (lease4) {
        RunScriptImpl::extractString(vars, lease4->addr_.toText(),
                                     prefix + "_ADDRESS", suffix);
        RunScriptImpl::extractInteger(vars, static_cast<uint64_t>(lease4->cltt_),
                                      prefix + "_CLTT", suffix);
        RunScriptImpl::extractString(vars, lease4->hostname_,
                                     prefix + "_HOSTNAME", suffix);
        RunScriptImpl::extractHWAddr(vars, lease4->hwaddr_,
                                     prefix + "_HWADDR", suffix);
        RunScriptImpl::extractString(vars, Lease4::statesToText(lease4->state_),
                                     prefix + "_STATE", suffix);
        RunScriptImpl::extractInteger(vars, lease4->subnet_id_,
                                      prefix + "_SUBNET_ID", suffix);
        RunScriptImpl::extractInteger(vars, lease4->valid_lft_,
                                      prefix + "_VALID_LIFETIME", suffix);
        RunScriptImpl::extractDUID(vars, lease4->client_id_,
                                   prefix + "_CLIENT_ID", suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ADDRESS", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_CLTT", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_HOSTNAME", suffix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(), prefix + "_HWADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_STATE", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_SUBNET_ID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_VALID_LIFETIME", suffix);
        RunScriptImpl::extractDUID(vars, DuidPtr(), prefix + "_CLIENT_ID", suffix);
    }
}

void
RunScriptImpl::extractLease6(ProcessEnvVars& vars,
                             const Lease6Ptr& lease6,
                             const string& prefix,
                             const string& suffix) {
    if (lease6) {
        RunScriptImpl::extractString(vars, lease6->addr_.toText(),
                                     prefix + "_ADDRESS", suffix);
        RunScriptImpl::extractInteger(vars, static_cast<uint64_t>(lease6->cltt_),
                                      prefix + "_CLTT", suffix);
        RunScriptImpl::extractString(vars, lease6->hostname_,
                                     prefix + "_HOSTNAME", suffix);
        RunScriptImpl::extractHWAddr(vars, lease6->hwaddr_,
                                     prefix + "_HWADDR", suffix);
        RunScriptImpl::extractString(vars, Lease6::statesToText(lease6->state_),
                                     prefix + "_STATE", suffix);
        RunScriptImpl::extractInteger(vars, lease6->subnet_id_,
                                      prefix + "_SUBNET_ID", suffix);
        RunScriptImpl::extractInteger(vars, lease6->valid_lft_,
                                      prefix + "_VALID_LIFETIME", suffix);
        RunScriptImpl::extractDUID(vars, lease6->duid_,
                                   prefix + "_DUID", suffix);
        RunScriptImpl::extractInteger(vars, lease6->iaid_,
                                      prefix + "_IAID", suffix);
        RunScriptImpl::extractInteger(vars, lease6->preferred_lft_,
                                      prefix + "_PREFERRED_LIFETIME", suffix);
        RunScriptImpl::extractInteger(vars, lease6->prefixlen_,
                                      prefix + "_PREFIX_LEN", suffix);
        RunScriptImpl::extractString(vars, Lease::typeToText(lease6->type_),
                                     prefix + "_TYPE", suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_ADDRESS", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_CLTT", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_HOSTNAME", suffix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(), prefix + "_HWADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_STATE", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_SUBNET_ID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_VALID_LIFETIME", suffix);
        RunScriptImpl::extractDUID(vars, DuidPtr(), prefix + "_DUID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IAID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFERRED_LIFETIME", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_PREFIX_LEN", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", suffix);
    }
}

void
RunScriptImpl::extractLeases4(ProcessEnvVars& vars,
                              const Lease4CollectionPtr& leases4,
                              const string& prefix,
                              const string& suffix) {
    if (leases4) {
        RunScriptImpl::extractInteger(vars, leases4->size(),
                                      prefix + "_SIZE", suffix);
        for (size_t i = 0; i < leases4->size(); ++i) {
            RunScriptImpl::extractLease4(vars, leases4->at(i),
                                         prefix + "_AT" +
                                         boost::lexical_cast<string>(i),
                                         suffix);
        }
    } else {
        RunScriptImpl::extractString(vars, "0", prefix + "_SIZE", suffix);
    }
}

void
RunScriptImpl::extractLeases6(ProcessEnvVars& vars,
                              const Lease6CollectionPtr& leases6,
                              const string& prefix,
                              const string& suffix) {
    if (leases6) {
        RunScriptImpl::extractInteger(vars, leases6->size(),
                                      prefix + "_SIZE", suffix);
        for (size_t i = 0; i < leases6->size(); ++i) {
            RunScriptImpl::extractLease6(vars, leases6->at(i),
                                         prefix + "_AT" +
                                         boost::lexical_cast<string>(i),
                                         suffix);
        }
    } else {
        RunScriptImpl::extractString(vars, "0", prefix + "_SIZE", suffix);
    }
}

void
RunScriptImpl::extractPkt4(ProcessEnvVars& vars,
                           const Pkt4Ptr& pkt4,
                           const string& prefix,
                           const string& suffix) {
    if (pkt4) {
        RunScriptImpl::extractString(vars, pkt4->getName(pkt4->getType()),
                                     prefix + "_TYPE", suffix);
        RunScriptImpl::extractInteger(vars, pkt4->getTransid(),
                                      prefix + "_TXID", suffix);
        RunScriptImpl::extractString(vars, pkt4->getLocalAddr().toText(),
                                     prefix + "_LOCAL_ADDR", suffix);
        RunScriptImpl::extractInteger(vars, pkt4->getLocalPort(),
                                      prefix + "_LOCAL_PORT", suffix);
        RunScriptImpl::extractString(vars, pkt4->getRemoteAddr().toText(),
                                     prefix + "_REMOTE_ADDR", suffix);
        RunScriptImpl::extractInteger(vars, pkt4->getRemotePort(),
                                      prefix + "_REMOTE_PORT", suffix);
        RunScriptImpl::extractInteger(vars, pkt4->getIndex(),
                                      prefix + "_IFACE_INDEX", suffix);
        RunScriptImpl::extractString(vars, pkt4->getIface(),
                                     prefix + "_IFACE_NAME", suffix);
        RunScriptImpl::extractInteger(vars, pkt4->getHops(),
                                      prefix + "_HOPS", suffix);
        RunScriptImpl::extractInteger(vars, pkt4->getSecs(),
                                      prefix + "_SECS", suffix);
        RunScriptImpl::extractInteger(vars, pkt4->getFlags(),
                                      prefix + "_FLAGS", suffix);
        RunScriptImpl::extractString(vars, pkt4->getCiaddr().toText(),
                                     prefix + "_CIADDR", suffix);
        RunScriptImpl::extractString(vars, pkt4->getSiaddr().toText(),
                                     prefix + "_SIADDR", suffix);
        RunScriptImpl::extractString(vars, pkt4->getYiaddr().toText(),
                                     prefix + "_YIADDR", suffix);
        RunScriptImpl::extractString(vars, pkt4->getGiaddr().toText(),
                                     prefix + "_GIADDR", suffix);
        RunScriptImpl::extractBoolean(vars, pkt4->isRelayed(),
                                      prefix + "_RELAYED", suffix);
        RunScriptImpl::extractHWAddr(vars, pkt4->getHWAddr(),
                                     prefix + "_HWADDR", suffix);
        RunScriptImpl::extractHWAddr(vars, pkt4->getLocalHWAddr(),
                                     prefix + "_LOCAL_HWADDR", suffix);
        RunScriptImpl::extractHWAddr(vars, pkt4->getRemoteHWAddr(),
                                     prefix + "_REMOTE_HWADDR", suffix);
        RunScriptImpl::extractOption(vars,
                                     pkt4->getOption(DHO_DHCP_AGENT_OPTIONS),
                                     prefix, suffix);
        RunScriptImpl::extractSubOption(vars,
                                        pkt4->getOption(DHO_DHCP_AGENT_OPTIONS),
                                        RAI_OPTION_AGENT_CIRCUIT_ID,
                                        prefix, suffix);
        RunScriptImpl::extractSubOption(vars,
                                        pkt4->getOption(DHO_DHCP_AGENT_OPTIONS),
                                        RAI_OPTION_REMOTE_ID,
                                        prefix, suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_TXID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_ADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_PORT", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_ADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_PORT", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_INDEX", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_NAME", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_HOPS", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_SECS", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_FLAGS", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_CIADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_SIADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_YIADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_GIADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_RELAYED", suffix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_HWADDR", suffix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_LOCAL_HWADDR", suffix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_REMOTE_HWADDR", suffix);
    }
}

void
RunScriptImpl::extractPkt6(ProcessEnvVars& vars,
                           const Pkt6Ptr& pkt6,
                           const string& prefix,
                           const string& suffix) {
    if (pkt6) {
        RunScriptImpl::extractString(vars, pkt6->getName(pkt6->getType()),
                                     prefix + "_TYPE", suffix);
        RunScriptImpl::extractInteger(vars, pkt6->getTransid(),
                                      prefix + "_TXID", suffix);
        RunScriptImpl::extractString(vars, pkt6->getLocalAddr().toText(),
                                     prefix + "_LOCAL_ADDR", suffix);
        RunScriptImpl::extractInteger(vars, pkt6->getLocalPort(),
                                      prefix + "_LOCAL_PORT", suffix);
        RunScriptImpl::extractString(vars, pkt6->getRemoteAddr().toText(),
                                     prefix + "_REMOTE_ADDR", suffix);
        RunScriptImpl::extractInteger(vars, pkt6->getRemotePort(),
                                      prefix + "_REMOTE_PORT", suffix);
        RunScriptImpl::extractInteger(vars, pkt6->getIndex(),
                                      prefix + "_IFACE_INDEX", suffix);
        RunScriptImpl::extractString(vars, pkt6->getIface(),
                                     prefix + "_IFACE_NAME", suffix);
        RunScriptImpl::extractHWAddr(vars, pkt6->getRemoteHWAddr(),
                                     prefix + "_REMOTE_HWADDR", suffix);
        string proto_data = (pkt6->getProto() == Pkt6::UDP ? "UDP" : "TCP");
        RunScriptImpl::extractString(vars, proto_data,
                                     prefix + "_PROTO", suffix);
        RunScriptImpl::extractDUID(vars, pkt6->getClientId(),
                                   prefix + "_CLIENT_ID", suffix);
    } else {
        RunScriptImpl::extractString(vars, "", prefix + "_TYPE", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_TXID", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_ADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_LOCAL_PORT", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_ADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_REMOTE_PORT", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_INDEX", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_IFACE_NAME", suffix);
        RunScriptImpl::extractHWAddr(vars, HWAddrPtr(),
                                     prefix + "_REMOTE_HWADDR", suffix);
        RunScriptImpl::extractString(vars, "", prefix + "_PROTO", suffix);
        RunScriptImpl::extractDUID(vars, DuidPtr(),
                                   prefix + "_CLIENT_ID", suffix);
    }
}

} // namespace run_script
} // namespace isc
