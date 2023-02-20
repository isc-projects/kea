// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <concrete_lease_mgr.h>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace dhcp {
namespace test {

ConcreteLeaseMgr::ConcreteLeaseMgr(const DatabaseConnection::ParameterMap&)
    : TrackingLeaseMgr() {
}

ConcreteLeaseMgr::~ConcreteLeaseMgr() {
}

bool
ConcreteLeaseMgr::addLease(const Lease4Ptr&) {
    return (false);
}

bool
ConcreteLeaseMgr::addLease(const Lease6Ptr&) {
    return (false);
}

Lease4Ptr
ConcreteLeaseMgr::getLease4(const IOAddress&) const {
    return (Lease4Ptr());
}

Lease4Collection
ConcreteLeaseMgr::getLease4(const HWAddr&) const {
    return (Lease4Collection());
}

Lease4Ptr
ConcreteLeaseMgr::getLease4(const HWAddr&, SubnetID) const {
    return (Lease4Ptr());
}

Lease4Collection
ConcreteLeaseMgr::getLease4(const ClientId&) const {
    return (Lease4Collection());
}

Lease4Ptr
ConcreteLeaseMgr::getLease4(const ClientId&, SubnetID) const {
    return (Lease4Ptr());
}

Lease4Collection
ConcreteLeaseMgr::getLeases4(SubnetID) const {
    return (Lease4Collection());
}

Lease4Collection
ConcreteLeaseMgr::getLeases4(const std::string&) const {
    return (Lease4Collection());
}

Lease4Collection
ConcreteLeaseMgr::getLeases4() const {
    return (Lease4Collection());
}

Lease4Collection
ConcreteLeaseMgr::getLeases4(const IOAddress& /* lower_bound_address */,
                             const LeasePageSize& /* page_size */) const {
    return (Lease4Collection());
}

Lease6Ptr
ConcreteLeaseMgr::getLease6(Lease::Type /* not used yet */,
                            const IOAddress&) const {
    return (Lease6Ptr());
}

Lease6Collection
ConcreteLeaseMgr::getLeases6(Lease::Type /* not used yet */,
                             const DUID&, uint32_t) const {
    return (leases6_);
}

Lease6Collection
ConcreteLeaseMgr::getLeases6(Lease::Type /* not used yet */,
                             const DUID&, uint32_t, SubnetID) const {
    return (leases6_);
}

Lease6Collection
ConcreteLeaseMgr::getLeases6(const DUID&) const {
    return (leases6_);
}

Lease6Collection
ConcreteLeaseMgr::getLeases6(SubnetID) const {
    return (Lease6Collection());
}

Lease6Collection
ConcreteLeaseMgr::getLeases6(const std::string&) const {
    return (Lease6Collection());
}

Lease6Collection
ConcreteLeaseMgr::getLeases6() const {
    return (Lease6Collection());
}

Lease6Collection
ConcreteLeaseMgr::getLeases6(const IOAddress& /* lower_bound_address */,
                             const LeasePageSize& /* page_size */) const {
    return (Lease6Collection());
};

void
ConcreteLeaseMgr::getExpiredLeases6(Lease6Collection&, const size_t) const {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getExpiredLeases6 is not"
              " implemented");
}

void
ConcreteLeaseMgr::getExpiredLeases4(Lease4Collection&, const size_t) const {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getExpiredLeases4 is not"
              " implemented");
}

void
ConcreteLeaseMgr::updateLease4(const Lease4Ptr&) {}

void
ConcreteLeaseMgr::updateLease6(const Lease6Ptr&) {}

bool
ConcreteLeaseMgr::deleteLease(const Lease4Ptr&) {
    return (false);
}

bool
ConcreteLeaseMgr::deleteLease(const Lease6Ptr&) {
    return (false);
}

uint64_t
ConcreteLeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::deleteExpir§edReclaimedLeases4"
              " is not implemented");
}

uint64_t
ConcreteLeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::deleteExpiredReclaimedLeases6"
              " is not implemented");
}

size_t
ConcreteLeaseMgr::wipeLeases4(const SubnetID&) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::wipeLeases4 not implemented");
}

size_t
ConcreteLeaseMgr::wipeLeases6(const SubnetID&) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::wipeLeases6 not implemented");
}

std::string
ConcreteLeaseMgr::checkLimits4(isc::data::ConstElementPtr const& /* user_context */) const {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::checkLimits4() not implemented");
}

std::string
ConcreteLeaseMgr::checkLimits6(isc::data::ConstElementPtr const& /* user_context */) const {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::checkLimits6() not implemented");
}

bool
ConcreteLeaseMgr::isJsonSupported() const {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::isJsonSupported() not implemented");
}

size_t
ConcreteLeaseMgr::getClassLeaseCount(const ClientClass& /* client_class */,
                                     const Lease::Type& /* ltype = Lease::TYPE_V4 */) const {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getClassLeaseCount() not implemented");
}

