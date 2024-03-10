// Copyright (C) 2010-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <exceptions/isc_assert.h>
#include <dns/rrparamregistry.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <cassert>
#include <algorithm>
#include <cctype>
#include <functional>
#include <map>
#include <stdint.h>
#include <string>
#include <sstream>
#include <utility>
#include <boost/shared_ptr.hpp>

using namespace isc::util;
using namespace isc::dns::rdata;

using namespace std;

namespace isc {
namespace dns {

namespace {
///
/// The following function and class are a helper to define case-insensitive
/// equivalence relationship on strings.  They are used in the mapping
/// containers below.
///
bool
CICharLess(char c1, char c2) {
    return (tolower(static_cast<unsigned char>(c1)) <
            tolower(static_cast<unsigned char>(c2)));
}

struct CIStringLess {
    bool operator()(const string& s1, const string& s2) const {
        return (lexicographical_compare(s1.begin(), s1.end(),
                                        s2.begin(), s2.end(), CICharLess));
    }
};

struct RRTypeParam {
    RRTypeParam(const string& code_string, uint16_t code) :
        code_string_(code_string), code_(code) {}
    string code_string_;
    uint16_t code_;

    /// magic constants
    static const unsigned int MAX_CODE = 0xffff;
    static const string& UNKNOWN_PREFIX();
    static size_t UNKNOWN_PREFIXLEN();
    static const string& UNKNOWN_MAX();
    static size_t UNKNOWN_MAXLEN();
};

typedef boost::shared_ptr<RRTypeParam> RRTypeParamPtr;
typedef map<string, RRTypeParamPtr, CIStringLess> StrRRTypeMap;
typedef map<uint16_t, RRTypeParamPtr> CodeRRTypeMap;

inline const string&
RRTypeParam::UNKNOWN_PREFIX() {
    static const string p("TYPE");
    return (p);
}

inline size_t
RRTypeParam::UNKNOWN_PREFIXLEN() {
    static size_t plen = UNKNOWN_PREFIX().size();
    return (plen);
}

inline const string&
RRTypeParam::UNKNOWN_MAX() {
    static const string p("TYPE65535");
    return (p);
}

inline size_t
RRTypeParam::UNKNOWN_MAXLEN() {
    static size_t plen = UNKNOWN_MAX().size();
    return (plen);
}

struct RRClassParam {
    RRClassParam(const string& code_string, uint16_t code) :
        code_string_(code_string), code_(code) {}
    string code_string_;
    uint16_t code_;

    /// magic constants
    static const unsigned int MAX_CODE = 0xffff;
    static const string& UNKNOWN_PREFIX();
    static size_t UNKNOWN_PREFIXLEN();
    static const string& UNKNOWN_MAX();
    static size_t UNKNOWN_MAXLEN();
};

typedef boost::shared_ptr<RRClassParam> RRClassParamPtr;
typedef map<string, RRClassParamPtr, CIStringLess> StrRRClassMap;
typedef map<uint16_t, RRClassParamPtr> CodeRRClassMap;

inline const string&
RRClassParam::UNKNOWN_PREFIX() {
    static const string p("CLASS");
    return (p);
}

inline size_t
RRClassParam::UNKNOWN_PREFIXLEN() {
    static size_t plen = UNKNOWN_PREFIX().size();
    return (plen);
}

inline const string&
RRClassParam::UNKNOWN_MAX() {
    static const string p("CLASS65535");
    return (p);
}

inline size_t
RRClassParam::UNKNOWN_MAXLEN() {
    static size_t plen = UNKNOWN_MAX().size();
    return (plen);
}
} // end of anonymous namespace

/// Note: the element ordering in the type/class pair is intentional.
/// The standard library will perform inequality comparison (i.e, '<')
/// in the way that the second elements (RRClass) are compared only when
/// the first elements are equivalent.
/// In practice, when we compare two pairs of RRType and RRClass, RRClass
/// would be the same (and, in particular, be class IN) in the majority of
/// cases.  So this comparison ordering should be more efficient in common
/// cases.
typedef pair<RRType, RRClass> RRTypeClass;
typedef map<RRTypeClass, RdataFactoryPtr> RdataFactoryMap;
typedef map<RRType, RdataFactoryPtr> GenericRdataFactoryMap;

template <typename T>
class RdataFactory : public AbstractRdataFactory {
public:
    virtual RdataPtr create(const string& rdata_str) const {
        return (RdataPtr(new T(rdata_str)));
    }

