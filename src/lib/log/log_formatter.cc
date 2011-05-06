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

#include <log/log_formatter.h>

using namespace std;
using namespace boost;

namespace isc {
namespace log {

void
replacePlaceholder(string* message, const string& arg,
                   const unsigned placeholder)
{
    string mark("%" + lexical_cast<string>(placeholder));
    size_t pos(message->find(mark));
    if (pos != string::npos) {
        message->replace(pos, mark.size(), arg);
    } else {
        // We're missing the placeholder, so add some complain
        message->append(" @@Missing placeholder " + mark + " for '" + arg +
                        "'@@");
    }
}

}
}
