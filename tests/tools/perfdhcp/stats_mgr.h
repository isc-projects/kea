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

#ifndef __STATS_MGR_H
#define __STATS_MGR_H

#include <map>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <exceptions/exceptions.h>

namespace isc {
namespace perfdhcp {

/// \brief Statistics Manager
///
/// This class template is a storage for various performance statistics
/// collected during performance tests execution with perfdhcp tool.
///
/// Statistics Manager holds lists of sent and received packets and
/// groups them into exchanges. For example: DHCPDISCOVER message and
/// corresponding DHCPOFFER messages belong to one exchange, DHCPREQUEST
/// and corresponding DHCPACK message belong to another exchange etc.
/// In order to update statistics for a particular exchange type, client
/// class passes sent and received packets. Internally, Statistics Manager
/// tries to match transaction id of received packet with sent packet
/// stored on the list of sent packets. When packets are matched the
/// round trip time can be calculated.
///
/// \tparam T class representing DHCPv4 or DHCPv6 packet.
template <class T>
class StatsMgr : public boost::noncopyable {
public:

    /// DHCP packet exchange types.
    enum ExchangeType {
        XCHG_DO,  ///< DHCPv4 DISCOVER-OFFER
        XCHG_RA,  ///< DHCPv4 REQUEST-ACK
        XCHG_SA,  ///< DHCPv6 SOLICIT-ADVERTISE
        XCHG_RR   ///< DHCPv6 REQUEST-REPLY
    };

    /// \brief Exchange Statistics.
    ///
    /// This class collects statistics for exchanges. Parent class
    /// may define number of different packet exchanges like:
    /// DHCPv4 DISCOVER-OFFER, DHCPv6 SOLICIT-ADVERTISE etc. Performance
    /// statistics will be collected for each of those separately in
    /// corresponding instance of ExchangeStats.
    class ExchangeStats {
    public:

        /// \brief List of packets (sent or received).
        ///
        /// List of packets based on multi index container allows efficient
        /// search of packets based on their sequence (order in which they
        /// were inserted) as well as based on packet transaction id.
        typedef boost::multi_index_container<
            boost::shared_ptr<T>,
            boost::multi_index::indexed_by<
                boost::multi_index::sequenced<>,
                boost::multi_index::ordered_unique<
                    boost::multi_index::const_mem_fun<
                        T, uint32_t, &T::getTransid>
                >
            >
        > PktList;

        /// Packet list iterator for sequencial access to elements.
        typedef typename PktList::iterator PktListIterator;
        /// Packet list index to search packets using transaction id.
        typedef typename PktList::template nth_index<1>::type
            PktListTransidIndex;
        /// Packet list iterator to access packets using transaction id.
        typedef typename PktListTransidIndex::iterator PktListTransidIterator;

        /// \brief Constructor
        ///
        /// \param xchg_type exchange type
        ExchangeStats(const ExchangeType xchg_type)
            : xchg_type_(xchg_type) {
            sent_packets_cache_ = sent_packets_.begin();
        }

        /// \brief Add new packet to list of sent packets.
        ///
        /// Method adds new packet to list of sent packets.
        ///
        /// \param packet packet object to be appended.
        void appendSent(const boost::shared_ptr<T> packet) {
            sent_packets_.template get<0>().push_back(packet);
        }

        /// \brief Find packet on the list of sent packets.
        ///
        /// Method finds packet with specified transaction id on the list
        /// of sent packets. It is used to match received packet with
        /// corresponding sent packet.
        /// Since packets from the server most often come in the same order
        /// as they were sent by client, this method will first check if
        /// next sent packet matches. If it doesn't, function will search
        /// the packet using indexing by transaction id. This reduces
        /// packet search time significantly.
        ///
        /// \param transid transaction id of the packet to search
        /// \throw isc::Unexpected if packet could not be found
        /// \return packet having specified transaction id
        boost::shared_ptr<T> findSent(const uint32_t transid) {
            if (sent_packets_.size() == 0) {
                isc_throw(Unexpected, "Sent packets list is empty.");
            } else if (sent_packets_cache_ == sent_packets_.end()) {
                sent_packets_cache_ = sent_packets_.begin();
            }

            bool packet_found = false;
            if ((*sent_packets_cache_)->getTransid() == transid) {
                packet_found = true;
            } else {
                PktListTransidIndex& idx = sent_packets_.template get<1>();
                PktListTransidIterator it =  idx.find(transid);
                if (it != idx.end()) {
                    packet_found = true;
                    sent_packets_cache_ = sent_packets_.template project<0>(it);
                }
            }

            if (!packet_found) {
                isc_throw(Unexpected, "Unable to find sent packet.");
            }

            boost::shared_ptr<T> sent_packet(*sent_packets_cache_);
            ++sent_packets_cache_;
            return sent_packet;
        }

