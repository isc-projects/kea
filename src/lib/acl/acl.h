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

#ifndef ACL_ACL_H
#define ACL_ACL_H

#include "check.h"
#include <vector>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace acl {

/**
 * \brief Default actions an ACL could perform.
 *
 * This is the default for the ACL class. It is possible to specify any other
 * data type, as the ACL class does nothing about them, but these look
 * reasonable, so they are provided for convenience.
 */
enum Action {
    ACCEPT,
    REJECT,
    DROP
};

/**
 * \brief The ACL itself.
 *
 * It holds bunch of ordered entries, each one consisting of a check (
 * of any kind, it might be even compound) and an action that is returned
 * whenever the action matches. They are tested in the order and first
 * match counts.
 */
template<typename Context, typename Action = isc::acl::Action> class Acl {
private:
    /**
     * \brief Copy constructor.
     *
     * It is private on purpose, this class is non-copyable, it holds raw
     * pointers of objects we don't know how to copy and there does not seem
     * to be any need to copy ACLs.
     */
    Acl(const Acl<Context, Action>& other);
    /**
     * \brief Assignment operator.
     *
     * It is private on purpose, this class is non-copyable, it holds raw
     * pointers of objects we don't know how to copy and there does not seem
     * to be any need to copy ACLs.
     */
    Acl& operator =(const Acl<Context, Action>& other);
public:
    /**
     * \brief Constructor.
     *
     * \param policy It is the action that is returned when the checked things
     *     "falls off" the end of the list (when no rule matched).
     */
    Acl(Action policy) : policy_(policy)
    { }
    /**
     * \brief Pointer to the check.
     *
     * We use the shared pointer, because we are not able to copy the checks.
     * However, we might need to copy the entries (when we concatenate ACLs
     * together in future).
     */
    typedef boost::shared_ptr<Check<Context> > CheckPtr;
    /**
     * \brief The actual main function that decides.
     *
     * This is the function that takes the entries one by one, checks
     * the context against conditions and if it matches, returns the
     * action that belongs to the first matched entry or policy action
     * if nothing matches.
     * \param context The thing that should be checked. It is directly
     *     passed to the checks.
     */
    Action execute(const Context& context) const {
        // TODO a for cycle
    }
    /**
     * \brief Add new entry at the end of the list.
     *
     * \note We currently allow only adding at the end. This is enough for now,
     * but we may need more when we start implementing some kind optimisations,
     * including replacements, reorderings and removals.
     *
     * \param check The check to test if the thing matches.
     * \param action The action to return when the thing matches this check.
     */
    void append(CheckPtr check, const Action& action) {

    }
private:
    // Just type abbreviations.
    typedef std::pair<CheckPtr, Action> Entry;
    typedef std::vector<Entry> Entries;
    /// \brief The policy.
    Action policy_;
    /// \brief The entries we have.
    Entries entries_;
};

}
}

#endif
