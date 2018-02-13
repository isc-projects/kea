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

class GenericHostDataSourceBenchmark : public ::benchmark::Fixture {
public:
    enum Universe { V4, V6 };
    enum AddedOptions { DHCP4_ONLY, DHCP6_ONLY, DHCP4_AND_DHCP6 };

    GenericHostDataSourceBenchmark();
    virtual ~GenericHostDataSourceBenchmark();

    HostPtr initializeHost4(const std::string& address,
                            const Host::IdentifierType& id);
    HostPtr initializeHost6(std::string address,
                            Host::IdentifierType id,
                            bool prefix,
                            bool new_identifier = true);
    std::vector<uint8_t> generateHWAddr(const bool new_identifier = true);
    std::vector<uint8_t> generateIdentifier(const bool new_identifier = true);

    OptionDescriptor createEmptyOption(const Option::Universe& universe,
                                       const uint16_t option_type,
                                       const bool persist) const;
    template <typename OptionType, typename DataType>
    OptionDescriptor createOption(const Option::Universe& universe,
                                  const uint16_t option_type,
                                  const bool persist,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(
            new OptionType(universe, option_type, value));
        std::ostringstream s;
        if (formatted) {
            // Using formatted option value. Convert option value to a
            // textual format.
            s << value;
        }
        OptionDescriptor desc(option, persist, s.str());
        return desc;
    }
    template <typename OptionType, typename DataType>
    OptionDescriptor createOption(const uint16_t option_type,
                                  const bool persist,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(
            new OptionType(option_type, value));

        std::ostringstream s;
        if (formatted) {
            // Using formatted option value. Convert option value to a
            // textual format.
            s << value;
        }

        OptionDescriptor desc(option, persist, s.str());
        return desc;
    }
    template <typename OptionType>
    OptionDescriptor
    createAddressOption(const uint16_t option_type,
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

        boost::shared_ptr<OptionType> option(
            new OptionType(option_type, addresses));
        OptionDescriptor desc(option, persist, s.str());
        return desc;
    }
    OptionDescriptor createVendorOption(const Option::Universe& universe,
                                        const bool persist,
                                        const bool formatted,
                                        const uint32_t vendor_id) const;
    void addTestOptions(const HostPtr& host,
                        const bool formatted,
                        const AddedOptions& added_options) const;

    void ReentrantSetUp(::benchmark::State& state, size_t const& host_count);
    void ReentrantSetUpWithInserts(::benchmark::State& state,
                                   size_t const& host_count);
    void prepareHosts(size_t const& lease_count);
    void insertHosts();
    void updateHosts();
    void getAll2();
    void getAll3();
    void getAll1();
    void get4_3();
    void get4_4();
    void get4_2();
    void get6_3();
    void get6_4();
    void get6_2_subnetid_address();
    void get6_2_prefix_prefixlen();

    HostDataSourcePtr hdsptr_;
    HostCollection hosts_;
};

}  // namespace bench
}  // namespace dhcp
}  // namespace isc

#endif
