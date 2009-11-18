#ifndef _DATA_DEF_H
#define _DATA_DEF_H 1

#include "data.h"

#include <sstream>

namespace ISC { namespace Data {

    class DataDefinitionError : public std::exception {
    public:
        DataDefinitionError(std::string m = "Data definition is invalid") : msg(m) {}
        ~DataDefinitionError() throw() {}
        const char* what() const throw() { return msg.c_str(); }
    private:
        std::string msg;
    };

    class DataDefinition {
    public:
        explicit DataDefinition() {};
        explicit DataDefinition(ElementPtr e) : definition(e) {};
        // todo: make check default false, or leave out option completely and always check?
        explicit DataDefinition(std::istream& in, const bool check = true)
                                throw(ParseError, DataDefinitionError);

        const ElementPtr getDefinition() { return definition; };
        // returns true if the given element conforms to this data
        // definition scheme
        bool validate(const ElementPtr data);

    private:
        bool validate_item(const ElementPtr spec, const ElementPtr data);
        bool validate_spec(const ElementPtr spec, const ElementPtr data);
        bool validate_spec_list(const ElementPtr spec, const ElementPtr data);

        ElementPtr definition;
    };

} }

#endif // _DATA_DEF_H
