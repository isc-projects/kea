// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/option6_ia.h>
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
/// This class represents a DHCP allocation engine. It is responsible
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
    /// This class implements an iterative algorithm that returns all addresses in
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

        /// @brief Returns the next prefix
        ///
        /// This method works for IPv6 addresses only. It increases the
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
    /// @todo: This is a skeleton class for now and is missing an implementation.
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
    /// @todo: This is a skeleton class for now and is missing an implementation.
    class RandomAllocator : public Allocator {
    public:

        /// @brief default constructor (does nothing)
        /// @param type - specifies allocation type
        RandomAllocator(Lease::Type type);

        /// @brief returns a random address from pool of specified subnet
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

    /// @brief Constructor.
    ///
    /// Instantiates necessary services, required to run DHCP server.
    /// In particular, creates IfaceMgr that will be responsible for
    /// network interaction. Will instantiate lease manager, and load
    /// old or create new DUID.
    ///
    /// @param engine_type selects allocation algorithm
    /// @param attempts number of attempts for each lease allocation before
    ///        we give up (0 means unlimited)
    /// @param ipv6 specifies if the engine should work for IPv4 or IPv6
    AllocEngine(AllocType engine_type, unsigned int attempts, bool ipv6 = true);

    /// @brief Destructor.
    virtual ~AllocEngine() { }

    /// @brief Returns allocator for a given pool type
    ///
    /// @param type type of pool (V4, IA, TA or PD)
    /// @throw BadValue if allocator for a given type is missing
    /// @return pointer to allocator handling a given resource types
    AllocatorPtr getAllocator(Lease::Type type);

private:

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

public:

    /// @brief Defines a single hint (an address + prefix-length).
    ///
    /// This is an entry that represents what the client had requested,
    /// either an address or a prefix. Prefix length is 128 for regular
    /// addresses.
    typedef std::pair<isc::asiolink::IOAddress, uint8_t> HintType;

    /// @brief Container for client's hints.
    typedef std::vector<HintType> HintContainer;

    /// @brief Context information for the DHCPv6 leases allocation.
    ///
    /// This structure holds a set of information provided by the DHCPv6
    /// server to the allocation engine. In particular, it holds the
    /// client identifying information, such as HW address or client
    /// identifier. It also holds the information about the subnet that
    /// the client is connected to.
    ///
    /// This structure is also used to pass some information from
    /// the allocation engine back to the server, i.e. the old leases
    /// which the client had before the allocation.
    ///
    /// This structure is expected to be common for a single client, even
    /// if multiple IAs are used. Some of the fields will need to be
    /// updated for every call (there's a separate call to the allocation
    /// engine for each IA option).
    ///
    /// This structure is meant to be extended in the future, if more
    /// information should be passed to the allocation engine. Note
    /// that the big advantage of using the context structure to pass
    /// information to the allocation engine methods is that adding
    /// new information doesn't modify the API of the allocation engine.
    struct ClientContext6 {
        /// @brief Subnet selected for the client by the server.
        Subnet6Ptr subnet_;

        /// @brief Client identifier
        DuidPtr duid_;

        /// @brief iaid IAID field from IA_NA or IA_PD that is being processed
        uint32_t iaid_;

        /// @brief Lease type (IA or PD)
        Lease::Type type_;

        /// @brief Hardware/MAC address (if available, may be NULL)
        HWAddrPtr hwaddr_;

        /// @brief client's hints
        ///
        /// There will typically be just one address, but the protocol allows
        /// more than one address or prefix for each IA container.
        HintContainer hints_;

        /// @brief A boolean value which indicates that server takes
        ///        responsibility for the forward DNS Update for this lease
        ///        (if true).
        bool fwd_dns_update_;

        /// @brief A boolean value which indicates that server takes
        ///        responsibility for the reverse DNS Update for this lease
        ///        (if true).
        bool rev_dns_update_;

        /// @brief Hostname.
        ///
        /// The server retrieves the hostname from the Client FQDN option,
        /// Hostname option or the host reservation record for the client.
        std::string hostname_;

        /// @brief Callout handle associated with the client's message.
        hooks::CalloutHandlePtr callout_handle_;

        /// @brief Indicates if this is a real or fake allocation.
        ///
        /// The real allocation is when the allocation engine is supposed
        /// to make an update in a lease database: create new lease, or
        /// update existing lease.
        bool fake_allocation_;

        /// @brief A pointer to any old leases that the client had before update
        ///        but are no longer valid after the update/allocation.
        ///
        /// This collection is typically empty, except cases when we are doing
        /// address reassignment, e.g. because there is a host reservation that
        /// gives this address to someone else, so we had to return the address,
        /// and give a new one to this client.
        Lease6Collection old_leases_;

        /// @brief A pointer to any leases that have changed FQDN information.
        ///
        /// This list may contain old versions of the leases that are still
        /// valid. In particular, it will contain a lease if the client's
        /// FQDN has changed.
        Lease6Collection changed_leases_;

        /// @brief A pointer to the object identifying host reservations.
        ///
        /// May be NULL if there are no reservations.
        ConstHostPtr host_;

        /// @brief A pointer to the client's message
        ///
        /// This is used exclusively for hook purposes.
        Pkt6Ptr query_;

        /// @brief A pointer to the IA_NA/IA_PD option to be sent in response
        Option6IAPtr ia_rsp_;


        /// @brief Specifies whether new leases in Renew/Rebind are allowed
        ///
        /// This field controls what to do when renewing or rebinding client
        /// does not have any leases. RFC3315 and the stateful-issues draft do
        /// not specify it and it is left up to the server configuration policy.
        /// False (the default) means that the client will not get any new
        /// unreserved leases if his existing leases are no longer suitable.
        /// True means that the allocation engine will do its best to assign
        /// something.
        bool allow_new_leases_in_renewals_;

        /// @brief Default constructor.
        ClientContext6();

        /// @brief Constructor with parameters.
        ///
        /// Note that several less frequently used parameters (callout_handle,
        /// old_leases, host) fields are not set. They should be set explicitly,
        /// if needed.
        ///
        /// @param subnet subnet the allocation should come from
        /// @param duid Client's DUID
        /// @param iaid iaid field from the IA_NA container that client sent
        /// @param hint a hint that the client provided
        /// @param type lease type (IA, TA or PD)
        /// @param fwd_dns A boolean value which indicates that server takes
        ///        responsibility for the forward DNS Update for this lease
        ///        (if true).
        /// @param rev_dns A boolean value which indicates that server takes
        ///        responsibility for the reverse DNS Update for this lease
        ///        (if true).
        /// @param hostname A fully qualified domain-name of the client.
        /// @param fake_allocation is this real i.e. REQUEST (false) or just picking
        ///        an address for SOLICIT that is not really allocated (true)
        ClientContext6(const Subnet6Ptr& subnet, const DuidPtr& duid,
                       const uint32_t iaid, const isc::asiolink::IOAddress& hint,
                       const Lease::Type type, const bool fwd_dns, const bool
                       rev_dns, const std::string& hostname, const bool
                       fake_allocation);
    };

    /// @brief Allocates IPv6 leases for a given IA container
    ///
    /// This method uses the currently selected allocator to pick allocatable
    /// resources (i.e. addresses or prefixes) from specified subnet, creates
    /// a lease (one or more, if needed) for that resources and then inserts
    /// it into LeaseMgr (if this allocation is not fake, i.e. this is not a
    /// response to SOLICIT).
    ///
    /// This method uses host reservation if ctx.host_ is set. The easy way to
    /// set it is to call @ref isc::dhcp::AllocEngine::findReservation(ctx).
    /// The host reservation is convenient, but incurs performance penalty,
    /// so it can be tweaked on a per subnet basis. There are three possible modes:
    /// 1. disabled (no host reservation at all). This is the most performant one
    /// as the code can skip all checks;
    /// 2. out-of-pool (only reservations that are outside
    /// of the dynamic pools are allowed. This is a compromise - it requires
    /// a sysadmin to be more careful with the reservations, but the code
    /// can skip reservation checks while managing in-pool addresses);
    /// 3. in-pool (which also allow out-of-pool; this is the most flexible
    /// mode, but it means that the allocation engine has to do reservation
    /// checks on every lease, even those dynamically assigned, which degrades
    /// performance).
    ///
    /// The logic in this method is as follows:
    /// -# Case 1. if there are no leases, and there are reservations...
    ///    Are the reserved addresses/prefixes used by someone else?
    ///   -# yes: we have a problem. We can't assign the reserved address yet,
    ///       because it is used by someone else. We can't immediately release
    ///       the lease as there is some other client that is currently using it.
    ///       We will temporarily assign a different, unreserved lease for this
    ///       client. In the mean time, the other client will hopefully get back
    ///       to us, so we could revoke his lease.
    ///   -# no: assign them => done
    /// -# Case 2. if there are leases and there are no reservations...
    ///    Are the leases reserved for someone else?
    ///    -# yes: release them, assign something else
    ///    -#  no: renew them => done
    /// -# Case 3. if there are leases and there are reservations...
    ///    Are the leases matching reservations?
    ///   -# yes: renew them => done
    ///   -#  no: release existing leases, assign new ones based on reservations
    /// -# Case 4. if there are no leases and no reservations...
    ///       assign new leases (this is the "normal" case when the reservations
    ///       are disabled).
    ///
    /// @param ctx client context that passes all necessary information. See
    ///        @ref ClientContext6 for details.
    ///
    /// The following fields of ClientContext6 are used:
    ///
    /// @ref ClientContext6::subnet_ subnet the allocation should come from<br/>
    /// @ref ClientContext6::duid_ Client's DUID<br/>
    /// @ref ClientContext6::iaid_ iaid field from the IA_NA container
    ///        that client sent<br/>
    /// @ref ClientContext6::hints_ a hint that the client provided<br/>
    /// @ref ClientContext6::type_ lease type (IA, TA or PD)<br/>
    /// @ref ClientContext6::fwd_dns_update_ A boolean value which indicates
    ///        that server takes responsibility for the forward DNS Update
    ///        for this lease (if true).<br/>
    /// @ref ClientContext6::rev_dns_update_ A boolean value which indicates
    ///        that server takes responsibility for the reverse DNS Update for
    ///        this lease (if true).<br/>
    /// @ref ClientContext6::hostname_ A fully qualified domain-name of the client.<br/>
    /// @ref ClientContext6::fake_allocation_ is this real i.e. REQUEST (false)
    ///        or just picking an address for SOLICIT that is not really
    ///        allocated (true)<br/>
    /// @ref ClientContext6::callout_handle_ a callout handle (used in hooks). A
    ///        lease callouts will be executed if this parameter is passed.<br/>
    /// @ref ClientContext6::old_leases_ [out] Collection to which this function
    ///        will append old leases. Leases are stored in the same order as in
    ///        the collection of new leases, being returned. For newly allocated
    ///        leases (not renewed) the NULL pointers are stored in this
    ///        collection as old leases.<br/>
    /// @ref ClientContext6::hwaddr_ Hardware address (optional, may be null if
    ///        not available)<br/>
    /// @ref ClientContext6::host_ Host reservation. allocateLeases6 will set
    ///        this field, if appropriate reservation is found.
    ///
    /// @return Allocated IPv6 leases (may be empty if allocation failed)
    Lease6Collection
    allocateLeases6(ClientContext6& ctx);

    /// @brief Renews existing DHCPv6 leases for a given IA.
    ///
    /// This method updates the leases associated with a specified IA container.
    /// It will extend the leases under normal circumstances, but sometimes
    /// there may be reasons why not to do so. Such a reasons may be:
    /// - client attempts to renew an address that is not valid
    /// - client attempts to renew an address that is now reserved for someone
    ///   else (see host reservation)
    /// - client's leases does not match his reservations
    ///
    /// This method will call  the lease6_renew callout.
    ///
    /// @param ctx Message processing context. It holds various information
    /// extracted from the client's message and required to allocate a lease.
    /// In particular, @ref ClientContext6::hints_ provides list of addresses or
    /// prefixes the client had sent. @ref ClientContext6::old_leases_ will
    /// contain removed leases in this case.
    ///
    /// @return Returns renewed lease.
    Lease6Collection renewLeases6(ClientContext6& ctx);

    /// @brief Attempts to find appropriate host reservation.
    ///
    /// Attempts to find appropriate host reservation in HostMgr. If found, it
    /// will be set in ctx.host_.
    /// @param ctx Client context that contains all necessary information.
    void findReservation(ClientContext6& ctx) const;

private:

    /// @brief creates a lease and inserts it in LeaseMgr if necessary
    ///
    /// Creates a lease based on specified parameters and tries to insert it
    /// into the database. That may fail in some cases, i.e. when there is another
    /// allocation process and we lost a race to a specific lease.
    ///
    /// @param ctx client context that passes all necessary information. See
    ///        @ref ClientContext6 for details.
    /// @param addr an address that was selected and is confirmed to be
    ///        available
    /// @param prefix_len length of the prefix (for PD only)
    ///        should be 128 for other lease types
    ///
    /// The following fields of the ctx structure are used:
    /// @ref ClientContext6::subnet_ subnet the lease is allocated from
    /// @ref ClientContext6::duid_ client's DUID
    /// @ref ClientContext6::iaid_ IAID from the IA_NA container the client sent to us
    /// @ref ClientContext6::type_ lease type (IA, TA or PD)
    /// @ref ClientContext6::fwd_dns_update_ A boolean value which indicates that server takes
    ///        responsibility for the forward DNS Update for this lease
    ///        (if true).
    /// @ref ClientContext6::rev_dns_update_ A boolean value which indicates that server takes
    ///        responsibility for the reverse DNS Update for this lease
    ///        (if true).
    /// @ref ClientContext6::hostname_ A fully qualified domain-name of the client.
    /// @ref ClientContext6::hwaddr_ Hardware address (optional, may be null for Lease6)
    /// @ref ClientContext6::callout_handle_ a callout handle (used in hooks). A lease callouts
    ///        will be executed if this parameter is passed (and there are callouts
    ///        registered)
    /// @ref ClientContext6::fake_allocation_ is this real i.e. REQUEST (false) or just picking
    ///        an address for SOLICIT that is not really allocated (true)
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///         became unavailable)
    Lease6Ptr createLease6(ClientContext6& ctx,
                           const isc::asiolink::IOAddress& addr,
                           const uint8_t prefix_len);

    /// @brief Allocates a normal, in-pool, unreserved lease from the pool.
    ///
    /// It attempts to pick a hint first, then uses allocator iteratively until
    /// an available (not used, not reserved) lease is found. In principle, it
    /// may return more than one lease, but we currently handle only one.
    /// This may change in the future.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @return collection of newly allocated leases
    Lease6Collection allocateUnreservedLeases6(ClientContext6& ctx);

    /// @brief Creates new leases based on reservations.
    ///
    /// This method allocates new leases, based on host reservation. Existing
    /// leases are specified in existing_leases parameter. A new lease is not created,
    /// if there is a lease for specified address on existing_leases list or there is
    /// a lease used by someone else.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @param existing_leases leases that are already associated with the client
    void
    allocateReservedLeases6(ClientContext6& ctx, Lease6Collection& existing_leases);

    /// @brief Removes leases that are reserved for someone else.
    ///
    /// Goes through the list specified in existing_leases and removes those that
    /// are reserved by someone else. The removed leases are added to the
    /// ctx.removed_leases_ collection.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @param existing_leases [in/out] leases that should be checked
    void
    removeNonmatchingReservedLeases6(ClientContext6& ctx,
                                     Lease6Collection& existing_leases);

    /// @brief Removed leases that are not reserved for this client
    ///
    /// This method iterates over existing_leases and will remove leases that are
    /// not reserved for this client. It will leave at least one lease on the list,
    /// if possible. The reason to run this method is that if there is a reservation
    /// for address A for client X and client X already has a lease for a
    /// different address B, we should assign A and release B. However,
    /// if for some reason we can't assign A, keeping B would be better than
    /// not having a lease at all. Hence we may keep B if that's the only lease
    /// left.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @param existing_leases [in/out] leases that should be checked
    void
    removeNonreservedLeases6(ClientContext6& ctx,
                             Lease6Collection& existing_leases);

    /// @brief Reuses expired IPv6 lease
    ///
    /// Updates existing expired lease with new information. Lease database
    /// is updated if this is real (i.e. REQUEST, fake_allocation = false), not
    /// dummy allocation request (i.e. SOLICIT, fake_allocation = true).
    ///
    /// @param expired old, expired lease
    /// @param ctx client context that contains all details.
    /// @param prefix_len prefix length (for PD leases)
    ///        Should be 128 for other lease types
    ///
    /// The following parameters are used from the ctx structure:
    /// @ref ClientContext6::subnet_ subnet the lease is allocated from
    /// @ref ClientContext6::duid_ client's DUID
    /// @ref ClientContext6::iaid_ IAID from the IA_NA container the client sent to us
    /// @ref ClientContext6::fwd_dns_update_ A boolean value which indicates that server takes
    ///        responsibility for the forward DNS Update for this lease
    ///        (if true).
    /// @ref ClientContext6::rev_dns_update_ A boolean value which indicates that server takes
    ///        responsibility for the reverse DNS Update for this lease
    ///        (if true).
    /// @ref ClientContext6::hostname_ A fully qualified domain-name of the client.
    /// @ref ClientContext6::callout_handle_ a callout handle (used in hooks). A
    ///        lease callouts will be executed if this parameter is passed.
    /// @ref ClientContext6::fake_allocation_ is this real i.e. REQUEST (false)
    ///        or just picking an address for SOLICIT that is not really
    ///        allocated (true)
    ///
    /// @return refreshed lease
    /// @throw BadValue if trying to recycle lease that is still valid
    Lease6Ptr reuseExpiredLease(Lease6Ptr& expired,
                                ClientContext6& ctx,
                                uint8_t prefix_len);

    /// @brief Updates FQDN and Client's Last Tranmission Time for a collection
    /// of leases.
    ///
    /// This method is executed when the server finds existing leases for a
    /// client and updates some date for these leases if needed:
    /// - client's last transmission time (cltt), if the lease to be returned
    ///   to the client should have its lifetime extended,
    /// - FQDN data, when the client has negotiated new FQDN with the server.
    ///
    /// @param ctx IPv6 client context (old versions of the leases that had
    ///            FQDN data changed will be stored in ctx.changed_leases_,
    ///            ctx.fwd_dns_update, ctx.rev_dns_update, ctx.hostname_
    ///            and ctx.fake_allocation_ will be used.
    /// @param leases Collection of leases for which lease data should be
    /// updated.
    ///
    /// @return Collection of leases with updated data. Note that returned
    /// collection holds updated FQDN data even for fake allocation.
    Lease6Collection updateLeaseData(ClientContext6& ctx,
                                     const Lease6Collection& leases);

    /// @brief Utility function that removes all leases with a specified address
    /// @param container A collection of Lease6 pointers
    /// @param addr address to be removed
    /// @return true if removed (false otherwise)
    static bool
    removeLeases(Lease6Collection& container,
                 const asiolink::IOAddress& addr);

    /// @brief Extends specified IPv6 lease
    ///
    /// This method attempts to extend the lease. It will call the lease6_renew
    /// or lease6_rebind hooks (depending on the client's message specified in
    /// ctx.query). The lease will be extended in LeaseMgr, unless the hooks
    /// library will set the skip flag.
    ///
    /// @param ctx client context that passes all necessary information. See
    ///        @ref ClientContext6 for details.
    /// @param lease IPv6 lease to be extended.
    void extendLease6(ClientContext6& ctx, Lease6Ptr lease);

public:

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
    struct ClientContext4 {
        /// @brief Subnet selected for the client by the server.
        Subnet4Ptr subnet_;

        /// @brief Client identifier from the DHCP message.
        ClientIdPtr clientid_;

        /// @brief HW address from the DHCP message.
        HWAddrPtr hwaddr_;

        /// @brief An address that the client desires.
        ///
        /// If this address is set to 0 it indicates that this address
        /// is unspecified.
        asiolink::IOAddress requested_address_;

        /// @brief Perform forward DNS update.
        bool fwd_dns_update_;

        /// @brief Perform reverse DNS update.
        bool rev_dns_update_;

        /// @brief Hostname.
        ///
        /// The server retrieves the hostname from the Client FQDN option,
        /// Hostname option or the host reservation record for the client.
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

        /// @brief A pointer to the object representing a lease in conflict.
        ///
        /// This pointer is set by some of the allocation methods when
        /// the lease can't be allocated because there is another lease
        /// which is in conflict with this allocation.
        Lease4Ptr conflicting_lease_;

        /// @brief A pointer to the client's message.
        ///
        /// This is used in logging to retrieve the client's and the
        /// transaction identification information.
        Pkt4Ptr query_;

        /// @brief Default constructor.
        ClientContext4();

        /// @brief Constructor with parameters
        ///
        /// @param subnet subnet the allocation should come from (mandatory)
        /// @param clientid Client identifier (optional)
        /// @param hwaddr Client's hardware address info (mandatory)
        /// @param requested_addr A hint that the client provided (may be 0.0.0.0)
        /// @param fwd_dns_update Indicates whether forward DNS
        ///      update will be performed for the client (true) or not (false).
        /// @param rev_dns_update Indicates whether reverse DNS
        ///      update will be performed for the client (true) or not (false).
        /// @param hostname A string carrying hostname to be used for DNS updates.
        /// @param fake_allocation Is this real i.e. REQUEST (false)
        ///      or just picking an address for DISCOVER that is not really
        ///      allocated (true)
        ClientContext4(const Subnet4Ptr& subnet, const ClientIdPtr& clientid,
                       const HWAddrPtr& hwaddr,
                       const asiolink::IOAddress& requested_addr,
                       const bool fwd_dns_update, const bool rev_dns_update,
                       const std::string& hostname, const bool fake_allocation);

    };

    /// @brief Pointer to the @c ClientContext4.
    typedef boost::shared_ptr<ClientContext4> ClientContext4Ptr;

    /// @brief Returns IPv4 lease.
    ///
    /// This method finds a lease for a client using the following algorithm:
    /// - If a lease exists for the combination of the HW address or client id
    ///   and a subnet, try to use this lease for the client. If the client
    ///   has a reservation for an address for which the lease was created or
    ///   the client desires to renew the lease for this address (ciaddr or
    ///   requested IP address option), the server renews the lease for the
    ///   client. If the client desires a different address or the server has
    ///   a (potentially new) reservation for a different address for this
    ///   client, the existing lease is replaced with a new lease.
    /// - If the client has no lease in the lease database the server will try
    ///   to allocate a new lease. If the client has a reservation for the
    ///   particular address or if it has specified a desired address the
    ///   server will check if the particular address is not allocated to
    ///   another client. If the address is available, the server will allocate
    ///   this address for the client.
    /// - If the desired address is unavailable the server checks if the
    ///   lease for this address has expired. If the lease is expired, the
    ///   server will allocate this lease to the client. The relevant
    ///   information will be updated, e.g. new client HW address, host name
    ///   etc.
    /// - If the desired address is in use by another client, the server will
    ///   try to allocate a different address. The server picks addresses from
    ///   a dynamic pool and checks if the address is available and that
    ///   it is not reserved for another client. If it is in use by another
    ///   client or if it is reserved for another client, the address is not
    ///   allocated. The server picks the next address and repeats this check.
    ///   Note that the server ceases allocation after the configured number
    ///   of unsuccessful attempts.
    ///
    /// The lease allocation process is slightly different for the
    /// DHCPDISCOVER and DHCPREQUEST messages. In the former case, the client
    /// may specify the requested IP address option with a desired address and
    /// the server treats this address as a hint. This means that the server may
    /// allocate a different address at its discretion and send it to the
    /// client in the DHCPOFFER. If the client accepts this offer it specifies
    /// this address in the requested IP address option in the DHCPREQUEST.
    /// At this point, the allocation engine will use the requested IP address
    /// as a hard requirement and if this address can't be allocated for
    /// any reason, the allocation engine returns NULL lease. As a result,
    /// the DHCP server sends a DHCPNAK to the client and the client
    /// falls back to the DHCP server discovery.
    ///
    /// The only exception from this rule is when the client doesn't specify
    /// a requested IP address option (invalid behavior) in which case the
    /// allocation engine will try to allocate any address.
    ///
    /// If there is an address reservation specified for the particular client
    /// the reserved address always takes precedence over addresses from the
    /// dynamic pool or even an address currently allocated for this client.
    ///
    /// It is possible that the address reserved for the particular client
    /// is in use by another client, e.g. as a result of pools reconfiguration.
    /// In this case, when the client requests allocation of the reserved
    /// address and the server determines that it is leased to someone else,
    /// the allocation engine allocates a different address for this client.
    ///
    /// When the client having a lease returns to renew, the allocation engine
    /// doesn't extend the lease for it and returns a NULL pointer. The client
    /// falls back to the 4-way exchange and a different lease is allocated.
    /// At this point, the reserved address is freed and can be allocated to
    /// the client which holds this reservation. However, this client has a
    /// lease for a different address at this time. When the client renews its
    /// lease it receives the DHCPNAK and falls back to the DHCP server
    /// discovery and obtains the lease for the reserved address.
    ///
    /// When a server should do DNS updates, it is required that allocation
    /// returns the information about how the lease was obtained by the allocation
    /// engine. In particular, the DHCP server should be able to check whether
    /// an existing lease was returned, or a new lease was allocated. When an
    /// existing lease was returned, the server should check whether the FQDN has
    /// changed between the allocation of the old and new lease. If so, the server
    /// should perform the appropriate DNS update. If not, the server may choose
    /// to not perform the update. The information about the old lease is returned via
    /// @c old_lease parameter. If NULL value is returned, it is an indication
    /// that a new lease was allocated for the client. If non-NULL value is
    /// returned, it is an indication that allocation engine reused/renewed an
    /// existing lease.
    ///
    /// @param ctx client context that passes all necessary information. See
    ///        @ref ClientContext4 for details.
    ///
    /// The following fields of @ref ClientContext4 are used:
    ///
    /// - @ref ClientContext4::subnet_ subnet the allocation should come from
    /// - @ref ClientContext4::clientid_ Client identifier
    /// - @ref ClientContext4::hwaddr_ Client's hardware address info
    /// - @ref ClientContext4::requested_address_ A hint that the client provided
    /// - @ref ClientContext4::fwd_dns_update_ Indicates whether forward DNS
    ///      update will be performed for the client (true) or not (false).
    /// - @ref ClientContext4::rev_dns_update_ Indicates whether reverse DNS
    ///      update will be performed for the client (true) or not (false).
    /// - @ref ClientContext4::hostname_ A string carrying hostname to be used for
    ///      DNS updates.
    /// - @ref ClientContext4::fake_allocation_ Is this real i.e. REQUEST (false)
    ///      or just picking an address for DISCOVER that is not really
    ///      allocated (true)
    /// - @ref ClientContext4::host_ Pointer to the object representing the
    //       static reservations (host reservations) for the client.
    /// - @ref ClientContext4::callout_handle_ A callout handle (used in hooks).
    ///      A lease callouts will be executed if this parameter is passed.
    /// - @ref ClientContext4::old_lease_ [out] Holds the pointer to a previous
    ///      instance of a lease. The NULL pointer indicates that lease didn't
    ///      exist prior to calling this function (e.g. new lease has been allocated).
    ///
    /// @return Allocated IPv4 lease (or NULL if allocation failed).
    Lease4Ptr allocateLease4(ClientContext4& ctx);

    /// @brief Attempts to find the host reservation for the client.
    ///
    /// This method attempts to find the host reservation for the client. If
    /// found, it is set in the @c ctx.host_. If the host reservations are
    /// disabled for the particular subnet or the reservation is not found
    /// for the client, the @c ctx.host_ is set to NULL.
    ///
    /// @param ctx Client context holding various information about the client.
    static void findReservation(ClientContext4& ctx);

private:

    /// @brief Offers the lease.
    ///
    /// This method is called by the @c AllocEngine::allocateLease4 when
    /// the server is processing a DHCPDISCOVER message, i.e. the fake
    /// allocation case.
    ///
    /// This method doesn't modify leases in the lease database. It finds
    /// the most suitable lease for the client and returns it to the caller.
    /// The server uses this lease when it sends the DHCPOFFER to the
    /// client from which it has received a DHCPDISCOVER message.
    ///
    /// The lease is found using the following algorithm:
    /// -# If there is a reservation for the client, try to use the reserved
    ///    address. This may fail if the particular address is in use by
    ///    another client. In such case:
    /// -# If the client has a lease, try to offer this lease. This may fail
    ///    if it turns out that this address is reserved for another client
    ///    or the address doesn't belong to the address pool. In such case:
    /// -# Try to allocate the address provided by the client as a hint.
    ///    This may fail if the address is in use or is reserved by some
    ///    other client. In such case:
    /// -# Try to offer an address from the dynamic pool.
    ///
    /// @throw various exceptions if the allocation goes wrong.
    ///
    /// @param ctx Client context holding the data extracted from the
    /// client's message.
    ///
    /// @return A pointer to the offered lease, or NULL if no suitable lease
    /// has been found.
    Lease4Ptr discoverLease4(ClientContext4& ctx);

    /// @brief Allocates the lease.
    ///
    /// This method is called by the @c AllocEngine::allocateLease4 when
    /// the server is processing a DHCPREQUEST message, i.e. the real
    /// allocation case.
    ///
    /// This method modifies the lease information in the lease database.
    /// It adds new leases, modifies existing leases or deletes them.
    ///
    /// The method returns NULL to indicate that the lease allocation
    /// has failed when any of the following occur:
    /// -# The requested address is specified but is reserved for another
    ///    client.
    /// -# The requested address is in use by another client.
    /// -# There is a reservation for the particular client, the
    ///    reserved address is not in use by another client and the
    ///    requested address is different than the reserved address.
    /// -# There is no reservation for the client and the requested address
    ///    is not in the dynamic pool.
    ///
    /// If none of the above occurs, the method will try to allocate the
    /// lease for the client using the following algorithm:
    /// -# If the client has a lease and the client is requesting the
    ///    address for which it has a lease, renew its lease.
    /// -# If the client is requesting a different address than that for
    ///    which it has a lease, try to allocate the requested address.
    ///    This may fail if the address is in use by another client.
    /// -# If the client is not requesting any specific address, allocate
    ///    the address from the dynamic pool.
    ///
    /// @throws various exceptions if the allocation goes wrong.
    ///
    /// @param ctx Client context holding the data extracted from the
    /// client's message.
    ///
    /// @return A pointer to the allocated lease, or NULL if no suitable
    /// lease could be allocated.
    Lease4Ptr requestLease4(ClientContext4& ctx);

    /// @brief Creates a lease and inserts it in LeaseMgr if necessary
    ///
    /// Creates a lease based on specified parameters and tries to insert it
    /// into the database. That may fail in some cases, e.g. when there is another
    /// allocation process and we lost a race to a specific lease.
    ///
    /// @param ctx client context that contains additional parameters.
    /// @param addr An address that was selected and is confirmed to be available
    ///
    /// In particular, the following fields from Client context are used:
    /// - @ref ClientContext4::subnet_ Subnet the lease is allocated from
    /// - @ref ClientContext4::clientid_ Client identifier
    /// - @ref ClientContext4::hwaddr_ Client's hardware address
    /// - @ref ClientContext4::fwd_dns_update_ Indicates whether forward DNS update
    ///        will be performed for the client (true) or not (false).
    /// - @ref ClientContext4::rev_dns_update_ Indicates whether reverse DNS update
    ///        will be performed for the client (true) or not (false).
    /// - @ref ClientContext4::hostname_ A string carrying hostname to be used for
    ///        DNS updates.
    /// - @ref ClientContext4::callout_handle_ a callout handle (used in hooks).
    ///        A lease callouts will be executed if this parameter is passed
    ///        (and there are callouts registered)
    /// - @ref ClientContext4::fake_allocation_ Is this real i.e. REQUEST (false)
    ///        or just picking an address for DISCOVER that is not really
    ///        allocated (true)
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///        becomed unavailable)
    Lease4Ptr createLease4(const ClientContext4& ctx,
                           const isc::asiolink::IOAddress& addr);

    /// @brief Renews a DHCPv4 lease.
    ///
    /// This method updates the lease with the information from the provided
    /// context and invokes the lease4_renew callout.
    ///
    /// The address of the lease being renewed is NOT updated.
    ///
    /// @param lease A lease to be renewed.
    /// @param ctx Message processing context. It holds various information
    /// extracted from the client's message and required to allocate a lease.
    ///
    /// @return Returns renewed lease. Note that the lease is only updated when
    /// it is an actual allocation (not processing a DHCPDISCOVER message).
    Lease4Ptr renewLease4(const Lease4Ptr& lease, ClientContext4& ctx);

    /// @brief Reuses expired DHCPv4 lease.
    ///
    /// Makes a new allocation using an expired lease. The lease is updated with
    /// the information from the provided context. Typically, an expired lease
    /// which belonged to one client may be assigned to another client
    /// which asked for the specific address.
    ///
    /// @param expired An old, expired lease.
    /// @param ctx Message processing context. It holds various information
    /// extracted from the client's message and required to allocate a lease.
    ///
    /// @return Updated lease instance.
    /// @throw BadValue if trying to reuse a lease which is still valid or
    /// when the provided parameters are invalid.
    Lease4Ptr reuseExpiredLease4(Lease4Ptr& expired, ClientContext4& ctx);

    /// @brief Allocates the lease by replacing an existing lease.
    ///
    /// This method checks if the lease database contains the lease for
    /// the specified address. If the lease exists and has expired, it
    /// reuses the expired lease. If the lease doesn't exist, it creates
    /// the new lease.
    ///
    /// @param address Requested address for which the lease should be
    /// allocted.
    /// @param ctx Client context holding the data extracted from the
    /// client's message.
    ///
    /// @return A pointer to the allocated lease or NULL if the allocation
    /// was not successful.
    Lease4Ptr allocateOrReuseLease4(const asiolink::IOAddress& address,
                                    ClientContext4& ctx);

    /// @brief Allocates the lease from the dynamic pool.
    ///
    /// This method allocates the lease from the dynamic pool. It uses
    /// one of the allocators to pick addresses from the pool and if the
    /// address appears to be available, it allocates the new lease
    /// using this address. The number of attempts depends on the size
    /// of the dynamic pool. If all of the addresses in the pool have
    /// been tried and all of them appeared to be in use, the allocation
    /// fails. This is the case when the pool is exhausted.
    ///
    /// The time required to find a suitable lease depends on the current
    /// pool utilization.
    ///
    /// @param ctx Client context holding the data extracted from the
    /// client's message.
    ///
    /// @return A pointer to the allocated lease or NULL if the allocation
    /// was not successful.
    Lease4Ptr allocateUnreservedLease4(ClientContext4& ctx);

    /// @brief Updates the specified lease with the information from a context.
    ///
    /// The context, specified as an argument to this method, holds various
    /// information gathered from the client's message and passed to the
    /// allocation engine. The allocation engine uses this information to make
    /// lease allocation decisions. Some public methods of the allocation engine
    /// requires updating the lease information with the data gathered from the
    /// context, e.g. @c AllocEngine::reuseExpiredLease requires updating the
    /// expired lease with fresh information from the context to create a
    /// lease to be held for the client.
    ///
    /// Note that this doesn't update the lease address.
    ///
    /// @warning This method doesn't check if the pointer to the lease is
    /// valid nor if the subnet to the pointer in the @c ctx is valid.
    /// The caller is responsible for making sure that they are valid.
    ///
    /// @param [out] lease A pointer to the lease to be updated.
    /// @param ctx A context containing information from the server about the
    /// client and its message.
    void updateLease4Information(const Lease4Ptr& lease,
                                 ClientContext4& ctx) const;

    /// @brief Extends the lease lifetime.
    ///
    /// This function is called to conditionally extend the lifetime of
    /// the DHCPv4 or DHCPv6 lease. It is envisaged that this function will
    /// make a decision if the lease lifetime should be extended, using
    /// a preconfigured threshold, which would indicate how many percent
    /// of the valid lifetime should have passed for the lease lifetime
    /// to be extended. The lease lifetime would not be extended if
    /// the threshold hasn't been reached.
    ///
    /// @todo Currently this function always extends the lease lifetime.
    /// In the future, it will take the threshold value into account,
    /// once the threshold is configurable.
    ///
    /// @param [in,out] lease A lease for which the lifetime should be
    /// extended.
    ///
    /// @return true if the lease lifetime has been extended, false
    /// otherwise.
    bool conditionalExtendLifetime(Lease& lease) const;

};

/// @brief A pointer to the @c AllocEngine object.
typedef boost::shared_ptr<AllocEngine> AllocEnginePtr;

}; // namespace isc::dhcp
}; // namespace isc

#endif // ALLOC_ENGINE_H
