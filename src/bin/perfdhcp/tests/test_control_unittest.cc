// Copyright (C) 2012-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include "command_options_helper.h"
#include "../test_control.h"

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>

#include <cstddef>
#include <stdint.h>
#include <string>
#include <fstream>
#include <gtest/gtest.h>

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

    /// \brief Incremental transaction id generator.
    ///
    /// This is incremental transaction id generator. It overrides
    /// the default transaction id generator that generates transaction
    /// ids using random function. This generator will generate values
    /// like: 1,2,3 etc.
    class IncrementalGenerator : public TestControl::NumberGenerator {
    public:
        /// \brief Default constructor.
        IncrementalGenerator() :
            NumberGenerator(),
            transid_(0) {
        }

        /// \brief Generate unique transaction id.
        ///
        /// Generate unique transaction ids incrementally:
        /// 1,2,3,4 etc.
        ///
        /// \return generated transaction id.
        virtual uint32_t generate() {
            return (++transid_);
        }

        /// \brief Return next transaction id value.
        uint32_t getNext() const {
            return (transid_ + 1);
        }

    private:
        uint32_t transid_; ///< Last generated transaction id.
    };

    /// \brief Sets the due times for sedning Solicit, Renew and Release.
    ///
    /// There are three class members that hold the due time for sending DHCP
    /// messages:
    /// - send_due_ - due time to send Solicit,
    /// - renew_due_ - due time to send Renew,
    /// - release_due_ - due time to send Release.
    /// Some tests in this test suite need to modify these values relative to
    /// the current time. This function modifies this values using time
    /// offset values (positive or negative) specified as a difference in
    /// seconds between current time and the due time.
    ///
    /// \param send_secs An offset of the due time for Solicit.
    /// \param renew_secs An offset of the due time for Renew.
    /// \param release_secs An offset of the due time for Release.
    void setRelativeDueTimes(const int send_secs, const int renew_secs = 0,
                             const int release_secs = 0) {
        ptime now = microsec_clock::universal_time();
        basic_rate_control_.setRelativeDue(send_secs);
        renew_rate_control_.setRelativeDue(renew_secs);
        release_rate_control_.setRelativeDue(release_secs);

    }

    using TestControl::checkExitConditions;
    using TestControl::createMessageFromReply;
    using TestControl::createRequestFromAck;
    using TestControl::factoryElapsedTime6;
    using TestControl::factoryGeneric;
    using TestControl::factoryIana6;
    using TestControl::factoryOptionRequestOption6;
    using TestControl::factoryRapidCommit6;
    using TestControl::factoryRequestList4;
    using TestControl::generateDuid;
    using TestControl::generateMacAddress;
    using TestControl::getCurrentTimeout;
    using TestControl::getTemplateBuffer;
    using TestControl::initPacketTemplates;
    using TestControl::initializeStatsMgr;
    using TestControl::openSocket;
    using TestControl::processReceivedPacket4;
    using TestControl::processReceivedPacket6;
    using TestControl::registerOptionFactories;
    using TestControl::reset;
    using TestControl::sendDiscover4;
    using TestControl::sendPackets;
    using TestControl::sendMultipleRequests;
    using TestControl::sendMultipleMessages6;
    using TestControl::sendRequest6;
    using TestControl::sendSolicit6;
    using TestControl::setDefaults4;
    using TestControl::setDefaults6;
    using TestControl::basic_rate_control_;
    using TestControl::renew_rate_control_;
    using TestControl::release_rate_control_;
    using TestControl::last_report_;
    using TestControl::transid_gen_;
    using TestControl::macaddr_gen_;
    using TestControl::first_packet_serverid_;
    using TestControl::interrupted_;

    NakedTestControl() : TestControl() {
        uint32_t clients_num = CommandOptions::instance().getClientsNum() == 0 ?
            1 : CommandOptions::instance().getClientsNum();
        setMacAddrGenerator(NumberGeneratorPtr(new TestControl::SequentialGenerator(clients_num)));
    };

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

    /// \brief Create packet template file from binary data.
    ///
    /// Function creates file containing data from the provided buffer
    /// in hexadecimal format. The size parameter specifies the maximum
    /// size of the file. If total number of hexadecimal digits resulting
    /// from buffer size is greater than maximum file size the file is
    /// truncated.
    ///
    /// \param filename template file to be created.
    /// \param buffer with binary data to be stored in file.
    /// \param size target size of the file.
    /// \param invalid_chars inject invalid chars to the template file.
    /// \return true if file creation successful.
    bool createTemplateFile(const std::string& filename,
                            const std::vector<uint8_t>& buf,
                            const size_t size,
                            const bool invalid_chars = false) const {
        std::ofstream temp_file;
        temp_file.open(filename.c_str(), ios::out | ios::trunc);
        if (!temp_file.is_open()) {
            return (false);
        }
        for (size_t i = 0; i < buf.size(); ++i) {
            int first_digit = buf[i] / 16;
            int second_digit = buf[i] % 16;
            // Insert two spaces between two hexadecimal digits.
            // Spaces are allowed in template files.
            temp_file << std::string(2, ' ');
            if (2 * i + 1 < size) {
                if (!invalid_chars) {
                    temp_file << std::hex << first_digit << second_digit << std::dec;
                } else {
                    temp_file << "XY";
                }
            } else if (2 * i < size) {
                if (!invalid_chars) {
                    temp_file << std::hex << first_digit;
                } else {
                    temp_file << "X";
                }
            } else {
                break;
            }
        }
        temp_file.close();
        return (true);
    }

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
        BOOST_FOREACH(IfacePtr iface, IfaceMgr::instance().getIfaces()) {
            if (iface->flag_loopback_) {
                return (iface->getName());
            }
        }
        return ("");
    }

    /// \brief Get full path to a file in testdata directory.
    ///
    /// \param filename filename being appended to absolute
    /// path to testdata directory
    ///
    /// \return full path to a file in testdata directory.
    std::string getFullPath(const std::string& filename) const {
        std::ostringstream stream;
        stream << TEST_DATA_DIR << "/" << filename;
        return (stream.str());
    }

    /// \brief Match requested options in the buffer with given list.
    ///
    /// This method iterates through options provided in the buffer
    /// and matches them with the options specified with first parameter.
    /// Options in both vectors may be laid in different order.
    ///
    /// \param requested_options reference buffer with options.
    /// \param buf test buffer with options that will be matched.
    /// \return number of options from the buffer matched with options
    /// in the reference buffer.
    int matchRequestedOptions(const dhcp::OptionBuffer& requested_options,
                              const dhcp::OptionBuffer& buf) const {
        size_t matched_num = 0;
        for (size_t i = 0; i < buf.size(); ++i) {
            for (size_t j = 0; j < requested_options.size(); ++j) {
                if (requested_options[j] == buf[i]) {
                    // Requested option has been found.
                    ++matched_num;
                }
            }
        }
        return (matched_num);
    }

    /// \brief Match requested DHCPv6 options in the buffer with given list.
    ///
    /// This method iterates through options provided in the buffer and
    /// matches them with the options specified with first parameter.
    /// Options in both vectors ma be laid in different order.
    ///
    /// \param requested_options reference buffer with options.
    /// \param buf test buffer with options that will be matched.
    /// \return number of options from the buffer matched with options in
    /// the reference buffer or -1 if error occured.
    int matchRequestedOptions6(const dhcp::OptionBuffer& requested_options,
                               const dhcp::OptionBuffer& buf) const {
        // Sanity check.
        if ((requested_options.size() % 2 != 0) ||
            (buf.size() % 2 != 0)) {
            return -1;
        }
        size_t matched_num = 0;
        for (size_t i = 0; i < buf.size(); i += 2) {
            for (size_t j = 0; j < requested_options.size(); j += 2) {
                uint16_t opt_i = (buf[i + 1] << 8) + (buf[i] & 0xFF);
                uint16_t opt_j = (requested_options[j + 1] << 8)
                    + (requested_options[j] & 0xFF);
                if (opt_i == opt_j) {
                    // Requested option has been found.
                    ++matched_num;
                }
            }
        }
        return (matched_num);
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
    /// \param clients_num number of simulated clients
    /// \return maximum mismatch position
    int unequalOctetPosition(int clients_num) const {
        if (!clients_num) {
            return (0);
        }
        clients_num--;

        int cnt = 0;
        while (clients_num) {
            clients_num >>= 8;
            ++cnt;
        }

        return (cnt);
    }

    /// \brief Test generation of mulitple DUIDs
    ///
    /// This method checks the generation of multiple DUIDs. Number
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
        // Initialize Test Control class.
        NakedTestControl tc;
        // The old duid will be holding the previously generated DUID.
        // It will be used to compare against the new one. If we have
        // multiple clients we want to make sure that duids differ.
        uint8_t randomized = 0;
        Duid old_duid(tc.generateDuid(randomized));
        Duid new_duid(0);
        // total_dist shows the total difference between generated duid.
        // It has to be greater than zero if multiple clients are simulated.
        size_t total_dist = 0;
        // Number of unique DUIDs.
        size_t unique_duids = 0;
        // Holds the position if the octet on which two DUIDS can be different.
        // If number of clients is 256 or less it is last DUID octet (except for
        // single client when subsequent DUIDs have to be equal). If number of
        // clients is between 257 and 65536 the last two octets can differ etc.
        int unequal_pos = unequalOctetPosition(clients_num);
        // Keep generated DUIDs in this container.
        std::list<std::vector<uint8_t> > duids;
        // Perform number of iterations to generate number of DUIDs.
        for (int i = 0; i < 10 * clients_num; ++i) {
            if (new_duid.empty()) {
                new_duid = old_duid;
            } else {
                std::swap(old_duid, new_duid);
                new_duid = tc.generateDuid(randomized);
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
            for (int j = 4; j < 8; ++j) {
                duid_time |= new_duid[j] << (j - 4);
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
            // unique will inform if tested DUID is unique.
            bool unique = true;
            for (std::list<std::vector<uint8_t> >::const_iterator it =
                     duids.begin();
                 it != duids.end(); ++it) {
                // DUIDs should be of the same size if we want to compare them.
                ASSERT_EQ(new_duid.size(), it->size());
                // Check if DUID is unique.
                if (std::equal(new_duid.begin(), new_duid.end(), it->begin())) {
                    unique = false;
                }
            }
            // Expecting that DUIDs will be unique only when
            // first clients-num iterations is performed.
            // After that, DUIDs become non unique.
            if (unique) {
                ++unique_duids;
            }
            // For number of iterations equal to clients_num,2*clients_num
            // 3*clients_num ... we have to have number of unique duids
            // equal to clients_num.
            if ((i != 0) && (i % clients_num == 0)) {
                ASSERT_EQ(clients_num, unique_duids);
            }
            // Remember generated DUID.
            duids.push_back(new_duid);
        }
        // If we have more than one client at least one mismatch occured.
        if (clients_num < 2) {
            EXPECT_EQ(0, total_dist);
        }
    }

    /// \brief Test DHCPv4 exchanges.
    ///
    /// Function simulates DHCPv4 exchanges. Function caller specifies
    /// number of exchanges to be simulated and number of simulated
    /// responses. When number of responses is lower than number of
    /// iterations than the difference between them is the number
    /// of simulated packet drops. This is useful to test if program
    /// exit conditions are handled properly (maximum number of packet
    /// drops specified as -D<max-drops> is taken into account).
    ///
    /// \param iterations_num number of exchanges to simulate.
    /// \param receive_num number of received OFFER packets.
    /// \param iterations_performed actual number of iterations.
    void testPkt4Exchange(int iterations_num,
                          int receive_num,
                          bool use_templates,
                          int& iterations_performed) const {
        int sock_handle = 0;
        NakedTestControl tc;
        tc.initializeStatsMgr();

        // Use templates files to crate packets.
        if (use_templates) {
            tc.initPacketTemplates();
            ASSERT_NO_THROW(tc.getTemplateBuffer(0));
            ASSERT_NO_THROW(tc.getTemplateBuffer(1));
        }

        // Incremental transaction id generator will generate
        // predictable values of transaction id for each iteration.
        // This is important because we need to simulate responses
        // from the server and use the same transaction ids as in
        // packets sent by client.
        TestControl::NumberGeneratorPtr
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);
        // Socket is needed to send packets through the interface.
        ASSERT_NO_THROW(sock_handle = tc.openSocket());
        TestControl::TestControlSocket sock(sock_handle);
        uint32_t transid = 0;
        for (int i = 0; i < iterations_num; ++i) {
            if (use_templates) {
                ASSERT_NO_THROW(tc.sendDiscover4(sock, tc.getTemplateBuffer(0)));
            } else {
                ASSERT_NO_THROW(tc.sendDiscover4(sock));
            }
            ++transid;
            // Do not simulate responses for packets later
            // that specified as receive_num. This simulates
            // packet drops.
            if (i < receive_num) {
                boost::shared_ptr<Pkt4> offer_pkt4(createOfferPkt4(transid));
                ASSERT_NO_THROW(tc.processReceivedPacket4(sock, offer_pkt4));
                ++transid;
            }
            if (tc.checkExitConditions()) {
                iterations_performed = i + 1;
                break;
            }
            iterations_performed = i + 1;
        }
    }

    /// \brief Test DHCPv6 exchanges.
    ///
    /// Function simulates DHCPv6 exchanges. Function caller specifies
    /// number of exchanges to be simulated and number of simulated
    /// responses. When number of responses is lower than number of
    /// iterations than the difference between them is the number
    /// of simulated packet drops. This is useful to test if program
    /// exit conditions are handled properly (maximum number of packet
    /// drops specified as -D<max-drops> is taken into account).
    ///
    /// \param iterations_num number of exchanges to simulate.
    /// \param receive_num number of received OFFER packets.
    /// \param iterations_performed actual number of iterations.
    void testPkt6Exchange(int iterations_num,
                          int receive_num,
                          bool use_templates,
                          int& iterations_performed) const {
        int sock_handle = 0;
        NakedTestControl tc;
        tc.initializeStatsMgr();

        // Use templates files to crate packets.
        if (use_templates) {
            tc.initPacketTemplates();
            ASSERT_NO_THROW(tc.getTemplateBuffer(0));
            ASSERT_NO_THROW(tc.getTemplateBuffer(1));
        }

        // Incremental transaction id generator will generate
        // predictable values of transaction id for each iteration.
        // This is important because we need to simulate responses
        // from the server and use the same transaction ids as in
        // packets sent by client.
        TestControl::NumberGeneratorPtr
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);
        // Socket is needed to send packets through the interface.
        ASSERT_NO_THROW(sock_handle = tc.openSocket());
        TestControl::TestControlSocket sock(sock_handle);
        uint32_t transid = 0;
        for (int i = 0; i < iterations_num; ++i) {
            // Do not simulate responses for packets later
            // that specified as receive_num. This simulates
            // packet drops.
            if (use_templates) {
                ASSERT_NO_THROW(tc.sendSolicit6(sock, tc.getTemplateBuffer(0)));
            } else {
                ASSERT_NO_THROW(tc.sendSolicit6(sock));
            }
            ++transid;
            if (i < receive_num) {
                boost::shared_ptr<Pkt6>
                    advertise_pkt6(createAdvertisePkt6(transid));
                // Receive ADVERTISE and send REQUEST.
                ASSERT_NO_THROW(tc.processReceivedPacket6(sock,
                                                          advertise_pkt6));
                ++transid;
            }
            if (tc.checkExitConditions()) {
                iterations_performed = i + 1;
                break;
            }
            iterations_performed = i + 1;
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
        MacAddress old_mac(CommandOptions::instance().getMacTemplate());
        // Holds the position if the octet on which two MAC addresses can
        // be different. If number of clients is 256 or less it is last MAC
        // octet (except for single client when subsequent MAC addresses
        // have to be equal). If number of clients is between 257 and 65536
        // the last two octets can differ etc.
        int unequal_pos = unequalOctetPosition(clients_num);
        // Number of unique MACs.
        size_t unique_macs = 0;
        // Initialize Test Controller.
        NakedTestControl tc;
        size_t total_dist = 0;
        // Keep generated MACs in this container.
        std::list<std::vector<uint8_t> > macs;
        // Do many iterations to generate and test MAC address values.
        for (int i = 0; i < clients_num * 10; ++i) {
            // Generate new MAC address.
            uint8_t randomized = 0;
            MacAddress new_mac(tc.generateMacAddress(randomized));
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
            // unique will inform if tested DUID is unique.
            bool unique = true;
            for (std::list<std::vector<uint8_t> >::const_iterator it =
                     macs.begin();
                 it != macs.end(); ++it) {
                // MACs should be of the same size if we want to compare them.
                ASSERT_EQ(new_mac.size(), it->size());
                // Check if MAC is unique.
                if (std::equal(new_mac.begin(), new_mac.end(), it->begin())) {
                    unique = false;
                }
            }
            // Expecting that MACs will be unique only when
            // first clients-num iterations is performed.
            // After that, MACs become non unique.
            if (unique) {
                ++unique_macs;
            }
            // For number of iterations equal to clients_num,2*clients_num
            // 3*clients_num ... we have to have number of unique MACs
            // equal to clients_num.
            if ((i != 0) && (i % clients_num == 0)) {
                ASSERT_EQ(clients_num, unique_macs);
            }
            // Remember generated MAC.
            macs.push_back(new_mac);

        }
        if (clients_num < 2)  {
            EXPECT_EQ(total_dist, 0);
        }
    }

    /// \brief Test sending DHCPv4 renews.
    ///
    /// This function simulates acquiring 10 leases from the server. Returned
    /// DHCPACK messages are cached and used to send renew messages.
    /// The maxmimal number of messages which can be sent is equal to the
    /// number of leases acquired (10). This function also checks that an
    /// attempt to send more renew messages than the number of leases acquired
    /// will fail.
    void testSendRenew4() {
        std::string loopback_iface(getLocalLoopback());
        if (loopback_iface.empty()) {
            std::cout << "Skipping the test because loopback interface could"
                " not be detected" << std::endl;
            return;
        }
        // Build a command line. Depending on the message type, we will use
        // -f<renew-rate> or -F<release-rate> parameter.
        std::ostringstream s;
        s << "perfdhcp -4 -l " << loopback_iface << " -r 10 -f";
        s << " 10 -R 10 -L 10067 -n 10 127.0.0.1";
        ASSERT_NO_THROW(processCmdLine(s.str()));
        // Create a test controller class.
        NakedTestControl tc;
        tc.initializeStatsMgr();
        // Set the transaction id generator to sequential to control to
        // guarantee that transaction ids are predictable.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);
        // Socket has to be created so as we can actually send packets.
        int sock_handle = 0;
        ASSERT_NO_THROW(sock_handle = tc.openSocket());
        TestControl::TestControlSocket sock(sock_handle);

        // Send a number of DHCPDISCOVER messages. Each generated message will
        // be assigned a different transaction id, starting from 1 to 10.
        tc.sendPackets(sock, 10);

        // Simulate DHCPOFFER responses from the server. Each DHCPOFFER is
        // assigned a transaction id from the range of 1 to 10, so as they
        // match the transaction ids from the DHCPDISCOVER messages.
        for (unsigned i = generator->getNext() - 10;
             i < generator->getNext(); ++i) {
            Pkt4Ptr offer(createOfferPkt4(i));
            // If DHCPOFFER is matched with the DHCPDISCOVER the call below
            // will trigger a corresponding DHCPREQUEST. They will be assigned
            // transaction ids from the range from 11 to 20 (the range of
            // 1 to 10 has been used by DHCPDISCOVER-DHCPOFFER).
            ASSERT_NO_THROW(tc.processReceivedPacket4(sock, offer));
    }

        // Requests have been sent, so now let's simulate responses from the
        // server. Generate corresponding DHCPACK messages with the transaction
        // ids from the range from 11 to 20.
        for (unsigned i = generator->getNext() - 10;
             i < generator->getNext(); ++i) {
            Pkt4Ptr ack(createAckPkt4(i));
            // Each DHCPACK packet corresponds to the new lease acquired. Since
            // -f<renew-rate> option has been specified, received Reply
            // messages are held so as renew messages can be sent for
            // existing leases.
            ASSERT_NO_THROW(tc.processReceivedPacket4(sock, ack));
        }

        uint64_t msg_num;
        // Try to send 5 messages. It should be successful because 10
        // DHCPREQUEST messages has been received. For each of them we
        // should be able to send renewal.
        ASSERT_NO_THROW(
            msg_num = tc.sendMultipleRequests(sock, 5)
        );
        // Make sure that we have sent 5 messages.
        EXPECT_EQ(5, msg_num);

        // Try to do it again. We should still have 5 Reply packets for
        // which renews haven't been sent yet.
        ASSERT_NO_THROW(
            msg_num = tc.sendMultipleRequests(sock, 5)
        );
        EXPECT_EQ(5, msg_num);

        // We used all the DHCPACK packets (we sent renew or release for each of
        // them already). Therefore, no further renew messages should be sent
        // before we acquire new leases.
        ASSERT_NO_THROW(
            msg_num = tc.sendMultipleRequests(sock, 5)
        );
        // Make sure that no message has been sent.
        EXPECT_EQ(0, msg_num);
    }

    /// \brief Test that the DHCPREQUEST message is created correctly and
    /// comprises expected values.
    void testCreateRequest() {
        // This command line specifies that the Release/Renew messages should
        // be sent with the same rate as the Solicit messages.
        std::ostringstream s;
        s << "perfdhcp -4 -l lo -r 10 -f 10";
        s << " -R 10 -L 10067 -n 10 127.0.0.1";
        ASSERT_NO_THROW(processCmdLine(s.str()));
        // Create a test controller class.
        NakedTestControl tc;
        // Set the transaction id generator which will be used by the
        // createRenew or createRelease function to generate transaction id.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);

        Pkt4Ptr ack = createAckPkt4(1);

        // Create DHCPREQUST from DHCPACK.
        Pkt4Ptr request;
        ASSERT_NO_THROW(request = tc.createRequestFromAck(ack));

        // Make sure that the DHCPACK has been successfully created and that
        // it holds expected data.
        ASSERT_TRUE(request);
        EXPECT_EQ("127.0.0.1", request->getCiaddr().toText());

        // HW address.
        HWAddrPtr hwaddr_ack = ack->getHWAddr();
        ASSERT_TRUE(hwaddr_ack);
        HWAddrPtr hwaddr_req = request->getHWAddr();
        ASSERT_TRUE(hwaddr_req);
        EXPECT_TRUE(hwaddr_ack->hwaddr_ == hwaddr_req->hwaddr_);
    }

    /// \brief Test that the DHCPv6 Release or Renew message is created
    /// correctly and comprises expected options.
    ///
    /// \param msg_type A type of the message to be tested: DHCPV6_RELEASE
    /// or DHCPV6_RENEW.
    void testCreateRenewRelease(const uint16_t msg_type) {
        // This command line specifies that the Release/Renew messages should
        // be sent with the same rate as the Solicit messages.
        std::ostringstream s;
        s << "perfdhcp -6 -l lo -r 10 ";
        s << (msg_type == DHCPV6_RELEASE ? "-F" : "-f") << " 10 ";
        s << "-R 10 -L 10547 -n 10 -e address-and-prefix ::1";
        ASSERT_NO_THROW(processCmdLine(s.str()));
        // Create a test controller class.
        NakedTestControl tc;
        // Set the transaction id generator which will be used by the
        // createRenew or createRelease function to generate transaction id.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);

        // Create a Reply packet. The createRelease or createReply function will
        // need Reply packet to create a corresponding Release or Reply.
        Pkt6Ptr reply = createReplyPkt6(1);

        Pkt6Ptr msg;
        // Check that the message is created.
        ASSERT_NO_THROW(msg = tc.createMessageFromReply(msg_type, reply));

        ASSERT_TRUE(msg);
        // Check that the message type and transaction id is correct.
        EXPECT_EQ(msg_type, msg->getType());
        EXPECT_EQ(1, msg->getTransid());

        // Check that the message has expected options. These are the same for
        // Release and Renew.

        // Client Identifier.
        OptionPtr opt_clientid = msg->getOption(D6O_CLIENTID);
        ASSERT_TRUE(opt_clientid);
        EXPECT_TRUE(reply->getOption(D6O_CLIENTID)->getData() ==
                    opt_clientid->getData());

        // Server identifier
        OptionPtr opt_serverid = msg->getOption(D6O_SERVERID);
        ASSERT_TRUE(opt_serverid);
        EXPECT_TRUE(reply->getOption(D6O_SERVERID)->getData() ==
                opt_serverid->getData());

        // IA_NA
        OptionPtr opt_ia_na = msg->getOption(D6O_IA_NA);
        ASSERT_TRUE(opt_ia_na);
        EXPECT_TRUE(reply->getOption(D6O_IA_NA)->getData() ==
                    opt_ia_na->getData());

        // IA_PD
        OptionPtr opt_ia_pd = msg->getOption(D6O_IA_PD);
        ASSERT_TRUE(opt_ia_pd);
        EXPECT_TRUE(reply->getOption(D6O_IA_PD)->getData() ==
                    opt_ia_pd->getData());

        // Make sure that exception is thrown if the Reply message is NULL.
        EXPECT_THROW(tc.createMessageFromReply(msg_type, Pkt6Ptr()),
                     isc::BadValue);

    }

    /// \brief Test sending DHCPv6 Releases or Renews.
    ///
    /// This function simulates acquiring 10 leases from the server. Returned
    /// Reply messages are cached and used to send Renew or Release messages.
    /// The maxmimal number of Renew or Release messages which can be sent is
    /// equal to the number of leases acquired (10). This function also checks
    /// that an attempt to send more Renew or Release messages than the number
    /// of leases acquired will fail.
    ///
    /// \param msg_type A type of the message which is simulated to be sent
    /// (DHCPV6_RENEW or DHCPV6_RELEASE).
    void testSendRenewRelease(const uint16_t msg_type) {
        std::string loopback_iface(getLocalLoopback());
        if (loopback_iface.empty()) {
            std::cout << "Skipping the test because loopback interface could"
                " not be detected" << std::endl;
            return;
        }
        // Build a command line. Depending on the message type, we will use
        // -f<renew-rate> or -F<release-rate> parameter.
        std::ostringstream s;
        s << "perfdhcp -6 -l " << loopback_iface << " -r 10 ";
        s << (msg_type == DHCPV6_RENEW ? "-f" : "-F");
        s << " 10 -R 10 -L 10547 -n 10 ::1";
        ASSERT_NO_THROW(processCmdLine(s.str()));
        // Create a test controller class.
        NakedTestControl tc;
        tc.initializeStatsMgr();
        // Set the transaction id generator to sequential to control to
        // guarantee that transaction ids are predictable.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);
        // Socket has to be created so as we can actually send packets.
        int sock_handle = 0;
        ASSERT_NO_THROW(sock_handle = tc.openSocket());
        TestControl::TestControlSocket sock(sock_handle);

        // Send a number of Solicit messages. Each generated Solicit will be
        // assigned a different transaction id, starting from 1 to 10.
        tc.sendPackets(sock, 10);

        // Simulate Advertise responses from the server. Each advertise is
        // assigned a transaction id from the range of 1 to 10, so as they
        // match the transaction ids from the Solicit messages.
        for (unsigned i = generator->getNext() - 10;
             i < generator->getNext(); ++i) {
            Pkt6Ptr advertise(createAdvertisePkt6(i));
            // If Advertise is matched with the Solicit the call below will
            // trigger a corresponding Request. They will be assigned
            // transaction ids from the range from 11 to 20 (the range of
            // 1 to 10 has been used by Solicit-Advertise).
            ASSERT_NO_THROW(tc.processReceivedPacket6(sock, advertise));
    }

        // Requests have been sent, so now let's simulate responses from the
        // server. Generate corresponding Reply messages with the transaction
        // ids from the range from 11 to 20.
        for (unsigned i = generator->getNext() - 10;
             i < generator->getNext(); ++i) {
            Pkt6Ptr reply(createReplyPkt6(i));
            // Each Reply packet corresponds to the new lease acquired. Since
            // -f<renew-rate> option has been specified, received Reply
            // messages are held so as Renew messages can be sent for
            // existing leases.
            ASSERT_NO_THROW(tc.processReceivedPacket6(sock, reply));
        }

        uint64_t msg_num;
        // Try to send 5 messages. It should be successful because 10 Reply
        // messages has been received. For each of them we should be able to
        // send Renew or Release.
        ASSERT_NO_THROW(
            msg_num = tc.sendMultipleMessages6(sock, msg_type, 5)
        );
        // Make sure that we have sent 5 messages.
        EXPECT_EQ(5, msg_num);

        // Try to do it again. We should still have 5 Reply packets for
        // which Renews or Releases haven't been sent yet.
        ASSERT_NO_THROW(
            msg_num = tc.sendMultipleMessages6(sock, msg_type, 5)
        );
        EXPECT_EQ(5, msg_num);

        // We used all the Reply packets (we sent Renew or Release for each of
        // them already). Therefore, no further Renew or Release messages should
        // be sent before we acquire new leases.
        ASSERT_NO_THROW(
            msg_num = tc.sendMultipleMessages6(sock, msg_type, 5)
        );
        // Make sure that no message has been sent.
        EXPECT_EQ(0, msg_num);

    }

    /// \brief Parse command line string with CommandOptions.
    ///
    /// \param cmdline command line string to be parsed.
    /// \throw isc::Unexpected if unexpected error occured.
    /// \throw isc::InvalidParameter if command line is invalid.
    void processCmdLine(const std::string& cmdline) const {
        CommandOptionsHelper::process(cmdline);
    }

    /// \brief Create DHCPOFFER or DHCPACK packet.
    ///
    /// \param pkt_type DHCPOFFER or DHCPACK.
    /// \param transid Transaction id.
    ///
    /// \return Instance of the packet.
    Pkt4Ptr
    createResponsePkt4(const uint8_t pkt_type,
                       const uint32_t transid) const {
        Pkt4Ptr pkt(new Pkt4(pkt_type, transid));
        OptionPtr opt_serverid = Option::factory(Option::V4,
                                                 DHO_DHCP_SERVER_IDENTIFIER,
                                                 OptionBuffer(4, 1));
        pkt->setYiaddr(asiolink::IOAddress("127.0.0.1"));
        pkt->addOption(opt_serverid);
        pkt->updateTimestamp();
        return (pkt);
    }

    /// \brief Create DHCPv4 OFFER packet.
    ///
    /// \param transid transaction id.
    /// \return instance of the packet.
    Pkt4Ptr
    createOfferPkt4(uint32_t transid) const {
        return (createResponsePkt4(DHCPOFFER, transid));
    }

    /// \brief Create DHCPACK packet.
    ///
    /// \param transid transaction id.
    /// \return instance of the packet.
    Pkt4Ptr
    createAckPkt4(const uint32_t transid) const {
        return (createResponsePkt4(DHCPACK, transid));
    }

    /// \brief Create DHCPv6 ADVERTISE packet.
    ///
    /// \param transid transaction id.
    /// \return instance of the packet.
    Pkt6Ptr
    createAdvertisePkt6(const uint32_t transid) const {
        boost::shared_ptr<Pkt6> advertise(new Pkt6(DHCPV6_ADVERTISE, transid));
        // Add IA_NA if requested by the client.
        if (CommandOptions::instance().getLeaseType()
            .includes(CommandOptions::LeaseType::ADDRESS)) {
            OptionPtr opt_ia_na = Option::factory(Option::V6, D6O_IA_NA);
            advertise->addOption(opt_ia_na);
        }
        // Add IA_PD if requested by the client.
        if (CommandOptions::instance().getLeaseType()
            .includes(CommandOptions::LeaseType::PREFIX)) {
            OptionPtr opt_ia_pd = Option::factory(Option::V6, D6O_IA_PD);
            advertise->addOption(opt_ia_pd);
        }
        OptionPtr opt_serverid(new Option(Option::V6, D6O_SERVERID));
        NakedTestControl tc;
        uint8_t randomized = 0;
        std::vector<uint8_t> duid(tc.generateDuid(randomized));
        OptionPtr opt_clientid(Option::factory(Option::V6, D6O_CLIENTID, duid));
        advertise->addOption(opt_serverid);
        advertise->addOption(opt_clientid);
        advertise->updateTimestamp();
        return (advertise);
    }

    Pkt6Ptr
    createReplyPkt6(const uint32_t transid) const {
        Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, transid));
        // Add IA_NA if requested by the client.
        if (CommandOptions::instance().getLeaseType()
            .includes(CommandOptions::LeaseType::ADDRESS)) {
            OptionPtr opt_ia_na = Option::factory(Option::V6, D6O_IA_NA);
            reply->addOption(opt_ia_na);
        }
        // Add IA_PD if requested by the client.
        if (CommandOptions::instance().getLeaseType()
            .includes(CommandOptions::LeaseType::PREFIX)) {
            OptionPtr opt_ia_pd = Option::factory(Option::V6, D6O_IA_PD);
            reply->addOption(opt_ia_pd);
        }
        OptionPtr opt_serverid(new Option(Option::V6, D6O_SERVERID));
        NakedTestControl tc;
        uint8_t randomized = 0;
        std::vector<uint8_t> duid(tc.generateDuid(randomized));
        OptionPtr opt_clientid(Option::factory(Option::V6, D6O_CLIENTID, duid));
        reply->addOption(opt_serverid);
        reply->addOption(opt_clientid);
        reply->updateTimestamp();
        return (reply);

    }

};

