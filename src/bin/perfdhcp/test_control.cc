// Copyright (C) 2012-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option6_ia.h>
#include <util/unittests/check_valgrind.h>
#include "test_control.h"
#include "command_options.h"
#include "perf_pkt4.h"
#include "perf_pkt6.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace perfdhcp {

bool TestControl::interrupted_ = false;

TestControl::TestControlSocket::TestControlSocket(const int socket) :
    SocketInfo(asiolink::IOAddress("127.0.0.1"), 0, socket),
    ifindex_(0), valid_(true) {
    try {
        initSocketData();
    } catch (const Exception&) {
        valid_ = false;
    }
}

TestControl::TestControlSocket::~TestControlSocket() {
    IfacePtr iface = IfaceMgr::instance().getIface(ifindex_);
    if (iface) {
        iface->delSocket(sockfd_);
    }
}

void
TestControl::TestControlSocket::initSocketData() {
    BOOST_FOREACH(IfacePtr iface, IfaceMgr::instance().getIfaces()) {
        BOOST_FOREACH(SocketInfo s, iface->getSockets()) {
            if (s.sockfd_ == sockfd_) {
                ifindex_ = iface->getIndex();
                addr_ = s.addr_;
                return;
            }
        }
    }
    isc_throw(BadValue, "interface for for specified socket "
              "descriptor not found");
}

TestControl&
TestControl::instance() {
    static TestControl test_control;
    return (test_control);
}

TestControl::TestControl() {
    reset();
}

void
TestControl::checkLateMessages(RateControl& rate_control) {
    // If diagnostics is disabled, there is no need to log late sent messages.
    // If it is enabled and the rate control object indicates that the last
    // sent message was late, bump up the counter in Stats Manager.
    if (rate_control.isLateSent() && testDiags('i')) {
        CommandOptions& options = CommandOptions::instance();
        if (options.getIpVersion() == 4) {
            stats_mgr4_->incrementCounter("latesend");
        } else if (options.getIpVersion() == 6) {
            stats_mgr6_->incrementCounter("latesend");
        }
    }
}

void
TestControl::cleanCachedPackets() {
    CommandOptions& options = CommandOptions::instance();
    // When Renews are not sent, Reply packets are not cached so there
    // is nothing to do.
    if (options.getRenewRate() == 0) {
        return;
    }

    static boost::posix_time::ptime last_clean =
        microsec_clock::universal_time();

    // Check how much time has passed since last cleanup.
    time_period time_since_clean(last_clean,
                                 microsec_clock::universal_time());
    // Cleanup every 1 second.
    if (time_since_clean.length().total_seconds() >= 1) {
        // Calculate how many cached packets to remove. Actually we could
        // just leave enough packets to handle Renews for 1 second but
        // since we want to randomize leases to be renewed so leave 5
        // times more packets to randomize from.
        // @todo The cache size might be controlled from the command line.
        if (reply_storage_.size() > 5 * options.getRenewRate()) {
            reply_storage_.clear(reply_storage_.size() -
                                 5 * options.getRenewRate());
        }
        // Remember when we performed a cleanup for the last time.
        // We want to do the next cleanup not earlier than in one second.
        last_clean = microsec_clock::universal_time();
    }
}

void
TestControl::copyIaOptions(const Pkt6Ptr& pkt_from, Pkt6Ptr& pkt_to) {
    if (!pkt_from || !pkt_to) {
        isc_throw(BadValue, "NULL pointers must not be specified as arguments"
                  " for the copyIaOptions function");
    }
    // IA_NA
    if (CommandOptions::instance().getLeaseType()
        .includes(CommandOptions::LeaseType::ADDRESS)) {
        OptionPtr option = pkt_from->getOption(D6O_IA_NA);
        if (!option) {
            isc_throw(OptionNotFound, "IA_NA option not found in the"
                      " server's response");
        }
        pkt_to->addOption(option);
    }
    // IA_PD
    if (CommandOptions::instance().getLeaseType()
        .includes(CommandOptions::LeaseType::PREFIX)) {
        OptionPtr option = pkt_from->getOption(D6O_IA_PD);
        if (!option) {
            isc_throw(OptionNotFound, "IA_PD option not found in the"
                      " server's response");
        }
        pkt_to->addOption(option);
    }


}

std::string
TestControl::byte2Hex(const uint8_t b) const {
    const int b1 = b / 16;
    const int b0 = b % 16;
    ostringstream stream;
    stream << std::hex << b1 << b0 << std::dec;
    return (stream.str());
}

bool
TestControl::checkExitConditions() const {
    if (interrupted_) {
        return (true);
    }
    CommandOptions& options = CommandOptions::instance();
    bool test_period_reached = false;
    // Check if test period passed.
    if (options.getPeriod() != 0) {
        if (options.getIpVersion() == 4) {
            time_period period(stats_mgr4_->getTestPeriod());
            if (period.length().total_seconds() >= options.getPeriod()) {
                test_period_reached = true;
            }
        } else if (options.getIpVersion() == 6) {
            time_period period = stats_mgr6_->getTestPeriod();
            if (period.length().total_seconds() >= options.getPeriod()) {
                test_period_reached = true;
            }
        }
    }
    if (test_period_reached) {
        if (testDiags('e')) {
            std::cout << "reached test-period." << std::endl;
        }
        return (true);
    }

    bool max_requests = false;
    // Check if we reached maximum number of DISCOVER/SOLICIT sent.
    if (options.getNumRequests().size() > 0) {
        if (options.getIpVersion() == 4) {
            if (getSentPacketsNum(StatsMgr4::XCHG_DO) >=
                options.getNumRequests()[0]) {
                max_requests = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA) >=
                options.getNumRequests()[0]) {
                max_requests = true;
            }
        }
    }
    // Check if we reached maximum number REQUEST packets.
    if (options.getNumRequests().size() > 1) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA) >=
                options.getNumRequests()[1]) {
                max_requests = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR) >=
                options.getNumRequests()[1]) {
                max_requests = true;
            }
        }
    }
    if (max_requests) {
        if (testDiags('e')) {
            std::cout << "Reached max requests limit." << std::endl;
        }
        return (true);
    }

    // Check if we reached maximum number of drops of OFFER/ADVERTISE packets.
    bool max_drops = false;
    if (options.getMaxDrop().size() > 0) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_DO) >=
                options.getMaxDrop()[0]) {
                max_drops = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_SA) >=
                options.getMaxDrop()[0]) {
                max_drops = true;
            }
        }
    }
    // Check if we reached maximum number of drops of ACK/REPLY packets.
    if (options.getMaxDrop().size() > 1) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_RA) >=
                options.getMaxDrop()[1]) {
                max_drops = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_RR) >=
                options.getMaxDrop()[1]) {
                max_drops = true;
            }
        }
    }
    if (max_drops) {
        if (testDiags('e')) {
            std::cout << "Reached maximum drops number." << std::endl;
        }
        return (true);
    }

    // Check if we reached maximum drops percentage of OFFER/ADVERTISE packets.
    bool max_pdrops = false;
    if (options.getMaxDropPercentage().size() > 0) {
        if (options.getIpVersion() == 4) {
            if ((stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_DO) > 10) &&
                ((100. * stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_DO) /
                 stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_DO)) >=
                 options.getMaxDropPercentage()[0])) {
                max_pdrops = true;

            }
        } else if (options.getIpVersion() == 6) {
            if ((stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA) > 10) &&
                ((100. * stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_SA) /
                  stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA)) >=
                 options.getMaxDropPercentage()[0])) {
                max_pdrops = true;
            }
        }
    }
    // Check if we reached maximum drops percentage of ACK/REPLY packets.
    if (options.getMaxDropPercentage().size() > 1) {
        if (options.getIpVersion() == 4) {
            if ((stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA) > 10) &&
                ((100. * stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_RA) /
                 stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA)) >=
                 options.getMaxDropPercentage()[1])) {
                max_pdrops = true;
            }
        } else if (options.getIpVersion() == 6) {
            if ((stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR) > 10) &&
                ((100. * stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_RR) /
                  stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR)) >=
                 options.getMaxDropPercentage()[1])) {
                max_pdrops = true;
            }
        }
    }
    if (max_pdrops) {
        if (testDiags('e')) {
            std::cout << "Reached maximum percentage of drops." << std::endl;
        }
        return (true);
    }
    return (false);
}

Pkt4Ptr
TestControl::createRequestFromAck(const dhcp::Pkt4Ptr& ack) {
    if (!ack) {
        isc_throw(isc::BadValue, "Unable to create DHCPREQUEST from a"
                  " null DHCPACK message");
    } else if (ack->getYiaddr().isV4Zero()) {
        isc_throw(isc::BadValue, "Unable to create DHCPREQUEST from a"
                  " DHCPACK message containing yiaddr of 0");
    }
    Pkt4Ptr msg(new Pkt4(DHCPREQUEST, generateTransid()));
    msg->setCiaddr(ack->getYiaddr());
    msg->setHWAddr(ack->getHWAddr());
    msg->addOption(generateClientId(msg->getHWAddr()));
    return (msg);
}

Pkt6Ptr
TestControl::createMessageFromReply(const uint16_t msg_type,
                                    const dhcp::Pkt6Ptr& reply) {
    // Restrict messages to Release and Renew.
    if (msg_type != DHCPV6_RENEW && msg_type != DHCPV6_RELEASE) {
        isc_throw(isc::BadValue, "invalid message type " << msg_type
                  << " to be created from Reply, expected DHCPV6_RENEW or"
                  " DHCPV6_RELEASE");
    }
    // Get the string representation of the message - to be used for error
    // logging purposes.
    const char* msg_type_str = (msg_type == DHCPV6_RENEW ? "Renew" : "Release");
    // Reply message must be specified.
    if (!reply) {
        isc_throw(isc::BadValue, "Unable to create " << msg_type_str
                  << " message from the Reply message because the instance of"
                  " the Reply message is NULL");
    }

    Pkt6Ptr msg(new Pkt6(msg_type, generateTransid()));
    // Client id.
    OptionPtr opt_clientid = reply->getOption(D6O_CLIENTID);
    if (!opt_clientid) {
        isc_throw(isc::Unexpected, "failed to create " << msg_type_str
                  << " message because client id option has not been found"
                  " in the Reply message");
    }
    msg->addOption(opt_clientid);
    // Server id.
    OptionPtr opt_serverid = reply->getOption(D6O_SERVERID);
    if (!opt_serverid) {
        isc_throw(isc::Unexpected, "failed to create " << msg_type_str
                  << " because server id option has not been found in the"
                  " Reply message");
    }
    msg->addOption(opt_serverid);
    copyIaOptions(reply, msg);
    return (msg);
}

