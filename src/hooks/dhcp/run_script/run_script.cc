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
RunScriptImpl::runScript(const ProcessEnvVars& vars) {
    ProcessArgs args;
    ProcessSpawn process(name_, args, vars);
}

} // end of namespace run_script
} // end of namespace isc
