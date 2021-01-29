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
}

void
RunScriptImpl::extractBoolean(isc::util::ProcessEnvVars& vars,
                              const bool value,
                              const std::string prefix,
                              const std::string sufix) {
}

void
RunScriptImpl::extractInteger(isc::util::ProcessEnvVars& vars,
                              const uint32_t value,
                              const std::string prefix,
                              const std::string sufix) {
}

void
RunScriptImpl::extractString(isc::util::ProcessEnvVars& vars,
                             const bool value,
                             const std::string prefix,
                             const std::string sufix) {
}

void
RunScriptImpl::extractHWAddr(isc::util::ProcessEnvVars& vars,
                             const isc::dhcp::HWAddrPtr& hwaddr,
                             const std::string prefix,
                             const std::string sufix) {
}

void
RunScriptImpl::extractClientID(isc::util::ProcessEnvVars& vars,
                               const isc::dhcp::ClientIdPtr clientid,
                               const std::string prefix,
                               const std::string sufix) {
}

void
RunScriptImpl::extractOptionIA(isc::util::ProcessEnvVars& vars,
                               const isc::dhcp::Option6IAPtr option6IA,
                               const std::string prefix,
                               const std::string sufix) {
}

void
RunScriptImpl::extractSubnet4(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Subnet4Ptr subnet4,
                              const std::string prefix,
                              const std::string sufix) {
}

void
RunScriptImpl::extractSubnet6(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Subnet6Ptr subnet6,
                              const std::string prefix,
                              const std::string sufix) {
}

void
RunScriptImpl::extractLease4(isc::util::ProcessEnvVars& vars,
                             const isc::dhcp::Lease4Ptr& lease4,
                             const std::string prefix,
                             const std::string sufix) {
}

void
RunScriptImpl::extractLease6(isc::util::ProcessEnvVars& vars,
                             const isc::dhcp::Lease6Ptr& lease6,
                             const std::string prefix,
                             const std::string sufix) {
}

void
RunScriptImpl::extractLeases4(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Lease4CollectionPtr& leases4,
                              const std::string prefix,
                              const std::string sufix) {
}

void
RunScriptImpl::extractLeases6(isc::util::ProcessEnvVars& vars,
                              const isc::dhcp::Lease6CollectionPtr& leases6,
                              const std::string prefix,
                              const std::string sufix) {
}

void
RunScriptImpl::extractPkt4(isc::util::ProcessEnvVars& vars,
                           const isc::dhcp::Pkt4Ptr& pkt4,
                           const std::string prefix,
                           const std::string sufix) {
}

void
RunScriptImpl::extractPkt6(isc::util::ProcessEnvVars& vars,
                           const isc::dhcp::Pkt6Ptr& pkt6,
                           const std::string prefix,
                           const std::string sufix) {
}

} // end of namespace run_script
} // end of namespace isc