OptionPtr
TestControl::factoryElapsedTime6(Option::Universe, uint16_t,
                                 const OptionBuffer& buf) {
    if (buf.size() == 2) {
        return (OptionPtr(new Option(Option::V6, D6O_ELAPSED_TIME, buf)));
    } else if (buf.size() == 0) {
        return (OptionPtr(new Option(Option::V6, D6O_ELAPSED_TIME,
                                     OptionBuffer(2, 0))));
    }
    isc_throw(isc::BadValue,
              "elapsed time option buffer size has to be 0 or 2");
}

OptionPtr
TestControl::factoryGeneric(Option::Universe u, uint16_t type,
                            const OptionBuffer& buf) {
    OptionPtr opt(new Option(u, type, buf));
    return (opt);
}

OptionPtr
TestControl::factoryIana6(Option::Universe, uint16_t,
                          const OptionBuffer& buf) {
    // @todo allow different values of T1, T2 and IAID.
    const uint8_t buf_array[] = {
        0, 0, 0, 1,                     // IAID = 1
        0, 0, 3600 >> 8, 3600 & 0xff,  // T1 = 3600
        0, 0, 5400 >> 8, 5400 & 0xff,   // T2 = 5400
    };
    OptionBuffer buf_ia_na(buf_array, buf_array + sizeof(buf_array));
    for (size_t i = 0;  i < buf.size(); ++i) {
        buf_ia_na.push_back(buf[i]);
    }
    return (OptionPtr(new Option(Option::V6, D6O_IA_NA, buf_ia_na)));
}

OptionPtr
TestControl::factoryIapd6(Option::Universe, uint16_t,
                          const OptionBuffer& buf) {
    // @todo allow different values of T1, T2 and IAID.
    static const uint8_t buf_array[] = {
        0, 0, 0, 1,                     // IAID = 1
        0, 0, 3600 >> 8, 3600 & 0xff,   // T1 = 3600
        0, 0, 5400 >> 8, 5400 & 0xff,   // T2 = 5400
    };
    OptionBuffer buf_ia_pd(buf_array, buf_array + sizeof(buf_array));
    // Append sub-options to IA_PD.
    buf_ia_pd.insert(buf_ia_pd.end(), buf.begin(), buf.end());
    return (OptionPtr(new Option(Option::V6, D6O_IA_PD, buf_ia_pd)));
}


OptionPtr
TestControl::factoryRapidCommit6(Option::Universe, uint16_t,
                                 const OptionBuffer&) {
    return (OptionPtr(new Option(Option::V6, D6O_RAPID_COMMIT, OptionBuffer())));
}

OptionPtr
TestControl::factoryOptionRequestOption6(Option::Universe,
                                         uint16_t,
                                         const OptionBuffer&) {
    const uint8_t buf_array[] = {
        0, D6O_NAME_SERVERS,
        0, D6O_DOMAIN_SEARCH,
    };
    OptionBuffer buf_with_options(buf_array, buf_array + sizeof(buf_array));
    return (OptionPtr(new Option(Option::V6, D6O_ORO, buf_with_options)));
}


OptionPtr
TestControl::factoryRequestList4(Option::Universe u,
                                 uint16_t type,
                                 const OptionBuffer& buf) {
    const uint8_t buf_array[] = {
        DHO_SUBNET_MASK,
        DHO_BROADCAST_ADDRESS,
        DHO_TIME_OFFSET,
        DHO_ROUTERS,
        DHO_DOMAIN_NAME,
        DHO_DOMAIN_NAME_SERVERS,
        DHO_HOST_NAME
    };

    OptionBuffer buf_with_options(buf_array, buf_array + sizeof(buf_array));
    OptionPtr opt(new Option(u, type, buf));
    opt->setData(buf_with_options.begin(), buf_with_options.end());
    return (opt);
}

std::vector<uint8_t>
TestControl::generateMacAddress(uint8_t& randomized) const {
    CommandOptions& options = CommandOptions::instance();
    uint32_t clients_num = options.getClientsNum();
    if (clients_num < 2) {
        return (options.getMacTemplate());
    }
    // Get the base MAC address. We are going to randomize part of it.
    std::vector<uint8_t> mac_addr(options.getMacTemplate());
    if (mac_addr.size() != HW_ETHER_LEN) {
        isc_throw(BadValue, "invalid MAC address template specified");
    }
    uint32_t r = macaddr_gen_->generate();
    randomized = 0;
    // Randomize MAC address octets.
    for (std::vector<uint8_t>::iterator it = mac_addr.end() - 1;
         it >= mac_addr.begin();
         --it) {
        // Add the random value to the current octet.
        (*it) += r;
        ++randomized;
        if (r < 256) {
            // If we are here it means that there is no sense
            // to randomize the remaining octets of MAC address
            // because the following bytes of random value
            // are zero and it will have no effect.
            break;
        }
        // Randomize the next octet with the following
        // byte of random value.
        r >>= 8;
    }
    return (mac_addr);
}

OptionPtr
TestControl::generateClientId(const dhcp::HWAddrPtr& hwaddr) const {
    std::vector<uint8_t> client_id(1, static_cast<uint8_t>(hwaddr->htype_));
    client_id.insert(client_id.end(), hwaddr->hwaddr_.begin(),
                     hwaddr->hwaddr_.end());
    return (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                 client_id)));
}

std::vector<uint8_t>
TestControl::generateDuid(uint8_t& randomized) const {
    CommandOptions& options = CommandOptions::instance();
    uint32_t clients_num = options.getClientsNum();
    if ((clients_num == 0) || (clients_num == 1)) {
        return (options.getDuidTemplate());
    }
    // Get the base DUID. We are going to randomize part of it.
    std::vector<uint8_t> duid(options.getDuidTemplate());
    // @todo: add support for DUIDs of different sizes.
    std::vector<uint8_t> mac_addr(generateMacAddress(randomized));
    duid.resize(duid.size());
    std::copy(mac_addr.begin(), mac_addr.end(),
              duid.begin() + duid.size() - mac_addr.size());
    return (duid);
}

uint32_t
TestControl::getCurrentTimeout() const {
    CommandOptions& options = CommandOptions::instance();
    ptime now(microsec_clock::universal_time());
    // Check that we haven't passed the moment to send the next set of
    // packets.
    if (now >= basic_rate_control_.getDue() ||
        (options.getRenewRate() != 0 && now >= renew_rate_control_.getDue()) ||
        (options.getReleaseRate() != 0 &&
         now >= release_rate_control_.getDue())) {
        return (0);
    }

    // Let's assume that the due time for Solicit is the soonest.
    ptime due = basic_rate_control_.getDue();
    // If we are sending Renews and due time for Renew occurs sooner,
    // set the due time to Renew due time.
    if ((options.getRenewRate()) != 0 && (renew_rate_control_.getDue() < due)) {
        due = renew_rate_control_.getDue();
    }
    // If we are sending Releases and the due time for Release occurs
    // sooner than the current due time, let's use the due for Releases.
    if ((options.getReleaseRate() != 0) &&
        (release_rate_control_.getDue() < due)) {
        due = release_rate_control_.getDue();
    }
    // Return the timeout in microseconds.
    return (time_period(now, due).length().total_microseconds());
}

int
TestControl::getElapsedTimeOffset() const {
    int elp_offset = CommandOptions::instance().getIpVersion() == 4 ?
        DHCPV4_ELAPSED_TIME_OFFSET : DHCPV6_ELAPSED_TIME_OFFSET;
    if (CommandOptions::instance().getElapsedTimeOffset() > 0) {
        elp_offset = CommandOptions::instance().getElapsedTimeOffset();
    }
    return (elp_offset);
}

template<class T>
uint32_t
TestControl::getElapsedTime(const T& pkt1, const T& pkt2) {
    using namespace boost::posix_time;
    ptime pkt1_time = pkt1->getTimestamp();
    ptime pkt2_time = pkt2->getTimestamp();
    if (pkt1_time.is_not_a_date_time() ||
        pkt2_time.is_not_a_date_time()) {
        isc_throw(InvalidOperation, "packet timestamp not set");;
    }
    time_period elapsed_period(pkt1_time, pkt2_time);
    return (elapsed_period.is_null() ? 0 :
            elapsed_period.length().total_milliseconds());
}

int
TestControl::getRandomOffset(const int arg_idx) const {
    int rand_offset = CommandOptions::instance().getIpVersion() == 4 ?
        DHCPV4_RANDOMIZATION_OFFSET : DHCPV6_RANDOMIZATION_OFFSET;
    if (CommandOptions::instance().getRandomOffset().size() > arg_idx) {
        rand_offset = CommandOptions::instance().getRandomOffset()[arg_idx];
    }
    return (rand_offset);
}

int
TestControl::getRequestedIpOffset() const {
    int rip_offset = CommandOptions::instance().getIpVersion() == 4 ?
        DHCPV4_REQUESTED_IP_OFFSET : DHCPV6_IA_NA_OFFSET;
    if (CommandOptions::instance().getRequestedIpOffset() > 0) {
        rip_offset = CommandOptions::instance().getRequestedIpOffset();
    }
    return (rip_offset);
}

