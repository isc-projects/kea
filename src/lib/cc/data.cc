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

#include <config.h>

#include <cc/data.h>

#include <cassert>
#include <climits>
#include <map>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp> // for iequals

#include <cmath>

using namespace std;

namespace isc {
namespace data {

std::string
Element::str() const {
    std::stringstream ss;
    toJSON(ss);
    return (ss.str());
}

std::string
Element::toWire() const {
    std::stringstream ss;
    toJSON(ss);
    return (ss.str());
}

void
Element::toWire(std::ostream& ss) const {
    toJSON(ss);
}

//
// The following methods are effectively empty, and their parameters are
// unused.  To silence compilers that warn unused function parameters,
// we specify a (compiler dependent) special keyword when available.
// It's defined in config.h, and to avoid including this header file from
// installed files we define the methods here.
//
bool
Element::getValue(long int& t UNUSED_PARAM) {
    return (false);
}

bool
Element::getValue(double& t UNUSED_PARAM) {
    return (false);
}

bool
Element::getValue(bool& t UNUSED_PARAM) {
    return (false);
}

bool
Element::getValue(std::string& t UNUSED_PARAM) {
    return (false);
}

bool
Element::getValue(std::vector<ConstElementPtr>& t UNUSED_PARAM) {
    return (false);
}

bool
Element::getValue(std::map<std::string, ConstElementPtr>& t UNUSED_PARAM) {
    return (false);
}

bool
Element::setValue(const long int v UNUSED_PARAM) {
    return (false);
}

bool
Element::setValue(const double v UNUSED_PARAM) {
    return (false);
}

bool
Element::setValue(const bool t UNUSED_PARAM) {
    return (false);
}

bool
Element::setValue(const std::string& v UNUSED_PARAM) {
    return (false);
}

bool
Element::setValue(const std::vector<ConstElementPtr>& v UNUSED_PARAM) {
    return (false);
}

bool
Element::setValue(const std::map<std::string,
                  ConstElementPtr>& v UNUSED_PARAM)
{
    return (false);
}

ConstElementPtr
Element::get(const int i UNUSED_PARAM) const {
    isc_throw(TypeError, "get(int) called on a non-list Element");
}

void
Element::set(const size_t i UNUSED_PARAM, ConstElementPtr element UNUSED_PARAM) {
    isc_throw(TypeError, "set(int, element) called on a non-list Element");
}

void
Element::add(ConstElementPtr element UNUSED_PARAM) {
    isc_throw(TypeError, "add() called on a non-list Element");
}

void
Element::remove(const int i UNUSED_PARAM) {
    isc_throw(TypeError, "remove(int) called on a non-list Element");
}

size_t
Element::size() const {
    isc_throw(TypeError, "size() called on a non-list Element");
}

ConstElementPtr
Element::get(const std::string& name UNUSED_PARAM) const {
    isc_throw(TypeError, "get(string) called on a non-map Element");
}

void
Element::set(const std::string& name UNUSED_PARAM,
             ConstElementPtr element UNUSED_PARAM)
{
    isc_throw(TypeError, "set(name, element) called on a non-map Element");
}

void
Element::remove(const std::string& name UNUSED_PARAM) {
    isc_throw(TypeError, "remove(string) called on a non-map Element");
}

bool
Element::contains(const std::string& name UNUSED_PARAM) const {
    isc_throw(TypeError, "contains(string) called on a non-map Element");
}

ConstElementPtr
Element::find(const std::string& identifier UNUSED_PARAM) const {
    isc_throw(TypeError, "find(string) called on a non-map Element");
}

bool
Element::find(const std::string& identifier UNUSED_PARAM,
              ConstElementPtr t UNUSED_PARAM) const
{
    return (false);
}

namespace {
inline void
throwJSONError(const std::string& error, const std::string& file, int line, int pos)
{
    std::stringstream ss;
    ss << error << " in " + file + ":" << line << ":" << pos;
    isc_throw(JSONError, ss.str());
}
}

std::ostream&
operator<<(std::ostream &out, const Element& e) {
    return (out << e.str());
}

bool
operator==(const Element& a, const Element& b) {
    return (a.equals(b));
}

bool operator!=(const Element& a, const Element& b) {
    return (!a.equals(b));
};

//
// factory functions
//
ElementPtr
Element::create() {
    return (ElementPtr(new NullElement()));
}

ElementPtr
Element::create(const long int i) {
    return (ElementPtr(new IntElement(i)));
}

ElementPtr
Element::create(const double d) {
    return (ElementPtr(new DoubleElement(d)));
}

ElementPtr
Element::create(const std::string& s) {
    return (ElementPtr(new StringElement(s)));
}

ElementPtr
Element::create(const bool b) {
    return (ElementPtr(new BoolElement(b)));
}

ElementPtr
Element::createList() {
    return (ElementPtr(new ListElement()));
}

ElementPtr
Element::createMap() {
    return (ElementPtr(new MapElement()));
}


//
// helper functions for fromJSON factory
//
namespace {
bool
char_in(const char c, const char *chars) {
    for (size_t i = 0; i < strlen(chars); ++i) {
        if (chars[i] == c) {
            return (true);
        }
    }
    return (false);
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
            throwJSONError(std::string("'") + c + "' read, one of \"" + chars + "\" expected", file, line, pos);
        }
    }
    throwJSONError(std::string("EOF read, one of \"") + chars + "\" expected", file, line, pos);
}

// TODO: Should we check for all other official escapes here (and
// error on the rest)?
std::string
str_from_stringstream(std::istream &in, const std::string& file, const int line,
                      int& pos) throw (JSONError)
{
    char c = 0;
    std::stringstream ss;
    c = in.get();
    ++pos;
    if (c == '"') {
        c = in.get();
        ++pos;
    } else {
        throwJSONError("String expected", file, line, pos);
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
    return (ss.str());
}

std::string
word_from_stringstream(std::istream &in, int& pos) {
    std::stringstream ss;
    while (isalpha(in.peek())) {
        ss << (char) in.get();
    }
    pos += ss.str().size();
    return (ss.str());
}

static std::string
number_from_stringstream(std::istream &in, int& pos) {
    std::stringstream ss;
    while (isdigit(in.peek()) || in.peek() == '+' || in.peek() == '-' ||
           in.peek() == '.' || in.peek() == 'e' || in.peek() == 'E') {
        ss << (char) in.get();
    }
    pos += ss.str().size();
    return (ss.str());
}

// Should we change from IntElement and DoubleElement to NumberElement
// that can also hold an e value? (and have specific getters if the
// value is larger than an int can handle)
ElementPtr
from_stringstream_number(std::istream &in, int &pos) {
    long int i = 0;
    double d = 0.0;
    bool is_double = false;
    char *endptr;

    std::string number = number_from_stringstream(in, pos);

    i = strtol(number.c_str(), &endptr, 10);
    if (*endptr != '\0') {
        d = strtod(number.c_str(), &endptr);
        is_double = true;
        if (*endptr != '\0') {
            isc_throw(JSONError, std::string("Bad number: ") + number);
        } else {
            if (d == HUGE_VAL || d == -HUGE_VAL) {
                isc_throw(JSONError, std::string("Number overflow: ") + number);
            }
        }
    } else {
        if (i == LONG_MAX || i == LONG_MIN) {
            isc_throw(JSONError, std::string("Number overflow: ") + number);
        }
    }
    
    if (is_double) {
        return (Element::create(d));
    } else {
        return (Element::create(i));
    }
}

ElementPtr
from_stringstream_bool(std::istream &in, const std::string& file,
                       const int line, int& pos)
{
    const std::string word = word_from_stringstream(in, pos);
    if (boost::iequals(word, "True")) {
        return (Element::create(true));
    } else if (boost::iequals(word, "False")) {
        return (Element::create(false));
    } else {
        throwJSONError(std::string("Bad boolean value: ") + word, file, line, pos);
        // above is a throw shortcurt, return empty is never reached
        return (ElementPtr());
    }
}

ElementPtr
from_stringstream_null(std::istream &in, const std::string& file,
                       const int line, int& pos)
{
    const std::string word = word_from_stringstream(in, pos);
    if (boost::iequals(word, "null")) {
        return (Element::create());
    } else {
        throwJSONError(std::string("Bad null value: ") + word, file, line, pos);
        return (ElementPtr());
    }
}

ElementPtr
from_stringstream_string(std::istream& in, const std::string& file, int& line, int& pos)
{
    return (Element::create(str_from_stringstream(in, file, line, pos)));
}

ElementPtr
from_stringstream_list(std::istream &in, const std::string& file, int& line, int& pos)
{
    char c = 0;
    ElementPtr list = Element::createList();
    ConstElementPtr cur_list_element;

    skip_chars(in, " \t\n", line, pos);
    while (c != EOF && c != ']') {
        if (in.peek() != ']') {
            cur_list_element = Element::fromJSON(in, file, line, pos);
            list->add(cur_list_element);
            skip_to(in, file, line, pos, ",]", " \t\n");
        }
        c = in.get();
        pos++;
    }
    return (list);
}

ElementPtr
from_stringstream_map(std::istream &in, const std::string& file, int& line,
                      int& pos)
{
    ElementPtr map = Element::createMap();
    skip_chars(in, " \t\n", line, pos);
    char c = in.peek();
    if (c == '}') {
        // empty map, skip closing curly
        c = in.get();
    } else {
        while (c != EOF && c != '}') {
            std::string key = str_from_stringstream(in, file, line, pos);

            skip_to(in, file, line, pos, ":", " \t\n");
            // skip the :
            in.get();
            pos++;

            ConstElementPtr value = Element::fromJSON(in, file, line, pos);
            map->set(key, value);
            
            skip_to(in, file, line, pos, ",}", " \t\n");
            c = in.get();
            pos++;
        }
    }
    return (map);
}
}

std::string
Element::typeToName(Element::types type)
{
    switch (type) {
    case Element::integer:
        return (std::string("integer"));
    case Element::real:
        return (std::string("real"));
    case Element::boolean:
        return (std::string("boolean"));
    case Element::string:
        return (std::string("string"));
    case Element::list:
        return (std::string("list"));
    case Element::map:
        return (std::string("map"));
    case Element::null:
        return (std::string("null"));
    case Element::any:
        return (std::string("any"));
    default:
        return (std::string("unknown"));
    }
}

Element::types
Element::nameToType(const std::string& type_name) {
    if (type_name == "integer") {
        return (Element::integer);
    } else if (type_name == "real") {
        return (Element::real);
    } else if (type_name == "boolean") {
        return (Element::boolean);
    } else if (type_name == "string") {
        return (Element::string);
    } else if (type_name == "list") {
        return (Element::list);
    } else if (type_name == "map") {
        return (Element::map);
    } else if (type_name == "null") {
        return (Element::null);
    } else if (type_name == "any") {
        return (Element::any);
    } else {
        isc_throw(TypeError, type_name + " is not a valid type name");
    }
}

ElementPtr
Element::fromJSON(std::istream& in) throw(JSONError) {
    int line = 1, pos = 1;
    return (fromJSON(in, "<istream>", line, pos));
}

ElementPtr
Element::fromJSON(std::istream& in, const std::string& file_name) throw(JSONError)
{
    int line = 1, pos = 1;
    return (fromJSON(in, file_name, line, pos));
}

ElementPtr
Element::fromJSON(std::istream &in, const std::string& file, int& line, int& pos) throw(JSONError)
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
            case '-':
            case '+':
            case '.':
                in.putback(c);
                element = from_stringstream_number(in, pos);
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
            case 'n':
            case 'N':
                in.putback(c);
                element = from_stringstream_null(in, file, line, pos);
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
                throwJSONError(std::string("error: unexpected character ") + c, file, line, pos);
                break;
        }
    }
    if (el_read) {
        return (element);
    } else {
        isc_throw(JSONError, "nothing read");
    }
}

