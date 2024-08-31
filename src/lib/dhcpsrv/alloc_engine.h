// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ALLOC_ENGINE_H
#define ALLOC_ENGINE_H

#include <asiolink/io_address.h>
#include <dhcp/classify.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcpsrv/allocator.h>
#include <dhcpsrv/d2_client_cfg.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/srv_config.h>
#include <hooks/callout_handle.h>
#include <util/multi_threading_mgr.h>
#include <util/readwrite_mutex.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <utility>

namespace isc {
namespace dhcp {

/// @brief DHCPv4 and DHCPv6 allocation engine
///
/// This class represents a DHCP allocation engine. It is responsible
/// for picking subnets, choosing and allocating a lease, extending,
/// renewing, releasing and possibly expiring leases.
class AllocEngine : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// Instantiates necessary services, required to run DHCP server.
    /// In particular, creates IfaceMgr that will be responsible for
    /// network interaction. Will instantiate lease manager, and load
    /// old or create new DUID.
    ///
    /// @param attempts number of attempts for each lease allocation before
    ///        we give up (0 means unlimited)
    AllocEngine(isc::util::uint128_t const& attempts);

    /// @brief Destructor.
    virtual ~AllocEngine() { }

private:

    /// @brief number of attempts before we give up lease allocation (0=unlimited)
    isc::util::uint128_t attempts_;

    /// @brief Hook name indexes (used in hooks callouts)
    int hook_index_lease4_select_; ///< index for lease4_select hook
    int hook_index_lease6_select_; ///< index for lease6_select hook

public:

    /// @brief Defines a single hint
    ///
    /// This is an entry that represents what the client had requested,
    /// either an address or a prefix. Prefix length is 128 for regular
    /// addresses. Optionally it provides wanted preferred and valid
    /// lifetimes.
    ///
    /// @note Seems to be used only for DHCPv6.
    class Resource {
    public:

        /// @brief Default constructor.
        ///
        /// @param address the address or prefix
        /// @param prefix_len the prefix length (defaults to 128)
        /// @param preferred the optional preferred lifetime,
        /// defaults to 0, meaning not specified
        /// @param valid the optional valid lifetime,
        /// defaults to 0, meaning not specified
        Resource(const isc::asiolink::IOAddress& address,
                 const uint8_t prefix_len = 128,
                 const uint32_t preferred = 0,
                 const uint32_t valid = 0)
            : address_(address), prefix_len_(prefix_len),
              preferred_(preferred), valid_(valid) {
        }

        /// @brief Returns the address.
        ///
        /// @return the address or prefix
        isc::asiolink::IOAddress getAddress() const {
            return (address_);
        }

        /// @brief Returns the prefix length.
        ///
        /// @return the prefix length
        uint8_t getPrefixLength() const {
            return (prefix_len_);
        }

        /// @brief Returns the optional preferred lifetime.
        ///
        /// @return the preferred lifetime (0 if not set)
        uint32_t getPreferred() const {
            return (preferred_);
        }

        /// @brief Returns the optional valid lifetime.
        ///
        /// @return the valid lifetime (0 if not set)
        uint32_t getValid() const {
            return (valid_);
        }

        /// @brief Compares two @c AllocEngine::Resource objects for equality.
        ///
        /// @param other object to be compared with this object
        ///
        /// @return true if objects are equal, false otherwise.
        bool equals(const Resource& other) const {
            return (address_ == other.address_ &&
                    prefix_len_ == other.prefix_len_);
        }

        /// @brief Equality operator.
        ///
        /// @param other object to be compared with this object
        ///
        /// @return true if objects are equal, false otherwise.
        bool operator==(const Resource& other) const {
            return (equals(other));
        }

    protected:

        /// @brief The address or prefix.
        isc::asiolink::IOAddress address_;

        /// @brief The prefix length (128 for an address).
        uint8_t prefix_len_;

        /// @brief The preferred lifetime (0 when not set).
        uint32_t preferred_;

        /// @brief The valid lifetime (0 when not set).
        uint32_t valid_;
    };

    /// @brief Resource compare class.
    ///
    /// Needed for using sets of Resource objects.
    struct ResourceCompare {
        /// @brief Compare operator
        ///
        /// @note Only the address/prefix part of resources is used.
        /// @param lhr Left hand resource object
        /// @param rhr Right hand resource object
        ///
        /// @return true if lhr is less than rhr, false otherwise
        bool operator() (const Resource& lhr, const Resource& rhr) const {
            if (lhr.getAddress() == rhr.getAddress()) {
                return (lhr.getPrefixLength() < rhr.getPrefixLength());
            } else {
                return (lhr.getAddress() < rhr.getAddress());
            }
        }
    };

    /// @brief Container for client's hints.
    typedef std::vector<Resource> HintContainer;

    /// @brief Container holding allocated prefixes or addresses.
    typedef std::set<Resource, ResourceCompare> ResourceContainer;

    /// @brief A tuple holding host identifier type and value.
    typedef std::pair<Host::IdentifierType, std::vector<uint8_t> > IdentifierPair;

    /// @brief Map holding values to be used as host identifiers.
    typedef std::list<IdentifierPair> IdentifierList;

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
    struct ClientContext6 : public boost::noncopyable {

        /// @name Parameters pertaining to DHCPv6 message
        //@{

        /// @brief A pointer to the client's message
        ///
        /// This is used exclusively for hook purposes.
        Pkt6Ptr query_;

        /// @brief Indicates if this is a real or fake allocation.
        ///
        /// The real allocation is when the allocation engine is supposed
        /// to make an update in a lease database: create new lease, or
        /// update existing lease.
        bool fake_allocation_;

        /// @brief Indicates if early global reservation is enabled.
        ///
        /// This caches the early-global-reservations-lookup value.
        bool early_global_reservations_lookup_;

        /// @brief Subnet selected for the client by the server.
        Subnet6Ptr subnet_;

        /// @brief Subnet from which host reservations should be retrieved.
        ///
        /// It can be NULL, in which case @c subnet_ value is used.
        Subnet6Ptr host_subnet_;

        /// @brief Client identifier
        DuidPtr duid_;

        /// @brief Hardware/MAC address (if available, may be NULL)
        HWAddrPtr hwaddr_;

