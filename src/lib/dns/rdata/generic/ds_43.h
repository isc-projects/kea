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

// BEGIN_HEADER_GUARD

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <util/buffer.h>
#include <util/encode/hex.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <stdio.h>
#include <time.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

#include <dns/rdata/generic/detail/ds_like.h>

class DS : public DS_LIKE<DS, 43> {
    friend class DS_LIKE<DS, 43>;
    static string const id;

public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

};

///    explicit DS(const std::string& type_str);
inline DS::DS(const std::string& type_str) : DS_LIKE<DS, 43>(type_str) {}

///    DS(isc::util::InputBuffer& buffer, size_t rdata_len);
inline DS::DS(isc::util::InputBuffer& buffer, size_t rdata_len) : DS_LIKE<DS, 43>(buffer, rdata_len) {}

///    DS(const DS& other);
inline DS::DS(const DS& other) : DS_LIKE<DS, 43>(other) {}

///    virtual std::string toText() const;
inline std::string DS::toText() const
{
    return DS_LIKE<DS, 43>::toText();
}

///    virtual void toWire(isc::util::OutputBuffer& buffer) const;
inline void DS::toWire(isc::util::OutputBuffer& buffer) const
{
    DS_LIKE<DS, 43>::toWire(buffer);
}

///    virtual void toWire(AbstractMessageRenderer& renderer) const;
inline void DS::toWire(AbstractMessageRenderer& renderer) const
{
    DS_LIKE<DS, 43>::toWire(renderer);
}

///    virtual int compare(const Rdata& other) const;
inline int DS::compare(const Rdata& other) const
{
    return DS_LIKE<DS, 43>::compare(other);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
