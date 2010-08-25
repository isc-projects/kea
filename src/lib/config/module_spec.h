// Copyright (C) 2010  Internet Systems Consortium.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
// DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
// INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
// FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
// NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
// WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef _MODULE_SPEC_H
#define _MODULE_SPEC_H 1

#include <cc/data.h>

#include <sstream>

using namespace isc::data;

namespace isc { namespace config {

    ///
    /// A standard ModuleSpec exception that is thrown when a
    /// specification is not in the correct form.
    ///
    /// TODO: use jinmei's exception class as a base and not c_str in
    /// what() there
    class ModuleSpecError : public std::exception {
    public:
        ModuleSpecError(std::string m = "Module specification is invalid") : msg(m) {}
        ~ModuleSpecError() throw() {}
        const char* what() const throw() { return (msg.c_str()); }
    private:
        std::string msg;
    };

    ///
    /// The \c ModuleSpec class holds a data specification.
    /// Each module should have a .spec file containing the specification
    /// for configuration and commands for that module.
    /// This class holds that specification, and provides a function to
    /// validate a set of data, to see whether it conforms to the given
    /// specification
    ///
    /// The form of the specification is described in doc/ (TODO)
    ///
    class ModuleSpec {
    public:
        ModuleSpec() {};
        /// Create a \c ModuleSpec instance with the given data as
        /// the specification
        /// \param e The Element containing the data specification
        explicit ModuleSpec(ConstElementPtr e, const bool check = true)
            throw(ModuleSpecError);

        /// Returns the commands part of the specification as an
        /// ElementPtr, returns an empty ElementPtr if there is none
        /// \return ElementPtr Shared pointer to the commands
        ///                    part of the specification
        ConstElementPtr getCommandsSpec() const;

        /// Returns the configuration part of the specification as an
        /// ElementPtr
        /// \return ElementPtr Shared pointer to the configuration
        ///                    part of the specification
        ConstElementPtr getConfigSpec() const;

        /// Returns the full module specification as an ElementPtr
        /// \return ElementPtr Shared pointer to the specification
        ConstElementPtr getFullSpec() const { return module_specification; }

        /// Returns the module name as specified by the specification
        const std::string getModuleName() const;
        
        /// Returns the module description as specified by the specification
        /// returns an empty string if there is no description
        const std::string getModuleDescription() const;
        
        // returns true if the given element conforms to this data
        // configuration specification
        /// Validates the given configuration data for this specification.
        /// \param data The base \c Element of the data to check
        /// \return true if the data conforms to the specification,
        /// false otherwise.
        bool validate_config(ConstElementPtr data,
                             const bool full = false) const;

        /// errors must be of type ListElement
        bool validate_config(ConstElementPtr data, const bool full,
                             ElementPtr errors) const;

    private:
        bool validate_item(ConstElementPtr spec, ConstElementPtr data,
                           const bool full, ElementPtr errors) const;
        bool validate_spec(ConstElementPtr spec, ConstElementPtr data,
                           const bool full, ElementPtr errors) const;
        bool validate_spec_list(ConstElementPtr spec, ConstElementPtr data,
                                const bool full, ElementPtr errors) const;

        ConstElementPtr module_specification;
    };

    /// Creates a \c ModuleSpec instance from the contents
    /// of the file given by file_name.
    /// If check is true, and the module specification is not of
    /// the correct form, a ModuleSpecError is thrown. If the file
    /// could not be parse, a ParseError is thrown.
    /// \param file_name The file to be opened and parsed
    /// \param check If true, the module specification in the file
    /// is checked to be of the correct form
    ModuleSpec
    moduleSpecFromFile(const std::string& file_name, const bool check = true)
                       throw(JSONError, ModuleSpecError);

    /// Creates a \c ModuleSpec instance from the given input
    /// stream that contains the contents of a .spec file.
    /// If check is true, and the module specification is not of
    /// the correct form, a ModuleSpecError is thrown. If the
    /// file could not be parsed, a ParseError is thrown.
    /// \param in The std::istream containing the .spec file data
    /// \param check If true, the module specification is checked
    /// to be of the correct form
    ModuleSpec
    moduleSpecFromFile(std::ifstream& in, const bool check = true)
                       throw(JSONError, ModuleSpecError);
} }

#endif // _DATA_DEF_H

// Local Variables: 
// mode: c++
// End: 