        /// @brief A list holding host identifiers extracted from a message
        /// received by the server.
        IdentifierList host_identifiers_;

        /// @brief Holds a map of hosts belonging to the client within different
        /// subnets.
        ///
        /// Multiple hosts may appear when the client belongs to a shared
        /// network.
        std::map<SubnetID, ConstHostPtr> hosts_;

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

        /// @brief Holds addresses and prefixes allocated for all IAs.
        ResourceContainer allocated_resources_;

        /// @brief A collection of newly allocated leases.
        Lease6Collection new_leases_;

        //@}

        /// @brief Parameters pertaining to individual IAs.
        struct IAContext {

            /// @brief The IAID field from IA_NA or IA_PD that is being
            /// processed
            uint32_t iaid_;

            /// @brief Lease type (IA or PD)
            Lease::Type type_;

            /// @brief Client's hints
            ///
            /// There will typically be just one address, but the protocol
            /// allows more than one address or prefix for each IA container.
            HintContainer hints_;

            /// @brief A pointer to any old leases that the client had before
            /// update but are no longer valid after the update/allocation.
            ///
            /// This collection is typically empty, except cases when we are
            /// doing address reassignment, e.g. because there is a host
            /// reservation that gives this address to someone else, so we had
            /// to return the address, and give a new one to this client.
            Lease6Collection old_leases_;

            /// @brief A pointer to any leases that have changed FQDN
            /// information.
            ///
            /// This list may contain old versions of the leases that are still
            /// valid. In particular, it will contain a lease if the client's
            /// FQDN has changed.
            Lease6Collection changed_leases_;

            /// @brief Holds addresses and prefixes allocated for this IA.
            ///
            /// This collection is used to update at most once new leases.
            ResourceContainer new_resources_;

            /// @brief A pointer to the IA_NA/IA_PD option to be sent in
            /// response
            Option6IAPtr ia_rsp_;

            /// @brief Default constructor.
            ///
            /// Initializes @ref type_ to @c Lease::TYPE_NA and @ref iaid_ to 0.
            IAContext();

            /// @brief Convenience method adding new hint.
            ///
            /// @param prefix Prefix or address.
            /// @param prefix_len Prefix length. Default is 128 for addresses.
            /// @param preferred Wanted preferred lifetime. Default 0.
            /// @param valid Wanted valid lifetime. Default 0.
            void addHint(const asiolink::IOAddress& prefix,
                         const uint8_t prefix_len = 128,
                         const uint32_t preferred = 0,
                         const uint32_t valid = 0);

            /// @brief Convenience method adding new hint from IAADDR option.
            ///
            /// @param iaaddr Pointer to IAADDR.
            ///
            /// @throw BadValue if iaaddr is null.
            void addHint(const Option6IAAddrPtr& iaaddr);

            /// @brief Convenience method adding new hint from IAPREFIX option.
            ///
            /// @param iaprefix Pointer to IAPREFIX.
            ///
            /// @throw BadValue if iaprefix is null.
            void addHint(const Option6IAPrefixPtr& iaprefix);

            /// @brief Convenience method adding new prefix or address.
            ///
            /// @param prefix Prefix or address
            /// @param prefix_len Prefix length. Default is 128 for addresses.
            void addNewResource(const asiolink::IOAddress& prefix,
                                const uint8_t prefix_len = 128);

            /// @brief Checks if specified address or prefix was new.
            ///
            /// @param prefix Prefix or address
            /// @param prefix_len Prefix length. Default is 128 for addresses.
            bool isNewResource(const asiolink::IOAddress& prefix,
                               const uint8_t prefix_len = 128) const;
        };

        /// @brief Container holding IA specific contexts.
        std::vector<IAContext> ias_;

        /// @brief Returns the set of DDNS behavioral parameters based on
        /// the selected subnet.
        ///
        /// If there is no selected subnet (i.e. subnet_ is empty), the
        /// returned set will contain default values.
        ///
        /// @return pointer to a DdnsParams instance
        DdnsParamsPtr getDdnsParams();

        /// @brief Convenience method adding allocated prefix or address.
        ///
        /// @param prefix Prefix or address.
        /// @param prefix_len Prefix length. Default is 128 for addresses.
        void addAllocatedResource(const asiolink::IOAddress& prefix,
                                  const uint8_t prefix_len = 128);

        /// @brief Checks if specified address or prefix was allocated.
        ///
        /// @param prefix Prefix or address.
        /// @param prefix_len Prefix length. Default is 128 for addresses.
        bool isAllocated(const asiolink::IOAddress& prefix,
                         const uint8_t prefix_len = 128) const;

        /// @brief Convenience function adding host identifier into
        /// @ref host_identifiers_ list.
        ///
        /// @param id_type Identifier type.
        /// @param identifier Identifier value.
        void addHostIdentifier(const Host::IdentifierType& id_type,
                               const std::vector<uint8_t>& identifier) {
            host_identifiers_.push_back(IdentifierPair(id_type, identifier));
        }

        /// @brief Returns IA specific context for the currently processed IA.
        ///
        /// If IA specific context doesn't exist, it is created.
        ///
        /// @return Reference to IA specific context.
        IAContext& currentIA() {
            if (ias_.empty()) {
                createIAContext();
            }
            return (ias_.back());
        }

        /// @brief Creates new IA context.
        ///
        /// This method should be invoked prior to processing a next IA included
        /// in the client's message.
        void createIAContext() {
            ias_.push_back(IAContext());
        };

        /// @brief Returns host from the most preferred subnet.
        ///
        /// If there is no such host and global reservations are enabled
        /// returns the global host.
        ///
        /// @return Pointer to the host object.
        ConstHostPtr currentHost() const;

        /// @brief Returns global host reservation if there is one
        ///
        /// If the current subnet's reservations-global is true and
        /// there is a global host (i.e. reservation belonging to
        /// the global subnet), return it.  Otherwise return an
        /// empty pointer.
        ///
        /// @return Pointer to the host object.
        ConstHostPtr globalHost() const;

