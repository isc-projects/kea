// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2017 Deutsche Telekom AG.
//
// Authors: Andrei Pavel <andrei.pavel@qualitance.com>
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

#ifndef GENERIC_HOST_DATA_SOURCE_UNITTEST_H
#define GENERIC_HOST_DATA_SOURCE_UNITTEST_H

#include <benchmark/benchmark.h>

#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/host.h>

namespace isc {
namespace dhcp {
namespace bench {

/// @brief Base fixture class for benchmarking host backends.
class GenericHostDataSourceBenchmark : public ::benchmark::Fixture {
public:
    /// @brief Defines universe (IPv4 or IPv6)
    enum Universe { V4, V6 };

    /// @brief Defines what kind of options should be added for a host
    enum AddedOptions {
        DHCP4_ONLY,      ///< DHCPv4-only options
        DHCP6_ONLY,      ///< DHCPv6-only options
        DHCP4_AND_DHCP6  ///< Both DHCPv4 and DHCPv6 options
    };

    /// @brief Constructor
    ///
    /// Clears runtime option definitions.
    GenericHostDataSourceBenchmark();

    /// @brief Destructor
    ///
    /// Clears runtime option definitions and clears hdsptr_ pointer.
    virtual ~GenericHostDataSourceBenchmark();

    /// @brief Creates a generic option with specific parameters.
    ///
    /// @param universe (v4 or v6)
    /// @param option_type code of the option
    /// @param persist whether the option should always be included (yes) or not (no)
    /// @return the option created wrapped in an option descriptor structure
    OptionDescriptor createEmptyOption(const Option::Universe& universe,
                                       const uint16_t option_type,
                                       const bool persist) const;

    /// @brief Creates an option of specified type and value
    ///
    /// @tparam OptionType Option class to be instantiated
    /// @tparam DataType type of parameter to be passed to OptionType constructor
    /// @param universe (v4 or v6)
    /// @param option_type code of the option
    /// @param persist whether the option should always be included (yes) or not (no)
    /// @param formatted whether the value passed to description should be converted to text
    /// @param value option value
    /// @return the option created wrapped in an option descriptor structure
    template <typename OptionType, typename DataType>
    OptionDescriptor createOption(const Option::Universe& universe,
                                  const uint16_t option_type,
                                  const bool persist,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<Option> option(new OptionType(universe, option_type, value));
        std::ostringstream s;
        if (formatted) {
            // Using formatted option value. Convert option value to a
            // textual format.
            s << value;
        }
        OptionDescriptor desc(option, persist, s.str());
        return desc;
    }

    /// @brief Creates an option with addresses
    ///
    /// @tparam OptionType specifies a class to be instantiated
    /// @param option_type code of the option
    /// @param persist whether the option should always be included (yes) or not (no)
    /// @param formatted whether the value passed to description should be converted to text
    /// @param address1 first address to be used (optional)
    /// @param address2 second address to be used (optional)
    /// @param address3 third address to be used (optional)
    /// @return the option created wrapped in an option descriptor structure
    template <typename OptionType>
    OptionDescriptor createAddressOption(const uint16_t option_type,
                                         const bool persist,
                                         const bool formatted,
                                         const std::string& address1 = "",
                                         const std::string& address2 = "",
                                         const std::string& address3 = "") const {

        std::ostringstream s;
        // First address.
        typename OptionType::AddressContainer addresses;
        if (!address1.empty()) {
            addresses.push_back(asiolink::IOAddress(address1));
            if (formatted) {
                s << address1;
            }
        }
        // Second address.
        if (!address2.empty()) {
            addresses.push_back(asiolink::IOAddress(address2));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address2;
            }
        }
        // Third address.
        if (!address3.empty()) {
            addresses.push_back(asiolink::IOAddress(address3));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address3;
            }
        }

        boost::shared_ptr<OptionType> option(new OptionType(option_type, addresses));
        OptionDescriptor desc(option, persist, s.str());
        return desc;
    }

    /// @brief creates a vendor-option
    ///
    /// @param universe (v4 or v6)
    /// @param persist whether the option should always be included
    /// @param formatted whether the value passed to description should be
    ///        converted to text
    /// @param vendor_id 32-unsigned bit enterprise-id
    /// @return the option created wrapped in an option descriptor structure
    OptionDescriptor createVendorOption(const Option::Universe& universe,
                                        const bool persist,
                                        const bool formatted,
                                        const uint32_t vendor_id) const;

    /// @brief Adds several v4 and/or v6 options to the host
    ///
    /// @param host host reservation to be extended with options
    /// @param formatted whether to generate text representation
    /// @param added_options v4, v6 or both
    void addTestOptions(const HostPtr& host,
                        const bool formatted,
                        const AddedOptions& added_options) const;

    /// @brief Sets up timers, creates and inserts hosts.
    ///
    /// @param state reference to the state of the benchmark
    /// @param host_count number of hosts to be created
    void setUp(::benchmark::State& state, size_t const& host_count);

    /// @brief Sets up the benchmark with specified number of hosts
    ///
    /// @param state reference to the state of the benchmark
    /// @param host_count number of hosts to be created
    void setUpWithInserts(::benchmark::State& state, size_t const& host_count);

    /// @brief Creates specified number of hosts and stores them in hosts_
    ///
    /// @param host_count number of hosts to be created
    void prepareHosts(size_t const& host_count);

    /// @brief Inserts all hosts stored in hosts_ into the benchmarked host backend
    void insertHosts();

    /// @brief Updates all hosts stored in hosts_ in the benchmarked host backend
    void updateHosts();

    /// @brief Essential steps required to benchmark the
    ///        getAll(identifier-type, identifier) call.
    void benchGetAll();

    /// @brief Essential steps required to benchmark host reservation retrieval
    ///        using getAll(ipv4-reservation) call.
    void getAllv4Resv();

    /// @brief Essential steps requires to benchmark host reservation retrieval
    ///        using getAll(identifier-type, identifier, subnet-id) call.
    void benchGet4IdentifierSubnetId();

    /// @brief Essential steps requires to benchmark host reservation retrieval
    ///        using getAll(v4-reservation) call.
    void benchGet4SubnetIdv4Resrv();

    /// @brief Essential steps requires to benchmark host reservation retrieval
    ///        using get6(identifier-type, identifier, subnet-id) call.
    void benchGet6IdentifierSubnetId();

    /// @brief Essential steps requires to benchmark host reservation retrieval
    ///        using get6(ip-addr, subnet-id) call.
    void benchGet6SubnetIdAddr();

    /// @brief Essential steps requires to benchmark host reservation retrieval
    ///        using get6(prefix, len) call.
    void benchGet6Prefix();

    /// Pointer to the host backend being benchmarked
    HostDataSourcePtr hdsptr_;

    /// Store hosts being used during benchmark.
    HostCollection hosts_;
};

}  // namespace bench
}  // namespace dhcp
}  // namespace isc

#endif
