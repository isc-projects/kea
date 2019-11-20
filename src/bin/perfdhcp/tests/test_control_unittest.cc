// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/pkt4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
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

/// \brief FakePerfSocket class that mocks PerfSocket.
///
/// It stubs send and receive operations and collects statistics.
class FakeTestControlPerfSocket: public BasePerfSocket {
public:
    /// \brief Default constructor for FakePerfSocket.
    FakeTestControlPerfSocket() :
        iface_(boost::make_shared<Iface>("fake", 0)),
        sent_cnt_(0),
        recv_cnt_(0) {};

    IfacePtr iface_;  ///< Local fake interface.

    int sent_cnt_;  ///< Counter of sent packets
    int recv_cnt_;  ///< Counter of received packets.

    /// \brief Simulate receiving DHCPv4 packet.
    virtual dhcp::Pkt4Ptr receive4(uint32_t timeout_sec, uint32_t timeout_usec) override {
        (void)timeout_sec; // silence compile 'unused parameter' warning;
        (void)timeout_usec; // silence compile 'unused parameter' warning;
        recv_cnt_++;
        return(dhcp::Pkt4Ptr());
    };

    /// \brief Simulate receiving DHCPv6 packet.
    virtual dhcp::Pkt6Ptr receive6(uint32_t timeout_sec, uint32_t timeout_usec) override {
        (void)timeout_sec; // silence compile 'unused parameter' warning;
        (void)timeout_usec; // silence compile 'unused parameter' warning;
        recv_cnt_++;
        return(dhcp::Pkt6Ptr());
    };

    /// \brief Simulate sending DHCPv4 packet.
    virtual bool send(const dhcp::Pkt4Ptr& pkt) override {
        sent_cnt_++;
        pkt->updateTimestamp();
        return true;
    };

    /// \brief Simulate sending DHCPv6 packet.
    virtual bool send(const dhcp::Pkt6Ptr& pkt) override {
        sent_cnt_++;
        pkt->updateTimestamp();
        return true;
    };

    /// \brief Override getting interface.
    virtual IfacePtr getIface() override { return iface_; }

    void reset() {
        sent_cnt_ = 0;
        recv_cnt_ = 0;
    }
};


