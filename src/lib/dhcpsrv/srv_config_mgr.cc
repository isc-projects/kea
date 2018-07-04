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

#include <dhcpsrv/srv_config_mgr.h>

#include <exceptions/exceptions.h>

using namespace std;

namespace isc {
namespace dhcp {

SrvConfigMgr::SrvConfigMgr() {
}

SrvConfigMgr::~SrvConfigMgr() {
}

std::string SrvConfigMgr::getDBVersion() {
    isc_throw(NotImplemented, "SrvConfigMgr::getDBVersion() called");
}

}  // namespace dhcp
}  // namespace isc