    virtual RdataPtr create(InputBuffer& buffer, size_t rdata_len) const {
        return (RdataPtr(new T(buffer, rdata_len)));
    }

    virtual RdataPtr create(const Rdata& source) const {
        return (RdataPtr(new T(dynamic_cast<const T&>(source))));
    }

    virtual RdataPtr create(MasterLexer& lexer, const Name* origin,
                            MasterLoader::Options options,
                            MasterLoaderCallbacks& callbacks) const {
        return (RdataPtr(new T(lexer, origin, options, callbacks)));
    }
};

///
/// \brief The \c RRParamRegistryImpl class is the actual implementation of
/// \c RRParamRegistry.
///
/// The implementation is hidden from applications.  We can refer to specific
/// members of this class only within the implementation source file.
///
struct RRParamRegistryImpl {
    /// Mappings from RR type codes to textual representations.
    StrRRTypeMap str2typemap;
    /// Mappings from textual representations of RR types to integer codes.
    CodeRRTypeMap code2typemap;
    /// Mappings from RR class codes to textual representations.
    StrRRClassMap str2classmap;
    /// Mappings from textual representations of RR classes to integer codes.
    CodeRRClassMap code2classmap;
    RdataFactoryMap rdata_factories;
    GenericRdataFactoryMap genericrdata_factories;
};

RRParamRegistry::RRParamRegistry() : impl_(new RRParamRegistryImpl()) {

    // set up parameters for well-known RRs
    try {
        // ANY class well known RR types.
        add("TSIG", 250, "ANY", 255, RdataFactoryPtr(new RdataFactory<any::TSIG>()));
        // CH class well known RR types.
        add("A", 1, "CH", 3, RdataFactoryPtr(new RdataFactory<ch::A>()));
        // IN class well known RR types.
        add("A", 1, "IN", 1, RdataFactoryPtr(new RdataFactory<in::A>()));
;
        add("NS", 2, "IN", 1, RdataFactoryPtr(new RdataFactory<generic::NS>()));
        add("SOA", 6, "IN", 1, RdataFactoryPtr(new RdataFactory<generic::SOA>()));
        add("PTR", 12, "IN", 1, RdataFactoryPtr(new RdataFactory<generic::PTR>()));
        add("TXT", 16, "IN", 1, RdataFactoryPtr(new RdataFactory<generic::TXT>()));
        add("AAAA", 28, "IN", 1, RdataFactoryPtr(new RdataFactory<in::AAAA>()));
        add("OPT", 41, "IN", 1, RdataFactoryPtr(new RdataFactory<generic::OPT>()));
        add("RRSIG", 46, "IN", 1, RdataFactoryPtr(new RdataFactory<generic::RRSIG>()));
        add("DHCID", 49, "IN", 1, RdataFactoryPtr(new RdataFactory<in::DHCID>()));
        add("TKEY", 249, "IN", 1, RdataFactoryPtr(new RdataFactory<generic::TKEY>()));
        // Generic well known RR types.
        add("NS", 2, RdataFactoryPtr(new RdataFactory<generic::NS>()));
        add("SOA", 6, RdataFactoryPtr(new RdataFactory<generic::SOA>()));
        add("PTR", 12, RdataFactoryPtr(new RdataFactory<generic::PTR>()));
        add("TXT", 16, RdataFactoryPtr(new RdataFactory<generic::TXT>()));
        add("OPT", 41, RdataFactoryPtr(new RdataFactory<generic::OPT>()));
        add("RRSIG", 46, RdataFactoryPtr(new RdataFactory<generic::RRSIG>()));
        add("TKEY", 249, RdataFactoryPtr(new RdataFactory<generic::TKEY>()));
        // Meta and Not supported RR classes.
        addClass("HS", 4);
        addClass("NONE", 254);
        // Meta and non-implemented RR types
        addType("MD", 3);
        addType("MF", 4);
        addType("CNAME", 5);
        addType("MB", 7);
        addType("MG", 8);
        addType("MR", 9);
        addType("NULL", 10);
        addType("WKS", 11);
        addType("HINFO", 13);
        addType("MINFO", 14);
        addType("MX", 15);
        addType("RP", 17);
        addType("AFSDB", 18);
        addType("X25", 19);
        addType("ISDN", 20);
        addType("RT", 21);
        addType("NSAP", 22);
        addType("NSAP-PTR", 23);
        addType("SIG", 24);
        addType("KEY", 25);
        addType("PX", 26);
        addType("GPOS", 27);
        addType("LOC", 29);
        addType("NXT", 30);
        addType("EID", 31);
        addType("NIMLOC", 32);
        addType("SRV", 33);
        addType("ATMA", 34);
        addType("NAPTR", 35);
        addType("KX", 36);
        addType("CERT", 37);
        addType("A6", 38);
        addType("DNAME", 39);
        addType("SINK", 40);
        addType("APL", 42);
        addType("DS", 43);
        addType("SSHFP", 44);
        addType("IPSECKEY", 45);
        addType("NSEC", 47);
        addType("DNSKEY", 48);
        addType("NSEC3", 50);
        addType("NSEC3PARAM", 51);
        addType("TLSA", 52);
        addType("SMIMEA", 53);
        // Unassigned  54
        addType("HIP", 55);
        addType("NINFO", 56);
        addType("RKEY", 57);
        addType("TALINK", 58);
        addType("CDS", 59);
        addType("CDNSKEY", 60);
        addType("OPENPGPKEY", 61);
        addType("CSYNC", 62);
        addType("ZONEMD", 63);
        addType("SVCB", 64);
        addType("HTTPS", 65);
        // Unassigned  66-98
        addType("SPF", 99);
        addType("UINFO", 100);
        addType("UID", 101);
        addType("GID", 102);
        addType("UNSPEC", 103);
        addType("NID", 104);
        addType("L32", 105);
        addType("L64", 106);
        addType("LP", 107);
        addType("EUI48", 108);
        addType("EUI64", 109);
        // Unassigned  110-248
        addType("IXFR", 251);
        addType("AXFR",  252);
        addType("MAILB", 253);
        addType("MAILA", 254);
        addType("ANY", 255); // also known as "*"
        addType("URI", 256);
        addType("CAA", 257);
        addType("AVC", 258);
        addType("DOA", 259);
        addType("AMTRELAY", 260);
        addType("RESINFO", 261);
        // Unassigned  262-32767
        addType("TA", 32768);
        addType("DLV", 32769);
    } catch (...) {
        throw;
    }
}

RRParamRegistry::~RRParamRegistry() {
}

RRParamRegistry&
RRParamRegistry::getRegistry() {
    static RRParamRegistry registry;

    return (registry);
}

void
RRParamRegistry::add(const std::string& typecode_string, uint16_t typecode,
                     RdataFactoryPtr rdata_factory) {
    bool type_added = false;
    try {
        type_added = addType(typecode_string, typecode);
        impl_->genericrdata_factories.insert(pair<RRType, RdataFactoryPtr>(
                                                 RRType(typecode),
                                                 rdata_factory));
    } catch (...) {
        if (type_added) {
            removeType(typecode);
        }
        throw;
    }
}

void
RRParamRegistry::add(const std::string& typecode_string, uint16_t typecode,
                     const std::string& classcode_string, uint16_t classcode,
                     RdataFactoryPtr rdata_factory) {
    // Rollback logic on failure is complicated.  If adding the new type or
    // class fails, we should revert to the original state, cleaning up
    // intermediate state.  But we need to make sure that we don't remove
    // existing data.  addType()/addClass() will simply ignore an attempt to
    // add the same data, so the cleanup should be performed only when we add
    // something new but we fail in other part of the process.
    bool type_added = false;
    bool class_added = false;

    try {
        type_added = addType(typecode_string, typecode);
        class_added = addClass(classcode_string, classcode);
        impl_->rdata_factories.insert(pair<RRTypeClass, RdataFactoryPtr>(
                                          RRTypeClass(RRType(typecode),
                                                      RRClass(classcode)),
                                          rdata_factory));
    } catch (...) {
        if (type_added) {
            removeType(typecode);
        }
        if (class_added) {
            removeClass(classcode);
        }
        throw;
    }
}

bool
RRParamRegistry::removeRdataFactory(const RRType& rrtype,
                                    const RRClass& rrclass) {
    RdataFactoryMap::iterator found =
        impl_->rdata_factories.find(RRTypeClass(rrtype, rrclass));
    if (found != impl_->rdata_factories.end()) {
        impl_->rdata_factories.erase(found);
        return (true);
    }

    return (false);
}

bool
RRParamRegistry::removeRdataFactory(const RRType& rrtype) {
    GenericRdataFactoryMap::iterator found =
        impl_->genericrdata_factories.find(rrtype);
    if (found != impl_->genericrdata_factories.end()) {
        impl_->genericrdata_factories.erase(found);
        return (true);
    }

    return (false);
}

namespace {
///
/// These are helper functions to implement case-insensitive string comparison.
/// This could be simplified using strncasecmp(), but unfortunately it's not
/// included in <cstring>.  To be as much as portable within the C++ standard
/// we take the "in house" approach here.
///
bool CICharEqual(char c1, char c2) {
    return (tolower(static_cast<unsigned char>(c1)) ==
            tolower(static_cast<unsigned char>(c2)));
}

bool
caseStringEqual(const string& s1, const string& s2, size_t n) {
    isc_throw_assert(s1.size() >= n && s2.size() >= n);

    return (mismatch(s1.begin(), s1.begin() + n, s2.begin(), CICharEqual).first
            == s1.begin() + n);
}

/// Code logic for RRTypes and RRClasses is mostly common except (C++) type and
/// member names.  So we define type-independent templates to describe the
/// common logic and let concrete classes use it to avoid code duplicates.
/// The following summarize template parameters used in the set of template
/// functions:
/// PT: parameter type, either RRTypeParam or RRClassParam
/// MC: type of mapping class from code: either CodeRRTypeMap or CodeRRClassMap
/// MS: type of mapping class from string: either StrRRTypeMap or StrRRClassMap
/// ET: exception type for error handling: either InvalidRRType or
///     InvalidRRClass
template <typename PT, typename MC, typename MS, typename ET>
inline bool
addParam(const string& code_string, uint16_t code, MC& codemap, MS& stringmap) {
    // Duplicate type check
    typename MC::const_iterator found = codemap.find(code);
    if (found != codemap.end()) {
        if (found->second->code_string_ != code_string) {
            isc_throw(ET, "Duplicate RR parameter registration");
        }
        return (false);
    }

    typedef boost::shared_ptr<PT> ParamPtr;
    typedef pair<string, ParamPtr> StrParamPair;
    typedef pair<uint16_t, ParamPtr> CodeParamPair;
    ParamPtr param = ParamPtr(new PT(code_string, code));
    try {
        stringmap.insert(StrParamPair(code_string, param));
        codemap.insert(CodeParamPair(code, param));
    } catch (...) {
        // Rollback to the previous state: not all of the erase operations will
        // find the entry, but we don't care.
        stringmap.erase(code_string);
        codemap.erase(code);
        throw;
    }

    return (true);
}

template <typename MC, typename MS>
inline bool
removeParam(uint16_t code, MC& codemap, MS& stringmap) {
    typename MC::iterator found = codemap.find(code);

    if (found != codemap.end()) {
        size_t erased = stringmap.erase(found->second->code_string_);
        // We must have a corresponding entry of the str2 map exists
        isc_throw_assert(erased == 1);

        codemap.erase(found);

        return (true);
    }

    return (false);
}

template <typename PT, typename MS>
inline bool
textToCode(const string& code_str, MS& stringmap, uint16_t& ret_code) {
    typename MS::const_iterator found;

    found = stringmap.find(code_str);
    if (found != stringmap.end()) {
        ret_code = found->second->code_;
        return (true);
    }

    size_t l = code_str.size();
    if (l > PT::UNKNOWN_PREFIXLEN() &&
        l <= PT::UNKNOWN_MAXLEN() &&
        caseStringEqual(code_str, PT::UNKNOWN_PREFIX(),
                        PT::UNKNOWN_PREFIXLEN())) {
        unsigned int code;
        istringstream iss(code_str.substr(PT::UNKNOWN_PREFIXLEN(),
                                          l - PT::UNKNOWN_PREFIXLEN()));
        iss >> dec >> code;
        if (iss.rdstate() == ios::eofbit && code <= PT::MAX_CODE) {
            ret_code = code;
            return (true);
        }
    }

    return (false);
}

template <typename PT, typename MC>
inline string
codeToText(uint16_t code, MC& codemap) {
    typename MC::const_iterator found;

    found = codemap.find(code);
    if (found != codemap.end()) {
        return (found->second->code_string_);
    }

    ostringstream ss;
    ss << code;
    return (PT::UNKNOWN_PREFIX() + ss.str());
}
}

bool
RRParamRegistry::addType(const string& type_string, uint16_t code) {
    return (addParam<RRTypeParam, CodeRRTypeMap, StrRRTypeMap, RRTypeExists>
            (type_string, code, impl_->code2typemap, impl_->str2typemap));
}

bool
RRParamRegistry::removeType(uint16_t code) {
    return (removeParam<CodeRRTypeMap, StrRRTypeMap>(code, impl_->code2typemap,
                                                     impl_->str2typemap));
}

bool
RRParamRegistry::textToTypeCode(const string& type_string,
                                uint16_t& type_code) const {
    return (textToCode<RRTypeParam, StrRRTypeMap>
            (type_string, impl_->str2typemap, type_code));
}

string
RRParamRegistry::codeToTypeText(uint16_t code) const {
    return (codeToText<RRTypeParam, CodeRRTypeMap>(code, impl_->code2typemap));
}

bool
RRParamRegistry::addClass(const string& class_string, uint16_t code) {
    return (addParam<RRClassParam, CodeRRClassMap, StrRRClassMap, RRClassExists>
            (class_string, code, impl_->code2classmap, impl_->str2classmap));
}

bool
RRParamRegistry::removeClass(uint16_t code) {
    return (removeParam<CodeRRClassMap, StrRRClassMap>(code,
                                                       impl_->code2classmap,
                                                       impl_->str2classmap));
}

bool
RRParamRegistry::textToClassCode(const string& class_string,
                                 uint16_t& class_code) const {
    return (textToCode<RRClassParam, StrRRClassMap>
            (class_string, impl_->str2classmap, class_code));
}

string
RRParamRegistry::codeToClassText(uint16_t code) const {
    return (codeToText<RRClassParam, CodeRRClassMap>(code,
                                                     impl_->code2classmap));
}

namespace {
inline const AbstractRdataFactory*
findRdataFactory(RRParamRegistryImpl* reg_impl,
                 const RRType& rrtype, const RRClass& rrclass) {
    RdataFactoryMap::const_iterator found;
    found = reg_impl->rdata_factories.find(RRTypeClass(rrtype, rrclass));
    if (found != reg_impl->rdata_factories.end()) {
        return (found->second.get());
    }

    GenericRdataFactoryMap::const_iterator genfound =
        reg_impl->genericrdata_factories.find(rrtype);
    if (genfound != reg_impl->genericrdata_factories.end()) {
        return (genfound->second.get());
    }

    return (0);
}
}

RdataPtr
RRParamRegistry::createRdata(const RRType& rrtype, const RRClass& rrclass,
                             const std::string& rdata_string) {
    // If the text indicates that it's rdata of an "unknown" type (beginning
    // with '\# n'), parse it that way. (TBD)

    const AbstractRdataFactory* factory =
        findRdataFactory(impl_.get(), rrtype, rrclass);
    if (factory) {
        return (factory->create(rdata_string));
    }

    return (RdataPtr(new generic::Generic(rdata_string)));
}

RdataPtr
RRParamRegistry::createRdata(const RRType& rrtype, const RRClass& rrclass,
                             InputBuffer& buffer, size_t rdata_len) {
    const AbstractRdataFactory* factory =
        findRdataFactory(impl_.get(), rrtype, rrclass);
    if (factory) {
        return (factory->create(buffer, rdata_len));
    }

    return (RdataPtr(new generic::Generic(buffer, rdata_len)));
}

RdataPtr
RRParamRegistry::createRdata(const RRType& rrtype, const RRClass& rrclass,
                             const Rdata& source) {
    const AbstractRdataFactory* factory =
        findRdataFactory(impl_.get(), rrtype, rrclass);
    if (factory) {
        return (factory->create(source));
    }

    return (RdataPtr(new rdata::generic::Generic(
                         dynamic_cast<const generic::Generic&>(source))));
}

RdataPtr
RRParamRegistry::createRdata(const RRType& rrtype, const RRClass& rrclass,
                             MasterLexer& lexer, const Name* name,
                             MasterLoader::Options options,
                             MasterLoaderCallbacks& callbacks) {
    const AbstractRdataFactory* factory =
        findRdataFactory(impl_.get(), rrtype, rrclass);
    if (factory) {
        return (factory->create(lexer, name, options, callbacks));
    }

    return (RdataPtr(new generic::Generic(lexer, name, options, callbacks)));
}
}
}
