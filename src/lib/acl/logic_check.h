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

/// \brief Constants for the AnyOf implementation
class AnyOfSpec {
public:
    static bool start() { return (false); }
    static bool terminate(const bool another) {
        return (another);
    }
};

/// \brief Constants for the AllOf implementation
class AllOfSpec {
public:
    static bool start() { return (true); }
    static bool terminate(const bool another) {
        return (!another);
    }
};

/**
 * \brief Logic operators
 *
 * This class implements the AllOf and AnyOf compound checks. As their
 * behaviour is almost the same, the same template class is used. Which
 * one it is depends on the Mode template parameter. The Mode should be
 * one of AnyOfSpec or AllOfSpec, which provide some commands for the
 * internal implementation. It would be nice to provide typedefs for
 * them, but it is impossible to do so, as we have the Context template
 * parameter as well and C++ doesn't like templated typedefs.
 *
 * The object holds several subexpressions and returns true if all
 * of the subexpressions return true (in case of AllOfSpec Mode) or
 * at last one of them return true (in case of AnyOfSpec Mode). If
 * some subexpression guarantees the result (eg. some returns false
 * in case of AllOfSpec), the rest is not tried for performance
 * reasons.
 */
template<typename Mode, typename Context>
class LogicOperator : public CompoundCheck<Context> {
public:
    /**
     * \brief Add another subexpression.
     *
     * This adds another subexpression to the list of checked expressions.
     * This is usually done shortly after the creation, before using the
     * check for matches.
     *
     * Currently there's no way to place the expression into arbitrary place
     * or to remove it. It might turn out it would be needed in future to
     * optimise or it might even turn out we need shared pointers for it.
     *
     * \param expr The new expression to put inside.
     */
    void addSubexpression(const boost::shared_ptr<Check<Context> >& expr) {
        checks_.push_back(expr);
    }
    /**
     * \brief The current list of subexpressions.
     */
    virtual typename CompoundCheck<Context>::Checks getSubexpressions() const {
        typename CompoundCheck<Context>::Checks result;
        for (typename Checks::const_iterator i(checks_.begin());
             i != checks_.end(); ++i) {
            result.push_back(i->get());
        }
        return (result);
    }
    /**
     * \brief The match of the check.
     *
     * Runs the subexpressions, one by one, and then decides based on that
     * what to return.
     */
    virtual bool matches(const Context& context) const {
        /*
         * This might look slightly complicated. However, this is just
         * generalized version of multi-and or multi-or. The usual
         * implementation of multi-and starts with true and if one with
         * false is found, it turns to be false forever and false is
         * returned. It is exactly the other way around with or.
         *
         * So, if we ever find one that makes it the other one than start
         * (false in case of and, true in case of or), we can just stop and
         * return that one right away. If it meets no such expression, we
         * get to the end and return the default.
         */
        for (typename Checks::const_iterator i(checks_.begin());
             i != checks_.end(); ++i) {
            if (Mode::terminate((*i)->matches(context))) {
                return (!Mode::start());
            }
        }
        return (Mode::start());
    }
private:
    /// \brief List of subexpressions
    typedef typename std::vector<boost::shared_ptr<Check<Context> > > Checks;
    Checks checks_;
};

/**
 * \brief Creator for the LogicOperator compound check.
 *
 * This class can load the ANY and ALL operators from JSON. They expect
 * a list of subexpressions as a parameter, eg. like this:
 *
 * \verbatim
 * {"ANY": [
 *    {"ip": "1.2.3.4"},
 *    {"ip": "5.6.7.8"}
 * ]}
 * \endverbatim
 *
 * It uses the loader to load the subexpressions, therefore whatever is
 * supported there is supported here as well.
 *
 * The Mode template parameter has the same meaning as with LogicOperator,
 * it is used to know which operators to create.
 */
