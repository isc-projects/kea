// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/simple_parser.h>
#include <asiolink/io_address.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <cc/data.h>
#include <string>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using isc::dhcp::DhcpConfigError;

namespace isc {
namespace data {

void
SimpleParser::checkRequired(const SimpleRequiredKeywords& required,
                            ConstElementPtr scope) {
    for (auto name : required) {
        if (scope->contains(name)) {
            continue;
        }
        isc_throw(DhcpConfigError, "missing '" << name << "' parameter");
    }
}

void
SimpleParser::checkKeywords(const SimpleKeywords& keywords,
                            ConstElementPtr scope) {
    string spurious;
    for (auto entry : scope->mapValue()) {
        if (keywords.count(entry.first) == 0) {
            if (spurious.empty()) {
                spurious = entry.first;
            }
            continue;
        }
        Element::types expected = keywords.at(entry.first);
        if ((expected == Element::any) ||
            (entry.second->getType() == expected)) {
            continue;
        }
        isc_throw(DhcpConfigError, "'" << entry.first << "' parameter is not "
                  << (expected == Element::integer ? "an " : "a ")
                  << Element::typeToName(expected));
    }
    if (!spurious.empty()) {
        isc_throw(DhcpConfigError, "spurious '" << spurious << "' parameter");
    }
}

std::string
SimpleParser::getString(ConstElementPtr scope, const std::string& name) {
    ConstElementPtr x = scope->get(name);
    if (!x) {
        isc_throw(DhcpConfigError,
                  "missing parameter '" << name << "' ("
                  << scope->getPosition() << ")");
    }
    if (x->getType() != Element::string) {
        isc_throw(DhcpConfigError,
                  "invalid type specified for parameter '" << name
                  << "' (" << x->getPosition() << ")");
    }

    return (x->stringValue());
}

int64_t
SimpleParser::getInteger(ConstElementPtr scope, const std::string& name) {
    ConstElementPtr x = scope->get(name);
    if (!x) {
        isc_throw(DhcpConfigError,
                  "missing parameter '" << name << "' ("
                  << scope->getPosition() << ")");
    }
    if (x->getType() != Element::integer) {
        isc_throw(DhcpConfigError,
                  "invalid type specified for parameter '" << name
                  << "' (" << x->getPosition() << ")");
    }

    return (x->intValue());
}

int64_t
SimpleParser::getInteger(isc::data::ConstElementPtr scope, const std::string& name,
                         int64_t min, int64_t max) {
    int64_t tmp = getInteger(scope, name);
    if (tmp < min || tmp > max) {
        isc_throw(OutOfRange,
                  "The '" << name << "' value (" << tmp
                  << ") is not within expected range: (" << min << " - " << max
                  << ")");
    }

    return (tmp);
}

bool
SimpleParser::getBoolean(ConstElementPtr scope, const std::string& name) {
    ConstElementPtr x = scope->get(name);
    if (!x) {
        isc_throw(DhcpConfigError,
                  "missing parameter '" << name << "' ("
                  << scope->getPosition() << ")");
    }
    if (x->getType() != Element::boolean) {
        isc_throw(DhcpConfigError,
                  "invalid type specified for parameter '" << name
                  << "' (" << x->getPosition() << ")");
    }

    return (x->boolValue());
}

IOAddress
SimpleParser::getAddress(const ConstElementPtr& scope,
                         const std::string& name) {
    std::string str = getString(scope, name);
    try {
        return (IOAddress(str));
    } catch (const std::exception& e) {
        isc_throw(DhcpConfigError, "Failed to convert '" << str
                  << "' to address: " << e.what() << "("
                  << getPosition(name, scope) << ")");
    }
}

double
SimpleParser::getDouble(const ConstElementPtr& scope,
                        const std::string& name) {
    ConstElementPtr x = scope->get(name);
    if (!x) {
        isc_throw(DhcpConfigError,
                  "missing parameter '" << name << "' ("
                  << scope->getPosition() << ")");
    }

    if (x->getType() != Element::real) {
        isc_throw(DhcpConfigError,
                  "invalid type specified for parameter '" << name
                  << "' (" << x->getPosition() << ")");
    }

    return (x->doubleValue());
}


const data::Element::Position&
SimpleParser::getPosition(const std::string& name, const data::ConstElementPtr parent) {
    if (!parent) {
        return (data::Element::ZERO_POSITION());
    }
    ConstElementPtr elem = parent->get(name);
    if (!elem) {
        return (parent->getPosition());
    }

    return (elem->getPosition());
}

size_t SimpleParser::setDefaults(ElementPtr scope,
                                 const SimpleDefaults& default_values) {
    size_t cnt = 0;

    // This is the position representing a default value. As the values
    // we're inserting here are not present in whatever the config file
    // came from, we need to make sure it's clearly labeled as default.
    const Element::Position pos("<default-value>", 0, 0);

    // Let's go over all parameters we have defaults for.
    BOOST_FOREACH(SimpleDefault def_value, default_values) {

        // Try if such a parameter is there. If it is, let's
        // skip it, because user knows best *cough*.
        ConstElementPtr x = scope->get(string(def_value.name_));
        if (x) {
            // There is such a value already, skip it.
            continue;
        }

        // There isn't such a value defined, let's create the default
        // value...
        switch (def_value.type_) {
        case Element::string: {
            x.reset(new StringElement(def_value.value_, pos));
            break;
        }
        case Element::integer: {
            try {
                int int_value = boost::lexical_cast<int>(def_value.value_);
                x.reset(new IntElement(int_value, pos));
            }
            catch (const std::exception& ex) {
                isc_throw(BadValue, "Internal error. Integer value expected for: "
                                    << def_value.name_ << ", value is: "
                                    << def_value.value_ );
            }

            break;
        }
        case Element::boolean: {
            bool bool_value;
            if (def_value.value_ == string("true")) {
                bool_value = true;
            } else if (def_value.value_ == string("false")) {
                bool_value = false;
            } else {
                isc_throw(DhcpConfigError,
                          "Internal error. Boolean value specified as "
                          << def_value.value_ << ", expected true or false");
            }
            x.reset(new BoolElement(bool_value, pos));
            break;
        }
        case Element::real: {
            double dbl_value = boost::lexical_cast<double>(def_value.value_);
            x.reset(new DoubleElement(dbl_value, pos));
            break;
        }
        default:
            // No default values for null, list or map
            isc_throw(DhcpConfigError,
                      "Internal error. Incorrect default value type.");
        }

        // ... and insert it into the provided Element tree.
        scope->set(def_value.name_, x);
        ++cnt;
    }

    return (cnt);
}

size_t
SimpleParser::setListDefaults(ConstElementPtr list,
                              const SimpleDefaults& default_values) {
    size_t cnt = 0;
    BOOST_FOREACH(ElementPtr entry, list->listValue()) {
        cnt += setDefaults(entry, default_values);
    }
    return (cnt);
}

size_t
SimpleParser::deriveParams(ConstElementPtr parent,
                           ElementPtr child,
                           const ParamsList& params) {
    if ( (parent->getType() != Element::map) ||
         (child->getType() != Element::map)) {
        return (0);
    }

    size_t cnt = 0;
    BOOST_FOREACH(string param, params) {
        ConstElementPtr x = parent->get(param);
        if (!x) {
            // Parent doesn't define this parameter, so there's
            // nothing to derive from
            continue;
        }

        if (child->get(param)) {
            // Child defines this parameter already. There's
            // nothing to do here.
            continue;
        }

        // Copy the parameters to the child scope.
        child->set(param, x);
        cnt++;
    }

    return (cnt);
}

const util::Triplet<uint32_t>
SimpleParser::parseIntTriplet(const ConstElementPtr& scope,
                              const std::string& name) {
    // Initialize as some compilers complain otherwise.
    uint32_t value = 0;
    bool has_value = false;
    uint32_t min_value = 0;
    bool has_min = false;
    uint32_t max_value = 0;
    bool has_max = false;
    if (scope->contains(name)) {
        value = getInteger(scope, name);
        has_value = true;
    }
    if (scope->contains("min-" + name)) {
        min_value = getInteger(scope, "min-" + name);
        has_min = true;
    }
    if (scope->contains("max-" + name)) {
        max_value = getInteger(scope, "max-" + name);
        has_max = true;
    }
    if (!has_value && !has_min && !has_max) {
        return (util::Triplet<uint32_t>());
    }
    if (has_value) {
        if (!has_min && !has_max) {
            // default only.
            min_value = value;
            max_value = value;
        } else if (!has_min) {
            // default and max.
            min_value = value;
        } else if (!has_max) {
            // default and min.
            max_value = value;
        }
    } else if (has_min) {
        // min only.
        if (!has_max) {
            value = min_value;
            max_value = min_value;
        } else {
            // min and max.
            isc_throw(DhcpConfigError, "have min-" << name << " and max-"
                      << name << " but no " << name << " (default) in "
                      << scope->getPosition());
        }
    } else {
        // max only.
        min_value = max_value;
        value = max_value;
    }
    // Check that min <= max.
    if (min_value > max_value) {
        if (has_min && has_max) {
            isc_throw(DhcpConfigError, "the value of min-" << name << " ("
                      << min_value << ") is not less than max-" << name << " ("
                      << max_value << ")");
        } else if (has_min) {
            // Only min and default so min > default.
            isc_throw(DhcpConfigError, "the value of min-" << name << " ("
                      << min_value << ") is not less than (default) " << name
                      << " (" << value << ")");
        } else {
            // Only default and max so default > max.
            isc_throw(DhcpConfigError, "the value of (default) " << name
                      << " (" << value << ") is not less than max-" << name
                      << " (" << max_value << ")");
        }
    }
    // Check that value is between min and max.
    if ((value < min_value) || (value > max_value)) {
        isc_throw(DhcpConfigError, "the value of (default) " << name << " ("
                  << value << ") is not between min-" << name << " ("
                  << min_value << ") and max-" << name << " ("
                  << max_value << ")");
    }

    return (util::Triplet<uint32_t>(min_value, value, max_value));
}

} // end of isc::dhcp namespace
} // end of isc namespace
