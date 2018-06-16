// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/testutils/memory_host_data_source.h>

using namespace std;

namespace isc {
namespace dhcp {
namespace test {

ConstHostCollection
MemHostDataSource::getAll(const Host::IdentifierType& /*identifier_type*/,
                          const uint8_t* /*identifier_begin*/,
                          const size_t /*identifier_len*/) const {
    return (ConstHostCollection());
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

void
MemHostDataSource::add(const HostPtr& host) {
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
