// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STATS_MGR_H
#define STATS_MGR_H

#include <dhcp/pkt.h>
#include <exceptions/exceptions.h>
#include <perfdhcp/command_options.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>
#include <map>
#include <queue>


namespace isc {
namespace perfdhcp {

/// DHCP packet exchange types.
enum class ExchangeType {
    DO,  ///< DHCPv4 DISCOVER-OFFER
    RA,  ///< DHCPv4 REQUEST-ACK
    RNA, ///< DHCPv4 REQUEST-ACK (renewal)
    RLA, ///< DHCPv4 RELEASE
    SA,  ///< DHCPv6 SOLICIT-ADVERTISE
    RR,  ///< DHCPv6 REQUEST-REPLY
    RN,  ///< DHCPv6 RENEW-REPLY
    RL   ///< DHCPv6 RELEASE-REPLY
};

/// \brief Get the DHCP version that fits the exchange type.
///
/// \param exchange_type exchange type that will determine the version
/// \throw isc::BadValue exchange type is unrecognized
/// \return DHCP version: 4 or 6
int dhcpVersion(ExchangeType const exchange_type);

/// \brief Return name of the exchange.
///
/// Function returns name of the specified exchange type.
/// This function is mainly for logging purposes.
///
/// \param os output stream to use.
/// \param xchg_type exchange type.
/// \return string representing name of the exchange.
std::ostream& operator<<(std::ostream& os, ExchangeType xchg_type);

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
        name_(name) {
    }

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
    uint64_t getValue() const {
        return (counter_);
    }

    /// \brief Return counter name.
    ///
    /// Method returns counter name.
    ///
    /// \return counter name.
    const std::string& getName() const {
        return (name_);
    }

private:
    /// \brief Default constructor.
    ///
    /// Default constructor is private because we don't want client
    /// class to call it because we want client class to specify
    /// counter's name.
    CustomCounter() : counter_(0) {
    }

    uint64_t counter_;  ///< Counter's value.
    std::string name_;  ///< Counter's name.
};

typedef typename boost::shared_ptr<CustomCounter> CustomCounterPtr;

/// Map containing custom counters.
typedef typename std::map<std::string, CustomCounterPtr> CustomCountersMap;

/// Iterator for \ref CustomCountersMap.
typedef typename CustomCountersMap::const_iterator CustomCountersMapIterator;


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
    static uint32_t hashTransid(const dhcp::PktPtr& packet) {
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
    /// search within a range to find a packet with particular transaction
    /// id will not be intensive.
    ///
    /// Example 1: Add elements to the list
    /// \code
    /// PktList packets_collection();
    /// boost::shared_ptr<Pkt4> pkt1(new Pkt4(...));
    /// boost::shared_ptr<Pkt4> pkt2(new Pkt4(...));
    /// // Add new packet to the container, it will be available through
    /// // both indexes
    /// static_cast<void>(packets_collection.push_back(pkt1));
    /// // Here is another way to add packet to the container. The result
    /// // is exactly the same as previously.
    /// static_cast<void>(packets_collection.template get<0>().push_back(pkt2));
    /// \endcode
    ///
    /// @note The multi index has no unique index so insertion should never
    /// fail and there is no need to check the return of push_back().
    ///
    /// Example 2: Access elements through sequential index
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
    /// Example 3: Access elements through ordered index by hash
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
        // Container holds PktPtr objects.
        dhcp::PktPtr,
        // List container indexes.
        boost::multi_index::indexed_by<
            // Sequenced index provides the way to use this container
            // in the same way as std::list.
            boost::multi_index::sequenced<>,
            // The other index keeps products of transaction id.
            // Elements with the same hash value are grouped together
            // into buckets and transactions are ordered from the
            // oldest to latest within a bucket.
            boost::multi_index::ordered_non_unique<
                // Specify hash function to get the product of
                // transaction id. This product is obtained by calling
                // hashTransid() function.
                boost::multi_index::global_fun<
                    // Hashing function takes PktPtr as argument.
                    const dhcp::PktPtr&,
                    // ... and returns uint32 value.
                    uint32_t,
                    // ... and here is a reference to it.
                    &ExchangeStats::hashTransid
                    >
                >
            >
        > PktList;

    /// Packet list iterator for sequential access to elements.
    typedef typename PktList::iterator PktListIterator;
    /// Packet list index to search packets using transaction id hash.
    typedef typename PktList::template nth_index<1>::type
    PktListTransidHashIndex;
    /// Packet list iterator to access packets using transaction id hash.
    typedef typename PktListTransidHashIndex::const_iterator
    PktListTransidHashIterator;
    /// Packet list iterator queue for removal.
    typedef typename std::queue<PktListTransidHashIterator>
    PktListRemovalQueue;

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
                  const boost::posix_time::ptime boot_time);

    /// \brief Add new packet to list of sent packets.
    ///
    /// Method adds new packet to list of sent packets.
    ///
    /// \param packet packet object to be added.
    /// \throw isc::BadValue if packet is null.
    void appendSent(const dhcp::PktPtr& packet) {
        if (!packet) {
            isc_throw(BadValue, "Packet is null");
        }
        static_cast<void>(sent_packets_.template get<0>().push_back(packet));
        ++sent_packets_num_;
    }

    /// \brief Add new packet to list of received packets.
    ///
    /// Method adds new packet to list of received packets.
    ///
    /// \param packet packet object to be added.
    /// \throw isc::BadValue if packet is null.
    void appendRcvd(const dhcp::PktPtr& packet) {
        if (!packet) {
            isc_throw(BadValue, "Packet is null");
        }
        static_cast<void>(rcvd_packets_.push_back(packet));
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
    void updateDelays(const dhcp::PktPtr& sent_packet,
                      const dhcp::PktPtr& rcvd_packet);

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
    dhcp::PktPtr matchPackets(const dhcp::PktPtr& rcvd_packet);

    /// \brief Return minimum delay between sent and received packet.
    ///
    /// Method returns minimum delay between sent and received packet.
    ///
    /// \return minimum delay between packets.
    double getMinDelay() const { return(min_delay_); }

    /// \brief Return maximum delay between sent and received packet.
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

    /// \brief Return number of orphan packets.
    ///
    /// Method returns number of received packets that had no matching
    /// sent packet. It is possible that such packet was late or not
    /// for us.
    ///
    /// \return number of orphan received packets.
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

    /// \brief Return number of unordered sent packets lookups.
    ///
    /// Method returns number of unordered sent packet lookups.
    /// Unordered lookup is used when received packet was sent
    /// out of order by server - transaction id of received
    /// packet does not match transaction id of next sent packet.
    ///
    /// \return number of unordered lookups.
    uint64_t getUnorderedLookups() const { return(unordered_lookups_); }

    /// \brief Return number of ordered sent packets lookups.
    ///
    /// Method returns number of ordered sent packet lookups.
    /// Ordered lookup is used when packets are received in the
    /// same order as they were sent to the server.
    /// If packets are skipped or received out of order, lookup
    /// function will use unordered lookup (with hash table).
    ///
    /// \return number of ordered lookups.
    uint64_t getOrderedLookups() const { return(ordered_lookups_); }

    /// \brief Return total number of sent packets.
    ///
    /// Method returns total number of sent packets.
    ///
    /// \return number of sent packets.
    uint64_t getSentPacketsNum() const { return(sent_packets_num_); }

    /// \brief Return total number of received packets.
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

    /// \brief Return total number of rejected leases.
    ///
    /// Method returns total number of rejected leases.
    ///
    /// \return number of rejected leases.
    uint64_t getRejLeasesNum() const { return(rejected_leases_num_); }

    /// \brief Return total number of non unique addresses.
    ///
    /// Method returns total number of non unique addresses.
    ///
    /// \return number of non unique addresses.
    uint64_t getNonUniqueAddrNum() const { return(non_unique_addr_num_); }

    /// \brief Increase number of rejected leases.
    ///
    /// Method increases total number of rejected leases by one.
    void updateRejLeases() { ++rejected_leases_num_; }

    /// \brief Increase number of non unique addresses.
    ///
    /// Method increases total number of non unique addresses by one.
    void updateNonUniqueAddr() { ++non_unique_addr_num_; }

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
    /// not identified as a response to any of the messages sent by
    /// perfdhcp.
    void printMainStats() const {
        using namespace std;
        auto sent = getSentPacketsNum();
        auto drops = getDroppedPacketsNum();
        double drops_ratio = 100.0 * static_cast<double>(drops) / static_cast<double>(sent);

        cout << "sent packets: " << sent << endl
             << "received packets: " << getRcvdPacketsNum() << endl
             << "drops: " << drops << endl
             << "drops ratio: " << drops_ratio << " %" << endl
             << "orphans: " << getOrphans() << endl
             << "rejected leases: " << getRejLeasesNum() << endl
             << "non unique addresses: " << getNonUniqueAddrNum() << endl;
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
            // repeated output for easier automated parsing
            cout << "min delay: n/a" << endl
                 << "avg delay: n/a" << endl
                 << "max delay: n/a" << endl
                 << "std deviation: n/a" << endl
                 << "collected packets: 0" << endl;
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
    void printTimestamps();

    std::tuple<PktListIterator, PktListIterator> getSentPackets() {
        return(std::make_tuple(sent_packets_.begin(), sent_packets_.end()));
    }

    /// \brief Return the list of received leases in CSV format as string.
    ///
    /// Depending exchange type, it can apply to
    /// potential leases received in offers and advertisements,
    /// committed leases received in acknowledgements and replies,
    /// renewed or released leases.
    ///
    /// \return multiline string of received leases in CSV format
    std::string receivedLeases() const;

    /// \brief Print the list of received leases.
    void printLeases() const;

    static int malformed_pkts_;

// Private stuff of ExchangeStats class
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
            static_cast<void>(archived_packets_.push_back(*it));
        }
        // get<0>() template returns sequential index to
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

    /// Maximum time elapsed between sending and receiving packet
    /// before packet is assumed dropped.
    double drop_time_;

    double min_delay_;             ///< Minimum delay between sent
                                   ///< and received packets.
    double max_delay_;             ///< Maximum delay between sent
                                   ///< and received packets.
    double sum_delay_;             ///< Sum of delays between sent
                                   ///< and received packets.
    double sum_delay_squared_;     ///< Squared sum of delays between
                                   ///< sent and received packets.

    uint64_t orphans_;   ///< Number of orphan received packets.

    uint64_t collected_; ///< Number of garbage collected packets.

    /// Sum of unordered lookup sets. Needed to calculate mean size of
    /// lookup set. It is desired that number of unordered lookups is
    /// minimal for performance reasons. Tracking number of lookups and
    /// mean size of the lookup set should give idea of packets search
    /// complexity.
    uint64_t unordered_lookup_size_sum_;

    uint64_t unordered_lookups_;   ///< Number of unordered sent packets
                                   ///< lookups.
    uint64_t ordered_lookups_;     ///< Number of ordered sent packets
                                   ///< lookups.

    uint64_t sent_packets_num_;    ///< Total number of sent packets.
    uint64_t rcvd_packets_num_;    ///< Total number of received packets.

    uint64_t non_unique_addr_num_; ///< Total number of non unique addresses
                                   ///< offered/advertised.
    uint64_t rejected_leases_num_; ///< Total number of rejected leases
                                   /// (e.g. NoAddrAvail)
    boost::posix_time::ptime boot_time_; ///< Time when test is started.
};

/// Pointer to ExchangeStats.
typedef boost::shared_ptr<ExchangeStats> ExchangeStatsPtr;

/// Map containing all specified exchange types.
typedef typename std::map<ExchangeType, ExchangeStatsPtr> ExchangesMap;

/// Iterator pointing to \ref ExchangesMap.
typedef typename ExchangesMap::const_iterator ExchangesMapIterator;


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
class StatsMgr : public boost::noncopyable {
public:
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
    StatsMgr(CommandOptions& options);

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
    /// \param xchg_type A type of the exchange being represented by the
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