uint64_t
TestControl::getRcvdPacketsNum(ExchangeType xchg_type) const {
    uint8_t ip_version = CommandOptions::instance().getIpVersion();
    if (ip_version == 4) {
        return (stats_mgr4_->getRcvdPacketsNum(xchg_type));
    }
    return (stats_mgr6_->
            getRcvdPacketsNum(static_cast<StatsMgr6::ExchangeType>(xchg_type)));
}

uint64_t
TestControl::getSentPacketsNum(ExchangeType xchg_type) const {
    uint8_t ip_version = CommandOptions::instance().getIpVersion();
    if (ip_version == 4) {
        return (stats_mgr4_->getSentPacketsNum(xchg_type));
    }
    return (stats_mgr6_->
            getSentPacketsNum(static_cast<StatsMgr6::ExchangeType>(xchg_type)));
}

int
TestControl::getServerIdOffset() const {
    int srvid_offset = CommandOptions::instance().getIpVersion() == 4 ?
        DHCPV4_SERVERID_OFFSET : DHCPV6_SERVERID_OFFSET;
    if (CommandOptions::instance().getServerIdOffset() > 0) {
        srvid_offset = CommandOptions::instance().getServerIdOffset();
    }
    return (srvid_offset);
}

TestControl::TemplateBuffer
TestControl::getTemplateBuffer(const size_t idx) const {
    if (template_buffers_.size() > idx) {
        return (template_buffers_[idx]);
    }
    isc_throw(OutOfRange, "invalid buffer index");
}

int
TestControl::getTransactionIdOffset(const int arg_idx) const {
    int xid_offset = CommandOptions::instance().getIpVersion() == 4 ?
        DHCPV4_TRANSID_OFFSET : DHCPV6_TRANSID_OFFSET;
    if (CommandOptions::instance().getTransactionIdOffset().size() > arg_idx) {
        xid_offset = CommandOptions::instance().getTransactionIdOffset()[arg_idx];
    }
    return (xid_offset);
}

void
TestControl::handleChild(int) {
    int status = 0;
    while (wait3(&status, WNOHANG, NULL) > 0) {
        // continue
    }
}

void
TestControl::handleInterrupt(int) {
    interrupted_ = true;
}

void
TestControl::initPacketTemplates() {
    template_packets_v4_.clear();
    template_packets_v6_.clear();
    template_buffers_.clear();
    CommandOptions& options = CommandOptions::instance();
    std::vector<std::string> template_files = options.getTemplateFiles();
    for (std::vector<std::string>::const_iterator it = template_files.begin();
         it != template_files.end(); ++it) {
        readPacketTemplate(*it);
    }
}

void
TestControl::initializeStatsMgr() {
    CommandOptions& options = CommandOptions::instance();
    // Check if packet archive mode is required. If user
    // requested diagnostics option -x t we have to enable
    // it so as StatsMgr preserves all packets.
    const bool archive_mode = testDiags('t') ? true : false;
    if (options.getIpVersion() == 4) {
        stats_mgr4_.reset();
        stats_mgr4_ = StatsMgr4Ptr(new StatsMgr4(archive_mode));
        stats_mgr4_->addExchangeStats(StatsMgr4::XCHG_DO,
                                      options.getDropTime()[0]);
        if (options.getExchangeMode() == CommandOptions::DORA_SARR) {
            stats_mgr4_->addExchangeStats(StatsMgr4::XCHG_RA,
                                          options.getDropTime()[1]);
        }
        if (options.getRenewRate() != 0) {
            stats_mgr4_->addExchangeStats(StatsMgr4::XCHG_RN);
        }

    } else if (options.getIpVersion() == 6) {
        stats_mgr6_.reset();
        stats_mgr6_ = StatsMgr6Ptr(new StatsMgr6(archive_mode));
        stats_mgr6_->addExchangeStats(StatsMgr6::XCHG_SA,
                                      options.getDropTime()[0]);
        if (options.getExchangeMode() == CommandOptions::DORA_SARR) {
            stats_mgr6_->addExchangeStats(StatsMgr6::XCHG_RR,
                                          options.getDropTime()[1]);
        }
        if (options.getRenewRate() != 0) {
            stats_mgr6_->addExchangeStats(StatsMgr6::XCHG_RN);
        }
        if (options.getReleaseRate() != 0) {
            stats_mgr6_->addExchangeStats(StatsMgr6::XCHG_RL);
        }
    }
    if (testDiags('i')) {
        if (options.getIpVersion() == 4) {
            stats_mgr4_->addCustomCounter("latesend", "Late sent packets");
            stats_mgr4_->addCustomCounter("shortwait", "Short waits for packets");
            stats_mgr4_->addCustomCounter("multircvd", "Multiple packets receives");
            stats_mgr4_->addCustomCounter("latercvd", "Late received packets");
        } else if (options.getIpVersion() == 6) {
            stats_mgr6_->addCustomCounter("latesend", "Late sent packets");
            stats_mgr6_->addCustomCounter("shortwait", "Short waits for packets");
            stats_mgr6_->addCustomCounter("multircvd", "Multiple packets receives");
            stats_mgr6_->addCustomCounter("latercvd", "Late received packets");
        }
    }
}

int
TestControl::openSocket() const {
    CommandOptions& options = CommandOptions::instance();
    std::string localname = options.getLocalName();
    std::string servername = options.getServerName();
    uint16_t port = options.getLocalPort();
    int sock = 0;

    uint8_t family = (options.getIpVersion() == 6) ? AF_INET6 : AF_INET;
    IOAddress remoteaddr(servername);

    // Check for mismatch between IP option and server address
    if (family != remoteaddr.getFamily()) {
        isc_throw(InvalidParameter,
                  "Values for IP version: " <<
                  static_cast<unsigned int>(options.getIpVersion()) <<
                  " and server address: " << servername << " are mismatched.");
    }

    if (port == 0) {
        if (family == AF_INET6) {
            port = DHCP6_CLIENT_PORT;
        } else if (options.getIpVersion() == 4) {
            port = 67; //  TODO: find out why port 68 is wrong here.
        }
    }

    // Local name is specified along with '-l' option.
    // It may point to interface name or local address.
    if (!localname.empty()) {
        // CommandOptions should be already aware wether local name
        // is interface name or address because it uses IfaceMgr to
        // scan interfaces and get's their names.
        if (options.isInterface()) {
            sock = IfaceMgr::instance().openSocketFromIface(localname,
                                                            port,
                                                            family);
        } else {
            IOAddress localaddr(localname);
            sock = IfaceMgr::instance().openSocketFromAddress(localaddr,
                                                              port);
        }
    } else if (!servername.empty()) {
        // If only server name is given we will need to try to resolve
        // the local address to bind socket to based on remote address.
        sock = IfaceMgr::instance().openSocketFromRemoteAddress(remoteaddr,
                                                                port);
    }
    if (sock <= 0) {
        isc_throw(BadValue, "unable to open socket to communicate with "
                  "DHCP server");
    }

    // IfaceMgr does not set broadcast option on the socket. We rely
    // on CommandOptions object to find out if socket has to have
    // broadcast enabled.
    if ((options.getIpVersion() == 4) && options.isBroadcast()) {
        int broadcast_enable = 1;
        int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
                             &broadcast_enable, sizeof(broadcast_enable));
        if (ret < 0) {
            isc_throw(InvalidOperation,
                      "unable to set broadcast option on the socket");
        }
    } else if (options.getIpVersion() == 6) {
        // If remote address is multicast we need to enable it on
        // the socket that has been created.
        if (remoteaddr.isV6Multicast()) {
            int hops = 1;
            int ret = setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
                                 &hops, sizeof(hops));
            // If user specified interface name with '-l' the
            // IPV6_MULTICAST_IF has to be set.
            if ((ret >= 0)  && options.isInterface()) {
                IfacePtr iface =
                    IfaceMgr::instance().getIface(options.getLocalName());
                if (iface == NULL) {
                    isc_throw(Unexpected, "unknown interface "
                              << options.getLocalName());
                }
                int idx = iface->getIndex();
                ret = setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_IF,
                                     &idx, sizeof(idx));
            }
            if (ret < 0) {
                isc_throw(InvalidOperation,
                          "unable to enable multicast on socket " <<  sock
                          << ". errno = " << errno);
            }
        }
    }

    return (sock);
}

void
TestControl::sendPackets(const TestControlSocket& socket,
                         const uint64_t packets_num,
                         const bool preload /* = false */) {
    CommandOptions& options = CommandOptions::instance();
    for (uint64_t i = packets_num; i > 0; --i) {
        if (options.getIpVersion() == 4) {
            // No template packets means that no -T option was specified.
            // We have to build packets ourselfs.
            if (template_buffers_.empty()) {
                sendDiscover4(socket, preload);
            } else {
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendDiscover4(socket, template_buffers_[0], preload);
            }
        } else {
            // No template packets means that no -T option was specified.
            // We have to build packets ourselfs.
            if (template_buffers_.empty()) {
                sendSolicit6(socket, preload);
            } else {
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendSolicit6(socket, template_buffers_[0], preload);
            }
        }
        // If we preload server we don't want to receive any packets.
        if (!preload) {
            uint64_t latercvd = receivePackets(socket);
            if (testDiags('i')) {
                if (options.getIpVersion() == 4) {
                    stats_mgr4_->incrementCounter("latercvd", latercvd);
                } else if (options.getIpVersion() == 6) {
                    stats_mgr6_->incrementCounter("latercvd", latercvd);
                }
            }
        }
    }
}

uint64_t
TestControl::sendMultipleRequests(const TestControlSocket& socket,
                                  const uint64_t msg_num) {
    for (uint64_t i = 0; i < msg_num; ++i) {
        if (!sendRequestFromAck(socket)) {
            return (i);
        }
    }
    return (msg_num);
}

