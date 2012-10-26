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

#include <boost/noncopyable.hpp>
#include <dhcp/duid.h>
#include <dhcp/subnet.h>
#include <asiolink/io_address.h>
#include <dhcp/lease_mgr.h>
#include <iostream>

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
        virtual isc::asiolink::IOAddress
            pickAddress(const Subnet6Ptr& subnet,
                        const DuidPtr& duid,
                        const isc::asiolink::IOAddress& hint) = 0;
    protected:
        /// @brief protected constructor
        ///
        /// Prevents anyone from attempting to instantiate Allocator objects
        /// directly. Derived classes should be used instead.
        Allocator() {
        }
    };

    /// @brief Address/prefix allocator that iterates over all addresses
    ///
    /// This class implements iterative algorithm that returns all addresses in
    /// a pool iteratively, one after another.
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
            pickAddress(const Subnet6Ptr& subnet,
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
        virtual isc::asiolink::IOAddress pickAddress(const Subnet6Ptr& subnet,
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
        pickAddress(const Subnet6Ptr& subnet, const DuidPtr& duid,
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

    /// @brief Allocates an IPv6 lease
    ///
    /// This method uses currently selected allocator to pick an address from
    /// specified subnet, creates a lease for that address and then inserts
    /// it into LeaseMgr (if this allocation is not fake).
    ///
    /// @param subnet subnet the allocation should come from
    /// @param duid Client'd DUID
    /// @param iaid iaid field from the IA_NA container that client sent
    /// @param hint a hint that the client provided
    /// @param fake is this real (REQUEST) or fake (SOLICIT) allocation
    /// @return Allocated IPv6 lease (or NULL if allocation failed)
    Lease6Ptr
    allocateAddress6(const Subnet6Ptr& subnet,
                     const DuidPtr& duid,
                     uint32_t iaid,
                     const isc::asiolink::IOAddress& hint,
                     bool fake);

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    virtual ~AllocEngine();
private:

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
    /// @param fake is this SOLICIT (true) or a real/REQUEST allocation (false)?
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///        becomed unavailable)
    Lease6Ptr createLease(const Subnet6Ptr& subnet, const DuidPtr& duid,
                          uint32_t iaid, const isc::asiolink::IOAddress& addr,
                          bool fake = false);

    /// @brief a pointer to currently used allocator
    Allocator* allocator_;

    /// @brief number of attempts before we give up lease allocation (0=unlimited)
    unsigned int attempts_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP6_SRV_H
