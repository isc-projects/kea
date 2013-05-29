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

#include <string>

/// @file
/// CalloutHandle/LibraryCalloutHandle interaction tests
///
/// This file holds unit tests checking the interaction between the
/// CalloutHandle and LibraryCalloutHandle[Collection] classes.  In particular,
/// they check that:
///
/// - A CalloutHandle's context is shared between callouts from the same
///   library, but is separate for each library.
/// - The LibraryHandle retrieved by the CalloutHandle is the same for each
///   callout in the library, but different for different libraries.
///
/// Some minor interactions between the two classes were checked in the unit
/// tests for each class (mainly the use of the "skip" flag).

using namespace isc::util;
using namespace std;

namespace {

// This test checks the many-faced nature of the context for both the
// CalloutContext and the LibraryContext.
//
// Three libraries are assumed, and each supplies four callouts.  All callouts
// manipulate four context elements - two in the CalloutHandle and two in the
// LibraryHandle, the elements being called "string" and "uint64_t" (which
// describe the type of data manipulated).
//
// As with other tests, each callout shifts data to the left and inserts its
// own data.  Data is a string of the form "nmwc", where "n" is the number of
// the library, "m" is the callout number and "w" is an indication of what
// is being altered (library context ["x"] or callout context ["c"]) and "y" is
// the indication of what callout was passed as an argument ("x" or "b"). ("x"
// is used instead of "l" to indicate that library context is being altered,
// since in the results, these single characters will be mixed with digits and
// "l" looks too much like "1".)  Hence we have:
//
// - "xa" if library context is being altered from a callout made with the
//        first callout handle passed as argument.
// - "xb" if library context is being altered from a callout made with the
//        second callout handle passed as argument.
// - "ca" if the first callout handle's context is being manipulated.
// - "cb" if the second callout handle's context is being manipulated.
//
//
// For simplicity, and to cut down the number of functions actually written,
// the ollout indicator ("a" or "b") ) used in the in the CalloutHandle
// functions is passed via a CalloutArgument.  The argument is named "string":
// use of a name the same as that of one of the context elements serves as a
// check that the argument name space and argument context space are separate.
//
// Finally, the fourth callout copies the data into variables accessible
// to the test program.

// Values to be inspected at the end of the test.

// Values set in the LibraryHandle context.  There are three libraries, so
// there are three sets of library context.  To avoid a static initialization
// fiasco, encapsulate these in a function.

std::string& resultLibrary(int i) {
    static std::string result_library[3];
    return (result_library[i]);
}

// Values set in the CalloutHandle context.  There are three libraries, so
// there are three contexts for the callout, one for each library.

std::string& resultCallout(int i) {
    static std::string result_callout[3];
    return (result_callout[i]);
}

// A simple function to zero the results.

static void zero_results() {
    for (int i = 0; i < 3; ++i) {
        resultLibrary(i) = "";
        resultCallout(i) = "";
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
    string data = boost::lexical_cast<string>(10 * library_num + callout_num);

    // Get the library context data.  As the context will not exist on the
    // first call, catch the exception and create it. (In real life, the context
    // should have been created by the libraries' "load()" function.)
    string string_value = "";
    try {
        callout_handle.getLibraryHandle().getContext("string", string_value);
    } catch (const NoSuchContext&) {
        string_value = "";
    }

    // Update the context value with the library/callout indication (and the
    // suffix "l" to denote library) and set it.
    string_value += (data + string("x") + indicator);
    callout_handle.getLibraryHandle().setContext("string", string_value);

    // Get the context data. As before, this will not exist for the first
    // callout called. (In real life, the library should create it when the
    // "context_create" hook gets called before any packet processing takes
    // place.)
    try {
        callout_handle.getContext("string", string_value);
    } catch (const NoSuchCalloutContext&) {
        string_value = "";
    }

    // Update the value and set it.
    string_value += (data + string("c") + indicator);
    callout_handle.setContext("string", string_value);

    return (0);
}

// The following functions are the actual callouts - ther name is of the
// form "callout_<library number>_<callout number>"

int
callout_1_1(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 1, 1));
}

