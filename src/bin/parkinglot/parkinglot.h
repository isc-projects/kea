// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __PARKINGLOT_H
#define __PARKINGLOT_H 1

#include "zoneset.h"
#include <cc/cpp/data.h>

class ParkingLot {
public:
    explicit ParkingLot(int port);
    virtual ~ParkingLot() {}
    int getSocket() { return (sock); }
    void processMessage();
    void command(std::pair<std::string,isc::data::ElementPtr>);
    void serve(std::string zone_name);
    void clear_zones() { zones.clear_zones(); };

    void clearARecords() { a_records.clear(); };
    void clearAAAARecords() { aaaa_records.clear(); };
    void clearNSRecords() { ns_records.clear(); };

    void addARecord(std::string data);
    void addAAAARecord(std::string data);
    void addNSRecord(std::string data);

    void setSOARecord(isc::dns::Rdata::RdataPtr soa_record);

private:
    void setDefaultZoneData();

    std::vector<isc::dns::Rdata::RdataPtr> a_records, aaaa_records, ns_records;
    isc::dns::Rdata::RdataPtr soa;
    ZoneSet zones;
    int sock;
};

#endif // __PARKINGLOT_H

// Local Variables:
// mode: c++
// End:
