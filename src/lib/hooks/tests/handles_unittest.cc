// Copyright (C) 2013,2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/server_hooks.h>

#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

/// @file
/// CalloutHandle/LibraryHandle interaction tests
///
/// This file holds unit tests checking the interaction between the
/// CalloutHandle/LibraryHandle and CalloutManager classes.  In particular,
/// they check that:
///
/// - A CalloutHandle's context is shared between callouts from the same
///   library, but there is a separate context for each library.
///
/// - The various methods manipulating the items in the CalloutHandle's context
///   work correctly.
///
/// - An active callout can only modify the registration of callouts registered
///   by its own library.

using namespace isc::hooks;
using namespace std;

namespace {

class HandlesTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up the various elements used in each test.
    HandlesTest() {
        // Set up four hooks, although through gamma
        ServerHooks& hooks = ServerHooks::getServerHooks();
        hooks.reset();
        alpha_index_ = hooks.registerHook("alpha");
        beta_index_ = hooks.registerHook("beta");
        gamma_index_ = hooks.registerHook("gamma");
        delta_index_ = hooks.registerHook("delta");

        // Set up for three libraries.
        manager_.reset(new CalloutManager(3));

        // Initialize remaining variables.
        common_string_ = "";
    }

    /// @brief Return callout manager
    boost::shared_ptr<CalloutManager> getCalloutManager() {
        return (manager_);
    }

    /// Hook indexes - these are frequently accessed, so are accessed directly.
    int alpha_index_;
    int beta_index_;
    int gamma_index_;
    int delta_index_;

    /// String accessible by all callouts whatever the library
    static std::string common_string_;

private:
    /// Callout manager.  Declared static so that the callout functions can
    /// access it.
    boost::shared_ptr<CalloutManager> manager_;
};

/// Define the common string
std::string HandlesTest::common_string_;


// The next set of functions define the callouts used by the tests.  They
// manipulate the data in such a way that callouts called - and the order in
// which they were called - can be determined.  The functions also check that
// the "callout context" data areas are separate.
//
// Three libraries are assumed, and each supplies four callouts.  All callouts
// manipulate two context elements the CalloutHandle, the elements being called
// "string" and "int" (which describe the type of data manipulated).
//
// For the string item, each callout shifts data to the left and inserts its own
// data.  The data is a string of the form "nmc", where "n" is the number of
// the library, "m" is the callout number and "y" is the indication of what
// callout handle was passed as an argument ("1" or "2": "0" is used when no
// identification has been set in the callout handle).
//
// For simplicity, and to cut down the number of functions actually written,
// the callout indicator ("1" or "2") ) used in the in the CalloutHandle
// functions is passed via a CalloutArgument.  The argument is named "string":
// use of a name the same as that of one of the context elements serves as a
// check that the argument name space and argument context space are separate.
//
// For integer data, the value starts at zero and an increment is added on each
// call.  This increment is equal to:
//
// 100 * library number + 10 * callout number + callout handle
//
// Although this gives less information than the string value, the reasons for
// using it are:
//
// - It is a separate item in the context, so checks that the context can
//   handle multiple items.
// - It provides an item that can be deleted by the context deletion
//   methods.


// Values set in the CalloutHandle context.  There are three libraries, so
// there are three contexts for the callout, one for each library.

std::string& resultCalloutString(int index) {
    static std::string result_callout_string[3];
    return (result_callout_string[index]);
}

int& resultCalloutInt(int index) {
    static int result_callout_int[3];
    return (result_callout_int[index]);
}

// A simple function to zero the results.

static void zero_results() {
    for (int i = 0; i < 3; ++i) {
        resultCalloutString(i) = "";
        resultCalloutInt(i) = 0;
    }
}


// Library callouts.

// Common code for setting the callout context values.

