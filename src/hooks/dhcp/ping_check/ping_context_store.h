// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PING_CONTEXT_STORE_H
#define PING_CONTEXT_STORE_H

#include <asiolink/io_address.h>
#include <ping_context.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/scoped_ptr.hpp>

#include <mutex>
#include <vector>

namespace isc {
namespace ping_check {

/// @brief Exception thrown when an attempt was made to add a duplicate context
class DuplicateContext : public Exception {
public:
    DuplicateContext(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Tag for index by target address.
struct AddressIndexTag { };

/// @brief Tag for index by the query packet.
struct QueryIndexTag { };

/// @brief Tag for index by send wait start time.
struct NextToSendIndexTag { };

/// @brief Tag for index by expiration time.
struct ExpirationIndexTag { };

/// @brief A multi index container holding pointers to PingContexts.
///
/// The contexts in the container may be accessed using different indexes:
/// - using an IPv4 address,
/// - using a query packet
/// - using a send wait start time
/// - using an expiration time
/// - using a context state
///
/// Indexes can be accessed using the index number (from 0 to 2) or a
/// name tag. It is recommended to use the tags to access indexes as
/// they do not depend on the order of indexes in the container.
typedef boost::multi_index_container<
    // It holds pointers to Lease6 objects.
    PingContextPtr,
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts PingContexts by IPv4 addresses represented as
        // IOAddress objects.
        /// @todo Does it need to be ordered or only unique?
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<AddressIndexTag>,
            boost::multi_index::const_mem_fun<PingContext, const isc::asiolink::IOAddress&,
                                              &PingContext::getTarget>
        >,

        // Specification of the second index starts here.
        // This index sorts contexts by query.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<QueryIndexTag>,
            boost::multi_index::const_mem_fun<PingContext, isc::dhcp::Pkt4Ptr,
                                              &PingContext::getQuery>
        >,

        // Specification of the third index starts here.
        // This index sorts contexts by send_wait_start.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<NextToSendIndexTag>,
            boost::multi_index::composite_key<
                PingContext,
                // The boolean value specifying if context is waiting to send
                boost::multi_index::const_mem_fun<PingContext, bool,
                                                  &PingContext::isWaitingToSend>,
                // Context expiration time.
                boost::multi_index::const_mem_fun<PingContext, const TimeStamp&,
                                                  &PingContext::getSendWaitStart>
            >
        >,

        // Specification of the fourth index starts here.
        // This index sorts contexts by next_expiry.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<ExpirationIndexTag>,
            boost::multi_index::composite_key<
                PingContext,
                // The boolean value specifying if context is waiting for a reply
                boost::multi_index::const_mem_fun<PingContext, bool,
                                                  &PingContext::isWaitingForReply>,
                // Context expiration time.
                boost::multi_index::const_mem_fun<PingContext, const TimeStamp&,
                                                  &PingContext::getNextExpiry>
            >
        >
    >
> PingContextContainer;

/// @brief Type for a collection of PingContextPtrs.
typedef std::vector<PingContextPtr> PingContextCollection;
/// @brief Type for a pointer to a collection of PingContextPtrs.
typedef boost::shared_ptr<PingContextCollection> PingContextCollectionPtr;

/// @brief Maintains an in-memory store of PingContexts
///
/// Provides essential CRUD functions for managing a collection of
/// PingContexts.  Additionally there are finders that can return
/// contexts by target IP address, instigating query, WAITING_TO_SEND
/// start time, WAITING_FOR_REPLY expiration time, and context state.
/// All finders return copies of the contexts found, rather than the
/// stored context itself.
class PingContextStore {
public:

    /// @brief Constructor
    PingContextStore() : pings_(), mutex_(new std::mutex) {
    }

    /// @brief Destructor
    ~PingContextStore() = default;

    /// @brief Creates a new PingContext and adds it to the store
    ///
    /// @param lease lease whose address is to be ping checked
    /// @param query query that instigated the lease
    /// @param min_echos minimum number of ECHO REQUESTs sent without replies
    /// received required to declare an address free to offer.  Must be
    /// greater than zero.
    /// @param reply_timeout maximum number of milliseconds to wait for an
    /// ECHO REPLY after an ECHO REQUEST has been sent. Must be greater than 0.
    /// @param parking_lot parking lot in which query is parked.  If empty,
    /// parking is assumed to not be employed.
    ///
    /// @return pointer to the newly created context
    /// @throw DuplicateContext is a context for the lease address already
    /// exists in the store.
    PingContextPtr addContext(isc::dhcp::Lease4Ptr& lease,
                              isc::dhcp::Pkt4Ptr& query,
                              uint32_t min_echos,
                              uint32_t reply_timeout,
                              isc::hooks::ParkingLotHandlePtr& parking_lot
                              = PingContext::EMPTY_LOT());

    /// @brief Updates a context in the store.
    ///
    /// The context is assumed to already exist in the store.
    ///
    /// @param context context to update.
    ///
    /// @throw InvalidOperation if PingContext does not exist in the store.
    void updateContext(const PingContextPtr& context);

    /// @brief Removes the context from the store.
    ///
    /// If the context does not exist in the store, it simply returns.
    ///
    /// @param context context to delete.
    void deleteContext(const PingContextPtr& context);

    /// @brief Fetches the context with a given target address
    ///
    /// @param address target IP address for which to search
    ///
    /// @return pointer to the matching PingContext or an empty pointer if
    /// not found.
    PingContextPtr getContextByAddress(const isc::asiolink::IOAddress& address);

    /// @brief Fetches the context with a given query packet
    ///
    /// @param query query for which to search
    ///
    /// @return pointer to the matching PingContext or an empty pointer if
    /// not found.
    PingContextPtr getContextByQuery(isc::dhcp::Pkt4Ptr& query);

    /// @brief Fetches the context in WAITING_TO_SEND with the oldest send wait
    /// start time.
    ///
    /// @return pointer to the matching PingContext or an empty pointer if
    /// not found.
    PingContextPtr getNextToSend();

    /// @brief Fetches the context in WAITING_FOR_REPLY with the oldest expiration
    /// time that has not already passed (i.e. is still in the future)
    ///
    /// @return pointer to the matching PingContext or an empty pointer if
    /// not found.
    PingContextPtr getExpiresNext();

    /// @brief Fetches the contexts in WAITING_FOR_REPLY that expired since a given time
    ///
    /// @param since timestamp to search by. Defaults to current time.
    ///
    /// @return a collection of the matching contexts, ordered by expiration time.
    PingContextCollectionPtr getExpiredSince(const TimeStamp& since = PingContext::now());

    /// @brief Fetches all of the contexts (in order by target)
    ///
    /// @return a collection of all contexts in the store.
    PingContextCollectionPtr getAll();

    /// @brief Removes all contexts from the store.
    void clear();

private:
    /// @brief Container instance.
    PingContextContainer pings_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

} // end of namespace ping_check
} // end of namespace isc

#endif