        ///  \brief Update delay counters.
        ///
        /// Method updates delay counters based on timestamps of
        /// sent and received packets.
        ///
        /// \param sent_packet sent packet
        /// \param rcvd_packet received packet
        /// \throw isc::Unexpected if failed to calculate timestamps
        void updateDelays(const boost::shared_ptr<T> sent_packet,
                          const boost::shared_ptr<T> rcvd_packet) {
            boost::posix_time::ptime sent_time = sent_packet->getTimestamp();
            boost::posix_time::ptime rcvd_time = rcvd_packet->getTimestamp();

            if (sent_time.is_not_a_date_time() ||
                rcvd_time.is_not_a_date_time()) {
                isc_throw(Unexpected,
                          "Timestamp must be set for sent and "
                          "received packet to measure RTT");
            }
            boost::posix_time::time_period period(sent_time, rcvd_time);
            double delta =
                static_cast<double>(period.length().total_nanoseconds()) / 1e9;

            if (delta < 0) {
                isc_throw(Unexpected, "Sent packet's timestamp must not be "
                          "greater than received packet's timestamp");
            }

            if (delta < min_delay_) {
                min_delay_ = delta;
            }
            if (delta > max_delay_) {
                max_delay_ = delta;
            }
            sum_delay_ += delta;
            square_sum_delay_ += delta * delta;
        }

        /// \brief Return minumum delay between sent and received packet.
        ///
        /// Method returns minimum delay between sent and received packet.
        ///
        /// \return minimum delay between packets.
        double getMinDelay() const { return min_delay_; }

        /// \brief Return maxmimum delay between sent and received packet.
        ///
        /// Method returns maximum delay between sent and received packet.
        ///
        /// \return maximum delay between packets.
        double getMaxDelay() const { return max_delay_; }

        /// \brief Return sum of delays between sent and received packets.
        ///
        /// Method returns sum of delays between sent and received packets.
        ///
        /// \return sum of delays between sent and received packets.
        double getSumDelay() const { return sum_delay_; }

        /// \brief Return square sum of delays between sent and received
        /// packets.
        ///
        /// Method returns square sum of delays between sent and received
        /// packets.
        ///
        /// \return square sum of delays between sent and received packets.
        double getSquareSumDelay() const  { return square_sum_delay_; }
    private:

        /// \brief Private default constructor.
        ///
        /// Default constructor is private because we want the client
        /// class to specify exchange type explicitely.
        ExchangeStats();

        ExchangeType xchg_type_;             ///< Packet exchange type.
        PktList sent_packets_;               ///< List of sent packets.

        /// Iterator pointing to the packet on sent list which will most
        /// likely match next received packet. This is based on the
        /// assumption that server responds in order to incoming packets.
        PktListIterator sent_packets_cache_;

        PktList rcvd_packets_;         ///< List of received packets.

        double min_delay_;             ///< Minimum delay between sent
                                       ///< and received packets.
        double max_delay_;             ///< Maximum delay between sent
                                       ///< and received packets.
        double sum_delay_;             ///< Sum of delays between sent
                                       ///< and received packets.
        double square_sum_delay_;      ///< Square sum of delays between
                                       ///< sent and recived packets.
    };

    /// Pointer to ExchangeStats.
    typedef boost::shared_ptr<ExchangeStats> ExchangeStatsPtr;
    /// Map containing all specified exchange types.
    typedef typename std::map<ExchangeType, ExchangeStatsPtr> ExchangesMap;
    /// Iterator poiting to \ref ExchangesMap
    typedef typename ExchangesMap::iterator ExchangesMapIterator;

    /// \brief Specify new exchange type.
    ///
    /// This method creates new \ref ExchangeStats object that will
    /// collect statistics data from packets exchange of the specified
    /// type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if exchange of specified type exists.
    void addExchangeStats(const ExchangeType xchg_type) {
        if (exchanges_.find(xchg_type) != exchanges_.end()) {
            isc_throw(BadValue, "Exchange of specified type already added.");
        }
        exchanges_[xchg_type] = ExchangeStatsPtr(new ExchangeStats(xchg_type));
    }

    /// \brief Adds new packet to the sent packets list.
    ///
    /// Method adds new packet to the sent packets list.
    /// Packets are added to the list sequentially and
    /// most often read sequentially.
    ///
    /// \param xchg_type exchange type.
    /// \param packet packet to be added to the list
    /// \throw isc::BadValue if invalid exchange type specified.
    void passSentPacket(const ExchangeType xchg_type,
                        const boost::shared_ptr<T> packet) {
        ExchangesMapIterator it = exchanges_.find(xchg_type);
        if (it == exchanges_.end()) {
            isc_throw(BadValue, "Packets exchange not specified");
        }
        it->second->appendSent(packet);
    }

    /// \brief Add new received packet and match with sent packet.
    ///
    /// Method adds new packet to the list of received packets. It
    /// also searches for corresponding packet on the list of sent
    /// packets. When packets are matched the statistics counters
    /// are updated accordingly for the particular exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \param packet received packet
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \throw isc::Unexpected if corresponding packet was not
    /// found on the list of sent packets.
    void passRcvdPacket(const ExchangeType xchg_type,
                        const boost::shared_ptr<T> packet) {
        ExchangesMapIterator it = exchanges_.find(xchg_type);
        if (it == exchanges_.end()) {
            isc_throw(BadValue, "Packets exchange not specified");
        }
        ExchangeStatsPtr xchg_stats = it->second;
        boost::shared_ptr<T> sent_packet
            = xchg_stats->findSent(packet->getTransid());

        xchg_stats->updateDelays(sent_packet, packet);
    }


private:
    ExchangesMap exchanges_;        ///< Map of exchange types.
};

} // namespace perfdhcp
} // namespace isc

#endif // __STATS_MGR_H
