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

namespace isc { namespace data {

    ///
    /// A standard ModuleSpec exception that is thrown when a
    /// specification is not in the correct form.
    ///
    /// TODO: use jinmei's exception class as a base and not c_str in
    /// what() there
    class ModuleSpecError : public std::exception {
    public:
        ModuleSpecError(std::string m = "Data definition is invalid") : msg(m) {}
        ~ModuleSpecError() throw() {}
        const char* what() const throw() { return msg.c_str(); }
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
        explicit ModuleSpec() {};
        /// Create a \c ModuleSpec instance with the given data as
        /// the specification
        /// \param e The Element containing the data specification
        explicit ModuleSpec(ElementPtr e) : definition(e) {};

        /// Creates a \c ModuleSpec instance from the contents
        /// of the file given by file_name.
        /// If check is true, and the definition is not of the correct
        /// form, a ModuleSpecError is thrown. If the file could
        /// not be parse, a ParseError is thrown.
        /// \param file_name The file to be opened and parsed
        /// \param check If true, the data definition in the file is
        /// checked to be of the correct form
        ModuleSpec(const std::string& file_name, const bool check = true)
                       throw(ParseError, ModuleSpecError);

        // todo: make check default false, or leave out option completely and always check?
        /// Creates a \c ModuleSpec instance from the given input
        /// stream that contains the contents of a .spec file.
        /// If check is true, and the definition is not of
        /// the correct form, a ModuleSpecError is thrown. If the
        /// file could not be parsed, a ParseError is thrown.
        /// \param in The std::istream containing the .spec file data
        /// \param check If true, the data definition is checked to be
        /// of the correct form
        explicit ModuleSpec(std::istream& in, const bool check = true)
                                throw(ParseError, ModuleSpecError);

        /// Returns the base \c element of the data definition contained
        /// by this instance
        /// \return ElementPtr Shared pointer to the data definition
        const ElementPtr getDefinition() { return definition; };
        // returns true if the given element conforms to this data
        // definition scheme
        /// Validates the given data for this specification.
        /// \param data The base \c Element of the data to check
        /// \return true if the data conforms to the specification,
        /// false otherwise.
        bool validate(const ElementPtr data);

    private:
        bool validate_item(const ElementPtr spec, const ElementPtr data);
        bool validate_spec(const ElementPtr spec, const ElementPtr data);
        bool validate_spec_list(const ElementPtr spec, const ElementPtr data);

        ElementPtr definition;
    };

} }

#endif // _DATA_DEF_H
