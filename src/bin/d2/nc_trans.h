// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef NC_TRANS_H
#define NC_TRANS_H

/// @file nc_trans.h This file defines the class NameChangeTransaction.

#include <exceptions/exceptions.h>
#include <d2/d2_asio.h>
#include <d2/d2_config.h>
#include <d2/dns_client.h>
#include <d2/state_model.h>
#include <dhcp_ddns/ncr_msg.h>

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
/// DNSClient via the callbacka.  Suspension is done by posting a
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

    /// @brief Constructor
    ///
    /// Instantiates a transaction that is ready to be started.
    ///
    /// @param io_service IO service to be used for IO processing
    /// @param ncr is the NameChangeRequest to fulfill
    /// @param forward_domain is the domain to use for forward DNS updates
    /// @param reverse_domain is the domain to use for reverse DNS updates
    ///
    /// @throw NameChangeTransactionError if given an null request,
    /// if forward change is enabled but forward domain is null, if
    /// reverse change is enabled but reverse domain is null.
    NameChangeTransaction(IOServicePtr& io_service,
                          dhcp_ddns::NameChangeRequestPtr& ncr,
                          DdnsDomainPtr& forward_domain,
                          DdnsDomainPtr& reverse_domain);

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
    /// @brief Adds events defined by NameChangeTransaction to the event set.
    ///
    /// This method adds the events common to NCR transaction processing to
    /// the set of define events.  It invokes the superclass's implementation
    /// first to maitain the hierarchical chain of event defintion.
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
    /// first to maitain the hierarchical chain of state defintion.
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
    /// error occurs the transaction is deemed inoperable, and futher model
    /// execution cannot be performed.  It marks the transaction as failed by
    /// setting the NCR status to dhcp_ddns::ST_FAILED
    ///
    /// @param explanation is text detailing the error
    virtual void onModelFailure(const std::string& explanation);

    /// @brief Sets the update status to the given status value.
    ///
    /// @param status is the new value for the update status.
    void setDnsUpdateStatus(const DNSClient::Status& status);

    /// @brief Sets the update response packet to the given packet.
    ///
    /// @param response is the new response packet to assign.
    void setDnsUpdateResponse(D2UpdateMessagePtr& response);

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
    /// the current server to the next server and creates a new DNSClient
    /// instance.
    ///
    /// @return True if a server has been selected, false if there are no more
    /// servers from which to select.
    bool selectNextServer();

    /// @brief Fetches the currently selected server.
    ///
    /// @return A const pointer reference to the DnsServerInfo of the current
    /// server.
    const DnsServerInfoPtr& getCurrentServer() const;

    /// @brief Fetches the DNSClient instance
    ///
    /// @return A const pointer reference to the DNSClient
    const DNSClientPtr& getDNSClient() const;

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
    /// @return A pointer reference to the forward DdnsDomain.  If the
    /// the request does not include a forward change, the pointer will empty.
    DdnsDomainPtr& getForwardDomain();

    /// @brief Fetches the reverse DdnsDomain.
    ///
    /// @return A pointer reference to the reverse DdnsDomain.  If the
    /// the request does not include a reverse change, the pointer will empty.
    DdnsDomainPtr& getReverseDomain();

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

private:
    /// @brief The IOService which should be used to for IO processing.
    IOServicePtr io_service_;

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
};

/// @brief Defines a pointer to a NameChangeTransaction.
typedef boost::shared_ptr<NameChangeTransaction> NameChangeTransactionPtr;

} // namespace isc::d2
} // namespace isc
#endif
