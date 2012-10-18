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

class AllocEngine : public boost::noncopyable {
protected:

    class Allocator {
    public:
        virtual isc::asiolink::IOAddress
            pickAddress(const Subnet6Ptr& subnet,
                        const DuidPtr& duid,
                        const isc::asiolink::IOAddress& hint) = 0;
    protected:
        Allocator() {
        }
    };

    class IterativeAllocator : public Allocator {
    public:
        IterativeAllocator();
        virtual isc::asiolink::IOAddress
            pickAddress(const Subnet6Ptr& subnet,
                        const DuidPtr& duid,
                        const isc::asiolink::IOAddress& hint);
    private:
        isc::asiolink::IOAddress increaseAddress(const isc::asiolink::IOAddress& addr);

    };

#if 0
    class HashedAllocator {
    public:
        IterativeAllocator(unsigned int attempts);
        virtual isc::asiolink::IOAddress allocateAddress(const Subnet6Ptr& subnet,
                                                         const DuidPtr& duid,
                                                         const DUIOAddress& hint);
    }

    class RandomAllocator() {
    public:
        IterativeAllocator(unsigned int attempts);
        virtual isc::asiolink::IOAddress
        allocateAddress(const Subnet6Ptr& subnet,
                        const DuidPtr& duid,
                        const DUIOAddress& hint);
    }
#endif

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
    AllocEngine(AllocType engine_type, unsigned int attempts);

    Lease6Ptr
    allocateAddress6(const Subnet6Ptr& subnet,
                     const DuidPtr& duid,
                     uint32_t iaid,
                     const isc::asiolink::IOAddress& hint);

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    virtual ~AllocEngine();
private:
    isc::asiolink::IOAddress
    allocateAddress(const Subnet6Ptr& subnet,
                    const DuidPtr& duid,
                    const isc::asiolink::IOAddress& hint);

    Lease6Ptr createLease(const Subnet6Ptr& subnet,
                          const DuidPtr& duid,
                          uint32_t iaid,
                          const isc::asiolink::IOAddress& addr);

    Allocator* allocator_;

    unsigned int attempts_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP6_SRV_H