template<typename Mode, typename Context, typename Action = BasicAction>
class LogicCreator : public Loader<Context, Action>::CheckCreator {
public:
    /**
     * \brief Constructor.
     *
     * \param name The name for which the loader will work. In practice,
     *     it will usually be ANY or ALL (depending on the mode), but
     *     anything else can be used as well.
     */
    LogicCreator(const std::string& name) :
        name_(name)
    {}
    /// \brief Returns vector containing the name.
    virtual std::vector<std::string> names() const {
        std::vector<std::string> result;
        result.push_back(name_);
        return (result);
    }
    /**
     * \brief Converts a JSON description into the logic operator.
     *
     * This is the place where the actual loading happens. It creates
     * the logic operator and calls the loader on each of the list
     * elements, placing the result into the logic operator.
     *
     * The first parameter is ignored and is there only to match interface.
     *
     * \param definition The JSON definition of the subexpressions. This must
     *     be a list (if it isn't, the LoaderError is thrown) and the elements
     *     must be loadable by the loader (the exceptions from it are not
     *     caught).
     * \param loader The loader to use for loading of subexpressions.
     */
    virtual boost::shared_ptr<Check<Context> > create(const std::string&,
                                                      data::ConstElementPtr
                                                      definition,
                                                      const Loader<Context,
                                                      Action>& loader)
    {
        std::vector<data::ConstElementPtr> subexprs;
        try {
            subexprs = definition->listValue();
        }
        catch (const data::TypeError&) {
            isc_throw_1(LoaderError, "Logic operator takes list", definition);
        }
        boost::shared_ptr<LogicOperator<Mode, Context> >
            result(new LogicOperator<Mode, Context>);
        for (std::vector<data::ConstElementPtr>::const_iterator
                 i(subexprs.begin());
             i != subexprs.end(); ++i) {
            result->addSubexpression(loader.loadCheck(*i));
        }
        return (result);
    }
    virtual bool allowListAbbreviation() const { return (false); }
private:
    const std::string name_;
};

/**
 * \brief The NOT operator for ACLs.
 *
 * This simply returns the negation of whatever returns the subexpression.
 */
template<typename Context>
class NotOperator : public CompoundCheck<Context> {
public:
    /**
     * \brief Constructor
     *
     * \param expr The subexpression to be negated by this NOT.
     */
    NotOperator(const boost::shared_ptr<Check<Context> >& expr) :
        expr_(expr)
    { }
    /**
     * \brief The list of subexpressions
     *
     * \return The vector will contain single value and it is the expression
     *     passed by constructor.
     */
    virtual typename CompoundCheck<Context>::Checks getSubexpressions() const {
        typename CompoundCheck<Context>::Checks result;
        result.push_back(expr_.get());
        return (result);
    }
    /// \brief The matching function
    virtual bool matches(const Context& context) const {
        return (!expr_->matches(context));
    }
private:
    /// \brief The subexpression
    const boost::shared_ptr<Check<Context> > expr_;
};

template<typename Context, typename Action = BasicAction>
class NotCreator : public Loader<Context, Action>::CheckCreator {
public:
    /**
     * \brief Constructor
     *
     * \param name The name of the NOT operator to be loaded as.
     */
    NotCreator(const std::string& name) :
        name_(name)
    { }
    /**
     * \brief List of the names this loads
     *
     * \return Single-value vector containing the name passed to the
     *     constructor.
     */
    virtual std::vector<std::string> names() const {
        std::vector<std::string> result;
        result.push_back(name_);
        return (result);
    }
    /// \brief Create the check.
    virtual boost::shared_ptr<Check<Context> > create(const std::string&,
                                                      data::ConstElementPtr
                                                      definition,
                                                      const Loader<Context,
                                                      Action>& loader)
    {
        return (boost::shared_ptr<Check<Context> >(new NotOperator<Context>(
                    loader.loadCheck(definition))));
    }
    /**
     * \brief Or-abbreviated form.
     *
     * This returns false. In theory, the NOT operator could be used with
     * the abbreviated form, but it would be confusing. Such syntax is
     * therefore explicitly forbidden.
     */
    virtual bool allowListAbbreviation() const { return (false); }
public:
    const std::string name_;
};

}
}

#endif