/// \brief Test Control class with protected members made public.
///
/// This class makes protected TestControl class's members public
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

    /// \brief Pointer to incremental generator.
    typedef boost::shared_ptr<IncrementalGenerator> IncrementalGeneratorPtr;

    using TestControl::createMessageFromReply;
    using TestControl::createRequestFromAck;
    using TestControl::factoryElapsedTime6;
    using TestControl::factoryGeneric;
    using TestControl::factoryIana6;
    using TestControl::factoryOptionRequestOption6;
    using TestControl::factoryRapidCommit6;
    using TestControl::factoryRequestList4;
    using TestControl::generateClientId;
    using TestControl::generateDuid;
    using TestControl::generateMacAddress;
    using TestControl::getTemplateBuffer;
    using TestControl::initPacketTemplates;
    using TestControl::processReceivedPacket4;
    using TestControl::processReceivedPacket6;
    using TestControl::registerOptionFactories;
    using TestControl::reset;
    using TestControl::sendDiscover4;
    using TestControl::sendRequest4;
    using TestControl::sendPackets;
    using TestControl::sendMultipleRequests;
    using TestControl::sendMultipleMessages6;
    using TestControl::sendRequest6;
    using TestControl::sendSolicit6;
    using TestControl::setDefaults4;
    using TestControl::setDefaults6;
    using TestControl::socket_;
    using TestControl::last_report_;
    using TestControl::transid_gen_;
    using TestControl::macaddr_gen_;
    using TestControl::first_packet_serverid_;
    using TestControl::interrupted_;
    using TestControl::template_packets_v4_;
    using TestControl::template_packets_v6_;
    using TestControl::ack_storage_;
    using TestControl::sendRequestFromAck;
    using TestControl::options_;
    using TestControl::stats_mgr_;

    FakeTestControlPerfSocket fake_sock_;

    NakedTestControl(CommandOptions &opt) : TestControl(opt, fake_sock_) {
        uint32_t clients_num = opt.getClientsNum() == 0 ?
            1 : opt.getClientsNum();
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
    /// the reference buffer or -1 if error occurred.
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

    /// \brief Test generation of multiple DUIDs
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
    void testDuid(CommandOptions &opt) const {
        int clients_num = opt.getClientsNum();
        // Initialize Test Control class.
        NakedTestControl tc(opt);
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

            // As described in RFC 8415: 'the time value is the time
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
            // Mismatch may have occurred on the DUID octet position
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
        // If we have more than one client at least one mismatch occurred.
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
    /// \param tc test control instance
    void testPkt4Exchange(int iterations_num,
                          int receive_num,
                          bool use_templates,
                          NakedTestControl& tc) const {
        //int sock_handle = 0;

        // Use templates files to crate packets.
        if (use_templates) {
            tc.initPacketTemplates();
            tc.getTemplateBuffer(0);
            tc.getTemplateBuffer(1);
        }

        // Incremental transaction id generator will generate
        // predictable values of transaction id for each iteration.
        // This is important because we need to simulate responses
        // from the server and use the same transaction ids as in
        // packets sent by client.
        NakedTestControl::IncrementalGeneratorPtr
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);
        for (int i = 0; i < iterations_num; ++i) {
            // Get next transaction id, without actually using it. The same
            // id wll be used by the TestControl class for DHCPDISCOVER.
            uint32_t transid = generator->getNext();
            if (use_templates) {
                tc.sendDiscover4(tc.getTemplateBuffer(0));
            } else {
                tc.sendDiscover4();
            }

            // Do not simulate responses for packets later
            // that specified as receive_num. This simulates
            // packet drops.
            if (i < receive_num) {
                boost::shared_ptr<Pkt4> offer_pkt4(createOfferPkt4(transid));
                tc.processReceivedPacket4(offer_pkt4);
            }
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
    /// \param tc test control instance
    void testPkt6Exchange(int iterations_num,
                          int receive_num,
                          bool use_templates,
                          NakedTestControl& tc) const {
        //int sock_handle = 0;

        // Use templates files to crate packets.
        if (use_templates) {
            tc.initPacketTemplates();
            tc.getTemplateBuffer(0);
            tc.getTemplateBuffer(1);
        }

        // Incremental transaction id generator will generate
        // predictable values of transaction id for each iteration.
        // This is important because we need to simulate responses
        // from the server and use the same transaction ids as in
        // packets sent by client.
        TestControl::NumberGeneratorPtr
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);
        uint32_t transid = 0;
        for (int i = 0; i < iterations_num; ++i) {
            // Do not simulate responses for packets later
            // that specified as receive_num. This simulates
            // packet drops.
            if (use_templates) {
                tc.sendSolicit6(tc.getTemplateBuffer(0));
            } else {
                tc.sendSolicit6();
            }
            ++transid;
            if (i < receive_num) {
                boost::shared_ptr<Pkt6>
                    advertise_pkt6(createAdvertisePkt6(tc, transid));
                // Receive ADVERTISE and send REQUEST.
                tc.processReceivedPacket6(advertise_pkt6);
                ++transid;
            }
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
    void testMacAddress(CommandOptions &opt) const {
        int clients_num = opt.getClientsNum();
        // The old_mac will be holding the value of previously generated
        // MAC address. We will be comparing the newly generated one with it
        // to see if it changes when multiple clients are simulated or if it
        // does not change when single client is simulated.
        MacAddress old_mac(opt.getMacTemplate());
        // Holds the position if the octet on which two MAC addresses can
        // be different. If number of clients is 256 or less it is last MAC
        // octet (except for single client when subsequent MAC addresses
        // have to be equal). If number of clients is between 257 and 65536
        // the last two octets can differ etc.
        int unequal_pos = unequalOctetPosition(clients_num);
        // Number of unique MACs.
        size_t unique_macs = 0;
        // Initialize Test Controller.
        NakedTestControl tc(opt);
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
            // Mismatch may have occurred on the MAC address's octet position
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
    /// The maximal number of messages which can be sent is equal to the
    /// number of leases acquired (10). This function also checks that an
    /// attempt to send more renew messages than the number of leases acquired
    /// will fail.
    void testSendRenew4() {
        // Build a command line. Depending on the message type, we will use
        // -f<renew-rate> or -F<release-rate> parameter.
        CommandOptions opt;
        std::ostringstream s;
        s << "perfdhcp -4 -l fake -r 10 -f";
        s << " 10 -R 10 -L 10067 -n 10 127.0.0.1";
        processCmdLine(opt, s.str());
        // Create a test controller class.
        NakedTestControl tc(opt);
        // Set the transaction id generator to sequential to control to
        // guarantee that transaction ids are predictable.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);

        // Send a number of DHCPDISCOVER messages. Each generated message will
        // be assigned a different transaction id, starting from 1 to 10.
        tc.sendPackets(10);

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
            tc.processReceivedPacket4(offer);
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
            tc.processReceivedPacket4(ack);
        }

        uint64_t msg_num;
        // Try to send 5 messages. It should be successful because 10
        // DHCPREQUEST messages has been received. For each of them we
        // should be able to send renewal.
        msg_num = tc.sendMultipleRequests(5);
        // Make sure that we have sent 5 messages.
        EXPECT_EQ(5, msg_num);

        // Try to do it again. We should still have 5 Reply packets for
        // which renews haven't been sent yet.
        msg_num = tc.sendMultipleRequests(5);
        EXPECT_EQ(5, msg_num);

        // We used all the DHCPACK packets (we sent renew or release for each of
        // them already). Therefore, no further renew messages should be sent
        // before we acquire new leases.
        msg_num = tc.sendMultipleRequests(5);
        // Make sure that no message has been sent.
        EXPECT_EQ(0, msg_num);
    }

    /// \brief Test that the DHCPREQUEST message is created correctly and
    /// comprises expected values.
    void testCreateRequest() {
        // This command line specifies that the Release/Renew messages should
        // be sent with the same rate as the Solicit messages.
        CommandOptions opt;
        std::ostringstream s;
        s << "perfdhcp -4 -l lo -r 10 -f 10";
        s << " -R 10 -L 10067 -n 10 127.0.0.1";
        processCmdLine(opt, s.str());
        // Create a test controller class.
        NakedTestControl tc(opt);
        // Set the transaction id generator which will be used by the
        // createRenew or createRelease function to generate transaction id.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);

        Pkt4Ptr ack = createAckPkt4(1);

        // Create DHCPREQUEST from DHCPACK.
        Pkt4Ptr request;
        request = tc.createRequestFromAck(ack);

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

        // Creating message from null DHCPACK should fail.
        EXPECT_THROW(tc.createRequestFromAck(Pkt4Ptr()), isc::BadValue);

        // Creating message from DHCPACK holding zero yiaddr should fail.
        asiolink::IOAddress yiaddr = ack->getYiaddr();
        ack->setYiaddr(asiolink::IOAddress::IPV4_ZERO_ADDRESS());
        EXPECT_THROW(tc.createRequestFromAck(ack), isc::BadValue);
        ack->setYiaddr(yiaddr);
    }

    /// \brief Test that the DHCPv6 Release or Renew message is created
    /// correctly and comprises expected options.
    ///
    /// \param msg_type A type of the message to be tested: DHCPV6_RELEASE
    /// or DHCPV6_RENEW.
    void testCreateRenewRelease(const uint16_t msg_type) {
        // This command line specifies that the Release/Renew messages should
        // be sent with the same rate as the Solicit messages.
        CommandOptions opt;
        std::ostringstream s;
        s << "perfdhcp -6 -l lo -r 10 ";
        s << (msg_type == DHCPV6_RELEASE ? "-F" : "-f") << " 10 ";
        s << "-R 10 -L 10547 -n 10 -e address-and-prefix ::1";
        processCmdLine(opt, s.str());
        // Create a test controller class.
        NakedTestControl tc(opt);
        // Set the transaction id generator which will be used by the
        // createRenew or createRelease function to generate transaction id.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);

        // Create a Reply packet. The createRelease or createReply function will
        // need Reply packet to create a corresponding Release or Reply.
        Pkt6Ptr reply = createReplyPkt6(tc, 1);

        Pkt6Ptr msg;
        // Check that the message is created.
        msg = tc.createMessageFromReply(msg_type, reply);

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
    /// The maximal number of Renew or Release messages which can be sent is
    /// equal to the number of leases acquired (10). This function also checks
    /// that an attempt to send more Renew or Release messages than the number
    /// of leases acquired will fail.
    ///
    /// \param msg_type A type of the message which is simulated to be sent
    /// (DHCPV6_RENEW or DHCPV6_RELEASE).
    void testSendRenewRelease(const uint16_t msg_type) {
        // Build a command line. Depending on the message type, we will use
        // -f<renew-rate> or -F<release-rate> parameter.
        CommandOptions opt;
        std::ostringstream s;
        s << "perfdhcp -6 -l fake -r 10 ";
        s << (msg_type == DHCPV6_RENEW ? "-f" : "-F");
        s << " 10 -R 10 -L 10547 -n 10 ::1";
        processCmdLine(opt, s.str());
        // Create a test controller class.
        NakedTestControl tc(opt);
        // Set the transaction id generator to sequential to control to
        // guarantee that transaction ids are predictable.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);

        // Send a number of Solicit messages. Each generated Solicit will be
        // assigned a different transaction id, starting from 1 to 10.
        tc.sendPackets(10);

        // Simulate Advertise responses from the server. Each advertise is
        // assigned a transaction id from the range of 1 to 10, so as they
        // match the transaction ids from the Solicit messages.
        for (unsigned i = generator->getNext() - 10;
             i < generator->getNext(); ++i) {
            Pkt6Ptr advertise(createAdvertisePkt6(tc, i));
            // If Advertise is matched with the Solicit the call below will
            // trigger a corresponding Request. They will be assigned
            // transaction ids from the range from 11 to 20 (the range of
            // 1 to 10 has been used by Solicit-Advertise).
            tc.processReceivedPacket6(advertise);
        }

        // Requests have been sent, so now let's simulate responses from the
        // server. Generate corresponding Reply messages with the transaction
        // ids from the range from 11 to 20.
        for (unsigned i = generator->getNext() - 10;
             i < generator->getNext(); ++i) {
            Pkt6Ptr reply(createReplyPkt6(tc, i));
            // Each Reply packet corresponds to the new lease acquired. Since
            // -f<renew-rate> option has been specified, received Reply
            // messages are held so as Renew messages can be sent for
            // existing leases.
            tc.processReceivedPacket6(reply);
        }

        uint64_t msg_num;
        // Try to send 5 messages. It should be successful because 10 Reply
        // messages has been received. For each of them we should be able to
        // send Renew or Release.
        msg_num = tc.sendMultipleMessages6(msg_type, 5);
        // Make sure that we have sent 5 messages.
        EXPECT_EQ(5, msg_num);

        // Try to do it again. We should still have 5 Reply packets for
        // which Renews or Releases haven't been sent yet.
        msg_num = tc.sendMultipleMessages6(msg_type, 5);
        EXPECT_EQ(5, msg_num);

        // We used all the Reply packets (we sent Renew or Release for each of
        // them already). Therefore, no further Renew or Release messages should
        // be sent before we acquire new leases.
        msg_num = tc.sendMultipleMessages6(msg_type, 5);
        // Make sure that no message has been sent.
        EXPECT_EQ(0, msg_num);

    }

    /// \brief Test counting rejected leases in Solicit-Advertise.
    ///
    /// This function simulates acquiring 4 leases from the server and
    /// rejecting allocating of 6 leases

    void testCountRejectedLeasesSolAdv() {
        // Build a command line.
        CommandOptions opt;
        std::ostringstream s;
        s << "perfdhcp -6 -l fake -r 10 -R 10 -L 10547 -n 10 ::1";
        processCmdLine(opt, s.str());
        // Create a test controller class.
        NakedTestControl tc(opt);
        // Set the transaction id generator to sequential to control to
        // guarantee that transaction ids are predictable.
        boost::shared_ptr<NakedTestControl::IncrementalGenerator>
            generator(new NakedTestControl::IncrementalGenerator());
        tc.setTransidGenerator(generator);

        // Send a number of Solicit messages. Each generated Solicit will be
        // assigned a different transaction id, starting from 1 to 10.
        tc.sendPackets(10);

        // Simulate Advertise responses from the server. Each advertise is
        // assigned a transaction id from the range of 1 to 6 with incorrect IA
        // included in the message
        for (uint32_t i = generator->getNext() - 10; i < 7; ++i) {
            Pkt6Ptr advertise(createAdvertisePkt6(tc, i, false));
            tc.processReceivedPacket6(advertise);
        }
        // counter of rejected leases has to be 6
        EXPECT_EQ(tc.stats_mgr_.getRejLeasesNum(ExchangeType::SA), 6);
        // Simulate Advertise responses from the server. Each advertise is
        // assigned a transaction id from the range of 7 to 10 with correct IA
        // included in the message
        for (uint32_t i = generator->getNext() - 7; i < 11; ++i) {
            Pkt6Ptr advertise(createAdvertisePkt6(tc, i));
            tc.processReceivedPacket6(advertise);
        }
        // counter of rejected leases can't change at this point
        EXPECT_EQ(tc.stats_mgr_.getRejLeasesNum(ExchangeType::SA), 6);
    }

    /// \brief Parse command line string with CommandOptions.
    ///
    /// \param cmdline command line string to be parsed.
    /// \throw isc::Unexpected if unexpected error occurred.
    /// \throw isc::InvalidParameter if command line is invalid.
    void processCmdLine(CommandOptions &opt, const std::string& cmdline) const {
        CommandOptionsHelper::process(opt, cmdline);
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
    createAdvertisePkt6(NakedTestControl &tc, const uint32_t transid,
                        const bool validIA = true) const {
        boost::shared_ptr<Pkt6> advertise(new Pkt6(DHCPV6_ADVERTISE, transid));
        // Add IA_NA if requested by the client.
        if (tc.options_.getLeaseType().includes(CommandOptions::LeaseType::ADDRESS)) {
            OptionPtr opt_ia_na = Option::factory(Option::V6, D6O_IA_NA);
            if (validIA) {
                OptionPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                 isc::asiolink::IOAddress("fe80::abcd"), 300, 500));
                opt_ia_na->addOption(iaaddr);
            }
            advertise->addOption(opt_ia_na);
        }
        // Add IA_PD if requested by the client.
        if (tc.options_.getLeaseType().includes(CommandOptions::LeaseType::PREFIX)) {
            OptionPtr opt_ia_pd = Option::factory(Option::V6, D6O_IA_PD);
            if (validIA) {
                OptionPtr iapref(new Option6IAPrefix(D6O_IAPREFIX,
                                 isc::asiolink::IOAddress("fe80::"), 64, 300, 500));
                opt_ia_pd->addOption(iapref);
            }
            advertise->addOption(opt_ia_pd);
        }
        OptionPtr opt_serverid(new Option(Option::V6, D6O_SERVERID));
        uint8_t randomized = 0;
        std::vector<uint8_t> duid(tc.generateDuid(randomized));
        OptionPtr opt_clientid(Option::factory(Option::V6, D6O_CLIENTID, duid));
        advertise->addOption(opt_serverid);
        advertise->addOption(opt_clientid);
        advertise->updateTimestamp();
        return (advertise);
    }

    Pkt6Ptr
    createReplyPkt6(NakedTestControl &tc, const uint32_t transid,
                    const bool validIA = true) const {
        Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, transid));
        // Add IA_NA if requested by the client.
        if (tc.options_.getLeaseType().includes(CommandOptions::LeaseType::ADDRESS)) {
            OptionPtr opt_ia_na = Option::factory(Option::V6, D6O_IA_NA);
            if (validIA) {
                OptionPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                 isc::asiolink::IOAddress("fe80::abcd"), 300, 500));
                opt_ia_na->addOption(iaaddr);
            }
            reply->addOption(opt_ia_na);
        }
        // Add IA_PD if requested by the client.
        if (tc.options_.getLeaseType().includes(CommandOptions::LeaseType::PREFIX)) {
            OptionPtr opt_ia_pd = Option::factory(Option::V6, D6O_IA_PD);
            if (validIA) {
                OptionPtr iapref(new Option6IAPrefix(D6O_IAPREFIX,
                                 isc::asiolink::IOAddress("fe80::"), 64, 300, 500));
                opt_ia_pd->addOption(iapref);
            }
            reply->addOption(opt_ia_pd);
        }
        OptionPtr opt_serverid(new Option(Option::V6, D6O_SERVERID));
        uint8_t randomized = 0;
        std::vector<uint8_t> duid(tc.generateDuid(randomized));
        OptionPtr opt_clientid(Option::factory(Option::V6, D6O_CLIENTID, duid));
        reply->addOption(opt_serverid);
        reply->addOption(opt_clientid);
        reply->updateTimestamp();
        return (reply);

    }

    /// @brief check if v4 options 200 and 201 are present.
    ///
    /// The options are expected to have specific format, as if parameters
    /// -o 200,abcdef1234, -o 201,00 were passed to the command line.
    void checkOptions20x(const Pkt4Ptr& pkt) {
        ASSERT_TRUE(pkt);
        OptionPtr opt = pkt->getOption(200);
        ASSERT_TRUE(opt);
        EXPECT_TRUE(opt->getUniverse() == Option::V4);
        EXPECT_EQ(opt->toText(), "type=200, len=005: ab:cd:ef:12:34");

        opt = pkt->getOption(201);
        ASSERT_TRUE(opt);
        EXPECT_EQ(opt->toText(), "type=201, len=001: 00");
    }

    /// @brief check if v6 options 200 and 201 are present.
    ///
    /// The options are expected to have specific format, as if parameters
    /// -o 200,abcdef1234, -o 201,00 were passed to the command line.
    void checkOptions20x(const Pkt6Ptr& pkt) {
        ASSERT_TRUE(pkt);
        OptionPtr opt = pkt->getOption(200);
        ASSERT_TRUE(opt);
        EXPECT_TRUE(opt->getUniverse() == Option::V6);
        EXPECT_EQ(opt->toText(), "type=00200, len=00005: ab:cd:ef:12:34");

        opt = pkt->getOption(201);
        ASSERT_TRUE(opt);
        EXPECT_EQ(opt->toText(), "type=00201, len=00001: 00");
    }

};

