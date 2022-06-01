// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <communication_state.h>
#include <ha_config.h>
#include <ha_config_parser.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/network_state.h>
#include <hooks/libinfo.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace isc {
namespace ha {
namespace test {

/// @brief Derivation of the @c CommunicationState class which allows
/// for modifications of poke time.
///
/// @tparam @c CommunicationState4 or @c CommunicationState6.
template<typename StateType>
class NakedCommunicationState : public StateType {
public:

    /// @brief Constructor.
    ///
    /// @param io_service pointer to the IO service object.
    explicit NakedCommunicationState(const asiolink::IOServicePtr& io_service,
                                     const HAConfigPtr& config)
        : StateType(io_service, config) {
    }

    /// @brief Checks if the object was poked recently.
    ///
    /// @return true if the object was poked less than 5 seconds ago,
    /// false otherwise.
    bool isPoked() const {
        return (StateType::getDurationInMillisecs() < 5000);
    }

    using StateType::config_;
    using StateType::timer_;
    using StateType::clock_skew_;
    using StateType::last_clock_skew_warn_;
    using StateType::my_time_at_skew_;
    using StateType::partner_time_at_skew_;
    using StateType::unsent_update_count_;
};

/// @brief Type of the NakedCommunicationState for DHCPv4.
typedef NakedCommunicationState<CommunicationState4> NakedCommunicationState4;

/// @brief Type of the pointer to the @c NakedCommunicationState4.
typedef boost::shared_ptr<NakedCommunicationState4> NakedCommunicationState4Ptr;

/// @brief Type of the NakedCommunicationState for DHCPv6.
typedef NakedCommunicationState<CommunicationState6> NakedCommunicationState6;

/// @brief Type of the pointer to the @c NakedCommunicationState6.
typedef boost::shared_ptr<NakedCommunicationState6> NakedCommunicationState6Ptr;

/// @brief General test fixture class for all HA unittests.
///
/// It provides basic functions to load and unload HA hooks library.
/// All test classes should derive from this class.
class HATest : public ::testing::Test {
public:

    /// @brief Constructor.
    HATest();

    /// @brief Destructor.
    virtual ~HATest();

    /// @brief Calls dhcp4_srv_configured callout to set IO service pointer.
    void startHAService();

    /// @brief Runs IO service for a specified amount of time.
    ///
    /// @param ms number of milliseconds for which the IO service should be
    /// run.
    void runIOService(long ms);

    /// @brief Runs IO service until timeout occurs or until provided method
    /// returns true.
    ///
    /// @param ms number of milliseconds for which the IO service should be
    /// run.
    /// @param stop_condition pointer to the function which returns true if
    /// when the IO service should be stopped.
    void runIOService(long ms, std::function<bool()> stop_condition);

    /// @brief Runs IO service in a thread.
    ///
    /// @return Shared pointer to the thread.
    boost::shared_ptr<std::thread> runIOServiceInThread();

    /// @brief Executes commands while running IO service in a thread.
    ///
    /// @param commands pointer to a function to be executed while IO service
    /// is run in thread.
    void testSynchronousCommands(std::function<void()> commands);

protected:

    /// @brief Signals that the IO service is running.
    ///
    /// @param running reference to the flag which is set to true when the
    /// IO service starts running and executes this function.
    /// @param mutex reference to the mutex used for synchronization.
    /// @param condvar reference to condition variable used for synchronization.
    void signalServiceRunning(bool& running, std::mutex& mutex,
                              std::condition_variable& condvar);

public:

    /// @brief Handler for timeout during runIOService invocation.
    ///
    /// @param [out] stop_flag set to true when the handler is invoked.
    void stopIOServiceHandler(bool& stop_flag);

    /// @brief Return HA configuration with three servers in JSON format.
    ///
    /// @param ha_mode HA operation mode (default is load balancing).
    /// @return Pointer to the unparsed configuration.
    data::ConstElementPtr
    createValidJsonConfiguration(const HAConfig::HAMode& ha_mode =
                                 HAConfig::LOAD_BALANCING) const;

    /// @brief Return HA configuration with one primary and two backup
    /// servers in the JSON format.
    ///
    /// @return Pointer to the unparsed configuration.
    data::ConstElementPtr
    createValidPassiveBackupJsonConfiguration() const;

    /// @brief Return HA configuration with three servers.
    ///
    /// @param ha_mode HA operation mode (default is load balancing).
    /// @return Pointer to the parsed configuration.
    HAConfigPtr createValidConfiguration(const HAConfig::HAMode& ha_mode =
                                         HAConfig::LOAD_BALANCING) const;

    /// @brief Return passive-backup configuration.
    ///
    /// @return Pointer to the parsed configuration.
    HAConfigPtr createValidPassiveBackupConfiguration() const;

    /// @brief Checks the status code and message against expected values.
    ///
    /// @param answer Element set containing an integer response and string
    /// comment.
    /// @param exp_status Status code against which to compare the status.
    /// @param exp_txt Expected text (not checked if empty)
    void checkAnswer(const isc::data::ConstElementPtr& answer,
                     const int exp_status,
                     const std::string& exp_txt = "");

