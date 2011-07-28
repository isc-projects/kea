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

#ifndef __TXT_LIKE_H
#define __TXT_LIKE_H 1

#include <stdint.h>

#include <string>
#include <vector>

using namespace std;
using namespace isc::util;

template<class RTYPE, uint16_t typeCode>class TXT_LIKE : public Rdata {
public:
    TXT_LIKE(InputBuffer& buffer, size_t rdata_len) {
	if (rdata_len > MAX_RDLENGTH) {
	    isc_throw(InvalidRdataLength, "RDLENGTH too large: " << rdata_len);
	}

	if (rdata_len == 0) {       // note that this couldn't happen in the loop.
	    isc_throw(DNSMessageFORMERR,
		      "Error in parsing " + RRParamRegistry::getRegistry().codeToTypeText(typeCode)
		     + " RDATA: 0-length character string");
	}

	do {
	    const uint8_t len = buffer.readUint8();
	    if (rdata_len < len + 1) {
		isc_throw(DNSMessageFORMERR,
			  "Error in parsing " + RRParamRegistry::getRegistry().codeToTypeText(typeCode)
			 + " RDATA: character string length is too large: " << static_cast<int>(len));
	    }
	    vector<uint8_t> data(len + 1);
	    data[0] = len;
	    buffer.readData(&data[0] + 1, len);
	    string_list_.push_back(data);

	    rdata_len -= (len + 1);
	} while (rdata_len > 0);
    }

    explicit TXT_LIKE(const std::string& txtstr) {
	// TBD: this is a simple, incomplete implementation that only supports
	// a single character-string.

	size_t length = txtstr.size();
	size_t pos_begin = 0;

	if (length > 1 && txtstr[0] == '"' && txtstr[length - 1] == '"') {
	    pos_begin = 1;
	    length -= 2;
	}

	if (length > MAX_CHARSTRING_LEN) {
	    isc_throw(CharStringTooLong, RRParamRegistry::getRegistry().codeToTypeText(typeCode)
			 + " RDATA construction from text: string length is too long: " << length);
	}

	// TBD: right now, we don't support escaped characters
	if (txtstr.find('\\') != string::npos) {
	    isc_throw(InvalidRdataText, RRParamRegistry::getRegistry().codeToTypeText(typeCode)
			+ " RDATA from text: escaped character is currently not supported: " << txtstr);
	}

	vector<uint8_t> data;
	data.reserve(length + 1);
	data.push_back(length);
	data.insert(data.end(), txtstr.begin() + pos_begin,
		    txtstr.begin() + pos_begin + length);
	string_list_.push_back(data);
    }

    TXT_LIKE(const RTYPE& other) :
	Rdata(), string_list_(other.string_list_)
    {}

    void
    toWire(OutputBuffer& buffer) const {
	for (vector<vector<uint8_t> >::const_iterator it = string_list_.begin();
	     it != string_list_.end();
	     ++it)
	{
	    buffer.writeData(&(*it)[0], (*it).size());
	}
    }

    void
    toWire(AbstractMessageRenderer& renderer) const {
	for (vector<vector<uint8_t> >::const_iterator it = string_list_.begin();
	     it != string_list_.end();
	     ++it)
	{
	    renderer.writeData(&(*it)[0], (*it).size());
	}
    }

    string
    toText() const {
	string s;

	// XXX: this implementation is not entirely correct.  for example, it
	// should escape double-quotes if they appear in the character string.
	for (vector<vector<uint8_t> >::const_iterator it = string_list_.begin();
	     it != string_list_.end();
	     ++it)
	{
	    if (!s.empty()) {
		s.push_back(' ');
	    }
	    s.push_back('"');
	    s.insert(s.end(), (*it).begin() + 1, (*it).end());
	    s.push_back('"');
	}

	return (s);
    }

    int
    compare(const Rdata& other) const {
	const RTYPE& other_txt = dynamic_cast<const RTYPE&>(other);

	// This implementation is not efficient.  Revisit this (TBD).
	OutputBuffer this_buffer(0);
	toWire(this_buffer);
	size_t this_len = this_buffer.getLength();

	OutputBuffer other_buffer(0);
	other_txt.toWire(other_buffer);
	const size_t other_len = other_buffer.getLength();

	const size_t cmplen = min(this_len, other_len);
	const int cmp = memcmp(this_buffer.getData(), other_buffer.getData(),
			       cmplen);
	if (cmp != 0) {
	    return (cmp);
	} else {
	    return ((this_len == other_len) ? 0 :
		    (this_len < other_len) ? -1 : 1);
	}
    }

private:
    /// Note: this is a prototype version; we may reconsider
    /// this representation later.
    std::vector<std::vector<uint8_t> > string_list_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE

#endif //  __TXT_LIKE_H

// Local Variables: 
// mode: c++
// End: 
