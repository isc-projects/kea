// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_vendor.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option_int.h>
#include <stats/stats_mgr.h>
#include <algorithm>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace std;

namespace {

/// @brief Set of JSON configurations used throughout the classify tests.
///
/// - Configuration 0:
///   - Used for testing dynamic assignment of client classes
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - the following classes defined:
///     option[93].hex == 0x0009, next-server set to 1.2.3.4
///     option[93].hex == 0x0007, set server-hostname to deneb
///     option[93].hex == 0x0006, set boot-file-name to pxelinux.0
///     option[93].hex == 0x0001, set boot-file-name to ipxe.efi
///
/// - Configuration 1:
///   - Used for testing reservations of client classes for a client
///   - The following classes are defined:
///     - 'pxe', next-server set to 1.2.3.4, assigned dynamically
///     - 'reserved-class1', routers set to 10.0.0.200, reserved for a
///        host using HW address 'aa:bb:cc:dd:ee:ff'
///     - 'reserved-class2', domain-name-servers set to 10.0.0.201,
///        also reserved for the host using HW address
///        'aa:bb:cc:dd:ee:ff'
///   - Subnet of 10.0.0.0/24 with a single address pool
///
/// - Configuration 2:
///   - Used for testing client class combination
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - the following classes defined:
///     not (option[93].hex == 0x0009)
///     not member(<preceeding>), next-server set to 1.2.3.4
///     option[93].hex == 0x0006
///     option[93].hex == 0x0001
///     or member(<last two>), set boot-file-name to pxelinux.0
///
/// - Configuration 3:
///   - Used for required classification
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - the following classes defined:
///     option[93].hex == 0x0009, next-server set to 1.2.3.4
///     option[93].hex == 0x0007, set server-hostname to deneb
///     option[93].hex == 0x0006, set boot-file-name to pxelinux.0
///     option[93].hex == 0x0001, set boot-file-name to ipxe.efi
///
/// - Configuration 4:
///   - Used for complex membership (example taken from HA)
///   - 1 subnet: 10.0.0.0/24
///   - 4 pools: 10.0.0.10-10.0.0.49, 10.0.0.60-10.0.0.99,
///              10.0.0.110-10.0.0.149, 10.0.0.1.60-10.0.0.199
///   - 4 classes to compose:
///      server1 and server2 for each HA server
///      option[93].hex == 0x0009 aka telephones
///      option[93].hex == 0x0007 aka computers
///
/// - Configuration 5:
///   - Used for the DROP class
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - the following class defined: option[93].hex == 0x0009, DROP
///
/// - Configuration 6:
///   - Used for the DROP class and reservation existence.
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - 1 reservation for HW address 'aa:bb:cc:dd:ee:ff'
///   - the following class defined: not member('KNOWN'), DROP
///     (the not member also verifies that the DROP class is set only
///      after the host reservation lookup)
/// @note the reservation includes a hostname because raw reservations are
/// not yet allowed.
///
/// - Configuration 7:
///   - Used for the DROP class and reservation class.
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - 1 reservation for HW address 'aa:bb:cc:dd:ee:ff'
///     setting the allowed class
///   - the following classes defined:
///     - allowed
///     - member('KNOWN') or member('UNKNOWN'), t
///     - not member('allowed') and member('t'), DROP
///     The function of the always true 't' class is to move the DROP
///     evaluation to the classification point after the host reservation
///     lookup, i.e. indirect KNOWN / UNKNOWN dependency.
///
/// - Configuration 8:
///   - Used for the early global reservations lookup / select subnet.
///   - 2 subnets: 10.0.0.0/24 guarded by first and 10.0.1.0/24
///   - 2 pools: 10.0.0.10-10.0.0.100 and 10.0.1.10-10.0.1.100
///   - 1 global reservation for HW address 'aa:bb:cc:dd:ee:ff'
///     setting the first class
///   - the following class defined: first
///
/// - Configuration 9:
///   - Used for the early global reservations lookup / drop.
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - 1 reservation for HW address 'aa:bb:cc:dd:ee:ff'
///     setting the DROP class
///
const char* CONFIGS[] = {
    // Configuration 0
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"pxe1\","
        "   \"test\": \"option[93].hex == 0x0009\","
        "   \"next-server\": \"1.2.3.4\""
        "},"
        "{"
        "   \"name\": \"pxe2\","
        "   \"test\": \"option[93].hex == 0x0007\","
        "   \"server-hostname\": \"deneb\""
        "},"
        "{"
        "   \"name\": \"pxe3\","
        "   \"test\": \"option[93].hex == 0x0006\","
        "   \"boot-file-name\": \"pxelinux.0\""
        "},"
        "{"
        "   \"name\": \"pxe4\","
        "   \"test\": \"option[93].hex == 0x0001\","
        "   \"boot-file-name\": \"ipxe.efi\""
        "}],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ]"
        " } ]"
    "}",

    // Configuration 1
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"pxe\","
        "   \"test\": \"option[93].hex == 0x0009\","
        "   \"next-server\": \"1.2.3.4\""
        "},"
        "{"
        "   \"name\": \"reserved-class1\","
        "   \"option-data\": ["
        "   {"
        "       \"name\": \"routers\","
        "       \"data\": \"10.0.0.200\""
        "   }"
        "   ]"
        "},"
        "{"
        "   \"name\": \"reserved-class2\","
        "   \"option-data\": ["
        "   {"
        "       \"name\": \"domain-name-servers\","
        "       \"data\": \"10.0.0.201\""
        "   }"
        "   ]"
        "}"
        "],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"reservations\": [ "
        "    {"
        "        \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "        \"client-classes\": [ \"reserved-class1\", \"reserved-class2\" ]"
        "    }"
        "    ]"
        " } ]"
    "}",

    // Configuration 2
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"not-pxe1\","
        "   \"test\": \"not (option[93].hex == 0x0009)\""
        "},"
        "{"
        "   \"name\": \"pxe1\","
        "   \"test\": \"not member('not-pxe1')\","
        "   \"next-server\": \"1.2.3.4\""
        "},"
        "{"
        "   \"name\": \"pxe3\","
        "   \"test\": \"option[93].hex == 0x0006\""
        "},"
        "{"
        "   \"name\": \"pxe4\","
        "   \"test\": \"option[93].hex == 0x0001\""
        "},"
        "{"
        "   \"name\": \"pxe34\","
        "   \"test\": \"member('pxe3') or member('pxe4')\","
        "   \"boot-file-name\": \"pxelinux.0\""
        "}],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ]"
        " } ]"
    "}",

    // Configuration 3
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"pxe1\","
        "   \"test\": \"option[93].hex == 0x0009\","
        "   \"only-in-additional-list\": true,"
        "   \"next-server\": \"1.2.3.4\""
        "},"
        "{"
        "   \"name\": \"pxe2\","
        "   \"test\": \"option[93].hex == 0x0007\","
        "   \"only-in-additional-list\": true,"
        "   \"server-hostname\": \"deneb\""
        "},"
        "{"
        "   \"name\": \"pxe3\","
        "   \"test\": \"option[93].hex == 0x0006\","
        "   \"only-in-additional-list\": false,"
        "   \"boot-file-name\": \"pxelinux.0\""
        "},"
        "{"
        "   \"name\": \"pxe4\","
        "   \"test\": \"option[93].hex == 0x0001\","
        "   \"boot-file-name\": \"ipxe.efi\""
        "}],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"evaluate-additional-classes\": [ \"pxe2\" ]"
        " } ]"
    "}",

    // Configuration 4
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"server1\""
        "},"
        "{"
        "   \"name\": \"server2\""
        "},"
        "{"
        "   \"name\": \"telephones\","
        "   \"test\": \"option[93].hex == 0x0009\""
        "},"
        "{"
        "   \"name\": \"computers\","
        "   \"test\": \"option[93].hex == 0x0007\""
        "},"
        "{"
        "   \"name\": \"server1_and_telephones\","
        "   \"test\": \"member('server1') and member('telephones')\""
        "},"
        "{"
        "   \"name\": \"server1_and_computers\","
        "   \"test\": \"member('server1') and member('computers')\""
        "},"
        "{"
        "   \"name\": \"server2_and_telephones\","
        "   \"test\": \"member('server2') and member('telephones')\""
        "},"
        "{"
        "   \"name\": \"server2_and_computers\","
        "   \"test\": \"member('server2') and member('computers')\""
        "} ],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ "
        "        { \"pool\": \"10.0.0.10-10.0.0.49\","
        "          \"client-classes\": [ \"server1_and_telephones\" ] },"
        "        { \"pool\": \"10.0.0.60-10.0.0.99\","
        "          \"client-classes\": [ \"server1_and_computers\" ] },"
        "        { \"pool\": \"10.0.0.110-10.0.0.149\","
        "          \"client-classes\": [ \"server2_and_telephones\" ] },"
        "        { \"pool\": \"10.0.0.160-10.0.0.199\","
        "          \"client-classes\": [ \"server2_and_computers\" ] } ]"
        " } ]"
    "}",

    // Configuration 5
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"DROP\","
        "   \"test\": \"option[93].hex == 0x0009\""
        "}],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ]"
        " } ]"
    "}",

    // Configuration 6
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"DROP\","
        "   \"test\": \"not member('KNOWN')\""
        "}],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"reservations\": [ {"
        "        \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "        \"hostname\": \"allowed\" } ]"
        " } ]"
    "}",

    // Configuration 7
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"allowed\""
        "},"
        "{"
        "   \"name\": \"t\","
        "   \"test\": \"member('KNOWN') or member('UNKNOWN')\""
        "},"
        "{"
        "   \"name\": \"DROP\","
        "   \"test\": \"not member('allowed') and member('t')\""
        "}],"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"reservations\": [ {"
        "        \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "        \"client-classes\": [ \"allowed\" ] } ]"
        " } ]"
    "}",

    // Configuration 8
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"early-global-reservations-lookup\": true,"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"first\""
        "}],"
        "\"subnet4\": ["
        "{"
        "    \"subnet\": \"10.0.0.0/24\","
        "    \"id\": 1,"
        "    \"interface\": \"eth0\","
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"client-class\": \"first\""
        "},"
        "{"
        "    \"subnet\": \"10.0.1.0/24\","
        "    \"interface\": \"eth0\","
        "    \"id\": 2,"
        "    \"pools\": [ { \"pool\": \"10.0.1.10-10.0.1.100\" } ]"
        "}],"
        "\"reservations\": [ {"
        "    \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "    \"client-classes\": [ \"first\" ] } ]"
    "}",

    // Configuration 9
    "{ \"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"early-global-reservations-lookup\": true,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"interface\": \"eth0\","
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ] } ],"
        "\"reservations\": [ {"
        "    \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "    \"client-classes\": [ \"DROP\" ] } ]"
    "}",

};

