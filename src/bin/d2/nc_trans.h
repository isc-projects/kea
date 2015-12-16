// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NC_TRANS_H
#define NC_TRANS_H

/// @file nc_trans.h This file defines the class NameChangeTransaction.

#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/dns_client.h>
#include <d2/state_model.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dns/tsig.h>

#include <boost/shared_ptr.hpp>
#include <map>

namespace isc {
namespace d2 {

/// @brief Thrown if the transaction encounters a general error.
class NameChangeTransactionError : public isc::Exception {
public:
    NameChangeTransactionError(const char* file, size_t line,
                               const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Defines the type used as the unique key for transactions.
typedef isc::dhcp_ddns::D2Dhcid TransactionKey;

/// @brief Embodies the "life-cycle" required to carry out a DDNS update.
///
/// NameChangeTransaction is the base class that provides the common state
/// model mechanics and services performing the DNS updates needed to carry out
/// a DHCP_DDNS request as described by a NameChangeRequest.  It is derived
/// from StateModel which supplies a simple, general purpose FSM implementation.
///
/// Upon construction, each transaction has all of the information and
/// resources required to carry out its assigned request, including the list(s)
/// of DNS server(s) needed. It is responsible for knowing what conversations
/// it must have with which servers and in the order necessary to fulfill the
/// request. Upon fulfillment of the request, the transaction's work is complete
/// and it is destroyed.
///
/// Fulfillment of the request is carried out through the performance of the
/// transaction's state model.  Using a state driven implementation accounts
/// for the conditional processing flow necessary to meet the DDNS RFCs as well
/// as the asynchronous nature of IO with DNS servers.
///
/// Derivations of the class are responsible for defining the state model and
/// conversations necessary to carry out the specific of request.
///
/// Conversations with DNS servers are done through the use of the DNSClient
/// class.  The DNSClient provides a IOService-based means a service which
/// performs a single, packet exchange with a given DNS server.  It sends a
/// single update to the server and returns the response, asynchronously,
/// through a callback.  At each point in a transaction's state model, where
/// an update is to be sent, the model "suspends" until notified by the
/// DNSClient via the callback.  Suspension is done by posting a
/// StateModel::NOP_EVT as the next event, stopping the state model execution.
///
/// Resuming state model execution when a DNS update completes is done by a
/// call to StateModel::runStateModel() from within the DNSClient callback,
/// with an event value of IO_COMPLETED_EVT (described below).
///
/// This class defines a set of events and states that are a common to all
/// transactions. Each derivation may add define additional states and events
/// as needed, but it must support the common set.  NameChangeTransaction
/// does not supply any state handlers.  These are the sole responsibility of
/// derivations.
class NameChangeTransaction : public DNSClient::Callback, public StateModel {
public:

    //@{ States common to all transactions.

    /// @brief State from which a transaction is started.
    static const int READY_ST = SM_DERIVED_STATE_MIN + 1;

    /// @brief State in which forward DNS server selection is done.
    ///
    /// Within this state, the actual selection of the next forward server
    /// to use is conducted.  Upon conclusion of this state the next server
    /// is either selected or it should transition out with NO_MORE_SERVERS_EVT
    /// event.
    static const int SELECTING_FWD_SERVER_ST = SM_DERIVED_STATE_MIN + 2;

    /// @brief State in which reverse DNS server  selection is done.
    ///
    /// Within this state, the actual selection of the next reverse server
    /// to use is conducted.  Upon conclusion of this state the next server
    /// is either selected or it should transition out with NO_MORE_SERVERS_EVT
    /// event.
    static const int SELECTING_REV_SERVER_ST = SM_DERIVED_STATE_MIN + 3;

    /// @brief State which processes successful transaction conclusion.
    static const int PROCESS_TRANS_OK_ST = SM_DERIVED_STATE_MIN + 4;

    /// @brief State which processes an unsuccessful transaction conclusion.
    static const int PROCESS_TRANS_FAILED_ST = SM_DERIVED_STATE_MIN + 5;

    /// @brief Value at which custom states in a derived class should begin.
    static const int NCT_DERIVED_STATE_MIN = SM_DERIVED_STATE_MIN + 101;
    //@}

    //@{ Events common to all transactions.
    /// @brief Issued when a server needs to be selected.
    static const int SELECT_SERVER_EVT = SM_DERIVED_EVENT_MIN + 1;

    /// @brief Issued when a server  has been selected.
    static const int SERVER_SELECTED_EVT = SM_DERIVED_EVENT_MIN + 2;

    /// @brief Issued when an update fails due to an IO error.
    static const int SERVER_IO_ERROR_EVT = SM_DERIVED_EVENT_MIN + 3;

    /// @brief Issued when there are no more servers from which to select.
    /// This occurs when none of the servers in the list can be reached to
    /// perform the update.

    static const int NO_MORE_SERVERS_EVT =SM_DERIVED_EVENT_MIN +  4;
    /// @brief Issued when a DNS update packet exchange has completed.
    /// This occurs whenever the DNSClient callback is invoked whether the
    /// exchange was successful or not.

    static const int IO_COMPLETED_EVT = SM_DERIVED_EVENT_MIN + 5;
    /// @brief Issued when the attempted update successfully completed.
    /// This occurs when an DNS update packet was successfully processed
    /// by the server.

    static const int UPDATE_OK_EVT = SM_DERIVED_EVENT_MIN + 6;

    /// @brief Issued when the attempted update fails to complete.
    /// This occurs when an DNS update packet fails to process. The nature of
    /// the failure is given by the DNSClient return status and the response
    /// packet (if one was received).
    static const int UPDATE_FAILED_EVT = SM_DERIVED_EVENT_MIN + 7;

    /// @brief Value at which custom events in a derived class should begin.
    static const int NCT_DERIVED_EVENT_MIN = SM_DERIVED_EVENT_MIN + 101;
    //@}

    /// @brief Defualt time to assign to a single DNS udpate.
    /// @todo  This value will be made configurable in the very near future
    /// under trac3268. For now we will define it to 100 milliseconds
    /// so unit tests will run within a reasonable amount of time.
    static const unsigned int DNS_UPDATE_DEFAULT_TIMEOUT = 100;

    /// @brief Maximum times to attempt a single update on a given server.
    static const unsigned int MAX_UPDATE_TRIES_PER_SERVER = 3;

    /// @brief Constructor
    ///
    /// Instantiates a transaction that is ready to be started.
    ///
    /// @param io_service IO service to be used for IO processing
    /// @param ncr is the NameChangeRequest to fulfill
    /// @param forward_domain is the domain to use for forward DNS updates
    /// @param reverse_domain is the domain to use for reverse DNS updates
    /// @param cfg_mgr reference to the current configuration manager
    ///
    /// @throw NameChangeTransactionError if given an null request,
    /// if forward change is enabled but forward domain is null, if
    /// reverse change is enabled but reverse domain is null.
    NameChangeTransaction(asiolink::IOServicePtr& io_service,
                          dhcp_ddns::NameChangeRequestPtr& ncr,
                          DdnsDomainPtr& forward_domain,
                          DdnsDomainPtr& reverse_domain,
                          D2CfgMgrPtr& cfg_mgr);

    /// @brief Destructor
    virtual ~NameChangeTransaction();

    /// @brief Begins execution of the transaction.
    ///
    /// This method invokes StateModel::startModel() with a value of READY_ST.
    /// This causes transaction's state model to attempt to begin execution
    /// with the state handler for READY_ST.
    void startTransaction();

    /// @brief Serves as the DNSClient IO completion event handler.
    ///
    /// This is the implementation of the method inherited by our derivation
    /// from DNSClient::Callback.  When the DNSClient completes an update it
    /// invokes this method as the completion handler.  This method stores
    /// the given status and invokes runStateModel() with an event value of
    /// IO_COMPLETED_EVT.
    ///
    /// @param status is the outcome of the DNS update packet exchange.
    /// This method is exception safe.
    virtual void operator()(DNSClient::Status status);

protected:
    /// @brief Send the update request to the current server.
    ///
    /// This method increments the update attempt count and then passes the
    /// current update request to the DNSClient instance to be sent to the
    /// currently selected server.  Since the send is asynchronous, the method
    /// posts NOP_EVT as the next event and then returns.
    ///
    /// If tsig_key_ is not NULL, then the update will be conducted using
    /// the key to sign the request and verify the response, otherwise it
    /// will be conducted without TSIG.
    ///
    /// @param comment text to include in log detail
    ///
    /// If an exception occurs it will be logged and and the transaction will
    /// be failed.
    virtual void sendUpdate(const std::string& comment = "");

    /// @brief Adds events defined by NameChangeTransaction to the event set.
    ///
    /// This method adds the events common to NCR transaction processing to
    /// the set of define events.  It invokes the superclass's implementation
    /// first to maintain the hierarchical chain of event definition.
    /// Derivations of NameChangeTransaction must invoke its implementation
    /// in like fashion.
    ///
    /// @throw StateModelError if an event definition is invalid or a duplicate.
    virtual void defineEvents();

    /// @brief Validates the contents of the set of events.
    ///
    /// This method verifies that the events defined by both the superclass and
    /// this class are defined.  As with defineEvents, this method calls the
    /// superclass's implementation first, to verify events defined by it and
    /// then this implementation to verify events defined by
    /// NameChangeTransaction.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyEvents();

    /// @brief Adds states defined by NameChangeTransaction to the state set.
    ///
    /// This method adds the states common to NCR transaction processing to
    /// the dictionary of states.  It invokes the superclass's implementation
    /// first to maintain the hierarchical chain of state definition.
    /// Derivations of NameChangeTransaction must invoke its implementation
    /// in like fashion.
    ///
    /// @throw StateModelError if an state definition is invalid or a duplicate.
    virtual void defineStates();

    /// @brief Validates the contents of the set of states.
    ///
    /// This method verifies that the states defined by both the superclass and
    /// this class are defined.  As with defineStates, this method calls the
    /// superclass's implementation first, to verify states defined by it and
    /// then this implementation to verify states defined by
    /// NameChangeTransaction.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyStates();

    /// @brief Handler for fatal model execution errors.
    ///
    /// This handler is called by the StateModel implementation when the model
    /// execution encounters a model violation:  attempt to call an unmapped
    /// state, an event not valid for the current state, or an uncaught
    /// exception thrown during a state handler invocation.  When such an
    /// error occurs the transaction is deemed inoperable, and further model
    /// execution cannot be performed.  It marks the transaction as failed by
    /// setting the NCR status to dhcp_ddns::ST_FAILED
    ///
    /// @param explanation is text detailing the error
    virtual void onModelFailure(const std::string& explanation);

    /// @brief Determines the state and next event based on update attempts.
    ///
    /// This method will post a next event of SERVER_SELECTED_EVT to the
    /// current state if the number of update attempts has not reached the
    /// maximum allowed.
    ///
    /// If the maximum number of attempts has been reached, it will transition
    /// to the given state with a next event of SERVER_IO_ERROR_EVT.
    ///
    /// @param fail_to_state  State to transition to if maximum attempts
    /// have been tried.
    ///
    void retryTransition(const int fail_to_state);

    /// @brief Sets the update request packet to the given packet.
    ///
    /// @param request is the new request packet to assign.
    void setDnsUpdateRequest(D2UpdateMessagePtr& request);

    /// @brief Destroys the current update request packet and resets
    /// udpate attempts count.
    void clearDnsUpdateRequest();

    /// @brief Sets the update status to the given status value.
    ///
    /// @param status is the new value for the update status.
    void setDnsUpdateStatus(const DNSClient::Status& status);

    /// @brief Sets the update response packet to the given packet.
    ///
    /// @param response is the new response packet to assign.
    void setDnsUpdateResponse(D2UpdateMessagePtr& response);

    /// @brief Destroys the current update response packet.
    void clearDnsUpdateResponse();

    /// @brief Sets the forward change completion flag to the given value.
    ///
    /// @param value is the new value to assign to the flag.
    void setForwardChangeCompleted(const bool value);

    /// @brief Sets the reverse change completion flag to the given value.
    ///
    /// @param value is the new value to assign to the flag.
    void setReverseChangeCompleted(const bool value);

    /// @brief Sets the status of the transaction's NameChangeRequest
    ///
    /// @param status is the new value to assign to the NCR status.
    void setNcrStatus(const dhcp_ddns::NameChangeStatus& status);

    /// @brief Initializes server selection from the given DDNS domain.
    ///
    /// Method prepares internal data to conduct server selection from the
    /// list of servers supplied by the given domain.  This method should be
    /// called when a transaction is ready to begin selecting servers from
    /// a new list.  Typically this will be prior to starting the updates for
    /// a given DNS direction.
    ///
    /// @param domain is the domain from which server selection is to be
    /// conducted.
    void initServerSelection(const DdnsDomainPtr& domain);

    /// @brief Selects the next server in the current server list.
    ///
    /// This method is used to iterate over the list of servers.  If there are
    /// no more servers in the list, it returns false.  Otherwise it sets the
    /// current server to the next server and creates a new DNSClient
    /// instance.
    ///
    /// @return True if a server has been selected, false if there are no more
    /// servers from which to select.
    bool selectNextServer();

    /// @brief Sets the update attempt count to the given value.
    ///
    /// @param value is the new value to assign.
    void setUpdateAttempts(const size_t value);

    /// @brief Fetches the IOService the transaction uses for IO processing.
    ///
    /// @return returns a const pointer to the IOService.
    const asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

    /// @brief Creates a new DNS update request based on the given domain.
    ///
    /// Constructs a new "empty", OUTBOUND, request with the message id set
    /// and zone section populated based on the given domain.
    /// It is declared virtual for test purposes.
    ///
    /// @return A D2UpdateMessagePtr to the new request.
    ///
    /// @throw NameChangeTransactionError if request cannot be constructed.
    virtual D2UpdateMessagePtr prepNewRequest(DdnsDomainPtr domain);

    /// @brief Adds an RData for the lease address to the given RRset.
    ///
    /// Creates an in::A() or in:AAAA() RData instance from the NCR
    /// lease address and adds it to the given RRset.
    ///
    /// @param rrset RRset to which to add the RData
    ///
    /// @throw NameChangeTransactionError if RData cannot be constructed or
    /// the RData cannot be added to the given RRset.
    void addLeaseAddressRdata(dns::RRsetPtr& rrset);

    /// @brief Adds an RData for the lease client's DHCID to the given RRset.
    ///
    /// Creates an in::DHCID() RData instance from the NCR DHCID and adds
    /// it to the given RRset.
    ///
    /// @param rrset RRset to which to add the RData
    ///
    /// @throw NameChangeTransactionError if RData cannot be constructed or
    /// the RData cannot be added to the given RRset.
    void addDhcidRdata(dns::RRsetPtr& rrset);

    /// @brief Adds an RData for the lease FQDN to the given RRset.
    ///
    /// Creates an in::PTR() RData instance from the NCR FQDN and adds
    /// it to the given RRset.
    ///
    /// @param rrset RRset to which to add the RData
    ///
    /// @throw NameChangeTransactionError if RData cannot be constructed or
    /// the RData cannot be added to the given RRset.
    void addPtrRdata(dns::RRsetPtr& rrset);

    /// @brief Returns a string version of the current response status and rcode
    ///
    /// Renders a string containing the a text label current DNS update status
    /// and RCODE (if status is DNSClient::SUCCESS)
    ///
    /// @return std::string containing constructed text
    std::string responseString() const;

    /// @brief Returns a string version of transaction outcome.
    ///
    /// Renders a string containing summarizes the outcome of the
    /// transaction. The information includes the overall status,
    /// the last event, whether not forward and reverse changes were
    /// done, as well as the NCR serviced.
    ///
    /// @return std::string containing constructed text
    std::string transactionOutcomeString() const;

public:
    /// @brief Fetches the NameChangeRequest for this transaction.
    ///
    /// @return A const pointer reference to the NameChangeRequest.
    const dhcp_ddns::NameChangeRequestPtr& getNcr() const;

    /// @brief Fetches the unique key that identifies this transaction.
    ///
    /// Transactions are uniquely identified by a TransactionKey. Currently
    /// this is wrapper around a D2Dhcid.
    ///
    /// @return A const reference to the TransactionKey.
    const TransactionKey& getTransactionKey() const;

    /// @brief Fetches the request id that identifies this transaction.
    ///
    /// This is a wrapper around getRequestId from the NCR which currently
    /// returns DHCID. In the future we may include a distinct request id.
    /// The primary purpose of this function is to provide a consistent way
    /// to identify requests for logging purposes.
    ///
    /// @return a string with the the request's request ID (currently DHCID)
    std::string getRequestId() const;

    /// @brief Fetches the NameChangeRequest status of the transaction.
    ///
    /// This is the current status of the NameChangeRequest, not to
    /// be confused with the state of the transaction.  Once the transaction
    /// is reached its conclusion, the request will end up with a final
    /// status.
    ///
    /// @return A dhcp_ddns::NameChangeStatus representing the current
    /// status of the transaction.
    dhcp_ddns::NameChangeStatus getNcrStatus() const;

    /// @brief Fetches the forward DdnsDomain.
    ///
    /// @return A pointer reference to the forward DdnsDomain.  If
    /// the request does not include a forward change, the pointer will empty.
    DdnsDomainPtr& getForwardDomain();

    /// @brief Fetches the reverse DdnsDomain.
    ///
    /// @return A pointer reference to the reverse DdnsDomain.  If
    /// the request does not include a reverse change, the pointer will empty.
    DdnsDomainPtr& getReverseDomain();

    /// @brief Fetches the currently selected server.
    ///
    /// @return A const pointer reference to the DnsServerInfo of the current
    /// server.
    const DnsServerInfoPtr& getCurrentServer() const;

    /// @brief Fetches the DNSClient instance
    ///
    /// @return A const pointer reference to the DNSClient
    const DNSClientPtr& getDNSClient() const;

    /// @brief Fetches the current DNS update request packet.
    ///
    /// @return A const pointer reference to the current D2UpdateMessage
    /// request.
    const D2UpdateMessagePtr& getDnsUpdateRequest() const;

    /// @brief Fetches the most recent DNS update status.
    ///
    /// @return A DNSClient::Status indicating the result of the most recent
    /// DNS update to complete.
    DNSClient::Status getDnsUpdateStatus() const;

    /// @brief Fetches the most recent DNS update response packet.
    ///
    /// @return A const pointer reference to the D2UpdateMessage most recently
    /// received.
    const D2UpdateMessagePtr& getDnsUpdateResponse() const;

    /// @brief Returns whether the forward change has completed or not.
    ///
    /// The value returned is only meaningful if the NameChangeRequest calls
    /// for a forward change to be done. The value returned indicates if
    /// forward change has been completed successfully.
    ///
    /// @return True if the forward change has been completed, false otherwise.
    bool getForwardChangeCompleted() const;

    /// @brief Returns whether the reverse change has completed or not.
    ///
    /// The value returned is only meaningful if the NameChangeRequest calls
    /// for a reverse change to be done. The value returned indicates if
    /// reverse change has been completed successfully.
    ///
    /// @return True if the reverse change has been completed, false otherwise.
    bool getReverseChangeCompleted() const;

    /// @brief Fetches the update attempt count for the current update.
    ///
    /// @return size_t which is the number of times the current request has
    /// been attempted against the current server.
    size_t getUpdateAttempts() const;

    /// @brief Returns the DHCP data type for the lease address
    ///
    /// @return constant reference to dns::RRType::A() if the lease address
    /// is IPv4 or dns::RRType::AAAA() if the lease address is IPv6.
    const dns::RRType& getAddressRRType() const;

private:
    /// @brief The IOService which should be used to for IO processing.
    asiolink::IOServicePtr io_service_;

    /// @brief The NameChangeRequest that the transaction is to fulfill.
    dhcp_ddns::NameChangeRequestPtr ncr_;

    /// @brief The forward domain that matches the request.
    ///
    /// The forward "domain" is DdnsDomain which contains all of the information
    /// necessary, including the list of DNS servers to be used for a forward
    /// change.
    DdnsDomainPtr forward_domain_;

    /// @brief The reverse domain that matches the request.
    ///
    /// The reverse "domain" is DdnsDomain which contains all of the information
    /// necessary, including the list of DNS servers to be used for a reverse
    /// change.
    DdnsDomainPtr reverse_domain_;

    /// @brief The DNSClient instance that will carry out DNS packet exchanges.
    DNSClientPtr dns_client_;

    /// @brief The DNS current update request packet.
    D2UpdateMessagePtr dns_update_request_;

    /// @brief The outcome of the most recently completed DNS packet exchange.
    DNSClient::Status dns_update_status_;

    /// @brief The DNS update response packet most recently received.
    D2UpdateMessagePtr dns_update_response_;

    /// @brief Indicator for whether or not the forward change completed ok.
    bool forward_change_completed_;

    /// @brief Indicator for whether or not the reverse change completed ok.
    bool reverse_change_completed_;

    /// @brief Pointer to the current server selection list.
    DnsServerInfoStoragePtr current_server_list_;

    /// @brief Pointer to the currently selected server.
    DnsServerInfoPtr current_server_;

    /// @brief Next server position in the list.
    ///
    /// This value is always the position of the next selection in the server
    /// list, which may be beyond the end of the list.
    size_t next_server_pos_;

    /// @brief Number of transmit attempts for the current request.
    size_t update_attempts_;

    /// @brief Pointer to the configuration manager.
    D2CfgMgrPtr cfg_mgr_;

    /// @brief Pointer to the TSIG key which should be used (if any).
    dns::TSIGKeyPtr tsig_key_;
};

/// @brief Defines a pointer to a NameChangeTransaction.
typedef boost::shared_ptr<NameChangeTransaction> NameChangeTransactionPtr;

} // namespace isc::d2
} // namespace isc
#endif
