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
#include <boost/foreach.hpp>

namespace isc {
namespace dhcp {

//********** ClientClassDef ******************//

ClientClassDef::ClientClassDef(const std::string& name,
                               const ExpressionPtr& match_expr,
                               const CfgOptionPtr& cfg_option)
    : name_(name), match_expr_(match_expr), cfg_option_(cfg_option) {

    // Name can't be blank
    if (name_.empty()) {
        isc_throw(BadValue, "ClientClassDef name cannot be empty");
    }

    // We permit an empty expression for now.  This will likely be useful
    // for automatic classes such as vendor class.

    // For classes without options, make sure we have an empty collection
    if (!cfg_option_) {
        cfg_option_.reset(new CfgOption());
    }
}

ClientClassDef::ClientClassDef(const ClientClassDef& rhs)
    : name_(rhs.name_), match_expr_(ExpressionPtr()),
      cfg_option_(new CfgOption()) {

    if (rhs.match_expr_) {
        match_expr_.reset(new Expression());
        *match_expr_ = *(rhs.match_expr_);
    }

    if (rhs.cfg_option_) {
        rhs.cfg_option_->copyTo(*cfg_option_);
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

const CfgOptionPtr&
ClientClassDef::getCfgOption() const {
    return (cfg_option_);
}

void
ClientClassDef::setCfgOption(const CfgOptionPtr& cfg_option) {
    cfg_option_ = cfg_option;
}

bool
ClientClassDef::equals(const ClientClassDef& other) const {
    return ((name_ == other.name_) &&
        ((!match_expr_ && !other.match_expr_) ||
        (match_expr_ && other.match_expr_ &&
         (*match_expr_ == *(other.match_expr_)))) &&
        ((!cfg_option_ && !other.cfg_option_) ||
        (cfg_option_ && other.cfg_option_ &&
         (*cfg_option_ == *other.cfg_option_))));
}

std::ostream& operator<<(std::ostream& os, const ClientClassDef& x) {
    os << "ClientClassDef:" << x.getName();
    return (os);
}

//********** ClientClassDictionary ******************//

ClientClassDictionary::ClientClassDictionary()
    : classes_(new ClientClassDefMap()) {
}

ClientClassDictionary::ClientClassDictionary(const ClientClassDictionary& rhs)
    : classes_(new ClientClassDefMap()) {
    BOOST_FOREACH(ClientClassMapPair cclass, *(rhs.classes_)) {
        ClientClassDefPtr copy(new ClientClassDef(*(cclass.second)));
        addClass(copy);
    }
}

ClientClassDictionary::~ClientClassDictionary() {
}

void
ClientClassDictionary::addClass(const std::string& name,
                                const ExpressionPtr& match_expr,
                                const CfgOptionPtr& cfg_option) {
    ClientClassDefPtr cclass(new ClientClassDef(name, match_expr, cfg_option));
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

bool
ClientClassDictionary::equals(const ClientClassDictionary& other) const {
    if (classes_->size() != other.classes_->size()) {
        return (false);
    }

    ClientClassDefMap::iterator this_class = classes_->begin();
    ClientClassDefMap::iterator other_class = other.classes_->begin();
    while (this_class != classes_->end() &&
           other_class != other.classes_->end()) {
        if (!(*this_class).second || !(*other_class).second ||
            (*(*this_class).second) != (*(*other_class).second)) {
                return false;
        }

        ++this_class;
        ++other_class;
    }

    return (true);
}


} // namespace isc::dhcp
} // namespace isc
