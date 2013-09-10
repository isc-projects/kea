// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
    static const int DUMMY_ST = SM_STATE_MAX + 1;

    ///@brief Starting state for the test state model.
    static const int READY_ST = SM_STATE_MAX + 2;

    ///@brief State which simulates doing asynchronous work.
    static const int DO_WORK_ST = SM_STATE_MAX + 3;

    ///@brief State which finishes off processing.
    static const int DONE_ST = SM_STATE_MAX + 4;

    // StateModelTest events
    ///@brief Event used to trigger initiation of asynchronous work.
    static const int WORK_START_EVT = SM_EVENT_MAX + 1;

    ///@brief Event issued when the asynchronous work "completes".
    static const int WORK_DONE_EVT = SM_EVENT_MAX + 2;

    ///@brief Event issued when all the work is done.
    static const int ALL_DONE_EVT = SM_EVENT_MAX + 3;

    /// @brief Constructor
    ///
    /// Parameters match those needed by StateModel.
    StateModelTest() : dummy_called_(false), model_failure_called_(false),
                      work_completed_(false) {
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

    /// @brief Returns indication of whether or not the model failed to execute.
    ///
    /// If true, this indicates that the test model suffered an error
    /// during execution such as an invalid state, event, or exception thrown by
    /// a state handler. The flag is only set true by onModelFailure() method.
    bool getModelFailureCalled() {
        return (model_failure_called_);
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

    /// @brief Initializes the state handler map.
    virtual void initStateHandlerMap() {
        addToMap(DUMMY_ST,
            boost::bind(&StateModelTest::dummyHandler, this));

        addToMap(READY_ST,
            boost::bind(&StateModelTest::readyHandler, this));

        addToMap(DO_WORK_ST,
            boost::bind(&StateModelTest::doWorkHandler, this));

        addToMap(DONE_ST,
            boost::bind(&StateModelTest::doneWorkHandler, this));
    }

    /// @brief Validates the contents of the state handler map.
    virtual void verifyStateHandlerMap() {
        getStateHandler(DUMMY_ST);
        getStateHandler(READY_ST);
        getStateHandler(DO_WORK_ST);
        getStateHandler(DONE_ST);
    }

    /// @brief  Handler called when the model suffers an execution error.
    virtual void onModelFailure() {
        model_failure_called_ = true;
    }

    const char* getStateLabel(const int state) const {
        const char* str = "Unknown";
        switch(state) {
        case DUMMY_ST:
            str = "StateModelTest::DUMMY_ST";
            break;
        case READY_ST:
            str = "StateModelTest::READY_ST";
            break;
        case DO_WORK_ST:
            str = "StateModelTest::DO_WORK_ST";
            break;
        case DONE_ST:
            str = "StateModelTest::DONE_ST";
            break;
        default:
            str = StateModel::getStateLabel(state);
            break;
        }

        return (str);
    }

    const char* getEventLabel(const int event) const {
        const char* str = "Unknown";
        switch(event) {
        case WORK_START_EVT:
            str = "StateModelTest::WORK_START_EVT";
            break;
        case WORK_DONE_EVT:
            str = "StateModelTest::WORK_DONE_EVT";
            break;
        case ALL_DONE_EVT :
            str = "StateModelTest::ALL_DONE_EVT";
            break;
        default:
            str = StateModel::getEventLabel(event);
            break;
        }

        return (str);
    }

    /// @brief Indicator of whether or not the DUMMY_ST handler has been called.
    bool dummy_called_;

    /// @brief Indicator of whether or not onModelError has been called.
    bool model_failure_called_;

    /// @brief Indicator of whether or not DONE_ST handler has been called.
    bool work_completed_;
};

// Declare them so gtest can see them.
const int StateModelTest::DUMMY_ST;
const int StateModelTest::READY_ST;
const int StateModelTest::DO_WORK_ST;
const int StateModelTest::DONE_ST;
const int StateModelTest::WORK_START_EVT;
const int StateModelTest::WORK_DONE_EVT;
const int StateModelTest::ALL_DONE_EVT;

/// @brief Tests the fundamental methods used for state handler mapping.
/// Verifies the ability to search for and add entries in the state handler map.
TEST_F(StateModelTest, basicStateMapping) {
    // After construction, the state map should be empty. Verify that
    // getStateHandler will throw when, state cannot be found.
    EXPECT_THROW(getStateHandler(READY_ST), StateModelError);

    // Verify that we can add a handler to the map.
    ASSERT_NO_THROW(addToMap(READY_ST, boost::bind(&StateModelTest::
                                                   dummyHandler, this)));

    // Verify that we can find the handler by its state.
    StateHandler retreived_handler;
    EXPECT_NO_THROW(retreived_handler = getStateHandler(READY_ST));

    // Now we will Verify that retrieved handler executes the correct method.
    // Make sure the dummy called flag is false prior to invocation.
    EXPECT_FALSE(getDummyCalled());

    // Invoke the retreived handler.
    ASSERT_NO_THROW((retreived_handler)());

    // Verify the dummy called flag is now true.
    EXPECT_TRUE(getDummyCalled());

    // Verify that we cannot add a duplicate.
    EXPECT_THROW(addToMap(READY_ST, boost::bind(&StateModelTest::readyHandler,
                                                this)),
                 StateModelError);

    // Verify that we can still find the handler by its state.
    EXPECT_NO_THROW(getStateHandler(READY_ST));


    // Verify that we cannot add a handler for NEW_ST.
    EXPECT_THROW(addToMap(NEW_ST, boost::bind(&StateModelTest::dummyHandler,
                                              this)),
                 StateModelError);

    // Verify that we cannot add a handler for END_ST.
    EXPECT_THROW(addToMap(END_ST, boost::bind(&StateModelTest::dummyHandler,
                                              this)),
                 StateModelError);
}

/// @brief Tests state map initialization and validation.
/// This tests the basic concept of state map initialization and verification
/// by manually invoking the map methods normally called by startModel.
TEST_F(StateModelTest, stateMapInit) {
    // Verify that the map validation throws prior to the map being
    // initialized.
    EXPECT_THROW(verifyStateHandlerMap(), StateModelError);

    // Call initStateHandlerMap to initialize the state map.
    ASSERT_NO_THROW(initStateHandlerMap());

    // Verify that the map validation succeeds now that the map is initialized.
    EXPECT_NO_THROW(verifyStateHandlerMap());
}

/// @brief Tests the ability to decode state values into text labels.
TEST_F(StateModelTest, stateLabels) {
    // Verify base class labels.
    EXPECT_EQ("StateModel::NEW_ST", getStateLabel(NEW_ST));
    EXPECT_EQ("StateModel::END_ST", getStateLabel(END_ST));

    // Verify stub class labels.
    EXPECT_EQ("StateModelTest::DUMMY_ST", getStateLabel(DUMMY_ST));
    EXPECT_EQ("StateModelTest::READY_ST", getStateLabel(READY_ST));
    EXPECT_EQ("StateModelTest::DO_WORK_ST", getStateLabel(DO_WORK_ST));
    EXPECT_EQ("StateModelTest::DONE_ST", getStateLabel(DONE_ST));

    // Verify unknown state.
    EXPECT_EQ("Unknown", getStateLabel(-1));
}

/// @brief Tests the ability to decode event values into text labels.
TEST_F(StateModelTest, eventLabels) {
    // Verify base class labels.
    EXPECT_EQ("StateModel::NOP_EVT", getEventLabel(NOP_EVT));
    EXPECT_EQ("StateModel::START_EVT", getEventLabel(START_EVT));
    EXPECT_EQ("StateModel::END_EVT", getEventLabel(END_EVT));
    EXPECT_EQ("StateModel::FAIL_EVT", getEventLabel(FAIL_EVT));

    // Verify stub class labels.
    EXPECT_EQ("StateModelTest::WORK_START_EVT", getEventLabel(WORK_START_EVT));
    EXPECT_EQ("StateModelTest::WORK_DONE_EVT", getEventLabel(WORK_DONE_EVT));
    EXPECT_EQ("StateModelTest::ALL_DONE_EVT", getEventLabel(ALL_DONE_EVT));

    // Verify unknown state.
    EXPECT_EQ("Unknown", getEventLabel(-1));
}

/// @brief General testing of member accessors.
/// Most if not all of these are also tested as a byproduct off larger tests.
TEST_F(StateModelTest, stateAccessors) {
    // setState will throw unless we initialize the handler map.
    ASSERT_NO_THROW(initStateHandlerMap());
    ASSERT_NO_THROW(verifyStateHandlerMap());

    // Verify post-construction state values.
    EXPECT_EQ(NEW_ST, getState());
    EXPECT_EQ(NEW_ST, getPrevState());

    // Call setState which will update both state and previous state.
    EXPECT_NO_THROW(setState(READY_ST));

    // Verify the values are what we expect.
    EXPECT_EQ(READY_ST, getState());
    EXPECT_EQ(NEW_ST, getPrevState());

    // Call setState again.
    EXPECT_NO_THROW(setState(DO_WORK_ST));

    // Verify the values are what we expect.
    EXPECT_EQ(DO_WORK_ST, getState());
    EXPECT_EQ(READY_ST, getPrevState());

    // Verify that calling setState with an state that has no handler
    // will throw.
    EXPECT_THROW(setState(-1), StateModelError);

    // Verify that calling setState with NEW_ST is ok.
    EXPECT_NO_THROW(setState(NEW_ST));

    // Verify that calling setState with END_ST is ok.
    EXPECT_NO_THROW(setState(END_ST));
}

TEST_F(StateModelTest, eventAccessors) {
    // Verify post-construction event values.
    EXPECT_EQ(NOP_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call setEvent which will update both next event and last event.
    EXPECT_NO_THROW(postNextEvent(START_EVT));

    // Verify the values are what we expect.
    EXPECT_EQ(START_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call setEvent again.
    EXPECT_NO_THROW(postNextEvent(WORK_START_EVT));
    EXPECT_EQ(WORK_START_EVT, getNextEvent());
    EXPECT_EQ(START_EVT, getLastEvent());

    // Verify the values are what we expect.
}

TEST_F(StateModelTest, transitionWithEnd) {
    // Manually init the handlers map.
    ASSERT_NO_THROW(initStateHandlerMap());
    ASSERT_NO_THROW(verifyStateHandlerMap());

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    //  Verify that state and event members are as expected.
    EXPECT_EQ(DUMMY_ST, getState());
    EXPECT_EQ(NEW_ST, getPrevState());
    EXPECT_EQ(START_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call endModel to transition us to the end of the model.
    EXPECT_NO_THROW(endModel());

    // Verify state and event members are correctly set.
    EXPECT_EQ(END_ST, getState());
    EXPECT_EQ(DUMMY_ST, getPrevState());
    EXPECT_EQ(END_EVT, getNextEvent());
    EXPECT_EQ(START_EVT, getLastEvent());
}

TEST_F(StateModelTest, transitionWithAbort) {
    // Manually init the handlers map.
    ASSERT_NO_THROW(initStateHandlerMap());
    ASSERT_NO_THROW(verifyStateHandlerMap());

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    //  Verify that state and event members are as expected.
    EXPECT_EQ(DUMMY_ST, getState());
    EXPECT_EQ(NEW_ST, getPrevState());
    EXPECT_EQ(START_EVT, getNextEvent());
    EXPECT_EQ(NOP_EVT, getLastEvent());

    // Call endModel to transition us to the end of the model.
    EXPECT_NO_THROW(abortModel());

    // Verify state and event members are correctly set.
    EXPECT_EQ(END_ST, getState());
    EXPECT_EQ(DUMMY_ST, getPrevState());
    EXPECT_EQ(FAIL_EVT, getNextEvent());
    EXPECT_EQ(START_EVT, getLastEvent());
}

TEST_F(StateModelTest, doFlags) {
    // Manually init the handlers map.
    ASSERT_NO_THROW(initStateHandlerMap());
    ASSERT_NO_THROW(verifyStateHandlerMap());

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

TEST_F(StateModelTest, statusMethods) {
    // Manually init the handlers map.
    ASSERT_NO_THROW(initStateHandlerMap());
    ASSERT_NO_THROW(verifyStateHandlerMap());

    // After construction, state model is "new", all others should be false.
    EXPECT_TRUE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_FALSE(isModelDone());
    EXPECT_FALSE(didModelFail());

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

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

TEST_F(StateModelTest, statusMethodsOnFailure) {
    // Manually init the handlers map.
    ASSERT_NO_THROW(initStateHandlerMap());
    ASSERT_NO_THROW(verifyStateHandlerMap());

    // call transition to move from NEW_ST to DUMMY_ST with START_EVT
    EXPECT_NO_THROW(transition(DUMMY_ST, START_EVT));

    // Call endModel to transition us to the end of the model.
    EXPECT_NO_THROW(abortModel());

    // With state set to END_ST, model should be done.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_TRUE(didModelFail());
}

TEST_F(StateModelTest, contextStrs) {
    // Manually init the handlers map.
    ASSERT_NO_THROW(initStateHandlerMap());
    ASSERT_NO_THROW(verifyStateHandlerMap());

    // transition uses setState and setEvent, testing it tests all three.
    EXPECT_NO_THROW(transition(READY_ST, START_EVT));

    std::string ctx_str = getContextStr();
    EXPECT_NE(std::string::npos, ctx_str.find(getStateLabel(READY_ST)));
    EXPECT_NE(std::string::npos, ctx_str.find(getEventLabel(START_EVT)));

    ctx_str = getPrevContextStr();
    EXPECT_NE(std::string::npos, ctx_str.find(getStateLabel(NEW_ST)));
    EXPECT_NE(std::string::npos, ctx_str.find(getEventLabel(NOP_EVT)));
}

/// @brief Tests that invalid states are handled gracefully.
/// This test verifies that attempting to execute a state which has no handler
/// results in a failed model.
TEST_F(StateModelTest, invalidState) {
    // First, verify state is NEW_ST and that NEW_ST has no handler.
    // This is the state that runModel will attempt to execute.
    ASSERT_EQ(NEW_ST, getState());
    ASSERT_THROW(getStateHandler(NEW_ST), StateModelError);

    // Verify that the StateModelTest's outcome flags are both false.
    EXPECT_FALSE(getModelFailureCalled());
    EXPECT_FALSE(getWorkCompleted());

    // Now call runModel() which should not throw, but should result
    // in a failed model and a call to onModelFailure().
    EXPECT_NO_THROW(runModel(START_EVT));

    // Verify that status methods are correct: model is done but failed.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_TRUE(didModelFail());

    // Verify that model failure flag is true.
    EXPECT_TRUE(getModelFailureCalled());

    // Verify that work completed flag is still false.
    EXPECT_FALSE(getWorkCompleted());
}

/// @brief Tests that invalid events are handled gracefully.
/// This test verifies that submitting an invalid event to the state machine
/// results in a failed transaction.
TEST_F(StateModelTest, invalidEvent) {
    // Verify that the StateModelTest's outcome flags are both false.
    EXPECT_FALSE(getModelFailureCalled());
    EXPECT_FALSE(getWorkCompleted());

    // First, lets execute the state model to a known valid point, by
    // calling startModel with a start state of READY_ST.
    // This should run the model through to DO_WORK_ST.
    ASSERT_NO_THROW(startModel(READY_ST));

    // Verify we are in the state of DO_WORK_ST with event of NOP_EVT.
    EXPECT_EQ(DO_WORK_ST, getState());
    EXPECT_EQ(NOP_EVT, getNextEvent());

    // Submitting an invalid event to a valid state, should cause runModel to
    // return without throwing and yield a failed model. (Current state is
    // DO_WORK_ST, during which START_EVT, is invalid).
    EXPECT_NO_THROW(runModel(START_EVT));

    // Verify that status methods are correct: model is done but failed.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());
    EXPECT_TRUE(didModelFail());

    // Verify that model failure flag is true.
    EXPECT_TRUE(getModelFailureCalled());

    // Verify that work completed flag is still false.
    EXPECT_FALSE(getWorkCompleted());
}

/// @brief Test the basic mechanics of state model execution.
/// This test exercises the ability to execute state model from state to
/// finish, including the handling of a asynchronous IO operation.
TEST_F(StateModelTest, stateModelTest) {
    // Verify that status methods are correct: model is new.
    EXPECT_TRUE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_FALSE(isModelDone());

    // Verify that the StateModelTest's outcome flags are both false.
    EXPECT_FALSE(getModelFailureCalled());
    EXPECT_FALSE(getWorkCompleted());

    // Launch the transaction by calling startModel.  The state model
    // should run up until the simulated async work operation is initiated
    // in DO_WORK_ST.
    ASSERT_NO_THROW(startModel(READY_ST));

    // Verify that we are now in state of DO_WORK_ST, the last event was
    // WORK_START_EVT, the next event is NOP_EVT.
    EXPECT_EQ(DO_WORK_ST, getState());
    EXPECT_EQ(WORK_START_EVT, getLastEvent());
    EXPECT_EQ(NOP_EVT, getNextEvent());

    // Simulate completion of async work completion by resuming runModel with
    // an event of WORK_DONE_EVT.
    ASSERT_NO_THROW(runModel(WORK_DONE_EVT));

    // Verify that the state model has progressed through to completion:
    // it is in the DONE_ST, the status is ST_COMPLETED, and the next event
    // is NOP_EVT.
    EXPECT_EQ(END_ST, getState());
    EXPECT_EQ(END_EVT, getNextEvent());

    // Verify that status methods are correct: model done.
    EXPECT_FALSE(isModelNew());
    EXPECT_FALSE(isModelRunning());
    EXPECT_FALSE(isModelWaiting());
    EXPECT_TRUE(isModelDone());

    // Verify that model failure flag is false.
    EXPECT_FALSE(getModelFailureCalled());

    // Verify that work completed flag is true.
    EXPECT_TRUE(getWorkCompleted());
}

}
