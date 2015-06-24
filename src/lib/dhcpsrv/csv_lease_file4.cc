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

#include <config.h>
#include <dhcpsrv/csv_lease_file4.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

CSVLeaseFile4::CSVLeaseFile4(const std::string& filename)
    : CSVFile(filename) {
    initColumns();
}

void
CSVLeaseFile4::open(const bool seek_to_end) {
    // Call the base class to open the file
    CSVFile::open(seek_to_end);

    // and clear any statistics we may have
    clearStatistics();
}

void
CSVLeaseFile4::append(const Lease4& lease) {
    // Bump the number of write attempts
    ++writes_;

    CSVRow row(getColumnCount());
    row.writeAt(getColumnIndex("address"), lease.addr_.toText());
    if (!lease.hwaddr_) {
        // Bump the error counter
        ++write_errs_;

        isc_throw(BadValue, "Lease4 must have hardware address specified.");
    }
    row.writeAt(getColumnIndex("hwaddr"), lease.hwaddr_->toText(false));
    // Client id may be unset (NULL).
    if (lease.client_id_) {
        row.writeAt(getColumnIndex("client_id"), lease.client_id_->toText());
    }
    row.writeAt(getColumnIndex("valid_lifetime"), lease.valid_lft_);
    row.writeAt(getColumnIndex("expire"), lease.cltt_ + lease.valid_lft_);
    row.writeAt(getColumnIndex("subnet_id"), lease.subnet_id_);
    row.writeAt(getColumnIndex("fqdn_fwd"), lease.fqdn_fwd_);
    row.writeAt(getColumnIndex("fqdn_rev"), lease.fqdn_rev_);
    row.writeAt(getColumnIndex("hostname"), lease.hostname_);

    try {
        CSVFile::append(row);
    } catch (const std::exception& ex) {
        // Catch any errors so we can bump the error counter than rethrow it
        ++write_errs_;
        throw;
    }

    // Bump the number of leases written
    ++write_leases_;
}

bool
CSVLeaseFile4::next(Lease4Ptr& lease) {
    // Bump the number of read attempts
    ++reads_;

    // Read the CSV row and try to create a lease from the values read.
    // This may easily result in exception. We don't want this function
    // to throw exceptions, so we catch them all and rather return the
    // false value.
    try {
        // Get the row of CSV values.
        CSVRow row;
        CSVFile::next(row);
        // The empty row signals EOF.
        if (row == CSVFile::EMPTY_ROW()) {
            lease.reset();
            return (true);
        }

        // Get client id. It is possible that the client id is empty and the
        // returned pointer is NULL. This is ok, but if the client id is NULL,
        // we need to be careful to not use the NULL pointer.
        ClientIdPtr client_id = readClientId(row);
        std::vector<uint8_t> client_id_vec;
        if (client_id) {
            client_id_vec = client_id->getClientId();
        }
        size_t client_id_len = client_id_vec.size();

        // Get the HW address. It should never be empty and the readHWAddr checks
        // that.
        HWAddr hwaddr = readHWAddr(row);
        lease.reset(new Lease4(readAddress(row),
                               HWAddrPtr(new HWAddr(hwaddr)),
                               client_id_vec.empty() ? NULL : &client_id_vec[0],
                               client_id_len,
                               readValid(row),
                               0, 0, // t1, t2 = 0
                               readCltt(row),
                               readSubnetID(row),
                               readFqdnFwd(row),
                               readFqdnRev(row),
                               readHostname(row)));

    } catch (std::exception& ex) {
        // bump the read error count
        ++read_errs_;

        // The lease might have been created, so let's set it back to NULL to
        // signal that lease hasn't been parsed.
        lease.reset();
        setReadMsg(ex.what());
        return (false);
    }

    // bump the number of leases read
    ++read_leases_;

    return (true);
}

void
CSVLeaseFile4::initColumns() {
    addColumn("address");
    addColumn("hwaddr");
    addColumn("client_id");
    addColumn("valid_lifetime");
    addColumn("expire");
    addColumn("subnet_id");
    addColumn("fqdn_fwd");
    addColumn("fqdn_rev");
    addColumn("hostname");
}

IOAddress
CSVLeaseFile4::readAddress(const CSVRow& row) {
    IOAddress address(row.readAt(getColumnIndex("address")));
    return (address);
}

HWAddr
CSVLeaseFile4::readHWAddr(const CSVRow& row) {
    HWAddr hwaddr = HWAddr::fromText(row.readAt(getColumnIndex("hwaddr")));
    if (hwaddr.hwaddr_.empty()) {
        isc_throw(isc::BadValue, "hardware address in the lease file"
                  " must not be empty");
    }
    return (hwaddr);
}

ClientIdPtr
CSVLeaseFile4::readClientId(const CSVRow& row) {
    std::string client_id = row.readAt(getColumnIndex("client_id"));
    // NULL client ids are allowed in DHCPv4.
    if (client_id.empty()) {
        return (ClientIdPtr());
    }
    ClientIdPtr cid = ClientId::fromText(client_id);
    return (cid);
}

uint32_t
CSVLeaseFile4::readValid(const CSVRow& row) {
    uint32_t valid =
        row.readAndConvertAt<uint32_t>(getColumnIndex("valid_lifetime"));
    return (valid);
}

time_t
CSVLeaseFile4::readCltt(const CSVRow& row) {
    uint32_t cltt = row.readAndConvertAt<uint32_t>(getColumnIndex("expire"))
        - readValid(row);
    return (cltt);
}

SubnetID
CSVLeaseFile4::readSubnetID(const CSVRow& row) {
    SubnetID subnet_id =
        row.readAndConvertAt<SubnetID>(getColumnIndex("subnet_id"));
    return (subnet_id);
}

bool
CSVLeaseFile4::readFqdnFwd(const CSVRow& row) {
    bool fqdn_fwd = row.readAndConvertAt<bool>(getColumnIndex("fqdn_fwd"));
    return (fqdn_fwd);
}

bool
CSVLeaseFile4::readFqdnRev(const CSVRow& row) {
    bool fqdn_rev = row.readAndConvertAt<bool>(getColumnIndex("fqdn_rev"));
    return (fqdn_rev);
}

std::string
CSVLeaseFile4::readHostname(const CSVRow& row) {
    std::string hostname = row.readAt(getColumnIndex("hostname"));
    return (hostname);
}

} // end of namespace isc::dhcp
} // end of namespace isc