// This test verifies that the class members are reset to expected values.
TEST_F(TestControlTest, reset) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -4 127.0.0.1");
    NakedTestControl tc(opt);
    tc.reset();
    EXPECT_FALSE(tc.last_report_.is_not_a_date_time());
    EXPECT_FALSE(tc.transid_gen_);
    EXPECT_FALSE(tc.macaddr_gen_);
    EXPECT_TRUE(tc.first_packet_serverid_.empty());
    EXPECT_FALSE(tc.interrupted_);

}

// This test verifies that the client id is generated from the HW address.
TEST_F(TestControlTest, generateClientId) {
    // Generate HW address.
    std::vector<uint8_t> hwaddr;
    for (unsigned int i = 0; i < 6; ++i) {
        hwaddr.push_back(i);
    }
    HWAddrPtr hwaddr_ptr(new HWAddr(hwaddr, 5));

    // Use generated HW address to generate client id.
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -4 127.0.0.1");
    NakedTestControl tc(opt);
    OptionPtr opt_client_id;
    opt_client_id = tc.generateClientId(hwaddr_ptr);
    ASSERT_TRUE(opt_client_id);

    // Extract the client id data.
    const OptionBuffer& client_id = opt_client_id->getData();
    ASSERT_EQ(7, client_id.size());

    // Verify that the client identifier is generated correctly.

    // First byte is the HW type.
    EXPECT_EQ(5, client_id[0]);
    // The rest of the client identifier should be equal to the HW address.
    std::vector<uint8_t> sub(client_id.begin() + 1, client_id.end());
    EXPECT_TRUE(hwaddr == sub);
}

