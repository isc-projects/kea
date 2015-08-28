// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <util/buffer.h>
#include <util/encode/hex.h>

#include <boost/pointer_cast.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

// DHCPv6 suboptions of Vendor Options Option.
/// @todo move to src/lib/dhcp/docsis3_option_defs.h once #3194 is merged.
const uint16_t OPTION_CMTS_CAPS = 1025;
const uint16_t OPTION_CM_MAC = 1026;

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
        return (OptionPtr(new Option(u, type, buf)));
    }

    /// @brief Test DHCPv4 option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param code option code.
    /// @param begin iterator pointing at beginning of a buffer to
    /// be used to create option instance.
    /// @param end iterator pointing at end of a buffer to be
    /// used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    /// @param encapsulates name of the option space being encapsulated
    /// by the option.
    static void testStdOptionDefs4(const uint16_t code,
                                   const OptionBufferConstIter begin,
                                   const OptionBufferConstIter end,
                                   const std::type_info& expected_type,
                                   const std::string& encapsulates = "") {
        // Use V4 universe.
        testStdOptionDefs(Option::V4, code, begin, end, expected_type,
                          encapsulates);
    }

    /// @brief Test DHCPv6 option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param code option code.
    /// @param begin iterator pointing at beginning of a buffer to
    /// be used to create option instance.
    /// @param end iterator pointing at end of a buffer to be
    /// used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    /// @param encapsulates name of the option space being encapsulated
    /// by the option.
    static void testStdOptionDefs6(const uint16_t code,
                                   const OptionBufferConstIter begin,
                                   const OptionBufferConstIter end,
                                   const std::type_info& expected_type,
                                   const std::string& encapsulates = "") {
        // Use V6 universe.
        testStdOptionDefs(Option::V6, code, begin, end, expected_type,
                          encapsulates);
    }

    /// @brief Create a sample DHCPv4 option 43 with suboptions.
    static OptionBuffer createVendorOption() {
        const uint8_t opt_data[] = {
            0x2B, 0x0D,  // Vendor-Specific Information (CableLabs)
            // Suboptions start here...
            0x02, 0x05,  // Device Type Option (length = 5)
            'D', 'u', 'm', 'm', 'y',
            0x04, 0x04,   // Serial Number Option (length = 4)
            0x42, 0x52, 0x32, 0x32 // Serial number
        };
        return (OptionBuffer(opt_data, opt_data + sizeof(opt_data)));
    }

    /// @brief Create a sample DHCPv4 option 82 with suboptions.
    static OptionBuffer createAgentInformationOption() {
        const uint8_t opt_data[] = {
            0x52, 0x0E, // Agent Information Option (length = 14)
            // Suboptions start here...
            0x01, 0x04, // Agent Circuit ID (length = 4)
            0x20, 0x00, 0x00, 0x02, // ID
            0x02, 0x06, // Agent Remote ID
            0x20, 0xE5, 0x2A, 0xB8, 0x15, 0x14 // ID
        };
        return (OptionBuffer(opt_data, opt_data + sizeof(opt_data)));
    }

private:

    /// @brief Test DHCPv4 or DHCPv6 option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param code option code.
    /// @param begin iterator pointing at beginning of a buffer to
    /// be used to create option instance.
    /// @param end iterator pointing at end of a buffer to be
    /// used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    /// @param encapsulates name of the option space being encapsulated
    /// by the option.
    static void testStdOptionDefs(const Option::Universe u,
                                  const uint16_t code,
                                  const OptionBufferConstIter begin,
                                  const OptionBufferConstIter end,
                                  const std::type_info& expected_type,
                                  const std::string& encapsulates) {
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
        ASSERT_EQ(1, std::distance(range.first, range.second))
            << "Standard option definition for the code " << code
            << " has not been found.";
        // If we have single option definition returned, the
        // first iterator holds it.
        OptionDefinitionPtr def = *(range.first);
        // It should not happen that option definition is NULL but
        // let's make sure (test should take things like that into
        // account).
        ASSERT_TRUE(def) << "Option definition for the code "
                         << code << " is NULL.";
        // Check that option definition is valid.
        ASSERT_NO_THROW(def->validate())
            << "Option definition for the option code " << code
            << " is invalid";
        // Check that the valid encapsulated option space name
        // has been specified.
        EXPECT_EQ(encapsulates, def->getEncapsulatedSpace());
        OptionPtr option;
        // Create the option.
        ASSERT_NO_THROW(option = def->optionFactory(u, code, begin, end))
            << "Option creation failed for option code " << code;
        // Make sure it is not NULL.
        ASSERT_TRUE(option);
        // And the actual object type is the one that we expect.
        // Note that for many options there are dedicated classes
        // derived from Option class to represent them.
        EXPECT_TRUE(typeid(*option) == expected_type)
            << "Invalid class returned for option code " << code;
    }
};

