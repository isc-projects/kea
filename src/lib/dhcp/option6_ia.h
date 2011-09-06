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

#ifndef OPTION_IA_H_
#define OPTION_IA_H_

#include "option.h"

namespace isc {
namespace dhcp {

class Option6IA: public Option {
        
public:
    // ctor, used for options constructed, usually during transmission
    Option6IA(Universe u, unsigned short type, unsigned int iaid); 

    // ctor, used for received options
    // boost::shared_array allows sharing a buffer, but it requires that 
    // different instances share pointer to the whole array, not point
    // to different elements in shared array. Therefore we need to share
    // pointer to the whole array and remember offset where data for
    // this option begins
    Option6IA(Universe u, unsigned short type, boost::shared_array<char> buf, 
              unsigned int buf_len,
              unsigned int offset, 
              unsigned int len);
    
    // writes option in wire-format to buf, returns pointer to first unused 
    // byte after stored option
    unsigned int
    pack(boost::shared_array<char> buf, unsigned int buf_len, 
         unsigned int offset);

    // parses received buffer, returns offset to the first unused byte after
    // parsed option
    virtual unsigned int 
    unpack(boost::shared_array<char> buf, 
           unsigned int buf_len,
           unsigned int offset, 
           unsigned int parse_len);

    virtual std::string toText(int indent = 0);

    void setT1(unsigned int t1) { t1_=t1; }
    void setT2(unsigned int t2) { t2_=t2; }

    unsigned int getIAID() { return iaid_; }
    unsigned int getT1()   { return t1_; }
    unsigned int getT2()   { return t2_; }

    // returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual unsigned short len();

protected:
    unsigned int iaid_;
    unsigned int t1_;
    unsigned int t2_;
};

} // isc::dhcp namespace
} // isc namespace
    
#endif /* OPTION_IA_H_ */