        /// @brief Determines if a global reservation exists
        ///
        /// @return true if there current subnet's reservations-global
        /// is true and there is global host containing the given
        /// lease reservation, false otherwise
        bool hasGlobalReservation(const IPv6Resrv& resv) const;

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
        /// @param fwd_dns A boolean value which indicates that server takes
        ///        responsibility for the forward DNS Update for this lease
        ///        (if true).
        /// @param rev_dns A boolean value which indicates that server takes
        ///        responsibility for the reverse DNS Update for this lease
        ///        (if true).
        /// @param hostname A fully qualified domain-name of the client.
        /// @param fake_allocation is this real i.e. REQUEST (false) or just
        ///        picking an address for SOLICIT that is not really allocated
        ///        (true)
        /// @param query Pointer to the DHCPv6 message being processed.
        /// @param callout_handle Callout handle associated with a client's
        ///        message
        ClientContext6(const Subnet6Ptr& subnet, const DuidPtr& duid,
                       const bool fwd_dns, const bool rev_dns,
                       const std::string& hostname, const bool fake_allocation,
                       const Pkt6Ptr& query,
                       const hooks::CalloutHandlePtr& callout_handle =
                       hooks::CalloutHandlePtr());

        private:
            /// @brief Contains a pointer to the DDNS parameters for selected
            /// subnet.  Set by the first call to getDdnsParams() made when
            /// the context has a selected subnet (i.e. subnet_ is not empty).
            DdnsParamsPtr ddns_params_;
    };

    /// @brief Allocates IPv6 leases for a given IA container
    ///
    /// This method uses the currently selected allocator to pick allocable
    /// resources (i.e. addresses or prefixes) from specified subnet, creates
    /// a lease (one or more, if needed) for that resources and then inserts
    /// it into LeaseMgr (if this allocation is not fake, i.e. this is not a
    /// response to SOLICIT).
    ///
    /// This method uses host reservation if @ref ClientContext6::hosts_ is set.
    /// The easy way to set it is to call @ref findReservationDecl.
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
    /// @ref ClientContext6::subnet_ subnet the allocation should
    ///        come from<br/>
    /// @ref ClientContext6::duid_ Client's DUID<br/>
    /// @ref ClientContext6::IAContext::iaid_ iaid field from the IA_NA container
    ///        that client sent<br/>
    /// @ref ClientContext6::IAContext::hints_ a hint that the client provided<br/>
    /// @ref ClientContext6::IAContext::type_ lease type (IA, TA or PD)<br/>
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
    /// @ref ClientContext6::IAContext::old_leases_ [out] Collection to which this
    ///        function
    ///        will append old leases. Leases are stored in the same order as in
    ///        the collection of new leases, being returned. For newly allocated
    ///        leases (not renewed) the NULL pointers are stored in this
    ///        collection as old leases.<br/>
    /// @ref ClientContext6::hwaddr_ Hardware address (optional, may be null if
    ///        not available)<br/>
    /// @ref ClientContext6::hosts_ Host reservations. allocateLeases6 will set
    ///        this field, if appropriate reservations are found.
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
    /// This method will call the lease6_renew callout.
    ///
    /// @param ctx Message processing context. It holds various information
    /// extracted from the client's message and required to allocate a lease.
    /// In particular, @ref ClientContext6::IAContext::hints_ provides list
    /// of addresses or
    /// prefixes the client had sent. @ref ClientContext6::IAContext::old_leases_
    /// will contain removed leases in this case.
    ///
    /// @return Returns renewed lease.
    Lease6Collection renewLeases6(ClientContext6& ctx);

    /// @brief Reclaims expired IPv6 leases.
    ///
    /// This method retrieves a collection of expired leases and reclaims them.
    /// See
    /// https://gitlab.isc.org/isc-projects/kea/wikis/designs/lease-expiration#leases-reclamation-routine
    /// for the details.
    ///
    /// This method is executed periodically to act upon expired leases. This
    /// includes for each lease:
    /// - executing "lease_expire6" hook,
    /// - removing DNS record for a lease,
    /// - reclaiming a lease in the database, i.e. setting its state to
    ///   "expired-reclaimed" or removing it from the lease database,
    /// - updating statistics of assigned and reclaimed leases
    ///
    /// Note: declined leases fall under the same expiration/reclamation
    /// processing as normal leases. In principle, it would be more elegant
    /// to have a separate processing for declined leases reclamation. However,
    /// due to performance reasons we decided to use them together. Several
    /// aspects were taken into consideration. First, normal leases are expected
    /// to expire frequently, so in a typical deployment this method will have
    /// some leases to process. Second, declined leases are expected to be very
    /// rare event, so in most cases there won't be any declined expired leases.
    /// Third, the calls to LeaseMgr to obtain all leases of specific expiration
    /// criteria are expensive, so it is better to have one call rather than
    /// two, especially if one of those calls is expected to usually return no
    /// leases.
    ///
    /// It doesn't make sense to retain declined leases that are reclaimed,
    /// because those leases don't contain any useful information (all client
    /// identifying information was stripped when the leave was moved to the
    /// declined state). Therefore remove_leases parameter is ignored for
    /// declined leases. They are always removed.
    ///
    /// Also, for declined leases @ref reclaimDeclinedLease6 is
    /// called. It conducts several declined specific operation (extra log
    /// entry, stats dump, hooks).
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclamation routine
    /// may be processing expired leases, expressed in milliseconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    /// @param max_unwarned_cycles A number of consecutive processing cycles
    /// of expired leases, after which the system issues a warning if there
    /// are still expired leases in the database. If this value is 0, the
    /// warning is never issued.
    void reclaimExpiredLeases6(const size_t max_leases, const uint16_t timeout,
                               const bool remove_lease,
                               const uint16_t max_unwarned_cycles = 0);

    /// @brief Body of reclaimExpiredLeases6.
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclamation routine
    /// may be processing expired leases, expressed in milliseconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    /// @param max_unwarned_cycles A number of consecutive processing cycles
    /// of expired leases, after which the system issues a warning if there
    /// are still expired leases in the database. If this value is 0, the
    /// warning is never issued.
    void reclaimExpiredLeases6Internal(const size_t max_leases,
                                       const uint16_t timeout,
                                       const bool remove_lease,
                                       const uint16_t max_unwarned_cycles = 0);

