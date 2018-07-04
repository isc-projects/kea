// Copyright (C) 2016-2018 Deutsche Telekom AG.
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

#include <config.h>
#include <kea_config_tool/config_tool_controller.h>
#include <kea_config_tool/config_tool_log.h>

namespace isc {
namespace config_tool {

/// @brief Defines the logger used within Kea Config Tool.
isc::log::Logger config_tool_logger(ConfigToolController::config_tool_app_name_);

}  // namespace config_tool
}  // namespace isc
