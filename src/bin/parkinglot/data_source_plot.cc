
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

isc::dns::DataSource::result
DataSourceParkingLot:: findRRset(isc::dns::RRsetPtr& target, isc::dns::Name name,
                                isc::dns::RRClass clas, isc::dns::RRType type) {
    Name authors_name("authors.bind");
    Name version_name("version.bind");

    std::cout << "findRRset()" << std::endl;
    if (clas == RRClass::CH) {
        if (type == RRType::TXT) {
            if (name == authors_name) {
                target->addRdata(Rdata::RdataPtr(TXT("JINMEI Tatuya").copy()));
            } else if (name == version_name) {
                target->addRdata(Rdata::RdataPtr(TXT("BIND10 0.0.1").copy()));
            } else {
                std::cout << "ch txt but unknown name" << std::endl;
                return DataSource::name_not_found;
            }
            return DataSource::success;
        } else {
            std::cout << "ch but not txt" << std::endl;
            return DataSource::name_not_found;
        }
    } else if (clas == RRClass::IN) {
        // make zoneset contain Name instead of string?
        std::cout << "Finding zone for " << name.toText() << std::endl;
        if (zones.contains(name.toText(true))) {
            if (type == RRType::A) {
                BOOST_FOREACH(isc::dns::Rdata::RdataPtr a, a_records) {
                    target->addRdata(a);
                }
            } else if (type == RRType::AAAA) {
                BOOST_FOREACH(isc::dns::Rdata::RdataPtr aaaa, aaaa_records) {
                    target->addRdata(aaaa);
                }
            } else if (type == RRType::NS) {
                BOOST_FOREACH(isc::dns::Rdata::RdataPtr ns, ns_records) {
                    target->addRdata(ns);
                }
            } else if (type == RRType::SOA) {
                target->addRdata(soa);
            } else {
                std::cout << "type not supported" << std::endl;
                return name_not_found;
            }
            std::cout << "rrset: " << target->toText() << std::endl;
            
            std::cout << "success" << std::endl;
            return success;
        } else {
            std::cout << "zone not in zoneset" << std::endl;
            return DataSource::zone_not_found;
        }
    } else {
        std::cout << "not ch or in" << std::endl;
        return DataSource::zone_not_found;
    }
    // no match at all, error?
    return DataSource::error;
}

}
}