uint64_t
TestControl::sendMultipleMessages6(const TestControlSocket& socket,
                                   const uint32_t msg_type,
                                   const uint64_t msg_num) {
    for (uint64_t i = 0; i < msg_num; ++i) {
        if (!sendMessageFromReply(msg_type, socket)) {
            return (i);
        }
    }
    return (msg_num);
}

void
TestControl::printDiagnostics() const {
    CommandOptions& options = CommandOptions::instance();
    if (testDiags('a')) {
        // Print all command line parameters.
        options.printCommandLine();
        // Print MAC and DUID.
        std::cout << "Set MAC to " << vector2Hex(options.getMacTemplate(), "::")
                  << std::endl;
        if (options.getDuidTemplate().size() > 0) {
            std::cout << "Set DUID to " << vector2Hex(options.getDuidTemplate()) << std::endl;
        }
    }
}

void
TestControl::printTemplate(const uint8_t packet_type) const {
    std::string hex_buf;
    int arg_idx = 0;
    if (CommandOptions::instance().getIpVersion() == 4) {
        if (packet_type == DHCPREQUEST) {
            arg_idx = 1;
        }
        std::map<uint8_t, dhcp::Pkt4Ptr>::const_iterator pkt_it =
            template_packets_v4_.find(packet_type);
        if ((pkt_it != template_packets_v4_.end()) &&
            pkt_it->second) {
            const util::OutputBuffer& out_buf(pkt_it->second->getBuffer());
            const char* out_buf_data =
                static_cast<const char*>(out_buf.getData());
            std::vector<uint8_t> buf(out_buf_data, out_buf_data + out_buf.getLength());
            hex_buf = vector2Hex(buf);
        }
    } else if (CommandOptions::instance().getIpVersion() == 6) {
        if (packet_type == DHCPV6_REQUEST) {
            arg_idx = 1;
        }
        std::map<uint8_t, dhcp::Pkt6Ptr>::const_iterator pkt_it =
            template_packets_v6_.find(packet_type);
        if (pkt_it != template_packets_v6_.end() &&
            pkt_it->second) {
            const util::OutputBuffer& out_buf(pkt_it->second->getBuffer());
            const char* out_buf_data =
                static_cast<const char*>(out_buf.getData());
            std::vector<uint8_t> buf(out_buf_data, out_buf_data + out_buf.getLength());
            hex_buf = vector2Hex(buf);
        }
    }
    std::cout << "xid-offset=" << getTransactionIdOffset(arg_idx) << std::endl;
    std::cout << "random-offset=" << getRandomOffset(arg_idx) << std::endl;
    if (arg_idx > 0) {
        std::cout << "srvid-offset=" << getServerIdOffset() << std::endl;
        std::cout << "time-offset=" << getElapsedTimeOffset() << std::endl;
        std::cout << "ip-offset=" << getRequestedIpOffset() << std::endl;
    }

    std::cout << "contents: " << std::endl;
    int line_len = 32;
    int i = 0;
    while (line_len == 32) {
        if (hex_buf.length() - i < 32) {
            line_len = hex_buf.length() - i;
        };
        if (line_len > 0) {
            std::cout << setfill('0') << setw(4) << std::hex << i << std::dec
                      << "   " << hex_buf.substr(i, line_len) << std::endl;
        }
        i += 32;
    }
    std::cout << std::endl;
}

void
TestControl::printTemplates() const {
    CommandOptions& options = CommandOptions::instance();
    if (options.getIpVersion() == 4) {
        printTemplate(DHCPDISCOVER);
        printTemplate(DHCPREQUEST);
    } else if (options.getIpVersion() == 6) {
        printTemplate(DHCPV6_SOLICIT);
        printTemplate(DHCPV6_REQUEST);
    }
}

void
TestControl::printRate() const {
    double rate = 0;
    CommandOptions& options = CommandOptions::instance();
    if (options.getIpVersion() == 4) {
        double duration =
            stats_mgr4_->getTestPeriod().length().total_nanoseconds() / 1e9;
        rate = stats_mgr4_->getRcvdPacketsNum(StatsMgr4::XCHG_DO) / duration;
    } else if (options.getIpVersion() == 6) {
        double duration =
            stats_mgr6_->getTestPeriod().length().total_nanoseconds() / 1e9;
        rate = stats_mgr6_->getRcvdPacketsNum(StatsMgr6::XCHG_SA) / duration;
    }
    std::cout << "***Rate statistics***" << std::endl;
    if (options.getRate() > 0) {
        std::cout << "Rate: " << rate << " exchanges/second, expected rate: "
                  << options.getRate() << " exchanges/second" <<  std::endl << std::endl;
    } else {
        std::cout << "Rate: " << rate << std::endl << std::endl;
    }
}

void
TestControl::printIntermediateStats() {
    CommandOptions& options = CommandOptions::instance();
    int delay = options.getReportDelay();
    ptime now = microsec_clock::universal_time();
    time_period time_since_report(last_report_, now);
    if (time_since_report.length().total_seconds() >= delay) {
        if (options.getIpVersion() == 4) {
            stats_mgr4_->printIntermediateStats();
        } else if (options.getIpVersion() == 6) {
            stats_mgr6_->printIntermediateStats();
        }
        last_report_ = now;
    }
}

void
TestControl::printStats() const {
    printRate();
    CommandOptions& options = CommandOptions::instance();
    if (options.getIpVersion() == 4) {
        if (!stats_mgr4_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                      "hasn't been initialized");
        }
        stats_mgr4_->printStats();
        if (testDiags('i')) {
            stats_mgr4_->printCustomCounters();
        }
    } else if (options.getIpVersion() == 6) {
        if (!stats_mgr6_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                      "hasn't been initialized");
        }
        stats_mgr6_->printStats();
        if (testDiags('i')) {
            stats_mgr6_->printCustomCounters();
        }
    }
}

std::string
TestControl::vector2Hex(const std::vector<uint8_t>& vec,
                        const std::string& separator /* ="" */) const {
    std::ostringstream stream;
    for (std::vector<uint8_t>::const_iterator it = vec.begin();
         it != vec.end();
         ++it) {
        if (it == vec.begin()) {
            stream << byte2Hex(*it);
        } else {
            stream << separator << byte2Hex(*it);
        }
    }
    return (stream.str());
}

void
TestControl::readPacketTemplate(const std::string& file_name) {
    std::ifstream temp_file;
    temp_file.open(file_name.c_str(), ios::in | ios::binary | ios::ate);
    if (!temp_file.is_open()) {
        isc_throw(BadValue, "unable to open template file " << file_name);
    }
    // Read template file contents.
    std::streampos temp_size = temp_file.tellg();
    if (temp_size == std::streampos(0)) {
        temp_file.close();
        isc_throw(OutOfRange, "the template file " << file_name << " is empty");
    }
    temp_file.seekg(0, ios::beg);
    std::vector<char> file_contents(temp_size);
    temp_file.read(&file_contents[0], temp_size);
    temp_file.close();
    // Spaces are allowed so we have to strip the contents
    // from them. In the same time we want to make sure that
    // apart from spaces the file contains hexadecimal digits
    // only.
    std::vector<char> hex_digits;
    for (size_t i = 0; i < file_contents.size(); ++i) {
        if (isxdigit(file_contents[i])) {
            hex_digits.push_back(file_contents[i]);
        } else if (!isxdigit(file_contents[i]) &&
                   !isspace(file_contents[i])) {
            isc_throw(BadValue, "'" << file_contents[i] << "' is not a"
                      " hexadecimal digit");
        }
    }
    // Expect even number of digits.
    if (hex_digits.size() % 2 != 0) {
        isc_throw(OutOfRange, "odd number of digits in template file");
    } else if (hex_digits.empty()) {
        isc_throw(OutOfRange, "template file " << file_name << " is empty");
    }
    std::vector<uint8_t> binary_stream;
    for (size_t i = 0; i < hex_digits.size(); i += 2) {
        stringstream s;
        s << "0x" << hex_digits[i] << hex_digits[i+1];
        int b;
        s >> std::hex >> b;
        binary_stream.push_back(static_cast<uint8_t>(b));
    }
    template_buffers_.push_back(binary_stream);
}

void
TestControl::processReceivedPacket4(const TestControlSocket& socket,
                            const Pkt4Ptr& pkt4) {
    if (pkt4->getType() == DHCPOFFER) {
        Pkt4Ptr discover_pkt4(stats_mgr4_->passRcvdPacket(StatsMgr4::XCHG_DO,
                                                          pkt4));
        CommandOptions::ExchangeMode xchg_mode =
            CommandOptions::instance().getExchangeMode();
        if ((xchg_mode == CommandOptions::DORA_SARR) && discover_pkt4) {
            if (template_buffers_.size() < 2) {
                sendRequest4(socket, discover_pkt4, pkt4);
            } else {
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendRequest4(socket, template_buffers_[1], discover_pkt4, pkt4);
            }
        }
    } else if (pkt4->getType() == DHCPACK) {
        // If received message is DHCPACK, we have to check if this is a response
        // to 4-way exchange. We'll match this packet with a DHCPREQUESTs sent
        // as part of the 4-way exchages.
        if (stats_mgr4_->passRcvdPacket(StatsMgr4::XCHG_RA, pkt4)) {
            // The DHCPACK belongs to DHCPREQUEST-DHCPACK exchange type. So, we
            // may need to keep this DHCPACK in the storage if renews. Note that,
            // DHCPACK messages hold the information about leases assigned.
            // We use this information to renew.
            if (stats_mgr4_->hasExchangeStats(StatsMgr4::XCHG_RN)) {
                // Renew messages are sent, because StatsMgr has the
                // specific exchange type specified. Let's append the DHCPACK.
                // message to a storage
                ack_storage_.append(pkt4);
            }
        // The DHCPACK message is not a server's response to the DHCPREQUEST
        // message sent within the 4-way exchange. It may be a response to a
        // renewal. In this case we first check if StatsMgr has exchange type
        // for renew specified, and if it has, if there is a corresponding
        // renew message for the received DHCPACK.
        } else if (stats_mgr4_->hasExchangeStats(StatsMgr4::XCHG_RN)) {
            stats_mgr4_->passRcvdPacket(StatsMgr4::XCHG_RN, pkt4);
        }
    }
}

