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

#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <auth/common.h>

using namespace boost;

void
changeUser(const char* const username) {
    const struct passwd *runas_pw = NULL;

    runas_pw = getpwnam(username);
    endpwent();
    if (runas_pw == NULL) {
        try {
            runas_pw = getpwuid(lexical_cast<uid_t>(username));
            endpwent();
        } catch (const bad_lexical_cast&) {
            ;                   // fall through to isc_throw below.
        }
    }
    if (runas_pw == NULL) {
        isc_throw(FatalError, "Unknown user name or UID:" << username);
    }

    if (setgid(runas_pw->pw_gid) < 0) {
        isc_throw(FatalError, "setgid() failed: " << strerror(errno));
    }

    if (setuid(runas_pw->pw_uid) < 0) {
        isc_throw(FatalError, "setuid() failed: " << strerror(errno));
    }
}
