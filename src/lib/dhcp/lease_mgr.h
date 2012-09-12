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
#include <map>
#include <asiolink/io_address.h>
#include <boost/shared_ptr.hpp>
#include <dhcp/option.h>
#include <dhcp/duid.h>

namespace isc {
namespace dhcp {

/// @brief Structure that holds a lease for IPv4 address
///
/// For performance reasons it is a simple structure, not a class. If we chose
/// make it a class, all fields would have to made private and getters/setters
/// would be required. As this is a critical part of the code that will be used
/// extensively, direct access is warranted.
struct Lease4 {
    /// IPv4 address
    isc::asiolink::IOAddress addr_;

    /// @brief Address extension
    ///
    /// It is envisaged that in some cases IPv4 address will be accompanied with some
    /// additional data. One example of such use are Address + Port solutions (or
    /// Port-restricted Addresses), where several clients may get the same address, but
    /// different port ranges. This feature is not expected to be widely used.
    /// Under normal circumstances, the value should be 0.
    uint32_t ext_;

    /// @brief hardware address
    std::vector<uint8_t> hwaddr_;

    /// @brief client identifier
    boost::shared_ptr<ClientId> client_id_;

    /// @brief valid lifetime
    ///
    /// Expressed as number of seconds since cltt
    uint32_t valid_lft_;

    /// @brief Recycle timer
    ///
    /// Typically, the lease return to free pool immediately after it is released
    /// or expired. This timer specifies number of seconds that it should be kept
    /// after release or expiration, in case the client returns. This feature is not
    /// currently used and this value is set to 0.
    uint32_t recycle_time_;

    /// @brief client last transmission time
    ///
    /// Specifies a timestamp, when last transmission from a client was received.
    time_t cltt_;

    /// @brief Pool identifier
    ///
    /// Specifies pool-id of the pool that the lease belongs to
    uint32_t pool_id_;

    /// @brief Is this a fixed lease?
    ///
    /// Fixed leases are kept after they are released/expired.
    bool fixed_;

    /// @brief client hostname
    ///
    /// This field may be empty
    std::string hostname_;

    /// @brief did we update AAAA record for this lease?
    bool fqdn_fwd_;

    /// @brief did we update PTR record for this lease?
    bool fqdn_rev_;

    /// @brief additional options stored with this lease
    ///
    /// This field is currently not used.
    /// @todo We need a way to store options in the databased.
    Option::OptionCollection options_;

    /// @brief Lease comments.
    ///
    /// Currently not used. It may be used for keeping comments made by the
    /// system administrator.
    std::string comments_;
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
    std::vector<uint8_t> hwaddr_;

    /// @brief client identifier
    boost::shared_ptr<DUID> duid_;

    /// @brief preferred lifetime
    ///
    /// This parameter specifies preferred lifetime since the lease was assigned/renewed
    /// (cltt), expressed in seconds.
    uint32_t preferred_lft_;

    /// @brief valid lifetime
    ///
    /// This parameter specified valid lifetime since the lease was assigned/renewed
    /// (cltt), expressed in seconds.
    uint32_t valid_lft_;

    /// @brief T1 timer
    ///
    /// Specifies renewal time. Although technically it is a property of IA container,
    /// not the address itself, since our data model does not define separate IA
    /// entity, we are keeping it in the lease. In case of multiple addresses/prefixes
    /// for the same IA, each must have consistent T1 and T2 values. Specified in
    /// seconds since cltt.
    uint32_t t1_;

    /// @brief T2 timer
    ///
    /// Specifies rebinding time. Although technically it is a property of IA container,
    /// not the address itself, since our data model does not define separate IA
    /// entity, we are keeping it in the lease. In case of multiple addresses/prefixes
    /// for the same IA, each must have consistent T1 and T2 values. Specified in
    /// seconds since cltt.
    uint32_t t2_;

    /// @brief Recycle timer
    ///
    /// Typically, the lease return to free pool immediately after it is released
    /// or expired. This timer specifies number of seconds that it should be kept
    /// after release or expiration, in case the client returns. This feature is not
    /// currently used and this value is set to 0.
    uint32_t recycle_time_;

    /// @brief client last transmission time
    ///
    /// Specifies a timestamp, when last transmission from a client was received.
    time_t cltt_;

    /// @brief Pool identifier
    ///
    /// Specifies pool-id of the pool that the lease belongs to
    uint32_t pool_id_;

    /// @brief Is this a fixed lease?
    ///
    /// Fixed leases are kept after they are released/expired.
    bool fixed_;

    /// @brief client hostname
    ///
    /// This field may be empty
    std::string hostname_;

    /// @brief did we update AAAA record for this lease?
    bool fqdn_fwd_;

    /// @brief did we update PTR record for this lease?
    bool fqdn_rev_;

    /// @brief additional options stored with this lease
    ///
    /// That field is currently not used. We may keep extra options assigned
    /// for leasequery and possibly other purposes.
    /// @todo We need a way to store options in the databased.
    Option::OptionCollection options_;

    /// @brief Lease comments
    ///
    /// This field is currently not used.
    std::string comments_;
};

/// @brief Pointer to a Lease6 structure.
typedef boost::shared_ptr<Lease6> Lease6Ptr;

/// @brief Const pointer to a Lease6 structure.
typedef boost::shared_ptr<const Lease6> ConstLease6Ptr;


/// @brief Abstract Lease Manager
///
/// This is an abstract API for lease database backends. It provides unified
/// interface to all backends. As this is an abstract class, it should not
/// be used directly, but rather specialized derived class should be used
/// instead.
class LeaseMgr {
public:

    /// Client Hardware address
    typedef std::vector<uint8_t> HWAddr;

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ///
    /// @param dbconfig database configuration
    LeaseMgr(const std::string& dbconfig);

    /// @brief Destructor (closes file)
    virtual ~LeaseMgr();

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(Lease4Ptr lease) = 0;

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(Lease6Ptr lease) = 0;

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(isc::asiolink::IOAddress addr) const = 0;

    /// @brief Returns existing IPv4 lease for specified hardware address.
    ///
    /// @param hwaddr hardware address of the client
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const HWAddr& hwaddr) const = 0;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    virtual Lease4Ptr getLease4(const ClientId& clientid) const = 0;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(isc::asiolink::IOAddress addr) const = 0;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const DUID& duid, uint32_t iaid) const = 0;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(Lease4Ptr lease4) = 0;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease6(Lease6Ptr lease6) = 0;

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease4(uint32_t addr) = 0;

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease6(isc::asiolink::IOAddress addr) = 0;

    /// @brief Returns backend name.
    ///
    /// Each backend have specific name, e.g. "mysql" or "sqlite".
    virtual std::string getName() const = 0;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    virtual std::string getDescription() const = 0;

    /// @brief Returns backend version.
    ///
    /// @todo: We will need to implement 3 version functions eventually:
    /// A. abstract API version
    /// B. backend version
    /// C. database version (stored in the database scheme)
    ///
    /// and then check that:
    /// B>=A and B=C (it is ok to have newer backend, as it should be backward
    /// compatible)
    /// Also if B>C, some database upgrade procedure may happen
    virtual std::string getVersion() const = 0;

    /// @todo: Add host management here
    /// As host reservation is outside of scope for 2012, support for hosts
    /// is currently postponed.

protected:
    /// @brief returns value of the parameter
    std::string getParameter(const std::string& name) const;

    /// @brief list of parameters passed in dbconfig
    ///
    /// That will be mostly used for storing database name, username,
    /// password and other parameters required for DB access. It is not
    /// intended to keep any DHCP-related parameters.
    std::map<std::string, std::string> parameters_;
};


}; // end of isc::dhcp namespace

}; // end of isc namespace
