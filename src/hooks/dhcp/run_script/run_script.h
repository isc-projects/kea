// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RUN_SCRIPT_H
#define RUN_SCRIPT_H

#include <asiolink/process_spawn.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/option6_ia.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <hooks/library_handle.h>
#include <string>

namespace isc {
namespace run_script {

/// @brief Run Script implementation.
class RunScriptImpl {
public:
    /// @brief Constructor.
    RunScriptImpl();

    /// @brief Destructor.
    ~RunScriptImpl() = default;

    /// @brief Sets IO service to be used by the @ref ProcessSpawn instance.
    ///
    /// @param io_service The IOService object, used for all ASIO operations.
    static void setIOService(const isc::asiolink::IOServicePtr& io_service) {
        io_service_ = io_service;
    }

    /// @brief Gets IO service to be used by the @ref ProcessSpawn instance.
    ///
    /// @return The IOService object, used for all ASIO operations.
    static isc::asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

    /// @brief Extract boolean data and append to environment.
    ///
    /// @param value The value to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractBoolean(isc::asiolink::ProcessEnvVars& vars,
                               const bool value,
                               const std::string& prefix = "",
                               const std::string& suffix = "");

    /// @brief Extract integer data and append to environment.
    ///
    /// @param value The value to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractInteger(isc::asiolink::ProcessEnvVars& vars,
                               const uint64_t value,
                               const std::string& prefix = "",
                               const std::string& suffix = "");

    /// @brief Extract string data and append to environment.
    ///
    /// @param value The value to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractString(isc::asiolink::ProcessEnvVars& vars,
                              const std::string& value,
                              const std::string& prefix = "",
                              const std::string& suffix = "");

    /// @brief Extract HWAddr data and append to environment.
    ///
    /// @param hwaddr The hwaddr to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractHWAddr(isc::asiolink::ProcessEnvVars& vars,
                              const isc::dhcp::HWAddrPtr& hwaddr,
                              const std::string& prefix = "",
                              const std::string& suffix = "");

    /// @brief Extract DUID data and append to environment.
    ///
    /// @param duid The duid to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractDUID(isc::asiolink::ProcessEnvVars& vars,
                            const isc::dhcp::DuidPtr duid,
                            const std::string& prefix = "",
                            const std::string& suffix = "");

    /// @brief Extract Option data and append to environment.
    ///
    /// @param option The option to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractOption(isc::asiolink::ProcessEnvVars& vars,
                              const isc::dhcp::OptionPtr option,
                              const std::string& prefix = "",
                              const std::string& suffix = "");

    /// @brief Extract Option SubOption data and append to environment.
    ///
    /// @param option The parent option of the suboption to be exported to
    /// target script environment.
    /// @param code The code of the suboption.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractSubOption(isc::asiolink::ProcessEnvVars& vars,
                                 const isc::dhcp::OptionPtr option,
                                 uint16_t code,
                                 const std::string& prefix = "",
                                 const std::string& suffix = "");

    /// @brief Extract Option6IA data and append to environment.
    ///
    /// @param option6IA The option6IA to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractOptionIA(isc::asiolink::ProcessEnvVars& vars,
                                const isc::dhcp::Option6IAPtr option6IA,
                                const std::string& prefix = "",
                                const std::string& suffix = "");

    /// @brief Extract Subnet4 data and append to environment.
    ///
    /// @param subnet4 The subnet4 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractSubnet4(isc::asiolink::ProcessEnvVars& vars,
                               const isc::dhcp::Subnet4Ptr subnet4,
                               const std::string& prefix = "",
                               const std::string& suffix = "");

    /// @brief Extract Subnet6 data and append to environment.
    ///
    /// @param subnet6 The subnet6 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractSubnet6(isc::asiolink::ProcessEnvVars& vars,
                               const isc::dhcp::Subnet6Ptr subnet6,
                               const std::string& prefix = "",
                               const std::string& suffix = "");

    /// @brief Extract Lease4 data and append to environment.
    ///
    /// @param lease4 The lease4 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractLease4(isc::asiolink::ProcessEnvVars& vars,
                              const isc::dhcp::Lease4Ptr& lease4,
                              const std::string& prefix = "",
                              const std::string& suffix = "");

    /// @brief Extract Lease6 data and append to environment.
    ///
    /// @param lease6 The lease6 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractLease6(isc::asiolink::ProcessEnvVars& vars,
                              const isc::dhcp::Lease6Ptr& lease6,
                              const std::string& prefix = "",
                              const std::string& suffix = "");

    /// @brief Extract Lease4Collection data and append to environment.
    ///
    /// @param leases4 The leases4 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractLeases4(isc::asiolink::ProcessEnvVars& vars,
                               const isc::dhcp::Lease4CollectionPtr& leases4,
                               const std::string& prefix = "",
                               const std::string& suffix = "");

    /// @brief Extract Lease6Collection data and append to environment.
    ///
    /// @param leases6 The leases6 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractLeases6(isc::asiolink::ProcessEnvVars& vars,
                               const isc::dhcp::Lease6CollectionPtr& leases6,
                               const std::string& prefix = "",
                               const std::string& suffix = "");

    /// @brief Extract Pkt4 data and append to environment.
    ///
    /// @param pkt4 The pkt4 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractPkt4(isc::asiolink::ProcessEnvVars& vars,
                            const isc::dhcp::Pkt4Ptr& pkt4,
                            const std::string& prefix = "",
                            const std::string& suffix = "");

    /// @brief Extract Pkt6 data and append to environment.
    ///
    /// @param pkt6 The pkt6 to be exported to target script environment.
    /// @param prefix The prefix for the name of the environment variable.
    /// @param suffix The suffix for the name of the environment variable.
    static void extractPkt6(isc::asiolink::ProcessEnvVars& vars,
                            const isc::dhcp::Pkt6Ptr& pkt6,
                            const std::string& prefix = "",
                            const std::string& suffix = "");

    /// @brief Run Script with specified arguments and environment parameters.
    ///
    /// @param args The arguments for the target script.
    /// @param vars The environment variables made available for the target
    /// script.
    void runScript(const isc::asiolink::ProcessArgs& args,
                   const isc::asiolink::ProcessEnvVars& vars);

    /// @brief Set name of the target script.
    ///
    /// @param name The name of the target script.
    void setName(const std::string& name) {
        name_ = name;
    }

    /// @brief Get name of the target script.
    ///
    /// @return The name of the target script.
    std::string getName() const {
        return (name_);
    }

    /// @brief Set the synchronous call mode for the target script.
    ///
    /// @param name The synchronous call mode for the target script.
    void setSync(const bool sync) {
        sync_ = sync;
    }

    /// @brief Get the synchronous call mode for the target script.
    ///
    /// @return The synchronous call mode for the target script.
    bool getSync() const {
        return (sync_);
    }

    /// @brief This function parses and applies configuration parameters.
    void configure(isc::hooks::LibraryHandle& handle);

private:
    /// @brief Script name.
    std::string name_;

    /// @brief Sync flag
    ///
    /// When set to true, the call to @ref runScript blocks until the script
    /// exits, otherwise the call will return immediately after the script is
    /// started.
    bool sync_;

    /// @brief The IOService object, used for all ASIO operations.
    static isc::asiolink::IOServicePtr io_service_;
};

/// @brief The type of shared pointers to Run Script implementations.
typedef boost::shared_ptr<RunScriptImpl> RunScriptImplPtr;

} // namespace run_script
} // namespace isc
#endif