int
execute(CalloutHandle& callout_handle, int library_num, int callout_num) {

    // Obtain the callout handle number
    int handle_num = 0;
    try  {
        callout_handle.getArgument("handle_num", handle_num);
    } catch (const NoSuchArgument&) {
        // handle_num argument not set: this is the case in the tests where
        // the context_create hook check is tested.
        handle_num = 0;
    }

    // Create the basic data to be appended to the context value.
    int idata = 100 * library_num + 10 * callout_num + handle_num;
    string sdata = boost::lexical_cast<string>(idata);

    // Get the context data. As before, this will not exist for the first
    // callout called. (In real life, the library should create it when the
    // "context_create" hook gets called before any packet processing takes
    // place.)
    int int_value = 0;
    try {
        callout_handle.getContext("int", int_value);
    } catch (const NoSuchCalloutContext&) {
        int_value = 0;
    }

    string string_value = "";
    try {
        callout_handle.getContext("string", string_value);
    } catch (const NoSuchCalloutContext&) {
        string_value = "";
    }

    // Update the values and set them back in the callout context.
    int_value += idata;
    callout_handle.setContext("int", int_value);

    string_value += sdata;
    callout_handle.setContext("string", string_value);

    return (0);
}

// The following functions are the actual callouts - the name is of the
// form "callout_<library number>_<callout number>"

int
callout11(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 1, 1));
}

int
callout12(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 1, 2));
}

int
callout13(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 1, 3));
}

int
callout21(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 2, 1));
}

int
callout22(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 2, 2));
}

int
callout23(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 2, 3));
}

int
callout31(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 3, 1));
}

int
callout32(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 3, 2));
}

int
callout33(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 3, 3));
}

// Common callout code for the fourth hook (which makes the data available for
// checking).  It copies the library and callout context data to the global
// variables.

int printExecute(CalloutHandle& callout_handle, int library_num) {
    callout_handle.getContext("string", resultCalloutString(library_num - 1));
    callout_handle.getContext("int", resultCalloutInt(library_num - 1));

    return (0);
}

// These are the actual callouts.

int
print1(CalloutHandle& callout_handle) {
    return (printExecute(callout_handle, 1));
}

int
print2(CalloutHandle& callout_handle) {
    return (printExecute(callout_handle, 2));
}

int
print3(CalloutHandle& callout_handle) {
    return (printExecute(callout_handle, 3));
}

// This test checks the many-faced nature of the context for the CalloutContext.

TEST_F(HandlesTest, ContextAccessCheck) {
    // Register callouts for the different libraries.
    CalloutHandle handle(getCalloutManager());

    // Library 0.
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout11);
    getCalloutManager()->registerCallout("beta", callout12);
    getCalloutManager()->registerCallout("gamma", callout13);
    getCalloutManager()->registerCallout("delta", print1);

    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout21);
    getCalloutManager()->registerCallout("beta", callout22);
    getCalloutManager()->registerCallout("gamma", callout23);
    getCalloutManager()->registerCallout("delta", print2);

    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout31);
    getCalloutManager()->registerCallout("beta", callout32);
    getCalloutManager()->registerCallout("gamma", callout33);
    getCalloutManager()->registerCallout("delta", print3);

    // Create the callout handles and distinguish them by setting the
    // "handle_num" argument.
    CalloutHandle callout_handle_1(getCalloutManager());
    callout_handle_1.setArgument("handle_num", static_cast<int>(1));

    CalloutHandle callout_handle_2(getCalloutManager());
    callout_handle_2.setArgument("handle_num", static_cast<int>(2));

    // Now call the callouts attached to the first three hooks.  Each hook is
    // called twice (once for each callout handle) before the next hook is
    // called.
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_1);
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_2);
    getCalloutManager()->callCallouts(beta_index_, callout_handle_1);
    getCalloutManager()->callCallouts(beta_index_, callout_handle_2);
    getCalloutManager()->callCallouts(gamma_index_, callout_handle_1);
    getCalloutManager()->callCallouts(gamma_index_, callout_handle_2);

    // Get the results for each callout (the callout on hook "delta" copies
    // the context values into a location the test can access).  Explicitly
    // zero the variables before getting the results so we are certain that
    // the values are the results of the callouts.

    zero_results();

    // To explain the expected callout context results.
    //
    // Each callout handle maintains a separate context for each library.  When
    // the first call to callCallouts() is made, "111" gets appended to
    // the context for library 1 maintained by the first callout handle, "211"
    // gets appended to the context maintained for library 2, and "311" to
    // the context maintained for library 3.  In each case, the first digit
    // corresponds to the library number, the second to the callout number and
    // the third to the "handle_num" of the callout handle. For the first call
    // to callCallouts, handle 1 is used, so the last digit is always 1.
    //
    // The next call to callCallouts() calls the same callouts but for the
    // second callout handle.  It also maintains three contexts (one for
    // each library) and they will get "112", "212", "312" appended to
    // them. The explanation for the digits is the same as before, except that
    // in this case, the callout handle is number 2, so the third digit is
    // always 2.  These additions don't affect the contexts maintained by
    // callout handle 1.
    //
    // The process is then repeated for hooks "beta" and "gamma" which, for
    // callout handle 1, append "121", "221" and "321" for hook "beta" and
    // "311", "321" and "331" for hook "gamma".
    //
    // The expected integer values can be found by summing up the values
    // corresponding to the elements of the strings.

    // At this point, we have only called the "print" function for callout
    // handle "1", so the following results are checking the context values
    // maintained in that callout handle.

    getCalloutManager()->callCallouts(delta_index_, callout_handle_1);
    EXPECT_EQ("111121131", resultCalloutString(0));
    EXPECT_EQ("211221231", resultCalloutString(1));
    EXPECT_EQ("311321331", resultCalloutString(2));

    EXPECT_EQ((111 + 121 + 131), resultCalloutInt(0));
    EXPECT_EQ((211 + 221 + 231), resultCalloutInt(1));
    EXPECT_EQ((311 + 321 + 331), resultCalloutInt(2));

    // Repeat the checks for callout 2.

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_2);

    EXPECT_EQ((112 + 122 + 132), resultCalloutInt(0));
    EXPECT_EQ((212 + 222 + 232), resultCalloutInt(1));
    EXPECT_EQ((312 + 322 + 332), resultCalloutInt(2));

    EXPECT_EQ("112122132", resultCalloutString(0));
    EXPECT_EQ("212222232", resultCalloutString(1));
    EXPECT_EQ("312322332", resultCalloutString(2));
}

