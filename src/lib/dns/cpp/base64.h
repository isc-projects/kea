// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __BASE64_H
#define __BASE64_H 1

#include <string>
#include <vector>

#include <exceptions/exceptions.h>

//
// Note: this helper module isn't specific to the DNS protocol per se.
// We should probably move this to somewhere else, possibly in some common
// utility area.
//

namespace isc {
namespace dns {

///
/// \brief A standard DNS (or ISC) module exception that is thrown a Base64
/// decoder encounters an invalid input.
///
class BadBase64String : public Exception {
public:
    BadBase64String(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

std::string encodeBase64(const std::vector<char>& binary);
void decodeBase64(const std::string& base64, std::vector<char>& result);
}
}

#endif  // __BASE64_H

// Local Variables: 
// mode: c++
// End: 
