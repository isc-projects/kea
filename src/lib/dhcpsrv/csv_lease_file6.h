// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CSV_LEASE_FILE6_H
#define CSV_LEASE_FILE6_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease_file_stats.h>
#include <util/optional.h>
#include <util/versioned_csv_file.h>

#include <stdint.h>

#include <string>

namespace isc {
namespace dhcp {

/// @brief Provides methods to access CSV file with DHCPv6 leases.
///
/// This class contains methods customized to read and write DHCPv6 leases from
/// and to the CSV file. It expects that the CSV file being parsed contains a
/// set of columns with well known names (initialized in the class constructor).
///
/// @todo This class doesn't validate the lease values read from the file.
/// The @c Lease6 is a structure that should be itself responsible for this
/// validation. However, the @c next function may need to be updated to use the
/// validation capability of @c Lease6.
class CSVLeaseFile6 : public isc::util::VersionedCSVFile, public LeaseFileStats {
public:

    /// @brief Constructor.
    ///
    /// Initializes columns of the lease file.
    ///
    /// @param filename Name of the lease file.
    CSVLeaseFile6(const std::string& filename);

    /// @brief Opens a lease file.
    ///
    /// This function calls the base class open to do the
    /// work of opening a file.  It is used to clear any
    /// statistics associated with any previous use of the file
    /// While it doesn't throw any exceptions of its own
    /// the base class may do so.
    virtual void open(const bool seek_to_end = false);

    /// @brief Appends the lease record to the CSV file.
    ///
    /// This function doesn't throw exceptions itself. In theory, exceptions
    /// are possible when the index of the indexes of the values being written
    /// to the file are invalid. However, this would have been a programming
    /// error.
    ///
    /// @param lease Structure representing a DHCPv6 lease.
    /// @throw BadValue if the lease to be written has an empty DUID and is
    /// whose state is not STATE_DECLINED.
    void append(const Lease6& lease);

    /// @brief Reads next lease from the CSV file.
    ///
    /// If this function hits an error during lease read, it sets the error
    /// message using @c CSVFile::setReadMsg and returns false. The error
    /// string may be read using @c CSVFile::getReadMsg.
    ///
    /// This function is exception safe.
    ///
    /// @param [out] lease Pointer to the lease read from CSV file or
    /// NULL pointer if lease hasn't been read.
    ///
    /// @return Boolean value indicating that the new lease has been
    /// read from the CSV file (if true), or that the error has occurred
    /// (false).
    ///
    /// @todo Make sure that the values read from the file are correct.
    /// The appropriate @c Lease6 validation mechanism should be used.
    bool next(Lease6Ptr& lease);

private:

    /// @brief Initializes columns of the CSV file holding leases.
    ///
    /// This function initializes the following columns:
    /// - address
    /// - duid
    /// - valid_lifetime
    /// - expire
    /// - subnet_id
    /// - pref_lifetime
    /// - lease_type
    /// - iaid
    /// - prefix_len
    /// - fqdn_fwd
    /// - fqdn_rev
    /// - hostname
    /// - hwaddr
    /// - state
    /// - user_context
    /// - hwtype
    /// - hwaddr_source
    /// - pool_id
    void initColumns();

    ///
    /// @name Methods which read specific lease fields from the CSV row.
    ///
    //@{
    ///
    /// @brief Reads lease type from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    Lease::Type readType(const util::CSVRow& row);

    /// @brief Reads lease address from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    asiolink::IOAddress readAddress(const util::CSVRow& row);

    /// @brief Reads DUID from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    DuidPtr readDUID(const util::CSVRow& row);

    /// @brief Reads IAID from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    uint32_t readIAID(const util::CSVRow& row);

    /// @brief Reads preferred lifetime from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    uint32_t readPreferred(const util::CSVRow& row);

    /// @brief Reads valid lifetime from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    uint32_t readValid(const util::CSVRow& row);

    /// @brief Reads cltt value from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    uint32_t readCltt(const util::CSVRow& row);

    /// @brief Reads subnet id from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    SubnetID readSubnetID(const util::CSVRow& row);

    /// @brief Reads pool id from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    uint32_t readPoolID(const util::CSVRow& row);

    /// @brief Reads prefix length from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    uint8_t readPrefixLen(const util::CSVRow& row);

    /// @brief Reads the FQDN forward flag from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    bool readFqdnFwd(const util::CSVRow& row);

    /// @brief Reads the FQDN reverse flag from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    bool readFqdnRev(const util::CSVRow& row);

    /// @brief Reads hostname from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    std::string readHostname(const util::CSVRow& row);

    /// @brief Reads HW address from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    /// @return pointer to the HWAddr structure that was read
    HWAddrPtr readHWAddr(const util::CSVRow& row);

    /// @brief Reads lease state from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    uint32_t readState(const util::CSVRow& row);

    /// @brief Reads lease user context from the CSV file row.
    ///
    /// @param row CSV file row holding lease information.
    data::ConstElementPtr readContext(const util::CSVRow& row);

    /// @brief Reads hardware address type from the CSV file row.
    ///
    /// @param row CSV file row holding lease information
    ///
    /// @return the integer value of the hardware address type that was read
    /// or an unspecified Optional if it is not specified in the CSV
    isc::util::Optional<uint16_t> readHWType(const util::CSVRow& row);

    /// @brief Reads hardware address source from the CSV file row.
    ///
    /// @param row CSV file row holding lease information
    ///
    /// @return the integer value of the hardware address source that was read
    /// or an unspecified Optional if it is not specified in the CSV
    isc::util::Optional<uint32_t> readHWAddrSource(const util::CSVRow& row);
    //@}
};

} // namespace isc::dhcp
} // namespace isc

#endif // CSV_LEASE_FILE6_H