// Now repeat the test, but add a deletion callout to the list.  The "beta"
// hook of library 2 will have an additional callout to delete the "int"
// element: the same hook for library 3 will delete both elements.  In
// addition, the names of context elements for the libraries at this point
// will be printed.

// List of context item names.

vector<string>&
getItemNames(int index) {
    static vector<string> context_items[3];
    return (context_items[index]);
}

// Context item deletion functions.

int
deleteIntContextItem(CalloutHandle& handle) {
    handle.deleteContext("int");
    return (0);
}

int
deleteAllContextItems(CalloutHandle& handle) {
    handle.deleteAllContext();
    return (0);
}

// Generic print function - copy names in sorted order.

int
printContextNamesExecute(CalloutHandle& handle, int library_num) {
    const int index = library_num - 1;
    getItemNames(index) = handle.getContextNames();
    sort(getItemNames(index).begin(), getItemNames(index).end());
    return (0);
}

int
printContextNames1(CalloutHandle& handle) {
    return (printContextNamesExecute(handle, 1));
}

int
printContextNames2(CalloutHandle& handle) {
    return (printContextNamesExecute(handle, 2));
}

int
printContextNames3(CalloutHandle& handle) {
    return (printContextNamesExecute(handle, 3));
}

// Perform the test including deletion of context items.

