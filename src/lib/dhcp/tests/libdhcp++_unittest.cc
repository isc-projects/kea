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

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_int.h>
#include <dhcp/option6_int_array.h>
#include <dhcp/option_custom.h>
#include <util/buffer.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {
class LibDhcpTest : public ::testing::Test {
public:
    LibDhcpTest() { }

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

    /// @brief Test DHCPv4 option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param code option code.
    /// @param bug buffer to be used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    static void testStdOptionDefs4(const uint16_t code,
                                   const OptionBuffer& buf,
                                   const std::type_info& expected_type) {
        // Use V4 universe.
        testStdOptionDefs(Option::V4, code, buf, expected_type);
    }

    /// @brief Test DHCPv6 option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param code option code.
    /// @param bug buffer to be used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    static void testStdOptionDefs6(const uint16_t code,
                                   const OptionBuffer& buf,
                                   const std::type_info& expected_type) {
        // Use V6 universe.
        testStdOptionDefs(Option::V6, code, buf, expected_type);
    }
private:

    /// @brief Test DHCPv4 or DHCPv6 option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param code option code.
    /// @param bug buffer to be used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    static void testStdOptionDefs(const Option::Universe u,
                                  const uint16_t code,
                                  const OptionBuffer& buf,
                                  const std::type_info& expected_type) {
        // Get all option definitions, we will use them to extract
        // the definition for a particular option code.
        // We don't have to initialize option definitions here because they
        // are initialized in the class's constructor.
        OptionDefContainer options = LibDHCP::getOptionDefs(u);
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
        OptionPtr option;
        // Create the option.
        ASSERT_NO_THROW(option = def->optionFactory(u, code, buf))
            << "Option creation failed to option code " << code;
        // Make sure it is not NULL.
        ASSERT_TRUE(option);
        // And the actual object type is the one that we expect.
        // Note that for many options there are dedicated classes
        // derived from Option class to represent them.
        EXPECT_TRUE(typeid(*option) == expected_type)
            << "Invalid class returned for option code " << code;
    }
};

static const uint8_t packed[] = {
    0, 1, 0, 5, 100, 101, 102, 103, 104, // CLIENT_ID (9 bytes)
    0, 2, 0, 3, 105, 106, 107, // SERVER_ID (7 bytes)
    0, 14, 0, 0, // RAPID_COMMIT (0 bytes)
    0,  6, 0, 4, 108, 109, 110, 111, // ORO (8 bytes)
    0,  8, 0, 2, 112, 113 // ELAPSED_TIME (6 bytes)
};

TEST_F(LibDhcpTest, optionFactory) {
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

TEST_F(LibDhcpTest, packOptions6) {
    OptionBuffer buf(512);
    isc::dhcp::Option::OptionCollection opts; // list of options

    // generate content for options
    for (int i = 0; i < 64; i++) {
        buf[i]=i+100;
    }

    OptionPtr opt1(new Option(Option::V6, 1, buf.begin() + 0, buf.begin() + 5));
    OptionPtr opt2(new Option(Option::V6, 2, buf.begin() + 5, buf.begin() + 8));
    OptionPtr opt3(new Option(Option::V6, 14, buf.begin() + 8, buf.begin() + 8));
    OptionPtr opt4(new Option(Option::V6, 6, buf.begin() + 8, buf.begin() + 12));
    OptionPtr opt5(new Option(Option::V6, 8, buf.begin() + 12, buf.begin() + 14));

    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt1));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt2));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt3));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt4));
    opts.insert(pair<int, OptionPtr >(opt1->getType(), opt5));

    OutputBuffer assembled(512);

    EXPECT_NO_THROW(LibDHCP::packOptions6(assembled, opts));
    EXPECT_EQ(sizeof(packed), assembled.getLength());
    EXPECT_EQ(0, memcmp(assembled.getData(), packed, sizeof(packed)));
}

