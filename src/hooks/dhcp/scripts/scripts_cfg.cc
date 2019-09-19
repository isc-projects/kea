// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <scripts_cfg.h>

namespace {
hooks::scripts::ScriptsConfigPtr config;
};

namespace hooks {
namespace scripts {

ScriptsConfig::ScriptsConfig() {
    clear();
}

void
ScriptsConfig::clear() {
    async_ = true;
    scripts_.clear();
}

ScriptsConfigPtr getScriptsConfig() {
    if (!config) {
        config.reset(new ScriptsConfig());
    }
    return (config);
}



};
};
