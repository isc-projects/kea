// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
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
#include <dhcp/option6_pdexclude.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <util/buffer.h>
#include <util/encode/hex.h>

#include <boost/pointer_cast.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <typeinfo>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

// DHCPv6 suboptions of Vendor Options Option.
/// @todo move to src/lib/dhcp/docsis3_option_defs.h once #3194 is merged.
const uint16_t OPTION_CMTS_CAPS = 1025;
const uint16_t OPTION_CM_MAC = 1026;

class LibDhcpTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Removes runtime option definitions.
    LibDhcpTest() {
        LibDHCP::clearRuntimeOptionDefs();
    }

    /// @brief Destructor.
    ///
    /// Removes runtime option definitions.
    virtual ~LibDhcpTest() {
        LibDHCP::clearRuntimeOptionDefs();
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
        testStdOptionDefs(Option::V4, DHCP4_OPTION_SPACE, code, begin, end,
                          expected_type, encapsulates);
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
        testStdOptionDefs(Option::V6, DHCP6_OPTION_SPACE, code, begin,
                          end, expected_type, encapsulates);
    }

    /// @brief Test DHCPv6 option definition in a given option space.
    ///
    /// This function tests if option definition for an option from a
    /// given option space has been initialized correctly.
    ///
    /// @param option_space option space.
    /// @param code option code.
    /// @param begin iterator pointing at beginning of a buffer to
    /// be used to create option instance.
    /// @param end iterator pointing at end of a buffer to be
    /// used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    /// @param encapsulates name of the option space being encapsulated
    /// by the option.
    static void testOptionDefs6(const std::string& option_space,
                                const uint16_t code,
                                const OptionBufferConstIter begin,
                                const OptionBufferConstIter end,
                                const std::type_info& expected_type,
                                const std::string& encapsulates = "") {
        testStdOptionDefs(Option::V6, option_space, code, begin,
                          end, expected_type, encapsulates);
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

    /// @brief Create option definitions and store in the container.
    ///
    /// @param spaces_num Number of option spaces to be created.
    /// @param defs_num Number of option definitions to be created for
    /// each option space.
    /// @param [out] defs Container to which option definitions should be
    /// added.
    static void createRuntimeOptionDefs(const uint16_t spaces_num,
                                        const uint16_t defs_num,
                                        OptionDefSpaceContainer& defs) {
        for (uint16_t space = 0; space < spaces_num; ++space) {
            std::ostringstream space_name;
            space_name << "option-space-" << space;
            for (uint16_t code = 0; code < defs_num; ++code) {
                std::ostringstream name;
                name << "name-for-option-" << code;
                OptionDefinitionPtr opt_def(new OptionDefinition(name.str(),
                                                                 code,
                                                                 space_name.str(),
                                                                 "string"));
                defs.addItem(opt_def);
            }
        }
    }

    /// @brief Test if runtime option definitions have been added.
    ///
    /// This method uses the same naming conventions for space names and
    /// options names as @c createRuntimeOptionDefs method.
    ///
    /// @param spaces_num Number of option spaces to be tested.
    /// @param defs_num Number of option definitions that should exist
    /// in each option space.
    /// @param should_exist Boolean value which indicates if option
    /// definitions should exist. If this is false, this function will
    /// check that they don't exist.
    static void testRuntimeOptionDefs(const uint16_t spaces_num,
                                      const uint16_t defs_num,
                                      const bool should_exist) {
        for (uint16_t space = 0; space < spaces_num; ++space) {
            std::ostringstream space_name;
            space_name << "option-space-" << space;
            for (uint16_t code = 0; code < defs_num; ++code) {
                std::ostringstream name;
                name << "name-for-option-" << code;
                OptionDefinitionPtr opt_def =
                    LibDHCP::getRuntimeOptionDef(space_name.str(), name.str());
                if (should_exist) {
                    ASSERT_TRUE(opt_def);
                } else {
                    ASSERT_FALSE(opt_def);
                }
            }
        }
    }

private:

    /// @brief Test DHCPv4 or DHCPv6 option definition.
    ///
    /// This function tests if option definition for standard
    /// option has been initialized correctly.
    ///
    /// @param option_space option space.
    /// @param code option code.
    /// @param begin iterator pointing at beginning of a buffer to
    /// be used to create option instance.
    /// @param end iterator pointing at end of a buffer to be
    /// used to create option instance.
    /// @param expected_type type of the option created by the
    /// factory function returned by the option definition.
    /// @param encapsulates name of the option space being encapsulated
    /// by the option.
    static void testStdOptionDefs(const Option::Universe& u,
                                  const std::string& option_space,
                                  const uint16_t code,
                                  const OptionBufferConstIter begin,
                                  const OptionBufferConstIter end,
                                  const std::type_info& expected_type,
                                  const std::string& encapsulates) {
        // Get all option definitions, we will use them to extract
        // the definition for a particular option code.
        // We don't have to initialize option definitions here because they
        // are initialized in the class's constructor.
        OptionDefContainerPtr options = LibDHCP::getOptionDefs(option_space);
        // Get the container index #1. This one allows for searching
        // option definitions using option code.
        const OptionDefContainerTypeIndex& idx = options->get<1>();
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
        EXPECT_EQ(encapsulates, def->getEncapsulatedSpace()) <<
            "opt name: " << def->getName();
        OptionPtr option;
        // Create the option.
        ASSERT_NO_THROW(option = def->optionFactory(u, code, begin, end))
            << "Option creation failed for option code " << code;
        // Make sure it is not NULL.
        ASSERT_TRUE(option);
        // And the actual object type is the one that we expect.
        // Note that for many options there are dedicated classes
        // derived from Option class to represent them.
        const Option* optptr = option.get();
        EXPECT_TRUE(typeid(*optptr) == expected_type)
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
    // is raised.
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

    EXPECT_NO_THROW(LibDHCP::packOptions6(assembled, opts));
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
                                    DHCP6_OPTION_SPACE, options);
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
    // Prepare the reference data.
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

// Check parsing of an empty DHCPv6 option.
TEST_F(LibDhcpTest, unpackEmptyOption6) {
    // Create option definition for the option code 1024 without fields.
    OptionDefinitionPtr opt_def(new OptionDefinition("option-empty", 1024,
                                                     DHCP6_OPTION_SPACE,
                                                     "empty", false));

    // Use it as runtime option definition within standard options space.
    // The tested code should find this option definition within runtime
    // option definitions set when it detects that this definition is
    // not a standard definition.
    OptionDefSpaceContainer defs;
    defs.addItem(opt_def);
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    // Create the buffer holding the structure of the empty option.
    OptionBuffer buf = {
      0x04, 0x00,                // option code = 1024
      0x00, 0x00                 // option length = 0
    };

    // Parse options.
    OptionCollection options;
    ASSERT_NO_THROW(LibDHCP::unpackOptions6(buf, DHCP6_OPTION_SPACE,
                                            options));

    // There should be one option.
    ASSERT_EQ(1, options.size());
    OptionPtr option_empty = options.begin()->second;
    ASSERT_TRUE(option_empty);
    EXPECT_EQ(1024, option_empty->getType());
    EXPECT_EQ(4, option_empty->len());
}

// This test verifies that the following option structure can be parsed:
// - option (option space 'foobar')
//   - sub option (option space 'foo')
//      - sub option (option space 'bar')
TEST_F(LibDhcpTest, unpackSubOptions6) {
    // Create option definition for each level of encapsulation. Each option
    // definition is for the option code 1. Options may have the same
    // option code because they belong to different option spaces.

    // Top level option encapsulates options which belong to 'space-foo'.
    OptionDefinitionPtr opt_def(new OptionDefinition("option-foobar", 1,
                                                     "space-foobar",
                                                     "uint32",
                                                     "space-foo"));
    // Middle option encapsulates options which belong to 'space-bar'
    OptionDefinitionPtr opt_def2(new OptionDefinition("option-foo", 1,
                                                      "space-foo",
                                                      "uint16",
                                                      "space-bar"));
    // Low level option doesn't encapsulate any option space.
    OptionDefinitionPtr opt_def3(new OptionDefinition("option-bar", 1,
                                                      "space-bar",
                                                      "uint8"));

    // Register created option definitions as runtime option definitions.
    OptionDefSpaceContainer defs;
    ASSERT_NO_THROW(defs.addItem(opt_def));
    ASSERT_NO_THROW(defs.addItem(opt_def2));
    ASSERT_NO_THROW(defs.addItem(opt_def3));
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    // Create the buffer holding the structure of options.
    OptionBuffer buf = {
        // First option starts here.
        0x00, 0x01,   // option code = 1
        0x00, 0x0F,   // option length = 15
        0x00, 0x01, 0x02, 0x03, // This option carries uint32 value
        // Sub option starts here.
        0x00, 0x01,  // option code = 1
        0x00, 0x07,  // option length = 7
        0x01, 0x02,  // this option carries uint16 value
        // Last option starts here.
        0x00, 0x01,  // option code = 1
        0x00, 0x01,  // option length = 1
        0x00 // This option carries a single uint8 value and has no sub options.
    };

    // Parse options.
    OptionCollection options;
    ASSERT_NO_THROW(LibDHCP::unpackOptions6(buf, "space-foobar", options, 0, 0));

    // There should be one top level option.
    ASSERT_EQ(1, options.size());
    boost::shared_ptr<OptionInt<uint32_t> > option_foobar =
        boost::dynamic_pointer_cast<OptionInt<uint32_t> >(options.begin()->
                                                          second);
    ASSERT_TRUE(option_foobar);
    EXPECT_EQ(1, option_foobar->getType());
    EXPECT_EQ(0x00010203, option_foobar->getValue());
    // There should be a middle level option held in option_foobar.
    boost::shared_ptr<OptionInt<uint16_t> > option_foo =
        boost::dynamic_pointer_cast<OptionInt<uint16_t> >(option_foobar->
                                                          getOption(1));
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(1, option_foo->getType());
    EXPECT_EQ(0x0102, option_foo->getValue());
    // Finally, there should be a low level option under option_foo.
    boost::shared_ptr<OptionInt<uint8_t> > option_bar =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >(option_foo->getOption(1));
    ASSERT_TRUE(option_bar);
    EXPECT_EQ(1, option_bar->getType());
    EXPECT_EQ(0x0, option_bar->getValue());
}

/// V4 Options being used to test pack/unpack operations.
/// These are variable length options only so as there
/// is no restriction on the data length being carried by them.
/// For simplicity, we assign data of the length 3 for each
/// of them.
static uint8_t v4_opts[] = {
    12,  3, 0,   1,  2,        // Hostname
    60,  3, 10, 11, 12,        // Class Id
    14,  3, 20, 21, 22,        // Merit Dump File
    254, 3, 30, 31, 32,        // Reserved
    128, 3, 40, 41, 42,        // Vendor specific
    125, 11, 0, 0, 0x11, 0x8B, // V-I Vendor-Specific Information (Cable Labs)
    6, 2, 4, 10, 0, 0, 10,     // TFTP servers suboption (2)
    43, 2,                     // Vendor Specific Information
    0xDC, 0,                   // VSI suboption
    0x52, 0x19,                // RAI
    0x01, 0x04, 0x20, 0x00, 0x00, 0x02, // Agent Circuit ID
    0x02, 0x06, 0x20, 0xE5, 0x2A, 0xB8, 0x15, 0x14, // Agent Remote ID
    0x09, 0x09, 0x00, 0x00, 0x11, 0x8B, 0x04, // Vendor Specific Information
    0x01, 0x02, 0x03, 0x00 // Vendor Specific Information continued
};

// This test verifies that split options throws if there is no space left in the
// packet buffer.
TEST_F(LibDhcpTest, splitOptionNoBuffer) {
    OptionDefinition opt_def("option-foo", 231, "my-space", "binary",
                             "option-foo-space");

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(2560);
    for (uint32_t i = 0; i < 2560; ++i) {
        buf_in[i] = i;
    }

    boost::shared_ptr<OptionCustom> option;
    ASSERT_NO_THROW(option.reset(new OptionCustom(opt_def, Option::V4, buf_in)));
    ASSERT_TRUE(option);
    isc::util::OutputBuffer buf(0);
    OptionCollection col;
    col.insert(std::make_pair(231, option));
    ManagedScopedOptionsCopyContainer scoped_options;
    ASSERT_THROW(LibDHCP::splitOptions4(col, scoped_options.scoped_options_, 253), BadValue);
}

// This test verifies that split options works if there is only one byte
// available for data in the packet buffer.
TEST_F(LibDhcpTest, splitOptionOneByteLeftBuffer) {
    OptionDefinition opt_def("option-foo", 231, "my-space", "binary",
                             "option-foo-space");

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(64);
    for (uint32_t i = 0; i < 64; ++i) {
        buf_in[i] = i;
    }

    boost::shared_ptr<OptionCustom> option;
    ASSERT_NO_THROW(option.reset(new OptionCustom(opt_def, Option::V4, buf_in)));
    ASSERT_TRUE(option);
    isc::util::OutputBuffer buf(0);
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 1234));
    OptionCollection& col = pkt->options_;
    col.clear();
    col.insert(std::make_pair(231, option));
    std::string expected = pkt->toText();
    {
        ScopedPkt4OptionsCopy initial_scoped_options(*pkt);
        ManagedScopedOptionsCopyContainer scoped_options;
        ASSERT_NO_THROW(LibDHCP::splitOptions4(col, scoped_options.scoped_options_, 252));
        ASSERT_NO_THROW(LibDHCP::packOptions4(buf, col, true));
        ASSERT_NE(expected, pkt->toText());

        ASSERT_EQ(64, col.size());
        uint8_t index = 0;
        for (auto const& option : col) {
            ASSERT_EQ(option.first, 231);
            ASSERT_EQ(1, option.second->getData().size());
            ASSERT_EQ(index, option.second->getData()[0]);
            index++;
        }
    }
    ASSERT_EQ(expected, pkt->toText());
}

// This test verifies that split options for v4 is working correctly.
TEST_F(LibDhcpTest, splitLongOption) {
    OptionDefinition opt_def("option-foo", 231, "my-space", "binary",
                             "option-foo-space");

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(2560);
    for (uint32_t i = 0; i < 2560; ++i) {
        buf_in[i] = i;
    }

    boost::shared_ptr<OptionCustom> option;
    ASSERT_NO_THROW(option.reset(new OptionCustom(opt_def, Option::V4, buf_in)));
    ASSERT_TRUE(option);
    isc::util::OutputBuffer buf(0);
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 1234));
    OptionCollection& col = pkt->options_;
    col.clear();
    col.insert(std::make_pair(231, option));
    std::string expected = pkt->toText();
    {
        ScopedPkt4OptionsCopy initial_scoped_options(*pkt);
        ManagedScopedOptionsCopyContainer scoped_options;
        ASSERT_NO_THROW(LibDHCP::splitOptions4(col, scoped_options.scoped_options_));
        ASSERT_NO_THROW(LibDHCP::packOptions4(buf, col, true));
        ASSERT_NE(expected, pkt->toText());

        ASSERT_EQ(11, col.size());
        ASSERT_EQ(2560 + 11 * option->getHeaderLen(), buf.getLength());
    }
    ASSERT_EQ(expected, pkt->toText());

    OptionCollection col_back;
    std::list<uint16_t> deferred_options;

    size_t opts_len = buf.getLength();
    vector<uint8_t> opts_buffer;
    InputBuffer buffer_in(buf.getData(), opts_len);

    // Use readVector because a function which parses option requires
    // a vector as an input.
    buffer_in.readVector(opts_buffer, opts_len);
    ASSERT_NO_THROW(LibDHCP::unpackOptions4(opts_buffer, DHCP4_OPTION_SPACE,
                    col_back, deferred_options));

    uint32_t index = 0;
    ASSERT_EQ(11, col_back.size());
    for (auto const& option : col_back) {
        ASSERT_EQ(option.first, 231);
        for (auto const& value : option.second->getData()) {
            ASSERT_EQ(value, static_cast<uint8_t>(index));
            index++;
        }
    }
    ASSERT_EQ(index, 2560);
}

// This test verifies that split options for v4 is working correctly even if
// every suboption is smaller than 255 bytes, but the parent option still
// overflows.
TEST_F(LibDhcpTest, splitOptionWithSuboptionWhichOverflow) {
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    // Create RAI options which should be fused by the server.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(128);
    for (uint32_t i = 0; i < 128; ++i) {
        buf_in[i] = i;
    }

    OptionPtr circuit_id_opt(new Option(Option::V4,
                                        RAI_OPTION_AGENT_CIRCUIT_ID, buf_in));
    ASSERT_TRUE(circuit_id_opt);
    rai->addOption(circuit_id_opt);

    OptionPtr remote_id_opt(new Option(Option::V4,
                                       RAI_OPTION_REMOTE_ID, buf_in));
    ASSERT_TRUE(remote_id_opt);
    rai->addOption(remote_id_opt);

    OptionPtr subscriber_id_opt(new Option(Option::V4,
                                           RAI_OPTION_SUBSCRIBER_ID, buf_in));
    ASSERT_TRUE(subscriber_id_opt);
    rai->addOption(subscriber_id_opt);

    isc::util::OutputBuffer buf(0);
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 1234));
    OptionCollection& col = pkt->options_;
    col.clear();
    col.insert(std::make_pair(DHO_DHCP_AGENT_OPTIONS, rai));
    std::string expected = pkt->toText();
    {
        ScopedPkt4OptionsCopy initial_scoped_options(*pkt);
        ManagedScopedOptionsCopyContainer scoped_options;
        ASSERT_NO_THROW(LibDHCP::splitOptions4(col, scoped_options.scoped_options_));
        ASSERT_NO_THROW(LibDHCP::packOptions4(buf, col, true));
        ASSERT_NE(expected, pkt->toText());

        ASSERT_EQ(3, col.size());
        ASSERT_EQ(3 * rai->getHeaderLen() + circuit_id_opt->getHeaderLen() +
                  remote_id_opt->getHeaderLen() + subscriber_id_opt->getHeaderLen() +
                  3 * 128, buf.getLength());
    }
    ASSERT_EQ(expected, pkt->toText());

    OptionCollection col_back;
    std::list<uint16_t> deferred_options;

    size_t opts_len = buf.getLength();
    vector<uint8_t> opts_buffer;
    InputBuffer buffer_in(buf.getData(), opts_len);

    // Use readVector because a function which parses option requires
    // a vector as an input.
    buffer_in.readVector(opts_buffer, opts_len);
    ASSERT_NO_THROW(LibDHCP::unpackOptions4(opts_buffer, DHCP4_OPTION_SPACE,
                    col_back, deferred_options));

    uint8_t index = 0;
    uint8_t opt_number = 0;
    uint32_t opt_type = RAI_OPTION_AGENT_CIRCUIT_ID;
    ASSERT_EQ(3, col_back.size());
    for (auto const& option : col_back) {
        ASSERT_EQ(option.first, DHO_DHCP_AGENT_OPTIONS);
        for (auto const& sub_option : option.second->getOptions()) {
            if (sub_option.first != opt_type) {
                opt_type = sub_option.first;
                ASSERT_EQ(index, 128);
                index = 0;
                opt_number++;
            }
            if (opt_number == 0) {
                ASSERT_EQ(sub_option.first, RAI_OPTION_AGENT_CIRCUIT_ID);
            } else if (opt_number == 1) {
                ASSERT_EQ(sub_option.first, RAI_OPTION_REMOTE_ID);
            } else if (opt_number == 2){
                ASSERT_EQ(sub_option.first, RAI_OPTION_SUBSCRIBER_ID);
            }
            for (auto const& value : sub_option.second->getData()) {
                ASSERT_EQ(value, index);
                index++;
            }
        }
    }
    ASSERT_EQ(index, 128);
}