TEST_F(HandlesTest, ContextDeletionCheck) {

    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout11);
    getCalloutManager()->registerCallout("beta", callout12);
    getCalloutManager()->registerCallout("beta", printContextNames1);
    getCalloutManager()->registerCallout("gamma", callout13);
    getCalloutManager()->registerCallout("delta", print1);

    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout21);
    getCalloutManager()->registerCallout("beta", callout22);
    getCalloutManager()->registerCallout("beta", deleteIntContextItem);
    getCalloutManager()->registerCallout("beta", printContextNames2);
    getCalloutManager()->registerCallout("gamma", callout23);
    getCalloutManager()->registerCallout("delta", print2);

    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout31);
    getCalloutManager()->registerCallout("beta", callout32);
    getCalloutManager()->registerCallout("beta", deleteAllContextItems);
    getCalloutManager()->registerCallout("beta", printContextNames3);
    getCalloutManager()->registerCallout("gamma", callout33);
    getCalloutManager()->registerCallout("delta", print3);

    // Create the callout handles and distinguish them by setting the "long"
    // argument.
    CalloutHandle callout_handle_1(getCalloutManager());
    callout_handle_1.setArgument("handle_num", static_cast<int>(1));

    CalloutHandle callout_handle_2(getCalloutManager());
    callout_handle_2.setArgument("handle_num", static_cast<int>(2));

    // Now call the callouts attached to the first three hooks.  Each hook is
    // called twice (once for each callout handle) before the next hook is
    // called.
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_1);
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_2);
    getCalloutManager()->callCallouts(beta_index_, callout_handle_1);
    getCalloutManager()->callCallouts(beta_index_, callout_handle_2);
    getCalloutManager()->callCallouts(gamma_index_, callout_handle_1);
    getCalloutManager()->callCallouts(gamma_index_, callout_handle_2);

    // Get the results for each callout.  Explicitly zero the variables before
    // getting the results so we are certain that the values are the results
    // of the callouts.

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_1);

    // The logic by which the expected results are arrived at is described
    // in the ContextAccessCheck test.  The results here are different
    // because context items have been modified along the way.

    EXPECT_EQ((111 + 121 + 131), resultCalloutInt(0));
    EXPECT_EQ((            231), resultCalloutInt(1));
    EXPECT_EQ((            331), resultCalloutInt(2));

    EXPECT_EQ("111121131", resultCalloutString(0));
    EXPECT_EQ("211221231", resultCalloutString(1));
    EXPECT_EQ(      "331", resultCalloutString(2));

    // Repeat the checks for callout handle 2.

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_2);

    EXPECT_EQ((112 + 122 + 132), resultCalloutInt(0));
    EXPECT_EQ((            232), resultCalloutInt(1));
    EXPECT_EQ((            332), resultCalloutInt(2));

    EXPECT_EQ("112122132", resultCalloutString(0));
    EXPECT_EQ("212222232", resultCalloutString(1));
    EXPECT_EQ(      "332", resultCalloutString(2));

    // ... and check what the names of the context items are after the callouts
    // for hook "beta".  We know they are in sorted order.

    EXPECT_EQ(2, getItemNames(0).size());
    EXPECT_EQ(string("int"),    getItemNames(0)[0]);
    EXPECT_EQ(string("string"), getItemNames(0)[1]);

    EXPECT_EQ(1, getItemNames(1).size());
    EXPECT_EQ(string("string"), getItemNames(1)[0]);

    EXPECT_EQ(0, getItemNames(2).size());
}

// Tests that the CalloutHandle's constructor and destructor call the
// context_create and context_destroy callbacks (if registered).  For
// simplicity, we'll use the same callout functions as used above.

TEST_F(HandlesTest, ConstructionDestructionCallouts) {

    // Register context callouts.
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("context_create", callout11);
    getCalloutManager()->registerCallout("context_create", print1);
    getCalloutManager()->registerCallout("context_destroy", callout12);
    getCalloutManager()->registerCallout("context_destroy", print1);

    // Create the CalloutHandle and check that the constructor callout
    // has run.
    zero_results();
    boost::scoped_ptr<CalloutHandle>
        callout_handle(new CalloutHandle(getCalloutManager()));
    EXPECT_EQ("110", resultCalloutString(0));
    EXPECT_EQ(110, resultCalloutInt(0));

    // Check that the destructor callout runs.  Note that the "print1" callout
    // didn't destroy the library context - it only copied it to where it
    // could be examined.  As a result, the destructor callout appends its
    // elements to the constructor's values and the result is printed.
    zero_results();
    callout_handle.reset();

    EXPECT_EQ("110120", resultCalloutString(0));
    EXPECT_EQ((110 + 120), resultCalloutInt(0));
}

// Dynamic callout registration and deregistration.
// The following are the dynamic registration/deregistration callouts.


// Add callout_78_alpha - adds a callout to hook alpha that appends "78x"
// (where "x" is the callout handle) to the current output.

int
callout78(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 7, 8));
}

int
add_callout78_alpha(CalloutHandle& callout_handle) {
    callout_handle.getLibraryHandle().registerCallout("alpha", callout78);
    return (0);
}