// The DHCPv6 options in the wire format, used by multiple tests.
const uint8_t v6packed[] = {
    0, 1, 0, 5, 100, 101, 102, 103, 104, // CLIENT_ID (9 bytes)
    0, 2, 0, 3, 105, 106, 107, // SERVER_ID (7 bytes)
    0, 14, 0, 0, // RAPID_COMMIT (0 bytes)
    0,  6, 0, 4, 108, 109, 110, 111, // ORO (8 bytes)
    0,  8, 0, 2, 112, 113, // ELAPSED_TIME (6 bytes)
    // Vendor Specific Information Option starts here
    0x00, 0x11,  // VSI Option Code
    0x00, 0x16,  // VSI Option Length
    0x00, 0x00, 0x11, 0x8B, // Enterprise ID
    0x04, 0x01,  // CMTS Capabilities Option
    0x00, 0x04,  // Length
    0x01, 0x02,
    0x03, 0x00,  // DOCSIS Version Number
    0x04, 0x02,  // CM MAC Address Suboption
    0x00, 0x06,  // Length
    0x74, 0x56, 0x12, 0x29, 0x97, 0xD0, // Actual MAC Address

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
    isc::dhcp::OptionCollection opts; // list of options

    // generate content for options
    for (unsigned i = 0; i < 64; i++) {
        buf[i]=i+100;
    }

    OptionPtr opt1(new Option(Option::V6, 1, buf.begin() + 0, buf.begin() + 5));
    OptionPtr opt2(new Option(Option::V6, 2, buf.begin() + 5, buf.begin() + 8));
    OptionPtr opt3(new Option(Option::V6, 14, buf.begin() + 8, buf.begin() + 8));
    OptionPtr opt4(new Option(Option::V6, 6, buf.begin() + 8, buf.begin() + 12));
    OptionPtr opt5(new Option(Option::V6, 8, buf.begin() + 12, buf.begin() + 14));

    OptionPtr cm_mac(new Option(Option::V6, OPTION_CM_MAC,
                                OptionBuffer(v6packed + 54, v6packed  + 60)));

    OptionPtr cmts_caps(new Option(Option::V6, OPTION_CMTS_CAPS,
                                   OptionBuffer(v6packed + 46, v6packed + 50)));

    boost::shared_ptr<OptionInt<uint32_t> >
        vsi(new OptionInt<uint32_t>(Option::V6, D6O_VENDOR_OPTS, 4491));
    vsi->addOption(cm_mac);
    vsi->addOption(cmts_caps);

    opts.insert(make_pair(opt1->getType(), opt1));
    opts.insert(make_pair(opt1->getType(), opt2));
    opts.insert(make_pair(opt1->getType(), opt3));
    opts.insert(make_pair(opt1->getType(), opt4));
    opts.insert(make_pair(opt1->getType(), opt5));
    opts.insert(make_pair(opt1->getType(), vsi));

    OutputBuffer assembled(512);

    EXPECT_NO_THROW(LibDHCP::packOptions(assembled, opts));
    EXPECT_EQ(sizeof(v6packed), assembled.getLength());
    EXPECT_EQ(0, memcmp(assembled.getData(), v6packed, sizeof(v6packed)));
}

