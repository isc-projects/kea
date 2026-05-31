// Copyright (C) 2014-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcp/classify.h>
#include <util/str.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>

#include <sstream>
#include <vector>

namespace isc {
namespace dhcp {

using namespace isc::data;

ClientClasses::ClientClasses(const std::string& class_names)
    : container_() {
    std::vector<std::string> split_text;
    boost::split(split_text, class_names, boost::is_any_of(","),
                 boost::algorithm::token_compress_off);
    for (size_t i = 0; i < split_text.size(); ++i) {
        std::string trimmed = util::str::trim(split_text[i]);
        // Ignore empty class names.
        if (!trimmed.empty()) {
            insert(ClientClass(trimmed));
        }
    }
}

ClientClasses::ClientClasses(const ClientClasses& other) {
    for (auto const& cclass : other) {
        insert(cclass);
    }
}

void
ClientClasses::erase(const ClientClass& class_name) {
    auto& idx = container_.get<ClassNameTag>();
    auto it = idx.find(class_name);
    if (it != idx.end()) {
        static_cast<void>(idx.erase(it));
    }
}

bool
ClientClasses::contains(const ClientClass& x) const {
    auto const& idx = container_.get<ClassNameTag>();
    return (idx.count(x) != 0);
}

bool
ClientClasses::intersects(const ClientClasses& cclasses) const {
    if (cclasses.size() > size()) {
        for (const auto& cclass : *this) {
            if (cclasses.contains(cclass)) {
                return (true);
            }
        }
    } else {
        for (const auto& cclass : cclasses) {
            if (contains(cclass)) {
                return (true);
            }
        }
    }

    return (false);
}

std::string
ClientClasses::toText(const std::string& separator) const {
    std::stringstream s;
    bool first = true;
    for (auto const& class_it : *this) {
        if (!first) {
            s << separator;
        } else {
            first = false;
        }
        s << class_it;
    }
    return (s.str());
}

ElementPtr
ClientClasses::toElement() const {
    ElementPtr result(Element::createList());
    for (auto const& c : container_) {
        result->add(Element::create(c));
    }
    return (result);
}

void
ClientClasses::fromElement(isc::data::ConstElementPtr cc_list) {
    if (cc_list) {
        clear();
        if (cc_list->getType() != Element::list) {
            isc_throw(BadValue, "not a List element");
        }

        for (unsigned i = 0; i < cc_list->size(); ++i) {
            auto cclass = cc_list->get(i);
            if (cclass->getType() != Element::string) {
                isc_throw(BadValue, "elements of list must be valid strings");
            }

            static_cast<void>(insert(cclass->stringValue()));
        }
    }
}

bool
ClientClasses::equals(const ClientClasses& other) const {
    return ((size() == other.size()) && std::equal(cbegin(), cend(), other.cbegin()));
}

ClientClasses&
ClientClasses::operator=(const ClientClasses& other) {
    clear();
    for (auto const& cclass : other) {
        insert(cclass);
    }

    return (*this);
}

size_t
ClientClasses::Hash::operator()(const ClientClasses &client_classes) {
    return (hash_value(client_classes));
}

size_t hash_value(const ClientClasses& client_classes) {
    boost::hash<std::string> hasher;
    return (hasher(client_classes.toText("+")));
}

/****************
// Code creating the CLIENT_CLASS_VALID_CHARACTERS value.
#include <iostream>
#include <string>
#include <vector>

std::string valid_s =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&*+-./:?@^_|~";
std::vector<bool> valid_v(128, false);

void gen() {
    for (int i = 0; i < 128; ++i) {
        valid_v[i] = (valid_s.find_first_of(i) != std::string::npos);
    }
}

int main() {
    gen();
    std::cout << std::boolalpha;
    for (size_t i = 0; i < valid_v.size(); ++i) {
        if ((i % 8) == 0) {
            std::cout << "   ";
        }
        std::cout << " " << valid_v[i] << ",";
        if ((i % 8) == 7) {
            std::cout << std::endl;
        }
    }

    return 0;
}
****************/

const std::vector<bool> ClientClasses::CLIENT_CLASS_VALID_CHARACTERS = {
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
    false, true, false, true, true, true, true, false,
    false, false, true, true, false, true, true, true,
    true, true, true, true, true, true, true, true,
    true, true, true, false, false, false, false, true,
    true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true,
    true, true, true, false, false, false, true, true,
    false, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true,
    true, true, true, false, true, false, true, false,
};

std::string
ClientClasses::escape(const std::string& name) {
    std::stringstream ss;
    for (char const& c : name) {
        unsigned u = static_cast<unsigned>(c);
        if ((u < 128) && CLIENT_CLASS_VALID_CHARACTERS[u]) {
            ss << c;
            if (c == '%') {
                ss << c;
            }
        } else {
            ss << '%' << std::hex << std::setfill('0') << std::setw(2) << u;
        }
    }
    return (ss.str());
}

} // end of namespace dhcp
} // end of namespace isc
