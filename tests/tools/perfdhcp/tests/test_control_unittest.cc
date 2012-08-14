// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <cstddef>
#include <stdint.h>
#include <string>
#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include "command_options_helper.h"
#include "../test_control.h"

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

/// \brief Test Control class with protected members made public.
///
/// This class makes protected TestControl class'es member public
/// to allow unit testing.
class NakedTestControl: public TestControl {
public:
    using TestControl::checkExitConditions;
    using TestControl::factoryElapsedTime6;
    using TestControl::factoryGeneric;
    using TestControl::factoryIana6;
    using TestControl::factoryOptionRequestOption6;
    using TestControl::factoryRapidCommit6;
    using TestControl::factoryRequestList4;
    using TestControl::generateDuid;
    using TestControl::generateMacAddress;
    using TestControl::getNextExchangesNum;
    using TestControl::openSocket;
    using TestControl::receivePackets;
    using TestControl::registerOptionFactories;
    using TestControl::sendDiscover4;
    using TestControl::sendSolicit6;
    using TestControl::setDefaults4;
    using TestControl::setDefaults6;
    using TestControl::updateSendDue;

    NakedTestControl() : TestControl() { };

};

/// \brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on perfdhcp TestControl class.
class TestControlTest : public virtual ::testing::Test
{
public:

    typedef std::vector<uint8_t> MacAddress;
    typedef MacAddress::iterator MacAddressIterator;

    typedef std::vector<uint8_t> Duid;
    typedef Duid::iterator DuidIterator;

    /// \brief Default Constructor
    TestControlTest() { }

    /// \brief Get local loopback interface name.
    ///
    /// Scan available network interfaces for local loopback
    /// interface and get its name. On Linux this interface is
    /// usually called 'lo' but on other systems, e.g. BSD
    /// it will have slightly different name. Local loopback
    /// interface is required for unit tests that require
    /// socket creation.
    ///
    /// \return local loopback interface name.
    std::string getLocalLoopback() const {
        const IfaceMgr::IfaceCollection& ifaces =
            IfaceMgr::instance().getIfaces();
        for (IfaceMgr::IfaceCollection::const_iterator iface = ifaces.begin();
             iface != ifaces.end();
             ++iface) {
            for (IfaceMgr::AddressCollection::const_iterator addr_it =
                     iface->getAddresses().begin();
                 addr_it != iface->getAddresses().end();
                 ++addr_it) {
                if (asiolink::IOAddress("127.0.0.1").getAddress() ==
                    addr_it->getAddress()) {
                    return iface->getName();
                }
            }
        }
        return("");
    }

    /// \brief Match requested options in the buffer with given list.
    ///
    /// This method iterates through options provided in the buffer
    /// and matches them with the options specified with first parameter.
    /// Options in both vectors may be layed in different order.
    ///
    /// \param requested_options reference buffer with options.
    /// \param buf test buffer with options that will be matched.
    /// \return number of options from the buffer matched with options
    /// in the reference buffer.
    int matchRequestedOptions(const dhcp::OptionBuffer& requested_options,
                              const dhcp::OptionBuffer& buf) const {
        size_t matched_num = 0;
        for (size_t i = 0; i < buf.size(); ++i) {
            for (int j = 0; j < requested_options.size(); ++j) {
                if (requested_options[j] == buf[i]) {
                    // Requested option has been found.
                    ++matched_num;
                    break;
                }
            }
        }
        return matched_num;
    }

    /// \brief Calculate the maximum vectors' mismatch position.
    ///
    /// This helper function calculates the maximum mismatch position
    /// between two vectors (two different DUIDs or MAC addresses).
    /// Calculated position is counted from the end of vectors.
    /// Calculation is based on number of simulated clients. When number
    /// of clients is less than 256 different DUIDs or MAC addresses can
    /// can be coded in such a way that they differ on last vector element.
    /// If number of clients is between 257 and 65536 they can differ
    /// on two last positions so the returned value will be 2 and so on.
    ///
    /// \param clients_num number of simulated clinets
    /// \param randomization range - for either MAC or DUID it is 6
    /// \return maximum mismatch position
    int unequalOctetPosition(const int clients_num,
                             const size_t random_size) const {
        int unequal_pos = 0;
        int n = clients_num - 1;
        if (n > 0) {
            for (int i = 0; i < random_size; ++i) {
                if (n < 256) {
                    unequal_pos = i + 1;
                    break;
                }
                n %= 256;
            }
        }
        return unequal_pos;
    }

