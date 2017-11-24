// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    : name_(name), match_expr_(match_expr), cfg_option_(cfg_option),
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
    : name_(rhs.name_), match_expr_(ExpressionPtr()),
      cfg_option_(new CfgOption()),
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
            (next_server_ == other.next_server_) &&
            (sname_ == other.sname_) &&
            (filename_ == other.filename_));
}

ElementPtr
ClientClassDef:: toElement() const {
    uint16_t family = CfgMgr::instance().getFamily();
    ElementPtr result = Element::createMap();
    // Set name
    result->set("name", Element::create(name_));
    // Set original match expression (empty string won't parse)
    if (!test_.empty()) {
        result->set("test", Element::create(test_));
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
                                const CfgOptionPtr& cfg_option,
                                CfgOptionDefPtr cfg_option_def,
                                asiolink::IOAddress next_server,
                                const std::string& sname,
                                const std::string& filename) {
    ClientClassDefPtr cclass(new ClientClassDef(name, match_expr, cfg_option));
    cclass->setTest(test);
    cclass->setCfgOptionDef(cfg_option_def);
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
    for (ClientClassDefList::const_iterator this_class = list_->cbegin();
         this_class != list_->cend(); ++this_class) {
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

} // namespace isc::dhcp
} // namespace isc