ElementPtr
Element::fromJSON(const std::string &in) {
    std::stringstream ss;
    ss << in;
    return (fromJSON(ss, "<string>"));
}

// to JSON format

void
IntElement::toJSON(std::ostream& ss) const {
    ss << intValue();
}

void
DoubleElement::toJSON(std::ostream& ss) const {
    ss << doubleValue();
}

void
BoolElement::toJSON(std::ostream& ss) const {
    if (boolValue()) {
        ss << "true";
    } else {
        ss << "false";
    }
}

void
NullElement::toJSON(std::ostream& ss) const {
    ss << "null";
}

void
StringElement::toJSON(std::ostream& ss) const {
    ss << "\"";
    ss << stringValue();
    ss << "\"";
}

void
ListElement::toJSON(std::ostream& ss) const {
    ss << "[ ";

    const std::vector<ConstElementPtr>& v = listValue();
    for (std::vector<ConstElementPtr>::const_iterator it = v.begin();
         it != v.end(); ++it) {
        if (it != v.begin()) {
            ss << ", ";
        }
        (*it)->toJSON(ss);
    }
    ss << " ]";
}

void
MapElement::toJSON(std::ostream& ss) const {
    ss << "{ ";

    const std::map<std::string, ConstElementPtr>& m = mapValue();
    for (std::map<std::string, ConstElementPtr>::const_iterator it = m.begin();
         it != m.end(); ++it) {
        if (it != m.begin()) {
            ss << ", ";
        }
        ss << "\"" << (*it).first << "\": ";
        if ((*it).second) {
            (*it).second->toJSON(ss);
        } else {
            ss << "None";
        }
    }
    ss << " }";
}

// throws when one of the types in the path (except the one
// we're looking for) is not a MapElement
// returns 0 if it could simply not be found
// should that also be an exception?
ConstElementPtr
MapElement::find(const std::string& id) const {
    const size_t sep = id.find('/');
    if (sep == std::string::npos) {
        return (get(id));
    } else {
        ConstElementPtr ce = get(id.substr(0, sep));
        if (ce) {
            // ignore trailing slash
            if  (sep + 1 != id.size()) {
                return (ce->find(id.substr(sep + 1)));
            } else {
                return (ce);
            }
        } else {
            return (ElementPtr());
        }
    }
}

ElementPtr
Element::fromWire(const std::string& s) {
    std::stringstream ss;
    ss << s;
    int line = 0, pos = 0;
    return (fromJSON(ss, "<wire>", line, pos));
}

ElementPtr
Element::fromWire(std::stringstream& in, int length) {
    //
    // Check protocol version
    //
    //for (int i = 0 ; i < 4 ; ++i) {
    //    const unsigned char version_byte = get_byte(in);
    //    if (PROTOCOL_VERSION[i] != version_byte) {
    //        throw DecodeError("Protocol version incorrect");
    //    }
    //}
    //length -= 4;
    int line = 0, pos = 0;
    return (fromJSON(in, "<wire>", line, pos));
}

