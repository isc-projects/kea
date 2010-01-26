#ifndef _DATA_DEF_H
#define _DATA_DEF_H 1

#include "data.h"

#include <sstream>

namespace isc { namespace data {

    ///
    /// A standard DataDefinition exception that is thrown when a
    /// specification is not in the correct form.
    ///
    /// TODO: use jinmei's exception class as a base and not c_str in
    /// what() there
    class DataDefinitionError : public std::exception {
    public:
        DataDefinitionError(std::string m = "Data definition is invalid") : msg(m) {}
        ~DataDefinitionError() throw() {}
        const char* what() const throw() { return msg.c_str(); }
    private:
        std::string msg;
    };

    ///
    /// The \c DataDefinition class holds a data specification.
    /// Each module should have a .spec file containing the specification
    /// for configuration and commands for that module.
    /// This class holds that specification, and provides a function to
    /// validate a set of data, to see whether it conforms to the given
    /// specification
    ///
    /// The form of the specification is described in doc/ (TODO)
    ///
    class DataDefinition {
    public:
        explicit DataDefinition() {};
        /// Create a \c DataDefinition instance with the given data as
        /// the specification
        /// \param e The Element containing the data specification
        explicit DataDefinition(ElementPtr e) : definition(e) {};
        // todo: make check default false, or leave out option completely and always check?
        /// Creates a \c DataDefinition instance from the given .spec
        /// file stream. If check is true, and the definition is not of
        /// the correct form, a DataDefinitionError is thrown. If the
        /// file could not be parsed, a ParseError is thrown.
        /// \param in The std::istream containing the .spec file data
        /// \param check If true, the data definition is checked to be
        /// of the correct form
        explicit DataDefinition(std::istream& in, const bool check = true)
                                throw(ParseError, DataDefinitionError);

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
