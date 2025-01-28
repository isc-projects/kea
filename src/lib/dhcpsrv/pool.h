// Copyright (C) 2012-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef POOL_H
#define POOL_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/user_context.h>
#include <dhcp/classify.h>
#include <dhcp/option6_pdexclude.h>
#include <dhcpsrv/allocation_state.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/d2_client_cfg.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/ip_range_permutation.h>
#include <util/bigints.h>
#include <util/optional.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace isc {
namespace dhcp {

/// @brief base class for Pool4 and Pool6
///
/// Stores information about pool of IPv4 or IPv6 addresses.
/// That is a basic component of a configuration.
class Pool : public isc::data::UserContext, public isc::data::CfgToElement {

public:
    /// @note:
    /// PoolType enum was removed. Please use Lease::Type instead

    /// @brief Returns Pool-id
    ///
    /// Pool-id is an unique value that can be used to identify a pool within a
    /// subnet or shared network.
    ///
    /// @return pool-id value
    uint64_t getID() const {
        return (id_);
    }

    /// @brief Sets Pool-id
    ///
    /// Pool-id is an unique value that can be used to identify a pool within a
    /// subnet or shared network.
    ///
    /// @param id value to be set
    void setID(const uint64_t id) {
        id_ = id;
    }

    /// @brief Returns the first address in a pool.
    ///
    /// @return first address in a pool
    const isc::asiolink::IOAddress& getFirstAddress() const {
        return (first_);
    }

    /// @brief Returns the last address in a pool.
    /// @return last address in a pool
    const isc::asiolink::IOAddress& getLastAddress() const {
        return (last_);
    }

    /// @brief Checks if a given address is in the range.
    ///
    /// @return true, if the address is in pool
    bool inRange(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns pool type (v4, v6 non-temporary, v6 temp, v6 prefix)
    /// @return returns pool type
    Lease::Type getType() const {
        return (type_);
    }

    /// @brief returns textual representation of the pool
    ///
    /// @return textual representation
    virtual std::string toText() const;

    /// @brief virtual destructor
    ///
    /// We need Pool to be a polymorphic class, so we could dynamic cast
    /// from PoolPtr to Pool6Ptr if we need to. A class becomes polymorphic,
    /// when there is at least one virtual method.
    virtual ~Pool() = default;

    /// @brief Returns the number of all leases in this pool.
    ///
    /// Note that this is the upper bound, assuming that no leases are used
    /// and there are no host reservations. This is just a theoretical calculation.
    /// @return number of possible leases in this pool
    isc::util::uint128_t getCapacity() const {
        return (capacity_);
    }

    /// @brief Returns pointer to the option data configuration for this pool.
    CfgOptionPtr getCfgOption() {
        return (cfg_option_);
    }

    /// @brief Returns const pointer to the option data configuration for
    /// this pool.
    ConstCfgOptionPtr getCfgOption() const {
        return (cfg_option_);
    }

    /// @brief Checks whether this pool supports client that belongs to
    /// specified classes.
    ///
    /// @param client_classes list of all classes the client belongs to
    /// @return true if client can be supported, false otherwise
    bool clientSupported(const ClientClasses& client_classes) const;

    /// @brief Adds class clas_name to the allowed client classes list.
    ///
    /// @param class_name client class to be supported by this network
    void allowClientClass(const isc::dhcp::ClientClass& class_name);

    /// @brief Returns the list of allowed client classes.
    const ClientClasses& getClientClasses() const {
        return (client_classes_);
    }

    /// @brief Returns the mutable list of allowed client classes.
    ClientClasses& getMutableClientClasses() {
        return (client_classes_);
    }

    /// @brief Adds class class_name to the additional classes list.
    ///
    /// @param class_name client class to add
    void addAdditionalClass(const ClientClass& class_name);

    /// @brief Returns the additional classes list.
    const ClientClasses& getAdditionalClasses() const {
        return (additional_classes_);
    }

    /// @brief Returns the mutable additional classes list.
    ClientClasses& getMutableAdditionalClasses() {
        return (additional_classes_);
    }

    /// @brief Returns pool-specific allocation state.
    ///
    /// The actual type of the state depends on the allocator type.
    ///
    /// @return allocation state.
    AllocationStatePtr getAllocationState() const {
        return (allocation_state_);
    }

    /// @brief Sets pool-specific allocation state.
    ///
    /// @param allocation_state allocation state instance.
    void setAllocationState(const AllocationStatePtr& allocation_state) {
        allocation_state_ = allocation_state;
    }

    /// @brief Unparse a pool object.
    ///
    /// @return A pointer to unparsed pool configuration.
    virtual data::ElementPtr toElement() const;


    /// @brief Returns ddns-send-updates
    util::Optional<bool>
    getDdnsSendUpdates() const {
        return (ddns_send_updates_);
    }

    /// @brief Sets new ddns-send-updates
    ///
    /// @param ddns_send_updates New value to use.
    void setDdnsSendUpdates(const util::Optional<bool>& ddns_send_updates) {
        ddns_send_updates_ = ddns_send_updates;
    }

    /// @brief Returns ddns-override-no-update
    util::Optional<bool>
    getDdnsOverrideNoUpdate() const {
        return (ddns_override_no_update_);
    }

    /// @brief Sets new ddns-override-no-update
    ///
    /// @param ddns_override_no_update New value to use.
    void setDdnsOverrideNoUpdate(const util::Optional<bool>& ddns_override_no_update) {
        ddns_override_no_update_ = ddns_override_no_update;
    }

    /// @brief Returns ddns-override-client-update
    util::Optional<bool>
    getDdnsOverrideClientUpdate() const {
        return (ddns_override_client_update_);
    }

    /// @brief Sets new ddns-override-client-update
    ///
    /// @param ddns_override_client_update New value to use.
    void setDdnsOverrideClientUpdate(const util::Optional<bool>&
                                     ddns_override_client_update) {
        ddns_override_client_update_ = ddns_override_client_update;
    }

    /// @brief Returns ddns-replace-client-name-mode
    util::Optional<D2ClientConfig::ReplaceClientNameMode>
    getDdnsReplaceClientNameMode() const {
        return (ddns_replace_client_name_mode_);
    }

    /// @brief Sets new ddns-replace-client-name-mode
    ///
    /// @param ddns_replace_client_name_mode New value to use.
    void
    setDdnsReplaceClientNameMode(const util::Optional<D2ClientConfig::ReplaceClientNameMode>&
                                 ddns_replace_client_name_mode) {
        ddns_replace_client_name_mode_ = ddns_replace_client_name_mode;
    }

    /// @brief Returns ddns-generated-prefix
    util::Optional<std::string>
    getDdnsGeneratedPrefix() const {
        return (ddns_generated_prefix_);
    }

    /// @brief Sets new ddns-generated-prefix
    ///
    /// @param ddns_generated_prefix New value to use.
    void setDdnsGeneratedPrefix(const util::Optional<std::string>& ddns_generated_prefix) {
        ddns_generated_prefix_ = ddns_generated_prefix;
    }

    /// @brief Returns ddns-qualifying-suffix
    util::Optional<std::string>
    getDdnsQualifyingSuffix() const {
        return (ddns_qualifying_suffix_);
    }

    /// @brief Sets new ddns-qualifying-suffix
    ///
    /// @param ddns_qualifying_suffix New value to use.
    void setDdnsQualifyingSuffix(const util::Optional<std::string>& ddns_qualifying_suffix) {
        ddns_qualifying_suffix_ = ddns_qualifying_suffix;
    }

    /// @brief Returns ddns-update-on-renew
    util::Optional<bool>
    getDdnsUpdateOnRenew() const {
        return (ddns_update_on_renew_);
    }

    /// @brief Sets new ddns-update-on-renew
    ///
    /// @param ddns_update_on_renew New value to use.
    void setDdnsUpdateOnRenew(const util::Optional<bool>& ddns_update_on_renew) {
        ddns_update_on_renew_ = ddns_update_on_renew;
    }

    /// @brief Returns ddns-conflict-resolution-mode
    util::Optional<std::string>
    getDdnsConflictResolutionMode() const {
        return (ddns_conflict_resolution_mode_);
    }

    /// @brief Sets new ddns-conflict-resolution-mode
    ///
    /// @param ddns_conflict_resolution_mode New value to use.
    void setDdnsConflictResolutionMode(const util::Optional<std::string>& ddns_conflict_resolution_mode) {
        ddns_conflict_resolution_mode_ = ddns_conflict_resolution_mode;
    }


    /// @brief Returns ddns-ttl-percent
    util::Optional<double>
    getDdnsTtlPercent() const {
        return (ddns_ttl_percent_);
    }

    /// @brief Sets new ddns-ttl-percent
    ///
    /// @param ddns_ttl_percent New value to use.
    void setDdnsTtlPercent(const util::Optional<double>& ddns_ttl_percent) {
        ddns_ttl_percent_ = ddns_ttl_percent;
    }

    /// @brief Returns ddns-ttl
    util::Optional<uint32_t>
    getDdnsTtl() const {
        return (ddns_ttl_);
    }

    /// @brief Sets new ddns-ttl
    ///
    /// @param ddns_ttl New value to use.
    void setDdnsTtl(const util::Optional<uint32_t>& ddns_ttl) {
        ddns_ttl_ = ddns_ttl;
    }

    /// @brief Returns ddns-ttl-min
    util::Optional<uint32_t>
    getDdnsTtlMin() const {
        return (ddns_ttl_min_);
    }

    /// @brief Sets new ddns-ttl-min
    ///
    /// @param ddns_ttl_min New value to use.
    void setDdnsTtlMin(const util::Optional<uint32_t>& ddns_ttl_min) {
        ddns_ttl_min_ = ddns_ttl_min;
    }

    /// @brief Returns ddns-ttl-max
    util::Optional<uint32_t>
    getDdnsTtlMax() const {
        return (ddns_ttl_max_);
    }

    /// @brief Sets new ddns-ttl-max
    ///
    /// @param ddns_ttl_max New value to use.
    void setDdnsTtlMax(const util::Optional<uint32_t>& ddns_ttl_max) {
        ddns_ttl_max_ = ddns_ttl_max;
    }

    /// @brief Return the char set regexp used to sanitize client hostnames.
    util::Optional<std::string>
    getHostnameCharSet() const {
        return (hostname_char_set_);
    }

    /// @brief Sets new hostname-char-set
    ///
    /// @param hostname_char_set New value to use.
    void setHostnameCharSet(const util::Optional<std::string>& hostname_char_set) {
        hostname_char_set_ = hostname_char_set;
    }

    /// @brief Return the invalid char replacement used to sanitize client hostnames.
    util::Optional<std::string>
    getHostnameCharReplacement() const {
        return (hostname_char_replacement_);
    }

    /// @brief Sets new hostname-char-replacement
    ///
    /// @param hostname_char_replacement New value to use.
    void setHostnameCharReplacement(const util::Optional<std::string>&
                                    hostname_char_replacement) {
        hostname_char_replacement_ = hostname_char_replacement;
    }

    /// @brief Checks if any of the DDNS parameters has a value.
    ///
    /// @return True if any of the DDNS parameters are specified.
    bool hasDdnsParameters() const;

protected:

    /// @brief protected constructor
    ///
    /// This constructor is protected to prevent anyone from instantiating
    /// Pool class directly. Instances of Pool4 and Pool6 should be created
    /// instead.
    ///
    /// @param type type of lease that will be served from this pool
    /// @param first first address of a range
    /// @param last last address of a range
    Pool(Lease::Type type,
         const isc::asiolink::IOAddress& first,
         const isc::asiolink::IOAddress& last);

    /// @brief pool-id
    ///
    /// This id is an unique value that can be used to identify a pool within a
    /// subnet or shared network.
    uint64_t id_;

    /// @brief The first address in a pool
    isc::asiolink::IOAddress first_;

    /// @brief The last address in a pool
    isc::asiolink::IOAddress last_;

    /// @brief defines a lease type that will be served from this pool
    Lease::Type type_;

    /// @brief Stores number of possible leases.
    ///
    /// This could be calculated on the fly, but the calculations are somewhat
    /// involved, so it is more efficient to calculate it once and just store
    /// the result. Note that for very large pools, the number is capped at
    /// max value of uint64_t.
    isc::util::uint128_t capacity_;

    /// @brief Pointer to the option data configuration for this pool.
    CfgOptionPtr cfg_option_;

    /// @brief List of client classes allowed to use this pool.
    ///
    /// If not empty, only clients belonging to at least one of the classes
    /// in this list will be allowed to use this particular pool.  By default
    /// the list is empty which means that any client is allowed, regardless
    /// of its class membership.
    ClientClasses client_classes_;

    /// @brief Additional classes
    ///
    /// @ref isc::dhcp::Network::additional_classes_
    ClientClasses additional_classes_;

    /// @brief Pointer to the user context (may be NULL)
    data::ConstElementPtr user_context_;

    /// @brief Holds pool-specific allocation state.
    AllocationStatePtr allocation_state_;

    /// @brief Should Kea perform DNS updates. Used to provide scoped enabling
    /// and disabling of updates.
    util::Optional<bool> ddns_send_updates_;

    /// @brief Should Kea perform updates, even if client requested no updates.
    /// Overrides the client request for no updates via the N flag.
    util::Optional<bool> ddns_override_no_update_;

    /// @brief Should Kea perform updates, even if client requested delegation.
    util::Optional<bool> ddns_override_client_update_;

    /// @brief How Kea should handle the domain-name supplied by the client.
    util::Optional<D2ClientConfig::ReplaceClientNameMode> ddns_replace_client_name_mode_;

    /// @brief Prefix Kea should use when generating domain-names.
    util::Optional<std::string> ddns_generated_prefix_;

    /// @brief Suffix Kea should use when to qualify partial domain-names.
    util::Optional<std::string> ddns_qualifying_suffix_;

    /// @brief Should Kea perform updates when leases are extended
    util::Optional<bool> ddns_update_on_renew_;

    /// @brief DDNS conflict resolution mode
    util::Optional<std::string> ddns_conflict_resolution_mode_;

    /// @brief Percentage of the lease lifetime to use for DNS TTL.
    util::Optional<double> ddns_ttl_percent_;

    /// @brief Explicit value to use for DNS TTL.
    util::Optional<uint32_t> ddns_ttl_;

    /// @brief Minimum value to use for DNS TTL.
    util::Optional<uint32_t> ddns_ttl_min_;

    /// @brief Maximum value to use for DNS TTL.
    util::Optional<uint32_t> ddns_ttl_max_;

    /// @brief Regular expression describing invalid characters for client
    /// hostnames.
    util::Optional<std::string> hostname_char_set_;

    /// @brief A string to replace invalid characters when scrubbing hostnames.
    /// Meaningful only if hostname_char_set_ is not empty.
    util::Optional<std::string> hostname_char_replacement_;
};

class Pool4;

/// @brief a pointer an IPv4 Pool
typedef boost::shared_ptr<Pool4> Pool4Ptr;

/// @brief Pool information for IPv4 addresses
///
/// It holds information about pool4, i.e. a range of IPv4 address space that
/// is configured for DHCP allocation.
class Pool4 : public Pool {
public:
    /// @brief the constructor for Pool4 "min-max" style definition
    ///
    /// @param first the first address in a pool
    /// @param last the last address in a pool
    Pool4(const isc::asiolink::IOAddress& first,
          const isc::asiolink::IOAddress& last);

    /// @brief the constructor for Pool4 "prefix/len" style definition
    ///
    /// @param prefix specifies prefix of the pool
    /// @param prefix_len specifies length of the prefix of the pool
    Pool4(const isc::asiolink::IOAddress& prefix,
          uint8_t prefix_len);

    /// @brief Factory function for creating an instance of the @c Pool4.
    ///
    /// This function should be used to create an instance of the pool
    /// within a hooks library in cases when the library may be unloaded
    /// before the object is destroyed. This ensures that the ownership
    /// of the object by the Kea process is retained.
    ///
    /// @param first the first address in a pool
    /// @param last the last address in a pool
    ///
    /// @return Pointer to the @c Pool4 instance.
    static Pool4Ptr create(const isc::asiolink::IOAddress& first,
                           const isc::asiolink::IOAddress& last);

    /// @brief Factory function for creating an instance of the @c Pool4.
    ///
    /// This function should be used to create an instance of the pool
    /// within a hooks library in cases when the library may be unloaded
    /// before the object is destroyed. This ensures that the ownership
    /// of the object by the Kea process is retained.
    ///
    /// @param prefix specifies prefix of the pool.
    /// @param prefix_len specifies length of the prefix of the pool.
    ///
    /// @return Pointer to the @c Pool4 instance.
    static Pool4Ptr create(const isc::asiolink::IOAddress& prefix,
                           uint8_t prefix_len);

    /// @brief Unparse a Pool4 object.
    ///
    /// @return A pointer to unparsed Pool4 configuration.
    virtual data::ElementPtr toElement() const;
};

class Pool6;

/// @brief a pointer an IPv6 Pool
typedef boost::shared_ptr<Pool6> Pool6Ptr;

/// @brief Pool information for IPv6 addresses and prefixes
///
/// It holds information about pool6, i.e. a range of IPv6 address space that
/// is configured for DHCP allocation.
class Pool6 : public Pool {
public:

    /// @brief the constructor for Pool6 "min-max" style definition
    ///
    /// @throw BadValue if PD is define (PD can be only prefix/len)
    ///
    /// @param type type of the pool (IA or TA)
    /// @param first the first address in a pool
    /// @param last the last address in a pool
    Pool6(Lease::Type type, const isc::asiolink::IOAddress& first,
          const isc::asiolink::IOAddress& last);

    /// @brief the constructor for Pool6 "prefix/len" style definition
    ///
    /// For addressed, this is just a prefix/len definition. For prefixes,
    /// there is one extra additional parameter delegated_len. It specifies
    /// a size of delegated prefixes that the pool will be split into. For
    /// example pool 2001:db8::/56, delegated_len=64 means that there is a
    /// pool 2001:db8::/56. It will be split into 256 prefixes of length /64,
    /// e.g. 2001:db8:0:1::/64, 2001:db8:0:2::/64 etc.
    ///
    /// Naming convention:
    /// A smaller prefix length yields a shorter prefix which describes a larger
    /// set of addresses. A larger length yields a longer prefix which describes
    /// a smaller set of addresses.
    ///
    /// Obviously, prefix_len must define shorter or equal prefix length than
    /// delegated_len, so prefix_len <= delegated_len. Note that it is slightly
    /// confusing: bigger (larger) prefix actually has smaller prefix length,
    /// e.g. /56 is a bigger prefix than /64, but has shorter (smaller) prefix
    /// length.
    ///
    /// @throw BadValue if delegated_len is defined for non-PD types or
    ///        when delegated_len < prefix_len
    ///
    /// @param type type of the pool (IA, TA or PD)
    /// @param prefix specifies prefix of the pool
    /// @param prefix_len specifies prefix length of the pool
    /// @param delegated_len specifies length of the delegated prefixes
    Pool6(Lease::Type type, const isc::asiolink::IOAddress& prefix,
          uint8_t prefix_len, uint8_t delegated_len = 128);

    /// @brief Constructor for DHCPv6 prefix pool with an excluded prefix.
    ///
    /// If @c excluded_prefix is equal to '::' and the @c excluded_prefix_len
    /// is equal to 0, the excluded prefix is assumed to be unspecified for
    /// the pool. In this case, the server will not send the Prefix Exclude
    /// option to a client.
    ///
    /// @param prefix specified a prefix of the pool.
    /// @param prefix_len specifies prefix length of the pool.
    /// @param delegated_len specifies length of the delegated prefixes.
    /// @param excluded_prefix specifies an excluded prefix as per RFC6603.
    /// @param excluded_prefix_len specifies length of an excluded prefix.
    Pool6(const asiolink::IOAddress& prefix, const uint8_t prefix_len,
          const uint8_t delegated_len,
          const asiolink::IOAddress& excluded_prefix,
          const uint8_t excluded_prefix_len);

    /// @brief Factory function for creating an instance of the @c Pool6.
    ///
    /// This function should be used to create an instance of the pool
    /// within a hooks library in cases when the library may be unloaded
    /// before the object is destroyed. This ensures that the ownership
    /// of the object by the Kea process is retained.
    ///
    /// @param type type of the pool (IA or TA)
    /// @param first the first address in a pool
    /// @param last the last address in a pool
    ///
    /// @return Pointer to the @c Pool6 instance.
    static Pool6Ptr create(Lease::Type type,
                           const isc::asiolink::IOAddress& first,
                           const isc::asiolink::IOAddress& last);

