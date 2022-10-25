// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <run_script.h>

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>

#include <cstdio>
#include <fstream>

#include <gtest/gtest.h>

using namespace isc::run_script;

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;
using namespace std;

extern "C" {
extern int lease4_renew(CalloutHandle& handle);
extern int lease4_expire(CalloutHandle& handle);
extern int lease4_recover(CalloutHandle& handle);
extern int leases4_committed(CalloutHandle& handle);
extern int lease4_release(CalloutHandle& handle);
extern int lease4_decline(CalloutHandle& handle);
extern int lease6_renew(CalloutHandle& handle);
extern int lease6_rebind(CalloutHandle& handle);
extern int lease6_expire(CalloutHandle& handle);
extern int lease6_recover(CalloutHandle& handle);
extern int leases6_committed(CalloutHandle& handle);
extern int lease6_release(CalloutHandle& handle);
extern int lease6_decline(CalloutHandle& handle);
}

namespace isc {
namespace run_script {

extern RunScriptImplPtr impl;

} // namespace run_script
} // namespace isc

namespace {

/// @brief This function joins all received environment variables and adds a
/// newline after each one so that a simple compare can be done in the test.
///
/// @param vars The list of environment variables to join.
/// @return The joined environment.
string
join(const ProcessEnvVars& vars) {
    string result;
    for (auto var : vars) {
        result += var + "\n";
    }
    return (result);
}

/// @brief Generate a valid HWAddr.
///
/// @return The generated HWAddr.
HWAddrPtr
generateHWAddr() {
    return (HWAddrPtr(new HWAddr({0, 1, 2 ,3}, HTYPE_ETHER)));
}

/// @brief Generate a valid DUID.
///
/// @return The generated DUID.
ClientIdPtr
generateDUID() {
    return (ClientIdPtr(new ClientId({0, 1, 2, 3, 4, 5, 6})));
}

/// @brief Generate a valid Option.
///
/// @param universe The option universe (V4 or V6).
/// @param code The Option code to use.
/// @return The generated Option.
OptionPtr
generateOption(Option::Universe universe, uint16_t code, OptionBuffer& data) {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(universe == Option::V4 ?
                                                    DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE,
                                                    code);
    if (def) {
        return (OptionCustomPtr(new OptionCustom(*def, universe, data)));
    }

    return (OptionPtr());
}

/// @brief Generate a valid Option6IA.
///
/// @return The generated Option6IA.
Option6IAPtr
generateOptionIA() {
    OptionBuffer buf;
    buf.resize(12);
    buf[0] = 0xa1; // iaid
    buf[1] = 0xa2;
    buf[2] = 0xa3;
    buf[3] = 0xa4;
    buf[4] = 0x81; // T1
    buf[5] = 0x02;
    buf[6] = 0x03;
    buf[7] = 0x04;
    buf[8] = 0x84; // T2
    buf[9] = 0x03;
    buf[10] = 0x02;
    buf[11] = 0x01;

    return (Option6IAPtr(new Option6IA(D6O_IA_NA, buf.begin(), buf.end())));
}

/// @brief Generate a valid Subnet4.
///
/// @return The generated Subnet4.
Subnet4Ptr
generateSubnet4() {
    return (Subnet4Ptr(new Subnet4(IOAddress("182.168.0.1"), 2, 3, 4, 5, 6)));
}

/// @brief Generate a valid Subnet6.
///
/// @return The generated Subnet6.
Subnet6Ptr
generateSubnet6() {
    return (Subnet6Ptr(new Subnet6(IOAddress("2003:db8::1"), 2, 3, 4, 5, 6, 7)));
}

/// @brief Generate a valid Lease4.
///
/// @return The generated Lease4.
Lease4Ptr
generateLease4() {
    HWAddrPtr hwaddr = generateHWAddr();
    ClientIdPtr clientid = generateDUID();

    Lease4Ptr lease4(new Lease4(IOAddress("192.168.0.1"), hwaddr, clientid,
                                2, 3, 4, false, false, "test.hostname"));

    return(lease4);
}

/// @brief Generate a valid Lease6.
///
/// @return The generated Lease6.
Lease6Ptr
generateLease6() {
    HWAddrPtr hwaddr = generateHWAddr();
    DuidPtr duid = generateDUID();

    Lease6Ptr lease6(new Lease6(Lease::TYPE_NA, IOAddress("2003:db8::1"), duid,
                                2, 3, 4, 5, false, false, "test.hostname",
                                hwaddr));

    lease6->cltt_ = 7;

    return (lease6);
}

/// @brief Generate a Pkt4 with all parameters set.
///
/// @return The generated Pkt4.
Pkt4Ptr
generatePkt4() {
    // A dummy MAC address, padded with 0s
    const uint8_t dummyChaddr[16] = {0, 1, 2, 3, 4, 5, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0 };

    // Let's use some creative test content here (128 chars + \0)
    const uint8_t dummyFile[] = "Lorem ipsum dolor sit amet, consectetur "
        "adipiscing elit. Proin mollis placerat metus, at "
        "lacinia orci ornare vitae. Mauris amet.";

    // Yet another type of test content (64 chars + \0)
    const uint8_t dummySname[] = "Lorem ipsum dolor sit amet, consectetur "
        "adipiscing elit posuere.";

    // That is only part of the header. It contains all "short" fields,
    // larger fields are constructed separately.
    uint8_t hdr[] = {
        1, 6, 6, 13,            // op, htype, hlen, hops,
        0x12, 0x34, 0x56, 0x78, // transaction-id
        0, 42, 0x80, 0x00,      // 42 secs, BROADCAST flags
        192, 0, 2, 1,           // ciaddr
        1, 2, 3, 4,             // yiaddr
        192, 0, 2, 255,         // siaddr
        192, 0, 2, 50,          // giaddr
    };

    // Initialize the vector with the header fields defined above.
    vector<uint8_t> buf(hdr, hdr + sizeof(hdr));

    // Append the large header fields.
    copy(dummyChaddr, dummyChaddr + Pkt4::MAX_CHADDR_LEN, back_inserter(buf));
    copy(dummySname, dummySname + Pkt4::MAX_SNAME_LEN, back_inserter(buf));
    copy(dummyFile, dummyFile + Pkt4::MAX_FILE_LEN, back_inserter(buf));

    // Should now have all the header, so check.  The "static_cast" is used
    // to get round an odd bug whereby the linker appears not to find the
    // definition of DHCPV4_PKT_HDR_LEN if it appears within an EXPECT_EQ().
    EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), buf.size());

    // Add magic cookie
    buf.push_back(0x63);
    buf.push_back(0x82);
    buf.push_back(0x53);
    buf.push_back(0x63);

    // Add message type DISCOVER
    buf.push_back(static_cast<uint8_t>(DHO_DHCP_MESSAGE_TYPE));
    buf.push_back(1); // length (just one byte)
    buf.push_back(static_cast<uint8_t>(DHCPDISCOVER));

    Pkt4Ptr pkt4(new Pkt4(&buf[0], buf.size()));

    pkt4->setIface("eth1");
    pkt4->setIndex(2);

    pkt4->setHWAddr(generateHWAddr());
    pkt4->setLocalHWAddr(generateHWAddr());
    pkt4->setRemoteHWAddr(generateHWAddr());

    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                        DHO_DHCP_AGENT_OPTIONS);

    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));

    uint8_t circuit_id[] = { 0x68, 0x6f, 0x77, 0x64, 0x79 };
    OptionPtr circuit_id_opt(new Option(Option::V4, RAI_OPTION_AGENT_CIRCUIT_ID,
                                        OptionBuffer(circuit_id,
                                        circuit_id + sizeof(circuit_id))));
    rai->addOption(circuit_id_opt);

    uint8_t subscriber_id[] = { 0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f };
    OptionPtr subscriber_id_opt(new Option(Option::V4, RAI_OPTION_SUBSCRIBER_ID,
                                           OptionBuffer(subscriber_id,
                                           subscriber_id + sizeof(subscriber_id))));
    rai->addOption(subscriber_id_opt);

    uint8_t remote_id[] = { 0x87, 0xf6, 0x79, 0x77, 0xef };
    OptionPtr remote_id_opt(new Option(Option::V4, RAI_OPTION_REMOTE_ID,
                                       OptionBuffer(remote_id,
                                       remote_id + sizeof(remote_id))));
    rai->addOption(remote_id_opt);

    pkt4->addOption(rai);

    return (pkt4);
}

