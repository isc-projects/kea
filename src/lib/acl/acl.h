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
#include <boost/noncopyable.hpp>

namespace isc {
namespace acl {

/**
 * \brief Default actions an ACL could perform.
 *
 * This is the default for the ACL class. It is possible to specify any other
 * data type, as the ACL class does nothing about them, but these look
 * reasonable, so they are provided for convenience. It is not specified what
 * exactly these mean and it's up to whoever uses them.
 */
enum BasicAction {
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
 *
 * This is non-copyable. It seems that there's no need to copy them (even
 * when it would be technically possible), so we forbid it just to prevent
 * copying it by accident. If there really is legitimate use, this restriction
 * can be removed.
 *
 * The class is template. It is possible to specify on which context the checks
 * match and which actions it returns. The actions must be copyable
 * for this to work and it is expected to be something small, usually an enum
 * (but other objects are also possible).
 *
 * \note There are protected functions. In fact, you should consider them
 *     private, they are protected so tests can get inside. This class
 *     is not expected to be subclassed in real applications.
 */
template<typename Context, typename Action = BasicAction> class ACL :
    public boost::noncopyable {
public:
    /**
     * \brief Constructor.
     *
     * \param default_action It is the action that is returned when the checked
     *     things "falls off" the end of the list (when no rule matched).
     */
    ACL(const Action& default_action) : default_action_(default_action)
    {}

    /**
     * \brief Pointer to the check.
     *
     * We use the shared pointer, because we are not able to copy the checks.
     * However, we might need to copy the entries (when we concatenate ACLs
     * together in future).
     */
    typedef boost::shared_ptr<const Check<Context> > ConstCheckPtr;

    /**
     * \brief The actual main function that decides.
     *
     * This is the function that takes the entries one by one, checks
     * the context against conditions and if it matches, returns the
     * action that belongs to the first matched entry or default action
     * if nothing matches.
     *
     * \param context The thing that should be checked. It is directly
     *     passed to the checks.
     *
     * \return The action for the ACL entry that first matches the context.
     */
    const Action& execute(const Context& context) const {
        const typename Entries::const_iterator end(entries_.end());
        for (typename Entries::const_iterator i(entries_.begin()); i != end;
             ++i) {
            if (i->first->matches(context)) {
                return (i->second);
            }
        }
        return (default_action_);
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
    void append(ConstCheckPtr check, const Action& action) {
        entries_.push_back(Entry(check, action));
    }
private:
    // Just type abbreviations.
    typedef std::pair<ConstCheckPtr, Action> Entry;
    typedef std::vector<Entry> Entries;
    /// \brief The default action, when nothing mathes.
    const Action default_action_;
    /// \brief The entries we have.
    Entries entries_;
protected:
    /**
     * \brief Get the default action.
     *
     * This is for testing purposes only.
     */
    const Action& getDefaultAction() const {
        return (default_action_);
    }
};

}
}

#endif
