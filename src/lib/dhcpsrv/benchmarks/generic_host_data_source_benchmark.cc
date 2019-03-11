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

#include <config.h>

#include <dhcpsrv/benchmarks/generic_host_data_source_benchmark.h>

#include <asiolink/io_address.h>
#include <database/testutils/schema.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>

using isc::asiolink::IOAddress;
using isc::dhcp::test::HostDataSourceUtils;
using std::cerr;
using std::endl;

namespace isc {
namespace dhcp {
namespace bench {

GenericHostDataSourceBenchmark::GenericHostDataSourceBenchmark() : hdsptr_() {
    LibDHCP::clearRuntimeOptionDefs();
}

GenericHostDataSourceBenchmark::~GenericHostDataSourceBenchmark() {
    LibDHCP::clearRuntimeOptionDefs();
    hdsptr_.reset();
}

void
GenericHostDataSourceBenchmark::setUp(::benchmark::State& state, size_t const& host_count) {
    state.PauseTiming();
    SetUp(state);
    prepareHosts(host_count);
    state.ResumeTiming();
}

void
GenericHostDataSourceBenchmark::setUpWithInserts(::benchmark::State& state,
                                                 size_t const& host_count) {
    state.PauseTiming();
    SetUp(state);
    prepareHosts(host_count);
    insertHosts();
    state.ResumeTiming();
}

OptionDescriptor
GenericHostDataSourceBenchmark::createEmptyOption(const Option::Universe& universe,
                                                  const uint16_t option_type,
                                                  const bool persist) const {
    OptionPtr option(new Option(universe, option_type));
    OptionDescriptor desc(option, persist);
    return desc;
}

OptionDescriptor
GenericHostDataSourceBenchmark::createVendorOption(const Option::Universe& universe,
                                                   const bool persist,
                                                   const bool formatted,
                                                   const uint32_t vendor_id) const {
    OptionVendorPtr option(new OptionVendor(universe, vendor_id));

    std::ostringstream s;
    if (formatted) {
        // Vendor id comprises vendor-id field, for which we need to
        // assign a value in the textual (formatted) format.
        s << vendor_id;
    }

    OptionDescriptor desc(option, persist, s.str());
    return desc;
}

void
GenericHostDataSourceBenchmark::addTestOptions(const HostPtr& host,
                                               const bool formatted,
                                               const AddedOptions& added_options) const {
    OptionDefSpaceContainer defs;

    if ((added_options == DHCP4_ONLY) || (added_options == DHCP4_AND_DHCP6)) {
        // Add DHCPv4 options.
        CfgOptionPtr opts = host->getCfgOption4();
        opts->add(createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                             true, formatted, "my-boot-file"),
                  DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint8>(Option::V4, DHO_DEFAULT_IP_TTL,
                                            false, formatted, 64),
                  DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V4, 1, false, formatted, 312131),
                  "vendor-encapsulated-options");
        opts->add(createAddressOption<Option4AddrLst>(254, false, formatted, "192.0.2.3"),
                  DHCP4_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V4, 1, true), "isc");
        opts->add(createAddressOption<Option4AddrLst>(2, false, formatted,
                                                      "10.0.0.5", "10.0.0.3",
                                                      "10.0.3.4"), "isc");

        // Add definitions for DHCPv4 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("vendor-encapsulated-1",
                                         1, "uint32")), "vendor-encapsulated-options");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-254", 254,
                                         "ipv4-address", true)), DHCP4_OPTION_SPACE);
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-1", 1, "empty")), "isc");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-2", 2,
                                         "ipv4-address", true)), "isc");
    }

    if ((added_options == DHCP6_ONLY) || (added_options == DHCP4_AND_DHCP6)) {
        // Add DHCPv6 options.
        CfgOptionPtr opts = host->getCfgOption6();
        opts->add(createOption<OptionString>(Option::V6, D6O_BOOTFILE_URL,
                                             true, formatted, "my-boot-file"),
                  DHCP6_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V6, D6O_INFORMATION_REFRESH_TIME,
                                             false, formatted, 3600),
                  DHCP6_OPTION_SPACE);
        opts->add(createVendorOption(Option::V6, false, formatted, 2495),
                  DHCP6_OPTION_SPACE);
        opts->add(createAddressOption<Option6AddrLst>(1024, false, formatted, "2001:db8:1::1"),
                  DHCP6_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V6, 1, true), "isc2");
        opts->add(createAddressOption<Option6AddrLst>(2, false, formatted,
                                                      "3000::1", "3000::2",
                                                      "3000::3"), "isc2");

        // Add definitions for DHCPv6 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-1024", 1024,
                                         "ipv6-address", true)), DHCP6_OPTION_SPACE);
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-1", 1, "empty")), "isc2");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-2", 2,
                                         "ipv6-address", true)), "isc2");
    }

    // Register created "runtime" option definitions. They will be used by a
    // host data source to convert option data into the appropriate option
    // classes when the options are retrieved.
    LibDHCP::setRuntimeOptionDefs(defs);
}