// This test verifies that the class members are reset to expected values.
TEST_F(TestControlTest, reset) {
    ASSERT_NO_THROW(processCmdLine("perfdhcp -6 -l ethx -r 50 -f 30 -F 10 -a 3 all"));
    NakedTestControl tc;
    tc.reset();
    EXPECT_EQ(3, tc.basic_rate_control_.getAggressivity());
    EXPECT_EQ(3, tc.renew_rate_control_.getAggressivity());
    EXPECT_EQ(3, tc.release_rate_control_.getAggressivity());
    EXPECT_EQ(50, tc.basic_rate_control_.getRate());
    EXPECT_EQ(30, tc.renew_rate_control_.getRate());
    EXPECT_EQ(10, tc.release_rate_control_.getRate());
    EXPECT_FALSE(tc.last_report_.is_not_a_date_time());
    EXPECT_FALSE(tc.transid_gen_);
    EXPECT_FALSE(tc.macaddr_gen_);
    EXPECT_TRUE(tc.first_packet_serverid_.empty());
    EXPECT_FALSE(tc.interrupted_);

}

TEST_F(TestControlTest, GenerateDuid) {
    // Simple command line that simulates one client only. Always the
    // same DUID will be generated.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 all"));
    testDuid();

    // Simulate 50 clients. Different DUID will be generated.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 -R 50 all"));
    testDuid();
}