TEST_F(TestControlTest, GenerateDuid) {
    // Simple command line that simulates one client only. Always the
    // same DUID will be generated.
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l 127.0.0.1 all");
    testDuid(opt);

    // Simulate 50 clients. Different DUID will be generated.
    processCmdLine(opt, "perfdhcp -l 127.0.0.1 -R 50 all");
    testDuid(opt);

    // Checks that the random mac address returned by generateDuid
    // is in the list of mac addresses in the mac-list.txt data file
    std::string mac_list_full_path = getFullPath("mac-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -M " << mac_list_full_path << " 127.0.0.1";
    processCmdLine(opt, cmd.str());
    // Initialize Test Controller.
    NakedTestControl tc(opt);
    uint8_t randomized = 0;
    std::vector<uint8_t> generated_duid = tc.generateDuid(randomized);

    // Check that generated_duid is DUID_LL
    ASSERT_EQ(10, generated_duid.size());
    DuidPtr duid(new DUID(generated_duid));
    ASSERT_EQ(duid->getType(), DUID::DUID_LL);

    // Make sure it's on the list
    const CommandOptions::MacAddrsVector& macs = opt.getMacsFromFile();
    // DUID LL comprises 2 bytes of duid type, 2 bytes of hardware type,
    // then 6 bytes of HW address.
    vector<uint8_t> mac(6);
    std::copy(generated_duid.begin() + 4, generated_duid.begin() + 10,
              mac.begin());
    // Check that mac is in macs.
    ASSERT_TRUE(std::find(macs.begin(), macs.end(), mac) != macs.end());
}

TEST_F(TestControlTest, GenerateMacAddress) {
    CommandOptions opt;
    // Simulate one client only. Always the same MAC address will be
    // generated.
    processCmdLine(opt, "perfdhcp -l 127.0.0.1 all");
    testMacAddress(opt);

    // Simulate 50 clients. Different MAC addresses will be generated.
    processCmdLine(opt, "perfdhcp -l 127.0.0.1 -R 50 all");
    testMacAddress(opt);

    // Checks that the random mac address returned by generateMacAddress
    // is in the list of mac addresses in the mac-list.txt data file
    std::string mac_list_full_path = getFullPath("mac-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -M " << mac_list_full_path << " 127.0.0.1";
    processCmdLine(opt, cmd.str());
    // Initialize Test Controller.
    NakedTestControl tc(opt);
    uint8_t randomized = 0;
    // Generate MAC address and sanity check its size.
    std::vector<uint8_t> mac = tc.generateMacAddress(randomized);
    ASSERT_EQ(6, mac.size());
    // Make sure that the generated MAC address belongs to the MAC addresses
    // read from a file.
    const CommandOptions::MacAddrsVector& macs = opt.getMacsFromFile();
    ASSERT_TRUE(std::find(macs.begin(), macs.end(), mac) !=  macs.end());
}

TEST_F(TestControlTest, Options4) {
    using namespace isc::dhcp;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -4 127.0.0.1");
    NakedTestControl tc(opt);
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
    msg_type = opt_msg_type->getUint8();
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
    CommandOptions opt;

    // Lets override the IP version to test V6 options (-6 parameter)
    processCmdLine(opt, "perfdhcp -l lo -6 ::1");

    NakedTestControl tc(opt);
    tc.registerOptionFactories();

    // Validate the D6O_ELAPSED_TIME option.
    OptionPtr opt_elapsed_time(Option::factory(Option::V6, D6O_ELAPSED_TIME));
    // Validate the option type and universe.
    EXPECT_EQ(Option::V6, opt_elapsed_time->getUniverse());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt_elapsed_time->getType());
    // The default value of elapsed time is zero.
    uint16_t elapsed_time;
    elapsed_time = opt_elapsed_time->getUint16();
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
    elapsed_time = opt_elapsed_time2->getUint16();
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
    OptionBuffer duid(opt.getDuidTemplate());
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
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -L 10547 all");
    NakedTestControl tc(opt);
    uint32_t transid = 123;
    boost::shared_ptr<Pkt4> pkt4(new Pkt4(DHCPDISCOVER, transid));
    // Set parameters on outgoing packet.
    tc.setDefaults4(pkt4);
    // Validate that packet has been setup correctly.
    EXPECT_EQ(tc.fake_sock_.iface_->getName(), pkt4->getIface());
    EXPECT_EQ(tc.fake_sock_.ifindex_, pkt4->getIndex());
    EXPECT_EQ(DHCP4_CLIENT_PORT, pkt4->getLocalPort());
    EXPECT_EQ(DHCP4_SERVER_PORT, pkt4->getRemotePort());
    EXPECT_EQ(1, pkt4->getHops());
    EXPECT_EQ(asiolink::IOAddress("255.255.255.255"),
              pkt4->getRemoteAddr());
    EXPECT_EQ(asiolink::IOAddress(tc.socket_.addr_), pkt4->getLocalAddr());
    EXPECT_EQ(asiolink::IOAddress(tc.socket_.addr_), pkt4->getGiaddr());
}

TEST_F(TestControlTest, Packet6) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -6 -l fake -L 10547 servers");
    NakedTestControl tc(opt);
    uint32_t transid = 123;
    boost::shared_ptr<Pkt6> pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
    // Set packet's parameters.
    tc.setDefaults6(pkt6);
    // Validate if parameters have been set correctly.
    EXPECT_EQ(tc.fake_sock_.iface_->getName(), pkt6->getIface());
    EXPECT_EQ(tc.socket_.ifindex_, pkt6->getIndex());
    EXPECT_EQ(DHCP6_CLIENT_PORT, pkt6->getLocalPort());
    EXPECT_EQ(DHCP6_SERVER_PORT, pkt6->getRemotePort());
    EXPECT_EQ(tc.socket_.addr_, pkt6->getLocalAddr());
    EXPECT_EQ(asiolink::IOAddress("FF05::1:3"), pkt6->getRemoteAddr());
    // Packet must not be relayed.
    EXPECT_TRUE(pkt6->relay_info_.empty());
}

