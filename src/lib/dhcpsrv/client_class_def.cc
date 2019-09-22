// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <eval/dependency.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/cfgmgr.h>
#include <boost/foreach.hpp>

using namespace isc::data;

namespace isc {
namespace dhcp {

//********** ClientClassDef ******************//

ClientClassDef::ClientClassDef(const std::string& name,
                               const ExpressionPtr& match_expr,
                               const CfgOptionPtr& cfg_option)
    : name_(name), match_expr_(match_expr), required_(false),
      depend_on_known_(false), cfg_option_(cfg_option),
      next_server_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()) {

    // Name can't be blank
    if (name_.empty()) {
        isc_throw(BadValue, "Client Class name cannot be blank");
    }

    // We permit an empty expression for now.  This will likely be useful
    // for automatic classes such as vendor class.

    // For classes without options, make sure we have an empty collection
    if (!cfg_option_) {
        cfg_option_.reset(new CfgOption());
    }
}

ClientClassDef::ClientClassDef(const ClientClassDef& rhs)
    : name_(rhs.name_), match_expr_(ExpressionPtr()), required_(false),
      depend_on_known_(false), cfg_option_(new CfgOption()),
      next_server_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()) {

    if (rhs.match_expr_) {
        match_expr_.reset(new Expression());
        *match_expr_ = *(rhs.match_expr_);
    }

    if (rhs.cfg_option_def_) {
        rhs.cfg_option_def_->copyTo(*cfg_option_def_);
    }

    if (rhs.cfg_option_) {
        rhs.cfg_option_->copyTo(*cfg_option_);
    }

    required_ = rhs.required_;
    depend_on_known_ = rhs.depend_on_known_;
    next_server_ = rhs.next_server_;
    sname_ = rhs.sname_;
    filename_ = rhs.filename_;
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

std::string
ClientClassDef::getTest() const {
    return (test_);
}

void
ClientClassDef::setTest(const std::string& test) {
    test_ = test;
}

bool
ClientClassDef::getRequired() const {
    return (required_);
}

void
ClientClassDef::setRequired(bool required) {
    required_ = required;
}

bool
ClientClassDef::getDependOnKnown() const {
    return (depend_on_known_);
}

void
ClientClassDef::setDependOnKnown(bool depend_on_known) {
    depend_on_known_ = depend_on_known;
}

const CfgOptionDefPtr&
ClientClassDef::getCfgOptionDef() const {
    return (cfg_option_def_);
}

void
ClientClassDef::setCfgOptionDef(const CfgOptionDefPtr& cfg_option_def) {
    cfg_option_def_ = cfg_option_def;
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
ClientClassDef::dependOnClass(const std::string& name) const {
    return (isc::dhcp::dependOnClass(match_expr_, name));
}

bool
ClientClassDef::equals(const ClientClassDef& other) const {
    return ((name_ == other.name_) &&
        ((!match_expr_ && !other.match_expr_) ||
        (match_expr_ && other.match_expr_ &&
         (*match_expr_ == *(other.match_expr_)))) &&
        ((!cfg_option_ && !other.cfg_option_) ||
        (cfg_option_ && other.cfg_option_ &&
         (*cfg_option_ == *other.cfg_option_))) &&
        ((!cfg_option_def_ && !other.cfg_option_def_) ||
        (cfg_option_def_ && other.cfg_option_def_ &&
         (*cfg_option_def_ == *other.cfg_option_def_))) &&
            (required_ == other.required_) &&
            (depend_on_known_ == other.depend_on_known_) &&
            (next_server_ == other.next_server_) &&
            (sname_ == other.sname_) &&
            (filename_ == other.filename_));
}

ElementPtr
ClientClassDef:: toElement() const {
    uint16_t family = CfgMgr::instance().getFamily();
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);
    // Set name
    result->set("name", Element::create(name_));
    // Set original match expression (empty string won't parse)
    if (!test_.empty()) {
        result->set("test", Element::create(test_));
    }
    // Set only-if-required
    if (required_) {
        result->set("only-if-required", Element::create(required_));
    }
    // Set option-def (used only by DHCPv4)
    if (cfg_option_def_ && (family == AF_INET)) {
        result->set("option-def", cfg_option_def_->toElement());
    }
    // Set option-data
    result->set("option-data", cfg_option_->toElement());
    if (family != AF_INET) {
        // Other parameters are DHCPv4 specific
        return (result);
    }
    // Set next-server
    result->set("next-server", Element::create(next_server_.toText()));
    // Set server-hostname
    result->set("server-hostname", Element::create(sname_));
    // Set boot-file-name
    result->set("boot-file-name", Element::create(filename_));
    return (result);
}

std::ostream& operator<<(std::ostream& os, const ClientClassDef& x) {
    os << "ClientClassDef:" << x.getName();
    return (os);
}

//********** ClientClassDictionary ******************//

ClientClassDictionary::ClientClassDictionary()
    : map_(new ClientClassDefMap()), list_(new ClientClassDefList()) {
}

ClientClassDictionary::ClientClassDictionary(const ClientClassDictionary& rhs)
    : map_(new ClientClassDefMap()), list_(new ClientClassDefList()) {
    BOOST_FOREACH(ClientClassDefPtr cclass, *(rhs.list_)) {
        ClientClassDefPtr copy(new ClientClassDef(*cclass));
        addClass(copy);
    }
}

ClientClassDictionary::~ClientClassDictionary() {
}

void
ClientClassDictionary::addClass(const std::string& name,
                                const ExpressionPtr& match_expr,
                                const std::string& test,
                                bool required,
                                bool depend_on_known,
                                const CfgOptionPtr& cfg_option,
                                CfgOptionDefPtr cfg_option_def,
                                ConstElementPtr user_context,
                                asiolink::IOAddress next_server,
                                const std::string& sname,
                                const std::string& filename) {
    ClientClassDefPtr cclass(new ClientClassDef(name, match_expr, cfg_option));
    cclass->setTest(test);
    cclass->setRequired(required);
    cclass->setDependOnKnown(depend_on_known);
    cclass->setCfgOptionDef(cfg_option_def);
    cclass->setContext(user_context),
    cclass->setNextServer(next_server);
    cclass->setSname(sname);
    cclass->setFilename(filename);
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

    list_->push_back(class_def);
    (*map_)[class_def->getName()] = class_def;
}

ClientClassDefPtr
ClientClassDictionary::findClass(const std::string& name) const {
    ClientClassDefMap::iterator it = map_->find(name);
    if (it != map_->end()) {
        return (*it).second;
    }

    return(ClientClassDefPtr());
}

void
ClientClassDictionary::removeClass(const std::string& name) {
    for (ClientClassDefList::iterator this_class = list_->begin();
         this_class != list_->end(); ++this_class) {
        if ((*this_class)->getName() == name) {
            list_->erase(this_class);
            break;
        }
    }
    map_->erase(name);
}

const ClientClassDefListPtr&
ClientClassDictionary::getClasses() const {
    return (list_);
}

bool
ClientClassDictionary::dependOnClass(const std::string& name,
                                     std::string& dependent_class) const {
    // Skip previous classes as they should not depend on name.
    bool found = false;
    for (ClientClassDefList::iterator this_class = list_->begin();
         this_class != list_->end(); ++this_class) {
        if (found) {
            if ((*this_class)->dependOnClass(name)) {
                dependent_class = (*this_class)->getName();
                return (true);
            }
        } else {
            if ((*this_class)->getName() == name) {
                found = true;
            }
        }
    }
    return (false);
}

bool
ClientClassDictionary::equals(const ClientClassDictionary& other) const {
    if (list_->size() != other.list_->size()) {
        return (false);
    }

    ClientClassDefList::const_iterator this_class = list_->cbegin();
    ClientClassDefList::const_iterator other_class = other.list_->cbegin();
    while (this_class != list_->cend() &&
           other_class != other.list_->cend()) {
        if (!*this_class || !*other_class ||
            **this_class != **other_class) {
                return false;
        }

        ++this_class;
        ++other_class;
    }

    return (true);
}

ElementPtr
ClientClassDictionary::toElement() const {
    ElementPtr result = Element::createList();
    // Iterate on the map
    for (ClientClassDefList::const_iterator this_class = list_->begin();
         this_class != list_->cend(); ++this_class) {
        result->add((*this_class)->toElement());
    }
    return (result);
}

std::list<std::string>
builtinNames = {
    // DROP is not in this list because it is special but not built-in.
    // In fact DROP is set from an expression as callouts can drop
    // directly the incoming packet. The expression must not depend on
    // KNOWN/UNKNOWN which are set far after the drop point.
    "ALL", "KNOWN", "UNKNOWN", "BOOTP"
};

std::list<std::string>
builtinPrefixes = {
    "VENDOR_CLASS_", "HA_", "AFTER_", "EXTERNAL_"
};

bool
isClientClassBuiltIn(const ClientClass& client_class) {
    for (std::list<std::string>::const_iterator bn = builtinNames.cbegin();
         bn != builtinNames.cend(); ++bn) {
        if (client_class == *bn) {
            return true;
        }
    }

    for (std::list<std::string>::const_iterator bt = builtinPrefixes.cbegin();
         bt != builtinPrefixes.cend(); ++bt) {
        if (client_class.size() <= bt->size()) {
            continue;
        }
        auto mis = std::mismatch(bt->cbegin(), bt->cend(), client_class.cbegin());
        if (mis.first == bt->cend()) {
            return true;
        }
    }

    return false;
}

bool
isClientClassDefined(ClientClassDictionaryPtr& class_dictionary,
                     bool& depend_on_known,
                     const ClientClass& client_class) {
    // First check built-in classes
    if (isClientClassBuiltIn(client_class)) {
        // Check direct dependency on [UN]KNOWN
        if ((client_class == "KNOWN") || (client_class == "UNKNOWN")) {
            depend_on_known = true;
        }
        return (true);
    }

    // Second check already defined, i.e. in the dictionary
    ClientClassDefPtr def = class_dictionary->findClass(client_class);
    if (def) {
        // Check indirect dependency on [UN]KNOWN
        if (def->getDependOnKnown()) {
            depend_on_known = true;
        }
        return (true);
    }

    // Not defined...
    return (false);
}

} // namespace isc::dhcp
} // namespace isc