TEST_F(TestControlTest, MisMatchVerionServer) {
    NakedTestControl tc;

    // make sure we catch -6 paired with v4 address
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 -6 192.168.1.1"));
    EXPECT_THROW(tc.openSocket(), isc::InvalidParameter);

    // make sure we catch -4 paired with v6 address
    ASSERT_NO_THROW(processCmdLine("perfdhcp -l 127.0.0.1 -4 ff02::1:2"));
    EXPECT_THROW(tc.openSocket(), isc::InvalidParameter);
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
    // different in general so we need to search each value separately.
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
    OptionBuffer duid(CommandOptions::instance().getDuidTemplate());
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
        0, D6O_NAME_SERVERS,
        0, D6O_DOMAIN_SEARCH
    };
    // Each option code in ORO is 2 bytes long. We calculate the number of
    // requested options by dividing the size of the buffer holding options
    // by the size of each individual option.
    int requested_options_num = sizeof(requested_options) / sizeof(uint16_t);
    OptionBuffer
        requested_options_ref(requested_options,
                              requested_options + sizeof(requested_options));
    // Get the buffer from option.
    const OptionBuffer& requested_options_buf = opt_oro->getData();
    // Size of reference buffer and option buffer have to be
    // the same for comparison.
    EXPECT_EQ(requested_options_ref.size(), requested_options_buf.size());
    // Check if all options in the buffer are matched with reference buffer.
    size_t matched_num = matchRequestedOptions6(requested_options_ref,
                                                requested_options_buf);
    EXPECT_EQ(requested_options_num, matched_num);

    // Validate the D6O_IA_NA option.
    OptionPtr opt_ia_na(Option::factory(Option::V6, D6O_IA_NA));
    EXPECT_EQ(Option::V6, opt_ia_na->getUniverse());
    EXPECT_EQ(D6O_IA_NA, opt_ia_na->getType());
    // Every IA_NA option is expected to start with this sequence.
    const uint8_t opt_ia_na_array[] = {
        0, 0, 0, 1,                     // IAID = 1
        0, 0, 3600 >> 8, 3600 & 0xff,  // T1 = 3600
        0, 0, 5400 >> 8, 5400 & 0xff,   // T2 = 5400
    };
    OptionBuffer opt_ia_na_ref(opt_ia_na_array,
                               opt_ia_na_array + sizeof(opt_ia_na_array));
    const OptionBuffer& opt_ia_na_buf = opt_ia_na->getData();
    ASSERT_EQ(opt_ia_na_buf.size(), opt_ia_na_ref.size());
    EXPECT_TRUE(std::equal(opt_ia_na_ref.begin(), opt_ia_na_ref.end(),
                           opt_ia_na_buf.begin()));

    // @todo Add more tests for IA address options.
}