int
delete_callout78_alpha(CalloutHandle& callout_handle) {
    static_cast<void>(
        callout_handle.getLibraryHandle().deregisterCallout("alpha",
                                                            callout78));
    return (0);
}

// Check that a callout can register another callout on a different hook.

TEST_F(HandlesTest, DynamicRegistrationAnotherHook) {
    // Register callouts for the different libraries.
    CalloutHandle handle(getCalloutManager());

    // Set up callouts on "alpha".
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout11);
    getCalloutManager()->registerCallout("delta", print1);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout21);
    getCalloutManager()->registerCallout("delta", print2);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout31);
    getCalloutManager()->registerCallout("delta", print3);

    // ... and on "beta", set up the function to add a hook to alpha (but only
    // for library 1).
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("beta", add_callout78_alpha);

    // See what we get for calling the callouts on alpha first.
    CalloutHandle callout_handle_1(getCalloutManager());
    callout_handle_1.setArgument("handle_num", static_cast<int>(1));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_1);

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_1);
    EXPECT_EQ("111", resultCalloutString(0));
    EXPECT_EQ("211", resultCalloutString(1));
    EXPECT_EQ("311", resultCalloutString(2));

    // All as expected, now call the callouts on beta.  This should add a
    // callout to the list of callouts for alpha, which we should see when
    // we run the test again.
    getCalloutManager()->callCallouts(beta_index_, callout_handle_1);

    // Use a new callout handle so as to get fresh callout context.
    CalloutHandle callout_handle_2(getCalloutManager());
    callout_handle_2.setArgument("handle_num", static_cast<int>(2));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_2);

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_2);
    EXPECT_EQ("112", resultCalloutString(0));
    EXPECT_EQ("212782", resultCalloutString(1));
    EXPECT_EQ("312", resultCalloutString(2));
}

// Check that a callout can register another callout on the same hook.
// Note that the registration only applies to a subsequent invocation of
// callCallouts, not to the current one. In other words, if
//
// * the callout list for a library is "A then B then C"
// * when callCallouts is executed "B" adds "D" to that list,
//
// ... the current execution of callCallouts only executes A, B and C.  A
// subsequent invocation will execute A, B, C then D.

TEST_F(HandlesTest, DynamicRegistrationSameHook) {
    // Register callouts for the different libraries.
    CalloutHandle handle(getCalloutManager());

    // Set up callouts on "alpha".
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout11);
    getCalloutManager()->registerCallout("alpha", add_callout78_alpha);
    getCalloutManager()->registerCallout("delta", print1);

    // See what we get for calling the callouts on alpha first.
    CalloutHandle callout_handle_1(getCalloutManager());
    callout_handle_1.setArgument("handle_num", static_cast<int>(1));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_1);
    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_1);
    EXPECT_EQ("111", resultCalloutString(0));

    // Run it again - we should have added something to this hook.
    CalloutHandle callout_handle_2(getCalloutManager());
    callout_handle_2.setArgument("handle_num", static_cast<int>(2));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_2);
    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_2);
    EXPECT_EQ("112782", resultCalloutString(0));

    // And a third time...
    CalloutHandle callout_handle_3(getCalloutManager());
    callout_handle_3.setArgument("handle_num", static_cast<int>(3));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_3);
    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_3);
    EXPECT_EQ("113783783", resultCalloutString(0));
}

// Deregistration of a callout from a different hook

TEST_F(HandlesTest, DynamicDeregistrationDifferentHook) {
    // Register callouts for the different libraries.
    CalloutHandle handle(getCalloutManager());

    // Set up callouts on "alpha".
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout11);
    getCalloutManager()->registerCallout("alpha", callout78);
    getCalloutManager()->registerCallout("alpha", callout11);
    getCalloutManager()->registerCallout("delta", print1);

    getCalloutManager()->registerCallout("beta", delete_callout78_alpha);

    // Call the callouts on alpha
    CalloutHandle callout_handle_1(getCalloutManager());
    callout_handle_1.setArgument("handle_num", static_cast<int>(1));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_1);

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_1);
    EXPECT_EQ("111781111", resultCalloutString(0));

    // Run the callouts on hook beta to remove the callout on alpha.
    getCalloutManager()->callCallouts(beta_index_, callout_handle_1);

    // The run of the callouts should have altered the callout list on the
    // first library for hook alpha, so call again to make sure.
    CalloutHandle callout_handle_2(getCalloutManager());
    callout_handle_2.setArgument("handle_num", static_cast<int>(2));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_2);

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_2);
    EXPECT_EQ("112112", resultCalloutString(0));
}

