// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SCRIPTS_HOOK_H
#define SCRIPTS_HOOK_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>

namespace hooks {
namespace scripts {

/// @brief Represents scripts hook configuration
class ScriptsConfig {
 public:
    /// @brief default constructor
    ScriptsConfig();

    /// @brief Clears configuration.
    void clear();
    
    /// @brief scripts to be called.
    std::vector<std::string> scripts_;

    /// @brief define whether scripts should be called async (true) or sync (false)
    bool async_;
};

/// @brief pointer to ScriptsConfig
typedef boost::shared_ptr<ScriptsConfig> ScriptsConfigPtr;

/// @brief returns current Scripts hook configuration
ScriptsConfigPtr getScriptsConfig();

};
};

#endif
