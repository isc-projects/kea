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

#ifndef __NAME_H
#define __NAME_H 1

#include <string>
#include <vector>

namespace ISC {
namespace DNS {
class Buffer;
class NameCompressor;
class NameDecompressor;

class NameComparisonResult {
public:
    enum NameRelation {
        none = 0,
        contains = 1,
        subdomain = 2,
        equal = 3,
        commonancestor = 4
    };

    explicit NameComparisonResult(int order, int nlabels,
                                  NameRelation relation) :
        order_(order), nlabels_(nlabels), relation_(relation) {}
    int get_order() const { return (order_); }
    int get_common_labels() const { return (nlabels_); }
    NameRelation get_relation() const { return (relation_); }
private:
    int order_;
    int nlabels_;
    NameRelation relation_;
};

class Name {
public:
    Name() : length_(0), labels_(0) {}
    explicit Name(const std::string& namestr) : length_(0), labels_(0)
	{ from_string(namestr); }
    explicit Name(NameDecompressor& decompressor, Buffer& buffer);
    // copy constructor (default cp-ctor should work fine)
    //Name(const Name& orig);
    // destructor (default dtor should work fine)
    //~Name();

    std::string to_text(bool omit_final_dot = false) const;
    void to_wire(Buffer& buffer, NameCompressor& compressor) const;
    size_t get_length() const { return (length_); }
    unsigned int get_labels() const { return (labels_); }
    NameComparisonResult compare(const Name& other) const;
    Name split(unsigned int first, unsigned int n) const;
    Name concatenate(const Name& suffix) const;
    bool is_wildcard() const;
    bool operator==(const Name& other) const;
    bool equals(const Name& other) const; // alias of ==
    bool operator!=(const Name& other) const { return (!(*this == other)); }
    bool nequals(const Name& other) const; // alias of !=
    bool operator<=(const Name& other) const;
    bool leq(const Name& other) const; // alias of <=
    bool operator>=(const Name& other) const;
    bool geq(const Name& other) const; // alias of >=
    bool operator<(const Name& other) const;
    bool lthan(const Name& other) const; // alias of <
    bool operator>(const Name& other) const;
    bool gthan(const Name& other) const; // alias of >

private:
    static const unsigned int MAXWIRE = 255;

    std::string ndata_;
    std::vector<char> offsets_;
    unsigned int length_;
    unsigned int labels_;

    void from_string(const std::string& namestr);
};

std::ostream& operator<<(std::ostream& os, const Name& name);
}
}
#endif // __NAME_H

// Local Variables: 
// mode: c++
// End: 
