// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/testutils/lease_file_io.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
	char filename[256];
	sprintf(filename, "/tmp/libfuzzer.%d", getpid());

	FILE *fp = fopen(filename, "wb");
	if (!fp)
		return 0;
	fwrite(Data, Size, 1, fp);
	fclose(fp);

    try {
        CSVLeaseFile4 lease_file(filename);
        lease_file.open(false);
        Lease4Ptr lease;
        lease_file.next(lease);
        lease_file.close();
    } catch (const std::exception&) {
      // ignore any errors
    }

    try {
        CSVLeaseFile6 lease_file(filename);
        lease_file.open(false);
        Lease6Ptr lease;
        lease_file.next(lease);
        lease_file.close();
    } catch (const std::exception&) {
        // ignore any errors
    }

    unlink(filename);
    return 0;
}
