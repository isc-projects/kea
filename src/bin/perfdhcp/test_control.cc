// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <perfdhcp/test_control.h>
#include <perfdhcp/receiver.h>
#include <perfdhcp/command_options.h>
#include <perfdhcp/perf_pkt4.h>
#include <perfdhcp/perf_pkt6.h>

#include <exceptions/exceptions.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option_int.h>
#include <util/unittests/check_valgrind.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <sstream>
#include <sys/wait.h>

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace perfdhcp {

bool TestControl::interrupted_ = false;

bool
TestControl::waitToExit() {
    uint32_t const wait_time = options_.getExitWaitTime();

    // If we care and not all packets are in yet
    if (wait_time && !haveAllPacketsBeenReceived()) {
        const ptime now = microsec_clock::universal_time();

        // Init the end time if it hasn't started yet
        if (exit_time_.is_not_a_date_time()) {
            exit_time_ = now + time_duration(microseconds(wait_time));
        }

        // If we're not at end time yet, return true
        return (now < exit_time_);
    }

    // No need to wait, return false;
    return (false);
}

bool
TestControl::haveAllPacketsBeenReceived() const {
    const uint8_t& ipversion = options_.getIpVersion();
    const std::vector<int>& num_request = options_.getNumRequests();
    const size_t& num_request_size = num_request.size();

    if (num_request_size == 0) {
        return false;
    }

    uint32_t responses = 0;
    uint32_t requests = num_request[0];
    if (num_request_size >= 2) {
        requests += num_request[1];
    }

    if (ipversion == 4) {
        responses = stats_mgr_.getRcvdPacketsNum(ExchangeType::DO) +
                    stats_mgr_.getRcvdPacketsNum(ExchangeType::RA);
    } else {
        responses = stats_mgr_.getRcvdPacketsNum(ExchangeType::SA) +
                    stats_mgr_.getRcvdPacketsNum(ExchangeType::RR);
    }

    return (responses == requests);
}

void
TestControl::cleanCachedPackets() {
    // When Renews are not sent, Reply packets are not cached so there
    // is nothing to do.
    if (options_.getRenewRate() == 0) {
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
        /// @todo The cache size might be controlled from the command line.
        if (reply_storage_.size() > 5 * options_.getRenewRate()) {
            reply_storage_.clear(reply_storage_.size() -
                                 5 * options_.getRenewRate());
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
    if (options_.getLeaseType()
        .includes(CommandOptions::LeaseType::ADDRESS)) {
        OptionPtr option = pkt_from->getOption(D6O_IA_NA);
        if (!option) {
            isc_throw(NotFound, "IA_NA option not found in the"
                      " server's response");
        }
        pkt_to->addOption(option);
    }
    // IA_PD
    if (options_.getLeaseType()
        .includes(CommandOptions::LeaseType::PREFIX)) {
        OptionPtr option = pkt_from->getOption(D6O_IA_PD);
        if (!option) {
            isc_throw(NotFound, "IA_PD option not found in the"
                      " server's response");
        }
        pkt_to->addOption(option);
    }
}

std::string
TestControl::byte2Hex(const uint8_t b) {
    const int b1 = b / 16;
    const int b0 = b % 16;
    ostringstream stream;
    stream << std::hex << b1 << b0 << std::dec;
    return (stream.str());
}

Pkt4Ptr
TestControl::createMessageFromAck(const uint16_t msg_type,
                                  const dhcp::Pkt4Ptr& ack) {
    // Restrict messages to Release and Renew.
    if (msg_type != DHCPREQUEST && msg_type != DHCPRELEASE) {
        isc_throw(isc::BadValue, "invalid message type " << msg_type
                  << " to be created from Reply, expected DHCPREQUEST or"
                  " DHCPRELEASE");
    }

    // Get the string representation of the message - to be used for error
    // logging purposes.
    auto msg_type_str = [=]() -> const char* {
        return (msg_type == DHCPREQUEST ? "Request" : "Release");
    };

    if (!ack) {
        isc_throw(isc::BadValue, "Unable to create "
                                     << msg_type_str()
                                     << " from a null DHCPACK message");
    } else if (ack->getYiaddr().isV4Zero()) {
        isc_throw(isc::BadValue,
                  "Unable to create "
                      << msg_type_str()
                      << " from a DHCPACK message containing yiaddr of 0");
    }
    Pkt4Ptr msg(new Pkt4(msg_type, generateTransid()));
    msg->setCiaddr(ack->getYiaddr());
    msg->setHWAddr(ack->getHWAddr());
    msg->addOption(generateClientId(msg->getHWAddr()));
    if (msg_type == DHCPRELEASE) {
        // RFC 2132: DHCPRELEASE MUST include server ID.
        if (options_.isUseFirst()) {
            // Honor the '-1' flag if it exists.
            if (first_packet_serverid_.empty()) {
                isc_throw(isc::BadValue,
                          "Unable to create "
                              << msg_type_str()
                              << "from the first packet which lacks the server "
                                 "identifier option");
            }
            msg->addOption(Option::factory(Option::V4,
                                           DHO_DHCP_SERVER_IDENTIFIER,
                                           first_packet_serverid_));
        } else {
            // Otherwise take it from the DHCPACK message.
            OptionPtr server_identifier(
                ack->getOption(DHO_DHCP_SERVER_IDENTIFIER));
            if (!server_identifier) {
                isc_throw(isc::BadValue,
                          "Unable to create "
                              << msg_type_str()
                              << "from a DHCPACK message without the server "
                                 "identifier option");
            }
            msg->addOption(server_identifier);
        }
    }
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
    auto msg_type_str = [=]() -> const char* {
        return (msg_type == DHCPV6_RENEW ? "Renew" : "Release");
    };

    // Reply message must be specified.
    if (!reply) {
        isc_throw(isc::BadValue, "Unable to create " << msg_type_str()
                  << " message from the Reply message because the instance of"
                  " the Reply message is NULL");
    }

    Pkt6Ptr msg(new Pkt6(msg_type, generateTransid()));
    // Client id.
    OptionPtr opt_clientid = reply->getOption(D6O_CLIENTID);
    if (!opt_clientid) {
        isc_throw(isc::Unexpected, "failed to create " << msg_type_str()
                  << " message because client id option has not been found"
                  " in the Reply message");
    }
    msg->addOption(opt_clientid);
    // Server id.
    OptionPtr opt_serverid = reply->getOption(D6O_SERVERID);
    if (!opt_serverid) {
        isc_throw(isc::Unexpected, "failed to create " << msg_type_str()
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
    /// @todo allow different values of T1, T2 and IAID.
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
    /// @todo allow different values of T1, T2 and IAID.
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
TestControl::generateMacAddress(uint8_t& randomized) {
    const CommandOptions::MacAddrsVector& macs = options_.getMacsFromFile();
    // if we are using the -M option return a random one from the list...
    if (macs.size() > 0) {
      uint16_t r = number_generator_();
      if (r >= macs.size()) {
        r = 0;
      }
      return macs[r];

    } else {
      // ... otherwise use the standard behavior
      uint32_t clients_num = options_.getClientsNum();
      if (clients_num < 2) {
          return (options_.getMacTemplate());
      }
      // Get the base MAC address. We are going to randomize part of it.
      std::vector<uint8_t> mac_addr(options_.getMacTemplate());
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
TestControl::generateDuid(uint8_t& randomized) {
    std::vector<uint8_t> mac_addr(generateMacAddress(randomized));
    const CommandOptions::MacAddrsVector& macs = options_.getMacsFromFile();
    // pick a random mac address if we are using option -M..
    if (macs.size() > 0) {
      uint16_t r = number_generator_();
      if (r >= macs.size()) {
        r = 0;
      }
      std::vector<uint8_t> mac = macs[r];
      // DUID_LL is in this format
      //  0                   1                   2                   3
      //  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      // |               3               |    hardware type (16 bits)    |
      // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      // .                                                               .
      // .             link-layer address (variable length)              .
      // .                                                               .
      // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

      // No C++11 so initializer list support, building a vector<uint8_t> is a
      // pain...
      uint8_t duid_ll[] = {0, 3, 0, 1, 0, 0, 0, 0, 0, 0};
      // copy duid_ll array into the vector
      std::vector<uint8_t> duid(duid_ll,
                                duid_ll + sizeof(duid_ll) / sizeof(duid_ll[0]));
      // put the mac address bytes at the end
      std::copy(mac.begin(), mac.end(), duid.begin() + 4);
      return (duid);
    } else {
      uint32_t clients_num = options_.getClientsNum();
      if ((clients_num == 0) || (clients_num == 1)) {
          return (options_.getDuidTemplate());
      }
      // Get the base DUID. We are going to randomize part of it.
      std::vector<uint8_t> duid(options_.getDuidTemplate());
      /// @todo: add support for DUIDs of different sizes.
      duid.resize(duid.size());
      std::copy(mac_addr.begin(), mac_addr.end(),
                duid.begin() + duid.size() - mac_addr.size());
      return (duid);
    }
}

int
TestControl::getElapsedTimeOffset() const {
    int elp_offset = options_.getIpVersion() == 4 ?
        DHCPV4_ELAPSED_TIME_OFFSET : DHCPV6_ELAPSED_TIME_OFFSET;
    if (options_.getElapsedTimeOffset() > 0) {
        elp_offset = options_.getElapsedTimeOffset();
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
    int rand_offset = options_.getIpVersion() == 4 ?
        DHCPV4_RANDOMIZATION_OFFSET : DHCPV6_RANDOMIZATION_OFFSET;
    if (options_.getRandomOffset().size() > arg_idx) {
        rand_offset = options_.getRandomOffset()[arg_idx];
    }
    return (rand_offset);
}

int
TestControl::getRequestedIpOffset() const {
    int rip_offset = options_.getIpVersion() == 4 ?
        DHCPV4_REQUESTED_IP_OFFSET : DHCPV6_IA_NA_OFFSET;
    if (options_.getRequestedIpOffset() > 0) {
        rip_offset = options_.getRequestedIpOffset();
    }
    return (rip_offset);
}

int
TestControl::getServerIdOffset() const {
    int srvid_offset = options_.getIpVersion() == 4 ?
        DHCPV4_SERVERID_OFFSET : DHCPV6_SERVERID_OFFSET;
    if (options_.getServerIdOffset() > 0) {
        srvid_offset = options_.getServerIdOffset();
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
    int xid_offset = options_.getIpVersion() == 4 ?
        DHCPV4_TRANSID_OFFSET : DHCPV6_TRANSID_OFFSET;
    if (options_.getTransactionIdOffset().size() > arg_idx) {
        xid_offset = options_.getTransactionIdOffset()[arg_idx];
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
    std::vector<std::string> template_files = options_.getTemplateFiles();
    for (std::vector<std::string>::const_iterator it = template_files.begin();
         it != template_files.end(); ++it) {
        readPacketTemplate(*it);
    }
}

void
TestControl::sendPackets(const uint64_t packets_num,
                         const bool preload /* = false */) {
    for (uint64_t i = packets_num; i > 0; --i) {
        if (options_.getIpVersion() == 4) {
            // No template packets means that no -T option was specified.
            // We have to build packets ourselves.
            if (template_buffers_.empty()) {
                sendDiscover4(preload);
            } else {
                /// @todo add defines for packet type index that can be
                /// used to access template_buffers_.
                sendDiscover4(template_buffers_[0], preload);
            }
        } else {
            // No template packets means that no -T option was specified.
            // We have to build packets ourselves.
            if (template_buffers_.empty()) {
                sendSolicit6(preload);
            } else {
                /// @todo add defines for packet type index that can be
                /// used to access template_buffers_.
                sendSolicit6(template_buffers_[0], preload);
            }
        }
    }
}

uint64_t
TestControl::sendMultipleMessages4(const uint32_t msg_type,
                                   const uint64_t msg_num) {
    for (uint64_t i = 0; i < msg_num; ++i) {
        if (!sendMessageFromAck(msg_type)) {
            return (i);
        }
    }
    return (msg_num);
}

uint64_t
TestControl::sendMultipleMessages6(const uint32_t msg_type,
                                   const uint64_t msg_num) {
    for (uint64_t i = 0; i < msg_num; ++i) {
        if (!sendMessageFromReply(msg_type)) {
            return (i);
        }
    }
    return (msg_num);
}

void
TestControl::printDiagnostics() const {
    if (options_.testDiags('a')) {
        // Print all command line parameters.
        options_.printCommandLine();
        // Print MAC and DUID.
        std::cout << "Set MAC to " << vector2Hex(options_.getMacTemplate(), "::")
                  << std::endl;
        if (options_.getDuidTemplate().size() > 0) {
            std::cout << "Set DUID to " << vector2Hex(options_.getDuidTemplate()) << std::endl;
        }
    }
}

void
TestControl::printTemplate(const uint8_t packet_type) const {
    std::string hex_buf;
    int arg_idx = 0;
    if (options_.getIpVersion() == 4) {
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
    } else if (options_.getIpVersion() == 6) {
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
    if (options_.getIpVersion() == 4) {
        printTemplate(DHCPDISCOVER);
        printTemplate(DHCPREQUEST);
    } else if (options_.getIpVersion() == 6) {
        printTemplate(DHCPV6_SOLICIT);
        printTemplate(DHCPV6_REQUEST);
    }
}

void
TestControl::printRate() const {
    double rate = 0;
    std::string exchange_name = "4-way exchanges";
    ExchangeType xchg_type = ExchangeType::DO;
    if (options_.getIpVersion() == 4) {
        xchg_type =
            options_.getExchangeMode() == CommandOptions::DO_SA ?
            ExchangeType::DO : ExchangeType::RA;
        if (xchg_type == ExchangeType::DO) {
            exchange_name = "DISCOVER-OFFER";
        }
    } else if (options_.getIpVersion() == 6) {
        xchg_type =
            options_.getExchangeMode() == CommandOptions::DO_SA ?
            ExchangeType::SA : ExchangeType::RR;
        if (xchg_type == ExchangeType::SA) {
            exchange_name = options_.isRapidCommit() ? "Solicit-Reply" :
                "Solicit-Advertise";
        }
    }
    double duration =
        stats_mgr_.getTestPeriod().length().total_nanoseconds() / 1e9;
    rate = stats_mgr_.getRcvdPacketsNum(xchg_type) / duration;
    std::ostringstream s;
    s << "***Rate statistics***" << std::endl;
    s << "Rate: " << rate << " " << exchange_name << "/second";
    if (options_.getRate() > 0) {
        s << ", expected rate: " << options_.getRate() << std::endl;
    }

    std::cout << s.str() << std::endl;

    std::cout <<"***Malformed Packets***" << std::endl
              << "Malformed packets: " << ExchangeStats::malformed_pkts_
	      << std::endl;
}

void
TestControl::printIntermediateStats() {
    int delay = options_.getReportDelay();
    ptime now = microsec_clock::universal_time();
    time_period time_since_report(last_report_, now);
    if (time_since_report.length().total_seconds() >= delay) {
        stats_mgr_.printIntermediateStats(options_.getCleanReport(),
                                          options_.getCleanReportSeparator());
        last_report_ = now;
    }
}

void
TestControl::printStats() const {
    printRate();
    stats_mgr_.printStats();
    if (options_.testDiags('i')) {
        stats_mgr_.printCustomCounters();
    }
}

std::string
TestControl::vector2Hex(const std::vector<uint8_t>& vec,
                        const std::string& separator /* = "" */) {
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
TestControl::processReceivedPacket4(const Pkt4Ptr& pkt4) {
    if (pkt4->getType() == DHCPOFFER) {
        PktPtr pkt = stats_mgr_.passRcvdPacket(ExchangeType::DO, pkt4);
        address4Uniqueness(pkt4, ExchangeType::DO);
        Pkt4Ptr discover_pkt4(boost::dynamic_pointer_cast<Pkt4>(pkt));
        CommandOptions::ExchangeMode xchg_mode = options_.getExchangeMode();
        if ((xchg_mode == CommandOptions::DORA_SARR) && discover_pkt4) {
            if (template_buffers_.size() < 2) {
                sendRequest4(discover_pkt4, pkt4);
            } else {
                /// @todo add defines for packet type index that can be
                /// used to access template_buffers_.
                sendRequest4(template_buffers_[1], discover_pkt4, pkt4);
            }
        }
    } else if (pkt4->getType() == DHCPACK) {
        // If received message is DHCPACK, we have to check if this is
        // a response to 4-way exchange. We'll match this packet with
        // a DHCPREQUEST sent as part of the 4-way exchanges.
        if (stats_mgr_.passRcvdPacket(ExchangeType::RA, pkt4)) {
            address4Uniqueness(pkt4, ExchangeType::RA);
            // The DHCPACK belongs to DHCPREQUEST-DHCPACK exchange type.
            // So, we may need to keep this DHCPACK in the storage if renews.
            // Note that, DHCPACK messages hold the information about
            // leases assigned. We use this information to renew.
            if (stats_mgr_.hasExchangeStats(ExchangeType::RNA) ||
                stats_mgr_.hasExchangeStats(ExchangeType::RLA)) {
                // Renew or release messages are sent, because StatsMgr has the
                // specific exchange type specified. Let's append the DHCPACK
                // message to a storage.
                ack_storage_.append(pkt4);
            }
        // The DHCPACK message is not a server's response to the DHCPREQUEST
        // message sent within the 4-way exchange. It may be a response to a
        // renewal. In this case we first check if StatsMgr has exchange type
        // for renew specified, and if it has, if there is a corresponding
        // renew message for the received DHCPACK.
        } else if (stats_mgr_.hasExchangeStats(ExchangeType::RNA)) {
            stats_mgr_.passRcvdPacket(ExchangeType::RNA, pkt4);
        }
    }
}

void
TestControl::address6Uniqueness(const Pkt6Ptr& pkt6, ExchangeType xchg_type) {
    // check if received address is unique
    if (options_.getAddrUnique()) {
        std::set<std::string> current;
        // addresses were already checked in validateIA
        // we can safely assume that those are correct
        for (OptionCollection::iterator opt = pkt6->options_.begin();
             opt != pkt6->options_.end(); ++opt) {
            switch (opt->second->getType()) {
            case D6O_IA_PD: {
                // add address and check if it has not been already assigned
                // addresses should be unique cross options of the packet
                auto ret = current.emplace(boost::dynamic_pointer_cast<
                    Option6IAPrefix>(opt->second->getOption(D6O_IAPREFIX))->getAddress().toText());
                if (!ret.second) {
                    stats_mgr_.updateNonUniqueAddrNum(xchg_type);
                }
                break;
	    }
	    case D6O_IA_NA: {
                // add address and check if it has not been already assigned
                // addresses should be unique cross options of the packet
                auto ret = current.emplace(boost::dynamic_pointer_cast<
                    Option6IAAddr>(opt->second->getOption(D6O_IAADDR))->getAddress().toText());
                if (!ret.second) {
                    stats_mgr_.updateNonUniqueAddrNum(xchg_type);
                }
                break;
            }
            default:
                break;
            }
        }
        // addresses should be unique cross packets
        addUniqeAddr(current, xchg_type);
    }
}

void
TestControl::address4Uniqueness(const Pkt4Ptr& pkt4, ExchangeType xchg_type) {
    // check if received address is unique
    if (options_.getAddrUnique()) {
        // addresses were already checked in validateIA
        // we can safely assume that those are correct
        std::set<std::string> current;
        current.insert(pkt4->getYiaddr().toText());
        // addresses should be unique cross packets
        addUniqeAddr(current, xchg_type);
    }
}

bool
TestControl::validateIA(const Pkt6Ptr& pkt6) {
    // check if iaaddr exists - if it does, we can continue sending request
    // if not we will update statistics about rejected leases
    // @todo it's checking just one iaaddress option for now it's ok
    // but when perfdhcp will be extended to create message with multiple IA
    // this will have to be iterate on:
    // OptionCollection ias = pkt6->getOptions(D6O_IA_NA);
    Option6IAPrefixPtr iapref;
    Option6IAAddrPtr iaaddr;
    if (pkt6->getOption(D6O_IA_PD)) {
        iapref = boost::dynamic_pointer_cast<
                 Option6IAPrefix>(pkt6->getOption(D6O_IA_PD)->getOption(D6O_IAPREFIX));
    }
    if (pkt6->getOption(D6O_IA_NA)) {
        iaaddr = boost::dynamic_pointer_cast<
                 Option6IAAddr>(pkt6->getOption(D6O_IA_NA)->getOption(D6O_IAADDR));
    }

    bool address_and_prefix = options_.getLeaseType().includes(
                              CommandOptions::LeaseType::ADDRESS_AND_PREFIX);
    bool prefix_only = options_.getLeaseType().includes(
                       CommandOptions::LeaseType::PREFIX);
    bool address_only = options_.getLeaseType().includes(
                        CommandOptions::LeaseType::ADDRESS);
    if ((address_and_prefix && iapref && iaaddr) ||
        (prefix_only && iapref && !address_and_prefix) ||
        (address_only && iaaddr && !address_and_prefix)) {
        return true;
    } else {
        return false;
    }
}

void
TestControl::processReceivedPacket6(const Pkt6Ptr& pkt6) {
    uint8_t packet_type = pkt6->getType();
    if (packet_type == DHCPV6_ADVERTISE) {
        PktPtr pkt = stats_mgr_.passRcvdPacket(ExchangeType::SA, pkt6);
        Pkt6Ptr solicit_pkt6(boost::dynamic_pointer_cast<Pkt6>(pkt));
        CommandOptions::ExchangeMode xchg_mode = options_.getExchangeMode();
        if ((xchg_mode == CommandOptions::DORA_SARR) && solicit_pkt6) {
            if (validateIA(pkt6)) {
               // if address is correct - check uniqueness
               address6Uniqueness(pkt6, ExchangeType::SA);
               if (template_buffers_.size() < 2) {
                    sendRequest6(pkt6);
               } else {
                    /// @todo add defines for packet type index that can be
                    /// used to access template_buffers_.
                    sendRequest6(template_buffers_[1], pkt6);
               }
            } else {
                stats_mgr_.updateRejLeases(ExchangeType::SA);
            }
        }
    } else if (packet_type == DHCPV6_REPLY) {
        // If the received message is Reply, we have to find out which exchange
        // type the Reply message belongs to. It is doable by matching the Reply
        // transaction id with the transaction id of the sent Request, Renew
        // or Release. First we start with the Request.
        if (stats_mgr_.passRcvdPacket(ExchangeType::RR, pkt6)) {
            // The Reply belongs to Request-Reply exchange type. So, we may need
            // to keep this Reply in the storage if Renews or/and Releases are
            // being sent. Note that, Reply messages hold the information about
            // leases assigned. We use this information to construct Renew and
            // Release messages.
            if (validateIA(pkt6)) {
                // if address is correct - check uniqueness
                address6Uniqueness(pkt6, ExchangeType::RR);
                // check if there is correct IA to continue with Renew/Release
                if (stats_mgr_.hasExchangeStats(ExchangeType::RN) ||
                    stats_mgr_.hasExchangeStats(ExchangeType::RL)) {
                    // Renew or Release messages are sent, because StatsMgr has the
                    // specific exchange type specified. Let's append the Reply
                    // message to a storage.
                    reply_storage_.append(pkt6);
                }
            } else {
                stats_mgr_.updateRejLeases(ExchangeType::RR);
            }
        // The Reply message is not a server's response to the Request message
        // sent within the 4-way exchange. It may be a response to the Renew
        // or Release message. In the if clause we first check if StatsMgr
        // has exchange type for Renew specified, and if it has, if there is
        // a corresponding Renew message for the received Reply. If not,
        // we check that StatsMgr has exchange type for Release specified,
        // as possibly the Reply has been sent in response to Release.
        } else if (!(stats_mgr_.hasExchangeStats(ExchangeType::RN) &&
                     stats_mgr_.passRcvdPacket(ExchangeType::RN, pkt6)) &&
                   stats_mgr_.hasExchangeStats(ExchangeType::RL)) {
            // At this point, it is only possible that the Reply has been sent
            // in response to a Release. Try to match the Reply with Release.
            stats_mgr_.passRcvdPacket(ExchangeType::RL, pkt6);
        }
    }
}

unsigned int
TestControl::consumeReceivedPackets() {
    unsigned int pkt_count = 0;
    PktPtr pkt;
    while ((pkt = receiver_.getPkt())) {
        pkt_count += 1;
        if (options_.getIpVersion() == 4) {
            Pkt4Ptr pkt4 = boost::dynamic_pointer_cast<Pkt4>(pkt);
            processReceivedPacket4(pkt4);
        } else {
            Pkt6Ptr pkt6 = boost::dynamic_pointer_cast<Pkt6>(pkt);
            processReceivedPacket6(pkt6);
        }
    }
    return pkt_count;
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
        // D6O_ELAPSED_TIME
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
    switch(options_.getIpVersion()) {
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
    transid_gen_.reset();
    last_report_ = microsec_clock::universal_time();
    // Actual generators will have to be set later on because we need to
    // get command line parameters first.
    setTransidGenerator(NumberGeneratorPtr());
    setMacAddrGenerator(NumberGeneratorPtr());
    first_packet_serverid_.clear();
    interrupted_ = false;
}

TestControl::TestControl(CommandOptions& options, BasePerfSocket &socket) :
    exit_time_(not_a_date_time),
    number_generator_(0, options.getMacsFromFile().size()),
    socket_(socket),
    receiver_(socket, options.isSingleThreaded(), options.getIpVersion()),
    stats_mgr_(options),
    options_(options)
{
    // Reset singleton state before test starts.
    reset();

    // Ip version is not set ONLY in case the command options
    // were not parsed. This surely means that parse() function
    // was not called prior to starting the test. This is fatal
    // error.
    if (options_.getIpVersion() == 0) {
        isc_throw(InvalidOperation,
                  "command options must be parsed before running a test");
    } else if (options_.getIpVersion() == 4) {
        // Turn off packet queueing.
        IfaceMgr::instance().configureDHCPPacketQueue(AF_INET, data::ElementPtr());
        setTransidGenerator(NumberGeneratorPtr(new SequentialGenerator()));
    } else {
        // Turn off packet queueing.
        IfaceMgr::instance().configureDHCPPacketQueue(AF_INET6, data::ElementPtr());
        setTransidGenerator(NumberGeneratorPtr(new SequentialGenerator(0x00FFFFFF)));
    }

    uint32_t clients_num = options_.getClientsNum() == 0 ?
        1 : options_.getClientsNum();
    setMacAddrGenerator(NumberGeneratorPtr(new SequentialGenerator(clients_num)));

    // Diagnostics are command line options mainly.
    printDiagnostics();
    // Option factories have to be registered.
    registerOptionFactories();
    // Initialize packet templates.
    initPacketTemplates();
    // Initialize randomization seed.
    if (options_.isSeeded()) {
        srandom(options_.getSeed());
    } else {
        // Seed with current time.
        time_period duration(from_iso_string("20111231T235959"),
                             microsec_clock::universal_time());
        srandom(duration.length().total_seconds()
                + duration.length().fractional_seconds());
    }
    // If user interrupts the program we will exit gracefully.
    signal(SIGINT, TestControl::handleInterrupt);
}

void
TestControl::runWrapped(bool do_stop /*= false */) const {
    if (!options_.getWrapped().empty()) {
        pid_t pid = 0;
        signal(SIGCHLD, handleChild);
        pid = fork();
        if (pid < 0) {
            isc_throw(Unexpected, "unable to fork");
        } else if (pid == 0) {
            execlp(options_.getWrapped().c_str(), do_stop ? "stop" : "start", (void*)0);
        }
    }
}

void
TestControl::saveFirstPacket(const Pkt4Ptr& pkt) {
    if (options_.testDiags('T')) {
        if (template_packets_v4_.find(pkt->getType()) == template_packets_v4_.end()) {
            template_packets_v4_[pkt->getType()] = pkt;
        }
    }
}

void
TestControl::saveFirstPacket(const Pkt6Ptr& pkt) {
    if (options_.testDiags('T')) {
        if (template_packets_v6_.find(pkt->getType()) == template_packets_v6_.end()) {
            template_packets_v6_[pkt->getType()] = pkt;
        }
    }
}

void
TestControl::sendDiscover4(const bool preload /*= false*/) {
    // Generate the MAC address to be passed in the packet.
    uint8_t randomized = 0;
    std::vector<uint8_t> mac_address = generateMacAddress(randomized);
    // Generate transaction id to be set for the new exchange.
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
    setDefaults4(pkt4);

    // Set hardware address
    pkt4->setHWAddr(HTYPE_ETHER, mac_address.size(), mac_address);

    // Set client identifier
    pkt4->addOption(generateClientId(pkt4->getHWAddr()));

    // Check if we need to simulate HA failures by pretending no responses were received.
    // The DHCP protocol signals that by increasing secs field (seconds since the configuration attempt started).
    if (options_.getIncreaseElapsedTime() &&
        stats_mgr_.getTestPeriod().length().total_seconds() >= options_.getWaitForElapsedTime() &&
        stats_mgr_.getTestPeriod().length().total_seconds() < options_.getWaitForElapsedTime() +
                                     options_.getIncreaseElapsedTime()) {

        // Keep increasing elapsed time. The value should start increasing steadily.
        uint32_t val = stats_mgr_.getTestPeriod().length().total_seconds() - options_.getWaitForElapsedTime() + 1;
        if (val > 65535) {
            val = 65535;
        }
        pkt4->setSecs(static_cast<uint16_t>(val));
    }

    // Add any extra options that user may have specified.
    addExtraOpts(pkt4);

    pkt4->pack();
    socket_.send(pkt4);
    if (!preload) {
        stats_mgr_.passSentPacket(ExchangeType::DO, pkt4);
    }

    saveFirstPacket(pkt4);
}

void
TestControl::sendDiscover4(const std::vector<uint8_t>& template_buf,
                           const bool preload /* = false */) {
    // Get the first argument if multiple the same arguments specified
    // in the command line. First one refers to DISCOVER packets.
    const uint8_t arg_idx = 0;
    // Generate the MAC address to be passed in the packet.
    uint8_t randomized = 0;
    std::vector<uint8_t> mac_address = generateMacAddress(randomized);
    // Generate transaction id to be set for the new exchange.
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
    setDefaults4(boost::static_pointer_cast<Pkt4>(pkt4));
    // Pack the input packet buffer to output buffer so as it can
    // be sent to server.
    pkt4->rawPack();
    socket_.send(boost::static_pointer_cast<Pkt4>(pkt4));
    if (!preload) {
        // Update packet stats.
        stats_mgr_.passSentPacket(ExchangeType::DO,
                                    boost::static_pointer_cast<Pkt4>(pkt4));
    }
    saveFirstPacket(pkt4);
}

bool
TestControl::sendMessageFromAck(const uint16_t msg_type) {
    // We only permit Request or Release messages to be sent using this
    // function.
    if (msg_type != DHCPREQUEST && msg_type != DHCPRELEASE) {
        isc_throw(isc::BadValue,
                  "invalid message type "
                      << msg_type
                      << " to be sent, expected DHCPREQUEST or DHCPRELEASE");
    }

    // Get one of the recorded DHCPACK messages.
    Pkt4Ptr ack = ack_storage_.getRandom();
    if (!ack) {
        return (false);
    }

    // Create message of the specified type.
    Pkt4Ptr msg = createMessageFromAck(msg_type, ack);
    setDefaults4(msg);

    // Override relay address
    msg->setGiaddr(ack->getGiaddr());

    // Add any extra options that user may have specified.
    addExtraOpts(msg);

    // Pack it.
    msg->pack();

    // And send it.
    socket_.send(msg);
    address4Uniqueness(msg, ExchangeType::RLA);
    stats_mgr_.passSentPacket((msg_type == DHCPREQUEST ? ExchangeType::RNA :
                                                         ExchangeType::RLA),
                              msg);
    return (true);
}


bool
TestControl::sendMessageFromReply(const uint16_t msg_type) {
    // We only permit Release or Renew messages to be sent using this function.
    if (msg_type != DHCPV6_RENEW && msg_type != DHCPV6_RELEASE) {
        isc_throw(isc::BadValue, "invalid message type " << msg_type
                  << " to be sent, expected DHCPV6_RENEW or DHCPV6_RELEASE");
    }

    // Get one of the recorded DHCPV6_OFFER messages.
    Pkt6Ptr reply = reply_storage_.getRandom();
    if (!reply) {
        return (false);
    }
    // Prepare the message of the specified type.
    Pkt6Ptr msg = createMessageFromReply(msg_type, reply);
    setDefaults6(msg);

    // Add any extra options that user may have specified.
    addExtraOpts(msg);

    // Pack it.
    msg->pack();

    // And send it.
    socket_.send(msg);
    address6Uniqueness(msg, ExchangeType::RL);
    stats_mgr_.passSentPacket((msg_type == DHCPV6_RENEW ? ExchangeType::RN
                                : ExchangeType::RL), msg);
    return (true);
}

void
TestControl::sendRequest4(const dhcp::Pkt4Ptr& discover_pkt4,
                          const dhcp::Pkt4Ptr& offer_pkt4) {
    // Use the same transaction id as the one used in the discovery packet.
    const uint32_t transid = discover_pkt4->getTransid();
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, transid));

    // Use first flags indicates that we want to use the server
    // id captured in first packet.
    if (options_.isUseFirst() &&
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
        if (stats_mgr_.getRcvdPacketsNum(ExchangeType::DO) == 1) {
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
    opt_requested_address->setUint32(yiaddr.toUint32());
    pkt4->addOption(opt_requested_address);
    OptionPtr opt_parameter_list =
        Option::factory(Option::V4, DHO_DHCP_PARAMETER_REQUEST_LIST);
    pkt4->addOption(opt_parameter_list);
    // Set client's and server's ports as well as server's address
    setDefaults4(pkt4);
    // Override relay address
    pkt4->setGiaddr(offer_pkt4->getGiaddr());
    // Add any extra options that user may have specified.
    addExtraOpts(pkt4);

    // Set hardware address
    pkt4->setHWAddr(offer_pkt4->getHWAddr());
    // Set client id.
    pkt4->addOption(generateClientId(pkt4->getHWAddr()));
    // Set elapsed time.
    uint32_t elapsed_time = getElapsedTime<Pkt4Ptr>(discover_pkt4, offer_pkt4);
    pkt4->setSecs(static_cast<uint16_t>(elapsed_time / 1000));
    // Prepare on wire data to send.
    pkt4->pack();
    socket_.send(pkt4);
    stats_mgr_.passSentPacket(ExchangeType::RA, pkt4);
    saveFirstPacket(pkt4);
}

void
TestControl::sendRequest4(const std::vector<uint8_t>& template_buf,
                          const dhcp::Pkt4Ptr& discover_pkt4,
                          const dhcp::Pkt4Ptr& offer_pkt4) {
    // Get the second argument if multiple the same arguments specified
    // in the command line. Second one refers to REQUEST packets.
    const uint8_t arg_idx = 1;
    // Use the same transaction id as the one used in the discovery packet.
    const uint32_t transid = discover_pkt4->getTransid();
    // Get transaction id offset.
    size_t transid_offset = getTransactionIdOffset(arg_idx);
    // Get the offset of MAC's last octet.
    // We need to go back by HW_ETHER_LEN (MAC address length)
    // because this offset points to last octet of MAC address.
    size_t rand_offset = getRandomOffset(arg_idx) - HW_ETHER_LEN + 1;
    // Create temporary buffer from the template.
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
    if (options_.isUseFirst() &&
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
        if (stats_mgr_.getRcvdPacketsNum(ExchangeType::DO) == 1) {
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
    // The IOAddress is convertible to uint32_t and returns exactly what we need.
    opt_requested_ip->setUint32(yiaddr.toUint32());
    pkt4->addOption(opt_requested_ip);

    setDefaults4(boost::static_pointer_cast<Pkt4>(pkt4));

    // Add any extra options that user may have specified.
    addExtraOpts(pkt4);

    // Prepare on-wire data.
    pkt4->rawPack();
    socket_.send(boost::static_pointer_cast<Pkt4>(pkt4));
    // Update packet stats.
    stats_mgr_.passSentPacket(ExchangeType::RA,
                               boost::static_pointer_cast<Pkt4>(pkt4));
    saveFirstPacket(pkt4);
}

void
TestControl::sendRequest6(const Pkt6Ptr& advertise_pkt6) {
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
    if (options_.isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        pkt6->addOption(Option::factory(Option::V6, D6O_SERVERID,
                                        first_packet_serverid_));
    } else {
        OptionPtr opt_serverid = advertise_pkt6->getOption(D6O_SERVERID);
        if (!opt_serverid) {
            isc_throw(Unexpected, "server id not found in received packet");
        }
        if (stats_mgr_.getRcvdPacketsNum(ExchangeType::SA) == 1) {
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
    setDefaults6(pkt6);

    // Add any extra options that user may have specified.
    addExtraOpts(pkt6);

    // Prepare on-wire data.
    pkt6->pack();
    socket_.send(pkt6);
    stats_mgr_.passSentPacket(ExchangeType::RR, pkt6);
    saveFirstPacket(pkt6);
}

void
TestControl::sendRequest6(const std::vector<uint8_t>& template_buf,
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
    if (options_.isUseFirst() &&
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
        if (stats_mgr_.getRcvdPacketsNum(ExchangeType::SA) == 1) {
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
    setDefaults6(pkt6);

    // Add any extra options that user may have specified.
    addExtraOpts(pkt6);

    // Prepare on wire data.
    pkt6->rawPack();
    // Send packet.
    socket_.send(pkt6);
    // Update packet stats.
    stats_mgr_.passSentPacket(ExchangeType::RR, pkt6);

    // When 'T' diagnostics flag is specified it means that user requested
    // printing packet contents. It will be just one (first) packet which
    // contents will be printed. Here we check if this packet has been already
    // collected. If it hasn't we save this packet so as we can print its
    // contents when test is finished.
    if (options_.testDiags('T') &&
        (template_packets_v6_.find(DHCPV6_REQUEST) == template_packets_v6_.end())) {
        template_packets_v6_[DHCPV6_REQUEST] = pkt6;
    }
}

void
TestControl::sendSolicit6(const bool preload /*= false*/) {
    // Generate DUID to be passed to the packet
    uint8_t randomized = 0;
    std::vector<uint8_t> duid = generateDuid(randomized);
    // Generate transaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
    if (!pkt6) {
        isc_throw(Unexpected, "failed to create SOLICIT packet");
    }

    // Check if we need to simulate HA failures by pretending no responses were received.
    // The DHCPv6 protocol signals that by increasing the elapsed option field. Note it is in 1/100 of a second.
    if (options_.getIncreaseElapsedTime() &&
        stats_mgr_.getTestPeriod().length().total_seconds() >= options_.getWaitForElapsedTime() &&
        stats_mgr_.getTestPeriod().length().total_seconds() < options_.getWaitForElapsedTime() +
                                     options_.getIncreaseElapsedTime()) {


        // Keep increasing elapsed time. The value should start increasing steadily.
        uint32_t val = (stats_mgr_.getTestPeriod().length().total_seconds() - options_.getWaitForElapsedTime() + 1)*100;
        if (val > 65535) {
            val = 65535;
        }
        OptionPtr elapsed(new OptionInt<uint16_t>(Option::V6, D6O_ELAPSED_TIME, val));
        pkt6->addOption(elapsed);
    } else {
        pkt6->addOption(Option::factory(Option::V6, D6O_ELAPSED_TIME));
    }

    if (options_.isRapidCommit()) {
        pkt6->addOption(Option::factory(Option::V6, D6O_RAPID_COMMIT));
    }
    pkt6->addOption(Option::factory(Option::V6, D6O_CLIENTID, duid));
    pkt6->addOption(Option::factory(Option::V6, D6O_ORO));


    // Depending on the lease-type option specified, we should request
    // IPv6 address (with IA_NA) or IPv6 prefix (IA_PD) or both.

    // IA_NA
    if (options_.getLeaseType().includes(CommandOptions::LeaseType::ADDRESS)) {
        pkt6->addOption(Option::factory(Option::V6, D6O_IA_NA));
    }
    // IA_PD
    if (options_.getLeaseType().includes(CommandOptions::LeaseType::PREFIX)) {
        pkt6->addOption(Option::factory(Option::V6, D6O_IA_PD));
    }

    setDefaults6(pkt6);

    // Add any extra options that user may have specified.
    addExtraOpts(pkt6);

    pkt6->pack();
    socket_.send(pkt6);
    if (!preload) {
        stats_mgr_.passSentPacket(ExchangeType::SA, pkt6);
    }

    saveFirstPacket(pkt6);
}

void
TestControl::sendSolicit6(const std::vector<uint8_t>& template_buf,
                          const bool preload /*= false*/) {
    const int arg_idx = 0;
    // Get transaction id offset.
    size_t transid_offset = getTransactionIdOffset(arg_idx);
    // Generate transaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    // Create packet.
    PerfPkt6Ptr pkt6(new PerfPkt6(&template_buf[0], template_buf.size(),
                                  transid_offset, transid));
    if (!pkt6) {
        isc_throw(Unexpected, "failed to create SOLICIT packet");
    }
    size_t rand_offset = getRandomOffset(arg_idx);
    // randomized will pick number of bytes randomized so we can
    // just use part of the generated duid and substitute a few bytes
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
    setDefaults6(pkt6);

    // Add any extra options that user may have specified.
    addExtraOpts(pkt6);

    // Send solicit packet.
    socket_.send(pkt6);
    if (!preload) {
        // Update packet stats.
        stats_mgr_.passSentPacket(ExchangeType::SA, pkt6);
    }
    saveFirstPacket(pkt6);
}


void
TestControl::setDefaults4(const Pkt4Ptr& pkt) {
    // Interface name.
    IfacePtr iface = socket_.getIface();
    if (iface == NULL) {
        isc_throw(BadValue, "unable to find interface with given index");
    }
    pkt->setIface(iface->getName());
    // Interface index.
    pkt->setIndex(socket_.ifindex_);
    // Local client's port (68)
    pkt->setLocalPort(DHCP4_CLIENT_PORT);
    // Server's port (67)
    if (options_.getRemotePort()) {
        pkt->setRemotePort(options_.getRemotePort());
    } else {
        pkt->setRemotePort(DHCP4_SERVER_PORT);
    }
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options_.getServerName()));
    // Set local address.
    pkt->setLocalAddr(IOAddress(socket_.addr_));
    // Set relay (GIADDR) address to local address if multiple
    // subnet mode is not enabled
    if (!options_.checkMultiSubnet()) {
        pkt->setGiaddr(IOAddress(socket_.addr_));
    } else {
        pkt->setGiaddr(IOAddress(options_.getRandRelayAddr()));
    }
    // Pretend that we have one relay (which is us).
    pkt->setHops(1);
}

void
TestControl::setDefaults6(const Pkt6Ptr& pkt) {
    // Interface name.
    IfacePtr iface = socket_.getIface();
    if (iface == NULL) {
        isc_throw(BadValue, "unable to find interface with given index");
    }
    pkt->setIface(iface->getName());
    // Interface index.
    pkt->setIndex(socket_.ifindex_);
    // Local client's port (547)
    pkt->setLocalPort(DHCP6_CLIENT_PORT);
    // Server's port (548)
    if (options_.getRemotePort()) {
        pkt->setRemotePort(options_.getRemotePort());
    } else {
        pkt->setRemotePort(DHCP6_SERVER_PORT);
    }
    // Set local address.
    pkt->setLocalAddr(socket_.addr_);
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options_.getServerName()));

    // only act as a relay agent when told so.
    /// @todo: support more level of encapsulation, at the moment we only support
    /// one, via -A1 option.
    if (options_.isUseRelayedV6()) {
      Pkt6::RelayInfo relay_info;
      relay_info.msg_type_ = DHCPV6_RELAY_FORW;
      relay_info.hop_count_ = 0;
      if (options_.checkMultiSubnet()) {
          relay_info.linkaddr_ = IOAddress(options_.getRandRelayAddr());
      } else {
          relay_info.linkaddr_ = IOAddress(socket_.addr_);
      }
      relay_info.peeraddr_ = IOAddress(socket_.addr_);
      pkt->addRelayInfo(relay_info);
    }
}

namespace {

static OptionBuffer const concatenateBuffers(OptionBuffer const& a,
                                             OptionBuffer const& b) {
    OptionBuffer result;
    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

static void mergeOptionIntoPacket(Pkt4Ptr const& packet,
                                  OptionPtr const& extra_option) {
    uint16_t const code(extra_option->getType());
    // If option already exists...
    OptionPtr const& option(packet->getOption(code));
    if (option) {
        switch (code) {
        // List here all the options for which we want to concatenate buffers.
        case DHO_DHCP_PARAMETER_REQUEST_LIST:
            packet->delOption(code);
            packet->addOption(boost::make_shared<Option>(
                Option::V4, code,
                concatenateBuffers(option->getData(),
                                   extra_option->getData())));
            return;
        default:
            // For all others, add option as usual, it will result in "Option
            // already present in this message" error.
            break;
        }
    }
    packet->addOption(extra_option);
}

}  // namespace

void
TestControl::addExtraOpts(const Pkt4Ptr& pkt) {
    // Add all extra options that the user may have specified.
    const dhcp::OptionCollection& extra_opts = options_.getExtraOpts();
    for (auto entry : extra_opts) {
        mergeOptionIntoPacket(pkt, entry.second);
    }
}

void
TestControl::addExtraOpts(const Pkt6Ptr& pkt) {
    // Add all extra options that the user may have specified.
    const dhcp::OptionCollection& extra_opts = options_.getExtraOpts();
    for (auto entry : extra_opts) {
        pkt->addOption(entry.second);
    }
}

}  // namespace perfdhcp
}  // namespace isc
