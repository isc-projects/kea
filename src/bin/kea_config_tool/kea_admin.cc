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

#include <kea_config_tool/kea_admin.h>

#include <kea_config_tool/config_tool_controller.h>
#include <kea_config_tool/config_tool_log.h>
#include <log/macros.h>

#include <libgen.h>

using namespace std;
using namespace isc::dhcp;

static const uint32_t MAX_LINE = 256U;

namespace isc {
namespace config_tool {

KeaAdmin::KeaAdmin() {
}

KeaAdmin::~KeaAdmin() {
}

std::string KeaAdmin::getPathToExecutable() {
    const ssize_t maxPathLength = FILENAME_MAX;
    std::stringstream proc_path;
    boost::scoped_array<char> exe_path(new char[maxPathLength]);

    proc_path << "/proc/" << getpid() << "/exe";
    int bytes = readlink(proc_path.str().c_str(), exe_path.get(), maxPathLength);
    if (bytes < 0) {
        bytes = 0;
    }
    exe_path[bytes] = '\0';

    return std::string(exe_path.get());
}

void KeaAdmin::runAdminScript(const std::string& admin_script_params) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_RUN_KEAADMIN);

    std::string configToolPath = getPathToExecutable();
    std::string executable(dirname(const_cast<char*>(configToolPath.c_str())));
    executable += "/kea-admin";

    // The command line is composed of the script's executable name, path and
    // parameters.
    std::string cmdLine = executable + " " + admin_script_params;

    FILE* fProcess;
    int status;

    fProcess = popen(cmdLine.c_str(), "r");
    if (fProcess == NULL) {
        isc_throw(RunTimeFail, "could not start run the admin script: " << cmdLine);
    }

    char buffProcOutput[MAX_LINE];
    while (!feof(fProcess)) {
        if (fgets(buffProcOutput, MAX_LINE, fProcess) == NULL) {
            break;
        }
        std::cout << buffProcOutput;
    }
    std::cout << std::endl;

    status = pclose(fProcess);

    if (status == -1) {
        isc_throw(RunTimeFail,
                  "could not close the admin script process. pclose error. " << cmdLine);
    } else if (WIFEXITED(status)) {
        int exitCode = WEXITSTATUS(status);
        if (exitCode == 0) {
            // The kea-admin process has returned success as error code.
            return;
        }

        isc_throw(RunTimeFail, "admin script error: " << exitCode);

    } else {
        isc_throw(RunTimeFail, "admin script abnormal termination, error: " << status);
    }
}

}  // namespace config_tool
}  // namespace isc