TEST_F(TestControlTest, Packet4) {
    // Use Interface Manager to get the local loopback interface.
    // If interface can't be found we don't want to fail test.
    std::string loopback_iface(getLocalLoopback());
    if (!loopback_iface.empty()) {
        ASSERT_NO_THROW(processCmdLine("perfdhcp -l " + loopback_iface +
                                       " -L 10547 all"));
        NakedTestControl tc;
        int sock_handle = 0;
        // We have to create the socket to setup some parameters of
        // outgoing packet.
        ASSERT_NO_THROW(sock_handle = tc.openSocket());
        TestControl::TestControlSocket sock(sock_handle);
        uint32_t transid = 123;
        boost::shared_ptr<Pkt4> pkt4(new Pkt4(DHCPDISCOVER, transid));
        // Set parameters on outgoing packet.
        ASSERT_NO_THROW(tc.setDefaults4(sock, pkt4));
        // Validate that packet has been setup correctly.
        EXPECT_EQ(loopback_iface, pkt4->getIface());
        EXPECT_EQ(sock.ifindex_, pkt4->getIndex());
        EXPECT_EQ(DHCP4_CLIENT_PORT, pkt4->getLocalPort());
        EXPECT_EQ(DHCP4_SERVER_PORT, pkt4->getRemotePort());
        EXPECT_EQ(1, pkt4->getHops());
        EXPECT_EQ(asiolink::IOAddress("255.255.255.255"),
                  pkt4->getRemoteAddr());
        EXPECT_EQ(asiolink::IOAddress(sock.addr_), pkt4->getLocalAddr());
        EXPECT_EQ(asiolink::IOAddress(sock.addr_), pkt4->getGiaddr());
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
                                       " -L 10547 servers"));
        NakedTestControl tc;
        int sock_handle = 0;
        // Create the socket. It will be needed to set packet's
        // parameters.
        ASSERT_NO_THROW(sock_handle = tc.openSocket());
        TestControl::TestControlSocket sock(sock_handle);
        uint32_t transid = 123;
        boost::shared_ptr<Pkt6> pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
        // Set packet's parameters.
        ASSERT_NO_THROW(tc.setDefaults6(sock, pkt6));
        // Validate if parameters have been set correctly.
        EXPECT_EQ(loopback_iface, pkt6->getIface());
        EXPECT_EQ(sock.ifindex_, pkt6->getIndex());
        EXPECT_EQ(DHCP6_CLIENT_PORT, pkt6->getLocalPort());
        EXPECT_EQ(DHCP6_SERVER_PORT, pkt6->getRemotePort());
        EXPECT_EQ(sock.addr_, pkt6->getLocalAddr());
        EXPECT_EQ(asiolink::IOAddress("FF05::1:3"), pkt6->getRemoteAddr());
    } else {
        std::cout << "Unable to find the loopback interface. Skip test. "
                  << std::endl;
    }
}

