
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

#ifndef __DATA_SOURCE_SIMPLE_H
#define __DATA_SOURCE_SIMPLE_H

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/message.h>

#include <cc/data.h>

#include "common.h"

#include "data_source.h"

#include "zoneset.h"

namespace isc {
namespace dns {

class DataSourceParkingLot : public DataSource {
public:
    DataSourceParkingLot();
    
    void init() {};
    void close() {};
    bool hasZoneFor(const Name& name, Name &zone_name);
    SearchResult findRRsets(const isc::dns::Name& zone_name,
                            const isc::dns::Name& name,
                            const isc::dns::RRClass& clas,
                            const isc::dns::RRType& type) const;

    /* move these to private (or to zoneset) and the calling functions
     * from parkinglot to here? */
    void serve(std::string zone_name);
    void clear_zones() { zones.clear_zones(); };

    void clearARecords() { a_records.clear(); };
    void clearAAAARecords() { aaaa_records.clear(); };
    void clearNSRecords() { ns_records.clear(); };

    void addARecord(std::string data);
    void addAAAARecord(std::string data);
    void addNSRecord(std::string data);

    void setSOARecord(isc::dns::rdata::RdataPtr soa_record);

    /// Do direct 'search' in database, no extra processing,
    /// and add the resulting rrsets to the specified section
    /// in the given message
    /// Once the dns logic is moved from parkinglot to this class,
    /// we should probably make this private
    SearchResult::status_type addToMessage(Message& msg,
                                           const isc::dns::Section& section,
                                           const isc::dns::Name& zone_name,
                                           const isc::dns::Name& name,
                                           const isc::dns::RRClass& clas,
                                           const isc::dns::RRType& type) const;

private:
    //
    void setDefaultZoneData();

    std::vector<isc::dns::rdata::RdataPtr> a_records, aaaa_records, ns_records;
    isc::dns::rdata::RdataPtr soa;
    ZoneSet zones;

};

}
}

#endif

// Local Variables: 
// mode: c++
// End: 