/// @brief Generate a Pkt6 with all parameters set.
///
/// @return The generated Pkt6.
Pkt6Ptr
generatePkt6() {
    // That is only part of the header. It contains all "short" fields,
    // larger fields are constructed separately.
    uint8_t data[98];
    data[0]  = 1;
    data[1]  = 1;       data[2]  = 2;     data[3] = 3;      data[4]  = 0;
    data[5]  = 1;       data[6]  = 0;     data[7] = 14;     data[8]  = 0;
    data[9]  = 1;       data[10] = 0;     data[11] = 1;     data[12] = 21;
    data[13] = 158;     data[14] = 60;    data[15] = 22;    data[16] = 0;
    data[17] = 30;      data[18] = 140;   data[19] = 155;   data[20] = 115;
    data[21] = 73;      data[22] = 0;     data[23] = 3;     data[24] = 0;
    data[25] = 40;      data[26] = 0;     data[27] = 0;     data[28] = 0;
    data[29] = 1;       data[30] = 255;   data[31] = 255;   data[32] = 255;
    data[33] = 255;     data[34] = 255;   data[35] = 255;   data[36] = 255;
    data[37] = 255;     data[38] = 0;     data[39] = 5;     data[40] = 0;
    data[41] = 24;      data[42] = 32;    data[43] = 1;     data[44] = 13;
    data[45] = 184;     data[46] = 0;     data[47] = 1;     data[48] = 0;
    data[49] = 0;       data[50] = 0;     data[51] = 0;     data[52] = 0;
    data[53] = 0;       data[54] = 0;     data[55] = 0;     data[56] = 18;
    data[57] = 52;      data[58] = 255;   data[59] = 255;   data[60] = 255;
    data[61] = 255;     data[62] = 255;   data[63] = 255;   data[64] = 255;
    data[65] = 255;     data[66] = 0;     data[67] = 23;    data[68] = 0;
    data[69] = 16;      data[70] = 32;    data[71] = 1;     data[72] = 13;
    data[73] = 184;     data[74] = 0;     data[75] = 1;     data[76] = 0;
    data[77] = 0;       data[78] = 0;     data[79] = 0;     data[80] = 0;
    data[81] = 0;       data[82] = 0;     data[83] = 0;     data[84] = 221;
    data[85] = 221;     data[86] = 0;     data[87] = 8;     data[88] = 0;
    data[89] = 2;       data[90] = 0;     data[91] = 100;   data[92] = 0;
    data[93] = 6;       data[94] = 0;     data[95] = 2;     data[96] = 0;
    data[97] = 23;

    Pkt6Ptr pkt6(new Pkt6(data, sizeof(data)));

    pkt6->setRemotePort(546);
    pkt6->setRemoteAddr(IOAddress("fe80::21e:8cff:fe9b:7349"));
    pkt6->setLocalPort(0);
    pkt6->setLocalAddr(IOAddress("ff02::1:2"));

    pkt6->setIface("eth1");
    pkt6->setIndex(2);

    pkt6->setRemoteHWAddr(generateHWAddr());
    pkt6->addOption(OptionPtr(new Option(Option::V6, D6O_CLIENTID,
                              generateDUID()->getDuid())));

    return (pkt6);
}