/// @brief Test fixture class for testing classification.
///
/// For the time being it covers only fixed fields, but it's going to be
/// expanded to cover other cases.
class ClassifyTest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    ClassifyTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
    }

    /// @brief Destructor.
    ///
    ~ClassifyTest() {
    }

    /// @brief Does client exchanges and checks if fixed fields have expected values.
    ///
    /// Depending on the value of msgtype (allowed types: DHCPDISCOVER, DHCPREQUEST or
    /// DHCPINFORM), this method sets up the server, then conducts specified exchange
    /// and then checks if the response contains expected values of next-server, sname
    /// and filename fields.
    ///
    /// @param config server configuration to be used
    /// @param msgtype DHCPDISCOVER, DHCPREQUEST or DHCPINFORM
    /// @param extra_opt option to include in client messages (optional)
    /// @param exp_next_server expected value of the next-server field
    /// @param exp_sname expected value of the sname field
    /// @param exp_filename expected value of the filename field
    void
    testFixedFields(const char* config, uint8_t msgtype, const OptionPtr& extra_opt,
                    const std::string& exp_next_server, const std::string& exp_sname,
                    const std::string& exp_filename) {
         Dhcp4Client client(Dhcp4Client::SELECTING);

         // Configure DHCP server.
         configure(config, *client.getServer());

         if (extra_opt) {
             client.addExtraOption(extra_opt);
         }

         switch (msgtype) {
         case DHCPDISCOVER:
             client.doDiscover();
             break;
         case DHCPREQUEST:
             client.doDORA();
             break;
         case DHCPINFORM:
             // Preconfigure the client with the IP address.
             client.createLease(IOAddress("10.0.0.56"), 600);

             client.doInform(false);
             break;
         }

         ASSERT_TRUE(client.getContext().response_);
         Pkt4Ptr resp = client.getContext().response_;

         EXPECT_EQ(exp_next_server, resp->getSiaddr().toText());

         // This is bizarre. If I use Pkt4::MAX_SNAME_LEN in the ASSERT_GE macro,
         // the linker will complain about it being not defined.
         const size_t max_sname = Pkt4::MAX_SNAME_LEN;

         ASSERT_GE(max_sname, exp_sname.length());
         vector<uint8_t> sname(max_sname, 0);
         memcpy(&sname[0], &exp_sname[0], exp_sname.size());
         EXPECT_TRUE(std::equal(sname.begin(), sname.end(),
                                resp->getSname().begin()));

         const size_t max_filename = Pkt4::MAX_FILE_LEN;
         ASSERT_GE(max_filename, exp_filename.length());
         vector<uint8_t> filename(max_filename, 0);
         memcpy(&filename[0], &exp_filename[0], exp_filename.size());
         EXPECT_TRUE(std::equal(filename.begin(), filename.end(),
                                resp->getFile().begin()));
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// This test checks that an incoming DISCOVER that does not match any classes
// will get the fixed fields empty.
TEST_F(ClassifyTest, fixedFieldsDiscoverNoClasses) {
    testFixedFields(CONFIGS[0], DHCPDISCOVER, OptionPtr(), "0.0.0.0", "", "");
}
// This test checks that an incoming REQUEST that does not match any classes
// will get the fixed fields empty.
TEST_F(ClassifyTest, fixedFieldsRequestNoClasses) {
    testFixedFields(CONFIGS[0], DHCPREQUEST, OptionPtr(), "0.0.0.0", "", "");
}
// This test checks that an incoming INFORM that does not match any classes
// will get the fixed fields empty.
TEST_F(ClassifyTest, fixedFieldsInformNoClasses) {
    testFixedFields(CONFIGS[0], DHCPINFORM, OptionPtr(), "0.0.0.0", "", "");
}

// This test checks that an incoming DISCOVER that does match a class that has
// next-server specified will result in a response that has the next-server set.
TEST_F(ClassifyTest, fixedFieldsDiscoverNextServer) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[0], DHCPDISCOVER, pxe, "1.2.3.4", "", "");
}
// This test checks that an incoming REQUEST that does match a class that has
// next-server specified will result in a response that has the next-server set.
TEST_F(ClassifyTest, fixedFieldsRequestNextServer) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[0], DHCPREQUEST, pxe, "1.2.3.4", "", "");
}
// This test checks that an incoming INFORM that does match a class that has
// next-server specified will result in a response that has the next-server set.
TEST_F(ClassifyTest, fixedFieldsInformNextServer) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[0], DHCPINFORM, pxe, "1.2.3.4", "", "");
}

