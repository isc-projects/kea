// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SIMPLE_ADD_H
#define SIMPLE_ADD_H

/// @file nc_add.h This file defines the class SimpleAddTransaction.

#include <d2srv/nc_trans.h>
#include <dns/rdata.h>

namespace isc {
namespace d2 {

/// @brief Thrown if the SimpleAddTransaction encounters a general error.
class SimpleAddTransactionError : public isc::Exception {
public:
    SimpleAddTransactionError(const char* file, size_t line,
                               const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Embodies the "life-cycle" required to carry out a DDNS Add update.
///
/// SimpleAddTransaction implements a state machine for adding (or replacing) a
/// forward and/or reverse DNS mapping. This state machine follows a basic
/// remove and replace scheme, that does not attempt to avoid conflicts
/// between updating clients.  The logic may be paraphrased as follows:
///
/// @code
///
/// If the request includes a forward change:
///     Select a forward server
///     Send the server a request to delete and then add forward entry
///
/// If the request includes a reverse change:
///     Select a reverse server
///     Send a server a request to delete and then add reverse entry
///
/// @endcode
///
/// This class derives from NameChangeTransaction from which it inherits
/// states, events, and methods common to NameChangeRequest processing.
class SimpleAddTransaction : public NameChangeTransaction {
public:

    //@{  Additional states needed for SimpleAdd state model.
    /// @brief State that attempts to add forward address records.
    static const int REPLACING_FWD_ADDRS_ST = NCT_DERIVED_STATE_MIN + 1;

    /// @brief State that attempts to replace reverse PTR records
    static const int REPLACING_REV_PTRS_ST = NCT_DERIVED_STATE_MIN + 3;
    //@}

    //@{ Additional events needed for SimpleAdd state model.
    /// @brief Event sent when an add attempt fails with address in use.
    static const int FQDN_IN_USE_EVT = NCT_DERIVED_EVENT_MIN + 1;

    /// @brief Event sent when replace attempt to fails with address not in use.
    static const int FQDN_NOT_IN_USE_EVT = NCT_DERIVED_EVENT_MIN + 2;
    //@}

    /// @brief Constructor
    ///
    /// Instantiates an Add transaction that is ready to be started.
    ///
    /// @param io_service IO service to be used for IO processing
    /// @param ncr is the NameChangeRequest to fulfill
    /// @param forward_domain is the domain to use for forward DNS updates
    /// @param reverse_domain is the domain to use for reverse DNS updates
    /// @param cfg_mgr pointer to the configuration manager
    ///
    /// @throw SimpleAddTransaction error if given request is not a CHG_ADD,
    /// NameChangeTransaction error for base class construction errors.
    SimpleAddTransaction(asiolink::IOServicePtr& io_service,
                       dhcp_ddns::NameChangeRequestPtr& ncr,
                       DdnsDomainPtr& forward_domain,
                       DdnsDomainPtr& reverse_domain,
                       D2CfgMgrPtr& cfg_mgr);

    /// @brief Destructor
    virtual ~SimpleAddTransaction();

protected:
    /// @brief Adds events defined by SimpleAddTransaction to the event set.
    ///
    /// Invokes NameChangeTransaction's implementation and then defines the
    /// events unique to NCR Add transaction processing.
    ///
    /// @throw StateModelError if an event definition is invalid or a duplicate.
    virtual void defineEvents();

    /// @brief Validates the contents of the set of events.
    ///
    /// Invokes NameChangeTransaction's implementation and then verifies the
    /// Add transaction's.  This tests that the needed events are in the event
    /// dictionary.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyEvents();

    /// @brief Adds states defined by SimpleAddTransaction to the state set.
    ///
    /// Invokes NameChangeTransaction's implementation and then defines the
    /// states unique to NCR Add transaction processing.
    ///
    /// @throw StateModelError if an state definition is invalid or a duplicate.
    virtual void defineStates();

    /// @brief Validates the contents of the set of states.
    ///
    /// Invokes NameChangeTransaction's implementation and then verifies the
    /// Add transaction's states. This tests that the needed states are in the
    /// state dictionary.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyStates();

    /// @brief State handler for READY_ST.
    ///
    /// Entered from:
    /// - INIT_ST with next event of START_EVT
    ///
    /// The READY_ST is the state the model transitions into when the inherited
    /// method, startTransaction() is invoked.  This handler, therefore, is the
    /// entry point into the state model execution.h  Its primary task is to
    /// determine whether to start with a forward DNS change or a reverse DNS
    /// change.
    ///
    /// Transitions to:
    /// - SELECTING_FWD_SERVER_ST with next event of SERVER_SELECT_ST if request
    /// includes a forward change.
    ///
    /// - SELECTING_REV_SERVER_ST with next event of SERVER_SELECT_ST if request
    /// includes only a reverse change.
    ///
    /// @throw SimpleAddTransactionError if upon entry next event is not
    /// START_EVT.
    void readyHandler();

    /// @brief State handler for SELECTING_FWD_SERVER_ST.
    ///
    /// Entered from:
    /// - READY_ST with next event of SELECT_SERVER_EVT
    /// - REPLACING_FWD_ADDRS_ST with next event of SERVER_IO_ERROR_EVT
    ///
    /// Selects the server to be used from the forward domain for the forward
    /// DNS update.  If next event is SELECT_SERVER_EVT the handler initializes
    /// the forward domain's server selection mechanism and then attempts to
    /// select the next server. If next event is SERVER_IO_ERROR_EVT then the
    /// handler simply attempts to select the next server.
    ///
    /// Transitions to:
    /// - REPLACING_FWD_ADDRS_ST with next event of SERVER_SELECTED upon
    /// successful server selection
    ///
    /// - PROCESS_TRANS_FAILED with next event of NO_MORE_SERVERS_EVT upon
    /// failure to select a server
    ///
    /// @throw SimpleAddTransactionError if upon entry next event is not
    /// SELECT_SERVER_EVT or SERVER_IO_ERROR_EVT.
    void selectingFwdServerHandler();

    /// @brief State handler for SELECTING_REV_SERVER_ST.
    ///
    /// Entered from:
    /// - READY_ST with next event of SELECT_SERVER_EVT
    /// - REPLACING_FWD_ADDRS_ST with next event of SELECT_SERVER_EVT
    /// - REPLACING_REV_PTRS_ST with next event of SERVER_IO_ERROR_EVT
    ///
    /// Selects the server to be used from the reverse domain for the reverse
    /// DNS update.  If next event is SELECT_SERVER_EVT the handler initializes
    /// the reverse domain's server selection mechanism and then attempts to
    /// select the next server. If next event is SERVER_IO_ERROR_EVT then the
    /// handler simply attempts to select the next server.
    ///
    /// Transitions to:
    /// - REPLACING_REV_PTRS_ST with next event of SERVER_SELECTED upon
    /// successful server selection
    ///
    /// - PROCESS_TRANS_FAILED with next event of NO_MORE_SERVERS_EVT upon
    /// failure to select a server
    ///
    /// @throw SimpleAddTransactionError if upon entry next event is not
    /// SELECT_SERVER_EVT or SERVER_IO_ERROR_EVT.
    void selectingRevServerHandler();

    /// @brief State handler for REPLACING_FWD_ADDRS_ST.
    ///
    /// Entered from:
    /// - SELECTING_FWD_SERVER with next event of SERVER_SELECTED_EVT
    ///
    /// Attempts to replace a forward DNS entry for a given FQDN.  If this is
    /// first invocation of the handler after transitioning into this state,
    /// any previous update request context is deleted.   If next event
    /// is SERVER_SELECTED_EVT, the handler builds the forward add request,
    /// schedules an asynchronous send via sendUpdate(), and returns.  Note
    /// that sendUpdate will post NOP_EVT as next event.
    ///
    /// Posting the NOP_EVT will cause runModel() to suspend execution of
    /// the state model thus affecting a "wait" for the update IO to complete.
    /// Update completion occurs via the DNSClient callback operator() method
    /// inherited from NameChangeTransaction.  When invoked this callback will
    /// post a next event of IO_COMPLETED_EVT and then invoke runModel which
    /// resumes execution of the state model.
    ///
    /// When the handler is invoked with a next event of IO_COMPLETED_EVT,
    /// the DNS update status is checked and acted upon accordingly:
    ///
    /// Transitions to:
    /// - SELECTING_REV_SERVER_ST with next event of SELECT_SERVER_EVT upon
    /// successful addition and the request includes a reverse DNS update.
    ///
    /// - PROCESS_TRANS_OK_ST with next event of UPDATE_OK_EVT upon successful
    /// addition and no reverse DNS update is required.
    ///
    /// - PROCESS_TRANS_FAILED_ST with next event of UPDATE_FAILED_EVT if the
    /// DNS server rejected the update for any other reason or the IO completed
    /// with an unrecognized status.
    ///
    /// - RE-ENTER this states with next event of SERVER_SELECTED_EVT_EVT if
    /// there was an IO error communicating with the server and the number of
    /// per server retries has not been exhausted.
    ///
    /// - SELECTING_FWD_SERVER_ST with next event of SERVER_IO_ERROR_EVT if
    /// there was an IO error communicating with the server and the number of
    /// per server retries has been exhausted.
    ///
    /// @throw SimpleAddTransactionError if upon entry next event is not
    /// SERVER_SELECTED_EVT or IO_COMPLETE_EVT.
    void replacingFwdAddrsHandler();

    /// @brief State handler for REPLACING_REV_PTRS_ST.
    ///
    /// Entered from:
    /// - SELECTING_REV_SERVER_ST with a next event of SERVER_SELECTED_EVT
    ///
    /// Attempts to delete and then add a reverse DNS entry for a given FQDN.
    /// If this is first invocation of the handler after transitioning into
    /// this state, any previous update request context is deleted.  If next
    /// event is SERVER_SELECTED_EVT, the handler builds the reverse replacement
    /// add request, schedules an asynchronous send via sendUpdate(), and
    /// returns.  Note that sendUpdate will post NOP_EVT as next event.
    ///
    /// Posting the NOP_EVT will cause runModel() to suspend execution of
    /// the state model thus affecting a "wait" for the update IO to complete.
    /// Update completion occurs via the DNSClient callback operator() method
    /// inherited from NameChangeTransaction.  When invoked this callback will
    /// post a next event of IO_COMPLETED_EVT and then invoke runModel which
    /// resumes execution of the state model.
    ///
    /// When the handler is invoked with a next event of IO_COMPLETED_EVT,
    /// the DNS update status is checked and acted upon accordingly:
    ///
    /// Transitions to:
    /// - PROCESS_TRANS_OK_ST with a next event of UPDATE_OK_EVT upon
    /// successful replacement.
    ///
    /// - PROCESS_TRANS_FAILED_ST with a next event of UPDATE_FAILED_EVT If the
    /// DNS server rejected the update for any reason or the IO completed
    /// with an unrecognized status.
    ///
    /// - RE-ENTER this state with a next event of SERVER_SELECTED_EVT if
    /// there was an IO error communicating with the server and the number of
    /// per server retries has not been exhausted.
    ///
    /// - SELECTING_REV_SERVER_ST with next event of SERVER_IO_ERROR_EVT if
    /// there was an IO error communicating with the server and the number of
    /// per server retries has been exhausted.
    ///
    /// @throw SimpleAddTransactionError if upon entry next event is not:
    /// SERVER_SELECTED_EVT or IO_COMPLETED_EVT
    void replacingRevPtrsHandler();

    /// @brief State handler for PROCESS_TRANS_OK_ST.
    ///
    /// Entered from:
    /// - REPLACING_FWD_ADDRS_ST with a next event of UPDATE_OK_EVT
    /// - REPLACING_REV_PTRS_ST with a next event of UPDATE_OK_EVT
    ///
    /// Sets the transaction action status to indicate success and ends
    /// model execution.
    ///
    /// Transitions to:
    /// - END_ST with a next event of END_EVT.
    ///
    /// @throw SimpleAddTransactionError if upon entry next event is not:
    /// UPDATE_OK_EVT
    void processAddOkHandler();

    /// @brief State handler for PROCESS_TRANS_FAILED_ST.
    ///
    /// Entered from:
    /// - SELECTING_FWD_SERVER_ST with a next event of NO_MORE_SERVERS
    /// - REPLACING_FWD_ADDRS_ST with a next event of UPDATE_FAILED_EVT
    /// - SELECTING_REV_SERVER_ST with a next event of NO_MORE_SERVERS
    /// - REPLACING_REV_PTRS_ST with a next event of UPDATE_FAILED_EVT
    ///
    /// Sets the transaction status to indicate failure and ends
    /// model execution.
    ///
    /// Transitions to:
    /// - END_ST with a next event of FAIL_EVT.
    ///
    /// @throw SimpleAddTransactionError if upon entry next event is not:
    /// UPDATE_FAILED_EVT
    void processAddFailedHandler();

    /// @brief Builds a DNS request to add/replace a forward DNS entry for an
    /// FQDN
    ///
    /// Constructs a DNS update request, based upon the NCR, for adding a
    /// forward DNS mapping.  Once constructed, the request is stored as
    /// the transaction's DNS update request.
    ///
    /// Prerequisite RRsets:
    /// - There are no prerequisites.
    ///
    /// Updates RRsets:
    /// -# A delete of any existing PTR RRs for the lease address
    /// -# A delete of any existing DHCID RRs for the lease address
    /// -# An FQDN/IP RR addition    (type A for IPv4, AAAA for IPv6)
    /// -# An FQDN/DHCID RR addition (type DHCID)
    ///
    /// @throw This method does not throw but underlying methods may.
    void buildReplaceFwdAddressRequest();

    /// @brief Builds a DNS request to replace a reverse DNS entry for an FQDN
    ///
    /// Constructs a DNS update request, based upon the NCR, for replacing a
    /// reverse DNS mapping.  Once constructed, the request is stored as
    /// the transaction's DNS update request.
    ///
    /// Prerequisite RRsets:
    /// - There are no prerequisites.
    ///
    /// Updates RRsets:
    /// -# A delete of any existing PTR RRs for the lease address
    /// -# A delete of any existing DHCID RRs for the lease address
    /// -# A PTR RR addition for the lease address and FQDN
    /// -# A DHCID RR addition for the lease address and lease client DHCID
    ///
    /// @throw This method does not throw but underlying methods may.
    void buildReplaceRevPtrsRequest();
};

/// @brief Defines a pointer to a SimpleAddTransaction.
typedef boost::shared_ptr<SimpleAddTransaction> SimpleAddTransactionPtr;

} // namespace isc::d2
} // namespace isc
#endif
