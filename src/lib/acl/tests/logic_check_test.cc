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

#include "creators.h"
#include <acl/logic_check.h>
#include <typeinfo>
#include <boost/shared_ptr.hpp> // for static_pointer_cast

using namespace std;
using namespace boost;
using namespace isc::acl;
using namespace isc::acl::tests;
using isc::data::Element;

namespace {

// Test the defs in AnyOfSpec
TEST(LogicOperators, AnyOfSpec) {
    EXPECT_FALSE(AnyOfSpec::start());
    EXPECT_FALSE(AnyOfSpec::terminate(false));
    EXPECT_TRUE(AnyOfSpec::terminate(true));
}

// Test the defs in AllOfSpec
TEST(LogicOperators, AllOfSpec) {
    EXPECT_TRUE(AllOfSpec::start());
    EXPECT_TRUE(AllOfSpec::terminate(false));
    EXPECT_FALSE(AllOfSpec::terminate(true));
}

// Generic test of one check
template<typename Mode>
void
testCheck(bool emptyResult) {
    // It can be created
    LogicOperator<Mode, Log> oper;
    // It is empty by default
    EXPECT_EQ(0, oper.getSubexpressions().size());
    // And returns true, as all 0 of the subexpressions return true
    Log log;
    EXPECT_EQ(emptyResult, oper.matches(log));
    log.checkFirst(0);
    // Fill it with some subexpressions
    typedef boost::shared_ptr<ConstCheck> CheckPtr;
    oper.addSubexpression(CheckPtr(new ConstCheck(emptyResult, 0)));
    oper.addSubexpression(CheckPtr(new ConstCheck(emptyResult, 1)));
    // Check what happens when only the default-valued are there
    EXPECT_EQ(2, oper.getSubexpressions().size());
    EXPECT_EQ(emptyResult, oper.matches(log));
    log.checkFirst(2);
    oper.addSubexpression(CheckPtr(new ConstCheck(!emptyResult, 2)));
    oper.addSubexpression(CheckPtr(new ConstCheck(!emptyResult, 3)));
    // They are listed there
    EXPECT_EQ(4, oper.getSubexpressions().size());
    // Now, the last one kills it, but the first ones will run, the fourth
    // won't
    EXPECT_EQ(!emptyResult, oper.matches(log));
    log.checkFirst(3);
}

TEST(LogicOperators, AllOf) {
    testCheck<AllOfSpec>(true);
}

TEST(LogicOperators, AnyOf) {
    testCheck<AnyOfSpec>(false);
}

// Fixture for the tests of the creators
class LogicCreatorTest : public ::testing::Test {
private:
    typedef boost::shared_ptr<Loader<Log>::CheckCreator> CreatorPtr;
public:
    // Register some creators, both tested ones and some auxiliary ones for
    // help
    LogicCreatorTest():
        loader_(REJECT)
    {
        loader_.registerCreator(CreatorPtr(new
            LogicCreator<AnyOfSpec, Log>("ANY")));
        loader_.registerCreator(CreatorPtr(new
            LogicCreator<AllOfSpec, Log>("ALL")));
        loader_.registerCreator(CreatorPtr(new ThrowCreator));
        loader_.registerCreator(CreatorPtr(new LogCreator));
        loader_.registerCreator(CreatorPtr(new NotCreator<Log>("NOT")));
    }
    // To mark which parts of the check did run
    Log log_;
    // The loader
    Loader<Log> loader_;
    // Some convenience shortcut names
    typedef LogicOperator<AnyOfSpec, Log> AnyOf;
    typedef LogicOperator<AllOfSpec, Log> AllOf;
    typedef boost::shared_ptr<AnyOf> AnyOfPtr;
    typedef boost::shared_ptr<AllOf> AllOfPtr;
    // Loads the JSON as a check and tries to convert it to the given check
    // subclass
    template<typename Result> boost::shared_ptr<Result> load(const string& JSON) {
        boost::shared_ptr<Check<Log> > result;
        EXPECT_NO_THROW(result = loader_.loadCheck(Element::fromJSON(JSON)));
        /*
         * Optimally, we would use a dynamic_pointer_cast here to both
         * convert the pointer and to check the type is correct. However,
         * clang++ seems to be confused by templates and creates two typeids
         * for the same templated type (even with the same parameters),
         * therfore considering the types different, even if they are the same.
         * This leads to false alarm in the test. Luckily, it generates the
         * same name for both typeids, so we use them instead (which is enough
         * to test the correct type of Check is returned). Then we can safely
         * cast statically, as we don't use any kind of nasty things like
         * multiple inheritance.
         */
        EXPECT_STREQ(typeid(Result).name(), typeid(*result.get()).name());
        boost::shared_ptr<Result>
            resultConverted(static_pointer_cast<Result>(result));
        EXPECT_NE(boost::shared_ptr<Result>(), resultConverted);
        return (resultConverted);
    }
};

// Test it can load empty ones
TEST_F(LogicCreatorTest, empty) {
    AnyOfPtr emptyAny(load<AnyOf>("{\"ANY\": []}"));
    EXPECT_EQ(0, emptyAny->getSubexpressions().size());
    AllOfPtr emptyAll(load<AllOf>("{\"ALL\": []}"));
    EXPECT_EQ(0, emptyAll->getSubexpressions().size());
}

// Test it rejects invalid inputs (not a list as a parameter)
TEST_F(LogicCreatorTest, invalid) {
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ANY\": null}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ANY\": {}}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ANY\": true}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ANY\": 42}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ANY\": \"hello\"}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ALL\": null}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ALL\": {}}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ALL\": true}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ALL\": 42}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"ALL\": \"hello\"}")),
                 LoaderError);
}