// This test verifies that split options for v4 is working correctly.
TEST_F(LibDhcpTest, splitLongOptionWithLongSuboption) {
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    // Create RAI options which should be fused by the server.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(2560);
    for (uint32_t i = 0; i < 2560; ++i) {
        buf_in[i] = i;
    }

    OptionPtr circuit_id_opt(new Option(Option::V4,
                                        RAI_OPTION_AGENT_CIRCUIT_ID, buf_in));
    ASSERT_TRUE(circuit_id_opt);
    rai->addOption(circuit_id_opt);

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer small_buf_in(64);
    for (uint32_t i = 0; i < 64; ++i) {
        small_buf_in[i] = i;
    }

    OptionPtr remote_id_opt(new Option(Option::V4,
                                       RAI_OPTION_REMOTE_ID, small_buf_in));
    ASSERT_TRUE(remote_id_opt);
    rai->addOption(remote_id_opt);

    OptionPtr subscriber_id_opt(new Option(Option::V4,
                                           RAI_OPTION_SUBSCRIBER_ID, buf_in));
    ASSERT_TRUE(subscriber_id_opt);
    rai->addOption(subscriber_id_opt);

    isc::util::OutputBuffer buf(0);
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 1234));
    OptionCollection& col = pkt->options_;
    col.clear();
    col.insert(std::make_pair(DHO_DHCP_AGENT_OPTIONS, rai));
    std::string expected = pkt->toText();
    {
        ScopedPkt4OptionsCopy initial_scoped_options(*pkt);
        ManagedScopedOptionsCopyContainer scoped_options;
        ASSERT_NO_THROW(LibDHCP::splitOptions4(col, scoped_options.scoped_options_));
        ASSERT_NO_THROW(LibDHCP::packOptions4(buf, col, true));
        ASSERT_NE(expected, pkt->toText());

        ASSERT_EQ(23, col.size());
        ASSERT_EQ((11 + 1 + 11) * rai->getHeaderLen() + 11 * circuit_id_opt->getHeaderLen() +
                  remote_id_opt->getHeaderLen() + 11 * subscriber_id_opt->getHeaderLen() +
                  2560 + 64 + 2560, buf.getLength());
    }
    ASSERT_EQ(expected, pkt->toText());

    OptionCollection col_back;
    std::list<uint16_t> deferred_options;

    size_t opts_len = buf.getLength();
    vector<uint8_t> opts_buffer;
    InputBuffer buffer_in(buf.getData(), opts_len);

    // Use readVector because a function which parses option requires
    // a vector as an input.
    buffer_in.readVector(opts_buffer, opts_len);
    ASSERT_NO_THROW(LibDHCP::unpackOptions4(opts_buffer, DHCP4_OPTION_SPACE,
                    col_back, deferred_options));

    uint32_t index = 0;
    uint8_t opt_number = 0;
    uint32_t opt_type = RAI_OPTION_AGENT_CIRCUIT_ID;
    ASSERT_EQ(23, col_back.size());
    for (auto const& option : col_back) {
        ASSERT_EQ(option.first, DHO_DHCP_AGENT_OPTIONS);
        for (auto const& sub_option : option.second->getOptions()) {
            if (sub_option.first != opt_type) {
                opt_type = sub_option.first;
                if (opt_number == 0) {
                    ASSERT_EQ(index, 2560);
                } else if (opt_number == 1) {
                    ASSERT_EQ(index, 64);
                } else if (opt_number == 2){
                    ASSERT_EQ(index, 2560);
                }
                index = 0;
                opt_number++;
            }
            if (opt_number == 0) {
                ASSERT_EQ(sub_option.first, RAI_OPTION_AGENT_CIRCUIT_ID);
            } else if (opt_number == 1) {
                ASSERT_EQ(sub_option.first, RAI_OPTION_REMOTE_ID);
            } else if (opt_number == 2){
                ASSERT_EQ(sub_option.first, RAI_OPTION_SUBSCRIBER_ID);
            }
            for (auto const& value : sub_option.second->getData()) {
                ASSERT_EQ(value, static_cast<uint8_t>(index));
                index++;
            }
        }
    }
    ASSERT_EQ(index, 2560);
}

// This test verifies that fuse options for v4 is working correctly.
TEST_F(LibDhcpTest, fuseLongOption) {
    OptionCollection col;

    OptionDefinition opt_def("option-foo", 231, "my-space", "binary",
                             "option-foo-space");

    for (uint32_t i = 0; i < 256; ++i) {
        // Create a buffer holding some binary data. This data will be
        // used as reference when we read back the data from a created
        // option.
        OptionBuffer buf_in(64);
        for (uint32_t j = 0; j < 64; ++j) {
            buf_in[j] = j;
        }

        boost::shared_ptr<OptionCustom> option;
        ASSERT_NO_THROW(option.reset(new OptionCustom(opt_def, Option::V4, buf_in)));
        ASSERT_TRUE(option);
        col.insert(std::make_pair(231, option));
    }
    ASSERT_EQ(256, col.size());
    LibDHCP::fuseOptions4(col);

    ASSERT_EQ(1, col.size());
    uint8_t index = 0;
    for (auto const& option : col) {
        for (auto const& value : option.second->getData()) {
            ASSERT_EQ(index, value);
            index++;
            if (index == 64) {
                index = 0;
            }
        }
    }
}

// This test verifies that fuse options for v4 is working correctly.
TEST_F(LibDhcpTest, fuseLongOptionWithLongSuboption) {
    OptionCollection col;

    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                         DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    // Create RAI options which should be fused by the server.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));

    for (uint32_t i = 0; i < 256; ++i) {
        // Create a buffer holding some binary data. This data will be
        // used as reference when we read back the data from a created
        // option.
        OptionBuffer buf_in(64);
        for (uint32_t j = 0; j < 64; ++j) {
            buf_in[j] = j;
        }

        OptionPtr circuit_id_opt(new Option(Option::V4,
                                            RAI_OPTION_AGENT_CIRCUIT_ID, buf_in));
        ASSERT_TRUE(circuit_id_opt);
        rai->addOption(circuit_id_opt);
    }
    col.insert(std::make_pair(213, rai));
    ASSERT_EQ(1, col.size());
    ASSERT_EQ(256, col.begin()->second->getOptions().size());
    LibDHCP::fuseOptions4(col);

    ASSERT_EQ(1, col.size());
    ASSERT_EQ(1, col.begin()->second->getOptions().size());
    uint8_t index = 0;
    for (auto const& option : col.begin()->second->getOptions()) {
        for (auto const& value : option.second->getData()) {
            ASSERT_EQ(index, value);
            index++;
            if (index == 64) {
                index = 0;
            }
        }
    }
}

// This test verifies that pack options for v4 is working correctly.
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

    // Create vendor option instance with DOCSIS3.0 enterprise id.
    OptionVendorPtr vivsi(new OptionVendor(Option::V4, 4491));
    vivsi->addOption(OptionPtr(new Option4AddrLst(DOCSIS3_V4_TFTP_SERVERS,
                                                  IOAddress("10.0.0.10"))));

    OptionPtr vsi(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS,
                              OptionBuffer()));
    vsi->addOption(OptionPtr(new Option(Option::V4, 0xDC, OptionBuffer())));

    // Add RAI option, which comprises 3 sub-options.

    // Get the option definition for RAI option. This option is represented
    // by OptionCustom which requires a definition to be passed to
    // the constructor.
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));

    // The sub-options are created using the bits of v4_opts buffer because
    // we want to use this buffer as a reference to verify that produced
    // option in on-wire format is correct.

    // Create Circuit ID sub-option and add to RAI.
    OptionPtr circuit_id(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                    OptionBuffer(v4_opts + 46,
                                                 v4_opts + 50)));
    rai->addOption(circuit_id);

    // Create Remote ID option and add to RAI.
    OptionPtr remote_id(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                   OptionBuffer(v4_opts + 52, v4_opts + 58)));
    rai->addOption(remote_id);

    // Create Vendor Specific Information and add to RAI.
    OptionPtr rai_vsi(new Option(Option::V4, RAI_OPTION_VSI,
                                 OptionBuffer(v4_opts + 60, v4_opts + 69)));
    rai->addOption(rai_vsi);

    isc::dhcp::OptionCollection opts; // list of options
    // Note that we insert each option under the same option code into
    // the map. This guarantees that options are packed in the same order
    // they were added. Otherwise, options would get sorted by code and
    // the resulting buffer wouldn't match with the reference buffer.
    opts.insert(make_pair(opt1->getType(), opt1));
    opts.insert(make_pair(opt1->getType(), opt2));
    opts.insert(make_pair(opt1->getType(), opt3));
    opts.insert(make_pair(opt1->getType(), opt4));
    opts.insert(make_pair(opt1->getType(), opt5));
    opts.insert(make_pair(opt1->getType(), vivsi));
    opts.insert(make_pair(opt1->getType(), vsi));
    opts.insert(make_pair(opt1->getType(), rai));

    OutputBuffer buf(100);
    EXPECT_NO_THROW(LibDHCP::packOptions4(buf, opts));
    ASSERT_EQ(buf.getLength(), sizeof(v4_opts));
    EXPECT_EQ(0, memcmp(v4_opts, buf.getData(), sizeof(v4_opts)));
}

// This test verifies that pack options for v4 is working correctly
// and RAI option is packed last.
TEST_F(LibDhcpTest, packOptions4Order) {

    uint8_t expected[] = {
        12,  3, 0,   1,  2, // Just a random option
        99,  3, 10, 11, 12, // Another random option
        82,  3, 20, 21, 22 // Relay Agent Info option
    };

    vector<uint8_t> payload[3];
    for (unsigned i = 0; i < 3; i++) {
        payload[i].resize(3);
        payload[i][0] = i*10;
        payload[i][1] = i*10+1;
        payload[i][2] = i*10+2;
    }

    OptionPtr opt12(new Option(Option::V4, 12, payload[0]));
    OptionPtr opt99(new Option(Option::V4, 99, payload[1]));
    OptionPtr opt82(new Option(Option::V4, 82, payload[2]));

    // Let's create options. They are added in 82,12,99, but the should be
    // packed in 12,99,82 order (82, which is RAI, should go last)
    isc::dhcp::OptionCollection opts;
    opts.insert(make_pair(opt82->getType(), opt82));
    opts.insert(make_pair(opt12->getType(), opt12));
    opts.insert(make_pair(opt99->getType(), opt99));

    OutputBuffer buf(100);
    EXPECT_NO_THROW(LibDHCP::packOptions4(buf, opts));
    ASSERT_EQ(buf.getLength(), sizeof(expected));
    EXPECT_EQ(0, memcmp(expected, buf.getData(), sizeof(expected)));
}

TEST_F(LibDhcpTest, unpackOptions4) {

    vector<uint8_t> v4packed(v4_opts, v4_opts + sizeof(v4_opts));
    isc::dhcp::OptionCollection options; // list of options
    list<uint16_t> deferred;

    ASSERT_NO_THROW(
        LibDHCP::unpackOptions4(v4packed, DHCP4_OPTION_SPACE, options,
                                deferred, false);
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
    ASSERT_FALSE(x == options.end()); // option 4 should exist
    EXPECT_EQ(254, x->second->getType());  // this should be option 254
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4_opts + 17, 3)); // data len=3

    x = options.find(128);
    ASSERT_FALSE(x == options.end()); // option 5 should exist
    EXPECT_EQ(128, x->second->getType());  // this should be option 128
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4_opts + 22, 3)); // data len=3

    // Verify that V-I Vendor Specific Information option is parsed correctly.
    x = options.find(125);
    ASSERT_FALSE(x == options.end());
    OptionVendorPtr vivsi = boost::dynamic_pointer_cast<OptionVendor>(x->second);
    ASSERT_TRUE(vivsi);
    EXPECT_EQ(DHO_VIVSO_SUBOPTIONS, vivsi->getType());
    EXPECT_EQ(4491, vivsi->getVendorId());
    OptionCollection suboptions = vivsi->getOptions();

    // There should be one suboption of V-I VSI.
    ASSERT_EQ(1, suboptions.size());
    // This vendor option has a standard definition and thus should be
    // converted to appropriate class, i.e. Option4AddrLst. If this cast
    // fails, it means that its definition was not used while it was
    // parsed.
    Option4AddrLstPtr tftp =
        boost::dynamic_pointer_cast<Option4AddrLst>(suboptions.begin()->second);
    ASSERT_TRUE(tftp);
    EXPECT_EQ(DOCSIS3_V4_TFTP_SERVERS, tftp->getType());
    EXPECT_EQ(6, tftp->len());
    Option4AddrLst::AddressContainer addresses = tftp->getAddresses();
    ASSERT_EQ(1, addresses.size());
    EXPECT_EQ("10.0.0.10", addresses[0].toText());

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
    EXPECT_EQ(0, memcmp(&rai_option->getData()[0], v4_opts + 46, 4));

    // Check that Remote ID option is among parsed options.
    rai_option = rai->getOption(RAI_OPTION_REMOTE_ID);
    ASSERT_TRUE(rai_option);
    EXPECT_EQ(RAI_OPTION_REMOTE_ID, rai_option->getType());
    ASSERT_EQ(8, rai_option->len());
    EXPECT_EQ(0, memcmp(&rai_option->getData()[0], v4_opts + 52, 6));

    // Check that Vendor Specific Information option is among parsed options.
    rai_option = rai->getOption(RAI_OPTION_VSI);
    ASSERT_TRUE(rai_option);
    EXPECT_EQ(RAI_OPTION_VSI, rai_option->getType());
    ASSERT_EQ(11, rai_option->len());
    EXPECT_EQ(0, memcmp(&rai_option->getData()[0], v4_opts + 60, 9));

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

// Check parsing of an empty option.
TEST_F(LibDhcpTest, unpackEmptyOption4) {
    // Create option definition for the option code 254 without fields.
    OptionDefinitionPtr opt_def(new OptionDefinition("option-empty", 254,
                                                     DHCP4_OPTION_SPACE,
                                                     "empty", false));

    // Use it as runtime option definition within standard options space.
    // The tested code should find this option definition within runtime
    // option definitions set when it detects that this definition is
    // not a standard definition.
    OptionDefSpaceContainer defs;
    defs.addItem(opt_def);
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    // Create the buffer holding the structure of the empty option.
    OptionBuffer buf = {
      0xFE,                     // option code = 254
      0x00                      // option length = 0
    };

    // Parse options.
    OptionCollection options;
    list<uint16_t> deferred;
    ASSERT_NO_THROW(LibDHCP::unpackOptions4(buf, DHCP4_OPTION_SPACE,
                                            options, deferred, false));

    // There should be one option.
    ASSERT_EQ(1, options.size());
    OptionPtr option_empty = options.begin()->second;
    ASSERT_TRUE(option_empty);
    EXPECT_EQ(254, option_empty->getType());
    EXPECT_EQ(2, option_empty->len());
}

// This test verifies that the following option structure can be parsed:
// - option (option space 'foobar')
//   - sub option (option space 'foo')
//      - sub option (option space 'bar')
// @todo Add more thorough unit tests for unpackOptions.
TEST_F(LibDhcpTest, unpackSubOptions4) {
    // Create option definition for each level of encapsulation. Each option
    // definition is for the option code 1. Options may have the same
    // option code because they belong to different option spaces.

    // Top level option encapsulates options which belong to 'space-foo'.
    OptionDefinitionPtr opt_def(new OptionDefinition("option-foobar", 1,
                                                     "space-foobar",
                                                     "uint32",
                                                     "space-foo"));     \
    // Middle option encapsulates options which belong to 'space-bar'
    OptionDefinitionPtr opt_def2(new OptionDefinition("option-foo", 1,
                                                      "space-foo",
                                                      "uint16",
                                                      "space-bar"));
    // Low level option doesn't encapsulate any option space.
    OptionDefinitionPtr opt_def3(new OptionDefinition("option-bar", 1,
                                                      "space-bar",
                                                      "uint8"));

    // Register created option definitions as runtime option definitions.
    OptionDefSpaceContainer defs;
    ASSERT_NO_THROW(defs.addItem(opt_def));
    ASSERT_NO_THROW(defs.addItem(opt_def2));
    ASSERT_NO_THROW(defs.addItem(opt_def3));
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    // Create the buffer holding the structure of options.
    OptionBuffer buf = {
        // First option starts here.
        0x01,                   // option code = 1
        0x0B,                   // option length = 11
        0x00, 0x01, 0x02, 0x03, // This option carries uint32 value
        // Sub option starts here.
        0x01,                   // option code = 1
        0x05,                   // option length = 5
        0x01, 0x02,             // this option carries uint16 value
        // Last option starts here.
        0x01,                   // option code = 1
        0x01,                   // option length = 1
        0x00                    // This option carries a single uint8
                                // value and has no sub options.
    };

    // Parse options.
    OptionCollection options;
    list<uint16_t> deferred;
    ASSERT_NO_THROW(LibDHCP::unpackOptions4(buf, "space-foobar",
                                            options, deferred, false));

    // There should be one top level option.
    ASSERT_EQ(1, options.size());
    boost::shared_ptr<OptionInt<uint32_t> > option_foobar =
        boost::dynamic_pointer_cast<OptionInt<uint32_t> >(options.begin()->
                                                          second);
    ASSERT_TRUE(option_foobar);
    EXPECT_EQ(1, option_foobar->getType());
    EXPECT_EQ(0x00010203, option_foobar->getValue());
    // There should be a middle level option held in option_foobar.
    boost::shared_ptr<OptionInt<uint16_t> > option_foo =
        boost::dynamic_pointer_cast<OptionInt<uint16_t> >(option_foobar->
                                                          getOption(1));
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(1, option_foo->getType());
    EXPECT_EQ(0x0102, option_foo->getValue());
    // Finally, there should be a low level option under option_foo.
    boost::shared_ptr<OptionInt<uint8_t> > option_bar =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >(option_foo->getOption(1));
    ASSERT_TRUE(option_bar);
    EXPECT_EQ(1, option_bar->getType());
    EXPECT_EQ(0x0, option_bar->getValue());
}

