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

#include <iostream>
#include <map>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/global_fun.hpp>
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

    /// \brief Custom Counter
    ///
    /// This class represents custom statistics counters. Client class
    /// may create unlimited number of counters. Such counters are
    /// being stored in map in Statistics Manager and access using
    /// unique string key.
    class CustomCounter {
    public:
        /// \brief Constructor.
        ///
        /// This constructor sets counter name. This name is used in
        /// log file to report value of each counter.
        ///
        /// \param name name of the counter used in log file.
        CustomCounter(const std::string& name) :
            counter_(0),
            name_(name) { };

        /// \brief Increment operator.
        const CustomCounter& operator++() {
            ++counter_;
            return *this;
        }

        /// \brief Increment operator.
        const CustomCounter& operator++(int) {
            CustomCounter& this_counter(*this);
            operator++();
            return this_counter;
        }

        /// \brief Return counter value.
        ///
        /// Method returns counter value.
        ///
        /// \return counter value.
        uint64_t getValue() const {
            return counter_;
        }

        /// \brief Return counter name.
        ///
        /// Method returns counter name.
        ///
        /// \return counter name.
        const std::string& getName() const {
            return name_;
        }
    private:
        /// \brief Default constructor.
        ///
        /// Default constrcutor is private because we don't want client
        /// class to call it because we want client class to specify
        /// counter's name.
        CustomCounter() { };

        uint64_t counter_;  ///< Counter's value.
        std::string name_;  ///< Counter's name.
    };

    typedef typename boost::shared_ptr<CustomCounter> CustomCounterPtr;

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

        static uint32_t transid_hash(boost::shared_ptr<T> packet) {
            return packet->getTransid() & 1023;
        }

        /// \brief List of packets (sent or received).
        ///
        /// List of packets based on multi index container allows efficient
        /// search of packets based on their sequence (order in which they
        /// were inserted) as well as based on packet transaction id.
        typedef boost::multi_index_container<
            boost::shared_ptr<T>,
            boost::multi_index::indexed_by<
                boost::multi_index::sequenced<>,
                boost::multi_index::hashed_non_unique<
                        boost::multi_index::global_fun<
                            boost::shared_ptr<T>,
                            uint32_t,
                            &ExchangeStats::transid_hash
                        >
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
            : xchg_type_(xchg_type),
            min_delay_(std::numeric_limits<double>::max()),
            max_delay_(0.),
            sum_delay_(0.),
            orphans_(0),
            square_sum_delay_(0.),
            ordered_lookups_(0),
            unordered_lookup_size_sum_(0),
            unordered_lookups_(0),
            sent_packets_num_(0),
            rcvd_packets_num_(0) {
            sent_packets_cache_ = sent_packets_.begin();
        }

        /// \brief Add new packet to list of sent packets.
        ///
        /// Method adds new packet to list of sent packets.
        ///
        /// \param packet packet object to be added.
        void appendSent(const boost::shared_ptr<T> packet) {
            ++sent_packets_num_;
            sent_packets_.template get<0>().push_back(packet);
        }

        /// \brief Add new packet to list of received packets.
        ///
        /// Method adds new packet to list of received packets.
        ///
        /// \param packet packet object to be added.
        void appendRcvd(const boost::shared_ptr<T> packet) {
            ++rcvd_packets_num_;
            rcvd_packets_.template get<0>().push_back(packet);
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
            // We don't bother calculating deltas in nanoseconds. It is much
            // more convenient to use seconds instead because we are going to
            // sum them up.
            double delta =
                static_cast<double>(period.length().total_nanoseconds()) / 1e9;

            if (delta < 0) {
                isc_throw(Unexpected, "Sent packet's timestamp must not be "
                          "greater than received packet's timestamp");
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
            square_sum_delay_ += delta * delta;
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
        /// \return packet having specified transaction or NULL if packet
        /// not found
        boost::shared_ptr<T> findSent(const uint32_t transid) {
            if (sent_packets_.size() == 0) {
                // List of sent packets is empty so there is no sense
                // to continue looking fo the packet. It also means
                // that the received packet we got has no corresponding
                // sent packet so orphans counter has to be updated.
                ++orphans_;
                return boost::shared_ptr<T>();
            } else if (sent_packets_cache_ == sent_packets_.end()) {
                // Even if there are still many unmatched packets on the
                // list we might hit the end of it because of unordered
                // lookups. The next logical step is to reset cache.
                sent_packets_cache_ = sent_packets_.begin();
            }

            // With this variable we will be signalling success or failure
            // to find the packet.
            bool packet_found = false;
            // Most likely responses are sent from the server in the same
            // order as client's requests to the server. We are caching
            // next sent packet and first try to match with it the next
            // incoming packet. We are successful if there is no
            // packet drop or out of order packets sent. This is actually
            // the fastest way to look for packets.
            if ((*sent_packets_cache_)->getTransid() == transid) {
                ++ordered_lookups_;
                packet_found = true;
            } else {
                // If we are here, it means that we were unable to match the
                // next incoming packet with next sent packet so we need to
                // take a little more expensive approach to look packets using
                // alternative index (transaction id & 1023).
                PktListTransidIndex& idx = sent_packets_.template get<1>();
                // Packets are grouped using trasaction id masking with value
                // of 1023. For instance, packets with transaction id equal to
                // 1, 1024 ... will belong to the same group (a.k.a. bucket).
                // When using alternative index we don't find the packet but
                // bucket of packets and need to iterate through the bucket
                // to find the one that has desired transaction id.
                std::pair<PktListTransidIterator,PktListTransidIterator> p =
                    idx.equal_range(transid & 1023);
                // We want to keep statistics of unordered lookups to make
                // sure that there is a right balance before number of
                // unordered lookups and ordered lookups. If number of unordered
                // lookups is high it may mean that many packets are lost or
                // sent out of order.
                ++unordered_lookups_;
                // We also want to keep the mean value of the bucket. The lower
                // bucket size the better. If bucket sizes appear to big we
                // might want to increase number of buckets.
                unordered_lookup_size_sum_ += std::distance(p.first, p.second);
                for (PktListTransidIterator it = p.first; it != p.second;
                     ++it) {
                    if ((*it)->getTransid() == transid) {
                        packet_found = true;
                        sent_packets_cache_ =
                            sent_packets_.template project<0>(it);
                        break;
                    }
                }
            }

            if (!packet_found) {
                // If we are here, it means that both ordered lookup and
                // unordered lookup failed. Searched packet is not on the list.
                ++orphans_;
                return boost::shared_ptr<T>();
            }

            boost::shared_ptr<T> sent_packet(*sent_packets_cache_);
            // If packet was found, we assume it will be never searched
            // again. We want to delete this packet from the list to
            // improve performance of future searches.
            sent_packets_cache_ = eraseSent(sent_packets_cache_);
            return sent_packet;
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

        /// \brief Return number of orphant packets.
        ///
        /// Method returns number of received packets that had no matching
        /// sent packet. It is possible that such packet was late or not
        /// for us.
        ///
        /// \return number of orphant received packets.
        uint64_t getOrphans() const { return orphans_; }

        /// \brief Return average unordered lookup set size.
        ///
        /// Method returns average unordered lookup set size.
        /// This value is changes every time \findSet function uses
        /// unordered packet lookup using transaction id.
        ///
        /// \return average unordered lookup set size.
        double getAvgUnorderedLookupSetSize() const {
            if (unordered_lookups_ == 0) {
                return 0.;
            }
            return static_cast<double>(unordered_lookup_size_sum_) /
                static_cast<double>(unordered_lookups_);
        }

        /// \brief Return number of unordered sent packets lookups
        ///
        /// Method returns number of unordered sent packet lookups.
        /// Unordered lookup is used when received packet was sent
        /// out of order by server - transaction id of received
        /// packet does not match transaction id of next sent packet.
        ///
        /// \return number of unordered lookups.
        uint64_t getUnorderedLookups() const { return unordered_lookups_; }

        /// \brief Return number of ordered sent packets lookups
        ///
        /// Method returns number of ordered sent packet lookups.
        /// Ordered lookup is used when packets are received in the
        /// same order as they were sent to the server.
        /// If packets are skipped or received out of order, lookup
        /// function will use unordered lookup (with hash table).
        ///
        /// \return number of ordered lookups.
        uint64_t getOrderedLookups() const { return ordered_lookups_; }

        /// \brief Return total number of sent packets
        ///
        /// Method returns total number of sent packets.
        ///
        /// \return number of sent packets.
        uint64_t getSentPacketsNum() const {
            return sent_packets_num_;
        }

        /// \brief Return total number of received packets
        ///
        /// Method returns total number of received packets.
        ///
        /// \return number of received packets.
        uint64_t getRcvdPacketsNum() const {
            return rcvd_packets_num_;
        }

    private:

        /// \brief Private default constructor.
        ///
        /// Default constructor is private because we want the client
        /// class to specify exchange type explicitely.
        ExchangeStats();


        /// \brief Erase packet from the list of sent packets.
        ///
        /// Method erases packet from the list of sent packets.
        ///
        /// \param it iterator pointing to packet to be erased.
        /// \return iterator pointing to packet following erased
        /// packet or sent_packets_.end() if packet not found.
         PktListIterator eraseSent(const PktListIterator it) {
            return sent_packets_.template get<0>().erase(it);
        }

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

        uint64_t orphans_;             ///< Number of orphant received packets.

        /// Sum of unordered lookup sets. Needed to calculate mean size of
        /// lookup set. It is desired that number of unordered lookups is
        /// minimal for performance reasons. Tracking number of lookups and
        /// mean size of the lookup set should give idea of packets serach
        /// complexity.
        uint64_t unordered_lookup_size_sum_;

        uint64_t unordered_lookups_;   ///< Number of unordered sent packets
                                       ///< lookups.
        uint64_t ordered_lookups_;     ///< Number of ordered sent packets
                                       ///< lookups.

        uint64_t sent_packets_num_;    ///< Total number of sent packets.
        uint64_t rcvd_packets_num_;    ///< Total number of received packets.
    };

    /// Pointer to ExchangeStats.
    typedef boost::shared_ptr<ExchangeStats> ExchangeStatsPtr;
    /// Map containing all specified exchange types.
    typedef typename std::map<ExchangeType, ExchangeStatsPtr> ExchangesMap;
    /// Iterator poiting to \ref ExchangesMap
    typedef typename ExchangesMap::const_iterator ExchangesMapIterator;
    /// Map containing custom counters.
    typedef typename std::map<std::string, CustomCounterPtr> CustomCountersMap;
    /// Iterator for \ref CustomCountersMap.
    typedef typename CustomCountersMap::iterator CustomCountersMapIterator;

    /// \brief Constructor.
    StatsMgr()
        : exchanges_(),
          custom_counters_() {
    }

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

    /// \brief Add named custom uint64 counter.
    ///
    /// Method creates new named counter and stores in counter's map under
    /// key specified here as short_name.
    ///
    /// \param short_name key to use to access counter in the map.
    /// \param long_name name of the counter presented in the log file.
    void addCustomCounter(const std::string& short_name,
                          const std::string& long_name) {
        if (custom_counters_.find(short_name) != custom_counters_.end()) {
            isc_throw(BadValue,
                      "Custom counter " << short_name << " already added.");
        }
        custom_counters_[short_name] =
            CustomCounterPtr(new CustomCounter(long_name));
    }

    /// \brief Return specified counter.
    ///
    /// Method returns specified counter.
    ///
    /// \param counter_key key poiting to the counter in the counters map.
    /// \return pointer to specified counter object.
    CustomCounterPtr getCounter(const std::string& counter_key) {
        CustomCountersMapIterator it = custom_counters_.find(counter_key);
        if (it == custom_counters_.end()) {
            isc_throw(BadValue,
                      "Custom counter " << counter_key << "does not exist");
        }
        return it->second;
    }

    /// \brief Increment specified counter.
    ///
    /// Increement counter value by one.
    ///
    /// \param counter_key key poitinh to the counter in the counters map.
    /// \return pointer to specified counter after incrementation.
    const CustomCounter& IncrementCounter(const std::string& counter_key) {
        CustomCounterPtr counter = getCounter(counter_key);
        return ++(*counter);
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
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        xchg_stats->appendSent(packet);
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
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        boost::shared_ptr<T> sent_packet
            = xchg_stats->findSent(packet->getTransid());

        if (sent_packet) {
            xchg_stats->updateDelays(sent_packet, packet);
            xchg_stats->appendRcvd(packet);
        }
    }

    /// \brief Return minumum delay between sent and received packet.
    ///
    /// Method returns minimum delay between sent and received packet
    /// for specified exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return minimum delay between packets.
    double getMinDelay(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getMinDelay();
    }

    /// \brief Return maxmimum delay between sent and received packet.
    ///
    /// Method returns maximum delay between sent and received packet
    /// for specified exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return maximum delay between packets.
    double getMaxDelay(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getMaxDelay();
    }

    /// \brief Return sum of delays between sent and received packets.
    ///
    /// Method returns sum of delays between sent and received packets
    /// for specified exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return sum of delays between sent and received packets.
    double getSumDelay(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getSumDelay();
    }

    /// \brief Return square sum of delays between sent and received
    /// packets.
    ///
    /// Method returns square sum of delays between sent and received
    /// packets for specified exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return square sum of delays between sent and received packets.
    double getSquareSumDelay(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getSquareSumDelay();
    }

    /// \brief Return number of orphant packets.
    ///
    /// Method returns number of orphant packets for specified
    /// exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of orphant packets so far.
    uint64_t getOrphans(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getOrphans();
    }

    /// \brief Return average unordered lookup set size.
    ///
    /// Method returns average unordered lookup set size.
    /// This value is changes every time \findSet function uses
    /// unordered packet lookup using transaction id.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return average unordered lookup set size.
    double getAvgUnorderedLookupSetSize(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getAvgUnorderedLookupSetSize();
    }

    /// \brief Return number of unordered sent packets lookups
    ///
    /// Method returns number of unordered sent packet lookups.
    /// Unordered lookup is used when received packet was sent
    /// out of order by server - transaction id of received
    /// packet does not match transaction id of next sent packet.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of unordered lookups.
    uint64_t getUnorderedLookups(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getUnorderedLookups();
    }

    /// \brief Return number of ordered sent packets lookups
    ///
    /// Method returns number of ordered sent packet lookups.
    /// Ordered lookup is used when packets are received in the
    /// same order as they were sent to the server.
    /// If packets are skipped or received out of order, lookup
    /// function will use unordered lookup (with hash table).
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of ordered lookups.
    uint64_t getOrderedLookups(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getOrderedLookups();
    }

    /// \brief Return total number of sent packets
    ///
    /// Method returns total number of sent packets for specified
    /// exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of sent packets.
    uint64_t getSentPacketsNum(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getSentPacketsNum();
    }

    /// \brief Return total number of received packets
    ///
    /// Method returns total number of received packets for specified
    /// exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of received packets.
    uint64_t getRcvdPacketsNum(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return xchg_stats->getRcvdPacketsNum();
    }

private:
    /// \brief Return exchange stats object for given exchange type
    ///
    /// Method returns exchange stats object for given exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return exchange stats object.
    ExchangeStatsPtr getExchangeStats(const ExchangeType xchg_type) const {
        ExchangesMapIterator it = exchanges_.find(xchg_type);
        if (it == exchanges_.end()) {
            isc_throw(BadValue, "Packets exchange not specified");
        }
        ExchangeStatsPtr xchg_stats = it->second;
        return xchg_stats;
    }

    ExchangesMap exchanges_;            ///< Map of exchange types.
    CustomCountersMap custom_counters_; ///< Map with custom counters.
};

} // namespace perfdhcp
} // namespace isc

#endif // __STATS_MGR_H
