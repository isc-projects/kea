// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/env_var_wrapper.h>

#include <cstdlib>

namespace isc {
namespace test {

EnvVarWrapper::EnvVarWrapper(const std::string& name) : name_(name) {
    original_value_ = getValue();
}

EnvVarWrapper::~EnvVarWrapper() {
    setValue(original_value_);
}

std::string
EnvVarWrapper::getOriginalValue() const {
    return (original_value_);
}

std::string
EnvVarWrapper::getValue() const {
    auto value = getenv(name_.c_str());
    return (value ? std::string(value) : std::string(""));
}

void
EnvVarWrapper::setValue(const std::string value /* = "" */) {
    if (value.empty()) {
        unsetenv(name_.c_str());
    } else {
        setenv(name_.c_str(), value.c_str(), 1);
    }
}

}  // end of isc::test namespace
}  // end of isc namespace
