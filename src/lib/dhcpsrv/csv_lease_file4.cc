// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <ctime>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

CSVLeaseFile4::CSVLeaseFile4(const std::string& filename)
    : VersionedCSVFile(filename) {
    initColumns();
}

void
CSVLeaseFile4::open(const bool seek_to_end) {
    // Call the base class to open the file
    VersionedCSVFile::open(seek_to_end);

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
    row.writeAt(getColumnIndex("expire"), static_cast<uint64_t>(lease.cltt_ + lease.valid_lft_));
    row.writeAt(getColumnIndex("subnet_id"), lease.subnet_id_);
    row.writeAt(getColumnIndex("fqdn_fwd"), lease.fqdn_fwd_);
    row.writeAt(getColumnIndex("fqdn_rev"), lease.fqdn_rev_);
    row.writeAt(getColumnIndex("hostname"), lease.hostname_);
    row.writeAt(getColumnIndex("state"), lease.state_);
    // User context is optional.
    if (lease.getContext()) {
        row.writeAt(getColumnIndex("user_context"), lease.getContext()->str());
    }

    try {
        VersionedCSVFile::append(row);
    } catch (const std::exception&) {
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
        VersionedCSVFile::next(row);
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
        uint32_t state = readState(row);
        if (hwaddr.hwaddr_.empty() && state != Lease::STATE_DECLINED) {
            isc_throw(isc::BadValue, "A blank hardware address is only"
                      " valid for declined leases");
        }

        // Get the user context (can be NULL).
        ConstElementPtr ctx = readContext(row);

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
        lease->state_ = state;

        if (ctx) {
            lease->setContext(ctx);
        }

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
    addColumn("address", "1.0");
    addColumn("hwaddr", "1.0");
    addColumn("client_id", "1.0");
    addColumn("valid_lifetime", "1.0");
    addColumn("expire", "1.0");
    addColumn("subnet_id", "1.0");
    addColumn("fqdn_fwd", "1.0");
    addColumn("fqdn_rev", "1.0");
    addColumn("hostname", "1.0");
    addColumn("state", "2.0", "0");
    addColumn("user_context", "2.1");
    // Any file with less than hostname is invalid
    setMinimumValidColumns("hostname");
}

IOAddress
CSVLeaseFile4::readAddress(const CSVRow& row) {
    IOAddress address(row.readAt(getColumnIndex("address")));
    return (address);
}

HWAddr
CSVLeaseFile4::readHWAddr(const CSVRow& row) {
    HWAddr hwaddr = HWAddr::fromText(row.readAt(getColumnIndex("hwaddr")));
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
    time_t cltt =
        static_cast<time_t>(row.readAndConvertAt<uint64_t>(getColumnIndex("expire"))
                            - readValid(row));
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

uint32_t
CSVLeaseFile4::readState(const util::CSVRow& row) {
    uint32_t state = row.readAndConvertAt<uint32_t>(getColumnIndex("state"));
    return (state);
}

ConstElementPtr
CSVLeaseFile4::readContext(const util::CSVRow& row) {
    std::string user_context = row.readAt(getColumnIndex("user_context"));
    if (user_context.empty()) {
        return (ConstElementPtr());
    }
    ConstElementPtr ctx = Element::fromJSON(user_context);
    if (!ctx || (ctx->getType() != Element::map)) {
        isc_throw(isc::BadValue, "user context '" << user_context
                  << "' is not a JSON map");
    }
    return (ctx);
}

} // end of namespace isc::dhcp
} // end of namespace isc