// This test checks that an incoming DISCOVER that does match a class that has
// server-hostname specified will result in a response that has the sname field set.
TEST_F(ClassifyTest, fixedFieldsDiscoverHostname) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));

    testFixedFields(CONFIGS[0], DHCPDISCOVER, pxe, "0.0.0.0", "deneb", "");
}
// This test checks that an incoming REQUEST that does match a class that has
// server-hostname specified will result in a response that has the sname field set.
TEST_F(ClassifyTest, fixedFieldsRequestHostname) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));

    testFixedFields(CONFIGS[0], DHCPREQUEST, pxe, "0.0.0.0", "deneb", "");
}
// This test checks that an incoming INFORM that does match a class that has
// server-hostname specified will result in a response that has the sname field set.
TEST_F(ClassifyTest, fixedFieldsInformHostname) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));

    testFixedFields(CONFIGS[0], DHCPINFORM, pxe, "0.0.0.0", "deneb", "");
}

// This test checks that an incoming DISCOVER that does match a class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsDiscoverFile1) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[0], DHCPDISCOVER, pxe, "0.0.0.0", "", "pxelinux.0");
}
// This test checks that an incoming REQUEST that does match a class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsRequestFile1) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[0], DHCPREQUEST, pxe, "0.0.0.0", "", "pxelinux.0");
}
// This test checks that an incoming INFORM that does match a class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsInformFile1) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[0], DHCPDISCOVER, pxe, "0.0.0.0", "", "pxelinux.0");
}

// This test checks that an incoming DISCOVER that does match a different class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsDiscoverFile2) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[0], DHCPDISCOVER, pxe, "0.0.0.0", "", "ipxe.efi");
}
// This test checks that an incoming REQUEST that does match a different class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsRequestFile2) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[0], DHCPREQUEST, pxe, "0.0.0.0", "", "ipxe.efi");
}
// This test checks that an incoming INFORM that does match a different class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsInformFile2) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[0], DHCPINFORM, pxe, "0.0.0.0", "", "ipxe.efi");
}

// This test checks that it is possible to specify static reservations for
// client classes.
TEST_F(ClassifyTest, clientClassesInHostReservations) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Initially, the client uses hardware address for which there are
    // no reservations.
    client.setHWAddress("aa:bb:cc:dd:ee:fe");
    // DNS servers have to be requested to be returned.
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

    // Add option 93 that matches 'pxe' class in the configuration.
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));
    client.addExtraOption(pxe);

    // Configure DHCP server.
    configure(CONFIGS[1], *client.getServer());

    // Perform 4-way exchange. The client's HW address doesn't match the
    // reservations, so we expect that only 'pxe' class will be matched.
    ASSERT_NO_THROW(client.doDORA());

    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;

    // 'pxe' class matches so the siaddr should be set appropriately.
    EXPECT_EQ("1.2.3.4", resp->getSiaddr().toText());
    // This client has no reservations for the classes associated with
    // DNS servers and Routers options.
    EXPECT_EQ(0, client.config_.routers_.size());
    EXPECT_EQ(0, client.config_.dns_servers_.size());

    // Modify HW address to match the reservations.
    client.setHWAddress("aa:bb:cc:dd:ee:ff");
    ASSERT_NO_THROW(client.doDORA());

    ASSERT_TRUE(client.getContext().response_);
    resp = client.getContext().response_;

    // This time, the client matches 3 classes (for two it has reservations).
    EXPECT_EQ("1.2.3.4", resp->getSiaddr().toText());
    EXPECT_EQ(1, client.config_.routers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.routers_[0].toText());
    EXPECT_EQ(1, client.config_.dns_servers_.size());
    EXPECT_EQ("10.0.0.201", client.config_.dns_servers_[0].toText());

    // This should also work for DHCPINFORM case.
    ASSERT_NO_THROW(client.doInform());
    ASSERT_TRUE(client.getContext().response_);
    resp = client.getContext().response_;

    EXPECT_EQ("1.2.3.4", resp->getSiaddr().toText());
    EXPECT_EQ(1, client.config_.routers_.size());
    EXPECT_EQ("10.0.0.200", client.config_.routers_[0].toText());
    EXPECT_EQ(1, client.config_.dns_servers_.size());
    EXPECT_EQ("10.0.0.201", client.config_.dns_servers_[0].toText());
}

// This test checks that an incoming DISCOVER that does not match any classes
// will get the fixed fields empty.
TEST_F(ClassifyTest, fixedFieldsDiscoverNoClasses2) {
    testFixedFields(CONFIGS[2], DHCPDISCOVER, OptionPtr(), "0.0.0.0", "", "");
}
// This test checks that an incoming REQUEST that does not match any classes
// will get the fixed fields empty.
TEST_F(ClassifyTest, fixedFieldsRequestNoClasses2) {
    testFixedFields(CONFIGS[2], DHCPREQUEST, OptionPtr(), "0.0.0.0", "", "");
}
// This test checks that an incoming INFORM that does not match any classes
// will get the fixed fields empty.
TEST_F(ClassifyTest, fixedFieldsInformNoClasses2) {
    testFixedFields(CONFIGS[2], DHCPINFORM, OptionPtr(), "0.0.0.0", "", "");
}

// This test checks that an incoming DISCOVER that does match a class that has
// next-server specified will result in a response that has the next-server set.
TEST_F(ClassifyTest, fixedFieldsDiscoverNextServer2) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[2], DHCPDISCOVER, pxe, "1.2.3.4", "", "");
}
// This test checks that an incoming REQUEST that does match a class that has
// next-server specified will result in a response that has the next-server set.
TEST_F(ClassifyTest, fixedFieldsRequestNextServer2) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[2], DHCPREQUEST, pxe, "1.2.3.4", "", "");
}
// This test checks that an incoming INFORM that does match a class that has
// next-server specified will result in a response that has the next-server set.
TEST_F(ClassifyTest, fixedFieldsInformNextServer2) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[2], DHCPINFORM, pxe, "1.2.3.4", "", "");
}

