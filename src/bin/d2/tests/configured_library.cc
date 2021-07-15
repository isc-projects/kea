// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @brief d2_srv_configured callout testing library

#include <config.h>
#include <cc/data.h>
#include <hooks/hooks.h>

using namespace isc::data;
using namespace isc::hooks;
using namespace std;

namespace {

extern "C" {

// d2_srv_configured callout.
int
d2_srv_configured(CalloutHandle& handle) {
    // Get the parameters.
    ConstElementPtr cfg;
    string error;
    handle.getArgument("json_config", cfg);
    handle.getArgument("error", error);

    if (cfg) {
        ConstElementPtr uc = cfg->get("user-context");
        if (uc) {
            ConstElementPtr msg = uc->get("error");
            if (msg && (msg->getType() == Element::string)) {
                error += msg->stringValue();
            }
        }
    }

    if (!error.empty()) {
        handle.setArgument("error", error);
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    }
    return (0);
}

// Framework functions.
int
version() {
    return (KEA_HOOKS_VERSION);
}

// load() initializes the user library if the main image was statically linked.
int
load(isc::hooks::LibraryHandle&) {
#ifdef USE_STATIC_LINK
    hooksStaticLinkInit();
#endif
    return (0);
}

}
}