TEST_F(LibDhcpTest, unpackOptions6) {

    // just couple of random options
    // Option is used as a simple option implementation
    // More advanced uses are validated in tests dedicated for
    // specific derived classes.
    isc::dhcp::OptionCollection options; // list of options

    OptionBuffer buf(512);
    memcpy(&buf[0], v6packed, sizeof(v6packed));

    EXPECT_NO_THROW ({
            LibDHCP::unpackOptions6(OptionBuffer(buf.begin(), buf.begin() + sizeof(v6packed)),
                                    "dhcp6", options);
    });

    EXPECT_EQ(options.size(), 6); // there should be 5 options

    isc::dhcp::OptionCollection::const_iterator x = options.find(1);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(1, x->second->getType());  // this should be option 1
    ASSERT_EQ(9, x->second->len()); // it should be of length 9
    ASSERT_EQ(5, x->second->getData().size());
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v6packed + 4, 5)); // data len=5

        x = options.find(2);
    ASSERT_FALSE(x == options.end()); // option 2 should exist
    EXPECT_EQ(2, x->second->getType());  // this should be option 2
    ASSERT_EQ(7, x->second->len()); // it should be of length 7
    ASSERT_EQ(3, x->second->getData().size());
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v6packed + 13, 3)); // data len=3

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
    // represented by the OptionIntArray<uint16_t> class which
    // comprises the set of uint16_t values. We need to cast the
    // returned pointer to this type to get values stored in it.
    boost::shared_ptr<OptionIntArray<uint16_t> > opt_oro =
        boost::dynamic_pointer_cast<OptionIntArray<uint16_t> >(x->second);
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
    boost::shared_ptr<OptionInt<uint16_t> > opt_elapsed_time =
        boost::dynamic_pointer_cast<OptionInt<uint16_t> >(x->second);
    // This value will be NULL if cast was unsuccessful. This is the case
    // when returned option has different type than expected.
    ASSERT_TRUE(opt_elapsed_time);
    // Returned value should be equivalent to two byte values: 112, 113
    EXPECT_EQ(0x7071, opt_elapsed_time->getValue());

    // Check if Vendor Specific Information Option along with suboptions
    // have been parsed correctly.
    x = options.find(D6O_VENDOR_OPTS);
    EXPECT_FALSE(x == options.end());
    EXPECT_EQ(D6O_VENDOR_OPTS, x->second->getType());
    EXPECT_EQ(26, x->second->len());

    // CM MAC Address Option
    OptionPtr cm_mac = x->second->getOption(OPTION_CM_MAC);
    ASSERT_TRUE(cm_mac);
    EXPECT_EQ(OPTION_CM_MAC, cm_mac->getType());
    ASSERT_EQ(10, cm_mac->len());
    EXPECT_EQ(0, memcmp(&cm_mac->getData()[0], v6packed + 54, 6));

    // CMTS Capabilities
    OptionPtr cmts_caps = x->second->getOption(OPTION_CMTS_CAPS);
    ASSERT_TRUE(cmts_caps);
    EXPECT_EQ(OPTION_CMTS_CAPS, cmts_caps->getType());
    ASSERT_EQ(8, cmts_caps->len());
    EXPECT_EQ(0, memcmp(&cmts_caps->getData()[0], v6packed + 46, 4));

    x = options.find(0);
    EXPECT_TRUE(x == options.end()); // option 0 not found

    x = options.find(256); // 256 is htons(1) on little endians. Worth checking
    EXPECT_TRUE(x == options.end()); // option 1 not found

    x = options.find(7);
    EXPECT_TRUE(x == options.end()); // option 2 not found

    x = options.find(32000);
    EXPECT_TRUE(x == options.end()); // option 32000 not found */
}

/// V4 Options being used to test pack/unpack operations.
/// These are variable length options only so as there
/// is no restriction on the data length being carried by them.
/// For simplicity, we assign data of the length 3 for each
/// of them.
static uint8_t v4_opts[] = {
    12,  3, 0,   1,  2, // Hostname
    60,  3, 10, 11, 12, // Class Id
    14,  3, 20, 21, 22, // Merit Dump File
    254, 3, 30, 31, 32, // Reserved
    128, 3, 40, 41, 42, // Vendor specific
    0x52, 0x19,         // RAI
    0x01, 0x04, 0x20, 0x00, 0x00, 0x02, // Agent Circuit ID
    0x02, 0x06, 0x20, 0xE5, 0x2A, 0xB8, 0x15, 0x14, // Agent Remote ID
    0x09, 0x09, 0x00, 0x00, 0x11, 0x8B, 0x04, // Vendor Specific Information
    0x01, 0x02, 0x03, 0x00  // Vendor Specific Information continued
};

TEST_F(LibDhcpTest, packOptions4) {

    vector<uint8_t> payload[5];
    for (unsigned i = 0; i < 5; i++) {
        payload[i].resize(3);
        payload[i][0] = i*10;
        payload[i][1] = i*10+1;
        payload[i][2] = i*10+2;
    }

    OptionPtr opt1(new Option(Option::V4, 12, payload[0]));
    OptionPtr opt2(new Option(Option::V4, 60, payload[1]));
    OptionPtr opt3(new Option(Option::V4, 14, payload[2]));
    OptionPtr opt4(new Option(Option::V4,254, payload[3]));
    OptionPtr opt5(new Option(Option::V4,128, payload[4]));

    // Add RAI option, which comprises 3 sub-options.

    // Get the option definition for RAI option. This option is represented
    // by OptionCustom which requires a definition to be passed to
    // the constructor.
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(Option::V4,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));

    // The sub-options are created using the bits of v4_opts buffer because
    // we want to use this buffer as a reference to verify that produced
    // option in on-wire format is correct.

    // Create Ciruit ID sub-option and add to RAI.
    OptionPtr circuit_id(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                    OptionBuffer(v4_opts + 29,
                                                 v4_opts + 33)));
    rai->addOption(circuit_id);

    // Create Remote ID option and add to RAI.
    OptionPtr remote_id(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                   OptionBuffer(v4_opts + 35, v4_opts + 41)));
    rai->addOption(remote_id);

    // Create Vendor Specific Information and add to RAI.
    OptionPtr vsi(new Option(Option::V4, RAI_OPTION_VSI,
                             OptionBuffer(v4_opts + 43, v4_opts + 52)));
    rai->addOption(vsi);

    isc::dhcp::OptionCollection opts; // list of options
    // Note that we insert each option under the same option code into
    // the map. This gurantees that options are packed in the same order
    // they were added. Otherwise, options would get sorted by code and
    // the resulting buffer wouldn't match with the reference buffer.
    opts.insert(make_pair(opt1->getType(), opt1));
    opts.insert(make_pair(opt1->getType(), opt2));
    opts.insert(make_pair(opt1->getType(), opt3));
    opts.insert(make_pair(opt1->getType(), opt4));
    opts.insert(make_pair(opt1->getType(), opt5));
    opts.insert(make_pair(opt1->getType(), rai));

    OutputBuffer buf(100);
    EXPECT_NO_THROW(LibDHCP::packOptions(buf, opts));
    ASSERT_EQ(buf.getLength(), sizeof(v4_opts));
    EXPECT_EQ(0, memcmp(v4_opts, buf.getData(), sizeof(v4_opts)));
}

TEST_F(LibDhcpTest, unpackOptions4) {

    vector<uint8_t> v4packed(v4_opts, v4_opts + sizeof(v4_opts));
    isc::dhcp::OptionCollection options; // list of options

    ASSERT_NO_THROW(
        LibDHCP::unpackOptions4(v4packed, "dhcp4", options);
    );

    isc::dhcp::OptionCollection::const_iterator x = options.find(12);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    // Option 12 holds a string so let's cast it to an appropriate type.
    OptionStringPtr option12 = boost::static_pointer_cast<OptionString>(x->second);
    ASSERT_TRUE(option12);
    EXPECT_EQ(12, option12->getType());  // this should be option 12
    ASSERT_EQ(3, option12->getValue().length()); // it should be of length 3
    EXPECT_EQ(5, option12->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&option12->getValue()[0], v4_opts + 2, 3)); // data len=3

    x = options.find(60);
    ASSERT_FALSE(x == options.end()); // option 2 should exist
    EXPECT_EQ(60, x->second->getType());  // this should be option 60
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4_opts + 7, 3)); // data len=3

    x = options.find(14);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    OptionStringPtr option14 = boost::static_pointer_cast<OptionString>(x->second);
    ASSERT_TRUE(option14);
    EXPECT_EQ(14, option14->getType());  // this should be option 14
    ASSERT_EQ(3, option14->getValue().length()); // it should be of length 3
    EXPECT_EQ(5, option14->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&option14->getValue()[0], v4_opts + 12, 3)); // data len=3

    x = options.find(254);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(254, x->second->getType());  // this should be option 254
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4_opts + 17, 3)); // data len=3

    x = options.find(128);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(128, x->second->getType());  // this should be option 254
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4_opts + 22, 3)); // data len=3

    // Checking DHCP Relay Agent Information Option.
    x = options.find(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_FALSE(x == options.end());
    EXPECT_EQ(DHO_DHCP_AGENT_OPTIONS, x->second->getType());
    // RAI is represented by OptionCustom.
    OptionCustomPtr rai = boost::dynamic_pointer_cast<OptionCustom>(x->second);
    ASSERT_TRUE(rai);
    // RAI should have 3 sub-options: Circuit ID, Agent Remote ID, Vendor
    // Specific Information option. Note that by parsing these suboptions we
    // are checking that unpackOptions4 differentiates between standard option
    // space called "dhcp4" and other option spaces. These sub-options do not
    // belong to standard option space and should be parsed using different
    // option definitions.
    // @todo Currently, definitions for option space "dhcp-agent-options-space"
    // are not defined. Therefore all suboptions will be represented here by
    // the generic Option class.

    // Check that Circuit ID option is among parsed options.
    OptionPtr rai_option = rai->getOption(RAI_OPTION_AGENT_CIRCUIT_ID);
    ASSERT_TRUE(rai_option);
    EXPECT_EQ(RAI_OPTION_AGENT_CIRCUIT_ID, rai_option->getType());
    ASSERT_EQ(6, rai_option->len());
    EXPECT_EQ(0, memcmp(&rai_option->getData()[0], v4_opts + 29, 4));

    // Check that Remote ID option is among parsed options.
    rai_option = rai->getOption(RAI_OPTION_REMOTE_ID);
    ASSERT_TRUE(rai_option);
    EXPECT_EQ(RAI_OPTION_REMOTE_ID, rai_option->getType());
    ASSERT_EQ(8, rai_option->len());
    EXPECT_EQ(0, memcmp(&rai_option->getData()[0], v4_opts + 35, 6));

    // Check that Vendor Specific Information option is among parsed options.
    rai_option = rai->getOption(RAI_OPTION_VSI);
    ASSERT_TRUE(rai_option);
    EXPECT_EQ(RAI_OPTION_VSI, rai_option->getType());
    ASSERT_EQ(11, rai_option->len());
    EXPECT_EQ(0, memcmp(&rai_option->getData()[0], v4_opts + 43, 9));

    // Make sure, that option other than those above is not present.
    EXPECT_FALSE(rai->getOption(10));

    // Check the same for the global option space.
    x = options.find(0);
    EXPECT_TRUE(x == options.end()); // option 0 not found

    x = options.find(1);
    EXPECT_TRUE(x == options.end()); // option 1 not found

    x = options.find(2);
    EXPECT_TRUE(x == options.end()); // option 2 not found

}

