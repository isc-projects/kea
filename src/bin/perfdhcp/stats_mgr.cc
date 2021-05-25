// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/pkt4.h>
#include <perfdhcp/stats_mgr.h>
#include <perfdhcp/test_control.h>

using isc::dhcp::DHO_DHCP_CLIENT_IDENTIFIER;
using isc::dhcp::DUID;
using isc::dhcp::Option6IAAddr;
using isc::dhcp::Option6IAAddrPtr;
using isc::dhcp::Option6IAPrefix;
using isc::dhcp::Option6IAPrefixPtr;
using isc::dhcp::OptionPtr;
using isc::dhcp::Pkt4;
using isc::dhcp::Pkt4Ptr;
using isc::dhcp::PktPtr;

namespace isc {
namespace perfdhcp {

int dhcpVersion(ExchangeType const exchange_type) {
    switch (exchange_type) {
    case ExchangeType::DO:
    case ExchangeType::RA:
    case ExchangeType::RNA:
    case ExchangeType::RLA:
        return 4;
    case ExchangeType::SA:
    case ExchangeType::RR:
    case ExchangeType::RN:
    case ExchangeType::RL:
        return 6;
    default:
        isc_throw(BadValue,
                  "unrecognized exchange type '" << exchange_type << "'");
    }
}

std::ostream& operator<<(std::ostream& os, ExchangeType xchg_type)
{
    switch(xchg_type) {
    case ExchangeType::DO:
        return(os << "DISCOVER-OFFER");
    case ExchangeType::RA:
        return(os << "REQUEST-ACK");
    case ExchangeType::RNA:
        return(os << "REQUEST-ACK (renewal)");
    case ExchangeType::RLA:
        return(os << "RELEASE");
    case ExchangeType::SA:
        return(os << "SOLICIT-ADVERTISE");
    case ExchangeType::RR:
        return(os << "REQUEST-REPLY");
    case ExchangeType::RN:
        return(os << "RENEW-REPLY");
    case ExchangeType::RL:
        return(os << "RELEASE-REPLY");
    default:
        return(os << "Unknown exchange type");
    }
}


ExchangeStats::ExchangeStats(const ExchangeType xchg_type,
                             const double drop_time,
                             const bool archive_enabled,
                             const boost::posix_time::ptime boot_time)
    : xchg_type_(xchg_type),
      sent_packets_(),
      rcvd_packets_(),
      archived_packets_(),
      archive_enabled_(archive_enabled),
      drop_time_(drop_time),
      min_delay_(std::numeric_limits<double>::max()),
      max_delay_(0.),
      sum_delay_(0.),
      sum_delay_squared_(0.),
      orphans_(0),
      collected_(0),
      unordered_lookup_size_sum_(0),
      unordered_lookups_(0),
      ordered_lookups_(0),
      sent_packets_num_(0),
      rcvd_packets_num_(0),
      non_unique_addr_num_(0),
      rejected_leases_num_(0),
      boot_time_(boot_time)
{
    next_sent_ = sent_packets_.begin();
}

void
ExchangeStats::updateDelays(const PktPtr& sent_packet,
                            const PktPtr& rcvd_packet) {
    if (!sent_packet) {
        isc_throw(BadValue, "Sent packet is null");
    }
    if (!rcvd_packet) {
        isc_throw(BadValue, "Received packet is null");
    }

    boost::posix_time::ptime sent_time = sent_packet->getTimestamp();
    boost::posix_time::ptime rcvd_time = rcvd_packet->getTimestamp();

    if (sent_time.is_not_a_date_time() ||
        rcvd_time.is_not_a_date_time()) {
        isc_throw(Unexpected,
                  "Timestamp must be set for sent and "
                  "received packet to measure RTT,"
                  << " sent: " << sent_time
                  << " recv: " << rcvd_time);
    }
    boost::posix_time::time_period period(sent_time, rcvd_time);
    // We don't bother calculating deltas in nanoseconds. It is much
    // more convenient to use seconds instead because we are going to
    // sum them up.
    double delta =
        static_cast<double>(period.length().total_nanoseconds()) / 1e9;

    if (delta < 0) {
        isc_throw(Unexpected, "Sent packet's timestamp must not be "
                  "greater than received packet's timestamp in "
                  << xchg_type_ << ".\nTime difference: "
                  << delta << ", sent: " << sent_time << ", rcvd: "
                  << rcvd_time << ".\nTrans ID: " << sent_packet->getTransid()
                  << ".");
    }

    // Record the minimum delay between sent and received packets.
    if (delta < min_delay_) {
        min_delay_ = delta;
    }
    // Record the maximum delay between sent and received packets.
    if (delta > max_delay_) {
        max_delay_ = delta;
    }
    // Update delay sum and square sum. That will be used to calculate
    // mean delays.
    sum_delay_ += delta;
    sum_delay_squared_ += delta * delta;
}

PktPtr
ExchangeStats::matchPackets(const PktPtr& rcvd_packet) {
    using namespace boost::posix_time;

    if (!rcvd_packet) {
        isc_throw(BadValue, "Received packet is null");
    }

    if (sent_packets_.size() == 0) {
        // List of sent packets is empty so there is no sense
        // to continue looking fo the packet. It also means
        // that the received packet we got has no corresponding
        // sent packet so orphans counter has to be updated.
        ++orphans_;
        return(PktPtr());
    } else if (next_sent_ == sent_packets_.end()) {
        // Even if there are still many unmatched packets on the
        // list we might hit the end of it because of unordered
        // lookups. The next logical step is to reset iterator.
        next_sent_ = sent_packets_.begin();
    }

    // With this variable we will be signalling success or failure
    // to find the packet.
    bool packet_found = false;
    // Most likely responses are sent from the server in the same
    // order as client's requests to the server. We are caching
    // next sent packet and first try to match it with the next
    // incoming packet. We are successful if there is no
    // packet drop or out of order packets sent. This is actually
    // the fastest way to look for packets.
    if ((*next_sent_)->getTransid() == rcvd_packet->getTransid()) {
        ++ordered_lookups_;
        packet_found = true;
    } else {
        // If we are here, it means that we were unable to match the
        // next incoming packet with next sent packet so we need to
        // take a little more expensive approach to look packets using
        // alternative index (transaction id & 1023).
        PktListTransidHashIndex& idx = sent_packets_.template get<1>();
        // Packets are grouped using transaction id masked with value
        // of 1023. For instance, packets with transaction id equal to
        // 1, 1024 ... will belong to the same group (a.k.a. bucket).
        // When using alternative index we don't find the packet but
        // bucket of packets and we need to iterate through the bucket
        // to find the one that has desired transaction id.
        std::pair<PktListTransidHashIterator,PktListTransidHashIterator> p =
            idx.equal_range(hashTransid(rcvd_packet));
        // We want to keep statistics of unordered lookups to make
        // sure that there is a right balance between number of
        // unordered lookups and ordered lookups. If number of unordered
        // lookups is high it may mean that many packets are lost or
        // sent out of order.
        ++unordered_lookups_;
        // We also want to keep the mean value of the bucket. The lower
        // bucket size the better. If bucket sizes appear to big we
        // might want to increase number of buckets.
        unordered_lookup_size_sum_ += std::distance(p.first, p.second);
        bool non_expired_found = false;
        // Removal can be done only after the loop
        PktListRemovalQueue to_remove;
        for (PktListTransidHashIterator it = p.first; it != p.second; ++it) {
            // If transaction id is matching, we found the original
            // packet sent to the server. Therefore, we reset the
            // 'next sent' pointer to point to this location. We
            // also indicate that the matching packet is found.
            // Even though the packet has been found, we continue
            // iterating over the bucket to remove all those packets
            // that are timed out.
            if (!packet_found && ((*it)->getTransid() == rcvd_packet->getTransid())) {
                packet_found = true;
                next_sent_ = sent_packets_.template project<0>(it);
            }

            if (!non_expired_found) {
                // Check if the packet should be removed due to timeout.
                // This includes the packet matching the received one.
                ptime now = microsec_clock::universal_time();
                ptime packet_time = (*it)->getTimestamp();
                time_period packet_period(packet_time, now);
                if (!packet_period.is_null()) {
                    double period_fractional =
                        packet_period.length().total_seconds() +
                        (static_cast<double>(packet_period.length().fractional_seconds())
                         / packet_period.length().ticks_per_second());
                    if (drop_time_ > 0 && (period_fractional > drop_time_)) {
                        // Push the iterator on the removal queue.
                        to_remove.push(it);

                    } else {
                        // We found first non-expired transaction. All other
                        // transactions within this bucket are considered
                        // non-expired because packets are held in the
                        // order of addition within the bucket.
                        non_expired_found = true;
                    }
                }
            }

            // If we found the packet and all expired transactions,
            // there is nothing more to do.
            if (non_expired_found && packet_found) {
                break;
            }
        }

        // Deal with the removal queue.
        while (!to_remove.empty()) {
            PktListTransidHashIterator it = to_remove.front();
            to_remove.pop();
            // If timed out packet is not the one matching server response,
            // we simply remove it and keep the pointer to the 'next sent'
            // packet as it was. If the timed out packet appears to be the
            // one that is matching the server response, we still want to
            // remove it, but we need to update the 'next sent' pointer to
            // point to a valid location.
            if (sent_packets_.template project<0>(it) != next_sent_) {
                eraseSent(sent_packets_.template project<0>(it));
            } else {
                next_sent_ = eraseSent(sent_packets_.template project<0>(it));
                // We removed the matching packet because of the timeout. It
                // means that there is no match anymore.
                packet_found = false;
            }
            ++collected_;
        }
    }

    if (!packet_found) {
        // If we are here, it means that both ordered lookup and
        // unordered lookup failed. Searched packet is not on the list.
        ++orphans_;
        return(PktPtr());
    }

    // Packet is matched so we count it. We don't count unmatched packets
    // as they are counted as orphans with a separate counter.
    ++rcvd_packets_num_;
    PktPtr sent_packet(*next_sent_);
    // If packet was found, we assume it will be never searched
    // again. We want to delete this packet from the list to
    // improve performance of future searches.
    next_sent_ = eraseSent(next_sent_);
    return(sent_packet);
}


void
ExchangeStats::printTimestamps() {
    // If archive mode is disabled there is no sense to proceed
    // because we don't have packets and their timestamps.
    if (!archive_enabled_) {
        isc_throw(isc::InvalidOperation,
                  "packets archive mode is disabled");
    }
    if (rcvd_packets_num_ == 0) {
        std::cout << "Unavailable! No packets received." << std::endl;
    }
    // We will be using boost::posix_time extensively here
    using namespace boost::posix_time;

    // Iterate through all received packets.
    for (PktListIterator it = rcvd_packets_.begin();
         it != rcvd_packets_.end();
         ++it) {
        PktPtr rcvd_packet = *it;
        PktListTransidHashIndex& idx =
            archived_packets_.template get<1>();
        std::pair<PktListTransidHashIterator,
                  PktListTransidHashIterator> p =
            idx.equal_range(hashTransid(rcvd_packet));
        for (PktListTransidHashIterator it_archived = p.first;
             it_archived != p.second;
             ++it_archived) {
            if ((*it_archived)->getTransid() ==
                rcvd_packet->getTransid()) {
                PktPtr sent_packet = *it_archived;
                // Get sent and received packet times.
                ptime sent_time = sent_packet->getTimestamp();
                ptime rcvd_time = rcvd_packet->getTimestamp();
                // All sent and received packets should have timestamps
                // set but if there is a bug somewhere and packet does
                // not have timestamp we want to catch this here.
                if (sent_time.is_not_a_date_time() ||
                    rcvd_time.is_not_a_date_time()) {
                    isc_throw(InvalidOperation,
                              "packet time is not set");
                }
                // Calculate durations of packets from beginning of epoch.
                time_period sent_period(boot_time_, sent_time);
                time_period rcvd_period(boot_time_, rcvd_time);
                // Print timestamps for sent and received packet.
                std::cout << "sent / received: "
                          << to_iso_string(sent_period.length())
                          << " / "
                          << to_iso_string(rcvd_period.length())
                          << std::endl;
                break;
            }
        }
    }
}

StatsMgr::StatsMgr(CommandOptions& options) :
    exchanges_(),
    boot_time_(boost::posix_time::microsec_clock::universal_time())
{
    // Check if packet archive mode is required. If user
    // requested diagnostics option -x l or -x t we have to enable
    // it so as StatsMgr preserves all packets.
    archive_enabled_ = options.testDiags('l') || options.testDiags('t');

    if (options.getIpVersion() == 4) {
        addExchangeStats(ExchangeType::DO, options.getDropTime()[0]);
        if (options.getExchangeMode() == CommandOptions::DORA_SARR) {
            addExchangeStats(ExchangeType::RA, options.getDropTime()[1]);
        }
        if (options.getRenewRate() != 0) {
            addExchangeStats(ExchangeType::RNA);
        }
        if (options.getReleaseRate() != 0) {
            addExchangeStats(ExchangeType::RLA);
        }
    } else if (options.getIpVersion() == 6) {
        addExchangeStats(ExchangeType::SA, options.getDropTime()[0]);
        if (options.getExchangeMode() == CommandOptions::DORA_SARR) {
            addExchangeStats(ExchangeType::RR, options.getDropTime()[1]);
        }
        if (options.getRenewRate() != 0) {
            addExchangeStats(ExchangeType::RN);
        }
        if (options.getReleaseRate() != 0) {
            addExchangeStats(ExchangeType::RL);
        }
    }
    if (options.testDiags('i')) {
        addCustomCounter("shortwait", "Short waits for packets");
    }
}

std::string
ExchangeStats::receivedLeases() const {
    // Get DHCP version.
    int const v(dhcpVersion(xchg_type_));

    std::stringstream result;
    // Iterate through all received packets.
    for (PktPtr const& packet : rcvd_packets_) {

        // Get client identifier.
        if (v == 4) {
            OptionPtr const& client_id_option(
                packet->getOption(DHO_DHCP_CLIENT_IDENTIFIER));
            if (client_id_option) {
                result << TestControl::vector2Hex(client_id_option->getData());
            }
        } else if (v == 6) {
            OptionPtr const& client_id_option(packet->getOption(D6O_CLIENTID));
            if (client_id_option) {
                result << DUID(client_id_option->getData()).toText();
            }
        } else {
            isc_throw(BadValue, "unrecognized DHCP version '" << v << "'");
        }
        result << ',';

        // Get address.
        if (v == 4) {
            Pkt4Ptr const& packet4(boost::dynamic_pointer_cast<Pkt4>(packet));
            if (packet4) {
                result << packet4->getYiaddr().toText();
            }
        } else if (v == 6) {
            OptionPtr const& option(packet->getOption(D6O_IA_NA));
            if (option) {
                Option6IAAddrPtr const& iaaddr(
                    boost::dynamic_pointer_cast<Option6IAAddr>(
                        option->getOption(D6O_IAADDR)));
                if (iaaddr) {
                    result << iaaddr->getAddress().toText();
                }
            }
        }
        result << ',';

        // Get prefix.
        OptionPtr const& option(packet->getOption(D6O_IA_PD));
        if (option) {
            Option6IAPrefixPtr const& iaprefix(
                boost::dynamic_pointer_cast<Option6IAPrefix>(
                    option->getOption(D6O_IAPREFIX)));
            if (iaprefix) {
                result << iaprefix->getAddress().toText();
            }
        }

        result << std::endl;
    }

    return result.str();
}

void
ExchangeStats::printLeases() const {
    std::cout << receivedLeases() << std::endl;
}

void StatsMgr::printLeases() const {
    for (auto const& exchange : exchanges_) {
        std::cout << "***Leases for " << exchange.first << "***" << std::endl;
        std::cout << "client_id,adrress,prefix" << std::endl;
        exchange.second->printLeases();
        std::cout << std::endl;
    }
}

int ExchangeStats::malformed_pkts_{0};

}  // namespace perfdhcp
}  // namespace isc