    /// brief Test generation of mulitple DUIDs
    ///
    /// Thie method checks the generation of multiple DUIDs. Number
    /// of iterations depends on the number of simulated clients.
    /// It is expected that DUID's size is 14 (consists of DUID-LLT
    /// HW type field, 4 octets of time value and MAC address). The
    /// MAC address can be randomized depending on the number of
    /// simulated clients. The DUID-LLT and HW type are expected to
    /// be constant. The time value has to be properly calculated
    /// as the number of seconds since DUID time epoch. The parts
    /// of MAC address has to change if multiple clients are simulated
    /// and do not change if single client is simulated.
    void testDuid() const {
        int clients_num = CommandOptions::instance().getClientsNum();
        // The old duid will be holding the previously generated DUID.
        // It will be used to compare against the new one. If we have
        // multiple clients we want to make sure that duids differ.
        Duid old_duid(CommandOptions::instance().getDuidPrefix());
        Duid new_duid(0);
        // total_dist shows the total difference between generated duid.
        // It has to be greater than zero if multiple clients are simulated.
        size_t total_dist = 0;
        // Holds the position if the octet on which two DUIDS can be different.
        // If number of clients is 256 or less it is last DUID octet (except for
        // single client when subsequent DUIDs have to be equal). If number of
        // clients is between 257 and 65536 the last two octets can differ etc.
        const size_t mac_addr_size = 6;
        int unequal_pos = unequalOctetPosition(clients_num, mac_addr_size);

        // Initialize Test Control class.
        NakedTestControl tc;
        // Perform number of iterations to generate number of DUIDs.
        // If single clinet is involved, try multiple times (10) and
        // see if the same DUID is always generated.
        for (int i = 0; i < clients_num * 10; ++i) {
            if (new_duid.empty()) {
                new_duid = old_duid;
            } else {
                std::swap(old_duid, new_duid);
                new_duid = tc.generateDuid();
            }
            // The DUID-LLT is expected to start with DUID_LLT value
            // of 1 and hardware ethernet type equal to 1 (HWETHER_TYPE).
            const uint8_t duid_llt_and_hw[4] = { 0x0, 0x1, 0x0, 0x1 };
            // We assume DUID-LLT length 14. This includes 4 octets of
            // DUID_LLT value, two octets of hardware type, 4 octets
            // of time value and 6 octets of variable link layer (MAC)
            // address.
            const int duid_llt_size = 14;
            ASSERT_EQ(duid_llt_size, new_duid.size());
            // The first four octets do not change.
            EXPECT_TRUE(std::equal(new_duid.begin(), new_duid.begin() + 4,
                                   duid_llt_and_hw));

            // As described in RFC3315: 'the time value is the time
            // that the DUID is generated represented in seconds
            // since midnight (UTC), January 1, 2000, modulo 2^32.'
            uint32_t duid_time = 0;
            // Pick 4 bytes of the time from generated DUID and put them
            // in reverse order (in DUID they are stored in network order).
            for (int i = 4; i < 8; ++i) {
                duid_time |= new_duid[i] << (i - 4);
            }
            // Calculate the duration since epoch time.
            ptime now = microsec_clock::universal_time();
            ptime duid_epoch(from_iso_string("20000101T000000"));
            time_period period(duid_epoch, now);

            // Current time is the same or later than time from the DUID because
            // DUID had been generated before reference duration was calculated.
            EXPECT_GE(period.length().total_seconds(), duid_time);

            // Get the mismatch position (counting from the end) of
            // mismatched octet between previously generated DUID
            // and current.
            std::pair<DuidIterator, DuidIterator> mismatch_pos =
                std::mismatch(old_duid.begin(), old_duid.end(),
                              new_duid.begin());
            size_t mismatch_dist =
                std::distance(mismatch_pos.first, old_duid.end());
            // For single client total_dist is expected to be 0 because
            // old_duid and new_duid should always match. If we have
            // more clients then duids have to differ except the case
            // if randomization algorithm generates the same values but
            // this would be an error in randomization algorithm.
            total_dist += mismatch_dist;
            // Mismatch may have occured on the DUID octet position
            // up to calculated earlier unequal_pos.
            ASSERT_LE(mismatch_dist, unequal_pos);
        }
        // If we have more than one client at least one mismatch occured.
        if (clients_num > 1) {
            EXPECT_GT(total_dist, 0);
        } else {
            EXPECT_EQ(0, total_dist);
        }
    }

