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

#ifndef __RRPARAMREGISTRY_H
#define __RRPARAMREGISTRY_H 1

#include <string>

#include <stdint.h>

#include "exceptions.h"

namespace isc {
namespace dns {

struct RRParamRegistryImpl;

///
/// \brief A standard DNS module exception that is thrown if a new RR class is
/// being registered with a different type string.
///
class RRClassExist : public Exception {
public:
    RRClassExist(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a new RR type is
/// being registered with a different type string.
///
class RRTypeExist : public Exception {
public:
    RRTypeExist(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

class RRParamRegistry {
private:
    RRParamRegistry();
    ~RRParamRegistry();
public:
    void add(const std::string& class_string, uint16_t class_code,
             const std::string& type_string, uint16_t type_code);

    void addClass(const std::string& class_string, uint16_t class_code);
    bool removeClass(uint16_t class_code);

    /// Note:
    /// Duplicate type check: if the given type is already registered with the
    /// same type string, simply ignore the new attempt.
    void addType(const std::string& type_string, uint16_t type_code);
    bool removeType(uint16_t type_code);

    /// Convert type string to the corresponding 16-bit integer code.
    uint16_t getClassCode(const std::string& class_str) const;
    /// Convert type code into its textual representation.
    std::string getClassText(uint16_t class_code) const;

    /// Convert type string to the corresponding 16-bit integer code.
    uint16_t getTypeCode(const std::string& type_str) const;
    /// Convert type code into its textual representation.
    std::string getTypeText(uint16_t type_code) const;

    static const RRParamRegistry& getRegistry();
private:
    RRParamRegistryImpl* impl_;
};

}
}
#endif  // __RRPARAMREGISTRY_H

// Local Variables: 
// mode: c++
// End: 
