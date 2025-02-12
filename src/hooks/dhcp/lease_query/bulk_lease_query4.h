// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BULK_LEASE_QUERY4_H
#define BULK_LEASE_QUERY4_H

#include <config.h>

#include <lease_query_impl.h>
#include <bulk_lease_query.h>
#include <dhcp/dhcp4.h>
#include <dhcpsrv/lease.h>

namespace isc {
namespace lease_query {

/// @brief Status Codes.
enum BLQStatusCode {
    BLQ_STATUS_Success          = 0,
    BLQ_STATUS_UnspecFail       = 1,
    BLQ_STATUS_QueryTerminated  = 2,
    BLQ_STATUS_MalformedQuery   = 3,
    BLQ_STATUS_NotAllowed       = 4
};

/// @brief Return the name of the status code.
std::string getStatusCodeName(BLQStatusCode status);

/// @brief States.
enum BLQStates {
    BLQ_STATE_AVAILABLE      = 1,
    BLQ_STATE_ACTIVE         = 2,
    BLQ_STATE_EXPIRED        = 3,
    BLQ_STATE_RELEASED       = 4,
    BLQ_STATE_ABANDONED      = 5,
    BLQ_STATE_RESET          = 6,
    BLQ_STATE_REMOTE         = 7,
    BLQ_STATE_TRANSITIONING  = 8
};

/// @brief Return the name of the state.
std::string getStateName(BLQStates state);

/// @brief Virtual Subnet Selection Option code point (RFC 6607 and 6926).
#ifndef DHO_VSS
#define DHO_VSS 221
#endif

/// @brief Forward declaration of BulkLeaseQuery4 class.
class BulkLeaseQuery4;

/// @brief Defines a shared pointer to a BulkLeaseQuery4 object.
typedef boost::shared_ptr<BulkLeaseQuery4> BulkLeaseQuery4Ptr;

/// @brief Provides control flow for processing a bulk query.
class BulkLeaseQuery4 : public BulkLeaseQuery {
public:

    /// @brief Constructor.
    ///
    /// @param query The query.
    /// @param post The post callback.
    /// @param push_to_send The pushToSend callback.
    /// @param query_complete The queryComplete callback.
    /// @throw BadValue if the query is invalid for a number reasons.
    BulkLeaseQuery4(BlqQueryPtr query,
                    const BlqPostCb& post,
                    const BlqPushToSendCb& push_to_send,
                    const BlqQueryCompleteCb& query_complete)
        : BulkLeaseQuery(query, post, push_to_send, query_complete),
          query4_(),
          start_addr_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
          page_size_(10),
          query_mask_(0),
          query_client_id_(), query_hwaddr_(),
          query_relay_id_(), query_remote_id_(),
          query_start_time_(0), query_end_time_(0),
          sent_(0) {
        init();
    }

    /// @brief Destructor.
    virtual ~BulkLeaseQuery4() {
    }

    /// @brief Convenience method for generating per packet logging info.
    ///
    /// @param msg Lease query message.
    static std::string leaseQueryLabel(const BlqMsgPtr& msg);

    /// @brief Initialization.
    ///
    /// Check the query and fill processing context fields.
    ///
    /// @throw BadValue if the query is invalid for a number reasons.
    virtual void init();

    /// @brief Start processing.
    virtual void start();

    /// @brief Get the DHCPv4 query.
    dhcp::Pkt4Ptr getQuery4() const {
        return (query4_);
    }

    /// @brief Get the current start address.
    asiolink::IOAddress getStartAddress() const {
        return (start_addr_);
    }

    /// @brief Get the page size.
    size_t getPageSize() const {
        return (page_size_);
    }

protected:
    /// @brief Start processing of a by client id bulk query.
    void bulkQueryByClientId();

    /// @brief Start processing of a by harware address bulk query.
    void bulkQueryByHWAddr();

    /// @brief Start processing of a by relay id bulk query.
    void bulkQueryByRelayId();

    /// @brief Start processing of a by remote id bulk query.
    void bulkQueryByRemoteId();

    /// @brief Class/static subsequent processing of a by relay id bulk query.
    ///
    /// @param ptr Pointer to a BulkLeaseQuery4 object (must not be null).
    static void doBulkQueryByRelayId(BulkLeaseQuery4Ptr ptr) {
        if (!ptr) {
            // Should not happen.
            return;
        }
        ptr->bulkQueryByRelayId();
    }

    /// @brief Class/static subsequent processing of a by remote id bulk query.
    ///
    /// @param ptr Pointer to a BulkLeaseQuery4 object (must not be null).
    static void doBulkQueryByRemoteId(BulkLeaseQuery4Ptr ptr) {
        if (!ptr) {
            // Should not happen.
            return;
        }
        ptr->bulkQueryByRemoteId();
    }

    /// @brief Send a response.
    ///
    /// @param response The response packet.
    virtual void send(dhcp::Pkt4Ptr response);

    /// @brief Send a DHCPLEASEQUERYDONE message.
    ///
    /// @param status The status code.
    /// @param message The optional message.
    virtual void sendDone(BLQStatusCode status,
                          const std::string& message = "");

    /// @brief Send a DHCPLEASEACTIVE message.
    ///
    /// @param lease The lease.
    virtual void sendActive(const dhcp::Lease4Ptr& lease);

    /// @brief Get the query mask.
    uint8_t getQueryMask() const {
        return (query_mask_);
    }

    /// @brief Get the query client id for a by client id bulk query.
    ///
    /// @return The query client id for a by client id bulk query or null.
    dhcp::OptionPtr getQueryClientId() const {
        return (query_client_id_);
    }

    /// @brief Get the query hardware address for a by hardware address bulk query.
    ///
    /// @return The query client id for a by client id bulk query or null.
    dhcp::HWAddrPtr getQueryHWAddr() const {
        return (query_hwaddr_);
    }

    /// @brief Get the query relay id for a by relay id bulk query.
    ///
    /// @return The query relay id for a by relay id bulk query or null.
    dhcp::OptionPtr getQueryRelayId() const {
        return (query_relay_id_);
    }

    /// @brief Get the query remote id for a by remote id bulk query.
    ///
    /// @return The remote id for a by remote id bulk query or null.
    dhcp::OptionPtr getQueryRemoteId() const {
        return (query_remote_id_);
    }

    /// @brief The DHCPv4 query.
    dhcp::Pkt4Ptr query4_;

    /// @brief The start address (for paged processing).
    asiolink::IOAddress start_addr_;

    /// @brief The page size (for paged processing, taken from the MT Lease
    /// query manager or defaults to 10).
    size_t page_size_;

    /// @brief The query mask.
    ///
    /// 1 - by client id
    /// 2 - by hardware address
    /// 4 - by relay id
    /// 8 - by remote id
    uint8_t query_mask_;

    /// @brief The query client id (for a by client id bulk query).
    dhcp::OptionPtr query_client_id_;

    /// @brief The query hardware address (for a by hardware address bulk query).
    dhcp::HWAddrPtr query_hwaddr_;

    /// @brief The query relay id (for a by relay id bulk query).
    dhcp::OptionPtr query_relay_id_;

    /// @brief The remote id (for a by remote id bulk query).
    dhcp::OptionPtr query_remote_id_;

    /// @brief The query start time.
    time_t query_start_time_;

    /// @brief The query end time.
    time_t query_end_time_;

    /// @brief Sent response counter.
    size_t sent_;
};

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // BULK_LEASE_QUERY4_H
