// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CSV_LEASE_FILE4_H
#define CSV_LEASE_FILE4_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease_file_stats.h>
#include <util/csv_file.h>
#include <stdint.h>
#include <string>
#include <time.h>

namespace isc {
namespace dhcp {

/// @brief Provides methods to access CSV file with DHCPv4 leases.
///
/// This class contains methods customized to read and write DHCPv4 leases from
/// and to the CSV file. It expects that the CSV file being parsed contains a
/// set of columns with well known names (initialized in the class constructor).
///
/// @todo This class doesn't validate the lease values read from the file.
/// The @c Lease4 is a structure that should be itself responsible for this
/// validation (see http://kea.isc.org/ticket/2405). However, when #2405
/// is implemented, the @c next function may need to be updated to use the
/// validation capablity of @c Lease4.
class CSVLeaseFile4 : public isc::util::CSVFile, public LeaseFileStats {
public:

    /// @brief Constructor.
    ///
    /// Initializes columns of the lease file.
    ///
    /// @param filename Name of the lease file.
    CSVLeaseFile4(const std::string& filename);

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
    /// @param lease Structure representing a DHCPv4 lease.
    void append(const Lease4& lease);

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
    /// The appropriate @c Lease4 validation mechanism should be used once
    /// ticket http://kea.isc.org/ticket/2405 is implemented.
    bool next(Lease4Ptr& lease);

private:

    /// @brief Initializes columns of the CSV file holding leases.
    ///
    /// This function initializes the following columns:
    /// - address
    /// - hwaddr
    /// - client_id
    /// - valid_lifetime
    /// - expire
    /// - subnet_id
    /// - fqdn_fwd
    /// - fqdn_rev
    /// - hostname
    void initColumns();

    ///
    /// @name Methods which read specific lease fields from the CSV row.
    ///
    //@{
    ///
    /// @brief Reads lease address from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    asiolink::IOAddress readAddress(const util::CSVRow& row);

    /// @brief Reads HW address from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    HWAddr readHWAddr(const util::CSVRow& row);

    /// @brief Reads client identifier from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    ClientIdPtr readClientId(const util::CSVRow& row);

    /// @brief Reads valid lifetime from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    uint32_t readValid(const util::CSVRow& row);

    /// @brief Reads cltt value from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    time_t readCltt(const util::CSVRow& row);

    /// @brief Reads subnet id from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    SubnetID readSubnetID(const util::CSVRow& row);

    /// @brief Reads the FQDN forward flag from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    bool readFqdnFwd(const util::CSVRow& row);

    /// @brief Reads the FQDN reverse flag from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    bool readFqdnRev(const util::CSVRow& row);

    /// @brief Reads hostname from the CSV file row.
    ///
    /// @param row CSV file holding lease values.
    std::string readHostname(const util::CSVRow& row);
    //@}

};

} // namespace isc::dhcp
} // namespace isc

#endif // CSV_LEASE_FILE4_H
