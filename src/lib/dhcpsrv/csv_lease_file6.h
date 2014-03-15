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

#ifndef CSV_LEASE_FILE6_H
#define CSV_LEASE_FILE6_H

#include <dhcpsrv/lease.h>
#include <util/csv_file.h>

namespace isc {
namespace dhcp {

class CSVLeaseFile6 : public isc::util::CSVFile {
public:

    CSVLeaseFile6(const std::string& filename);

    void append(const Lease6& lease) const;

private:

    void initColumns();

};

} // namespace isc::dhcp
} // namespace isc

#endif // CSV_LEASE_FILE6_H