int
callout_1_2(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 1, 2));
}

int
callout_1_3(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 1, 3));
}

int
callout_2_1(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 2, 1));
}

int
callout_2_2(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 2, 2));
}

int
callout_2_3(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 2, 3));
}

int
callout_3_1(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 3, 1));
}

int
callout_3_2(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 3, 2));
}

int
callout_3_3(CalloutHandle& callout_handle) {
    return (execute(callout_handle, 3, 3));
}

// Common callout code for the fourth hook (which makes the data available for
// checking).  It copies the library and callout context data to the global
// variables.

int print_execute(CalloutHandle& callout_handle, int library_num) {

    // Print per-library context values.
    string result;
    callout_handle.getLibraryHandle()
                  .getContext("string", resultLibrary(library_num - 1));


    // Print callout context.
    callout_handle.getContext("string", resultCallout(library_num - 1));

    return (0);
}

// These are the actual callouts.

int
print_1(CalloutHandle& callout_handle) {
    return (print_execute(callout_handle, 1));
}

int
print_2(CalloutHandle& callout_handle) {
    return (print_execute(callout_handle, 2));
}

int
print_3(CalloutHandle& callout_handle) {
    return (print_execute(callout_handle, 3));
}

// The test begin here

TEST(HandlesTest, ContextCheck) {
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

    handle->registerCallout("one", callout_1_1);
    handle->registerCallout("two", callout_1_2);
    handle->registerCallout("three", callout_1_3);
    handle->registerCallout("four", print_1);

    collection->addLibraryHandle(handle);


    handle.reset(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout_2_1);
    handle->registerCallout("two", callout_2_2);
    handle->registerCallout("three", callout_2_3);
    handle->registerCallout("four", print_2);
    collection->addLibraryHandle(handle);

    handle.reset(new LibraryHandle(server_hooks));
    handle->registerCallout("one", callout_3_1);
    handle->registerCallout("two", callout_3_2);
    handle->registerCallout("three", callout_3_3);
    handle->registerCallout("four", print_3);
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
    // with callout handle "a".  This calls the callouts attached to hook "one"
    // from library 1, then those attached to hook "one" from library 2, then
    // from library 3.  The callout in library 1 appends "11xa" to the first
    // library's context. The callout in library 2 appends "21xa" to that
    // library's context.  Finally, the third library's context gets "31xa"
    // appended to it.
    //
    // The next callCallouts() call repeats the calls to the callouts attached
    // to hook "one", which result in "11xb", "21xb", "31xb" being appended to
    // the context of libraries 1, 2, and 3 respectively.
    //
    // The process is then repeated for hooks "two" and "three", leading to
    // the expected context values listed below.

    EXPECT_EQ("11xa11xb12xa12xb13xa13xb", resultLibrary(0));
    EXPECT_EQ("21xa21xb22xa22xb23xa23xb", resultLibrary(1));
    EXPECT_EQ("31xa31xb32xa32xb33xa33xb", resultLibrary(2));

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
    // At this point, we have only called the "print" function for callout
    // handle "a", so the following results are checking the context values
    // maintained in that callout handle.

    EXPECT_EQ("11ca12ca13ca", resultCallout(0));
    EXPECT_EQ("21ca22ca23ca", resultCallout(1));
    EXPECT_EQ("31ca32ca33ca", resultCallout(2));

    // Repeat the checks for callout b.  The library handle context values
    // should not change, but the context maintained by the callout handle
    // should.

    zero_results();
    collection->callCallouts(four_index, callout_handle_b);

    EXPECT_EQ("11xa11xb12xa12xb13xa13xb", resultLibrary(0));
    EXPECT_EQ("21xa21xb22xa22xb23xa23xb", resultLibrary(1));
    EXPECT_EQ("31xa31xb32xa32xb33xa33xb", resultLibrary(2));

    EXPECT_EQ("11cb12cb13cb", resultCallout(0));
    EXPECT_EQ("21cb22cb23cb", resultCallout(1));
    EXPECT_EQ("31cb32cb33cb", resultCallout(2));
}

} // Anonymous namespace

