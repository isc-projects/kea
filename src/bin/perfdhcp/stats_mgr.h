// Copyright (C) 2012-2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef STATS_MGR_H
#define STATS_MGR_H

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>
#include <map>


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
/// \param T class representing DHCPv4 or DHCPv6 packet.
template <class T = dhcp::Pkt4>
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
            return (*this);
        }

        /// \brief Increment operator.
        const CustomCounter& operator++(int) {
            CustomCounter& this_counter(*this);
            operator++();
            return (this_counter);
        }

        const CustomCounter& operator+=(int val) {
            counter_ += val;
            return (*this);
        }

        /// \brief Return counter value.
        ///
        /// Method returns counter value.
        ///
        /// \return counter value.
        uint64_t getValue() const { return(counter_); }

        /// \brief Return counter name.
        ///
        /// Method returns counter name.
        ///
        /// \return counter name.
        const std::string& getName() const { return(name_); }
    private:
        /// \brief Default constructor.
        ///
        /// Default constructor is private because we don't want client
        /// class to call it because we want client class to specify
        /// counter's name.
        CustomCounter() { };

        uint64_t counter_;  ///< Counter's value.
        std::string name_;            ///< Counter's name.
    };

    typedef typename boost::shared_ptr<CustomCounter> CustomCounterPtr;

    /// DHCP packet exchange types.
    enum ExchangeType {
        XCHG_DO,  ///< DHCPv4 DISCOVER-OFFER
        XCHG_RA,  ///< DHCPv4 REQUEST-ACK
        XCHG_SA,  ///< DHCPv6 SOLICIT-ADVERTISE
        XCHG_RR,  ///< DHCPv6 REQUEST-REPLY
        XCHG_RN,  ///< DHCPv6 RENEW-REPLY
        XCHG_RL   ///< DHCPv6 RELEASE-REPLY
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

        /// \brief Hash transaction id of the packet.
        ///
        /// Function hashes transaction id of the packet. Hashing is
        /// non-unique. Many packets may have the same hash value and thus
        /// they belong to the same packet buckets. Packet buckets are
        /// used for unordered packets search with multi index container.
        ///
        /// \param packet packet which transaction id is to be hashed.
        /// \throw isc::BadValue if packet is null.
        /// \return transaction id hash.
        static uint32_t hashTransid(const boost::shared_ptr<T>& packet) {
            if (!packet) {
                isc_throw(BadValue, "Packet is null");
            }
            return(packet->getTransid() & 1023);
        }

        /// \brief List of packets (sent or received).
        ///
        /// List of packets based on multi index container allows efficient
        /// search of packets based on their sequence (order in which they
        /// were inserted) as well as based on their hashed transaction id.
        /// The first index (sequenced) provides the way to use container
        /// as a regular list (including iterators, removal of elements from
        /// the middle of the collection etc.). This index is meant to be used
        /// more frequently than the latter one and it is based on the
        /// assumption that responses from the DHCP server are received in
        /// order. In this case, when next packet is received it can be
        /// matched with next packet on the list of sent packets. This
        /// prevents intensive searches on the list of sent packets every
        /// time new packet arrives. In many cases however packets can be
        /// dropped by the server or may be sent out of order and we still
        ///  want to have ability to search packets using transaction id.
        /// The second index can be used for this purpose. This index is
        /// hashing transaction ids using custom function \ref hashTransid.
        /// Note that other possibility would be to simply specify index
        /// that uses transaction id directly (instead of hashing with
        /// \ref hashTransid). In this case however we have chosen to use
        /// hashing function because it shortens the index size to just
        /// 1023 values maximum. Search operation on this index generally
        /// returns the range of packets that have the same transaction id
        /// hash assigned but most often these ranges will be short so further
        /// search within a range to find a packet with pacrticular transaction
        /// id will not be intensive.
        ///
        /// Example 1: Add elements to the list
        /// \code
        /// PktList packets_collection();
        /// boost::shared_ptr<Pkt4> pkt1(new Pkt4(...));
        /// boost::shared_ptr<Pkt4> pkt2(new Pkt4(...));
        /// // Add new packet to the container, it will be available through
        /// // both indexes
        /// packets_collection.push_back(pkt1);
        /// // Here is another way to add packet to the container. The result
        /// // is exactly the same as previously.
        /// packets_collection.template get<0>().push_back(pkt2);
        /// \endcode
        ///
        /// Example 2: Access elements through sequencial index
        /// \code
        /// PktList packets_collection();
        /// ...  # Add elements to the container
        /// for (PktListIterator it = packets_collection.begin();
        ///      it != packets_collection.end();
        ///      ++it) {
        ///          boost::shared_ptr<Pkt4> pkt = *it;
        ///          # Do something with packet;
        ///      }
        /// \endcode
        ///
        /// Example 3: Access elements through hashed index
        /// \code
        /// // Get the instance of the second search index.
        /// PktListTransidHashIndex& idx = sent_packets_.template get<1>();
        /// // Get the range (bucket) of packets sharing the same transaction
        /// // id hash.
        /// std::pair<PktListTransidHashIterator,PktListTransidHashIterator> p =
        ///     idx.equal_range(hashTransid(rcvd_packet));
        /// // Iterate through the returned bucket.
        /// for (PktListTransidHashIterator it = p.first; it != p.second;
        ///     ++it) {
        ///    boost::shared_ptr pkt = *it;
        ///    ... # Do something with the packet (e.g. check transaction id)
        /// }
        /// \endcode
        typedef boost::multi_index_container<
            // Container holds shared_ptr<Pkt4> or shared_ptr<Pkt6> objects.
            boost::shared_ptr<T>,
            // List container indexes.
            boost::multi_index::indexed_by<
                // Sequenced index provides the way to use this container
                // in the same way as std::list.
                boost::multi_index::sequenced<>,
                // The other index keeps products of transaction id.
                boost::multi_index::hashed_non_unique<
                    // Specify hash function to get the product of
                    // transaction id. This product is obtained by calling
                    // hashTransid() function.
                    boost::multi_index::global_fun<
                        // Hashing function takes shared_ptr<Pkt4> or
                        // shared_ptr<Pkt6> as argument.
                        const boost::shared_ptr<T>&,
                        // ... and returns uint32 value.
                        uint32_t,
                        // ... and here is a reference to it.
                        &ExchangeStats::hashTransid
                    >
                >
            >
        > PktList;

        /// Packet list iterator for sequencial access to elements.
        typedef typename PktList::iterator PktListIterator;
        /// Packet list index to search packets using transaction id hash.
        typedef typename PktList::template nth_index<1>::type
            PktListTransidHashIndex;
        /// Packet list iterator to access packets using transaction id hash.
        typedef typename PktListTransidHashIndex::const_iterator
            PktListTransidHashIterator;

        /// \brief Constructor
        ///
        /// \param xchg_type exchange type
        /// \param drop_time maximum time elapsed before packet is
        /// assumed dropped. Negative value disables it.
        /// \param archive_enabled if true packets archive mode is enabled.
        /// In this mode all packets are stored throughout the test execution.
        /// \param boot_time Holds the timestamp when perfdhcp has been started.
        ExchangeStats(const ExchangeType xchg_type,
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
              boot_time_(boot_time)
        {
            next_sent_ = sent_packets_.begin();
        }

        /// \brief Add new packet to list of sent packets.
        ///
        /// Method adds new packet to list of sent packets.
        ///
        /// \param packet packet object to be added.
        /// \throw isc::BadValue if packet is null.
        void appendSent(const boost::shared_ptr<T>& packet) {
            if (!packet) {
                isc_throw(BadValue, "Packet is null");
            }
            ++sent_packets_num_;
            sent_packets_.template get<0>().push_back(packet);
        }

        /// \brief Add new packet to list of received packets.
        ///
        /// Method adds new packet to list of received packets.
        ///
        /// \param packet packet object to be added.
        /// \throw isc::BadValue if packet is null.
        void appendRcvd(const boost::shared_ptr<T>& packet) {
            if (!packet) {
                isc_throw(BadValue, "Packet is null");
            }
            rcvd_packets_.push_back(packet);
        }

        ///  \brief Update delay counters.
        ///
        /// Method updates delay counters based on timestamps of
        /// sent and received packets.
        ///
        /// \param sent_packet sent packet
        /// \param rcvd_packet received packet
        /// \throw isc::BadValue if sent or received packet is null.
        /// \throw isc::Unexpected if failed to calculate timestamps
        void updateDelays(const boost::shared_ptr<T>& sent_packet,
                          const boost::shared_ptr<T>& rcvd_packet) {
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
            sum_delay_squared_ += delta * delta;
        }

        /// \brief Match received packet with the corresponding sent packet.
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
        /// \param rcvd_packet received packet to be matched with sent packet.
        /// \throw isc::BadValue if received packet is null.
        /// \return packet having specified transaction or NULL if packet
        /// not found
        boost::shared_ptr<T>
        matchPackets(const boost::shared_ptr<T>& rcvd_packet) {
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
                return(boost::shared_ptr<T>());
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
                // Packets are grouped using trasaction id masked with value
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
                for (PktListTransidHashIterator it = p.first; it != p.second;
                     ++it) {
                    if ((*it)->getTransid() == rcvd_packet->getTransid()) {
                        packet_found = true;
                        next_sent_ =
                            sent_packets_.template project<0>(it);
                        break;
                    }
                    ptime now = microsec_clock::universal_time();
                    ptime packet_time = (*it)->getTimestamp();
                    time_period packet_period(packet_time, now);
                    if (!packet_period.is_null()) {
                        double period_fractional =
                            packet_period.length().total_seconds() +
                            (static_cast<double>(packet_period.length().fractional_seconds())
                             / packet_period.length().ticks_per_second());
                        if (drop_time_ > 0 && (period_fractional > drop_time_)) {
                            // The packet pointed to by 'it' is timed out so we
                            // have to remove it. Removal may invalidate the
                            // next_sent_ pointer if it points to the packet
                            // being removed. So, we set the next_sent_ to point
                            // to the next packet after removed one. This
                            // pointer will be further updated in the following
                            // iterations, if the subsequent packets are also
                            // timed out.
                            next_sent_ = eraseSent(sent_packets_.template project<0>(it));
                            ++collected_;
                        }
                    }
                }
            }

            if (!packet_found) {
                // If we are here, it means that both ordered lookup and
                // unordered lookup failed. Searched packet is not on the list.
                ++orphans_;
                return(boost::shared_ptr<T>());
            }

            // Packet is matched so we count it. We don't count unmatched packets
            // as they are counted as orphans with a separate counter.
            ++rcvd_packets_num_;
            boost::shared_ptr<T> sent_packet(*next_sent_);
            // If packet was found, we assume it will be never searched
            // again. We want to delete this packet from the list to
            // improve performance of future searches.
            next_sent_ = eraseSent(next_sent_);
            return(sent_packet);
        }

        /// \brief Return minumum delay between sent and received packet.
        ///
        /// Method returns minimum delay between sent and received packet.
        ///
        /// \return minimum delay between packets.
        double getMinDelay() const { return(min_delay_); }

        /// \brief Return maxmimum delay between sent and received packet.
        ///
        /// Method returns maximum delay between sent and received packet.
        ///
        /// \return maximum delay between packets.
        double getMaxDelay() const { return(max_delay_); }

        /// \brief Return average packet delay.
        ///
        /// Method returns average packet delay. If no packets have been
        /// received for this exchange avg delay can't be calculated and
        /// thus method throws exception.
        ///
        /// \throw isc::InvalidOperation if no packets for this exchange
        /// have been received yet.
        /// \return average packet delay.
        double getAvgDelay() const {
            if (rcvd_packets_num_  == 0) {
                isc_throw(InvalidOperation, "no packets received");
            }
            return(sum_delay_ / rcvd_packets_num_);
        }

        /// \brief Return standard deviation of packet delay.
        ///
        /// Method returns standard deviation of packet delay. If no
        /// packets have been received for this exchange, the standard
        /// deviation can't be calculated and thus method throws
        /// exception.
        ///
        /// \throw isc::InvalidOperation if number of received packets
        /// for the exchange is equal to zero.
        /// \return standard deviation of packet delay.
        double getStdDevDelay() const {
            if (rcvd_packets_num_ == 0) {
                isc_throw(InvalidOperation, "no packets received");
            }
            return(sqrt(sum_delay_squared_ / rcvd_packets_num_ -
                        getAvgDelay() * getAvgDelay()));
        }

        /// \brief Return number of orphant packets.
        ///
        /// Method returns number of received packets that had no matching
        /// sent packet. It is possible that such packet was late or not
        /// for us.
        ///
        /// \return number of orphant received packets.
        uint64_t getOrphans() const { return(orphans_); }

        /// \brief Return number of garbage collected packets.
        ///
        /// Method returns number of garbage collected timed out
        /// packets. Packet is assumed timed out when duration
        /// between sending it to server and receiving server's
        /// response is greater than value specified with -d<value>
        /// command line argument.
        ///
        /// \return number of garbage collected packets.
        uint64_t getCollectedNum() const { return(collected_); }

        /// \brief Return average unordered lookup set size.
        ///
        /// Method returns average unordered lookup set size.
        /// This value changes every time \ref ExchangeStats::matchPackets
        /// function performs unordered packet lookup.
        ///
        /// \throw isc::InvalidOperation if there have been no unordered
        /// lookups yet.
        /// \return average unordered lookup set size.
        double getAvgUnorderedLookupSetSize() const {
            if (unordered_lookups_ == 0) {
                isc_throw(InvalidOperation, "no unordered lookups");
            }
            return(static_cast<double>(unordered_lookup_size_sum_) /
                   static_cast<double>(unordered_lookups_));
        }

        /// \brief Return number of unordered sent packets lookups
        ///
        /// Method returns number of unordered sent packet lookups.
        /// Unordered lookup is used when received packet was sent
        /// out of order by server - transaction id of received
        /// packet does not match transaction id of next sent packet.
        ///
        /// \return number of unordered lookups.
        uint64_t getUnorderedLookups() const { return(unordered_lookups_); }

        /// \brief Return number of ordered sent packets lookups
        ///
        /// Method returns number of ordered sent packet lookups.
        /// Ordered lookup is used when packets are received in the
        /// same order as they were sent to the server.
        /// If packets are skipped or received out of order, lookup
        /// function will use unordered lookup (with hash table).
        ///
        /// \return number of ordered lookups.
        uint64_t getOrderedLookups() const { return(ordered_lookups_); }

        /// \brief Return total number of sent packets
        ///
        /// Method returns total number of sent packets.
        ///
        /// \return number of sent packets.
        uint64_t getSentPacketsNum() const { return(sent_packets_num_); }

        /// \brief Return total number of received packets
        ///
        /// Method returns total number of received packets.
        ///
        /// \return number of received packets.
        uint64_t getRcvdPacketsNum() const { return(rcvd_packets_num_); }

        /// \brief Return number of dropped packets.
        ///
        /// Method returns number of dropped packets.
        ///
        /// \return number of dropped packets.
        uint64_t getDroppedPacketsNum() const {
            uint64_t drops = 0;
            if (getSentPacketsNum() > getRcvdPacketsNum()) {
                drops = getSentPacketsNum() - getRcvdPacketsNum();
            }
            return(drops);
        }

        /// \brief Print main statistics for packet exchange.
        ///
        /// Method prints main statistics for particular exchange.
        /// Statistics includes: number of sent and received packets,
        /// number of dropped packets and number of orphans.
        ///
        /// \todo Currently the number of orphans is not displayed because
        /// Reply messages received for Renew and Releases are counted as
        /// orphans for the 4-way exchanges, which is wrong. We will need to
        /// move the orphans counting out of the Statistics Manager so as
        /// orphans counter is increased only if the particular message is
        /// not identified as a reponse to any of the messages sent by perfdhcp.
        void printMainStats() const {
            using namespace std;
            cout << "sent packets: " << getSentPacketsNum() << endl
                 << "received packets: " << getRcvdPacketsNum() << endl
                 << "drops: " << getDroppedPacketsNum() << endl;
            //                 << "orphans: " << getOrphans() << endl;
        }

        /// \brief Print round trip time packets statistics.
        ///
        /// Method prints round trip time packets statistics. Statistics
        /// includes minimum packet delay, maximum packet delay, average
        /// packet delay and standard deviation of delays. Packet delay
        /// is a duration between sending a packet to server and receiving
        /// response from server.
        void printRTTStats() const {
            using namespace std;
            try {
                cout << fixed << setprecision(3)
                     << "min delay: " << getMinDelay() * 1e3 << " ms" << endl
                     << "avg delay: " << getAvgDelay() * 1e3 << " ms" << endl
                     << "max delay: " << getMaxDelay() * 1e3 << " ms" << endl
                     << "std deviation: " << getStdDevDelay() * 1e3 << " ms"
                     << endl
                     << "collected packets: " << getCollectedNum() << endl;
            } catch (const Exception&) {
                cout << "Delay summary unavailable! No packets received." << endl;
            }
        }

        //// \brief Print timestamps for sent and received packets.
        ///
        /// Method prints timestamps for all sent and received packets for
        /// packet exchange. In order to run this method the packets
        /// archiving mode has to be enabled during object constructions.
        /// Otherwise sent packets are not stored during tests execution
        /// and this method has no ability to get and print their timestamps.
        ///
        /// \throw isc::InvalidOperation if found packet with no timestamp or
        /// if packets archive mode is disabled.
        void printTimestamps() {
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
                boost::shared_ptr<T> rcvd_packet = *it;
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
                        boost::shared_ptr<T> sent_packet = *it_archived;
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

    private:

        /// \brief Private default constructor.
        ///
        /// Default constructor is private because we want the client
        /// class to specify exchange type explicitly.
        ExchangeStats();

        /// \brief Erase packet from the list of sent packets.
        ///
        /// Method erases packet from the list of sent packets.
        ///
        /// \param it iterator pointing to packet to be erased.
        /// \return iterator pointing to packet following erased
        /// packet or sent_packets_.end() if packet not found.
         PktListIterator eraseSent(const PktListIterator it) {
             if (archive_enabled_) {
                 // We don't want to keep list of all sent packets
                 // because it will affect packet lookup performance.
                 // If packet is matched with received packet we
                 // move it to list of archived packets. List of
                 // archived packets may be used for diagnostics
                 // when test is completed.
                 archived_packets_.push_back(*it);
             }
             // get<0>() template returns sequencial index to
             // container.
             return(sent_packets_.template get<0>().erase(it));
        }

        ExchangeType xchg_type_;             ///< Packet exchange type.
        PktList sent_packets_;               ///< List of sent packets.

        /// Iterator pointing to the packet on sent list which will most
        /// likely match next received packet. This is based on the
        /// assumption that server responds in order to incoming packets.
        PktListIterator next_sent_;

        PktList rcvd_packets_;         ///< List of received packets.

        /// List of archived packets. All sent packets that have
        /// been matched with received packet are moved to this
        /// list for diagnostics purposes.
        PktList archived_packets_;

        /// Indicates all packets have to be preserved after matching.
        /// By default this is disabled which means that when received
        /// packet is matched with sent packet both are deleted. This
        /// is important when test is executed for extended period of
        /// time and high memory usage might be the issue.
        /// When timestamps listing is specified from the command line
        /// (using diagnostics selector), all packets have to be preserved
        /// so as the printing method may read their timestamps and
        /// print it to user. In such usage model it will be rare to
        /// run test for extended period of time so it should be fine
        /// to keep all packets archived throughout the test.
        bool archive_enabled_;

        /// Maxmimum time elapsed between sending and receiving packet
        /// before packet is assumed dropped.
        double drop_time_;

        double min_delay_;             ///< Minimum delay between sent
                                       ///< and received packets.
        double max_delay_;             ///< Maximum delay between sent
                                       ///< and received packets.
        double sum_delay_;             ///< Sum of delays between sent
                                       ///< and received packets.
        double sum_delay_squared_;     ///< Squared sum of delays between
                                       ///< sent and recived packets.

        uint64_t orphans_;   ///< Number of orphant received packets.

        uint64_t collected_; ///< Number of garbage collected packets.

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
        boost::posix_time::ptime boot_time_; ///< Time when test is started.
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
    typedef typename CustomCountersMap::const_iterator CustomCountersMapIterator;

    /// \brief Constructor.
    ///
    /// This constructor by default disables packets archiving mode.
    /// In this mode all packets from the list of sent packets are
    /// moved to list of archived packets once they have been matched
    /// with received packets. This is required if it has been selected
    /// from the command line to print timestamps for all packets after
    /// the test. If this is not selected archiving should be disabled
    /// for performance reasons and to avoid waste of memory for storing
    /// large list of archived packets.
    ///
    /// \param archive_enabled true indicates that packets
    /// archive mode is enabled.
    StatsMgr(const bool archive_enabled = false) :
        exchanges_(),
        archive_enabled_(archive_enabled),
        boot_time_(boost::posix_time::microsec_clock::universal_time()) {
    }

    /// \brief Specify new exchange type.
    ///
    /// This method creates new \ref ExchangeStats object that will
    /// collect statistics data from packets exchange of the specified
    /// type.
    ///
    /// \param xchg_type exchange type.
    /// \param drop_time maximum time elapsed before packet is
    /// assumed dropped. Negative value disables it.
    /// \throw isc::BadValue if exchange of specified type exists.
    void addExchangeStats(const ExchangeType xchg_type,
                          const double drop_time = -1) {
        if (exchanges_.find(xchg_type) != exchanges_.end()) {
            isc_throw(BadValue, "Exchange of specified type already added.");
        }
        exchanges_[xchg_type] =
            ExchangeStatsPtr(new ExchangeStats(xchg_type,
                                               drop_time,
                                               archive_enabled_,
                                               boot_time_));
    }

    /// \brief Check if the exchange type has been specified.
    ///
    /// This method checks if the \ref ExchangeStats object of a particular type
    /// exists (has been added using \ref addExchangeStats function).
    ///
    /// \param xchg_type A type of the exchange being repersented by the
    /// \ref ExchangeStats object.
    ///
    /// \return true if the \ref ExchangeStats object has been added for a
    /// specified exchange type.
    bool hasExchangeStats(const ExchangeType xchg_type) const {
        return (exchanges_.find(xchg_type) != exchanges_.end());
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

    /// \brief Check if any packet drops occured.
    ///
    // \return true, if packet drops occured.
    bool droppedPackets() const {
        for (ExchangesMapIterator it = exchanges_.begin();
             it != exchanges_.end();
             ++it) {
            if (it->second->getDroppedPacketsNum() > 0) {
                return (true);
            }
        }
        return (false);
    }

    /// \brief Return specified counter.
    ///
    /// Method returns specified counter.
    ///
    /// \param counter_key key poiting to the counter in the counters map.
    /// The short counter name has to be used to access counter.
    /// \return pointer to specified counter object.
    CustomCounterPtr getCounter(const std::string& counter_key) {
        CustomCountersMapIterator it = custom_counters_.find(counter_key);
        if (it == custom_counters_.end()) {
            isc_throw(BadValue,
                      "Custom counter " << counter_key << "does not exist");
        }
        return(it->second);
    }

    /// \brief Increment specified counter.
    ///
    /// Increment counter value by one.
    ///
    /// \param counter_key key poiting to the counter in the counters map.
    /// \param value value to increment counter by.
    /// \return pointer to specified counter after incrementation.
    const CustomCounter& incrementCounter(const std::string& counter_key,
                                          const uint64_t value = 1) {
        CustomCounterPtr counter = getCounter(counter_key);
        *counter += value;
        return (*counter);
    }

    /// \brief Adds new packet to the sent packets list.
    ///
    /// Method adds new packet to the sent packets list.
    /// Packets are added to the list sequentially and
    /// most often read sequentially.
    ///
    /// \param xchg_type exchange type.
    /// \param packet packet to be added to the list
    /// \throw isc::BadValue if invalid exchange type specified or
    /// packet is null.
    void passSentPacket(const ExchangeType xchg_type,
                        const boost::shared_ptr<T>& packet) {
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
    /// \throw isc::BadValue if invalid exchange type specified
    /// or packet is null.
    /// \throw isc::Unexpected if corresponding packet was not
    /// found on the list of sent packets.
    boost::shared_ptr<T>
    passRcvdPacket(const ExchangeType xchg_type,
                   const boost::shared_ptr<T>& packet) {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        boost::shared_ptr<T> sent_packet
            = xchg_stats->matchPackets(packet);

        if (sent_packet) {
            xchg_stats->updateDelays(sent_packet, packet);
            if (archive_enabled_) {
                xchg_stats->appendRcvd(packet);
            }
        }
        return(sent_packet);
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
        return(xchg_stats->getMinDelay());
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
        return(xchg_stats->getMaxDelay());
    }

    /// \brief Return average packet delay.
    ///
    /// Method returns average packet delay for specified
    /// exchange type.
    ///
    /// \return average packet delay.
    double getAvgDelay(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return(xchg_stats->getAvgDelay());
    }

    /// \brief Return standard deviation of packet delay.
    ///
    /// Method returns standard deviation of packet delay
    /// for specified exchange type.
    ///
    /// \return standard deviation of packet delay.
    double getStdDevDelay(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return(xchg_stats->getStdDevDelay());
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
        return(xchg_stats->getOrphans());
    }

    /// \brief Return average unordered lookup set size.
    ///
    /// Method returns average unordered lookup set size.
    /// This value changes every time \ref ExchangeStats::matchPackets
    /// function performs unordered packet lookup.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return average unordered lookup set size.
    double getAvgUnorderedLookupSetSize(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return(xchg_stats->getAvgUnorderedLookupSetSize());
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
        return(xchg_stats->getUnorderedLookups());
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
        return(xchg_stats->getOrderedLookups());
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
        return(xchg_stats->getSentPacketsNum());
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
        return(xchg_stats->getRcvdPacketsNum());
    }

    /// \brief Return total number of dropped packets.
    ///
    /// Method returns total number of dropped packets for specified
    /// exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of dropped packets.
    uint64_t getDroppedPacketsNum(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return(xchg_stats->getDroppedPacketsNum());
    }

    /// \brief Return number of garbage collected packets.
    ///
    /// Method returns number of garbage collected timed out
    /// packets. Packet is assumed timed out when duration
    /// between sending it to server and receiving server's
    /// response is greater than value specified with -d<value>
    /// command line argument.
    ///
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of garbage collected packets.
    uint64_t getCollectedNum(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return(xchg_stats->getCollectedNum());
    }


    /// \brief Get time period since the start of test.
    ///
    /// Calculate dna return period since the test start. This
    /// can be specifically helpful when calculating packet
    /// exchange rates.
    ///
    /// \return test period so far.
    boost::posix_time::time_period getTestPeriod() const {
        using namespace boost::posix_time;
        time_period test_period(boot_time_,
                                microsec_clock::universal_time());
        return test_period;
    }

    /// \brief Return name of the exchange.
    ///
    /// Method returns name of the specified exchange type.
    /// This function is mainly for logging purposes.
    ///
    /// \param xchg_type exchange type.
    /// \return string representing name of the exchange.
    static std::string exchangeToString(ExchangeType xchg_type) {
        switch(xchg_type) {
        case XCHG_DO:
            return("DISCOVER-OFFER");
        case XCHG_RA:
            return("REQUEST-ACK");
        case XCHG_SA:
            return("SOLICIT-ADVERTISE");
        case XCHG_RR:
            return("REQUEST-REPLY");
        case XCHG_RN:
            return("RENEW-REPLY");
        case XCHG_RL:
            return("RELEASE-REPLY");
        default:
            return("Unknown exchange type");
        }
    }

   /// \brief Print statistics counters for all exchange types.
    ///
    /// Method prints statistics for all exchange types.
    /// Statistics includes:
    /// - number of sent and received packets
    /// - number of dropped packets and number of orphans
    /// - minimum packets delay,
    /// - average packets delay,
    /// - maximum packets delay,
    /// - standard deviation of packets delay.
    ///
    /// \throw isc::InvalidOperation if no exchange type added to
    /// track statistics.
     void printStats() const {
        if (exchanges_.empty()) {
            isc_throw(isc::InvalidOperation,
                      "no exchange type added for tracking");
        }
        for (ExchangesMapIterator it = exchanges_.begin();
             it != exchanges_.end();
             ++it) {
            ExchangeStatsPtr xchg_stats = it->second;
            std::cout << "***Statistics for: " << exchangeToString(it->first)
                      << "***" << std::endl;
            xchg_stats->printMainStats();
            std::cout << std::endl;
            xchg_stats->printRTTStats();
            std::cout << std::endl;
        }
    }

    /// \brief Print intermediate statistics.
    ///
    /// Method prints intermediate statistics for all exchanges.
    /// Statistics includes sent, received and dropped packets
    /// counters.
    void printIntermediateStats() const {
        std::ostringstream stream_sent;
        std::ostringstream stream_rcvd;
        std::ostringstream stream_drops;
        std::string sep("");
        for (ExchangesMapIterator it = exchanges_.begin();
             it != exchanges_.end(); ++it) {

            if (it != exchanges_.begin()) {
                sep = "/";
            }
            stream_sent << sep << it->second->getSentPacketsNum();
            stream_rcvd << sep << it->second->getRcvdPacketsNum();
            stream_drops << sep << it->second->getDroppedPacketsNum();
        }
        std::cout << "sent: " << stream_sent.str()
                  << "; received: " << stream_rcvd.str()
                  << "; drops: " << stream_drops.str()
                  << std::endl;
    }

    /// \brief Print timestamps of all packets.
    ///
    /// Method prints timestamps of all sent and received
    /// packets for all defined exchange types.
    ///
    /// \throw isc::InvalidOperation if one of the packets has
    /// no timestamp value set or if packets archive mode is
    /// disabled.
    ///
    /// \throw isc::InvalidOperation if no exchange type added to
    /// track statistics or packets archive mode is disabled.
    void printTimestamps() const {
        if (exchanges_.empty()) {
            isc_throw(isc::InvalidOperation,
                      "no exchange type added for tracking");
        }
        for (ExchangesMapIterator it = exchanges_.begin();
             it != exchanges_.end();
             ++it) {
            ExchangeStatsPtr xchg_stats = it->second;
            std::cout << "***Timestamps for packets: "
                      << exchangeToString(it->first)
                      << "***" << std::endl;
            xchg_stats->printTimestamps();
            std::cout << std::endl;
        }
    }

    /// \brief Print names and values of custom counters.
    ///
    /// Method prints names and values of custom counters. Custom counters
    /// are defined by client class for tracking different statistics.
    ///
    /// \throw isc::InvalidOperation if no custom counters added for tracking.
    void printCustomCounters() const {
        if (custom_counters_.empty()) {
            isc_throw(isc::InvalidOperation, "no custom counters specified");
        }
        for (CustomCountersMapIterator it = custom_counters_.begin();
             it != custom_counters_.end();
             ++it) {
            CustomCounterPtr counter = it->second;
            std::cout << counter->getName() << ": " << counter->getValue()
                      << std::endl;
        }
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
        return(xchg_stats);
    }

    ExchangesMap exchanges_;            ///< Map of exchange types.
    CustomCountersMap custom_counters_; ///< Map with custom counters.

    /// Indicates that packets from list of sent packets should be
    /// archived (moved to list of archived packets) once they are
    /// matched with received packets. This is required when it has
    /// been selected from the command line to print packets'
    /// timestamps after test. This may affect performance and
    /// consume large amount of memory when the test is running
    /// for extended period of time and many packets have to be
    /// archived.
    bool archive_enabled_;

    boost::posix_time::ptime boot_time_; ///< Time when test is started.
};

} // namespace perfdhcp
} // namespace isc

#endif // STATS_MGR_H
