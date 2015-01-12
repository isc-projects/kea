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

#ifndef MEMFILE_LEASE_MGR_H
#define MEMFILE_LEASE_MGR_H

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/lease_mgr.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>

namespace isc {
namespace dhcp {

/// @brief Concrete implementation of a lease database backend using flat file.
///
/// This class implements a lease database backend using CSV files to store
/// DHCPv4 and DHCPv6 leases on disk. The format of the files is determined
/// by the @c CSVLeaseFile4 and @c CSVLeaseFile6 classes.
///
/// The backend stores leases incrementally, i.e. updates to leases are appended
/// at the end of the lease file. To record the deletion of a lease, the lease
/// record is appended to the lease file with the valid lifetime set to 0.
///
/// When the backend is starting up, it reads leases from the lease file (one
/// by one) and adds them to the in-memory container as follows:
/// - if the lease record being parsed identifies a lease which is not present
/// in the container, and the lease has valid lifetime greater than 0,
/// the lease is added to the container,
/// - if the lease record being parsed identifies a lease which is present in
/// the container, and the valid lifetime of the lease record being parsed is
/// greater than 0, the lease in the container is updated
/// - if the lease record being parsed has valid lifetime equal to 0, and the
/// corresponding lease exists in the container, the lease is removed from
/// the container.
///
/// After the container holding leases is initialized, each subsequent update,
/// removal or addition of the lease is appended to the lease file
/// synchronously.
///
/// Originally, the Memfile backend didn't write leases to disk. This was
/// particularly useful for testing server performance in non-disk bound
/// conditions. In order to preserve this capability, the new parameter
/// "persist=true|false" has been introduced in the database access string.
/// For example, database access string: "type=memfile persist=true"
/// enables writes of leases to a disk.
///
/// The lease file locations can be specified with the "name=[path]"
/// parameter in the database access string. The [path] is the
/// absolute path to the file (including file name). If this parameter
/// is not specified, the default location in the installation
/// directory is used: var/kea/kea-leases4.csv and
/// var/kea/kea-leases6.csv.
class Memfile_LeaseMgr : public LeaseMgr {
public:

    /// @defgroup versions Specified memfile backend version.
    ///
    /// @brief Defines major version of the memfile backend.
    ///
    /// Version history:
    /// 1.0 - initial version (released in Kea 0.9)
    /// 2.0 - hwaddr column added (to be released in Kea 0.9.1)
    ///
    /// @{
    static const int MAJOR_VERSION = 2;

    /// Defines minor version of the memfile backend.
    static const int MINOR_VERSION = 0;

    /// @}


    /// @brief Specifies universe (V4, V6)
    ///
    /// This enumeration is used by various functions in Memfile Lease Manager,
    /// to identify the lease type referred to. In particular, it is used by
    /// functions operating on the lease files to distinguish between lease
    /// files for DHCPv4 and DHCPv6.
    enum Universe {
        V4,
        V6
    };

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
    /// @param lease lease to be added
    virtual bool addLease(const Lease4Ptr& lease);

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease6Ptr& lease);

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// @param addr An address of the searched lease.
    ///
    /// @return a collection of leases
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv4 leases for specified hardware address.
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

    /// @brief Returns existing IPv4 lease for specified hardware address
    ///        and a subnet
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
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
    /// @param client_id client identifier
    virtual Lease4Collection getLease4(const ClientId& client_id) const;

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
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param addr An address of the searched lease.
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(Lease::Type type,
                                const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv6 lease for a given DUID + IA + lease type
    /// combination
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection getLeases6(Lease::Type type,
                                        const DUID& duid, uint32_t iaid) const;

    /// @brief Returns existing IPv6 lease for a given DUID + IA + subnet-id +
    /// lease type combination.
    ///
    /// This function returns a copy of the lease. The modification in the
    /// return lease does not affect the instance held in the lease storage.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id identifier of the subnet the lease must belong to
    ///
    /// @return lease collection (may be empty if no lease is found)
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                        uint32_t iaid,
                                        SubnetID subnet_id) const;

    /// @brief Updates IPv4 lease.
    ///
    /// @warning This function does not validate the pointer to the lease.
    /// It is caller's responsibility to pass the valid pointer.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr& lease4);

    /// @brief Updates IPv6 lease.
    ///
    /// @warning This function does not validate the pointer to the lease.
    /// It is caller's responsibility to pass the valid pointer.
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
        return (std::make_pair(MAJOR_VERSION, MINOR_VERSION));
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

    /// @brief Returns default path to the lease file.
    ///
    /// @param u Universe (V4 or V6).
    std::string getDefaultLeaseFilePath(Universe u) const;

    /// @brief Returns an absolute path to the lease file.
    ///
    /// @param u Universe (V4 or V6).
    ///
    /// @return Absolute path to the lease file or empty string if no lease
    /// file is used.
    std::string getLeaseFilePath(Universe u) const;

    /// @brief Specifies whether or not leases are written to disk.
    ///
    /// It is possible that leases for DHCPv4 are written to disk whereas leases
    /// for DHCPv6 are not; or vice versa. The argument of the method specifies
    /// the type of lease in that respect.
    ///
    /// @param u Universe (V4 or V6).
    ///
    /// @return true if leases are written to lease file; if false is
    /// returned, leases will be held in memory and will be lost upon
    /// server shut down.
    bool persistLeases(Universe u) const;

protected:

    /// @brief A callback function triggering Lease File Cleanup.
    ///
    /// This method is virtual so as it can be overriden and customized in
    /// the unit tests. In particular, the unit test which checks that the
    /// callback function has been executed would override this function
    /// to increase the execution counter each time it is executed.
    virtual void lfcCallback();

private:

    /// @brief Load all DHCPv4 leases from the file.
    ///
    /// This method loads all DHCPv4 leases from a file to memory. It removes
    /// existing leases before reading a file.
    ///
    /// @throw isc::DbOperationError If failed to read a lease from the lease
    /// file.
    void load4();

    /// @brief Loads a single DHCPv4 lease from the file.
    ///
    /// This method reads a single lease record from the lease file. If the
    /// corresponding record doesn't exist in the in-memory container, the
    /// lease is added to the container (except for a lease which valid lifetime
    /// is 0). If the corresponding lease exists, the lease being read updates
    /// the existing lease. If the lease being read from the lease file has
    /// valid lifetime of 0 and the corresponding lease exists in the in-memory
    /// database, the existing lease is removed.
    ///
    /// @param lease Pointer to the lease read from the lease file.
    void loadLease4(Lease4Ptr& lease);

    /// @brief Load all DHCPv6 leases from the file.
    ///
    /// This method loads all DHCPv6 leases from a file to memory. It removes
    /// existing leases before reading a file.
    ///
    /// @throw isc::DbOperationError If failed to read a lease from the lease
    /// file.
    void load6();

    /// @brief Loads a single DHCPv6 lease from the file.
    ///
    /// This method reads a single lease record from the lease file. If the
    /// corresponding record doesn't exist in the in-memory container, the
    /// lease is added to the container (except for a lease which valid lifetime
    /// is 0). If the corresponding lease exists, the lease being read updates
    /// the existing lease. If the lease being read from the lease file has
    /// valid lifetime of 0 and the corresponding lease exists in the in-memory
    /// database, the existing lease is removed.
    ///
    /// @param lease Pointer to the lease read from the lease file.
    void loadLease6(Lease6Ptr& lease);

