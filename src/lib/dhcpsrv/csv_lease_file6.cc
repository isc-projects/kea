// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/csv_lease_file6.h>

#include <ctime>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

CSVLeaseFile6::CSVLeaseFile6(const std::string& filename)
    : VersionedCSVFile(filename) {
    initColumns();
}

void
CSVLeaseFile6::open(const bool seek_to_end) {
    // Call the base class to open the file
    VersionedCSVFile::open(seek_to_end);

    // and clear any statistics we may have
    clearStatistics();
}

void
CSVLeaseFile6::append(const Lease6& lease) {
    // Bump the number of write attempts
    ++writes_;

    if (((!(lease.duid_)) || (*(lease.duid_) == DUID::EMPTY())) &&
        (lease.state_ != Lease::STATE_DECLINED)) {
        ++write_errs_;
        isc_throw(BadValue, "Lease6: " << lease.addr_.toText() << ", state: "
                  << Lease::basicStatesToText(lease.state_) << ", has no DUID");
    }

    CSVRow row(getColumnCount());
    row.writeAt(getColumnIndex("address"), lease.addr_.toText());
    row.writeAt(getColumnIndex("duid"), lease.duid_->toText());
    row.writeAt(getColumnIndex("valid_lifetime"), lease.valid_lft_);
    row.writeAt(getColumnIndex("expire"), static_cast<uint64_t>(lease.cltt_) + lease.valid_lft_);
    row.writeAt(getColumnIndex("subnet_id"), lease.subnet_id_);
    row.writeAt(getColumnIndex("pref_lifetime"), lease.preferred_lft_);
    row.writeAt(getColumnIndex("lease_type"), lease.type_);
    row.writeAt(getColumnIndex("iaid"), lease.iaid_);
    row.writeAt(getColumnIndex("prefix_len"),
                static_cast<int>(lease.prefixlen_));
    row.writeAt(getColumnIndex("fqdn_fwd"), lease.fqdn_fwd_);
    row.writeAt(getColumnIndex("fqdn_rev"), lease.fqdn_rev_);
    row.writeAtEscaped(getColumnIndex("hostname"), lease.hostname_);
    // We may not have hardware information.
    if (lease.hwaddr_) {
        row.writeAt(getColumnIndex("hwaddr"), lease.hwaddr_->toText(false));
        row.writeAt(getColumnIndex("hwtype"), lease.hwaddr_->htype_);
        row.writeAt(getColumnIndex("hwaddr_source"), lease.hwaddr_->source_);
    }
    row.writeAt(getColumnIndex("state"), lease.state_);
    // User context is optional.
    if (lease.getContext()) {
        row.writeAtEscaped(getColumnIndex("user_context"), lease.getContext()->str());
    }
    row.writeAt(getColumnIndex("pool_id"), lease.pool_id_);
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
CSVLeaseFile6::next(Lease6Ptr& lease) {
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

        Lease::Type type = readType(row);
        uint8_t prefixlen = 128;
        if (type == Lease::TYPE_PD) {
            prefixlen = readPrefixLen(row);
        }

        lease.reset(new Lease6(type, readAddress(row), readDUID(row),
                               readIAID(row), readPreferred(row),
                               readValid(row),
                               readSubnetID(row),
                               readHWAddr(row),
                               prefixlen));

        lease->cltt_ = readCltt(row);
        lease->fqdn_fwd_ = readFqdnFwd(row);
        lease->fqdn_rev_ = readFqdnRev(row);
        lease->hostname_ = readHostname(row);
        lease->state_ = readState(row);

        if ((*lease->duid_ == DUID::EMPTY())
            && lease->state_ != Lease::STATE_DECLINED) {
            isc_throw(isc::BadValue,
                      "The Empty DUID is only valid for declined leases");
        }

        ConstElementPtr ctx = readContext(row);
        if (ctx) {
            lease->setContext(ctx);
        }

        lease->pool_id_ = readPoolID(row);
    } catch (const std::exception& ex) {
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
CSVLeaseFile6::initColumns() {
    addColumn("address", "1.0");
    addColumn("duid", "1.0");
    addColumn("valid_lifetime", "1.0");
    addColumn("expire", "1.0");
    addColumn("subnet_id", "1.0");
    addColumn("pref_lifetime", "1.0");
    addColumn("lease_type", "1.0");
    addColumn("iaid", "1.0");
    addColumn("prefix_len", "1.0");
    addColumn("fqdn_fwd", "1.0");
    addColumn("fqdn_rev", "1.0");
    addColumn("hostname", "1.0");
    addColumn("hwaddr", "2.0");
    addColumn("state", "3.0", "0" /* == STATE_DEFAULT */);
    addColumn("user_context", "3.1");
    // Default not added for hwtype and hwaddr_source, because they depend on
    // hwaddr having value. When a CSV lease having a hwaddr is upgraded to 4.0,
    // hwtype will have value "1" meaning HTYPE_ETHER and
    // hwaddr_source will have value "0" meaning HWADDR_SOURCE_UNKNOWN.
    addColumn("hwtype", "4.0");
    addColumn("hwaddr_source", "4.0");
    addColumn("pool_id", "5.0", "0");

    // Any file with less than hostname is invalid
    setMinimumValidColumns("hostname");
}

Lease::Type
CSVLeaseFile6::readType(const CSVRow& row) {
    return (static_cast<Lease::Type>
            (row.readAndConvertAt<int>(getColumnIndex("lease_type"))));
}

IOAddress
CSVLeaseFile6::readAddress(const CSVRow& row) {
    IOAddress address(row.readAt(getColumnIndex("address")));
    return (address);
}

DuidPtr
CSVLeaseFile6::readDUID(const util::CSVRow& row) {
    DuidPtr duid(new DUID(DUID::fromText(row.readAt(getColumnIndex("duid")))));
    return (duid);
}

uint32_t
CSVLeaseFile6::readIAID(const CSVRow& row) {
    uint32_t iaid = row.readAndConvertAt<uint32_t>(getColumnIndex("iaid"));
    return (iaid);
}

uint32_t
CSVLeaseFile6::readPreferred(const CSVRow& row) {
    uint32_t pref =
        row.readAndConvertAt<uint32_t>(getColumnIndex("pref_lifetime"));
    return (pref);
}

uint32_t
CSVLeaseFile6::readValid(const CSVRow& row) {
    uint32_t valid =
        row.readAndConvertAt<uint32_t>(getColumnIndex("valid_lifetime"));
    return (valid);
}

uint32_t
CSVLeaseFile6::readCltt(const CSVRow& row) {
    time_t cltt =
        static_cast<time_t>(row.readAndConvertAt<uint64_t>(getColumnIndex("expire"))
                            - readValid(row));
    return (static_cast<uint32_t>(cltt));
}

SubnetID
CSVLeaseFile6::readSubnetID(const CSVRow& row) {
    SubnetID subnet_id =
        row.readAndConvertAt<SubnetID>(getColumnIndex("subnet_id"));
    return (subnet_id);
}

uint32_t
CSVLeaseFile6::readPoolID(const CSVRow& row) {
    uint32_t pool_id =
        row.readAndConvertAt<uint32_t>(getColumnIndex("pool_id"));
    return (pool_id);
}

uint8_t
CSVLeaseFile6::readPrefixLen(const CSVRow& row) {
    int prefixlen = row.readAndConvertAt<int>(getColumnIndex("prefix_len"));
    return (static_cast<uint8_t>(prefixlen));
}

bool
CSVLeaseFile6::readFqdnFwd(const CSVRow& row) {
    bool fqdn_fwd = row.readAndConvertAt<bool>(getColumnIndex("fqdn_fwd"));
    return (fqdn_fwd);
}

bool
CSVLeaseFile6::readFqdnRev(const CSVRow& row) {
    bool fqdn_rev = row.readAndConvertAt<bool>(getColumnIndex("fqdn_rev"));
    return (fqdn_rev);
}

std::string
CSVLeaseFile6::readHostname(const CSVRow& row) {
    std::string hostname = row.readAtEscaped(getColumnIndex("hostname"));
    return (hostname);
}

HWAddrPtr
CSVLeaseFile6::readHWAddr(const CSVRow& row) {

    try {
        uint16_t const hwtype(readHWType(row).valueOr(HTYPE_ETHER));
        HWAddr hwaddr(
            HWAddr::fromText(row.readAt(getColumnIndex("hwaddr")), hwtype));
        if (hwaddr.hwaddr_.empty()) {
            return (HWAddrPtr());
        }
        hwaddr.source_ =
            readHWAddrSource(row).valueOr(HWAddr::HWADDR_SOURCE_UNKNOWN);

        /// @todo: HWAddr returns an object, not a pointer. Without HWAddr
        /// refactoring, at least one copy is unavoidable.

        // Let's return a pointer to new freshly created copy.
        return (HWAddrPtr(new HWAddr(hwaddr)));

    } catch (const std::exception& ex) {
        // That's worse. There was something in the file, but its conversion
        // to HWAddr failed. Let's log it on warning and carry on.
        LOG_WARN(dhcpsrv_logger, DHCPSRV_MEMFILE_READ_HWADDR_FAIL)
            .arg(ex.what());

        return (HWAddrPtr());
    }
}

uint32_t
CSVLeaseFile6::readState(const util::CSVRow& row) {
    uint32_t state = row.readAndConvertAt<uint32_t>(getColumnIndex("state"));
    return (state);
}

ConstElementPtr
CSVLeaseFile6::readContext(const util::CSVRow& row) {
    std::string user_context = row.readAtEscaped(getColumnIndex("user_context"));
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

Optional<uint16_t>
CSVLeaseFile6::readHWType(const CSVRow& row) {
    size_t const index(getColumnIndex("hwtype"));
    if (row.readAt(index).empty()) {
        return Optional<uint16_t>();
    }
    return row.readAndConvertAt<uint16_t>(index);
}

Optional<uint32_t>
CSVLeaseFile6::readHWAddrSource(const CSVRow& row) {
    size_t const index(getColumnIndex("hwaddr_source"));
    if (row.readAt(index).empty()) {
        return Optional<uint16_t>();
    }
    return row.readAndConvertAt<uint32_t>(index);
}

} // end of namespace isc::dhcp
} // end of namespace isc
