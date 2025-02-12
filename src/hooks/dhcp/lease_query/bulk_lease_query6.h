// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BULK_LEASE_QUERY6_H
#define BULK_LEASE_QUERY6_H

#include <config.h>

#include <lease_query_impl.h>
#include <bulk_lease_query.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcpsrv/subnet_id.h>

namespace isc {
namespace lease_query {

/// @brief Forward declaration of BulkLeaseQuery6 class.
class BulkLeaseQuery6;

/// @brief Defines a shared pointer to a BulkLeaseQuery6 object.
typedef boost::shared_ptr<BulkLeaseQuery6> BulkLeaseQuery6Ptr;

/// @brief Provides control flow for processing a bulk query.
class BulkLeaseQuery6 : public BulkLeaseQuery {
public:

    /// @brief Constructor.
    ///
    /// @param query The query.
    /// @param post The post callback.
    /// @param push_to_send The pushToSend callback.
    /// @param query_complete The queryComplete callback.
    /// @throw BadValue if the query is invalid for a number reasons.
    BulkLeaseQuery6(BlqQueryPtr query,
                    const BlqPostCb& post,
                    const BlqPushToSendCb& push_to_send,
                    const BlqQueryCompleteCb& query_complete)
        : BulkLeaseQuery(query, post, push_to_send, query_complete),
          query6_(),
          link_addr_(asiolink::IOAddress::IPV6_ZERO_ADDRESS()), links_(),
          start_addr_(asiolink::IOAddress::IPV6_ZERO_ADDRESS()),
          page_size_(10),
          lq_option_(), query_iaaddr_(), query_client_id_(),
          query_relay_id_(), query_remote_id_() {
        init();
    }

    /// @brief Destructor.
    virtual ~BulkLeaseQuery6() {
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

    /// @brief Get the DHCPv6 query.
    dhcp::Pkt6Ptr getQuery6() const {
        return (query6_);
    }

    /// @brief Get the link address.
    const asiolink::IOAddress& getLinkAddress() const {
        return (link_addr_);
    }

    /// @brief Get the links set.
    const dhcp::SubnetIDSet& links() const {
        return (links_);
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
    /// @brief Start processing of a by ip address bulk query.
    void bulkQueryByIpAddress();

    /// @brief Start processing of a by client id bulk query.
    void bulkQueryByClientId();

    /// @brief Start processing of a by relay id bulk query.
    void bulkQueryByRelayId();

    /// @brief Start processing of a by remote id bulk query.
    void bulkQueryByRemoteId();

    /// @brief Start processing of a by link address bulk query.
    void bulkQueryByLinkAddress();

    /// @brief Subsequent processing of a by relay id bulk query.
    void bulkQueryByRelayIdNext();

    /// @brief Class/static subsequent processing of a by relay id bulk query.
    ///
    /// @param ptr Pointer to a BulkLeaseQuery6 object (must not be null).
    static void doBulkQueryByRelayIdNext(BulkLeaseQuery6Ptr ptr) {
        if (!ptr) {
            // Should not happen.
            return;
        }
        ptr->bulkQueryByRelayIdNext();
    }

    /// @brief Subsequent processing of a by remote id bulk query.
    void bulkQueryByRemoteIdNext();

    /// @brief Class/static subsequent processing of a by remote id bulk query.
    ///
    /// @param ptr Pointer to a BulkLeaseQuery6 object (must not be null).
    static void doBulkQueryByRemoteIdNext(BulkLeaseQuery6Ptr ptr) {
        if (!ptr) {
            // Should not happen.
            return;
        }
        ptr->bulkQueryByRemoteIdNext();
    }

    /// @brief Subsequent processing of a by link address bulk query.
    void bulkQueryByLinkAddressNext();

    /// @brief Class/static subsequent processing of a by link address bulk query.
    ///
    /// @param ptr Pointer to a BulkLeaseQuery6 object (must not be null).
    static void doBulkQueryByLinkAddressNext(BulkLeaseQuery6Ptr ptr) {
        if (!ptr) {
            // Should not happen.
            return;
        }
        ptr->bulkQueryByLinkAddressNext();
    }

    /// @brief Send a response.
    ///
    /// @param response The response packet.
    virtual void send(dhcp::Pkt6Ptr response) const;

    /// @brief Send a final reply.
    ///
    /// @param status The status code option.
    virtual void sendReply(dhcp::OptionPtr status);

    /// @brief Get the lease query option.
    dhcp::OptionCustomPtr getLeaseQueryOption() const {
        return (lq_option_);
    }

    /// @brief Get the query ip address for a by ip address bulk query.
    ///
    /// @return The query ip address for a by ip address bulk query or null.
    dhcp::Option6IAAddrPtr getQueryIpAddress() const {
        return (query_iaaddr_);
    }

    /// @brief Get the query client id for a by client id bulk query.
    ///
    /// @return The query client id for a by client id bulk query or null.
    dhcp::DuidPtr getQueryClientId() const {
        return (query_client_id_);
    }

    /// @brief Get the query relay id for a by relay id bulk query.
    ///
    /// @return The query relay id for a by relay id bulk query or null.
    dhcp::DuidPtr getQueryRelayId() const {
        return (query_relay_id_);
    }

    /// @brief Get the query remote id for a by remote id bulk query.
    ///
    /// @return The remote id for a by remote id bulk query or null.
    dhcp::OptionPtr getQueryRemoteId() const {
        return (query_remote_id_);
    }

    /// @brief The DHCPv6 query.
    dhcp::Pkt6Ptr query6_;

    /// @brief The link address.
    asiolink::IOAddress link_addr_;

    /// @brief The links the link address (when not ::) belongs to.
    dhcp::SubnetIDSet links_;

    /// @brief The start address (for paged processing).
    asiolink::IOAddress start_addr_;

    /// @brief The page size (for paged processing, taken from the MT Lease
    /// query manager or defaults to 10).
    size_t page_size_;

    /// @brief The lease query option.
    dhcp::OptionCustomPtr lq_option_;

    /// @brief The query ip address (for a by ip address bulk query).
    dhcp::Option6IAAddrPtr query_iaaddr_;

    /// @brief The query client id (for a by client id bulk query).
    dhcp::DuidPtr query_client_id_;

    /// @brief The query relay id (for a by relay id bulk query).
    dhcp::DuidPtr query_relay_id_;

    /// @brief The remote id (for a by remote id bulk query).
    dhcp::OptionPtr query_remote_id_;
};

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // BULK_LEASE_QUERY6_H
