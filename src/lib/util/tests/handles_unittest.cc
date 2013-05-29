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

#include <util/hooks/callout_handle.h>
#include <util/hooks/library_handle.h>
#include <util/hooks/server_hooks.h>

#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

/// @file
/// CalloutHandle/LibraryCalloutHandle interaction tests
///
/// This file holds unit tests checking the interaction between the
/// CalloutHandle and LibraryCalloutHandle[Collection] classes.  In particular,
/// they check that:
///
/// - A CalloutHandle's context is shared between callouts from the same
///   library, but there is a separate context for each library.
///
/// - The LibraryHandle retrieved by the CalloutHandle is the same for each
///   callout in the library, but different for different libraries.
///
/// - The various methods manipulating the items in the CalloutHandle's context
///   work correctly.
///
/// Some minor interactions between the two classes are checked in the unit
/// tests for each class (mainly the use of the "skip" flag).

using namespace isc::util;
using namespace std;

namespace {

// The next set of functions define the callouts used by the tests.  They
// manipulate the data in such a way that callouts called - and the order in
// which they were called - can be determined.  The functions also check that
// the "callout context" and "library context" data areas are separate.
//
// Three libraries are assumed, and each supplies four callouts.  All callouts
// manipulate four context elements - two in the CalloutHandle and two in the
// LibraryHandle, the elements being called "string" and "int" (which describe
// the type of data manipulated).
//
// For the string item, each callout shifts data to the left and inserts its own
// data.  The aata is a string of the form "nmwc", where "n" is the number of
// the library, "m" is the callout number and "w" is an indication of what is
// being altered (library context ["x"] or callout context ["c"]) and "y" is the
// indication of what callout was passed as an argument ("x" or "b"). ("x" is
// used instead of "l" to indicate that library context is being altered since
// in the results, these single characters will be mixed with digits and "l"
// " looks too much like "1".)  Hence we have:
//
// - "xa" if library context is being altered from a callout made with the
//        first callout handle passed as argument.
// - "xb" if library context is being altered from a callout made with the
//        second callout handle passed as argument.
// - "ca" if the first callout handle's context is being manipulated.
// - "cb" if the second callout handle's context is being manipulated.
//
// For simplicity, and to cut down the number of functions actually written,
// the callout indicator ("a" or "b") ) used in the in the CalloutHandle
// functions is passed via a CalloutArgument.  The argument is named "string":
// use of a name the same as that of one of the context elements serves as a
// check that the argument name space and argument context space are separate.
//
// For integer data, the value starts at zero and an increment is added on each
// call.  This increment is equal to:
//
// 1000 * library number + 100 * callout_number + 10 * lib/callout + indicator
//
// where "lib/callout" is 1 if a library context is updated and 2 if a
// a callout context is changed. "indicator" is 1 for callout a and 2 for
// callout b.  This scheme gives a direct correspondence between the characters
//  appended to the string context item and the amount by which the integers
// context item is incremented.  For example, the string "21cb" corresponds to
// a value of 2122.
//
// Although this gives less information than the string value, the reasons for
// using it are:
//
// - It is a separate item in the context, so checks that the context can
//   handle multiple items.
// - It provides an item that can be deleted by the context deletion
//   methods.

// Values set in the LibraryHandle context.  There are three libraries, so
// there are three sets of library context.  To avoid a static initialization
// fiasco, encapsulate these in a function.

std::string& resultLibraryString(int index) {
    static std::string result_library_string[3];
    return (result_library_string[index]);
}

int& resultLibraryInt(int index) {
    static int result_library_int[3];
    return (result_library_int[index]);
}

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
        resultLibraryString(i) = "";
        resultLibraryInt(i) = 0;
        resultCalloutString(i) = "";
        resultCalloutInt(i) = 0;
    }
}


// Library callouts.

// Common code for setting the callout and library context values.