    /// \brief Test generation of multiple MAC addresses.
    ///
    /// This method validates generation of multiple MAC addresses.
    /// The MAC address can be randomized depending on  the number
    /// of simulated clients. This test checks if different MAC
    /// addresses are generated if number of simulated clients is
    /// greater than 1. It also checks if the same MAC addresses is
    /// generated if only 1 client is simulated.
    void testMacAddress() const {
        int clients_num = CommandOptions::instance().getClientsNum();
        // The old_mac will be holding the value of previously generated
        // MAC address. We will be comparing the newly generated one with it
        // to see if it changes when mulitple clients are simulated or if it
        // does not change when single client is simulated.
        MacAddress old_mac(CommandOptions::instance().getMacPrefix());
        // Holds the position if the octet on which two MAC addresses can
        // be different. If number of clients is 256 or less it is last MAC
        // octet (except for single client when subsequent MAC addresses
        // have to be equal). If number of clients is between 257 and 65536
        // the last two octets can differ etc.
        int unequal_pos = unequalOctetPosition(clients_num, old_mac.size());;

        NakedTestControl tc;
        size_t total_dist = 0;
        // Do many iterations to generate and test MAC address values.
        for (int i = 0; i < clients_num * 10; ++i) {
            // Generate new MAC address.
            MacAddress new_mac(tc.generateMacAddress());
            // Get the mismatch position (counting from the end) of
            // mismatched octet between previously generated MAC address
            // and current.
            std::pair<MacAddressIterator, MacAddressIterator> mismatch_pos =
                std::mismatch(old_mac.begin(), old_mac.end(), new_mac.begin());
            size_t mismatch_dist =
                std::distance(mismatch_pos.first, old_mac.end());
            // For single client total_dist is expected to be 0 because
            // old_mac and new_mac should always match. If we have
            // more clients then MAC addresses have to differ except
            // the case if randomization algorithm generates the same
            // values but this would be an error in randomization algorithm.
            total_dist += mismatch_dist;
            // Mismatch may have occured on the MAC address'es octet position
            // up to calculated earlier unequal_pos.
            ASSERT_LE(mismatch_dist, unequal_pos);
        }
        // If we have more than one client at least one mismatch occured.
        if (clients_num > 1) {
            EXPECT_GT(total_dist, 0);
        } else {
            EXPECT_EQ(total_dist, 0);
        }
    }

    /// \brief Parse command line string with CommandOptions.
    ///
    /// \param cmdline command line string to be parsed.
    /// \throw isc::Unexpected if unexpected error occured.
    /// \throw isc::InvalidParameter if command line is invalid.
    void processCmdLine(const std::string& cmdline) const {
        CommandOptionsHelper::process(cmdline);
    }

};

TEST_F(TestControlTest, GenerateDuid) {
    // Simple command line that simulates one client only. Always the
    // same DUID will be generated.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 all"));
    testDuid();

    // Simulate 50 clients. Different DUID will be generated.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 -R 50 all"));
    testDuid();
}

TEST_F(TestControlTest, GenerateMacAddress) {
    // Simulate one client only. Always the same MAC address will be
    // generated.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 all"));
    testMacAddress();

    // Simulate 50 clients. Different MAC addresses will be generated.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 -R 50 all"));
    testMacAddress();
}

