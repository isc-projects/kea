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

#ifndef CONFIG_TOOOL_LOG_H
#define CONFIG_TOOOL_LOG_H

#include <kea_config_tool/config_tool_messages.h>
#include <log/logger_support.h>
#include <log/macros.h>

namespace isc {
namespace config_tool {

/// Define the logger for the "lfc" logging.
extern isc::log::Logger config_tool_logger;

}  // namespace config_tool
}  // namespace isc

#endif  // LFC_LOG_H
