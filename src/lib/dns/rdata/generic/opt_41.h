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

#include <string>

#include <dns/rdata.h>

#include <boost/shared_ptr.hpp>

#include <vector>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct OPTImpl;

class OPT : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    // The default constructor makes sense for OPT as it can be empty.
    OPT();
    OPT& operator=(const OPT& source);
    ~OPT();

    class PseudoRR {
    public:
        PseudoRR(uint16_t code,
                 boost::shared_ptr<std::vector<uint8_t> >& data);

        uint16_t getCode() const;
        const uint8_t* getData() const;
        uint16_t getLength() const;

    private:
        uint16_t code_;
        boost::shared_ptr<std::vector<uint8_t> > data_;
    };

    void appendPseudoRR(uint16_t code, const uint8_t* data, uint16_t length);
    const std::vector<PseudoRR>& getPseudoRRs() const;

private:
    OPTImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