TEST_F(TestControlTest, Options4) {
    using namespace isc::dhcp;
    NakedTestControl tc;
    // By default the IP version mode is V4 so there is no need to
    // parse command line to override the IP version. Note that
    // registerOptionFactories is used for both V4 and V6.
    tc.registerOptionFactories();
    // Create option with buffer size equal to 1 and holding DHCPDISCOVER
    // message type.
    OptionPtr opt_msg_type(Option::factory(Option::V4, DHO_DHCP_MESSAGE_TYPE,
                                           OptionBuffer(1, DHCPDISCOVER)));
    // Validate the option type and universe.
    EXPECT_EQ(Option::V4, opt_msg_type->getUniverse());
    EXPECT_EQ(DHO_DHCP_MESSAGE_TYPE, opt_msg_type->getType());
    // Validate the message type from the option we have now created.
    uint8_t msg_type = 0;
    ASSERT_NO_THROW(msg_type = opt_msg_type->getUint8());
    EXPECT_EQ(DHCPDISCOVER, msg_type);

    // Create another option: DHCP_PARAMETER_REQUEST_LIST
    OptionPtr
        opt_requested_options(Option::factory(Option::V4,
                                              DHO_DHCP_PARAMETER_REQUEST_LIST));
    // Here is a list of options that we are requesting in the
    // server's response.
    const uint8_t requested_options[] = {
        DHO_SUBNET_MASK,
        DHO_BROADCAST_ADDRESS,
        DHO_TIME_OFFSET,
        DHO_ROUTERS,
        DHO_DOMAIN_NAME,
        DHO_DOMAIN_NAME_SERVERS,
        DHO_HOST_NAME
    };

    OptionBuffer
        requested_options_ref(requested_options,
                              requested_options + sizeof(requested_options));

    // Get the option buffer. It should hold the combination of values
    // listed in requested_options array. However their order can be
    // different in general so we need to search each value separatelly.
    const OptionBuffer& requested_options_buf =
        opt_requested_options->getData();
    EXPECT_EQ(requested_options_ref.size(), requested_options_buf.size());
    size_t matched_num = matchRequestedOptions(requested_options_ref,
                                               requested_options_buf);
    // We want exactly the same requested options as listed in
    // requested_options array - nothing more or less.
    EXPECT_EQ(requested_options_ref.size(), matched_num);
}

