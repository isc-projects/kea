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

#ifndef ACL_LOADER_H
#define ACL_LOADER_H

#include <exceptions/exceptions.h>
#include <acl/acl.h>
#include <cc/data.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

namespace isc {
namespace acl {

class AnyOfSpec;
class AllOfSpec;
template<typename Mode, typename Context> class LogicOperator;

/**
 * \brief Exception for bad ACL specifications.
 *
 * This will be thrown by the Loader if the ACL description is malformed
 * in some way.
 *
 * It also can hold optional JSON element where was the error detected, so
 * it can be examined.
 *
 * Checks may subclass this exception for similar errors if they see it fit.
 */
class LoaderError : public BadValue {
private:
    const data::ConstElementPtr element_;
public:
    /**
     * \brief Constructor.
     *
     * Should be used with isc_throw if the fourth argument isn't used.
     *
     * \param file The file where the throw happened.
     * \param line Similar as file, just for the line number.
     * \param what Human readable description of what happened.
     * \param element This might be passed to hold the JSON element where
     *     the error was detected.
     */
    LoaderError(const char* file, size_t line, const char* what,
                data::ConstElementPtr element = data::ConstElementPtr()) :
        BadValue(file, line, what),
        element_(element)
    {}

    ~ LoaderError() throw() {}

