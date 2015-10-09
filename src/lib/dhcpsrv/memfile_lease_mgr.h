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
#include <dhcpsrv/database_connection.h>
#include <dhcpsrv/lease_mgr.h>
#include <util/process_spawn.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

class LFCSetup;

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
/// from the lease file(s).
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
    /// This enumeration is used by various functions in Memfile %Lease Manager,
    /// to identify the lease type referred to. In particular, it is used by
    /// functions operating on the lease files to distinguish between lease
    /// files for DHCPv4 and DHCPv6.
    enum Universe {
        V4,
        V6
    };

    /// @name Methods implementing the API of the lease database backend.
    ///       The following methods are implementing the API of the
    ///       @c LeaseMgr to manage leases.
    //@{

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    Memfile_LeaseMgr(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor (closes file)
    virtual ~Memfile_LeaseMgr();

    /// @brief Local version of getDBVersion() class method
    static std::string getDBVersion();

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

    /// @brief Returns a collection of expired DHCPv6 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases6(Lease6Collection& expired_leases,
                                   const size_t max_leases) const;


    /// @brief Returns a collection of expired DHCPv4 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases4(Lease4Collection& expired_leases,
                                   const size_t max_leases) const;

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

    /// @brief Deletes all expired-reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t secs);

    /// @brief Deletes all expired-reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t secs);

private:

    /// @brief Deletes all expired-reclaimed leases.
    ///
    /// This private method is called by both of the public methods:
    /// @c deleteExpiredReclaimedLeases4 and
    /// @c deleteExpiredReclaimedLeases6 to remove all expired
    /// reclaimed DHCPv4 or DHCPv6 leases respectively.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    /// @param universe V4 or V6.
    /// @param storage Reference to the container where leases are held.
    /// Some expired-reclaimed leases will be removed from this container.
    /// @param lease_file Reference to a DHCPv4 or DHCPv6 lease file
    /// instance where leases should be marked as deleted.
    ///
    /// @return Number of leases deleted.
    ///
    /// @tparam IndexType Index type to be used to search for the
    /// expired-reclaimed leases, i.e.
    /// @c Lease4StorageExpirationIndex or @c Lease6StorageExpirationIndex.
    /// @tparam LeaseType Lease type, i.e. @c Lease4 or @c Lease6.
    /// @tparam StorageType Type of storage where leases are held, i.e.
    /// @c Lease4Storage or @c Lease6Storage.
    /// @tparam LeaseFileType Type of the lease file, i.e. DHCPv4 or
    /// DHCPv6 lease file type.
    template<typename IndexType, typename LeaseType, typename StorageType,
             typename LeaseFileType>
    uint64_t deleteExpiredReclaimedLeases(const uint32_t secs,
                                          const Universe& universe,
                                          StorageType& storage,
                                          LeaseFileType& lease_file) const;

public:

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

    //@}

    /// @name Public type and method used to determine file names for LFC.
    //@{

    /// @brief Types of the lease files used by the %Lease File Cleanup.
    ///
    /// This enumeration is used by a method which appends the appropriate
    /// suffix to the lease file name.
    enum LFCFileType {
        FILE_CURRENT,  ///< %Lease File
        FILE_INPUT,    ///< %Lease File Copy
        FILE_PREVIOUS, ///< Previous %Lease File
        FILE_OUTPUT,   ///< LFC Output File
        FILE_FINISH,   ///< LFC Finish File
        FILE_PID       ///< PID File
    };

    /// @brief Appends appropriate suffix to the file name.
    ///
    /// The suffix is selected using the LFC file type specified as a
    /// parameter. Each file type uses a unique suffix or no suffix:
    /// - Current File: no suffix
    /// - %Lease File Copy or Input File: ".1"
    /// - Previous File: ".2"
    /// - LFC Output File: ".output"
    /// - LFC Finish File: ".completed"
    /// - LFC PID File: ".pid"
    ///
    /// See http://kea.isc.org/wiki/LFCDesign for details.
    ///
    /// @param file_name A base file name to which suffix is appended.
    /// @param file_type An LFC file type.
    /// @return A lease file name with a suffix appended.
    static std::string appendSuffix(const std::string& file_name,
                                    const LFCFileType& file_type);
    //@}


    /// @name Miscellaneous public convenience methods.
    ///       The following methods allow for retrieving useful information
    ///       about the state of the backend.
    //@{

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

    //@}

