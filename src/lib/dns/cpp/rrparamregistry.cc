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

#include <algorithm>
#include <cctype>
#include <functional>
#include <map>
#include <string>
#include <sstream>
#include <utility>

#include <stdint.h>

#include <boost/shared_ptr.hpp>

#include "exceptions.h"
#include "rrparamregistry.h"
#include "rrclass.h"
#include "rrtype.h"

using namespace std;
using namespace boost;

namespace isc {
namespace dns {

namespace {
bool CICharEqual(char c1, char c2)
{
    return (tolower(static_cast<unsigned char>(c1)) ==
            tolower(static_cast<unsigned char>(c2)));
}

bool
caseStringEqual(const string& s1, const string& s2, size_t n)
{
    if (s1.size() < n || s2.size() < n) {
        return (false);
    }

    return (mismatch(s1.begin(), s1.begin() + n, s2.begin(), CICharEqual).first
            == s1.begin() + n);
}

bool
CICharLess(char c1, char c2)
{
    return (tolower(static_cast<unsigned char>(c1)) <
            tolower(static_cast<unsigned char>(c2)));
}

struct CIStringLess :
        public binary_function<string, string, bool>
{
    bool operator()(const string& s1, const string& s2) const
    {
        return (lexicographical_compare(s1.begin(), s1.end(),
                                        s2.begin(), s2.end(), CICharLess));
    }
};

struct RRTypeParam {
    RRTypeParam(const string& type_string, uint16_t type_code) :
        type_string_(type_string), type_code_(type_code) {}
    string type_string_;
    uint16_t type_code_;

    /// magic constants
    static const unsigned int MAX_CODE = 0xffff;
    static const string UNKNOWN_PREFIX;
    static const size_t UNKNOWN_PREFIXLEN;
    static const string UNKNOWN_MAX;
    static const size_t UNKNOWN_MAXLEN;
};

typedef shared_ptr<RRTypeParam> RRTypeParamPtr;
typedef pair<string, RRTypeParamPtr> StrRRTypePair;
typedef pair<uint16_t, RRTypeParamPtr> CodeRRTypePair;
typedef map<string, RRTypeParamPtr, CIStringLess> StrRRTypeMap;
typedef map<uint16_t, RRTypeParamPtr> CodeRRTypeMap;

const string RRTypeParam::UNKNOWN_PREFIX = "TYPE";
const size_t RRTypeParam::UNKNOWN_PREFIXLEN =
    RRTypeParam::UNKNOWN_PREFIX.size();
const string RRTypeParam::UNKNOWN_MAX = "TYPE65535";
const size_t RRTypeParam::UNKNOWN_MAXLEN =
    RRTypeParam::UNKNOWN_MAX.size();

struct RRClassParam {
    RRClassParam(const string& class_string, uint16_t class_code) :
        class_string_(class_string), class_code_(class_code) {}
    string class_string_;
    uint16_t class_code_;