    /// @brief Initialize the location of the lease file.
    ///
    /// This method uses the parameters passed as a map to the constructor to
    /// initialize the location of the lease file. If the lease file is not
    /// specified, the method will use the default location for the universe
    /// (v4 or v6) selected. If the location is specified in the map as empty
    /// or the "persist" parameter is set to "no" it will set the empty
    /// location, which implies that leases belonging to the specified universe
    /// will not be written to disk.
    ///
    /// @param u Universe (v4 or v6)
    ///
    /// @return The location of the lease file that should be assigned to the
    /// lease_file4_ or lease_file6_, depending on the universe specified as an
    /// argument to this function.
    std::string initLeaseFilePath(Universe u);

    /// @brief Initialize the timers used to perform repeating tasks.
    ///
    /// Currently only one timer is supported. This timer executes the
    /// Lease File Cleanup periodically.
    ///
    /// @param universe A V4 or V6 value.
    void initTimers(const Universe& universe);

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
            boost::multi_index::ordered_non_unique<
                // This is a composite index that will be used to search for
                // the lease using three attributes: DUID, IAID and lease type.
                boost::multi_index::composite_key<
                    Lease6,
                    // The DUID can be retrieved from the Lease6 object using
                    // a getDuidVector const function.
                    boost::multi_index::const_mem_fun<Lease6, const std::vector<uint8_t>&,
                                                      &Lease6::getDuidVector>,
                    // The two other ingredients of this index are IAID and
                    // lease type.
                    boost::multi_index::member<Lease6, uint32_t, &Lease6::iaid_>,
                    boost::multi_index::member<Lease6, Lease::Type, &Lease6::type_>
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
                    // Lease4 object, which is a HWAddr object. Boost does not
                    // provide a key extractor for getting a member of a member,
                    // so we need a simple method for that.
                    boost::multi_index::const_mem_fun<Lease, const std::vector<uint8_t>&,
                                               &Lease::getHWAddrVector>,
                    // The subnet id is held in the subnet_id_ member of Lease4
                    // class. Note that the subnet_id_ is defined in the base
                    // class (Lease) so we have to point to this class rather
                    // than derived class: Lease4.
                    boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>
                >
            >,

            // Specification of the third index starts here.
            boost::multi_index::ordered_non_unique<
                // This is a composite index that uses two values to search for a
                // lease: client id and subnet id.
                boost::multi_index::composite_key<
                    Lease4,
                    // The client id can be retrieved from the Lease4 object by
                    // calling getClientIdVector const function.
                    boost::multi_index::const_mem_fun<Lease4, const std::vector<uint8_t>&,
                                                      &Lease4::getClientIdVector>,
                    // The subnet id is accessed through the subnet_id_ member.
                    boost::multi_index::member<Lease, uint32_t, &Lease::subnet_id_>
                >
            >,

            // Specification of the fourth index starts here.
            boost::multi_index::ordered_non_unique<
                // This is a composite index that uses two values to search for a
                // lease: client id and subnet id.
                boost::multi_index::composite_key<
                    Lease4,
                    // The client id can be retrieved from the Lease4 object by
                    // calling getClientIdVector const function.
                    boost::multi_index::const_mem_fun<Lease4, const std::vector<uint8_t>&,
                                                      &Lease4::getClientIdVector>,
                    // The hardware address is held in the hwaddr_ object. We can
                    // access the raw data using lease->hwaddr_->hwaddr_, but Boost
                    // doesn't seem to provide a way to use member of a member for this,
                    // so we need a simple key extractor method (getRawHWAddr).
                    boost::multi_index::const_mem_fun<Lease, const std::vector<uint8_t>&,
                                            &Lease::getHWAddrVector>,
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

    /// @brief Holds the pointer to the DHCPv4 lease file IO.
    boost::shared_ptr<CSVLeaseFile4> lease_file4_;

    /// @brief Holds the pointer to the DHCPv6 lease file IO.
    boost::shared_ptr<CSVLeaseFile6> lease_file6_;

    /// @brief A timer scheduled to perform Lease File Cleanup.
    asiolink::IntervalTimer lfc_timer_;

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // MEMFILE_LEASE_MGR
