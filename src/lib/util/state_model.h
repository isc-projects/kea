// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STATE_MODEL_H
#define STATE_MODEL_H

/// @file state_model.h This file defines the class StateModel.

#include <exceptions/exceptions.h>
#include <util/labeled_value.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <map>
#include <mutex>
#include <string>

namespace isc {
namespace util {

/// @brief Thrown if the state machine encounters a general error.
class StateModelError : public isc::Exception {
public:
    StateModelError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Define an Event.
typedef LabeledValue Event;

/// @brief Define Event pointer.
typedef LabeledValuePtr EventPtr;

/// @brief Defines a pointer to an instance method for handling a state.
typedef std::function<void()> StateHandler;

/// @brief State machine pausing modes.
///
/// Supported modes are:
/// - always pause in the given state,
/// - never pause in the given state,
/// - pause upon first transition to the given state.
enum StatePausing {
    STATE_PAUSE_ALWAYS,
    STATE_PAUSE_NEVER,
    STATE_PAUSE_ONCE
};

/// @brief Defines a State within the State Model.
///
/// This class provides the means to define a state within a set or dictionary
/// of states, and assign the state an handler method to execute the state's
/// actions.  It derives from LabeledValue which allows a set of states to be
/// keyed by integer constants.
///
/// Because a state model can be paused in selected states, this class also
/// provides the means for specifying a pausing mode and for checking whether
/// the state model should be paused when entering this state.
class State : public LabeledValue {
public:
    /// @brief Constructor
    ///
    /// @param value is the numeric value of the state
    /// @param label is the text label to assign to the state
    /// @param handler is the bound instance method which handles the state's
    /// action.
    /// @param state_pausing pausing mode selected for the given state. The
    /// default value is @c STATE_PAUSE_NEVER.
    ///
    /// A typical invocation might look this:
    ///
    /// @code
    ///     State(SOME_INT_VAL, "SOME_INT_VAL",
    ///            std::bind(&StateModelDerivation::someHandler, this));
    /// @endcode
    ///
    /// @throw StateModelError if label is null or blank.
    State(const int value, const std::string& label, StateHandler handler,
          const StatePausing& state_pausing = STATE_PAUSE_NEVER);

    /// @brief Destructor
    virtual ~State();

    /// @brief Invokes the State's handler.
    void run();

    /// @brief Indicates if the state model should pause upon entering
    /// this state.
    ///
    /// It modifies the @c was_paused_ flag if the state model should
    /// pause. That way, it keeps track of visits in this particular state,
    /// making it possible to pause only upon the first transition to the
    /// state when @c STATE_PAUSE_ONCE mode is used.
    bool shouldPause();

private:
    /// @brief Bound instance method pointer to the state's handler method.
    StateHandler handler_;

    /// @brief Specifies selected pausing mode for a state.
    StatePausing pausing_;

    /// @brief Indicates if the state machine was already paused in this
    /// state.
    bool was_paused_;
};

/// @brief Defines a shared pointer to a State.
typedef boost::shared_ptr<State> StatePtr;

/// @brief Implements a unique set or dictionary of states.
///
/// This class provides the means to construct and access a unique set of
/// states.  This provide the ability to validate state values, look up their
/// text labels, and their handlers.
class StateSet : public LabeledValueSet {
public:
    /// @brief Constructor
    StateSet();

    /// @brief Destructor
    virtual ~StateSet();

    /// @brief Adds a state definition to the set of states.
    ///
    /// @param value is the numeric value of the state
    /// @param label is the text label to assign to the state
    /// @param handler is the bound instance method which handles the state's
    /// @param state_pausing state pausing mode for the given state.
    ///
    /// @throw StateModelError if the value is already defined in the set, or
    /// if the label is null or blank.
    void add(const int value, const std::string& label, StateHandler handler,
             const StatePausing& state_pausing);

