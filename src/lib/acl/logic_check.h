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

#ifndef ACL_LOGIC_CHECK_H
#define ACL_LOGIC_CHECK_H

#include "check.h"
#include "loader.h"

namespace isc {
namespace acl {

class AnyOfSpec {
public:
    static bool start() { return (false); }
    static bool terminate(const bool another) {
        return (another);
    }
};

class AllOfSpec {
public:
    static bool start() { return (true); }
    static bool terminate(const bool another) {
        return (!another);
    }
};

template<typename Mode, typename Context>
class LogicOperator : public CompoundCheck<Context>, boost::noncopyable {
public:
    ~ LogicOperator() {
        for (typename CompoundCheck<Context>::Checks::iterator
                 i(checks_.begin());
             i != checks_.end(); ++i) {
            delete *i;
        }
    }
    void addSubexpression(const Check<Context>* expr) {
        checks_.push_back(expr);
    }
    virtual typename CompoundCheck<Context>::Checks getSubexpressions() const {
        return (checks_);
    }
    virtual bool matches(const Context& context) const {
        for (typename CompoundCheck<Context>::Checks::const_iterator
                 i(checks_.begin());
             i != checks_.end(); ++i) {
            if (Mode::terminate((*i)->matches(context))) {
                return (!Mode::start());
            }
        }
        return (Mode::start());
    }
private:
    typename CompoundCheck<Context>::Checks checks_;
};

template<typename Mode, typename Context, typename Action = BasicAction>
class LogicCreator : public Loader<Context, Action>::CheckCreator {
public:
    LogicCreator(const std::string& name);
    virtual std::vector<std::string> names() const;
    virtual boost::shared_ptr<Check<Context> > create(const std::string&,
                                                      data::ConstElementPtr
                                                      definition,
                                                      const Loader<Context,
                                                      Action>& loader);
    virtual bool allowListAbbreviation() const { return (false); }
};

}
}

#endif
