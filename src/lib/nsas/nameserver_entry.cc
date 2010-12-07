// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>

#include <ctype.h>
#include <strings.h>

#include "config.h"

#include "exceptions/exceptions.h"
#include "name.h"
#include "rrclass.h"
#include "rrttl.h"

#include "address_entry.h"
#include "nameserver_address.h"
#include "nameserver_entry.h"

using namespace asiolink;
using namespace isc::nsas;
using namespace isc::dns;
using namespace std;
using namespace boost;

namespace isc {
namespace nsas {

// Constructor, initialized with the list of addresses associated with this
// nameserver.
NameserverEntry::NameserverEntry(const AbstractRRset* v4Set,
    const AbstractRRset* v6Set, time_t curtime) : expiration_(0)
{
    uint32_t rtt = 1;       // Round-trip time for an address
    string v4name = "";     // Name from the V4 RRset
    string v6name = "";     // Name from the v6 RRset
    uint16_t v4class = 0;   // Class of V4 RRset
    uint16_t v6class = 0;   // Class for V6 RRset

    // Get the time for setting the expiration time.
    if (curtime == 0) {
        curtime = time(NULL);
    }

    // Add the v4 addresses to the list of addresses.  Each address is assigned
    // a small RTT that ensures that each server is used at least once (in a
    // random order).


    // Do the V4 addresses first
    // XXX: Do we need to check that these are V4 addresses?
    if (v4Set) {
        RdataIteratorPtr i = v4Set->getRdataIterator();
        i->first();
        while (! i->isLast()) {
            v4_addresses_.push_back(AddressEntry(IOAddress(i->getCurrent().toText()),
            rtt));
            i->next();
        }

        // Set the expiration time and extract the owner name and class
        expiration_ = curtime + v4Set->getTTL().getValue();
        v4name = v4Set->getName().toText(false);    // Ensure trailing dot
        v4class = v4Set->getClass().getCode();

        // Update the address selector
        updateAddressSelector(v4_addresses_, v4_address_selector_);
    }

    // Now the v6 addresses
    // XXX: Do we need to check that these are V6 addresses?
    if (v6Set) {
        RdataIteratorPtr i = v6Set->getRdataIterator();
        i->first();
        while (! i->isLast()) {
            v6_addresses_.push_back(AddressEntry(IOAddress(i->getCurrent().toText()),
            rtt));
            i->next();
        }

        // Update the expiration time of the data
        time_t v6expiration = curtime + v6Set->getTTL().getValue();
        if (expiration_ == 0) {
            expiration_ = v6expiration;
        }
        else {
            expiration_ = min(expiration_, v6expiration);
        }

        // Extract the name of the v6 set and its class
        v6name = v6Set->getName().toText(false);    // Ensure trailing dot
        v6class = v6Set->getClass().getCode();

        // Update the address selector
        updateAddressSelector(v6_addresses_, v6_address_selector_);
    }

    // TODO: Log a problem if both V4 and V6 address were null.

    if (v4Set && v6Set) {

        // If two owner names were specified and they were different, something
        // has gone wrong with the logic that created this object.
       if (strcasecmp(v4name.c_str(), v6name.c_str()) != 0) {
           isc_throw(InconsistentOwnerNames,
               "Owner names for NameserverEntry RRsets are different");
       }

       // Likewise with the class
       if (v4class != v6class) {
           isc_throw(InconsistentClass,
               "Class codes for NameserverEntry RRsets are different");
       }
    }

    // Otherwise set the owner name
    name_ = v4Set ? v4name : v6name;
    classCode_ = v4Set ? v4class : v6class;
}

// Returns the list of addresses matching the given family
void NameserverEntry::getAddresses(AddressVector& addresses, short family) const {

    // Quick check that allows validation of the assumption in the header file
    // that a family value of 0 will select all address families.
    assert(AF_INET != 0);
    assert(AF_INET6 != 0);
    
    // Now copy all entries that meet the criteria.  Since remove_copy_if
    // does the inverse (copies all entries that do not meet the criteria),
    // the predicate for address selection is negated.
    remove_copy_if(v4_addresses_.begin(), v4_addresses_.end(), back_inserter(addresses),
        bind1st(AddressSelection(), family));
    remove_copy_if(v6_addresses_.begin(), v6_addresses_.end(), back_inserter(addresses),
        bind1st(AddressSelection(), family));
}

// Return one address matching the given family
bool NameserverEntry::getAddress(NameserverAddress& address, short family)
{
    // Get the shared_ptr object that point to "this" object
    shared_ptr<NameserverEntry> shared_ptr_to_this = shared_from_this();

    if(family == AF_INET){
        if(v4_addresses_.size() == 0) return false;

        address = NameserverAddress(shared_ptr_to_this, v4_address_selector_(), AF_INET);
        return true;
    } else if(family == AF_INET6){
        if(v6_addresses_.size() == 0) return false;

        //address = NameserverAddress(shared_from_this(), v6_address_selector_(), AF_INET6);
        return true;
    }
    return false;
}

// Return the address corresponding to the family
asiolink::IOAddress NameserverEntry::getAddressAtIndex(uint32_t index, short family) const
{
    const vector<AddressEntry> *addresses = &v4_addresses_;
    if(family == AF_INET6){
        addresses = &v6_addresses_;
    }
    assert(index < addresses->size());

    return (*addresses)[index].getAddress();
}

// Set the address RTT to a specific value
void NameserverEntry::setAddressRTT(const IOAddress& address, uint32_t rtt) {

    // Search through the list of addresses for a match
    for (AddressVectorIterator i = v4_addresses_.begin(); i != v4_addresses_.end(); ++i) {
        if (i->getAddress().equal(address)) {
            i->setRTT(rtt);

            // Update the selector
            updateAddressSelector(v4_addresses_, v4_address_selector_);
            return;
        }
    }

    // Search the v6 list
    for (AddressVectorIterator i = v6_addresses_.begin(); i != v6_addresses_.end(); ++i) {
        if (i->getAddress().equal(address)) {
            i->setRTT(rtt);

            // Update the selector
            updateAddressSelector(v6_addresses_, v6_address_selector_);
            return;
        }
    }
}

// Update the address's rtt 
#define UPDATE_RTT_ALPHA 0.7
void NameserverEntry::updateAddressRTTAtIndex(uint32_t rtt, uint32_t index, short family) {
    vector<AddressEntry>* addresses = &v4_addresses_;
    if(family == AF_INET6){
        addresses = &v6_addresses_;
    }

    //make sure it is a valid index
    if(index >= addresses->size()) return;

    // Smoothly update the rtt
    // The algorithm is as the same as bind8/bind9:
    //    new_rtt = old_rtt * alpha + new_rtt * (1 - alpha), where alpha is a float number in [0, 1.0]
    // The default value for alpha is 0.7
    uint32_t old_rtt = (*addresses)[index].getRTT();
    uint32_t new_rtt = (int)(old_rtt * UPDATE_RTT_ALPHA + rtt * (1 - UPDATE_RTT_ALPHA));
    (*addresses)[index].setRTT(new_rtt);

    // Update the selector
    if(family == AF_INET) { 
        updateAddressSelector(v4_addresses_, v4_address_selector_);
    } else if(family == AF_INET6) {
        updateAddressSelector(v6_addresses_, v6_address_selector_);
    }
}

// Sets the address to be unreachable
void NameserverEntry::setAddressUnreachable(const IOAddress& address) {
    setAddressRTT(address, AddressEntry::UNREACHABLE);
}

// Update the address selector according to the RTTs
//
// Each address has a probability to be selected if multiple addresses are available
// The weight factor is equal to 1/(rtt*rtt), then all the weight factors are normalized
// to make the sum equal to 1.0
void NameserverEntry::updateAddressSelector(std::vector<AddressEntry>& addresses, 
        WeightedRandomIntegerGenerator& selector)
{
    vector<double> probabilities;
    for(vector<AddressEntry>::iterator it = addresses.begin(); 
            it != addresses.end(); ++it){
        uint32_t rtt = (*it).getRTT();
        if(rtt == 0) isc_throw(RTTIsZero, "The RTT is 0");

        if(rtt == AddressEntry::UNREACHABLE) {
            probabilities.push_back(0);
        } else {
            probabilities.push_back(1.0/(rtt*rtt));
        }
    }
    // Calculate the sum
    double sum = accumulate(probabilities.begin(), probabilities.end(), 0.0);

    // Normalize the probabilities to make the sum equal to 1.0
    for(vector<double>::iterator it = probabilities.begin(); 
            it != probabilities.end(); ++it){
        (*it) /= sum;
    }

    selector.reset(probabilities);
}

} // namespace dns
} // namespace isc
