// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <acl/loader.h>

#include <string>
#include <gtest/gtest.h>

using namespace isc::acl;
using namespace std;
using namespace boost;
using isc::data::ConstElementPtr;

namespace {

// Just for convenience, create JSON objects from JSON string
ConstElementPtr el(const string& JSON) {
    return (isc::data::Element::fromJSON(JSON));
}

// We don't use the EXPECT_THROW macro, as it doesn't allow us
// to examine the exception. We want to check the element is stored
// there as well.
void testActionLoaderException(const string& JSON) {
    SCOPED_TRACE("Should throw with input: " + JSON);
    ConstElementPtr elem(el(JSON));
    try {
        defaultActionLoader(elem);
        FAIL() << "It did not throw";
    }
    catch (const LoaderError& error) {
        // Yes, comparing for pointer equality, that is enough, it
        // should return the exact instance of the JSON object
        EXPECT_EQ(elem, error.element());
    }
}

// Test the defaultActionLoader function
TEST(LoaderHelpers, DefaultActionLoader) {
    // First the three valid inputs
    EXPECT_EQ(ACCEPT, defaultActionLoader(el("\"ACCEPT\"")));
    EXPECT_EQ(REJECT, defaultActionLoader(el("\"REJECT\"")));
    EXPECT_EQ(DROP, defaultActionLoader(el("\"DROP\"")));
    // Now few invalid ones
    // String, but unknown one
    testActionLoaderException("\"UNKNOWN\"");
    testActionLoaderException("42");
    testActionLoaderException("true");
    testActionLoaderException("null");
    testActionLoaderException("[]");
    testActionLoaderException("{}");
}

// We need to pass a context, but it doesn't matter here which one
class NullContext {};

// A check that doesn't check anything but remembers it's own name
// and data
class NamedCheck : public Check<NullContext> {
public:
    NamedCheck(const string& name, ConstElementPtr data) :
        name_(name),
        data_(data)
    {}
    const string name_;
    const ConstElementPtr data_;
};

// The creator of NamedCheck
class NamedCreator : public Loader<NullContext>::CheckCreator {
public:
    NamedCreator(const string& name, bool abbreviatedList = true) :
        abbreviated_list_(abbreviatedList)
    {
        names_.push_back(name);
    }
    NamedCreator(const vector<string>& names) :
        names_(names),
        abbreviated_list_(true)
    {}
    vector<string> names() const {
        return (names_);
    }
    shared_ptr<Check<NullContext> > create(const string&, ConstElementPtr) {
        return (shared_ptr<Check<NullContext> >());
    }
    bool allowListAbbreviation() const {
        return (abbreviated_list_);
    }
private:
    vector<string> names_;
    const bool abbreviated_list_;
};

// To be thrown in tests internally
class TestCreatorError {};

// This will throw every time it should create something
class ThrowCreator : public Loader<NullContext>::CheckCreator {
public:
    vector<string> names() const {
        vector<string> result;
        result.push_back("throw");
        return (result);
    }
    shared_ptr<Check<NullContext> > create(const string&, ConstElementPtr) {
        throw TestCreatorError();
    }
};

class LoaderTest : public ::testing::Test {
public:
    Loader<NullContext> loader_;
    // Some convenience functions to set up