    /**
     * \brief Get the element.
     *
     * This returns the element where the error was detected. Note that it
     * might be NULL in some situations.
     */
    const data::ConstElementPtr& element() const {
        return (element_);
    }
};

/**
 * \brief Loader of the default actions of ACLs.
 *
 * Declared outside the Loader class, as this one does not need to be
 * templated. This will throw LoaderError if the parameter isn't string
 * or if it doesn't contain one of the accepted values.
 *
 * \param action The JSON representation of the action. It must be a string
 *     and contain one of "ACCEPT", "REJECT" or "DROP.
 * \note We could define different names or add aliases if needed.
 */
BasicAction defaultActionLoader(data::ConstElementPtr action);

/**
 * \brief Loader of ACLs.
 *
 * The goal of this class is to convert JSON description of an ACL to object
 * of the ACL class (including the checks inside it).
 *
 * The class can be used to load the checks only. This is supposed to be used
 * by compound checks to create the subexpressions.
 *
 * To allow any kind of checks to exist in the application, creators are
 * registered for the names of the checks.
 *
 * An ACL definition looks like this:
 * \verbatim
 [
   {
      "action": "ACCEPT",
      "match-type": <parameter>
   },
   {
      "action": "REJECT",
      "match-type": <parameter>,
      "another-match-type": [<parameter1>, <parameter2>]
   },
   {
      "action": "DROP"
   }
 ]
 \endverbatim
 *
 * This is a list of elements. Each element must have an "action"
 * entry/keyword. That one specifies which action is returned if this
 * element matches (the value of the key is passed to the action loader
 * (see the constructor). It may be any piece of JSON which the action
 * loader expects.
 *
 * The rest of the element are matches. The left side is the name of the
 * match type (for example match for source IP address or match for message
 * size). The parameter is whatever is needed to describe the match and
 * depends on the match type, the loader passes it verbatim to creator
 * of that match type.
 *
 * There may be multiple match types in single element. In such case, all
 * of the matches must match for the element to take action (so, in the second
 * element, both "match-type" and "another-match-type" must be satisfied).
 * If there's no match in the element, the action is taken/returned without
 * conditions, every time (makes sense as the last entry, as the ACL will
 * never get past it).
 *
 * The second entry shows another thing - if there's a list as the value
 * for some match and the match itself is not expecting a list, it is taken
 * as an "or" - a match for at last one of the choices in the list must match.
 * So, for the second entry, both "match-type" and "another-match-type" must
 * be satisfied, but the another one is satisfied by either parameter1 or
 * parameter2.
 */
template<typename Context, typename Action = BasicAction> class Loader {
public:
    /**
     * \brief Constructor.
     *
     * \param defaultAction The default action for created ACLs.
     * \param actionLoader is the loader which will be used to convert actions
     *     from their JSON representation. The default value is suitable for
     *     the BasicAction enum. If you did not specify the second
     *     template argument, you don't need to specify this loader.
     */
    Loader(const Action& defaultAction,
           const boost::function1<Action, data::ConstElementPtr>
               &actionLoader = &defaultActionLoader) :
        default_action_(defaultAction),
        action_loader_(actionLoader)
    {}

    /**
     * \brief Creator of the checks.
     *
     * This can be registered within the Loader and will be used to create the
     * checks. It is expected multiple creators (for multiple types, one can
     * handle even multiple names) will be created and registered to support
     * range of things we could check. This allows for customizing/extending
     * the loader.
     */
    class CheckCreator {
    public:
        /** \brief Virtual class needs virtual destructor */
        virtual ~CheckCreator() {}

        /**
         * \brief List of names supported by this loader.
         *
         * List of all names for which this loader is able to create the
         * checks. There can be multiple names, to support both aliases
         * to the same checks and creators capable of creating multiple
         * types of checks.
         */
        virtual std::vector<std::string> names() const = 0;

        /**
         * \brief Creates the check.
         *
         * This function does the actual creation. It is passed all the
         * relevant data and is supposed to return shared pointer to the
         * check.
         *
         * It is expected to throw the LoaderError exception when the
         * definition is invalid.
         *
         * \param name The type name of the check. If the creator creates
         *     only one type of check, it can safely ignore this parameter.
         * \param definition The part of JSON describing the parameters of
         *     check. As there's no way for the loader to know how the
         *     parameters might look like, they are not checked in any way.
         *     Therefore it's up to the creator (or the check being created)
         *     to validate the data and throw if it is bad.
         * \param loader Current loader calling this creator. This can be used
         *     to load subexpressions in case of compound check.
         */
        virtual boost::shared_ptr<Check<Context> > create(
            const std::string& name, data::ConstElementPtr definition,
            const Loader<Context, Action>& loader) = 0;

        /**
         * \brief Is list or-abbreviation allowed?
         *
         * If this returns true and the parameter (eg. the value we check
         * against, the one that is passed as the second parameter of create)
         * is list, the loader will call the create method with each element of
         * the list and aggregate all the results in OR compound check. If it
         * is false, the parameter is passed verbatim no matter if it is or
         * isn't a list. For example, IP check will have this as true (so
         * multiple IP addresses can be passed as options), but AND operator
         * will return false and handle the list of subexpressions itself.
         *
         * The rationale behind this is that it is common to specify list of
         * something that matches (eg. list of IP addresses).
         */
        virtual bool allowListAbbreviation() const {
            return (true);
        }
    };

    /**
     * \brief Register another check creator.
     *
     * Adds a creator to the list of known ones. The creator's list of names
     * must be disjoint with the names already known to the creator or the
     * LoaderError exception is thrown. In such case, the creator is not
     * registered under any of the names. In case of other exceptions, like
     * bad_alloc, only weak exception safety is guaranteed.
     *
     * \param creator Shared pointer to the creator.
     * \note We don't support deregistration yet, but it is expected it will
     *     be needed in future, when we have some kind of plugins. These
     *     plugins might want to unload, in which case they would need to
     *     deregister their creators. It is expected they would pass the same
     *     pointer to such method as they pass here.
     */
    void registerCreator(boost::shared_ptr<CheckCreator> creator) {
        // First check we can insert all the names
        typedef std::vector<std::string> Strings;
        const Strings names(creator->names());
        for (Strings::const_iterator i(names.begin()); i != names.end();
             ++i) {
            if (creators_.find(*i) != creators_.end()) {
                isc_throw(LoaderError, "The loader already contains creator "
                          "named " << *i);
            }
        }
        // Now insert them
        for (Strings::const_iterator i(names.begin()); i != names.end();
             ++i) {
            creators_[*i] = creator;
        }
    }

    /**
     * \brief Load a check.
     *
     * This parses a check dict (block, the one element of ACL) and calls a
     * creator (or creators, if more than one check is found inside) for it. It
     * ignores the "action" key, as it is a reserved keyword used to specify
     * actions inside the ACL.
     *
     * This may throw LoaderError if it is not a dict or if some of the type
     * names is not known (there's no creator registered for it). The
     * exceptions from creators aren't caught.
     *
     * \param description The JSON description of the check.
     */
    boost::shared_ptr<Check<Context> > loadCheck(const data::ConstElementPtr&
                                                 description) const
    {
        // Get the description as a map
        typedef std::map<std::string, data::ConstElementPtr> Map;
        Map map;
        try {
            map = description->mapValue();
        }
        catch (const data::TypeError&) {
            isc_throw_1(LoaderError, "Check description is not a map",
                        description);
        }
        // Call the internal part with extracted map
        return (loadCheck(description, map));
    }

    /**
     * \brief Load an ACL.
     *
     * This parses an ACL list, creates the checks and actions of each element
     * and returns it.
     *
     * No exceptions from \c loadCheck (therefore from whatever creator is
     * used) and from the actionLoader passed to constructor are caught.
     *
     * \exception InvalidParameter The given element is NULL (most likely a
     * caller's bug)
     * \exception LoaderError The given element isn't a list or the
     * "action" key is missing in some element
     *
     * \param description The JSON list of ACL.
     *
     * \return The newly created ACL object
     */
    boost::shared_ptr<ACL<Context, Action> > load(const data::ConstElementPtr&
                                                  description) const
    {
        if (!description) {
            isc_throw(isc::InvalidParameter,
                      "Null description is passed to ACL loader");
        }

        // We first check it's a list, so we can use the list reference
        // (the list may be huge)
        if (description->getType() != data::Element::list) {
            isc_throw_1(LoaderError, "ACL not a list", description);
        }
        // First create an empty ACL
        const List &list(description->listValue());
        boost::shared_ptr<ACL<Context, Action> > result(
            new ACL<Context, Action>(default_action_));
        // Run trough the list of elements
        for (List::const_iterator i(list.begin()); i != list.end(); ++i) {
            Map map;
            try {
                map = (*i)->mapValue();
            }
            catch (const data::TypeError&) {
                isc_throw_1(LoaderError, "ACL element not a map", *i);
            }
            // Create an action for the element
            const Map::const_iterator action(map.find("action"));
            if (action == map.end()) {
                isc_throw_1(LoaderError, "No action in ACL element", *i);
            }
            const Action acValue(action_loader_(action->second));
            // Now create the check if there's one
            if (map.size() >= 2) { // One is the action, another one the check
                result->append(loadCheck(*i, map), acValue);
            } else {
                // In case there's no check, this matches every time. We
                // simulate it by our own private "True" check.
                result->append(boost::shared_ptr<Check<Context> >(new True()),
                               acValue);
            }
        }
        return (result);
    }

private:
    // Some type aliases to save typing
    typedef std::map<std::string, boost::shared_ptr<CheckCreator> > Creators;
    typedef std::map<std::string, data::ConstElementPtr> Map;
    typedef std::vector<data::ConstElementPtr> List;
    // Private members
    Creators creators_;
    const Action default_action_;
    const boost::function1<Action, data::ConstElementPtr> action_loader_;

    /**
     * \brief Internal version of loadCheck.
     *
     * This is the internal part, shared between load and loadCheck.
     * \param description The bit of JSON (used in exceptions).
     * \param map The extracted map describing the check. It does change
     *     the map.
     */
    boost::shared_ptr<Check<Context> > loadCheck(const data::ConstElementPtr&
                                                 description, Map& map) const
    {
        // Remove the action keyword
        map.erase("action");
        // Now, do we have any definition? Or is it and abbreviation?
        switch (map.size()) {
            case 0:
                isc_throw_1(LoaderError, "Check description is empty",
                            description);
            case 1: {
                // Get the first and only item
                const Map::const_iterator checkDesc(map.begin());
                const std::string& name(checkDesc->first);
                const typename Creators::const_iterator
                    creatorIt(creators_.find(name));
                if (creatorIt == creators_.end()) {
                    isc_throw_1(LoaderError, "No creator for ACL check " <<
                                name, description);
                }
                if (creatorIt->second->allowListAbbreviation() &&
                    checkDesc->second->getType() == data::Element::list) {
                    // Or-abbreviated form - create an OR and put everything
                    // inside.
                    const std::vector<data::ConstElementPtr>&
                        params(checkDesc->second->listValue());
                    boost::shared_ptr<LogicOperator<AnyOfSpec, Context> >
                        oper(new LogicOperator<AnyOfSpec, Context>);
                    for (std::vector<data::ConstElementPtr>::const_iterator
                             i(params.begin());
                         i != params.end(); ++i) {
                        oper->addSubexpression(
                            creatorIt->second->create(name, *i, *this));
                    }
                    return (oper);
                }
                // Create the check and return it
                return (creatorIt->second->create(name, checkDesc->second,
                                                  *this));
            }
            default: {
                // This is the AND-abbreviated form. We need to create an
                // AND (or "ALL") operator, loop trough the whole map and
                // fill it in. We do a small trick - we create bunch of
                // single-item maps, call this loader recursively (therefore
                // it will get into the "case 1" branch, where there is
                // the actual loading) and use the results to fill the map.
                //
                // We keep the description the same, there's nothing we could
                // take out (we could create a new one, but that would be
                // confusing, as it is used for error messages only).
                boost::shared_ptr<LogicOperator<AllOfSpec, Context> >
                    oper(new LogicOperator<AllOfSpec, Context>);
                for (Map::const_iterator i(map.begin()); i != map.end(); ++i) {
                    Map singleSubexpr;
                    singleSubexpr.insert(*i);
                    oper->addSubexpression(loadCheck(description,
                                                     singleSubexpr));
                }
                return (oper);
            }
        }
    }

    /**
     * \brief Check that always matches.
     *
     * This one is used internally for ACL elements without condition. We may
     * want to make this publicly accesible sometime maybe, but for now,
     * there's no need.
     */
    class True : public Check<Context> {
    public:
        virtual bool matches(const Context&) const { return (true); };
        virtual unsigned cost() const { return (1); }
        // We don't write "true" here, as this one was created using empty
        // input
        virtual std::string toText() const { return ""; }
    };
};

}
}

/*
 * This include at the end of the file is unusual. But we need to include it,
 * we use template classes from there. However, they need to be present only
 * at instantiation of our class, which will happen below this header.
 *
 * The problem is, the header uses us as well, therefore there's a circular
 * dependency. If we loaded it at the beginning and someone loaded us first,
 * the logic_check header wouldn't have our definitions. This way, no matter
 * in which order they are loaded, the definitions from this header will be
 * above the ones from logic_check.
 */
#include "logic_check.h"

#endif

// Local Variables:
// mode: c++
// End:
