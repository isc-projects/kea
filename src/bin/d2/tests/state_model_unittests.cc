// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/state_model.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace {

/// @brief Test derivation of StateModel for exercising state model mechanics.
///
/// This class facilitates testing by making non-public methods accessible so
/// they can be invoked directly in test routines.  It implements a very
/// rudimentary state model, sufficient to test the state model mechanics
/// supplied by the base class.
class StateModelTest : public StateModel, public testing::Test {
public:

    ///@brief StateModelTest states
    ///@brief Fake state used for handler mapping tests.
    static const int DUMMY_ST = SM_DERIVED_STATE_MIN + 1;

    ///@brief Starting state for the test state model.
    static const int READY_ST = SM_DERIVED_STATE_MIN + 2;

    ///@brief State which simulates doing asynchronous work.
    static const int DO_WORK_ST = SM_DERIVED_STATE_MIN + 3;

    ///@brief State which finishes off processing.
    static const int DONE_ST = SM_DERIVED_STATE_MIN + 4;

    // StateModelTest events
    ///@brief Event used to trigger initiation of asynchronous work.
    static const int WORK_START_EVT = SM_DERIVED_EVENT_MIN + 1;

    ///@brief Event issued when the asynchronous work "completes".
    static const int WORK_DONE_EVT = SM_DERIVED_EVENT_MIN + 2;

    ///@brief Event issued when all the work is done.
    static const int ALL_DONE_EVT = SM_DERIVED_EVENT_MIN + 3;

    ///@brief Event used to trigger an attempt to transition to bad state
    static const int FORCE_UNDEFINED_ST_EVT = SM_DERIVED_EVENT_MIN + 4;

    ///@brief Event used to trigger an attempt to transition to bad state
    static const int SIMULATE_ERROR_EVT = SM_DERIVED_EVENT_MIN + 5;

    /// @brief Constructor
    ///
    /// Parameters match those needed by StateModel.
    StateModelTest() : dummy_called_(false), work_completed_(false),
                       failure_explanation_("") {
    }
    /// @brief Destructor
    virtual ~StateModelTest() {
    }

    /// @brief Fetches the value of the dummy called flag.
    bool getDummyCalled() {
        return (dummy_called_);
    }

    /// @brief StateHandler for fake state, DummyState.
    ///
    /// It simply sets the dummy called flag to indicate that this method
    /// was invoked.
    void dummyHandler() {
        dummy_called_ = true;
    }

    /// @brief Returns the failure explanation string.
    ///
    /// This value is set only via onModelFailure and it stores whatever
    /// explanation that method was passed.
    const std::string& getFailureExplanation() {
        return (failure_explanation_);
    }

    /// @brief Returns indication of whether or not the model succeeded.
    ///
    /// If true, this indicates that the test model executed correctly through
    /// to completion.  The flag is only by the DONE_ST handler.
    bool getWorkCompleted() {
        return (work_completed_);
    }

    /// @brief State handler for the READY_ST.
    ///
    /// Serves as the starting state handler, it consumes the
    /// START_EVT "transitioning" to the state, DO_WORK_ST and
    /// sets the next event to WORK_START_EVT.
    void readyHandler() {
        switch(getNextEvent()) {
        case START_EVT:
            transition(DO_WORK_ST, WORK_START_EVT);
            break;
        default:
            // its bogus
            isc_throw(StateModelError, "readyHandler:invalid event: "
                      << getContextStr());
        }
    }

    /// @brief State handler for the DO_WORK_ST.
    ///
    /// Simulates a state that starts some form of asynchronous work.
    /// When next event is WORK_START_EVT it sets the status to pending
    /// and signals the state model must "wait" for an event by setting
    /// next event to NOP_EVT.
    ///
    /// When next event is IO_COMPLETED_EVT, it transitions to the state,
    /// DONE_ST, and sets the next event to WORK_DONE_EVT.
    void doWorkHandler() {
        switch(getNextEvent()) {
        case WORK_START_EVT:
            postNextEvent(NOP_EVT);
            break;
        case WORK_DONE_EVT:
            work_completed_ = true;
            transition(DONE_ST, ALL_DONE_EVT);
            break;
        case FORCE_UNDEFINED_ST_EVT:
            transition(9999, ALL_DONE_EVT);
            break;
        case SIMULATE_ERROR_EVT:
            throw std::logic_error("Simulated Unexpected Error");
            break;
        default:
            // its bogus
            isc_throw(StateModelError, "doWorkHandler:invalid event: "
                      <<  getContextStr());
        }
    }

    /// @brief State handler for the DONE_ST.
    ///
    /// This is the last state in the model.  Note that it sets the
    /// status to completed and next event to NOP_EVT.
    void doneWorkHandler() {
        switch(getNextEvent()) {
        case ALL_DONE_EVT:
            endModel();
            break;
        default:
            // its bogus
            isc_throw(StateModelError, "doneWorkHandler:invalid event: "
                      << getContextStr());
        }
    }

    /// @brief Construct the event dictionary.
    virtual void defineEvents() {
        // Invoke the base call implementation first.
        StateModel::defineEvents();

        // Define our events.
        defineEvent(WORK_START_EVT, "WORK_START_EVT");
        defineEvent(WORK_DONE_EVT , "WORK_DONE_EVT");
        defineEvent(ALL_DONE_EVT, "ALL_DONE_EVT");
        defineEvent(FORCE_UNDEFINED_ST_EVT, "FORCE_UNDEFINED_ST_EVT");
        defineEvent(SIMULATE_ERROR_EVT, "SIMULATE_ERROR_EVT");
    }

    /// @brief Verify the event dictionary.
    virtual void verifyEvents() {
        // Invoke the base call implementation first.
        StateModel::verifyEvents();

        // Verify our events.
        getEvent(WORK_START_EVT);
        getEvent(WORK_DONE_EVT);
        getEvent(ALL_DONE_EVT);
        getEvent(FORCE_UNDEFINED_ST_EVT);
        getEvent(SIMULATE_ERROR_EVT);
    }

    /// @brief Construct the state dictionary.
    virtual void defineStates() {
        // Invoke the base call implementation first.
        StateModel::defineStates();

        // Define our states.
        defineState(DUMMY_ST, "DUMMY_ST",
                    boost::bind(&StateModelTest::dummyHandler, this));

        defineState(READY_ST, "READY_ST",
            boost::bind(&StateModelTest::readyHandler, this));

        defineState(DO_WORK_ST, "DO_WORK_ST",
            boost::bind(&StateModelTest::doWorkHandler, this));

        defineState(DONE_ST, "DONE_ST",
            boost::bind(&StateModelTest::doneWorkHandler, this));
    }

    /// @brief Verify the state dictionary.
    virtual void verifyStates() {
        // Invoke the base call implementation first.
        StateModel::verifyStates();

        // Verify our states.
        getState(DUMMY_ST);
        getState(READY_ST);
        getState(DO_WORK_ST);
        getState(DONE_ST);
    }

    /// @brief  Manually construct the event and state dictionaries.
    /// This allows testing without running startModel.
    void initDictionaires() {
        ASSERT_NO_THROW(defineEvents());
        ASSERT_NO_THROW(verifyEvents());
        ASSERT_NO_THROW(defineStates());
        ASSERT_NO_THROW(verifyStates());
    }

    /// @brief Tests the event dictionary entry for the given event value.
    bool checkEvent(const int value, const std::string& label) {
        EventPtr event;
        try  {
            event = getEvent(value);
            EXPECT_TRUE(event);
            EXPECT_EQ(value, event->getValue());
            EXPECT_EQ(label, event->getLabel());
        } catch (const std::exception& ex) {
            return false;
        }

        return true;
    }

    /// @brief Tests the state dictionary entry for the given state value.
    bool checkState(const int value, const std::string& label) {
        EventPtr state;
        try  {
            state = getState(value);
            EXPECT_TRUE(state);
            EXPECT_EQ(value, state->getValue());
            EXPECT_EQ(label, state->getLabel());
        } catch (const std::exception& ex) {
            return false;
        }

        return true;
    }


    /// @brief  Handler called when the model suffers an execution error.
    virtual void onModelFailure(const std::string& explanation) {
        failure_explanation_ = explanation;
    }

    /// @brief Indicator of whether or not the DUMMY_ST handler has been called.
    bool dummy_called_;

    /// @brief Indicator of whether or not DONE_ST handler has been called.
    bool work_completed_;

    /// @brief Stores the failure explanation
    std::string failure_explanation_;
};

// Declare them so gtest can see them.
const int StateModelTest::DUMMY_ST;
const int StateModelTest::READY_ST;
const int StateModelTest::DO_WORK_ST;
const int StateModelTest::DONE_ST;
const int StateModelTest::WORK_START_EVT;
const int StateModelTest::WORK_DONE_EVT;
const int StateModelTest::ALL_DONE_EVT;

/// @brief Checks the fundamentals of defining and retrieving events.
TEST_F(StateModelTest, eventDefinition) {
    // After construction, the event dictionary should be empty. Verify that
    // getEvent will throw when event is not defined.
    EXPECT_THROW(getEvent(NOP_EVT), StateModelError);

    // Verify that we can add a handler to the map.
    ASSERT_NO_THROW(defineEvent(NOP_EVT, "NOP_EVT"));

    // Verify that we can find the event by value and its content is correct.
    EXPECT_TRUE(checkEvent(NOP_EVT, "NOP_EVT"));

    // Verify that we cannot add a duplicate.
    ASSERT_THROW(defineEvent(NOP_EVT, "NOP_EVT"), StateModelError);

    // Verify that we can still find the event.
    EXPECT_TRUE(checkEvent(NOP_EVT, "NOP_EVT"));
}

/// @brief Tests event dictionary construction and verification.
TEST_F(StateModelTest, eventDictionary) {
    // After construction, the event dictionary should be empty.
    // Make sure that verifyEvents() throws.
    EXPECT_THROW(verifyEvents(), StateModelError);

    // Construct the dictionary and verify it.
    EXPECT_NO_THROW(defineEvents());
    EXPECT_NO_THROW(verifyEvents());

    // Verify base class events are defined.
    EXPECT_TRUE(checkEvent(NOP_EVT, "NOP_EVT"));
    EXPECT_TRUE(checkEvent(START_EVT, "START_EVT"));
    EXPECT_TRUE(checkEvent(END_EVT, "END_EVT"));
    EXPECT_TRUE(checkEvent(FAIL_EVT, "FAIL_EVT"));

    // Verify stub class events are defined.
    EXPECT_TRUE(checkEvent(WORK_START_EVT, "WORK_START_EVT"));
    EXPECT_TRUE(checkEvent(WORK_DONE_EVT, "WORK_DONE_EVT"));
    EXPECT_TRUE(checkEvent(ALL_DONE_EVT, "ALL_DONE_EVT"));
    EXPECT_TRUE(checkEvent(FORCE_UNDEFINED_ST_EVT, "FORCE_UNDEFINED_ST_EVT"));
    EXPECT_TRUE(checkEvent(SIMULATE_ERROR_EVT, "SIMULATE_ERROR_EVT"));

    // Verify that undefined events are handled correctly.
    EXPECT_THROW(getEvent(9999), StateModelError);
    EXPECT_EQ(LabeledValueSet::UNDEFINED_LABEL, getEventLabel(9999));
}

/// @brief General testing of event context accessors.
/// Most if not all of these are also tested as a byproduct off larger tests.
TEST_F(StateModelTest, eventContextAccessors) {
    // Construct the event definitions, normally done by startModel.
    ASSERT_NO_THROW(defineEvents());
    ASSERT_NO_THROW(verifyEvents());

    // Verify the post-construction values.
    EXPECT_EQ(NOP_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call setEvent which will update both next event and last event.
    EXPECT_NO_THROW(postNextEvent(START_EVT));

    // Verify the values are what we expect.
    EXPECT_EQ(START_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call setEvent again.
    EXPECT_NO_THROW(postNextEvent(WORK_START_EVT));

    // Verify the values are what we expect.
    EXPECT_EQ(WORK_START_EVT, getNextEvent());
    EXPECT_EQ(START_EVT, getLastEvent());

    // Verify that posting an undefined event throws.
    EXPECT_THROW(postNextEvent(9999), StateModelError);
}

/// @brief Tests the fundamental methods used for state handler mapping.
/// Verifies the ability to search for and add entries in the state handler map.
TEST_F(StateModelTest, stateDefinition) {
    // After construction, the state dictionary should be empty. Verify that
    // getState will throw when, state is not defined.
    EXPECT_THROW(getState(READY_ST), StateModelError);

    // Verify that we can add a state to the dictionary.
    ASSERT_NO_THROW(defineState(READY_ST, "READY_ST",
                                boost::bind(&StateModelTest::dummyHandler,
                                            this)));

    // Verify that we can find the state by its value.
    StatePtr state;
    EXPECT_NO_THROW(state = getState(READY_ST));
    EXPECT_TRUE(state);

    // Verify the state's value and label.
    EXPECT_EQ(READY_ST, state->getValue());
    EXPECT_EQ("READY_ST", state->getLabel());

    // Now verify that retrieved state's handler executes the correct method.
    // Make sure the dummy called flag is false prior to invocation.
    EXPECT_FALSE(getDummyCalled());

    // Invoke the state's handler.
    EXPECT_NO_THROW(state->run());

    // Verify the dummy called flag is now true.
    EXPECT_TRUE(getDummyCalled());

    // Verify that we cannot add a duplicate.
    EXPECT_THROW(defineState(READY_ST, "READY_ST",
                             boost::bind(&StateModelTest::readyHandler, this)),
                 StateModelError);

    // Verify that we can still find the state.
    EXPECT_NO_THROW(getState(READY_ST));
}

/// @brief Tests state dictionary initialization and validation.
/// This tests the basic concept of state dictionary initialization and
/// verification by manually invoking the methods normally called by startModel.
TEST_F(StateModelTest, stateDictionary) {
    // Verify that the map validation throws prior to the dictionary being
    // initialized.
    EXPECT_THROW(verifyStates(), StateModelError);

    // Construct the dictionary and verify it.
    ASSERT_NO_THROW(defineStates());
    EXPECT_NO_THROW(verifyStates());

    // Verify the base class states.
    EXPECT_TRUE(checkState(NEW_ST, "NEW_ST"));
    EXPECT_TRUE(checkState(END_ST, "END_ST"));

    // Verify stub class states.
    EXPECT_TRUE(checkState(DUMMY_ST, "DUMMY_ST"));
    EXPECT_TRUE(checkState(READY_ST, "READY_ST"));
    EXPECT_TRUE(checkState(DO_WORK_ST, "DO_WORK_ST"));
    EXPECT_TRUE(checkState(DONE_ST, "DONE_ST"));

    // Verify that undefined states are handled correctly.
    EXPECT_THROW(getState(9999), StateModelError);
    EXPECT_EQ(LabeledValueSet::UNDEFINED_LABEL, getStateLabel(9999));
}

/// @brief General testing of state context accessors.
/// Most if not all of these are also tested as a byproduct off larger tests.
TEST_F(StateModelTest, stateContextAccessors) {
    // setState will throw unless we initialize the handler map.
    ASSERT_NO_THROW(defineStates());
    ASSERT_NO_THROW(verifyStates());

    // Verify post-construction state values.
    EXPECT_EQ(NEW_ST, getCurrState());
    EXPECT_EQ(NEW_ST, getPrevState());

    // Call setState which will update both state and previous state.
    EXPECT_NO_THROW(setState(READY_ST));

    // Verify the values are what we expect.
    EXPECT_EQ(READY_ST, getCurrState());
    EXPECT_EQ(NEW_ST, getPrevState());

    // Call setState again.
    EXPECT_NO_THROW(setState(DO_WORK_ST));

    // Verify the values are what we expect.
    EXPECT_EQ(DO_WORK_ST, getCurrState());
    EXPECT_EQ(READY_ST, getPrevState());

    // Verify that calling setState with an state that has no handler
    // will throw.
    EXPECT_THROW(setState(-1), StateModelError);

    // Verify that calling setState with NEW_ST is ok.
    EXPECT_NO_THROW(setState(NEW_ST));

    // Verify that calling setState with END_ST is ok.
    EXPECT_NO_THROW(setState(END_ST));

    // Verify that calling setState with an undefined state throws.
    EXPECT_THROW(setState(9999), StateModelError);
}

/// @brief Checks that invoking runModel prior to startModel is not allowed.
TEST_F(StateModelTest, runBeforeStart) {
    // Verify that the failure explanation is empty and work is not done.
    EXPECT_TRUE(getFailureExplanation().empty());

    // Attempt to call runModel before startModel.  This should result in an
    // orderly model failure.
    ASSERT_NO_THROW(runModel(START_EVT));

    // Check that state and event are correct.
    EXPECT_EQ(END_ST, getCurrState());
    EXPECT_EQ(FAIL_EVT, getNextEvent());

    // Verify that failure explanation is not empty.
    EXPECT_FALSE(getFailureExplanation().empty());
}

/// @brief Tests that the endModel may be used to transition the model to
/// a normal conclusion.
TEST_F(StateModelTest, transitionWithEnd) {
    // Init dictionaries manually, normally done by startModel.
    initDictionaires();

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    //  Verify that state and event members are as expected.
    EXPECT_EQ(DUMMY_ST, getCurrState());
    EXPECT_EQ(NEW_ST, getPrevState());
    EXPECT_EQ(START_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call endModel to transition us to the end of the model.
    EXPECT_NO_THROW(endModel());

    // Verify state and event members are correctly set.
    EXPECT_EQ(END_ST, getCurrState());
    EXPECT_EQ(DUMMY_ST, getPrevState());
    EXPECT_EQ(END_EVT, getNextEvent());
    EXPECT_EQ(START_EVT, getLastEvent());
}

/// @brief Tests that the abortModel may be used to transition the model to
/// failed conclusion.
TEST_F(StateModelTest, transitionWithAbort) {
    // Init dictionaries manually, normally done by startModel.
    initDictionaires();

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    //  Verify that state and event members are as expected.
    EXPECT_EQ(DUMMY_ST, getCurrState());
    EXPECT_EQ(NEW_ST, getPrevState());
    EXPECT_EQ(START_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call endModel to transition us to the end of the model.
    EXPECT_NO_THROW(abortModel("test invocation"));

    // Verify state and event members are correctly set.
    EXPECT_EQ(END_ST, getCurrState());
    EXPECT_EQ(DUMMY_ST, getPrevState());
    EXPECT_EQ(FAIL_EVT, getNextEvent());
    EXPECT_EQ(START_EVT, getLastEvent());
}

/// @brief Tests that the boolean indicators for on state entry and exit
/// work properly.
TEST_F(StateModelTest, doFlags) {
    // Init dictionaries manually, normally done by startModel.
    initDictionaires();

    // Verify that "do" flags are false.
    EXPECT_FALSE(doOnEntry());
    EXPECT_FALSE(doOnExit());

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    // We are transitioning states, so "do" flags should be true.
    EXPECT_TRUE(doOnEntry());
    EXPECT_TRUE(doOnExit());

    // "do" flags are one-shots, so they should now both be false.
    EXPECT_FALSE(doOnEntry());
    EXPECT_FALSE(doOnExit());

    // call transition to re-enter same state, "do" flags should be false.
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    // "do" flags should be false.
    EXPECT_FALSE(doOnEntry());
    EXPECT_FALSE(doOnExit());

}

/// @brief Verifies that the model status methods accurately reflect the model
/// status.  It also verifies that the dictionaries can be modified before
/// the model is running but not after.
TEST_F(StateModelTest, statusMethods) {
    // Init dictionaries manually, normally done by startModel.
    initDictionaires();

    // After construction, state model is "new", all others should be false.
    EXPECT_TRUE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_FALSE(isModelDone());
    EXPECT_FALSE(didModelFail());

    // Verify that events and states can be added before the model is started.
    EXPECT_NO_THROW(defineEvent(9998, "9998"));
    EXPECT_NO_THROW(defineState(9998, "9998",
                                boost::bind(&StateModelTest::readyHandler,
                                            this)));

    // "START" the model.
    // Fake out starting the model by calling transition to move from NEW_ST
    // to DUMMY_ST with START_EVT.  If we used startModel this would blow by
    // the status  of "running" but not "waiting".
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));


    // Verify that events and states cannot be added after the model is started.
    EXPECT_THROW(defineEvent(9999, "9999"), StateModelError);
    EXPECT_THROW(defineState(9999, "9999",
                             boost::bind(&StateModelTest::readyHandler, this)),
                 StateModelError);

    // The state and event combos set above, should show the model as
    // "running", all others should be false.
    EXPECT_FALSE(isModelNew());
    EXPECT_TRUE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_FALSE(isModelDone());
    EXPECT_FALSE(didModelFail());

    // call transition to submit NOP_EVT to current state, DUMMY_ST.
    EXPECT_NO_THROW(transition(DUMMY_ST, NOP_EVT));

    // Verify the status methods are correct: with next event set to NOP_EVT,
    // model should be "running" and "waiting".
    EXPECT_FALSE(isModelNew());
    EXPECT_TRUE(isModelRunning());
    EXPECT_TRUE(isModelWaiting());
    EXPECT_FALSE(isModelDone());
    EXPECT_FALSE(didModelFail());

    // Call endModel to transition us to the end of the model.
    EXPECT_NO_THROW(endModel());

    // With state set to END_ST, model should be done.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_FALSE(didModelFail());
}

/// @brief Tests that the model status methods are correct after a model
/// failure.
TEST_F(StateModelTest, statusMethodsOnFailure) {
    // Construct the event and state definitions, normally done by startModel.
    ASSERT_NO_THROW(defineEvents());
    ASSERT_NO_THROW(verifyEvents());
    ASSERT_NO_THROW(defineStates());
    ASSERT_NO_THROW(verifyStates());

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    // Call endModel to transition us to the end of the model.
    EXPECT_NO_THROW(abortModel("test invocation"));

    // With state set to END_ST, model should be done.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_TRUE(didModelFail());
}

/// @brief Checks that the context strings accurately reflect context and
/// are safe to invoke.
TEST_F(StateModelTest, contextStrs) {
    // Verify context methods do not throw prior to dictionary init.
    ASSERT_NO_THROW(getContextStr());
    ASSERT_NO_THROW(getPrevContextStr());

    // Construct the event and state definitions, normally done by startModel.
    ASSERT_NO_THROW(defineEvents());
    ASSERT_NO_THROW(verifyEvents());
    ASSERT_NO_THROW(defineStates());
    ASSERT_NO_THROW(verifyStates());

    // transition uses setState and setEvent, testing it tests all three.
    EXPECT_NO_THROW(transition(READY_ST, START_EVT));

    // Verify the current context string depicts correct state and event.
    std::string ctx_str;
    ASSERT_NO_THROW(ctx_str = getContextStr());
    EXPECT_NE(std::string::npos, ctx_str.find(getStateLabel(READY_ST)));
    EXPECT_NE(std::string::npos, ctx_str.find(getEventLabel(START_EVT)));

    // Verify the previous context string depicts correct state and event.
    ASSERT_NO_THROW(ctx_str = getPrevContextStr());
    EXPECT_NE(std::string::npos, ctx_str.find(getStateLabel(NEW_ST)));
    EXPECT_NE(std::string::npos, ctx_str.find(getEventLabel(NOP_EVT)));
}

/// @brief Tests that undefined states are handled gracefully.
/// This test verifies that attempting to transition to an undefined state,
/// which constitutes a model violation, results in an orderly model failure.
TEST_F(StateModelTest, undefinedState) {
    // Verify that the failure explanation is empty and work is not done.
    EXPECT_TRUE(getFailureExplanation().empty());
    EXPECT_FALSE(getWorkCompleted());

    // First, lets execute the state model to a known valid point, by
    // calling startModel. This should run the model through to DO_WORK_ST.
    ASSERT_NO_THROW(startModel(READY_ST));

    // Verify we are in the state of DO_WORK_ST with event of NOP_EVT.
    EXPECT_EQ(DO_WORK_ST, getCurrState());
    EXPECT_EQ(NOP_EVT, getNextEvent());

    // Resume the model with next event set to cause the DO_WORK_ST handler
    // to transition to an undefined state. This should cause it to return
    // without throwing and yield a failed model.
    EXPECT_NO_THROW(runModel(FORCE_UNDEFINED_ST_EVT));

    // Verify that status methods are correct: model is done but failed.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_TRUE(didModelFail());

    // Verify that failure explanation is not empty.
    EXPECT_FALSE(getFailureExplanation().empty());

    // Verify that work completed flag is still false.
    EXPECT_FALSE(getWorkCompleted());
}

/// @brief Tests that an unexpected exception thrown by a state handler is
/// handled gracefully.  State models are supposed to account for and handle
/// all errors that they actions (i.e. handlers) may cause.  In the event they
/// do not, this constitutes a model violation.  This test verifies such
/// violations are handled correctly and result in an orderly model failure.
TEST_F(StateModelTest, unexpectedError) {
    // Verify that the failure explanation is empty and work is not done.
    EXPECT_TRUE(getFailureExplanation().empty());
    EXPECT_FALSE(getWorkCompleted());

    // First, lets execute the state model to a known valid point, by
    // calling startModel with a start state of READY_ST.
    // This should run the model through to DO_WORK_ST.
    ASSERT_NO_THROW(startModel(READY_ST));

    // Verify we are in the state of DO_WORK_ST with event of NOP_EVT.
    EXPECT_EQ(DO_WORK_ST, getCurrState());
    EXPECT_EQ(NOP_EVT, getNextEvent());

    // Resume the model with next event set to cause the DO_WORK_ST handler
    // to transition to an undefined state. This should cause it to return
    // without throwing and yield a failed model.
    EXPECT_NO_THROW(runModel(SIMULATE_ERROR_EVT));

    // Verify that status methods are correct: model is done but failed.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_TRUE(didModelFail());

    // Verify that failure explanation is not empty.
    EXPECT_FALSE(getFailureExplanation().empty());

    // Verify that work completed flag is still false.
    EXPECT_FALSE(getWorkCompleted());
}

/// @brief Tests that undefined events are handled gracefully.
/// This test verifies that submitting an undefined event to the state machine
/// results, which constitutes a model violation, results in an orderly model
/// failure.
TEST_F(StateModelTest, undefinedEvent) {
    // Verify that the failure explanation is empty and work is not done.
    EXPECT_TRUE(getFailureExplanation().empty());
    EXPECT_FALSE(getWorkCompleted());

    // First, lets execute the state model to a known valid point, by
    // calling startModel with a start state of READY_ST.
    // This should run the model through to DO_WORK_ST.
    ASSERT_NO_THROW(startModel(READY_ST));

    // Verify we are in the state of DO_WORK_ST with event of NOP_EVT.
    EXPECT_EQ(DO_WORK_ST, getCurrState());
    EXPECT_EQ(NOP_EVT, getNextEvent());

    // Attempting to post an undefined event within runModel should cause it
    // to return without throwing and yield a failed model.
    EXPECT_NO_THROW(runModel(9999));

    // Verify that status methods are correct: model is done but failed.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_TRUE(didModelFail());

    // Verify that failure explanation is not empty.
    EXPECT_FALSE(getFailureExplanation().empty());

    // Verify that work completed flag is still false.
    EXPECT_FALSE(getWorkCompleted());
}

/// @brief Test the basic mechanics of state model execution.
/// This test exercises the ability to execute state model from start to
/// finish, including the handling of a asynchronous IO operation.
TEST_F(StateModelTest, stateModelTest) {
    // Verify that status methods are correct: model is new.
    EXPECT_TRUE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_FALSE(isModelDone());

    // Verify that the failure explanation is empty and work is not done.
    EXPECT_TRUE(getFailureExplanation().empty());
    EXPECT_FALSE(getWorkCompleted());

    // Launch the transaction by calling startModel.  The state model
    // should run up until the simulated async work operation is initiated
    // in DO_WORK_ST.
    ASSERT_NO_THROW(startModel(READY_ST));

    // Verify that we are now in state of DO_WORK_ST, the last event was
    // WORK_START_EVT, the next event is NOP_EVT.
    EXPECT_EQ(DO_WORK_ST, getCurrState());
    EXPECT_EQ(WORK_START_EVT, getLastEvent());
    EXPECT_EQ(NOP_EVT, getNextEvent());

    // Simulate completion of async work completion by resuming runModel with
    // an event of WORK_DONE_EVT.
    ASSERT_NO_THROW(runModel(WORK_DONE_EVT));

    // Verify that the state model has progressed through to completion:
    // it is in the DONE_ST, the status is ST_COMPLETED, and the next event
    // is NOP_EVT.
    EXPECT_EQ(END_ST, getCurrState());
    EXPECT_EQ(END_EVT, getNextEvent());

    // Verify that status methods are correct: model done.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());

    // Verify that failure explanation is empty.
    EXPECT_TRUE(getFailureExplanation().empty());

    // Verify that work completed flag is true.
    EXPECT_TRUE(getWorkCompleted());
}

}
