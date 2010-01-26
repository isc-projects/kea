
#include <boost/foreach.hpp>

#include "data_source_plot.h"

namespace isc {
namespace dns {

// this implementation returns fixed records,
// and does not allow update statements

using namespace isc::dns;
using namespace isc::dns::Rdata::IN;
using namespace isc::dns::Rdata::Generic;
using namespace isc::data;

void
DataSourceParkingLot::serve(std::string zone_name) {
    zones.serve(zone_name);
}

void
DataSourceParkingLot::addARecord(std::string data) {
    a_records.push_back(Rdata::RdataPtr(new A(data)));
}

void
DataSourceParkingLot::addAAAARecord(std::string data) {
    aaaa_records.push_back(Rdata::RdataPtr(new AAAA(data)));
}

void
DataSourceParkingLot::addNSRecord(std::string data) {
    ns_records.push_back(Rdata::RdataPtr(new NS(data)));
}

void
DataSourceParkingLot::setSOARecord(isc::dns::Rdata::RdataPtr soa_record) {
}

void
DataSourceParkingLot::setDefaultZoneData() {
    clearARecords();
    clearAAAARecords();
    clearNSRecords();

    addARecord("127.0.0.1");
    addAAAARecord("::1");
    addNSRecord("ns1.parking.example");
    addNSRecord("ns2.parking.example");
    addNSRecord("ns3.parking.example");
}

DataSourceParkingLot::DataSourceParkingLot() {
    setDefaultZoneData();
    soa = Rdata::RdataPtr(new SOA("parking.example", "noc.parking.example",
                                        1, 1800, 900, 604800, TTL(86400)));
}

bool
DataSourceParkingLot::hasZoneFor(const Name& name, Name &zone_name)
{
    return zones.findClosest(name, zone_name);
}

SearchResult
DataSourceParkingLot:: findRRsets(const isc::dns::Name& zone_name,
                                  const isc::dns::Name& name,
                                  const isc::dns::RRClass& clas,
                                  const isc::dns::RRType& type) {
    SearchResult result;
    Name authors_name("authors.bind");
    Name version_name("version.bind");
    
    if (clas == RRClass::CH) {
        if (type == RRType::TXT) {
            if (name == authors_name) {
                RRsetPtr rrset = RRsetPtr(new RRset(authors_name, RRClass::CH, RRType::TXT, TTL(3600)));
                rrset->addRdata(Rdata::RdataPtr(TXT("JINMEI Tatuya").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Han Feng").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Kazunori Fujiwara").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Michael Graff").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Evan Hunt").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Jelte Jansen").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Jin Jian").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("JINMEI Tatuya").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Naoki Kambe").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Shane Kerr").copy())); 
                rrset->addRdata(Rdata::RdataPtr(TXT("Zhang Likun").copy()));
                rrset->addRdata(Rdata::RdataPtr(TXT("Jeremy C. Reed").copy())); 

                result.addRRset(rrset);
                result.setStatus(SearchResult::success);
            } else if (name == version_name) {
                RRsetPtr rrset = RRsetPtr(new RRset(version_name, RRClass::CH, RRType::TXT, TTL(3600)));
                rrset->addRdata(Rdata::RdataPtr(TXT("BIND10 0.0.1").copy()));
                result.addRRset(rrset);
                result.setStatus(SearchResult::success);
            } else {
                result.setStatus(SearchResult::name_not_found);
            }
        } else {
            result.setStatus(SearchResult::name_not_found);
        }
    } else if (clas == RRClass::IN) {
        if (zones.contains(name)) {
            RRsetPtr rrset = RRsetPtr(new RRset(name, clas, type, TTL(3600)));
            result.setStatus(SearchResult::success);
            if (type == RRType::A) {
                BOOST_FOREACH(isc::dns::Rdata::RdataPtr a, a_records) {
                    rrset->addRdata(a);
                }
            } else if (type == RRType::AAAA) {
                BOOST_FOREACH(isc::dns::Rdata::RdataPtr aaaa, aaaa_records) {
                    rrset->addRdata(aaaa);
                }
            } else if (type == RRType::NS) {
                BOOST_FOREACH(isc::dns::Rdata::RdataPtr ns, ns_records) {
                    rrset->addRdata(ns);
                }
            } else if (type == RRType::SOA) {
                rrset->addRdata(soa);
            }
            result.addRRset(rrset);
        } else {
            // we don't have the name itself. Do we have the zone?
            if (zones.contains(zone_name)) {
                result.setStatus(SearchResult::name_not_found);
            } else {
                result.setStatus(SearchResult::zone_not_found);
            }
        }
    } else {
        result.setStatus(SearchResult::zone_not_found);
    }
    return result;
}

/// Do direct 'search' in database, no extra processing,
/// and add the resulting rrsets to the specified section
/// in the given message
/// returns the status code of the searchresult
/// Once the dns logic is moved from parkinglot to this class,
/// we should probably make this private
SearchResult::status_type
DataSourceParkingLot::addToMessage(Message& msg,
             section_t section,
             const Name& zone_name,
             const Name& name,
             const isc::dns::RRClass& clas,
             const isc::dns::RRType& type)
{
    SearchResult result = findRRsets(zone_name, name, clas, type);
    BOOST_FOREACH(RRsetPtr rrset, result) {
        msg.addRRset(section, rrset);
    }
    return result.getStatus();
}


}
}
