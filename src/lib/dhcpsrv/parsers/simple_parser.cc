#include <dhcpsrv/parsers/simple_parser.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <cc/data.h>
#include <string>

using namespace std;
using namespace isc::data;

namespace isc {
namespace dhcp {

/// This table defines default values for option definitions in DHCPv4
const SimpleDefaults OPTION4_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp4"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for option definitions in DHCPv6
const SimpleDefaults OPTION6_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp6"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for options in DHCPv4
const SimpleDefaults OPTION4_DEFAULTS = {
    { "space",        Element::string,  "dhcp4"},
    { "csv-format",   Element::boolean, "true"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for options in DHCPv6
const SimpleDefaults OPTION6_DEFAULTS = {
    { "space",        Element::string,  "dhcp6"},
    { "csv-format",   Element::boolean, "true"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for both DHCPv4 and DHCPv6
const SimpleDefaults GLOBAL_DEFAULTS = {
    { "renew-timer",        Element::integer, "900" },
    { "rebind-timer",       Element::integer, "1800" },
    { "preferred-lifetime", Element::integer, "3600" },
    { "valid-lifetime",     Element::integer, "7200" }
};

std::string
SimpleParser::getString(isc::data::ConstElementPtr scope, const std::string& name) {
    ConstElementPtr x = scope->get(name);
    if (!x) {
        isc_throw(BadValue, "Element " << name << " not found");
    }
    if (x->getType() != Element::string) {
        isc_throw(BadValue, "Element " << name << " found, but is not a string");
    }

    return (x->stringValue());
}

int64_t
SimpleParser::getInteger(isc::data::ConstElementPtr scope, const std::string& name) {
    ConstElementPtr x = scope->get(name);
    if (!x) {
        isc_throw(BadValue, "Element " << name << " not found");
    }
    if (x->getType() != Element::integer) {
        isc_throw(BadValue, "Element " << name << " found, but is not an integer");
    }

    return (x->intValue());
}

bool
SimpleParser::getBoolean(isc::data::ConstElementPtr scope, const std::string& name) {
    ConstElementPtr x = scope->get(name);
    if (!x) {
        isc_throw(BadValue, "Element " << name << " not found");
    }
    if (x->getType() != Element::boolean) {
        isc_throw(BadValue, "Element " << name << " found, but is not a boolean");
    }

    return (x->boolValue());
}

const data::Element::Position&
SimpleParser::getPosition(const std::string& name, const data::ConstElementPtr parent) const {
    if (!parent) {
        return (data::Element::ZERO_POSITION());
    }
    ConstElementPtr elem = parent->get(name);
    if (!elem) {
        return (data::Element::ZERO_POSITION());
    }
    return (elem->getPosition());
}

size_t SimpleParser::setDefaults(isc::data::ElementPtr scope,
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
            int int_value = boost::lexical_cast<int>(def_value.value_);
            x.reset(new IntElement(int_value, pos));
            break;
        }
        case Element::boolean: {
            bool bool_value;
            if (def_value.value_ == string("true")) {
                bool_value = true;
            } else if (def_value.value_ == string("false")) {
                bool_value = false;
            } else {
                isc_throw(BadValue, "Internal error. Boolean value specified as "
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
            isc_throw(BadValue, "Internal error. Incorrect default value type.");
        }

        // ... and insert it into the provided Element tree.
        scope->set(def_value.name_, x);
        cnt++;
    }

    return (cnt);
}

size_t SimpleParser::setGlobalDefaults(isc::data::ElementPtr global) {
    return (setDefaults(global, GLOBAL_DEFAULTS));
}

size_t SimpleParser::setOptionDefaults(isc::data::ElementPtr option, bool v6) {
    return (setDefaults(option, v6?OPTION6_DEFAULTS : OPTION4_DEFAULTS));
}

size_t SimpleParser::setOptionListDefaults(isc::data::ElementPtr option_list, bool v6) {
    size_t cnt = 0;
    BOOST_FOREACH(ElementPtr single_option, option_list->listValue()) {
        cnt += setOptionDefaults(single_option, v6);
    }
    return (cnt);
}

size_t SimpleParser::setOptionDefDefaults(isc::data::ElementPtr option_def, bool v6) {
    return (setDefaults(option_def, v6? OPTION6_DEF_DEFAULTS : OPTION4_DEF_DEFAULTS));
}

size_t SimpleParser::setOptionDefListDefaults(isc::data::ElementPtr option_def_list,
                                              bool v6) {
    size_t cnt = 0;
    BOOST_FOREACH(ElementPtr single_def, option_def_list->listValue()) {
        cnt += setOptionDefDefaults(single_def, v6);
    }
    return (cnt);
}


size_t SimpleParser::setAllDefaults(isc::data::ElementPtr global, bool v6) {
    size_t cnt = 0;

    // Set global defaults first.
    //cnt = setGlobalDefaults(global);

    // Now set option defintion defaults for each specified option definition
    ConstElementPtr option_defs = global->get("option-def");
    if (option_defs) {
        BOOST_FOREACH(ElementPtr single_def, option_defs->listValue()) {
            cnt += setOptionDefDefaults(single_def, v6);
        }
    }

    ConstElementPtr options = global->get("option-data");
    if (options) {
        BOOST_FOREACH(ElementPtr single_option, options->listValue()) {
            cnt += setOptionDefaults(single_option, v6);
        }
        //setOptionListDefaults(options);
    }

    return (cnt);
}

size_t
SimpleParser::deriveParams(isc::data::ConstElementPtr parent,
                           isc::data::ElementPtr child,
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

}; // end of isc::dhcp namespace
}; // end of isc namespace
