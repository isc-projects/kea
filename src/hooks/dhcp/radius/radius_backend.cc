// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <radius.h>
#include <radius_backend.h>
#include <radius_log.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace isc {
namespace radius {

RadiusBackend::RadiusBackend() : impl_(new RadiusBackendImpl()) {
}

RadiusBackend::~RadiusBackend() {
}

ConstHostCollection
RadiusBackend::getAll(const Host::IdentifierType& /*identifier_type*/,
                      const uint8_t* /*identifier_begin*/,
                      const size_t /*identifier_len*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
RadiusBackend::getAll4(const isc::dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
RadiusBackend::getAll6(const isc::dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
RadiusBackend::getAllbyHostname(const std::string& /*hostname*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
RadiusBackend::getAllbyHostname4(const std::string& /*hostname*/,
                                 const dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
RadiusBackend::getAllbyHostname6(const std::string& /*hostname*/,
                                 const dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

isc::dhcp::ConstHostCollection
RadiusBackend::getPage4(const isc::dhcp::SubnetID& /*subnet_id*/,
                        size_t& /*source_index*/,
                        uint64_t /*lower_host_id*/,
                        const dhcp::HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

isc::dhcp::ConstHostCollection
RadiusBackend::getPage6(const isc::dhcp::SubnetID& /*subnet_id*/,
                        size_t& /*source_index*/,
                        uint64_t /*lower_host_id*/,
                        const dhcp::HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

isc::dhcp::ConstHostCollection
RadiusBackend::getPage4(size_t& /*source_index*/,
                        uint64_t /*lower_host_id*/,
                        const dhcp::HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

isc::dhcp::ConstHostCollection
RadiusBackend::getPage6(size_t& /*source_index*/,
                        uint64_t /*lower_host_id*/,
                        const dhcp::HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
RadiusBackend::getAll4(const isc::asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

ConstHostPtr
RadiusBackend::get4(const isc::dhcp::SubnetID& subnet_id,
                    const isc::dhcp::Host::IdentifierType& identifier_type,
                    const uint8_t* identifier_begin,
                    const size_t identifier_len) const {
    return (impl_->get4(subnet_id, identifier_type, identifier_begin,
                        identifier_len));
}

ConstHostPtr
RadiusBackend::get4(const isc::dhcp::SubnetID& /*subnet_id*/,
                    const isc::asiolink::IOAddress& /*address*/) const {
    return (ConstHostPtr());
}

ConstHostCollection
RadiusBackend::getAll4(const isc::dhcp::SubnetID /*subnet_id*/&,
                       const isc::asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

ConstHostPtr
RadiusBackend::get6(const isc::dhcp::SubnetID& subnet_id,
                    const isc::dhcp::Host::IdentifierType& identifier_type,
                    const uint8_t* identifier_begin,
                    const size_t identifier_len) const {
    return (impl_->get6(subnet_id, identifier_type, identifier_begin,
                        identifier_len));
}

ConstHostPtr
RadiusBackend::get6(const isc::asiolink::IOAddress& /*prefix*/,
                    const uint8_t /*prefix_len*/) const {
    return (ConstHostPtr());
}

ConstHostPtr
RadiusBackend::get6(const isc::dhcp::SubnetID& /*subnet_id*/,
                    const isc::asiolink::IOAddress& /*address*/) const {
    return (ConstHostPtr());
}

ConstHostCollection
RadiusBackend::getAll6(const isc::dhcp::SubnetID& /*subnet_id*/,
                       const isc::asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
RadiusBackend::getAll6(const isc::asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

void
RadiusBackend::add(const HostPtr& /*host*/) {
}

bool
RadiusBackend::del(const SubnetID& /*subnet_id*/,
                   const IOAddress& /*address */) {
    return (false);
}

bool
RadiusBackend::del4(const SubnetID& /*subnet_id*/,
                    const Host::IdentifierType& /*identifier_type*/,
                    const uint8_t* /*identifier_begin*/,
                    const size_t /*identifier_len*/) {
    return (false);
}

bool
RadiusBackend::del6(const SubnetID& /*subnet_id*/,
                    const Host::IdentifierType& /*identifier_type*/,
                    const uint8_t* /*identifier_begin*/,
                    const size_t /*identifier_len*/) {
    return (false);
}

bool
RadiusBackend::setIPReservationsUnique(const bool unique) {
    // This backend does not support the mode in which multiple reservations
    // for the same IP address are created. If selecting this mode is
    // attempted this function returns false to indicate that this is
    // not allowed.
    return (unique);
}

size_t
RadiusBackend::getUnexpected4() const {
    return (impl_->xcount4_);
}

size_t
RadiusBackend::getUnexpected6() const {
    return (impl_->xcount6_);
}

RadiusBackendImpl::RadiusBackendImpl() : xcount4_(0), xcount6_(0) {
}

RadiusBackendImpl::~RadiusBackendImpl() {
}

ConstHostPtr
RadiusBackendImpl::get4(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) {
    if (identifier_type != RadiusImpl::instance().id_type4_) {
        // Not handle by us. Either it is used by host reservations
        // in the configuration or it was left by accident (i.e. forgotten)
        // in host-reservation-identifiers.
        return (ConstHostPtr());
    }
    if (InHook::check()) {
        // get4Any() was called for an entry not (yet) cached.
        return (ConstHostPtr());
    }
    // Unexpected call.
    ++xcount4_;
    ostringstream id;
    for (unsigned i = 0; i < identifier_len; ++i) {
        if (i > 0) {
            id << ':';
        }
        id << hex << setfill('0') << setw(2) << identifier_begin[i];
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_BACKEND_GET4)
        .arg(subnet_id)
        .arg(id.str())
        .arg(Host::getIdentifierName(identifier_type));
    return (ConstHostPtr());
}

ConstHostPtr
RadiusBackendImpl::get6(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) {
    if (identifier_type != RadiusImpl::instance().id_type6_) {
        // Not handle by us. Either it is used by host reservations
        // in the configuration or it was left by accident (i.e. forgotten)
        // in host-reservation-identifiers.
        return (ConstHostPtr());
    }
    if (InHook::check()) {
        // get6Any() was called for an entry not (yet) cached.
        return (ConstHostPtr());
    }
    // Unexpected call.
    ++xcount6_;
    ostringstream id;
    for (unsigned i = 0; i < identifier_len; ++i) {
        if (i > 0) {
            id << ':';
        }
        id << hex << setfill('0') << setw(2) << identifier_begin[i];
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_BACKEND_GET6)
        .arg(subnet_id)
        .arg(id.str())
        .arg(Host::getIdentifierName(identifier_type));
    return (ConstHostPtr());
}

} // namespace radius
} // namespace isc