TEST_F(TestControlTest, Packet4Exchange) {
    // Get the local loopback interface to open socket on
    // it and test packets exchanges. We don't want to fail
    // the test if interface is not available.
    std::string loopback_iface(getLocalLoopback());
    if (loopback_iface.empty()) {
        std::cout << "Unable to find the loopback interface. Skip test."
                  << std::endl;
        return;
    }

    // Set number of iterations to some high value.
    const int iterations_num = 100;
    processCmdLine("perfdhcp -l " + loopback_iface
                   + " -r 100 -n 10 -R 20 -L 10547 127.0.0.1");
    // The actual number of iterations will be stored in the
    // following variable.
    int iterations_performed = 0;
    bool use_templates = false;
    testPkt4Exchange(iterations_num, iterations_num, use_templates, iterations_performed);
    // The command line restricts the number of iterations to 10
    // with -n 10 parameter.
    EXPECT_EQ(10, iterations_performed);

    // With the following command line we restrict the maximum
    // number of dropped packets to 20% of all.
    // Use templates for this test.
    processCmdLine("perfdhcp -l " + loopback_iface
                   + " -r 100 -R 20 -n 20 -D 10% -L 10547"
                   + " -T " + getFullPath("discover-example.hex")
                   + " -T " + getFullPath("request4-example.hex")
                   + " 127.0.0.1");
    // The number iterations is restricted by the percentage of
    // dropped packets (-D 10%). We also have to bump up the number
    // of iterations because the percentage limitation checks starts
    // at packet #10. We expect that at packet #12 the 10% threshold
    // will be reached.
    const int received_num = 10;
    use_templates = true;
    testPkt4Exchange(iterations_num, received_num, use_templates, iterations_performed);
    EXPECT_EQ(12, iterations_performed);
}

