// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/testutils/memory_host_data_source.h>

using namespace isc::db;
using namespace std;

namespace isc {
namespace dhcp {
namespace test {

ConstHostCollection
MemHostDataSource::getAll(const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {
    vector<uint8_t> ident(identifier_begin, identifier_begin + identifier_len);
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // If identifier type do not match, it's not for us
        if ((*h)->getIdentifierType() != identifier_type) {
            continue;
        }
        // If the identifier matches, we found one!
        if ((*h)->getIdentifier() == ident) {
            hosts.push_back(*h);
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getAll4(const SubnetID& subnet_id) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // Keep it when subnet_id matches.
        if ((*h)->getIPv4SubnetID() == subnet_id) {
            hosts.push_back(*h);
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getAll6(const SubnetID& subnet_id) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // Keep it when subnet_id matches.
        if ((*h)->getIPv6SubnetID() == subnet_id) {
            hosts.push_back(*h);
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getAllbyHostname(const std::string& hostname) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // Keep it when hostname matches.
        if ((*h)->getLowerHostname() == hostname) {
            hosts.push_back(*h);
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getAllbyHostname4(const std::string& hostname,
                                     const SubnetID& subnet_id) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // Keep it when hostname and subnet_id match.
        if (((*h)->getLowerHostname() == hostname) &&
            ((*h)->getIPv4SubnetID() == subnet_id)) {
            hosts.push_back(*h);
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getAllbyHostname6(const std::string& hostname,
                                     const SubnetID& subnet_id) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // Keep it when hostname and subnet_id match.
        if (((*h)->getLowerHostname() == hostname) &&
            ((*h)->getIPv6SubnetID() == subnet_id)) {
            hosts.push_back(*h);
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getPage4(const SubnetID& subnet_id,
                            size_t& /*source_index*/,
                            uint64_t lower_host_id,
                            const HostPageSize& page_size) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // Skip it when subnet_id does not match.
        if ((*h)->getIPv4SubnetID() != subnet_id) {
            continue;
        }
        if (lower_host_id && ((*h)->getHostId() <= lower_host_id)) {
            continue;
        }
        hosts.push_back(*h);
        if (hosts.size() == page_size.page_size_) {
            break;
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getPage6(const SubnetID& subnet_id,
                            size_t& /*source_index*/,
                            uint64_t lower_host_id,
                            const HostPageSize& page_size) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // Skip it when subnet_id does not match.
        if ((*h)->getIPv6SubnetID() != subnet_id) {
            continue;
        }
        if (lower_host_id && ((*h)->getHostId() <= lower_host_id)) {
            continue;
        }
        hosts.push_back(*h);
        if (hosts.size() == page_size.page_size_) {
            break;
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getPage4(size_t& /*source_index*/,
                            uint64_t lower_host_id,
                            const HostPageSize& page_size) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        if (lower_host_id && ((*h)->getHostId() <= lower_host_id)) {
            continue;
        }
        hosts.push_back(*h);
        if (hosts.size() == page_size.page_size_) {
            break;
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getPage6(size_t& /*source_index*/,
                            uint64_t lower_host_id,
                            const HostPageSize& page_size) const {
    ConstHostCollection hosts;
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        if (lower_host_id && ((*h)->getHostId() <= lower_host_id)) {
            continue;
        }
        hosts.push_back(*h);
        if (hosts.size() == page_size.page_size_) {
            break;
        }
    }
    return (hosts);
}

ConstHostCollection
MemHostDataSource::getAll4(const asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

ConstHostPtr
MemHostDataSource::get4(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) const {
    vector<uint8_t> ident(identifier_begin, identifier_begin + identifier_len);
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // If either subnet-id or identifier type do not match,
        // it's not our host
        if (((*h)->getIPv4SubnetID() != subnet_id) ||
            ((*h)->getIdentifierType() != identifier_type)) {
            continue;
        }
        // If the identifier matches, we found it!
        if ((*h)->getIdentifier() == ident) {
            return (*h);
        }
    }

    // Nothing found
    return (ConstHostPtr());
}

ConstHostPtr
MemHostDataSource::get6(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) const {
    vector<uint8_t> ident(identifier_begin, identifier_begin + identifier_len);
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // If either subnet-id or identifier type do not match,
        // it's not our host
        if (((*h)->getIPv6SubnetID() != subnet_id) ||
            ((*h)->getIdentifierType() != identifier_type)) {
            continue;
        }
        // If the identifier matches, we found it!
        if ((*h)->getIdentifier() == ident) {
            return (*h);
        }
    }

    return (ConstHostPtr());
}

ConstHostPtr
MemHostDataSource::get4(const SubnetID& subnet_id,
                        const asiolink::IOAddress& address) const {
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        if ((*h)->getIPv4SubnetID() == subnet_id &&
            (*h)->getIPv4Reservation() == address) {
            return (*h);
        }
    }

    return (ConstHostPtr());
}

ConstHostCollection
MemHostDataSource::getAll4(const SubnetID& subnet_id,
                           const asiolink::IOAddress& address) const {
    ConstHostCollection hosts;
    auto host = get4(subnet_id, address);
    if (host) {
        hosts.push_back(host);
    }
    return (hosts);
}

ConstHostPtr
MemHostDataSource::get6(const asiolink::IOAddress& /*prefix*/,
                        const uint8_t /*prefix_len*/) const {
    return (ConstHostPtr());
}

ConstHostPtr
MemHostDataSource::get6(const SubnetID& subnet_id,
                        const asiolink::IOAddress& address) const {
    for (auto h = store_.begin(); h != store_.end(); ++h) {

        // Naive approach: check hosts one by one

        // First check: subnet-id must match.
        if ((*h)->getIPv6SubnetID() != subnet_id) {
            // wrong subnet-id? ok, skip this one
            continue;
        }

        // Second check: the v6 reservation must much. This is very simple
        // as we ignore the reservation type.
        auto resrvs = (*h)->getIPv6Reservations();
        for (auto r = resrvs.first; r != resrvs.second; ++r) {
            if ((*r).second.getPrefix() == address) {
                return (*h);
            }
        }
    }

    return (ConstHostPtr());
}

ConstHostCollection
MemHostDataSource::getAll6(const SubnetID& subnet_id,
                           const asiolink::IOAddress& address) const {
    ConstHostCollection hosts;
    auto host = get6(subnet_id, address);
    if (host) {
        hosts.push_back(host);
    }
    return (hosts);
}

void
MemHostDataSource::add(const HostPtr& host) {
    host->setHostId(++next_host_id_);
    store_.push_back(host);
}

bool
MemHostDataSource::del(const SubnetID& subnet_id,
                       const asiolink::IOAddress& addr) {
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        if (addr.isV4()) {
            if ((*h)->getIPv4SubnetID() == subnet_id &&
                (*h)->getIPv4Reservation() == addr) {
                store_.erase(h);
                return (true);
            }
        } else {

            if ((*h)->getIPv6SubnetID() != subnet_id) {
                continue;
            }

            // Second check: the v6 reservation must much. This is very simple
            // as we ignore the reservation type.
            auto resrvs = (*h)->getIPv6Reservations();
            for (auto r = resrvs.first; r != resrvs.second; ++r) {
                if ((*r).second.getPrefix() == addr) {
                    store_.erase(h);
                    return (true);
                }
            }
        }
    }

    return (false);
}

bool
MemHostDataSource::del4(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) {
    vector<uint8_t> ident(identifier_begin, identifier_begin + identifier_len);
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // If either subnet-id or identifier type do not match,
        // it's not our host
        if (((*h)->getIPv4SubnetID() != subnet_id) ||
            ((*h)->getIdentifierType() != identifier_type)) {
            continue;
        }
        // If the identifier matches, we found it!
        if ((*h)->getIdentifier() == ident) {
            store_.erase(h);
            return (true);
        }
    }

    return (false);
}

bool
MemHostDataSource::del6(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) {
    vector<uint8_t> ident(identifier_begin, identifier_begin + identifier_len);
    for (auto h = store_.begin(); h != store_.end(); ++h) {
        // If either subnet-id or identifier type do not match,
        // it's not our host
        if (((*h)->getIPv6SubnetID() != subnet_id) ||
            ((*h)->getIdentifierType() != identifier_type)) {
            continue;
        }
        // If the identifier matches, we found it!
        if ((*h)->getIdentifier() == ident) {
            store_.erase(h);
            return (true);
        }
    }
    return (false);
}

size_t
MemHostDataSource::size() const {
    return (store_.size());
}

HostDataSourcePtr
memFactory(const DatabaseConnection::ParameterMap& /*parameters*/) {
    return (HostDataSourcePtr(new MemHostDataSource()));
}

} // namespace isc::dhcp::test
} // namespace isc::dhcp
} // namespace isc
