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

#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <d2/d2_config.h>
#include <d2/dns_client.h>
#include <dhcp_ddns/ncr_msg.h>

#include <boost/shared_ptr.hpp>
#include <map>

namespace isc {
namespace d2 {

/// @brief Thrown if the update manager encounters a general error.
class NameChangeTransactionError : public isc::Exception {
public:
    NameChangeTransactionError(const char* file, size_t line,
                               const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Defines the type used as the unique key for transactions.
typedef isc::dhcp_ddns::D2Dhcid TransactionKey;

/// @brief Defines a function pointer for the handler method for a state.
typedef boost::function<void()> StateHandler;

/// @brief Defines a map of states to their handler methods.
typedef std::map<unsigned int, StateHandler> StateHandlerMap;

/// @brief Embodies the "life-cycle" required to carry out a DDNS update.
///
/// NameChangeTransaction is the base class that provides the common state
/// model mechanics and services performing the DNS updates needed to carry out
/// a DHCP_DDNS request as described by a NameChangeRequest.
///
/// Upon construction, each transaction has all of the information and
/// resources required to carry out its assigned request, including the list(s)
/// of DNS server(s) needed. It is responsible for knowing what conversations
/// it must have with which servers and in the order necessary to fulfill the
/// request. Upon fulfillment of the request, the transaction's work is complete
/// it is destroyed.
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
/// DNSClient via the callback.
///
/// The state model implementation used is a very basic approach. States
/// and events are simple integer constants. Each state must have a state
/// handler. State handlers are void methods which accept an event as their
/// only parameter.  Each transaction instance contains a map of states to
/// to bound method pointers to their respective state handlers.
///
/// When invoked, the handler determines what it should do based upon the event,
/// including what the next state and event should be. In other words the state
/// transition knowledge is distributed among the state handlers rather than
/// encapsulated in some form of state transition table.  Events set from within
/// the state handlers are "internally" triggered events.  Events set from
/// outside the state model, such as through the DNSClient completion callback
/// are "externally" triggered.
///
/// Executing the model consists of iteratively invoking the state handler
/// indicated by the current state and passing it the current event.  As the
/// handlers update the state and event, the machine is traversed. The loop
/// "stops" whenever the model cannot continue without an externally triggered
/// event or when it has reached its final state.  In the case of the former,
/// the loop is re-entered upon arrival of the external event.
///
/// This loop is implemented in the runStateModel method.  This method accepts
/// an event as argument.  This event is treated as the "next event" to process
/// and is fed to the current state's handler.  The runStateModel does not exit
/// until a handler sets the next event to a special value, NOP_EVT,
/// indicating that either it is now waiting for IO to complete of the state
/// model has reached its conclusion.
///
/// Re-entering the "loop" when a DNS update completes is done by a call to
/// runStateModel() from within the DNSClient callback, with an event value
/// of IO_COMPLETED_EVT.  As above, runStateModel() will loop until either the
/// next IO is issued or the state model has reached its conclusion.
///
/// This class defines a set of events and states that are a common to all
/// transactions. Each derivation may add define additional states and events
/// as needed, but it must support the common set.  NameChangeTransaction
/// does not supply any state handlers.  These are the sole responsibility of
/// derivations.
class NameChangeTransaction : public DNSClient::Callback {
public:

    //@{ States common to all transactions.
    /// @brief State a transaction is in immediately after construction.
    static const int NEW_ST = 0;
    /// @brief State from which a transaction is started.
    static const int READY_ST = 1;
    /// @brief State in which forward DNS server  selection is done.
    static const int SELECTING_FWD_SERVER_ST = 2;
    /// @brief State in which reverse DNS server  selection is done.
    static const int SELECTING_REV_SERVER_ST = 3;
    /// @brief Final state, all work has been performed.
    static const int DONE_ST = 4;

    /// @define Value at which custom states in a derived class should begin.
    static const int DERIVED_STATES = 100;
    //@}


    //@{ Events common to all transactions.
    /// @brief Signifies that no event has occurred.
    /// This is event used to interrupt the event loop to allow waiting for
    /// an IO event or when there is no more work to be done.
    static const int NOP_EVT = 0;
    /// @brief Event used to start the transaction.
    static const int START_TRANSACTION_EVT = 1;
    /// @brief Issued when a server needs to be selected.
    static const int SELECT_SERVER_EVT = 2;
    /// @brief Issued when a server  has been selected.
    static const int SERVER_SELECTED_EVT = 3;
    /// @brief Issued when an update fails due to an IO error.
    static const int SERVER_IO_ERROR_EVT = 4;
    /// @brief Issued when there are no more servers from which to select.
    /// This occurs when none of the servers in the list can be reached to
    /// perform the update.
    static const int NO_MORE_SERVERS_EVT = 5;
    /// @brief Issued when a DNS update packet exchange has completed.
    /// This occurs whenever the DNSClient callback is invoked whether the
    /// exchange was successful or not.
    static const int IO_COMPLETED_EVT = 6;
    /// @brief Issued when the attempted update successfully completed.
    /// This occurs when an DNS update packet was successfully processed
    /// by the server.
    static const int UPDATE_OK_EVT = 7;
    /// @brief Issued when the attempted update fails to complete.
    /// This occurs when an DNS update packet fails to process. The nature of
    /// the failure is given by the DNSClient return status and the response
    /// packet (if one was received).
    static const int UPDATE_FAILED_EVT = 8;
    /// @brief Issued when the transaction should be cancelled.
    /// @todo - still on the fence about this one.
    static const int CANCEL_TRANSACTION_EVT = 9;
    /// @brief Issued when the state model has no more work left to do.
    static const int ALL_DONE_EVT = 10;

    /// @define Value at which custom events in a derived class should begin.
    static const int DERIVED_EVENTS = 100;
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
    /// @throw NameChangeTransaction error if given an null request,
    /// if forward change is enabled but forward domain is null, if
    /// reverse change is enabled but reverse domain is null.
    NameChangeTransaction(isc::asiolink::IOService& io_service,
                          dhcp_ddns::NameChangeRequestPtr& ncr,
                          DdnsDomainPtr forward_domain,
                          DdnsDomainPtr reverse_domain);

    virtual ~NameChangeTransaction();

    /// @brief Begins execution of the transaction.
    ///
    /// This method invokes initHandlersMap() to initialize the map of state
    /// handlers. It then starts the transaction's state model by setting the
    /// current state to READY_ST and invoking runStateModel() with an event
    /// parameter of START_TRANSACTION_EVT.
    void startTransaction();

    /// @todo - Not sure about this yet.
    void cancelTransaction();

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
    /// @brief Populates the map of state handlers.
    ///
    /// This method is used by derivations to construct a map of states to
    /// their appropriate state handlers (bound method pointers).  It is
    /// invoked at the beginning of startTransaction().
    ///
    /// Implementations should use the addToMap() method add entries to
    /// the map.
    /// @todo This method should be pure virtual but until there are
    /// derivations for the update manager to use we will provide an
    /// temporary empty, implementation.  If we make it pure virtual now
    /// D2UpdateManager will not compile.
    virtual void initStateHandlerMap() {};

    /// @brief Adds an entry to the state handler map.
    ///
    /// This method attempts to add an entry to the handler map which maps
    /// the given handler to the given state.  The state handler must be
    /// a bound member pointer to a handler method of the transaction instance.
    /// The following code snippet shows an example derivation and call to
    /// addToMap() within its initStateHandlerMap() method.
    ///
    /// @code
    /// class ExampleTrans : public NameChangeTransaction {
    /// public:
    /// :
    /// void readyHandler() {
    /// }
    ///
    /// void initStateHandlerMap() {
    ///     addToMap(READY_ST,
    ///        boost::bind(&ExampleTrans::readyHandler, this));
    ///     :
    ///
    /// @endcode
    ///
    /// @param state the value of the state to which to map
    /// @param handler the bound method pointer to the handler for the state
    ///
    /// @throw NameChangeTransactionError if the map already contains an entry
    /// for the given state.
    void addToMap(unsigned int idx, StateHandler handler);

    /// @brief Processes events through the state model
    ///
    /// This method implements the state model "execution loop".  It uses
    /// the given event as the next event to process and begins looping by
    /// passing it the state handler for the current state.   As described
    /// above, the invoked state handler determines the current state and the
    /// next event required to implement the business logic. The method
    /// continues to loop until next event is set to NOP_EVT, at which point
    /// the method exits.
    ///
    /// Any exception thrown during the loop is caught, logged, and the
    /// transaction is immediately set to failed status.  The state model is
    /// expected to account for any possible errors so any that escape are
    /// treated as unrecoverable in terms of the current transaction.
    ///
    /// @param event is the next event to process
    ///
    /// This is guaranteed not to throw.
    void runStateModel(unsigned int event);

    /// @brief Return the state handler for a given state.
    ///
    /// This method looks up the state handler for the given state from within
    /// the state handler map.
    ///
    /// @param state is the state constant of the desired handler.
    ///
    /// @return A StateHandler (bound method pointer) for the method that
    /// handles the given state for this transaction.
    ///
    /// @throw NameChangeTransactionError
    StateHandler getStateHandler(unsigned int state);

    /// @brief Sets the current state to the given state value.
    ///
    /// This updates the transaction's notion of the current state and is the
    /// state whose handler will be executed on the next iteration of the run
    /// loop.
    ///
    /// @param state the new value to assign to the current state.
    void setState(unsigned int state);

    /// @brief Sets the next event to the given event value.
    ///
    /// This updates the transaction's notion of the next event and is the
    /// event that will be passed into the current state's handler on the next
    /// iteration of the run loop.
    ///
    /// @param state the new value to assign to the current state.
    void setNextEvent(unsigned int event);

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
    /// is reached it's conclusion, the request will end up with a final
    /// status.
    ///
    /// @return A dhcp_ddns::NameChangeStatus representing the current
    /// status of the transaction.
    dhcp_ddns::NameChangeStatus getNcrStatus() const;

    /// @brief Sets the status of the transaction's NameChangeRequest
    ///
    /// @param status is the new value to assign to the NCR status.
    void setNcrStatus(const dhcp_ddns::NameChangeStatus& status);

    /// @brief Fetches the transaction's current state.
    ///
    /// This returns the transaction's notion of the current state. It is the
    /// state whose handler will be executed on the next iteration of the run
    /// loop.
    ///
    /// @return An unsigned int representing the current state.
    unsigned int getState() const;

    /// @brief Fetches the transaction's previous state.
    ///
    /// @return An unsigned int representing the previous state.
    unsigned int getPrevState() const;

    /// @brief Fetches the transaction's last event.
    ///
    /// @return An unsigned int representing the last event.
    unsigned int getLastEvent() const;

    /// @brief Fetches the transaction's next event.
    ///
    /// This returns the transaction's notion of the next event. It is the
    /// event that will be passed into the current state's handler on the next
    /// iteration of the run loop.
    ///
    /// @return An unsigned int representing the next event.
    unsigned int getNextEvent() const;

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
    /// @brief Contains a map of states to their state handlers.
    StateHandlerMap state_handlers_;

    /// @brief The IOService which should be used to for IO processing.
    isc::asiolink::IOService& io_service_;

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

    /// @brief The current state within the transaction's state model.
    unsigned int state_;

    /// @brief The previous state within the transaction's state model.
    unsigned int prev_state_;

    /// @brief The event last processed by the transaction.
    unsigned int last_event_;

    /// @brief The event the transaction should process next.
    unsigned int next_event_;

    /// @brief The outcome of the most recently completed DNS packet exchange.
    DNSClient::Status dns_update_status_;

    /// @brief The DNS update response packet most recently received.
    D2UpdateMessagePtr dns_update_response_;

    /// @brief Indicator for whether or not the forward change completed ok.
    bool forward_change_completed_;

    /// @brief Indicator for whether or not the reverse change completed ok.
    bool reverse_change_completed_;
};

/// @brief Defines a pointer to a NameChangeTransaction.
typedef boost::shared_ptr<NameChangeTransaction> NameChangeTransactionPtr;

} // namespace isc::d2
} // namespace isc
#endif