    /// @brief Fetches a state for the given value.
    ///
    /// @param value the numeric value of the state desired
    ///
    /// @return A constant pointer the State found.
    /// Note, this relies on dynamic cast and cannot return a pointer reference.
    ///
    /// @throw StateModelError if the value is undefined.
    const StatePtr getState(int value);
};

/// @brief Implements a finite state machine.
///
/// StateModel is an abstract class that provides the structure and mechanics
/// of a basic finite state machine.
///
/// The state model implementation used is a very basic approach. The model
/// uses numeric constants to identify events and states, and maintains
/// dictionaries of defined events and states.  Event and state definitions
/// include a text label for logging purposes.  Additionally, each state
/// definition includes a state handler. State handlers are methods which
/// implement the actions that need to occur when the model is "in" a given
/// state.  The implementation provides methods to add entries to and verify
/// the contents of both dictionaries.
///
/// During model execution, the following context is tracked:
///
/// * current state - The current state of the model
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
/// repeats this process until either a NOP_EVT posts or the state changes
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
/// the event and state dictionaries.  The following virtual methods are
/// provided for this:
///
/// * defineEvents - define events
/// * verifyEvents - verifies that the expected events are defined
/// * defineStates - defines states
/// * verifyStates - verifies that the expected states are defined
///
/// The concept behind the verify methods is to provide an initial sanity
/// check of the dictionaries.  This should help avoid using undefined event
/// or state values accidentally.
///
/// These methods are intended to be implemented by each "layer" in a StateModel
/// derivation hierarchy.  This allows each layer to define additional events
/// and states.
///
/// Once the dictionaries have been properly initialized, the startModel method
/// invokes runModel with an event of START_EVT.  From this point forward and
/// until the model reaches the END_ST or fails, it is considered to be
/// "running".  If the model encounters a NOP_EVT then it is "running" and
/// "waiting".   If the model reaches END_ST with an END_EVT it is considered
/// "done".  If the  model fails (END_ST with a FAILED_EVT) it is considered
/// "done" and "failed".  There are several boolean status methods which may
/// be used to check these conditions.
/// Once the model has been started, defining new events or new states is
/// illegal. It is possible to call startModel only once.
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
///
/// The model can be paused in the selected states. The states in which the
/// state model should pause (always or only once) are determined within the
/// @c StateModel::defineStates method. The state handlers can check whether
/// the state machine is paused or not by calling @c StateModel::isModelPaused
/// and act accordingy. Typically, the state handler would simply post the
/// @c NOP_EVT when it finds that the state model is paused. The model
/// remains paused until @c StateModel::unpauseModel is called.
class StateModel {
public:

    //@{ States common to all models.
    /// @brief State that a state model is in immediately after construction.
    static const int NEW_ST = 0;

    /// @brief Final state, all the state model has reached its conclusion.
    static const int END_ST = 1;

    /// @brief Value at which custom states in a derived class should begin.
    static const int SM_DERIVED_STATE_MIN = 11;
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

    /// @brief Value at which custom events in a derived class should begin.
    static const int SM_DERIVED_EVENT_MIN = 11;
    //@}

    /// @brief Constructor
    StateModel();

    /// @brief Destructor
    virtual ~StateModel();

    /// @brief Begins execution of the model.
    ///
    /// This method invokes initDictionaries method to initialize the event
    /// and state dictionaries and then starts the model execution setting
    /// the current state to the given start state, and the event to START_EVT.
    /// This method can be called only once to start the state model.
    ///
    /// @param start_state is the state in which to begin execution.
    ///
    /// @throw StateModelError or others indirectly, as this method calls
    /// dictionary define and verify methods.
    void startModel(const int start_state);

    /// @brief Processes events through the state model
    ///
    /// This method implements the state model "execution loop".  It uses
    /// the given event as the next event to process and begins invoking
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
    /// @note This method is made virtual for the unit tests which require
    /// customizations allowing for more control over the state model
    /// execution.
    ///
    /// @param event is the next event to process
    ///
    /// This method is guaranteed not to throw.
    virtual void runModel(unsigned int event);

    /// @brief Conducts a normal transition to the end of the model.
    ///
    /// This method posts an END_EVT and sets the current state to END_ST.
    /// It should be called by any state handler in the model from which
    /// an exit leads to the model end.  In other words, if the transition
    /// out of a particular state is to the end of the model, that state's
    /// handler should call endModel.
    void endModel();

    /// @brief Unpauses state model.
    void unpauseModel();

    /// @brief An empty state handler.
    ///
    /// This method is primarily used to permit special states, NEW_ST and
    /// END_ST to be included in the state dictionary.  Currently it is an
    /// empty method.
    void nopStateHandler();

protected:

    /// @brief Initializes the event and state dictionaries.
    ///
    /// This method invokes the define and verify methods for both events and
    /// states to initialize their respective dictionaries.
    /// This method can be called only once to initialize the state model.
    ///
    /// @throw StateModelError or others indirectly, as this method calls
    /// dictionary define and verify methods.
    void initDictionaries();

    /// @brief Populates the set of events.
    ///
    /// This method is used to construct the set of valid events. Each class
    /// within a StateModel derivation hierarchy uses this method to add any
    /// events it defines to the set.  Each derivation's implementation must
    /// also call its superclass's implementation.  This allows each class
    /// within the hierarchy to make contributions to the set of defined
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
    ///
    /// This method is called in a thread safe context from
    /// @ref initDictionaries.
    virtual void defineEvents();

