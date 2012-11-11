// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef FETCHABLE_H
#define FETCHABLE_H

/**
 * \file fetchable.h
 * \short Interface of information that can be fetched.
 */

namespace isc {
namespace nsas {

/**
 * \short Interface of information that can be fetched.
 *
 * This just holds a state of information that can be fetched from somewhere.
 * No locking is performed, if it is desirable, it should be locked manually.
 */
class Fetchable {
    public:
        /// \short States the Fetchable object can be in.
        enum State {
            /// \short No one yet asked for the information.
            NOT_ASKED,
            /// \short The information is too old and should not be used.
            EXPIRED,
            /// \short The information is asked for but it did not arrive.
            IN_PROGRESS,
            /// \short It is not possible to get the information.
            UNREACHABLE,
            /// \short The information is already present.
            READY
        };
        /// \short Constructors
        //@{
        /// This creates the Fetchable object in the given state.
        Fetchable(State state = NOT_ASKED) :
            state_(state)
        { }
        //@}
        /// \short Getter and setter of current state.
        //@{
        State getState() const { return state_; }
        void setState(State state) { state_ = state; }
        //@}
    private:
        State state_;
};

} // namespace nsas
} // namespace isc

#endif // FETCHABLE_H