void
MapElement::set(const std::string& key, ConstElementPtr value) {
    m[key] = value;
}

bool
MapElement::find(const std::string& id, ConstElementPtr t) const {
    try {
        ConstElementPtr p = find(id);
        if (p) {
            t = p;
            return (true);
        }
    } catch (const TypeError& e) {
        // ignore
    }
    return (false);
}

bool
IntElement::equals(const Element& other) const {
    return (other.getType() == Element::integer) &&
           (i == other.intValue());
}

bool
DoubleElement::equals(const Element& other) const {
    return (other.getType() == Element::real) &&
           (d == other.doubleValue());
}

bool
BoolElement::equals(const Element& other) const {
    return (other.getType() == Element::boolean) &&
           (b == other.boolValue());
}

bool
NullElement::equals(const Element& other) const {
    return (other.getType() == Element::null);
}

bool
StringElement::equals(const Element& other) const {
    return (other.getType() == Element::string) &&
           (s == other.stringValue());
}

bool
ListElement::equals(const Element& other) const {
    if (other.getType() == Element::list) {
        const int s = size();
        if (s != other.size()) {
            return (false);
        }
        for (int i = 0; i < s; ++i) {
            if (!get(i)->equals(*other.get(i))) {
                return (false);
            }
        }
        return (true);
    } else {
        return (false);
    }
}