    /// @brief Adds an event value and associated label to the set of events.
    ///
    /// This method is called in a thread safe context from @ref defineEvents.
    ///
    /// @param value is the numeric value of the event
    /// @param label is the text label of the event used in log messages and
    /// exceptions.
    ///
    /// @throw StateModelError if the model has already been started, if
    /// the value is already defined, or if the label is empty.
    void defineEvent(unsigned int value, const std::string& label);

    /// @brief Fetches the event referred to by value.
    ///
    /// This method is called in a thread safe context from @ref verifyEvents.
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
    /// is used to verify that all the required events are defined.  If the
    /// event set is determined to be invalid this method should throw a
    /// StateModelError.  As with the defineEvents method, each class within
    /// a StateModel derivation hierarchy must supply an implementation
    /// which calls its superclass's implementation as well as verifying any
    /// events added by the derivation.  Validating an event is accomplished
    /// by simply attempting to fetch an event by its value from the event set.
    /// An example of the derivation's implementation follows:
    ///
    /// @code
    /// void StateModelDerivation::verifyEvents() {
    ///     // Call the superclass implementation.
    ///     StateModelDerivation::verifyEvents();
    ///
    ///     // Verify the events defined by the derivation.
    ///     getEvent(SOME_CUSTOM_EVT_1, "CUSTOM_EVT_1");
    ///     getEvent(SOME_CUSTOM_EVT_2, "CUSTOM_EVT_2");
    ///     :
    /// }
    /// @endcode
    ///
    /// This method is called in a thread safe context from
    /// @ref initDictionaries.
    virtual void verifyEvents();

    /// @brief Populates the set of states.
    ///
    /// This method is used to construct the set of valid states. Each class
    /// within a StateModel derivation hierarchy uses this method to add any
    /// states it defines to the set.  Each derivation's implementation must
    /// also call its superclass's implementation.  This allows each class
    /// within the hierarchy to make contributions to the set of defined
    /// states. Implementations use the method, defineState(), to add state
    /// definitions.  An example of the derivation's implementation follows:
    ///
    /// @code
    /// void StateModelDerivation::defineStates() {
    ///     // Call the superclass implementation.
    ///     StateModelDerivation::defineStates();
    ///
    ///     // Add the states defined by the derivation.
    ///     defineState(SOME_ST, "SOME_ST",
    ///                 std::bind(&StateModelDerivation::someHandler, this));
    ///     :
    /// }
    /// @endcode
    ///
    /// This method is called in a thread safe context from
    /// @ref initDictionaries.
    virtual void defineStates();

    /// @brief Adds an state value and associated label to the set of states.
    ///
    /// This method is called in a thread safe context from @ref defineStates.
    ///
    /// @param value is the numeric value of the state
    /// @param label is the text label of the state used in log messages and
    /// exceptions.
    /// @param handler is the bound instance method which implements the state's
    /// actions.
    /// @param state_pausing pausing mode selected for the given state. The
    /// default value is @c STATE_PAUSE_NEVER.
    ///
    /// @throw StateModelError if the model has already been started, if
    /// the value is already defined, or if the label is empty.
    void defineState(unsigned int value, const std::string& label,
                     StateHandler handler,
                     const StatePausing& state_pausing = STATE_PAUSE_NEVER);

    /// @brief Fetches the state referred to by value.
    ///
    /// @param value is the numeric value of the state desired.
    ///
    /// @return returns a constant pointer to the state if found
    ///
    /// @throw StateModelError if the state is not defined.
    const StatePtr getState(unsigned int value);

    /// @brief Validates the contents of the set of states.
    ///
    /// This method is invoked immediately after the defineStates method and
    /// is used to verify that all the required states are defined.  If the
    /// state set is determined to be invalid this method should throw a
    /// StateModelError.  As with the defineStates method, each class within
    /// a StateModel derivation hierarchy must supply an implementation
    /// which calls its superclass's implementation as well as verifying any
    /// states added by the derivation.  Validating an state is accomplished
    /// by simply attempting to fetch the state by its value from the state set.
    /// An example of the derivation's implementation follows:
    ///
    /// @code
    /// void StateModelDerivation::verifyStates() {
    ///     // Call the superclass implementation.
    ///     StateModelDerivation::verifyStates();
    ///
    ///     // Verify the states defined by the derivation.
    ///     getState(SOME_CUSTOM_EVT_2);
    ///     :
    /// }
    /// @endcode
    ///
    /// This method is called in a thread safe context from
    /// @ref initDictionaries.
    virtual void verifyStates();