void
TestControl::processReceivedPacket6(const TestControlSocket& socket,
                            const Pkt6Ptr& pkt6) {
    uint8_t packet_type = pkt6->getType();
    if (packet_type == DHCPV6_ADVERTISE) {
        Pkt6Ptr solicit_pkt6(stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_SA,
                                                         pkt6));
        CommandOptions::ExchangeMode xchg_mode =
            CommandOptions::instance().getExchangeMode();
        if ((xchg_mode == CommandOptions::DORA_SARR) && solicit_pkt6) {
            // \todo check whether received ADVERTISE packet is sane.
            // We might want to check if STATUS_CODE option is non-zero
            // and if there is IAADR option in IA_NA.
            if (template_buffers_.size() < 2) {
                sendRequest6(socket, pkt6);
            } else {
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendRequest6(socket, template_buffers_[1], pkt6);
            }
        }
    } else if (packet_type == DHCPV6_REPLY) {
        // If the received message is Reply, we have to find out which exchange
        // type the Reply message belongs to. It is doable by matching the Reply
        // transaction id with the transaction id of the sent Request, Renew
        // or Release. First we start with the Request.
        if (stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_RR, pkt6)) {
            // The Reply belongs to Request-Reply exchange type. So, we may need
            // to keep this Reply in the storage if Renews or/and Releases are
            // being sent. Note that, Reply messages hold the information about
            // leases assigned. We use this information to construct Renew and
            // Release messages.
            if (stats_mgr6_->hasExchangeStats(StatsMgr6::XCHG_RN) ||
                stats_mgr6_->hasExchangeStats(StatsMgr6::XCHG_RL)) {
                // Renew or Release messages are sent, because StatsMgr has the
                // specific exchange type specified. Let's append the Reply
                // message to a storage.
                reply_storage_.append(pkt6);
            }
        // The Reply message is not a server's response to the Request message
        // sent within the 4-way exchange. It may be a response to the Renew
        // or Release message. In the if clause we first check if StatsMgr
        // has exchange type for Renew specified, and if it has, if there is
        // a corresponding Renew message for the received Reply. If not,
        // we check that StatsMgr has exchange type for Release specified,
        // as possibly the Reply has been sent in response to Release.
        } else if (!(stats_mgr6_->hasExchangeStats(StatsMgr6::XCHG_RN) &&
                     stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_RN, pkt6)) &&
                   stats_mgr6_->hasExchangeStats(StatsMgr6::XCHG_RL)) {
            // At this point, it is only possible that the Reply has been sent
            // in response to a Release. Try to match the Reply with Release.
            stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_RL, pkt6);
        }
    }
}

uint64_t
TestControl::receivePackets(const TestControlSocket& socket) {
    bool receiving = true;
    uint64_t received = 0;
    while (receiving) {
        if (CommandOptions::instance().getIpVersion() == 4) {
            Pkt4Ptr pkt4;
            try {
                pkt4 = IfaceMgr::instance().receive4(0, getCurrentTimeout());
            } catch (const Exception& e) {
                std::cerr << "Failed to receive DHCPv4 packet: "
                          << e.what() <<  std::endl;
            }
            if (!pkt4) {
                receiving = false;
            } else {
                ++received;
                if ((received > 1) && testDiags('i')) {
                    stats_mgr4_->incrementCounter("multircvd");
                }

                /// @todo: Add packet exception handling here. Right now any
                /// malformed packet will cause perfdhcp to abort.
                pkt4->unpack();
                processReceivedPacket4(socket, pkt4);
            }
        } else if (CommandOptions::instance().getIpVersion() == 6) {
            Pkt6Ptr pkt6;
            try {
                pkt6 = IfaceMgr::instance().receive6(0, getCurrentTimeout());
            } catch (const Exception& e) {
                std::cerr << "Failed to receive DHCPv6 packet: "
                          << e.what() << std::endl;
            }
            if (!pkt6) {
                receiving  = false;
            } else {
                ++received;
                if ((received > 1) && testDiags('i')) {
                    stats_mgr6_->incrementCounter("multircvd");
                }

                /// @todo: Add packet exception handling here. Right now any
                /// malformed packet will cause perfdhcp to abort.
                pkt6->unpack();
                processReceivedPacket6(socket, pkt6);
            }
        }
    }
    return (received);
}

void
TestControl::registerOptionFactories4() const {
    static bool factories_registered = false;
    if (!factories_registered) {
        // DHCP_MESSAGE_TYPE option factory.
        LibDHCP::OptionFactoryRegister(Option::V4,
                                       DHO_DHCP_MESSAGE_TYPE,
                                       &TestControl::factoryGeneric);
        // DHCP_SERVER_IDENTIFIER option factory.
        LibDHCP::OptionFactoryRegister(Option::V4,
                                       DHO_DHCP_SERVER_IDENTIFIER,
                                       &TestControl::factoryGeneric);
        // DHCP_PARAMETER_REQUEST_LIST option factory.
        LibDHCP::OptionFactoryRegister(Option::V4,
                                       DHO_DHCP_PARAMETER_REQUEST_LIST,
                                       &TestControl::factoryRequestList4);
    }
    factories_registered = true;
}

void
TestControl::registerOptionFactories6() const {
    static bool factories_registered = false;
    if (!factories_registered) {
        // D60_ELAPSED_TIME
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_ELAPSED_TIME,
                                       &TestControl::factoryElapsedTime6);
        // D6O_RAPID_COMMIT
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_RAPID_COMMIT,
                                       &TestControl::factoryRapidCommit6);
        // D6O_ORO (option request option) factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_ORO,
                                       &TestControl::factoryOptionRequestOption6);
        // D6O_CLIENTID option factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_CLIENTID,
                                       &TestControl::factoryGeneric);
        // D6O_SERVERID option factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_SERVERID,
                                       &TestControl::factoryGeneric);
        // D6O_IA_NA option factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_IA_NA,
                                       &TestControl::factoryIana6);

        // D6O_IA_PD option factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_IA_PD,
                                       &TestControl::factoryIapd6);


    }
    factories_registered = true;
}

void
TestControl::registerOptionFactories() const {
    CommandOptions& options = CommandOptions::instance();
    switch(options.getIpVersion()) {
    case 4:
        registerOptionFactories4();
        break;
    case 6:
        registerOptionFactories6();
        break;
    default:
        isc_throw(InvalidOperation, "command line options have to be parsed "
                  "before DHCP option factories can be registered");
    }
}

void
TestControl::reset() {
    CommandOptions& options = CommandOptions::instance();
    basic_rate_control_.setAggressivity(options.getAggressivity());
    basic_rate_control_.setRate(options.getRate());
    renew_rate_control_.setAggressivity(options.getAggressivity());
    renew_rate_control_.setRate(options.getRenewRate());
    release_rate_control_.setAggressivity(options.getAggressivity());
    release_rate_control_.setRate(options.getReleaseRate());

    transid_gen_.reset();
    last_report_ = microsec_clock::universal_time();
    // Actual generators will have to be set later on because we need to
    // get command line parameters first.
    setTransidGenerator(NumberGeneratorPtr());
    setMacAddrGenerator(NumberGeneratorPtr());
    first_packet_serverid_.clear();
    interrupted_ = false;
}