    /// magic constants
    static const unsigned int MAX_CODE = 0xffff;
    static const string UNKNOWN_PREFIX;
    static const size_t UNKNOWN_PREFIXLEN;
    static const string UNKNOWN_MAX;
    static const size_t UNKNOWN_MAXLEN;
};

typedef shared_ptr<RRClassParam> RRClassParamPtr;
typedef pair<string, RRClassParamPtr> StrRRClassPair;
typedef pair<uint16_t, RRClassParamPtr> CodeRRClassPair;
typedef map<string, RRClassParamPtr, CIStringLess> StrRRClassMap;
typedef map<uint16_t, RRClassParamPtr> CodeRRClassMap;

const string RRClassParam::UNKNOWN_PREFIX = "CLASS";
const size_t RRClassParam::UNKNOWN_PREFIXLEN =
    RRClassParam::UNKNOWN_PREFIX.size();
const string RRClassParam::UNKNOWN_MAX = "CLASS65535";
const size_t RRClassParam::UNKNOWN_MAXLEN =
    RRClassParam::UNKNOWN_MAX.size();
}

struct RRParamRegistryImpl {
    StrRRClassMap str2classmap;
    CodeRRClassMap code2classmap;
    StrRRTypeMap str2typemap;
    CodeRRTypeMap code2typemap;
};

RRParamRegistry::RRParamRegistry()
{
    impl_ = new RRParamRegistryImpl;

    // set up parameters for well-known RRs
    // XXX: this should eventually be more automatic.
    try {
        add("IN", 1, "A", 1);
        add("IN", 1, "NS", 2);

        add("CH", 3, "A", 1);
    } catch (...) {
        delete impl_;
        throw;
    }
    //...
}

RRParamRegistry::~RRParamRegistry()
{
    delete impl_;
}

const RRParamRegistry&
RRParamRegistry::getRegistry()
{
    static RRParamRegistry registry;

    return (registry);
}

void
RRParamRegistry::add(const string& class_string, uint16_t class_code,
                     const string& type_string, uint16_t type_code
                     /* rdata_factory (notyet) */)
{
    // XXX: rollback logic on failure is complicated.
    bool add_type = false;
    bool add_class = false;

    if (impl_->code2typemap.find(type_code) == impl_->code2typemap.end()) {
        add_type = true;
    }
    if (impl_->code2classmap.find(class_code) == impl_->code2classmap.end()) {
        add_class = true;
    }

    try {
        addType(type_string, type_code);
        addClass(class_string, class_code);
    } catch (...) {
        if (add_type) {
            removeType(type_code);
        }
        if (add_class) {
            removeClass(class_code);
        }
        throw;
    }
}

void
RRParamRegistry::addClass(const string& class_string, uint16_t class_code)
{
    // Duplicate type check
    CodeRRClassMap::const_iterator found =
        impl_->code2classmap.find(class_code);
    if (found != impl_->code2classmap.end()) {
        if (found->second->class_string_ != class_string) {
            dns_throw(RRClassExist, "Duplicate RR class registration");
        }
        return;
    }

    RRClassParamPtr class_param = RRClassParamPtr(new RRClassParam(class_string,
                                                               class_code));
    try {
        impl_->str2classmap.insert(StrRRClassPair(class_string, class_param));
        impl_->code2classmap.insert(CodeRRClassPair(class_code, class_param));
    } catch (...) {
        // Rollback to the previous state: not all of the erase operations will
        // find the entry, but we don't care.
        impl_->str2classmap.erase(class_string);
        impl_->code2classmap.erase(class_code);
        throw;
    }
}

bool
RRParamRegistry::removeClass(uint16_t class_code)
{
    CodeRRClassMap::iterator found = impl_->code2classmap.find(class_code);
    if (found != impl_->code2classmap.end()) {
        size_t erased = impl_->str2classmap.erase(found->second->class_string_);
        // We must have a corresponding entry of the str2 map exists
        assert(erased == 1);

        impl_->code2classmap.erase(found);

        return (true);
    }

    return (false);
}

uint16_t
RRParamRegistry::getClassCode(const string& class_str) const
{
    StrRRClassMap::const_iterator found;

    found = impl_->str2classmap.find(class_str);
    if (found != impl_->str2classmap.end()) {
        return (found->second->class_code_);
    }

    size_t l = class_str.size();
    if (l > RRClassParam::UNKNOWN_PREFIXLEN &&
        l <= RRClassParam::UNKNOWN_MAXLEN &&
        caseStringEqual(class_str, RRClassParam::UNKNOWN_PREFIX,
                        RRClassParam::UNKNOWN_PREFIXLEN)) {
        unsigned int code;
        istringstream iss(class_str.substr(RRClassParam::UNKNOWN_PREFIXLEN,
                                           l -
                                           RRClassParam::UNKNOWN_PREFIXLEN));
        iss >> dec >> code;
        if (iss.rdstate() == ios::eofbit && code <= RRClassParam::MAX_CODE) {
            return (code);
        }
    }
    dns_throw(InvalidRRClass, "Unrecognized RR Class string");
}

string
RRParamRegistry::getClassText(uint16_t class_code) const
{
    CodeRRClassMap::const_iterator found;

    found = impl_->code2classmap.find(class_code);
    if (found != impl_->code2classmap.end()) {
        return (found->second->class_string_);
    }

    ostringstream ss;
    ss << class_code;
    return (RRClassParam::UNKNOWN_PREFIX + ss.str());
}

///
/// The code logic is same as addClass(), but we only have these two variations
/// we live with duplicate rather than trying to unify them.
///
void
RRParamRegistry::addType(const string& type_string, uint16_t type_code)
{
    CodeRRTypeMap::const_iterator found = impl_->code2typemap.find(type_code);
    if (found != impl_->code2typemap.end()) {
        if (found->second->type_string_ != type_string) {
            dns_throw(RRTypeExist, "Duplicate RR type registration");
        }
        return;
    }

    RRTypeParamPtr type_param = RRTypeParamPtr(new RRTypeParam(type_string,
                                                               type_code));
    try {
        impl_->str2typemap.insert(StrRRTypePair(type_string, type_param));
        impl_->code2typemap.insert(CodeRRTypePair(type_code, type_param));
    } catch (...) {
        impl_->str2typemap.erase(type_string);
        impl_->code2typemap.erase(type_code);
        throw;
    }
}

bool
RRParamRegistry::removeType(uint16_t type_code)
{
    CodeRRTypeMap::iterator found = impl_->code2typemap.find(type_code);
    if (found != impl_->code2typemap.end()) {
        size_t erased = impl_->str2typemap.erase(found->second->type_string_);
        // We must have a corresponding entry of the str2 map exists
        assert(erased == 1);

        impl_->code2typemap.erase(found);

        return (true);
    }

    return (false);
}

uint16_t
RRParamRegistry::getTypeCode(const string& type_str) const
{
    StrRRTypeMap::const_iterator found;

    found = impl_->str2typemap.find(type_str);
    if (found != impl_->str2typemap.end()) {
        return (found->second->type_code_);
    }

    size_t l = type_str.size();
    if (l > RRTypeParam::UNKNOWN_PREFIXLEN &&
        l <= RRTypeParam::UNKNOWN_MAXLEN &&
        caseStringEqual(type_str, RRTypeParam::UNKNOWN_PREFIX,
                        RRTypeParam::UNKNOWN_PREFIXLEN)) {
        unsigned int code;
        istringstream iss(type_str.substr(RRTypeParam::UNKNOWN_PREFIXLEN,
                                          l - RRTypeParam::UNKNOWN_PREFIXLEN));
        iss >> dec >> code;
        if (iss.rdstate() == ios::eofbit && code <= RRTypeParam::MAX_CODE) {
            return (code);
        }
    }
    dns_throw(InvalidRRType, "Unrecognized RR Type string");
}

string
RRParamRegistry::getTypeText(uint16_t type_code) const
{
    CodeRRTypeMap::const_iterator found;

    found = impl_->code2typemap.find(type_code);
    if (found != impl_->code2typemap.end()) {
        return (found->second->type_string_);
    }

    ostringstream ss;
    ss << type_code;
    return (RRTypeParam::UNKNOWN_PREFIX + ss.str());
}
}
}
