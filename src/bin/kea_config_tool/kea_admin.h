// Copyright (C) 2016 Deutsche Telekom AG.
//
// Author: Cristian Secareanu <cristian.secareanu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef KEA_ADMIN_H
#define KEA_ADMIN_H

#include <string>

namespace isc {
namespace config_tool {

/// @brief Used to run kea-admin tool from the Kea server.
class KeaAdmin {
private:
    /// @brief Constructor
    KeaAdmin();

    /// @brief Destructor
    ~KeaAdmin();

    /// @brief Reads symbolic link from /proc/<pid>/exe to get the absolute path
    ///     to the kea-admin executable.
    static std::string getPathToExecutable();

public:
    /// @brief Runs kea-admin with given parameters.
    ///
    /// @param admin_script_params parameters
    static void runAdminScript(const std::string& admin_script_params);
};

}  // namespace config_tool
}  // namespace isc

#endif  // KEA_ADMIN_H
