// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NC_REMOVE_H
#define NC_REMOVE_H

/// @file nc_remove.h This file defines the class NameRemoveTransaction.

#include <d2/nc_trans.h>

namespace isc {
namespace d2 {

/// @brief Thrown if the NameRemoveTransaction encounters a general error.
class NameRemoveTransactionError : public isc::Exception {
public:
    NameRemoveTransactionError(const char* file, size_t line,
                               const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Embodies the "life-cycle" required to carry out a DDNS Remove update.
///
/// NameRemoveTransaction implements a state machine for removing a forward
/// and/or reverse DNS mappings. This state machine is based upon the processing
/// logic described in RFC 4703, Section 5.5. That logic may be paraphrased as
/// follows:
///
/// @code
///
/// If the request includes a forward change:
///     Select a forward server
///     Send the server a request to remove client's specific forward address RR
///     If it succeeds or the server responds with name no longer in use
///         Send a server a request to delete any other RRs for that FQDN, such
///         as the DHCID RR.
///     otherwise
///         abandon the update
///
/// If the request includes a reverse change:
///     Select a reverse server
///     Send a server a request to delete reverse entry (PTR RR)
///
/// @endcode
///
/// This class derives from NameChangeTransaction from which it inherits
/// states, events, and methods common to NameChangeRequest processing.
class NameRemoveTransaction : public NameChangeTransaction {
public:

    //@{  Additional states needed for NameRemove state model.
    /// @brief State that attempts to remove specific forward address record.
    static const int REMOVING_FWD_ADDRS_ST = NCT_DERIVED_STATE_MIN + 1;

    /// @brief State that attempts to remove any other forward RRs for the DHCID
    static const int REMOVING_FWD_RRS_ST = NCT_DERIVED_STATE_MIN + 2;

    /// @brief State that attempts to remove reverse PTR records
    static const int REMOVING_REV_PTRS_ST = NCT_DERIVED_STATE_MIN + 3;
    //@}

    //@{ Additional events needed for NameRemove state model.
    /// @brief Event sent when replace attempt to fails with address not in use.
    /// @todo Currently none have been identified.
    //@}

    /// @brief Constructor
    ///
    /// Instantiates an Remove transaction that is ready to be started.
    ///
    /// @param io_service IO service to be used for IO processing
    /// @param ncr is the NameChangeRequest to fulfill
    /// @param forward_domain is the domain to use for forward DNS updates
    /// @param reverse_domain is the domain to use for reverse DNS updates
    /// @param cfg_mgr pointer to the configuration manager
    ///
    /// @throw NameRemoveTransaction error if given request is not a CHG_REMOVE,
    /// NameChangeTransaction error for base class construction errors.
    NameRemoveTransaction(asiolink::IOServicePtr& io_service,
                          dhcp_ddns::NameChangeRequestPtr& ncr,
                          DdnsDomainPtr& forward_domain,
                          DdnsDomainPtr& reverse_domain,
                          D2CfgMgrPtr& cfg_mgr);

    /// @brief Destructor
    virtual ~NameRemoveTransaction();

protected:
    /// @brief Adds events defined by NameRemoveTransaction to the event set.
    ///
    /// Invokes NameChangeTransaction's implementation and then defines the
    /// events unique to NCR Remove transaction processing.
    ///
    /// @throw StateModelError if an event definition is invalid or a duplicate.
    virtual void defineEvents();

    /// @brief Validates the contents of the set of events.
    ///
    /// Invokes NameChangeTransaction's implementation and then verifies the
    /// Remove transaction's events. This tests that the needed events are in
    /// the event dictionary.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyEvents();

    /// @brief Adds states defined by NameRemoveTransaction to the state set.
    ///
    /// Invokes NameChangeTransaction's implementation and then defines the
    /// states unique to NCR Remove transaction processing.
    ///
    /// @throw StateModelError if an state definition is invalid or a duplicate.
    virtual void defineStates();

    /// @brief Validates the contents of the set of states.
    ///
    /// Invokes NameChangeTransaction's implementation and then verifies the
    /// Remove transaction's states.  This tests that the needed states are in
    /// the state dictionary.
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
    /// entry point into the state model execution.  Its primary task is to
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
    /// @throw NameRemoveTransactionError if upon entry next event is not
    /// START_EVT.
    void readyHandler();

    /// @brief State handler for SELECTING_FWD_SERVER_ST.
    ///
    /// Entered from:
    /// - READY_ST with next event of SELECT_SERVER_EVT
    /// - REMOVING_FWD_ADDRS_ST with next event of SERVER_IO_ERROR_EVT
    ///
    /// Selects the server to be used from the forward domain for the forward
    /// DNS update.  If next event is SELECT_SERVER_EVT the handler initializes
    /// the forward domain's server selection mechanism and then attempts to
    /// select the next server. If next event is SERVER_IO_ERROR_EVT then the
    /// handler simply attempts to select the next server.
    ///
    /// Transitions to:
    /// - REMOVING_FWD_ADDRS_ST with next event of SERVER_SELECTED upon
    /// successful server selection
    ///
    /// - PROCESS_TRANS_FAILED with next event of NO_MORE_SERVERS_EVT upon
    /// failure to select a server
    ///
    /// @throw NameRemoveTransactionError if upon entry next event is not
    /// SELECT_SERVER_EVT or SERVER_IO_ERROR_EVT.
    void selectingFwdServerHandler();

    /// @brief State handler for SELECTING_REV_SERVER_ST.
    ///
    /// Entered from:
    /// - READY_ST with next event of SELECT_SERVER_EVT
    /// - REMOVING_FWD_RRS_ST with next event of SELECT_SERVER_EVT
    /// - REMOVING_REV_PTRS_ST with next event of SERVER_IO_ERROR_EVT
    ///
    /// Selects the server to be used from the reverse domain for the reverse
    /// DNS update.  If next event is SELECT_SERVER_EVT the handler initializes
    /// the reverse domain's server selection mechanism and then attempts to
    /// select the next server. If next event is SERVER_IO_ERROR_EVT then the
    /// handler simply attempts to select the next server.
    ///
    /// Transitions to:
    /// - REMOVING_REV_PTRS_ST with next event of SERVER_SELECTED upon
    /// successful server selection
    ///
    /// - PROCESS_TRANS_FAILED with next event of NO_MORE_SERVERS_EVT upon
    /// failure to select a server
    ///
    /// @throw NameRemoveTransactionError if upon entry next event is not
    /// SELECT_SERVER_EVT or SERVER_IO_ERROR_EVT.
    void selectingRevServerHandler();

    /// @brief State handler for REMOVING_FWD_ADDRS_ST.
    ///
    /// Entered from:
    /// - SELECTING_FWD_SERVER with next event of SERVER_SELECTED_EVT
    ///
    /// Attempts to remove the forward DNS entry for a given FQDN, provided
    /// a DHCID RR exists which matches the requesting DHCID.  If this is
    /// first invocation of the handler after transitioning into this state,
    /// any previous update request context is deleted.   If next event
    /// is SERVER_SELECTED_EVT, the handler builds the forward remove request,
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
    /// When the handler is invoked with a next event of IO_COMPELTED_EVT,
    /// the DNS update status is checked and acted upon accordingly:
    ///
    /// Transitions to:
    /// - REMOVING_FWD_RRS_ST with next event of UPDATE_OK_EVT upon successful
    /// removal or RCODE of indication FQDN is no longer in use (NXDOMAIN).
    ///
    /// - PROCESS_TRANS_FAILED_ST with next event of UPDATE_FAILED_EVT if the
    /// DNS server rejected the update for any reason or the IO completed
    /// with an unrecognized status.
    ///
    /// - RE-ENTER this state with next event of SERVER_SELECTED_EVT if
    /// there was an IO error communicating with the server and the number of
    /// per server retries has not been exhausted.
    ///
    /// - SELECTING_FWD_SERVER_ST with next event of SERVER_IO_ERROR_EVT if
    /// there was an IO error communicating with the server and the number of
    /// per server retries has been exhausted.
    ///
    /// @throw NameRemoveTransactionError if upon entry next event is not
    /// SERVER_SELECTED_EVT or IO_COMPLETE_EVT
    void removingFwdAddrsHandler();

    /// @brief State handler for REMOVING_FWD_RRS_ST.
    ///
    /// Entered from:
    /// - REMOVING_FWD_ADDRS_ST with next event of UPDATE_OK_EVT
    ///
    /// Attempts to delete any remaining RRs associated with the given FQDN
    /// such as the DHCID RR.  If this is first invocation of the handler after
    /// transitioning into this state, any previous update request context is
    /// deleted and the handler builds the forward remove request. It then
    /// schedules an asynchronous send via sendUpdate(),
    /// and returns.  Note that sendUpdate will post NOP_EVT as the next event.
    ///
    /// Posting the NOP_EVT will cause runModel() to suspend execution of
    /// the state model thus affecting a "wait" for the update IO to complete.
    /// Update completion occurs via the DNSClient callback operator() method
    /// inherited from NameChangeTransaction.  When invoked this callback will
    /// post a next event of IO_COMPLETED_EVT and then invoke runModel which
    /// resumes execution of the state model.
    ///
    /// When the handler is invoked with a next event of IO_COMPELTED_EVT,
    /// the DNS update status is checked and acted upon accordingly:
    ///
    /// Transitions to:
    /// - SELECTING_REV_SERVER_ST with a next event of SELECT_SERVER_EVT upon
    /// successful completion and the request includes a reverse DNS update.
    ///
    /// - PROCESS_TRANS_OK_ST with next event of UPDATE_OK_EVT upon successful
    /// completion and the request does not include a reverse DNS update.
    ///
    /// - PROCESS_TRANS_FAILED_ST with a next event of UPDATE_FAILED_EVT if the
    /// DNS server rejected the update for any other reason or the IO completed
    /// with an unrecognized status.
    ///
    /// - RE-ENTER this state with a next event of SERVER_SELECTED_EVT if
    /// there was an IO error communicating with the server and the number of
    /// per server retries has not been exhausted.
    ///
    /// - PROCESS_TRANS_FAILED_ST with a next event of SERVER_IO_ERROR_EVT if
    /// there we have reached maximum number of retries without success on the
    /// current server.
    ///
    /// @note If we exhaust the IO retries for the current server due to IO
    /// failures, we will abort the remaining updates.  The rational is that
    /// we are only in this state, if the remove of the forward address RR
    /// succeeded (removingFwdAddrsHandler) on the current server so we should
    /// not attempt another removal on a different server.  This is perhaps a
    /// point for discussion. @todo Should we go ahead with the reverse remove?
    ///
    /// @throw NameRemoveTransactionError if upon entry next event is not:
    /// UPDATE_OK_EVT or IO_COMPLETE_EVT
    void removingFwdRRsHandler();

    /// @brief State handler for REMOVING_REV_PTRS_ST.
    ///
    /// Entered from:
    /// - SELECTING_REV_SERVER_ST with a next event of SERVER_SELECTED_EVT
    ///
    /// Attempts to delete a reverse DNS entry for a given FQDN. If this is
    /// first invocation of the handler after transitioning into this state,
    /// any previous update request context is deleted.  If next event is
    /// SERVER_SELECTED_EVT, the handler builds the reverse remove request,
    /// schedules an asynchronous send via sendUpdate(), and then returns.
    /// Note that sendUpdate will post NOP_EVT as next event.
    ///
    /// Posting the NOP_EVT will cause runModel() to suspend execution of
    /// the state model thus affecting a "wait" for the update IO to complete.
    /// Update completion occurs via the DNSClient callback operator() method
    /// inherited from NameChangeTransaction.  When invoked this callback will
    /// post a next event of IO_COMPLETED_EVT and then invoke runModel which
    /// resumes execution of the state model.
    ///
    /// When the handler is invoked with a next event of IO_COMPELTED_EVT,
    /// the DNS update status is checked and acted upon accordingly:
    ///
    /// Transitions to:
    /// - PROCESS_TRANS_OK_ST with a next event of UPDATE_OK_EVT upon
    /// successful completion.
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
    /// @throw NameRemoveTransactionError if upon entry next event is not:
    /// SERVER_SELECTED_EVT or IO_COMPLETED_EVT
    void removingRevPtrsHandler();

    /// @brief State handler for PROCESS_TRANS_OK_ST.
    ///
    /// Entered from:
    /// - REMOVING_FWD_RRS_ST with a next event of UPDATE_OK_EVT
    /// - REMOVING_REV_PTRS_ST with a next event of UPDATE_OK_EVT
    ///
    /// Sets the transaction action status to indicate success and ends
    /// model execution.
    ///
    /// Transitions to:
    /// - END_ST with a next event of END_EVT.
    ///
    /// @throw NameRemoveTransactionError if upon entry next event is not:
    /// UPDATE_OK_EVT
    void processRemoveOkHandler();

    /// @brief State handler for PROCESS_TRANS_FAILED_ST.
    ///
    /// Entered from:
    /// - SELECTING_FWD_SERVER_ST with a next event of NO_MORE_SERVERS
    /// - REMOVING_FWD_ADDRS_ST with a next event of UPDATE_FAILED_EVT
    /// - REMOVING_FWD_RRS_ST with a next event of UPDATE_FAILED_EVT
    /// - REMOVING_FWD_RRS_ST with a next event of SERVER_IO_ERROR_EVT
    /// - SELECTING_REV_SERVER_ST with a next event of NO_MORE_SERVERS
    /// - REMOVING_REV_PTRS_ST with a next event of UPDATE_FAILED_EVT
    ///
    /// Sets the transaction status to indicate failure and ends
    /// model execution.
    ///
    /// Transitions to:
    /// - END_ST with a next event of FAIL_EVT.
    ///
    /// @throw NameRemoveTransactionError if upon entry next event is not:
    /// UPDATE_FAILED_EVT
    void processRemoveFailedHandler();

    /// @brief Builds a DNS request to remove a forward DNS address for a FQDN.
    ///
    /// Constructs a DNS update request, based upon the NCR, for removing a
    /// forward DNS address mapping. Once constructed, the request is stored as
    /// the transaction's DNS update request.
    ///
    /// The request content is adherent to RFC 4703 section 5.5, paragraph 4.
    ///
    /// Prerequisite RRsets:
    /// 1. An assertion that a matching DHCID RR exists
    ///
    /// Updates RRsets:
    /// 1. A delete of the FQDN/IP RR (type A for IPv4, AAAA for IPv6)
    ///
    /// @throw This method does not throw but underlying methods may.
    void buildRemoveFwdAddressRequest();

    /// @brief Builds a DNS request to remove all forward DNS RRs for a FQDN.
    ///
    /// Constructs a DNS update request, based upon the NCR, for removing any
    /// remaining forward DNS RRs, once all A or AAAA entries for the FQDN
    /// have been removed. Once constructed, the request is stored as the
    /// transaction's DNS update request.
    ///
    /// The request content is adherent to RFC 4703 section 5.5, paragraph 5.
    ///
    /// Prerequisite RRsets:
    /// 1. An assertion that a matching DHCID RR exists
    /// 2. An assertion that no A RRs for the FQDN exist
    /// 3. An assertion that no AAAA RRs for the FQDN exist
    ///
    /// Updates RRsets:
    /// 1. A delete of all RRs for the FQDN
    ///
    /// @throw This method does not throw but underlying methods may.
    void buildRemoveFwdRRsRequest();

    /// @brief Builds a DNS request to remove a reverse DNS entry for a FQDN
    ///
    /// Constructs a DNS update request, based upon the NCR, for removing a
    /// reverse DNS mapping.  Once constructed, the request is stored as
    /// the transaction's DNS update request.
    ///
    /// The request content is adherent to RFC 4703 section 5.5, paragraph 2:
    ///
    /// Prerequisite RRsets:
    /// 1. An assertion that a PTR record matching the client's FQDN exists.
    ///
    /// Updates RRsets:
    /// 1. A delete of all RRs for the FQDN
    ///
    /// @throw This method does not throw but underlying methods may.
    void buildRemoveRevPtrsRequest();
};

/// @brief Defines a pointer to a NameRemoveTransaction.
typedef boost::shared_ptr<NameRemoveTransaction> NameRemoveTransactionPtr;


} // namespace isc::d2
} // namespace isc
#endif