// Verifies that options 0 (PAD) and 255 (END) are handled as PAD and END
// in and only in the dhcp4 space.
TEST_F(LibDhcpTest, unpackPadEnd) {
    // Create option definition for the container.
    OptionDefinitionPtr opt_def(new OptionDefinition("container", 200,
                                                     DHCP4_OPTION_SPACE,
                                                     "empty", "my-space"));
    // Create option definition for option 0.
    OptionDefinitionPtr opt_def0(new OptionDefinition("zero", 0,
                                                      "my-space", "uint8"));

    // Create option definition for option 255.
    OptionDefinitionPtr opt_def255(new OptionDefinition("max", 255,
                                                        "my-space", "uint8"));

    // Create option definition for another option.
    OptionDefinitionPtr opt_def2(new OptionDefinition("my-option", 1,
                                                      "my-space", "string"));

    // Register created option definitions as runtime option definitions.
    OptionDefSpaceContainer defs;
    ASSERT_NO_THROW(defs.addItem(opt_def));
    ASSERT_NO_THROW(defs.addItem(opt_def0));
    ASSERT_NO_THROW(defs.addItem(opt_def255));
    ASSERT_NO_THROW(defs.addItem(opt_def2));
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    // Create the buffer holding the structure of options.
    OptionBuffer buf = {
        // Add a PAD
        0x00,                         // option code = 0 (PAD)
        // Container option starts here.
        0xc8,                         // option code = 200 (container)
        0x0b,                         // option length = 11
        // Suboption 0.
        0x00, 0x01, 0x00,             // code = 0, length = 1, content = 0
        // Suboption 255.
        0xff, 0x01, 0xff,             // code = 255, length = 1, content = 255
        // Suboption 1.
        0x01, 0x03, 0x66, 0x6f, 0x6f, // code = 1, length = 2, content = "foo"
        // END
        0xff,
        // Extra bytes at tail.
        0x01, 0x02, 0x03, 0x04
    };

    // Parse options.
    OptionCollection options;
    list<uint16_t> deferred;
    size_t offset = 0;
    ASSERT_NO_THROW(offset = LibDHCP::unpackOptions4(buf, DHCP4_OPTION_SPACE,
                                                     options, deferred, false));

    // Returned offset should point to the END.
    EXPECT_EQ(0xff, buf[offset]);

    // There should be one top level option.
    ASSERT_EQ(1, options.size());

    // Get it.
    OptionPtr option = options.begin()->second;
    ASSERT_TRUE(option);
    EXPECT_EQ(200, option->getType());

    // There should be 3 suboptions.
    ASSERT_EQ(3, option->getOptions().size());

    // Get suboption 0.
    boost::shared_ptr<OptionInt<uint8_t> > sub0 =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >
            (option->getOption(0));
    ASSERT_TRUE(sub0);
    EXPECT_EQ(0, sub0->getType());
    EXPECT_EQ(0, sub0->getValue());

    // Get suboption 255.
    boost::shared_ptr<OptionInt<uint8_t> > sub255 =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >
            (option->getOption(255));
    ASSERT_TRUE(sub255);
    EXPECT_EQ(255, sub255->getType());
    EXPECT_EQ(255, sub255->getValue());

    // Get suboption 1.
    boost::shared_ptr<OptionString> sub =
        boost::dynamic_pointer_cast<OptionString>(option->getOption(1));
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    EXPECT_EQ("foo", sub->getValue());
}

// Verifies that option 0 (PAD) is handled as PAD in option 43 (so when
// flexible pad end flag is true) only when option 0 (PAD) is not defined.
TEST_F(LibDhcpTest, option43Pad) {
    string space = "my-option43-space";

    // Create option definition for option 1.
    OptionDefinitionPtr opt_def1(new OptionDefinition("one", 1, space, "binary"));

    // Create option definition for option 2.
    OptionDefinitionPtr opt_def2(new OptionDefinition("two", 2, space, "uint8"));

    // Register created option definitions as runtime option definitions.
    OptionDefSpaceContainer defs;
    ASSERT_NO_THROW(defs.addItem(opt_def1));
    ASSERT_NO_THROW(defs.addItem(opt_def2));
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    // Create the buffer holding an option 43 content.
    OptionBuffer buf = {
        // Suboption 0,
        0x00, 0x01, 0x00,             // code = 0, length = 1, content = 0
                                      // or option code = 0 (PAD) followed by
                                      // code = 1, length = 0
        // Suboption 2.
        0x02, 0x01, 0x01,             // code = 2, length = 1, content = 1
    };

    // Parse options.
    OptionCollection options;
    list<uint16_t> deferred;
    ASSERT_NO_THROW(LibDHCP::unpackOptions4(buf, space, options, deferred, true));

    // There should be 2 suboptions (1 and 2) because no sub-option 0
    // was defined so code 0 means PAD.
    ASSERT_EQ(2, options.size());

    // Get suboption 1.
    OptionPtr sub1 = options.begin()->second;
    ASSERT_TRUE(sub1);
    EXPECT_EQ(1, sub1->getType());
    EXPECT_EQ(0, sub1->len() - sub1->getHeaderLen());

    // Get suboption 2.
    boost::shared_ptr<OptionInt<uint8_t> > sub2 =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >
            (options.rbegin()->second);
    ASSERT_TRUE(sub2);
    EXPECT_EQ(2, sub2->getType());
    EXPECT_EQ(1, sub2->getValue());

    // Create option definition for option 0 and register it.
    OptionDefinitionPtr opt_def0(new OptionDefinition("zero", 0, space, "uint8"));
    ASSERT_NO_THROW(defs.addItem(opt_def0));
    LibDHCP::clearRuntimeOptionDefs();
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    options.clear();
    ASSERT_NO_THROW(LibDHCP::unpackOptions4(buf, space, options, deferred, true));

    // There should be 2 suboptions (0 and 1).
    EXPECT_EQ(2, options.size());

    // Get suboption 0
    boost::shared_ptr<OptionInt<uint8_t> > sub0 =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >
            (options.begin()->second);
    ASSERT_TRUE(sub0);
    EXPECT_EQ(0, sub0->getType());
    EXPECT_EQ(0, sub0->getValue());

    // Get suboption 2.
    sub2 =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >
            (options.rbegin()->second);
    ASSERT_TRUE(sub2);
    EXPECT_EQ(2, sub2->getType());
    EXPECT_EQ(1, sub2->getValue());
}

// Verifies that option 255 (END) is handled as END in option 43 (so when
//flexible pad end flag is true) only when option 255 (END) is not defined.
TEST_F(LibDhcpTest, option43End) {
    string space = "my-option43-space";

    // Create the buffer holding an option 43 content.
    OptionBuffer buf = {
        // Suboption 255,
        0xff, 0x01, 0x02              // code = 255, length = 1, content = 2
    };

    // Parse options.
    OptionCollection options;
    list<uint16_t> deferred;
    size_t offset = 0;
    ASSERT_NO_THROW(offset = LibDHCP::unpackOptions4(buf, space,
                                                     options, deferred, true));

    // Parsing should stop at the first byte.
    EXPECT_EQ(0, offset);

    // There should be 0 suboptions.
    EXPECT_EQ(0, options.size());


    // Create option definition for option 255.
    OptionDefinitionPtr opt_def255(new OptionDefinition("max", 255, space, "uint8"));

    // Register created option definition as runtime option definitions.
    OptionDefSpaceContainer defs;
    ASSERT_NO_THROW(defs.addItem(opt_def255));
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    options.clear();
    offset = 0;
    ASSERT_NO_THROW(offset = LibDHCP::unpackOptions4(buf, space,
                                                     options, deferred, true));

    // There should be 1 suboption.
    ASSERT_EQ(1, options.size());

    // Get suboption 255.
    boost::shared_ptr<OptionInt<uint8_t> > sub255 =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >
            (options.begin()->second);
    ASSERT_TRUE(sub255);
    EXPECT_EQ(255, sub255->getType());
    EXPECT_EQ(2, sub255->getValue());
}