    // Create a NamedCreator, convert to shared pointer
    shared_ptr<NamedCreator> namedCreator(const string& name,
                                          bool abbreviatedList = true)
    {
        return (shared_ptr<NamedCreator>(new NamedCreator(name,
                                                          abbreviatedList)));
    }
    // Create and add a NamedCreator
    void addNamed(const string& name, bool abbreviatedList = true) {
        EXPECT_NO_THROW(loader_.registerCreator(
            namedCreator(name, abbreviatedList)));
    }
    // Load a check and convert it to named check to examine it
    shared_ptr<NamedCheck> loadCheck(const string& definition) {
        SCOPED_TRACE("Loading check " + definition);
        shared_ptr<Check<NullContext> > loaded;
        EXPECT_NO_THROW(loaded = loader_.loadCheck(el(definition)));
        shared_ptr<NamedCheck> result(dynamic_pointer_cast<NamedCheck>(
            loaded));
        EXPECT_TRUE(result);
        return (result);
    }
    // The loadCheck throws an exception
    void checkException(const string& JSON) {
        SCOPED_TRACE("Loading check exception: " + JSON);
        ConstElementPtr input(el(JSON));
        // Not using EXPECT_THROW, we want to examine the exception
        try {
            loader_.loadCheck(input);
            FAIL() << "Should have thrown";
        }
        catch (const LoaderError& e) {
            // It should be identical copy, so checking pointers
            EXPECT_EQ(input, e.element());
        }
    }
};

// Test that it does not accept duplicate creator
TEST_F(LoaderTest, CreatorDuplicity) {
    addNamed("name");
    EXPECT_THROW(loader_.registerCreator(namedCreator("name")), LoaderError);
}

// Test that we can register a creator and load a check with the name
TEST_F(LoaderTest, SimpleCheckLoad) {
    addNamed("name");
    shared_ptr<NamedCheck> check(loadCheck("{\"name\": 42}"));
    EXPECT_EQ("name", check->name_);
    EXPECT_TRUE(check->data_->equals(*el("42")));
}

// As above, but there are multiple creators registered within the loader
TEST_F(LoaderTest, MultiCreatorCheckLoad) {
    addNamed("name1");
    addNamed("name2");
    shared_ptr<NamedCheck> check(loadCheck("{\"name2\": 42}"));
    EXPECT_EQ("name2", check->name_);
    EXPECT_TRUE(check->data_->equals(*el("42")));
}

// Similar to above, but there's a creator with multiple names
TEST_F(LoaderTest, MultiNameCheckLoad) {
    addNamed("name1");
    vector<string> names;
    names.push_back("name2");
    names.push_back("name3");
    EXPECT_NO_THROW(loader_.registerCreator(shared_ptr<NamedCreator>(
        new NamedCreator(names))));
    shared_ptr<NamedCheck> check(loadCheck("{\"name3\": 42}"));
    EXPECT_EQ("name3", check->name_);
    EXPECT_TRUE(check->data_->equals(*el("42")));
}

// Invalid format is rejected
TEST_F(LoaderTest, InvalidFormatCheck) {
    checkException("[]");
    checkException("42");
    checkException("\"hello\"");
    checkException("null");
}

// Empty check is rejected
TEST_F(LoaderTest, EmptyCheck) {
    checkException("{}");
}

// The name isn't known
TEST_F(LoaderTest, UnkownName) {
    checkException("{\"unknown\": null}");
}

// Exception from the creator is propagated
TEST_F(LoaderTest, CheckPropagate) {
    loader_.registerCreator(shared_ptr<ThrowCreator>(new ThrowCreator()));
    EXPECT_THROW(loader_.loadCheck(el("{\"throw\": null}")), TestCreatorError);
}

// The abbreviated form is not yet implemented
// (we need the operators to be implemented)
TEST_F(LoaderTest, AndAbbrev) {
    addNamed("name1");
    addNamed("name2");
    EXPECT_THROW(loader_.loadCheck(el("{\"name1\": 1, \"name2\": 2}")),
                 LoaderError);
}

TEST_F(LoaderTest, OrAbbrev) {
    addNamed("name1");
    EXPECT_THROW(loader_.loadCheck(el("{\"name1\": [1, 2]}")),
                 LoaderError);
}

// But this is not abbreviated form, this should be passed directly to the
// creator
TEST_F(LoaderTest, ListCheck) {
    addNamed("name1", false);
    shared_ptr<NamedCheck> check(loadCheck("{\"name1\": [1, 2]}"));
    EXPECT_EQ("name1", check->name_);
    EXPECT_TRUE(check->data_->equals(*el("[1, 2]")));
}

// Check the action key is ignored as it should be
TEST_F(LoaderTest, CheckNoAction) {
    addNamed("name1");
    shared_ptr<NamedCheck> check(loadCheck("{\"name1\": 1, \"action\": 2}"));
    EXPECT_EQ("name1", check->name_);
    EXPECT_TRUE(check->data_->equals(*el("1")));
}

}