TEST_F(TestControlTest, Packet6Relayed) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -6 -l fake -A1 -L 10547 servers");
    NakedTestControl tc(opt);
    uint32_t transid = 123;
    boost::shared_ptr<Pkt6> pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
    // Set packet's parameters.
    tc.setDefaults6(pkt6);
    // Validate if parameters have been set correctly.
    EXPECT_EQ(tc.fake_sock_.iface_->getName(), pkt6->getIface());
    EXPECT_EQ(tc.socket_.ifindex_, pkt6->getIndex());
    EXPECT_EQ(DHCP6_CLIENT_PORT, pkt6->getLocalPort());
    EXPECT_EQ(DHCP6_SERVER_PORT, pkt6->getRemotePort());
    EXPECT_EQ(tc.socket_.addr_, pkt6->getLocalAddr());
    EXPECT_EQ(asiolink::IOAddress("FF05::1:3"), pkt6->getRemoteAddr());
    // Packet should be relayed.
    EXPECT_EQ(pkt6->relay_info_.size(), 1);
    EXPECT_EQ(pkt6->relay_info_[0].hop_count_, 1);
    EXPECT_EQ(pkt6->relay_info_[0].msg_type_, DHCPV6_RELAY_FORW);
    EXPECT_EQ(pkt6->relay_info_[0].linkaddr_, tc.socket_.addr_);
    EXPECT_EQ(pkt6->relay_info_[0].peeraddr_, tc.socket_.addr_);
}