// This test checks that an incoming DISCOVER that does match a class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsDiscoverFile21) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[2], DHCPDISCOVER, pxe, "0.0.0.0", "", "pxelinux.0");
}
// This test checks that an incoming REQUEST that does match a class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsRequestFile21) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[2], DHCPREQUEST, pxe, "0.0.0.0", "", "pxelinux.0");
}
// This test checks that an incoming INFORM that does match a class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsInformFile21) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[2], DHCPDISCOVER, pxe, "0.0.0.0", "", "pxelinux.0");
}

// This test checks that an incoming DISCOVER that does match a different class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsDiscoverFile22) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[2], DHCPDISCOVER, pxe, "0.0.0.0", "", "pxelinux.0");
}
// This test checks that an incoming REQUEST that does match a different class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsRequestFile22) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[2], DHCPREQUEST, pxe, "0.0.0.0", "", "pxelinux.0");
}
// This test checks that an incoming INFORM that does match a different class that has
// boot-file-name specified will result in a response that has the filename field set.
TEST_F(ClassifyTest, fixedFieldsInformFile22) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[2], DHCPINFORM, pxe, "0.0.0.0", "", "pxelinux.0");
}

// No class
TEST_F(ClassifyTest, fixedFieldsDiscoverNoClasses3) {
    testFixedFields(CONFIGS[3], DHCPDISCOVER, OptionPtr(), "0.0.0.0", "", "");
}
TEST_F(ClassifyTest, fixedFieldsRequestNoClasses3) {
    testFixedFields(CONFIGS[3], DHCPREQUEST, OptionPtr(), "0.0.0.0", "", "");
}
TEST_F(ClassifyTest, fixedFieldsInformNoClasses3) {
    testFixedFields(CONFIGS[3], DHCPINFORM, OptionPtr(), "0.0.0.0", "", "");
}

// Class 'pxe1' is only-in-additional-list and not subject to additional evaluation
TEST_F(ClassifyTest, fixedFieldsDiscoverNextServer3) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[3], DHCPDISCOVER, pxe, "0.0.0.0", "", "");
}
TEST_F(ClassifyTest, fixedFieldsRequestNextServer3) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[3], DHCPREQUEST, pxe, "0.0.0.0", "", "");
}
TEST_F(ClassifyTest, fixedFieldsInformNextServer3) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));

    testFixedFields(CONFIGS[3], DHCPINFORM, pxe, "0.0.0.0", "", "");
}

// Class pxe2 is only-in-additional-list but the subnet requires its evaluation
TEST_F(ClassifyTest, fixedFieldsDiscoverHostname3) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));

    testFixedFields(CONFIGS[3], DHCPDISCOVER, pxe, "0.0.0.0", "deneb", "");
}
TEST_F(ClassifyTest, fixedFieldsRequestHostname3) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));

    testFixedFields(CONFIGS[3], DHCPREQUEST, pxe, "0.0.0.0", "deneb", "");
}
TEST_F(ClassifyTest, fixedFieldsInformHostname3) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));

    testFixedFields(CONFIGS[3], DHCPINFORM, pxe, "0.0.0.0", "deneb", "");
}

// No change from config #0 for pxe3 and pxe4
TEST_F(ClassifyTest, fixedFieldsDiscoverFile31) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[3], DHCPDISCOVER, pxe, "0.0.0.0", "", "pxelinux.0");
}
TEST_F(ClassifyTest, fixedFieldsRequestFile31) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[3], DHCPREQUEST, pxe, "0.0.0.0", "", "pxelinux.0");
}
TEST_F(ClassifyTest, fixedFieldsInformFile31) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0006));

    testFixedFields(CONFIGS[3], DHCPDISCOVER, pxe, "0.0.0.0", "", "pxelinux.0");
}
TEST_F(ClassifyTest, fixedFieldsDiscoverFile32) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[3], DHCPDISCOVER, pxe, "0.0.0.0", "", "ipxe.efi");
}
TEST_F(ClassifyTest, fixedFieldsRequestFile32) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[3], DHCPREQUEST, pxe, "0.0.0.0", "", "ipxe.efi");
}
TEST_F(ClassifyTest, fixedFieldsInformFile32) {
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0001));

    testFixedFields(CONFIGS[3], DHCPINFORM, pxe, "0.0.0.0", "", "ipxe.efi");
}

// This test checks the complex membership from HA with server1 telephone.
TEST_F(ClassifyTest, server1Telephone) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[4], *client.getServer());

    // Add option.
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));
    client.addExtraOption(pxe);

    // Add server1
    client.addClass("server1");

    // Get an address
    client.doDORA();

    // Check response.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the first pool.
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());
}

// This test checks the complex membership from HA with server1 computer.
TEST_F(ClassifyTest, server1computer) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[4], *client.getServer());

    // Add option.
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));
    client.addExtraOption(pxe);

    // Add server1
    client.addClass("server1");

    // Get an address
    client.doDORA();

    // Check response.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the second pool.
    EXPECT_EQ("10.0.0.60", resp->getYiaddr().toText());
}

// This test checks the complex membership from HA with server2 telephone.
TEST_F(ClassifyTest, server2Telephone) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[4], *client.getServer());

    // Add option.
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));
    client.addExtraOption(pxe);

    // Add server2
    client.addClass("server2");

    // Get an address
    client.doDORA();

    // Check response.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the third pool.
    EXPECT_EQ("10.0.0.110", resp->getYiaddr().toText());
}

// This test checks the complex membership from HA with server2 computer.
TEST_F(ClassifyTest, server2computer) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[4], *client.getServer());

    // Add option.
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0007));
    client.addExtraOption(pxe);

    // Add server2
    client.addClass("server2");

    // Get an address
    client.doDORA();

    // Check response.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the forth pool.
    EXPECT_EQ("10.0.0.160", resp->getYiaddr().toText());
}

// This test checks the precedence order in additional evaluation.
// This order is: pools > subnet > shared-network
TEST_F(ClassifyTest, precedenceNone) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"subnet4\": [ { "
        "        \"subnet\": \"10.0.0.0/24\","
        "        \"id\": 1,"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\""
        "         } ]"
        "    } ]"
        "} ]"
        "}";

    // Create a client requesting domain-name-servers option
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

    // Load the config and perform a DORA
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doDORA());

    // Check response
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());

    // Check domain-name-servers option
    OptionPtr opt = resp->getOption(DHO_DOMAIN_NAME_SERVERS);
    EXPECT_FALSE(opt);
}

