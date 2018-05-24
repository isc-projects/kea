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
#include <kea_config_tool/command_options.h>
#include <kea_config_tool/config_tool_controller.h>
#include <kea_config_tool/config_tool_log.h>

#include <boost/exception/all.hpp>

#include <iostream>

using namespace isc::config_tool;

int main(int argc, char* argv[]) {
    constexpr int EXIT_SUCCESSFUL = 0;
    constexpr int EXIT_TRANSACTION_EXCEPTION = 1;
    constexpr int EXIT_INVALID_USAGE = 2;
    constexpr int EXIT_BOOST_EXCEPTION = 3;
    constexpr int EXIT_STD_EXCEPTION = 4;
    constexpr int EXIT_UNKNOWN_EXCEPTION = 5;

    int ret = EXIT_SUCCESSFUL;

    // Launch the controller passing in command line arguments.
    // Exit program with the controller's return code.
    try {
        ConfigToolController config_controller;
        config_controller.launch(argc, argv);
    } catch (const isc::TransactionException& ex) {
        ret = EXIT_TRANSACTION_EXCEPTION;
        std::cerr << "TransactionException: " << ex.what() << ", exiting with code " << ret
                  << std::endl;
        LOG_ERROR(config_tool_logger, CONFIG_TOOL_FAIL_PROCESS).arg(ex.what()).arg(ret);
    } catch (const InvalidUsage& ex) {
        ret = EXIT_INVALID_USAGE;
        std::cerr << "Invalid usage: " << ex.what() << ", exiting with code " << ret << std::endl;
        LOG_ERROR(config_tool_logger, CONFIG_TOOL_INVALID_USAGE).arg(ex.what()).arg(ret);
    } catch (const boost::exception& ex) {
        ret = EXIT_BOOST_EXCEPTION;
        std::cerr << "boost::exception: " << boost::diagnostic_information(ex)
                  << ", exiting with code " << ret << std::endl;
        LOG_ERROR(config_tool_logger, CONFIG_TOOL_FAIL_PROCESS)
            .arg(boost::diagnostic_information(ex))
            .arg(ret);
    } catch (const std::exception& ex) {
        ret = EXIT_STD_EXCEPTION;
        std::cerr << "std::exception: " << ex.what() << ", exiting with code " << ret << std::endl;
        LOG_ERROR(config_tool_logger, CONFIG_TOOL_FAIL_PROCESS).arg(ex.what()).arg(ret);
    } catch (...) {
        ret = EXIT_UNKNOWN_EXCEPTION;
        std::cerr << "unknown exception"
                  << ", exiting with code " << ret << std::endl;
        LOG_ERROR(config_tool_logger, CONFIG_TOOL_FAIL_PROCESS).arg("unknown exception").arg(ret);
    }

    LOG_INFO(config_tool_logger, CONFIG_TOOL_TERMINATE);
    return ret;
}
