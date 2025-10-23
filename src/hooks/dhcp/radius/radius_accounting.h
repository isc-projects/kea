// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_ACCOUNTING_H
#define RADIUS_ACCOUNTING_H

#include <util/csv_file.h>
#include <dhcpsrv/lease.h>
#include <radius_service.h>
#include <radius_request.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <mutex>

namespace isc {
namespace radius {

/// @brief Type of accounting events.
enum Event : int {
    EVENT_CREATE = 0,  //< A new lease was created (leaseX_select hooks).
    EVENT_RENEW = 1,   //< A lease was renewed (leaseX_renew hooks).
    EVENT_REBIND = 2,  //< A lease was rebound (lease6_rebind hook).
    EVENT_EXPIRE = 3,  //< A lease was expired (leaseX_expire hooks).
    EVENT_RELEASE = 4, //< A lease was released (leaseX_release hooks).
    EVENT_DECLINE = 5, //< A lease was declined (leaseX_decline hooks).
    EVENT_ADD = 6,     //< A command added a lease (command_processed hook).
    EVENT_UPDATE = 7,  //< A command updated a lease (command_processed hook).
    EVENT_DEL = 8,     //< A command deleted a lease (command_processed hook).
};

/// @brief Translate an event to text.
///
/// @param event The event.
/// @return textual representation of the event.
std::string eventToText(Event event);

/// @brief Create timestamp entry.
///
/// Associate a lease address (primary key in database) with a create
/// timestamp (only a first seen timestamp when started with a not empty
/// lease database).
class LeaseTS {
public:

    /// @brief Constructor.
    ///
    /// @param addr Lease address.
    /// @param timestamp Create (or first seen) timestamp.
    LeaseTS(const asiolink::IOAddress& addr,
            const boost::posix_time::ptime& timestamp)
        : addr_(addr), timestamp_(timestamp) {
    }

    /// @brief Lease address.
    const asiolink::IOAddress addr_;

    /// @brief Create timestamp.
    const boost::posix_time::ptime timestamp_;
};

/// @brief Tag for the index for searching by address.
struct TMAddressIndexTag { };

/// @brief Tag for the index for searching by timestamp.
struct TMTimestampIndexTag { };

/// @brief Create timestamp container.
typedef boost::multi_index_container<

    /// This container stores create timestamp entries.
    LeaseTS,

    // Start specification of indexes here.
    boost::multi_index::indexed_by<

        // First index is used to search by an address.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<TMAddressIndexTag>,
            boost::multi_index::member<LeaseTS,
                                       const asiolink::IOAddress,
                                       &LeaseTS::addr_>
        >,

        // Second index is used to search by timestamp.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<TMTimestampIndexTag>,
            boost::multi_index::member<LeaseTS,
                                       const boost::posix_time::ptime,
                                       &LeaseTS::timestamp_>
        >
    >
> TMContainer;

/// @brief First index type in the @c TMContainer.
typedef TMContainer::index<TMAddressIndexTag>::type TMContainerAddressIndex;

/// @brief Second index type in the @c TMContainer.
typedef TMContainer::index<TMTimestampIndexTag>::type TMContainerTimestampIndex;

/// @brief Class of Radius accounting environments.
///
/// This class is a container for the communication environment.
class RadiusAcctEnv {
public:

    /// Constructor.
    ///
    /// @param session_id Session ID.
    /// @param event The event.
    /// @param subnet_id Subnet ID aka NAS port.
    /// @param send_attrs Attributes to send.
    RadiusAcctEnv(std::string session_id, Event event, uint32_t subnet_id,
                  AttributesPtr send_attrs);

    /// @brief Session Id.
    std::string session_id_;

    /// @brief Event.
    Event event_;

    /// @brief Subnet Id (aka client/NAS port).
    uint32_t subnet_id_;

    /// @brief Attributes to send.
    AttributesPtr send_attrs_;

    /// @brief Termination flag.
    bool finished_;
};

/// @brief Class of Radius accounting communication handler.
class RadiusAcctHandler {
public:

    /// Constructor.
    ///
    /// @param env The environment.
    /// @param callback Termination callback.
    RadiusAcctHandler(RadiusAcctEnv env, const CallbackAcct& callback);

    /// Destructor.
    virtual ~RadiusAcctHandler();

    /// @brief Start communication.
    void start();

    /// @brief Get instance counter.
    static size_t getCounter();

    /// @brief Environment.
    RadiusAcctEnv env_;

protected:

    /// @brief Pointer to the communication class.
    RadiusAsyncAcctPtr acct_;

private:

    /// @brief Instance counter.
    static size_t counter_;

