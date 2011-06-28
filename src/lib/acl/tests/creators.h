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

// This is not a public header, but some code shared between tests
// This one contains various creators to test the loader and other creators

#ifndef CREATORS_H
#define CREATORS_H

#include "logcheck.h"

#include <cc/data.h>
#include <acl/loader.h>
#include <string>

namespace isc {
namespace acl {
namespace tests {

// A check that doesn't check anything but remembers it's own name
// and data
class NamedCheck : public Check<Log> {
public:
    NamedCheck(const std::string& name, isc::data::ConstElementPtr data) :
        name_(name),
        data_(data)
    {}
    virtual bool matches(const Log&) const { return (true); }
    const std::string name_;
    const isc::data::ConstElementPtr data_;
};

// The creator of NamedCheck
class NamedCreator : public Loader<Log>::CheckCreator {
public:
    NamedCreator(const std::string& name, bool abbreviatedList = true) :
        abbreviated_list_(abbreviatedList)
    {
        names_.push_back(name);
    }
    NamedCreator(const std::vector<std::string>& names) :
        names_(names),
        abbreviated_list_(true)
    {}
    std::vector<std::string> names() const {
        return (names_);
    }
    boost::shared_ptr<Check<Log> > create(const std::string& name,
                                          isc::data::ConstElementPtr data,
                                          const Loader<Log>&)
    {
        bool found(false);
        for (std::vector<std::string>::const_iterator i(names_.begin());
             i != names_.end(); ++i) {
            if (*i == name) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "Name " << name << " passed to creator which "
            "doesn't handle it.";
        return (boost::shared_ptr<Check<Log> >(new NamedCheck(name, data)));
    }
    bool allowListAbbreviation() const {
        return (abbreviated_list_);
    }
private:
    std::vector<std::string> names_;
    const bool abbreviated_list_;
};

// To be thrown in tests internally
class TestCreatorError {};

// This will throw every time it should create something
class ThrowCreator : public Loader<Log>::CheckCreator {
public:
    std::vector<std::string> names() const {
        std::vector<std::string> result;
        result.push_back("throw");
        return (result);
    }
    boost::shared_ptr<Check<Log> > create(const std::string&,
                                          isc::data::ConstElementPtr,
                                          const Loader<Log>&)
    {
        throw TestCreatorError();
    }
};

// This throws whenever the match is called on it
class ThrowCheck : public Check<Log> {
public:
    virtual bool matches(const Log&) const {
        throw TestCreatorError();
    }
};

// And creator for it
class ThrowCheckCreator : public Loader<Log>::CheckCreator {
public:
    std::vector<std::string> names() const {
        std::vector<std::string> result;
        result.push_back("throwcheck");
        return (result);
    }
    boost::shared_ptr<Check<Log> > create(const std::string&,
                                          isc::data::ConstElementPtr,
                                          const Loader<Log>&)
    {
        return (boost::shared_ptr<Check<Log> >(new ThrowCheck()));
    }
};

class LogCreator : public Loader<Log>::CheckCreator {
public:
    std::vector<std::string> names() const {
        std::vector<std::string> result;
        result.push_back("logcheck");
        return (result);
    }
    /*
     * For simplicity, we just take two values as a list, first is the
     * logging cell used, the second is result of the check. No error checking
     * is done, if there's bug in the test, it will throw TypeError for us.
     */
    boost::shared_ptr<Check<Log> > create(const std::string&,
                                          isc::data::ConstElementPtr definition,
                                          const Loader<Log>&)
    {
        std::vector<isc::data::ConstElementPtr> list(definition->listValue());
        int logpos(list[0]->intValue());
        bool accept(list[1]->boolValue());
        return (boost::shared_ptr<ConstCheck>(new ConstCheck(accept, logpos)));
    }
    // We take a list, so don't interpret it for us
    virtual bool allowListAbbreviation() const { return (false); }
};

}
}
}
#endif

// Local Variables:
// mode: c++
// End:
