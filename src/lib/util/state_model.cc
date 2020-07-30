// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/state_model.h>
#include <string>

namespace isc {
namespace util {

/********************************** State *******************************/

State::State(const int value, const std::string& label, StateHandler handler,
             const StatePausing& state_pausing)
    : LabeledValue(value, label), handler_(handler), pausing_(state_pausing),
      was_paused_(false) {
}

State::~State() {
}

void
State::run() {
    (handler_)();
}

bool
State::shouldPause() {
    if ((pausing_ == STATE_PAUSE_ALWAYS) ||
        ((pausing_ == STATE_PAUSE_ONCE) && (!was_paused_))) {
        was_paused_ = true;
        return (true);
    }
    return (false);
}

/********************************** StateSet *******************************/

StateSet::StateSet() {
}

StateSet::~StateSet() {
}

void
StateSet::add(const int value, const std::string& label, StateHandler handler,
              const StatePausing& state_pausing) {
    try {
        LabeledValueSet::add(LabeledValuePtr(new State(value, label, handler,
                                                       state_pausing)));
    } catch (const std::exception& ex) {
        isc_throw(StateModelError, "StateSet: cannot add state :" << ex.what());
    }

}

const StatePtr
StateSet::getState(int value) {
    if (!isDefined(value)) {
        isc_throw(StateModelError," StateSet: state is undefined");
    }

    // Since we have to use dynamic casting, to get a state pointer
    // we can't return a reference.
    StatePtr state = boost::dynamic_pointer_cast<State>(get(value));
    return (state);
}

/********************************** StateModel *******************************/


// Common state model states
const int StateModel::NEW_ST;
const int StateModel::END_ST;

const int StateModel::SM_DERIVED_STATE_MIN;

// Common state model events
const int StateModel::NOP_EVT;
const int StateModel::START_EVT;
const int StateModel::END_EVT;
const int StateModel::FAIL_EVT;

const int StateModel::SM_DERIVED_EVENT_MIN;

StateModel::StateModel() : events_(), states_(), dictionaries_initted_(false),
                           curr_state_(NEW_ST), prev_state_(NEW_ST),
                           last_event_(NOP_EVT), next_event_(NOP_EVT),
                           on_entry_flag_(false), on_exit_flag_(false),
                           paused_(false), mutex_(new std::mutex) {
}

StateModel::~StateModel(){
}

void
StateModel::startModel(const int start_state) {
    // Initialize dictionaries of events and states.
    initDictionaries();

    // Set the current state to starting state and enter the run loop.
    setState(start_state);

    // Start running the model.
    runModel(START_EVT);
}

void
StateModel::runModel(unsigned int run_event) {
    /// If the dictionaries aren't built bail out.
    if (!dictionaries_initted_) {
        abortModel("runModel invoked before model has been initialized");
    }

    try {
        // Seed the loop with the given event as the next to process.
        postNextEvent(run_event);
        do {
            // Invoke the current state's handler.  It should consume the
            // next event, then determine what happens next by setting
            // current state and/or the next event.
            getState(curr_state_)->run();

            // Keep going until a handler sets next event to a NOP_EVT.
        } while (!isModelDone() && getNextEvent() != NOP_EVT);
    } catch (const std::exception& ex) {
        // The model has suffered an unexpected exception. This constitutes
        // a model violation and indicates a programmatic shortcoming.
        // In theory, the model should account for all error scenarios and
        // deal with them accordingly.  Transition to END_ST with FAILED_EVT
        // via abortModel.
        abortModel(ex.what());
    }
}

void
StateModel::nopStateHandler() {
}

void
StateModel::initDictionaries() {
    std::lock_guard<std::mutex> lock(*mutex_);
    if (dictionaries_initted_) {
        isc_throw(StateModelError, "Dictionaries already initialized");
    }
    // First let's build and verify the dictionary of events.
    try {
        defineEvents();
        verifyEvents();
    } catch (const std::exception& ex) {
        isc_throw(StateModelError, "Event set is invalid: " << ex.what());
    }

    // Next let's build and verify the dictionary of states.
    try {
        defineStates();
        verifyStates();
    } catch (const std::exception& ex) {
        isc_throw(StateModelError, "State set is invalid: " << ex.what());
    }

    // Record that we are good to go.
    dictionaries_initted_ = true;
}

void
StateModel::defineEvent(unsigned int event_value, const std::string& label) {
    if (!isModelNewInternal()) {
        // Don't allow for self-modifying models.
        isc_throw(StateModelError, "Events may only be added to a new model."
                   << event_value << " - " << label);
    }

    // Attempt to add the event to the set.
    try {
        events_.add(event_value, label);
    } catch (const std::exception& ex) {
        isc_throw(StateModelError, "Error adding event: " << ex.what());
    }
}

const EventPtr&
StateModel::getEvent(unsigned int event_value) {
    if (!events_.isDefined(event_value)) {
        isc_throw(StateModelError,
                  "Event value is not defined:" << event_value);
    }

    return (events_.get(event_value));
}

void
StateModel::defineState(unsigned int state_value, const std::string& label,
                        StateHandler handler, const StatePausing& state_pausing) {
    if (!isModelNewInternal()) {
        // Don't allow for self-modifying maps.
        isc_throw(StateModelError, "States may only be added to a new model."
                   << state_value << " - " << label);
    }

    // Attempt to add the state to the set.
    try {
        states_.add(state_value, label, handler, state_pausing);
    } catch (const std::exception& ex) {
        isc_throw(StateModelError, "Error adding state: " << ex.what());
    }
}

const StatePtr
StateModel::getState(unsigned int state_value) {
    std::lock_guard<std::mutex> lock(*mutex_);
    return getStateInternal(state_value);
}

const StatePtr
StateModel::getStateInternal(unsigned int state_value) {
    if (!states_.isDefined(state_value)) {
        isc_throw(StateModelError,
                  "State value is not defined:" << state_value);
    }

    return (states_.getState(state_value));
}

void
StateModel::defineEvents() {
    defineEvent(NOP_EVT, "NOP_EVT");
    defineEvent(START_EVT, "START_EVT");
    defineEvent(END_EVT, "END_EVT");
    defineEvent(FAIL_EVT, "FAIL_EVT");
}

void
StateModel::verifyEvents() {
    getEvent(NOP_EVT);
    getEvent(START_EVT);
    getEvent(END_EVT);
    getEvent(FAIL_EVT);
}

void
StateModel::defineStates() {
    defineState(NEW_ST, "NEW_ST",
                std::bind(&StateModel::nopStateHandler, this));
    defineState(END_ST, "END_ST",
                std::bind(&StateModel::nopStateHandler, this));
}

void
StateModel::verifyStates() {
    getStateInternal(NEW_ST);
    getStateInternal(END_ST);
}

void
StateModel::onModelFailure(const std::string&) {
    // Empty implementation to make deriving classes simpler.
}

void
StateModel::transition(unsigned int state, unsigned int event) {
    std::lock_guard<std::mutex> lock(*mutex_);
    setStateInternal(state);
    postNextEventInternal(event);
}

void
StateModel::endModel() {
    transition(END_ST, END_EVT);
}

void
StateModel::unpauseModel() {
    std::lock_guard<std::mutex> lock(*mutex_);
    paused_ = false;
}

void
StateModel::abortModel(const std::string& explanation) {
    transition(END_ST, FAIL_EVT);

    std::ostringstream stream ;
    stream << explanation << " : " << getContextStr();
    onModelFailure(stream.str());
}

void
StateModel::setState(unsigned int state) {
    std::lock_guard<std::mutex> lock(*mutex_);
    setStateInternal(state);
}

void
StateModel::setStateInternal(unsigned int state) {
    if (state != END_ST && !states_.isDefined(state)) {
        isc_throw(StateModelError,
                  "Attempt to set state to an undefined value: " << state );
    }

    prev_state_ = curr_state_;
    curr_state_ = state;

    // Set the "do" flags if we are transitioning.
    on_entry_flag_ = ((state != END_ST) && (prev_state_ != curr_state_));

    // At this time they are calculated the same way.
    on_exit_flag_ = on_entry_flag_;

    // If we're entering the new state we need to see if we should
    // pause the state model in this state.
    if (on_entry_flag_ && !paused_ && getStateInternal(state)->shouldPause()) {
        paused_ = true;
    }
}

void
StateModel::postNextEvent(unsigned int event_value) {
    std::lock_guard<std::mutex> lock(*mutex_);
    postNextEventInternal(event_value);
}

void
StateModel::postNextEventInternal(unsigned int event_value) {
    // Check for FAIL_EVT as special case of model error before events are
    // defined.
    if (event_value != FAIL_EVT && !events_.isDefined(event_value)) {
        isc_throw(StateModelError,
                  "Attempt to post an undefined event, value: " << event_value);
    }

    last_event_ = next_event_;
    next_event_ = event_value;
}

bool
StateModel::doOnEntry() {
    std::lock_guard<std::mutex> lock(*mutex_);
    bool ret = on_entry_flag_;
    on_entry_flag_ = false;
    return (ret);
}

bool
StateModel::doOnExit() {
    std::lock_guard<std::mutex> lock(*mutex_);
    bool ret = on_exit_flag_;
    on_exit_flag_ = false;
    return (ret);
}

unsigned int
StateModel::getCurrState() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return (curr_state_);
}

unsigned int
StateModel::getPrevState() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return (prev_state_);
}

unsigned int
StateModel::getLastEvent() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return (last_event_);
}

unsigned int
StateModel::getNextEvent() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return (next_event_);
}

bool
StateModel::isModelNew() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return isModelNewInternal();
}

bool
StateModel::isModelNewInternal() const {
    return (curr_state_ == NEW_ST);
}

bool
StateModel::isModelRunning() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return ((curr_state_ != NEW_ST) && (curr_state_ != END_ST));
}

bool
StateModel::isModelWaiting() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return ((curr_state_ != NEW_ST) && (curr_state_ != END_ST) &&
            (next_event_ == NOP_EVT));
}

bool
StateModel::isModelDone() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return (curr_state_ == END_ST);
}

bool
StateModel::didModelFail() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return ((curr_state_ == END_ST) && (next_event_ == FAIL_EVT));
}

bool
StateModel::isModelPaused() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return (paused_);
}

std::string
StateModel::getStateLabel(const int state) const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return getStateLabelInternal(state);
}

std::string
StateModel::getStateLabelInternal(const int state) const {
    return (states_.getLabel(state));
}

std::string
StateModel::getEventLabel(const int event) const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return getEventLabelInternal(event);
}

std::string
StateModel::getEventLabelInternal(const int event) const {
    return (events_.getLabel(event));
}

std::string
StateModel::getContextStr() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    std::ostringstream stream;
    stream << "current state: [ "
            << curr_state_ << " " << getStateLabelInternal(curr_state_)
            << " ] next event: [ "
            << next_event_ << " " << getEventLabelInternal(next_event_) << " ]";
    return (stream.str());
}

std::string
StateModel::getPrevContextStr() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    std::ostringstream stream;
    stream << "previous state: [ "
           << prev_state_ << " " << getStateLabelInternal(prev_state_)
           << " ] last event: [ "
           << next_event_ << " " << getEventLabelInternal(last_event_) << " ]";
    return (stream.str());
}

} // namespace isc::util
} // namespace isc
