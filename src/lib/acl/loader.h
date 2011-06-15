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

#include "acl.h"
#include <cc/data.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace acl {

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
 *     and contain one of "ACCEPT", "REJECT" or "DENY".
 * \note We could define different names or add aliases if needed.
 */
Action defaultActionLoader(data::ConstElementPtr action);

/**
 * \brief Loader of ACLs.
 *
 * The goal of this class is to convert JSON description of an ACL to object
 * of the Acl class (including the checks inside it).
 *
 * The class can be used to load the checks only. This is supposed to be used
 * by compound checks to create the subexpressions.
 *
 * To allow any kind of checks to exist in the application, creators are
 * registered for the names of the checks.
 */
template<typename Context, typename Action = isc::acl::Action> class Loader {
public:
    /**
     * \brief Constructor.
     *
     * \param actionLoader is the loader which will be used to convert actions
     *     from their JSON representation. The default value is suitable for
     *     the isc::acl::Action enum. If you did not specify the second
     *     template argument, you don't need to specify this loader.
     */
    Loader(boost::function1<Action, data::ConstElementPtr> actionLoader =
           &defaultActionLoader)
    { }
    /**
     * \brief Creator of the checks.
     *
     * This can be registered within the Loader and will be used to create the
     * checks.
     */
    class CheckCreator {
    public:
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
         * This function does the actuall creation. It is passed all the
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
         */
        virtual boost::shared_ptr<Check<Context> > create(
            const std::string& name, data::ConstElementPtr definition) = 0;
        /**
         * \brief Is list or-abbreviation allowed?
         *
         * If this returns true and the parameter is list, the loader will
         * call the create method with each element of the list and aggregate
         * all the results in OR compound check. If it is false, the parameter
         * is passed verbatim no matter if it is or isn't a list.
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
     * LoaderError exception is thrown.
     *
     * \param creator Shared pointer to the creator.
     * \note We don't support deregistration yet, but it is expected it will
     *     be needed in future, when we have some kind of plugins. These
     *     plugins might want to unload, in which case they would need to
     *     deregister their creators. It is expected they would pass the same
     *     pointer to such method as they pass here.
     */
    void registerCreator(boost::shared_ptr<CheckCreator> creator);
    /**
     * \brief Load a check.
     *
     * This parses a check dict (block) and calls a creator (or creators, if
     * more than one check is found inside) for it. It ignores the "action"
     * key, as it is a reserved keyword used to specify actions inside the
     * ACL.
     *
     * This may throw LoaderError if it is not a dict or if some of the type
     * names is not known (there's no creator registered for it). The
     * exceptions from creators aren't caught.
     *
     * \param description The JSON description of the check.
     */
    boost::shared_ptr<Check<Context> > loadCheck(const data::ConstElementPtr&
                                                 description);
    /**
     * \brief Load an ACL.
     *
     * This parses an ACL list, creates the checks and actions of each element
     * and returns it. It may throw LoaderError if it isn't a list or the
     * "action" key is missing in some element. Also, no exceptions from
     * loadCheck (therefore from whatever creator is used) and from the
     * actionLoader passed to constructor are not caught.
     *
     * \param description The JSON list of ACL.
     */
    boost::shared_ptr<Acl<Context, Action> > load(const data::ConstElementPtr&
                                                  description);
};

}
}

#endif
