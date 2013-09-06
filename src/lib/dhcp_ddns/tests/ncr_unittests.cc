// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp_ddns/ncr_msg.h>
#include <dhcp/duid.h>
#include <util/time_utilities.h>

#include <gtest/gtest.h>
#include <algorithm>

using namespace std;
using namespace isc;
using namespace isc::dhcp_ddns;
using namespace isc::dhcp;

namespace {

/// @brief Defines a list of valid JSON NameChangeRequest renditions.
/// They are used as input to test conversion from JSON.
const char *valid_msgs[] =
{
    // Valid Add.
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Valid Remove.
     "{"
     " \"change_type\" : 1 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
     // Valid Add with IPv6 address
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"fe80::2acf:e9ff:fe12:e56f\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}"
};

/// @brief Defines a list of invalid JSON NameChangeRequest renditions.
/// They are used as input to test conversion from JSON.
const char *invalid_msgs[] =
{
    // Invalid change type.
     "{"
     " \"change_type\" : 7 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Invalid forward change.
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : \"bogus\" , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Invalid reverse change.
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : 500 , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Forward and reverse change both false.
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : false , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Blank FQDN
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Bad IP address
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"xxxxxx\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Blank DHCID
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Odd number of digits in DHCID
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Text in DHCID
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"THIS IS BOGUS!!!\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Invalid lease expiration string
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"Wed Jun 26 13:46:46 EDT 2013\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Non-integer for lease length.
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : \"BOGUS\" "
     "}"

};

/// @brief Tests the NameChangeRequest constructors.
/// This test verifies that:
/// 1. Default constructor works.
/// 2. "Full" constructor, when given valid parameter values, works.
/// 3. "Full" constructor, given a blank FQDN fails
/// 4. "Full" constructor, given an invalid IP Address FQDN fails
/// 5. "Full" constructor, given a blank DHCID fails
/// 6. "Full" constructor, given false for both forward and reverse fails
TEST(NameChangeRequestTest, constructionTests) {
    // Verify the default constructor works.
    NameChangeRequestPtr ncr;
    EXPECT_NO_THROW(ncr.reset(new NameChangeRequest()));
    EXPECT_TRUE(ncr);

    // Verify that full constructor works.
    uint64_t expiry = isc::util::detail::gettimeWrapper();
    D2Dhcid dhcid("010203040A7F8E3D");

    EXPECT_NO_THROW(ncr.reset(new NameChangeRequest(
                    CHG_ADD, true, true, "walah.walah.com",
                    "192.168.1.101", dhcid, expiry, 1300)));
    EXPECT_TRUE(ncr);
    ncr.reset();

    // Verify blank FQDN is detected.
    EXPECT_THROW(NameChangeRequest(CHG_ADD, true, true, "",
                 "192.168.1.101", dhcid, expiry, 1300), NcrMessageError);

    // Verify that an invalid IP address is detected.
    EXPECT_THROW(NameChangeRequest(CHG_ADD, true, true, "valid.fqdn",
                 "xxx.168.1.101", dhcid, expiry, 1300), NcrMessageError);

    // Verify that a blank DHCID is detected.
    D2Dhcid blank_dhcid;
    EXPECT_THROW(NameChangeRequest(CHG_ADD, true, true, "walah.walah.com",
                 "192.168.1.101", blank_dhcid, expiry, 1300), NcrMessageError);

    // Verify that one or both of direction flags must be true.
    EXPECT_THROW(NameChangeRequest(CHG_ADD, false, false, "valid.fqdn",
                "192.168.1.101", dhcid, expiry, 1300), NcrMessageError);

}

/// @brief Tests the basic workings of D2Dhcid to and from string conversions.
/// It verifies that:
/// 1. DHCID input strings must contain an even number of characters
/// 2. DHCID input strings must contain only hexadecimal character digits
/// 3. A valid DHCID string converts correctly.
/// 4. Converting a D2Dhcid to a string works correctly.
/// 5. Equality, inequality, and less-than-equal operators work.
TEST(NameChangeRequestTest, dhcidTest) {
    D2Dhcid dhcid;

    // Odd number of digits should be rejected.
    std::string test_str = "010203040A7F8E3";
    EXPECT_THROW(dhcid.fromStr(test_str), NcrMessageError);

    // Non digit content should be rejected.
    test_str = "0102BOGUSA7F8E3D";
    EXPECT_THROW(dhcid.fromStr(test_str), NcrMessageError);

    // Verify that valid input converts into a proper byte array.
    test_str = "010203040A7F8E3D";
    ASSERT_NO_THROW(dhcid.fromStr(test_str));

    // Create a test vector of expected byte contents.
    const uint8_t bytes[] = { 0x1, 0x2, 0x3, 0x4, 0xA, 0x7F, 0x8E, 0x3D };
    std::vector<uint8_t> expected_bytes(bytes, bytes + sizeof(bytes));

    // Fetch the byte vector from the dhcid and verify if equals the expected
    // content.
    const std::vector<uint8_t>& converted_bytes = dhcid.getBytes();
    EXPECT_EQ(expected_bytes.size(), converted_bytes.size());
    EXPECT_TRUE (std::equal(expected_bytes.begin(),
                            expected_bytes.begin()+expected_bytes.size(),
                            converted_bytes.begin()));

    // Convert the new dhcid back to string and verify it matches the original
    // DHCID input string.
    std::string next_str = dhcid.toStr();
    EXPECT_EQ(test_str, next_str);

    // Test equality, inequality, and less-than-equal operators
    test_str="AABBCCDD";
    EXPECT_NO_THROW(dhcid.fromStr(test_str));

    D2Dhcid other_dhcid;
    EXPECT_NO_THROW(other_dhcid.fromStr(test_str));

    EXPECT_TRUE(dhcid == other_dhcid);
    EXPECT_FALSE(dhcid != other_dhcid);

    EXPECT_NO_THROW(other_dhcid.fromStr("BBCCDDEE"));
    EXPECT_TRUE(dhcid < other_dhcid);

}

/// Tests that DHCID is correctly created from a DUID and FQDN. The final format
/// of the DHCID is as follows:
/// <identifier-type> <digest-type-code> <digest>
/// where:
/// - identifier-type (2 octets) is 0x0002.
/// - digest-type-code (1 octet) indicates SHA-256 hashing and is equal 0x1.
/// - digest = SHA-256(<DUID> <FQDN>)
/// Note: FQDN is given in the on-wire canonical format.
TEST(NameChangeRequestTest, dhcidFromDUID) {
    D2Dhcid dhcid;

    // Create DUID.
    uint8_t duid_data[] = { 0, 1, 2, 3, 4, 5, 6 };
    DUID duid(duid_data, sizeof(duid_data));

    // Create FQDN in on-wire format: myhost.example.com. It is encoded
    // as a set of labels, each preceded by its length. The whole FQDN
    // is zero-terminated.
    const uint8_t fqdn_data[] = {
        6, 109, 121, 104, 111, 115, 116,     // myhost.
        7, 101, 120, 97, 109, 112, 108, 101, // example.
        3, 99, 111, 109, 0                   // com.
    };
    std::vector<uint8_t> wire_fqdn(fqdn_data, fqdn_data + sizeof(fqdn_data));

    // Create DHCID.
    ASSERT_NO_THROW(dhcid.fromDUID(duid, wire_fqdn));

    // The reference DHCID (represented as string of hexadecimal digits)
    // has been calculated using one of the online calculators.
    std::string dhcid_ref = "0002012191B7B21AF97E0E656DF887C5E2D"
        "EF30E7758A207EDF4CCB2DE8CA37066021C";

    // Make sure that the DHCID is valid.
    EXPECT_EQ(dhcid_ref, dhcid.toStr());
}

// Test that DHCID is correctly created when the DUID has minimal length (1).
TEST(NameChangeRequestTest, dhcidFromMinDUID) {
    D2Dhcid dhcid;

    // Create DUID.
    uint8_t duid_data[] = { 1 };
    DUID duid(duid_data, sizeof(duid_data));

    // Create FQDN in on-wire format: myhost.example.com. It is encoded
    // as a set of labels, each preceded by its length. The whole FQDN
    // is zero-terminated.
    const uint8_t fqdn_data[] = {
        6, 109, 121, 104, 111, 115, 116,     // myhost.
        7, 101, 120, 97, 109, 112, 108, 101, // example.
        3, 99, 111, 109, 0                   // com.
    };
    std::vector<uint8_t> wire_fqdn(fqdn_data, fqdn_data + sizeof(fqdn_data));

    // Create DHCID.
    ASSERT_NO_THROW(dhcid.fromDUID(duid, wire_fqdn));

    // The reference DHCID (represented as string of hexadecimal digits)
    // has been calculated using one of the online calculators.
    std::string dhcid_ref = "000201F89004F73E60CAEDFF514E11CB91D"
        "1F45C8F0A55D4BC4C688484A819F8EA4074";

    // Make sure that the DHCID is valid.
    EXPECT_EQ(dhcid_ref, dhcid.toStr());
}

// Test that DHCID is correctly created when the DUID has maximal length (128).
TEST(NameChangeRequestTest, dhcidFromMaxDUID) {
    D2Dhcid dhcid;

    // Create DUID.
    std::vector<uint8_t> duid_data(128, 1);
    DUID duid(&duid_data[0], duid_data.size());

    // Create FQDN in on-wire format: myhost.example.com. It is encoded
    // as a set of labels, each preceded by its length. The whole FQDN
    // is zero-terminated.
    const uint8_t fqdn_data[] = {
        6, 109, 121, 104, 111, 115, 116,     // myhost.
        7, 101, 120, 97, 109, 112, 108, 101, // example.
        3, 99, 111, 109, 0                   // com.
    };
    std::vector<uint8_t> wire_fqdn(fqdn_data, fqdn_data + sizeof(fqdn_data));

    // Create DHCID.
    ASSERT_NO_THROW(dhcid.fromDUID(duid, wire_fqdn));

    // The reference DHCID (represented as string of hexadecimal digits)
    // has been calculated using one of the online calculators.
    std::string dhcid_ref = "00020137D8FBDC0585B44DFA03FAD2E36C6"
        "159737D545A12EFB40B0D88D110A5748234";

    // Make sure that the DHCID is valid.
    EXPECT_EQ(dhcid_ref, dhcid.toStr());
}

// test operator<< on D2Dhcid
TEST(NameChangeRequestTest, leftShiftOperation) {
    const D2Dhcid dhcid("010203040A7F8E3D");

    ostringstream oss;
    oss << dhcid;
    EXPECT_EQ(dhcid.toStr(), oss.str());
}

/// @brief Verifies the fundamentals of converting from and to JSON.
/// It verifies that:
/// 1. A NameChangeRequest can be created from a valid JSON string.
/// 2. A valid JSON string can be created from a NameChangeRequest
TEST(NameChangeRequestTest, basicJsonTest) {
    // Define valid JSON rendition of a request.
    std::string msg_str = "{"
                            "\"change_type\":1,"
                            "\"forward_change\":true,"
                            "\"reverse_change\":false,"
                            "\"fqdn\":\"walah.walah.com\","
                            "\"ip_address\":\"192.168.2.1\","
                            "\"dhcid\":\"010203040A7F8E3D\","
                            "\"lease_expires_on\":\"20130121132405\","
                            "\"lease_length\":1300"
                          "}";

    // Verify that a NameChangeRequests can be instantiated from the
    // a valid JSON rendition.
    NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(ncr  = NameChangeRequest::fromJSON(msg_str));
    ASSERT_TRUE(ncr);

    // Verify that the JSON string created by the new request equals the
    // original input string.
    std::string json_str = ncr->toJSON();
    EXPECT_EQ(msg_str, json_str);
}

/// @brief Tests a variety of invalid JSON message strings.
/// This test iterates over a list of JSON messages, each containing a single
/// content error. The list of messages is defined by the global array,
/// invalid_messages. Currently that list contains the following invalid
/// conditions:
///  1. Invalid change type
///  2. Invalid forward change
///  3. Invalid reverse change
///  4. Forward and reverse change both false
///  5. Invalid forward change
///  6. Blank FQDN
///  7. Bad IP address
///  8. Blank DHCID
///  9. Odd number of digits in DHCID
/// 10. Text in DHCID
/// 11. Invalid lease expiration string
/// 12. Non-integer for lease length.
/// If more permutations arise they can easily be added to the list.
TEST(NameChangeRequestTest, invalidMsgChecks) {
    // Iterate over the list of JSON strings, attempting to create a
    // NameChangeRequest. The attempt should throw a NcrMessageError.
    int num_msgs = sizeof(invalid_msgs)/sizeof(char*);
    for (int i = 0; i < num_msgs; i++) {
        EXPECT_THROW(NameChangeRequest::fromJSON(invalid_msgs[i]),
                     NcrMessageError) << "Invalid message not caught idx: "
                     << i << std::endl << " text:[" << invalid_msgs[i] << "]"
                     << std::endl;
    }
}

/// @brief Tests a variety of valid JSON message strings.
/// This test iterates over a list of JSON messages, each containing a single
/// valid request rendition. The list of messages is defined by the global
/// array, valid_messages. Currently that list contains the following valid
/// messages:
///  1. Valid, IPv4 Add
///  2. Valid, IPv4 Remove
///  3. Valid, IPv6 Add
/// If more permutations arise they can easily be added to the list.
TEST(NameChangeRequestTest, validMsgChecks) {
    // Iterate over the list of JSON strings, attempting to create a
    // NameChangeRequest. The attempt should succeed.
    int num_msgs = sizeof(valid_msgs)/sizeof(char*);
    for (int i = 0; i < num_msgs; i++) {
        EXPECT_NO_THROW(NameChangeRequest::fromJSON(valid_msgs[i]))
                        << "Valid message failed,  message idx: " << i
                        << std::endl << " text:[" << valid_msgs[i] << "]"
                        << std::endl;
    }
}

/// @brief Tests converting to and from JSON via isc::util buffer classes.
/// This test verifies that:
/// 1. A NameChangeRequest can be rendered in JSON written to an OutputBuffer
/// 2. A InputBuffer containing a valid JSON request rendition can be used
/// to create a NameChangeRequest.
TEST(NameChangeRequestTest, toFromBufferTest) {
    // Define a string containing a valid JSON NameChangeRequest rendition.
    std::string msg_str = "{"
                            "\"change_type\":1,"
                            "\"forward_change\":true,"
                            "\"reverse_change\":false,"
                            "\"fqdn\":\"walah.walah.com\","
                            "\"ip_address\":\"192.168.2.1\","
                            "\"dhcid\":\"010203040A7F8E3D\","
                            "\"lease_expires_on\":\"20130121132405\","
                            "\"lease_length\":1300"
                          "}";

    // Create a request from JSON directly.
    NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(msg_str));

    // Verify that we output the request as JSON text to a buffer
    // without error.
    isc::util::OutputBuffer output_buffer(1024);
    ASSERT_NO_THROW(ncr->toFormat(FMT_JSON, output_buffer));

    // Make an InputBuffer from the OutputBuffer.
    isc::util::InputBuffer input_buffer(output_buffer.getData(),
                                        output_buffer.getLength());

    // Verify that we can create a new request from the InputBuffer.
    NameChangeRequestPtr ncr2;
    ASSERT_NO_THROW(ncr2 =
                    NameChangeRequest::fromFormat(FMT_JSON, input_buffer));

    // Convert the new request to JSON directly.
    std::string final_str = ncr2->toJSON();

    // Verify that the final string matches the original.
    ASSERT_EQ(final_str, msg_str);
}


} // end of anonymous namespace