void
ConcreteLeaseMgr::recountClassLeases4() {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::recountClassLeases4() not implemented");
}

void
ConcreteLeaseMgr::recountClassLeases6() {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::recountClassLeases6() not implemented");
}

void
ConcreteLeaseMgr::clearClassLeaseCounts() {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::clearClassLeaseCounts() not implemented");
}

void
ConcreteLeaseMgr::deleteExtendedInfo6(const IOAddress& addr) {
    auto relay_id_it = relay_id6_.begin();
    while (relay_id_it != relay_id6_.end()) {
        if ((*relay_id_it)->lease_addr_ == addr) {
            relay_id_it = relay_id6_.erase(relay_id_it);
        } else {
            ++relay_id_it;
        }
    }
    auto remote_id_it = remote_id6_.begin();
    while (remote_id_it != remote_id6_.end()) {
        if ((*remote_id_it)->lease_addr_ == addr) {
            remote_id_it = remote_id6_.erase(remote_id_it);
        } else {
            ++remote_id_it;
        }
    }
}

void
ConcreteLeaseMgr::addRelayId6(const IOAddress& lease_addr,
                              const vector<uint8_t>& relay_id) {
    Lease6ExtendedInfoPtr ex_info;
    ex_info.reset(new Lease6ExtendedInfo(lease_addr, relay_id));
    relay_id6_.push_back(ex_info);
}

void
ConcreteLeaseMgr::addRemoteId6(const IOAddress& lease_addr,
                               const vector<uint8_t>& remote_id) {
    Lease6ExtendedInfoPtr ex_info;
    ex_info.reset(new Lease6ExtendedInfo(lease_addr, remote_id));
    remote_id6_.push_back(ex_info);
}

Lease4Collection
ConcreteLeaseMgr::getLeases4ByRelayId(const OptionBuffer& /* relay_id */,
                                      const IOAddress& /* lower_bound_address */,
                                      const LeasePageSize& /* page_size */,
                                      const time_t& /* qry_start_time = 0 */,
                                      const time_t& /* qry_end_time = 0 */) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases4ByRelayId not implemented");
}

Lease4Collection
ConcreteLeaseMgr::getLeases4ByRemoteId(const OptionBuffer& /* remote_id */,
                                       const IOAddress& /* lower_bound_address */,
                                       const LeasePageSize& /* page_size */,
                                       const time_t& /* qry_start_time = 0 */,
                                       const time_t& /* qry_end_time = 0 */) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases4ByRemoteId not implemented");
}

Lease6Collection
ConcreteLeaseMgr::getLeases6ByRelayId(const DUID& /* relay_id */,
                                      const IOAddress& /* link_addr */,
                                      uint8_t /* link_len */,
                                      const IOAddress& /* lower_bound_address */,
                                      const LeasePageSize& /* page_size */) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases6ByRelayId not implemented");
}

Lease6Collection
ConcreteLeaseMgr::getLeases6ByRemoteId(const OptionBuffer& /* remote_id */,
                                       const IOAddress& /* link_addr */,
                                       uint8_t /* link_len */,
                         const IOAddress& /* lower_bound_address */,
                                       const LeasePageSize& /* page_size*/) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases6ByRemoteId not implemented");
}

Lease6Collection
ConcreteLeaseMgr::getLeases6ByLink(const IOAddress& /* link_addr */,
                                   uint8_t /* link_len */,
                                   const IOAddress& /* lower_bound_address */,
                                   const LeasePageSize& /* page_size */) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::getLeases6ByLink not implemented");
}

size_t
ConcreteLeaseMgr::buildExtendedInfoTables6(bool /* update */,
                                           bool /* current */) {
    isc_throw(isc::NotImplemented, "ConcreteLeaseMgr:buildExtendedInfoTables6 not implemented");
}

void
ConcreteLeaseMgr::writeLeases4(const std::string&) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::writeLeases4() not implemented");
}

void
ConcreteLeaseMgr::writeLeases6(const std::string&) {
    isc_throw(NotImplemented, "ConcreteLeaseMgr::writeLeases6() not implemented");
}

std::string
ConcreteLeaseMgr::getType() const {
    return (std::string("concrete"));
}

std::string
ConcreteLeaseMgr::getName() const {
    return (std::string("concrete"));
}

std::string
ConcreteLeaseMgr::getDescription() const {
    return (std::string("This is a dummy concrete backend implementation."));
}

std::pair<uint32_t, uint32_t>
ConcreteLeaseMgr::getVersion() const {
    return (make_pair(uint32_t(0), uint32_t(0)));
}

void
ConcreteLeaseMgr::commit() {
}

void
ConcreteLeaseMgr::rollback() {
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