void
GenericHostDataSourceBenchmark::prepareHosts(size_t const& host_count) {
    if (host_count > 0xfffdu) {
        cerr << "host_count <= 0xfffd or change address xgeneration in "
                "GenericLeaseMgrBenchmark::prepareLeases6()"
             << endl;
    }
    hosts_.clear();
    for (size_t i = 0x0001u; i < 0x0001u + host_count; ++i) {
        std::stringstream ss;
        std::string n_host;
        ss << std::hex << i;
        ss >> n_host;

        const std::string prefix = std::string("2001:db8::") + n_host;
        HostPtr host = HostDataSourceUtils::initializeHost6(prefix, Host::IDENT_HWADDR, false);
        addTestOptions(host, false, DHCP4_AND_DHCP6);
        hosts_.push_back(host);
    }
}

void
GenericHostDataSourceBenchmark::insertHosts() {
    for (HostPtr host : hosts_) {
        hdsptr_->add(host);
    }
}

void
GenericHostDataSourceBenchmark::updateHosts() {
    for (HostPtr host : hosts_) {
        hdsptr_->add(host);
    }
}

void
GenericHostDataSourceBenchmark::benchGetAll() {
    for (HostPtr host : hosts_) {
        std::vector<uint8_t> hwaddr = host->getIdentifier();
        hdsptr_->getAll(host->getIdentifierType(), &hwaddr[0], hwaddr.size());
    }
}

void
GenericHostDataSourceBenchmark::getAllv4Resv() {
    for (HostPtr host : hosts_) {
        hdsptr_->getAll4(host->getIPv4Reservation());
    }
}

void
GenericHostDataSourceBenchmark::benchGet4IdentifierSubnetId() {
    for (HostPtr host : hosts_) {
        std::vector<uint8_t> hwaddr = host->getIdentifier();
        hdsptr_->get4(host->getIPv4SubnetID(), host->getIdentifierType(),
                      &hwaddr[0], hwaddr.size());
    }
}

void
GenericHostDataSourceBenchmark::benchGet4SubnetIdv4Resrv() {
    for (HostPtr host : hosts_) {
        hdsptr_->get4(host->getIPv4SubnetID(), host->getIPv4Reservation());
    }
}

void
GenericHostDataSourceBenchmark::benchGet6IdentifierSubnetId() {
    for (HostPtr host : hosts_) {
        std::vector<uint8_t> hwaddr = host->getIdentifier();
        hdsptr_->get6(host->getIPv6SubnetID(), host->getIdentifierType(),
                      &hwaddr[0], hwaddr.size());
    }
}

void
GenericHostDataSourceBenchmark::benchGet6SubnetIdAddr() {
    for (HostPtr host : hosts_) {
        const IPv6ResrvRange range = host->getIPv6Reservations();
        hdsptr_->get6(host->getIPv6SubnetID(), range.first->second.getPrefix());
    }
}

void
GenericHostDataSourceBenchmark::benchGet6Prefix() {
    for (HostPtr host : hosts_) {
        const IPv6ResrvRange range = host->getIPv6Reservations();
        hdsptr_->get6(range.first->second.getPrefix(),
                      range.first->second.getPrefixLen());
    }
}

}  // namespace bench
}  // namespace dhcp
}  // namespace isc
