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

#ifndef STATE_MODEL_H
#define STATE_MODEL_H

/// @file state_model.h This file defines the class StateModel.

#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <d2/d2_config.h>
#include <d2/dns_client.h>
#include <d2/labeled_value.h>
#include <dhcp_ddns/ncr_msg.h>

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

namespace isc {
namespace d2 {

/// @brief Thrown if the state machine encounters a general error.
class StateModelError : public isc::Exception {
public:
    StateModelError(const char* file, size_t line,
                               const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Define an Event. 
typedef LabeledValue Event;

/// @brief Define Event pointer.
typedef LabeledValuePtr EventPtr;

/// @brief Defines a pointer to an instance method for handling a state.
typedef boost::function<void()> StateHandler;

/// @brief Defines a map of states to their handler methods.
typedef std::map<unsigned int, StateHandler> StateHandlerMap;

/// @brief Implements a finite state machine.
///
/// StateModel is an abstract class that provides the structure and mechanics
/// of a basic finite state machine.
///
/// The state model implementation used is a very basic approach. States
/// and events described by simple integer constants. Each state must have a 
/// state handler. State handlers are void methods which require no parameters.
/// Each model instance contains a map of states to instance method pointers
/// to their respective state handlers.  The model tracks the following
/// context values:
///
/// * state - The current state of the model
/// * previous state -  The state the model was in prior to the current state
/// * next event - The next event to be consumed
/// * last event - The event most recently consumed
///
/// When invoked, a state handler determines what it should do based upon the
/// next event including what the next state and event should be. In other
/// words the state transition knowledge is distributed among the state
/// handlers rather than encapsulated in some form of state transition table.
///
/// Events "posted" from within the state handlers are "internally" triggered
/// events.  Events "posted" from outside the state model, such as through
/// the invocation of a callback are "externally" triggered.
///
/// StateModel defines two states:
///
/// * NEW_ST - State that a model is in following instantiation. It remains in
/// this state until model execution has begun.
/// * END_ST - State that a model is in once it has reached its conclusion.
///
/// and the following events:
///
/// * START_EVT - Event used to start model execution.
/// * NOP_EVT - Event used to signify that the model stop and wait for an
/// external event, such as the completion of an asynchronous IO operation.
/// * END_EVT - Event used to trigger a normal conclusion of the model. This
/// means only that the model was traversed from start to finish, without any
/// model violations (i.e. invalid state, event, or transition) or uncaught
/// exceptions.
/// * FAIL_EVT - Event to trigger an abnormal conclusion of the model. This
/// event is posted internally when model execution fails due to a model
/// violation or uncaught exception.  It signifies that the model has reached
/// an inoperable condition.
///
/// Derivations add their own states and events appropriate for their state
/// model.  Note that NEW_ST and END_ST do not support handlers.  No work can
/// be done (events consumed) prior to starting the model nor can work be done
/// once the model has ended.
///
/// Model execution consists of iteratively invoking the state handler
/// indicated by the current state which should consume the next event. As the
/// handlers post events and/or change the state, the model is traversed. The
/// loop stops whenever the model cannot continue without an externally
/// triggered event or when it has reached its final state.  In the case of
/// the former, the loop may be re-entered upon arrival of the external event.
///
/// This loop is implemented in the runModel method.  This method accepts an
/// event as argument which it "posts" as the next event.  It then retrieves the
/// handler for the current state from the handler map and invokes it. runModel
/// repeats this process until it either a NOP_EVT posts or the state changes
/// to END_ST.  In other words each invocation of runModel causes the model to
/// be traversed from the current state until it must wait or ends.
///
/// Re-entering the "loop" upon the occurrence of an external event is done by
/// invoking runModel with the appropriate event.  As before, runModel will
/// loop until either the NOP_EVT occurs or until the model reaches its end.
///
/// A StateModel (derivation) is in the NEW_ST when constructed and remains
/// there until it has been "started".  Starting the model is done by invoking
/// the startModel method which accepts a state as a parameter.  This parameter
/// specifies the "start" state and it becomes the current state.

/// The first task undertaken by startModel is to initialize and verify the
/// state handler map.  Two virtual methods, initializeStateHandlerMap and
/// verifyStateHandlerMap, are provided for the express purpose of allowing
/// derivations to populate the state handler map and then verify that map is
/// contents are correct.
///
/// Once the handler map has been properly initialized, the startModel method
/// invokes runModel with an event of START_EVT.  From this point forward and
/// until the model reaches the END_ST or fails, it is considered to be
/// "running".  If the model encounters a NOP_EVT then it is "running" and
/// "waiting".   If the model reaches END_ST with an END_EVT it is considered
/// "done".  If the  model fails (END_ST with a FAILED_EVT) it is considered
/// "done" and "failed".  There are several boolean status methods which may
/// be used to check these conditions.
///
/// To progress from one state to the another, state handlers invoke use
/// the method, transition.  This method accepts a state and an event as
/// parameters.  These values become the current state and the next event
/// respectively.  This has the effect of entering the given state having posted
/// the given event.  The postEvent method may be used to post a new event
/// to the current state.
///
/// Bringing the model to a normal end is done by invoking the endModel method
/// which transitions the model to END_ST with END_EVT.  Bringing the model to
/// an abnormal end is done via the abortModel method, which transitions the
/// model to END_ST with FAILED_EVT.
class StateModel {
public:

    //@{ States common to all models.
    /// @brief State that a state model is in immediately after construction.
    static const int NEW_ST = 0;

    /// @brief Final state, all the state model has reached its conclusion.
    static const int END_ST = 1;

    /// @define Value at which custom states in a derived class should begin.
    static const int SM_STATE_MAX = 10;
    //@}

    //@{ Events common to all state models.
    /// @brief Signifies that no event has occurred.
    /// This is event used to interrupt the event loop to allow waiting for
    /// an IO event or when there is no more work to be done.
    static const int NOP_EVT = 0;

    /// @brief Event issued to start the model execution.
    static const int START_EVT = 1;

    /// @brief Event issued to end the model execution.
    static const int END_EVT = 2;

    /// @brief Event issued to abort the model execution.
    static const int FAIL_EVT = 3;

    /// @define Value at which custom events in a derived class should begin.
    static const int SM_EVENT_MAX = 10;
    //@}

    /// @brief Constructor
    StateModel();

    /// @brief Destructor
    virtual ~StateModel();

    /// @brief Begins execution of the model.
    ///
    /// This method invokes initStateHandlerMap() to initialize the map of state
    /// handlers, followed by verifyStateHandlerMap which validates the map
    /// contents. It then starts the  model execution setting the current
    /// state to the given start state, and the event to START_EVT.
    ///
    /// @param start_state is the state in which to begin execution.
    /// @throw StateModelError or others indirectly, as this method calls
    /// initializeStateHandlerMap and verifyStateHandlerMap.
    void startModel(const int start_state);

    /// @brief Processes events through the state model
    ///
    /// This method implements the state model "execution loop".  It uses
    /// the given event as the next event to process and begins invoking the
    /// the state handler for the current state.   As described above, the
    /// invoked state handler consumes the next event and then determines the
    /// next event and the current state as required to implement the business
    /// logic. The method continues to loop until the next event posted is
    /// NOP_EVT or the model ends.
    ///
    /// Any exception thrown during the loop is caught, logged, and the
    /// model is aborted with a FAIL_EVT.  The derivation's state
    /// model is expected to account for any possible errors so any that
    /// escape are treated as unrecoverable.
    ///
    /// @param event is the next event to process
    ///
    /// This method is guaranteed not to throw.
    void runModel(unsigned int event);

    /// @brief Conducts a normal transition to the end of the model.
    ///
    /// This method posts an END_EVT and sets the current state to END_ST.
    /// It should be called by any state handler in the model from which
    /// an exit leads to the model end.  In other words, if the transition
    /// out of a particular state is to the end of the model, that state's
    /// handler should call endModel.
    void endModel();

protected:
    /// @brief Populates the set of events. 
    ///
    /// This method is used to construct the set of valid events. Each class
    /// within a StateModel derivation heirarchy uses this method to add any
    /// events it defines to the set.  Each derivation's implementation must
    /// also call it's superclass's implementation.  This allows each class 
    /// within the heirarchy to make contributions to the set of defined 
    /// events. Implementations use the method, defineEvent(), to add event 
    /// definitions.  An example of the derivation's implementation follows:
    ///
    /// @code
    /// void StateModelDerivation::defineEvents() {
    ///     // Call the superclass implementation.
    ///     StateModelDerivation::defineEvents();
    ///
    ///     // Add the events defined by the derivation. 
    ///     defineEvent(SOME_CUSTOM_EVT_1, "CUSTOM_EVT_1");
    ///     defineEvent(SOME_CUSTOM_EVT_2, "CUSTOM_EVT_2");
    ///     :
    /// }
    /// @endcode
    virtual void defineEvents();

    /// @brief Adds an event value and associated label to the set of events.
    ///
    /// @param value is the numeric value of the event
    /// @param label is the text label of the event used in log messages and
    /// exceptions.
    ///
    /// @throw StateModelError if the model has already been started, if
    /// the value is already defined, or if the label is null or empty.
    void defineEvent(unsigned int value, const char* label);

    /// @brief Fetches the event referred to by value.
    ///
    /// @param value is the numeric value of the event desired.
    /// 
    /// @return returns a constant pointer reference to the event if found
    ///
    /// @throw StateModelError if the event is not defined.
    const EventPtr& getEvent(unsigned int value);

    /// @brief Validates the contents of the set of events.
    ///
    /// This method is invoked immediately after the defineEvents method and 
    /// is used to verify that all the requred events are defined.  If the 
    /// event set is determined to be invalid this method should throw a 
    /// StateModelError.  As with the defineEvents method, each class within
    /// the a StateModel derivation heirarchy must supply an implementation
    /// which calls it's superclass's implemenation as well as verifying any
    /// events added by the derivation.  Validating an event is accomplished
    /// by simply attempting to fetch en event by its value from the the 
    /// event set.  An example of the derivation's implementation follows:
    ///
    /// @code
    /// void StateModelDerivation::verifyEvents() {
    ///     // Call the superclass implementation.
    ///     StateModelDerivation::verifyEvents();
    ///
    ///     // Verify the events defined by the derivation. 
    ///     events_.get(SOME_CUSTOM_EVT_1, "CUSTOM_EVT_1");
    ///     events_.get(SOME_CUSTOM_EVT_2, "CUSTOM_EVT_2");
    ///     :
    /// }
    /// @endcode
    virtual void verifyEvents();

    /// @brief Populates the map of state handlers.
    ///
    /// This method is used by derivations to construct a map of states to
    /// their appropriate state handlers (bound method pointers).  It is
    /// invoked at the beginning of startModel().
    ///
    /// Implementations should use the addToStateHandlerMap() method add
    /// entries to the map.
    virtual void initStateHandlerMap() = 0;

    /// @brief Validates the contents of the state handler map.
    ///
    /// This method is invoked immediately after initStateHandlerMap and
    /// provides an opportunity for derivations to verify that the map
    /// is correct.  If the map is determined to be invalid this method
    /// should throw a StateModelError.
    ///
    /// The simplest implementation would include a call to getStateHandler,
    /// for each state the derivation supports.  For example, an implementation
    /// which included three states, READY_ST, DO_WORK_ST, and DONE_ST could
    /// implement this function as follows:
    ///
    /// @code
    ///    void verifyStateHandlerMap() {
    ///        getStateHandler(READY_ST);
    ///        getStateHandler(DO_WORK_ST);
    ///        getStateHandler(DONE_ST);
    ///    }
    /// @endcode
    ///
    virtual void verifyStateHandlerMap() = 0;

    /// @brief Adds an entry to the state handler map.
    ///
    /// This method attempts to add an entry to the handler map which maps
    /// the given handler to the given state.  The state handler must be
    /// a bound member pointer to a handler method of derivation instance.
    /// The following code snippet shows an example derivation and call to
    /// addToStateHandlerMap() within its initStateHandlerMap() method.
    ///
    /// @code
    /// class ExampleModel : public StateModel {
    /// public:
    /// :
    /// void readyHandler() {
    /// }
    ///
    /// void initStateHandlerMap() {
    ///     addToStateHandlerMap(READY_ST,
    ///        boost::bind(&ExampleModel::readyHandler, this));
    ///     :
    ///
    /// @endcode
    ///
    /// @param state the value of the state to which to map
    /// @param handler the bound method pointer to the handler for the state
    ///
    /// @throw StateModelError if the map already contains an entry
    /// for the given state, or if the model is beyond the NEW_ST.
    void addToStateHandlerMap(unsigned int state, StateHandler handler);

    /// @brief Handler for fatal model execution errors.
    ///
    /// This method is called when an unexpected error renders during
    /// model execution, such as a state handler throwing an exception.
    /// It provides derivations an opportunity to act accordingly by setting
    /// the appropriate status or taking other remedial action.   This allows
    /// the model execution loop to remain exception safe.
    virtual void onModelFailure() = 0;

    /// @brief Return the state handler for a given state.
    ///
    /// This method looks up the state handler for the given state from within
    /// the state handler map.
    ///
    /// @param state is the state constant of the desired handler.
    ///
    /// @return A StateHandler (bound member pointer) for the method that
    /// handles the given state for this model.
    ///
    /// @throw StateModelError
    StateHandler getStateHandler(unsigned int state);

    /// @brief Sets up the model to transition into given state with a given
    /// event.
    ///
    /// This updates the model's notion of the current state and the next
    /// event to process.  State handlers use this method to move from one state
    /// to the next.
    ///
    /// @param state the new value to assign to the current state.
    /// @param event the new value to assign to the next event.
    ///
    /// @throw StateModelError if the state is invalid.
    void transition(unsigned int state, unsigned int event);

    /// @brief Aborts model execution.
    ///
    /// This method posts a FAILED_EVT and sets the current state to END_ST.
    /// It is called internally when a model violation occurs. Violations are
    /// any sort of inconsistency such as attempting to reference an invalid
    /// state, or if the next event is not valid for the current state, or a
    /// state handler throws an uncaught exception.
    void abortModel();

    /// @brief Sets the current state to the given state value.
    ///
    /// This updates the model's notion of the current state and is the
    /// state whose handler will be executed on the next iteration of the run
    /// loop.  This is intended primarily for internal use and testing. It is
    /// unlikely that transitioning to a new state without a new event is of
    /// much use.
    ///
    /// @param state the new value to assign to the current state.
    ///
    /// @throw StateModelError if the state is invalid.
    void setState(unsigned int state);

    /// @brief Sets the next event to the given event value.
    ///
    /// This updates the model's notion of the next event and is the
    /// event that will be passed into the current state's handler on the next
    /// iteration of the run loop.
    ///
    /// @param the numeric event value to post as the next event.
    ///
    /// @throw StateModelError if the event is undefined 
    void postNextEvent(unsigned int event);

    /// @brief Checks if on entry flag is true.
    ///
    /// This method acts as a one-shot test of whether or not  the model is
    /// transitioning into a new state.  It returns true if the on-entry flag
    /// is true upon entering this method and will set the flag false prior
    /// to exit.  It may be used within state handlers to perform steps that
    /// should only occur upon entry into the state.
    ///
    /// @return true if the on entry flag is true, false otherwise.
    bool doOnEntry();

    /// @brief Checks if on exit flag is true.
    ///
    /// This method acts as a one-shot test of whether or not the model is
    /// transitioning out of the current state.  It returns true if the
    /// on-exit flag is true upon entering this method and will set the flag
    /// false prior to exiting.  It may be used within state handlers to perform
    /// steps that should only occur upon exiting out of the current state.
    ///
    /// @return true if the on entry flag is true, false otherwise.
    bool doOnExit();

public:
    /// @brief Fetches the model's current state.
    ///
    /// This returns the model's notion of the current state. It is the
    /// state whose handler will be executed on the next iteration of the run
    /// loop.
    ///
    /// @return An unsigned int representing the current state.
    unsigned int getState() const;

    /// @brief Fetches the model's previous state.
    ///
    /// @return An unsigned int representing the previous state.
    unsigned int getPrevState() const;

    /// @brief Fetches the model's last event.
    ///
    /// @return An unsigned int representing the last event.
    unsigned int getLastEvent() const;

    /// @brief Fetches the model's next event.
    ///
    /// This returns the model's notion of the next event. It is the
    /// event that will be passed into the current state's handler on the next
    /// iteration of the run loop.
    ///
    /// @return An unsigned int representing the next event.
    unsigned int getNextEvent() const;

    /// @brief Returns whether or not the model is new.
    ///
    /// @return Boolean true if the model has not been started.
    bool isModelNew() const;

    /// @brief Returns whether or not the model is running.
    ///
    /// @return Boolean true if the model has been started but has not yet
    /// ended.
    bool isModelRunning() const;

    /// @brief Returns whether or not the model is waiting.
    ///
    /// @return Boolean true if the model is running but is waiting for an
    /// external event for resumption.
    bool isModelWaiting() const;

    /// @brief Returns whether or not the model has finished execution.
    ///
    /// @return Boolean true if the model has reached the END_ST.
    bool isModelDone() const;

    /// @brief Returns whether or not the model failed.
    ///
    /// @return Boolean true if the model has reached the END_ST and the last
    /// event indicates a model violation, FAILED_EVT.
    bool didModelFail() const;

    /// @brief Converts a state value into a text label.
    ///
    /// This method supplies labels for StateModel's predefined states. It is
    /// declared virtual to allow derivations to embed a call to this method
    /// within their own implementation which would define labels for its
    /// states.  An example implementation might look like the following:
    /// @code
    ///
    /// class DerivedModel : public StateModel {
    ///     :
    ///     static const int EXAMPLE_1_ST = SM_STATE_MAX + 1;
    ///     :
    ///     const char* getStateLabel(const int state) const {
    ///         const char* str = "Unknown";
    ///         switch(state) {
    ///         case EXAMPLE_1_ST:
    ///             str = "DerivedModel::EXAMPLE_1_ST";
    ///             break;
    ///         :
    ///         default:
    ///             // Not a derived state, pass it down to StateModel's method.
    ///             str = StateModel::getStateLabel(state);
    ///             break;
    ///         }
    ///
    ///         return (str);
    ///      }
    ///
    /// @endcode
    ///
    /// @param state is the state for which a label is desired.
    ///
    /// @return Returns a const char* containing the state label or
    /// "Unknown" if the value cannot be mapped.
    virtual const char* getStateLabel(const int state) const;

    /// @brief Fetches the label associated with an event value.
    ///
    /// @param event is the numeric event value for which the label is desired.
    ///
    /// @return Returns a const char* containing the event label or
    /// LabeledValueSet::UNDEFINED_LABEL if the value is undefined.
    virtual const char* getEventLabel(const int event) const;

    /// @brief Convenience method which returns a string rendition of the
    /// current state and next event.
    ///
    /// The string will be of the form:
    ///
    ///   current state: [ {state} {label} ] next event: [ {event} {label} ]
    ///
    /// @return Returns a std::string of the format described above.
    std::string getContextStr() const;

    /// @brief Convenience method which returns a string rendition of the
    /// previous state and last event.
    ///
    /// The string will be of the form:
    ///
    ///   previous state: [ {state} {label} ] last event: [ {event} {label} ]
    ///
    /// @return Returns a std::string of the format described above.
    std::string getPrevContextStr() const;

private:
    /// @brief Contains the set of defined Events.
    LabeledValueSet events_;

    /// @brief Contains a map of states to their state handlers.
    StateHandlerMap state_handlers_;

    /// @brief The current state within the model's state model.
    unsigned int state_;

    /// @brief The previous state within the model's state model.
    unsigned int prev_state_;

    /// @brief The event last processed by the model.
    unsigned int last_event_;

    /// @brief The event the model should process next.
    unsigned int next_event_;

    /// @brief Indicates if state entry logic should be executed.
    bool on_entry_flag_;

    /// @brief Indicates if state exit logic should be executed.
    bool on_exit_flag_;
};

/// @brief Defines a pointer to a StateModel.
typedef boost::shared_ptr<StateModel> StateModelPtr;

} // namespace isc::d2
} // namespace isc
#endif
