// Copyright (C) 2010-2015 Internet Systems Consortium.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MODULE_SPEC_H
#define MODULE_SPEC_H 1

#include <cc/data.h>

#include <sstream>

namespace isc { namespace config {

    ///
    /// A standard ModuleSpec exception that is thrown when a
    /// specification is not in the correct form.
    ///
    class ModuleSpecError : public isc::Exception {
    public:
        ModuleSpecError(const char* file, size_t line,
                        const char* what = "Module specification is invalid") :
            isc::Exception(file, line, what) {}
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
        /// \param check If false, the module specification in the file
        /// is not checked to be of the correct form.
        explicit ModuleSpec(isc::data::ConstElementPtr e,
                            const bool check = true)
            throw(ModuleSpecError);

        /// Returns the commands part of the specification as an
        /// ElementPtr, returns an empty ElementPtr if there is none
        /// \return ElementPtr Shared pointer to the commands
        ///                    part of the specification
        isc::data::ConstElementPtr getCommandsSpec() const;

        /// Returns the configuration part of the specification as an
        /// ElementPtr
        /// \return ElementPtr Shared pointer to the configuration
        ///                    part of the specification
        isc::data::ConstElementPtr getConfigSpec() const;

        /// Returns the statistics part of the specification as an
        /// ElementPtr
        /// \return ElementPtr Shared pointer to the statistics
        ///                    part of the specification
        isc::data::ConstElementPtr getStatisticsSpec() const;

        /// Returns the full module specification as an ElementPtr
        /// \return ElementPtr Shared pointer to the specification
        isc::data::ConstElementPtr getFullSpec() const {
            return module_specification;
        }

        /// Returns the module name as specified by the specification
        const std::string getModuleName() const;
        
        /// Returns the module description as specified by the specification
        /// returns an empty string if there is no description
        const std::string getModuleDescription() const;
        
        // returns true if the given element conforms to this data
        // configuration specification
        /// Validates the given configuration data for this specification.
        /// \param data The base \c Element of the data to check
        /// \param full If true, all non-optional configuration parameters
        /// must be specified.
        /// \return true if the data conforms to the specification,
        /// false otherwise.
        bool validateConfig(isc::data::ConstElementPtr data,
                             const bool full = false) const;

        // returns true if the given element conforms to this data
        // statistics specification
        /// Validates the given statistics data for this specification.
        /// \param data The base \c Element of the data to check
        /// \param full If true, all non-optional statistics parameters
        /// must be specified.
        /// \return true if the data conforms to the specification,
        /// false otherwise.
        bool validateStatistics(isc::data::ConstElementPtr data,
                             const bool full = false) const;

        /// Validates the arguments for the given command
        ///
        /// This checks the command and argument against the
        /// specification in the module's .spec file.
        ///
        /// A command is considered valid if:
        /// - it is known (the 'command' string must have an entry in
        ///                the specification)
        /// - the args is a MapElement
        /// - args contains all mandatory arguments
        /// - args does not contain unknown arguments
        /// - all arguments in args match their specification
        /// If all of these are true, this function returns \c true
        /// If not, this method returns \c false
        ///
        /// Example usage:
        /// \code
        ///     ElementPtr errors = Element::createList();
        ///     if (module_specification_.validateCommand(cmd_str,
        ///                                               arg,
        ///                                               errors)) {
        ///         std::cout << "Command is valid" << std::endl;
        ///     } else {
        ///         std::cout << "Command is invalid: " << std::endl;
        ///         BOOST_FOREACH(ConstElementPtr error,
        ///                       errors->listValue()) {
        ///             std::cout << error->stringValue() << std::endl;
        ///         }
        ///     }
        /// \endcode
        ///
        /// \param command The command to validate the arguments for
        /// \param args A dict containing the command parameters
        /// \param errors An ElementPtr pointing to a ListElement. Any
        ///               errors that are found are added as
        ///               StringElements to this list
        /// \return true if the command is known and the parameters are correct
        ///         false otherwise
        bool validateCommand(const std::string& command,
                              isc::data::ConstElementPtr args,
                              isc::data::ElementPtr errors) const;


        /// errors must be of type ListElement
        bool validateConfig(isc::data::ConstElementPtr data, const bool full,
                             isc::data::ElementPtr errors) const;

        /// errors must be of type ListElement
        bool validateStatistics(isc::data::ConstElementPtr data, const bool full,
                                isc::data::ElementPtr errors) const;

    private:
        bool validateItem(isc::data::ConstElementPtr spec,
                          isc::data::ConstElementPtr data,
                          const bool full,
                          isc::data::ElementPtr errors) const;
        bool validateSpec(isc::data::ConstElementPtr spec,
                           isc::data::ConstElementPtr data,
                           const bool full,
                           isc::data::ElementPtr errors) const;
        bool validateSpecList(isc::data::ConstElementPtr spec,
                                isc::data::ConstElementPtr data,
                                const bool full,
                                isc::data::ElementPtr errors) const;

        isc::data::ConstElementPtr module_specification;
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
        throw(isc::data::JSONError, ModuleSpecError);

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
                       throw(isc::data::JSONError, ModuleSpecError);
} }

#endif // _DATA_DEF_H

// Local Variables: 
// mode: c++
// End: 
