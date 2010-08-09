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

// $Id$

#ifndef __CHANGE_USER_H
#define __CHANGE_USER_H 1

/// \brief Change the run time user.
///
/// This function changes the user and its group of the authoritative server
/// process.
///
/// On success the user ID of the process is changed to the specified user,
/// and the group is changed to that of the new user.
///
/// This is considered a short term workaround until we develop clearer
/// privilege separation, where the server won't even have to open privileged
/// ports and can be started by a non privileged user from the beginning.
/// This function therefore ignores some corner case problems (see below)
/// which we would address otherwise.
///
/// \c username can be either a textual user name or its numeric ID.
/// If the specified user name (or ID) doesn't specify a local user ID
/// or the user originally starting the process doesn't have a permission
/// of changing the user to \c username, this function throws an exception
/// of class \c FatalError.
///
/// This function internally uses system libraries that do not guarantee
/// reentrancy.  In fact, it doesn't even expect to be called more than once.
/// The behavior is undefined if this function is called from multiple threads
/// simultaneously or more generally called multiple times.
///
/// This function only offers the basic exception guarantee, that is, if
/// an exception is thrown from this function, it's possible that an exception
/// is thrown after changing the group ID.  This function doesn't recover
/// from that situation.  In practice, the process is expected to consider
/// this event a fatal error and will immediately exit, and shouldn't cause
/// a real trouble.
///
/// \param username User name or ID of the new effective user.
void changeUser(const char* const username);

#endif // __CHANGE_USER_H

// Local Variables:
// mode: c++
// End:
