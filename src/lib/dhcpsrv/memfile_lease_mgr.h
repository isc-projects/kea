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
#include <dhcp/hwaddr.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <dhcpsrv/lease_mgr.h>
#include <util/process_spawn.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Concrete implementation of a lease database backend using flat file.
///
/// This class implements a lease database backend using CSV files to store
/// DHCPv4 and DHCPv6 leases on disk. The format of the files is determined
/// by the @c CSVLeaseFile4 and @c CSVLeaseFile6 classes.
///
/// In order to obtain good performance, the backend stores leases
/// incrementally, i.e. updates to leases are appended at the end of the lease
/// file. To record the deletion of a lease, the lease record is appended to
/// the lease file with the valid lifetime set to 0. However, this may result
/// in a significant growth of the lease file size over time, because the lease
/// file will contain many entries for each lease. In order to mitigate this
/// problem, the backend implements the Lease File Cleanup mechanism which is
/// described on the Kea wiki: http://kea.isc.org/wiki/LFCDesign.
///
/// The backend installs an @c asiolink::IntervalTimer to periodically execute
/// the @c Memfile_LeaseMgr::lfcCallback. This callback function controls
/// the startup of the background process which removes redundant information
/// from the lease file(s). Note that the @c asiolink::IntervalTimer uses
/// @c asiolink::IOService to execute the callback. The @c LeaseMgr class
/// creates this object, which can be obtained by the caller using the
/// @c LeaseMgr::getIOService. The caller should later call an appropriate
/// method, @c asio::io_service::poll_one to execute the callback when
/// the timer is ready.
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

    /// @brief Types of the lease files used by the Lease File Cleanup.
    ///
    /// This enumeration is used by a method which appends the appropriate
    /// suffix to the lease file name.
    enum LFCFileType {
        FILE_CURRENT,
        FILE_INPUT,
        FILE_PREVIOUS,
        FILE_OUTPUT,
        FILE_FINISH,
        FILE_PID
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

    /// @brief Appends appropriate suffix to the file name.
    ///
    /// The suffix is selected using the LFC file type specified as a
    /// parameter. Each file type uses a unique suffix or no suffix:
    /// - Current File: no suffix
    /// - Lease File Copy or Input File: ".1"
    /// - Previous File: ".2"
    /// - LFC Output File: ".output"
    /// - LFC Finish File: ".completed"
    ///
    /// See http://kea.isc.org/wiki/LFCDesign for details.
    ///
    /// @param file_name A base file name to which suffix is appended.
    /// @param file_type An LFC file type.
    /// @return A lease file name with a suffix appended.
    static std::string appendSuffix(const std::string& file_name,
                                    const LFCFileType& file_type);

    /// @brief Returns the interval at which the @c IOService events should
    /// be released.
    ///
    /// The Memfile backend may install a timer to execute the Lease File
    /// Cleanup periodically. If this timer is installed, the method returns
    /// the LFC interval in milliseconds.
    ///
    /// @return A maximum interval (in seconds) at which the @c IOService
    /// should be executed. A value of 0 means that no timers are installed
    /// and that there is no requirement for the @c IOService to be
    /// executed at any specific interval.
    virtual uint32_t getIOServiceExecInterval() const;

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
    ///
    /// @todo Once the callback is implemented, there is a need to
    /// extend the documentation of this method. Currently, it simply
    /// logs that it has been called.
    virtual void lfcCallback();

private:

    /// @brief Setup the periodic Lease File Cleanup.
    ///
    /// This method checks if the @c lfc-interval configuration parameter
    /// is set to a non-zero value and sets up the interval timer to
    /// perform the Lease File Cleanup periodically. It also prepares the
    /// path and arguments for the @c kea-lfc application which will be
    /// executed to perform the cleanup. By default the backend will use
    /// the path to the kea-lfc in the Kea installation directory. If
    /// the unit tests need to override this path (with the path in the
    /// Kea build directory, the @c KEA_LFC_EXECUTABLE environmental
    /// variable should be set to hold an absolute path to the kea-lfc
    /// excutable.
    void lfcSetup();

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

    template<typename LeaseFileType>
    void leaseFileCleanup(boost::shared_ptr<LeaseFileType>& lease_file);

    /// @brief Load leases from the persistent storage.
    ///
    /// This method loads DHCPv4 or DHCPv6 leases from lease files in the
    /// following order:
    /// - If the <filename>.completed doesn't exist:
    ///   - leases from the <filename>.2
    ///   - leases from the <filename>.1
    ///   - leases from the <filename>
    /// - else
    ///   - leases from the <filename>.completed
    ///   - leases from the <filename>
    ///
    /// If any of the files doesn't exist the method proceeds to reading
    /// leases from the subsequent file. If the <filename> doesn't exist
    /// it is created.
    ///
    /// When the method successfully reads leases from the files, it leaves
    /// the file <filename> open and its internal pointer is set to the
    /// end of file. The server will append lease entries to this file as
    /// a result of processing new messages from the clients.
    ///
    /// The <filename>.2, <filename>.1 and <filename>.completed are the
    /// products of the lease file cleanups (LFC).
    /// See: http://kea.isc.org/wiki/LFCDesign for details.
    ///
    /// @param filename Name of the lease file.
    /// @param lease_file An object representing a lease file to which
    /// the server will store lease updates.
    /// @param storage A storage for leases read from the lease file.
    /// @tparam LeaseObjectType @c Lease4 or @c Lease6.
    /// @tparam LeaseFileType @c CSVLeaseFile4 or @c CSVLeaseFile6.
    /// @tparam StorageType @c Lease4Storage or @c Lease6Storage.
    ///
    /// @throw CSVFileError when parsing any of the lease files fails.
    template<typename LeaseObjectType, typename LeaseFileType,
             typename StorageType>
    void loadLeasesFromFiles(const std::string& filename,
                             boost::shared_ptr<LeaseFileType>& lease_file,
                             StorageType& storage);

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

protected:

    /// @brief An object representing the kea-lfc process.
    ///
    /// This object is created when the LFC is configured to be executed
    /// periodically. It holds the path to kea-lfc program and the
    /// arguments. When the LFC timer kicks the lease file cleanup
    /// this object is used to spawn the kea-lfc as a background
    /// process.
    boost::scoped_ptr<util::ProcessSpawn> lfc_process_;

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // MEMFILE_LEASE_MGR_H
