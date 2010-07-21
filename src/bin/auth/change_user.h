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
/// This function changes the user of the authoritative server process.
///
/// \c username can be either a textual user name or its numeric ID.
/// If the specified user name (or ID) doesn't specify a local user ID
/// or the user originally starting the process doesn't have a permission
/// of changing the user to \c username, this function throws an exception
/// of class \c FatalError.
///
/// \param username User name or ID of the new effective user.
void changeUser(const char* const username);

#endif // __CHANGE_USER_H

// Local Variables:
// mode: c++
// End:
