// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __CONFIG_DATA_H
#define __CONFIG_DATA_H 1

#include <string>
#include <vector>

#include <config/module_spec.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace config {

class DataNotFoundError : public isc::Exception {
public:
    DataNotFoundError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};
    
class ConfigData {
public:
    ConfigData() { _config = Element::createFromString("{}"); };
    ConfigData(const ModuleSpec& module_spec) : _module_spec(module_spec) { _config = Element::createFromString("{}"); }

    ElementPtr getValue(const std::string& identifier);
    ElementPtr getValue(bool &is_default, const std::string& identifier);
    const ModuleSpec getModuleSpec() { return _module_spec; };
    void setModuleSpec(ModuleSpec module_spec) { _module_spec = module_spec; };
    void setLocalConfig(ElementPtr config) { _config = config; }
    ElementPtr getLocalConfig() { return _config; }
    ElementPtr getItemList(const std::string& identifier, bool recurse = false);
    ElementPtr getFullConfig();

private:
    ElementPtr _config;
    ModuleSpec _module_spec;
};

}
}
#endif