int
TestControl::run() {
    // Reset singleton state before test starts.
    reset();

    CommandOptions& options = CommandOptions::instance();
    // Ip version is not set ONLY in case the command options
    // were not parsed. This surely means that parse() function
    // was not called prior to starting the test. This is fatal
    // error.
    if (options.getIpVersion() == 0) {
        isc_throw(InvalidOperation,
                  "command options must be parsed before running a test");
    } else if (options.getIpVersion() == 4) {
        setTransidGenerator(NumberGeneratorPtr(new SequentialGenerator()));
    } else {
        setTransidGenerator(NumberGeneratorPtr(new SequentialGenerator(0x00FFFFFF)));
    }

    uint32_t clients_num = options.getClientsNum() == 0 ?
        1 : options.getClientsNum();
    setMacAddrGenerator(NumberGeneratorPtr(new SequentialGenerator(clients_num)));

    // Diagnostics are command line options mainly.
    printDiagnostics();
    // Option factories have to be registered.
    registerOptionFactories();
    TestControlSocket socket(openSocket());
    if (!socket.valid_) {
        isc_throw(Unexpected, "invalid socket descriptor");
    }
    // Initialize packet templates.
    initPacketTemplates();
    // Initialize randomization seed.
    if (options.isSeeded()) {
        srandom(options.getSeed());
    } else {
        // Seed with current time.
        time_period duration(from_iso_string("20111231T235959"),
                             microsec_clock::universal_time());
        srandom(duration.length().total_seconds()
                + duration.length().fractional_seconds());
    }
    // If user interrupts the program we will exit gracefully.
    signal(SIGINT, TestControl::handleInterrupt);

    // Preload server with the number of packets.
    sendPackets(socket, options.getPreload(), true);

    // Fork and run command specified with -w<wrapped-command>
    if (!options.getWrapped().empty()) {
        runWrapped();
    }

    // Initialize Statistics Manager. Release previous if any.
    initializeStatsMgr();
    for (;;) {
        // Calculate number of packets to be sent to stay
        // catch up with rate.
        uint64_t packets_due = basic_rate_control_.getOutboundMessageCount();
        checkLateMessages(basic_rate_control_);
        if ((packets_due == 0) && testDiags('i')) {
            if (options.getIpVersion() == 4) {
                stats_mgr4_->incrementCounter("shortwait");
            } else if (options.getIpVersion() == 6) {
                stats_mgr6_->incrementCounter("shortwait");
            }
        }

        // @todo: set non-zero timeout for packets once we implement
        // microseconds timeout in IfaceMgr.
        receivePackets(socket);

        // If test period finished, maximum number of packet drops
        // has been reached or test has been interrupted we have to
        // finish the test.
        if (checkExitConditions()) {
            break;
        }

        // Initiate new DHCP packet exchanges.
        sendPackets(socket, packets_due);

        // If -f<renew-rate> option was specified we have to check how many
        // Renew packets should be sent to catch up with a desired rate.
        if (options.getRenewRate() != 0) {
            uint64_t renew_packets_due =
                renew_rate_control_.getOutboundMessageCount();
            checkLateMessages(renew_rate_control_);

            // Send multiple renews to satify the desired rate.
            if (options.getIpVersion() == 4) {
                sendMultipleRequests(socket, renew_packets_due);
            } else {
                sendMultipleMessages6(socket, DHCPV6_RENEW, renew_packets_due);
            }
        }

        // If -F<release-rate> option was specified we have to check how many
        // Release messages should be sent to catch up with a desired rate.
        if ((options.getIpVersion() == 6) && (options.getReleaseRate() != 0)) {
            uint64_t release_packets_due =
                release_rate_control_.getOutboundMessageCount();
            checkLateMessages(release_rate_control_);
            // Send Release messages.
            sendMultipleMessages6(socket, DHCPV6_RELEASE, release_packets_due);
        }

        // Report delay means that user requested printing number
        // of sent/received/dropped packets repeatedly.
        if (options.getReportDelay() > 0) {
            printIntermediateStats();
        }

        // If we are sending Renews to the server, the Reply packets are cached
        // so as leases for which we send Renews can be idenitfied. The major
        // issue with this approach is that most of the time we are caching
        // more packets than we actually need. This function removes excessive
        // Reply messages to reduce the memory and CPU utilization. Note that
        // searches in the long list of Reply packets increases CPU utilization.
        cleanCachedPackets();
    }
    printStats();

    if (!options.getWrapped().empty()) {
        // true means that we execute wrapped command with 'stop' argument.
        runWrapped(true);
    }

    // Print packet timestamps
    if (testDiags('t')) {
        if (options.getIpVersion() == 4) {
            stats_mgr4_->printTimestamps();
        } else if (options.getIpVersion() == 6) {
            stats_mgr6_->printTimestamps();
        }
    }

    // Print server id.
    if (testDiags('s') && (first_packet_serverid_.size() > 0)) {
        std::cout << "Server id: " << vector2Hex(first_packet_serverid_) << std::endl;
    }

    // Diagnostics flag 'e' means show exit reason.
    if (testDiags('e')) {
        std::cout << "Interrupted" << std::endl;
    }
    // Print packet templates. Even if -T options have not been specified the
    // dynamically build packet will be printed if at least one has been sent.
    if (testDiags('T')) {
        printTemplates();
    }

    int ret_code = 0;
    // Check if any packet drops occured.
    if (options.getIpVersion() == 4) {
        ret_code = stats_mgr4_->droppedPackets() ? 3 : 0;
    } else if (options.getIpVersion() == 6)  {
        ret_code = stats_mgr6_->droppedPackets() ? 3 : 0;
    }
    return (ret_code);
}

void
TestControl::runWrapped(bool do_stop /*= false */) const {
    CommandOptions& options = CommandOptions::instance();
    if (!options.getWrapped().empty()) {
        pid_t pid = 0;
        signal(SIGCHLD, handleChild);
        pid = fork();
        if (pid < 0) {
            isc_throw(Unexpected, "unable to fork");
        } else if (pid == 0) {
            execlp(options.getWrapped().c_str(),
                   do_stop ? "stop" : "start",
                   NULL);
        }
    }
}

void
TestControl::saveFirstPacket(const Pkt4Ptr& pkt) {
    if (testDiags('T')) {
        if (template_packets_v4_.find(pkt->getType()) == template_packets_v4_.end()) {
            template_packets_v4_[pkt->getType()] = pkt;
        }
    }
}

void
TestControl::saveFirstPacket(const Pkt6Ptr& pkt) {
    if (testDiags('T')) {
        if (template_packets_v6_.find(pkt->getType()) == template_packets_v6_.end()) {
            template_packets_v6_[pkt->getType()] = pkt;
        }
    }
}

void
TestControl::sendDiscover4(const TestControlSocket& socket,
                           const bool preload /*= false*/) {
    basic_rate_control_.updateSendTime();
    // Generate the MAC address to be passed in the packet.
    uint8_t randomized = 0;
    std::vector<uint8_t> mac_address = generateMacAddress(randomized);
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, transid));
    if (!pkt4) {
        isc_throw(Unexpected, "failed to create DISCOVER packet");
    }

    // Delete the default Message Type option set by Pkt4
    pkt4->delOption(DHO_DHCP_MESSAGE_TYPE);

    // Set options: DHCP_MESSAGE_TYPE and DHCP_PARAMETER_REQUEST_LIST
    OptionBuffer buf_msg_type;
    buf_msg_type.push_back(DHCPDISCOVER);
    pkt4->addOption(Option::factory(Option::V4, DHO_DHCP_MESSAGE_TYPE,
                                    buf_msg_type));
    pkt4->addOption(Option::factory(Option::V4,
                                    DHO_DHCP_PARAMETER_REQUEST_LIST));

    // Set client's and server's ports as well as server's address,
    // and local (relay) address.
    setDefaults4(socket, pkt4);

    // Set hardware address
    pkt4->setHWAddr(HTYPE_ETHER, mac_address.size(), mac_address);

    // Set client identifier
    pkt4->addOption(generateClientId(pkt4->getHWAddr()));

    pkt4->pack();
    IfaceMgr::instance().send(pkt4);
    if (!preload) {
        if (!stats_mgr4_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                      "hasn't been initialized");
        }
        stats_mgr4_->passSentPacket(StatsMgr4::XCHG_DO, pkt4);
    }
    saveFirstPacket(pkt4);
}

void
TestControl::sendDiscover4(const TestControlSocket& socket,
                           const std::vector<uint8_t>& template_buf,
                           const bool preload /* = false */) {
    basic_rate_control_.updateSendTime();
    // Get the first argument if mulitple the same arguments specified
    // in the command line. First one refers to DISCOVER packets.
    const uint8_t arg_idx = 0;
    // Generate the MAC address to be passed in the packet.
    uint8_t randomized = 0;
    std::vector<uint8_t> mac_address = generateMacAddress(randomized);
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    // Get transaction id offset.
    size_t transid_offset = getTransactionIdOffset(arg_idx);
    // Get randomization offset.
    // We need to go back by HW_ETHER_LEN (MAC address length)
    // because this offset points to last octet of MAC address.
    size_t rand_offset = getRandomOffset(arg_idx) - HW_ETHER_LEN + 1;
    // Create temporary buffer with template contents. We will
    // modify this temporary buffer but we don't want to modify
    // the original template.
    std::vector<uint8_t> in_buf(template_buf.begin(),
                                template_buf.end());
    // Check if we are not going out of bounds.
    if (rand_offset + HW_ETHER_LEN > in_buf.size()) {
        isc_throw(OutOfRange, "randomization offset is out of bounds");
    }
    PerfPkt4Ptr pkt4(new PerfPkt4(&in_buf[0], in_buf.size(),
                                  transid_offset,
                                  transid));

    // Replace MAC address in the template with actual MAC address.
    pkt4->writeAt(rand_offset, mac_address.begin(), mac_address.end());
    // Create a packet from the temporary buffer.
    setDefaults4(socket, boost::static_pointer_cast<Pkt4>(pkt4));
    // Pack the input packet buffer to output buffer so as it can
    // be sent to server.
    pkt4->rawPack();
    IfaceMgr::instance().send(boost::static_pointer_cast<Pkt4>(pkt4));
    if (!preload) {
        if (!stats_mgr4_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                      "hasn't been initialized");
        }
        // Update packet stats.
        stats_mgr4_->passSentPacket(StatsMgr4::XCHG_DO,
                                    boost::static_pointer_cast<Pkt4>(pkt4));
    }
    saveFirstPacket(pkt4);
}

bool
TestControl::sendRequestFromAck(const TestControlSocket& socket) {
    // Update timestamp of last sent renewal.
    renew_rate_control_.updateSendTime();

    // Get one of the recorded DHCPACK messages.
    Pkt4Ptr ack = ack_storage_.getRandom();
    if (!ack) {
        return (false);
    }

    // Create message of the specified type.
    Pkt4Ptr msg = createRequestFromAck(ack);
    setDefaults4(socket, msg);
    msg->pack();
    // And send it.
    IfaceMgr::instance().send(msg);
    if (!stats_mgr4_) {
        isc_throw(Unexpected, "Statistics Manager for DHCPv4 "
                  "hasn't been initialized");
    }
    stats_mgr4_->passSentPacket(StatsMgr4::XCHG_RN, msg);
    return (true);
}


bool
TestControl::sendMessageFromReply(const uint16_t msg_type,
                                  const TestControlSocket& socket) {
    // We only permit Release or Renew messages to be sent using this function.
    if (msg_type != DHCPV6_RENEW && msg_type != DHCPV6_RELEASE) {
        isc_throw(isc::BadValue, "invalid message type " << msg_type
                  << " to be sent, expected DHCPV6_RENEW or DHCPV6_RELEASE");
    }
    // We track the timestamp of last Release and Renew in different variables.
    if (msg_type == DHCPV6_RENEW) {
        renew_rate_control_.updateSendTime();
    } else {
        release_rate_control_.updateSendTime();
    }
    Pkt6Ptr reply = reply_storage_.getRandom();
    if (!reply) {
        return (false);
    }
    // Prepare the message of the specified type.
    Pkt6Ptr msg = createMessageFromReply(msg_type, reply);
    setDefaults6(socket, msg);
    msg->pack();
    // And send it.
    IfaceMgr::instance().send(msg);
    if (!stats_mgr6_) {
        isc_throw(Unexpected, "Statistics Manager for DHCPv6 "
                  "hasn't been initialized");
    }
    stats_mgr6_->passSentPacket((msg_type == DHCPV6_RENEW ? StatsMgr6::XCHG_RN
                                 : StatsMgr6::XCHG_RL), msg);
    return (true);
}

