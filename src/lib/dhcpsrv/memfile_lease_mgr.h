// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef MEMFILE_LEASE_MGR_H
#define MEMFILE_LEASE_MGR_H

#include <dhcp/hwaddr.h>
#include <dhcpsrv/key_from_key.h>
#include <dhcpsrv/lease_mgr.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>

namespace isc {
namespace dhcp {

// This is a concrete implementation of a Lease database.
//
// It is for testing purposes only. It is NOT a production code.
//
// It does not do anything useful now, and is used for abstract LeaseMgr
// class testing. It may later evolve into more useful backend if the
// need arises. We can reuse code from memfile benchmark. See code in
// tests/tools/dhcp-ubench/memfile_bench.{cc|h}
class Memfile_LeaseMgr : public LeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    Memfile_LeaseMgr(const ParameterMap& parameters);

    /// @brief Destructor (closes file)
    virtual ~Memfile_LeaseMgr();

    /// @brief Adds an IPv4 lease.
    ///
    /// @todo Not implemented yet
    /// @param lease lease to be added
    virtual bool addLease(const Lease4Ptr& lease);

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease6Ptr& lease);

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @todo Not implemented yet
    /// @param addr address of the searched lease
    ///
    /// @return a collection of leases
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv4 leases for specified hardware address.
    ///
    /// @todo Not implemented yet
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param hwaddr hardware address of the client
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const isc::dhcp::HWAddr& hwaddr) const;

    /// @brief Returns existing IPv4 leases for specified hardware address
    ///        and a subnet
    ///
    /// @todo Not implemented yet
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const HWAddr& hwaddr,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @todo Not implemented yet
    ///
    /// @param clientid client identifier
    virtual Lease4Collection getLease4(const ClientId& clientid) const;

    /// @brief Returns IPv4 lease for specified client-id/hwaddr/subnet-id tuple
    ///
    /// There can be at most one lease for a given client-id/hwaddr tuple
    /// in a single pool, so this method with either return a single lease
    /// or NULL.
    ///
    /// @param clientid client identifier
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                const HWAddr& hwaddr,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @todo Not implemented yet
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @todo Not implemented yet
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection getLease6(const DUID& duid, uint32_t iaid) const;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @todo Not implemented yet
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id identifier of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const DUID& duid, uint32_t iaid, SubnetID subnet_id) const;

    /// @brief Updates IPv4 lease.
    ///
    /// @todo Not implemented yet
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr& lease4);

    /// @brief Updates IPv4 lease.
    ///
    /// @todo Not implemented yet
    ///
    /// @param lease6 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease6(const Lease6Ptr& lease6);

    /// @brief Deletes a lease.
    ///
    /// @param addr Address of the lease to be deleted. (This can be IPv4 or
    ///        IPv6.)
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease(const isc::asiolink::IOAddress& addr);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend.
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("memfile"));
    }

    /// @brief Returns backend name.
    ///
    /// For now, memfile can only store data in memory.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const {
        return ("memory");
    }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    virtual std::pair<uint32_t, uint32_t> getVersion() const {
        return (std::make_pair(1, 0));
    }

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void commit();

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void rollback();

protected:

    // This is a multi-index container, which holds elements that can
    // be accessed using different search indexes.
    typedef boost::multi_index_container<
        // It holds pointers to Lease6 objects.
        Lease6Ptr,
        boost::multi_index::indexed_by<
            // Specification of the first index starts here.
            // This index sorts leases by IPv6 addresses represented as
            // IOAddress objects.
            boost::multi_index::ordered_unique<
                boost::multi_index::member<Lease, isc::asiolink::IOAddress, &Lease::addr_>
            >,

            // Specification of the second index starts here.
            boost::multi_index::ordered_unique<
                // This is a composite index that will be used to search for
                // the lease using three attributes: DUID, IAID, Subnet Id.
                boost::multi_index::composite_key<
                    Lease6,
                    // The DUID value can't be directly accessed from the Lease6
                    // object because it is wrapped with the DUID object (actually
                    // pointer to this object). Therefore we need to use
                    // KeyFromKeyExtractor class to extract the DUID value from
                    // this cascaded structure.
                    KeyFromKeyExtractor<
                        // The value of the DUID is accessed by the getDuid() method
                        // from the DUID object.
                        boost::multi_index::const_mem_fun<DUID, std::vector<uint8_t>,
                                                          &DUID::getDuid>,
                        // The DUID object is stored in the duid_ member of the
                        // Lease6 object.
                        boost::multi_index::member<Lease6, DuidPtr, &Lease6::duid_>
                    >,
                    // The two other ingredients of this index are IAID and
                    // subnet id.
                    boost::multi_index::member<Lease6, uint32_t, &Lease6::iaid_>,
                    boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>
                >
            >
        >
     > Lease6Storage; // Specify the type name of this container.

    // This is a multi-index container, which holds elements that can
    // be accessed using different search indexes.
    typedef boost::multi_index_container<
        // It holds pointers to Lease4 objects.
        Lease4Ptr, 
        // Specification of search indexes starts here.
        boost::multi_index::indexed_by<
            // Specification of the first index starts here.
            // This index sorts leases by IPv4 addresses represented as
            // IOAddress objects.
            boost::multi_index::ordered_unique<
                // The IPv4 address are held in addr_ members that belong to
                // Lease class.
                boost::multi_index::member<Lease, isc::asiolink::IOAddress, &Lease::addr_>
            >,

            // Specification of the second index starts here.
            boost::multi_index::ordered_unique<
                // This is a composite index that combines two attributes of the
                // Lease4 object: hardware address and subnet id.
                boost::multi_index::composite_key<
                    Lease4,
                    // The hardware address is held in the hwaddr_ member of the
                    // Lease4 object.
                    boost::multi_index::member<Lease4, std::vector<uint8_t>,
                                               &Lease4::hwaddr_>,
                    // The subnet id is held in the subnet_id_ member of Lease4
                    // class. Note that the subnet_id_ is defined in the base
                    // class (Lease) so we have to point to this class rather
                    // than derived class: Lease4.
                    boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>
                >
            >,

            // Specification of the third index starts here.
            boost::multi_index::ordered_unique<
                // This is a composite index that uses two values to search for a
                // lease: client id and subnet id.
                boost::multi_index::composite_key<
                    Lease4,
                    // The client id value is not directly accessible through the
                    // Lease4 object as it is wrapped with the ClientIdPtr object.
                    // Therefore we use the KeyFromKeyExtractor class to access
                    // client id through this cascaded structure. The client id
                    // is used as an index value.
                    KeyFromKeyExtractor<
                        // Specify that the vector holding client id value can be obtained
                        // from the ClientId object.
                        boost::multi_index::const_mem_fun<ClientId, std::vector<uint8_t>,
                                                          &ClientId::getClientId>,
                        // Specify that the ClientId object (actually pointer to it) can
                        // be accessed by the client_id_ member of Lease4 class.
                        boost::multi_index::member<Lease4, ClientIdPtr, &Lease4::client_id_>
                    >,
                    // The subnet id is accessed through the subnet_id_ member.
                    boost::multi_index::member<Lease, uint32_t, &Lease::subnet_id_>
                >
            >,

            // Specification of the fourth index starts here.
            boost::multi_index::ordered_unique<
                // This is a composite index that uses two values to search for a
                // lease: client id and subnet id.
                boost::multi_index::composite_key<
                    Lease4,
                    // The client id value is not directly accessible through the
                    // Lease4 object as it is wrapped with the ClientIdPtr object.
                    // Therefore we use the KeyFromKeyExtractor class to access
                    // client id through this cascaded structure. The client id
                    // is used as an index value.
                    KeyFromKeyExtractor<
                        // Specify that the vector holding client id value can be obtained
                        // from the ClientId object.
                        boost::multi_index::const_mem_fun<ClientId, std::vector<uint8_t>,
                                                          &ClientId::getClientId>,
                        // Specify that the ClientId object (actually pointer to it) can
                        // be accessed by the client_id_ member of Lease4 class.
                        boost::multi_index::member<Lease4, ClientIdPtr, &Lease4::client_id_>
                    >,
                    // The hardware address is held in the hwaddr_ member of the
                    // Lease4 object.
                    boost::multi_index::member<Lease4, std::vector<uint8_t>,
                                               &Lease4::hwaddr_>,
                    // The subnet id is accessed through the subnet_id_ member.
                    boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>
                >
            >
        >
    > Lease4Storage; // Specify the type name for this container.

    /// @brief stores IPv4 leases
    Lease4Storage storage4_;

    /// @brief stores IPv6 leases
    Lease6Storage storage6_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // MEMFILE_LEASE_MGR
