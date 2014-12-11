// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease_mgr.h>
#include <hooks/callout_handle.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <map>

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
        /// This method can also be used to pick a prefix. We should not rename
        /// it to pickLease(), because at this early stage there is no concept
        /// of a lease yet. Here it is a matter of selecting one address or
        /// prefix from the defined pool, without going into details who it is
        /// for or who uses it. I thought that pickAddress() is less confusing
        /// than pickResource(), because nobody would immediately know what the
        /// resource means in this context.
        ///
        /// @param subnet next address will be returned from pool of that subnet
        /// @param duid Client's DUID
        /// @param hint client's hint
        ///
        /// @return the next address
        virtual isc::asiolink::IOAddress
        pickAddress(const SubnetPtr& subnet, const DuidPtr& duid,
                    const isc::asiolink::IOAddress& hint) = 0;

        /// @brief Default constructor.
        ///
        /// Specifies which type of leases this allocator will assign
        /// @param pool_type specifies pool type (addresses, temp. addr or prefixes)
        Allocator(Lease::Type pool_type)
            :pool_type_(pool_type) {
        }

        /// @brief virtual destructor
        virtual ~Allocator() {
        }
    protected:

        /// @brief defines pool type allocation
        Lease::Type pool_type_;
    };

    /// defines a pointer to allocator
    typedef boost::shared_ptr<Allocator> AllocatorPtr;

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
        /// @param type - specifies allocation type
        IterativeAllocator(Lease::Type type);

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
    protected:

        /// @brief Returns an address increased by one
        ///
        /// This method works for both IPv4 and IPv6 addresses. For example,
        /// increase 192.0.2.255 will become 192.0.3.0.
        ///
        /// @param addr address to be increased
        /// @return address increased by one
        static isc::asiolink::IOAddress
        increaseAddress(const isc::asiolink::IOAddress& addr);

        /// @brief Returns the next prefix
        ///
        /// This method works for IPv6 addresses only. It increases
        /// specified prefix by a given prefix_len. For example, 2001:db8::
        /// increased by prefix length /32 will become 2001:db9::. This method
        /// is used to iterate over IPv6 prefix pools
        ///
        /// @param prefix prefix to be increased
        /// @param prefix_len length of the prefix to be increased
        /// @return result prefix
        static isc::asiolink::IOAddress
        increasePrefix(const isc::asiolink::IOAddress& prefix,
                       const uint8_t prefix_len);
    };

    /// @brief Address/prefix allocator that gets an address based on a hash
    ///
    /// @todo: This is a skeleton class for now and is missing implementation.
    class HashedAllocator : public Allocator {
    public:

        /// @brief default constructor (does nothing)
        /// @param type - specifies allocation type
        HashedAllocator(Lease::Type type);

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
        /// @param type - specifies allocation type
        RandomAllocator(Lease::Type type);

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

    /// @brief Context information for the DHCPv4 lease allocation.
    ///
    /// This structure holds a set of information provided by the DHCPv4
    /// server to the allocation engine. In particular, it holds the
    /// client identifying information, such as HW address or client
    /// identifier. It also holds the information about the subnet that
    /// the client is connected to.
    ///
    /// This structure is also used to pass  some information from
    /// the allocation engine back to the server, i.e. the old lease
    /// which the client had before the allocation.
    ///
    /// This structure is meant to be extended in the future, if more
    /// information should be passed to the allocation engine. Note
    /// that the big advantage of using the context structure to pass
    /// information to the allocation engine methods is that adding
    /// new information doesn't modify the API of the allocation engine.
    struct Context4 {
        /// @brief Subnet selected for the client by the server.
        SubnetPtr subnet_;

        /// @brief Client identifier from the DHCP message.
        ClientIdPtr clientid_;

        /// @brief HW address from the DHCP message.
        HWAddrPtr hwaddr_;

        /// @brief An address that the client desires.
        ///
        /// If this address is set to 0 it indicates that this address
        /// is unspecified.
        asiolink::IOAddress hint_;

        /// @brief Perform forward DNS update.
        bool fwd_dns_update_;

        /// @brief Perform reverse DNS update.
        bool rev_dns_update_;

        /// @brief Hostname.
        std::string hostname_;

        /// @brief Callout handle associated with the client's message.
        hooks::CalloutHandlePtr callout_handle_;

        /// @brief Indicates if this is a real or fake allocation.
        ///
        /// The real allocation is when the allocation engine is supposed
        /// to make an update in a lease database: create new lease, or
        /// update existing lease.
        bool fake_allocation_;

        /// @brief A pointer to an old lease that the client had before update.
        Lease4Ptr old_lease_;

        /// @brief A pointer to the object identifying host reservations.
        ConstHostPtr host_;

        /// @brief Signals that the allocation should be interrupted.
        ///
        /// This flag is set by the downstream methods called by the
        /// @c AllocEngine::allocateLease4. This flag is set to true to
        /// indicate that an attempt to allocate a lease should be
        /// interrupted.
        bool interrupt_processing_;

        /// @brief Default constructor.
        Context4()
            : subnet_(), clientid_(), hwaddr_(), hint_("0.0.0.0"),
              fwd_dns_update_(false), rev_dns_update_(false),
              hostname_(""), callout_handle_(), fake_allocation_(false),
              old_lease_(), host_(), interrupt_processing_(false) {
        }
    };

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
    /// @param ipv6 specifies if the engine should work for IPv4 or IPv6
    AllocEngine(AllocType engine_type, unsigned int attempts, bool ipv6 = true);

    /// @brief Returns IPv4 lease.
    ///
    /// This method finds the appropriate lease for the client using the
    /// following algorithm:
    /// - If lease exists for the combination of the HW address, client id and
    /// subnet, try to renew a lease and return it.
    /// - If lease exists for the combination of the client id and subnet, try
    /// to renew the lease and return it.
    /// - If client supplied an address hint and this address is available,
    /// allocate the new lease with this address.
    /// - If client supplied an address hint and the lease for this address
    /// exists in the database, return this lease if it is expired.
    /// - Pick new address from the pool and try to allocate it for the client,
    /// if expired lease exists for the picked address, try to reuse this lease.
    ///
    /// When a server should do DNS updates, it is required that allocation
    /// returns the information how the lease was obtained by the allocation
    /// engine. In particular, the DHCP server should be able to check whether
    /// existing lease was returned, or new lease was allocated. When existing
    /// lease was returned, server should check whether the FQDN has changed
    /// between the allocation of the old and new lease. If so, server should
    /// perform appropriate DNS update. If not, server may choose to not
    /// perform the update. The information about the old lease is returned via
    /// @c old_lease parameter. If NULL value is returned, it is an indication
    /// that new lease was allocated for the client. If non-NULL value is
    /// returned, it is an indication that allocation engine reused/renewed an
    /// existing lease.
    ///
    /// @param subnet subnet the allocation should come from
    /// @param clientid Client identifier
    /// @param hwaddr Client's hardware address info
    /// @param hint A hint that the client provided
    /// @param fwd_dns_update Indicates whether forward DNS update will be
    ///        performed for the client (true) or not (false).
    /// @param rev_dns_update Indicates whether reverse DNS update will be
    ///        performed for the client (true) or not (false).
    /// @param hostname A string carrying hostname to be used for DNS updates.
    /// @param fake_allocation Is this real i.e. REQUEST (false) or just picking
    ///        an address for DISCOVER that is not really allocated (true)
    /// @param callout_handle A callout handle (used in hooks). A lease callouts
    ///        will be executed if this parameter is passed.
    /// @param [out] old_lease Holds the pointer to a previous instance of a
    ///        lease. The NULL pointer indicates that lease didn't exist prior
    ///        to calling this function (e.g. new lease has been allocated).
    ///
    /// @return Allocated IPv4 lease (or NULL if allocation failed)
    Lease4Ptr
    allocateLease4(const SubnetPtr& subnet, const ClientIdPtr& clientid,
                   const HWAddrPtr& hwaddr,
                   const isc::asiolink::IOAddress& hint,
                   const bool fwd_dns_update, const bool rev_dns_update,
                   const std::string& hostname, bool fake_allocation,
                   const isc::hooks::CalloutHandlePtr& callout_handle,
                   Lease4Ptr& old_lease);

    /// @brief Renews an DHCPv4 lease.
    ///
    /// This method updates the lease with the information from the provided
    /// context and invokes the lease4_renew callout.
    ///
    /// The address of the lease being renewed is NOT updated.
    ///
    /// @param ctx Message processing context. It holds various information
    /// extracted from the client's message and required to allocate a lease.
    ///
    /// @return Returns renewed lease. Note that the lease is only updated when
    /// it is an actual allocation (not processing DHCPDISCOVER message).
    Lease4Ptr
    renewLease4(const Lease4Ptr& lease, Context4& ctx);

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
    /// @param type lease type (IA, TA or PD)
    /// @param fwd_dns_update A boolean value which indicates that server takes
    ///        responsibility for the forward DNS Update for this lease
    ///        (if true).
    /// @param rev_dns_update A boolean value which indicates that server takes
    ///        responsibility for the reverse DNS Update for this lease
    ///        (if true).
    /// @param hostname A fully qualified domain-name of the client.
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for SOLICIT that is not really allocated (true)
    /// @param callout_handle a callout handle (used in hooks). A lease callouts
    ///        will be executed if this parameter is passed.
    /// @param [out] old_leases Collection to which this function will append
    ///        old leases. Leases are stored in the same order as in the
    ///        collection of new leases, being returned. For newly allocated
    ///        leases (not renewed) the NULL pointers are stored in this
    ///        collection as old leases.
    /// @param hwaddr Hardware address (optional, may be null for Lease6)
    ///
    /// @return Allocated IPv6 leases (may be empty if allocation failed)
    Lease6Collection
    allocateLeases6(const Subnet6Ptr& subnet, const DuidPtr& duid,
                    const uint32_t iaid,
                    const isc::asiolink::IOAddress& hint, Lease::Type type,
                    const bool fwd_dns_update, const bool rev_dns_update,
                    const std::string& hostname, bool fake_allocation,
                    const isc::hooks::CalloutHandlePtr& callout_handle,
                    Lease6Collection& old_leases, const HWAddrPtr& hwaddr);

    /// @brief returns allocator for a given pool type
    /// @param type type of pool (V4, IA, TA or PD)
    /// @throw BadValue if allocator for a given type is missing
    /// @return pointer to allocator handing a given resource types
    AllocatorPtr getAllocator(Lease::Type type);

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    virtual ~AllocEngine();
private:

    /// @brief Creates a lease and inserts it in LeaseMgr if necessary
    ///
    /// Creates a lease based on specified parameters and tries to insert it
    /// into the database. That may fail in some cases, e.g. when there is another
    /// allocation process and we lost a race to a specific lease.
    ///
    /// @param subnet Subnet the lease is allocated from
    /// @param clientid Client identifier
    /// @param hwaddr Client's hardware address
    /// @param addr An address that was selected and is confirmed to be available
    /// @param fwd_dns_update Indicates whether forward DNS update will be
    ///        performed for the client (true) or not (false).
    /// @param rev_dns_update Indicates whether reverse DNS update will be
    ///        performed for the client (true) or not (false).
    /// @param hostname A string carrying hostname to be used for DNS updates.
    /// @param callout_handle a callout handle (used in hooks). A lease callouts
    ///        will be executed if this parameter is passed (and there are callouts
    ///        registered)
    /// @param fake_allocation Is this real i.e. REQUEST (false) or just picking
    ///        an address for DISCOVER that is not really allocated (true)
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///        becomed unavailable)
    Lease4Ptr createLease4(const SubnetPtr& subnet, const DuidPtr& clientid,
                           const HWAddrPtr& hwaddr,
                           const isc::asiolink::IOAddress& addr,
                           const bool fwd_dns_update,
                           const bool rev_dns_update,
                           const std::string& hostname,
                           const isc::hooks::CalloutHandlePtr& callout_handle,
                           bool fake_allocation = false);

    /// @brief Updates the specified lease with the information from a context.
    ///
    /// The context, specified as an argument to this method, holds various
    /// information gathered from the client's message and passed to the
    /// allocation engine. The allocation engine uses this information to make
    /// lease allocation decisions. Some public methods of the allocation engine
    /// requires updating the lease information with the data gathered from the
    /// context, e.g. @c AllocEngine::reuseExpiredLease requires updating the
    /// expired lease with a fresh information from the context to create a
    /// lease to be held for the client.
    ///
    /// Note that this doesn't update the lease address.
    ///
    /// @param [out] lease A pointer to the lease to be updated.
    /// @param ctx A context containing information from the server about the
    /// client and its message.
    void updateLease4Information(const Lease4Ptr& lease,
                                 Context4& ctx) const;

    /// @brief creates a lease and inserts it in LeaseMgr if necessary
    ///
    /// Creates a lease based on specified parameters and tries to insert it
    /// into the database. That may fail in some cases, i.e. when there is another
    /// allocation process and we lost a race to a specific lease.
    ///
    /// @param subnet subnet the lease is allocated from
    /// @param duid client's DUID
    /// @param iaid IAID from the IA_NA container the client sent to us
    /// @param addr an address that was selected and is confirmed to be
    ///        available
    /// @param prefix_len length of the prefix (for PD only)
    ///        should be 128 for other lease types
    /// @param type lease type (IA, TA or PD)
    /// @param fwd_dns_update A boolean value which indicates that server takes
    ///        responsibility for the forward DNS Update for this lease
    ///        (if true).
    /// @param rev_dns_update A boolean value which indicates that server takes
    ///        responsibility for the reverse DNS Update for this lease
    ///        (if true).
    /// @param hostname A fully qualified domain-name of the client.
    /// @param hwaddr Hardware address (optional, may be null for Lease6)
    /// @param callout_handle a callout handle (used in hooks). A lease callouts
    ///        will be executed if this parameter is passed (and there are callouts
    ///        registered)
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for SOLICIT that is not really allocated (true)
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///         became unavailable)
    Lease6Ptr createLease6(const Subnet6Ptr& subnet, const DuidPtr& duid,
                           const uint32_t iaid, const isc::asiolink::IOAddress& addr,
                           const uint8_t prefix_len, const Lease::Type type,
                           const bool fwd_dns_update, const bool rev_dns_update,
                           const std::string& hostname, const HWAddrPtr& hwaddr,
                           const isc::hooks::CalloutHandlePtr& callout_handle,
                           bool fake_allocation = false);

    /// @brief Reuses expired DHCPv4 lease.
    ///
    /// Makes new allocation using an expired lease. The lease is updated with
    /// the information from the provided context. Typically, an expired lease
    /// lease which belonged to one client may be assigned to another client
    /// which asked for the specific address.
    ///
    /// @param expired An old, expired lease.
    /// @param ctx Message processing context. It holds various information
    /// extracted from the client's message and required to allocate a lease.
    ///
    /// @return Updated lease instance.
    /// @throw BadValue if trying to reuse a lease which is still valid or
    /// when the provided parameters are invalid.
    Lease4Ptr reuseExpiredLease(Lease4Ptr& expired, Context4& ctx);

    /// @brief Updates the existing, non expired lease with a information from
    /// the context.
    ///
    /// This method is invoked when the client requests allocation of the
    /// (reserved) lease but there is a lease for this client with a different
    /// address in the database already. In this case the existing lease must
    /// be updated in the database with a new information. In particular,
    /// with a new address.
    ///
    /// This method invokes the lease4_release and lease4_select callouts.
    ///
    /// @param lease A pointer to the lease to be updated.
    /// @param ctx A context to be used to update the lease.
    ///
    /// @return Pointer to the updated lease.
    /// @throw BadValue if the provided parameters are invalid.
    Lease4Ptr replaceClientLease(Lease4Ptr& lease, Context4& ctx);

    /// @brief Replace or renew client's lease.
    ///
    /// This method is ivoked by the @c AllocEngine::allocateLease4 when it
    /// finds that the lease for the particular client already exists in the
    /// database. If the existing lease has the same IP address as the one
    /// that the client should be allocated the existing lease is renewed.
    /// If the client should be allocated a different address, e.g. there
    /// is a static reservation for the client, the existing lease is replaced
    /// with a new one. This method handles both cases.
    ///
    /// @param lease Existing lease.
    /// @param ctx Context holding parameters to be used for the lease
    /// allocation.
    ///
    /// @return Updated lease, or NULL if allocation was unsucessful.
    /// @throw BadValue if specified parameters are invalid.
    Lease4Ptr reallocateClientLease(Lease4Ptr& lease, Context4& ctx);

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
    /// @param prefix_len prefix length (for PD leases)
    ///        Should be 128 for other lease types
    /// @param fwd_dns_update A boolean value which indicates that server takes
    ///        responsibility for the forward DNS Update for this lease
    ///        (if true).
    /// @param rev_dns_update A boolean value which indicates that server takes
    ///        responsibility for the reverse DNS Update for this lease
    ///        (if true).
    /// @param hostname A fully qualified domain-name of the client.
    /// @param callout_handle a callout handle (used in hooks). A lease callouts
    ///        will be executed if this parameter is passed.
    /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
    ///        an address for SOLICIT that is not really allocated (true)
    /// @return refreshed lease
    /// @throw BadValue if trying to recycle lease that is still valid
    Lease6Ptr reuseExpiredLease(Lease6Ptr& expired, const Subnet6Ptr& subnet,
                                const DuidPtr& duid, const uint32_t iaid,
                                uint8_t prefix_len,
                                const bool fwd_dns_update,
                                const bool rev_dns_update,
                                const std::string& hostname,
                                const isc::hooks::CalloutHandlePtr& callout_handle,
                                bool fake_allocation = false);

    /// @brief Updates FQDN data for a collection of leases.
    ///
    /// @param leases Collection of leases for which FQDN data should be
    /// updated.
    /// @param fwd_dns_update Boolean value which indicates whether forward FQDN
    /// update was performed for each lease (true) or not (false).
    /// @param rev_dns_update Boolean value which indicates whether reverse FQDN
    /// update was performed for each lease (true) or not (false).
    /// @param hostname Client hostname associated with a lease.
    /// @param fake_allocation Boolean value which indicates that it is a real
    /// lease allocation, e.g. Request message is processed (false), or address
    /// is just being picked as a result of processing Solicit (true). In the
    /// latter case, the FQDN data should not be updated in the lease database.
    ///
    /// @return Collection of leases with updated FQDN data. Note that returned
    /// collection holds updated FQDN data even for fake allocation.
    Lease6Collection updateFqdnData(const Lease6Collection& leases,
                                    const bool fwd_dns_update,
                                    const bool rev_dns_update,
                                    const std::string& hostname,
                                    const bool fake_allocation);

    /// @brief a pointer to currently used allocator
    ///
    /// For IPv4, there will be only one allocator: TYPE_V4
    /// For IPv6, there will be 3 allocators: TYPE_NA, TYPE_TA, TYPE_PD
    std::map<Lease::Type, AllocatorPtr> allocators_;

    /// @brief number of attempts before we give up lease allocation (0=unlimited)
    unsigned int attempts_;

    // hook name indexes (used in hooks callouts)
    int hook_index_lease4_select_; ///< index for lease4_select hook
    int hook_index_lease6_select_; ///< index for lease6_select hook
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // ALLOC_ENGINE_H