    /// @brief Deletes reclaimed leases expired more than specified amount
    /// of time ago.
    ///
    /// @param secs Minimum number of seconds after which the lease can be
    /// deleted.
    void deleteExpiredReclaimedLeases6(const uint32_t secs);

    /// @brief Reclaims expired IPv4 leases.
    ///
    /// This method retrieves a collection of expired leases and reclaims them.
    /// See
    /// https://gitlab.isc.org/isc-projects/kea/wikis/designs/lease-expiration#leases-reclamation-routine
    /// for the details.
    ///
    /// This method is executed periodically to act upon expired leases. This
    /// includes for each lease:
    /// - executing "lease_expire4" hook,
    /// - removing DNS record for a lease,
    /// - reclaiming a lease in the database, i.e. setting its state to
    ///   "expired-reclaimed" or removing it from the lease database,
    /// - updating statistics of assigned and reclaimed leases
    ///
    /// Note: declined leases fall under the same expiration/reclamation
    /// processing as normal leases. In principle, it would be more elegant
    /// to have a separate processing for declined leases reclamation. However,
    /// due to performance reasons we decided to use them together. Several
    /// aspects were taken into consideration. First, normal leases are expected
    /// to expire frequently, so in a typical deployment this method will have
    /// some leases to process. Second, declined leases are expected to be very
    /// rare event, so in most cases there won't be any declined expired leases.
    /// Third, the calls to LeaseMgr to obtain all leases of specific expiration
    /// criteria are expensive, so it is better to have one call rather than
    /// two, especially if one of those calls is expected to usually return no
    /// leases.
    ///
    /// It doesn't make sense to retain declined leases that are reclaimed,
    /// because those leases don't contain any useful information (all client
    /// identifying information was stripped when the leave was moved to the
    /// declined state). Therefore remove_leases parameter is ignored for
    /// declined leases. They are always removed.
    ///
    /// Also, for declined leases @ref reclaimDeclinedLease4 is
    /// called. It conducts several declined specific operation (extra log
    /// entry, stats dump, hooks).
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclamation routine
    /// may be processing expired leases, expressed in milliseconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    /// @param max_unwarned_cycles A number of consecutive processing cycles
    /// of expired leases, after which the system issues a warning if there
    /// are still expired leases in the database. If this value is 0, the
    /// warning is never issued.
    void reclaimExpiredLeases4(const size_t max_leases, const uint16_t timeout,
                               const bool remove_lease,
                               const uint16_t max_unwarned_cycles = 0);

    /// @brief Body of reclaimExpiredLeases4.
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclamation routine
    /// may be processing expired leases, expressed in milliseconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    /// @param max_unwarned_cycles A number of consecutive processing cycles
    /// of expired leases, after which the system issues a warning if there
    /// are still expired leases in the database. If this value is 0, the
    /// warning is never issued.
    void reclaimExpiredLeases4Internal(const size_t max_leases,
                                       const uint16_t timeout,
                                       const bool remove_lease,
                                       const uint16_t max_unwarned_cycles = 0);

    /// @brief Deletes reclaimed leases expired more than specified amount
    /// of time ago.
    ///
    /// @param secs Minimum number of seconds after which the lease can be
    /// deleted.
    void deleteExpiredReclaimedLeases4(const uint32_t secs);

    /// @anchor findReservationDecl
    /// @brief Attempts to find appropriate host reservation.
    ///
    /// Attempts to find appropriate host reservation in HostMgr. If found, it
    /// is set in the @ref ClientContext6::hosts_.
    ///
    /// @note When the out-of-pool flag is enabled, because the function is
    /// called only once per DHCP message, the reservations that are in-subnet
    /// are not filtered out as there is no sufficient information regarding the
    /// selected subnet, shared network or lease types, but will be filtered out
    /// at allocation time.
    ///
    /// @param ctx Client context that contains all necessary information.
    static void findReservation(ClientContext6& ctx);

    /// @brief Attempts to find the host reservation for the client.
    ///
    /// This method attempts to find a "global" host reservation matching the
    /// client identifier.  It will return the first global reservation that
    /// matches per the configured list of host identifiers, or an empty
    /// pointer if no matches are found.
    ///
    /// @param ctx Client context holding various information about the client.
    ///
    /// @return Pointer to the reservation found, or an empty pointer.
    static ConstHostPtr findGlobalReservation(ClientContext6& ctx);

    /// @brief Creates an IPv6Resrv instance from a Lease6
    ///
    /// @param lease Reference to the Lease6
    ///
    /// @return The newly formed IPv6Resrv instance
    static IPv6Resrv makeIPv6Resrv(const Lease6& lease) {
        if (lease.type_ == Lease::TYPE_NA) {
            return (IPv6Resrv(IPv6Resrv::TYPE_NA, lease.addr_,
                              (lease.prefixlen_ ? lease.prefixlen_ : 128)));
        }

        return (IPv6Resrv(IPv6Resrv::TYPE_PD, lease.addr_, lease.prefixlen_));
    }

public:
    /// @brief Determines the preferred and valid v6 lease lifetimes.
    ///
    /// A candidate triplet for both preferred and valid lifetimes will be
    /// selected from the first class matched to the query which defines the
    /// value or from the subnet if none do. Classes are searched in the order
    /// they are assigned to the query.
    ///
    /// If the client requested a lifetime IA hint, then the
    /// lifetime values returned will be the requested values bounded by
    /// the candidate triplets.  If the client did not request a value, then
    /// it simply returns the candidate triplet's default value.
    ///
    /// @param ctx client context that passes all necessary information. See
    ///        @ref ClientContext6 for details.
    /// @param [out] preferred set to the preferred lifetime that should be used.
    /// @param [out] valid set to the valid lifetime that should be used.
    static void getLifetimes6(ClientContext6& ctx, uint32_t& preferred,
                              uint32_t& valid);
private:

    /// @brief Creates a lease and inserts it in LeaseMgr if necessary
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
    /// @param [out] callout_status callout returned by the lease6_select
    ///
    /// The following fields of the ctx structure are used:
    /// @ref ClientContext6::subnet_ Subnet the lease is allocated from
    /// @ref ClientContext6::duid_ Client's DUID
    /// @ref ClientContext6::iaid_ IAID from the IA_NA container the client sent to us
    /// @ref ClientContext6::type_ Lease type (IA, TA or PD)
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
    ///
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///         became unavailable)
    Lease6Ptr createLease6(ClientContext6& ctx,
                           const isc::asiolink::IOAddress& addr,
                           const uint8_t prefix_len,
                           hooks::CalloutHandle::CalloutNextStep& callout_status);

