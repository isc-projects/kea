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

#include <d2/d2_log.h>
#include <d2/state_model.h>

#include <string>

namespace isc {
namespace d2 {

// Common state model states
const int StateModel::NEW_ST;
const int StateModel::END_ST;

const int StateModel::SM_STATE_MAX;

// Common state model events
const int StateModel::NOP_EVT;
const int StateModel::START_EVT;
const int StateModel::END_EVT;
const int StateModel::FAIL_EVT;

const int StateModel::SM_EVENT_MAX;

StateModel::StateModel() : state_handlers_(), state_(NEW_ST),
                          prev_state_(NEW_ST), last_event_(NOP_EVT),
                          next_event_(NOP_EVT), on_entry_flag_(false),
                          on_exit_flag_(false) {
}

StateModel::~StateModel(){
}

void
StateModel::startModel(const int start_state) {
    // Initialize the state handler map first.
    initStateHandlerMap();

    // Test validity of the handler map. This provides an opportunity to
    // sanity check the map prior to attempting to execute the model.
    verifyStateHandlerMap();

    // Set the current state to startng state and enter the run loop.
    setState(start_state);
    runModel(START_EVT);
}

void
StateModel::runModel(unsigned int run_event) {
    try {
        // Seed the loop with the given event as the next to process.
        postNextEvent(run_event);
        do {
            // Invoke the current state's handler.  It should consume the
            // next event, then determine what happens next by setting
            // current state and/or the next event.
            (getStateHandler(state_))();

            // Keep going until a handler sets next event to a NOP_EVT.
        } while (!isModelDone() && getNextEvent() != NOP_EVT);
    }
    catch (const std::exception& ex) {
        // The model has suffered an unexpected exception. This constitutes a
        // a model violation and indicates a programmatic shortcoming.
        // In theory, the model should account for all error scenarios and
        // deal with them accordingly.  Log it and transition to END_ST with
        // FAILED_EVT via abortModel.
        LOG_ERROR(dctl_logger, DHCP_DDNS_STATE_MODEL_UNEXPECTED_ERROR)
                  .arg(ex.what()).arg(getContextStr());
        abortModel();
    }
}

StateHandler
StateModel::getStateHandler(unsigned int state) {
    StateHandlerMap::iterator it = state_handlers_.find(state);
    // It is wrong to try to find a state that isn't mapped.
    if (it == state_handlers_.end()) {
        isc_throw(StateModelError, "No handler for state: "
                  << state << " - " << getStateLabel(state));
    }

    return ((*it).second);
}

void
StateModel::addToMap(unsigned int state, StateHandler handler) {
    StateHandlerMap::iterator it = state_handlers_.find(state);
    // Check for a duplicate attempt.  State's can't have more than one.
    if (it != state_handlers_.end()) {
        isc_throw(StateModelError,
                  "Attempted duplicate entry in state handler map, state: "
                   << state << " - " << getStateLabel(state));
    }

    // Do not allow handlers for special states fo NEW_ST and END_ST.
    if (state == NEW_ST || state == END_ST) {
        isc_throw(StateModelError, "A handler is not supported for state: "
                  << state << " - " << getStateLabel(state));
    }

    state_handlers_[state] = handler;
}

void
StateModel::transition(unsigned int state, unsigned int event) {
    setState(state);
    postNextEvent(event);
}

void
StateModel::endModel() {
    transition(END_ST, END_EVT);
}

void
StateModel::abortModel() {
    transition(END_ST, FAIL_EVT);
    onModelFailure();
}

void
StateModel::setState(unsigned int state) {
    // If the new state isn't NEW_ST or END_ST, make sure it has a handler.
    if ((state && state != NEW_ST && state != END_ST)
        && (state_handlers_.end() == state_handlers_.find(state))) {
        isc_throw(StateModelError, "Attempt to set state to invalid stat :"
                  << state << "=" << getStateLabel(state));
    }

    prev_state_ = state_;
    state_ = state;

    // Set the "do" flags if we are transitioning.
    on_entry_flag_ = ((state != END_ST) && (prev_state_ != state_));
    // At this time they are calculated the same way.
    on_exit_flag_ = on_entry_flag_;
}

void
StateModel::postNextEvent(unsigned int event) {
    last_event_ = next_event_;
    next_event_ = event;
}

bool
StateModel::doOnEntry() {
    bool ret = on_entry_flag_;
    on_entry_flag_ = false;
    return (ret);
}

bool
StateModel::doOnExit() {
    bool ret = on_exit_flag_;
    on_exit_flag_ = false;
    return (ret);
}

unsigned int
StateModel::getState() const {
    return (state_);
}

unsigned int
StateModel::getPrevState() const {
    return (prev_state_);
}

unsigned int
StateModel::getLastEvent() const {
    return (last_event_);
}

unsigned int
StateModel::getNextEvent() const {
    return (next_event_);
}
bool
StateModel::isModelNew() const {
    return (state_ == NEW_ST);
}

bool
StateModel::isModelRunning() const {
    return ((state_ != NEW_ST) && (state_ != END_ST));
}

bool
StateModel::isModelWaiting() const {
    return (isModelRunning() && (next_event_ == NOP_EVT));
}

bool
StateModel::isModelDone() const {
    return (state_ == END_ST);
}

bool
StateModel::didModelFail() const {
    return (isModelDone() && (next_event_ == FAIL_EVT));
}

const char*
StateModel::getStateLabel(const int state) const {
    const char* str = "Unknown";
    switch(state) {
    case NEW_ST:
        str = "StateModel::NEW_ST";
        break;
    case END_ST:
        str = "StateModel::END_ST";
        break;
    default:
        break;
    }

    return (str);
}

std::string
StateModel::getContextStr() const {
    std::ostringstream stream;
    stream << "current state: [ "
            << state_ << " " << getStateLabel(state_)
            << " ] next event: [ "
            << next_event_ << " " << getEventLabel(next_event_) << " ]";
    return(stream.str());
}

std::string
StateModel::getPrevContextStr() const {
    std::ostringstream stream;
    stream << "previous state: [ "
           << prev_state_ << " " << getStateLabel(prev_state_)
           << " ] last event: [ "
           << next_event_ << " " << getEventLabel(last_event_) << " ]";
    return(stream.str());
}

const char*
StateModel::getEventLabel(const int event) const {
    const char* str = "Unknown";
    switch(event) {
    case NOP_EVT:
        str = "StateModel::NOP_EVT";
        break;
    case START_EVT:
        str = "StateModel::START_EVT";
        break;
    case END_EVT:
        str = "StateModel::END_EVT";
        break;
    case FAIL_EVT:
        str = "StateModel::FAIL_EVT";
        break;
    default:
        break;
    }

    return (str);
}

} // namespace isc::d2
} // namespace isc
