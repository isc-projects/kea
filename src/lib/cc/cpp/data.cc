
#include "data.h"

#include <cstdio>
#include <iostream>
#include <sstream>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace ISC::Data;

const unsigned char PROTOCOL_VERSION[4] = { 0x53, 0x6b, 0x61, 0x6e };

const unsigned char ITEM_DATA = 0x01;
const unsigned char ITEM_HASH = 0x02;
const unsigned char ITEM_LIST = 0x03;
const unsigned char ITEM_NULL = 0x04;
const unsigned char ITEM_MASK = 0x0f;

const unsigned char ITEM_LENGTH_32   = 0x00;
const unsigned char ITEM_LENGTH_16   = 0x10;
const unsigned char ITEM_LENGTH_8    = 0x20;
const unsigned char ITEM_LENGTH_MASK = 0x30;

std::ostream& operator <<(std::ostream &out, const ISC::Data::ElementPtr& e) {
    return out << e->str();
}

//
// factory functions
//
ElementPtr
Element::create(const int i)
{
    try {
        return ElementPtr(new IntElement(i));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const double d)
{
    try {
        return ElementPtr(new DoubleElement(d));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const std::string& s)
{
    try {
        return ElementPtr(new StringElement(s));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const bool b)
{
    try {
        cout << "creating boolelement" << endl;
        return ElementPtr(new BoolElement(b));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const std::vector<ElementPtr>& v)
{
    try {
        return ElementPtr(new ListElement(v));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}

ElementPtr
Element::create(const std::map<std::string, ElementPtr>& m)
{
    try {
        return ElementPtr(new MapElement(m));
    } catch (std::bad_alloc) {
        return ElementPtr();
    }
}


//
// helper functions for create_from_string factory
// these should probably also be moved to member functions
//

static bool
char_in(char c, const char *chars)
{
    for (size_t i = 0; i < strlen(chars); i++) {
        if (chars[i] == c) {
            return true;
        }
    }
    return false;
}

static void
skip_chars(std::stringstream &in, const char *chars)
{
    char c = in.peek();
    while (char_in(c, chars) && c != EOF) {
        in.get();
        c = in.peek();
    }
}

// skip on the input stream to one of the characters in chars
// if another character is found this function returns false
// unles that character is specified in the optional may_skip
//
// the character found is left on the stream
static bool
skip_to(std::stringstream &in, const char *chars, const char *may_skip="")
{
    char c = in.get();
    while (c != EOF) {
        if (char_in(c, may_skip)) {
            c = in.get();
        } else if (char_in(c, chars)) {
            while(char_in(in.peek(), may_skip)) {
                in.get();
            }
            in.putback(c);
            return true;
        } else {
            // TODO: provide feeback mechanism?
            cout << "error, '" << c << "' read; one of \"" << chars << "\" expected" << endl;
            in.putback(c);
            return false;
        }
    }
    // TODO: provide feeback mechanism?
    cout << "error, EOF read; one of \"" << chars << "\" expected" << endl;
            in.putback(c);
    return false;
}

static std::string
str_from_stringstream(std::stringstream &in)
{
    char c = 0;
    std::stringstream ss;
    c = in.get();
    if (c == '"') {
        c = in.get();
    } else {
        return "badstring";
    }
    while (c != EOF && c != '"') {
        ss << c;
        if (c == '\\' && in.peek() == '"') {
            ss << in.get();
        }
        c = in.get();
    }
    return ss.str();
}

static std::string
word_from_stringstream(std::stringstream &in)
{
    std::stringstream ss;
    while (isalpha(in.peek())) {
        ss << (char) in.get();
    }
    return ss.str();
}


static ElementPtr
from_stringstream_int_or_double(std::stringstream &in)
{
    int i;
    in >> i;
    if (in.peek() == '.') {
        double d;
        in >> d;
        d += i;
        return Element::create(d);
    } else {
        return Element::create(i);
    }
}

static ElementPtr
from_stringstream_bool(std::stringstream &in)
{
    std::string word = word_from_stringstream(in);
    if (boost::iequals(word, "True")) {
        return Element::create(true);
    } else if (boost::iequals(word, "False")) {
        return Element::create(false);
    } else {
        return ElementPtr();
    }
}

static ElementPtr
from_stringstream_string(std::stringstream &in)
{
    return Element::create(str_from_stringstream(in));
}

static ElementPtr
from_stringstream_list(std::stringstream &in)
{
    char c = 0;
    std::vector<ElementPtr> v;
    ElementPtr cur_list_element;

    skip_chars(in, " \t\n");
    while (c != EOF && c != ']') {
        cur_list_element = Element::create_from_string(in);
        v.push_back(cur_list_element);
        if (!skip_to(in, ",]", " \t\n")) {
            return ElementPtr();
        }
        c = in.get();
    }
    return Element::create(v);
}

static ElementPtr
from_stringstream_map(std::stringstream &in)
{
    char c = 0;
    std::map<std::string, ElementPtr> m;
    std::pair<std::string, ElementPtr> p;
    std::string cur_map_key;
    ElementPtr cur_map_element;
    skip_chars(in, " \t\n");
    while (c != EOF && c != '}') {
        p.first = str_from_stringstream(in);
        if (!skip_to(in, ":", " \t\n")) {
            return ElementPtr();
        } else {
            // skip the :
            in.get();
        }
        p.second = Element::create_from_string(in);
        if (!p.second) { return ElementPtr(); };
        m.insert(p);
        skip_to(in, ",}", " \t\n");
        c = in.get();
    }
    return Element::create(m);
}

ElementPtr
Element::create_from_string(std::stringstream &in)
{
    char c = 0;
    ElementPtr element;
    bool el_read = false;
    skip_chars(in, " \n\t");
    while (c != EOF && !el_read) {
        c = in.get();
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
                element = from_stringstream_int_or_double(in);
                el_read = true;
                break;
            case 't':
            case 'T':
            case 'f':
            case 'F':
                in.putback(c);
                element = from_stringstream_bool(in);
                el_read = true;
                break;
            case '"':
                in.putback('"');
                element = from_stringstream_string(in);
                el_read = true;
                break;
            case '[':
                element = from_stringstream_list(in);
                el_read = true;
                break;
            case '{':
                element = from_stringstream_map(in);
                el_read = true;
                break;
            default:
                // TODO this might not be a fatal error
                // provide feedback mechanism?
                cout << "error: unexpected '" << c << "'" << endl;
                return ElementPtr();
                break;
        }
    }
    if (el_read) {
        return element;
    } else {
        // throw exception?
        return ElementPtr();
    }
}

//
// a general to_str() function
//
std::string
IntElement::str()
{
    std::stringstream ss;
    ss << int_value();
    return ss.str();
}

std::string
DoubleElement::str()
{
    std::stringstream ss;
    ss << double_value();
    return ss.str();
}

std::string
BoolElement::str()
{
    if (b) {
        return "True";
    } else {
        return "False";
    }
}

std::string
StringElement::str()
{
    std::stringstream ss;
    ss << "\"";
    ss << string_value();
    ss << "\"";
    return ss.str();
}

std::string
ListElement::str()
{
    std::stringstream ss;
    std::vector<ElementPtr> v;
    ss << "[ ";
    v = list_value();
    for (std::vector<ElementPtr>::iterator it = v.begin(); it != v.end(); ++it) {
        if (it != v.begin()) {
            ss << ", ";
        }
        ss << (*it)->str();
    }
    ss << " ]";
    return ss.str();
}

std::string
MapElement::str()
{
    std::stringstream ss;
    std::map<std::string, ElementPtr> m;
    ss << "{";
    m = map_value();
    for (std::map<std::string, ElementPtr>::iterator it = m.begin(); it != m.end(); ++it) {
        if (it != m.begin()) {
            ss << ", ";
        }
        ss << "\"" << (*it).first << "\": ";
        ss << (*it).second->str();
    }
    ss << "}";
    return ss.str();
}

//
// helpers for str_xml() functions
//

// prefix with 'prefix' number of spaces
static void
pre(std::ostream &out, size_t prefix)
{
    for (size_t i = 0; i < prefix; i++) {
        out << " ";
    }
}

std::string
IntElement::str_xml(size_t prefix)
{
    std::stringstream ss;
    pre(ss, prefix);
    ss << str();
    return ss.str();
}

std::string
DoubleElement::str_xml(size_t prefix)
{
    std::stringstream ss;
    pre(ss, prefix);
    ss << str();
    return ss.str();
}

std::string
BoolElement::str_xml(size_t prefix)
{
    std::stringstream ss;
    pre(ss, prefix);
    ss << str();
    return ss.str();
}

std::string
StringElement::str_xml(size_t prefix)
{
    std::stringstream ss;
    pre(ss, prefix);
    ss << string_value();
    return ss.str();
}

std::string
ListElement::str_xml(size_t prefix)
{
    std::stringstream ss;
    std::vector<ElementPtr> v;
    pre(ss, prefix);
    ss << "<list>" << endl;;
    v = list_value();
    for (std::vector<ElementPtr>::iterator it = v.begin(); it != v.end(); ++it) {
        pre(ss, prefix + 4);
        ss << "<listitem>" << endl;
        ss << (*it)->str_xml(prefix + 8) << endl;
        pre(ss, prefix + 4);
        ss << "</listitem>" << endl;
    }
    pre(ss, prefix);
    ss << "</list>";
    return ss.str();
}

std::string
MapElement::str_xml(size_t prefix)
{
    std::stringstream ss;
    std::map<std::string, ElementPtr> m;
    m = map_value();
    pre(ss, prefix);
    ss << "<map>" << endl;
    for (std::map<std::string, ElementPtr>::iterator it = m.begin(); it != m.end(); ++it) {
        pre(ss, prefix + 4);
        ss << "<mapitem name=\"" << (*it).first << "\">" << endl;
        pre(ss, prefix);
        ss << (*it).second->str_xml(prefix+8) << endl;
        pre(ss, prefix + 4);
        ss << "</mapitem>" << endl;
    }
    pre(ss, prefix);
    ss << "</map>";
    return ss.str();
}

// currently throws when one of the types in the path (except the one
// we're looking for) is not a MapElement
// returns 0 if it could simply not be found
// should that also be an exception?
ElementPtr
MapElement::find(const std::string& id)
{
    if (get_type() != map) {
        throw TypeError();
    }
    size_t sep = id.find('/');
    if (sep == std::string::npos) {
        return get(id);
    } else {
        ElementPtr ce = get(id.substr(0, sep));
        if (ce) {
            return ce->find(id.substr(sep+1));
        } else {
            return ElementPtr();
        }
    }
}

//
// Decode from wire format.
//

ElementPtr decode_element(std::stringstream& in, int& in_length);

static unsigned char
get_byte(std::stringstream& in)
{
    int c = in.get();
    if (c == EOF) {
        throw DecodeError("End of data while decoding wire format message");
    }

    return c;
}

std::string
decode_tag(std::stringstream& in, int& item_length)
{
    char buf[256];

    int len = get_byte(in);
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
decode_data(std::stringstream& in, int& item_length)
{
    char *buf = new char[item_length + 1];

    in.read(buf, item_length);
    if (in.fail()) {
        throw DecodeError();
    }
    buf[item_length] = 0;

    std::string s = std::string(buf, item_length);
    item_length -= item_length;

    delete [] buf;
    return Element::create(s);
}

ElementPtr
decode_hash(std::stringstream& in, int& item_length)
{
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
decode_list(std::stringstream& in, int& item_length)
{
    std::vector<ElementPtr> v;

    while (item_length > 0) {
        v.push_back(decode_element(in, item_length));
    }
    return Element::create(v);
}

ElementPtr
decode_null(std::stringstream& in, int& item_length)
{
    return Element::create("NULL");
}

ElementPtr
decode_element(std::stringstream& in, int& in_length)
{
    ElementPtr element;

    unsigned char type_and_length = get_byte(in);
    unsigned char type = type_and_length & ITEM_MASK;
    unsigned char lenbytes = type_and_length & ITEM_LENGTH_MASK;
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
    case ITEM_DATA:
        element = decode_data(in, item_length);
        break;
    case ITEM_HASH:
        element = decode_hash(in, item_length);
        break;
    case ITEM_LIST:
        element = decode_list(in, item_length);
        break;
    case ITEM_NULL:
        element = decode_null(in, item_length);
        break;
    }

    return (element);
}

ElementPtr
Element::from_wire(const std::string& s)
{
    std::stringstream ss;
    ss << s;
    return from_wire(ss, s.length());
}

ElementPtr
Element::from_wire(std::stringstream& in, int length)
{
    //
    // Check protocol version
    //
    for (int i = 0 ; i < 4 ; i++) {
        unsigned char version_byte = get_byte(in);
        if (PROTOCOL_VERSION[i] != version_byte) {
            throw DecodeError("Protocol version incorrect");
        }
    }
    length -= 4;

    ElementPtr element;
    element = decode_hash(in, length);
    return (element);
}

//
// Encode into wire format.
//

std::string
encode_length(unsigned int length, unsigned char type)
{
    std::stringstream ss;

    if (length <= 0x000000ff) {
        unsigned char val = (length & 0x000000ff);
        type |= ITEM_LENGTH_8;
        ss << type << val;
    } else if (length <= 0x0000ffff) {
        unsigned char val[2];
        val[0] = (length & 0x0000ff00) >> 8;
        val[1] = (length & 0x000000ff);
        type |= ITEM_LENGTH_16;
        ss << type << val;
    } else {
        unsigned char val[4];
        val[0] = (length & 0xff000000) >> 24;
        val[1] = (length & 0x00ff0000) >> 16;
        val[2] = (length & 0x0000ff00) >> 8;
        val[3] = (length & 0x000000ff);
        type |= ITEM_LENGTH_32;
        ss << type << val;
    }
    return ss.str();
}

std::string
StringElement::to_wire(int omit_length)
{
    std::stringstream ss;

    int length = string_value().length();
    ss << encode_length(length, ITEM_DATA) << string_value();

    return ss.str();
}

std::string
IntElement::to_wire(int omit_length)
{
    std::stringstream ss;
    std::stringstream text;

    text << str();
    int length = text.str().length();
    ss << encode_length(length, ITEM_DATA) << text.str();

    return ss.str();
}

std::string
BoolElement::to_wire(int omit_length)
{
    std::stringstream ss;
    std::stringstream text;

    text << str();
    int length = text.str().length();
    ss << encode_length(length, ITEM_DATA) << text.str();

    return ss.str();
}

std::string
DoubleElement::to_wire(int omit_length)
{
    std::stringstream ss;
    std::stringstream text;

    text << str();
    int length = text.str().length();
    ss << encode_length(length, ITEM_DATA) << text.str();

    return ss.str();
}

std::string
ListElement::to_wire(int omit_length)
{
    std::stringstream ss;
    std::vector<ElementPtr> v;
    v = list_value();
    for (std::vector<ElementPtr>::iterator it = v.begin() ;
         it != v.end() ; ++it) {
        ss << (*it)->to_wire(0);
    }

    if (omit_length) {
        return ss.str();
    } else {
        std::stringstream ss_len;
        ss_len << encode_length(ss.str().length(), ITEM_LIST);
        ss_len << ss.str();
        return ss_len.str();
    }
}

std::string
encode_tag(const std::string &s)
{
    std::stringstream ss;
    int length = s.length();
    unsigned char val = length & 0x000000ff;

    ss << val << s;

    return ss.str();
}

std::string
MapElement::to_wire(int omit_length)
{
    std::stringstream ss;
    std::map<std::string, ElementPtr> m;

    //
    // If we don't want the length, we will want the protocol header
    //
    if (omit_length) {
        ss << PROTOCOL_VERSION[0] << PROTOCOL_VERSION[1];
        ss << PROTOCOL_VERSION[2] << PROTOCOL_VERSION[3];
    }

    m = map_value();
    for (std::map<std::string, ElementPtr>::iterator it = m.begin() ;
         it != m.end() ; ++it) {
        ss << encode_tag((*it).first);
        ss << (*it).second->to_wire(0);
    }

    //
    // add length if needed
    //
    if (omit_length) {
        return ss.str();
    } else {
        std::stringstream ss_len;
        ss_len << encode_length(ss.str().length(), ITEM_HASH);
        ss_len << ss.str();
        return ss_len.str();
    }
}

bool
MapElement::find(const std::string& id, ElementPtr& t) {
    ElementPtr p;
    try {
        p = find(id);
        if (p) {
            t = p;
            return true;
        }
    } catch (TypeError e) {
        // ignore
    }
    return false;
}