    /// @brief Handler for fatal model execution errors.
    ///
    /// This method is called when an unexpected error renders during
    /// model execution, such as a state handler throwing an exception.
    /// It provides derivations an opportunity to act accordingly by setting
    /// the appropriate status or taking other remedial action.   This allows
    /// the model execution loop to remain exception safe.  This default
    /// implementation does nothing.
    ///
    /// @param explanation text detailing the error and state machine context
    virtual void onModelFailure(const std::string& explanation);

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
    ///
    /// @param explanation is text detailing the reason for aborting.
    void abortModel(const std::string& explanation);

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
    /// @param event the numeric event value to post as the next event.
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
    unsigned int getCurrState() const;

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

    /// @brief Returns whether or not the model is paused.
    ///
    /// @return Boolean true if the model is paused, false otherwise.
    bool isModelPaused() const;

    /// @brief Returns whether or not the model failed.
    ///
    /// @return Boolean true if the model has reached the END_ST and the last
    /// event indicates a model violation, FAILED_EVT.
    bool didModelFail() const;

    /// @brief Fetches the label associated with an event value.
    ///
    /// @param event is the numeric event value for which the label is desired.
    ///
    /// @return Returns a string containing the event label or
    /// LabeledValueSet::UNDEFINED_LABEL if the value is undefined.
    std::string getEventLabel(const int event) const;

    /// @brief Fetches the label associated with an state value.
    ///
    /// @param state is the numeric state value for which the label is desired.
    ///
    /// @return Returns a const char* containing the state label or
    /// LabeledValueSet::UNDEFINED_LABEL if the value is undefined.
    std::string getStateLabel(const int state) const;

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

protected:

    /// @brief Fetches the state referred to by value.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param value is the numeric value of the state desired.
    ///
    /// @return returns a constant pointer to the state if found
    ///
    /// @throw StateModelError if the state is not defined.
    const StatePtr getStateInternal(unsigned int value);

private:

    /// @brief Sets the current state to the given state value.
    ///
    /// This updates the model's notion of the current state and is the
    /// state whose handler will be executed on the next iteration of the run
    /// loop.  This is intended primarily for internal use and testing. It is
    /// unlikely that transitioning to a new state without a new event is of
    /// much use.
    /// This method should be called in a thread safe context.
    ///
    /// @param state the new value to assign to the current state.
    ///
    /// @throw StateModelError if the state is invalid.
    void setStateInternal(unsigned int state);

    /// @brief Sets the next event to the given event value.
    ///
    /// This updates the model's notion of the next event and is the
    /// event that will be passed into the current state's handler on the next
    /// iteration of the run loop.
    /// This method should be called in a thread safe context.
    ///
    /// @param event the numeric event value to post as the next event.
    ///
    /// @throw StateModelError if the event is undefined
    void postNextEventInternal(unsigned int event);

    /// @brief Returns whether or not the model is new.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @return Boolean true if the model has not been started.
    bool isModelNewInternal() const;

    /// @brief Fetches the label associated with an event value.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param event is the numeric event value for which the label is desired.
    ///
    /// @return Returns a string containing the event label or
    /// LabeledValueSet::UNDEFINED_LABEL if the value is undefined.
    std::string getEventLabelInternal(const int event) const;

    /// @brief Fetches the label associated with an state value.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param state is the numeric state value for which the label is desired.
    ///
    /// @return Returns a const char* containing the state label or
    /// LabeledValueSet::UNDEFINED_LABEL if the value is undefined.
    std::string getStateLabelInternal(const int state) const;

    /// @brief Convenience method which returns a string rendition of the
    /// current state and next event.
    ///
    /// The string will be of the form:
    ///
    ///   current state: [ {state} {label} ] next event: [ {event} {label} ]
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @return Returns a std::string of the format described above.
    std::string getContextStrInternal() const;

    /// @brief Convenience method which returns a string rendition of the
    /// previous state and last event.
    ///
    /// The string will be of the form:
    ///
    ///   previous state: [ {state} {label} ] last event: [ {event} {label} ]
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @return Returns a std::string of the format described above.
    std::string getPrevContextStrInternal() const;

    /// @brief The dictionary of valid events.
    LabeledValueSet events_;

    /// @brief The dictionary of valid states.
    StateSet states_;

    /// @brief Indicates if the event and state dictionaries have been initted.
    bool dictionaries_initted_;

    /// @brief The current state within the model's state model.
    unsigned int curr_state_;

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

    /// @brief Indicates if the state model is paused.
    bool paused_;

    /// @brief Protects against concurrent transitions.
    boost::shared_ptr<std::mutex> mutex_;
};

/// @brief Defines a pointer to a StateModel.
typedef boost::shared_ptr<StateModel> StateModelPtr;

} // namespace isc::util
} // namespace isc
#endif