int
execute(CalloutHandle& callout_handle, int library_num, int callout_num) {

    // Obtain the callout handle indicator.
    string indicator;
    callout_handle.getArgument("string", indicator);

    // Create the basic data to be appended to the context value.
    int idata = 1000 * library_num + 100 * callout_num;
    string sdata = boost::lexical_cast<string>(10 * library_num + callout_num);

    // Get the library context data.  As the context will not exist on the
    // first call, catch the exception and create it. (In real life, the context
    // should have been created by the libraries' "load()" function.)
    string string_value = "";
    try {
        callout_handle.getLibraryHandle().getContext("string", string_value);
    } catch (const NoSuchLibraryContext&) {
        string_value = "";
    }

    int int_value = 0;
    try {
        callout_handle.getLibraryHandle().getContext("int", int_value);
    } catch (const NoSuchLibraryContext&) {
        int_value = 0;
    }

    // Update the context value with the library/callout indication (and the
    // suffix "x" to denote library) and set it.
    string_value += (sdata + string("x") + indicator);
    callout_handle.getLibraryHandle().setContext("string", string_value);

    int_value += (idata + 10 + (indicator == "a" ? 1 : 2));
    callout_handle.getLibraryHandle().setContext("int", int_value);

    // Get the context data. As before, this will not exist for the first
    // callout called. (In real life, the library should create it when the
    // "context_create" hook gets called before any packet processing takes
    // place.)
    string_value = "";
    try {
        callout_handle.getContext("string", string_value);
    } catch (const NoSuchCalloutContext&) {
        string_value = "";
    }

    int_value = 0;
    try {
        callout_handle.getContext("int", int_value);
    } catch (const NoSuchCalloutContext&) {
        int_value = 0;
    }

    // Update the values and set them.
    string_value += (sdata + string("c") + indicator);
    callout_handle.setContext("string", string_value);

    int_value += (idata + 20 + (indicator == "a" ? 1 : 2));
    callout_handle.setContext("int", int_value);

    return (0);
}

// The following functions are the actual callouts - ther name is of the
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

    // Print per-library context values.
    callout_handle.getLibraryHandle()
                  .getContext("string", resultLibraryString(library_num - 1));
    callout_handle.getLibraryHandle()
                  .getContext("int", resultLibraryInt(library_num - 1));


    // Print callout context.
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

// This test checks the many-faced nature of the context for both the
// CalloutContext and the LibraryContext.

