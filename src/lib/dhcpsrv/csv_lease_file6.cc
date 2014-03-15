// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/csv_lease_file6.h>

using namespace isc::util;

namespace isc {
namespace dhcp {

CSVLeaseFile6::CSVLeaseFile6(const std::string& filename)
    : CSVFile(filename) {
    initColumns();
}

void
CSVLeaseFile6::initColumns() {
    addColumn("address");
    addColumn("duid");
    addColumn("valid_lifetime");
    addColumn("expire");
    addColumn("subnet_id");
    addColumn("pref_lifetime");
    addColumn("lease_type");
    addColumn("iaid");
    addColumn("prefix_len");
    addColumn("fqdn_fwd");
    addColumn("fqdn_rev");
    addColumn("hostname");
}

void
CSVLeaseFile6::append(const Lease6& lease) const {
    CSVRow row(getColumnCount());
    row.writeAt(getColumnIndex("address"), lease.addr_.toText());
    row.writeAt(getColumnIndex("duid"), lease.duid_->toText());
    row.writeAt(getColumnIndex("valid_lifetime"), lease.valid_lft_);
    row.writeAt(getColumnIndex("expire"), lease.cltt_ + lease.valid_lft_);
    row.writeAt(getColumnIndex("subnet_id"), lease.subnet_id_);
    row.writeAt(getColumnIndex("pref_lifetime"), lease.preferred_lft_);
    row.writeAt(getColumnIndex("lease_type"), lease.type_);
    row.writeAt(getColumnIndex("iaid"), lease.iaid_);
    row.writeAt(getColumnIndex("prefix_len"),
                static_cast<int>(lease.prefixlen_));
    row.writeAt(getColumnIndex("fqdn_fwd"), lease.fqdn_fwd_);
    row.writeAt(getColumnIndex("fqdn_rev"), lease.fqdn_rev_);
    row.writeAt(getColumnIndex("hostname"), lease.hostname_);
    CSVFile::append(row);
}


} // end of namespace isc::dhcp
} // end of namespace isc
