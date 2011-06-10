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

#ifndef ACL_CHECK_H
#define ACL_CHECK_H

#include <vector>
#include <typeinfo>
#include <sstream>

namespace isc {
namespace acl {

/**
 * \brief ACL check base class.
 *
 * It is intended that all ACL checks are inherited (maybe indirectly) from
 * this base class. This will allow us to define new types of checks without
 * changing any of the code that is using it and with the correct
 * implementation even without changing the thing that parses configuration
 * and creates instances of the checks.
 *
 * It is implemented as a template. This allows easy reuse of the code for
 * checking of different types of things (packets of different protocols, etc).
 * We'll implement the loader and compound checks as templates as well (
 * and just make sure they are instantiated for each type of thing we want
 * to check). While most of concrete checks will be specific for one protocol
 * (or whatever the entity we check is), it makes sense to implement some of
 * these as templates as well (for example the IP address check, for whatever
 * context that contains member called ip and has the right methods).
 *
 * The Context carries whatever information might be checked for that protocol
 * (eg. the packet, information where it came from, to what port, ...).
 */
template<typename Context> class Check {
protected:
    /// \brief Constructor.
    ///
    /// Just to make sure this thing is not directly instantiated.
    Check() { }
public:
    /**
     * \brief The check itself.
     *
     * The actual check will be performed here. Every concrete child class
     * will reimplement it and decide based on the context passed if it
     * matches.
     *
     * The caller should expect this method can throw. The list of exceptions
     * isn't restricted, as we don't know what kind of checks will be needed.
     * An exception should be considered as it is impossible to check the
     * condition. It should lead to either blackholing the packet or returning
     * some 500-like error (ServFail).
     *
     * \param context The thing we are trying to match against this check.
     * \return true if the context satisfies the check, false otherwise.
     */
    virtual bool matches(const Context& context) const = 0;

    /**
     * \brief Cost for unknown cost estimate.
     *
     * This indicates that the estimate for cost is not provided. This
     * is arbitrary large value, meaning "somehow longish time". To be
     * on the safe side, we guess more and be just happily suprirised
     * if it turns out to run faster.
     */
    static const unsigned UNKNOWN_COST;

    /**
     * \brief The expected cost of single match.
     *
     * This is here to provide some kind of cost information to optimising
     * routines. It is in units without any real size, just bigger number
     * means the check takes longer time. It is expected to be linear scale.
     * It doesn't need to be exact, but better accuracy might lead to better
     * optimisations. As of writing this, no optimisations exist yet, but
     * are expected to exist in future.
     *
     * The default is UNKNOWN_COST.
     */
    virtual unsigned cost() const {
        return (UNKNOWN_COST);
    }

    /// \brief Virtual destructor, as we're virtual
    virtual ~ Check() { }

    /**
     * \brief Conversion to text.
     *
     * This is meant for debugging purposes, it doesn't have to
     * serialise the whole information stored in this Check.
     *
     * If the check is compound, it should not include the subexpressions
     * (while we're able to build whatever treeish representation using
     * CompoundCheck::subexpressions, we're not able to separate them
     * automatically, as this may produce any kind of free-form string).
     */
    virtual std::string toText() const {
        std::stringstream output;
        output << typeid(*this).name() << "@" << this;
        return (output.rdbuf()->str());
    }
};

// This seems to be the propper way for static template members
template<typename Context> const unsigned Check<Context>::UNKNOWN_COST = 10000;

/**
 * \brief Base class for compound checks.
 *
 * While some checks will be a match against some property of the information
 * passed (eg. the sender's IP address must be in some range), others will
 * combine results of more checks together to get their own. This is base class
 * for the second type, allowing listing of the subexpressions (mostly for
 * debugging purposes to print the whole tree of matches and possible future
 * optimisations which would like to crawl the expression tree).
 */
template<typename Context> class CompoundCheck : public Check<Context> {
public:
    /// \brief Abbreviated name for list of subexpressions
    typedef std::vector<const Check<Context>*> Checks;

    /**
     * \brief Get the list of subexpressions.
     *
     * The result contains pointers to the all subexpressions this check holds
     * (and therefore might call during its own match() function).
     *
     * Using shared pointers looks an overkill here. All the checks must be
     * alive for the whole life of this one and this check will hold their
     * ownership. Therefore the only thing the caller needs to do is to make
     * sure this check is not deleted while it's still using the ones from the
     * result.
     *
     * This method must not throw except for the standard allocation exceptions
     * to allocate the result.
     */
    virtual Checks getSubexpressions() const = 0;

    /**
     * \brief If the result depends only on results of subexpressions.
     *
     * Some optimisations might use the fact that a compound expression is
     * a function of results of its subexpressions (subchecks) only. But
     * some compound checks might want to look into the provided context in
     * their match() as well as looking at the results of the subexpressions.
     *
     * This function informs the optimisation routines if it is safe to use
     * these optimisations.
     *
     * \return true if the check depends only on results of subexpressions
     *    only, false if it examines the context itself as well.
     * \note The default implementation returns true, as it is expected to
     *    be the case in majority of cases.
     */
    virtual bool pure() const { return (true); }

    /**
     * \brief Default compound cost function.
     *
     * It is simply sum of all subexpressions, as an expected upper bound
     * on the cost. This expects that the combining itself is cheap relatively
     * to the checks performed by the subexpressions. In most cases, this
     * should be good enough, but it can be reimplemented in situations
     * where most of the subexpressions will be avoided in usual situations.
     * Replacing the default of 10000 from Check.
     */
    virtual unsigned cost() const {
        Checks checks(getSubexpressions());
        unsigned result(0);
        for (typename Checks::const_iterator i(checks.begin());
             i != checks.end(); ++ i) {
            result += (*i)->cost();
        }
        return (result);
    }
};

}
}

#endif
