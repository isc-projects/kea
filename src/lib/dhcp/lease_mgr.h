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

#include <string>
#include <fstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "benchmark.h"

/// @brief Holds DUID (DHCPv6 Unique Identifier)
///
/// This class holds DUID, that is used in client-id, server-id and
/// several other options. It is used to identify DHCPv6 entity.
class DUID {

    /// @brief specifies DUID type
    typedef enum {
        DUID_UNKNOWN = 0, // invalid/unknown type
        DUID_LLT = 1, // link-layer + time, see RFC3315, section 9.2
        DUID_EN = 2,  // enterprise-id, see RFC3315, section 9.3
        DUID_LL = 3,  // link-layer, see RFC3315, section 9.4
        DUID_UUID = 4, // UUID, see RFC6355
    } DUIDType;

 public:
    DUID(const std::vector<uint8_t>& duid);
    DUID(const char *duid, size_t len);
    const std::vector<uint8_t> getDuid() const;
    DUIDType getType();
    bool operator == (const DUID& other);
 protected:
    std::vector<uint8_t> duid_;
    
}

/// @brief Structure that holds a lease for IPv4 address
///
/// For performance reasons it is a simple structure, not a class. If we chose
/// make it a class, all fields would have to made private and getters/setters
/// would be required. As this is a critical part of the code that will be used
/// extensively, direct access is warranted.
struct Lease4 {
    uint32_t addr_; /// IPv4 address

    /// @brief Address extension
    ///
    /// It is envisaged that in some cases IPv4 address will be accompanied with some
    /// additional data. One example of such use are Address + Port solutions (or
    /// Port-restricted Addresses), where several clients may get the same address, but
    /// different port ranges. This feature is not expected to be widely used.
    /// Under normal circumstances, the value should be 0.
    uint32_t ext_; /// address extension

    /// @brief hardware address
    std::vector<uint8_t> hwaddr;

    /// @brief client identifier
    std::vector<uint8_t> client_id; 

    /// valid lifetime timestamp
    uint32_t valid_lft;

    /// @brief Recycle timer
    ///
    /// Typically, the lease return to free pool immediately after it is released
    /// or expired. This timer specifies number of seconds that it should be kept
    /// after release or expiration, in case the client returns. This feature is not
    /// currently used and this value is set to 0.
    uint32_t recycle_time; 

    /// @brief client last transmission time
    ///
    /// Specifies a timestamp, when last transmission from a client was received.
    time_t cltt;

    /// @brief Pool identifier
    ///
    /// Specifies pool-id of the pool that the lease belongs to
    uint32_t pool_id;

    /// @brief Is this a fixed lease?
    ///
    /// Fixed leases are kept after they are released/expired.
    bool fixed;

    /// @brief client hostname
    ///
    /// This field may be empty
    std::string hostname;

    /// @brief did we update AAAA record for this lease?
    bool fqdn_fwd;

    /// @brief did we update PTR record for this lease? 
    bool fqdn_rev;

    /// @brief additional options stored with this lease
    ///
    /// Currently not used.
    std::string options; 

    /// @brief Lease comments.
    ///
    /// Currently not used. It may be used for keeping comments made by the
    /// system administrator.
    std::string comments; 
};

/// @brief Pointer to a Lease4 structure.
typedef boost::shared_ptr<Lease4> Lease4Ptr;


/// @brief Structure that holds a lease for IPv6 address and/or prefix
///
/// For performance reasons it is a simple structure, not a class. Had we chose to
/// make it a class, all fields would have to be made private and getters/setters
/// would be required. As this is a critical part of the code that will be used
/// extensively, direct access rather than through getters/setters is warranted.
struct Lease6 {
    typedef enum {
        LEASE_IA_NA, /// the lease contains non-temporary IPv6 address
        LEASE_IA_TA, /// the lease contains temporary IPv6 address
        LEASE_IA_PD  /// the lease contains IPv6 prefix (for prefix delegation)
    } LeaseType;

    /// @brief specifies lease type (normal addr, temporary addr, prefix)
    LeaseType type_;

    /// IPv6 address
    isc::asiolink::IOAddress addr_;

    /// IPv6 prefix length (used only for PD)
    uint8_t prefixlen_;

    /// @brief IAID
    ///
    /// Identity Association IDentifier. DHCPv6 stores all addresses and prefixes
    /// in IA containers (IA_NA, IA_TA, IA_PD). Most containers may appear more
    /// than once in a message. To differentiate between them, IAID field is present
    uint32_t iaid_;