TEST_F(LibDhcpTest, isStandardOption4) {
    // Get all option codes that are not occupied by standard options.
    const uint16_t unassigned_codes[] = { 84, 96, 102, 103, 104, 105, 106, 107, 108,
                                          109, 110, 111, 115, 126, 127, 147, 148, 149,
                                          178, 179, 180, 181, 182, 183, 184, 185, 186,
                                          187, 188, 189, 190, 191, 192, 193, 194, 195,
                                          196, 197, 198, 199, 200, 201, 202, 203, 204,
                                          205, 206, 207, 214, 215, 216, 217, 218, 219,
                                          222, 223, 224, 225, 226, 227, 228, 229, 230,
                                          231, 232, 233, 234, 235, 236, 237, 238, 239,
                                          240, 241, 242, 243, 244, 245, 246, 247, 248,
                                          249, 250, 251, 252, 253, 254 };
    const size_t unassigned_num = sizeof(unassigned_codes) / sizeof(unassigned_codes[0]);

    // Try all possible option codes.
    for (size_t i = 0; i < 256; ++i) {
        // Some ranges of option codes are unassigned and thus the isStandardOption
        // should return false for them.
        bool check_unassigned = false;
        // Check the array of unassigned options to find out whether option code
        // is assigned to standard option or unassigned.
        for (size_t j = 0; j < unassigned_num; ++j) {
            // If option code is found within the array of unassigned options
            // we the isStandardOption function should return false.
            if (unassigned_codes[j] == i) {
                check_unassigned = true;
                EXPECT_FALSE(LibDHCP::isStandardOption(Option::V4,
                                                       unassigned_codes[j]))
                    << "Test failed for option code " << unassigned_codes[j];
                break;
            }
        }
        // If the option code belongs to the standard option then the
        // isStandardOption should return true.
        if (!check_unassigned) {
            EXPECT_TRUE(LibDHCP::isStandardOption(Option::V4, i))
                << "Test failed for the option code " << i;
        }
    }
}

TEST_F(LibDhcpTest, isStandardOption6) {
    // All option codes in the range from 0 to 78 (except 10 and 35)
    // identify the standard options.
    for (uint16_t code = 0; code < 79; ++code) {
        if (code != 10 && code != 35) {
            EXPECT_TRUE(LibDHCP::isStandardOption(Option::V6, code))
                << "Test failed for option code " << code;
        }
    }

    // Check the option codes 10 and 35. They are unassigned.
    EXPECT_FALSE(LibDHCP::isStandardOption(Option::V6, 10));
    EXPECT_FALSE(LibDHCP::isStandardOption(Option::V6, 35));

    // Check a range of option codes above 78. Those are option codes
    // identifying non-standard options.
    for (uint16_t code = 79; code < 512; ++code) {
        EXPECT_FALSE(LibDHCP::isStandardOption(Option::V6, code))
            << "Test failed for option code " << code;
    }
}