void
TestControl::sendRequest4(const TestControlSocket& socket,
                          const dhcp::Pkt4Ptr& discover_pkt4,
                          const dhcp::Pkt4Ptr& offer_pkt4) {
    const uint32_t transid = generateTransid();
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, transid));

    // Use first flags indicates that we want to use the server
    // id captured in first packet.
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        pkt4->addOption(Option::factory(Option::V4, DHO_DHCP_SERVER_IDENTIFIER,
                                        first_packet_serverid_));
    } else {
        OptionPtr opt_serverid =
            offer_pkt4->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        if (!opt_serverid) {
            isc_throw(BadValue, "there is no SERVER_IDENTIFIER option "
                      << "in OFFER message");
        }
        if (stats_mgr4_->getRcvdPacketsNum(StatsMgr4::XCHG_DO) == 1) {
            first_packet_serverid_ = opt_serverid->getData();
        }
        pkt4->addOption(opt_serverid);
    }

    /// Set client address.
    asiolink::IOAddress yiaddr = offer_pkt4->getYiaddr();
    if (!yiaddr.isV4()) {
        isc_throw(BadValue, "the YIADDR returned in OFFER packet is not "
                  " IPv4 address");
    }
    OptionPtr opt_requested_address =
        OptionPtr(new Option(Option::V4, DHO_DHCP_REQUESTED_ADDRESS,
                             OptionBuffer()));
    opt_requested_address->setUint32(static_cast<uint32_t>(yiaddr));
    pkt4->addOption(opt_requested_address);
    OptionPtr opt_parameter_list =
        Option::factory(Option::V4, DHO_DHCP_PARAMETER_REQUEST_LIST);
    pkt4->addOption(opt_parameter_list);
    // Set client's and server's ports as well as server's address,
    // and local (relay) address.
    setDefaults4(socket, pkt4);

    // Set hardware address
    pkt4->setHWAddr(offer_pkt4->getHWAddr());
    // Set client id.
    pkt4->addOption(generateClientId(pkt4->getHWAddr()));
    // Set elapsed time.
    uint32_t elapsed_time = getElapsedTime<Pkt4Ptr>(discover_pkt4, offer_pkt4);
    pkt4->setSecs(static_cast<uint16_t>(elapsed_time / 1000));
    // Prepare on wire data to send.
    pkt4->pack();
    IfaceMgr::instance().send(pkt4);
    if (!stats_mgr4_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                  "hasn't been initialized");
    }
    stats_mgr4_->passSentPacket(StatsMgr4::XCHG_RA, pkt4);
    saveFirstPacket(pkt4);
}

void
TestControl::sendRequest4(const TestControlSocket& socket,
                          const std::vector<uint8_t>& template_buf,
                          const dhcp::Pkt4Ptr& discover_pkt4,
                          const dhcp::Pkt4Ptr& offer_pkt4) {
    // Get the second argument if multiple the same arguments specified
    // in the command line. Second one refers to REQUEST packets.
    const uint8_t arg_idx = 1;
    // Generate new transaction id.
    const uint32_t transid = generateTransid();
    // Get transaction id offset.
    size_t transid_offset = getTransactionIdOffset(arg_idx);
    // Get the offset of MAC's last octet.
    // We need to go back by HW_ETHER_LEN (MAC address length)
    // because this offset points to last octet of MAC address.
    size_t rand_offset = getRandomOffset(arg_idx) - HW_ETHER_LEN + 1;
    // Create temporaru buffer from the template.
    std::vector<uint8_t> in_buf(template_buf.begin(),
                                template_buf.end());
    // Check if given randomization offset is not out of bounds.
    if (rand_offset + HW_ETHER_LEN > in_buf.size()) {
        isc_throw(OutOfRange, "randomization offset is out of bounds");
    }

    // Create packet from the temporary buffer.
    PerfPkt4Ptr pkt4(new PerfPkt4(&in_buf[0], in_buf.size(),
                                  transid_offset,
                                  transid));

     // Set hardware address from OFFER packet received.
    HWAddrPtr hwaddr = offer_pkt4->getHWAddr();
    std::vector<uint8_t> mac_address(HW_ETHER_LEN, 0);
    uint8_t hw_len = hwaddr->hwaddr_.size();
    if (hw_len != 0) {
        memcpy(&mac_address[0], &hwaddr->hwaddr_[0],
               hw_len > HW_ETHER_LEN ? HW_ETHER_LEN : hw_len);
    }
    pkt4->writeAt(rand_offset, mac_address.begin(), mac_address.end());

    // Set elapsed time.
    size_t elp_offset = getElapsedTimeOffset();
    uint32_t elapsed_time = getElapsedTime<Pkt4Ptr>(discover_pkt4, offer_pkt4);
    pkt4->writeValueAt<uint16_t>(elp_offset,
                                 static_cast<uint16_t>(elapsed_time / 1000));

    // Get the actual server id offset.
    size_t sid_offset = getServerIdOffset();
    // Use first flags indicates that we want to use the server
    // id captured in first packet.
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V4,
                                             DHO_DHCP_SERVER_IDENTIFIER,
                                             first_packet_serverid_,
                                             sid_offset));
        pkt4->addOption(opt_serverid);
    } else {
        // Copy the contents of server identifier received in
        // OFFER packet to put this into REQUEST.
        OptionPtr opt_serverid_offer =
            offer_pkt4->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        if (!opt_serverid_offer) {
            isc_throw(BadValue, "there is no SERVER_IDENTIFIER option "
                      << "in OFFER message");
        }
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V4,
                                             DHO_DHCP_SERVER_IDENTIFIER,
                                             opt_serverid_offer->getData(),
                                             sid_offset));
        pkt4->addOption(opt_serverid);
        if (stats_mgr4_->getRcvdPacketsNum(StatsMgr4::XCHG_DO) == 1) {
            first_packet_serverid_ = opt_serverid_offer->getData();
        }
    }

    /// Set client address.
    asiolink::IOAddress yiaddr = offer_pkt4->getYiaddr();
    if (!yiaddr.isV4()) {
        isc_throw(BadValue, "the YIADDR returned in OFFER packet is not "
                  " IPv4 address");
    }

    // Get the actual offset of requested ip.
    size_t rip_offset = getRequestedIpOffset();
    // Place requested IP option at specified position (rip_offset).
    boost::shared_ptr<LocalizedOption>
        opt_requested_ip(new LocalizedOption(Option::V4,
                                             DHO_DHCP_REQUESTED_ADDRESS,
                                             OptionBuffer(),
                                             rip_offset));
    // The IOAddress is castable to uint32_t and returns exactly what we need.
    opt_requested_ip->setUint32(static_cast<uint32_t>(yiaddr));
    pkt4->addOption(opt_requested_ip);

    setDefaults4(socket, boost::static_pointer_cast<Pkt4>(pkt4));
    // Prepare on-wire data.
    pkt4->rawPack();
    IfaceMgr::instance().send(boost::static_pointer_cast<Pkt4>(pkt4));
    if (!stats_mgr4_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                  "hasn't been initialized");
    }
    // Update packet stats.
    stats_mgr4_->passSentPacket(StatsMgr4::XCHG_RA,
                                boost::static_pointer_cast<Pkt4>(pkt4));
    saveFirstPacket(pkt4);
}

void
TestControl::sendRequest6(const TestControlSocket& socket,
                          const Pkt6Ptr& advertise_pkt6) {
    const uint32_t transid = generateTransid();
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REQUEST, transid));
    // Set elapsed time.
    OptionPtr opt_elapsed_time =
        Option::factory(Option::V6, D6O_ELAPSED_TIME);
    pkt6->addOption(opt_elapsed_time);
    // Set client id.
    OptionPtr opt_clientid = advertise_pkt6->getOption(D6O_CLIENTID);
    if (!opt_clientid) {
        isc_throw(Unexpected, "client id not found in received packet");
    }
    pkt6->addOption(opt_clientid);

    // Use first flags indicates that we want to use the server
    // id captured in first packet.
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        pkt6->addOption(Option::factory(Option::V6, D6O_SERVERID,
                                        first_packet_serverid_));
    } else {
        OptionPtr opt_serverid = advertise_pkt6->getOption(D6O_SERVERID);
        if (!opt_serverid) {
            isc_throw(Unexpected, "server id not found in received packet");
        }
        if (stats_mgr6_->getRcvdPacketsNum(StatsMgr6::XCHG_SA) == 1) {
            first_packet_serverid_ = opt_serverid->getData();
        }
        pkt6->addOption(opt_serverid);
    }

    // Copy IA_NA or IA_PD option from the Advertise message to the Request
    // message being sent to the server. This will throw exception if the
    // option to be copied is not found. Note that this function will copy
    // one of IA_NA or IA_PD options, depending on the lease-type value
    // specified in the command line.
    copyIaOptions(advertise_pkt6, pkt6);

    // Set default packet data.
    setDefaults6(socket, pkt6);
    // Prepare on-wire data.
    pkt6->pack();
    IfaceMgr::instance().send(pkt6);
    if (!stats_mgr6_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                  "hasn't been initialized");
    }
    stats_mgr6_->passSentPacket(StatsMgr6::XCHG_RR, pkt6);
    saveFirstPacket(pkt6);
}

