// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include "client_class_def.h"

namespace isc {
namespace dhcp {

//********** ClientClassDef ******************//

ClientClassDef::ClientClassDef(const std::string& name,
                         const ExpressionPtr& match_expr,
                         const OptionCollectionPtr& options)
    : name_(name), match_expr_(match_expr), options_(options) {
    // Name can't be blank
    if (name_.empty()) {
        isc_throw(BadValue, "ClientClassDef name cannot be empty");
    }
    // @todo Does it make sense for a class to NOT have match expression?

    // For classes without options, make sure we have an empty collection
    if (!options_) {
        options_.reset(new OptionCollection());
    }
}

ClientClassDef::~ClientClassDef() {
}

std::string
ClientClassDef::getName() const {
    return (name_);
}

void
ClientClassDef::setName(const std::string& name) {
  name_ = name;
}

const ExpressionPtr&
ClientClassDef::getMatchExpr() const {
    return (match_expr_);
}

void
ClientClassDef::setMatchExpr(const ExpressionPtr& match_expr) {
  match_expr_ = match_expr;
}

const OptionCollectionPtr&
ClientClassDef::getOptions() const {
    return (options_);
}

void
ClientClassDef::setOptions(const OptionCollectionPtr& options) {
    options_ = options;
}

OptionPtr
ClientClassDef::findOption(uint16_t option_code) const {
    if (options_) {
        isc::dhcp::OptionCollection::iterator it = options_->find(option_code);
        if (it != options_->end()) {
            return ((*it).second);
        }
    }

    return (OptionPtr());
}

std::ostream& operator<<(std::ostream& os, const ClientClassDef& x) {
    os << "ClientClassDef:" << x.getName();
    return (os);
}

//********** ClientClassDictionary ******************//

ClientClassDictionary::ClientClassDictionary()
    : classes_(new ClientClassDefMap()) {
}

ClientClassDictionary::~ClientClassDictionary() {
}

void
ClientClassDictionary::addClass(const std::string& name,
                          const ExpressionPtr& match_expr,
                          const OptionCollectionPtr& options) {
    ClientClassDefPtr cclass(new ClientClassDef(name, match_expr, options));
    addClass(cclass);
}

void
ClientClassDictionary::addClass(ClientClassDefPtr& class_def) {
    if (!class_def) {
        isc_throw(BadValue, "ClientClassDictionary::addClass "
                            " - class definition cannot be null");
    }

    if (findClass(class_def->getName())) {
        isc_throw(DuplicateClientClassDef, "Client Class: "
                  << class_def->getName() << " has already been defined");
    }

   (*classes_)[class_def->getName()] = class_def;
}

ClientClassDefPtr
ClientClassDictionary::findClass(const std::string& name) const {
    ClientClassDefMap::iterator it = classes_->find(name);
    if (it != classes_->end()) {
        return (*it).second;
    }

    return(ClientClassDefPtr());
}

void
ClientClassDictionary::removeClass(const std::string& name) {
    classes_->erase(name);
}

const ClientClassDefMapPtr&
ClientClassDictionary::getClasses() const {
    return (classes_);
}

} // namespace isc::dhcp
} // namespace isc