TEST_F(TestControlTest, Packet4Exchange) {
    const int iterations_num = 100;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -r 100 -n 10 -R 20 -L 10547 127.0.0.1");
    bool use_templates = false;
    NakedTestControl tc(opt);
    testPkt4Exchange(iterations_num, iterations_num, use_templates, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num * 2); // Discovery + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::DO), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::DO), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RA), 0);
}

TEST_F(TestControlTest, Packet4ExchangeFromTemplate) {
    const int iterations_num = 100;
    CommandOptions opt;

    processCmdLine(opt, "perfdhcp -l fake -r 100 -R 20 -n 20 -L 10547"
                   " -T " + getFullPath("discover-example.hex")
                   + " -T " + getFullPath("request4-example.hex")
                   + " 127.0.0.1");
    const int received_num = 10;
    bool use_templates = true;
    NakedTestControl tc(opt);
    testPkt4Exchange(iterations_num, received_num, use_templates, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num + received_num);  // Discovery + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::DO), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::DO), received_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RA), received_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RA), 0);
}

TEST_F(TestControlTest, Packet6Exchange) {
    const int iterations_num = 100;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    bool use_templates = false;
    NakedTestControl tc(opt);
    testPkt6Exchange(iterations_num, iterations_num, use_templates, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num * 2); // Solicit + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RR), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RR), 0);
}