/// @brief Tests the RunScript setName and getName functions.
TEST(RunScript, testSetNameGetName) {
    RunScriptImpl script;
    string script_name = "test";
    ASSERT_NO_THROW(script.setName(script_name));
    EXPECT_EQ(script_name, script.getName());
}

/// @brief Tests the RunScript setSync and getSync functions.
TEST(RunScript, testSetSyncGetSync) {
    RunScriptImpl script;
    bool sync = true;
    ASSERT_NO_THROW(script.setSync(sync));
    EXPECT_EQ(sync, script.getSync());
}

/// @brief Tests the extractBoolean method works as expected.
TEST(RunScript, extractBoolean) {
    ProcessEnvVars vars;
    bool flag = false;
    RunScriptImpl::extractBoolean(vars, flag, "FALSE_PREFIX", "_FALSE_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "FALSE_PREFIX_FALSE_SUFFIX=false\n";
    EXPECT_EQ(expected, join(vars));
    flag = true;
    RunScriptImpl::extractBoolean(vars, flag, "TRUE_PREFIX", "_TRUE_SUFFIX");
    ASSERT_EQ(2, vars.size());
    expected = "FALSE_PREFIX_FALSE_SUFFIX=false\n"
               "TRUE_PREFIX_TRUE_SUFFIX=true\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractInteger method works as expected.
TEST(RunScript, extractInteger) {
    ProcessEnvVars vars;
    uint64_t value = 0;
    RunScriptImpl::extractInteger(vars, value, "ZERO_PREFIX", "_ZERO_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "ZERO_PREFIX_ZERO_SUFFIX=0\n";
    EXPECT_EQ(expected, join(vars));
    value = 1;
    RunScriptImpl::extractInteger(vars, value, "ONE_PREFIX", "_ONE_SUFFIX");
    ASSERT_EQ(2, vars.size());
    expected = "ZERO_PREFIX_ZERO_SUFFIX=0\n"
               "ONE_PREFIX_ONE_SUFFIX=1\n";
    EXPECT_EQ(expected, join(vars));
    value = 1000;
    RunScriptImpl::extractInteger(vars, value, "THOUSAND_PREFIX", "_THOUSAND_SUFFIX");
    ASSERT_EQ(3, vars.size());
    expected = "ZERO_PREFIX_ZERO_SUFFIX=0\n"
               "ONE_PREFIX_ONE_SUFFIX=1\n"
               "THOUSAND_PREFIX_THOUSAND_SUFFIX=1000\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractString method works as expected.
TEST(RunScript, extractString) {
    ProcessEnvVars vars;
    string value = "";
    RunScriptImpl::extractString(vars, value, "EMPTY_PREFIX", "_EMPTY_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "EMPTY_PREFIX_EMPTY_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    value = "SOMETHING";
    RunScriptImpl::extractString(vars, value, "NON_EMPTY_PREFIX", "_NON_EMPTY_SUFFIX");
    ASSERT_EQ(2, vars.size());
    expected = "EMPTY_PREFIX_EMPTY_SUFFIX=\n"
               "NON_EMPTY_PREFIX_NON_EMPTY_SUFFIX=SOMETHING\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractHWAddr method works as expected.
TEST(RunScript, extractHWAddr) {
    ProcessEnvVars vars;
    HWAddrPtr hwaddr;
    RunScriptImpl::extractHWAddr(vars, hwaddr, "HWADDR_PREFIX", "_HWADDR_SUFFIX");
    ASSERT_EQ(2, vars.size());
    string expected = "HWADDR_PREFIX_HWADDR_SUFFIX=\n"
                      "HWADDR_PREFIX_TYPE_HWADDR_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    hwaddr = generateHWAddr();
    RunScriptImpl::extractHWAddr(vars, hwaddr, "HWADDR_PREFIX", "_HWADDR_SUFFIX");
    ASSERT_EQ(2, vars.size());
    expected = "HWADDR_PREFIX_HWADDR_SUFFIX=00:01:02:03\n"
               "HWADDR_PREFIX_TYPE_HWADDR_SUFFIX=1\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractDUID method works as expected.
TEST(RunScript, extractDUID) {
    ProcessEnvVars vars;
    DuidPtr duid;
    RunScriptImpl::extractDUID(vars, duid, "DUID_PREFIX", "_DUID_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "DUID_PREFIX_DUID_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    duid = generateDUID();
    RunScriptImpl::extractDUID(vars, duid, "DUID_PREFIX", "_DUID_SUFFIX");
    ASSERT_EQ(1, vars.size());
    expected = "DUID_PREFIX_DUID_SUFFIX=00:01:02:03:04:05:06\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractOption method works as expected.
TEST(RunScript, extractOption) {
    ProcessEnvVars vars;
    OptionPtr option;
    RunScriptImpl::extractOption(vars, option, "OPTION_PREFIX", "_OPTION_SUFFIX");
    ASSERT_EQ(0, vars.size());
    OptionBuffer buffer = { 0xca, 0xfe, 0xba, 0xbe };
    option = generateOption(Option::V4, DHO_USER_CLASS, buffer);
    RunScriptImpl::extractOption(vars, option, "OPTION_PREFIX", "_OPTION_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "OPTION_PREFIX_OPTION_77_OPTION_SUFFIX=0xCAFEBABE\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractSubOption method works as expected.
TEST(RunScript, extractSubOption) {
    ProcessEnvVars vars;
    OptionPtr option;
    RunScriptImpl::extractOption(vars, option, "OPTION_SUBOPTION_PREFIX", "_OPTION_SUBOPTION_SUFFIX");
    ASSERT_EQ(0, vars.size());
    OptionBuffer data;
    option = generateOption(Option::V4, DHO_DHCP_AGENT_OPTIONS, data);
    uint8_t subscriber_id[] = { 0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f };
    OptionPtr subscriber_id_opt(new Option(Option::V4, RAI_OPTION_SUBSCRIBER_ID,
                                           OptionBuffer(subscriber_id,
                                           subscriber_id + sizeof(subscriber_id))));
    option->addOption(subscriber_id_opt);
    RunScriptImpl::extractSubOption(vars, option, RAI_OPTION_SUBSCRIBER_ID, "OPTION_SUBOPTION_PREFIX", "_OPTION_SUBOPTION_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "OPTION_SUBOPTION_PREFIX_OPTION_82_SUB_OPTION_6_OPTION_SUBOPTION_SUFFIX=0x1A2B3C4D5E6F\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractOptionIA method works as expected.
TEST(RunScript, extractOptionIA) {
    ProcessEnvVars vars;
    Option6IAPtr optionia;
    RunScriptImpl::extractOptionIA(vars, optionia, "OPTIONIA_PREFIX", "_OPTIONIA_SUFFIX");
    ASSERT_EQ(4, vars.size());
    string expected = "OPTIONIA_PREFIX_IAID_OPTIONIA_SUFFIX=\n"
                      "OPTIONIA_PREFIX_IA_TYPE_OPTIONIA_SUFFIX=\n"
                      "OPTIONIA_PREFIX_IA_T1_OPTIONIA_SUFFIX=\n"
                      "OPTIONIA_PREFIX_IA_T2_OPTIONIA_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    optionia = generateOptionIA();
    RunScriptImpl::extractOptionIA(vars, optionia, "OPTIONIA_PREFIX", "_OPTIONIA_SUFFIX");
    ASSERT_EQ(4, vars.size());
    expected = "OPTIONIA_PREFIX_IAID_OPTIONIA_SUFFIX=2711790500\n"
               "OPTIONIA_PREFIX_IA_TYPE_OPTIONIA_SUFFIX=3\n"
               "OPTIONIA_PREFIX_IA_T1_OPTIONIA_SUFFIX=2164392708\n"
               "OPTIONIA_PREFIX_IA_T2_OPTIONIA_SUFFIX=2214789633\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractSubnet4 method works as expected.
TEST(RunScript, extractSubnet4) {
    ProcessEnvVars vars;
    Subnet4Ptr subnet4;
    RunScriptImpl::extractSubnet4(vars, subnet4, "SUBNET4_PREFIX", "_SUBNET4_SUFFIX");
    ASSERT_EQ(4, vars.size());
    string expected = "SUBNET4_PREFIX_ID_SUBNET4_SUFFIX=\n"
                      "SUBNET4_PREFIX_NAME_SUBNET4_SUFFIX=\n"
                      "SUBNET4_PREFIX_PREFIX_SUBNET4_SUFFIX=\n"
                      "SUBNET4_PREFIX_PREFIX_LEN_SUBNET4_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    subnet4 = generateSubnet4();
    RunScriptImpl::extractSubnet4(vars, subnet4, "SUBNET4_PREFIX", "_SUBNET4_SUFFIX");
    ASSERT_EQ(4, vars.size());
    expected = "SUBNET4_PREFIX_ID_SUBNET4_SUFFIX=6\n"
               "SUBNET4_PREFIX_NAME_SUBNET4_SUFFIX=182.168.0.1/2\n"
               "SUBNET4_PREFIX_PREFIX_SUBNET4_SUFFIX=182.168.0.1\n"
               "SUBNET4_PREFIX_PREFIX_LEN_SUBNET4_SUFFIX=2\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractSubnet6 method works as expected.
TEST(RunScript, extractSubnet6) {
    ProcessEnvVars vars;
    Subnet6Ptr subnet6;
    RunScriptImpl::extractSubnet6(vars, subnet6, "SUBNET6_PREFIX", "_SUBNET6_SUFFIX");
    ASSERT_EQ(4, vars.size());
    string expected = "SUBNET6_PREFIX_ID_SUBNET6_SUFFIX=\n"
                      "SUBNET6_PREFIX_NAME_SUBNET6_SUFFIX=\n"
                      "SUBNET6_PREFIX_PREFIX_SUBNET6_SUFFIX=\n"
                      "SUBNET6_PREFIX_PREFIX_LEN_SUBNET6_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    subnet6 = generateSubnet6();
    RunScriptImpl::extractSubnet6(vars, subnet6, "SUBNET6_PREFIX", "_SUBNET6_SUFFIX");
    ASSERT_EQ(4, vars.size());
    expected = "SUBNET6_PREFIX_ID_SUBNET6_SUFFIX=7\n"
               "SUBNET6_PREFIX_NAME_SUBNET6_SUFFIX=2003:db8::1/2\n"
               "SUBNET6_PREFIX_PREFIX_SUBNET6_SUFFIX=2003:db8::1\n"
               "SUBNET6_PREFIX_PREFIX_LEN_SUBNET6_SUFFIX=2\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractLease4 method works as expected.
TEST(RunScript, extractLease4) {
    ProcessEnvVars vars;
    Lease4Ptr lease4;
    RunScriptImpl::extractLease4(vars, lease4, "LEASE4_PREFIX", "_LEASE4_SUFFIX");
    ASSERT_EQ(9, vars.size());
    string expected = "LEASE4_PREFIX_ADDRESS_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_CLTT_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_HOSTNAME_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_HWADDR_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_HWADDR_TYPE_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_STATE_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_SUBNET_ID_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_VALID_LIFETIME_LEASE4_SUFFIX=\n"
                      "LEASE4_PREFIX_CLIENT_ID_LEASE4_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    lease4 = generateLease4();
    RunScriptImpl::extractLease4(vars, lease4, "LEASE4_PREFIX", "_LEASE4_SUFFIX");
    ASSERT_EQ(9, vars.size());
    expected = "LEASE4_PREFIX_ADDRESS_LEASE4_SUFFIX=192.168.0.1\n"
               "LEASE4_PREFIX_CLTT_LEASE4_SUFFIX=3\n"
               "LEASE4_PREFIX_HOSTNAME_LEASE4_SUFFIX=test.hostname\n"
               "LEASE4_PREFIX_HWADDR_LEASE4_SUFFIX=00:01:02:03\n"
               "LEASE4_PREFIX_HWADDR_TYPE_LEASE4_SUFFIX=1\n"
               "LEASE4_PREFIX_STATE_LEASE4_SUFFIX=default\n"
               "LEASE4_PREFIX_SUBNET_ID_LEASE4_SUFFIX=4\n"
               "LEASE4_PREFIX_VALID_LIFETIME_LEASE4_SUFFIX=2\n"
               "LEASE4_PREFIX_CLIENT_ID_LEASE4_SUFFIX=00:01:02:03:04:05:06\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractLease6 method works as expected.
TEST(RunScript, extractLease6) {
    ProcessEnvVars vars;
    Lease6Ptr lease6;
    RunScriptImpl::extractLease6(vars, lease6, "LEASE6_PREFIX", "_LEASE6_SUFFIX");
    ASSERT_EQ(13, vars.size());
    string expected = "LEASE6_PREFIX_ADDRESS_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_CLTT_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_HOSTNAME_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_HWADDR_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_HWADDR_TYPE_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_STATE_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_SUBNET_ID_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_VALID_LIFETIME_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_DUID_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_IAID_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_PREFERRED_LIFETIME_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_PREFIX_LEN_LEASE6_SUFFIX=\n"
                      "LEASE6_PREFIX_TYPE_LEASE6_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    lease6 = generateLease6();
    RunScriptImpl::extractLease6(vars, lease6, "LEASE6_PREFIX", "_LEASE6_SUFFIX");
    ASSERT_EQ(13, vars.size());
    expected = "LEASE6_PREFIX_ADDRESS_LEASE6_SUFFIX=2003:db8::1\n"
               "LEASE6_PREFIX_CLTT_LEASE6_SUFFIX=7\n"
               "LEASE6_PREFIX_HOSTNAME_LEASE6_SUFFIX=test.hostname\n"
               "LEASE6_PREFIX_HWADDR_LEASE6_SUFFIX=00:01:02:03\n"
               "LEASE6_PREFIX_HWADDR_TYPE_LEASE6_SUFFIX=1\n"
               "LEASE6_PREFIX_STATE_LEASE6_SUFFIX=default\n"
               "LEASE6_PREFIX_SUBNET_ID_LEASE6_SUFFIX=5\n"
               "LEASE6_PREFIX_VALID_LIFETIME_LEASE6_SUFFIX=4\n"
               "LEASE6_PREFIX_DUID_LEASE6_SUFFIX=00:01:02:03:04:05:06\n"
               "LEASE6_PREFIX_IAID_LEASE6_SUFFIX=2\n"
               "LEASE6_PREFIX_PREFERRED_LIFETIME_LEASE6_SUFFIX=3\n"
               "LEASE6_PREFIX_PREFIX_LEN_LEASE6_SUFFIX=128\n"
               "LEASE6_PREFIX_TYPE_LEASE6_SUFFIX=IA_NA\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractLeases4 method works as expected.
TEST(RunScript, extractLeases4) {
    ProcessEnvVars vars;
    Lease4CollectionPtr leases4;
    RunScriptImpl::extractLeases4(vars, leases4, "LEASES4_PREFIX", "_LEASES4_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "LEASES4_PREFIX_SIZE_LEASES4_SUFFIX=0\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    leases4.reset(new Lease4Collection());
    leases4->push_back(generateLease4());
    leases4->push_back(generateLease4());
    RunScriptImpl::extractLeases4(vars, leases4, "LEASES4_PREFIX", "_LEASES4_SUFFIX");
    ASSERT_EQ(19, vars.size());
    expected = "LEASES4_PREFIX_SIZE_LEASES4_SUFFIX=2\n"
               "LEASES4_PREFIX_AT0_ADDRESS_LEASES4_SUFFIX=192.168.0.1\n"
               "LEASES4_PREFIX_AT0_CLTT_LEASES4_SUFFIX=3\n"
               "LEASES4_PREFIX_AT0_HOSTNAME_LEASES4_SUFFIX=test.hostname\n"
               "LEASES4_PREFIX_AT0_HWADDR_LEASES4_SUFFIX=00:01:02:03\n"
               "LEASES4_PREFIX_AT0_HWADDR_TYPE_LEASES4_SUFFIX=1\n"
               "LEASES4_PREFIX_AT0_STATE_LEASES4_SUFFIX=default\n"
               "LEASES4_PREFIX_AT0_SUBNET_ID_LEASES4_SUFFIX=4\n"
               "LEASES4_PREFIX_AT0_VALID_LIFETIME_LEASES4_SUFFIX=2\n"
               "LEASES4_PREFIX_AT0_CLIENT_ID_LEASES4_SUFFIX=00:01:02:03:04:05:06\n"
               "LEASES4_PREFIX_AT1_ADDRESS_LEASES4_SUFFIX=192.168.0.1\n"
               "LEASES4_PREFIX_AT1_CLTT_LEASES4_SUFFIX=3\n"
               "LEASES4_PREFIX_AT1_HOSTNAME_LEASES4_SUFFIX=test.hostname\n"
               "LEASES4_PREFIX_AT1_HWADDR_LEASES4_SUFFIX=00:01:02:03\n"
               "LEASES4_PREFIX_AT1_HWADDR_TYPE_LEASES4_SUFFIX=1\n"
               "LEASES4_PREFIX_AT1_STATE_LEASES4_SUFFIX=default\n"
               "LEASES4_PREFIX_AT1_SUBNET_ID_LEASES4_SUFFIX=4\n"
               "LEASES4_PREFIX_AT1_VALID_LIFETIME_LEASES4_SUFFIX=2\n"
               "LEASES4_PREFIX_AT1_CLIENT_ID_LEASES4_SUFFIX=00:01:02:03:04:05:06\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractLeases6 method works as expected.
TEST(RunScript, extractLeases6) {
    ProcessEnvVars vars;
    Lease6CollectionPtr leases6;
    RunScriptImpl::extractLeases6(vars, leases6, "LEASES6_PREFIX", "_LEASES6_SUFFIX");
    ASSERT_EQ(1, vars.size());
    string expected = "LEASES6_PREFIX_SIZE_LEASES6_SUFFIX=0\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    leases6.reset(new Lease6Collection());
    leases6->push_back(generateLease6());
    leases6->push_back(generateLease6());
    RunScriptImpl::extractLeases6(vars, leases6, "LEASES6_PREFIX", "_LEASES6_SUFFIX");
    ASSERT_EQ(27, vars.size());
    expected = "LEASES6_PREFIX_SIZE_LEASES6_SUFFIX=2\n"
               "LEASES6_PREFIX_AT0_ADDRESS_LEASES6_SUFFIX=2003:db8::1\n"
               "LEASES6_PREFIX_AT0_CLTT_LEASES6_SUFFIX=7\n"
               "LEASES6_PREFIX_AT0_HOSTNAME_LEASES6_SUFFIX=test.hostname\n"
               "LEASES6_PREFIX_AT0_HWADDR_LEASES6_SUFFIX=00:01:02:03\n"
               "LEASES6_PREFIX_AT0_HWADDR_TYPE_LEASES6_SUFFIX=1\n"
               "LEASES6_PREFIX_AT0_STATE_LEASES6_SUFFIX=default\n"
               "LEASES6_PREFIX_AT0_SUBNET_ID_LEASES6_SUFFIX=5\n"
               "LEASES6_PREFIX_AT0_VALID_LIFETIME_LEASES6_SUFFIX=4\n"
               "LEASES6_PREFIX_AT0_DUID_LEASES6_SUFFIX=00:01:02:03:04:05:06\n"
               "LEASES6_PREFIX_AT0_IAID_LEASES6_SUFFIX=2\n"
               "LEASES6_PREFIX_AT0_PREFERRED_LIFETIME_LEASES6_SUFFIX=3\n"
               "LEASES6_PREFIX_AT0_PREFIX_LEN_LEASES6_SUFFIX=128\n"
               "LEASES6_PREFIX_AT0_TYPE_LEASES6_SUFFIX=IA_NA\n"
               "LEASES6_PREFIX_AT1_ADDRESS_LEASES6_SUFFIX=2003:db8::1\n"
               "LEASES6_PREFIX_AT1_CLTT_LEASES6_SUFFIX=7\n"
               "LEASES6_PREFIX_AT1_HOSTNAME_LEASES6_SUFFIX=test.hostname\n"
               "LEASES6_PREFIX_AT1_HWADDR_LEASES6_SUFFIX=00:01:02:03\n"
               "LEASES6_PREFIX_AT1_HWADDR_TYPE_LEASES6_SUFFIX=1\n"
               "LEASES6_PREFIX_AT1_STATE_LEASES6_SUFFIX=default\n"
               "LEASES6_PREFIX_AT1_SUBNET_ID_LEASES6_SUFFIX=5\n"
               "LEASES6_PREFIX_AT1_VALID_LIFETIME_LEASES6_SUFFIX=4\n"
               "LEASES6_PREFIX_AT1_DUID_LEASES6_SUFFIX=00:01:02:03:04:05:06\n"
               "LEASES6_PREFIX_AT1_IAID_LEASES6_SUFFIX=2\n"
               "LEASES6_PREFIX_AT1_PREFERRED_LIFETIME_LEASES6_SUFFIX=3\n"
               "LEASES6_PREFIX_AT1_PREFIX_LEN_LEASES6_SUFFIX=128\n"
               "LEASES6_PREFIX_AT1_TYPE_LEASES6_SUFFIX=IA_NA\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractPkt4 method works as expected.
TEST(RunScript, extractPkt4) {
    ProcessEnvVars vars;
    Pkt4Ptr pkt4;
    RunScriptImpl::extractPkt4(vars, pkt4, "PKT4_PREFIX", "_PKT4_SUFFIX");
    ASSERT_EQ(22, vars.size());
    string expected = "PKT4_PREFIX_TYPE_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_TXID_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_LOCAL_ADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_LOCAL_PORT_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_REMOTE_ADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_REMOTE_PORT_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_IFACE_INDEX_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_IFACE_NAME_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_HOPS_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_SECS_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_FLAGS_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_CIADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_SIADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_YIADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_GIADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_RELAYED_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_HWADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_HWADDR_TYPE_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_LOCAL_HWADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_LOCAL_HWADDR_TYPE_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_REMOTE_HWADDR_PKT4_SUFFIX=\n"
                      "PKT4_PREFIX_REMOTE_HWADDR_TYPE_PKT4_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    pkt4 = generatePkt4();
    RunScriptImpl::extractPkt4(vars, pkt4, "PKT4_PREFIX", "_PKT4_SUFFIX");
    ASSERT_EQ(25, vars.size());
    expected = "PKT4_PREFIX_TYPE_PKT4_SUFFIX=UNKNOWN\n"
               "PKT4_PREFIX_TXID_PKT4_SUFFIX=0\n"
               "PKT4_PREFIX_LOCAL_ADDR_PKT4_SUFFIX=0.0.0.0\n"
               "PKT4_PREFIX_LOCAL_PORT_PKT4_SUFFIX=67\n"
               "PKT4_PREFIX_REMOTE_ADDR_PKT4_SUFFIX=0.0.0.0\n"
               "PKT4_PREFIX_REMOTE_PORT_PKT4_SUFFIX=68\n"
               "PKT4_PREFIX_IFACE_INDEX_PKT4_SUFFIX=2\n"
               "PKT4_PREFIX_IFACE_NAME_PKT4_SUFFIX=eth1\n"
               "PKT4_PREFIX_HOPS_PKT4_SUFFIX=0\n"
               "PKT4_PREFIX_SECS_PKT4_SUFFIX=0\n"
               "PKT4_PREFIX_FLAGS_PKT4_SUFFIX=0\n"
               "PKT4_PREFIX_CIADDR_PKT4_SUFFIX=0.0.0.0\n"
               "PKT4_PREFIX_SIADDR_PKT4_SUFFIX=0.0.0.0\n"
               "PKT4_PREFIX_YIADDR_PKT4_SUFFIX=0.0.0.0\n"
               "PKT4_PREFIX_GIADDR_PKT4_SUFFIX=0.0.0.0\n"
               "PKT4_PREFIX_RELAYED_PKT4_SUFFIX=false\n"
               "PKT4_PREFIX_HWADDR_PKT4_SUFFIX=00:01:02:03\n"
               "PKT4_PREFIX_HWADDR_TYPE_PKT4_SUFFIX=1\n"
               "PKT4_PREFIX_LOCAL_HWADDR_PKT4_SUFFIX=00:01:02:03\n"
               "PKT4_PREFIX_LOCAL_HWADDR_TYPE_PKT4_SUFFIX=1\n"
               "PKT4_PREFIX_REMOTE_HWADDR_PKT4_SUFFIX=00:01:02:03\n"
               "PKT4_PREFIX_REMOTE_HWADDR_TYPE_PKT4_SUFFIX=1\n"
               "PKT4_PREFIX_OPTION_82_PKT4_SUFFIX=0x0105686F776479020587F67977EF06061A2B3C4D5E6F\n"
               "PKT4_PREFIX_OPTION_82_SUB_OPTION_1_PKT4_SUFFIX=0x686F776479\n"
               "PKT4_PREFIX_OPTION_82_SUB_OPTION_2_PKT4_SUFFIX=0x87F67977EF\n";
    EXPECT_EQ(expected, join(vars));
}

/// @brief Tests the extractPkt6 method works as expected.
TEST(RunScript, extractPkt6) {
    ProcessEnvVars vars;
    Pkt6Ptr pkt6;
    RunScriptImpl::extractPkt6(vars, pkt6, "PKT6_PREFIX", "_PKT6_SUFFIX");
    ASSERT_EQ(12, vars.size());
    string expected = "PKT6_PREFIX_TYPE_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_TXID_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_LOCAL_ADDR_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_LOCAL_PORT_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_REMOTE_ADDR_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_REMOTE_PORT_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_IFACE_INDEX_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_IFACE_NAME_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_REMOTE_HWADDR_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_REMOTE_HWADDR_TYPE_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_PROTO_PKT6_SUFFIX=\n"
                      "PKT6_PREFIX_CLIENT_ID_PKT6_SUFFIX=\n";
    EXPECT_EQ(expected, join(vars));
    vars.clear();
    pkt6 = generatePkt6();
    RunScriptImpl::extractPkt6(vars, pkt6, "PKT6_PREFIX", "_PKT6_SUFFIX");
    ASSERT_EQ(12, vars.size());
    expected = "PKT6_PREFIX_TYPE_PKT6_SUFFIX=UNKNOWN\n"
               "PKT6_PREFIX_TXID_PKT6_SUFFIX=0\n"
               "PKT6_PREFIX_LOCAL_ADDR_PKT6_SUFFIX=ff02::1:2\n"
               "PKT6_PREFIX_LOCAL_PORT_PKT6_SUFFIX=0\n"
               "PKT6_PREFIX_REMOTE_ADDR_PKT6_SUFFIX=fe80::21e:8cff:fe9b:7349\n"
               "PKT6_PREFIX_REMOTE_PORT_PKT6_SUFFIX=546\n"
               "PKT6_PREFIX_IFACE_INDEX_PKT6_SUFFIX=2\n"
               "PKT6_PREFIX_IFACE_NAME_PKT6_SUFFIX=eth1\n"
               "PKT6_PREFIX_REMOTE_HWADDR_PKT6_SUFFIX=00:01:02:03\n"
               "PKT6_PREFIX_REMOTE_HWADDR_TYPE_PKT6_SUFFIX=1\n"
               "PKT6_PREFIX_PROTO_PKT6_SUFFIX=UDP\n"
               "PKT6_PREFIX_CLIENT_ID_PKT6_SUFFIX=00:01:02:03:04:05:06\n";
    EXPECT_EQ(expected, join(vars));
}

class RunScriptTest : public ::testing::Test {
public:

    /// @brief Constructor.
    RunScriptTest() :
        co_manager_(new CalloutManager(1)), io_service_(new IOService()) {
        RunScriptImpl::setIOService(io_service_);
        clearLogFile();
    }

    /// @brief Destructor.
    ~RunScriptTest() {
        RunScriptImpl::setIOService(IOServicePtr());
        clearLogFile();
    }

    /// @brief Clear the test file if it exists.
    void clearLogFile() {
        ::remove(TEST_LOG_FILE);
    }

    void checkScriptResult() {
        ifstream test_log;
        vector<string> extracted_lines;
        time_t now(time(NULL));
        while (true) {
            test_log.open(TEST_LOG_FILE);
            if (!test_log.fail()) {
                string line;
                while (getline(test_log, line)) {
                    extracted_lines.push_back(line) ;
                }
                test_log.close();
                break;
            }
            ASSERT_LT(time(NULL), now + 3) << "timeout";
            usleep(100000);
        }
        ASSERT_EQ(join(extracted_lines), "SUCCESS\n");
    }

    /// @brief Fetches the callout manager instance.
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return (co_manager_);
    }

private:
    /// @brief Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;

    /// @brief IOService instance to process IO.
    isc::asiolink::IOServicePtr io_service_;
};

TEST_F(RunScriptTest, lease4Renew) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt4Ptr pkt4 = generatePkt4();
    handle.setArgument("query4", pkt4);
    Subnet4Ptr subnet4 = generateSubnet4();
    handle.setArgument("subnet4", subnet4);
    ClientIdPtr clientid = generateDUID();
    handle.setArgument("clientid", clientid);
    HWAddrPtr hwaddr = generateHWAddr();
    handle.setArgument("hwaddr", hwaddr);
    Lease4Ptr lease4 = generateLease4();
    handle.setArgument("lease4", lease4);
    int ret;
    ASSERT_NO_THROW(ret = lease4_renew(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease4Expire) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Lease4Ptr lease4 = generateLease4();
    handle.setArgument("lease4", lease4);
    bool remove_lease = true;
    handle.setArgument("remove_lease", remove_lease);
    int ret;
    ASSERT_NO_THROW(ret = lease4_expire(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease4Recover) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Lease4Ptr lease4 = generateLease4();
    handle.setArgument("lease4", lease4);
    int ret;
    ASSERT_NO_THROW(ret = lease4_recover(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease4Committed) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt4Ptr pkt4 = generatePkt4();
    handle.setArgument("query4", pkt4);
    Lease4CollectionPtr leases4;
    leases4.reset(new Lease4Collection());
    leases4->push_back(Lease4Ptr());
    leases4->push_back(generateLease4());
    handle.setArgument("leases4", leases4);
    Lease4CollectionPtr deleted_leases4;
    deleted_leases4.reset(new Lease4Collection());
    deleted_leases4->push_back(generateLease4());
    deleted_leases4->push_back(Lease4Ptr());
    handle.setArgument("deleted_leases4", deleted_leases4);
    int ret;
    ASSERT_NO_THROW(ret = leases4_committed(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease4Release) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt4Ptr pkt4 = generatePkt4();
    handle.setArgument("query4", pkt4);
    Lease4Ptr lease4 = generateLease4();
    handle.setArgument("lease4", lease4);
    int ret;
    ASSERT_NO_THROW(ret = lease4_release(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease4Decline) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt4Ptr pkt4 = generatePkt4();
    handle.setArgument("query4", pkt4);
    Lease4Ptr lease4 = generateLease4();
    handle.setArgument("lease4", lease4);
    int ret;
    ASSERT_NO_THROW(ret = lease4_decline(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease6Renew) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt6Ptr pkt6 = generatePkt6();
    handle.setArgument("query6", pkt6);
    Lease6Ptr lease6 = generateLease6();
    handle.setArgument("lease6", lease6);
    Option6IAPtr option6IA = generateOptionIA();
    handle.setArgument("ia_na", option6IA);
    int ret;
    ASSERT_NO_THROW(ret = lease6_renew(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease6Rebind) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt6Ptr pkt6 = generatePkt6();
    handle.setArgument("query6", pkt6);
    Lease6Ptr lease6 = generateLease6();
    handle.setArgument("lease6", lease6);
    Option6IAPtr option6IA = generateOptionIA();
    handle.setArgument("ia_na", option6IA);
    int ret;
    ASSERT_NO_THROW(ret = lease6_rebind(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease6Expire) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Lease6Ptr lease6 = generateLease6();
    handle.setArgument("lease6", lease6);
    bool remove_lease = true;
    handle.setArgument("remove_lease", remove_lease);
    int ret;
    ASSERT_NO_THROW(ret = lease6_expire(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease6Recover) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Lease6Ptr lease6 = generateLease6();
    handle.setArgument("lease6", lease6);
    int ret;
    ASSERT_NO_THROW(ret = lease6_recover(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease6Committed) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt6Ptr pkt6 = generatePkt6();
    handle.setArgument("query6", pkt6);
    Lease6CollectionPtr leases6;
    leases6.reset(new Lease6Collection());
    leases6->push_back(Lease6Ptr());
    leases6->push_back(generateLease6());
    handle.setArgument("leases6", leases6);
    Lease6CollectionPtr deleted_leases6;
    deleted_leases6.reset(new Lease6Collection());
    deleted_leases6->push_back(generateLease6());
    deleted_leases6->push_back(Lease6Ptr());
    handle.setArgument("deleted_leases6", deleted_leases6);
    int ret;
    ASSERT_NO_THROW(ret = leases6_committed(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease6Release) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt6Ptr pkt6 = generatePkt6();
    handle.setArgument("query6", pkt6);
    Lease6Ptr lease6 = generateLease6();
    handle.setArgument("lease6", lease6);
    int ret;
    ASSERT_NO_THROW(ret = lease6_release(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

TEST_F(RunScriptTest, lease6Decline) {
    impl.reset(new RunScriptImpl());
    impl->setName(RUN_SCRIPT_TEST_SH);
    CalloutHandle handle(getCalloutManager());
    Pkt6Ptr pkt6 = generatePkt6();
    handle.setArgument("query6", pkt6);
    Lease6Ptr lease6 = generateLease6();
    handle.setArgument("lease6", lease6);
    int ret;
    ASSERT_NO_THROW(ret = lease6_decline(handle));
    EXPECT_EQ(0, ret);
    checkScriptResult();
}

} // end of anonymous namespace
