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

#ifndef OPTION_H_
#define OPTION_H_

#include <string>
#include <map>
#include <boost/shared_array.hpp>

namespace isc {
namespace dhcp {

class Option {
public:
    typedef std::map<unsigned int, boost::shared_ptr<Option> > Option4Lst;
    typedef std::multimap<unsigned int, boost::shared_ptr<Option> > Option6Lst;

    enum Universe { V4, V6 };

    // ctor, used for options constructed, usually during transmission
    Option(Universe u, unsigned short type); 

    // ctor, used for received options
    // boost::shared_array allows sharing a buffer, but it requires that 
    // different instances share pointer to the whole array, not point
    // to different elements in shared array. Therefore we need to share
    // pointer to the whole array and remember offset where data for
    // this option begins
    Option(Universe u, unsigned short type, boost::shared_array<char> buf, 
           unsigned int offset, 
           unsigned int len);

    // writes option in wire-format to buf, returns pointer to first unused 
    // byte after stored option
    virtual char* pack(char* buf, unsigned int len);

    // parses received buffer, returns pointer to first unused byte 
    // after parsed option
    // TODO: Do we need this overload? Commented out for now
    // virtual const char* unpack(const char* buf, unsigned int len);

    // parses received buffer, returns offset to the first unused byte after
    // parsed option
    virtual unsigned int 
        unpack(boost::shared_array<char> buf, 
               unsigned int buf_len,
               unsigned int offset, 
               unsigned int parse_len);

    virtual std::string toText();

    unsigned short getType();

    // returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual unsigned short len();
    
    // returns if option is valid (e.g. option may be truncated)
    virtual bool valid(); 

    // just to force that every option has virtual dtor
    virtual ~Option(); 

protected:
    virtual char* pack4(char* buf, unsigned short len);
    virtual char* pack6(char* buf, unsigned short len);
    virtual unsigned int unpack4(boost::shared_array<char> buf, 
                                 unsigned int buf_len,
                                 unsigned int offset, 
                                 unsigned int parse_len);
    virtual unsigned int unpack6(boost::shared_array<char> buf, 
                                 unsigned int buf_len,
                                 unsigned int offset, 
                                 unsigned int parse_len);

    Universe universe_;
    unsigned short type_;

    boost::shared_array<char> data_;
    unsigned int data_len_;
    unsigned int offset_; // data is a shared_pointer that points out to the
                          // whole packet. offset_ specifies where data for
                          // this option begins.
    unsigned int len_; // length of data only. Use len() if you want to know 
                       // proper length with option header overhead
    char * value_;

    // 2 different containers are used, because v4 options are unique
    // and v6 allows multiple instances of the same option types
    // originally 2 separate containers were planned. Let's try if we
    // can use a single apporach
    Option6Lst optionLst_;
};

} // namespace isc::dhcp
} // namespace isc

#endif