TEST_F(TestControlTest, Packet6ExchangeFromTemplate) {
    // Get the local loopback interface to open socket on
    // it and test packets exchanges. We don't want to fail
    // the test if interface is not available.
    std::string loopback_iface(getLocalLoopback());
    if (loopback_iface.empty()) {
        std::cout << "Unable to find the loopback interface. Skip test."
                  << std::endl;
        return;
    }

    const int iterations_num = 100;
    // Set number of iterations to 10.
    processCmdLine("perfdhcp -l " + loopback_iface
                   + " -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    int iterations_performed = 0;
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    bool use_templates = false;
    testPkt6Exchange(iterations_num, iterations_num, use_templates,
                     iterations_performed);
    // Actual number of iterations should be 10.
    EXPECT_EQ(10, iterations_performed);

    // The maximum number of dropped packets is 3 (because of -D 3).
    use_templates = true;
    processCmdLine("perfdhcp -l " + loopback_iface
                   + " -6 -r 100 -n 10 -R 20 -D 3 -L 10547"
                   + " -T " + getFullPath("solicit-example.hex")
                   + " -T " + getFullPath("request6-example.hex ::1"));
    // For the first 3 packets we are simulating responses from server.
    // For other packets we don't so packet as 4,5,6 will be dropped and
    // then test should be interrupted and actual number of iterations will
    // be 6.
    const int received_num = 3;
    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) echanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. The number of exchanges
    // actually performed is returned in 'iterations_performed' argument. If
    // processing is successful, the number of performed iterations should be
    // equal to the number of exchanges specified with the '-n' command line
    // parameter (10 in this case). All exchanged packets carry the IA_NA option
    // to simulate the IPv6 address acquisition and to verify that the
    // IA_NA options returned by the server are processed correctly.
    testPkt6Exchange(iterations_num, received_num, use_templates,
                     iterations_performed);
    EXPECT_EQ(6, iterations_performed);
}