TEST_F(LibDhcpTest, stdOptionDefs4) {

    // Create a buffer that holds dummy option data.
    // It will be used to create most of the options.
    std::vector<uint8_t> buf(48, 1);
    OptionBufferConstIter begin = buf.begin();
    OptionBufferConstIter end = buf.end();

    LibDhcpTest::testStdOptionDefs4(DHO_SUBNET_MASK, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_TIME_OFFSET, begin, begin + 4,
                                    typeid(OptionInt<int32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_ROUTERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_TIME_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_NAME_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_NAME_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_LOG_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_COOKIE_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_LPR_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_IMPRESS_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_RESOURCE_LOCATION_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_HOST_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_BOOT_SIZE, begin, begin + 2,
                                    typeid(OptionInt<uint16_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_MERIT_DUMP, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_SWAP_SERVER, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_ROOT_PATH, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_EXTENSIONS_PATH, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_IP_FORWARDING, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_NON_LOCAL_SOURCE_ROUTING, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_POLICY_FILTER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_MAX_DGRAM_REASSEMBLY, begin, begin + 2,
                                    typeid(OptionInt<uint16_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_DEFAULT_IP_TTL, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_PATH_MTU_AGING_TIMEOUT, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_PATH_MTU_PLATEAU_TABLE, begin, begin + 10,
                                    typeid(OptionIntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_INTERFACE_MTU, begin, begin + 2,
                                    typeid(OptionInt<uint16_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_ALL_SUBNETS_LOCAL, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_BROADCAST_ADDRESS, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_PERFORM_MASK_DISCOVERY, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_MASK_SUPPLIER, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_ROUTER_DISCOVERY, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_ROUTER_SOLICITATION_ADDRESS, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_STATIC_ROUTES, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_TRAILER_ENCAPSULATION, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_ARP_CACHE_TIMEOUT, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_IEEE802_3_ENCAPSULATION, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_DEFAULT_TCP_TTL, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_TCP_KEEPALIVE_INTERVAL, begin,
                                    begin + 4, typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_TCP_KEEPALIVE_GARBAGE, begin, begin + 1,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_NIS_DOMAIN, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_NIS_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_NTP_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    // The following option requires well formed buffer to be created from.
    // Not just a dummy one. This buffer includes some suboptions.
    OptionBuffer vendor_opts_buf = createVendorOption();
    LibDhcpTest::testStdOptionDefs4(DHO_VENDOR_ENCAPSULATED_OPTIONS,
                                    vendor_opts_buf.begin(),
                                    vendor_opts_buf.end(),
                                    typeid(OptionCustom),
                                    "vendor-encapsulated-options-space");

    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_NAME_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_DD_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_NODE_TYPE, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_NETBIOS_SCOPE, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_FONT_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_X_DISPLAY_MANAGER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_REQUESTED_ADDRESS, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_LEASE_TIME, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_OPTION_OVERLOAD, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_MESSAGE_TYPE, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_SERVER_IDENTIFIER, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_PARAMETER_REQUEST_LIST, begin, end,
                                    typeid(OptionUint8Array));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_MESSAGE, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_MAX_MESSAGE_SIZE, begin, begin + 2,
                                    typeid(OptionInt<uint16_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_RENEWAL_TIME, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_REBINDING_TIME, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_VENDOR_CLASS_IDENTIFIER, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_CLIENT_IDENTIFIER, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs4(DHO_NWIP_DOMAIN_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_NWIP_SUBOPTIONS, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs4(DHO_TFTP_SERVER_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_BOOT_FILE_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_USER_CLASS, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs4(DHO_FQDN, begin, begin + 3,
                                    typeid(Option4ClientFqdn));

    // The following option requires well formed buffer to be created from.
    // Not just a dummy one. This buffer includes some suboptions.
    OptionBuffer agent_info_buf = createAgentInformationOption();
    LibDhcpTest::testStdOptionDefs4(DHO_DHCP_AGENT_OPTIONS,
                                    agent_info_buf.begin(),
                                    agent_info_buf.end(),
                                    typeid(OptionCustom),
                                    "dhcp-agent-options-space");

    LibDhcpTest::testStdOptionDefs4(DHO_AUTHENTICATE, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs4(DHO_CLIENT_LAST_TRANSACTION_TIME,
                                    begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_ASSOCIATED_IP, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_SUBNET_SELECTION, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_SEARCH, begin, end,
                                    typeid(Option));

    // V-I Vendor option requires specially crafted data.
    const char vivco_data[] = {
        1, 2, 3, 4, // enterprise id
        3, 1, 2, 3  // first byte is opaque data length, the rest is opaque data
    };
    std::vector<uint8_t> vivco_buf(vivco_data, vivco_data + sizeof(vivco_data));
    const char vivsio_data[] = {
        1, 2, 3, 4, // enterprise id
        4,          // first byte is vendor block length
        1, 2, 3, 4  // option type=1 length=2
    };
    std::vector<uint8_t> vivsio_buf(vivsio_data, vivsio_data + sizeof(vivsio_data));

    LibDhcpTest::testStdOptionDefs4(DHO_VIVCO_SUBOPTIONS, vivco_buf.begin(),
                                    vivco_buf.end(), typeid(OptionVendorClass));


    LibDhcpTest::testStdOptionDefs4(DHO_VIVSO_SUBOPTIONS, vivsio_buf.begin(),
                                    vivsio_buf.end(), typeid(OptionVendor));
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
    OptionBufferConstIter begin = buf.begin();
    OptionBufferConstIter end = buf.end();

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

    // Prepare buffer holding a vendor option
    const char vopt_data[] = {
        1, 2, 3, 4,                               // enterprise=0x1020304
        0, 100,                                   // type=100
        0, 6,                                     // length=6
        102, 111, 111, 98, 97, 114                // data="foobar"
    };
    // Initialize a vector with the suboption data.
    std::vector<uint8_t> vopt_buf(vopt_data, vopt_data + sizeof(vopt_data));

    // The CLIENT_FQDN holds a uint8_t value and FQDN. We have
    // to add the uint8_t value to it and then append the buffer
    // holding some valid FQDN.
    std::vector<uint8_t> client_fqdn_buf(1);
    client_fqdn_buf.insert(client_fqdn_buf.end(), fqdn_buf.begin(),
                           fqdn_buf.end());

    // Initialize test buffer for Vendor Class option.
    const char vclass_data[] = {
        0x00, 0x01, 0x02, 0x03,
        0x00, 0x01, 0x02
    };
    std::vector<uint8_t> vclass_buf(vclass_data,
                                    vclass_data + sizeof(vclass_data));;

    // The actual test starts here for all supported option codes.
    LibDhcpTest::testStdOptionDefs6(D6O_CLIENTID, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_SERVERID, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_IA_NA, begin, end,
                                    typeid(Option6IA));

    LibDhcpTest::testStdOptionDefs6(D6O_IA_TA, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_IAADDR, begin, end,
                                    typeid(Option6IAAddr));

    LibDhcpTest::testStdOptionDefs6(D6O_ORO, begin, end,
                                    typeid(OptionIntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_PREFERENCE, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_ELAPSED_TIME, begin, begin + 2,
                                    typeid(OptionInt<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_RELAY_MSG, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_STATUS_CODE, begin, end,
                                    typeid(Option6StatusCode));

    LibDhcpTest::testStdOptionDefs6(D6O_RAPID_COMMIT, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_USER_CLASS, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_VENDOR_CLASS, vclass_buf.begin(),
                                    vclass_buf.end(),
                                    typeid(OptionVendorClass));

    LibDhcpTest::testStdOptionDefs6(D6O_VENDOR_OPTS, vopt_buf.begin(),
                                    vopt_buf.end(),
                                    typeid(OptionVendor),
                                    "vendor-opts-space");

    LibDhcpTest::testStdOptionDefs6(D6O_INTERFACE_ID, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_RECONF_MSG, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_RECONF_ACCEPT, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_SIP_SERVERS_DNS, fqdn_buf.begin(),
                                    fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SIP_SERVERS_ADDR, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NAME_SERVERS, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_DOMAIN_SEARCH, fqdn_buf.begin(),
                                    fqdn_buf.end(), typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_IA_PD, begin, end,
                                    typeid(Option6IA));

    LibDhcpTest::testStdOptionDefs6(D6O_IAPREFIX, begin, begin + 25,
                                    typeid(Option6IAPrefix));

    LibDhcpTest::testStdOptionDefs6(D6O_NIS_SERVERS, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NISP_SERVERS, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NIS_DOMAIN_NAME, fqdn_buf.begin(),
                                    fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_NISP_DOMAIN_NAME, fqdn_buf.begin(),
                                    fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SNTP_SERVERS, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_INFORMATION_REFRESH_TIME,
                                    begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_BCMCS_SERVER_D, fqdn_buf.begin(),
                                    fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_BCMCS_SERVER_A, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_GEOCONF_CIVIC, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_REMOTE_ID, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SUBSCRIBER_ID, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_CLIENT_FQDN, client_fqdn_buf.begin(),
                                    client_fqdn_buf.end(),
                                    typeid(Option6ClientFqdn));

    LibDhcpTest::testStdOptionDefs6(D6O_PANA_AGENT, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_PANA_AGENT, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_NEW_POSIX_TIMEZONE, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs6(D6O_NEW_TZDB_TIMEZONE, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs6(D6O_ERO, begin, end,
                                    typeid(OptionIntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_QUERY, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_CLIENT_DATA, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_CLT_TIME, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_RELAY_DATA, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_CLIENT_LINK, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_RSOO, begin, end,
                                    typeid(OptionCustom),
                                    "rsoo-opts");

    LibDhcpTest::testStdOptionDefs6(D6O_ERP_LOCAL_DOMAIN_NAME,
                                    fqdn_buf.begin(), fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_PUBLIC_KEY, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_CERTIFICATE, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_SIGNATURE, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_TIMESTAMP, begin, begin + 8,
                                    typeid(Option));
}

// This test checks if the DHCPv6 option definition can be searched by
// an option name.
TEST_F(LibDhcpTest, getOptionDefByName6) {
    // Get all definitions.
    const OptionDefContainer& defs = LibDHCP::getOptionDefs(Option::V6);
    // For each definition try to find it using option name.
    for (OptionDefContainer::const_iterator def = defs.begin();
         def != defs.end(); ++def) {
        OptionDefinitionPtr def_by_name =
            LibDHCP::getOptionDef(Option::V6, (*def)->getName());
        ASSERT_TRUE(def_by_name);
        ASSERT_TRUE(**def == *def_by_name);
    }
}


// This test checks if the DHCPv4 option definition can be searched by
// an option name.
TEST_F(LibDhcpTest, getOptionDefByName4) {
    // Get all definitions.
    const OptionDefContainer& defs = LibDHCP::getOptionDefs(Option::V4);
    // For each definition try to find it using option name.
    for (OptionDefContainer::const_iterator def = defs.begin();
         def != defs.end(); ++def) {
        OptionDefinitionPtr def_by_name =
            LibDHCP::getOptionDef(Option::V4, (*def)->getName());
        ASSERT_TRUE(def_by_name);
        ASSERT_TRUE(**def == *def_by_name);
    }
}

// This test checks if the definition of the DHCPv6 vendor option can
// be searched by option name.
TEST_F(LibDhcpTest, getVendorOptionDefByName6) {
    const OptionDefContainer* defs =
        LibDHCP::getVendorOption6Defs(VENDOR_ID_CABLE_LABS);
    ASSERT_TRUE(defs != NULL);
    for (OptionDefContainer::const_iterator def = defs->begin();
         def != defs->end(); ++def) {
        OptionDefinitionPtr def_by_name =
            LibDHCP::getVendorOptionDef(Option::V6, VENDOR_ID_CABLE_LABS,
                                        (*def)->getName());
        ASSERT_TRUE(def_by_name);
        ASSERT_TRUE(**def == *def_by_name);
    }
}

// This test checks if the definition of the DHCPv4 vendor option can
// be searched by option name.
TEST_F(LibDhcpTest, getVendorOptionDefByName4) {
    const OptionDefContainer* defs =
        LibDHCP::getVendorOption4Defs(VENDOR_ID_CABLE_LABS);
    ASSERT_TRUE(defs != NULL);
    for (OptionDefContainer::const_iterator def = defs->begin();
         def != defs->end(); ++def) {
        OptionDefinitionPtr def_by_name =
            LibDHCP::getVendorOptionDef(Option::V4, VENDOR_ID_CABLE_LABS,
                                        (*def)->getName());
        ASSERT_TRUE(def_by_name);
        ASSERT_TRUE(**def == *def_by_name);
    }
}

// tests whether v6 vendor-class option can be parsed properly.
TEST_F(LibDhcpTest, vendorClass6) {

    isc::dhcp::OptionCollection options; // Will store parsed option here

    // Exported from wireshark: vendor-class option with enterprise-id = 4491
    // and a single data entry containing "eRouter1.0"
    string vendor_class_hex = "001000100000118b000a65526f75746572312e30";
    OptionBuffer bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(vendor_class_hex, bin);

    ASSERT_NO_THROW ({
            LibDHCP::unpackOptions6(bin, "dhcp6", options);
        });

    EXPECT_EQ(options.size(), 1); // There should be 1 option.

    // Option vendor-class should be there
    ASSERT_FALSE(options.find(D6O_VENDOR_CLASS) == options.end());

    // It should be of type OptionVendorClass
    boost::shared_ptr<OptionVendorClass> vclass =
        boost::dynamic_pointer_cast<OptionVendorClass>(options.begin()->second);
    ASSERT_TRUE(vclass);

    // Let's investigate if the option content is correct

    // 3 fields expected: vendor-id, data-len and data
    EXPECT_EQ(4491, vclass->getVendorId());
    EXPECT_EQ(20, vclass->len());
    ASSERT_EQ(1, vclass->getTuplesNum());
    EXPECT_EQ("eRouter1.0", vclass->getTuple(0).getText());
}

} // end of anonymous space