void
TestControl::sendRequest6(const TestControlSocket& socket,
                          const std::vector<uint8_t>& template_buf,
                          const Pkt6Ptr& advertise_pkt6) {
    // Get the second argument if multiple the same arguments specified
    // in the command line. Second one refers to REQUEST packets.
    const uint8_t arg_idx = 1;
    // Generate transaction id.
    const uint32_t transid = generateTransid();
    // Get transaction id offset.
    size_t transid_offset = getTransactionIdOffset(arg_idx);
    PerfPkt6Ptr pkt6(new PerfPkt6(&template_buf[0], template_buf.size(),
                                  transid_offset, transid));
    // Set elapsed time.
    size_t elp_offset = getElapsedTimeOffset();
    boost::shared_ptr<LocalizedOption>
        opt_elapsed_time(new LocalizedOption(Option::V6, D6O_ELAPSED_TIME,
                                             OptionBuffer(), elp_offset));
    pkt6->addOption(opt_elapsed_time);

    // Get the actual server id offset.
    size_t sid_offset = getServerIdOffset();
    // Use first flags indicates that we want to use the server
    // id captured in first packet.
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V6,
                                             D6O_SERVERID,
                                             first_packet_serverid_,
                                             sid_offset));
        pkt6->addOption(opt_serverid);

    } else {
        // Copy the contents of server identifier received in
        // ADVERTISE packet to put this into REQUEST.
        OptionPtr opt_serverid_advertise =
            advertise_pkt6->getOption(D6O_SERVERID);
        if (!opt_serverid_advertise) {
            isc_throw(BadValue, "there is no SERVERID option "
                      << "in ADVERTISE message");
        }
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V6,
                                             D6O_SERVERID,
                                             opt_serverid_advertise->getData(),
                                             sid_offset));
        pkt6->addOption(opt_serverid);
        if (stats_mgr6_->getRcvdPacketsNum(StatsMgr6::XCHG_SA) == 1) {
            first_packet_serverid_ = opt_serverid_advertise->getData();
        }
    }
    // Set IA_NA
    boost::shared_ptr<Option6IA> opt_ia_na_advertise =
        boost::static_pointer_cast<Option6IA>(advertise_pkt6->getOption(D6O_IA_NA));
    if (!opt_ia_na_advertise) {
        isc_throw(Unexpected, "DHCPv6 IA_NA option not found in received "
                  "packet");
    }
    size_t addr_offset = getRequestedIpOffset();
    boost::shared_ptr<LocalizedOption>
        opt_ia_na(new LocalizedOption(opt_ia_na_advertise, addr_offset));
    if (!opt_ia_na->valid()) {
        isc_throw(BadValue, "Option IA_NA in advertise packet is invalid");
    }
    pkt6->addOption(opt_ia_na);
    // Set server id.
    OptionPtr opt_serverid_advertise = advertise_pkt6->getOption(D6O_SERVERID);
    if (!opt_serverid_advertise) {
        isc_throw(Unexpected, "DHCPV6 SERVERID option not found in received "
                  "packet");
    }
    size_t srvid_offset = getServerIdOffset();
    boost::shared_ptr<LocalizedOption>
        opt_serverid(new LocalizedOption(Option::V6, D6O_SERVERID,
                                         opt_serverid_advertise->getData(),
                                         srvid_offset));
    pkt6->addOption(opt_serverid);
    // Get randomization offset.
    size_t rand_offset = getRandomOffset(arg_idx);
    OptionPtr opt_clientid_advertise = advertise_pkt6->getOption(D6O_CLIENTID);
    if (!opt_clientid_advertise) {
        isc_throw(Unexpected, "DHCPV6 CLIENTID option not found in received packet");
    }
    rand_offset -= (opt_clientid_advertise->len() - 1);
    // Set client id.
    boost::shared_ptr<LocalizedOption>
        opt_clientid(new LocalizedOption(Option::V6, D6O_CLIENTID,
                                         opt_clientid_advertise->getData(),
                                         rand_offset));
    pkt6->addOption(opt_clientid);
    // Set default packet data.
    setDefaults6(socket, pkt6);
    // Prepare on wire data.
    pkt6->rawPack();
    // Send packet.
    IfaceMgr::instance().send(pkt6);
    if (!stats_mgr6_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                  "hasn't been initialized");
    }
    // Update packet stats.
    stats_mgr6_->passSentPacket(StatsMgr6::XCHG_RR, pkt6);

    // When 'T' diagnostics flag is specified it means that user requested
    // printing packet contents. It will be just one (first) packet which
    // contents will be printed. Here we check if this packet has been already
    // collected. If it hasn't we save this packet so as we can print its
    // contents when test is finished.
    if (testDiags('T') &&
        (template_packets_v6_.find(DHCPV6_REQUEST) == template_packets_v6_.end())) {
        template_packets_v6_[DHCPV6_REQUEST] = pkt6;
    }
}

void
TestControl::sendSolicit6(const TestControlSocket& socket,
                          const bool preload /*= false*/) {
    basic_rate_control_.updateSendTime();
    // Generate DUID to be passed to the packet
    uint8_t randomized = 0;
    std::vector<uint8_t> duid = generateDuid(randomized);
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
    if (!pkt6) {
        isc_throw(Unexpected, "failed to create SOLICIT packet");
    }
    pkt6->addOption(Option::factory(Option::V6, D6O_ELAPSED_TIME));
    if (CommandOptions::instance().isRapidCommit()) {
        pkt6->addOption(Option::factory(Option::V6, D6O_RAPID_COMMIT));
    }
    pkt6->addOption(Option::factory(Option::V6, D6O_CLIENTID, duid));
    pkt6->addOption(Option::factory(Option::V6, D6O_ORO));

    // Depending on the lease-type option specified, we should request
    // IPv6 address (with IA_NA) or IPv6 prefix (IA_PD) or both.

    // IA_NA
    if (CommandOptions::instance().getLeaseType()
        .includes(CommandOptions::LeaseType::ADDRESS)) {
        pkt6->addOption(Option::factory(Option::V6, D6O_IA_NA));
    }
    // IA_PD
    if (CommandOptions::instance().getLeaseType()
        .includes(CommandOptions::LeaseType::PREFIX)) {
        pkt6->addOption(Option::factory(Option::V6, D6O_IA_PD));
    }

    setDefaults6(socket, pkt6);
    pkt6->pack();
    IfaceMgr::instance().send(pkt6);
    if (!preload) {
        if (!stats_mgr6_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                      "hasn't been initialized");
        }
        stats_mgr6_->passSentPacket(StatsMgr6::XCHG_SA, pkt6);
    }

    saveFirstPacket(pkt6);
}

void
TestControl::sendSolicit6(const TestControlSocket& socket,
                          const std::vector<uint8_t>& template_buf,
                          const bool preload /*= false*/) {
    basic_rate_control_.updateSendTime();
    const int arg_idx = 0;
    // Get transaction id offset.
    size_t transid_offset = getTransactionIdOffset(arg_idx);
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    // Create packet.
    PerfPkt6Ptr pkt6(new PerfPkt6(&template_buf[0], template_buf.size(),
                                  transid_offset, transid));
    if (!pkt6) {
        isc_throw(Unexpected, "failed to create SOLICIT packet");
    }
    size_t rand_offset = getRandomOffset(arg_idx);
    // randomized will pick number of bytes randomized so we can
    // just use part of the generated duid and substitude a few bytes
    /// in template.
    uint8_t randomized = 0;
    std::vector<uint8_t> duid = generateDuid(randomized);
    if (rand_offset > template_buf.size()) {
        isc_throw(OutOfRange, "randomization offset is out of bounds");
    }
    // Store random part of the DUID into the packet.
    pkt6->writeAt(rand_offset - randomized + 1,
                  duid.end() - randomized, duid.end());

    // Prepare on-wire data.
    pkt6->rawPack();
    setDefaults6(socket, pkt6);
    // Send solicit packet.
    IfaceMgr::instance().send(pkt6);
    if (!preload) {
        if (!stats_mgr6_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                      "hasn't been initialized");
        }
        // Update packet stats.
        stats_mgr6_->passSentPacket(StatsMgr6::XCHG_SA, pkt6);
    }
    saveFirstPacket(pkt6);
}


void
TestControl::setDefaults4(const TestControlSocket& socket,
                          const Pkt4Ptr& pkt) {
    CommandOptions& options = CommandOptions::instance();
    // Interface name.
    IfacePtr iface = IfaceMgr::instance().getIface(socket.ifindex_);
    if (iface == NULL) {
        isc_throw(BadValue, "unable to find interface with given index");
    }
    pkt->setIface(iface->getName());
    // Interface index.
    pkt->setIndex(socket.ifindex_);
    // Local client's port (68)
    pkt->setLocalPort(DHCP4_CLIENT_PORT);
    // Server's port (67)
    pkt->setRemotePort(DHCP4_SERVER_PORT);
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options.getServerName()));
    // Set local address.
    pkt->setLocalAddr(IOAddress(socket.addr_));
    // Set relay (GIADDR) address to local address.
    pkt->setGiaddr(IOAddress(socket.addr_));
    // Pretend that we have one relay (which is us).
    pkt->setHops(1);
}

void
TestControl::setDefaults6(const TestControlSocket& socket,
                          const Pkt6Ptr& pkt) {
    CommandOptions& options = CommandOptions::instance();
    // Interface name.
    IfacePtr iface = IfaceMgr::instance().getIface(socket.ifindex_);
    if (iface == NULL) {
        isc_throw(BadValue, "unable to find interface with given index");
    }
    pkt->setIface(iface->getName());
    // Interface index.
    pkt->setIndex(socket.ifindex_);
    // Local client's port (547)
    pkt->setLocalPort(DHCP6_CLIENT_PORT);
    // Server's port (548)
    pkt->setRemotePort(DHCP6_SERVER_PORT);
    // Set local address.
    pkt->setLocalAddr(socket.addr_);
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options.getServerName()));
}

bool
TestControl::testDiags(const char diag) const {
    std::string diags(CommandOptions::instance().getDiags());
    if (diags.find(diag) != std::string::npos) {
        return (true);
    }
    return (false);
}

} // namespace perfdhcp
} // namespace isc