// Deregistration of a callout from the same hook

TEST_F(HandlesTest, DynamicDeregistrationSameHook) {
    // Register callouts for the different libraries.
    CalloutHandle handle(getCalloutManager());

    // Set up callouts on "alpha".
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout11);
    getCalloutManager()->registerCallout("alpha", delete_callout78_alpha);
    getCalloutManager()->registerCallout("alpha", callout78);
    getCalloutManager()->registerCallout("delta", print1);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout21);
    getCalloutManager()->registerCallout("alpha", callout78);
    getCalloutManager()->registerCallout("delta", print2);

    // Call the callouts on alpha
    CalloutHandle callout_handle_1(getCalloutManager());
    callout_handle_1.setArgument("handle_num", static_cast<int>(1));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_1);

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_1);
    EXPECT_EQ("111781", resultCalloutString(0));
    EXPECT_EQ("211781", resultCalloutString(1));

    // The run of the callouts should have altered the callout list on the
    // first library for hook alpha, so call again to make sure.
    CalloutHandle callout_handle_2(getCalloutManager());
    callout_handle_2.setArgument("handle_num", static_cast<int>(2));
    getCalloutManager()->callCallouts(alpha_index_, callout_handle_2);

    zero_results();
    getCalloutManager()->callCallouts(delta_index_, callout_handle_2);
    EXPECT_EQ("112", resultCalloutString(0));
    EXPECT_EQ("212782", resultCalloutString(1));
}

// Testing the operation of the "skip" flag.  Callouts print the value
// they see in the flag and either leave it unchanged, set it or clear it.
int
calloutPrintSkip(CalloutHandle& handle) {
    static const std::string YES("Y");
    static const std::string NO("N");
    static const std::string DROP("D");

    switch (handle.getStatus()) {
    case CalloutHandle::NEXT_STEP_CONTINUE:
        HandlesTest::common_string_ += NO; // skip = no
        break;
    case CalloutHandle::NEXT_STEP_SKIP:
        HandlesTest::common_string_ += YES; // skip = yes
        break;
    case CalloutHandle::NEXT_STEP_DROP:
        HandlesTest::common_string_ += DROP; // drop
        break;
    }
    return (0);
}

int
calloutSetSkip(CalloutHandle& handle) {
    static_cast<void>(calloutPrintSkip(handle));
    handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
    return (0);
}

int
calloutClearSkip(CalloutHandle& handle) {
    static_cast<void>(calloutPrintSkip(handle));
    handle.setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    return (0);
}

// Do a series of tests, returning with the skip flag set "true".

TEST_F(HandlesTest, ReturnSkipSet) {
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", calloutPrintSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);

    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", calloutPrintSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);

    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", calloutPrintSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);

    CalloutHandle callout_handle(getCalloutManager());
    getCalloutManager()->callCallouts(alpha_index_, callout_handle);

    // Check result.  For each of visual checking, the expected string is
    // divided into sections corresponding to the blocks of callouts above.
    EXPECT_EQ(std::string("NNYY" "NNYYN" "NNYN"), common_string_);

    // ... and check that the skip flag on exit from callCallouts is set.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle.getStatus());
}

// Repeat the test, returning with the skip flag clear.
TEST_F(HandlesTest, ReturnSkipClear) {
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);

    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", calloutPrintSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);

    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);
    getCalloutManager()->registerCallout("alpha", calloutPrintSkip);
    getCalloutManager()->registerCallout("alpha", calloutSetSkip);
    getCalloutManager()->registerCallout("alpha", calloutClearSkip);

    CalloutHandle callout_handle(getCalloutManager());
    getCalloutManager()->callCallouts(alpha_index_, callout_handle);

    // Check result.  For each of visual checking, the expected string is
    // divided into sections corresponding to the blocks of callouts above.
    EXPECT_EQ(std::string("NYY" "NNYNYN" "NNNY"), common_string_);

    // ... and check that the skip flag on exit from callCallouts is set.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle.getStatus());
}

// Check that the skip flag is cleared when callouts are called - even if
// there are no callouts.

TEST_F(HandlesTest, NoCalloutsSkipTest) {
    // Note - no callouts are registered on any hook.
    CalloutHandle callout_handle(getCalloutManager());

    // Clear the skip flag and call a hook with no callouts.
    callout_handle.setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    getCalloutManager()->callCallouts(alpha_index_, callout_handle);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle.getStatus());

    // Set the skip flag and call a hook with no callouts.
    callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
    getCalloutManager()->callCallouts(alpha_index_, callout_handle);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle.getStatus());
}

// The next set of callouts do a similar thing to the above "skip" tests,
// but alter the value of a string argument.  This is for testing that the
// a callout is able to change an argument and return it to the caller.

const char* MODIFIED_ARG = "modified_arg";

int
calloutSetArgumentCommon(CalloutHandle& handle, const char* what) {
    std::string modified_arg = "";

    handle.getArgument(MODIFIED_ARG, modified_arg);
    modified_arg = modified_arg + std::string(what);
    handle.setArgument(MODIFIED_ARG, modified_arg);
    return (0);
}

int
calloutSetArgumentYes(CalloutHandle& handle) {
    return (calloutSetArgumentCommon(handle, "Y"));
}

int
calloutSetArgumentNo(CalloutHandle& handle) {
    return (calloutSetArgumentCommon(handle, "N"));
}

// ... and a callout to just copy the argument to the "common_string_" variable
// but otherwise not alter it.

int
calloutPrintArgument(CalloutHandle& handle) {
    handle.getArgument(MODIFIED_ARG, HandlesTest::common_string_);
    return (0);
}

TEST_F(HandlesTest, CheckModifiedArgument) {
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentYes);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentNo);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentNo);

    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentYes);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentYes);
    getCalloutManager()->registerCallout("alpha", calloutPrintArgument);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentNo);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentNo);

    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentYes);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentNo);
    getCalloutManager()->registerCallout("alpha", calloutSetArgumentYes);

    // Create the argument with an initial empty string value.  Then call the
    // sequence of callouts above.
    CalloutHandle callout_handle(getCalloutManager());
    std::string modified_arg = "";
    callout_handle.setArgument(MODIFIED_ARG, modified_arg);
    getCalloutManager()->callCallouts(alpha_index_, callout_handle);

    // Check the intermediate and results.  For visual checking, the expected
    // string is divided into sections corresponding to the blocks of callouts
    // above.
    EXPECT_EQ(std::string("YNN" "YY"), common_string_);

    callout_handle.getArgument(MODIFIED_ARG, modified_arg);
    EXPECT_EQ(std::string("YNN" "YYNN" "YNY"), modified_arg);
}

// Test that the CalloutHandle provides the name of the hook to which the
// callout is attached.

int
callout_hook_name(CalloutHandle& callout_handle) {
    HandlesTest::common_string_ = callout_handle.getHookName();
    return (0);
}

int
callout_hook_dummy(CalloutHandle&) {
    return (0);
}

TEST_F(HandlesTest, HookName) {
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_hook_name);
    getCalloutManager()->registerCallout("beta", callout_hook_name);

    // Call alpha and beta callouts and check the hook to which they belong.
    CalloutHandle callout_handle(getCalloutManager());

    EXPECT_EQ(std::string(""), HandlesTest::common_string_);

    getCalloutManager()->callCallouts(alpha_index_, callout_handle);
    EXPECT_EQ(std::string("alpha"), HandlesTest::common_string_);

    getCalloutManager()->callCallouts(beta_index_, callout_handle);
    EXPECT_EQ(std::string("beta"), HandlesTest::common_string_);

    // Make sure that the callout accesses the name even if it is not the
    // only callout in the list.
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("gamma", callout_hook_dummy);
    getCalloutManager()->registerCallout("gamma", callout_hook_name);
    getCalloutManager()->registerCallout("gamma", callout_hook_dummy);

    EXPECT_EQ(std::string("beta"), HandlesTest::common_string_);
    getCalloutManager()->callCallouts(gamma_index_, callout_handle);
    EXPECT_EQ(std::string("gamma"), HandlesTest::common_string_);
}

} // Anonymous namespace

