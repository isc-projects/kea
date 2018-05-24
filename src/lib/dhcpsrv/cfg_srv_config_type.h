// Copyright (C) 2016 Deutsche Telekom AG.
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

#ifndef CFG_CONFIGURATIONTYPE_H
#define CFG_CONFIGURATIONTYPE_H

namespace isc {
namespace dhcp {

/// @brief Holds the location from where the server retrieves its configuration
/// data
///
/// Holds the location from where the server retrieves its configuration data.
/// The configuration data may reside in a local file or in a database.
///
class CfgSrvConfigType {
public:
    /// @brief Specifies the configuration type
    enum ConfigurationType {
        UNKNOWN = 0,
        // the configuration is read from the provided configuration file
        FILE = 1,
        //the configuration is read from the master database specified in the
        //provided configuration file
        MASTER_DATABASE = 2,
        //the configuration is read from a configuration database specified in the
        //provided configuration file. There is no need of master database
        CONFIG_DATABASE = 3
    };

    /// @brief Constructor.
    CfgSrvConfigType();

    ConfigurationType type_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // CFG_CONFIGURATIONTYPE_H