// This test checks the precedence order in required evaluation.
// This order is: pools > subnet > shared-network
TEST_F(ClassifyTest, precedencePool) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"evaluate-additional-classes\": [ \"for-network\" ],"
        "    \"subnet4\": [ { "
        "        \"subnet\": \"10.0.0.0/24\","
        "        \"id\": 1,"
        "        \"evaluate-additional-classes\": [ \"for-subnet\" ],"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\","
        "            \"evaluate-additional-classes\": [ \"for-pool\" ]"
        "         } ]"
        "    } ]"
        "} ]"
        "}";

    // Create a client requesting domain-name-servers option
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

    // Load the config and perform a DORA
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doDORA());

    // Check response
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());

    // Check domain-name-servers option
    OptionPtr opt = resp->getOption(DHO_DOMAIN_NAME_SERVERS);
    ASSERT_TRUE(opt);
    Option4AddrLstPtr servers =
        boost::dynamic_pointer_cast<Option4AddrLst>(opt);
    ASSERT_TRUE(servers);
    auto addrs = servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("10.0.0.1", addrs[0].toText());
}

// This test checks the precedence order in required evaluation.
// This order is: pools > subnet > shared-network
TEST_F(ClassifyTest, precedenceSubnet) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"evaluate-additional-classes\": [ \"for-network\" ],"
        "    \"subnet4\": [ { "
        "        \"subnet\": \"10.0.0.0/24\","
        "        \"id\": 1,"
        "        \"evaluate-additional-classes\": [ \"for-subnet\" ],"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\""
        "         } ]"
        "    } ]"
        "} ]"
        "}";

    // Create a client requesting domain-name-servers option
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

    // Load the config and perform a DORA
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doDORA());

    // Check response
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());

    // Check domain-name-servers option
    OptionPtr opt = resp->getOption(DHO_DOMAIN_NAME_SERVERS);
    ASSERT_TRUE(opt);
    Option4AddrLstPtr servers =
        boost::dynamic_pointer_cast<Option4AddrLst>(opt);
    ASSERT_TRUE(servers);
    auto addrs = servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("10.0.0.2", addrs[0].toText());
}

// This test checks the precedence order in required evaluation.
// This order is: pools > subnet > shared-network
TEST_F(ClassifyTest, precedenceNetwork) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('ALL')\","
        "       \"only-in-additional-list\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"evaluate-additional-classes\": [ \"for-network\" ],"
        "    \"subnet4\": [ { "
        "        \"subnet\": \"10.0.0.0/24\","
        "        \"id\": 1,"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\""
        "         } ]"
        "    } ]"
        "} ]"
        "}";

    // Create a client requesting domain-name-servers option
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

    // Load the config and perform a DORA
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doDORA());

    // Check response
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());

    // Check domain-name-servers option
    OptionPtr opt = resp->getOption(DHO_DOMAIN_NAME_SERVERS);
    ASSERT_TRUE(opt);
    Option4AddrLstPtr servers =
        boost::dynamic_pointer_cast<Option4AddrLst>(opt);
    ASSERT_TRUE(servers);
    auto addrs = servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("10.0.0.3", addrs[0].toText());
}

// This test checks a required class without a test entry can be
// unconditionally added.
TEST_F(ClassifyTest, requiredNoTest) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"for-network\","
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"evaluate-additional-classes\": [ \"for-network\" ],"
        "    \"subnet4\": [ { "
        "        \"subnet\": \"10.0.0.0/24\","
        "        \"id\": 1,"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\""
        "         } ]"
        "    } ]"
        "} ]"
        "}";

    // Create a client requesting domain-name-servers option
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

    // Load the config and perform a DORA
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doDORA());

    // Check response
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());

    // Check domain-name-servers option
    OptionPtr opt = resp->getOption(DHO_DOMAIN_NAME_SERVERS);
    ASSERT_TRUE(opt);
    Option4AddrLstPtr servers =
        boost::dynamic_pointer_cast<Option4AddrLst>(opt);
    ASSERT_TRUE(servers);
    auto addrs = servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("10.0.0.3", addrs[0].toText());
}

// This test checks a required class which is not defined is ignored.
// Please set KEA_LOGGER_DESTINATION to stderr or stdout and check
// that DHCP4_ADDITIONAL_CLASS_UNDEFINED is logged,
TEST_F(ClassifyTest, requiredNotDefined) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"evaluate-additional-classes\": [ \"for-network\" ],"
        "    \"subnet4\": [ { "
        "        \"subnet\": \"10.0.0.0/24\","
        "        \"id\": 1,"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\""
        "         } ]"
        "    } ]"
        "} ]"
        "}";

    // Create a client requesting domain-name-servers option
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

    // Load the config and perform a DORA
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doDORA());

    // Check response
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());
}

// This test checks the handling for the DROP special class.
TEST_F(ClassifyTest, dropClass) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[5], *client.getServer());

    // Send the discover.
    client.doDiscover();

    // No option: no drop.
    EXPECT_TRUE(client.getContext().response_);

    // Retry with an option matching the DROP class.
    Dhcp4Client client2(Dhcp4Client::SELECTING);

    // Add the pxe option.
    OptionPtr pxe(new OptionInt<uint16_t>(Option::V4, 93, 0x0009));
    client2.addExtraOption(pxe);

    // Send the discover.
    client2.doDiscover();

    // Option, dropped.
    EXPECT_FALSE(client2.getContext().response_);

    // There should also be pkt4-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt4-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

// This test checks the handling for the DROP special class at the host
// reservation classification point with KNOWN / UNKNOWN.
TEST_F(ClassifyTest, dropClassUnknown) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[6], *client.getServer());

    // Set the HW address to the reservation.
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Send the discover.
    client.doDiscover();

    // Reservation match: no drop.
    EXPECT_TRUE(client.getContext().response_);

    // Retry with another HW address.
    Dhcp4Client client2(Dhcp4Client::SELECTING);
    client2.setHWAddress("aa:bb:cc:dd:ee:fe");

    // Send the discover.
    client2.doDiscover();

    // No reservation, dropped.
    EXPECT_FALSE(client2.getContext().response_);

    // There should also be pkt4-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt4-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

// This test checks the handling for the DROP special class at the host
// reservation classification point with a reserved class.
TEST_F(ClassifyTest, dropClassReservedClass) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[7], *client.getServer());

    // Set the HW address to the reservation.
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Send the discover.
    client.doDiscover();

    // Reservation match: no drop.
    EXPECT_TRUE(client.getContext().response_);

    // Retry with another HW address.
    Dhcp4Client client2(Dhcp4Client::SELECTING);
    client2.setHWAddress("aa:bb:cc:dd:ee:fe");

    // Send the discover.
    client2.doDiscover();

    // No reservation, dropped.
    EXPECT_FALSE(client2.getContext().response_);

    // There should also be pkt4-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt4-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

// This test checks the early global reservations lookup for selecting
// a guarded subnet.
TEST_F(ClassifyTest, earlySubnet) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[8], *client.getServer());

    // Set the HW address to the reservation.
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Send the discover.
    client.doDiscover();

    // Check response.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.0.10", resp->getYiaddr().toText());

    // Try with a different HW address.
    Dhcp4Client client2(Dhcp4Client::SELECTING);

    // Set the HW address to another value.
    client2.setHWAddress("aa:bb:cc:01:ee:ff");

    // Send the discover.
    client2.doDiscover();

    // Check response.
    resp = client2.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ("10.0.1.10", resp->getYiaddr().toText());
}

// This test checks the early global reservations lookup for dropping.
TEST_F(ClassifyTest, earlyDrop) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(CONFIGS[9], *client.getServer());

    // Set the HW address to the reservation.
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Send the discover.
    client.doDiscover();

    // Match the reservation so dropped.
    EXPECT_FALSE(client.getContext().response_);

    // There should also be pkt4-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt4-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);

    // Try with a different HW address.
    Dhcp4Client client2(Dhcp4Client::SELECTING);

    // Set the HW address to another value.
    client2.setHWAddress("aa:bb:cc:01:ee:ff");

    // Send the discover.
    client2.doDiscover();

    // Not matching so not dropped.
    EXPECT_TRUE(client2.getContext().response_);
}

// Checks that sub-class options have precedence of template class options
TEST_F(ClassifyTest, subClassPrecedence) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }],
        "option-def": [{
            "name": "opt1",
            "code": 249,
            "type": "string"
        },
        {
            "name": "opt2",
            "code": 250,
            "type": "string"
        }],
        "client-classes": [{
            "name": "template-client-id",
            "template-test": "substring(option[61].hex,0,3)",
            "option-data": [{
                "name": "opt1",
                "data": "template one"
            },
            {
                "name": "opt2",
                "data": "template two"
            }]
        },
        {
            "name": "SPAWN_template-client-id_111",
            "option-data": [{
                "name": "opt2",
                "data": "spawn two"
            }]
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create packets with enough to select the subnet
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the first 2 queries
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    prl->addValue(249);
    prl->addValue(250);
    query1->addOption(prl);

    // Classify packets
    srv.classifyPacket(query1);

    // Verify class membership is as expected.
    EXPECT_TRUE(query1->inClass("template-client-id"));
    EXPECT_TRUE(query1->inClass("SPAWN_template-client-id_111"));

    // Process query
    Pkt4Ptr response1 = srv.processDiscover(query1);

    // Verify that opt1 is inherited from the template.
    OptionPtr opt = response1->getOption(249);
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->toString(), "template one");

    // Verify that for opt2 subclass overrides the template.
    opt = response1->getOption(250);
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->toString(), "spawn two");
}

// Verifies that (non-vendor) requested options can be gated
// by option class tagging.
TEST_F(ClassifyTest, requestedOptionClassTagTest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }],
        "option-def": [{
            "name": "no_classes",
            "code": 249,
            "type": "string"
        },
        {
            "name": "wrong_class",
            "code": 250,
            "type": "string"
        },
        {
            "name": "right_class",
            "code": 251,
            "type": "string"
        }],
        "option-data": [{
            "name": "no_classes",
            "data": "oompa"
        },
        {
            "name": "wrong_class",
            "data": "loompa",
            "client-classes": [ "wrong" ]
        },
        {
            "name": "right_class",
            "data": "doompadee",
            "client-classes": [ "right" ]
        }],
        "client-classes": [{
            "name": "right",
            "test": "substring(option[61].hex,0,3) == '111'"
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create packets with enough to select the subnet
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the first 2 queries
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    prl->addValue(249);
    prl->addValue(250);
    prl->addValue(251);
    query1->addOption(prl);

    // Classify packets
    srv.classifyPacket(query1);

    // Verify class membership is as expected.
    EXPECT_TRUE(query1->inClass("right"));

    // Process query
    Pkt4Ptr response1 = srv.processDiscover(query1);

    // Option without class tags should be included.
    OptionPtr opt = response1->getOption(249);
    ASSERT_TRUE(opt);

    // Option with class tag that doesn't match should not included.
    opt = response1->getOption(250);
    ASSERT_FALSE(opt);

    // Option with class tag that matches should be included.
    opt = response1->getOption(251);
    ASSERT_TRUE(opt);
}

// Verifies the requested vendor options can be gated by
// option class tagging.
TEST_F(ClassifyTest, vendorOptionClassTagTest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }],
        "option-def": [{
            "space": "vendor-4491",
            "name": "one",
            "code": 101,
            "type": "string"
        },
        {
            "space": "vendor-4491",
            "name": "two",
            "code": 102,
            "type": "string"
        },
        {
            "space": "vendor-4491",
            "name": "three",
            "code": 103,
            "type": "string"
        }],
        "option-data": [{
            "space": "vendor-4491",
            "code": 101,
            "csv-format": true,
            "data": "zippy-ah",
            "client-classes": [ "melon" ]
        },
        {
            "space": "vendor-4491",
            "code": 102,
            "csv-format": true,
            "data": "dee",
            "client-classes": [ "ball" ]
        },
        {
            "space": "vendor-4491",
            "code": 103,
            "csv-format": true,
            "data": "doo-dah"
        }],
        "client-classes": [{
            "name": "melon",
            "test": "substring(option[61].hex,0,3) == '111'"
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create a DISCOVER that matches class "melon" but not "ball".
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Add a vendor-option (vendor-id=4491).
    OptionPtr vendor(new OptionVendor(Option::V4, 4491));
    query1->addOption(vendor);

    // Add the ORO sub-option requesting all three sub-options.
    boost::shared_ptr<OptionUint8Array> vendor_oro(new OptionUint8Array(Option::V4,
                                                                        DOCSIS3_V4_ORO));
    vendor_oro->addValue(101);
    vendor_oro->addValue(102);
    vendor_oro->addValue(103);
    vendor->addOption(vendor_oro);

    // Classify query.
    srv.classifyPacket(query1);

    // Verify it belongs to "melon" but not "ball".
    EXPECT_TRUE(query1->inClass("melon"));
    EXPECT_FALSE(query1->inClass("ball"));

    // Process the query
    Pkt4Ptr response1 = srv.processDiscover(query1);

    // Check if there is a vendor option response
    OptionPtr tmp = response1->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(tmp);

    // The response should be OptionVendor object
    boost::shared_ptr<OptionVendor> vendor_resp =
        boost::dynamic_pointer_cast<OptionVendor>(tmp);
    ASSERT_TRUE(vendor_resp);

    // Should have options 1 and 3, but not 2.
    EXPECT_EQ(2, vendor_resp->getOptions().size());
    EXPECT_TRUE(vendor_resp->getOption(101));
    EXPECT_FALSE(vendor_resp->getOption(102));
    EXPECT_TRUE(vendor_resp->getOption(103));
}

// Verifies that a requested VIVCO suboption can be gated by
// option class tagging.
TEST_F(ClassifyTest, vivcoOptionClassTagTest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }],
        "option-data": [{
            "name": "vivco-suboptions",
            "data": "1234, 03666f6f",
            "client-classes": [ "melon" ]
        }],
        "client-classes": [{
            "name": "melon",
            "test": "substring(option[61].hex,0,3) == '111'"
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create a DISCOVER that matches class "melon".
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Add a PRL option requesting the VIVCO suboption.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    prl->addValue(DHO_VIVCO_SUBOPTIONS);
    query1->addOption(prl);

    // Classify packet
    srv.classifyPacket(query1);

    // Verify it is a member of "melon".
    ASSERT_TRUE(query1->inClass("melon"));

    // Process query
    Pkt4Ptr response1 = srv.processDiscover(query1);

    // Check if there is a vendor option response
    OptionPtr tmp = response1->getOption(DHO_VIVCO_SUBOPTIONS);
    EXPECT_TRUE(tmp);

    // Try again with a client id that does not match "melon".
    id = ClientId::fromText("31:31:32");
    clientid = (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                                 id->getClientId())));
    query1.reset(new Pkt4(DHCPDISCOVER, 1235));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);
    query1->addOption(prl);

    // Classify packet
    srv.classifyPacket(query1);

    // Verify it is not a member of "melon".
    ASSERT_FALSE(query1->inClass("melon"));

    // Process query
    response1 = srv.processDiscover(query1);

    // VIVCO suboption should not be present.
    tmp = response1->getOption(DHO_VIVCO_SUBOPTIONS);
    ASSERT_FALSE(tmp);
}

