// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <util/buffer.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_int.h>
#include <dhcp/option6_int_array.h>
#include <dhcp/option6_addrlst.h>
#include "config.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {
class LibDhcpTest : public ::testing::Test {
public:
    LibDhcpTest() {
    }

    /// @brief Generic factory function to create any option.
    ///
    /// Generic factory function to create any option.
    ///
    /// @param u universe (V4 or V6)
    /// @param type option-type
    /// @param buf option-buffer
    static OptionPtr genericOptionFactory(Option::Universe u, uint16_t type,
                                          const OptionBuffer& buf) {
        Option* option = new Option(u, type, buf);
        return OptionPtr(option);
    }

    /// @brief Test option option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param code option code.
    /// @param bug buffer to be used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    static void testInitOptionDefs6(const uint16_t code,
                             const OptionBuffer& buf,
                             const std::type_info& expected_type) {
        // Initialize stdandard options definitions. They are held
        // in the static container throughout the program.
        LibDHCP::initStdOptionDefs(Option::V6);
        // Get all option definitions, we will use them to extract
        // the definition for a particular option code.
        OptionDefContainer options = LibDHCP::getOptionDefs(Option::V6);
        // Get the container index #1. This one allows for searching
        // option definitions using option code.
        const OptionDefContainerTypeIndex& idx = options.get<1>();
        // Get 'all' option definitions for a particular option code.
        // For standard options we expect that the range returned
        // will contain single option as their codes are unique.
        OptionDefContainerTypeRange range = idx.equal_range(code);
        ASSERT_EQ(1, std::distance(range.first, range.second));
        // If we have single option definition returned, the
        // first iterator holds it.
        OptionDefinitionPtr def = *(range.first);
        // It should not happen that option definition is NULL but
        // let's make sure (test should take things like that into
        // account).
        ASSERT_TRUE(def);
        // Check that option definition is valid.
        ASSERT_NO_THROW(def->validate());
        // Get the factory function for the particular option
        // definition. We will use this factory function to
        // create option instance.
        Option::Factory* factory = NULL;
        ASSERT_NO_THROW(factory = def->getFactory());
        OptionPtr option;
        // Create the option.
        ASSERT_NO_THROW(option = factory(Option::V6, code, buf));
        // Make sure it is not NULL.
        ASSERT_TRUE(option);
        // And the actual object type is the one that we expect.
        // Note that for many options there are dedicated classes
        // derived from Option class to represent them.
        EXPECT_TRUE(typeid(*option) == expected_type);
    }
};

static const uint8_t packed[] = {
    0, 12, 0, 5, 100, 101, 102, 103, 104, // opt1 (9 bytes)
    0, 13, 0, 3, 105, 106, 107, // opt2 (7 bytes)
    0, 14, 0, 2, 108, 109, // opt3 (6 bytes)
    1,  0, 0, 4, 110, 111, 112, 113, // opt4 (8 bytes)
    1,  1, 0, 1, 114 // opt5 (5 bytes)
};

TEST(LibDhcpTest, optionFactory) {
    OptionBuffer buf;
    // Factory functions for specific options must be registered before
    // they can be used to create options instances. Otherwise exception
    // is rised.
    EXPECT_THROW(LibDHCP::optionFactory(Option::V4, DHO_SUBNET_MASK, buf),
                 isc::BadValue);

    // Let's register some factory functions (two v4 and one v6 function).
    // Registration may trigger exception if function for the specified
    // option has been registered already.
    ASSERT_NO_THROW(
        LibDHCP::OptionFactoryRegister(Option::V4, DHO_SUBNET_MASK,
                                       &LibDhcpTest::genericOptionFactory);
    );
    ASSERT_NO_THROW(
        LibDHCP::OptionFactoryRegister(Option::V4, DHO_TIME_OFFSET,
                                       &LibDhcpTest::genericOptionFactory);
    );
    ASSERT_NO_THROW(
        LibDHCP::OptionFactoryRegister(Option::V6, D6O_CLIENTID,
                                       &LibDhcpTest::genericOptionFactory);
    );

    // Invoke factory functions for all options (check if registration
    // was successful).
    OptionPtr opt_subnet_mask;
    opt_subnet_mask = LibDHCP::optionFactory(Option::V4,
                                             DHO_SUBNET_MASK,
                                             buf);
    // Check if non-NULL DHO_SUBNET_MASK option pointer has been returned.
    ASSERT_TRUE(opt_subnet_mask);
    // Validate if type and universe is correct.
    EXPECT_EQ(Option::V4, opt_subnet_mask->getUniverse());
    EXPECT_EQ(DHO_SUBNET_MASK, opt_subnet_mask->getType());
    // Expect that option does not have content..
    EXPECT_EQ(0, opt_subnet_mask->len() - opt_subnet_mask->getHeaderLen());

    // Fill the time offset buffer with 4 bytes of data. Each byte set to 1.
    OptionBuffer time_offset_buf(4, 1);
    OptionPtr opt_time_offset;
    opt_time_offset = LibDHCP::optionFactory(Option::V4,
                                             DHO_TIME_OFFSET,
                                             time_offset_buf);
    // Check if non-NULL DHO_TIME_OFFSET option pointer has been returned.
    ASSERT_TRUE(opt_time_offset);
    // Validate if option length, type and universe is correct.
    EXPECT_EQ(Option::V4, opt_time_offset->getUniverse());
    EXPECT_EQ(DHO_TIME_OFFSET, opt_time_offset->getType());
    EXPECT_EQ(time_offset_buf.size(),
              opt_time_offset->len() - opt_time_offset->getHeaderLen());
    // Validate data in the option.
    EXPECT_TRUE(std::equal(time_offset_buf.begin(), time_offset_buf.end(),
                           opt_time_offset->getData().begin()));

    // Fill the client id buffer with 20 bytes of data. Each byte set to 2.
    OptionBuffer clientid_buf(20, 2);
    OptionPtr opt_clientid;
    opt_clientid = LibDHCP::optionFactory(Option::V6,
                                          D6O_CLIENTID,
                                          clientid_buf);
    // Check if non-NULL D6O_CLIENTID option pointer has been returned.
    ASSERT_TRUE(opt_clientid);
    // Validate if option length, type and universe is correct.
    EXPECT_EQ(Option::V6, opt_clientid->getUniverse());
    EXPECT_EQ(D6O_CLIENTID, opt_clientid->getType());
    EXPECT_EQ(clientid_buf.size(), opt_clientid->len() - opt_clientid->getHeaderLen());
    // Validate data in the option.
    EXPECT_TRUE(std::equal(clientid_buf.begin(), clientid_buf.end(),
                           opt_clientid->getData().begin()));
}