    /// @brief Mutex to protect the instance counter.
    static std::mutex mutex_;
};

/// @brief Type of pointers to Radius accounting communication handler.
typedef boost::shared_ptr<RadiusAcctHandler> RadiusAcctHandlerPtr;

/// @brief Type of pointers to CSV file.
typedef boost::shared_ptr<util::CSVFile> CSVFilePtr;

/// @brief Radius accounting class.
class RadiusAccounting : public RadiusService {
public:

    /// @brief Constructor.
    RadiusAccounting();

    /// @brief Destructor.
    virtual ~RadiusAccounting() = default;

    /// @brief Initialize.
    ///
    /// To keep session history between reconfiguration and rebooting
    /// the history is saved in a file which provides stable storage.
    ///
    /// @param filename Name of the file.
    void init(const std::string& filename);

    /// @brief Build RadiusAcct handler for Accounting-Request - IPv4.
    ///
    /// This method is called when appropriate DHCPv4 packet is received
    /// or IPv4 lease expires.
    ///
    /// This method will prepare Accounting-Request with the following
    /// attributes:
    /// - User-Name = duid
    /// - Calling-Station-Id = hardware address (if available)
    /// - Framed-IPv6-Address = IPv6 address or
    /// - Delegated-IPv6-Prefix = IPv6 prefix
    /// - Acct-Status-Type = Start,Stop or Interim-Update
    /// - Acct-Session-Id = IPv4 address with a start of the lease assignment
    ///
    /// @param lease DHCPv4 lease of the event.
    /// @param event the type of event.
    /// @return RadiusAcct handler.
    RadiusAcctHandlerPtr buildAcct(const dhcp::Lease4Ptr& lease, Event event);

    /// @brief Build RadiusAcct handler for Accounting-Request - IPv6.
    ///
    /// This method is called when appropriate DHCPv6 packet is received
    /// or IPv6 lease expires.
    ///
    /// This method will prepare Accounting-Request with the following
    /// attributes:
    /// - User-Name = client-id or duid (or hw-addr if client-id not specified)
    /// - Calling-Station-Id = hardware address
    /// - Framed-IP-Address = IPv4 address
    /// - Acct-Status-Type = Start,Stop or Interim-Update
    /// - Acct-Session-Id = IPv4 address with a start of the lease assignment
    ///
    /// @param lease DHCPv6 lease of the event.
    /// @param event the type of event.
    /// @return RadiusAcct handler.
    RadiusAcctHandlerPtr buildAcct(const dhcp::Lease6Ptr& lease, Event event);

    /// @brief Build RadiusAcct handler for Accounting-Request.
    ///
    /// This method is called when lease4-X commands are received.
    ///
    /// @param arguments lease command arguments.
    /// @param event the type of event.
    /// @return RadiusAcct handler.
    RadiusAcctHandlerPtr buildAcct4(const data::ConstElementPtr& arguments,
                                    Event event);

    /// @brief Build RadiusAcct handler for Accounting-Request.
    ///
    /// This method is called when lease6-X commands are received.
    ///
    /// @param arguments lease command arguments.
    /// @param event the type of event.
    /// @return RadiusAcct handler.
    RadiusAcctHandlerPtr buildAcct6(const data::ConstElementPtr& arguments,
                                    Event event);

    /// @brief Run asynchronously.
    ///
    /// @param handler The communication handler.
    static void runAsync(RadiusAcctHandlerPtr handler);

    /// @brief Termination callback.
    ///
    /// @param env Communication environment.
    /// @param result return code.
    static void terminate(RadiusAcctEnv env, int result);

    /// @brief Get lease create-timestamp entry from session history.
    ///
    /// @param addr lease address.
    /// @param generate true if it is a new lease.
    /// @return the create timestamp.
    boost::posix_time::ptime
    getCreateTimestamp(const asiolink::IOAddress& addr, bool generate);

    /// @brief Erase create-timestamp entry to session history.
    ///
    /// @param addr lease address.
    void eraseCreateTimestamp(const asiolink::IOAddress& addr);

    /// @brief Load create-timestamp entries from file.
    ///
    /// @return true if there was no error.
    bool loadFromFile();

    /// @brief Store create-timestamp entries to a file.
    ///
    /// Content of the create timestamp container is written to a file
    /// in the increasing timestamp order.
    void storeToFile();

protected:

    /// @brief Create timestamps file name.
    std::string filename_;

    /// @brief The Create timestamp container which holds session history.
    TMContainer container_;

    /// @brief Epoch to avoid too long values.
    ///
    /// Initialized to date at which feature was introduced.
    const boost::posix_time::ptime epoch_;

    /// @brief Pointer to the CSVFile.
    CSVFilePtr file_;

    /// @brief New record counter.
    ///
    /// This counter is incremented each time a record is added to the file.
    /// It could be used to trigger a cleanup file tool.
    size_t record_count_;

    /// @brief Mutex to protect access to @ref container_ and @ref file_.
    std::mutex mutex_;
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