// Exceptions from subexpression creation isn't caught
TEST_F(LogicCreatorTest, propagate) {
    EXPECT_THROW(loader_.loadCheck(
                     Element::fromJSON("{\"ANY\": [{\"throw\": null}]}")),
                 TestCreatorError);
    EXPECT_THROW(loader_.loadCheck(
                     Element::fromJSON("{\"ALL\": [{\"throw\": null}]}")),
                 TestCreatorError);
}

// We can create more complex ANY check and run it correctly
TEST_F(LogicCreatorTest, anyRun) {
    AnyOfPtr any(load<AnyOf>("{\"ANY\": ["
                             "    {\"logcheck\": [0, false]},"
                             "    {\"logcheck\": [1, true]},"
                             "    {\"logcheck\": [2, true]}"
                             "]}"));
    EXPECT_EQ(3, any->getSubexpressions().size());
    EXPECT_TRUE(any->matches(log_));
    log_.checkFirst(2);
}

// We can create more complex ALL check and run it correctly
TEST_F(LogicCreatorTest, allRun) {
    AllOfPtr any(load<AllOf>("{\"ALL\": ["
                             "    {\"logcheck\": [0, true]},"
                             "    {\"logcheck\": [1, false]},"
                             "    {\"logcheck\": [2, false]}"
                             "]}"));
    EXPECT_EQ(3, any->getSubexpressions().size());
    EXPECT_FALSE(any->matches(log_));
    log_.checkFirst(2);
}

// Or is able to return false
TEST_F(LogicCreatorTest, anyFalse) {
    AnyOfPtr any(load<AnyOf>("{\"ANY\": ["
                             "    {\"logcheck\": [0, false]},"
                             "    {\"logcheck\": [1, false]},"
                             "    {\"logcheck\": [2, false]}"
                             "]}"));
    EXPECT_EQ(3, any->getSubexpressions().size());
    EXPECT_FALSE(any->matches(log_));
    log_.checkFirst(3);
}

// And is able to return true
TEST_F(LogicCreatorTest, andTrue) {
    AllOfPtr all(load<AllOf>("{\"ALL\": ["
                             "    {\"logcheck\": [0, true]},"
                             "    {\"logcheck\": [1, true]},"
                             "    {\"logcheck\": [2, true]}"
                             "]}"));
    EXPECT_EQ(3, all->getSubexpressions().size());
    EXPECT_TRUE(all->matches(log_));
    log_.checkFirst(3);
}

// We can nest them together
TEST_F(LogicCreatorTest, nested) {
    AllOfPtr all(load<AllOf>("{\"ALL\": ["
                             "    {\"ANY\": ["
                             "        {\"logcheck\": [0, true]},"
                             "        {\"logcheck\": [2, true]},"
                             "    ]},"
                             "    {\"logcheck\": [1, false]}"
                             "]}"));
    EXPECT_EQ(2, all->getSubexpressions().size());
    /*
     * This has the same problem as load function above, and we use the
     * same solution here.
     */
    ASSERT_STREQ(typeid(LogicOperator<AnyOfSpec, Log>).name(),
                 typeid(*all->getSubexpressions()[0]).name());
    const LogicOperator<AnyOfSpec, Log>*
        any(static_cast<const LogicOperator<AnyOfSpec, Log>*>
            (all->getSubexpressions()[0]));
    EXPECT_EQ(2, any->getSubexpressions().size());
    EXPECT_FALSE(all->matches(log_));
    log_.checkFirst(2);
}

void notTest(bool value) {
    NotOperator<Log> notOp(boost::shared_ptr<Check<Log> >(
                                new ConstCheck(value, 0)));
    Log log;
    // It returns negated value
    EXPECT_EQ(!value, notOp.matches(log));
    // And runs the only one thing there
    log.checkFirst(1);
    // Check the getSubexpressions does sane things
    ASSERT_EQ(1, notOp.getSubexpressions().size());
    EXPECT_EQ(value, notOp.getSubexpressions()[0]->matches(log));
}

TEST(Not, trueValue) {
    notTest(true);
}

TEST(Not, falseValue) {
    notTest(false);
}

TEST_F(LogicCreatorTest, notInvalid) {
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"NOT\": null}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"NOT\": \"hello\"}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"NOT\": true}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"NOT\": 42}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"NOT\": []}")),
                 LoaderError);
    EXPECT_THROW(loader_.loadCheck(Element::fromJSON("{\"NOT\": [{"
                                                     "\"logcheck\": [0, true]"
                                                     "}]}")),
                 LoaderError);
}

TEST_F(LogicCreatorTest, notValid) {
    boost::shared_ptr<NotOperator<Log> > notOp(load<NotOperator<Log> >("{\"NOT\":"
                                                                "  {\"logcheck\":"
                                                                "     [0, true]}}"));
    EXPECT_FALSE(notOp->matches(log_));
    log_.checkFirst(1);
}

}
