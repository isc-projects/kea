// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BULK_LEASE_QUERY_H
#define BULK_LEASE_QUERY_H

#include <config.h>

#include <blq_msg.h>
#include <boost/enable_shared_from_this.hpp>
#include <functional>

namespace isc {
namespace lease_query {

/// @brief Type of BLQ post callback argument..
typedef std::function<void ()> BlqPostCbArg;

/// @brief Type of BLQ post callback.
typedef std::function<void (const BlqPostCbArg&)> BlqPostCb;

/// @brief Type of BLQ pushToSend callback.
typedef std::function<bool (BlqResponsePtr)> BlqPushToSendCb;

/// @brief Type of BLQ queryComplete callback.
typedef std::function<void (Xid)> BlqQueryCompleteCb;

/// @brief Forward declaration of BulkLeaseQuery class.
class BulkLeaseQuery;

/// @brief Defines a shared pointer to a BulkLeaseQuery object.
typedef boost::shared_ptr<BulkLeaseQuery> BulkLeaseQueryPtr;

/// @brief Base class for providing control flow for processing a bulk query.
class BulkLeaseQuery : public boost::enable_shared_from_this<BulkLeaseQuery> {
public:

    /// @brief Constructor.
    ///
    /// @param query The query.
    /// @param post The post callback.
    /// @param push_to_send The pushToSend callback.
    /// @param query_complete The queryComplete callback.
    /// @throw BadValue if the query is invalid for a number reasons.
    BulkLeaseQuery(BlqQueryPtr query,
                   const BlqPostCb& post,
                   const BlqPushToSendCb& push_to_send,
                   const BlqQueryCompleteCb& query_complete)
        : query_(query), post_(post), push_to_send_(push_to_send),
          query_complete_(query_complete), started_(false), done_(false) {
        if (!query) {
            isc_throw(BadValue, "BulkLeaseQuery query is null");
        }
    }

    /// @brief Destructor.
    virtual ~BulkLeaseQuery() {
    }

    /// @brief Initialization.
    ///
    /// Check the query and fill processing context fields.
    ///
    /// @throw BadValue if the query is invalid for a number reasons.
    virtual void init() = 0;

    /// @brief Start processing.
    virtual void start() = 0;

    /// @brief Class/static start processing.
    ///
    /// @param ptr Pointer to a BulkLeaseQuery object (must not be null).
    static void processStart(BulkLeaseQueryPtr ptr) {
        if (!ptr) {
            // Should not happen.
            return;
        }
        ptr->start();
    }

    /// @brief Processing in progress predicate.
    ///
    /// @return True when query processing is in progress, false
    /// when not yet started.
    bool isProcessing() const {
        return (started_);
    }

    /// @brief Processing finished predicate.
    ///
    /// @return True when query processing finished.
    bool isProcessed() const {
        return (done_);
    }

    /// @brief Get the query.
    ///
    /// @return The query.
    BlqQueryPtr getQuery() {
        return (query_);
    }

    /// @brief Get the query type.
    ///
    /// @return The query type.
    uint8_t getQueryType() const {
        return (query_type_);
    }

    /// @brief Get the transaction id of the query.
    ///
    /// @return The transaction id of the query.
    Xid getXid() const {
        return (query_->getXid());
    }

protected:
    /// @brief Set the done flag.
    virtual void setDone() {
        done_ = true;
        query_complete_(query_->getXid());
    }

    /// @brief The query.
    BlqQueryPtr query_;

    /// @brief The post callback.
    BlqPostCb post_;

    /// @brief The pushToSend callback.
    BlqPushToSendCb push_to_send_;

    /// @brief The queryComplete callback.
    BlqQueryCompleteCb query_complete_;

    /// @brief The query type.
    uint8_t query_type_;

    /// @brief The processing is in progress.
    bool started_;

    /// @brief The processing finished.
    bool done_;
};

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // BULK_LEASE_QUERY_H
