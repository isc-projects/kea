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

#ifndef __TSIG_H
#define __TSIG_H 1

#include <string>
#include <vector>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/message.h>

namespace isc {
namespace dns {

class BadTsigKey : public Exception {
public:
    BadTsigKey(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

//
// This class holds a Tsig key, including all its attributes.
//
class Tsig {
public:
    enum TsigAlgorithm {
        HMACMD5 = 0,
        GSS = 1,
        HMACSHA1 = 2,
        HMACSHA224 = 3,
        HMACSHA265 = 4,
        HMACSHA384 = 5,
        HMACSHA512 = 6,
    };

    Tsig(const Name& name, TsigAlgorithm algorithm,
         const std::string& algorithm_data) :
         name_(name), algorithm_(algorithm), algorithm_data_(algorithm_data) {};

    bool signMessage(const Message& message);
    bool verifyMessage(const Message &message);

private:
    Name name_;
    TsigAlgorithm algorithm_;
    std::string algorithm_data_;
};

}
}

#endif  // __TSIG_H

// Local Variables: 
// mode: c++
// End: 
