// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef ALLOC_ENGINE_H
#define ALLOC_ENGINE_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease_mgr.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace isc {
namespace dhcp {

/// An exception that is thrown when allocation module fails (e.g. due to
/// lack of available addresses)
class AllocFailed : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    AllocFailed(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

/// @brief DHCPv4 and DHCPv6 allocation engine
///
/// This class represents DHCP allocation engine. It is responsible
/// for picking subnets, choosing and allocating a lease, extending,
/// renewing, releasing and possibly expiring leases.
///
/// @todo: Does not handle out of leases well
/// @todo: Does not handle out of allocation attempts well
class AllocEngine : public boost::noncopyable {
protected:

    /// @brief base class for all address/prefix allocation algorithms
    ///
    /// This is an abstract class that should not be used directly, but rather
    /// specialized implementations should be used instead.
    class Allocator {
    public:

        /// @brief picks one address out of available pools in a given subnet
        ///
        /// This method returns one address from the available pools in the
        /// specified subnet. It should not check if the address is used or
        /// reserved - AllocEngine will check that and will call pickAddress
        /// again if necessary. The number of times this method is called will
        /// increase as the number of available leases will decrease.
        ///
        /// @param subnet next address will be returned from pool of that subnet
        /// @param duid Client's DUID
        /// @param hint client's hint
        ///
        /// @return the next address
        virtual isc::asiolink::IOAddress
        pickAddress(const SubnetPtr& subnet, const DuidPtr& duid,
                    const isc::asiolink::IOAddress& hint) = 0;

        /// @brief virtual destructor
        virtual ~Allocator() {
        }
    protected:
    };

    /// @brief Address/prefix allocator that iterates over all addresses
    ///
    /// This class implements iterative algorithm that returns all addresses in
    /// a pool iteratively, one after another. Once the last address is reached,
    /// it starts allocating from the beginning of the first pool (i.e. it loops
    /// over).
    class IterativeAllocator : public Allocator {
    public:

        /// @brief default constructor
        ///
        /// Does not do anything
        IterativeAllocator();

        /// @brief returns the next address from pools in a subnet
        ///
        /// @param subnet next address will be returned from pool of that subnet
        /// @param duid Client's DUID (ignored)
        /// @param hint client's hint (ignored)
        /// @return the next address
        virtual isc::asiolink::IOAddress
            pickAddress(const SubnetPtr& subnet,
                        const DuidPtr& duid,
                        const isc::asiolink::IOAddress& hint);
    private:

        /// @brief returns an address by one
        /// @param addr address to be increased
        /// @return address increased by one
        isc::asiolink::IOAddress increaseAddress(const isc::asiolink::IOAddress& addr);

    };

    /// @brief Address/prefix allocator that gets an address based on a hash
    ///
    /// @todo: This is a skeleton class for now and is missing implementation.
    class HashedAllocator : public Allocator {
    public:

        /// @brief default constructor (does nothing)
        HashedAllocator();

        /// @brief returns an address based on hash calculated from client's DUID.
        ///
        /// @todo: Implement this method
        ///
        /// @param subnet an address will be picked from pool of that subnet
        /// @param duid Client's DUID
        /// @param hint a hint (last address that was picked)
        /// @return selected address
        virtual isc::asiolink::IOAddress pickAddress(const SubnetPtr& subnet,
                                                     const DuidPtr& duid,
                                                     const isc::asiolink::IOAddress& hint);
    };

    /// @brief Random allocator that picks address randomly
    ///
    /// @todo: This is a skeleton class for now and is missing implementation.
    class RandomAllocator : public Allocator {
    public:

        /// @brief default constructor (does nothing)
        RandomAllocator();

        /// @brief returns an random address from pool of specified subnet
        ///
        /// @todo: Implement this method
        ///
        /// @param subnet an address will be picked from pool of that subnet
        /// @param duid Client's DUID (ignored)
        /// @param hint the last address that was picked (ignored)
        /// @return a random address from the pool
        virtual isc::asiolink::IOAddress
        pickAddress(const SubnetPtr& subnet, const DuidPtr& duid,
                    const isc::asiolink::IOAddress& hint);
    };

    public:

    /// @brief specifies allocation type
    typedef enum {
        ALLOC_ITERATIVE, // iterative - one address after another
        ALLOC_HASHED,    // hashed - client's DUID/client-id is hashed
        ALLOC_RANDOM     // random - an address is randomly selected
    } AllocType;


    /// @brief Default constructor.
    ///
    /// Instantiates necessary services, required to run DHCPv6 server.
    /// In particular, creates IfaceMgr that will be responsible for
    /// network interaction. Will instantiate lease manager, and load
    /// old or create new DUID.
    ///
    /// @param engine_type selects allocation algorithm
    /// @param attempts number of attempts for each lease allocation before
    ///        we give up (0 means unlimited)
    AllocEngine(AllocType engine_type, unsigned int attempts);

    /// @brief Allocates an IPv4 lease
    ///
    /// This method uses currently selected allocator to pick an address from
    /// specified subnet, creates a lease for that address and then inserts
    /// it into LeaseMgr (if this allocation is not fake).
    ///
    /// @param subnet subnet the allocation should come from
    /// @param clientid Client identifier
    /// @param hwaddr client's hardware address info
    /// @param hint a hint that the client provided
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for DISCOVER that is not really allocated (true)
    /// @return Allocated IPv4 lease (or NULL if allocation failed)
    Lease4Ptr
    allocateAddress4(const SubnetPtr& subnet,
                     const ClientIdPtr& clientid,
                     const HWAddrPtr& hwaddr,
                     const isc::asiolink::IOAddress& hint,
                     bool fake_allocation);

    /// @brief Renews a IPv4 lease
    ///
    /// Since both request and renew are implemented in DHCPv4 as the sending of
    /// a REQUEST packet, it is difficult to easily distinguish between those
    /// cases. Therefore renew for DHCPv4 is done in the allocation engine.
    /// This method is also used when client crashed/rebooted and tries
    /// to get a new lease. It thinks that it gets a new lease, but in fact
    /// we are only renewing the still valid lease for that client.
    ///
    /// @param subnet subnet the client is attached to
    /// @param clientid client identifier
    /// @param hwaddr client's hardware address
    /// @param lease lease to be renewed
    /// @param renewed lease (typically the same passed as lease parameter)
    ///        or NULL if the lease cannot be renewed
    Lease4Ptr
    renewLease4(const SubnetPtr& subnet,
                const ClientIdPtr& clientid,
                const HWAddrPtr& hwaddr,
                const Lease4Ptr& lease,
                bool fake_allocation /* = false */);

    /// @brief Allocates an IPv6 lease
    ///
    /// This method uses currently selected allocator to pick an address from
    /// specified subnet, creates a lease for that address and then inserts
    /// it into LeaseMgr (if this allocation is not fake).
    ///
    /// @param subnet subnet the allocation should come from
    /// @param duid Client's DUID
    /// @param iaid iaid field from the IA_NA container that client sent
    /// @param hint a hint that the client provided
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for SOLICIT that is not really allocated (true)
    /// @return Allocated IPv6 lease (or NULL if allocation failed)
    Lease6Ptr
    allocateAddress6(const Subnet6Ptr& subnet,
                     const DuidPtr& duid,
                     uint32_t iaid,
                     const isc::asiolink::IOAddress& hint,
                     bool fake_allocation);

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    virtual ~AllocEngine();
private:

    /// @brief Creates a lease and inserts it in LeaseMgr if necessary
    ///
    /// Creates a lease based on specified parameters and tries to insert it
    /// into the database. That may fail in some cases, e.g. when there is another
    /// allocation process and we lost a race to a specific lease.
    ///
    /// @param subnet subnet the lease is allocated from
    /// @param clientid client identifier
    /// @param hwaddr client's hardware address
    /// @param addr an address that was selected and is confirmed to be available
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for DISCOVER that is not really allocated (true)
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///        becomed unavailable)
    Lease4Ptr createLease4(const SubnetPtr& subnet, const DuidPtr& clientid,
                           const HWAddrPtr& hwaddr,
                           const isc::asiolink::IOAddress& addr,
                           bool fake_allocation = false);

    /// @brief creates a lease and inserts it in LeaseMgr if necessary
    ///
    /// Creates a lease based on specified parameters and tries to insert it
    /// into the database. That may fail in some cases, i.e. when there is another
    /// allocation process and we lost a race to a specific lease.
    ///
    /// @param subnet subnet the lease is allocated from
    /// @param duid client's DUID
    /// @param iaid IAID from the IA_NA container the client sent to us
    /// @param addr an address that was selected and is confirmed to be available
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for SOLICIT that is not really allocated (true)
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///        becomed unavailable)
    Lease6Ptr createLease6(const Subnet6Ptr& subnet, const DuidPtr& duid,
                           uint32_t iaid, const isc::asiolink::IOAddress& addr,
                           bool fake_allocation = false);

    /// @brief Reuses expired IPv4 lease
    ///
    /// Updates existing expired lease with new information. Lease database
    /// is updated if this is real (i.e. REQUEST, fake_allocation = false), not
    /// dummy allocation request (i.e. DISCOVER, fake_allocation = true).
    ///
    /// @param expired old, expired lease
    /// @param subnet subnet the lease is allocated from
    /// @param clientid client identifier
    /// @param hwaddr client's hardware address
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for DISCOVER that is not really allocated (true)
    /// @return refreshed lease
    /// @throw BadValue if trying to recycle lease that is still valid
    Lease4Ptr reuseExpiredLease(Lease4Ptr& expired, const SubnetPtr& subnet,
                                const ClientIdPtr& clientid,
                                const HWAddrPtr& hwaddr,
                                bool fake_allocation = false);

    /// @brief Reuses expired IPv6 lease
    ///
    /// Updates existing expired lease with new information. Lease database
    /// is updated if this is real (i.e. REQUEST, fake_allocation = false), not
    /// dummy allocation request (i.e. SOLICIT, fake_allocation = true).
    ///
    /// @param expired old, expired lease
    /// @param subnet subnet the lease is allocated from
    /// @param duid client's DUID
    /// @param iaid IAID from the IA_NA container the client sent to us
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for SOLICIT that is not really allocated (true)
    /// @return refreshed lease
    /// @throw BadValue if trying to recycle lease that is still valid
    Lease6Ptr reuseExpiredLease(Lease6Ptr& expired, const Subnet6Ptr& subnet,
                                const DuidPtr& duid, uint32_t iaid,
                                bool fake_allocation = false);

    /// @brief a pointer to currently used allocator
    boost::shared_ptr<Allocator> allocator_;

    /// @brief number of attempts before we give up lease allocation (0=unlimited)
    unsigned int attempts_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // ALLOC_ENGINE_H
