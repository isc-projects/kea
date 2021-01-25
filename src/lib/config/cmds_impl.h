// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef CMDS_IMPL_H
#define CMDS_IMPL_H

#include <config.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <hooks/hooks.h>
#include <exceptions/exceptions.h>

#include <string>

namespace isc {
namespace config {

/// @brief Base class that command handler implementers may use for common tasks.
class CmdsImpl {
protected:
    /// @brief Extracts the command name and arguments from a Callout handle
    ///
    /// @param handle Callout context handle expected to contain the JSON command
    /// text
    ///
    /// @throw isc::BadValue if the text does not contain a properly formed command
    void extractCommand(hooks::CalloutHandle& handle) {
        try {
            data::ConstElementPtr command;
            handle.getArgument("command", command);
            cmd_name_ = parseCommand(cmd_args_, command);
        } catch (const std::exception& ex) {
            isc_throw(isc::BadValue, "JSON command text is invalid: " << ex.what());
        }
    }

    /// @brief Set the callout argument "response" to indicate success
    ///
    /// @param handle Callout context handle in which to set the "response" argument
    /// @param text string text to be used as the response description
    void setSuccessResponse(hooks::CalloutHandle& handle, const std::string& text) {
        data::ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, text);
        setResponse (handle, response);
    }

    /// @brief Set the callout argument "response" to indicate an error
    ///
    /// @param handle Callout context handle in which to set the "response" argument
    /// @param text string text to be used as the response description
    /// @param status numeric value to use as the response result, defaults to
    /// CONTROL_RESULT_ERROR
    void setErrorResponse(hooks::CalloutHandle& handle, const std::string& text,
        int status=CONTROL_RESULT_ERROR) {
        data::ConstElementPtr response = createAnswer(status, text);
        setResponse (handle, response);
    }

    /// @brief Set the callout argument "response" to the given response
    ///
    /// @param handle Callout context handle in which to set the "response" argument
    /// @param response ElementPtr to the result to use as the response
    void setResponse(hooks::CalloutHandle& handle, data::ConstElementPtr& response) {
        handle.setArgument ("response", response);
    }

    /// @brief Stores the command name extracted by a call to extractCommand
    std::string cmd_name_;

    /// @brief Stores the command arguments extracted by a call to extractCommand
    data::ConstElementPtr cmd_args_;
};

}
}

#endif // CMDS_IMPL_H