// Verify the option 43 END bug is fixed (#950: option code 255 was not
// parse at END, now it is not parse at END only when an option code 255
// is defined in the corresponding option space).
TEST_F(LibDhcpTest, option43Factory) {
    // Create the buffer holding the structure of option 43 content.
    OptionBuffer buf = {
        // Suboption 1.
        0x01, 0x00,                     // option code = 1, option length = 0
        // END
        0xff
    };

    // Get last resort definition.
    OptionDefinitionPtr def =
        LibDHCP::getLastResortOptionDef(DHCP4_OPTION_SPACE, 43);
    ASSERT_TRUE(def);

    // Apply the definition.
    OptionPtr option;
    ASSERT_NO_THROW(option = def->optionFactory(Option::V4, 43, buf));
    ASSERT_TRUE(option);
    EXPECT_EQ(DHO_VENDOR_ENCAPSULATED_OPTIONS, option->getType());
    EXPECT_EQ(def->getEncapsulatedSpace(), option->getEncapsulatedSpace());

    // There should be 1 suboption.
    EXPECT_EQ(1, option->getOptions().size());

    // Get suboption 1.
    OptionPtr sub1 = option->getOption(1);
    ASSERT_TRUE(sub1);
    EXPECT_EQ(1, sub1->getType());
    EXPECT_EQ(0, sub1->len() - sub1->getHeaderLen());

    // Of course no suboption 255.
    EXPECT_FALSE(option->getOption(255));
}

