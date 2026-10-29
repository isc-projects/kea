// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_CB_CMDS_IMPL_H
#define TEST_CB_CMDS_IMPL_H

#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>

#include <functional>
#include <string>

#include <cb_cmds/cb_cmds_dhcp4.h>
#include <cb_cmds/cb_cmds_dhcp6.h>

namespace isc {
namespace cb {
namespace test {

/// @brief Template to derive ConfigCmdsDhcp[46]Impl used in unit tests.
///
/// @tparam ConfigCmdsDhcpXImpl Either @c ConfigCmdsDhcp4Impl or
/// @c ConfigCmdsDhcp6Impl.
template <typename ConfigCmdsDhcpXImpl>
class TestConfigCmdsDhcpXImpl : public ConfigCmdsDhcpXImpl {
public:

    /// @brief Runs a selected callout implementation.
    ///
    /// This wrapper method is used in unit tests to invoke a specified
    /// callout implementation for a given command specified in the
    /// textual format. The @c command_text is parsed and assigned to the
    /// callout handle. The callout handle is then used to invoke the
    /// specified callout. The callout sets response to the command in the
    /// callout handle. This method retrieves the response from the callout
    /// handle and returns to the caller.
    ///
    /// @param impl_call Pointer to the @c ConfigCmdsDhcp4Impl or @c
    /// ConfigCmdsDhcp6Impl class method to be invoked.
    ///
    /// @return Data structure representing response to command.
    data::ConstElementPtr
    run(void (TestConfigCmdsDhcpXImpl::*impl_call)(hooks::CalloutHandle&),
        const std::string& command_text) {
        // Parse command provided as text into JSON.
        data::ConstElementPtr command = data::Element::fromJSON(command_text);

        // Create new callout handle.
        hooks::CalloutHandlePtr callout_handle =
            hooks::HooksManager::createCalloutHandle();

        // Assign command to the callout handle.
        callout_handle->setArgument("command", command);

        // Call the callout under test.
        (this->*impl_call)(*callout_handle);

        // Retrieve response from the callout handle and return it.
        data::ConstElementPtr resp_element;
        callout_handle->getArgument("response", resp_element);
        return (resp_element);
    }
};


/// @brief Derivation of @c ConfigCmdsDhcp4Impl used in unit tests.
using TestConfigCmdsDhcp4Impl = TestConfigCmdsDhcpXImpl<ConfigCmdsDhcp4Impl>;

/// @brief Derivation of @c ConfigCmdsDhcp6Impl used in unit tests.
using TestConfigCmdsDhcp6Impl = TestConfigCmdsDhcpXImpl<ConfigCmdsDhcp6Impl>;

} // end of namespace isc::cb::test
} // end of namespace isc::cb
} // end of namespace isc

#endif // TEST_CB_CMDS_IMPL_H
