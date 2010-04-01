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

#include "config.h"

#include "data.h"

#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp> // for iequals

using namespace std;

namespace {
const unsigned char PROTOCOL_VERSION[4] = { 0x53, 0x6b, 0x61, 0x6e };

const unsigned char ITEM_BLOB = 0x01;
const unsigned char ITEM_HASH = 0x02;
const unsigned char ITEM_LIST = 0x03;
const unsigned char ITEM_NULL = 0x04;
const unsigned char ITEM_BOOL = 0x05;
const unsigned char ITEM_INT  = 0x06;
const unsigned char ITEM_REAL = 0x07;
const unsigned char ITEM_UTF8 = 0x08;
const unsigned char ITEM_MASK = 0x0f;

const unsigned char ITEM_LENGTH_32   = 0x00;
const unsigned char ITEM_LENGTH_16   = 0x10;
const unsigned char ITEM_LENGTH_8    = 0x20;
const unsigned char ITEM_LENGTH_MASK = 0x30;
}

namespace isc {
namespace data {

//
// The following methods are effectively empty, and their parameters are
// unused.  To silence compilers that warn unused function parameters,
// we specify a (compiler dependent) special keyword when available.
// It's defined in config.h, and to avoid including this header file from
// installed files we define the methods here.
//
bool
Element::getValue(int& t UNUSED_PARAM) {
    return false;
}

bool
Element::getValue(double& t UNUSED_PARAM) {
    return false;
}

bool
Element::getValue(bool& t UNUSED_PARAM) {
    return false;
}

bool
Element::getValue(std::string& t UNUSED_PARAM) {
    return false;
}

bool
Element::getValue(std::vector<ElementPtr>& t UNUSED_PARAM) {
    return false;
}

bool
Element::getValue(std::map<std::string, ElementPtr>& t UNUSED_PARAM) {
    return false;
}

bool
Element::setValue(const int v UNUSED_PARAM) {
    return false;
}

bool
Element::setValue(const double v UNUSED_PARAM) {
    return false;
}

bool
Element::setValue(const bool t UNUSED_PARAM) {
    return false;
}

bool
Element::setValue(const std::string& v UNUSED_PARAM) {
    return false;
}

bool
Element::setValue(const std::vector<ElementPtr>& v UNUSED_PARAM) {
    return false;
}

bool
Element::setValue(const std::map<std::string, ElementPtr>& v UNUSED_PARAM)
{
    return false;
}

ElementPtr
Element::get(const int i UNUSED_PARAM) {
    isc_throw(TypeError, "get(int) called on a non-list Element");
}

void
Element::set(const size_t i UNUSED_PARAM, ElementPtr element UNUSED_PARAM) {
    isc_throw(TypeError, "set(int, element) called on a non-list Element");
}

void
Element::add(ElementPtr element UNUSED_PARAM) {
    isc_throw(TypeError, "add() called on a non-list Element");
}

void
Element::remove(const int i UNUSED_PARAM) {
    isc_throw(TypeError, "remove(int) called on a non-list Element");
}

size_t
Element::size() {
    isc_throw(TypeError, "size() called on a non-list Element");
}

ElementPtr
Element::get(const std::string& name UNUSED_PARAM) {
    isc_throw(TypeError, "get(string) called on a non-map Element");
}

void
Element::set(const std::string& name UNUSED_PARAM,
             ElementPtr element UNUSED_PARAM)
{
    isc_throw(TypeError, "set(name, element) called on a non-map Element");
}

void
Element::remove(const std::string& name UNUSED_PARAM) {
    isc_throw(TypeError, "remove(string) called on a non-map Element");
}

bool
Element::contains(const std::string& name UNUSED_PARAM) {
    isc_throw(TypeError, "contains(string) called on a non-map Element");
}

ElementPtr
Element::find(const std::string& identifier UNUSED_PARAM) {
    isc_throw(TypeError, "find(string) called on a non-map Element");
}

bool
Element::find(const std::string& identifier UNUSED_PARAM,
              ElementPtr& t UNUSED_PARAM)
{
    return false;
}

namespace {
inline void
throwParseError(const std::string& error, const std::string& file, int line = 0, int pos = 0)
{
    if (line != 0 || pos != 0) {
        std::stringstream ss;
        ss << error << " in " + file + ":" << line << ":" << pos;
        throw ParseError(ss.str());
    } else {
        throw ParseError(error);
    }
}
}

std::ostream& operator <<(std::ostream &out, const isc::data::ElementPtr& e) {
    return out << e->str();
}

bool operator==(const isc::data::ElementPtr a, const isc::data::ElementPtr b) {
    return a->equals(b);
};

//
// factory functions
//
ElementPtr
Element::create(const int i) {
    try {
        return ElementPtr(new IntElement(i));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const double d) {
    try {
        return ElementPtr(new DoubleElement(d));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const std::string& s) {
    try {
        return ElementPtr(new StringElement(s));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const bool b) {
    try {
        return ElementPtr(new BoolElement(b));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const std::vector<ElementPtr>& v) {
    try {
        return ElementPtr(new ListElement(v));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const std::map<std::string, ElementPtr>& m) {
    try {
        return ElementPtr(new MapElement(m));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}


//
// helper functions for createFromString factory
//
namespace {
bool
char_in(const char c, const char *chars) {
    for (size_t i = 0; i < strlen(chars); ++i) {
        if (chars[i] == c) {
            return true;
        }
    }
    return false;
}

void
skip_chars(std::istream &in, const char *chars, int& line, int& pos) {
    char c = in.peek();
    while (char_in(c, chars) && c != EOF) {
        if (c == '\n') {
            ++line;
            pos = 1;
        } else {
            ++pos;
        }
        in.get();
        c = in.peek();
    }
}

// skip on the input stream to one of the characters in chars
// if another character is found this function returns false
// unless that character is specified in the optional may_skip
//
// the character found is left on the stream
void
skip_to(std::istream &in, const std::string& file, int& line,
        int& pos, const char* chars, const char* may_skip="")
{
    char c = in.get();
    ++pos;
    while (c != EOF) {
        if (c == '\n') {
            pos = 1;
            ++line;
        }
        if (char_in(c, may_skip)) {
            c = in.get();
            ++pos;
        } else if (char_in(c, chars)) {
            while(char_in(in.peek(), may_skip)) {
                if (in.peek() == '\n') {
                    pos = 1;
                    ++line;
                }
                in.get();
                ++pos;
            }
            in.putback(c);
            --pos;
            return;
        } else {
            throwParseError(std::string("'") + c + "' read, one of \"" + chars + "\" expected", file, line, pos);
        }
    }
    throwParseError(std::string("EOF read, one of \"") + chars + "\" expected", file, line, pos);
}

std::string
str_from_stringstream(std::istream &in, const std::string& file, const int line,
                      int& pos) throw (ParseError)
{
    char c = 0;
    std::stringstream ss;
    c = in.get();
    ++pos;
    if (c == '"') {
        c = in.get();
        ++pos;
    } else {
        throwParseError("String expected", file, line, pos);
    }
    while (c != EOF && c != '"') {
        ss << c;
        if (c == '\\' && in.peek() == '"') {
            ss << in.get();
            ++pos;
        }
        c = in.get();
        ++pos;
    }
    return ss.str();
}

std::string
word_from_stringstream(std::istream &in, int& pos) {
    std::stringstream ss;
    while (isalpha(in.peek())) {
        ss << (char) in.get();
    }
    pos += ss.str().size();
    return ss.str();
}

inline int
count_chars_i(int i) {
    int result = 1;
    while (i > 10) {
        ++result;
        i = i / 10;
    }
    return result;
}

inline int
count_chars_d(double d) {
    int result = 1;
    while (d < 1.0) {
        ++result;
        d = d * 10;
    }
    return result;
}

ElementPtr
from_stringstream_int_or_double(std::istream &in, int &pos) {
    int i;
    in >> i;
    pos += count_chars_i(i);
    if (in.peek() == '.') {
        double d;
        in >> d;
        pos += count_chars_d(i);
        d += i;
        return Element::create(d);
    } else {
        return Element::create(i);
    }
}

ElementPtr
from_stringstream_bool(std::istream &in, const std::string& file,
                       const int line, int& pos)
{
    const std::string word = word_from_stringstream(in, pos);
    if (boost::iequals(word, "True")) {
        return Element::create(true);
    } else if (boost::iequals(word, "False")) {
        return Element::create(false);
    } else {
        throwParseError(std::string("Bad boolean value: ") + word, file, line, pos);
        // above is a throw shortcur, return empty is never reached
        return ElementPtr();
    }
}

ElementPtr
from_stringstream_string(std::istream& in, const std::string& file, int& line, int& pos)
{
    return Element::create(str_from_stringstream(in, file, line, pos));
}

ElementPtr
from_stringstream_list(std::istream &in, const std::string& file, int& line, int& pos)
{
    char c = 0;
    std::vector<ElementPtr> v;
    ElementPtr cur_list_element;

    skip_chars(in, " \t\n", line, pos);
    while (c != EOF && c != ']') {
        if (in.peek() != ']') {
            cur_list_element = Element::createFromString(in, file, line, pos);
            v.push_back(cur_list_element);
            skip_to(in, file, line, pos, ",]", " \t\n");
        }
        c = in.get();
        pos++;
    }
    return Element::create(v);
}

ElementPtr
from_stringstream_map(std::istream &in, const std::string& file, int& line,
                      int& pos)
{
    std::map<std::string, ElementPtr> m;
    skip_chars(in, " \t\n", line, pos);
    char c = in.peek();
    if (c == '}') {
        // empty map, skip closing curly
        c = in.get();
    } else {
        while (c != EOF && c != '}') {
            std::pair<std::string, ElementPtr> p;

            p.first = str_from_stringstream(in, file, line, pos);
            if (p.first.length() > 255) {
                // Map tag has one-byte length field in wire format, so the
                // length cannot exceed 255.
                throwParseError("Map tag is too long", file, line, pos);
            }

            skip_to(in, file, line, pos, ":", " \t\n");
            // skip the :
            in.get();
            pos++;
            p.second = Element::createFromString(in, file, line, pos);
            m.insert(p);
            skip_to(in, file, line, pos, ",}", " \t\n");
            c = in.get();
            pos++;
        }
    }
    return Element::create(m);
}
}

ElementPtr
Element::createFromString(std::istream& in) throw(ParseError) {
    int line = 1, pos = 1;
    return createFromString(in, "<istream>", line, pos);
}

ElementPtr
Element::createFromString(std::istream& in, const std::string& file_name) throw(ParseError)
{
    int line = 1, pos = 1;
    return createFromString(in, file_name, line, pos);
}

ElementPtr
Element::createFromString(std::istream &in, const std::string& file, int& line, int& pos) throw(ParseError)
{
    char c = 0;
    ElementPtr element;
    bool el_read = false;
    skip_chars(in, " \n\t", line, pos);
    while (c != EOF && !el_read) {
        c = in.get();
        pos++;
        switch(c) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                in.putback(c);
                element = from_stringstream_int_or_double(in, pos);
                el_read = true;
                break;
            case 't':
            case 'T':
            case 'f':
            case 'F':
                in.putback(c);
                element = from_stringstream_bool(in, file, line, pos);
                el_read = true;
                break;
            case '"':
                in.putback('"');
                element = from_stringstream_string(in, file, line, pos);
                el_read = true;
                break;
            case '[':
                element = from_stringstream_list(in, file, line, pos);
                el_read = true;
                break;
            case '{':
                element = from_stringstream_map(in, file, line, pos);
                el_read = true;
                break;
            case EOF:
                break;
            default:
                throwParseError(std::string("error: unexpected character ") + c, file, line, pos);
                break;
        }
    }
    if (el_read) {
        return element;
    } else {
        throw ParseError("nothing read");
    }
}

ElementPtr
Element::createFromString(const std::string &in) {
    std::stringstream ss;
    ss << in;
    return createFromString(ss, "<string>");
}

//
// a general to_str() function
//
std::string
IntElement::str() {
    std::stringstream ss;
    ss << intValue();
    return ss.str();
}

std::string
DoubleElement::str() {
    std::stringstream ss;
    ss << doubleValue();
    return ss.str();
}

std::string
BoolElement::str() {
    if (b) {
        return "True";
    } else {
        return "False";
    }
}

std::string
StringElement::str() {
    std::stringstream ss;
    ss << "\"";
    ss << stringValue();
    ss << "\"";
    return ss.str();
}

std::string
ListElement::str() {
    std::stringstream ss;
    ss << "[ ";

    const std::vector<ElementPtr>& v = listValue();
    for (std::vector<ElementPtr>::const_iterator it = v.begin();
         it != v.end(); ++it) {
        if (it != v.begin()) {
            ss << ", ";
        }
        ss << (*it)->str();
    }
    ss << " ]";
    return ss.str();
}

std::string
MapElement::str() {
    std::stringstream ss;
    ss << "{";

    const std::map<std::string, ElementPtr>& m = mapValue();
    for (std::map<std::string, ElementPtr>::const_iterator it = m.begin();
         it != m.end(); ++it) {
        if (it != m.begin()) {
            ss << ", ";
        }
        ss << "\"" << (*it).first << "\": ";
        if ((*it).second) {
            ss << (*it).second->str();
        } else {
            ss << "None";
        }
    }
    ss << "}";
    return ss.str();
}

// throws when one of the types in the path (except the one
// we're looking for) is not a MapElement
// returns 0 if it could simply not be found
// should that also be an exception?
ElementPtr
MapElement::find(const std::string& id) {
    const size_t sep = id.find('/');
    if (sep == std::string::npos) {
        return get(id);
    } else {
        ElementPtr ce = get(id.substr(0, sep));
        if (ce) {
            // ignore trailing slash
            if  (sep + 1 != id.size()) {
                return ce->find(id.substr(sep + 1));
            } else {
                return ce;
            }
        } else {
            return ElementPtr();
        }
    }
}

//
// Decode from wire format.
//
namespace {
ElementPtr decode_element(std::stringstream& in, int& in_length);

unsigned char
get_byte(std::stringstream& in) {
    const int c = in.get();
    if (c == EOF) {
        throw DecodeError("End of data while decoding wire format message");
    }

    return c;
}

std::string
decode_tag(std::stringstream& in, int& item_length) {
    char buf[256];

    const int len = get_byte(in);
    item_length--;

    in.read(buf, len);
    if (in.fail()) {
        throw DecodeError();
    }
    buf[len] = 0;
    item_length -= len;

    return std::string(buf, len);
}

ElementPtr
decode_bool(std::stringstream& in) {
    const char c = in.get();
    
    if (c == '1') {
        return Element::create(true);
    } else {
        return Element::create(false);
    }
}

ElementPtr
decode_int(std::stringstream& in) {
    int me;
    return from_stringstream_int_or_double(in, me);
}

ElementPtr
decode_real(std::stringstream& in) {
    int me;
    return from_stringstream_int_or_double(in, me);
}

ElementPtr
decode_blob(std::stringstream& in, const int item_length) {
    vector<char> buf(item_length + 1);

    in.read(&buf[0], item_length);
    if (in.fail()) {
        throw DecodeError();
    }
    buf[item_length] = 0;

    return Element::create(std::string(&buf[0], item_length));
}

ElementPtr
decode_hash(std::stringstream& in, int item_length) {
    std::map<std::string, ElementPtr> m;
    std::pair<std::string, ElementPtr> p;

    while (item_length > 0) {
        p.first = decode_tag(in, item_length);
        p.second = decode_element(in, item_length);
        m.insert(p);
    }

    return Element::create(m);
}

ElementPtr
decode_list(std::stringstream& in, int item_length) {
    std::vector<ElementPtr> v;

    while (item_length > 0) {
        v.push_back(decode_element(in, item_length));
    }
    return Element::create(v);
}

ElementPtr
decode_null() {
    return Element::create("NULL");
}

ElementPtr
decode_element(std::stringstream& in, int& in_length) {
    ElementPtr element;

    const unsigned char type_and_length = get_byte(in);
    const unsigned char type = type_and_length & ITEM_MASK;
    const unsigned char lenbytes = type_and_length & ITEM_LENGTH_MASK;
    in_length--;

    int item_length = 0;
    switch (lenbytes) {
    case ITEM_LENGTH_32:
        item_length |= get_byte(in);
        item_length <<= 8;
        item_length |= get_byte(in);
        item_length <<= 8;
        in_length -= 2;  // only 2 here, we will get more later
    case ITEM_LENGTH_16:
        item_length |= get_byte(in);
        item_length <<= 8;
        in_length--;  // only 1 here
    case ITEM_LENGTH_8:
        item_length |= get_byte(in);
        in_length--;
    }

    in_length -= item_length;

    switch (type) {
    case ITEM_BOOL:
        element = decode_bool(in);
        break;
    case ITEM_INT:
        element = decode_int(in);
        break;
    case ITEM_REAL:
        element = decode_real(in);
        break;
    case ITEM_BLOB:
        element = decode_blob(in, item_length);
        break;
    case ITEM_UTF8:
        // XXXMLG currently identical to decode_blob
        element = decode_blob(in, item_length);
        break;
    case ITEM_HASH:
        element = decode_hash(in, item_length);
        break;
    case ITEM_LIST:
        element = decode_list(in, item_length);
        break;
    case ITEM_NULL:
        element = decode_null();
        break;
    }

    return (element);
}
}

ElementPtr
Element::fromWire(const std::string& s) {
    std::stringstream ss;
    ss << s;
    return fromWire(ss, s.length());
}

ElementPtr
Element::fromWire(std::stringstream& in, int length) {
    //
    // Check protocol version
    //
    for (int i = 0 ; i < 4 ; ++i) {
        const unsigned char version_byte = get_byte(in);
        if (PROTOCOL_VERSION[i] != version_byte) {
            throw DecodeError("Protocol version incorrect");
        }
    }
    length -= 4;

    return (decode_hash(in, length));
}

//
// Encode into wire format.
//

std::string
encode_length(const unsigned int length, unsigned char type) {
    std::stringstream ss;

    if (length <= 0x000000ff) {
        const unsigned char val = (length & 0x000000ff);
        type |= ITEM_LENGTH_8;
        ss << type << val;
    } else if (length <= 0x0000ffff) {
        unsigned char val[2];
        val[0] = (length & 0x0000ff00) >> 8;
        val[1] = (length & 0x000000ff);
        type |= ITEM_LENGTH_16;
        ss << type << val[0] << val[1];
    } else {
        unsigned char val[4];
        val[0] = (length & 0xff000000) >> 24;
        val[1] = (length & 0x00ff0000) >> 16;
        val[2] = (length & 0x0000ff00) >> 8;
        val[3] = (length & 0x000000ff);
        type |= ITEM_LENGTH_32;
        ss << type << val[0] << val[1] << val[2] << val[3];
    }
    return ss.str();
}

std::string
Element::toWire(const int omit_length) {
    std::stringstream ss;
    toWire(ss, omit_length);
    return ss.str();
}

void
StringElement::toWire(std::stringstream& ss,
                      const int omit_length UNUSED_PARAM)
{
    unsigned int length = stringValue().length();
    ss << encode_length(length, ITEM_UTF8) << stringValue();
}

void
IntElement::toWire(std::stringstream& ss,
                   const int omit_length UNUSED_PARAM)
{
    const std::string& s = str();
    ss << encode_length(s.length(), ITEM_INT) << s;
}

void
BoolElement::toWire(std::stringstream& ss,
                    const int omit_length UNUSED_PARAM)
{
    ss << encode_length(1, ITEM_BOOL);
    if (boolValue()) {
        ss << 0x01;
    } else {
        ss << 0x00;
    }
}

void
DoubleElement::toWire(std::stringstream& ss,
                      const int omit_length UNUSED_PARAM)
{
    std::stringstream text;

    text << str();
    const int length = text.str().length();
    ss << encode_length(length, ITEM_REAL) << text.str();
}

void
ListElement::toWire(std::stringstream& ss, const int omit_length) {
    std::stringstream ss2;
    const std::vector<ElementPtr>& v = listValue();
    for (std::vector<ElementPtr>::const_iterator it = v.begin() ;
         it != v.end() ; ++it) {
        (*it)->toWire(ss2, 0);
    }


    if (omit_length) {
        stringbuf *ss2_buf = ss2.rdbuf();
        ss2_buf->pubseekpos(0);
        if (ss2_buf->in_avail() > 0) {
            ss << ss2_buf;
        }
    } else {
        stringbuf *ss2_buf = ss2.rdbuf();
        ss2_buf->pubseekpos(0);
        ss << encode_length(ss2_buf->in_avail(), ITEM_LIST);
        if (ss2_buf->in_avail() > 0) {
            ss << ss2_buf;
        }
    }
}

void
MapElement::toWire(std::stringstream& ss, int omit_length) {
    std::stringstream ss2;

    //
    // If we don't want the length, we will want the protocol header
    //
    if (omit_length) {
        ss2 << PROTOCOL_VERSION[0] << PROTOCOL_VERSION[1];
        ss2 << PROTOCOL_VERSION[2] << PROTOCOL_VERSION[3];
    }

    const std::map<std::string, ElementPtr>& m = mapValue();
    for (std::map<std::string, ElementPtr>::const_iterator it = m.begin();
         it != m.end(); ++it) {
        const size_t taglen = (*it).first.length();
        assert(taglen <= 0xff);
        const unsigned char val = (taglen & 0x000000ff);
        ss2 << val << (*it).first;

        (*it).second->toWire(ss2, 0);
    }

    //
    // add length if needed
    //
    if (omit_length) {
        stringbuf *ss2_buf = ss2.rdbuf();
        ss2_buf->pubseekpos(0);
        if (ss2_buf->in_avail()) {
            ss << ss2_buf;
        }
    } else {
        stringbuf *ss2_buf = ss2.rdbuf();
        ss2_buf->pubseekpos(0);
        ss << encode_length(ss2_buf->in_avail(), ITEM_HASH);
        if (ss2_buf->in_avail()) {
            ss << ss2_buf;
        }
    }
}

bool
MapElement::find(const std::string& id, ElementPtr& t) {
    try {
        ElementPtr p = find(id);
        if (p) {
            t = p;
            return true;
        }
    } catch (const TypeError& e) {
        // ignore
    }
    return false;
}

bool
IntElement::equals(ElementPtr other) {
    return (other->getType() == Element::integer) &&
           (i == other->intValue());
}

bool
DoubleElement::equals(ElementPtr other) {
    return (other->getType() == Element::real) &&
           (d == other->doubleValue());
}

bool
BoolElement::equals(ElementPtr other) {
    return (other->getType() == Element::boolean) &&
           (b == other->boolValue());
}

bool
StringElement::equals(ElementPtr other) {
    return (other->getType() == Element::string) &&
           (s == other->stringValue());
}

bool
ListElement::equals(ElementPtr other) {
    if (other->getType() == Element::list) {
        const int s = size();
        if (s != other->size()) {
            return false;
        }
        for (int i = 0; i < s; ++i) {
            if (!get(i)->equals(other->get(i))) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool
MapElement::equals(ElementPtr other) {
    if (other->getType() == Element::map) {
        std::map<std::string, ElementPtr> m = mapValue();
        for (std::map<std::string, ElementPtr>::const_iterator it = m.begin();
             it != m.end() ; ++it) {
            if (other->contains((*it).first)) {
                if (!get((*it).first)->equals(other->get((*it).first))) {
                    return false;
                }
            } else {
                return false;
            }
        }
        // quickly walk through the other map too, to see if there's
        // anything in there that we don't have. We don't need to
        // compare those elements; if one of them is missing we
        // differ (and if it's not missing the loop above has checked
        // it)
        m = other->mapValue();
        for (std::map<std::string, ElementPtr>::const_iterator it = m.begin();
             it != m.end() ; ++it) {
            if (!contains((*it).first)) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool
isNull(ElementPtr p) {
    return !p;
}

void
removeIdentical(ElementPtr a, const ElementPtr b) {
    if (!b) {
        return;
    }
    if (a->getType() != Element::map || b->getType() != Element::map) {
        isc_throw(TypeError, "Non-map Elements passed to removeIdentical");
    }

    std::map<std::string, ElementPtr> m = a->mapValue();
    for (std::map<std::string, ElementPtr>::const_iterator it = m.begin();
         it != m.end() ; ++it) {
        if (b->contains((*it).first)) {
            if (a->get((*it).first)->equals(b->get((*it).first))) {
                a->remove((*it).first);
            }
        }
    }
}

void
merge(ElementPtr element, const ElementPtr other) {
    if (element->getType() != Element::map ||
        other->getType() != Element::map) {
        isc_throw(TypeError, "merge arguments not MapElements");
    }
    
    std::map<std::string, ElementPtr> m = other->mapValue();
    for (std::map<std::string, ElementPtr>::const_iterator it = m.begin();
         it != m.end() ; ++it) {
        if ((*it).second) {
            element->set((*it).first, (*it).second);
        } else if (element->contains((*it).first)) {
            element->remove((*it).first);
        }
    }
}

}
}