// Verifies that an Host Name (option 12), will be dropped when empty,
// while subsequent options will still be unpacked.
TEST_F(LibDhcpTest, emptyHostName) {

    uint8_t opts[] = {
        12,  0,             // Empty Hostname
        60,  3, 10, 11, 12  // Class Id
    };

    vector<uint8_t> packed(opts, opts + sizeof(opts));
    isc::dhcp::OptionCollection options; // list of options
    list<uint16_t> deferred;

    ASSERT_NO_THROW(
        LibDHCP::unpackOptions4(packed, DHCP4_OPTION_SPACE, options, deferred, false);
    );

    // Host Name should not exist, we quietly drop it when empty.
    isc::dhcp::OptionCollection::const_iterator x = options.find(12);
    ASSERT_TRUE(x == options.end());

    // Verify Option 60 exists correctly
    x = options.find(60);
    ASSERT_FALSE(x == options.end());
    EXPECT_EQ(60, x->second->getType());
    ASSERT_EQ(3, x->second->getData().size());
    EXPECT_EQ(5, x->second->len());
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], opts + 4, 3));
};


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

    LibDhcpTest::testStdOptionDefs4(DHO_NISP_DOMAIN_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_NISP_SERVER_ADDR, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_TFTP_SERVER_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_BOOT_FILE_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_HOME_AGENT_ADDRS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_SMTP_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_POP3_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_NNTP_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_WWW_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_FINGER_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_IRC_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_STREETTALK_SERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_STDASERVER, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_USER_CLASS, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs4(DHO_DIRECTORY_AGENT, begin, begin + 5,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_DIRECTORY_AGENT, begin, begin + 9,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_DIRECTORY_AGENT, begin, begin + 45,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_SERVICE_SCOPE, begin, end,
                                    typeid(Option4SlpServiceScope));

    // Check also with empty scope list
    LibDhcpTest::testStdOptionDefs4(DHO_SERVICE_SCOPE, begin, begin + 1,
                                    typeid(Option4SlpServiceScope));

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

    LibDhcpTest::testStdOptionDefs4(DHO_NDS_SERVERS, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_NDS_TREE_NAME, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_NDS_CONTEXT, begin, end,
                                    typeid(OptionString));

    // Prepare buffer holding an array of FQDNs.
    const char fqdn_data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0
    };
    // Initialize a vector with the FQDN data.
    std::vector<uint8_t> fqdn_buf(fqdn_data, fqdn_data + sizeof(fqdn_data));

    LibDhcpTest::testStdOptionDefs4(DHO_BCMCS_DOMAIN_NAME_LIST,
                                    fqdn_buf.begin(),
                                    fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_BCMCS_IPV4_ADDR, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_AUTHENTICATE, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs4(DHO_CLIENT_LAST_TRANSACTION_TIME,
                                    begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_ASSOCIATED_IP, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_AUTO_CONFIG, begin, begin + 1,
                                    typeid(OptionInt<uint8_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_NAME_SERVICE_SEARCH, begin, begin + 4,
                                    typeid(OptionIntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_SUBNET_SELECTION, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_SYSTEM, begin, end,
                                    typeid(OptionIntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_NDI, begin, begin + 3,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_UUID_GUID, begin, begin + 17,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_USER_AUTH, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_GEOCONF_CIVIC, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs4(DHO_PCODE, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_TCODE, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_V6_ONLY_PREFERRED, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs4(DHO_NETINFO_ADDR, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_NETINFO_TAG, begin, end,
                                    typeid(OptionString));

    /* Option 114 URL (RFC 3679) was retired and replaced with CAPTIVE_PORTAL (RFC8910)
       which was previously 160, but was reassigned (compare RFC7710 and RFC8910) */

    LibDhcpTest::testStdOptionDefs4(DHO_V4_CAPTIVE_PORTAL, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_SEARCH, fqdn_buf.begin(),
                                    fqdn_buf.end(), typeid(OptionCustom));

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

    LibDhcpTest::testStdOptionDefs4(DHO_PANA_AGENT, begin, end,
                                    typeid(Option4AddrLst));

    // Prepare buffer holding one FQDN.
    const char fqdn1_data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0
    };
    // Initialize a vector with the FQDN data.
    std::vector<uint8_t> fqdn1_buf(fqdn1_data,
                                   fqdn1_data + sizeof(fqdn1_data));

    LibDhcpTest::testStdOptionDefs4(DHO_V4_LOST, fqdn1_buf.begin(),
                                    fqdn1_buf.end(), typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_CAPWAP_AC_V4, begin, end,
                                    typeid(Option4AddrLst));

    LibDhcpTest::testStdOptionDefs4(DHO_SIP_UA_CONF_SERVICE_DOMAINS,
                                    fqdn_buf.begin(),
                                    fqdn_buf.end(),
                                    typeid(OptionCustom));

    std::vector<uint8_t> rdnss1_buf(begin, begin + 9);
    rdnss1_buf.insert(rdnss1_buf.end(), fqdn1_buf.begin(), fqdn1_buf.end());

    LibDhcpTest::testStdOptionDefs4(DHO_RDNSS_SELECT, rdnss1_buf.begin(),
                                    rdnss1_buf.end(),
                                    typeid(OptionCustom));

    std::vector<uint8_t> rdnss_buf(begin, begin + 9);
    rdnss_buf.insert(rdnss_buf.end(), fqdn_buf.begin(), fqdn_buf.end());

    LibDhcpTest::testStdOptionDefs4(DHO_RDNSS_SELECT, rdnss_buf.begin(),
                                    rdnss_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_V4_PORTPARAMS, begin, begin + 4,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_6RD, begin, begin + 22,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_6RD, begin, begin + 46,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs4(DHO_V4_ACCESS_DOMAIN, fqdn1_buf.begin(),
                                    fqdn1_buf.end(), typeid(OptionCustom));
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

    // Prepare buffer holding one FQDN.
    const char data1[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0
    };
    // Initialize a vector with the FQDN data1.
    std::vector<uint8_t> fqdn1_buf(data1, data1 + sizeof(data1));

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

    // Initialize test buffer for Bootfile Param option.
    const char bparam_data[] = {
        0x00, 0x01, 0x02
    };
    std::vector<uint8_t> bparam_buf(bparam_data,
                                    bparam_data + sizeof(bparam_data));;

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

    LibDhcpTest::testStdOptionDefs6(D6O_AUTH, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_UNICAST, begin, begin + 16,
                                    typeid(OptionCustom));

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
                                    typeid(OptionVendor));

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
                                    typeid(OptionCustom), DHCP6_OPTION_SPACE);

    LibDhcpTest::testStdOptionDefs6(D6O_CLIENT_DATA, begin, end,
                                    typeid(OptionCustom), DHCP6_OPTION_SPACE);

    LibDhcpTest::testStdOptionDefs6(D6O_CLT_TIME, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_RELAY_DATA, begin, end,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_LQ_CLIENT_LINK, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_V6_LOST,
                                    fqdn1_buf.begin(), fqdn1_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_CAPWAP_AC_V6, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_RELAY_ID, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_V6_ACCESS_DOMAIN,
                                    fqdn1_buf.begin(), fqdn1_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SIP_UA_CS_LIST,
                                    fqdn_buf.begin(), fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_BOOTFILE_URL, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs6(D6O_BOOTFILE_PARAM, bparam_buf.begin(),
                                    bparam_buf.end(),
                                    typeid(OptionOpaqueDataTuples));

    LibDhcpTest::testStdOptionDefs6(D6O_CLIENT_ARCH_TYPE, begin, end,
                                    typeid(OptionIntArray<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_NII, begin, begin + 3,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_AFTR_NAME, fqdn1_buf.begin(),
                                    fqdn1_buf.end(), typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_ERP_LOCAL_DOMAIN_NAME,
                                    fqdn_buf.begin(), fqdn_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_RSOO, begin, end,
                                    typeid(OptionCustom),
                                    "rsoo-opts");

    LibDhcpTest::testStdOptionDefs6(D6O_PD_EXCLUDE, begin, end,
                                    typeid(Option6PDExclude));

    std::vector<uint8_t> rdnss1_buf(begin, begin + 17);
    rdnss1_buf.insert(rdnss1_buf.end(), fqdn1_buf.begin(), fqdn1_buf.end());

    LibDhcpTest::testStdOptionDefs6(D6O_RDNSS_SELECTION, rdnss1_buf.begin(),
                                    rdnss1_buf.end(),
                                    typeid(OptionCustom));

    std::vector<uint8_t> rdnss_buf(begin, begin + 17);
    rdnss_buf.insert(rdnss_buf.end(), fqdn_buf.begin(), fqdn_buf.end());

    LibDhcpTest::testStdOptionDefs6(D6O_RDNSS_SELECTION, rdnss_buf.begin(),
                                    rdnss_buf.end(),
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_CLIENT_LINKLAYER_ADDR, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_LINK_ADDRESS, begin, begin + 16,
                                    typeid(OptionCustom));

    LibDhcpTest::testStdOptionDefs6(D6O_SOL_MAX_RT, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_INF_MAX_RT, begin, begin + 4,
                                    typeid(OptionInt<uint32_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_DHCPV4_MSG, begin, end,
                                    typeid(Option));

    LibDhcpTest::testStdOptionDefs6(D6O_DHCPV4_O_DHCPV6_SERVER, begin, end,
                                    typeid(Option6AddrLst));

    LibDhcpTest::testStdOptionDefs6(D6O_V6_CAPTIVE_PORTAL, begin, end,
                                    typeid(OptionString));

    LibDhcpTest::testStdOptionDefs6(D6O_RELAY_SOURCE_PORT, begin, begin + 2,
                                    typeid(OptionInt<uint16_t>));

    LibDhcpTest::testStdOptionDefs6(D6O_IPV6_ADDRESS_ANDSF, begin, end,
                                    typeid(Option6AddrLst));

    // RFC7598 options
    LibDhcpTest::testOptionDefs6(MAPE_V6_OPTION_SPACE, D6O_S46_RULE, begin, end,
                                 typeid(OptionCustom), V4V6_RULE_OPTION_SPACE);
    LibDhcpTest::testOptionDefs6(MAPT_V6_OPTION_SPACE, D6O_S46_RULE, begin, end,
                                 typeid(OptionCustom), V4V6_RULE_OPTION_SPACE);
    LibDhcpTest::testOptionDefs6(MAPE_V6_OPTION_SPACE, D6O_S46_BR, begin, end,
                                 typeid(OptionCustom));
    LibDhcpTest::testOptionDefs6(LW_V6_OPTION_SPACE, D6O_S46_BR, begin, end,
                                 typeid(OptionCustom));
    LibDhcpTest::testOptionDefs6(MAPT_V6_OPTION_SPACE, D6O_S46_DMR, begin, end,
                                 typeid(OptionCustom));
    LibDhcpTest::testOptionDefs6(LW_V6_OPTION_SPACE, D6O_S46_V4V6BIND, begin,
                                 end, typeid(OptionCustom),
                                 V4V6_BIND_OPTION_SPACE);
    LibDhcpTest::testOptionDefs6(V4V6_RULE_OPTION_SPACE, D6O_S46_PORTPARAMS,
                                 begin, end, typeid(OptionCustom), "");
    LibDhcpTest::testStdOptionDefs6(D6O_S46_CONT_MAPE, begin, end,
                                    typeid(OptionCustom),
                                    MAPE_V6_OPTION_SPACE);
    LibDhcpTest::testStdOptionDefs6(D6O_S46_CONT_MAPT, begin, end,
                                    typeid(OptionCustom),
                                    MAPT_V6_OPTION_SPACE);
    LibDhcpTest::testStdOptionDefs6(D6O_S46_CONT_LW, begin, end,
                                    typeid(OptionCustom),
                                    LW_V6_OPTION_SPACE);

}

// This test checks if the DHCPv6 option definition can be searched by
// an option name.
TEST_F(LibDhcpTest, getOptionDefByName6) {
    // Get all definitions.
    const OptionDefContainerPtr defs = LibDHCP::getOptionDefs(DHCP6_OPTION_SPACE);
    // For each definition try to find it using option name.
    for (OptionDefContainer::const_iterator def = defs->begin();
         def != defs->end(); ++def) {
        OptionDefinitionPtr def_by_name =
            LibDHCP::getOptionDef(DHCP6_OPTION_SPACE, (*def)->getName());
        ASSERT_TRUE(def_by_name);
        ASSERT_TRUE(**def == *def_by_name);
    }
}


// This test checks if the DHCPv4 option definition can be searched by
// an option name.
TEST_F(LibDhcpTest, getOptionDefByName4) {
    // Get all definitions.
    const OptionDefContainerPtr defs = LibDHCP::getOptionDefs(DHCP4_OPTION_SPACE);
    // For each definition try to find it using option name.
    for (OptionDefContainer::const_iterator def = defs->begin();
         def != defs->end(); ++def) {
        OptionDefinitionPtr def_by_name =
            LibDHCP::getOptionDef(DHCP4_OPTION_SPACE, (*def)->getName());
        ASSERT_TRUE(def_by_name);
        ASSERT_TRUE(**def == *def_by_name);
    }
}

// This test checks if the definition of the DHCPv6 vendor option can
// be searched by option name.
TEST_F(LibDhcpTest, getVendorOptionDefByName6) {
    const OptionDefContainerPtr& defs =
        LibDHCP::getVendorOptionDefs(Option::V6, VENDOR_ID_CABLE_LABS);
    ASSERT_TRUE(defs);
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
    const OptionDefContainerPtr& defs =
        LibDHCP::getVendorOptionDefs(Option::V4, VENDOR_ID_CABLE_LABS);
    ASSERT_TRUE(defs);
    for (OptionDefContainer::const_iterator def = defs->begin();
         def != defs->end(); ++def) {
        OptionDefinitionPtr def_by_name =
            LibDHCP::getVendorOptionDef(Option::V4, VENDOR_ID_CABLE_LABS,
                                        (*def)->getName());
        ASSERT_TRUE(def_by_name);
        ASSERT_TRUE(**def == *def_by_name);
    }
}

// This test checks handling of uncompressed FQDN list.
TEST_F(LibDhcpTest, fqdnList) {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                    DHO_DOMAIN_SEARCH);
    ASSERT_TRUE(def);

    // Prepare buffer holding an array of FQDNs.
    const uint8_t fqdn[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
        3, 99, 111, 109,                          // "com"
        0
    };
    /* This size is used later so protect ourselves against changes */
    static_assert(sizeof(fqdn) == 40,
                  "incorrect uncompressed domain list size");
    // Initialize a vector with the FQDN data.
    std::vector<uint8_t> fqdn_buf(fqdn, fqdn + sizeof(fqdn));

    OptionPtr option;
    ASSERT_NO_THROW(option = def->optionFactory(Option::V4,
                                                DHO_DOMAIN_SEARCH,
                                                fqdn_buf.begin(),
                                                fqdn_buf.end()));
    ASSERT_TRUE(option);
    OptionCustomPtr names = boost::dynamic_pointer_cast<OptionCustom>(option);
    ASSERT_TRUE(names);
    EXPECT_EQ(sizeof(fqdn), names->len() - names->getHeaderLen());
    ASSERT_EQ(3, names->getDataFieldsNum());
    EXPECT_EQ("mydomain.example.com.", names->readFqdn(0));
    EXPECT_EQ("example.com.", names->readFqdn(1));
    EXPECT_EQ("com.", names->readFqdn(2));

    LibDhcpTest::testStdOptionDefs4(DHO_DOMAIN_SEARCH, fqdn_buf.begin(),
                                    fqdn_buf.end(), typeid(OptionCustom));
}

// This test checks handling of compressed FQDN list.
// See RFC3397, section 2 (and 4.1.4 of RFC1035 for the actual
// compression algorithm).
TEST_F(LibDhcpTest, fqdnListCompressed) {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                    DHO_DOMAIN_SEARCH);
    ASSERT_TRUE(def);

    const uint8_t compressed[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
        192, 9,                                   // pointer to example.com
        192, 17                                   // pointer to com
    };
    std::vector<uint8_t> compressed_buf(compressed,
                                        compressed + sizeof(compressed));
    OptionPtr option;
    ASSERT_NO_THROW(option = def->optionFactory(Option::V4,
                                                DHO_DOMAIN_SEARCH,
                                                compressed_buf.begin(),
                                                compressed_buf.end()));
    ASSERT_TRUE(option);
    OptionCustomPtr names = boost::dynamic_pointer_cast<OptionCustom>(option);
    ASSERT_TRUE(names);
    /* Use the uncompress length here (cf fqdnList) */
    EXPECT_EQ(40, names->len() - names->getHeaderLen());
    ASSERT_EQ(3, names->getDataFieldsNum());
    EXPECT_EQ("mydomain.example.com.", names->readFqdn(0));
    EXPECT_EQ("example.com.", names->readFqdn(1));
    EXPECT_EQ("com.", names->readFqdn(2));
}

// Check that incorrect FQDN list compression is rejected.
// See RFC3397, section 2 (and 4.1.4 of RFC1035 for the actual
// compression algorithm).
TEST_F(LibDhcpTest, fqdnListBad) {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                    DHO_DOMAIN_SEARCH);
    ASSERT_TRUE(def);

    const uint8_t bad[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
        192, 80,                                  // too big/forward pointer
        192, 11                                   // pointer to com
    };
    std::vector<uint8_t> bad_buf(bad, bad + sizeof(bad));

    OptionPtr option;
    EXPECT_THROW(option = def->optionFactory(Option::V4,
                                             DHO_DOMAIN_SEARCH,
                                             bad_buf.begin(),
                                             bad_buf.end()),
                 InvalidOptionValue);
}

// Check that empty (truncated) option is rejected.
TEST_F(LibDhcpTest, fqdnListTrunc) {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                    DHO_DOMAIN_SEARCH);
    ASSERT_TRUE(def);

    std::vector<uint8_t> empty;

    OptionPtr option;
    EXPECT_THROW(option = def->optionFactory(Option::V4,
                                             DHO_DOMAIN_SEARCH,
                                             empty.begin(),
                                             empty.end()),
                 InvalidOptionValue);
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
            LibDHCP::unpackOptions6(bin, DHCP6_OPTION_SPACE, options);
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

// This test verifies that it is possible to add runtime option definitions,
// retrieve them and remove them.
TEST_F(LibDhcpTest, setRuntimeOptionDefs) {
    // Create option definitions in 5 namespaces.
    OptionDefSpaceContainer defs;
    createRuntimeOptionDefs(5, 100, defs);

    // Apply option definitions.
    ASSERT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    // Retrieve all inserted option definitions.
    testRuntimeOptionDefs(5, 100, true);

    // Attempting to retrieve non existing definitions.
    EXPECT_FALSE(LibDHCP::getRuntimeOptionDef("option-space-non-existent", 1));
    EXPECT_FALSE(LibDHCP::getRuntimeOptionDef("option-space-0", 145));

    // Remove all runtime option definitions.
    ASSERT_NO_THROW(LibDHCP::clearRuntimeOptionDefs());

    // All option definitions should be gone now.
    testRuntimeOptionDefs(5, 100, false);
}

// This test verifies the processing of option 43
TEST_F(LibDhcpTest, option43) {
    // Check shouldDeferOptionUnpack()
    EXPECT_TRUE(LibDHCP::shouldDeferOptionUnpack(DHCP4_OPTION_SPACE, 43));
    EXPECT_FALSE(LibDHCP::shouldDeferOptionUnpack(DHCP4_OPTION_SPACE, 44));
    EXPECT_FALSE(LibDHCP::shouldDeferOptionUnpack(DHCP6_OPTION_SPACE, 43));

    // Check last resort
    OptionDefinitionPtr def;
    def = LibDHCP::getLastResortOptionDef(DHCP6_OPTION_SPACE, 43);
    EXPECT_FALSE(def);
    def = LibDHCP::getLastResortOptionDef(DHCP4_OPTION_SPACE, 44);
    EXPECT_FALSE(def);
    def = LibDHCP::getLastResortOptionDef(DHCP4_OPTION_SPACE, 43);
    ASSERT_TRUE(def);
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ(43, def->getCode());
    EXPECT_EQ(VENDOR_ENCAPSULATED_OPTION_SPACE, def->getEncapsulatedSpace());
    EXPECT_EQ("vendor-encapsulated-options", def->getName());
    EXPECT_EQ(0, def->getRecordFields().size());
    EXPECT_EQ(OptionDataType::OPT_EMPTY_TYPE, def->getType());

    OptionDefinitionPtr def_by_name =
        LibDHCP::getLastResortOptionDef(DHCP4_OPTION_SPACE,
                                        "vendor-encapsulated-options");
    EXPECT_TRUE(def_by_name);
    EXPECT_EQ(def, def_by_name);
}

// RFC7598 defines several options for configuration of lw4over6 devices.
// These options are have complex structure, so dedicated tests are needed
// to test them reliably.
TEST_F(LibDhcpTest, sw46options) {


    // This constant defines the following structure:
    // MAP-E container
    //  - BR address option
    //  - S46 rule option
    //    - portparameters
    //  - S46 rule option
    std::vector<uint8_t> mape_bin = {
        0, 94, 0, 64,  // MAP-E container with 3 suboptions

        0, 90, 0, 16,                    // BR address
        0x20, 0x01, 0xd, 0xb8, 0, 0, 0, 0, // 2001:db8::abcd
        0, 0, 0, 0, 0, 0, 0xab, 0xcd,

        0, 89, 0, 16+8, // S46 rule
        128, // flags = 128 (F flag set)
        4, // ea-len
        30, // prefix4-len
        192, 0, 2, 192, // ipv4-prefix = 192.168.0.192
        64, // prefix6-len = /64
        0x20, 0x01, 0xd, 0xb8, 0, 1, 2, 3, // ipv6-prefix = 2001:db8::1:203::/64

        0, 93, 0, 4, // S46_PORTPARAMS option
        8, 6, 0xfc, 0x00, // offset is 8, psid-len 6, psid is fc00

        0, 89, 0, 12, // S46 rule
        0, // flags = 0 (F flag clear)
        6, // ea-len
        32, // prefix4-len
        192, 0, 2, 1, // ipv4-prefix = 192.168.0.1
        32, // prefix6-len = /32
        0x20, 0x01, 0xd, 0xb8 // ipv6-prefix = 2001:db8::/32
    };

    // List of parsed options will be stored here.
    isc::dhcp::OptionCollection options;

    OptionBuffer buf(mape_bin);

    size_t parsed = 0;

    EXPECT_NO_THROW (parsed = LibDHCP::unpackOptions6(buf, DHCP6_OPTION_SPACE, options));
    EXPECT_EQ(mape_bin.size(), parsed);

    // We expect to have exactly one option (with tons of suboptions, but we'll
    // get to that in a minute)
    EXPECT_EQ(1, options.size());
    auto opt = options.find(D6O_S46_CONT_MAPE);
    ASSERT_FALSE(opt == options.end());

    // Ok, let's iterate over the options. Start with the top one.
    using boost::shared_ptr;
    shared_ptr<OptionCustom> mape = dynamic_pointer_cast<OptionCustom>(opt->second);
    ASSERT_TRUE(mape);
    EXPECT_EQ(D6O_S46_CONT_MAPE, mape->getType());
    EXPECT_EQ(68, mape->len());
    EXPECT_EQ(64, mape->getData().size());

    // Let's check if there's a border router option.
    ASSERT_TRUE(mape->getOption(D6O_S46_BR));

    // Make sure the option is of proper type, not just plain Option
    shared_ptr<OptionCustom> br =
        dynamic_pointer_cast<OptionCustom>(mape->getOption(D6O_S46_BR));
    ASSERT_TRUE(br);
    EXPECT_EQ("type=00090, len=00016: 2001:db8::abcd (ipv6-address)", br->toText());

    // Now let's check the suboptions. There should be 3 (BR, 2x rule)
    const OptionCollection& subopts = mape->getOptions();
    ASSERT_EQ(3, subopts.size());
    EXPECT_EQ(1, subopts.count(D6O_S46_BR));
    EXPECT_EQ(2, subopts.count(D6O_S46_RULE));

    // Let's check the rules. There should be two of them.
    auto range = subopts.equal_range(D6O_S46_RULE);
    ASSERT_EQ(2, std::distance(range.first, range.second));
    OptionPtr opt1 = range.first->second;
    OptionPtr opt2 = (++range.first)->second;
    shared_ptr<OptionCustom> rule1 = dynamic_pointer_cast<OptionCustom>(opt1);
    shared_ptr<OptionCustom> rule2 = dynamic_pointer_cast<OptionCustom>(opt2);
    ASSERT_TRUE(rule1);
    ASSERT_TRUE(rule2);

    EXPECT_EQ("type=00089, len=00024: 128 (uint8) 4 (uint8) 30 (uint8) "
              "192.0.2.192 (ipv4-address)  (ipv6-prefix),\noptions:\n"
              "  type=00093, len=00004: 8 (uint8) len=6,psid=63 (psid)", rule1->toText());

    EXPECT_EQ("type=00089, len=00012: 0 (uint8) 6 (uint8) 32 (uint8) "
              "192.0.2.1 (ipv4-address)  (ipv6-prefix)", rule2->toText());

    // Finally, check that the subsuboption in the first rule is ok
    OptionPtr subsubopt = opt1->getOption(D6O_S46_PORTPARAMS);
    shared_ptr<OptionCustom> portparam = dynamic_pointer_cast<OptionCustom>(subsubopt);
    ASSERT_TRUE(portparam);

    EXPECT_EQ("type=00093, len=00004: 8 (uint8) len=6,psid=63 (psid)", portparam->toText());
}

}  // namespace
