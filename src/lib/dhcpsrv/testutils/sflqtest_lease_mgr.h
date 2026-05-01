// Copyright (C) 2023-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SFLQ_TEST_LEASE_MGR_H
#define SFLQ_TEST_LEASE_MGR_H

#include <config.h>

#include <database/database_connection.h>
#include <dhcpsrv/testutils/concrete_lease_mgr.h>
#include <list>
#include <utility>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Mock Shared FLQ pool and lease data.
///
/// Takes the place of flq_poolX and free_leaseX tables.
struct SflqPool {

    /// @brief Constructor.
    ///
    /// @param start_address first address in the pool.
    /// @param last_address last address in the pool.
    /// @param subnet_id id of the subnet to which the pool belongs.
    /// @param recreate when true, the pool is recreated if it already exits.
    /// @param lease_type Lease::TYPE_V4, TYPE_NA, or TYPE_PD
    /// @param delegated_len bit length of the address/prefix to be leases. For
    /// TYPE_NA this parameter should be 128.
    SflqPool(asiolink::IOAddress start_address_,
             asiolink::IOAddress end_address_,
             SubnetID subnet_id_,
             Lease::Type lease_type = Lease::TYPE_V4,
             uint8_t delegated_len  = 1);

    /// @brief Destructor.
    ~SflqPool(){};

    /// @brief Refills the free lease list with all leases in the pool.
    void repopulateFreeLeases();

    /// @brief Removes and returns an address from the front of the free
    /// address list.
    ///
    /// @return An address or '0.0.0.0'/'::' is there are none.
    asiolink::IOAddress popFreeAddress();

    /// @brief Convenience function that returns a pool-appropriate
    /// empty IOAddress.
    ///
    /// @return IPV4_ZERO_ADDRESS() if pool leas type is TYPE_V4,
    /// IPV6_ZERO_ADDRESS() otherwise.
    asiolink::IOAddress zeroAddress();

    /// @brief First address in the pool.
    asiolink::IOAddress start_address_;

    /// @brief Last address in the pool.
    asiolink::IOAddress end_address_;

    /// @brief Id of the subnet to which the pool belongs.
    SubnetID subnet_id_;

    /// @brief Lease type of pool.
    Lease::Type lease_type_;

    /// @brief Length of the address/prefix to be leases.
    uint8_t delegated_len_;

    /// @brief List of free addresses in the pool.
    std::list<asiolink::IOAddress> free_addresses_;

};

/// @brief A pointer to a SflqPool.
typedef boost::shared_ptr<SflqPool> SflqPoolPtr;

/// @brief A list of SflqPoolPtrs.
typedef std::list<SflqPoolPtr> SflqPoolCollection;

// This is a concrete implementation of a Lease database.  It does not do
// anything useful and is used for abstract LeaseMgr class testing.
class SflqTestLeaseMgr : public ConcreteLeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    SflqTestLeaseMgr(const db::DatabaseConnection::ParameterMap&);

    /// @brief Destructor
    virtual ~SflqTestLeaseMgr();

    /// @brief Factory for creating a SflqTestLeaseMgr.
    ///
    /// The only required parameters are "type=sflqtest" adn "universe=4"
    /// or "universe=6".
    ///
    /// @param params Connection parameters for creating the manager.
    static TrackingLeaseMgrPtr factory(const db::DatabaseConnection
                                             ::ParameterMap& params);

    /// @brief Creates a v4 SFLQ Pool
    ///
    /// @param start_address first address in the pool.
    /// @param last_address last address in the pool.
    /// @param subnet_id id of the subnet to which the pool belongs.
    /// @param recreate when true, the pool is recreated if it already exits.
    ///
    /// @return True if the pool is (re)created, false it if already exists.
    virtual bool sflqCreateFlqPool4(asiolink::IOAddress start_address,
                                    asiolink::IOAddress end_address,
                                    SubnetID subnet_id, bool recreate = false)
                                    override;

    /// @brief Finds a free V4 address within the given pool range.
    ///
    /// @param start_address first address in the pool.
    /// @param last_address last address in the pool.
    ///
    /// @return A free V4 address or IOAddress::IPV4_ZERO_ADDRESS().
    virtual asiolink::IOAddress sflqPickFreeLease4(asiolink::IOAddress start_address,
                                                   asiolink::IOAddress end_address)
                                                   override;

    /// @brief Calls stored procedure to create an SFLQ pool for v6.
    ///
    /// @param start_address first address/prefix in the pool.
    /// @param last_address last address/prefix in the pool.
    /// @param lease_type TYPE_NA or TYPE_PD.
    /// @param delegated_len bit length of the address/prefix to be leases. For
    /// TYPE_NA this parameter should be 128.
    /// @param subnet_id id of the subnet to which the pool belongs.
    /// @param recreate when true, the pool is recreated if it already exits.
    ///
    /// @return True if the pool is (re)created, false it if already exists.
    virtual bool sflqCreateFlqPool6(asiolink::IOAddress start_address,
                                    asiolink::IOAddress end_address,
                                    Lease::Type lease_type, uint8_t delegated_len,
                                    SubnetID subnet_id, bool recreate = false)
                                    override;

    /// @brief Finds a free V6 address/prefix within the given pool range.
    ///
    /// @param start_address first address in the pool.
    /// @param last_address last address in the pool.
    ///
    /// @return A free V6 address/prefix or IOAddress::IPV6_ZERO_ADDRESS().
    virtual asiolink::IOAddress sflqPickFreeLease6(asiolink::IOAddress start_address,
                                                   asiolink::IOAddress end_address)
                                                   override;

    /// @brief Finds an SflqPool in the list of SflqPools
    ///
    /// @param start_address first address in the pool.
    /// @param last_address last address in the pool.
    ///
    /// @return Pointer to the desired pool are an empty pointer.
    SflqPoolPtr findPool(asiolink::IOAddress start_address, asiolink::IOAddress end_address);

    /// @brief Refills the free lease lists for all SFLQ pools.
    void repopulateFlqPools();

    /// @brief Returns backend type.
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const override;

    /// @brief Collection of SFLQ pools that have been created.
    SflqPoolCollection sflq_pools_;
};

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SFLQ_TEST_LEASE_MGR_H
