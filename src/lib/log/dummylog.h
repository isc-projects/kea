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

#ifndef ISC_DUMMYLOG_H
#define ISC_DUMMYLOG_H 1

#include <string>

namespace isc {
namespace log {

/// Are we doing logging?
extern bool denabled;
/**
 * \short Prefix into logs.
 *
 * The prefix is printed in front of every log message in square brackets.
 * The usual convention is to put the name of program here.
 */
extern std::string dprefix;

/**
 * \short Temporary interface to logging.
 *
 * This is a temporary function to do logging. It has wrong interface currently
 * and should be replaced by something else. Its main purpose now is to mark
 * places where logging should happen. When it is removed, compiler will do
 * our work of finding the places.
 *
 * The only thing it does is printing the program prefix, message and
 * a newline if denabled is true.
 *
 * There are no tests for this function, since it is only temporary and
 * trivial. Tests will be written for the real logging framework when it is
 * created.
 *
 * It has the d in front of the name so it is unlikely anyone will create
 * a real logging function with the same name and the place wouldn't be found
 * as a compilation error.
 *
 * @param message The message to log. The real interface will probably have
 *     more parameters.
 * \param error_flag TODO
 */
void dlog(const std::string& message, bool error_flag=false);

}
}

#endif // ISC_DUMMYLOG_H
