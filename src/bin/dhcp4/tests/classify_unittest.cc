// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp/option_int.h>
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
        "   \"only-if-required\": true,"
        "   \"next-server\": \"1.2.3.4\""
        "},"
        "{"
        "   \"name\": \"pxe2\","
        "   \"test\": \"option[93].hex == 0x0007\","
        "   \"only-if-required\": true,"
        "   \"server-hostname\": \"deneb\""
        "},"
        "{"
        "   \"name\": \"pxe3\","
        "   \"test\": \"option[93].hex == 0x0006\","
        "   \"only-if-required\": false,"
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
        "    \"require-client-classes\": [ \"pxe2\" ]"
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
        "          \"client-class\": \"server1_and_telephones\" },"
        "        { \"pool\": \"10.0.0.60-10.0.0.99\","
        "          \"client-class\": \"server1_and_computers\" },"
        "        { \"pool\": \"10.0.0.110-10.0.0.149\","
        "          \"client-class\": \"server2_and_telephones\" },"
        "        { \"pool\": \"10.0.0.160-10.0.0.199\","
        "          \"client-class\": \"server2_and_computers\" } ]"
        " } ]"
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
        IfaceMgr::instance().openSockets4();
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

// Class 'pxe1' is only-if-required and not subject to required evaluation
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


// Class pxe2 is only-if-required but the subnet requires its evaluation
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

// This test checks the precedence order in required evaluation.
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedenceNone) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
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
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedencePool) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
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
        "            \"pool\": \"10.0.0.10-10.0.0.100\","
        "            \"require-client-classes\": [ \"for-pool\" ]"
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
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedenceSubnet) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
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
        "        \"require-client-classes\": [ \"for-subnet\" ],"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\","
        "            \"require-client-classes\": [ \"for-pool\" ]"
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
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedenceNetwork) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"10.0.0.3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"require-client-classes\": [ \"for-network\" ],"
        "    \"subnet4\": [ { "
        "        \"subnet\": \"10.0.0.0/24\","
        "        \"id\": 1,"
        "        \"require-client-classes\": [ \"for-subnet\" ],"
        "        \"pools\": [ { "
        "            \"pool\": \"10.0.0.10-10.0.0.100\","
        "            \"require-client-classes\": [ \"for-pool\" ]"
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

} // end of anonymous namespace