bool
MapElement::equals(const Element& other) const {
    if (other.getType() == Element::map) {
        const std::map<std::string, ConstElementPtr>& m = mapValue();
        for (std::map<std::string, ConstElementPtr>::const_iterator it =
                 m.begin();
             it != m.end() ; ++it) {
            if (other.contains((*it).first)) {
                if (!get((*it).first)->equals(*other.get((*it).first))) {
                    return (false);
                }
            } else {
                return (false);
            }
        }
        // quickly walk through the other map too, to see if there's
        // anything in there that we don't have. We don't need to
        // compare those elements; if one of them is missing we
        // differ (and if it's not missing the loop above has checked
        // it)
        std::map<std::string, ConstElementPtr>::const_iterator it;
        for (it = other.mapValue().begin();
             it != other.mapValue().end();
             ++it) {
            if (!contains((*it).first)) {
                return (false);
            }
        }
        return (true);
    } else {
        return (false);
    }
}

bool
isNull(ConstElementPtr p) {
    return (!p);
}

void
removeIdentical(ElementPtr a, ConstElementPtr b) {
    if (!b) {
        return;
    }
    if (a->getType() != Element::map || b->getType() != Element::map) {
        isc_throw(TypeError, "Non-map Elements passed to removeIdentical");
    }

    const std::map<std::string, ConstElementPtr>& m = a->mapValue();
    for (std::map<std::string, ConstElementPtr>::const_iterator it = m.begin();
         it != m.end() ; ++it) {
        if (b->contains((*it).first)) {
            if (a->get((*it).first)->equals(*b->get((*it).first))) {
                a->remove((*it).first);
            }
        }
    }
}

ConstElementPtr
removeIdentical(ConstElementPtr a, ConstElementPtr b) {
    ElementPtr result = Element::createMap();

    if (!b) {
        return (result);
    }
    
    if (a->getType() != Element::map || b->getType() != Element::map) {
        isc_throw(TypeError, "Non-map Elements passed to removeIdentical");
    }

    const std::map<std::string, ConstElementPtr>& m = a->mapValue();
    for (std::map<std::string, ConstElementPtr>::const_iterator it = m.begin();
         it != m.end() ; ++it) {
        if (!b->contains((*it).first) ||
            !a->get((*it).first)->equals(*b->get((*it).first))) {
            result->set((*it).first, (*it).second);
        }
    }

    return (result);
}

void
merge(ElementPtr element, ConstElementPtr other) {
    if (element->getType() != Element::map ||
        other->getType() != Element::map) {
        isc_throw(TypeError, "merge arguments not MapElements");
    }
    
    std::map<std::string, ConstElementPtr> m = other->mapValue();
    for (std::map<std::string, ConstElementPtr>::const_iterator it = m.begin();
         it != m.end() ; ++it) {
        if ((*it).second && (*it).second->getType() != Element::null) {
            element->set((*it).first, (*it).second);
        } else if (element->contains((*it).first)) {
            element->remove((*it).first);
        }
    }
}

}
}