TEST_F(TestControlTest, Packet6Exchange) {
    // Get the local loopback interface to open socket on
    // it and test packets exchanges. We don't want to fail
    // the test if interface is not available.
    std::string loopback_iface(getLocalLoopback());
    if (loopback_iface.empty()) {
        std::cout << "Unable to find the loopback interface. Skip test."
                  << std::endl;
        return;
    }

    const int iterations_num = 100;
    // Set number of iterations to 10.
    processCmdLine("perfdhcp -l " + loopback_iface
                   + " -e address-only"
                   + " -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    int iterations_performed = 0;
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    bool use_templates = false;

    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) echanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. The number of exchanges
    // actually performed is returned in 'iterations_performed' argument. If
    // processing is successful, the number of performed iterations should be
    // equal to the number of exchanges specified with the '-n' command line
    // parameter (10 in this case). All exchanged packets carry the IA_NA option
    // to simulate the IPv6 address acqusition and to verify that the IA_NA
    // options returned by the server are processed correctly.
    testPkt6Exchange(iterations_num, iterations_num, use_templates,
                     iterations_performed);
    // Actual number of iterations should be 10.
    EXPECT_EQ(10, iterations_performed);
}

TEST_F(TestControlTest, Packet6ExchangePrefixDelegation) {
    // Get the local loopback interface to open socket on
    // it and test packets exchanges. We don't want to fail
    // the test if interface is not available.
    std::string loopback_iface(getLocalLoopback());
    if (loopback_iface.empty()) {
        std::cout << "Unable to find the loopback interface. Skip test."
                  << std::endl;
        return;
    }

    const int iterations_num = 100;
    // Set number of iterations to 10.
    processCmdLine("perfdhcp -l " + loopback_iface
                   + " -e prefix-only"
                   + " -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    int iterations_performed = 0;
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    bool use_templates = false;

    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) echanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. The number of exchanges
    // actually performed is returned in 'iterations_performed' argument. If
    // processing is successful, the number of performed iterations should be
    // equal to the number of exchanges specified with the '-n' command line
    // parameter (10 in this case). All exchanged packets carry the IA_PD option
    // to simulate the Prefix Delegation and to verify that the IA_PD options
    // returned by the server are processed correctly.
    testPkt6Exchange(iterations_num, iterations_num, use_templates,
                     iterations_performed);
    // Actual number of iterations should be 10.
    EXPECT_EQ(10, iterations_performed);
}

TEST_F(TestControlTest, Packet6ExchangeAddressAndPrefix) {
    // Get the local loopback interface to open socket on
    // it and test packets exchanges. We don't want to fail
    // the test if interface is not available.
    std::string loopback_iface(getLocalLoopback());
    if (loopback_iface.empty()) {
        std::cout << "Unable to find the loopback interface. Skip test."
                  << std::endl;
        return;
    }

    const int iterations_num = 100;
    // Set number of iterations to 10.
    processCmdLine("perfdhcp -l " + loopback_iface
                   + " -e address-and-prefix"
                   + " -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    int iterations_performed = 0;
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    bool use_templates = false;
    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) echanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. The number of exchanges
    // actually performed is returned in 'iterations_performed' argument. If
    // processing is successful, the number of performed iterations should be
    // equal to the number of exchanges specified with the '-n' command line
    // parameter (10 in this case).  All exchanged packets carry either IA_NA
    // or IA_PD options to simulate the address and prefix acquisition with
    // the single message and to verify that the IA_NA and IA_PD options
    // returned by the server are processed correctly.
    testPkt6Exchange(iterations_num, iterations_num, use_templates,
                     iterations_performed);
    // Actual number of iterations should be 10.
    EXPECT_EQ(10, iterations_performed);
}

TEST_F(TestControlTest, PacketTemplates) {
    std::vector<uint8_t> template1(256);
    std::string file1("test1.hex");
    std::vector<uint8_t> template2(233);
    std::string file2("test2.hex");
    for (size_t i = 0; i < template1.size(); ++i) {
        template1[i] = static_cast<uint8_t>(random() % 256);
    }
    for (size_t i = 0; i < template2.size(); ++i) {
        template2[i] = static_cast<uint8_t>(random() % 256);
    }
    // Size of the file is 2 times larger than binary data size.
    ASSERT_TRUE(createTemplateFile(file1, template1, template1.size() * 2));
    ASSERT_TRUE(createTemplateFile(file2, template2, template2.size() * 2));

    NakedTestControl tc;

    ASSERT_NO_THROW(
        processCmdLine("perfdhcp -l 127.0.0.1"
                       " -T " + file1 + " -T " + file2 + " all")
    );
    ASSERT_NO_THROW(tc.initPacketTemplates());
    TestControl::TemplateBuffer buf1;
    TestControl::TemplateBuffer buf2;
    ASSERT_NO_THROW(buf1 = tc.getTemplateBuffer(0));
    ASSERT_NO_THROW(buf2 = tc.getTemplateBuffer(1));
    ASSERT_EQ(template1.size(), buf1.size());
    ASSERT_EQ(template2.size(), buf2.size());
    EXPECT_TRUE(std::equal(template1.begin(), template1.end(), buf1.begin()));
    EXPECT_TRUE(std::equal(template2.begin(), template2.end(), buf2.begin()));

    // Try to read template file with odd number of digits.
    std::string file3("test3.hex");
    // Size of the file is 2 times larger than binary data size and it is always
    // even number. Substracting 1 makes file size odd.
    ASSERT_TRUE(createTemplateFile(file3, template1, template1.size() * 2 - 1));
    ASSERT_NO_THROW(
        processCmdLine("perfdhcp -l 127.0.0.1 -T " + file3 + " all")
    );
    EXPECT_THROW(tc.initPacketTemplates(), isc::OutOfRange);

    // Try to read empty file.
    std::string file4("test4.hex");
    ASSERT_TRUE(createTemplateFile(file4, template2, 0));
    ASSERT_NO_THROW(
        processCmdLine("perfdhcp -l 127.0.0.1 -T " + file4 + " all")
    );
    EXPECT_THROW(tc.initPacketTemplates(), isc::OutOfRange);

    // Try reading file with non hexadecimal characters.
    std::string file5("test5.hex");
    ASSERT_TRUE(createTemplateFile(file5, template1, template1.size() * 2, true));
    ASSERT_NO_THROW(
        processCmdLine("perfdhcp -l 127.0.0.1 -T " + file5 + " all")
    );
    EXPECT_THROW(tc.initPacketTemplates(), isc::BadValue);
}

