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

#ifndef __QUESTION_H
#define __QUESTION_H 1

#include <iostream>

#include <boost/shared_ptr.hpp>

#include "name.h"
#include "rrclass.h"
#include "rrtype.h"

namespace isc {
namespace dns {

class InputBuffer;
class Question;
typedef boost::shared_ptr<Question> QuestionPtr;

///
/// This is a straightforward implementation of a "DNS question", modeling
/// an entry of the question section of DNS messages.
/// This could also be used as an input parameter for lookups into internal
/// data sources.
///
/// Open issue: we may want to introduce an abstract base class so that we
/// can have multiple concrete implementations (e.g. for better performance)
/// of the base class in a polymorphic way.
class Question {
public:
    Question(InputBuffer& buffer);
    Question(const Name& name, const RRClass& rrclass, const RRType& rrtype) :
        name_(name), rrtype_(rrtype), rrclass_(rrclass)
    {}

    ///
    /// \name Getter methods
    //@{
    const Name& getName() const { return (name_); }
    const RRType& getType() const { return (rrtype_); }
    const RRClass& getClass() const { return (rrclass_); }
    //@}

    std::string toText() const;
    unsigned int toWire(OutputBuffer& buffer) const;
    unsigned int toWire(MessageRenderer& renderer) const;

    bool operator==(const Question& other) const;
    bool operator!=(const Question& other) const
    { return !(*this == other); }
private:
    Name name_;
    RRType rrtype_;
    RRClass rrclass_;
};

std::ostream& operator<<(std::ostream& os, const Question& question);
} // end of namespace dns
} // end of namespace isc
#endif  // __QUESTION_H

// Local Variables: 
// mode: c++
// End: 