    /// @brief hardware address
    ///
    /// This field is not really used and is optional at best. The concept of identifying
    /// clients by their hardware address was replaced in DHCPv6 by DUID concept. Each
    /// client has its own unique DUID (DHCP Unique IDentifier). Furthermore, client's
    /// HW address is not always available, because client may be behind a relay (relay
    /// stores only link-local address).
    std::vector<uint8_t> hwaddr;

    /// @brief client identifier
    boost::shared_ptr<DUID> duid_;

    /// @brief preferred lifetime
    ///
    /// This parameter specifies preferred lifetime since the lease was assigned/renewed
    /// (cltt), expressed in seconds.
    uint32_t preferred_lft;

    /// @brief valid lifetime
    uint32_t valid_lft;

    /// @brief T1 timer
    ///
    /// Specifies renewal time. Although technically it is a property of IA container,
    /// not the address itself, since our data model does not define separate IA
    /// entity, we are keeping it in the lease. In case of multiple addresses/prefixes
    /// for the same IA, each must have consistent T1 and T2 values.
    uint32_t t1_;

    /// @brief T2 timer
    ///
    /// Specifies rebinding time. Although technically it is a property of IA container,
    /// not the address itself, since our data model does not define separate IA
    /// entity, we are keeping it in the lease. In case of multiple addresses/prefixes
    /// for the same IA, each must have consistent T1 and T2 values.
    uint32_t t2_;

    /// @brief Recycle timer
    ///
    /// Typically, the lease return to free pool immediately after it is released
    /// or expired. This timer specifies number of seconds that it should be kept
    /// after release or expiration, in case the client returns. This feature is not
    /// currently used and this value is set to 0.
    uint32_t recycle_time; 

    /// @brief client last transmission time
    ///
    /// Specifies a timestamp, when last transmission from a client was received.
    time_t cltt;

    /// @brief Pool identifier
    ///
    /// Specifies pool-id of the pool that the lease belongs to
    uint32_t pool_id;

    /// @brief Is this a fixed lease?
    ///
    /// Fixed leases are kept after they are released/expired.
    bool fixed;

    /// @brief client hostname
    ///
    /// This field may be empty
    std::string hostname;

    /// @brief did we update AAAA record for this lease?
    bool fqdn_fwd;

    /// @brief did we update PTR record for this lease? 
    bool fqdn_rev;

    /// @brief additional options stored with this lease
    ///
    /// That field is currently not used. We may keep extra options assigned
    /// for leasequery and possibly other purposes.
    /// @todo: Define this as a container of options
    std::string options; 

    /// @brief /// comments on that lease
    ///
    /// (currently not used)
    std::string comments; 
};

/// @brief Pointer to a Lease6 structure.
typedef boost::shared_ptr<Lease6> Lease6Ptr;

/// @brief Const pointer to a Lease6 structure.
typedef boost::shared_ptr<const Lease6> ConstLease6Ptr;


/// @brief In-memory + lease file database implementation
///
/// This is a simplified in-memory database that mimics ISC DHCP4 implementation.
/// It uses STL and boost: std::map for storage, boost::shared ptr for memory
/// management. It does use C file operations (fopen, fwrite, etc.), because
/// C++ streams does not offer any easy way to flush their contents, like
/// fflush() and fsync() does.
///
/// IPv4 address is used as a key in the hash.
class LeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// @param filename name of the lease file (will be overwritten)
    /// @param sync should operations be
    LeaseMgr(const std::string& filename, bool sync);

    /// @brief Destructor (closes file)
    ~LeaseMgr();

    /// @brief adds an IPv4 lease
    ///
    /// @param lease lease to be added
    bool addLease(Lease4Ptr lease);

    /// @brief adds a IPv6 lease
    ///
    /// @param lease lease to be added
    bool addLease(Lease6Ptr lease);

    /// @brief returns existing IPv4 lease
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if lease is not found)
    Lease4Ptr getLease4(isc::asiolink::IOAddress addr);

#error "Implement this"
    Lease4Ptr getLease4(hwaddress );

    Lease4Ptr getLease4(client-id);

    /// @brief returns existing IPv4 lease
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if lease is not found)
    Lease6Ptr getLease6(isc::asiolink::IOAddress addr);

#error "Implement this"
    Lease6Ptr getLease6(DUID);

    Lease6Ptr getLease6(DUID, iaid);


#error "Implement this"
    bool updateLease4(Lease4Ptr lease4);

    bool updateLease6(Lease6Ptr lease6);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease4(uint32_t addr);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease6(isc::asiolink::IOAddress addr);

protected:

};




};