    /// @brief Allocates a normal, in-pool, unreserved lease from the pool.
    ///
    /// It attempts to pick a hint first, then uses allocator iteratively until
    /// an available (not used, not reserved) lease is found. In principle, it
    /// may return more than one lease, but we currently handle only one.
    /// This may change in the future.
    ///
    /// @note If reservations-out-of-pool flag is enabled, dynamic address that
    /// match reservations from within the dynamic pool will not be prevented to
    /// be assigned to any client.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    ///
    /// @return collection of newly allocated leases
    Lease6Collection allocateUnreservedLeases6(ClientContext6& ctx);

    /// @brief Allocates a normal, in-pool, unreserved lease from the pool.
    ///
    /// @note This function is called by allocateUnreservedLeases6 and it tries
    /// to allocate a lease matching hint prefix length if explicitly required.
    ///
    /// @param ctx client context that passes all necessary information. See
    ///        @ref ClientContext6 for details.
    /// @param hint_lease the hint lease that is stored in the database. It is
    ///        updated according to search_hint_lease flag.
    /// @param search_hint_lease flag which indicates if hint_lease should be
    ///        retrieved from the lease storage or if it is already retrieved.
    /// @param hint the hint address that the client provided.
    /// @param hint_prefix_length The hint prefix length that the client
    ///        provided. For NAs this value is always 128. For PDs, 0 means that
    ///        there is no hint and that any pool will suffice. The value 128
    ///        for PDs is most likely a bug in the code when calling the addHint
    ///        function with the default value for prefix_len parameter. This
    ///        value is not a valid delegated prefix length anyway so it is
    ///        treated the same as when there is no hint provided.
    /// @param original_subnet the initial subnet selected for this client
    /// @param network the shared network selected for this client (if any)
    /// @param total_attempts the total number of attempt to allocate an address
    ///        for this client. This parameter contains the accumulative value
    ///        for previous calls and current call of this function for the
    ///        lease allocation for this client (current IAID).
    /// @param subnets_with_unavail_leases the number of subnets which have no
    ///        address available for this client. This parameter contains the
    ///        accumulative value for previous calls and current call of this
    ///        function for the lease allocation for this client (current IAID).
    /// @param subnets_with_unavail_pools the number of pools which have no
    ///        address available for the client. This parameter contains the
    ///        accumulative value for previous calls and current call of this
    ///        function for the lease allocation for this client (current IAID).
    /// @param [out] callout_status callout returned by the lease6_select
    /// @param prefix_length_match type which indicates the selection criteria
    ///        for the pools relative to the provided hint prefix length. It is
    ///        used for allocating PDs only and it is ignored for any non PD
    ///        type.
    ///
    /// @return a new allocated address or null pointer if none is available
    Lease6Ptr allocateBestMatch(ClientContext6& ctx,
                                Lease6Ptr& hint_lease,
                                bool& search_hint_lease,
                                const isc::asiolink::IOAddress& hint,
                                uint8_t hint_prefix_length,
                                Subnet6Ptr original_subnet,
                                SharedNetwork6Ptr& network,
                                uint64_t& total_attempts,
                                uint64_t& subnets_with_unavail_leases,
                                uint64_t& subnets_with_unavail_pools,
                                hooks::CalloutHandle::CalloutNextStep& callout_status,
                                Allocator::PrefixLenMatchType prefix_length_match);

    /// @brief Creates new leases based on reservations.
    ///
    /// This method allocates new leases, based on host reservations.
    /// Existing leases are specified in the existing_leases
    /// parameter.  It first checks for non-global reservations.  A
    /// new lease is not created, if there is a lease for specified
    /// address on existing_leases list or there is a lease used by
    /// someone else. It last calls @c allocateGlobalReservedLeases6
    /// to accommodate subnets using global reservations.
    ///
    /// @note If reservations-out-of-pool flag is enabled, reservations from
    /// within the dynamic pool will not be checked to be assigned to the
    /// respective client.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @param existing_leases leases that are already associated with the client
    void
    allocateReservedLeases6(ClientContext6& ctx, Lease6Collection& existing_leases);

    /// @brief Creates new leases based on global reservations.
    ///
    /// This method is used by @allocateReservedLeases6, to allocate new leases based
    /// on global reservation if one exists and global reservations are enabled for
    /// the selected subnet. It differs from it's caller by looking only at the global
    /// reservation and therefore has no need to iterate over the selected subnet or it's
    /// siblings looking for host reservations.  Like it's caller, existing leases are
    /// specified in existing_leases parameter. A new lease is not created, if there is
    /// a lease for specified address on existing_leases list or there is a lease used by
    /// someone else.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @param existing_leases leases that are already associated with the client
    void
    allocateGlobalReservedLeases6(ClientContext6& ctx, Lease6Collection& existing_leases);

    /// @brief Removes leases that are reserved for someone else.
    ///
    /// Goes through the list specified in existing_leases and removes those that
    /// are reserved by someone else or do not belong to an allowed pool.
    /// The removed leases are added to the ctx.removed_leases_ collection.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @param existing_leases [in/out] leases that should be checked
    void
    removeNonmatchingReservedLeases6(ClientContext6& ctx,
                                     Lease6Collection& existing_leases);