// Verifies that requested VIVSO suboption can be gated by
// option class tagging.
TEST_F(ClassifyTest, vivsoOptionClassTagTest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }],
        "option-data": [{
            "name": "vivso-suboptions",
            "data": "1234",
            "client-classes": [ "melon" ]
        }],
        "client-classes": [{
            "name": "melon",
            "test": "substring(option[61].hex,0,3) == '111'"
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create a DISCOVER that matches class "melon".
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Add a PRL option requesting the VIVSO sub-option.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    prl->addValue(DHO_VIVSO_SUBOPTIONS);
    query1->addOption(prl);

    // Classify packet
    srv.classifyPacket(query1);

    // Verify it is a member of "melon".
    ASSERT_TRUE(query1->inClass("melon"));

    // Process query
    Pkt4Ptr response1 = srv.processDiscover(query1);

    // Verify the reponse contains the VIVSO sub-option
    OptionPtr tmp = response1->getOption(DHO_VIVSO_SUBOPTIONS);
    EXPECT_TRUE(tmp);

    // Try again with a client id that does not match "melon".
    id = ClientId::fromText("31:31:32");
    clientid = (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                                 id->getClientId())));
    query1.reset(new Pkt4(DHCPDISCOVER, 1235));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);
    query1->addOption(prl);

    // Classify packet
    srv.classifyPacket(query1);

    // Verify it is not a member of "melon".
    ASSERT_FALSE(query1->inClass("melon"));

    // Process query
    response1 = srv.processDiscover(query1);

    // VIVSO suboption should not be present.
    tmp = response1->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_FALSE(tmp);
}

// Verifies that the "basic" options (routers, domain-name, domain-name-servers,
// and dhcp-server-id) can be gated by option class tagging.
TEST_F(ClassifyTest, basicOptionClassTagTest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }],
        "option-data": [{
            "name": "routers",
            "data": "192.0.2.1",
            "client-classes": [ "melon" ]
        },
        {
            "name": "domain-name",
            "data": "example.com",
            "client-classes": [ "melon" ]
        },
        {
            "name": "domain-name-servers",
            "data": "192.0.2.3",
            "client-classes": [ "melon" ]
        },
        {
            "name": "dhcp-server-identifier",
            "data": "192.0.2.0",
            "client-classes": [ "melon" ]
        }],
        "client-classes": [{
            "name": "melon",
            "test": "substring(option[61].hex,0,3) == '111'"
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create a DISCOVER that matches class "melon".
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Configure DHCP server.
    configure(config, srv);

    // Classify packet
    srv.classifyPacket(query1);

    // Verify it is a member of "melon".
    ASSERT_TRUE(query1->inClass("melon"));

    // Process query
    Pkt4Ptr response1 = srv.processDiscover(query1);

    // Verify that routers, domain-name, and domain-name-servers are present.
    OptionPtr tmp = response1->getOption(DHO_ROUTERS);
    EXPECT_TRUE(tmp);
    tmp = response1->getOption(DHO_DOMAIN_NAME);
    EXPECT_TRUE(tmp);
    tmp = response1->getOption(DHO_DOMAIN_NAME_SERVERS);
    EXPECT_TRUE(tmp);

    // Verify that server id is present and is the configured value.
    checkServerIdentifier(response1, "192.0.2.0");

    // Try again with a client id that does not match "melon".
    id = ClientId::fromText("31:31:32");
    clientid = (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                                 id->getClientId())));
    query1.reset(new Pkt4(DHCPDISCOVER, 1235));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Classify packet
    srv.classifyPacket(query1);

    // Verify it is not a member of "melon".
    ASSERT_FALSE(query1->inClass("melon"));

    // Process query
    response1 = srv.processDiscover(query1);

    // Verify that routers, domain-name, and domain-name-servers are not present.
    tmp = response1->getOption(DHO_ROUTERS);
    EXPECT_FALSE(tmp);
    tmp = response1->getOption(DHO_DOMAIN_NAME);
    EXPECT_FALSE(tmp);
    tmp = response1->getOption(DHO_DOMAIN_NAME_SERVERS);
    EXPECT_FALSE(tmp);

    // Verify that server id is present but it is the generated value.
    checkServerIdentifier(response1, "0.0.0.0");
}

// Verifies that class-tagging does not subvert always-send.
TEST_F(ClassifyTest, classTaggingAndAlwaysSend) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    // Global host-name option disables always-send.  Subnet level
    // host-name enables always-send but has a non-matching class
    // tag.  The Response should contain the global value for host-name.
    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "option-data": [{
            "name": "host-name",
            "data": "global.com",
            "always-send" : false,
            "never-send" : false
        }],
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "option-data": [{
                "name": "host-name",
                "data": "subnet.com",
                "client-classes": [ "no-match" ],
                "always-send" : true
            }],
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create a DISCOVER that matches class "melon".
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Process query
    Pkt4Ptr response = srv.processDiscover(query1);

    // Verify that global host-name is present.
    OptionStringPtr hostname;
    hostname = boost::dynamic_pointer_cast<OptionString>(response->getOption(DHO_HOST_NAME));
    ASSERT_TRUE(hostname);
    EXPECT_EQ("global.com", hostname->getValue());
}

// Verifies that class-tagging does not subvert never-send.
TEST_F(ClassifyTest, classTaggingAndNeverSend) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    // Global host-name option enables always-send.  Subnet level
    // host-name enables never-send but has a non-matching class
    // tag.  The Response should not contain a value for host-name.
    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "option-data": [{
            "name": "host-name",
            "data": "global.com",
            "always-send" : true,
            "never-send" : false
        }],
        "subnet4": [{
            "id": 1,
            "subnet": "192.0.2.0/24",
            "option-data": [{
                "name": "host-name",
                "data": "subnet.com",
                "client-classes": [ "no-match" ],
                "always-send" : false,
                "never-send" : true
            }],
            "pools": [{
                "pool": "192.0.2.1 - 192.0.2.100"
             }]
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Create a DISCOVER that matches class "melon".
    auto id = ClientId::fromText("31:31:31");
    OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                               DHO_DHCP_CLIENT_IDENTIFIER,
                                               id->getClientId())));

    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // Process query
    Pkt4Ptr response = srv.processDiscover(query1);

    // The response should not contain host-name.
    ASSERT_FALSE(response->getOption(DHO_HOST_NAME));
}