private:


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
    /// @note: When the server starts up or is reconfigured it will try to
    /// read leases from the lease files using this method. It is possible
    /// that the %Lease File Cleanup is performed upon the lease files to
    /// be read by this method. This may result in conflicts between the
    /// server process and the LFC. To prevent it, the method checks if the
    /// instance of the @c kea-lfc is running (using the PID file) before it
    /// tries to load leases from the lease files. If it finds that there
    /// is an LFC in progress, it throws an exception which will result
    /// in the server refuse to start or reconfigure. When the administrator
    /// retries starting up or reconfiguring the server it will most likely
    /// be successful as the LFC should be complete by that time.
    ///
    /// @todo Consider implementing delaying the lease files loading when
    /// the LFC is in progress by the specified amount of time.
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
    /// @throw DbOpenError when it is found that the LFC is in progress.
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

public:

    /// @name Public methods to retrieve information about the LFC process state.
    ///       These methods are meant to be used by unit tests to retrieve the
    ///       state of the spawned LFC process before validating the result of
    ///       the lease file cleanup.
    //@{

    /// @brief Checks if the process performing lease file cleanup is running.
    ///
    /// @return true if the process performing lease file cleanup is running.
    bool isLFCRunning() const;

    /// @brief Returns the status code returned by the last executed
    /// LFC process.
    int getLFCExitStatus() const;
    //@}


    /// @name Protected methods used for %Lease File Cleanup.
    /// The following methods are protected so as they can be accessed and
    /// tested by unit tests.
    //@{

protected:

    /// @brief A callback function triggering %Lease File Cleanup (LFC).
    ///
    /// This method is executed periodically to start the lease file cleanup.
    /// It checks whether the file is a DHCPv4 lease file or DHCPv6 lease file
    /// and executes the @c Memfile_LeaseMgr::lfcExecute private method
    /// with the appropriate parameters.
    ///
    /// This method is virtual so as it can be overridden and customized in
    /// the unit tests. In particular, the unit test which checks that the
    /// callback function has been executed would override this function
    /// to increase the execution counter each time it is executed.
    virtual void lfcCallback();
    //@}

    /// @name Private methods and members used for %Lease File Cleanup.
    //@{

private:

    /// @brief Setup the periodic %Lease File Cleanup.
    ///
    /// This method checks if the @c lfc-interval configuration parameter
    /// is set to a non-zero value and sets up the interval timer to
    /// perform the %Lease File Cleanup periodically. It also prepares the
    /// path and arguments for the @c kea-lfc application which will be
    /// executed to perform the cleanup. By default the backend will use
    /// the path to the kea-lfc in the Kea installation directory. If
    /// the unit tests need to override this path (with the path in the
    /// Kea build directory, the @c KEA_LFC_EXECUTABLE environmental
    /// variable should be set to hold an absolute path to the kea-lfc
    /// excutable.
    void lfcSetup();

    /// @brief Performs a lease file cleanup for DHCPv4 or DHCPv6.
    ///
    /// This method performs all the actions necessary to prepare for the
    /// execution of the LFC and if these actions are successful, it executes
    /// the @c kea-lfc application as a background process to process (cleanup)
    /// the lease files.
    ///
    /// For the design and the terminology used in this description refer to
    /// the http://kea.isc.org/wiki/LFCDesign.
    ///
    /// If the method finds that the %Lease File Copy exists it simply runs
    /// the @c kea-lfc application.
    ///
    /// If the %Lease File Copy doesn't exist it moves the Current %Lease File
    /// to Lease File Copy, and then recreates the Current Lease File without
    /// any lease entries. If the file has been successfully moved, it runs
    /// the @c kea-lfc application.
    ///
    /// @param lease_file A pointer to the object representing the Current
    /// %Lease File (DHCPv4 or DHCPv6 lease file).
    ///
    /// @tparam LeaseFileType One of @c CSVLeaseFile4 or @c CSVLeaseFile6.
    template<typename LeaseFileType>
    void lfcExecute(boost::shared_ptr<LeaseFileType>& lease_file);

    /// @brief A pointer to the Lease File Cleanup configuration.
    boost::scoped_ptr<LFCSetup> lfc_setup_;

    /// @brief Parameters storage
    ///
    /// DatabaseConnection object is used only for storing, accessing and
    /// printing parameter map.
    DatabaseConnection conn_;

    //@}
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // MEMFILE_LEASE_MGR_H
