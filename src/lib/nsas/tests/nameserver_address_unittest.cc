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

#include <config.h>

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include "../nameserver_address.h"
#include "../nameserver_entry.h"
#include "nsas_test.h"

namespace isc {
namespace nsas {

using namespace dns;
using namespace rdata;

#define TEST_ADDRESS_INDEX 1

/// \brief NameserverEntry sample class for testing
class NameserverEntrySample {
public:
    NameserverEntrySample():
        name_("example.org"),
        rrv4_(new RRset(name_, RRClass::IN(), RRType::A(), RRTTL(1200))),
        ns_(new NameserverEntry(name_.toText(), RRClass::IN())),
        resolver_(new TestResolver())
    {
        // Add some sample A records
        rrv4_->addRdata(ConstRdataPtr(new RdataTest<A>("1.2.3.4")));
        rrv4_->addRdata(ConstRdataPtr(new RdataTest<A>("5.6.7.8")));
        rrv4_->addRdata(ConstRdataPtr(new RdataTest<A>("9.10.11.12")));

        ns_.reset(new NameserverEntry(name_.toText(), RRClass::IN()));
        ns_->askIP(resolver_.get(), boost::shared_ptr<Callback>(new Callback), ANY_OK);
        resolver_->asksIPs(name_, 0, 1);
        resolver_->requests[0].second->success(
            isc::util::unittests::createResponseMessage(rrv4_));
    }

    // Return the sample NameserverEntry
    boost::shared_ptr<NameserverEntry>& getNameserverEntry() { return ns_; }

    // Return the IOAddress corresponding to the index in rrv4_
    isc::asiolink::IOAddress getAddressAtIndex(uint32_t index) {
        return ns_.get()->getAddressAtIndex(index, V4_ONLY);
    }

    // Return the addresses count stored in RRset
    unsigned int getAddressesCount() const { return rrv4_->getRdataCount(); }

    // Return the RTT of the address
    uint32_t getAddressRTTAtIndex(uint32_t index) { 
        NameserverEntry::AddressVector addresses;
        ns_.get()->getAddresses(addresses);
        return (addresses[index].getAddressEntry().getRTT());
    }

private:
    Name name_;                             ///< Name of the sample
    RRsetPtr rrv4_;           ///< Standard RRSet - IN, A, lowercase name
    boost::shared_ptr<NameserverEntry> ns_; ///< Shared_ptr that points to a NameserverEntry object
    boost::shared_ptr<TestResolver> resolver_;

    class Callback : public NameserverEntry::Callback {
        public:
            virtual void operator()(boost::shared_ptr<NameserverEntry>) { }
    };
};

/// \brief Test Fixture Class
class NameserverAddressTest : public ::testing::Test {
protected:
    // Constructor
    NameserverAddressTest(): 
        ns_address_(ns_sample_.getNameserverEntry(),
            ns_sample_.getNameserverEntry()->getAddressAtIndex(
            TEST_ADDRESS_INDEX, V4_ONLY), V4_ONLY)
    {
    }

    NameserverEntrySample ns_sample_;
    // Valid NameserverAddress object
    NameserverAddress ns_address_;
};

// Test that the address is equal to the address in NameserverEntry
TEST_F(NameserverAddressTest, Address) {
    EXPECT_TRUE(ns_address_.getAddress().equals( ns_sample_.getAddressAtIndex(TEST_ADDRESS_INDEX)));

    boost::shared_ptr<NameserverEntry> empty_ne((NameserverEntry*)NULL);
    // It will throw an NullNameserverEntryPointer exception with the empty NameserverEntry shared pointer
    ASSERT_THROW({NameserverAddress empty_ns_address(empty_ne,
        isc::asiolink::IOAddress("127.0.0.1"), V4_ONLY);},
        NullNameserverEntryPointer);
}

// Test that the RTT is updated
TEST_F(NameserverAddressTest, UpdateRTT) {
    uint32_t old_rtt = ns_sample_.getAddressRTTAtIndex(TEST_ADDRESS_INDEX);
    uint32_t new_rtt = old_rtt + 10;

    uint32_t old_rtt0 = ns_sample_.getAddressRTTAtIndex(0);
    uint32_t old_rtt2 = ns_sample_.getAddressRTTAtIndex(2);

    for(int i = 0; i < 10000; ++i){
        ns_address_.updateRTT(new_rtt);
    }

    //The RTT should have been updated
    EXPECT_NE(new_rtt, ns_sample_.getAddressRTTAtIndex(TEST_ADDRESS_INDEX));

    //The RTTs not been updated should remain unchanged
    EXPECT_EQ(old_rtt0, ns_sample_.getAddressRTTAtIndex(0));
    EXPECT_EQ(old_rtt2, ns_sample_.getAddressRTTAtIndex(2));
}

} // namespace nsas
} // namespace isc