// Verifies that client-classes specified at various
// network scopes result in proper subnet selection.
TEST_F(ClassifyTest, networkScopeClientClasses) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "client-classes":[{
            "name": "in-net",
            "test": "(substring(option[61].hex,0,1) == 'i')"
        },{
            "name": "subnet-1",
            "test": "(substring(option[61].hex,1,1) == '1')"
        },{
            "name": "subnet-2",
            "test": "(substring(option[61].hex,1,1) == '2')"
        },{
            "name": "pool-a",
            "test": "(substring(option[61].hex,2,1) == 'a')"
        },{
            "name": "pool-b",
            "test": "(substring(option[61].hex,2,1) == 'b')"
        }],
        "rebind-timer": 2000,
        "renew-timer": 1000,
        "valid-lifetime": 4000,
        "shared-networks": [{
            "name": "snet",
            "interface": "eth0",
            "client-classes": [ "in-net" ],
            "subnet4": [{
                "id": 1,
                "client-classes": [ "subnet-1" ],
                "subnet": "192.0.1.0/24",
                "pools": [{
                    "client-classes": [ "pool-a" ],
                    "pool": "192.0.1.1 - 192.0.1.1"
                },{
                    "client-classes": [ "pool-b" ],
                    "pool": "192.0.1.4 - 192.0.1.4"
                }]
            },{
                "id": 2,
               "client-classes": [ "subnet-2" ],
                "subnet": "192.0.2.0/24",
                "pools": [{
                    "pool": "192.0.2.1 - 192.0.2.1"
                }]
            },{
                "id": 3,
                "subnet": "192.0.3.0/24",
                "pools": [{
                    "pool": "192.0.3.1 - 192.0.3.1"
                }]
            }]
        }]
    }
    )^";

    // Configure DHCP server.
    configure(config, srv);

    // Describes a single scenario.
    struct Scenario {
        std::vector<uint8_t> client_id_; // client-id to use
        uint8_t exp_type_;               // expected DHCP response type (if one)
        std::string exp_address_;        // expected value for offered address (if one)
    };

    // Scenarios to run.
    std::list<Scenario> scenarios = {
        { { 'i', '1', 'a' }, DHCPOFFER,     "192.0.1.1" },
        { { 'i', '1', 'b' }, DHCPOFFER,     "192.0.1.4" },
        { { 'i', '1', '-' }, DHCPOFFER,     "192.0.3.1" },
        { { 'i', '2', '-' }, DHCPOFFER,     "192.0.2.1" },
        { { 'i', 'x', '-' }, DHCPOFFER,     "192.0.3.1" },
        { { '-', '1', 'a' }, DHCP_NOTYPE,   ""          },
        { { '-', '2', '-' }, DHCP_NOTYPE,   ""          },
        { { '-', 'x', '-' }, DHCP_NOTYPE,   ""          }
    };

    // Run scenarios.
    for (auto const& scenario : scenarios) {
        ClientId id(scenario.client_id_);
        SCOPED_TRACE(id.toText());
        Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
        query->addOption(OptionPtr(new Option(Option::V4,
                                              DHO_DHCP_CLIENT_IDENTIFIER,
                                              id.getClientId())));
        query->setIface("eth0");
        query->setIndex(ETH0_INDEX);

        // Classify packet
        srv.classifyPacket(query);

        // Process query
        Pkt4Ptr response = srv.processDiscover(query);
        if (scenario.exp_type_ == DHCP_NOTYPE) {
            EXPECT_FALSE(response);
        } else {
            ASSERT_TRUE(response);
            EXPECT_EQ(static_cast<int>(response->getType()), scenario.exp_type_);
            if (!scenario.exp_address_.empty()) {
                EXPECT_EQ(response->getYiaddr(), IOAddress(scenario.exp_address_));
            }
        }
    }
}

// Verifies that mulitple occurences of an option with
// different client class tags works properly.
TEST_F(ClassifyTest, classTaggingList) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv4Srv srv(0);

    // Define a client-str option for classification, and server-str
    // option to send in response.  Then define 3 possible values in 
    // a subnet for sever-str based on class membership.
    string config = R"^(
    {
        "interfaces-config": {
            "interfaces": [ "*" ]
        },
        "option-def": [{
            "name": "client-str",
            "code": 222,
            "type": "string"
        },{
            "name": "server-str",
            "code": 223,
            "type": "string"
        }],
        "client-classes": [{
               "name": "class-one",
               "test": "(option[222].text == 'one')"
            },
            {
               "name": "class-two",
               "test": "(option[222].text == 'two')"
            },
            {
               "name": "class-neither",
               "test": "not member('class-one') and not member('class-two')"
            }
        ],
        "subnet4": [{
           "id": 1,
           "interface": "eth1",
            "subnet": "192.0.1.0/24",
           "pools": [{ "pool": "192.0.1.1 - 192.0.1.255" }],
           "option-data": [{
               "client-classes":  [ "class-one" ],
               "name": "server-str",
               "data": "string.one"
           },{
               "name": "server-str",
               "data": "string.other"
           },{
               "client-classes":  [ "class-two" ],
               "name": "server-str",
               "data": "string.two"
           }]
        }],
        "valid-lifetime": 4000
    })^";

    ASSERT_NO_THROW(configure(config));

    struct Scenario {
        int line_;
        std::string client_str_;
        std::string exp_class_;
        std::string exp_server_str_;
    };

    std::list<Scenario> scenarios {
        { __LINE__, "one",     "class-one",     "string.one" }, 
        { __LINE__, "two",     "class-two",     "string.two" }, 
        { __LINE__, "neither", "class-neither", "string.other" }
    };

    for (const auto& scenario : scenarios) {
        std::ostringstream oss;
        oss << "Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());

        // Create DISCOVER.
        Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
        auto id = ClientId::fromText("31:31:31");
        OptionPtr clientid = (OptionPtr(new Option(Option::V4,
                                                   DHO_DHCP_CLIENT_IDENTIFIER,
                                                   id->getClientId())));
        query->addOption(clientid);
        query->setIface("eth1");
        query->setIndex(ETH1_INDEX);

        // Add an PRL option requestion server-str option to the query.
        OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                     DHO_DHCP_PARAMETER_REQUEST_LIST));
        prl->addValue(223);
        query->addOption(prl);

        // Add client-str opt of "one" to the query.
        OptionStringPtr client_str(new OptionString(Option::V4, 222, scenario.client_str_));
        query->addOption(client_str);

        // Classify the packet and verify class membership is as expected.
        srv.classifyPacket(query);
        ASSERT_TRUE(query->inClass(scenario.exp_class_));

        // Process the query
        Pkt4Ptr response = srv.processDiscover(query);
        ASSERT_TRUE(response);

        // Verify that server-str opt is as expected
        OptionPtr server_opt = response->getOption(223);
        ASSERT_TRUE(server_opt);
        EXPECT_EQ(server_opt->toString(), scenario.exp_server_str_);
    }
}

} // end of anonymous namespace