TEST_F(TestControlTest, Packet6ExchangeFromTemplate) {
    const int iterations_num = 100;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -6 -r 100 -n 10 -R 20 -L 10547"
                   " -T " + getFullPath("solicit-example.hex")
                   + " -T " + getFullPath("request6-example.hex ::1"));
    NakedTestControl tc(opt);

    // For the first 3 packets we are simulating responses from server.
    // For other packets we don't so packet as 4,5,6 will be dropped and
    // then test should be interrupted and actual number of iterations will
    // be 6.
    const int received_num = 3;
    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) exchanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. All exchanged packets carry
    // the IA_NA option to simulate the IPv6 address acquisition and to verify
    // that the IA_NA options returned by the server are processed correctly.
    bool use_templates = true;
    testPkt6Exchange(iterations_num, received_num, use_templates, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num + received_num); // Solicit + Advertise
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::SA), received_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RR), received_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RR), 0);
}

TEST_F(TestControlTest, Packet6ExchangeAddressOnly) {
    const int iterations_num = 100;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -e address-only"
                   " -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    bool use_templates = false;

    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) exchanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. All exchanged packets carry
    // the IA_NA option to simulate the IPv6 address acquisition and to verify
    // that the IA_NA options returned by the server are processed correctly.
    NakedTestControl tc(opt);
    testPkt6Exchange(iterations_num, iterations_num, use_templates, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num * 2); // Solicit + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RR), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RR), 0);
}

TEST_F(TestControlTest, Packet6ExchangePrefixDelegation) {
    const int iterations_num = 100;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -e prefix-only"
                   " -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    bool use_templates = false;

    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) exchanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. All exchanged packets carry
    // the IA_PD option to simulate the Prefix Delegation and to verify that
    // the IA_PD options returned by the server are processed correctly.
    NakedTestControl tc(opt);
    testPkt6Exchange(iterations_num, iterations_num, use_templates, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num * 2); // Discovery + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RR), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RR), 0);
}

TEST_F(TestControlTest, Packet6ExchangeAddressAndPrefix) {
    const int iterations_num = 100;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -e address-and-prefix"
                   " -6 -r 100 -n 10 -R 20 -L 10547 ::1");
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    bool use_templates = false;
    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) exchanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. All exchanged packets carry
    // either IA_NA or IA_PD options to simulate the address and prefix
    // acquisition with the single message and to verify that the IA_NA
    // and IA_PD options returned by the server are processed correctly.
    NakedTestControl tc(opt);
    testPkt6Exchange(iterations_num, iterations_num, use_templates, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num * 2); // Solicit + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RR), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RR), 0);
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

    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l 127.0.0.1"
                   " -T " + file1 + " -T " + file2 + " all");
    NakedTestControl tc(opt);

    tc.initPacketTemplates();
    TestControl::TemplateBuffer buf1;
    TestControl::TemplateBuffer buf2;
    buf1 = tc.getTemplateBuffer(0);
    buf2 = tc.getTemplateBuffer(1);
    ASSERT_EQ(template1.size(), buf1.size());
    ASSERT_EQ(template2.size(), buf2.size());
    EXPECT_TRUE(std::equal(template1.begin(), template1.end(), buf1.begin()));
    EXPECT_TRUE(std::equal(template2.begin(), template2.end(), buf2.begin()));

    // Try to read template file with odd number of digits.
    std::string file3("test3.hex");
    // Size of the file is 2 times larger than binary data size and it is always
    // even number. Substracting 1 makes file size odd.
    ASSERT_TRUE(createTemplateFile(file3, template1, template1.size() * 2 - 1));
    processCmdLine(opt, "perfdhcp -l 127.0.0.1 -T " + file3 + " all");
    EXPECT_THROW(tc.initPacketTemplates(), isc::OutOfRange);

    // Try to read empty file.
    std::string file4("test4.hex");
    ASSERT_TRUE(createTemplateFile(file4, template2, 0));
    processCmdLine(opt, "perfdhcp -l 127.0.0.1 -T " + file4 + " all");
    EXPECT_THROW(tc.initPacketTemplates(), isc::OutOfRange);

    // Try reading file with non hexadecimal characters.
    std::string file5("test5.hex");
    ASSERT_TRUE(createTemplateFile(file5, template1, template1.size() * 2, true));
    processCmdLine(opt, "perfdhcp -l 127.0.0.1 -T " + file5 + " all");
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