TEST(HandlesTest, ContextAccessCheck) {
    // Create the LibraryHandleCollection with a set of four callouts
    // (the test does not use the ContextCreate and ContextDestroy callouts.)

    boost::shared_ptr<ServerHooks> server_hooks(new ServerHooks());
    const int one_index = server_hooks->registerHook("one");
    const int two_index = server_hooks->registerHook("two");
    const int three_index = server_hooks->registerHook("three");
    const int four_index = server_hooks->registerHook("four");

    // Create the library handle collection and the library handles.
    boost::shared_ptr<LibraryHandleCollection>
        collection(new LibraryHandleCollection());

    boost::shared_ptr<LibraryHandle> handle(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout11);
    handle->registerCallout("two", callout12);
    handle->registerCallout("three", callout13);
    handle->registerCallout("four", print1);
    collection->addLibraryHandle(handle);

    handle.reset(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout21);
    handle->registerCallout("two", callout22);
    handle->registerCallout("three", callout23);
    handle->registerCallout("four", print2);
    collection->addLibraryHandle(handle);

    handle.reset(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout31);
    handle->registerCallout("two", callout32);
    handle->registerCallout("three", callout33);
    handle->registerCallout("four", print3);
    collection->addLibraryHandle(handle);

    // Create the callout handles and distinguish them by setting the "long"
    // argument.
    CalloutHandle callout_handle_a(collection);
    callout_handle_a.setArgument("string", string("a"));

    CalloutHandle callout_handle_b(collection);
    callout_handle_b.setArgument("string", string("b"));

    // Now call the callouts attached to the first three hooks.  Each hook is
    // called twice (once for each callout handle) before the next hook is
    // called.
    collection->callCallouts(one_index, callout_handle_a);
    collection->callCallouts(one_index, callout_handle_b);
    collection->callCallouts(two_index, callout_handle_a);
    collection->callCallouts(two_index, callout_handle_b);
    collection->callCallouts(three_index, callout_handle_a);
    collection->callCallouts(three_index, callout_handle_b);

    // Get the results for each callout.  Explicitly zero the variables before
    // getting the results so we are certain that the values are the results
    // of the callouts.

    zero_results();
    collection->callCallouts(four_index, callout_handle_a);

    // To explain the expected library context results:
    //
    // The first callCallouts() call above calls the callouts for hook "one"
    // with callout handle "a".  This calls the callout attached to hook "one"
    // from library 1, then that attached to hook "one" from library 2, then
    // from library 3.  The callout in library 1 appends "11xa" to the first
    // library's context. The callout in library 2 appends "21xa" to its
    // library's context.  Finally, the third library's context gets "31xa"
    // appended to it.
    //
    // The next callCallouts() call repeats the calls to the callouts attached
    // to hook "one", which result in "11xb", "21xb", "31xb" being appended to
    // the context of libraries 1, 2, and 3 respectively.
    //
    // The process is then repeated for hooks "two" and "three", leading to
    // the expected context values listed below.
    //
    // The expected integer values can be found by summing up the values
    // corresponding to the elements of the strings.

    EXPECT_EQ("11xa11xb12xa12xb13xa13xb", resultLibraryString(0));
    EXPECT_EQ("21xa21xb22xa22xb23xa23xb", resultLibraryString(1));
    EXPECT_EQ("31xa31xb32xa32xb33xa33xb", resultLibraryString(2));

    EXPECT_EQ((1111 + 1112 + 1211 + 1212 + 1311 + 1312), resultLibraryInt(0));
    EXPECT_EQ((2111 + 2112 + 2211 + 2212 + 2311 + 2312), resultLibraryInt(1));
    EXPECT_EQ((3111 + 3112 + 3211 + 3212 + 3311 + 3312), resultLibraryInt(2));

    // To explain the expected callout context results.
    //
    // The callout handle maintains a separate context for each library.  When
    // the first call to callCallouts() is made, "11ca" gets appended to
    // the context for library 1 maintained by by the callout handle, "21ca"
    // gets appended to the context maintained for library 2, and "31ca" to
    // the context maintained for library 3.
    //
    // The next call to callCallouts() calls the same callouts but for a
    // different callout handle.  It also maintains three contexts (one for
    // each library) and they will get "11cb", "21cb", "31cb" appended to
    // them.  These don't affect the contexts maintained  by callout handle a.
    //
    // The process is then repeated for hooks "two" and "three", which append
    // "12ca", "22ca" and "32ca" for hook "two" and "31ca", "32ca" and "33ca"
    // for hook "three".
    //
    // The expected integer values can be found by summing up the values
    // corresponding to the elements of the strings.

    // At this point, we have only called the "print" function for callout
    // handle "a", so the following results are checking the context values
    // maintained in that callout handle.

    EXPECT_EQ("11ca12ca13ca", resultCalloutString(0));
    EXPECT_EQ("21ca22ca23ca", resultCalloutString(1));
    EXPECT_EQ("31ca32ca33ca", resultCalloutString(2));

    EXPECT_EQ((1121 + 1221 + 1321), resultCalloutInt(0));
    EXPECT_EQ((2121 + 2221 + 2321), resultCalloutInt(1));
    EXPECT_EQ((3121 + 3221 + 3321), resultCalloutInt(2));

    // Repeat the checks for callout b.  The library handle context values
    // should not change, but the context maintained by the callout handle
    // should.

    zero_results();
    collection->callCallouts(four_index, callout_handle_b);

    EXPECT_EQ("11xa11xb12xa12xb13xa13xb", resultLibraryString(0));
    EXPECT_EQ("21xa21xb22xa22xb23xa23xb", resultLibraryString(1));
    EXPECT_EQ("31xa31xb32xa32xb33xa33xb", resultLibraryString(2));

    EXPECT_EQ((1111 + 1112 + 1211 + 1212 + 1311 + 1312), resultLibraryInt(0));
    EXPECT_EQ((2111 + 2112 + 2211 + 2212 + 2311 + 2312), resultLibraryInt(1));
    EXPECT_EQ((3111 + 3112 + 3211 + 3212 + 3311 + 3312), resultLibraryInt(2));

    EXPECT_EQ("11cb12cb13cb", resultCalloutString(0));
    EXPECT_EQ("21cb22cb23cb", resultCalloutString(1));
    EXPECT_EQ("31cb32cb33cb", resultCalloutString(2));

    EXPECT_EQ((1122 + 1222 + 1322), resultCalloutInt(0));
    EXPECT_EQ((2122 + 2222 + 2322), resultCalloutInt(1));
    EXPECT_EQ((3122 + 3222 + 3322), resultCalloutInt(2));
}

// Now repeat the test, but add a deletion callout to the list.  The "two"
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