    /// @brief Factory function for creating an instance of the @c Pool6.
    ///
    /// This function should be used to create an instance of the pool
    /// within a hooks library in cases when the library may be unloaded
    /// before the object is destroyed. This ensures that the ownership
    /// of the object by the Kea process is retained.
    ///
    /// @param type type of the pool (IA, TA or PD)
    /// @param prefix specifies prefix of the pool
    /// @param prefix_len specifies prefix length of the pool
    /// @param delegated_len specifies length of the delegated prefixes
    ///
    /// @return Pointer to the @c Pool6 instance.
    static Pool6Ptr create(Lease::Type type,
                           const isc::asiolink::IOAddress& prefix,
                           uint8_t prefix_len,
                           uint8_t delegated_len = 128);

    /// @brief Factory function for creating an instance of the @c Pool6.
    ///
    /// If @c excluded_prefix is equal to '::' and the @c excluded_prefix_len
    /// is equal to 0, the excluded prefix is assumed to be unspecified for
    /// the pool. In this case, the server will not send the Prefix Exclude
    /// option to a client.
    ///
    /// @param prefix specifies a prefix of the pool.
    /// @param prefix_len specifies prefix length of the pool.
    /// @param delegated_len specifies length of the delegated prefixes.
    /// @param excluded_prefix specifies an excluded prefix as per RFC6603.
    /// @param excluded_prefix_len specifies length of an excluded prefix.
    ///
    /// @return Pointer to the @c Pool6 instance.
    static Pool6Ptr create(const asiolink::IOAddress& prefix,
                           const uint8_t prefix_len,
                           const uint8_t delegated_len,
                           const asiolink::IOAddress& excluded_prefix,
                           const uint8_t excluded_prefix_len);

    /// @brief returns pool type
    ///
    /// @return pool type
    Lease::Type getType() const {
        return (type_);
    }

    /// @brief returns delegated prefix length
    ///
    /// This may be useful for "prefix/len" style definition for
    /// addresses, but is mostly useful for prefix pools.
    /// @return prefix length (1-128)
    uint8_t getLength() const {
        return (prefix_len_);
    }

    /// @brief Returns instance of the pool specific Prefix Exclude option.
    ///
    /// @return An instance of the Prefix Exclude option (RFC 6603) or NULL
    /// if such option hasn't been specified for the pool.
    Option6PDExcludePtr getPrefixExcludeOption() const {
        return (pd_exclude_option_);
    }

    /// @brief Unparse a Pool6 object.
    ///
    /// @return A pointer to unparsed Pool6 configuration.
    virtual data::ElementPtr toElement() const;

    /// @brief returns textual representation of the pool
    ///
    /// @return textual representation
    virtual std::string toText() const;

private:

    /// @brief Generic method initializing a DHCPv6 pool.
    ///
    /// This method should be called by the constructors to initialize
    /// DHCPv6 pools.
    ///
    /// @param Lease/pool type.
    /// @param prefix An address or delegated prefix (depending on the
    /// pool type specified as @c type).
    /// @param prefix_len Prefix length. If a pool is an address pool,
    /// this value should be set to 128.
    /// @param delegated_len Length of the delegated prefixes. If a pool
    /// is an address pool, this value should be set to 128.
    /// @param excluded_prefix An excluded prefix as per RFC6603. This
    /// value should only be specified for prefix pools. The value of
    /// '::' means "unspecified".
    /// @param excluded_prefix_len Length of the excluded prefix. This
    /// is only specified for prefix pools. The value of 0 should be
    /// used when @c excluded_prefix is not specified.
    void init(const Lease::Type& type,
              const asiolink::IOAddress& prefix,
              const uint8_t prefix_len,
              const uint8_t delegated_len,
              const asiolink::IOAddress& excluded_prefix,
              const uint8_t excluded_prefix_len);

    /// @brief Defines prefix length (for TYPE_PD only)
    uint8_t prefix_len_;

    /// @brief A pointer to the Prefix Exclude option (RFC 6603).
    Option6PDExcludePtr pd_exclude_option_;

};

/// @brief a pointer to either IPv4 or IPv6 Pool
typedef boost::shared_ptr<Pool> PoolPtr;

/// @brief a container for either IPv4 or IPv6 Pools
typedef std::vector<PoolPtr> PoolCollection;

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // POOL_H