TEST_F(TestControlTest, Options6) {
    using namespace isc::dhcp;

    // Lets override the IP version to test V6 options (-6 parameter)
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 -6 all"));

    NakedTestControl tc;
    tc.registerOptionFactories();

    // Validate the D6O_ELAPSED_TIME option.
    OptionPtr opt_elapsed_time(Option::factory(Option::V6, D6O_ELAPSED_TIME));
    // Validate the option type and universe.
    EXPECT_EQ(Option::V6, opt_elapsed_time->getUniverse());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt_elapsed_time->getType());
    // The default value of elapsed time is zero.
    uint16_t elapsed_time;
    ASSERT_NO_THROW(elapsed_time = opt_elapsed_time->getUint16());
    EXPECT_EQ(0, elapsed_time);

    // With the factory function we may also specify the actual
    // value of elapsed time. Let's make use of std::vector
    // constructor to create the option buffer, 2 octets long
    // with each octet initialized to 0x1.
    size_t elapsed_time_buf_size = 2;
    uint8_t elapsed_time_pattern = 0x1;
    OptionPtr
        opt_elapsed_time2(Option::factory(Option::V6, D6O_ELAPSED_TIME,
                                          OptionBuffer(elapsed_time_buf_size,
                                                       elapsed_time_pattern)));

    // Any buffer that has size neither equal to 0 nor 2 is considered invalid.
    elapsed_time_buf_size = 1;
    EXPECT_THROW(
        Option::factory(Option::V6, D6O_ELAPSED_TIME,
                        OptionBuffer(elapsed_time_buf_size, elapsed_time_pattern)),
        isc::BadValue
    );

    // Validate the option type and universe.
    EXPECT_EQ(Option::V6, opt_elapsed_time2->getUniverse());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt_elapsed_time2->getType());
    // Make sure the getUint16 does not throw exception. It wile throw
    // buffer is shorter than 2 octets.
    ASSERT_NO_THROW(elapsed_time = opt_elapsed_time2->getUint16());
    // Check the expected value of elapsed time.
    EXPECT_EQ(0x0101, elapsed_time);

    // Validate the D6O_RAPID_COMMIT option.
    OptionPtr opt_rapid_commit(Option::factory(Option::V6, D6O_RAPID_COMMIT));
    // Validate the option type and universe.
    EXPECT_EQ(Option::V6, opt_rapid_commit->getUniverse());
    EXPECT_EQ(D6O_RAPID_COMMIT, opt_rapid_commit->getType());
    // Rapid commit has no data payload.
    EXPECT_THROW(opt_rapid_commit->getUint8(), isc::OutOfRange);

    // Validate the D6O_CLIENTID option.
    OptionBuffer duid(CommandOptions::instance().getDuidPrefix());
    OptionPtr opt_clientid(Option::factory(Option::V6, D6O_CLIENTID, duid));
    EXPECT_EQ(Option::V6, opt_clientid->getUniverse());
    EXPECT_EQ(D6O_CLIENTID, opt_clientid->getType());
    const OptionBuffer& duid2 = opt_clientid->getData();
    ASSERT_EQ(duid.size(), duid2.size());
    // The Duid we set for option is the same we get.
    EXPECT_TRUE(std::equal(duid.begin(), duid.end(), duid2.begin()));

    // Validate the D6O_ORO (Option Request Option).
    OptionPtr opt_oro(Option::factory(Option::V6, D6O_ORO));
    // Prepare the reference buffer with requested options.
    const uint8_t requested_options[] = {
        D6O_NAME_SERVERS,
        D6O_DOMAIN_SEARCH
    };
    OptionBuffer
        requested_options_ref(requested_options,
                              requested_options + sizeof(requested_options));
    // Get the buffer from option.
    const OptionBuffer& requested_options_buf = opt_oro->getData();
    // Size of reference buffer and option buffer have to be
    // the same for comparison.
    EXPECT_EQ(requested_options_ref.size(), requested_options_buf.size());
    // Check if all options in the buffer are matched with reference buffer.
    size_t matched_num = matchRequestedOptions(requested_options_ref,
                                               requested_options_buf);
    EXPECT_EQ(sizeof(requested_options), matched_num);

    // Validate the D6O_IA_NA option.
    OptionPtr opt_ia_na(Option::factory(Option::V6, D6O_IA_NA));
    EXPECT_EQ(Option::V6, opt_ia_na->getUniverse());
    EXPECT_EQ(D6O_IA_NA, opt_ia_na->getType());
    // Every IA_NA option is expected to start with this sequence.
    const uint8_t opt_ia_na_array[] = {
        0, 0, 0, 1,                     // IAID = 1
        0, 0, 3600 >> 8, 3600 && 0xff,  // T1 = 3600
        0, 0, 5400 >> 8, 5400 & 0xff,   // T2 = 5400
    };
    OptionBuffer opt_ia_na_ref(opt_ia_na_array,
                               opt_ia_na_array + sizeof(opt_ia_na_array));
    const OptionBuffer& opt_ia_na_buf = opt_ia_na->getData();
    ASSERT_EQ(opt_ia_na_buf.size(), opt_ia_na_ref.size());
    EXPECT_TRUE(std::equal(opt_ia_na_ref.begin(), opt_ia_na_ref.end(),
                           opt_ia_na_buf.begin()));

    // TODO: Add more tests for IA address options.
}

TEST_F(TestControlTest, Packet4) {
    // Use Interface Manager to get the local loopback interface.
    // If interface can't be found we don't want to fail test.
    std::string loopback_iface(getLocalLoopback());
    if (!loopback_iface.empty()) {
        ASSERT_NO_THROW(processCmdLine("perfdhcp -l " + loopback_iface +
                                       " all"));
        uint16_t port = 10547;
        NakedTestControl tc;
        int sock_handle = 0;
        // We have to create the socket to setup some parameters of
        // outgoing packet.
        ASSERT_NO_THROW(sock_handle = tc.openSocket(port));
        TestControl::TestControlSocket sock(sock_handle);
        uint32_t transid = 123;
        boost::shared_ptr<Pkt4> pkt4(new Pkt4(DHCPDISCOVER, transid));
        // Set parameters on outgoing packet.
        ASSERT_NO_THROW(tc.setDefaults4(sock, pkt4));
        // Validate that packet has been setup correctly.
        EXPECT_EQ(loopback_iface, pkt4->getIface());
        EXPECT_EQ(sock.getIfIndex(), pkt4->getIndex());
        EXPECT_EQ(DHCP4_CLIENT_PORT, pkt4->getLocalPort());
        EXPECT_EQ(DHCP4_SERVER_PORT, pkt4->getRemotePort());
        EXPECT_EQ(1, pkt4->getHops());
        EXPECT_EQ(asiolink::IOAddress("255.255.255.255"),
                  pkt4->getRemoteAddr());
        EXPECT_EQ(asiolink::IOAddress(sock.getAddress()), pkt4->getLocalAddr());
        EXPECT_EQ(asiolink::IOAddress(sock.getAddress()), pkt4->getGiaddr());
    } else {
        std::cout << "Unable to find the loopback interface. Skip test. "
                  << std::endl;
    }
}

TEST_F(TestControlTest, Packet6) {
    // Use Interface Manager to get the local loopback interface.
    // If the interface can't be found we don't want to fail test.
    std::string loopback_iface(getLocalLoopback());
    if (!loopback_iface.empty()) {
        ASSERT_NO_THROW(processCmdLine("perfdhcp -6 -l " + loopback_iface +
                                       " servers"));
        uint16_t port = 10547;
        NakedTestControl tc;
        int sock_handle = 0;
        // Create the socket. It will be needed to set packet's
        // parameters.
        ASSERT_NO_THROW(sock_handle = tc.openSocket(port));
        TestControl::TestControlSocket sock(sock_handle);
        uint32_t transid = 123;
        boost::shared_ptr<Pkt6> pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
        // Set packet's parameters.
        ASSERT_NO_THROW(tc.setDefaults6(sock, pkt6));
        // Validate if parameters have been set correctly.
        EXPECT_EQ(loopback_iface, pkt6->getIface());
        EXPECT_EQ(sock.getIfIndex(), pkt6->getIndex());
        EXPECT_EQ(DHCP6_CLIENT_PORT, pkt6->getLocalPort());
        EXPECT_EQ(DHCP6_SERVER_PORT, pkt6->getRemotePort());
        EXPECT_EQ(sock.getAddress(), pkt6->getLocalAddr());
        EXPECT_EQ(asiolink::IOAddress("FF05::1:3"), pkt6->getRemoteAddr());
    } else {
        std::cout << "Unable to find the loopback interface. Skip test. "
                  << std::endl;
    }
}

TEST_F(TestControlTest, RateControl) {
    // We don't specify the exchange rate here so the aggressivity
    // value will determine how many packets are to be send each
    // time we query the getNextExchangesNum.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 all"));
    CommandOptions& options = CommandOptions::instance();

    NakedTestControl tc1;
    uint64_t xchgs_num = tc1.getNextExchangesNum();
    EXPECT_EQ(options.getAggressivity(), xchgs_num);

    // The exchange rate is now 1 per second. We don't know how many
    // exchanges have to initiated exactly but for sure it has to be
    // non-zero value. Also, since aggressivity is very high we expect
    // that it will not be restricted by aggressivity.
    ASSERT_NO_THROW(
        processCmdLine("perfdhcp -l 127.0.0.1 -a 1000000 -r 1 all")
    );
    NakedTestControl tc2;
    xchgs_num = tc2.getNextExchangesNum();
    EXPECT_GT(xchgs_num, 0);
    EXPECT_LT(xchgs_num, options.getAggressivity());
}