// This test verifies that DHCPv4 renew (DHCPREQUEST) messages can be
// sent for acquired leases.
TEST_F(TestControlTest, processRenew4) {
    testSendRenew4();
}

// This test verifies that DHCPv6 Renew messages can be sent for acquired
// leases.
TEST_F(TestControlTest, processRenew6) {
    testSendRenewRelease(DHCPV6_RENEW);
}

// This test verifies that DHCPv6 Release messages can be sent for acquired
// leases.
TEST_F(TestControlTest, processRelease6) {
    testSendRenewRelease(DHCPV6_RELEASE);
}

// This test verifies that DHCPREQUEST is created correctly from the
// DHCPACK message.
TEST_F(TestControlTest, createRequest) {
    testCreateRequest();
}

// This test verifies that the DHCPV6 Renew message is created correctly
// and that it comprises all required options.
TEST_F(TestControlTest, createRenew) {
    testCreateRenewRelease(DHCPV6_RENEW);
}

// This test verifies that the DHCPv6 Release message is created correctly
// and that it comprises all required options.
TEST_F(TestControlTest, createRelease) {
    testCreateRenewRelease(DHCPV6_RELEASE);
}

// This test verifies that the current timeout value for waiting for
// the server's responses is valid. The timeout value corresponds to the
// time period between now and the next message to be sent from the
// perfdhcp to a server.
TEST_F(TestControlTest, getCurrentTimeout) {
    // Process the command line: set the rate for Discovers to 10,
    // and set Renew rate to 0 (-f flag absent).
    ASSERT_NO_THROW(processCmdLine("perfdhcp -4 -l lo -r 10 ::1"));
    NakedTestControl tc;
    // Make sure that the renew rate is 0.
    ASSERT_EQ(0, CommandOptions::instance().getRenewRate());
    // Simulate the case when we are already behind the due time for
    // the next Discover to be sent.
    tc.setRelativeDueTimes(-3);
    // Expected timeout value is 0, which means that perfdhcp should
    // not wait for server's response but rather send the next
    // message to a server immediately.
    EXPECT_EQ(0, tc.getCurrentTimeout());
    // Now, let's do set the due time to a value in the future. The returned
    // timeout value should be somewhere between now and this time in the
    // future. The value of ten seconds ahead should be safe and guarantee
    // that the returned timeout value is non-zero, even though there is a
    // delay between setting the send_due_ value and invoking the function.
    tc.setRelativeDueTimes(10);
    uint32_t timeout = tc.getCurrentTimeout();
    EXPECT_GT(timeout, 0);
    EXPECT_LE(timeout, 10000000);
}

// This test verifies that the current timeout value for waiting for the
// server's responses is valid. In this case, we are simulating that perfdhcp
// sends Renew requests to the server, apart from the regular 4-way exchanges.
// The timeout value depends on both the due time to send next Solicit and the
// due time to send Renew - the timeout should be ajusted to the due time that
// occurs sooner.
TEST_F(TestControlTest, getCurrentTimeoutRenew) {
    // Set the Solicit rate to 10 and the Renew rate 5.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -6 -l lo -r 10 -f 5 ::1"));
    NakedTestControl tc;

    // Make sure, that the Renew rate has been set to 5.
    ASSERT_EQ(5, CommandOptions::instance().getRenewRate());
    // The send_due_ is in the past, the renew_due_ is in the future.
    tc.setRelativeDueTimes(-3, 3);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    // Swap the due times from the previous check. The effect should be the
    // same.
    tc.setRelativeDueTimes(3, -3);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    // Set both due times to the future. The renew due time is to occur
    // sooner. The timeout should be a value between now and the
    // renew due time.
    tc.setRelativeDueTimes(10, 5);
    EXPECT_GT(tc.getCurrentTimeout(), 0);
    EXPECT_LE(tc.getCurrentTimeout(), 5000000);

    // Repeat the same check, but swap the due times.
    tc.setRelativeDueTimes(5, 10);
    EXPECT_GT(tc.getCurrentTimeout(), 0);
    EXPECT_LE(tc.getCurrentTimeout(), 5000000);

}

// This test verifies that the current timeout value for waiting for the
// server's responses is valid. In this case, we are simulating that perfdhcp
// sends Release requests to the server, apart from the regular 4-way exchanges.
TEST_F(TestControlTest, getCurrentTimeoutRelease) {
    // Set the Solicit rate to 10 and the Release rate 5.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -6 -l lo -r 10 -F 5 ::1"));
    NakedTestControl tc;

    // Make sure, that the Release rate has been set to 5.
    ASSERT_EQ(5, CommandOptions::instance().getReleaseRate());
    // The send_due_ is in the past, the renew_due_ is in the future.
    tc.setRelativeDueTimes(-3, 0, 3);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    // Swap the due times from the previous check. The effect should be the
    // same.
    tc.setRelativeDueTimes(3, 0, -3);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    // Set both due times to the future. The renew due time is to occur
    // sooner. The timeout should be a value between now and the
    // release due time.
    tc.setRelativeDueTimes(10, 0, 5);
    EXPECT_GT(tc.getCurrentTimeout(), 0);
    EXPECT_LE(tc.getCurrentTimeout(), 5000000);

    // Repeat the same check, but swap the due times.
    tc.setRelativeDueTimes(5, 0, 10);
    EXPECT_GT(tc.getCurrentTimeout(), 0);
    EXPECT_LE(tc.getCurrentTimeout(), 5000000);

}

// This test verifies that the current timeout value for waiting for the
// server's responses is valid. In this case, we are simulating that perfdhcp
// sends both Renew and Release requests to the server, apart from the regular
// 4-way exchanges.
TEST_F(TestControlTest, getCurrentTimeoutRenewRelease) {
    // Set the Solicit rate to 10 and, Renew rate to 5, Release rate to 3.
    ASSERT_NO_THROW(processCmdLine("perfdhcp -6 -l lo -r 10 -f 5 -F 3 ::1"));
    NakedTestControl tc;

    // Make sure the Renew and Release rates has been set to a non-zero value.
    ASSERT_EQ(5, CommandOptions::instance().getRenewRate());
    ASSERT_EQ(3, CommandOptions::instance().getReleaseRate());

    // If any of the due times is in the past, the timeout value should be 0,
    // to indicate that the next message should be sent immediately.
    tc.setRelativeDueTimes(-3, 3, 5);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    tc.setRelativeDueTimes(-3, 5, 3);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    tc.setRelativeDueTimes(3, -3, 5);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    tc.setRelativeDueTimes(3, 2, -5);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    tc.setRelativeDueTimes(-3, -2, -5);
    EXPECT_EQ(0, tc.getCurrentTimeout());

    // If due times are in the future, the timeout value should be aligned to
    // the due time which occurs the soonest.
    tc.setRelativeDueTimes(10, 9, 8);
    EXPECT_GT(tc.getCurrentTimeout(), 0);
    EXPECT_LE(tc.getCurrentTimeout(), 8000000);

    tc.setRelativeDueTimes(10, 8, 9);
    EXPECT_GT(tc.getCurrentTimeout(), 0);
    EXPECT_LE(tc.getCurrentTimeout(), 8000000);

    tc.setRelativeDueTimes(5, 8, 9);
    EXPECT_GT(tc.getCurrentTimeout(), 0);
    EXPECT_LE(tc.getCurrentTimeout(), 5000000);

}