    /// \brief Check if any packet drops occurred.
    ///
    // \return true, if packet drops occurred.
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
    /// \param counter_key key pointing to the counter in the counters map.
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
    /// \param counter_key key pointing to the counter in the counters map.
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
                        const dhcp::PktPtr& packet) {
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
    dhcp::PktPtr
    passRcvdPacket(const ExchangeType xchg_type,
                   const dhcp::PktPtr& packet) {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        dhcp::PktPtr sent_packet = xchg_stats->matchPackets(packet);

        if (sent_packet) {
            xchg_stats->updateDelays(sent_packet, packet);
            if (archive_enabled_) {
                xchg_stats->appendRcvd(packet);
            }
        }
        return(sent_packet);
    }

    /// \brief Return minimum delay between sent and received packet.
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

    /// \brief Return maximum delay between sent and received packet.
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

    /// \brief Return number of orphan packets.
    ///
    /// Method returns number of orphan packets for specified
    /// exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of orphan packets so far.
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

    /// \brief Return number of unordered sent packets lookups.
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

    /// \brief Return number of ordered sent packets lookups.
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

    /// \brief Return total number of sent packets.
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

    /// \brief Return total number of received packets.
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

    /// \brief Return total number of rejected leases.
    ///
    /// Method returns total number of rejected leases for specified
    /// exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of rejected leases.
    uint64_t getRejLeasesNum(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return(xchg_stats->getRejLeasesNum());
    }

    /// \brief Increase total number of rejected leases.
    ///
    /// Method increases total number of rejected leases by one
    /// for specified exchange type.
    void updateRejLeases(const ExchangeType xchg_type) {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        xchg_stats->updateRejLeases();
    }

    /// \brief Increase total number of non unique addresses.
    ///
    /// Method increases total number of non unique addresses or
    /// prefixes by one for specified exchange type.
    void updateNonUniqueAddrNum(const ExchangeType xchg_type) {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        xchg_stats->updateNonUniqueAddr();
    }

    /// \brief Return total number of non unique addresses.
    ///
    /// Method returns total number of non unique addresses and/or
    /// prefixes for specified exchange type.
    ///
    /// \param xchg_type exchange type.
    /// \throw isc::BadValue if invalid exchange type specified.
    /// \return number of non unique addresses.
    uint64_t getNonUniqueAddrNum(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        return(xchg_stats->getNonUniqueAddrNum());
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
            std::cout << "***Statistics for: " << it->first
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
    ///
    /// \param clean_report value to generate easy to parse report.
    /// \param clean_sep string used as separator if clean_report enabled..
    void
    printIntermediateStats(bool clean_report, std::string clean_sep) const {
        std::ostringstream stream_sent;
        std::ostringstream stream_rcvd;
        std::ostringstream stream_drops;
        std::ostringstream stream_reject;
        std::string sep("");
        for (ExchangesMapIterator it = exchanges_.begin();
             it != exchanges_.end(); ++it) {

            if (it != exchanges_.begin()) {
                if (clean_report) {
                    sep = clean_sep;
                } else {
                    sep = "/";
                }
            }
            stream_sent << sep << it->second->getSentPacketsNum();
            stream_rcvd << sep << it->second->getRcvdPacketsNum();
            stream_drops << sep << it->second->getDroppedPacketsNum();
            stream_reject << sep << it->second->getRejLeasesNum();
        }

        if (clean_report) {
        std::cout << stream_sent.str()
                  << clean_sep << stream_rcvd.str()
                  << clean_sep << stream_drops.str()
                  << clean_sep << stream_reject.str()
                  << std::endl;

        } else {
        std::cout << "sent: " << stream_sent.str()
                  << "; received: " << stream_rcvd.str()
                  << "; drops: " << stream_drops.str()
                  << "; rejected: " << stream_reject.str()
                  << std::endl;
        }
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
                      << it->first
                      << "***" << std::endl;
            xchg_stats->printTimestamps();
            std::cout << std::endl;
        }
    }

    /// \brief Delegate to all exchanges to print their leases.
    void printLeases() const;

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

    std::tuple<typename ExchangeStats::PktListIterator, typename ExchangeStats::PktListIterator> getSentPackets(const ExchangeType xchg_type) const {
        ExchangeStatsPtr xchg_stats = getExchangeStats(xchg_type);
        std::tuple<typename ExchangeStats::PktListIterator, typename ExchangeStats::PktListIterator> sent_packets_its = xchg_stats->getSentPackets();
        return(sent_packets_its);
    }

private:

    /// \brief Return exchange stats object for given exchange type.
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

/// Pointer to Statistics Manager;
typedef boost::shared_ptr<StatsMgr> StatsMgrPtr;


} // namespace perfdhcp
} // namespace isc

#endif // STATS_MGR_H