TEST(HandlesTest, ContextDeletionCheck) {
    // Create the LibraryHandleCollection with a set of four callouts
    // (the test does not use the ContextCreate and ContextDestroy callouts.)

    boost::shared_ptr<ServerHooks> server_hooks(new ServerHooks());
    const int one_index = server_hooks->registerHook("one");
    const int two_index = server_hooks->registerHook("two");
    const int three_index = server_hooks->registerHook("three");
    const int four_index = server_hooks->registerHook("four");

    // Create the library handle collection and the library handles.
    boost::shared_ptr<LibraryHandleCollection>
        collection(new LibraryHandleCollection());

    boost::shared_ptr<LibraryHandle> handle(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout11);
    handle->registerCallout("two", callout12);
    handle->registerCallout("two", printContextNames1);
    handle->registerCallout("three", callout13);
    handle->registerCallout("four", print1);
    collection->addLibraryHandle(handle);

    handle.reset(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout21);
    handle->registerCallout("two", callout22);
    handle->registerCallout("two", deleteIntContextItem);
    handle->registerCallout("two", printContextNames2);
    handle->registerCallout("three", callout23);
    handle->registerCallout("four", print2);
    collection->addLibraryHandle(handle);

    handle.reset(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout31);
    handle->registerCallout("two", callout32);
    handle->registerCallout("two", deleteAllContextItems);
    handle->registerCallout("two", printContextNames3);
    handle->registerCallout("three", callout33);
    handle->registerCallout("four", print3);
    collection->addLibraryHandle(handle);

    // Create the callout handles and distinguish them by setting the "long"
    // argument.
    CalloutHandle callout_handle_a(collection);
    callout_handle_a.setArgument("string", string("a"));

    CalloutHandle callout_handle_b(collection);
    callout_handle_b.setArgument("string", string("b"));

    // Now call the callouts attached to the first three hooks.  Each hook is
    // called twice (once for each callout handle) before the next hook is
    // called.
    collection->callCallouts(one_index, callout_handle_a);
    collection->callCallouts(one_index, callout_handle_b);
    collection->callCallouts(two_index, callout_handle_a);
    collection->callCallouts(two_index, callout_handle_b);
    collection->callCallouts(three_index, callout_handle_a);
    collection->callCallouts(three_index, callout_handle_b);

    // Get the results for each callout.  Explicitly zero the variables before
    // getting the results so we are certain that the values are the results
    // of the callouts.

    zero_results();
    collection->callCallouts(four_index, callout_handle_a);

    // The logic by which the expected results are arrived at is described
    // in the ContextAccessCheck test.  The results here are different
    // because context items have been modified along the way.
    //
    // As only the ContextHandle context is modified, the LibraryHandle
    // context is unaltered from the values obtained in the previous test.

    EXPECT_EQ("11xa11xb12xa12xb13xa13xb", resultLibraryString(0));
    EXPECT_EQ("21xa21xb22xa22xb23xa23xb", resultLibraryString(1));
    EXPECT_EQ("31xa31xb32xa32xb33xa33xb", resultLibraryString(2));

    EXPECT_EQ((1111 + 1112 + 1211 + 1212 + 1311 + 1312), resultLibraryInt(0));
    EXPECT_EQ((2111 + 2112 + 2211 + 2212 + 2311 + 2312), resultLibraryInt(1));
    EXPECT_EQ((3111 + 3112 + 3211 + 3212 + 3311 + 3312), resultLibraryInt(2));

    // ContextHandle context results.

    EXPECT_EQ("11ca12ca13ca", resultCalloutString(0));
    EXPECT_EQ("21ca22ca23ca", resultCalloutString(1));
    EXPECT_EQ(        "33ca", resultCalloutString(2));

    EXPECT_EQ((1121 + 1221 + 1321), resultCalloutInt(0));
    EXPECT_EQ((              2321), resultCalloutInt(1));
    EXPECT_EQ((              3321), resultCalloutInt(2));

    // Repeat the checks for callout b.  The library handle context values
    // should not change, but the context maintained by the callout handle
    // should.

    zero_results();
    collection->callCallouts(four_index, callout_handle_b);

    EXPECT_EQ("11xa11xb12xa12xb13xa13xb", resultLibraryString(0));
    EXPECT_EQ("21xa21xb22xa22xb23xa23xb", resultLibraryString(1));
    EXPECT_EQ("31xa31xb32xa32xb33xa33xb", resultLibraryString(2));

    EXPECT_EQ((1111 + 1112 + 1211 + 1212 + 1311 + 1312), resultLibraryInt(0));
    EXPECT_EQ((2111 + 2112 + 2211 + 2212 + 2311 + 2312), resultLibraryInt(1));
    EXPECT_EQ((3111 + 3112 + 3211 + 3212 + 3311 + 3312), resultLibraryInt(2));

    EXPECT_EQ("11cb12cb13cb", resultCalloutString(0));
    EXPECT_EQ("21cb22cb23cb", resultCalloutString(1));
    EXPECT_EQ(        "33cb", resultCalloutString(2));

    EXPECT_EQ((1122 + 1222 + 1322), resultCalloutInt(0));
    EXPECT_EQ((              2322), resultCalloutInt(1));
    EXPECT_EQ((              3322), resultCalloutInt(2));

    // ... and check what the names of the context items are after the callouts
    // for hook "two".  We know they are in sorted order.

    EXPECT_EQ(2, getItemNames(0).size());
    EXPECT_EQ(string("int"),    getItemNames(0)[0]);
    EXPECT_EQ(string("string"), getItemNames(0)[1]);

    EXPECT_EQ(1, getItemNames(1).size());
    EXPECT_EQ(string("string"), getItemNames(1)[0]);

    EXPECT_EQ(0, getItemNames(2).size());
}

} // Anonymous namespace