// This test verifies that the counter of rejected leases in
// Solicit-Advertise message exchange works correctly
TEST_F(TestControlTest, rejectedLeasesAdv) {
    testCountRejectedLeasesSolAdv();
}

// This test verifies that the DHCPv6 Release message is created correctly
// and that it comprises all required options.
TEST_F(TestControlTest, createRelease) {
    testCreateRenewRelease(DHCPV6_RELEASE);
}

// Test checks if sendDiscover really includes custom options
TEST_F(TestControlTest, sendDiscoverExtraOpts) {

    // Important paramters here:
    // -xT - save first packet of each type for templates (useful for packet inspection)
    // -o 200,abcdef1234 - send option 200 with hex content: ab:cd:ef:12:34
    // -o 201,00 - send option 201 with hex content: 00
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -4 -l fake -xT -L 10068"
                   " -o 200,abcdef1234 -o 201,00 -r 1 127.0.0.1");

    // Create test control and set up some basic defaults.
    NakedTestControl tc(opt);
    tc.registerOptionFactories();
    NakedTestControl::IncrementalGeneratorPtr gen(new NakedTestControl::IncrementalGenerator());
    tc.setTransidGenerator(gen);

    // Make tc send the packet. The first packet of each type is saved in templates.
    tc.sendDiscover4();

    // Let's find the packet and see if it includes the right option.
    auto pkt_it = tc.template_packets_v4_.find(DHCPDISCOVER);
    ASSERT_TRUE(pkt_it != tc.template_packets_v4_.end());

    checkOptions20x(pkt_it->second);
}

// Test checks if regular packet exchange inserts the extra v4 options
// specified on command line.
TEST_F(TestControlTest, Packet4ExchangeExtraOpts) {
    // Important paramters here:
    // -xT - save first packet of each type for templates (useful for packet inspection)
    // -o 200,abcdef1234 - send option 200 with hex content: ab:cd:ef:12:34
    // -o 201,00 - send option 201 with hex content: 00
    const int iterations_num = 1;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -4 -o 200,abcdef1234 -o 201,00 "
                   "-r 100 -n 10 -R 20 -xT -L 10547 127.0.0.1");

    NakedTestControl tc(opt);
    tc.registerOptionFactories();

    // Do the actual exchange.
    testPkt4Exchange(iterations_num, iterations_num, false, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num * 2); // Discovery + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::DO), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::DO), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RA), 0);

    // Check if Discover was recored and if it contains options 200 and 201.
    auto disc = tc.template_packets_v4_.find(DHCPDISCOVER);
    ASSERT_TRUE(disc != tc.template_packets_v4_.end());
    checkOptions20x(disc->second);

    // Check if Request was recored and if it contains options 200 and 201.
    auto req = tc.template_packets_v4_.find(DHCPREQUEST);
    ASSERT_TRUE(req != tc.template_packets_v4_.end());
    checkOptions20x(req->second);
}

// Test checks if regular packet exchange inserts the extra v6 options
// specified on command line.
TEST_F(TestControlTest, Packet6ExchangeExtraOpts) {
    // Important paramters here:
    // -xT - save first packet of each type for templates (useful for packet inspection)
    // -o 200,abcdef1234 - send option 200 with hex content: ab:cd:ef:12:34
    // -o 201,00 - send option 201 with hex content: 00
    const int iterations_num = 1;
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake"
                   " -6 -e address-only"
                   " -xT -o 200,abcdef1234 -o 201,00 "
                   " -r 100 -n 10 -R 20 -L 10547 ::1");

    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) exchanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing.
    // First packet of each type is recorded as a template packet. The check
    // inspects this template to see if the expected options are really there.
    NakedTestControl tc(opt);
    testPkt6Exchange(iterations_num, iterations_num, false, tc);

    EXPECT_EQ(tc.fake_sock_.sent_cnt_, iterations_num * 2); // Solicit + Request
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::SA), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getSentPacketsNum(ExchangeType::RR), iterations_num);
    EXPECT_EQ(tc.stats_mgr_.getRcvdPacketsNum(ExchangeType::RR), 0);

    // Check if Solicit was recored and if it contains options 200 and 201.
    auto sol = tc.template_packets_v6_.find(DHCPV6_SOLICIT);
    ASSERT_TRUE(sol != tc.template_packets_v6_.end());
    checkOptions20x(sol->second);

    // Check if Request was recored and if it contains options 200 and 201.
    auto req = tc.template_packets_v6_.find(DHCPV6_REQUEST);
    ASSERT_TRUE(req != tc.template_packets_v6_.end());
    checkOptions20x(req->second);
}
