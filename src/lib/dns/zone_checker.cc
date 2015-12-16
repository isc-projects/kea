// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/zone_checker.h>

#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrset_collection_base.h>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <string>

using boost::lexical_cast;
using std::string;

namespace isc {
namespace dns {

namespace {
std::string
zoneText(const Name& zone_name, const RRClass& zone_class) {
    return (zone_name.toText(true) + "/" + zone_class.toText());
}

void
checkSOA(const Name& zone_name, const RRClass& zone_class,
         const RRsetCollectionBase& zone_rrsets,
         ZoneCheckerCallbacks& callback) {
    ConstRRsetPtr rrset =
        zone_rrsets.find(zone_name, zone_class, RRType::SOA());
    size_t count = 0;
    if (rrset) {
        for (RdataIteratorPtr rit = rrset->getRdataIterator();
             !rit->isLast();
             rit->next(), ++count) {
            if (dynamic_cast<const rdata::generic::SOA*>(&rit->getCurrent()) ==
                NULL) {
                isc_throw(Unexpected, "Zone checker found bad RDATA in SOA");
            }
        }
        if (count == 0) {
            // this should be an implementation bug, not an operational error.
            isc_throw(Unexpected, "Zone checker found an empty SOA RRset");
        }
    }
    if (count != 1) {
        callback.error("zone " + zoneText(zone_name, zone_class) + ": has " +
                       lexical_cast<string>(count) + " SOA records");
    }
}

// Check if a target name is beyond zone cut, either due to delegation or
// DNAME.  Note that DNAME works on the origin but not on the name itself,
// while delegation works on the name itself (but the NS at the origin is not
// delegation).
ConstRRsetPtr
findZoneCut(const Name& zone_name, const RRClass& zone_class,
            const RRsetCollectionBase& zone_rrsets, const Name& target_name) {
    const unsigned int origin_count = zone_name.getLabelCount();
    const unsigned int target_count = target_name.getLabelCount();
    assert(origin_count <= target_count);

    for (unsigned int l = origin_count; l <= target_count; ++l) {
        const Name& mid_name = (l == target_count) ? target_name :
            target_name.split(target_count - l);

        ConstRRsetPtr found;
        if (l != origin_count &&
            (found = zone_rrsets.find(mid_name, zone_class, RRType::NS())) !=
            NULL) {
            return (found);
        }
        if (l != target_count &&
            (found = zone_rrsets.find(mid_name, zone_class, RRType::DNAME()))
            != NULL) {
            return (found);
        }
    }
    return (ConstRRsetPtr());
}

// Check if each "in-zone" NS name has an address record, identifying some
// error cases.
void
checkNSNames(const Name& zone_name, const RRClass& zone_class,
             const RRsetCollectionBase& zone_rrsets,
             ConstRRsetPtr ns_rrset, ZoneCheckerCallbacks& callbacks) {
    if (ns_rrset->getRdataCount() == 0) {
        // this should be an implementation bug, not an operational error.
        isc_throw(Unexpected, "Zone checker found an empty NS RRset");
    }

    for (RdataIteratorPtr rit = ns_rrset->getRdataIterator();
         !rit->isLast();
         rit->next()) {
        const rdata::generic::NS* ns_data =
            dynamic_cast<const rdata::generic::NS*>(&rit->getCurrent());
        if (ns_data == NULL) {
            isc_throw(Unexpected, "Zone checker found bad RDATA in NS");
        }
        const Name& ns_name = ns_data->getNSName();
        const NameComparisonResult::NameRelation reln =
            ns_name.compare(zone_name).getRelation();
        if (reln != NameComparisonResult::EQUAL &&
            reln != NameComparisonResult::SUBDOMAIN) {
            continue;           // not in the zone.  we can ignore it.
        }

        // Check if there's a zone cut between the origin and the NS name.
        ConstRRsetPtr cut_rrset = findZoneCut(zone_name, zone_class,
                                              zone_rrsets, ns_name);
        if (cut_rrset) {
            if  (cut_rrset->getType() == RRType::NS()) {
                continue; // delegation; making the NS name "out of zone".
            } else if (cut_rrset->getType() == RRType::DNAME()) {
                callbacks.error("zone " + zoneText(zone_name, zone_class) +
                                ": NS '" + ns_name.toText(true) + "' is " +
                                "below a DNAME '" +
                                cut_rrset->getName().toText(true) +
                                "' (illegal per RFC6672)");
                continue;
            } else {
                assert(false);
            }
        }
        if (zone_rrsets.find(ns_name, zone_class, RRType::CNAME()) != NULL) {
            callbacks.error("zone " + zoneText(zone_name, zone_class) +
                            ": NS '" + ns_name.toText(true) + "' is a CNAME " +
                            "(illegal per RFC2181)");
            continue;
        }
        if (zone_rrsets.find(ns_name, zone_class, RRType::A()) == NULL &&
            zone_rrsets.find(ns_name, zone_class, RRType::AAAA()) == NULL) {
            callbacks.warn("zone " + zoneText(zone_name, zone_class) +
                           ": NS has no address records (A or AAAA)");
        }
    }
}

void
checkNS(const Name& zone_name, const RRClass& zone_class,
        const RRsetCollectionBase& zone_rrsets,
        ZoneCheckerCallbacks& callbacks) {
    ConstRRsetPtr rrset =
        zone_rrsets.find(zone_name, zone_class, RRType::NS());
    if (rrset == NULL) {
        callbacks.error("zone " + zoneText(zone_name, zone_class) +
                        ": has no NS records");
        return;
    }
    checkNSNames(zone_name, zone_class, zone_rrsets, rrset, callbacks);
}

// The following is a simple wrapper of checker callback so checkZone()
// can also remember any critical errors.
void
errorWrapper(const string& reason, const ZoneCheckerCallbacks* callbacks,
             bool* had_error) {
    *had_error = true;
    callbacks->error(reason);
}
}

bool
checkZone(const Name& zone_name, const RRClass& zone_class,
          const RRsetCollectionBase& zone_rrsets,
          const ZoneCheckerCallbacks& callbacks) {
    bool had_error = false;
    ZoneCheckerCallbacks my_callbacks(
        boost::bind(errorWrapper, _1, &callbacks, &had_error),
        boost::bind(&ZoneCheckerCallbacks::warn, &callbacks, _1));

    checkSOA(zone_name, zone_class, zone_rrsets, my_callbacks);
    checkNS(zone_name, zone_class, zone_rrsets, my_callbacks);

    return (!had_error);
}

} // end namespace dns
} // end namespace isc
