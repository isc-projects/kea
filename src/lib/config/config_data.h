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

/// This exception is thrown when the caller is trying to access
/// data that doesn't exist (i.e. with an identifier that does not
/// point to anything defined in the .spec file)
class DataNotFoundError : public isc::Exception {
public:
    DataNotFoundError(const char* file, size_t line, const std::string& what) :
        isc::Exception(file, line, what) {}
};
    
class ConfigData {
public:
    /// Constructs a ConfigData option with no specification and an
    /// empty configuration.
    ConfigData() { _config = Element::createMap(); };

    /// Constructs a ConfigData option with the given specification
    /// and an empty configuration.
    /// \param module_spec A ModuleSpec for the relevant module
    ConfigData(const ModuleSpec& module_spec) : _module_spec(module_spec) { _config = Element::createMap(); }

    virtual ~ConfigData() {};

    /// Returns the value currently set for the given identifier
    /// If no value is set, the default value (as specified by the
    /// .spec file) is returned. If there is no value and no default,
    /// an empty ElementPtr is returned.
    /// Raises a DataNotFoundError if the identifier is bad.
    /// \param identifier The identifier pointing to the configuration
    ///        value that is to be returned
    ConstElementPtr getValue(const std::string& identifier) const;

    /// Returns the value currently set for the given identifier
    /// If no value is set, the default value (as specified by the
    /// .spec file) is returned. If there is no value and no default,
    /// an empty ElementPtr is returned.
    /// Raises a DataNotFoundError if the identifier is bad.
    /// \param is_default will be set to true if the value is taken
    ///                   from the specifications item_default setting,
    ///                   false otherwise
    /// \param identifier The identifier pointing to the configuration
    ///        value that is to be returned
    ConstElementPtr getValue(bool& is_default,
                             const std::string& identifier) const;

    /// Returns the ModuleSpec associated with this ConfigData object
    const ModuleSpec& getModuleSpec() const { return (_module_spec); }

    /// Set the ModuleSpec associated with this ConfigData object
    void setModuleSpec(ModuleSpec module_spec) { _module_spec = module_spec; };

    /// Set the local configuration (i.e. all non-default values)
    /// \param config An ElementPtr pointing to a MapElement containing
    ///        *all* non-default configuration values. Existing values
    ///        will be removed.
    void setLocalConfig(ElementPtr config) { _config = config; }

    /// Returns the local (i.e. non-default) configuration.
    /// \returns An ElementPtr pointing to a MapElement containing all
    ///          non-default configuration options.
    ElementPtr getLocalConfig() { return (_config); }

    /// Returns a list of all possible configuration options as specified
    ///         by the ModuleSpec.
    /// \param identifier If given, show the items at the given identifier
    ///                   (iff that is also a MapElement)
    /// \param recurse If true, child MapElements will be traversed to
    ///                add their identifiers to the result list
    /// \return An ElementPtr pointing to a ListElement containing
    ///         StringElements that specify the identifiers at the given
    ///         location (or all possible identifiers if identifier==""
    ///         and recurse==false)
    ConstElementPtr getItemList(const std::string& identifier = "",
                                bool recurse = false) const;

    /// Returns all current configuration settings (both non-default and default).
    /// \return An ElementPtr pointing to a MapElement containing
    ///         string->value elements, where the string is the
    ///         full identifier of the configuration option and the
    ///         value is an ElementPtr with the value.
    ConstElementPtr getFullConfig() const;

private:
    ElementPtr _config;
    ModuleSpec _module_spec;
};

}
}
#endif

// Local Variables: 
// mode: c++
// End: 