TEST(LibDhcpTest, packOptions6) {
    OptionBuffer buf(512);
    isc::dhcp::Option::OptionCollection opts; // list of options

    // generate content for options
    for (int i = 0; i < 64; i++) {
        buf[i]=i+100;
    }

    OptionPtr opt1(new Option(Option::V6, 12, buf.begin() + 0, buf.begin() + 5));
    OptionPtr opt2(new Option(Option::V6, 13, buf.begin() + 5, buf.begin() + 8));
    OptionPtr opt3(new Option(Option::V6, 14, buf.begin() + 8, buf.begin() + 10));
    OptionPtr opt4(new Option(Option::V6,256, buf.begin() + 10,buf.begin() + 14));
    OptionPtr opt5(new Option(Option::V6,257, buf.begin() + 14,buf.begin() + 15));

    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt1));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt2));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt3));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt4));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt5));

    OutputBuffer assembled(512);

    EXPECT_NO_THROW(LibDHCP::packOptions6(assembled, opts));
    EXPECT_EQ(35, assembled.getLength()); // options should take 35 bytes
    EXPECT_EQ(0, memcmp(assembled.getData(), packed, 35) );
}

TEST(LibDhcpTest, unpackOptions6) {

    // just couple of random options
    // Option is used as a simple option implementation
    // More advanced uses are validated in tests dedicated for
    // specific derived classes.
    isc::dhcp::Option::OptionCollection options; // list of options

    OptionBuffer buf(512);
    memcpy(&buf[0], packed, 35);

    EXPECT_NO_THROW ({
        LibDHCP::unpackOptions6(OptionBuffer(buf.begin(), buf.begin()+35), options);
    });

    EXPECT_EQ(options.size(), 5); // there should be 5 options

    isc::dhcp::Option::OptionCollection::const_iterator x = options.find(12);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(12, x->second->getType());  // this should be option 12
    ASSERT_EQ(9, x->second->len()); // it should be of length 9
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+4, 5)); // data len=5

    x = options.find(13);
    ASSERT_FALSE(x == options.end()); // option 13 should exist
    EXPECT_EQ(13, x->second->getType());  // this should be option 13
    ASSERT_EQ(7, x->second->len()); // it should be of length 7
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+13, 3)); // data len=3

    x = options.find(14);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(14, x->second->getType());  // this should be option 14
    ASSERT_EQ(6, x->second->len()); // it should be of length 6
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+20, 2)); // data len=2

    x = options.find(256);
    ASSERT_FALSE(x == options.end()); // option 256 should exist
    EXPECT_EQ(256, x->second->getType());  // this should be option 256
    ASSERT_EQ(8, x->second->len()); // it should be of length 7
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+26, 4)); // data len=4

    x = options.find(257);
    ASSERT_FALSE(x == options.end()); // option 257 should exist
    EXPECT_EQ(257, x->second->getType());  // this should be option 257
    ASSERT_EQ(5, x->second->len()); // it should be of length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+34, 1)); // data len=1

    x = options.find(0);
    EXPECT_TRUE(x == options.end()); // option 0 not found

    x = options.find(1); // 1 is htons(256) on little endians. Worth checking
    EXPECT_TRUE(x == options.end()); // option 1 not found

    x = options.find(2);
    EXPECT_TRUE(x == options.end()); // option 2 not found

    x = options.find(32000);
    EXPECT_TRUE(x == options.end()); // option 32000 not found
}