    /// @brief Removes leases that are reserved for someone else.
    ///
    /// Simplified version of removeNonmatchingReservedLeases6 to be
    /// used when host reservations are disabled.
    ///
    /// @param ctx client context that contains all details (subnet, client-id, etc.)
    /// @param existing_leases [in/out] leases that should be checked
    void
    removeNonmatchingReservedNoHostLeases6(ClientContext6& ctx,
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
    /// @param [out] callout_status callout returned by the lease6_select
    ///
    /// The following parameters are used from the ctx structure:
    /// @ref ClientContext6::subnet_ Subnet the lease is allocated from
    /// @ref ClientContext6::duid_ Client's DUID
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
    ///
    /// @throw BadValue if trying to recycle lease that is still valid
    Lease6Ptr
    reuseExpiredLease(Lease6Ptr& expired,
                      ClientContext6& ctx,
                      uint8_t prefix_len,
                      hooks::CalloutHandle::CalloutNextStep& callout_status);

    /// @brief Updates FQDN and Client's Last Transmission Time
    /// for a collection of leases.
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
    ///
    /// @return true if removed (false otherwise)
    static bool
    removeLeases(Lease6Collection& container,
                 const asiolink::IOAddress& addr);

    /// @brief Extends specified IPv6 lease
    ///
    /// This method attempts to extend the lease. It will call the lease6_renew
    /// or lease6_rebind hooks (depending on the client's message specified in
    /// ctx.query). The lease will be extended in LeaseMgr, unless the hooks
    /// library will set the skip flag.  The old lease is added to the
    /// the context's changed_leases_ list which allows the server to make
    /// decisions regarding DNS updates.
    ///
    /// @param ctx client context that passes all necessary information. See
    ///        @ref ClientContext6 for details.
    /// @param lease IPv6 lease to be extended.
    void extendLease6(ClientContext6& ctx, Lease6Ptr lease);

    /// @brief Reclamation mode used by the variants of @c reclaimExpiredLease
    /// methods.
    ///
    /// The following operations are supported:
    /// - remove lease upon reclamation,
    /// - update lease's state upon reclamation to 'expired-reclaimed',
    /// - leave the lease in the database unchanged.
    enum DbReclaimMode {
        DB_RECLAIM_REMOVE,
        DB_RECLAIM_UPDATE,
        DB_RECLAIM_LEAVE_UNCHANGED
    };

    /// @brief Reclaim DHCPv4 or DHCPv6 lease with updating lease database.
    ///
    /// This method is called by the lease reclamation routine to reclaim the
    /// lease and update the lease database according to the value of the
    /// @c remove_lease parameter.
    ///
    /// @param lease Pointer to the DHCPv4 or DHCPv6 lease.
    /// @param remove_lease A boolean flag indicating if the lease should be
    /// removed from the lease database (if true) upon reclamation.
    /// @param callout_handle Pointer to the callout handle.
    /// @tparam LeasePtrPtr Lease type, i.e. @c Lease4Ptr or @c Lease6Ptr.
    template<typename LeasePtrType>
    void reclaimExpiredLease(const LeasePtrType& lease,
                             const bool remove_lease,
                             const hooks::CalloutHandlePtr& callout_handle);

    /// @brief Reclaim DHCPv4 or DHCPv6 lease without updating lease database.
    ///
    /// This method is called by the methods allocating leases, when the lease
    /// being allocated needs to be first reclaimed. These methods update the
    /// lease database on their own, so this reclamation method doesn't update
    /// the database on reclamation.
    ///
    /// @param lease Pointer to the DHCPv4 or DHCPv6 lease.
    /// @param callout_handle Pointer to the callout handle.
    /// @tparam LeasePtrType Lease type, i.e. @c Lease4Ptr or @c Lease6Ptr.
    template<typename LeasePtrType>
    void reclaimExpiredLease(const LeasePtrType& lease,
                             const hooks::CalloutHandlePtr& callout_handle);

    /// @brief Reclaim DHCPv6 lease.
    ///
    /// This method variant accepts the @c reclaim_mode parameter which
    /// controls if the reclaimed lease should be left in the database with
    /// no change or if it should be removed or updated.
    ///
    /// @param lease Pointer to the DHCPv6 lease.
    /// @param reclaim_mode Indicates what the method should do with the reclaimed
    /// lease in the lease database.
    /// @param callout_handle Pointer to the callout handle.
    void reclaimExpiredLease(const Lease6Ptr& lease,
                             const DbReclaimMode& reclaim_mode,
                             const hooks::CalloutHandlePtr& callout_handle);

    /// @brief Reclaim DHCPv4 lease.
    ///
    /// This method variant accepts the @c reclaim_mode parameter which
    /// controls if the reclaimed lease should be left in the database with
    /// no change or if it should be removed or updated.
    ///
    /// @param lease Pointer to the DHCPv4 lease.
    /// @param reclaim_mode Indicates what the method should do with the reclaimed
    /// lease in the lease database.
    /// @param callout_handle Pointer to the callout handle.
    void reclaimExpiredLease(const Lease4Ptr& lease,
                             const DbReclaimMode& reclaim_mode,
                             const hooks::CalloutHandlePtr& callout_handle);

    /// @brief Marks lease as reclaimed in the database.
    ///
    /// This method is called internally by the leases reclamation routines.
    /// Depending on the value of the @c remove_lease parameter this method
    /// will delete the reclaimed lease from the database or set its sate
    /// to "expired-reclaimed". In the latter case it will also clear the
    /// FQDN information.
    ///
    /// This method may throw exceptions if the operation on the lease database
    /// fails for any reason.
    ///
    /// @param lease Pointer to the lease.
    /// @param remove_lease Boolean flag indicating if the lease should be
    /// removed from the database (if true).
    /// @param lease_update_fun Pointer to the function in the @c LeaseMgr to
    /// be used to update the lease if the @c remove_lease is set to false.
    ///
    /// @tparam LeasePtrType One of the @c Lease6Ptr or @c Lease4Ptr.
    template<typename LeasePtrType>
    void reclaimLeaseInDatabase(const LeasePtrType& lease,
                                const bool remove_lease,
                                const std::function<void (const LeasePtrType&)>&
                                lease_update_fun) const;

    /// @anchor reclaimDeclinedLease4
    /// @brief Conducts steps necessary for reclaiming declined IPv4 lease.
    ///
    /// These are the additional steps required when recovering a declined lease:
    /// - bump decline recovered stat
    /// - log lease recovery
    /// - call lease4_recover hook
    ///
    /// @param lease Lease to be reclaimed from Declined state
    ///
    /// @return true if it's ok to remove the lease (false = hooks status says
    ///         to keep it)
    bool reclaimDeclined(const Lease4Ptr& lease);

    /// @anchor reclaimDeclinedLease6
    /// @brief Conducts steps necessary for reclaiming declined IPv6 lease.
    ///
    /// These are the additional steps required when recovering a declined lease:
    /// - bump decline recovered stat
    /// - log lease recovery
    /// - call lease6_recover hook
    ///
    /// @param lease Lease to be reclaimed from Declined state
    ///
    /// @return true if it's ok to remove the lease (false = hooks status says
    ///         to keep it)
    bool reclaimDeclined(const Lease6Ptr& lease);

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
    struct ClientContext4 : public boost::noncopyable {
        /// @brief Indicates if early global reservation is enabled.
        ///
        /// This caches the early-global-reservations-lookup value.
        bool early_global_reservations_lookup_;

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

        /// @brief If not zero, then we will allocate on DISCOVER for this
        /// amount of time.
        uint32_t offer_lft_;

        /// @brief A pointer to an old lease that the client had before update.
        Lease4Ptr old_lease_;

        /// @brief A pointer to a newly allocated lease.
        Lease4Ptr new_lease_;

        /// @brief Holds a map of hosts belonging to the client within different
        /// subnets.
        ///
        /// Multiple hosts may appear when the client belongs to a shared
        /// network.
        std::map<SubnetID, ConstHostPtr> hosts_;

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

        /// @brief A list holding host identifiers extracted from a message
        /// received by the server.
        IdentifierList host_identifiers_;

        /// @brief True when the address DHCPREQUEST'ed by client is not within
        /// a dynamic pool the server knows about.
        bool unknown_requested_addr_;

        /// @brief Returns the set of DDNS behavioral parameters based on
        /// the selected subnet.
        ///
        /// If there is no selected subnet (i.e. subnet_ is empty), the
        /// returned set will contain default values.
        ///
        /// @return pointer to a DdnsParams instance
        DdnsParamsPtr getDdnsParams();


        /// @brief Convenience function adding host identifier into
        /// @ref host_identifiers_ list.
        ///
        /// @param id_type Identifier type.
        /// @param identifier Identifier value.
        void addHostIdentifier(const Host::IdentifierType& id_type,
                               const std::vector<uint8_t>& identifier) {
            host_identifiers_.push_back(IdentifierPair(id_type, identifier));
        }

        /// @brief Returns host for currently selected subnet.
        ///
        /// If there is no such host and global reservations are enabled
        /// returns the global host.
        ///
        /// @return Pointer to the host object.
        ConstHostPtr currentHost() const;

        /// @brief Returns global host reservation if there is one
        ///
        /// If the current subnet's reservations-global is true and
        /// there is a global host (i.e. reservation belonging to
        /// the global subnet), return it.  Otherwise return an
        /// empty pointer.
        ///
        /// @return Pointer to the host object.
        ConstHostPtr globalHost() const;

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
        /// @param offer_lft When not zero, leases ARE allocated on DISCOVER and use
        /// this value as lease lifetime.
        ClientContext4(const Subnet4Ptr& subnet, const ClientIdPtr& clientid,
                       const HWAddrPtr& hwaddr,
                       const asiolink::IOAddress& requested_addr,
                       const bool fwd_dns_update, const bool rev_dns_update,
                       const std::string& hostname, const bool fake_allocation,
                       const uint32_t offer_lft = 0);
        private:
            /// @brief Contains a pointer to the DDNS parameters for selected
            /// subnet.  Set by the first call to getDdnsParams() made when
            /// the context has a selected subnet (i.e. subnet_ is not empty).
            DdnsParamsPtr ddns_params_;
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
    /// Attempts to find appropriate host reservation in HostMgr. If found, it
    /// is set in the @ref ClientContext4::hosts_.
    ///
    /// @note When the out-of-pool flag is enabled, because the function is
    /// called only once per DHCP message, the reservations that are in-subnet
    /// are not filtered out as there is no sufficient information regarding the
    /// selected subnet or shared network, but will be filtered out at
    /// allocation time.
    ///
    /// @param ctx Client context holding various information about the client.
    static void findReservation(ClientContext4& ctx);

    /// @brief Attempts to find the host reservation for the client.
    ///
    /// This method attempts to find a "global" host reservation matching the
    /// client identifier.  It will return the first global reservation that matches
    /// per the configured list of host identifiers, or an empty pointer if no
    /// matches are found.
    ///
    /// @param ctx Client context holding various information about the client.
    ///
    /// @return Pointer to the reservation found, or an empty pointer.
    static ConstHostPtr findGlobalReservation(ClientContext4& ctx);

    /// @brief Returns the valid lifetime based on the v4 context
    ///
    /// If the client query is a BOOTP query, the value returned will
    /// be Lease::INFINITY_LFT.
    ///
    /// Otherwise, a candidate triplet will be selected from the first
    /// class matched to the query which defines it or from the subnet
    /// if none do. Classes are searched in the order they are assigned
    /// to the query.
    ///
    /// If the client requested a lifetime value via DHCP option 51, then the
    /// lifetime value returned will be the requested value bounded by
    /// the candidate triplet.  If the client did not request a value, then
    /// it simply returns the candidate triplet's default value.
    ///
    /// @param ctx Client context holding various information about the client.
    /// @return unsigned integer value of the valid lifetime to use.
    static uint32_t getValidLft(const ClientContext4& ctx);

    /// @brief Returns the offer lifetime based on the v4 context
    ///
    /// If the client query is a BOOTP query or something other than
    /// DHCPDISCOVER, return 0.
    ///
    /// Otherwise, the value will be selected from the first
    /// class matched to the query which defines it or from the subnet
    /// if none do. Classes are searched in the order they are assigned
    /// to the query.
    ///
    /// @param ctx Client context holding various information about the client.
    /// @return unsigned integer value of the offer lifetime to use.
    static uint32_t getOfferLft(const ClientContext4& ctx);

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
    /// @throw various exceptions if the allocation goes wrong.
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
    /// @param [out] callout_status callout returned by the lease6_select
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
    ///
    /// @return allocated lease (or NULL in the unlikely case of the lease just
    ///        become unavailable)
    Lease4Ptr createLease4(const ClientContext4& ctx,
                           const isc::asiolink::IOAddress& addr,
                           hooks::CalloutHandle::CalloutNextStep& callout_status);

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
    /// @param [out] callout_status callout returned by the lease4_select
    ///
    /// @return Updated lease instance.
    ///
    /// @throw BadValue if trying to reuse a lease which is still valid or
    /// when the provided parameters are invalid.
    Lease4Ptr
    reuseExpiredLease4(Lease4Ptr& expired, ClientContext4& ctx,
                       hooks::CalloutHandle::CalloutNextStep& callout_status);

    /// @brief Allocates the lease by replacing an existing lease.
    ///
    /// This method checks if the lease database contains the lease for
    /// the specified address. If the lease exists and has expired, it
    /// reuses the expired lease. If the lease doesn't exist, it creates
    /// the new lease.
    ///
    /// @param address Requested address for which the lease should be
    /// allocated.
    /// @param ctx Client context holding the data extracted from the
    /// client's message.
    /// @param [out] callout_status callout returned by the lease4_select
    ///
    /// @return A pointer to the allocated lease or NULL if the allocation
    /// was not successful.
    Lease4Ptr
    allocateOrReuseLease4(const asiolink::IOAddress& address,
                          ClientContext4& ctx,
                          hooks::CalloutHandle::CalloutNextStep& callout_status);

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
    /// @return True if there was a significant (e.g. other than cltt) change,
    /// false otherwise.
    bool updateLease4Information(const Lease4Ptr& lease,
                                 ClientContext4& ctx) const;

protected:
    /// @brief Stores additional client query parameters on a V4 lease
    ///
    /// Extended features such as LeaseQuery require additional parameters
    /// to be stored for each lease, than we would otherwise retain.
    /// This function adds that information to the lease's user-context.
    /// (Note it is protected to facilitate unit testing).
    ///
    /// @warning This method doesn't check if the pointer to the lease is
    /// valid nor if the subnet to the pointer in the @c ctx is valid.
    /// The caller is responsible for making sure that they are valid.
    ///
    /// @param [out] lease A pointer to the lease to be updated.
    /// @param ctx A context containing information from the server about the
    /// client and its message.
    /// @return True if there was a significant (e.g. other than cltt) change,
    /// false otherwise.
    bool updateLease4ExtendedInfo(const Lease4Ptr& lease,
                                  const ClientContext4& ctx) const;

    /// @brief Stores additional client query parameters on a V6 lease
    ///
    /// Extended features such as LeaseQuery and Reconfigure require
    /// additional parameters to be stored for each lease, than we would
    /// otherwise retain.  This function adds that information to the
    /// lease's user-context.
    /// (Note it is protected to facilitate unit testing).
    ///
    /// @warning This method doesn't check if the pointer to the lease is
    /// valid nor if the subnet to the pointer in the @c ctx is valid.
    /// The caller is responsible for making sure that they are valid.
    ///
    /// @param [out] lease A pointer to the lease to be updated.
    /// @param ctx A context containing information from the server about the
    /// client and its message.
    void updateLease6ExtendedInfo(const Lease6Ptr& lease,
                                  const ClientContext6& ctx) const;

    /// @brief Clear extended info from a reclaimed V4 lease
    ///
    /// @param [out] lease A pointer to the reclaimed lease.
    void clearReclaimedExtendedInfo(const Lease4Ptr& lease) const;

    /// @brief Clear extended info from a reclaimed V6 lease
    ///
    /// @param [out] lease A pointer to the reclaimed lease.
    void clearReclaimedExtendedInfo(const Lease6Ptr& lease) const;

private:

    /// @brief Try to reuse an already allocated lease.
    ///
    /// This function computes and sets when acceptable the reusable
    /// valid lifetime of an already allocated lease.
    /// This uses the cache-threshold and cache-max-age parameters.
    ///
    /// A not zero value for the reusable valid lifetime means the
    /// lease can reuse i.e.:
    ///  - the lease is not updated in the lease database.
    ///  - the previous value of the lease can be returned to the client.
    ///
    /// @param [in,out] lease A pointer to the lease to be updated.
    /// @param subnet A pointer to the lease subnet.
    void setLeaseReusable(const Lease4Ptr& lease,
                          const ClientContext4& ctx) const;

    /// @brief Try to reuse an already allocated lease.
    ///
    /// This function computes and sets when acceptable the reusable
    /// valid lifetime of an already allocated lease.
    /// This uses the cache-threshold and cache-max-age parameters.
    ///
    /// A not zero value for the reusable valid lifetime means the
    /// lease can reuse i.e.:
    ///  - the lease is not updated in the lease database.
    ///  - the previous value of the lease can be returned to the client.
    ///
    /// @param [in,out] lease A pointer to the lease to be updated.
    /// @param current_preferred_lft Current preferred lease lifetime.
    /// @param subnet A pointer to the lease subnet.
    void setLeaseReusable(const Lease6Ptr& lease,
                          uint32_t current_preferred_lft,
                          const ClientContext6& ctx) const;

private:

    /// @brief Number of consecutive DHCPv4 leases' reclamations after
    /// which there are still expired leases in the database.
    uint16_t incomplete_v4_reclamations_;

    /// @brief Number of consecutive DHCPv6 leases' reclamations after
    /// which there are still expired leases in the database.
    uint16_t incomplete_v6_reclamations_;

public:

    /// @brief Get the read-write mutex.
    ///
    /// This read-write mutex is used to make reclamation exclusive
    /// of multi-threaded packet processing.
    /// @return A reference to the read-write mutex.
    isc::util::ReadWriteMutex& getReadWriteMutex() {
        return (rw_mutex_);
    }

    /// @brief The read-write mutex.
    isc::util::ReadWriteMutex rw_mutex_;

    /// @brief Generates a label for subnet or shared-network from subnet
    ///
    /// Creates a string for the subnet and its ID for stand alone subnets
    /// or the shared-network and its name if the given subnet belongs to a
    /// shared-network.
    ///
    /// @param subnet pointer to the source subnet
    /// @return string containing the generated label
    static std::string labelNetworkOrSubnet(SubnetPtr subnet);
};

/// @brief A pointer to the @c AllocEngine object.
typedef boost::shared_ptr<AllocEngine> AllocEnginePtr;

}  // namespace dhcp
}  // namespace isc

#endif // ALLOC_ENGINE_H