TEST_F(LibDhcpTest, unpackOptions6) {

    // just couple of random options
    // Option is used as a simple option implementation
    // More advanced uses are validated in tests dedicated for
    // specific derived classes.
    isc::dhcp::Option::OptionCollection options; // list of options

    OptionBuffer buf(512);
    memcpy(&buf[0], packed, sizeof(packed));

    EXPECT_NO_THROW ({
            LibDHCP::unpackOptions6(OptionBuffer(buf.begin(), buf.begin() + sizeof(packed)),
                                    options);
    });

    EXPECT_EQ(options.size(), 5); // there should be 5 options

    isc::dhcp::Option::OptionCollection::const_iterator x = options.find(1);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(1, x->second->getType());  // this should be option 1
    ASSERT_EQ(9, x->second->len()); // it should be of length 9
    ASSERT_EQ(5, x->second->getData().size());
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed + 4, 5)); // data len=5

        x = options.find(2);
    ASSERT_FALSE(x == options.end()); // option 2 should exist
    EXPECT_EQ(2, x->second->getType());  // this should be option 2
    ASSERT_EQ(7, x->second->len()); // it should be of length 7
    ASSERT_EQ(3, x->second->getData().size());
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed + 13, 3)); // data len=3

    x = options.find(14);
    ASSERT_FALSE(x == options.end()); // option 14 should exist
    EXPECT_EQ(14, x->second->getType());  // this should be option 14
    ASSERT_EQ(4, x->second->len()); // it should be of length 4
    EXPECT_EQ(0, x->second->getData().size()); // data len = 0

    x = options.find(6);
    ASSERT_FALSE(x == options.end()); // option 6 should exist
    EXPECT_EQ(6, x->second->getType());  // this should be option 6
    ASSERT_EQ(8, x->second->len()); // it should be of length 8
    // Option with code 6 is the OPTION_ORO. This option is
    // represented by the Option6IntArray<uint16_t> class which
    // comprises the set of uint16_t values. We need to cast the
    // returned pointer to this type to get values stored in it.
    boost::shared_ptr<Option6IntArray<uint16_t> > opt_oro =
        boost::dynamic_pointer_cast<Option6IntArray<uint16_t> >(x->second);
    // This value will be NULL if cast was unsuccessful. This is the case
    // when returned option has different type than expected.
    ASSERT_TRUE(opt_oro);
    // Get set of uint16_t values.
    std::vector<uint16_t> opts = opt_oro->getValues();
    // Prepare the refrence data.
    std::vector<uint16_t> expected_opts;
    expected_opts.push_back(0x6C6D); // equivalent to: 108, 109
    expected_opts.push_back(0x6E6F); // equivalent to 110, 111
    ASSERT_EQ(expected_opts.size(), opts.size());
    // Validated if option has been unpacked correctly.
    EXPECT_TRUE(std::equal(expected_opts.begin(), expected_opts.end(),
                           opts.begin()));

    x = options.find(8);
    ASSERT_FALSE(x == options.end()); // option 8 should exist
    EXPECT_EQ(8, x->second->getType());  // this should be option 8
    ASSERT_EQ(6, x->second->len()); // it should be of length 9
    // Option with code 8 is OPTION_ELAPSED_TIME. This option is
    // represented by Option6Int<uint16_t> value that holds single
    // uint16_t value.
    boost::shared_ptr<Option6Int<uint16_t> > opt_elapsed_time =
        boost::dynamic_pointer_cast<Option6Int<uint16_t> >(x->second);
    // This value will be NULL if cast was unsuccessful. This is the case
    // when returned option has different type than expected.
    ASSERT_TRUE(opt_elapsed_time);
    // Returned value should be equivalent to two byte values: 112, 113
    EXPECT_EQ(0x7071, opt_elapsed_time->getValue());

    x = options.find(0);
    EXPECT_TRUE(x == options.end()); // option 0 not found

    x = options.find(256); // 256 is htons(1) on little endians. Worth checking
    EXPECT_TRUE(x == options.end()); // option 1 not found

    x = options.find(7);
    EXPECT_TRUE(x == options.end()); // option 2 not found

    x = options.find(32000);
    EXPECT_TRUE(x == options.end()); // option 32000 not found */
}


static uint8_t v4Opts[] = {
    12,  3, 0,   1,  2,
    13,  3, 10, 11, 12,
    14,  3, 20, 21, 22,
    254, 3, 30, 31, 32,
    128, 3, 40, 41, 42
};