static uint8_t v4Opts[] = {
    12,  3, 0,   1,  2,
    13,  3, 10, 11, 12,
    14,  3, 20, 21, 22,
    254, 3, 30, 31, 32,
    128, 3, 40, 41, 42
};

TEST(LibDhcpTest, packOptions4) {

    vector<uint8_t> payload[5];
    for (int i = 0; i < 5; i++) {
        payload[i].resize(3);
        payload[i][0] = i*10;
        payload[i][1] = i*10+1;
        payload[i][2] = i*10+2;
    }

    OptionPtr opt1(new Option(Option::V4, 12, payload[0]));
    OptionPtr opt2(new Option(Option::V4, 13, payload[1]));
    OptionPtr opt3(new Option(Option::V4, 14, payload[2]));
    OptionPtr opt4(new Option(Option::V4,254, payload[3]));
    OptionPtr opt5(new Option(Option::V4,128, payload[4]));

    isc::dhcp::Option::OptionCollection opts; // list of options
    opts.insert(make_pair(opt1->getType(), opt1));
    opts.insert(make_pair(opt1->getType(), opt2));
    opts.insert(make_pair(opt1->getType(), opt3));
    opts.insert(make_pair(opt1->getType(), opt4));
    opts.insert(make_pair(opt1->getType(), opt5));

    vector<uint8_t> expVect(v4Opts, v4Opts + sizeof(v4Opts));

    OutputBuffer buf(100);
    EXPECT_NO_THROW(LibDHCP::packOptions(buf, opts));
    ASSERT_EQ(buf.getLength(), sizeof(v4Opts));
    EXPECT_EQ(0, memcmp(v4Opts, buf.getData(), sizeof(v4Opts)));

}

TEST(LibDhcpTest, unpackOptions4) {

    vector<uint8_t> packed(v4Opts, v4Opts + sizeof(v4Opts));
    isc::dhcp::Option::OptionCollection options; // list of options

    ASSERT_NO_THROW(
        LibDHCP::unpackOptions4(packed, options);
    );

    isc::dhcp::Option::OptionCollection::const_iterator x = options.find(12);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(12, x->second->getType());  // this should be option 12
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+2, 3)); // data len=3

    x = options.find(13);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(13, x->second->getType());  // this should be option 13
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+7, 3)); // data len=3

    x = options.find(14);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(14, x->second->getType());  // this should be option 14
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+12, 3)); // data len=3

    x = options.find(254);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(254, x->second->getType());  // this should be option 254
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+17, 3)); // data len=3

    x = options.find(128);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(128, x->second->getType());  // this should be option 254
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+22, 3)); // data len=3

    x = options.find(0);
    EXPECT_TRUE(x == options.end()); // option 0 not found

    x = options.find(1);
    EXPECT_TRUE(x == options.end()); // option 1 not found

    x = options.find(2);
    EXPECT_TRUE(x == options.end()); // option 2 not found
}

// Test that definitions of standard options have been initialized
// correctly.
// @todo Only limited number of option definitions are now created
// This test have to be extended once all option definitions are
// created.
TEST(LibDhcpTest, initStdOptionDefs) {
    LibDhcpTest::testInitOptionDefs6(D6O_CLIENTID, OptionBuffer(14, 1),
                                     typeid(Option));
    LibDhcpTest::testInitOptionDefs6(D6O_SERVERID, OptionBuffer(14, 1),
                                     typeid(Option));
    LibDhcpTest::testInitOptionDefs6(D6O_IA_NA, OptionBuffer(12, 1),
                                     typeid(Option6IA));
    LibDhcpTest::testInitOptionDefs6(D6O_IAADDR, OptionBuffer(24, 1),
                                     typeid(Option6IAAddr));
    LibDhcpTest::testInitOptionDefs6(D6O_ORO, OptionBuffer(10, 1),
                                     typeid(Option6IntArray<uint16_t>));
    LibDhcpTest::testInitOptionDefs6(D6O_ELAPSED_TIME, OptionBuffer(2, 1),
                                     typeid(Option6Int<uint16_t>));
    LibDhcpTest::testInitOptionDefs6(D6O_STATUS_CODE, OptionBuffer(10, 1),
                                     typeid(Option));
    LibDhcpTest::testInitOptionDefs6(D6O_RAPID_COMMIT, OptionBuffer(),
                                     typeid(Option));
    LibDhcpTest::testInitOptionDefs6(D6O_NAME_SERVERS, OptionBuffer(32, 1),
                                     typeid(Option6AddrLst));
}

}