    /// @brief Creates an identifier of arbitrary size with random values.
    ///
    /// This function is useful in generating random client identifiers and
    /// HW addresses for load balancing tests.
    ///
    /// @param key_size Size of the generated random identifier.
    std::vector<uint8_t> randomKey(const size_t key_size) const;

    /// @brief Generates simple DHCPv4 message.
    ///
    /// @param msg_type DHCPv4 message type to be created.
    /// @param hw_address_seed value from which HW address will be generated.
    /// @param client_id_seed value from which client identifier will be
    /// generated.
    /// @param secs value to be stored in the "secs" field of the DHCPv4 message.
    ///
    /// @return Pointer to the created message.
    dhcp::Pkt4Ptr createMessage4(const uint8_t msg_type,
                                 const uint8_t hw_address_seed,
                                 const uint8_t client_id_seed,
                                 const uint16_t secs) const;

    /// @brief Creates test DHCPv4 query instance.
    ///
    /// @param hw_address_text HW address to be included in the query. It is
    /// used in load balancing.
    ///
    /// @return Pointer to the DHCPv4 query instance.
    dhcp::Pkt4Ptr createQuery4(const std::string& hw_address_text) const;

    /// @brief Creates test DHCPv4 query instance.
    ///
    /// @param hw_address HW address to be included in the query. It is used
    /// in load balancing.
    /// @param client_id optional client identifier.
    dhcp::Pkt4Ptr createQuery4(const std::vector<uint8_t>& hw_address,
                               const std::vector<uint8_t>& client_id =
                               std::vector<uint8_t>()) const;

    /// @brief Creates test DHCPv6 query instance.
    ///
    /// @param duid DUI to be included in the query. It is used in load balancing.
    dhcp::Pkt6Ptr createQuery6(const std::vector<uint8_t>& duid) const;

    /// @brief Generates simple DHCPv6 message.
    ///
    /// @param msg_type DHCPv6 message type to be created.
    /// @param duid value from which DUID will be generated.
    /// @param elapsed_time value of the Elapsed Time option.
    ///
    /// @return Pointer to the created message.
    dhcp::Pkt6Ptr createMessage6(const uint8_t msg_type,
                                 const uint8_t duid_seed,
                                 const uint16_t elapsed_time) const;

    /// @brief Sets the DHCP multi-threading configuration in staging SrvConfig.
    ///
    /// @param enable_multi_threading value that maps to enable-multi-threading.
    /// @param thread_pool_size value that maps to thread-pool-size.
    /// @param queue_size value that maps to queue-size.
    void setDHCPMultiThreadingConfig(bool enable_multi_threading,
                                     uint32_t thread_pool_size = 0,
                                     uint32_t queue_size = 16);

    /// @brief Replace a pattern in a configuration.
    ///
    /// @param config Configuration to patch.
    /// @param from String to replace.
    /// @param repl String which replaces all occurrences of from.
    /// @result A copy of config where all occurrences of from were replaced
    /// by repl.
    std::string replaceInConfig(const std::string& config,
                                const std::string& from,
                                const std::string& repl) {
        std::string result(config);
        if (from.empty()) {
            return (result);
        }
        for (;;) {
            size_t where = result.find(from);
            if (where == std::string::npos) {
                return (result);
            }
            result.replace(where, from.size(), repl);
        }
        return (result);
    }

    /// @brief Constructs JSON string for HA "multi-threading" element.
    ///
    /// Constructs a JSON string with the following content:
    ///
    /// ```
    /// "multi-threading" {
    ///     "enable-multi-threading": <bool>,
    ///     "dedicated-http-listener": <bool>,
    ///     "http-listener-threads": <int>,
    ///     "http-client-threads": <int>
    /// }"
    /// ```
    ///
    /// @param enable_multi_threading value for enable-multi-threading.
    /// @param http_dedicated_listener value for dedicated-http-listener.
    /// @param http_listener_threads value for http-listener-threads
    /// @param http_client_threads value for http-client-threads
    ///
    /// @return JSON string
    std::string makeHAMtJson(bool enable_multi_threading,
                             bool http_dedicated_listener,
                             uint32_t http_listener_threads,
                             uint32_t http_client_threads);

    /// @brief Creates test DHCPv6 query instance.
    ///
    /// @param duid_text DUID to be included in the query. It is used in load
    /// balancing.
    ///
    /// @return Pointer to the DHCPv6 query instance.
    dhcp::Pkt6Ptr createQuery6(const std::string& duid_text) const;

    /// @brief Pointer to the IO service used in the tests.
    asiolink::IOServicePtr io_service_;

    /// @brief Object holding a state of the DHCP service.
    dhcp::NetworkStatePtr network_state_;
};

} // end of namespace isc::ha::test
} // end of namespace isc::ha
} // end of namespace isc