TEST_F(LibDhcpTest, packOptions4) {

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

TEST_F(LibDhcpTest, unpackOptions4) {

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

TEST_F(LibDhcpTest, stdOptionDefs4) {

    // Create a buffer that holds dummy option data.
    // It will be used to create most of the options.
    std::vector<uint8_t> buf(48, 1);

    LibDhcpTest::testStdOptionDefs4(DHO_SUBNET_MASK, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_TIME_OFFSET, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_ROUTERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_TIME_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NAME_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_NAME_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_LOG_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_COOKIE_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_LPR_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_IMPRESS_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_RESOURCE_LOCATION_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_HOST_NAME, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_BOOT_SIZE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_MERIT_DUMP, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_NAME, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_SWAP_SERVER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_ROOT_PATH, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_EXTENSIONS_PATH, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_IP_FORWARDING, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NON_LOCAL_SOURCE_ROUTING, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_POLICY_FILTER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_MAX_DGRAM_REASSEMBLY, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_MAX_DGRAM_REASSEMBLY, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DEFAULT_IP_TTL, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_PATH_MTU_AGING_TIMEOUT, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_PATH_MTU_PLATEAU_TABLE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_INTERFACE_MTU, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_ALL_SUBNETS_LOCAL, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_BROADCAST_ADDRESS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_PERFORM_MASK_DISCOVERY, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_MASK_SUPPLIER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_ROUTER_DISCOVERY, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_ROUTER_SOLICITATION_ADDRESS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_STATIC_ROUTES, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_TRAILER_ENCAPSULATION, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_ARP_CACHE_TIMEOUT, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_IEEE802_3_ENCAPSULATION, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DEFAULT_TCP_TTL, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_TCP_KEEPALIVE_INTERVAL, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_TCP_KEEPALIVE_GARBAGE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NIS_DOMAIN, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NIS_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NTP_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_VENDOR_ENCAPSULATED_OPTIONS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_NAME_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_DD_SERVER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_NODE_TYPE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_SCOPE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_FONT_SERVERS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_X_DISPLAY_MANAGER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_REQUESTED_ADDRESS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_LEASE_TIME, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_OPTION_OVERLOAD, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_MESSAGE_TYPE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_SERVER_IDENTIFIER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_PARAMETER_REQUEST_LIST, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_MESSAGE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_MAX_MESSAGE_SIZE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_RENEWAL_TIME, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_REBINDING_TIME, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_VENDOR_CLASS_IDENTIFIER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_CLIENT_IDENTIFIER, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NWIP_DOMAIN_NAME, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_NWIP_SUBOPTIONS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_USER_CLASS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_FQDN, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_AGENT_OPTIONS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_AUTHENTICATE, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_CLIENT_LAST_TRANSACTION_TIME, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_ASSOCIATED_IP, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_SUBNET_SELECTION, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_SEARCH, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_VIVCO_SUBOPTIONS, buf,
                                    typeid(OptionCustom));
    LibDhcpTest::testStdOptionDefs4(DHO_VIVSO_SUBOPTIONS, buf,
                                    typeid(OptionCustom));


}

// Test that definitions of standard options have been initialized
// correctly.
// @todo Only limited number of option definitions are now created
// This test have to be extended once all option definitions are
// created.
TEST_F(LibDhcpTest, stdOptionDefs6) {

    // Create a buffer that holds dummy option data.
    // It will be used to create most of the options.
    std::vector<uint8_t> buf(48, 1);

    // Prepare buffer holding an array of FQDNs.
    const char data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0
    };
    // Initialize a vector with the FQDN data.
    std::vector<uint8_t> fqdn_buf(data, data + sizeof(data));

    // The CLIENT_FQDN holds a uint8_t value and FQDN. We have
    // to add the uint8_t value to it and then append the buffer
    // holding some valid FQDN.
    std::vector<uint8_t> client_fqdn_buf(1);
    client_fqdn_buf.insert(client_fqdn_buf.end(), fqdn_buf.begin(),
                           fqdn_buf.end());

    // The actual test starts here for all supported option codes.
    LibDhcpTest::testStdOptionDefs6(D6O_CLIENTID, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_SERVERID, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_IA_NA, buf, typeid(Option6IA));

    LibDhcpTest::testStdOptionDefs6(D6O_IA_TA, buf,
                                    typeid(Option6Int<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_IAADDR, buf, typeid(Option6IAAddr));

    LibDhcpTest::testStdOptionDefs6(D6O_ORO, buf,
                                    typeid(Option6IntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_PREFERENCE, buf,
                                    typeid(Option6Int<uint8_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_ELAPSED_TIME, buf,
                                    typeid(Option6Int<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_RELAY_MSG, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_STATUS_CODE, buf, typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_RAPID_COMMIT, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_USER_CLASS, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_VENDOR_CLASS, buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_VENDOR_OPTS, buf, typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_INTERFACE_ID, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_RECONF_MSG, buf,
                                    typeid(Option6Int<uint8_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_RECONF_ACCEPT, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_SIP_SERVERS_DNS, fqdn_buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SIP_SERVERS_ADDR, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NAME_SERVERS, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_DOMAIN_SEARCH, fqdn_buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_IA_PD, buf, typeid(Option6IA));

    LibDhcpTest::testStdOptionDefs6(D6O_IAPREFIX, buf, typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_NIS_SERVERS, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NISP_SERVERS, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NIS_DOMAIN_NAME, fqdn_buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_NISP_DOMAIN_NAME, fqdn_buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SNTP_SERVERS, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_INFORMATION_REFRESH_TIME,
                                    buf, typeid(Option6Int<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_BCMCS_SERVER_D, fqdn_buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_BCMCS_SERVER_A, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_GEOCONF_CIVIC, buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_REMOTE_ID, buf, typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SUBSCRIBER_ID, buf,typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_CLIENT_FQDN, client_fqdn_buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_PANA_AGENT, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_PANA_AGENT, buf,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NEW_POSIX_TIMEZONE, buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_NEW_TZDB_TIMEZONE, buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_ERO, buf,
                                    typeid(Option6IntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_QUERY, buf, typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_CLIENT_DATA, buf, typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_CLT_TIME, buf,
                                    typeid(Option6Int<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_RELAY_DATA, buf,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_CLIENT_LINK, buf,
                                    typeid(Option6AddrLst));
}

}
